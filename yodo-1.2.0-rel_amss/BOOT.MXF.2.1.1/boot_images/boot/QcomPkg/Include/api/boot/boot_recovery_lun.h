/**
# @file boot_recovery_lun.h
#
#  Boot recovery LUN handling
#
#  Copyright 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
#  Qualcomm Technologies Proprietary and Confidential.
#
#**/

/*==============================================================================
#                              EDIT HISTORY
#
# when       who     what, where, why
# --------   ---     ----------------------------------------------------------
# 05/26/21   vk  Initial Revision
#
#==============================================================================*/

#ifndef __BOOT_RECOVERY_LUN_H__
#define __BOOT_RECOVERY_LUN_H__

#include <string.h>
#include <boot_config_context.h>
#include <boot_recovery_partition.h>
#include <boot_error_if.h>
#include <boot_coldplug_if.h>

#define BOOT_LUN_1                    1
#define BOOT_LUN_2                    2

#define BANK_AB_USABLE                (0x0UL)
#define DONT_USE_BANK_A               (0x1UL)
#define DONT_USE_BANK_B               (0x2UL)
#define DONT_USE_BANK_AB              (0x3UL)

#define RECOVERY_INFO_MAGIC           (0x72637279UL) /* 'rcry' */
#define RECOVERY_INFO_CURRENT_VERSION (1)

#define OWNER_XBL           (1)

#define GUID_SIZE           16

typedef struct _bl_recovery_info
{
  uint32 magic;
  uint32 version;
  uint32 bank_status;
  uint32 owner;
  uint32 reserved0;
  uint32 reserved1;
  uint8  corrupt_guid_bank_a[GUID_SIZE];
  uint8  corrupt_guid_bank_b[GUID_SIZE];
} bl_recovery_info_type;

bl_error_boot_type boot_recovery_select_boot_partitions (boot_handle config_context_handle);
bl_error_boot_type boot_recovery_is_boot_partition_valid (boot_handle config_context_handle);
bl_error_boot_type boot_recovery_media_partial_init_return (boot_handle config_context_handle);
bl_error_boot_type boot_recovery_load_recovery_lun(boot_handle config_context_handle, uint8 *recovsery_partition_id);
bl_error_boot_type boot_recovery_update_corrupt_patition_id (boot_handle config_context_handle, uint8 *partition_id);
bl_error_boot_type boot_recovery_is_partition_valid(boot_handle config_context_handle, uint8 *partition_id);

#endif
