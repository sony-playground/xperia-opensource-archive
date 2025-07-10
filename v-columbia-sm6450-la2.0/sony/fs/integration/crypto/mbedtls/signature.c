/*
 * Copyright 2017, 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */
#include <mbedtls/version.h>
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
#include <common.h> // MbedTLSLib/mbedtls/library/common.h
#endif

#include "signature.h"
#include <stdlib.h>
#include "fcserr.h"
#include "fcslog.h"
#include <mbedtls/x509_crt.h>
#include <mbedtls/error.h>

/**
 * Type definitions and defines
 */
#define ERROR_BUF_SIZE (512)
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
int parse_certchain_ext_cb(void *p_ctx,
			   mbedtls_x509_crt const *crt,
			   mbedtls_x509_buf const *oid,
			   int critical,
			   const unsigned char *cp,
			   const unsigned char *end )
{
	( void ) p_ctx;
	( void ) crt;
	( void ) oid;
	( void ) critical;
	( void ) cp;
	( void ) end;
	return 0;
}
#endif /* (MBEDTLS_VERSION_NUMBER == 0x03000000) */

static int signature_verify_intern(
		mbedtls_pk_type_t sign_alg,
		const void *sign_alg_options,
		uint8_t *certchain_buffer,
		size_t   certchain_buffer_length,
		uint8_t *signature,
		size_t   signature_length,
		uint8_t *hash,
		size_t   hash_length)
{
	int res = -FCSERR_EINVAL;
	int vres;
	mbedtls_x509_crt leaf_cert;
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
	mbedtls_x509_buf leaf_oid;
#endif /* (MBEDTLS_VERSION_STRING == "3.0.0") */
	char *error_text = NULL;

	/* Initiate cert chain */
	mbedtls_x509_crt_init(&leaf_cert);

	/* Check in parameters */
	if ((certchain_buffer == NULL) ||
		(certchain_buffer_length == 0) ||
		(signature == NULL) ||
		(signature_length == 0) ||
		(hash == NULL) ||
		(hash_length == 0)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto signature_verify_exit;
	}

	/* Parse and add one cert (leaf) to chain */
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
	vres = mbedtls_x509_crt_parse_der_with_ext_cb(
			&leaf_cert,
			certchain_buffer,
			certchain_buffer_length,
			1,
			parse_certchain_ext_cb,
			&leaf_oid);
#else /* !(MBEDTLS_VERSION_STRING == "3.0.0") */
	/* Support MbedTLS 2.16.0 */
	vres = mbedtls_x509_crt_parse_der(
			&leaf_cert,
			certchain_buffer,
			certchain_buffer_length);
#endif /* !(MBEDTLS_VERSION_STRING == "3.0.0") */
	if (vres != 0) {
		FCS_LOG_ERR("Parse of leaf certificate failed (%d).\n", vres);
		res = -FCSERR_EINFOR;
		goto signature_verify_exit;
	}

	vres = mbedtls_pk_verify_ext(
			sign_alg, sign_alg_options,
			&(leaf_cert.pk),
			MBEDTLS_MD_SHA256,
			hash, hash_length,
			signature, signature_length);
	if (vres != 0) {
		FCS_LOG_ERR("Signature verify failed (%d).\n", vres);

		error_text = malloc(ERROR_BUF_SIZE);
		if (error_text == NULL) {
			FCS_LOG_ERR("Malloc failed!\n");
			res = -FCSERR_ENOMEM;
			goto signature_verify_exit;
		}

		mbedtls_strerror(vres, error_text, ERROR_BUF_SIZE);
		FCS_LOG_ERR("Error text: %s.\n", error_text);
		res = -FCSERR_EVS;
		goto signature_verify_exit;
	}

	res = FCSERR_OK;

signature_verify_exit:
	mbedtls_x509_crt_free(&leaf_cert);
	free(error_text);
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
			MBEDTLS_PK_RSA,
			NULL,
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
	mbedtls_pk_rsassa_pss_options options;

	options.mgf1_hash_id = MBEDTLS_MD_SHA256;
	options.expected_salt_len = MBEDTLS_RSA_SALT_LEN_ANY;
	return signature_verify_intern(
			MBEDTLS_PK_RSASSA_PSS,
			&options,
			certchain_buffer,
			certchain_buffer_length,
			signature,
			signature_length,
			hash,
			hash_length);
}

