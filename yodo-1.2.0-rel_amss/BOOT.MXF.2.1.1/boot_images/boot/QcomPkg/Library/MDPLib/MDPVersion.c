/*=============================================================================
 
  File: MDPLIb.c
 
  Source file for MDP functions
  
  Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/
#include "MDPLib.h"
#include "MDPLib_i.h"
#include "MDPSystem.h"
#include "MDSSCatalog_8xx.h"
#include "MDSSCatalog_9xx.h"

/*=========================================================================
      Public APIs
==========================================================================*/

MDP_Status MDPInitHwPrivateInfo(MDP_HwPrivateInfo *pHwPrivateInfo)
{
  MDP_Status          eStatus             = MDP_STATUS_OK;
  HAL_MDP_HwInfo      sHwInfo; 

  if (HAL_MDSS_STATUS_SUCCESS != HAL_MDP_ReadVersionInfo(&(pHwPrivateInfo->sMDPVersionInfo), &sHwInfo))
  {
     eStatus = MDP_STATUS_HW_ERROR;
  }
  else if (pHwPrivateInfo->sMDPVersionInfo.uMinorVersion >= MDP_MAX_MINOR_VERSION)
  {
    // Invalid or unsupported hardware version
    eStatus = MDP_STATUS_NOT_SUPPORTED;
  }
  else
  {
    if (8 == pHwPrivateInfo->sMDPVersionInfo.uMajorVersion)
    {
      if (NULL == DeviceCapInfo_MDSS8xx[pHwPrivateInfo->sMDPVersionInfo.uMinorVersion])
      {
        // Invalid or unsupported hardware version
        eStatus = MDP_STATUS_NOT_SUPPORTED;
      }
      else
      {
        pHwPrivateInfo->pDeviceCaps = DeviceCapInfo_MDSS8xx[pHwPrivateInfo->sMDPVersionInfo.uMinorVersion];

        // MDP PingPong buffer split slave ID mapping table
        pHwPrivateInfo->pPPSplitSlaveMap = PingPongSplitSlaveMapInfo_MDSS8xx[pHwPrivateInfo->sMDPVersionInfo.uMinorVersion];
      }
    }
    else if (9 == pHwPrivateInfo->sMDPVersionInfo.uMajorVersion)
    {
      if (NULL == DeviceCapInfo_MDSS9xx[pHwPrivateInfo->sMDPVersionInfo.uMinorVersion])
      {
        // Invalid or unsupported hardware version
        eStatus = MDP_STATUS_NOT_SUPPORTED;
      }
      else
      {
        pHwPrivateInfo->pDeviceCaps = DeviceCapInfo_MDSS9xx[pHwPrivateInfo->sMDPVersionInfo.uMinorVersion];

        // MDP PingPong buffer split slave ID mapping table
        pHwPrivateInfo->pPPSplitSlaveMap = PingPongSplitSlaveMapInfo_MDSS9xx[pHwPrivateInfo->sMDPVersionInfo.uMinorVersion];
      }
    }
    else
    {
      eStatus = MDP_STATUS_NOT_SUPPORTED;
    }
  }
  return eStatus;
}

