/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef EXT_MODEM_H_
#define EXT_MODEM_H_

#include <stdint.h>

int ext_modem_probe(void);
int ext_modem_fuse(uint8_t config);

#endif
