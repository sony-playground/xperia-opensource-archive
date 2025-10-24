/*
================================================================================
*/
/**
  @file IPCCLegacyIsland.c

  Island-resident code of the IPCC driver legacy interface.
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

#ifdef IPCC_SUPPORT_LEGACY_MODE
#include "IPCC_Legacy.h"
#include "IPCC_Log.h"


/*==============================================================================
  Data
==============================================================================*/

IPCCLegacyDrvCtxt IPCCLegacyDrv;


/*==============================================================================
  Functions
==============================================================================*/

/* =============================================================================
**  Function : IPCC_LegacyIsr
** ===========================================================================*/
/**
  See IPCC_Legacy.h
*/

void IPCC_LegacyIsr
(
  uintptr_t pCtxt
)
{
  IPCCLegacyDataType *pLegacyData;
  IPCC_Client         eCID = DECODE_CID(pCtxt);
  IPCC_Signal         nSig = DECODE_SIG(pCtxt);

  pLegacyData = &IPCCLegacyDrv.pLegacyBSP->pLegacyData[eCID].pLegacyData[nSig];

  if (NULL != pLegacyData->pfnCb)
  {
    IPCCLog_Out(
      4, "%s: INFO. Invoking client %d callback for signal %d (island: %d)",
      __func__, eCID, nSig, 0);
    (pLegacyData->pfnCb)(pLegacyData->nArg, eCID, nSig);
  }
}

/* =============================================================================
**  Function : IPCCLegacy_Trigger
** ===========================================================================*/
/**
  See IPCC_Legacy.h
*/

IPCCErr IPCCLegacy_Trigger
(
  IPCCClientCtxt   *pClientCtxt,
  IPCC_Client       eTargetCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  uintptr_t       nAddr;
  uint32_t        nIdx, nMask;
  IPCCLegacyType *pLegacyData;

  /* Sanity check(s) */
  if ((NULL == pClientCtxt)                                        ||
      (NULL == pClientCtxt->pLegacyDrv)                            ||
      (NULL == pClientCtxt->pLegacyDrv->pLegacyBSP)                ||
      (eTargetCID  >= pClientCtxt->pLegacyDrv->pLegacyBSP->nCount) ||
      (nSignalLow  >  nSignalHigh)                                 ||
      (nSignalHigh >=
         pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eTargetCID].nCount))
  {
    IPCCLog_Out(
      4, "%s: FAIL. Invalid arg(s) - client %d, nSignalLow %d, nSignalHigh %d",
      __func__, eTargetCID, nSignalLow, nSignalHigh);

    return IPCC_EARG;
  }

  pLegacyData = &pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eTargetCID];

  /* Get the address needed to trigger outgoing interrupt */
  nAddr = pLegacyData->pReg->nBaseAddress + pLegacyData->pReg->nOffset;

  for (nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++)
  {
    nMask = pLegacyData->pLegacyData[nIdx].nOutMask;

    /* Trigger interrupt */
    IPCCOS_Write(nAddr, nMask);

    IPCCLog_Out(
      3, "%s: INFO. Triggered interrupt to client %d, signal %d",
      __func__, eTargetCID, nIdx);
  }

  return IPCC_EOK;
}
#endif /* IPCC_SUPPORT_LEGACY_MODE */
