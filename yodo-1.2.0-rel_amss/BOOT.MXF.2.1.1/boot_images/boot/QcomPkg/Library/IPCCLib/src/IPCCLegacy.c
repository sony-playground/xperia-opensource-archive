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

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/src/IPCCLegacy.c#1 $
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

#define ENCODE_ARG(c,s) ( ( ( s & SIG_MASK ) << SIG_SHIFT ) | \
                          ( ( c & CID_MASK ) << CID_SHIFT ) )


/*=========================================================================
      Static definitions
==========================================================================*/

extern IPCCLegacyDrvCtxt IPCCLegacyDrv;

/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : IPCCLegacy_Init
** =========================================================================*/

void
IPCCLegacy_Init
(
  void
)
{

  /*-------------------------------------------------------------------------*/

  /* Initialize BSP data */
  IPCCLegacy_InitImage(&IPCCLegacyDrv);

  /* Attach to InterruptDrv */
  IPCCOS_InitInterruptHandle(&IPCCLegacyDrv.hInterruptHandle);

  IPCCLog_Out(0, "IPCCLegacy Initialized");
}


/* =========================================================================
**  Function : IPCCLegacy_Attach
** =========================================================================*/

void
IPCCLegacy_Attach
(
  IPCCClientCtxt*   pClientCtxt
)
{
  if ( pClientCtxt )
  {
    pClientCtxt->pLegacyDrv = &IPCCLegacyDrv;
    pClientCtxt->pLegacyDrv->nRefs++;
  }
}


/* =========================================================================
**  Function : IPCCLegacy_Detach
** =========================================================================*/

void
IPCCLegacy_Detach
(
  IPCCClientCtxt*   pClientCtxt
)
{
  if ( pClientCtxt &&
       pClientCtxt->pLegacyDrv )
  {
    pClientCtxt->pLegacyDrv->nRefs--;
    pClientCtxt->pLegacyDrv = NULL;
  }
}


/* =========================================================================
**  Function : IPCCLegacy_RegisterInterrupt
** =========================================================================*/

IPCCErr 
IPCCLegacy_RegisterInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eSenderCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_CB           pfnCB,
  IPCC_CBData       nData
)
{
  uint32_t nIdx;
  uint32_t nInterruptId;

  /*-------------------------------------------------------------------------*/

  /* Check arguments */
  if ( pClientCtxt == NULL ||
       pClientCtxt->pLegacyDrv == NULL ||
       pClientCtxt->pLegacyDrv->pLegacyBSP == NULL ||
       eSenderCID >= pClientCtxt->pLegacyDrv->pLegacyBSP->nCount ||
       pfnCB == NULL ||
       nSignalLow > nSignalHigh ||
       nSignalHigh >= pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].nCount )
  {
    IPCCLog_Out(3, "IPCCLegacy_RegisterInterrupt failed (arg) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  /* Check that all requested lines are not in use */
  for ( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
  {
    if ( pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].pLegacyData[nIdx].pfnCb != NULL )
    {
      IPCCLog_Out(3, "IPCCLegacy_RegisterInterrupt failed (in use) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
      return IPCC_EINUSE;
    }
  }

  /* Populate State table */
  for ( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
  {
    /* Populate state table */
    pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].pLegacyData[nIdx].pfnCb = pfnCB;
    pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].pLegacyData[nIdx].nArg = nData;

    nInterruptId = pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].pLegacyData[nIdx].nInterruptId;

    /* Check if this line is supported */
    if ( IPCC_INT_NONE == nInterruptId )
    {
      /* For now, error fatal! */
      IPCCOS_ErrFatal("IPCCLegacy: Interrupt not supported for CID %d Signal %d", eSenderCID, nIdx, 0);
    }

    if ( IPCC_EOK != IPCCOS_RegisterInterrupt( &pClientCtxt->pLegacyDrv->hInterruptHandle,
                                               nInterruptId,
                                               pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].bIslandMode,
                                               IPCCOS_TRIGGER_RISING,
                                               (IPCCOSCB)IPCC_LegacyIsr,
                                               (uintptr_t)ENCODE_ARG(eSenderCID, nIdx) ) )
    {
      /* Log failure in registration */
      IPCCOS_ErrFatal("IPCCLegacy: Could not register interrupt %d for CID %d Signal %d", nInterruptId, eSenderCID, nIdx );
    }
  }

  IPCCLog_Out(3, "IPCCLegacy_RegisterInterrupt successfully registered for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);

  return IPCC_EOK;
}


/* =========================================================================
**  Function : IPCCLegacy_DeregisterInterrupt
** =========================================================================*/

IPCCErr 
IPCCLegacy_DeregisterInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eSenderCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  uint32_t nIdx;
  uint32_t nInterruptId;

  /*-------------------------------------------------------------------------*/

  /* Check arguments */
  if ( pClientCtxt == NULL ||
       pClientCtxt->pLegacyDrv == NULL ||
       pClientCtxt->pLegacyDrv->pLegacyBSP == NULL ||
       eSenderCID >= pClientCtxt->pLegacyDrv->pLegacyBSP->nCount ||
       nSignalLow > nSignalHigh ||
       nSignalHigh >= pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].nCount )
  {
    IPCCLog_Out(3, "IPCCLegacy_DeregisterInterrupt failed (arg) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  /* Check that all requested lines are not in use */
  for ( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
  {
    if ( pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].pLegacyData[nIdx].pfnCb == NULL )
    {
      IPCCLog_Out(3, "IPCCLegacy_DeregisterInterrupt failed (unused) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
      return IPCC_EUNUSED;
    }
  }

  /* Populate State table */
  for ( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
  {
    nInterruptId = pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].pLegacyData[nIdx].nInterruptId;

    if ( IPCC_EOK != IPCCOS_DeregisterInterrupt( &pClientCtxt->pLegacyDrv->hInterruptHandle,
                                                 nInterruptId ) )
    {
      /* Log failure in registration */
      IPCCOS_ErrFatal("IPCCLegacy: Could not register interrupt %d for CID %d Signal %d", nInterruptId, eSenderCID, nIdx );
    }

    /* Populate state table */
    pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].pLegacyData[nIdx].pfnCb = NULL;
    pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].pLegacyData[nIdx].nArg = 0;
  }

  IPCCLog_Out(3, "IPCCLegacy_DeregisterInterrupt successful for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);

  return IPCC_EOK;
}



/* =========================================================================
**  Function : IPCCLegacy_EnableInterrupt
** =========================================================================*/

IPCCErr 
IPCCLegacy_EnableInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eSenderCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  uint32_t nIdx;
  uint32_t nInterruptId;

  /*-------------------------------------------------------------------------*/

  /* Check arguments */
  if ( pClientCtxt == NULL ||
       pClientCtxt->pLegacyDrv == NULL ||
       pClientCtxt->pLegacyDrv->pLegacyBSP == NULL ||
       eSenderCID >= pClientCtxt->pLegacyDrv->pLegacyBSP->nCount ||
       nSignalLow > nSignalHigh ||
       nSignalHigh >= pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].nCount )
  {
    IPCCLog_Out(3, "IPCCLegacy_EnableInterrupt failed (arg) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  /* Check that all requested lines are not in use */
  for ( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
  {
     nInterruptId = pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].pLegacyData[nIdx].nInterruptId;
     /* Check if this line is supported */
     if ( IPCC_INT_NONE == nInterruptId )
     {
       /* For now, error fatal! */
       IPCCOS_ErrFatal("IPCCLegacy: Interrupt not supported for CID %d Signal %d", eSenderCID, nIdx, 0);
     }
     
     if ( IPCC_EOK != IPCCOS_EnableInterrupt( &pClientCtxt->pLegacyDrv->hInterruptHandle,
                                               nInterruptId ) )
     {
       /* Log failure in enable */
       IPCCOS_ErrFatal("IPCCLegacy: Could not enable interrupt %d for CID %d Signal %d", nInterruptId, eSenderCID, nIdx );
     }
  }

  IPCCLog_Out(3, "IPCCLegacy_EnableInterrupt successful for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);

  return IPCC_EOK;
}


/* =========================================================================
**  Function : IPCCLegacy_DisableInterrupt
** =========================================================================*/

IPCCErr 
IPCCLegacy_DisableInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eSenderCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  uint32_t nIdx;
  uint32_t nInterruptId;

  /*-------------------------------------------------------------------------*/

  /* Check arguments */
  if ( pClientCtxt == NULL ||
       pClientCtxt->pLegacyDrv == NULL ||
       pClientCtxt->pLegacyDrv->pLegacyBSP == NULL ||
       eSenderCID >= pClientCtxt->pLegacyDrv->pLegacyBSP->nCount ||
       nSignalLow > nSignalHigh ||
       nSignalHigh >= pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].nCount )
  {
    IPCCLog_Out(3, "IPCCLegacy_DisableInterrupt failed (arg) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  /* Check that all requested lines are not in use */
  for ( nIdx = nSignalLow; nIdx <= nSignalHigh; nIdx++ )
  {
     nInterruptId = pClientCtxt->pLegacyDrv->pLegacyBSP->pLegacyData[eSenderCID].pLegacyData[nIdx].nInterruptId;
     /* Check if this line is supported */
     if ( IPCC_INT_NONE == nInterruptId )
     {
       /* For now, error fatal! */
       IPCCOS_ErrFatal("IPCCLegacy: Interrupt not supported for CID %d Signal %d", eSenderCID, nIdx, 0);
     }
     
     if ( IPCC_EOK != IPCCOS_DisableInterrupt( &pClientCtxt->pLegacyDrv->hInterruptHandle,
                                               nInterruptId ) )
     {
       /* Log failure in disable */
       IPCCOS_ErrFatal("IPCCLegacy: Could not enable interrupt %d for CID %d Signal %d", nInterruptId, eSenderCID, nIdx );
     }
  }

  IPCCLog_Out(3, "IPCCLegacy_DisableInterrupt successful for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);

  return IPCC_EOK;
}


