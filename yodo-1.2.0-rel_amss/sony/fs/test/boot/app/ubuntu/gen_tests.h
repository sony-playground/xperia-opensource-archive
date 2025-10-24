/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef GEN_TESTS_H_
#define GEN_TESTS_H_

#include "iterator.h"
#include "fcserr.h"

extern int execute_module_xboot_normal_setup(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

extern int execute_module_xboot_delay_normal_setup(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

extern int execute_module_xboot_short_press(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_xfl(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_factmode_xfl(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_charger(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_qcfb(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_force_reset(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_force_shutdown(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_watchdog(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_empty_ks_usb_no(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_empty_ks_usb_yes(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_empty_hwc_usb_no(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_empty_hwc_usb_yes(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_first_keystore(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_apply_xcs_keystore(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

extern int execute_module_xboot_reset_arb(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_hwc_wrong_payload_usb_no(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_hwc_wrong_payload_usb_yes(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_hwc_wrong_devid_usb_no(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_hwc_wrong_devid_usb_yes(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_wrong_payload(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_both_wrong_payload_usb_no(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_both_wrong_payload_usb_yes(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_wrong_devid(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_wrong_imei(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_both_wrong_devid_usb_no(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_both_wrong_imei_usb_no(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_both_wrong_devid_usb_yes(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_both_wrong_imei_usb_yes(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_insert_ks_failed_due_to_xcs(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_insert_ks_failed_due_to_counter(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_bound_to_hmac_devid_valid_key(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_bound_to_hmac_imei_valid_key(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_bound_to_hmac_devid_wrong_key(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_bound_to_hmac_imei_wrong_key(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_both_bad_counters(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_diff_payload_eq_counter(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_invalid_bak_xcs_set_higher_counter(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_xcs_sl_not_rootable(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_xcs_sl_not_rootable_bak_invalid(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_same_payload_imei_hmac(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_same_payload_imei_hmac_diff_key(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_ks_valid_high_key_invalid_low_key(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_xboot_simlock_unlock_data(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_gen_hwconf_x_parser_normal(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_gen_hwconf_x_parser_error(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int execute_module_gen_der_parser(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);


int execute_module_gen_rule_verifier(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

int setup_modules(struct iterator_info *it);

#endif
