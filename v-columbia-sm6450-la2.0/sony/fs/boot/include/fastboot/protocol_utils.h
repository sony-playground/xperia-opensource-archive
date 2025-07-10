/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_PROTOCOL_UTIL_H_
#define FCS_PROTOCOL_UTIL_H_

#include <stdbool.h>
#include <stdlib.h>
#include "transport_verifier.h"
#include "cms_verifier.h"
#include "digest.h"



#ifndef MAX
#define MAX(x, y) ((x) > (y)?(x):(y))
#endif /* MAX */
#ifndef MIN
#define MIN(x, y) ((x) < (y)?(x):(y))
#endif /* MIN */


int get_miscta_unit_data(int ta_unit, char *buf, int buf_size);
int get_phone_id(char *buf, int buf_size);
int get_rooting_status_string(char *buf, unsigned int buf_size);
int bootloader_unlock_allowed(uint8_t *allow_unlock, uint8_t *rooting_status);
int get_simlock_rck_h(uint8_t *rck_h);
int pu_get_part_type(const char *ptn, char *type, size_t type_size);
int fastboot_get_secure_state(char *buf, size_t buf_size);
int pu_get_flash_info(char *buf, int buf_size);
int get_default_security(char *buf, size_t buf_size);
int get_s1_root(char *buf, size_t buf_size);
int fcs_wait_partition_rescan(char *name, int nbr_part);
int is_partition_restricted(char *partition, bool *is_restricted);
int get_x_conf_root_hash(uint8_t *buf, size_t buf_len, int *nroots);
int set_ship_mode(void);


int devid_to_buffer(uint8_t **outbuf, size_t *outbuf_len);
int remove_auth_partition(const char *part);
int add_auth_partition(const char *name,
        struct transport_verifier *transport_handle);
int fastboot_check_cmd_auth(const char *cmd, const char *param, void *data, uint32_t sz, uint8_t *cmsbuf, size_t cmsbuf_len, uint8_t auth_level);
int pu_digest_partition(const char *part, uint8_t *val, size_t len);

#endif
