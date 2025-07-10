#ifndef BOOT_MBN_IF_H
#define BOOT_MBN_IF_H
/*===========================================================================

                    BOOT MBN IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external MBN loader drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/12/20   rhy     Initial Creation

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"
#include "MIbib.h"



/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 



typedef struct boot_mbn_if_type
{
    bl_error_boot_type (*boot_mbn_header_init)(uint32, uint32, image_type image_id, uint32);
    bl_error_boot_type (*boot_mbn_header_size)(uint32*);
} boot_mbn_if_type;

extern boot_mbn_if_type mbn_loader_if;

#endif /* BOOT_MBN_IF_H */
