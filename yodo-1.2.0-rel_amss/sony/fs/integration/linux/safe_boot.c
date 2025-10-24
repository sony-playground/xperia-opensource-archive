/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "partman.h"
#include "fcslog.h"
#include "fcserr.h"
#include "protocol_util.h"
#include "storage.h"
#include "write_image.h"
#include <ctype.h>
#include <string.h>
#include "safe_boot.h"
#include <stdbool.h>
#include <sys/wait.h>
#include <stdio.h>
#include "flash_handler.h"

#define XBL_CONFIG "xbl_config"

static int sb_flash_boot(int erase_type, char slot)
{
	int ret = FCSERR_OK;
	struct storage_ctx *sctx = NULL;
	struct storage_ctx *rdctx = NULL;
	struct storage_dir *directory = NULL;
	struct storage_dirent dent;
	size_t file_name_len, i;
	char *path = NULL;
	ssize_t bytes_read, file_size, partition_size;
	uint8_t *fbuf = NULL;
	char partition[NAME_MAX];
	bool secure_erase = true;
	size_t slot_count;
	bool has_slot;
	uint32_t offset = 0;

	/* Open folder where boot files are */
	directory = storage_opendir("boot/");
	if (directory == NULL) {
		FCS_LOG_ERR("Invalid dir\n");
		return -FCSERR_EINVAL;
	}

	do {
		/* Read next item in directory */
		ret = storage_readdir(directory, &dent);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("Failed to read directory (%d)\n", ret);
			goto exit;
		}

		/* Did we handle all files in directory yet? */
		if (strlen(dent.d_name) < 1)
			break;

		/* Just skip . and .. */
		if (*dent.d_name == '.')
			continue;

		/* Add folder boot, where files are kept, as prefix */
		if (asprintf(&path, "%s%s", "boot/", dent.d_name) < 0) {
			FCS_LOG_ERR("Failed to allocate memory\n");
			ret = -FCSERR_ENOMEM;
			goto exit;
		}

		/* Keep all chars until the first non alpha-numerical char */
		file_name_len = strlen(dent.d_name);
		for (i = 0; i < file_name_len; i++) {
			if (isalnum(dent.d_name[i]))
				partition[i] = dent.d_name[i];
			else
				break;
		}

		/*
		 * xbl_config has an underscore (non alpha-numerical character)
		 * and needs to be handled separately.
		 */
		if (strlen(XBL_CONFIG) <= file_name_len &&
				strncmp(dent.d_name,
					XBL_CONFIG,
					strlen(XBL_CONFIG)) == 0) {
			strncpy(partition, dent.d_name, strlen(XBL_CONFIG));
			i = strlen(XBL_CONFIG);
		}

		partition[i] = '\0';

		/* Check if there are slots for partition */
		ret = partman_has_slot(partition, &has_slot);
		if (ret != FCSERR_OK && ret != -FCSERR_ENOTF) {
			FCS_LOG_ERR("Failed to look up slot\n");
			goto exit;
		}

		if (ret == -FCSERR_ENOTF) {
			ret = partman_get_slot_count(&slot_count);
			if (ret != FCSERR_OK) {
				FCS_LOG_ERR("Failed to get slot count\n");
				goto exit;
			}

			/*
			 * PRELOADER is a virtual partition and not present
			 * in the partition table, so partman_has_slot will
			 * return -FCSERR_ENOTF for it. However, if slot_count
			 * is a non-zero value, set has_slot = true for
			 * PRELOADER.
			 */
			if (strlen(PRELOADER) > 0) {
				if (!strncmp(PRELOADER, partition,
						strlen(PRELOADER) + 1)) {
					if (slot_count)
						has_slot = true;
					ret = FCSERR_OK;
				}
			}
		}

		/*
		 * If we have slots append the slot suffix where bootloader
		 * should go.
		 */
		if (has_slot) {
			partition[i] = '_';
			i++;
			partition[i] = slot;
			i++;
			partition[i] = '\0';
		}

		/* Open partition */
		sctx = storage_open_by_name(NULL, partition);
		if (sctx == NULL) {
			FCS_LOG_ERR("Cannot open partition: %s\n", partition);
			ret = -FCSERR_ENOTF;
			goto exit;
		}

		/* Get partition size */
		partition_size = pu_get_part_size(sctx);
		if (partition_size < 0) {
			FCS_LOG_ERR("Failed to get partition size (%zd)\n",
					partition_size);
			ret = -FCSERR_EIO;
			goto exit;
		}

		/* Open the file to flash */
		rdctx = storage_open_by_name(STORAGE_RAM_NAME, path);
		if (!rdctx) {
			FCS_LOG_ERR("Failed to open file\n");
			ret = -FCSERR_ENOENT;
			goto exit;
		}

		/* Get size of file to flash */
		file_size = pu_get_part_size(rdctx);
		if (file_size < 0) {
			FCS_LOG_ERR("Failed to get file size (%zd)\n",
				file_size);
			ret = -FCSERR_EIO;
			goto exit;
		}

		/* Make sure file fits in partition */
		if (partition_size < file_size) {
			FCS_LOG_ERR("File does not fit in partition\n");
			ret = -FCSERR_EPART;
			goto exit;
		}

		if (erase_type != SB_ERASE_NONE) {
			if (erase_type == SB_ERASE_SECURE)
				secure_erase = true;
			else
				secure_erase = false;
			ret = partman_erase(partition, secure_erase);
			if (ret != FCSERR_OK) {
				FCS_LOG_ERR("Failed to erase partition: %s\n",
						partition);
				goto exit;
			}
		}

		/* Create buffer for file to flash */
		fbuf = malloc(file_size);
		if (fbuf == NULL) {
			FCS_LOG_ERR("Out of memory\n");
			ret = -FCSERR_ENOMEM;
			goto exit;
		}

		/* Read file into buffer */
		bytes_read = storage_read(rdctx, fbuf, file_size);
		if (bytes_read != file_size) {
			FCS_LOG_ERR("Failed to read file\n");
			ret = -FCSERR_EIO;
			goto exit;
		}

		ret = pre_flash_handler(sctx, partition, &offset);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("Pre-flash handler failed (%d)\n", ret);
			goto exit;
		}

		/* Write file to partition */
		ret = write_image(sctx, fbuf, offset, file_size);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("Failed to write image\n");
			goto exit;
		}

		/* Delete already handled boot items */
		(void)storage_unlink_by_name(STORAGE_RAM_NAME, path);

		/* Free and close everything for another turn in loop */
		storage_close(sctx);
		storage_close(rdctx);
		free(fbuf);
		free(path);
		sctx = NULL;
		rdctx = NULL;
		fbuf = NULL;
		path = NULL;
	} while (true);

	sctx = storage_open_by_name(NULL, NULL);
	if (sctx == NULL) {
		FCS_LOG_ERR("Failed to open device\n");
		goto exit;
	}

exit:
	if (rdctx)
		storage_close(rdctx);
	if (sctx)
		storage_close(sctx);
	if (directory)
		storage_closedir(directory);
	free(fbuf);
	free(path);

	return ret;
}

static int sb_write_to_ramdisk(uint8_t *buf, ssize_t buf_size)
{
	int res = FCSERR_OK;
	struct storage_ctx *rdctx = NULL; /* ramdisk context */
	ssize_t data_written;

	(void)storage_unlink_by_name(STORAGE_RAM_NAME, STORAGE_RAMDISK_NAME);
	rdctx = storage_open_by_name(STORAGE_RAM_NAME, STORAGE_RAMDISK_NAME);
	if (rdctx == NULL) {
		FCS_LOG_ERR("Fail to open %s\n", STORAGE_RAMDISK_NAME);
		return -FCSERR_EINVAL;
	}

	/* Write buffer content to ram disk */
	data_written = storage_write(rdctx, buf, buf_size);
	if (data_written != buf_size) {
		FCS_LOG_ERR("IO error: (%zd/%zd)\n", data_written, buf_size);
		res = -FCSERR_EIO;
	}

	storage_close(rdctx);

	return res;
}

int do_safe_boot_upgrade(uint8_t *buf, ssize_t buf_size, int erase_type,
		char slot)
{
	int res = FCSERR_OK;
	int status;
	pid_t pid;
	static char * const cmd[] = {"/system/bin/tar", "-xf",
		"/tmp/ldr/"STORAGE_RAMDISK_NAME, "-C", "/tmp/ldr/boot",
		(char *) 0};

	res = sb_write_to_ramdisk(buf, buf_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to write content to ramdisk\n");
		return res;
	}

	/* Untar the files */
	pid = fork();

	if (pid < 0) {
		printf("Fork failed\n");
		return -FCSERR_EINVAL;

	} else if (pid == 0) {
		/* Child process */
		res = execvp(cmd[0], cmd);
		FCS_LOG_ERR("Failed to untar archive\n");
		res = -FCSERR_EINVAL;
		goto exit;
	} else {
		/* Parent process */
		if ((waitpid(pid, &status, 0) < 0) || WIFSIGNALED(status) ||
				WEXITSTATUS(status) != 0) {
			FCS_LOG_ERR("Bad bootloader archive.\n");
			return -FCSERR_EINVAL;
		}
	}

	res = sb_flash_boot(erase_type, slot);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("Failed to flash boot\n");

exit:
	return res;
}
