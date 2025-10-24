/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef ROOTING_STATUS_H_
#define ROOTING_STATUS_H_

#include <stdint.h>
#include <stdlib.h>
#include <rule_types.h>

/**
 *  Fetch bootloader unlock data from SIMLock.
 *
 *  @param [out] rooting_status            Ptr to buffer with rooting status.
 *  @param [out] rck_h                     Ptr to buffer with the rck hash.
 *
 *  @returns int
 */
int get_simlock_unlock_data(uint8_t *unlock_status, uint8_t *rck_h);

/**
 * Verify rck.
 *
 * Calculate the hash of a given rck, and compare it to a
 * precalculated hash value.
 *
 * @param [in] rck_h_bin     Precalculated rck hash value.
 * @param [in] rck_ascii     rck in ascii format.
 * @param [in] rck_ascii_len Length of rck_ascii.
 *
 * @returns int
 */
int verify_rck(uint8_t *rck_h_bin, const uint8_t *rck_ascii,
		uint32_t rck_ascii_len);

/**
 * Check TA_GOOGLE_LOCK_STATE
 *
 * Check the miscTA unit 66671. Bootloader unlocking is allowed
 * only if the unit is empty.
 *
 * @param [out] allow_unlock 1 if bootloader unlock is allowed,
 * 			     0 if bootloader unlock is not allowed.
 *
 * @returns int
 */
int google_allow_unlock(uint8_t *allow_unlock);

/** Delete Device Key
 *
 * Delete the miscTA unit 66667.
 *
 * @returns int
 */
int delete_dk(void);

#endif
