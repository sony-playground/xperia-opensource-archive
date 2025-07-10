/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "KeyStore.h"
#include "ks_parser.h"
#include "fcserr.h"

static asn_dec_rval_t keystore_decode(
		const void *buffer,
		size_t size,
		void **struct_ptr);
static void keystore_free(void *ptr);

asn_TYPE_descriptor_t asn_DEF_KeyStore = {
		.decode = keystore_decode,
		.free = keystore_free
};

static asn_dec_rval_t keystore_decode(
		const void *buffer,
		size_t size,
		void **struct_ptr)
{
	asn_dec_rval_t res_out = { .code = RC_OK };
	int res = -FCSERR_EINVAL;

	res = ks_parse((const uint8_t *)buffer,
		size,
		(struct ks_main **)struct_ptr);
	if (res != FCSERR_OK)
		res_out.code = RC_FAIL;
	return res_out;
}

static void keystore_free(void *ptr)
{
	ks_free((struct ks_main *)ptr);
}

