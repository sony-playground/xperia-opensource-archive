/*=============================================================================

  File: MDPLIb.c

  Source file for MDP functions


  Copyright (c) 2013-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>
#include "MDPLib.h"
#include "MDPLib_i.h"
#include "MDPSystem.h"
#include "MDPPlatformLib.h"
#include "DisplayUtils.h"
#include "ExternalDisplayDriver.h"
#include "DPInterface.h"
#include "MDPEDID.h"

/*=========================================================================
     Default Defines
==========================================================================*/
/* Default MDPInit Flags */
#define DEAFAULT_MDP_INIT_FLAGS                  (HAL_MDP_INIT_FLAGS_VBIF_CONFIGURATION |\
                                                  HAL_MDP_INIT_FLAGS_DISABLE_INTERRUPTS |\
                                                  HAL_MDP_INIT_FLAGS_CLEAR_INTERRUPTS)

/* Smart transfer time margin is 2ms for worst case */
#define MDP_SMART_TRANSFER_TIME_MARGIN            0.002

/*=========================================================================
     Local Static Variables
==========================================================================*/


/*=========================================================================
     Local Static Functions
==========================================================================*/


/* Function to detect the presence of external display
 */
static bool32 MDPDetectExtPlugin(MDP_Display_IDType eDisplayId, MDP_Panel_AttrType  *pPanelInfo, uint32 Flags);


/* Read UEFI variable DISABLEDISPLAY
 */
static bool32 MDPPlatformGetDisableDisplay(void);

/* Set MDSS base address
 */
static MDP_Status MDPPlatformSetMdssBase(EFIChipInfoFamilyType sEFIChipSetFamily);

/* Configuration parameters that are required to correctly setup the
   DSC related configuration like topology flags and resolution info
   for each compression encoder.
 */
static MDP_Status MDPSetupDSCProperty(MDP_Panel_AttrType *pPanelInfo);

/* Helper function to setup DSC
*/
static MDP_Status MDPConfigureLinkCompression(MDP_Panel_AttrType *pDisplayInfo);

/* Configuration default GPIO states
*/
static MDP_Status MDPSetGPIOState(MDP_Panel_AttrType *pDisplayInfo);

/* Get the highest bankbit based on DDR Type
*/
static uint32 MDPGetHighestBankBit();

/* Get the total bandwidth of all display devices and core clock value
*/
static MDP_Status MDPGetAggregatedCoreAndBandwidth(uint32 *pMaxCoreClock, uint64 *pBandwidth);

/* Give MDP a default version if found it's major version is invalid
*/
static MDP_Status MDPValidateVersion(MDP_HwPrivateInfo  *psMDPHwPrivateInfo);

/*  round up the Q16.16 format data
*/
static uint32 MDPRoundUpQ1616(uint32 data);

/* Check if panel FPS is beyond the SW Fuse 
*/
static void MDPCheckFpsFuse(MDP_Panel_AttrType* pDisplayInfo);

/*=========================================================================
     Globals
==========================================================================*/
extern uint8         *gpDSIInitSequenceBuffer;
extern uint8         *gpDSITermSequenceBuffer;
extern uint8         *gpDSIDscPpsBuffer;
extern uint8         *gpI2CInitSequenceBuffer;
extern uint8         *gpI2CTermSequenceBuffer;
MDP_HwPrivateInfo     gsMDPHwPrivateInfo;
MDP_Panel_AttrType    gDisplayInfo[MDP_DISPLAY_MAX];
MDP_ProfileLog       *gProfileLog = NULL;

/*Access Macro for gMDP_DSCMap */
#define MDP_GET_DSCMAP(_displayId_,_pingpongnum_)   (&gMDP_DSCMap[(_displayId_)<MDP_DISPLAY_MAX?(_displayId_):MDP_DISPLAY_PRIMARY][(_pingpongnum_)<MDP_DUAL_NUM_PINGPONGS?(_pingpongnum_):0])

/*DSC EngineID Mapping */
const MDP_DSCMapType gMDP_DSCMap[MDP_DISPLAY_MAX][MDP_DUAL_NUM_PINGPONGS] =
{
  {
    {MDP_DISPLAY_PRIMARY,   HAL_MDP_DSC_0},
    {MDP_DISPLAY_PRIMARY,   HAL_MDP_DSC_1},
  },
  {
    {MDP_DISPLAY_SECONDARY, HAL_MDP_DSC_2},
    {MDP_DISPLAY_SECONDARY, HAL_MDP_DSC_3},
  },
  {
    {MDP_DISPLAY_EXTERNAL,  HAL_MDP_DSC_NONE},
    {MDP_DISPLAY_EXTERNAL,  HAL_MDP_DSC_NONE},
  },
  {
    {MDP_DISPLAY_EXTERNAL2, HAL_MDP_DSC_NONE},
    {MDP_DISPLAY_EXTERNAL2, HAL_MDP_DSC_NONE},
  },
  {
    {MDP_DISPLAY_EXTERNAL3, HAL_MDP_DSC_NONE},
    {MDP_DISPLAY_EXTERNAL3, HAL_MDP_DSC_NONE},
  }
};

/* SMR Mask for MDP to route all MDP SIDs to a single Context Bank (from sid.mapping in ipcat)
 * MMU SID Masks and chip set family mapping
 */
static const sChip_MMUSidMasks asChip_MMUSidMasks[MDSS_BASEADDRESSMAPINGS_MAX] = {
    {EFICHIPINFO_FAMILY_WAIPIO, 0x402},               // for Waipio family
    {EFICHIPINFO_FAMILY_KAILUA, 0x002},               // for Kailua family
	{EFICHIPINFO_FAMILY_AURORA, 0x402},               // for Aurora family
};
static MDP_Status FindPlatformMMUSidMask (EFIChipInfoFamilyType	sEFIChipSetFamily, uint32 *pMMUSidMask);


/*=========================================================================
      Public APIs
==========================================================================*/

/****************************************************************************
*
** FUNCTION: MDPInit()
*/
/*!
* \brief
*   This function will perform the basic initialization and detection of the MDP core
*
* \param [out] pMDPInitParams   - Information regarding the hardware core
*        [in]  uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPInit(MDP_InitParamsType *pMDPInitParams, uint32 uFlags)
{
  MDP_Status          eStatus             = MDP_STATUS_OK;
  MDP_HwPrivateInfo  *psMDPHwPrivateInfo  = MDP_GETPRIVATEINFO();
  uint32              uMMUSidMask         = 0;

  MDP_LOG_FUNC_ENTRY("MDPInit", 0x00);
  
  MDP_OSAL_MEMZERO(psMDPHwPrivateInfo, sizeof(MDP_HwPrivateInfo));
  psMDPHwPrivateInfo->sEFIChipSetId = EFICHIPINFO_ID_UNKNOWN;

  if ((NULL == gpDSIInitSequenceBuffer ) ||
      (NULL == gpDSITermSequenceBuffer ))
  {
    gpDSIInitSequenceBuffer = (uint8*)MDP_OSAL_CALLOC(MDP_DSI_COMMAND_BUFFER_SIZE);
    gpDSITermSequenceBuffer = (uint8*)MDP_OSAL_CALLOC(MDP_DSI_COMMAND_BUFFER_SIZE);
  }

  if (NULL == gpDSIDscPpsBuffer )
  {
    gpDSIDscPpsBuffer = (uint8*)MDP_OSAL_CALLOC(MDP_DSI_DSC_PPS_TOTAL_PACKET_SIZE);
  }

  // Initialize I2C command buffer
  if ((NULL == gpI2CInitSequenceBuffer) ||
      (NULL == gpI2CTermSequenceBuffer))
  {
    gpI2CInitSequenceBuffer = (uint8*)MDP_OSAL_CALLOC(MDP_I2C_COMMAND_BUFFER_SIZE);
    gpI2CTermSequenceBuffer = (uint8*)MDP_OSAL_CALLOC(MDP_I2C_COMMAND_BUFFER_SIZE);
  }

  if ((NULL == gpDSIInitSequenceBuffer ) ||
      (NULL == gpDSITermSequenceBuffer ) ||
      (NULL == gpI2CInitSequenceBuffer)  ||
      (NULL == gpI2CTermSequenceBuffer)  ||
      (NULL == gpDSIDscPpsBuffer ))
  {
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (NULL == pMDPInitParams)
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    MDPPlatformParams     sPlatformParams;
    bool32                bSWRender  = FALSE;
    MDP_Display_IDType    eDisplayId = MDP_DISPLAY_PRIMARY;
    uint32                uNumValidDisplays = 0;

    if (MDP_INIT_FLAG_MINIMAL_INIT & uFlags)
    {
      //For minimal init do not clear the display context as it will be reused later.
    }
    else
    {
      // Default case is complete initialization, clear the display context.
      MDP_OSAL_MEMZERO(&gDisplayInfo, sizeof(gDisplayInfo));
    }

    // Need to know if the platform is hardware accelerated first. If it is not then we have to skip initialization of all HW.
    MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));

    for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_SECONDARY; eDisplayId++)
    {
      if (FALSE == pMDPInitParams->aSupportedDisplays[eDisplayId])
      {
        continue;
      }
      else if (MDP_STATUS_OK != (eStatus = MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_SW_RENDERER, &sPlatformParams)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDPPlatformConfigure(MDPPLATFORM_CONFIG_SW_RENDERER) failed!\n");
        continue;
      }
      else
      {
        uNumValidDisplays++;
      }
    }

    if ((0    == uNumValidDisplays)  ||
        (TRUE == sPlatformParams.sPlatformInfo.bSWRender))
    {
      // Update SW Render flag
      bSWRender = TRUE;
    }

    // Update SW render status
    psMDPHwPrivateInfo->bSWRender = bSWRender;

    //
    // Start hardware initialization, fall back to SW renderer in this path if key hardware functions fail
    //
    if (FALSE == bSWRender)
    {
      //Get the platform Chip ID and catch in gsMDPHwPrivateInfo
      if (MDP_STATUS_OK == (eStatus = MDPPlatformConfigure(MDP_DISPLAY_PRIMARY, MDPPLATFORM_CONFIG_GETPLATFORMINFO, &sPlatformParams)))
      {
        psMDPHwPrivateInfo->sEFIChipSetId     = sPlatformParams.sPlatformInfo.sEFIChipSetId;
        psMDPHwPrivateInfo->sEFIChipSetFamily = sPlatformParams.sPlatformInfo.sEFIChipSetFamily;
        psMDPHwPrivateInfo->eEFIPlatformInfo  = sPlatformParams.sPlatformInfo.sEFIPlatformType.platform;
      }

      // Hardware path
      //
      if (MDP_STATUS_OK != eStatus)
      {
        // Platform detection failed, cannot continue propagate error to caller
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: Failed to detect platform ID!\n");
      }
      else if (TRUE == Display_Utils_CheckPanelSkip())
      {
        //Panel override was set, either skip is forced by override
        //or this panel is not supported in bootloader
        //Fall back to SW render mode
        bSWRender = TRUE;

        // Panel is overridden to SW rendering mode, update internal SW render status to skip display resource release.
        psMDPHwPrivateInfo->bSWRender = bSWRender;
      }
      else if (MDP_STATUS_OK != (eStatus = MDPSetCoreClock(0x0)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: Failed to setup MDP core clocks!\n");

        // Fall back to SW render mode for error handling, skip updating internal SW render status to release display resources.
        bSWRender = TRUE;
      }
      //Set MDSS base address
      else if (MDP_STATUS_OK != (eStatus = MDPPlatformSetMdssBase(sPlatformParams.sPlatformInfo.sEFIChipSetFamily)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: MDPPlatformSetMdssBase() failed!\n");

        // Fall back to SW render mode for error handling, skip updating internal SW render status to release display resources.
        bSWRender = TRUE;
      }
      else
      {
        HAL_MDP_InitConfigType sInitConfig;

        /* Initialize highest bank bit based on DDR type */
        MDP_OSAL_MEMZERO(&sInitConfig, sizeof(sInitConfig));
        sInitConfig.uGpuHighestMemoryBankBit = MDPGetHighestBankBit();

        if (HAL_MDSS_STATUS_SUCCESS != HAL_MDP_Init(&sInitConfig, DEAFAULT_MDP_INIT_FLAGS))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: HAL_MDP_Init() failed!\n");

          // Fall back to SW render mode for error handling, skip updating internal SW render status to release display resources.
          bSWRender = TRUE;
          eStatus = MDP_STATUS_HW_ERROR;
        }
        // Initialize the HW private info
        else if (MDP_STATUS_OK != (eStatus = MDPInitHwPrivateInfo(psMDPHwPrivateInfo)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: MDPInitHwPrivateInfo() failed!\n");

          // Fall back to SW render mode for error handling, skip updating internal SW render status to release display resources.
          bSWRender = TRUE;
        }
        else if (HAL_MDSS_STATUS_SUCCESS != HAL_MDP_TrafficCtrl_Init(NULL, 0))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: HAL_MDP_TrafficCtrl_Init() failed!\n");

          // Fall back to SW render mode for error handling, skip updating internal SW render status to release display resources.
          bSWRender = TRUE;
          eStatus = MDP_STATUS_HW_ERROR;
        }
        else
        {
          // Hardware detected
          // - Setup based on the hardware configuration

          ExtDisp_AttrType   sExtDispAttr;

          // Populate the input parameters
          pMDPInitParams->uMDPVersionMajor    = psMDPHwPrivateInfo->sMDPVersionInfo.uMajorVersion;
          pMDPInitParams->uMDPVersionMinor    = psMDPHwPrivateInfo->sMDPVersionInfo.uMinorVersion;
          pMDPInitParams->uMDPVersionRevision = psMDPHwPrivateInfo->sMDPVersionInfo.uReleaseVersion;

          //For continuous splash feature, since frame buffer memory is shared between UEFI
          //and kernel, the MMU context need to be updated to enable sharing.
          //Ensure MMU is initialized only once when the DisplayDxe is loaded
          //to avoid multiple stream faults with dynamic SID programming.

          if (MDP_INIT_FLAG_MMU_INIT & uFlags)
          {
            if (MDP_STATUS_OK != FindPlatformMMUSidMask(sPlatformParams.sPlatformInfo.sEFIChipSetFamily, &uMMUSidMask))
            {
              MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: Failed to find MMU SID mask for this platform!\n");
            }
            else if (MDP_STATUS_OK != MDP_SetupMMUSIDs(sPlatformParams.sPlatformInfo.sEFIChipSetFamily, uMMUSidMask))
            {
              MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: Failed to setup MMU SIDs!\n");
            }
          }

          // Check the external display configuration.
          if (ExtDisp_SupportedByPlatform(&sExtDispAttr))
          {
            gDisplayInfo[MDP_DISPLAY_EXTERNAL].ePhysConnect          = sExtDispAttr.ePhysConnect;

            // Update supported displays for external display based on fuse register
            // Passing NULL as the 3rd parameter since in this call this parameter is not being accessed
            if ((TRUE == pMDPInitParams->aSupportedDisplays[eDisplayId]) && 
                (MDP_STATUS_OK != MDPGetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_INTERFACE_AVAILABLE, NULL)))
            {
              pMDPInitParams->aSupportedDisplays[MDP_DISPLAY_EXTERNAL] = FALSE;
            }
          }

          // If DISABLEDISPLAY variable is set, then disable primary display
          // Note: Make sure to check if external display is supported before proceeding
          if(TRUE == pMDPInitParams->aSupportedDisplays[MDP_DISPLAY_EXTERNAL])
          {
            if(TRUE == MDPPlatformGetDisableDisplay())
            {
              // DISABLEDISPLAY variable is set. Disable primary display
              pMDPInitParams->aSupportedDisplays[MDP_DISPLAY_PRIMARY]  = FALSE;
            }
          }
        }
      }
    }

    // Platform is configured for SW renderer, or hardware detection failed
    if (TRUE == bSWRender)
    {
      // Populate the input parameters
      pMDPInitParams->uMDPVersionMajor                         = 0;
      pMDPInitParams->uMDPVersionMinor                         = 0;
      pMDPInitParams->uMDPVersionRevision                      = 0;
      pMDPInitParams->aSupportedDisplays[MDP_DISPLAY_EXTERNAL] = FALSE;

      // Tell platform layer we are in SW render mode to by pass any hardware configuration
      MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));
      sPlatformParams.sPlatformInfo.bSWRenderOverrride = TRUE;

      for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_SECONDARY; eDisplayId++)
      {
        if (FALSE == pMDPInitParams->aSupportedDisplays[eDisplayId])
        {
          continue;
        }
        else if (MDP_STATUS_OK != (eStatus = MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_SW_RENDERER, &sPlatformParams)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: MDPPlatformConfigure(MDPPLATFORM_CONFIG_SW_RENDERER) failed!\n");
        }
      }
    }
  }
  
  MDP_LOG_FUNC_EXIT("MDPInit", 0x0);

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: MDPPower()
*/
/*!
* \brief
*   This function will power up and initialize the interface needed for a particular display.
*
* \param [in] eDisplayId       - The display to initialize
*        [in] pMDPPowerParams  - Power configuration
*        [in] uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPPower(MDP_Display_IDType eDisplayId, MDP_PowerParamsType *pMDPPowerParams, uint32 uFlags)
{
    MDP_Status eStatus = MDP_STATUS_OK;

    MDP_LOG_FUNC_ENTRY("MDPPower", eDisplayId);    

    if (NULL == pMDPPowerParams)
    {
      eStatus = MDP_STATUS_BAD_PARAM;
    }
    else if (TRUE == Display_Utils_CheckPanelSkip())
    {
      //Panel override was set, either skip is forced by override
      //or this panel is not supported in bootloader
      // Fall back to SW render mode
    }
    else if (TRUE == pMDPPowerParams->bPowerOn)
    {
        MDPPlatformParams sPlatformParams;

        MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));

        sPlatformParams.sPowerConfig.uFlags = uFlags;

        // Power up the respective displays
        if (MDP_STATUS_OK != (eStatus = MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_POWERUP, &sPlatformParams)))
        {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDPPlatformConfigure(MDPPLATFORM_CONFIG_POWERUP) failed!\n");
        }
    }
    else if (FALSE == pMDPPowerParams->bPowerOn)
    {
        MDPPlatformParams sPlatformParams;

        MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));

        sPlatformParams.sPowerConfig.uFlags = uFlags;

        // Power down the respective displays
        if (MDP_STATUS_OK != (eStatus = MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_POWERDOWN, &sPlatformParams)))
        {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDPPlatformConfigure(MDPPLATFORM_CONFIG_POWERDOWN) failed!\n");
        }

        /* Update core clock and bandwidth */
        if (MDP_STATUS_OK != MDPUpdateCoreClockAndBandwidth(eDisplayId, 0, 0, 0, FALSE))
        {
          MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDPUpdateCoreClockAndBandwidth failed!\n");
        }
    }

    MDP_LOG_FUNC_EXIT("MDPPower", eDisplayId);    

    return eStatus;
}


/****************************************************************************
*
** FUNCTION: MDPDetect()
*/
/*!
* \brief
*   This function will detect the presence of a display and supported modes.
*
* \param [in] eDisplayId       - The display to initialize
*        [in] MDPDetectParams  - Information regarding the hardware core
*        [in] uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPDetect(MDP_Display_IDType eDisplayId, MDP_DetectParamType *pMDPDetectParams, uint32 uFlags )
{
    MDP_Status           eStatus        = MDP_STATUS_OK;

    MDP_LOG_FUNC_ENTRY("MDPDetect", eDisplayId);

    if ((NULL == pMDPDetectParams) ||
        (eDisplayId >= MDP_DISPLAY_MAX))
    {
      eStatus = MDP_STATUS_BAD_PARAM;
    }
    else
    {
        MDP_Panel_AttrType  *pDisplayInfo = MDP_GET_DISPLAYINFO(eDisplayId);

        // Handle each display
        switch (eDisplayId)
        {
        case MDP_DISPLAY_PRIMARY:
        case MDP_DISPLAY_SECONDARY:
            {
              if (MDP_STATUS_OK == MDPDetectPanel(eDisplayId, pDisplayInfo))
              {
                 pMDPDetectParams->bDisplayDetected          = pDisplayInfo->bDetected;
                 pMDPDetectParams->uSupportedModes           = 1; // Only 1 mode is supported
                 pMDPDetectParams->aModeList[0].bInterlaced  = FALSE;
                 pMDPDetectParams->aModeList[0].uModeIndex   = 0;
                 pMDPDetectParams->aModeList[0].uWidth       = pDisplayInfo->uDisplayWidth;
                 pMDPDetectParams->aModeList[0].uHeight      = pDisplayInfo->uDisplayHeight;

                 switch (pDisplayInfo->ePhysConnect)
                 {
                 case MDP_DISPLAY_CONNECT_PRIMARY_DSI_VIDEO:
                 case MDP_DISPLAY_CONNECT_PRIMARY_DSI_CMD:
                 case MDP_DISPLAY_CONNECT_SECONDARY_DSI_VIDEO:
                 case MDP_DISPLAY_CONNECT_SECONDARY_DSI_CMD:
                    pMDPDetectParams->aModeList[0].uRefreshRate = pDisplayInfo->uAttrs.sDsi.uRefreshRate;
                    eStatus = MDPConfigureLinkCompression(pDisplayInfo);
                    break;
                  case  MDP_DISPLAY_CONNECT_EDP:
                    if (MDP_STATUS_OK == (eStatus = DPDriver_Open(eDisplayId, uFlags)))
                    {
                        /*
                         * both width and height are 0 means use timing from edid
                         * here will assign both xx->aModeList[0].uWidth and xx->aModeList[0].uHeight
                         * with correct value from edid so that both pMode->HorizontalResolution and
                         * pMode->VerticalResolution can inherit correct value to set up frame buffer
                         * correctly at DisplayDxe_SetMode later
                         */
                        if ((0 == pDisplayInfo->uDisplayWidth) &&
                            (0 == pDisplayInfo->uDisplayHeight))
                        {
                           MDP_Panel_AttrType    sMode;

                           MDP_OSAL_MEMZERO(&sMode, sizeof(MDP_Panel_AttrType));
                           eStatus = DPDriver_GetModeInfo(&sMode);
                           if (MDP_STATUS_OK == eStatus)
                           {
                              pMDPDetectParams->aModeList[0].uWidth  = sMode.uDisplayWidth;
                              pMDPDetectParams->aModeList[0].uHeight = sMode.uDisplayHeight;
                           }
                        }
                    }
                    break;
                 default:
                    break;
                 }
              }

              if (MDP_STATUS_OK != eStatus)
              {
                MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: Panel detection failed. Selecting SWRender mode!\n");

                if (MDP_DISPLAY_CONNECT_EDP == pDisplayInfo->ePhysConnect)
                {
                  // Landscape mode
                  pMDPDetectParams->aModeList[0].uWidth  = MDP_DEFAULT_RESOLUTION_WIDTH;
                  pMDPDetectParams->aModeList[0].uHeight = MDP_DEFAULT_RESOLUTION_HEIGHT;
                }
                else
                {
                  // Portrait mode - swap width & height
                  pMDPDetectParams->aModeList[0].uWidth  = MDP_DEFAULT_RESOLUTION_HEIGHT;
                  pMDPDetectParams->aModeList[0].uHeight = MDP_DEFAULT_RESOLUTION_WIDTH;
                }

                pDisplayInfo->bSWRenderer              = TRUE;
                eStatus                                = MDP_STATUS_OK;
              }
            }
            break;

        case MDP_DISPLAY_EXTERNAL:
            {
              if (!MDPDetectExtPlugin(eDisplayId, pDisplayInfo, uFlags))
              {
                MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: External monitor not detected!\n");
              }
              else
              {
                MDP_Panel_AttrType    sMode;
                uint32                i;

                // DP detected
                pDisplayInfo->bDetected            = TRUE;
                pDisplayInfo->uNumInterfaces       = MDP_INTERFACE_SINGLE;

                pMDPDetectParams->bDisplayDetected = TRUE;

                // Enumerate all modes
                for (i = 0; i < MDP_DISPLAY_MAX_MODES; i++)
                {
                  MDP_OSAL_MEMZERO(&sMode, sizeof(MDP_Panel_AttrType));
                  sMode.eDisplayId  = eDisplayId;
                  sMode.uModeId     = i;
                  if (MDP_STATUS_OK == ExtDisp_GetModeInfo(&sMode))
                  {
                    pMDPDetectParams->aModeList[i].uModeIndex   = i;
                    pMDPDetectParams->aModeList[i].uWidth       = sMode.uDisplayWidth;
                    pMDPDetectParams->aModeList[i].uHeight      = sMode.uDisplayHeight;
                    pMDPDetectParams->aModeList[i].uRefreshRate = sMode.uRefreshRate;
                    pMDPDetectParams->aModeList[i].bInterlaced  = FALSE;
                    pMDPDetectParams->uSupportedModes++;
                    MDP_Log_Message(MDP_LOGLEVEL_INFO, "MDPDetect: index=%d w=%d h=%d frate=%x\n",i, sMode.uDisplayWidth, sMode.uDisplayHeight, sMode.uRefreshRate);
                  }
                  else
                  {
                    break;
                  }
                }
              }
            }
            break;
        default:
            eStatus = MDP_STATUS_BAD_PARAM;
            break;
        }
    }
    
    MDP_LOG_FUNC_EXIT("MDPDetect", eDisplayId);    

    return eStatus;
}



/****************************************************************************
*
** FUNCTION: MDPSetMode()
*/
/*!
* \brief
*   This function setup the display for a particular mode.
*
* \param [in] eDisplayId       - The display to initialize
*        [in] MDPSetModeParams - Mode setup parameters
*        [in] uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPSetMode(MDP_Display_IDType eDisplayId, MDP_SetModeParamType *pMDPSetModeParams, uint32 uFlags )
{
  MDP_Status           eStatus      = MDP_STATUS_OK;
  MDP_Panel_AttrType  *pDisplayInfo = MDP_GET_DISPLAYINFO(eDisplayId);

  MDP_LOG_FUNC_ENTRY("MDPSetMode", eDisplayId); 

  if ((NULL == pMDPSetModeParams)     ||
      (eDisplayId >= MDP_DISPLAY_MAX))
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (TRUE == Display_Utils_CheckPanelSkip())
  {
    /* Panel override was set, either skip is forced by override,
     * or this panel is not supported in bootloader.
     * Fall back to SW render mode, but cache the buffer information to pass to the kernel.
     */
    MDP_OSAL_MEMCPY(&pDisplayInfo->sFrameBuffer, &pMDPSetModeParams->sSurfaceInfo, sizeof(MDPSurfaceInfo));

    eStatus = MDP_STATUS_OK;
  }
  else if (TRUE != pDisplayInfo->bDetected)
  {
    eStatus = MDP_STATUS_NOT_SUPPORTED;
  }
  else if (TRUE == pDisplayInfo->bSWRenderer)
  {
    // Cache the current mode and surface information
    pDisplayInfo->uModeId  = pMDPSetModeParams->uModeIndex;
    MDP_OSAL_MEMCPY(&pDisplayInfo->sFrameBuffer, &pMDPSetModeParams->sSurfaceInfo, sizeof(MDPSurfaceInfo));

    // Display is in software rendering mode, don't initialize hardware and continue
    eStatus = MDP_STATUS_OK;
  }
  else
  {
    // Setup GPIOs (Low and high list)
    if (MDP_STATUS_OK != (eStatus = MDPSetGPIOState(pDisplayInfo)))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: MDPSetGPIOState Failed!\n");
    }
	
	// Cache the source information
	MDP_OSAL_MEMCPY(&pDisplayInfo->sFrameBuffer, &pMDPSetModeParams->sSurfaceInfo, sizeof(MDPSurfaceInfo));

    // Setup MDP control paths
    if (MDP_STATUS_OK != (eStatus = MDPSetupPipe(pDisplayInfo, &pMDPSetModeParams->sSurfaceInfo)))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: MDPSetupPipe Failed!\n");
    }
    else if (MDP_STATUS_OK != (eStatus = MDPPanelInit(eDisplayId, pMDPSetModeParams->uModeIndex, pDisplayInfo)))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: MDPPanelInit Failed!\n");
    }
    else
    {
      // Dynamically update core clock and bandwidth to meet requirement of fps > 60Hz
      if (MDP_STATUS_OK != MDPUpdateCoreClockAndBandwidth(eDisplayId, pMDPSetModeParams->sSurfaceInfo.ePixelFormat, pMDPSetModeParams->sSurfaceInfo.uWidth, pMDPSetModeParams->sSurfaceInfo.uHeight, TRUE))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: MDPUpdateCoreClockAndBandwidth Failed!\n");
      }

      if (MDP_STATUS_OK != (eStatus = MDPStartPipe(pDisplayInfo))) // Kick start the displays
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: MDPStartPipe Failed!\n");
      }
      else
      {
        // Cache the current mode
        pDisplayInfo->uModeId  = pMDPSetModeParams->uModeIndex;
        pDisplayInfo->bModeSet = TRUE;

        // If DSI video transfer should be on during DCS transactions then send command for sending the init sequence.
        if (TRUE == pDisplayInfo->uAttrs.sDsi.bForceCmdInVideoHS)
        {
          if (MDP_STATUS_OK != MDPPanelSendCommandSequence(pDisplayInfo, MDP_PANEL_COMMAND_INIT, NULL, 0))
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: MDPPanelSendCommandSequence() failed to send INIT sequence!\n");
            pDisplayInfo->uInitFailures++;
          }
          /* If DSC is enabled then send the PPS command to the panel */
          if (TRUE == pDisplayInfo->sDSCConfig.bDSCEnable)
          {
            if (MDP_STATUS_OK != MDPPanelSendCommandSequence(pDisplayInfo, MDP_PANEL_COMMAND_PPS, NULL, 0))
            {
              MDP_Log_Message (MDP_LOGLEVEL_WARN, "DisplayDxe: MDPPanelSendCommandSequence() failed to send INIT sequence!\n");
              pDisplayInfo->uInitFailures++;
            }
          }
        }
      }
    
      //Check if panel FPS is beyond the SW Fuse, and give warning log.
      MDPCheckFpsFuse(pDisplayInfo);
    }
  }
  
  MDP_LOG_FUNC_EXIT("MDPSetMode", eDisplayId); 

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: MDPSetProperty()
*/
/*!
* \brief
*   This function will configure a specific property of the display
*
* \param [in] eDisplayId       - The display to initialize
*        [in] eProperty        - The particular property to set
*        [in] MDPSetModeParams - Mode setup parameters
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPSetProperty(MDP_Display_IDType eDisplayId, MDP_Display_Property eProperty, MDP_PropertiesParamType *pMDPPropertiesParams)
{
  MDP_Status           eStatus      = MDP_STATUS_OK;

  MDP_LOG_FUNC_ENTRY2("MDPSetProperty", eDisplayId, eProperty);
    
  if (eDisplayId >= MDP_DISPLAY_MAX)
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    MDP_Panel_AttrType  *pDisplayInfo = MDP_GET_DISPLAYINFO(eDisplayId);

    switch (eProperty)
    {
    case MDP_DISPLAY_PROPERTY_BACKLIGHT:
      {
        MDPPlatformParams  sPlatformParams;
        uint32             uDefaultBacklightLevel = pMDPPropertiesParams->uBacklightLevel;

        // Here, if default backlight level (non zero unsigned integer) is defined by panelcfg XML tags (<BacklightDefault>..</BacklightDefault>),
        // then it will override default pcd backlight level
        // Check if input backlight level is out of range
        if(uDefaultBacklightLevel > MDP_DISPLAY_MAX_BRIGHTNESS)
        {
          // Validate backlight level defined by panelcfg XML
          if((pDisplayInfo->sBacklightConfig.uLevel > 0)&&
             (pDisplayInfo->sBacklightConfig.uLevel <= MDP_DISPLAY_MAX_BRIGHTNESS))
          {
            // Override the PCD defualt backlight level
            uDefaultBacklightLevel = pDisplayInfo->sBacklightConfig.uLevel;
          }
          else
          {
            // Either We haven't defined backlight in panelcfg, or defined backlight value is invalid
            uDefaultBacklightLevel = PcdGet32(PcdBacklightLevel);
          }
        }

        // Setup any other display parameters
        MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));

        // Configure backlight parameters.
        sPlatformParams.sBacklightConfig.bEnable                        = TRUE;
        sPlatformParams.sBacklightConfig.eBacklightType                 = pDisplayInfo->sBacklightConfig.eBacklightType;
        sPlatformParams.sBacklightConfig.uBacklightCntrl.eBacklightCtrl = pDisplayInfo->sBacklightConfig.uBacklightCntrl.eBacklightCtrl;
        sPlatformParams.sBacklightConfig.uLevel                         = uDefaultBacklightLevel;
        sPlatformParams.sBacklightConfig.uNumBits                       = pDisplayInfo->sBacklightConfig.uNumBits;

        // Backlight control type specific functionality
        switch (pDisplayInfo->sBacklightConfig.eBacklightType)
        {
          case MDP_PANEL_BACKLIGHTTYPE_I2C:
            {
              // Setup backlight I2C configuration
              MDP_OSAL_MEMCPY(&sPlatformParams.sBacklightConfig.uBacklightCntrl.sI2CConfig, &pDisplayInfo->uAttrs.sDsi.sI2CConfig, sizeof(MDP_I2C_Configuration));
            }
            break;

          default:
            break;
        }

        if (MDP_STATUS_OK == (eStatus = MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_SETBACKLIGHT, &sPlatformParams)))
        {
          // Cache current backlight level
          pDisplayInfo->uBacklightLevel = uDefaultBacklightLevel;
        }
      }
      break;

    case MDP_DISPLAY_PROPERTY_FIRMWAREENV:
      {
        UINT32 uFrameBufferAddr;
        UINT32 uFrameBufferSize;

        if(MDP_STATUS_OK != (eStatus = MDP_SaveFirmwareEnvironmentVariable(eDisplayId)))
        {
          MDP_Log_Message (MDP_LOGLEVEL_WARN, "MDPSystem: MDP_SaveFirmwareEnvironmentVariable failed.\n");
        }

        /* Functions below can fail but we can continue */
        if (EFI_SUCCESS != Display_Utils_GetContinuousSplashInfo(&uFrameBufferAddr, &uFrameBufferSize))
        {
          MDP_Log_Message (MDP_LOGLEVEL_WARN, "MDPSystem: Display_Utils_GetContinuousSplashInfo failed.\n");
        }
        else if (MDP_STATUS_OK != MDP_SetDisplayBootConfig(uFrameBufferAddr, uFrameBufferSize))
        {
          MDP_Log_Message (MDP_LOGLEVEL_WARN, "MDPSystem: MDP_SetDisplayBootConfig failed.\n");
        }

        Display_Utils_StorePLLCodes();
        Display_Utils_LogSettings();
      }
      break;

    case MDP_DISPLAY_PROPERTY_MODE_INFO:
      {
         MDP_HwPrivateInfo *psMDPHwPrivateInfo = MDP_GETPRIVATEINFO();
         uint32             ModeIndex          =  pMDPPropertiesParams->sModeParams.uModeIndex;

         switch (eDisplayId)
         {
           case MDP_DISPLAY_PRIMARY:
           case MDP_DISPLAY_SECONDARY:
             /*
              * if edp is the primary dispay
              * populated the mode # 0 timing into PanelInfo
              */
              if (pDisplayInfo->ePhysConnect ==  MDP_DISPLAY_CONNECT_EDP)
              {
                 /* both width and height are 0 means panle timing is derived from edid */
                 if (pDisplayInfo->uDisplayWidth == 0 &&
                     pDisplayInfo->uDisplayHeight == 0)
                 {
                    /* invalid xml file, use panel timing from EDID */
                    pDisplayInfo->eDisplayFlags |= MDP_PANEL_FLAG_TIMING_FROM_EDID;

                    eStatus = DPDriver_GetModeInfo(pDisplayInfo);      /* populated PanelInfo from edid */
                 }
              }
              break;
            case MDP_DISPLAY_EXTERNAL:
              /*
               * External monitor supports more than one mode,
               * populated the selected mode timing info PanelInfo
               */
               pDisplayInfo->uModeId = ModeIndex;
               eStatus = ExtDisp_GetModeInfo(pDisplayInfo); /* populate panelInfo from edid */
            break;
            default:
            break;
         }

         // Check if we need Dual pipe for this panel
         if ((NULL != psMDPHwPrivateInfo->pDeviceCaps) &&
             (pDisplayInfo->uDisplayWidth > psMDPHwPrivateInfo->pDeviceCaps->pResolutionCaps->uMaxLayerWidthPx))
         {
             pDisplayInfo->uNumMixers = MDP_DUALPIPE_NUM_MIXERS;
         }
      }
      break;

    case MDP_DISPLAY_PROPERTY_POWER_STATE:
      {
        /* Cache the current display power state information */
        pDisplayInfo->bDisplayPwrState  =  pMDPPropertiesParams->bDisplayPwrState;
        break;
      }
    case MDP_DISPLAY_PROPERTY_ABL_INTERFACE_INIT:
      {
        /* Initialize Display context which will be used to create panel configuration string for ABL later */
        Display_Utils_Initialize(pMDPPropertiesParams->pSupportedDisplayList);

        break;
      }
    case MDP_DISPLAY_PROPERTY_SURFACE_RECT:
      {
         if (TRUE == pDisplayInfo->bModeSet)
         {
           MDPSurfaceInfo *pSurfaceInfo = NULL;

           /* Only pass a surface if it is valid, otherwise NULL means the surface address programming is unchanged */
           if ((MDP_PIXEL_FORMAT_NONE != pMDPPropertiesParams->sModeParams.sSurfaceInfo.ePixelFormat) &&
               (pMDPPropertiesParams->sModeParams.sSurfaceInfo.uWidth > 0)                            &&
               (pMDPPropertiesParams->sModeParams.sSurfaceInfo.uHeight > 0))
            {
               pSurfaceInfo =  &pMDPPropertiesParams->sModeParams.sSurfaceInfo;
            }

           /* Configure a new source surface and/or cropping rectangle */
           if (EFI_SUCCESS != (eStatus = MDPSetupSourcePipe(pDisplayInfo, pSurfaceInfo, &pMDPPropertiesParams->sModeParams.sRectInfo)))
           {
               MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: Error configuring a new surface/rect %r\n", eStatus);
           }
         }
         else
         {
           MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: Unable to change surface/rect.  Mode has not been set.\n");
         }
      }
      break;
    default:
      eStatus = MDP_STATUS_BAD_PARAM;
      break;
    }
  }

  MDP_LOG_FUNC_EXIT2("MDPSetProperty", eDisplayId, eProperty);

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: MDPGetProperty()
*/
/*!
* \brief
*   This function will retrieve a specific property of the display
*
* \param  [in] eDisplayId           - The display to initialize
*         [in] eProperty            - The particular property to set
*         [in] pMDPPropertiesParams - Property parameters
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPGetProperty(MDP_Display_IDType eDisplayId, MDP_Display_Property eProperty, MDP_PropertiesParamType *pMDPPropertiesParams)
{
  MDP_Status           eStatus      = MDP_STATUS_OK;

  MDP_LOG_FUNC_ENTRY_INFO("MDPGetProperty", eDisplayId);

  if (eDisplayId >= MDP_DISPLAY_MAX)
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    MDP_Panel_AttrType  *pDisplayInfo = MDP_GET_DISPLAYINFO(eDisplayId);

    switch (eProperty)
    {
      case MDP_DISPLAY_PROPERTY_BACKLIGHT:
      {
        /* Retrieve the current cached backlight level */
        pMDPPropertiesParams->uBacklightLevel  =  pDisplayInfo->uBacklightLevel;
        break;
      }

      case MDP_DISPLAY_PROPERTY_POWER_STATE:
      {
        /* Retrieve the current cached display state information */
        pMDPPropertiesParams->bDisplayPwrState  =  pDisplayInfo->bDisplayPwrState;
        break;
      }

      case MDP_DISPLAY_PROPERTY_MODE_INFO:
      {
        /* Retrieve the current cached display mode information */
        pMDPPropertiesParams->sModeParams.uModeIndex = pDisplayInfo->uModeId;
        MDP_OSAL_MEMCPY(&pMDPPropertiesParams->sModeParams.sSurfaceInfo, &pDisplayInfo->sFrameBuffer, sizeof(MDPSurfaceInfo));
        break;
      }
	  
	  case MDP_DISPLAY_PROPERTY_FRAMEBUFFER_INFO:
	  {
		MDPSurfaceInfo sSurfaceInfo;
		
		MDP_OSAL_MEMZERO(&sSurfaceInfo, sizeof(MDPSurfaceInfo));
		
		/* Retrieve pixel format and its properties based on FSD Support */
        sSurfaceInfo.ePixelFormat   = (MDP_PANEL_FLAG_FSD_FORMAT_CONFIG & pDisplayInfo->eDisplayFlags) ? MDP_PIXEL_FORMAT_RGB_PLANAR_888_8BPP : MDP_PIXEL_FORMAT_ARGB_8888_32BPP;
		sSurfaceInfo.uBytesPerPixel = gMDP_PixelFormatMap[sSurfaceInfo.ePixelFormat].uBitsPerPixel / 8;
		sSurfaceInfo.uNumPlanes     = gMDP_PixelFormatMap[sSurfaceInfo.ePixelFormat].uNumPlanes;
		MDP_OSAL_MEMCPY(&pMDPPropertiesParams->sModeParams.sSurfaceInfo, &sSurfaceInfo, sizeof(MDPSurfaceInfo));
		break;
      }
	  
      case MDP_DISPLAY_PROPERTY_DETECTION_INFO:
      {
        /* Retrieve the current cached display detection information */
        pMDPPropertiesParams->bDisplayDetected = pDisplayInfo->bDetected;
        break;
      }

      case MDP_DISPLAY_PROPERTY_DISPLAY_CONFIG:
      {
        /* Update display configuration info */
        eStatus = MDPDetectPanel(eDisplayId, pDisplayInfo);
        break;
      }

      case MDP_DISPLAY_PROPERTY_INTERFACE_AVAILABLE:
      {
        /* Check the availability of a display */
        MDP_HwPrivateInfo *psMDPHwPrivateInfo  = MDP_GETPRIVATEINFO();

        switch (pDisplayInfo->ePhysConnect)
        {
          case MDP_DISPLAY_CONNECT_PRIMARY_DSI_VIDEO:
          case MDP_DISPLAY_CONNECT_PRIMARY_DSI_CMD:
          case MDP_DISPLAY_CONNECT_SECONDARY_DSI_VIDEO:
          case MDP_DISPLAY_CONNECT_SECONDARY_DSI_CMD:
          {
            if (FALSE == MDP_CheckInterfaceAvailable(psMDPHwPrivateInfo->sEFIChipSetFamily, (MDP_DISPLAY_PERIPHERAL_DSI0 | MDP_DISPLAY_PERIPHERAL_DSI1)))
            {
              eStatus = MDP_STATUS_NOT_SUPPORTED;
            }
            break;
          }
          case MDP_DISPLAY_CONNECT_DP:
          {
            if (FALSE == MDP_CheckInterfaceAvailable(psMDPHwPrivateInfo->sEFIChipSetFamily, MDP_DISPLAY_PERIPHERAL_EDP1))
            {
              eStatus = MDP_STATUS_NOT_SUPPORTED;
            }
            break;
          }
          case MDP_DISPLAY_CONNECT_DP_1:
          {
            if (FALSE == MDP_CheckInterfaceAvailable(psMDPHwPrivateInfo->sEFIChipSetFamily, MDP_DISPLAY_PERIPHERAL_DP1))
            {
              eStatus = MDP_STATUS_NOT_SUPPORTED;
            }
            break;
          }
          case MDP_DISPLAY_CONNECT_EDP:
          {
            if (FALSE == MDP_CheckInterfaceAvailable(psMDPHwPrivateInfo->sEFIChipSetFamily, MDP_DISPLAY_PERIPHERAL_EDP0))
            {
              eStatus = MDP_STATUS_NOT_SUPPORTED;
            }
            break;
          }
          default:
          {
            break;
          }
        }
        break;
      }
      case MDP_DISPLAY_PROPERTY_GET_PANEL_EDID:
      {
        MDP_Panel_EDID_Config *pEDID = (MDP_Panel_EDID_Config *)pMDPPropertiesParams->sEDID.pEdid;

        if (NULL == pEDID)
        {
          eStatus = MDP_STATUS_BAD_PARAM;
        }
        else
        {
          // Initialize EDID table structure
          EDIDInitialize(pEDID);
          // Generate Detailed timings from XML data
          EDIDGenerateDetailedTiming(pEDID, pDisplayInfo);
          //Generate Monitor name descriptor
          EDIDGenerateMonitorNameDescriptor(&pEDID->EDID_DetailedInfo.DisplayDescriptors[1], pDisplayInfo->szName);
          // Generate EDID Checksum
          EDIDGenerateChecksum(pEDID);
          pMDPPropertiesParams->sEDID.uSize = sizeof(MDP_Panel_EDID_Config);
        }
        break;
      }
      default:
      {
        eStatus = MDP_STATUS_BAD_PARAM;
        break;
      }
    }
  }

  MDP_LOG_FUNC_EXIT_INFO("MDPGetProperty", eDisplayId);

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: MDPDeInit()
*/
/*!
* \brief
*   This function will de-initializes the panel interfaces
*
* \param [in]  eDisplayId       - Display to de-initialize
* \param [in]  uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPDeInit(MDP_Display_IDType eDisplayId, uint32 uFlags)
{
  MDP_Status           eStatus      = MDP_STATUS_OK;

  MDP_LOG_FUNC_ENTRY("MDPDeInit", eDisplayId);

  if (eDisplayId >= MDP_DISPLAY_MAX)
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    MDP_Panel_AttrType  *pDisplayInfo = MDP_GET_DISPLAYINFO(eDisplayId);

    // If the display id matches, then only de-initialize
    if (pDisplayInfo->eDisplayId == eDisplayId)
    {

      if(TRUE == pDisplayInfo->bSWRenderer)
      {
        /* do nothing if display is in SW rendering mode, skip HW configuration */
      }
      else
      {
        /* Handle interface specific differences */
        switch (pDisplayInfo->ePhysConnect)
        {
          case MDP_DISPLAY_CONNECT_PRIMARY_DSI_VIDEO:
          case MDP_DISPLAY_CONNECT_PRIMARY_DSI_CMD:      
          case MDP_DISPLAY_CONNECT_SECONDARY_DSI_VIDEO:
          case MDP_DISPLAY_CONNECT_SECONDARY_DSI_CMD:
            
            /* If DSI video transfer should be on during DCS transactions then send command for sending the termination sequence. */
            if (TRUE == pDisplayInfo->uAttrs.sDsi.bForceCmdInVideoHS)
            {
              if (MDP_STATUS_OK != MDPPanelSendCommandSequence(pDisplayInfo, MDP_PANEL_COMMAND_TERM, NULL, 0))
              {
                MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: MDPPanelSendCommandSequence() failed to send TERM sequence!\n");
              }
            }
            break;
            
           default:
            break;
        }

        /* Turn off the display timing engines */
        if (MDP_STATUS_OK != (eStatus = MDPStopPipe(pDisplayInfo)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDPPanelDeInit() failed! Status: %d\n", eStatus);      
        }
      
      
        /* Turn off the display controller and panel */
        if (MDP_STATUS_OK != (eStatus = MDPPanelDeInit(pDisplayInfo)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDPPanelDeInit() failed! Status: %d\n", eStatus);  
        }
      }
    }
  }

  MDP_LOG_FUNC_EXIT("MDPDeInit", eDisplayId);

  return eStatus;
}



/****************************************************************************
*
** FUNCTION: MDPTerm()
*/
/*!
* \brief
*   This function will deinitialize the MDP core and free all resources.
*
* \param [in]  uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPTerm(uint32 uFlags)
{
  MDP_Panel_AttrType  *pDisplayInfo = NULL;
  MDP_Status           eStatus      = MDP_STATUS_OK;

  MDP_LOG_FUNC_ENTRY("MDPTerm", 0x00);

  if (TRUE == MDPClockStatus(MDP_CLOCKTYPE_CORE))
  {
    /* Halt all vbif axi */
    if (HAL_MDSS_STATUS_SUCCESS != HAL_MDP_Term(0))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: Halt vbif axi failed!\n");
    }

    /* Turn off core clock */
    if (MDP_STATUS_OK != (eStatus = MDPDisableClocks(MDP_CLOCKTYPE_CORE)))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDP Disable Core Clock failed with Status(%d)!\n", eStatus);
    }

    if (NULL != (pDisplayInfo = MDP_GET_DISPLAYINFO(MDP_DISPLAY_PRIMARY)))
    {
      /* Turn off dsi0 clock */
      if (MDP_STATUS_OK != (eStatus = MDPDisableClocks(MDP_CLOCKTYPE_DSI0)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDP Disable Dsi0 Clock failed with Status(%d)!\n", eStatus);
      }

      /* Turn off dsi1 clock */
      if (MDP_STATUS_OK != (eStatus = MDPDisableClocks(MDP_CLOCKTYPE_DSI1)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDP Disable Dsi1 Clock failed with Status(%d)!\n", eStatus);
      }
    }

    if (NULL != (pDisplayInfo = MDP_GET_DISPLAYINFO(MDP_DISPLAY_EXTERNAL)))
    {
      /* Turn off hdmi clock */
      if (MDP_STATUS_OK != (eStatus = MDPDisableClocks(MDP_CLOCKTYPE_HDMI)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDP Disable HDMI Clock failed with Status(%d)!\n", eStatus);
      }

      /* Turn off dp clock */
      if (MDP_STATUS_OK != (eStatus = MDPDisableClocks(MDP_CLOCKTYPE_DP)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDP Disable DP Clock failed with Status(%d)!\n", eStatus);
      }
    }
  }

  MDP_LOG_FUNC_EXIT("MDPTerm", 0x0);

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: MDPExitBoot()
*/
/*!
* \brief
*   This function performs house cleaning before UEFI exit
*
* \param [in]  uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPExitBoot(uint32 uFlags)
{
  MDP_Panel_AttrType  *pDisplayInfo         = NULL;
  MDP_Status           eStatus              = MDP_STATUS_OK;
  bool32               bSeamlessSplash      = FALSE;
  MDP_Display_IDType   eDisplayId           = MDP_DISPLAY_PRIMARY;

  MDP_LOG_FUNC_ENTRY("MDPExitBoot", 0x0);

  /* If seamless splash is not required, turn off the display before leaving */
  MDP_PowerParamsType  sPowerParams;

  for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_EXTERNAL; eDisplayId++)
  {
    if (FALSE == MDP_SUPPORTED_DISPLAY(eDisplayId))
    {
      continue;
    }
    else
    {
      pDisplayInfo = MDP_GET_DISPLAYINFO(eDisplayId);

      if (0 == (MDP_PANEL_FLAG_DISABLE_SEAMLESS_SPLASH & pDisplayInfo->eDisplayFlags))
      {
        bSeamlessSplash = TRUE;
      }

      if ((MDP_PANEL_FLAG_DISABLE_SEAMLESS_SPLASH  & pDisplayInfo->eDisplayFlags) &&
          (TRUE                                   == pDisplayInfo->bDisplayPwrState))
      {
        MDP_OSAL_MEMZERO(&sPowerParams, sizeof(MDP_PowerParamsType));
        sPowerParams.bPowerOn = FALSE;

        // DeInit the panel interfaces before exiting
        if (MDP_STATUS_OK != (eStatus = MDPDeInit(eDisplayId, 0x0)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPExitBoot: Display deInit failed with status(%d)!\n", eStatus);
        }

        // Turn off MDP powers before exiting
        if (MDP_STATUS_OK != (eStatus = MDPPower(eDisplayId, &sPowerParams, 0x0)))
        {
           MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPExitBoot: Disable common display panel power failed with status(%d)!\n", eStatus);
        }

        // Turn off MDP powers before exiting
        if (MDP_STATUS_OK != (eStatus = MDPPower(eDisplayId, &sPowerParams, POWERCONFIG_FLAGS_PANEL_POWER)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPExitBoot: Disable specific display panel power failed with status(%d)!\n", eStatus);
        }
      }

      switch (MDP_CONNECTIONINTF_MAP(pDisplayInfo->ePhysConnect))
      {
      case MDP_INTERFACE_DSI:
      {
        if (NULL != pDisplayInfo->uAttrs.sDsi.pInitBuffer)
        {
          MDP_OSAL_FREE(pDisplayInfo->uAttrs.sDsi.pInitBuffer);
          pDisplayInfo->uAttrs.sDsi.pInitBuffer = NULL;
        }

        if (NULL != pDisplayInfo->uAttrs.sDsi.pTermBuffer)
        {
          MDP_OSAL_FREE(pDisplayInfo->uAttrs.sDsi.pTermBuffer);
          pDisplayInfo->uAttrs.sDsi.pTermBuffer = NULL;
        }

        if (NULL != pDisplayInfo->sDSCConfig.pDSCPpsBuffer)
        {
          MDP_OSAL_FREE(pDisplayInfo->sDSCConfig.pDSCPpsBuffer);
          pDisplayInfo->sDSCConfig.pDSCPpsBuffer = NULL;
        }

        if (NULL != pDisplayInfo->uAttrs.sDsi.sDemuraConfig.pSprXMLConfig)
        {
          MDP_OSAL_FREE(pDisplayInfo->uAttrs.sDsi.sDemuraConfig.pSprXMLConfig);
          pDisplayInfo->uAttrs.sDsi.sDemuraConfig.pSprXMLConfig = NULL;
        }

        if (NULL != pDisplayInfo->uAttrs.sDsi.sDemuraConfig.pDemuraHFCData)
        {
          MDP_OSAL_FREE(pDisplayInfo->uAttrs.sDsi.sDemuraConfig.pDemuraHFCData);
          pDisplayInfo->uAttrs.sDsi.sDemuraConfig.pDemuraHFCData = NULL;
          pDisplayInfo->uAttrs.sDsi.sDemuraConfig.uDemuraHFCSize = 0;
        }

       if (NULL != pDisplayInfo->uAttrs.sDsi.sDemuraConfig.psDemuraConfig)
        {
          MDP_OSAL_FREE(pDisplayInfo->uAttrs.sDsi.sDemuraConfig.psDemuraConfig);
          pDisplayInfo->uAttrs.sDsi.sDemuraConfig.psDemuraConfig = NULL;
        }
        break;
      }
      case MDP_INTERFACE_DP:
      {
        break;
      }
      default:
        break;
      }
    }
  }

  if (FALSE == bSeamlessSplash)
  {
    // Turn off MDP clocks before exiting
    if (MDP_STATUS_OK != (eStatus = MDPTerm(0x0)))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPExitBoot: Turn off MDP clocks failed with Status(%d)!\n", eStatus);
    }
  }
 

  if (NULL != gpDSIInitSequenceBuffer)
  {
    MDP_OSAL_FREE(gpDSIInitSequenceBuffer);
    gpDSIInitSequenceBuffer = NULL;
  }

  if (NULL != gpDSITermSequenceBuffer)
  {
    MDP_OSAL_FREE(gpDSITermSequenceBuffer);
    gpDSITermSequenceBuffer = NULL;
  }

  if (NULL != gpDSIDscPpsBuffer)
  {
    MDP_OSAL_FREE(gpDSIDscPpsBuffer);
    gpDSIDscPpsBuffer = NULL;
  }

  if (NULL != gpI2CInitSequenceBuffer)
  {
    MDP_OSAL_FREE(gpI2CInitSequenceBuffer);
    gpI2CInitSequenceBuffer = NULL;
  }

  if (NULL != gpI2CTermSequenceBuffer)
  {
    MDP_OSAL_FREE(gpI2CTermSequenceBuffer);
    gpI2CTermSequenceBuffer = NULL;
  }

  MDP_LOG_FUNC_EXIT("MDPExitBoot", 0x0);
  
  return MDP_STATUS_OK;
}

/****************************************************************************
*
** FUNCTION: MDPSetCoreClock()
*/
/*!
* \brief
*   This function will setup the MDP core clock, enable footswitch, and restore TZ of register access
*
* \param [in]  uFlags
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPSetCoreClock(uint32 uFlags)
{
  MDP_Status eStatus = MDP_STATUS_OK;

  MDP_LOG_FUNC_ENTRY("MDPSetCoreClock", 0x00);

  /* Turn on the core clock */
  if (MDP_STATUS_OK != (eStatus = MDPSetupClocks(MDP_CLOCKTYPE_CORE, NULL)))
  {
     MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDPSetupClocks() failed!\n");
  }

  MDP_LOG_FUNC_EXIT("MDPSetCoreClock", 0x0);

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: CalculateCoreClockAndBandwidth()
*/
/*!
* \brief
*   calculate core clock and bandwidth
*
* \param [in]  eDisplayId          -  the specific display device    
*        [in]  eSrcColorFormat     -  source color format
*        [in]  uSrcWidthPixels     -  source width in pixels 
*        [in]  uSrcHeightPixels    -  source height in pixels
*        [in]  uRefreshRate        -  refresh rate in Hz
*        [out] pCoreClock          -  pointer to store core clock value
*        [out] pBandwidth          -  pointer to store bandwidth value
* \retval MDP_Status
*
****************************************************************************/
static MDP_Status  CalculateCoreClockAndBandwidth(MDP_Display_IDType eDisplayId, MDP_PixelFormatType eSrcColorFormat, uint32 uSrcWidthPixels, uint32 uSrcHeightPixels, uint32 uRefreshRate, uint32 *pCoreClock, uint64 *pBandwidth)
{
  MDP_Status                eStatus                  = MDP_STATUS_OK;
  uint64                    uNewCoreClk              = 0;
  MDP_Panel_AttrType       *pDisplayInfo             = MDP_GET_DISPLAYINFO(eDisplayId);
  uint32                    uCoreClockFloor          = MDPGetMinCoreClock();

  if ((NULL == pDisplayInfo) ||
      (NULL == pCoreClock)   ||
      (NULL == pBandwidth))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "CalculateCoreClockAndBandwidth invalid parameter!\n");
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (0 == uRefreshRate)
  {
    /* In case of MDPPower(off) will enter this branch */
    pDisplayInfo->sDynamicResourceConfig.uCoreClock = 0;
    pDisplayInfo->sDynamicResourceConfig.uBandwidth = 0;
  }
  else
  {
    float  fSmartTransferTimeMargin = MDP_SMART_TRANSFER_TIME_MARGIN;
    float  fNewTransferTime         = (1.0 / uRefreshRate) - fSmartTransferTimeMargin;

    if (0 < fNewTransferTime)
    {
      uint32 uDstWidth                = pDisplayInfo->uDisplayWidth;
      uint32 uDstHeightActive         = pDisplayInfo->uDisplayHeight;
      uint32 uDstHeightTotal          = uDstHeightActive + 
                                        pDisplayInfo->sActiveTiming.uVsyncPulseWidthLines +
                                        pDisplayInfo->sActiveTiming.uVsyncBackPorchLines +
                                        pDisplayInfo->sActiveTiming.uVsyncFrontPorchLines;
      uint32 uBytePerPixel            = MDP_CEIL(MDP_GET_PIXELFMTMAP(eSrcColorFormat).uBitsPerPixel, 8);
      uint64 uBandwidth;
      uint32 uNewRefreshRate          = (uint32)(1.0 / fNewTransferTime);
      uint64 uBandwidthFloor;

      /* Handle dual pipe here */
      if (2 == pDisplayInfo->uNumMixers)
      {
        if ((MDP_SINGLEPIPE_NUM_MIXERS == pDisplayInfo->uNumInterfaces) &&
            (FALSE                     == pDisplayInfo->sDSCConfig.bDSCEnable))
        {
          // For 3D Merge enabled case, use total width instead of active
          uDstWidth += pDisplayInfo->sActiveTiming.uHsyncPulseWidthDclk +
                       pDisplayInfo->sActiveTiming.uHsyncBackPorchDclk  +
                       pDisplayInfo->sActiveTiming.uHsyncFrontPorchDclk;
        }

        uDstWidth /= 2;
      }

      /* The worst case of the core clock value */
      uNewCoreClk = uDstWidth * uDstHeightTotal * uNewRefreshRate;

      /* Limit the Core Clock to be always larger than the floor value */
      if (uNewCoreClk < uCoreClockFloor)
      {
        uNewCoreClk = uCoreClockFloor;
      }

      /* Calculate bandwidth value for this specific display */
      uBandwidth      = (uint64)((uint64)uSrcWidthPixels *  uSrcHeightPixels * uBytePerPixel * uNewRefreshRate);
      uBandwidthFloor = uNewCoreClk * uBytePerPixel * 1.05;
      if (uBandwidth < uBandwidthFloor)
      {
        uBandwidth = uBandwidthFloor;
      }

      /* Pass data back to caller */
      *pCoreClock = MIN(uNewCoreClk, MAX_UINT32);
      *pBandwidth = uBandwidth;
    }
    else
    {
      *pCoreClock = 0;
      *pBandwidth = 0;
       eStatus    = MDP_STATUS_NO_RESOURCES;
    }
  }

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: MDPUpdateCoreClockAndBandwidth()
*/
/*!
* \brief
*   Wrapper to update both bandwidth and core clock
*
* \param [in]  eDisplayId         -  the specific display device  
*        [in]  eSrcColorFormat    -  source color format
*        [in]  uSrcWidthPixels    -  source width in pixels
*        [in]  uSrcHeightPixels   -  source height in pixels
*        [in]  bPowerOn           -  flag to indicate whethre it is in power process
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPUpdateCoreClockAndBandwidth(MDP_Display_IDType eDisplayId, MDP_PixelFormatType eSrcColorFormat, uint32 uSrcWidthPixels, uint32 uSrcHeightPixels, bool32 bPowerOn)
{
  MDP_Status                eStatus         = MDP_STATUS_OK;
  MDP_Panel_AttrType       *pDisplayInfo    = MDP_GET_DISPLAYINFO(eDisplayId);
  uint32                    uAggregatedCoreClock;
  uint64                    uAggregatedBandwidth;

  MDP_LOG_FUNC_ENTRY("MDPUpdateCoreClockAndBandwidth", eDisplayId);

  if (NULL == pDisplayInfo)
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPUpdateCoreClockAndBandwidth: invalid parameter\n");
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    if (FALSE == bPowerOn)
    {
      pDisplayInfo->sDynamicResourceConfig.uCoreClock = 0;
      pDisplayInfo->sDynamicResourceConfig.uBandwidth = 0;
    }
    else
    {
      uint32 uRefreshRate;
      uint32 uTmpCoreClock;
      uint64 uTmpBandwidth;

      if (MDP_STATUS_OK != MDPGetRefreshRate(pDisplayInfo, &uRefreshRate))
      {
        uRefreshRate = 60;
      }

      if (MDP_STATUS_OK != (eStatus = CalculateCoreClockAndBandwidth(eDisplayId, eSrcColorFormat, uSrcWidthPixels, uSrcHeightPixels, uRefreshRate, &uTmpCoreClock, &uTmpBandwidth)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPUpdateCoreClockAndBandwidth: CalculateCoreClockAndBandwidth failed\n");
      }
      else
      {
        /* Save calculated value to this specific display device */
        pDisplayInfo->sDynamicResourceConfig.uCoreClock = uTmpCoreClock;
        pDisplayInfo->sDynamicResourceConfig.uBandwidth = uTmpBandwidth;
      }
    }

    /* Update clock and bandwidth in both power on/off cases */
    if (MDP_STATUS_OK == eStatus)
    {
      /* Loop all panels, get the maximal core clock and total bandwidth that can satify all panels/devices */
      if (MDP_STATUS_OK != (eStatus = MDPGetAggregatedCoreAndBandwidth(&uAggregatedCoreClock, &uAggregatedBandwidth)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPUpdateCoreClockAndBandwidth: MDPGetAggregatedCoreAndBandwidth failed\n");
      }
      else if (MDP_STATUS_OK != (eStatus = MDPUpdateDynamicClocks(MDP_DYNAMIC_CLOCKTYPE_CORE, uAggregatedCoreClock)))
      {
         MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPUpdateCoreClockAndBandwidth: MDPUpdateDynamicClocks failed!\n");
      }
      else if (MDP_STATUS_OK != (eStatus = MDPUpdateDynamicBandwidth(uAggregatedBandwidth)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPUpdateCoreClockAndBandwidth: MDPUpdateDynamicBandwidth failed!\n");
      }
    }
  }

  MDP_LOG_FUNC_EXIT("MDPUpdateCoreClockAndBandwidth", eDisplayId);

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: MDPProfiler()
*/
/*!
* \brief
*   This function performs the profiling of functions
*
* \param [in]  pFuncName        - Function name
* \param [in]  uParam1          - Display ID, Property or Mode info depending on the function
* \param [in]  bEntry           - Function entry or exit. True - entry; False - exit;
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPProfiler(uint8 *pFuncName, uint32 uParam1, bool32 bEntry)
{
  MDP_Status           eStatus            =  MDP_STATUS_OK; 
  
  // Disable logging in ramdump mode
  if (FALSE == MDP_IsRamDumpMode())
  {
     if (NULL == gProfileLog)
     {
      gProfileLog = (MDP_ProfileLog*)MDP_OSAL_CALLOC(sizeof(MDP_ProfileLog));
     }
  
    if ((NULL != gProfileLog) &&
        (gProfileLog->uEntryCount < MDP_PROFILER_LOG_ENTRIES))
    {
      MDP_ProfileLogEntry *pEntry = &gProfileLog->aProfileLog[gProfileLog->uEntryCount];

      AsciiStrnCpyS((CHAR8 *)pEntry->sFunctionName, sizeof(pEntry->sFunctionName), (const CHAR8*)pFuncName, sizeof(pEntry->sFunctionName));
      pEntry->uParams[0] = (bEntry)?MDP_PROFILER_FLAG_ENTRY:0;
      pEntry->uParams[1] = (uParam1 & 0xFF);
      pEntry->uParams[2] = ((uParam1>>8)  & 0xFF);
      pEntry->uParams[3] = ((uParam1>>16) & 0xFF);
      pEntry->uTimeStamp = MDP_GetTimerCountUS();

      gProfileLog->uEntryCount++;
    }
  }

#ifdef MDPLIB_REALTIMELOGS
  // For realtime profiling these logs can be enabled
  //
  MDP_Log_Message(MDP_LOGLEVEL_ERROR, "%-14d %-5a %-40a %-6d\n", MDP_GetTimerCountUS(),
                                                                 (bEntry)?"Entry":"Exit",
                                                                 pFuncName,
                                                                 uParam1);
#endif

  return eStatus;
}

/*=========================================================================
     Local Static Variables
==========================================================================*/

static bool32 MDPDetectExtPlugin(MDP_Display_IDType eDisplayId, MDP_Panel_AttrType  *pPanelInfo, uint32 Flags)
{
  bool32     bDetected   = FALSE;
  MDP_Status eStatus       = MDP_STATUS_OK;

  if (NULL == pPanelInfo)
  {
   MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPDetectExtPlugin: Null pointer passed\n");
  }
  else
  {
    eStatus =  ExtDisp_Init(eDisplayId, Flags);
    if(MDP_STATUS_OK == eStatus)
    {
      // Get Valid Mode information for mode at Index 0
      if (ExtDisp_IsDisplayPlugged(eDisplayId))
      {
        pPanelInfo->eDisplayId    = MDP_DISPLAY_EXTERNAL;
        pPanelInfo->ePhysConnect  = gDisplayInfo[MDP_DISPLAY_EXTERNAL].ePhysConnect;
        bDetected                 = TRUE;

        // Clear the GPIO list with 0xFF to signify an empty list.
        // External display has not implemented the parser to clear default fields
        MDP_OSAL_MEMSET(&pPanelInfo->uDefaultGPIOState, 0xFF, sizeof(pPanelInfo->uDefaultGPIOState));
      }
      else
      {
        ExtDisp_Close(eDisplayId);
      }
    }
  }

  return bDetected;
}


/****************************************************************************
*
** FUNCTION: MDPPlatformGetDisableDisplay()
*/
/*!
* \brief
*   Returns TRUE if DISABLEDISPLAY is set and FALSE otherwise
*
*
* \retval bool32
*
****************************************************************************/
static bool32 MDPPlatformGetDisableDisplay(void)
{
  UINT32       uValue        =  0;
  bool32       bDisableDisp  = FALSE;
  MDP_Status   eStatus       = MDP_STATUS_OK;

  eStatus =  MDP_Display_GetVariable_Integer (L"DISABLEDISPLAY", &uValue);

  if ((MDP_STATUS_OK ==  eStatus) &&
      (uValue         >  0))
  {
    bDisableDisp = TRUE;
  }

  return bDisableDisp;
}

/****************************************************************************
*
** FUNCTION: MDPPlatformSetMdssBase()
*/
/*!
* \brief
*   Set MDSS base address
*
*
* \retval MDP_Status
*
****************************************************************************/
static MDP_Status MDPPlatformSetMdssBase(EFIChipInfoFamilyType  sEFIChipSetFamily)
{
  MDP_Status                          Status  = MDP_STATUS_OK;
  HAL_MDP_SWMappedHWBaseAddressesType sMDSSAddress;

  MDP_OSAL_MEMZERO(&sMDSSAddress, sizeof(sMDSSAddress));

  sMDSSAddress.uMdpAddress = MDP_MDSS_HWIOBaseAddr((uint32)sEFIChipSetFamily); /* retrieve mdss base addr */

  if (sMDSSAddress.uMdpAddress == 0)
  {
     Status  = MDP_STATUS_FAILED;
     MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error!!! falied to allocate MDSS base addr\n", sMDSSAddress.uMdpAddress);
  }
  else
  {
     // Setup the HAL base address
     HAL_MDSS_SetBaseAddress(&sMDSSAddress);
  }

  return Status;
}

/****************************************************************************
*
** FUNCTION: FindPlatformMMUSidMask()
*/
/*!
* \brief
*   Find MMUSidMask according to the platform
*
*
* \retval MDP_Status
*
****************************************************************************/
static MDP_Status FindPlatformMMUSidMask (EFIChipInfoFamilyType	eEFIChipSetFamily, uint32 *pMMUSidMask)
{
  MDP_Status Status = MDP_STATUS_NOT_SUPPORTED;

  if (NULL == pMMUSidMask)
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: FindPlatformMMUSidMask - Ivalid pMMuSidMask!\n");
    Status = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    for(uint32 uCount = 0; uCount< MDSS_BASEADDRESSMAPINGS_MAX; uCount++)
    {
      if(asChip_MMUSidMasks[uCount].sEFIChipSetFamily == eEFIChipSetFamily)
      {
        *pMMUSidMask = asChip_MMUSidMasks[uCount].uSidMask;
        Status	    = MDP_STATUS_OK;
        break;
      }
    }
  }
  return Status;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: get_DefaultSliceHeight()
**
** DESCRIPTION:
**   Configuration parameters that are required to correctly setup the
**   DSC related configuration like topology flags and resolution info
**   for each compression encoder.
**
** ---------------------------------------------------------------------- */
static uint32 get_DefaultSliceHeight(uint32 uPictureHeight)
{
   uint32 aSliceHeight[4] = {64, 48, 32, 16};
   uint32 uHeight         = uPictureHeight;
   int    uCount          = sizeof(aSliceHeight)/sizeof(uint32);
   int    i;


   for (i = 0; i < uCount; i++)
   {
	if ((uPictureHeight % aSliceHeight[i]) == 0)
        {
           uHeight = aSliceHeight[i];
           break;
        }
   }

   return uHeight;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: CheckFreeDSCEncoder()
**
** DESCRIPTION:
**   Check if DSC core has been used by any panel.
**
** ---------------------------------------------------------------------- */
static bool32 CheckFreeDSCEncoder(HAL_MDP_DSCId uDSCId)
{
  bool32              bDSCEncoderFree      = TRUE;
  MDP_Display_IDType  eDisplayId;
  uint32              uPingpongIndex;

  /* Check if any panel has used the DSC core */
  for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_EXTERNAL; eDisplayId++)
  {
    for (uPingpongIndex = 0; uPingpongIndex < MDP_DUAL_NUM_PINGPONGS; uPingpongIndex++)
    {
      if (uDSCId == MDP_GET_DISPLAYINFO_DSC_ID(eDisplayId, uPingpongIndex))
      {
        bDSCEncoderFree = FALSE;
        break;
      }
    }

    if (FALSE == bDSCEncoderFree)
    {
      break;
    }
  }

  return bDSCEncoderFree;
}
/* ---------------------------------------------------------------------- */
/**
** FUNCTION: AllocateDSCEncoder()
**
** DESCRIPTION:
**   Allocate DSC encoder module from pool that is free and can support required chroma format.
**
** ---------------------------------------------------------------------- */
static MDP_Status AllocateDSCEncoder(MDP_Panel_AttrType* pPanelInfo, uint32 uDSCNumInUse)
{
  MDP_Status    eStatus = MDP_STATUS_NO_RESOURCES;

  if ((NULL == pPanelInfo)                                                 ||
      (pPanelInfo->sDSCConfig.eDSCChromaFormat > HAL_MDP_DSCCHROMA_YUV420) ||   /* Check DSC Chroma format */
      (uDSCNumInUse > MDP_DUAL_NUM_PINGPONGS))                                  /* Currently only support dual pipe/PP. */
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (HAL_MDP_DSC_NONE != pPanelInfo->sDSCConfig.uDSCID[0])
  {
    /* DSC has already been allocated for the panel*/
    eStatus = MDP_STATUS_OK;
  }
  else
  {
    HAL_MDP_DSCId       uDSCId;
    MDP_HwPrivateInfo  *psMDPHwPrivateInfo = MDP_GETPRIVATEINFO();
    uint32              uRequiredDSCCaps;

    if ((HAL_MDP_DSCCHROMA_YUV422 == pPanelInfo->sDSCConfig.eDSCChromaFormat) ||
        (HAL_MDP_DSCCHROMA_YUV420 == pPanelInfo->sDSCConfig.eDSCChromaFormat))
    {
      uRequiredDSCCaps = MDP_DSC_CAPS_YUV_SUPPORT;
    }
    else
    {
      uRequiredDSCCaps = MDP_DSC_CAPS_RGB_SUPPORT;
    }

    /* DSC has be used as either single or a pair[0,1], [2,3], [4,5] */
    for (uDSCId = HAL_MDP_DSC_0; uDSCId < HAL_MDP_DSC_MAX; uDSCId += 2)
    {
      if ((uRequiredDSCCaps & psMDPHwPrivateInfo->pDeviceCaps->pDSCCaps[uDSCId].uDSCFeatureFlags) && /* If Chroma format is supported              */
          (TRUE == CheckFreeDSCEncoder(uDSCId)))
      {
        pPanelInfo->sDSCConfig.uDSCID[0] = uDSCId;
        
        if (uDSCNumInUse > 1)
        {
          pPanelInfo->sDSCConfig.uDSCID[1] = psMDPHwPrivateInfo->pDeviceCaps->pDSCCaps[uDSCId].eSlaveDSCId;
        }

        eStatus = MDP_STATUS_OK;
        break;
      }
    }
  }

  return eStatus;
}
/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPSetupDSCProperty()
**
** DESCRIPTION:
**   Configuration parameters that are required to correctly setup the
**   DSC related configuration like topology flags and resolution info
**   for each compression encoder.
**
** ---------------------------------------------------------------------- */
static MDP_Status MDPSetupDSCProperty(MDP_Panel_AttrType* pPanelInfo)
{
  MDP_Status                      eStatus           = MDP_STATUS_OK;
  HAL_MDP_DSCInfoType             sDSCInfo;
  uint32                          uPingPongNumInUse = 1;
  uint32                          uPingpongIndex;

  MDP_OSAL_MEMZERO(&sDSCInfo, sizeof(HAL_MDP_DSCInfoType));
  MDP_OSAL_MEMZERO(pPanelInfo->sDSCConfig.pDSCPpsBuffer, MDP_DSI_DSC_PPS_TOTAL_PACKET_SIZE);

  pPanelInfo->sDSCConfig.uDSCBpc              = gDscProfileModes[pPanelInfo->sDSCConfig.uDSCProfileID].uBitsPerComponent;
  pPanelInfo->sDSCConfig.uDSCBpp              = gDscProfileModes[pPanelInfo->sDSCConfig.uDSCProfileID].uBitsPerPixel;
  pPanelInfo->sDSCConfig.uDSCCompressionRatio = ((pPanelInfo->sDSCConfig.uDSCBpc * 3 * 1000) / pPanelInfo->sDSCConfig.uDSCBpp);
  pPanelInfo->sDSCConfig.bDSCLayerMixSplit    = gDscProfileModes[pPanelInfo->sDSCConfig.uDSCProfileID].bLMSplitEnable;
  pPanelInfo->sDSCConfig.bDSCBlockPred        = gDscProfileModes[pPanelInfo->sDSCConfig.uDSCProfileID].bBlockPredEnable;
  pPanelInfo->sDSCConfig.uDSCEncodersNum      = gDscProfileModes[pPanelInfo->sDSCConfig.uDSCProfileID].uEncodersNum;

  // Override and disable DSC block prediction setting.
  if (MDP_PANEL_DSI_FLAG_DISABLE_DSC_BLOCK_PREDICT & pPanelInfo->uAttrs.sDsi.uFlags)
  {
    pPanelInfo->sDSCConfig.bDSCBlockPred      = FALSE;
  }

  /* Setup the dsc encoder config */
  sDSCInfo.pDSCEncoderCfg                      = &pPanelInfo->sDSCEncCfg;
  sDSCInfo.pPacketData                         = pPanelInfo->sDSCConfig.pDSCPpsBuffer + MDP_DSI_DSC_HEADER_SIZE + MDP_DSI_DSC_XML_HEADER_SIZE;

 /* Populate DSC Version */
  sDSCInfo.pDSCEncoderCfg->uDSCMajor           = pPanelInfo->sDSCConfig.uDSCMajor;
  sDSCInfo.pDSCEncoderCfg->uDSCMinor           = pPanelInfo->sDSCConfig.uDSCMinor;
  sDSCInfo.pDSCEncoderCfg->uDSCScr             = pPanelInfo->sDSCConfig.uDSCScr;
  sDSCInfo.pDSCEncoderCfg->eDSCChromaFormat    = pPanelInfo->sDSCConfig.eDSCChromaFormat;

  /* Configure the Slice Width and height */
  if ((0 == pPanelInfo->sDSCConfig.uDSCSliceHeight) ||
      (pPanelInfo->sDSCConfig.uDSCSliceHeight > pPanelInfo->uDisplayHeight))
  {
    pPanelInfo->sDSCConfig.uDSCSliceHeight = get_DefaultSliceHeight(pPanelInfo->uDisplayHeight);
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDPSetupDSCProperty: Slice Height not defined in XML, use %d\n", pPanelInfo->sDSCConfig.uDSCSliceHeight);
  }

  sDSCInfo.pDSCEncoderCfg->uSliceHeight        = pPanelInfo->sDSCConfig.uDSCSliceHeight;

  if ((0 == pPanelInfo->sDSCConfig.uDSCSliceWidth) ||
      (pPanelInfo->sDSCConfig.uDSCSliceWidth > pPanelInfo->uDisplayWidth))
  {
     pPanelInfo->sDSCConfig.uDSCSliceWidth = pPanelInfo->uDisplayWidth;   /* 1 slice */
     MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDPSetupDSCProperty: Slice Width not defined in XML, use %d\n", pPanelInfo->sDSCConfig.uDSCSliceWidth);
  }

  if ((MDP_INTERFACE_SINGLE != pPanelInfo->uNumInterfaces) &&
      (MDP_INTERFACE_DUAL   != pPanelInfo->uNumInterfaces))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDPSetupDSCProperty: unexpected number of interface %d, default to 1\n", pPanelInfo->uNumInterfaces);
    pPanelInfo->uNumInterfaces = MDP_INTERFACE_SINGLE;
  }

  sDSCInfo.pDSCEncoderCfg->uSliceWidth         = pPanelInfo->sDSCConfig.uDSCSliceWidth;
  pPanelInfo->sDSCConfig.uDSCSliceWidthByte   = MDP_CEIL(pPanelInfo->sDSCConfig.uDSCSliceWidth * pPanelInfo->sDSCConfig.uDSCBpp, 8);
  sDSCInfo.pDSCEncoderCfg->uBPC                = pPanelInfo->sDSCConfig.uDSCBpc; 
  sDSCInfo.pDSCEncoderCfg->uBPP                = pPanelInfo->sDSCConfig.uDSCBpp;
  sDSCInfo.pDSCEncoderCfg->bBlockPredEnable    = pPanelInfo->sDSCConfig.bDSCBlockPred;

  /* hard slice == number of encoder per inteface * number of intervce */
  sDSCInfo.pDSCEncoderCfg->uNumOfActiveHS      = pPanelInfo->sDSCConfig.uDSCEncodersNum * pPanelInfo->uNumInterfaces;

  if (MDP_INTERFACE_SINGLE == pPanelInfo->uNumInterfaces)
  {
    if (0 == pPanelInfo->sDSCConfig.bDSCLayerMixSplit)
    {
      /* Single encoder and single dsi Based on the profile id setup the following */
      sDSCInfo.pDSCEncoderCfg->bPingPongSplitMUXActive    = 0;
      sDSCInfo.pDSCEncoderCfg->bSplitDispActive           = 0;
      sDSCInfo.pDSCEncoderCfg->bSplitMuxActive            = 0;
      sDSCInfo.pDSCEncoderCfg->uInputFrameHeightInPixels  = pPanelInfo->uDisplayHeight;
      sDSCInfo.pDSCEncoderCfg->uInputFrameWidthInPixels   = pPanelInfo->uDisplayWidth;
      uPingPongNumInUse                                   = 1;
    }
    else
    {
      /* Place holder when we implement the 2.5k Panel with DSC with dual pipe/mixer */
      /* Single DSI interface, Layer Mixer Split Config */

      sDSCInfo.pDSCEncoderCfg->bPingPongSplitMUXActive = 0;
      sDSCInfo.pDSCEncoderCfg->bSplitDispActive        = 0;

      if (1 == pPanelInfo->sDSCConfig.uDSCEncodersNum)
      {
        sDSCInfo.pDSCEncoderCfg->bSplitMuxActive       = 0; /* two LMs -- 3D Mux -- one encoder -- one interface  */
        pPanelInfo->sDSCConfig.uDSC3DMux              = 1; /* use 3D mux */
        uPingPongNumInUse                              = 1;
      }
      else
      {
        sDSCInfo.pDSCEncoderCfg->bSplitMuxActive       = 1;  /* two LMs -- two encoder -- merge -- one interface  */
        uPingPongNumInUse                              = 2;
      }

      sDSCInfo.pDSCEncoderCfg->uInputFrameHeightInPixels = pPanelInfo->uDisplayHeight;
      sDSCInfo.pDSCEncoderCfg->uInputFrameWidthInPixels  = pPanelInfo->uDisplayWidth;
    }

  }
  else if (MDP_INTERFACE_DUAL == pPanelInfo->uNumInterfaces)
  {
    /* Place holder when we implement 4k Panel with DSC */

    /* Single Pipe Config(one encoder) -> each DSI  */
    sDSCInfo.pDSCEncoderCfg->bPingPongSplitMUXActive = 0;
    sDSCInfo.pDSCEncoderCfg->bSplitDispActive        = 0;
    sDSCInfo.pDSCEncoderCfg->bSplitMuxActive         = 0;

    sDSCInfo.pDSCEncoderCfg->uInputFrameHeightInPixels = pPanelInfo->uDisplayHeight;
    sDSCInfo.pDSCEncoderCfg->uInputFrameWidthInPixels  = pPanelInfo->uDisplayWidth;

    /* Need to setup both the DSC encoders and the split mux  */

    uPingPongNumInUse                                = 2;
  }

  sDSCInfo.pDSCEncoderCfg->uNumOfActiveSS    = sDSCInfo.pDSCEncoderCfg->uInputFrameWidthInPixels / pPanelInfo->sDSCConfig.uDSCSliceWidth;
  sDSCInfo.pDSCEncoderCfg->uNumOfActiveSS   /= sDSCInfo.pDSCEncoderCfg->uNumOfActiveHS;  /*  slice per encoder */

  if ((MDP_DISPLAY_CONNECT_PRIMARY_DSI_VIDEO == pPanelInfo->ePhysConnect) ||
      ( MDP_DISPLAY_CONNECT_SECONDARY_DSI_VIDEO == pPanelInfo->ePhysConnect))
  {
    sDSCInfo.pDSCEncoderCfg->eInterfaceMode = HAL_MDP_INTERFACE_MODE_VIDEO;
  }
  else if ((MDP_DISPLAY_CONNECT_PRIMARY_DSI_CMD == pPanelInfo->ePhysConnect) ||
           (MDP_DISPLAY_CONNECT_SECONDARY_DSI_CMD == pPanelInfo->ePhysConnect))
  {
    sDSCInfo.pDSCEncoderCfg->eInterfaceMode = HAL_MDP_INTERFACE_MODE_COMMAND;
  }

  /* Dynamically allocate DSC Encoder */
  if (MDP_STATUS_OK != (eStatus = AllocateDSCEncoder(pPanelInfo, uPingPongNumInUse)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPSetupDSCProperty: Failed to allocate DSC encoder for display[%d]!\n", pPanelInfo->eDisplayId);
  }
  else
  {
    /* If there are 2 pingpong paths then program both */
    for (uPingpongIndex = 0; uPingpongIndex < uPingPongNumInUse; uPingpongIndex++)
    {
      HAL_MDP_DSCId uDSCId = pPanelInfo->sDSCConfig.uDSCID[uPingpongIndex];
    
      /* Calculate the DSC configuration settings for HAL */
      HAL_MDP_DSC_GetPropery(uDSCId, &sDSCInfo, 0x00);

      if (0 == pPanelInfo->sDSCConfig.uDSCSlicePerPacket)  /* from panel xml */
      {
        /* If DSIDSCSlicePerPacket is not set in panel xml file, then use the default calculated value of that,
         * otherwise use the value of DSIDSCSlicePerPacket from panel xml file */
        pPanelInfo->sDSCConfig.uDSCSlicePerPacket = sDSCInfo.pDSCEncoderCfg->uSlicePerPacket;
      }
      else if (0 != sDSCInfo.pDSCEncoderCfg->uSliceWidth)
      {
        if (pPanelInfo->sDSCConfig.uDSCSlicePerPacket > (pPanelInfo->uDisplayWidth / sDSCInfo.pDSCEncoderCfg->uSliceWidth))
        {
          /* If the value of DSIDSCSlicePerPacket from panel xml is out of range, then use the default calculated value as well. */
          pPanelInfo->sDSCConfig.uDSCSlicePerPacket = sDSCInfo.pDSCEncoderCfg->uSlicePerPacket;
        }
      }

      // Total slice per interface = (Hard Slice number x Soft Slice number)/interface number
      pPanelInfo->sDSCEncCfg.uSlicePerInterface = (sDSCInfo.pDSCEncoderCfg->uNumOfActiveSS * sDSCInfo.pDSCEncoderCfg->uNumOfActiveHS) / pPanelInfo->uNumInterfaces;
      pPanelInfo->sDSCEncCfg.uBytePerPkt        = pPanelInfo->sDSCConfig.uDSCSliceWidthByte * pPanelInfo->sDSCConfig.uDSCSlicePerPacket;
      pPanelInfo->sDSCEncCfg.uPclkPerLine       = MDP_CEIL(pPanelInfo->sDSCConfig.uDSCSliceWidthByte * pPanelInfo->sDSCEncCfg.uSlicePerInterface, 6);

      /* Commit the DSC registers */
      HAL_MDP_DSC_Setup(uDSCId, &sDSCInfo, 0x00);
    }
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPConfigureLinkCompression()
**
** DESCRIPTION:
**   Helper function to setup DSC
**
** ---------------------------------------------------------------------- */
static MDP_Status MDPConfigureLinkCompression(MDP_Panel_AttrType *pDisplayInfo)
{
  MDP_Status    eStatus     = MDP_STATUS_OK;

  if (NULL == pDisplayInfo)
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    /* If DSC is enabled setup MDP structures for DSC */
    if (TRUE == pDisplayInfo->sDSCConfig.bDSCEnable)
    {
      if (pDisplayInfo->sDSCConfig.uDSCProfileID < MDP_DSC_PROFILEID_MAX)
      {
        eStatus = MDPSetupDSCProperty(pDisplayInfo);
      }
      else
      {
        eStatus = MDP_STATUS_BAD_PARAM;
      }
    }
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPSetGPIOState()
**
** DESCRIPTION:
**   Configuration default GPIO states
**
** ---------------------------------------------------------------------- */
static MDP_Status MDPSetGPIOState(MDP_Panel_AttrType *pDisplayInfo)
{
  MDP_Status    eStatus     = MDP_STATUS_OK;

  for (uint32 uGPIOState = 0;uGPIOState <= 1;uGPIOState++)
  {
    MDPPlatformParams sPlatformConfig;

    MDP_OSAL_MEMZERO(&sPlatformConfig, sizeof(MDPPlatformParams));
    sPlatformConfig.sGPIOState.eGPIOType = MDPPLATFORM_GPIOTYPE_TLMM;
    sPlatformConfig.sGPIOState.pGPIOList = (uint32*)&(pDisplayInfo->uDefaultGPIOState[uGPIOState]);
    sPlatformConfig.sGPIOState.uListSize = MDP_MAX_GPIO_LIST_ENTRIES;
    sPlatformConfig.sGPIOState.uState = uGPIOState;

    if (MDP_STATUS_OK != MDPPlatformConfigure(pDisplayInfo->eDisplayId, MDPPLATFORM_CONFIG_SETGPIOSTATE, &sPlatformConfig))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: Failed to configure list of GPIOs to %d\n", uGPIOState);
      eStatus = MDP_STATUS_FAILED;
      break;
    }
  }
  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPGetHighestBankBit()
**
** DESCRIPTION:
**   Get the highest bankbit based on DDR Type
**
** ---------------------------------------------------------------------- */
static uint32 MDPGetHighestBankBit()
{
  uint32 uHighestBankBit;
  uint32 uDDRType = MDP_GetDDRType();

  switch (uDDRType)
  {
    case 4:
      uHighestBankBit = 15;
      break;
    case 5:
      uHighestBankBit = 16;
      break;
    default:
      uHighestBankBit = 16;
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "WARNING: unsupported uDDRType=%d, use DDR5 as default\n", uDDRType);
      break;
  }

  return uHighestBankBit;
}

/****************************************************************************
*
** FUNCTION: MDPGetAggregatedCoreAndBandwidth()
*/
/*!
* \brief
*    Loop all the panels and get the largest core clock value
*
* \param [out]    pMaxCoreClock - pointer to store maximal core clock
*        [out]    pBandwidth    - pointer to store total bandwidth
* \retval         MDP_Status
*
****************************************************************************/
static MDP_Status MDPGetAggregatedCoreAndBandwidth(uint32 *pMaxCoreClock, uint64 *pBandwidth)
{
  MDP_Display_IDType eDisplayId;
  uint32             uMaxCoreClock     = 0;
  uint64             uTotalBandwidth   = 0;
  MDP_Status         eStatus           = MDP_STATUS_OK;

  if ((NULL == pMaxCoreClock) ||
      (NULL == pBandwidth))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPGetAggregatedCoreAndBandwidth: invalid parameter");
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    /* Loop all the panels and get the largest core clock value */
    for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId < MDP_DISPLAY_MAX; eDisplayId++)
    {
      MDP_Panel_AttrType  *pDisplayInfo = MDP_GET_DISPLAYINFO(eDisplayId);

      if (NULL == pDisplayInfo)
      {
        continue;
      }
      else if ((0 == pDisplayInfo->sDynamicResourceConfig.uCoreClock) ||
               (0 == pDisplayInfo->sDynamicResourceConfig.uBandwidth))
      {
        continue;
      }
      else
      {
        uTotalBandwidth += pDisplayInfo->sDynamicResourceConfig.uBandwidth;

        /* Get the max core clock of all displays */
        if (pDisplayInfo->sDynamicResourceConfig.uCoreClock > uMaxCoreClock)
        {
          uMaxCoreClock = pDisplayInfo->sDynamicResourceConfig.uCoreClock;
        }
      }
    }

    *pMaxCoreClock = uMaxCoreClock;
    *pBandwidth    = uTotalBandwidth;
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: MDPRoundUpQ1616()
*/
/*!
* \brief
*    round up the Q16.16 format data
*
* \param [in]    data    - Q16.16 format data that needs be round up
* \retval                  the rounded up value
*
****************************************************************************/
static uint32 MDPRoundUpQ1616(uint32 data)
{
  return ((data + 0x8000) >> 16);
}

/****************************************************************************
*
** FUNCTION: MDPGetRefreshRate()
*/
/*!
* \brief
*    Get panel refresh rate
*
* \param [in]    pDisplayInfo    - the specific display device
*        [out]   pRefreshRate    - pointer to store refresh rate
* \retval                          MDP_Status
*
****************************************************************************/
uint32 MDPGetRefreshRate(MDP_Panel_AttrType *pDisplayInfo, uint32 *pRefreshRate)
{
  MDP_Status                eStatus         = MDP_STATUS_OK;

  if (NULL == pDisplayInfo ||
     (NULL == pRefreshRate))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPGetRefreshRate: parameter is NULL\n");
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    /* Get refresh rate according to different phy connect type */
    switch(pDisplayInfo->ePhysConnect)
    {
      case MDP_DISPLAY_CONNECT_PRIMARY_DSI_VIDEO:
      case MDP_DISPLAY_CONNECT_PRIMARY_DSI_CMD:
      case MDP_DISPLAY_CONNECT_SECONDARY_DSI_VIDEO:
      case MDP_DISPLAY_CONNECT_SECONDARY_DSI_CMD:
      {
        // Calculate panel refresh rate, if OEM only set dsi bit clock without refresh rate
        if (0 == pDisplayInfo->uAttrs.sDsi.uRefreshRate)
        {
          // Default to 60fps
          uint32 uRefreshRate = 60;

          if (pDisplayInfo->uAttrs.sDsi.uBitClockFrequency)
          {
            uint32 uTotalPixels = (pDisplayInfo->uDisplayWidth + 
                                   pDisplayInfo->sActiveTiming.uHLeftBorderDClk       + 
                                   pDisplayInfo->sActiveTiming.uHRightBorderDClk      +
                                   pDisplayInfo->sActiveTiming.uHsyncBackPorchDclk    +
                                   pDisplayInfo->sActiveTiming.uHsyncFrontPorchDclk   +
                                   pDisplayInfo->sActiveTiming.uHsyncPulseWidthDclk)  *
                                  (pDisplayInfo->uDisplayHeight                       +
                                   pDisplayInfo->sActiveTiming.uVTopBorderLines       +
                                   pDisplayInfo->sActiveTiming.uVBottomBorderLines    +
                                   pDisplayInfo->sActiveTiming.uVsyncBackPorchLines   +
                                   pDisplayInfo->sActiveTiming.uVsyncFrontPorchLines  +
                                   pDisplayInfo->sActiveTiming.uVsyncPulseWidthLines);
            uint32 uBpp          = MDP_GET_PIXELFMTMAP(pDisplayInfo->eColorFormat).uBitsPerPixel;
               
            // Refresh rate = (lanes * bitclock frequency) / (total pixels * bpp);
            if ((uTotalPixels > 0) && (uBpp > 0))
            {
              uRefreshRate = MDP_CEIL(pDisplayInfo->uAttrs.sDsi.uDataLaneNum * pDisplayInfo->uAttrs.sDsi.uBitClockFrequency, 
                              uTotalPixels * uBpp);
            }
          }
          else
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPGetRefreshRate: Unable to calculate refresh rate, default to 60fps\n");
          }

          pDisplayInfo->uAttrs.sDsi.uRefreshRate = Q16_VALUE(uRefreshRate);
        }
        
        *pRefreshRate = MDPRoundUpQ1616(pDisplayInfo->uAttrs.sDsi.uRefreshRate);
         break;
      }
      case MDP_DISPLAY_CONNECT_DP:
      case MDP_DISPLAY_CONNECT_DP_1:
      case MDP_DISPLAY_CONNECT_EDP:
        *pRefreshRate = MDPRoundUpQ1616(pDisplayInfo->uAttrs.sDp.uRefreshRate);
         break;
      default:
        *pRefreshRate = 60;
         MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPGetRefreshRate: Invalid interface, ePhysConnect=%d, set refresh rate to 60Hz for default\n", pDisplayInfo->ePhysConnect);
         break;
    }
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: MDPValidateVersion()
*/
/*!
* \brief
*    Give MDP a default version if found it's major verion is invalid
*
* \param [out]   psMDPHwPrivateInfo    - pointer to store hardware version
* \retval        MDP_Status
*
****************************************************************************/
static MDP_Status MDPValidateVersion(MDP_HwPrivateInfo  *psMDPHwPrivateInfo)
{
  MDP_Status   eStatus    = MDP_STATUS_OK;

  if (NULL == psMDPHwPrivateInfo)
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (psMDPHwPrivateInfo->sMDPVersionInfo.uMajorVersion == 0)
  {
    switch (psMDPHwPrivateInfo->sEFIChipSetFamily)
    {
     case EFICHIPINFO_FAMILY_AURORA:
       psMDPHwPrivateInfo->sMDPVersionInfo.uMajorVersion = 0x09;
       psMDPHwPrivateInfo->sMDPVersionInfo.uMinorVersion = 0x01;
       break;
     case EFICHIPINFO_FAMILY_KAILUA:
      default:
      // Default, set Aurora family i.e MDSS 9.0
      psMDPHwPrivateInfo->sMDPVersionInfo.uMajorVersion = 0x09;
      psMDPHwPrivateInfo->sMDPVersionInfo.uMinorVersion = 0x00;
      break;
    }
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: GetMDPVersionIndex()
*/
/*!
* \brief
*    Helper function to get mdp resource list
*
* \param [out]   pMDPResourceList    - pointer to store resource
* \retval        MDP_Status
*
****************************************************************************/
MDP_Status MDPGetMDPResourceList(MDP_ResourceList **pMDPResourceList)
{
  MDP_Status                      eStatus               = MDP_STATUS_OK;
  MDP_HwPrivateInfo              *psMDPHwPrivateInfo    = MDP_GETPRIVATEINFO();
  MDP_HwMajorFamilyResourceList  *pResListMajor;
  MDP_HwMinorFamilyResourceList  *pResListMinor;
  DisplayResourceList            *pPlatformResourceList;
  MDP_ResourceList               *pClkResList;

  if ((NULL == pMDPResourceList) ||
      (NULL == psMDPHwPrivateInfo))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPGetMDPResourceList: invalid parameter\n");
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (MDP_STATUS_OK != MDPValidateVersion(psMDPHwPrivateInfo))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPGetMDPResourceList: GetMDPVersionIndex  failed!\n");
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (NULL == (pResListMajor = (MDP_HwMajorFamilyResourceList*)&(asHardwareFamilyMajor[psMDPHwPrivateInfo->sMDPVersionInfo.uMajorVersion])))
  {
     MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPGetMDPResourceList: pResListMajor is NULL!\n");
     eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (NULL == (pResListMinor = (MDP_HwMinorFamilyResourceList*)&(pResListMajor->pMinorFamily[psMDPHwPrivateInfo->sMDPVersionInfo.uMinorVersion])))
  {
     MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPGetMDPResourceList: pResListMinor is NULL!\n");
     eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (NULL == (pPlatformResourceList = (DisplayResourceList*)pResListMinor->pDisplayPlatfromResources))
  {
     MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPGetMDPResourceList: pPlatformResourceList is NULL\n");
     eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (NULL == (pClkResList = (MDP_ResourceList*)pPlatformResourceList->pResList))
  {
     MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPGetMDPResourceList: pClkResList is NULL!\n");
     eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    *pMDPResourceList = pClkResList;
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: MDPGetDeviceCaps()
*/
/*!
* \brief
*    Get the MDSS capabilities
*
* \retval   Pointer to MDSS device capability table
*
****************************************************************************/
const MDPDeviceCapsType* MDPGetDeviceCaps()
{
  MDP_ResourceList               *pResList        = NULL;
  const MDPDeviceCapsType        *pMDPDeviceCaps  = NULL;

  if (MDP_STATUS_OK != MDPGetMDPResourceList(&pResList))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPGetDeviceCap: MDPGetMDPResourceList failed!\n");
  }
  else if (NULL == (pMDPDeviceCaps = pResList->pMDPDeviceCaps))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPGetDeviceCap: pMDPDeviceCap is NULL!\n");
  }

  return pMDPDeviceCaps;
}


/****************************************************************************
*
** FUNCTION: MDPGetInterfaceCaps()
*/
/*!
* \brief
*    Get the MDSS capabilities
*
* \retval   Pointer to MDSS interface capability table
*
****************************************************************************/
const MDPInterfaceCapsType* MDPGetInterfaceCaps()
{
  const MDPInterfaceCapsType   *pMDPInterfaceCaps  = NULL;
  const MDPDeviceCapsType      *pMDPDeviceCaps     = MDPGetDeviceCaps();

  if ((NULL != pMDPDeviceCaps) &&
      (NULL != pMDPDeviceCaps->pInterfaceCaps))
  {
    pMDPInterfaceCaps = pMDPDeviceCaps->pInterfaceCaps;
  }

  return pMDPInterfaceCaps;
}

/****************************************************************************
*
** FUNCTION: MDPCheckFpsFuse()
*/
/*!
* \brief
*    Check if panel FPS is beyond the SW Fuse .
*
* \retval   none
*
****************************************************************************/
static void MDPCheckFpsFuse(MDP_Panel_AttrType* pDisplayInfo)
{
  if (NULL != pDisplayInfo)
  {
    const MDPInterfaceCapsType* pMDPInterfaceCaps = MDPGetInterfaceCaps();
    
    if ((NULL                        != pMDPInterfaceCaps) &&
        (MDP_INTERFACE_CAPS_FPSFUSE  &  pMDPInterfaceCaps->uInterfaceFeatureCaps))
    {
      float                             fFPSFuse = 0;
      HAL_MDP_InterfaceInfoParamsType   sInterfaceInfo;

      MDP_OSAL_MEMZERO(&sInterfaceInfo, sizeof(HAL_MDP_InterfaceInfoParamsType));
      sInterfaceInfo.pfFPSFuse = &fFPSFuse;
    
      // Get SW Fuse setting for FPS
      if (HAL_MDSS_STATUS_SUCCESS == HAL_MDP_Interface_GetProperty(pDisplayInfo->sDisplayControlPath[0].eInterfaceId, &sInterfaceInfo, 0))
      {
        uint32 uRefreshRate;

        // Get panel refresh rate
        if (MDP_STATUS_OK != MDPGetRefreshRate(pDisplayInfo, &uRefreshRate))
        {
          MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPCheckFpsFuse: MDPGetRefreshRate failed!\n");
        }
        else
        {
          if (Q16_TO_FLOAT(uRefreshRate) > fFPSFuse)
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPCheckFpsFuse: Panel refresh rate (%d fps) is beyond SW Fuse (%d fps)!\n",(uint32)(Q16_TO_FLOAT(uRefreshRate)), (uint32)fFPSFuse);
          }
        }
      }
    }

  }

  return;
}
