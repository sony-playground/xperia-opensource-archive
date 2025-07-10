/*=============================================================================
 
  File: MDPPlatformLib.c
 
  MDP platform specific functions
  
  Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
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
#include "boot_platforminfo_if.h"
#include "boot_config_context.h"
#include "ChipInfo.h"

/* -----------------------------------------------------------------------
** Defines
** ----------------------------------------------------------------------- */
#define PCD_PANEL_TYPE_OEM                1

#define DSI_READ_ADDRESS_SIZE             2
#define DSI_READ_READBACK_SIZE            8

#define PLATFORM_PANEL_ID_MAX_COMMANDS    3       // maximum panel ID read commands

#define PMIC_IBBLAB_READYTIME             25      // Maximum of milliseconds to wait for IBB/LAB to stabilize (Can be up to 8.8ms +/-16%)

// Main panel CDP/MTP specific defines
#define CDP_DISP_RESET_GPIO                92       // GPIO number for LCD0_RESET
#define CDP_DISP_TE_GPIO                   93      // GPIO number for TE
#define CDP_DISP_LCD_BIAS_EN               127     // GPIO for LCD bias enable
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
static uint32     CheckNumDisplayCores();


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
 *                   Ft8726 FHD Plus Panel                        *
 *                                                                *
 *                   ft8726 DDIC                                  *
 *                   1080x2408                                    *
 *                   Single-Dphy(DSI0)                            *
 *                   video mode DSC                             *
 ******************************************************************/
const static int8 ft8726_fhd_plus_dsc_120hz_vid_xmldata[] = 
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>Ft8726 </PanelName>"
"<PanelDescription>ft8726 Lcd video mode Dsi focaltech panel with DSC (1080x2408 24bpp)</PanelDescription>"
"<Group id=\"Active Timing\">"
" <HorizontalActive>1080</HorizontalActive>"
" <HorizontalFrontPorch>40</HorizontalFrontPorch>"
" <HorizontalBackPorch>36</HorizontalBackPorch>"
" <HorizontalSyncPulse>12</HorizontalSyncPulse>"
" <HorizontalSyncSkew>0</HorizontalSyncSkew>"
" <HorizontalLeftBorder>0</HorizontalLeftBorder>"
" <HorizontalRightBorder>0</HorizontalRightBorder>"
" <VerticalActive>2408</VerticalActive>"
" <VerticalFrontPorch>46</VerticalFrontPorch>"
" <VerticalBackPorch>18</VerticalBackPorch>"
" <VerticalSyncPulse>2</VerticalSyncPulse>"
" <VerticalSyncSkew>0</VerticalSyncSkew>"
" <VerticalTopBorder>0</VerticalTopBorder>"
" <VerticalBottomBorder>0</VerticalBottomBorder>"
" <InvertDataPolarity>False</InvertDataPolarity>"
" <InvertVsyncPolairty>False</InvertVsyncPolairty>"
" <InvertHsyncPolarity>False</InvertHsyncPolarity>"
" <BorderColor>0x0</BorderColor>"
"</Group>"
"<Group id=\"Display Interface\">"
" <InterfaceType>8</InterfaceType>"
" <InterfaceColorFormat>3</InterfaceColorFormat>"
"</Group>"
"<Group id=\"DSI Interface\">"
" <DSIChannelId>1</DSIChannelId>"
" <DSIVirtualId>0</DSIVirtualId>"
" <DSIColorFormat>36</DSIColorFormat>"
" <DSITrafficMode>2</DSITrafficMode>"
" <DSIDSCEnable>True</DSIDSCEnable>"
" <DSIDSCMajor>1</DSIDSCMajor>"
" <DSIDSCMinor>1</DSIDSCMinor>"
" <DSIDSCScr>0</DSIDSCScr>"
" <DSIDSCProfileID>4</DSIDSCProfileID>"
" <DSIDSCSliceWidth>540</DSIDSCSliceWidth>"
" <DSIDSCSliceHeight>8</DSIDSCSliceHeight>"
" <DSIDSCSlicePerPacket>2</DSIDSCSlicePerPacket>"
" <DSILanes>4</DSILanes>"
"   <DSIHsaHseAfterVsVe>False</DSIHsaHseAfterVsVe>"
"   <DSILowPowerModeInHFP>False</DSILowPowerModeInHFP>"
"   <DSILowPowerModeInHBP>False</DSILowPowerModeInHBP>"
"   <DSILowPowerModeInHSA>False</DSILowPowerModeInHSA>"
"   <DSILowPowerModeInBLLPEOF>True</DSILowPowerModeInBLLPEOF>"
"   <DSILowPowerModeInBLLP>True</DSILowPowerModeInBLLP>"
"   <DSIRefreshRate>0x780000</DSIRefreshRate>"
" <DSIControllerMapping>"
"  00"
" </DSIControllerMapping>"
"</Group>"
"<DSIInitSequence>"
" 15 00 00\n"
" 39 ff 87 20 01\n"
" 15 00 80\n"
" 39 ff 87 20\n"
" 15 00 00\n"
" 39 2A 00 00 04 37\n"
" 15 00 00\n"
" 39 2B 00 00 09 67\n"
" 15 00 a3\n"
" 39 b3 09 68 00 18\n"
" 15 00 00\n"
" 39 D9 23 23 23 23\n"
" 15 00 80\n"
" 39 C0 00 49 00 33 00 0F\n"
" 15 00 90\n"
" 39 C0 00 49 00 33 00 0F\n"
" 15 00 A0\n"
" 39 C0 00 5A 00 33 00 0F\n"
" 15 00 B0\n"
" 39 C0 00 D4 00 33 0F\n"
" 15 00 60\n"
" 39 C0 00 B4 00 33 00 0F\n"
" 15 00 70\n"
" 39 C0 00 C8 00 C8 0C 03 14 00 00 15 01 11\n"
" 15 00 A3\n"
" 39 C1 00 4A 00 29 00 02\n"
" 15 00 80\n"
" 39 CE 01 81 FF FF 01 68 01 98 00 00 00 00 01 90 01 90\n"
" 15 00 90\n"
" 39 CE 00 BD 12 75 00 BD 80 FF FF 00 07 08 14 0E 00\n"
" 15 00 A0\n"
" 39 CE 00 00 00\n"
" 15 00 B0\n"
" 39 CE 22 00 00\n"
" 15 00 D1\n"
" 39 CE 00 00 01 00 00 00 00\n"
" 15 00 E1\n"
" 39 CE 04 03 14 03 14 00 00 00 00 00 00\n"
" 15 00 F1\n"
" 39 CE 32 2A 00 01 30 01 0D 00 00\n"
" 15 00 B0\n"
" 39 CF 01 01 3D 41\n"
" 15 00 B5\n"
" 39 CF 05 05 50 54\n"
" 15 00 C0\n"
" 39 CF 09 09 63 67\n"
" 15 00 C5\n"
" 39 CF 09 09 69 6D\n"
" 15 00 00\n"
" 39 E1 00 05 0A 12 27 1E 26 2D 38 10 40 47 4E 53 F1 58 60 68 6F 25 76 7D 85 8D 51 97 9C A2 AA 2C B2 BD CB D3 83 DE ED F9 FF B3\n"
" 15 00 30\n"
" 39 E1 03 06 0A 12 07 1E 26 2D 38 10 40 47 4E 53 F1 58 60 68 6F 25 76 7D 85 8D 51 97 9C A2 AA 2C B2 BD CB D3 83 DE ED F9 FF B3\n"
" 15 00 60\n"
" 39 E1 00 05 0A 12 27 1E 26 2D 38 10 40 47 4E 53 F1 58 60 68 6F 25 76 7D 85 8D 51 97 9C A2 AA 2C B2 BD CB D3 83 DE ED F9 FF B3\n"
" 15 00 90\n"
" 39 E1 03 06 0A 12 07 1E 26 2D 38 10 40 47 4E 53 F1 58 60 68 6F 25 76 7D 85 8D 51 97 9C A2 AA 2C B2 BD CB D3 83 DE ED F9 FF B3\n"
" 15 00 C0\n"
" 39 E1 00 05 0A 12 27 1E 26 2D 38 10 40 47 4E 53 F1 58 60 68 6F 25 76 7D 85 8D 51 97 9C A2 AA 2C B2 BD CB D3 83 DE ED F9 FF B3\n"
" 15 00 F0\n"
" 39 E1 03 06 0A 12 07 1E 26 2D 38 10 40 47 4E 53 F1 58\n"
" 15 00 00\n"
" 39 E2 60 68 6F 25 76 7D 85 8D 51 97 9C A2 AA 2C B2 BD CB D3 83 DE ED F9 FF B3\n"
" 15 00 D1\n"
" 39 C1 0A A6 0E C8 19 67 07 E3 0B 11 13 04\n"
" 15 00 E1\n"
" 39 C1 0E C8\n"
" 15 00 E4\n"
" 39 CF 09 FF 09 FE 09 FE 09 FE 09 FE 09 FE\n"
" 15 00 80\n"
" 39 C1 44 44\n"
" 15 00 90\n"
" 15 C1 03\n"
" 15 00 F5\n"
" 15 CF 02\n"
" 15 00 F6\n"
" 15 CF 3C\n"
" 15 00 F1\n"
" 15 CF 3C\n"
" 15 00 F0\n"
" 15 C1 00\n"
" 15 00 CC\n"
" 15 C1 18\n"
" 15 00 F6\n"
" 15 CF 90\n"
" 15 00 80\n"
" 39 C2 82 01 1f 1f 00 00 00 00\n"
" 15 00 90\n"
" 39 C2 00 00 00 00\n"
" 15 00 A0\n"
" 39 C2 00 00 00 21 89 01 00 00 21 89 02 00 00 21 89\n"
" 15 00 B0\n"
" 39 C2 03 00 00 21 89 80 08 03 02 02\n"
" 15 00 CA\n"
" 39 C2 84 08 03 01 81\n"
" 15 00 E0\n"
" 39 C2 33 33 70 00 70\n"
" 15 00 E8\n"
" 39 C2 00 00 00 00 00 00 00 00\n"
" 15 00 D0\n"
" 39 C3 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n"
" 15 00 80\n"
" 39 CB 00 01 00 03 fD 01 01 00 00 00 fD 01 00 03 00 00\n"
" 15 00 90\n"
" 39 CB 00 00 00 0F F0 00 00 00 00 00 ff 00 00 00 00 00\n"
" 15 00 A0\n"
" 39 CB 00 00 00 00\n"
" 15 00 A4\n"
" 39 CB 03 00 0C 00\n"
" 15 00 B0\n"
" 39 CB 13 58 05 30\n"
" 15 00 C0\n"
" 39 CB 13 58 05 30\n"
" 15 00 D5\n"
" 39 CB 00 00 00 00 00 00 00 00 00 00 00\n"
" 15 00 E0\n"
" 39 CB 00 00 00 00 00 00 00 00 00 00 00 00 00\n"
" 15 00 80\n"
" 39 CC 23 12 23 1C 23 0A 23 23 09 08 07 06 23 23 23 23\n"
" 15 00 90\n"
" 39 CC 23 18 16 17 23 19 1A 1B\n"
" 15 00 A0\n"
" 39 CC 23 12 23 1D 23 0E 23 23 06 07 08 09 23 23 23 23\n"
" 15 00 B0\n"
" 39 CC 23 18 16 17 23 19 1A 1B\n"
" 15 00 80\n"
" 39 CD 23 23 23 02 23 0A 23 23 09 08 07 06 23 23 23 23\n"
" 15 00 90\n"
" 39 CD 23 18 16 17 23 19 1A 1B\n"
" 15 00 A0\n"
" 39 CD 23 23 23 02 23 0E 23 23 06 07 08 09 23 23 23 23\n"
" 15 00 B0\n"
" 39 CD 23 18 16 17 23 19 1A 1B\n"
" 15 00 86\n"
" 39 C0 00 00 00 01 10 05\n"
" 15 00 96\n"
" 39 C0 00 00 00 01 10 05\n"
" 15 00 A3\n"
" 39 Ce 00 00 00 01 10 05\n"
" 15 00 B3\n"
" 39 Ce 00 00 00 01 10 05\n"
" 15 00 69\n"
" 39 C0 01 14 01\n"
" 15 00 82\n"
" 39 a7 10 00\n"
" 15 00 8d\n"
" 15 a7 01\n"
" 15 00 8f\n"
" 15 a7 01\n"
" 15 00 93\n"
" 15 C5 37\n"
" 15 00 97\n"
" 15 C5 37\n"
" 15 00 9A\n"
" 15 C5 32\n"
" 15 00 9C\n"
" 15 C5 32\n"
" 15 00 B6\n"
" 39 C5 10 10 0E 0E 10 10 0E 0E\n"
" 15 00 88\n"
" 15 C4 08\n"
" 15 00 80\n"
" 15 A7 03\n"
" 15 00 B0\n"
" 15 C5 D1\n"
" 15 00 B3\n"
" 15 C5 D1\n"
" 15 00 99\n"
" 15 CF 50\n"
" 15 00 8C\n"
" 15 C3 00\n"
" 15 00 A0\n"
" 39 C3 35 21\n"
" 15 00 A4\n"
" 39 C3 01 20\n"
" 15 00 AA\n"
" 15 C3 21\n"
" 15 00 Ad\n"
" 15 C3 01\n"
" 15 00 Ae\n"
" 15 C3 20\n"
" 15 00 b3\n"
" 15 C3 21\n"
" 15 00 b6\n"
" 39 C3 01 20\n"
" 15 00 C3\n"
" 15 C5 FF\n"
" 15 00 A9\n"
" 15 F5 8E\n"
" 15 00 B0\n"
" 15 B3 00\n"
" 15 00 83\n"
" 15 B0 63\n"
" 15 00 93\n"
" 15 C4 08\n"
" 15 00 80\n"
" 15 B3 22\n"
" 15 00 90\n"
" 15 c3 08\n"
" 15 00 fa\n"
" 15 c2 14\n"
" 15 00 ca\n"
" 15 c0 80\n"
" 15 00 82\n"
" 15 F5 01\n"
" 15 00 93\n"
" 15 F5 01\n"
" 15 00 9b\n"
" 15 F5 49\n"
" 15 00 9d\n"
" 15 F5 49\n"
" 15 00 be\n"
" 39 c5 F0 F0\n"
" 15 00 85\n"
" 15 a7 01\n"
" 15 00 dc\n"
" 15 c3 37\n"
" 15 00 8A\n"
" 15 F5 C7\n"
" 15 00 99\n"
" 15 CF 50\n"
" 15 00 9C\n"
" 15 F5 00\n"
" 15 00 9E\n"
" 15 F5 00\n"
" 15 00 B0\n"
" 39 C5 D0 4A 39 D0 4A 0F\n"
" 15 00 C2\n"
" 15 F5 42\n"
" 15 00 E8\n"
" 15 C0 40\n"
" 15 00 D4\n"
" 15 CB 03\n"
" 15 00 B0\n"
" 39 CA 6B 6B 09\n"
" 15 00 80\n"
" 15 A4 CA\n"
" 15 00 87\n"
" 15 C5 0C\n"
" 15 00 89\n"
" 39 C5 0C 0C 0C\n"
" 15 00 8C\n"
" 39 C5 0C 0C 0C\n"
" 15 00 B0\n"
" 39 B4 00 08 02 00 00 BB 00 07 0D B7 0C B7 10 F0\n"
" 15 00 00\n"
" 39 FF FF FF FF\n"
" 15 51 F0\n"
" 15 53 2C\n"
" 15 55 00\n"
" 05 11\n"
" ff C8\n"
" 05 29\n"
" ff 96\n"
"</DSIInitSequence>"
"<DSITermSequence>"
" 05 28\n"
" ff 10\n"
" 05 10\n"
" ff 32\n"
"</DSITermSequence>"
"<Group id='Backlight Configuration'>"
" <BacklightType>1</BacklightType>"
" <BacklightPmicControlType>3</BacklightPmicControlType>"
" <DisplayResetInfo>0 10 1000 10000 0</DisplayResetInfo>"
"</Group>";

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

	/* turn on LDO5B, LD016B, LDO4E */
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_B, PM_LDO_5, 880000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO5 to 0.88V\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_B, PM_LDO_16, 1200000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO16 to 1.2V\n");
    }
	
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_E, PM_LDO_4, 3000000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO4 to 3.0V\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_B, PM_LDO_5, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO5\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_B, PM_LDO_16, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO16\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_E, PM_LDO_4, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO4\n");
    }
    
    /* LCD Bias */
    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(CDP_DISP_LCD_BIAS_EN, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_HIGH_VALUE);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);  
    MDP_OSAL_DELAYUS(10); 
 
    /* LCD VDDIO PIN*/
    pm_gpio_cfg_mode(PMIC_I, PM_GPIO_11, PM_GPIO_DIG_OUT);
    pm_gpio_set_voltage_source(PMIC_I, PM_GPIO_11, PM_GPIO_VIN0);
    pm_gpio_set_out_src_cfg(PMIC_I, PM_GPIO_11, PM_GPIO_SRC_GND);
    pm_gpio_set_out_drv_str(PMIC_I, PM_GPIO_11, PM_GPIO_OUT_DRV_STR_HIGH);
    pm_gpio_set_output_level(PMIC_I, PM_GPIO_11, PM_GPIO_LEVEL_HIGH);
    pm_gpio_set_out_buf_cfg(PMIC_I, PM_GPIO_11, PM_GPIO_OUT_BUF_CFG_CMOS);

    MDP_OSAL_DELAYUS(10); 
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

        if (PM_ERR_FLAG_SUCCESS != pm_wled_set_led_duty_cycle(PMIC_B, PM_MODULATOR_TYPE_A, uWLEDValue))  /* PM_WLED_ALL */
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxeBoot: Wled pm_wled_set_led_duty_cycle failed\n");
        }
      }
        break;
        
      case MDP_PMIC_BACKLIGHT_CONTROLTYPE_PWM:
       {
        /* LCD PWM Enable Pin */
        pm_gpio_cfg_mode(PMIC_B, PM_GPIO_6, PM_GPIO_DIG_OUT);
        pm_gpio_set_voltage_source(PMIC_B, PM_GPIO_6, PM_GPIO_VIN0);
        pm_gpio_set_out_src_cfg(PMIC_B, PM_GPIO_6, PM_GPIO_SRC_GND);
        pm_gpio_set_out_drv_str(PMIC_B, PM_GPIO_6, PM_GPIO_OUT_DRV_STR_HIGH);
        pm_gpio_set_output_level(PMIC_B, PM_GPIO_6, PM_GPIO_LEVEL_HIGH);
        pm_gpio_set_out_buf_cfg(PMIC_B, PM_GPIO_6, PM_GPIO_OUT_BUF_CFG_CMOS);
  
        /* LCD PWM Control Pin */
        pm_gpio_cfg_mode(PMIC_B, PM_GPIO_7, PM_GPIO_DIG_OUT);   
        pm_gpio_set_voltage_source(PMIC_B, PM_GPIO_7, PM_GPIO_VIN0);  
        pm_gpio_set_out_src_cfg(PMIC_B, PM_GPIO_7, PM_GPIO_SRC_SPECIAL_FUNCTION1);
        pm_gpio_set_out_drv_str(PMIC_B, PM_GPIO_7, PM_GPIO_OUT_DRV_STR_HIGH);
        pm_gpio_set_output_level(PMIC_B, PM_GPIO_7, PM_GPIO_LEVEL_LOW);
        pm_gpio_set_out_buf_cfg(PMIC_B, PM_GPIO_7, PM_GPIO_OUT_BUF_CFG_CMOS); 
  
        if (PM_ERR_FLAG_SUCCESS != (pm_pwm_clock_config(PMIC_B,
                                                        PM_PWM_RESOURCE_PWM_1,
                                                        PM_PWM_SIZE__9BIT,
                                                        PM_PWM_CLK__19_2_MHZ,
                                                        1,
                                                        2)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxeBoot: PWM Clock config failed\n");

          eStatus = MDP_STATUS_FAILED;
        }
        else if (PM_ERR_FLAG_SUCCESS != (pm_pwm_enable_pwm(PMIC_B,
                                                           PM_PWM_RESOURCE_PWM_1,
                                                           (boolean)TRUE)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxeBoot: Enable PWM failed\n");
        }
        else 
        {
          uint32  uBrightnessValue = (511 * pBacklightConfig->uLevel) / 100;
          if (PM_ERR_FLAG_SUCCESS !=  (pm_pwm_set_pwm_value(PMIC_B,
                                                         PM_PWM_RESOURCE_PWM_1,
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
    if (MDP_STATUS_OK == (eStatus = ReadPlatformIDAndChipID(&sPlatformInfo.sEFIPlatformType, &sPlatformInfo.sEFIChipSetId, &sPlatformInfo.sEFIChipSetFamily)))
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

    // Store the platform specific ID
    sPlatformInfo.uPlatformID = pPlatformParams->sPlatformInfo.uPlatformID;

    switch (sPlatformInfo.sEFIPlatformType.platform)
    {
    case EFI_PLATFORMINFO_TYPE_CDP:
    case EFI_PLATFORMINFO_TYPE_IDP:
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
        case EFI_PLATFORMINFO_TYPE_IDP:
        case EFI_PLATFORMINFO_TYPE_CDP:
        default:
          pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8*)ft8726_fhd_plus_dsc_120hz_vid_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(ft8726_fhd_plus_dsc_120hz_vid_xmldata);
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
          pPlatformParams->sPlatformPanel.pPanelXMLConfig   = (int8*)dummy_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize       = sizeof(dummy_xmldata);
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
        case EFI_PLATFORMINFO_TYPE_IDP:
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
        case EFI_PLATFORMINFO_TYPE_IDP:
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
        case EFI_PLATFORMINFO_TYPE_IDP:
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

/**********************************************************************************************
*
* FUNCTION: CheckNumDisplayCores()
*
* DESCRIPTION:
*   Check the valid display core number.
*
***********************************************************************************************/
static uint32 CheckNumDisplayCores()
{
  bl_error_boot_type       eChipInfoStatus       = BL_ERR_NONE;
  boolean                  bDisplayDisableMask   = 0;
  uint32                   uValidDisplayCores    = 1;

  if (CHIPINFO_SUCCESS  != ChipInfo_IsPartDisabled(CHIPINFO_PART_DISPLAY, 0, &bDisplayDisableMask))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "Ramdump:Display:ChipInfo_IsPartDisabled: with error = %d\n", eChipInfoStatus);
  }
  else if (TRUE == bDisplayDisableMask)
  {
    // uDisplayCoreMask is non-zero if the part is defective. "non-zero" currently means 1, but that might change in the future
    // if more granularity is needed to determine defectiveness
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "CheckNumDisplayCores(): Display part disabled \n");
    uValidDisplayCores = 0;
  }

  return uValidDisplayCores;
}
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
  else if (0 == CheckNumDisplayCores())   // Check if there is valid display core
  {
    eStatus = MDP_STATUS_FAILED;
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
