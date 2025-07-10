/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef __SONY_LIB_C__H__
#define __SONY_LIB_C__H__

#include <stddef.h>

size_t strlen(const char *str);
size_t strlcat(char *dest, const char *src, size_t size);
char *strnstr(const char *in, const char *str, size_t max_len);
size_t strlcpy(char *dest, const char *src, size_t size);

#endif
