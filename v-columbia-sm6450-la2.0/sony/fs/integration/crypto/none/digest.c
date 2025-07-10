/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "digest.h"
#include "fcserr.h"
#include "fcslog.h"
#include <string.h>

#define ROR(x, k) ((x>>k)|(x<<(32-k)))

static const unsigned int cubeRoot[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void Memset(void *dst, int c, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		((unsigned char *)dst)[a] = c & 0xff;
}

static void Memcpy(void *dst, const void *src, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		((char *)dst)[a] = ((char *)src)[a];
}

static void ExpandIt(unsigned int *w)
{
	int i;
	unsigned int s0, s1;

	for (i = 16; i < 64; i++) {
		s0 = ROR(w[i-15], 7) ^ ROR(w[i-15], 18) ^ (w[i-15]>>3);
		s1 = ROR(w[i-2], 17) ^ ROR(w[i-2], 19) ^ (w[i-2]>>10);
		w[i] = w[i-16] + s0 + w[i-7] + s1;
	}
}

static void MangleIt(const unsigned int *w, unsigned int *h)
{
	int i, k;
	unsigned int s0, s1, maj, t2, t1, ch;
	unsigned int a[8];

	Memcpy(a, h, sizeof(a));

	// main loop:
	for (i = 0; i < 64; i++) {
		s0 = ROR(a[0], 2) ^ ROR(a[0], 13) ^ ROR(a[0], 22);
		maj = (a[0] & a[1]) ^ (a[0] & a[2]) ^ (a[1] & a[2]);
		t2 = s0 + maj;
		s1 = ROR(a[4], 6) ^ ROR(a[4], 11) ^ ROR(a[4], 25);
		ch = (a[4] & a[5]) ^ ((~a[4]) & a[6]);
		t1 = a[7] + s1 + ch + cubeRoot[i] + w[i];

		a[7] = a[6];
		a[6] = a[5];
		a[5] = a[4];
		a[4] = a[3] + t1;
		a[3] = a[2];
		a[2] = a[1];
		a[1] = a[0];
		a[0] = t1 + t2;
	}

	for (k = 0; k < 8; k++)
		h[k] = h[k] + a[k];
}

static void FixEndian(unsigned int *w)
{
	unsigned char *wc;
	int i;

	wc = (unsigned char *)w;
	for (i = 0; i < 16; i++)
		w[i] = (wc[i*4]<<24) | (wc[i*4+1]<<16) | (wc[i*4+2]<<8) |
			(wc[i*4+3]);
}

static int digest_CalculateSha256_Init(
		unsigned int *totalLen,
		unsigned int *ocLen,
		unsigned int *h)
{
	unsigned int h_init[8] = {
			0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
			0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

	if (!totalLen || !ocLen || !h)
		return -1;

	*totalLen = 0;
	Memcpy(h, h_init, sizeof(h_init));
	*ocLen = 0;
	return 0;
}

static int digest_CalculateSha256_Block(
		const unsigned char *src,
		unsigned int srcLen,
		unsigned int *totalLen,
		unsigned char *oc,
		unsigned int *ocLen,
		unsigned int *h)
{
	unsigned int w[64];
	unsigned char *wc;
	unsigned int offs;

	if (!src || !totalLen || !oc || !ocLen || !h)
		return -1;

	wc = (unsigned char *)w;

	*totalLen += srcLen;
	/* Use overflow buffer */
	if (*ocLen + srcLen < 64) {
		Memcpy(oc + *ocLen, src, srcLen);
		*ocLen += srcLen;
		return 0;
	}

	Memcpy(wc, oc, *ocLen);
	Memcpy(wc + *ocLen, src, 64 - *ocLen);
	offs = 64 - *ocLen;
	*ocLen = 0;
	FixEndian(w);
	ExpandIt(w);
	MangleIt(w, h);

	/* Process message in 512-bit chunks */
	for (; (offs + 64) < srcLen; offs += 64) {
		Memcpy(wc, src + offs, 64);
		FixEndian(w);
		ExpandIt(w);
		MangleIt(w, h);
	}

	/* Save unprocessed message in overflow buffer */
	if ((srcLen - offs) > 0) {
		Memcpy(oc, src + offs, srcLen - offs);
		*ocLen = srcLen - offs;
	}
	return 0;
}

static int digest_CalculateSha256_final(
		unsigned int *totalLen,
		unsigned char *oc,
		unsigned int *ocLen,
		unsigned int *h,
		unsigned char *res)
{
	unsigned int w[64];
	unsigned int len;
	int stopBitDone = 0, footerDone = 0, k;
	unsigned char *wc;

	if (!oc || !ocLen || !h || !res)
		return -1;

	wc = (unsigned char *)w;

	/* Use overflow buffer */
	Memcpy(wc, oc, *ocLen);
	Memset(wc + *ocLen, 0, sizeof(w) - *ocLen);
	len = *ocLen;
	if (len < 64) {
		wc[len] = 0x80;
		len++;
		stopBitDone = 1;
		if (len <= 56) {
			/*
			 * Should be 8 bytes of length info, but
			 * we don't support that much data
			 */
			wc[60] = ((*totalLen * 8) >> 24) & 0xff;
			wc[61] = ((*totalLen * 8) >> 16) & 0xff;
			wc[62] = ((*totalLen * 8) >> 8) & 0xff;
			wc[63] = (*totalLen * 8) & 0xff;
			footerDone = 1;
		}
	}
	FixEndian(w);
	ExpandIt(w);
	MangleIt(w, h);

	if (footerDone == 0) {
		Memset(w, 0, sizeof(w) - 4);
		if (stopBitDone == 0)
			wc[0] = 0x80;
		wc[60] = ((*totalLen*8) >> 24) & 0xff;
		wc[61] = ((*totalLen*8) >> 16) & 0xff;
		wc[62] = ((*totalLen*8) >> 8) & 0xff;
		wc[63] = (*totalLen*8) & 0xff;
		FixEndian(w);
		ExpandIt(w);
		MangleIt(w, h);
	}

	for (k = 0; k < 8; k++) {
		res[k*4] = (h[k]>>24) & 0xff;
		res[k*4+1] = (h[k]>>16) & 0xff;
		res[k*4+2] = (h[k]>>8) & 0xff;
		res[k*4+3] = (h[k]) & 0xff;
	}
	*totalLen = 0;
	*ocLen = 0;
	return 0;
}

struct digest {
	/* Digest length */
	unsigned int total_len;
	/* Calculation buffer */
	unsigned int h[8];
	/* block overflow buffer */
	unsigned int o[64];
	unsigned int o_len;
	uint8_t hash[32];
};

/**
 * Exported functions
 */
int digest_sha256_init(struct digest **dgst)
{
	if (dgst == NULL)
		return -FCSERR_EINVAL;
	*dgst = malloc(sizeof(struct digest));
	if (*dgst == NULL)
		return -FCSERR_ENOMEM;
	if (digest_CalculateSha256_Init(
			&((*dgst)->total_len),
			&((*dgst)->o_len),
			(*dgst)->h))
		return -FCSERR_EHCLC;

	return FCSERR_OK;
}

void digest_sha256_deinit(struct digest *dgst)
{
	free(dgst);
}

int digest_sha256_update(
		struct digest *dgst,
		uint8_t *databuffer,
		uint32_t databuffer_size)
{
	if (dgst == NULL ||
			databuffer == NULL ||
			databuffer_size == 0)
		return -FCSERR_EINVAL;

	if (digest_CalculateSha256_Block(databuffer,
				databuffer_size,
				&(dgst->total_len),
				(unsigned char *)(dgst->o),
				&(dgst->o_len),
				dgst->h))
		return -FCSERR_EHCLC;

	return FCSERR_OK;
}

int digest_sha256_final(
		struct digest *dgst,
		uint8_t **hash,
		uint32_t *hash_size)
{
	if (dgst == NULL ||
			hash == NULL ||
			hash_size == NULL)
		return -FCSERR_EINVAL;

	if (digest_CalculateSha256_final(
			&(dgst->total_len),
			(unsigned char *)(dgst->o),
			&(dgst->o_len),
			dgst->h,
			dgst->hash))
		return -FCSERR_EHCLC;

	*hash = dgst->hash;
	*hash_size = sizeof(dgst->hash);
	return FCSERR_OK;
}

int digest_sha224_init(struct digest **dgst)
{
	(void)dgst;

	return -FCSERR_ENIMP;
}

void digest_sha224_deinit(struct digest *dgst)
{
	(void)dgst;
}

int digest_sha224_update(
		struct digest *dgst,
		uint8_t *databuffer,
		uint32_t databuffer_size)
{
	(void)dgst;
	(void)databuffer;
	(void)databuffer_size;

	return -FCSERR_ENIMP;
}

int digest_sha224_final(
		struct digest *dgst,
		uint8_t **hash,
		uint32_t *hash_size)
{
	(void)dgst;
	(void)hash;
	(void)hash_size;

	return -FCSERR_ENIMP;
}

int digest_sha1_init(struct digest **dgst)
{
	(void)dgst;

	return -FCSERR_ENIMP;
}

void digest_sha1_deinit(struct digest *dgst)
{
	(void)dgst;
}

int digest_sha1_update(
		struct digest *dgst,
		uint8_t *databuffer,
		uint32_t databuffer_size)
{
	(void)dgst;
	(void)databuffer;
	(void)databuffer_size;

	return -FCSERR_ENIMP;
}

int digest_sha1_final(
		struct digest *dgst,
		uint8_t **hash,
		uint32_t *hash_size)
{
	(void)dgst;
	(void)hash;
	(void)hash_size;

	return -FCSERR_ENIMP;
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
	(void)databuffer;
	(void)databuffer_size;
	(void)hash;

	return -FCSERR_ENIMP;
}

int digest_sha1_calc(uint8_t *buf, uint32_t sz, uint8_t *hash, uint32_t hash_sz)
{
	(void)buf;
	(void)sz;
	(void)hash;
	(void)hash_sz;

	return -FCSERR_ENIMP;
}
