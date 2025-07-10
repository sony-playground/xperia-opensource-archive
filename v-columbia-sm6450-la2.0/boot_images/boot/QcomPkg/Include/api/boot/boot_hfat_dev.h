#ifndef BOOT_HFAT_DEV_H
#define BOOT_HFAT_DEV_H
/*=============================================================================

                     Boot Hfat Device Driver

GENERAL DESCRIPTION
  HFAT access layer APIs

Copyright 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
02/19/21   vk           Initial revision.
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_media_interface_if.h"


/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
typedef enum
{
  BL_ERR_UNSUPPORTED_HFAT_DEV								= BL_ERR_CUSTOM_ERRORS_START,
} bl_error_hfat_dev_type;

bl_error_boot_type boot_hfat_dev_get_interface(void *media_interface_if);

#endif //BOOT_HFAT_DEV_H
