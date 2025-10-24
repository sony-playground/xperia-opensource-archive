/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "signature.h"
#include <stdlib.h>
#include "fcserr.h"
#include "fcslog.h"
#include "openssl/x509.h"
#include <openssl/evp.h>
#include <openssl/rsa.h>

/**
 * Type definitions and defines
 */

static int signature_verify_intern(
		int padding,
		uint8_t *certchain_buffer,
		size_t   certchain_buffer_length,
		uint8_t *signature,
		size_t   signature_length,
		uint8_t *hash,
		size_t   hash_length)
{
	int res = -FCSERR_EINVAL;
	int vres;
	uint8_t *certbuffer_ptr;
	X509 *leaf_cert_ptr;
	EVP_PKEY *pubkey;
	EVP_PKEY_CTX *verify_ctx;

	leaf_cert_ptr = NULL;
	pubkey = NULL;
	verify_ctx = NULL;

	/* Check in parameters */
	if ((NULL == certchain_buffer) ||
		(0 == certchain_buffer_length) ||
		(NULL == signature) ||
		(0 == signature_length) ||
		(NULL == hash) ||
		(0 == hash_length)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto signature_verify_exit;
	}

	certbuffer_ptr = certchain_buffer;
	leaf_cert_ptr = d2i_X509(NULL,
			(const unsigned char **)&certbuffer_ptr,
			certchain_buffer_length);
	if (NULL == leaf_cert_ptr) {
		FCS_LOG_ERR("Parse of leaf certificate failed.\n");
		res = -FCSERR_EINFOR;
		goto signature_verify_exit;
	}

	pubkey = X509_get_pubkey(leaf_cert_ptr);
	if (NULL == pubkey) {
		FCS_LOG_ERR("Failed extract public key.\n");
		res = -FCSERR_EINFOR;
		goto signature_verify_exit;
	}
	verify_ctx = EVP_PKEY_CTX_new(pubkey, NULL);
	if (NULL == verify_ctx) {
		FCS_LOG_ERR("Failed create verify ctx.\n");
		res = -FCSERR_ENOMEM;
		goto signature_verify_exit;
	}

	if (1 != EVP_PKEY_verify_init(verify_ctx)) {
		FCS_LOG_ERR("Failed init verify ctx.\n");
		res = -FCSERR_EVS;
		goto signature_verify_exit;
	}

	if (1 != EVP_PKEY_CTX_set_rsa_padding(
			verify_ctx, padding)) {
		FCS_LOG_ERR("Failed to set padding.\n");
		res = -FCSERR_EVS;
		goto signature_verify_exit;
	}

	if (1 != EVP_PKEY_CTX_set_signature_md(
				verify_ctx, EVP_sha256())) {
		FCS_LOG_ERR("Failed to set sha256.\n");
		res = -FCSERR_EVS;
		goto signature_verify_exit;
	}

	vres = EVP_PKEY_verify(verify_ctx,
			signature, signature_length,
			hash, hash_length);
	if (1 != vres) {
		FCS_LOG_ERR("Signature verify failed (%d).\n", vres);
		res = -FCSERR_EVS;
		goto signature_verify_exit;
	}

	res = FCSERR_OK;

signature_verify_exit:
	EVP_PKEY_CTX_free(verify_ctx);
	EVP_PKEY_free(pubkey);
	X509_free(leaf_cert_ptr);
	return res;
}

/**
 * Exported functions
 */

int signature_verify(
		uint8_t *certchain_buffer,
		size_t   certchain_buffer_length,
		uint8_t *signature,
		size_t   signature_length,
		uint8_t *hash,
		size_t   hash_length)
{
	return signature_verify_intern(
			RSA_PKCS1_PADDING,
			certchain_buffer,
			certchain_buffer_length,
			signature,
			signature_length,
			hash,
			hash_length);
}

int signature_verify_rsassa_pss(
		uint8_t *certchain_buffer,
		size_t   certchain_buffer_length,
		uint8_t *signature,
		size_t   signature_length,
		uint8_t *hash,
		size_t   hash_length)
{
	return signature_verify_intern(
			RSA_PKCS1_PSS_PADDING,
			certchain_buffer,
			certchain_buffer_length,
			signature,
			signature_length,
			hash,
			hash_length);
}

