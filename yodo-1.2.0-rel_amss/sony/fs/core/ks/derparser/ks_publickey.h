/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _KS_PUBLICKEY_H_
#define _KS_PUBLICKEY_H_

#include <stdint.h>

/* KeyStorePublicKey */
struct ks_publickey {
	uint32_t size;
	uint8_t *buf;
};

#endif /* _KS_PUBLICKEY_H_ */

