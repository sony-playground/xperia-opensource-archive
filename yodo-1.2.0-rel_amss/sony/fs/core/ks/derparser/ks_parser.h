/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _KS_PARSER_H_
#define _KS_PARSER_H_

#include "ks_main.h"
#include <stdint.h>

int ks_parse(const uint8_t *buffer,
		size_t size,
		struct ks_main **keystore_ptr);

void ks_free(struct ks_main *keystore);

#endif /* _KS_PARSER_H_ */

