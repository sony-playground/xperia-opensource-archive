/*
===========================================================================
*/
/**
  @file IPCCTx.c

  IPC Controller driver Tx portion of the driver.
*/
/*
  ====================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ====================================================================

  $Header: $
  $DateTime: $
  $Author: $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/
#include "IPCC.h"
#include "IPCC_Internal.h"
#include "IPCC_Tx.h"
#include "IPCC_Log.h"
#include "IPCCHWIO.h"

/*=========================================================================
      Static defiintions
==========================================================================*/

static IPCCTxDrvType TxDrv;

/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : IPCCTx_Init
** =========================================================================*/

void
IPCCTx_Init
(
   IPCCDrvCtxt* pDrv
)
{

  /*-------------------------------------------------------------------------*/

  /* Apply Tx Drv to Master Drv */
  if ( pDrv != NULL )
  {
    pDrv->pTxDrv = &TxDrv;
  }

  IPCCLog_Out(0, "IPCCTx Initialized");
}


/* =========================================================================
**  Function : IPCCTx_Trigger
** =========================================================================*/

IPCCErr 
IPCCTx_Trigger
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
      nSignalLow > nSignalHigh ||
      nSignalHigh >= pClientCtxt->pProtocol->nNumSigs )
  {
    IPCCLog_Out(3, "IPCCTx_Trigger failed (arg) for eCID %d, nSignalLow %d, nSignalHigh %d", eCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }


  /* Get address and protocol */
  nAddr = HWIO_ADDRXI2(pClientCtxt->pProtocol->nVirtBaseAddress, IPC_SEND, 0, 0);

  /* Trigger outgoing interrupt */
  /* For now, trigger one-by-one, but ideally we can use Global trigger mask */
  for( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
  {
    nSigEn = ( eCID << HWIO_SHFT(IPC_SEND, CLIENT_ID) ) | nIdx;
    IPCCOS_Write(nAddr, nSigEn);
  }

  IPCCLog_Out(
    5, "%s called for eCID %d, protocol %d, SignalLow: %d, SignalHigh: %d",
    __func__, eCID, pClientCtxt->pProtocol->nProtocolId, nSignalLow,
    nSignalHigh);

  return IPCC_EOK;
}
