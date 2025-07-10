/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 * Description:
 * If the SIMLock in MiscTA does not allow unlocking of the bootloader,
 * a newly flashed valid XCS keystore will not be applied. If the backup
 * keystore is also invalid, the device will not boot-up.
 *
 * Setup:
 * 1. SIMLock which does not allow bootloader unlock in MiscTA.
 * 2. Invalid Sony keystore in xflkeystorebak.
 * 3. Valid XCS keystore in xflkeystore bound to HMAC of IMEI.
 * 4. Valid HMAC key in MiscTA unit 2164.
 * 5. XCS flag in RPMB is not set.
 *
 * Execution:
 * 1. On boot-up, the xflkeystore and xflkeystorebak validation will fail.
 * 2. The XCS flag in RPMB will not be set.
 * 3. The RPMB ks counter will not be changed.
 * 4. MiscTA unit 66673 is empty.
 * 5. The phone will not boot-up successfully.
 */

#include "iterator.h"
#include "integration_main.h"
#include "integration_nv.h"
#include "xboot_glue.h"
#include "xboot_pal_types.h"
#include "ta_interface.h"
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

int execute_module_xboot_ks_xcs_sl_not_rootable_bak_invalid(
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

		/* Set a keystore that is bound to HMAC of IMEI */
		res = integration_set_property(INTG_PROP_KS,
			xcs_keystore_bound_to_hmac_imei,
			xcs_keystore_bound_to_hmac_imei_len);
		if (res != FCSERR_OK) {
			log("Set keystore failed with %d\n", res);
			return res;
		}

		/* Put a valid HMAC key to low TA */
		res = integration_set_property(TA_KEYSTORE_HMAC_KEY,
					hmac_key, hmac_key_len);
		if (res != FCSERR_OK) {
			log("Put HMAC key to low TA failed with %d\n", res);
			return res;
		}

		/* Set SIMLock which does not allow bootloader unlock */
		res = integration_set_property(
			INTG_PROP_SL_SIGNATURE,
			const_dut_sl_not_rootable_signature,
			const_dut_sl_not_rootable_signature_len);
		if (res != FCSERR_OK) {
			log("Set boot config failed with %d\n", res);
			return res;
		}
		res = integration_set_property(
			INTG_PROP_SL_DATA,
			const_dut_sl_not_rootable_data,
			const_dut_sl_not_rootable_data_len);
		if (res != FCSERR_OK) {
			log("Set boot config failed with %d\n", res);
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

		/* Check that the primary keystore has not changed */
		res = integration_is_equal_property(INTG_PROP_KS,
			&xcs_keystore_bound_to_hmac_imei,
			xcs_keystore_bound_to_hmac_imei_len);
		if (res != FCSERR_OK) {
			log("Check primary keystore failed with %d\n", res);
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

		/* Check that the HMAC key has been deleted from low TA */
		res = integration_is_equal_property(INTG_PROP_TA_HMAC_LOW,
								NULL, 0);
		if (res != FCSERR_OK) {
			log("Check HMAC key in low TA failed with %d\n", res);
			goto test_failure;
		}

		/* Check that the HMAC key has not been copied to high TA */
		res = integration_is_equal_property(INTG_PROP_TA_HMAC_HIGH,
						NULL, 0);
		if (res != FCSERR_OK) {
			log("Check HMAC key in high TA failed with %d\n", res);
			goto test_failure;
		}

		/* Check that the XCS flag in RPMB has not been set */
		res = integration_is_equal_property(
			INTG_PROP_SD_KS_XCS,
			&const_dut_sec_data_ks_xcs_rot,
			sizeof(const_dut_sec_data_ks_xcs_rot));
		if (res != FCSERR_OK) {
			log("INTG_PROP_SD_KS_XCS check failed with %d\n",
				res);
			goto test_failure;
		}

		/* Check that the ks counter in RPMB hasn't changed */
		res = integration_is_equal_property(
			INTG_PROP_SD_KS_COUNT,
			&const_dut_sec_data_ks_counter,
			sizeof(const_dut_sec_data_ks_counter));
		if (res != FCSERR_OK) {
			log("Check RPMB ks counter failed with %d\n",
				res);
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
