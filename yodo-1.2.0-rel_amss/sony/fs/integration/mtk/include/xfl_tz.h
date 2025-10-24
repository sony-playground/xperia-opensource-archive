/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef XFL_TZ_H_
#define XFL_TZ_H_


/*
 * This file defines common read functionality for fuses and rpmb.
 * The interface is not thread safe
 */
enum xfl_tz_read_type {
	RPMB,
	FUSE,
	SUID
};

int xfl_tz_read(enum xfl_tz_read_type type, uint8_t index,
		uint8_t *data, uint32_t size);

#endif
