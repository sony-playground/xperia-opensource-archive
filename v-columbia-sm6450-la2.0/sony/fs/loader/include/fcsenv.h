/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCSENV_H_
#define FCSENV_H_

#include "rule_types.h"
#include <stdlib.h>
#include <stdint.h>

/* Retrieve platform id */
int fcsenv_get_platformid(uint8_t *buf, size_t len);
int fcsenv_get_platformid_len(void);

#endif
