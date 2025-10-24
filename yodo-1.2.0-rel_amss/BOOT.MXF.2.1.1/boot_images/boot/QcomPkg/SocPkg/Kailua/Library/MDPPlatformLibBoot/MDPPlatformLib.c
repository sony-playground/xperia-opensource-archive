/*=============================================================================
 
  File: MDPPlatformLib.c
 
  MDP platform specific functions
  
  Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
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
#include <api/pmic/pm/pm_smps.h>
#include <api/pmic/pm/pm_boot.h>
#include <api/pmic/pm/pm_version.h>
#include "MDPTypes.h"
#include "MDPPlatformLib.h"
#include "MDPSystem.h"
#include "DDITlmm.h"
#include "pmapp_npa.h"
#include "npa.h"
#include "HALDSILib.h"
#include "boot_platforminfo_if.h"
#include "boot_config_context.h"

/* -----------------------------------------------------------------------
** Defines
** ----------------------------------------------------------------------- */
#define PCD_PANEL_TYPE_OEM                1

#define DSI_READ_ADDRESS_SIZE             2
#define DSI_READ_READBACK_SIZE            8

#define PLATFORM_PANEL_ID_MAX_COMMANDS    3       // maximum panel ID read commands

#define PMIC_IBBLAB_READYTIME             25      // Maximum of milliseconds to wait for IBB/LAB to stabilize (Can be up to 8.8ms +/-16%)

// Main panel CDP/MTP specific defines
#define CDP_DISP_RESET_GPIO                133     // GPIO number for LCD0_RESET
#define CDP_DISP_TE_GPIO                   86      // GPIO number for TE
#define CDP_SEC_DISP_RESET_GPIO            137     // GPIO number for LCD0_RESET on secondary display
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
*                   VTDR6130 FHD Plus Panel                       *
*                                                                 *
*                   VTDR6130 DDIC                                 *
*                   1080x2400                                     *
*                   Single-Dphy(DSI0)                             *
*                   command mode DSC                              *
******************************************************************/
 const static int8 vtdr6130_60hz_fhd_dsc_cmd_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>VTDR6130 Visionox</PanelName>"
"<PanelDescription>VTDR6130 Visionox Single DSI DSC Command Mode Amoled Panel (1080x2400 24bpp)</PanelDescription>"
"<Group id=\"Active Timing\">"
 "<HorizontalActive>1080</HorizontalActive>"
 "<HorizontalFrontPorch>20</HorizontalFrontPorch>"
 "<HorizontalBackPorch>20</HorizontalBackPorch>"
 "<HorizontalSyncPulse>2</HorizontalSyncPulse>"
 "<HorizontalSyncSkew>0</HorizontalSyncSkew>"
 "<HorizontalLeftBorder>0</HorizontalLeftBorder>"
 "<HorizontalRightBorder>0</HorizontalRightBorder>"
 "<VerticalActive>2400</VerticalActive>"
"<VerticalFrontPorch>20</VerticalFrontPorch>"
"<VerticalBackPorch>18</VerticalBackPorch>"
"<VerticalSyncPulse>2</VerticalSyncPulse>"
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
"<DSITEvSyncStartPos>2400</DSITEvSyncStartPos>"
"<DSITEvSyncInitVal>2400</DSITEvSyncInitVal>"
"<DSIDSCEnable>True</DSIDSCEnable>"
"<DSIDSCMajor>1</DSIDSCMajor>"
"<DSIDSCMinor>1</DSIDSCMinor>"
"<DSIDSCScr>0</DSIDSCScr>"
"<DSIDSCProfileID>7</DSIDSCProfileID>"
"<DSIDSCSliceWidth>540</DSIDSCSliceWidth>"
"<DSIDSCSliceHeight>40</DSIDSCSliceHeight>"
"<DSILanes>4</DSILanes>"
"<DSIHsaHseAfterVsVe>False</DSIHsaHseAfterVsVe>"
"<DSILowPowerModeInHFP>False</DSILowPowerModeInHFP>"
"<DSILowPowerModeInHBP>False</DSILowPowerModeInHBP>"
"<DSILowPowerModeInHSA>False</DSILowPowerModeInHSA>"
"<DSILowPowerModeInBLLPEOF>True</DSILowPowerModeInBLLPEOF>"
"<DSILowPowerModeInBLLP>True</DSILowPowerModeInBLLP>"
"<DSIRefreshRate>0x900000</DSIRefreshRate>"
"<DSICmdUsingTrigger>False</DSICmdUsingTrigger>"
"<DSIEnableAutoRefresh>True</DSIEnableAutoRefresh>"
"<DSIAutoRefreshFrameNumDiv>1</DSIAutoRefreshFrameNumDiv>"
"<DSIControllerMapping>"
"00"
"</DSIControllerMapping>"
"</Group>"
"<DSIInitSequence>"
"39 03 01\n"
"39 35 00\n"
"39 53 20\n"
"39 51 00 00\n"
"39 59 09\n"
"39 6C 01\n"
"39 6D 00\n"
"39 6F 02\n"
"39 70 12 00 00 AB 30 80 09 60 04 38 00 28 02 1C 02 1C 02 00 02 0E 00 20 03 DD 00 07 00 0C 02 77 02 8B 18 00 10 F0 07 10 20 00 06 0F 0F 33 0E 1C 2A 38 46 54 62 69 70 77 79 7B 7D 7E 02 02 22 00 2A 40 2A BE 3A FC 3A FA 3A F8 3B 38 3B 78 3B B6 4B B6 4B F4 4B F4 6C 34 84 74 00 00 00 00 00 00\n"
"39 F0 AA 10\n"
"39 B1 01 38 00 14 00 1C 00 01 66 00 14 00 14 00 01 66 00 14 05 CC 00\n"
"39 F0 AA 13\n"
"39 CE 09 11 09 11 08 C1 07 FA 05 A4 00 3C 00 34 00 24 00 0C 00 0C 04 00 35\n"
"39 F0 AA 14\n"
"39 B2 03 33\n"
"39 B4 00 33 00 00 00 3E 00 00 00 3E 00 00\n"
"39 B5 00 09 09 09 09 09 09 06 01\n"
"39 B9 00 00 08 09 09 09\n"
"39 BC 10 00 00 06 11 09 3B 09 47 09 47 00\n"
"39 BE 10 10 00 08 22 09 19 09 25 09 25 00\n"
"39 FF 5A 80\n"
"39 65 14\n"
"39 FA 08 08 08\n"
"39 FF 5A 81\n"
"39 65 05\n"
"39 F3 0F\n"
"39 F0 AA 00\n"
"39 FF 5A 82\n"
"39 F9 00\n"
"39 FF 51 83\n"
"39 65 04\n"
"39 F8 00\n"
"39 FF 5A 00\n"
"39 65 01\n"
"39 F4 9A\n"
"39 FF 5A 00\n"
"05 11 00\n"
"FF 78\n"
"05 29 00\n"
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
"<DisplayResetInfo>0 10 1000 10000 0</DisplayResetInfo>"
"</Group>";

/******************************************************************
*                   Secondary VTDR6130 FHD Plus Panel             *
*                                                                 *
*                   VTDR6130 DDIC                                 *
*                   1080x2400                                     *
*                   Single-Dphy(DSI0)                             *
*                   command mode DSC                              *
******************************************************************/
const static int8 vtdr6130_sec_60hz_fhd_dsc_cmd_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>VTDR6130 Visionox</PanelName>"
"<PanelDescription>Secondary VTDR6130 Visionox Single DSI DSC Command Mode Amoled Panel (1080x2400 24bpp)</PanelDescription>"
"<Group id=\"Active Timing\">"
"<HorizontalActive>1080</HorizontalActive>"
"<HorizontalFrontPorch>20</HorizontalFrontPorch>"
"<HorizontalBackPorch>20</HorizontalBackPorch>"
"<HorizontalSyncPulse>2</HorizontalSyncPulse>"
"<HorizontalSyncSkew>0</HorizontalSyncSkew>"
"<HorizontalLeftBorder>0</HorizontalLeftBorder>"
"<HorizontalRightBorder>0</HorizontalRightBorder>"
"<VerticalActive>2400</VerticalActive>"
"<VerticalFrontPorch>20</VerticalFrontPorch>"
"<VerticalBackPorch>18</VerticalBackPorch>"
"<VerticalSyncPulse>2</VerticalSyncPulse>"
"<VerticalSyncSkew>0</VerticalSyncSkew>"
"<VerticalTopBorder>0</VerticalTopBorder>"
"<VerticalBottomBorder>0</VerticalBottomBorder>"
"<InvertDataPolarity>False</InvertDataPolarity>"
"<InvertVsyncPolairty>False</InvertVsyncPolairty>"
"<InvertHsyncPolarity>False</InvertHsyncPolarity>"
"<BorderColor>0x0</BorderColor>"
"</Group>"
"<Group id=\"Display Interface\">"
"<InterfaceType>11</InterfaceType>"
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
"<DSITEvSyncStartPos>2400</DSITEvSyncStartPos>"
"<DSITEvSyncInitVal>2400</DSITEvSyncInitVal>"
"<DSITEvSyncSelect>1</DSITEvSyncSelect>"
"<DSIDSCEnable>True</DSIDSCEnable>"
"<DSIDSCMajor>1</DSIDSCMajor>"
"<DSIDSCMinor>1</DSIDSCMinor>"
"<DSIDSCScr>0</DSIDSCScr>"
"<DSIDSCProfileID>7</DSIDSCProfileID>"
"<DSIDSCSliceWidth>540</DSIDSCSliceWidth>"
"<DSIDSCSliceHeight>40</DSIDSCSliceHeight>"
"<DSILanes>4</DSILanes>"
"<DSIHsaHseAfterVsVe>False</DSIHsaHseAfterVsVe>"
"<DSILowPowerModeInHFP>False</DSILowPowerModeInHFP>"
"<DSILowPowerModeInHBP>False</DSILowPowerModeInHBP>"
"<DSILowPowerModeInHSA>False</DSILowPowerModeInHSA>"
"<DSILowPowerModeInBLLPEOF>True</DSILowPowerModeInBLLPEOF>"
"<DSILowPowerModeInBLLP>True</DSILowPowerModeInBLLP>"
"<DSIRefreshRate>0x3C0000</DSIRefreshRate>"
"<DSICmdUsingTrigger>False</DSICmdUsingTrigger>"
"<DSIEnableAutoRefresh>True</DSIEnableAutoRefresh>"
"<DSIAutoRefreshFrameNumDiv>1</DSIAutoRefreshFrameNumDiv>"
"<DSIControllerMapping>"
"01"
"</DSIControllerMapping>"
"</Group>"
"<DSIInitSequence>"
"39 03 01\n"
"39 35 00\n"
"39 53 20\n"
"39 51 00 00\n"
"39 59 09\n"
"39 6C 02\n"
"39 6D 00\n"
"39 6F 02\n"
"39 70 12 00 00 AB 30 80 09 60 04 38 00 28 02 1C 02 1C 02 00 02 0E 00 20 03 DD 00 07 00 0C 02 77 02 8B 18 00 10 F0 07 10 20 00 06 0F 0F 33 0E 1C 2A 38 46 54 62 69 70 77 79 7B 7D 7E 02 02 22 00 2A 40 2A BE 3A FC 3A FA 3A F8 3B 38 3B 78 3B B6 4B B6 4B F4 4B F4 6C 34 84 74 00 00 00 00 00 00\n"
"39 F0 AA 10\n"
"39 B1 01 38 00 14 00 1C 00 01 66 00 14 01 FC 00 01 66 00 14 0D 6C 00\n"
"39 F0 AA 13\n"
"39 D3 15 C2 15 C2 15 02 13 25 0D 8A 00 90 00 7D 00 57 00 0C 00 0C 0B 00 7E\n"
"39 F0 AA 14\n"
"39 B2 03 33\n"
"39 B4 00 33 00 00 00 3E 00 00 00 3E 00 00\n"
"39 B5 00 09 09 09 09 09 09 06 01\n"
"39 B9 00 00 08 09 09 09\n"
"39 BC 10 00 00 06 11 09 3B 09 47 09 47 00\n"
"39 BE 10 10 00 08 22 09 19 09 25 09 25 00\n"
"39 FF 5A 80\n"
"39 65 14\n"
"39 FA 08 08 08\n"
"39 FF 5A 81\n"
"39 65 05\n"
"39 F3 0F\n"
"39 F0 AA 00\n"
"39 FF 5A 82\n"
"39 F9 00\n"
"39 FF 51 83\n"
"39 65 04\n"
"39 F8 00\n"
"39 FF 5A 00\n"
"39 65 01\n"
"39 F4 9A\n"
"39 FF 5A 00\n"
"05 11 00\n"
"FF 78\n"
"05 29 00\n"
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
"<DisplayResetInfo>0 10 1000 10000 0</DisplayResetInfo>"
"</Group>"
;

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

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_B, PM_LDO_12, 1800000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO12B to 1.8V\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_B, PM_LDO_13, 3000000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO13B to 3.0V\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_B, PM_LDO_11, 1200000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO11B to 1.2V\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_E, PM_LDO_3, 1200000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO3E to 1.2V\n");
    }
    
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_E, PM_LDO_1, 880000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO1E to 0.88V\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_mode(PMIC_B, PM_LDO_12, PM_SW_MODE_NPM))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO12B to Normal power mode\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_mode(PMIC_B, PM_LDO_13, PM_SW_MODE_NPM))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO13B to Normal power mode\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_mode(PMIC_B, PM_LDO_11, PM_SW_MODE_NPM))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO11B to Normal power mode\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_mode(PMIC_E, PM_LDO_3, PM_SW_MODE_NPM))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO3E to Normal power mode\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_mode(PMIC_E, PM_LDO_1, PM_SW_MODE_NPM))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO1E to Normal power mode\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_B, PM_LDO_12, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO12B\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_B, PM_LDO_13, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO13B\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_B, PM_LDO_11, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO11B\n");
    }
    
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_E, PM_LDO_3, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO6E\n");
    }
    
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_E, PM_LDO_1, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO5E\n");
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
  MDP_Status                    eStatus = MDP_STATUS_OK;

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
    if (PM_ERR_FLAG_SUCCESS != pm_smps_volt_level(PMIC_E, PM_SMPS_1, 752*1000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error set VDDMM level \n");
    }
    if (PM_ERR_FLAG_SUCCESS != pm_smps_sw_enable(PMIC_E, PM_SMPS_1, PM_ON, TRUE))
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
        case EFI_PLATFORMINFO_TYPE_CDP:
        case EFI_PLATFORMINFO_TYPE_MTP:
        default:
          pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8*)vtdr6130_60hz_fhd_dsc_cmd_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(vtdr6130_60hz_fhd_dsc_cmd_xmldata);
          break;
        case EFI_PLATFORMINFO_TYPE_QRD:
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
          pPlatformParams->sPlatformPanel.pPanelXMLConfig   = (int8*)vtdr6130_sec_60hz_fhd_dsc_cmd_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize       = sizeof(vtdr6130_sec_60hz_fhd_dsc_cmd_xmldata);
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
  MDP_Status                           eStatus            = MDP_STATUS_OK;
  bl_error_boot_type                   status             = BL_ERR_NONE;
  boot_platforminfo_if_type           *platforminfo_if    = NULL;

  MDP_OSAL_MEMZERO(&dalPlatformInfo,	sizeof(DalPlatformInfoPlatformInfoType));

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PLATFORMINFO_INTERFACE, (void **)&platforminfo_if);
  if(status != BL_ERR_NONE)
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if((platforminfo_if->PlatformInfo(&dalPlatformInfo)) != BL_ERR_NONE)
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

    status = platforminfo_if->ChipId(pChipSetId);
	if (status != BL_ERR_NONE)
    {
     eStatus    = MDP_STATUS_FAILED;
    }
    status = platforminfo_if->ChipFamily(pChipSetFamily);
	if (status != BL_ERR_NONE)
    {
     eStatus    = MDP_STATUS_FAILED;
    }
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
