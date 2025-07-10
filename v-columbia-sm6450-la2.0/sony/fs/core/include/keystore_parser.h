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
 *   This interface contains functions to handle KeyStore content.            *
 *                                                                            *
 *****************************************************************************/
#ifndef KEYSTORE_PARSER_H_
#define KEYSTORE_PARSER_H_

#include <stdlib.h>
#include <stdint.h>

struct keystore_handle;

/**
 *  Create keystore parser handler from keystore content.
 *
 *  @param [in]   keystore         Keystore content
 *  @param [in]   keystore_length  Length of keystore content
 *  @param [out]  keystore_hdl_p   A pointer to a buffer with handle.
 *
 *  @returns int
 */
int keystore_parser_init(
		uint8_t                   *keystore,
		size_t                     keystore_length,
		struct keystore_handle **keystore_hdl_p);

/**
 *  Fetch root certificates for given domain.
 *
 *  The rootcert is a buffer of DER encoded certificates. ASN1 sizes
 *  separate the certificates. The rootcert should be deallocated by
 *  caller.
 *
 *  @param [in]  keystore_hdl      The handle
 *  @param [in] domain             Requested domain
 *  @param [out]  rootcert         A pointer to a buffer with rootcerts.
 *  @param [out]  rootcert_length  Length of the root cert buffer.
 *
 *  @returns int
 */
int keystore_parser_get_roots(struct keystore_handle *keystore_hdl,
		uint8_t   domain,
		uint8_t **rootcerts,
		size_t   *rootcerts_length);

/**
 *  Cleanup keystore parser handler.
 *
 *  @param [in]  keystore_hdl      The handle
 *
 *  @returns int
 */
int keystore_parser_deinit(struct keystore_handle *keystore_hdl);


#endif /* KEYSTORE_PARSER_H_ */
