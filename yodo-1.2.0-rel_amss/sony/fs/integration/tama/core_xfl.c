/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcserr.h"
#include "fcslog.h"
#include "fcs_endian.h"
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
	uint32_t buf = 0;

	if (is_fused == NULL) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	/* true is default */
	*is_fused = true;

	/* Read the fuse */
	res = fcs_read_memmap(SEC_BOOT_AUTH_ADDR, (uint8_t *)&buf, sizeof(buf));
	if (res < 0) {
		FCS_LOG_ERR("Failed memmap: %d\n", res);
		return -FCSERR_EIO;
	}

	/* Look at OEM SEC BOOT*/
	if (buf != SEC_BOOT_AUTH_MASK)
		*is_fused = false;

	return res;
}

int core_is_test_cert_allowed(void)
{
	int res;
	uint32_t hwid = 0;

	res = fcs_read_memmap(
		OEM_IDS_ADDR, (uint8_t *)&hwid, OEM_IDS_LEN);

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("fcs_read_memmap failed (%d)\n", res);
		return 0;
	}

	/* HWID is the 16 lowest bits */
	hwid &= 0xFFFF;

	if (hwid != 0) {
		FCS_LOG_INF("Unit is fused with hw id != 0\n");
		return 0;
	}

	return 1;
}

