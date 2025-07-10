#ifndef BOOT_MODES_H
#define BOOT_MODES_H
/*=============================================================================

                     Boot Modes definition

GENERAL DESCRIPTION
  This file contains definition of boot modes

Copyright 2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
03/22/21   digants      Additional modes support
12/18/20   digants      Initial revision.
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/

/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
typedef enum boot_mode_type
{
  BOOT_MODE_XBL = 0,
  BOOT_MODE_RAMDUMP,
  BOOT_MODE_DEVICEPROGRAMMER,
  BOOT_MODE_DEVICEPROGRAMMER_NO_DDR,
  BOOT_MODE_XBL_TEST_MODE,
  BOOT_MODE_MAX,
  BOOT_MODE_SIZE = 0X7FFFFFFFF
}boot_mode_type;

#endif //BOOT_MODES_H