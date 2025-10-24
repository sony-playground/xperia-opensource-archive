#ifndef EFIIPCC_H
#define EFIIPCC_H

/*!
 * @file EFIIPCC.h
 * This file defines the public API to the IPCC
 * driver.
 *
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/* $Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/Protocol/EFIIPCC.h#1 $ */

/*when     who      what, where, why
--------   ---      ----------------------------------------------------------
02/01/22   shm      Added additional definitions required for Lanai
01/31/22   shm      Added additional definitions required for Hamoa
12/14/21   dsundriy added additional clients required for lassen 
09/15/21   dsundriy added additional clients required for aurora 
02/05/21   dsundriy added additional clients required for fillmore
01/12/21   ssapre   added smp2p.lib and smp2pDxe along with few minor changes in QcomCatePck and few headers
04/30/20   cpaulo   Initial

===========================================================================*/


#ifdef __cplusplus
extern "C" {
#endif


/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include <Uefi.h>

/**
  Protocol version.
*/
#define EFI_IPCC_PROTOCOL_VERSION 0x0000000000010002

/**
 * IPCC Device Interface GUID
 *
 * This is the GUID that identifies the IPCC driver's interface and can be
 * used by the client to determine when the IPCC driver's interface is ready
 * via the plug and play manager. A client should use this GUID in conjunction
 * with the PnP API IoRegisterPlugPlayNotification().
 */
#define EFI_IPCC_PROTOCOL_GUID \
  { 0x52858ad7, 0x8b16, 0x4137, { 0x9c, 0x64, 0xdf, 0xe0, 0x4d, 0x94, 0x2e, 0x80 } };

/**
  External reference to the CLOCK Protocol GUID.
*/
extern EFI_GUID gEfiIpccProtocolGuid;

/**
 * Opaque handle for clients reference to the driver.
 */
typedef VOID*         EFIIPCC_Handle;

/**
 * Signal value to listen in on or to trigger. 
 * Values range from 0 to number supported. 
 */
typedef UINT32      EFIIPCC_Signal;

/**
 * Return value is a number.  They generally take form 
 * of definitions defined as IPCC_E*. Success generally 
 * returns IPCC_EOK for example. 
 */
typedef UINT32      EFIIPCCErr;

/**
 * Protocol enumeration based on IPCC specification.
 */
typedef enum
{
  /**< MPROC Protocol */
  EFI_IPCC_P_MPROC = 0,

  /**< Compute Level 0 Protocol */
  EFI_IPCC_P_COMPUTEL0 = 1,

  /**< Compute Level 1 Protocol */
  EFI_IPCC_P_COMPUTEL1 = 2,

  /**< PCIe Message Signal Interrupt / Peripheral Protocol */
  EFI_IPCC_P_PCIEMSI = 3,
  EFI_IPCC_P_PERIPH = EFI_IPCC_P_PCIEMSI,

  /**< Fence Protocol */
  EFI_IPCC_P_FENCE = 4,

  /**< Total number of supported protocols */
  EFI_IPCC_P_TOTAL
}
EFIIPCC_Protocol;

/**
 * Client enumeration based on IPCC specification.
 */
typedef enum
{
  /**< Always-On Processor */
  EFI_IPCC_C_AOP = 0,

  /**< Trustzone (Secure Application Processor) */
  EFI_IPCC_C_TZ = 1,
  EFI_IPCC_C_APSS_S = EFI_IPCC_C_TZ,

  /**< Modem DSP */
  EFI_IPCC_C_MPSS = 2,

  /**< Low-Power Audio DSP */
  EFI_IPCC_C_LPASS = 3,

  /**< Sensors Low Power Island DSP */
  EFI_IPCC_C_SLPI = 4,

  /**< Sensors Co-Processor */
  EFI_IPCC_C_SDC = 5,

  /**< Neuro System Processor (0) / Turing */
  EFI_IPCC_C_NSP0 = 6,
  EFI_IPCC_C_CDSP = EFI_IPCC_C_NSP0,

  /**< Neuro Processing Unit */
  EFI_IPCC_C_NPU = 7,

  /**< Application Processor (Non-Secure) */
  EFI_IPCC_C_APPS = 8,
  EFI_IPCC_C_APSS_NS0 = EFI_IPCC_C_APPS,

  /**< Graphics Processing Unit */
  EFI_IPCC_C_GPU = 9,

  /**< Computer Vision Processor */
  EFI_IPCC_C_CVP = 10,

  /**< Camera Processor */
  EFI_IPCC_C_CAM = 11,

  /**< Video Processing Unit */
  EFI_IPCC_C_VPU = 12,

  /**< PCIe Client 0 */
  EFI_IPCC_C_PCIE0 = 13,

  /**< PCIe Client 1 */
  EFI_IPCC_C_PCIE1 = 14,

  /**< PCIe Client 2 */
  EFI_IPCC_C_PCIE2 = 15,

  /**< Secure Processor */
  EFI_IPCC_C_SPSS = 16,

  /**< Safety Management Subsystem */
  EFI_IPCC_C_SMSS = 17,

  /**< Neuro System Processor */
  EFI_IPCC_C_NSP1 = 18,

  /**< PCIe Client 3 */
  EFI_IPCC_C_PCIE3 = 19,

  /**< PCIe Client 4 */
  EFI_IPCC_C_PCIE4 = 20,

  /**< PCIe Client 5 */
  EFI_IPCC_C_PCIE5 = 21,

  /**< PCIe Client 6 */
  EFI_IPCC_C_PCIE6 = 22,

  /**< TMESS Client */
  EFI_IPCC_C_TMESS = 23,

  /**< WPSS Client */
  EFI_IPCC_C_WPSS = 24,

  /**< DPU Client */
  EFI_IPCC_C_DPU = 25,
  EFI_IPCC_C_DPU0 = EFI_IPCC_C_DPU,

  /**< IPA Client */
  EFI_IPCC_C_IPA = 26,

  /**< SAIL0 Client */
  EFI_IPCC_C_SAIL0 = 27,

  /**< SAIL1 Client */
  EFI_IPCC_C_SAIL1 = 28,

  /**< SAIL2 Client */
  EFI_IPCC_C_SAIL2 = 29,

  /**< SAIL3 Client */
  EFI_IPCC_C_SAIL3 = 30,

  /**< GPDSP0 Client */
  EFI_IPCC_C_GPDSP0 = 31,

  /**< GPDSP1 Client */
  EFI_IPCC_C_GPDSP1 = 32,

  /**< APSS_NS1 Client */
  EFI_IPCC_C_APSS_NS1 = 33,

  /**< APSS_NS2 Client */
  EFI_IPCC_C_APSS_NS2 = 34,

  /**< APSS_NS3 Client */
  EFI_IPCC_C_APSS_NS3 = 35,

  /**< APSS_NS4 Client */
  EFI_IPCC_C_APSS_NS4 = 36,

  /**< APSS_NS5 Client */
  EFI_IPCC_C_APSS_NS5 = 37,

  /**< APSS_NS6 Client */
  EFI_IPCC_C_APSS_NS6 = 38,

  /**< APSS_NS7 Client */
  EFI_IPCC_C_APSS_NS7 = 39,

  /**< TENX Client */
  EFI_IPCC_C_TENX = 40,

  /**< ORAN Client */
  EFI_IPCC_C_ORAN = 41,

  /**< Message Verification Module Subsystem */
  EFI_IPCC_C_MVMSS = 42,

  /**< (Second) Display Processing Unit */
  EFI_IPCC_C_DPU1 = 43,

  /**< PCIe Client 7 */
  EFI_IPCC_C_PCIE7 = 44,

  /**< Debug Client */
  EFI_IPCC_C_DBG = 45,

  /**< Imaging Front End Client 0 */
  EFI_IPCC_C_IFE0 = 128,

  /**< Imaging Front End Client 1 */
  EFI_IPCC_C_IFE1 = 129,

  /**< Imaging Front End Client 2 */
  EFI_IPCC_C_IFE2 = 130,

  /**< Imaging Front End Client 3 */
  EFI_IPCC_C_IFE3 = 131,

  /**< Imaging Front End Client 4 */
  EFI_IPCC_C_IFE4 = 132,

  /**< Imaging Front End Client 5 */
  EFI_IPCC_C_IFE5 = 133,

  /**< Imaging Front End Client 6 */
  EFI_IPCC_C_IFE6 = 134,

  /**< Imaging Front End Client 7 */
  EFI_IPCC_C_IFE7 = 135,

  /**< Total number of supported clients */
  EFI_IPCC_C_TOTAL
}
EFIIPCC_Client;

/**
 * Callback data type, natural datatype size based on processor.
 */
typedef void*         EFIIPCC_CBData;


/**
 * Callback function prototype for receiving incoming interrupt 
 * signals. 
 */
typedef void (*EFIIPCC_CB) (EFIIPCC_CBData nData, EFIIPCC_Client eSenderID, EFIIPCC_Signal nSignal);

/** @} */ /* end_data_types */

/** @addtogroup constants_macros
@{ */

/**
 * Return value MACROs.
 */
#define EFI_IPCC_EOK             0 /**< Success */
#define EFI_IPCC_EGENERR        -1 /**< Generic (unspecified) error */
#define EFI_IPCC_EMEM           -2 /**< Memory error */
#define EFI_IPCC_EARG           -3 /**< Argument error */
#define EFI_IPCC_EINUSE         -4 /**< Signal in-use error */
#define EFI_IPCC_EUNUSED        -5 /**< Signal not used error */
#define EFI_IPCC_ENOTFOUND      -6 /**< Signal not found error */
#define EFI_IPCC_ENOTSUPPORTED  -7 /**< Signal not supported error */


/*--------------------------------------------------------------------------
  Function declarations
---------------------------------------------------------------------------*/

 /*=======================================================================
**  Function : EFIIPCC_Attach
** =========================================================================*/
/**
  Attaches given handle to IPCC driver and protocol.

  This function takes a reference to the IPCC handle and protocol enumeration.
  This function must be called before calling any other IPCC API in order to
  notify the IPCC driver of the requirement to use the protocol requested.  

  @param pH        [out] Reference to a client handle.
  @param eProtocol [in]  IPCC protocol requested to use.

  @return
  EFI_IPCC_EOK -- Successfully attached to protocol eProtocol. 
  EFI_IPCC_EGENERR -- IPCC not yet initialized. 
  EFI_IPCC_EMEM -- Insufficient memory available for client handle reference. 
  EFI_IPCC_ENOTSUPPORTED -- Protocol requested is not supported. 
  EFI_IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Driver must be initialized.
*/

typedef EFIIPCCErr (*EFI_IPCC_ATTACH)
(
  EFIIPCC_Handle   *pH,
  EFIIPCC_Protocol eProtocol
);


/* =========================================================================
**  Function : EFIIPCC_Detach
** =========================================================================*/
/**
  Detaches the given handle from IPCC driver.

  This function takes a reference to the IPCC handle and detaches it from the
  driver.  It should only be used if there is no requirement for this handle
  at the point it's called.  

  @param pH        [out] Reference to a client handle.

  @return
  EFI_IPCC_EOK -- Successfully detached client handle. \n
  EFI_IPCC_EARG -- Unsupported argument passed in by client.
*/
typedef EFIIPCCErr (*EFI_IPCC_DETACH)
(
  EFIIPCC_Handle *pH
);


/* =========================================================================
**  Function : EFIIPCC_RegisterInterrupt
** =========================================================================*/
/**
  Registers a callback function for when signals are received from a given
  sender.

  This function is used to register a notification with the IPCC driver.
  The callback function pfnCB is called whenever the sender eSenderCID
  signals the processor running this SW with any of the signals in the
  range nSignalLow to nSignalHigh.  If only one signal is being registered,
  then nSignalLow should be the same as nSignalHigh.  If any of the signals
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
  EFI_IPCC_EOK -- Successfully registered the signals for eSenderCID. \n
  EFI_IPCC_EARG -- Unsupported argument passed in by client. \n
  EFI_IPCC_EINUSE -- One or more of the requested signals are in use.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/
typedef EFIIPCCErr (*EFI_IPCC_REGISTERINTERRUPT)
(
  EFIIPCC_Handle       h,
  EFIIPCC_Client       eSenderCID, 
  EFIIPCC_Signal       nSignalLow,
  EFIIPCC_Signal       nSignalHigh,
  EFIIPCC_CB           pfnCB,
  EFIIPCC_CBData       nData
);


/* =========================================================================
**  Function : EFIIPCC_DeregisterInterrupt
** =========================================================================*/
/**
  Deregisters a previously registered callback function for signals
  received from a given sender.

  This function is used to deregister a notification from the IPCC driver.
  This will remove all future notificatoins of the previously registered
  callback function from happening.  If only one signal is being deregistered,
  then nSignalLow should be the same as nSignalHigh.  If any of the signals
  are not in use, then the API will fail and none of the requested signals will
  be deregistered.

  @param h           [in] Client handle.
  @param eSenderCID  [in] Client ID of the sender.
  @param nSignalLow  [in] Lowest signal number to deregister.
  @param nSignalHigh [in] Highest signal number to deregister.

  @return
  EFI_IPCC_EOK -- Successfully deregistered the signals for eSenderCID. \n
  EFI_IPCC_EARG -- Unsupported argument passed in by client. \n
  EFI_IPCC_EUNUSED -- One or more of the requested signals are not in use.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/
typedef EFIIPCCErr (*EFI_IPCC_DEREGISTERINTERRUPT)
(
  EFIIPCC_Handle       h,
  EFIIPCC_Client       eSenderCID, 
  EFIIPCC_Signal       nSignalLow,
  EFIIPCC_Signal       nSignalHigh
);


/* =========================================================================
**  Function : EFIIPCC_Trigger
** =========================================================================*/
/**
  Triggers interrupts on remote clients.

  This function is used to assert the signals in the range nSignalLow to
  nSignalHigh on target eTargetCID.  

  @param h           [in] Client handle.
  @param eTargetCID  [in] Client ID of the target.
  @param nSignalLow  [in] Lowest signal number to assert.
  @param nSignalHigh [in] Highest signal number to assert.

  @return
  EFI_IPCC_EOK -- Successfully trigger the signals to eTargetCID. \n
  EFI_IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/
typedef EFIIPCCErr (*EFI_IPCC_TRIGGER)
(
  EFIIPCC_Handle       h,
  EFIIPCC_Client       eTargetCID,
  EFIIPCC_Signal       nSignalLow,
  EFIIPCC_Signal       nSignalHigh
);


/*!
 * Interface for IPCC clients to the IPCC API
 */
typedef struct _EFI_IPCC_PROTOCOL
{
  UINT64                           Version;
  EFI_IPCC_ATTACH                  IpccAttach;
  EFI_IPCC_DETACH                  IpccDetach;
  EFI_IPCC_REGISTERINTERRUPT       IpccRegisterInterrupt;
  EFI_IPCC_DEREGISTERINTERRUPT     IpccDeregisterInterrupt;
  EFI_IPCC_TRIGGER                 IpccTrigger;
}EFI_IPCC_PROTOCOL;


#ifdef __cplusplus
}
#endif

#endif /* EFIIPCC_H */

