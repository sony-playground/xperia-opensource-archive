/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
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
#include "tee_client_api.h"

struct TEE_TZApp_Info {
	char *appname;
	TEEC_UUID appuuid;
};

#define MAX_CMD_RETRIES 3

int xfl_tz_read(enum xfl_tz_read_type type, uint8_t index,
		uint8_t *data, uint32_t size)
{
	int res = FCSERR_OK;
	TEEC_Result result = TEEC_SUCCESS;
	struct xflattest_cmd *cmd = NULL;
	struct xflattest_rsp *rsp = NULL;
	struct get_raw_data_cmd *req = NULL;
	struct TEE_TZApp_Info teeAppInfo = {
			"tzxflattest", sonytzxflattest_UUID };
	TEEC_Operation operation;
	TEEC_SharedMemory sharedMemIn;
	TEEC_SharedMemory sharedMemOut;
	TEEC_Context *context = NULL;
	TEEC_Session *session = NULL;
	bool context_opened = false;
	bool session_opened = false;
	TEEC_UUID *uuid;
	int retry_counter = 0;
	int read_count = 0;

	if (data == NULL) {
		FCS_LOG_ERR("invalid pointer\n");
		return -FCSERR_EINVAL;
	}

	/* Context */
	context = calloc(1, sizeof(TEEC_Context));
	if (context == NULL) {
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	/* Initialize context part */
	result = TEEC_InitializeContext(NULL, context);
	if (result != TEEC_SUCCESS) {
		FCS_LOG_ERR("TEEC_InitializeContext failed (%x)", result);
		goto exit;
	}
	context_opened = true;

	/* Session */
	session = calloc(1, sizeof(TEEC_Session));
	if (session == NULL) {
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	uuid = &teeAppInfo.appuuid;

	/* Start Open Session Part */
	memset(&operation, 0, sizeof(TEEC_Operation));
	operation.paramTypes = 0;
	result = TEEC_OpenSession(context, session, uuid, TEEC_LOGIN_PUBLIC,
					NULL, &operation, NULL);
	if (result != TEEC_SUCCESS) {
		FCS_LOG_ERR("TEEC_InitializeContext failed (%x)", result);
		goto exit;
	}
	session_opened = true;

	cmd = malloc(sizeof(struct xflattest_cmd) +
			sizeof(struct get_raw_data_cmd));
	if (cmd == NULL) {
		FCS_LOG_ERR("cmd malloc failed\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	req = (struct get_raw_data_cmd *) (cmd + 1);
	rsp = malloc(sizeof(struct xflattest_rsp) + size);
	if (rsp == NULL) {
		FCS_LOG_ERR("rsp malloc failed\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	switch (type) {
	case RPMB:
		cmd->cmd_id = XFLATTEST_CMD_GET_RAW_SEC_DATA;
		break;
	case FUSE:
		cmd->cmd_id = XFLATTEST_CMD_READ_FUSE_DATA;
		break;
	case SUID:
		cmd->cmd_id = XFLATTEST_CMD_READ_SUID;
		break;
	default:
		FCS_LOG_ERR("invalid tz read type\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}
	rsp->payload_len = size;
	read_count = size / rsp->payload_len;

	sharedMemIn.size = sizeof(struct xflattest_cmd) +
			sizeof(struct get_raw_data_cmd);
	sharedMemIn.flags = TEEC_MEM_INPUT;
	result = TEEC_AllocateSharedMemory(context, &sharedMemIn);
	if (result != TEEC_SUCCESS) {
		FCS_LOG_ERR(
		"TEEC_AllocateSharedMemory failed: result:%d, size:%d",
		result, sharedMemIn.size);
		goto exit;
	}

	sharedMemOut.size = sizeof(struct xflattest_rsp) +
			sizeof(struct xfl_sec_data);
	sharedMemOut.flags = TEEC_MEM_INPUT;
	sharedMemOut.flags |= TEEC_MEM_OUTPUT;
	result = TEEC_AllocateSharedMemory(context, &sharedMemOut);
	if (result != TEEC_SUCCESS) {
		FCS_LOG_ERR(
		"TEEC_AllocateSharedMemory failed: result:%d, size:%d",
		result, sharedMemOut.size);
		goto exit;
	}

	memcpy(sharedMemOut.buffer, rsp, sharedMemOut.size);

	operation.params[1].memref.parent = &sharedMemOut;
	operation.params[1].memref.offset = 0;
	operation.params[1].memref.size = sharedMemOut.size;

	operation.started = 0;
	operation.params[0].memref.parent = &sharedMemIn;
	operation.params[0].memref.offset = 0;
	operation.params[0].memref.size = sharedMemIn.size;

	operation.paramTypes = TEEC_MEMREF_PARTIAL_INPUT;
	operation.paramTypes |= TEEC_MEMREF_PARTIAL_OUTPUT << 4;

	for (int i = 0; i < read_count; i++) {
		/*
		 * There is a 2 second sleep in rpmb-mtk.c when opening the rpmb
		 * session. So make sure we retry the command in case it fails
		 * with -FCSERR_EOPEN, up to 4 times, in 500 ms intervals.
		 */
		req->index = index + i;
		memcpy(sharedMemIn.buffer, cmd, sharedMemIn.size);

		do {
			result = TEEC_InvokeCommand(session,
					cmd->cmd_id,
					&operation, NULL);
			if (result != TEEC_SUCCESS) {
				FCS_LOG_ERR(
					"TEEC_InvokeCommand failed: result:%d, command:%d",
					result, cmd->cmd_id);
				res = -FCSERR_ENOENT;
				goto exit;
			}
			memcpy(rsp, sharedMemOut.buffer, sharedMemOut.size);

			if (rsp->result == FCSERR_OK)
				break;

			if (rsp->result != -FCSERR_EOPEN ||
					retry_counter >= MAX_CMD_RETRIES) {
				FCS_LOG_ERR("xflattest returned error (%d)\n",
						rsp->result);
				goto error;
			}

			usleep(500000);
		} while (retry_counter++ < MAX_CMD_RETRIES);

		memcpy((void *) (data + i * rsp->payload_len),
				(void *) (rsp + 1), rsp->payload_len);
	}

error:
	TEEC_ReleaseSharedMemory(&sharedMemIn);
	TEEC_ReleaseSharedMemory(&sharedMemOut);

exit:
	if (session_opened)
		TEEC_CloseSession(session);
	if (context_opened)
		TEEC_FinalizeContext(context);
	if (session)
		free(session);
	if (context)
		free(context);
	if (cmd)
		free(cmd);
	if (rsp)
		free(rsp);

	if (result != TEEC_SUCCESS) {
		FCS_LOG_ERR("failed to read xfl sec data\n");
		res = -FCSERR_ENOENT;
	}

	return res;
}
