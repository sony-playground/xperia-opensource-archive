/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcserr.h"
#include "fcslog.h"
#include "fcsenv_def.h"
#include "linux_util.h"
#include <stdbool.h>

int core_has_sd_card(bool *has_card)
{
	(void) has_card;

	FCS_LOG_ERR("SD card status not supported\n");
	return -FCSERR_ENIMP;
}

int core_is_fused(bool *is_fused)
{
	int res = FCSERR_OK;
	uint32_t fuse = 0;

	if (is_fused == NULL) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	/* Read the fuse */
	res = fcs_read_memmap32(SEC_BOOT_AUTH_ADDR, &fuse);
	if (res < 0) {
		FCS_LOG_ERR("Failed memmap: %d\n", res);
		return -FCSERR_EIO;
	}

	/* Look at OEM SEC BOOT*/
	*is_fused = (fuse == SEC_BOOT_AUTH_MASK);

	return res;
}

int core_is_test_cert_allowed(void)
{
	int res;
	uint32_t productid = 0;

	res = fcs_read_memmap32(OEM_IDS_ADDR, &productid);

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("fcs_read_memmap failed (%d)\n", res);
		return 0;
	}

	/* Product id is bit 15-31 of the register */
	productid >>= 16;
	productid &= 0xFFFF;

	if (productid != 0) {
		FCS_LOG_INF("Unit is fused with product id != 0\n");
		return 0;
	}

	return 1;
}

