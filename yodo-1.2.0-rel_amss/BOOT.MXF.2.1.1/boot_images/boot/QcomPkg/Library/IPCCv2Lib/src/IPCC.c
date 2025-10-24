/*
================================================================================
*/
/**
  @file IPCC.c

  Interface implementation file for the IPCC driver.
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

#include <stdlib.h>
#include <string.h>
#include "IPCC.h"
#include "IPCC_Internal.h"
#include "IPCC_Rx.h"
#include "IPCC_Tx.h"
#include "IPCC_Legacy.h"
#include "IPCC_Image.h"
#include "IPCC_Log.h"
#ifdef IPCC_SUPPORT_INFO
#include "IPCC_InfoInternal.h"
#endif

/*==============================================================================
  Macros
==============================================================================*/

/* Code shortening macros */

/*
 * Macro to map the virtual client to physical client if HW memory optimization
 * is supported. If not, it performs input sanity.
 */
#define IPCC_CLIENT_MAP_AND_CHECK(eCID, nClientIdx)                       \
nErr = IPCCInternal_FindPhysClientIdx(                                    \
         eCID, pClientCtxt->pProtocol, &nClientIdx);                      \
if (IPCC_EOK != nErr)                                                     \
{                                                                         \
  IPCCLog_Out(                                                            \
    4,                                                                    \
    "%s: FAIL. Could not find physical client for protocol %d, client %d, \
err %d",                                                                  \
    __func__, pClientCtxt->pProtocol->nProtocolId, eCID, nErr);           \
                                                                          \
  return IPCC_EARG;                                                       \
}                                                                         \
                                                                          \
pClientBSP = &pClientCtxt->pProtocol->pClients[nClientIdx];

/* Common not supported log print macro */
#define IPCC_LOG_NOTSUPPORTED                                             \
IPCCLog_Out(                                                              \
  5, "%s: FAIL. Not supported - protocol %d, client %d, signals %d to %d",\
  __func__, pClientCtxt->pProtocol->nProtocolId, eCID, nSignalLow,        \
  nSignalHigh);                                                           \
                                                                          \
nErr = IPCC_ENOTSUPPORTED;

/* Common sanity check log print macro */
#define IPCC_LOG_CHECKARG                                                 \
IPCCLog_Out(                                                              \
  4,                                                                      \
  "%s: FAIL. Invalid arg(s) - eCID %d, nSignalLow %d, nSignalHigh %d",    \
  __func__, eCID, nSignalLow, nSignalHigh);                               \
                                                                          \
return IPCC_EARG;


/*==============================================================================
  Data
==============================================================================*/

static IPCCDrvCtxt IPCCDrv;


/*==============================================================================
  Functions
==============================================================================*/

/* =============================================================================
**  Function : IPCC_Init
** ===========================================================================*/
/**
  Initialize the IPCC driver.
  This function initializes the IPC controller driver,
  it is the main init entry point for this driver.

  @param
  None.

  @return
  None.

  @dependencies
  None.
*/

void IPCC_Init
(
  void
)
{
  /* Initialize log */
  IPCCLog_Init();

  /* Initialize BSP data */
  IPCC_InitImage(&IPCCDrv);

  /* Initialize Rx driver */
  IPCCRx_Init(&IPCCDrv);

  /* Initialize Tx driver */
  IPCCTx_Init(&IPCCDrv);

  /* Initialize legacy driver */
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  IPCCLegacy_Init();
  #endif

  #ifdef IPCC_SUPPORT_INFO
  /* Initialize Info portion of the driver */
  IPCCInfo_Init(&IPCCDrv);
  #endif
}

/* =============================================================================
**  Function : IPCC_Attach
** ===========================================================================*/
/**
  See IPCC.h
*/

IPCCErr IPCC_Attach
(
  IPCC_Handle   *pH,
  IPCC_Protocol  eProtocol
)
{
  IPCCClientCtxt *pClientCtxt;

  /* Sanity check(s) */
  if ((NULL == pH) || (IPCC_P_TOTAL <= eProtocol))
  {
    IPCCLog_Out(
      2, "%s: FAIL. Invalid handle or protocol %d passed", __func__, eProtocol);
    return IPCC_EARG;
  }

  /* Make sure driver is initialized */
  if (IPCCDrv.pBSP)
  {
    /* Check if this protocol is supported */
    if ((eProtocol >= IPCCDrv.pBSP->nNumProtocols) ||
        (IPCCDrv.pBSP->pProtocols[eProtocol].nNumSigs == 0))
    {
      IPCCLog_Out(
        2, "%s: FAIL. Protocol %d not supported on this target/subsystem",
        eProtocol);

      return IPCC_ENOTSUPPORTED;
    }

    /* Malloc client context */
    pClientCtxt = (IPCCClientCtxt*)IPCCOS_Malloc(sizeof(IPCCClientCtxt));
    if (NULL != pClientCtxt)
    {
      /* Clear memory */
      memset(pClientCtxt, 0, sizeof(IPCCClientCtxt));

      /* Set variables for client context */
      pClientCtxt->pProtocol = &IPCCDrv.pBSP->pProtocols[eProtocol];

      /* Attach to legacy driver if supported */
      #ifdef IPCC_SUPPORT_LEGACY_MODE
      if (pClientCtxt->pProtocol->bLegacySupported)
      {
        IPCCLegacy_Attach(pClientCtxt);
      }

      /* Attach to the Rx driver */
      if (pClientCtxt->pProtocol->bIPCCModeSupported)
      #endif
      {
        IPCCRx_Attach(pClientCtxt);
      }

      /* Set client pointer */
      *pH = (IPCC_Handle)pClientCtxt;

      /* Return success */
      return IPCC_EOK;
    }
    return IPCC_EMEM;
  }

  /* IPCC is not yet initialized */
  return IPCC_EGENERR;
}

/* =============================================================================
**  Function : IPCC_Detach
** ===========================================================================*/
/**
  See IPCC.h
*/

IPCCErr IPCC_Detach
(
  IPCC_Handle *pH
)
{
  IPCCClientCtxt *pClientCtxt;

  /* Sanity check(s) */
  if (NULL == pH)
  {
    return IPCC_EARG;
  }

  /* Get client context */
  pClientCtxt = (IPCCClientCtxt*)*pH;

  /* Attach to legacy driver if supported */
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  if (pClientCtxt->pProtocol && pClientCtxt->pProtocol->bLegacySupported)
  {
    IPCCLegacy_Detach(pClientCtxt);
  }
  #endif

  /* Clean up client context */
  pClientCtxt->pProtocol = NULL;

  /* Free up the memory */
  IPCCOS_Free(pClientCtxt);

  /* Clear pointer */
  *pH = NULL;

  /* Return success */
  return IPCC_EOK;
}

/* =============================================================================
**  Function : IPCC_RegisterInterrupt
** ===========================================================================*/
/**
  See IPCC.h
*/

IPCCErr IPCC_RegisterInterrupt
(
  IPCC_Handle h,
  IPCC_Client eCID,
  IPCC_Signal nSignalLow,
  IPCC_Signal nSignalHigh,
  IPCC_CB     pfnCB,
  IPCC_CBData nData
)
{
  uint32_t        nClientIdx;
  IPCCClientType *pClientBSP;
  IPCCErr         nErr = IPCC_EGENERR;
  IPCCClientCtxt *pClientCtxt = (IPCCClientCtxt*)h;

  /* Sanity check(s) */
  if ((NULL       == pClientCtxt)  ||
      (NULL       == pfnCB)        ||
      (nSignalLow >  nSignalHigh))
  {
    IPCC_LOG_CHECKARG;
  }

  IPCC_CLIENT_MAP_AND_CHECK(eCID, nClientIdx);

  #ifdef IPCC_SUPPORT_LEGACY_MODE
  if (pClientCtxt->pProtocol->bLegacySupported &&
      pClientBSP->bUseLegacyByDefault)
  {
    nErr = IPCCLegacy_RegisterInterrupt(
             pClientCtxt, eCID, nSignalLow, nSignalHigh, pfnCB, nData);
  }
  else if (pClientCtxt->pProtocol->bIPCCModeSupported)
  #endif
  {
    nErr = IPCCRx_RegisterInterrupt(
             pClientCtxt, pClientBSP, eCID, nSignalLow, nSignalHigh, pfnCB,
             nData);
  }
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  else
  {
    IPCC_LOG_NOTSUPPORTED;
  }
  #endif

  return nErr;
}

/* =============================================================================
**  Function : IPCC_DeregisterInterrupt
** ===========================================================================*/
/**
  See IPCC.h
*/

IPCCErr IPCC_DeregisterInterrupt
(
  IPCC_Handle h,
  IPCC_Client eCID,
  IPCC_Signal nSignalLow,
  IPCC_Signal nSignalHigh
)
{
  uint32_t        nClientIdx;
  IPCCClientType *pClientBSP;
  IPCCErr         nErr = IPCC_EGENERR;
  IPCCClientCtxt *pClientCtxt = (IPCCClientCtxt*)h;

  /* Sanity check(s) */
  if ((NULL == pClientCtxt) || (nSignalLow > nSignalHigh))
  {
    IPCC_LOG_CHECKARG;
  }

  IPCC_CLIENT_MAP_AND_CHECK(eCID, nClientIdx);

  #ifdef IPCC_SUPPORT_LEGACY_MODE
  if (pClientCtxt->pProtocol->bLegacySupported &&
      pClientBSP->bUseLegacyByDefault)
  {
    nErr = IPCCLegacy_DeregisterInterrupt(
             pClientCtxt, eCID, nSignalLow, nSignalHigh);
  }
  else if (pClientCtxt->pProtocol->bIPCCModeSupported)
  #endif
  {
    nErr = IPCCRx_DeregisterInterrupt(
             pClientCtxt, pClientBSP, eCID, nSignalLow, nSignalHigh);
  }
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  else
  {
    IPCC_LOG_NOTSUPPORTED;
  }
  #endif

  return nErr;
}

#ifdef IPCC_SUPPORT_EXTENDED_APIS
/* =============================================================================
**  Function : IPCC_GetConfig
** ===========================================================================*/
/**
  See IPCC.h
*/

IPCCErr IPCC_GetConfig
(
  IPCC_Handle      h,
  IPCC_Client      eCID,
  IPCC_Signal      nSignalLow,
  IPCC_Signal      nSignalHigh,
  IPCC_ConfigType  eConfigType,
  uint32_t        *pnValue
)
{
  uint32_t        nClientIdx;
  IPCCClientType *pClientBSP;
  IPCCErr         nErr = IPCC_EGENERR;
  IPCCClientCtxt *pClientCtxt = (IPCCClientCtxt*)h;

  /* Sanity check(s) */
  if ((NULL       == pClientCtxt)      ||
      (NULL       == pnValue)          ||
      (nSignalLow >  nSignalHigh))
  {
    IPCC_LOG_CHECKARG;
  }

  IPCC_CLIENT_MAP_AND_CHECK(eCID, nClientIdx);

  #ifdef IPCC_SUPPORT_LEGACY_MODE
  if (pClientCtxt->pProtocol->bLegacySupported &&
      pClientBSP->bUseLegacyByDefault)
  {
    nErr = IPCCLegacy_GetConfig(
             pClientCtxt, eCID, nSignalLow, nSignalHigh, eConfigType, pnValue);
  }
  else if (pClientCtxt->pProtocol->bIPCCModeSupported)
  #endif
  {
    nErr = IPCCRx_GetConfig(
             pClientCtxt, pClientBSP, eCID, nSignalLow, nSignalHigh,
             eConfigType, pnValue);
  }
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  else
  {
    IPCC_LOG_NOTSUPPORTED;
  }
  #endif

  return nErr;
}

/* =============================================================================
**  Function : IPCC_SetConfig
** ===========================================================================*/
/**
  See IPCC.h
*/

IPCCErr IPCC_SetConfig
(
  IPCC_Handle     h,
  IPCC_Client     eCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh,
  IPCC_ConfigType eConfigType,
  uint32_t        nValue
)
{
  uint32_t        nClientIdx;
  IPCCClientType *pClientBSP;
  IPCCErr         nErr = IPCC_EGENERR;
  IPCCClientCtxt *pClientCtxt = (IPCCClientCtxt*)h;

  /* Sanity check(s) */
  if ((NULL == pClientCtxt) || (nSignalLow > nSignalHigh))
  {
    IPCC_LOG_CHECKARG;
  }

  IPCC_CLIENT_MAP_AND_CHECK(eCID, nClientIdx);

  #ifdef IPCC_SUPPORT_LEGACY_MODE
  if (pClientCtxt->pProtocol->bLegacySupported &&
      pClientBSP->bUseLegacyByDefault)
  {
    nErr = IPCCLegacy_SetConfig(
             pClientCtxt, eCID, nSignalLow, nSignalHigh, eConfigType, nValue);
  }
  else if (pClientCtxt->pProtocol->bIPCCModeSupported)
  #endif
  {
    nErr = IPCCRx_SetConfig(
             pClientCtxt, pClientBSP, eCID, nSignalLow, nSignalHigh,
             eConfigType, nValue);
  }
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  else
  {
    IPCC_LOG_NOTSUPPORTED;
  }
  #endif

  return nErr;
}

/* =============================================================================
**  Function : IPCC_EnableInterrupt
** ===========================================================================*/
/**
  See IPCC.h
*/

IPCCErr IPCC_EnableInterrupt
(
  IPCC_Handle h,
  IPCC_Client eCID,
  IPCC_Signal nSignalLow,
  IPCC_Signal nSignalHigh
)
{
  IPCCClientCtxt *pClientCtxt = (IPCCClientCtxt*)h;

  return IPCCInternal_ToggleInterrupt(
           pClientCtxt, eCID, nSignalLow, nSignalHigh, true);
}

/* =============================================================================
**  Function : IPCC_DisableInterrupt
** ===========================================================================*/
/**
  See IPCC.h
*/

IPCCErr IPCC_DisableInterrupt
(
  IPCC_Handle h,
  IPCC_Client eCID,
  IPCC_Signal nSignalLow,
  IPCC_Signal nSignalHigh
)
{
  IPCCClientCtxt *pClientCtxt = (IPCCClientCtxt*)h;

  return IPCCInternal_ToggleInterrupt(
           pClientCtxt, eCID, nSignalLow, nSignalHigh, false);
}

/* =============================================================================
**  Function : IPCC_SoftInterrupt
** ===========================================================================*/
/**
  See IPCC.h
*/

IPCCErr IPCC_SoftInterrupt
(
  IPCC_Handle h,
  IPCC_Client eCID,
  IPCC_Signal nSignal
)
{
  uint32_t        nClientIdx;
  IPCCClientType *pClientBSP;
  IPCCErr         nErr = IPCC_EGENERR;
  IPCCClientCtxt *pClientCtxt = (IPCCClientCtxt*)h;

  /* Sanity check(s) */
  if (NULL == pClientCtxt)
  {
    IPCCLog_Out(
      3, "%s: FAIL. Invalid arg(s) - eCID %d, nSignal %d",
      __func__, eCID, nSignal);

    return IPCC_EARG;
  }

  IPCC_CLIENT_MAP_AND_CHECK(eCID, nClientIdx);

  #ifdef IPCC_SUPPORT_LEGACY_MODE
  if (pClientCtxt->pProtocol->bIPCCModeSupported)
  #endif
  {
    nErr = IPCCRx_SoftInterrupt(pClientCtxt, pClientBSP, eCID, nSignal);
  }
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  else
  {
    IPCCLog_Out(
      3, "%s: FAIL. Legacy not supported for client %d, signal %d",
      __func__, eCID, nSignal);

    nErr = IPCC_ENOTSUPPORTED;
  }
  #endif

  return nErr;
}

/* =============================================================================
**  Function : IPCCInternal_ToggleInterrupt
** ===========================================================================*/
/**
  See IPCC_Internal.h
*/

static IPCCErr IPCCInternal_ToggleInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCC_Client     eCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh,
  bool            bEnable
)
{
  uint32_t        nClientIdx;
  IPCCClientType *pClientBSP;
  IPCCErr         nErr = IPCC_EGENERR;

  /* Sanity check(s) */
  if ((NULL == pClientCtxt) || (nSignalLow > nSignalHigh))
  {
    IPCC_LOG_CHECKARG;
  }

  IPCC_CLIENT_MAP_AND_CHECK(eCID, nClientIdx);

  #ifdef IPCC_SUPPORT_LEGACY_MODE
  if (pClientCtxt->pProtocol->bLegacySupported &&
      pClientBSP->bUseLegacyByDefault)
  {
    nErr = IPCCLegacy_ToggleInterrupt(
             pClientCtxt, eCID, nSignalLow, nSignalHigh, bEnable);
  }
  else if (pClientCtxt->pProtocol->bIPCCModeSupported)
  #endif
  {
    nErr = IPCCRx_ToggleInterrupt(
              pClientCtxt, pClientBSP, eCID, nSignalLow, nSignalHigh, bEnable);
  }
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  else
  {
    IPCC_LOG_NOTSUPPORTED;
  }
  #endif

  return nErr;
}
#endif /* IPCC_SUPPORT_EXTENDED_APIS */
