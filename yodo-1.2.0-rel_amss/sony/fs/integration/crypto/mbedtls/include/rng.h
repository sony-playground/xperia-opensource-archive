/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef RNG_H_
#define RNG_H_

int mbedtls_rng(uint8_t *buf, char *additional, uint16_t len);

#endif /* RNG_H_*/
