/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef KS_STATIC_H_
#define KS_STATIC_H_

#include "kstypes.h"

/* Keystore Interface							*/
/* Currently one implementations exits:					*/
/* KSPK - NO support for dynamic  (on device) operations		*/
/* Initialize using ks_pk_init() (kspk.h)				*/
/* This implementation required NV and Crypto support			*/

/* The "domain" concept is to support separation of Sony|XCS		*/
/* Root of trusts - the key ownership offered to XCS partners does 	*/
/* not include keys used for sony proprietairy subsystems		*/

#define XFLKEYSTORE_PRIM 0
#define XFLKEYSTORE_BAK  1
/**
 * @brief Get number of keys for a specified domain
 *
 * @param[in]  context    The keystore handle (created in ks_create())
 * @param[in]  domain     The target domain
 * @param[out] nof_keys   The number keys in domaion
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int ks_get_nof_keys(struct ks_ctx *const context,
			uint32_t domain,
			uint32_t *nof_keys);

/**
 * @brief Get a key by index (index is within specified domain)
 *
 * @param[in]  context    The keystore handle (created in ks_create())
 * @param[in]  domain     The domain
 * @param[in]  index      Entry number (0 <= key_index < ks_get_nof_keys())
 * @param[out] keyblob    Data for entry index in domain domain
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int ks_get_key_by_index(struct ks_ctx *const context,
			const uint32_t domain,
			const uint32_t key_index,
			struct ksstore_blob *keyblob);


/**
 * @brief Updates the backup keystore and secure storage data if the
 *        keystore has been updated. Updates the HMAC key if the keystore
 *        has been verified against HMAC devid. Reverts the primary keystore if
 *        it is invalid.
 *
 * @param[in]  context    The keystore handle (created in ks_create())
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int ks_set_keystore(struct ks_ctx *const context);

/**
 * @brief Load the keystore from NV
 *
 * @param[in]  context    The keystore handle (created in ks_create())
 * @param[in]  part       The keystore partition (primary or backup).
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int ks_load_keystore(struct ks_ctx *const context, uint8_t part);

/**
 * @brief Compare the keystore partitions
 *
 * @param[in]  context    The keystore handle (created in ks_create())
 * @param[out] equal      Indicates whether the keystore partitions
 *                        are identical
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int ks_compare_partitions(struct ks_ctx * const context, int *equal);
/**
 * @brief Destroy keystore
 *
 * @param[in]  context    The keystore handle (created in ks_create())
 */
void ks_destroy(struct ks_ctx *const context);

/**
 * @brief Check if an XCS keystore has been updated
 *
 * @param[in]  context       The keystore handle (created in ks_create())
 * @param[out] xcs_updated   Indicates whether an XCS keystore has been updated
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int ks_get_xcs_updated(struct ks_ctx *const context, uint32_t *xcs_updated);

/* get the rpmb counter in keystore */
int ks_get_counter(struct ks_ctx *ctx, uint32_t *counter);

/* get the xcs rot boolean in keystore */
int ks_get_is_xcs_rot(struct ks_ctx *ctx, uint32_t *is_xcs_rot);

/* get the xcs rot flag in secure storage */
int ks_get_sec_stor_xcs_rot(struct ks_ctx *ctx, uint32_t *is_xcs_set);

/* get sha256 hash of keystore payload */
int ks_get_hash(struct ks_ctx *const context, uint8_t *hash,
		uint32_t hash_len);

/* Returns 1 if ks is loaded, 0 if not */
int ks_is_loaded(struct ks_ctx *const context);

/* Out-param retval will be 1 if ks has been verified with HMAC key, 0 if not */
int ks_verified_with_hmac(struct ks_ctx *const context, int *retval);

/* Sets the update_hmac_key flag in the keystore context */
int ks_set_update_hmac_key(struct ks_ctx *const context);

/* Sets hmac_key and hmac_key_len in the keystore context */
int ks_set_hmac_key(struct ks_ctx *const context, const uint8_t *hmac_key,
		uint32_t hmac_key_len);

#endif
