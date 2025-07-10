/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef LINUX_UTIL_H_
#define LINUX_UTIL_H_

#include <sys/types.h>

struct flash_info_data {
	char *name;
	char *buf;
	int buf_size;
	int index;
	char *type;
};

int fcs_read_memmap(off_t addr, uint8_t *buf, size_t len);
int fcs_read_memmap32(off_t addr, uint32_t *value);
int fcs_get_flash_info_data(const char *file_name,
		struct flash_info_data *fi_data);
/*
 * Fork and execute shell command with timeout in seconds
 * Set timeout to 0 to disable timeout
 */
int fcs_exec(char *const cmd[], int timeout);

#endif
