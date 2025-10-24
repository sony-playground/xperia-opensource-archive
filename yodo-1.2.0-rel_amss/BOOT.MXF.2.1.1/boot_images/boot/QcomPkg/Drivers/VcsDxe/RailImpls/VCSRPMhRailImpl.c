/*
===========================================================================
*/
/**
  @file VCSRPMhRailImpl.c 
  
  RPMh impl type functions for the VCS driver.
*/
/*  
  ====================================================================

  Copyright (c) 2017,2021 QUALCOMM Technologies Incorporated. All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/VcsDxe/RailImpls/VCSRPMhRailImpl.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $
 
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "VCSDriver.h"
#include "VCSRPMhRailImpl.h"
#include "DALDeviceId.h"
#include "DALSys.h"
#include "npa.h"
#include "npa_resource.h"
#include "cmd_db.h"
#include "pwr_utils_lvl.h"
#include "rpmh_client.h"
#include "voltage_level.h"
#include "limits.h"
#include "CoreVerify.h"


/*=========================================================================
      Macro Definitions
==========================================================================*/



/*=========================================================================
      Prototypes
==========================================================================*/

static DALResult VCS_RPMhRailImplInitImpl(VCSRailNodeType *pRail);
static DALResult VCS_RPMhRailImplSetCorner(npa_client_handle hClient, rail_voltage_level eCorner);
static DALResult VCS_RPMhRailImplMapCorner(VCSRailNodeType *pRail, rail_voltage_level *eCorner);
static DALResult VCS_RPMhRailImplPostChange(npa_client_handle hClient, rail_voltage_level eCorner);


/*=========================================================================
      Data
==========================================================================*/

VCSRailControlType VCSRPMhRailImplControl =
{
  .fpInit      = VCS_RPMhRailImplInitImpl,
  .fpSetCorner = VCS_RPMhRailImplSetCorner,
  .fpMapCorner = VCS_RPMhRailImplMapCorner,
  .fpPostChange = VCS_RPMhRailImplPostChange,
};


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : VCS_RPMhRailImplFlushSet
** =========================================================================*/
/**
  Flush the specified command set to RPMh.

  @param *pSet [in] -- Pointer command set.
  @param hRPMh [in] -- RPMh client handle.

  @return
  DAL_SUCCESS if command set flushed successfully.
  DAL_ERROR_INVALID_PARAMETER if NULL arguments provided.

  @dependencies
  None.
*/

static DALResult VCS_RPMhRailImplFlushSet
(
  rpmh_command_set_t *pSet,
  rpmh_client_handle  hRPMh
)
{
  uint32 nCommandId;

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  if (!pSet || !hRPMh)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Flush and clear each set.                                             */
  /*-----------------------------------------------------------------------*/

  if (pSet->num_commands)
  {
    nCommandId = rpmh_issue_command_set(hRPMh, pSet);

    /*
     * Barrier if command wants to wait for completion.
     */
    if (pSet->commands[0].completion)
    {
      rpmh_barrier_single(hRPMh, nCommandId);
    }

    /*
     * Invalidate commands.
     */
    pSet->num_commands = 0;
  }

  return DAL_SUCCESS;

} /* END of VCS_RPMhRailImplFlushSet */


/* =========================================================================
**  Function : VCS_RPMhRailImplQueueCommand
** =========================================================================*/
/**
  Flush the specified command set to RPMh.

  @param hClient [in] -- NPA client handle.
  @param *pSet [in] -- Pointer command set.
  @param nAddress [in] -- Destination address for data.
  @param nData [in] -- Data to queue.

  @return
  DAL_SUCCESS if command successfully queued.
  DAL_ERROR_INVALID_PARAMETER if NULL arguments provided.

  @dependencies
  None.
*/

static DALResult VCS_RPMhRailImplQueueCommand
(
  npa_client_handle   hClient,
  rpmh_command_set_t *pSet,
  uint32              nAddress,
  int                 nData
)
{
  rpmh_command_t *pCommand;
  boolean         bCompletion;

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  if (hClient == NULL ||
      pSet == NULL    ||
      nAddress == 0 ||
      pSet->num_commands == ARR_SIZE(pSet->commands))
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Determine if this command should wait for completion.                 */
  /*-----------------------------------------------------------------------*/

  if (pSet->set == RPMH_SET_ACTIVE &&
      !npa_request_has_attribute(hClient, NPA_REQUEST_FIRE_AND_FORGET))
  {
    bCompletion = TRUE;
  }
  else
  {
    bCompletion = FALSE;
  }

  /*-----------------------------------------------------------------------*/
  /* Queue command.                                                        */
  /*-----------------------------------------------------------------------*/

  pCommand = &pSet->commands[pSet->num_commands];
  pCommand->address = nAddress;
  pCommand->data = (uint32)nData;
  pCommand->completion = bCompletion;

  /*
   * Increment command count.
   */
  pSet->num_commands++;

  return DAL_SUCCESS;

} /* END of VCS_RPMhRailImplQueueCommand */


/* =========================================================================
**  Function : VCS_RPMhRailImplMapCorner
** =========================================================================*/
/**
  Map corner to an RPMh supported corner for this rail.

  This function will map the specified corner to an RPMh supported corner for
  this rail.

  @param *pRail   [in]     -- Pointer rail node.
  @param *eCorner [in/out] -- Request corner that gets mapped to supported corner.

  @return
  DAL_SUCCESS -- Sucessfully mapped corner to a supported corner.
  DAL_ERROR -- Failed to map corner to a supported corner.

  @dependencies
  None.
*/

static DALResult VCS_RPMhRailImplMapCorner(VCSRailNodeType *pRail, rail_voltage_level *eCorner)
{
  int                  nHLVL;
  int                  nCornerRequest, nCornerMapped;
  VCSRPMhRailImplType *pImpl;

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  if (pRail == NULL || pRail->pImpl == NULL || eCorner == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  pImpl = (VCSRPMhRailImplType *)pRail->pImpl;

  /*-----------------------------------------------------------------------*/
  /* Map request to a supported corner.                                    */
  /*-----------------------------------------------------------------------*/

  nCornerRequest = (int)*eCorner;
  nHLVL = pwr_utils_hlvl_named_resource(pImpl->szName, nCornerRequest, &nCornerMapped);
  if (nHLVL < 0)
  {
    return DAL_ERROR;
  }

  *eCorner = (rail_voltage_level)nCornerMapped;

  return DAL_SUCCESS;

} /* END of VCS_RPMhRailImplMapCorner */


/* =========================================================================
**  Function : VCS_RPMhRailImplSetCorner
** =========================================================================*/
/**
  Set RPMh rail to a requested corner.

  This function will set the rail to the requested corner.
  The dependency will be satisfied as specified by the bBatchCommand field
  of the rail impl data.

  In batched mode:
    This function will group commands for this rail with the set of commands
    to update the dependency rail as well so that RPMh can update them together
    atomically.

  In synchronous mode:
    This function will issue commands for this rail in a synchronous order with
    the commands issued for the dependency.

  @param hClient [in] -- Pointer to client making request.
  @param eCorner [in] -- Requested corner.

  @return
  DAL_SUCCESS -- Sucessfully configured rail to requested corner.
  DAL_ERROR -- Failed to configure rail to requested corner.

  @dependencies
  None.
*/

static DALResult VCS_RPMhRailImplSetCorner
(
  npa_client_handle  hClient,
  rail_voltage_level eCorner
)
{
  DALResult            eResult;
  VCSRailNodeType     *pRail, *pRailBatch;
  VCSRPMhRailImplType *pImpl, *pImplBatch;
  rpmh_command_set_t  *pCommandSets, *pSet;
  int                  nHLVL, mapped_vlvl;
  boolean              bFlush;
  uint8_t             *pImplHLVL, i;

  pRail = VCS_CLIENT_TO_RAIL(hClient);

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  if (pRail == NULL || pRail->pImpl == NULL)
  {
    return DAL_ERROR_INTERNAL;
  }

  pImpl = (VCSRPMhRailImplType *)pRail->pImpl;

  /*-----------------------------------------------------------------------*/
  /* Store prior corner.                                                   */
  /*-----------------------------------------------------------------------*/
  if (eCorner != pRail->eCorner)
  {
    pImpl->eCornerPrior = pRail->eCorner;
  }

  /*-----------------------------------------------------------------------*/
  /* Determine which command set to place this request.                    */
  /*  - For batched requests use the set contained within the rail pointed */
  /*    to by the client->resource_data.                                   */
  /*  - For single resource requests use this rail's set.                  */
  /*-----------------------------------------------------------------------*/

  bFlush = TRUE;
  if (NPA_CLIENT_BATCH == hClient->type)
  {
    // First resource in batch keeps track of all batch update commands.
    // Share this with NPA framework for subsequent requests in this batch.
    if (!hClient->resource_data)
    {
      hClient->resource_data = (npa_user_data)hClient->resource;
    }

    pRailBatch = (VCS_RESOURCE_TO_RAIL(hClient->resource_data));
    CORE_VERIFY_PTR(pRailBatch);

    pImplBatch = (VCSRPMhRailImplType *)pRailBatch->pImpl;
    CORE_VERIFY_PTR(pImplBatch);

    pCommandSets = (rpmh_command_set_t *)pImplBatch->aSets;

    // Insert rail in batch list for future post-change events.
    if (pRail != pRailBatch)
    {
      while(pImplBatch->pNextInBatch)
      { 
        if (pImplBatch->pNextInBatch == pRail)
        {
          break;
        }
        else
        {
          pRailBatch = pImplBatch->pNextInBatch;
          pImplBatch = (VCSRPMhRailImplType *)pRailBatch->pImpl;
        }
      }
      if (!pImplBatch->pNextInBatch)
      {
        pImplBatch->pNextInBatch = pRail;
      }
    }

    // Do not flush batch requests until receiving last in batch.
    if (!npa_request_has_attribute(hClient,
        (npa_request_attribute)NPA_REQUEST_LAST_IN_BATCH))
    {
      bFlush = FALSE;
    }
  }
  else
  {
    pCommandSets = (rpmh_command_set_t *)pImpl->aSets;
  }

  CORE_VERIFY_PTR(pCommandSets);

  /*-----------------------------------------------------------------------*/
  /* Update sleep set if request is not for the next active set.           */
  /*-----------------------------------------------------------------------*/

 //if (hClient->type == VCS_NPA_CLIENT_ACTIVE_FLOOR ||
 //     (hClient->type == NPA_CLIENT_REQUIRED &&
 //     !npa_request_has_attribute(hClient, NPA_REQUEST_NEXT_AWAKE)))
 // {
    /*
     * Get aggregation for REQUIRED client type.
     */
    nHLVL =
      pwr_utils_hlvl_named_resource(
        pImpl->szName,
        NPA_RESOURCE_REQUIRED_REQUEST(hClient->resource),
        &mapped_vlvl);

    pSet = &pCommandSets[RPMH_SET_SLEEP];

    eResult = VCS_RPMhRailImplQueueCommand(hClient, pSet, pImpl->nAddress, nHLVL);
    if (eResult != DAL_SUCCESS)
    {
      return DAL_ERROR;
    }

    pImpl->aHLVL[RPMH_SET_SLEEP] = (uint8_t)nHLVL;
  //}

  /*-----------------------------------------------------------------------*/
  /* Update active or wake set if max aggregation has changed.             */
  /*-----------------------------------------------------------------------*/

  if (npa_request_has_attribute(hClient, NPA_REQUEST_NEXT_AWAKE))
  {
    pSet = &pCommandSets[RPMH_SET_WAKE];
    pImplHLVL = &pImpl->aHLVL[RPMH_SET_WAKE];
  }
  else
  {
    pSet = &pCommandSets[RPMH_SET_ACTIVE];
    pImplHLVL = &pImpl->aHLVL[RPMH_SET_ACTIVE];
  }

  /*
   * Get overall aggregation.
   */
  nHLVL = pwr_utils_hlvl_named_resource(pImpl->szName, eCorner, &mapped_vlvl);

  eResult = VCS_RPMhRailImplQueueCommand(hClient, pSet, pImpl->nAddress, nHLVL);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  *pImplHLVL = (uint8_t)nHLVL;

  /*-----------------------------------------------------------------------*/
  /* Flush all commands added to the set by this point.                    */
  /*-----------------------------------------------------------------------*/

  if (bFlush)
  {
    CORE_VERIFY_PTR(pImpl->pRPMh);
    for (i = 0; i < RPMH_NUM_SETS; i++)
    {
      eResult = VCS_RPMhRailImplFlushSet(&pCommandSets[i], pImpl->pRPMh->hHandle);
      CORE_VERIFY(DAL_SUCCESS == eResult);
    }
  }

  pRail->eCorner = eCorner;

  return DAL_SUCCESS;

} /* END of VCS_RPMhRailImplSetCorner */


/* =========================================================================
**  Function : VCS_RPMhRailImplPostChange
** =========================================================================*/
/**
  This function will dispatch post-change events.

  In batched mode:
    PreChange corner uses prior active state.

  In synchronous mode:
    PreChange is resource->active_state.

  @param hClient [in] -- Pointer to client making request.
  @param eCorner [in] -- Requested corner.

  @return
  DAL_SUCCESS -- Sucessfully configured rail to requested corner.
  DAL_ERROR -- Failed to configure rail to requested corner.

  @dependencies
  None.
*/

static DALResult VCS_RPMhRailImplPostChange
(
  npa_client_handle  hClient,
  rail_voltage_level eCorner
)
{
  VCSRailNodeType         *pRail;
  VCSRPMhRailImplType     *pImpl;
  VCSNPARailEventDataType  RailEventData;

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  CORE_VERIFY(hClient);

  if (NPA_CLIENT_BATCH == hClient->type)
  {
    if (npa_request_has_attribute(hClient,
        (npa_request_attribute)NPA_REQUEST_LAST_IN_BATCH))
    {
      CORE_VERIFY(hClient->resource_data);
      pRail = VCS_RESOURCE_TO_RAIL(hClient->resource_data);
    }
    // short-circuit requests that haven't been flushed.
    else
    {
      return DAL_SUCCESS;
    }
  }
  else
  {
    pRail = VCS_CLIENT_TO_RAIL(hClient);
  }

  CORE_VERIFY_PTR(pRail);

  /*-----------------------------------------------------------------------*/
  /* Dispatch post-change event using last active state.                   */
  /*-----------------------------------------------------------------------*/

  RailEventData.PreChange.nVoltageUV = 0;
  RailEventData.PostChange.nVoltageUV = 0;

  do {
    pImpl = (VCSRPMhRailImplType *)pRail->pImpl;
    CORE_VERIFY_PTR(pImpl);

    RailEventData.PreChange.eCorner = pImpl->eCornerPrior;
    RailEventData.PostChange.eCorner = pRail->eCorner;

          // TODO: NpaApiLib does not support npa_dispatch_custom_events and NPA itself is lacking support for custom events
    // npa_dispatch_custom_events(hClient->resource, (npa_event_type)VCS_NPA_RAIL_EVENT_POST_CHANGE, &RailEventData);
    pRail = pImpl->pNextInBatch;
    pImpl->pNextInBatch = NULL;
  }
  while (pRail);

  return DAL_SUCCESS;

} /* END of VCS_RPMhRailImplPostChange */


/* =========================================================================
**  Function : VCS_RPMhRailImplResourceQuery
** =========================================================================*/
/**
  NPA rail resource query function.

  This function is called to get the following rail information:
    -- Number of corners.
    -- Voltage table for each corner.
    -- Current corner (id / table index).

  @param *pResource  [in]  -- Pointer to the resource in question
  @param  nID        [in]  -- ID of the query.
  @param *pResult    [out] -- Pointer to the data to be filled by this function.

  @return
  npa_query_status - NPA_QUERY_SUCCESS, if query supported.
                   - NPA_QUERY_UNSUPPORTED_QUERY_ID, if query not supported.

  @dependencies
  None.
*/

static npa_query_status VCS_RPMhRailImplResourceQuery
(
  npa_resource   *pResource,
  unsigned int    nID,
  npa_query_type *pResult
)
{
  VCSRailNodeType     *pRail;
  VCSRPMhRailImplType *pImpl;
  uint32               nLevel;

  /*-----------------------------------------------------------------------*/
  /* Validate parameters.                                                  */
  /*-----------------------------------------------------------------------*/

  if (pResource == NULL || pResult == NULL)
  {
    return NPA_QUERY_NULL_POINTER;
  }

  pRail = VCS_RESOURCE_TO_RAIL(pResource);
  if (pRail == NULL || pRail->pImpl == NULL)
  {
    return NPA_QUERY_NULL_POINTER;
  }

  pImpl = (VCSRPMhRailImplType *)pRail->pImpl;

  /*-----------------------------------------------------------------------*/
  /* Check for number of corners supported.                                */
  /*-----------------------------------------------------------------------*/

  if (nID == VCS_NPA_QUERY_VOLTAGE_NUM_ENTRIES)
  {
    pResult->data.value = pwr_utils_named_resource_lvls_count(pImpl->szName);
    pResult->type = NPA_QUERY_TYPE_VALUE;

    return NPA_QUERY_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Check for current corner in VLVL.                                     */
  /*-----------------------------------------------------------------------*/

  if(nID == VCS_NPA_QUERY_VOLTAGE_CURRENT_LEVEL_ID)
  {
    pResult->data.value = pRail->eCorner;
    pResult->type = NPA_QUERY_TYPE_VALUE;

    return NPA_QUERY_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Check for corner VLVL at specified performance level.                 */
  /*-----------------------------------------------------------------------*/

  if (nID >= VCS_NPA_QUERY_VOLTAGE_LEVEL_ID && nID < VCS_NPA_QUERY_END_MARKER)
  {
    nLevel = nID - VCS_NPA_QUERY_VOLTAGE_LEVEL_ID;
    if (nLevel < pwr_utils_named_resource_lvls_count(pImpl->szName))
    {
      pResult->data.value = pwr_utils_vlvl_named_resource(pImpl->szName, nLevel);
      pResult->type = NPA_QUERY_TYPE_VALUE;

      return NPA_QUERY_SUCCESS;
    }
  }

  return NPA_QUERY_UNSUPPORTED_QUERY_ID;

} /* END VCS_RPMhRailImplResourceQuery */


/* =========================================================================
**  Function : VCS_RPMhRailImplInitImpl
** =========================================================================*/
/**
  Initializes the RPMh data for this rail.

  @param *pRail [in] -- Pointer rail node.

  @return
  DAL_ERROR if a corner list not initialized, other DAL_SUCCESS.

  @dependencies
  None.
*/

static DALResult VCS_RPMhRailImplInitImpl
(
  VCSRailNodeType *pRail
)
{
  VCSRPMhRailImplType *pImpl;

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  if (pRail == NULL ||
      pRail->pImpl == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  pImpl = (VCSRPMhRailImplType *)pRail->pImpl;

  /*-----------------------------------------------------------------------*/
  /* Validate name defined.                                                */
  /*-----------------------------------------------------------------------*/

  if (pImpl->szName == NULL || pImpl->pRPMh == NULL)
  {
    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Create RPMh handle.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pImpl->pRPMh->hHandle)
  {
    pImpl->pRPMh->hHandle = rpmh_create_handle(pImpl->pRPMh->eDRVId, "VCS");
    if (pImpl->pRPMh->hHandle == NULL)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Failed to create client handle for RSC DRV.");

      return DAL_ERROR;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Query CMD DB for resource address.                                    */
  /*-----------------------------------------------------------------------*/

  pImpl->nAddress = cmd_db_query_addr(pImpl->szName);
  if (!pImpl->nAddress)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Failed to get valid RSC address for rail[%s]",
      VCS_RAIL_NAME(pRail));

    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Install function pointer for rail resource query.                     */
  /*-----------------------------------------------------------------------*/

  VCS_RAIL_RES_DEF_RAIL(pRail)->query_fcn = VCS_RPMhRailImplResourceQuery;

  /*-----------------------------------------------------------------------*/
  /* Create batch set for this rail.                                       */
  /*-----------------------------------------------------------------------*/

  pImpl->aSets[RPMH_SET_ACTIVE].set = RPMH_SET_ACTIVE;
  pImpl->aSets[RPMH_SET_ACTIVE].num_commands = 0;

  pImpl->aSets[RPMH_SET_SLEEP].set = RPMH_SET_SLEEP;
  pImpl->aSets[RPMH_SET_SLEEP].num_commands = 0;

  pImpl->aSets[RPMH_SET_WAKE].set = RPMH_SET_WAKE;
  pImpl->aSets[RPMH_SET_WAKE].num_commands = 0;

  /*-----------------------------------------------------------------------*/
  /* Initialize SLEEP set vote to lowest state.                            */
  /*-----------------------------------------------------------------------*/

  rpmh_issue_command(pImpl->pRPMh->hHandle, RPMH_SET_SLEEP, FALSE, pImpl->nAddress, 0);

  return DAL_SUCCESS;

} /* END of VCS_RPMhRailImplInitImpl */

