#ifndef BOOT_MEMORY_MGR_DAL_H
#define BOOT_MEMORY_MGR_DAL_H
/*===========================================================================

                    BOOT MEMORY MGR IF DEFINITIONS

DESCRIPTION
  Contains definition for memory manager 

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2011-2012, 2014, 2017, 2018 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/02/19   ep      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"
#include "boot_memory_mgr_if.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 




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

bl_error_boot_type boot_memory_mgr_get_interface_dal(boot_memory_mgr_if_type *memory_mgr_if);


extern boot_memory_mgr_if_type memory_mgr_dal;


#endif /* BOOT_MEMORY_MGR_IF_H */
