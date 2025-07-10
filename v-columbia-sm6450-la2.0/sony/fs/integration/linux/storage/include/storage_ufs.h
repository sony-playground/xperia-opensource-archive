/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_STORAGE_UFS_H_
#define FCS_STORAGE_UFS_H_

struct storage_ctx *storage_ufs_open(const char *dev, const char *name);

int storage_ufs_erase(struct storage_ctx *ctx, ssize_t count, int flags);

int storage_ufs_purge(struct storage_ctx *ctx);

struct storage_dir *storage_ufs_opendir(const char *dev);

int storage_ufs_rrpart(const char *dev, const char *name);

int storage_ufs_gpt_info(const char *name, void *buf, ssize_t *count);

ssize_t storage_ufs_get_storage_info(struct storage_ctx *ctx, void *buf,
		ssize_t *count);

int storage_ufs_set_bootdevice(struct storage_ctx *ctx, int lun);
#endif
