/*
 * Copyright 2017, 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */
#include <mbedtls/version.h>
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
#include <common.h> // MbedTLSLib/mbedtls/library/common.h
#endif

#include "certificate_chain.h"
#include "rule_verifier_intern.h"
#include "rule_mbedtls.h"
#include <stdlib.h>
#include "fcserr.h"
#include "fcslog.h"
#include <mbedtls/x509_crt.h>

/**
 * Exported functions
 */
#define ERROR_BUF_SIZE (512)

#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
int parse_crt_ext_cb(void *p_ctx,
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

int certificatechain_verify(
		struct rule_verifier *rule,
		uint8_t  *certchain_buffer,
		size_t  certchain_buffer_length,
		uint8_t  *rootcert_buffer,
		size_t  rootcert_buffer_length)
{
	int res = -FCSERR_EINVAL;
	int vres;
	uint8_t *certbuffer_ptr;
	uint8_t *certbuffer_end;
	mbedtls_x509_crt leaf_cert;
	mbedtls_x509_crt root_cert;
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
	mbedtls_x509_buf leaf_oid;
	mbedtls_x509_buf root_oid;
#endif /* (MBEDTLS_VERSION_NUMBER == 0x03000000) */
	size_t length;
	uint32_t flags = 0;
	char *error_text = NULL;
	mbedtls_x509_crt *p_cert;

	/* Initiate cert chain */
	mbedtls_x509_crt_init(&leaf_cert);
	mbedtls_x509_crt_init(&root_cert);

	/* Check in parameters */
	if ((certchain_buffer == NULL) ||
		(certchain_buffer_length == 0) ||
		(rootcert_buffer == NULL) ||
		(rootcert_buffer_length == 0)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto certificatechain_verify_exit;
	}

	/* Parse and add one cert (leaf) to chain */
	/* Currently no need for multiple certs in chain */
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
	vres = mbedtls_x509_crt_parse_der_with_ext_cb(
			&leaf_cert,
			certchain_buffer,
			certchain_buffer_length,
			1,
			parse_crt_ext_cb,
			&leaf_oid);
#else /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	/* Support MbedTLS 2.16.0 */
	vres = mbedtls_x509_crt_parse_der(
			&leaf_cert,
			certchain_buffer,
			certchain_buffer_length);
#endif /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	if (vres != 0) {
		FCS_LOG_ERR("Parse of certificate chain failed (%d).\n", vres);
		res = -FCSERR_ENOTF;
		goto certificatechain_verify_exit;
	}

	/* Create and setup roots */
	certbuffer_ptr = rootcert_buffer;
	certbuffer_end = rootcert_buffer + rootcert_buffer_length;
	while (certbuffer_ptr < certbuffer_end) {
		length = (uint32_t)(certbuffer_end - certbuffer_ptr);
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
		vres = mbedtls_x509_crt_parse_der_with_ext_cb(
			&root_cert,
			certbuffer_ptr,
			length,
			1,
			parse_crt_ext_cb,
			&root_oid);
#else /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
		/* Support MbedTLS 2.16.0 */
		vres = mbedtls_x509_crt_parse_der(
			&root_cert,
			certbuffer_ptr,
			length);
#endif /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
		if (vres != 0) {
			FCS_LOG_ERR(
				"Parse of root certificates failed (%d).\n",
				vres);
			res = -FCSERR_ENOTF;
			goto certificatechain_verify_exit;
		}
		vres = mbedtls_asn1_get_tag(
			&certbuffer_ptr,
			certbuffer_end,
			&length,
			MBEDTLS_ASN1_SEQUENCE | MBEDTLS_ASN1_CONSTRUCTED);
		if (vres != 0) {
			FCS_LOG_ERR(
				"Parse of root certificates failed (%d).\n",
				vres);
			res = -FCSERR_ENOTF;
			goto certificatechain_verify_exit;
		}
		certbuffer_ptr = certbuffer_ptr + length;
	}

	p_cert = &root_cert;
	while (p_cert != NULL) {
		/* MBedTLS requires a pure root cert to have
		 * basic constr CA True for Cert V3.
		 * This is not true for S1_Roots
		 * Temp workaround: If not set CA to true
		 */
		if (!p_cert->ca_istrue)
			p_cert->ca_istrue = 1;
		p_cert = p_cert->next;
	}

	/* Do verify */
	vres = mbedtls_x509_crt_verify(
			&leaf_cert,
			&root_cert,
			NULL,
			NULL,
			&flags,
			rule_mbedtls_verify_cb,
			rule);
	if (vres != 0) {
		FCS_LOG_ERR("Verify failed.\n");

		error_text = malloc(ERROR_BUF_SIZE);
		if (error_text == NULL) {
			FCS_LOG_ERR("malloc failed!\n");
			res = -FCSERR_ENOMEM;
			goto certificatechain_verify_exit;
		}

		mbedtls_x509_crt_verify_info(
			error_text,
			ERROR_BUF_SIZE,
			"Verify details: ",
			flags);
		FCS_LOG_ERR("%s\n", error_text);
		res = -FCSERR_EVCC;
		goto certificatechain_verify_exit;
	}

	res = rule_final(rule);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize rule check: (%d)\n", res);
		goto certificatechain_verify_exit;
	}

	res = FCSERR_OK;

certificatechain_verify_exit:
	mbedtls_x509_crt_free(&leaf_cert);
	mbedtls_x509_crt_free(&root_cert);
	free(error_text);
	return res;
}

