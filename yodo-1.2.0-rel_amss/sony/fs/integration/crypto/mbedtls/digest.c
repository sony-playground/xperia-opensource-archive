/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "digest.h"
#include <stdlib.h>
#include <string.h>
#include "fcserr.h"
#include "fcslog.h"
#include <mbedtls/md.h>

/**
 * Type definitions and defines
 */
struct digest {
	uint8_t out_hash[32];
	uint32_t out_hash_size;
	mbedtls_md_context_t md_ctx;
};

static void digest_sha_deinit(struct digest *dgst);

static int digest_sha_init(struct digest **dgst, mbedtls_md_type_t alg)
{
	int res = -FCSERR_EINVAL;
	const mbedtls_md_info_t *pInfo = NULL;

	/* Check in parameters */
	if (dgst == NULL) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto digest_sha_init_exit;
	}

	*dgst = (struct digest *)malloc(sizeof(struct digest));
	if (*dgst == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		goto digest_sha_init_exit;
	}

	mbedtls_md_init(&((*dgst)->md_ctx));

	pInfo = mbedtls_md_info_from_type(alg);
	if (pInfo == NULL) {
		FCS_LOG_ERR("Invalid digest algorithm.\n");
		res = -FCSERR_EHCLC;
		goto digest_sha_init_exit;
	}

	(*dgst)->out_hash_size = mbedtls_md_get_size(pInfo);

	if (mbedtls_md_setup(
			&((*dgst)->md_ctx),
			pInfo,
			0) != 0) {
		FCS_LOG_ERR("Failed to setup digest ctx.\n");
		res = -FCSERR_EHCLC;
		goto digest_sha_init_exit;
	}

	if (mbedtls_md_starts(&((*dgst)->md_ctx)) != 0) {
		FCS_LOG_ERR("Failed to start digest ctx.\n");
		res = -FCSERR_EHCLC;
		goto digest_sha_init_exit;
	}

	res = FCSERR_OK;

digest_sha_init_exit:
	if (res != FCSERR_OK) {
		if (dgst != NULL)
			digest_sha_deinit(*dgst);
	}
	return res;
}

static void digest_sha_deinit(struct digest *dgst)
{
	if (dgst != NULL) {
		mbedtls_md_free(&(dgst->md_ctx));
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

	if (mbedtls_md_update(
			&(dgst->md_ctx), databuffer, databuffer_size) != 0) {
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

	/* Check in parameters */
	if ((dgst == NULL) ||
		(hash == NULL) ||
		(hash_size == NULL)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto digest_sha_final_exit;
	}

	if (mbedtls_md_finish(
			&(dgst->md_ctx), dgst->out_hash) != 0) {
		FCS_LOG_ERR("Failed to finalize digest.\n");
		res = -FCSERR_EHCLC;
		goto digest_sha_final_exit;
	}

	*hash = dgst->out_hash;
	*hash_size = dgst->out_hash_size;

	res = FCSERR_OK;

digest_sha_final_exit:
	return res;
}

/**
 * Exported functions
 */
int digest_sha256_init(struct digest **dgst)
{
	return digest_sha_init(dgst, MBEDTLS_MD_SHA256);
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
	return digest_sha_init(dgst, MBEDTLS_MD_SHA224);
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
	return digest_sha_init(dgst, MBEDTLS_MD_SHA1);
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
	if ((databuffer == NULL) ||
		(databuffer_size == 0) ||
		(hash == NULL)) {
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
	if (memcmp(calc_hash, hash, calc_hash_length) != 0) {
		FCS_LOG_ERR("Digest verify failed.\n");
		res = -FCSERR_EVS;
		goto digest_sha256_verify_exit;
	}

	res = FCSERR_OK;

digest_sha256_verify_exit:
	if (dgst != NULL)
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
	if ((databuffer == NULL) ||
		(databuffer_size == 0) ||
		(hash == NULL)) {
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
	if (memcmp(calc_hash, hash, calc_hash_length) != 0) {
		FCS_LOG_ERR("Digest verify failed.\n");
		res = -FCSERR_EVS;
		goto digest_sha1_verify_exit;
	}

	res = FCSERR_OK;

digest_sha1_verify_exit:
	if (dgst != NULL)
		digest_sha1_deinit(dgst);
	return res;
}

int digest_sha1_calc(uint8_t *buf, uint32_t sz, uint8_t *hash, uint32_t hash_sz)
{
	int res;
	struct digest *dgst = NULL;
	uint32_t digest_len = DIGEST_SHA1_HASH_SIZE;
	uint8_t *digest = NULL;

	if (buf == NULL || sz == 0 || hash == NULL ||
	    hash_sz < DIGEST_SHA1_HASH_SIZE) {
		FCS_LOG_ERR("Invalid parameter.\n");
		return -FCSERR_EINVAL;
	}

	res = digest_sha1_init(&dgst);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init digest.\n");
		goto exit;
	}
	res = digest_sha1_update(dgst, buf, sz);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update digest.\n");
		goto exit;
	}

	res = digest_sha1_final(dgst, &digest, &digest_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize digest.\n");
		goto exit;
	} else if (digest_len != DIGEST_SHA1_HASH_SIZE) {
		FCS_LOG_ERR("Failed to digest.\n");
		res = -FCSERR_EHASH;
		goto exit;
	}

	/* copy sha1 hash (20 bytes) to output */
	memcpy(hash, digest, DIGEST_SHA1_HASH_SIZE);

exit:
	digest_sha1_deinit(dgst);
	return res;
}
