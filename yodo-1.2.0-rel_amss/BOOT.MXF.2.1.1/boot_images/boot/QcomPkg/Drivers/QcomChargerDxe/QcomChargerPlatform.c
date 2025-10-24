/** @file ChargerPlatform.c

  Implements Qualcomm's battery voltage based threshold Charging solution

  Copyright (c) 2017-2022,  Qualcomm Technologies Inc. All rights reserved.

**/

/*=====================================================================================
                              EDIT HISTORY


 when         who     what, where, why
 --------     ---     -----------------------------------------------------------------
 01/11/22     sch     Added check for supported charger while working for NO PMI support
 05/14/19     sg      Add config item to choose pull-up for BATT_ID detection
 31/01/19     pbitra  Fixed DieTemp threshold reading
 01/10/19     vr      Added support for wireless charging
 01/10/19     vr      Fix issue where charging is disabled in unknown battery cases
 06/29/18     dc      Support Input Current Status API & Log
 05/14/18     ra      Support for Debug Accessory Mode
 03/15/18     ra      Change to read Jeita enable parameters correctly
 02/22/18     cs      set batt therm coefficient even when not load profile.
 03/01/18     ra      Adding config items to SCHG
 02/09/18     ra      Removing Wipower related code
 11/27/17     ra      Battery Missing config chanegs for SDM855
 11/09/17     ra      Jeita code changes for Pm855B
 07/12/17     cs      remove redundent enum definition for platform charger Action
 06/21/17     dc      Move Platform Check to QcomChargerDxe and support config override
 06/07/17     cs      add configurable delay before enabling BMD
 05/16/17     cs      fixed in no charging wait state, battery status is printing all 0s
 04/24/17     va      Enable Charger App Changes
 03/30/17     ll      Implemented level file-logging
 03/27/17     pbitra  Updated to support section based config for different platforms.
 03/07/17     cs      remove duplicate get errors checking emergency shutdown condition.
 03/09/17     ll      Updated code based on latest smem_mem_type
 02/07/17     sm      add config to enable/disable INOV
 01/31/17     va      Adding Rconn configuration for considering compensation
 01/27/17     sm      Added support for pbs triggered AFP
 01/23/17     sm      CFG parameter Structure changes
 11/10/16     va      Adding Config VBtEmpty threshold, soc update for smem info
 11/09/16     sm      Added changes to disable watchdog before applying the config setting.
 10/19/16     sm      Removed EnableHvdcp cfg param from ChargerPlatform_ReadCfgParams()
 10/17/16     sm      Added SetChargeCmdBit() API call once CHARGERLIB_CHG_WDOG_STS_BITE_CHARGING_DISABLED is detected.
 10/14/16     va      adding aux coffs settings
 10/06/16     cs      configure batt therm/aux therm bias wait
 09/29/16     va      Emergency shutdown behavior changes and debug log update
 09/13/16     sm      removed unused parameters from ChargerPlatform_ReadCfgParams()
 09/06/16     cs      wipower changes to remove 3.5 sec, not suspend DCIn
 08/24/16     sm      Added changes for supporting different config parameters settings for
                      different platforms, MTP, QRD, etc.
 08/12/16     sm      Merged Vbatt and SOC based Platform files.
 08/05/16     va      Adding Charger led indication support
 07/26/16     va      Restarting FG Changes on warm boot
 07/15/16     cs      Adding Wipower support
 06/28/16     va      Changes to share charger info to smem
 06/24/16     sm      Added check for charging enabled in GetChargingAction()
 06/23/16     sm      Added EnableHvdcp in ChargerPlatform_ReadCfgParams()
 06/23/16     va      Adding support for Charger Fg Peripheral dumps
 06/14/16     va      Adding Thermal Support
 06/09/16     sm      Added SupportHostMode in ChargerPlatform_ReadCfgParams()
 05/31/16     va      Adding Battery profile load feature
 05/24/16     sm      Added changes to handle No_Charger_wait case in GetChargingAction()
 05/10/16     sm      Added ChargerPlatform_GetConfigData()
 04/26/16     va      Adding parameters for Aux Coffes, SkinHot and Charger Hot settings
 04/21/16     sm      Added API call for Watchdog
                      Added EnableChargerWdog in ChargerPlatform_ReadCfgParams
 04/12/16     sm      Edited variables in ChargerPlatform_ReadCfgParams()
 04/07/16     sm      Added ChargerPlatform_GetUefiVariableValues()
 03/31/16     sm      Completing API definitions
 03/28/16     va      Add logging CHARGER_DEBUG
 03/21/16     va      Remove dummy configs and add battery missing config
 01/27/16     sm      Initial revision

=============================================================================*/
#include <Uefi.h>

/**
  EFI interfaces
 */
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomUtilsLib.h>
#include <api/pmic/pm/pm_uefi.h>
#include <Library/FuseControlLib.h>
#include <Library/QcomBaseLib.h>

#include <Library/MemoryAllocationLib.h>

#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>

#include <Protocol/EFIChargerEx.h>
#include <Protocol/EFIPmicGlink.h>
#include <Protocol/EFIPIL.h>
#include <Library/SerialPortShLib.h>

/**
  EFI interfaces
 */
#include <Protocol/GraphicsOutput.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIUsbPwrCtrl.h>
#include <Protocol/EFIVariableServices.h>
#include <Protocol/EFIPmicSchg.h>
#include <Protocol/EFIPmicVersion.h>
#include <Protocol/EFIAdc.h>

#include "QcomChargerPlatform.h"
#include "QcomChargerPlatform_File.h"

#include <api/pmic/pm/pm_chg.h>

/**
Smem Interface
*/
#include "smem.h"

/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES                                     */
/*===========================================================================*/
#define QCOM_CHARGER_IDLE_WAIT_DURATION            3000 /*3 sec in milliseconds*/
#define QCOM_CHARGER_MS_TO_S                       1000

/* UI would be displayed if VBAT read is less than 3700mV is 7% Soc.
   Having a margin of extra 50mV to consider on the top of error margin */
#define QCOM_CHARGER_VBAT_ERROR_MARGIN 0 /*in Mv as of now keeping default as 0 error margin */
#define QCOM_CHARGER_LOW_THERSHOLD_VBAT 3700 /*in Mv*/
#define QCOM_CHARGER_INVALID_VALUE_MARKER  -1
#define CHARGER_FW_MODE 1
#define CHARGER_FW_MISSING 2
#define QCOM_CHARGER_VBAT_THRESHOLD_MARGIN 20 /*in mV*/
#define QCOM_CHARGER_SOC_THRESHOLD_MARGIN 1
#define LoggingCategoriesMax 0x1FFFFFFFFF  //Modify this value everytime we add a new category on chargerfw side, we write this to sdam before boot to HLOS

STATIC UINT32 gThresholdVbatt = 0;
STATIC UINT32 gThresholdSoc   = 0;
BOOLEAN gEnableChargerFW = FALSE;

QCOM_CHARGER_PLATFORM_CFGDATA_TYPE gChargerPlatformCfgData;

extern BOOLEAN ExitChargingLoop;
BOOLEAN gChargingInitialized = FALSE;

pm_chg_info_type gChargerSharedInfo;

STATIC EFI_PLATFORMINFO_PLATFORM_TYPE PlatformType;
STATIC BOOLEAN gChargerCfgInitialized = FALSE;

STATIC EFI_EVENT ReadChargerpdEvt = NULL;
BOOLEAN gIs_2S_Battery = FALSE;
STATIC UINT64 LoggingCategories;

#ifdef FEATURE_XBOOT
#define BOOT_TO_HLOS_TH_WITHOUT_CHGR        3500
#endif /* FEATURE_XBOOT */

EFI_STATUS ChargerPlatform_GetUefiVariableValues( void );
EFI_STATUS ChargerPlatform_SaveChargeInfoToSmem(pm_chg_info_type *ChargerActionInfo);
EFI_STATUS ChargerPlatform_ProfileLoadingInit(EFI_QCOM_CHARGER_ACTION_TYPE *pActionType, QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo, CHARGERLIB_CHARGING_ERROR_TYPES errType);
EFI_STATUS ChargerPlatform_CheckIfOkToBoot(EFI_QCOM_CHARGER_ACTION_TYPE *pActionType, QCOM_CHARGER_PLATFORM_ACTION_INFO ChargerActionInfo, QCOM_CHARGER_BATT_STATUS_INFO             CurrentBatteryStatus);
EFI_STATUS ChargerPlatform_HandleShipMode(void);
EFI_STATUS ChargerPlatform_LinkChargerFW(void);
EFI_STATUS ChargerPlatform_LoadChargerFW(void);
EFI_STATUS ChargerPlatform_ChkChgFwLoadRequired(EFI_QCOM_CHARGER_ACTION_TYPE *pActionType);
EFI_STATUS ChargerPlatform_HandleRecovery();
STATIC EFI_STATUS IsChargingSupported(void);

/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES                                     */
/*===========================================================================*/
/*
ChargerPlatform_Init(): This function locates and initializes ADC Protocal, Charger Protocal and other Protocols that are
needed for that specific platform. It also loads the cfg file and initialize charger and FG accordingly.
*/
EFI_STATUS ChargerPlatform_Init( VOID )
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_FG_BATT_TYPE cell_type = BATTERY_1S;

  Status = IsChargingSupported();
  if(EFI_SUCCESS != Status)
  {
	return Status;
  }

  SetMem(&gChargerPlatformCfgData, sizeof(QCOM_CHARGER_PLATFORM_CFGDATA_TYPE), 0x00);
  SetMem(&gChargerSharedInfo, sizeof(pm_chg_info_type), 0xFF);

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "QcomChargerPlatform:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  //Initialize Charger and Gauge HW Type to be invalid before reading Cfg Data
  gChargerPlatformCfgData.ChargerLibCfgData.plat_hw_cfg_override = CHARGERLIB_PLATFORM_HW_CONFIG_INVALID;
  // check if it is 1S or 2S
  Status = ChargerLib_GetBatteryCellType(&cell_type);
  if(EFI_SUCCESS == Status && cell_type == BATTERY_2S)
  {
    gIs_2S_Battery = TRUE;
  }
  /* Load CFG file */
  Status |= ChargerPlatformFile_ReadDefaultCfgData();
  if(EFI_SUCCESS == Status)
  {
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Successfully read config file\n\r", __FUNCTION__));
    gChargerCfgInitialized = TRUE;
  }

  /* Read debug var from pmic bds menu */
  Status  |= ChargerPlatform_GetUefiVariableValues();

  if ((EFI_SUCCESS == Status) && (TRUE == gChargerPlatformCfgData.ChargerLibCfgData.dbg_cfg_Data.print_charger_app_dbg_msg_to_file))
  {
    Status = ChargerPlatformFile_FileLogInit(gChargerPlatformCfgData);
  }

  CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a chargerlib_cfgdata_type = %d QCOM_CHARGER_PLATFORM_CFGDATA_TYPE = %d \r\n", __FUNCTION__, sizeof(chargerlib_cfgdata_type), sizeof(QCOM_CHARGER_PLATFORM_CFGDATA_TYPE) ));

  /* Init Charger lib */
  Status |= ChargerLibCommon_Init((chargerlib_cfgdata_type*)&gChargerPlatformCfgData.ChargerLibCfgData);
  if (EFI_UNSUPPORTED == Status)
  {
      CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Error: Charging is not supported for this platform. \r\n", __FUNCTION__));
      return EFI_SUCCESS;
  }
  else if(EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Error when initializing ChargerLibCommon = %r \r\n", __FUNCTION__, Status));
    return Status;
  }
  else
  {
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Successfully initialized ChargerLibCommon %r \r\n", __FUNCTION__, Status));
  }

  if ((EFI_SUCCESS == Status) && (TRUE == gChargerPlatformCfgData.ChargerLibCfgData.shipmode_cfg.enable_shipmode))
  {
    Status = ChargerPlatform_HandleShipMode();
  }

  gThresholdVbatt = gChargerPlatformCfgData.ChargerLibCfgData.boot_to_hlos_threshold_in_mv;
  gThresholdSoc   = gChargerPlatformCfgData.ChargerLibCfgData.boot_to_hlos_threshold_in_soc;

#ifdef FEATURE_XBOOT
  /* Disable HW JEITA*/
  Status |= ChargerLib_EnableHWJeita(FALSE);
#else /* !FEATURE_XBOOT */
  /* Enable HW JEITA*/
  Status |= ChargerLib_EnableHWJeita(TRUE);
#endif /* !FEATURE_XBOOT */

  /*Disable Charger wdog before applying config based wdog setting*/
  Status = ChargerLib_EnableWdog(FALSE);

  if((QCOM_CHG_WDOG_DISABLE_ON_EXIT == gChargerPlatformCfgData.ChargerLibCfgData.enable_charger_wdog)|| (QCOM_CHG_WDOG_LEAVE_ENABLED_ON_EXIT == gChargerPlatformCfgData.ChargerLibCfgData.enable_charger_wdog))
  {
    /* Enable Charger Watchdog*/
    Status = ChargerLib_EnableWdog(TRUE);
    if(EFI_SUCCESS == Status)
    {
      CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Enabled WDOG.\r\n", __FUNCTION__));
    }
    else if (EFI_UNSUPPORTED == Status)
    {
      /*Do not need to return status as unsupported. Debug statement will be printed from SCG protocol API*/
      Status = EFI_SUCCESS;
    }
  }

  return Status;
}

BOOLEAN ChargerPlatform_IsBelowThreshold(UINT32 threshold, UINT32 value, UINT32 hysterysis)
{
  if(value < (threshold + hysterysis)) { return TRUE; }
  return FALSE;
}

EFI_STATUS ChargerPlatform_ChkChgFwLoadRequired(EFI_QCOM_CHARGER_ACTION_TYPE *pActionType)
{
  EFI_STATUS                    Status            = EFI_SUCCESS;
  CHARGERLIB_PLATFORM_PWRON_REASON_TYPE PonReasonType = { 0 };
  BOOLEAN                       IsChargingSupported = FALSE;
  chargerlib_batt_status_info   BattStatus = { 0 };
  CHARGERLIB_ATTACHED_CHGR_TYPE     AttachedCharger = CHARGERLIB_ATTACHED_CHGR__NONE;
  BOOLEAN is_below_threshold = FALSE;
  ChgBattType batt_type = CHG_BATT_TYPE_INVALID;

  if(!pActionType)
    return EFI_INVALID_PARAMETER;
  /* Load ADSP on USB PON for off mode charging and threshold charging - VPH is lower than 3.6V
  */
  Status = ChargerLib_IsChargingSupported(&IsChargingSupported);
  if (Status != EFI_SUCCESS)
  {
    CHARGER_DEBUG((EFI_D_ERROR, "QcomChargerPlatform:: %a Error getting is charging supported = %r \r\n", __FUNCTION__, Status));
    return Status;
  }
  
  Status = ChargerLib_GetPlatformPwrOnReason(&PonReasonType);
  if (Status != EFI_SUCCESS)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerPlatform:: %a Error getting PON reason = %r \r\n", __FUNCTION__, Status));
    return Status;
  }

  CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerPlatform:: %a PonReasonType.KPDPWR = %d,  PonReasonType.HARD_RESET = %d, PonReasonType.CBLPWR = %d, PonReasonType.USB_CHG = %d, PonReasonType.DC_CHG = %d\r\n", 
        __FUNCTION__, PonReasonType.KPDPWR, PonReasonType.HARD_RESET, PonReasonType.CBLPWR, PonReasonType.USB_CHG, PonReasonType.DC_CHG));

  Status = ChargerLib_GetBatteryStatus(&BattStatus);
  if (Status != EFI_SUCCESS)
  {
    CHARGER_DEBUG((EFI_D_ERROR, "QcomChargerPlatform:: %a Error getting battery status = %r \r\n", __FUNCTION__, Status));
    return Status;
  }
  /* Charge Source Detection */
  Status = ChargerLib_GetChargingPath(&AttachedCharger);
  if(gChargerPlatformCfgData.ChargerLibCfgData.soc_based_boot)
  {
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a soc = %d , gThresholdSoc = %d  \r\n", __FUNCTION__, BattStatus.StateOfCharge, gThresholdSoc));
    is_below_threshold = ChargerPlatform_IsBelowThreshold(gThresholdSoc, BattStatus.StateOfCharge, 0);
  }
  else
  {
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a VBatt = %d mV, Ocv = %d mV, dgThresholdVbatt = %d V \r\n", __FUNCTION__, BattStatus.BatteryVoltage, BattStatus.Ocv, gThresholdVbatt));
#ifdef FEATURE_XBOOT
    is_below_threshold = ChargerPlatform_IsBelowThreshold(BOOT_TO_HLOS_TH_WITHOUT_CHGR, BattStatus.Ocv, 0);
#else /* !FEATURE_XBOOT */
    is_below_threshold = ChargerPlatform_IsBelowThreshold(gThresholdVbatt, BattStatus.Ocv, 0);
#endif /* !FEATURE_XBOOT */
  }
  
  if(is_below_threshold)
  {
    /* User can plug in USB later in boot so we need to check USB plug in here*/

    Status = ChargerLib_GetBatteryType(&batt_type);
    if(batt_type == CHG_BATT_TYPE_DEBUG_BOARD)
    {
     *pActionType = EFI_QCOM_CHARGER_ACTION_GOOD_TO_BOOT;
      CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Fake battery detected, boot to HLOS \r\n", __FUNCTION__));
      return Status;
    }

    if ((CHARGERLIB_ATTACHED_CHGR__BATT == AttachedCharger) || (CHARGERLIB_ATTACHED_CHGR__NONE == AttachedCharger))
    {
          *pActionType = EFI_QCOM_CHARGER_ACTION_SHUTDOWN;
          CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a USB not present shutdown as low voltage \r\n", __FUNCTION__));
    }
    else if (IsChargingSupported)
    {
        if (gEnableChargerFW || gThresholdSoc)
        {
          /* Load Chg FW if ChargerFW flag is set or use soc threshold.*/
            *pActionType = EFI_QCOM_CHARGER_ACTION_LOAD_CHARGER_FW;
             CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Load Chg Fw \r\n", __FUNCTION__));
      
             return Status;
        }
        /* If ChargerFW flag is not set, go to recovery mode */
        *pActionType = EFI_QCOM_CHARGER_ACTION_RECOVERY;
        CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Chg FW recover state \r\n", __FUNCTION__));
      }
    else
    {
      /* code */
      *pActionType = EFI_QCOM_CHARGER_ACTION_GOOD_TO_BOOT;
    }        
      return Status;

  }
  else
  {
    *pActionType = EFI_QCOM_CHARGER_ACTION_GOOD_TO_BOOT;
    CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Chg Fw Load not required boot to HLOS \r\n", __FUNCTION__));
  }

  return Status;

}


#define QCOM_CHARGER_CHG_FW_HEARTBEAT_CNT_MAX 3

EFI_STATUS ChargerPlatform_GetChargingAction(EFI_QCOM_CHARGER_ACTION_TYPE *pActionType, QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo, BOOLEAN vbattChecking)
{
  EFI_STATUS Status                = EFI_SUCCESS;
  BOOLEAN    bChargerReinserted    = FALSE, DAMConnectSts = FALSE;
  CHARGERLIB_CHARGING_ERROR_TYPES           ErrorType  = CHARGERLIB_CHARGING_ERROR_NONE;
  STATIC EFI_QCOM_CHARGER_ACTION_TYPE  PrevChargerAction = EFI_QCOM_CHARGER_ACTION_INVALID;
  BOOLEAN                                   ChargingEnabled    = FALSE;

  if (!pChargerActionInfo || !pActionType)
    return EFI_INVALID_PARAMETER;

  if(!(PlatformType == EFI_PLATFORMINFO_TYPE_MTP || PlatformType == EFI_PLATFORMINFO_TYPE_ATP || PlatformType == EFI_PLATFORMINFO_TYPE_QRD || EFI_PLATFORMINFO_TYPE_IDP == PlatformType)||
     gChargerPlatformCfgData.ChargerLibCfgData.dbg_cfg_Data.DISABLEBATTERY) 
  {
    /* For MTP/CDP or if DISABLEBATTERY flag is set, should not load ADSP for any PON reason, just boot to HLOS directly */
    PrevChargerAction = *pActionType = EFI_QCOM_CHARGER_ACTION_GOOD_TO_BOOT;
    return Status;
  }

  /* Check if factory cable is connected */
  if (gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.EnDebugAccessMode)
  {
      Status |= ChargerLib_GetDAMConnectStatus(&DAMConnectSts);
      if (EFI_SUCCESS != Status)
      {
          CHARGER_DEBUG((EFI_D_ERROR, "QcomChargerDxe:: %a Error Getting Debug Accessory Mode Status = %r.\r\n", __FUNCTION__, Status));
      }
      if (DAMConnectSts)
      {
          *pActionType = EFI_QCOM_CHARGER_ACTION_FACTORY_MODE_BOOT_TO_HLOS;
          PrevChargerAction = *pActionType;
          CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: EFI_QCOM_CHARGER_ACTION_FACTORY_MODE_BOOT_TO_HLOS \r\n"));
          return Status;
      }
  }
  
  if (PrevChargerAction == EFI_QCOM_CHARGER_ACTION_INVALID)
  {
    /* ADSP load required ? */
    Status = ChargerPlatform_ChkChgFwLoadRequired(pActionType);
    if(Status != EFI_SUCCESS )
    {
      CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Error = %r.\r\n", __FUNCTION__, Status));
      *pActionType = EFI_QCOM_CHARGER_ACTION_SHUTDOWN;
    }
    
    Status |= ChargerLib_GetErrors(vbattChecking, &ErrorType);
    if(Status != EFI_SUCCESS )
    {
        CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Error Getting Battery Error = %r.\r\n", __FUNCTION__, Status));
        *pActionType = EFI_QCOM_CHARGER_ACTION_SHUTDOWN;
    }

    /* Check for temperature as we can boot to HLOS directly at high temperatures, provided Vbatt is high */
    if (ErrorType == CHARGERLIB_CHARGING_ERROR_BATT_TEMP_OUTSIDE_OPERATIONAL_RANGE)
    {
        *pActionType = EFI_QCOM_CHARGER_ACTION_CRITICAL;
    }

    PrevChargerAction = *pActionType;
    return Status;
  }
  else if ((EFI_PLATFORMINFO_TYPE_CLS == PlatformType || EFI_PLATFORMINFO_TYPE_MTP == PlatformType || EFI_PLATFORMINFO_TYPE_ATP == PlatformType || EFI_PLATFORMINFO_TYPE_QRD == PlatformType ||  EFI_PLATFORMINFO_TYPE_IDP == PlatformType) && (PrevChargerAction == EFI_QCOM_CHARGER_ACTION_RECOVERY))
  {
    *pActionType = EFI_QCOM_CHARGER_ACTION_RECOVERY;
    PrevChargerAction = *pActionType;
    CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Chg FW recover state \r\n", __FUNCTION__));
  }
  else if ((gChargerSharedInfo.uefi_charger_fw_mode == CHARGER_FW_MISSING) && (PrevChargerAction != EFI_QCOM_CHARGER_ACTION_RECOVERY))
  {
    *pActionType = EFI_QCOM_CHARGER_ACTION_RECOVERY;
    PrevChargerAction = *pActionType;
    CHARGER_DEBUG((EFI_D_ERROR, "QcomChargerDxe:: %a Chg FW recover state \r\n", __FUNCTION__));
    AsciiErrorPrint("Charger FW Loading Failed!\n");
    return Status;
  }

  /* Get Error like debug board or battery not detected first */
  Status |= ChargerLib_GetErrors(vbattChecking, &ErrorType);
  if(EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Error Getting Battery Error = %r.\r\n", __FUNCTION__, Status));
    *pActionType = EFI_QCOM_CHARGER_ACTION_SHUTDOWN;
    PrevChargerAction = *pActionType;
    return Status;
  }
  
  if((ErrorType == CHARGERLIB_CHARGING_FW_LINK_ERROR) && 
     ((PrevChargerAction == EFI_QCOM_CHARGER_ACTION_LOAD_CHARGER_FW) || (PrevChargerAction == EFI_QCOM_CHARGER_ACTION_CONNECT_CHARGER_FW)))
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a cannot connect to charger FW after loading, go to recovery mode \r\n", __FUNCTION__));
    *pActionType = EFI_QCOM_CHARGER_ACTION_RECOVERY;
    PrevChargerAction = *pActionType;
    return Status;
  }
  /* Shutdown if Glink disconnect afterwards */
  if ((ErrorType == CHARGERLIB_CHARGING_FW_LINK_ERROR) && (PrevChargerAction != EFI_QCOM_CHARGER_ACTION_RECOVERY))
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Chg FW LINK Error = %d \r\n", __FUNCTION__, CHARGERLIB_CHARGING_FW_LINK_ERROR));
    *pActionType = EFI_QCOM_CHARGER_ACTION_SHUTDOWN;
    PrevChargerAction = *pActionType;
    return Status;
  }
  
  if((CHARGERLIB_CHARGING_ERROR_LOW_VBATT == ErrorType) || (CHARGERLIB_CHARGING_ERROR_BATTERY_NOT_DETECTED == ErrorType ) || (CHARGERLIB_CHARGING_ERROR_DEBUG_BOARD == ErrorType ) ||
    (CHARGERLIB_DEVICE_ERROR == ErrorType ) || (CHARGERLIB_CHARGING_ERROR_UNKNOWN_BATTERY == ErrorType ) ||
    (CHARGERLIB_CHARGING_ERROR_TSENSE_CRITICAL == ErrorType) || (CHARGERLIB_CHARGING_ERROR_TSENSE_TIMEOUT == ErrorType) || (CHARGERLIB_CHARGING_ERROR_TSENSE_HIGH == ErrorType))
  {
    Status = ChargerLib_GetErrorAction(ErrorType, (((CHARGERLIB_ERROR_ACTION_TYPE*)pActionType)));
    if(EFI_SUCCESS != Status)
    {
      CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Error Getting Charger Error Action = %r.\r\n", __FUNCTION__, Status));
      return Status;
    }

    if(*pActionType != EFI_QCOM_CHARGER_ACTION_START_CHARGING)
    {
    PrevChargerAction = *pActionType;
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a pActionType = %d.\r\n", __FUNCTION__, *pActionType));
    return Status;
    }
  }

  /* Assign Led config to toggle led */
  pChargerActionInfo->LedConfigType = (QCOM_CHARGER_PLATFORM_CHARGING_LED_CONFIG_TYPE)gChargerPlatformCfgData.ChargerLibCfgData.charger_led_config;

  if (PrevChargerAction == EFI_QCOM_CHARGER_ACTION_INVALID)
  {
    /* calling profile loading init in all conditions in order to parse the profile and pick the right batt_therm coeff in the right profile */
    /* actual writing to profile to sram will be determined in pmicDxe depend on the configuration set*/
      Status = ChargerPlatform_ProfileLoadingInit(pActionType, pChargerActionInfo, ErrorType);
      PrevChargerAction = *pActionType;

      /* Return since action is decided for this Invalid charging action case */
      return Status;
    }

  Status |= ChargerLib_GetBatteryStatus((chargerlib_batt_status_info*)&(pChargerActionInfo->BattStsInfo));
  if (EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Error Getting Battery Status = %r.\r\n", __FUNCTION__, Status));
    *pActionType = EFI_QCOM_CHARGER_ACTION_STOP_CHARGING;
    PrevChargerAction = *pActionType;

    /*If there is an error, return since action is decided */
    return Status;
  }

  if(CHARGERLIB_CHARGING_ERROR_NONE != ErrorType)
  {
    Status = ChargerLib_GetErrorAction(ErrorType, (((CHARGERLIB_ERROR_ACTION_TYPE*)pActionType)));
    PrevChargerAction = *pActionType;

    /*If there is a battery error, return */
    return Status;
  }

  Status = ChargerLib_GetChargingPath(&pChargerActionInfo->ChargerAttached);
  if (EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Error Getting Power Path = %r.\r\n", __FUNCTION__, Status));
    *pActionType = EFI_QCOM_CHARGER_ACTION_STOP_CHARGING;
    PrevChargerAction = *pActionType;
    return Status;
  }

  if (((QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_USB == pChargerActionInfo->ChargerAttached) || (QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_DCIN == pChargerActionInfo->ChargerAttached)) &&
    ((EFI_QCOM_CHARGER_ACTION_INVALID == PrevChargerAction) ||
    (EFI_QCOM_CHARGER_PLATFORM_ACTION_PROFILE_LOAD == PrevChargerAction) ||
    (EFI_QCOM_CHARGER_ACTION_NO_CHARGE_WAIT == PrevChargerAction)))
  {
    *pActionType = EFI_QCOM_CHARGER_ACTION_START_CHARGING;
  }
  else
  {
    Status = ChargerLib_GetChargingStatus(&ChargingEnabled);
    if(EFI_SUCCESS != Status)
    {
      CHARGER_DEBUG((EFI_D_WARN, "ChargerLib::%a Error Getting Charging Status = %r \r\n", __FUNCTION__, Status));
      return Status;
    }

    if(FALSE == ChargingEnabled)
    {
      /*Charger register dump in case need to determine why charging is disabled*/
        Status |= ChargerLib_DumpChargerPeripheral();
    }
    else
    {
        /* Charging already started, go to continue. */
      if(*pActionType != EFI_QCOM_CHARGER_ACTION_RECOVERY){ 
        *pActionType = EFI_QCOM_CHARGER_ACTION_CONTINUE;
      }
        /* Assign Led config to toggle led */
        /* pChargerActionInfo->LedConfigType = (QCOM_CHARGER_PLATFORM_CHARGING_LED_CONFIG_TYPE)gChargerPlatformCfgData.ChargerLibCfgData.charger_led_config;*/
      }

    if (QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_USB == pChargerActionInfo->ChargerAttached)
    {
      /* Check if charger was swapped/re-inserted */
      Status = ChargerLib_WasChargerReinserted(&bChargerReinserted);
      if(EFI_SUCCESS != Status )
      {
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib::%a Error = %d Error Checking Charger Re-insertion. \r\n", __FUNCTION__, Status));
        return Status;
      }

      if(bChargerReinserted)
      {
        //Status = ChargerLib_CheckAPSDResults();
        Status = ChargerLib_ReRunAicl();
      }
    }
  }

  Status |= ChargerPlatform_CheckIfOkToBoot(pActionType, *pChargerActionInfo, pChargerActionInfo->BattStsInfo);

  CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Action Returned = %d \r\n", __FUNCTION__,*pActionType));

  PrevChargerAction = *pActionType;

  return Status;
}

EFI_STATUS ChargerPlatform_LoadProfile(CONST QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo)
{
  QCOM_CHARGER_PLATFORM_BATT_PROFILE_DATA BattProfileInfo = {0};
  EFI_STATUS Status = EFI_SUCCESS;

  if(!pChargerActionInfo)
    return EFI_INVALID_PARAMETER;


  CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Battery Profile Loading is enabled \r\n", __FUNCTION__ ));
  switch(pChargerActionInfo->ProfState.eProfileState)
  {
    case QCOM_CHARGER_PLATFORM_PROFILE_LOAD:
      Status |= ChargerPlatformFile_ReadBatteryProfile(&BattProfileInfo);
      if(Status == EFI_SUCCESS)
      {
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Battery Profile File Read Success DataSize = %d \r\n", __FUNCTION__, BattProfileInfo.DataSize));
        Status |= ChargerLib_LoadProfile((chargerlib_batt_profile_data *)&BattProfileInfo);
      }
      else
      {
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Battery Profile File read Failed = %r \r\n", __FUNCTION__, Status));
      }
      /* Free allocated file buffer */
      if(NULL != BattProfileInfo.pFileBuffer)
        gBS->FreePool(BattProfileInfo.pFileBuffer);
    break;
    case QCOM_CHARGER_PLATFORM_PROFILE_RESTART:
      /* Restart FG Condition */
      Status |= ChargerPlatformFile_ReadBatteryProfile(&BattProfileInfo);
      if(Status == EFI_SUCCESS)
      {
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Battery Profile File Read Success DataSize = %d \r\n", __FUNCTION__, BattProfileInfo.DataSize));
        Status |= ChargerLib_LoadProfile((chargerlib_batt_profile_data *)&BattProfileInfo);
      }
      else
      {
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Battery Profile Restart = %r \r\n", __FUNCTION__, Status));
      }
      /* Free allocated file buffer */
      if(NULL != BattProfileInfo.pFileBuffer)
        gBS->FreePool(BattProfileInfo.pFileBuffer);
    break;
  
    default:
    break;
  }

  return Status;
}


EFI_STATUS ChargerPlatform_TakeAction(EFI_QCOM_CHARGER_ACTION_TYPE ChargingAction, CONST QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo)
{
  QCOM_CHARGER_BATT_STATUS_INFO CurrentBatteryStatus = {0};
  STATIC BOOLEAN bToggleLed = TRUE;
  EFI_STATUS Status = EFI_SUCCESS;
  CHARGERLIB_CHARGER_INPUT_STATUS ChargerInputStatus = {0};
  BOOLEAN charging_status = FALSE;

  if(!pChargerActionInfo)
  {
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Invalid parameter \r\n", __FUNCTION__));
    return EFI_INVALID_PARAMETER;
  }

  CurrentBatteryStatus = (QCOM_CHARGER_BATT_STATUS_INFO)pChargerActionInfo->BattStsInfo;

  switch (ChargingAction)
  {
  case EFI_QCOM_CHARGER_ACTION_CRITICAL:
         //print out and flush critical error messages
         //Perform AFP
         CHARGER_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerDxe::%a Critical Error occurred. Shutting down \r\n", __FUNCTION__));
         ChargerLib_ForceSysShutdown(CHGAPP_RESET_AFP);
         break;

  case   EFI_QCOM_CHARGER_ACTION_SHUTDOWN:
         //print error message and trigger system shutdown
         //These errors will only be checked and handled when battery voltage is not high enough to boot and uefi charging is needed.
         ChargerPlatform_Exit();
         CHARGER_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerDxe::%a Waiting for %d s \r\n", __FUNCTION__, QCOM_CHARGER_IDLE_WAIT_DURATION/QCOM_CHARGER_MS_TO_S));
#ifndef FEATURE_XBOOT
         WaitForTimeout (QCOM_CHARGER_IDLE_WAIT_DURATION, TIMEOUT_WAIT_FOR_KEY, NULL);
#endif /* !FEATURE_XBOOT */
         ChargerLib_ForceSysShutdown(CHGAPP_RESET_SHUTDOWN);
         break;

  case EFI_QCOM_CHARGER_ACTION_START_CHARGING:
          /* Assign entry voltage on warm boot and soc after profile is loaded or not loaded as in warm/cold boot */
          if(gChargerSharedInfo.uefi_entry_mV == QCOM_CHARGER_INVALID_VALUE_MARKER)
          {
            gChargerSharedInfo.uefi_entry_mV    = CurrentBatteryStatus.BatteryVoltage;
          }
          if (gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.LoadBatteryProfile == TRUE)
          {
            gChargerSharedInfo.uefi_entry_soc = CurrentBatteryStatus.StateOfCharge;
          }
          else
          {
            gChargerSharedInfo.uefi_entry_soc   = QCOM_CHARGER_INVALID_VALUE_MARKER;
          }
          CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Saving Entry VBatt  = %d SOC = %d \r\n", __FUNCTION__,
                          CurrentBatteryStatus.BatteryVoltage, CurrentBatteryStatus.StateOfCharge));
          if (QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_USB == pChargerActionInfo->ChargerAttached ||
                QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_DCIN == pChargerActionInfo->ChargerAttached)
          {
            ChargerLib_InitializeCharging();
          }
         break;

  case EFI_QCOM_CHARGER_ACTION_STOP_CHARGING:
         if(TRUE == gChargingInitialized)
         {
           ChargerLib_ChargerEnable(FALSE);
           gChargingInitialized = FALSE;
         }
         if(gChargerPlatformCfgData.ChargerLibCfgData.charger_led_config)
         {
           /* Turn Off Charging */
           bToggleLed = FALSE;
           ChargerLib_LedOn(bToggleLed);
         }
         break;

  case EFI_QCOM_CHARGER_ACTION_NO_CHARGE_WAIT:
  case EFI_QCOM_CHARGER_ACTION_TSENSE_HIGH_WAIT:
        ChargerLib_HandleNoChargeAndWait();
         if(gChargerPlatformCfgData.ChargerLibCfgData.enable_charger_wdog)
         {
           /* Pet the watchdog if feature is enabled */
           ChargerLib_PetChgWdog();
         }
         break;

  case EFI_QCOM_CHARGER_ACTION_CONTINUE:
         if(gChargerPlatformCfgData.ChargerLibCfgData.enable_charger_wdog)
         {
           /* Pet the watchdog if feature is enabled */
           ChargerLib_PetChgWdog();
         }
         if(gChargerPlatformCfgData.ChargerLibCfgData.charger_led_config)
         {
           ChargerLib_GetChargingStateForLed(&charging_status);
            /*  DEBUG ONLY */
           /* CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe::%a SWLedToggleConfig = %d \r\n", __FUNCTION__, gChargerPlatformCfgData.ChargerLibCfgData.charger_led_config)); */
           switch(gChargerPlatformCfgData.ChargerLibCfgData.charger_led_config)
           {
             case QCOM_CHARGER_PLATFORM_CHARGING_LED_ON:
              bToggleLed = charging_status;
              ChargerLib_LedOn(bToggleLed);
              break;
             case QCOM_CHARGER_PLATFORM_CHARGING_LED_TOGGLE:
               if(!charging_status)
               {
                 ChargerLib_LedOn(charging_status);
               }
               else
               {
                 ChargerLib_LedOn(bToggleLed);
                 bToggleLed = (bToggleLed == TRUE)? FALSE: TRUE;
               }               
              break;
             case QCOM_CHARGER_PLATFORM_CHARGING_LED_OFF:
              /* will not reache here */
             default:
              break;
            }
         }
         else
         {
           /*  DEBUG ONLY */
           /* CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Charging Led Indication is off = %d \r\n", __FUNCTION__, gChargerPlatformCfgData.ChargerLibCfgData.charger_led_config)); */
         }
         ChargerLib_GetChargerInputStatus(&ChargerInputStatus);
         CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a ICLFinal = %d mA, ICLMax = %d mA\r\n", __FUNCTION__,
                         ChargerInputStatus.ICLfinalMa, ChargerInputStatus.ICLMaxMa));
         /* Debug FG SRAM */
         ChargerLib_DumpSram(FALSE);
         break;

  case EFI_QCOM_CHARGER_ACTION_GOOD_TO_BOOT:
        /* Assign Exit voltage and soc */
        gChargerSharedInfo.uefi_exit_mV    = CurrentBatteryStatus.BatteryVoltage;
        if (gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.LoadBatteryProfile == TRUE)
        {
          gChargerSharedInfo.uefi_exit_soc = CurrentBatteryStatus.StateOfCharge;
        }
        else
        {
          gChargerSharedInfo.uefi_exit_soc   = QCOM_CHARGER_INVALID_VALUE_MARKER;
        }
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Saving Exit VBat = %d Soc = %d \r\n", __FUNCTION__,
                         CurrentBatteryStatus.BatteryVoltage, CurrentBatteryStatus.StateOfCharge));
        gChargerSharedInfo.uefi_charger_fw_mode = 0;
        /* Save Smem Info ignoring return status as XBL loader changes are not ready yet*/
        ChargerPlatform_SaveChargeInfoToSmem(&gChargerSharedInfo);
        if (gChargerPlatformCfgData.DCInCfgData.DCINDisableOnExit)
        {
          //suspend DCIn
          (void)ChargerLib_DcinSuspend(TRUE);
        }

        /* Turn Off Charging */
        bToggleLed = FALSE;
        ChargerLib_LedOn(bToggleLed);
        break;

  case EFI_QCOM_CHARGER_PLATFORM_ACTION_PROFILE_LOAD:
        /* Assign only entry voltage for smem before profile load, soc will be update after profile is loaded in next action which is start charging action*/
        gChargerSharedInfo.uefi_entry_mV    = CurrentBatteryStatus.BatteryVoltage;
        ChargerPlatform_LoadProfile(pChargerActionInfo);
        break;

  case EFI_QCOM_CHARGER_ACTION_SHUTDOWN_USB_DC_PON_DISABLED:
      //print error message and trigger system shutdown
      //These errors will only be checked and handled when battery voltage is not high enough to boot and uefi charging is needed.
      CHARGER_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerDxe::%a Waiting for %d s \r\n", __FUNCTION__, QCOM_CHARGER_IDLE_WAIT_DURATION/QCOM_CHARGER_MS_TO_S));
      WaitForTimeout (QCOM_CHARGER_IDLE_WAIT_DURATION, TIMEOUT_WAIT_FOR_KEY, NULL);
      ChargerLib_ForceSysShutdown(CHGAPP_RESET_SHUTDOWN_USB_DC_PON_DISABLED);
      break;

        break;
  case EFI_QCOM_CHARGER_ACTION_FACTORY_MODE_BOOT_TO_HLOS:
      CHARGER_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerDxe:: Factory Mode - Boot to HLOS\r\n"));
      break;

  case EFI_QCOM_CHARGER_ACTION_RESET_COLD:
      //print error message and trigger system reset
      //These errors will only be checked and handled when battery voltage is not high enough to boot and uefi charging is needed.
      ChargerPlatform_Exit();
      CHARGER_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerDxe::%a Waiting for %d s \r\n", __FUNCTION__, QCOM_CHARGER_IDLE_WAIT_DURATION/QCOM_CHARGER_MS_TO_S));
      WaitForTimeout (QCOM_CHARGER_IDLE_WAIT_DURATION, TIMEOUT_WAIT_FOR_KEY, NULL);
      ChargerLib_ForceSysShutdown(CHGAPP_RESET_COLD);
        break;

  case EFI_QCOM_CHARGER_ACTION_LOAD_CHARGER_FW:
      gChargerSharedInfo.uefi_charger_fw_mode = CHARGER_FW_MODE;
      ChargerPlatform_SaveChargeInfoToSmem(&gChargerSharedInfo);
      Status = ChargerPlatform_LoadChargerFW();
      if (Status != EFI_SUCCESS || !gEnableChargerFW)
      {
        gChargerSharedInfo.uefi_charger_fw_mode = CHARGER_FW_MISSING;
        Status = EFI_SUCCESS;
      }//test
      break;

  case EFI_QCOM_CHARGER_ACTION_CONNECT_CHARGER_FW:
      Status = ChargerPlatform_LinkChargerFW();
      if (Status != EFI_SUCCESS || !gEnableChargerFW)
      {
        gChargerSharedInfo.uefi_charger_fw_mode = CHARGER_FW_MISSING;
        Status = EFI_SUCCESS;
      }
      else
      {
        if((gChargerPlatformCfgData.ChargerPDLoggingCfgData.LoggingIntervalInSec > 0) && Status==EFI_SUCCESS)
        {
          Status = ChargerPlatform_CpdlogConfig();
        }
      }
      break;

  case EFI_QCOM_CHARGER_ACTION_RECOVERY:
      Status = ChargerPlatform_HandleRecovery();
      if(gChargerPlatformCfgData.ChargerLibCfgData.enable_charger_wdog)
      {
           /* Pet the watchdog if feature is enabled */
           ChargerLib_PetChgWdog();
      }
      ChargerLib_GetChargerInputStatus(&ChargerInputStatus);
      CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a ICLFinal = %d mA, ICLMax = %d mA\r\n", __FUNCTION__,
                      ChargerInputStatus.ICLfinalMa, ChargerInputStatus.ICLMaxMa));
                      
      break;

    default:
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Action Passed = %d \r\n", __FUNCTION__,ChargingAction));
      break;
  }

  return Status;
}


/**
ChargerPlatform_GetUefiVariableValues()

@brief
Reads UEFI Variables changed via BDS Menu
*/
EFI_STATUS ChargerPlatform_GetUefiVariableValues( VOID)
{
  UINT8          Flag          = 0;
  UINTN          VarSize       = sizeof(Flag);
  STATIC BOOLEAN VariablesRead = FALSE;
  EFI_STATUS     Status = EFI_SUCCESS;

  if (FALSE == VariablesRead)
  {
    VariablesRead = TRUE;
    /*We are supposed to read only once. if the variable doesn't exist, make assumption on the value to treat
      variable not being there as expected condition and cache the expectation instead. We are memsetting the
      structure variable and so by default it is disabled
    */
    VarSize = sizeof(Flag);
    Status = gRT->GetVariable(L"PrintChargerAppDbgMsg", &gQcomTokenSpaceGuid, NULL, &VarSize, &Flag);
    if (EFI_SUCCESS == Status )
    {
      gChargerPlatformCfgData.ChargerLibCfgData.dbg_cfg_Data.print_charger_app_dbg_msg = (Flag) ? TRUE : FALSE;
    }

    VarSize = sizeof(Flag);
    /*Read ChargerPD Log Level, set via BDS menu*/
    Status = gRT->GetVariable(L"ChargerPDLogLevel", &gQcomTokenSpaceGuid, NULL, &VarSize, &Flag);
    if (EFI_SUCCESS == Status )
    {
      gChargerPlatformCfgData.ChargerPDLoggingCfgData.LogLevel = Flag;
    }

    VarSize = sizeof(Flag);
    /*Read ChargerPD Log Timer, set via BDS menu*/
    Status = gRT->GetVariable(L"ChargerPDLogTimer", &gQcomTokenSpaceGuid, NULL, &VarSize, &Flag);
    if (EFI_SUCCESS == Status )
    {
      gChargerPlatformCfgData.ChargerPDLoggingCfgData.LoggingIntervalInSec = Flag;
      gChargerPlatformCfgData.ChargerLibCfgData.connect_glink_logging_channel = (gChargerPlatformCfgData.ChargerPDLoggingCfgData.LoggingIntervalInSec > 0) ? TRUE : FALSE;  //To be used by ChargerLibTarget.c to establish glink connection for fetching chargerPD logs after loading chargerPD
    } 
     VarSize = sizeof(Flag);
    /*Read SOC based threshold charging, set via BDS menu*/
    Status = gRT->GetVariable(L"SocBasedBoot", &gQcomTokenSpaceGuid, NULL, &VarSize, &Flag);
    if (EFI_SUCCESS == Status )
    {
        gChargerPlatformCfgData.ChargerLibCfgData.soc_based_boot = Flag;
    }
  }
  return EFI_SUCCESS;
}

/**
ChargerPlatform_GetConfigData()

@brief
Returns config data
*/
EFI_STATUS ChargerPlatform_GetConfigData
(
  QCOM_CHARGER_PLATFORM_CFGDATA_TYPE *pChargerPlatformCfgData
)
{

  if(!pChargerPlatformCfgData)
    return EFI_INVALID_PARAMETER;

  CopyMemS(pChargerPlatformCfgData, sizeof(QCOM_CHARGER_PLATFORM_CFGDATA_TYPE), &gChargerPlatformCfgData, sizeof(QCOM_CHARGER_PLATFORM_CFGDATA_TYPE));

  return EFI_SUCCESS;
}


/**
ChargerPlatform_ReadCfgParams()

@brief
Battery Parameter Default Configurations file read Call Back
*/
VOID
ChargerPlatform_ReadCfgParams
(
  UINT8* Section,
  UINT8* Key,
  UINT8* Value
)
{

  //CHARGER_DEBUG(( EFI_D_INFO, "Section = \"%s\", Key = \"%s\", Value = \"%s\"\n", Section, Key, Value));

  if (AsciiStriCmp ((CHAR8*)Section, "PlatformCommon") == 0) //Common
  {
    if (AsciiStriCmp ((CHAR8*)Key, "CfgVersion") == 0)
    {
    gChargerPlatformCfgData.CfgVersion = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "EnableChargerFW") == 0)
    {
      gEnableChargerFW = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }
    if (AsciiStriCmp ((CHAR8*)Key, "SWFlashMinBattVoltageMv") == 0)
    {
      gChargerPlatformCfgData.SWFlashMinBattVoltageMv = ChargerPlatformFile_AsciiToInt((char *)Value);
      if(gIs_2S_Battery)
      {
        gChargerPlatformCfgData.SWFlashMinBattVoltageMv *=2;
      }
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "BootToHLOSThresholdInMv") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.boot_to_hlos_threshold_in_mv = ChargerPlatformFile_AsciiToInt((char *)Value);
      if(gIs_2S_Battery)
      {
        gChargerPlatformCfgData.ChargerLibCfgData.boot_to_hlos_threshold_in_mv *=2;
      }
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "OsStandardBootSocThreshold") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.boot_to_hlos_threshold_in_soc = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "SocBasedBoot") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.soc_based_boot = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "EnDebugAccessMode") == 0)
    {
        gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.EnDebugAccessMode = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
        return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "EnFMB") == 0)
    {
        gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.EnFMB = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
        return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "DAMSelIcl3AorFMB") == 0)
    {
        gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.DAMSelIcl3AorFMB = ChargerPlatformFile_AsciiToInt((char *)Value);
        return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "EnableChargerWdog") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.enable_charger_wdog = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "DispSignOfLifeMaxThresholdMv") == 0)
    {
      gChargerPlatformCfgData.DispSignOfLifeMaxThresholdMv = ChargerPlatformFile_AsciiToInt((char *)Value);
      if(gIs_2S_Battery)
      {
        gChargerPlatformCfgData.DispSignOfLifeMaxThresholdMv *=2;
      }
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "ChargerLedConfig") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.charger_led_config = ChargerPlatformFile_AsciiToInt((CHAR8*)Value);
      return;
    }


    if (AsciiStriCmp((CHAR8*)Key, "DCInBootToHLOSThresholdInMv") == 0)
    {
      gChargerPlatformCfgData.DCInCfgData.DCInBootThreshold = ChargerPlatformFile_AsciiToInt((char *)Value);
      if(gIs_2S_Battery)
      {
        gChargerPlatformCfgData.DCInCfgData.DCInBootThreshold *=2;
      }
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "SuspendDCIn") == 0)
    {
      gChargerPlatformCfgData.DCInCfgData.DCINDisableOnExit = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
      return;
    }

    if (AsciiStriCmp((CHAR8 *)Key, "ChargingTermCurrent") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.ChargingTermCurrent = ChargerPlatformFile_AsciiToInt((char *)Value);
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.ChargingTermCurrent = gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.ChargingTermCurrent;
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "BattMissingCfg") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.BattMissingCfg = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "FgCondRestart") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgCondRestart = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "VBattEstDiffThreshold") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.VBattEstDiffThreshold = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "LoadBatteryProfile") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.LoadBatteryProfile = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "SWThermalMitigationEnable") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.sw_thermal_mitigation_enable = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      return;
    }

    if (AsciiStriCmp((CHAR8 *)Key, "BattVoltLimHighDelta") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.batt_volt_lim_high_delta = ChargerPlatformFile_AsciiToInt((char *)Value);
      if(gIs_2S_Battery)
      {
        gChargerPlatformCfgData.ChargerLibCfgData.batt_volt_lim_high_delta *=2;
      }
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "PrintChargerAppDbgMsg") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.dbg_cfg_Data.print_charger_app_dbg_msg = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "PrintChargerAppDbgMsgToFile") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.dbg_cfg_Data.print_charger_app_dbg_msg_to_file= ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "FileLoggingDbgLevelMask") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.dbg_cfg_Data.file_log_level_mask = ChargerPlatformFile_AsciiStrToHex((CHAR8 *)Value, AsciiStrLen((CHAR8 *)Value));
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "BatteryIdTolerance") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgBattIdCfg.BatteryIdTolerance = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "DebugBoardBatteryIdMin") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgBattIdCfg.DebugBoardBatteryIdMin = ChargerPlatformFile_AsciiToInt((char *)Value);;
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "DebugBoardBatteryIdMax") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgBattIdCfg.DebugBoardBatteryIdMax = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "RegularBatteryIdMin") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgBattIdCfg.RegularBatteryIdMin = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "RegularBatteryIdMax") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgBattIdCfg.RegularBatteryIdMax = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "SmartBatteryIdMin") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgBattIdCfg.SmartBatteryIdMin = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "SmartBatteryIdMax") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgBattIdCfg.SmartBatteryIdMax = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "ConservChgFvDelta") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.conserv_chg_fv_delta = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "NoChargeAndWait") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.no_charge_and_wait = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "EmergencyShutdownVbatt") == 0)
    {
      if(gIs_2S_Battery)
          return;
      
      gChargerPlatformCfgData.ChargerLibCfgData.emergency_shutdown_vbatt = ChargerPlatformFile_AsciiToInt((char *)Value);
    }
    
    if (AsciiStriCmp ((CHAR8*)Key, "EmergencyShutdownVbatt2s") == 0)
    {
      if(gIs_2S_Battery)
          gChargerPlatformCfgData.ChargerLibCfgData.emergency_shutdown_vbatt = ChargerPlatformFile_AsciiToInt((char *)Value);
      
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "UnknownBatteryBehavior") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.unknown_battery_behavior= ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "DebugBoardBehavior") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.debug_board_behavior= ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "ProgramSkinAndChargerHotThreshold") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.SkinAndChargerHotThreshold.ProgramSkinAndChargerHotThreshold = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgSkinDieTemp.ProgramSkinAndChargerHotThreshold = gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.SkinAndChargerHotThreshold.ProgramSkinAndChargerHotThreshold;
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "DeviceSkinHotInC") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.SkinAndChargerHotThreshold.DeviceSkinHotInC = ChargerPlatformFile_AsciiToInt((char *)Value);
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgSkinDieTemp.DeviceSkinHotInC = gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.SkinAndChargerHotThreshold.DeviceSkinHotInC;
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "DeviceSkinTooHotInC") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.SkinAndChargerHotThreshold.DeviceSkinTooHotInC = ChargerPlatformFile_AsciiToInt((char *)Value);
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgSkinDieTemp.DeviceSkinTooHotInC = gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.SkinAndChargerHotThreshold.DeviceSkinTooHotInC;
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "ChargerTooHotInC") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.SkinAndChargerHotThreshold.ChargerTooHotInC= ChargerPlatformFile_AsciiToInt((char *)Value);
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgSkinDieTemp.ChargerTooHotInC = gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.SkinAndChargerHotThreshold.ChargerTooHotInC;
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "ChargerHotInC") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.SkinAndChargerHotThreshold.ChargerHotInC = ChargerPlatformFile_AsciiToInt((char *)Value);
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgSkinDieTemp.ChargerHotInC = gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.SkinAndChargerHotThreshold.ChargerHotInC;
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "DumpSram") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgSramDbgCfg.DumpSram = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "DumpSramStartAddr") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgSramDbgCfg.DumpSramStartAddr = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "DumpSramEndAddr") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgSramDbgCfg.DumpSramEndAddr = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "DumpSramDuration") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgSramDbgCfg.DumpSramDuration = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "BattThermBiasWait") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgBattThermCfg.BiasWait = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }
    if (AsciiStriCmp((CHAR8*)Key, "BattThermGndSel") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgBattThermCfg.GroundSel = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "AuxThermBiasWait") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgAuxThermCfg.BiasWait = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }
    if (AsciiStriCmp((CHAR8*)Key, "AuxThermGndSel") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgAuxThermCfg.GroundSel = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "TsensExtremeTemp") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.thermal_configs.tsens_extreme_Temp = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "TsensHighTemp") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.thermal_configs.tsens_high_temp = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "TsensLowTemp") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.thermal_configs.tsens_low_temp = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "TsensTimeoutMins") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.thermal_configs.tsens_timeout_mins = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "EnableChargerFgDump") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.dbg_cfg_Data.enable_charger_fg_Dump = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "RconnComp") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.RconnComp = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }
    if (AsciiStriCmp ((CHAR8*)Key, "EnShipMode") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.shipmode_cfg.enable_shipmode = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      return;
    }

    if (AsciiStriCmp ((CHAR8*)Key, "ShipModeVarStr") == 0)
    {
      AsciiStrCpyS (gChargerPlatformCfgData.ChargerLibCfgData.shipmode_cfg.shipMode_str, CHARGERLIB_SHIPMODE_STR_LEN,(CHAR8*)Value);
      return;
    }
    if (AsciiStriCmp((CHAR8*)Key, "SkinTempSrc") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.EnableSkinTempINov = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "DieTempSrc") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.EnableDieTempINov = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "DieTempCompSrc") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.EnableDieTempCompINov = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "PlatHWCfgOverrdie") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.plat_hw_cfg_override = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "ChargerPDLoggingCategories") == 0)
    {
      gChargerPlatformCfgData.ChargerPDLoggingCfgData.LogCategories = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "ChargerPDLoggingLevel") == 0)
    {
      gChargerPlatformCfgData.ChargerPDLoggingCfgData.LogLevel = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "ChargerPDLoggingSize") == 0)
    {
      gChargerPlatformCfgData.ChargerPDLoggingCfgData.MaxLogSize = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }

    if (AsciiStriCmp((CHAR8*)Key, "ChargerpdReadInterval") == 0)
    {
      gChargerPlatformCfgData.ChargerPDLoggingCfgData.LoggingIntervalInSec = ChargerPlatformFile_AsciiToInt((char *)Value);
      
      gChargerPlatformCfgData.ChargerLibCfgData.connect_glink_logging_channel = (gChargerPlatformCfgData.ChargerPDLoggingCfgData.LoggingIntervalInSec > 0) ? TRUE : FALSE; //To be used by ChargerLibTarget.c to establish glink connection for fetching chargerPD logs after loading chargerPD
      return;
    }
    if (AsciiStriCmp((CHAR8*)Key, "ChargerpdQBGDumpEnable") == 0)
    {
      gChargerPlatformCfgData.ChargerPDLoggingCfgData.EnableQBGDump = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
    }
    
    if (AsciiStriCmp ((CHAR8*)Key, "VbattThresholdMarginInMv") == 0)
    {
      gChargerPlatformCfgData.ChargerLibCfgData.vbatt_threshold_margin_in_mv = ChargerPlatformFile_AsciiToInt((char *)Value);
      if(gIs_2S_Battery)
      {
        gChargerPlatformCfgData.ChargerLibCfgData.vbatt_threshold_margin_in_mv *=2;
      }
      return;
    }
  }
  else if ( ((EFI_PLATFORMINFO_TYPE_MTP == PlatformType || EFI_PLATFORMINFO_TYPE_ATP == PlatformType || EFI_PLATFORMINFO_TYPE_IDP == PlatformType) && (AsciiStriCmp ((CHAR8*)Section, "PlatformMTP") == 0)) ||
       (((EFI_PLATFORMINFO_TYPE_QRD == PlatformType) || (EFI_PLATFORMINFO_TYPE_HDK == PlatformType)) && (AsciiStriCmp ((CHAR8*)Section, "PlatformQRD") == 0)))
  {
  /*Parameters w.r.t. MTP and QRD Platforms*/
  if (AsciiStriCmp ((CHAR8*)Key, "ChgFccMax") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.ChgFccMax = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "ChgFvMax") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.ChgFvMax = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaFvCompHotCfg") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaFvCompHotCfg = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "JeitaFvCompColdCfg") == 0)
  {
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaFvCompColdCfg = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaCcCompHotCfg") == 0)
  {
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaCcCompHotCfg = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "JeitaCcCompColdCfg") == 0)
  {
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaCcCompColdCfg = ChargerPlatformFile_AsciiToInt((char *)Value);
      return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "HwAfpHotLimit") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.HwAfpHotThreshold = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "HwAfpColdLimit") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.HwAfpColdThreshold = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaCriticalTempLowLimit") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.HwJeitaThreshold.JeitaCriticalTempLowLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaCriticalTempLowLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
        return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaHardColdLimit") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.HwJeitaThreshold.JeitaHardColdLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaHardColdLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
        return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftColdLimit") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.HwJeitaThreshold.JeitaSoftColdLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaSoftColdLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
        return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftHotLimit") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.HwJeitaThreshold.JeitaSoftHotLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaSoftHotLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
        return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaHardHotLimit") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.HwJeitaThreshold.JeitaHardHotLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaHardHotLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
        return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaCriticalTempHighLimit") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.HwJeitaThreshold.JeitaCriticalTempHighLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaCriticalTempHighLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
        return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "JeitaHardLimitEnable") == 0)
  {
      gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaHardLimitEnable = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
      return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftColdFvCompEnable") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.HwJeitaThreshold.JeitaSoftColdFvCompEnable = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaSoftColdFvCompEnable = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
        return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftHotFvCompEnable") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.HwJeitaThreshold.JeitaSoftHotFvCompEnable = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaSoftHotFvCompEnable = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftColdCcCompEnable") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.HwJeitaThreshold.JeitaSoftColdCcCompEnable = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaSoftColdCcCompEnable = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftHotCcCompEnable") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.HwJeitaThreshold.JeitaSoftHotCcCompEnable = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    gChargerPlatformCfgData.ChargerLibCfgData.schg_cfg_data.SchgJeitaData.JeitaSoftHotCcCompEnable = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "VBatEmpty") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.VBatEmpty= ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "BattMissingDelay") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgBattIdCfg.BattMissingDelay = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "BattIdPullUp") == 0)
  {
    gChargerPlatformCfgData.ChargerLibCfgData.fg_cfg_data.FgBattIdCfg.IdPullup = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }
  }
  return;
}


EFI_STATUS ChargerPlatform_SaveChargeInfoToSmem(pm_chg_info_type *ChargerActionInfo)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32     buf_size = sizeof(pm_chg_info_type);
  UINT32     buf_size_ret = 0;
  pm_chg_info_type *pSmemChargerInfo = NULL, *pSmemChargerInfoRet = NULL;

  pSmemChargerInfo = (pm_chg_info_type *) smem_get_addr(SMEM_CHARGER_BATTERY_INFO, &buf_size_ret);
  if(!pSmemChargerInfo)
  {
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Retrieve Error.. XBL Core allocating SMEM now \r\n",__FUNCTION__));
      /* Assume Smem is already initilized in XBL Loader - No need to alloc as XBL loader will alloc for Core keeping this as debug code */
    pSmemChargerInfo = (pm_chg_info_type *)smem_alloc(SMEM_CHARGER_BATTERY_INFO, buf_size);
    if(!pSmemChargerInfo)
    {
      CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a smem_alloc Error \r\n",__FUNCTION__));
      return EFI_DEVICE_ERROR;
    }
    else
    {
      CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a SMEM Allocated \r\n",__FUNCTION__));
      /* Initialized to -1 since SBL did not allocate smem yet */
      pSmemChargerInfo->version       = 1;
      pSmemChargerInfo->sbl_entry_mV  = QCOM_CHARGER_INVALID_VALUE_MARKER;
      pSmemChargerInfo->sbl_entry_soc = QCOM_CHARGER_INVALID_VALUE_MARKER;
    }
  }

  /* Assign required values to smem memory */
  pSmemChargerInfo->uefi_entry_mV  = ChargerActionInfo->uefi_entry_mV;
  pSmemChargerInfo->uefi_exit_mV   = ChargerActionInfo->uefi_exit_mV;
  pSmemChargerInfo->uefi_entry_soc = ChargerActionInfo->uefi_entry_soc;
  pSmemChargerInfo->uefi_exit_soc  = ChargerActionInfo->uefi_exit_soc;
  pSmemChargerInfo->uefi_charger_fw_mode = ChargerActionInfo->uefi_charger_fw_mode; /**< uefi_charger_fw_mode */

  buf_size_ret = 0;

  pSmemChargerInfoRet = (pm_chg_info_type *) smem_get_addr(SMEM_CHARGER_BATTERY_INFO, &buf_size_ret);
  if(!pSmemChargerInfoRet){
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Retrieve Error 2 \r\n",__FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: buf_size_ret = %d uefi_entry_mV = %d uefi_exit_mV = %d uefi_entry_soc = %d \r\n", buf_size_ret, pSmemChargerInfoRet->uefi_entry_mV, pSmemChargerInfoRet->uefi_exit_mV, pSmemChargerInfoRet->uefi_entry_soc));
  CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: sbl_entry_mV = %d sbl_entry_soc = %d ueft_exit_soc = %d \r\n", pSmemChargerInfoRet->sbl_entry_mV, pSmemChargerInfoRet->sbl_entry_soc, pSmemChargerInfoRet->uefi_exit_soc));

  pSmemChargerInfoRet = NULL;
  pSmemChargerInfo    = NULL;

  return Status;

}

EFI_STATUS ChargerPlatform_ProfileLoadingInit(EFI_QCOM_CHARGER_ACTION_TYPE *pActionType, QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo, CHARGERLIB_CHARGING_ERROR_TYPES errType)
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_CHARGER_PLATFORM_BATT_PROFILE_STATUS BattProfileStatus    = {0};
  QCOM_CHARGER_BATT_STATUS_INFO             CurrentBatteryStatus = {0};
  //CHARGERLIB_CHARGING_ERROR_TYPES           ErrorType  = CHARGERLIB_CHARGING_ERROR_NONE;

  Status = ChargerLib_GetBatteryProfileStatus((chargerlib_batt_profile_status *)&BattProfileStatus);
  if( EFI_SUCCESS == Status)
  {
    /* Attempt to load profile or restart FG will be called if below errors turns not TRUE */
    if ((errType != CHARGERLIB_CHARGING_ERROR_BATTERY_NOT_DETECTED) &&
       (errType != CHARGERLIB_CHARGING_ERROR_DEBUG_BOARD) &&
       (errType != CHARGERLIB_CHARGING_ERROR_BATT_TEMP_OUTSIDE_OPERATIONAL_RANGE) &&
       (errType != CHARGERLIB_CHARGING_ERROR_TSENSE_CRITICAL) &&
       (errType != CHARGERLIB_DEVICE_ERROR) &&
       (errType != CHARGERLIB_CHARGING_ERROR_FG_ERROR) &&
       (errType != CHARGERLIB_CHARGING_ERROR_ADC_ERROR))
    {
      /* Assign Profile State info for action */
      pChargerActionInfo->ProfState.eProfileState = (QCOM_CHARGER_PLATFORM_BATT_PROFILE_STATE) BattProfileStatus.eProfileState;
      Status |= ChargerLib_GetBatteryStatus((chargerlib_batt_status_info*)&CurrentBatteryStatus);
      if(EFI_SUCCESS != Status )
      {
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Get Battery Status Error = %r.\r\n", __FUNCTION__, Status));
        return Status;
      }
      pChargerActionInfo->BattStsInfo = CurrentBatteryStatus;
      /* Return same action for both profile state as FG would internally handle profile load or restart */
      *pActionType = EFI_QCOM_CHARGER_PLATFORM_ACTION_PROFILE_LOAD;
      switch(BattProfileStatus.eProfileState)
      {
        case PM_FG_BATT_PROFILE_LOAD:
          if(gChargerPlatformCfgData.DispSignOfLifeMaxThresholdMv == 0)
          {
            gChargerPlatformCfgData.DispSignOfLifeMaxThresholdMv  = QCOM_CHARGER_LOW_THERSHOLD_VBAT;
          }
          pChargerActionInfo->DispSignOfLifeMaxThresholdMv = gChargerPlatformCfgData.DispSignOfLifeMaxThresholdMv + QCOM_CHARGER_VBAT_ERROR_MARGIN;
          if (errType == CHARGERLIB_CHARGING_ERROR_CHARGING_SOURCE_NOT_DETECTED)
            pChargerActionInfo->bChargerSrcPresent = FALSE;
          else
            pChargerActionInfo->bChargerSrcPresent = TRUE;
          /*Disable Charging to get accurate VBAT reading */
          Status |= ChargerLib_ChargerEnable(FALSE);

          /* Not enabling charging since charger app does not know if charging needs to enabled or not at this stage */
          /* Status |= ChargerLib_ChargerEnable(TRUE); */
          break;
          case PM_FG_BATT_PROFILE_RESTART:
            /* Restart FG if needed */
            /* PrevChargerAction = *pActionType = QCOM_CHARGER_PLATFORM_ACTION_PROFILE_LOAD; */
          break;
          default:
          break;
      }
    }
    else
    {
      CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a eProfileState = %d.Charger Lib Error = %d \r\n", __FUNCTION__, BattProfileStatus.eProfileState, errType));
    }
  }
  else
  {
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a _GetBatteryProfileStatus/ChargerLib_GetErrors Error = %r.\r\n", __FUNCTION__, Status));
    Status = EFI_SUCCESS; /* Not an error to stop boot */
  }

  return Status;
}

EFI_STATUS ChargerPlatform_CheckIfOkToBoot
(
  EFI_QCOM_CHARGER_ACTION_TYPE *pActionType,
  QCOM_CHARGER_PLATFORM_ACTION_INFO  ChargerActionInfo,
  QCOM_CHARGER_BATT_STATUS_INFO      CurrentBatteryStatus
)
{
  BOOLEAN is_below_threshold = FALSE;
  EFI_STATUS Status = EFI_SUCCESS;
  CHARGERLIB_PLATFORM_PWRON_REASON_TYPE PonReasonType = { 0 };
#ifdef FEATURE_XBOOT
  UINT32 Threshold;
#endif /* FEATURE_XBOOT */

  Status = ChargerLib_GetPlatformPwrOnReason(&PonReasonType);
  if (Status != EFI_SUCCESS)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerPlatform:: %a Error getting PON reason = %r \r\n", __FUNCTION__, Status));
    return Status;
  }
  if(gChargerPlatformCfgData.ChargerLibCfgData.soc_based_boot)
  {
    if(gChargerSharedInfo.uefi_charger_fw_mode == CHARGER_FW_MODE)
      is_below_threshold = ChargerPlatform_IsBelowThreshold(gThresholdSoc, CurrentBatteryStatus.StateOfCharge, QCOM_CHARGER_SOC_THRESHOLD_MARGIN);
    else
      is_below_threshold = ChargerPlatform_IsBelowThreshold(gThresholdSoc, CurrentBatteryStatus.StateOfCharge, 0);
  }
  else
  {
#ifdef FEATURE_XBOOT
    if((QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_DCIN == ChargerActionInfo.ChargerAttached) ||
        (QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_USB == ChargerActionInfo.ChargerAttached))
    {
        /* case of charging */
        Threshold = gThresholdVbatt;
    }
    else
    {
        /* case of not charging */
        Threshold = BOOT_TO_HLOS_TH_WITHOUT_CHGR;
    }
    CHARGER_DEBUG((EFI_D_ERROR, "QcomChargerDxe:: %a VBatt = %d mV, Ocv = %d mV, Threshold = %d\r\n",
            __FUNCTION__, CurrentBatteryStatus.BatteryVoltage, CurrentBatteryStatus.Ocv, Threshold));
    if(gChargerSharedInfo.uefi_charger_fw_mode == CHARGER_FW_MODE)
      is_below_threshold = ChargerPlatform_IsBelowThreshold(Threshold, CurrentBatteryStatus.Ocv, gChargerPlatformCfgData.ChargerLibCfgData.vbatt_threshold_margin_in_mv);
    else
      //in recovery mode use Vbatt threshold which is 3.6V.
      is_below_threshold = ChargerPlatform_IsBelowThreshold(Threshold, CurrentBatteryStatus.BatteryVoltage, 0);
#else /* !FEATURE_XBOOT */
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a VBatt = %d mV, Ocv = %d mV, dgThresholdVbatt = %d , vbatt_threshold_margin_in_mv = %d \r\n",
                  __FUNCTION__, CurrentBatteryStatus.BatteryVoltage, CurrentBatteryStatus.Ocv, gThresholdVbatt, gChargerPlatformCfgData.ChargerLibCfgData.vbatt_threshold_margin_in_mv));
    if(gChargerSharedInfo.uefi_charger_fw_mode == CHARGER_FW_MODE)
      is_below_threshold = ChargerPlatform_IsBelowThreshold(gThresholdVbatt, CurrentBatteryStatus.Ocv, gChargerPlatformCfgData.ChargerLibCfgData.vbatt_threshold_margin_in_mv);
    else
      //in recovery mode use Vbatt threshold which is 3.6V.
      is_below_threshold = ChargerPlatform_IsBelowThreshold(gChargerPlatformCfgData.SWFlashMinBattVoltageMv, CurrentBatteryStatus.BatteryVoltage, 0);
#endif /* !FEATURE_XBOOT */
  }

  if(gChargerSharedInfo.uefi_charger_fw_mode == CHARGER_FW_MODE)
  {
    if(!is_below_threshold)
    {
      if(((QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_DCIN == ChargerActionInfo.ChargerAttached) || (QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_USB == ChargerActionInfo.ChargerAttached)) 
      && (PonReasonType.USB_CHG || PonReasonType.DC_CHG || PonReasonType.CBLPWR))          
      {
        *pActionType = EFI_QCOM_CHARGER_ACTION_SHUTDOWN;
        CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Device Will Reboot After ADSP Charging \r\n", __FUNCTION__));
      }
      else
      {
        /* charger removed, do reset */
        *pActionType = EFI_QCOM_CHARGER_ACTION_RESET_COLD;
        CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Device Will Reboot After ADSP Charging \r\n", __FUNCTION__));
      }
      
    }
  }
  else
  {
    if(!is_below_threshold)
    {
      *pActionType = EFI_QCOM_CHARGER_ACTION_GOOD_TO_BOOT;
      CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a no fw loaded good to boot \r\n", __FUNCTION__));
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS ChargerPlatformFile_GetChargerConfig(EFI_QCOM_CHARGER_CONFIG_KEY ChargerCfgKey, UINT32 *KeyValue)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(FALSE == gChargerCfgInitialized)
  {
    return EFI_DEVICE_ERROR;
  }

  if(NULL == KeyValue)
  {
    return EFI_INVALID_PARAMETER;
  }

  switch(ChargerCfgKey)
  {
    case EFI_QCOM_CHARGER_CONFIG_KEY_SW_FLASH_VOLTAGE:
      *KeyValue = gChargerPlatformCfgData.SWFlashMinBattVoltageMv;
    break;
    default:
      Status = EFI_INVALID_PARAMETER;
    break;
  }

  return Status;
}


EFI_STATUS ChargerPlatform_HandleShipMode(void)
{
  EFI_STATUS Status     = EFI_SUCCESS;
  BOOLEAN    EnShipMode = FALSE;

  /* Read Ship mode var value */
  Status  = ChargerLib_GetShipMode(&EnShipMode);
  if ((EFI_SUCCESS == Status )&& (EnShipMode == TRUE))
  {
    /* Enable ship mode
    Flash LED or HW flashes LED on ship mode entering
    flush logs on debug environment */
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Performing AFP \r\n",__FUNCTION__));

    Status = ChargerLib_ForceSysShutdown(CHGAPP_RESET_AFP);
    /* Control does not return */
  }
  return EFI_SUCCESS;
}


EFI_STATUS ChargerPlatform_LoadChargerFW()
{
  EFI_STATUS         Status      = EFI_SUCCESS;

  if (!RETAIL)
  {
    SerialPortFlush();
  }
  /* TBD - Return BACK up NV error state so Action can display with minimum charging specification or return error during actual loading */
  Status = ChargerLib_LoadChargerFW();

  if (!RETAIL)
  {
    SerialPortFlush();
  }

  return Status;
}


EFI_STATUS ChargerPlatform_LinkChargerFW()
{
  EFI_STATUS                Status            = EFI_SUCCESS;

  Status = ChargerLib_LinkChargerFW();
  return Status;
}

EFI_STATUS ChargerPlatform_HandleRecovery()
{
  EFI_STATUS                Status            = EFI_SUCCESS;

  Status = ChargerLib_HandleRecovery();
  return Status;

}


EFI_STATUS ChargerPlatform_CpdlogConfig( VOID ){
  EFI_STATUS  Status = EFI_SUCCESS; 

  Status = ChargerLib_CpdlogGetProperty(&LoggingCategories); // Read Chargerpd logging categories from SDAM before setting config file parameter via glink. 
  if(Status != EFI_SUCCESS){
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Get ChargerPD logging categories from SDAM failed \r\n", __FUNCTION__));
  }

  /*Set ChargerPD Logging Level and Categories via PMIC GLINK*/
  Status = ChargerLib_CpdlogSetProperties(gChargerPlatformCfgData.ChargerPDLoggingCfgData.LogCategories, gChargerPlatformCfgData.ChargerPDLoggingCfgData.LogLevel);
  if(Status == EFI_INVALID_PARAMETER)    
  {        
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a ChargerPD logging properties invalid \r\n", __FUNCTION__));      
  }
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }
  
  /* Create a timer to read ChargerPD Buffer */     
  Status = gBS->CreateEvent(                
        EVT_TIMER | EVT_NOTIFY_SIGNAL,
        TPL_CALLBACK,
        ReadChargerpdLogs,
        NULL,                
        &ReadChargerpdEvt
        );      
  
  if(EFI_ERROR(Status))    
  {        
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a CreateEvent Failed \r\n", __FUNCTION__));
    return Status;      
  }    

  /* Set the polling period for reading chargerPD periodic event */      
  Status = gBS->SetTimer(                 
          ReadChargerpdEvt,                 
          TimerPeriodic,                
          EFI_TIMER_PERIOD_SECONDS(gChargerPlatformCfgData.ChargerPDLoggingCfgData.LoggingIntervalInSec)
          );

  if(EFI_ERROR(Status))    
  {    
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a event SetTimer Failed \r\n", __FUNCTION__));     
    return Status;    
  }

  gBS->SignalEvent(ReadChargerpdEvt);     

  CHARGER_DEBUG((EFI_D_INFO, "QcomChargerDxe:: %a Timer Event is created\r\n", __FUNCTION__)); 

  return Status;
}


VOID 
EFIAPI 
ReadChargerpdLogs(
    IN EFI_EVENT Event,
    IN VOID        *Context
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  STATIC BOOLEAN init_flag=TRUE;
  //To allow fetching chargerfw init logs only once
  if(init_flag==TRUE){
    Status = ChargerLib_CpdlogGetInitBuffer();
    init_flag=FALSE;
  }
  else{
    Status = ChargerLib_CpdlogGetBuffer(gChargerPlatformCfgData.ChargerPDLoggingCfgData.MaxLogSize);
  }
  if(gChargerPlatformCfgData.ChargerPDLoggingCfgData.EnableQBGDump)
    Status |= ChargerLib_CpdlogGetQbgDump();
  if(Status == EFI_INVALID_PARAMETER)    
  {        
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a ChargerPD log size set is invalid \r\n", __FUNCTION__));      
  }
}


EFI_STATUS ChargerPlatform_CpdlogTimer_Exit( VOID ){
  
  EFI_STATUS  Status = EFI_SUCCESS;
  
  if(ReadChargerpdEvt != NULL){

    // If logging categories read from SDAM is a valid number, set that value back in ChargerFw.
    if(LoggingCategories==0){
      // If log categories read from SDAM is 0, set it to 0x1FFFFFFFF in ChargerFw for complete logs when boot to hlos. This overwrites selfhost log category (set by uefi) in SDAM.
      LoggingCategories = LoggingCategoriesMax; 
    }
    Status = ChargerLib_CpdlogSetProperties(LoggingCategories, gChargerPlatformCfgData.ChargerPDLoggingCfgData.LogLevel);
    if(Status == EFI_SUCCESS)    
    {        
      CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a ChargerPD logging categories set to %ld \r\n", __FUNCTION__, LoggingCategories));      
    }
    
    Status |= gBS->CloseEvent (ReadChargerpdEvt);
    
    if(Status==EFI_SUCCESS)
      CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Timer Event Exit Success\r\n", __FUNCTION__));
  }
  
  return Status;
}


EFI_STATUS ChargerPlatform_Exit( VOID ){
  
  EFI_STATUS Status = EFI_SUCCESS;
  
  Status = ChargerLib_Exit();
  Status |= ChargerPlatform_CpdlogTimer_Exit();

  return Status;
}

STATIC EFI_STATUS IsChargingSupported(VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_QCOM_PMIC_VERSION_PROTOCOL *PmicVersionProtocol = NULL;
  EFI_QCOM_PMIC_SCHG_PROTOCOL	*PmicSchgProtocol  = NULL;
  EFI_PM_DEVICE_INFO_TYPE        PmicDeviceInfo;
  EFI_PM_SCHG_PMIC_INFO          PmicInfo;
  EFI_PLATFORMINFO_PLATFORM_TYPE    PlatformType;
  EFI_ADC_PROTOCOL  *AdcProtocol  = NULL;
  //  UINT8 ChgPmicIndex = 0x00;

  Status = gBS->LocateProtocol(&gEfiAdcProtocolGuid, NULL, (VOID**) &AdcProtocol);
  if(EFI_SUCCESS != Status || !AdcProtocol)
  {
      CHARGER_DEBUG(( EFI_D_ERROR, "%a Cannot locate AdcProtocol: %r \r\n", __FUNCTION__, Status));
      return EFI_UNSUPPORTED;
  }

  Status = gBS->LocateProtocol(&gQcomPmicSchgProtocolGuid, NULL, (VOID **)&PmicSchgProtocol);
  if(EFI_SUCCESS != Status || !PmicSchgProtocol)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "%a Cannot locate PmicSchgProtocol: %r \r\n", __FUNCTION__, Status));
    return EFI_UNSUPPORTED;
  }

  Status = GetPlatformType(&PlatformType); 
  if(EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG((EFI_D_ERROR, " %a Error getting platform type  \r\n", __FUNCTION__));
    return Status;
  }
  if((EFI_PLATFORMINFO_TYPE_RUMI == PlatformType))
  {
      CHARGER_DEBUG((EFI_D_ERROR, " %a RUMI platform detected \r\n", __FUNCTION__));
      return EFI_UNSUPPORTED;
  }
  
  Status = gBS->LocateProtocol(&gQcomPmicVersionProtocolGuid, NULL, (VOID **)&PmicVersionProtocol);
  if(EFI_SUCCESS != Status || !PmicVersionProtocol)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "%a Cannot locate PmicVersionProtocol: %r \r\n", __FUNCTION__, Status));
    return EFI_UNSUPPORTED;
  }
  
  /*
  Status = PmicSchgProtocol->SchgGetChargerPmicIndex(&ChgPmicIndex);
  if(EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "%a Invalid Charger index: %d %r \r\n", __FUNCTION__, ChgPmicIndex,Status));
    return EFI_UNSUPPORTED;
    }
  */

  Status = PmicSchgProtocol->SchgGetPmicInfo(&PmicInfo);
  if(EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "%a Invalid Charger index: %d %r \r\n", __FUNCTION__, PmicInfo.PmicIndex,Status));
    return EFI_UNSUPPORTED;
  }
  
  Status = PmicVersionProtocol->GetPmicInfo(PmicInfo.PmicIndex, &PmicDeviceInfo);
  if(EFI_SUCCESS != Status)
  {
	CHARGER_DEBUG(( EFI_D_WARN, "%a GetPmicInfo failed!: %r \r\n", __FUNCTION__, Status));  
	return EFI_UNSUPPORTED;
  }

  if((EFI_PMIC_IS_INVALID == PmicDeviceInfo.PmicModel) || (EFI_PMIC_IS_UNKNOWN == PmicDeviceInfo.PmicModel))
  {
	Status = EFI_UNSUPPORTED;
	CHARGER_DEBUG(( EFI_D_WARN, "%a Charging is not supported on this Platform for PMIC Model: %d Pmic Index: %d%r \r\n", __FUNCTION__, PmicDeviceInfo.PmicModel, PmicInfo.PmicIndex, Status));
	return Status;
  }
  return Status;
}

