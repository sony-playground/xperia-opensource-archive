/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright (c) 2016 Sony Mobile Communications Inc.                         *
 * All rights, including trade secret rights, reserved.                       *
 ******************************************************************************
 * DESCRIPTION:                                                               *
 *   The interface is responsible for verifying a payload.                    *
 *                                                                            *
 *****************************************************************************/
#ifndef DIGEST_H_
#define DIGEST_H_

#include <stdlib.h>
#include <stdint.h>

#define DIGEST_SHA1_HASH_SIZE 20

struct digest;

/**
 *  Basic calculate and verify of sha256 digest given a data buffer and
 *  expected hash value.
 *
 *  @param [in]  databuffer              A pointer to the buffer of data
 *  @param [in]  databuffer_size         Size, in bytes, of the buffer
 *  @param [in]  hash                    Hash value for verify
 *
 *  @returns int
 */
int digest_sha256_verify(
		uint8_t *databuffer,
		uint32_t databuffer_size,
		uint8_t *hash);

/**
 *  Create a sha256 digest session.
 *
 *  @param [in]  dgst              A pointer to variable receiving
 *                                   the session.
 *
 *  @returns int
 */
int digest_sha256_init(struct digest **dgst);

/**
 *  Create a sha224 digest session.
 *
 *  @param [in]  dgst              A pointer to variable receiving
 *                                   the session.
 *
 *  @returns int
 */
int digest_sha224_init(struct digest **dgst);

/**
 *  Clean up a sha256 digest session.
 *
 *  @param [in]  dgst              The session.
 *
 *  @returns none
 */
void digest_sha256_deinit(struct digest *dgst);

/**
 *  Clean up a sha224 digest session.
 *
 *  @param [in]  dgst              The session.
 *
 *  @returns none
 */
void digest_sha224_deinit(struct digest *dgst);

/**
 *  Update sha256 digest session with a data buffer.
 *
 *  @param [in]  dgst                  The session.
 *  @param [in]  databuffer              A pointer to the buffer of data
 *  @param [in]  databuffer_size         Size, in bytes, of the buffer
 *
 *  @returns int
 */
int digest_sha256_update(
		struct digest *dgst,
		uint8_t *databuffer,
		uint32_t databuffer_size);

/**
 *  Update sha224 digest session with a data buffer.
 *
 *  @param [in]  dgst                  The session.
 *  @param [in]  databuffer              A pointer to the buffer of data
 *  @param [in]  databuffer_size         Size, in bytes, of the buffer
 *
 *  @returns int
 */
int digest_sha224_update(
		struct digest *dgst,
		uint8_t *databuffer,
		uint32_t databuffer_size);

/**
 *  Finalize calculation of hash for sha256 digest session and
 *  return a buffer with hash value and size of hash. The buffer
 *  should NOT be freed.
 *
 *  @param [in]  dgst                  The session.
 *  @param [out]  hash                   Pointer to hash value
 *  @param [out]  hash_size              Size, in bytes, of the hash
 *
 *  @returns int
 */
int digest_sha256_final(
		struct digest *dgst,
		uint8_t **hash,
		uint32_t *hash_size);

/**
 *  Finalize calculation of hash for sha224 digest session and
 *  return a buffer with hash value and size of hash. The buffer
 *  should NOT be freed.
 *
 *  @param [in]  dgst                  The session.
 *  @param [out]  hash                   Pointer to hash value
 *  @param [out]  hash_size              Size, in bytes, of the hash
 *
 *  @returns int
 */
int digest_sha224_final(
		struct digest *dgst,
		uint8_t **hash,
		uint32_t *hash_size);

/**
 *  Create a sha1 digest session.
 *
 *  @param [in]  dgst              A pointer to variable receiving
 *                                   the session.
 *
 *  @returns int
 */
int digest_sha1_init(struct digest **dgst);

/**
 *  Update sha1 digest session with a data buffer.
 *
 *  @param [in]  dgst                  The session.
 *  @param [in]  databuffer            A pointer to the buffer of data
 *  @param [in]  databuffer_size       Size, in bytes, of the buffer
 *
 *  @returns int
 */
int digest_sha1_update(
		struct digest *dgst,
		uint8_t *databuffer,
		uint32_t databuffer_size);

/**
 *  Finalize calculation of hash for sha1 digest session and
 *  return a buffer with hash value and size of hash. The buffer
 *  should NOT be freed.
 *
 *  @param [in]  dgst                  The session.
 *  @param [out]  hash                 Pointer to hash value
 *  @param [out]  hash_size            Size, in bytes, of the hash
 *
 *  @returns int
 */
int digest_sha1_final(
		struct digest *dgst,
		uint8_t **hash,
		uint32_t *hash_size);

/**
 *  Clean up a sha1 digest session.
 *
 *  @param [in]  dgst              The session.
 *
 *  @returns none
 */
void digest_sha1_deinit(struct digest *dgst);

/**
 *  Basic calculate and verify of sha1 digest given a data buffer and
 *  expected hash value.
 *
 *  @param [in]  databuffer              A pointer to the buffer of data
 *  @param [in]  databuffer_size         Size, in bytes, of the buffer
 *  @param [in]  hash                    Hash value for verify
 *
 *  @returns int
 */
int digest_sha1_verify(
		uint8_t *databuffer,
		uint32_t databuffer_size,
		uint8_t *hash);

/**
 *  Calculation of sha1 hash and return a buffer with hash value and size of
 *  hash. The hash buffer MUST be allocated by the caller (20 bytes).
 *
 *  @param [in]     buf                   A pointer to the buffer of data
 *  @param [in]     sz                    Size, in bytes, of the buffer
 *  @param [in/out] hash                  Pointer to hash value (20 bytes)
 *  @param [in]     hash_sz               Size, in bytes, of the hash buffer
 *
 *  @returns FCSERR code
 */
int digest_sha1_calc(
	uint8_t *buf, uint32_t sz, uint8_t *hash, uint32_t hash_sz);

#endif /* DIGEST_H_ */
