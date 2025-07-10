/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "fcslog.h"
#include "fcserr.h"
#include "xflattest.h"
#include "xflattest_int.h"
#include "xfl_tz.h"
#include "sonytzxflattest_uuid.h"
#include "tar_utils.h"

#define SOC_UNIQUE_ID_LEN 16

int read_xfl_sec_data(struct xfl_sec_data *data)
{
	return xfl_tz_read(
		RPMB,
		RAW_XFL_SECDATA_INDEX,
		(uint8_t *)data,
		sizeof(struct xfl_sec_data));
}

int write_xfl_sec_data(struct xfl_sec_data *data)
{
	(void)(data); /* Unused parameter */
	return FCSERR_OK;
}

int read_suid_data(uint8_t *buf, uint8_t bufsize)
{
	int res;

	if (buf == NULL) {
		FCS_LOG_ERR("Buffer not allocated\n");
		return -FCSERR_EINVAL;
	}

	if (bufsize < SOC_UNIQUE_ID_LEN) {
		FCS_LOG_ERR("Buffer too small\n");
		return -FCSERR_ENOBUFS;
	}

	res = xfl_tz_read(SUID, 0, buf, SOC_UNIQUE_ID_LEN);

	return res;
}

int get_suid_len(void)
{
	return SOC_UNIQUE_ID_LEN;
}

int init_xflattest(void)
{
	int res;

	res = extract_tar_from_partition("/vendor/app/mcRegistry",
			"tzxflattest");
	if (res != FCSERR_OK)
		FCS_LOG_ERR("Failed to extract tzxflattest trustlets\n");

	return res;
}

int deinit_xflattest(void)
{
	return FCSERR_OK;
}
