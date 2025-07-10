/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "integration_main.h"
#include "integration_eroot.h"
#include "fcserr.h"
#include <stddef.h>
#include <stdio.h>

struct integration_eroot_context *g_integration_eroot_context_ptr = { NULL };

/* Implemented function from eroot.h */
int get_embedded_roots(
	struct embed_rootcert_item **embed_rootcert_list,
	size_t *embed_rootcert_list_count)
{
	struct integration_eroot_context *context =
		g_integration_eroot_context_ptr;
	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->get != NULL)) {
		return context->functions->get(context,
				embed_rootcert_list,
				embed_rootcert_list_count);
	} else {
		return -FCSERR_EINVAL;
	}
}

void free_embedded_roots(struct embed_rootcert_item **rootcert_list)
{
	struct integration_eroot_context *context =
		g_integration_eroot_context_ptr;
	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->free != NULL)) {
		context->functions->free(context,
				rootcert_list);
	} else {
		printf("Not handled!\n");
	}
}

