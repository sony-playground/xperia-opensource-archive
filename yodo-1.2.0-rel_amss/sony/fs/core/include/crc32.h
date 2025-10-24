/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef FCS_CRC32_H_
#define FCS_CRC32_H_

/**
 * @defgroup crc32 CRC32 calculator
 * @brief Functions for calculating 32-bit CRC checksum on databuffers.
 * @{
 * @file crc32.h
*/

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initialize 32-bit CRC table.
 *
 * @returns 32-bit table handle
 */
void *init_crc32_tab(void);

/**
 * @brief De-initialize 32-bit CRC table.
 *
 * @param[in] crc_tab32 32-bit table handle
 */
void deinit_crc32_tab(void *crc_tab32);

/**
 * @brief Update 32-bit CRC checksum.
 *
 * @param[in] crc_tab32 32-bit table handle
 * @param[in] crc_in Current checksum value
 * @param[in] c Byte to update checksum with
 * @param[out] p_crc_out Pointer to storage of calculated checksum
 */
int update_crc_32(
	void *crc_tab32, uint32_t crc_in, uint8_t c, uint32_t *p_crc_out);
/** @}*/

#endif /* FCS_CRC32_H_ */
