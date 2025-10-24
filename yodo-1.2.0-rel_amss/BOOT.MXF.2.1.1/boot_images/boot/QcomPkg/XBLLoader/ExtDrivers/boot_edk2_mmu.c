/*===========================================================================

GENERAL DESCRIPTION
  This module contains the initial memory map for SBL.

  Copyright (c) 2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

 ==============================================================================*/
 /*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/21/20   rama    Initial revision
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <boot_edk2_mmu_if.h>

/*=============================================================================
   
                              FUNCTION DEFINITIONS

=============================================================================*/
/*===========================================================================
**  Function :  boot_cachelib_if
** ==========================================================================
*/
/*!
* 
* @brief
*   This function table initializes a edk2 mmulib interface
*
* @par Dependencies
*   None 
* 
*/
boot_edk2_mmu_if_type edk2_mmu_if = {
  ArmConfigureMmu,
  ArmSetMemoryAttributes
};
