#ifndef __IPCC_LEGACY_H__
#define __IPCC_LEGACY_H__

/*
================================================================================
*/
/**
  @file IPCC_Legacy.h

  Header file for the IPCC legacy driver.
*/
/*
  ==============================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ==============================================================================

  $Header: //components/dev/core.boot/6.1/shantonu.core.boot.6.1.ipccHwMemOpt_uefi/QcomPkg/Library/IPCCLib/inc/IPCC_Legacy.h#1 $
  $DateTime: 2022/06/08 16:30:11 $
  $Author: shantonu $

  ==============================================================================
*/

/*==============================================================================
  Includes
==============================================================================*/

#include "IPCC_Internal.h"


/*==============================================================================
  Macros
==============================================================================*/

/*
 * Macros to encode and decode client and signal IDs in the intermediate ISR
 * context.
 */
#define CID_SHIFT   16
#define SIG_SHIFT   0
#define CID_MASK    0xFFFF
#define SIG_MASK    0xFFFF

#define DECODE_CID(x) ((x >> CID_SHIFT) & CID_MASK)
#define DECODE_SIG(x) ((x >> SIG_SHIFT) & SIG_MASK)

#define ENCODE_ARG(c, s) (((s & SIG_MASK) << SIG_SHIFT) | \
                          ((c & CID_MASK) << CID_SHIFT))


/*==============================================================================
  Prototypes
==============================================================================*/

/* =============================================================================
**  Function : IPCCLegacy_Init
** ===========================================================================*/
/**
  Initializes the legacy driver.

  @param
  None.

  @return
  None.

  @dependencies
  None.
*/

void IPCCLegacy_Init
(
  void
);

/* =============================================================================
**  Function : IPCCLegacy_Attach
** ===========================================================================*/
/**
  Attaches the legacy driver to a client handle.

  @param[in]  pClientCtxt  Pointer to client context

  @return
  None.

  @dependencies
  None.
*/

void IPCCLegacy_Attach
(
  IPCCClientCtxt *pClientCtxt
);

/* =============================================================================
**  Function : IPCCLegacy_Detach
** ===========================================================================*/
/**
  Detaches the legacy driver from a client handle.

  @param[in]  pClientCtxt  Pointer to client context

  @return
  None.

  @dependencies
  None.
*/

void IPCCLegacy_Detach
(
  IPCCClientCtxt *pClientCtxt
);

/* =============================================================================
**  Function : IPCCLegacy_RegisterInterrupt
** ===========================================================================*/
/**
  Registers a user callback for the input legacy interrupts.

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  eSenderCID   IPCC client ID of the source
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

IPCCErr IPCCLegacy_RegisterInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCC_Client     eSenderCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh,
  IPCC_CB         pfnCB,
  IPCC_CBData     nData
);

/* =============================================================================
**  Function : IPCCLegacy_DeregisterInterrupt
** ===========================================================================*/
/**
  Deregisters a user callback for the input legacy interrupts.

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  eSenderCID   IPCC client ID of the source
  @param[in]  nSignalLow   Lowest signal number to deregister
  @param[in]  nSignalHigh  Highest signal number to deregister

  @return
  IPCC_EOK -- Successfully deregistered the user callback.
  IPCC_EARG -- Invalid argument(s) passed by client.
  IPCC_EGENERR -- A requested signal could not be deregistered with the OS.
  IPCC_EUNUSED -- A requested signal is not registered.

  @dependencies
  None.
*/

IPCCErr IPCCLegacy_DeregisterInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCC_Client     eSenderCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh
);

/* =============================================================================
**  Function : IPCCLegacy_Trigger
** ===========================================================================*/
/**
  Triggers legacy interrupt(s) to the target client.

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  eTargetCID   IPCC client ID of the source or target
  @param[in]  nSignalLow   Lowest signal number to trigger
  @param[in]  nSignalHigh  Highest signal number to trigger

  @return
  IPCC_EOK -- Successfully triggered requested signals.
  IPCC_EARG -- Invalid argument(s) passed by client.

  @dependencies
  None.
*/

IPCCErr IPCCLegacy_Trigger
(
  IPCCClientCtxt *pClientCtxt,
  IPCC_Client     eTargetCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh
);

/* =============================================================================
**  Function : IPCCLegacy_GetConfig
** ===========================================================================*/
/**
  Sets user configuration data for legacy interrupts.

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  eCID         IPCC client ID of the source or target
  @param[in]  nSignalLow   Lowest signal number for getting config
  @param[in]  nSignalHigh  Highest signal number for getting config
  @param[in]  eConfigType  Key of the config to get
  @param[out] pnValue      Pointer to returh the config value

  @return
  IPCC_EOK -- Successfully set the config value.
  IPCC_EARG -- Invalid argument(s) passed by client.
  IPCC_ENOTSUPPORTED -- Config type is not suppported.

  @dependencies
  None.
*/

IPCCErr IPCCLegacy_GetConfig
(
  IPCCClientCtxt  *pClientCtxt,
  IPCC_Client      eCID,
  IPCC_Signal      nSignalLow,
  IPCC_Signal      nSignalHigh,
  IPCC_ConfigType  eConfigType,
  uint32_t        *pnValue
);

/* =============================================================================
**  Function : IPCCLegacy_SetConfig
** ===========================================================================*/
/**
  Sets user configuration data for legacy interrupts.

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  eCID         IPCC client ID of the source or target
  @param[in]  nSignalLow   Lowest signal number for setting config
  @param[in]  nSignalHigh  Highest signal number for setting config
  @param[in]  eConfigType  Key of the config to set
  @param[in]  nValue       Value of the config to set

  @return
  IPCC_EOK -- Successfully set the config value.
  IPCC_EARG -- Invalid argument(s) passed by client.
  IPCC_ENOTSUPPORTED -- Config type is not suppported.

  @dependencies
  None.
*/

IPCCErr IPCCLegacy_SetConfig
(
  IPCCClientCtxt  *pClientCtxt,
  IPCC_Client      eCID,
  IPCC_Signal      nSignalLow,
  IPCC_Signal      nSignalHigh,
  IPCC_ConfigType  eConfigType,
  uint32_t         nValue
);

/* =============================================================================
**  Function : IPCCLegacy_ToggleInterrupt
** ===========================================================================*/
/**
  Enables or disable the input interrupt(s) through the OS interrupt controller.

  @param[in]  pClientCtxt  Pointer to client context
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

IPCCErr IPCCLegacy_ToggleInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCC_Client     eCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh,
  bool            bEnable
);

/* =============================================================================
**  Function : IPCC_LegacyIsr
** ===========================================================================*/
/**
  Intermediate legacy ISR function to invoke the client callback. This ISR is
  registered with the OS.

  @param[in]  pCtxt  ISR context

  @return
  None.

  @dependencies
  None.
*/

void IPCC_LegacyIsr
(
  uintptr_t pCtxt
);

#endif /* __IPCC_LEGACY_H__ */
