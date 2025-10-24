/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef SECDATA_UTILS_H_
#define SECDATA_UTILS_H_

int sec_data_get_rooting_status(uint8_t *data);

int sec_data_get_keystore_hash(uint8_t *data, size_t data_sz);

int sec_data_get_rollback_counter(uint32_t index, uint64_t *val);

uint32_t sec_data_get_num_rollback_counters(void);

int sec_data_get_xcs_rot(uint32_t *is_xcs_rot);

int sec_data_get_ks_counter(uint32_t *ks_counter);

int sec_data_get_has_been_unlocked(uint32_t *has_been_unlocked);

#endif /* SECDATA_UTILS_H_ */
