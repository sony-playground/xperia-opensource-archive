/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef KS_PKCS_H_
#define KS_PKCS_H_

#include <stdint.h>
#include "ks.h"
#include "ksio.h"
#include "kscrypto.h"

/* PKI/Static implementation of Keystore                          */
/* Only static (server signed keystore) is supported (for NV)     */
/* Alternatively keystore can be linked into integration          */
/* A Platform specific signature verification callback is needed  */
/* (HW signature verification or OpenSSL)                         */

/**
 * @brief Create Static (PKI verified) keystore
 * This function creates the handle, it does not
 * initialize the keystore handle with any data
 *
 * @param[out] keystore_handle    Opaque handle to keystore
 * @param[in]  dev_id             Device ID
 * @param[in]  dev_id_len         Length of the Device ID
 * @param[in]  imei               IMEI
 * @param[in]  imei_len           Length of the IMEI
 * @param[in]  nv_org_handle      NV IO handle
 * @param[in]  nv_bak_handle      NV IO handle
 * @param[in]  rpmb_handle        RPMB IO handle
 * @param[in]  rot                Root of trust
 * @param[in]  rot_sz             Size of root of trust
 * @param[in]  hmac_key           Key used for hmac sha256 of the device binding
 *                                data in the keystore(DeviceID), can be NULL
 *                                if not present in the device.
 * @param[in]  hmac_key_len       length of the hmac_key
 * All pointers are cleared when ks_destroy() is called.
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int ks_create_static(
	struct ks_ctx **keystore_handle, uint8_t *dev_id,
	uint32_t dev_id_len, uint8_t *imei, uint32_t imei_len,
	uint8_t *rot, uint32_t rot_sz,
	const uint8_t *hmac_key, uint32_t hmac_key_len);

#endif
