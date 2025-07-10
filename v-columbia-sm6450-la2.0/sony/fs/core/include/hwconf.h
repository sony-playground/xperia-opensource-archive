/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright (c) 2012-2016 Sony Mobile Communications Inc.                    *
 * All rights, including trade secret rights, reserved.                       *
 ******************************************************************************
 * Description                                                                *
 * Handling the hwconfig can be achieved by using this API.                   *
 *                                                                            *
 *****************************************************************************/

#ifndef HWCONF_H
#define HWCONF_H

#include "rule_types.h"

#define MAX_PHONEID_SIZE 8

/**
 * Handle used when accessing hwconfig information.
 */
#define hwconfig_t void *

/**
 *  Utility function: Setup hardware config.
 *
 *  This interface is for internal use (xboot, xfl and xmodem)
 *
 *  The rootcert_buf is a buffer of DER encoded certificates. ASN1 sizes
 *  separate the certificates.
 *
 *  If successful parsing and verification the function will return a
 *  hwconfig parser handle.
 *  The handle should be deallocated with hwconf_parser_deinit.
 *
 *  @param [in]  devid                     Ptr to buffer with DevId
 *  @param [in]  devid_len                 Length of DevId
 *  @param [in]  embed_rootcert_list       Embedded rootcerts
 *                                         for current security state
 *  @param [in]  embed_rootcert_list_count Number of embedded rootcerts items
 *  @param [out] handle_p                  Ptr to variable receiving handle.
 *
 *  @returns int
 */
int setup_hwconfig(
	uint8_t *devid,
	size_t devid_len,
	struct embed_rootcert_item *embed_rootcert_list,
	size_t embed_rootcert_list_count,
	hwconfig_t *handle_p);

/**
 *  Utility function: Teardown hardware config.
 *
 *  @param [in] handle              HwConfig handle.
 *
 *  @returns none
 */
void teardown_hwconfig(hwconfig_t handle);

/*
 * Get number IMEIs in HWConfig.
 * Returns a FCSERR_x code.
 *
 *  @param [out] count                     Number of IMEIs.
 *  @param [in]  handle                    HwConfig handle.
 *
 *  @returns int
 */
int get_imei_count(uint8_t *count,
		hwconfig_t handle);

/*
 * Read imei at index from HWConfig and return the result in <buf> which has
 * size <buf_size>.
 * Returns a FCSERR_x code.
 *
 *  @param [in]  index                     IMEI index
 *                                         0 for first IMEI, 1 for second
 *  @param [out] buf                       Ptr to buffer receiving the IMEI
 *  @param [in]  buf_size                  Size of buffer
 *  @param [out] id_length                 Length of returned IMEI.
 *  @param [in]  handle                    HwConfig handle.
 *
 *  @returns int
 */
int get_imei(uint8_t index, uint8_t *buf, size_t buf_size, size_t *id_length,
		hwconfig_t handle);

/*
 * Read DK from HWConfig. Returned buffer should be freed by caller.
 * Returns a FCSERR_x code.
 *
 *  @param [out] device_key                Returns buffer with HwConf DK
 *  @param [out] device_key_len            Returns length of buffer
 *  @param [in]  handle                    HwConfig handle.
 *
 *  @returns int
 */
int get_hwconf_dk(uint8_t **device_key, size_t *device_key_len,
	hwconfig_t handle);

/*
 * Read Is Prototype from HWConfig.
 * Returns a FCSERR_x code.
 *
 *  @param [out] is_prototype              Returns is_prototype
 *  @param [in]  handle                    HwConfig handle.
 *
 *  @returns int
 */
int get_is_prototype(int *is_prototype, hwconfig_t handle);


#endif /* HWCONF_H */
