/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef SAKE_ALG_H
#define SAKE_ALG_H

#include "sake_engine_internal.h"

/*
 * sake_add_padding
 *
 * @param [in] data
 * @param [in] dataLen
 * @param [in] result
 * @param [in] sigLen
 *
 * @return The function returns FCSERR_OK on success
 *  and a negative error code otherwise.
 */
int sake_add_padding(
	const uint8_t *data, int32_t dataLen, uint8_t *result, int sigLen);

/*
 * sake_pub_key_encrypt
 *
 * @param [in] handle
 * @param [in] from
 * @param [in] length
 * @param [in] to
 * @param [in] nkey
 * @param [in] nlen
 * @param [in] ekey
 * @param [in] elen
 *
 * @return The function returns FCSERR_OK on success
 *  and a negative error code otherwise.
 */
int sake_pub_key_encrypt(struct sake_internal_handle *handle,
			 const uint8_t *from, int32_t length,
			 uint8_t *to, const uint8_t *nkey,
			 int32_t nlen, const uint8_t *ekey,
			 int32_t elen);

#endif /* SAKE_ALG_H */
