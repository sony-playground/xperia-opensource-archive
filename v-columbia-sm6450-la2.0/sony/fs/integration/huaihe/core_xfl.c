/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcserr.h"
#include "fcslog.h"
#include "fcs_endian.h"
#include "fcsenv_def.h"
#include "fcsotp_def.h"
#include "linux_util.h"
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

#define SD_CARD_SYSFS_NODE "/dev/block/mmcblk1"

int core_has_sd_card(bool *has_card)
{
	int fd;

	if (has_card == NULL) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	*has_card = false;

	/* no card is inserted if open returns < 0  */
	fd = open(SD_CARD_SYSFS_NODE, O_RDONLY, 0644);
	if (fd >= 0)
		*has_card = true;

	return FCSERR_OK;
}

int core_is_fused(bool *is_fused)
{
	int res = FCSERR_OK;
	uint32_t lock;
	uint32_t sec_lock;
	uint32_t sec_ctrl;
	uint32_t sec_msc;

	if (is_fused == NULL) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	/* false is default */
	*is_fused = false;

	/* Read the fuses */
	res = fcs_read_memmap32(EFUSE_LOCK_ADDR, &lock);
	if (res != FCSERR_OK)
		goto exit;

	res = fcs_read_memmap32(EFUSE_SEC_LOCK_ADDR, &sec_lock);
	if (res != FCSERR_OK)
		goto exit;

	res = fcs_read_memmap32(EFUSE_SEC_CTRL_ADDR, &sec_ctrl);
	if (res != FCSERR_OK)
		goto exit;

	res = fcs_read_memmap32(EFUSE_SEC_MSC_ADDR, &sec_msc);
	if (res != FCSERR_OK)
		goto exit;

	/* check state against flags and update result */
	lock &= LOCK_FLAGS;
	sec_lock &= SEC_LOCK_FLAGS;
	sec_ctrl &= SEC_CTRL_FLAGS;
	sec_msc &= SEC_MSC_FLAGS;

	if (sec_lock == SEC_LOCK_FLAGS && lock == LOCK_FLAGS &&
		sec_ctrl == SEC_CTRL_FLAGS && sec_msc == SEC_MSC_FLAGS) {
		*is_fused = true;
	}
exit:
	return res;
}

int core_is_test_cert_allowed(void)
{
	int res;
	uint32_t productid = 0;

	res = fcs_read_memmap32(EFUSE_C_DAT0_ADDR, &productid);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("fcs_read_memmap failed (%d)\n", res);
		return 0;
	}

	if (productid != 0) {
		FCS_LOG_INF("Unit is fused with product id != 0\n");
		return 0;
	}

	return 1;
}
