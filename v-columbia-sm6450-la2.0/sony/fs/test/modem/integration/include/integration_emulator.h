/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_EMULATOR_H_
#define INTEGRATION_EMULATOR_H_

#include "iterator.h"
#include "integration_main.h"

extern const struct integration_eroot_func intemul_eroot_func;

int integration_emulator_setup(
		void (*log)(const char *fmt, ...),
		struct iterator_info *it);
void integration_emulator_teardown(void);

#endif
