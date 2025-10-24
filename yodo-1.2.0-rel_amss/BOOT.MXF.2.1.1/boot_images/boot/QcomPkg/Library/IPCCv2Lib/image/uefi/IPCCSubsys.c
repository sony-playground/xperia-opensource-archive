/*
================================================================================
*/
/**
  @file IPCCSubsys.c

  This module implements the image-specific sub-driver for the UEFI IPCC driver.
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

#include "HALhwio.h"
#include "IPCC_Image.h"
#include "IPCCHWIO.h"


/*==============================================================================
  Functions
==============================================================================*/

/* =============================================================================
**  Function : IPCC_InitSubsysImage
** ===========================================================================*/
/**
  See IPCC_Image.h
*/

void IPCC_InitSubsysImage
(
  IPCCDrvCtxt *pDrv
)
{
  IPCCErr           nErr;
  IPCCProtocolType *pProtocol;
  uint32_t          nIdx, nClientIdx;

  if ((NULL == pDrv) || (NULL == pDrv->pBSP))
  {
    return;
  }

  for (nIdx = 0; nIdx < pDrv->pBSP->nNumProtocols; nIdx++)
  {
    pProtocol = &pDrv->pBSP->pProtocols[nIdx];
    if (0 != pProtocol->nPhysBaseAddress)
    {
      pProtocol->nVirtBaseAddress = pProtocol->nPhysBaseAddress;

      /* Add client and protocol offset */
      nErr = IPCCInternal_FindPhysClientIdx(
               pDrv->pBSP->eClient, pProtocol, &nClientIdx);
      if (IPCC_EOK != nErr)
      {
        IPCCOS_ErrFatal(
          "Could not get physical client idx (err: %d)", nErr, 0, 0);
      }

      pProtocol->nVirtBaseAddress +=
        (nClientIdx *
          (HWIO_ADDRXI2(0, IPC_ID, 0, 1) - HWIO_ADDRXI2(0, IPC_ID, 0, 0)));

      pProtocol->nVirtBaseAddress +=
        (pProtocol->nProtocolId *
          (HWIO_ADDRXI2(0, IPC_ID, 1, 0) - HWIO_ADDRXI2(0, IPC_ID, 0, 0)));
    }
  }
}

#ifdef IPCC_SUPPORT_LEGACY_MODE
/* =============================================================================
**  Function : IPCCLegacy_InitSubsysImage
** ===========================================================================*/
/**
  See IPCC_Image.h
*/

void IPCCLegacy_InitSubsysImage
(
  IPCCLegacyDrvCtxt *pLegacyDrv
)
{
  return;
}
#endif
