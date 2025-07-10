/*
 * Copyright 2023 Sony Corporation.
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

#define DUMMY_PLATFORM_ROOT_KEY_HASH_LEN 56
#define ROOT_KEY_HASH_COPY_SIZE 4

int core_is_fused(bool *is_fused)
{
	if ((*(uint32_t *)SEC_BOOT_AUTH_ADDR & SEC_BOOT_AUTH_MASK)
                                             == SEC_BOOT_IS_FUSED)
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
	unsigned char dummy_buf[DUMMY_PLATFORM_ROOT_KEY_HASH_LEN];
	unsigned char buf_tmp[PLATFORM_ROOT_KEY_HASH_LEN + 1];
	uint32_t dummy_index = 0;
	uint32_t buf_i = 0;

	if (len != PLATFORM_ROOT_KEY_HASH_LEN) {
		FCS_LOG_ERR("Wrong buffer size (%u), expected %u\n", len,
			PLATFORM_ROOT_KEY_HASH_LEN);
		return -FCSERR_ESIZE;
	}


	/* Obtain from the PLATFORM_ROOT_KEY_HASH_ADDR address        */
	/* with copymem for each ROOT_KEY_HASH_COPY_SIZE.             */
	unsigned char * addr = (void *)PLATFORM_ROOT_KEY_HASH_ADDR;
	int copy_size = ROOT_KEY_HASH_COPY_SIZE;
	for(int j = 0; j < DUMMY_PLATFORM_ROOT_KEY_HASH_LEN;
					j = j + ROOT_KEY_HASH_COPY_SIZE)
	{
		if((j + ROOT_KEY_HASH_COPY_SIZE) >= DUMMY_PLATFORM_ROOT_KEY_HASH_LEN)
			copy_size = (DUMMY_PLATFORM_ROOT_KEY_HASH_LEN - j);
		memcpy((dummy_buf + j), (addr + j), copy_size);
	}

	/* There is 1 byte of 00 padding for every 7 bytes.           */
	/* Therefore, the value without padding is returned.          */
	/*                                                            */
	/*          |<--------------------56byte------------------>|  */
	/*          | 7byte |  1byte | 7byte |  1byte |............|  */
	/*          |----------------------------------------------|  */
	/* dummy_buf|<value>|<pading>|<value>|<pading>|............|  */
	/*          |----------------------------------------------|  */
	/*                                                            */
	/*          |<--------------------48byte------------------>|  */
	/*          | 7byte | 7byte | 7byte | 7byte |..............|  */
	/*          |----------------------------------------------|  */
	/* buf_tmp  |<value>|<value>|<value>|<value>|..............|  */
	/*          |----------------------------------------------|  */
	while(buf_i < PLATFORM_ROOT_KEY_HASH_LEN)
	{
		memcpy((buf_tmp + buf_i), (dummy_buf + dummy_index), 8);
		buf_i= buf_i + 7;
		dummy_index = dummy_index + 8;
	}

	memcpy(buf, (const void *)buf_tmp, PLATFORM_ROOT_KEY_HASH_LEN);
	res = FCSERR_OK;
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
	FCS_LOG_INF("get battery not support\n");
	snprintf(buf, buf_sz, "N/A");
	return -FCSERR_SUPPORT;
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
