/***********************************************************************
 * fs_boot_mount.c
 *
 * EFS module.
 *
 * This file contains the function implemetation to assist in mounting partitions discovered
 * by the coldplug module with the EFS module.
 *
 * Copyright (C) 2021 QUALCOMM Technologies, Inc.
 *
 ***********************************************************************/

 /*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when          who     what, where, why
--------      ---     ------------------------------------------------------
2021-02-04    rp      Create

===========================================================================*/

#include "fs_boot_mount.h"
#include "fs_public.h"
#include "fs_errno.h"
#include "coldplug_priv_api.h"

#include <string.h>

static int fs_boot_mount_first_fat_partition(enum coldplug_device_type dev_type,
	int is_embedded_device, const char *mount_point_path)
{
	int result;
	struct coldplug_iter *citer = NULL;
	struct coldplug_iter_record *citer_rec = NULL;

	result = -ENODEV;
	citer = coldplug_iter_open(dev_type, is_embedded_device, 1);
	if (citer == NULL)
		goto End;

	citer_rec = coldplug_iter_next (citer);
	if (citer_rec == NULL)
		goto End;

	result = efs_mount("", mount_point_path, "extfs", 0, citer_rec->parti_name);
End:
	if (citer != NULL)
		coldplug_iter_close(citer);
	return result;
}

static int fs_boot_mount_guid_partition(enum coldplug_device_type dev_type,
	int is_embedded_device, const struct coldplug_guid *guid,
	const char *mount_point_path)
{
	const char *parti_name;
	int result;

	parti_name = coldplug_search_and_get_partition_name(dev_type,
		is_embedded_device, guid);
	if (parti_name == NULL)
		return  -ENODEV;

	result = efs_mount("", mount_point_path, "extfs", 0, parti_name);
	return result;
}

static struct coldplug_guid coldplug_zeros_guid =
{0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

int fs_boot_mount(enum coldplug_device_type dev_type,
	int is_embedded_device, const struct coldplug_guid *guid,
	const char *mount_point_path)
{
	struct fs_stat sbuf;
	int result;

	if ((dev_type <= COLDPLUG_DEVICE_DEVNULL) ||
		(dev_type >= COLDPLUG_DEVICE_MAX))
		return -EINVAL;

	if ((is_embedded_device != 0) &&
		(is_embedded_device != 1))
		return -EINVAL;

	if (guid == NULL)
		return -EINVAL;

	if (mount_point_path == NULL)
		return -EINVAL;

	memset(&sbuf, 0, sizeof(sbuf));
	result = efs_stat(mount_point_path, &sbuf);
	if (result != 0)
		return result;

	result = memcmp(guid, &coldplug_zeros_guid, sizeof(coldplug_zeros_guid));
	if (result == 0) {
		result = fs_boot_mount_first_fat_partition(dev_type,
				is_embedded_device, mount_point_path);
	} else {
		result = fs_boot_mount_guid_partition(dev_type,
				is_embedded_device, guid, mount_point_path);
	}

	return result;
}

