/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "storage.h"
#include "storage_int.h"
#include "storage_file.h"
#include "fcslog.h"
#include "fcserr.h"
#include "gpt.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <libgen.h>

#include <linux/mmc/core.h>
#include <linux/mmc/ioctl.h>
#include <linux/mmc/mmc.h>
#include <linux/major.h>
#include <linux/fs.h>
#include <asm-generic/ioctl.h>

#define STORAGE_EMMC_PATH "/dev/block/mmcblk0"
#define STORAGE_EMMC_PATH_BOOT0 "/dev/block/mmcblk0boot0"
#define STORAGE_EMMC_PATH_BOOT1 "/dev/block/mmcblk0boot1"
#define STORAGE_EMMC_BY_NAME_PATH "/dev/block/bootdevice/by-name/"

#define STORAGE_EMMC_OPEN_FLAGS	(O_RDWR)
#define GPT_INFO_SIZE		(512*34)

/*
 * MMC_SWITCH_MODE_* defines from include/linux/mmc/mmc.h in kernel not
 * present in the included mmc.h (the userspace api)
 */
#define MMC_SWITCH_MODE_CMD_SET      0x00 /* Change the command set */
#define MMC_SWITCH_MODE_SET_BITS     0x01 /* Set bits which are 1 in value */
#define MMC_SWITCH_MODE_CLEAR_BITS   0x02 /* Clear bits which are 1 in value */
#define MMC_SWITCH_MODE_WRITE_BYTE   0x03 /* Set target to value */

/*
 * EXT_CSD_* defines from include/linux/mmc/mmc.h in kernel not present
 * in the included mmc.h (the userspace api)
 */
#define EXT_CSD_FLUSH_CACHE            32 /* W */
#define EXT_CSD_SANITIZE_START        165 /* W */
#define EXT_CSD_PART_CONFIG           179 /* W */

/* Internal partition configuration defines */
#define EXT_CSD_PARTITION_CONFIG_CLR    0x38 /* Boot selection bits (3-5) */
#define EXT_CSD_PARTITION_CONFIG_SHIFT  3    /* Bit shift for boot selection */

/*
 * R1_SWITCH_ERROR define from include/linux/mmc/mmc.h in kernel
 */
#define R1_SWITCH_ERROR          (1 << 7) /* sx, c */

#define MMC_BLK_SIZE                  512
#define MMC_BLK_SHIFT                   9

#define MMC_EXT_CSD_SIZE              512

#define MAX_ERASE_CHUNK               0x40000
#define MAX_SEND_STATUS_RETRIES       5

#define SEC_TRIM_MARK_BLOCKS          0x80000001
#define SEC_TRIM_ERASE_BLOCKS         0x80008000
#define TRIM_ERASE                    0x00000001


static int storage_emmc_get_sysll(
	struct storage_file_ctx *ctx, char *file, long long *retval)
{
	char lnkp[PATH_MAX + 1] = {0}; /* readlink do not null terminate */
	char sysp[PATH_MAX + 1];
	char *base;
	int res;

	if (!ctx || !file || !retval) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = readlink(ctx->name, lnkp, PATH_MAX);
	if (res == -1) {
		FCS_LOG_ERR("Failed to read link %s (%d)\n", ctx->name, errno);
		return -FCSERR_ENOENT;
	}

	base = basename(lnkp);
	res = snprintf(sysp, PATH_MAX + 1, "/sys/block/mmcblk0/%s/%s",
		       base, file);
	if (res < 0) {
		FCS_LOG_ERR("Failed to create path %s (%d)\n", ctx->name,
			errno);
		return -FCSERR_EINVAL;
	}

	return storage_file_read_strtoll(sysp, retval);
}

static int storage_emmc_send_status(const int fd, uint32_t *response)
{
	struct mmc_ioc_cmd mmc_cmd = {
		0, 0, 0, 0, {0, 0, 0, 0}, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	if (!response) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	mmc_cmd.opcode = MMC_SEND_STATUS;
	mmc_cmd.arg = (1 << 16);
	mmc_cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;

	if (ioctl(fd, MMC_IOC_CMD, &mmc_cmd)) {
		FCS_LOG_ERR("ioctl() MMC_IOC_CMD MMC_SEND_STATUS failed: %s\n",
			strerror(errno));
		return -FCSERR_EIO;
	}

	*response = mmc_cmd.response[0];
	return FCSERR_OK;
}

static int storage_emmc_send_switch_cmd(
	const int fd, uint32_t op, uint32_t index, uint8_t value)
{
	struct mmc_ioc_cmd mmc_cmd = {
		0, 0, 0, 0, {0, 0, 0, 0}, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint32_t status = 0;
	uint32_t i = 0;
	int res;

	FCS_LOG_INF("Sending MMC_SWITCH index %u(0x%x) value %u(0x%x)\n",
		index, index, value, value);

	mmc_cmd.write_flag = 1;
	mmc_cmd.opcode = MMC_SWITCH;
	mmc_cmd.arg = op << 24;

	if (op == MMC_SWITCH_MODE_CMD_SET)
		mmc_cmd.arg |= value & 0x07;
	else {
		mmc_cmd.arg |= index << 16;
		mmc_cmd.arg |= value << 8;
	}
	mmc_cmd.flags = MMC_RSP_R1B | MMC_CMD_AC;

	if (ioctl(fd, MMC_IOC_CMD, &mmc_cmd)) {
		FCS_LOG_ERR("ioctl() MMC_IOC_CMD  MMC_SWITCH failed: %s\n",
			strerror(errno));
		return -FCSERR_EIO;
	}

	do {
		res = storage_emmc_send_status(fd, &status);
		if (res != FCSERR_OK)
			return res;
		if (!(status & R1_SWITCH_ERROR))
			break;
	} while (i++ < MAX_SEND_STATUS_RETRIES);

	if (status & R1_SWITCH_ERROR) {
		FCS_LOG_ERR("MMC_STAT_SWITCH_ERROR\n");
		return -FCSERR_EIO;
	}

	return FCSERR_OK;
}

/*
 * implements storage_open_by_name
 */
struct storage_ctx *storage_emmc_open(const char *dev, const char *name)
{
	char *path = NULL;
	struct storage_ctx *ctx;
	int res = 0;

	if (dev && strncmp(dev, STORAGE_EMMC_NAME, strlen(STORAGE_EMMC_NAME))) {
		FCS_LOG_INF("invalid device\n");
		return NULL;
	}

	if (name) {
		const char partitionTableFileName = '0';

		if (strlen(name) == 1 && name[0] == partitionTableFileName)
			res = asprintf(&path, "%s",
					STORAGE_EMMC_PATH);
		else if ((strlen(PRELOADER) > 0) &&
			 (strncmp(name, PRELOADER, strlen(PRELOADER)) == 0)) {
			const char slot = name[strlen(name) - 1];
			/* Use slot a by default */
			if (slot == 'b')
				res = asprintf(&path, "%s",
						STORAGE_EMMC_PATH_BOOT1);
			else
				res = asprintf(&path, "%s",
						STORAGE_EMMC_PATH_BOOT0);
		} else
			res = asprintf(&path, "%s%s",
					STORAGE_EMMC_BY_NAME_PATH, name);

	} else {
		res = asprintf(&path, "%s",
				STORAGE_EMMC_PATH);
	}

	if (res == -1) {
		FCS_LOG_ERR("could not allocate memory\n");
		return NULL;
	}

	ctx = storage_file_open(path, STORAGE_EMMC_OPEN_FLAGS, 0);
	if (!ctx) {
		FCS_LOG_ERR("could not create ctx\n");
		goto err;
	}

	if (storage_set_name(ctx, name)) {
		FCS_LOG_ERR("could not set name\n");
		storage_close(ctx);
		free(ctx);
		ctx = NULL;
		goto err;
	}

	ctx->desc = *(storage_get_desc(STORAGE_EMMC_NAME));

err:
	if (name)
		free(path);
	return ctx;
}

/*
 * Implements storage_purge
 */
int storage_emmc_purge(struct storage_ctx *ctx)
{
	int ret = FCSERR_OK;
	(void) ctx;
	/* Dummy implementation temporary */
	FCS_LOG_INF("Dummy implementation of purge function!\n");
	return ret;
}

/*
 * Implements storage_erase
 */
int storage_emmc_erase(struct storage_ctx *ctx, long long count, int flags)
{
	long long pos;
	long long tpos;
	int ret;
	struct mmc_ioc_cmd mmc_cmd = {
		0, 0, 0, 0, {0, 0, 0, 0}, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	struct storage_file_ctx *fctx;
	long long bstart;
	long long bend;
	long long bsize;
	int fd = -1;
	void *ibuf = NULL;
	void *tbuf = NULL;
	char *path = NULL;

	if (!ctx) {
		FCS_LOG_ERR("Invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	fctx = (struct storage_file_ctx *)ctx->ictx;
	if (!fctx) {
		FCS_LOG_ERR("Invalid fctx\n");
		return -FCSERR_EINVAL;
	}

	if (count == 0)
		return FCSERR_OK;

	/* Get current position */
	pos = storage_file_lseek(ctx, 0, STORAGE_SEEK_CUR);
	if (pos < 0) {
		FCS_LOG_ERR("lseek failed\n");
		return -FCSERR_EIO;
	}

	if (memcmp(fctx->name, STORAGE_EMMC_PATH,
		    strlen(STORAGE_EMMC_PATH)) == 0) {
		bstart = 0;
		bsize = 0;
	} else {
		/* Query sys about partition properties */
		ret = storage_emmc_get_sysll(fctx, "start", &bstart);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("Get bstart failed: (%d)\n", ret);
			return ret;
		}
		ret = storage_emmc_get_sysll(fctx, "size", &bsize);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("Get bsize failed: (%d)\n", ret);
			return ret;
		}

		/* Check bounds */
		if (pos + count > (bsize << MMC_BLK_SHIFT)) {
			FCS_LOG_ERR("Erase out of part, size %lld erase %lld\n",
				bsize << MMC_BLK_SHIFT, (pos + count));
			return -FCSERR_EOOB;
		}
	}

	/* Read pre non-aligned bytes */
	if (pos % MMC_BLK_SIZE) {
		tpos = storage_file_lseek(
			ctx, pos - (pos % MMC_BLK_SIZE), STORAGE_SEEK_SET);
		if (tpos != pos - (pos % MMC_BLK_SIZE)) {
			FCS_LOG_ERR("lseek failed\n");
			ret = -FCSERR_EIO;
			goto exit;
		}
		ibuf = calloc(MMC_BLK_SIZE, 1);
		if (ibuf == NULL) {
			FCS_LOG_ERR("calloc failed\n");
			ret = -FCSERR_ENOMEM;
			goto exit;
		}
		ret = storage_file_read(ctx, ibuf, (pos % MMC_BLK_SIZE));
		if (ret != (pos % MMC_BLK_SIZE)) {
			FCS_LOG_ERR("read failed (%d, %d)\n", ret, errno);
			ret = -FCSERR_EIO;
			goto exit;
		}
	}

	/* Read trailing non-aligned bytes */
	if ((pos + count) % MMC_BLK_SIZE) {
		tpos = storage_file_lseek(ctx, pos + count, STORAGE_SEEK_SET);
		if (tpos != pos + count) {
			FCS_LOG_ERR("file seek failed (%lld, %lld)\n",
				tpos, pos + count);
			ret = -FCSERR_EIO;
			goto exit;
		}
		tbuf = calloc(MMC_BLK_SIZE, 1);
		if (tbuf == NULL) {
			FCS_LOG_ERR("calloc failed\n");
			ret = -FCSERR_ENOMEM;
			goto exit;
		}
		ret = storage_file_read(
			ctx, tbuf,
			MMC_BLK_SIZE - ((pos + count) % MMC_BLK_SIZE));
		if (ret != MMC_BLK_SIZE - ((pos + count) % MMC_BLK_SIZE)) {
			FCS_LOG_ERR("read failed (%d)\n", ret);
			ret = -FCSERR_EIO;
			goto exit;
		}
	}

	if (ctx->name) {
		/*
		 * Make sure fctx->fd cache is flushed.
		 * Flush can take a very long time if done on the whole
		 * mmcblk0, so do it only if there is a valid partition name.
		 */
		ret = ioctl(fctx->fd, BLKFLSBUF, 0);
		if (ret) {
			FCS_LOG_ERR("ioctl() BLKFLSBUF failed: %s\n",
					strerror(errno));
			ret = -FCSERR_EIO;
			goto exit;
		}

		if ((strlen(PRELOADER) > 0) &&
		    (strncmp(ctx->name, PRELOADER, strlen(PRELOADER)) == 0)) {
			const char slot = ctx->name[strlen(ctx->name) - 1];
			/* Use slot a by default */
			if (slot == 'b') {
				ret = asprintf(&path, "%s",
						STORAGE_EMMC_PATH_BOOT1);
			} else {
				ret = asprintf(&path, "%s",
						STORAGE_EMMC_PATH_BOOT0);
			}
		} else
			ret = asprintf(&path, "%s", STORAGE_EMMC_PATH);
	} else
		ret = asprintf(&path, "%s", STORAGE_EMMC_PATH);

	/* ioctl below requires us to operate on raw flash */
	fd = open(path, STORAGE_EMMC_OPEN_FLAGS | O_NONBLOCK);
	if (fd == -1) {
		FCS_LOG_ERR("Unable to open %s\n", path);
		ret = -FCSERR_EIO;
		goto exit;
	}

	bstart += (pos >> MMC_BLK_SHIFT);
	bend = bstart + ((count - 1) >> MMC_BLK_SHIFT);

	do {
		/* CMD35 - ERASE_GROUP_START */
		mmc_cmd.write_flag = 1;
		mmc_cmd.opcode = MMC_ERASE_GROUP_START;
		mmc_cmd.arg = bstart;
		mmc_cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;
		ret = ioctl(fd, MMC_IOC_CMD, &mmc_cmd);
		if (ret) {
			FCS_LOG_ERR(
				"ioctl,MMC_IOC_CMD ERASE GROUP START failed: %s\n",
				strerror(errno));
			ret = -FCSERR_EIO;
			goto exit;
		}

		/* CMD36 - ERASE_GROUP_END */
		mmc_cmd.opcode = MMC_ERASE_GROUP_END;
		mmc_cmd.arg =
			bstart + ((bend - bstart > MAX_ERASE_CHUNK) ?
				MAX_ERASE_CHUNK : bend - bstart);
		ret = ioctl(fd, MMC_IOC_CMD, &mmc_cmd);
		if (ret) {
			FCS_LOG_ERR(
				"ioctl() MMC_IOC_CMD ERASE GROUP END failed: %s\n",
				strerror(errno));
			ret = -FCSERR_EIO;
			goto exit;
		}

		/* CMD38 - ERASE */
		mmc_cmd.opcode = MMC_ERASE;
		mmc_cmd.flags = MMC_RSP_R1B | MMC_CMD_AC;

		if (flags & STORAGE_ERASE_SECURE) {
			FCS_LOG_INF("Start secure trim\n");
			mmc_cmd.arg = SEC_TRIM_MARK_BLOCKS;
			ret = ioctl(fd, MMC_IOC_CMD, &mmc_cmd);
			if (ret) {
				FCS_LOG_ERR("Secure TRIM step 1 failed: %s\n",
					strerror(errno));
				ret = -FCSERR_EIO;
				goto exit;
			}
			mmc_cmd.arg = SEC_TRIM_ERASE_BLOCKS;
			ret = ioctl(fd, MMC_IOC_CMD, &mmc_cmd);
			if (ret) {
				FCS_LOG_ERR(
					"Secure TRIM step 2 failed: %s\n",
					strerror(errno));
				ret = -FCSERR_EIO;
				goto exit;
			}
		} else {
			FCS_LOG_INF("Start regular trim\n");
			mmc_cmd.arg = TRIM_ERASE;
			ret = ioctl(fd, MMC_IOC_CMD, &mmc_cmd);
			if (ret) {
				FCS_LOG_ERR("TRIM erase failed: %s\n",
					strerror(errno));
				ret = -FCSERR_EIO;
				goto exit;
			}
		}
		bstart += MAX_ERASE_CHUNK;
	} while (bend - bstart >= 0);

	FCS_LOG_INF("Start flush cache\n");
	ret = storage_emmc_send_switch_cmd(
		fd, MMC_SWITCH_MODE_SET_BITS, EXT_CSD_FLUSH_CACHE, 1);
	if (ret) {
		FCS_LOG_ERR("Flush cache failed (%d)\n", ret);
		goto exit;
	}

	if (ctx->name) {
		/*
		 * This flush is needed to make sure that read - erase - read
		 * sequence works.
		 * Flush can take a very long time if done on the whole
		 * mmcblk0, so do it only if there is a valid partition name.
		 */
		FCS_LOG_INF("Start flush block device buffers\n");
		ret = ioctl(fd, BLKFLSBUF, 0);
		if (ret) {
			FCS_LOG_ERR("ioctl() BLKFLSBUF failed: %s\n",
					strerror(errno));
			ret = -FCSERR_EIO;
			goto exit;
		}
	}

	/* Write back */
	if (ibuf) {
		tpos = storage_file_lseek(
			ctx, pos - (pos % MMC_BLK_SIZE), STORAGE_SEEK_SET);
		if (tpos < 0) {
			FCS_LOG_ERR("lseek failed\n");
			ret = -FCSERR_EIO;
			goto exit;
		}
		ret = storage_file_write(ctx, ibuf, (pos % MMC_BLK_SIZE));
		if (ret != (pos % MMC_BLK_SIZE)) {
			FCS_LOG_ERR("write failed (%d)\n", ret);
			ret = -FCSERR_EIO;
			goto exit;
		}
	}

	if (tbuf) {
		tpos = storage_file_lseek(ctx, pos + count, STORAGE_SEEK_SET);
		if (tpos != pos + count) {
			FCS_LOG_ERR("file seek failed (%lld, %lld)\n",
				tpos, pos + count);
			ret = -FCSERR_EIO;
			goto exit;
		}
		ret = storage_file_write(
			ctx, tbuf,
			MMC_BLK_SIZE - ((pos + count) % MMC_BLK_SIZE));
		if (ret != MMC_BLK_SIZE - ((pos + count) % MMC_BLK_SIZE)) {
			FCS_LOG_ERR("write failed (%d)\n", ret);
			ret = -FCSERR_EIO;
			goto exit;
		}
	}

	ret = FCSERR_OK;
exit:
	/* Reset the file pointer */
	tpos = storage_file_lseek(ctx, pos, STORAGE_SEEK_SET);
	if (pos != tpos) {
		FCS_LOG_ERR("file seek failed (%lld)\n", pos);
		ret = -FCSERR_EIO;
	}

	if (fd > 0)
		close(fd);
	free(ibuf);
	free(tbuf);
	free(path);
	FCS_LOG_INF("Erase done\n");

	return ret;
}

struct storage_dir *storage_emmc_opendir(const char *dev)
{
	struct storage_dir *ctx;

	if (dev && strncmp(dev, STORAGE_EMMC_NAME, strlen(STORAGE_EMMC_NAME))) {
		FCS_LOG_INF("invalid device\n");
		return NULL;
	}

	/*
	 * If NULL ptr is provided & emmc driver is registred we assume that
	 * the user wants emmc
	 */
	ctx = storage_file_opendir(STORAGE_EMMC_BY_NAME_PATH);
	if (!ctx) {
		FCS_LOG_ERR("could not create ctx\n");
		goto err;
	}
	ctx->desc = *(storage_get_desc(STORAGE_EMMC_NAME));

err:
	return ctx;
}

int storage_emmc_rrpart(const char *dev, const char *name)
{
	int fd;
	int ret = FCSERR_OK;

	(void)name;
	if (dev && strncmp(dev, STORAGE_EMMC_NAME, strlen(STORAGE_EMMC_NAME))) {
		FCS_LOG_INF("invalid device\n");
		return -FCSERR_ENODEV;
	}

	fd = open(STORAGE_EMMC_PATH, STORAGE_EMMC_OPEN_FLAGS);
	if (fd == -1) {
		FCS_LOG_ERR("unable to open %s\n", STORAGE_EMMC_PATH);
		return -FCSERR_EIO;
	}

	if (ioctl(fd, BLKRRPART, 0)) {
		FCS_LOG_ERR("ioctl failed: errno: %d\n", errno);
		ret = -FCSERR_ERRPART;
	}
	close(fd);

	/*
	 * make sure the partition table re read execution
	 * has time to finish.
	 */
	usleep(50000);

	return ret;
}

/*
 * Get gpt info. Call with buf == NULL to get the size of the gpt info.
 */
int storage_emmc_gpt_info(const char *name, void *buf, ssize_t *count)
{
	int ret = FCSERR_OK;
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

	/* Make sure only raw device is opened */
	if (strncmp(name, "0", sizeof("0"))) {
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
		FCS_LOG_ERR("Failed to read %zd bytes, got %zd.\n", *count,
			data_read);
		ret = -FCSERR_EIO;
		goto exit;
	}

	/* Restore file pointer */
	temporary = storage_file_lseek(ctx, original, STORAGE_SEEK_SET);
	if (temporary < 0) {
		FCS_LOG_ERR("IO Error: %s\n", strerror(errno));
		ret = -FCSERR_EIO;
	}
exit:
	storage_close(ctx);

	return ret;
}

/*
 * implements storage_get_storage_info
 */
ssize_t storage_emmc_get_storage_info(struct storage_ctx *ctx, void *buf,
		ssize_t *count)
{
	int ret = FCSERR_OK;

	struct mmc_ioc_cmd mmc_cmd = {
		0, 0, 0, 0, {0, 0, 0, 0}, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	struct storage_file_ctx *fctx;
	uint8_t ext_csd[MMC_EXT_CSD_SIZE];


	if (!ctx) {
		FCS_LOG_ERR("invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	fctx = (struct storage_file_ctx *)ctx->ictx;
	if (!fctx) {
		FCS_LOG_ERR("invalid fctx\n");
		return -FCSERR_EINVAL;
	}

	if (buf == NULL) {
		*count = MMC_EXT_CSD_SIZE;
		goto exit;
	}

	if (*count != MMC_EXT_CSD_SIZE) {
		FCS_LOG_ERR("Trying to read wrong size\n");
		return -FCSERR_EINVAL;
	}

	mmc_cmd.write_flag = 0;
	mmc_cmd.opcode = MMC_SEND_EXT_CSD;
	mmc_cmd.arg = 0;
	mmc_cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;
	mmc_cmd.blksz = 512;
	mmc_cmd.blocks = 1;

	mmc_ioc_cmd_set_data(mmc_cmd, ext_csd);
	ret = ioctl(fctx->fd, MMC_IOC_CMD, &mmc_cmd);

	if (ret) {
		FCS_LOG_ERR("ioctl,MMC_SEND_EXT_CSD failed: %s\n",
			strerror(errno));
		ret = -FCSERR_EIO;
		goto exit;
	}
	memcpy(buf, ext_csd, MMC_EXT_CSD_SIZE);

exit:
	return ret;
}

