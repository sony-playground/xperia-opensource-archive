/*
===========================================================================
*/
/**
  @file IPCC.c

  Interface implementation file for the IPC Controller driver.
*/
/*
  ====================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/src/IPCCIsland.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/
#include "IPCC.h"
#include "IPCC_Internal.h"
#include "IPCC_Rx.h"
#include "IPCC_Tx.h"
#include "IPCC_Legacy.h"
#include "IPCC_Image.h"
#include "IPCC_Log.h"
#include "IPCC_Info.h"
#include "IPCC_InfoInternal.h"
#include <stdlib.h>
#include <string.h>


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : IPCC_Trigger
** =========================================================================*/

IPCCErr
IPCC_Trigger
(
  IPCC_Handle       h,
  IPCC_Client       eTargetCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  IPCCClientCtxt* pClientCtxt = (IPCCClientCtxt*)h;

  /*-------------------------------------------------------------------------*/

  /* Check argument(s) */
  if ( ( pClientCtxt == NULL                                ) ||
       ( eTargetCID >= pClientCtxt->pProtocol->nNumClients  ) ) 
  {
    IPCCLog_Out(3, "IPCC_Trigger failed (arg) for eTargetCID %d, nSignalLow %d, nSignalHigh %d", eTargetCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  if ( ( pClientCtxt->pProtocol->bLegacySupported ) && 
       ( pClientCtxt->pProtocol->pClients[eTargetCID].bUseLegacyByDefault ) )
  {
    return IPCCLegacy_Trigger(pClientCtxt, 
                              eTargetCID, 
                              nSignalLow,
                              nSignalHigh);
  }
  else if ( pClientCtxt->pProtocol->bIPCCModeSupported )
  {
    /* We should exit island mode here to access IPCC */
    return IPCCTx_Trigger(pClientCtxt, 
                          eTargetCID, 
                          nSignalLow,
                          nSignalHigh);
  }
  else
  {
    IPCCLog_Out(3, "IPCC_Trigger failed (not supported) for eTargetCID %d, nSignalLow %d, nSignalHigh %d", eTargetCID, nSignalLow, nSignalHigh);
    return IPCC_ENOTSUPPORTED;
  }
}
