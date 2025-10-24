/*
 * Copyright (C) 2013 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "otp_rw.h"

#include "fcserr.h"
#include "fcslog.h"
#include "qsee.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
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
	struct otp_rw_read_res *response;
	int32_t request_len;
	int res;
	uint8_t buf[OTP_CMD_SIZE];

	if (qsee_com_handle == NULL) {
		FCS_LOG_ERR("execute_tz_cmd, qsee_com_handle is NULL\n");
		return -FCSERR_EINVAL;
	}

	if (!hbuf) {
		FCS_LOG_ERR("execute_tz_cmd, hbuf is NULL\n");
		return -FCSERR_EINVAL;
	}

	if (hbuf->len && !dbuf) {
		FCS_LOG_ERR("execute_tz_cmd, dbuf is NULL\n");
		return -FCSERR_EINVAL;
	}

	if (hbuf->len + sizeof(struct otp_rw_head) > OTP_CMD_SIZE) {
		FCS_LOG_ERR("execute_tz_cmd, cmd too large\n");
		return -FCSERR_EINVAL;
	}

	/* prepare request struct with header and data */
	memcpy(buf, hbuf, sizeof(struct otp_rw_head));
	request_len = sizeof(struct otp_rw_head);
	if (dbuf) {
		memcpy(buf + sizeof(struct otp_rw_head), dbuf, hbuf->len);
		request_len += hbuf->len;
	}

	res = qsee_execute_cmd(
		qsee_com_handle, buf, request_len,
		buf, sizeof(struct otp_rw_read_res));

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to execute qsee_execute_cmd, %d", res);
		return res;
	}

	response = (struct otp_rw_read_res *)buf;

	FCS_LOG_INF(
		"sending cmd, req len: %d; resp data: (0x%08x 0x%08x)\n",
		request_len, response->data[0], response->data[1]);

	memcpy(rbuf->data, response->data, sizeof(response->data));
	rbuf->res = response->res;

	if (response->res) {
		FCS_LOG_ERR("Failed to read/write in tz-app (%08x)\n",
				response->res);
		return -FCSERR_EBURN;
	}

	return FCSERR_OK;
}

int otp_rw_init(void)
{
	qsee_com_handle = qsee_start_app("tzloader", OTP_CMD_SIZE);
	/* start tz app */
	if (!qsee_com_handle) {
		FCS_LOG_ERR("Error, Fused secure app did not start.\n");
		return -FCSERR_EBURN;
	}

	return FCSERR_OK;
}

void otp_rw_final(void)
{
	if (qsee_stop_app(qsee_com_handle))
		FCS_LOG_ERR("Error, fused_stop_tz_app failed.\n");

	qsee_com_handle = NULL;
}

int otp_read_row(uint32_t otp_addr, uint32_t *otp_data)
{
	int res;
	struct otp_rw_head head = {0, 0, 0, 0};
	struct otp_rw_entry ent = {0, 0, {0, 0} };
	struct otp_rw_read_res cmd_res = {0, {0, 0} };

	if (!otp_data) {
		FCS_LOG_ERR("invalid param");
		return -FCSERR_EINVAL;
	}

	/* init header */
	head.magic = OTP_RW_MAGIC;
	head.version = OTP_RW_VERSION;
	head.cmd = OTP_RW_CMD_READ;
	head.len = sizeof(ent);

	/* set addr */
	ent.addr = otp_addr;

	/* handle buffer */
	res =  otp_execute_tz_cmd(&head, (uint8_t *)&ent, &cmd_res);
	if (res) {
		FCS_LOG_ERR("Error, execute_tz_cmd failed, (%d).\n", res);
		return res;
	}

	otp_data[0] = cmd_res.data[0];
	otp_data[1] = cmd_res.data[1];

	return res;
}

int otp_write_cfg(const void *buf, const int len)
{
	int ret;
	struct otp_rw_head head = {0, 0, 0, 0};
	struct otp_rw_read_res cmd_res = {0, {0, 0} };

	if (!buf || len == 0) {
		FCS_LOG_ERR("invalid param");
		return -FCSERR_EINVAL;
	}

	/* init header */
	head.magic = OTP_RW_MAGIC;
	head.version = OTP_RW_VERSION;
	head.cmd = OTP_RW_CMD_WRITE;
	head.len = len;

	/* handle buffer */
	ret =  otp_execute_tz_cmd(&head, (uint8_t *)buf, &cmd_res);
	if (ret)
		FCS_LOG_ERR("Error, execute_tz_cmd failed, (%d).\n", ret);

	return ret;
}
