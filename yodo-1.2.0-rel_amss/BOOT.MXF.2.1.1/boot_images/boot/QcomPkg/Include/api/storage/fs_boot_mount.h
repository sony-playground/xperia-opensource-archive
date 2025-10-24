/***********************************************************************
 * fs_boot_mount.h
 *
 * EFS module.
 *
 * This file documents APIs to assist in mounting partitions discovered
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


#ifndef __FS_BOOT_MOUNT_H__
#define __FS_BOOT_MOUNT_H__

#include "coldplug_api.h"

/*************************************************************************//**
 * @par Name:
 *   fs_boot_mount - Mount an raw partition as FAT filesystem with EFS.
 *
 * @par Description:
 *   Mounts the supplied raw partition as FAT filesystem with EFS. This
 *   raw partition can belong to either GPT or MBR. While mounting an
 *   raw-partition from GPT, suppy its guid in the argument or if the
 *   raw-partition is from MBR, then supply an special guid with all 0s in
 *   which case the first FAT-partition in the MBR will get mounted.
 *
 * @param dev_type
 *   Coldplug device type (eg: eMMC or UFS). See enum coldplug_device_type for
 *   the complete list of all the coldplug devices.
 *
 * @param is_embedded_device
 *   Is it an internal device (hardwired) or an external device (pluggable)?
 *   1 -> Internal device
 *   0 -> External device
 *
 * @param guid
 *   If the raw-partition belongs to an GPT, then supply its GUID.
 *   If the raw-partition belongs to MBR, then supply an GUID of 0s in which
 *   case the first fat type partition in the MBR will get mounted.
 *
 * @param mount_path
 *   File system mount-path at which to mount the FAT partition.
 *
 * @return
 *   Returns 0 on success and negative value on failure. On failure
 *   efs_errno is set to appropriate value indicating the reason of failure.
*****************************************************************************/
int fs_boot_mount(enum coldplug_device_type dev_type,
	int is_embedded_device, const struct coldplug_guid *guid,
	const char *mount_point_path);

#endif /* __FS_BOOT_MOUNT_H__ */
