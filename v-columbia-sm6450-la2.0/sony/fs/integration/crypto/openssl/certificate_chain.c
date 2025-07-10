/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "certificate_chain.h"
#include "rule_verifier_intern.h"
#include "rule_openssl.h"
#include <stdlib.h>
#include "fcserr.h"
#include "fcslog.h"
#include "openssl/x509.h"
#include "openssl/x509_vfy.h"

/**
 * Exported functions
 */
int certificatechain_verify(
		struct rule_verifier *rule,
		uint8_t  *certchain_buffer,
		size_t  certchain_buffer_length,
		uint8_t  *rootcert_buffer,
		size_t  rootcert_buffer_length)
{
	int res = -FCSERR_EINVAL;
	uint8_t *certbuffer_ptr;
	uint8_t *certbuffer_end;
	X509 *cert_ptr;
	X509 *leaf_cert_ptr;
	uint32_t length;

	STACK_OF(X509) * cert_stack;
	X509_STORE *root_store;
	X509_STORE_CTX *verify_ctx;

	leaf_cert_ptr = NULL;
	cert_stack = NULL;
	root_store = NULL;
	verify_ctx = NULL;

	/* Check in parameters */
	if ((NULL == certchain_buffer) ||
		(0 == certchain_buffer_length) ||
		(NULL == rootcert_buffer) ||
		(0 == rootcert_buffer_length)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto certificatechain_verify_exit;
	}

	cert_stack = sk_X509_new_null();
	if (NULL == cert_stack) {
		FCS_LOG_ERR("Create of certificate stack failed.\n");
		res = -FCSERR_ENOMEM;
		goto certificatechain_verify_exit;
	}

	certbuffer_ptr = certchain_buffer;
	certbuffer_end = certchain_buffer + certchain_buffer_length;
	while (certbuffer_ptr < certbuffer_end) {
		length = (uint32_t)(certbuffer_end - certbuffer_ptr);
		cert_ptr = d2i_X509(NULL,
			(const unsigned char **)&certbuffer_ptr, length);
		if (NULL == cert_ptr) {
			FCS_LOG_ERR("Parse of certificate failed.\n");
			res = -FCSERR_EINFOR;
			goto certificatechain_verify_exit;
		}
		if (NULL == leaf_cert_ptr)
				leaf_cert_ptr = cert_ptr;
		if (!sk_X509_push(cert_stack, cert_ptr)) {
			FCS_LOG_ERR(
				"Appending certificate to certificate stack failed.\n");
			res = -FCSERR_ENOMEM;
			X509_free(cert_ptr);
			goto certificatechain_verify_exit;
		}
	}

	if (NULL == leaf_cert_ptr) {
		FCS_LOG_ERR("No leaf certificate found.\n");
		res = -FCSERR_ENOTF;
		goto certificatechain_verify_exit;
	}

	/* Create and setup root store */
	res = rule_openssl_setup_root_store(&root_store,
		rootcert_buffer,
		rootcert_buffer_length,
		rule);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to setup root store: (%d)\n", res);
		goto certificatechain_verify_exit;
	}

	/* Create verify context */
	verify_ctx = X509_STORE_CTX_new();
	if (NULL == verify_ctx) {
		FCS_LOG_ERR("Failed to create verify context.\n");
		res = -FCSERR_ENOMEM;
		goto certificatechain_verify_exit;
	}

	/* Setup verify context */
	if (1 != X509_STORE_CTX_init(
			verify_ctx,
			root_store,
			leaf_cert_ptr,
			cert_stack)) {
		FCS_LOG_ERR("Failed to set ext_data OID list ptr.\n");
		res = -FCSERR_ENOMEM;
		goto certificatechain_verify_exit;
	}

	/* Do verify */
	if (1 != X509_verify_cert(verify_ctx)) {
		FCS_LOG_ERR("Verify failed.\n");
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
	sk_X509_pop_free(cert_stack, X509_free);
	if (NULL != root_store)
		X509_STORE_free(root_store);
	X509_STORE_CTX_free(verify_ctx);
	return res;
}

