/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef QSEE_H_
#define QSEE_H_

#include <stddef.h>

struct qsee_handle;

struct qsee_handle *qsee_start_app(char *name, size_t len);

int qsee_stop_app(struct qsee_handle *handle);

int qsee_execute_cmd(
	struct qsee_handle *handle,
	void *req, size_t req_len, void *res, size_t res_len);

int qsee_start_qseecomd(void);

int qsee_stop_qseecomd(void);

#endif
