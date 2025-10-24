/*
===========================================================================
*/
/**
  @file IPCC.c

  Interface implementation file for the IPC Controller driver.
*/
/*
  ====================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/src/IPCC.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
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
#include "IPCC_Info.h"
#include "IPCC_InfoInternal.h"


/*=========================================================================
      Static definitions
==========================================================================*/

static IPCCDrvCtxt IPCCDrv;

/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : IPCC_Init
** =========================================================================*/
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

void
IPCC_Init
(
  void
)
{

  /*-------------------------------------------------------------------------*/
  /* Initialize Log */
  IPCCLog_Init();

  /* Initialize BSP data */
  IPCC_InitImage(&IPCCDrv);

  /* Initialize Rx Driver */
  IPCCRx_Init(&IPCCDrv);

  /* Initialize Rx Driver */
  IPCCTx_Init(&IPCCDrv);

  /* Initialize Legacy Driver */
  IPCCLegacy_Init();

  /* Initialize Info portion of the driver */
  IPCCInfo_Init(&IPCCDrv);
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
  if ((NULL         == pH)         ||
      (IPCC_P_TOTAL <= eProtocol))
  {
    IPCCLog_Out(2, "%s: Failed (arg) for protocol %d", __func__, eProtocol);
    return IPCC_EARG;
  }

  /* Make sure driver is initialized */
  if (IPCCDrv.pBSP)
  {
    /* Check if this protocol is supported */
    if (0 == IPCCDrv.pBSP->pProtocols[eProtocol].bIsSupported)
    {
      IPCCLog_Out(
        2, "%s: Failed, protocol %d not supported", __func__, eProtocol);
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
      if (pClientCtxt->pProtocol->bLegacySupported)
      {
        IPCCLegacy_Attach(pClientCtxt);
      }

      /* Attach to the Rx driver */
      if (pClientCtxt->pProtocol->bIPCCModeSupported)
      {
        IPCCRx_Attach(pClientCtxt);
      }

      /* Set client pointer */
      *pH = (IPCC_Handle)pClientCtxt;

      return IPCC_EOK;
    }

    return IPCC_EMEM;
  }

  /* IPCC is not yet initialized */
  return IPCC_EGENERR;
}


/* =========================================================================
**  Function : IPCC_Detach
** =========================================================================*/

IPCCErr
IPCC_Detach
(
  IPCC_Handle *pH
)
{
  IPCCClientCtxt* pClientCtxt;

  /*-------------------------------------------------------------------------*/

  /* Check argument(s) */
  if ( pH == NULL ) return IPCC_EARG;

  /* Get client context */
  pClientCtxt = (IPCCClientCtxt *)*pH;

  /* Attach to legacy driver if supported */
  if ( pClientCtxt->pProtocol &&
       pClientCtxt->pProtocol->bLegacySupported )
  {
    IPCCLegacy_Detach( pClientCtxt );
  }

  /* Clean up client context */
  pClientCtxt->pProtocol = NULL;

  /* Free up the memory */
  IPCCOS_Free(pClientCtxt);

  /* Clear pointer */
  *pH = NULL;

  /* Return success */
  return IPCC_EOK;
}


/* =========================================================================
**  Function : IPCC_RegisterInterrupt
** =========================================================================*/

IPCCErr 
IPCC_RegisterInterrupt
(
  IPCC_Handle       h,
  IPCC_Client       eSenderCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_CB           pfnCB,
  IPCC_CBData       nData
)
{
  IPCCClientCtxt* pClientCtxt = (IPCCClientCtxt*)h;

  /*-------------------------------------------------------------------------*/

  /* Check argument(s) */
  if ( ( pClientCtxt == NULL                                ) ||
       ( pfnCB == NULL                                      ) ||
       ( nSignalLow > nSignalHigh                           ) || 
       ( eSenderCID >= pClientCtxt->pProtocol->nNumClients  )  ) 
  {
    IPCCLog_Out(3, "IPCC_RegisterInterrupt failed (arg) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  if ( ( pClientCtxt->pProtocol->bLegacySupported ) && 
       ( pClientCtxt->pProtocol->pClients[eSenderCID].bUseLegacyByDefault  ) )
  {
    return IPCCLegacy_RegisterInterrupt(pClientCtxt, 
                                        eSenderCID, 
                                        nSignalLow, 
                                        nSignalHigh, 
                                        pfnCB, 
                                        nData);
  }
  else if ( pClientCtxt->pProtocol->bIPCCModeSupported )
  {
    return IPCCRx_RegisterInterrupt(pClientCtxt, 
                                    eSenderCID, 
                                    nSignalLow, 
                                    nSignalHigh, 
                                    pfnCB, 
                                    nData);
  }
  else
  {
    IPCCLog_Out(3, "IPCC_RegisterInterrupt failed (not supported) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_ENOTSUPPORTED;
  }
}


/* =========================================================================
**  Function : IPCC_DeregisterInterrupt
** =========================================================================*/

IPCCErr 
IPCC_DeregisterInterrupt
(
  IPCC_Handle       h,
  IPCC_Client       eSenderCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  IPCCClientCtxt* pClientCtxt = (IPCCClientCtxt*)h;

  /*-------------------------------------------------------------------------*/

  /* Check argument(s) */
  if ( ( pClientCtxt == NULL                                ) ||
       ( nSignalLow > nSignalHigh                           ) || 
       ( eSenderCID >= pClientCtxt->pProtocol->nNumClients  )  ) 
  {
    IPCCLog_Out(3, "IPCC_DeregisterInterrupt failed (arg) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  if ( ( pClientCtxt->pProtocol->bLegacySupported ) && 
       ( pClientCtxt->pProtocol->pClients[eSenderCID].bUseLegacyByDefault ) )
  {
    return IPCCLegacy_DeregisterInterrupt(pClientCtxt, 
                                          eSenderCID, 
                                          nSignalLow, 
                                          nSignalHigh);
  }
  else if ( pClientCtxt->pProtocol->bIPCCModeSupported  )
  {
    return IPCCRx_DeregisterInterrupt(pClientCtxt, 
                                      eSenderCID, 
                                      nSignalLow, 
                                      nSignalHigh);
  }
  else
  {
    IPCCLog_Out(3, "IPCC_DeregisterInterrupt failed (not supported) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_ENOTSUPPORTED;
  }
}


/* =========================================================================
**  Function : IPCC_EnableInterrupt
** =========================================================================*/

IPCCErr 
IPCC_EnableInterrupt
(
  IPCC_Handle       h,
  IPCC_Client       eSenderCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  IPCCClientCtxt* pClientCtxt = (IPCCClientCtxt*)h;

  /*-------------------------------------------------------------------------*/

  /* Check argument(s) */
  if ( ( pClientCtxt == NULL                                ) ||
       ( nSignalLow > nSignalHigh                           ) || 
       ( eSenderCID >= pClientCtxt->pProtocol->nNumClients  )  ) 
  {
    IPCCLog_Out(3, "IPCC_EnableInterrupt failed (arg) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  if ( ( pClientCtxt->pProtocol->bLegacySupported ) && 
       ( pClientCtxt->pProtocol->pClients[eSenderCID].bUseLegacyByDefault  ) )
  {
    return IPCCLegacy_EnableInterrupt(pClientCtxt, 
                                          eSenderCID, 
                                          nSignalLow, 
                                          nSignalHigh);
  }
  else if ( pClientCtxt->pProtocol->bIPCCModeSupported  )
  {
    return IPCCRx_EnableInterrupt(pClientCtxt, 
                                      eSenderCID, 
                                      nSignalLow, 
                                      nSignalHigh);
  }
  else
  {
    IPCCLog_Out(3, "IPCC_EnableInterrupt failed (not supported) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_ENOTSUPPORTED;
  }
}


/* =========================================================================
**  Function : IPCC_DisableInterrupt
** =========================================================================*/

IPCCErr 
IPCC_DisableInterrupt
(
  IPCC_Handle       h,
  IPCC_Client       eSenderCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
)
{
  IPCCClientCtxt* pClientCtxt = (IPCCClientCtxt*)h;

  /*-------------------------------------------------------------------------*/

  /* Check argument(s) */
  if ( ( pClientCtxt == NULL                                ) ||
       ( nSignalLow > nSignalHigh                           ) || 
       ( eSenderCID >= pClientCtxt->pProtocol->nNumClients  )  ) 
  {
    IPCCLog_Out(3, "IPCC_DisableInterrupt failed (arg) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_EARG;
  }

  if ( ( pClientCtxt->pProtocol->bLegacySupported ) && 
       ( pClientCtxt->pProtocol->pClients[eSenderCID].bUseLegacyByDefault  ) )
  {
    return IPCCLegacy_DisableInterrupt(pClientCtxt, 
                                          eSenderCID, 
                                          nSignalLow, 
                                          nSignalHigh);
  }
  else if ( pClientCtxt->pProtocol->bIPCCModeSupported  )
  {
    return IPCCRx_DisableInterrupt(pClientCtxt, 
                                      eSenderCID, 
                                      nSignalLow, 
                                      nSignalHigh);
  }
  else
  {
    IPCCLog_Out(3, "IPCC_DisableInterrupt failed (not supported) for eSenderCID %d, nSignalLow %d, nSignalHigh %d", eSenderCID, nSignalLow, nSignalHigh);
    return IPCC_ENOTSUPPORTED;
  }
}



/* =========================================================================
**  Function : IPCC_GetConfig
** =========================================================================*/

IPCCErr 
IPCC_GetConfig
(
  IPCC_Handle       h,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_ConfigType   eConfigType,
  uint32_t*         pnValue
)
{
  IPCCClientCtxt* pClientCtxt = (IPCCClientCtxt*)h;

  /*-------------------------------------------------------------------------*/

  /* Check argument(s) */
  if ( ( pClientCtxt == NULL                                ) ||
       ( pnValue == NULL                                    ) ||
       ( nSignalLow > nSignalHigh                           ) || 
       ( eCID >= pClientCtxt->pProtocol->nNumClients        )  ) 
  {
    IPCCLog_Out(4, "IPCC_GetConfig failed (arg) for eCID %d, nSignalLow %d, nSignalHigh %d, eConfigType %d", eCID, nSignalLow, nSignalHigh, eConfigType);
    return IPCC_EARG;
  }

  if ( pClientCtxt->pProtocol->bIPCCModeSupported )
  {
    return IPCCRx_GetConfig(pClientCtxt, 
                            eCID, 
                            nSignalLow, 
                            nSignalHigh, 
                            eConfigType, 
                            pnValue);
  }
  else
  {
    IPCCLog_Out(4, "IPCC_GetConfig failed (not supported) for eCID %d, nSignalLow %d, nSignalHigh %d, eConfigType %d", eCID, nSignalLow, nSignalHigh, eConfigType);
    return IPCC_ENOTSUPPORTED;
  }
}


/* =========================================================================
**  Function : IPCC_SetConfig
** =========================================================================*/

IPCCErr 
IPCC_SetConfig
(
  IPCC_Handle       h,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_ConfigType   eConfigType,
  uint32_t          nValue
)
{
  IPCCClientCtxt* pClientCtxt = (IPCCClientCtxt*)h;

  /*-------------------------------------------------------------------------*/

  /* Check argument(s) */
  if ( ( pClientCtxt == NULL                                ) ||
       ( nSignalLow > nSignalHigh                           ) || 
       ( eCID >= pClientCtxt->pProtocol->nNumClients        )  ) 
  {
    IPCCLog_Out(4, "IPCC_SetConfig failed (arg) for eCID %d, nSignalLow %d, nSignalHigh %d, eConfigType %d", eCID, nSignalLow, nSignalHigh, eConfigType);
    return IPCC_EARG;
  }

  if ( pClientCtxt->pProtocol->bIPCCModeSupported )
  {
    return IPCCRx_SetConfig(pClientCtxt, 
                            eCID, 
                            nSignalLow, 
                            nSignalHigh, 
                            eConfigType, 
                            nValue);
  }
  else
  {
    IPCCLog_Out(4, "IPCC_SetConfig failed (not supported) for eCID %d, nSignalLow %d, nSignalHigh %d, eConfigType %d", eCID, nSignalLow, nSignalHigh, eConfigType);
    return IPCC_ENOTSUPPORTED;
  }
}
