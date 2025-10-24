/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_STORAGE_FILE_H_
#define FCS_STORAGE_FILE_H_

#include "storage_int.h"

/*
 * struct defining a connection to a memory
 */
struct storage_file_ctx {
	int fd;
	char *name;
};

struct storage_ctx *storage_file_open(const char *path, int flags, mode_t mode);

int storage_file_close(struct storage_ctx *ctx);

ssize_t storage_file_read(struct storage_ctx *ctx, void *buf, ssize_t count);

ssize_t storage_file_write(
	struct storage_ctx *ctx, const void *buf, ssize_t count);

off_t storage_file_lseek(struct storage_ctx *ctx, off_t offset, int whence);

int storage_file_unlink(const char *path);

/*
 * Read a number from file. The number is written to retval.
 * If overflow, retval becomes LLONG_MIN or LLONG_MAX.
 */
int storage_file_read_strtoll(const char *file, long long *retval);

int storage_file_fill(
	struct storage_ctx *ctx, unsigned char val, size_t count);

struct storage_dir *storage_file_opendir(const char *path);

int storage_file_closedir(struct storage_dir *dir);

int storage_file_readdir(
	struct storage_dir *dir, struct storage_dirent *dirent);

ssize_t storage_file_get_ssz(struct storage_ctx *ctx);

#endif
