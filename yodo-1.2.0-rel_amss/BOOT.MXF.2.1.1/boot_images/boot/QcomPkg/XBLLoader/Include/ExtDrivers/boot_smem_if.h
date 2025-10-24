#ifndef BOOT_SMEM_IF_H
#define BOOT_SMEM_IF_H
/*===========================================================================

                    BOOT SMEM IF DEFINITIONS

DESCRIPTION
  Contains definition for smem if 

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019 by QUALCOMM Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/02/19   ep      Created the file

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"
#include "boot_error_if.h"
#include "boot_framework.h"
#include "smem.h"
#include "image_version.h"
#include "image_uuid.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

typedef struct boot_smem_if_type
{
  void (*init)(void);
  void* (*get_addr) (smem_mem_type smem_type, uint32 *buf_size);
  void (*boot_init)(void);
  void (*boot_debug_init)(void);
  void *(*alloc)(smem_mem_type smem_type, uint32 buf_size);
  uint32 (*image_version_populate_version)(image_index_type image_index);
  uint32 (*image_version_initialize_version_table)(void);
  void (*image_populate_uuid)(void);
} boot_smem_if_type;


/*===========================================================================
**  Function :  boot_smem_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_smem_get_interface
*
* @par Dependencies
*   None 
* 
*/

//bl_error_boot_type boot_smem_get_interface(boot_smem_if_type *smem_if);


extern boot_smem_if_type smem_if;


#endif /* BOOT_SMEM_IF_H */

