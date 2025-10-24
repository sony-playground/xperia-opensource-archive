/*
===========================================================================
*/
/**
  @file IPCCLegacy.c

  IPC Controller driver legacy interface.
*/
/*
  ====================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/src/IPCCLegacyIsland.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/
#include "IPCC.h"
#include "IPCC_Image.h"
#include "IPCC_Internal.h"
#include "IPCC_Legacy.h"
#include "IPCC_Log.h"
#include "IPCC_OS.h"
#include "err.h"
#include "HALhwio.h"

/*=========================================================================
      Macros
==========================================================================*/
#define CID_SHIFT 16
#define SIG_SHIFT 0
#define CID_MASK  0xffff
#define SIG_MASK  0xffff

#define DECODE_CID(a) ( ( a >> CID_SHIFT ) & CID_MASK )
#define DECODE_SIG(a) ( ( a >> SIG_SHIFT ) & SIG_MASK )

/*=========================================================================
      Static definitions
==========================================================================*/

IPCCLegacyDrvCtxt IPCCLegacyDrv;

/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : IPCC_LegacyIsr
** =========================================================================*/

void
IPCC_LegacyIsr
(
  uint32_t nDataIn
)
{
  IPCC_Client       eCid = DECODE_CID(nDataIn);
  IPCC_Signal       nSig = DECODE_SIG(nDataIn);

  /*-------------------------------------------------------------------------*/


  if ( IPCCLegacyDrv.pLegacyBSP->pLegacyData[eCid].pLegacyData[nSig].pfnCb != NULL )
  {
    IPCCOS_Callback(IPCCLegacyDrv.pLegacyBSP->pLegacyData[eCid].pLegacyData[nSig].pfnCb,
                    IPCCLegacyDrv.pLegacyBSP->pLegacyData[eCid].pLegacyData[nSig].nArg,
                    eCid,
                    nSig);
  }
  IPCCOS_InterruptDone(&IPCCLegacyDrv.hInterruptHandle, 
                       IPCCLegacyDrv.pLegacyBSP->pLegacyData[eCid].pLegacyData[nSig].nInterruptId);
}


/* =========================================================================
**  Function : IPCCLegacy_Trigger
** =========================================================================*/

IPCCErr 
IPCCLegacy_Trigger
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eTargetCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  uintptr_t nBaseAddress;
  uint32_t nMask;
  uint32_t nIdx;

  /*-------------------------------------------------------------------------*/

  /* Check arguments */
  if ( pClientCtxt == NULL ||
       pClientCtxt->pLegacyDrv == NULL ||
       pClientCtxt->pLegacyDrv->pLegacyBSP == NULL ||
       eTargetCID >= pClientCtxt->pLegacyDrv->pLegacyBSP->nCount ||
       nSignalHigh >= pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eTargetCID].nCount ||
       nSignalLow  >= pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eTargetCID].nCount )
  {
    IPCCLog_Out(3, "IPCCLegacy_Trigger failed for eTargetCID %d, nSignalLow %d, nSignalHigh %d", eTargetCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  /* Get the data needed to trigger outgoing interrupt */
  nBaseAddress = pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eTargetCID].pReg->nBaseAddress;
  nBaseAddress += pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eTargetCID].pReg->nOffset;

  for ( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
  {
    nMask = pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eTargetCID].pLegacyData[nIdx].nOutMask;

    /* Trigger interrupt */
    IPCCOS_Write(nBaseAddress, nMask);

    /* Log triggering */
    IPCCLog_Out(3, "IPCCLegacy_Trigger for eTargetCID %d, nSignalLow %d, nSignalHigh %d", eTargetCID, nSignalLow, nSignalHigh);
  }

  /* Success */
  return IPCC_EOK;
}
