/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_STORAGE_HEAP_H_
#define FCS_STORAGE_HEAP_H_

struct storage_ctx *storage_heap_open(const char *dev, const char *name);

int storage_heap_close(struct storage_ctx *ctx);

ssize_t storage_heap_read(struct storage_ctx *ctx, void *buf, ssize_t count);

ssize_t storage_heap_write(
	struct storage_ctx *ctx, const void *buf, ssize_t count);

off_t storage_heap_lseek(struct storage_ctx *ctx, off_t offset, int whence);

int storage_heap_unlink(const char *dev, const char *path);

#endif
