/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_PARTMAN_H_
#define FCS_PARTMAN_H_

#include <stdint.h>
#include <unistd.h>
#include "storage.h"
#include <stdbool.h>

/*
 * erase overlapping/changed partitions.
 * buf contains the new gpt
 * lun is set to lun name (byname) or NULL if not applicable
 */
int partman_erase_overlap(uint8_t *buf, ssize_t buf_sz, const char *lun);

int partman_prepare_secondary_gpt(struct storage_ctx *rdctx,
		uint8_t *buf, ssize_t buf_sz, const char *lun);

int partman_patch_primary_gpt(uint8_t *buf, ssize_t buf_sz, const char *lun);

int partman_get_gpt_info(uint8_t *buf, ssize_t *buf_sz, const char *name);

int partman_gpt_sanity_check(uint8_t *buf, ssize_t buf_sz, const char *name,
		int *nbr_part);

int partman_erase(const char *pname, bool secure_erase);

int partman_erase_sector(int lun,
		ssize_t start, ssize_t end, bool secure_erase);

int partman_has_slot(const char *part_name, bool *has_slot);

int partman_get_slot_count(size_t *slot_count);
#endif
