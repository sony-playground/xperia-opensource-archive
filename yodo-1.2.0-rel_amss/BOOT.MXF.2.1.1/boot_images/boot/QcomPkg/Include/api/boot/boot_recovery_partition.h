#ifndef BOOT_RECOVERY_PARTITION_H
#define BOOT_RECOVERY_PARTITION_H

/*===========================================================================
                                Boot Recovery Partitiom SMEM
                                Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for saving 
  recovery partition info in smem shared between boot and other subsystems. 

Copyright 2021 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================
                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   --------     ------------------------------------------------------
01/25/21   sp           Initial Revision
============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <boot_error_if.h>
#include <boot_config_context.h>

/*=============================================================================
            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.
=============================================================================*/

#define SMEM_RECOVERY_PARTITION_MAGIC_COOKIE  0x72637672
#define SMEM_RECOVERY_PARTITION_VERSION       0x1
#define NUM_OF_PARTITIONS 40 
#define IMEM_PARTITIONS 5

/*Unique smem id for smem_recovery_partitions_info*/
#define RECOVERY_PARTITION_SMEM_ID 630

typedef struct recovery_partition_info
{
  uint64 last_errorcode;
  uint32 flags;
  uint8 corrupted_partition_id[PARTITION_ID_MAX_SIZE];
  uint8 recovery_partition_id[PARTITION_ID_MAX_SIZE];
  uint8 number_of_corruption_reports;
}recovery_partition_info;

typedef struct smem_recovery_partitions_info
{
  uint32 magic_cookie;
  uint16 version;
  uint8 max_entries;
  uint8 num_of_entries;
  recovery_partition_info partition_info[NUM_OF_PARTITIONS];
}smem_recovery_partitions_info;

typedef enum
{
  BOOT_RECOVERY_ERROR_NONE,
  BOOT_RECOVERY_SMEM_UNINITIALIZED_VARIABLE,
  BOOT_RECOVERY_SMEM_BUFFER_SIZE_TOO_SMALL
}boot_recovery_status;

bl_error_boot_type boot_recovery_partitions_info_smem_init(boot_handle config_context_handle);

bl_error_boot_type boot_load_recovery_image(boot_handle config_context_handle, uint8 *recovery_partition_id);

bl_error_boot_type boot_load_recovery_lun(boot_handle config_context_handle, uint8 *recovery_partition_id);

bl_error_boot_type boot_recovery_partitions_info_imem_init(boot_handle config_context_handle);

bl_error_boot_type boot_recovery_add_partition_info(uint8 *partition_id, uint8 *recovery_partition_id);

boot_recovery_status boot_recovery_add_good_and_corrupted_partition_id(uint8 *partition_id, uint8 *recovery_partition_id);

#endif /* BOOT_RECOVERY_PARTITION_H */
