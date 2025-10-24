/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef KSCRYPTO_H_
#define KSCRYPTO_H_

#include "fcs_defines.h"
#include <stdint.h>

/**
 * @brief CMS Signature verification pointer prototype
 */
int plf_cms_cb(
	const uint8_t *const rot, const uint32_t rot_sz,
	const uint8_t *const msg, const uint32_t msg_sz,
	struct dev_binding *binding,
	uint32_t *verified_with_hmac, uint32_t *counter,
	uint8_t **payload, uint32_t *payload_sz);

#endif
