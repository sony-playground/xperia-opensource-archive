#ifndef BOOT_MBN_LOADER_H
#define BOOT_MBN_LOADER_H

/*=============================================================================

                              Boot Loader

GENERAL DESCRIPTION
  This module performs ELF image loading.

Copyright 2020 - 2022 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/27/22   rhy 	   Added mbn_loader_if
01/23/20   rhy     Initial revision
============================================================================*/

/*===========================================================================

                           INCLUDE FILES
						   
===========================================================================*/
#include "boot_comdef.h"
#include "boot_framework.h"
#include "boot_loader_if.h"
#include "MIbib.h"

/*=============================================================================
                              DEFINITIONS
=============================================================================*/
typedef enum
{
  BL_ERR_MBN_LOADER_IMAGE_SIZE_NULL								= BL_ERR_CUSTOM_ERRORS_START,
  BL_ERR_MBN_LOADER_IMAGE_ID_MISMATCH,
  BL_ERR_MBN_LOADER_AUTH_NOT_SUPPORTED,
  BL_ERR_MBN_LOADER_UNSUPPORTED_INTERFACE,
  
} bl_error_mbn_loader_type;

typedef struct boot_mbn_if_type
{
    bl_error_boot_type (*boot_mbn_header_init)(uint32, uint32, image_type image_id, uint32);
    bl_error_boot_type (*boot_mbn_header_size)(uint32*);
} boot_mbn_if_type;

/*===========================================================================
                      PUBLIC FUNCTION DECLARATIONS
===========================================================================*/



/*===========================================================================
**  Function :  boot_mbn_loader_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_loader_interface_type object 
*
* @par Dependencies
*   None 
* 
*/
bl_error_boot_type boot_mbn_loader_get_interface(void *);

extern boot_mbn_if_type mbn_loader_if;

#endif /* BOOT_MBN_LOADER_H */