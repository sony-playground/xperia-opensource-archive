/*=============================================================================
 
  File: MDPPlatformLib.c
 
  MDP platform specific functions
  
  Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include <PlatformInfo.h>
#include <Library/PcdLib.h>
#include <api/pmic/pm/pm_lcdb.h>
#include <api/pmic/pm/pm_wled.h>
#include <api/pmic/pm/pm_ldo.h>
#include <api/pmic/pm/pm_pwm.h>
#include <api/pmic/pm/pm_gpio.h>
#include <api/pmic/pm/pm_smps.h>
#include <api/pmic/pm/pm_boot.h>
#include <api/pmic/pm/pm_version.h>
#include "MDPTypes.h"
#include "MDPPlatformLib.h"
#include "MDPSystem.h"
#include "DDITlmm.h"
#include "pmapp_npa.h"
#include "npa.h"
#include "boot_extern_platforminfo_interface.h"
#include "HALDSILib.h"

/* -----------------------------------------------------------------------
** Defines
** ----------------------------------------------------------------------- */
#define PCD_PANEL_TYPE_OEM                1

#define DSI_READ_ADDRESS_SIZE             2
#define DSI_READ_READBACK_SIZE            8

#define PLATFORM_PANEL_ID_MAX_COMMANDS    3       // maximum panel ID read commands

#define PMIC_IBBLAB_READYTIME             25      // Maximum of milliseconds to wait for IBB/LAB to stabilize (Can be up to 8.8ms +/-16%)

// Main panel CDP/MTP specific defines
#define CDP_DISP_RESET_GPIO                0       // GPIO number for LCD0_RESET
#define CDP_DISP_TE_GPIO                   86      // GPIO number for TE
#define CDP_DISP_LCD_REG_EN                186     // GPIO for LCD internal boost power
#define CDP_DISP_LCD_BKLT_EN               187     // GPIO for backlight enable
#define CDP_SEC_DISP_RESET_GPIO            4       // GPIO number for LCD0_RESET on secondary display
#define CDP_SEC_DISP_TE_GPIO               87      // GPIO number for TE on secondary display

#define DSI_WRITE_BACKLIGHT_SIZE           3

#define DISP_DIV_ROUND_UP(x, y) (((x) + (y/2)) / (y))

// Get reset gpio based on display id
#define GET_CDP_DISP_RESET_GPIO(_displayId_)  (((_displayId_) == MDP_DISPLAY_SECONDARY) ? CDP_SEC_DISP_RESET_GPIO : CDP_DISP_RESET_GPIO)

// Get te gpio based on display id
#define GET_CDP_DISP_TE_GPIO(_displayId_)     (((_displayId_) == MDP_DISPLAY_SECONDARY) ? CDP_SEC_DISP_TE_GPIO : CDP_DISP_TE_GPIO)

/* Return the a specific panel's configuration
 */
#define GET_PANEL_CONFIG(_id_)                (&asPanelConfig[((_id_)<MDP_DISPLAY_MAX)?(_id_):0])

/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */

/* Panel backlight DCS command
 */ 
typedef struct {
  uint8      uCmdType;                                                                // DCS command type for backlight control
  uint8      command[DSI_WRITE_BACKLIGHT_SIZE];                                       // DCS command for backlight control
} PlatformPanelBacklightControl;

/* -----------------------------------------------------------------------
** Local functions
** ----------------------------------------------------------------------- */

/* Platform detection 
*/
static MDP_Status ReadPlatformIDAndChipID(EFI_PLATFORMINFO_PLATFORM_INFO_TYPE *pPlatformInfo, EFIChipInfoIdType *pChipSetId, EFIChipInfoFamilyType *pChiSetFamily);


/* Main Panel CDP/MTP Functions
*/
static MDP_Status Panel_CDP_PowerUp(MDP_Display_IDType eDisplayId);
static MDP_Status Panel_CDP_PowerDown(MDP_Display_IDType eDisplayId);
static MDP_Status Panel_CDP_Reset(MDP_Display_IDType eDisplayId);
static MDP_Status Panel_CDP_BacklightLevel(MDP_Display_IDType eDisplayId, BacklightConfigType *pBacklightConfig);

/* General helper functions */
MDP_Status SetDefaultGPIOState(GpioStateType *pGPIOList);


/*===========================================================================
 Local Configuration Definitions
 ===========================================================================*/
/******************************************************************
 *                   R66451 FHD Plus Panel                        *
 *                                                                *
 *                   R66451 DDIC                                  *
 *                   1080x2340                                    *
 *                   Single-Dphy(DSI0)                            *
 *                   command mode DSC                             *
 ******************************************************************/
const static int8 r66451_sec_60hz_fhd_plus_dsc_cmd_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf - 8\"?>"
"<PanelName>R66451 Visionox</PanelName>"
"<PanelDescription>R66451 Visionox Single DSI DSC Command Mode Amoled Panel (1440x2560 24bpp)</PanelDescription>"
"<Group id=\"Active Timing\">"
"<HorizontalActive>1080</HorizontalActive>"
"<HorizontalFrontPorch>95</HorizontalFrontPorch>"
"<HorizontalBackPorch>40</HorizontalBackPorch>"
"<HorizontalSyncPulse>1</HorizontalSyncPulse>"
"<HorizontalSyncSkew>0</HorizontalSyncSkew>"
"<HorizontalLeftBorder>0</HorizontalLeftBorder>"
"<HorizontalRightBorder>0</HorizontalRightBorder>"
"<VerticalActive>2340</VerticalActive>"
"<VerticalFrontPorch>25</VerticalFrontPorch>"
"<VerticalBackPorch>4</VerticalBackPorch>"
"<VerticalSyncPulse>1</VerticalSyncPulse>"
"<VerticalSyncSkew>0</VerticalSyncSkew>"
"<VerticalTopBorder>0</VerticalTopBorder>"
"<VerticalBottomBorder>0</VerticalBottomBorder>"
"<InvertDataPolarity>False</InvertDataPolarity>"
"<InvertVsyncPolairty>False</InvertVsyncPolairty>"
"<InvertHsyncPolarity>False</InvertHsyncPolarity>"
"<BorderColor>0x0</BorderColor>"
"</Group>"
"<Group id=\"Display Interface\">"
"<InterfaceType>9</InterfaceType>"
"<InterfaceColorFormat>3</InterfaceColorFormat>"
"</Group>"
"<Group id=\"DSI Interface\">"
"<DSIChannelId>2</DSIChannelId>"
"<DSIVirtualId>0</DSIVirtualId>"
"<DSIColorFormat>36</DSIColorFormat>"
"<DSITrafficMode>1</DSITrafficMode>"
"<DSILanes>4</DSILanes>"
"<DSICmdSwapInterface>False</DSICmdSwapInterface>"
"<DSITECheckEnable>True</DSITECheckEnable>"
"<DSITEUsingDedicatedTEPin>True</DSITEUsingDedicatedTEPin>"
"<DSITEvSyncStartPos>2340</DSITEvSyncStartPos>"
"<DSITEvSyncInitVal>2340</DSITEvSyncInitVal>"
"<DSIDSCEnable>True</DSIDSCEnable>"
"<DSIDSCMajor>1</DSIDSCMajor>"
"<DSIDSCMinor>1</DSIDSCMinor>"
"<DSIDSCScr>0</DSIDSCScr>"
"<DSIDSCProfileID>7</DSIDSCProfileID>"
"<DSIDSCSliceWidth>540</DSIDSCSliceWidth>"
"<DSIDSCSliceHeight>20</DSIDSCSliceHeight>"
"<DSILanes>4</DSILanes>"
"<DSIHsaHseAfterVsVe>False</DSIHsaHseAfterVsVe>"
"<DSILowPowerModeInHFP>False</DSILowPowerModeInHFP>"
"<DSILowPowerModeInHBP>False</DSILowPowerModeInHBP>"
"<DSILowPowerModeInHSA>False</DSILowPowerModeInHSA>"
"<DSILowPowerModeInBLLPEOF>True</DSILowPowerModeInBLLPEOF>"
"<DSILowPowerModeInBLLP>True</DSILowPowerModeInBLLP>"
"<DSIRefreshRate>0x3C0000</DSIRefreshRate>"
"<DSIDynamicRefreshRates>0x3B8000 0x3BC000 0x3C0000</DSIDynamicRefreshRates>"
"<DSICmdUsingTrigger>False</DSICmdUsingTrigger>"
"<DSIEnableAutoRefresh>True</DSIEnableAutoRefresh>"
"<DSIAutoRefreshFrameNumDiv>1</DSIAutoRefreshFrameNumDiv>"
"<DSIControllerMapping>"
"00"
"</DSIControllerMapping>"
"</Group>"
"<DSIInitSequence>"
"39 b0 00\n"
"39 d8 00 00 00 00 00 00 00 00 00 5b 00 5b 00 5b 00 5b 00 5b\n"
"39 b0 80\n"
"39 e6 00\n"
"39 b0 00\n"
"39 cf 64 0b 00 00 00 00 00 00 08 00 0b 77 01 01 01 01 01 01 04 04 04 04 04 05\n"
"39 b0 04\n"
"39 f7 01\n"
"39 df 50 40\n"
"39 f3 50 00 00 00 00\n"
"39 f2 11\n"
"39 f3 01 00 00 00 01\n"
"39 f4 00 02\n"
"39 f2 19\n"
"39 df 50 42\n"
"39 35 00\n"
"39 2a 00 00 04 37\n"
"39 2b 00 00 09 23\n"
"05 11\n"
"ff 78\n"
"05 29\n"
"</DSIInitSequence>"
"<DSITermSequence>"
"05 28\n"
"ff 14\n"
"05 10\n"
"ff 78\n"
"</DSITermSequence>"
"<Group id='Backlight Configuration'>"
"<BacklightType>3</BacklightType>"
"<BacklightBitWidth>12</BacklightBitWidth>"
"</Group>";

/******************************************************************
 *                   R66451 FHD Plus Panel                        *
 *                                                                *
 *                   R66451 DDIC                                  *
 *                   1080x2340                                    *
 *                   Single-Cphy(DSI0)                            *
 *                   command mode DSC                             *
 ******************************************************************/
const static int8 r66451_120hz_fhd_plus_dsc_cmd_cphy_xmldata[] = 
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>R66451 Visionox</PanelName>"
"<PanelDescription>R66451 Visionox Single DSI DSC Command Mode Amoled Cphy Panel (1080x2340 24bpp)</PanelDescription>"
"<Group id=\"Active Timing\">"
 "<HorizontalActive>1080</HorizontalActive>"
 "<HorizontalFrontPorch>96</HorizontalFrontPorch>"
 "<HorizontalBackPorch>40</HorizontalBackPorch>"
 "<HorizontalSyncPulse>32</HorizontalSyncPulse>"
 "<HorizontalSyncSkew>0</HorizontalSyncSkew>"
 "<HorizontalLeftBorder>0</HorizontalLeftBorder>"
 "<HorizontalRightBorder>0</HorizontalRightBorder>"
 "<VerticalActive>2340</VerticalActive>"
 "<VerticalFrontPorch>25</VerticalFrontPorch>"
 "<VerticalBackPorch>4</VerticalBackPorch>"
 "<VerticalSyncPulse>1</VerticalSyncPulse>"
 "<VerticalSyncSkew>0</VerticalSyncSkew>"
 "<VerticalTopBorder>0</VerticalTopBorder>"
 "<VerticalBottomBorder>0</VerticalBottomBorder>"
 "<InvertDataPolarity>False</InvertDataPolarity>"
 "<InvertVsyncPolairty>False</InvertVsyncPolairty>"
 "<InvertHsyncPolarity>False</InvertHsyncPolarity>"
 "<BorderColor>0x0</BorderColor>"
"</Group>"
"<Group id=\"Display Interface\">"
 "<InterfaceType>9</InterfaceType>"
 "<InterfaceColorFormat>3</InterfaceColorFormat>"
"</Group>"
"<Group id=\"DSI Interface\">"
 "<DSIChannelId>2</DSIChannelId>"
 "<DSIVirtualId>0</DSIVirtualId>"
 "<DSIColorFormat>36</DSIColorFormat>"
 "<DSITrafficMode>1</DSITrafficMode>"
 "<DSICPhyMode>True</DSICPhyMode>"
 "<DSICmdSwapInterface>False</DSICmdSwapInterface>"
 "<DSITECheckEnable>True</DSITECheckEnable>"
 "<DSITEUsingDedicatedTEPin>True</DSITEUsingDedicatedTEPin>"
 "<DSITEvSyncStartPos>2340</DSITEvSyncStartPos>"
 "<DSITEvSyncInitVal>2340</DSITEvSyncInitVal>"
 "<DSIDSCEnable>True</DSIDSCEnable>"
 "<DSIDSCMajor>1</DSIDSCMajor>"
 "<DSIDSCMinor>1</DSIDSCMinor>"
 "<DSIDSCScr>0</DSIDSCScr>"
 "<DSIDSCProfileID>7</DSIDSCProfileID>"
 "<DSIDSCSliceWidth>540</DSIDSCSliceWidth>"
 "<DSIDSCSliceHeight>20</DSIDSCSliceHeight>"
 "<DSIDSCSlicePerPacket>2</DSIDSCSlicePerPacket>"
 "<DSILanes>3</DSILanes>"
   "<DSIHsaHseAfterVsVe>False</DSIHsaHseAfterVsVe>"
   "<DSILowPowerModeInHFP>False</DSILowPowerModeInHFP>"
   "<DSILowPowerModeInHBP>False</DSILowPowerModeInHBP>"
   "<DSILowPowerModeInHSA>False</DSILowPowerModeInHSA>"
   "<DSILowPowerModeInBLLPEOF>True</DSILowPowerModeInBLLPEOF>"
   "<DSILowPowerModeInBLLP>True</DSILowPowerModeInBLLP>"
   "<DSIRefreshRate>0x780000</DSIRefreshRate>"
 "<DSICmdUsingTrigger>False</DSICmdUsingTrigger>"
 "<DSIEnableAutoRefresh>True</DSIEnableAutoRefresh>"
 "<DSIAutoRefreshFrameNumDiv>1</DSIAutoRefreshFrameNumDiv>"
 "<DSIControllerMapping>"
 "00"
 "</DSIControllerMapping>"
"</Group>"
"<DSIInitSequence>"
 "39 b0 00\n"
 "39 c2 09 24 0c 00 00 0c 00 00 00 09 3c\n"
 "39 d7 00 b9 3c 00 40 04 00 a0 0a 00 40 00 00 00 00 00 00 19 3c 00 40 04 00 a0 0a\n"
 "39 b0 80\n"
 "39 de 40 00 18 00 18 00 18 00 18 10 00 18 00 18 00 18 02 00 00\n"
 "39 b0 04\n"
 "39 e8 00 02\n"
 "39 e4 00 08\n"
 "39 b4 20 1c\n"
 "39 b6 6c 00 06 23 af 13 1a 05 04 fa 05 20\n"
 "39 b0 00\n"
 "39 c4 00 00 00 00 00 00 00 00 10 00 00 02 00 00 00 29 00 01 00 00 00 00 00 00 00 00 00 00 00 22 00 00 00 00 11 00 00 0c 00 00 00 00 30 00 00 00 00 00 00\n"
 "39 d3 49 00 00 01 1a 15 00 15 07 0f 77 77 77 37 b2 11 00 a0 3c 9a\n"
 "39 d8 00 00 00 00 00 00 00 00 00 3a 00 3a 00 3a 00 3a 00 3a 05 00 00 00 00 00 00 00 00 00 0f 00 0f 00 00 00 00 00 00 00 00 00 00 00 00 00 0f 00 2f 00 0f 00 20\n"
 "39 df 50 42 58 81 2d 00 00 00 00 00 00 6b 00 00 00 00 00 00 00 00 01 0f ff d4 0e 00 00 00 00 00 00 0f 53 18 00 0f 00 00 00 00 00 00\n"
 "39 eb 8b 8b\n"
 "39 f7 01\n"
 "39 b0 80\n"
 "39 e4 34 b4 00 00 00 30 04 0c e2\n"
 "39 e6 00\n"
 "39 b0 04\n"
 "39 df 50 40\n"
 "39 f3 50 00 00 00 00\n"
 "39 f2 11\n"
 "39 f3 01 00 00 00 01\n"
 "39 f4 00 02\n"
 "39 f2 19\n"
 "39 df 50 42\n"
 "39 35 00\n"
 "39 2a 00 00 04 37\n"
 "39 2b 00 00 09 23\n"
 "05 11\n"
 "ff 78\n"
 "05 29\n"
"</DSIInitSequence>\n"
"<DSITermSequence>\n"
 "05 28\n"
 "ff 14\n"
 "05 10\n"
 "ff 78\n"
"</DSITermSequence>\n"
"<Group id='Backlight Configuration'>\n"
 "<BacklightType>3</BacklightType>\n"
 "<BacklightBitWidth>12</BacklightBitWidth>\n"
 "<DisplayResetInfo>0 10 1000 10000 0</DisplayResetInfo>\n"
"</Group>\n";

/*
* Dummy panel configuration, default fallback mode.
*
*/
const static int8 dummy_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
" <PanelName>VirtioDSI</PanelName>"
" <PanelDescription>DSI Model (640x480 24bpp)</PanelDescription>"
" <Group id=\"Active Timing\">"
"  <HorizontalActive>640</HorizontalActive>"
"  <HorizontalFrontPorch>13</HorizontalFrontPorch>"
"  <HorizontalBackPorch>14</HorizontalBackPorch>"
"  <HorizontalSyncPulse>15</HorizontalSyncPulse>"
"  <VerticalActive>480</VerticalActive>"
"  <VerticalFrontPorch>11</VerticalFrontPorch>"
"  <VerticalBackPorch>12</VerticalBackPorch>"
"  <VerticalSyncPulse>13</VerticalSyncPulse>"
" </Group>"
" <Group id=\"Display Interface\">"
"  <InterfaceType>8</InterfaceType>"
"  <InterfaceColorFormat>3</InterfaceColorFormat>"
" </Group>"
" <Group id=\"DSI Interface\">"
"  <DSIChannelId>1</DSIChannelId>"     
"  <DSIVirtualId>0</DSIVirtualId>"     
"  <DSIColorFormat>36</DSIColorFormat>"     
"  <DSITrafficMode>0</DSITrafficMode>"
"  <DSILanes>2</DSILanes>"
"  <DSIHsaHseAfterVsVe>False</DSIHsaHseAfterVsVe>"
"  <DSILowPowerModeInHFP>False</DSILowPowerModeInHFP>"
"  <DSILowPowerModeInHBP>False</DSILowPowerModeInHBP>"
"  <DSILowPowerModeInHSA>False</DSILowPowerModeInHSA>"
"  <DSILowPowerModeInBLLPEOF>False</DSILowPowerModeInBLLPEOF>"
"  <DSILowPowerModeInBLLP>False</DSILowPowerModeInBLLP>"
"  <DSIRefreshRate>0x3c0000</DSIRefreshRate>" 
" </Group>"
" <DisplayPrimaryFlags>0x2</DisplayPrimaryFlags>"
" <DSIInitSequence>"
"  32 00 00\n"
" </DSIInitSequence>";

PanelConfigType        asPanelConfig[MDP_DISPLAY_MAX];

/*===========================================================================
Function Definitions
===========================================================================*/

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: PlatformClientInit()
** 
** DESCRIPTION:
**        Initialize NPA client
**
*//* -------------------------------------------------------------------- */
static MDP_Status PlatformClientInit(MDP_Display_IDType eDisplayId)
{
  MDP_Status    eStatus = MDP_STATUS_OK;

  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_PowerUp()
** 
** DESCRIPTION:
**        Panel power up sequence for CDP
**
*/ /* -------------------------------------------------------------------- */
static MDP_Status Panel_CDP_PowerUp(MDP_Display_IDType eDisplayId)
{
  MDP_Status          eStatus        = MDP_STATUS_OK;
  DALGpioSignalType   uGPIOCfg       = 0;
  uint32              uResetGpio     = GET_CDP_DISP_RESET_GPIO(eDisplayId);
  uint32              uTeGpio        = GET_CDP_DISP_TE_GPIO(eDisplayId);

  uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(uResetGpio, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_LOW_VALUE);
  Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);

  if (MDP_STATUS_OK != (eStatus =  PlatformClientInit(eDisplayId)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayLib: Failed to initialize handle for Primary display NPA node.\n");
  }
  else
  {
    DALGpioSignalType uGPIOCfg = 0;

    /* LDO1, LDO2 for DSI PHY/PLL are already turned on by system driver.*/

    /*Turn on LDO14 for V_LCD_VDDI_1P8 which is used by panel */
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_B, PM_LDO_5, 880000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO12 to 0.88V\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_C, PM_LDO_10, 1200000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO12 to 1.2V\n");
    }
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_D, PM_LDO_1, 1200000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO6 to 1.2V\n");
    }
    
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_C, PM_LDO_12, 1800000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO5 to 1.8V\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_C, PM_LDO_13, 3000000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO5 to 3.0V\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_B, PM_LDO_5, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO5\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_C, PM_LDO_10, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO10\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_D, PM_LDO_1, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO1\n");
    }
    
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_C, PM_LDO_12, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO12\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_C, PM_LDO_13, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO13\n");
    }

    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG(uTeGpio, 1, DAL_GPIO_INPUT, DAL_GPIO_NO_PULL, DAL_GPIO_LOW_VALUE);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);
  }

  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_PowerDown()
** 
** DESCRIPTION:
**        Panel power down sequence for CDP
**
*/ /* -------------------------------------------------------------------- */
static MDP_Status Panel_CDP_PowerDown(MDP_Display_IDType eDisplayId)
{
  MDP_Status          eStatus      = MDP_STATUS_OK;
  DALGpioSignalType   uGPIOCfg     = 0;  
  uint32              uResetGpio   = GET_CDP_DISP_RESET_GPIO(eDisplayId);

  uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(uResetGpio, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_LOW_VALUE);
  eStatus  = Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);
  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_Reset()
** 
** DESCRIPTION:
**        Panel reset sequence for CDP
**
*/ /* -------------------------------------------------------------------- */
MDP_Status Panel_CDP_Reset(MDP_Display_IDType eDisplayId)
{
  MDP_Status          eStatus     = MDP_STATUS_OK;
  DALGpioSignalType   uGPIOCfg    = 0;
  uint32              uResetGpio   = GET_CDP_DISP_RESET_GPIO(eDisplayId);

  uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(uResetGpio, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_LOW_VALUE);
  Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);
    
  MDP_OSAL_DELAYMS(10);

  uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(uResetGpio, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_HIGH_VALUE);
  Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);

  MDP_OSAL_DELAYMS(10);
  uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(uResetGpio, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_LOW_VALUE);
  Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);

  MDP_OSAL_DELAYMS(10);
    
  uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(uResetGpio, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_HIGH_VALUE);
  Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);
  MDP_OSAL_DELAYMS(10);
  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_BacklightLevel()
**
** DESCRIPTION:
**
*/ /* -------------------------------------------------------------------- */
static MDP_Status Panel_CDP_BacklightLevel(MDP_Display_IDType eDisplayId, BacklightConfigType *pBacklightConfig)
{
  MDP_Status                    eStatus  = MDP_STATUS_OK;
  DALGpioSignalType             uGPIOCfg = 0;  

  if (MDP_PANEL_BACKLIGHTTYPE_PMIC == pBacklightConfig->eBacklightType)
  {
    // Configure the power grid based on the module type
    switch (pBacklightConfig->uBacklightCntrl.eBacklightCtrl)
    {
      case MDP_PMIC_BACKLIGHT_CONTROLTYPE_WLED:
      {

        uint32 uWLEDValue = (0xFFF * pBacklightConfig->uLevel) / 100; // Calculate duty cycle based on 12 bit mode

        if (PM_ERR_FLAG_SUCCESS != pm_wled_set_led_duty_cycle(PMIC_C, PM_MODULATOR_TYPE_A, uWLEDValue))  /* PM_WLED_ALL */
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxeBoot: Wled pm_wled_set_led_duty_cycle failed\n");
        }
      }
        break;
      case MDP_PMIC_BACKLIGHT_CONTROLTYPE_PWM:
      {
        /* LCD PWM Enable Pin */
        uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(CDP_DISP_LCD_REG_EN, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_HIGH_VALUE);
        Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);

        uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(CDP_DISP_LCD_BKLT_EN, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_HIGH_VALUE);
        Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);

        /* LCD PWM Control Pin */
        pm_gpio_cfg_mode(PMIC_C, PM_GPIO_8, PM_GPIO_DIG_OUT);   
        pm_gpio_set_voltage_source(PMIC_C, PM_GPIO_8, PM_GPIO_VIN0);  
        pm_gpio_set_out_src_cfg(PMIC_C, PM_GPIO_8, PM_GPIO_SRC_SPECIAL_FUNCTION1);
        pm_gpio_set_out_drv_str(PMIC_C, PM_GPIO_8, PM_GPIO_OUT_DRV_STR_HIGH);
        pm_gpio_set_output_level(PMIC_C, PM_GPIO_8, 0);
        pm_gpio_set_out_buf_cfg(PMIC_C, PM_GPIO_8, PM_GPIO_OUT_BUF_CFG_CMOS); 
  
        if (PM_ERR_FLAG_SUCCESS != (pm_pwm_clock_config(PMIC_C,
                                                         PM_PWM_RESOURCE_PWM_4,
                                                         PM_PWM_SIZE__9BIT,
                                                         PM_PWM_CLK__19_2_MHZ,
                                                         1,
                                                         2)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxeBoot: PWM Clock config failed\n");
          eStatus = MDP_STATUS_FAILED;
        }
        else if (PM_ERR_FLAG_SUCCESS != (pm_pwm_enable_pwm(PMIC_C,
                                                           PM_PWM_RESOURCE_PWM_4,
                                                           (boolean)TRUE)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxeBoot: Enable PWM failed\n");
        }
        else 
        {
          uint32  uBrightnessValue = (511 * pBacklightConfig->uLevel) / 100;
      
          if (PM_ERR_FLAG_SUCCESS !=  (pm_pwm_set_pwm_value(PMIC_C,
                                                         PM_PWM_RESOURCE_PWM_4,
                                                         uBrightnessValue)))
          {
            eStatus = MDP_STATUS_FAILED;
          }
        }
      }
        break;
      default:
        break;
    }
  }
  else if (MDP_PANEL_BACKLIGHTTYPE_DSI == pBacklightConfig->eBacklightType)
  {
     if (pBacklightConfig->uNumBits > 16)
     {
       MDP_Log_Message(MDP_LOGLEVEL_ERROR, "Backlight dcs bit width is not available\n");
       eStatus = MDP_STATUS_BAD_PARAM;
     }
     else
     {
       PlatformPanelBacklightControl panelBacklightControl = {
         0x00,
         {0x51, 0x00, 0x00}, // Using standard MIPI DCS commands to control brightness
       };

       if (pBacklightConfig->uNumBits > 8)
       {
         // Calculate brightness
         panelBacklightControl.uCmdType   = 0x39; // Use dcs long write type, e.g. 10bits: first byte is bits 8:11, the second byte is bits 0:7.
         panelBacklightControl.command[1] = DISP_DIV_ROUND_UP(((1 << pBacklightConfig->uNumBits) - 1) * pBacklightConfig->uLevel, 100) >> 0x08;
         panelBacklightControl.command[2] = DISP_DIV_ROUND_UP(((1 << pBacklightConfig->uNumBits) - 1) * pBacklightConfig->uLevel, 100) &  0xFF;
       }
       else
       {
         // Default to calculate brightness based on 8 bit mode
         panelBacklightControl.uCmdType   = 0x15; // Use dcs short write type as only needs one byte.
         panelBacklightControl.command[1] = DISP_DIV_ROUND_UP(0xFF * pBacklightConfig->uLevel, 100) & 0xFF;
       }

       eStatus = DSIDriver_Write(eDisplayId,
                                 panelBacklightControl.uCmdType,
                                 panelBacklightControl.command,
                                 sizeof(panelBacklightControl.command),
                                 0);
       if (MDP_STATUS_OK != eStatus)
       {
         MDP_Log_Message(MDP_LOGLEVEL_ERROR, "Backlight brightness DCS command send failed\n");
       }
    }
  }
  else
  {
    // Nothing to do for other configurations
  }

  return eStatus;
}

MDP_Status MDPPlatformConfigure(MDP_Display_IDType eDisplayId, MDPPlatformConfigType eConfig, MDPPlatformParams *pPlatformParams)
{
  MDP_Status  eStatus  = MDP_STATUS_OK;

  /* Static information, initial once during the first call */
  static MDPPlatformInfo        sPlatformInfo;
  static uint32                 uHardwareVersionMinor = 0;

  switch (eConfig)
  {
  case MDPPLATFORM_CONFIG_INIT:
    MDP_OSAL_MEMZERO(&sPlatformInfo,    sizeof(MDPPlatformInfo));

    // Read the platform ID once
    if (MDP_STATUS_OK == ReadPlatformIDAndChipID(&sPlatformInfo.sEFIPlatformType, &sPlatformInfo.sEFIChipSetId, &sPlatformInfo.sEFIChipSetFamily))
    {
      UINT32 uPanelOverride = 0;

      // Read the display panel ID override
      if ((MDP_STATUS_OK  == MDP_Display_GetVariable_Integer (PANEL_OVERRIDE_STRINGNAME, &uPanelOverride)) &&
          (uPanelOverride  > 0))
      {
        sPlatformInfo.uPanelIdOverride = (uint32) uPanelOverride;
      }

      // Parse sub-revision specific info to determine the platform type
      uHardwareVersionMinor = sPlatformInfo.sEFIPlatformType.version & 0xFF;
    }

    /* Enable VDDMM so that MMCX Arc can be configured */
    if (PM_ERR_FLAG_SUCCESS != pm_smps_volt_level(PMIC_H, PM_SMPS_4, 752*1000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error set VDDMM level \n");
    }
    if (PM_ERR_FLAG_SUCCESS != pm_smps_sw_enable(PMIC_H, PM_SMPS_4, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enable VDDMM\n");
    }

    // Store the platform specific ID
    sPlatformInfo.uPlatformID = pPlatformParams->sPlatformInfo.uPlatformID;

    switch (sPlatformInfo.sEFIPlatformType.platform)
    {
    case EFI_PLATFORMINFO_TYPE_CDP:
      // Default to enable primary display
      MDP_SUPPORTED_DISPLAY(MDP_DISPLAY_PRIMARY) = TRUE;

      if (MDP_BOOT_PLATFORMID_DUAL_PANEL == sPlatformInfo.uPlatformID)
      {
        // On the dual panel platform reference multiple displays are supported.
        MDP_SUPPORTED_DISPLAY(MDP_DISPLAY_SECONDARY) = TRUE;
      }
      break;

    default:
      // Enable primary display
      MDP_SUPPORTED_DISPLAY(MDP_DISPLAY_PRIMARY) = TRUE;
      break;
    }
    break;
  
  case MDPPLATFORM_CONFIG_SW_RENDERER:

    if ((EFI_PLATFORMINFO_TYPE_UNKNOWN == sPlatformInfo.sEFIPlatformType.platform) ||
        (EFI_PLATFORMINFO_TYPE_VIRTIO  == sPlatformInfo.sEFIPlatformType.platform) ||
        (EFI_PLATFORMINFO_TYPE_RUMI    == sPlatformInfo.sEFIPlatformType.platform) ||
        (TRUE == PcdGetBool(PcdDisplayForceSwRenderer)))
    {
      // Treat unknown platforms as a SW model only
      pPlatformParams->sPlatformInfo.bSWRender = TRUE;
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxeBoot: SW renderer only\n");
    }
    else
    {
      pPlatformParams->sPlatformInfo.bSWRender = FALSE;
    }
    break;
  case MDPPLATFORM_CONFIG_GETPANELCONFIG:
    {
      pPlatformParams->sPlatformPanel.uDefaultVendor   = 0;
      pPlatformParams->sPlatformPanel.uDefaultRevision = 0;
      pPlatformParams->sPlatformPanel.uPanelId         = 0;

      // Retrieve panel configuration (could be dependent on the interface)
      switch (eDisplayId)
      {
      case MDP_DISPLAY_PRIMARY:
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_MTP:
        case EFI_PLATFORMINFO_TYPE_QRD:            
          pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8*)r66451_120hz_fhd_plus_dsc_cmd_cphy_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(r66451_120hz_fhd_plus_dsc_cmd_cphy_xmldata);
          break;
        case EFI_PLATFORMINFO_TYPE_CDP:
        default:
          pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8*)dummy_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(dummy_xmldata);
          break;
        }
        break;

      case MDP_DISPLAY_EXTERNAL:
          pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8*)dummy_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(dummy_xmldata);
          break;

      case MDP_DISPLAY_SECONDARY:
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
          pPlatformParams->sPlatformPanel.pPanelXMLConfig   = (int8*)r66451_sec_60hz_fhd_plus_dsc_cmd_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize       = sizeof(r66451_sec_60hz_fhd_plus_dsc_cmd_xmldata);
        default:
          break;
        }
        break;
      default:
        break;
      }
    }
    break;
  case MDPPLATFORM_CONFIG_POWERUP:
    {
      switch (eDisplayId)
      {
      case MDP_DISPLAY_PRIMARY:
      case MDP_DISPLAY_SECONDARY:

        // Config based on the platform
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
        case EFI_PLATFORMINFO_TYPE_MTP:
        case EFI_PLATFORMINFO_TYPE_QRD:

          /* Check for common power or panel specific power,
           * Common Power : pPlatformParams is NULL or uFlags is 0x0,
           * Panel Power  : uFlags is set to panel specific power flag.
           */
          if ((NULL                          != pPlatformParams) &&
              (POWERCONFIG_FLAGS_PANEL_POWER  & pPlatformParams->sPowerConfig.uFlags))
          {
            switch (sPlatformInfo.uPrimaryPanelId)
            {
            default:
              // OEM to populate panel specific power up.
              break;
            }
          }
          else
          {
            /*
             * Ramdump mode Primary Power Sequence:
             * MDPPLATFORM_CONFIG_POWERDOWN is not be called at both enter and exit ramdump mode
             * Therefore panel power down is called first before power up panel to obey panel
             * power up sequence
             */
            if (MDP_STATUS_OK != (eStatus = Panel_CDP_PowerDown(eDisplayId)))
            {
              MDP_Log_Message(MDP_LOGLEVEL_ERROR, "Ramdump: Panel_PowerDown: Primary Power Down Sequence Failed (%d)\n", eStatus);
            }

            MDP_OSAL_DELAYMS(10);   /* delay 10ms to allow power grid to settle */

            // Primary Power Sequence
            if (MDP_STATUS_OK != (eStatus = Panel_CDP_PowerUp(eDisplayId)))
            {
              MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib: Primary Power Up Sequence Failed (%d)\n", eStatus);
            }
          }
          break;

        default:
          break;
        }

        break;

      case MDP_DISPLAY_EXTERNAL:

        // Config based on the platform
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
        case EFI_PLATFORMINFO_TYPE_QRD:
          break;
        default:
          break;
        }
        break;

      default:
        break;

      }

    }
    break;

  case MDPPLATFORM_CONFIG_POWERDOWN:
    {
       MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxeBoot: Power Down not supported in this mode\n");
    }
    break;
  case MDPPLATFORM_CONFIG_SETBACKLIGHT:
    {
      // Handle backlight level
      switch (eDisplayId)
      {
      case MDP_DISPLAY_PRIMARY:
      case MDP_DISPLAY_SECONDARY:
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
        case EFI_PLATFORMINFO_TYPE_MTP:
        case EFI_PLATFORMINFO_TYPE_QRD:
          eStatus = Panel_CDP_BacklightLevel(eDisplayId, &pPlatformParams->sBacklightConfig);
        default:
          break;
        }
        break;
      case MDP_DISPLAY_EXTERNAL:
        eStatus = MDP_STATUS_NOT_SUPPORTED;
        break;
      default:
        break;
      }
    }
    break;
  case MDPPLATFORM_CONFIG_GETPANELID:
    {
    }
    break;
  case MDPPLATFORM_CONFIG_GETPLATFORMINFO:
    {
      //
      // Return platform information
      //
      MDP_OSAL_MEMCPY(&pPlatformParams->sPlatformInfo, &sPlatformInfo, sizeof(MDPPlatformInfo));
    }
    break;
  case MDPPLATFORM_CONFIG_RESETPANEL:
    {
      // Handle power down
      switch (eDisplayId)
      {
      case MDP_DISPLAY_PRIMARY:
      case MDP_DISPLAY_SECONDARY:

        // Config based on the platform
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
        case EFI_PLATFORMINFO_TYPE_MTP:
        case EFI_PLATFORMINFO_TYPE_QRD:
          eStatus = Panel_CDP_Reset(eDisplayId);
        default:
          break;
        }

        break;
      case MDP_DISPLAY_EXTERNAL:
        eStatus = MDP_STATUS_NOT_SUPPORTED;
        break;
      default:
        break;
      }
    }
    break;

  case MDPPLATFORM_CONFIG_SETGPIOSTATE:
    {
      eStatus = SetDefaultGPIOState(&pPlatformParams->sGPIOState);
    }
    break;
  case MDPPLATFORM_CONFIG_GETPANELDTINFO:
    {
      if (NULL == pPlatformParams)
      {
        eStatus = MDP_STATUS_BAD_PARAM;
      }
      else
      {
        pPlatformParams->pPanelConfig             = GET_PANEL_CONFIG(eDisplayId);
        if (pPlatformParams->pPanelConfig)
        {
          MDP_OSAL_MEMZERO(pPlatformParams->pPanelConfig, sizeof(PanelConfigType));
          pPlatformParams->pPanelConfig->ePanelType = MDPPLATFORM_PANEL_PHYSICAL;
        }
      }
    }
    break;
  default:
    eStatus = MDP_STATUS_BAD_PARAM;
    break;
  }
  
  return eStatus;
}



/*===========================================================================
Private Function Definitions
===========================================================================*/

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: ReadPlatformIDAndChipID()
** 
** DESCRIPTION:
**
*/ /* -------------------------------------------------------------------- */
static MDP_Status ReadPlatformIDAndChipID(EFI_PLATFORMINFO_PLATFORM_INFO_TYPE *pPlatformInfo, EFIChipInfoIdType *pChipSetId, EFIChipInfoFamilyType *pChipSetFamily)
{
  DalPlatformInfoPlatformInfoType      dalPlatformInfo;
  DALResult                            eDalStatus = DAL_SUCCESS;
  MDP_Status                           eStatus    = MDP_STATUS_OK;

  MDP_OSAL_MEMZERO(&dalPlatformInfo,	sizeof(DalPlatformInfoPlatformInfoType));

  eDalStatus = boot_DalPlatformInfo_PlatformInfo(&dalPlatformInfo);
  if (eDalStatus != DAL_SUCCESS)
  {
     MDP_Log_Message(MDP_LOGLEVEL_ERROR, "Ramdump:Display:ReadPlatformIDAndChipId: Failed\n");

     eStatus    = MDP_STATUS_FAILED;
  }
  else
  {
    pPlatformInfo->platform = (EFI_PLATFORMINFO_PLATFORM_TYPE)dalPlatformInfo.platform;
    pPlatformInfo->version  = dalPlatformInfo.version;
    pPlatformInfo->subtype  = dalPlatformInfo.subtype;
    pPlatformInfo->fusion   = dalPlatformInfo.fusion;

    eDalStatus = boot_DalPlatformInfo_ChipId(pChipSetId);
    eDalStatus = boot_DalPlatformInfo_ChipFamily(pChipSetFamily);
  }


  return eStatus;
}

/****************************************************************************
*
** FUNCTION: SetDefaultGPIOState()
*/
/*!
* \brief
*   The \b SetDefaultGPIOState function toggles a list of GPIO's based on the requested configuration
**
* \retval MDP_Status
*
****************************************************************************/
MDP_Status SetDefaultGPIOState(GpioStateType *pGPIOList)
{
  MDP_Status          eStatus = MDP_STATUS_OK;

  if ((NULL == pGPIOList) ||
      (NULL == pGPIOList->pGPIOList))
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    // Handle each type of GPIO differently
    switch (pGPIOList->eGPIOType)
    {
    case MDPPLATFORM_GPIOTYPE_TLMM:
    {
      uint32              uCount;

      // Loop the list to configure all GPIOs.
      for (uCount = 0;uCount < pGPIOList->uListSize;uCount++)
      {
        // Only try to program GPIOs that are within range, TLMM Macro (EFI_GPIO_CFG) supports up to 0x3FF
        if (pGPIOList->pGPIOList[uCount] < 0x3FF)
        {

          DALGpioSignalType   uGPIOCfg = 0;
          uint32              uValue  = (pGPIOList->uState > 0) ? DAL_GPIO_HIGH_VALUE : DAL_GPIO_LOW_VALUE;

          uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(pGPIOList->pGPIOList[uCount], 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_2MA, uValue);
          Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);
        }
      }
    }
    break;
    default:
      // Others (PMIC, PMI) not supported
      break;
    }
  }

  return eStatus;
}

#ifdef __cplusplus
}
#endif
