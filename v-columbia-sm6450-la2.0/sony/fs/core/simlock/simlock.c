/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "simlock.h"
#include "digest.h"
#include "simlock_parser.h"
#include "asahi_verifier.h"
#include "rule_types.h"
#include "rule_verifier.h"
#include "rule_rootcert.h"
#include "fcserr.h"
#include "fcslog.h"
#include "cms_verifier.h"
#include "fcs_defines.h"
#include "convert.h"
#include <string.h>

static int simlock_digest_and_verify(void *sl_parser,
		struct embed_rootcert_item *embed_rootcert_list,
		size_t embed_rootcert_list_count,
		unsigned int opid)
{
	int res;
	uint8_t *rootcerts = NULL;
	size_t rootcerts_length = 0;
	struct rule_verifier *rule_handle = NULL;
	struct digest *dgst = NULL;
	uint32_t n_segments = 0;
	uint8_t *verify_data = NULL;
	uint32_t verify_data_length = 0;
	uint8_t *calc_hash = NULL;
	uint32_t calc_hash_length = 0;
	uint8_t *asahi = NULL;
	uint32_t asahi_length = 0;
	uint32_t i = 0;
	struct dev_binding binding = {};

	if (sl_parser == NULL) {
		FCS_LOG_ERR("sl_parser == NULL\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	res = simlock_parser_get_asahi_signature(
			sl_parser, &asahi, &asahi_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get asahi signature: (%d)\n", res);
		goto exit;
	}

	/* Verifying simlock signature and payload Begin */
	res = simlock_parser_get_image_hash_segments(&n_segments);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get number of digest segments: (%d)\n",
				res);
		goto exit;
	}

	res = digest_sha256_init(&dgst);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init digest calculation: (%d)\n",
				res);
		goto exit;
	}

	for (i = 0; i < n_segments; i++) {
		res = simlock_parser_get_image_hash_segment(
				sl_parser, i, &verify_data,
				&verify_data_length);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get digest segment: (%d)\n",
					res);
			goto exit;
		}

		res = digest_sha256_update(
				dgst, verify_data, verify_data_length);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to update digest: (%d)\n",
					res);
			goto exit;
		}
	}

	res = digest_sha256_final(
			dgst, &calc_hash, &calc_hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize digest: (%d)\n",
				res);
		goto exit;
	}

	res = rule_get_roots(RULE_USAGE_SIMLOCK,
			embed_rootcert_list,
			embed_rootcert_list_count,
			NULL,
			&rootcerts,
			&rootcerts_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get roots: (%d)\n", res);
		goto exit;
	}


	res = rule_init(&rule_handle, &binding, RULE_USAGE_SIMLOCK);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init rule session\n");
		goto exit;
	}

	if (opid > 0) {
		res = rule_set_opid(rule_handle, opid);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to set opid\n");
			goto exit;
		}
	}

	res = asahi_verify(
			rule_handle,
			rootcerts,
			rootcerts_length,
			asahi,
			asahi_length,
			calc_hash,
			calc_hash_length);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("Failed to verify asahi signature: (%d)\n",
				res);

exit:
	if (dgst != NULL)
		digest_sha256_deinit(dgst);
	rule_deinit(rule_handle);
	free(rootcerts);

	return res;
}

static int simlock_verify_s1(
	uint8_t *imei,
	size_t imei_length,
	struct embed_rootcert_item *embed_rootcert_list,
	size_t embed_rootcert_list_count,
	uint8_t *data,
	size_t data_length,
	uint8_t *signature,
	size_t signature_length,
	unsigned int opid,
	unsigned int *range_offset,
	size_t *range_length)
{
	int res = FCSERR_OK;
	void *sl_parser = NULL;
	uint8_t *sl_parameters = NULL;
	uint32_t sl_parameters_size;

	/* input params is checked in simlock_verify */

	/* All buffers must be kept for the duration of the sl_parser */
	res = simlock_parser_init(&sl_parser, SIMLOCK_PHONE_DATA_TYPE_IMEI,
			imei, imei_length,
			data, data_length,
			signature, signature_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init simlock parser: (%d)\n", res);
		goto exit;
	}

	res = simlock_digest_and_verify(sl_parser,
				embed_rootcert_list,
				embed_rootcert_list_count,
				opid);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify simlock: (%d)\n", res);
		goto exit;
	}

	/* Read out the parameter part of the simlock data unit */
	res = simlock_parser_get_parameters(sl_parser, &sl_parameters,
			&sl_parameters_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get simlock parameters: (%d)\n", res);
		goto exit;
	}

	*range_offset = sl_parameters - data;
	*range_length = sl_parameters_size;

exit:
	if (sl_parser != NULL)
		simlock_parser_deinit(sl_parser);
	return res;
}

static int simlock_verify_cms(
	uint8_t *imei,
	size_t imei_length,
	struct embed_rootcert_item *embed_rootcert_list,
	size_t embed_rootcert_list_count,
	uint8_t *data,
	size_t data_length,
	uint8_t *signature,
	size_t signature_length,
	unsigned int opid,
	unsigned int *range_offset,
	size_t *range_length)
{
	uint8_t *rootcerts = NULL;
	size_t rootcerts_length = 0;
	uint8_t *pld = NULL;
	size_t pld_sz;
	int res;
	struct rule_verifier *rule_handle = NULL;
	struct dev_binding binding = {};
	int start;
	int len;
	uint8_t  imei_ascii[IMEI_ASCII_SIZE + 1] = {0};

	/* input params is checked in simlock_verify */

	res = rule_get_roots(RULE_USAGE_SIMLOCK,
			embed_rootcert_list,
			embed_rootcert_list_count,
			NULL,
			&rootcerts,
			&rootcerts_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get roots: (%d)\n", res);
		goto exit;
	}

	/* make sure that we have zeros in struct on all compiler versions */
	memset(&binding, 0, sizeof(binding));

	/* convert to ascii and remove last byte */
	res = bin_to_ascii(
		(char *)imei_ascii, sizeof(imei_ascii), imei, imei_length - 1);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to convert imei (%d)\n", res);
		goto exit;
	}

	binding.imei = imei_ascii;
	binding.imei_sz = sizeof(imei_ascii) - 1; /* remove null termination */

	res = rule_init(&rule_handle, &binding, RULE_USAGE_SIMLOCK);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init rule session\n");
		goto exit;
	}

	/* set opid if available */
	if (opid > 0) {
		res = rule_set_opid(rule_handle, opid);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to set opid\n");
			goto exit;
		}
	}

	res = cms_verify(
		signature, signature_length, rule_handle, rootcerts,
		rootcerts_length, NULL, 0, &pld, &pld_sz);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify cms\n");
		goto exit;
	}

	/* get start, len attributes */
	res = rule_get_simlock_range(rule_handle, &start, &len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Could not get range attributes\n");
		goto exit;
	}

	/* sanity check */
	if (start + len > (int)data_length) {
		FCS_LOG_ERR("Invalid range, start: %d, len: %d, exp sz: %d\n",
			    start, len, data_length);
		res = -FCSERR_ESIZE;
		goto exit;
	}


	*range_offset = start;
	*range_length = len;

	/* verify simlock data */
	res = digest_sha256_verify(data + start, len, pld);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Hash verification fail\n");
		goto exit;
	}

exit:
	free(rootcerts);
	free(pld);
	rule_deinit(rule_handle);
	return res;
}

static int simlock_is_s1(
	uint8_t *imei,
	size_t imei_length,
	uint8_t *data,
	size_t data_length,
	uint8_t *signature,
	size_t signature_length)
{
	int res = FCSERR_OK;
	void *sl_parser = NULL;

	res = simlock_parser_init(&sl_parser, SIMLOCK_PHONE_DATA_TYPE_IMEI,
			imei, imei_length,
			data, data_length,
			signature, signature_length);
	if (res == FCSERR_OK) {
		/* we have an asahi signature */
		simlock_parser_deinit(sl_parser);
		return 1;
	}

	/* not a valid s1 signature, might be cms */
	return 0;
}

int simlock_verify(
	uint8_t *imei,
	size_t imei_length,
	struct embed_rootcert_item *embed_rootcert_list,
	size_t embed_rootcert_list_count,
	uint8_t *data,
	size_t data_length,
	uint8_t *signature,
	size_t signature_length,
	unsigned int opid,
	unsigned int *range_offset,
	size_t *range_length)
{
	if (imei == NULL || imei_length == 0 || embed_rootcert_list == NULL ||
	    embed_rootcert_list_count == 0 || data == NULL ||
	    data_length == 0 || signature == NULL || signature_length == 0 ||
	    range_offset == NULL || range_length == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (simlock_is_s1(
		    imei, imei_length, data, data_length,
		    signature, signature_length)) {
		return simlock_verify_s1(
			imei, imei_length, embed_rootcert_list,
			embed_rootcert_list_count, data, data_length,
			signature, signature_length, opid, range_offset,
			range_length);
	}

	return simlock_verify_cms(
		imei, imei_length, embed_rootcert_list,
		embed_rootcert_list_count, data, data_length, signature,
		signature_length, opid, range_offset, range_length);
}
