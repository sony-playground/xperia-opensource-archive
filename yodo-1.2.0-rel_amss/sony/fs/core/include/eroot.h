/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef ROOT_H_
#define ROOT_H_

#include <stdlib.h>
#include <rule_types.h>

/* Retrieve embedded root certificates
   for current security state */
int get_embedded_roots(
	struct embed_rootcert_item **embed_rootcert_list,
	size_t *embed_rootcert_list_count);

void free_embedded_roots(struct embed_rootcert_item **rootcert_list);

#endif
