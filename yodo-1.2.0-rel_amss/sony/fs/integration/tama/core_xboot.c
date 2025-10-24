/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdbool.h>
#include <stdint.h>
#include <fcsenv_def.h>
#include <fcserr.h>
#include <fcslog.h>
#include <fcs_endian.h>

int core_is_fused(bool *is_fused)
{
	if (*(uint32_t *)SEC_BOOT_AUTH_ADDR == SEC_BOOT_AUTH_MASK)
		*is_fused = true;
	else
		*is_fused = false;
	return FCSERR_OK;
}

int core_get_dieid(uint8_t *buf, size_t len)
{
	if (len < DIE_ID_LEN || len < sizeof(uint32_t)) {
		FCS_LOG_ERR("buffer too small (%d)\n", len);
		return -FCSERR_ESIZE;
	}
	write_be_u32(*(uint32_t *)DIE_ID_ADDR, buf);

	return FCSERR_OK;
}

int core_get_dieid_len(void)
{
	return DIE_ID_LEN;
}

int core_is_test_cert_allowed(void)
{
	uint32_t hwid = *(uint32_t *)OEM_IDS_ADDR;

	/* HWID is the 16 lowest bits */
	hwid &= 0xFFFF;

	if (hwid != 0) {
		FCS_LOG_INF("Unit is fused with hw id != 0\n");
		return 0;
	}

	return 1;
}

