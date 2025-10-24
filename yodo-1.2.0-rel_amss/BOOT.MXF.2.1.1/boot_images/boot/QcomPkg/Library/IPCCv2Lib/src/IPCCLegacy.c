/*
================================================================================
*/
/**
  @file IPCCLegacy.c

  IPCC driver legacy interface.
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
#include "IPCC_Image.h"
#include "IPCC_Log.h"
#include "IPCC_Legacy.h"


/*==============================================================================
  Externs
==============================================================================*/

extern IPCCLegacyDrvCtxt IPCCLegacyDrv;


/*==============================================================================
  Functions
==============================================================================*/

/* =============================================================================
**  Function : IPCCLegacy_Init
** ===========================================================================*/
/**
  See IPCC_Legacy.h
*/

void IPCCLegacy_Init
(
  void
)
{
  /* Initialize BSP data */
  IPCCLegacy_InitImage(&IPCCLegacyDrv);

  /* Attach to InterruptDrv */
  IPCCOS_InitInterruptHandle(&IPCCLegacyDrv.hInterruptHandle);

  IPCCLog_Out(0, "IPCCLegacy Initialized");
}

/* =============================================================================
**  Function : IPCCLegacy_Attach
** ===========================================================================*/
/**
  See IPCC_Legacy.h
*/

void IPCCLegacy_Attach
(
  IPCCClientCtxt *pClientCtxt
)
{
  if (pClientCtxt)
  {
    pClientCtxt->pLegacyDrv = &IPCCLegacyDrv;
    pClientCtxt->pLegacyDrv->nRefs++;
  }
}

/* =============================================================================
**  Function : IPCCLegacy_Detach
** ===========================================================================*/
/**
  See IPCC_Legacy.h
*/

void IPCCLegacy_Detach
(
  IPCCClientCtxt *pClientCtxt
)
{
  if (pClientCtxt && pClientCtxt->pLegacyDrv)
  {
    pClientCtxt->pLegacyDrv->nRefs--;
    pClientCtxt->pLegacyDrv = NULL;
  }
}

/* =============================================================================
**  Function : IPCCLegacy_RegisterInterrupt
** ===========================================================================*/
/**
  See IPCC_Legacy.h
*/

IPCCErr IPCCLegacy_RegisterInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCC_Client     eSenderCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh,
  IPCC_CB         pfnCB,
  IPCC_CBData     nData
)
{
  uint32_t        nIdx;
  IPCCLegacyType *pLegacyData;
  uint32_t        nInterruptId;

  /* Sanity check(s) */
  if ((NULL == pClientCtxt)                                        ||
      (NULL == pClientCtxt->pLegacyDrv)                            ||
      (NULL == pClientCtxt->pLegacyDrv->pLegacyBSP)                ||
      (eSenderCID  >= pClientCtxt->pLegacyDrv->pLegacyBSP->nCount) ||
      (nSignalLow  >  nSignalHigh)                                 ||
      (nSignalHigh >=
         pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].nCount))
  {
    IPCCLog_Out(
      4, "%s: FAIL. Invalid arg(s) - client %d, nSignalLow %d, nSignalHigh %d",
      __func__, eSenderCID, nSignalLow, nSignalHigh);

    return IPCC_EARG;
  }

  pLegacyData = &pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID];

  /* Check that none of the requested signals are in use */
  for (nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++)
  {
    if (NULL != pLegacyData->pLegacyData[nIdx].pfnCb)
    {
      IPCCLog_Out(
        4,
        "%s: FAIL. Requested signals already in use for eSenderCID %d, \
nSignalLow %d, nSignalHigh %d",
        __func__, eSenderCID, nSignalLow, nSignalHigh);

      return IPCC_EINUSE;
    }
  }

  /* Populate state table and register the interrupts with the OS */
  for (nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++)
  {
    pLegacyData->pLegacyData[nIdx].pfnCb = pfnCB;
    pLegacyData->pLegacyData[nIdx].nArg  = nData;

    nInterruptId = pLegacyData->pLegacyData[nIdx].nInterruptId;

    /* Check if this line is supported */
    if (IPCC_INT_NONE == nInterruptId)
    {
      IPCCLog_Out(
        3, "%s: FAIL. Signal %d not supported for client %d",
        __func__, nIdx, eSenderCID);

      return IPCC_ENOTSUPPORTED;
    }

    /*
     * This is a roundabout way to ensure legacy interrupts which can be handled
     * in island mode, are in fact handled in island mode. For normal IPCC
     * interrupts, IPCC_SetConfig is expected to be invoked after
     * IPCC_RegisterInterrupt. To support island legacy interrupts, we cannot
     * use the BSP island mode flag here as it will not be set through
     * SetConfig() at this point.
     * The workaround to this self-imposed quandary: handle all interrupts in
     * island mode. Within the ISR, issue an island exit if an interrupt is not
     * marked as island capable by the client.
     */
    if (IPCC_EOK != IPCCOS_RegisterInterrupt(
                      &pClientCtxt->pLegacyDrv->hInterruptHandle, nInterruptId,
                      1, IPCCOS_TRIGGER_RISING, (IPCCOSCB)IPCC_LegacyIsr,
                      (uintptr_t)ENCODE_ARG(eSenderCID, nIdx)))
    {
      IPCCLog_Out(
        3, "%s: FAIL. Signal %d could not be registered for client %d",
        __func__, nIdx, eSenderCID);

      return IPCC_EGENERR;
    }
  }

  IPCCLog_Out(
    4, "%s: SUCCESS. Registered signals %d to %d for client %d",
    __func__, nSignalLow, nSignalHigh, eSenderCID);

  return IPCC_EOK;
}

/* =============================================================================
**  Function : IPCCLegacy_DeregisterInterrupt
** ===========================================================================*/
/**
  See IPCC_Legacy.h
*/

IPCCErr IPCCLegacy_DeregisterInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCC_Client     eSenderCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh
)
{
  uint32_t        nIdx;
  IPCCLegacyType *pLegacyData;
  uint32_t        nInterruptId;

  /* Sanity check(s) */
  if ((NULL == pClientCtxt)                                        ||
      (NULL == pClientCtxt->pLegacyDrv)                            ||
      (NULL == pClientCtxt->pLegacyDrv->pLegacyBSP)                ||
      (eSenderCID  >= pClientCtxt->pLegacyDrv->pLegacyBSP->nCount) ||
      (nSignalLow  >  nSignalHigh)                                 ||
      (nSignalHigh >=
         pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].nCount))
  {
    IPCCLog_Out(
      4, "%s: FAIL. Invalid arg(s) - client %d, nSignalLow %d, nSignalHigh %d",
      __func__, eSenderCID, nSignalLow, nSignalHigh);

    return IPCC_EARG;
  }

  pLegacyData = &pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID];

  /* Check that all requested signals are registered for */
  for (nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++)
  {
    if (NULL == pLegacyData->pLegacyData[nIdx].pfnCb)
    {
      IPCCLog_Out(
        4, "%s: FAIL. No callback registered for client %d, signal %d",
        __func__, eSenderCID, nIdx);

      return IPCC_EUNUSED;
    }
  }

  /* Deregister the interrupts with the OS and update the state table */
  for (nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++)
  {
    nInterruptId = pLegacyData->pLegacyData[nIdx].nInterruptId;

    if (IPCC_EOK != IPCCOS_DeregisterInterrupt(
                      &pClientCtxt->pLegacyDrv->hInterruptHandle, nInterruptId))
    {
      IPCCLog_Out(
        3, "%s: FAIL. Signal %d could not be deregistered for client %d",
        __func__, nIdx, eSenderCID);

      return IPCC_EGENERR;
    }

    /* Update the state table */
    pLegacyData->pLegacyData[nIdx].pfnCb = NULL;
    pLegacyData->pLegacyData[nIdx].nArg = 0;
  }

  IPCCLog_Out(
    4, "%s: SUCCESS. Deregistered signals %d to %d for client %d",
    __func__, nSignalLow, nSignalHigh, eSenderCID);

  return IPCC_EOK;
}

/* =============================================================================
**  Function : IPCCLegacy_GetConfig
** ===========================================================================*/
/**
  See IPCC_Legacy.h
*/

IPCCErr IPCCLegacy_GetConfig
(
  IPCCClientCtxt  *pClientCtxt,
  IPCC_Client      eCID,
  IPCC_Signal      nSignalLow,
  IPCC_Signal      nSignalHigh,
  IPCC_ConfigType  eConfigType,
  uint32_t        *pnValue
)
{
  uint32_t        nIdx;
  IPCCLegacyType *pLegacyData;

  /* Sanity check(s) */
  if ((NULL == pClientCtxt)                                        ||
      (NULL == pnValue)                                            ||
      (NULL == pClientCtxt->pLegacyDrv)                            ||
      (NULL == pClientCtxt->pLegacyDrv->pLegacyBSP)                ||
      (eCID        >= pClientCtxt->pLegacyDrv->pLegacyBSP->nCount) ||
      (nSignalLow  >  nSignalHigh)                                 ||
      (nSignalHigh >=
         pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eCID].nCount))
  {
    IPCCLog_Out(
      4,
      "%s: FAIL. Invalid arg(s) - client %d, nSignalLow %d, nSignalHigh %d",
      __func__, eCID, nSignalLow, nSignalHigh);

    return IPCC_EARG;
  }

  switch (eConfigType)
  {
    case IPCC_CT_ISLAND:
      pLegacyData = &pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eCID];

      /*
       * Iterate from nSignalLow to nSignalHigh. Return 1 only if all the
       * signals are configured as island-capable.
       */
      for (nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++)
      {
        *pnValue &= pLegacyData->pLegacyData[nIdx].bIslandMode;
      }

      break;

    default:
      IPCCLog_Out(
        2, "%s: FAIL. Unsupported eConfigType %d", __func__, eConfigType);

      return IPCC_ENOTSUPPORTED;
  }

  return IPCC_EOK;
}

/* =============================================================================
**  Function : IPCCLegacy_SetConfig
** ===========================================================================*/
/**
  See IPCC_Legacy.h
*/

IPCCErr IPCCLegacy_SetConfig
(
  IPCCClientCtxt  *pClientCtxt,
  IPCC_Client      eCID,
  IPCC_Signal      nSignalLow,
  IPCC_Signal      nSignalHigh,
  IPCC_ConfigType  eConfigType,
  uint32_t         nValue
)
{
  uint32_t        nIdx;
  IPCCLegacyType *pLegacyData;

  /* Sanity check(s) */
  if ((NULL == pClientCtxt)                                        ||
      (NULL == pClientCtxt->pLegacyDrv)                            ||
      (NULL == pClientCtxt->pLegacyDrv->pLegacyBSP)                ||
      (eCID        >= pClientCtxt->pLegacyDrv->pLegacyBSP->nCount) ||
      (nSignalLow  >  nSignalHigh)                                 ||
      (nSignalHigh >=
         pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eCID].nCount))
  {
    IPCCLog_Out(
      4,
      "%s: FAIL. Invalid arg(s) - client %d, nSignalLow %d, nSignalHigh %d",
      __func__, eCID, nSignalLow, nSignalHigh);

    return IPCC_EARG;
  }

  switch (eConfigType)
  {
    case IPCC_CT_ISLAND:
      if (1 < nValue)
      {
        IPCCLog_Out(
          2, "%s: FAIL. Invalid nValue argument %d", __func__, nValue);

        return IPCC_EARG;
      }

      pLegacyData = &pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eCID];
      for (nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++)
      {
        pLegacyData->pLegacyData[nIdx].bIslandMode = nValue;
      }

      break;

    default:
      IPCCLog_Out(
        2, "%s: FAIL. Unsupported eConfigType %d", __func__, eConfigType);

      return IPCC_ENOTSUPPORTED;
  }

  IPCCLog_Out(
    6,
    "%s: SUCCESS. Signals %d to %d configured for client %d, eConfigType %d - \
value %d",
    __func__, nSignalLow, nSignalHigh, eCID, eConfigType, nValue);

  return IPCC_EOK;
}

/* =============================================================================
**  Function : IPCCLegacy_ToggleInterrupt
** ===========================================================================*/
/**
  See IPCC_Legacy.h
*/

IPCCErr IPCCLegacy_ToggleInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCC_Client     eCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh,
  bool            bEnable
)
{
  uint32_t        nIdx;
  IPCCLegacyType *pLegacyData;
  uint32_t        nInterruptId;

  /* Sanity check(s) */
  if ((NULL == pClientCtxt)                                        ||
      (NULL == pClientCtxt->pLegacyDrv)                            ||
      (NULL == pClientCtxt->pLegacyDrv->pLegacyBSP)                ||
      (eCID        >= pClientCtxt->pLegacyDrv->pLegacyBSP->nCount) ||
      (nSignalLow  >  nSignalHigh)                                 ||
      (nSignalHigh >=
         pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eCID].nCount))
  {
    IPCCLog_Out(
      4,
      "%s: FAIL. Invalid arg(s) - client %d, nSignalLow %d, nSignalHigh %d",
      __func__, eCID, nSignalLow, nSignalHigh);

    return IPCC_EARG;
  }

  pLegacyData = &pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eCID];

  /*
   * Check that the requested signal is valid and toggle it through the OS
   * interrupt controller.
   */
  for (nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++)
  {
    nInterruptId = pLegacyData->pLegacyData[nIdx].nInterruptId;

    /* Check if this line is supported */
    if (IPCC_INT_NONE == nInterruptId)
    {
      IPCCLog_Out(
        3, "%s: FAIL. Signal %d not supported for client %d",
        __func__, nIdx, eCID);

      return IPCC_ENOTSUPPORTED;
    }

    if (IPCC_EOK !=
          IPCCOS_ToggleInterrupt(
            &pClientCtxt->pLegacyDrv->hInterruptHandle, nInterruptId, bEnable))
    {
      IPCCLog_Out(
        4, "%s: FAIL. Signal %d could not be toggled for client %d (bEnable %d)",
        __func__, nIdx, eCID, bEnable);

      return IPCC_EGENERR;
    }
  }

  if (bEnable)
  {
    IPCCLog_Out(
      4, "%s: SUCCESS. Signals %d to %d enabled for client %d",
      __func__, nSignalLow, nSignalHigh, eCID);
  }
  else
  {
    IPCCLog_Out(
      4, "%s: SUCCESS. Signals %d to %d disabled for client %d",
      __func__, nSignalLow, nSignalHigh, eCID);
  }

  return IPCC_EOK;
}
#endif /* IPCC_SUPPORT_LEGACY_MODE */
