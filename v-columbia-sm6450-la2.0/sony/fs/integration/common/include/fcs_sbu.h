/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_SBU_H_
#define FCS_SBU_H_

#include <stdint.h>

/* Partition guids */
struct sbu_list {
	uint8_t *key;
	size_t key_length;
};

extern int num_boot_partitions;
extern struct sbu_list boot_partitions[];

#endif
