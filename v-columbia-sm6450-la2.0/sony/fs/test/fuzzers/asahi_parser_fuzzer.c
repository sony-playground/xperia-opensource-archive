/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdlib.h>
#include <stdint.h>

#include "asahi_parser.h"

static void check_chain(void *handle)
{
	uint8_t *chain;
	size_t sz;

	if (asahiparser_get_certificate_chain(handle, &chain, &sz) >= 0)
		free(chain);
}

static void check_algo(void *handle)
{
	uint8_t algo;

	asahiparser_get_signature_algorithm(handle, &algo);
}

static void check_rsa_sig(void *handle)
{
	uint8_t *sig;
	size_t sz;

	asahiparser_get_rsa_signature(handle, &sig, &sz);
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
	void *handle;

	if (asahiparser_init(&handle, (uint8_t *) Data, Size) >= 0) {
		check_chain(handle);
		check_algo(handle);
		check_rsa_sig(handle);
		asahiparser_deinit(handle);
	}

	return 0;
}
