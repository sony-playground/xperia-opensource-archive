/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "iterator.h"
#include "fcserr.h"
#include "gen_tests.h"

int setup_modules(struct iterator_info *it)
{
	if (add_module(it, "xboot-normal-setup:",
			execute_module_xboot_normal_setup))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-delay-normal-setup:",
			execute_module_xboot_delay_normal_setup))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-short-press:",
			execute_module_xboot_short_press))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-xfl:",
			execute_module_xboot_xfl))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-factmode-xfl:",
			execute_module_xboot_factmode_xfl))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-charger:",
			execute_module_xboot_charger))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-qcfb:",
			execute_module_xboot_qcfb))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-freset:",
			execute_module_xboot_force_reset))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-fshutdown:",
			execute_module_xboot_force_shutdown))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-watchdog:",
			execute_module_xboot_watchdog))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-empty-ks-usb-no:",
			execute_module_xboot_empty_ks_usb_no))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-empty-ks-usb-yes:",
			execute_module_xboot_empty_ks_usb_yes))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-empty-hwc-usb-no:",
			execute_module_xboot_empty_hwc_usb_no))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-empty-hwc-usb-yes:",
			execute_module_xboot_empty_hwc_usb_yes))
		return -FCSERR_ENOMEM;
	return FCSERR_OK;
}
