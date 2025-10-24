/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef KS_UTIL_
#define KS_UTIL_

#include <kstypes.h>
#include <stdbool.h>

int ksutil_keystore_load(struct ks_ctx *ks, uint8_t part);
int ksutil_keystore_init(struct ks_ctx **ks, bool load, uint8_t part,
		const uint8_t *hmac_key, uint32_t hmac_key_len);

#endif
