/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdlib.h>
#include "fcserr.h"
#include "write_image.h"

int pre_flash_handler(struct storage_ctx *sctx, const char *partition,
		uint32_t *offset)
{
	/* No custom handling needed in QC platform */
	(void) sctx;
	(void) partition;
	*offset = 0;
	return FCSERR_OK;
}

