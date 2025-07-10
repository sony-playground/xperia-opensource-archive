/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "qsee.h"

#include "fcs_prop.h"
#include "fcserr.h"
#include "fcslog.h"
#include "fcsenv_def.h"
#include <cutils/properties.h>
#include <unistd.h>
#include <string.h>

#include "QSEEComAPI.h"


#define SLEEP_TIME_USEC 50000
#define QSEECOMD_WAIT_RETRY 60

/*
 * Start fuse tz app with a len size buffer for request and response data
 */
struct qsee_handle *qsee_start_app(char *name, size_t len)
{
	int32_t result = 0;
	struct QSEECom_handle *handle = NULL;

	if (!name) {
		FCS_LOG_ERR("Invalid input\n");
		return NULL;
	}

	FCS_LOG_INF("Starting TZ-app %s\n", name);
	result = QSEECom_start_app(
		&handle, "/etc/firmware", name, QSEECOM_ALIGN(len));

	if (result) {
		FCS_LOG_ERR("Failed to start %s tz app. (%d)\n", name, result);
		return NULL;
	}

	return (struct qsee_handle *)handle;
}

/*
 * Stop tz app
 */
int qsee_stop_app(struct qsee_handle *handle)
{
	(void)(handle); /* Unused parameter */

	FCS_LOG_INF("Stopping TZ-app (stubbed)\n");
	/* QSEE apps should never be stopped due to the data will be unloaded */

	return FCSERR_OK;
}

int qsee_execute_cmd(
	struct qsee_handle *handle,
	void *req, size_t req_len, void *res, size_t res_len)
{
	int32_t request_len = req_len;
	int32_t response_len = res_len;
	int32_t result;
	struct QSEECom_handle *hdl = (struct QSEECom_handle *)handle;
	void *ion_cmd = hdl->ion_sbuffer;
	void *ion_rsp = NULL;

	memcpy(hdl->ion_sbuffer, req, req_len);

	if (request_len & QSEECOM_ALIGN_MASK)
		request_len = QSEECOM_ALIGN(request_len);

	if (response_len & QSEECOM_ALIGN_MASK)
		response_len = QSEECOM_ALIGN(response_len);

	/*Copy in rsp cmd and rsp_msg to handle*/
	ion_rsp = (void *)(hdl->ion_sbuffer + request_len);
	memcpy(ion_rsp, res, res_len);

	/* send to secure side */
	result = QSEECom_send_cmd(
		hdl, ion_cmd, request_len,
		ion_rsp, response_len);

	memcpy(res, ion_rsp, res_len);

	if (result) {
		FCS_LOG_ERR("Failed to execute cmd (%08x)\n", result);
		return -FCSERR_EIO;
	}

	return FCSERR_OK;
}

int qsee_start_qseecomd(void)
{
	int res;
	int registered = 0;
	int retry = 0;

	res = fcs_prop_set(FCS_PROP_START_QSEECOMD);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("fcs_prop_set failed (%d)\n", res);
		return res;
	}

	/* Wait for qseecomd to be started.
	 * When qseecomd is started it will set
	 * QSEE_LISTENER_PROP property to true.
	 */
	do {
		registered = property_get_bool(
				QSEE_LISTENER_PROP, false);

		if (registered != 0)
			break;

		usleep(SLEEP_TIME_USEC);

		if (retry > QSEECOMD_WAIT_RETRY) {
			FCS_LOG_ERR("Failed to start qseecomd\n");
			res = -FCSERR_EIO;
		}
		retry++;
	} while (1);

	return res;
}

int qsee_stop_qseecomd(void)
{
	int res;

	res = fcs_prop_set(FCS_PROP_STOP_QSEECOMD);

	if (res != FCSERR_OK)
		FCS_LOG_ERR("Failed to stop qseecomd(%d)\n", res);
	else
		/* Set QSEE_LISTENER_PROP property to false.
		 * This indicates that qseecomd is not started.
		 */
		res = property_set(QSEE_LISTENER_PROP, false);

	return res;
}
