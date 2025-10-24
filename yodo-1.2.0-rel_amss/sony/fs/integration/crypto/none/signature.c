/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "signature.h"
#include "fcserr.h"

/**
 * Exported functions
 */

int signature_verify(
		uint8_t *certchain_buffer,
		size_t   certchain_buffer_length,
		uint8_t *signature,
		size_t   signature_length,
		uint8_t *hash,
		size_t   hash_length)
{
	(void)certchain_buffer;
	(void)certchain_buffer_length;
	(void)signature;
	(void)signature_length;
	(void)hash;
	(void)hash_length;

	return FCSERR_OK;
}

int signature_verify_rsassa_pss(
		uint8_t *certchain_buffer,
		size_t   certchain_buffer_length,
		uint8_t *signature,
		size_t   signature_length,
		uint8_t *hash,
		size_t   hash_length)
{
	(void)certchain_buffer;
	(void)certchain_buffer_length;
	(void)signature;
	(void)signature_length;
	(void)hash;
	(void)hash_length;

	return FCSERR_OK;
}

