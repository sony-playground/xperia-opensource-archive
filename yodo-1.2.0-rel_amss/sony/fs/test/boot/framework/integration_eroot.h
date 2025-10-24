/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_EROOT_H_
#define INTEGRATION_EROOT_H_

#include "xboot_pal_include.h"

struct integration_eroot_context;

struct integration_eroot_func {
	int (*get)(
		struct integration_eroot_context *context,
		struct embed_rootcert_item **embed_rootcert_list,
		size_t *embed_rootcert_list_count);
	void (*free)(
		struct integration_eroot_context *context,
		struct embed_rootcert_item **rootcert_list);
};

struct integration_eroot_context {
	struct integration_eroot_func *functions;
};

extern struct integration_eroot_context *g_integration_eroot_context_ptr;

#endif
