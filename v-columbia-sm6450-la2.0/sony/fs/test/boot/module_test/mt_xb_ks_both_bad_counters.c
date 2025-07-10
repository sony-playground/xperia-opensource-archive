/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 * Description:
 * When both xflkeystore and xflkeystorebak have counters
 * smaller than the RPMB counter, there is no
 * valid keystore on boot-up, and the phone shuts down.
 *
 * Setup:
 * 1. xflkeystore and xflkeystorebak have counter < rpmb_counter.
 *
 * Execution:
 * 1. On boot-up, the keystore validation fails and the phone shuts down.
 */

#include "iterator.h"
#include "integration_main.h"
#include "integration_nv.h"
#include "xboot_glue.h"
#include "xboot_pal_types.h"
#include "mt_xb_common.h"
#include "mt_xb_valid_data.h"

static int module_setup_hwstate(fcsmt_log_t log)
{
	/* Prepare hardware state */
	struct integration_hwstate state = {
		.startup_flags = XBPAL_STARTUP_MASK_ONKEY,
		.wb_reason = XBPAL_WB_NONE,
		.reset_detect = 0,
		.usb_vbus_detect = 0,
		.usb_otg_detect = 0,
		.pwr_button_pressed_time = 1500,
		.vldwn_button_pressed_time = 0,
		.vlup_button_pressed_time = 0
	};

	return integration_prepare_hwstate(&state);
}

int execute_module_xboot_ks_both_bad_counters(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match)
{
	int res = FCSERR_OK;
	struct xboot_ctx *ctx = NULL;

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

		/* If unexpected shutdown, goto MT_XB_UNEXPECTED_SHUTDOWN */
		set_next_module_item(it, MT_XB_UNEXPECTED_SHUTDOWN);
		export_tcstate(it);

		res = module_setup_normal(log);
		if (res != FCSERR_OK) {
			log("Module setup failed\n");
			return res;
		}

		/* Set KS counter in RPMB to 5 */
		res = integration_set_property(INTG_PROP_SD_KS_COUNT,
			&sec_data_keystore_counter5,
			sizeof(sec_data_keystore_counter5));
		if (res != FCSERR_OK) {
			log("Set keystore counter failed with %d\n", res);
			return res;
		}

		/***************************************
		 * Execute test
		 ***************************************/

		/* In this test, no valid keystore will be found */
		res = xboot_init(&ctx);
		if (res != FCSERR_OK) {
			log("xboot_init failed with %d\n", res);
			goto test_failure;
		}

		/* Shutdown is expected */
		set_next_module_item(it, MT_XB_EXPECTED_SHUTDOWN);
		export_tcstate(it);

		res = xboot_make_decisions(ctx);
		if (res != FCSERR_OK) {
			log("xboot_make_decisions failed with %d\n", res);
			goto test_failure;
		}

		/* Should not come here */
		goto test_failure;

	case MT_XB_UNEXPECTED_SHUTDOWN:
		/* Unexpected shutdown/restart */
		goto test_failure;

	case MT_XB_EXPECTED_SHUTDOWN:
		/* We got through the test */
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
	inc_n_failed(it);
	inc_n_executed(it);
	return FCSERR_OK;
}
