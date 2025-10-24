/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "integration_nv.h"
#include "fcserr.h"

struct integration_nv_context *g_integration_nv_context_ptr = NULL;

/* Implemented function from nvio.h */
int plf_nv_read_cb(
	ks_io_state_t *state, uint8_t *data, uint32_t *data_sz)
{
	struct integration_nv_context *context =
		g_integration_nv_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->read)) {
		return context->functions->read(context,
						state,
						data,
						data_sz);
	} else {
		return -FCSERR_EINVAL;
	}
}

int plf_nv_write_cb(
	ks_io_state_t *state, uint8_t *data, const uint32_t data_sz)
{
	struct integration_nv_context *context =
		g_integration_nv_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->write)) {
		return context->functions->write(context,
						state,
						data,
						data_sz);
	} else {
		return -FCSERR_EINVAL;
	}
}
