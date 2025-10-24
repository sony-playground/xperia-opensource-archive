/*===========================================================================

                    BOOT SLAVECOM NULL INTERFACE DEFINITIONS

DESCRIPTION
  Contains definition for NULL Slave com if

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/10/22   batta    Initial revision
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <boot_error_if.h>
#include "boot_slvcom_if.h"
#include "slvcom.h"

slvcom_handle_type slv_handle;

/*=========================================================================

**  FUNCTION  boot_slvcom_init

**  [in] params : None.

**  [RETURN] : BL_ERR_NONE, if success.
               BOOT slvcom specific error in case of failure.

===========================================================================*/

bl_error_boot_type boot_slvcom_driver_init(void)
{
   return BL_ERR_NONE;
}

/*=========================================================================

**  FUNCTION  boot_slvcom_init

**  [in] params : buf - Sahara buffer passed from Sahara Client.
                  offset - Restricted region address.
                  size - Restricted region size.

**  [RETURN] : BL_ERR_NONE, if success.
               Boot slvcom specific error in case of failure.
===========================================================================*/

bl_error_boot_type boot_slvcom_ahb_read(uint8 *buf, uint64 offset, uint64 size)
{
   return BL_ERR_NONE;
}
    
/*=========================================================================

** Boot SLVCOM interface initialization.

==========================================================================*/
boot_slvcom_if_type boot_slvcom_if = {
    boot_slvcom_driver_init,
    boot_slvcom_ahb_read
};
