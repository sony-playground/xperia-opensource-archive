/*
===========================================================================
*/
/**
  @file IPCCRx.c

  IPC Controller driver Rx portion of the driver.
*/
/*
  ====================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/src/IPCCRx.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/
#include "IPCC.h"
#include "IPCC_Internal.h"
#include "IPCC_Rx.h"
#include "IPCC_Log.h"
#include "IPCCHWIO.h"
#include <stdlib.h>
#include <string.h>


/*=========================================================================
      Static defiintions
==========================================================================*/

extern IPCCRxDrvType RxDrv;

/*=========================================================================
      Internal functions
==========================================================================*/


/* =========================================================================
**  Function : IPCCRx_IsOverlap
** =========================================================================*/

static 
bool 
IPCCRx_IsOverlap
(
   IPCCRxDataType* pData,
   IPCC_Signal     nSignalLow,
   IPCC_Signal     nSignalHigh
)
{

  /*-------------------------------------------------------------------------*/

  if( ( nSignalLow <= pData->nSignalHigh && nSignalLow >= pData->nSignalLow ) ||
      ( nSignalHigh >= pData->nSignalLow && nSignalHigh <= pData->nSignalHigh ) )
  {
    return true;
  }

  return false;
}

/* =========================================================================
**  Function : IPCCRx_IsExactOverlap
** =========================================================================*/

static 
bool 
IPCCRx_IsExactOverlap
(
   IPCCRxDataType* pData,
   IPCC_Signal     nSignalLow,
   IPCC_Signal     nSignalHigh
)
{

  /*-------------------------------------------------------------------------*/

  if( ( nSignalLow  == pData->nSignalLow  ) && 
      ( nSignalHigh == pData->nSignalHigh ) )
  {
    return true;
  }

  return false;
}



/* =========================================================================
**  Function : IPCCRx_IPCCRx_GetNode
** =========================================================================*/

static 
IPCCRxDataType* 
IPCCRx_GetNode
(
   IPCCRxDataType* pList,
   IPCC_Signal     nSignalLow,
   IPCC_Signal     nSignalHigh
)
{

  /*-------------------------------------------------------------------------*/

  while ( pList )
  {
    if( IPCCRx_IsExactOverlap(pList, nSignalLow, nSignalHigh) )
    {
      return pList;
    }
    pList = pList->pNext;
  }

  return NULL;
}

/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : IPCCRx_Init
** =========================================================================*/
/**
  Initialize the IPCC Rx driver.

  This function initializes the IPC controller Rx driver,
  it is the main init entry point for this driver.

  @param
  None.

  @return
  None.

  @dependencies
  None.
*/

void
IPCCRx_Init
(
   IPCCDrvCtxt* pDrv
)
{

  /*-------------------------------------------------------------------------*/

  /* Apply Rx Drv to Master Drv */
  if ( pDrv != NULL )
  {
    pDrv->pRxDrv = &RxDrv;
    RxDrv.eClient = pDrv->pBSP->eClient;
  }

  IPCCLog_Out(0, "IPCCRx Initialized");
}


/* =========================================================================
**  Function : IPCCRx_Attach
** =========================================================================*/

void
IPCCRx_Attach
(
  IPCCClientCtxt*   pClientCtxt
)
{
  uintptr_t nAddress;
  uint32_t  nData;

  /*-------------------------------------------------------------------------*/

  if ( pClientCtxt &&
       pClientCtxt->pProtocol )
  {
    pClientCtxt->pRxDrv = &RxDrv.RxProtocolDrv[pClientCtxt->pProtocol->nProtocolId];

    /* Check if this is the first reference */
    if( pClientCtxt->pRxDrv->nRefs == 0 )
    {
      /* Initialize Rx Data */
      IPCCOS_MutexInit(&pClientCtxt->pRxDrv->sMutex);

      /* Attach to InterruptDrv */
      IPCCOS_InitInterruptHandle(&pClientCtxt->pRxDrv->hInterruptHandle);

      /* If clear on recv is set, enable it */
      if ( pClientCtxt->pProtocol->bClearOnRecvEn )
      {
        nAddress = HWIO_ADDRXI2(pClientCtxt->pProtocol->nVirtBaseAddress, IPC_CONFIG, 0, 0);
        nData = IPCCOS_Read(nAddress);
        nData |= HWIO_IPC_CONFIG_CLEAR_ON_RECV_RD_BMSK;
        IPCCOS_Write(nAddress, nData);
      }

      /* Register for Rx Interrupt */
      if ( IPCC_EOK != IPCCOS_RegisterInterrupt( &pClientCtxt->pRxDrv->hInterruptHandle,
                                                 pClientCtxt->pProtocol->nInterrupt, 
                                                 pClientCtxt->pProtocol->bIsIslandInterrupt,
                                                 IPCCOS_TRIGGER_HIGH,
                                                 (IPCCOSCB)IPCC_RxIsr,
                                                 (uintptr_t)pClientCtxt->pProtocol ) ) 
      {
        /* Log failure in registration */
        IPCCOS_ErrFatal("IPCCRx_Attach: Could not register interrupt %d for protocol ID %d", 
                        pClientCtxt->pProtocol->nInterrupt, 
                        pClientCtxt->pProtocol->nProtocolId, 
                        0 );
      }
    }

    pClientCtxt->pRxDrv->nRefs++;
    RxDrv.nRefs++;
  }
}


/* =========================================================================
**  Function : IPCCRx_Detach
** =========================================================================*/

void
IPCCRx_Detach
(
  IPCCClientCtxt*   pClientCtxt
)
{

  /*-------------------------------------------------------------------------*/

  if ( pClientCtxt &&
       pClientCtxt->pRxDrv )
  {
    pClientCtxt->pRxDrv->nRefs--;
    RxDrv.nRefs--;

    /* Check if we were the last reference */
    if( pClientCtxt->pRxDrv->nRefs == 0 )
    {
      /* Unregister for Rx Interrupt */
      if ( IPCC_EOK != IPCCOS_DeregisterInterrupt( &pClientCtxt->pRxDrv->hInterruptHandle,
                                                    pClientCtxt->pProtocol->nInterrupt ) ) 
													
      {
        /* Log failure if deregistration fails */
        IPCCOS_ErrFatal("IPCCRx_Detach: Could not unregister interrupt %d for protocol ID %d", 
                        pClientCtxt->pProtocol->nInterrupt, 
                        pClientCtxt->pProtocol->nProtocolId, 
                        0 );
      }

      /* Kill mutex */
      IPCCOS_MutexDeinit(&pClientCtxt->pRxDrv->sMutex);
    }

    pClientCtxt->pRxDrv = NULL;
  }
}

/* =========================================================================
**  Function : IPCCRx_RegisterInterrupt
** =========================================================================*/

IPCCErr 
IPCCRx_RegisterInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_CB           pfnCB,
  IPCC_CBData       nData
)
{
  IPCCRxDataType* pRxData, *pRxList;
  
  uintptr_t nAddr;
  uint32_t nIdx, nSigEn;

  /*-------------------------------------------------------------------------*/

  if( pClientCtxt == NULL ||
      pClientCtxt->pProtocol == NULL ||
      eCID >= pClientCtxt->pProtocol->nNumClients ||
      nSignalLow > nSignalHigh ||
      nSignalHigh >= pClientCtxt->pProtocol->nNumSigs || 
      pfnCB == NULL )
  {
    IPCCLog_Out(3, "IPCCRx_RegisterInterrupt failed (arg) for eCID %d, nSignalLow %d, nSignalHigh %d", eCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  IPCCLog_Out(3, "IPCCRx_RegisterInterrupt called for eCID %d, SignalLow: %d, SignalHigh: %d", eCID, nSignalLow, nSignalHigh);

  /* Enter critical section */
  IPCCOS_MutexLock(&pClientCtxt->pRxDrv->sMutex);

  /* Check that all requested lines are not in use */
  pRxList = pClientCtxt->pProtocol->pClients[eCID].pList;
  while( pRxList != NULL )
  {
    if( IPCCRx_IsOverlap(pRxList, nSignalLow, nSignalHigh) )
    {
      IPCCLog_Out(3, "IPCCRx_RegisterInterrupt failed (in use) for eCID %d, nSignalLow %d, nSignalHigh %d", eCID, nSignalLow, nSignalHigh);

      /* Leave critical section */
      IPCCOS_MutexUnlock(&pClientCtxt->pRxDrv->sMutex);

      return IPCC_EINUSE;
    }

    pRxList = pRxList->pNext;
  }

  /* Now we've confirmed that the lines are not in use, let's get memory and add it to the list */
  pRxData = (IPCCRxDataType*) IPCCOS_Malloc ( sizeof(IPCCRxDataType) );

  /* Fail if we're out of memory for whatever reason */
  if ( pRxData == NULL ) 
  {
    IPCCLog_Out(3, "IPCCRx_RegisterInterrupt failed (no memory) for eCID %d, nSignalLow %d, nSignalHigh %d", eCID, nSignalLow, nSignalHigh);

    /* Leave critical section */
    IPCCOS_MutexUnlock(&pClientCtxt->pRxDrv->sMutex);

    return IPCC_EMEM;
  }

  /* Clear the memory */
  memset( pRxData, 0, sizeof(IPCCRxDataType) );

  /* Populate structure accordingly */
  pRxData->nSignalLow = nSignalLow;
  pRxData->nSignalHigh = nSignalHigh;
  pRxData->pfnCb = pfnCB;
  pRxData->nArg = nData;
  pRxData->bIsland = false;

  /* Insert in the list */
  pRxList = pClientCtxt->pProtocol->pClients[eCID].pList;
  if( pRxList == NULL ||
      pRxList->nSignalLow > pRxData->nSignalHigh )
  {
    /* Insert at the front */
    pClientCtxt->pProtocol->pClients[eCID].pList = pRxData;
    pRxData->pNext = pRxList;
  }
  else
  {
    while( pRxList->pNext != NULL )
    {
      if( pRxList->pNext->nSignalLow > pRxData->nSignalHigh )
      {
        break;
      }

      pRxList = pRxList->pNext;
    }

    if( pRxList == NULL )
    {
      IPCCOS_ErrFatal("Something went wrong trying to insert node 0x%x into list 0x%x",0,0,0);
    }

    /* Insert after pRxList */
    pRxData->pNext = pRxList->pNext;
    pRxList->pNext = pRxData;
  }

  /* Leave critical section */
  IPCCOS_MutexUnlock(&pClientCtxt->pRxDrv->sMutex);

  /* Now enable it in IPCC */
  nAddr = HWIO_ADDRXI2(pClientCtxt->pProtocol->nVirtBaseAddress, IPC_RECV_SIGNAL_ENABLE, 0, 0);

  /* Enable the signal for incoming interrupts */
  /* For now, enable one-by-one, but ideally we can use Global enable mask */
  for( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
  {
    nSigEn = ( eCID << HWIO_SHFT(IPC_RECV_SIGNAL_ENABLE, CLIENT_ID) ) | nIdx;
    IPCCOS_Write(nAddr, nSigEn);
  }

  return IPCC_EOK;
}


/* =========================================================================
**  Function : IPCCRx_DeregisterInterrupt
** =========================================================================*/

IPCCErr 
IPCCRx_DeregisterInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  IPCCRxDataType* pRxData, *pRxToRemove, **ppRxList;
  
  uintptr_t nAddr;
  uint32_t nIdx, nSigEn;

  /*-------------------------------------------------------------------------*/

  if( pClientCtxt == NULL ||
      pClientCtxt->pProtocol == NULL ||
      eCID >= pClientCtxt->pProtocol->nNumClients ||
      nSignalLow > nSignalHigh ||
      nSignalHigh >= pClientCtxt->pProtocol->nNumSigs )
  {
    IPCCLog_Out(3, "IPCCRx_DeregisterInterrupt failed (arg) for eCID %d, nSignalLow %d, nSignalHigh %d", eCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  /* Get data needed for IPCC */
  nAddr = HWIO_ADDRXI2(pClientCtxt->pProtocol->nVirtBaseAddress, IPC_RECV_SIGNAL_DISABLE, 0, 0);

  /* Enter critical section */
  IPCCOS_MutexLock(&pClientCtxt->pRxDrv->sMutex);

  /* Check that all requested lines are in use */
  /* NOTE: Currently the same continuous signal vector needs to be unregistered as registered */
  ppRxList = &pClientCtxt->pProtocol->pClients[eCID].pList;

  if ( *ppRxList == NULL )
  { 
    IPCCLog_Out(3, "IPCCRx_DeregisterInterrupt failed (empty list) for eCID %d, nSignalLow %d, nSignalHigh %d", eCID, nSignalLow, nSignalHigh);

    /* Leave critical section */
    IPCCOS_MutexUnlock(&pClientCtxt->pRxDrv->sMutex);

    return IPCC_EUNUSED;
  }

  pRxData = *ppRxList;

  if ( ( *ppRxList != NULL ) &&
       ( IPCCRx_IsExactOverlap(*ppRxList, nSignalLow, nSignalHigh) ) )
  {
    /* Head of the list is the match */
    *ppRxList = pRxData->pNext;

    /* Disable in IPCC */
    for ( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
    {
      nSigEn = ( eCID << HWIO_SHFT(IPC_RECV_SIGNAL_DISABLE, CLIENT_ID) ) | nIdx;
      IPCCOS_Write(nAddr, nSigEn);
    }

    /* Free memory */
    IPCCOS_Free(pRxData);

    /* Leave critical section */
    IPCCOS_MutexUnlock(&pClientCtxt->pRxDrv->sMutex);

    /* Log removal */
    IPCCLog_Out(3, "IPCCRx_DeregisterInterrupt successful for eCID %d, nSignalLow %d, nSignalHigh %d from head", eCID, nSignalLow, nSignalHigh);

    return IPCC_EOK;
  }

  while( pRxData->pNext != NULL )
  {
    if( IPCCRx_IsExactOverlap(pRxData->pNext, nSignalLow, nSignalHigh) )
    {
      /* Remove between */
      pRxToRemove = pRxData->pNext;
      pRxData->pNext = pRxToRemove->pNext;

      /* Disable in IPCC */
      for ( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
      {
        nSigEn = ( eCID << HWIO_SHFT(IPC_RECV_SIGNAL_DISABLE, CLIENT_ID) ) | nIdx;
        IPCCOS_Write(nAddr, nSigEn);
      }

      /* Free memory */
      IPCCOS_Free(pRxToRemove);

      /* Leave critical section */
      IPCCOS_MutexUnlock(&pClientCtxt->pRxDrv->sMutex);

      /* Log removal */
      IPCCLog_Out(3, "IPCCRx_DeregisterInterrupt successful for eCID %d, nSignalLow %d, nSignalHigh %d from between", eCID, nSignalLow, nSignalHigh);

      return IPCC_EOK;
    }

    pRxData = pRxData->pNext;
  }

  /* Leave critical section */
  IPCCOS_MutexUnlock(&pClientCtxt->pRxDrv->sMutex);

  IPCCLog_Out(3, "IPCCRx_DeregisterInterrupt failed (not found) for eCID %d, SignalLow: %d, SignalHigh: %d", eCID, nSignalLow, nSignalHigh);

  return IPCC_ENOTFOUND;
}




/* =========================================================================
**  Function : IPCCRx_EnableInterrupt
** =========================================================================*/

IPCCErr 
IPCCRx_EnableInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  uintptr_t nAddr;
  uint32_t nIdx, nSigEn;
  
  /*-------------------------------------------------------------------------*/

  if( pClientCtxt == NULL ||
      pClientCtxt->pProtocol == NULL ||
      eCID >= pClientCtxt->pProtocol->nNumClients ||
      nSignalLow > nSignalHigh ||
      nSignalHigh >= pClientCtxt->pProtocol->nNumSigs )
  {
    IPCCLog_Out(3, "IPCCRx_EnableInterrupt failed (arg) for eCID %d, nSignalLow %d, nSignalHigh %d", eCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }
  
  /* Get data needed for IPCC */
  nAddr = HWIO_ADDRXI2(pClientCtxt->pProtocol->nVirtBaseAddress, IPC_RECV_SIGNAL_ENABLE, 0, 0 );

  /* Enter critical section */
  IPCCOS_MutexLock(&pClientCtxt->pRxDrv->sMutex);
  
  /* Enable in IPCC */
  for ( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
  {
    nSigEn = ( eCID << HWIO_SHFT(IPC_RECV_SIGNAL_ENABLE, CLIENT_ID) ) | nIdx;
    IPCCOS_Write(nAddr, nSigEn);
  }
  
  /* Leave critical section */
  IPCCOS_MutexUnlock(&pClientCtxt->pRxDrv->sMutex);
   
  /* Log */
  IPCCLog_Out(3, "IPCCRx_EnableInterrupt successful for eCID %d, nSignalLow %d, nSignalHigh %d", eCID, nSignalLow, nSignalHigh);
    
  return IPCC_EOK;
}

/* =========================================================================
**  Function : IPCCRx_DisableInterrupt
** =========================================================================*/

IPCCErr 
IPCCRx_DisableInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  uintptr_t nAddr;
  uint32_t nIdx, nSigEn;
  
  /*-------------------------------------------------------------------------*/

  if( pClientCtxt == NULL ||
      pClientCtxt->pProtocol == NULL ||
      eCID >= pClientCtxt->pProtocol->nNumClients ||
      nSignalLow > nSignalHigh ||
      nSignalHigh >= pClientCtxt->pProtocol->nNumSigs )
  {
    IPCCLog_Out(3, "IPCCRx_DisableInterrupt failed (arg) for eCID %d, nSignalLow %d, nSignalHigh %d", eCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }
   
  /* Get data needed for IPCC */
  nAddr = HWIO_ADDRXI2(pClientCtxt->pProtocol->nVirtBaseAddress, IPC_RECV_SIGNAL_DISABLE, 0, 0 );

  /* Enter critical section */
  IPCCOS_MutexLock(&pClientCtxt->pRxDrv->sMutex);
  
  /* Disable in IPCC */
  for ( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
  {
    nSigEn = ( eCID << HWIO_SHFT(IPC_RECV_SIGNAL_DISABLE, CLIENT_ID) ) | nIdx;
    IPCCOS_Write(nAddr, nSigEn);
  }
  
  /* Leave critical section */
  IPCCOS_MutexUnlock(&pClientCtxt->pRxDrv->sMutex);
   
  /* Log */
  IPCCLog_Out(3, "IPCCRx_DisableInterrupt successful for eCID %d, nSignalLow %d, nSignalHigh %d", eCID, nSignalLow, nSignalHigh);
    
  return IPCC_EOK;
   
}


/* =========================================================================
**  Function : IPCCRx_GetConfig
** =========================================================================*/

IPCCErr 
IPCCRx_GetConfig
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_ConfigType   eConfigType,
  uint32_t*         pnValue
)
{
  IPCCRxDataType* pRxData;

  /*-------------------------------------------------------------------------*/

  if( pClientCtxt == NULL ||
      pClientCtxt->pProtocol == NULL ||
      eCID >= pClientCtxt->pProtocol->nNumClients ||
      nSignalLow > nSignalHigh ||
      nSignalHigh >= pClientCtxt->pProtocol->nNumSigs ||
      pnValue == NULL )
  {
    IPCCLog_Out(4, "IPCCRx_GetConfig failed (arg) for eCID %d, nSignalLow %d, nSignalHigh %d, eConfigType %d", eCID, nSignalLow, nSignalHigh, eConfigType);
    return IPCC_EARG;
  }

  switch ( eConfigType )
  {
    case IPCC_CT_PRIORITY:
      /* TODO: Implement? */
      *pnValue = 0;
      break;
    case IPCC_CT_ISLAND:
      pRxData = IPCCRx_GetNode(pClientCtxt->pProtocol->pClients[eCID].pList, nSignalLow, nSignalHigh);
      if (!pRxData)
      {
        return IPCC_ENOTFOUND;
      }
      *pnValue = pRxData->bIsland;
      break;
    default:
      break;
  }

  return IPCC_EOK;
}


/* =========================================================================
**  Function : IPCC_SetConfig
** =========================================================================*/

IPCCErr 
IPCCRx_SetConfig
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_ConfigType   eConfigType,
  uint32_t          nValue
)
{
  IPCCRxDataType* pRxData;

  /*-------------------------------------------------------------------------*/

  if( pClientCtxt == NULL ||
      pClientCtxt->pProtocol == NULL ||
      eCID >= pClientCtxt->pProtocol->nNumClients ||
      nSignalLow > nSignalHigh ||
      nSignalHigh >= pClientCtxt->pProtocol->nNumSigs )
  {
    IPCCLog_Out(4, "IPCCRx_GetConfig failed (arg) for eCID %d, nSignalLow %d, nSignalHigh %d, eConfigType %d", eCID, nSignalLow, nSignalHigh, eConfigType);
    return IPCC_EARG;
  }

  switch ( eConfigType )
  {
    case IPCC_CT_PRIORITY:
      /* TODO: Implement? */

      break;
    case IPCC_CT_ISLAND:
      if ( nValue > 1 )
      {
        return IPCC_EARG;
      }

      pRxData = IPCCRx_GetNode(pClientCtxt->pProtocol->pClients[eCID].pList, nSignalLow, nSignalHigh);
      if ( !pRxData )
      {
        return IPCC_ENOTFOUND;
      }

      pRxData->bIsland = nValue;
      break;

    default:
      break;
  }

  return IPCC_EOK;
}