/*! @file PmicVersionProtocol.c 

 *  PMIC-VERSION MODULE RELATED DECLARATION
 *  This file contains functions and variable declarations to support 
 *  the PMIC GPIO module.
 *
 *  Copyright (c) 2012 - 2020, 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
 *  Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
13/12/13   aa      PmicLib Dec Addition
04/11/13   al      Created
===========================================================================*/

/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include "pm_uefi.h"
#include "pm_version.h"

#include <Protocol/EFIPmicVersion.h>

/*===========================================================================
                  EXTERNAL FUNCTION DECLARATIONS
===========================================================================*/

/**
  EFI_PmicGetPmicInfo ()

  @brief
  GetPmicInfo implementation of EFI_QCOM_PMIC_VERSION_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicGetPmicInfo
(
  IN   UINT32                     PmicDeviceIndex, 
  OUT  EFI_PM_DEVICE_INFO_TYPE    *DeviceInfo
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  pm_device_info_type PmicDeviceInfo = {0};

  errFlag = pm_get_pmic_info((uint8)PmicDeviceIndex, &PmicDeviceInfo);

  if (errFlag || (!DeviceInfo))
  {
     return EFI_DEVICE_ERROR;
  }

  DeviceInfo->PmicModel = (EFI_PM_MODEL_TYPE )PmicDeviceInfo.ePmicModel;
  DeviceInfo->PmicAllLayerRevision = (UINT32)PmicDeviceInfo.nPmicAllLayerRevision;
  DeviceInfo->PmicMetalRevision = (UINT32)PmicDeviceInfo.nPmicMetalRevision;
  DeviceInfo->SlaveCount    = (UINT32)PmicDeviceInfo.nSlaveCount;

  return EFI_SUCCESS;

}

EFI_STATUS
EFIAPI
EFI_PmicGetPrimaryPmicIndex
(
   OUT  UINT32    *PrimaryPmicIndex
)
{
   EFI_STATUS Status = EFI_SUCCESS;

   UINT32 PrimaryPmic = 0;

   PrimaryPmic = pm_get_primary_pmic_index();

   if (NULL != PrimaryPmicIndex)
   {
      *PrimaryPmicIndex = PrimaryPmic;
   }
   else
   {
      Status = EFI_DEVICE_ERROR;
   }

   return Status;
}


/**
  PMIC VERSION UEFI Protocol implementation
 */
EFI_QCOM_PMIC_VERSION_PROTOCOL PmicVersionProtocolImplementation = 
{
    EFI_PMIC_VERSION_REVISION_1,
    EFI_PmicGetPmicInfo,
    EFI_PmicGetPrimaryPmicIndex
    
};
	
