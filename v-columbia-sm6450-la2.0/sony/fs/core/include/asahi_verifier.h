/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef ASAHI_VERIFIER_H_
#define ASAHI_VERIFIER_H_

#include "rule_verifier.h"
#include <stdlib.h>
#include <stdint.h>

/*
 * DESCRIPTION:
 *   The ASAHI Verifier is responsible for verifying a ASAHI signature.
 * NOTE:
 *   The verifier will only do the general operations for signature
 *   verification with ASAHI signature content and provided hash value.
 *   Additional checks should be done by client code.
 */

/**
 *  Basic verify of ASAHI signature given a calculated hash value.
 *
 *  The rootcert_buf is a buffer of DER encoded certificates. The certs
 *  is concatenated together without any extra information. The
 *  ASN1/DER format will give enough information to separate certs.
 *
 *  @param [in]  rule                  Handler to rule verifier
 *  @param [in]  rootcert_buf          A pointer to a buffer with root certs
 *  @param [in]  rootcert_buf_length   Length of the root cert buffer
 *  @param [in]  asahi_buffer          A pointer to the asahi buffer data
 *  @param [in]  asahi_buffer_length   Length of the ASAHI buffer
 *  @param [in]  hash                  Hash value for verify
 *  @param [in]  hash_length           Size of Hash value
 *
 *  @returns int
 */
int asahi_verify(
		struct rule_verifier *rule,
		uint8_t *rootcert_buf,
		size_t rootcert_buf_length,
		uint8_t *asahi_buffer,
		size_t asahi_buffer_length,
		uint8_t *hash,
		size_t hash_length);

#endif /* ASAHI_VERIFIER_H_ */
