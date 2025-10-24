#ifndef BOOT_SAHARA_STATUS_MAP_IF_H
#define BOOT_SAHARA_STATUS_MAP_IF_H

/*===========================================================================
                    BOOT SAHARA STATUS MAPPING IF DEFINITIONS

DESCRIPTION
  Contains function pointers for Sahara Status Mapping Library

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020-2021 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
11/25/20   rhy     Inital revision

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_error_if.h"
#include "boot_sahara.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/
typedef struct boot_sahara_status_map_handler_if
{                       
    bl_error_boot_type (*get_mapped_sahara_status)(bl_error_boot_type,
                                                    boot_sahara_status *);
}boot_sahara_status_map_handler_if;

extern boot_sahara_status_map_handler_if sahara_status_map_if;

#endif /* BOOT_SAHARA_STATUS_MAP_IF_H */
