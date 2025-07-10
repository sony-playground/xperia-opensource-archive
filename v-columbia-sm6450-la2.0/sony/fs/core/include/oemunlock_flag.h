/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef OEMUNLOCK_FLAG_H_
#define OEMUNLOCK_FLAG_H_

#include <stdlib.h>
#include <stdint.h>
#include "kstypes.h"
#include "rule_types.h"

/* DESCRIPTION:
 *   The Oemunlock flag Verifier is responsible for verifying
 *   an Oemunlock request. This request is used to set the
 *   oemunlock allow flag, thus disabling the factory
 *   reset protection feature.
 *   It will verify a CMS signed message, with binding on the IMEI.
 *   It will also check if a google account data is present
 *   in the header of the frp partition.
 *   If account is present the verification will fail.
 */

/**
 *  Verify oemunlcok flag . If verification is successful the oem unlcok flag
 *  can be set.
 *
 *  Function will return FCSERR_OK if request is valid.
 *
 *  @param [in]  ks                         Keystore context
 *  @param [in]  phone_id                   Phone ID of the device
 *  @param [in]  phone_id_len               Phone ID length
 *  @param [in]  embed_rootcert_list        List with embedded roots
 *  @param [in]  embed_rootcert_list_count  Count of list elements
 *  @param [in]  oemunlock_request          A pointer to the request msg
 *  @param [in]  oemunlock_request_len      Length of the request msg
 *  @param [in]  frp_data                   Google factory reset
 *                                          protection data
 *  @param [in]  frp_data_len               Length of the frp_data
 *
 *  @returns int
 */
int oemunlock_flag_verify(
		struct ks_ctx *ks,
		uint8_t *phone_id,
		size_t phone_id_len,
		struct embed_rootcert_item *embed_rootcert_list,
		size_t embed_rootcert_list_count,
		uint8_t *oemunlock_request,
		size_t oemunlock_request_len,
		uint8_t *frp_data,
		size_t frp_data_len);


#endif /* OEMUNLOCK_FLAG_H_ */
