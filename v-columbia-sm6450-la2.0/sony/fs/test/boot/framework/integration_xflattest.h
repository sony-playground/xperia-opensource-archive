/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_XFLATTEST_H_
#define INTEGRATION_XFLATTEST_H_

#include <stdint.h>
#include "xflattest_int.h"

struct integration_xflattest_context;

struct integration_xflattest_func {
	int (*read)(
		struct integration_xflattest_context *context,
		struct xfl_sec_data *data);
	int (*write)(
		struct integration_xflattest_context *context,
		struct xfl_sec_data *data);
};

struct integration_xflattest_context {
	struct integration_xflattest_func *functions;
};

extern struct integration_xflattest_context
	*g_integration_xflattest_context_ptr;

#endif

