/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "digest.h"
#include <stdlib.h>
#include <string.h>
#include "fcserr.h"
#include "fcslog.h"
#include <openssl/x509.h>
#include <openssl/evp.h>

/**
 * Type definitions and defines
 */
struct digest {
	uint8_t out_hash[32];
	EVP_MD_CTX *md_ctx;
};

static int digest_sha_init(struct digest **dgst, char *alg)
{
	int res = -FCSERR_EINVAL;

	/* Check in parameters */
	if (NULL == dgst) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto digest_sha_init_exit;
	}

	*dgst = (struct digest *)malloc(sizeof(struct digest));
	if (NULL == *dgst) {
		FCS_LOG_ERR("Out of memory\n");
		goto digest_sha_init_exit;
	}

	(*dgst)->md_ctx = EVP_MD_CTX_create();
	if (NULL == (*dgst)->md_ctx) {
		FCS_LOG_ERR("Failed to create digest ctx.\n");
		res = -FCSERR_ENOMEM;
		goto digest_sha_init_exit;
	}

	if (1 != EVP_DigestInit_ex(
			(*dgst)->md_ctx,
			EVP_get_digestbyname(alg), NULL)) {
		FCS_LOG_ERR("Failed to init digest ctx.\n");
		res = -FCSERR_EHCLC;
		goto digest_sha_init_exit;
	}

	res = FCSERR_OK;

digest_sha_init_exit:
	if (FCSERR_OK != res) {
		if (NULL != dgst)
			digest_sha256_deinit(*dgst);
	}
	return res;
}

static void digest_sha_deinit(struct digest *dgst)
{
	if (NULL != dgst) {
		(void)EVP_MD_CTX_cleanup(dgst->md_ctx);
		EVP_MD_CTX_destroy(dgst->md_ctx);
		free(dgst);
	}
}

static int digest_sha_update(
		struct digest *dgst,
		uint8_t *databuffer,
		uint32_t databuffer_size)
{
	int res = -FCSERR_EINVAL;

	/* Check in parameters */
	if (dgst == NULL) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto digest_sha_update_exit;
	}

	if (1 != EVP_DigestUpdate(
			dgst->md_ctx, databuffer, databuffer_size)) {
		FCS_LOG_ERR("Failed to update digest.\n");
		res = -FCSERR_EHCLC;
		goto digest_sha_update_exit;
	}

	res = FCSERR_OK;

digest_sha_update_exit:
	return res;
}

static int digest_sha_final(
		struct digest *dgst,
		uint8_t **hash,
		uint32_t *hash_size)
{
	int res = -FCSERR_EINVAL;
	uint32_t calc_hash_length = 0;

	/* Check in parameters */
	if ((NULL == dgst) ||
		(NULL == hash) ||
		(NULL == hash_size)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto digest_sha_final_exit;
	}

	if (1 != EVP_DigestFinal_ex(
			dgst->md_ctx, dgst->out_hash, &calc_hash_length)) {
		FCS_LOG_ERR("Failed to update digest.\n");
		res = -FCSERR_EHCLC;
		goto digest_sha_final_exit;
	}

	*hash = dgst->out_hash;
	*hash_size = calc_hash_length;

	res = FCSERR_OK;

digest_sha_final_exit:
	return res;
}

/**
 * Exported functions
 */
int digest_sha256_init(struct digest **dgst)
{
	return digest_sha_init(dgst, "SHA256");
}

void digest_sha256_deinit(struct digest *dgst)
{
	digest_sha_deinit(dgst);
}

int digest_sha256_update(
		struct digest *dgst,
		uint8_t *databuffer,
		uint32_t databuffer_size)
{
	return digest_sha_update(dgst, databuffer, databuffer_size);
}

int digest_sha256_final(
		struct digest *dgst,
		uint8_t **hash,
		uint32_t *hash_size)
{
	return digest_sha_final(dgst, hash, hash_size);
}

int digest_sha224_init(struct digest **dgst)
{
	return digest_sha_init(dgst, "SHA224");
}

void digest_sha224_deinit(struct digest *dgst)
{
	digest_sha_deinit(dgst);
}

int digest_sha224_update(
		struct digest *dgst,
		uint8_t *databuffer,
		uint32_t databuffer_size)
{
	return digest_sha_update(dgst, databuffer, databuffer_size);
}

int digest_sha224_final(
		struct digest *dgst,
		uint8_t **hash,
		uint32_t *hash_size)
{
	return digest_sha_final(dgst, hash, hash_size);
}

int digest_sha1_init(struct digest **dgst)
{
	return digest_sha_init(dgst, "SHA1");
}

void digest_sha1_deinit(struct digest *dgst)
{
	digest_sha_deinit(dgst);
}

int digest_sha1_update(
		struct digest *dgst,
		uint8_t *databuffer,
		uint32_t databuffer_size)
{
	return digest_sha_update(dgst, databuffer, databuffer_size);
}

int digest_sha1_final(
		struct digest *dgst,
		uint8_t **hash,
		uint32_t *hash_size)
{
	return digest_sha_final(dgst, hash, hash_size);
}

int digest_sha256_verify(
		uint8_t *databuffer,
		uint32_t databuffer_size,
		uint8_t *hash)
{
	int res = -FCSERR_EINVAL;
	struct digest *dgst = NULL;
	uint8_t *calc_hash = NULL;
	uint32_t calc_hash_length = 0;

	/* Check in parameters */
	if ((NULL == databuffer) ||
		(0 == databuffer_size) ||
		(NULL == hash)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto digest_sha256_verify_exit;
	}

	res = digest_sha256_init(&dgst);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init digest session\n");
		goto digest_sha256_verify_exit;
	}

	res = digest_sha256_update(
			dgst,
			databuffer,
			databuffer_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update digest session\n");
		goto digest_sha256_verify_exit;
	}

	res = digest_sha256_final(
			dgst,
			&calc_hash,
			&calc_hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize digest session\n");
		goto digest_sha256_verify_exit;
	}


	/* Compare to expected hash value */
	if (0 != memcmp(calc_hash, hash, calc_hash_length)) {
		FCS_LOG_ERR("Digest verify failed.\n");
		res = -FCSERR_EVS;
		goto digest_sha256_verify_exit;
	}

	res = FCSERR_OK;

digest_sha256_verify_exit:
	if (NULL != dgst)
		digest_sha256_deinit(dgst);
	return res;
}

int digest_sha1_verify(
		uint8_t *databuffer,
		uint32_t databuffer_size,
		uint8_t *hash)
{
	int res = -FCSERR_EINVAL;
	struct digest *dgst = NULL;
	uint8_t *calc_hash = NULL;
	uint32_t calc_hash_length = 0;

	/* Check in parameters */
	if ((NULL == databuffer) ||
		(0 == databuffer_size) ||
		(NULL == hash)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto digest_sha1_verify_exit;
	}

	res = digest_sha1_init(&dgst);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init digest session\n");
		goto digest_sha1_verify_exit;
	}

	res = digest_sha1_update(
			dgst,
			databuffer,
			databuffer_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update digest session\n");
		goto digest_sha1_verify_exit;
	}

	res = digest_sha1_final(
			dgst,
			&calc_hash,
			&calc_hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize digest session\n");
		goto digest_sha1_verify_exit;
	}


	/* Compare to expected hash value */
	if (0 != memcmp(calc_hash, hash, calc_hash_length)) {
		FCS_LOG_ERR("Digest verify failed.\n");
		res = -FCSERR_EVS;
		goto digest_sha1_verify_exit;
	}

	res = FCSERR_OK;

digest_sha1_verify_exit:
	if (NULL != dgst)
		digest_sha1_deinit(dgst);
	return res;
}

