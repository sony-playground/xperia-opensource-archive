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
 *   The verifier is responsible for verifying a signture.                    *
 * NOTE:                                                                      *
 *   The verifier will only do general operations for signature               *
 *   verification.                                                            *
 *   Additional checks should be done by client code.                         *
 *                                                                            *
 *****************************************************************************/
#ifndef SIGNATURE_H_
#define SIGNATURE_H_

#include <stdlib.h>
#include <stdint.h>

/**
 *  Basic verify of PKCS1 signature given a certificate chain and a hash.
 *
 *  The certchain is a buffer of DER encoded certificates. ASN1 sizes
 *  separate the certificates. The first certificate should be the leaf
 *  certificate (the signer).
 *
 *  @param [in]  certchain_buffer        A pointer to a buffer with cert chain
 *  @param [in]  certchain_buffer_length Size of the cert chain buffer
 *  @param [in]  signature               A pointer to a signature.
 *  @param [in]  signature_length        Size of the signature.
 *  @param [in]  hash                    A pointer to a hash.
 *  @param [in]  hash_length             Size of the hash.
 *
 *  @returns int
 */
int signature_verify(
		uint8_t *certchain_buffer,
		size_t   certchain_buffer_length,
		uint8_t *signature,
		size_t   signature_length,
		uint8_t *hash,
		size_t   hash_length);

/**
 *  Basic verify of RSASSA-PSS signature given a certificate chain and a hash.
 *
 *  The certchain is a buffer of DER encoded certificates. ASN1 sizes
 *  separate the certificates. The first certificate should be the leaf
 *  certificate (the signer).
 *
 *  @param [in]  certchain_buffer        A pointer to a buffer with cert chain
 *  @param [in]  certchain_buffer_length Size of the cert chain buffer
 *  @param [in]  signature               A pointer to a signature.
 *  @param [in]  signature_length        Size of the signature.
 *  @param [in]  hash                    A pointer to a hash.
 *  @param [in]  hash_length             Size of the hash.
 *
 *  @returns int
 */
int signature_verify_rsassa_pss(
		uint8_t *certchain_buffer,
		size_t   certchain_buffer_length,
		uint8_t *signature,
		size_t   signature_length,
		uint8_t *hash,
		size_t   hash_length);

#endif /* SIGNATURE_H_ */
