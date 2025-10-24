/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "iterator.h"
#include "integration_main.h"
#include "xboot_glue.h"
#include "xboot_pal_types.h"
#include "xflattest.h"
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
		.pwr_button_pressed_time = 1500,
		.vldwn_button_pressed_time = 0,
		.vlup_button_pressed_time = 0
	};

	return integration_prepare_hwstate(&state);
}

int execute_module_xboot_first_keystore(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match)
{
	int res = FCSERR_OK;
	struct xboot_ctx *ctx = NULL;
	unsigned int boot_mode = XBOOT_BOOT_INVALID_MODE;
	char *cmdline_additions = NULL;
	unsigned int cert_count = 0;
	int i;
	const unsigned char *cert = NULL;
	unsigned int cert_len = 0;
	unsigned char called_expected = 1;

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

		/* Reset secure data (RPMB) for virgin unit */
		res = integration_clear_property(INTG_PROP_SD_UNLOCK);
		if (res != FCSERR_OK) {
			log("Reset secdata unlock failed\n");
			return res;
		}

		res = integration_clear_property(INTG_PROP_SD_KS_COUNT);
		if (res != FCSERR_OK) {
			log("Reset secdata ks counter failed\n");
			return res;
		}

		res = integration_clear_property(INTG_PROP_SD_KS_XCS);
		if (res != FCSERR_OK) {
			log("Reset secdata ks xcs root failed\n");
			return res;
		}

		res = integration_clear_property(INTG_PROP_SD_KS_HASH);
		if (res != FCSERR_OK) {
			log("Reset secdata ks hash failed\n");
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
			log("xboot_check_auto_set_oem_unlock ");
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

		res = xboot_get_signer_cert_count(ctx,
			RULE_USAGE_NORMAL_KERNEL, &cert_count);
		if (res != FCSERR_OK) {
			log("xboot_get_signer_cert_count failed (%d)\n", res);
			goto test_failure;
		}
		if (cert_count != const_dut_ks_valid_n_normal_cert) {
			log("Unexpected cert_count %d\n", cert_count);
			goto test_failure;
		}

		/* Check certs */
		for (i = 0; i < const_dut_ks_valid_n_normal_cert; i++) {
			res = xboot_get_signer_cert(ctx,
				RULE_USAGE_NORMAL_KERNEL, i,
				&cert, &cert_len);
			if (res != FCSERR_OK) {
				log("xboot_get_signer_cert failed (%d)\n",
					res);
				goto test_failure;
			}
			if (cert == NULL || cert_len == 0) {
				log("Unexpected cert data\n");
				goto test_failure;
			}
		}

		res = integration_is_equal_property(INTG_PROP_LED,
			&const_led_off,
			sizeof(const_led_off));
		if (res != FCSERR_OK) {
			log("is_equal check failed with %d\n", res);
			goto test_failure;
		}

		/* RPMB should have been updated */
		res = integration_is_equal_property(INTG_PROP_CNT_WRSECDATA,
			(const void *)&called_expected,
			sizeof(called_expected));
		if (res != FCSERR_OK) {
			log("INTG_PROP_COUNTERS check failed with %d\n", res);
			goto test_failure;
		}

		/* Check RPMB values */
		res = integration_is_equal_property(
			INTG_PROP_SD_UNLOCK,
			&const_dut_sec_data_unlock,
			sizeof(const_dut_sec_data_unlock));
		if (res != FCSERR_OK) {
			log("INTG_PROP_SD_UNLOCK check failed with %d\n",
				res);
			goto test_failure;
		}
		res = integration_is_equal_property(
			INTG_PROP_SD_KS_COUNT,
			&const_dut_sec_data_ks_counter,
			sizeof(const_dut_sec_data_ks_counter));
		if (res != FCSERR_OK) {
			log("Check RPMB ks counter failed with %d\n",
				res);
			goto test_failure;
		}
		res = integration_is_equal_property(
			INTG_PROP_SD_KS_XCS,
			&const_dut_sec_data_ks_xcs_rot,
			sizeof(const_dut_sec_data_ks_xcs_rot));
		if (res != FCSERR_OK) {
			log("INTG_PROP_SD_KS_XCS check failed with %d\n",
				res);
			goto test_failure;
		}
		res = integration_is_equal_property(
			INTG_PROP_SD_KS_HASH,
			&const_dut_sec_data_ks_hash,
			sizeof(const_dut_sec_data_ks_hash));
		if (res != FCSERR_OK) {
			log("INTG_PROP_SD_KS_HASH check failed with %d\n",
				res);
			goto test_failure;
		}

		/* We got through the test, goto next test */
		inc_n_executed(it);
		set_next_module_item(it, -1);
		break;

	case MT_XB_UNEXPECTED_SHUTDOWN:
		/* Unexpected shutdown/restart */
		goto test_failure;

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
