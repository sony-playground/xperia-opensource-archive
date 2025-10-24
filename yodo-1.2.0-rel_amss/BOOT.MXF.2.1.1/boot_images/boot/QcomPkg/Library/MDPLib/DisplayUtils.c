/*=============================================================================

  File: DisplayUtils.c

  Source file for MDP Utils functions


  Copyright (c) 2016-2021,2022 Qualcomm Technologies, Inc.  
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/* Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*  * Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*  * Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
*  * Neither the name of The Linux Foundation nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*/

#include <Uefi.h>
#include <libfdt.h>
#include <string.h>
#include <stdio.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/SynchronizationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/RamPartitionTableLib.h>
#include <Protocol/EFIScm.h>
#include <Protocol/EFIDisplayUtils.h>
#include <Protocol/EFIDisplayPwrCtrl.h>
#include <Include/scm_sip_interface.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BootConfig.h>
#include <Library/PrintLib.h>
#include <IndustryStandard/Acpi50.h>
#include <IndustryStandard/Bmp.h>
#include <Library/GuidedFvLib.h>
#include "MDPLib.h"
#include "MDPLib_i.h"
#include "MDPSystem.h"
#include "MDPPlatformLib.h"
#include "DisplayUtils.h"
#include "HALDSILib.h"


/*=========================================================================
     Default Defines
==========================================================================*/

#define PANEL_LIST_STR_LEN_MAX                1024                   // maximum length for the panel list string
#define PANEL_CONFIG_STR_LEN_MAX              256                    // maximum length for panel configuration string

#define PANEL_CMD_MARKER_PRIM                 "prim:"                // Panel override: primary panel marker for state on & cont-splash on
#define PANEL_CMD_MARKER_PRIM_LEN             5                      // Length
#define PANEL_CMD_MARKER_PRIM0                "prim0:"               // Panel override: primary panel marker for state on & cont-splash on
#define PANEL_CMD_MARKER_PRIM1                "prim1:"               // Panel override: primary panel marker for state on & cont-splash off
#define PANEL_CMD_MARKER_PRIM2                "prim2:"               // Panel override: primary panel marker for state off
#define PANEL_CMD_MARKER_PRIM_LEN_EXT         6                      // Length

#define PANEL_CMD_MARKER_SEC                  "sec:"                 // Panel override: secondary panel marker for state on & cont-splash on
#define PANEL_CMD_MARKER_SEC_LEN              4                      // Length 
#define PANEL_CMD_MARKER_SEC0                 "sec0:"                // Panel override: secondary panel marker for state on & cont-splash on
#define PANEL_CMD_MARKER_SEC1                 "sec1:"                // Panel override: secondary panel marker for state on & cont-splash off
#define PANEL_CMD_MARKER_SEC2                 "sec2:"                // Panel override: secondary panel marker for state off
#define PANEL_CMD_MARKER_SEC_LEN_EXT          5                      // Length 

#define PANEL_CMD_MARKER_CONFIG               ":cfg"                 // Panel override: topology selection marker
#define PANEL_CMD_MARKER_CONFIG_LEN           4                      // Length

#define PANEL_CMD_MARKER_TIMING               ":timing"              // Panel override: timing selection marker
#define PANEL_CMD_MARKER_TIMING_LEN           7                      // Length

#define PANEL_CMD_MARKER_SKIP                 ":skip"                // Panel override: skip override in bootloader
#define PANEL_CMD_MARKER_SWAP                 ":swap"                // Panel override: swap DSI controllers
#define PANEL_CMD_MARKER_PLL0                 ":pll0"                // Panel override: use pll0
#define PANEL_CMD_MARKER_PLL1                 ":pll1"                // Panel override: use pll1
#define PANEL_CMD_MARKER_SPLASH_OFF           ":cs0"                 // Panel override: SEAMLESS_SPLASH OFF
#define PANEL_CMD_MARKER_SPLASH_ON            ":cs1"                 // Panel override: SEAMLESS_SPLASH ON

#define PANEL_CMD_MARKER_SIM                  "#sim"                 // Panel override: simulator panel
#define PANEL_CMD_MARKER_SIM_SWTE             "#sim-swte"            // Panel override: software tear check
#define PANEL_CMD_MARKER_SIM_HWTE             "#sim-hwte"            // Panel override: hardware tear check

#define NO_PANEL_CONFIG                       "none"                 // Panel override: skip display in bootloader


#define DISPLAY_CMDLINE_DSI_PRIMARY           " msm_drm.dsi_display0="   // Panel config prefix
#define DISPLAY_CMDLINE_DSI_SECONDARY         " msm_drm.dsi_display1="   // Panel config prefix


#define SIM_OVERRIDE                          "#override:"           // Panel config: override marker
#define DSI_0_STRING                          ":0:"                  // Panel config: dsi controller 0
#define DSI_1_STRING                          ":1:"                  // Panel config: dsi controller 1
#define DSI_CFG_STRING                        ":cfg:"                // Panel config: topology selection marker

#define HDMI_CONTROLLER_STRING                "hdmi:0"               // Panel config: HDMI controller marker
#define DSI_CONTROLLER_0_STRING               "dsi:0:"               // Panel config: DSI0 controller marker
#define DSI_CONTROLLER_1_STRING               "dsi:1:"               // Panel config: DSI1 controller marker

#define SPLIT_DSI_STRING                      "split_dsi"            // Panel config: ping pong split mode
#define DUAL_DSI_STRING                       "dual_dsi"             // Panel config: dual dsi mode
#define SINGLE_DSI_STRING                     "single_dsi"           // Panel config: single dsi_mode

#define SIM_MODE_STRING                       "sim"                  // Panel config: simulator panel
#define SIM_HWTE_STRING                       "sim-hwte"             // Panel config: software tear check
#define SIM_SWTE_STRING                       "sim-swte"             // Panel config: hardware tear check

//Device tree related constants
#define DTB_PAD_SIZE                           1024                              // Device tree buffer padding size
#define SPLASH_MEM_DT_NODE_NAME                "/reserved-memory/splash_region"  // Name of the splash buffer device tree node
#define SPLASH_MEM_DT_REG                      "reg"                             // Splash Node's sub node name
#define SPLASH_MEM_PROP_SIZE                   (4 * sizeof(UINT32))              // Size of splash node in bytes
/* Helper to get display params struct*/
#define GET_DISPLAY_CONTEXT()                 (&gsDisplayContext)

// The display panel configuration file macro definition
#define DISP_FILE_EXT                         L".cfg"
#define DISP_VARIABLE_VALUE_MAX_SIZE          256
#define DISP_LOGFS                            L"logfs"

// Maximum  register log output file size in bytes
#define DISP_LOG_REG_OUT_FILE_MAX_SIZE        (1*1024*1024)

// Minium size for storing a line in bytes
#define DISP_LOG_REG_OUT_LINE_MIN_SIZE        (32)

// Max logo file index
#define MDP_MAX_LOGO_FILE_INDEX               (16)

// Middle of the logo should be 38% from first scanline.
#define BGRT_NORMAL_POSITION_RATIO            (0.382f)
#define BGRT_INVERT_POSITION_RATIO            (1.0f - BGRT_NORMAL_POSITION_RATIO)

/* -----------------------------------------------------------------------
** Local Types
** ----------------------------------------------------------------------- */

/* Display Utils Context
 */
typedef struct
{
  Display_UtilsParamsType       sDisplayParams;                           /* Params parsed from override command */
  bool32                        bOverride;                                /* Flag panel override */
  CHAR8                         pPanelConfig[PANEL_CONFIG_STR_LEN_MAX];   /* Panel configuration command to kernel */
  uint32                        uDynamicRefreshDataAddress;               /* Memory address for PLL calibration data */
  uint32                        uContinuousSplashAddress;                 /* Memory address for continuous splash buffer */
  uint32                        uContinuousSplashDataSize;                /* Size of data in the continous splash buffer */
  EFI_DISABLED_DISPLAYS_TYPE    sDisabledDisplayList;                     /* List of displays to be disabled during boot */
  CHAR8                         aLogoConfig[FRAMEBUFFER_MAX_NUMBER][16];  /* Logo string configured for display */
} Display_UtilsContextType;

/* External references */

// Physical Partition Guids
extern EFI_GUID gEfiEmmcGppPartition1Guid;
extern EFI_GUID gEfiEmmcUserPartitionGuid;
extern EFI_GUID gEfiUfsLU4Guid;
extern EFI_GUID gMainFvGuid;
extern EFI_GUID gEfiImageFvNameGuid;

// Partition Type
extern EFI_GUID gEfiPlatPartitionTypeGuid;

/*=========================================================================
     Local Functions Prototype Headers
==========================================================================*/
/* CalculateLogoPosition() - Calculate the location of the logo image within the screen
 */
static VOID CalculateLogoPosition(
    IN  UINT32                LogoWidth,
    IN  UINT32                LogoHeight,
    OUT UINT32               *pPosX,
    OUT UINT32               *pPosY,
    RenderLogoParamsType     *pRenderLogoParams);

/* ConversionPixelCopy() - Pixel copy with fomat conversion
 */
static VOID ConversionPixelCopy(
    IN UINT32     SourceBitDepth,
    IN VOID      *ColorMap,
    IN UINT8     *SourceBuffer,
    IN UINT32     DestBitDepth,
    IN UINT8     *DestBuffer,
    IN UINT32     NumPixels);

/* RotatePixel32Copy() - Pixel copy rotation
 */
static VOID RotatePixel32Copy(
    IN UINT32               *SourceBuffer,
    IN UINT32               *DestBuffer,
    IN UINT32                ImageWidth,
    IN UINT32                ImageHeight,
    IN DispBGRTRotationType  eBGRTRotation);

/* Display_Utils_SavePLLCodes() - Store pll codes to service variable
 */
static EFI_STATUS Display_Utils_SavePLLCodes(CHAR16 *pVariableName, MDP_PLLCodesIDEntryInfo *pPllCodesIDEntry, UINT32 uNumEntries);

/* Display_Utils_SetProperty
 */
EFI_STATUS Display_Utils_SetProperty (
    EFI_DISPLAY_UTILS_PROPERTY_TYPE ePropertyType,
    void                           *pData,
    UINT32                          uDataSize);

/* Display_Utils_GetProperty
 */
EFI_STATUS Display_Utils_GetProperty (
    EFI_DISPLAY_UTILS_PROPERTY_TYPE ePropertyType,
    void                           *pData,
    UINT32                         *pDataSize);

/* Display_Utils_RenderLogo
 */
EFI_STATUS Display_Utils_RenderLogo(IN  EFI_DISPLAY_UTILS_RENDERLOGO_CONFIG *psRenderLogoConfig);

/* Display_Utils_SetMode
 */
EFI_STATUS Display_Utils_SetMode (
    UINT32                         DisplayId,
    UINT32                         ModeNum,
    UINT32                         Flags);


/*=========================================================================
     Global Variables
==========================================================================*/

/* Display Utils Context
 */
Display_UtilsContextType gsDisplayContext;

/* Display Utils Protocol Implementation
 */
EFI_QCOM_DISPLAY_UTILS_PROTOCOL  gQcomDisplayUtilsProtocolImplementation =
{
  DISPLAY_UTILS_REVISION_2,
  Display_Utils_SetProperty,
  Display_Utils_GetProperty,
  Display_Utils_RenderLogo,
  Display_Utils_SetMode,
  Display_Utils_SetVariable,
  Display_Utils_GetVariable
};


/*=========================================================================
     Local Static Functions
==========================================================================*/

/****************************************************************************
*
** FUNCTION: LocalAsciiStrnCat()
*/
/*!
* \brief
*   Helper function to concatenate strings upto limit and ignore further
*   characters.
*
* \param [in] pDest          - Destination string
*        [in] uLimit         - Max length for dest
*        [in] pSrc           - Source string
*
* \retval available chars in dest
*
****************************************************************************/
static uint32 LocalAsciiStrnCat(CHAR8 *pDest, uint32 uLimit, CHAR8 *pSrc)
{
  uint32 uSize  = AsciiStrLen(pSrc);
  uint32 uStart = AsciiStrLen(pDest);
  uint32 uAvail = 0;

  if (uLimit > (uStart + 1))
  {
    uAvail = uLimit - (uStart + 1); // 1 termination char
  }

  /* Check if there is enough size available */
  if ( uSize > uAvail )
  {
    //pSrc too big - will be truncated
    DEBUG((EFI_D_WARN, "DisplayUtils: Not enough room available for strcat: will truncate <%a> avail %d reqd %d\n",
           pSrc, uAvail, uSize));

    uSize = uAvail;
  }

  if (0 < uAvail)
  {
    /* AsciiStnCpy will copy pSrc and the fill the next byte with zero */
    AsciiStrnCpyS(pDest+uStart, uLimit, pSrc, uSize);

    uAvail -= uSize;
  }

  return uAvail;
}


/****************************************************************************
*
** FUNCTION: LocalAsciiPrintConfig()
*/
/*!
* \brief
*   Helper function to append configuration string. Converts num to ascii and
*   then concatenates to pDest
*
* \param [in] pDest          - Destination string
*        [in] uLimit         - Max length for pDest
*        [in] iNum           - configuration index
*
* \retval None
*
****************************************************************************/
static void LocalAsciiPrintConfig(CHAR8 *pDest, uint32 uLimit, int32 iNum)
{
  /* config ranges from 0 - 99 */
  if ((0 <= iNum)  &&
      (100 > iNum))
  {
    uint32 i       = 0;
    uint32 uDigit;
    CHAR8  str[3];

    MDP_OSAL_MEMZERO(str, sizeof(str));

    uDigit = iNum / 10;

    if (0 < uDigit)
    {
      str[i++] = '0'+uDigit;
    }

    uDigit   = iNum - (10 * uDigit);
    str[i++] = '0' + uDigit;
    str[i]   = 0;

    LocalAsciiStrnCat(pDest, uLimit, ":config");
    LocalAsciiStrnCat(pDest, uLimit, str);
  }
}


/****************************************************************************
*
** FUNCTION: LocalAsciiTrim()
*/
/*!
* \brief
*   Helper function to remove leading spaces in ascii string
*
* \param [in] pSrc     - pointer to string
*
* \retval Trimmed ascii string or NULL if input is NULL
*
****************************************************************************/
static CHAR8* LocalAsciiTrim(CHAR8* pStr)
{
  if (NULL != pStr)
  {
    /* remove leading spaces, if any */
    while (' ' == *pStr)
    {
      pStr++;
    }
  }

  return pStr;
}


/****************************************************************************
*
** FUNCTION: GetTokenEnd()
*/
/*!
* \brief
*   Helper function to find the index of specific tokens inside string
*
* \param [in] pString        - input string to look for delimiters
*
* \retval pointer to delimiter or NULL if not found
*
****************************************************************************/
static CHAR8* GetTokenEnd(const CHAR8 *pString)
{
  CHAR8 *pHash  = NULL;
  CHAR8 *pColon = NULL;
  CHAR8 *pOut   = NULL;

  /* ':' and '#' are delimiters in the string */
  pColon = AsciiStrStr((CHAR8 *) pString, ":");
  pHash  = AsciiStrStr((CHAR8 *) pString, "#");

  if ((NULL != pColon) &&
      (NULL != pHash))
  {
    pOut = ((pColon < pHash) ? pColon : pHash);
  }
  else if (NULL != pColon)
  {
    pOut = pColon;
  }
  else if (NULL != pHash)
  {
    pOut = pHash;
  }

  return pOut;
}


/****************************************************************************
*
** FUNCTION: UpdateDisplayParams()
*/
/*!
* \brief
*   Helper function to update display params struct with selected panel info
*
* \param Index of display interface
*
* \retval None
*
****************************************************************************/
static void UpdateDisplayParams(MDP_Display_IDType eDisplayId)
{
  Display_UtilsContextType *pDisplayContext = GET_DISPLAY_CONTEXT();
  PanelOverrideParams      *pPanelParams;
  MDPPlatformParams         sPlatformParams;

  if (MDP_DISPLAY_PRIMARY == eDisplayId)
  {
    pPanelParams = &pDisplayContext->sDisplayParams.sPrimary;
  }
  else
  {
    pPanelParams = &pDisplayContext->sDisplayParams.sSecondary;
  }

  MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));

  if (MDP_STATUS_OK != MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_GETPANELDTINFO, &sPlatformParams))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: MDPPLATFORM_CONFIG_GETPANELDTINFO failed\n"));
  }
  else if ((NULL                     == sPlatformParams.pPanelConfig)             ||
           (MDPPLATFORM_PANEL_BYPASS == sPlatformParams.pPanelConfig->ePanelType) ||
           (MDPPLATFORM_PANEL_MAX    <= sPlatformParams.pPanelConfig->ePanelType))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: Panel '%a' not found, passing command to the kernel\n", pPanelParams->shortName));
  }
  else
  {
    PanelConfigType *pPanelConfig = sPlatformParams.pPanelConfig;

    pPanelParams->pPanelConfig    = pPanelConfig;

    AsciiStrCpyS(pPanelParams->shortName, DISPLAY_PANEL_NAME_MAX_LEN, pPanelConfig->szName);

    if (MDPPLATFORM_PANEL_PHYSICAL == sPlatformParams.pPanelConfig->ePanelType)
    {
      pDisplayContext->sDisplayParams.uFlags   |= pPanelConfig->pPhysicalPanelConfig->pModeInfo->uModeFlag;
      pPanelParams->uSelectedModeFlags         |= pPanelConfig->pPhysicalPanelConfig->pModeInfo->uModeFlag;
    }
  }
}



/****************************************************************************
*
** FUNCTION: SetupSupportedDisplayInterface()
*/
/*!
* \brief
*   Helper function to setup display interfaces according to fastboot oem override string
*
* \param pSupportedDisplayList  - Supported display interface list.
*        pPanelOverrideCmd      - panel override command.
*
* \retval None
*
****************************************************************************/
static void SetupSupportedDisplayInterface(bool32 (*pSupportedDisplayList)[], char *pPanelOverrideCmd, bool32 bPrimSelected, bool32 bSecSelected)
{
  char *pOverride = (char*) pPanelOverrideCmd;

  if ((NULL == pOverride) ||
      (NULL == pSupportedDisplayList))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: Invalid panel override command or supported display list\n"));
  }
  else if ((FALSE == bPrimSelected) &&
           (FALSE == bSecSelected))
  {
    /* If both prim<0/1/2> and sec<0/1/2> can't be detected, then only enable primray display by default */
    (*pSupportedDisplayList)[MDP_DISPLAY_PRIMARY]   = TRUE;
    (*pSupportedDisplayList)[MDP_DISPLAY_SECONDARY] = FALSE;
  }
  else
  {
    (*pSupportedDisplayList)[MDP_DISPLAY_PRIMARY]   = bPrimSelected;
    (*pSupportedDisplayList)[MDP_DISPLAY_SECONDARY] = bSecSelected;
  }
}


/****************************************************************************
*
** FUNCTION: ParsePanelOverrideCommand()
*/
/*!
* \brief
*   Helper function to parse and extract params from panel override string
*
* \param [in]  pPanelOverrideCmd - panel override command from ABL
*        [out] pDisplayParams    - display override params
*
* Description:
*   For more details about the fastboot commands, see Docs/DisplayFastbootCmds.txt for reference.
*
* \retval bool32 - TRUE: panel override enabled, FALSE: disable panel override, using default panel
*
****************************************************************************/
static bool32 ParsePanelOverrideCommand(bool32 (*pSupportedDisplayList)[], const char *pPanelOverrideCmd, Display_UtilsParamsType *pDisplayParams)
{
  char    *pStr           = NULL;
  char    *pStrTmp        = NULL;
  char    *pOverride      = (char*) pPanelOverrideCmd;
  bool32   bPrimSelected  = FALSE;
  bool32   bSecSelected   = FALSE;
  int32    len;

  if ((NULL == pDisplayParams) ||
      (NULL == (pOverride = LocalAsciiTrim(pOverride))))
  {
    DEBUG((EFI_D_ERROR, "DisplayUtils: Invalid arguments\n"));
  }
  /* check for special configuration */
  else if(0 == AsciiStrnCmp(pOverride, NO_PANEL_CONFIG, AsciiStrLen(NO_PANEL_CONFIG)))
  {
    /* special case: if fastboot oem panel name is "none" then enable SW render and pass empty string to kernel */
    pDisplayParams->uFlags |= DISP_MODE_SKIP_BOOTLOADER|DISP_MODE_PANEL_NONE;
  }
  else if ((0 == AsciiStrnCmp(pOverride, DISP_ENABLE_LOG, AsciiStrLen(DISP_ENABLE_LOG))) ||
           (0 == AsciiStrnCmp(pOverride, DISP_DISABLE_LOG, AsciiStrLen(DISP_DISABLE_LOG))))
  {
    if (EFI_SUCCESS != MDP_SetBootServiceVariable(DISPVAR_LOG_ENABLE, pOverride, AsciiStrLen(pOverride), EFI_VARIABLE_NON_VOLATILE))
    {
      DEBUG((EFI_D_WARN,"DisplayUtils: Failed to set display log enable service variable\n"));
    }

    /* For special strings, we don't actually want to inform UEFI Driver that panel configuration has changed.
     * By setting *pOverride to '\0', this function will return FALSE to indicate no panel override happen.
     */
    *pOverride = '\0';
  }
  else
  {
    MDPPlatformParams sPlatformParams;
    char                       *pPrimStr        = NULL;
    char                       *pSecStr         = NULL;
    Display_UtilsContextType   *pDisplayContext = GET_DISPLAY_CONTEXT();
    uint32                      uIndex          = 0;
    uint32                      uPrimLen        = 0;
    uint32                      uSecLen         = 0;

    MDP_OSAL_MEMZERO(pDisplayParams, sizeof(Display_UtilsParamsType));

    if (NULL != (pPrimStr = AsciiStrStr((char *) pOverride, PANEL_CMD_MARKER_PRIM)))
    {
      bPrimSelected = TRUE;
      uPrimLen      = PANEL_CMD_MARKER_PRIM_LEN;
    }
    else if (NULL != (pPrimStr = AsciiStrStr((char *) pOverride, PANEL_CMD_MARKER_PRIM0)))
    {
      bPrimSelected = TRUE;
      uPrimLen      = PANEL_CMD_MARKER_PRIM_LEN_EXT;
    }
    else if (NULL != (pPrimStr = AsciiStrStr((char *) pOverride, PANEL_CMD_MARKER_PRIM1)))
    {
      bPrimSelected                    = TRUE;
      uPrimLen                         = PANEL_CMD_MARKER_PRIM_LEN_EXT;
      pDisplayParams->sPrimary.uFlags |= DISP_MODE_SEAMLESS_SPLASH_OFF;
    }
    else if (NULL != (pPrimStr = AsciiStrStr((char *) pOverride, PANEL_CMD_MARKER_PRIM2)))
    {
      pDisplayContext->sDisabledDisplayList.aDisabledDisplays[0] = EFI_DISPLAY_TYPE_PRIMARY;
      pDisplayContext->sDisabledDisplayList.uNumOfDisplays       = 1;
      bPrimSelected                                              = TRUE;
      uPrimLen                                                   = PANEL_CMD_MARKER_PRIM_LEN_EXT;
      uIndex++;
    }

    if (NULL != (pSecStr = AsciiStrStr((char *) pOverride, PANEL_CMD_MARKER_SEC)))
    {
      bSecSelected = TRUE;
      uSecLen      = PANEL_CMD_MARKER_SEC_LEN;
    }
    else if (NULL != (pSecStr = AsciiStrStr((char *) pOverride, PANEL_CMD_MARKER_SEC0)))
    {
      bSecSelected = TRUE;
      uSecLen      = PANEL_CMD_MARKER_SEC_LEN_EXT;
    }
    else if (NULL != (pSecStr = AsciiStrStr((char *) pOverride, PANEL_CMD_MARKER_SEC1)))
    {
      bSecSelected                       = TRUE;
      uSecLen                            = PANEL_CMD_MARKER_SEC_LEN_EXT;
      pDisplayParams->sSecondary.uFlags |= DISP_MODE_SEAMLESS_SPLASH_OFF;
    }
    else if (NULL != (pSecStr = AsciiStrStr((char *) pOverride, PANEL_CMD_MARKER_SEC2)))
    {
      pDisplayContext->sDisabledDisplayList.aDisabledDisplays[uIndex] = EFI_DISPLAY_TYPE_SECONDARY;
      pDisplayContext->sDisabledDisplayList.uNumOfDisplays++;
      bSecSelected                                                    = TRUE;
      uSecLen                                                         = PANEL_CMD_MARKER_SEC_LEN_EXT;
    }

    SetupSupportedDisplayInterface(pSupportedDisplayList, pOverride, bPrimSelected, bSecSelected);

    /* Primary panel string */
    if (NULL != pPrimStr)
    {
      /*
       * Parse the primary panel for cases where 'prim' or 'prim<0/1/2>' prefix
       * is present in the fastboot oem command before primary
       * panel string.
       * Examples:
       * 1.) fastboot oem select-display-panel prim:jdi_1080p_video:sec:sharp_1080p_cmd
       * 2.) fastboot oem select-display-panel prim<0/1/2>:jdi_1080p_video:sec<0/1/2>:sharp_1080p_cmd
       * 3.) fastboot oem select-display-panel prim<0/1/2>:jdi_1080p_video:skip
       */
      pPrimStr += uPrimLen;
      pStrTmp   = GetTokenEnd((const char*) pPrimStr);
      if (NULL == pStrTmp)
      {
        pStrTmp = pPrimStr + AsciiStrLen(pPrimStr);
      }
      len = pStrTmp - pPrimStr;
      if (len > (DISPLAY_PANEL_NAME_MAX_LEN - 1) )
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Panel name is too long %d vs max %d\n", len, DISPLAY_PANEL_NAME_MAX_LEN - 1));
        len = DISPLAY_PANEL_NAME_MAX_LEN - 1;
      }

      AsciiStrnCpyS(pDisplayParams->sPrimary.shortName, DISPLAY_PANEL_NAME_MAX_LEN, pPrimStr, len);

      pDisplayParams->sPrimary.shortName[DISPLAY_PANEL_NAME_MAX_LEN-1] = 0;
    }
    else
    {
      /*
       * Check if secondary panel string is present.
       * The 'prim' or 'prim<0/1/2>' prefix definitely needs to be present
       * to specify primary panel for cases where secondary panel
       * is also specified in fastboot oem command.
       * If 'sec' or 'sec<0/1/2>' prefix is used without 'prim' or 'prim<0/1/2>' prefix, it
       * means the default panel needs to be picked as single secondary panel.
       * Example:
       * 1.) fastboot oem select-display-panel sec:sharp_1080p_cmd
       * 2.) fastboot oem select-display-panel sec<0/1/2>:sharp_1080p_cmd
       */
      if (NULL == pSecStr)
      {
        /*
         * This code will be executed for cases where the
         * secondary panel is not specified i.e., single/split
         * DSI cases.
         * Examples:
         * 1.) fastboot oem select-display-panel jdi_1080p_video
         * 2.) fastboot oem select-display-panel sharp_1080p_cmd:skip
         * 3.) fastboot oem select-display-panel sim_cmd_panel#sim-swte
         */
        pStrTmp = GetTokenEnd(pOverride);
        if (NULL != pStrTmp)
        {
          len = pStrTmp - pOverride;
        }
        else
        {
          len = AsciiStrLen(pOverride);
        }

        if (len > (DISPLAY_PANEL_NAME_MAX_LEN - 1) )
        {
          DEBUG((EFI_D_WARN, "DisplayUtils: Panel name is too long %d vs max %d\n", len, DISPLAY_PANEL_NAME_MAX_LEN - 1));
          len = DISPLAY_PANEL_NAME_MAX_LEN - 1;
        }
        AsciiStrnCpyS(pDisplayParams->sPrimary.shortName, DISPLAY_PANEL_NAME_MAX_LEN, pOverride, len);
      }
    }

    MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));
    AsciiStrCpyS(sPlatformParams.sPlatformPanel.szName, DISPLAY_PANEL_NAME_MAX_LEN, pDisplayParams->sPrimary.shortName);

    /* Select panel config according to panel name */
    if (MDP_STATUS_OK != MDPPlatformConfigure(MDP_DISPLAY_PRIMARY, MDPPLATFORM_CONFIG_SELECTPANELCONFIG, &sPlatformParams))
    {
      DEBUG((EFI_D_WARN, "DisplayUtils: Panel configuration not supported, entering SW rendering mode\n"));
    }
    else
    {
      pDisplayParams->sPrimary.pPanelConfig = sPlatformParams.sPanelConfigInfo.pPanelConfig;
    }

    /*
     * Secondary panel string.
     * This is relatively simple. The secondary panel string gets
     * parsed if the 'sec' prefix is present.
     */
    if (NULL != pSecStr)
    {

      pSecStr += uSecLen;
      pStrTmp  = GetTokenEnd((const char*)pSecStr);

      if (NULL == pStrTmp)
      {
        pStrTmp = pSecStr + AsciiStrLen(pSecStr);
      }
      len = pStrTmp - pSecStr;
      if (len > (DISPLAY_PANEL_NAME_MAX_LEN - 1))
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Panel name is too long %d vs max %d\n", len, DISPLAY_PANEL_NAME_MAX_LEN - 1));
        len = DISPLAY_PANEL_NAME_MAX_LEN - 1;
      }
      AsciiStrnCpyS(pDisplayParams->sSecondary.shortName, DISPLAY_PANEL_NAME_MAX_LEN, pSecStr, len);
      pDisplayParams->sSecondary.shortName[DISPLAY_PANEL_NAME_MAX_LEN - 1] = 0;

      AsciiStrCpyS(sPlatformParams.sPlatformPanel.szName, DISPLAY_PANEL_NAME_MAX_LEN, pDisplayParams->sSecondary.shortName);

      /* Select panel config according to panel name */
      if (MDP_STATUS_OK != MDPPlatformConfigure(MDP_DISPLAY_SECONDARY, MDPPLATFORM_CONFIG_SELECTPANELCONFIG, &sPlatformParams))
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Panel configuration not supported, entering SW rendering mode\n"));
      }
      else
      {
        pDisplayParams->sSecondary.pPanelConfig = sPlatformParams.sPanelConfigInfo.pPanelConfig;
      }


      /* Topology configuration for secondary panel */
      pDisplayParams->sSecondary.eTopologyCfg = DISP_TOPOLOGY_CONFIG_NONE;

      pStrTmp = AsciiStrStr((char *)pSecStr, PANEL_CMD_MARKER_CONFIG);
      if (NULL != pStrTmp)
      {
        pDisplayParams->sSecondary.eTopologyCfg = AsciiStrDecimalToUintn((const char*)(pStrTmp + PANEL_CMD_MARKER_CONFIG_LEN)) + 1;
      }
    }
    else
    {
      pDisplayParams->sSecondary.shortName[0] = '\0';
    }

    /* Topology configuration for primary panel */
    pDisplayParams->sPrimary.eTopologyCfg = DISP_TOPOLOGY_CONFIG_NONE;

    pStrTmp = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_CONFIG);
    if ((NULL != pStrTmp) &&
        ((NULL == pSecStr) ||
         ((NULL != pSecStr) &&
          (pStrTmp < pSecStr))))
    {
      pDisplayParams->sPrimary.eTopologyCfg = AsciiStrDecimalToUintn((const char*)(pStrTmp + PANEL_CMD_MARKER_CONFIG_LEN)) + 1;
    }

    pStrTmp = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_TIMING);
    if ((NULL != pStrTmp) &&
        ((NULL == pSecStr) ||
         ((NULL != pSecStr) &&
          (pStrTmp < pSecStr))))
    {
      pDisplayParams->sPrimary.eTimingCfg = AsciiStrDecimalToUintn((const char*)(pStrTmp + PANEL_CMD_MARKER_TIMING_LEN)) + 1;
    }

    /* Skip LK configuration */
    pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SKIP);
    if (NULL != pStr)
    {
      pDisplayParams->uFlags |= DISP_MODE_SKIP_BOOTLOADER;
    }

   /* SEAMLESS SPLASH COntrol */
    pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SPLASH_ON);
    if (NULL != pStr)
    {
      pDisplayParams->sPrimary.uFlags |= DISP_MODE_SEAMLESS_SPLASH_ON;
    }

    pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SPLASH_OFF);
    if (NULL != pStr)
    {
      pDisplayParams->sPrimary.uFlags |= DISP_MODE_SEAMLESS_SPLASH_OFF;
    }

    /* Interposer card to swap DSI0 and DSI1 lanes */
    pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SWAP);
    if (NULL != pStr)
    {
      pDisplayParams->uFlags |= DISP_MODE_SWAP_DSI_CONTROLLER;
    }

    /* DSI PLL source */
    pDisplayParams->ePllOverride = PLL_OVERRIDE_NONE;
    pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_PLL0);
    if (NULL != pStr)
    {
      pDisplayParams->ePllOverride = PLL_OVERRIDE_PLL0;
    }
    else
    {
      pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_PLL1);
      if (NULL != pStr)
      {
        pDisplayParams->ePllOverride = PLL_OVERRIDE_PLL1;
      }
    }

    /* Simulator status */
    pDisplayParams->eSimMode = PANELSIM_NONE;
    if (NULL != AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SIM_HWTE))
    {
      pDisplayParams->eSimMode = PANELSIM_HWTE;
    }
    else if (NULL != AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SIM_SWTE))
    {
      pDisplayParams->eSimMode = PANELSIM_SWTE;
    }
    else if (NULL != AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SIM))
    {
      pDisplayParams->eSimMode = PANELSIM_MODE;
    }

    /* disable cont splash when booting in simulator mode */
    if (PANELSIM_NONE != pDisplayParams->eSimMode)
    {
      pDisplayParams->sPrimary.uFlags &= ~DISP_MODE_SEAMLESS_SPLASH_ON;
      pDisplayParams->sPrimary.uFlags |= DISP_MODE_SEAMLESS_SPLASH_OFF;
    }
  }

  /* Consider it override as long as user input something */
  return ((NULL == pOverride) ? FALSE : ((AsciiStrLen(pOverride) > 0) ? TRUE : FALSE));
}


/****************************************************************************
*
** FUNCTION: panelConfigOutput()
*/
/*!
* \brief
*   Helper to build panel configuration string
*
* \param [in]  eDisplayId       - ID of display interface
         [in]  psOverrideParam  - display override params
*        [out] ppStr            - Panel configuration string
*
* \retval None
*
****************************************************************************/
void panelConfigOutput(MDP_Display_IDType eDisplayId, PanelOverrideParams *psOverrideParam, CHAR8 **ppStr)
{
  uint32              uShortNameLen       = 0;
  uint32              uTopology           = 0;
  uint32              uTiming             = 0;
  uint32              uNumError           = 0;
  MDP_Panel_AttrType *pDisplayInfo        = MDP_GET_DISPLAYINFO(eDisplayId);
  CHAR8               DTLabel[DISPLAY_PANEL_DT_LABEL_MAX_LEN];

  /* Don't pass the panel ID string for panels that cannot be detected or initialized */
  if (FALSE == pDisplayInfo->bDetected)
  {
    uNumError++;
  }
  uNumError += pDisplayInfo->uInitFailures;

  if (uNumError > 0)
  {
    **ppStr = 0;
  }
  else if ((NULL                     == psOverrideParam->pPanelConfig)             ||
           (MDPPLATFORM_PANEL_BYPASS == psOverrideParam->pPanelConfig->ePanelType) ||
           (MDPPLATFORM_PANEL_MAX    <= psOverrideParam->pPanelConfig->ePanelType))
  {
    LocalAsciiStrnCat(*ppStr, PANEL_CONFIG_STR_LEN_MAX, (CHAR8 *)psOverrideParam->shortName);
  }
  else
  {
    /* Update panel attribute for PP Split info */
    if(DISP_MODE_PING_PONG_SPLIT & psOverrideParam->uSelectedModeFlags)
    {
      MDP_Panel_AttrType *pDisplayInfo = MDP_GET_DISPLAYINFO(eDisplayId);
      pDisplayInfo->eDisplayFlags |= MDP_PANEL_FLAG_ENABLE_PINGPONG_SPLIT;
    }

    MDP_OSAL_MEMZERO(DTLabel, sizeof(DTLabel));
    uShortNameLen = AsciiStrLen(psOverrideParam->shortName);
    uTopology     = (uint32)psOverrideParam->eTopologyCfg;

    /* Decide how to construct the DTLabel */
    if (MDPPLATFORM_PANEL_PHYSICAL == psOverrideParam->pPanelConfig->ePanelType)
    {
      LocalAsciiStrnCat(DTLabel, DISPLAY_PANEL_DT_LABEL_MAX_LEN, (CHAR8 *)psOverrideParam->pPanelConfig->pPhysicalPanelConfig->DTLabel);
    }
    else if (MDPPLATFORM_PANEL_SIMULATION == psOverrideParam->pPanelConfig->ePanelType)
    {
      LocalAsciiStrnCat(DTLabel, DISPLAY_PANEL_DT_LABEL_MAX_LEN, (CHAR8 *)psOverrideParam->pPanelConfig->sSimPanelConfig.DTLabel);
    }

    if(uShortNameLen > 0)
    {
      CHAR8 *pDisplayCmdLine;
      uTiming = (uint32)psOverrideParam->eTimingCfg;

      if (MDP_DISPLAY_PRIMARY == eDisplayId)
      {
        pDisplayCmdLine = DISPLAY_CMDLINE_DSI_PRIMARY;
      }
      else
      {
        pDisplayCmdLine = DISPLAY_CMDLINE_DSI_SECONDARY;
      }

      LocalAsciiStrnCat(*ppStr, PANEL_CONFIG_STR_LEN_MAX, pDisplayCmdLine);
      (*ppStr) += AsciiStrLen(pDisplayCmdLine);

      LocalAsciiStrnCat(*ppStr, PANEL_CONFIG_STR_LEN_MAX, (CHAR8 *)DTLabel);
      (*ppStr) += AsciiStrLen(DTLabel);

      if (MDPPLATFORM_PANEL_PHYSICAL == psOverrideParam->pPanelConfig->ePanelType)
      {
        if (uTopology)
        {
          LocalAsciiStrnCat(*ppStr, PANEL_CONFIG_STR_LEN_MAX, "config");
          (*ppStr) += 6;
          **ppStr   = uTopology - 1 + '0';
          (*ppStr) += 1;
          **ppStr   = '\0';
        }

        if (uTiming)
        {
          LocalAsciiStrnCat(*ppStr, PANEL_CONFIG_STR_LEN_MAX, ":timing");
          (*ppStr) += 7;
          **ppStr = uTiming - 1 + '0';
          (*ppStr) += 1;
          **ppStr = '\0';
        }
      }
      else if (MDPPLATFORM_PANEL_SIMULATION == psOverrideParam->pPanelConfig->ePanelType)
      {
        LocalAsciiStrnCat(*ppStr, PANEL_CONFIG_STR_LEN_MAX, psOverrideParam->pPanelConfig->sSimPanelConfig.szKernelModeInfo);
      }
    }
  }
}


/****************************************************************************
*
** FUNCTION: UpdatePanelConfiguration()
*/
/*!
* \brief
*   Helper to build panel configuration string
*
* \param [in]  eDisplayId            - Display id
*        [out] pConfigStr            - Panel configuration string
*
* \retval None
*
****************************************************************************/
static void UpdatePanelConfiguration(MDP_Display_IDType eDisplayId, CHAR8 *pConfigStr)
{
  Display_UtilsContextType  *pDisplayContext = GET_DISPLAY_CONTEXT();
  Display_UtilsParamsType   *pDisplayParams  = &pDisplayContext->sDisplayParams;
  CHAR8                     *pSimModeStr     = NULL;

  /* Get updated display params */
  UpdateDisplayParams(eDisplayId);

  if (DISP_MODE_PANEL_NONE & pDisplayParams->uFlags)
  {
    /* Panel override with NONE, no string will be generated */
  }
  else
  {
    CHAR8 *pStr = pConfigStr;

    /*
     * Don't make change to pConfigStr
     * instead of have pStr move to end of string after every panelConfigOutput() called.
     */
    if (MDP_DISPLAY_PRIMARY == eDisplayId)
    {
      panelConfigOutput(MDP_DISPLAY_PRIMARY,   &pDisplayParams->sPrimary,   &pStr);
    }
    else if (MDP_DISPLAY_SECONDARY == eDisplayId)
    {
      panelConfigOutput(MDP_DISPLAY_SECONDARY, &pDisplayParams->sSecondary, &pStr);
    }

    switch(pDisplayParams->eSimMode)
    {
    case PANELSIM_MODE:
      pSimModeStr = SIM_MODE_STRING;
      break;
    case PANELSIM_HWTE:
      pSimModeStr = SIM_HWTE_STRING;
      break;
    case PANELSIM_SWTE:
      pSimModeStr = SIM_SWTE_STRING;
      break;
    case PANELSIM_NONE:
    default:
      pSimModeStr = NULL;
      break;
    }

    if (NULL != pSimModeStr)
    {
      LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, SIM_OVERRIDE);
      LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, pSimModeStr);
    }
  }
}

/****************************************************************************
*
** FUNCTION: CheckPanelOverride()
*/
/*!
* \brief
*   Helper function to check if panel override is set and parse the override
*   string, if set.
*
* \param  None
*
* \retval None
*
****************************************************************************/
static void CheckPanelOverride(bool32 (*pSupportedDisplayList)[])
{

  Display_UtilsContextType *pDisplayContext   = GET_DISPLAY_CONTEXT();
  UINTN                     uLength           = 0;
  CHAR8                     panelOverrideStr[PANEL_OVERRIDE_STR_LEN_MAX];

  MDP_OSAL_MEMZERO(panelOverrideStr, sizeof(panelOverrideStr));
  uLength = PANEL_OVERRIDE_STR_LEN_MAX;

  /* Check Panel Override
  */
  if (MDP_STATUS_OK == MDP_Display_GetVariable(DISPVAR_PANEL_OVERRIDE, (UINT8 *)panelOverrideStr, &uLength, 0))
  {
    /* Parse String - Since this is an override scenario print the command to log*/
    DEBUG((EFI_D_ERROR, "DisplayUtils: Panel override command: <%a>\n", panelOverrideStr));

    /*Panel override string */
    pDisplayContext->bOverride  = ParsePanelOverrideCommand(pSupportedDisplayList, panelOverrideStr, &pDisplayContext->sDisplayParams);
  }
}


/****************************************************************************
*
** FUNCTION: ConversionPixelCopy()
*/
/*!
* \brief
*   Helper function to Convert a source 24bpp image to 32bpp with a dynamically
*   allocated buffer.
*
* \param[in]  SourceBitDepth    Source image bit depth
*       [in]  ColorMap          Pointer to BMP indexed color map table
*       [in]  SourceBuffer      Source image buffer
*       [in]  DestBitDepth      Destination image bit depth
*       [in]  DestBuffer        Destination image buffer
*       [in]  NumPixels         Number of pixels to process
*
* \retval None
*
****************************************************************************/
static
VOID
ConversionPixelCopy(
    IN UINT32     SourceBitDepth,
    IN VOID      *ColorMap,
    IN UINT8     *SourceBuffer,
    IN UINT32     DestBitDepth,
    IN UINT8     *DestBuffer,
    IN UINT32     NumPixels)
{

  // Check for valid input parameters
  if (SourceBitDepth == DestBitDepth)
  {
    CopyMem(DestBuffer, SourceBuffer, NumPixels*(SourceBitDepth/8));
  }
  else if ((24 == SourceBitDepth) && (32 == DestBitDepth))
  {
    UINT32  Count;
    UINT32 *Buffer32BPP = (UINT32*)DestBuffer;
    UINT8  *Buffer24BPP = (UINT8*)SourceBuffer;

    for (Count=0;Count<NumPixels;Count++)
    {
       Buffer32BPP[Count] = (UINT32) (0x00000000 | (Buffer24BPP[2]<<16) | (Buffer24BPP[1]<<8) | (Buffer24BPP[0]));

       // Increment to the next pixel
       Buffer24BPP+=3;
    }
  }
  else if ((8 == SourceBitDepth) && (32 == DestBitDepth))
  {
    UINT32  Count;
    UINT32 *Buffer32BPP = (UINT32*)DestBuffer;
    UINT8  *Buffer8BPP  = (UINT8*)SourceBuffer;

    for (Count=0;Count<NumPixels;Count++)
    {
       UINT8          uIndex = *Buffer8BPP;
       BMP_COLOR_MAP *pColor = (BMP_COLOR_MAP*)ColorMap;

       Buffer32BPP[Count] = (UINT32) (0x00000000 | (pColor[uIndex].Red<<16) | (pColor[uIndex].Green<<8) | (pColor[uIndex].Blue));

       // Increment to the next pixel
       Buffer8BPP+=1;
    }
  }
  else
  {
    // All other conversion are not supported, fill with an solid color (gray)
    UINT32  Count;
    UINT32 *Buffer8BPP = (UINT32*)DestBuffer;

    for (Count=0;Count<NumPixels*(DestBitDepth/8);Count++)
    {
        Buffer8BPP[Count] = 0x5A;
    }
  }
}

/****************************************************************************
*
** FUNCTION: RotatePixel32Copy()
*/
/*!
* \brief
*   Helper function to Convert a source 24bpp image to 32bpp with a dynamically
*   allocated buffer.
*
* \param[in]  SourceBuffer      Source image buffer
*       [in]  DestBuffer        Destination image buffer
*       [in]  ImageWidth        Source image width
*       [in]  ImageHeight       Source image height
*       [in]  eBGRTRotation     BRGT rotation
*
* \retval None
*
****************************************************************************/
static VOID RotatePixel32Copy(
    IN UINT32               *SourceBuffer,
    IN UINT32               *DestBuffer,
    IN UINT32                ImageWidth,
    IN UINT32                ImageHeight,
    IN DispBGRTRotationType  eBGRTRotation)
{
  for (uint32 y = 0; y < ImageHeight; y++)
  {
    for (uint32 x = 0; x < ImageWidth; x++)
    {
      switch (eBGRTRotation)
      {
        case DISP_BGRT_ROTATION_90:
        {
          DestBuffer[x * ImageHeight + (ImageHeight - y - 1)]                   = SourceBuffer[y * ImageWidth + x];
          break;
        }
        case DISP_BGRT_ROTATION_180:
        {
          DestBuffer[(ImageHeight - y - 1) * ImageWidth + (ImageWidth - x - 1)] = SourceBuffer[y * ImageWidth + x];
          break;
        }
        case DISP_BGRT_ROTATION_270:
        {
          DestBuffer[(ImageWidth - x - 1) * ImageHeight + y]                    = SourceBuffer[y * ImageWidth + x];
          break;
        }
        default:
        {
          DestBuffer[y * ImageWidth + x]                                        = SourceBuffer[y * ImageWidth + x];
          break;
        }
      }
    }
  }
}
/****************************************************************************
*
** FUNCTION: ConversionPixelRotateCopy()
*/
/*!
* \brief
*   Helper function to Convert a source 8/24bpp image to 32bpp with a dynamically
*   allocated buffer, and perform 0/90/180/270 degree rotation.
*
* \param[in]  SourceBitDepth    Source image bit depth
*       [in]  ColorMap          Pointer to BMP indexed color map table
*       [in]  SourceBuffer      Source image buffer
*       [in]  DestBitDepth      Destination image bit depth
*       [in]  DestBuffer        Destination image buffer
*       [in]  ImageWidth        Image Width
*       [in]  ImageHeight       Image Height
*       [in]  SrcStride         Source image stride, it could be negative to indicate the inverted row order.
*       [in]  eBGRTRotation     Image rotation degree
*
* \retval None
*
****************************************************************************/
static
VOID
ConversionPixelRotateCopy(
    IN UINT32                  SourceBitDepth,
    IN VOID                   *ColorMap,
    IN UINT8                  *SourceBuffer,
    IN UINT32                  DestBitDepth,
    IN UINT32                 *DestBuffer,
    IN UINT32                  ImageWidth,
    IN UINT32                  ImageHeight,
    IN INT32                   SrcStride,
    IN DispBGRTRotationType    eBGRTRotation)
{

  if (32 != DestBitDepth)
  {
    DEBUG((EFI_D_WARN, "ConversionPixelRotateCopy: (%d) Destnation bitdepth is not supported.", DestBitDepth));
    MDP_OSAL_MEMSET(DestBuffer, 0x5A, ImageWidth * ImageHeight * DestBitDepth / 8);
  }
  else
  {
    bool32  bVerticalInvert = ((DISP_BGRT_ROTATION_90  == eBGRTRotation) ||
                               (DISP_BGRT_ROTATION_180 == eBGRTRotation)) ? TRUE : FALSE;

    for (uint32 y = 0; y < ImageHeight; y++)
    {
      uint32  uVerticalPos = (bVerticalInvert == (SrcStride > 0)) ? y : (ImageHeight - y - 1);
      UINT32 *Buffer32     = (UINT32*)SourceBuffer;
      UINT8  *Buffer8      = (UINT8*)SourceBuffer;

      for (uint32 x = 0; x < ImageWidth; x++)
      {
        uint32  uSrcPixel = 0;

        // Fetch the source image pixels and convert to XRGB8888.
        switch (SourceBitDepth)
        {
          case 32:
          {
            uSrcPixel = Buffer32[x];
            break;
          }
          case 24:
          {
            uSrcPixel = (UINT32)((Buffer8[2] << 16) | (Buffer8[1] << 8) | (Buffer8[0]));
            
            // Increment to the next pixel
            Buffer8 += 3;
            break;
          }
          case 8:
          {
            uint8 uIndex          = *Buffer8;
            BMP_COLOR_MAP* pColor = (BMP_COLOR_MAP*)ColorMap;

            uSrcPixel = (UINT32)((pColor[uIndex].Red << 16) | (pColor[uIndex].Green << 8) | (pColor[uIndex].Blue));
            
            // Increment to the next pixel
            Buffer8 += 1;
            break;
          }
          default:
          {
            // All other conversion are not supported, fill with an solid color (gray)
            uSrcPixel = 0x5A5A5A5A;
            break;
          }
        }

        //Store pixel data to rotated position of destination image 
        switch (eBGRTRotation)
        {
          case DISP_BGRT_ROTATION_90:
          {
            DestBuffer[x * ImageHeight + uVerticalPos]                    = uSrcPixel;
            break;
          }
          case DISP_BGRT_ROTATION_180:
          {
            DestBuffer[uVerticalPos * ImageWidth + (ImageWidth - x - 1)]  = uSrcPixel;
            break;
          }
          case DISP_BGRT_ROTATION_270:
          {
            DestBuffer[(ImageWidth - x - 1) * ImageHeight + uVerticalPos] = uSrcPixel;
            break;
          }         
          case DISP_BGRT_ROTATION_NONE:
          default:
          {
            DestBuffer[uVerticalPos * ImageWidth + x]                     = uSrcPixel;
            break;
          }
        }
      }

      SourceBuffer += SrcStride;
    }
  }

}


/****************************************************************************
*
** FUNCTION: CalculateLogoPosition()
*/
/*!
* \brief
*   Helper function to Calculate the x,y position of the logo based on logo size,
*   screen size and placement rules.
*
* \param[in]   LogoWidth             Logo width in pixels
*       [in]   LogoHeight            Logo height in pixels
*       [out]  pPosX                 Horizontal placement of logo top left corder
*       [out]  pPoxY                 Vertical placement of logo top left corder
*       [in]   pRenderLogoParams     Render logo parameters
*
* \retval None
*
****************************************************************************/
static
VOID
CalculateLogoPosition(
    IN  UINT32                LogoWidth,
    IN  UINT32                LogoHeight,
    OUT UINT32               *pPosX,
    OUT UINT32               *pPosY,
    RenderLogoParamsType     *pRenderLogoParams)
{
  if (NULL == pRenderLogoParams)
  {
    DEBUG((EFI_D_WARN, "CalculateLogoPosition: Invalid inputs of pRenderLogoParams.\r\n"));
  }
  else if ((NULL == pPosX) ||
           (NULL == pPosY))
  {
    DEBUG((EFI_D_WARN, "CalculateLogoPosition: Invalid inputs of pPos and resolution.\r\n"));
  }
  else
  {
    MDP_Panel_AttrType  *pDisplayInfo = MDP_GET_DISPLAYINFO(pRenderLogoParams->eDisplayId);
    UINT32               PanelWidth   = pDisplayInfo->sFrameBuffer.uWidth;
    UINT32               PanelHeight  = pDisplayInfo->sFrameBuffer.uHeight;
    INT32                LogoPosX     = 0;
    INT32                LogoPosY     = 0;

    if (pRenderLogoParams->uFlags &  RENDER_LOGO_POSITION_OVERRIDE)
    {
      LogoPosX = pRenderLogoParams->uXPosition;
      LogoPosY = pRenderLogoParams->uYPosition;
    }
    else
    {
      // Calculate LogoPosX and LogoPosY based on platform panel resolution.
      switch (pRenderLogoParams->eBGRTRotation)
      {
        case DISP_BGRT_ROTATION_90:
        {
          // Center of BGRT image should be at 38.2 percent of panel width from the right as logo is rotated 90 CW
          if (PanelWidth > LogoWidth)
          {
            LogoPosX = (BGRT_INVERT_POSITION_RATIO * PanelWidth) - (UINT32)(LogoHeight / 2);
          }

          // Center of BGRT image should be at the vertical center of the panel as logo is rotated 90 CW.
          if (PanelHeight > LogoHeight)
          {
            LogoPosY = (PanelHeight - LogoWidth) / 2;
          }
          break;
        }
        case DISP_BGRT_ROTATION_180:
        {
          // Center of BGRT image should be at the horizontal center of the panel as logo is rotated 180
          if (PanelWidth > LogoWidth)
          {
            LogoPosX = (PanelWidth - LogoWidth) / 2;
          }

          // Center of BGRT image should be at 38.2 percent of panel height from the bottom as logo is rotated 180 CW.
          if (PanelHeight > LogoHeight)
          {
            LogoPosY = (BGRT_INVERT_POSITION_RATIO * PanelHeight) - (UINT32)(LogoHeight / 2);
          }
          break;
        }
        case DISP_BGRT_ROTATION_270:
        {
          // Center of BGRT image should be at 38.2 percent of panel height from the left as logo is rotated 270 CW
          if (PanelWidth > LogoWidth)
          {
            LogoPosX = (BGRT_NORMAL_POSITION_RATIO * PanelWidth) - (UINT32)(LogoHeight / 2);
          }

          // Center of BGRT image should be at the vertical center of the panel as logo is rotated 270 CW.
          if (PanelHeight > LogoHeight)
          {
            LogoPosY = (PanelHeight - LogoWidth) / 2;
          }
          break;
        }
        case DISP_BGRT_ROTATION_NONE:
        default:
        {
          // Center of BGRT image should be at the horizontal center of the panel.
          if (PanelWidth > LogoWidth)
          {
            LogoPosX = (PanelWidth - LogoWidth) / 2;
          }

          // Center of BGRT image should be at 38.2 percent of panel height from the top.
          if (PanelHeight > LogoHeight)
          {
            LogoPosY = (BGRT_NORMAL_POSITION_RATIO * PanelHeight) - (UINT32)(LogoHeight / 2);
          }
          break;
        }
      }
    }

    // If LogoPosX and LogoPosY does not have valid values, set them to (0,0)
    if ((LogoPosX         < 0)              ||
        (LogoPosY         < 0)              ||
        ((UINT32)LogoPosX > (PanelWidth-1)) ||
        ((UINT32)LogoPosY > (PanelHeight-1)))
    {
      LogoPosX = 0;
      LogoPosY = 0;
    }

    // Update the image offsets
    *pPosX = (UINT32)LogoPosX;
    *pPosY = (UINT32)LogoPosY;
  }
}

/****************************************************************************
*
** FUNCTION: Display_Utils_SavePLLCodes()
*/
/*!
* \brief
*   Helper function to store pll codes data to boot service variable
*
* \param [in]  pVariableName    - Service variable name that will save to
*        [in]  pPllCodesIDEntry - Points to pll codes data array that needs be saved
*        [in]  uNumEntries      - Array length of the arrry pPllCodesIDEntry points to
*
* \retval EFI_STATUS
*
****************************************************************************/
static EFI_STATUS Display_Utils_SavePLLCodes(CHAR16 *pVariableName, MDP_PLLCodesIDEntryInfo *pPllCodesIDEntry, UINT32 uNumEntries)
{
  EFI_STATUS eStatus = EFI_SUCCESS;
  
  if ((NULL == pPllCodesIDEntry) ||
      (NULL == pVariableName))
  {
    eStatus = EFI_INVALID_PARAMETER;
  }
  else
  {
    MDP_DisplayPllCodesInfoType  *pPLLCodes        = NULL;
    UINT32                        uEntryCount      = 0;
    UINT32                        uTotalSize       = 0;
    UINT32                        i;

    /* Save up to what we can store */
    if (uNumEntries >= MDP_DISPLAY_PLL_CODEID_MAX)
    {
      uNumEntries = MDP_DISPLAY_PLL_CODEID_MAX - 1;
    }

    /* Calculate total entry count for all devices */
    for (i = 0 ; i < uNumEntries; i++)
    {
      uEntryCount += pPllCodesIDEntry[i].sPllCodesInfo.uRefreshRateCount;
    }

    uTotalSize = (uEntryCount * sizeof (MDP_DisplayPllCodeEntryType)) + sizeof(MDP_DisplayPllCodesHeaderType);

    pPLLCodes = (MDP_DisplayPllCodesInfoType*) MDP_OSAL_CALLOC(uTotalSize);

    if (NULL == pPLLCodes)
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "Display_Utils_SavePLLCodes: fail to alloc memory for pll codes\n");
      eStatus = EFI_INVALID_PARAMETER;
    }
    else
    {
      MDP_DisplayPllCodeEntryType *pEntry = (MDP_DisplayPllCodeEntryType*)&pPLLCodes->pCodeData;

      for (i = 0; i < uNumEntries; i++)
      {
        UINT32            j;
        MDP_PLLCodesInfo *pPllCodesInfo = (MDP_PLLCodesInfo *)&pPllCodesIDEntry[i].sPllCodesInfo;

        for (j = 0; j < pPllCodesInfo->uRefreshRateCount; j++)
        {
          UINT32 k;

          pEntry->uDeviceID = pPllCodesIDEntry[i].uDeviceID;
          pEntry->uVCORate  = pPllCodesInfo->sPllCodes[j].uVcoRate;
          pEntry->uNumCodes = MDP_PLL_CODES_NUM_PER_FREQ;

          for (k = 0; k < pEntry->uNumCodes; k++)
          {
            pEntry->uPLLCode[k] = pPllCodesInfo->sPllCodes[j].uPllCodes[k];
          }

          pEntry++;
        }
      }

      pPLLCodes->sHeader.uMagicID =  MDP_PLL_CODE_MAGIC_ID;
      pPLLCodes->sHeader.uVersion =  MDP_PLL_CODE_VERSION;
      pPLLCodes->sHeader.uEntries =  uEntryCount;
      pPLLCodes->sHeader.uSize    =  uTotalSize;

      eStatus = MDP_SetBootServiceVariable(pVariableName, (void*)pPLLCodes, pPLLCodes->sHeader.uSize, 0);

      MDP_OSAL_FREE(pPLLCodes);
    }
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: LogDisplayPanelConfig()
*/
/*!
* \brief
*   Function to log display registers and store result as txt file in
*   imagefv_b partition
*
* \retval EFI_STATUS
*
****************************************************************************/
static EFI_STATUS LogDisplayPanelConfig(void)
{
    EFI_STATUS          eStatus          = EFI_SUCCESS;
    MDP_Display_IDType  eDisplayId;
    MDPPlatformParams   sPlatformParams;

    for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_SECONDARY; eDisplayId++)
    {
      if ((FALSE == MDP_SUPPORTED_DISPLAY(eDisplayId)) ||
          (TRUE  == Display_Utils_IsDisplayDisabled(eDisplayId)))
      {
        continue;
      }

      MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));

      if (EFI_SUCCESS != (eStatus = MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_GETPANELXMLINFO, &sPlatformParams)))
      {
          MDP_Log_Message(MDP_LOGLEVEL_WARN, "LogDisplayPanelConfig: Fail to get panel xml file\n");
      }
      else
      {
        CHAR16 PanelConfig[DISP_FILE_NAME_MAX_SIZE];
        CHAR8  aAsciiPanelconfig[DISP_FILE_NAME_MAX_SIZE];

        snprintf(aAsciiPanelconfig, DISP_FILE_NAME_MAX_SIZE, "%s%d.txt", DISP_PANEL_CONFIG_PREFIX_ASCII, eDisplayId);
        AsciiStrToUnicodeStrS(aAsciiPanelconfig, PanelConfig, DISP_FILE_NAME_MAX_SIZE);

        eStatus = MDP_Display_WriteTextFile(DISP_CONFIG_PART_NAME, PanelConfig, (UINT8*)sPlatformParams.sPanelXMLInfo.pPanelXMLConfig, sPlatformParams.sPanelXMLInfo.uPanelXMLSize, 0);
      }
    }

    return eStatus;
}

/****************************************************************************
*
** FUNCTION: LogDisplayCmdline()
*/
/*!
* \brief
*   Function to log display command line and store result as txt file
*   in imagefv_b partition
*
* \retval EFI_STATUS
*
****************************************************************************/
static EFI_STATUS LogDisplayCmdline(void)
{
    EFI_STATUS          eStatus          = EFI_SUCCESS;
    MDP_Display_IDType  eDisplayId;
    CHAR8               szCmdline[PANEL_CONFIG_STR_LEN_MAX];

    MDP_OSAL_MEMZERO(szCmdline, sizeof(szCmdline));

    for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_EXTERNAL; eDisplayId++)
    {
      if ((FALSE == MDP_SUPPORTED_DISPLAY(eDisplayId)) ||
          (TRUE  == Display_Utils_IsDisplayDisabled(eDisplayId)))
      {
        continue;
      }

      UpdatePanelConfiguration(eDisplayId, szCmdline);
    }

    eStatus = MDP_Display_WriteTextFile(DISP_CONFIG_PART_NAME, DISP_DSI_CMDLINE_FILE, (UINT8*)szCmdline, AsciiStrLen(szCmdline), 0);

    return eStatus;
}

/****************************************************************************
*
** FUNCTION: LogDisplayRegs()
*/
/*!
* \brief
*   Function to log specified display registers and store result as txt file
*   in imagefv_b partition
*
* \retval EFI_STATUS
*
****************************************************************************/
static EFI_STATUS LogDisplayRegs(void)
{
  EFI_STATUS  eStatus           = EFI_SUCCESS;
  UINT8      *pWriteFileBuf     = NULL;
  UINT8      *pReadFileBuf      = NULL;
  UINTN       uFileSize         = 0;

  if (EFI_SUCCESS != MDP_Display_ReadConfigFile(DISP_CONFIG_PART_NAME, DISP_REGS_FILE, &pReadFileBuf, &uFileSize, 0))
  {
    DEBUG((EFI_D_WARN, "LogDisplayRegs: Read %s failed\n", DISP_REGS_FILE));
  }
  else if (NULL == (pWriteFileBuf = (UINT8*)MDP_OSAL_CALLOC(DISP_LOG_REG_OUT_FILE_MAX_SIZE)))
  {
    eStatus = EFI_UNSUPPORTED;
    DEBUG((EFI_D_WARN, "LogDisplayRegs: Fail to allocate memory\n"));
  }
  else
  {
    CHAR8  *pTmp0;
    CHAR8  *pTmp1;
    UINTN   uRegAddr             = 0;
    UINT32  uRegVal              = 0;
    UINTN   uWriteFileBufSize    = 0;
    UINTN   uWriteCount          = 0;
    INTN    iAvailableSize       = DISP_LOG_REG_OUT_FILE_MAX_SIZE;
    CHAR8  *pLine                = (CHAR8*)strtok_r((CHAR8*)pReadFileBuf, "\n", &pTmp0);

    while((NULL           != pLine) &&
          (iAvailableSize >= DISP_LOG_REG_OUT_LINE_MIN_SIZE))
    {
      /* Incase of the line is already a addr:val pair, only take the addr here */
      if (NULL != (pTmp1 = AsciiStrStr(pLine, ":")))
      {
        *pTmp1 = '\0';
      }

      uRegAddr = AsciiStrHexToUintn(pLine);

      if (HAL_MDSS_STATUS_SUCCESS == HAL_MDSS_ReadRegister(uRegAddr, &uRegVal))
      {
        uRegVal           =  *(UINTN *)uRegAddr;
        uWriteCount       =  snprintf((char*)&pWriteFileBuf[uWriteFileBufSize], iAvailableSize, "0x%08x: %08x\n", uRegAddr, uRegVal);
        uWriteFileBufSize += uWriteCount;
        iAvailableSize    -= uWriteCount;
      }

      pLine = (CHAR8*)strtok_r(NULL, "\n", &pTmp0);
    }

    eStatus = MDP_Display_WriteTextFile(DISP_CONFIG_PART_NAME, DISP_REGS_FILE, pWriteFileBuf, uWriteFileBufSize, 0);
  }

  if (pWriteFileBuf != NULL)
  {
    MDP_OSAL_FREE(pWriteFileBuf);
  }

  if (pReadFileBuf != NULL)
  {
     MDP_OSAL_FREE(pReadFileBuf);
  }

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: Display_Utils_LogSettings()
*/
/*!
* \brief
*   Display Utils to log display information to FAT16 partition
*
* \retval None
*
****************************************************************************/
void Display_Utils_LogSettings()
{
  if (FALSE == MDPClockStatus(MDP_CLOCKTYPE_CORE))
  {
    DEBUG ((EFI_D_WARN, "Display_Utils_LogSettings: MDP core clock not enabled, no display log will be captured\n"));
  }
  else
  {
    CHAR8   aLogEnableVariable[PANEL_OVERRIDE_STR_LEN_MAX];
    UINTN   uLogEnableVariableSize = sizeof(aLogEnableVariable);

    /* Check whether display log is enabled */
    if ((MDP_STATUS_OK  == MDP_GetBootServiceVariable(DISPVAR_LOG_ENABLE, aLogEnableVariable, &uLogEnableVariableSize)) &&
         (0             != uLogEnableVariableSize) &&
         (0             == AsciiStrnCmp(aLogEnableVariable, DISP_ENABLE_LOG, AsciiStrLen(DISP_ENABLE_LOG))))
    {
      MDP_Display_IDType   eDisplayId;
      MDP_Panel_AttrType  *pDisplayInfo = NULL;

      /* If dump enabled, disable continuous splash so UEFI won't affect kernel side registers */
      for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_EXTERNAL; eDisplayId++)
      {
        if ((FALSE == MDP_SUPPORTED_DISPLAY(eDisplayId)) ||
            (TRUE  == Display_Utils_IsDisplayDisabled(eDisplayId)))
        {
          continue;
        }

        pDisplayInfo = MDP_GET_DISPLAYINFO(eDisplayId);
        pDisplayInfo->eDisplayFlags |= MDP_PANEL_FLAG_DISABLE_SEAMLESS_SPLASH;
      }

      if (MDP_STATUS_OK != LogDisplayRegs())
      {
        DEBUG ((EFI_D_WARN, "Display_Utils_LogSettings: Fail to log display registers\n"));
      }

      if (MDP_STATUS_OK != LogDisplayPanelConfig())
      {
        DEBUG ((EFI_D_WARN, "Display_Utils_LogSettings: Fail to log display panel config\n"));
      }

      if (MDP_STATUS_OK != LogDisplayCmdline())
      {
        DEBUG ((EFI_D_WARN, "Display_Utils_LogSettings: Fail to log display command line\n"));
      }
    }
  }
}

/****************************************************************************
*
** FUNCTION: Display_Utils_LoadFile()
*/
/*!
* \brief
*   Helper function to read a file from the GPP partition in to a caller
*   specified buffer.
*
* \param[in]       FileName     Filename including path in ascii.
*       [in][out]  Buffer       Pointer to a pointer to a buffer allocated by the caller.
*                               If buffer is NULL or smaller in size than required,
*                               then dynamically allocate buffer.
*       [in][out]  BufferSize   If input buffer is provided, then BufferSize indicates the size
*                               of callers buffer in bytes.
*                               If input buffer is null or buffersize is smaller than the filesize,
*                               size of a newly allocated buffer is stored here.
*       [out]      RetSize      The returned size of the image file that has been loaded in to memory.
*       [in]       eFlags       Flags to load file.
*
* \retval EFI_STATUS
* EFI_SUCCESS                 : Function returned successfully.
* EFI_SUCCESS                 : Image loaded successfully in to memory.
* EFI_INVALID_PARAMETER       : Invalid input parameters passed in
* EFI_OUT_OF_RESOURCES        : Input buffer is too small to hold the incoming image and dynamic allocation
*                               for a bigger memory failed.
*
****************************************************************************/
EFI_STATUS
Display_Utils_LoadFile(
    IN      CHAR8                   *FileName,
    IN OUT  UINT8                  **Buffer,
    IN OUT  UINT32                  *BufferSize,
    OUT     UINT32                  *RetSize,
    IN      DisplayLoadFileFlags     eFlags)
{
  EFI_STATUS  Status = EFI_SUCCESS;

  Status = MDP_Display_LoadFile(FileName, Buffer, BufferSize, RetSize, eFlags);

  return Status;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: GetUpdatedCmdLine()
**
** DESCRIPTION:
**   Append the display command line to the existing command line
**
** ---------------------------------------------------------------------- */
static bool32 GetUpdatedCmdLine(CHAR8* pOrig, uint32 uOrigSize, CHAR8 **ppUpdatedStr, int *piUpdatedSize)
{

  CHAR8 *pCmdLine = NULL;
  UINT32 uLen     = 0;
  UINT32 uSize    = 0;
  bool32 bUpdate  = FALSE;
  CHAR8* pStr     = NULL;

  /* Get the display command line */
  Display_Utils_GetDisplayCommandLine(&pCmdLine, &uLen);

  /* calculate size including termination*/
  uSize = sizeof(CHAR8) * (uLen + 1);

  if ((NULL == pCmdLine) ||
      (0 == uLen))
  {
    /* No panel configuration available */
  }
  else if (NULL == (pStr = MDP_OSAL_CALLOC(uOrigSize + uSize)))
  {
    DEBUG ((EFI_D_ERROR, "Display: Failed to allocate memory for display command line\n"));
  }
  /* Replace null termination with space */
  else
  {
    /* uOrigSize is checked for zero in the calling function */
    UINT32 uOrigLen = uOrigSize - sizeof(CHAR8);

    /* Copy original string - without termination character*/
    MDP_OSAL_MEMCPY(pStr, pOrig, uOrigLen * sizeof(CHAR8));

    /* space to separate */
    pStr[uOrigLen] = ' ';

    /* copy display command line - has termination at end*/
    MDP_OSAL_MEMCPY(&pStr[uOrigLen + 1], pCmdLine, uSize);

    /* Return updated data & size */
    *ppUpdatedStr = pStr;
    *piUpdatedSize = (int) uOrigSize + uSize;

    /* Flag property update */
    bUpdate = TRUE;
  }

  return bUpdate;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: UpdateDisplayCmdLine()
**
** DESCRIPTION:
**   Update the display command line in the device tree node
**
** ---------------------------------------------------------------------- */
static void UpdateDisplayCmdLine(void *pFdt)
{
  int           iRet     = 0;
  const CHAR8  *pOrigStr = NULL;
  CHAR8        *pNewStr  = NULL;
  int           iOrigSize= 0;
  int           iNewSize = 0;
  int           iOffset;

  /* Get offset of the chosen node */
  if (0 > (iOffset = fdt_path_offset(pFdt, "/chosen")))
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Could not find chosen node ...\n"));
  }
  else if ((NULL == (pOrigStr = (const CHAR8*) fdt_getprop(pFdt, iOffset, (CONST char*)"bootargs", &iOrigSize))) ||
           (iOrigSize <= 0 ))
  {
    DEBUG ((EFI_D_ERROR, "Display: Could not get bootargs from device tree\n"));
  }
  else if (FALSE == GetUpdatedCmdLine((CHAR8*) pOrigStr, iOrigSize, &pNewStr, &iNewSize))
  {
    /* Nothing to update - Ignore and quit */
  }
  /* Set property */
  else if (0 != (iRet = fdt_setprop(pFdt, iOffset, (const char*)"bootargs", (const void*)pNewStr, iNewSize)))
  {
    DEBUG ((EFI_D_ERROR, "Display: Failed to update display command line on device tree. Return code: %d\n", iRet));
  }

  /* Free memory if allocated */
  if (NULL != pNewStr)
  {
    MDP_OSAL_FREE(pNewStr);
  }
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: UpdateSplashNode()
**
** DESCRIPTION:
**   Update the continuous splash device tree node
**
** ---------------------------------------------------------------------- */
static void UpdateSplashNode(void *pFdt)
{
  CONST struct fdt_property  *pProperty     = NULL;
  int                         iPropertySize = 0;
  int                         iRet          = 0;
  int                         iOffset;

  /* Get offset of the splash memory reservation node */
  if (0 > (iOffset = fdt_path_offset(pFdt, SPLASH_MEM_DT_NODE_NAME)))
  {
    DEBUG ((EFI_D_ERROR, "Display: Could not get splash memory region node\n"));
  }
  /* Get the property that specifies the splash memory details */
  else if (0 == (pProperty = fdt_get_property(pFdt, iOffset, SPLASH_MEM_DT_REG, &iPropertySize)))
  {
    DEBUG ((EFI_D_ERROR, "Display: Could not find the splash reg property\n"));
  }
  else if (iPropertySize != SPLASH_MEM_PROP_SIZE)
  {
    DEBUG ((EFI_D_ERROR, "Display: Splash memory node size mismatch in device tree. Expected: %d, Actual: %d\n",
            SPLASH_MEM_PROP_SIZE, iPropertySize));
  }
  else
  {
    UINT32* pData = (UINT32*) pProperty->data;
    UINT32  uAddr = 0;
    UINT32  uSize = 0;

    /* Get splash buffer info */
    Display_Utils_GetContinuousSplashInfo(&uAddr, &uSize);

    pData[0] = 0;
    pData[1] = cpu_to_fdt32(uAddr);
    pData[2] = 0;
    pData[3] = cpu_to_fdt32(uSize);

    /* Update the property value in place */
    if (0 > (iRet = fdt_setprop_inplace(pFdt, iOffset, SPLASH_MEM_DT_REG, pProperty->data, iPropertySize)))
    {
      DEBUG ((EFI_D_ERROR, "Display: Could not update splash mem device tree node\n"));
    }
  }
}

/****************************************************************************
*
** FUNCTION: UpdateDeviceTree()
*/
/*!
* \brief
*   Update display specific devicee tree nodes
*
* \param [in] pFdt         - Device tree address
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS UpdateDeviceTree(void *pFdt)
{
  EFI_STATUS                  eStatus       = EFI_NOT_FOUND;
  int                         iRet           = 0;

  if (0 != fdt_check_header(pFdt))
  {
      DEBUG ((EFI_D_ERROR, "Display: Failed to validate device tree header\n"));
  }
  /* Add padding to make space for new nodes and properties. */
  else if (0 != (iRet = fdt_open_into(pFdt, pFdt, fdt_totalsize(pFdt) + DTB_PAD_SIZE)))
  {
    DEBUG ((EFI_D_ERROR, "Display: Failed to move/resize device tree buffer\n"));
  }
  else
  {
    /* Update display command line*/
    UpdateDisplayCmdLine(pFdt);

    /* Update continuous splash node */
    UpdateSplashNode(pFdt);

    if (0 != (iRet = fdt_pack(pFdt)))
    {
      DEBUG((EFI_D_ERROR, "Display: Device tree write failed: %d\n", iRet));
    }
    eStatus = EFI_SUCCESS;
  }

  return eStatus;
}

/*=========================================================================
      Public APIs
==========================================================================*/

/****************************************************************************
*
** FUNCTION: Display_Utils_Initialize()
*/
/*!
* \brief
*   Initialize Display Utils interface
*
* \param None
*
* \retval None
*
****************************************************************************/
void Display_Utils_Initialize(bool32 (*pSupportedDisplayList)[])
{
  Display_UtilsContextType *pDisplayContext = GET_DISPLAY_CONTEXT();

  /* initialize override flag */
  MDP_OSAL_MEMZERO(pDisplayContext, sizeof(Display_UtilsContextType));

  /* Check panel override */
  CheckPanelOverride(pSupportedDisplayList);
}


/****************************************************************************
*
** FUNCTION: Display_Utils_GetParams()
*/
/*!
* \brief
*   Helper to get display override params
*
* \param None
*
* \retval pointer to Display_UtilsParamsType or NULL if not set
*
****************************************************************************/
Display_UtilsParamsType* Display_Utils_GetParams(void)
{
  Display_UtilsContextType *pDisplayContext = GET_DISPLAY_CONTEXT();
  Display_UtilsParamsType  *pDisplayParams  = NULL;

  if (pDisplayContext->bOverride)
  {
    pDisplayParams = &pDisplayContext->sDisplayParams;
  }
  return pDisplayParams;
}


/****************************************************************************
*
** FUNCTION: Display_Utils_SetPanelConfiguration()
*/
/*!
* \brief
*   Send panel configuration string to ABL
*
* \param eDisplayId - Display id
*
* \retval None
*
****************************************************************************/
void Display_Utils_SetPanelConfiguration(MDP_Display_IDType eDisplayId)
{

  EFI_STATUS                eStatus;
  Display_UtilsContextType *pDisplayContext = GET_DISPLAY_CONTEXT();
  CHAR8*                    pConfigStr      = pDisplayContext->pPanelConfig;
  MDP_Panel_AttrType       *pDisplayInfo    = MDP_GET_DISPLAYINFO(eDisplayId);
  uint32                    uFlags          = (MDP_DISPLAY_SECONDARY == eDisplayId) ? pDisplayContext->sDisplayParams.sSecondary.uFlags
                                                                                    : pDisplayContext->sDisplayParams.sPrimary.uFlags;

  if (TRUE  == Display_Utils_IsDisplayDisabled(eDisplayId))
  {
    // Display disabled state, set bDetected flag to TRUE to append panel info
    pDisplayInfo->bDetected = TRUE;
  }

  UpdatePanelConfiguration(eDisplayId, pConfigStr);

  /* Set panel configuration variable */
  if (EFI_SUCCESS != (eStatus = MDP_SetBootServiceVariable(DISPVAR_PANEL_CONFIGURATION, pConfigStr, AsciiStrLen(pConfigStr)+1, 0)))
  {
    DEBUG((EFI_D_WARN,"DisplayUtils: Failed to set boot service variable <%s>. Returned %d\n", DISPVAR_PANEL_CONFIGURATION, eStatus));
  }

  if (DISP_MODE_SEAMLESS_SPLASH_ON & uFlags)
  {
    pDisplayInfo->eDisplayFlags &= ~MDP_PANEL_FLAG_DISABLE_SEAMLESS_SPLASH;
  }
  else if (DISP_MODE_SEAMLESS_SPLASH_OFF & uFlags)
  {
    pDisplayInfo->eDisplayFlags |= MDP_PANEL_FLAG_DISABLE_SEAMLESS_SPLASH;
  }
}


/****************************************************************************
*
** FUNCTION: Display_Utils_CheckPanelSkip()
*/
/*!
* \brief
*   Check for panel override and if the overridden panel is supported in
*   bootloader
*
* \param None
*
* \retval TRUE if panel configuration is to be skipped in bootloader
*
****************************************************************************/
bool32 Display_Utils_CheckPanelSkip()
{
  bool32                    bSkip           = FALSE;
  Display_UtilsContextType *pDisplayContext = GET_DISPLAY_CONTEXT();

  if (TRUE == pDisplayContext->bOverride)
  {
    if (pDisplayContext->sDisplayParams.uFlags & DISP_MODE_SKIP_BOOTLOADER)
    {
      bSkip = TRUE;
    }
    else if (NULL == pDisplayContext->sDisplayParams.sPrimary.pPanelConfig)
    {
      bSkip = TRUE;
    }
    else if (MDPPLATFORM_PANEL_PHYSICAL != pDisplayContext->sDisplayParams.sPrimary.pPanelConfig->ePanelType)
    {
      bSkip = TRUE;
    }
    else
    {
      pDisplayContext->sDisplayParams.uFlags |= pDisplayContext->sDisplayParams.sPrimary.pPanelConfig->pPhysicalPanelConfig->pModeInfo->uModeFlag;

      if (DISP_MODE_SKIP_BOOTLOADER & pDisplayContext->sDisplayParams.uFlags)
      {
        bSkip = TRUE;
      }
    }
  }
  else
  {
    MDPPlatformParams     sPlatformParams;
    PanelConfigType      *pPanelConfig    = NULL;

    MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));

    // No override cmd but still need to check whether the panel skip bootloader flag is set or not
    if ((MDP_STATUS_OK != MDPPlatformConfigure(MDP_DISPLAY_PRIMARY, MDPPLATFORM_CONFIG_GETPANELDTINFO, &sPlatformParams)) ||
        (NULL           == (pPanelConfig = sPlatformParams.pPanelConfig)))
    {
      bSkip = TRUE;
      DEBUG ((EFI_D_WARN, "Display_Utils_CheckPanelSkip: fail to get panel config\n"));
    }
    else if (pPanelConfig->ePanelType != MDPPLATFORM_PANEL_PHYSICAL)
    {
      bSkip = TRUE;
      DEBUG ((EFI_D_WARN, "Display_Utils_CheckPanelSkip: not physical panel!\n"));
    }
    else if (pPanelConfig->pPhysicalPanelConfig)
    {
      UINT32 uFlags    = pPanelConfig->pPhysicalPanelConfig->pModeInfo->uModeFlag;

      if (uFlags & DISP_MODE_SKIP_BOOTLOADER)
      {
        bSkip = TRUE;
      }
    }
  }

  return bSkip;
}


/****************************************************************************
*
** FUNCTION: Display_Utils_GetDisplayCommandLine()
*/
/*!
* \brief
*   Gets the pointer to the panel configuration string & string length
*
* \param [out] ppCmdLine - pointer to command line string
*        [out] pLen      - Ascii length of the string
*
* \retval None
*
****************************************************************************/
void Display_Utils_GetDisplayCommandLine(CHAR8 **ppCmdLine, UINT32 *pLen)
{
  Display_UtilsContextType *pDisplayContext = GET_DISPLAY_CONTEXT();

  /* To make sure we dont go overrun the string */
  pDisplayContext->pPanelConfig[PANEL_CONFIG_STR_LEN_MAX - 1] = '\0';

  /* Set command line & len */
  *ppCmdLine = pDisplayContext->pPanelConfig;
  *pLen      = AsciiStrLen(pDisplayContext->pPanelConfig);

}


/****************************************************************************
*
** FUNCTION: Display_Utils_SetContinuousSplashInfo()
*/
/*!
* \brief
*   Saves the continuous splash address in Display context
*
* \param [in] uAddr - Splash buffer address
*        [in] uSize - Splash buffer size in bytes
*
* \retval None
*
****************************************************************************/
void Display_Utils_SetContinuousSplashInfo(UINT32 uAddr, UINT32 uSize)
{
  Display_UtilsContextType *pDisplayContext = GET_DISPLAY_CONTEXT();

  pDisplayContext->uContinuousSplashAddress  = uAddr;
  pDisplayContext->uContinuousSplashDataSize = uSize;
}


/****************************************************************************
*
** FUNCTION: Display_Utils_GetContinuousSplashInfo()
*/
/*!
* \brief
*   Retrieves the continuous splash buffer info
*
* \param [out] pAddr - Splash buffer address
*        [out] pSize - Splash buffer size in bytes
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS Display_Utils_GetContinuousSplashInfo(UINT32 *pAddr, UINT32 *pSize)
{
  EFI_STATUS                eStatus         = EFI_SUCCESS;
  Display_UtilsContextType *pDisplayContext = GET_DISPLAY_CONTEXT();

  if ((NULL == pAddr) ||
      (NULL == pSize))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: Invalid arguments to continous splash configuration.\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else
  {
    *pAddr = pDisplayContext->uContinuousSplashAddress;
    *pSize = pDisplayContext->uContinuousSplashDataSize;
  }

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: Display_Utils_SetProperty()
*/
/*!
* \brief
*   Set a property on Display UEFI
*
* \param [in] PropertyType - Property identifier
*        [in] Data         - Pointer to data buffer
*        [in] Size         - Size of valid data in bytes
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS Display_Utils_SetProperty (
    EFI_DISPLAY_UTILS_PROPERTY_TYPE ePropertyType,
    void                           *pData,
    UINT32                          uDataSize)
{
  EFI_STATUS                   eStatus          = EFI_SUCCESS;
  Display_UtilsContextType    *pDisplayContext  = GET_DISPLAY_CONTEXT();

  switch(ePropertyType)
  {
  case EFI_DISPLAY_UTILS_DEVICE_TREE_ADDR:
    {
      /* Locate device tree at the address provided and update display specific nodes */
      if ((NULL == pData) ||
          (uDataSize != sizeof(void*)))
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Set property (id=%d) with invalid parameter!\n", ePropertyType));
        eStatus = EFI_INVALID_PARAMETER;
      }
      else if(EFI_SUCCESS != (eStatus = UpdateDeviceTree(pData)))
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Device tree update failed with %d\n", eStatus));
      }
    }
    break;

  case EFI_DISPLAY_UTILS_PANEL_OVERRIDE:
    {
      if ((NULL == pData) ||
          (0 == uDataSize))
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Set property (id=%d) with invalid parameter!\n", ePropertyType));
        eStatus = EFI_INVALID_PARAMETER;
      }
      else if ( uDataSize > (PANEL_OVERRIDE_STR_LEN_MAX *sizeof(CHAR8)))
      {
        DEBUG((EFI_D_WARN,"DisplayUtils: Panel override string is too long. Input %d, Max allowed %d\n",
              uDataSize/sizeof(CHAR8), PANEL_OVERRIDE_STR_LEN_MAX));

        eStatus = EFI_INVALID_PARAMETER;
      }
      else if (EFI_SUCCESS != (eStatus = MDP_Display_SetVariable (DISPVAR_PANEL_OVERRIDE,
                                                                  (UINT8 *) pData,
                                                                  (uDataSize / (sizeof(CHAR8))),
                                                                  0)))
      {
        DEBUG((EFI_D_WARN,"DisplayUtils: Failed to set boot service variable <%s>. Returned %d\n", DISPVAR_PANEL_OVERRIDE, eStatus));
      }
      else
      {
        eStatus = EFI_SUCCESS;
      }
    }
    break;

  case EFI_DISPLAY_UTILS_DYNAMIC_REFRESH:
    {
      if ((NULL == pData) ||
          (0 == uDataSize))
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Set property (id=%d) with invalid parameter!\n", ePropertyType));
        eStatus = EFI_INVALID_PARAMETER;
      }
      else
      {
        if(MDP_STATUS_OK == DSIDriver_SetDynamicRefreshFreqs(pData, uDataSize))
        {
          eStatus = EFI_SUCCESS;
        }
        else
        {
          eStatus = EFI_UNSUPPORTED;
        }
      }
    }
    break;

  case EFI_DISPLAY_UTILS_DISABLE_DISPLAY:
    if ((NULL == pData) ||
        (0    == uDataSize))
    {
      eStatus = EFI_INVALID_PARAMETER;
    }
    else if (uDataSize >= sizeof(pDisplayContext->sDisabledDisplayList))
    {
      MDP_OSAL_MEMCPY(&pDisplayContext->sDisabledDisplayList, pData, sizeof(pDisplayContext->sDisabledDisplayList));
    }
    break;
  case EFI_DISPLAY_UTILS_DISPLAY_ORIENTATION:
    {
      if ((NULL == pData) ||
          (0 == uDataSize))
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Set property (id=%d) with invalid parameter!\n", ePropertyType));
        eStatus = EFI_INVALID_PARAMETER;
      }
      else
      {
        MDP_Panel_AttrType                           *pDisplayInfo = MDP_GET_DISPLAYINFO(MDP_DISPLAY_PRIMARY);
        EFI_DISPLAY_UTILS_DISPLAY_ORIENTATION_PARAMS *pOrientation = (EFI_DISPLAY_UTILS_DISPLAY_ORIENTATION_PARAMS*)pData;
        MDP_PropertiesParamType                       sModeInfo;

        // Change orientation
        pDisplayInfo->ePhysPanelOrientation = (TRUE==pOrientation->bInverted)?MDP_ROTATE_180:MDP_ROTATE_NONE;

        // Don't change the current mode, use the current information.
        MDP_OSAL_MEMZERO(&sModeInfo, sizeof(MDP_PropertiesParamType));
        MDP_OSAL_MEMCPY(&sModeInfo.sModeParams.sSurfaceInfo, &pDisplayInfo->sFrameBuffer, sizeof(sModeInfo.sModeParams.sSurfaceInfo));
        sModeInfo.sModeParams.sRectInfo.uWidth  = pDisplayInfo->sFrameBuffer.uWidth;
        sModeInfo.sModeParams.sRectInfo.uHeight = pDisplayInfo->sFrameBuffer.uHeight;


        if (MDP_STATUS_OK == MDPSetProperty(MDP_DISPLAY_PRIMARY, MDP_DISPLAY_PROPERTY_SURFACE_RECT, &sModeInfo))
        {
          eStatus = EFI_SUCCESS;
        }
        else
        {
          eStatus = EFI_UNSUPPORTED;
        }
      }
    }
    break;

    case EFI_DISPLAY_UTILS_DISPLAY_WRITE:
    {
      EFI_DISPLAY_UTILS_READWRITE_PARAMS *pWriteParams = (EFI_DISPLAY_UTILS_READWRITE_PARAMS *)pData;

      if ((0 == uDataSize) ||
          (NULL == pData))
      {
        eStatus = EFI_INVALID_PARAMETER;
      }
      else
      {
        MDP_Panel_AttrType  *pDisplayInfo = MDP_GET_DISPLAYINFO(pWriteParams->uDisplayId);

        if (MDP_INTERFACE_DSI == MDP_CONNECTIONINTF_MAP(pDisplayInfo->ePhysConnect))
        {
          if (MDP_STATUS_OK == DSIDriver_Write(pWriteParams->uDisplayId, pWriteParams->uCmdType, pWriteParams->uPayload, pWriteParams->uPayloadSize, pWriteParams->uFlags))
          {
            eStatus = EFI_SUCCESS;
          }
          else
          {
            eStatus = EFI_DEVICE_ERROR;
          }
        }
        else
        {
          eStatus = EFI_UNSUPPORTED;
        }
      }
   }
   break;

  default:
    eStatus = EFI_UNSUPPORTED;
  }
  return eStatus;
}


/****************************************************************************
*
** FUNCTION: Display_Utils_GetProperty()
*/
/*!
* \brief
*   Set a property on Display UEFI
*
* \param [in]     Type            Property type
*        [out]    Data            Pointer to data structure
*        [in/out] DataSize        [in] Max size of data
*                                 [out] Actual size of data
*
* \retval EFI_STATUS
* EFI_SUCCESS              : Function returned successfully.
* EFI_INVALID_PARAMETER    : Parameter passed is incorrect.
* EFI_UNSUPPORTED          : Parameter passed is not supported.
* EFI_DEVICE_ERROR         : Physical device reported an error.
* EFI_BUFFER_TOO_SMALL     : Buffer to small to copy data into
*
****************************************************************************/
EFI_STATUS Display_Utils_GetProperty(
    EFI_DISPLAY_UTILS_PROPERTY_TYPE ePropertyType,
    void                           *pData,
    UINT32                         *pDataSize)
{
  EFI_STATUS                   eStatus          = EFI_SUCCESS;
  Display_UtilsContextType    *pDisplayContext  = GET_DISPLAY_CONTEXT();

  switch(ePropertyType)
  {
  case EFI_DISPLAY_UTILS_PANEL_CONFIG:
    {
      if ((NULL == pDataSize) ||
          (NULL == pData))
      {
        eStatus = EFI_INVALID_PARAMETER;
      }
      else if (*pDataSize < sizeof(EFI_DISPLAY_UTILS_PANEL_CONFIG))
      {
        eStatus = EFI_BUFFER_TOO_SMALL;
      }
      else
      {
        MDPPlatformParams                      sPlatformParams;
        EFI_DISPLAY_UTILS_PANEL_CONFIG_PARAMS *pPanelConfig = (EFI_DISPLAY_UTILS_PANEL_CONFIG_PARAMS*)pData;

        MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));
        sPlatformParams.sPanelXMLInfo.uIndex = pPanelConfig->uPanelIndex;

        if (MDP_STATUS_OK == MDPPlatformConfigure(MDP_DISPLAY_PRIMARY, MDPPLATFORM_CONFIG_GETPANELXMLINFO, &sPlatformParams))
        {
          // Return the details
          pPanelConfig->pPanelConfig       = (CHAR8*)sPlatformParams.sPanelXMLInfo.pPanelXMLConfig;
          pPanelConfig->uPanelConfigLength = sPlatformParams.sPanelXMLInfo.uPanelXMLSize;

          eStatus = EFI_SUCCESS;
        }
        else
        {
          eStatus = EFI_UNSUPPORTED;
        }
      }
    }
    break;

    case EFI_DISPLAY_UTILS_DYNAMIC_REFRESH:
    {
      if ((NULL == pDataSize) ||
          (NULL == pData))
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Set property (id=%d) with invalid parameter!\n", ePropertyType));
        eStatus = EFI_INVALID_PARAMETER;
      }
      else
      {
        MDP_Status               eMDPStatus = MDP_STATUS_OK;
        MDP_Display_IDType       eDisplayId = MDP_DISPLAY_PRIMARY;

        if ((FALSE == MDP_SUPPORTED_DISPLAY(eDisplayId) ||
            (TRUE  == Display_Utils_IsDisplayDisabled(eDisplayId))))
        {
          eStatus = EFI_UNSUPPORTED;
        }
        else
        {
          MDP_PropertiesParamType  sDisplayProp;
          MDP_PropertiesParamType  sDisplayBLProp;
          MDP_Panel_AttrType      *pDisplayInfo = MDP_GET_DISPLAYINFO(eDisplayId);

          MDP_OSAL_MEMZERO(&sDisplayProp,   sizeof(MDP_PropertiesParamType));
          MDP_OSAL_MEMZERO(&sDisplayBLProp, sizeof(MDP_PropertiesParamType));
          sDisplayProp.uBacklightLevel = 0;

          /* Save the backlight level, turn off backlight and stop pipes to avoid any visual corruption during PLL calculation*/
          if (MDP_STATUS_OK != (eMDPStatus = MDPGetProperty(MDP_DISPLAY_PRIMARY, MDP_DISPLAY_PROPERTY_BACKLIGHT, &sDisplayBLProp)))
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "Display_Utils_GetProperty: MDPGetProperty() failed! Status: %d\n", eMDPStatus);
          }
          else if (MDP_STATUS_OK != (eMDPStatus = MDPSetProperty(MDP_DISPLAY_PRIMARY, MDP_DISPLAY_PROPERTY_BACKLIGHT, &sDisplayProp)))
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "Display_Utils_GetProperty: MDPSetProperty() failed! Status: %d\n", eMDPStatus);
          }
          else if (MDP_STATUS_OK != (eMDPStatus = MDPStopPipe(pDisplayInfo)))
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "Display_Utils_GetProperty: MDPStopPipe() failed! Status: %d\n", eMDPStatus);
          }
          else if (MDP_STATUS_OK != (eMDPStatus = DSIDriver_CalibratePLL(pData, pDataSize)))
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "Display_Utils_GetProperty: DSIDriver_CalibratePLL() failed! Status: %d\n", eMDPStatus);
          }
          else if (MDP_STATUS_OK != (eMDPStatus = MDPStartPipe(pDisplayInfo)))
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "Display_Utils_GetProperty: MDPStartPipe() failed! Status: %d\n", eMDPStatus);
          }
          else if (MDP_STATUS_OK != (eMDPStatus = MDPSetProperty(MDP_DISPLAY_PRIMARY, MDP_DISPLAY_PROPERTY_BACKLIGHT, &sDisplayBLProp)))
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "Display_Utils_GetProperty: MDPSetProperty() failed! Status: %d\n", eMDPStatus);
          }

          if (MDP_STATUS_OK != eMDPStatus)
          {
            eStatus = EFI_DEVICE_ERROR;
          }

        }
      }
    }
    break;

  case EFI_DISPLAY_UTILS_DISABLE_DISPLAY:
    if ((NULL == pData) ||
        (NULL == pDataSize))
    {
      eStatus = EFI_INVALID_PARAMETER;
    }
    else
    {
      MDP_OSAL_MEMCPY(pData, &pDisplayContext->sDisabledDisplayList, sizeof(pDisplayContext->sDisabledDisplayList));
      *pDataSize = sizeof(pDisplayContext->sDisabledDisplayList);
    }
    break;
  case EFI_DISPLAY_UTILS_PROFILING_LOG:
    {
      uint32 uCount = 0;

      if (NULL != gProfileLog)
      {
        uint32 uIndex;

        if (gProfileLog->uEntryCount > MDP_PROFILER_LOG_ENTRIES)
        {
          uCount = MDP_PROFILER_LOG_ENTRIES;
        }
        else
        {
          uCount = gProfileLog->uEntryCount;
        }

        AsciiPrint("\nDisplayDxe Profiling Log\n\n");
        AsciiPrint("%-14a %-5a %-40a %-6a %-6a %-10a\n", "Timestamp(us)", "Entry", "Function", "Param1", "Param2", "Delta(us)");
        for (uIndex=0; uIndex < uCount; uIndex++)
        {
          AsciiPrint("%-14d ", gProfileLog->aProfileLog[uIndex].uTimeStamp);
          AsciiPrint("%-5a ",  (1 & gProfileLog->aProfileLog[uIndex].uParams[0])?"Entry":"Exit");
          AsciiPrint("%-40a ", gProfileLog->aProfileLog[uIndex].sFunctionName);
          AsciiPrint("%-6d ",  gProfileLog->aProfileLog[uIndex].uParams[1]);
          AsciiPrint("%-6d ",  gProfileLog->aProfileLog[uIndex].uParams[2]);
          if (0==uIndex)
          {
            AsciiPrint("%-10d\n", 0);
          }
          else
          {
            AsciiPrint("%-10d\n", gProfileLog->aProfileLog[uIndex].uTimeStamp-gProfileLog->aProfileLog[uIndex-1].uTimeStamp);
          }
        }
      }
      AsciiPrint("\n%d Entries\n", uCount);      

      eStatus = EFI_SUCCESS;
    }
    break;

    case EFI_DISPLAY_UTILS_STATS:
    { 
      if ((NULL == pData) ||
          (NULL == pDataSize))
      {
        eStatus = EFI_INVALID_PARAMETER;
      }
      else
      { 
        HAL_MDP_InterfaceInfoParamsType           sInterfaceInfo;
        HAL_MDP_Interface_FrameRefreshInfoType    sFrameRefreshInfo;
        EFI_DISPLAY_UTILS_STATS_INFO              *pDisplayStateInfo = (EFI_DISPLAY_UTILS_STATS_INFO *)pData;
        MDP_Display_IDType                         eDisplayId        = (MDP_Display_IDType)pDisplayStateInfo->uDisplayId;

        switch (eDisplayId)
        {
          case MDP_DISPLAY_PRIMARY:
          case MDP_DISPLAY_SECONDARY:
          case MDP_DISPLAY_EXTERNAL:
          case MDP_DISPLAY_EXTERNAL2:
          case MDP_DISPLAY_EXTERNAL3:
          case MDP_DISPLAY_EXTERNAL4:
          case MDP_DISPLAY_EXTERNAL5:
          case MDP_DISPLAY_EXTERNAL6:
          {
            if ((FALSE == MDP_SUPPORTED_DISPLAY(eDisplayId) ||
                 (TRUE  == Display_Utils_IsDisplayDisabled(eDisplayId))))
            {
              DEBUG((EFI_D_WARN, "DisplayUtils: not support display %d\n", eDisplayId));
              eStatus = EFI_UNSUPPORTED;
            }
            else
            {
              MDP_Panel_AttrType *pDisplayInfo     = MDP_GET_DISPLAYINFO(eDisplayId);

              MDP_OSAL_MEMZERO(&sFrameRefreshInfo, sizeof(HAL_MDP_Interface_FrameRefreshInfoType));
              MDP_OSAL_MEMZERO(&sInterfaceInfo,    sizeof(HAL_MDP_InterfaceInfoParamsType));
              sInterfaceInfo.pFrameRefreshInfo     = &sFrameRefreshInfo;

              if (HAL_MDSS_STATUS_SUCCESS == HAL_MDP_Interface_GetProperty(pDisplayInfo->sDisplayControlPath[0].eInterfaceId, &sInterfaceInfo, 0))
              {
                pDisplayStateInfo->uFrameCount = sInterfaceInfo.pFrameRefreshInfo->uCurrentFrameCnt;
                pDisplayStateInfo->uLineCount  = sInterfaceInfo.pFrameRefreshInfo->uCurrentLineCnt;
                eStatus = EFI_SUCCESS;
              }
              else
              {
                DEBUG((EFI_D_WARN, "DisplayUtils: Get interface property failed\n"));
                eStatus = EFI_UNSUPPORTED;
              }
            }
          }
          break;

          default:
            DEBUG((EFI_D_WARN, "DisplayUtils: Display Id invalid\n"));
            eStatus = EFI_UNSUPPORTED;
          break;
        }
      }
    }
    break;

  case EFI_DISPLAY_UTILS_DISPLAY_CONFIGURATION:
  {
    EFI_DISPLAY_UTILS_SUPPORTED_PANELS_PARAMS *pPanelParams = (EFI_DISPLAY_UTILS_SUPPORTED_PANELS_PARAMS *)pData;

    if ((NULL == pDataSize) ||
        (NULL == pData))
    {
      eStatus = EFI_INVALID_PARAMETER;
    }
    else
    {
      if (TRUE == MDP_SUPPORTED_DISPLAY(pPanelParams->uDisplayId))
      {
        MDP_Panel_AttrType  *pDisplayInfo = MDP_GET_DISPLAYINFO(pPanelParams->uDisplayId);

        pPanelParams->uNumInterfaces = pDisplayInfo->uNumInterfaces;

        switch (MDP_CONNECTIONINTF_MAP(pDisplayInfo->ePhysConnect))
        {
          case MDP_INTERFACE_DSI:
          {
            pPanelParams->eInterfaceType = EFI_DISPLAY_UTILS_INTERFACE_DSI;

            if ((pPanelParams->uNumInterfaces < MDP_INTERFACE_DUAL))
            {
              if (pDisplayInfo->uAttrs.sDsi.uControllerSinglePrimary)
              {
                pPanelParams->uIntefaceList[0] = DSI_1_SINGLE_PRIMARY;
              }
              else
              {
                pPanelParams->uIntefaceList[0] = DSI_0_SINGLE_PRIMARY;
              }
            }
            else
            {
              pPanelParams->uIntefaceList[0] = DSI_0_SINGLE_PRIMARY;
              pPanelParams->uIntefaceList[1] = DSI_1_SINGLE_PRIMARY;
            }
          }
          break;

          case MDP_INTERFACE_DP:
          {
            pPanelParams->eInterfaceType = EFI_DISPLAY_UTILS_INTERFACE_DP;
          }
          break;

          default:
          {
            pPanelParams->eInterfaceType = EFI_DISPLAY_UTILS_INTERFACE_NONE;
          }
          break;
        }
      }
      else
      {
        eStatus = EFI_UNSUPPORTED;
      }
    }
  }
  break;

  case EFI_DISPLAY_UTILS_DISPLAY_READ:
  {
    EFI_DISPLAY_UTILS_READWRITE_PARAMS *pRWParams = (EFI_DISPLAY_UTILS_READWRITE_PARAMS *)pData;

    if ((NULL == pDataSize) ||
        (NULL == pData))
    {
      eStatus = EFI_INVALID_PARAMETER;
    }
    else
    {
      MDP_Panel_AttrType  *pDisplayInfo = MDP_GET_DISPLAYINFO(pRWParams->uDisplayId);

      if (MDP_INTERFACE_DSI == MDP_CONNECTIONINTF_MAP(pDisplayInfo->ePhysConnect))
      {
        if (MDP_STATUS_OK == DSIDriver_Read(pRWParams->uDisplayId, pRWParams->uCmdType, (void *)&pRWParams->uAddress,
                                            sizeof(pRWParams->uAddress), pRWParams->uPayload,
                                            &pRWParams->uPayloadSize, pRWParams->uFlags))
        {
          eStatus = EFI_SUCCESS;
        }
        else
        {
          eStatus = EFI_DEVICE_ERROR;
        }
      }
      else
      {
        eStatus = EFI_UNSUPPORTED;
      }
    }
  }
  break;

  default:
    eStatus = EFI_UNSUPPORTED;
  }

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: Display_Utils_RenderBGRTImage()
*/
/*!
* \brief
*   Render an image on to the screen from the BGRT buffer.
*
* \param[in]  BGRTImage         BGRT Source image buffer.
*       [in]  BGRTImageSize     BGRT image buffer size.
*       [in]  pRenderLogoParams Render logo parameters.
*
* \retval EFI_STATUS
* EFI_SUCCESS                 : Image loaded successfully in to memory.
* EFI_INVALID_PARAMETER       : Invalid input parameters passed in.
* EFI_OUT_OF_RESOURCES        : Not enough resources for buffer allocations.
*
****************************************************************************/
EFI_STATUS
Display_Utils_RenderBGRTImage(
    IN UINT8                 *BGRTImage,
    IN UINT32                 BGRTImageSize,
    RenderLogoParamsType     *pRenderLogoParams)
{

  EFI_STATUS                     Status         = EFI_SUCCESS;
  EFI_GRAPHICS_OUTPUT_PROTOCOL  *GraphicsOutput = NULL;
  BMP_IMAGE_HEADER              *ImageHeader    = (BMP_IMAGE_HEADER*)BGRTImage;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  bgPixel        = {0};

  //
  // Try to open GOP(Graphics output protocol) for blt operations
  //
  Status = gBS->LocateProtocol(&gEfiGraphicsOutputProtocolGuid,
                               NULL,
                               (VOID **)&GraphicsOutput);

  if ((EFI_SUCCESS != Status) ||
      (NULL        == GraphicsOutput))
  {
    DEBUG((EFI_D_ERROR, "DisplayUtils: Cannot locate GraphicsOutput.\r\n"));
    Status = EFI_UNSUPPORTED;
  }
  // Validate all inputs
  else if ((0 == GraphicsOutput->Mode->Info->HorizontalResolution) ||
           (0 == GraphicsOutput->Mode->Info->VerticalResolution))
  {
    DEBUG((EFI_D_ERROR, "DisplayUtils: Invalid inputs of horizontal / vertical resolution.\r\n"));
    Status = EFI_INVALID_PARAMETER;
  }
  else if ((NULL == ImageHeader) ||
           (0 == BGRTImageSize)  ||
           (NULL == BGRTImage)   ||
           (BGRTImageSize < sizeof(BMP_IMAGE_HEADER)))
  {
      // Invalid input parameters
      Status = EFI_INVALID_PARAMETER;
  }
  else if (('B' != ImageHeader->CharB) ||
           ('M' != ImageHeader->CharM) ||
           (0 != ImageHeader->CompressionType))
  {
      // Unsupported image format
      Status = EFI_UNSUPPORTED;

  }
   else if ((32 != ImageHeader->BitPerPixel) &&
            (24 != ImageHeader->BitPerPixel) &&
            (8  != ImageHeader->BitPerPixel))
   {
      // Unsupported pixel format
      Status = EFI_UNSUPPORTED;
   }
   else if (((ImageHeader->PixelWidth * ImageHeader->PixelHeight * ImageHeader->BitPerPixel) / 8) > (BGRTImageSize - sizeof(BMP_IMAGE_HEADER)))
   {
     // Resolution cannot be larger than the file itself minus the header
     Status = EFI_UNSUPPORTED;
   }
   else if (NULL == pRenderLogoParams)
   {
     Status = EFI_INVALID_PARAMETER;
   }
   else
   {
      UINT32         ImageHeight;
      UINT32         ImageWidth;
      UINT32         ImageStride;
      UINT8         *SrcAddress;
      INT32          SrcStride;
      UINT32         DestStride;
      UINT32        *ConversionBuffer;
      BMP_COLOR_MAP *ColorMap        = (BMP_COLOR_MAP *) (BGRTImage + sizeof (BMP_IMAGE_HEADER));

      //
      // This section of code handles conversion from the native BMP format to a GOP compatible format, this includes
      // - Conversion from 24bpp to 32bpp
      // - Handling an inverted image
      // - Handling BMP stride alignment of 4 bytes.
      //
      // Potential optimization to perform conversion using MDPBlt() API to use hardware to perform this conversion and blt
      // directly to the frame buffer.
      //
      //

      // Populate the image width and height
      ImageWidth = ImageHeader->PixelWidth;
      // Image source is 24bpp, but is always aligned to a dword (4 bytes)
      ImageStride = (ImageWidth * (ImageHeader->BitPerPixel/8));
      // Align stride on a dword boundary
      ImageStride = ((ImageStride)+3) & ~3;

      // Populate starting address, height and stride information, the source image could be stored
      // upside down, need to handle the case of an inverted image
      if ((INT32)ImageHeader->PixelHeight < 0)
      {
        // Image height is negative, indicating the image is in raster order, setup the pointers so we can
        // copy the image directly
        ImageHeight = (UINT32)- ImageHeader->PixelHeight;
        // Calculate the starting address which starts after the header
        SrcAddress = (UINT8*)((UINTN)BGRTImage + (UINT32)ImageHeader->ImageOffset);

        // Source stride is incremented by the image stride directly
        SrcStride = ImageStride;
      }
      else
      {
        // by default BMP images are stored upside down, setup the buffers to copy in the reverse direction
        ImageHeight = (UINT32)ImageHeader->PixelHeight;
        // Image source is 24bpp, but is always aligned to a dword (4 bytes)
        // Source image starts on the last line and we copy from the last line to the top
        SrcAddress =  (UINT8*)((UINTN)BGRTImage + (UINT32)ImageHeader->ImageOffset + (UINT32)((ImageHeight-1)*ImageStride));
        // Reverse stride since we are subtracting from the bottom
        SrcStride = -ImageStride;
      }

      // Calcualte the destination output stride.
      DestStride  = ImageWidth * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);

      // Allocate a temporary buffer that is compatible with the GOP protocol
      ConversionBuffer = AllocatePool(ImageHeight * DestStride);

      if (NULL == ConversionBuffer)
      {
        // Cannot allocate a conversion buffer
        Status = EFI_OUT_OF_RESOURCES;
      }
      else
      {
        UINT32 Count;
        //
        // If the OEM supports two logos (logo1.bmp & logo2.bmp), they should use the BGRT table to override the offsets for logo2.bmp.
        //
        UINT32              LogoPosX      = 0;
        UINT32              LogoPosY      = 0;
        UINT8              *DestAddress   = (UINT8*)ConversionBuffer;
        MDP_Display_IDType  eDisplayId    = pRenderLogoParams->eDisplayId;
        uint32              uBGRTRotation = (PcdGet32(PcdBGRTRotation) > DISP_BGRT_ROTATION_270) ? DISP_BGRT_ROTATION_NONE : PcdGet32(PcdBGRTRotation);
        bool32              bRotated90    = ((DISP_BGRT_ROTATION_90  == uBGRTRotation) ||
                                             (DISP_BGRT_ROTATION_270 == uBGRTRotation)) ? TRUE:FALSE;

        pRenderLogoParams->eBGRTRotation = uBGRTRotation;
        
        CalculateLogoPosition(ImageWidth, ImageHeight, &LogoPosX, &LogoPosY, pRenderLogoParams);

        // Copy line by line to handle inverted images and images that have padding (due to odd widths)
        //
        for (Count=0;Count<ImageHeight;Count++)
        {

          // Perform conversion, all pixel depths are in bits, so multiply byte size by 8
          ConversionPixelCopy(ImageHeader->BitPerPixel,
                              ColorMap,
                              SrcAddress,
                              (sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)*8),
                              DestAddress,
                              ImageWidth);

          // Increment the source and destination pointers by their respective strides.
          DestAddress += DestStride;
          SrcAddress += SrcStride;
        }
        
        /* Rotate the logo */
        if (DISP_BGRT_ROTATION_NONE != pRenderLogoParams->eBGRTRotation)
        {
          UINT32* pRotatioBuffer  = AllocatePool(ImageHeight * DestStride);

          if ( NULL == pRotatioBuffer )
          {
            DEBUG((EFI_D_ERROR, "Display_Utils_RenderBGRTImage: AllocatePool failed\r\n"));
          }
          else
          {
            RotatePixel32Copy(ConversionBuffer, pRotatioBuffer , ImageWidth, ImageHeight, pRenderLogoParams->eBGRTRotation);

            //Swapping Conversion buffer with the rotation buffer
            FreePool(ConversionBuffer);
            ConversionBuffer = pRotatioBuffer ;
          }
        }

        //
        // Setup blt of conversion buffer to the screen
        //
        if (EFI_SUCCESS != (Status = DisplayDxe_Blt(GraphicsOutput,
                                                    eDisplayId,
                                                    (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&bgPixel,
                                                    EfiBltVideoFill,
                                                    0, 0,
                                                    0, 0,
                                                    ImageWidth,
                                                    ImageHeight,
                                                    0)))
        {
          DEBUG((EFI_D_ERROR, "DisplayUtils: Blt(EfiBltVideoFill) failed. Status =%d\r\n", Status));
        }
        else if (EFI_SUCCESS != (Status = DisplayDxe_Blt (GraphicsOutput,
                                                          eDisplayId,
                                                          (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)ConversionBuffer,
                                                          EfiBltBufferToVideo,
                                                          0,
                                                          0,
                                                          (UINTN) LogoPosX,
                                                          (UINTN) LogoPosY,
                                                          ((bRotated90) ? ImageHeight: ImageWidth),
                                                          ((bRotated90) ? ImageWidth : ImageHeight),
                                                          ((bRotated90) ? ImageHeight: ImageWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL))))
        {
          DEBUG((EFI_D_ERROR, "DisplayUtils: Blt(EfiBltBufferToVideo) failed. Status =%d\r\n", Status));
        }

        //
        // Free the conversion buffer
        //
        if (ConversionBuffer)
        {
          FreePool(ConversionBuffer);
        }
      }
  }

  return Status;
}


/****************************************************************************
*
** FUNCTION: Display_Utils_RenderSplashScreen()
*/
/*!
* \brief
*   Load, process and display OEM logo bitmaps including processing needed to
*   support ACPI2.0 BGRT.
*
*   - Display_Utils_RenderSplashScreen is called with NULL which will render the logo
*     (found in FV or HLOS partitions).
*   - Display_Utils_RenderSplashScreen is called with valid BGRT will update the BGRT table.  
*
* \param[out]  BGRTTable         Pointer to the BGRT table in ACPI, if NULL the
*                                primary logo is rendered with no BGRT information returned.
*       [in]   pRenderLogoParams Render logo parameters.
*
* \retval EFI_STATUS
* EFI_SUCCESS                  : Image loaded successfully in to memory.
* EFI_INVALID_PARAMETER        : Invalid input parameters passed in.
* EFI_OUT_OF_RESOURCES         : Not enough resources for buffer allocations.
*
****************************************************************************/
EFI_STATUS
EFIAPI
Display_Utils_RenderSplashScreen(
  OUT VOID             *BGRTTable OPTIONAL,
  RenderLogoParamsType *pRenderLogoParams)
{
  EFI_STATUS                                        Status          = EFI_SUCCESS;
  static EFI_ACPI_6_3_BOOT_GRAPHICS_RESOURCE_TABLE *pLocalBGRTTable = NULL;

  // Handle cases where the BGRT is not yet loaded or not applicable
  if(NULL == BGRTTable)
  {
     // Allocate space for the local cached copy of the BGRT table if it doesn't exist
     if (NULL == pLocalBGRTTable)
     {
        if (NULL == (pLocalBGRTTable  = (EFI_ACPI_6_3_BOOT_GRAPHICS_RESOURCE_TABLE*) AllocateZeroPool(sizeof(EFI_ACPI_6_3_BOOT_GRAPHICS_RESOURCE_TABLE))))
        {
            DEBUG ((EFI_D_ERROR, "Display_Utils_RenderSplashScreen: Unable to allocate memory for local BGRT table!\n"));
            Status = EFI_OUT_OF_RESOURCES;
        }
     }

     // Load and render the logo file, cache the BGRT information till a valid BGRT is passed in.
     if (EFI_SUCCESS == Status)
     {
       UINT8                     *BGRTAddress     = NULL;
       CHAR8                     *pLogoFileName   = NULL;
       UINT32                     ImageSize       = 0;
       UINT32                     BGRTBufferSize  = 0;
       UINT32                     uFlags          = 0;
       UINT32                     uImageFvSetting = 0;

       // Enable display imagefv based on the settings for runtime and compile time.
       if (((MDP_STATUS_OK  == MDP_Display_GetVariable_Integer(DISPVAR_ENABLE_DISPLAY_IMAGEFV, &uImageFvSetting))  &&
            (1              == uImageFvSetting))                                                                   ||
           ((MDP_STATUS_OK  == MDP_GetConfigValue(DISPVAR_ENABLE_DISPLAY_IMAGEFV_ASCII, &uImageFvSetting))         &&
            (1              == uImageFvSetting)))
       {
         // Set imagefv flag if logo policy is 1, which indicates loading logo from imagefv system.
         uFlags = DISP_LOAD_FILE_FLAG_IMAGEFV;
       }

       pLogoFileName = Display_Utils_GetLogoConfig(pRenderLogoParams);

       // Load logo from FV.
       Status = Display_Utils_LoadFile(pLogoFileName, &BGRTAddress, &BGRTBufferSize, &ImageSize, uFlags);

       if (EFI_SUCCESS == Status)
       {
         // Render logo file after loading it.
         if (EFI_SUCCESS == (Status = Display_Utils_RenderBGRTImage(BGRTAddress, ImageSize, pRenderLogoParams)))
         {
           BMP_IMAGE_HEADER *ImageHeader = (BMP_IMAGE_HEADER*)BGRTAddress;
           UINT32            ImageWidth  = ImageHeader->PixelWidth;
           UINT32            ImageHeight = ((INT32)ImageHeader->PixelHeight < 0) ? ((UINT32)- ImageHeader->PixelHeight):ImageHeader->PixelHeight;

           DEBUG ((EFI_D_INFO, "Display_Utils_RenderSplashScreen: OEM Logo Successfully Loaded\n"));

           // Update the BGRT position, store it in the cached version of the BGRT
           CalculateLogoPosition(ImageWidth, ImageHeight, &pLocalBGRTTable->ImageOffsetX, &pLocalBGRTTable->ImageOffsetY, pRenderLogoParams);

           // As logo file is rendered to the panel, set the status field to 1.
           pLocalBGRTTable->Status       = 0x1 | (pRenderLogoParams->eBGRTRotation << 1);
           // Update the BGRT address
           pLocalBGRTTable->ImageAddress = (UINT64)BGRTAddress;
         }
         else
         {
           DEBUG((EFI_D_ERROR, "Display_Utils_RenderSplashScreen: Display_Utils_RenderBGRTImage failed %d\n", Status));
         }
       }
     }
  }
  else  // Valid BGRT passed in, validate is and process it.
  {
    // The define of ACPI 6.3 covers version 5.0 to 6.3
    EFI_ACPI_6_3_BOOT_GRAPHICS_RESOURCE_TABLE  *pBGRTTable = (EFI_ACPI_6_3_BOOT_GRAPHICS_RESOURCE_TABLE *)BGRTTable;

    if ((EFI_ACPI_6_3_BOOT_GRAPHICS_RESOURCE_TABLE_SIGNATURE != pBGRTTable->Header.Signature) || // "BGRT" Signature
        (EFI_ACPI_6_3_BGRT_VERSION                           != pBGRTTable->Version)          || // Valid version 1.0
        (EFI_ACPI_6_3_BGRT_IMAGE_TYPE_BMP                    != pBGRTTable->ImageType))          // Valid type BMP
    {
      DEBUG ((EFI_D_ERROR, "Display_Utils_RenderSplashScreen: BGRT table header corrupt or invalid!\n"));
      Status = EFI_LOAD_ERROR;
    }
    else
    {
      // Pass information loaded during logo1 back to the caller's BGRT table
        if (NULL != pLocalBGRTTable)
        {
          pBGRTTable->ImageOffsetX = pLocalBGRTTable->ImageOffsetX;
          pBGRTTable->ImageOffsetY = pLocalBGRTTable->ImageOffsetY;
          pBGRTTable->Status       = pLocalBGRTTable->Status;
          pBGRTTable->ImageAddress = pLocalBGRTTable->ImageAddress;
        }
        else
        {
          DEBUG ((EFI_D_ERROR, "Display_Utils_RenderSplashScreen: BGRT was not loaded correctly, table cannot be updated!\n"));
        }
      }
    }

  return Status;
}


/****************************************************************************
*
** FUNCTION: DisplayRenderLogoInternal()
*/
/*!
* \brief
*   Display Utils Protocol Render logo function.
*
* \param[in]  psRenderLogoConfig  Configurations of clearing screen and overriding position.
*
* \retval EFI_STATUS
* EFI_SUCCESS                   : Function returned successfully.
* EFI_INVALID_PARAMETER         : Parameter passed is incorrect.
* EFI_UNSUPPORTED               : Parameter passed is not supported.
* EFI_DEVICE_ERROR              : Physical device reported an error.
*
****************************************************************************/
static EFI_STATUS DisplayRenderLogoInternal(
  IN  EFI_DISPLAY_UTILS_RENDERLOGO_CONFIG *psRenderLogoConfig)
{
  EFI_STATUS                     eStatus           = EFI_SUCCESS;

  if (NULL == psRenderLogoConfig)
  {
    eStatus = EFI_INVALID_PARAMETER;
  }
  else
  {
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL  bgPixel;
    RenderLogoParamsType           sRenderLogoParams;
    EFI_GRAPHICS_OUTPUT_PROTOCOL  *GraphicsOutput = NULL;

    MDP_OSAL_MEMZERO(&bgPixel,           sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
    MDP_OSAL_MEMZERO(&sRenderLogoParams, sizeof(RenderLogoParamsType));

    sRenderLogoParams.eDisplayId = psRenderLogoConfig->uDisplayId;

    // Clear Screen
    if (psRenderLogoConfig->uFlags & DISPLAY_UTILS_RENDERLOGO_CLEARSCREEN)
    {
      eStatus = gBS->LocateProtocol(&gEfiGraphicsOutputProtocolGuid,
                                    NULL,
                                   (void**)&GraphicsOutput);
      if ((eStatus != EFI_SUCCESS)                                      ||
          (NULL    == GraphicsOutput)                                   ||
          (0       == GraphicsOutput->Mode->Info->HorizontalResolution) ||
          (0       == GraphicsOutput->Mode->Info->VerticalResolution))
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Locate Protocol or Get Resolution failed!\n"));
      }
      else
      {
        GraphicsOutput->Blt(GraphicsOutput,
                            (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&bgPixel,
                            EfiBltVideoFill,
                            0, 0,
                            0, 0,
                            GraphicsOutput->Mode->Info->HorizontalResolution,
                            GraphicsOutput->Mode->Info->VerticalResolution,
                            0);
      }
    }

    // Override Logo Position
    if (psRenderLogoConfig->uFlags & DISPLAY_UTILS_RENDERLOGO_POSITION_OVERRIDE)
    {
      sRenderLogoParams.uXPosition  = psRenderLogoConfig->xPosition;
      sRenderLogoParams.uYPosition  = psRenderLogoConfig->yPosition;
      sRenderLogoParams.uFlags     |= RENDER_LOGO_POSITION_OVERRIDE;
    }

    // Render BGRT Image
    if(psRenderLogoConfig->uFlags & DISPLAY_UTILS_RENDERLOGO_RENDER_BGRT_IMAGE)
    {
      if (EFI_SUCCESS != (eStatus = Display_Utils_RenderBGRTImage(psRenderLogoConfig->BGRTImage,
                                                                  psRenderLogoConfig->BGRTImageSize,
                                                                  &sRenderLogoParams)))
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Render BGRT Image failed with Status(%d)!\n", eStatus));
      }
    }
    // Render Splash Screen
    else if (EFI_SUCCESS != (eStatus = Display_Utils_RenderSplashScreen(psRenderLogoConfig->BGRTTable,
                                                                        &sRenderLogoParams)))
    {
      DEBUG((EFI_D_WARN, "DisplayUtils: Render Splash Screen failed with Status(%d)!\n", eStatus));
    }
  }

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: Display_Utils_RenderLogo()
*/
/*!
* \brief
*   Display Utils Protocol Render logo function.
*
* \param[in]  psRenderLogoConfig  Configurations of clearing screen and overriding position.
*
* \retval EFI_STATUS
* EFI_SUCCESS                   : Function returned successfully.
* EFI_INVALID_PARAMETER         : Parameter passed is incorrect.
* EFI_UNSUPPORTED               : Parameter passed is not supported.
* EFI_DEVICE_ERROR              : Physical device reported an error.
*
****************************************************************************/
EFI_STATUS
Display_Utils_RenderLogo(
  IN  EFI_DISPLAY_UTILS_RENDERLOGO_CONFIG *psRenderLogoConfig)
{
  EFI_STATUS                          eStatus     = EFI_SUCCESS;
  MDP_Display_IDType                  eDisplayId  = MDP_DISPLAY_PRIMARY;
  EFI_DISPLAY_UTILS_RENDERLOGO_CONFIG sRenderLogoConfig;

  MDP_LOG_FUNC_ENTRY("Display_Utils_RenderLogo", 0x0);

  MDP_OSAL_MEMZERO(&sRenderLogoConfig, sizeof(sRenderLogoConfig));

  if (NULL != psRenderLogoConfig)
  {
    MDP_OSAL_MEMCPY(&sRenderLogoConfig, psRenderLogoConfig, sizeof(sRenderLogoConfig));
  }

  for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_SECONDARY; eDisplayId++)
  {
    if ((FALSE == MDP_SUPPORTED_DISPLAY(eDisplayId)) ||
        (TRUE  == Display_Utils_IsDisplayDisabled(eDisplayId)))
    {
      continue;
    }
    else 
    {
      sRenderLogoConfig.uDisplayId = eDisplayId;
    }

    if (EFI_SUCCESS != (eStatus = DisplayRenderLogoInternal(&sRenderLogoConfig)))
    {
      DEBUG((EFI_D_WARN, "DisplayUtils: Display(%d) Render Logo failed with Status(%d)!\n", sRenderLogoConfig.uDisplayId, eStatus));
    }
  }

  MDP_LOG_FUNC_EXIT("Display_Utils_RenderLogo", 0x0);

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: Display_Utils_SetMode()
*/
/*!
* \brief
*   Display Utils Protocol to set display mode
*
  @param[in]  DisplayId                 display id, can be either primary, secondary or external
  @param[in]  ModeNumber                Abstraction that defines the current video mode.
  @param[in]  Flags                     More info
*
* \retval EFI_STATUS
* EFI_SUCCESS                   : Function returned successfully.
* EFI_INVALID_PARAMETER         : Parameter passed is incorrect.
* EFI_UNSUPPORTED               : Parameter passed is not supported.
* EFI_DEVICE_ERROR              : Physical device reported an error.
*
****************************************************************************/
EFI_STATUS
Display_Utils_SetMode(
  IN  UINT32           DisplayId,
  IN  UINT32           ModeNum,
  IN  UINT32           Flags)
{
    EFI_STATUS    eStatus        = EFI_NOT_FOUND;


     switch(DisplayId)
     {
       case MDP_DISPLAY_EXTERNAL:
          eStatus = DisplayDxe_SetModeExt(DisplayId, ModeNum, Flags);
          break;
       default:
          DEBUG((EFI_D_WARN, "DisplayUtils: DisplayId=%d NOT Supported\n", DisplayId));
          break;
     }

    return eStatus;
}


/****************************************************************************
*
** FUNCTION: Display_Utils_SetVariable()
*/
/*!
* \brief
*   Display Utils Protocol to set the variable value
*
  @param[in]  pVariableName              The variable name that need to set.
  @param[in]  pVariableValue             The variable value.
  @param[in]  uDataLength                The length of the variable value.
  @param[in]  uFlags                     The flag to set variable.
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS Display_Utils_SetVariable (CHAR16 *pVariableName, UINT8 *pVariableValue, UINTN uDataLength, UINTN uFlags)
{
  EFI_STATUS eStatus = EFI_SUCCESS;

  if (RETAIL)
  {
    // Do nothing here but just return EFI_NOT_FOUND for RETAIL to indicate nothing to be set.
    eStatus = EFI_NOT_FOUND;
  }
  else if ((NULL == pVariableName) ||
           (NULL == pVariableValue))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: variable name or value buffer is NULL!\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else if ((StrLen(pVariableName) > (DISP_FILE_NAME_MAX_SIZE - StrLen(DISP_FILE_EXT) - 1)) ||
           (uDataLength           >  DISP_VARIABLE_VALUE_MAX_SIZE))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: variable name or value size is out of limit!\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else if (EFI_NOT_FOUND != (eStatus = MountFatPartition(DISP_LOGFS)) && eStatus != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: mount logfs system failed with status %d!\n", eStatus));
  }
  else
  {
    CHAR16      DisplayConfigFile[DISP_FILE_NAME_MAX_SIZE];
    UINT32      uFileNameSize   = 0;
    UINTN       uWriteDataSize  = uDataLength * sizeof (UINT8);

    uFileNameSize = StrLen(pVariableName) * sizeof (CHAR16);

    MDP_OSAL_MEMZERO(DisplayConfigFile, sizeof(DisplayConfigFile));
    MDP_OSAL_MEMCPY(DisplayConfigFile, pVariableName, uFileNameSize);

    StrCatS(DisplayConfigFile, DISP_FILE_NAME_MAX_SIZE, DISP_FILE_EXT);

    /* Clear the configuration file before writing it if already exists */
    DeleteFile (DisplayConfigFile,
                NULL,
                NULL,
                DISP_LOGFS,
                TRUE,
                NULL);

    if ((NULL != pVariableValue) &&
        (0    != uWriteDataSize))
    {
      eStatus = WriteFile (DisplayConfigFile,
                           NULL,
                           NULL,
                           DISP_LOGFS,
                           TRUE,
                           NULL,
                           &uWriteDataSize,
                           0,
                           pVariableValue,
                           uWriteDataSize);

      if(eStatus != EFI_SUCCESS)
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Saving variable(%s) failed (status:%d)\n", pVariableName, eStatus));
      }
    }
  }

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: Display_Utils_GetVariable()
*/
/*!
* \brief
*   Display Utils Protocol to get the variable value
*
  @param[in]   pVariableName              The variable name that need to get.
  @param[out]  pVariableValue             The variable value.
  @param[out]  pDataLength                The length of the variable value.
  @param[in]   uFlags                     The flag to get variable.
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS Display_Utils_GetVariable(CHAR16 *pVariableName, UINT8 *pVariableValue, UINTN *pDataLength, UINTN uFlags)
{
  EFI_STATUS  eStatus = EFI_SUCCESS;

  if (RETAIL)
  {
    // Do nothing here but just return EFI_NOT_FOUND for RETAIL to indicate nothing to be read.
    eStatus = EFI_NOT_FOUND;
  }
  else if ((NULL == pVariableName)  ||
           (NULL == pVariableValue) ||
           (NULL == pDataLength))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: variable name or value buffer is NULL!\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else if (StrLen(pVariableName) > (DISP_FILE_NAME_MAX_SIZE - StrLen(DISP_FILE_EXT) - 1))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: variable name is too long!\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else if (EFI_NOT_FOUND != (eStatus = MountFatPartition(DISP_LOGFS)) && eStatus != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: mount logfs system failed with status %d!\n", eStatus));
  }
  else
  {
    CHAR16      DisplayConfigFile[DISP_FILE_NAME_MAX_SIZE];
    UINT32      uFileNameSize  = 0;
    UINTN       uReadDataSize  = (*pDataLength) * sizeof (UINT8);

    uFileNameSize = StrLen(pVariableName) * sizeof (CHAR16);

    MDP_OSAL_MEMZERO(DisplayConfigFile, sizeof(DisplayConfigFile));
    MDP_OSAL_MEMCPY(DisplayConfigFile, pVariableName, uFileNameSize);

    StrCatS(DisplayConfigFile, DISP_FILE_NAME_MAX_SIZE, DISP_FILE_EXT);

    eStatus = ReadFile (DisplayConfigFile,
                        NULL,
                        NULL,
                        DISP_LOGFS,
                        TRUE,
                        NULL,
                        &uReadDataSize,
                        0,
                        pVariableValue,
                        uReadDataSize);

    *pDataLength = AsciiStrLen((CHAR8 *)pVariableValue);

    if ((EFI_NOT_FOUND == eStatus)     ||
        (0             == *pDataLength))
    {
      // Variable not found
      eStatus = EFI_NOT_FOUND;
    }
    else if(EFI_SUCCESS != eStatus)
    {
      DEBUG((EFI_D_WARN, "DisplayUtils: Reading variable(%s) failed (status:%d)\n", pVariableName, eStatus));
    }
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: Display_Utils_StorePLLCodes()
*/
/*!
* \brief
*   Store pll codes to memory (legacy way) and boot service variable
*
* \retval EFI_STATUS
*
****************************************************************************/
void Display_Utils_StorePLLCodes(void)
{
  MDP_PLLCodesInfo        sPllCodesInfo[MDP_MAX_NUM_DSI_DEVICE];
  MDP_PLLCodesIDEntryInfo sPllCodesIDEntry[MDP_DISPLAY_PLL_CODEID_MAX];
  UINT32                  uPllCodesIDCount = 0;
  UINT32                  i;

  MDP_OSAL_MEMSET(sPllCodesInfo, 0, sizeof(sPllCodesInfo));

  /* Gather pll codes for all devices here */
  for (i = 0; i < MDP_MAX_NUM_DSI_DEVICE; i++)
  {
    if (MDP_STATUS_OK == DSIDriver_GetCalibrationCodes(i, &sPllCodesInfo[i]))
    {
      sPllCodesIDEntry[uPllCodesIDCount].uDeviceID = i;
      sPllCodesIDEntry[uPllCodesIDCount].sPllCodesInfo = sPllCodesInfo[i];
      uPllCodesIDCount++;
    }
  }

  /* Construct PLL codes data and save to boot service variable*/
  if ((0             != uPllCodesIDCount) &&
      (MDP_STATUS_OK != Display_Utils_SavePLLCodes(DISPVAR_DSI_PLLCODES_INFO, sPllCodesIDEntry, uPllCodesIDCount)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayUtils: Fail to save pll codes to boot service variable\n");
  }
}


/****************************************************************************
*
** FUNCTION: Display_Utils_GetLogoConfig()
*/
/*!
* \brief
*   Display Utils to get the logo configured for display.
*
  @param[in]   eDisplayId                     Display id.
*
* \retval CHAR8*
*
****************************************************************************/
CHAR8* Display_Utils_GetLogoConfig(RenderLogoParamsType *pRenderLogoParams)
{
  Display_UtilsContextType  *pDisplayContext = GET_DISPLAY_CONTEXT();
  UINT32                     uLogoIndex      = 0;
  UINT32                     uConfigValue    = 0;
  MDP_Display_IDType         eDisplayId      = MDP_DISPLAY_PRIMARY;
  CHAR8                     *pLogoIndexAscii = NULL;

  // Check if pRenderLogoParams is NULL or eDisplayId is out of range.
  if ((NULL                          == pRenderLogoParams) ||
      (pRenderLogoParams->eDisplayId >= FRAMEBUFFER_MAX_NUMBER))
  {
    eDisplayId = MDP_DISPLAY_PRIMARY;
  }
  else
  {
    eDisplayId = pRenderLogoParams->eDisplayId;
  }

  switch (eDisplayId)
  {
  case MDP_DISPLAY_SECONDARY:
    pLogoIndexAscii = DISPVAR_SECONDARY_LOGO_INDEX_ASCII;
    break;

  case MDP_DISPLAY_PRIMARY:
  default:
    pLogoIndexAscii = DISPVAR_PRIMARY_LOGO_INDEX_ASCII;
    break;
  }

  MDP_GetConfigValue(pLogoIndexAscii, &uConfigValue);

  if ((uConfigValue == 0) || 
      (uConfigValue  > MDP_MAX_LOGO_FILE_INDEX))
  {
    // Set default logo1.bmp if uLogoIndex is 0 or out of range.
    uLogoIndex = 1;
  }
  else
  {
    uLogoIndex = uConfigValue;
  }

  AsciiSPrint (pDisplayContext->aLogoConfig[eDisplayId], sizeof(pDisplayContext->aLogoConfig[0]), "logo%d.bmp", uLogoIndex);

  return pDisplayContext->aLogoConfig[eDisplayId];
}


/****************************************************************************
*
** FUNCTION: Display_Utils_IsDisplayDisabled()
*/
/*!
* \brief
*   Display Utils to check whether the display is in disabled state
*
  @param[in]   eDisplayId                     Display id.
*
* \retval BOOLEAN
*
****************************************************************************/
BOOLEAN Display_Utils_IsDisplayDisabled(MDP_Display_IDType eDisplayId)
{
  BOOLEAN                      bDisplayDisabled                     = FALSE;
  Display_UtilsContextType    *pDisplayContext                      = GET_DISPLAY_CONTEXT();
  EFI_DISPLAY_TYPE             aDisplayTypeMapping[MDP_DISPLAY_MAX] =
  {
    EFI_DISPLAY_TYPE_PRIMARY,       // MDP_DISPLAY_PRIMARY
    EFI_DISPLAY_TYPE_SECONDARY,     // MDP_DISPLAY_SECONDARY
    EFI_DISPLAY_TYPE_EXTERNAL,      // MDP_DISPLAY_EXTERNAL
    EFI_DISPLAY_TYPE_EXTERNAL2,     // MDP_DISPLAY_EXTERNAL2
    EFI_DISPLAY_TYPE_EXTERNAL3,     // MDP_DISPLAY_EXTERNAL3
    EFI_DISPLAY_TYPE_EXTERNAL4,     // MDP_DISPLAY_EXTERNAL4
    EFI_DISPLAY_TYPE_EXTERNAL5,     // MDP_DISPLAY_EXTERNAL5
    EFI_DISPLAY_TYPE_EXTERNAL6      // MDP_DISPLAY_EXTERNAL6
  };

  if (0 !=  pDisplayContext->sDisabledDisplayList.uNumOfDisplays)
  {
    UINT32 uIndex;

    for (uIndex = 0; uIndex < pDisplayContext->sDisabledDisplayList.uNumOfDisplays; uIndex++)
    {
      if (eDisplayId >= MDP_DISPLAY_MAX)
      {
        // eDisplayId is out of range, only return FALSE by default for bDisplayDisabled.
        bDisplayDisabled = FALSE;
        break;
      }
      else if (aDisplayTypeMapping[eDisplayId] == pDisplayContext->sDisabledDisplayList.aDisabledDisplays[uIndex])
      {
        bDisplayDisabled = TRUE;
        break;
      }
    }
  }

  return bDisplayDisabled;
}

/**
  Calculate display run time(include internal execution time and total time) when exit

  @param  pDxeExecTime              Pointer (non NULL) to display internal driver execution time.
  @param  pDxeTotalTime             Pointer (non NULL) to display total run time.
**/
void Display_Utils_BootExit(uint32 *pDxeExecTime, uint32 *pDxeTotalTime)
{
  uint32 uCount = 0;

  if ((NULL != gProfileLog) &&
      (NULL != pDxeExecTime) &&
      (NULL != pDxeTotalTime))
  {
    if (gProfileLog->uEntryCount > MDP_PROFILER_LOG_ENTRIES)
    {
      uCount = MDP_PROFILER_LOG_ENTRIES;
    }
    else
    {
      uCount = gProfileLog->uEntryCount;
    }

    if (0 == AsciiStrCmp("DisplayDxeInitialize", gProfileLog->aProfileLog[0].sFunctionName))
    {
      UINT32 uEntryIndex;
      UINT32 uEntryCount      = 0;
      UINT32 uExitCount       = 0;
      UINT32 uStart           = 0;

      /* Calculat display total runtime base on profile logs, since entry/exit are pairs,
       * when the entry count equal to exit count means this part is continuous and has ended
       */

      for (uEntryIndex = 0; uEntryIndex < uCount; uEntryIndex++)
      {
        if (gProfileLog->aProfileLog[uEntryIndex].uParams[0])
        {
          uEntryCount++;
        }
        else
        {
          uExitCount++;
        }

        if ((uEntryCount == uExitCount) &&
            (uStart < MDP_PROFILER_LOG_ENTRIES))
        {
          *pDxeExecTime += gProfileLog->aProfileLog[uEntryIndex].uTimeStamp - gProfileLog->aProfileLog[uStart].uTimeStamp;
          uEntryCount = 0;
          uExitCount  = 0;
          uStart = uEntryIndex + 1;
        }
      }

      *pDxeTotalTime = gProfileLog->aProfileLog[uCount - 1].uTimeStamp - gProfileLog->aProfileLog[0].uTimeStamp;
    }
  }
}

