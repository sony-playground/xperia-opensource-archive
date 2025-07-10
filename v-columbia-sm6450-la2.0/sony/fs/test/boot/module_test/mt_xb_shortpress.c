/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "iterator.h"
#include "integration_main.h"
#include "xboot_glue.h"
#include "xboot_pal_types.h"
#include "mt_xb_common.h"

static int module_setup_hwstate(fcsmt_log_t log)
{
	/* Prepare hardware state */
	struct integration_hwstate state = {
		.startup_flags = XBPAL_STARTUP_MASK_ONKEY,
		.wb_reason = XBPAL_WB_NONE,
		.reset_detect = 0,
		.usb_vbus_detect = 0,
		.usb_otg_detect = 0,
		.pwr_button_pressed_time = 400,
		.vldwn_button_pressed_time = 0,
		.vlup_button_pressed_time = 0
	};

	return integration_prepare_hwstate(&state);
}

int execute_module_xboot_short_press(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match)
{
	int res = FCSERR_OK;
	struct xboot_ctx *ctx = NULL;
	unsigned int boot_mode = XBOOT_BOOT_INVALID_MODE;
	char *cmdline_additions = NULL;

	switch (it->cur_module_item) {
	case MT_XB_REQ_HWSTATE:
		set_next_module_item(it, MT_XB_EXECUTE);
		/* Must export - integration might shutdown/restart device */
		export_tcstate(it);

		res = module_setup_hwstate(log);
		if (res != FCSERR_OK) {
			log("Setup hardware state failed with %d\n", res);
			return res;
		}
		break;

	case MT_XB_EXECUTE:
		/***************************************
		 * Setup test
		 ***************************************/

		/* If expected shutdown, goto MT_XB_EXPECTED_SHUTDOWN */
		set_next_module_item(it, MT_XB_EXPECTED_SHUTDOWN);
		export_tcstate(it);

		res = module_setup_normal(log);
		if (res != FCSERR_OK) {
			log("Module setup failed\n");
			return res;
		}

		/***************************************
		 * Execute test
		 ***************************************/

		res = xboot_init(&ctx);
		if (res != FCSERR_OK) {
			log("xboot_init failed with %d\n", res);
			goto test_failure;
		}

		res = xboot_make_decisions(ctx);
		if (res != FCSERR_OK) {
			log("xboot_make_decisions failed with %d\n", res);
			goto test_failure;
		}

		res = xboot_check_auto_set_oem_unlock(ctx);
		if (res != FCSERR_OK && res != -FCSERR_ENOTF) {
			log("xboot_check_auto_set_oem_unlock failed ");
			log("failed with %d\n", res);
			goto test_failure;
		}

		boot_mode = xboot_get_boot_mode(ctx);
		if (boot_mode != XBOOT_BOOT_DEFAULT_MODE) {
			log("Unexpected boot_mode: %d\n", boot_mode);
			goto test_failure;
		}

		cmdline_additions = xboot_get_cmdline_additions(ctx);
		if (check_cmdline(cmdline_additions, log) != FCSERR_OK)
			goto test_failure;

		res = xboot_finalize_longpress(ctx);
		if (res != FCSERR_OK) {
			log("xboot_finalize_longpress failed with %d\n", res);
			goto test_failure;
		}

		/* We should not come here due to short press timer */
		goto test_failure;

	case MT_XB_EXPECTED_SHUTDOWN:
		/* Expected shutdown/restart */
		inc_n_executed(it);
		set_next_module_item(it, -1);
		break;

	default:
		/* Should be impossible to end up here */
		return -FCSERR_ESTATE;
	}

	return FCSERR_OK;

test_failure:
	set_next_module_item(it, -1);
	inc_n_executed(it);
	inc_n_failed(it);
	return FCSERR_OK;
}
