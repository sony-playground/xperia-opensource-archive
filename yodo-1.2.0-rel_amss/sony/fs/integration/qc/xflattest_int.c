/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdint.h>
#include <string.h>
#include <xflattest.h>
#include <qsee.h>
#include <fcslog.h>
#include <fcserr.h>
#include "xflattest.h"
#include "xflattest_int.h"

#define QSEE_CMD_SIZE 4096

int read_xfl_sec_data(struct xfl_sec_data *data)
{
	int res;

	struct xflattest_cmd *cmd = NULL;
	struct xflattest_rsp *rsp = NULL;
	struct get_raw_data_cmd *req = NULL;
	static struct qsee_handle *hdl;

	if (data == NULL) {
		FCS_LOG_ERR("invalid pointer\n");
		return -FCSERR_EINVAL;
	}

	if (!hdl) {
		hdl = qsee_start_app("tzxflattest", QSEE_CMD_SIZE);
		if (!hdl) {
			FCS_LOG_ERR("could not find application\n");
			res = -FCSERR_ENOTF;
			goto exit;
		}
	}

	cmd = calloc(1,
		sizeof(struct xflattest_cmd) + sizeof(struct get_raw_data_cmd));

	if (cmd == NULL) {
		FCS_LOG_ERR("calloc failed\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	req = (struct get_raw_data_cmd *) (cmd + 1);
	cmd->cmd_id = XFLATTEST_CMD_GET_RAW_SEC_DATA;
	req->index = RAW_XFL_SECDATA_INDEX;

	rsp = calloc(1,
		sizeof(struct xflattest_rsp) + sizeof(struct xfl_sec_data));

	if (rsp == NULL) {
		FCS_LOG_ERR("calloc failed\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	rsp->payload_len = sizeof(struct xfl_sec_data);

	res = qsee_execute_cmd(
		hdl, cmd,
		sizeof(struct xflattest_cmd) + sizeof(struct get_raw_data_cmd),
		rsp,
		sizeof(struct xflattest_rsp) + sizeof(struct xfl_sec_data));

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("failed to execute qsee app\n");
		res = -FCSERR_ENOENT;
		goto exit;
	}

	if (rsp->result) {
		FCS_LOG_ERR("xflattest returned error (%d)\n", rsp->result);
		res = -FCSERR_PERM;
		goto exit;
	}

	memcpy(data, (void *)(rsp + 1), sizeof(struct xfl_sec_data));

exit:
	if (cmd)
		free(cmd);
	if (rsp)
		free(rsp);

	return res;
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

	FCS_LOG_INF("%s Soc-unique-id not supported on QC platform\n",
		__func__);

	return -FCSERR_ENIMP;
}

int get_suid_len(void)
{
	return 0;
}

int init_xflattest(void)
{
	int res;

	res = qsee_start_qseecomd();
	if (res != FCSERR_OK)
		FCS_LOG_ERR("qsee_start_qseecomd failed (%d)\n", res);

	return res;
}

int deinit_xflattest(void)
{
	int res;

	res = qsee_stop_qseecomd();
	if (res != FCSERR_OK)
		FCS_LOG_ERR("qsee_stop_qseecomd failed (%d)\n", res);

	return res;
}
