/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef FCSTEST_DEFINES_H_
#define FCSTEST_DEFINES_H_

#define fcstest_container_of(ptr, type, member) ({              \
	const typeof(((type *)0)->member) * __mptr = (ptr);    \
	(type *)((char *)__mptr - offsetof(type, member)); })

#endif

