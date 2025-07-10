/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "integration_ta_interface.h"
#include <stdlib.h>

struct integration_ta_interface_context
	*g_integration_ta_interface_context_ptr = { NULL };

/* Implemented function from ta_interface.h */
int ta_init(void)
{
	struct integration_ta_interface_context *context =
		g_integration_ta_interface_context_ptr;

	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->init != NULL)) {
		return context->functions->init(context);
	} else {
		return -FCSERR_ENIMP;
	}
}

int get_ta_unit_size(uint8_t partition, uint32_t unit, int *unit_size)
{
	struct integration_ta_interface_context *context =
		g_integration_ta_interface_context_ptr;

	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->get_unit_size != NULL)) {
		return context->functions->get_unit_size(context,
			partition, unit, unit_size);
	} else {
		return -FCSERR_ENIMP;
	}
}

int read_ta(uint8_t partition, uint32_t unit, uint8_t *buf, int buf_size)
{
	struct integration_ta_interface_context *context =
		g_integration_ta_interface_context_ptr;

	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->read_unit != NULL)) {
		return context->functions->read_unit(context,
			partition, unit, buf, buf_size);
	} else {
		return -FCSERR_ENIMP;
	}
}

