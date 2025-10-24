/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 *  Stubs for early bringup
 *
 */
#include "otp_rw.h"

#include "fcserr.h"
#include "fcslog.h"
#include "qsee.h"
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define OTP_RW_CMD_READ   0x00000000
#define OTP_RW_CMD_WRITE  0x01000000

#define OTP_RW_MAGIC   0x66553545
#define OTP_RW_VERSION 0

/* 8k is big enough for everyone (TM) */
#define OTP_CMD_SIZE 8192

static struct qsee_handle *qsee_com_handle;

struct otp_rw_head {
	uint32_t magic;
	uint32_t version;
	uint32_t cmd;
	uint32_t len;
};

struct otp_rw_read_res {
	uint32_t res;
	uint32_t data[2];
};

/*
 * Execute fused tz app cmd
 */
static int otp_execute_tz_cmd(
		struct otp_rw_head *hbuf, uint8_t *dbuf,
		struct otp_rw_read_res *rbuf)
{
	(void)(hbuf);
	(void)(dbuf);
	(void)(rbuf);

	return FCSERR_OK;
}

int otp_rw_init(void)
{
	return FCSERR_OK;
}

void otp_rw_final(void)
{
	qsee_com_handle = NULL;
}

int otp_read_row(uint32_t otp_addr, uint32_t *otp_data)
{

	(void)(otp_addr);
	(void)(otp_data);

	return FCSERR_OK;
}

int otp_write_cfg(const void *buf, const int len)
{
	(void)(buf);
	(void)(len);

	return FCSERR_OK;
}
