#ifndef BOOT_PCIE_IF_H
#define BOOT_PCIE_IF_H

/*===========================================================================
                    BOOT PCIE IF DEFINITIONS

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
01/06/21   ck      Initial creation

===========================================================================*/

#include "boot_error_if.h"


typedef struct boot_pcie_if_type
{
  void (*reg_dump)(void * dump_addr, uint32 max_size);
} boot_pcie_if_type;


/*===========================================================================
**  Function :  boot_pcie_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_pcie_get_interface
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_pcie_get_interface(void *pcie_ptr);

#endif /* BOOT_PCIE_IF_H */
