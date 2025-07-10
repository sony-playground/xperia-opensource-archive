/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "storage.h"
#include "storage_int.h"
#include "storage_file.h"
#include "fcslog.h"
#include "fcserr.h"
#include "ufs_int.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <libgen.h>
#include <linux/fs.h>

#define STORAGE_UFS_PATH "/dev/block/sda" /* Start of first LUN */
#define STORAGE_UFS_BY_NAME_PATH "/dev/block/bootdevice/by-name/"

#define STORAGE_UFS_OPEN_FLAGS       (O_RDWR)

#define LINUX_BLK_SIZE               512
#define GPT_INFO_SIZE		(4096*6)

#define MIN(x, y) ((x) < (y)?(x):(y))

static int storage_ufs_rrpart_internal(const char *name)
{
	int fd;
	int ret = FCSERR_OK;

	if (name == NULL) {
		FCS_LOG_ERR("Broken input parameters\n");
		return -FCSERR_EINVAL;
	}

	fd = open(name, STORAGE_UFS_OPEN_FLAGS);
	if (fd == -1) {
		if (errno == 2) {
			/* Not an error, exit loop */
			FCS_LOG_INF("No more LUNs\n");
			return FCSERR_OK;
		}
		FCS_LOG_ERR("unable to open %s\n", name);
		return -FCSERR_EIO;
	}

	if (ioctl(fd, BLKRRPART, 0)) {
		FCS_LOG_ERR("ioctl failed: errno: %d\n", errno);
		ret = -FCSERR_ERRPART;
	}
	close(fd);

	/*
	 * make sure the partition table re read execution
	 * has time to finish
	 */
	usleep(50000);

	return ret;
}

static int storage_ufs_get_sysll(
	struct storage_file_ctx *ctx, char *file, long long *retval)
{
	char lnkp[PATH_MAX + 1] = {0};
	char sysp[PATH_MAX + 1] = {0};
	char *base;
	char lun_alphabet;
	int res;

	if (!ctx || !file || !retval) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/*
	 * If ctx->name is /dev/block/sdX, where X is a lower case letter,
	 * then we are trying to access lun X raw.
	 */
	if (strlen(ctx->name) == strlen(STORAGE_UFS_PATH) &&
		strncmp(ctx->name, STORAGE_UFS_PATH,
			strlen(STORAGE_UFS_PATH) - 1) == 0) {
		lun_alphabet = ctx->name[strlen(ctx->name)-1];
		if (lun_alphabet >= 'a' && lun_alphabet <= 'j') {
			base = basename(ctx->name);
			res = snprintf(sysp, PATH_MAX + 1, "/sys/block/%s/%s",
					base, file);
			if (res < 0) {
				FCS_LOG_ERR("Failed to create path %s (%d)\n",
						ctx->name, errno);
				return -FCSERR_EINVAL;
			}
		}
	/* Otherwise try to access partition on a lun */
	} else {
		res = readlink(ctx->name, lnkp, PATH_MAX);

		if (res == -1) {
			FCS_LOG_ERR("Failed to read link %s (%d)\n",
					ctx->name, errno);
			return -FCSERR_ENOENT;
		}

		base = basename(lnkp);
		lun_alphabet = base[2]; /* extract char sdX */

		res = snprintf(sysp, PATH_MAX + 1, "/sys/block/sd%c/%s/%s",
				lun_alphabet, base, file);
		if (res < 0) {
			FCS_LOG_ERR("Failed to create path %s (%d)\n",
					ctx->name, errno);
			return -FCSERR_EINVAL;
		}
	}

	return storage_file_read_strtoll(sysp, retval);
}

static ssize_t storage_ufs_get_device_descriptor(struct storage_ctx *ctx,
		void *buf, ssize_t buf_sz)
{
	int ret = FCSERR_OK;
	struct storage_file_ctx *fctx = NULL;

	if (buf == NULL || buf_sz == 0 || ctx == NULL) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	fctx = (struct storage_file_ctx *)ctx->ictx;
	if (!fctx) {
		FCS_LOG_ERR("Invalid context\n");
		return -FCSERR_EINVAL;
	}

	if (buf_sz < DEVICE_DESCRIPTOR_LEN) {
		FCS_LOG_ERR("Buffer too small\n");
		return -FCSERR_EINVAL;
	}

	ret = ufs_ioctl_get_device_desc(fctx->fd, buf, buf_sz);
	if (ret < 0)
		FCS_LOG_ERR("Fail to get device descriptor\n");

	return ret;
}

static ssize_t storage_ufs_get_unit_descriptor(struct storage_ctx *ctx,
		void *buf, ssize_t buf_sz)
{
	int ret = FCSERR_OK;
	struct storage_file_ctx *fctx = NULL;

	if (buf == NULL || buf_sz == 0 || ctx == NULL) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	fctx = (struct storage_file_ctx *)ctx->ictx;
	if (!fctx) {
		FCS_LOG_ERR("Invalid context\n");
		return -FCSERR_EINVAL;
	}

	if (buf_sz < UNIT_DESCRIPTOR_LEN) {
		FCS_LOG_ERR("Buffer too small\n");
		return -FCSERR_EINVAL;
	}

	ret = ufs_ioctl_get_unit_desc(fctx->fd, buf, buf_sz);
	if (ret < 0)
		FCS_LOG_ERR("Fail to get unit descriptor\n");

	return ret;
}

static int storage_ufs_get_lun_count(unsigned int *luns)
{
	int ret;
	uint8_t *lbuf = NULL;
	struct storage_ctx *local_ctx = NULL;

	if (!luns) {
		FCS_LOG_ERR("bad input parameter\n");
		return -FCSERR_EINVAL;
	}

	lbuf = malloc(DEVICE_DESCRIPTOR_LEN);
	if (!lbuf) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	local_ctx = storage_open_by_name(NULL, NULL);
	if (!local_ctx) {
		FCS_LOG_ERR("IO Error\n");
		ret = -FCSERR_EIO;
		goto exit;
	}

	/* Get the device descriptor */
	ret = storage_ufs_get_device_descriptor(local_ctx, lbuf,
			DEVICE_DESCRIPTOR_LEN);
	if (ret < 0) {
		FCS_LOG_ERR("Failed to read device descriptor\n");
		goto exit;
	}

	/* Parse device descriptor to read number of luns */
	*luns = (lbuf[B_NUMBER_LU_OFFSET] & 0xFF);
	if (*luns > MAX_LUN_COUNT) {
		FCS_LOG_ERR("Insane number of luns: (%u)\n", *luns);
		ret = -FCSERR_EIO;
		goto exit;
	}

exit:
	if (local_ctx != NULL)
		storage_close(local_ctx);
	free(lbuf);

	return ret;
}

/*
 * implements storage_open_by_name
 */
struct storage_ctx *storage_ufs_open(const char *dev, const char *name)
{
	char *path = NULL;
	struct storage_ctx *ctx;
	char *internal_name = (char *)name;

	if (dev && strncmp(dev, STORAGE_UFS_NAME, strlen(STORAGE_UFS_NAME))) {
		FCS_LOG_INF("invalid device\n");
		return NULL;
	}

	/* Open LUN 0 if name is NULL */
	if (!name)
		internal_name = "0";

	/* If one digit "name" we want to access a LUN raw */
	if (strlen(internal_name) == 1 && internal_name[0] >= '0' &&
			internal_name[0] < (MAX_LUN_COUNT + '0')) {
		/* We want to open a LUN raw */
		char lundev[2] = "?";

		lundev[0] = ('a' + internal_name[0] - '0');
		if (asprintf(&path, "%s%s", "/dev/block/sd", lundev) < 0) {
			FCS_LOG_ERR("Failed to aquire path\n");
			return NULL;
		}
	/* Otherwise it's a partition */
	} else if (asprintf(&path, "%s%s",
			STORAGE_UFS_BY_NAME_PATH, internal_name) == -1) {
		FCS_LOG_ERR("could not allocate memory\n");
		return NULL;
	}

	ctx = storage_file_open(path, STORAGE_UFS_OPEN_FLAGS, 0);
	if (!ctx) {
		FCS_LOG_ERR("could not create ctx\n");
		goto err;
	}

	if (storage_set_name(ctx, internal_name)) {
		FCS_LOG_ERR("could not set name\n");
		storage_close(ctx);
		free(ctx);
		ctx = NULL;
		goto err;
	}

	ctx->desc = *(storage_get_desc(STORAGE_UFS_NAME));

err:
	free(path);
	return ctx;
}

/*
 * Implements purge
 */
int storage_ufs_purge(struct storage_ctx *ctx)
{
	int ret = FCSERR_OK;
	struct storage_file_ctx *fctx;
	uint8_t *buf;
	struct storage_ctx *local_ctx;

	if (!ctx) {
		FCS_LOG_ERR("invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	fctx = (struct storage_file_ctx *)ctx->ictx;
	if (!fctx) {
		FCS_LOG_ERR("invalid fctx\n");
		return -FCSERR_EINVAL;
	}

	if (fsync(fctx->fd)) {
		FCS_LOG_ERR("fsync failed:(%s)\n", strerror(errno));
		/* Not a critical error, try to do purge anyway */
	}

	buf = malloc(UNIT_DESCRIPTOR_LEN);
	if (buf == NULL) {
		FCS_LOG_ERR("Failed to allocate memory\n");
		return -FCSERR_ENOMEM;
	}

	/* Open lun 0 */
	local_ctx = storage_open_by_name(NULL, "0");
	if (local_ctx == NULL) {
		FCS_LOG_ERR("Failed to open lun 0\n");
		ret = -FCSERR_ENOTF;
		goto exit;
	}

	ret = storage_ufs_get_unit_descriptor(local_ctx,
			buf, UNIT_DESCRIPTOR_LEN);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get unit descriptor for lun 0\n");
		goto exit;
	}

	/*
	 * If the UFS is provisioned with bProvisioningType=3, there is
	 * no need to do purge.
	 */
	if (buf[B_PROVISIONING_TYPE_OFFSET] == 3)
		goto exit;

	ret = ufs_ioctl_purge(fctx->fd);
	if (ret < 0)
		FCS_LOG_ERR("Purge failed\n");

exit:
	if (local_ctx)
		storage_close(local_ctx);
	free(buf);
	return ret;
}

/*
 * Implements storage_erase
 */
int storage_ufs_erase(struct storage_ctx *ctx, long long count, int flags)
{
	int ret = FCSERR_OK;
	struct storage_file_ctx *fctx;
	long long bsize;
	long long pos;
	long long range[2];

	unsigned long int req = BLKDISCARD;

	if (!ctx) {
		FCS_LOG_ERR("Invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	fctx = (struct storage_file_ctx *)ctx->ictx;
	if (!fctx) {
		FCS_LOG_ERR("Invalid fctx\n");
		return -FCSERR_EINVAL;
	}

	/* Only support erase on whole block sizes*/
	if (count % LINUX_BLK_SIZE) {
		FCS_LOG_ERR("Erase only supports whole sector sizes\n");
		return -FCSERR_EINVAL;
	}

	/* Get current position, pos needs to be aligned to block */
	pos = storage_file_lseek(ctx, 0, STORAGE_SEEK_CUR);
	if (pos < 0 || pos % LINUX_BLK_SIZE) {
		FCS_LOG_ERR("lseek failed\n");
		return -FCSERR_EIO;
	}

	/*
	 * Query sys about partition properties. Linux considers sectors to be
	 * 512 bytes long independently of the devices real block size.
	 */
	ret = storage_ufs_get_sysll(fctx, "size", &bsize);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Get sector size failed: (%d)\n", ret);
		return ret;
	}

	/* check bounds */
	if (pos + count > (bsize * LINUX_BLK_SIZE)) {
		FCS_LOG_ERR(
			"Erase out of partition, size (%lld), erase (%lld)\n",
			bsize * LINUX_BLK_SIZE, (pos + count));
		return -FCSERR_EOOB;
	}

	FCS_LOG_INF("Start flush block device buffers\n");
	if (fsync(fctx->fd))
		FCS_LOG_ERR("fsync failed:(%s)\n", strerror(errno));

	range[0] = pos;
	range[1] = count;

	ret = ioctl(fctx->fd, req, range);

	if (ret) {
		FCS_LOG_ERR("BLKDISCARD failed:(%s)\n",
				strerror(errno));
		return ret;
	}

	if (flags & STORAGE_ERASE_SECURE) {
		ret = ufs_ioctl_purge(fctx->fd);
		if (ret < 0)
			FCS_LOG_ERR("Purge failed\n");
	}

	FCS_LOG_INF("Erase done\n");

	return ret;
}

struct storage_dir *storage_ufs_opendir(const char *dev)
{
	struct storage_dir *ctx;

	if (dev && strncmp(dev, STORAGE_UFS_NAME, strlen(STORAGE_UFS_NAME))) {
		FCS_LOG_INF("invalid device\n");
		return NULL;
	}

	/*
	 * If NULL ptr is provided & ufs driver is registred we assume that
	 * the user wants ufs
	 */
	ctx = storage_file_opendir(STORAGE_UFS_BY_NAME_PATH);
	if (!ctx) {
		FCS_LOG_ERR("could not create ctx\n");
		goto err;
	}
	ctx->desc = *(storage_get_desc(STORAGE_UFS_NAME));

err:
	return ctx;
}

int storage_ufs_rrpart(const char *dev, const char *name)
{
	char lun_alphabet;
	char lun_raw_path[] = STORAGE_UFS_PATH;
	int lun;
	int ret = FCSERR_OK;

	if (dev && strncmp(dev, STORAGE_UFS_NAME, strlen(STORAGE_UFS_NAME))) {
		FCS_LOG_INF("invalid device\n");
		return -FCSERR_ENODEV;
	}

	/* Only update one lun */
	if (name) {
		lun = atoi(name);
		if (lun >= MAX_LUN_COUNT) {
			FCS_LOG_ERR("Above max number of lun:s\n");
			ret = -FCSERR_EINVAL;
			goto exit;
		}
		lun_alphabet = 'a' + lun;
		lun_raw_path[strlen(lun_raw_path)-1] = lun_alphabet;

		ret = storage_ufs_rrpart_internal(lun_raw_path);
		goto exit;
	}

	/* Cycle through all LUN:s */
	for (lun_alphabet = 'a'; lun_alphabet <= 'j'; lun_alphabet++) {
		lun_raw_path[strlen(lun_raw_path)-1] = lun_alphabet;
		ret = storage_ufs_rrpart_internal(lun_raw_path);
		if (ret)
			break;
	}

exit:
	return ret;
}

/*
 * Get gpt info. Call with buf == NULL to get the size of the gpt info.
 */
int storage_ufs_gpt_info(const char *name, void *buf, ssize_t *count)
{
	int ret = FCSERR_OK;
	unsigned int luns;
	off_t original, temporary;
	struct storage_ctx *ctx = NULL;
	ssize_t data_read;

	if (name == NULL || count == NULL) {
		FCS_LOG_ERR("Broken input parameters\n");
		return -FCSERR_EINVAL;
	}

	if (buf == NULL) {
		*count = GPT_INFO_SIZE;
		return FCSERR_OK;
	}

	if (*count != GPT_INFO_SIZE) {
		FCS_LOG_ERR("Trying to read wrong size\n");
		return -FCSERR_EINVAL;
	}

	if (storage_ufs_get_lun_count(&luns) < 0) {
		FCS_LOG_ERR("Failed to read number of luns\n");
		return -FCSERR_EIO;
	}

	/* Make sure we only read a raw LUN */
	if (strlen(name) != 1 || name[0] < '0' ||
			name[0] >= (luns + '0')) {
		FCS_LOG_ERR("Invalid parameter\n");
		return -FCSERR_EINVAL;
	}

	ctx = storage_open_by_name(NULL, name);
	if (!ctx) {
		FCS_LOG_ERR("Failed to open device\n");
		return -FCSERR_EIO;
	}

	/* save position */
	original = storage_file_lseek(ctx, 0, STORAGE_SEEK_CUR);
	if (original < 0) {
		FCS_LOG_ERR("IO Error\n");
		ret = -FCSERR_EIO;
		goto exit;
	}

	/* Set file pointer to start of partition/lun */
	temporary = storage_file_lseek(ctx, 0, STORAGE_SEEK_SET);
	if (temporary < 0) {
		FCS_LOG_ERR("Failed to reset file pointer\n");
		ret = -FCSERR_EIO;
		goto exit;
	}

	/* Read gpt table */
	data_read = storage_file_read(ctx, buf, GPT_INFO_SIZE);
	if (data_read != *count) {
		FCS_LOG_ERR("Failed to read data: (%zd)\n", data_read);
		ret = -FCSERR_EIO;
		goto exit;
	}

	/* Restore file pointer */
	temporary = storage_file_lseek(ctx, original, STORAGE_SEEK_SET);
	if (temporary < 0) {
		FCS_LOG_ERR("IO Error\n");
		ret = -FCSERR_EIO;
		goto exit;
	}
exit:
	storage_close(ctx);

	return ret;
}

ssize_t storage_ufs_get_storage_info(struct storage_ctx *ctx, void *buf,
		ssize_t *count)
{
	int ret = FCSERR_OK;
	uint8_t *lbuf = NULL;
	unsigned int i, index, number_of_luns = 0;
	struct storage_ctx *local_ctx = NULL;
	char lun[2];

	if (!count) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	lbuf = malloc(DEVICE_DESCRIPTOR_LEN);
	if (lbuf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}
	/* Get the device descriptor */
	ret = storage_ufs_get_device_descriptor(ctx, lbuf,
			DEVICE_DESCRIPTOR_LEN);
	if (ret < 0) {
		FCS_LOG_ERR("Failed to read device descriptor\n");
		goto exit;
	}

	/* Parse device descriptor to read number of luns */
	number_of_luns = (lbuf[B_NUMBER_LU_OFFSET] & 0xFF);
	if (number_of_luns > MAX_LUN_COUNT) {
		FCS_LOG_ERR("Insane number of luns: (%u)\n", number_of_luns);
		ret = -FCSERR_EIO;
		goto exit;
	}

	if (!buf) {
		*count = DEVICE_DESCRIPTOR_LEN +
			number_of_luns * UNIT_DESCRIPTOR_LEN;
		goto exit;
	}

	if (*count < DEVICE_DESCRIPTOR_LEN) {
		FCS_LOG_ERR("Too small buffer allocated\n");
		ret = -FCSERR_EINVAL;
		goto exit;
	}
	/* Copy device descriptor to caller buf */
	memcpy(buf, lbuf, DEVICE_DESCRIPTOR_LEN);

	/* Loop through all luns and read out unit descriptors */
	index = DEVICE_DESCRIPTOR_LEN;
	for (i = 0; i < number_of_luns; i++) {
		/* Check boundaries of caller buffer */
		if (index + UNIT_DESCRIPTOR_LEN > *count) {
			FCS_LOG_ERR("Too small buffer allocated\n");
			ret = -FCSERR_EINVAL;
			goto exit;
		}

		/* Open each lun raw */
		snprintf(lun, sizeof(lun), "%u", i);
		local_ctx = storage_open_by_name(NULL, lun);
		if (local_ctx == NULL) {
			FCS_LOG_ERR("Failed to open lun: %s\n", lun);
			ret = -FCSERR_ENOTF;
			goto exit;
		}

		ret = storage_ufs_get_unit_descriptor(local_ctx,
				(uint8_t *)buf + index, UNIT_DESCRIPTOR_LEN);
		index += UNIT_DESCRIPTOR_LEN;
		if (storage_close(local_ctx) == FCSERR_OK)
			local_ctx = NULL;
	}

exit:
	if (local_ctx)
		storage_close(local_ctx);
	free(lbuf);

	return ret;
}

int storage_ufs_set_bootdevice(struct storage_ctx *ctx, int lun)
{
	int ret = FCSERR_OK;
	struct storage_file_ctx *fctx = NULL;

	if (ctx == NULL) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}
	fctx = (struct storage_file_ctx *)ctx->ictx;

	ret = ufs_ioctl_set_bootdevice(fctx->fd, lun);
	if (ret < 0)
		FCS_LOG_ERR("Failed to set lun %d (%d)\n", lun, ret);

	return ret;
}

