/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef SIMLOCK_H
#define SIMLOCK_H

#include "rule_types.h"

/**
 *  Verify Simlock.
 *
 *  This function verifies a range in data buffer with provided signature.
 *  The range offset which is fetched from signature is returned.
 *
 *  The rootcert_buf is a buffer of DER encoded certificates. ASN1 sizes
 *  separate the certificates.
 *
 *  @param [in]  imei                      Ptr to buffer with IMEI
 *  @param [in]  imei_length               Length of IMEI
 *  @param [in]  embed_rootcert_list       Embedded rootcerts
 *                                         for current security state
 *  @param [in]  embed_rootcert_list_count Number of embedded rootcerts items
 *  @param [in]  data                      Payload containing range to verify
 *  @param [in]  data_length               Length of above payload
 *  @param [in]  signature                 Signature protecting payload range
 *  @param [in]  signature_length          Length of Signature
 *  @param [in]  opid                      Operator ID.
 *                                         If non-zero the signing certificate
 *                                         MUST contain an OU with MATCHING
 *                                         OPID.
 *                                         If zero the signing certificate
 *                                         MUST NOT contain an OU with OPID.
 *                                         All use cases other than OTA
 *                                         Simlock shall use zero.
 *  @param [out] range_offset              Offset of range in data
 *  @param [out] range_length              Length of range
 *
 *  @returns int                           FCS error code
 */
int simlock_verify(
	uint8_t *imei,
	size_t imei_length,
	struct embed_rootcert_item *embed_rootcert_list,
	size_t embed_rootcert_list_count,
	uint8_t *data,
	size_t data_length,
	uint8_t *signature,
	size_t signature_length,
	unsigned int opid,
	unsigned int *range_offset,
	size_t *range_length);

#endif /* SIMLOCK_H */
