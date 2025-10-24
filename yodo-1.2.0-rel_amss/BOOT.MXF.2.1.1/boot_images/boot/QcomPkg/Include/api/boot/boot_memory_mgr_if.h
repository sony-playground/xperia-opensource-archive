#ifndef BOOT_MEMORY_MGR_IF_H
#define BOOT_MEMORY_MGR_IF_H
/*===========================================================================

                    BOOT MEMORY MGR IF DEFINITIONS

DESCRIPTION
  Contains definition for memory manager 

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2011-2012, 2014, 2017, 2018, 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/16/21   rama    Added uncached malloc.
08/02/19   ep      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 



typedef struct boot_memory_mgr_if_type
{
  bl_error_boot_type (*malloc)(uint32 dwSize, void **ppMem);
  bl_error_boot_type (*memalign)(uint32 dwSize, uint32 alignment, void **ppMem);
  bl_error_boot_type (*malloc_uncached) (uint32 dwSize, void **ppMem);
  bl_error_boot_type (*free)(void *pmem);
} boot_memory_mgr_if_type;



/*===========================================================================
**  Function :  boot_memory_mgr_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_memory_mgr_get_interface
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_memory_mgr_get_interface(boot_memory_mgr_if_type *memory_mgr_if);



#endif /* BOOT_MEMORY_MGR_IF_H */
