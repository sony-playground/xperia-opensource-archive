/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_EROOT_H_
#define INTEGRATION_EROOT_H_

#include "eroot.h"

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
