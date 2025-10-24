/*
================================================================================
*/
/**
  @file IPCCRxIsland.c

  Island-resident portion of the IPCC Rx driver.
*/
/*
  ==============================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ==============================================================================

  $Header: $
  $DateTime: $
  $Author: $

  ==============================================================================
*/

/*==============================================================================
  Includes
==============================================================================*/

#include "IPCC_Rx.h"
#include "IPCC_Log.h"
#include "IPCCHWIO.h"


/*==============================================================================
  Data
==============================================================================*/

IPCCRxDrvType RxDrv;


/*==============================================================================
  Functions
==============================================================================*/

/* =============================================================================
**  Function : IPCC_RxIsr
** ===========================================================================*/
/**
  See IPCC_Rx.h
*/

void IPCC_RxIsr
(
  uintptr_t pArg
)
{
  IPCC_CB             pfnCB;
  IPCC_CBData         nData;
  IPCC_Client         eCid;
  IPCC_Signal         nSig;
  uint32_t            nInData;
  IPCCRxDataType     *pRxList;
  uintptr_t           nAddress;
  IPCCProtocolType   *pProtocol = (IPCCProtocolType*)pArg;

  /* Read IPCC_RECV register to determine the signal */
  #ifdef IPCC_HWMEMOPT
  nAddress = HWIO_ADDRXI2(pProtocol->nVirtBaseAddress, IPC_RECV_ID_PHYS, 0, 0);
  #else
  nAddress = HWIO_ADDRXI2(pProtocol->nVirtBaseAddress, IPC_RECV_ID, 0, 0);
  #endif
  nInData = IPCCOS_Read(nAddress);

  while (IPCC_NO_DATA != nInData)
  {
    #ifdef IPCC_CLEAR_ON_RECV_FEATURE
    /* First, clear signal if required */
    if (1 != pProtocol->bClearOnRecvEn)
    {
      nAddress = HWIO_ADDRXI2(
                   pProtocol->nVirtBaseAddress, IPC_RECV_SIGNAL_CLEAR, 0, 0);
      IPCCOS_Write(nAddress, nInData);
    }
    #endif

    /* Clear callback data */
    pfnCB = NULL;
    nData = 0;

    /* Get sender CID and SID */
    eCid = IPCC_GET_CID(nInData);
    nSig = IPCC_GET_SID(nInData);

    IPCCOS_MutexLock(&RxDrv.RxProtocolDrv[pProtocol->nProtocolId].sMutex);

    /* Get the callback */
    pRxList = pProtocol->pClients[eCid].pList;
    while (NULL != pRxList)
    {
      if (nSig >= pRxList->nSignalLow && nSig <= pRxList->nSignalHigh)
      {
        /* Get callback data */
        pfnCB = pRxList->pfnCb;
        nData = pRxList->nArg;

        /* Break since it was handled */
        break;
      }

      pRxList = pRxList->pNext;
    }

    IPCCOS_MutexUnlock(&RxDrv.RxProtocolDrv[pProtocol->nProtocolId].sMutex);

    if (NULL != pfnCB)
    {
      IPCCLog_Out(
        4, "%s: SUCCESS. Handled signal %d from protocol %d, client %d",
        __func__, nSig, pProtocol->nProtocolId, eCid);
      pfnCB(nData, eCid, nSig);
    }
    else
    {
      IPCCLog_Out(
        4, "%s: WARN. Unhandled signal %d from protocol %d, client %d",
        __func__, nSig, pProtocol->nProtocolId, eCid);
    }

    /* Read IPCC_RECV register to check for any other signals */
    #ifdef IPCC_HWMEMOPT
    nAddress = HWIO_ADDRXI2(
                 pProtocol->nVirtBaseAddress, IPC_RECV_ID_PHYS, 0, 0);
    #else
    nAddress = HWIO_ADDRXI2(pProtocol->nVirtBaseAddress, IPC_RECV_ID, 0, 0);
    #endif
    nInData = IPCCOS_Read(nAddress);
  }

  IPCCOS_InterruptDone(
    RxDrv.RxProtocolDrv[pProtocol->nProtocolId].hInterruptHandle,
    pProtocol->nInterrupt);
}
