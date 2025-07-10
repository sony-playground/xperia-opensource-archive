/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 *  Stubs for early bringup
 *
 */

#include "qsee.h"

#include "fcserr.h"
#include "fcslog.h"


/*
 *  Stubs for early bringup
 *
 */
/*
 * Start fuse tz app with a len size buffer for request and response data
 */
struct qsee_handle *qsee_start_app(char *name, size_t len)
{
	(void)(name);
	(void)(len);

	FCS_LOG_ERR("%s (stubbed)\n",  __func__);
	return (struct qsee_handle *)NULL;
}

/*
 * Stop tz app
 */
int qsee_stop_app(struct qsee_handle *handle)
{
	(void)(handle); /* Unused parameter */

	FCS_LOG_ERR("%s (stubbed)\n",  __func__);
	/* QSEE apps should never be stopped due to the data will be unloaded */

	return FCSERR_OK;
}

int qsee_execute_cmd(
	struct qsee_handle *handle,
	void *req, size_t req_len, void *res, size_t res_len)
{
	(void)(handle);
	(void)(req);
	(void)(req_len);
	(void)(res);
	(void)(res_len);

	FCS_LOG_ERR("%s (stubbed)\n",  __func__);

	return FCSERR_OK;
}

int qsee_start_qseecomd(void)
{
	FCS_LOG_ERR("%s (stubbed)\n",  __func__);
	return FCSERR_OK;
}

int qsee_stop_qseecomd(void)
{
	FCS_LOG_ERR("%s (stubbed)\n",  __func__);
	return FCSERR_OK;
}
