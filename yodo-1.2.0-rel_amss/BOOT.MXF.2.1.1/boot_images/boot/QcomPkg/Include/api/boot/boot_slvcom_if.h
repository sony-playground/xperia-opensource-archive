#ifndef BOOT_SLVCOM_IF_H
#define BOOT_SLVCOM_IF_H

/*===========================================================================

                    BOOT SLAVECOM IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for Slvcom drivers

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
06/10/22   batta      Initial Creation.

===========================================================================*/
/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

typedef struct boot_slvcom_if_type
{
    bl_error_boot_type (*init)(void);
    bl_error_boot_type (*ahb_read)(uint8* buf, uint64 offset, uint64 size);
} boot_slvcom_if_type;


/*============================================================================
                      Boot SLVCOM error codes.
============================================================================*/
typedef enum
{
    BL_ERR_BOOT_SLVCOM_INTERFACE_FAILURE = BL_ERR_CUSTOM_ERRORS_START,
    BL_ERR_BOOT_SLVCOM_OPEN_FAILURE,
    BL_ERR_BOOT_SLVCOM_SECMODE_ENABLE_FAILURE,
    BL_ERR_BOOT_SLVCOM_AHB_READ_FAILURE
} boot_slvinfo_error_type;


extern boot_slvcom_if_type boot_slvcom_if;

#endif /* BOOT_SLVCOM_IF_H */
