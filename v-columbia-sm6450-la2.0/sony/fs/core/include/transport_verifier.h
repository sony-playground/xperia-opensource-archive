/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef TRANSPORT_VERIFIER_H_
#define TRANSPORT_VERIFIER_H_

#include "rule_types.h"
#include <stdlib.h>
#include <stdbool.h>

struct transport_verifier;

/**
 *  Initialize transport verifier session.
 *
 *  @param [out] handle                  Returned handle
 *  @param [in]  payload                 A pointer to the payload buffer
 *  @param [in]  payload_len             Length, in bytes, of the payload
 *
 *  @returns int
 */
int transport_init(struct transport_verifier **handle,
	uint8_t *payload,
	size_t payload_len);

/**
 *  Cleanup transport verifier session.
 *
 *  The function will release allocated resources.
 *
 *  @param [in]  handle                  Verify session handle
 *
 *  @returns none
 */
void transport_deinit(struct transport_verifier *handle);

/**
 *  Transport session has more hash values.
 *
 *  @returns bool
 */
bool transport_has_more(struct transport_verifier *handle);

/**
 *  Verify hash towards current transport session hash.
 *
 *  @param [in]  handle                  Verify session handle
 *  @param [in]  hash                    A pointer to the hash value
 *  @param [in]  hash_len                Length, in bytes, of the hash
 *
 *  @returns int
 */
int transport_verify_hash(struct transport_verifier *handle,
	uint8_t *hash,
	size_t hash_len);

#endif /* TRANSPORT_VERIFIER_H_ */
