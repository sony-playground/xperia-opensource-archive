/** @file ChargerLibTarget.c

  Provide access to Charger Libraries

  Copyright (c) 2019-2022, Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when         who     what, where, why
 --------     ---     ---------------------------------------------------------
05/20/19      mr      Added support to move display functionality from Chargerlib to ChargerApp
03/05/2019    pbitra  Fixed die temp values and channel passed to ADC
01/12/2019    vr      Fix issue where charging is disabled in unknown battery cases
01/12/2019    vr      Moved HW Jeita config to PmicDxe after batt therm (from profile) is read
06/29/2018    dc      Support USB Charger Type Logging
06/29/2018    dc      Support Input Current Status API & Log
06/13/2018    cs      need to also set CBLPWR to edge trigger to avoid device reboot with usb inserted
05/14/2018    ra      Support for Debug Accessory Mode
03/26/2018    va      Initial revision
=============================================================================*/

/*===========================================================================*/
/*                  INCLUDE FILES                                            */
/*===========================================================================*/
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomLib.h>
#include "Library/SerialPortShLib.h"
#include <Library/QcomTargetLib.h>
#include <api/pmic/pm/pm_uefi.h>
#include <Library/QcomBaseLib.h>
#include <PrintShLib.h>
#include <Library/UefiCfgLib.h>

#include <Library/BaseMemoryLib.h>
#include "string.h"

#include <api/pmic/charger/ChargerLibCommon.h>
#include "../Library/ChargerLib/ChargerLibTarget.h"

#include <api/pmic/pm/pm_sdam.h>
#include <api/pmic/pm/pm_chg.h>

/**
  Protocol Dependencies
*/
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIPmicFg.h>
#include <Protocol/EFIPmicSchg.h>
//#include <Protocol/EFIPmicUsb.h>
#include <Protocol/EFIPmicVersion.h>
#include <Protocol/EFIPmicPwrOn.h>
#include <Protocol/EFIVariableServices.h>
#include <Protocol/EFITsens.h>
#include <Protocol/EFIPmicRTC.h>
#include <Protocol/EFIUsbfnChgSrv.h>
#include <Protocol/EFIPmicRgbLed.h>
#include <Protocol/EFIUsbInitProtocol.h>
#include <Protocol/EFIUsbPwrCtrl.h>

#include <Protocol/EFIPIL.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPmicSdam.h>

/*===========================================================================*/
/*                  TYPEDEF AND MACRO DEFINITIONS                            */
/*===========================================================================*/
#define BATTERY_EMULATOR_UPPER_THRSHOLD_MV  4450
#define BATTERY_EMULATOR_LOWER_THRSHOLD_MV  3450
#define BATTERY_EMULATOR_BATT_ID            1500
#define BATTERY_EMULATOR_TEMP_C             23
#define BATTERY_EMULATOR_SOC                99

#ifdef FEATURE_XBOOT
#define VBATT_TOLERANCE                     45 //Battery upper voltage tolerance limit.
#else  /* !FEATURE_XBOOT */
#define VBATT_TOLERANCE                     5 //Battery upper voltage tolerance limit.
#endif /* !FEATURE_XBOOT */

#define UNKNOWN_BATT_SHUTDOWN               0
#define UNKNOWN_BATT_BOOT_TO_HLOS           1
#define UNKNOWN_BATT_CONSERVATIVE_CHARGING  2
#define UNKNOWN_BATT_REGULAR_CHARGING       3

#define DEBUG_BOARD_LOWVBAT_SHUTDOWN        0
#define DEBUG_BOARD_LOWVBAT_NOCHARGE        1
#define DEBUG_BOARD_BOOT_TO_HLOS            2

#define CHARGER_COOL_OFF_PERIOD_DEFAULT     300000 //5minutes=1000millisec*60*5=300000 milli sec
#define BOOT_THRESHOLD_VOLT                 3600

#define TWO_SECONDS                         2000000 /*2seconds = 2000000 uSec*/

#define FIVE_SEC_IN_MILLI_SEC               5000
#define TIMEOUT_WAIT_FOR_KEY                0x01

#define MAX_3000_MA                         3000
#define MAX_1500_MA                         1500

#define THERMAL_TIMEOUT_NOTSET              0
#define MIN_TO_SEC                          60

#define MAX_THERMAL_WAIT_PERIOD_IN_MINS     60

#define USB_3_IUSB_MAX                      900 //IUSB_MAX for USB 3.0 port
#define USB_2_IUSB_MAX                      500 //IUSB_MAX for USB 2.0 port
#define FCC_CONSERVE_CHG                    500
#define USB_ENUM_WAIT_DURATION              500 /*500 milliseconds*/

#define MAX_EMERGENCY_SHUTDOWN_COUNT        3

#define THERMAL_TIMEOUT_NOTSET              0
#define MIN_TO_SEC                          60

#define MAX_THERMAL_WAIT_PERIOD_IN_MINS     60

#define MAX_MSG_LENGTH                      251
#define CPDLOG_READ_MAX_BUFFER_SIZE         8192
#define MAX_QBG_DUMP_SIZE                   612

#define MAX_VBUS_MISSING_COUNT              3

#define QBG_AGED_SDAM_TIME_DURATION_S 1800 //30min
#define QBG_SDAM_C0_BATTERY_ID_LSB                5
#define QBG_SDAM_C0_BATTERY_ID_MSB                6
#define QBG_SDAM_C0_PREV_RTC_0                   47
#define QBG_SDAM_C0_PREV_RTC_1                   48
#define QBG_SDAM_C0_PREV_RTC_2                   49
#define QBG_SDAM_C0_PREV_RTC_3                   50
#define QBG_SDAM_C0_BAT_THERM_LSB                51
#define QBG_SDAM_C0_BAT_THERM_MSB                52
#define QBG_SDAM_C0_OCV_LSB                      53
#define QBG_SDAM_C0_OCV_MSB                      54
#define QBG_SDAM_C0_AGG_MSOC_LSB                 55
#define QBG_SDAM_C0_AGG_MSOC_MSB                 56
#define QBG_SDAM_C1_OCV_LSB                      112
#define QBG_SDAM_C1_OCV_MSB                      113

/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES                                     */
/*===========================================================================*/
void ChargerLibTarget_HWInit(chargerlib_cfgdata_type *pChargerLibConfig);
EFI_STATUS ChargerLibTarget_ConfigureUsbCurrentSetting( VOID );
EFI_STATUS ChargerLibTarget_PrintDCInStatus();
EFI_STATUS ChargerLibTarget_GetBatteryType(ChgBattType *pBatteryType);
EFI_STATUS ChargerLibTarget_GetUsbcPortType(CHARGERLIB_CHG_USBC_SINK_TYPE *pUsbcPortType);

/*===========================================================================*/
/*                  LOCAL VARIABLE DECLARATIONS                              */
/*===========================================================================*/
STATIC EFI_QCOM_PMIC_SCHG_PROTOCOL          *PmicSchgProtocol  = NULL;
STATIC EFI_QCOM_PMIC_FG_BASIC_PROTOCOL      *PmicFgProtocol    = NULL;
STATIC EFI_ADC_PROTOCOL                     *AdcProtocol       = NULL;
STATIC EFI_USBFN_CHG_SRV_PROTOCOL           *UsbChgSrvProtocol = NULL;
STATIC EFI_USB_INIT_PROTOCOL                *UsbInitProtocol = NULL;
STATIC EFI_PMIC_GLINK_PROTOCOL              *pmicGlinkProtocol = NULL;
STATIC EFI_CHIPINFO_PROTOCOL                *pChipInfoProtocol  = NULL;
extern EFI_QCOM_PMIC_PWRON_PROTOCOL         *PmicPwronProtocol;
STATIC EFI_QCOM_PMIC_SDAM_PROTOCOL          *sdam_protocol = NULL;
STATIC EFI_QCOM_PMIC_RTC_PROTOCOL           *pPmicRtc = NULL;

EFI_BATTERY_CHARGER_INFO_TYPE           ChargerInfo = {0};
EFI_BATTERY_GAUGE_INFO_TYPE             BatteryGaugeInfo = {0};
chargerlib_cfgdata_type                 gChargerLibTargetCfgData = {0};


extern EFI_GUID gQcomPmicPwrOnProtocolGuid;
extern EFI_GUID gQcomPmicUsbProtocolGuid;
extern BOOLEAN gIs_2S_Battery;
//extern EFI_GUID gEfiUsbfnChgSrvProtocolGuid;

STATIC EFI_PLATFORMINFO_PLATFORM_TYPE  PlatformType;
STATIC BOOLEAN                         gChargingEnabled = FALSE;
STATIC BOOLEAN                         gStartControllerCalled = FALSE;
STATIC BOOLEAN                         gProfileLoadCalled = FALSE;

STATIC CHARGERLIB_EVENT_DISP_IMAGE_TYPE gDispImage = CHARGERLIB_EVENT_DISP_IMAGE_NONE;

STATIC CONST CHARGERLIB_HW_CONFIG_INFO ChargerLibHwConfigTable[CHARGERLIB_PLATFORM_HW_CONFIG_MAX]= {
  {EfiBatteryChargerNone,         0x00010000, EfiBatteryGaugeNone,       0x00010000}, //NONE
  {EfiBatteryChargerQcomPmicSchg, 0x00010000, EfiBatteryGaugeQcomPmicFg, 0x00010000}, //PMIC
};

STATIC CONST CHARGERLIB_PLATFORM_HW_CONFIG_INFO ChargerLibPlatformHwInfo[]=
{
  {EFI_PLATFORMINFO_TYPE_MTP,     NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_PMIC},
  {EFI_PLATFORMINFO_TYPE_FLUID,   NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_PMIC},
  {EFI_PLATFORMINFO_TYPE_QRD,     NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_PMIC},
  {EFI_PLATFORMINFO_TYPE_HDK,     NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_PMIC},
  {EFI_PLATFORMINFO_TYPE_CHI,     NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_PMIC},
  {EFI_PLATFORMINFO_TYPE_SBC,     NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_PMIC},
  {EFI_PLATFORMINFO_TYPE_LIQUID,  NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_PMIC},
  {EFI_PLATFORMINFO_TYPE_RUMI,    NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_NONE},
  {EFI_PLATFORMINFO_TYPE_CDP,     NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_NONE},
  {EFI_PLATFORMINFO_TYPE_CLS,     NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_NONE},
  {EFI_PLATFORMINFO_TYPE_ATP,     NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_PMIC},
  {EFI_PLATFORMINFO_TYPE_IDP,     NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_PMIC},
  {EFI_PLATFORMINFO_TYPE_RCM,     NULL,   CHARGERLIB_PLATFORM_HW_CONFIG_NONE},
};

STATIC UINT32 BatteryIndex = 0;

extern BOOLEAN gEnableChargerFW;
extern pm_chg_info_type gChargerSharedInfo;

#define CHARGERLIB_IPC_MAX_LINK_WAIT_COUNT    20//200

#define CHARGERLIB_IPC_LINK_WAIT_TIME         1000 * 1000//1000 //100 MSEC   

STATIC UINT32 BatteryID = 0;
STATIC BOOLEAN FirstBatteryIDRead = TRUE;

/*===========================================================================*/
/*                 FUNCTION DEFINITIONS                                      */
/*===========================================================================*/
/**
  Initialize ChargerLib Target functon Library functions

  @param none

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_INVALID_PARAMETER: A Parameter was incorrect.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_NOT_READY:         The physical device is busy or not ready to
                         process this request.
*/
EFI_STATUS ChargerLibTarget_Init( chargerlib_cfgdata_type *pChargerLibTargetConfig )
{
  EFI_STATUS                  Status         = EFI_SUCCESS;
  BOOLEAN                     bDbgBoard = FALSE;

  CopyMemS(&gChargerLibTargetCfgData, sizeof(chargerlib_cfgdata_type), pChargerLibTargetConfig , sizeof(chargerlib_cfgdata_type));

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  /* Enable USB and DCIN PON triggers to be certain and avoid bad use case*/
  Status = ChargerLibTarget_SetPon1Trigger(EFI_PM_PON_OPTION_DC_CHG_REDGE_PON, FALSE);
  Status |= ChargerLibTarget_SetPon1Trigger(EFI_PM_PON_OPTION_USB_CHG_REDGE_PON, FALSE);

  if(Status != EFI_SUCCESS)
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Error locating Pwron Protocol = %r \r\n", __FUNCTION__, Status));
  }

  ChargerLibTarget_HWInit(pChargerLibTargetConfig);

  switch (BatteryGaugeInfo.BatteryGaugeHW)
  {
    /* Remove FG Protocol, will need to add Qbg Protocol later */
    case EfiBatteryGaugeQcomPmicFg:
      // Locate FG Protocol
      if (!PmicFgProtocol)
      {
        Status |= gBS->LocateProtocol( &gQcomPmicFgProtocolGuid,
                                      NULL,
                                     (VOID **)&PmicFgProtocol );
      }

      // Initialize FG Protocol
      if((EFI_SUCCESS == Status ) && ( NULL != PmicFgProtocol))
      {
        Status |= PmicFgProtocol->FgBasicGetPmicInfo(&BatteryGaugeInfo.BatteryGaugePmicInfo);
        if(EFI_SUCCESS != Status)
        {
          CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Failed to get PmicIndex for Fuel Gauge : 0x%08X \r\n", __FUNCTION__, Status));
          return Status;
        }

        gChargerLibTargetCfgData.fg_cfg_data.FgDbgCfg =  *(EFI_PM_FG_DEBUG_CFGDATA_TYPE *)&gChargerLibTargetCfgData.dbg_cfg_Data;

        Status |= PmicFgProtocol->FgBasicInit(BatteryGaugeInfo.BatteryGaugePmicInfo.PmicIndex,
                                              &gChargerLibTargetCfgData.fg_cfg_data);
        if(EFI_SUCCESS != Status)
        {
          CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Failed to initialize Fuel Gauge: 0x%08X  \r\n", __FUNCTION__, Status));
          return Status;
        }
      }
      break;
    case EfiBatteryGaugeNone:
		break;

    default:
      Status = EFI_UNSUPPORTED;
      break;

  }

  /* Initialize Charger and Gauge HW */
  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      /* Locate SCHG Protocol */
      if (!PmicSchgProtocol)
      {
        Status |= gBS->LocateProtocol( &gQcomPmicSchgProtocolGuid,
                                       NULL,
                                      (VOID **)&PmicSchgProtocol );
      }

      if ((EFI_SUCCESS == Status) && (NULL != PmicSchgProtocol))
      {
          Status = PmicSchgProtocol->SchgGetPmicInfo(&ChargerInfo.ChargerPmicInfo);
          if (EFI_SUCCESS != Status)
          {
              CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Failed to get PmicIndex for SCHG : 0x%08X \r\n", __FUNCTION__, Status));
              return Status;
          }

          gChargerLibTargetCfgData.schg_cfg_data.SchgDbgCfg = *(EFI_PM_SCHG_DEBUG_CFGDATA_TYPE *)&gChargerLibTargetCfgData.dbg_cfg_Data;

          /* Initialize SCHG Protocol */
          /* SchgInit does not use dDbgBoard info. Hence leaving bDbgBoard to FALSE */
          Status = PmicSchgProtocol->SchgInit(ChargerInfo.ChargerPmicInfo.PmicIndex, gChargerLibTargetCfgData.schg_cfg_data, bDbgBoard);
          if (EFI_SUCCESS != Status)
          {
              CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Failed to initialize SCHG : 0x%08X \r\n", __FUNCTION__, Status));
          }
      }
      break;

	case EfiBatteryChargerNone:
		break;

    default:
      Status = EFI_UNSUPPORTED;
      break;
  }
  
  /* Locate Glink Protocol */
  if(NULL == pmicGlinkProtocol)
  {
    Status = gBS->LocateProtocol (&gpmicGlinkProtocolGuid,NULL, (VOID **) &pmicGlinkProtocol);
    if((EFI_SUCCESS != Status) || (NULL == pmicGlinkProtocol))
    {
      CHARGER_DEBUG(( EFI_D_ERROR, "ChargerLib:: %a pmicGlinkProtocol Failed %r \r\n", __FUNCTION__, Status));
    }
  }
  Status |= ChargerLibTarget_SetOS(OS_HLOS);
  return Status;
}

BOOLEAN ChargerLibTarget_RtcTimePassedDuration(UINT32 curr_time, UINT32 prev_time, UINT32 duration)
{
	BOOLEAN passed = FALSE;

	if(curr_time >= prev_time)
	{
		if((curr_time - prev_time) >= duration)
		{
			passed = TRUE;
		}
	}
	else // system time wraps around to 0 when it exceeds the maximum value. curr_time could be smaller than prev_time
	{
		if((curr_time < prev_time)&& (curr_time + (UINT32)(~(UINT32)(0) - prev_time + 1) >= duration))
		{
			passed = TRUE;
		}
	}
	return passed;
}

EFI_STATUS ChargerLibTarget_ValidateAndGetOcv(UINT32 *ocv, UINT32 *soc, INT32 tbat)
{

  EFI_STATUS Status = EFI_SUCCESS;
  BOOLEAN id_matched = FALSE, b_sdam_outdated = FALSE, b_ocv_increase_100mv = FALSE, b_batt_therm_cold_to_warm = FALSE;
  BOOLEAN pon_reset = FALSE;
  UINT32 batt_id_diff = 0;
  INT32 batt_therm = 0, jeita_cold_10mdeg = 10;
  INT32                        actual_batt_id = 0;
  UINT32                       current_rtc_time = 0;
  INT32                        sdam_batt_id = 0;
  UINT32                       sdam_rtc_time = 0;
  UINT32                       sdam_ocv = 0, sdam_ocv_cell0 = 0, sdam_ocv_cell1 = 0;
  UINT32                       sdam_msoc = 0;
  UINT8                        sdam_batt_therm = 0;
  INT32                        pon_ocv = *ocv;
  UINT32                       sdam_pmic_index = 0;
  UINT32                       sdam_index = 0;
	//get pon_ocv
	DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: pon_ocv = %d \r\n", pon_ocv));

	//get batt_id
	Status = ChargerLibTarget_GetBatteryID(&actual_batt_id);

	if(EFI_SUCCESS != Status)
	{
		return Status;
	}
	DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: actual_batt_id = %d \r\n", actual_batt_id));

	//get rtc time
	if(!pPmicRtc)
	{
		Status = gBS->LocateProtocol( &gQcomPmicRtcProtocolGuid,
				NULL,
				(VOID**) &pPmicRtc);
		if (Status != EFI_SUCCESS || NULL == pPmicRtc) {
			DEBUG(( EFI_D_ERROR, "ChargerLibTarget_ValidateAndGetOcv: ERROR, gQcomPmicRtcProtocolGuid not found!\r\n"));
			return Status;
		}
	}

	Status |= pPmicRtc->GetTimeValueRaw(0, &current_rtc_time);
	DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: current_rtc_time = %d \r\n", current_rtc_time));

	//locate sdam protocol
	if(!sdam_protocol)
	{
		Status = gBS->LocateProtocol(&gQcomPmicSdamProtocolGuid, NULL, (void**)&sdam_protocol);
		if(Status != EFI_SUCCESS || NULL == sdam_protocol)
		{

			DEBUG(( EFI_D_ERROR, "ChargerLibTarget_ValidateAndGetOcv: ERROR, PMIC SDAM protocol not found!\r\n"));
			return EFI_DEVICE_ERROR;
		}
	}
	
    //locate pmic fg protocol
	if(!PmicFgProtocol)
	{
		Status = gBS->LocateProtocol(&gQcomPmicFgProtocolGuid, NULL, (void**)&PmicFgProtocol);
		if(Status != EFI_SUCCESS || NULL == PmicFgProtocol)
		{

			DEBUG(( EFI_D_ERROR, "ChargerLibTarget_ValidateAndGetOcv: ERROR, PMIC FG protocol not found!\r\n"));
			return EFI_DEVICE_ERROR;
		}
	}

    Status |= PmicFgProtocol->FGGetPmicGaugeSDAMInfo(&sdam_pmic_index, &sdam_index);
    if(EFI_SUCCESS != Status)
    {
        DEBUG(( EFI_D_ERROR, "ChargerLib:: %a Failed to get SDAM info for Fuel Gauge : 0x%08X \r\n", __FUNCTION__, Status));
        return Status;
    }
	DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: SDAM Pmic index = %d SDAM index: %d \r\n", sdam_pmic_index, sdam_index));
    
    //get sdam_batt_id
	Status = sdam_protocol->SdamMemRead(sdam_pmic_index, sdam_index, QBG_SDAM_C0_BATTERY_ID_LSB, 2, (UINT8 *)&sdam_batt_id);
	sdam_batt_id <<= 4;
	if(Status != EFI_SUCCESS)
	{
		sdam_batt_id = 0;
		DEBUG(( EFI_D_ERROR, "read sdam_batt_id failed \r\n"));
	}
	DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: sdam_batt_id = %d \r\n", sdam_batt_id));

	//get sdam rtc time
	Status = sdam_protocol->SdamMemRead(sdam_pmic_index, sdam_index, QBG_SDAM_C0_PREV_RTC_0, 4, (UINT8 *)&sdam_rtc_time);
	if(Status != EFI_SUCCESS)
	{
		sdam_rtc_time = 0;
		DEBUG(( EFI_D_ERROR, "ChargerLibTarget_ValidateAndGetOcv: read sdam_rtc_time failed \r\n"));
	}
	DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: sdam_rtc_time = %d \r\n", sdam_rtc_time));

	//get sdam batt_therm
	Status = sdam_protocol->SdamMemRead(sdam_pmic_index, sdam_index, QBG_SDAM_C0_BAT_THERM_LSB, 2, &sdam_batt_therm);
	DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: sdam_batt_therm =%d C\r\n", sdam_batt_therm));

	//get sdam ocv for cell0
	Status = sdam_protocol->SdamMemRead(sdam_pmic_index, sdam_index, QBG_SDAM_C0_OCV_LSB, 2, (UINT8 *)&sdam_ocv_cell0);
	if(Status != EFI_SUCCESS)
	{
		sdam_ocv_cell0 = 0;
		DEBUG(( EFI_D_ERROR, "ChargerLibTarget_ValidateAndGetOcv: read sdam_ocv_cell0 failed \r\n"));
	}
	DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: sdam_ocv_cell0 = %d \r\n", sdam_ocv_cell0));	

	sdam_ocv_cell0 <<= 16;//10nV
	sdam_ocv_cell0 /= 100;//uV
	sdam_ocv_cell0 /= 1000;//mV
	DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: sdam_ocv_cell0 = %d mV \r\n", sdam_ocv_cell0));

    //get sdam ocv for cell1
    if(gIs_2S_Battery)
    {
	  Status = sdam_protocol->SdamMemRead(sdam_pmic_index, sdam_index, QBG_SDAM_C1_OCV_LSB, 2, (UINT8 *)&sdam_ocv_cell1);
	  if(Status != EFI_SUCCESS)
	  {
		  sdam_ocv_cell1 = 0;
		  DEBUG(( EFI_D_ERROR, "ChargerLibTarget_ValidateAndGetOcv: read sdam_ocv_cell1 failed \r\n"));
	  }
	  DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: sdam_ocv_cell1 = %d \r\n", sdam_ocv_cell1));

	  sdam_ocv_cell1 <<= 16;//10nV
	  sdam_ocv_cell1 /= 100;//uV
	  sdam_ocv_cell1 /= 1000;//mV
	  DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: sdam_ocv_cell1 = %d mV \r\n", sdam_ocv_cell1));
    }

    sdam_ocv = sdam_ocv_cell0 + sdam_ocv_cell1;
    DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: sdam_ocv = %d mV \r\n", sdam_ocv));

	//get sdam msoc
	Status = sdam_protocol->SdamMemRead(sdam_pmic_index, sdam_index, QBG_SDAM_C0_AGG_MSOC_LSB, 2, (UINT8 *)&sdam_msoc);
	if(Status != EFI_SUCCESS)
	{
		sdam_msoc = 0;
		DEBUG(( EFI_D_ERROR, "ChargerLibTarget_ValidateAndGetOcv: read sdam_msoc failed \r\n"));
	}
	sdam_msoc <<= 16;//10n
	sdam_msoc /= 10000;
	sdam_msoc /= 100;

    DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: sdam_msoc = %d\r\n", sdam_msoc));

    //check if actual_batt_id is within the range of sdam_batt_id +/- 6%
    batt_id_diff = (actual_batt_id > sdam_batt_id) ? (actual_batt_id - sdam_batt_id) : (sdam_batt_id - actual_batt_id);
    id_matched = (batt_id_diff * 100 / sdam_batt_id <= 6) ? TRUE : FALSE;

	if(current_rtc_time < 10 || sdam_batt_id == 0 || sdam_ocv == 0 || sdam_rtc_time == 0 || sdam_batt_therm == 0)
	{
		pon_reset = TRUE;
		DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: pon reset\r\n"));
	}
	else if(id_matched)
    {
        //get batt therm from adc
		batt_therm = tbat;

        b_sdam_outdated = ChargerLibTarget_RtcTimePassedDuration(current_rtc_time, sdam_rtc_time, QBG_AGED_SDAM_TIME_DURATION_S);

        b_ocv_increase_100mv = (pon_ocv > sdam_ocv + 100) ? TRUE : FALSE;

		b_batt_therm_cold_to_warm = ((sdam_batt_therm < jeita_cold_10mdeg) && (batt_therm > (jeita_cold_10mdeg + 10))) ? TRUE : FALSE;

		DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: b_sdam_outdated = %d, rtc_time = %d s, prev_rtc_time = %d\r\n", b_sdam_outdated, current_rtc_time, sdam_rtc_time));
		DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: b_ocv_increase_100mv = %d, pon_ocv = %d mV, sdam_ocv = %d mV\r\n", b_ocv_increase_100mv, pon_ocv, sdam_ocv));
		DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: b_batt_therm_cold_to_warm = %d, batt_temp = %d C, sdam_batt_therm = %d C \r\n", b_batt_therm_cold_to_warm, batt_therm, sdam_batt_therm));
	}

    //discard short term data if:
    // (1) sdam age is over 30min OR
    // (2) previous therm < 10C and now therm > 20C also ocv increases by 100mV
    if (pon_reset || !id_matched || b_sdam_outdated || (b_ocv_increase_100mv && b_batt_therm_cold_to_warm))
	{
		*ocv = pon_ocv;
		if(*ocv < gChargerLibTargetCfgData.boot_to_hlos_threshold_in_mv)
			*soc = gChargerLibTargetCfgData.boot_to_hlos_threshold_in_soc - 1;
		DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: re-estimate using pon_ocv == %d mV, set soc=%d \r\n", pon_ocv, *soc));
	}
    else
    {
		*ocv = sdam_ocv;
		*soc = sdam_msoc;
		DEBUG(( EFI_D_INFO, "ChargerLibTarget_ValidateAndGetOcv: using sdam_ocv == %d mV, sdam_soc=%d \r\n", sdam_ocv, sdam_msoc));
    }

    return Status;
}

/**
  Get Battery Status Information
  @param[out] BattStatusInfo  refer EFI_PM_FG_BATT_STATUS_INFO
  This function gets the battery status, battery SOC, Charge current, battery voltage
  and battery temperature from Fuel Gauge

  @param[out] BatteryStatus  see chargerlib_batt_status_info for more details

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_GetBatteryStatus(chargerlib_batt_status_info *pBatteryStatus)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_GLINK_LINK_STATUS      PmicGLinkStatus = { 0 };
  EFI_PM_FG_BATT_STATUS_INFO BatteryStatus = {0};
  EFI_PM_GLINK_BATT_STATUS_INFO BattStsInfo = { 0 };
  EfiAdcResultType AdcResult = { 0 };
  UINT32                       ocv = 0;
  static BOOLEAN                      first_get_ocv = FALSE;

  if(NULL == pBatteryStatus)
  {
    return EFI_INVALID_PARAMETER;
  }

  if ((EFI_SUCCESS == ChargerLibTarget_GetIPCStatus(&PmicGLinkStatus)) && (PmicGLinkStatus.IsPMICChannelOpen == TRUE))
  {
  		CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a use PmicGlink \r\n",__FUNCTION__));
		Status = pmicGlinkProtocol->GetBatteryStatus(BatteryIndex, &BattStsInfo);
		if(EFI_SUCCESS != Status)
		{
			CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Status: %r \r\n",__FUNCTION__, Status));
			return EFI_DEVICE_ERROR;
		}
		else
		{
			pBatteryStatus->StateOfCharge = BattStsInfo.StateOfCharge;
			pBatteryStatus->ChargeCurrent = BattStsInfo.ChargeCurrent;
			pBatteryStatus->BatteryVoltage= BattStsInfo.BatteryVoltage;
			pBatteryStatus->BatteryTemperature = BattStsInfo.BatteryTemperature;

            Status = pmicGlinkProtocol->GetBatteryStatusExt(&ocv);
            if (Status != EFI_SUCCESS)
                return EFI_DEVICE_ERROR;
            pBatteryStatus->Ocv = ocv;
            DEBUG(( EFI_D_INFO, "ChargerLibTarget_GetBatteryStatus: ocv = %d mv\r\n", ocv));
		}
  }
  else
  {
	  switch (BatteryGaugeInfo.BatteryGaugeHW)
	  {
	    case EfiBatteryGaugeQcomPmicFg:
			CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a use PmicFgProtocol \r\n",__FUNCTION__));
        if (!PmicFgProtocol)
        {
          Status |= gBS->LocateProtocol( &gQcomPmicFgProtocolGuid,
                                      NULL,
                                     (VOID **)&PmicFgProtocol );
          if(Status != EFI_SUCCESS || NULL == PmicFgProtocol)
            return EFI_DEVICE_ERROR;
        }

        Status = PmicFgProtocol->GetBatteryStatus(BatteryGaugeInfo.BatteryGaugePmicInfo.PmicIndex,
                                                    (EFI_PM_FG_BATT_STATUS_INFO *)&BatteryStatus);

        if(EFI_SUCCESS == Status)
        {
            ChgBattType BatteryType = CHG_BATT_TYPE_INVALID;
            Status = ChargerLibTarget_GetBatteryType(&BatteryType);
            if(Status != EFI_SUCCESS) 
                return EFI_DEVICE_ERROR;
            
            if(BatteryType == CHG_BATT_TYPE_DEBUG_BOARD)
            {
                BatteryStatus.BatteryTemperature = 25;
                if(BatteryStatus.Ocv < gChargerLibTargetCfgData.boot_to_hlos_threshold_in_mv && gIs_2S_Battery)
                {
                  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a 2S debug board, invalid OCV, set to 8V \r\n",__FUNCTION__));
                  BatteryStatus.Ocv = 8000;
                }
                  
            }
            else
            {
                Status = ChargerLibTarget_GetADCReading(ADC_INPUT_BATT_THERM , sizeof(ADC_INPUT_BATT_THERM ), &AdcResult);
                
                BatteryStatus.BatteryTemperature = AdcResult.nPhysical;         

                if(!first_get_ocv){
                    ChargerLibTarget_ValidateAndGetOcv(&(BatteryStatus.Ocv), &(BatteryStatus.StateOfCharge), BatteryStatus.BatteryTemperature);
                    first_get_ocv = TRUE;
                }
                else{
                    //for now, just use 100 mOhm as rbatt since this is an edge case.
                    BatteryStatus.Ocv = BatteryStatus.BatteryVoltage + BatteryStatus.ChargeCurrent * 100 / 1000;

                    if(BatteryStatus.Ocv < gChargerLibTargetCfgData.boot_to_hlos_threshold_in_mv)
                    {
                        BatteryStatus.StateOfCharge = gChargerLibTargetCfgData.boot_to_hlos_threshold_in_soc - 1;
                    }
                    else
                    {
                        //in recovery mode, will have to use this workaround, cannot get soc.
                        BatteryStatus.StateOfCharge = gChargerLibTargetCfgData.boot_to_hlos_threshold_in_soc + 1;
                    }
                }
            }

            if (sizeof(chargerlib_batt_status_info) >= sizeof(EFI_PM_FG_BATT_STATUS_INFO))
            {
#if defined(FEATURE_FAKE_DBI)
                STATIC INT32  BatteryVoltage = 3000;
                DEBUG((EFI_D_ERROR, "%a: %d: BatteryStatus.BatteryVoltage=%d -> %d\n", __func__, __LINE__, BatteryStatus.BatteryVoltage, BatteryVoltage));
                BatteryStatus.BatteryVoltage = BatteryVoltage;
                BatteryVoltage += 5;
#endif /* defined(FEATURE_FAKE_DBI) */
                CopyMemS(pBatteryStatus, sizeof(chargerlib_batt_status_info), &BatteryStatus, sizeof(EFI_PM_FG_BATT_STATUS_INFO));                
            }
            else
            {
                Status = EFI_BAD_BUFFER_SIZE;
            }
        }

        break;

        default:
          Status = EFI_UNSUPPORTED;
          break;
       }
  }

  return Status;
}

/**
  Get Battery Status Information
  @param[out] BattStatusInfo  refer EFI_PM_FG_BATT_STATUS_INFO
  This function gets the battery status, battery SOC, Charge current, battery voltage
  and battery temperature from Fuel Gauge

  @param[out] BatteryStatus  see chargerlib_batt_status_info for more details

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_GetBatteryProfileStatus(chargerlib_batt_profile_status *ProfileSts)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(!ProfileSts)
  {
    return EFI_INVALID_PARAMETER;
  }

  switch (BatteryGaugeInfo.BatteryGaugeHW)
  {
    case EfiBatteryGaugeQcomPmicFg:
      /* Locate FG Protocol */
      if (!PmicFgProtocol)
      {
        Status |= gBS->LocateProtocol( &gQcomPmicFgProtocolGuid,
                                      NULL,
                                     (VOID **)&PmicFgProtocol );
        if(Status != EFI_SUCCESS || NULL == PmicFgProtocol)
          return EFI_DEVICE_ERROR;
      }
      Status = PmicFgProtocol->GetBattProfileStatus(BatteryGaugeInfo.BatteryGaugePmicInfo.PmicIndex,
                                                    (EFI_PM_FG_BATT_PROFILE_STATUS *)ProfileSts);
      break;
    default:
      Status = EFI_UNSUPPORTED;
      break;
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_LoadProfile(OPTIONAL chargerlib_batt_profile_data *pBattProfileInfo)
{
  EFI_STATUS Status = EFI_SUCCESS;

  switch (BatteryGaugeInfo.BatteryGaugeHW)
  {
  case EfiBatteryGaugeQcomPmicFg:
    if (!PmicFgProtocol)
    {
      Status |= gBS->LocateProtocol( &gQcomPmicFgProtocolGuid,
                                    NULL,
                                   (VOID **)&PmicFgProtocol );
    }
    /* Initialize FG Protocol */
    if((EFI_SUCCESS == Status ) && ( NULL != PmicFgProtocol))
    {
      Status |= PmicFgProtocol->FgExtendedInit(BatteryGaugeInfo.BatteryGaugePmicInfo.PmicIndex,
                                               (EFI_PM_FG_BATT_PROFILE_DATA *)pBattProfileInfo);
      if(EFI_SUCCESS != Status)
      {
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Failed to initialize Fuel Gauge: 0x%08X  \r\n", __FUNCTION__, Status));
        return Status;
      }
    }
    break;

  default:
    Status = EFI_UNSUPPORTED;
    break;
  }

  gProfileLoadCalled = TRUE;

  return Status;

}

/**
  Enable charger

  @param[in] Enable  TRUE  - Enable Charging
                     FALSE - Disable Charging

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_ChargerEnable(BOOLEAN Enable)
{
  EFI_STATUS Status = EFI_SUCCESS;
  return Status;
}

/**
  Set charger max current

  @param[in] MaxCurrent  Max current for charger in mA

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_SetMaxUsbCurrent(UINT32 MaxCurrent)
{
  EFI_STATUS Status = EFI_SUCCESS;

  return Status;
}

/**
  Set Battery FCC Max current

  @param[in] FccMaxCurrent  Max current for charger in mA

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_SetFccMaxCurrent(UINT32 FccMaxCurrent)
{
  EFI_STATUS Status = EFI_SUCCESS;

  return Status;
}

EFI_STATUS ChargerLibTarget_WasChargerReinserted(BOOLEAN *pChargerReinserted)
{
  EFI_STATUS Status = EFI_SUCCESS;
  //boolean aicl_done = FALSE;

  if(!pChargerReinserted)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pChargerReinserted = FALSE;

  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      Status = PmicSchgProtocol->ChgrSourceReinserted(ChargerInfo.ChargerPmicInfo.PmicIndex, pChargerReinserted);
      break;
    default:
      break;
  }

  if(EFI_SUCCESS == Status)
  {
    CHARGER_DEBUG((EFI_D_INFO, "ChargerLib:: %a charger reinserted\n",__FUNCTION__));
  }
  else
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Error checking Charger re-insertion status, Status: 0x%08X\n",__FUNCTION__, Status));
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_ReRunAicl( VOID )
{
  EFI_STATUS Status = EFI_SUCCESS;

  return Status;
}

/**
  Set Battery Floating Max Voltage

  @param[in] VddMaxVoltage  Max Voltage for Charger in mV

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_SetFvMaxVoltage(UINT32 VddMaxVoltage)
{
  EFI_STATUS Status = EFI_UNSUPPORTED;

  return Status;
}

/**
  Get Charger/Power Path

  @param[out] Powerpath

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_INVALID_PARAMETER: Parameter is invalid.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
//EFI_STATUS ChargerLibTarget_GetPowerPath(CHARGERLIB_ATTACHED_CHGR_TYPE *PowerPath)
//{
//  EFI_STATUS Status = EFI_SUCCESS;
//
//  switch (ChargerInfo.ChargerHW)
//  {
//  case EfiBatteryChargerQcomPmicSchg:
//    Status = PmicSchgProtocol->GetPowerPath(ChargerInfo.ChargerPmicInfo.PmicIndex, (PM_SCHG_POWER_PATH_TYPE *)PowerPath);
//    break;
//  default:
//    Status = EFI_UNSUPPORTED;
//    break;
//  }
//
//  return Status;
//}

EFI_STATUS ChargerLibTarget_GetChargingPath(CHARGERLIB_ATTACHED_CHGR_TYPE *ChargingPath)
{
  EFI_STATUS Status = EFI_SUCCESS;
  BOOLEAN IsInputValid = FALSE;
  EFI_PM_SCHG_TYPEC_CONNECT_MODE_STATUS typec_conn_st = EFI_PM_SCHG_TYPEC_CONNECT_MODE_NONE;
  static UINT32 usb_vbus_missing_count = 0;

  if (!ChargingPath)
  {
    return EFI_INVALID_PARAMETER;
  }
  *ChargingPath = CHARGERLIB_ATTACHED_CHGR__NONE;
  switch (ChargerInfo.ChargerHW)
  {
  case EfiBatteryChargerQcomPmicSchg:
    Status = PmicSchgProtocol->UsbinValid(ChargerInfo.ChargerPmicInfo.PmicIndex, &IsInputValid);
    Status|= PmicSchgProtocol->GetConnectState(ChargerInfo.ChargerPmicInfo.PmicIndex, &typec_conn_st);
    if(Status != EFI_SUCCESS)
    {
      break;
    }
    if (IsInputValid)
    {
      *ChargingPath = CHARGERLIB_ATTACHED_CHGR__USB;
    }
    else if((typec_conn_st == EFI_PM_SCHG_TYPEC_CONNECT_MODE_UFP) && usb_vbus_missing_count < MAX_VBUS_MISSING_COUNT)
    {
      usb_vbus_missing_count++;
      *ChargingPath = CHARGERLIB_ATTACHED_CHGR__USB;
      CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Vbus Missing but UFP detected, count=%d \r\n", __FUNCTION__, usb_vbus_missing_count));
    }
    else
    {
      Status = PmicSchgProtocol->DcinValid(ChargerInfo.ChargerPmicInfo.PmicIndex, &IsInputValid);
      if(Status != EFI_SUCCESS)
      {
        break;
      }
      if (IsInputValid)
      {
        *ChargingPath = CHARGERLIB_ATTACHED_CHGR__DCIN;
      }
      else
      {
        *ChargingPath = CHARGERLIB_ATTACHED_CHGR__NONE;
      }
    }
    break;
  default:
    Status = EFI_UNSUPPORTED;
    break;
  }

  return Status;
}

/**
  Get Battery Presence

  @param[out] BatteryPresence

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_INVALID_PARAMETER: Parameter is invalid.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_GetBatteryPresence(BOOLEAN *BatteryPresence)
{
  EFI_STATUS Status = EFI_SUCCESS;

  switch (BatteryGaugeInfo.BatteryGaugeHW)
  {
    case EfiBatteryGaugeQcomPmicFg:
         if (!PmicFgProtocol)
         {
          Status |= gBS->LocateProtocol( &gQcomPmicFgProtocolGuid,
                                      NULL,
                                     (VOID **)&PmicFgProtocol );
          if(Status != EFI_SUCCESS || NULL == PmicFgProtocol)
          return EFI_DEVICE_ERROR;
         }

         Status = PmicFgProtocol->QBGIsBatteryPresent(BatteryGaugeInfo.BatteryGaugePmicInfo.PmicIndex, BatteryPresence);
         break;
    default:
         Status = EFI_UNSUPPORTED;
         break;
  }

  return Status;
}

/**
  Gets charger port type

  @param[out] pPortType  Charger port type

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_GetPortType(CHARGERLIB_CHGR_PORT_TYPE *pPortType)
{
  EFI_STATUS                  Status = EFI_SUCCESS;
  EFI_PM_SCHG_CHGR_PORT_TYPE  PortType;

  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      Status  = PmicSchgProtocol->GetChargerPortType(ChargerInfo.ChargerPmicInfo.PmicIndex, &PortType);
      *pPortType = (CHARGERLIB_CHGR_PORT_TYPE)PortType;

      CHARGER_FILE_UART_DEBUG((EFI_D_WARN,"ChargerLib:: %a Charger Port type = %d \r\n", __FUNCTION__, PortType));

      break;
    default:
      Status = EFI_UNSUPPORTED;
      break;
  }

  return Status;
}


EFI_STATUS ChargerLibTarget_HandleNoChargeAndWait(void)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (TRUE == gChargerLibTargetCfgData.no_charge_and_wait)
  {
    /*Disable Charging */
    Status = ChargerLibTarget_ChargerEnable(FALSE);
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Charging Disabled \r\n", __FUNCTION__));
  }
  else
  {
    ChargerLibTarget_ForceSysShutdown(CHGAPP_RESET_AFP);
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_EnableAfpMode(void)
{
  EFI_STATUS Status = EFI_SUCCESS;
  return Status;
}

EFI_STATUS ChargerLibTarget_GetBatteryID(INT32 *pBatteryID)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EfiAdcResultType AdcResult = {0};

  if(NULL == pBatteryID)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pBatteryID = 7500;
  if(FirstBatteryIDRead)
  {
    Status = ChargerLibTarget_GetADCReading(ADC_INPUT_BATT_ID_OHMS, sizeof(ADC_INPUT_BATT_ID_OHMS), &AdcResult);
  
    if (EFI_ERROR(Status))
    {
      CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a: Failed to read ADC ADC_INPUT_BATT_ID_OHMS Channel! \r\n", __FUNCTION__));
      return Status;
    }

    *pBatteryID = AdcResult.nPhysical;
    BatteryID = AdcResult.nPhysical;
    FirstBatteryIDRead = FALSE;
  }
  else
  {
    *pBatteryID = BatteryID;
  }
  
  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a BATT_ID_2 = %d \r\n", __FUNCTION__, *pBatteryID));

  return Status;
}

EFI_STATUS ChargerLibTarget_GetBatteryType(ChgBattType *pBatteryType)
{
  EFI_STATUS Status = EFI_SUCCESS;
  INT32      battery_id = 0;

  if(NULL == pBatteryType)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pBatteryType = CHG_BATT_TYPE_INVALID;
  
  Status = ChargerLibTarget_GetBatteryID(&battery_id);
  if(EFI_SUCCESS != Status)
  {
    return Status;
  }

  /*Check if battery ID is within real battery range*/
  if((battery_id >= gChargerLibTargetCfgData.fg_cfg_data.FgBattIdCfg.SmartBatteryIdMin) &&
     (battery_id <= gChargerLibTargetCfgData.fg_cfg_data.FgBattIdCfg.SmartBatteryIdMax))
   {
     *pBatteryType = CHG_BATT_TYPE_SMART;
   }
   else if((battery_id >= gChargerLibTargetCfgData.fg_cfg_data.FgBattIdCfg.RegularBatteryIdMin) &&
     (battery_id <= gChargerLibTargetCfgData.fg_cfg_data.FgBattIdCfg.RegularBatteryIdMax))
   {
     *pBatteryType = CHG_BATT_TYPE_NORMAL;
   }
   else if((battery_id >= gChargerLibTargetCfgData.fg_cfg_data.FgBattIdCfg.DebugBoardBatteryIdMin) &&
     (battery_id <= gChargerLibTargetCfgData.fg_cfg_data.FgBattIdCfg.DebugBoardBatteryIdMax))
   {
     *pBatteryType = CHG_BATT_TYPE_DEBUG_BOARD;
   }
   else
   {
     *pBatteryType = CHG_BATT_TYPE_UNKNOWN;
   }

   CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Battery type = %d \r\n", __FUNCTION__, *pBatteryType));

  return Status;
}

EFI_STATUS ChargerLibTarget_UsbSuspend(BOOLEAN Enable)
{
  EFI_STATUS Status = EFI_SUCCESS;

  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a ChargerLib UsbSuspend = %d \r\n", __FUNCTION__, Enable));

  switch (ChargerInfo.ChargerHW)
  {
  case EfiBatteryChargerQcomPmicSchg:
    Status = PmicSchgProtocol->UsbSuspend(ChargerInfo.ChargerPmicInfo.PmicIndex, Enable);
    break;
  default:
    Status = EFI_UNSUPPORTED;
    break;
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_DcinSuspend(BOOLEAN Suspend)
{
  EFI_STATUS Status = EFI_SUCCESS;

  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a ChargerLib DcinSuspend = %d \r\n", __FUNCTION__, Suspend));

  switch (ChargerInfo.ChargerHW)
  {
  case EfiBatteryChargerQcomPmicSchg:
    Status = PmicSchgProtocol->DcinSuspend(ChargerInfo.ChargerPmicInfo.PmicIndex, Suspend);
    break;
  default:
    Status = EFI_UNSUPPORTED;
    break;
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_DcinSetPowerLimit(UINT32 PowerInMicroW)
{
  EFI_STATUS Status = EFI_SUCCESS;

  return Status;
}

EFI_STATUS ChargerLibTarget_GetDebugBoardAction(CHARGERLIB_ERROR_ACTION_TYPE *pDebugBoardAction)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32     DebugBoardBehaviour = gChargerLibTargetCfgData.debug_board_behavior;

  chargerlib_batt_status_info  BatteryStatus;

  if (!pDebugBoardAction)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status = ChargerLibTarget_GetBatteryStatus(&BatteryStatus);
  if( EFI_SUCCESS != Status )
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Error getting battery status = %r \r\n", __FUNCTION__, Status));
    return Status;
  }

  /*ignore return type to allow continued booting*/
  ChargerLibTarget_UsbSuspend(TRUE);
  //suspend dcin
  ChargerLibTarget_DcinSuspend(TRUE);

  if(BatteryStatus.BatteryVoltage < gChargerLibTargetCfgData.boot_to_hlos_threshold_in_mv)
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Debug board voltage = %d mV is below Threshold = %d mV \r\n", __FUNCTION__, BatteryStatus.BatteryVoltage, gChargerLibTargetCfgData.boot_to_hlos_threshold_in_mv));

    switch(DebugBoardBehaviour)
    {
      case DEBUG_BOARD_LOWVBAT_SHUTDOWN:
        Status = ChargerLibTarget_SetPon1Trigger(EFI_PM_PON_OPTION_USB_CHG_REDGE_PON, TRUE);
        Status |= ChargerLibTarget_SetPon1Trigger(EFI_PM_PON_OPTION_DC_CHG_REDGE_PON, TRUE);
        *pDebugBoardAction = CHARGERLIB_ERROR_ACTION_SHUTDOWN;
        //display red debug icon
        gDispImage = CHARGERLIB_EVENT_DISP_IMAGE_DEBUG_LOW_SYMBOL;
        break;
      case DEBUG_BOARD_LOWVBAT_NOCHARGE:
        *pDebugBoardAction = CHARGERLIB_ERROR_ACTION_DEBUG_BOARD_WAIT;
        gDispImage = CHARGERLIB_EVENT_DISP_IMAGE_DEBUG_LOW_SYMBOL;
        break;
      case DEBUG_BOARD_BOOT_TO_HLOS:
        *pDebugBoardAction = CHARGERLIB_ERROR_ACTION_DEBUG_BOARD_GOOD_TO_BOOT;
        gDispImage = CHARGERLIB_EVENT_DISP_IMAGE_DEBUG_BOOT_SYMBOL;
        break;
      default:
        break;
    }
  }
  else
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a: Debug board voltage = %d mV is above Threshold = %d mV \r\n", __FUNCTION__, BatteryStatus.BatteryVoltage, gChargerLibTargetCfgData.boot_to_hlos_threshold_in_mv));
    *pDebugBoardAction = CHARGERLIB_ERROR_ACTION_DEBUG_BOARD_GOOD_TO_BOOT;
  }

  return EFI_SUCCESS;
}


EFI_STATUS ChargerLibTarget_ConservativeCharging( void )
{
  EFI_STATUS Status = EFI_SUCCESS;

  /*set conservative parameter */
  Status = ChargerLibTarget_SetFvMaxVoltage(gChargerLibTargetCfgData.schg_cfg_data.ChgFvMax - gChargerLibTargetCfgData.conserv_chg_fv_delta);
  Status |= ChargerLibTarget_SetFccMaxCurrent(FCC_CONSERVE_CHG);

  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a enabling conservative charging \r\n", __FUNCTION__));
  Status |= ChargerLibTarget_ChargerEnable(TRUE);

  return Status;
}

EFI_STATUS ChargerLibTarget_GetUnknownBatteryAction(CHARGERLIB_ERROR_ACTION_TYPE *pUnknownBatteryAction)
{
  EFI_STATUS Status               = EFI_SUCCESS;
  UINT32     UnknownBattBehaviour = gChargerLibTargetCfgData.unknown_battery_behavior;
  chargerlib_batt_status_info  BatteryStatus;

  switch (UnknownBattBehaviour)
  {
    case UNKNOWN_BATT_SHUTDOWN:
      *pUnknownBatteryAction = CHARGERLIB_ERROR_ACTION_SHUTDOWN_USB_DC_PON_DISABLED;
      break;
    case UNKNOWN_BATT_BOOT_TO_HLOS:
    /*Boot to HLOS if battery more than threshold. Else shutdown */
      Status = ChargerLibTarget_GetBatteryStatus(&BatteryStatus);
      if( EFI_SUCCESS != Status )
      {
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Error getting battery status = %r \r\n", __FUNCTION__, Status));
        return Status;
      }

      /*ignore return type to allow continued booting*/
      ChargerLibTarget_UsbSuspend(TRUE);
      //suspend dcin
      ChargerLibTarget_DcinSuspend(TRUE);

      if(BatteryStatus.BatteryVoltage > gChargerLibTargetCfgData.boot_to_hlos_threshold_in_mv)
      {
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a: Unknown battery detected, voltage = %d mV is above Threshold = %d mV \r\n", __FUNCTION__, BatteryStatus.BatteryVoltage, gChargerLibTargetCfgData.boot_to_hlos_threshold_in_mv));
        *pUnknownBatteryAction = CHARGERLIB_ERROR_ACTION_GOOD_TO_BOOT;
      }
      else
      {
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a: Unknown battery detected, shutting down. Voltage = %d mV is below Threshold = %d mV \r\n", __FUNCTION__, BatteryStatus.BatteryVoltage, gChargerLibTargetCfgData.boot_to_hlos_threshold_in_mv));
        Status = ChargerLibTarget_SetPon1Trigger(EFI_PM_PON_OPTION_DC_CHG_REDGE_PON, TRUE);
        Status |= ChargerLibTarget_SetPon1Trigger(EFI_PM_PON_OPTION_USB_CHG_REDGE_PON, TRUE);
        *pUnknownBatteryAction = CHARGERLIB_ERROR_ACTION_SHUTDOWN;
      }

      break;
    case UNKNOWN_BATT_CONSERVATIVE_CHARGING:
      ChargerLibTarget_ConservativeCharging();
      break;
    case UNKNOWN_BATT_REGULAR_CHARGING:
      *pUnknownBatteryAction = CHARGERLIB_ERROR_ACTION_START_CHARGING;
      break;
    default:
      ChargerLibTarget_GetDebugBoardAction( pUnknownBatteryAction );
      break;
  }

  return Status;
}


/*This API initiates different types of reset */
EFI_STATUS ChargerLibTarget_ForceSysShutdown(ChgAppSysShutdownType ShutdownType)
{
  EFI_STATUS Status = EFI_SUCCESS;

  EFI_RESET_TYPE   ResetType = EfiResetPlatformSpecific;

  switch (ShutdownType)
  {
  case CHGAPP_RESET_SHUTDOWN:
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a CHGAPP_RESET_SHUTDOWN.\r\n", __FUNCTION__));
    ResetType = EfiResetShutdown;
    break;
  case CHGAPP_RESET_AFP:
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a CHGAPP_RESET_AFP.\r\n", __FUNCTION__));
    /*if AFP not supported then enable USB as edge PON trigger and issue shut down */
    Status = ChargerLibTarget_SetPon1Trigger(EFI_PM_PON_OPTION_USB_CHG_REDGE_PON, TRUE);
    Status |= ChargerLibTarget_SetPon1Trigger(EFI_PM_PON_OPTION_DC_CHG_REDGE_PON, TRUE);
    ResetType = EfiResetShutdown;
    break;
  case CHGAPP_RESET_COLD:
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a CHGAPP_RESET_COLD.\r\n", __FUNCTION__));
    ResetType = EfiResetCold;
    break;
  /* Ship mode is not supported on LA
  case CHGAPP_RESET_SHIPMODE:
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a CHGAPP_RESET_TO_SHIPMODE.\r\n", __FUNCTION__));
    if (EFI_SUCCESS != ChargerLibTarget_EnableShipMode())
    {
      *if Ship mode not supported then disable USB as PON trigger and issue shut down *
      if (NULL != PmicPwronProtocol)
      {
        Status |= PmicPwronProtocol->SetPonTrigger(PM_DEVICE_0, EFI_PM_PON_TRIGGER_DC_CHG, FALSE);
        Status |= PmicPwronProtocol->SetPonTrigger(PM_DEVICE_0, EFI_PM_PON_TRIGGER_USB_CHG, FALSE);
      }
      ResetType = EfiResetShutdown;
    }
    break;
  */

  case CHGAPP_RESET_SHUTDOWN_USB_DC_PON_DISABLED:
     /*Disable USB as PON trigger and issue shut down */
     Status = ChargerLibTarget_SetPon1Trigger(EFI_PM_PON_OPTION_USB_CHG_REDGE_PON, TRUE);
     Status |= ChargerLibTarget_SetPon1Trigger(EFI_PM_PON_OPTION_DC_CHG_REDGE_PON, TRUE);
     ResetType = EfiResetShutdown;
    break;
  case CHGAPP_RESET_NONE:
  case CHGAPP_RESET_INVALID:
  default:
    /*Do nothing*/
    return Status;
  }

  /* Reset  Device*/
  gRT->ResetSystem(ResetType, EFI_SUCCESS, 0, NULL);

  return Status;
}

EFI_STATUS ChargerLibTarget_GetThermalStatus( ChargerLibThermalStatus *ThermalStatus)
{
  EFI_STATUS Status = EFI_SUCCESS;
  INT32 CurrTemp = 0;
  STATIC ChargerLibThermalStatus ThermalSts = CHARGERLIB_THERMAL_INIT; /* Start with Init */
  if((NULL == PmicFgProtocol ) || (NULL == ThermalStatus))
    return EFI_DEVICE_ERROR;

  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      Status = ChargerLibTarget_GetTSensTemp(&CurrTemp);
      if (Status != EFI_SUCCESS)
      {
        CHARGER_FILE_UART_DEBUG((EFI_D_WARN,"ChargerLib:: %a Failed = %r \r\n", __FUNCTION__, Status));
        *ThermalStatus = ThermalSts = CHARGERLIB_THERMAL_STATUS_MAX;/*Updated output params*/
        return Status;
      }
    break;

    default:
      Status = EFI_UNSUPPORTED;
      break;
  }
  /*  Handle if any Error */
  if(EFI_ERROR(Status))
    return Status;

  switch(ThermalSts)
  {
    case CHARGERLIB_THERMAL_INIT:
    case CHARGERLIB_THERMAL_OK:
      if (CurrTemp >= gChargerLibTargetCfgData.thermal_configs.tsens_extreme_Temp)
      {
        *ThermalStatus = ThermalSts = CHARGERLIB_THERMAL_CRITICAL;/*Updated output params*/
      }
      else if (CurrTemp >= gChargerLibTargetCfgData.thermal_configs.tsens_high_temp )
      {
        *ThermalStatus = ThermalSts = CHARGERLIB_THERMAL_HIGH;
      }
      else
      {
        *ThermalStatus = ThermalSts = CHARGERLIB_THERMAL_OK;
      }
    break;

    case CHARGERLIB_THERMAL_HIGH:
      if (CurrTemp >= gChargerLibTargetCfgData.thermal_configs.tsens_extreme_Temp)
      {
        *ThermalStatus = ThermalSts = CHARGERLIB_THERMAL_CRITICAL;/*Updated output params*/
      }
      else if ((CurrTemp > gChargerLibTargetCfgData.thermal_configs.tsens_low_temp) && (CurrTemp < gChargerLibTargetCfgData.thermal_configs.tsens_extreme_Temp))
      {
        *ThermalStatus = ThermalSts = CHARGERLIB_THERMAL_HIGH;
      }
      else if (CurrTemp <= gChargerLibTargetCfgData.thermal_configs.tsens_low_temp)
      {
        *ThermalStatus = ThermalSts = CHARGERLIB_THERMAL_OK;
      }
      else
      {
        CHARGER_DEBUG((EFI_D_WARN,"ChargerLib:: %a Error = %d ThermalSts = %d \r\n", __FUNCTION__, CurrTemp, ThermalSts));
      }
    break;

    case CHARGERLIB_THERMAL_CRITICAL:
      /*should not hit this use case as it is already hanlded by then */
      *ThermalStatus = ThermalSts = CHARGERLIB_THERMAL_CRITICAL;/*Updated output params*/
    break;

    case CHARGERLIB_THERMAL_HIGH_TIMEOUT:
      /*should not hit this use case as it is already hanlded by then */
      *ThermalStatus = ThermalSts = CHARGERLIB_THERMAL_HIGH_TIMEOUT;/*Updated output params*/
    break;

    default:
    break;
  }

  CHARGER_DEBUG((EFI_D_WARN,"ChargerLib:: %a CurrTsensTemp = %d ThermalStatus = %d\r\n", __FUNCTION__, CurrTemp, *ThermalStatus));

  return Status;
}


EFI_STATUS ChargerLibTarget_GetTSensTemp( INT32 *TSensTemp)
{
  EFI_STATUS Status = EFI_SUCCESS;
  INT32 nTempDeciDegC = 0, nTempDegC = 0;

  STATIC EFI_TSENS_PROTOCOL *Tsens = NULL;

  if(NULL == Tsens)
  {
    Status = gBS->LocateProtocol(&gEfiTsensProtocolGuid, NULL, (VOID**)&Tsens);
    if (Status != EFI_SUCCESS)
    {
      CHARGER_FILE_UART_DEBUG((EFI_D_WARN,"ChargerLib:: %a TSENS Protocol Locate Failed %r \r\n", __FUNCTION__, Status));
      return Status;
    }
  }

  /* Loop if current temperature of device is greater than max */
  Status = Tsens->GetMaxTemp(&nTempDeciDegC);
  if (EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG((EFI_D_WARN,"ChargerLib:: %a TSENS Protocol GetMaxTemp Failed = %r \r\n", __FUNCTION__, Status));
    /* break and exit to AFP ??*/
    return Status;
  }

  /*Temp is divide by 10 in C*/
  nTempDegC = nTempDeciDegC / 10;

  *TSensTemp  = nTempDegC;

  return Status;
}

EFI_STATUS ChargerLibTarget_DumpSram(BOOLEAN bDumpExplicit)
{
  EFI_STATUS    Status = EFI_SUCCESS;

  return Status;
}

EFI_STATUS ChargerLibTarget_DumpChargerPeripheral()
{
  EFI_STATUS Status = EFI_SUCCESS;

  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      if((TRUE == gChargerLibTargetCfgData.dbg_cfg_Data.enable_charger_fg_Dump ) && ( !RETAIL))
      {
        if( EFI_SUCCESS == Status )
        {
          if(NULL != PmicFgProtocol)
            Status = PmicFgProtocol->DumpPeripheral();

          if(NULL != PmicSchgProtocol)
            Status |= PmicSchgProtocol->DumpPeripheral();
        }
      }
    break;

    default:
      Status = EFI_UNSUPPORTED;
    break;
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_GetHwJeitaStatus(CHARGERLIB_HW_JEITA_STATUS *pHwJeitaStatus)
{
  EFI_STATUS  Status = EFI_SUCCESS;
  EFI_PM_SCHG_BATT_TEMP_STATUS HwJeitaStatus = { 0 };

  if (!pHwJeitaStatus)
    return EFI_INVALID_PARAMETER;

  if (!gProfileLoadCalled)
    return EFI_SUCCESS;

  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      Status |= PmicSchgProtocol->GetHwJeitaStatus(ChargerInfo.ChargerPmicInfo.PmicIndex, &HwJeitaStatus);
    break;

  default:
    break;
  }

  if (Status == EFI_SUCCESS)
  {
    pHwJeitaStatus->JeitaHardHot = HwJeitaStatus.jeitaHardHot;
    pHwJeitaStatus->JeitaSoftHot = HwJeitaStatus.jeitaSoftHot;
    pHwJeitaStatus->JeitaHardCold = HwJeitaStatus.jeitaHardCold;
    pHwJeitaStatus->JeitaSoftCold = HwJeitaStatus.jeitaSoftCold;
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_GetBatteryTempStatus(CHARGERLIB_BATT_TEMP_STATUS *pBattTempStatus)
{
  //Battery temperature outside of operational range, extreme cold or hot condition (below -15 , above 70 degree, configurable) (AFP) -- BatteryTemperatureOutOfRangeError
  EFI_STATUS Status      = EFI_SUCCESS;
  CHARGERLIB_HW_JEITA_STATUS   HwJeitaStatus = {0};
  chargerlib_batt_status_info  BatteryStatus = {0};

  if (!pBattTempStatus)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pBattTempStatus = ChargerLib_Batt_Temp_Normal;

  Status = ChargerLibTarget_GetBatteryStatus(&BatteryStatus);
  if(EFI_SUCCESS != Status )
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib::%a Error getting battery status = %r \r\n", __FUNCTION__, Status));
    return Status;
  }
  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib::%a BatteryTemp = %d C \r\n", __FUNCTION__, BatteryStatus.BatteryTemperature));

  Status = ChargerLibTarget_GetHwJeitaStatus( &HwJeitaStatus );
  if((TRUE == HwJeitaStatus.JeitaHardCold) || (TRUE == HwJeitaStatus.JeitaHardHot))
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib::%a BatteryTemp out-of-range = %d C \r\n",__FUNCTION__, BatteryStatus.BatteryTemperature));
    *pBattTempStatus = ChargerLib_Batt_Temp_OutsideChargingRange;
  }

  if(( BatteryStatus.BatteryTemperature < gChargerLibTargetCfgData.fg_cfg_data.HwJeitaThreshold.JeitaCriticalTempLowLimit) ||
     ( BatteryStatus.BatteryTemperature > gChargerLibTargetCfgData.fg_cfg_data.HwJeitaThreshold.JeitaCriticalTempHighLimit))
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a BatteryTemp = %d C, Operational Range lower limit = %d, upper limit = %d \r\n",
                __FUNCTION__, BatteryStatus.BatteryTemperature, gChargerLibTargetCfgData.fg_cfg_data.HwJeitaThreshold.JeitaCriticalTempLowLimit,
                  gChargerLibTargetCfgData.fg_cfg_data.HwJeitaThreshold.JeitaCriticalTempHighLimit));

    *pBattTempStatus = ChargerLib_Batt_Temp_OutsideOperationalRange;
  }

  if(EFI_SUCCESS != Status)
  {
    *pBattTempStatus = ChargerLib_Batt_Temp_Invalid;
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib::%a BatteryTemp invalid = %r \r\n",__FUNCTION__, Status));
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_GetBatteryVoltageStatus(CHARGERLIB_VBATT_STATUS *pBatteryVoltageStatus)
{
  EFI_STATUS                   Status      = EFI_SUCCESS;
  STATIC UINT32                EmergencyShutdownCounter = 0;
  chargerlib_batt_status_info  BatteryStatus = {0};
  UINT32 high_vbatt_threshold = gChargerLibTargetCfgData.schg_cfg_data.ChgFvMax;

  if (!pBatteryVoltageStatus)
  {
    return EFI_INVALID_PARAMETER;
  }
  
  *pBatteryVoltageStatus = ChargerLib_VBatt_Normal;

  Status = ChargerLibTarget_GetBatteryStatus(&BatteryStatus);
  if( EFI_SUCCESS != Status )
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Error getting battery status = %r \r\n", __FUNCTION__, Status));
    return Status;
  }

  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Battery voltage = %d mV \r\n", __FUNCTION__, BatteryStatus.BatteryVoltage));
  if(gIs_2S_Battery)
  {
    high_vbatt_threshold = 2* gChargerLibTargetCfgData.schg_cfg_data.ChgFvMax;
  }
  /* Return status if vbatt is good */
  if ((UINT32)BatteryStatus.BatteryVoltage > (high_vbatt_threshold + gChargerLibTargetCfgData.batt_volt_lim_high_delta))
  {
    EmergencyShutdownCounter = 0;

    Status = ChargerLibTarget_GetBatteryStatus(&BatteryStatus);
    if( EFI_SUCCESS != Status )
    {
      CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Error getting battery status = %r \r\n", __FUNCTION__, Status));
      return Status;
    }

    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Current Battery voltage =  %d mV \r\n", __FUNCTION__, BatteryStatus.BatteryVoltage));

    /* Check for High Voltage Limit */
    if (((UINT32)(BatteryStatus.BatteryVoltage - VBATT_TOLERANCE)) > (high_vbatt_threshold + gChargerLibTargetCfgData.batt_volt_lim_high_delta))
    {
      CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Current Battery voltage too high %d mV, Threshold = %d mV  \r\n", __FUNCTION__,
                                BatteryStatus.BatteryVoltage, (gChargerLibTargetCfgData.schg_cfg_data.ChgFvMax + gChargerLibTargetCfgData.batt_volt_lim_high_delta)));
      *pBatteryVoltageStatus = ChargerLib_VBatt_TooHigh;
    }
  }
  /* Check for vbatt below emergency shutdown limit */
  else if ((UINT32)BatteryStatus.BatteryVoltage < gChargerLibTargetCfgData.emergency_shutdown_vbatt)
  {
    if(BatteryStatus.ChargeCurrent > 0) /* Battery is discharging */
    {
      CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Current BattVoltage = %d mV is below EmergencyShutdownVbatt = %d mV ", __FUNCTION__,
                    BatteryStatus.BatteryVoltage, gChargerLibTargetCfgData.emergency_shutdown_vbatt));
    CHARGER_DEBUG((EFI_D_WARN, " EmergencyShutdownCounter = %d \r\n", EmergencyShutdownCounter));
      if(EmergencyShutdownCounter >= MAX_EMERGENCY_SHUTDOWN_COUNT)
      {
        *pBatteryVoltageStatus = ChargerLib_VBatt_BelowThreshold;
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a EmergencyShutdownCounter Exceeded : \r\n", __FUNCTION__ ));
    CHARGER_DEBUG((EFI_D_WARN, " Curr Battery voltage = %d mV is below threshold = %d mV \r\n",
          BatteryStatus.BatteryVoltage, gChargerLibTargetCfgData.emergency_shutdown_vbatt ));
      }
      else
      {
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a EmergencyShutdownCounter = %d \r\n", __FUNCTION__, EmergencyShutdownCounter));
      }
      EmergencyShutdownCounter++;
    }
    else
    {
      EmergencyShutdownCounter = 0;
    }
  }
  else
  {
    EmergencyShutdownCounter = 0;
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_EnableHWJeita(BOOLEAN Enable)
{
  EFI_STATUS Status = EFI_SUCCESS;

  /* For 8250, HW Jeita will be enabled from PmicDxe after battery therm (from profile) is read.
     Battery profile contains batt therm pull-up, which is required for converting JEITA thresholds
     from degree C to ADC code based on batt therm pull-up */

#ifdef FEATURE_XBOOT
  if(TRUE == Enable)
  {
    Status = EFI_UNSUPPORTED;
    CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a ChargerLibTarget_EnableHWJeita(TRUE) %s \r\n", __FUNCTION__, Status));
  }
#endif /* FEATURE_XBOOT */

  return Status;
}

EFI_STATUS ChargerLibTarget_GetSdpMaxCurrent(UINT32 *pSdpMaxCurrent)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_USBFN_CHG_SRV_SPEED_TYPE                SdpSpeed = USB_CHG_SPD_UNKNOWN;

  if(NULL == pSdpMaxCurrent)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pSdpMaxCurrent = USB_2_IUSB_MAX;

  if (!UsbInitProtocol)
  {
    Status = gBS->LocateProtocol(&gEfiUsbInitProtocolGuid, NULL, (VOID **)&UsbInitProtocol);
  }

  if (!UsbChgSrvProtocol)
  {
    Status |= gBS->LocateProtocol(&gEfiUsbfnChgSrvProtocolGuid, NULL, (VOID **)&UsbChgSrvProtocol);
  }

  if((EFI_SUCCESS == Status) && (NULL != UsbInitProtocol) && (NULL != UsbChgSrvProtocol))
  {
    if((FALSE == gStartControllerCalled))
    {
      Status |= UsbInitProtocol->StartController(UsbInitProtocol, 0, EFI_USB_PERIPHERAL_MODE);

      Status |= UsbChgSrvProtocol->StartController(UsbChgSrvProtocol);

      if(EFI_SUCCESS == Status)
      {
        /* Store Enumeration done state, since we will need to call StopController in case of any error and charger swap*/
        gStartControllerCalled = TRUE;
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a success from StartController API, Status: %r \r\n", __FUNCTION__, Status));
      }
      else
      {
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a error from StartController API, Status: %r \r\n", __FUNCTION__, Status));
      }
    }
    else
    {
      WaitForTimeoutNoKey (USB_ENUM_WAIT_DURATION);
    }

    Status |= UsbChgSrvProtocol->GetSpeed(UsbChgSrvProtocol, &SdpSpeed);
    if(EFI_SUCCESS == Status)
    {/*If Status is not success, SDP */
      if(USB_CHG_SPD_SUPER == SdpSpeed)
      {
        *pSdpMaxCurrent = USB_3_IUSB_MAX;
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a CHARGERLIB_CHG_PORT_SDP_CHARGER 3.0 Detected, ChargerCurrent = %d mA \r\n", __FUNCTION__, *pSdpMaxCurrent));
        return Status;
      }
    }
    else
    {
       CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a error getting SDP Speed, Status: : %r \r\n", __FUNCTION__, Status));
    }
  }
  else
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a error locating UsbChgSrv Protocol, Status: : %r \r\n", __FUNCTION__, Status));
    /*if the protocol is not supported, we will fall back to USB2.0 and return SUCCESS*/
    Status = EFI_SUCCESS;
  }

  *pSdpMaxCurrent = USB_2_IUSB_MAX;
  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a CHARGERLIB_CHG_PORT_SDP_CHARGER 2.0 Detected, ChargerCurrent = %d mA \r\n", __FUNCTION__, *pSdpMaxCurrent));

  return Status;
}


EFI_STATUS ChargerLibTarget_GetChgWdogStatus( CHARGERLIB_CHG_WDOG_STS_TYPE *pChgWdogSts)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(NULL == pChgWdogSts)
    return EFI_INVALID_PARAMETER;

  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      /* Locate SCHG Protocol */
      if (!PmicSchgProtocol)
      {
        Status |= gBS->LocateProtocol( &gQcomPmicSchgProtocolGuid,
                                      NULL,
                                     (VOID **)&PmicSchgProtocol );
      }

      if((EFI_SUCCESS == Status) && (NULL != PmicSchgProtocol))
      {
        Status = PmicSchgProtocol->GetChgWdogStatus(ChargerInfo.ChargerPmicInfo.PmicIndex, (EFI_PM_SCHG_WDOG_STS_TYPE *)pChgWdogSts);
      }
      break;
    default:
      return EFI_UNSUPPORTED;
      break;

  }

  return Status;
}

EFI_STATUS ChargerLibTarget_InitializeCharging( VOID )
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_SCHG_CHARGING_STATUS ChargingSts = {0};

  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Entry \r\n", __FUNCTION__));

  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      if (!PmicSchgProtocol)
      {
        Status |= gBS->LocateProtocol( &gQcomPmicSchgProtocolGuid,
                                       NULL,
                                      (VOID **)&PmicSchgProtocol );
      }

      if((EFI_SUCCESS != Status) || (NULL == PmicSchgProtocol))
      {
        return EFI_UNSUPPORTED;
      }
      break;
    default:
      Status = EFI_UNSUPPORTED;
      break;
  }

  // charging is enabled in SBL
  gChargingEnabled = TRUE;

  Status = PmicSchgProtocol->GetChargingStatus(ChargerInfo.ChargerPmicInfo.PmicIndex, &ChargingSts);
  if((EFI_SUCCESS == Status) && (!ChargingSts.bChargingEnabled) && gChargingEnabled)
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a WDOG Bite may have happened, Toggling charging command to re-enable charging. \r\n", __FUNCTION__));
    Status = PmicSchgProtocol->SetChargeCmdBit(ChargerInfo.ChargerPmicInfo.PmicIndex, FALSE);    
    Status |= PmicSchgProtocol->SetChargeCmdBit(ChargerInfo.ChargerPmicInfo.PmicIndex, TRUE);
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_EnableWdog(BOOLEAN Enable)
{
  EFI_STATUS Status = EFI_SUCCESS;

  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      /* Locate SCHG Protocol */
      if (!PmicSchgProtocol)
      {
        Status |= gBS->LocateProtocol( &gQcomPmicSchgProtocolGuid,
                                      NULL,
                                     (VOID **)&PmicSchgProtocol );
      }

      if((EFI_SUCCESS == Status) && (NULL != PmicSchgProtocol))
      {
        Status = PmicSchgProtocol->EnableChgWdog(ChargerInfo.ChargerPmicInfo.PmicIndex, Enable);
      }
      break;
    default:
      return EFI_UNSUPPORTED;
      break;
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_PetChgWdog( VOID )
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_SCHG_CHARGING_STATUS ChargingSts = {0};

  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      /* Locate SCHG Protocol */
      if (!PmicSchgProtocol)
      {
        Status |= gBS->LocateProtocol( &gQcomPmicSchgProtocolGuid,
                                      NULL,
                                     (VOID **)&PmicSchgProtocol );
      }

      if((EFI_SUCCESS == Status) && (NULL != PmicSchgProtocol))
      {
        Status = PmicSchgProtocol->PetChgWdog(ChargerInfo.ChargerPmicInfo.PmicIndex);

        Status |= PmicSchgProtocol->GetChargingStatus(ChargerInfo.ChargerPmicInfo.PmicIndex, &ChargingSts);
        if((EFI_SUCCESS == Status) && (!ChargingSts.bChargingEnabled) && gChargingEnabled)
        {
          CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a WDOG Bite may have happened, Toggling charging command to re-enable charging. \r\n", __FUNCTION__));
          Status = PmicSchgProtocol->SetChargeCmdBit(ChargerInfo.ChargerPmicInfo.PmicIndex, FALSE);    
          Status |= PmicSchgProtocol->SetChargeCmdBit(ChargerInfo.ChargerPmicInfo.PmicIndex, TRUE);
        }        
      }
      break;
    default:
      return EFI_UNSUPPORTED;
      break;
  }

  return Status;
}

/**
  Charger Lib Exit

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_Exit( VOID )
{
  EFI_STATUS     Status      = EFI_SUCCESS;

  if(gChargerLibTargetCfgData.charger_led_config)
  {
    /* Make sure to Turn Off LED during exit */
    ChargerLibTarget_LedOn(FALSE);
  }
  if(TRUE == gStartControllerCalled)
  {
    if (!UsbChgSrvProtocol)
    {
      Status |= gBS->LocateProtocol(&gEfiUsbfnChgSrvProtocolGuid, NULL, (VOID **)&UsbChgSrvProtocol);
    }

    Status |= UsbChgSrvProtocol->StopController(UsbChgSrvProtocol);

    if (!UsbInitProtocol)
    {
      Status |= gBS->LocateProtocol(&gEfiUsbInitProtocolGuid, NULL, (VOID **)&UsbInitProtocol);
    }

    Status |= UsbInitProtocol->StopController(UsbInitProtocol, 0, EFI_USB_PERIPHERAL_MODE);

    if(EFI_SUCCESS != Status)
    {
      CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Error checking Charger re-insertion status, Status: 0x%08X\n",__FUNCTION__, Status));
    }

    gStartControllerCalled = FALSE;
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_GetChargingStatus(BOOLEAN *pChargingEnabled)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_SCHG_CHARGING_STATUS ChargingSts = {0};
  EFI_PM_GLINK_LINK_STATUS      PmicGLinkStatus = { 0 };
  EFI_PM_GLINK_BATT_STATUS_INFO BattStsInfo = { 0 };
  
  if(!pChargingEnabled)
    return EFI_INVALID_PARAMETER;

  *pChargingEnabled = FALSE;

 if ((EFI_SUCCESS == ChargerLibTarget_GetIPCStatus(&PmicGLinkStatus)) && (PmicGLinkStatus.IsPMICChannelOpen == TRUE))
  {

    Status = pmicGlinkProtocol->GetBatteryStatus(BatteryIndex, &BattStsInfo);
    if(EFI_SUCCESS != Status)
    {
      CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Status: %r \r\n",__FUNCTION__, Status));
      return EFI_DEVICE_ERROR;
    }
    else if (BattStsInfo.ChargeCurrent < 0 || BattStsInfo.ChargingSource < PMIC_GLINK_CHARGING_SOURCE_TYPE_MAX)
    {
      *pChargingEnabled = TRUE;
    }
  }
  else
  {
    switch (ChargerInfo.ChargerHW)
    {
      case EfiBatteryChargerQcomPmicSchg:
        /* Locate SCHG Protocol */
        if (!PmicSchgProtocol)
        {
          Status |= gBS->LocateProtocol( &gQcomPmicSchgProtocolGuid,
                                        NULL,
                                       (VOID **)&PmicSchgProtocol );
        }

        if((EFI_SUCCESS == Status ) && (NULL != PmicSchgProtocol))
        {
          Status |= PmicSchgProtocol->GetChargingStatus(ChargerInfo.ChargerPmicInfo.PmicIndex, &ChargingSts);
        }
        if(EFI_SUCCESS == Status )
        {
          *pChargingEnabled = ChargingSts.bChargingEnabled;
        }
      break;

      default:
        break;
    }
  }
  return Status;
}

EFI_STATUS ChargerLibTarget_PrintDCInStatus()
{
  EFI_STATUS Status = EFI_SUCCESS;
  EfiAdcResultType AdcResult = { 0 };

  Status = ChargerLibTarget_GetADCReading(ADC_INPUT_DC_IN, sizeof(ADC_INPUT_DC_IN), &AdcResult);

  if (EFI_ERROR(Status))
  {
    CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a: Failed to get ADC reading from ADC_INPUT_DC_IN!\n", __FUNCTION__));
    return Status;
  }

  CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a: DCInVoltage = %d\n", __FUNCTION__, AdcResult.nPhysical));

  Status = ChargerLibTarget_GetADCReading(ADC_INPUT_DC_IN_I, sizeof(ADC_INPUT_DC_IN_I), &AdcResult);
  if (EFI_ERROR(Status))
  {
    CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a: Failed to get ADC reading from ADC_INPUT_DC_IN_I!\n", __FUNCTION__));
    return Status;
  }

  CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a: DCInCurrent = %d\n", __FUNCTION__, AdcResult.nPhysical));
  return Status;
}

EFI_STATUS ChargerLibTarget_GetADCReading(CONST CHAR8 *pszInputName, UINT32 uInputNameSize, EfiAdcResultType *pEfiAdcResult)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EfiAdcDeviceChannelType channel;

  if (NULL == pszInputName || NULL == pEfiAdcResult)
  {
    return EFI_INVALID_PARAMETER;
  }

  if (!AdcProtocol)
  {
    Status = gBS->LocateProtocol(&gEfiAdcProtocolGuid,
      NULL,
      (VOID**)&AdcProtocol);
  }

  if ((EFI_ERROR(Status)) || (NULL == AdcProtocol))
  {
    CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a: Failed to load ADC Protocol!\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  Status = AdcProtocol->GetChannel(pszInputName, uInputNameSize, &channel);
  if (EFI_ERROR(Status))
  {
    CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a: Failed to get ADC Channel!\n", __FUNCTION__ ));
    return EFI_DEVICE_ERROR;
  }

  Status = AdcProtocol->AdcRead(&channel, pEfiAdcResult);
  if ((EFI_ERROR(Status)) || (EFI_ADC_RESULT_INVALID == pEfiAdcResult->eStatus))
  {
    CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a: Failed to read ADC Channel!\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_SetUSbICLMode(CHARGERLIB_USB_ICL_MODE_TYPE IclModeType)
{
  EFI_STATUS Status = EFI_SUCCESS;

  return Status;
}

EFI_STATUS ChargerLibTarget_ConfigureUsbCurrentSetting( VOID )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32     MaxCurrent = 0;
  CHARGERLIB_CHGR_PORT_TYPE PortType = CHARGERLIB_CHG_PORT_INVALID;
  CHARGERLIB_USB_ICL_MODE_TYPE IclModeType = CHARGERLIB_USB_ICL_MODE_INVALID;
  CHARGERLIB_CHG_USBC_SINK_TYPE UsbcSinkType = CHARGERLIB_CHG_USBC_SINK_NONE;

  Status = ChargerLibTarget_GetUsbcPortType(&UsbcSinkType);
  Status |= ChargerLibTarget_GetPortType(&PortType);

  if(EFI_SUCCESS == Status)
  {
    if(CHARGERLIB_CHG_PORT_SDP_CHARGER == PortType)
    {
      Status = ChargerLibTarget_GetSdpMaxCurrent(&MaxCurrent);
    if (USB_3_IUSB_MAX == MaxCurrent)
    {
      IclModeType = CHARGERLIB_USB_ICL_MODE_SDP_3_0;
    }
    else
    {
      IclModeType = CHARGERLIB_USB_ICL_MODE_SDP_2_0;
    }
    }
    else
    {
      IclModeType = CHARGERLIB_USB_ICL_MODE_WALL_CHARGERS;
    }
  }

  CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a Setting ICL MOde to:  %d \r\n", __FUNCTION__, IclModeType));
  return Status;
}

EFI_STATUS ChargerLibTarget_LedOn( BOOLEAN bLedOn)
{
  EFI_STATUS Status = EFI_SUCCESS;
  STATIC EFI_QCOM_PMIC_RGB_LED_PROTOCOL *PmicRgbLedProtocol = NULL;
  static BOOLEAN ledOnStatus = FALSE;

  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      if (!PmicRgbLedProtocol)
      {
        Status = gBS->LocateProtocol(&gQcomPmicRgbLedProtocolGuid, NULL, (VOID **)&PmicRgbLedProtocol);
      }
      if ((Status != EFI_SUCCESS) || (NULL == PmicRgbLedProtocol))
      {
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Protocol Failed = %r \r\n", __FUNCTION__, Status));
        return EFI_DEVICE_ERROR;
      }
      if (bLedOn == TRUE)
      {
        /* Check if LED has already been turned on */
        if (ledOnStatus != bLedOn)
        {
          /* Change Led state irrespective of charging status called to make sure of charging status */
          Status |= PmicRgbLedProtocol->ConfigRgbLed(PM_DEVICE_2, EFI_PM_RGB_1, EFI_PM_RGB_LED_RED, EFI_PM_RGB_DIM_LEVEL_MID, bLedOn);
          /*  Handle if any Error */
          if (Status != EFI_SUCCESS)
          {
            CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Failed = %r \r\n", __FUNCTION__, Status));
            return Status;
          }
          else
          {
            ledOnStatus = TRUE;
            CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a LED TURNED ON = %r \r\n", __FUNCTION__, Status));
          }
        }
      }
      else
      {
        /* Turn OFF LED irrespective of charging status */
        Status |= PmicRgbLedProtocol->ConfigRgbLed(PM_DEVICE_2, EFI_PM_RGB_1, EFI_PM_RGB_LED_RED, EFI_PM_RGB_DIM_LEVEL_MID, bLedOn);
        /*  Handle if any Error */
        if (Status != EFI_SUCCESS)
        {
          CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Failed = %r \r\n", __FUNCTION__, Status));
          return Status;
        }
        else
        {
          ledOnStatus = FALSE;
          CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a LED TURNED OFF = %r \r\n", __FUNCTION__, Status));
        }
      }
      break;

    default:
      Status = EFI_UNSUPPORTED;
    break;
  }
  return Status;
}

EFI_STATUS ChargerLibTarget_SetDcinCurrent(UINT32 DcinCurrentInmA)
{
  EFI_STATUS Status = EFI_SUCCESS;

  return Status;
}

EFI_STATUS ChargeLibTarget_IsDcinValid(BOOLEAN* pIsValid)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (!pIsValid)
  {
    return EFI_INVALID_PARAMETER;
  }

  if (!PmicSchgProtocol)
  {
    Status = gBS->LocateProtocol(&gQcomPmicSchgProtocolGuid,
      NULL,
      (VOID **)&PmicSchgProtocol);

    if((Status != EFI_SUCCESS) || (NULL == PmicSchgProtocol ))
    {
      CHARGER_DEBUG((EFI_D_WARN,"ChargerLib:: %a pmicSchgProtocol Failed = %r \r\n", __FUNCTION__, Status));
      return EFI_DEVICE_ERROR;
    }
  }

  Status = PmicSchgProtocol->DcinValid(ChargerInfo.ChargerPmicInfo.PmicIndex, pIsValid);

  return Status;
}


void ChargerLibTarget_HWInit(chargerlib_cfgdata_type *pChargerLibConfig)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32  plat_index = 0;
  CHARGERLIB_PLATFORM_HW_CONFIG_TYPE config_index = CHARGERLIB_PLATFORM_HW_CONFIG_INVALID;
  UINT32  HwInfoSize = (UINT32)(sizeof(ChargerLibPlatformHwInfo)/sizeof(CHARGERLIB_PLATFORM_HW_CONFIG_INFO));

  //Initialize Charger and Battery GaugeInfo
  ChargerInfo.ChargerHW           = EfiBatteryChargerNone;
  ChargerInfo.Version             = 0x00010000;
  BatteryGaugeInfo.BatteryGaugeHW = EfiBatteryGaugeNone;
  BatteryGaugeInfo.Version        = 0x00010000;

  //Read Flag from Config Item to see if we need override the setting
  if (pChargerLibConfig->plat_hw_cfg_override < CHARGERLIB_PLATFORM_HW_CONFIG_INVALID)
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Charger PlatHWConfig = %d, (overrided by CFG item)\r\n",
                   __FUNCTION__, pChargerLibConfig->plat_hw_cfg_override));

    config_index = pChargerLibConfig->plat_hw_cfg_override;

    ChargerInfo.ChargerHW =           ChargerLibHwConfigTable[config_index].charger_hw_type;
    ChargerInfo.Version =             ChargerLibHwConfigTable[config_index].charger_hw_version;
    BatteryGaugeInfo.BatteryGaugeHW = ChargerLibHwConfigTable[config_index].gauge_hw_type;
    BatteryGaugeInfo.Version        = ChargerLibHwConfigTable[config_index].gauge_hw_version;
  }
  else
  {
    //Assign HWInfo Type based on the table
    for (plat_index = 0; plat_index < HwInfoSize; plat_index++)
    {
      if (ChargerLibPlatformHwInfo[plat_index].PlatformType == PlatformType)
      {
        //Execute HW Config Detect Function if available
        if (ChargerLibPlatformHwInfo[plat_index].pHwConfigDetectFunc != NULL)
        {
          Status = ChargerLibPlatformHwInfo[plat_index].pHwConfigDetectFunc(&ChargerInfo, &BatteryGaugeInfo);
          if (EFI_SUCCESS != Status)
          {
              CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a ERROR: Platform HW detection function failed %r \r\n",
                   __FUNCTION__, Status));
          }
        }
        //Else, perform static assignment
        else
        {
          config_index = ChargerLibPlatformHwInfo[plat_index].StaticHwConfigIndex;
          if (config_index < CHARGERLIB_PLATFORM_HW_CONFIG_INVALID)
          {
            ChargerInfo.ChargerHW =           ChargerLibHwConfigTable[config_index].charger_hw_type;
            ChargerInfo.Version =             ChargerLibHwConfigTable[config_index].charger_hw_version;
            BatteryGaugeInfo.BatteryGaugeHW = ChargerLibHwConfigTable[config_index].gauge_hw_type;
            BatteryGaugeInfo.Version        = ChargerLibHwConfigTable[config_index].gauge_hw_version;
            CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a PlatformType = %d has Static PlatHWConfig = %d \r\n",
                           __FUNCTION__, PlatformType, config_index));
          }
          else
          {
            CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a ERROR: Invalid Static Platform HW assignment \r\n",
                           __FUNCTION__, Status));
          }
        }
        break;
      }
    }
  }

  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a PlatformType = %d: ChargerHW = %d, GaugeHW = %d \r\n",
                 __FUNCTION__, PlatformType, ChargerInfo.ChargerHW, BatteryGaugeInfo.BatteryGaugeHW));

  return;
}

EFI_STATUS ChargerLibTarget_IsChargingSupported(BOOLEAN *pChargingSupported)
{
  EFI_STATUS Status = EFI_SUCCESS;
  //Checking Configuration
  if ((EfiBatteryChargerNone == ChargerInfo.ChargerHW) ||
      (EfiBatteryGaugeNone == BatteryGaugeInfo.BatteryGaugeHW))
  {
    *pChargingSupported = FALSE;
  }
  else
  {
    *pChargingSupported = TRUE;
  }
  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a PlatformType = %d: ChargerHW = %d, GaugeHW = %d \r\n",
                 __FUNCTION__, PlatformType, ChargerInfo.ChargerHW, BatteryGaugeInfo.BatteryGaugeHW));

  //Add HW Validation here in the future

  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Support Charging = %d\r\n", __FUNCTION__, *pChargingSupported));
  return Status;
}

EFI_STATUS ChargerLibTarget_GetDefectiveParts(BOOLEAN *pIsDefective)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 nMask = 0x0;
  *pIsDefective = FALSE;

  // Locate ChipInfo Protocol to get Defective Parts and CPUs
  if (!pChipInfoProtocol)
  {
    Status |= gBS->LocateProtocol(&gEfiChipInfoProtocolGuid, NULL, (VOID **) &pChipInfoProtocol);
    if((Status != EFI_SUCCESS) || (NULL == pChipInfoProtocol))
    {
      CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a Error locating ChipInfo Protocol = %r \r\n", __FUNCTION__, Status));
      return Status;
    }
  }
  // call chipinfo protocol
  Status = pChipInfoProtocol->GetDefectivePart(pChipInfoProtocol, EFICHIPINFO_PART_AUDIO, &nMask);
  if (EFI_ERROR(Status))
  {
    CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a failed, Status = %r, default to Non-Defective Part EFICHIPINFO_PART_AUDIO \r\n", __FUNCTION__, Status));
  }
  else
  {
    // nMask is non-zero if the part is defective. "non-zero" currently means 1, but that might change in the future
    // if more granularity is needed to determine defectiveness
    if (nMask != 0)
    {
      CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a got Defective Part EFICHIPINFO_PART_AUDIO(0x%x)\r\n", __FUNCTION__, nMask));
      *pIsDefective = TRUE;
    }
    else
    {
      CHARGER_DEBUG((EFI_D_INFO, "ChargerLib:: %a got Non-Defective Part EFICHIPINFO_PART_AUDIO(0x%x)\r\n", __FUNCTION__, nMask));
    }
  }
  return Status;
}

EFI_STATUS ChargerLibTarget_SetPon1Trigger(EFI_PM_PON_OPTION_BIT_TYPE bit_type, BOOLEAN bFlag )
{
  EFI_STATUS Status = EFI_SUCCESS;
  /* Enable USB and DCIN PON triggers to be certain and avoid bad use case*/
  if (!PmicPwronProtocol)
  {
    Status |= gBS->LocateProtocol(&gQcomPmicPwrOnProtocolGuid, NULL, (VOID **)&PmicPwronProtocol);
  }

  if((Status == EFI_SUCCESS) && (NULL != PmicPwronProtocol))
  {
    Status |= PmicPwronProtocol->EnableEdgePonTrigger(PM_DEVICE_0, bit_type, bFlag);
  }
  else
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Error locating Pwron Protocol = %r \r\n", __FUNCTION__, Status));
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_GetIPCStatus(EFI_PM_GLINK_LINK_STATUS *PmicGLinkStatus)
{
  EFI_STATUS  Status            = EFI_SUCCESS;

  if (NULL == PmicGLinkStatus)
    return EFI_INVALID_PARAMETER;

  if (!gEnableChargerFW)
  {
    PmicGLinkStatus->IsPMICChannelOpen = FALSE;
    return Status;
  }
  /* Return If Link is not up */
  if(NULL == pmicGlinkProtocol)
  {
    Status = gBS->LocateProtocol (&gpmicGlinkProtocolGuid,NULL, (VOID **) &pmicGlinkProtocol);
    if((EFI_SUCCESS != Status) || (NULL == pmicGlinkProtocol))
    {
      CHARGER_DEBUG(( EFI_D_ERROR, "ChargerLib:: %a pmicGlinkProtocol Failed %r \r\n", __FUNCTION__, Status));
      return EFI_UNSUPPORTED;
    }
  }

  Status |= pmicGlinkProtocol->LinkStatus(PmicGLinkStatus);
  if(EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "ChargerLib:: %a pmicGlinkProtocol Failed %r \r\n", __FUNCTION__, Status));
  }
  return Status;

}

EFI_STATUS ChargerLibTarget_GetIPCError(CHARGERLIB_CHARGING_ERROR_TYPES  *pChargingError)
{
  EFI_STATUS               Status          = EFI_SUCCESS;
  EFI_PM_GLINK_LINK_STATUS PmicGLinkStatus = { 0 };

  if(NULL == pChargingError)
    return EFI_INVALID_PARAMETER;
  
/* Check it in ChargerLib_GetErrors() */
/*
  if (!gEnableChargerFW)
  {
    *pChargingError = CHARGERLIB_CHARGING_FW_LINK_ERROR;
    return Status;
  }
*/
  Status = ChargerLibTarget_GetIPCStatus(&PmicGLinkStatus);

  if((EFI_SUCCESS != Status) || (PmicGLinkStatus.IsPMICChannelOpen == FALSE))
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "ChargerLib:: %a Glink Channel is not Open = %r Open = %d \r\n", __FUNCTION__, Status, PmicGLinkStatus.IsPMICChannelOpen));
    *pChargingError = CHARGERLIB_CHARGING_FW_LINK_ERROR;
    return Status;
  }
  else
  {
    /* Glink channel is open and connected */
    *pChargingError = CHARGERLIB_CHARGING_ERROR_NONE;
  }

  return Status;

}

#define QCOM_CHARGER_FW_PARTITION_STRING_W L"modem_a"
#define QCOM_CHARGER_FW_PARTITION_STRING   "modem_a"

EFI_STATUS ChargerLibTarget_LoadChargerFW()
{
  EFI_PIL_PROTOCOL  *PILProtocol = NULL;
  EFI_STATUS         Status      = EFI_SUCCESS;

  if (!gEnableChargerFW)
  {
    return Status;
  }
  Status = gBS->LocateProtocol (&gEfiPilProtocolGuid,NULL, (VOID **) &PILProtocol);
  if ((EFI_SUCCESS != Status) && (NULL == PILProtocol))
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "ChargerLib:: %a %r \r\n", __FUNCTION__, Status));
    return Status;
  }

  Status = ChargerLibTarget_SetOS(OS_BOOTLOADER);
  if (EFI_SUCCESS != Status)
  {
    return Status;
  }

  Status |= MountFatPartition(QCOM_CHARGER_FW_PARTITION_STRING_W);
  CHARGER_DEBUG(( EFI_D_ERROR, "MountFatPartition %r \r\n", Status));

   Status = PILProtocol->ProcessPilImage(L"FULL_ADSP");
  CHARGER_DEBUG(( EFI_D_ERROR, "ChargerLib:: %a ProcessPilImageExt = %r \r\n", __FUNCTION__, Status));

  return Status;

}

EFI_STATUS ChargerLibTarget_LinkChargerFW()
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PMIC_GLINK_PROTOCOL  *pmicGlinkProtocol = NULL;
  //EFI_PM_GLINK_BATT_STATUS_INFO BattStsInfo = {0};
  UINT32 count =0;
  EFI_PM_GLINK_LINK_STATUS PmicGLinkStatus = { 0 };

  if (!gEnableChargerFW)
  {
    return Status;
  }

  if(NULL == pmicGlinkProtocol)
  {
   Status = gBS->LocateProtocol (&gpmicGlinkProtocolGuid,NULL, (VOID **) &pmicGlinkProtocol);
   if((EFI_SUCCESS != Status) && (NULL == pmicGlinkProtocol))
   {
     CHARGER_DEBUG(( EFI_D_ERROR, "ChargerLib:: %a pmicGlinkProtocol Failed %r \r\n", __FUNCTION__, Status));
     return Status;
   }
  }

  Status |= pmicGlinkProtocol->Connect();
  if(EFI_SUCCESS != Status)
  {
   CHARGER_DEBUG(( EFI_D_ERROR, "ChargerLib:: %a pmicGlinkProtocol Connect Failed %r \r\n", __FUNCTION__, Status));
   return Status;
  }
  else 
  {
   CHARGER_DEBUG(( EFI_D_WARN, "ChargerLib:: %a pmicGlinkProtocol Connect %r \r\n", __FUNCTION__, Status));
  }

  if(gChargerLibTargetCfgData.connect_glink_logging_channel){
    Status |= pmicGlinkProtocol->CpdlogConnect();
    if(EFI_SUCCESS != Status)
    {
      CHARGER_DEBUG(( EFI_D_ERROR, "ChargerLib:: %a PmicGlinkProtocol for ChargerPD Logging Connect Failed %r \r\n", __FUNCTION__, Status));
      return Status;
    }
    else
    {
      CHARGER_DEBUG(( EFI_D_WARN, "ChargerLib:: %a pmicGlinkProtocol for ChargerPD Logging Connect %r \r\n", __FUNCTION__, Status));
    }
  }

  /* Wait Till ADSP link comes up  */
  while (count < CHARGERLIB_IPC_MAX_LINK_WAIT_COUNT)
  {
    gBS->Stall(CHARGERLIB_IPC_LINK_WAIT_TIME);
    Status |= pmicGlinkProtocol->LinkStatus(&PmicGLinkStatus);
    if(EFI_SUCCESS != Status)
    {
      break;
    }
    if (PmicGLinkStatus.IsPMICChannelOpen == TRUE)
    {
      break;
    }
    CHARGER_DEBUG(( EFI_D_WARN, "ChargerLib:: %a PmicGLinkStatus = %d \r\n", __FUNCTION__, PmicGLinkStatus.IsPMICChannelOpen));
    count++;
  }

  /* Debug Check */
  //if(PmicGLinkStatus.IsPMICChannelOpen == TRUE)
  //{
    //Status |= pmicGlinkProtocol->GetBatteryStatus(BatteryIndex, &BattStsInfo);
    //if(EFI_SUCCESS == Status)
    //{
    //  //here the chargerpd is up and communication is good, so can deinit i2c on uefi side
    //  SmartChargerLibFG_Deinit();
    //  CHARGER_DEBUG(( EFI_D_ERROR, "ChargerLib:: %a turned off i2c_power, GetBatteryStatus = %r BatteryVoltage = %d v \r\n", __FUNCTION__, Status, BattStsInfo.BatteryVoltage));
    //}
    //else
    //{
    //CHARGER_DEBUG(( EFI_D_ERROR, "ChargerLib:: %a pmicGlinkProtocol Channel not open %r %d \r\n", __FUNCTION__, Status, PmicGLinkStatus.IsPMICChannelOpen));
    //}
  //}
  return Status;
}

EFI_STATUS ChargerLibTarget_DAMConnectSts(BOOLEAN *DAMConnectSts)
{
    EFI_STATUS Status = EFI_SUCCESS;

    if (!DAMConnectSts)
    {
        return EFI_INVALID_PARAMETER;
    }

    if (!PmicSchgProtocol)
    {
        Status = gBS->LocateProtocol(&gQcomPmicSchgProtocolGuid,
            NULL,
            (VOID **)&PmicSchgProtocol);
        if ((Status != EFI_SUCCESS) || (NULL == PmicSchgProtocol))
        {
            CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a pmicSchgProtocol Failed = %r \r\n", __FUNCTION__, Status));
            return EFI_DEVICE_ERROR;
        }
    }

    Status |= PmicSchgProtocol->GetDAMConnectSts(ChargerInfo.ChargerPmicInfo.PmicIndex, DAMConnectSts);
    return Status;
}

EFI_STATUS ChargerLibTarget_GetErrorAction( CHARGERLIB_CHARGING_ERROR_TYPES  ChargingErrorType, CHARGERLIB_ERROR_ACTION_TYPE *pErrorAction)
{
  EFI_STATUS  Status = EFI_SUCCESS;
  chargerlib_batt_status_info BatteryStatus = {0};

  if(!pErrorAction)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pErrorAction = CHARGERLIB_ERROR_ACTION_NONE;

  Status = ChargerLib_GetBatteryStatus(&BatteryStatus);
  if( EFI_SUCCESS != Status )
  {
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Error getting battery status = %r \r\n", __FUNCTION__, Status));
    return Status;
  }

  switch (ChargingErrorType)
  {
    case CHARGERLIB_CHARGING_ERROR_NONE:
    case CHARGERLIB_CHARGING_ERROR_TSENSE_OK:
        /* No Action just continue */
        gDispImage = CHARGERLIB_EVENT_DISP_IMAGE_LOWBATTERYCHARGING;
        break;
    case CHARGERLIB_CHARGING_ERROR_TSENSE_CRITICAL:
        // case ChargerLib_ChargingError_TsensCritical:
        gDispImage = CHARGERLIB_EVENT_DISP_IMAGE_TSENS_CRITICAL_SYMBOL;
    case CHARGERLIB_CHARGING_ERROR_BATT_TEMP_OUTSIDE_OPERATIONAL_RANGE:
        *pErrorAction = CHARGERLIB_ERROR_ACTION_CRITICAL_SHUTDOWN;
        break;
    case CHARGERLIB_CHARGING_ERROR_BATTERY_NOT_DETECTED:
        gDispImage = CHARGERLIB_EVENT_DISP_IMAGE_NOBATTERY;
        *pErrorAction = CHARGERLIB_ERROR_ACTION_SHUTDOWN;
        break;
    case CHARGERLIB_CHARGING_ERROR_LOW_VBATT:
        /* Emergency Low VBatt shutdown */
        gDispImage = CHARGERLIB_EVENT_DISP_IMAGE_NOBATTERY;
        *pErrorAction = CHARGERLIB_ERROR_ACTION_SHUTDOWN_USB_DC_PON_DISABLED;
        break;
    case CHARGERLIB_CHARGING_ERROR_TSENSE_TIMEOUT:
        gDispImage = CHARGERLIB_EVENT_DISP_IMAGE_TSENS_THERMAL_SYMBOL;
    case CHARGERLIB_CHARGING_ERROR_ADC_ERROR:
    case CHARGERLIB_CHARGING_ERROR_FG_ERROR:
    case CHARGERLIB_CHARGING_ERROR_VBATT_OUTSIDE_RANGE:
    case CHARGERLIB_CHARGING_ERROR_CHARGING_TIMEOUT:
    case CHARGERLIB_DEVICE_ERROR:
        *pErrorAction = CHARGERLIB_ERROR_ACTION_SHUTDOWN;
        break;
    case CHARGERLIB_CHARGING_ERROR_CHARGING_SOURCE_NOT_DETECTED:
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a FW_mode : %d\r\n", __FUNCTION__, gChargerSharedInfo.uefi_charger_fw_mode));
        if(gChargerLibTargetCfgData.soc_based_boot == TRUE)
        {
          if(BatteryStatus.StateOfCharge < gChargerLibTargetCfgData.boot_to_hlos_threshold_in_soc)
          {
            gDispImage = CHARGERLIB_EVENT_DISP_IMAGE_NOCHARGER;
            *pErrorAction = CHARGERLIB_ERROR_ACTION_SHUTDOWN;
          }
          else
          {//if already reached threshold,it's not an error and goot to boot
            *pErrorAction = CHARGERLIB_ERROR_ACTION_GOOD_TO_BOOT;
          }
        }
        else
        {
          if ((gChargerLibTargetCfgData.boot_to_hlos_threshold_in_mv + gChargerLibTargetCfgData.vbatt_threshold_margin_in_mv) > BatteryStatus.Ocv)
          {
              gDispImage = CHARGERLIB_EVENT_DISP_IMAGE_NOCHARGER;
              *pErrorAction = CHARGERLIB_ERROR_ACTION_SHUTDOWN;
          }
          else
          {
            if(gChargerSharedInfo.uefi_charger_fw_mode == 1)
                *pErrorAction = CHARGERLIB_ERROR_ACTION_RESET_COLD;
            else
                *pErrorAction = CHARGERLIB_ERROR_ACTION_GOOD_TO_BOOT;
          }
        }
        break;
    case CHARGERLIB_CHARGING_ERROR_BATT_TEMP_OUTSIDE_CHARGING_RANGE:
        if(gChargerLibTargetCfgData.soc_based_boot == TRUE)
        {
          if(BatteryStatus.StateOfCharge < gChargerLibTargetCfgData.boot_to_hlos_threshold_in_soc)
          {
            *pErrorAction = CHARGERLIB_ERROR_ACTION_NO_CHARGE_WAIT;
          }
          else
          {//if already reached threshold,it's not an error and goot to boot
            *pErrorAction = CHARGERLIB_ERROR_ACTION_GOOD_TO_BOOT;
            CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a Temp outside charging range good soc boot to hlos \r\n", __FUNCTION__));
          }
        }
        else
        {
          if(BatteryStatus.BatteryVoltage < gChargerLibTargetCfgData.boot_to_hlos_threshold_in_mv)
          {
            *pErrorAction = CHARGERLIB_ERROR_ACTION_NO_CHARGE_WAIT;
          }
          else
          {
            if(gChargerSharedInfo.uefi_charger_fw_mode == 1)
                *pErrorAction = CHARGERLIB_ERROR_ACTION_RESET_COLD;
            else
               *pErrorAction = CHARGERLIB_ERROR_ACTION_GOOD_TO_BOOT;
          }
        }
        break;
    case CHARGERLIB_CHARGING_ERROR_TSENSE_HIGH:
        *pErrorAction = CHARGERLIB_ERROR_ACTION_TSENSE_HIGH_WAIT;
        break;
    case CHARGERLIB_CHARGING_ERROR_DEBUG_BOARD:
        Status = ChargerLibTarget_GetDebugBoardAction(pErrorAction);
        break;
    case CHARGERLIB_CHARGING_ERROR_UNKNOWN_BATTERY:
        Status = ChargerLibTarget_GetUnknownBatteryAction(pErrorAction);
        break;
     default:
        *pErrorAction = CHARGERLIB_ERROR_ACTION_STOP_CHARGING;
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a default action stop charging %d \r\n", __FUNCTION__, *pErrorAction));
        break;
  }

  return Status;
}

EFI_STATUS ChargerLibTarget_HandleRecovery()
{
  EFI_STATUS       Status    = EFI_SUCCESS;
  STATIC BOOLEAN firstTime = TRUE;
  
  /* TBD to handle recovery - use USBPWRCtrl to read and print status */
  if (firstTime)
  {
  	Status = ChargerLibTarget_InitializeCharging();
	firstTime = FALSE;
  }
  return Status;
}

EFI_STATUS ChargerLibTarget_SetDAMIcl(DAM_SEL_ICL DAMIcl)
{
    EFI_STATUS Status = EFI_SUCCESS;
    return Status;
}


EFI_STATUS ChargerLibTarget_GetChargerInputStatus(CHARGERLIB_CHARGER_INPUT_STATUS *pChargerInputStatus)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_SCHG_ICL_STATUS pmschg_icl_status = {0};

  //NULL Check
  if(pChargerInputStatus == NULL)
    return EFI_INVALID_PARAMETER;

  //Reset Parameter
  pChargerInputStatus->bAiclDone = FALSE;
  pChargerInputStatus->ICLMaxMa = 0;
  pChargerInputStatus->ICLfinalMa = 0;

  switch (ChargerInfo.ChargerHW)
  {
  case EfiBatteryChargerQcomPmicSchg:
    if (!PmicSchgProtocol)
    {
      Status = gBS->LocateProtocol(&gQcomPmicSchgProtocolGuid,
                                   NULL,
                                   (VOID **)&PmicSchgProtocol);

      if((Status != EFI_SUCCESS) || (NULL == PmicSchgProtocol ))
      {
        CHARGER_DEBUG((EFI_D_WARN,"ChargerLib:: %a pmicSchgProtocol Failed = %r \r\n", __FUNCTION__, Status));
        return EFI_DEVICE_ERROR;
      }
    }
    Status = PmicSchgProtocol->GetIclStatus(ChargerInfo.ChargerPmicInfo.PmicIndex, &pmschg_icl_status);
    break;
  default:
    Status = EFI_UNSUPPORTED;
    break;
  }

  if(Status == EFI_SUCCESS)
  {
    pChargerInputStatus->bAiclDone = (pmschg_icl_status.aicl_done > 0)? TRUE:FALSE;
    pChargerInputStatus->ICLMaxMa = pmschg_icl_status.max_icl_status;
    pChargerInputStatus->ICLfinalMa = pmschg_icl_status.final_icl_status;
  }
  return Status;
}

EFI_STATUS ChargerLibTarget_GetUsbcPortType(CHARGERLIB_CHG_USBC_SINK_TYPE *pUsbcPortType)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_SCHG_TYPEC_PORT_STATUS UsbcStatus;

  //NULL Check
  if(pUsbcPortType == NULL)
    return EFI_INVALID_PARAMETER;

  //Reset Parameter
  *pUsbcPortType = CHARGERLIB_CHG_USBC_SINK_NONE;

  switch (ChargerInfo.ChargerHW)
  {
  case EfiBatteryChargerQcomPmicSchg:
    if (!PmicSchgProtocol)
    {
      Status = gBS->LocateProtocol(&gQcomPmicSchgProtocolGuid,
                                   NULL,
                                   (VOID **)&PmicSchgProtocol);

      if((Status != EFI_SUCCESS) || (NULL == PmicSchgProtocol ))
      {
        CHARGER_DEBUG((EFI_D_WARN,"ChargerLib:: %a pmicSchgProtocol Failed = %r \r\n", __FUNCTION__, Status));
        return EFI_DEVICE_ERROR;
      }
    }
    Status = PmicSchgProtocol->GetPortState(ChargerInfo.ChargerPmicInfo.PmicIndex, &UsbcStatus);
    break;
  default:
    Status = EFI_UNSUPPORTED;
    break;
  }

  if(Status == EFI_SUCCESS)
  {
    switch (UsbcStatus.dfp_curr_adv)
    {
    case EFI_PM_SCHG_TYPEC_DFP_CURR_ADV_3A:
      *pUsbcPortType = CHARGERLIB_CHG_USBC_SINK_3P0A;
      break;
    case EFI_PM_SCHG_TYPEC_DFP_CURR_ADV_1P5A:
      *pUsbcPortType = CHARGERLIB_CHG_USBC_SINK_1P5A;
      break;
    case EFI_PM_SCHG_TYPEC_DFP_CURR_ADV_STD:
      *pUsbcPortType = CHARGERLIB_CHG_USBC_SINK_DFAULT;
      break;
    default:
      *pUsbcPortType = CHARGERLIB_CHG_USBC_SINK_NONE;
      break;
    }
  }

  CHARGER_FILE_UART_DEBUG((EFI_D_WARN,"ChargerLib:: %a Charger Usbc Sink Port type = %d \r\n", __FUNCTION__, *pUsbcPortType));

  return Status;
}

EFI_STATUS ChargerLibTarget_GetDisplayImageType(CHARGERLIB_EVENT_DISP_IMAGE_TYPE *pDispImage)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(NULL == pDispImage)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pDispImage = gDispImage;

  CHARGER_DEBUG((EFI_D_WARN,"ChargerLib:: %a Display Image type = %d \r\n", __FUNCTION__, *pDispImage));

  return Status;
}


/**
  This function sets ChargerPD logging level and categories via PMIC GLINK  
  
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_CpdlogSetProperties(UINT64 categories, UINT32 level)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_GLINK_LINK_STATUS      PmicGLinkStatus = { 0 };

  if((EFI_SUCCESS == pmicGlinkProtocol->CpdlogLinkStatus(&PmicGLinkStatus)) && (PmicGLinkStatus.IsPMICChannelOpen == TRUE)){
    Status = pmicGlinkProtocol->CpdlogSetProperties(categories,level);

    if (Status != EFI_SUCCESS)
    {
      CHARGER_DEBUG((EFI_D_ERROR, "QcomChargerDxe:: %a Set ChargerPD Logging Properties failed \r\n", __FUNCTION__));
    }
  } 
  
  return Status;
}


/**
  This function gets ChargerPD logging categories from SDAM  
  
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_CpdlogGetProperty(UINT64* LogCategories)
{
  EFI_STATUS Status = EFI_SUCCESS;
  if (!PmicSchgProtocol)
  {
    Status |= gBS->LocateProtocol( &gQcomPmicSchgProtocolGuid,
                                  NULL,
                                  (VOID **)&PmicSchgProtocol );
  }

  if((EFI_SUCCESS == Status ) && (NULL != PmicSchgProtocol))
  {
    Status |= PmicSchgProtocol->GetLogCategoriesFromSdam(LogCategories);

    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Log Categories read From Sdam is %ld \r\n", __FUNCTION__, *LogCategories));
  }
  
  return Status;
}


/**
  This function gets ChargerPD log Buffer via PMIC GLINK   
  
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_CpdlogGetBuffer(UINT32 maxSize)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_GLINK_LINK_STATUS      PmicGLinkStatus = { 0 };
  
  char received_buff[CPDLOG_READ_MAX_BUFFER_SIZE];
  char received_buff_modified[256];
  uint32 buff_index=0, counter=0, copy_size=0;
  size_t received_buff_size=0;

  memset(received_buff, '\0', CPDLOG_READ_MAX_BUFFER_SIZE);

  if ((EFI_SUCCESS == pmicGlinkProtocol->CpdlogLinkStatus(&PmicGLinkStatus)) && (PmicGLinkStatus.IsPMICChannelOpen == TRUE)){ 
    
    Status = pmicGlinkProtocol->CpdlogGetBuffer(maxSize, received_buff);
    if (Status != EFI_SUCCESS)
    {
      CHARGER_DEBUG((EFI_D_ERROR, "QcomChargerDxe:: %a Get ChargerPD Logs failed \r\n", __FUNCTION__));
      return Status;
    }
    
    received_buff_size= strlen(received_buff);   
    
    if(received_buff_size == 0){
      CHARGER_DEBUG((EFI_D_WARN, "ChargerPD Ulog is Empty\r\n"));
      return Status;
    }

    CHARGER_DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_process_rx_data::****Received ChargerPD Logs of size %d****\r\n", received_buff_size));
    
    while(counter < received_buff_size){
      if(received_buff[counter] == '\n' || received_buff[counter] == '\0'){
        copy_size = (counter - buff_index) + 1; 
        if(copy_size<MAX_MSG_LENGTH){
          memset(received_buff_modified, '\0', 256);
          strlcpy(received_buff_modified, &received_buff[buff_index], copy_size); //Strlcpy copies 1 byte less than the #of bytes specified
          CHARGER_LOG_DEBUG((EFI_D_WARN, "%a\r\n", received_buff_modified));  //(copy_size+1) will copy '\n' from the ulog. So no need for including '\n' while printing 
          buff_index += copy_size;
        }
        else{
          while(buff_index < counter){  
            copy_size = (copy_size > MAX_MSG_LENGTH) ? MAX_MSG_LENGTH : (counter - buff_index)+1;
            memset(received_buff_modified, '\0', 256);
            if(copy_size <= MAX_MSG_LENGTH)
            {
              strlcpy(received_buff_modified, &received_buff[buff_index], copy_size); //Strlcpy copies 1 byte less than the #of bytes specified
              CHARGER_LOG_DEBUG((EFI_D_WARN, "%a", received_buff_modified)); 
              buff_index += copy_size;
            }
            else
            {
              CHARGER_LOG_DEBUG((EFI_D_WARN, "copy size greater than buffer, buffer_index = %d not copied", buff_index)); 
            }
            
            
          }
          CHARGER_LOG_DEBUG((EFI_D_WARN, "\r\n")); 
        }    
      }   
      counter++; 
    }
  }
  return Status;
}


/**
  This function gets QBG device context dump via PMIC GLINK  
  
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_CpdlogGetQbgDump()
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_GLINK_LINK_STATUS      PmicGLinkStatus = { 0 };
  EFI_PM_FG_BATT_TYPE           battery_type = BATTERY_1S;
  uint32 received_qbg_dump[MAX_QBG_DUMP_SIZE];
  uint32 received_qbg_dump_size = 0; 
  uint32 counter = 0;
  uint32 cell_count = 1;

  ChargerLibTarget_GetBatteryCellType(&battery_type);
  switch(battery_type)
  {
    case BATTERY_1S:
      cell_count = 1;
      break;
    case BATTERY_2S:
    case BATTERY_2P:
      cell_count = 2;
      break;
    case BATTERY_3S:
      cell_count = 3;
      break;
    default:
      cell_count = 1;
      break;
  }

  if((EFI_SUCCESS == pmicGlinkProtocol->CpdlogLinkStatus(&PmicGLinkStatus)) && (PmicGLinkStatus.IsPMICChannelOpen == TRUE))
  {    
    CHARGER_LOG_DEBUG((EFI_D_WARN, "*****QBG deviceContext Dump @ %lld*********\r\n", ChargerLib_CalculateTime()));    
    for (uint32 cell_idx = 0; cell_idx < cell_count; cell_idx++)
    {
        memset(received_qbg_dump, 0, MAX_QBG_DUMP_SIZE);
        counter = 0;
        Status = pmicGlinkProtocol->CpdlogGetQbgDump(&received_qbg_dump_size, received_qbg_dump, cell_idx);

        if (Status != EFI_SUCCESS)
        {
          CHARGER_DEBUG((EFI_D_ERROR, "QcomChargerDxe:: %a Get ChargerPD Qbg Device context Dump failed\r\n", __FUNCTION__));
          return Status;
        }
          
        if(received_qbg_dump_size > 0){ 
          CHARGER_LOG_DEBUG((EFI_D_WARN, "*********Cell [%d]*********\r\n", cell_idx));
          while(counter < received_qbg_dump_size){
            CHARGER_LOG_DEBUG((EFI_D_WARN, "%08x, ", received_qbg_dump[counter]));
            counter++;

            if(counter%4 == 0)
              CHARGER_LOG_DEBUG((EFI_D_WARN, "\r\n")); //formatting to 4 elements per line 
          }
        }
        CHARGER_LOG_DEBUG((EFI_D_WARN, "\r\n"));
    }
    
    CHARGER_LOG_DEBUG((EFI_D_WARN, "*****end of QBG device context dump*********\r\n"));

  } 
  
  return Status;
}


/**
  This function toggles value for LED based on Charging state read from PMIC using PmicSchgProtocol
  
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_GetChargingStateForLed(BOOLEAN *pToggleLed)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_SCHG_CHARGING_STATUS battChgrStatus = {0};
  
  if(!pToggleLed)
    return EFI_INVALID_PARAMETER;

  switch (ChargerInfo.ChargerHW)
  {
    case EfiBatteryChargerQcomPmicSchg:
      // Locate SCHG Protocol 
      if (!PmicSchgProtocol)
      {
        Status |= gBS->LocateProtocol( &gQcomPmicSchgProtocolGuid,
                                      NULL,
                                      (VOID **)&PmicSchgProtocol );
      }

      if((EFI_SUCCESS == Status ) && (NULL != PmicSchgProtocol))
      {
        Status |= PmicSchgProtocol->GetChargingStatus(ChargerInfo.ChargerPmicInfo.PmicIndex, &battChgrStatus);

        if(EFI_SUCCESS == Status )
        {
          *pToggleLed = battChgrStatus.bChargingEnabled;
          
          CHARGER_DEBUG((EFI_D_INFO,"ChargerLib:: %a pToggleLed value set is %d \r\n", __FUNCTION__, *pToggleLed));  
        }
      }
      break;

    default:
      break;
  }

  return Status;
}

/**
  This function send HLOS shutdown notification via PMIC GLINK  
  
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_SendShdnNotification()
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_GLINK_LINK_STATUS      PmicGLinkStatus = { 0 };

  if((EFI_SUCCESS == ChargerLibTarget_GetIPCStatus(&PmicGLinkStatus)) && (PmicGLinkStatus.IsPMICChannelOpen == TRUE)){
    CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a use PmicGlink \r\n",__FUNCTION__));
    Status = pmicGlinkProtocol->SendShdnNotification();
    if (Status != EFI_SUCCESS)
    {
      CHARGER_DEBUG((EFI_D_ERROR, "QcomChargerDxe:: %a Send Shutdown Notification failed \r\n", __FUNCTION__));
    }
  }
  return Status;
}

EFI_STATUS ChargerLibTarget_SetOS(CHARGERLIB_OS_TYPE OS)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (OS >= OS_INVALID)
      return EFI_INVALID_PARAMETER;

  if(!PmicSchgProtocol)
  {
      Status = gBS->LocateProtocol(&gQcomPmicSchgProtocolGuid, NULL, (VOID **)&PmicSchgProtocol);
  }

  if((NULL == PmicSchgProtocol ) || (Status != EFI_SUCCESS))
      return EFI_DEVICE_ERROR;

  if (OS >= OS_INVALID)
      return EFI_INVALID_PARAMETER;

  Status = PmicSchgProtocol->SetOS((EFI_PM_SCHG_OS_TYPE)OS);
  if (EFI_SUCCESS != Status)
  {
      CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib:: %a  SetOS failed, Error[%r] \r\n", __FUNCTION__, Status));
      return Status;
  }

  CHARGER_DEBUG((EFI_D_WARN, "ChargerLib:: %a  SetOS = %d \r\n", __FUNCTION__, OS));
  return Status;

}

EFI_STATUS ChargerLibTarget_GetBatteryCellType(EFI_PM_FG_BATT_TYPE *battery_cell_type)
{
  EFI_STATUS Status = EFI_SUCCESS;

  //NULL Check
  if(battery_cell_type == NULL)
    return EFI_INVALID_PARAMETER;

  //Reset Parameter
  *battery_cell_type = BATTERY_1S;

    if (!PmicFgProtocol)
    {
      Status = gBS->LocateProtocol(&gQcomPmicFgProtocolGuid,
                                   NULL,
                                   (VOID **)&PmicFgProtocol);

      if((Status != EFI_SUCCESS) || (NULL == PmicFgProtocol ))
      {
        CHARGER_DEBUG((EFI_D_WARN,"ChargerLib:: %a PmicFgProtocol Failed = %r \r\n", __FUNCTION__, Status));
        return EFI_DEVICE_ERROR;
      }
    }
    Status = PmicFgProtocol->FgBasicGetPmicInfo(&BatteryGaugeInfo.BatteryGaugePmicInfo);
    Status |= PmicFgProtocol->QBGGetBatteryType(BatteryGaugeInfo.BatteryGaugePmicInfo.PmicIndex, battery_cell_type);

  CHARGER_FILE_UART_DEBUG((EFI_D_WARN,"ChargerLib:: %a battery cell type = %d \r\n", __FUNCTION__, *battery_cell_type));

  return Status;

}


/**
  This function gets ChargerPD init log Buffer via PMIC GLINK   
  
  EFI_SUCCESS:           Function returned successfully.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_UNSUPPORTED:       No Library function linked
*/
EFI_STATUS ChargerLibTarget_CpdlogGetInitBuffer(UINT32 maxSize)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_GLINK_LINK_STATUS      PmicGLinkStatus = { 0 };
  
  char received_buff[CPDLOG_READ_MAX_BUFFER_SIZE];
  char received_buff_modified[256];
  uint32 buff_index=0, counter=0, copy_size=0;
  size_t received_buff_size=0;

  memset(received_buff, '\0', CPDLOG_READ_MAX_BUFFER_SIZE);

  if ((EFI_SUCCESS == pmicGlinkProtocol->CpdlogLinkStatus(&PmicGLinkStatus)) && (PmicGLinkStatus.IsPMICChannelOpen == TRUE)){ 
    
    Status = pmicGlinkProtocol->CpdlogGetInitBuffer(maxSize, received_buff);
    if (Status != EFI_SUCCESS)
    {
      CHARGER_DEBUG((EFI_D_ERROR, "QcomChargerDxe:: %a Get ChargerPD Init Logs failed \r\n", __FUNCTION__));
      return Status;
    }
    
    received_buff_size= strlen(received_buff);   
    
    if(received_buff_size == 0){
      CHARGER_DEBUG((EFI_D_WARN, "ChargerPD Init Ulog is Empty\r\n"));
      return EFI_END_OF_FILE;
    }

    CHARGER_DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_process_rx_data::****Received ChargerPD Init Logs of size %d****\r\n", received_buff_size));
    
    while(counter < received_buff_size){
      if(received_buff[counter] == '\n' || received_buff[counter] == '\0'){
        copy_size = (counter - buff_index) + 1; 
        if(copy_size<MAX_MSG_LENGTH){
          memset(received_buff_modified, '\0', 256);
          strlcpy(received_buff_modified, &received_buff[buff_index], copy_size); //Strlcpy copies 1 byte less than the #of bytes specified
          CHARGER_LOG_DEBUG((EFI_D_WARN, "%a\r\n", received_buff_modified));  //(copy_size+1) will copy '\n' from the ulog. So no need for including '\n' while printing 
          buff_index += copy_size;
        }
        else{
          while(buff_index < counter){  
            copy_size = (copy_size > MAX_MSG_LENGTH) ? MAX_MSG_LENGTH : (counter - buff_index)+1;
            memset(received_buff_modified, '\0', 256);
            if(copy_size <= MAX_MSG_LENGTH)
            {
              strlcpy(received_buff_modified, &received_buff[buff_index], copy_size); //Strlcpy copies 1 byte less than the #of bytes specified
              CHARGER_LOG_DEBUG((EFI_D_WARN, "%a", received_buff_modified)); 
              buff_index += copy_size;
            }
            else
            {
              CHARGER_LOG_DEBUG((EFI_D_WARN, "copy size greater than buffer, buffer_index = %d not copied", buff_index)); 
            }
            
            
          }
          CHARGER_LOG_DEBUG((EFI_D_WARN, "\r\n")); 
        }    
      }   
      counter++; 
    }
  }
  return Status;
}
