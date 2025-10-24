/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "authenticate_common.h"
#include "fcslog.h"
#include "fcserr.h"
#include "digest.h"
#include <openssl/x509.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/pem.h>
#include <stdlib.h>
#include <string.h>

int rsa_encrypt_nopad(const uint8_t *in_buffer_p,
			     size_t in_buffer_size,
			     uint8_t *out_buffer_p,
			     size_t out_buffer_size,
			     const asn_rsa_public_key_t public_key)
{
	int res = FCSERR_OK;
	struct item_array item_m, item_e;

	if (in_buffer_size != out_buffer_size)
		return -FCSERR_EINVAL;

	RSA *pubkey = RSA_new();
	BIGNUM *modul = BN_new();
	BIGNUM *expon = BN_new();

	res = extract_public_key_parts(public_key, &item_m,
				       ITEM_ARRAY_MODULUS);
	if (res != FCSERR_OK)
		goto error;

	res = extract_public_key_parts(public_key, &item_e,
				       ITEM_ARRAY_EXPONENT);
	if (res != FCSERR_OK)
		goto error;

	BN_bin2bn(item_m.data, item_m.length, modul);
	BN_bin2bn(item_e.data, item_e.length, expon);

	pubkey->n = modul;
	pubkey->e = expon;
	modul = NULL;
	expon = NULL;

	res = RSA_public_encrypt(in_buffer_size, in_buffer_p, out_buffer_p,
				 pubkey, RSA_NO_PADDING);

	if (res < 0)
		res = -FCSERR_ENIMP;
	else
		res = FCSERR_OK;

error:
	RSA_free(pubkey);
	BN_free(modul);
	BN_free(expon);
	return res;
}

int extract_pubkey(struct ksstore_blob *ksblob,
		struct sake_pubkey_info *root)
{
	int res = FCSERR_OK;
	X509 *cert = NULL;
	EVP_PKEY *pubkey = NULL;
	EVP_MD_CTX *mdctx = NULL;
	BUF_MEM *bufmem = NULL;
	BIO *mem = NULL;
	RSA *rsa = NULL;
	uint32_t digest_len;
	uint8_t *digest = NULL;
	struct sake_pubkey_info temp_root;
	struct digest *dgst = NULL;
	int written;
	size_t mod_len;
	size_t exp_len;
	size_t total_len;
	int mod_pad;
	int exp_pad;

	if (ksblob == NULL || root == NULL)
		return -FCSERR_EINVAL;

	memset(&temp_root, 0, sizeof(temp_root));

	cert = d2i_X509(NULL, (const unsigned char **)&(ksblob->blob),
			ksblob->size);
	if (!cert) {
		FCS_LOG_ERR("d2i_X509 failed\n");
		return -FCSERR_ESTATE;
	}

	pubkey = X509_get_pubkey(cert);
	if (pubkey == NULL) {
		FCS_LOG_ERR("X509_get_pubkey failed\n");
		res = -FCSERR_ESTATE;
		goto error;
	}

	/* Step 1: Generate rsa key in PEM format and calc hash */
	mem = BIO_new(BIO_s_mem());
	if (mem == NULL) {
		res = -FCSERR_ENOMEM;
		goto error;
	}

	if (!PEM_write_bio_PUBKEY(mem, pubkey)) {
		FCS_LOG_ERR("PEM_write_bio_PUBKEY failed\n");
		res = -FCSERR_ESTATE;
		goto error;
	}

	BIO_get_mem_ptr(mem, &bufmem);

	res = digest_sha1_init(&dgst);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init digest.\n");
		goto error;
	}
	res = digest_sha1_update(dgst,
			(uint8_t *)(bufmem->data),
			bufmem->length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update digest.\n");
		goto error;
	}

	res = digest_sha1_final(dgst, &digest, &digest_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize digest.\n");
		goto error;
	}

	/* Step 2: Store hash in expected format */
	temp_root.pub_hash[0] = 0x02;
	temp_root.pub_hash[1] = sizeof(temp_root.pub_hash) - 2;
	memcpy(&(temp_root.pub_hash[2]), digest, sizeof(temp_root.pub_hash)-2);

	/* Step 3: Store rsa key in expected format */
	written = 0;
	rsa = EVP_PKEY_get1_RSA(pubkey);
	if (rsa == NULL) {
		FCS_LOG_ERR("EVP_PKEY_get1_RSA failed\n");
		res = -FCSERR_ESTATE;
		goto error;
	}

	mod_len = BN_num_bytes(rsa->n);
	exp_len = BN_num_bytes(rsa->e);
	if (BN_is_bit_set(rsa->n, (mod_len << 3) - 1))
		mod_pad = 1;
	else
		mod_pad = 0;
	if (BN_is_bit_set(rsa->e, (exp_len << 3) - 1))
		exp_pad = 1;
	else
		exp_pad = 0;
	mod_len += mod_pad;
	exp_len += exp_pad;
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
	temp_root.rsa_pub_key[written++] = 0x30;
	temp_root.rsa_pub_key[written++] = 0x82;
	temp_root.rsa_pub_key[written++] = mod_len >> 8;
	temp_root.rsa_pub_key[written++] = mod_len & 0xFF;
	temp_root.rsa_pub_key[written] = 0x00;
	BN_bn2bin(rsa->n, &temp_root.rsa_pub_key[written + mod_pad]);
	written += mod_len;
	temp_root.rsa_pub_key[written++] = 0x02;
	temp_root.rsa_pub_key[written++] = exp_len & 0xFF;
	temp_root.rsa_pub_key[written] = 0x00;
	BN_bn2bin(rsa->e, &temp_root.rsa_pub_key[written + exp_pad]);
	written += exp_len;

	/* Step 4: Store crl in expected format */
	memcpy(temp_root.crl, default_crl, sizeof(temp_root.crl));

	/* Step 5: Everything is OK, copy to out buffer */
	memcpy(root, &temp_root, sizeof(temp_root));

error:
	digest_sha1_deinit(dgst);
	if (mem != NULL)
		BIO_free(mem);
	if (mdctx != NULL)
		EVP_MD_CTX_destroy(mdctx);
	if (cert != NULL)
		X509_free(cert);
	if (pubkey != NULL)
		EVP_PKEY_free(pubkey);
	return res;

}

