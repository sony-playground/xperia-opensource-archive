/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdint.h>
#include <string.h>
#include "fcslog.h"
#include "fcserr.h"
#include "cryp_util.h"

int cryp_get_pk_hash(
	const uint8_t *cert_data, uint32_t cert_len,
	uint8_t *hash, uint32_t hash_len)
{
	/* Getting the x-conf root is not supported using openssl.
	 * Add this if/when the need comes.
	 */

	(void)cert_data;
	(void)cert_len;
	(void)hash;
	(void)hash_len;

	FCS_LOG_ERR("Operation not supported\n");
	return -FCSERR_ENIMP;
}
