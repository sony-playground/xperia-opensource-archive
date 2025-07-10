/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "decoder.h"

asn_dec_rval_t ber_decode(struct asn_codec_ctx_s *opt_codec_ctx,
	struct asn_TYPE_descriptor_s *type_descriptor,
	void **struct_ptr,
	const void *buffer,
	size_t size)
{
	asn_dec_rval_t res = { .code = RC_OK };

	if (opt_codec_ctx != NULL ||
			type_descriptor == NULL ||
			struct_ptr == NULL ||
			buffer == NULL ||
			size == 0) {
		res.code = RC_FAIL;
		goto exit;
	}

	if (type_descriptor->decode == NULL) {
		res.code = RC_FAIL;
		goto exit;
	}

	res = type_descriptor->decode(buffer, size, struct_ptr);

exit:
	return res;
}

void ASN_STRUCT_FREE(asn_TYPE_descriptor_t asn_DEF, void *ptr)
{
	if (ptr == NULL)
		return;
	if (asn_DEF.free == NULL)
		return;

	asn_DEF.free(ptr);
}

