#ifndef XBL_CONFIG_LOADER_ELF_H
#define XBL_CONFIG_LOADER_ELF_H
/*=============================================================================

                      XBLConfig Image Interface Module Sources

GENERAL DESCRIPTION
  This file defines XBL config api's that interface with Elf image
  load module.

Copyright 2016 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
10/14/16     kpa      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "XBLConfig.h"
#include "boot_loader_if.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/

xblconfig_status_type xcfg_get_data(uintnt file_offset, uintnt file_size, void *buffer);


#endif /* XBL_CONFIG_LOADER_ELF_H */
