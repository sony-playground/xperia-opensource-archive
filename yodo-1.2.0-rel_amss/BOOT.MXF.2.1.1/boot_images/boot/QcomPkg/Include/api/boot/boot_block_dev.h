#ifndef BOOT_BLOCK_DEV_H
#define BOOT_BLOCK_DEV_H
/*=============================================================================

                     Boot Block Device Driver

GENERAL DESCRIPTION
  This file contains the implementation for the boot-specific whitelist based
  protection module, to facilitate preventing the bootloader address spaces
  from being overwritten by a flash load.

Copyright 2019 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
09/29/19   digants      Initial revision.
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
  BL_ERR_UNSUPPORTED_BLOCK_DEV								= BL_ERR_CUSTOM_ERRORS_START,
  BL_ERR_COLDPLUG_INIT_FAILURE,
  BL_ERR_COLDPLUG_HANDLE_FAILURE,
  BL_ERR_COLDPLUG_OPEN_BOOT_DEV_FAILURE,
  BL_ERR_COLDPLUG_BACKGRND_INIT_START_FAILURE,
  BL_ERR_COLDPLUG_BACKGRND_INIT_FINISH_FAILURE,
  BL_ERR_COLDPLUG_OPEN_DEV_FAILURE,
  BL_ERR_INCORRECT_SECTOR_SIZE,
  BL_ERR_COLDPLUG_READ_FAILURE,
  BL_ERR_COLDPLUG_WRITE_FAILURE,
  BL_ERR_COLDPLUG_CLOSE_PARTITION_FAILURE,
  BL_ERR_COLDPLUG_GET_SIZE_FAILURE
} bl_error_block_dev_type;

bl_error_boot_type boot_block_dev_get_interface(void *media_interface_if);

#endif //BOOT_BLOCK_DEV_H
