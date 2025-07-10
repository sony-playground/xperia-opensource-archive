/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "sin_verifier.h"
#include "asahi_verifier.h"
#include <stdlib.h>
#include "fcserr.h"
#include "fcslog.h"
#include "digest.h"

/**
 * Exported functions
 */
int sin_verify(
		struct rule_verifier *rule,
		uint8_t *rootcert_buf,
		size_t rootcert_buf_length,
		uint8_t *sin_buffer,
		uint32_t sin_buffer_length,
		struct sin_header **sin_parser_handle)
{
	int res = -FCSERR_EINVAL;
	struct sin_header *sin_handle;
	struct sin_asahi_signature *asahi_signature;
	struct sin_header_static_field *sin_static_header;
	uint32_t hash_segment_count;
	uint8_t *verify_data;
	uint32_t verify_data_length;
	struct digest *header_digest = NULL;
	uint8_t *header_hash = NULL;
	uint32_t header_hash_length = 0;
	uint32_t i;

	sin_handle = NULL;

	/* Check in parameters */
	if ((NULL == rule) ||
		(NULL == rootcert_buf) ||
		(0 == rootcert_buf_length) ||
		(NULL == sin_buffer) ||
		(0 == sin_buffer_length) ||
		(NULL == sin_parser_handle)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto sin_verifier_exit;
	}

	res = sinparser_init(
		&sin_handle,
		sin_buffer,
		sin_buffer_length);
	if (FCSERR_OK != res) {
		FCS_LOG_ERR("Failed to init sin parser.\n");
		res = -FCSERR_EINFOR;
		goto sin_verifier_exit;
	}

	res = sinparser_get_header(sin_handle, &sin_static_header);
	if (FCSERR_OK != res) {
		FCS_LOG_ERR("Failed to get sin header.\n");
		res = -FCSERR_EINFOR;
		goto sin_verifier_exit;
	}

	if (sin_static_header->type_payload_hash != SIN_SHA256_RSA) {
		FCS_LOG_ERR("Failed to unsupported hash alg.\n");
		res = -FCSERR_EINFOR;
		goto sin_verifier_exit;
	}

	/* Calculate Digest of SIN Header */
	res = digest_sha256_init(&header_digest);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init header digest ctx.\n");
		goto sin_verifier_exit;
	}

	hash_segment_count = sinparser_get_header_hash_segments();
	for (i = 0; i < hash_segment_count; i++) {
		res = sinparser_get_header_hash_segment(
			sin_handle, i, &verify_data, &verify_data_length);
		if (FCSERR_OK != res) {
			FCS_LOG_ERR("Failed to get hash data.\n");
			res = -FCSERR_EINFOR;
			goto sin_verifier_exit;
		}

		res = digest_sha256_update(header_digest,
				verify_data, verify_data_length);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to update header digest.\n");
			goto sin_verifier_exit;
		}
	}

	res = digest_sha256_final(header_digest,
			&header_hash, &header_hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize header digest.\n");
		goto sin_verifier_exit;
	}

	res = sinparser_get_asahi_data(sin_handle, &asahi_signature);
	if (FCSERR_OK != res) {
		FCS_LOG_ERR("Failed to get asahi data.\n");
		res = -FCSERR_EINFOR;
		goto sin_verifier_exit;
	}

	res = asahi_verify(rule,
			rootcert_buf,
			rootcert_buf_length,
			asahi_signature->asahi_signature,
			asahi_signature->size_asahi_signature,
			header_hash,
			header_hash_length);
	if (FCSERR_OK != res) {
		FCS_LOG_ERR("Failed to verify asahi signature.\n");
		goto sin_verifier_exit;
	}

	*sin_parser_handle = sin_handle;
	sin_handle = NULL;

sin_verifier_exit:
	digest_sha256_deinit(header_digest);
	(void)sinparser_deinit(sin_handle);
	return res;
}

