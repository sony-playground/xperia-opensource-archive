/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef KSNVIO_H_
#define KSNVIO_H_

#include <stdint.h>
#include "kstypes.h"
#include "ksio.h"

#define KS_NV_ORG		(0)   /* Keystore "partition" #0 */
#define KS_NV_BAK		(1)   /* Keystore "partition" #1 */

struct nvio_state {
	uint32_t partition;
};

/**
 * @brief Create NV handle
 *
 *
 * @param[out] handle        Opaque handle to keystore
 * @param[in]  partition     KS_NV_ORG | KS_NV_BAK
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int nv_open(struct ks_io_handle **handle, uint32_t partition);

int plf_nv_read_cb(
	ks_io_state_t *state, uint8_t *data, uint32_t *data_sz);

int plf_nv_write_cb(
	ks_io_state_t *state, uint8_t *data, const uint32_t data_sz);

#endif
