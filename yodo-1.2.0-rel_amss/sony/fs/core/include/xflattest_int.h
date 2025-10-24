/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef XFLATTEST_INT_H_
#define XFLATTEST_INT_H_

#include "xflattest.h"

int read_xfl_sec_data(struct xfl_sec_data *data);
int write_xfl_sec_data(struct xfl_sec_data *data);
int read_suid_data(uint8_t *buf, uint8_t bufsize);
int get_suid_len(void);
int init_xflattest(void);
int deinit_xflattest(void);

#endif
