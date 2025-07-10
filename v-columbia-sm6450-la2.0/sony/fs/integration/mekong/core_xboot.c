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
	uint16_t productid = 0;

	/* Product id is bit 15-31 of the register */
	write_be_u16((*(uint32_t *)OEM_IDS_ADDR) >> 16, (uint8_t *)&productid);

	if (productid != 0) {
		FCS_LOG_INF("Unit is fused with product id != 0\n");
		return 0;
	}

	return 1;
}
