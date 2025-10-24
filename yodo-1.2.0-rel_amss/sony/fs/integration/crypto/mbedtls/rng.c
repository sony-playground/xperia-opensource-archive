/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <mbedtls/ctr_drbg.h>
#include <stdio.h>
#include <string.h>
#include <fcslog.h>
#include <fcserr.h>

int mbedtls_rng(uint8_t *buf, char *additional, uint16_t len)
{
	int ret;
	mbedtls_ctr_drbg_context ctr_drbg;

	if (buf == NULL || additional == NULL || len == 0) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	mbedtls_ctr_drbg_init(&ctr_drbg);

	ret = mbedtls_ctr_drbg_random_with_add(&ctr_drbg, buf, len,
			(const unsigned char *)additional, strlen(additional));
	if (ret != 0)
		FCS_LOG_ERR("mbedtls_ctr_drbg_random failed: %d\n", ret);

	mbedtls_ctr_drbg_free(&ctr_drbg);
	return ret;
}

