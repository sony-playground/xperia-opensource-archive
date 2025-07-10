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
