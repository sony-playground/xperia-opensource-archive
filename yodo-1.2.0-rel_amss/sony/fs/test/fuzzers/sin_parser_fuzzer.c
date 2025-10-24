/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdlib.h>
#include <stdint.h>

#include "sin_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
	struct sin_header *handle;

	if (sinparser_init(&handle, (uint8_t *) Data, Size) >= 0) {
		sinparser_deinit(handle);
	};

	return 0;
}
