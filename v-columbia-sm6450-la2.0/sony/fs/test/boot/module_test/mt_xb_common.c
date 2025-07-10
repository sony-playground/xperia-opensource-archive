/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <string.h>
#include "iterator.h"
#include "mt_xb_common.h"
#include "integration_main.h"
#include "xboot_glue.h"
#include "xboot_pal_types.h"
#include "xflattest.h"

int module_setup_normal(fcsmt_log_t log)
{
	int res = FCSERR_OK;

	res = integration_set_property(
		INTG_PROP_FUSED,
		&const_dut_fuse,
		const_dut_fuse_len);
	if (res != FCSERR_OK) {
		log("set is_fused failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_DEV_ID,
		const_dut_dev_id,
		const_dut_dev_id_len);
	if (res != FCSERR_OK) {
		log("set dev_id failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_HWCONFIG,
		const_dut_hwconfig,
		const_dut_hwconfig_len);
	if (res != FCSERR_OK) {
		log("set hwconfig failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_MISCTA_DK,
		const_dut_miscta_dk,
		const_dut_miscta_dk_len);
	if (res != FCSERR_OK) {
		log("set misc ta DK failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_KS,
		const_dut_ks_valid_imei,
		const_dut_ks_valid_imei_len);
	if (res != FCSERR_OK) {
		log("set org keystore failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_KS_BAK,
		const_dut_ks_valid_imei,
		const_dut_ks_valid_imei_len);
	if (res != FCSERR_OK) {
		log("set bak keystore failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_SD_VERSION,
		&const_dut_sec_data_version,
		sizeof(const_dut_sec_data_version));
	if (res != FCSERR_OK) {
		log("set secdata version failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_SD_UNLOCK,
		&const_dut_sec_data_unlock,
		sizeof(const_dut_sec_data_unlock));
	if (res != FCSERR_OK) {
		log("set secdata unlock failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_SD_KS_COUNT,
		&const_dut_sec_data_ks_counter,
		sizeof(const_dut_sec_data_ks_counter));
	if (res != FCSERR_OK) {
		log("set secdata ks counter failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_SD_KS_XCS,
		&const_dut_sec_data_ks_xcs_rot,
		sizeof(const_dut_sec_data_ks_xcs_rot));
	if (res != FCSERR_OK) {
		log("set secdata ks xcs root failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_SD_KS_HASH,
		&const_dut_sec_data_ks_hash,
		sizeof(const_dut_sec_data_ks_hash));
	if (res != FCSERR_OK) {
		log("set secdata ks hash failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_SD_NONCE,
		&const_dut_sec_data_sake_nonce,
		sizeof(const_dut_sec_data_sake_nonce));
	if (res != FCSERR_OK) {
		log("set secdata nonce failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_SD_VBM_RB,
		&const_dut_sec_data_rollback_counter,
		sizeof(const_dut_sec_data_rollback_counter));
	if (res != FCSERR_OK) {
		log("set secdata vbm rb failed with %d\n", res);
		return res;
	}
	res = integration_clear_property(
		INTG_PROP_COUNTERS);
	if (res != FCSERR_OK) {
		log("clear counters failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_SW_VERSION,
		const_dut_boot_version,
		const_dut_boot_version_len);
	if (res != FCSERR_OK) {
		log("set sw boot version failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_TA_VERSION,
		const_dut_boot_version,
		const_dut_boot_version_len);
	if (res != FCSERR_OK) {
		log("set TA boot version failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_BOOT_CONFIG,
		const_dut_boot_config,
		const_dut_boot_config_len);
	if (res != FCSERR_OK) {
		log("Set boot config failed with %d\n", res);
		return res;
	}
	res = integration_clear_property(
		INTG_PROP_FACTORY_MODE);
	if (res != FCSERR_OK) {
		log("clear factory_mode failed with %d\n", res);
		return res;
	}
	res = integration_clear_property(
		INTG_PROP_RESET_FRP);
	if (res != FCSERR_OK) {
		log("clear reset_frp failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_LED,
		&const_led_off,
		sizeof(const_led_off));
	if (res != FCSERR_OK) {
		log("set led failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_SL_SIGNATURE,
		const_dut_sl_signature,
		const_dut_sl_signature_len);
	if (res != FCSERR_OK) {
		log("Set boot config failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_SL_DATA,
		const_dut_sl_data,
		const_dut_sl_data_len);
	if (res != FCSERR_OK) {
		log("Set boot config failed with %d\n", res);
		return res;
	}
	return FCSERR_OK;
}

int check_cmdline(char *cmdline, fcsmt_log_t log)
{
	int i;

	if (cmdline == NULL) {
		log("No command line additions\n");
		return -FCSERR_ENOTF;
	}

	/* Check the existence of the command line arguments */
	for (i = 0; i < nr_of_cmdline_args; i++) {
		if (!strstr(cmdline, cmdline_args[i])) {
			log("Command line argument %s is missing\n",
				cmdline_args[i]);
			return -FCSERR_ENOTF;
		}
	}
	return FCSERR_OK;
}
