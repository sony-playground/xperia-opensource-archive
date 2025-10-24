/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef CRYP_UTIL_H_
#define CRYP_UTIL_H_

int cryp_get_pk_hash(
	const uint8_t *cert_data, uint32_t cert_len,
	uint8_t *hash, uint32_t hash_len);

#define CRYP_MAX_PK_LEN 4096

#endif
