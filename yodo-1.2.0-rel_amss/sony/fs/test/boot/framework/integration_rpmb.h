/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_RPMB_H_
#define INTEGRATION_RPMB_H_

#include "xboot_pal_include.h"

struct integration_rpmb_context;

/* typedef functions rpmbio.h */
struct integration_rpmb_func {
	int (*read)(
		struct integration_rpmb_context *context,
		ks_io_state_t *state,
		uint8_t *data,
		uint32_t *data_sz);
	int (*write)(
		struct integration_rpmb_context *context,
		ks_io_state_t *state,
		uint8_t *data,
		uint32_t data_sz);
};

struct integration_rpmb_context {
	struct integration_rpmb_func *functions;
};

extern struct integration_rpmb_context *g_integration_rpmb_context_ptr;

#endif
