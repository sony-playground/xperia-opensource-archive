/*=============================================================================
 
  File: MDPPlatformLib.c
 
  MDP platform specific functions
  
  Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
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
#define CDP_DISP_RESET_GPIO                42       // GPIO number for LCD0_RESET
#define CDP_DISP_TE_GPIO                   82       // GPIO number for TE
#define AMOLED_EXT_DVDD_VREG_EN           148       //GPIO for DVDD enable
#define Default_DISP_LCD_BIAS_EN          168       //GPIO for LCD Bias enable
  
#define CDP_SEC_DISP_RESET_GPIO            4        // GPIO number for LCD0_RESET on secondary display
#define CDP_SEC_DISP_TE_GPIO               83       // GPIO number for TE on secondary display

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
 *                   NT36672E FHD Plus Panel                      *
 *                                                                *
 *                   NT36672E DDIC                                *
 *                   1080x2408                                    *
 *                   Single-Dphy(DSI0)                            *
 *                   Video mode DSC                               *
 ******************************************************************/
/******************************************************************
 *                   NT36672E FHD Plus Panel                      *
 *                                                                *
 *                   NT36672E DDIC                                *
 *                   1080x2408                                    *
 *                   Single-Dphy(DSI0)                            *
 *                   Video mode DSC                               *
 ******************************************************************/
const static int8 nt36672e_60hz_fhd_plus_dsc_vid_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>NT36672E Video</PanelName>"
"<PanelDescription>NT36672E Single DSI DSC Video Mode Panel (1080x2408 24bpp)</PanelDescription>"
"<Group id=\"Active Timing\">"
" <HorizontalActive>1080</HorizontalActive>"
" <HorizontalFrontPorch>76</HorizontalFrontPorch>"
" <HorizontalBackPorch>56</HorizontalBackPorch>"
" <HorizontalSyncPulse>12</HorizontalSyncPulse>"
" <HorizontalSyncSkew>0</HorizontalSyncSkew>"
" <HorizontalLeftBorder>0</HorizontalLeftBorder>"
" <HorizontalRightBorder>0</HorizontalRightBorder>"
" <VerticalActive>2408</VerticalActive>"
" <VerticalFrontPorch>46</VerticalFrontPorch>"
" <VerticalBackPorch>10</VerticalBackPorch>"
" <VerticalSyncPulse>10</VerticalSyncPulse>"
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
"   <DSIRefreshRate>0x3c0000</DSIRefreshRate>"
" <DSIControllerMapping>"
"  00"
" </DSIControllerMapping>"
"</Group>"
"<DSIInitSequence>"
" 39 ff 10 \n"
" 39 fb 01 \n"
" 39 b0 00 \n"
" 39 c0 03 \n"
" 39 c1 89 28 00 08 00 aa 02 0e 00 2b 00 07 0d b7 0c b7 \n"
" 39 c2 1b a0 \n"
" 15 35 00 \n"
" 39 ff 20 \n"
" 39 fb 01 \n"
" 39 01 66 \n"
" 39 06 40 \n"
" 39 07 38 \n"
" 39 2f 83 \n"
" 39 69 91 \n"
" 39 95 d1 \n"
" 39 96 d1 \n"
" 39 f2 64 \n"
" 39 f3 54 \n"
" 39 f4 64 \n"
" 39 f5 54 \n"
" 39 f6 64 \n"
" 39 f7 54 \n"
" 39 f8 64 \n"
" 39 f9 54 \n"
" 39 ff 24 \n"
" 39 fb 01 \n"
" 39 01 0f \n"
" 39 03 0c \n"
" 39 05 1d \n"
" 39 08 2f \n"
" 39 09 2e \n"
" 39 0a 2d \n"
" 39 0b 2c \n"
" 39 11 17 \n"
" 39 12 13 \n"
" 39 13 15 \n"
" 39 15 14 \n"
" 39 16 16 \n"
" 39 17 18 \n"
" 39 1b 01 \n"
" 39 1d 1d \n"
" 39 20 2f \n"
" 39 21 2e \n"
" 39 22 2d \n"
" 39 23 2c \n"
" 39 29 17 \n"
" 39 2a 13 \n"
" 39 2b 15 \n"
" 39 2f 14 \n"
" 39 30 16 \n"
" 39 31 18 \n"
" 39 32 04 \n"
" 39 34 10 \n"
" 39 35 1f \n"
" 39 36 1f \n"
" 39 4d 14 \n"
" 39 4e 36 \n"
" 39 4f 36 \n"
" 39 53 36 \n"
" 39 71 30 \n"
" 39 79 11 \n"
" 39 7a 82 \n"
" 39 7b 8f \n"
" 39 7d 04 \n"
" 39 80 04 \n"
" 39 81 04 \n"
" 39 82 13 \n"
" 39 84 31 \n"
" 39 85 00 \n"
" 39 86 00 \n"
" 39 87 00 \n"
" 39 90 13 \n"
" 39 92 31 \n"
" 39 93 00 \n"
" 39 94 00 \n"
" 39 95 00 \n"
" 39 9c f4 \n"
" 39 9d 01 \n"
" 39 a0 0f \n"
" 39 a2 0f \n"
" 39 a3 02 \n"
" 39 a4 04 \n"
" 39 a5 04 \n"
" 39 c6 c0 \n"
" 39 c9 00 \n"
" 39 d9 80 \n"
" 39 e9 02 \n"
" 39 ff 25 \n"
" 39 fb 01 \n"
" 39 18 22 \n"
" 39 19 e4 \n"
" 39 21 40 \n"
" 39 66 d8 \n"
" 39 68 50 \n"
" 39 69 10 \n"
" 39 6b 00 \n"
" 39 6d 0d \n"
" 39 6e 48 \n"
" 39 72 41 \n"
" 39 73 4a \n"
" 39 74 d0 \n"
" 39 77 62 \n"
" 39 79 7e \n"
" 39 7d 03 \n"
" 39 7e 15 \n"
" 39 7f 00 \n"
" 39 84 4d \n"
" 39 cf 80 \n"
" 39 d6 80 \n"
" 39 d7 80 \n"
" 39 ef 20 \n"
" 39 f0 84 \n"
" 39 ff 26 \n"
" 39 fb 01 \n"
" 39 81 0f \n"
" 39 83 01 \n"
" 39 84 03 \n"
" 39 85 01 \n"
" 39 86 03 \n"
" 39 87 01 \n"
" 39 88 05 \n"
" 39 8a 1a \n"
" 39 8b 11 \n"
" 39 8c 24 \n"
" 39 8e 42 \n"
" 39 8f 11 \n"
" 39 90 11 \n"
" 39 91 11 \n"
" 39 9a 80 \n"
" 39 9b 04 \n"
" 39 9c 00 \n"
" 39 9d 00 \n"
" 39 9e 00 \n"
" 39 ff 27 \n"
" 39 fb 01 \n"
" 39 01 68 \n"
" 39 20 81 \n"
" 39 21 6a \n"
" 39 25 81 \n"
" 39 26 94 \n"
" 39 6e 00 \n"
" 39 6f 00 \n"
" 39 70 00 \n"
" 39 71 00 \n"
" 39 72 00 \n"
" 39 75 00 \n"
" 39 76 00 \n"
" 39 77 00 \n"
" 39 7d 09 \n"
" 39 7e 67 \n"
" 39 80 23 \n"
" 39 82 09 \n"
" 39 83 67 \n"
" 39 88 01 \n"
" 39 89 10 \n"
" 39 a5 10 \n"
" 39 a6 23 \n"
" 39 a7 01 \n"
" 39 b6 40 \n"
" 39 e5 02 \n"
" 39 e6 d3 \n"
" 39 eb 03 \n"
" 39 ec 28 \n"
" 39 ff 2a \n"
" 39 fb 01 \n"
" 39 00 91 \n"
" 39 03 20 \n"
" 39 07 50 \n"
" 39 0a 70 \n"
" 39 0c 04 \n"
" 39 0d 40 \n"
" 39 0f 01 \n"
" 39 11 e0 \n"
" 39 15 0f \n"
" 39 16 a4 \n"
" 39 19 0f \n"
" 39 1a 78 \n"
" 39 1b 23 \n"
" 39 1d 36 \n"
" 39 1e 3e \n"
" 39 1f 3e \n"
" 39 20 3e \n"
" 39 28 fd \n"
" 39 29 12 \n"
" 39 2a e1 \n"
" 39 2d 0a \n"
" 39 30 49 \n"
" 39 33 96 \n"
" 39 34 ff \n"
" 39 35 40 \n"
" 39 36 de \n"
" 39 37 f9 \n"
" 39 38 45 \n"
" 39 39 d9 \n"
" 39 3a 49 \n"
" 39 4a f0 \n"
" 39 7a 09 \n"
" 39 7b 40 \n"
" 39 7f f0 \n"
" 39 83 0f \n"
" 39 84 a4 \n"
" 39 87 0f \n"
" 39 88 78 \n"
" 39 89 23 \n"
" 39 8b 36 \n"
" 39 8c 7d \n"
" 39 8d 7d \n"
" 39 8e 7d \n"
" 39 ff 20 \n"
" 39 fb 01 \n"
" 39 b0 00 00 00 17 00 49 00 6a 00 89 00 9f 00 b6 00 c8 \n"
" 39 b1 00 d9 01 10 01 3a 01 7a 01 a9 01 f2 02 2d 02 2e \n"
" 39 b2 02 64 02 a3 02 ca 03 00 03 1e 03 4a 03 59 03 6a \n"
" 39 b3 03 7d 03 93 03 ab 03 c8 03 ec 03 fe 00 00 \n"
" 39 b4 00 00 00 1b 00 51 00 71 00 90 00 a7 00 bf 00 d1 \n"
" 39 b5 00 e2 01 1a 01 43 01 83 01 b2 01 fa 02 34 02 36 \n"
" 39 b6 02 6b 02 a8 02 d0 03 03 03 21 03 4d 03 5b 03 6b \n"
" 39 b7 03 7e 03 94 03 ac 03 c8 03 ec 03 fe 00 00 \n"
" 39 b8 00 00 00 1b 00 51 00 72 00 92 00 a8 00 bf 00 d1 \n"
" 39 b9 00 e2 01 18 01 42 01 81 01 af 01 f5 02 2f 02 31 \n"
" 39 ba 02 68 02 a6 02 cd 03 01 03 1f 03 4a 03 59 03 6a \n"
" 39 bb 03 7d 03 93 03 ab 03 c8 03 ec 03 fe 00 00 \n"
" 39 ff 21 \n"
" 39 fb 01 \n"
" 39 b0 00 00 00 17 00 49 00 6a 00 89 00 9f 00 b6 00 c8 \n"
" 39 b1 00 d9 01 10 01 3a 01 7a 01 a9 01 f2 02 2d 02 2e \n"
" 39 b2 02 64 02 a3 02 ca 03 00 03 1e 03 4a 03 59 03 6a \n"
" 39 b3 03 7d 03 93 03 ab 03 c8 03 ec 03 fe 00 00 \n"
" 39 b4 00 00 00 1b 00 51 00 71 00 90 00 a7 00 bf 00 d1 \n"
" 39 b5 00 e2 01 1a 01 43 01 83 01 b2 01 fa 02 34 02 36 \n"
" 39 b6 02 6b 02 a8 02 d0 03 03 03 21 03 4d 03 5b 03 6b \n"
" 39 b7 03 7e 03 94 03 ac 03 c8 03 ec 03 fe 00 00 \n"
" 39 b8 00 00 00 1b 00 51 00 72 00 92 00 a8 00 bf 00 d1 \n"
" 39 b9 00 e2 01 18 01 42 01 81 01 af 01 f5 02 2f 02 31 \n"
" 39 ba 02 68 02 a6 02 cd 03 01 03 1f 03 4a 03 59 03 6a \n"
" 39 bb 03 7d 03 93 03 ab 03 c8 03 ec 03 fe 00 00 \n"
" 39 ff 2c \n"
" 39 fb 01 \n"
" 39 61 1f \n"
" 39 62 1f \n"
" 39 7e 03 \n"
" 39 6a 14 \n"
" 39 6b 36 \n"
" 39 6c 36 \n"
" 39 6d 36 \n"
" 39 53 04 \n"
" 39 54 04 \n"
" 39 55 04 \n"
" 39 56 0f \n"
" 39 58 0f \n"
" 39 59 0f \n"
" 39 ff f0 \n"
" 39 fb 01 \n"
" 39 5a 00 \n"
" 39 ff 10 \n"
" 05 11 \n"
" FF C8 \n"
" 05 29 \n"
" FF 96 \n"
"</DSIInitSequence>"
"<DSITermSequence>"
" 05 28 \n"
" ff 10 \n"
" 05 10 \n"
" ff 32 \n"
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

    /* LDO1, LDO2 for DSI PHY/PLL are already turned on by system driver.*/

    /*Turn on LDO14 for V_LCD_VDDI_1P8 which is used by panel */
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_C, PM_LDO_12, 1800000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO12 to 1.8V\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_C, PM_LDO_13, 3000000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO12 to 3.0V\n");
    }
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_B, PM_LDO_6, 1200000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO6 to 1.2V\n");
    }
    
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_volt_level(PMIC_C, PM_LDO_10, 880000, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO5 to 0.88V\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_C, PM_LDO_12, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO12\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_C, PM_LDO_13, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO13\n");
    }

    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_B, PM_LDO_6, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO6\n");
    }
    
    if (PM_ERR_FLAG_SUCCESS != pm_ldo_sw_enable(PMIC_C, PM_LDO_10, PM_ON, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO10\n");
    }
     
    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(Default_DISP_LCD_BIAS_EN, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_HIGH_VALUE);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);
    
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
      case MDP_PMIC_BACKLIGHT_CONTROLTYPE_PWM:
      {
        /* LCD PWM Enable Pin */
        pm_gpio_cfg_mode(PMIC_C, PM_GPIO_7, PM_GPIO_DIG_OUT);   
        pm_gpio_set_voltage_source(PMIC_C, PM_GPIO_7, PM_GPIO_VIN0);  
        pm_gpio_set_out_src_cfg(PMIC_C, PM_GPIO_7, PM_GPIO_SRC_GND);
        pm_gpio_set_out_drv_str(PMIC_C, PM_GPIO_7, PM_GPIO_OUT_DRV_STR_HIGH);
        pm_gpio_set_output_level(PMIC_C, PM_GPIO_7, 1);
        pm_gpio_set_out_buf_cfg(PMIC_C, PM_GPIO_7, PM_GPIO_OUT_BUF_CFG_CMOS); 
      
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
        case EFI_PLATFORMINFO_TYPE_IDP:
        default:
          pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8*)nt36672e_60hz_fhd_plus_dsc_vid_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(nt36672e_60hz_fhd_plus_dsc_vid_xmldata);
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
          pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8*)dummy_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(dummy_xmldata);
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
