/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_UEFI_H_
#define INTEGRATION_UEFI_H_

#include "iterator.h"
#include "integration_main.h"

int integration_uefi_setup(
		void (*log)(const char *fmt, ...),
		struct iterator_info *it,
		void (*export_hwstate)(
			struct integration_hwstate *state));
void integration_uefi_teardown(void);

#endif
