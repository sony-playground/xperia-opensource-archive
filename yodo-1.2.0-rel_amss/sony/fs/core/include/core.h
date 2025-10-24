/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef CORE_H_
#define CORE_H_
#include <stdint.h>
#include <stdbool.h>

/*
 *   Functions for prepare core functionality for use.
 */

/**
 *  Do application level setup of crypto block.
 *
 *  @returns none
 */
void core_crypto_setup(void);

/**
 *  Do application level cleanup of crypto block.
 *
 *  @returns none
 */
void core_crypto_cleanup(void);

int core_has_sd_card(bool *has_card);

int core_is_fused(bool *is_fused);

int core_get_dieid(unsigned char *id, unsigned int len);

int core_get_dieid_len(void);

int core_get_platformid(unsigned char *id, unsigned int len);

int core_get_platformid_len(void);

int core_get_root_key_hash(unsigned char *buf, unsigned int len);

int core_get_root_key_hash_len(void);

int core_get_hmac_key(uint8_t **hmac_key, uint32_t *hmac_key_len);

int core_get_sector_size(char *buf, unsigned int buf_sz);

int core_get_usb_version(char *buf, unsigned int buf_sz);

int core_get_battery_capacity(char *buf, unsigned int buf_sz);

int core_get_storage_info(char *buf, unsigned int buf_sz);

/**
 * Returns 1 if test certificates are allowed
 * otherwise 0.
 *
 * @returns int
 */
int core_is_test_cert_allowed(void);

/**
 * Generate random number.
 *
 * @returns int
 */
int fcs_urand(uint8_t *buf, uint16_t len);

/**
 * Seed the random number generator.
 *
 * @returns int
 */
int fcs_srand(unsigned int seed);

#endif /* CORE_H_ */
