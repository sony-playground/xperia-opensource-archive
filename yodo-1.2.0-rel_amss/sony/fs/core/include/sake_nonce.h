/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef SAKE_NONCE_H_
#define SAKE_NONCE_H_

#include <stdint.h>
#include <string.h>

#define SAKE_NONCE_LEN 20

/* nonce buffer must be at least SAKE_NONCE_LEN bytes long */
int sake_get_nonce(uint8_t *nonce, size_t nonce_len);

#endif
