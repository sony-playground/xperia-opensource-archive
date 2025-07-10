/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 * Description:
 * If the SIMLock in MiscTA does not allow unlocking of the bootloader,
 * a newly flashed valid XCS keystore will not be applied.
 *
 * Setup:
 * 1. SIMLock which does not allow bootloader unlock in MiscTA.
 * 2. Valid Sony keystore in xflkeystorebak.
 * 3. Valid XCS keystore in xflkeystore bound to HMAC of IMEI.
 * 4. Valid HMAC key in MiscTA unit 2164.
 * 5. XCS flag in RPMB is not set.
 *
 * Execution:
 * 1. On boot-up, the xflkeystore validation will fail and the keystore
 *    will be reverted, i.e. the data from xflkeystorebak will be copied
 *    to xflkeystore.
 * 2. The XCS flag in RPMB will not be set.
 * 3. The RPMB ks counter will not be changed.
 * 4. MiscTA unit 66673 is empty.
 * 5. The phone will boot-up successfully.
 */

#include "iterator.h"
#include "integration_main.h"
#include "integration_nv.h"
#include "xboot_glue.h"
#include "xboot_pal_types.h"
#include "ta_interface.h"
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

int execute_module_xboot_ks_xcs_sl_not_rootable(
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

		/* Check that the primary keystore is the correct one */
		res = integration_is_equal_property(INTG_PROP_KS,
			&const_dut_ks_valid_imei,
			const_dut_ks_valid_imei_len);
		if (res != FCSERR_OK) {
			log("Check primary keystore failed with %d\n", res);
			goto test_failure;
		}

		/* Check that the backup keystore is the correct one */
		res = integration_is_equal_property(INTG_PROP_KS_BAK,
			&const_dut_ks_valid_imei,
			const_dut_ks_valid_imei_len);
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

		/* Boot normally */
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
		if (cert_count != ks_bound_to_hmac_valid_n_normal_cert) {
			log("Unexpected cert_count %d\n", cert_count);
			goto test_failure;
		}

		/* Check certs */
		for (i = 0; i < ks_bound_to_hmac_valid_n_normal_cert; i++) {
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
