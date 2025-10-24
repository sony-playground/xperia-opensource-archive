#ifndef TRIAL_BOOT_INFO_H
#define TRIAL_BOOT_INFO_H

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
05/27/21   sp      Initial Revision
=============================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

/*===========================================================================
                      DATA DECLARATIONS
===========================================================================*/
#define TBI_MAGIC_COOKIE      0x74726269
#define TBI_VERSION           0x1
#define TBI_MAX_ATTEMPTS      7
#define TBI_ENABLE_TRIAL_BOOT 0x1

#define TRIAL_BOOT_INFO_PARTITION_ID \
    { 0X5334F9BA, 0X02CE, 0X4609, { 0x90, 0x81, 0x2E, 0xC3, 0x9D, 0xCD, 0x6A, 0xC6 } }

typedef struct {
  uint32 magic_cookie;
  uint32 version;
  uint32 trial_boot_enable;
  uint32 trial_boot_max_attempts;
  uint32 trial_boot_failed_attempts;
}trial_boot_info_type;

trial_boot_status tbi_get_trial_boot_info(trial_boot_info_type **trial_boot_info_ptr);

trial_boot_status tbi_write_partition(trial_boot_info_type *trial_boot_info_ptr);


#endif