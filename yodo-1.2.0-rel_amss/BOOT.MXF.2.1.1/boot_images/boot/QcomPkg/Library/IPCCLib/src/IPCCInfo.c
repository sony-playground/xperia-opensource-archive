/*
===========================================================================
*/
/**
  @file IPCCInfo.c

  IPC Controller driver Info portion of the driver.
*/
/*
  ====================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/src/IPCCInfo.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/
#include "IPCC_Info.h"
#include "IPCC_InfoInternal.h"
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

  if (!pClientCtxt->pProtocol->bIPCCModeSupported)
  {
    IPCCLog_Out(
      2, "%s: IPCC mode not supported for protocol %d",
      __func__, pClientCtxt->pProtocol->nProtocolId);
    return IPCC_ENOTSUPPORTED;
  }

  /* Get address */
  nAddr = pClientCtxt->pProtocol->nPhysBaseAddress + pClientCtxt->pProtocol->nOffset;

  /* Mask out lower bits since we only care about minor and major */
  nIPCCVersion = IPCCOS_Read(HWIO_ADDRXI2(pClientCtxt->pProtocol->nVirtBaseAddress, IPC_VERSION, 0, 0))
                  & ~HWIO_FMSK(IPC_VERSION, STEP_VER);

  /* FR61991 - If IPCC_VERSION == v1.2 or >= v1.6, use IPC_SEND16 */
  if ( nIPCCVersion == IPCC_VERSION(1,2) || nIPCCVersion >= IPCC_VERSION(1,6) )
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
