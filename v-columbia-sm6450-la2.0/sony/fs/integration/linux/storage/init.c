/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "storage.h"
#include "storage_int.h"
#include "storage_emmc.h"
#include "storage_ufs.h"
#include "storage_file.h"
#include "storage_ram.h"
#include "storage_heap.h"
#include "fcslog.h"
#include "input_args.h"
#include "fcserr.h"

#include <string.h>

struct storage_interface emmc_if = {
	.open = storage_emmc_open,
	.close = storage_file_close,
	.read = storage_file_read,
	.write = storage_file_write,
	.lseek = storage_file_lseek,
	.erase = storage_emmc_erase,
	.purge = storage_emmc_purge,
	.unlink = NULL,
	.opendir = storage_emmc_opendir,
	.closedir = storage_file_closedir,
	.readdir = storage_file_readdir,
	.rrpart = storage_emmc_rrpart,
	.get_ssz = storage_file_get_ssz,
	.get_gpt_info = storage_emmc_gpt_info,
	.get_storage_info = storage_emmc_get_storage_info,
	.set_bootdevice = storage_emmc_set_bootdevice,
};

struct storage_interface ufs_if = {
	.open = storage_ufs_open,
	.close = storage_file_close,
	.read = storage_file_read,
	.write = storage_file_write,
	.lseek = storage_file_lseek,
	.erase = storage_ufs_erase,
	.purge = storage_ufs_purge,
	.unlink = NULL,
	.opendir = storage_ufs_opendir,
	.closedir = storage_file_closedir,
	.readdir = storage_file_readdir,
	.rrpart = storage_ufs_rrpart,
	.get_ssz = storage_file_get_ssz,
	.get_gpt_info = storage_ufs_gpt_info,
	.get_storage_info = storage_ufs_get_storage_info,
	.set_bootdevice = storage_ufs_set_bootdevice,
};

struct storage_interface ram_if = {
	.open = storage_ram_open,
	.close = storage_file_close,
	.read = storage_file_read,
	.write = storage_file_write,
	.lseek = storage_file_lseek,
	.erase = NULL,
	.purge = NULL,
	.unlink = storage_ram_unlink,
	.opendir = storage_ram_opendir,
	.closedir = storage_file_closedir,
	.readdir = storage_file_readdir,
	.rrpart = NULL,
	.get_ssz = NULL,
	.get_gpt_info = NULL,
	.get_storage_info = NULL,
	.set_bootdevice = NULL,
};

struct storage_interface heap_if = {
	.open = storage_heap_open,
	.close = storage_heap_close,
	.read = storage_heap_read,
	.write = storage_heap_write,
	.lseek = storage_heap_lseek,
	.erase = NULL,
	.purge = NULL,
	.unlink = storage_heap_unlink,
	.opendir = NULL,
	.closedir = NULL,
	.readdir = NULL,
	.rrpart = NULL,
	.get_ssz = NULL,
	.get_gpt_info = NULL,
	.get_storage_info = NULL,
	.set_bootdevice = NULL,
};

int storage_init(void)
{
	struct storage_desc desc;
	int res;
	const char *dev = NULL;

	dev = input_args_get_flash();

	if (!dev) {
		FCS_LOG_ERR("Could not get storage string\n");
		return -FCSERR_EINVAL;
	}

	if (!strncmp(dev, STORAGE_EMMC_NAME, strlen(STORAGE_EMMC_NAME))) {
		desc.dev = STORAGE_EMMC_NAME;
		desc.interface = emmc_if;
		res = storage_add_dev(&desc);
		if (res)
			goto err;
	} else if (!strncmp(dev, STORAGE_UFS_NAME, strlen(STORAGE_UFS_NAME))) {
		desc.dev = STORAGE_UFS_NAME;
		desc.interface = ufs_if;
		res = storage_add_dev(&desc);
		if (res)
			goto err;
	} else {
		FCS_LOG_ERR("Unknown storage device\n");
		desc.dev = "unknown storage";
		res = -FCSERR_EINVAL;
		goto err;
	}

	desc.dev = STORAGE_RAM_NAME;
	desc.interface = ram_if;
	res = storage_add_dev(&desc);
	if (res)
		goto err;

	desc.dev = STORAGE_HEAP_NAME;
	desc.interface = heap_if;
	res = storage_add_dev(&desc);
	if (res)
		goto err;

	return res;
err:
	FCS_LOG_ERR("could not add %s\n", desc.dev);
	return res;
}
