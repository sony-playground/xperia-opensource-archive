/*! @file PmicPowerOnProtocol.c 

 *  PMIC-POWERON MODULE RELATED DECLARATION
 *  This file contains functions and variable declarations to support 
 *  the PMIC POWERON module.
 *
 * Copyright (c) 2012-2022 Qualcomm Technologies, Inc.  All Rights Reserved. 
 * Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
12/20/21   bxr     Update python decode error to genarate uefi build report 
                   with build option "-y, -Y"
05/27/19   sg      Boot to HLOS directly if POFF is due to Pmic FAULT
12/29/16   cs      Adding PON protocol API to enable/disable edge trigger
05/10/16   al      Adding PON protocol and removing deprecated ones
01/22/16   al      Added API to write to spare registers
09/16/15   al      Updating Xvdd reading API
05/05/15   al      Adding API to read PON real time irq status
04/21/15   sv      Removed unwanted variable check from PonTrigger API.
01/14/15   al      Adding API to enable/disable PON trigger
06/09/14   al      Arch update
05/19/14   sm      Added API to get PBL_PON Status
                   Deprecated GetBatteryRemovedStatus API
04/29/14   al      Deprecating unsupported APIs
02/20/14   al      Adding watchdog APIs 
13/12/13   aa      PmicLib Dec Addition
01/29/13   al      Cleaning compiler warnings  
01/24/13   al      Adding API to get pmic on/off/reset reason 
11/01/12   al      Battery removal status 
10/25/12   al      File renamed 
02/27/12   al      Added device index and resource index
04/11/12   dy      Add GetWatchDogStatus API
04/04/12   al      Added API EFI_PmicPwrUpHardReset 
03/20/12   sm      New file.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

/**
  EFI interfaces
 */
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include "DALSys.h"

/**
  PMIC Lib interfaces
 */
#include "pm_uefi.h"
#include "pm_pon.h"
#include "pm_pon_hlos.h"
#include "pm_version.h"
#include "Protocol/EFIPmicPwrOn.h"

/*===========================================================================
                  EXTERNAL FUNCTION DECLARATIONS
===========================================================================*/


/**
  EFI_PmicPwronGetPonPblStatus ()

  @brief
  GetPonPblStatus implementation of EFI_QCOM_PMIC_POWERON_PROTOCOL
 */
EFI_STATUS 
EFIAPI 
EFI_PmicPwronGetPonPblStatus
(
  IN  UINT32 PmicDeviceIndex, 
  IN  EFI_PM_PWRON_PON_PBL_STATUS_TYPE PblStatusType,
  OUT BOOLEAN *Status
)
{
  pm_err_flag_type  errFlag = PM_ERR_FLAG_SUCCESS;

  if(!Status)
  {
    return EFI_INVALID_PARAMETER;
  }
   
  switch(PblStatusType)
  {
  case EFI_PM_PWRON_PON_PBL_STATUS_DVDD_RB_OCCURRED:
    errFlag = pm_pon_pbl_get_status(PmicDeviceIndex, PM_PON_PBL_DVDD_RB_OCCURRED, Status);
    break;
  case EFI_PM_PWRON_PON_PBL_STATUS_XVDD_RB_OCCURRED:
    errFlag = pm_pon_pbl_get_status(PmicDeviceIndex, PM_PON_PBL_XVDD_RB_OCCURRED, Status);
    break;
  default:
    errFlag = PM_ERR_FLAG_INVALID_PARAMETER;
    break;
  }

  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmicPwronSetPonTrigger ()

  @brief
  EFI_PmicPwronSetPonTrigger implementation of EFI_PM_PWRON_SET_PON_TRIGGER 
 */
EFI_STATUS 
EFIAPI 
EFI_PmicPwronSetPonTrigger
(
  IN UINT32 PmicDeviceIndex, 
  IN EFI_PM_PON_TRIGGER_TYPE PonTrigger,
  OUT BOOLEAN Enable
)
{
  pm_err_flag_type  errFlag = PM_ERR_FLAG_SUCCESS;
  EFI_STATUS Status = EFI_SUCCESS;

  errFlag = pm_pon_trigger_enable(PmicDeviceIndex, (pm_pon_trigger_type)PonTrigger, Enable);

  Status = (PM_ERR_FLAG_SUCCESS == errFlag)? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}


pm_pon_hlos_irq_type pon_hlos_irq_map(EFI_PM_PON_IRQ_TYPE PonIrqType)
{
    pm_pon_hlos_irq_type irq_type = PM_PON_HLOS_IRQ_INVALID;

    switch(PonIrqType)
    {
    case EFI_PM_PON_IRQ_KPDPWR_ON :
        irq_type = PM_PON_HLOS_IRQ_KPD_PWR_N_DEB;
        break;
    case EFI_PM_PON_IRQ_RESIN_ON :
        irq_type = PM_PON_HLOS_IRQ_RESIN_N_DEB;
        break;
    case EFI_PM_PON_IRQ_CBLPWR_ON :
        irq_type = PM_PON_HLOS_IRQ_INVALID;
        break;
    case EFI_PM_PON_IRQ_KPDPWR_BARK :
        irq_type = PM_PON_HLOS_IRQ_KPDPWR_N_S1;
        break;
    case EFI_PM_PON_IRQ_RESIN_BARK :
        irq_type = PM_PON_HLOS_IRQ_RESIN_N_S1;
        break;
    case EFI_PM_PON_IRQ_KPDPWR_RESIN_BARK :
        irq_type = PM_PON_HLOS_IRQ_RESIN_AND_KPDPWR_S1;
        break;
    case EFI_PM_PON_IRQ_PMIC_WD_BARK :
        irq_type = PM_PON_HLOS_IRQ_PMIC_WDOG_S1;
        break;
    case EFI_PM_PON_IRQ_SOFT_RESET :
        irq_type = PM_PON_HLOS_IRQ_SW_RESET;
        break;
    case EFI_PM_PON_IRQ_INVALID  :
        irq_type = PM_PON_HLOS_IRQ_INVALID;
        break;
    default  :
        irq_type = PM_PON_HLOS_IRQ_INVALID;
        break;
    }

    return irq_type;

}


/**
  EFI_PmicPwronIrqEnable ()

  @brief
  EFI_PmicPwronIrqEnable enable/disable one the interrupt of PON module
 */
EFI_STATUS 
EFIAPI 
EFI_PmicPwronIrqEnable
(
  IN UINT32              PmicDeviceIndex, 
  IN EFI_PM_PON_IRQ_TYPE PonIrqType,
  IN BOOLEAN             enable
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  pm_err_flag_type  errFlag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = pm_get_primary_pmic_index();
  
  if(PonIrqType >= EFI_PM_PON_IRQ_INVALID)
  {
    return EFI_DEVICE_ERROR;
  }
  
  if(pm_get_pmic_model(pmic_index) == PMIC_IS_PM8250)
  {
    errFlag = pm_pon_irq_enable(PmicDeviceIndex, (pm_pon_irq_type)PonIrqType, enable);
  }
  else
  {
    errFlag = pm_pon_hlos_irq_enable(PmicDeviceIndex, pon_hlos_irq_map( PonIrqType ), enable);
  }
  
  Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}

/**
  EFI_PmicPwronIrqClear ()

  @brief
  EFI_PmicPwronIrqClear clear one of latched interrupt status of PON module
 */
EFI_STATUS 
EFIAPI 
EFI_PmicPwronIrqClear
(
  IN UINT32              PmicDeviceIndex, 
  IN EFI_PM_PON_IRQ_TYPE PonIrqType
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  pm_err_flag_type  errFlag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = pm_get_primary_pmic_index();
 
  if(PonIrqType >= EFI_PM_PON_IRQ_INVALID)
  {
    return EFI_DEVICE_ERROR;
  }
  
  if(pm_get_pmic_model(pmic_index) == PMIC_IS_PM8250)
  {
    errFlag = pm_pon_irq_clear(PmicDeviceIndex, (pm_pon_irq_type)PonIrqType);
  }
  else
  {
    errFlag = pm_pon_hlos_irq_clear(PmicDeviceIndex, pon_hlos_irq_map(PonIrqType));
  }
  
  Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}

/**
  EFI_PmicPwronIrqSetTrigger ()

  @brief
  EFI_PmicPwronIrqSetTrigger configures the irq trigger of PON module
 */
EFI_STATUS 
EFIAPI 
EFI_PmicPwronIrqSetTrigger
(
  IN UINT32              PmicDeviceIndex, 
  IN EFI_PM_PON_IRQ_TYPE PonIrqType,
  IN EFI_PM_PON_IRQ_TRIGGER_TYPE TriggerType
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  pm_err_flag_type  errFlag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = pm_get_primary_pmic_index();

  if(PonIrqType >= EFI_PM_PON_IRQ_INVALID
    || TriggerType >= EFI_PM_PON_IRQ_TRIGGER_INVALID)
  {
    return EFI_DEVICE_ERROR;
  }

  if(pm_get_pmic_model(pmic_index) == PMIC_IS_PM8250)
  {
    errFlag = pm_pon_irq_set_trigger(PmicDeviceIndex, (pm_pon_irq_type)PonIrqType, (pm_irq_trigger_type) TriggerType);
  }
  else
  {
    errFlag = pm_pon_hlos_irq_set_trigger(PmicDeviceIndex, pon_hlos_irq_map( PonIrqType ),
                                (pm_irq_trigger_type) TriggerType);
  }
  
  Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}


/**
  EFI_PmicPwronGetPonIrqStatus ()

  @brief
  EFI_PmicPwronGetPonIrqStatus returns the interrupt status of PON module
 */
EFI_STATUS 
EFIAPI 
EFI_PmicPwronGetPonIrqStatus
(
  IN UINT32              PmicDeviceIndex, 
  IN EFI_PM_PON_IRQ_TYPE PonIrqType,
  IN EFI_PM_PON_IRQ_STATUS_TYPE PonIrqStatusType,
  OUT BOOLEAN            *IrqStatus
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  pm_err_flag_type  errFlag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = pm_get_primary_pmic_index();
 
  if(NULL == IrqStatus ||
    PonIrqType >= EFI_PM_PON_IRQ_INVALID ||
    PonIrqStatusType >= EFI_PM_PON_IRQ_STATUS_INVALID)
  {
    return EFI_DEVICE_ERROR;
  }

  if(pm_get_pmic_model(pmic_index) == PMIC_IS_PM8250)
  {
    errFlag = pm_pon_irq_status(PmicDeviceIndex, (pm_pon_irq_type)PonIrqType,
                              (pm_irq_status_type)PonIrqStatusType, IrqStatus);
  }
  else
  {
    errFlag = pm_pon_hlos_irq_status(PmicDeviceIndex, pon_hlos_irq_map( PonIrqType ),
                              (pm_irq_status_type)PonIrqStatusType, IrqStatus);
  }
  
  Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}

/**
  EFI_PmicPwronGetPonRtStatus ()

  @brief
  EFI_PmicPwronGetPonRtStatus returns the real time interrupt status of PON module
 */
EFI_STATUS 
EFIAPI 
EFI_PmicPwronGetPonRtStatus
(
  IN UINT32              PmicDeviceIndex, 
  IN EFI_PM_PON_IRQ_TYPE PonIrqType,
  OUT BOOLEAN            *RtStatus
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  pm_err_flag_type  errFlag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = pm_get_primary_pmic_index();

  if(NULL == RtStatus)
  {
    return EFI_DEVICE_ERROR;
  }

  if(pm_get_pmic_model(pmic_index) == PMIC_IS_PM8250)
  {
    errFlag = pm_pon_irq_status(PmicDeviceIndex, (pm_pon_irq_type)PonIrqType, PM_IRQ_STATUS_RT, RtStatus);
  }
  else
  {
    errFlag = pm_pon_hlos_irq_status(PmicDeviceIndex, pon_hlos_irq_map( PonIrqType ), PM_IRQ_STATUS_RT, RtStatus);
  }
  
  Status = (PM_ERR_FLAG_SUCCESS == errFlag)? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}

EFI_STATUS 
EFIAPI 
EFI_PmicPonGetSpareReg
(
  IN UINT32                    PmicDeviceIndex, 
  IN EFI_PM_PON_SPARE_REG_TYPE SpareReg,
  OUT UINT8                    *DataPtr
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;

  pm_pon_spare_reg_type spare_reg = PM_PON_SPARE_INVALID;
 
  if(NULL == DataPtr)
  {
    return EFI_INVALID_PARAMETER;
  }

  switch(SpareReg)
  {
     case EFI_PM_PON_PERPH_SPARE:  
        spare_reg = PM_PON_PERPH_SPARE; 
        break;
     case EFI_PM_PON_DVDD_SPARE: 
        spare_reg = PM_PON_DVDD_SPARE;  
        break;
     case EFI_PM_PON_XVDD_SPARE:  
        spare_reg = PM_PON_XVDD_SPARE;  
        break;
     case EFI_PM_PON_SOFT_SPARE: 
        spare_reg = PM_PON_SOFT_SPARE;  
        break;
     default:
         spare_reg = PM_PON_SPARE_INVALID; 
         break;
  }

  err_flag = pm_pon_get_spare_reg(PmicDeviceIndex, spare_reg, DataPtr);

  Status = (PM_ERR_FLAG_SUCCESS == err_flag)? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}


EFI_STATUS 
EFIAPI 
EFI_PmicPonSetSpareReg
(
  IN UINT32                    PmicDeviceIndex, 
  IN EFI_PM_PON_SPARE_REG_TYPE SpareReg,  
  IN UINT8                     SetValue,
  IN UINT8                     Mask
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;

  pm_pon_spare_reg_type spare_reg = PM_PON_SPARE_INVALID;

    switch(SpareReg)
  {
     case EFI_PM_PON_PERPH_SPARE:  
        spare_reg = PM_PON_PERPH_SPARE; 
        break;
     case EFI_PM_PON_DVDD_SPARE: 
        spare_reg = PM_PON_DVDD_SPARE;  
        break;
     case EFI_PM_PON_XVDD_SPARE:  
        spare_reg = PM_PON_XVDD_SPARE;  
        break;
     case EFI_PM_PON_SOFT_SPARE: 
        spare_reg = PM_PON_SOFT_SPARE;  
        break;
     default:
         spare_reg = PM_PON_SPARE_INVALID; 
         break;
  }
 
  err_flag = pm_pon_set_spare_reg(PmicDeviceIndex, spare_reg, SetValue, Mask);

  Status = (PM_ERR_FLAG_SUCCESS == err_flag)? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}


EFI_STATUS 
EFIAPI 
EFI_PmicPonGetPonReason
(
   IN  UINT32                  PmicDeviceIndex, 
   OUT EFI_PM_PON_REASON_TYPE* PonReason
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;

  pm_pon_reason_type pon_reason = { 0 };

  if(NULL == PonReason)
  {
    Status = EFI_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_reason(PmicDeviceIndex, &pon_reason);

    PonReason->HARD_RESET = pon_reason.hard_reset; 
    PonReason->SMPL = pon_reason.smpl;       
    PonReason->RTC = pon_reason.rtc;        
    PonReason->DC_CHG = pon_reason.dc_chg;     
    PonReason->USB_CHG = pon_reason.usb_chg;    
    PonReason->PON1 = pon_reason.pon1;       
    PonReason->CBLPWR = pon_reason.cblpwr;     
    PonReason->KPDPWR = pon_reason.kpdpwr;     
        
    Status = (PM_ERR_FLAG_SUCCESS == err_flag)? EFI_SUCCESS : EFI_DEVICE_ERROR;
  }

  return Status;
}


EFI_STATUS 
EFIAPI 
EFI_PmicPonWarmResetStatus
(
   IN  UINT32      PmicDeviceIndex, 
   OUT BOOLEAN*    WarmReset
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;
  pm_pon_on_state_reason_type Reason;

  if(NULL == WarmReset)
  {
    Status = EFI_DEVICE_ERROR;
  }
  else
  {
    err_flag =  pm_pon_get_on_reason(PmicDeviceIndex, &Reason);

    if(err_flag == PM_ERR_FLAG_SUCCESS)
    {
      *WarmReset = (Reason.warm_seq == TRUE) ? TRUE : FALSE;
    }

    Status = (PM_ERR_FLAG_SUCCESS == err_flag)? EFI_SUCCESS : EFI_DEVICE_ERROR;
  }

  return Status;
}


EFI_STATUS 
EFIAPI 
EFI_PmicPonGetAllPonReasons
(
   IN  UINT32      PmicDeviceIndex, 
   OUT UINT64*     PonReasons
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;

  if(NULL == PonReasons)
  {
    Status = EFI_DEVICE_ERROR;
  }
  else
  {
    err_flag =  pm_pon_get_all_pon_reasons(PmicDeviceIndex, PonReasons);

    Status = (PM_ERR_FLAG_SUCCESS == err_flag)? EFI_SUCCESS : EFI_DEVICE_ERROR;
  }

  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicPonGetAllFaultReasons

(
   IN  UINT32      PmicDeviceIndex,
   OUT UINT64*     FaultReasons
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;

  if(NULL == FaultReasons)
  {
    Status = EFI_DEVICE_ERROR;
  }
  else
  {
    err_flag =  pm_pon_get_fault_reasons(PmicDeviceIndex, FaultReasons);

    Status = (PM_ERR_FLAG_SUCCESS == err_flag)? EFI_SUCCESS : EFI_DEVICE_ERROR;
  }

  return Status;
}


/**
EFI_PmicPwronEnableEdgePonTrigger ()

@brief
EFI_PmicPwronEnableEdgePonTrigger implementation of EFI_PM_PWRON_ENABLE_EDGE_PON_TRIGGER
*/
EFI_STATUS
EFIAPI
EFI_PmicPwronEnableEdgePonTrigger
(
IN UINT32 PmicDeviceIndex,
IN EFI_PM_PON_OPTION_BIT_TYPE OptionBitType,
IN BOOLEAN Enable
)
{
  pm_err_flag_type  errFlag = PM_ERR_FLAG_SUCCESS;
  EFI_STATUS Status = EFI_SUCCESS;

  errFlag = pm_pon_set_option_bit(PmicDeviceIndex, (pm_pon_option_bit_type)OptionBitType, Enable);

  Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}

#ifdef FEATURE_XBOOT

EFI_STATUS
EFIAPI
EFI_PmicPonResetSourceCfg
(
IN UINT32                       PmicDeviceIndex,
IN EFI_PM_PON_RESET_SOURCE_TYPE ResetSource,
IN UINT32                       s1TimerMs,
IN UINT32                       s2TimerMs,
IN EFI_PM_PWRON_RESET_CFG_TYPE  ResetCfgType
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  pm_pon_reset_cfg_type ponResetCfg;
  EFI_STATUS Status = EFI_SUCCESS;

  switch (ResetCfgType)
  {
  case EFI_PM_PWRON_RESET_CFG_WARM_RESET:
    ponResetCfg = PM_PON_RESET_CFG_WARM_RESET;
    break;
  case EFI_PM_PWRON_RESET_CFG_NORMAL_SHUTDOWN:
    ponResetCfg = PM_PON_RESET_CFG_NORMAL_SHUTDOWN;
    break;
  case EFI_PM_PWRON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN:
    ponResetCfg = PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN;
    break;
  case EFI_PM_PWRON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:
    ponResetCfg = PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN;
    break;
  case EFI_PM_PWRON_RESET_CFG_HARD_RESET:
    ponResetCfg = PM_PON_RESET_CFG_HARD_RESET;
    break;
  case EFI_PM_PWRON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET:
    ponResetCfg = PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET;
    break;
  case EFI_PM_PWRON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET:
    ponResetCfg = PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET;
    break;
  case EFI_PM_PWRON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:
    ponResetCfg = PM_PON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN;
    break;
  case EFI_PM_PWRON_RESET_CFG_WARM_RESET_AND_D_VDD_BATT_REMOVE_SHUTDOWN:
    ponResetCfg = PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_SHUTDOWN;
    break;
  case EFI_PM_PWRON_RESET_CFG_WARM_RESET_AND_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:
    ponResetCfg = PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_SHUTDOWN;
    break;
  case EFI_PM_PWRON_RESET_CFG_WARM_RESET_AND_SHUTDOWN:
    ponResetCfg = PM_PON_RESET_CFG_WARM_RESET_THEN_SHUTDOWN;
    break;
  case EFI_PM_PWRON_RESET_CFG_WARM_RESET_THEN_HARD_RESET:
    ponResetCfg = PM_PON_RESET_CFG_WARM_RESET_THEN_HARD_RESET;
    break;
  case EFI_PM_PWRON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_HARD_RESET:
    ponResetCfg = PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_HARD_RESET;
    break;
  case EFI_PM_PWRON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_HARD_RESET:
    ponResetCfg = PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_HARD_RESET;
    break;
  default:
    return EFI_INVALID_PARAMETER;
  }

  errFlag = pm_pon_reset_source_cfg(PmicDeviceIndex,
                                    (pm_pon_reset_source_type)ResetSource,
                                    s1TimerMs,
                                    s2TimerMs,
                                    ponResetCfg);
  Status = (PM_ERR_FLAG_SUCCESS == errFlag)? EFI_SUCCESS : EFI_DEVICE_ERROR;
  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicPonEnableResetSource
(
IN UINT32                       PmicDeviceIndex,
IN EFI_PM_PON_RESET_SOURCE_TYPE ResetSource,
IN BOOLEAN                      enable
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  EFI_STATUS Status = EFI_SUCCESS;
  errFlag = pm_pon_reset_source_ctl(PmicDeviceIndex, (pm_pon_reset_source_type)ResetSource, enable);
  Status = (PM_ERR_FLAG_SUCCESS == errFlag)? EFI_SUCCESS : EFI_DEVICE_ERROR;
  return Status;
}
#include "pm_version.h"

EFI_STATUS
EFIAPI
EFI_PmicPonGetDecideResetDisable
(
IN UINT32   PmicDeviceIndex,
OUT BOOLEAN *enable
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  EFI_STATUS Status = EFI_DEVICE_ERROR;
  pm_pon_reason_type PonReason = {0};
  pm_pon_poff_reason_type PoffReason = {0};
  pm_pon_warm_reset_reason_type WarmResetReason = {0};
  boolean int_rt_sts_resin = FALSE;
  boolean ini_rt_sts_pwr   = FALSE;

  errFlag |= pm_pon_get_pon_reason(PmicDeviceIndex, &PonReason);
  errFlag |= pm_pon_get_warm_reset_reason(PmicDeviceIndex, &WarmResetReason);
  errFlag |= pm_pon_get_poff_reason(PmicDeviceIndex, &PoffReason);
  errFlag |= pm_pon_irq_status(PmicDeviceIndex, PM_PON_IRQ_RESIN_N_DEB, PM_IRQ_STATUS_RT, &int_rt_sts_resin);
  errFlag |= pm_pon_irq_status(PmicDeviceIndex, PM_PON_IRQ_KPD_PWR_N_DEB, PM_IRQ_STATUS_RT, &ini_rt_sts_pwr);

  if (PM_ERR_FLAG_SUCCESS == errFlag)
  {
    Status = EFI_SUCCESS;
    *enable = ((PoffReason.kpdpwr_and_resin == 1) && (PonReason.hard_reset == 1 )) || // PKDPWR and RESIN + HwReset
              (WarmResetReason.kpdpwr_and_resin == 1) || // PKDPWR and RESIN
              ((int_rt_sts_resin == TRUE) && (ini_rt_sts_pwr == TRUE)); // RESIN_ON and KPDPWR_ON bit on PON_INT_RT_STS
  }
  return Status;
}
#endif /* FEATURE_XBOOT */

/**
  PMIC PWRON UEFI Protocol implementation
 */
EFI_QCOM_PMIC_PWRON_PROTOCOL PmicPwronProtocolImplementation = 
{
  PMIC_PWRON_REVISION,
  EFI_PmicPwronGetPonPblStatus,
  EFI_PmicPwronSetPonTrigger,
  EFI_PmicPwronGetPonRtStatus,
  EFI_PmicPonGetSpareReg,
  EFI_PmicPonSetSpareReg,
  EFI_PmicPonGetPonReason,
  EFI_PmicPonWarmResetStatus,
  EFI_PmicPonGetAllPonReasons,
  EFI_PmicPwronEnableEdgePonTrigger,
  EFI_PmicPwronIrqEnable,
  EFI_PmicPwronIrqClear,
  EFI_PmicPwronIrqSetTrigger,
  EFI_PmicPwronGetPonIrqStatus,
  EFI_PmicPonGetAllFaultReasons,
#ifdef FEATURE_XBOOT
  EFI_PmicPonResetSourceCfg,
  EFI_PmicPonEnableResetSource,
  EFI_PmicPonGetDecideResetDisable,
#endif /* FEATURE_XBOOT */
};

EFI_QCOM_PMIC_PON_PROTOCOL PmicPonProtocolImplementation = 
{
  PMIC_PON_REVISION,
  EFI_PmicPonGetSpareReg,
  EFI_PmicPonSetSpareReg,
  EFI_PmicPonGetPonReason,
  EFI_PmicPonWarmResetStatus,
};
