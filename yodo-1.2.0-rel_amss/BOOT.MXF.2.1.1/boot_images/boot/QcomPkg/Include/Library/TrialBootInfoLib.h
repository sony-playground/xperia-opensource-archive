#ifndef TBI_BOOT_INFO_H
#define TBI_BOOT_INFO_H

/*=============================================================================

                            XBLConfig Module Sources

GENERAL DESCRIPTION
  This file defines Trial Boot Info api's to support read or write trial_boot_info to storage

Copyright 2022 Qualcomm Technologies Incorporated.  All Rights Reserved.
=============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/27/22   sp      Initial Revision
=============================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <com_dtypes.h>

/*===========================================================================
                      DATA DECLARATIONS
===========================================================================*/

typedef enum
{
  TBI_SUCCESS,
  TBI_READ_ERR,
  TBI_WRITE_ERR,
  TBI_NULL_PTR,
  TBI_MAX_ATTEMPTS_REACHED,
  TBI_ERR = 0x7FFFFFFF
}trial_boot_status;

/*===========================================================================

                      FUNCTION DECLARATIONS

===========================================================================*/

trial_boot_status tbi_init(void);

trial_boot_status tbi_enable_trial_boot(void);

trial_boot_status tbi_is_trial_boot_enabled (uint8 *is_trial_boot_enabled);

trial_boot_status tbi_max_attempts_reached(uint8 *is_max_attempts_reached);

trial_boot_status tbi_get_curr_failed_attempts(uint32 *trial_boot_failed_attempts);

trial_boot_status tbi_increment_failed_boot_attempts(void);

trial_boot_status tbi_induce_trial_boot_failure(void);

trial_boot_status tbi_clear_partition(void);


#endif