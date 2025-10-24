/*
===========================================================================
*/
/**
  @file ClockDriver.c

  Interface implementation file for the clock device driver.
*/
/*
  ====================================================================

  Copyright (c) 2021-2022 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/ClockDxe/ClockDriver.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "DALDeviceId.h"
#include "ClockDriver.h"
#include "ClockDriverImage.h"
#include "HALclk.h"
#include "DDIChipInfo.h"
#include "DDIPlatformInfo.h"
#include "busywait.h"
#include "DDIHWIO.h"
#include "CoreVerify.h"
#include "DALPropDef.h"

/*=========================================================================
      Externs
==========================================================================*/

extern ClockBSPType ClockBSP;


/*=========================================================================
      Macros
==========================================================================*/

/*
 * This is the maximum number of delay attempts that will be made when
 * waiting for a clock change (config, enable, disable, etc) to propagate
 * to the status register.
 */
#define CLOCK_CONFIG_DELAY_ATTEMPTS 300    /* Expressed in micro-secinds */

#define CLOCK_IS_CONTROLLABLE(n, c) \
  (!CLOCK_FLAG_IS_SET(n, INTERNAL_CONTROL) || \
   CLOCK_FLAG_IS_SET(((ClockClientCtxt *)(c)), INTERNAL_CONTROL))

#define CLOCK_LOCAL_CLIENT_ID 0

#define CLOCK_PD_NAME_LEN 32


/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * GetId function type.
 */
typedef ClockResult (*ClockGetIdFn) (ClockHandle, const char *, ClockIdType *);


/*=========================================================================
      Data
==========================================================================*/

/*
 * Main clock driver context.
 */
static ClockDrvCtxt Clock_DriverCtxt;

/*
 * Object-specific GetId function pointers.
 */
static ClockGetIdFn ClockGetIdFunctions[] =
{
  Clock_GetSourceId,
  Clock_GetPowerDomainId,
  Clock_GetClockId,
  Clock_GetDividerId,
  Clock_GetDebugMuxId,
};


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_MapAddress
** =========================================================================*/
/*
  See ClockDriver.h.
*/

ClockResult Clock_MapAddress
(
  uintptr_t *pnAddr
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockBaseType *pBase;
  uint32_t       i;

  if (*pnAddr == 0)
  {
    return CLOCK_SUCCESS;
  }

  for (i = 0; i < pDrvCtxt->pBSP->nNumBases; i++)
  {
    pBase = &pDrvCtxt->pBSP->aBases[i];

    if (*pnAddr >= pBase->nPhysAddr &&
        *pnAddr <  pBase->nPhysAddr + pBase->nSize)
    {
      *pnAddr = *pnAddr - pBase->nPhysAddr + *pBase->pnVirtAddr;
      return CLOCK_SUCCESS;
    }
  }

  return CLOCK_ERROR;

} /* END Clock_MapAddress */


/* =========================================================================
**  Function : Clock_InitBases
** =========================================================================*/
/*
  See ClockDriver.h.
*/

ClockResult Clock_InitBases
(
  void
)
{
  ClockBSPType                *pBSP = Clock_GetDrvCtxt()->pBSP;
  ClockBaseType               *pBase;
  HAL_clk_ClockDescType       *pHALClock;
  HAL_clk_SourceDescType      *pHALSource;
  HAL_clk_ClockDomainDescType *pHALDomain;
  HAL_clk_DividerDescType     *pHALDivider;
  HAL_clk_PowerDomainDescType *pHALPowerDomain;
  ClockResult                  eResult = CLOCK_SUCCESS;
  uint32_t                     i;

  if (pBSP->aBases == NULL || pBSP->nNumBases == 0)
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Map base regions.                                                     */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < pBSP->nNumBases; i++)
  {
    pBase = &pBSP->aBases[i];
    eResult = Clock_MapHWIORegion(pBase->nPhysAddr, pBase->nSize, pBase->pnVirtAddr);
    if (eResult != CLOCK_SUCCESS)
    {
      return CLOCK_ERROR;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Map individual register addresses.                                    */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < pBSP->nNumClocks; i++)
  {
    pHALClock = &pBSP->aClocks[i].HALClock;
    eResult |= Clock_MapAddress(&pHALClock->mRegisters.nBranchAddr);
    eResult |= Clock_MapAddress(&pHALClock->mRegisters.nResetAddr);
    eResult |= Clock_MapAddress(&pHALClock->mRegisters.mHWVotable.nAddr);
  }

  for (i = 0; i < pBSP->nNumDomains; i++)
  {
    pHALDomain = &pBSP->aDomains[i]->HALDomain;
    eResult |= Clock_MapAddress(&pHALDomain->nCGRAddr);
  }

  for (i = 0; i < pBSP->nNumSources; i++)
  {
    pHALSource = &pBSP->aSources[i]->HALSource;
    eResult |= Clock_MapAddress(&pHALSource->nAddr);
    eResult |= Clock_MapAddress(&pHALSource->VoterRegister.nAddr);
  }

  for (i = 0; i < pBSP->nNumDividers; i++)
  {
    pHALDivider = &pBSP->aDividers[i].HALDivider;
    eResult |= Clock_MapAddress(&pHALDivider->nAddr);
  }

  for (i = 0; i < pBSP->nNumPowerDomains; i++)
  {
    pHALPowerDomain = &pBSP->aPowerDomains[i].HALPowerDomain;
    eResult |= Clock_MapAddress(&pHALPowerDomain->nGDSCRAddr);
    eResult |= Clock_MapAddress(&pHALPowerDomain->VoterRegister.nAddr);
  }

  if (eResult != CLOCK_SUCCESS)
  {
    return CLOCK_ERROR;
  }

  return CLOCK_SUCCESS;

} /* END Clock_InitBases */


/*=========================================================================
**  Function : Clock_InsertLLNode
** =========================================================================*/
/*
  See ClockDriver.h.
*/
void Clock_InsertLLNode
(
  ClockLLNodeType **pListHead,
  ClockLLNodeType  *pNode
)
{
  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pListHead || !pNode)
  {
    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Insert node at beginning of list.                                     */
  /*-----------------------------------------------------------------------*/

  pNode->pNext = *pListHead;
  *pListHead = pNode;

} /* END Clock_InsertLLNode */


/*=========================================================================
**  Function : Clock_RemoveLLNode
** =========================================================================*/
/*
  See ClockDriver.h.
*/
ClockResult Clock_RemoveLLNode
(
  ClockLLNodeType **pListHead,
  ClockLLNodeType  *pNode,
  ClockCleanupFunc  pfCleanup
)
{
  ClockLLNodeType *pTemp;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pListHead || !pNode)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Check if node being removed is positioned at the list head.           */
  /*-----------------------------------------------------------------------*/

  if (pNode == *pListHead)
  {
    *pListHead = pNode->pNext;
  }

  /*-----------------------------------------------------------------------*/
  /* Remove node by joining adjacent neighbors.                            */
  /*-----------------------------------------------------------------------*/

  else
  {
    for (pTemp = *pListHead; pTemp; pTemp = pTemp->pNext)
    {
      if (pTemp->pNext == pNode)
      {
        break;
      }
    }

    if (!pTemp)
    {
      return CLOCK_ERROR_NOT_FOUND;
    }

    else
    {
      pTemp->pNext = pNode->pNext;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Cleanup memory allocated for node.                                    */
  /*-----------------------------------------------------------------------*/

  if (pfCleanup)
  {
    pfCleanup(pNode);
  }

  return CLOCK_SUCCESS;

} /* END Clock_RemoveLLNode */


/*=========================================================================
**  Function : Clock_InvokeFreqChangeCallbacks
** =========================================================================*/
/**
  Traverses through per-resource type callback linked list & invokes client
  callbacks for a given resource ID & event type.

  @param pDomain    [in] -- Pointer to domain node
  @param eEvent     [in] -- Event type
  @param pEventData [in] -- Pointer to event data

  @return
  None.
*/
static void Clock_InvokeFreqChangeCallbacks
(
  ClockDomainNodeType      *pDomain,
  ClockCallbackEventType    eEvent,
  ClockEventDataFreqChange *pEventData
)
{
  ClockCallbackNodeType *pTemp;
  ClockNodeType         *pClock;
  ClockDrvCtxt          *pDrvCtxt = Clock_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  CORE_VERIFY_PTR(pDomain);
  CORE_VERIFY_PTR(pEventData);
  CORE_VERIFY(eEvent < CLOCK_CALLBACK_EVENT_NUM_TYPES);

  /*-----------------------------------------------------------------------*/
  /* Traverse the linked list.                                             */
  /* NOTE: Use the clock callback list for domains.                        */
  /*-----------------------------------------------------------------------*/

  for (pTemp = pDrvCtxt->pCallbacks[CLOCK_ID_CATEGORY_CLOCK]; pTemp;
       pTemp = pTemp->pNext)
  {
    if (pTemp->eEvent == eEvent)
    {
      pClock = Clock_GetClockNode(pTemp->nResourceID);
      CORE_VERIFY_PTR(pClock);

      if (pClock->pDomain == pDomain)
      {
        /* Logging */
        if (CLOCK_GLOBAL_FLAG_IS_SET(LOG_CALLBACK))
        {
          ULOG_RT_PRINTF_3(
            pDrvCtxt->hClockLog,
            "Callback 0x%x start for event %d and resource ID 0x%x",
            pTemp->pfnCallback, eEvent, pTemp->nResourceID);
        }

        /* Invoke the client callback */
        pTemp->pfnCallback(
          pTemp->CallbackCtxt, pTemp->eEvent,
          pTemp->nResourceID, (ClockCallbackData)pEventData);

        /* Logging */
        if (CLOCK_GLOBAL_FLAG_IS_SET(LOG_CALLBACK))
        {
          ULOG_RT_PRINTF_3(
            pDrvCtxt->hClockLog,
            "Callback 0x%x end for event %d and resource ID 0x%x",
            pTemp->pfnCallback, eEvent, pTemp->nResourceID);
        }
      }
    }
  }

} /* END Clock_InvokeFreqChangeCallbacks */


/*=========================================================================
**  Function : Clock_InvokeClientCallbacks
** =========================================================================*/
/**
  Traverses through per-resource type callback linked list & invokes client
  callbacks for a given resource ID & event type.

  @param nId                 [in] -- Resource identifier
  @param eEvent              [in] -- Event type

  @return
  None.
*/
static void Clock_InvokeClientCallbacks
(
  ClockIdType            nId,
  ClockCallbackEventType eEvent
)
{
  ClockCallbackNodeType *pTemp;
  ClockDrvCtxt          *pDrvCtxt = Clock_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  CORE_VERIFY(CLOCK_GET_ID_CATEGORY(nId) < CLOCK_ID_CATEGORY_TOTAL);
  CORE_VERIFY(eEvent < CLOCK_CALLBACK_EVENT_NUM_TYPES);

  /*-----------------------------------------------------------------------*/
  /* Traverse the linked list.                                             */
  /* NOTE: Only power domains supported currently.                         */
  /*-----------------------------------------------------------------------*/

  for (pTemp = pDrvCtxt->pCallbacks[CLOCK_GET_ID_CATEGORY(nId)]; pTemp;
       pTemp = pTemp->pNext)
  {
    if ((pTemp->nResourceID == nId   ) &&
        (pTemp->eEvent      == eEvent))
    {
      /* Logging */
      if (CLOCK_GLOBAL_FLAG_IS_SET(LOG_CALLBACK))
      {
        ULOG_RT_PRINTF_3(
          pDrvCtxt->hClockLog,
          "Callback 0x%x start for event %d and resource ID 0x%x",
          pTemp->pfnCallback, eEvent, nId);
      }

      /* Invoke the client callback */
      pTemp->pfnCallback(
        pTemp->CallbackCtxt, pTemp->eEvent,
        pTemp->nResourceID, NULL);

      /* Logging */
      if (CLOCK_GLOBAL_FLAG_IS_SET(LOG_CALLBACK))
      {
        ULOG_RT_PRINTF_3(
          pDrvCtxt->hClockLog,
          "Callback 0x%x end for event %d and resource ID 0x%x",
          pTemp->pfnCallback, eEvent, nId);
      }
    }
  }

}


/* =========================================================================
**  Function : Clock_DriverDeInit
** =========================================================================*/
/**
  De-initialize the clock driver.

  This function shuts-down the clock driver.  It is not expected to ever
  be called.

  @return
  CLOCK_SUCCESS -- Deinititialization was successful.
  CLOCK_ERROR -- Deinitialization failed.

  @dependencies
  None.
*/

ClockResult Clock_DriverDeInit
(
  void
)
{
  /*-----------------------------------------------------------------------*/
  /* Destroy the mutex object.                                             */
  /*-----------------------------------------------------------------------*/

  DALSYS_DestroyObject(Clock_GetDrvCtxt()->hLock);

  /*-----------------------------------------------------------------------*/
  /* Shut-down complete.                                                   */
  /*-----------------------------------------------------------------------*/

  return CLOCK_SUCCESS;

} /* END Clock_DriverDeInit */


/* =========================================================================
**  Function : ClockStub_DriverDeInit
** =========================================================================*/
/**
  De-initialize the clock driver stub.

  This function shuts-down the clock driver.  It is not expected to ever
  be called.

  @return
  CLOCK_SUCCESS -- Deinititialization was successful.
  CLOCK_ERROR -- Deinitialization failed.

  @dependencies
  None.
*/

ClockResult ClockStub_DriverDeInit
(
  void
)
{
  /*-----------------------------------------------------------------------*/
  /* Shut-down complete.                                                   */
  /*-----------------------------------------------------------------------*/

  return CLOCK_SUCCESS;

} /* END ClockStub_DriverDeInit */


/* =========================================================================
**  Function : Clock_GetClientRefCount
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockClientRefCountType * Clock_GetClientRefCount
(
  ClockHandle              hClient,
  ClockClientRefCountType *pClients
)
{
  ClockClientRefCountType *pClient;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !pClients)
  {
    return NULL;
  }

  /*-----------------------------------------------------------------------*/
  /* Search through linked list for this client.                           */
  /*-----------------------------------------------------------------------*/

  for (pClient = pClients; pClient; pClient = pClient->pNext)
  {
    if (pClient->hClient == hClient)
    {
      break;
    }
  }

  return pClient;

} /* END of Clock_GetClientRefCount */


/* =========================================================================
**  Function : Clock_InsertRefCountClient
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockResult Clock_InsertRefCountClient
(
  ClockHandle               hClient,
  ClockClientRefCountType **pClients
)
{
  ClockClientRefCountType *pTemp;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !pClients)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if client node already present in linked list.          */
  /*-----------------------------------------------------------------------*/

  for (pTemp = *pClients; pTemp; pTemp = pTemp->pNext)
  {
    if (pTemp->hClient == hClient)
    {
      return CLOCK_SUCCESS;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Create new reference count node for this client/node tuple.           */
  /*-----------------------------------------------------------------------*/

  if (DAL_SUCCESS != DALSYS_Malloc(sizeof(ClockClientRefCountType),(void **)(&pTemp)))
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to allocate %lu bytes for new reference count node.", sizeof(ClockClientRefCountType));

    return CLOCK_ERROR_INSUFFICIENT_MEMORY;
  }

  if (!pTemp)
  {
    return CLOCK_ERROR_INSUFFICIENT_MEMORY;
  }

  DALSYS_memset(pTemp, 0, sizeof(ClockClientRefCountType));

  pTemp->hClient = hClient;

  /*
   * Insert into linked list.
   */
  CLOCK_INSERT_LL_NODE(pClients, pTemp);

  return CLOCK_SUCCESS;

} /* END Clock_InsertRefCountClient */


/* =========================================================================
**  Function : Clock_RemoveRefCountClient
** =========================================================================*/
/*
 * TODO
*/

ClockResult Clock_RemoveRefCountClient
(
  ClockHandle               hClient,
  ClockClientRefCountType **pClients
)
{
  ClockClientRefCountType *pTemp;
  ClockResult              eResult;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !pClients)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Look for client ref count in linked list.                             */
  /*-----------------------------------------------------------------------*/

  for (pTemp = *pClients; pTemp; pTemp = pTemp->pNext)
  {
    if (pTemp->hClient == hClient)
    {
      break;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Return SUCCESS if client already removed.                             */
  /*-----------------------------------------------------------------------*/

  if (!pTemp)
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Remove from linked list.                                              */
  /*-----------------------------------------------------------------------*/

  eResult = CLOCK_REMOVE_LL_NODE(pClients, pTemp, free);
  if (eResult != CLOCK_SUCCESS)
  {
    return eResult;
  }

  return CLOCK_SUCCESS;

} /* END Clock_RemoveRefCountClient */

/*=========================================================================
**  Function : Clock_CleanupClient
** =========================================================================*/
/**
  TODO
*/
void Clock_CleanupClient
(
  void *pData
)
{
  ClockBSPType            *pBSP = Clock_GetDrvCtxt()->pBSP;
  ClockClientCtxt         *pClient;
  ClockResult              eResult;
  uint32_t                 i;
  ClockIdType              nClockId;
  ClockIdType              nSourceId;
  ClockIdType              nPowerDomainId;
  ClockClientRefCountType *pClockRefClient;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pData)
  {
    return;
  }

  pClient = (ClockClientCtxt *)pData;

  /*-----------------------------------------------------------------------*/
  /* Release reference counting contexts for all node types.               */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < pBSP->nNumClocks; i++)
  {
    pClockRefClient = Clock_GetClientRefCount((ClockHandle)pClient,
      pBSP->aClocks[i].pClients);

    if (!pClockRefClient)
    {
      continue;
    }

    eResult = Clock_GetClockId((ClockHandle)pClient, pBSP->aClocks[i].szName, &nClockId);

    /*-----------------------------------------------------------------------*/
    /* Disable the clock until reference count for this client becomes 0.    */
    /*-----------------------------------------------------------------------*/

    while (CLOCK_REF_COUNT_TOTAL(pClockRefClient) > 0)
    {
      eResult = Clock_DisableClock((ClockHandle)pClient, nClockId);
      if (eResult != CLOCK_SUCCESS)
      {
        DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
          "Unable to disable clock[%a]: client: %a",
          pBSP->aClocks[i].szName, pClient->szName);
      }
    }

     /*-----------------------------------------------------------------------*/
     /* Remove refcount client type for this client in this clock node        */
     /*-----------------------------------------------------------------------*/

    eResult = Clock_RemoveRefCountClient((ClockHandle)pClient,
      &pBSP->aClocks[i].pClients);
    if (eResult != CLOCK_SUCCESS)
    {
      DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
        "Unable to remove ref count for clock[%a]: client: %a",
        pBSP->aClocks[i].szName, pClient->szName);
    }
  }

  for (i = 0; i < pBSP->nNumSources; i++)
  {
    pClockRefClient = Clock_GetClientRefCount((ClockHandle)pClient,
      pBSP->aSources[i]->pClients);

    if (!pClockRefClient)
    {
      continue;
    }

    eResult = Clock_GetSourceId((ClockHandle)pClient, pBSP->aSources[i]->szName, &nSourceId);

    /*-----------------------------------------------------------------------*/
    /* Disable the source until reference count for this client becomes 0.   */
    /*-----------------------------------------------------------------------*/

    while (CLOCK_REF_COUNT_TOTAL(pClockRefClient) > 0)
    {
      eResult = Clock_DisableSource((ClockHandle)pClient, nSourceId);
      if (eResult != CLOCK_SUCCESS)
      {
        DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
          "Unable to disable Source[%a]: client: %a",
          pBSP->aSources[i]->szName, pClient->szName);
      }
    }


    eResult = Clock_RemoveRefCountClient((ClockHandle)pClient,
      &pBSP->aSources[i]->pClients);
    if (eResult != CLOCK_SUCCESS)
    {
      DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
        "Unable to remove ref count for source[%a]: client: %a",
        pBSP->aSources[i]->szName, pClient->szName);
    }
  }

  for (i = 0; i < pBSP->nNumPowerDomains; i++)
  {
     pClockRefClient = Clock_GetClientRefCount((ClockHandle)pClient,
       pBSP->aPowerDomains[i].pClients);
     if (!pClockRefClient)
     {
       continue;
     }
     eResult = Clock_GetPowerDomainId((ClockHandle)pClient, pBSP->aPowerDomains[i].szName, &nPowerDomainId);

     /*-----------------------------------------------------------------------------*/
     /* Disable the Power Domain until reference count for this client becomes 0.   */
     /*-----------------------------------------------------------------------------*/

     while (CLOCK_REF_COUNT_TOTAL(pClockRefClient) > 0)
     {
       eResult = Clock_DisablePowerDomain((ClockHandle)pClient, nPowerDomainId);
       if (eResult != CLOCK_SUCCESS)
       {
         DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
           "Unable to disable PowerDomain[%a]: client: %a",
           pBSP->aPowerDomains[i].szName, pClient->szName);
       }
     }

     eResult = Clock_RemoveRefCountClient((ClockHandle)pClient,
       &pBSP->aPowerDomains[i].pClients);
     if (eResult != CLOCK_SUCCESS)
     {
       DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
         "Unable to remove ref count for PowerDomain[%a]: client: %a",
         pBSP->aPowerDomains[i].szName, pClient->szName);
     }
  }

  /*-----------------------------------------------------------------------*/
  /* Release allocated memory.                                             */
  /*-----------------------------------------------------------------------*/

  if (pClient->szName)
  {
    free(pClient->szName);
  }

  free(pClient);

} /* END Clock_CleanupClient */


/*=========================================================================
**  Function : Clock_CleanupPD
** =========================================================================*/
/**
  TODO
*/
void Clock_CleanupPD
(
  void *pData
)
{
  ClockPDCtxt *pPD;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pData)
  {
    return;
  }

  pPD = (ClockPDCtxt *)pData;

  /*-----------------------------------------------------------------------*/
  /* Hook for image processing.                                            */
  /*-----------------------------------------------------------------------*/

  if (Clock_DestroyPDEventProcess)
  {
    Clock_DestroyPDEventProcess(pPD);
  }

  /*-----------------------------------------------------------------------*/
  /* Release allocated memory.                                             */
  /*-----------------------------------------------------------------------*/

  if (pPD->szName)
  {
    free(pPD->szName);
  }

  free(pPD);

} /* END Clock_CleanupPD */


/* =========================================================================
**  Function : Clock_GetId
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_GetId
(
  ClockHandle  hClient,
  const char  *szName,
  ClockIdType *pId
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockIdType   nId;
  ClockGetIdFn  fGetId;
  ClockResult   eResult;
  uint32        i;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  if (!hClient || !szName || !pId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  for (i = 0; i < SIZEOF_ARRAY(ClockGetIdFunctions); i++)
  {
    fGetId = ClockGetIdFunctions[i];
    eResult = fGetId(hClient, szName, &nId);
    if (eResult == CLOCK_SUCCESS)
    {
      *pId = nId;
      return CLOCK_SUCCESS;
    }
  }

  *pId = CLOCK_ID_INVALID;
  return CLOCK_ERROR_NOT_FOUND;

} /* END Clock_GetId */


/* =========================================================================
**  Function : Clock_GetClockId
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_GetClockId
(
  ClockHandle  hClient,
  const char  *szName,
  ClockIdType *pId
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockBSPType  *pBSP = pDrvCtxt->pBSP;
  ClockNodeType *pClock;
  uint32_t       nIndex;;
  ClockResult    eResult;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !szName || !pId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Search the array of clock nodes, break if we find a match             */
  /*-----------------------------------------------------------------------*/

  pClock = NULL;
  for (nIndex = 0; nIndex < pBSP->nNumClocks; nIndex++)
  {
    if (strcmp(szName, pBSP->aClocks[nIndex].szName) == 0)
    {
      pClock = &pBSP->aClocks[nIndex];
      break;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Return a pointer to the clock node if found, otherwise return NULL    */
  /*-----------------------------------------------------------------------*/

  if (pClock)
  {
    *pId = CLOCK_MAKE_ID(CLOCK_ID_CATEGORY_CLOCK, nIndex);

    /*
     * Create ref count node for this client/clock tuple.
     */
    eResult = Clock_InsertRefCountClient(hClient, &pClock->pClients);
    return eResult;
  }
  else
  {
    *pId = CLOCK_ID_INVALID;
    return CLOCK_ERROR_NOT_FOUND;
  }

} /* END Clock_GetClockId */


/*=========================================================================
**  Function : Clock_GetClockNode
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockNodeType *Clock_GetClockNode
(
  ClockIdType ClockId
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockIdCategoryType  nCat = (ClockIdCategoryType)CLOCK_GET_ID_CATEGORY(ClockId);
  uint32_t             nIdx = CLOCK_GET_ID_INDEX(ClockId);

  if (nCat == CLOCK_ID_CATEGORY_CLOCK && nIdx < pDrvCtxt->pBSP->nNumClocks)
  {
    return &pDrvCtxt->pBSP->aClocks[nIdx];
  }

  return NULL;

} /* END Clock_GetClockNode */


/* =========================================================================
**  Function : Clock_InitMuxConfigFromHW
** =========================================================================*/
/**
  Initialize ClockMuxConfigType structure from detected HW values.
*/

static DALResult Clock_InitMuxConfigFromHW
(
  ClockDomainNodeType         *pDomain,
  HAL_clk_ClockMuxConfigType  *pHALConfig,
  ClockMuxConfigType          *pFreqConfig
)
{
  const ClockSourceMapType    *pSourceMap;
  DALResult                    eResult;
  rail_voltage_level           eVRegLevel;
  uint32                       nFreqHz;
  uint32                       nDenom;

  if (!pDomain || !pHALConfig || !pFreqConfig)
  {
    return DAL_ERROR;
  }

  DALSYS_memset(pFreqConfig, 0, sizeof(*pFreqConfig));
  DALSYS_memscpy(&pFreqConfig->HALConfig, sizeof(pFreqConfig->HALConfig),
                 pHALConfig,              sizeof(*pHALConfig));

  /*
   * Get source mapping that matches mux select value.
   */
  eResult =
    Clock_GetMappedSource(pDomain->aSourceMap, pHALConfig->nMuxSel, &pSourceMap);
  if (eResult != DAL_SUCCESS || !pSourceMap)
  {
    return DAL_ERROR;
  }
  pFreqConfig->pSource = pSourceMap->pSource;

  /*
   * Determine frequency.
   */
  nDenom = pHALConfig->nDiv2x;
  nFreqHz = ((pSourceMap->nFreqHz * 2 + nDenom / 2) / nDenom);
  if (pHALConfig->nM)
  {
    nDenom = pHALConfig->nN;
    nFreqHz =
      (uint32)(((uint64)nFreqHz * pHALConfig->nM + nDenom / 2) / nDenom);
  }
  pFreqConfig->nFreqHz = nFreqHz;

  /*
   * Determine required corner.
   */
  eResult = Clock_GetRequiredCorner(pDomain->aFMax, nFreqHz, &eVRegLevel);
  if (eResult != DAL_SUCCESS || nFreqHz == 0)
  {
    eResult = Clock_GetMaxDomainCorner(pDomain, &eVRegLevel);
    if (eResult != DAL_SUCCESS)
    {
      return DAL_ERROR;
    }
  }

  pFreqConfig->eVRegLevel = eVRegLevel;
  return DAL_SUCCESS;

} /* END Clock_InitMuxConfigFromHW */


/*=========================================================================
**  Function : Clock_InitDFSDomain
** =========================================================================*/
/**
  Initialize a DFS domain.

  @param  *pDomain [in] -- DFS domain to initialize.

  @return
  CLOCK_SUCCESS -- Initialization was successful.
  CLOCK_ERROR -- Initialization failed.
*/

static ClockResult Clock_InitDFSDomain
(
  ClockDomainNodeType *pDomain
)
{
  HAL_clk_ClockMuxConfigType  DetectedCfg;
  const ClockSourceMapType   *pSourceMap;
  ClockMuxConfigType         *pFreqConfig;
  rail_voltage_level          eVRegLevel;
  ClockResult                 eResult;
  uint32_t                    nFreqHz;
  uint32_t                    nDFSStates;
  uint32_t                    nSize;
  uint32_t                    i;
  uint32_t                    nDenom;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pDomain)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*
   * If DFS isn't enabled in HW, then there is nothing to do.
   */
  if (!HAL_clk_IsClockDomainDFSEnabled(&pDomain->HALDomain))
  {
    return CLOCK_SUCCESS;
  }

  CLOCK_FLAG_SET(pDomain, DFS_CONTROLLED);

  /*-----------------------------------------------------------------------*/
  /* Allocate new BSP array to store DFS configurations.                   */
  /*-----------------------------------------------------------------------*/

  nDFSStates = pDomain->HALDomain.nDFSStates;
  pDomain->nBSPLen = nDFSStates;

  nSize = nDFSStates * sizeof(ClockMuxConfigType);
  if (DAL_SUCCESS != DALSYS_Malloc(nSize, (void **)&pDomain->aBSP))
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to allocate %lu bytes for Clock DFS array.", nSize);

    return CLOCK_ERROR_INSUFFICIENT_MEMORY;
  }

  DALSYS_memset(pDomain->aBSP, 0, nSize);

  /*-----------------------------------------------------------------------*/
  /* Initialize new BSP array with dynamically detected DFS configs.       */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < nDFSStates; i++)
  {
    HAL_clk_DetectDFSMuxConfig(&pDomain->HALDomain, &DetectedCfg, i);

    eResult =
      Clock_GetMappedSource(pDomain->aSourceMap, DetectedCfg.nMuxSel, &pSourceMap);
    if (eResult != CLOCK_SUCCESS || pSourceMap->nFreqHz == 0)
    {
      DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to map mux input to source for DFS domain.");
      return CLOCK_ERROR_INTERNAL;
    }

    nDenom = DetectedCfg.nDiv2x;
    nFreqHz = ((pSourceMap->nFreqHz * 2 + nDenom / 2) / nDenom);

    if (DetectedCfg.nM)
    {
      nDenom = DetectedCfg.nN;
      nFreqHz =
        (uint32_t)(((uint64)nFreqHz * DetectedCfg.nM + nDenom / 2) / nDenom);
    }

    eResult = Clock_GetRequiredCorner(pDomain->aFMax, nFreqHz, &eVRegLevel);
    if (eResult != CLOCK_SUCCESS)
    {
      /*
       * Frequency from boot exceeds our known max, so the fmax has most
       * likely changed. Default to Turbo until the local BSP data is
       * updated.
       */
      eVRegLevel = RAIL_VOLTAGE_LEVEL_TUR;
      DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_WARNING,
        "DFS frequency exceeds known max. Assuming Turbo.");
    }

    pFreqConfig = &pDomain->aBSP[i];
    pFreqConfig->nFreqHz = nFreqHz;
    pFreqConfig->eVRegLevel = eVRegLevel;
    pFreqConfig->pSource = pSourceMap->pSource;
    DALSYS_memscpy(&pFreqConfig->HALConfig, sizeof(pFreqConfig->HALConfig),
                   &DetectedCfg,            sizeof(DetectedCfg));
  }

  return CLOCK_SUCCESS;

} /* END Clock_InitDFSDomain */


/*=========================================================================
**  Function : Clock_InitDFSDomains
** =========================================================================*/
/**
  Initialize DFS domains.

  @return
  CLOCK_SUCCESS -- Initialization was successful.
  CLOCK_ERROR -- Initialization failed.
*/

static ClockResult Clock_InitDFSDomains
(
  void
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockDomainNodeType *pDomain;
  ClockResult          eResult;
  uint32_t             i;

  for (i = 0; i < pDrvCtxt->pBSP->nNumDomains; i++)
  {
    pDomain = pDrvCtxt->pBSP->aDomains[i];
    if (pDomain->HALDomain.nDFSStates > 0)
    {
      eResult = Clock_InitDFSDomain(pDomain);
      if (eResult != CLOCK_SUCCESS)
      {
        return CLOCK_ERROR;
      }
    }
  }

  return CLOCK_SUCCESS;

} /* END Clock_InitDFSDomains */


/* =========================================================================
**  Function : Clock_EnableDFS
** =========================================================================*/
/**
  Enable DFS control for a clock domain.

  @param hClient [in] Handle to the client.
  @param ClockId [in] Clock for which to enable DFS control.
*/

ClockResult Clock_EnableDFS
(
  ClockHandle hClient,
  ClockIdType ClockId
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockDomainNodeType *pDomain;
  ClockMuxConfigType  *pConfig;
  ClockNodeType       *pClock;
  ClockResult          eResult;
  uint32_t             i;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pClock, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  if (!pClock->pDomain || pClock->pDomain->HALDomain.nDFSStates == 0)
  {
    return CLOCK_ERROR_NOT_SUPPORTED;
  }

  pDomain = pClock->pDomain;
  if (CLOCK_FLAG_IS_SET(pDomain, DFS_CONTROLLED))
  {
    return CLOCK_SUCCESS;
  }

  /*
   * Write DFS-supported configurations to HW.
   */
  for (i = 0; i < pDomain->nBSPLen; i++)
  {
    pConfig = &pDomain->aBSP[i];
    if (pConfig->HALConfig.nDFSIdx != 0xFF &&
        Clock_IsBSPSupported(&pConfig->HWVersion))
    {
      HAL_clk_ConfigDFSMux(&pDomain->HALDomain, &pConfig->HALConfig);
    }
  }

  /*
   * Enable DFS control in HW.
   */
  HAL_clk_EnableDFS(&pDomain->HALDomain);

  /*
   * Now that DFS is configured and enabled in HW, initialize the driver node
   * to detect and dynamically create new BSP array from configured DFS HW
   * settings.
   */
  eResult = Clock_InitDFSDomain(pDomain);
  if (eResult != CLOCK_SUCCESS)
  {
    return CLOCK_ERROR_INTERNAL;
  }

  return CLOCK_SUCCESS;

} /* END Clock_EnableDFS */


/* =========================================================================
**  Function : Clock_InitClockDomain
** =========================================================================*/
/**
  Initializes a clock domain.

  This function initializes a clock domain, generally as a result of a call to
  Clock_EnableClockDomain().

  @param  hClient [in] -- Requesting client.
  @param *pClockDomain [in] -- Pointer to a clock domain node.

  @return
  CLOCK_SUCCESS -- The domain was successfully initialized.
  CLOCK_ERROR -- The domain was not enabled.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

ClockResult Clock_InitClockDomain
(
  ClockHandle          hClient,
  ClockDomainNodeType *pClockDomain
)
{
  ClockDrvCtxt               *pDrvCtxt = Clock_GetDrvCtxt();
  HAL_clk_ClockMuxConfigType  DetectedConfig = {0};
  HAL_clk_ClockMuxConfigType *pSafeMuxConfig;
  const ClockMuxConfigType   *pFreqConfig;
  ClockMuxConfigType          NewMuxConfig;
  ClockVRegRequestType        VRegRequest;
  ClockResult                 eResult;
  uint32_t                    i;
  uint32                      nSize;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !pClockDomain)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if (!pClockDomain->aBSP ||
      pClockDomain->pActiveMuxConfig ||
      CLOCK_FLAG_IS_SET(pClockDomain, DFS_CONTROLLED))
  {
    return DAL_SUCCESS;
  }

  /* Check if the domain is suppressible */
  if (CLOCK_FLAG_IS_SET(pClockDomain, SUPPRESSIBLE))
  {
    VRegRequest.bSuppressible = TRUE;
  }
  else
  {
    VRegRequest.bSuppressible = FALSE;
  }

  /* Request Minimum Operating Level (MinSVS) for the rail
   * the domain is on before accessing HW
   */
  VRegRequest.eVRegLevel = RAIL_VOLTAGE_LEVEL_MIN_SVS;
  Clock_VoltageRequest(pClockDomain->nRailMask,
    &pClockDomain->VRegRequest, &VRegRequest);


  HAL_clk_DetectClockMuxConfig(&pClockDomain->HALDomain, &DetectedConfig);

  for (i = 0; i < pClockDomain->nBSPLen; i++)
  {
    pFreqConfig = &pClockDomain->aBSP[i];
    if (!Clock_IsBSPSupported(&pFreqConfig->HWVersion))
    {
      continue;
    }

    /*
     * Check if this configuration matches what was detected.
     */
    if (HAL_clk_IsClockMuxConfigEqual(&DetectedConfig, &pFreqConfig->HALConfig))
    {
      /*
       * If the frequency config has a source to configure, then
       * detect the source configuration as well.
       */
      if (pFreqConfig->pSource && pFreqConfig->pSourceFreqConfig)
      {
        eResult = Clock_DetectSourceConfig(pFreqConfig->pSource);
        if (eResult != CLOCK_SUCCESS)
        {
          return CLOCK_ERROR;
        }
      }

      /*
       * If there is no source component or the active source configuration
       * matches, then we've found the active domain configuration.
       */
      if (!pFreqConfig->pSource ||
          !pFreqConfig->pSourceFreqConfig ||
           pFreqConfig->pSource->pActiveFreqConfig == pFreqConfig->pSourceFreqConfig)
      {
        pClockDomain->pActiveMuxConfig = pFreqConfig;
        pClockDomain->pSource = pFreqConfig->pSource;
        break;
      }
    }
  }

  /*
   * Found a matching BSP entry. Return success.
   */
  if (pClockDomain->pActiveMuxConfig)
  {
    return CLOCK_SUCCESS;
  }

  /*
   * If we didn't find a match for the detected configuration in the BSP data
   * and the detected configuration isn't the default safe configuration, then
   * return an error. Don't flag an error for the safe configuration since it
   * doesn't have any dependencies and including it in every domains BSP
   * data is expensive.
   */
  pSafeMuxConfig = &pDrvCtxt->pBSP->SafeMuxConfig;
  if (HAL_clk_IsClockMuxConfigEqual(&DetectedConfig, pSafeMuxConfig))
  {
    return CLOCK_SUCCESS;
  }

  /*
   * If we fail to find a matching BSP entry and the RCG isn't in its
   * default "safe" configuration, then attempt to dynamically detect
   * and allocate a new configuration.
   */
  eResult = Clock_InitMuxConfigFromHW(pClockDomain, &DetectedConfig, &NewMuxConfig);
  if (eResult == CLOCK_SUCCESS)
  {
    nSize = sizeof(*pClockDomain->pActiveMuxConfig);
    eResult = DALSYS_Malloc(nSize, (void **)&pClockDomain->pActiveMuxConfig);
    if (eResult != CLOCK_SUCCESS)
    {
      ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
        "DALSYS_LOGEVENT_FATAL_ERROR: Unable to allocate %lu bytes for detected initial domain config.", nSize);
      ERR_FATAL("Clock_InitClockDomain", 0, 0, 0);

      return CLOCK_ERROR_INSUFFICIENT_MEMORY;
    }

    DALSYS_memscpy((void *)
      pClockDomain->pActiveMuxConfig, sizeof(*pClockDomain->pActiveMuxConfig),
      &NewMuxConfig,                  sizeof(NewMuxConfig)
    );

    pClockDomain->pSource = pClockDomain->pActiveMuxConfig->pSource;
    CLOCK_FLAG_SET(pClockDomain, DOMAIN_DYNAMIC_CONFIG);
    return CLOCK_SUCCESS;
  }

  /*
   * No configuration found, detected, or allocated.
   */
  return CLOCK_ERROR;

} /* END Clock_InitClockDomain */


/* =========================================================================
**  Function : Clock_EnableClockDomain
** =========================================================================*/
/**
  Enables a clock domain.

  This function enables a clock domain, generally as a result of a call to
  Clock_EnableClock().

  @param  hClient [in] -- Requesting client.
  @param *pClockDomain [in] -- Pointer to a clock domain node.
  @param  nClockFlags  [in] -- Flags for any clock attributes.

  @return
  CLOCK_SUCCESS -- The domain was successfully enabled.
  CLOCK_ERROR -- The domain was not enabled.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

ClockResult Clock_EnableClockDomain
(
  ClockHandle          hClient,
  ClockDomainNodeType *pClockDomain,
  uint32_t             nClockFlags
)
{
  ClockResult          eResult;
  bool                 bSuppressibleRequest;
  ClockVRegRequestType VRegRequest;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !pClockDomain)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize domain if not done yet.                                    */
  /*-----------------------------------------------------------------------*/

  if (pClockDomain->aBSP != NULL &&
      pClockDomain->pActiveMuxConfig == NULL)
  {
    eResult = Clock_InitClockDomain(hClient, pClockDomain);
    if (eResult != CLOCK_SUCCESS)
    {
      return CLOCK_ERROR_INTERNAL;
    }
  }

  /* Check if the clock or domain are suppressible */
  if ((nClockFlags & CLOCK_FLAG_SUPPRESSIBLE) != 0 ||
      CLOCK_FLAG_IS_SET(pClockDomain, SUPPRESSIBLE))
  {
    bSuppressibleRequest = true;
  }
  else
  {
    bSuppressibleRequest = false;
  }

  /*-----------------------------------------------------------------------*/
  /* Only enable on ref count transition from 0 -> 1.                      */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_REF_COUNT(pClockDomain, bSuppressibleRequest))
  {
    /* If this domain has a controllable source, enable it first */
    if (pClockDomain->pSource != NULL)
    {
      eResult = Clock_EnableSourceInternal(hClient, pClockDomain->pSource, bSuppressibleRequest);
      if (eResult != CLOCK_SUCCESS)
      {
        return eResult;
      }
    }

    if (!CLOCK_FLAG_IS_SET(pClockDomain, DOMAIN_HOLD_VREG_REQUEST) &&
        pClockDomain->pActiveMuxConfig != NULL)
    {
      VRegRequest.eVRegLevel = pClockDomain->pActiveMuxConfig->eVRegLevel;

      /*
       * Voltage request is only suppressible when no required client requests
       * have been issued.
       * This first required client request will result in a required voltage
       * request to override the previously issued suppressible request.
       */
      VRegRequest.bSuppressible = bSuppressibleRequest && !CLOCK_REF_COUNT_REQ(pClockDomain);
      Clock_VoltageRequest(pClockDomain->nRailMask, &pClockDomain->VRegRequest, &VRegRequest);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Increment ref count for domain.                                       */
  /*-----------------------------------------------------------------------*/

  CLOCK_REF_COUNT_INC(pClockDomain, bSuppressibleRequest);

  /*-----------------------------------------------------------------------*/
  /* Restore domain to its active configuration after enabling it, since   */
  /* it was set to a safe frequency before disabling.                      */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_REF_COUNT_TOTAL(pClockDomain) == 1 &&
      pClockDomain->pActiveMuxConfig &&
      !CLOCK_FLAG_IS_SET(pClockDomain, DFS_CONTROLLED) &&
      !CLOCK_FLAG_IS_SET(pClockDomain, DOMAIN_FORCE_SETTINGS))
  {
    HAL_clk_ConfigClockMux(&pClockDomain->HALDomain,
      &pClockDomain->pActiveMuxConfig->HALConfig);
  }

  return CLOCK_SUCCESS;

} /* END Clock_EnableClockDomain */


/* =========================================================================
**  Function : Clock_DisableClockDomain
** =========================================================================*/
/**
  Disables a clock domain.

  This function disables a clock domain, generally as a result of a call to
  Clock_DisableClock().

  @param  hClient [in] -- Requesting client.
  @param *pClockDomain [in] -- Pointer to a clock domain node.
  @param  nClockFlags  [in] -- Flags for any clock attributes.

  @return
  CLOCK_SUCCESS -- The domain was successfully disabled.
  CLOCK_ERROR -- The domain was not disabled.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

ClockResult Clock_DisableClockDomain
(
  ClockHandle          hClient,
  ClockDomainNodeType *pClockDomain,
  uint32_t             nClockFlags
)
{
  ClockDrvCtxt         *pDrvCtxt = Clock_GetDrvCtxt();
  ClockResult           eResult;
  bool                  bSuppressibleRequest;
  ClockVRegRequestType  VRegRequest;
  uint32_t              nTimeout = 0;
  bool                  bIsOn;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !pClockDomain)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /* Check if the clock or domain are suppressible */
  if ((nClockFlags & CLOCK_FLAG_SUPPRESSIBLE) != 0 ||
      CLOCK_FLAG_IS_SET(pClockDomain, SUPPRESSIBLE))
  {
    bSuppressibleRequest = true;
  }
  else
  {
    bSuppressibleRequest = false;
  }

  if (CLOCK_REF_COUNT_TOTAL(pClockDomain) == 1)
  {

    /*-----------------------------------------------------------------------*/
    /* In some cases when disabling the last clock in a domain that is       */
    /* configured to a low frequency, it can take extra time for the clock   */
    /* root to receive the "off" signal.  If the "off" signal has not been   */
    /* received before switching the domain to the safe configuration, the   */
    /* clock domain can be left in an unexpected state and lock up during    */
    /* the switch. To avoid reconfiguring the domain root before it receives */
    /* the "off" signal, if there are no more clocks enabled in this domain, */
    /* wait for the root-off signal from HW.                                 */
    /*                                                                       */
    /* If this "off" signal has not been received before the source is       */
    /* turned off, the clock domain can be left in an unexpected state,      */
    /* causing a hang when switching the domain frequency.  To avoid         */
    /* disabling the source before the clock domain receives this off signal,*/
    /* if there are no more clocks enabled in this domain, wait for the      */
    /*root-off signal from HW.                                               */
    /*-----------------------------------------------------------------------*/

    if (CLOCK_FLAG_IS_SET(pClockDomain, DOMAIN_WAIT_FOR_ROOT_OFF))
    {
      if (HAL_clk_IsClockDomainSupported(&pClockDomain->HALDomain, HAL_CLK_CLOCK_DOMAIN_API_ISON))
      {
        bIsOn = HAL_clk_IsClockDomainOn(&pClockDomain->HALDomain);

        while ((bIsOn == true) && (nTimeout++ < 150000))
        {
          busywait(1);
          bIsOn = HAL_clk_IsClockDomainOn(&pClockDomain->HALDomain);
        }

        if (nTimeout == 150000)
        {
          DALSYS_LogEvent(
              DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
              "Clock domain root did not turn off after all domain clocks are off");
          return CLOCK_ERROR_INTERNAL;
        }
      }
    }

    /*
     * Set domain to a safe configuration prior to disabling it to ensure
     * source and voltage dependencies are satisfied if some other entity
     * (HW or SW) enables it without our knowledge.  Skip this if the flag 
     * specifies not to set to a safe mux configuration.
     */
    if (pClockDomain->pActiveMuxConfig &&
        !CLOCK_FLAG_IS_SET(pClockDomain, DFS_CONTROLLED) &&
        !CLOCK_FLAG_IS_SET(pClockDomain, DOMAIN_FORCE_SETTINGS))
    {
      HAL_clk_ConfigClockMux(&pClockDomain->HALDomain, &pDrvCtxt->pBSP->SafeMuxConfig);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Only disable on ref count transition from 1 -> 0.                     */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_REF_COUNT(pClockDomain, bSuppressibleRequest) == 1)
  {
    /*
     * We disable the source for the last insuppressible clock even if
     * another suppressible clock is still enabled because we need to keep
     * reference counting within the source.
     */
    if (pClockDomain->pSource != NULL)
    {
      eResult = Clock_DisableSourceInternal(hClient, pClockDomain->pSource,
        bSuppressibleRequest);
      if (eResult != CLOCK_SUCCESS)
      {
        return eResult;
      }
    }

    /*
     * If there is no suppressible reference count, just remove the voltage
     * request. If there is a suppressible reference count, then update the
     * voltage request to be suppressible.
     */
    if (!CLOCK_FLAG_IS_SET(pClockDomain, DOMAIN_HOLD_VREG_REQUEST) &&
        pClockDomain->pActiveMuxConfig != NULL)
    {
      if (!CLOCK_REF_COUNT(pClockDomain, !bSuppressibleRequest))
      {
        VRegRequest.eVRegLevel = RAIL_VOLTAGE_LEVEL_OFF;
        VRegRequest.bSuppressible = bSuppressibleRequest;
      }
      else
      {
        VRegRequest.eVRegLevel = pClockDomain->pActiveMuxConfig->eVRegLevel;
        VRegRequest.bSuppressible = !bSuppressibleRequest;
      }

      Clock_VoltageRequest(pClockDomain->nRailMask, &pClockDomain->VRegRequest, &VRegRequest);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Decrement ref count for domain.                                       */
  /*-----------------------------------------------------------------------*/

  CLOCK_REF_COUNT_DEC(pClockDomain, bSuppressibleRequest);

  return CLOCK_SUCCESS;

} /* END Clock_DisableClockDomain */


/* =========================================================================
**  Function : Clock_EnableClock
** =========================================================================*/
/*
  Clock_EnableEx implementation for ClockNodeType.
*/

ClockResult Clock_EnableClockEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
  ClockResult              eResult;
  bool                     bIsOn;
  uint32_t                 nTimeout = 0;
  ClockDrvCtxt            *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType           *pClock;
  ClockClientRefCountType *pClientRefCount;
  bool                     bSuppressibleRequest;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pClock, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /*-----------------------------------------------------------------------*/
  /* Get reference count for this client.                                  */
  /*-----------------------------------------------------------------------*/

  pClientRefCount = Clock_GetClientRefCount(hClient, pClock->pClients);
  if (!pClientRefCount)
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to find client(%x) for source: %a.", hClient, pClock->szName);

    return CLOCK_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Get reference counts for this client and clock.                       */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Only enable on ref count transition from 0 -> 1.                      */
  /*-----------------------------------------------------------------------*/

  bSuppressibleRequest = CLOCK_FLAG_IS_SET(pClock, SUPPRESSIBLE) ||
                         CLOCK_FLAG_IS_SET(pClock->pDomain, SUPPRESSIBLE);
  if (!CLOCK_REF_COUNT(pClock, bSuppressibleRequest))
  {
    /* Enable the domain first */
    eResult = Clock_EnableClockDomain(pDrvCtxt->hClient,
      pClock->pDomain, pClock->nFlags);
    if (eResult != CLOCK_SUCCESS)
    {
      DALCLOCK_FREE(pDrvCtxt);
      return CLOCK_ERROR_INTERNAL;
    }

    /* Enable the clock */
    HAL_clk_EnableClock(&pClock->HALClock);

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pClock, LOG_STATE_CHANGE) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_STATE_CHANGE))
    {
      ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
                       "%s (Enabled: 1)", pClock->szName);
    }

    /* Determine whether this clock supports "IsOn" API functionality */
    if (!CLOCK_API_FLAG_IS_SET(nFlags, ENABLE, DONT_WAIT_FOR_CLOCK_ON) &&
        HAL_clk_IsClockSupported(&pClock->HALClock, HAL_CLK_CLOCK_API_ISON))
    {
      bIsOn = HAL_clk_IsClockOn(&pClock->HALClock);

      /* Wait for the clock to turn ON */
      while (!bIsOn && nTimeout++ < CLOCK_CONFIG_DELAY_ATTEMPTS)
      {
        busywait(1);
        bIsOn = HAL_clk_IsClockOn(&pClock->HALClock);
      }

      /* Log a warning if the clock does not turn ON */
      if(!bIsOn)
      {
        ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
            "Unable to turn ON clock: %a.", pClock->szName);
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Increment ref count for client and clock.                             */
  /*-----------------------------------------------------------------------*/

  CLOCK_REF_COUNT_INC(pClock, bSuppressibleRequest);
  CLOCK_REF_COUNT_INC(pClientRefCount, bSuppressibleRequest);

  /*-----------------------------------------------------------------------*/
  /* Log clock enable event                                                */
  /*-----------------------------------------------------------------------*/

  Clock_SWEvent(
    CLOCK_EVENT_CLOCK_STATUS,
    3,
    pClock->nUniqueId,
    1, CLOCK_REF_COUNT_TOTAL(pClock));

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_EnableClock */


/* =========================================================================
**  Function : Clock_DisableClock
** =========================================================================*/
/*
  Clock_DisableEx implementation for ClockNodeType.
*/

ClockResult Clock_DisableClockEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
  ClockResult              eResult;
  ClockDrvCtxt            *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType           *pClock;
  ClockClientRefCountType *pClientRefCount;
  bool                     bSuppressibleRequest;
  bool                     bIsOn;
  uint32_t                 nTimeout = 0;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pClock, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if the clock should not be disabled.                    */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_FLAG_IS_SET(pClock, DO_NOT_DISABLE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(DO_NOT_DISABLE_CLOCKS))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Get reference count for this client.                                  */
  /*-----------------------------------------------------------------------*/

  pClientRefCount = Clock_GetClientRefCount(hClient, pClock->pClients);
  if (!pClientRefCount)
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to find client(%x) for source: %a.", hClient, pClock->szName);

    return CLOCK_ERROR_INTERNAL;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if client doesn't have outstanding enable requests.     */
  /*-----------------------------------------------------------------------*/

  bSuppressibleRequest = CLOCK_FLAG_IS_SET(pClock, SUPPRESSIBLE) ||
                         CLOCK_FLAG_IS_SET(pClock->pDomain, SUPPRESSIBLE);
  if (!CLOCK_REF_COUNT(pClientRefCount, bSuppressibleRequest))
  {
    DALCLOCK_FREE(pDrvCtxt);
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Only disable on ref count transition from 1 -> 0.                     */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_REF_COUNT(pClock, bSuppressibleRequest) == 1)
  {
    /* Disable the clock */
    HAL_clk_DisableClock(&pClock->HALClock);

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pClock, LOG_STATE_CHANGE) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_STATE_CHANGE))
    {
      ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
                       "%s (Enabled: 0)", pClock->szName);
    }

    if (CLOCK_API_FLAG_IS_SET(nFlags, DISABLE, WAIT_FOR_CLOCK_OFF) &&
        HAL_clk_IsClockSupported(&pClock->HALClock, HAL_CLK_CLOCK_API_ISON))
    {
      bIsOn = HAL_clk_IsClockOn(&pClock->HALClock);

      /* Wait for the clock to turn OFF */
      while (bIsOn && nTimeout++ < CLOCK_CONFIG_DELAY_ATTEMPTS)
      {
        busywait(1);
        bIsOn = HAL_clk_IsClockOn(&pClock->HALClock);
      }

      /* Log a warning if the clock does not OFF */
      if (bIsOn)
      {
        ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
                         "Unable to turn OFF clock: %a.", pClock->szName);
      }
    }

    /* Disable the domain */
    eResult = Clock_DisableClockDomain(pDrvCtxt->hClient,
      pClock->pDomain, pClock->nFlags);

    if (eResult != CLOCK_SUCCESS)
    {
      DALCLOCK_FREE(pDrvCtxt);
      return CLOCK_ERROR_INTERNAL;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Decrement client ref count if non-zero.                               */
  /*-----------------------------------------------------------------------*/

  CLOCK_REF_COUNT_DEC(pClientRefCount, bSuppressibleRequest);
  CLOCK_REF_COUNT_DEC(pClock, bSuppressibleRequest);

  /*-----------------------------------------------------------------------*/
  /* Log clock disable event                                               */
  /*-----------------------------------------------------------------------*/

  Clock_SWEvent(
    CLOCK_EVENT_CLOCK_STATUS,
    3,
    pClock->nUniqueId,
    0, CLOCK_REF_COUNT_TOTAL(pClock));

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_DisableClock */


/* =========================================================================
**  Function : Clock_FindClockConfig
** =========================================================================*/
/*
  See ClockDriver.h.
*/

ClockResult Clock_FindClockConfig
(
  ClockDomainNodeType *pDomain,
  uint32_t             nFreqHz,
  ClockFrequencyType   eMatch,
  ClockMuxConfigType **pMatchingConfig
)
{
  uint32_t            nAtLeastFrequency = 0xFFFFFFFF;
  ClockMuxConfigType *pAtLeastConfig = NULL;
  uint32_t            nAtMostFrequency = 0;
  ClockMuxConfigType *pAtMostConfig = NULL;
  ClockMuxConfigType *pMaxConfig = NULL;
  uint32_t            nMaxFrequency = 0;
  ClockMuxConfigType *pBSPConfig;
  uint32_t            i;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pDomain || !pMatchingConfig)
  {
    return CLOCK_ERROR;
  }

  /* Loop over all configurations */
  for (i = 0; i < pDomain->nBSPLen; i++)
  {
    pBSPConfig = &pDomain->aBSP[i];

    /*
     * Skip configurations that aren't for this chip or version.
     */
    if (!Clock_IsBSPSupported(&pBSPConfig->HWVersion))
    {
      continue;
    }

    /* Stop if we find an exact match */
    if (pBSPConfig->nFreqHz == nFreqHz)
    {
      *pMatchingConfig = pBSPConfig;
      return CLOCK_SUCCESS;
    }

    /*
     * Update the maximum frequency seen so far
     */
    if (pBSPConfig->nFreqHz > nMaxFrequency)
    {
      nMaxFrequency = pBSPConfig->nFreqHz;
      pMaxConfig = pBSPConfig;
    }

    /* Look for the lowest at-least frequency */
    if ((pBSPConfig->nFreqHz > nFreqHz) &&
        (pBSPConfig->nFreqHz < nAtLeastFrequency))
    {
      nAtLeastFrequency = pBSPConfig->nFreqHz;
      pAtLeastConfig = pBSPConfig;
    }
    /* Look for the highest at-most frequency */
    else if ((pBSPConfig->nFreqHz < nFreqHz) &&
             (pBSPConfig->nFreqHz > nAtMostFrequency))
    {
      nAtMostFrequency = pBSPConfig->nFreqHz;
      pAtMostConfig = pBSPConfig;
    }
  }

  /* Select a config based on the match criteria */
  switch (eMatch)
  {
    case CLOCK_FREQUENCY_HZ_AT_LEAST:
      if (pAtLeastConfig != NULL)
      {
        *pMatchingConfig = pAtLeastConfig;
        return CLOCK_SUCCESS;
      }
      break;

    case CLOCK_FREQUENCY_HZ_AT_MOST:
      if (pAtMostConfig != NULL)
      {
        *pMatchingConfig = pAtMostConfig;
        return CLOCK_SUCCESS;
      }
      break;

    case CLOCK_FREQUENCY_HZ_CLOSEST:
      if ((pAtLeastConfig != NULL) && (pAtMostConfig == NULL))
      {
        *pMatchingConfig = pAtLeastConfig;
        return CLOCK_SUCCESS;
      }
      else if ((pAtMostConfig != NULL) && (pAtLeastConfig == NULL))
      {
        *pMatchingConfig = pAtMostConfig;
        return CLOCK_SUCCESS;
      }
      else if ((pAtLeastConfig != NULL) && (pAtMostConfig != NULL))
      {
        /* Select the closest match, select the lowest in case of a tie */
        if ((nAtLeastFrequency - nFreqHz) < (nFreqHz - nAtMostFrequency))
        {
          *pMatchingConfig = pAtLeastConfig;
          return CLOCK_SUCCESS;
        }
        else
        {
          *pMatchingConfig = pAtMostConfig;
          return CLOCK_SUCCESS;
        }
        }
      break;

    case CLOCK_FREQUENCY_HZ_AT_LEAST_OR_MAX:
      if (pAtLeastConfig != NULL)
      {
        *pMatchingConfig = pAtLeastConfig;
        return CLOCK_SUCCESS;
      }
      else if (pMaxConfig != NULL)
      {
        *pMatchingConfig = pMaxConfig;
        return CLOCK_SUCCESS;
      }
      break;

    default:
      break;
  }

  /* No match was found */
  *pMatchingConfig = NULL;

  return CLOCK_ERROR;

} /* END Clock_FindClockConfig */


/* =========================================================================
**  Function : Clock_SetClockConfig
** =========================================================================*/
/*
  See ClockDriver.h.
*/

ClockResult Clock_SetClockConfig
(
  ClockHandle          hClient,
  ClockDomainNodeType *pDomain,
  ClockMuxConfigType  *pNewConfig
)
{
  ClockDrvCtxt             *pDrvCtxt = Clock_GetDrvCtxt();
  ClockSourceNodeType      *pNewSource;
  ClockResult               eResult;
  bool                      bVoltageRequest;
  bool                      bSlewing;
  bool                      bStub;
  ClockVRegRequestType      VRegRequest;
  const ClockMuxConfigType *pActiveConfig;
  ClockEventDataFreqChange  EventData;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !pDomain || !pNewConfig)
  {
    return CLOCK_ERROR;
  }

  if (CLOCK_FLAG_IS_SET(pDomain, STUB_HW_RUMI) &&
      (DalPlatformInfo_Platform() == DALPLATFORMINFO_TYPE_RUMI ||
       DalPlatformInfo_Platform() == DALPLATFORMINFO_TYPE_VIRTIO))
  {
    bStub = true;
  }
  else
  {
    bStub = false;
  }

  pActiveConfig = pDomain->pActiveMuxConfig;

  if(CLOCK_FLAG_IS_SET(pDomain, DOMAIN_FORCE_SETTINGS))
  {
    HAL_clk_ConfigClockMux(&pDomain->HALDomain, &pNewConfig->HALConfig);
  }

  /*
   * If the domain is currently disabled, just update the domain's active
   * configuration without updating the RCG since disabled domains are parked
   * in a safe configuration. The new configuration will be applied when
   * enabling the domain.
   *
   * The domain's source will not be configured when being enabled, so that
   * configuration needs to happen here.
   */
  if (CLOCK_REF_COUNT_TOTAL(pDomain)== 0)
  {
    pDomain->pSource = pNewConfig->pSource;
    if(CLOCK_FLAG_IS_SET(pDomain, DOMAIN_DYNAMIC_CONFIG) &&
       pDomain->pActiveMuxConfig != NULL)
    {
      CLOCK_FLAG_CLEAR(pDomain, DOMAIN_DYNAMIC_CONFIG);
      DALSYS_Free((void*)pDomain->pActiveMuxConfig);
    }

    pDomain->pActiveMuxConfig = pNewConfig;
    if (pDomain->pSource && pNewConfig->pSourceFreqConfig)
    {
      eResult = Clock_ConfigSource(pDomain->pSource, pNewConfig->pSourceFreqConfig);
      if (eResult != CLOCK_SUCCESS)
      {
        return CLOCK_ERROR_INTERNAL;
      }
    }

    return CLOCK_SUCCESS;
  }

  /*
   * Determine if we should make a voltage request.  We do so if this
   * domain is not configured to make requests when enabled, or if it
   * is thus configured and is currently enabled.
   */
  bVoltageRequest = !CLOCK_FLAG_IS_SET(pDomain, DOMAIN_HOLD_VREG_REQUEST);

  /*
   * Voltage requests to make if necessary.
   */
  VRegRequest.eVRegLevel = pNewConfig->eVRegLevel;
  VRegRequest.bSuppressible = (CLOCK_REF_COUNT_REQ(pDomain) == 0);

  /*
   * Pre frequency change event broadcast.
   */
  if (pDomain->nCallbackCount)
  {
    EventData.PreChange.nFreqHz = pActiveConfig ? pActiveConfig->nFreqHz : 0;
    EventData.PreChange.eCorner = pActiveConfig ? pActiveConfig->eVRegLevel : RAIL_VOLTAGE_LEVEL_OFF;
    EventData.PostChange.nFreqHz = pNewConfig->nFreqHz;
    EventData.PostChange.eCorner = pNewConfig->eVRegLevel;
    Clock_InvokeFreqChangeCallbacks(pDomain, CLOCK_CALLBACK_EVENT_PRE_FREQ_CHANGE, &EventData);
  }

  /*
   * If we are increasing the voltage requirement, do so now.
   */
  if ((bVoltageRequest == true) &&
      (pNewConfig->eVRegLevel > pDomain->VRegRequest.eVRegLevel))
  {
    Clock_VoltageRequest(pDomain->nRailMask, &pDomain->VRegRequest, &VRegRequest);
  }

  pNewSource = pNewConfig->pSource;

  bSlewing =
    (pActiveConfig &&
     pNewConfig->pSourceFreqConfig != pActiveConfig->pSourceFreqConfig &&
     pNewSource == pDomain->pSource);
  if (bSlewing)
  {
    /*
     * Slewing to different PLL outputs isn't supported, since the driver
     * doesn't know the divider configurations for the dividers based on
     * the mux select in the domain and thus can't determine proper sequencing.
     */
    if (pNewConfig->HALConfig.nMuxSel != pActiveConfig->HALConfig.nMuxSel)
    {
      return CLOCK_ERROR_INTERNAL;
    }

    /*
     * If the domain divider is increasing, then it needs to be updated
     * before slewing the PLL to prevent temporarily slewing above
     * the target frequency.
     */
    if (!CLOCK_FLAG_IS_SET(pDomain, DFS_CONTROLLED) &&
        pNewConfig->HALConfig.nDiv2x > pActiveConfig->HALConfig.nDiv2x &&
        !bStub)
    {
      HAL_clk_ConfigClockMux(&pDomain->HALDomain, &pNewConfig->HALConfig);
    }
  }

  /*
   * Configure the source if required.
   */
  if (pNewSource != NULL && pNewConfig->pSourceFreqConfig != NULL)
  {
    eResult = Clock_ConfigSource(pNewSource, pNewConfig->pSourceFreqConfig);
    if (eResult != CLOCK_SUCCESS)
    {
      // TODO error!
      return eResult;
    }
  }

  /*
   * If the domain is active, and the new source is different from the
   * current one then we enable the new source.
   */
  if (pDomain->pSource != pNewSource &&
      pNewSource != NULL)
  {
    /*
     * If there are insuppressible clocks enabled in this clock domain then we
     * need to make an insuppressible request on the new source.
     */
    if (CLOCK_REF_COUNT_REQ(pDomain) > 0)
    {
      eResult = Clock_EnableSourceInternal(pDrvCtxt->hClient, pNewSource, false);
      if (eResult != CLOCK_SUCCESS)
      {
        return eResult;
      }
    }

    /*
     * If there are suppressible clocks enabled in this clock domain then we
     * need to make a suppressible request on the new source.
     */
    if (CLOCK_REF_COUNT_SUPP(pDomain) > 0)
    {
      eResult = Clock_EnableSourceInternal(pDrvCtxt->hClient, pNewSource, true);
      if (eResult != CLOCK_SUCCESS)
      {
        return eResult;
      }
    }
  }

  /*
   * Configure the clock MUX
   */
  if (!CLOCK_FLAG_IS_SET(pDomain, DFS_CONTROLLED) &&
      (!bSlewing ||
       pNewConfig->HALConfig.nDiv2x <= pActiveConfig->HALConfig.nDiv2x) &&
      !bStub)
  {
    HAL_clk_ConfigClockMux(&pDomain->HALDomain, &pNewConfig->HALConfig);
  }

  /*
   * If we are decreasing the voltage requirement, do so now.
   */
  if ((bVoltageRequest == true) &&
      (pNewConfig->eVRegLevel < pDomain->VRegRequest.eVRegLevel))
  {
    Clock_VoltageRequest(pDomain->nRailMask, &pDomain->VRegRequest, &VRegRequest);
  }

  /*
   * Post frequency change event broadcast.
   */
  if (pDomain->nCallbackCount)
  {
    Clock_InvokeFreqChangeCallbacks(pDomain, CLOCK_CALLBACK_EVENT_POST_FREQ_CHANGE, &EventData);
  }

  /*
   * If the domain is active, and the new source is different from the
   * current then we disable the old source.
   */
  if (pDomain->pSource != pNewSource &&
      pDomain->pSource != NULL)
  {
    /*
     * If there are insuppressible clocks enabled in this clock domain then we
     * need to remove the insuppressible request on the old source.
     */
    if (CLOCK_REF_COUNT_REQ(pDomain) > 0)
    {
      eResult = Clock_DisableSourceInternal(pDrvCtxt->hClient, pDomain->pSource, false);

      if (eResult != CLOCK_SUCCESS)
      {
        return eResult;
      }
    }

    /*
     * If there are suppressible clocks enabled in this clock domain then we
     * need to remove the suppressible request on the old source.
     */
    if (CLOCK_REF_COUNT_SUPP(pDomain) > 0)
    {
      eResult = Clock_DisableSourceInternal(pDrvCtxt->hClient, pDomain->pSource, true);

      if (eResult != CLOCK_SUCCESS)
      {
        return eResult;
      }
    }
  }

  /*
   * Free previous configuration if it was dynamically allocated.
   */
  if (CLOCK_FLAG_IS_SET(pDomain, DOMAIN_DYNAMIC_CONFIG) &&
      pDomain->pActiveMuxConfig != pNewConfig)
  {
    CLOCK_FLAG_CLEAR(pDomain, DOMAIN_DYNAMIC_CONFIG);
    DALSYS_Free((void *)pDomain->pActiveMuxConfig);
  }

  /* Link the domain node to the new source node and update the active config */
  pDomain->pSource = pNewSource;
  pDomain->pActiveMuxConfig = pNewConfig;

  return CLOCK_SUCCESS;

} /* END Clock_SetClockConfig */


/* =========================================================================
**  Function : Clock_SetClockFrequency
** =========================================================================*/
/*
  Clock_SetFrequencyEx implementation for ClockNodeType.
*/

ClockResult Clock_SetClockFrequency
(
  ClockHandle         hClient,
  ClockIdType         ClockId,
  uint32_t            nFreq,
  ClockFrequencyType  eMatch,
  uint32_t           *pnResultFreq
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType       *pClock;
  ClockDomainNodeType *pDomain;
  ClockMuxConfigType  *pNewConfig = NULL;
  ClockResult          eResult;
  uint32_t             nFreqHz;
  uint32_t             nMult;
  uint32_t             nResultFreq;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pDomain = pClock->pDomain;

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pClock, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  if (pDomain == NULL)
  {
    return CLOCK_ERROR_INTERNAL;
  }

  if (pDomain->aBSP == NULL)
  {
    return CLOCK_ERROR_NOT_SUPPORTED;
  }

  /* Initialize the output parameter */
  if (pnResultFreq != NULL)
  {
    *pnResultFreq = 0;
  }

  /* Convert to Hz if necessary. */
  if (eMatch >= CLOCK_FREQUENCY_MHZ_AT_LEAST)
  {
    nMult = 1000000;
    nFreqHz = nFreq * 1000000;
    eMatch -= CLOCK_FREQUENCY_MHZ_AT_LEAST;
  }
  else if (eMatch >= CLOCK_FREQUENCY_KHZ_AT_LEAST)
  {
    nMult = 1000;
    nFreqHz = nFreq * 1000;
     eMatch -= CLOCK_FREQUENCY_KHZ_AT_LEAST;
  }
  else
  {
    nMult = 1;
    nFreqHz = nFreq;
  }

  /* Look for a valid configuration */
  eResult = Clock_FindClockConfig(pDomain, nFreqHz, eMatch, &pNewConfig);

  if ((eResult != CLOCK_SUCCESS) || (pNewConfig == NULL))
  {
    return CLOCK_ERROR_NOT_SUPPORTED;
  }
  
  DALCLOCK_LOCK(pDrvCtxt);

  /* If the new config is the same as the active config, we're done */
  nResultFreq = 0;
  if (pNewConfig != pDomain->pActiveMuxConfig)
  {
    eResult = Clock_SetClockConfig(hClient, pDomain, pNewConfig);
  if (eResult == CLOCK_SUCCESS)
  {
    nResultFreq = pNewConfig->nFreqHz / nMult;

    if (CLOCK_FLAG_IS_SET(pClock, LOG_FREQ_CHANGE) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_FREQ_CHANGE))
    {
      ULOG_RT_PRINTF_2(pDrvCtxt->hClockLog,
        "%s (Freq: %lu)",
        pClock->szName, pNewConfig->nFreqHz);
    }

  /*
   * Only send out SW event when successful.
  */
  Clock_SWEvent(
    CLOCK_EVENT_CLOCK_FREQ,
    2,
    pClock->nUniqueId,
    ((nResultFreq) * nMult) );
    }
    else
    {
      eResult = CLOCK_ERROR_INTERNAL;
    }
  }
  else
  {
    nResultFreq = pDomain->pActiveMuxConfig->nFreqHz / nMult;
  }

  if (pnResultFreq != NULL)
  {
    *pnResultFreq = nResultFreq;
  }

  DALCLOCK_FREE(pDrvCtxt);

  return eResult;

} /* END Clock_SetClockFrequency */


/* =========================================================================
**  Function : Clock_SetClockDivider
** =========================================================================*/
/*
  Clock_SetDivider implementation for ClockNodeType.
*/

ClockResult Clock_SetClockDivider
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nDivider
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType *pClock;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pClock, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /*-----------------------------------------------------------------------*/
  /* Configure the hardware divider.                                       */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  HAL_clk_ConfigClockDivider(&pClock->HALClock, nDivider);

  /* Logging */
  if (CLOCK_FLAG_IS_SET(pClock, LOG_CONFIG_CHANGE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_CONFIG_CHANGE))
  {
    ULOG_RT_PRINTF_2(pDrvCtxt->hClockLog,
                      "%s (Clock Divider: %lu)",
                      pClock->szName, nDivider);
  }

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_SetClockDivider */


/* =========================================================================
**  Function : Clock_InvertClock
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_Invert
(
  ClockHandle hClient,
  ClockIdType ClockId,
  bool        bInvert
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType *pClock;
  ClockResult    eResult = CLOCK_ERROR_NOT_SUPPORTED;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if (CLOCK_GET_ID_CATEGORY(ClockId) != CLOCK_ID_CATEGORY_CLOCK)
  {
    return CLOCK_ERROR_NOT_SUPPORTED;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pClock, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /*-----------------------------------------------------------------------*/
  /* Configure the clock inversion if supported.                           */
  /*-----------------------------------------------------------------------*/

  if (true == HAL_clk_IsClockSupported(&pClock->HALClock, HAL_CLK_CLOCK_API_INVERT))
  {
    DALCLOCK_LOCK(pDrvCtxt);

    HAL_clk_InvertClock(&pClock->HALClock, bInvert);

    eResult = CLOCK_SUCCESS;

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pClock, LOG_INVERT_CHANGE) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_INVERT_CHANGE))
    {
      ULOG_RT_PRINTF_2(pDrvCtxt->hClockLog,
          "%s (Inverted: %lu)",
          pClock->szName, (uint32_t)bInvert);
    }

    DALCLOCK_FREE(pDrvCtxt);
  }

  return eResult;

} /* END Clock_InvertClock */


/* =========================================================================
**  Function : Clock_ResetClock
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_ResetBlock
(
  ClockHandle    hClient,
  ClockIdType    ClockId,
  ClockResetType  eReset
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType *pClock;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if (CLOCK_GET_ID_CATEGORY(ClockId) != CLOCK_ID_CATEGORY_CLOCK)
  {
    return CLOCK_ERROR_NOT_SUPPORTED;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pClock, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /*-----------------------------------------------------------------------*/
  /* Reset clock.                                                          */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  if (eReset == CLOCK_RESET_ASSERT || eReset == CLOCK_RESET_PULSE)
  {
    HAL_clk_ResetClock(&pClock->HALClock, true);

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pClock, LOG_RESET) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_RESET))
    {
      ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
                        "%s (Reset: 1)", pClock->szName);
    }
  }

  if (eReset == CLOCK_RESET_DEASSERT || eReset == CLOCK_RESET_PULSE)
  {
    HAL_clk_ResetClock(&pClock->HALClock, false);

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pClock, LOG_RESET) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_RESET))
    {
      ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
                        "%s (Reset: 0)", pClock->szName);
    }
  }

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_ResetClock */


/* =========================================================================
**  Function : Clock_ResetClockBranch
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_Reset
(
  ClockHandle    hClient,
  ClockIdType    ClockId,
  ClockResetType eReset
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType *pClock;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if (CLOCK_GET_ID_CATEGORY(ClockId) != CLOCK_ID_CATEGORY_CLOCK)
  {
    return CLOCK_ERROR_NOT_SUPPORTED;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pClock, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /*-----------------------------------------------------------------------*/
  /* Reset clock.                                                          */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  if (eReset == CLOCK_RESET_ASSERT || eReset == CLOCK_RESET_PULSE)
  {
    HAL_clk_ResetClockBranch(&pClock->HALClock, true);

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pClock, LOG_RESET) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_RESET))
    {
      ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
                        "%s (ResetBranch: 1)", pClock->szName);
    }
  }

  if (eReset == CLOCK_RESET_DEASSERT || eReset == CLOCK_RESET_PULSE)
  {
    HAL_clk_ResetClockBranch(&pClock->HALClock, false);

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pClock, LOG_RESET) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_RESET))
    {
      ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
                        "%s (ResetBranch: 0)", pClock->szName);
    }
  }

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_ResetClockBranch */


/* =========================================================================
**  Function : Clock_IsClockEnabled
** =========================================================================*/
/*
  Clock_IsEnabled implementation for ClockNodeType.
*/

ClockResult Clock_IsClockEnabled
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  bool        *pbIsEnabled
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType *pClock;
  ClockVRegRequestType VRegRequest;
  bool           bExplicitVotting = FALSE;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId || !pbIsEnabled)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the output argument here.                                  */
  /*-----------------------------------------------------------------------*/

  *pbIsEnabled = false;
  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Get state from the HAL.                                               */
  /*-----------------------------------------------------------------------*/
  /*
   * Request minimum operating level on the parent rail
   */

  if ( pClock->pDomain && pClock->pDomain->nRailMask && (CLOCK_REF_COUNT_TOTAL(pClock->pDomain)==0) )
  {
    VRegRequest.eVRegLevel = RAIL_VOLTAGE_LEVEL_MIN_SVS;
    VRegRequest.bSuppressible = CLOCK_FLAG_IS_SET(pClock->pDomain, SUPPRESSIBLE);

    Clock_VoltageRequest(pClock->pDomain->nRailMask,
      &pClock->pDomain->VRegRequest, &VRegRequest);
    bExplicitVotting = TRUE;
  }

  *pbIsEnabled = HAL_clk_IsClockEnabled(&pClock->HALClock);

  /*
   * Remove minimum operating level on the parent rail
   */
  if (bExplicitVotting)
  {
    VRegRequest.eVRegLevel = RAIL_VOLTAGE_LEVEL_OFF;
    VRegRequest.bSuppressible = CLOCK_FLAG_IS_SET(pClock->pDomain, SUPPRESSIBLE);

    Clock_VoltageRequest(pClock->pDomain->nRailMask,
      &pClock->pDomain->VRegRequest, &VRegRequest);
    bExplicitVotting=FALSE;
  }

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_IsClockEnabled */


/* =========================================================================
**  Function : Clock_IsClockOn
** =========================================================================*/
/*
  Clock_IsOn implementation for ClockNodeType.
*/

ClockResult Clock_IsClockOn
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  bool        *pbIsOn
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType *pClock;
  ClockVRegRequestType VRegRequest;
  bool           bExplicitVotting = FALSE;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId || !pbIsOn)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the output argument here.                                  */
  /*-----------------------------------------------------------------------*/

  *pbIsOn = false;
  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Get state from the HAL.                                               */
  /*-----------------------------------------------------------------------*/
  /*
   * Request minimum operating level on the parent rail
   */

  if ( pClock->pDomain && pClock->pDomain->nRailMask && (CLOCK_REF_COUNT_TOTAL(pClock->pDomain)==0) )
  {
    VRegRequest.eVRegLevel = RAIL_VOLTAGE_LEVEL_MIN_SVS;
    VRegRequest.bSuppressible = CLOCK_FLAG_IS_SET(pClock->pDomain, SUPPRESSIBLE);

    Clock_VoltageRequest(pClock->pDomain->nRailMask,
      &pClock->pDomain->VRegRequest, &VRegRequest);
    bExplicitVotting = TRUE;
  }

  *pbIsOn = HAL_clk_IsClockOn(&pClock->HALClock);

  /*
   * Remove minimum operating level on the parent rail
   */
  if (bExplicitVotting)
  {
    VRegRequest.eVRegLevel = RAIL_VOLTAGE_LEVEL_OFF;
    VRegRequest.bSuppressible = CLOCK_FLAG_IS_SET(pClock->pDomain, SUPPRESSIBLE);

    Clock_VoltageRequest(pClock->pDomain->nRailMask,
      &pClock->pDomain->VRegRequest, &VRegRequest);
    bExplicitVotting = FALSE;
  }

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_IsClockOn */


/* =========================================================================
**  Function : Clock_IsPowerDomainOn
** =========================================================================*/
/*
  Clock_IsOn implementation for ClockPowerDomainNodeType.
*/

ClockResult Clock_IsPowerDomainOn
(
  ClockHandle  hClient,
  ClockIdType  PowerDomainId,
  bool        *pbIsOn
)
{
  ClockDrvCtxt             *pDrvCtxt = Clock_GetDrvCtxt();
  ClockPowerDomainNodeType *pPowerDomain;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !PowerDomainId || !pbIsOn)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pPowerDomain = Clock_GetPowerDomainNode(PowerDomainId);
  if (!pPowerDomain)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the output argument here.                                  */
  /*-----------------------------------------------------------------------*/

  *pbIsOn = false;

  /*-----------------------------------------------------------------------*/
  /* Get state from the HAL.                                               */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  *pbIsOn = HAL_clk_IsPowerDomainOn(&pPowerDomain->HALPowerDomain);

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_IsPowerDomainOn */


/* =========================================================================
**  Function : Clock_GetClockFrequency
** =========================================================================*/
/*
  Clock_GetFrequency implementation for ClockNodeType.
*/

ClockResult Clock_GetClockFrequency
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  uint32_t    *pnFrequencyHz
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType *pClock;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId || !pnFrequencyHz)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if (!pClock->pDomain)
  {
    return CLOCK_ERROR_INTERNAL;
  }

  if (pClock->pDomain->pActiveMuxConfig)
  {
    *pnFrequencyHz = pClock->pDomain->pActiveMuxConfig->nFreqHz;
    return CLOCK_SUCCESS;
  }

  *pnFrequencyHz = 0;
  return CLOCK_ERROR_NOT_INITIALIZED;

} /* END Clock_GetClockFrequency */


/* =========================================================================
**  Function : Clock_SelectExternalSource
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_SelectExternalSourceEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFreqHz,
  uint32_t    nSource,
  uint32_t    nDiv2x,
  uint32_t    nM,
  uint32_t    nN,
  uint32_t    n2D,
  uint32_t    nFlags
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockDomainNodeType *pDomain;
  ClockNodeType       *pClock;
  ClockMuxConfigType  *pNewConfig;
  rail_voltage_level   eVRegLevel;
  ClockResult          eResult;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  /* TODO: only allow nSource that is external? */

  if (!hClient || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if (CLOCK_GET_ID_CATEGORY(ClockId) != CLOCK_ID_CATEGORY_CLOCK)
  {
    return CLOCK_ERROR_NOT_SUPPORTED;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pDomain = pClock->pDomain;
  if (pDomain == NULL)
  {
    return CLOCK_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pClock, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /*
   * Find the voltage corner data for the given frequency, if specified.
   * If the voltage corner data. or the frequency is not specified, then
   * assume the voltage does not matter.
   */
  if (nFreqHz != 0)
  {
    eResult = Clock_GetRequiredCorner(pDomain->aFMax, nFreqHz, &eVRegLevel);
    if (eResult != CLOCK_SUCCESS)
    {
      return CLOCK_ERROR;
    }
  }
  else
  {
    /* TODO: require clients to specify frequency? */
    eVRegLevel = RAIL_VOLTAGE_LEVEL_OFF;
  }

  /*
   * Allocate a new configuration structure
   */

  if (DAL_SUCCESS != DALSYS_Malloc(sizeof(*pNewConfig),(void **)(&pNewConfig)))
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to allocate %lu bytes for allocating a new configuration.",sizeof(*pNewConfig));

    return CLOCK_ERROR_INSUFFICIENT_MEMORY;
  }
  CORE_VERIFY(pNewConfig);

  DALSYS_memset(pNewConfig, 0, sizeof(*pNewConfig));

  /*-----------------------------------------------------------------------*/
  /* Define the mux configuration.                                         */
  /*-----------------------------------------------------------------------*/

  pNewConfig->nFreqHz           = nFreqHz;
  pNewConfig->eVRegLevel        = eVRegLevel;
  pNewConfig->HALConfig.nMuxSel = (uint8_t)nSource;
  pNewConfig->HALConfig.nDiv2x  = (uint8_t)nDiv2x;
  pNewConfig->HALConfig.nM      = (uint16_t)nM;
  pNewConfig->HALConfig.nN      = (uint16_t)nN;

  /*-----------------------------------------------------------------------*/
  /* Set the new configuration                                             */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);
  eResult = Clock_SetClockConfig(hClient, pDomain, pNewConfig);
  if (eResult != DAL_SUCCESS)
  {
    DALSYS_Free((void *)pNewConfig);
  }
  else
  {
    CLOCK_FLAG_SET(pDomain, DOMAIN_DYNAMIC_CONFIG);
  }

  DALCLOCK_FREE(pDrvCtxt);

  return eResult;

} /* END Clock_SelectExternalSource */


/* =========================================================================
**  Function : Clock_GetDebugMuxId
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_GetDebugMuxId
(
  ClockHandle  hClient,
  const char  *szName,
  ClockIdType *pId
)
{
  ClockDrvCtxt *pDrvCtxt = Clock_GetDrvCtxt();
  ClockBSPType *pBSP = pDrvCtxt->pBSP;
  uint32_t      nIndex;
  bool             bFound;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !szName || !pId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Search the array of clock nodes, break if we find a match             */
  /*-----------------------------------------------------------------------*/

  bFound = false;

  for (nIndex = 0; nIndex < pBSP->nNumDebugMuxes; nIndex++)
  {
    if (strcmp(szName, pBSP->aDebugMuxes[nIndex]->szName) == 0)
    {
      bFound = true;
      break;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Return a pointer to the clock node if found, otherwise return NULL    */
  /*-----------------------------------------------------------------------*/

  if (bFound)
  {
    *pId = CLOCK_MAKE_ID(CLOCK_ID_CATEGORY_DEBUGMUX, nIndex);
    return CLOCK_SUCCESS;
  }
  else
  {
    *pId = CLOCK_ID_INVALID;
    return CLOCK_ERROR_NOT_FOUND;
  }

} /* END Clock_GetDebugMuxId */


/*=========================================================================
**  Function : DebugMux_GetDebugMuxNode
** =========================================================================*/
/**
  See DebugMuxDriver.h
*/

ClockDebugMuxType *Clock_GetDebugMuxNode
(
  ClockIdType DebugMuxId
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockIdCategoryType  nCat = (ClockIdCategoryType)CLOCK_GET_ID_CATEGORY(DebugMuxId);
  uint32_t             nIdx = CLOCK_GET_ID_INDEX(DebugMuxId);

  if (nCat == CLOCK_ID_CATEGORY_DEBUGMUX &&
      nIdx < pDrvCtxt->pBSP->nNumDebugMuxes)
  {
    return pDrvCtxt->pBSP->aDebugMuxes[nIdx];
  }

  return NULL;

} /* END Clock_GetDebugMuxNode */


/*=========================================================================
**  Function : Clock_GetDebugMuxInputDiv
** =========================================================================*/
/**
  Get the divider applied to the specific mux input.

  @param *pDebugMux        [in] -- Pointer to debug mux.
  @param  nMuxSel          [in] -- Mux select value for which to return the divider.

  @return
  Divide value applied to input specified by nMuxSel.

  @dependencies
  None.
*/

static uint32_t Clock_GetDebugMuxInputDiv
(
  ClockDebugMuxType *pDebugMux,
  uint32_t           nMuxSel
)
{
  ClockDebugMuxInputDivType *pInputDiv;

  if (!pDebugMux || !pDebugMux->anInputDivs)
  {
    return 1;
  }

  for (pInputDiv = pDebugMux->anInputDivs;
       pInputDiv->nMuxSel != CLOCK_DEBUG_MUX_INPUT_DIV_END;
       pInputDiv++)
  {
    if (pInputDiv->nMuxSel == nMuxSel)
    {
      return MAX(1, pInputDiv->nDivider);
    }
  }

  return 1;

} /* END Clock_GetDebugMuxInputDiv */


/* =========================================================================
**  Function : Clock_MeasureDebugMuxInput
** =========================================================================*/
/*
  Clock_MeasureFrequencyEx implementation for ClockDebugMuxType.
*/

ClockResult Clock_MeasureDebugMuxInput
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  uint32_t     nDebugMuxSel,
  uint32_t    *pnFrequencyHz
)
{
  ClockDrvCtxt      *pDrvCtxt = Clock_GetDrvCtxt();
  uint32_t           nMultiplier;
  ClockDebugMuxType *pDebugMux;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId || !pnFrequencyHz)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate clock resource id.                                           */
  /*-----------------------------------------------------------------------*/

  pDebugMux = Clock_GetDebugMuxNode(ClockId);
  if (!pDebugMux)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Configure requested mux.                                              */
  /*-----------------------------------------------------------------------*/

  DALSYS_SyncEnter(pDrvCtxt->hDebugLock);
  nMultiplier = MAX(1, pDebugMux->nDivider);
  nMultiplier *= Clock_GetDebugMuxInputDiv(pDebugMux, nDebugMuxSel);

  HAL_clk_ConfigDebugMux(&pDebugMux->HALDebugMux, nDebugMuxSel);

  /*-----------------------------------------------------------------------*/
  /* Configure parent muxes.                                               */
  /*-----------------------------------------------------------------------*/

  for (; pDebugMux->pParent != NULL; pDebugMux = pDebugMux->pParent)
  {
    nMultiplier *= MAX(1, pDebugMux->pParent->nDivider);
    nMultiplier *= Clock_GetDebugMuxInputDiv(pDebugMux->pParent,
      pDebugMux->nParentSel);

    HAL_clk_ConfigDebugMux(&pDebugMux->pParent->HALDebugMux,
      pDebugMux->nParentSel);
  }

  /*-----------------------------------------------------------------------*/
  /* Calculate frequency.                                                  */
  /*-----------------------------------------------------------------------*/

  HAL_clk_CalcDebugMuxFreq(&pDebugMux->HALDebugMux, pnFrequencyHz);
  *pnFrequencyHz *= nMultiplier;
  DALSYS_SyncLeave(pDrvCtxt->hDebugLock);

  return CLOCK_SUCCESS;

} /* END Clock_MeasureDebugMuxInput */


/* =========================================================================
**  Function : Clock_MeasureClockFrequency
** =========================================================================*/
/*
  Clock_MeasureFrequencyEx implementation for ClockNodeType.
*/

ClockResult Clock_MeasureClockFrequency
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  uint32_t    *pnFrequencyHz
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockIdType    DebugMuxId;
  ClockNodeType *pClock;
  ClockResult    eResult;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if (pClock->pDebugMux == NULL ||
      pClock->HALClock.nDebugMuxSel == HAL_CLK_NO_DEBUG_MUX_SEL)
  {
    return CLOCK_ERROR_NOT_SUPPORTED;
  }

  eResult = Clock_GetDebugMuxId(pDrvCtxt->hClient, pClock->pDebugMux->szName,
    &DebugMuxId);
  if (eResult != CLOCK_SUCCESS)
  {
    return eResult;
  }

  return Clock_MeasureDebugMuxInput(
    hClient,
    DebugMuxId,
    pClock->HALClock.nDebugMuxSel,
    pnFrequencyHz);

} /* END Clock_MeasureClockFrequency */


/* =========================================================================
**  Function : Clock_GetPowerDomainId
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_GetPowerDomainId
(
  ClockHandle  hClient,
  const char  *szName,
  ClockIdType *pId
)
{
  ClockDrvCtxt             *pDrvCtxt = Clock_GetDrvCtxt();
  ClockBSPType             *pBSP = Clock_GetDrvCtxt()->pBSP;
  ClockPowerDomainNodeType *pPowerDomain;
  ClockResult               eResult;
  uint32_t                  nIndex;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient|| !szName || !pId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Search the array of power domain nodes, break if we find a match      */
  /*-----------------------------------------------------------------------*/

  pPowerDomain = NULL;
  for (nIndex = 0; nIndex < pBSP->nNumPowerDomains; nIndex++)
  {
    if (strcmp(szName, pBSP->aPowerDomains[nIndex].szName) == 0)
    {
      pPowerDomain = &pBSP->aPowerDomains[nIndex];
      break;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Return a pointer to the power domain node if found, otherwise NULL    */
  /*-----------------------------------------------------------------------*/

  if (pPowerDomain)
  {
    *pId = CLOCK_MAKE_ID(CLOCK_ID_CATEGORY_POWERDOMAIN, nIndex);

    /*
     * Create ref count node for this client/powerdomain tuple.
     */
    eResult = Clock_InsertRefCountClient(hClient, &pPowerDomain->pClients);
    return eResult;
  }
  else
  {
    *pId = CLOCK_ID_INVALID;
    return CLOCK_ERROR_NOT_FOUND;
  }

} /* END Clock_GetPowerDomainId */


/*=========================================================================
**  Function : Clock_GetPowerDomainNode
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockPowerDomainNodeType *Clock_GetPowerDomainNode
(
  ClockIdType PowerDomainId
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockIdCategoryType  nCat = (ClockIdCategoryType)CLOCK_GET_ID_CATEGORY(PowerDomainId);
  uint32_t             nIdx = CLOCK_GET_ID_INDEX(PowerDomainId);

  if (nCat == CLOCK_ID_CATEGORY_POWERDOMAIN &&
      nIdx < pDrvCtxt->pBSP->nNumPowerDomains)
  {
    return &pDrvCtxt->pBSP->aPowerDomains[nIdx];
  }

  return NULL;

} /* END Clock_GetPowerDomainNode */


/* =========================================================================
**  Function : Clock_EnablePowerDomain
** =========================================================================*/
/*
  Clock_EnableEx implementation for ClockPowerDomainNodeType.
*/

ClockResult Clock_EnablePowerDomain
(
  ClockHandle hClient,
  ClockIdType PowerDomainId
)
{
  ClockDrvCtxt             *pDrvCtxt = Clock_GetDrvCtxt();
  ClockPowerDomainNodeType *pPowerDomain;
  ClockClientRefCountType  *pClientRefCount;
  bool                      bSuppressibleRequest;
  ClockVRegRequestType      VRegRequest;
  ClockResult               eResult;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !PowerDomainId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate clock resource id.                                           */
  /*-----------------------------------------------------------------------*/

  pPowerDomain = Clock_GetPowerDomainNode(PowerDomainId);
  if (!pPowerDomain)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pPowerDomain, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /*-----------------------------------------------------------------------*/
  /* Get reference count for this client.                                  */
  /*-----------------------------------------------------------------------*/

  pClientRefCount = Clock_GetClientRefCount(hClient, pPowerDomain->pClients);
  if (!pClientRefCount)
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to find client(%x) for power domain: %a.", hClient, pPowerDomain->szName);

    return CLOCK_ERROR_INTERNAL;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Only enable on ref count transition from 0 -> 1.                      */
  /*-----------------------------------------------------------------------*/

  bSuppressibleRequest = CLOCK_FLAG_IS_SET(pPowerDomain, SUPPRESSIBLE);
  if (!CLOCK_REF_COUNT(pPowerDomain, bSuppressibleRequest))
  {
    /*
     * Check if a client has registered for pre-enable callbacks
     */
    if (pPowerDomain->nCallbackCount)
    {
      Clock_InvokeClientCallbacks(
        PowerDomainId, CLOCK_CALLBACK_EVENT_PRE_ENABLE);
    }

    /*
     * Request MOL (minimum operating level) on the parent rail
     * before enabling the power domain.
     */
    if (pPowerDomain->nRailMask)
    {
      VRegRequest.eVRegLevel = RAIL_VOLTAGE_LEVEL_MIN_SVS;
      VRegRequest.bSuppressible = bSuppressibleRequest;

      eResult = Clock_VoltageRequest(pPowerDomain->nRailMask,
        &pPowerDomain->VRegRequest, &VRegRequest);
      if (eResult != CLOCK_SUCCESS)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return CLOCK_ERROR_INTERNAL;
      }
    }

    /*
     * Enable the power domain.
     */
    HAL_clk_EnablePowerDomain(&pPowerDomain->HALPowerDomain);

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pPowerDomain, LOG_STATE_CHANGE) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_POWER_DOMAIN_STATE_CHANGE))
    {
      ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
                       "%s (Enabled: 1)", pPowerDomain->szName);
    }

    /*
     * Check if a client has registered for post-enable callbacks
     */
    if (pPowerDomain->nCallbackCount)
    {
      Clock_InvokeClientCallbacks(
        PowerDomainId, CLOCK_CALLBACK_EVENT_POST_ENABLE);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Increment ref counts.                                                 */
  /*-----------------------------------------------------------------------*/

  CLOCK_REF_COUNT_INC(pClientRefCount, bSuppressibleRequest);
  CLOCK_REF_COUNT_INC(pPowerDomain, bSuppressibleRequest);

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_EnablePowerDomain */


/* =========================================================================
**  Function : Clock_DisablePowerDomain
** =========================================================================*/
/*
  Clock_DisableEx implementation for ClockPowerDomainNodeType.
*/

ClockResult Clock_DisablePowerDomain
(
  ClockHandle hClient,
  ClockIdType PowerDomainId
)
{
  ClockDrvCtxt             *pDrvCtxt = Clock_GetDrvCtxt();
  ClockPowerDomainNodeType *pPowerDomain;
  ClockClientRefCountType  *pClientRefCount;
  bool                      bSuppressibleRequest;
  ClockVRegRequestType      VRegRequest;
  boolean                   bResult;
  ClockResult               eResult;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !PowerDomainId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate clock resource id.                                           */
  /*-----------------------------------------------------------------------*/

  pPowerDomain = Clock_GetPowerDomainNode(PowerDomainId);
  if (!pPowerDomain)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pPowerDomain, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if the clock should not be disabled.                    */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_FLAG_IS_SET(pPowerDomain, DO_NOT_DISABLE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(DO_NOT_DISABLE_POWER_DOMAINS))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Get reference count for this client.                                  */
  /*-----------------------------------------------------------------------*/

  pClientRefCount = Clock_GetClientRefCount(hClient, pPowerDomain->pClients);
  if (!pClientRefCount)
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to find client(%x) for power domain: %a.", hClient, pPowerDomain->szName);

    return CLOCK_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if client doesn't have any outstanding enable requests. */
  /*-----------------------------------------------------------------------*/

  bSuppressibleRequest = CLOCK_FLAG_IS_SET(pPowerDomain, SUPPRESSIBLE);
  if (!CLOCK_REF_COUNT(pClientRefCount, bSuppressibleRequest))
  {
    return CLOCK_SUCCESS;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Only disable on ref count transition from 1 -> 0.                     */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_REF_COUNT(pPowerDomain, bSuppressibleRequest) == 1)
  {
    /*
     * Check if a client has registered for pre-disable callbacks
     */
    if (pPowerDomain->nCallbackCount)
    {
      Clock_InvokeClientCallbacks(
        PowerDomainId, CLOCK_CALLBACK_EVENT_PRE_DISABLE);
    }

    HAL_clk_DisablePowerDomain(&pPowerDomain->HALPowerDomain);

    /*
     * Check if a client has registered for post-disable callbacks
     */
    if (pPowerDomain->nCallbackCount)
    {
      Clock_InvokeClientCallbacks(
        PowerDomainId, CLOCK_CALLBACK_EVENT_POST_DISABLE);
    }

    /*
     * Remove vote on the parent rail.
     */
    if (pPowerDomain->nRailMask)
    {
      /*
       * Wait for power domain to turn off before removing the parent vote,
       * since the rail is still required during the collapse sequence. Do
       * this only if the GDSC is non voteable
       */
      if(pPowerDomain->HALPowerDomain.VoterRegister.nAddr == 0)
      {
      bResult = HAL_clk_WaitForPowerDomainOff(&pPowerDomain->HALPowerDomain);
      if (!bResult)
      {
        return CLOCK_ERROR_INTERNAL;
      }
      }

      VRegRequest.eVRegLevel = RAIL_VOLTAGE_LEVEL_OFF;
      VRegRequest.bSuppressible = bSuppressibleRequest;

      eResult = Clock_VoltageRequest(pPowerDomain->nRailMask,
        &pPowerDomain->VRegRequest, &VRegRequest);
      if (eResult != CLOCK_SUCCESS)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return CLOCK_ERROR_INTERNAL;
      }
    }

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pPowerDomain, LOG_STATE_CHANGE) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_POWER_DOMAIN_STATE_CHANGE))
    {
      ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
                       "%s (Enabled: 0)", pPowerDomain->szName);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Decrement ref counts.                                                 */
  /*-----------------------------------------------------------------------*/

  CLOCK_REF_COUNT_DEC(pClientRefCount, bSuppressibleRequest);
  CLOCK_REF_COUNT_DEC(pPowerDomain, bSuppressibleRequest);

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_DisablePowerDomain */


/* =========================================================================
**  Function : Clock_ConfigureClock
** =========================================================================*/
/*
  Clock_Configure implementation for ClockNodeType.
*/

ClockResult Clock_ConfigureClock
(
  ClockHandle     hClient,
  ClockIdType     ClockId,
  ClockConfigType eConfig
)
{
  ClockResult    eResult = CLOCK_SUCCESS;
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType *pClock;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pClock, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /*-----------------------------------------------------------------------*/
  /* Handle request.                                                       */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  switch (eConfig)
  {
    case CLOCK_CONFIG_HW_CTL_ON:
      HAL_clk_ConfigClock(&pClock->HALClock, HAL_CLK_CONFIG_HW_CTL_ON);
      break;

    case CLOCK_CONFIG_HW_CTL_OFF:
      HAL_clk_ConfigClock(&pClock->HALClock, HAL_CLK_CONFIG_HW_CTL_OFF);
      break;

    case CLOCK_CONFIG_MEM_CORE_FORCE_ON:
      HAL_clk_ConfigClock(&pClock->HALClock, HAL_CLK_CONFIG_MEM_CORE_FORCE_ON);
      break;

    case CLOCK_CONFIG_MEM_CORE_DONT_FORCE_ON:
      HAL_clk_ConfigClock(&pClock->HALClock, HAL_CLK_CONFIG_MEM_CORE_DONT_FORCE_ON);
      break;

    case CLOCK_CONFIG_MEM_PERIPH_FORCE_ON:
      HAL_clk_ConfigClock(&pClock->HALClock, HAL_CLK_CONFIG_MEM_PERIPH_FORCE_ON);
      break;

    case CLOCK_CONFIG_MEM_PERIPH_DONT_FORCE_ON:
      HAL_clk_ConfigClock(&pClock->HALClock, HAL_CLK_CONFIG_MEM_PERIPH_DONT_FORCE_ON);
      break;

    case CLOCK_CONFIG_MEM_PERIPH_FORCE_OFF:
      HAL_clk_ConfigClock(&pClock->HALClock, HAL_CLK_CONFIG_MEM_PERIPH_FORCE_OFF);
      break;

    case CLOCK_CONFIG_MEM_PERIPH_DONT_FORCE_OFF:
      HAL_clk_ConfigClock(&pClock->HALClock, HAL_CLK_CONFIG_MEM_PERIPH_DONT_FORCE_OFF);
      break;

    case CLOCK_CONFIG_DFS_ENABLE:
      eResult = Clock_EnableDFS(hClient, ClockId);
      break;

    default:
      eResult = CLOCK_ERROR_NOT_SUPPORTED;
  }

  DALCLOCK_FREE(pDrvCtxt);

  return eResult;

} /* END Clock_ConfigureClock */


/* =========================================================================
**  Function : Clock_LogState
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_LogState
(
  ClockHandle hClient,
  ULogHandle  hULog,
  uint32_t    nFlags
)
{
  ClockDrvCtxt              *pDrvCtxt = Clock_GetDrvCtxt();
  ClockBSPType              *pBSP = pDrvCtxt->pBSP;
  ClockNodeType             *pClock;
  ClockIdType                ClockId;
  ClockPowerDomainNodeType  *pPowerDomain;
  uint32_t                   i, nFreqHz, nFreqHzConfig;
  int32                      nIsOn, nIsEnabled, nReset;
  bool                       bIsEnabled, bIsOn, bCalcSupported;
  ClockResult                eResultClock;
  DALResult                  eResultDAL;
  const char                *szSource;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if(!hClient || !hULog)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  ULOG_RT_PRINTF_0(hULog, ",CLOCK,ON,ENABLED,RESET,REF COUNT,FREQ CONFIG,FREQ CALC,VOLTAGE,SOURCE");

  /*------------------------------------------------------------------------*/
  /* Log clock state.                                                       */
  /*------------------------------------------------------------------------*/

  for (i = 0; i < pBSP->nNumClocks; i++)
  {
    pClock = &pBSP->aClocks[i];
    eResultClock = Clock_GetClockId(hClient, pClock->szName, &ClockId);
    if (eResultClock != CLOCK_SUCCESS)
    {
      return eResultClock;
    }

    nIsEnabled = nIsOn = nReset = -1;
    nFreqHzConfig = 0;
    bCalcSupported = false;

    if (CLOCK_FLAG_IS_SET(pClock, EXPLICIT_ACCESS_ONLY))
    {
      continue;
    }

    /*
     * Get enabled state.
     */
    if (HAL_clk_IsClockSupported(&pClock->HALClock, HAL_CLK_CLOCK_API_ISENABLED))
    {
      Clock_IsClockEnabled(hClient, ClockId, &bIsEnabled);
      nIsEnabled = bIsEnabled ? 1 : 0;
    }

    /*
     * Get ON state.
     */
    if (HAL_clk_IsClockSupported(&pClock->HALClock, HAL_CLK_CLOCK_API_ISON))
    {
      Clock_IsClockOn(hClient, ClockId, &bIsOn);
      nIsOn = bIsOn ? 1 : 0;
    }

    /*
     * Get reset state.
     */
    if (HAL_clk_IsClockSupported(&pClock->HALClock, HAL_CLK_CLOCK_API_RESET))
    {
      nReset = HAL_clk_IsClockReset(&pClock->HALClock);
    }

    /*
     * Get frequency.
     */
    if (pClock->pDomain->pActiveMuxConfig != NULL)
    {
      nFreqHzConfig = pClock->pDomain->pActiveMuxConfig->nFreqHz;
    }

    /*
     * Calculate frequency.
     */
    if ((nFlags & CLOCK_LOG_STATE_CLOCK_FREQUENCY) &&
        HAL_clk_IsClockSupported(&pClock->HALClock, HAL_CLK_CLOCK_API_CALCFREQ))
    {
      bCalcSupported = true;
      Clock_MeasureClockFrequency(hClient, ClockId, &nFreqHz);
    }

    /*
     * Get source.
     */
    if (pClock->pDomain->pSource)
    {
      szSource = pClock->pDomain->pSource->szName;
    }
    else
    {
      szSource = "";
    }

    /*
     * Log results.
     */
    if (bCalcSupported)
    {
      eResultDAL = ULOG_RT_PRINTF_9(hULog, ",%s,%d,%d,%d,%d,%u,%u,%d,%s",
        pClock->szName, nIsOn, nIsEnabled, nReset, CLOCK_REF_COUNT_REQ(pClock),
        nFreqHzConfig, nFreqHz, pClock->pDomain->VRegRequest.eVRegLevel, szSource);
    }
    else
    {
      eResultDAL = ULOG_RT_PRINTF_8(hULog, ",%s,%d,%d,%d,%d,%u,-1,%d,%s",
        pClock->szName, nIsOn, nIsEnabled, nReset, CLOCK_REF_COUNT_REQ(pClock),
        nFreqHzConfig, pClock->pDomain->VRegRequest.eVRegLevel, szSource);
    }

    if (eResultDAL != DAL_SUCCESS)
    {
      return CLOCK_ERROR_INTERNAL;
    }
  }

  /*------------------------------------------------------------------------*/
  /* Log power domain state.                                                */
  /*------------------------------------------------------------------------*/

  ULOG_RT_PRINTF_0(hULog, "");
  ULOG_RT_PRINTF_0(hULog, "");
  ULOG_RT_PRINTF_0(hULog, ",POWER DOMAIN,ON,ENABLED,REF COUNT");

  for (i = 0; i < pBSP->nNumPowerDomains; i++)
  {
    pPowerDomain = &pBSP->aPowerDomains[i];
    if (CLOCK_FLAG_IS_SET(pPowerDomain, EXPLICIT_ACCESS_ONLY))
    {
      continue;
    }

    bIsEnabled = HAL_clk_IsPowerDomainEnabled(&pBSP->aPowerDomains[i].HALPowerDomain);
    bIsOn = HAL_clk_IsPowerDomainOn(&pBSP->aPowerDomains[i].HALPowerDomain);

    eResultDAL = ULOG_RT_PRINTF_4(hULog, ",%s,%d,%d,%d", pPowerDomain->szName, bIsOn,
      bIsEnabled, CLOCK_REF_COUNT_REQ(pPowerDomain));

    if (eResultDAL != CLOCK_SUCCESS)
    {
      return CLOCK_ERROR_INTERNAL;
    }
  }

  return CLOCK_SUCCESS;

} /* END Clock_LogState */


/* =========================================================================
**  Function : Clock_GetSourceId
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_GetSourceId
(
  ClockHandle  hClient,
  const char  *szName,
  ClockIdType *pId
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockBSPType *pBSP = pDrvCtxt->pBSP;
  ClockSourceNodeType *pSource;
  ClockResult          eResult;
  uint32_t             nIndex;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !szName || !pId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Search the array of source nodes, break if we find a match            */
  /*-----------------------------------------------------------------------*/

  pSource = NULL;
  for (nIndex = 0; nIndex < pBSP->nNumSources; nIndex++)
  {
    if (strcmp(szName, pBSP->aSources[nIndex]->szName) == 0)
    {
      pSource = pBSP->aSources[nIndex];
      break;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Return a pointer to the source node if found, otherwise return NULL   */
  /*-----------------------------------------------------------------------*/

  if (pSource)
  {
    *pId = CLOCK_MAKE_ID(CLOCK_ID_CATEGORY_SOURCE, nIndex);

    /*
     * Create ref count node for this client/source tuple.
     */
    eResult = Clock_InsertRefCountClient(hClient, &pSource->pClients);
    return eResult;
  }
  else
  {
    *pId = CLOCK_ID_INVALID;
    return CLOCK_ERROR_NOT_FOUND;
  }

} /* END Clock_GetSourceId */


/*=========================================================================
**  Function : Source_GetSourceNode
** =========================================================================*/
/**
  See SourceDriver.h
*/

ClockSourceNodeType *Clock_GetSourceNode
(
  ClockIdType SourceId
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockIdCategoryType  nCat = (ClockIdCategoryType)CLOCK_GET_ID_CATEGORY(SourceId);
  uint32_t             nIdx = CLOCK_GET_ID_INDEX(SourceId);

  if (nCat == CLOCK_ID_CATEGORY_SOURCE && nIdx < pDrvCtxt->pBSP->nNumSources)
  {
    return pDrvCtxt->pBSP->aSources[nIdx];
  }

  return NULL;

} /* END Clock_GetSourceNode */


/* =========================================================================
**  Function : Clock_EnableSource
** =========================================================================*/
/*
  Clock_EnableEx implementation for ClockSourceNodeType.
*/

ClockResult Clock_EnableSource
(
  ClockHandle hClient,
  ClockIdType SourceId
)
{
  ClockResult          eResult;
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockSourceNodeType *pSource;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !SourceId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate clock resource id.                                           */
  /*-----------------------------------------------------------------------*/

  pSource = Clock_GetSourceNode(SourceId);
  if (!pSource)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pSource, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  eResult = Clock_EnableSourceInternal(hClient, pSource, CLOCK_FLAG_IS_SET(pSource, SUPPRESSIBLE));

  DALCLOCK_FREE(pDrvCtxt);

  return eResult;

} /* END Clock_EnableSource */


/* =========================================================================
**  Function : Clock_DisableSource
** =========================================================================*/
/*
  Clock_DisableEx implementation for ClockSourceNodeType.
*/

ClockResult Clock_DisableSource
(
  ClockHandle hClient,
  ClockIdType SourceId
)
{
  ClockResult          eResult;
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockSourceNodeType *pSource;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !SourceId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate clock resource id.                                           */
  /*-----------------------------------------------------------------------*/

  pSource = Clock_GetSourceNode(SourceId);
  if (!pSource)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pSource, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  eResult = Clock_DisableSourceInternal(hClient, pSource, CLOCK_FLAG_IS_SET(pSource, SUPPRESSIBLE));

  DALCLOCK_FREE(pDrvCtxt);

  return eResult;

} /* END Clock_DisableSource */


/* =========================================================================
**  Function : Clock_SetSourceFrequency
** =========================================================================*/
/*
  Clock_SetFrequencyEx implementation for ClockSourceNodeType.
*/

ClockResult Clock_SetSourceFrequency
(
  ClockHandle         hClient,
  ClockIdType         SourceId,
  uint32_t            nFreq,
  ClockFrequencyType   eMatch,
  uint32_t           *pnResultFreq
)
{
  const ClockSourceFreqConfigType *pNewConfig = NULL;
  ClockDrvCtxt                    *pDrvCtxt = Clock_GetDrvCtxt();
  ClockSourceNodeType             *pSource;
  ClockResult                      eResult;
  uint32_t                         nFreqHz;
  uint32_t                         nMult;
  uint32_t                         nResultFreq;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !SourceId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate clock resource id.                                           */
  /*-----------------------------------------------------------------------*/

  pSource = Clock_GetSourceNode(SourceId);
  if (!pSource)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pSource, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /* Initialize output parameter */
  if (pnResultFreq != NULL)
  {
    *pnResultFreq = 0;
  }

  /* Convert to Hz if necessary. */
  if (eMatch >= CLOCK_FREQUENCY_MHZ_AT_LEAST)
  {
    nMult = 1000000;
    nFreqHz = nFreq * 1000000;
    eMatch -= CLOCK_FREQUENCY_MHZ_AT_LEAST;
  }
  else if (eMatch >= CLOCK_FREQUENCY_KHZ_AT_LEAST)
  {
    nMult = 1000;
    nFreqHz = nFreq * 1000;
    eMatch -= CLOCK_FREQUENCY_KHZ_AT_LEAST;
  }
  else
  {
    nMult = 1;
    nFreqHz = nFreq;
  }

  /* Look for a valid configuration */
  eResult =
    Clock_FindSourceConfig(
      pSource->aBSP,
      pSource->nBSPLen,
      nFreqHz,
      eMatch,
      &pNewConfig);

  if ((eResult != CLOCK_SUCCESS) || (pNewConfig == NULL))
  {
    return CLOCK_ERROR_NOT_SUPPORTED;
  }

    DALCLOCK_LOCK(pDrvCtxt);

  nResultFreq = 0;

  /* If the new config is the same as the active config, we're done */
  if (pNewConfig != pSource->pActiveFreqConfig)
  {
    eResult = Clock_ConfigSource(pSource, pNewConfig);
    if (eResult == CLOCK_SUCCESS)
    {
      nResultFreq = pNewConfig->nFreqHz / nMult;

      if (CLOCK_FLAG_IS_SET(pSource, LOG_FREQ_CHANGE) ||
          CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_FREQ_CHANGE))
      {
        ULOG_RT_PRINTF_2(pDrvCtxt->hClockLog,
                          "%s (Freq: %lu)",
                          pSource->szName, pNewConfig->nFreqHz);
      }

      /*
       * Only send out SW event when successful.
       */
      Clock_SWEvent(
        CLOCK_EVENT_SOURCE_FREQ,
        2,
        0, /* TODO: log source identifier */
        nResultFreq * nMult);
    }
    else
    {
      eResult = CLOCK_ERROR_INTERNAL;
    }
  }
  else
  {
    nResultFreq = pSource->pActiveFreqConfig->nFreqHz;
  }

  if (pnResultFreq != NULL)
  {
    *pnResultFreq = nResultFreq;
  }

    DALCLOCK_FREE(pDrvCtxt);
  return eResult;

} /* END Clock_SetSourceFrequency */


/* =========================================================================
**  Function : Clock_GetSourceFrequency
** =========================================================================*/
/*
  Clock_GetFrequency implementation for ClockSourceNodeType.
*/

ClockResult Clock_GetSourceFrequency
(
  ClockHandle  hClient,
  ClockIdType  SourceId,
  uint32_t    *pnFrequencyHz
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockSourceNodeType *pSource;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !SourceId || !pnFrequencyHz)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate clock resource id.                                           */
  /*-----------------------------------------------------------------------*/

  pSource = Clock_GetSourceNode(SourceId);
  if (!pSource)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if (pSource->pActiveFreqConfig != NULL)
  {
    *pnFrequencyHz = pSource->pActiveFreqConfig->nFreqHz;
    return CLOCK_SUCCESS;
  }

  *pnFrequencyHz = 0;
  return CLOCK_ERROR_NOT_INITIALIZED;

} /* END Clock_GetSourceFrequency */


/*=========================================================================
**  Function : Clock_IsBSPSupported
** =========================================================================*/
/**
 *
  See ClockDriver.h
*/

bool    Clock_IsBSPSupported
(
  const ClockHWVersionType *pHWVersion
)
{
  uint32_t                 nHWVersion, nHWMaxVersion, nHWMinVersion;
  DalChipInfoIdType        eChipId;
  const DalChipInfoIdType *aeChipInfoId;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pHWVersion)
  {
    return false;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate chip family. If not provided then we do not check.           */
  /*-----------------------------------------------------------------------*/

  if ( (pHWVersion->eChipInfoFamily != 0) &&
       (pHWVersion->eChipInfoFamily != DalChipInfo_ChipFamily()) )
  {
    return false;
  }

  /*-----------------------------------------------------------------------*/
  /* Ensure the specific chip ID is supported.                             */
  /*-----------------------------------------------------------------------*/

  aeChipInfoId = pHWVersion->aeChipInfoId;

  if (aeChipInfoId != NULL)
  {
    eChipId = DalChipInfo_ChipId();

    while (*aeChipInfoId < DALCHIPINFO_NUM_IDS)
    {
      if (eChipId == *aeChipInfoId)
      {
        break;
      }

      aeChipInfoId++;
    }

    if (*aeChipInfoId == DALCHIPINFO_NUM_IDS)
    {
      return false;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Get the actual hardware revision.                                     */
  /*-----------------------------------------------------------------------*/

  nHWVersion = HAL_clk_GetChipVersion();

  nHWMinVersion =
    DALCHIPINFO_VERSION(pHWVersion->Min.nMajor, pHWVersion->Min.nMinor);
  nHWMaxVersion =
    DALCHIPINFO_VERSION(pHWVersion->Max.nMajor, pHWVersion->Max.nMinor);

  /*-----------------------------------------------------------------------*/
  /* No chip version data implies support in all HW versions.              */
  /*-----------------------------------------------------------------------*/

  if ( (nHWMinVersion == 0) && (nHWMaxVersion == 0) )
  {
    return true;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate the HW version falls within the min/max.                     */
  /*-----------------------------------------------------------------------*/

  if ( (nHWVersion >= nHWMinVersion) && (nHWVersion < nHWMaxVersion) )
  {
    return true;
  }
  else
  {
    return false;
  }
}


/* =========================================================================
**  Function : Clock_GetDividerId
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_GetDividerId
(
  ClockHandle  hClient,
  const char  *szName,
  ClockIdType *pId
)
{
  ClockDrvCtxt *pDrvCtxt = Clock_GetDrvCtxt();
  ClockBSPType *pBSP = pDrvCtxt->pBSP;
  uint32_t      nIndex;
  bool             bFound;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !szName || !pId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Search the array of clock nodes, break if we find a match             */
  /*-----------------------------------------------------------------------*/

  bFound = false;

  for (nIndex = 0; nIndex < pBSP->nNumDividers; nIndex++)
  {
    if (strcmp(szName, pBSP->aDividers[nIndex].szName) == 0)
    {
      bFound = true;
      break;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Return a pointer to the clock node if found, otherwise return NULL    */
  /*-----------------------------------------------------------------------*/

  if (bFound)
  {
    *pId = CLOCK_MAKE_ID(CLOCK_ID_CATEGORY_DIVIDER, nIndex);
    return CLOCK_SUCCESS;
  }
  else
  {
    *pId = CLOCK_ID_INVALID;
    return CLOCK_ERROR_NOT_FOUND;
  }

} /* END Clock_GetDividerId */


/*=========================================================================
**  Function : Clock_GetDividerNode
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockDividerNodeType * Clock_GetDividerNode
(
  ClockIdType DividerId
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockIdCategoryType  nCat = (ClockIdCategoryType)CLOCK_GET_ID_CATEGORY(DividerId);
  uint32_t             nIdx = CLOCK_GET_ID_INDEX(DividerId);

  if (nCat == CLOCK_ID_CATEGORY_DIVIDER && nIdx < pDrvCtxt->pBSP->nNumDividers)
  {
    return &pDrvCtxt->pBSP->aDividers[nIdx];
  }

  return NULL;

} /* END Clock_GetDividerNode */


/* =========================================================================
**  Function : Clock_SetClockDivider
** =========================================================================*/
/*
  Clock_SetDivider implementation for ClockDividerNodeType.
*/

ClockResult Clock_SetDividerDivider
(
  ClockHandle hClient,
  ClockIdType DividerId,
  uint32_t    nDivider
)
{
  ClockDrvCtxt         *pDrvCtxt = Clock_GetDrvCtxt();
  ClockDividerNodeType *pDivider;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !DividerId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate clock resource id.                                           */
  /*-----------------------------------------------------------------------*/

  pDivider = Clock_GetDividerNode(DividerId);
  if (!pDivider)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify client has permissions.                                        */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_IS_CONTROLLABLE(pDivider, hClient))
  {
    return CLOCK_ERROR_NOT_ALLOWED;
  }

  /*-----------------------------------------------------------------------*/
  /* Configure the hardware divider.                                       */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  HAL_clk_ConfigDivider(&pDivider->HALDivider, nDivider);

  /* Logging */
  if (CLOCK_FLAG_IS_SET(pDivider, LOG_CONFIG_CHANGE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_CONFIG_CHANGE))
  {
    ULOG_RT_PRINTF_2(pDrvCtxt->hClockLog,
                     "%s (Divider: %lu)",
                     pDivider->szName, nDivider);
  }

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_SetClockDivider */


/* =========================================================================
**  Function : Clock_GetFrequencyPlan
** =========================================================================*/
/**
  See Clock.h
*/

ClockResult Clock_GetFrequencyPlan
(
  ClockHandle         hClient,
  ClockIdType         ClockId,
  ClockFreqPlanType **aFreqPlan,
  uint32_t           *nSize
)
{
  ClockDrvCtxt       *pDrvCtxt = Clock_GetDrvCtxt();
  ClockMuxConfigType  *pBSP;
  ClockFreqPlanType   *pFreqPlan;
  ClockNodeType      *pClock;
  uint32_t            nBytes, nBSPTotal = 0;
  uint32_t            i;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !nSize || !ClockId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if (!pClock->pDomain || pClock->pDomain->aBSP == NULL)
  {
    *nSize = 0;
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Count total number of supported frequencies.                          */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < pClock->pDomain->nBSPLen; i++)
  {
    pBSP = &pClock->pDomain->aBSP[i];
    if (Clock_IsBSPSupported(&pBSP->HWVersion))
    {
      nBSPTotal++;
    }
  }

  if (!aFreqPlan)
  {
    *nSize = nBSPTotal;
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* If the client passes a NULL pointer, allocate the array for them.     */
  /*-----------------------------------------------------------------------*/

  if (*aFreqPlan == NULL)
  {
    *nSize = nBSPTotal;
    nBytes = nBSPTotal * sizeof(ClockFreqPlanType);

    if (DALSYS_Malloc(nBytes, (void **)aFreqPlan) != DAL_SUCCESS)
    {
      DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_ERROR,
        "Unable to allocate %lu bytes for %a frequency plan.",
                        nBytes, pClock->szName);
      *nSize = 0;
      return CLOCK_ERROR_INSUFFICIENT_MEMORY;
    }
  }

  if (*nSize < nBSPTotal)
  {
    /*
     * Buffer is too small. Return an error and inform the client of
     * the required buffer size.
     */
    *nSize = nBSPTotal;
    return CLOCK_ERROR_INSUFFICIENT_MEMORY;
  }

  /*-----------------------------------------------------------------------*/
  /* Fill in the frequency plan.                                           */
  /*-----------------------------------------------------------------------*/

  pFreqPlan = *aFreqPlan;
  for (i = 0; i < pClock->pDomain->nBSPLen; i++)
  {
    pBSP = &pClock->pDomain->aBSP[i];
    if (!Clock_IsBSPSupported(&pBSP->HWVersion))
    {
      continue;
    }

    pFreqPlan->nFreqHz = pBSP->nFreqHz;
    pFreqPlan->eVRegLevel = pBSP->eVRegLevel;
    pFreqPlan++;
  }

  *nSize = nBSPTotal;
  return CLOCK_SUCCESS;

} /* END Clock_GetFrequencyPlan */


/*=========================================================================
**  Function : Clock_GetDomainNumPerfLevels
** =========================================================================*/
/**
  See ClockDriver.h
*/

uint32_t Clock_GetDomainNumPerfLevels
(
  ClockDomainNodeType *pDomain
)
{
  ClockMuxConfigType  *pConfig;
  uint32               i;
  uint32               nNumLevels = 0;

  if (!pDomain || !pDomain->aBSP)
  {
    return 0;
  }

  for (i = 0; i < pDomain->nBSPLen; i++)
  {
    pConfig = &pDomain->aBSP[i];
    if (Clock_IsBSPSupported(&pConfig->HWVersion))
    {
      nNumLevels++;
    }
  }

  return nNumLevels;
}


/*=========================================================================
**  Function : Clock_GetDomainPerfLevelConfig
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockMuxConfigType *Clock_GetDomainPerfLevelConfig
(
  ClockDomainNodeType *pDomain,
  uint32               nPerfLevel
)
{
  ClockMuxConfigType  *pConfig;
  uint32               i;
  uint32               nCurLevel;

  if (!pDomain || !pDomain->aBSP)
  {
    return NULL;
  }

  for (i = 0, nCurLevel = 0; i < pDomain->nBSPLen; i++)
  {
    pConfig = &pDomain->aBSP[i];
    if (Clock_IsBSPSupported(&pConfig->HWVersion))
    {
      if (nCurLevel == nPerfLevel)
      {
        return pConfig;
      }

      nCurLevel++;
    }
  }

  return NULL;
}


/* =========================================================================
**  Function : Clock_QueryClock
** =========================================================================*/
/**
  Clock_Query implementation for ClockNodeType.
*/

ClockResult Clock_QueryClock
(
  ClockHandle            hClient,
  ClockIdType            ClockId,
  ClockQueryType         eQuery,
  uint32_t               nIndex,
  ClockQueryResultType  *pResult
)
{
  ClockNodeType       *pClock;
  ClockDomainNodeType *pDomain;
  ClockMuxConfigType  *pFreqConfig;
  const char          *szName = "";
  ClockBSPType        *pBSP = Clock_GetDrvCtxt()->pBSP;
  uint8_t              i, nCount;

  pClock = Clock_GetClockNode(ClockId);
  if (!hClient || !pClock || !pResult)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pDomain = pClock->pDomain;
  if (!pDomain)
  {
    return CLOCK_ERROR_INTERNAL;
  }

  pResult->eType = eQuery;

  /*-----------------------------------------------------------------------*/
  /* Handle top-level object queries.                                      */
  /*-----------------------------------------------------------------------*/

  switch (eQuery)
  {
    case CLOCK_QUERY_NUM_PERF_LEVELS:
      pResult->Data.nNumPerfLevels = Clock_GetDomainNumPerfLevels(pDomain);
      return CLOCK_SUCCESS;

    case CLOCK_QUERY_RAIL_NAME:
      for (i = 0, nCount = 0;
           i < pBSP->nNumRails && i < CLOCK_MAX_RAIL_INDICES;
           i++)
      {
        /* Skip rails not included in mask */
        if (!CLOCK_RAIL_MASK_SET(pDomain->nRailMask, i))
        {
          continue;
        }

        /* Stop if found the desired rail instance in bit mask */
        if (nCount == nIndex)
        {
          szName = pBSP->aRails[i]->szName;
          break;
        }

        /* Keep searching for next rail in mask */
        nCount++;
      }
      strlcpy(pResult->Data.szRailName, szName, CLOCK_MAX_NAME_LEN);
      return CLOCK_SUCCESS;

    case CLOCK_QUERY_DFS_ENABLED:
      pResult->Data.bDFSEnabled =
        HAL_clk_IsClockDomainDFSEnabled(&pDomain->HALDomain);
      return CLOCK_SUCCESS;

    case CLOCK_QUERY_REF_COUNT:
      pResult->Data.nRefCount = CLOCK_REF_COUNT_TOTAL(pClock);
      return CLOCK_SUCCESS;

    default:
      break;
  }

  /*-----------------------------------------------------------------------*/
  /* Handle performance level queries.                                     */
  /*-----------------------------------------------------------------------*/

  pFreqConfig = Clock_GetDomainPerfLevelConfig(pDomain, nIndex);
  if (!pFreqConfig)
  {
    return CLOCK_ERROR_NOT_SUPPORTED;
  }

  switch (eQuery)
  {
    case CLOCK_QUERY_PERF_LEVEL_FREQ_HZ:
      pResult->Data.nPerfLevelFreqHz = pFreqConfig->nFreqHz;
      break;

    case CLOCK_QUERY_PERF_LEVEL_CORNER:
      pResult->Data.ePerfLevelCorner = pFreqConfig->eVRegLevel;
      break;

    case CLOCK_QUERY_PERF_LEVEL_DFS_IDX:
      pResult->Data.nPerfLevelDFSIdx = pFreqConfig->HALConfig.nDFSIdx;
      break;

    case CLOCK_QUERY_PERF_LEVEL_SRC_NAME:
      if (pFreqConfig->pSource)
      {
        szName = pFreqConfig->pSource->szName;
      }
      strlcpy(pResult->Data.szPerfLevelSrcName, szName, CLOCK_MAX_NAME_LEN);
      break;

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }

  return CLOCK_SUCCESS;

} /* END Clock_QueryClock */


/* =========================================================================
**  Function : Clock_GetHighestFreqConfig
** =========================================================================*/
/**
  Get the highest frequency configuration supported by domain.

  @param *pDomain[in] -- Pointer to a clock domain.

  @return
  Non-NULL  -- Highest configuration found.
  NULL      -- No supported configurations found.

  @dependencies
  None.
*/

static ClockMuxConfigType * Clock_GetHighestFreqConfig
(
  ClockDomainNodeType *pDomain
)
{
  ClockMuxConfigType  *pConfig;
  int32                i;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pDomain || !pDomain->aBSP)
  {
    return NULL;
  }

  for (i = pDomain->nBSPLen - 1; i >= 0; i--)
  {
    pConfig = &pDomain->aBSP[i];
    if (Clock_IsBSPSupported(&pConfig->HWVersion))
    {
      return pConfig;
    }
  }

  return NULL;

}; /* END Clock_GetHighestFreqConfig */


/* =========================================================================
**  Function : Clock_InitNPA
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockResult Clock_InitNPA
(
  void
)
{
  ClockDrvCtxt       *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNPANodeType    *pNodeDef;
  ClockNPACtxtType    *pNPACtxt;
  ClockMuxConfigType  *pConfig;
  ClockNodeType       *pClock;
  ClockIdType          nClockId;
  ClockResult         eResult;
  uint32_t            nMaxFreqKHz;
  uint32_t            i;

  pNodeDef = pDrvCtxt->pBSP->pGenericNPANode;
  if (!pNodeDef)
  {
    return CLOCK_SUCCESS;
  }

  for (i = 0; i < pNodeDef->Node.resource_count; i++)
  {
    pNPACtxt = pNodeDef->Node.resources[i].data;

    eResult = Clock_GetClockId(pDrvCtxt->hClient, pNPACtxt->szClockName,
      &nClockId);
    if (eResult != CLOCK_SUCCESS)
    {
      return eResult;
    }

    pClock = Clock_GetClockNode(nClockId);
    if (!pClock || !pClock->pDomain || !pClock->pDomain->aBSP)
    {
      return CLOCK_ERROR;
    }

    pNPACtxt->pClock = pClock;

    CLOCK_FLAG_SET(pClock->pDomain, INTERNAL_CONTROL);

    pConfig = Clock_GetHighestFreqConfig(pClock->pDomain);
    if (!pConfig)
    {
      return CLOCK_ERROR;
    }

    nMaxFreqKHz = pConfig->nFreqHz / 1000;
    pNodeDef->Node.resources[i].max = nMaxFreqKHz;
    pNodeDef->anInitStates[i] = MIN(pNodeDef->anInitStates[i], nMaxFreqKHz);
  }

  pNodeDef->Node.data = pDrvCtxt;
  npa_define_node_cb(&pNodeDef->Node, pNodeDef->anInitStates, NULL, NULL);
  return CLOCK_SUCCESS;
};


/* =========================================================================
**  Function : Clock_GenericNPANodeFunc
** =========================================================================*/
/**
  See ClockDriver.h
*/

npa_resource_state Clock_GenericNPANodeFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
)
{
  ClockDrvCtxt        *pDrvCtxt = (ClockDrvCtxt *)pResource->node->data;
  ClockNPACtxtType    *pNPACtxt = (ClockNPACtxtType *)pResource->definition->data;
  uint32_t          nResultFreq;
  uint32_t          nFreqHz = NPA_TO_HZ(nState);
  ClockIdType       ClockId;
  ClockResult       eResult;

  eResult = Clock_GetClockId(pDrvCtxt->hClient, pNPACtxt->pClock->szName,
    &ClockId);
  if (eResult != CLOCK_SUCCESS)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to get clock id for root NPA node clock.");
  }

  /*-----------------------------------------------------------------------*/
  /* Perform necessary setup during resource creation.                     */
  /*-----------------------------------------------------------------------*/

  if (hClient->type == NPA_CLIENT_INITIALIZE)
  {
    if (nFreqHz == 0)
    {
      return 0;
    }

    /*
     * If we're setting a non-zero initial state, then assume we also want
     * to enable the clock. Most of the time this would be for suppressible
     * clocks like CPUs or busses.
     */
    eResult = Clock_EnableClock(pDrvCtxt->hClient, ClockId);
    if (eResult != CLOCK_SUCCESS)
    {
      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to enable root NPA node clock.");
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Update clock frequency.                                               */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_SetClockFrequency(pDrvCtxt->hClient, ClockId,
    nFreqHz, CLOCK_FREQUENCY_HZ_AT_LEAST, &nResultFreq);
  if (eResult != CLOCK_SUCCESS)
  {
    return pResource->active_state;
  }

  return nResultFreq / 1000;

} /* END Clock_GenericNPANodeFunc */


/* =========================================================================
**  Function : Clock_GetRequiredCorner
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockResult Clock_GetRequiredCorner
(
  const ClockFMaxType *aFMax,
  uint32_t             nFreqHz,
  rail_voltage_level  *peVRegLevel
)
{
  const ClockFMaxType *pFMax;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!aFMax || !peVRegLevel)
  {
    return CLOCK_ERROR;
  }

  for (pFMax = aFMax; pFMax->nMaxFreqHz; pFMax++)
  {
    if (!Clock_IsBSPSupported(&pFMax->HWVersion))
    {
      continue;
    }

    if (pFMax->nMaxFreqHz >= nFreqHz)
    {
      *peVRegLevel = pFMax->eVRegLevel;
      return CLOCK_SUCCESS;
    }
  }

  return CLOCK_ERROR;

} /* END Clock_GetRequiredCorner */


/* =========================================================================
**  Function : Clock_GetMappedSource
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockResult Clock_GetMappedSource
(
  const ClockSourceMapType   *aSourceMap,
  uint32_t                    nMuxSel,
  const ClockSourceMapType  **pMatchingSourceMap
)
{
  const ClockSourceMapType *pSourceMap;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!aSourceMap || !pMatchingSourceMap)
  {
    return CLOCK_ERROR;
  }

  for (pSourceMap = aSourceMap;
       pSourceMap->nMuxSel != CLOCK_SOURCE_MAP_END; pSourceMap++)
  {
    if (!Clock_IsBSPSupported(&pSourceMap->HWVersion))
    {
      continue;
    }

    if (pSourceMap->nMuxSel == nMuxSel)
    {
      *pMatchingSourceMap = pSourceMap;
      return CLOCK_SUCCESS;
    }
  }

  return CLOCK_ERROR;

} /* END Clock_GetMappedSource */


/* =========================================================================
**  Function : Clock_AssignNPAState
** =========================================================================*/
/**
  See ClockDriver.h
*/

npa_resource_state Clock_AssignNPAState
(
  npa_resource        *pResource,
  npa_resource_state   nRequest
)
{
  npa_client          DummyClient = {0};
  npa_client_handle   hClient = (npa_client_handle)&DummyClient;
  npa_resource_state  nActiveState;

  npa_resource_lock(pResource);
  nActiveState = pResource->node->driver_fcn(pResource, hClient, nRequest);
  npa_assign_resource_state(pResource, nActiveState);
  npa_resource_unlock(pResource);

  return nActiveState;

} /* END Clock_AssignNPAState */


/* =========================================================================
**  Function : Clock_RestoreNPAState
** =========================================================================*/
/**
  See ClockDriver.h
*/

npa_resource_state Clock_RestoreNPAState
(
  npa_resource *pResource
)
{
  return Clock_AssignNPAState(pResource, pResource->request_state);

} /* END Clock_RestoreNPAState */


/* =========================================================================
**  Function : Clock_GetRailNode
** =========================================================================*/
/**
  See ClockDriver.h
*/
ClockRailType *Clock_GetRailNode
(
  const char *szRail
)
{
  int            i;
  ClockBSPType  *pBSP = Clock_GetDrvCtxt()->pBSP;
  ClockRailType *nRailMask = NULL;

  if (!szRail)
  {
    return NULL;
  }

  for (i = 0; i < pBSP->nNumRails; i++)
  {
    if (!strcmp(pBSP->aRails[i]->szName, szRail))
    {
      nRailMask = pBSP->aRails[i];
      break;
    }
  }

  return nRailMask;
}


/* =========================================================================
**  Function : Clock_GetPropertyValue
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_GetPropertyValue
(
  const char              *szName,
  ClockPropertyValueType  *pValue
)
{
  return Clock_GetPropertyHandle(szName, (void**)pValue);
} /* END Clock_GetPropertyValue */


/* =========================================================================
**  Function : Clock_MapHWIORegion
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_MapHWIORegion
(
  uintptr_t  nPhysAddr,
  uint32_t   nSizeBytes,
  uintptr_t *pnVirtAddr
)
{
  ClockResult   eResultClock = CLOCK_SUCCESS;
  DALResult     eResultDAL;
  ClockDrvCtxt *pDrvCtxt = Clock_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* If we attached to the HWIO DAL, then map the regions.                 */
  /*-----------------------------------------------------------------------*/

  if (pDrvCtxt->phHWIO != NULL)
  {
    eResultDAL = DalHWIO_MapRegionByAddress(
      pDrvCtxt->phHWIO, (uint8 *)nPhysAddr, (uint8 **)pnVirtAddr);
    if (DAL_SUCCESS != eResultDAL)
    {
      eResultClock = CLOCK_ERROR_INTERNAL;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* No HWIO DAL, so assume base address is the physical address.          */
  /*-----------------------------------------------------------------------*/

  else
  {
    *pnVirtAddr = nPhysAddr;
  }

  return eResultClock;

} /* END Clock_MapHWIORegion */


/*=========================================================================
**  Function : Clock_AttachPD
** =========================================================================*/
/**
  See ClockDriver.h
*/
ClockResult Clock_AttachPD
(
  ClockHandle *phClient,
  int          nPDId,
  const char  *szName
)
{
  ClockDrvCtxt    *pDrvCtxt = Clock_GetDrvCtxt();
  ClockClientCtxt *pClient;
  ClockPDCtxt     *pPD;
  size_t           nLen;

  /*-----------------------------------------------------------------------*/
  /* Validate driver has initialized.                                      */
  /*-----------------------------------------------------------------------*/

  if (!pDrvCtxt->pBSP)
  {
    return CLOCK_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!phClient || !szName)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Search for existing client.                                           */
  /*-----------------------------------------------------------------------*/

  for (pPD = pDrvCtxt->pPDs; pPD; pPD = pPD->pNext)
  {
    if (pPD->nId == nPDId)
    {
      /*
       * Only one client per PD for now.
       */
      CORE_VERIFY(pPD->pClients);
      *phClient = (ClockHandle)pPD->pClients;

      return CLOCK_SUCCESS;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Create a new PD if necessary.                                         */
  /*-----------------------------------------------------------------------*/

  if (!pPD)
  {
    if (DAL_SUCCESS !=  DALSYS_Malloc(sizeof(ClockPDCtxt),(void **)(&pPD)))
    {
      DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to allocate %lu bytes for new PD.",sizeof(ClockPDCtxt));
    }
    CORE_VERIFY(pPD);

    /*
     * Store identifier
     */
    pPD->nId = nPDId;

    /*
     * Store string name
     */
    if (nPDId == CLOCK_LOCAL_CLIENT_ID)
    {
      pPD->szName = "INTERNAL";
    }
    else
    {
      if (DAL_SUCCESS != DALSYS_Malloc(CLOCK_PD_NAME_LEN,(void **)(&(pPD->szName))))
      {
        DALSYS_Free ((void *)pPD);
        DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to allocate %lu bytes for string name.", CLOCK_PD_NAME_LEN);
      }
      CORE_VERIFY(pPD->szName);

      DALSYS_memset(pPD->szName, 0, CLOCK_PD_NAME_LEN);
      strlcpy((char *)pPD->szName, szName, CLOCK_PD_NAME_LEN);

    }

    /*
     * Insert new PD context into linked list.
     */
    CLOCK_INSERT_LL_NODE(&pDrvCtxt->pPDs, pPD);
  }

  /*-----------------------------------------------------------------------*/
  /* No matching client found - create new client context.                 */
  /*-----------------------------------------------------------------------*/

  if (DAL_SUCCESS != DALSYS_Malloc(sizeof(ClockClientCtxt),(void **)(&pClient)))
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to allocate %lu bytes for new client context.", sizeof(ClockClientCtxt));
  }

  CORE_VERIFY(pClient);
  DALSYS_memset(pClient, 0, sizeof(ClockClientCtxt));
  pClient->pPD = pPD;

  /*-----------------------------------------------------------------------*/
  /* Store string name                                                     */
  /*-----------------------------------------------------------------------*/

  nLen = strlen(szName) + 1;

  if (DAL_SUCCESS != DALSYS_Malloc(nLen,(void **)(&(pClient->szName))))
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to allocate %lu bytes for String name.", nLen);
  }
  CORE_VERIFY(pClient->szName);
  strlcpy((char *)pClient->szName, szName, nLen);

  /*-----------------------------------------------------------------------*/
  /* Insert new client into PD linked list.                                */
  /*-----------------------------------------------------------------------*/

  CLOCK_INSERT_LL_NODE(&pPD->pClients, pClient);

  /*-----------------------------------------------------------------------*/
  /* Return newly created client.                                          */
  /*-----------------------------------------------------------------------*/

  *phClient = (ClockHandle)pClient;

  /*-----------------------------------------------------------------------*/
  /* Hook for image processing.                                            */
  /*-----------------------------------------------------------------------*/

  if (Clock_CreatePDEventProcess)
  {
    Clock_CreatePDEventProcess(pPD);
  }

  return CLOCK_SUCCESS;

} /* END Clock_AttachPD */


/*=========================================================================
**  Function : Clock_Attach
** =========================================================================*/
/**
  See ClockDriver.h
*/
ClockResult Clock_Attach
(
  ClockHandle *phClient,
  const char  *szName
)
{
  /* Call Attach with local client id */
  return Clock_AttachPD(phClient, CLOCK_LOCAL_CLIENT_ID, szName);

} /* END Clock_Attach */


/*=========================================================================
**  Function : Clock_Detach
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_Detach
(
  ClockHandle hClient
)
{
  ClockDrvCtxt    *pDrvCtxt = Clock_GetDrvCtxt();
  ClockClientCtxt *pClient;
  ClockPDCtxt     *pPD;
  ClockResult      eResult;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Do not detach INTERNAL client.                                        */
  /*-----------------------------------------------------------------------*/

  if (hClient == pDrvCtxt->hClient)
  {
    return CLOCK_SUCCESS;
  }

  pClient = (ClockClientCtxt *)hClient;
  pPD = pClient->pPD;
  CORE_VERIFY(pPD && pPD->pClients);

  /*-----------------------------------------------------------------------*/
  /* Remove client from linked list.                                       */
  /*-----------------------------------------------------------------------*/

  eResult = CLOCK_REMOVE_LL_NODE(&pPD->pClients, pClient, Clock_CleanupClient);
  CORE_VERIFY(CLOCK_SUCCESS == eResult);

  /*-----------------------------------------------------------------------*/
  /* Cleanup PD if no clients remain.                                      */
  /*-----------------------------------------------------------------------*/

  if (!pPD->pClients)
  {
    CORE_VERIFY(pDrvCtxt->pPDs);
    eResult = CLOCK_REMOVE_LL_NODE(&pDrvCtxt->pPDs, pPD, Clock_CleanupPD);
    CORE_VERIFY(CLOCK_SUCCESS == eResult);
  }

  return CLOCK_SUCCESS;

} /* END Clock_Detach */


/*=========================================================================
**  Function : Clock_GetDrvCtxt
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockDrvCtxt * Clock_GetDrvCtxt
(
  void
)
{
  return &Clock_DriverCtxt;

} /* END of Clock_GetDrvCtxt */


/* =========================================================================
**  Function : Clock_DriverInit
** =========================================================================*/
/**
  Initialize the clock driver.

  This function initializes the clock driver, it is the main init entry
  point.

  @return
  CLOCK_SUCCESS -- Initialization was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult Clock_DriverInit
(
  void
)
{
  ClockResult                  eResult;
  ClockDrvCtxt                *pDrvCtxt = Clock_GetDrvCtxt();
  HAL_clk_ContextType          HALClkCtxt = {0};
  ClockPropertyValueType       PropVal;
  uint32_t                     nLogSize;
  ClockStubType               *pClockStubConfig;
  DalPlatformInfoPlatformType  PlatformInfo;
  ClockClientCtxt             *pClient;

  /*-----------------------------------------------------------------------*/
  /* Hookup BSP data linked to target built in this image.                 */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt->pBSP = &ClockBSP;

  /*-----------------------------------------------------------------------*/
  /* Initialize the log.                                                   */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyValue("ClockLogDefaults", &PropVal);
  if (eResult == CLOCK_SUCCESS)
  {
    nLogSize = ((ClockLogType *)PropVal)->nLogSize;
    pDrvCtxt->pBSP->nFlags |= ((ClockLogType *)PropVal)->nGlobalLogFlags;
  }
  else
  {
    nLogSize = CLOCK_DEFAULT_LOG_SIZE;
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_WARNING,
      "Missing clock log defaults. Defaulting size to %lu.", nLogSize);
  }

  ULogFront_RealTimeInit(&pDrvCtxt->hClockLog, "Clock Log",
                         nLogSize,
                         ULOG_MEMORY_LOCAL, ULOG_LOCK_OS);

  ULogCore_HeaderSet(pDrvCtxt->hClockLog,
                     "Content-Type: text/tagged-log-1.0;");

  /*-----------------------------------------------------------------------*/
  /* Check DEVCFG for stub flags.                                          */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyValue("ClockStubConfig", &PropVal);
  if (eResult == CLOCK_SUCCESS)
  {
    pClockStubConfig = (ClockStubType *)PropVal;
    PlatformInfo = DalPlatformInfo_Platform();

    if ((PlatformInfo == DALPLATFORMINFO_TYPE_RUMI) &&
        (pClockStubConfig->bRUMI == true))
    {
      CLOCK_GLOBAL_FLAG_SET(STUB_API);

      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
        "CLOCK_GLOBAL_FLAG_STUB_API set - stubbing out on RUMI.");
    }
    if ((PlatformInfo == DALPLATFORMINFO_TYPE_VIRTIO) &&
        (pClockStubConfig->bVirtio == true))
    {
      CLOCK_GLOBAL_FLAG_SET(STUB_API);

      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
        "CLOCK_GLOBAL_FLAG_STUB_API set - stubbing out on Virtio.");
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Determine whether this is a warm start, or a cold boot.               */
  /*                                                                       */
  /* If this is a warm start, then we must be waking up from hibernation.  */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt->bColdStart = TRUE;

  if (pDrvCtxt->hLock != 0)
  {
    Clock_DriverDeInit();
    pDrvCtxt->bColdStart = FALSE;
  }

  /*-----------------------------------------------------------------------*/
  /* Create the driver synchronization object.                             */
  /*-----------------------------------------------------------------------*/

  if (DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE,
                       &pDrvCtxt->hLock, &pDrvCtxt->LockObj))
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "DALSYS_SyncCreate failed.");

    return CLOCK_ERROR;
  }
  
  /*-----------------------------------------------------------------------*/
  /* DebugLock is used for serializing Clock_MeasureFrequency api.         */
  /*-----------------------------------------------------------------------*/

  if (DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE,
                       &pDrvCtxt->hDebugLock, &pDrvCtxt->DebugLockObj))
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "DALSYS_SyncCreate failed for Debug Lock.");

    return CLOCK_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Attach to HWIO.                                                       */
  /*-----------------------------------------------------------------------*/

  DAL_DeviceAttach(DALDEVICEID_HWIO, &pDrvCtxt->phHWIO);
  if (!pDrvCtxt->phHWIO)
  {
    return CLOCK_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize base addresses.                                            */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_InitBases();
  if (eResult != CLOCK_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitBases failed.");

    return CLOCK_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the clock HAL.                                             */
  /*-----------------------------------------------------------------------*/

  /*
   * Use DALSys busy wait function for HAL modules.
   */
  HALClkCtxt.BusyWait = (void (*)(uint32_t))busywait;

  /*
   * Get chip version to send to the HAL.
   */
  HALClkCtxt.nChipVersion = DalChipInfo_ChipVersion();
  HALClkCtxt.nChipId = DalChipInfo_ChipId();
  HALClkCtxt.nChipFamily = DalChipInfo_ChipFamily();

  HAL_clk_Init(&HALClkCtxt);


  /*-----------------------------------------------------------------------*/
  /* Attach internal client.                                               */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_Attach(&pDrvCtxt->hClient, "INTERNAL");
  if (eResult != CLOCK_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_Attach failed on INTERNAL client.");

    return CLOCK_ERROR;
  }
  pClient = (ClockClientCtxt *)pDrvCtxt->hClient;
  CLOCK_FLAG_SET(pClient, INTERNAL_CONTROL);

  /*-----------------------------------------------------------------------*/
  /* Setup of context related to dynamic memory usage on sources.          */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_InitSourcesSoft();
  if (eResult != CLOCK_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitSourcesSoft failed.");

    return CLOCK_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Init voltage module.                                                  */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_InitVoltage();
  if (eResult != CLOCK_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitVoltage failed.");

    return CLOCK_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Init DFS domains.                                                     */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_InitDFSDomains();
  if (eResult != CLOCK_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitDFSDomains failed.");

    return CLOCK_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the image specific driver.                                 */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_InitTarget();
  if (eResult != CLOCK_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitTarget failed.");

    return CLOCK_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Init NPA resources.                                                   */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_InitNPA();
  if (eResult != CLOCK_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitNPA failed.");

    return CLOCK_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialization complete.                                              */
  /*-----------------------------------------------------------------------*/

  return CLOCK_SUCCESS;

} /* END Clock_DriverInit */


/* =========================================================================
**  Function : ClockStub_DriverInit
** =========================================================================*/
/**
  Initialize the clock driver stub.

  This function initializes the clock driver, it is the main init entry
  point.

  @return
  CLOCK_SUCCESS -- Initialization was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult ClockStub_DriverInit
(
  void
)
{
  ClockResult eResult;

  /*-----------------------------------------------------------------------*/
  /* Initialize the image specific driver stub.                            */
  /*-----------------------------------------------------------------------*/

  eResult = ClockStub_InitTarget();
  if (eResult != CLOCK_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "ClockStub_InitTarget failed.");
    return eResult;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialization complete.                                              */
  /*-----------------------------------------------------------------------*/

  return CLOCK_SUCCESS;

} /* END ClockStub_DriverInit */


/* =========================================================================
**  Function : clk_regime_init
** =========================================================================*/

void clk_regime_init(void)
{
  /*-----------------------------------------------------------------------*/
  /* Initialize driver.                                                    */
  /*-----------------------------------------------------------------------*/

  CORE_VERIFY(CLOCK_SUCCESS == Clock_DriverInit());

  /*-----------------------------------------------------------------------*/
  /* Initialize framework shim.                                            */
  /*-----------------------------------------------------------------------*/

  CORE_VERIFY(CLOCK_SUCCESS == Clock_FrameworkInit());

} /* END clk_regime_init */


/* =========================================================================
**  Function : clk_regime_bist
** =========================================================================*/

void clk_regime_bist(void)
{
  ClockDrvCtxt *pDrvCtxt = Clock_GetDrvCtxt();

  if (!pDrvCtxt->bBISTEnabled)
  {
    return;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  if (pDrvCtxt->nBISTLogSize == 0)
  {
    pDrvCtxt->nBISTLogSize = CLOCK_BIST_DEFAULT_LOG_SIZE;
  }

  Clock_BIST();

  DALCLOCK_FREE(pDrvCtxt);

} /* END clk_regime_bist */


/* =========================================================================
**  Function : Clock_MapAlias
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_MapAlias
(
  ClockHandle  hClient,
  const char  *szAlias,
  char        *szNameBuf,
  uint32_t     nNameBufLen
)
{
  ClockDrvCtxt          *pDrvCtxt = Clock_GetDrvCtxt();
  const ClockAliasType  *pAlias;
  uint32_t               i;
  uint32_t               nLen;

  if (!szAlias || !szNameBuf)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  for (i = 0; i < pDrvCtxt->pBSP->nNumAliases; i++)
  {
    pAlias = &pDrvCtxt->pBSP->aAliases[i];
    if (!strcmp(pAlias->szFrom, szAlias))
    {
      szAlias = pAlias->szTo;
      break;
    }
  }

  nLen = strlcpy(szNameBuf, szAlias, nNameBufLen);
  if (nLen >= nNameBufLen)
  {
    return CLOCK_ERROR_INSUFFICIENT_BUFFER_LEN;
  }

  return CLOCK_SUCCESS;

} /* END Clock_MapAlias */


/* =========================================================================
**  Function : Clock_EnableEx
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_EnableEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
   ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_EnableClockEx(hClient, ClockId, nFlags);

    case CLOCK_ID_CATEGORY_SOURCE:
      return Clock_EnableSource(hClient, ClockId);

    case CLOCK_ID_CATEGORY_POWERDOMAIN:
      return Clock_EnablePowerDomain(hClient, ClockId);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }

} /* END Clock_EnableEx */


/* =========================================================================
**  Function : Clock_DisableEx
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_DisableEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_DisableClockEx(hClient, ClockId, nFlags);

    case CLOCK_ID_CATEGORY_SOURCE:
      return Clock_DisableSource(hClient, ClockId);

    case CLOCK_ID_CATEGORY_POWERDOMAIN:
      return Clock_DisablePowerDomain(hClient, ClockId);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }

} /* END Clock_DisableEx */


/* =========================================================================
**  Function : Clock_SetFrequencyEx
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_SetFrequencyEx
(
  ClockHandle          hClient,
  ClockIdType          ClockId,
  uint32_t             nFreq,
  ClockFrequencyType   eMatch,
  uint32_t            *pnResultFreq,
  uint32_t             nFlags
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_SetClockFrequency(hClient, ClockId, nFreq, eMatch, pnResultFreq);

    case CLOCK_ID_CATEGORY_SOURCE:
      return Clock_SetSourceFrequency(hClient, ClockId, nFreq, eMatch, pnResultFreq);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }

} /* END Clock_SetFrequencyEx */


/* =========================================================================
**  Function : Clock_IsEnabled
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_IsEnabled
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  bool        *pbIsEnabled
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_IsClockEnabled(hClient, ClockId, pbIsEnabled);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }

} /* END Clock_IsEnabled */


/* =========================================================================
**  Function : Clock_IsOn
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_IsOn
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  bool        *pbIsOn
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_IsClockOn(hClient, ClockId, pbIsOn);

    case CLOCK_ID_CATEGORY_POWERDOMAIN:
      return Clock_IsPowerDomainOn(hClient, ClockId, pbIsOn);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }

} /* END Clock_IsOn */


/* =========================================================================
**  Function : Clock_GetFrequency
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_GetFrequency
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  uint32_t    *pnFrequencyHz
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_GetClockFrequency(hClient, ClockId, pnFrequencyHz);

    case CLOCK_ID_CATEGORY_SOURCE:
      return Clock_GetSourceFrequency(hClient, ClockId, pnFrequencyHz);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }

} /* END Clock_GetFrequency */


/* =========================================================================
**  Function : Clock_MeasureFrequency
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_MeasureFrequencyEx
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  uint32_t     nMuxSel,
  uint32_t    *pnFrequencyHz
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_MeasureClockFrequency(hClient, ClockId, pnFrequencyHz);

    case CLOCK_ID_CATEGORY_DEBUGMUX:
      return Clock_MeasureDebugMuxInput(hClient, ClockId, nMuxSel, pnFrequencyHz);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }

} /* END Clock_MeasureFrequency */


/* =========================================================================
**  Function : Clock_Configure
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_Configure
(
  ClockHandle     hClient,
  ClockIdType     ClockId,
  ClockConfigType eConfig
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_ConfigureClock(hClient, ClockId, eConfig);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }

} /* END Clock_Configure */


/* =========================================================================
**  Function : Clock_SetDivider
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_SetDivider
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nDivider
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_SetClockDivider(hClient, ClockId, nDivider);

    case CLOCK_ID_CATEGORY_DIVIDER:
      return Clock_SetDividerDivider(hClient, ClockId, nDivider);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }

} /* END Clock_SetDivider */


/* =========================================================================
**  Function : Clock_Query
** =========================================================================*/
/*
  See Clock.h
*/

ClockResult Clock_Query
(
  ClockHandle            hClient,
  ClockIdType            ClockId,
  ClockQueryType         eQuery,
  uint32_t               nIndex,
  ClockQueryResultType  *pResult
)
{
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_QueryClock(hClient, ClockId, eQuery, nIndex, pResult);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }

} /* END Clock_Query */


/* =========================================================================
**  Function : Clock_RegisterCallback
** =========================================================================*/
/**
  See Clock.h
*/

ClockResult Clock_RegisterCallback
(
  ClockHandle            hClient,
  ClockIdType            nResourceId,
  ClockCallbackEventType eEvent,
  ClockCallbackFn        pFn,
  ClockCallbackCtxt      pCtxt,
  ClockCallbackIdType   *pCallbackId
)
{
  uint32_t                  nSize;
  ClockCallbackNodeType    *pTemp;
  ClockCallbackNodeType   **pHead;
  DALResult                 nResult;
  ClockPowerDomainNodeType *pPowerDomain=NULL;
  ClockNodeType            *pClock=NULL;
  ClockDrvCtxt              *pDrvCtxt = Clock_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !pFn || !pCallbackId ||
      eEvent >= CLOCK_CALLBACK_EVENT_NUM_TYPES)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize output parameter                                           */
  /*-----------------------------------------------------------------------*/

  *pCallbackId = (ClockCallbackIdType)NULL;

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Get the resource node.                                                */
  /*-----------------------------------------------------------------------*/

  switch (CLOCK_GET_ID_CATEGORY(nResourceId))
  {
    case CLOCK_ID_CATEGORY_NONE:
    {
      DALCLOCK_FREE(pDrvCtxt);
      return CLOCK_ERROR_INVALID_PARAMETER;
    }
    case CLOCK_ID_CATEGORY_CLOCK:
    {
      pClock = Clock_GetClockNode(nResourceId);
      if (pClock == NULL)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return CLOCK_ERROR_INVALID_PARAMETER;
      }

      pHead = &pDrvCtxt->pCallbacks[CLOCK_ID_CATEGORY_CLOCK];

      break;
    }
    case CLOCK_ID_CATEGORY_POWERDOMAIN:
    {
      pPowerDomain = Clock_GetPowerDomainNode(nResourceId);
      if (pPowerDomain == NULL)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return CLOCK_ERROR_INVALID_PARAMETER;
      }

      pHead = &pDrvCtxt->pCallbacks[CLOCK_ID_CATEGORY_POWERDOMAIN];

      break;
    }
    default:
    {
      DALCLOCK_FREE(pDrvCtxt);
      return CLOCK_ERROR_NOT_SUPPORTED;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if node is already present in linked list.              */
  /*-----------------------------------------------------------------------*/

  for (pTemp = *pHead; pTemp; pTemp = pTemp->pNext)
  {
    if ((pTemp->nResourceID  == nResourceId) &&
        (pTemp->eEvent       == eEvent     ) &&
        (pTemp->pfnCallback  == pFn        ) &&
        (pTemp->CallbackCtxt == pCtxt      ))
    {
      *pCallbackId = (ClockCallbackIdType)pTemp;
      DALCLOCK_FREE(pDrvCtxt);
      return CLOCK_SUCCESS;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Create the callback node & add it to the global linked list.          */
  /*-----------------------------------------------------------------------*/

  nSize = sizeof(ClockCallbackNodeType);
  nResult = DALSYS_Malloc(nSize, (void **)&pTemp);
  if (nResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to allocate %u bytes for callback linked list node", nSize);

    DALCLOCK_FREE(pDrvCtxt);
    return CLOCK_ERROR_INSUFFICIENT_MEMORY;
  }

  pTemp->nResourceID = nResourceId;
  pTemp->eEvent = eEvent;
  pTemp->pfnCallback = pFn;
  pTemp->CallbackCtxt = pCtxt;

  CLOCK_INSERT_LL_NODE(pHead, pTemp);

  switch (CLOCK_GET_ID_CATEGORY(nResourceId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
    {
      if (CLOCK_CALLBACK_EVENT_PRE_FREQ_CHANGE == eEvent ||
          CLOCK_CALLBACK_EVENT_POST_FREQ_CHANGE == eEvent)
      {
        CORE_VERIFY_PTR(pClock->pDomain);
        pClock->pDomain->nCallbackCount++;
      }
      else
  {
        pClock->nCallbackCount++;
      }
      break;
    }
    case CLOCK_ID_CATEGORY_POWERDOMAIN:
    {
      pPowerDomain->nCallbackCount++;
      break;
    }
    default:
    {
      break;
    }
  }

  /*
   * Fill up the callback ID pointer
   */
  *pCallbackId = (ClockCallbackIdType)pTemp;

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_RegisterCallback */


/* =========================================================================
**  Function : Clock_DeregisterCallback
** =========================================================================*/
/**
  See Clock.h
*/

ClockResult Clock_DeregisterCallback
(
  ClockHandle            hClient,
  ClockCallbackIdType    nCallbackId
)
{
  ClockIdCategoryType       nCat;
  ClockResult               eResult;
  ClockCallbackNodeType   **pHead;
  ClockCallbackNodeType    *pCallback;
  ClockPowerDomainNodeType *pPowerDomain;
  ClockNodeType            *pClock;
  ClockDrvCtxt             *pDrvCtxt = Clock_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if driver is stubbed.                                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  pCallback = (ClockCallbackNodeType*)nCallbackId;
  if (!hClient || !nCallbackId || !pCallback)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Get the resource node.                                                */
  /*-----------------------------------------------------------------------*/

  nCat = CLOCK_GET_ID_CATEGORY(pCallback->nResourceID);
  switch (nCat)
  {
    case CLOCK_ID_CATEGORY_NONE:
    {
      DALCLOCK_FREE(pDrvCtxt);
      return CLOCK_ERROR_INVALID_PARAMETER;
    }
    case CLOCK_ID_CATEGORY_CLOCK:
    {
      pClock = Clock_GetClockNode(pCallback->nResourceID);
      if (pClock == NULL)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return CLOCK_ERROR_INVALID_PARAMETER;
      }

      if (CLOCK_CALLBACK_EVENT_PRE_FREQ_CHANGE == pCallback->eEvent ||
          CLOCK_CALLBACK_EVENT_POST_FREQ_CHANGE == pCallback->eEvent)
      {
        CORE_VERIFY_PTR(pClock->pDomain);
        if (pClock->pDomain->nCallbackCount == 0)
        {
          DALCLOCK_FREE(pDrvCtxt);
          return CLOCK_ERROR_INVALID_PARAMETER;
        }
      }
      else
      {
        if (pClock->nCallbackCount == 0)
        {
          DALCLOCK_FREE(pDrvCtxt);
          return CLOCK_ERROR_INVALID_PARAMETER;
        }
      }

      pHead = &pDrvCtxt->pCallbacks[CLOCK_ID_CATEGORY_CLOCK];
      break;
    }
    case CLOCK_ID_CATEGORY_POWERDOMAIN:
    {
      pPowerDomain = Clock_GetPowerDomainNode(pCallback->nResourceID);
      if ((pPowerDomain == NULL) || pPowerDomain->nCallbackCount == 0)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return CLOCK_ERROR_INVALID_PARAMETER;
      }

      pHead = &pDrvCtxt->pCallbacks[CLOCK_ID_CATEGORY_POWERDOMAIN];
      break;
    }
    default:
    {
      DALCLOCK_FREE(pDrvCtxt);
      return CLOCK_ERROR_NOT_SUPPORTED;
    }
  }

  eResult = CLOCK_REMOVE_LL_NODE(pHead, pCallback, free);
  if (eResult != CLOCK_SUCCESS)
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to remove callback node from linked list, error: %d", eResult);

    DALCLOCK_FREE(pDrvCtxt);
    return CLOCK_ERROR_INTERNAL;
  }

  switch (nCat)
  {
    case CLOCK_ID_CATEGORY_CLOCK:
    {
      if (CLOCK_CALLBACK_EVENT_PRE_FREQ_CHANGE == pCallback->eEvent ||
          CLOCK_CALLBACK_EVENT_POST_FREQ_CHANGE == pCallback->eEvent)
      {
        CORE_VERIFY_PTR(pClock->pDomain);
        pClock->pDomain->nCallbackCount--;
      }
      else
      {
        pClock->nCallbackCount--;
      }
      break;
    }
    case CLOCK_ID_CATEGORY_POWERDOMAIN:
    {
      pPowerDomain->nCallbackCount--;
      break;
    }
    default:
    {
      break;
    }
  }

  DALCLOCK_FREE(pDrvCtxt);

  return CLOCK_SUCCESS;

} /* END Clock_DeregisterCallback */
