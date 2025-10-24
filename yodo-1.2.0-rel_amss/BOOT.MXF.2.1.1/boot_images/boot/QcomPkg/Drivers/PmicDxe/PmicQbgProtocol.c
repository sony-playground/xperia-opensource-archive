/*! @file PmicQbgProtocol.c 

*  PMIC- QBG MODULE RELATED DECLARATION
*  This file contains functions and variable declarations to support 
*  the PMIC QBG module.
*
*  Copyright (c) 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Inc Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     --------------------------------------------------------------------------
02/21/20   xp      Initial draft
===========================================================================*/

/*===========================================================================

INCLUDE FILES FOR MODULE

===========================================================================*/
#include <Library/UefiBootServicesTableLib.h>

#include "EFIPmicQbg.h"
#include "PmicFileLog.h"


/**
  PMIC Lib interfaces
 */
#include "pm_uefi.h"
#include "pm_core_utils.h"
#include "pm_qbg.h"
#include "pm_chg.h"


/**
EFI_PmicQbgGetPmicInfo()

@brief
Provides PMIC Index on which QBG resides
*/
EFI_STATUS
EFIAPI
EFI_PmicQbgGetPmicInfo
(
  OUT EFI_PM_QBG_PMIC_INFO *QbgPmicInfo
)
{
  if(QbgPmicInfo == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  QbgPmicInfo->PmicIndex = 3;
  QbgPmicInfo->SlaveIndex = 3;
  return EFI_SUCCESS;
}

/**
EFI_PmicQbgDumpPeripheral()

@brief
 Dump QBG Pheripheral
 */
EFI_STATUS
EFIAPI
EFI_PmicQbgDumpPeripheral( VOID )
{
  return EFI_SUCCESS;
}

/**
EFI_PmicQbgInit()

@brief
Initializes Fule Gauge Module
*/
EFI_STATUS
EFIAPI
EFI_PmicQbgInit
(
  UINT32                      PmicDeviceIndex
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  /* Enable after verification */
  EFI_PmicQbgDumpPeripheral();

  return Status;
}

/**
EFI_PmicQbgExit()

@brief
Exit Fule Gauge Module
*/
EFI_STATUS
EFIAPI
EFI_PmicQbgExit
(
  UINT32 PmicDeviceIndex
)
{
  return EFI_SUCCESS;
}




/**
EFI_PmicQbgBatteryStatus()

@brief
Returns Battery Status parameters such as State of Charge (SOC)
*/
EFI_STATUS
EFIAPI
EFI_PmicQbgGetBatteryStatus
(
   IN  UINT32         PmicDeviceIndex,
   OUT EFI_PM_QBG_BATT_STATUS_INFO *BattStsInfo
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

  if(NULL == BattStsInfo)
  {
    return EFI_INVALID_PARAMETER;
  }
  errFlag = pm_chg_get_vbatt((uint32*)&(BattStsInfo->BatteryVoltage));
  errFlag |= pm_chg_get_ibatt(&(BattStsInfo->ChargeCurrent));
  BattStsInfo->StateOfCharge = 15; //todo this is a dummy value
  BattStsInfo->BatteryTemperature = 25; //todo this is a dummy value
  Status = (errFlag == PM_ERR_FLAG_SUCCESS) ? EFI_SUCCESS: EFI_DEVICE_ERROR;
  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicQbgGetBatteryId
(
  OUT EFI_PM_QBG_BATTERY_ID* BatteryId
)
{
  return EFI_SUCCESS;
}


/**
EFI_PmicQbgBatteryPresent()

@brief
Provides if battery is missing
*/
EFI_STATUS
EFIAPI
EFI_PmicQbgBatteryPresent
( 
  IN UINT32 PmicDeviceIndex, 
  OUT BOOLEAN *isBatteryPresent
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  pm_qbg_status_type qbg_status = {0};
  pm_qbg_fsm_staus_type qbg_fsm_state = PM_QBG_FSM_INVALID;
  if(NULL == isBatteryPresent)
  {
    return EFI_INVALID_PARAMETER;
  }
  errFlag = pm_qbg_get_status(PmicDeviceIndex, &qbg_status, &qbg_fsm_state);
  Status = (errFlag == PM_ERR_FLAG_SUCCESS) ? EFI_SUCCESS: EFI_DEVICE_ERROR;
  *isBatteryPresent = qbg_status.battery_present;
  return Status;
}


/**
  PMIC Lib interfaces
 */

 /**
   PMIC QBG Basic UEFI Protocol implementation
  */
EFI_QCOM_PMIC_QBG_PROTOCOL PmicQbgProtocolImplementation =
{
  .Revision                               = PMIC_QBG_REVISION,
  .GetPmicInfo                            = EFI_PmicQbgGetPmicInfo,
  .Init                                   = EFI_PmicQbgInit,
  .Exit                                   = EFI_PmicQbgExit,
  .DumpPeripheral                         = EFI_PmicQbgDumpPeripheral,
  .GetBatteryStatus                       = EFI_PmicQbgGetBatteryStatus,
  .GetBatteryId                           = EFI_PmicQbgGetBatteryId,
  .IsBatteryPresent                       = EFI_PmicQbgBatteryPresent,
};

