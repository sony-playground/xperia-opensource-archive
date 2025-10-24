/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_TA_INTERFACE_H_
#define INTEGRATION_TA_INTERFACE_H_

#include "ta_interface.h"

struct integration_ta_interface_context;

struct integration_ta_interface_func {
	int (*init)(
		struct integration_ta_interface_context *context);
	int (*get_unit_size)(
		struct integration_ta_interface_context *context,
		uint8_t partition,
		uint32_t unit,
		int *unit_size);
	int (*read_unit)(
		struct integration_ta_interface_context *context,
		uint8_t partition,
		uint32_t unit,
		uint8_t *buf,
		int buf_size);
};

struct integration_ta_interface_context {
	struct integration_ta_interface_func *functions;
};

extern struct integration_ta_interface_context
	*g_integration_ta_interface_context_ptr;

#endif

