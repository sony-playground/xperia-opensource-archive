/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_STORAGE_H_
#define FCS_STORAGE_H_

#include <stdint.h>
#include <unistd.h>

/*
 * Storage interface
 */

struct storage_ctx;
struct storage_dir;

struct storage_dirent {
	char d_name[PATH_MAX];
};

/*
 * whence defines for lseek
 */

/* The offset is set to offset bytes. */
#define STORAGE_SEEK_SET 1
/* The offset is set to its current location plus offset bytes. */
#define STORAGE_SEEK_CUR 2
/*  The offset is set to the size of the file plus offset bytes. */
#define STORAGE_SEEK_END 3

/*
 * flags for erase
 */

/* use secure erase */
#define STORAGE_ERASE_NORMAL 0
#define STORAGE_ERASE_SECURE 1

/*
 * Device names used by storage_open_by_name
 */
#define STORAGE_UFS_NAME  "ufs"
#define STORAGE_EMMC_NAME "emmc"
#define STORAGE_RAM_NAME  "ram"
#define STORAGE_HEAP_NAME "heap"
#define STORAGE_RPMB_NAME "rpmb"
#define STORAGE_RAMDISK_NAME "flash.bin"

/*
 * storage_init must be called to register devices
 * The function is implemented in the integration layer and initializes
 * the available storage interfaces.
 */
int storage_init(void);

/*
 * dev is set to required device and name is set to partition name. One
 * of the parameters could be set to NULL.
 */
struct storage_ctx *storage_open_by_name(const char *dev, const char *name);

int storage_close(struct storage_ctx *ctx);

ssize_t storage_read(struct storage_ctx *ctx, void *buf, ssize_t count);

ssize_t storage_write(struct storage_ctx *ctx, const void *buf, ssize_t count);

/*
 * reposition read, write, erase etc file offset
 */
off_t storage_lseek(struct storage_ctx *ctx, off_t offset, int whence);

/*
 * Erase memory from position set by storage_lseek and count number of bytes
 * forward.
 */
int storage_erase(struct storage_ctx *ctx, ssize_t count, int flags);

int storage_purge(void);

int storage_unlink_by_name(const char *dev, const char *name);

/*
 * Open device directory to iterate through available files/partitions.
 */
struct storage_dir *storage_opendir(const char *dev);

/*
 * Close dir context and free up resources.
 */
int storage_closedir(struct storage_dir *dir);

/*
 * Get the next entry in the device directory.
 */
int storage_readdir(struct storage_dir *dir, struct storage_dirent *dirent);

/*
 * Reread the partition table. If changes is made in the partition table this
 * function will update the partitions available.
 * If no name is provided all devices will be reread, otherwise only the one
 * specified.
 */
int storage_rrpart(const char *dev, const char *name);

/* get sector size */
ssize_t storage_get_ssz(struct storage_ctx *ctx);

/* Get name used to open device. The string returned should not be deallocated
 * and is valid as long as the context is open. The name returned could be NULL
 */
char *storage_get_name(struct storage_ctx *ctx);

int storage_get_gpt_info(struct storage_ctx *ctx, const char *name,
		void *buf, ssize_t *count);

ssize_t storage_get_storage_info(struct storage_ctx *ctx, void *buf,
		ssize_t *count);

int storage_set_bootdevice(struct storage_ctx *ctx, int lun);
#endif
