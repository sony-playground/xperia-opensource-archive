/*=============================================================================

  File: MDPPlatformLibPanelConfig.h

  MDP platform specific types

  Copyright (c) 2021 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#ifndef __MDP_PLATFORM_LIB_PANEL_CONFIG__H__
#define __MDP_PLATFORM_LIB_PANEL_CONFIG__H__

#include "MDPPlatformLibPanelCommon.h"

extern PanelConfigType    asPanelConfig[MDP_DISPLAY_MAX];
extern SimPanelConfigType asSimPanelConfig[MDP_DISPLAY_MAX];


/* Defines HW config with default gpio/power/reset function, brightness level is dynamically defined
 */
#define MDP_PLATFORM_CREATE_PANEL_HW_CONFIG_BRIGHTLEVEL(_brightness_level_) \
{\
  .pMDPPlatformPanelGpio    = &sDefaultGpioConfig,\
  .pPanel_PowerUp           = Panel_Default_PowerUp,\
  .pPanel_PowerDown         = Panel_Default_PowerDown,\
  .pPanel_Reset             = Panel_Default_Reset,\
  .pPanel_Brightness_Enable = Panel_Default_Brightness_Enable,\
  .pPanel_Brightness_Level  = (_brightness_level_)\
}

/* Defines HW config with default power/reset function,no brightness control, gpio is dynamically defined
 */
#define MDP_PLATFORM_CREATE_PANEL_HW_CONFIG_GPIO(_gpio_) \
{\
  .pMDPPlatformPanelGpio    = (_gpio_),\
  .pPanel_PowerUp           = Panel_Default_PowerUp,\
  .pPanel_PowerDown         = Panel_Default_PowerDown,\
  .pPanel_Reset             = Panel_Default_Reset,\
  .pPanel_Brightness_Enable = NULL,\
  .pPanel_Brightness_Level  = NULL\
}

/* Defines HW config with default gpio/power/reset function, brightness level is dynamically defined
 */
#define MDP_PLATFORM_CREATE_PANEL_HW_CONFIG_BRIGHTLEVEL_GPIO(_brightness_level_, _gpio_) \
{\
  .pMDPPlatformPanelGpio    = (_gpio_),\
  .pPanel_PowerUp           = Panel_Default_PowerUp,\
  .pPanel_PowerDown         = Panel_Default_PowerDown,\
  .pPanel_Reset             = Panel_Default_Reset,\
  .pPanel_Brightness_Enable = Panel_Default_Brightness_Enable,\
  .pPanel_Brightness_Level  = (_brightness_level_)\
}

#ifdef FEATURE_XBOOT
#include "XMDPPlatformLibPanelConfig_PanelFunction.h"
#endif /* FEATURE_XBOOT */

/* Return the a specific panel's configuration
 */
#define GET_PANEL_CONFIG(_id_)             (&asPanelConfig[((_id_)<MDP_DISPLAY_MAX)?(_id_):0])

/* Default platform panel functions - From MDPPlatformLibPanelCommon.c */
MDP_Status       Panel_Default_PowerUp(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);
MDP_Status       Panel_Default_PowerDown(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);
MDP_Status       Panel_Default_Brightness_Enable(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);
MDP_Status       Panel_Default_Brightness_Level(MDP_Display_IDType eDisplayId, BacklightConfigType *pBacklightConfig);
MDP_Status       Panel_Default_V2_Brightness_Level(MDP_Display_IDType eDisplayId, BacklightConfigType *pBacklightConfig);
MDP_Status       Panel_Default_Reset(MDPPlatformPanelResetInfo *pResetInfo);

MDP_Status       MDPPlatformSetupPanelConfig(MDP_Display_IDType eDisplayId,MDPPlatformPanelInfo *pPlatformPanel, MDPPlatformInfo *pPlatformInfo, MDPPlatformInfo *pMDPPlatformInfo);
MDP_Status       MDPPlatformGetPanelXmlConfig(MDP_Display_IDType eDisplayId, MDPPlatformPanelInfo *pPlatformPanel);
BOOLEAN          MDPPlatformValidPanelName(CHAR8 *pPanelName);
VOID             MDPPlatformSetPanelName(CHAR8 *pBuf, CHAR8 *pPanelName);
VOID             MDPPlatformClearPanelName(CHAR8 *pPanelName);
VOID             MDPPlatformGetPanelList(MDPDisplayAutoDetectType eAutoDetect, PlatformDSIDetectParams **pPanelList, UINT32 *pListLen, UINT32 *pPanelIndex);
PanelConfigType* MDPPlatformSelectPanelConfig(MDP_Display_IDType eDisplayId, CHAR8 *pPanelName, bool32 *bSWEnable);

#ifdef FEATURE_XBOOT
#include "XMDPPlatformLibPanelConfig_extern.h"
#endif /* FEATURE_XBOOT */

#endif // __MDP_PLATFORM_LIB_PANEL_CONFIG__H__

