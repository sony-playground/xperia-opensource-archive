/*=============================================================================

  File: MDPPlatformPanelConfig.c

  MDP platform specific functions

  Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <Protocol/EFITlmm.h>
#include "MDPPlatformLibPanelConfig.h"
#include "MDPSystem.h"
#include "DisplayUtils.h"


/*===========================================================================
                        Defines
===========================================================================*/
#define HDK_DISP_DSI_STATUS_GPIO    143         /* GPIO LOW: DSI panel, HIGH: HDMI */

/*===========================================================================
                        Enumerations
===========================================================================*/

/* Column type of config in the PanelConfig.csv file
 */
typedef enum
{
  CONFIGFILE_COLUMN_NAME = 0,
  CONFIGFILE_COLUMN_DTLABEL,
  CONFIGFILE_COLUMN_KERNELMODE,
  CONFIGFILE_COLUMN_MAX
} ConfigFileColumnType;

/* Mode configs
 */
typedef enum
{
  MDP_MODE_SINGLEDSI0 = 0,
  MDP_MODE_SINGLEDSI1,
  MDP_MODE_DUALDSI,
  MDP_MODE_DUALDSI_PPSPLIT,
} ModeConfigType;

/* HW configs
 */
typedef enum
{
  HW_CONFIG_DEFAULT = 0,
  HW_CONFIG_DEFAULT_BRIGHT_V2,
  HW_CONFIG_DEFAULT_NOBRIGHT_DEFAULT_GPIO,
  HW_CONFIG_DEFAULT_NOBRIGHT_SEC_GPIO,
  HW_CONFIG_DEFAULT_BRIGHT_V2_SEC_GPIO,
#ifdef FEATURE_XBOOT
#include "XMDPPlatformLibModeConfigType.c"
#endif /* FEATURE_XBOOT */
} HwConfigType;

/* Panel config location
 */
typedef enum
{
  CONFIG_LOCATION_PHYSICAL_TABLE = 0,
  CONFIG_LOCATION_MAINFV,
  CONFIG_LOCATION_IMAGEFVB,
  CONFIG_LOCATION_MAX
} ConfigLocationType;


/*===========================================================================
 Local helper function
 ===========================================================================*/
static EFI_STATUS GetPanelConfigFromFile(CHAR8 *pPanelName, UINT8 *pFileBuf, UINT32 uFileBufLen, PanelConfigType *pOutPanelConfig);
static EFI_STATUS LookUpPanel(MDP_Display_IDType eDisplayId, ConfigLocationType eLocation, CHAR8 *pPanelName);


/*===========================================================================
 Local Configuration Definitions
 ===========================================================================*/

/* Config data for different display devices
*/
PanelConfigType asPanelConfig[MDP_DISPLAY_MAX];

/* Default display panel gpio information
 */
static MDPPlatformPanelGpioType sDefaultGpioConfig =
{
  133,            /* Display reset gpio */
  86,             /* Display te gpio */
  1,              /* Display te gpio function select */
};

/* Secondary display panel gpio information
 */
static MDPPlatformPanelGpioType sSecondaryGpioConfig =
{
  137,            /* Display reset gpio */
  87,             /* Display te gpio */
  1,              /* Display te gpio function select */
};

/* Mode configuration table that a panel can select from
 */
static MDPPlatformModeInfoType sModeConfig[] =
{
  /* MDP_MODE_SINGLEDSI0 */
  {
    DISP_INTF_DSI,
    DISP_MODE_SINGLE_DSI,
  },
  /* MDP_MODE_SINGLEDSI1 */
  {
    DISP_INTF_DSI,
    DISP_MODE_SINGLE_DSI|DISP_MODE_USE_DSI1,
  },
  /* MDP_MODE_DUALDSI */
  {
    DISP_INTF_DSI,
    DISP_MODE_DUAL_DSI,
  },
  /* MDP_MODE_DUALDSI_PPSPLIT */
  {
    DISP_INTF_DSI,
    DISP_MODE_DUAL_DSI|DISP_MODE_PING_PONG_SPLIT,
  },
};

/* HW configuration table that a panel can select from
 */
static MDPPlatformHardwareConfig sHwConfig[] =
{
  MDP_PLATFORM_CREATE_PANEL_HW_CONFIG_BRIGHTLEVEL(Panel_Default_Brightness_Level),                              /* HW_CONFIG_DEFAULT */
  MDP_PLATFORM_CREATE_PANEL_HW_CONFIG_BRIGHTLEVEL(Panel_Default_V2_Brightness_Level),                           /* HW_CONFIG_DEFAULT_BRIGHT_V2 */
  MDP_PLATFORM_CREATE_PANEL_HW_CONFIG_GPIO(&sDefaultGpioConfig),                                                /* HW_CONFIG_DEFAULT_NOBRIGHT_DEFAULT_GPIO */
  MDP_PLATFORM_CREATE_PANEL_HW_CONFIG_GPIO(&sSecondaryGpioConfig),                                              /* HW_CONFIG_DEFAULT_NOBRIGHT_SEC_GPIO */
  MDP_PLATFORM_CREATE_PANEL_HW_CONFIG_BRIGHTLEVEL_GPIO(Panel_Default_V2_Brightness_Level, &sSecondaryGpioConfig) /* HW_CONFIG_DEFAULT_BRIGHT_V2_SEC_GPIO  */
#ifdef FEATURE_XBOOT
#include "XMDPPlatformLib_sHwConfigTable.c"
#endif /* FEATURE_XBOOT */
};

/* Panel config for physical panel
*/
static PhysicalPanelConfigType sPhysicalPanelConfigTable[] =
{
  {"sharp_4k_dsc_cmd",                  "Panel_sharp_4k_dsc_cmd.xml",                             "qcom,mdss_dsi_sharp_4k_dsc_cmd:",                             &sModeConfig[MDP_MODE_DUALDSI],    &sHwConfig[HW_CONFIG_DEFAULT]},
  {"sharp_4k_dsc_vid",                  "Panel_sharp_4k_dsc_vid.xml",                             "qcom,mdss_dsi_sharp_4k_dsc_video:",                           &sModeConfig[MDP_MODE_DUALDSI],    &sHwConfig[HW_CONFIG_DEFAULT]},
  {"truly_wqxga_dsc_cmd",               "Panel_truly_wqxga_dsc_cmd.xml",                          "qcom,mdss_dsi_nt35597_dsc_cmd_truly:",                        &sModeConfig[MDP_MODE_SINGLEDSI1], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"truly_wqxga_dsc_vid",               "Panel_truly_wqxga_dsc_vid.xml",                          "qcom,mdss_dsi_nt35597_dsc_video_truly:",                      &sModeConfig[MDP_MODE_SINGLEDSI1], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"truly_wqxga_dual_cmd",              "Panel_truly_wqxga_dual_cmd.xml",                         "qcom,mdss_dsi_nt35597_truly_wqxga_cmd:",                      &sModeConfig[MDP_MODE_DUALDSI],    &sHwConfig[HW_CONFIG_DEFAULT]},
  {"truly_wqxga_dual_vid",              "Panel_truly_wqxga_dual_vid.xml",                         "qcom,mdss_dsi_nt35597_wqxga_video_truly:",                    &sModeConfig[MDP_MODE_DUALDSI],    &sHwConfig[HW_CONFIG_DEFAULT]},
  {"boe_amoled_wqhd_dsc_cmd",           "Panel_boe_amoled_wqhd_dsc_cmd.xml",                      "qcom,mdss_dsi_sw43404_amoled_wqhd_cmd:",                      &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"boe_amoled_wqhd_dsc_vid",           "Panel_boe_amoled_wqhd_dsc_vid.xml",                      "qcom,mdss_dsi_sw43404_amoled_wqhd_video:",                    &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"boe_amoled_fhd_dsc_cmd",            "Panel_boe_amoled_fhd_dsc_cmd.xml",                       "qcom,mdss_dsi_sw43404_fhd_plus_cmd:",                         &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"sharp_1080p_cmd",                   "Panel_sharp_1080p_cmd.xml",                              "qcom,mdss_dsi_sharp_1080p_cmd:",                              &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"truly_1080p_cmd",                   "Panel_truly_1080p_cmd.xml",                              "qcom,mdss_dsi_nt35695b_truly_fhd_cmd:",                       &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"truly_1080p_vid",                   "Panel_truly_1080p_vid.xml",                              "qcom,mdss_dsi_nt35695b_truly_fhd_video:",                     &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"nt36860_wqhd_dsc_cmd",              "Panel_nt36860_wqhd_dsc_cmd.xml",                         "qcom,mdss_dsi_nt36860_dsc_cmd:",                              &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"nt36860_wqhd_dsc_vid",              "Panel_nt36860_wqhd_dsc_vid.xml",                         "qcom,mdss_dsi_nt36860_dsc_vid:",                              &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"pri_sharp_cmd",                     "Panel_primary_sharp_1080p_cmd.xml",                      "qcom,mdss_dsi_sharp_1080p_cmd:",                              &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_NOBRIGHT_DEFAULT_GPIO]},
  {"sec_truly_cmd",                     "Panel_secondary_truly_1080p_cmd.xml",                    "qcom,mdss_dsi_nt35695b_truly_fhd_cmd:",                       &sModeConfig[MDP_MODE_SINGLEDSI1], &sHwConfig[HW_CONFIG_DEFAULT_NOBRIGHT_SEC_GPIO]},
  {"sec_truly_vid",                     "Panel_secondary_truly_1080p_vid.xml",                    "qcom,mdss_dsi_nt35695b_truly_fhd_video:",                     &sModeConfig[MDP_MODE_SINGLEDSI1], &sHwConfig[HW_CONFIG_DEFAULT_NOBRIGHT_SEC_GPIO]},
  {"r66451_60hz_fhd_dsc_cmd",           "Panel_r66451_60hz_fhd_plus_dsc_cmd.xml",                 "qcom,mdss_dsi_visionox_r66451_fhd_plus_cmd:",                 &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"r66451_60hz_fhd_dsc_vid",           "Panel_r66451_60hz_fhd_plus_dsc_vid.xml",                 "qcom,mdss_dsi_visionox_r66451_fhd_plus_vid:",                 &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"r66451_120hz_fhd_dsc_cmd",          "Panel_r66451_120hz_fhd_plus_dsc_cmd.xml",                "qcom,mdss_dsi_visionox_r66451_fhd_plus_cmd:config2:timing2:", &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"r66451_120hz_fhd_dsc_vid",          "Panel_r66451_120hz_fhd_plus_dsc_vid.xml",                "qcom,mdss_dsi_visionox_r66451_fhd_plus_video:",               &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"r66451_60hz_fhd_dsc_cmd_cphy",      "Panel_r66451_60hz_fhd_plus_dsc_cmd_cphy.xml",            "qcom,mdss_dsi_r66451_fhd_plus_cphy_cmd:",                     &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"r66451_120hz_fhd_dsc_cmd_cphy",     "Panel_r66451_120hz_fhd_plus_dsc_cmd_cphy.xml",           "qcom,mdss_dsi_r66451_fhd_plus_120hz_cphy_cmd:",               &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"r66451_sec_120hz_fhd_dsc_cmd_cphy", "Panel_secondary_r66451_120hz_fhd_plus_dsc_cmd_cphy.xml", "qcom,mdss_dsi_r66451_fhd_plus_120hz_cphy_cmd:",               &sModeConfig[MDP_MODE_SINGLEDSI1], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2_SEC_GPIO]},
  {"r66451_144hz_fhd_dsc_cmd_cphy",     "Panel_r66451_144hz_fhd_plus_dsc_cmd_cphy.xml",           "qcom,mdss_dsi_r66451_fhd_plus_144hz_cphy_cmd:",               &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"r66451_144hz_fhd_dsc_vid_cphy",     "Panel_r66451_144hz_fhd_plus_dsc_vid_cphy.xml",           "qcom,mdss_dsi_r66451_fhd_plus_cphy_144hz_vid:",               &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"r66451_sec_fhd_dsc_sync_cmd",       "Panel_secondary_r66451_fhd_plus_dsc_cmd.xml",            "qcom,mdss_dsi_visionox_r66451_fhd_plus_sync_cmd:",            &sModeConfig[MDP_MODE_SINGLEDSI1], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2_SEC_GPIO]},
  {"r66451_sec_120hz_fhd_dsc_cmd",      "Panel_secondary_r66451_120hz_fhd_plus_dsc_cmd.xml",      "qcom,mdss_dsi_visionox_r66451_fhd_plus_sync_cmd:",            &sModeConfig[MDP_MODE_SINGLEDSI1], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2_SEC_GPIO]},
  {"dsi_dual_nt35597_truly_sl_cmd",     "Panel_truly_wqxga_cmd_splitlink.xml",                    "qcom,mdss_dsi_nt35597_truly_sl_wqxga_cmd:",                   &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"r66451_120hz_fhd_dsc_cmd_demura",   "Panel_r66451_120hz_fhd_plus_dsc_cmd_demura.xml",         "qcom,mdss_dsi_visionox_r66451_fhd_plus_cmd:config2:timing2:", &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"vtdr6130_144hz_fhd_dsc_cmd",        "Panel_vtdr6130_144hz_fhd_plus_dsc_cmd.xml",              "qcom,mdss_dsi_vtdr6130_fhd_plus_cmd:config0:timing0:",        &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"vtdr6130_144hz_fhd_dsc_vid",        "Panel_vtdr6130_144hz_fhd_plus_dsc_vid.xml",              "qcom,mdss_dsi_vtdr6130_fhd_plus_vid:",                        &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"vtdr6130_60hz_fhd_dsc_cmd",         "Panel_vtdr6130_60hz_fhd_plus_dsc_cmd.xml",               "qcom,mdss_dsi_vtdr6130_fhd_plus_cmd:config3:timing3:",        &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"vtdr6130_60hz_fhd_dsc_vid",         "Panel_vtdr6130_60hz_fhd_plus_dsc_vid.xml",               "qcom,mdss_dsi_vtdr6130_fhd_plus_vid:",                        &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"sharp_qhd_plus_dsc_cmd",            "Panel_sharp_120hz_qhd_plus_dsc_cmd.xml",                 "qcom,mdss_dsi_sharp_qhd_plus_dsc_cmd:",                       &sModeConfig[MDP_MODE_SINGLEDSI1], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"sharp_qhd_plus_dsc_vid",            "Panel_sharp_120hz_qhd_plus_dsc_vid.xml",                 "qcom,mdss_dsi_sharp_qhd_plus_dsc_video:",                     &sModeConfig[MDP_MODE_SINGLEDSI1], &sHwConfig[HW_CONFIG_DEFAULT]},
  {"vtdr6130_sec_144hz_fhd_dsc_cmd",    "Panel_secondary_vtdr6130_144hz_fhd_plus_dsc_cmd.xml",    "qcom,mdss_dsi_vtdr6130_fhd_plus_cmd:config0:timing0:",        &sModeConfig[MDP_MODE_SINGLEDSI1], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2_SEC_GPIO]},
  {"vtdr6130_sec_144hz_fhd_dsc_vid",    "Panel_secondary_vtdr6130_144hz_fhd_plus_dsc_vid.xml",    "qcom,mdss_dsi_vtdr6130_fhd_plus_vid:",                        &sModeConfig[MDP_MODE_SINGLEDSI1], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2_SEC_GPIO]},
  {"vtdr6130_144hz_fhd_dsc_cmd_demura", "Panel_vtdr6130_144hz_fhd_plus_dsc_cmd_demura.xml",       "qcom,mdss_dsi_vtdr6130_fhd_plus_cmd:config0:timing0:",        &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
  {"vtdr6130_144hz_fhd_dsc_cmd_rfi",    "Panel_vtdr6130_144hz_fhd_plus_dsc_cmd_rfi.xml",          "qcom,mdss_dsi_vtdr6130_fhd_plus_cmd:config0:timing0:",        &sModeConfig[MDP_MODE_SINGLEDSI0], &sHwConfig[HW_CONFIG_DEFAULT_BRIGHT_V2]},
#ifdef FEATURE_XBOOT
#include "XMDPPlatformLib_sPhysicalPanelConfigTable.c"
#endif /* FEATURE_XBOOT */
};


/***************************************************************************
Dynamic panel detect list for dphy panels:
    -- first entry contains default panel
***************************************************************************/
static PlatformDSIDetectParams uefiDphyPanelList[] = {
    // Panel #0 - VTDR6130 FHD+ single dsc Command Mode Panel (1080x2400 24bpp)
    {
      "vtdr6130_144hz_fhd_dsc_cmd",
      0x06,                                                  // uCmdType
      0x05,                                                  // total number of retry on failures
      {
        {{0x70, 0x00},                                       // address to read ID1
        {0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}     // expected readback
        },
      },
      0,                                                     // Lane remap order {0, 1, 2, 3}
      0                                                      // uFlags
    },
#ifdef FEATURE_XBOOT
#include "XMDPPlatformLib_uefiDphyPanelList.c"
#endif /* FEATURE_XBOOT */
};

/***************************************************************************
Dynamic panel detect list for cphy panels:
    -- first entry contains default panel
***************************************************************************/
static PlatformDSIDetectParams uefiCphyPanelList[] = {
    // Panel #0 - R66451 fhd single dsc Command Mode Cphy Panel (1080x2340 24bpp)
    {
      "r66451_144hz_fhd_dsc_cmd_cphy",
      0x06,                                                  // uCmdType
      0x05,                                                  // total number of retry on failures
      {
        {{0xDA, 0x00},                                       // address to read ID1
        {0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}     // expected readback
        },
      },
      0,                                                     // Lane remap order {0, 1, 2, 3}
      0                                                      // uFlags
    },
};


/*===========================================================================
Function Definitions
===========================================================================*/

/**********************************************************************************************
*
* FUNCTION: MDPPlatformGetPanelXmlConfig()
*
* DESCRIPTION:
*   The function can get the panel xml configurations.
*
***********************************************************************************************/
MDP_Status MDPPlatformGetPanelXmlConfig (MDP_Display_IDType eDisplayId, MDPPlatformPanelInfo *pPlatformPanel)
{
  MDP_Status                     eStatus                   = MDP_STATUS_OK;
  UINT32                         uRetSize                  = 0;
  UINT8                         *pFileBuffer               = NULL;
  UINT32                         uBufferSize               = 0;
  MDPPlatformPanelFunctionTable *pMDPSupportPanelFunctions = MDP_GET_PANELFUNC(eDisplayId);
  PanelConfigType               *pPanelConfig              = GET_PANEL_CONFIG(eDisplayId);

  if ((NULL == pPlatformPanel)            ||
      (NULL == pMDPSupportPanelFunctions) ||
      (NULL == pPanelConfig))
  {
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (pPanelConfig->ePanelType != MDPPLATFORM_PANEL_PHYSICAL)
  {
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (EFI_SUCCESS != MDP_Display_LoadFile(pMDPSupportPanelFunctions->pPanelXml,
                                               &pFileBuffer,
                                               &uBufferSize,
                                               &uRetSize,
                                               0))
  {
    eStatus = MDP_STATUS_FAILED;
    DEBUG((EFI_D_WARN, "MDPPlatformGetPanelXmlConfig: MDP_Display_LoadFile fail\n"));
  }
  else if (NULL != pFileBuffer)
  {
    pPlatformPanel->pPanelXMLConfig = (int8 *)pFileBuffer;
    pPlatformPanel->uConfigSize     = uRetSize;
  }
  else
  {
    /* Read null from the file, just return with fail status */
    eStatus = MDP_STATUS_FAILED;
    DEBUG((EFI_D_WARN, "MDPPlatformGetPanelXmlConfig: MDP_Display_LoadFile fail\n"));
  }

  return eStatus;
}

/**********************************************************************************************
*
* FUNCTION: MDPPlatformGetPanelList()
*
* DESCRIPTION:
* The function returns the pointer and array size of uefiDphyPanelList or uefiCphyPanelList
*
***********************************************************************************************/
VOID MDPPlatformGetPanelList(MDPDisplayAutoDetectType eAutoDetect, PlatformDSIDetectParams **pPanelList, UINT32 *pListLen, UINT32 *pPanelIndex)
{
  if ((NULL == pPanelList) ||
      (NULL == pListLen))
  {
    DEBUG((EFI_D_WARN, "MDPPlatformGetPanelList: pPanelList or pListLen is NULL\n"));
  }
  else if (MDP_DISPLAY_AUTODETECT_MIPI_CPHY == eAutoDetect)
  {
    if (NULL == pPanelIndex)
    {
      *pPanelList = (PlatformDSIDetectParams*)uefiCphyPanelList;
      *pListLen   = PANEL_LIST_LENGTH(uefiCphyPanelList);
    }
    else
    {
      UINT32 uIndex = (*pPanelIndex < PANEL_LIST_LENGTH(uefiCphyPanelList)) ? *pPanelIndex : 0;

      *pPanelList   = (PlatformDSIDetectParams*)(&uefiCphyPanelList[uIndex]);
      *pListLen     = 1;
    }
  }
  else
  {
    if (NULL == pPanelIndex)
    {
#ifdef FEATURE_XBOOT
      *pPanelList = (PlatformDSIDetectParams*)&uefiDphyPanelList[PANEL_LIST_LENGTH(uefiDphyPanelList)-1]; // Panel ## - Dummy Panel for PanelId Detection
#else /* !FEATURE_XBOOT */
      *pPanelList = (PlatformDSIDetectParams*)uefiDphyPanelList;
#endif /* !FEATURE_XBOOT */
      *pListLen   = PANEL_LIST_LENGTH(uefiDphyPanelList);
    }
    else
    {
      UINT32 uIndex = (*pPanelIndex < PANEL_LIST_LENGTH(uefiDphyPanelList)) ? *pPanelIndex : 0;

      *pPanelList   = (PlatformDSIDetectParams*)(&uefiDphyPanelList[uIndex]);
      *pListLen     = 1;
    }
  }
}

/**********************************************************************************************
*
* FUNCTION: MDPPlatformValidPanelName()
*
* DESCRIPTION:
*   Check whether a panel name is valid or not
*
***********************************************************************************************/
BOOLEAN MDPPlatformValidPanelName(CHAR8 *pPanelName)
{
  BOOLEAN bPanelEmpty = FALSE;

  if ((NULL == pPanelName) ||
      ('\0' == pPanelName[0]))
  {
    bPanelEmpty = TRUE;
  }

  return !bPanelEmpty;
}

/**********************************************************************************************
*
* FUNCTION: MDPPlatformSetPanelName()
*
* DESCRIPTION:
*   Set panel name to a specific name
*
***********************************************************************************************/
VOID MDPPlatformSetPanelName(CHAR8 *pBuf, CHAR8 *pPanelName)
{
  if ((NULL                       != pBuf)       &&
      (NULL                       != pPanelName) &&
      (DISPLAY_PANEL_NAME_MAX_LEN > AsciiStrLen(pPanelName)))
  {
    AsciiStrCpyS(pBuf, DISPLAY_PANEL_NAME_MAX_LEN, pPanelName);
  }
}

/**********************************************************************************************
*
* FUNCTION: MDPPlatformClearPanelName()
*
* DESCRIPTION:
*   Clear panel name
*
***********************************************************************************************/
VOID MDPPlatformClearPanelName(CHAR8 *pPanelName)
{
  if (NULL != pPanelName)
  {
    pPanelName[0] = '\0';
  }
}


/**********************************************************************************************
*
* FUNCTION: PanelCheckOverride()
*
* DESCRIPTION:
*   Check if the panel was overridden by ABL (apps boot loader) and if so check
*   if the overridden panel is supported by this platform.
*
*   This function has 1 of 3 outcomes
*   1. Panel is supported by both bootloader & kernel
*      - Set matching xmlconfig
*   2. panel is only supported in kernel
*      - Return dummyconfig, since sw rendering was already selected during initialization in this scenario
*   3. panel override is not set or the panel is not supported by bootloader & kernel
*      - Return FALSE to trigger panel detection
*
***********************************************************************************************/
static bool32 PanelCheckOverride(MDP_Display_IDType eDisplayId, MDPPlatformPanelInfo *pPlatformPanel, MDPPlatformInfo *pPlatformInfo)
{
  Display_UtilsParamsType* pDisplayOverride = Display_Utils_GetParams();
  bool32                   bRet             = FALSE;
  PanelOverrideParams *pPanelParams;

  if (MDP_DISPLAY_PRIMARY == eDisplayId)
  {
    pPanelParams = &pDisplayOverride->sPrimary;
  }
  else
  {
    pPanelParams = &pDisplayOverride->sSecondary;
  }

  if ((NULL == pDisplayOverride))
  {
    /* do nothing */
  }
  else if ((pDisplayOverride->uFlags & (DISP_MODE_SKIP_BOOTLOADER | DISP_MODE_PANEL_NONE)))
  {
    /* panel select "none" */
    bRet = TRUE;
    pPlatformInfo->bSWRender = TRUE;
  }
  else if (NULL != pPanelParams->pPanelConfig)
  {
    bRet = TRUE;

    if ((MDPPLATFORM_PANEL_BYPASS < pPanelParams->pPanelConfig->ePanelType) &&
        (MDPPLATFORM_PANEL_MAX    > pPanelParams->pPanelConfig->ePanelType))
    {
      MDPPlatformSetPanelName(pPlatformPanel->szName, pPanelParams->shortName);
    }

    if ((pDisplayOverride->uFlags               & DISP_MODE_SKIP_BOOTLOADER) ||
        (pPanelParams->pPanelConfig->ePanelType != MDPPLATFORM_PANEL_PHYSICAL))
    {
      pPlatformInfo->bSWRender = TRUE;
      DEBUG((EFI_D_WARN, "PanelCheckOverride: Panel override <%a> in skip mode\n", pPanelParams->shortName));
    }
    else
    {
      DEBUG((EFI_D_WARN, "PanelCheckOverride: Panel override <%a>\n", pPanelParams->shortName));
    }
  }
  else if (NULL == pPanelParams->pPanelConfig)
  {
    uint32 uShortNameLen = AsciiStrLen(pPanelParams->shortName);

    if(uShortNameLen > 0)
    {
      /* Panel not found in panel list, but shortName is not empty, still consider it as override*/
      MDPPlatformSetPanelName(pPlatformPanel->szName, pPanelParams->shortName);
      pPlatformInfo->bSWRender       = TRUE;
      bRet                           = TRUE;
    }
    else
    {
      /* Using default panel if shortName is empty, actually the logic will never enter this branch,
       * if shortName is empty, pDisplayOverride will be NULL.
       */
      pPlatformInfo->bSWRender       = FALSE;
      bRet                           = FALSE;
    }
  }

  return bRet;
}

/**********************************************************************************************
*
* FUNCTION: SetupSupportPanelFunctions()
*
* DESCRIPTION:
* Set up gpio/power/brightness functions for a specific display device
*
***********************************************************************************************/
static MDP_Status SetupSupportPanelFunctions(MDP_Display_IDType  eDisplayId)
{
  MDP_Status                     eStatus                   = MDP_STATUS_OK;
  MDPPlatformPanelFunctionTable *pMDPSupportPanelFunctions = MDP_GET_PANELFUNC(eDisplayId);
  PanelConfigType               *psPanelConfig             = GET_PANEL_CONFIG(eDisplayId);

  if ((NULL                       == pMDPSupportPanelFunctions) ||
      (NULL                       == psPanelConfig)             ||
      (MDPPLATFORM_PANEL_PHYSICAL != psPanelConfig->ePanelType))
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    pMDPSupportPanelFunctions->pPanel_PowerUp           = psPanelConfig->pPhysicalPanelConfig->pHwConfig->pPanel_PowerUp;
    pMDPSupportPanelFunctions->pPanel_PowerDown         = psPanelConfig->pPhysicalPanelConfig->pHwConfig->pPanel_PowerDown;
    pMDPSupportPanelFunctions->pPanel_Reset             = psPanelConfig->pPhysicalPanelConfig->pHwConfig->pPanel_Reset;
    pMDPSupportPanelFunctions->pPanel_Brightness_Enable = psPanelConfig->pPhysicalPanelConfig->pHwConfig->pPanel_Brightness_Enable;
    pMDPSupportPanelFunctions->pPanel_Brightness_Level  = psPanelConfig->pPhysicalPanelConfig->pHwConfig->pPanel_Brightness_Level;
    pMDPSupportPanelFunctions->pMDPPlatformPanelGpio    = psPanelConfig->pPhysicalPanelConfig->pHwConfig->pMDPPlatformPanelGpio;
    pMDPSupportPanelFunctions->pPanelXml                = psPanelConfig->pPhysicalPanelConfig->szXmlName;
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

/**********************************************************************************************
*
* FUNCTION: MDPPlatformSetupPanelConfig()
*
* DESCRIPTION:
* The function can get the display panel that is being used.
*
***********************************************************************************************/
MDP_Status MDPPlatformSetupPanelConfig(MDP_Display_IDType                 eDisplayId,
                                                    MDPPlatformPanelInfo *pPlatformPanel,
                                                    MDPPlatformInfo      *pPlatformInfo,
                                                    MDPPlatformInfo      *pMDPPlatformInfo)
{
  MDP_Status               eStatus         = MDP_STATUS_OK;
  PlatformDSIDetectParams *pPanelList      = NULL;
  uint32                   uPanelCnt       = 0;
  uint32                   uPanelID        = 0;
  PanelConfigType         *pPanelConfig    = NULL;

  if ((NULL == pPlatformPanel) ||
      (NULL == pPlatformInfo)  ||
      (NULL == pMDPPlatformInfo))
  {
    DEBUG((EFI_D_ERROR, "MDPPlatformSetupPanelConfig: The platform panel info is NULL\n"));
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (TRUE == pPlatformInfo->bPanelInitialized[eDisplayId])
  {
    // Panel has already been initialized once,
  }
  else
  {
    // Parse sub-revision specific info to determine the platform type
    if (TRUE == PanelCheckOverride(eDisplayId, pPlatformPanel, pPlatformInfo))
    {
      // Use configuration set by panel override
    }
    else if (TRUE == pPlatformInfo->bSWRender)
    {
      // Use dummy panel for sw rendering
      MDPPlatformClearPanelName(pPlatformPanel->szName);
    }
    else
    {
      uint32 uPanelIdOverride = PANEL_OVERRIDE_PANELID(pPlatformInfo->uPanelIdOverride);

      // Report the proper information depending on the display.
      switch (pPlatformInfo->sEFIPlatformType.platform)
      {
      case EFI_PLATFORMINFO_TYPE_CDP:
      case EFI_PLATFORMINFO_TYPE_MTP:
      case EFI_PLATFORMINFO_TYPE_QRD:
      {
        // Set default auto detection for dphy mode
        MDPDisplayAutoDetectType eAutoDetect = MDP_DISPLAY_AUTODETECT_MIPI_DPHY;

        // If the panel ID override is enabled and within range, force that panel configuration.
        if ((pPlatformInfo->uPanelIdOverride & PANEL_OVERRIDE_ENABLE_MASK) &&
            (uPanelIdOverride                < uPanelCnt))
        {
          MDPPlatformGetPanelList(eAutoDetect, &pPanelList, &uPanelCnt, &uPanelIdOverride);
          DEBUG((EFI_D_WARN, "DisplayDxe: Panel override enabled (Index: %d ID:0x%x)\n", PANEL_OVERRIDE_PANELID(pPlatformInfo->uPanelIdOverride), uPanelID));
        }
        else
        {
          // No override and it is not SW render - select default panel for power up and trigger dynamic detection
          MDPPlatformGetPanelList(eAutoDetect, &pPanelList, &uPanelCnt, NULL);
          pPlatformPanel->eAutoDetect = eAutoDetect;
        }

        MDPPlatformSetPanelName(pPlatformPanel->szName, pPanelList->szName);
        uPanelID                         = ((pPanelList->panelIdCommands[1].expectedReadback[0] << 8) |
                                              pPanelList->panelIdCommands[2].expectedReadback[0]);
        pPlatformPanel->uPanelId         = uPanelID;
        pPlatformInfo->uPrimaryPanelId   = uPanelID;
        break;
      }

      case EFI_PLATFORMINFO_TYPE_RCM:
        MDPPlatformSetPanelName(pPlatformPanel->szName, "sharp_qhd_plus_dsc_cmd");
        break;

      case EFI_PLATFORMINFO_TYPE_HDK:
      {
        TLMM_ValueType eGpioValue = GPIO_HIGH_VALUE;

        if ((EFI_SUCCESS    == GetDisplayGpioValue(HDK_DISP_DSI_STATUS_GPIO, &eGpioValue)) &&
            (GPIO_LOW_VALUE == eGpioValue))
        {
          MDPPlatformSetPanelName(pPlatformPanel->szName, "vtdr6130_144hz_fhd_dsc_cmd");
        }
        else
        {
          MDPPlatformClearPanelName(pPlatformPanel->szName);
        }
      }
      break;

      case EFI_PLATFORMINFO_TYPE_RUMI:
      default:
        MDPPlatformClearPanelName(pPlatformPanel->szName);
        break;
      }

      /* Enable SW Render if no valid panel name, and skip panel xml loading*/
      if ('\0' == pPlatformPanel->szName[0])
      {
        pPlatformInfo->bSWRender = TRUE;
      }
      /* Setup default panel config */
      else if (NULL == (pPanelConfig = MDPPlatformSelectPanelConfig(eDisplayId, pPlatformPanel->szName, &pPlatformInfo->bSWRender)))
      {
         DEBUG((EFI_D_WARN, "MDPPlatformSetupPanelConfig: MDPPlatformSelectPanelConfig failed\n"));
         eStatus = MDP_STATUS_NOT_SUPPORTED;
       }
       else
       {
         pPlatformInfo->bPanelInitialized[eDisplayId]  = TRUE;
         MDPPlatformSetPanelName(pPlatformPanel->szName, pPanelConfig->szName);
       }
     }
   }

   return eStatus;
}

/****************************************************************************
*
** FUNCTION: MDPPlatformSelectPanelConfig()
*/
/*!
* \brief
*   Helper function to select panel configuration by panel name
*
* \param [in]  eDisplayId   - Display ID
         [in]  pPanelName   - Panel name
         [out] bSWEnable    - Indicate whether SW render should be enabled
*
* \retval pointer to panel config for physical/simulation panel, otherwise return NULL
*
****************************************************************************/
PanelConfigType* MDPPlatformSelectPanelConfig(MDP_Display_IDType eDisplayId, CHAR8 *pPanelName, bool32 *bSWEnable)
{
  PanelConfigType *pRetConfig          = NULL;
  EFI_STATUS       eStatus             = EFI_SUCCESS;

  if ((MDP_DISPLAY_MAX  <  eDisplayId) ||
      (NULL             == pPanelName))
  {
    DEBUG((EFI_D_ERROR, "MDPPlatformSelectPanelConfig: Invalid parameter\n"));
  }
  else
  {
    if (EFI_SUCCESS != LookUpPanel(eDisplayId, CONFIG_LOCATION_PHYSICAL_TABLE, pPanelName))
    {
      if (EFI_SUCCESS != LookUpPanel(eDisplayId, CONFIG_LOCATION_MAINFV, pPanelName))
      {
        if (EFI_SUCCESS != LookUpPanel(eDisplayId, CONFIG_LOCATION_IMAGEFVB, pPanelName))
        {
          eStatus = EFI_UNSUPPORTED;
        }
      }
    }
  }

  /* In case physical/simulation panel found */
  if (EFI_SUCCESS == eStatus)
  {
    PanelConfigType *pPanelConfig = GET_PANEL_CONFIG(eDisplayId);

    /* Only setup support functions for physical panel */
    if (MDPPLATFORM_PANEL_PHYSICAL == pPanelConfig->ePanelType)
    {
      SetupSupportPanelFunctions(eDisplayId);
    }

    if (NULL != bSWEnable)
    {
      *bSWEnable = (MDPPLATFORM_PANEL_PHYSICAL == pPanelConfig->ePanelType) ? FALSE:TRUE;
    }

    /* Only return valid panel config */
    pRetConfig = pPanelConfig;
  }

  return pRetConfig;
}

/****************************************************************************
*
** FUNCTION: TrimLeft()
*/
/*!
* \brief
*   Helper function to skip blanks for a input buffer
*
* \param [in] pBuf        - input buffer that need skip blank at the head

*
* \retval
*
****************************************************************************/
static VOID TrimLeft(CHAR8 **pBuf)
{
  if (NULL != pBuf)
  {
    while((**pBuf != '\0') &&
          isblank(**pBuf))
    {
      (*pBuf)++;
    }
  }
}

/****************************************************************************
*
** FUNCTION: TrimRight()
*/
/*!
* \brief
*   Helper function to remove blanks from the end for a input buffer
*
* \param [in] pBuf        - input buffer that need remove blank from end

*
* \retval
*
****************************************************************************/
static VOID TrimRight(CHAR8 *pBuf)
{
  if (NULL != pBuf)
  {
    /* Remove blank from the end of the sub item */
    pBuf += (AsciiStrLen(pBuf) - 1);
    while(isblank(*pBuf))
    {
      pBuf--;
    }
    *(++pBuf) = '\0';
  }
}


/****************************************************************************
*
** FUNCTION: TrimQuote()
*/
/*!
* \brief
*   Helper function to remove Quotes
*
* \param [in/out] pBuf        - Buffer that needs trim quote
         [in]     uBufLen     - Buffer length
*
* \retval
*
****************************************************************************/
static VOID TrimQuote(CHAR8 *pBuf, UINT32 uBufLen)
{
  if ((NULL != pBuf) &&
      (1    < uBufLen))
  {
    CHAR8 *pFront = AsciiStrStr(pBuf, "\"");
    CHAR8 *pRear  = NULL;

    if (NULL != pFront)
    {
      pRear  = AsciiStrStr(pFront+1, "\"");
    }

    /* validate that two qotes exist */
    if ((NULL != pFront)    &&
        (NULL != pRear)     &&
        (pFront < pRear)    &&
        ((pRear - pFront) < uBufLen))
    {
      UINT32 i;
      UINT32 uLen;

      pFront++;
      *pRear = '\0';

      TrimLeft((CHAR8**)&pFront);
      TrimRight(pFront);

      uLen = AsciiStrLen(pFront);

      /* Copy the string without quote and blank removed */
      for (i = 0; i < uLen; i++)
      {
        pBuf[i] = pFront[i];
      }
      pBuf[i] = '\0';
    }
  }
}


/****************************************************************************
*
** FUNCTION: IsCommentLine()
*/
/*!
* \brief
*   Helper function to check whether a line a comment line
*
* \param [in]  pLineBuf        - Panel config line buffer
*
* \retval BOOLEAN                TRUE for this is a comment line, FALSE otherwise
*
****************************************************************************/
static BOOLEAN IsCommentLine(CHAR8 *pLineBuf)
{
  BOOLEAN bRet    = FALSE;

  if (NULL != pLineBuf)
  {
    /* Skip space at the head */
    TrimLeft((CHAR8**)&pLineBuf);

    /* Check whether the first character is '#' */
    if ('#' == *pLineBuf)
    {
      bRet = TRUE;
    }
  }

  return bRet;
}

/****************************************************************************
*
** FUNCTION: ParseConfigLine()
*/
/*!
* \brief
*   Helper function to parse a line from config file
*
* \param [in]  pPanelName      - Expected panel name for early matching,
         [in]  pLineBuf        - Panel config line
         [out] pOutPanelConfig   Output panel config

*
* \retval EFI_STATUS
*
****************************************************************************/
static EFI_STATUS ParseConfigLine(CHAR8 *pPanelName, CHAR8 *pLineBuf, PanelConfigType *pOutPanelConfig)
{
  EFI_STATUS                     eStatus             = EFI_SUCCESS;
  SimPanelConfigType             sSimPanelConfig;

  if ((NULL == pPanelName)   ||
      (NULL == pLineBuf)     ||
      (NULL == pOutPanelConfig))
  {
    DEBUG ((EFI_D_ERROR, "ParseConfigLine invalid parameter\n"));
    eStatus = EFI_UNSUPPORTED;
  }
  else if (IsCommentLine(pLineBuf))
  {
    eStatus = EFI_UNSUPPORTED;
  }
  else
  {
    UINT32                       uDTLabelCount       = 0;
    ConfigFileColumnType         uColumnIndex        = 0;
    CHAR8                       *pSavePtr            = NULL;
    CHAR8                       *pSubItemStr         = NULL;

    MDP_OSAL_MEMZERO(&sSimPanelConfig, sizeof(sSimPanelConfig));

    pSubItemStr = (CHAR8*)strtok_r(pLineBuf, ",", &pSavePtr);

    while((NULL         != pSubItemStr) &&
          (uColumnIndex < CONFIGFILE_COLUMN_MAX))
    {
      TrimLeft((CHAR8**)&pSubItemStr);
      TrimRight(pSubItemStr);

      /* Sub string is ready, column parsing */
      switch(uColumnIndex)
      {
        case CONFIGFILE_COLUMN_NAME:
          /* if panel name not match in this config line, no need to continue to parse */
          if (0 != AsciiStrCmp(pPanelName, (CHAR8*)pSubItemStr))
          {
            eStatus = EFI_UNSUPPORTED;

            /* For early exit */
            uColumnIndex = CONFIGFILE_COLUMN_MAX;
          }
          else
          {
             MDPPlatformSetPanelName(sSimPanelConfig.szName, pPanelName);
          }
          uColumnIndex++;
          break;

        case CONFIGFILE_COLUMN_DTLABEL:
          /* Expect to parse string like "qcom,mdss_dsi_sharp_4k_dsc_cmd:",
           * This string is special that it contain a comma inside
           * double quote will be removed
           */
          if (uDTLabelCount == 0)
          {
            AsciiStrCpyS(sSimPanelConfig.DTLabel, DISPLAY_PANEL_DT_LABEL_MAX_LEN, (CHAR8*)pSubItemStr);
            uDTLabelCount++;
          }
          else
          {
            AsciiStrCatS(sSimPanelConfig.DTLabel, DISPLAY_PANEL_DT_LABEL_MAX_LEN, ",");
            AsciiStrCatS(sSimPanelConfig.DTLabel, DISPLAY_PANEL_DT_LABEL_MAX_LEN, (CHAR8*)pSubItemStr);

            /* Remove quote */
            TrimQuote(sSimPanelConfig.DTLabel, AsciiStrLen(sSimPanelConfig.DTLabel));
            uColumnIndex++;
          }
          break;

        case CONFIGFILE_COLUMN_KERNELMODE:
          AsciiStrCpyS(sSimPanelConfig.szKernelModeInfo, DISPLAY_PANEL_KERNELMODE_INFO_MAX_LEN, (CHAR8*)pSubItemStr);

          /* Remove quote */
          TrimQuote(sSimPanelConfig.szKernelModeInfo, AsciiStrLen(sSimPanelConfig.szKernelModeInfo));
          uColumnIndex++;
          break;

        default:
          break;
      }

      pSubItemStr = (CHAR8*)strtok_r(NULL, ",", &pSavePtr);
    }

    if (EFI_SUCCESS == eStatus)
    {
      /* It is simulation panel when a line parsing needed */
      pOutPanelConfig->ePanelType = MDPPLATFORM_PANEL_SIMULATION;

      MDPPlatformSetPanelName(pOutPanelConfig->szName, pPanelName);

      MDP_OSAL_MEMCPY(&pOutPanelConfig->sSimPanelConfig, &sSimPanelConfig, sizeof(sSimPanelConfig));
    }
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: GetPanelConfigFromFile()
*/
/*!
* \brief
*   Helper function to get panel config from file and fill the value to pOutDtInfo
*
* \param [in]  pPanelName      - Panel name
         [in]  pFileBuf        - Config file buffer
         [in]  uFileBufLen     - Config file buffer length
         [out] pOutPanelConfig - Panel config that parsed out from config file
*
* \retval EFI_STATUS
*
****************************************************************************/
static EFI_STATUS GetPanelConfigFromFile(CHAR8 *pPanelName, UINT8 *pFileBuf, UINT32 uFileBufLen, PanelConfigType *pOutPanelConfig)
{
  EFI_STATUS eStatus     = EFI_SUCCESS;
  CHAR8     *pSavePtr    = NULL;

  if ((NULL == pPanelName)      ||
      (NULL == pFileBuf)        ||
      (NULL == pOutPanelConfig) ||
      (0    == uFileBufLen))
  {
    DEBUG ((EFI_D_ERROR, "GetPanelConfigFromFile invalid parameter\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else
  {
    BOOLEAN  bIsFirstLine = TRUE;
    CHAR8   *pLine        = (CHAR8*)strtok_r((CHAR8*)pFileBuf, "\r\n", &pSavePtr);

    while(pLine)
    {
      /* Always skip first line */
      if (bIsFirstLine)
      {
        pLine        = (CHAR8*)strtok_r(NULL, "\r\n", &pSavePtr);
        bIsFirstLine = FALSE;
        continue;
      }

      if (MDP_STATUS_OK == (eStatus = ParseConfigLine(pPanelName, pLine, pOutPanelConfig)))
      {
        break;
      }

      pLine = (CHAR8*)strtok_r(NULL, "\r\n", &pSavePtr);
    }
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: LookUpPanel()
*/
/*!
* \brief
*   Helper function to lookup panel config by panel name in different locations
*
* \param [in]  eDisplayId   - Display ID
         [in]  eLocation    - Panel config location
         [in]  pPanelName   - Panel name
*
* \retval EFI_STATUS
*
****************************************************************************/
static EFI_STATUS LookUpPanel(MDP_Display_IDType eDisplayId, ConfigLocationType eLocation, CHAR8 *pPanelName)
{
  PanelConfigType *pPanelConfig        = GET_PANEL_CONFIG(eDisplayId);
  EFI_STATUS       eStatus             = EFI_UNSUPPORTED;

  pPanelConfig->eDisplayId             =  eDisplayId;

  switch (eLocation)
  {
  case CONFIG_LOCATION_PHYSICAL_TABLE:
    {
      UINT32  i;

      /* Lookup from the physical panel table */
      for (i = 0; i < ARRAY_SIZE(sPhysicalPanelConfigTable); i++)
      {
        if (0 == AsciiStrCmp(pPanelName, sPhysicalPanelConfigTable[i].szName))
        {
          pPanelConfig->ePanelType           = MDPPLATFORM_PANEL_PHYSICAL;
          pPanelConfig->pPhysicalPanelConfig = &sPhysicalPanelConfigTable[i];
          MDPPlatformSetPanelName(pPanelConfig->szName, pPanelConfig->pPhysicalPanelConfig->szName);
          eStatus = EFI_SUCCESS;
          break;
        }
      }
    }
    break;

  case CONFIG_LOCATION_MAINFV:
    {
      UINT8           *pPanelConfigFileBuf         = NULL;
      UINTN            uPanelConfigFileSize        = 0;

      if (EFI_SUCCESS != MDP_Display_LoadFile(DISP_SIMPANEL_CONFIG_FILE_ASICII, &pPanelConfigFileBuf, (UINT32*)&uPanelConfigFileSize, (UINT32*)&uPanelConfigFileSize, 0))
      {
        DEBUG((EFI_D_WARN, "MDPPlatformSelectPanelConfig: fail to load %a\n", DISP_SIMPANEL_CONFIG_FILE_ASICII));
      }
      else
      {
        if (EFI_SUCCESS != (eStatus = GetPanelConfigFromFile(pPanelName, pPanelConfigFileBuf, uPanelConfigFileSize, pPanelConfig)))
        {
          DEBUG((EFI_D_INFO, "MDPPlatformSelectPanelConfig: fail to get panel config from PanelConfig.csv at mainfv\n"));
        }

        /* Free memory */
        if (NULL != pPanelConfigFileBuf)
        {
          MDP_OSAL_FREE(pPanelConfigFileBuf);
        }
      }
    }
    break;

  case CONFIG_LOCATION_IMAGEFVB:
    {
      UINT8           *pPanelConfigFileBuf         = NULL;
      UINTN            uPanelConfigFileSize        = 0;

      if (EFI_SUCCESS != MDP_Display_ReadConfigFile(DISP_CONFIG_PART_NAME, DISP_SIMPANEL_CONFIG_FILE, &pPanelConfigFileBuf, &uPanelConfigFileSize, 0))
      {
        DEBUG((EFI_D_WARN, "MDPPlatformSelectPanelConfig: fail to read panel config data\n"));
      }
      else
      {
        if (EFI_SUCCESS != (eStatus = GetPanelConfigFromFile(pPanelName, pPanelConfigFileBuf, uPanelConfigFileSize, pPanelConfig)))
        {
          DEBUG((EFI_D_INFO, "MDPPlatformSelectPanelConfig: fail to get panel config from PanelConfig.csv at %s\n", DISP_CONFIG_PART_NAME));
        }

        /* Free memory */
        if (NULL != pPanelConfigFileBuf)
        {
          MDP_OSAL_FREE(pPanelConfigFileBuf);
        }
      }
    }
    break;

  default:
    break;
  }

  return eStatus;
}

#ifdef __cplusplus
}
#endif
