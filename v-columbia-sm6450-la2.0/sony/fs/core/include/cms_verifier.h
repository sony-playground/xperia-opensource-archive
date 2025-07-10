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
 *   The CMS Verifier is responsible for verifying a CMD signature.           *
 * NOTE:                                                                      *
 *   The verifier will do the operations:                                     *
 *   - verify certificate chain                                               *
 *   - verify signature                                                       *
 *   - verify payload                                                         *
 *   - verify somc specific usages and bindings                               *
 *   - if detached payload the caller need to provide buffer with payload     *
 *                                                                            *
 *****************************************************************************/
#ifndef CMS_VERIFIER_H_
#define CMS_VERIFIER_H_

#include <stdlib.h>
#include "rule_verifier.h"

/**
 *  Do CMS verifier operation.
 *
 *  The rootcerts is a buffer of DER encoded certificates. ASN1 sizes
 *  separate the certificates.
 *  The external_payload is optional but must be present if detached
 *  CMS.
 *  If detached CMS the embedded_payload will be NULL.
 *
 *  @param [in]  cms                     A pointer to a buffer with CMS
 *  @param [in]  cms_length              Length of the CMS
 *  @param [in]  rule                    Rule Verify session handle
 *  @param [in]  rootcerts               A pointer to a buffer with root certs
 *  @param [in]  rootcerts_length        Length of the root cert buffer
 *  @param [in]  external_payload        A pointer to a buffer with payload
 *  @param [in]  external_payload_length Length of the payload
 *  @param [out] embedded_payload        Returns pointer to embedded payload
 *                                       (freed by caller)
 *  @param [out] embedded_payload_length Length of embedded payload
 *
 *  @returns int
 */
int cms_verify(uint8_t         *cms,
	size_t                  cms_length,
	struct rule_verifier *rule,
	uint8_t                *rootcerts,
	size_t                  rootcerts_length,
	uint8_t                *external_payload,
	size_t                  external_payload_length,
	uint8_t               **embedded_payload,
	size_t                 *embedded_payload_length);

#endif /* CMS_VERIFIER_H_ */
