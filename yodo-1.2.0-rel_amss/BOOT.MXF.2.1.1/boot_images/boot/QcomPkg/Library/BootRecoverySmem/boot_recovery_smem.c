/*===========================================================================

                       Boot Recovery Partition Info Source File

GENERAL DESCRIPTION
  This file contains functions to save recovery partition info in smem 
  shared between boot and other subsystems.  

Copyright 2021 Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
06/29/21   sp      Initial Revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <stdio.h>
#include <string.h>
#include <smem.h>
#include <boot_recovery_partition.h>

 /*===========================================================================

**  Function :  boot_recovery_partition_info_add_to_smem

** ==========================================================================
*/
/*!
*
* @brief
*   This function copies corrupted and recovery partions info to shared memory.
*
* @par Dependencies
*   Call this api after smem allocation.
*
* @retval
*   None
*
* @par Side Effects
*   None
*/
boot_recovery_status boot_recovery_add_good_and_corrupted_partition_id(uint8 *partition_id, uint8 *recovery_partition_id)
{
  boot_recovery_status status = BOOT_RECOVERY_ERROR_NONE;
  smem_recovery_partitions_info* recovery_partition_base = NULL;
  recovery_partition_info smem_recovery_partition_info;
  uint32 recovery_smem_size = 0;
  uint32 copy_size = 0;
  boot_boolean flag = FALSE;

  do
  {
    recovery_partition_base = (smem_recovery_partitions_info *)smem_get_addr(RECOVERY_PARTITION_SMEM_ID, &recovery_smem_size);
    if(recovery_partition_base == NULL)
    {
      status = BOOT_RECOVERY_SMEM_UNINITIALIZED_VARIABLE;
      break;
    }

    for(uint8 i = 0; i < recovery_partition_base->num_of_entries; i++)
    {
      if( memcmp(partition_id, recovery_partition_base->partition_info[i].corrupted_partition_id, PARTITION_ID_MAX_SIZE) == 0)
      {
        recovery_partition_base->partition_info[i].number_of_corruption_reports++;
        flag = TRUE;
        break;
      }
    }

    if(flag)
      break;

    if((recovery_partition_base->magic_cookie == SMEM_RECOVERY_PARTITION_MAGIC_COOKIE) &&
       (recovery_partition_base->num_of_entries < recovery_partition_base->max_entries))
    {
      copy_size = memscpy(recovery_partition_base->partition_info[recovery_partition_base->num_of_entries].corrupted_partition_id, sizeof(smem_recovery_partition_info.corrupted_partition_id), partition_id, PARTITION_ID_MAX_SIZE);
      if(copy_size < PARTITION_ID_MAX_SIZE)
      {
        status = BOOT_RECOVERY_SMEM_BUFFER_SIZE_TOO_SMALL;
        break;
      }
      copy_size = memscpy(recovery_partition_base->partition_info[recovery_partition_base->num_of_entries].recovery_partition_id, sizeof(smem_recovery_partition_info.recovery_partition_id), recovery_partition_id, PARTITION_ID_MAX_SIZE);
      if(copy_size < PARTITION_ID_MAX_SIZE)
      {
        status = BOOT_RECOVERY_SMEM_BUFFER_SIZE_TOO_SMALL;
        break;
      }
      recovery_partition_base->partition_info[recovery_partition_base->num_of_entries].number_of_corruption_reports = 1;
      recovery_partition_base->num_of_entries++;
    }

  }while(FALSE);

  return status;
}