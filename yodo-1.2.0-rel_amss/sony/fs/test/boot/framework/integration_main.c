/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "integration_main.h"
#include "fcserr.h"
#include <stddef.h>

struct integration_context *g_integration_context_ptr = NULL;

int integration_set_property(
		unsigned int id,
		const void *value,
		unsigned int value_len)
{
	struct integration_context *context = g_integration_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->set_property)) {
		return context->functions->set_property(
				context, id, value, value_len);
	} else {
		return -FCSERR_ENIMP;
	}
}

int integration_clear_property(
		unsigned int id)
{
	struct integration_context *context = g_integration_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->clear_property)) {
		return context->functions->clear_property(context, id);
	} else {
		return -FCSERR_ENIMP;
	}
}

int integration_is_equal_property(
		unsigned int id,
		const void *value,
		unsigned int value_len)
{
	struct integration_context *context = g_integration_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->is_equal_property)) {
		return context->functions->is_equal_property(
					context, id, value, value_len);
	} else {
		return -FCSERR_ENIMP;
	}
}

int integration_prepare_hwstate(
		struct integration_hwstate *state)
{
	struct integration_context *context = g_integration_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->prepare_hwstate)) {
		return context->functions->prepare_hwstate(context, state);
	} else {
		return -FCSERR_ENIMP;
	}
}

