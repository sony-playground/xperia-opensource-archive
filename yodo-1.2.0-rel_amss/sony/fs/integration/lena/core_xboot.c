/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdbool.h>
#include <stdint.h>
#include <fcsenv_def.h>
#include <fcserr.h>
#include <fcslog.h>
#include <fcs_endian.h>

#include <string.h>	/* memcpy */
#include <stdio.h>	/* snprintf */

#include "xboot_pal_types.h"

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

int core_get_platformid(uint8_t *buf, size_t len)
{
	if (len < PLATFORM_ID_LEN || len < sizeof(uint32_t)) {
		FCS_LOG_ERR("buffer too small (%d)\n", len);
		return -FCSERR_ESIZE;
	}
	write_be_u32(*(uint32_t *)PLATFORM_ID_ADDR, buf);

	return FCSERR_OK;
}

int core_get_platformid_len(void)
{
	return DIE_ID_LEN;
}

int core_get_root_key_hash(unsigned char *buf, unsigned int len)
{
	int res;

	if (len != PLATFORM_ROOT_KEY_HASH_LEN) {
		FCS_LOG_ERR("Wrong buffer size (%u), expected %u\n", len,
			PLATFORM_ROOT_KEY_HASH_LEN);
		return -FCSERR_ESIZE;
	}

#if 1
	memcpy(buf, (const void *)PLATFORM_ROOT_KEY_HASH_ADDR, PLATFORM_ROOT_KEY_HASH_LEN);
	res = FCSERR_OK;
#else
	res = fcs_read_memmap(PLATFORM_ROOT_KEY_HASH_ADDR, buf,
		PLATFORM_ROOT_KEY_HASH_LEN);
#endif

	return res;
}

int core_get_root_key_hash_len(void)
{
	return PLATFORM_ROOT_KEY_HASH_LEN;
}

int core_get_sector_size(char *buf, unsigned int buf_sz)
{
	snprintf(buf, buf_sz, "%d", DEFAULT_SECTOR_SIZE);
	return FCSERR_OK;
}

int core_get_usb_version(char *buf, unsigned int buf_sz)
{

	UINTN addr = USB3_PRI_DSTS_ADDR;
	DWC_DEVICE_CONNECT_SPEED support_speed = DWC_SUPER_SPEED;
	DWC_DEVICE_CONNECT_SPEED bus_speed;
	UINT16 speed = 0x0100;

	bus_speed = (DWC_DEVICE_CONNECT_SPEED)((*(volatile UINT32*)addr) &
                                    USB3_PRI_DSTS_CONNECTSPD_BMSK);
	if (bus_speed > support_speed)
		bus_speed = support_speed;

	/* It is made with reference to kernel/msm-4.19/drivers/usb/gadget/composite.c */
	switch (bus_speed) {
	case DWC_HIGH_SPEED:
		speed = 0x0210;
		break;
	case DWC_FULL_SPEED:
	case DWC_FULL_SPEED_48:
		speed = 0x0110;
		break;
	case DWC_LOW_SPEED:
		speed = 0x0100;
		break;
	case DWC_SUPER_SPEED:
		speed = 0x0300;
		break;
	case DWC_SUPER_SPEED_PLUS:
		speed = 0x0310;
		break;
	}
	snprintf(buf, buf_sz, "0x%04x", speed);

	return FCSERR_OK;
}

int core_get_battery_capacity(char *buf, unsigned int buf_sz)
{
	UINT32 soc;
	if (xbpal_get_battery_capacity(&soc) != FCSERR_OK ){
		FCS_LOG_WRN("Failed to read battery capacity\n");
		snprintf(buf, buf_sz, "N/A");
	} else {
		snprintf(buf, buf_sz, "%d", soc);
	}

	return FCSERR_OK;
}

int core_is_test_cert_allowed(void)
{
	uint32_t productid = *(uint32_t *)OEM_IDS_ADDR;

	/* Product id is bit 15-31 of the register */
	productid >>= 16;
	productid &= 0xFFFF;

	if (productid != 0) {
		FCS_LOG_INF("Unit is fused with product id != 0\n");
		return 0;
	}

	return 1;
}

int core_get_storage_info(char *buf, unsigned int buf_sz)
{
	if (xbpal_get_ufs_info((UINT8 *)buf, buf_sz) != FCSERR_OK) {
		return -FCSERR_EIO;
	}
	return FCSERR_OK;
}
