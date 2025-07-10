/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdbool.h>
#include <stdint.h>
#include <fcsenv_def.h>
#include <fcserr.h>
#include <fcslog.h>
#include <fcs_endian.h>
#include "fcsotp_def.h"

int core_is_fused(bool *is_fused)
{
	uint32_t lock;
	uint32_t sec_lock;
	uint32_t sec_ctrl;
	uint32_t sec_msc;

	if (is_fused == NULL) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	/* Read the fuses */
	lock = *(uint32_t *)EFUSE_LOCK_ADDR & LOCK_FLAGS;
	sec_lock = *(uint32_t *)EFUSE_SEC_LOCK_ADDR & SEC_LOCK_FLAGS;
	sec_ctrl = *(uint32_t *)EFUSE_SEC_CTRL_ADDR & SEC_CTRL_FLAGS;
	sec_msc = *(uint32_t *)EFUSE_SEC_MSC_ADDR & SEC_MSC_FLAGS;

	/* check state against flags and update result */
	if (sec_lock == SEC_LOCK_FLAGS && lock == LOCK_FLAGS &&
		sec_ctrl == SEC_CTRL_FLAGS && sec_msc == SEC_MSC_FLAGS) {
		*is_fused = true;
	} else
		*is_fused = false;

	return FCSERR_OK;
}

int core_get_dieid(uint8_t *buf, size_t len)
{
	int offset;

	if (len < DIE_ID_LEN || len < sizeof(uint32_t)) {
		FCS_LOG_ERR("buffer too small (%d)\n", len);
		return -FCSERR_ESIZE;
	}
	for (offset = 0; offset < DIE_ID_LEN; offset += sizeof(uint32_t))
		write_be_u32(*(uint32_t *)(DIE_ID_ADDR + offset), buf + offset);

	return FCSERR_OK;
}

int core_get_dieid_len(void)
{
	return DIE_ID_LEN;
}

int core_is_test_cert_allowed(void)
{
	uint32_t productid;

	productid = *(uint32_t *)EFUSE_C_DAT0_ADDR;
	if (productid != 0) {
		FCS_LOG_INF("Unit is fused with product id != 0\n");
		return 0;
	}

	return 1;
}
