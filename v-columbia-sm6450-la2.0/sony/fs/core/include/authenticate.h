/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef AUTHENTICATE_H_
#define AUTHENTICATE_H_

#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

#define AUTH_LEVEL_INVALID (0xFF)
#define AUTH_LEVEL_NONE (0)
#define AUTH_LEVEL_PRODUCTION (1)
#define AUTH_LEVEL_CUSTOMER_SERVICE (2)

#define SAKE_SSN_INVALID (0xFFFF)
#define SAKE_SSN_PRODUCTION (1)
#define SAKE_SSN_CUSTOMER_SERVICE (0)
struct authenticate_ctx;

int authenticate_init(struct authenticate_ctx **ctx, uint16_t sake_ssn,
		      const char *rev_str, size_t rev_str_len);

void authenticate_destroy(struct authenticate_ctx *ctx);

int authenticate_generate_challenge(struct authenticate_ctx **ctx,
				    uint8_t *challenge_buf,
				    size_t *challenge_len);

int authenticate_verify_response(struct authenticate_ctx **ctx,
				 uint8_t *response_buf,
				 ssize_t response_buf_len);

int authenticate_get_sake_root_name(struct authenticate_ctx **ctx,
				    char *buf, size_t buf_len);

int authenticate_get_level(struct authenticate_ctx *ctx,
				uint8_t *auth_level);

#endif /* AUTHENTICATE_H_ */
