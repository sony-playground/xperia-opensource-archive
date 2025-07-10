/*
 * Copyright (c) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
/**
 * @defgroup xmodem Sony Modem support functions
 * @{
 * @brief Interface to set up and verify protected properities
 *
 * During intialization the security settings (and keystore) is loaded and
 * verified.
 *
 * The functionality relies on the following support from integration:
 * - Implementation of PAL interface
 * - Crypto functionality
 * - Fuse config (is_fused/die_id)
 * - Heap
 *
 * Detailed information on the integration is found in
 * doc/integration/modem.txt.
 *
 * @file xmodem.h
 */
#ifndef XMODEM_H_
#define XMODEM_H_

#include <fcserr.h>
#include <rule_types.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Init Xperia Modem context.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xmodem_init(void);

/**
 * @brief Cleanup Xperia Modem context.
 *
 * @returns None.
 */
void xmodem_deinit(void);

/**
 * @brief Returns the IMEI from the requested index.
 *
 * It is required that the #xmodem_init has executed successfully.
 *
 * NOTE: Caller should not deallocate returned buffer
 *
 *
 * @param[in]  index               Index of requested IMEI. (0/1)
 * @param[in/out]  phone_data      Buffer for the IMEI data.
 * @param[in] phone_data_len       Length of phone_data buffer.
 *
 * @returns Phone ID buffer for success, else NULL.
 */
int xmodem_get_phoneid(unsigned int index,
		unsigned char *phone_data,
		unsigned int phone_data_len);

/**
 *  Verify Simlock signature and data.
 *  Returns success if RSA protected hash in
 *  signature matches the hash of over part of data.
 *
 *  @param [in]  data                  Payload with range to verify
 *  @param [in]  data_length           Length of above payload
 *  @param [in]  signature             Signature protecting payload range
 *  @param [in]  signature_length      Length of Signature
 *  @param [in]  opid                  Operator ID.
 *                                     If non-zero the signing certificate
 *                                     MUST contain an OU with MATCHING OPID.
 *                                     IF zero the signing certificate MUST
 *                                     NOT contain an OU with OPID.
 *                                     All use cases other than OTA Simlock
 *                                     shall use zero.
 *  @param [out] range_offset          Offset of range in data
 *  @param [out] range_length          Length of range

 *  @returns int
 */
int xmodem_verify_simlock(
		unsigned char *data,
		unsigned int data_length,
		unsigned char *signature,
		unsigned int signature_length,
		unsigned int opid,
		unsigned int *range_offset,
		unsigned int *range_length);

#endif
/** @}*/

