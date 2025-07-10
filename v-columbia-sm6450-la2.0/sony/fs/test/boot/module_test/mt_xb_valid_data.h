/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef MT_XB_CORRECT_DATA_
#define MT_XB_CORRECT_DATA_

extern const unsigned char keystore_counter5[];
extern const unsigned int keystore_counter5_len;
extern unsigned int sec_data_keystore_counter5;

extern const unsigned char xcs_keystore_bound_to_hmac_devid[];
extern const unsigned int xcs_keystore_bound_to_hmac_devid_len;
extern const unsigned char xcs_keystore_bound_to_hmac_imei[];
extern const unsigned int xcs_keystore_bound_to_hmac_imei_len;
extern const unsigned char sony_keystore_bound_to_hmac_imei[];
extern const unsigned int sony_keystore_bound_to_hmac_imei_len;
extern const unsigned char sony_keystore_bound_to_hmac_imei_new_key[];
extern const unsigned int sony_keystore_bound_to_hmac_imei_new_key_len;
extern const unsigned int ks_bound_to_hmac_valid_n_normal_cert;

extern const unsigned char hmac_key[];
extern const unsigned int hmac_key_len;
extern const unsigned char hmac_key_new[];
extern const unsigned int hmac_key_new_len;

#endif
