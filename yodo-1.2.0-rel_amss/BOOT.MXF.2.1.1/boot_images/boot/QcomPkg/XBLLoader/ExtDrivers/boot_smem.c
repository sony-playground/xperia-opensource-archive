/*===========================================================================

                    BOOT SMEM WRAPPER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external smem drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019 by Qualcomm Technologies Incorporated.  All Rights Reserved.
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
#include "MIprogressive.h"
#include "boot_error_if.h"
#include "smem_v.h"
#include "image_version.h"
#include "image_uuid.h"
#include "boot_smem_if.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


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
/*
bl_error_boot_type boot_smem_get_interface(boot_smem_if_type *smem_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(smem_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SMEM, BL_ERR_INVALID_PARAMETER);
      break;
    }

    smem_if->boot_init = smem_boot_init;
    smem_if->boot_debug_init = smem_boot_debug_init;
    smem_if->alloc = smem_alloc;
    smem_if->image_version_populate_version = image_version_populate_version;
    smem_if->image_version_initialize_version_table = image_version_initialize_version_table;
    smem_if->image_populate_uuid = image_version_uuid_init;

  } while(FALSE);

  return return_status;
}
*/

boot_smem_if_type smem_if = {
    smem_init,
    smem_get_addr,
    smem_boot_init,
    smem_boot_debug_init,
    smem_alloc,
    image_version_populate_version,
    image_version_initialize_version_table,
    image_version_uuid_init
};
