/*=============================================================================
Copyright (c) 2020 Qualcomm Technologies International, Ltd.
All Rights Reserved.
Qualcomm Technologies International, Ltd. Confidential and Proprietary. 
=============================================================================*/
#include "MDPLib.h"
#include "MDPLib_i.h"
#include "MDPSystem.h"
#include "hal_mdp.h"
#include <Library/BaseLib.h>
#include "DisplayUtils.h"
#include "HALDSILib.h"

/*=========================================================================
     Default Defines
==========================================================================*/
/*------------------------------------------------------------------------------------------
 * Public Functions
 *------------------------------------------------------------------------------------------*/

/****************************************************************************
*
** FUNCTION: MDPDemuraSetupConfig()
*/
/*!
* \brief
*  Setup Demura configure
*
* \param [in] pPanelConfig       - The display configuration to setup
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPDemuraSetupConfig(MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status  eStatus = MDP_STATUS_OK;

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: MDPDemuraLoadConfig()
*/
/*!
* \brief
*   Read Demura file from QMCS partition.
*
* \param [in] pPanelConfig     - The display configuration to setup
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDPDemuraLoadConfig(MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status  eStatus = MDP_STATUS_OK;
 
  return eStatus;
}

/****************************************************************************
*
** FUNCTION: MDPGetDemmuraPanelID()
*/
/*!
* \brief
*   Get display Demura panel ID.
*
* \param [in] pPanelConfig          - The display configuration to setup
* \param [in] pDemuraPanelIDCmd     - Demura panel id read command
* \param [in] uDemuraPanelIDCmdLen  - Demura panel id read command length

*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDPGetDemmuraPanelID(MDP_Panel_AttrType *pDisplayInfo, uint8* pDemuraPanelIDCmd, uint32 uDemuraPanelIDCmdLen)
{
  MDP_Status  eStatus = MDP_STATUS_OK;

  return eStatus;
}
