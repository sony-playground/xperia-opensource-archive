/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "storage.h"
#include "storage_int.h"
#include "fcslist.h"
#include "fcslog.h"
#include "fcserr.h"

#include <string.h>
#include <stdlib.h>

struct storage_entry {
	struct storage_desc desc;
	struct list_entry list;
};
static LIST(storage_dev_list);

int storage_add_dev(const struct storage_desc *desc)
{
	struct storage_entry *ent;

	if (!desc) {
		FCS_LOG_ERR("Invalid desc\n");
		return -FCSERR_EINVAL;
	}

	if (!list_empty(&storage_dev_list))
		LIST_FOR_EACH_DATA(&storage_dev_list, ent, list)
			if (strncmp(ent->desc.dev, desc->dev,
				    strlen(ent->desc.dev)) == 0) {
				FCS_LOG_ERR("dev already defined\n");
				return -FCSERR_EINVAL;
			}

	ent = calloc(1, sizeof(struct storage_entry));
	if (!ent) {
		FCS_LOG_ERR("Unable to allocate memory\n");
		return -FCSERR_ENOMEM;
	}
	ent->desc = *desc;

	list_add_tail(&storage_dev_list, &ent->list);

	return FCSERR_OK;
}

int storage_remove_dev(const struct storage_desc *desc)
{
	struct storage_entry *ent;

	if (!desc) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (list_empty(&storage_dev_list)) {
		FCS_LOG_ERR("List empty\n");
		return -FCSERR_ENXIO;
	}

	LIST_FOR_EACH_DATA(&storage_dev_list, ent, list)
		if (strncmp(ent->desc.dev, desc->dev, strlen(ent->desc.dev))
		    == 0) {
			list_remove(&ent->list);
			free(ent);
			return FCSERR_OK;
		}

	FCS_LOG_ERR("Could not find device\n");
	return -FCSERR_ENXIO;
}

struct storage_desc *storage_get_desc(const char *dev)
{
	struct storage_entry *ent;

	if (!dev) {
		FCS_LOG_ERR("Invalid argument\n");
		return NULL;
	}

	LIST_FOR_EACH_DATA(&storage_dev_list, ent, list)
		if (strncmp(ent->desc.dev, dev, strlen(ent->desc.dev)) == 0)
			return &(ent->desc);

	return NULL;
}

struct storage_ctx *storage_open_by_name(const char *dev, const char *name)
{
	struct storage_entry *ent;
	struct storage_ctx *ctx;

	if (list_empty(&storage_dev_list)) {
		FCS_LOG_ERR("List empty\n");
		return NULL;
	}

	LIST_FOR_EACH_DATA(&storage_dev_list, ent, list) {
		if (!ent->desc.interface.open)
			continue;

		ctx = ent->desc.interface.open(dev, name);
		if (ctx)
			return ctx;
	}

	/* all registered devices failed */
	FCS_LOG_ERR("Could not find dev\n");
	return NULL;
}

int storage_close(struct storage_ctx *ctx)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	if (!ctx->desc.interface.close) {
		FCS_LOG_ERR("Close not supported\n");
		return -FCSERR_ENIMP;
	}
	free(ctx->name);

	return ctx->desc.interface.close(ctx);
}

ssize_t storage_read(struct storage_ctx *ctx, void *buf, ssize_t count)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	if (!ctx->desc.interface.read) {
		FCS_LOG_ERR("Read not supported\n");
		return -FCSERR_ENIMP;
	}

	return ctx->desc.interface.read(ctx, buf, count);
}

ssize_t storage_write(struct storage_ctx *ctx, const void *buf, ssize_t count)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	if (!ctx->desc.interface.write) {
		FCS_LOG_ERR("Write not supported\n");
		return -FCSERR_ENIMP;
	}

	return ctx->desc.interface.write(ctx, buf, count);
}

off_t storage_lseek(struct storage_ctx *ctx, off_t offset, int whence)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	if (!ctx->desc.interface.lseek) {
		FCS_LOG_ERR("lseek not supported\n");
		return -FCSERR_ENIMP;
	}

	return ctx->desc.interface.lseek(ctx, offset, whence);
}

int storage_erase(struct storage_ctx *ctx, ssize_t count, int flags)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	if (!ctx->desc.interface.erase) {
		FCS_LOG_ERR("Erase not supported\n");
		return -FCSERR_ENIMP;
	}

	return ctx->desc.interface.erase(ctx, count, flags);
}

int storage_purge(void)
{
	struct storage_entry *ent;
	struct storage_ctx *ctx = NULL;
	int ret;

	if (list_empty(&storage_dev_list)) {
		FCS_LOG_ERR("List empty\n");
		return -FCSERR_EINVAL;
	}

	LIST_FOR_EACH_DATA(&storage_dev_list, ent, list) {
		if (!ent->desc.interface.open)
			continue;

		ctx = ent->desc.interface.open(NULL, NULL);
		if (ctx)
			break;
	}

	if (!ctx) {
		FCS_LOG_ERR("Invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	if (!ctx->desc.interface.purge) {
		FCS_LOG_ERR("purge not supported\n");
		return -FCSERR_ENIMP;
	}

	ret = ctx->desc.interface.purge(ctx);
	storage_close(ctx);

	return ret;
}

int storage_unlink_by_name(const char *dev, const char *name)
{
	struct storage_entry *ent;
	int ret;

	if (list_empty(&storage_dev_list)) {
		FCS_LOG_ERR("List empty\n");
		return -FCSERR_EFAULT;
	}

	LIST_FOR_EACH_DATA(&storage_dev_list, ent, list) {
		if (!ent->desc.interface.unlink)
			continue;
		ret = ent->desc.interface.unlink(dev, name);
		if (ret == 0)
			return 0;
		else if (ret != -FCSERR_ENOENT)
			return ret;
	}

	/* all registered devices failed */
	FCS_LOG_ERR("Could not find dev\n");
	return -FCSERR_ENOENT;
}

struct storage_dir *storage_opendir(const char *dev)
{
	struct storage_entry *ent;
	struct storage_dir *ctx;

	if (list_empty(&storage_dev_list)) {
		FCS_LOG_ERR("List empty\n");
		return NULL;
	}

	LIST_FOR_EACH_DATA(&storage_dev_list, ent, list) {
		if (!ent->desc.interface.opendir)
			continue;

		ctx = ent->desc.interface.opendir(dev);
		if (ctx)
			return ctx;
	}

	/* all registered devices failed */
	FCS_LOG_ERR("Could not find dev\n");
	return NULL;
}

int storage_closedir(struct storage_dir *dir)
{
	if (!dir) {
		FCS_LOG_ERR("Invalid dir\n");
		return -FCSERR_EINVAL;
	}

	if (!dir->desc.interface.closedir) {
		FCS_LOG_ERR("closedir not supported\n");
		return -FCSERR_ENIMP;
	}

	return dir->desc.interface.closedir(dir);
}

int storage_readdir(struct storage_dir *dir, struct storage_dirent *dirent)
{
	if (!dir) {
		FCS_LOG_ERR("Invalid dir\n");
		return -FCSERR_EINVAL;
	}

	if (!dirent) {
		FCS_LOG_ERR("Invalid dirent\n");
		return -FCSERR_EINVAL;
	}

	if (!dir->desc.interface.readdir) {
		FCS_LOG_ERR("readdir not supported\n");
		return -FCSERR_ENIMP;
	}

	return dir->desc.interface.readdir(dir, dirent);
}

int storage_rrpart(const char *dev, const char *name)
{
	struct storage_entry *ent;
	int ret = -FCSERR_ENODEV;

	if (list_empty(&storage_dev_list)) {
		FCS_LOG_ERR("List empty\n");
		return ret;
	}

	LIST_FOR_EACH_DATA(&storage_dev_list, ent, list) {
		if (!ent->desc.interface.rrpart)
			continue;

		ret = ent->desc.interface.rrpart(dev, name);
		if (ret != -FCSERR_ENODEV)
			return ret;
	}
	return ret;
}

ssize_t storage_get_ssz(struct storage_ctx *ctx)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	if (!ctx->desc.interface.get_ssz) {
		FCS_LOG_ERR("get_ssz not supported\n");
		return -FCSERR_ENIMP;
	}

	return ctx->desc.interface.get_ssz(ctx);
}

int storage_set_name(struct storage_ctx *ctx, const char *name)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	free(ctx->name);
	ctx->name = NULL;

	if (!name)
		return FCSERR_OK;

	ctx->name = malloc(strlen(name) + 1);
	if (!ctx->name) {
		FCS_LOG_ERR("out of memory\n");
		return -FCSERR_ENOMEM;
	}
	memcpy(ctx->name, name, strlen(name) + 1);

	return FCSERR_OK;
}

char *storage_get_name(struct storage_ctx *ctx)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return NULL;
	}

	return ctx->name;
}

int storage_get_gpt_info(struct storage_ctx *ctx, const char *name,
		void *buf, ssize_t *count)
{
	if (!ctx || !count || !name) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	if (!ctx->desc.interface.get_gpt_info) {
		FCS_LOG_ERR("get_ssz not supported\n");
		return -FCSERR_ENIMP;
	}

	return ctx->desc.interface.get_gpt_info(name, buf, count);
}

ssize_t storage_get_storage_info(struct storage_ctx *ctx, void *buf,
		ssize_t *count)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid context\n");
		return -FCSERR_EINVAL;
	}

	if (!ctx->desc.interface.get_storage_info) {
		FCS_LOG_ERR("Get storage info not supported\n");
		return -FCSERR_ENIMP;
	}

	return ctx->desc.interface.get_storage_info(ctx, buf, count);
}

int storage_set_bootdevice(struct storage_ctx *ctx, int lun)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid context\n");
		return -FCSERR_EINVAL;
	}

	if (!ctx->desc.interface.set_bootdevice) {
		FCS_LOG_INF("Set bootdevice not supported\n");
		return FCSERR_OK;
	}

	return ctx->desc.interface.set_bootdevice(ctx, lun);
}
