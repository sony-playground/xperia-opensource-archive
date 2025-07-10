/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _SAFE_BOOT_H_
#define _SAFE_BOOT_H_

#include "storage.h"

#define SB_ERASE_NONE 0
#define SB_ERASE_NORMAL 1
#define SB_ERASE_SECURE 2

/*
 * Buffer contains all boot elements
 */
int do_safe_boot_upgrade(uint8_t *buf, ssize_t buf_size, int erase_type,
		char slot);

#endif
