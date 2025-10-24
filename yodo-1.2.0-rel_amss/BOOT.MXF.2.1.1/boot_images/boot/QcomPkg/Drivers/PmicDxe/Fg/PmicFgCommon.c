/*! @file PmicFgCommon.c
 *
 *  PMIC-FG MODULE RELATED DECLARATION
 *  This file contains functions and variable declarations to support
 *  the PMIC FG commone file.
 *
 *  Copyright (c) 2016 - 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
 *  Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who    what, where, why
--------   ---    ---------------------------------------------------------- 
09/09/21   sch    use bmd peripheral to detect battery presence
08/01/18   ivy    Set batt them pull up and HW Jeita/AFP after battery profile is read
07/24/18   ivy	  Set rslow age register
06/13/18   cs	  remove rr-adc temp reading.
05/17/18   ivy	  Set Rslow shape and SoC reduction parameters, and support PM8150B v2.0 register map
03/21/18   cs     integrity bit and Rconn workaround.
03/15/18   ra     Read battery temp from ADC
02/22/18   cs     modify profile parser, set batt therm coefficient even when not load profile. 
03/01/18   ra     Remove obsolete code
01/29/18   cs     modified APIs to get batt id and batt temp.
11/27/17   ra     Removing unsupported API's
11/09/17   ra     Remove unsupported protocols
09/19/17   cs     for SDM855 remvoe unsupported function calls.
06/09/17   va     Detect the bad conditions of FG SRAM (trim registers) and issue VDD hard reset on PM/PMi to recover
06/07/17   cs     add configurable delay before enabling BMD
03/30/17   ll     Implemented level file-logging
03/15/17   cs     fix SBL 160 ms extra delay due to getting fresh batt id issue
01/27/17   ai     Fix use of retail
01/23/17   sm      CFG parameter Structure changes
12/19/16   sm     Added API to get FG PmicIndex
11/10/16   va     Removing SOC EMPTY IRQ
11/07/16   cs     Added API to disable ESR Pulse
10/14/16   va     update Aux setting 
10/11/16   va     Read profile on every boot, compare profile data vs sram data
10/06/16   cs     configuring batt therm/aux therm
09/20/16   sv     fixing klocwork issues
09/20/16   va     Enable Restarting FG 
07/26/16   va     Restarting FG Changes on warm boot 
06/23/16   va     Adding support for Charger Fg Peripheral dumps
06/14/16   va     Updating calculations for jeita thresholds, Reading IBat, Vbat from batt info
05/26/16   va     Update for Profile Load
05/24/16   sm     Added API calls to Enable FG Algorithm, BCL and GOC 
04/26/16   va     Adding parameters for Aux Coffes, SkinHot and Charger Hot settings
03/28/16   va     Consolidating config data into one struct 
03/21/16   va     New File.

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
/**
  EFI interfaces
 */
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EFIPmicFg.h>
#include <Protocol/EFIPmicPwrOn.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIChipInfo.h>
#include <Library/QcomTargetLib.h>
#include <Library/FuseControlLib.h>

#include "DDIPlatformInfo.h"

/**
SPMI depedency
*/
#include "SpmiBus.h"

/**
  PMIC Lib interfaces
 */
#include "pm_uefi.h"
#include "PmicFileLog.h"
#include "PmicFgCommon.h"
#include "pm_version.h"
#include <../../Library/PmicLib/utils/inc/pm_utils.h>
#include "pm_err_flags.h"
#include "pm_core_utils.h"
#include "pm_qbg.h"
#include "pm_bmd.h"
#include "pm_chg.h"
#include <Protocol/EFIPmicPwrOn.h>


/**
QCom Lib dependency
*/
//#include <Library/QcomLib.h>
//#include <Library/MemoryAllocationLib.h>
#include "string.h"
#include <Library/BaseMemoryLib.h>

/**
  ADC Dependencies
 */
#include <Protocol/EFIAdc.h>

/**
  SChg interface
 */
#include "EFIPmicSchg.h"



/*===========================================================================

                        MACRO DEFINITIONS

===========================================================================*/
#define AZURA_PMIC_INDEX         0
#define TIOMAN_PMIC_INDEX        8

/*===========================================================================

                        GLOBAL DATA DEFINITIONS

===========================================================================*/
EFI_PM_FG_CFGDATA_TYPE      gFgConfigData = {0};
extern EFI_GUID gQcomPmicPwrOnProtocolGuid;

/*===========================================================================

                        LOCAL FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================

                        EXTERNAL FUNCTION DEFINITIONS

===========================================================================*/

/**
EFI_PmicFgExit()

@brief
Exit Fule Gauge Module
*/
EFI_STATUS
EFIAPI
EFI_PmicFgBasicExit
(
  UINT32 PmicDeviceIndex
)
{
  return EFI_SUCCESS;
}

/**
EFI_PmicFgExtendedExit()

@brief
Extended Exit for Fule Gauge Module
*/
EFI_STATUS
EFIAPI
EFI_PmicFgExtendedExit
(
  UINT32 PmicDeviceIndex
)
{
  return EFI_SUCCESS;
}

/**
EFI_PmicFgInit()

@brief
Initializes Fule Gauge Module
*/
EFI_STATUS
EFIAPI
EFI_PmicFgBasicInit
(
  UINT32                      PmicDeviceIndex,
  EFI_PM_FG_CFGDATA_TYPE     *pFgCfgData
)
{
  return EFI_SUCCESS;
}


/**
EFI_PmicFgExtendedInit()

@brief
Initializes Fule Gauge Module with battery profile if profile loading is enabled
*/
EFI_STATUS
EFIAPI
EFI_PmicFgExtendedInit
(
  IN UINT32                        PmicDeviceIndex,
  OPTIONAL EFI_PM_FG_BATT_PROFILE_DATA  *pBattProfileData
)
{
  return EFI_SUCCESS;
}

/**
EFI_PmicFgBatteryStatus()

@brief
Returns Battery Status parameters such as State of Charge (SOC)
*/
EFI_STATUS
EFIAPI
EFI_GetBatteryStatus
(
   IN  UINT32         PmicDeviceIndex,
   OUT EFI_PM_FG_BATT_STATUS_INFO *BattStsInfo
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

  errFlag |= pm_chg_get_battery_ocv((uint32*)&(BattStsInfo->Ocv));//mV
  DEBUG(( EFI_D_INFO, "EFI_GetBatteryStatus: pon_ocv=%d mV \r\n", BattStsInfo->Ocv));

  return Status;
}


/**
EFI_GetBattProfileStatus()

@brief
Returns Battery profile Status parameters such as profile load status
*/
EFI_STATUS
EFIAPI
EFI_GetBattProfileStatus
(
   IN  UINT32         PmicDeviceIndex,
   OUT EFI_PM_FG_BATT_PROFILE_STATUS *pBattProfileStatus
)
{
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmicFgGetBatteryId
(
  OUT EFI_PM_BATTERY_ID* BatteryId
)
{
  return EFI_SUCCESS;
}


/**
EFI_PmicFgDumpPeripheral()

@brief
 Dump FG Pheripheral
 */
EFI_STATUS
EFIAPI
EFI_PmicFgDumpPeripheral( VOID )
{
  return EFI_SUCCESS;
}

/**
EFI_PmicFgDumpFgSram()

@brief
 Dump FG SRAM
*/
EFI_STATUS
EFIAPI
EFI_PmicFgDumpFgSram( IN UINT32 PmicDeviceIndex)
{
  return EFI_SUCCESS;
}




EFI_STATUS
EFIAPI
EFI_PmicFgConfigureHwJeita( UINT32 PmicDeviceIndex )
{
  /* Functionality not supported in FG module on PM855B, moved to CHGR peripheral */
  EFI_STATUS Status = EFI_UNSUPPORTED;

  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicFgGetHWJeitaStatus( UINT32 PmicDeviceIndex, EFI_PM_FG_BATT_TEMP_STATUS *pHwJeitaStatus)
{
  /* Functionality not supported in FG module on PM855B, moved to CHGR peripheral */
	EFI_STATUS Status = EFI_UNSUPPORTED;

  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicFgEnableESRPulse(UINT32 PmicDeviceIndex, BOOLEAN enable)
{
  return EFI_SUCCESS;
}

/**
EFI_PmicFgBasicGetPmicInfo()

@brief
Provides PMIC Index on which FG resides
*/
EFI_STATUS
EFIAPI
EFI_PmicFgBasicGetPmicInfo
(
    OUT EFI_PM_FG_PMIC_INFO *FgPmicInfo
)
{
  if(FgPmicInfo == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  FgPmicInfo->PmicIndex = 7;
  FgPmicInfo->SlaveIndex = 7;
  return EFI_SUCCESS;
}

/**
EFI_PmicFgBasicIsBatteryPresent()

@brief
Provides if battery is missing
*/
EFI_STATUS
EFIAPI
EFI_PmicFgBasicIsBatteryPresent
( 
  IN UINT32 PmicDeviceIndex, 
  OUT BOOLEAN *isBatteryPresent
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  BOOLEAN batt_miss = 0;

  if(NULL == isBatteryPresent)
  {
    return EFI_INVALID_PARAMETER;
  }
  
  errFlag = pm_bmd_get_battery_missing_rt_status(PmicDeviceIndex, PM_BMD_BAT_MISS_STS_RAW, &batt_miss); 
  *isBatteryPresent = (!batt_miss);
  Status = (errFlag == PM_ERR_FLAG_SUCCESS) ? EFI_SUCCESS: EFI_DEVICE_ERROR;
  return Status;
}

EFI_STATUS
EFIAPI
EFI_GetBatteryType
(
  IN UINT32 PmicDeviceIndex,
  OUT EFI_PM_FG_BATT_TYPE* battery_type
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  pm_chg_battery_type pm_batt_type = PM_CHG_BATT_TYPE_INVALID;
  if(NULL == battery_type)
  {
    return EFI_INVALID_PARAMETER;
  }

  errFlag = pm_qbg_get_qbg_mode_ctl1_batt_opt(PmicDeviceIndex, &pm_batt_type);
  Status = (errFlag == PM_ERR_FLAG_SUCCESS) ? EFI_SUCCESS: EFI_DEVICE_ERROR;
  if(Status == EFI_SUCCESS)
  {
    if(pm_batt_type == PM_CHG_2S_BATT_TYPE)
    {
        *battery_type = BATTERY_2S;
    }
    else if (pm_batt_type == PM_CHG_1S_BATT_TYPE)
    {
        *battery_type = BATTERY_1S;
    }
    else if (pm_batt_type == PM_CHG_2P_BATT_TYPE)
    {
        *battery_type = BATTERY_2P;
    }
    else
    {
        *battery_type = BATTERY_1S;
    }
  }
  
  return Status;
}

/**
 * EFI_PmicFgGetPmicGaugeSDAMInfo()
 * @brief
 * Provides SDAM information of Gauge.
 * */
EFI_STATUS
EFIAPI
EFI_PmicFgGetPmicGaugeSDAMInfo
(
 OUT UINT32 *SdamPmicIndex,
 OUT UINT32 *SdamIndex
)
{
    uint32 pmic_index = 0;
    pm_chg_get_primary_charger_pmic_index(&pmic_index);
    //temp change for NHLOS reference.
    if(NULL == SdamPmicIndex || NULL == SdamIndex)
    {
        return EFI_INVALID_PARAMETER;
    }
    if(pmic_index == PMIC_H)
    {
        *SdamPmicIndex = AZURA_PMIC_INDEX;
        *SdamIndex = PM_SDAM_24;
        return EFI_SUCCESS;
    }
    else if(pmic_index == PMIC_I)
    {
        *SdamPmicIndex = TIOMAN_PMIC_INDEX;
        *SdamIndex = PM_SDAM_2;
        return EFI_SUCCESS;
    }
    return EFI_DEVICE_ERROR;
}
