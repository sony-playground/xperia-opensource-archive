/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright (c) 2016 Sony Mobile Communications Inc.                         *
 * All rights, including trade secret rights, reserved.                       *
 ******************************************************************************
 * DESCRIPTION:                                                               *
 *   The verifier is responsible for verifying a certificate chain.           *
 * NOTE:                                                                      *
 *   The verifier will only do general operations for certificate chain       *
 *   verification.                                                            *
 *   Additional checks should be done by client code.                         *
 *                                                                            *
 *****************************************************************************/
#ifndef CERTIFICATE_CHAIN_H_
#define CERTIFICATE_CHAIN_H_

#include "rule_verifier.h"
#include <stdlib.h>
#include <stdint.h>

/**
 *  Basic verify of certificate chain given a list of allowed root certificates.
 *
 *  The certchain is a buffer of DER encoded certificates. ASN1 sizes
 *  separate the certificates.
 *  The rootcert_buffer is a buffer of DER encoded certificates. ASN1 sizes
 *  separate the certificates.
 *
 *  @param [in]  rule                    Rule Verify session handle
 *  @param [in]  certchain_buffer        A pointer to a buffer with cert chain
 *  @param [in]  certchain_buffer_length Size of the cert chain buffer
 *  @param [in]  rootcert_buffer         A pointer to a buffer with rootcerts.
 *  @param [in]  rootcert_buffer_length  Size of the root cert buffer.
 *
 *  @returns int
 */
int certificatechain_verify(
		struct rule_verifier *rule,
		uint8_t  *certchain_buffer,
		size_t  certchain_buffer_length,
		uint8_t  *rootcert_buffer,
		size_t  rootcert_buffer_length);

#endif /* CERTIFICATE_CHAIN_H_ */
