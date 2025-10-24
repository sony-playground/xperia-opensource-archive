#ifndef __MDSSCATALOG_8xx_H__
#define __MDSSCATALOG_8xx_H__
/*=============================================================================

  Copyright (c) 2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "MDPLib_i.h"


/*=========================================================================
     Default Defines
==========================================================================*/

/* Maximum number of minor versions supported */
#define MDP_MAX_MINOR_VERSION            6


/*=========================================================================
     Local Variables
==========================================================================*/

/* MDSS8xx Resolution Capabilities
*/
const MDP_ResolutionCaps sResolutionCaps_MDSS810 =
{
    2,     /* uMinLayerWidth  */
    2,     /* uMinLayerHeight */
    2560,  /* uMaxLayerWidth  */
    2048,  /* uMaxLayerHeight */
};

/**************************************************************
* MDSS8xx PP (Ping-Pong) Capabilities
*
* Note: set MDP_PINGPONG_CAP_PINGPONG_SPLIT in uPPFeatureFlags to enable pingpong-split
*************************************************************/
const MDP_PingPongCaps sPPCaps_MDSS810[HAL_MDP_PINGPONG_MAX] =
{
  /* bSupported, uMaxWidth, uPPFeatureFlags */
  { FALSE,       0,         0 },                                // HAL_MDP_PING_PONG_NONE
  { TRUE,        2560,      MDP_PINGPONG_CAP_PINGPONG_SPLIT },  // HAL_MDP_PING_PONG_0
  { TRUE,        2560,      MDP_PINGPONG_CAP_PINGPONG_SPLIT },  // HAL_MDP_PING_PONG_1
  { TRUE,        2560,      0 },                                // HAL_MDP_PING_PONG_2
  { TRUE,        2560,      0 },                                // HAL_MDP_PING_PONG_3
  { FALSE,       0,         0 },                                // HAL_MDP_PING_PONG_4
  { FALSE,       0,         0 }                                 // HAL_MDP_PING_PONG_5
};

/* Mapping from master ping-pong to slave ping-pong used ONLY when ping-pong split is enabled. */
const HAL_MDP_PingPongId sMDSS810_PPSplitSlaveMap[HAL_MDP_PINGPONG_MAX] =
{
    HAL_MDP_PINGPONG_NONE, // HAL_MDP_PINGPONG_NONE,
    HAL_MDP_PINGPONG_6,    // HAL_MDP_PINGPONG_0,
    HAL_MDP_PINGPONG_6,    // HAL_MDP_PINGPONG_1,
    HAL_MDP_PINGPONG_NONE, // HAL_MDP_PINGPONG_2,
    HAL_MDP_PINGPONG_NONE, // HAL_MDP_PINGPONG_3,
    HAL_MDP_PINGPONG_NONE, // HAL_MDP_PINGPONG_4,
    HAL_MDP_PINGPONG_NONE  // HAL_MDP_PINGPONG_4,
};

/* MDSS8xx DSC Capabilities */
const MDP_DSCCaps sDSCCaps_MDSS810[HAL_MDP_DSC_MAX] =
{
  {0                                                  , HAL_MDP_DSC_NONE},  // HAL_MDP_DSC_NONE
  {MDP_DSC_CAPS_RGB_SUPPORT                           , HAL_MDP_DSC_1   },  // HAL_MDP_DSC_0
  {MDP_DSC_CAPS_RGB_SUPPORT                           , HAL_MDP_DSC_NONE},  // HAL_MDP_DSC_1
  {MDP_DSC_CAPS_RGB_SUPPORT | MDP_DSC_CAPS_YUV_SUPPORT, HAL_MDP_DSC_3   },  // HAL_MDP_DSC_2
  {MDP_DSC_CAPS_RGB_SUPPORT | MDP_DSC_CAPS_YUV_SUPPORT, HAL_MDP_DSC_NONE},  // HAL_MDP_DSC_3
  {0                                                  , HAL_MDP_DSC_NONE},  // HAL_MDP_DSC_4
  {0                                                  , HAL_MDP_DSC_NONE}   // HAL_MDP_DSC_5
};

/* Slave PingPong Buffer ID for PP split for all MDP versions
*/
const HAL_MDP_PingPongId* PingPongSplitSlaveMapInfo_MDSS8xx[MDP_MAX_MINOR_VERSION] =
{
   NULL,                           /* MDSS 8.0.0  */
   &sMDSS810_PPSplitSlaveMap[0],   /* MDSS 8.1.0  */
   NULL,                           /* MDSS 8.2.0  */
   NULL,                           /* MDSS 8.3.0  */
   NULL,                           /* MDSS 8.4.0  */
   NULL                            /* MDSS 8.5.0  */
};



/* MDSS8xx Device Capabilities
 */
const MDP_DeviceCaps sDeviceCaps_MDSS810 =
{
  &sResolutionCaps_MDSS810,
  &sPPCaps_MDSS810[0],
  &sDSCCaps_MDSS810[0],
};



/* MDP Device caps  for all MDP versions
 */
const MDP_DeviceCaps* DeviceCapInfo_MDSS8xx[MDP_MAX_MINOR_VERSION] =
{
  NULL,                           /* MDSS 8.0.0  */
  &sDeviceCaps_MDSS810,           /* MDSS 8.1.0  */
  NULL,                           /* MDSS 8.2.0  */
  NULL,                           /* MDSS 8.3.0  */
  NULL,                           /* MDSS 8.4.0  */
  NULL                            /* MDSS 8.5.0  */
};

#endif