/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "storage.h"
#include "storage_int.h"
#include "storage_file.h"
#include "fcslog.h"
#include "fcserr.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define STORAGE_RAM_PATH "/tmp/ldr/"

#define STORAGE_RAM_OPEN_FLAGS (O_SYNC | O_RDWR | O_CREAT)
#define STORAGE_RAM_OPEN_MODE (0600)

/*
 * implements storage_open_by_name
 */
struct storage_ctx *storage_ram_open(const char *dev, const char *name)
{
	char *path = NULL;
	struct storage_ctx *ctx;

	if (!dev || !name) {
		FCS_LOG_INF("invalid input\n");
		return NULL;
	}

	if (strncmp(dev, STORAGE_RAM_NAME, strlen(STORAGE_RAM_NAME))) {
		FCS_LOG_INF("invalid device\n");
		return NULL;
	}

	if (asprintf(&path, "%s%s", STORAGE_RAM_PATH, name) == -1) {
		FCS_LOG_ERR("could not allocate memory\n");
		return NULL;
	}

	ctx = storage_file_open(
		path, STORAGE_RAM_OPEN_FLAGS, STORAGE_RAM_OPEN_MODE);
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

	ctx->desc = *(storage_get_desc(STORAGE_RAM_NAME));

err:
	free(path);
	return ctx;
}

int storage_ram_unlink(const char *dev, const char *name)
{
	char *path = NULL;

	if (!dev || !name) {
		FCS_LOG_INF("invalid input\n");
		return -FCSERR_ENOENT;
	}

	if (strncmp(dev, STORAGE_RAM_NAME, strlen(STORAGE_RAM_NAME))) {
		FCS_LOG_INF("invalid device\n");
		return -FCSERR_ENOENT;
	}

	if (asprintf(&path, "%s%s", STORAGE_RAM_PATH, name) == -1) {
		FCS_LOG_ERR("could not allocate memory\n");
		return -FCSERR_ENOMEM;
	}

	return storage_file_unlink(path);
}

struct storage_dir *storage_ram_opendir(const char *dev)
{
	struct storage_dir *ctx;
	char *path = NULL;

	if (!dev) {
		FCS_LOG_ERR("invalid device\n");
		return NULL;
	}

	if (asprintf(&path, "%s%s", STORAGE_RAM_PATH, dev) == -1) {
		FCS_LOG_ERR("Could not allocate memory\n");
		return NULL;
	}

	ctx = storage_file_opendir(path);
	if (!ctx) {
		FCS_LOG_ERR("Could not create ctx\n");
		goto err;
	}

	ctx->desc = *(storage_get_desc(STORAGE_RAM_NAME));

err:
	free(path);

	return ctx;
}
