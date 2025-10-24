/*
================================================================================
*/
/**
  @file IPCCIsland.c

  Island-resident portion of the interface implementation file for the IPCC
  driver.
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

#include "IPCC.h"
#include "IPCC_Internal.h"
#include "IPCC_Tx.h"
#include "IPCC_Legacy.h"
#include "IPCC_Log.h"


/*==============================================================================
  Functions
==============================================================================*/

/* =============================================================================
**  Function : IPCC_Trigger
** ===========================================================================*/
/**
  See IPCC.h
*/

IPCCErr IPCC_Trigger
(
  IPCC_Handle h,
  IPCC_Client eCID,
  IPCC_Signal nSignalLow,
  IPCC_Signal nSignalHigh
)
{
  uint32_t        nClientIdx;
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  IPCCClientType *pClientBSP;
  #endif
  IPCCErr         nErr = IPCC_EGENERR;
  IPCCClientCtxt *pClientCtxt = (IPCCClientCtxt*)h;

  /* Sanity check(s) */
  if ((NULL       == pClientCtxt) ||
      (nSignalLow >  nSignalHigh))
  {
    IPCCLog_Out(
      4, "%s: FAIL. Invalid arg(s) - eCID %d, nSignalLow %d, nSignalHigh %d",
      __func__, eCID, nSignalLow, nSignalHigh);

    return IPCC_EARG;
  }

  nErr = IPCCInternal_FindPhysClientIdx(
          eCID, pClientCtxt->pProtocol, &nClientIdx);
  if (IPCC_EOK != nErr)
  {
    IPCCLog_Out(
      4,
      "%s: FAIL. Could not find physical client for protocol %d, client %d, \
err %d",
      __func__, pClientCtxt->pProtocol->nProtocolId, eCID, nErr);

    return IPCC_EARG;
  }

  #ifdef IPCC_SUPPORT_LEGACY_MODE
  pClientBSP = &pClientCtxt->pProtocol->pClients[nClientIdx];

  if (pClientCtxt->pProtocol->bLegacySupported &&
      pClientBSP->bUseLegacyByDefault)
  {
    nErr = IPCCLegacy_Trigger(
             pClientCtxt, eCID, nSignalLow, nSignalHigh);
  }
  else if (pClientCtxt->pProtocol->bIPCCModeSupported)
  #endif
  {
    /* We should exit island mode here to access IPCC */
    nErr = IPCCTx_Trigger(
             pClientCtxt, eCID, nSignalLow, nSignalHigh);
  }
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  else
  {
    IPCCLog_Out(
      5, "%s: FAIL. Not supported - protocol %d, client %d, signals %d to %d",
      __func__, pClientCtxt->pProtocol->nProtocolId, eCID, nSignalLow,
      nSignalHigh);

    nErr = IPCC_ENOTSUPPORTED;
  }
  #endif

  return nErr;
}

/* =============================================================================
**  Function : IPCCInternal_FindPhysClientIdx
** ===========================================================================*/
/**
  See IPCC_Internal.h
*/

IPCCErr IPCCInternal_FindPhysClientIdx
(
  IPCC_Client       eVirtClient,
  IPCCProtocolType *pProtocol,
  uint32_t         *pnPhysClientIdx
)
{
  #ifdef IPCC_HWMEMOPT
  uint32_t nIdx;
  #endif
  IPCCErr  nErr = IPCC_ENOTSUPPORTED;

  /* Sanity check(s) */
  if ((NULL == pProtocol) || (NULL == pnPhysClientIdx))
  {
    return IPCC_EARG;
  }

  /* Initialize the output pointer */
  *pnPhysClientIdx = (uint32_t)-1;

  #ifdef IPCC_HWMEMOPT
  /* Loop through the client array in BSP to find the client index */
  for (nIdx = 0; nIdx < pProtocol->nNumClients; nIdx++)
  {
    if (eVirtClient == pProtocol->pClients[nIdx].eClient)
    {
      *pnPhysClientIdx = nIdx;
      nErr = IPCC_EOK;
      break;
    }
  }

  #else

  *pnPhysClientIdx = (uint32_t)eVirtClient;
  nErr = IPCC_EOK;

  #endif /* IPCC_HWMEMOPT */

  if (*pnPhysClientIdx >= pProtocol->nNumClients)
  {
    IPCCLog_Out(
      3, "%s: FAIL. Invalid client %d for protocol %d",
      __func__, eVirtClient, pProtocol->nProtocolId);

    nErr = IPCC_ENOTSUPPORTED;
  }

  return nErr;
}
