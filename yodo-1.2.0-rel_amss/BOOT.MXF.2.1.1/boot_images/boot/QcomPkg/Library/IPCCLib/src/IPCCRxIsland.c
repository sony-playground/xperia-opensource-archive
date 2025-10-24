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

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/src/IPCCRxIsland.c#1 $
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

IPCCRxDrvType RxDrv;

/*=========================================================================
      Internal functions
==========================================================================*/


/* =========================================================================
**  Function : IPCC_RxIsr
** =========================================================================*/

void
IPCC_RxIsr
(
  uintptr_t nArg
)
{
  IPCC_CB           pfnCB;
  IPCC_CBData       nData;
  IPCC_Client       eCid;
  IPCC_Signal       nSig;
  uint32_t          nInData;
  IPCCRxDataType*   pRxList;
  IPCCRxDataType*   pRxData;
  IPCCProtocolType* pProtocol = (IPCCProtocolType*)nArg; 
  uintptr_t         nAddress;

  /*-------------------------------------------------------------------------*/

  /* Read IPCC_RECV register to determine the signal */
  nAddress = HWIO_ADDRXI2(pProtocol->nVirtBaseAddress, IPC_RECV_ID, 0, 0 );
  nInData = IPCCOS_Read(nAddress);

  while ( nInData != IPCC_NO_DATA )
  {
    /* First clear signal if required */
    if ( pProtocol->bClearOnRecvEn != 1 )
    {
      nAddress = HWIO_ADDRXI2(pProtocol->nVirtBaseAddress, IPC_RECV_SIGNAL_CLEAR, 0, 0);
      IPCCOS_Write(nAddress, nInData);
    }

    /* Clear callback data */
    pfnCB = NULL;
    nData = 0;
    pRxData = NULL;

    /* Get Sender CID and SID */
    eCid = IPCC_GET_CID(nInData);
    nSig = IPCC_GET_SID(nInData);

    /* Enter list critical section */
    IPCCOS_MutexLock(&RxDrv.RxProtocolDrv[pProtocol->nProtocolId].sMutex);

    /* Get the callback */
    pRxList = pProtocol->pClients[eCid].pList;
    while( pRxList != NULL )
    {
      if( nSig >= pRxList->nSignalLow && nSig <= pRxList->nSignalHigh )
      {
        /* Get Callback Data */
        pfnCB = pRxList->pfnCb;
        nData = pRxList->nArg;

        pRxData = pRxList;

        /* Break since it was handled */
        break;
      }

      pRxList = pRxList->pNext;
    }

    /* Exit list critical section */
    IPCCOS_MutexUnlock(&RxDrv.RxProtocolDrv[pProtocol->nProtocolId].sMutex);

    if ( pfnCB != NULL )
    {
      IPCCLog_Out(2, "IPCC_RxIsr handled signal for eCID %d, nSignal %d", eCid, nSig);
      if (pProtocol->bIsIslandInterrupt)
      {
        IPCCOS_CallbackExt(pfnCB, nData, eCid, nSig, pRxData->bIsland);
      }
      else
      {
        IPCCOS_Callback(pfnCB, nData, eCid, nSig);
      }
    }
    else
    {
      IPCCLog_Out(2, "IPCC_RxIsr unhandled signal for eCID %d, nSignal %d", eCid, nSig);
    }

    /* Read IPCC_RECV register to check for any other signals */
    nAddress = HWIO_ADDRXI2(pProtocol->nVirtBaseAddress, IPC_RECV_ID, 0, 0 );
    nInData = IPCCOS_Read(nAddress);
  }

  IPCCOS_InterruptDone(RxDrv.RxProtocolDrv[pProtocol->nProtocolId].hInterruptHandle, pProtocol->nInterrupt);
}
