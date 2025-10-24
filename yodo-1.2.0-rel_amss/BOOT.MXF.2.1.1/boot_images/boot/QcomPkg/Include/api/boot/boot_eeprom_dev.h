#ifndef BOOT_EEPROM_DEV_H
#define BOOT_EEPROM_DEV_H
/*=============================================================================

                     Boot Eeprom Device Driver

GENERAL DESCRIPTION
  This file contains the definition for boot layer that provides the APIs
  for reading and writing to eeprom devices.

Copyright 2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
05/12/20   ck           Initial revision.
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
  BL_ERR_UNSUPPORTED_EEPROM_DEV = BL_ERR_CUSTOM_ERRORS_START,
} bl_error_eeprom_dev_type;

bl_error_boot_type boot_eeprom_dev_get_interface(void *media_interface_if);

#endif //BOOT_EEPROM_DEV_H