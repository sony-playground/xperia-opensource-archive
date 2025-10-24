/*=============================================================================
Copyright (c) 2020-2022 Qualcomm Technologies International, Ltd.
All Rights Reserved.
Qualcomm Technologies International, Ltd. Confidential and Proprietary.
=============================================================================*/
#include "MDPLib.h"
#include "MDPLib_i.h"
#include "MDPSystem.h"

/****************************************************************************
*
** FUNCTION: MDPSetupPostProcessing()
*/
/*!
* \brief
*   Setup the MDP for post processing
*
* \param [in] pPanelConfig       - The display configuration to setup
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPSetupPostProcessing(MDP_Panel_AttrType* pPanelConfig)
{
  MDP_Status                    eStatus           = MDP_STATUS_OK;
  MDP_Status                    eLocalStatus      = MDP_STATUS_OK;
  const MDPInterfaceCapsType   *pMDPInterfaceCaps = MDPGetInterfaceCaps();
  uint32                        uI                = 0;

  if ((NULL                  != pMDPInterfaceCaps)                        &&
      (MDP_INTERFACE_CAPS_SPR & pMDPInterfaceCaps->uInterfaceFeatureCaps) &&
      (HAL_MDP_SPR_PACK_NONE != pPanelConfig->uAttrs.sDsi.sDemuraConfig.eSprPackType))
  {
    for (uI = 0; uI < pPanelConfig->uNumMixers; uI++)
    {
      MDP_DisplayCtrlPathMapType         *pControlPathMap = (MDP_DisplayCtrlPathMapType*)MDP_GET_CTRLPATHMAP(pPanelConfig->eDisplayId, uI);
      HAL_MDP_SprId                       eSprId          = MDP_GET_SPR_ID(pControlPathMap->eDestinationPipeId);
      HAL_MDSS_ErrorType                  eHalStatus      = HAL_MDSS_STATUS_SUCCESS;
      HAL_MDP_ControlPathConfigType       sControlPathConfig;
      HAL_MDP_ControlPath_DSPPFlushType   sDSPPFlushConfig;

      pPanelConfig->uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig.uNumMixers = pPanelConfig->uNumMixers;

      MDP_OSAL_MEMZERO(&sControlPathConfig, sizeof(HAL_MDP_ControlPathConfigType));
      MDP_OSAL_MEMZERO(&sDSPPFlushConfig,   sizeof(HAL_MDP_ControlPath_DSPPFlushType));
      
      //Setup DSPP Flush
      sDSPPFlushConfig.eDestinationPipeId   = pPanelConfig->sDisplayControlPath[uI].eDestinationPipeId;
      sDSPPFlushConfig.eDsppMoudle          = HAL_MDP_DSPPMODULE_SPR;
      sControlPathConfig.psDsppFlushConfig  = &sDSPPFlushConfig;

      if (HAL_MDP_SPR_NONE == eSprId)
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPSetupPostProcessing: Invalid SPR ID for DSPP_%d\n", pControlPathMap->eDestinationPipeId);
        eStatus = MDP_STATUS_INVALID_STATE;
        break;
      }
      else if (HAL_MDSS_STATUS_SUCCESS != (eHalStatus = HAL_MDP_SPR_SetupConfig(eSprId, pPanelConfig->uAttrs.sDsi.sDemuraConfig.eSprPackType, &pPanelConfig->uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPSetupPostProcessing: Hal mdp SPR setup config failed! eHalStatus = 0x%x\n", eHalStatus);
        eStatus = MDP_STATUS_FAILED;
        break;
      }
      else
      {
        /* Set dspp flush bit flag to enable */
        pPanelConfig->bDsppEnabled = TRUE;
        
        if (HAL_MDSS_STATUS_SUCCESS != (eHalStatus = HAL_MDP_ControlPath_Setup(pPanelConfig->sDisplayControlPath[uI].eControlPathId,
                                                                   &sControlPathConfig,
                                                                    0)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPSetupPostProcessing: HAL_MDP_ControlPath_Setup failed!\n");
          eStatus = MDP_STATUS_FAILED;
          break;
        }
      }
    }
    
    if (MDP_STATUS_OK == eStatus)
    {
      if (MDP_STATUS_OK != (eLocalStatus = MDPDemuraLoadConfig(pPanelConfig)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPSetupPostProcessing: MDPDemuraLoadConfig failed, Status = 0x%x\n", eLocalStatus);
      }
      else if (MDP_STATUS_OK != (eLocalStatus = MDPDemuraSetupConfig(pPanelConfig)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPSetupPostProcessing: MDPDemuraSetupConfig failed, Status = 0x%x\n", eLocalStatus);
      }

      if (MDP_STATUS_OK != eLocalStatus)
      {
        // Mark Demara panel ID to 0, so demura info won't be passed to HLOS
        pPanelConfig->uAttrs.sDsi.sDemuraConfig.uDemuraPanelID = 0;
      }
      else
      {
        /* Set dspp flush bit flag to enable */
        pPanelConfig->bDsppEnabled = TRUE;
      }
    }
  }

  return eStatus;
}
