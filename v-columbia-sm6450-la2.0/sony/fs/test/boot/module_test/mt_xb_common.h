/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef MT_XB_COMMON_H_
#define MT_XB_COMMON_H_

#include "iterator.h"
#include "xboot_pal_types.h"

#define MT_XB_REQ_HWSTATE          0
#define MT_XB_EXECUTE              1
#define MT_XB_UNEXPECTED_SHUTDOWN  2
#define MT_XB_EXPECTED_SHUTDOWN    3

static const enum xbpal_rgb_led_cfg_t const_led_off = XBPAL_LED_TURN_OFF;
static const enum xbpal_rgb_led_cfg_t const_led_red = XBPAL_LED_TURN_ON_RED;
static const enum xbpal_rgb_led_cfg_t const_led_green = XBPAL_LED_TURN_ON_GREEN;
static const enum xbpal_rgb_led_cfg_t const_led_blue = XBPAL_LED_TURN_ON_BLUE;

static const unsigned char const_factory_mode_on = 1;

int module_setup_normal(fcsmt_log_t log);
int check_cmdline(char *cmdline, fcsmt_log_t log);

/* Normal values values below should be suited to the target device */
/* Is found under app folder or will be generated for the DUT. */
extern const unsigned char const_dut_fuse;
extern const unsigned int const_dut_fuse_len;

extern const unsigned char const_dut_dev_id[];
extern const unsigned int const_dut_dev_id_len;

extern const unsigned char const_dut_hwconfig[];
extern const unsigned int const_dut_hwconfig_len;

extern const unsigned char const_dut_miscta_dk[];
extern const unsigned int const_dut_miscta_dk_len;

extern const unsigned char const_dut_ks_valid_devid[];
extern const unsigned int const_dut_ks_valid_devid_len;
extern const unsigned char const_dut_ks_valid_imei[];
extern const unsigned int const_dut_ks_valid_imei_len;
extern const unsigned char const_dut_ks_valid_imei_diff_payload[];
extern const unsigned int const_dut_ks_valid_imei_diff_payload_len;
extern const unsigned char const_dut_ks_xcs_valid[];
extern const unsigned int const_dut_ks_xcs_valid_len;

extern const unsigned int const_dut_sec_data_version;
extern const unsigned int const_dut_sec_data_unlock;
extern const unsigned int const_dut_sec_data_ks_counter;
extern const unsigned int const_dut_sec_data_ks_xcs_rot;
extern const unsigned char const_dut_sec_data_sake_nonce[20];
extern const unsigned char const_dut_sec_data_ks_hash[32];
extern const unsigned long const_dut_sec_data_rollback_counter[32];

extern const unsigned int const_dut_sec_data_ks_xcs_counter;
extern const unsigned int const_dut_sec_data_ks_xcs_xcs_rot;
extern const unsigned char const_dut_sec_data_ks_xcs_hash[32];

extern const unsigned int const_dut_ks_valid_n_normal_cert;
extern const unsigned int const_dut_ks_valid_n_xfl_cert;
extern const unsigned int const_dut_emb_valid_n_xfl_cert;
extern const unsigned int const_dut_ks_xcs_valid_n_normal_cert;
extern const unsigned int const_dut_ks_xcs_valid_n_xfl_cert;

extern const unsigned char const_dut_boot_version[];
extern const unsigned int const_dut_boot_version_len;

extern const unsigned char const_dut_boot_config[];
extern const unsigned int const_dut_boot_config_len;

extern const unsigned char const_dut_reset_frp[];
extern const unsigned int const_dut_reset_frp_len;

extern const unsigned char const_dut_sl_signature[];
extern const unsigned int const_dut_sl_signature_len;
extern const unsigned char const_dut_sl_data[];
extern const unsigned int const_dut_sl_data_len;
extern const unsigned char const_dut_sl_not_rootable_signature[];
extern const unsigned int const_dut_sl_not_rootable_signature_len;
extern const unsigned char const_dut_sl_not_rootable_data[];
extern const unsigned int const_dut_sl_not_rootable_data_len;

extern const unsigned char const_dut_auth_channel[];
extern const unsigned int const_dut_auth_channel_len;
extern const unsigned char const_dut_authch_sake_nonce[];
extern const unsigned int const_dut_authch_sake_nonce_len;

extern const char * const cmdline_args[];
extern const int nr_of_cmdline_args;

#endif
