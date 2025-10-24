/*! @file PmicSdamProtocol.c 

 *  PMIC-SDAM MODULE RELATED DECLARATION
 *  This file contains functions and variable declarations to support 
 *  the PMIC SDAM module.
 *
 *  Copyright (c) 2019, 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
 *  Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when        who     what, where, why
----------  ---     ---------------------------------------------------------- 
2019-10-21   rh     Created
===========================================================================*/

/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include "pm_uefi.h"
#include "pm_sdam.h"

#include <Protocol/EFIPmicSdam.h>

/*===========================================================================
                  EXTERNAL FUNCTION DECLARATIONS
===========================================================================*/

/**
  EFI_PmicSdamMemRead ()

  @brief
  SdamMemRead implementation of EFI_QCOM_PMIC_SDAM_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicSdamMemRead
(
  IN   UINT32                     PmicDeviceIndex, 
  IN   UINT32                     SdamSrcIndex,
  IN   UINT8                      StartAddress,
  IN   UINT32                     NumOfBytes,
  OUT  UINT8                      *DataPtr
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

  errFlag = pm_sdam_mem_read((uint8)PmicDeviceIndex, (pm_sdam_type)SdamSrcIndex, StartAddress, NumOfBytes, DataPtr);

  if (errFlag)
  {
     return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmicSdamMemWrite ()

  @brief
  SdamMemRead implementation of EFI_QCOM_PMIC_SDAM_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicSdamMemWrite
(
  IN   UINT32                     PmicDeviceIndex, 
  IN   UINT32                     SdamSrcIndex,
  IN   UINT8                      StartAddress,
  IN   UINT32                     NumOfBytes,
  IN   UINT8                      *DataPtr
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

  errFlag = pm_sdam_mem_write((uint8)PmicDeviceIndex, (pm_sdam_type)SdamSrcIndex, StartAddress, NumOfBytes, DataPtr);

  if (errFlag)
  {
     return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}


/**
  PMIC SDAM UEFI Protocol implementation
 */
EFI_QCOM_PMIC_SDAM_PROTOCOL PmicSdamProtocolImplementation = 
{
    PMIC_SDAM_REVISION,
    EFI_PmicSdamMemRead,
    EFI_PmicSdamMemWrite
    
};
	
