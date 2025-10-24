/*! @file PmicScpqProtocol.c 

*  PMIC- SCPQ MODULE RELATED DECLARATION
*  This file contains functions and variable declarations to support 
*  the PMIC SCPQ module.
*
*  Copyright (c) 2020-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
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

#include "EFIPmicScpq.h"
#include "PmicFileLog.h"

/**
  PMIC Lib interfaces
 */
#include "pm_uefi.h"
#include "pm_core_utils.h"
#include "pm_scpq_usb.h"
#include "pm_scpq_chgr.h"
#include "pm_scpq_typec.h"
#include "pm_scpq_dcdc.h"

#define PMIC_SCPQ_MAX_APSD_DONE_CHECK_ITERATION 5
#define PM_SCPQ_200_MS_WAIT 200000 //200 milli Second wait

#define CHARGER_PMIC_IDX    7

/**
EFI_PmicScpqIsBatteryPresent ()

@brief
Gets battery presence status
*/
EFI_STATUS
EFIAPI
EFI_PmicScpqIsBatteryPresent
(
  IN UINT32 PmicDeviceIndex,
  OUT BOOLEAN *BatteryPresent
)
{
  return EFI_SUCCESS;
}

/**
EFI_PmicScpqDumpPeripheral()

@brief
 Dump SCPQ Peripheral
 */
EFI_STATUS
EFIAPI
EFI_PmicScpqDumpPeripheral( VOID )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicScpqGetChargingStatus
(
  UINT32 PmicDeviceIndex,
  OUT EFI_PM_SCPQ_CHARGING_STATUS *pChargingStatus
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicScpqDCInValid
(
  IN UINT32 PmicDeviceIndex,
  OUT BOOLEAN *Valid
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicScpqGetChgWdogStatus
(
  IN UINT32 PmicDeviceIndex,
  OUT EFI_PM_SCPQ_WDOG_STS_TYPE *pWdogSts
)
{
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicScpqGetIclStatus
(
  IN UINT32 PmicDeviceIndex,
  OUT EFI_PM_SCPQ_ICL_STATUS *pIclStatus
)
{
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicScpqGetDCIrqStatus
(
  IN UINT32 PmicDeviceIndex,
  IN EFI_PM_SCPQ_DC_IRQ_TYPE irq,
  OUT BOOLEAN* irq_status
)
{
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicScpqGetBatteryMissingStatus
(
  IN UINT32 PmicDeviceIndex,
  IN EFI_PM_SCPQ_BATTERY_MISSING_STATUS_TYPE status_type,
  OUT BOOLEAN* status_val
)
{
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicScpqGetActivePort
(
  OUT UINT8* active_pmic_index
)
{
  return EFI_SUCCESS;
}



/**
EFI_PmicScpqGetPmicInfo ()

@brief
Provides SCPQ charger PMIC Index.
*/
EFI_STATUS
EFIAPI
EFI_PmicScpqGetPmicInfo
(
  OUT EFI_PM_SCPQ_PMIC_INFO *ScpqPmicInfo
)
{
  ScpqPmicInfo->PmicIndex = CHARGER_PMIC_IDX;
  ScpqPmicInfo->SlaveIndex = CHARGER_PMIC_IDX;
  return EFI_SUCCESS;
}

EFI_STATUS
EFI_PmicScpqGetChargerPmicIndex
(
    OUT UINT8 *ChargerPmicIndex
)
{
	if(NULL == ChargerPmicIndex)
		return EFI_INVALID_PARAMETER;
	else{
		pm_chg_get_primary_charger_pmic_index((UINT32*)ChargerPmicIndex);
	}
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicScpqUsbinValid
(
  IN UINT32 PmicDeviceIndex,
  OUT BOOLEAN *Valid
)
{
  pm_err_flag_type errFlag;
  if(NULL == Valid)
  {
    return EFI_INVALID_PARAMETER;
  }

  errFlag = pm_scpq_usb_irq_status(PmicDeviceIndex, PM_SCPQ_USB_IRQ_USBIN_PLUGIN, PM_IRQ_STATUS_RT, Valid);

  return (errFlag == PM_ERR_FLAG_SUCCESS) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
}

EFI_STATUS
EFIAPI
EFI_PmicScpqGetPowerPath
(
  IN UINT32 PmicDeviceIndex,
  OUT PM_SCPQ_POWER_PATH_TYPE *PowerPath
)
{
  pm_scpq_chgr_status_type chargerStatus = {0};
  pm_err_flag_type errFlag;
  if(NULL == PowerPath)
  {
    return EFI_INVALID_PARAMETER;
  }

  errFlag = pm_scpq_chgr_get_chgr_status(PmicDeviceIndex, &chargerStatus);
  if(errFlag == PM_ERR_FLAG_SUCCESS)
  {
    if(chargerStatus.charger_status.valid_input_power_source)
    {
      //either usb or wireless
      BOOLEAN Valid = FALSE;
      errFlag = pm_scpq_usb_irq_status(PmicDeviceIndex, PM_SCPQ_USB_IRQ_USBIN_PLUGIN, PM_IRQ_STATUS_RT, &Valid);
      if(errFlag == PM_ERR_FLAG_SUCCESS)
      {
        if(Valid) 
        { 
          *PowerPath = PM_SCPQ_POWER_PATH__USBIN; 
        }
        else
        {
          *PowerPath = PM_SCPQ_POWER_PATH__DCIN; 
        }        
      }
      else
      {
        //todo print out error.
        *PowerPath = PM_SCPQ_POWER_PATH__INVALID; 
        return EFI_DEVICE_ERROR;
      }            
    }
    else
    {
      *PowerPath = PM_SCPQ_POWER_PATH__BATTERY; 
    }

    return EFI_SUCCESS;
  }

  return EFI_DEVICE_ERROR;
}

/**
EFI_PmicChargerPortType ()

@brief
Gets charger port type
*/
EFI_STATUS
EFIAPI
EFI_PmicScpqGetChargerPortType
(
  IN UINT32 PmicDeviceIndex,
  OUT EFI_PM_SCPQ_CHGR_PORT_TYPE *PortType
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  BOOLEAN ApsdDoneStatus = FALSE;
  UINT32 ApsdDoneCheckIteration = 0;

  if(NULL == PortType)
  {
    return EFI_INVALID_PARAMETER;
  }

  *PortType = EFI_PM_SCPQ_CHG_PORT_INVALID;

  do
  {
    errFlag = pm_scpq_usb_get_apsd_status(PmicDeviceIndex, PM_SCPQ_USB_APSD_STATUS_APSD_DTC_STATUS_DONE , &ApsdDoneStatus);
    PMIC_UART_DEBUG(( EFI_D_WARN, "PmicDxe:: %a APSD done status: %d \n\r", __FUNCTION__, ApsdDoneStatus));
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      break;
    }

    if(TRUE == ApsdDoneStatus)
    {
      errFlag =  pm_scpq_usb_get_apsd_result_status(PmicDeviceIndex, (pm_chg_charger_port_type*) PortType);
      if(PM_ERR_FLAG_SUCCESS != errFlag)
      {
        break;
      }
    }
    else
    {
      /*if APSD result is not available yet, read again after 200 milli second.*/
      PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a APSD not done, stalling for 200mS before re-checking \n\r", __FUNCTION__));
      gBS->Stall(PM_SCPQ_200_MS_WAIT);
    }

    ApsdDoneCheckIteration ++;

  }while ((FALSE == ApsdDoneStatus) && (ApsdDoneCheckIteration < PMIC_SCPQ_MAX_APSD_DONE_CHECK_ITERATION));

  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    *PortType = EFI_PM_SCPQ_CHG_PORT_INVALID;
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicScpqGetOtgStatus
(
  IN UINT32 PmicDeviceIndex,
  OUT EFI_PM_SCPQ_DCDC_OTG_STATUS_TYPE* pOtgStatus
)
{
  EFI_STATUS         Status      = EFI_SUCCESS;
  pm_err_flag_type   err_flag    = PM_ERR_FLAG_SUCCESS;
  pm_scpq_dcdc_otg_status_type TempOtgStatus = PM_SCPQ_DCDC_OTG_STATUS_INVALID;

  err_flag = pm_scpq_dcdc_get_otg_status(PmicDeviceIndex, &TempOtgStatus);

  switch (TempOtgStatus)
  {
  case PM_SCPQ_DCDC_OTG_DISABLED: 
    *pOtgStatus = EFI_PM_SCPQ_DCDC_OTG_DISABLED;
    break;
  case PM_SCPQ_DCDC_OTG_EXECUTING_ENABLE_SEQ: 
    *pOtgStatus = EFI_PM_SCPQ_DCDC_OTG_EXECUTING_ENABLE_SEQ;
    break;
  case PM_SCPQ_DCDC_OTG_ENABLED: 
    *pOtgStatus = EFI_PM_SCPQ_DCDC_OTG_ENABLED;
    break;
  case PM_SCPQ_DCDC_OTG_EXECUTING_DISABLE_SEQ: 
    *pOtgStatus = EFI_PM_SCPQ_DCDC_OTG_EXECUTING_DISABLE_SEQ;
    break;
  case PM_SCPQ_DCDC_OTG_STATUS_INVALID: 
    *pOtgStatus = EFI_PM_SCPQ_DCDC_OTG_DISABLED;
    break;
  case PM_SCPQ_DCDC_OTG_ERROR: 
    *pOtgStatus = EFI_PM_SCPQ_DCDC_OTG_ERROR;
    break;
  default: 
    *pOtgStatus = EFI_PM_SCPQ_DCDC_OTG_ERROR;
  }

  Status = (PM_ERR_FLAG_SUCCESS == err_flag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}

EFI_STATUS EFI_PmicScpqGetPortState
(
  IN UINT32 PmicDeviceIndex,
  OUT EFI_PM_SCPQ_TYPEC_PORT_STATUS* TypeCStatus
)
{
  pm_err_flag_type errFlag;
  pm_chg_typec_status_type typec_status = { 0 };

  if (!TypeCStatus)
  {
    return EFI_INVALID_PARAMETER;
  }

  errFlag = pm_scpq_usb_get_typec_status(PmicDeviceIndex, &typec_status);
  if (PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }
  else
  {
    TypeCStatus->cc_out_sts = (EFI_PM_SCPQ_TYPEC_CC_OUT_STATUS)typec_status.cc_out_sts;
    TypeCStatus->dfp_curr_adv = (EFI_PM_SCPQ_TYPEC_DFP_CURR_ADV)typec_status.dfp_curr_adv;
    TypeCStatus->ufp_conn_type = (EFI_PM_SCPQ_TYPEC_UFP_CONNECTOR_TYPE)typec_status.ufp_conn_type;
    TypeCStatus->vbus_sts = typec_status.vbus_sts;
    TypeCStatus->vbus_err_sts = typec_status.vbus_err_sts;
    TypeCStatus->debounce_done_sts = typec_status.debounce_done_sts;
    TypeCStatus->vconn_oc_sts = typec_status.vconn_oc_sts;
    TypeCStatus->ccout_out_hiz_sts = typec_status.ccout_out_hiz_sts;
  }

  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicScpqGetConnectState
(
  IN UINT32 PmicDeviceIndex,
  OUT EFI_PM_SCPQ_TYPEC_CONNECT_MODE_STATUS* TypeCConnStatus
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  pm_chg_typec_port_role_type port_role = PM_CHG_TYPEC_ROLE_NONE;

  if (!TypeCConnStatus)
  {
    return EFI_INVALID_PARAMETER;
  }

  errFlag = pm_scpq_usb_typec_get_port_role(PmicDeviceIndex, &port_role);
  if (PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }
  else
  {
    *TypeCConnStatus = (EFI_PM_SCPQ_TYPEC_CONNECT_MODE_STATUS)port_role;
  }

  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicScpqSetOS
(
IN EFI_PM_SCHG_OS_TYPE OS
)
{
  return EFI_SUCCESS;
}

EFI_QCOM_PMIC_SCPQ_PROTOCOL PmicScpqProtocolImplementation =
{
  .Revision                     = PMIC_SCPQ_REVISION,
  .GetPmicInfo                  = EFI_PmicScpqGetPmicInfo,
  .DumpPeripheral               = EFI_PmicScpqDumpPeripheral,
  .UsbinValid                   = EFI_PmicScpqUsbinValid,
  .DcinValid                    = EFI_PmicScpqDCInValid,
  .GetPowerPath                 = EFI_PmicScpqGetPowerPath,
  .IsBatteryPresent             = EFI_PmicScpqIsBatteryPresent,
  .GetChargerPortType           = EFI_PmicScpqGetChargerPortType,
  .GetOtgStatus                 = EFI_PmicScpqGetOtgStatus,
  .GetChargingStatus            = EFI_PmicScpqGetChargingStatus,
  .GetIclStatus                 = EFI_PmicScpqGetIclStatus,
  .GetPortState                 = EFI_PmicScpqGetPortState,
  .GetConnectState              = EFI_PmicScpqGetConnectState,
  .GetDcIrqStatus               = EFI_PmicScpqGetDCIrqStatus,
  .GetBatteryMissingStatus      = EFI_PmicScpqGetBatteryMissingStatus,
  .SetOS                        = EFI_PmicScpqSetOS,
  .GetChargerPmicIndex          = EFI_PmicScpqGetChargerPmicIndex,
};



