/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcserr.h"
#include "digest.h"
#include "cryp_util.h"

int cryp_get_pk_hash(
	const uint8_t *cert_data, uint32_t cert_len,
	uint8_t *hash, uint32_t hash_len)
{
	(void)cert_data;
	(void)cert_len;
	(void)hash;
	(void)hash_len;

	return -FCSERR_ENIMP;
}
