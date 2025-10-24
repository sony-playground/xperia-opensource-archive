/*=============================================================================

  File: MDPPlatformLib.c

  MDP platform specific functions

  Copyright (c) 2021 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFIPmicClkBuff.h>
#include <Protocol/EFITlmm.h>
#include <Protocol/EFIPmicLpg.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFIPmicVreg.h>
#include <Protocol/EFIPmicWled.h>
#include <Protocol/EFIPmicIbb.h>
#include <Protocol/EFIPmicLab.h>
#include <stdio.h>
#include "DDIChipInfo.h"
#include "MDPTypes.h"
#include "MDPPlatformLib.h"
#include "MDPPlatformLibPanelConfig.h"
#include "MDPSystem.h"
#include "MDPPeripherals.h"
#include "DisplayUtils.h"
#include "npa.h"
#include "pmapp_npa.h"
#include "DDITlmm.h"
#include "HALDSILib.h"

#ifdef FEATURE_XBOOT
#include <Library/XBootPanelLib.h>
#endif /* FEATURE_XBOOT */

/* -----------------------------------------------------------------------
** Defines
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Local functions
** ----------------------------------------------------------------------- */

/* Platform detection
 */
static MDP_Status ReadPlatformIDAndChipID(EFI_PLATFORMINFO_PLATFORM_INFO_TYPE *pPlatformInfo, EFIChipInfoIdType *pChipSetId, EFIChipInfoFamilyType *pChiSetFamily);
static MDP_Status DynamicDSIPanelDetection(MDP_Display_IDType eDisplayId, MDPPlatformPanelInfo *pPlatformPanel, uint32 *puPanelID, PlatformDSIDetectParams *pPanelList, uint32 uPanelCnt);

/* General helper functions
 */
static MDP_Status SetDefaultGPIOState(GpioStateType *pGPIOList);
static EFI_STATUS GetDisplayGpioValue(uint32 uGpioNum, TLMM_ValueType *pGpioValue);

/* External display default functions
 */
extern MDP_Status ExternalPanel_Default_PowerUp(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);
extern MDP_Status ExternalPanel_Default_PowerDown(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);
extern bool32     DP_USBPlugInvertedOrientation(void);

/*===========================================================================
 Local Configuration Definitions
 ===========================================================================*/

/*
* Dummy panel configuration, default fallback mode.
*
*/
const static int8 dummy_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"    <PanelName>VirtioDSI</PanelName>"
"    <PanelDescription>DSI Model (640x480 24bpp)</PanelDescription>"
"    <Group id=\"Active Timing\">"
"        <HorizontalActive>640</HorizontalActive>"
"        <HorizontalFrontPorch>13</HorizontalFrontPorch>"
"        <HorizontalBackPorch>14</HorizontalBackPorch>"
"        <HorizontalSyncPulse>15</HorizontalSyncPulse>"
"        <HorizontalSyncSkew>0</HorizontalSyncSkew>"
"        <HorizontalLeftBorder>0</HorizontalLeftBorder>"
"        <HorizontalRightBorder>0</HorizontalRightBorder>"
"        <VerticalActive>480</VerticalActive>"
"        <VerticalFrontPorch>11</VerticalFrontPorch>"
"        <VerticalBackPorch>12</VerticalBackPorch>"
"        <VerticalSyncPulse>13</VerticalSyncPulse>"
"        <VerticalSyncSkew>0</VerticalSyncSkew>"
"        <VerticalTopBorder>0</VerticalTopBorder>"
"        <VerticalBottomBorder>0</VerticalBottomBorder>"
"        <InvertDataPolarity>False</InvertDataPolarity>"
"        <InvertVsyncPolairty>False</InvertVsyncPolairty>"
"        <InvertHsyncPolarity>False</InvertHsyncPolarity>"
"        <BorderColor>0x0</BorderColor>"
"    </Group>"
"    <Group id=\"Display Interface\">"
"        <InterfaceType>8</InterfaceType>"
"        <InterfaceColorFormat>3</InterfaceColorFormat>"
"    </Group>"
"    <Group id=\"DSI Interface\">"
"        <DSIChannelId>1</DSIChannelId>"
"        <DSIVirtualId>0</DSIVirtualId>"
"        <DSIColorFormat>36</DSIColorFormat>"
"        <DSITrafficMode>0</DSITrafficMode>"
"        <DSILanes>3</DSILanes>"
"        <DSIHsaHseAfterVsVe>False</DSIHsaHseAfterVsVe>"
"        <DSILowPowerModeInHFP>False</DSILowPowerModeInHFP>"
"        <DSILowPowerModeInHBP>False</DSILowPowerModeInHBP>"
"        <DSILowPowerModeInHSA>False</DSILowPowerModeInHSA>"
"        <DSILowPowerModeInBLLPEOF>False</DSILowPowerModeInBLLPEOF>"
"        <DSILowPowerModeInBLLP>False</DSILowPowerModeInBLLP>"
"        <DSIRefreshRate>0x3c0000</DSIRefreshRate>"
"    </Group>"
"        <DisplayPrimaryFlags>0x2</DisplayPrimaryFlags>"
"    <DSIInitSequence>"
"    </DSIInitSequence>";


/*===========================================================================
Function Definitions
===========================================================================*/

/**********************************************************************************************
*
* FUNCTION: PlatformClientInit()
*
* DESCRIPTION:
*   Initialize NPA client.
*
***********************************************************************************************/
MDP_Status PlatformClientInit(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status    Status = MDP_STATUS_OK;

  NPAClientName aNPAClientName[MDP_DISPLAY_MAX] =
  {
    /* Both primary and secondary display are sharing the same NPA nodes */
    {MDP_DISPLAY_PRIMARY,  PMIC_NPA_GROUP_ID_DISP_PRIM_AMOLED,     "DisplayPrim"},
    {MDP_DISPLAY_PRIMARY,  PMIC_NPA_GROUP_ID_DISP_PRIM_AMOLED,     "DisplaySec"},
  };

  if (eDisplayId >= MDP_DISPLAY_MAX )
  {
    DEBUG ((EFI_D_ERROR, "DisplayDxe: Unsupported Display ID for power init.\n"));
    Status =  MDP_STATUS_FAILED;
  }
  else if (NULL == pPowerParams->sNPAClient[eDisplayId])
  {
    if ((eDisplayId != aNPAClientName[eDisplayId].eMapDisplayId) &&
        (NULL       != pPowerParams->sNPAClient[aNPAClientName[eDisplayId].eMapDisplayId]))
    {
      pPowerParams->sNPAClient[eDisplayId]        = pPowerParams->sNPAClient[aNPAClientName[eDisplayId].eMapDisplayId];
      pPowerParams->bDisplayNPAStatus[eDisplayId] = TRUE;
    }
    else
    {
      pPowerParams->sNPAClient[eDisplayId] = npa_create_sync_client(aNPAClientName[eDisplayId].cResourceName, aNPAClientName[eDisplayId].cClientName, NPA_CLIENT_REQUIRED); 

      if (NULL == pPowerParams->sNPAClient[eDisplayId])
      {
        DEBUG ((EFI_D_ERROR, "DisplayDxe: Failed to retrieve NPA Display Handle for Display ID %x.\n", eDisplayId ));
        Status =  MDP_STATUS_FAILED;
      }
      else
      {
        pPowerParams->bDisplayNPAStatus[eDisplayId] = TRUE;
      }
    }
  }

  return Status;
}

/**********************************************************************************************
*
* FUNCTION: DynamicDSIPanelDetection()
*
* DESCRIPTION:
*   Detect DSI panels by doing a DSI read specific to each panels.
*   This function could be used as sample for OEM to detect DSI panels,
*   it is not a complete implementation of all possible combinations of read
*   commands that could be needed for this detection.
*
*   Return success only if a DSI panel was correctly detected and the information
*   is updated in pPlatformParams->sPlatformPanel
*
***********************************************************************************************/
static MDP_Status DynamicDSIPanelDetection(MDP_Display_IDType eDisplayId, MDPPlatformPanelInfo *pPlatformPanel, uint32 *puPanelID, PlatformDSIDetectParams *pPanelList, uint32 uPanelCnt)
{
  MDP_Status   Status          = MDP_STATUS_NOT_SUPPORTED;
#ifdef FEATURE_XBOOT
  Status = SOMC_DynamicDSIPanelDetection(pPlatformPanel);
#else
  bool32       bDumpPanelId    = FALSE;
  bool32       bCPhyMode       = (MDP_DISPLAY_AUTODETECT_MIPI_CPHY == pPlatformPanel->eAutoDetect) ? TRUE : FALSE;

  // do minimal DSI init
  if (MDP_STATUS_OK == DSIDriver_MinimalInit(eDisplayId, bCPhyMode))
  {
    uint8       panelID[PLATFORM_PANEL_ID_MAX_COMMANDS];
    uint32      uPanelIndex;
    bool32      bMatch         = FALSE;
    uint32      uPrevClkConfig = 0;

    // go through all possible panels
    for (uPanelIndex = 0; uPanelIndex < uPanelCnt; uPanelIndex++)
    {
      uint8     readback[DSI_READ_READBACK_SIZE];
      uint32    readSize                          = sizeof(readback);
      int       iCommandIndex                     = 0;
      uint32    uClkConfig                        = (MDPPLATFORM_PANEL_DETECT_FLAG_CLOCK_FORCEHS &
                                                     pPanelList[uPanelIndex].uFlags);

      // Check if there is any change in the clock config and set it accordingly
      if (uPrevClkConfig != uClkConfig)
      {
        if (MDP_STATUS_OK != DSIDriver_ConfigClockLane(eDisplayId, uClkConfig))
        {
          DEBUG((EFI_D_ERROR, "Display: DSIDriver_ConfigClockLane failed\n"));
        }

        uPrevClkConfig = uClkConfig;
      }

      // Reprogram the DSI lane swap based on remap order
      if (MDP_STATUS_OK != DSIDriver_RemapLane(eDisplayId, pPanelList[uPanelIndex].uLaneRemapOrder))
      {
        DEBUG((EFI_D_WARN, "Display: DSIDriver_RemapLane failed\n"));
      }

      // Allow debug option to scan panel registers (used to help generate a uniquie panel ID for detection)
      if (TRUE == bDumpPanelId)
      {
        DsiPanelDumpRegisters();
        // Dump just once
        bDumpPanelId = FALSE;
      }

      // clear the panel ID
      MDP_OSAL_MEMZERO(panelID, PLATFORM_PANEL_ID_MAX_COMMANDS);

      // for each possible panel ID read
      for(iCommandIndex = 0; iCommandIndex<PLATFORM_PANEL_ID_MAX_COMMANDS; iCommandIndex++)
      {
        uint32         uRetryCount = 0;

        // if read command is 0, then stop reading panel ID
        if ((0 == pPanelList[uPanelIndex].panelIdCommands[iCommandIndex].address[0]) &&
            (0 == pPanelList[uPanelIndex].panelIdCommands[iCommandIndex].address[1]) )
        {
          break;
        }
        // DSI read
        bMatch = FALSE;

        uRetryCount = 0;
        do
        {
          // clear the readback buffer
          MDP_OSAL_MEMZERO(&readback[0], readSize);
          readSize = sizeof(readback);
          Status = DSIDriver_Read(eDisplayId,
                                  pPanelList[uPanelIndex].uCmdType,
                                  pPanelList[uPanelIndex].panelIdCommands[iCommandIndex].address,
                                  sizeof(pPanelList[uPanelIndex].panelIdCommands[iCommandIndex].address),
                                  readback,
                                  &readSize,
                                  0);

          uRetryCount++;
        } while((uRetryCount < pPanelList[uPanelIndex].uTotalRetry) &&
               ((MDP_STATUS_OK != Status)                           ||
                (0 == readSize)));

        if ((uRetryCount <= pPanelList[uPanelIndex].uTotalRetry) &&
            (0 != readSize))
        {
          // Read was successful, now check the data is what we expect
          if (0 == CompareMem(readback, pPanelList[uPanelIndex].panelIdCommands[iCommandIndex].expectedReadback, readSize))
          {
            panelID[iCommandIndex] = readback[0];    // store the first byte of readback as panel ID
            bMatch                 = TRUE;                       // mark one panel ID matched
          }
        }

        // if any panel ID is not matched, then go to detect next panel in the list
        if(FALSE == bMatch)
        {
          break;
        }
      }

      // if all panel IDs are matched for a specific panel, store settings and stop
      if(TRUE == bMatch)
      {
        // store matched panel configuration xml data
        MDPPlatformSetPanelName(pPlatformPanel->szName, pPanelList[uPanelIndex].szName);

        // return the final combined panel ID
        *puPanelID = (panelID[0]<<16) | (panelID[1]<<8) | (panelID[2]);
        Status     = MDP_STATUS_OK;
        DEBUG((EFI_D_WARN, "Detected panel id:%08x\n", *puPanelID));
        break;
      }
      else
      {
        DEBUG((EFI_D_WARN, "Dynamic-Detected panel Failed\n"));
        Status = MDP_STATUS_FAILED;
      }
    }

    // Close the DSI context opened in DSIDriver_MinimalInit()
    DSIDriver_Close(eDisplayId);
  }
#endif /* FEATURE_XBOOT */
  return Status;
}


/**********************************************************************************************
*
* FUNCTION: PlatformConfigRemap()
*
* DESCRIPTION:
*   Remapping of the platform configuration enumeration based on platform properties.
*
***********************************************************************************************/
static MDPPlatformConfigType PlatformConfigRemap(MDPPlatformInfo *pPlatformConfig, MDPPlatformConfigType eConfig)
{
  MDPPlatformConfigType eRemappedConfig;

  // In SW render mode bypass all configuration that manipulate the hardware
  if ((NULL !=  pPlatformConfig) &&
      (TRUE == pPlatformConfig->bSWRender))
  {
    switch (eConfig)
    {
      case MDPPLATFORM_CONFIG_POWERUP:
      case MDPPLATFORM_CONFIG_POWERDOWN:
      case MDPPLATFORM_CONFIG_SETBACKLIGHT:
      case MDPPLATFORM_CONFIG_RESETPANEL:
      case MDPPLATFORM_CONFIG_SETGPIOSTATE:

        // In SW render mode don't execute these hardware configurations
        eRemappedConfig = MDPPLATFORM_CONFIG_BYPASS;

        break;
     default:

        // Default mapping (output = input)
        eRemappedConfig = eConfig;

        break;
   }
 }
 else
 {
    // Default mapping (output = input)
    eRemappedConfig = eConfig;
 }

 return eRemappedConfig;
}


/**********************************************************************************************
*
* FUNCTION: MDPPlatformConfigure()
*
* DESCRIPTION:
*   The function is used to configure display, control power and brightness etc.
*
***********************************************************************************************/
MDP_Status MDPPlatformConfigure(MDP_Display_IDType eDisplayId, MDPPlatformConfigType eConfig, MDPPlatformParams *pPlatformParams)
{
  MDP_Status               eStatus               = MDP_STATUS_OK;
  MDPPlatformConfigType    ePlatformConfig;

  /* Static information, initial once during the first call */
  static MDPPlatformInfo         sPlatformInfo;
  static Panel_PowerCtrlParams   sPanelPowerCtrl;
  static MDPPlatformPanelInfo    sPlatformPanel[MDP_DISPLAY_MAX];
  MDPPlatformPanelFunctionTable *pMDPSupportPanelFunctions = MDP_GET_PANELFUNC(eDisplayId);

  // Get remapped platform configuration enum
  ePlatformConfig = PlatformConfigRemap(&sPlatformInfo, eConfig);

  switch (ePlatformConfig)
  {
  case MDPPLATFORM_CONFIG_INIT:
    MDP_OSAL_MEMZERO(&sPlatformInfo,              sizeof(MDPPlatformInfo));
    MDP_OSAL_MEMZERO(&sPanelPowerCtrl,            sizeof(Panel_PowerCtrlParams));
    MDP_OSAL_MEMZERO(sPlatformPanel,              sizeof(sPlatformPanel));
    MDP_OSAL_MEMZERO(&gMDPSupportPanelFunctions,  sizeof(MDPPlatformPanelFunctionTable)*MDP_DISPLAY_MAX);
    MDP_OSAL_MEMZERO(&asPanelConfig,              sizeof(PanelConfigType)*MDP_DISPLAY_MAX);

    // Read the platform ID once
    if (MDP_STATUS_OK != ReadPlatformIDAndChipID(&sPlatformInfo.sEFIPlatformType, &sPlatformInfo.sEFIChipSetId, &sPlatformInfo.sEFIChipSetFamily))
    {
      sPlatformInfo.bSWRender = TRUE;
    }
    break;

  case MDPPLATFORM_CONFIG_SW_RENDERER:

    if (NULL == pPlatformParams)
    {
      eStatus = MDP_STATUS_BAD_PARAM;
    }
    else if (EFI_PLATFORMINFO_TYPE_VIRTIO  == sPlatformInfo.sEFIPlatformType.platform)
    {
      // Emulation platform
      sPlatformInfo.bSWRender                  = FALSE;
      pPlatformParams->sPlatformInfo.bSWRender = FALSE;
    }
    else if (TRUE == PcdGetBool(PcdDisplayForceSwRenderer))
    {
      // Force SW render mode for emulation and unknown platforms
      pPlatformParams->sPlatformInfo.bSWRender = TRUE;
      // Store that an override has been requested by the caller
      sPlatformInfo.bSWRenderOverrride         = pPlatformParams->sPlatformInfo.bSWRenderOverrride;
      // Cache that SW Rendering is enabled
      sPlatformInfo.bSWRender                  = TRUE;
    }
    /* Setup display panel configurations according to CDT */
    else if (MDP_STATUS_OK != MDPPlatformSetupPanelConfig(eDisplayId, &sPlatformPanel[eDisplayId], &sPlatformInfo, &pPlatformParams->sPlatformInfo))
    {
      eStatus = MDP_STATUS_FAILED;
    }
    else if (TRUE == sPlatformInfo.bSWRender)
    {
      // SW Render mode is enabled already, just return the status
      pPlatformParams->sPlatformInfo.bSWRender = TRUE;
    }
    else
    {
      // Force SW render mode off
      sPlatformInfo.bSWRender                  = FALSE;
      // Report SW render mode is disabled
      pPlatformParams->sPlatformInfo.bSWRender = FALSE;
    }
    break;
  case MDPPLATFORM_CONFIG_GETPANELCONFIG:
    {
      if (NULL == pPlatformParams)
      {
        eStatus = MDP_STATUS_BAD_PARAM;
      }
      else
      {
        // Retrieve panel configuration (could be dependent on the interface)
        switch (eDisplayId)
        {
        case MDP_DISPLAY_PRIMARY:
        case MDP_DISPLAY_SECONDARY:
          {
            uint32                    uPanelID   = 0;
            PlatformDSIDetectParams  *pPanelList = NULL;
            UINT32                    uPanelCnt  = 0;

            MDPPlatformGetPanelList(sPlatformPanel[eDisplayId].eAutoDetect, &pPanelList, &uPanelCnt, NULL);

            if (TRUE == sPlatformInfo.bSWRender)
            {
              pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)dummy_xmldata;
              pPlatformParams->sPlatformPanel.uConfigSize     = sizeof (dummy_xmldata);
              MDPPlatformClearPanelName(pPlatformParams->sPlatformPanel.szName);
            }
            else
            {
              switch (sPlatformInfo.sEFIPlatformType.platform)
              {
#ifdef FEATURE_XBOOT
                case EFI_PLATFORMINFO_TYPE_QRD:
#endif /* FEATURE_XBOOT */
                case EFI_PLATFORMINFO_TYPE_CDP:
                {
                  if ((MDP_DISPLAY_AUTODETECT_DISABLE    != sPlatformPanel[eDisplayId].eAutoDetect) &&
                      (MDP_STATUS_OK                     == DynamicDSIPanelDetection(eDisplayId, &sPlatformPanel[eDisplayId], &uPanelID, pPanelList, uPanelCnt)))
                  {
#ifdef FEATURE_XBOOT
                    // Dummy Panel Power OFF
                    if (MDP_STATUS_OK != (eStatus = MDPPlatformConfigure(MDP_DISPLAY_PRIMARY, MDPPLATFORM_CONFIG_POWERDOWN, NULL)))
                    {
                      DEBUG((EFI_D_ERROR, "MDPLib: MDPPlatformConfigure(MDPPLATFORM_CONFIG_POWERDOWN) failed!\n"));
                    }
#endif /* FEATURE_XBOOT */
                    /* Detected */
                    sPlatformPanel[eDisplayId].uPanelId       = uPanelID;
                    sPlatformInfo.uPrimaryPanelId             = uPanelID;

                    /* Always re-setup panel config for the new detected panel */
                    if (NULL == MDPPlatformSelectPanelConfig(eDisplayId, sPlatformPanel[eDisplayId].szName, &sPlatformInfo.bSWRender))
                    {
                      DEBUG((EFI_D_WARN, "MDPPlatformConfigure: MDPPlatformSelectPanelConfig no physical or simulation panel found\n"));
                    }
#ifdef FEATURE_XBOOT
                    //Panel Specific Power ON sequence
                    if (MDP_STATUS_OK != (eStatus = MDPPlatformConfigure(MDP_DISPLAY_PRIMARY, MDPPLATFORM_CONFIG_POWERUP, NULL)))
                    {
                      DEBUG((EFI_D_ERROR, "MDPLib: MDPPlatformConfigure(MDPPLATFORM_CONFIG_POWERUP) failed!\n"));
                    }
#endif /* FEATURE_XBOOT */
                  }
                  break;
                }
                case EFI_PLATFORMINFO_TYPE_MTP:
#ifndef FEATURE_XBOOT
                case EFI_PLATFORMINFO_TYPE_QRD:
#endif /* !FEATURE_XBOOT */
                default:
                {
                  break;
                }
              }

              // Get the panel xml configurations.
              if ((FALSE == sPlatformInfo.bSWRender) &&
                  (MDP_STATUS_OK == MDPPlatformGetPanelXmlConfig(eDisplayId, &sPlatformPanel[eDisplayId])))
              {
                /* Copy the panel configurations to pPlatformParams->sPlatformPanel */
                MDP_OSAL_MEMCPY(&pPlatformParams->sPlatformPanel, &sPlatformPanel[eDisplayId], sizeof(MDPPlatformPanelInfo));
              }
              else
              {
                pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)dummy_xmldata;
                pPlatformParams->sPlatformPanel.uConfigSize     = sizeof (dummy_xmldata);
                MDPPlatformClearPanelName(pPlatformParams->sPlatformPanel.szName);
              }
            }
          }
          break;

        case MDP_DISPLAY_EXTERNAL:
          switch (PcdGet32(PcdExtDisplayType))
          {
            case PCD_EXTERNAL_DISPLAY_DP:
              pPlatformParams->sDPConfig.bInvertPlugPolarity = DP_USBPlugInvertedOrientation();

              // For Nazgul, DP Phy lane to pad connection is the reverse of DP alt mode over usb type-c spec defined mapping
              pPlatformParams->sDPConfig.bReversePhyDataPath = TRUE;
              break;

            default:
              break;
          }
          break;

        default:
          break;
        }
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
        case EFI_PLATFORMINFO_TYPE_HDK:
        {
          /* Check for common power or panel specific power,
           * Common Power : pPlatformParams is NULL or uFlags is 0x0,
           * Panel Power  : uFlags is set to panel specific power flag.
           */
          if ((NULL                          != pPlatformParams) &&
              (POWERCONFIG_FLAGS_PANEL_POWER  & pPlatformParams->sPowerConfig.uFlags))
          {
            switch (sPlatformPanel[eDisplayId].uPanelId)
            {
            default:
              // OEM to populate panel specific power up.
              break;
            }
          }
          else
          {
            // Primary Power Sequence
            if (NULL != pMDPSupportPanelFunctions->pPanel_PowerUp)
            {
              if (MDP_STATUS_OK != (eStatus = pMDPSupportPanelFunctions->pPanel_PowerUp(eDisplayId, &sPanelPowerCtrl)))
              {
                DEBUG((EFI_D_WARN, "DisplayDxe: Primary Power Up Sequence failed (%d)\n", eStatus));
              }
            }
          }
          break;

        }
        default:
          break;
        }
        break;

      case MDP_DISPLAY_EXTERNAL:
        // Config based on the platform
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
        case EFI_PLATFORMINFO_TYPE_MTP:
        case EFI_PLATFORMINFO_TYPE_QRD:
        case EFI_PLATFORMINFO_TYPE_HDK:
          if ((NULL                          != pPlatformParams) &&
              (POWERCONFIG_FLAGS_PANEL_POWER  & pPlatformParams->sPowerConfig.uFlags))
          {
            // Do nothing for external panel specific power.
          }
          else
          {
            eStatus = ExternalPanel_Default_PowerUp(eDisplayId, &sPanelPowerCtrl);
          }
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
        case EFI_PLATFORMINFO_TYPE_HDK:
          /* Check for common power or panel specific power,
           * Common Power : pPlatformParams is NULL or uFlags is 0x0,
           * Panel Power  : uFlags is set to panel specific power flag.
           */
          if ((NULL                          != pPlatformParams) &&
              (POWERCONFIG_FLAGS_PANEL_POWER  & pPlatformParams->sPowerConfig.uFlags))
          {
            switch (sPlatformPanel[eDisplayId].uPanelId)
            {
            default:
              // OEM to populate panel specific power down.
              break;
            }
          }
          else
          {
            if (NULL != pMDPSupportPanelFunctions->pPanel_PowerDown)
            {
              if (MDP_STATUS_OK != (eStatus = pMDPSupportPanelFunctions->pPanel_PowerDown(eDisplayId, &sPanelPowerCtrl)))
              {
                DEBUG((EFI_D_WARN, "DisplayDxe: Primary Power Down Sequence failed (%d)\n", eStatus));
              }
            }

            sPanelPowerCtrl.bBacklightEnabled = FALSE; /* wled is turned off */
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
        case EFI_PLATFORMINFO_TYPE_MTP:
        case EFI_PLATFORMINFO_TYPE_QRD:
        case EFI_PLATFORMINFO_TYPE_HDK:
          if ((NULL                          != pPlatformParams) &&
              (POWERCONFIG_FLAGS_PANEL_POWER  & pPlatformParams->sPowerConfig.uFlags))
          {
            // Do nothing for external panel specific power.
          }
          else
          {
            eStatus = ExternalPanel_Default_PowerDown(eDisplayId, &sPanelPowerCtrl);
          }
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

  case MDPPLATFORM_CONFIG_SETBACKLIGHT:
    {
      if (NULL == pPlatformParams)
      {
        eStatus = MDP_STATUS_BAD_PARAM;
      }
      else
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
          case EFI_PLATFORMINFO_TYPE_HDK:

            if (FALSE == sPanelPowerCtrl.bBacklightEnabled)
            {
              if (NULL != pMDPSupportPanelFunctions->pPanel_Brightness_Enable)
              {
                if (MDP_STATUS_OK != (eStatus = pMDPSupportPanelFunctions->pPanel_Brightness_Enable(eDisplayId, &sPanelPowerCtrl)))
                {
                  DEBUG((EFI_D_WARN, "MDPPlatformConfig: Backlight enabled failed\n"));
                }
              }

              sPanelPowerCtrl.bBacklightEnabled = TRUE;
            }

            if (NULL != pMDPSupportPanelFunctions->pPanel_Brightness_Level)
            {
              if (MDP_STATUS_OK != (eStatus = pMDPSupportPanelFunctions->pPanel_Brightness_Level(eDisplayId, &pPlatformParams->sBacklightConfig)))
              {
                DEBUG((EFI_D_WARN, "MDPPlatformConfig: Backlight level control failed\n"));
              }
            }
            break;

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
    }
    break;

  case MDPPLATFORM_CONFIG_GETPANELID:
    {
    }
    break;

  case MDPPLATFORM_CONFIG_GETPLATFORMINFO:
    {
      if (NULL == pPlatformParams)
      {
        eStatus = MDP_STATUS_BAD_PARAM;
      }
      else
      {
        //
        // Return platform information
        //
        MDP_OSAL_MEMCPY(&pPlatformParams->sPlatformInfo, &sPlatformInfo, sizeof(MDPPlatformInfo));
      }
    }
    break;

  case MDPPLATFORM_CONFIG_RESETPANEL:
    {
      if (NULL == pPlatformParams)
      {
        eStatus = MDP_STATUS_BAD_PARAM;
      }
      else
      {

         if ((MDP_RESET_STATE_INVALID == (pPlatformParams->sPlatformPanelReset.uResetGpio)) &&
             (NULL                    != pMDPSupportPanelFunctions->pMDPPlatformPanelGpio))
         {
           sPanelPowerCtrl.uResetGpio                      = pMDPSupportPanelFunctions->pMDPPlatformPanelGpio->uDispResetGpio;
           pPlatformParams->sPlatformPanelReset.uResetGpio = pMDPSupportPanelFunctions->pMDPPlatformPanelGpio->uDispResetGpio;
         }
         else
         {
           sPanelPowerCtrl.uResetGpio = pPlatformParams->sPlatformPanelReset.uResetGpio;
         }

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
           case EFI_PLATFORMINFO_TYPE_HDK:

             if (NULL != pMDPSupportPanelFunctions->pPanel_Reset)
             {
               if (MDP_STATUS_OK != (eStatus = pMDPSupportPanelFunctions->pPanel_Reset(&pPlatformParams->sPlatformPanelReset)))
               {
                DEBUG((EFI_D_WARN, "MDPPlatformConfig: Panel reset failed (%d)\n", eStatus));
               }
             }
             break;
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
    }
    break;

  case MDPPLATFORM_CONFIG_SETGPIOSTATE:
    {
      if (NULL == pPlatformParams)
      {
        eStatus = MDP_STATUS_BAD_PARAM;
      }
      else
      {
        eStatus = SetDefaultGPIOState(&pPlatformParams->sGPIOState);
      }
    }
    break;

  case MDPPLATFORM_CONFIG_GETPANELXMLINFO:
    {
      if (NULL == pPlatformParams)
      {
        eStatus = MDP_STATUS_BAD_PARAM;
      }
      else
      {
        PlatformDSIDetectParams  *pUEFIPanelList    = NULL;
        UINT32                    uPanelListLen     = 0;

        MDPPlatformGetPanelList(sPlatformPanel[eDisplayId].eAutoDetect, &pUEFIPanelList, &uPanelListLen, NULL);

        // Return the raw xml information if it is within range.
        if (pPlatformParams->sPanelXMLInfo.uIndex >= uPanelListLen)
        {
          eStatus = MDP_STATUS_FAILED;
        }
        else if (TRUE == sPlatformInfo.bSWRender)
        {
          pPlatformParams->sPanelXMLInfo.pPanelXMLConfig = (int8 *)dummy_xmldata;
          pPlatformParams->sPanelXMLInfo.uPanelXMLSize   = sizeof (dummy_xmldata);
        }
        else
        {
          MDPPlatformPanelInfo sPlatformPanelInfo;

          MDP_OSAL_MEMZERO(&sPlatformPanelInfo, sizeof(MDPPlatformPanelInfo));

          if (MDP_STATUS_OK == MDPPlatformGetPanelXmlConfig(eDisplayId, &sPlatformPanelInfo))
          {
            pPlatformParams->sPanelXMLInfo.pPanelXMLConfig = (int8*)sPlatformPanelInfo.pPanelXMLConfig;
            pPlatformParams->sPanelXMLInfo.uPanelXMLSize   = sPlatformPanelInfo.uConfigSize;
          }
          else
          {
            pPlatformParams->sPanelXMLInfo.pPanelXMLConfig = (int8 *)dummy_xmldata;
            pPlatformParams->sPanelXMLInfo.uPanelXMLSize   = sizeof (dummy_xmldata);
          }
        }
      }
    }
    break;

  case MDPPLATFORM_CONFIG_GETSPRXMLINFO:
    {
      if (NULL == pPlatformParams)
      {
        eStatus = MDP_STATUS_BAD_PARAM;
      }
      else
      {
        eStatus = MDP_STATUS_NOT_SUPPORTED;
      }
    }
    break;

  case MDPPLATFORM_CONFIG_BYPASS:
    {
      // SW Render Bypass mode
      eStatus = MDP_STATUS_OK;
    }
    break;

  case MDPPLATFORM_CONFIG_SELECTPANELCONFIG:
    {
      if (NULL == pPlatformParams)
      {
        eStatus = MDP_STATUS_BAD_PARAM;
      }
      else
      {
        pPlatformParams->sPanelConfigInfo.pPanelConfig = MDPPlatformSelectPanelConfig(eDisplayId, pPlatformParams->sPlatformPanel.szName, NULL);

        if (NULL == pPlatformParams->sPanelConfigInfo.pPanelConfig)
        {
          eStatus = MDP_STATUS_NOT_SUPPORTED;
        }
        else
        {
          MDPPlatformSetPanelName(sPlatformPanel[eDisplayId].szName, pPlatformParams->sPlatformPanel.szName);
        }
      }
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
        pPlatformParams->pPanelConfig = GET_PANEL_CONFIG(eDisplayId);
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
* FUNCTION: ReadPlatformIDAndChipID()
*
* DESCRIPTION:
*   Read the platform info.
*
***********************************************************************************************/
static MDP_Status ReadPlatformIDAndChipID(EFI_PLATFORMINFO_PLATFORM_INFO_TYPE *pPlatformInfo, EFIChipInfoIdType *pChipSetId, EFIChipInfoFamilyType *pChipSetFamily)
{
  MDP_Status                           eStatus                = MDP_STATUS_OK;
  EFI_PLATFORMINFO_PROTOCOL            *hPlatformInfoProtocol;
  EFI_CHIPINFO_PROTOCOL                *hChipInfoProtocol;

  if (EFI_SUCCESS == gBS->LocateProtocol(&gEfiPlatformInfoProtocolGuid,
                                         NULL,
                                         (VOID **)&hPlatformInfoProtocol))
  {
    if (EFI_SUCCESS != hPlatformInfoProtocol->GetPlatformInfo(hPlatformInfoProtocol, pPlatformInfo))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: gEfiPlatformInfoProtocolGuid->GetPlatformInfo() failed.\n"));

      eStatus = MDP_STATUS_FAILED;
    }
  }
  else
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: gEfiPlatformInfoProtocolGuid protocol failed.\n"));

    eStatus = MDP_STATUS_FAILED;
  }

  // Default to emulation platform
  if (EFI_PLATFORMINFO_TYPE_UNKNOWN == pPlatformInfo->platform)
  {
    pPlatformInfo->platform = EFI_PLATFORMINFO_TYPE_VIRTIO;
  }

  // Read the chipset ID
  if (EFI_SUCCESS == gBS->LocateProtocol(&gEfiChipInfoProtocolGuid,
                                         NULL,
                                         (VOID **)&hChipInfoProtocol))
  {
     if (EFI_SUCCESS != hChipInfoProtocol->GetChipId(hChipInfoProtocol, pChipSetId))
     {
       DEBUG((EFI_D_WARN, "DisplayDxe: gEfiChipInfoProtocolGuid->GetChipId() failed. \n"));

       eStatus = MDP_STATUS_FAILED;
     }

     if (EFI_SUCCESS != hChipInfoProtocol->GetChipFamily(hChipInfoProtocol, pChipSetFamily))
     {
       DEBUG((EFI_D_WARN, "DisplayDxe: gEfiChipInfoProtocolGuid->GetChipFamily() failed. \n"));

       eStatus = MDP_STATUS_FAILED;
     }
  }
  else
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: gEfiChipInfoProtocolGuid protocol failed.\n"));

    eStatus = MDP_STATUS_FAILED;
  }

  return eStatus;
}


/**********************************************************************************************
*
* FUNCTION: SetDefaultGPIOState()
*
* DESCRIPTION:
*   The function toggles a list of GPIO's based on the requested configuration.
*
****************************************************************************/
static MDP_Status SetDefaultGPIOState(GpioStateType *pGPIOList)
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
           EFI_TLMM_PROTOCOL   *TLMMProtocol;

           if (EFI_SUCCESS == gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void**)&TLMMProtocol))
           {
             uint32 uCount;

             // Loop the list to configure all GPIOs.
             for (uCount=0;uCount<pGPIOList->uListSize;uCount++)
             {
                // Only try to program GPIOs that are within range, TLMM Macro (EFI_GPIO_CFG) supports up to 0x3FF
                if (pGPIOList->pGPIOList[uCount] < 0x3FF)
                {
                  uint32 uValue = (pGPIOList->uState>0)?GPIO_HIGH_VALUE:GPIO_LOW_VALUE;

                  // Setup GPIO
                  if (EFI_SUCCESS != TLMMProtocol->ConfigGpio((UINT32)EFI_GPIO_CFG(pGPIOList->pGPIOList[uCount], 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA), TLMM_GPIO_ENABLE))
                  {
                    DEBUG((EFI_D_ERROR, "DisplayDxe: Error configuring TLMM GPIO%d\n", uCount));

                  }

                  // Setup Output
                  if (EFI_SUCCESS != TLMMProtocol->GpioOut((UINT32)EFI_GPIO_CFG(pGPIOList->pGPIOList[uCount], 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA), uValue))
                  {
                    DEBUG((EFI_D_ERROR, "DisplayDxe: Error configuring TLMM GPIO%d\n", uCount));
                  }
                }
             }
           }
           else
           {
             eStatus = MDP_STATUS_NO_RESOURCES;
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


/**********************************************************************************************
*
* FUNCTION: GetDisplayGpioValue()
*
* DESCRIPTION:
*   The function can get the display gpio value.
*
***********************************************************************************************/
static EFI_STATUS GetDisplayGpioValue(uint32 uGpioNum, TLMM_ValueType *pGpioValue)
{
  EFI_STATUS           eStatus       = EFI_SUCCESS;
  EFI_TLMM_PROTOCOL   *TLMMProtocol  = NULL;

  if ((NULL         ==  pGpioValue) ||
      (EFI_SUCCESS  !=  gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void **)&TLMMProtocol)))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Invalid gpio value parameter or Locate TLMM protocol failed!\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else
  {
    UINT32 uGpioConfig = (UINT32)EFI_GPIO_CFG(uGpioNum, 0, GPIO_INPUT, GPIO_NO_PULL, GPIO_2MA);

    if (EFI_SUCCESS != (eStatus = TLMMProtocol->ConfigGpio(uGpioConfig, TLMM_GPIO_ENABLE)))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Configure display GPIO(%d) failed with status(%d)!\n", uGpioNum, eStatus));
    }

    if (EFI_SUCCESS != (eStatus = TLMMProtocol->GpioIn(uGpioConfig, pGpioValue)))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Get display GPIO(%d) value failed with status(%d)!\n", uGpioNum, eStatus));
    }
  }

  return eStatus;
}


#ifdef __cplusplus
}
#endif
