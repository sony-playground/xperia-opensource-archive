/*
 * Copyright 2018, 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */
#include <mbedtls/version.h>
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
#include <common.h> // MbedTLSLib/mbedtls/library/common.h
#endif

#include "authenticate_common.h"
#include "fcslog.h"
#include "fcserr.h"
#include "digest.h"
#include <mbedtls/x509_crt.h>
#include "mbedtls/rsa.h"
#include <stdlib.h>
#include <string.h>
#include "cryp_util.h"

#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
int parse_ksblob_ext_cb(void *p_ctx,
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
int rsa_encrypt_nopad(const uint8_t *in_buffer_p,
			     size_t in_buffer_size,
			     uint8_t *out_buffer_p,
			     size_t out_buffer_size,
			     const asn_rsa_public_key_t public_key)
{
	int res = FCSERR_OK;
	int mbedtls_res = 0;
	struct item_array item_m, item_e;
	mbedtls_rsa_context rsa;

	if (in_buffer_size != out_buffer_size)
		return -FCSERR_EINVAL;
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
	mbedtls_rsa_init(&rsa);
#else /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	/* Support MbedTLS 2.16.0 */
	mbedtls_rsa_init(&rsa, MBEDTLS_RSA_PKCS_V15, 0);
#endif /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	res = extract_public_key_parts(public_key, &item_m,
				       ITEM_ARRAY_MODULUS);
	if (res != FCSERR_OK)
		goto error;

	res = extract_public_key_parts(public_key, &item_e,
				       ITEM_ARRAY_EXPONENT);
	if (res != FCSERR_OK)
		goto error;

	mbedtls_res = mbedtls_mpi_read_binary(
			&rsa.N, item_m.data, item_m.length);
	if (mbedtls_res != 0)
		goto error;

	mbedtls_res = mbedtls_mpi_read_binary(
			&rsa.E, item_e.data, item_e.length);
	if (mbedtls_res != 0)
		goto error;

	rsa.len = (mbedtls_mpi_bitlen(&rsa.N) + 7) >> 3;

	if (rsa.len != in_buffer_size) {
		res = -FCSERR_EINVAL;
		goto error;
	}

	mbedtls_res = mbedtls_rsa_public(
			&rsa,
			in_buffer_p,
			out_buffer_p);

error:
	if ((res == FCSERR_OK) && (mbedtls_res != 0)) {
		if (mbedtls_res == MBEDTLS_ERR_MPI_ALLOC_FAILED)
			res = -FCSERR_ENOMEM;
		else
			res = -FCSERR_ENIMP;
	}
	mbedtls_rsa_free(&rsa);
	return res;
}

int extract_pubkey(struct ksstore_blob *ksblob,
		struct sake_pubkey_info *root)
{
	int res = FCSERR_OK;
	int mbedtls_res = 0;
	mbedtls_x509_crt cert;
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
	mbedtls_x509_buf oid;
#endif /* (MBEDTLS_VERSION_NUMBER == 0x03000000) */
	uint8_t digest[DIGEST_SHA1_HASH_SIZE];
	mbedtls_rsa_context *rsa = NULL;
	struct sake_pubkey_info temp_root;
	int written;
	size_t mod_len;
	size_t exp_len;
	size_t total_len;
	uint8_t *buf = NULL;

	if (ksblob == NULL || root == NULL)
		return -FCSERR_EINVAL;

	memset(&temp_root, 0, sizeof(temp_root));

	/* Initiate cert */
	mbedtls_x509_crt_init(&cert);

	/* Parse and add one cert (leaf) to chain */
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
	mbedtls_res = mbedtls_x509_crt_parse_der_with_ext_cb(
			&cert,
			ksblob->blob,
			ksblob->size,
			1,
			parse_ksblob_ext_cb,
			&oid);
#else /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	/* Support MbedTLS 2.16.0 */
	mbedtls_res = mbedtls_x509_crt_parse_der(
			&cert,
			ksblob->blob,
			ksblob->size);
#endif /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	if (mbedtls_res != 0) {
		FCS_LOG_ERR("Parse of certificate failed (%d).\n", mbedtls_res);
		return -FCSERR_ESTATE;
	}

	if (mbedtls_pk_can_do(&(cert.pk), MBEDTLS_PK_RSA) == 0) {
		FCS_LOG_ERR("Certificate contains unsupported pk.\n");
		res = -FCSERR_PERM;
		goto error;
	}

	buf = malloc(CRYP_MAX_PK_LEN);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory.\n");
		res = -FCSERR_ENOMEM;
		goto error;
	}

	/* Step 1: Generate rsa key in PEM format and calc hash */
	mbedtls_res = mbedtls_pk_write_pubkey_pem(&(cert.pk), buf,
						  CRYP_MAX_PK_LEN);
	if (mbedtls_res != 0) {
		FCS_LOG_ERR("PEM format generation of KS key failed.\n");
		res = -FCSERR_ESTATE;
		goto error;
	}
	written = strlen((const char *)buf);

	res = digest_sha1_calc(buf, written, digest, sizeof(digest));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update digest.\n");
		goto error;
	}

	/* Step 2: Store hash in expected format */
	temp_root.pub_hash[0] = MBEDTLS_ASN1_INTEGER;
	 /* Size of pub hash field - type field and length field */
	temp_root.pub_hash[1] = sizeof(temp_root.pub_hash) - 2;
	memcpy(&(temp_root.pub_hash[2]), digest, sizeof(temp_root.pub_hash)-2);

	/* Step 3: Store rsa key in expected format */
	written = 0;
	rsa = mbedtls_pk_rsa(cert.pk);
	mod_len = mbedtls_mpi_size(&rsa->N);

	/* Multiplication by 8 is bits per byte */
	if (mbedtls_mpi_bitlen(&rsa->N) == (mod_len * 8))
		mod_len++;

	exp_len = mbedtls_mpi_size(&rsa->E);

	/* Multiplication by 8 is bits per byte */
	if (mbedtls_mpi_bitlen(&rsa->E) == (exp_len * 8))
		exp_len++;
	total_len = 4 + mod_len + 2 + exp_len;
	if (sizeof(temp_root.rsa_pub_key) < (4 + total_len)) {
		FCS_LOG_ERR("Unsupported size of KS key.\n");
		res = -FCSERR_ESTATE;
		goto error;
	}
	temp_root.rsa_pub_key[written++] = 0x30;
	temp_root.rsa_pub_key[written++] = 0x82;
	temp_root.rsa_pub_key[written++] = total_len >> 8;
	temp_root.rsa_pub_key[written++] = total_len & 0xFF;
	temp_root.rsa_pub_key[written++] = MBEDTLS_ASN1_INTEGER;
	temp_root.rsa_pub_key[written++] = 0x82;
	temp_root.rsa_pub_key[written++] = mod_len >> 8;
	temp_root.rsa_pub_key[written++] = mod_len & 0xFF;
	mbedtls_res = mbedtls_mpi_write_binary(
			&rsa->N,
			&temp_root.rsa_pub_key[written],
			mod_len);
	if (mbedtls_res != 0) {
		FCS_LOG_ERR("Failed to write KS key.\n");
		res = -FCSERR_ESTATE;
		goto error;
	}
	written += mod_len;
	temp_root.rsa_pub_key[written++] = MBEDTLS_ASN1_INTEGER;
	temp_root.rsa_pub_key[written++] = exp_len & 0xFF;
	mbedtls_res = mbedtls_mpi_write_binary(
			&rsa->E,
			&temp_root.rsa_pub_key[written],
			exp_len);
	if (mbedtls_res != 0) {
		FCS_LOG_ERR("Failed to write KS key.\n");
		res = -FCSERR_ESTATE;
		goto error;
	}
	written += exp_len;

	/* Step 4: Store crl in expected format */
	memcpy(temp_root.crl, default_crl, sizeof(temp_root.crl));

	/* Step 5: Everything is OK, copy to out buffer */
	memcpy(root, &temp_root, sizeof(temp_root));

error:
	free(buf);
	mbedtls_x509_crt_free(&cert);
	return res;

}
