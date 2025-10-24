/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/* This is the platform dependent layer, currently supported platforms tone and
 * yoshino have the same implementation but when other platforms are added the
 * functions in this file needs to be moved to platform dependent folders/files
 */

#include "fcsenv.h"
#include "fcslog.h"
#include "fcserr.h"
#include "fcsenv_def.h"
#include "linux_util.h"
#include "fcs_endian.h"

int fcsenv_get_platformid(uint8_t *buf, size_t len)
{
	int res;

	if (len < PLATFORM_ID_LEN) {
		FCS_LOG_ERR("buffer too small (%zd)\n", len);
		return -FCSERR_ESIZE;
	}

	res = fcs_read_memmap(PLATFORM_ID_ADDR, buf, PLATFORM_ID_LEN);
	write_be_u32(*((uint32_t *)buf), buf);

	return res;
}

int fcsenv_get_platformid_len(void)
{
	return PLATFORM_ID_LEN;
}
