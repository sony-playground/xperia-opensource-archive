/**
# @file BootRecoveryPartitionLibNull.c
#
#  BootRecoveryPartitionLibNull
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
# 01/25/21   sp  Initial Revision
#
#==============================================================================*/

#include <boot_config_context.h>
#include <boot_recovery_partition.h>
#include <boot_error_if.h>


bl_error_boot_type boot_recovery_partitions_info_smem_init(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  return status;
}

bl_error_boot_type boot_recovery_add_partition_info(uint8 *partition_id, uint8 *recovery_partition_id)
{
  bl_error_boot_type status = BL_ERR_NONE;
  return status;
}

bl_error_boot_type boot_recovery_partitions_info_imem_init(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  return status;
}

bl_error_boot_type boot_load_recovery_image(boot_handle config_context_handle, uint8 *recovery_partition_id)
{
  bl_error_boot_type status = GET_ERROR_INFO;
  return status;
}

bl_error_boot_type boot_recovery_load_recovery_lun(boot_handle config_context_handle, uint8 *recovery_partition_id)
{
  bl_error_boot_type status = GET_ERROR_INFO;
  return status;
}

bl_error_boot_type boot_recovery_select_boot_partitions (boot_handle config_context_handle)
{
  return BL_ERR_NONE;
}

bl_error_boot_type boot_recovery_media_partial_init_return (boot_handle config_context_handle)
{
  return BL_ERR_NONE;
}

bl_error_boot_type boot_recovery_update_corrupt_patition_id (boot_handle config_context_handle, uint8 *partition_id)
{
  return BL_ERR_NONE;
}

bl_error_boot_type boot_recovery_is_partition_valid(boot_handle config_context_handle, uint8 *partition_id)
{
  return BL_ERR_NONE;
}