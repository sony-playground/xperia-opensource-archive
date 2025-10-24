/*
===========================================================================
*/
/**
  @file IPCCInfo.c

  IPC Controller driver Info portion of the driver.
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

#include "IPCC_InfoInternal.h"
#ifdef IPCC_SUPPORT_INFO
#include "IPCC_Internal.h"
#include "IPCCHWIO.h"
#include "IPCC_Log.h"

/*=========================================================================
      Static defiintions
==========================================================================*/

IPCC_Client nIPCCInfoLocalClient;


#define IPCC_VERSION(ma,mi) ( (ma) << HWIO_IPC_VERSION_MAJOR_VER_SHFT | \
                              (mi) << HWIO_IPC_VERSION_MINOR_VER_SHFT )

/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : IPCCInfo_Init
** =========================================================================*/

IPCCErr
IPCCInfo_Init
(
   IPCCDrvCtxt* pDrv
)
{
  /*-------------------------------------------------------------------------*/

  /* Apply Tx Drv to Master Drv */
  if ( pDrv != NULL )
  {
    nIPCCInfoLocalClient = pDrv->pBSP->eClient;
  }

  IPCCLog_Out(0, "IPCCInfo Initialized");

  return IPCC_EOK;
}


/* =========================================================================
**  Function : IPCC_GetTriggerAddressAndData
** =========================================================================*/

IPCCErr
IPCC_GetTriggerAddressAndData
(
   IPCC_Handle   h,
   IPCC_Client   eSenderCID,
   IPCC_Signal   nSignal,
   uintptr_t    *pa,
   uint32_t     *nData
)
{
  IPCCClientCtxt* pClientCtxt = (IPCCClientCtxt*)h;
  uintptr_t nAddr;
  uint32_t nIPCCVersion;

  /*-------------------------------------------------------------------------*/

  if( pClientCtxt == NULL ||
      pClientCtxt->pProtocol == NULL ||
      eSenderCID >= pClientCtxt->pProtocol->nNumClients ||
      nSignal >= pClientCtxt->pProtocol->nNumSigs ||
      pa == NULL ||
      nData == NULL )
  {
    IPCCLog_Out(
      3, "%s failed (arg) for eCID %d, nSignal %d",
      __func__, eSenderCID, nSignal);
    return IPCC_EARG;
  }

  #ifdef IPCC_SUPPORT_LEGACY_MODE
  if (!pClientCtxt->pProtocol->bIPCCModeSupported)
  {
    IPCCLog_Out(
      2, "%s: IPCC mode not supported for protocol %d",
      __func__, pClientCtxt->pProtocol->nProtocolId);
    return IPCC_ENOTSUPPORTED;
  }
  #endif

  /* Get address */
  nAddr = pClientCtxt->pProtocol->nPhysBaseAddress +
            (pClientCtxt->pProtocol->nProtocolId *
              (HWIO_ADDRXI2(0, IPC_ID, 1, 0) - HWIO_ADDRXI2(0, IPC_ID, 0, 0)));

  /* Mask out lower bits since we only care about minor and major */
  nIPCCVersion = IPCCOS_Read(HWIO_ADDRXI2(pClientCtxt->pProtocol->nVirtBaseAddress, IPC_VERSION, 0, 0))
                  & ~HWIO_FMSK(IPC_VERSION, STEP_VER);

  /* FR61991 - If IPCC_VERSION == v1.2 or >= v1.5, use IPC_SEND16 */
  if ( nIPCCVersion == IPCC_VERSION(1,2) || nIPCCVersion >= IPCC_VERSION(1,5) )
  {
    *pa = (uintptr_t)HWIO_ADDRXI2(nAddr, IPC_SEND16, 0, eSenderCID);
    *nData = ( nIPCCInfoLocalClient << HWIO_SHFT(IPC_SEND16, CLIENT_ID) ) | nSignal;
  }
  else
  {
    *pa = (uintptr_t)HWIO_ADDRXI2(nAddr, IPC_SEND, 0, eSenderCID);
    *nData = ( nIPCCInfoLocalClient << HWIO_SHFT(IPC_SEND, CLIENT_ID) ) | nSignal;
  }

  return IPCC_EOK;
}
#endif /* IPCC_SUPPORT_INFO */