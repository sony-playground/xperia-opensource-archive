/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 * Description:
 * When xflkeystorebak is invalid, XCS flag in RPMB is set, and
 * a Sony keystore with counter higher than the RPMB counter is flashed into
 * xflkeystore, there is no valid keystore on boot-up, and the phone shuts down.
 *
 * Setup:
 * 1. xflkeystorebak is invalid.
 * 2. XCS flag in RPMB is set.
 * 3. xflkeystore is non-XCS with counter > rpmb_counter.
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
#include "mt_xb_wrong_data.h"

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

int execute_module_xboot_ks_invalid_bak_xcs_set_higher_counter(
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

		/* Set backup keystore bound to wrong IMEI */
		res = integration_set_property(INTG_PROP_KS_BAK,
			keystore_wrong_imei, keystore_wrong_imei_len);
		if (res != FCSERR_OK) {
			log("Set backup keystore failed with %d\n", res);
			return res;
		}

		/* Set XCS rot in RPMB to true */
		res = integration_set_property(INTG_PROP_SD_KS_XCS,
			&const_dut_sec_data_ks_xcs_xcs_rot,
			sizeof(const_dut_sec_data_ks_xcs_xcs_rot));
		if (res != FCSERR_OK) {
			log("Set XCS rot failed with %d\n", res);
			return res;
		}

		/* Set KS counter in RPMB */
		res = integration_set_property(INTG_PROP_SD_KS_COUNT,
			&const_dut_sec_data_ks_xcs_counter,
			sizeof(const_dut_sec_data_ks_xcs_counter));
		if (res != FCSERR_OK) {
			log("Set keystore counter failed with %d\n", res);
			return res;
		}

		/* Set keystore hash in RPMB */
		res = integration_set_property(INTG_PROP_SD_KS_HASH,
			const_dut_sec_data_ks_xcs_hash,
			sizeof(const_dut_sec_data_ks_xcs_hash));
		if (res != FCSERR_OK) {
			log("Set keystore hash failed with %d\n", res);
			return res;
		}

		/*
		 * Set primary keystore to a normal Sony keystore,
		 * with counter higher than the RPMB counter.
		 */
		res = integration_set_property(INTG_PROP_KS,
			keystore_counter5, keystore_counter5_len);
		if (res != FCSERR_OK) {
			log("Set primary keystore failed with %d\n", res);
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

		res = integration_is_equal_property(
			INTG_PROP_SD_KS_COUNT,
			&const_dut_sec_data_ks_xcs_counter,
			sizeof(const_dut_sec_data_ks_xcs_counter));
		if (res != FCSERR_OK) {
			log("Check RPMB ks counter failed with %d\n",
				res);
			goto test_failure;
		}

		/* Check that the backup keystore has not changed */
		res = integration_is_equal_property(INTG_PROP_KS_BAK,
			&keystore_wrong_imei,
			keystore_wrong_imei_len);
		if (res != FCSERR_OK) {
			log("Check backup keystore failed with %d\n", res);
			goto test_failure;
		}

		/* Check that the primary keystore has not changed */
		res = integration_is_equal_property(INTG_PROP_KS,
			&keystore_counter5,
			keystore_counter5_len);
		if (res != FCSERR_OK) {
			log("Check primary keystore failed with %d\n", res);
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
