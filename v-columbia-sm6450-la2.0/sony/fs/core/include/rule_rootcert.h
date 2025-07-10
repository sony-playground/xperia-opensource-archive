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
 *   This interface contains utility functions to fetch root cerificates      *
 *   content.                                                                 *
 *                                                                            *
 *****************************************************************************/
#ifndef RULE_ROOTCERT_H_
#define RULE_ROOTCERT_H_

#include <stdlib.h>
#include <stdint.h>
#include "rule_types.h"
#include "kstypes.h"

/**
 *  Fetch allowed root certificates given a usage.
 *
 *  The rootcert is a buffer of DER encoded certificates. ASN1 sizes
 *  separate the certificates. The rootcert buffer should be deallocated by
 *  caller.
 *
 *  @param [in]  usage                     The expected usage
 *  @param [in]  embed_rootcert_list       Embedded rootcerts
 *                                         for current security state
 *  @param [in]  embed_rootcert_list_count Number of embedded rootcerts items
 *  @param [in]  keystore_hdl              KeyStore handle.
 *                                         NULL if not present.
 *  @param [out] rootcert                  Ptr to buffer with rootcerts.
 *  @param [out] rootcert_length           Length of the root cert buffer.
 *
 *  @returns int
 */
int rule_get_roots(
		uint32_t usage,
		struct embed_rootcert_item *embed_rootcert_list,
		size_t embed_rootcert_list_count,
		struct ks_ctx *keystore_hdl,
		uint8_t **rootcerts,
		size_t *rootcerts_length);


#endif /* RULE_ROOTCERT_H_ */
