/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_STORAGE_INT_H_
#define FCS_STORAGE_INT_H_

/*
 * Interface file to be used _internaly_ by storage generic and storage
 * integration implementations
 */

#include "storage.h"

/*
 * struct defining the configurabe part of the storage intefrace
 */
struct storage_interface {

	/*
	 * Open a memory for processing. name can be NULL to open the
	 * raw memory. If name is set it will open the by-name specified
	 * partition.
	 */
	struct storage_ctx *(*open)(const char *dev, const char *name);

	/*
	 * Close partition
	 */
	int (*close)(struct storage_ctx *ctx);
	ssize_t (*read)(struct storage_ctx *ctx, void *buf, ssize_t count);
	ssize_t (*write)(struct storage_ctx *ctx, const void *buf,
			 ssize_t count);
	off_t (*lseek)(struct storage_ctx *ctx, off_t offset, int whence);
	int (*erase)(struct storage_ctx *ctx, ssize_t count, int flags);
	int (*purge)(struct storage_ctx *ctx);
	int (*unlink)(const char *dev, const char *name);

	struct storage_dir *(*opendir)(const char *dev);
	int (*closedir)(struct storage_dir *dir);
	int (*readdir)(struct storage_dir *dir, struct storage_dirent *dirent);
	int (*rrpart)(const char *dev, const char *name);
	ssize_t (*get_ssz)(struct storage_ctx *ctx);
	int (*get_gpt_info)(const char *name, void *buf, ssize_t *count);
	ssize_t (*get_storage_info)(struct storage_ctx *ctx, void *buf,
			ssize_t *count);
	int (*set_bootdevice)(struct storage_ctx *ctx, int lun);
};

/*
 * struct to descibe the memory and how to access
 */
struct storage_desc {
	char *dev;
	struct storage_interface interface;
};

struct storage_ctx {
	char *name;
	struct storage_desc desc;
	void *ictx; /* implementation defined context */
};

/*
 * for now this is identical as storage_ctx but the ictx will be
 * different so we will separate storage_ctx and storage_dir for now
 */
struct storage_dir {
	struct storage_desc desc;
	void *ictx; /* implementation defined context */
};

int storage_add_dev(const struct storage_desc *desc);

int storage_remove_dev(const struct storage_desc *desc);

struct storage_desc *storage_get_desc(const char *dev);

int storage_set_name(struct storage_ctx *ctx, const char *name);

#endif
