/*===========================================================================

                       Trial Boot Loader Source File

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
#include "boot_partition_rw.h"
#include "trial_boot_info.h"
#include "coldplug_api.h"


struct coldplug_guid trial_boot_info_partition_id = TRIAL_BOOT_INFO_PARTITION_ID;

static trial_boot_info_type trial_boot_info;

uint32 trial_boot_info_size = sizeof(trial_boot_info_type);


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
  boolean read_status = FALSE;
  trial_boot_status status = TBI_SUCCESS;

  
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

    read_status = boot_read_from_partition((uint8*)&trial_boot_info_partition_id, NULL, 0, (uint8*)&trial_boot_info_ptr, trial_boot_info_size);
    if(read_status != TRUE)
    {
      status = TBI_READ_ERR;
      break;
    }

    if(trial_boot_info.magic_cookie != TBI_MAGIC_COOKIE)
    {
      trial_boot_info.magic_cookie = TBI_MAGIC_COOKIE;
      trial_boot_info.version = TBI_VERSION;
      trial_boot_info.trial_boot_max_attempts = TBI_MAX_ATTEMPTS;
      trial_boot_info.trial_boot_enable = 0;
      trial_boot_info.trial_boot_failed_attempts = 0;
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
  boolean write_status = FALSE;
  trial_boot_status status = TBI_SUCCESS;
  
  write_status = boot_write_to_partition((uint8*)&trial_boot_info_partition_id, NULL, 0, (uint8*)trial_boot_info_ptr, trial_boot_info_size);
  if(write_status != TRUE)
  {
    status = TBI_WRITE_ERR;
  }
  
  return status;
}


