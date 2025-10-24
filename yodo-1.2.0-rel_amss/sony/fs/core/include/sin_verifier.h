/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef SIN_VERIFIER_H_
#define SIN_VERIFIER_H_

#include "rule_verifier.h"
#include "sin_parser.h"
#include <stdlib.h>
#include <stdint.h>

/* DESCRIPTION:
 *   The SIN Verifier is responsible for verifying a SIN header.
 * NOTE:
 *   The verifier will do the general operation like Certificate chain and
 *   signature verification with SIN header content.
 *   Other checks should be done by client code:
 *     - Payload checks
 *     - Sony specific checks
 */

/**
 *  Basic verify of certificate chain and signature of SIN format given a
 *  list of allowed root certificates.
 *
 *  The rootcert_buf is a buffer of DER encoded certificates. The certs
 *  is concatenated together without any extra information. The
 *  ASN1/DER format will give enough information to separate certs.
 *
 *  The function will return a sin_parser handle if successful.
 *
 *  @param [in]  rule                  Handler to rule verifier
 *  @param [in]  rootcert_buf          A pointer to a buffer with root certs
 *  @param [in]  rootcert_buf_length   Length of the root cert buffer
 *  @param [in]  sin_buffer            A pointer to the sin buffer binary data
 *  @param [in]  sin_buffer_length     Length of the raw SIN buffer
 *  @param [out] sin_parser_handle     A pointer to sin parser handle
 *
 *  @returns int
 */
int sin_verify(
		struct rule_verifier *rule,
		uint8_t *rootcert_buf,
		size_t rootcert_buf_length,
		uint8_t *sin_buffer,
		uint32_t sin_buffer_length,
		struct sin_header **sin_parser_handle);

#endif /* SIN_VERIFIER_H_ */
