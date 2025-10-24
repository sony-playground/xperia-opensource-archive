/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "asahi_verifier.h"
#include "asahi_parser.h"
#include "certificate_chain.h"
#include "signature.h"
#include "signature.h"
#include <stdlib.h>
#include "fcserr.h"
#include "fcslog.h"
#include "digest.h"

/**
 * Exported functions
 */
int asahi_verify(
		struct rule_verifier *rule,
		uint8_t *rootcert_buf,
		size_t rootcert_buf_length,
		uint8_t *asahi_buffer,
		size_t asahi_buffer_length,
		uint8_t *hash,
		size_t hash_length)
{
	int res = -FCSERR_EINVAL;
	void *asahi_handle;
	uint8_t *certificate_chain = NULL;
	size_t certificate_chain_length = 0;
	uint8_t algorithm;
	uint8_t *rsa_signature_ptr;
	size_t rsa_signature_size;
	size_t header_digest_len;
	struct digest *header_digest = NULL;
	struct digest *concat_digest = NULL;
	uint8_t *header_hash = NULL;
	uint32_t header_hash_length = 0;
	uint8_t *concat_hash = NULL;
	uint32_t concat_hash_length = 0;

	asahi_handle = NULL;

	/* Check in parameters */
	if ((NULL == rule) ||
		(NULL == rootcert_buf) ||
		(0 == rootcert_buf_length) ||
		(NULL == asahi_buffer) ||
		(0 == asahi_buffer_length) ||
		(NULL == hash)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto asahi_verify_exit;
	}

	res = asahiparser_init(
			&asahi_handle,
			asahi_buffer,
			asahi_buffer_length);
	if (FCSERR_OK != res) {
		FCS_LOG_ERR("Failed to init asahi parser.\n");
		res = -FCSERR_EINFOR;
		goto asahi_verify_exit;
	}

	res = asahiparser_get_certificate_chain(asahi_handle,
			&certificate_chain, &certificate_chain_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get certificate chain: (%d)\n", res);
		goto asahi_verify_exit;
	}

	res = certificatechain_verify(rule,
			certificate_chain,
			certificate_chain_length,
			rootcert_buf,
			rootcert_buf_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Certificate chain verification fail: (%d)\n", res);
		goto asahi_verify_exit;
	}

	res = asahiparser_get_signature_algorithm(
			asahi_handle,
			&algorithm);
	if (FCSERR_OK != res) {
		FCS_LOG_ERR("Failed to read algorithm.\n");
		res = -FCSERR_EINFOR;
		goto asahi_verify_exit;
	}

	if (algorithm != ASAHI_SHA256_RSA) {
		FCS_LOG_ERR("Unsupported algorithm.\n");
		res = -FCSERR_EINFOR;
		goto asahi_verify_exit;
	}

	res = asahiparser_get_rsa_signature(
			asahi_handle,
			&rsa_signature_ptr,
			&rsa_signature_size);
	if (FCSERR_OK != res) {
		FCS_LOG_ERR("Failed to read signature location.\n");
		res = -FCSERR_EINFOR;
		goto asahi_verify_exit;
	}

	header_digest_len = rsa_signature_ptr - asahi_buffer - 2;

	/* Calculate Digest of ASAHI Header */
	res = digest_sha256_init(&header_digest);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init header digest ctx.\n");
		goto asahi_verify_exit;
	}

	res = digest_sha256_update(header_digest,
			asahi_buffer, header_digest_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update header digest.\n");
		goto asahi_verify_exit;
	}

	res = digest_sha256_final(header_digest,
			&header_hash, &header_hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize header digest.\n");
		goto asahi_verify_exit;
	}

	/* Calculate Digest over ASAHI Header digest and input hash */
	res = digest_sha256_init(&concat_digest);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init concat digest ctx.\n");
		goto asahi_verify_exit;
	}

	res = digest_sha256_update(concat_digest,
			header_hash, header_hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update concat digest 1.\n");
		goto asahi_verify_exit;
	}

	res = digest_sha256_update(concat_digest, hash, hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update concat digest 2.\n");
		goto asahi_verify_exit;
	}

	res = digest_sha256_final(concat_digest,
			&concat_hash, &concat_hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize concat digest.\n");
		goto asahi_verify_exit;
	}

	/* Do the final signature verification */
	res = signature_verify(
			certificate_chain,
			certificate_chain_length,
			rsa_signature_ptr,
			rsa_signature_size,
			concat_hash,
			concat_hash_length);

asahi_verify_exit:
	digest_sha256_deinit(concat_digest);
	digest_sha256_deinit(header_digest);
	(void)asahiparser_deinit(asahi_handle);
	free(certificate_chain);
	return res;
}

