/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "integration_main.h"
#include "integration_core.h"
#include "fcserr.h"
#include <stdbool.h>

struct integration_core_context *g_integration_core_context_ptr = NULL;

/* Implemented function from core.h */
int core_is_fused(bool *is_fused)
{
	struct integration_core_context *context =
		g_integration_core_context_ptr;
	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->is_fused)) {
		return context->functions->is_fused(context, is_fused);
	} else {
		return -FCSERR_EINVAL;
	}
}

int core_get_dieid(unsigned char *buf, unsigned int len)
{
	struct integration_core_context *context =
		g_integration_core_context_ptr;
	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->get_dieid)) {
		return context->functions->get_dieid(context, buf, len);
	} else {
		return -FCSERR_EINVAL;
	}
}

int core_get_dieid_len(void)
{
	struct integration_core_context *context =
		g_integration_core_context_ptr;
	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->get_dieid_len)) {
		return context->functions->get_dieid_len(context);
	} else {
		return -FCSERR_EINVAL;
	}
}

int core_is_test_cert_allowed(void)
{
	struct integration_core_context *context =
		g_integration_core_context_ptr;
	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->is_test_cert_allowed != NULL)) {
		return context->functions->is_test_cert_allowed(context);
	} else {
		return 0;
	}
}

