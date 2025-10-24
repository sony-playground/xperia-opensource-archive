/*! @file PmicChgProtocol.c 

*  PMIC- CHG MODULE RELATED DECLARATION
*  This file contains functions and variable declarations to support 
*  the PMIC CHG (Charger) module.
*
*  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Inc Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     --------------------------------------------------------------------------
06/29/22   dv      Creating protocol.

===========================================================================*/

/*===========================================================================

INCLUDE FILES FOR MODULE

===========================================================================*/

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/QcomTargetLib.h>

/**
  PMIC Lib interfaces
 */
#include <Protocol/EFIPmicChg.h>
#include "pm_chg.h"


/*===========================================================================
EXTERNAL FUNCTION DECLARATIONS
===========================================================================*/

EFI_STATUS
EFIAPI
EFI_PmicChgGetPrimaryChgrPmicIndex
(
  OUT UINT32 *PrimaryChgrPmicIndex
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  
  if(NULL == PrimaryChgrPmicIndex)
  {
    return EFI_INVALID_PARAMETER;
  }

  errFlag = pm_chg_get_primary_charger_pmic_index(PrimaryChgrPmicIndex);
  Status = (errFlag == PM_ERR_FLAG_SUCCESS) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
  
  return Status;
}


/**
PMIC CHG UEFI Protocol implementation
*/
EFI_QCOM_PMIC_CHG_PROTOCOL PmicChgProtocolImplementation = 
{
  EFI_PMIC_CHG_REVISION_1,
  EFI_PmicChgGetPrimaryChgrPmicIndex
};
