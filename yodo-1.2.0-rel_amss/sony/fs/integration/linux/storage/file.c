/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "storage.h"
#include "storage_int.h"
#include "storage_file.h"
#include "fcslog.h"
#include "fcserr.h"

#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

#include <linux/fs.h>

#define FILE_READ_BUF_SIZE             128
#define FILE_FILL_SIZE                4096

struct storage_file_dir {
	DIR *d;
};

/*
 * internal integration function, this do not implement storage.h
 */
struct storage_ctx *storage_file_open(
	const char *path, int flags, mode_t mode)
{
	struct storage_ctx *ctx = NULL;
	struct storage_file_ctx *fctx = NULL;

	if (!path) {
		FCS_LOG_ERR("invalid input\n");
		return NULL;
	}

	ctx = calloc(1, sizeof(struct storage_ctx));
	if (!ctx) {
		FCS_LOG_ERR("could not allocate memory\n");
		return NULL;
	}

	fctx = calloc(1, sizeof(struct storage_file_ctx));
	if (!fctx) {
		FCS_LOG_ERR("could not allocate memory\n");
		goto err;
	}

	ctx->ictx = fctx;

	fctx->fd = open(path, flags, mode);
	if (fctx->fd == -1) {
		FCS_LOG_ERR("could not open device %s\n", path);
		goto err;
	}

	fctx->name = calloc(1, strlen(path) + 1);
	if (!fctx->name) {
		FCS_LOG_ERR("could not allocate memory\n");
		goto err;
	}
	memcpy(fctx->name, path, strlen(path) + 1);

	return ctx;

err:
	free(ctx);
	if (fctx)
		free(fctx->name);
	free(fctx);
	return NULL;
}


int storage_file_close(struct storage_ctx *ctx)
{
	struct storage_file_ctx *fctx = NULL;
	int ret = FCSERR_OK;

	if (!ctx) {
		FCS_LOG_ERR("invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	fctx = (struct storage_file_ctx *)ctx->ictx;

	if (fctx && (fctx->fd > 0)) {
		if (close(fctx->fd)) {
			FCS_LOG_ERR("unable to close fd\n");
			ret = -FCSERR_EIO;
		}
	}

	if (fctx)
		free(fctx->name);
	free(fctx);
	free(ctx);

	return ret;
}

ssize_t storage_file_read(struct storage_ctx *ctx, void *buf, ssize_t count)
{
	struct storage_file_ctx *fctx;

	if (!ctx) {
		FCS_LOG_ERR("invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	fctx = (struct storage_file_ctx *)ctx->ictx;
	if (!fctx) {
		FCS_LOG_ERR("invalid fctx\n");
		return -FCSERR_EINVAL;
	}

	if (count == 0)
		return 0;

	if (!buf) {
		FCS_LOG_ERR("invalid buffer\n");
		return -FCSERR_ENOBUFS;
	}

	return read(fctx->fd, buf, count);
}

ssize_t storage_file_write(
	struct storage_ctx *ctx, const void *buf, ssize_t count)
{
	struct storage_file_ctx *fctx;

	if (!ctx) {
		FCS_LOG_ERR("invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	fctx = (struct storage_file_ctx *)ctx->ictx;
	if (!fctx) {
		FCS_LOG_ERR("invalid fctx\n");
		return -FCSERR_EINVAL;
	}

	if (count == 0)
		return 0;

	if (!buf) {
		FCS_LOG_ERR("invalid buffer\n");
		return -FCSERR_ENOBUFS;
	}

	return write(fctx->fd, buf, count);
}

off_t storage_file_lseek(struct storage_ctx *ctx, off_t offset, int whence)
{
	int f_whence;
	off_t res;
	struct storage_file_ctx *fctx;

	if (!ctx) {
		FCS_LOG_ERR("invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	fctx = (struct storage_file_ctx *)ctx->ictx;
	if (!fctx) {
		FCS_LOG_ERR("invalid fctx\n");
		return -FCSERR_EINVAL;
	}

	switch (whence) {
	case STORAGE_SEEK_SET:
		f_whence = SEEK_SET;
		break;
	case STORAGE_SEEK_CUR:
		f_whence = SEEK_CUR;
		break;
	case STORAGE_SEEK_END:
		f_whence = SEEK_END;
		break;
	default:
		FCS_LOG_ERR("invalid whence\n");
		return -FCSERR_EINVAL;
	}

	res = lseek(fctx->fd, offset, f_whence);

	if (res == -1) {
		FCS_LOG_ERR("lseek failed, errno (%d)\n", errno);
		return -errno;
	}

	return res;
}

int storage_file_unlink(const char *path)
{
	int res;

	if (!path) {
		FCS_LOG_ERR("invalid input\n");
		return -FCSERR_EINVAL;
	}

	res = unlink(path);

	if (res == -1) {
		FCS_LOG_ERR("unlink failed, errno (%d)\n", errno);
		return -errno;
	}

	return res;
}

int storage_file_read_strtoll(const char *file, long long *retval)
{
	char sbuf[FILE_READ_BUF_SIZE + 1] = {0};
	int res;
	int fd;

	if (!file || !retval) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	fd = open(file, O_RDONLY);
	if (fd == -1) {
		FCS_LOG_ERR("Failed to open %s (%d)\n", file, errno);
		return -FCSERR_EIO;
	}

	res = read(fd, sbuf, FILE_READ_BUF_SIZE);
	if (res == -1) {
		close(fd);
		FCS_LOG_ERR("Failed to read %s (%d)\n", file, errno);
		return -FCSERR_EIO;
	}

	res = close(fd);
	if (res == -1) {
		FCS_LOG_ERR("Failed to close %s (%d)\n", file, errno);
		return -FCSERR_EIO;
	}

	*retval = strtoll(sbuf, NULL, 10);
	return FCSERR_OK;
}

int storage_file_fill(
	struct storage_ctx *ctx, unsigned char val, size_t count)
{
	unsigned char buf[FILE_FILL_SIZE] = {val};
	size_t n = count;
	int res;

	if (!ctx) {
		FCS_LOG_ERR("invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	while (n > sizeof(buf)) {
		res = storage_file_write(ctx, buf, sizeof(buf));
		if (res != sizeof(buf)) {
			FCS_LOG_ERR("write failed (%d)\n", errno);
			return res;
		}
		n -= sizeof(buf);
	}
	return storage_file_write(ctx, buf, n);
}

struct storage_dir *storage_file_opendir(const char *path)
{
	struct storage_dir *ctx = NULL;
	struct storage_file_dir *dctx = NULL;

	if (!path) {
		FCS_LOG_ERR("invalid path\n");
		return NULL;
	}

	ctx = calloc(1, sizeof(struct storage_dir));
	if (!ctx) {
		FCS_LOG_ERR("could not allocate memory\n");
		return NULL;
	}

	dctx = calloc(1, sizeof(struct storage_file_dir));
	if (!dctx) {
		FCS_LOG_ERR("could not allocate memory\n");
		goto err;
	}

	ctx->ictx = dctx;
	dctx->d = opendir(path);
	if (dctx->d == NULL) {
		FCS_LOG_ERR("could not opendir %s\n", path);
		goto err;
	}

	return ctx;

err:
	free(dctx);
	free(ctx);
	return NULL;
}

int storage_file_closedir(struct storage_dir *dir)
{
	int res = FCSERR_OK;

	if (!dir) {
		FCS_LOG_ERR("invalid dir\n");
		return -FCSERR_EINVAL;
	}

	res = closedir(((struct storage_file_dir *)(dir->ictx))->d);
	if (res) {
		FCS_LOG_ERR("Failed to close directory: (errno=%d)\n", errno);
		res = -FCSERR_EIO;
	}

	free(dir->ictx);
	free(dir);

	return res;
}

int storage_file_readdir(struct storage_dir *dir, struct storage_dirent *dirent)
{
	struct dirent *dent;
	struct storage_file_dir *dctx;

	if (!dir || !dir->ictx) {
		FCS_LOG_ERR("invalid dir\n");
		return -FCSERR_EINVAL;
	}

	if (!dirent) {
		FCS_LOG_ERR("invalid dirent\n");
		return -FCSERR_EINVAL;
	}

	dctx = (struct storage_file_dir *)dir->ictx;
	errno = 0;
	dent = readdir(dctx->d);

	if (!dent) {
		dirent->d_name[0] = '\0';
		if (errno) {
			FCS_LOG_ERR("readdir failed (errno=%d)\n", errno);
			return -FCSERR_EIO;
		}
	} else {
		strlcpy(dirent->d_name, dent->d_name, NAME_MAX + 1);
	}

	return FCSERR_OK;
}

ssize_t storage_file_get_ssz(struct storage_ctx *ctx)
{
	struct storage_file_ctx *fctx;
	int ssz = 0;

	if (!ctx) {
		FCS_LOG_ERR("invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	fctx = (struct storage_file_ctx *)ctx->ictx;
	if (!fctx) {
		FCS_LOG_ERR("invalid fctx\n");
		return -FCSERR_EINVAL;
	}

	/* get sector size */
	if (ioctl(fctx->fd, BLKSSZGET, &ssz)) {
		FCS_LOG_ERR("ioctl, get sector size falied (%d)\n", errno);
		return -FCSERR_EIO;
	}

	return ssz;
}
