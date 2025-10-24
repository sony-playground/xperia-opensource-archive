/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "authenticate_common.h"
#include "fcserr.h"

int rsa_encrypt_nopad(const uint8_t *in_buffer_p,
			     size_t in_buffer_size,
			     uint8_t *out_buffer_p,
			     size_t out_buffer_size,
			     const asn_rsa_public_key_t public_key)
{
	(void)in_buffer_p;
	(void)in_buffer_size;
	(void)out_buffer_p;
	(void)out_buffer_size;
	(void)public_key;

	return -FCSERR_ENIMP;
}

int extract_pubkey(struct ksstore_blob *ksblob,
		struct sake_pubkey_info *root)
{
	(void)ksblob;
	(void)root;

	return -FCSERR_ENIMP;

}
