/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */


#ifndef AUTHENTICATE_COMMON_H_
#define AUTHENTICATE_COMMON_H_

#include <ks.h>
#include "sake_engine_internal.h"

/* Default empty cert revocation list */
static const uint8_t default_crl[14] = {
	0x30, 0x82, 0x00, 0x0a, 0x02, 0x01, 0x00, 0x02,
	0x01, 0x00, 0x02, 0x82, 0x00, 0x00
};

struct sake_pubkey_info {
	uint8_t pub_hash[4];
	uint8_t rsa_pub_key[526]; /* contain pk in DER */
	uint8_t crl[14];
};

enum item_array_type {
	ITEM_ARRAY_EXPONENT = 1,
	ITEM_ARRAY_MODULUS
};

struct item_array {
	uint32_t length;
	uint8_t *data;
};

/*
 * Utility functions begin
 */

int extract_public_key_parts(asn_rsa_public_key_t asn1,
				    struct item_array *item,
				    enum item_array_type iat);

/*
 * Crypto Integration functions
 */

/*
 * Raw RSA Encrypt
 */
int rsa_encrypt_nopad(const uint8_t *in_buffer_p,
			     size_t in_buffer_size,
			     uint8_t *out_buffer_p,
			     size_t out_buffer_size,
			     const asn_rsa_public_key_t public_key);

/*
 * Digest is generated with sha1 on RSA public key in PEM format
 */
int extract_pubkey(struct ksstore_blob *ksblob,
		struct sake_pubkey_info *root);


#endif
