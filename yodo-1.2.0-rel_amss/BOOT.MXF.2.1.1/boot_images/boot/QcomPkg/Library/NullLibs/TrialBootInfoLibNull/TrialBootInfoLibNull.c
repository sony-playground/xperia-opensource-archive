/*===========================================================================

                       Trial Boot Info Source File

GENERAL DESCRIPTION
  This file contains functions to update Trial Boot Info in Trial Boot Info Partition

Copyright 2022 Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/27/22   sp      Initial Revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <TrialBootInfoLib.h>

trial_boot_status tbi_enable_trial_boot(void)
{
  return TBI_SUCCESS;
}

trial_boot_status tbi_is_trial_boot_enabled (uint8 *is_trial_boot_enabled)
{
  *is_trial_boot_enabled = 0x0;
  return TBI_SUCCESS;
}

trial_boot_status tbi_max_attempts_reached(uint8 *is_max_attempts_reached)
{
  *is_max_attempts_reached = 0x0;
  return TBI_SUCCESS;
}

trial_boot_status tbi_get_curr_failed_attempts(uint32 *trial_boot_failed_attempts)
{
  *trial_boot_failed_attempts = 0x0;
  return TBI_SUCCESS;
}

trial_boot_status tbi_increment_failed_boot_attempts(void)
{
  return TBI_SUCCESS;
}

trial_boot_status  tbi_induce_trial_boot_failure(void)
{
  return TBI_SUCCESS;
}

trial_boot_status tbi_clear_partition(void)
{
  return TBI_SUCCESS;
}
