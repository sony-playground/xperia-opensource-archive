/*
 * Copyright (c) 2014 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef FCS_CRYPTO_H_
#define FCS_CRYPTO_H_

#include "stddef.h"
#include "stdint.h"

/**
 * @defgroup fcs_crypto Cryptographic interface
 * @brief Generic definitions and function types for cryptographic
 * operations.
 *
 * Software implementations for these functions are provided in openssl,
 * but the interface can also be implemented using hardware accelerated
 * drivers.
 *
 */

/**
 * @defgroup hash Hash calculation interface
 * @brief API definition for hash calculations.
 * @{
 */

/**
 * @brief HASH types supported
 */
typedef enum {
	UNDEFINED_HASH    = 0, /*!< Unsupported hash */
	SHA1_HASH         = 1, /*!< SHA1 hash (size is 20 bytes) */
	SHA256_HASH       = 2, /*!< SHA256 hash (size is 32 bytes) */
} hash_type_t;

/**
 * @brief Hash context type.
 */
typedef void *hash_context_t;

/**
 * @brief Do atomic hash calculation
 *
 * This function is used to make an atomic hash calculation on the provided
 * data. Implementation must be thread safe. ERR_BUSY should be returned
 * if the host crypto engine is busy with an ongoing hash operation in which
 * case the (*hast_t) call can be retried after a short delay.
 *
 * @param[in] hash_type           Hash type
 * @param[in] data_p              Data to hash
 * @param[in] len                 Length of data to hash
 * @param[out] digest_p           Return hash
 * @param[in] digest_size         Expected length of hash
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*hash_t)(hash_type_t hash_type, const uint8_t *data_p,
		      size_t len, uint8_t *digest_p, size_t digest_size);

/**
 * @brief Init hash session/context
 *
 * This function is called to start a hash session.
 * It will allocate the context and initiate the session state.
 *
 * @param[in] context_p           Returned context
 * @param[in] hash_type           Hash type
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*hash_init_t)(hash_context_t *context_p,
			   hash_type_t hash_type);

/**
 * @brief Reinit hash session/context
 *
 * This function is called to restart a hash session without allocation of
 * new context.
 *
 * @param[in] context             Context
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*hash_reinit_t)(hash_context_t context);

/**
 * @brief Update hash with section of data
 *
 * This function is called to calculate hash on a section of data.
 *
 * @param[in] context             Context
 * @param[in] data_p              Data to hash
 * @param[in] len                 Length of data to hash
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*hash_update_t)(hash_context_t context,
			     const uint8_t *data_p, size_t len);

/**
 * @brief Get the length of hash
 *
 * This function is called to return the length of a hash for a given context.
 *
 * @param[in] context         Context
 * @param[out] size_p         Return size of hash (storage allocated by caller)
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*hash_get_hash_size_t)(hash_context_t context,
				    size_t *size_p);

/**
 * @brief Complete hash calculation
 *
 * This function is called to finalize hash calculate and return hash.
 *
 * @param[in] context             Context
 * @param[out] digest_p           Return hash (storage allocated by caller)
 * @param[in] digest_size         Expected length of hash
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*hash_final_t)(hash_context_t context,
			    uint8_t *digest_p, size_t digest_size);

/**
 * @brief Cleanup session/context
 *
 * This function is called to cleanup the hash session/context.
 *
 * @param[in] context             Context
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*hash_deinit_t)(hash_context_t context);
/** @} */

/**
 * @defgroup rsa RSA calculation interface
 * @brief API definition for RSA calculations.
 * @{
 */

/**
 * @brief ASN.1 endcoded RSA key type.
 *
 * Expected format:
 * 0x30, 0x82, lenTotHi, lenTotLo,
 * 0x02, 0x82, lenHiMod, lenLoMod, ... modulus,
 * 0x02, lenExp, ... exponent
 */
typedef uint8_t *asn_rsa_public_key_t;

/**
 * @brief Verify RSA signture with data
 *
 * This function is called to verify a PKCS1 v1.5? RSA signature.
 * The digest (hash) on the data is calculated inside the function.
 *
 * @param[in] signature_p         The signature
 * @param[in] signature_size      The signature length
 * @param[in] message_p           The signed data
 * @param[in] message_size,       The length of the signed data
 * @param[in] public_key          The public key
 * @param[in] hash_type           The digest (hash) operation
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*rsa_verify_signature_t)(
				      const uint8_t *signature_p,
				      size_t signature_size,
				      const uint8_t *message_p,
				      size_t message_size,
				      const asn_rsa_public_key_t public_key,
				      hash_type_t hash_type);

/**
 * @brief Verify RSA signture with data
 *
 * This function is called to verify a PKCS1 v1.5? RSA signature.
 * The digest (hash) on the data is calculated outside the function.
 *
 * @param[in] signature_p         The signature
 * @param[in] signature_size      The signature length
 * @param[in] hash_p              The digest of the signed data
 * @param[in] hash_size,          The digest length
 * @param[in] public_key          The public key
 * @param[in] hash_type           The digest (hash) operation
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*rsa_verify_digest_t)(
				   const uint8_t *signature_p,
				   size_t signature_size,
				   const uint8_t *hash_p,
				   size_t hash_size,
				   const asn_rsa_public_key_t public_key,
				   hash_type_t hash_type);

/**
 * @brief RSA encrypt data
 *
 * This function is called to do a raw RSA encrypt of data (modulus size).
 *
 * @param[in] in_buffer_p         The indata
 * @param[in] in_buffer_size      The indata length
 * @param[in] out_buffer_p        The outdata
 * @param[in] out_buffer_size     The outdata length
 * @param[in] public_key          The public key
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*rsa_encrypt_nopad_t)(
				   const uint8_t *in_buffer_p,
				   size_t in_buffer_size,
				   uint8_t *out_buffer_p,
				   size_t out_buffer_size,
				   const asn_rsa_public_key_t public_key);

/**
 * @brief Generate random data
 *
 * This function is called to generate random data.
 *
 * @param[out] data_p             The random data (storage allocated by caller)
 * @param[in] len                 The random data length
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int (*random_data_t)(uint8_t *data_p, size_t len);
/** @} */
/** @} */
#endif /* FCS_CRYPTO_H_ */
