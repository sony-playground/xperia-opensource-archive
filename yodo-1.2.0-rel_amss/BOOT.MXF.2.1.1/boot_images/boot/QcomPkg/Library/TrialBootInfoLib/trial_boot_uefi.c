/*===========================================================================

                       Trial Boot UEFI Source File

GENERAL DESCRIPTION
  This file contains functions to read/write Trial Boot Info to trial_boot_info_partition

Copyright 2022 Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/27/21   sp      Initial Revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/

#include "TrialBootInfoLib.h"
#include "Library/QcomLib.h"
#include "Library/QcomBaseLib.h"
#include "Library/MemoryAllocationLib.h"
#include "trial_boot_info.h"

EFI_GUID trial_boot_info_partition_id = TRIAL_BOOT_INFO_PARTITION_ID;

UINTN trial_boot_info_size = sizeof(trial_boot_info_type);

static trial_boot_info_type trial_boot_info;
/*==============================================================================
**  Functions
**============================================================================*/

/*=========================================================================

**  Function :  tbi_read_partition

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage
*
*/

trial_boot_status tbi_get_trial_boot_info(trial_boot_info_type **trial_boot_info_ptr)
{
  EFI_STATUS read_status;
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *ReadBuffer = NULL;
  UINTN ReadSize = 0;
  
  do
  {
    if(trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    *trial_boot_info_ptr = &trial_boot_info;

    if(trial_boot_info.magic_cookie == TBI_MAGIC_COOKIE)
    {
      break;
    }

    read_status = ReadFromPartition (&trial_boot_info_partition_id, NULL, (void**)&ReadBuffer, &ReadSize, 0);
    if (EFI_ERROR(read_status))
    {
      status = TBI_READ_ERR;
      break;
    }

    if(ReadBuffer->magic_cookie != TBI_MAGIC_COOKIE)
    {
      trial_boot_info.magic_cookie = TBI_MAGIC_COOKIE;
      trial_boot_info.version = TBI_VERSION;
      trial_boot_info.trial_boot_max_attempts = TBI_MAX_ATTEMPTS;
      trial_boot_info.trial_boot_enable = 0;
      trial_boot_info.trial_boot_failed_attempts = 0;
    }
    else
    {
      CopyMemS((void*)*trial_boot_info_ptr, trial_boot_info_size, ReadBuffer, ReadSize);
    }

  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_write_partition

** ==========================================================================
*/
/*!
*
* @brief
*   This api writes trial boot info to storage
*
*/
trial_boot_status tbi_write_partition(trial_boot_info_type *trial_boot_info_ptr)
{
  EFI_STATUS write_status;
  trial_boot_status status = TBI_SUCCESS;

  write_status = WriteToPartition (&trial_boot_info_partition_id, NULL, (void*)trial_boot_info_ptr, trial_boot_info_size, 0);
  if (EFI_ERROR(write_status))
  {
    status = TBI_WRITE_ERR;
  }

  return status;
}