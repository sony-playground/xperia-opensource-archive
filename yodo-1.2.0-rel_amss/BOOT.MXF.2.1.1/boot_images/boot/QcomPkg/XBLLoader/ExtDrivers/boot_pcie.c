/*===========================================================================

                    BOOT PCIe IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external pcie drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2021 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/06/21   ck     Initial creation

===========================================================================*/

/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "boot_pcie_if.h"
#include "pcie_boot.h"


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

/*===========================================================================
**  Function :  boot_pcie_get_interface
** ==========================================================================
*/
bl_error_boot_type boot_pcie_get_interface(void *pcie_ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  
  do
  {
    if(pcie_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_PCIE, BL_ERR_INVALID_PARAMETER);
      break;
    }
    
    boot_pcie_if_type *pcie_if = (boot_pcie_if_type *)pcie_ptr;
    
    pcie_if->reg_dump           = pcie_reg_dump;
   
  } while(FALSE);
  
  return return_status;
}

