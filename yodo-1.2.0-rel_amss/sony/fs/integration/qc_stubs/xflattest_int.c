/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdint.h>
#include <string.h>
#include <xflattest.h>
#include <fcslog.h>
#include <fcserr.h>
#include "xflattest.h"
#include "xflattest_int.h"

#define QSEE_CMD_SIZE 4096

int read_xfl_sec_data(struct xfl_sec_data *data)
{
	(void)data;
	return FCSERR_OK;
}

int write_xfl_sec_data(struct xfl_sec_data *data)
{
	(void)data;
	FCS_LOG_ERR("%s is not implemented\n", __func__);
	return -FCSERR_ENIMP;
}

int read_suid_data(uint8_t *buf, uint8_t bufsize)
{
	(void)(buf); /* Unused parameter */
	(void)(bufsize); /* Unused parameter */

	FCS_LOG_ERR("%s Soc-unique-id not supported on QC platform\n",
		__func__);

	return -FCSERR_ENIMP;
}

int get_suid_len(void)
{
	return 0;
}

int init_xflattest(void)
{
	return FCSERR_OK;
}

int deinit_xflattest(void)
{
	return FCSERR_OK;
}
