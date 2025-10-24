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
 *   The Rule Verifier is responsible for verifying SOMC specific rules       *
 *   concerning usage of image and binding towards devices.                   *
 *   This file contains the interface used by cert chain verify               *
 *   implementation.                                                          *
 *                                                                            *
 *****************************************************************************/
#ifndef RULE_VERIFIER_INTERN_H_
#define RULE_VERIFIER_INTERN_H_

#include "rule_verifier.h"

struct rule_extension {
	int            cert_level;
	const uint8_t *oid;
	size_t         oid_len;
	const uint8_t *asn1_buffer;
	size_t         asn1_buffer_len;
};

struct rule_attribute {
	const uint8_t *oid;
	size_t         oid_len;
	const uint8_t *asn1_buffer;
	size_t         asn1_buffer_len;
};

struct rule_cn {
	int            cert_level;
	const uint8_t *cn;
	size_t         cn_len;
};

struct rule_ou {
	int            cert_level;
	const uint8_t *ou;
	size_t         ou_len;
};

/**
 *  Do the verify of found extensions and attributes for requested usage.
 *  This should be called after signature is parsed and cert chain is
 *  verified.
 *
 *  @param [in]  handle                  Rule Verify session handle
 *  @param [out] list_ptr                Returned pointer to extensions list
 *  @param [out] list_num                Number of extensions in list
 *
 *  @returns int
 */
int rule_final(struct rule_verifier *handle);

/**
 *  Update unhandled extension with found during cert chain verify operation.
 *
 *  @param [in]  handle                  Rule Verify session handle
 *  @param [in]  attribute               Found unhandled extension
 *
 *  @returns int
 */
int rule_update_unhandled_extensions(struct rule_verifier *handle,
		const struct rule_extension *extension);

/**
 *  Update unhandled attributes with found during signature parse operation.
 *
 *  @param [in]  handle                  Rule Verify session handle
 *  @param [in]  attribute               Found unhandled attribute
 *
 *  @returns int
 */
int rule_update_unhandled_attributes(struct rule_verifier *handle,
		const struct rule_attribute *attribute);

/**
 *  Update certificate subject common found during cert chain verify
 *  operation.
 *
 *  @param [in]  handle                  Rule Verify session handle
 *  @param [in]  cn                      Found subject cn
 *
 *  @returns int
 */
int rule_update_subject_cn(struct rule_verifier *handle,
		const struct rule_cn *cn);

/**
 *  Update certificate subject organizational unit found during cert chain
 *  verify operation.
 *
 *  @param [in]  handle                  Rule Verify session handle
 *  @param [in]  ou                      Found subject ou
 *
 *  @returns int
 */
int rule_update_subject_ou(struct rule_verifier *handle,
		const struct rule_ou *ou);

#endif /* RULE_VERIFIER_INTERNAL_H_ */
