/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _DECODER_H_
#define _DECODER_H_

#include <stdlib.h>
#include <stdint.h>

enum asn_dec_rval_code_e {
	RC_OK,		/* Decoded successfully */
	RC_WMORE,	/* More data expected, call again */
	RC_FAIL		/* Failure to decode data */
};

typedef struct {
	enum asn_dec_rval_code_e code;
} asn_dec_rval_t;

struct asn_codec_ctx_s {
	int notused;
};

typedef asn_dec_rval_t (*asn_struct_decode_t)(
	const void *buffer,
	size_t size,
	void **struct_ptr);
typedef void (*asn_struct_free_t)(void *ptr);

typedef struct asn_TYPE_descriptor_s {
	asn_struct_decode_t decode;
	asn_struct_free_t free;
} asn_TYPE_descriptor_t;

asn_dec_rval_t ber_decode(struct asn_codec_ctx_s *opt_codec_ctx,
	struct asn_TYPE_descriptor_s *type_descriptor,
	void **struct_ptr,
	const void *buffer,
	size_t size);

void ASN_STRUCT_FREE(asn_TYPE_descriptor_t asn_DEF, void *ptr);

#endif /* _DECODER_H_ */

