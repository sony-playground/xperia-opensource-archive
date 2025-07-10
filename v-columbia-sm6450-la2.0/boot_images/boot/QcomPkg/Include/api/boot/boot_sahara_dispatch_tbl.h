#ifndef BOOT_SAHARA_DISPATCH_TBL_H
#define BOOT_SAHARA_DISPATCH_TBL_H

/*=============================================================================

                    Boot Sahara Dispatch Table Interface

GENERAL DESCRIPTION
  Contains wrapper definition for external QUSB drivers

Copyright 2020 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when       who       what, where, why
--------   ---       ----------------------------------------------------------
05/17/20   rhy       Initial revision
=============================================================================*/

/*=========================================================================

**  Function :  boot_sahara_dispatch_table_init

** ==========================================================================
*/
/*!
* 
* @brief
*   Initialize flashless sahara dispatch table based in boot device.
* 
* @param[in] config context and pointer to media_interface_if
* 
*/
bl_error_boot_type boot_sahara_dispatch_table_init(boot_handle);

#endif /* BOOT_SAHARA_DISPATCH_TBL_H */