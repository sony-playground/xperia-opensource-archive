/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/* Implemented functions from xflattest_int.h */

#include "integration_xflattest.h"
#include "fcserr.h"
#include "fcslog.h"
#include <stdio.h>

struct integration_xflattest_context *g_integration_xflattest_context_ptr =
					NULL;

/* Implemented function from xflattest_int.h */
int read_xfl_sec_data(struct xfl_sec_data *data)
{
	struct integration_xflattest_context *context =
		g_integration_xflattest_context_ptr;

	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->read != NULL))
		return context->functions->read(context, data);

	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}

int write_xfl_sec_data(struct xfl_sec_data *data)
{
	struct integration_xflattest_context *context =
		g_integration_xflattest_context_ptr;

	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->write != NULL))
		return context->functions->write(context, data);

	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}
