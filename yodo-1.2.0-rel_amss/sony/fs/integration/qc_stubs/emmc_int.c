/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "storage_int.h"
#include "fcserr.h"
#include "emmc_int.h"

/*
 * implements storage_set_bootdevice
 */
int storage_emmc_set_bootdevice(struct storage_ctx *ctx, int index)
{
	(void) ctx;
	(void) index;
	return FCSERR_OK;
}
