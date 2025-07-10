/*
 * Copyright (c) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef MT_XM_COMMON_H_
#define MT_XM_COMMON_H_

#include "iterator.h"
int module_setup_normal(fcsmt_log_t log);

/* Normal values values below should be suited to the target device */
/* Is found under app folder or will be generated for the DUT. */
extern const unsigned char const_dut_fuse;
extern const unsigned int const_dut_fuse_len;

extern const unsigned char const_dut_dev_id[];
extern const unsigned int const_dut_dev_id_len;

extern const unsigned char const_dut_imei[];
extern const unsigned int const_dut_imei_len;

extern const unsigned char const_dut_hwconfig[];
extern const unsigned int const_dut_hwconfig_len;

extern const unsigned char const_dut_sl_signature[];
extern const unsigned int const_dut_sl_signature_len;

extern const unsigned char const_dut_sl_data[];
extern const unsigned int const_dut_sl_data_len;

extern const unsigned int const_dut_sl_asahi_opid;

#endif

