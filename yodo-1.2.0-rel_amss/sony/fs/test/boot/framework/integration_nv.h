/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_NV_H_
#define INTEGRATION_NV_H_

#include "xboot_pal_include.h"

struct integration_nv_context;

struct integration_nv_func {
	int (*read)(
		struct integration_nv_context *context,
		ks_io_state_t *state,
		uint8_t *data,
		uint32_t *data_sz);
	int (*write)(
		struct integration_nv_context *context,
		ks_io_state_t *state,
		uint8_t *data,
		const uint32_t data_sz);
};

struct integration_nv_context {
	struct integration_nv_func *functions;
};

extern struct integration_nv_context *g_integration_nv_context_ptr;

#endif
