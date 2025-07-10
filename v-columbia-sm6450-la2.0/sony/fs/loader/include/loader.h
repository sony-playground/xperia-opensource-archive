/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_LOADER_H_
#define FCS_LOADER_H_

#include <stdint.h>

struct loader_ctx {
	/* transport handle */
	struct protocol *prot_hdl;

	/* List with handlers for security properties*/
	struct list_entry *sec_prop_list;

	/* authentication level set by the current device security level
	 * or by the SAKE authentication cmd
	 */
	uint8_t auth_level;

	/* SSN specifies authentication level */
	uint16_t ssn;
};


int loader_main(struct loader_ctx *ctx);

#endif
