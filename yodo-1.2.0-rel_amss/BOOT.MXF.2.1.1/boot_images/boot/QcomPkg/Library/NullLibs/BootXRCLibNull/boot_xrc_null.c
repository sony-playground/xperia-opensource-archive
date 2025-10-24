/*===========================================================================

                    BOOT XRC INTERFACE DEFINITIONS

DESCRIPTION
  Contains definition for XRC if

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
07/08/22   batta    Initial revision
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <boot_xrc_if.h>
#include "slvcom.h"

/*=========================================================================

**  FUNCTION  boot_xrc_ramdump_init

**  [in] params : None.

**  [RETURN] : return_status, TRUE or FALSE.

===========================================================================*/
boolean boot_xrc_ramdump_init(slvcom_handle_type *handle)
{
   return TRUE;
}

/*=========================================================================

**  FUNCTION  boot_xrc_ramdump_done

**  [in] params : None.

**  [RETURN] : return_status, TRUE or FALSE.

===========================================================================*/
boolean boot_xrc_ramdump_done(slvcom_handle_type *handle)
{
   return TRUE;
}

/*=========================================================================

** Boot XRC interface initialization.

==========================================================================*/
boot_xrc_if_type boot_xrc_if =  {
    boot_xrc_ramdump_init,
    boot_xrc_ramdump_done
};
