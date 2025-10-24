/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
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
	if (add_module(it, "xboot-first-keystore:",
			execute_module_xboot_first_keystore))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-apply-xcs-keystore:",
			execute_module_xboot_apply_xcs_keystore))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-reset-arb:",
			execute_module_xboot_reset_arb))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-hwc-wrong-payload-usb-no:",
			execute_module_xboot_hwc_wrong_payload_usb_no))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-hwc-wrong-payload-usb-yes:",
			execute_module_xboot_hwc_wrong_payload_usb_yes))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-hwc-wrong-devid-usb-no:",
			execute_module_xboot_hwc_wrong_devid_usb_no))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-hwc-wrong-devid-usb-yes:",
			execute_module_xboot_hwc_wrong_devid_usb_yes))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-wrong-payload:",
			execute_module_xboot_ks_wrong_payload))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-both-wrong-payload-usb-no:",
			execute_module_xboot_ks_both_wrong_payload_usb_no))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-both-wrong-payload-usb-yes:",
			execute_module_xboot_ks_both_wrong_payload_usb_yes))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-wrong-devid:",
			execute_module_xboot_ks_wrong_devid))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-wrong-imei:",
			execute_module_xboot_ks_wrong_imei))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-both-wrong-devid-usb-no:",
			execute_module_xboot_ks_both_wrong_devid_usb_no))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-both-wrong-imei-usb-no:",
			execute_module_xboot_ks_both_wrong_imei_usb_no))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-both-wrong-devid-usb-yes:",
			execute_module_xboot_ks_both_wrong_devid_usb_yes))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-both-wrong-imei-usb-yes:",
			execute_module_xboot_ks_both_wrong_imei_usb_yes))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-insert-ks-failed-due-to-xcs:",
			execute_module_xboot_insert_ks_failed_due_to_xcs))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-insert-ks-failed-due-to-counter:",
			execute_module_xboot_insert_ks_failed_due_to_counter))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-bound-to-hmac-devid-valid-key:",
			execute_module_xboot_ks_bound_to_hmac_devid_valid_key))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-bound-to-hmac-devid-wrong-key:",
			execute_module_xboot_ks_bound_to_hmac_devid_wrong_key))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-bound-to-hmac-imei-valid-key:",
			execute_module_xboot_ks_bound_to_hmac_imei_valid_key))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-bound-to-hmac-imei-wrong-key:",
			execute_module_xboot_ks_bound_to_hmac_imei_wrong_key))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-both-bad-counters:",
			execute_module_xboot_ks_both_bad_counters))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-diff-payload-eq-counter:",
			execute_module_xboot_ks_diff_payload_eq_counter))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-invalid-bak-xcs-set-higher-counter:",
		execute_module_xboot_ks_invalid_bak_xcs_set_higher_counter))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-xcs-sl-not-rootable:",
		execute_module_xboot_ks_xcs_sl_not_rootable))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-xcs-sl-not-rootable-bak-invalid:",
		execute_module_xboot_ks_xcs_sl_not_rootable_bak_invalid))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-same-payload-imei-hmac:",
		execute_module_xboot_ks_same_payload_imei_hmac))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-same-payload-imei-hmac-diff-key:",
		execute_module_xboot_ks_same_payload_imei_hmac_diff_key))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot-ks-valid-high-key-invalid-low-key:",
		execute_module_xboot_ks_valid_high_key_invalid_low_key))
		return -FCSERR_ENOMEM;
	if (add_module(it, "xboot_simlock_unlock_data:",
			execute_module_xboot_simlock_unlock_data))
		return -FCSERR_ENOMEM;
	if (add_module(it, "gen-hwconf-x-parser-normal:",
			execute_module_gen_hwconf_x_parser_normal))
		return -FCSERR_ENOMEM;
	if (add_module(it, "gen-hwconf-x-parser-error:",
			execute_module_gen_hwconf_x_parser_error))
		return -FCSERR_ENOMEM;
	if (add_module(it, "gen-der-parser:",
			execute_module_gen_der_parser))
		return -FCSERR_ENOMEM;
	if (add_module(it, "gen-rule-verifier:",
			execute_module_gen_rule_verifier))
		return -FCSERR_ENOMEM;
	return FCSERR_OK;
}
