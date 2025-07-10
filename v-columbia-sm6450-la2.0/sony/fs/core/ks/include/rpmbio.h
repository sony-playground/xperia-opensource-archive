/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _RPMB_IO_H_
#define _RPMB_IO_H_

#include <stdint.h>
#include "kstypes.h"
#include "ksio.h"
#include "digest_types.h"

#define RPMB_DATA_VERSION 1

struct ks_rpmb_data {
	uint32_t ks_counter;
	uint32_t xcs_rot;
	uint8_t  ks_hash_sha256[SHA256_HASH_OUT_SIZE];
};

/**
 * @brief Create RPMB IO handle
 *
 *
 * @param[out] handle        Opaque IO Handle
 * Handle can be used for functions in ksstore.h and ksaccess.h
 * Handle must be freed with with ks_io_delete() when use is over
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int rpmb_open(struct ks_io_handle **handle);

#endif
