#ifndef __IPCC_RX_H__
#define __IPCC_RX_H__

/*
================================================================================
*/
/**
  @file IPCC_Rx.h

  Header file for the IPCC Rx driver.
*/
/*
  ==============================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ==============================================================================

  $Header: //components/dev/core.boot/6.1/shantonu.core.boot.6.1.ipccHwMemOpt_uefi/QcomPkg/Library/IPCCLib/inc/IPCC_Rx.h#1 $
  $DateTime: 2022/06/08 16:30:11 $
  $Author: shantonu $

  ==============================================================================
*/

/*==============================================================================
  Includes
==============================================================================*/

#include <stdint.h>
#include "IPCC.h"
#include "IPCC_Internal.h"
#include "IPCC_OS.h"


/*==============================================================================
  Macros
==============================================================================*/

/* Value read from HW to indicate there's no more interrupts to process */
#define IPCC_NO_DATA    0xFFFFFFFF


/*==============================================================================
  Prototypes
==============================================================================*/

/* =============================================================================
**  Function : IPCCRx_Init
** ===========================================================================*/
/**
  Initializes the Rx driver.

  @param[in]  pDrv    Pointer to driver context

  @return
  None.

  @dependencies
  Logging must be initialized.
*/

void IPCCRx_Init
(
  IPCCDrvCtxt *pDrv
);

/* =============================================================================
**  Function : IPCCRx_Attach
** ===========================================================================*/
/**
  Attaches the Rx driver to a client handle. If this is the first client attach
  to a protocol, it registers the protocol interrupt with the OS.

  @param[in]  pClientCtxt  Pointer to client context

  @return
  None.

  @dependencies
  None.
*/

void IPCCRx_Attach
(
  IPCCClientCtxt *pClientCtxt
);

/* =============================================================================
**  Function : IPCCRx_Detach
** ===========================================================================*/
/**
  Detaches the Rx driver from a client handle. If this is the first client
  detach from a protocol, it deregisters the protocol interrupt with the OS.

  @param[in]  pClientCtxt  Pointer to client context

  @return
  None.

  @dependencies
  None.
*/

void IPCCRx_Detach
(
  IPCCClientCtxt *pClientCtxt
);

/* =============================================================================
**  Function : IPCCRx_RegisterInterrupt
** ===========================================================================*/
/**
  Registers a user callback for the input signals.

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  pClientBSP   Pointer to the BSP client array
  @param[in]  eCID         IPCC client ID of the source
  @param[in]  nSignalLow   Lowest signal number to listen on
  @param[in]  nSignalHigh  Highest signal number to listen on
  @param[in]  pfnCB        User callback for the signal(s)
  @param[in]  nData        Context to pass to user callback

  @return
  IPCC_EOK -- Successfully registered the user callback.
  IPCC_EARG -- Invalid argument(s) passed by client.
  IPCC_EGENERR -- A requested signal could not be registered with the OS.
  IPCC_EINUSE -- A requested signal is already registered.
  IPCC_ENOTSUPPORTED -- A requested signal is not supported.

  @dependencies
  None.
*/

IPCCErr IPCCRx_RegisterInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCCClientType *pClientBSP,
  IPCC_Client     eCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh,
  IPCC_CB         pfnCB,
  IPCC_CBData     nData
);

/* =============================================================================
**  Function : IPCCRx_DeregisterInterrupt
** ===========================================================================*/
/**
  Deregisters a user callback for the input signals.

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  pClientBSP   Pointer to the BSP client array
  @param[in]  eCID         IPCC client ID of the source
  @param[in]  nSignalLow   Lowest signal number to deregister
  @param[in]  nSignalHigh  Highest signal number to deregister

  @return
  IPCC_EOK -- Successfully registered the user callback.
  IPCC_EARG -- Invalid argument(s) passed by client.
  IPCC_EGENERR -- A requested signal could not be registered with the OS.
  IPCC_EINUSE -- A requested signal is already registered.
  IPCC_ENOTSUPPORTED -- A requested signal is not supported.

  @dependencies
  None.
*/

IPCCErr IPCCRx_DeregisterInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCCClientType *pClientBSP,
  IPCC_Client     eCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh
);

/* =============================================================================
**  Function : IPCCRx_GetConfig
** ===========================================================================*/
/**
  Gets user configuration data for the input signals.

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  pClientBSP   Pointer to the BSP client array
  @param[in]  eCID         IPCC client ID of the source
  @param[in]  nSignalLow   Lowest signal number for getting config
  @param[in]  nSignalHigh  Highest signal number for getting config
  @param[in]  eConfigType  Key of the config to get
  @param[out] pnValue      Pointer to return the config value

  @return
  IPCC_EOK -- Successfully registered the user callback.
  IPCC_EARG -- Invalid argument(s) passed by client.
  IPCC_EGENERR -- A requested signal could not be registered with the OS.
  IPCC_EINUSE -- A requested signal is already registered.
  IPCC_ENOTSUPPORTED -- A requested signal is not supported.

  @dependencies
  None.
*/

IPCCErr IPCCRx_GetConfig
(
  IPCCClientCtxt  *pClientCtxt,
  IPCCClientType  *pClientBSP,
  IPCC_Client      eCID,
  IPCC_Signal      nSignalLow,
  IPCC_Signal      nSignalHigh,
  IPCC_ConfigType  eConfigType,
  uint32_t        *pnValue
);

/* =============================================================================
**  Function : IPCCRx_SetConfig
** ===========================================================================*/
/**
  Sets user configuration data for the input signals.

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  pClientBSP   Pointer to the BSP client array
  @param[in]  eCID         IPCC client ID of the source
  @param[in]  nSignalLow   Lowest signal number for setting config
  @param[in]  nSignalHigh  Highest signal number for setting config
  @param[in]  eConfigType  Key of the config to set
  @param[in]  nValue       Value of the config to set

  @return
  IPCC_EOK -- Successfully registered the user callback.
  IPCC_EARG -- Invalid argument(s) passed by client.
  IPCC_EGENERR -- A requested signal could not be registered with the OS.
  IPCC_EINUSE -- A requested signal is already registered.
  IPCC_ENOTSUPPORTED -- A requested signal is not supported.

  @dependencies
  None.
*/

IPCCErr IPCCRx_SetConfig
(
  IPCCClientCtxt  *pClientCtxt,
  IPCCClientType  *pClientBSP,
  IPCC_Client      eCID,
  IPCC_Signal      nSignalLow,
  IPCC_Signal      nSignalHigh,
  IPCC_ConfigType  eConfigType,
  uint32_t         nValue
);

/* =============================================================================
**  Function : IPCCRx_ToggleInterrupt
** ===========================================================================*/
/**
  Enables or disable the input signal(s) through the OS interrupt controller.

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  pClientBSP   Pointer to the BSP client array
  @param[in]  eCID         IPCC client ID of the source
  @param[in]  nSignalLow   Lowest signal number to toggle
  @param[in]  nSignalHigh  Highest signal number to toggle
  @param[in]  bEnable      Flag to indicate enable/disable request

  @return
  IPCC_EOK -- Successfully toggled the interrupt.
  IPCC_EARG -- Invalid argument(s) passed by client.

  @dependencies
  None.
*/

IPCCErr IPCCRx_ToggleInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCCClientType *pClientBSP,
  IPCC_Client     eCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh,
  bool            bEnable
);

/* =============================================================================
**  Function : IPCCRx_SoftInterrupt
** ===========================================================================*/
/**
  Soft trigger the interrupt by directly invoking the client callback.

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  pClientBSP   Pointer to the BSP client array
  @param[in]  eCID         IPCC client ID of the source
  @param[in]  nSignal      Signal to be soft triggered

  @return
  IPCC_EOK -- Successfully registered the user callback.
  IPCC_EARG -- Invalid argument(s) passed by client.
  IPCC_EGENERR -- A requested signal could not be registered with the OS.
  IPCC_EINUSE -- A requested signal is already registered.
  IPCC_ENOTSUPPORTED -- A requested signal is not supported.

  @dependencies
  None.
*/

IPCCErr IPCCRx_SoftInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCCClientType *pClientBSP,
  IPCC_Client     eCID,
  IPCC_Signal     nSignal
);

/* =============================================================================
**  Function : IPCC_RxIsr
** ===========================================================================*/
/**
  Intermediate ISR function to invoke the client callback. This ISR is
  registered with the OS.

  @param[in]  pCtxt  ISR context

  @return
  None.

  @dependencies
  None.
*/

void IPCC_RxIsr
(
  uintptr_t pCtxt
);

#endif /* __IPCC_RX_H__ */
