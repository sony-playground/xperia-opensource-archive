/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef GEN_TESTS_H_
#define GEN_TESTS_H_

#include "iterator.h"
#include "fcserr.h"

extern int execute_module_xmodem_normal_setup(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int setup_modules(struct iterator_info *it);

#endif

