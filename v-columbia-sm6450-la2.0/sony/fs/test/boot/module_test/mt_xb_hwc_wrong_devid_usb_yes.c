/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "iterator.h"
#include "integration_main.h"
#include "xboot_glue.h"
#include "xboot_pal_types.h"
#include "mt_xb_common.h"
#include "mt_xb_wrong_data.h"

static int module_setup_hwstate(fcsmt_log_t log)
{
	/* Prepare hardware state */
	struct integration_hwstate state = {
		.startup_flags = XBPAL_STARTUP_MASK_VBUS,
		.wb_reason = XBPAL_WB_NONE,
		.reset_detect = 0,
		.usb_vbus_detect = 1,
		.usb_otg_detect = 0,
		.pwr_button_pressed_time = 0,
		.vldwn_button_pressed_time = 0,
		.vlup_button_pressed_time = 0
	};

	return integration_prepare_hwstate(&state);
}

int execute_module_xboot_hwc_wrong_devid_usb_yes(
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

		/* Replace HWConfig */
		res = integration_set_property(INTG_PROP_HWCONFIG,
				hwconfig_wrong_devid, hwconfig_wrong_devid_len);
		if (res != FCSERR_OK) {
			log("Set HWConfig failed with %d\n", res);
			return res;
		}

		/* Set keystores with devid binding */
		res = integration_set_property(
			INTG_PROP_KS,
			const_dut_ks_valid_devid,
			const_dut_ks_valid_devid_len);
		if (res != FCSERR_OK) {
			log("set org keystore failed with %d\n", res);
			return res;
		}
		res = integration_set_property(
			INTG_PROP_KS_BAK,
			const_dut_ks_valid_devid,
			const_dut_ks_valid_devid_len);
		if (res != FCSERR_OK) {
			log("set bak keystore failed with %d\n", res);
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
		if (res != FCSERR_OK) {
			log("xboot_check_auto_set_oem_unlock err=%d\n", res);
			goto test_failure;
		}

		/* If DevID is wrong, then we shall boot XFL */
		boot_mode = xboot_get_boot_mode(ctx);
		if (boot_mode != XBOOT_BOOT_SONY_SERVICE_MODE) {
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
			RULE_USAGE_LOADER_KERNEL, &cert_count);
		if (res != FCSERR_OK) {
			log("xboot_get_signer_cert_count failed (%d)\n", res);
			goto test_failure;
		}
		if (cert_count != const_dut_ks_valid_n_xfl_cert) {
			log("Unexpected cert_count %d\n", cert_count);
			goto test_failure;
		}

		/* Check certs */
		for (i = 0; i < const_dut_ks_valid_n_xfl_cert; i++) {
			res = xboot_get_signer_cert(ctx,
					RULE_USAGE_LOADER_KERNEL, i,
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
			&const_led_green,
			sizeof(const_led_green));
		if (res != FCSERR_OK) {
			log("is_equal check failed with %d\n", res);
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
