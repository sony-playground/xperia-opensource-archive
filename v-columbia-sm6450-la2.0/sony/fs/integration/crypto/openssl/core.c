/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <openssl/evp.h>

void core_crypto_setup(void)
{
	OpenSSL_add_all_algorithms();
}

void core_crypto_cleanup(void)
{
	EVP_cleanup();
}

