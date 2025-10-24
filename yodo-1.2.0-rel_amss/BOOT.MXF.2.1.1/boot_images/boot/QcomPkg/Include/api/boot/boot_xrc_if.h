#ifndef BOOT_XRC_IF_H
#define BOOT_XRC_IF_H

/*===========================================================================

                    BOOT XRC IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for XRC driver.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/08/22   batta      Initial Creation.

===========================================================================*/
/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"
#include "slvcom.h"
/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

typedef struct boot_xrc_if_type
{
    boolean (*init)(slvcom_handle_type *handle);
    boolean (*done)(slvcom_handle_type *handle);
} boot_xrc_if_type;

/*============================================================================
                      Boot SLVCOM error codes.
============================================================================*/
typedef enum
{
   BL_ERROR_BOOT_XRC_INTERFACE_FAILURE = BL_ERR_CUSTOM_ERRORS_START
} boot_xrc_error_type;

extern boot_xrc_if_type boot_xrc_if;

#endif /* BOOT_XRC_IF_H */
