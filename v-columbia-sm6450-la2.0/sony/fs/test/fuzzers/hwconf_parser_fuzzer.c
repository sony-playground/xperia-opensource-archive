/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdlib.h>
#include <stdint.h>

#include "hwconf_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
	hwconf_handle_t handle;

	if (hwconf_parser_init((uint8_t *) Data, Size, &handle) >= 0)
		hwconf_parser_deinit(handle);

	return 0;
}
