/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcsenv.h"
#include "fcslog.h"
#include "fcserr.h"
#include "fcsenv_def.h"
#include "linux_util.h"
#include "fcs_endian.h"

int core_get_dieid(uint8_t *buf, size_t len)
{
	int res;
	int offset;

	if (len < DIE_ID_LEN || len < sizeof(uint32_t)) {
		FCS_LOG_ERR("buffer too small (%zd)\n", len);
		return -FCSERR_ESIZE;
	}

	res = fcs_read_memmap(DIE_ID_ADDR, buf, DIE_ID_LEN);
	for (offset = 0; offset < DIE_ID_LEN; offset += sizeof(uint32_t))
		write_be_u32(*(uint32_t *)(buf + offset), buf + offset);

	return res;
}

int core_get_dieid_len(void)
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

	res = fcs_read_memmap(PLATFORM_ROOT_KEY_HASH_ADDR, buf,
		PLATFORM_ROOT_KEY_HASH_LEN);

	return res;
}

int core_get_root_key_hash_len(void)
{
	return PLATFORM_ROOT_KEY_HASH_LEN;
}

