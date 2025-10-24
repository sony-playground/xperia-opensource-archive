/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "sake_hash.h"
#include "fcserr.h"

int sake_calculate_hash(struct sake_ext_hash_functions hash_functions,
			const uint8_t *src, uint32_t src_len,
			hash_type_t hash_type, uint32_t hash_digest_size,
			uint8_t *output)
{
	hash_context_t context = 0;
	int result = FCSERR_OK;


	do {
		result = hash_functions.hash_init(&context, hash_type);
		if (result != FCSERR_OK)
			break;

		result = hash_functions.hash_update(context, src, src_len);
		if (result != FCSERR_OK)
			break;

		result = hash_functions.hash_final(context, output,
						   hash_digest_size);
	} while (0);

	hash_functions.hash_deinit(context);
	SAKE_DBGDUMP(output, hash_digest_size);
	return result;
}
