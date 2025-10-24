/*
 * Copyright 2018, 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */
#include <mbedtls/version.h>
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
#include <common.h> // MbedTLSLib/mbedtls/library/common.h
#endif

#include <stdint.h>
#include <string.h>
#include <mbedtls/x509_crt.h>
#include "fcslog.h"
#include "fcserr.h"
#include "digest.h"
#include "cryp_util.h"

#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
int parse_cert_ext_cb(void *p_ctx,
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

int cryp_get_pk_hash(
	const uint8_t *cert_data, uint32_t cert_len,
	uint8_t *hash, uint32_t hash_len)
{
	int res = FCSERR_OK;
	mbedtls_x509_crt cert;
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
	mbedtls_x509_buf oid;
#endif /* (MBEDTLS_VERSION_NUMBER == 0x03000000) */
	int written;
	uint8_t buf[CRYP_MAX_PK_LEN];

	if (cert_data == NULL || cert_len == 0) {
		FCS_LOG_ERR("Invalid input\n", res);
		return -FCSERR_EINVAL;
	}

	/* Initiate cert */
	mbedtls_x509_crt_init(&cert);

	/* Parse and add one cert (leaf) to chain */
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
	res = mbedtls_x509_crt_parse_der_with_ext_cb(
			&cert,
			cert_data,
			cert_len,
			1,
			parse_cert_ext_cb,
			&oid);
#else /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	/* Support MbedTLS 2.16.0 */
	res = mbedtls_x509_crt_parse_der(&cert, cert_data, cert_len);
#endif /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	if (res != 0) {
		FCS_LOG_ERR("Parse of certificate failed (%d).\n", res);
		return -FCSERR_ESTATE;
	}

	if (mbedtls_pk_can_do(&(cert.pk), MBEDTLS_PK_RSA) == 0) {
		FCS_LOG_ERR("Certificate contains unsupported pk.\n");
		res = -FCSERR_PERM;
		goto exit;
	}

	/* Step 1: Generate rsa key in PEM format and calc hash */
	res = mbedtls_pk_write_pubkey_pem(&(cert.pk), buf, CRYP_MAX_PK_LEN);
	if (res != 0) {
		FCS_LOG_ERR("PEM format generation of KS key failed.\n");
		res = -FCSERR_ESTATE;
		goto exit;
	}
	written = strlen((const char *)(buf));

	res = digest_sha1_calc(buf, written, hash, hash_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update digest.\n");
		goto exit;
	}

exit:
	mbedtls_x509_crt_free(&cert);
	return res;
}
