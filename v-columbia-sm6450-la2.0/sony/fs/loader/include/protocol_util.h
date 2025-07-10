/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_PROTOCOL_UTIL_H_
#define FCS_PROTOCOL_UTIL_H_

#include <stdbool.h>
#include "digest.h"
#include "storage.h"

#define MAX(x, y) ((x) > (y)?(x):(y))
#define MIN(x, y) ((x) < (y)?(x):(y))

int get_miscta_unit_data(int ta_unit, char *buf, int buf_size);
int get_phone_id(char *buf, int buf_size);
int get_rooting_status_string(char *buf, unsigned int buf_size);
int bootloader_unlock_allowed(uint8_t *allow_unlock, uint8_t *rooting_status);
int get_simlock_rck_h(uint8_t *rck_h);
ssize_t pu_get_part_size(struct storage_ctx *ctx);
int pu_get_part_type(const char *ptn, char *type, size_t type_size);
int pu_digest_partition(const char *part, uint8_t *val, size_t len);
int fastboot_get_secure_state(char *buf, size_t buf_size);
int pu_get_flash_info(char *buf, int buf_size);
int get_default_security(char *buf, size_t buf_size);
int get_s1_root(char *buf, size_t buf_size);
int fcs_usb_version(char *buf, ssize_t buf_sz);
int fcs_get_lun_and_index_of_partition(const char *partition,
		ssize_t partition_sz, char *lun, ssize_t lun_sz, int *idx);
int fcs_wait_partition_rescan(char *name, int nbr_part);
int is_partition_restricted(char *partition, bool *is_restricted);
int get_x_conf_root_hash(uint8_t *buf, size_t buf_len, int *nroots);
int set_ship_mode(void);

#endif
