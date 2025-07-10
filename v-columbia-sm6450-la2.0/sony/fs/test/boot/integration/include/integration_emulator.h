/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_EMULATOR_H_
#define INTEGRATION_EMULATOR_H_

#include "iterator.h"
#include "integration_main.h"

extern const struct integration_eroot_func intemul_eroot_func;

int integration_emulator_setup(
		void (*log)(const char *fmt, ...),
		struct iterator_info *it,
		struct integration_hwstate *state,
		void (*export_hwstate)(
			struct integration_hwstate *state));
void integration_emulator_teardown(void);

#endif
