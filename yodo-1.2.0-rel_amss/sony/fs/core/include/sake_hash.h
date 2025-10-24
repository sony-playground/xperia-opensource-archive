/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef SAKE_HASH_H_
#define SAKE_HASH_H_

#include "sake_engine.h"
#include "sake_engine_internal.h"

/*
 *Calculate hash
 *
 * @param [in] hash_functions
 *
 * @param [in] src
 * @param [in] src_len
 * @param [in] hash_type
 * @param [in] hash_digest_size
 * @param [in] output
 *
 * @return The function returns FCSERR_OK on success
 *  and a negative error code otherwise.
 */
int sake_calculate_hash(struct sake_ext_hash_functions hash_functions,
			const uint8_t *src, uint32_t src_len,
			hash_type_t hash_type, uint32_t hash_digest_size,
			uint8_t *output);


#endif /* SAKE_HASH_H_ */
