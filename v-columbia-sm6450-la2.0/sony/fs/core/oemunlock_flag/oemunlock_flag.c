/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "string.h"
#include "oemunlock_flag.h"
#include "fcserr.h"
#include "fcslog.h"
#include "fcs_defines.h"
#include "rule_verifier.h"
#include "rule_rootcert.h"
#include "cms_verifier.h"

#define OEMUNLOCK_FLAG_PARTITION "OEMunlocking"
#define FRP_HEADER_SIZE (40)
#define SHA_256_HASH_SIZE (32)

int oemunlock_flag_verify(
		struct ks_ctx *ks,
		uint8_t *phone_id,
		size_t phone_id_len,
		struct embed_rootcert_item *embed_rootcert_list,
		size_t embed_rootcert_list_count,
		uint8_t *oemunlock_request,
		size_t oemunlock_request_len,
		uint8_t *frp_data,
		size_t frp_data_len)
{
	int res = -FCSERR_EINVAL;
	uint8_t *rootcerts = NULL;
	size_t rootcerts_length = 0;
	struct rule_verifier *rule_handle = NULL;
	uint32_t usage;
	char *param = NULL;
	uint8_t magic[4] = {0x19, 0x90, 0x18, 0x73};
	uint8_t zero[4] = {0x0};
	struct dev_binding binding = {};
	uint8_t *cms_payload = NULL;
	size_t cms_payload_length = 0;

	/* Check in parameters */
	if ((ks == NULL) ||
		(phone_id == NULL) ||
		(phone_id_len == 0) ||
		(embed_rootcert_list == NULL) ||
		(embed_rootcert_list_count == 0) ||
		(oemunlock_request == NULL) ||
		(oemunlock_request_len == 0) ||
		(frp_data == NULL) ||
		(frp_data_len == 0) ||
		frp_data_len < FRP_HEADER_SIZE) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto exit;
	}

	binding.imei = phone_id;
	binding.imei_sz = phone_id_len;

	/* Check if there is google account
	 * data in frp_data.
	 * google frp data format:
	 * SHA-256 of partition (32 bytes)
	 * Magic "0x19901873" (4 bytes)
	 * Size of rest of the data (4 bytes)
	 * ... data ..
	 */

	/* Check magic number */
	/* If account is present the size must not be 0 */
	if ((memcmp(&frp_data[SHA_256_HASH_SIZE], &magic,
			sizeof(magic)) == 0) &&
		(memcmp(&frp_data[SHA_256_HASH_SIZE] + sizeof(magic), &zero,
			sizeof(zero)) != 0)) {
		FCS_LOG_ERR("Google account present.\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	res = rule_get_roots(RULE_USAGE_FLASH,
			embed_rootcert_list,
			embed_rootcert_list_count,
			ks,
			&rootcerts,
			&rootcerts_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get roots: (%d)\n", res);
		goto exit;
	}

	res = rule_init(&rule_handle, &binding, RULE_USAGE_FLASH);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init rule session\n");
		goto exit;
	}

	res = cms_verify(oemunlock_request, oemunlock_request_len,
			rule_handle,
			rootcerts, rootcerts_length,
			NULL, 0,
			&cms_payload, &cms_payload_length);
	if (res < 0) {
		FCS_LOG_ERR("Failed to verify cms\n");
		goto exit;
	}

	/* OEM unlock cms message should not contain a payload*/
	if (cms_payload != NULL || cms_payload_length != 0) {
		FCS_LOG_ERR("Cms should not contain a payload\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	res = rule_get_actual_usage(rule_handle, &usage, &param);
	if (res < 0) {
		FCS_LOG_ERR("Failed to get actual usage\n");
		goto exit;
	}

	if ((param == NULL) ||
			(usage != RULE_USAGE_FLASH) ||
			strncmp(param, OEMUNLOCK_FLAG_PARTITION,
			strlen(OEMUNLOCK_FLAG_PARTITION))) {
		FCS_LOG_ERR("Wrong usage and/or partition name\n");
		res = -FCSERR_EUSAGE;
		goto exit;
	}

exit:
	free(cms_payload);
	return res;
}
