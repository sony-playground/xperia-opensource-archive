/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef GEN_TESTS_H_
#define GEN_TESTS_H_

#include "iterator.h"
#include "fcserr.h"

extern int execute_module_xboot_normal_setup(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

extern int execute_module_xboot_delay_normal_setup(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

extern int execute_module_xboot_short_press(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_xfl(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_factmode_xfl(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_charger(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_qcfb(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_force_reset(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_force_shutdown(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_watchdog(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_empty_ks_usb_no(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_empty_ks_usb_yes(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_empty_hwc_usb_no(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_empty_hwc_usb_yes(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int setup_modules(struct iterator_info *it);

#endif
