/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef RULE_VERIFIER_H_
#define RULE_VERIFIER_H_

#include "fcs_defines.h"
#include "rule_types.h"
#include <stdlib.h>

struct rule_verifier;

/**
 *  Initialize verifier session for one or more of the following usages:
 *    Usage:                Parameter               Flag:
 *    flash                 <partition>             RULE_USAGE_FLASH
 *    partition-table       <unit>                  RULE_USAGE_PARTTBL
 *    hwconfig              <none>                  RULE_USAGE_HWCONFIG
 *    simlock               <none>                  RULE_USAGE_SIMLOCK
 *    ...                   <none>                  ...
 *
 *  Only FLASH and PARTTBL should normally be combined.
 *  If only one usage is allowed and no parameter is required the caller
 *  do not need to call rule_get_actual_usage.
 *
 *  @param [out] handle                  Returned handle
 *  @param [in]  binding                 A pointer to the binding structure
 *  @param [in]  usage                   Combination of allowed usage flags
 *
 *  @returns int
 */
int rule_init(struct rule_verifier **handle,
	struct dev_binding *binding,
	uint32_t usage);

/**
 *  Cleanup verifier session.
 *
 *  The function will release allocated resources.
 *
 *  @param [in]  handle                  Verify session handle
 *
 *  @returns none
 */
void rule_deinit(struct rule_verifier *handle);

/**
 *  Set expected OPID value. Only for SIMLOCK usage.
 *
 *  @param [in]  handle                  Verify session handle
 *  @param [in]  opid                    The expected OPID
 *
 *  @returns int
 */
int rule_set_opid(struct rule_verifier *handle,
	uint32_t opid);

/**
 *  Returns actual usage from session.
 *
 *  @param [in]  handle                  Verify session handle
 *  @param [out]  usage                  The actual usage of the session
 *  @param [out]  param                  The usage parameter
 *                                       (The returned param buffer should not
 *                                       be freed by caller)
 *
 *  @returns int
 */
int rule_get_actual_usage(struct rule_verifier *handle,
	uint32_t *usage,
	char **param);

/**
 *  Returns sequence value from session.
 *
 *  The sequence is extracted from attribute.
 *
 *  @param [in]  handle                  Verify session handle
 *  @param [out]  sequence               The found sequence
 *
 *  @returns int
 */
int rule_get_sequence(struct rule_verifier *handle,
	uint32_t *sequence);

/**
 * Returns info whether binding match was an HMAC
 *
 * @param [in]  handle                   Verify session handle
 * @param [out] verified_with_hmac       Pointer with value 1 or 0,
 *                                       depending whether binding match is
 *                                       HMAC or not
 *
 * @returns int
 */
int rule_verified_with_hmac(struct rule_verifier *handle,
		uint32_t *verified_with_hmac);

/**
 *  Returns simlock range to be verified from handle.
 *
 *  The data is extracted from attribute.
 *
 *  @param [in]  handle                  Verify session handle
 *  @param [out] start                   Simlock blob start position
 *  @param [out] len                     Simlock blob length
 *
 *  @returns int
 */
int rule_get_simlock_range(struct rule_verifier *handle, int *start, int *len);

#endif /* RULE_VERIFIER_H_ */
