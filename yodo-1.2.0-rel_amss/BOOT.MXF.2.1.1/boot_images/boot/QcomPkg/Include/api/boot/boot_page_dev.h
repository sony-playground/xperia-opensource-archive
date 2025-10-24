#ifndef BOOT_PAGE_DEV_H
#define BOOT_PAGE_DEV_H
/*=============================================================================

                     Boot Page Device Driver

GENERAL DESCRIPTION
  This file contains the definition for boot layer that provides the APIs
  for reading and writing to page based flash devices.

Copyright 2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
03/24/20   ck           Initial revision.
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
  BL_ERR_UNSUPPORTED_PAGE_DEV								= BL_ERR_CUSTOM_ERRORS_START,
} bl_error_page_dev_type;

bl_error_boot_type boot_page_dev_get_interface(void *media_interface_if);

#endif //BOOT_PAGE_DEV_H
