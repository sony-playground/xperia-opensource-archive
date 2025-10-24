/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_CORE_H_
#define INTEGRATION_CORE_H_

#include "core.h"

struct integration_core_context;

struct integration_core_func {
	int (*is_fused)(
		struct integration_core_context *context,
		bool *is_fused);
	int (*get_dieid)(
		struct integration_core_context *context,
		unsigned char *buf, unsigned int len);
	int (*get_dieid_len)(
		struct integration_core_context *context);
	int (*is_test_cert_allowed)(
		struct integration_core_context *context);
};

struct integration_core_context {
	struct integration_core_func *functions;
};

extern struct integration_core_context *g_integration_core_context_ptr;

#endif
