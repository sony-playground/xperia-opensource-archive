/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_STORAGE_EMMC_H_
#define FCS_STORAGE_EMMC_H_

#include "emmc_int.h"

struct storage_ctx *storage_emmc_open(const char *dev, const char *name);

int storage_emmc_erase(struct storage_ctx *ctx, ssize_t count, int flags);

int storage_emmc_purge(struct storage_ctx *ctx);

struct storage_dir *storage_emmc_opendir(const char *dev);

int storage_emmc_rrpart(const char *dev, const char *name);

int storage_emmc_gpt_info(const char *name, void *buf, ssize_t *count);

ssize_t storage_emmc_get_storage_info(struct storage_ctx *ctx, void *buf,
		ssize_t *count);

#endif
