#ifndef __IPCC_H__
#define __IPCC_H__

/*
================================================================================
*/
/**
  @file IPCC.h
  @brief Public interface include file for accessing the IPCC device driver.

  The IPCC.h file is the public API interface to the Inter-Processor 
  Communication Controller driver.
*/
/*
  ==============================================================================

  Copyright (c) 2018-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ==============================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/IPCC.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ==============================================================================
*/


/*==============================================================================
  Includes
==============================================================================*/

#include <IPCCDefs.h>


#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
  Interface declarations
==============================================================================*/

/** @addtogroup ipcc_functions
@{ */

/* =============================================================================
**  Function : IPCC_Attach
** ===========================================================================*/
/**
  Attaches given handle to IPCC driver and protocol.

  This function takes a reference to a user handle and protocol enumeration.
  This function must be called before calling any other IPCC API in order to
  notify the IPCC driver of the requirement to use the protocol requested.

  @param pH        [out] Reference to a client handle.
  @param eProtocol [in]  IPCC protocol requested to use.

  @return
  IPCC_EOK -- Successfully attached to protocol eProtocol. \n
  IPCC_EGENERR -- IPCC not yet initialized. \n
  IPCC_EMEM -- Insufficient memory available for client handle reference. \n
  IPCC_ENOTSUPPORTED -- Protocol requested is not supported. \n
  IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Driver must be initialized.
*/

IPCCErr IPCC_Attach
(
  IPCC_Handle   *pH,
  IPCC_Protocol  eProtocol
);

/* =============================================================================
**  Function : IPCC_Detach
** ===========================================================================*/
/**
  Detaches the given handle from IPCC driver.

  This function takes a reference to a user handle and detaches it from the
  driver. It should only be used if there is no requirement for this handle
  at the point it's called.

  @param pH        [out] Reference to a client handle.

  @return
  IPCC_EOK -- Successfully detached client handle. \n
  IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/

IPCCErr IPCC_Detach
(
  IPCC_Handle *pH
);

/* =============================================================================
**  Function : IPCC_RegisterInterrupt
** ===========================================================================*/
/**
  Registers a callback function for when signals are received from a given
  sender.

  This function is used to register a notification with the IPCC driver.
  The callback function pfnCB is called whenever the sender eSenderCID
  signals the processor running this SW with any of the signals in the
  range nSignalLow to nSignalHigh. If only one signal is being registered,
  then nSignalLow should be the same as nSignalHigh. If any of the signals
  are in use, then the API will fail and none of the requested signals will
  be registered.

  @param h           [in] Client handle.
  @param eSenderCID  [in] Client ID of the sender.
  @param nSignalLow  [in] Lowest signal number to listen on.
  @param nSignalHigh [in] Highest signal number to listen on.
  @param pfnCB       [in] Callback function for when signal is received.
  @param nData       [in] Data to pass into callback function when signal
                          is received.

  @return
  IPCC_EOK -- Successfully registered the signals for eSenderCID. \n
  IPCC_EARG -- Unsupported argument passed in by client. \n
  IPCC_EINUSE -- One or more of the requested signals are in use.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/

IPCCErr IPCC_RegisterInterrupt
(
  IPCC_Handle       h,
  IPCC_Client       eSenderCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_CB           pfnCB,
  IPCC_CBData       nData
);

/* =============================================================================
**  Function : IPCC_DeregisterInterrupt
** ===========================================================================*/
/**
  Deregisters a previously registered callback function for signals
  received from a given sender.

  This function is used to deregister a notification from the IPCC driver.
  This will remove all future notificatoins of the previously registered
  callback function from happening. If only one signal is being deregistered,
  then nSignalLow should be the same as nSignalHigh. If any of the signals
  are not in use, then the API will fail and none of the requested signals will
  be deregistered.

  @param h           [in] Client handle.
  @param eSenderCID  [in] Client ID of the sender.
  @param nSignalLow  [in] Lowest signal number to deregister.
  @param nSignalHigh [in] Highest signal number to deregister.

  @return
  IPCC_EOK -- Successfully deregistered the signals for eSenderCID. \n
  IPCC_EARG -- Unsupported argument passed in by client. \n
  IPCC_EUNUSED -- One or more of the requested signals are not in use.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/

IPCCErr IPCC_DeregisterInterrupt
(
  IPCC_Handle       h,
  IPCC_Client       eSenderCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);

/* =============================================================================
**  Function : IPCC_Trigger
** ===========================================================================*/
/**
  Triggers interrupts on remote clients.

  This function is used to assert the signals in the range nSignalLow to
  nSignalHigh on target eTargetCID.

  @param h           [in] Client handle.
  @param eTargetCID  [in] Client ID of the target.
  @param nSignalLow  [in] Lowest signal number to assert.
  @param nSignalHigh [in] Highest signal number to assert.

  @return
  IPCC_EOK -- Successfully trigger the signals to eTargetCID. \n
  IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/

IPCCErr IPCC_Trigger
(
  IPCC_Handle       h,
  IPCC_Client       eTargetCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);

/* =========================================================================
**  Function : IPCC_GetConfig
** =========================================================================*/
/**
  Gets config data associated with (a) given signal(s).

  @param h           [in]  Client handle.
  @param eCID        [in]  Client ID of the source or target.
  @param nSignalLow  [in]  Lowest signal number for config.
  @param nSignalHigh [in]  Highest signal number for config.
  @param eConfigType [in]  Key of the config to get
  @param pnValue     [out] Value of the config requested

  @return
  IPCC_EOK -- Successfully retrieved the config value. \n
  IPCC_EARG -- Unsupported argument passed in by client.
  IPCC_ENOTFOUND -- Cannot find config.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/

IPCCErr IPCC_GetConfig
(
  IPCC_Handle      h,
  IPCC_Client      eCID,
  IPCC_Signal      nSignalLow,
  IPCC_Signal      nSignalHigh,
  IPCC_ConfigType  eConfigType,
  uint32_t        *pnValue
);

/* =============================================================================
**  Function : IPCC_SetConfig
** ===========================================================================*/
/**
  Sets config data associated with (a) given signal(s).

  @param h           [in]  Client handle.
  @param eCID        [in]  Client ID of the source or target.
  @param nSignalLow  [in]  Lowest signal number for config.
  @param nSignalHigh [in]  Highest signal number for config.
  @param eConfigType [in]  Key of the config to get
  @param nValue      [in]  Value of the config to set

  @return
  IPCC_EOK -- Successfully retrieved the config value. \n
  IPCC_EARG -- Unsupported argument passed in by client.
  IPCC_ENOTFOUND -- Cannot find config.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/

IPCCErr IPCC_SetConfig
(
  IPCC_Handle     h,
  IPCC_Client     eCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh,
  IPCC_ConfigType eConfigType,
  uint32_t        nValue
);

/* =============================================================================
**  Function : IPCC_EnableInterrupt
** ===========================================================================*/
/**
  Enable interrupts from sender.

  This function will enable the RECV signal lines in the range nSignalLow to
  nSignalHigh from sender eSenderCID.

  @param h           [in] Client handle.
  @param eSenderCID  [in] Client ID of the sender.
  @param nSignalLow  [in] Lowest signal number to enable.
  @param nSignalHigh [in] Highest signal number to enable.

  @return
  IPCC_EOK -- Successfully enabled the signals from eSenderCID. \n
  IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/
IPCCErr IPCC_EnableInterrupt
(
  IPCC_Handle       h,
  IPCC_Client       eSenderCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);

/* =============================================================================
**  Function : IPCC_DisableInterrupt
** ===========================================================================*/
/**
  Disable interrupts from sender.

  This function will disable the RECV signal lines in the range nSignalLow to
  nSignalHigh from sender eSenderCID.

  @param h           [in] Client handle.
  @param eSenderCID  [in] Client ID of the sender.
  @param nSignalLow  [in] Lowest signal number to disable.
  @param nSignalHigh [in] Highest signal number to disable.

  @return
  IPCC_EOK -- Successfully disabled the signals from eSenderCID. \n
  IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/
IPCCErr IPCC_DisableInterrupt
(
  IPCC_Handle       h,
  IPCC_Client       eSenderCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);

/* =============================================================================
**  Function : IPCC_SoftInterrupt
** ===========================================================================*/
/**
  This function is used to simulate software interrupts from sender CID.

  @param h           [in] Client handle.
  @param eTargetCID  [in] Client ID of the sender.
  @param nSignal     [in] Signal number to assert.

  @return
  IPCC_EOK -- Successfully trigger the signals to eTargetCID. \n
  IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/
IPCCErr IPCC_SoftInterrupt
(
  IPCC_Handle       h,
  IPCC_Client       eSenderCID,
  IPCC_Signal       nSignal
);

/** @} */ /* end_addtogroup ipcc_functions */

#ifdef __cplusplus
}
#endif

#endif /* __IPCC_H__ */
