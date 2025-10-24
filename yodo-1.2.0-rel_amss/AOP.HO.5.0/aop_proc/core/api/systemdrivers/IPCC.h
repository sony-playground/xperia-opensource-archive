#ifndef __IPCC_H__
#define __IPCC_H__
/*
===========================================================================
*/
/**
  @file IPCC.h
  @brief Public interface include file for accessing the IPCC device driver.

  The IPCC.h file is the public API interface to the Inter-Processor 
  Communication Controller driver.
*/
/*
  ===========================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ===========================================================================

  $Header: //components/rel/aop.ho/5.0/aop_proc/core/api/systemdrivers/IPCC.h#3 $
  $DateTime: 2022/04/08 12:11:36 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ---------------------------------------------------------- 
  03/30/22   shm     Added definitions required for Lanai and Hamoa
  02/04/22   shm     Added definitions required for Pinnacles
  05/18/18   cp      Initial revision.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include <stdint.h>

/*=========================================================================
      Type Definitions
==========================================================================*/

/** @addtogroup data_types
@{ */

/**
 * Opaque handle for clients reference to the driver.
 */
typedef void*         IPCC_Handle;

/**
 * Signal value to listen in on or to trigger.
 * Values range from 0 to number supported.
 */
typedef uint32_t      IPCC_Signal;

/**
 * Return value is a number. They generally take form
 * of definitions defined as IPCC_E*. Success generally
 * returns IPCC_EOK for example.
 */
typedef uint32_t      IPCCErr;

/**
 * Protocol enumeration based on IPCC specification.
 */
typedef enum
{
  /**< MPROC Protocol */
  IPCC_P_MPROC = 0,

  /**< Compute Level 0 Protocol */
  IPCC_P_COMPUTEL0 = 1,

  /**< Compute Level 1 Protocol */
  IPCC_P_COMPUTEL1 = 2,

  /**< PCIe Message Signal Interrupt / Peripheral Protocol */
  IPCC_P_PCIEMSI = 3,
  IPCC_P_PERIPH = IPCC_P_PCIEMSI,

  /**< Fence Protocol */
  IPCC_P_FENCE = 4,

  /**< Total number of supported protocols */
  IPCC_P_TOTAL
}
IPCC_Protocol;

/**
 * Client enumeration based on IPCC specification.
 */
typedef enum
{
  /**< Always-On Processor */
  IPCC_C_AOP = 0,

  /**< Trustzone (Secure Application Processor) */
  IPCC_C_TZ = 1,
  IPCC_C_APSS_S = IPCC_C_TZ,

  /**< Modem DSP */
  IPCC_C_MPSS = 2,

  /**< Low-Power Audio DSP */
  IPCC_C_LPASS = 3,

  /**< Sensors Low Power Island DSP */
  IPCC_C_SLPI = 4,

  /**< Sensors Co-Processor */
  IPCC_C_SDC = 5,

  /**< Neuro System Processor (0) / Turing */
  IPCC_C_NSP0 = 6,
  IPCC_C_CDSP = IPCC_C_NSP0,

  /**< Neuro Processing Unit */
  IPCC_C_NPU = 7,

  /**< Application Processor (Non-Secure) */
  IPCC_C_APPS = 8,
  IPCC_C_APSS_NS0 = IPCC_C_APPS,

  /**< Graphics Processing Unit */
  IPCC_C_GPU = 9,

  /**< Computer Vision Processor */
  IPCC_C_CVP = 10,

  /**< Camera Processor */
  IPCC_C_CAM = 11,

  /**< Video Processing Unit */
  IPCC_C_VPU = 12,

  /**< PCIe Client 0 */
  IPCC_C_PCIE0 = 13,

  /**< PCIe Client 1 */
  IPCC_C_PCIE1 = 14,

  /**< PCIe Client 2 */
  IPCC_C_PCIE2 = 15,

  /**< Secure Processor */
  IPCC_C_SPSS = 16,

  /**< Safety Management Subsystem */
  IPCC_C_SMSS = 17,

  /**< Neuro System Processor */
  IPCC_C_NSP1 = 18,

  /**< PCIe Client 3 */
  IPCC_C_PCIE3 = 19,

  /**< PCIe Client 4 */
  IPCC_C_PCIE4 = 20,

  /**< PCIe Client 5 */
  IPCC_C_PCIE5 = 21,

  /**< PCIe Client 6 */
  IPCC_C_PCIE6 = 22,
  
  /**< Trust Management Engine Subsystem */
  IPCC_C_TMESS = 23,

  /**< WPSS */
  IPCC_C_WPSS = 24,

  /**< Display Processing Unit */
  IPCC_C_DPU = 25,
  IPCC_C_DPU0 = IPCC_C_DPU,

  /**< Internet Protocol Accelerator */
  IPCC_C_IPA = 26,

  /**< SAIL0 Client */
  IPCC_C_SAIL0 = 27,

  /**< SAIL1 Client */
  IPCC_C_SAIL1 = 28,

  /**< SAIL2 Client */
  IPCC_C_SAIL2 = 29,

  /**< SAIL3 Client */
  IPCC_C_SAIL3 = 30,

  /**< GPDSP0 Client */
  IPCC_C_GPDSP0 = 31,

  /**< GPDSP1 Client */
  IPCC_C_GPDSP1 = 32,

  /**< APSS_NS1 Client */
  IPCC_C_APSS_NS1 = 33,

  /**< APSS_NS2 Client */
  IPCC_C_APSS_NS2 = 34,

  /**< APSS_NS3 Client */
  IPCC_C_APSS_NS3 = 35,

  /**< APSS_NS4 Client */
  IPCC_C_APSS_NS4 = 36,

  /**< APSS_NS5 Client */
  IPCC_C_APSS_NS5 = 37,

  /**< APSS_NS6 Client */
  IPCC_C_APSS_NS6 = 38,

  /**< APSS_NS7 Client */
  IPCC_C_APSS_NS7 = 39,

  /**< TENX Client */
  IPCC_C_TENX = 40,

  /**< ORAN Client */
  IPCC_C_ORAN = 41,

  /**< Message Verification Module Subsystem */
  IPCC_C_MVMSS = 42,

  /**< (Second) Display Processing Unit */
  IPCC_C_DPU1 = 43,

  /**< PCIe Client 7 */
  IPCC_C_PCIE7 = 44,

  /**< Debug Client */
  IPCC_C_DBG = 45,

  /**< Imaging Front End Client 0 */
  IPCC_C_IFE0 = 128,

  /**< Imaging Front End Client 1 */
  IPCC_C_IFE1 = 129,

  /**< Imaging Front End Client 2 */
  IPCC_C_IFE2 = 130,

  /**< Imaging Front End Client 3 */
  IPCC_C_IFE3 = 131,

  /**< Imaging Front End Client 4 */
  IPCC_C_IFE4 = 132,

  /**< Imaging Front End Client 5 */
  IPCC_C_IFE5 = 133,

  /**< Imaging Front End Client 6 */
  IPCC_C_IFE6 = 134,

  /**< Imaging Front End Client 7 */
  IPCC_C_IFE7 = 135,

  /**< Total number of supported clients */
  IPCC_C_TOTAL
}
IPCC_Client;

/**
 * Callback data type, natural datatype size based on processor.
 */
typedef void*         IPCC_CBData;


/**
 * Callback function prototype for receiving incoming interrupt
 * signals.
 */
typedef void (*IPCC_CB) (IPCC_CBData nData, IPCC_Client eSenderID, IPCC_Signal nSignal);

/** @} */ /* end_data_types */

/** @addtogroup constants_macros
@{ */

/**
 * Return value MACROs.
 */
#define IPCC_EOK             0 /**< Success */
#define IPCC_EGENERR        -1 /**< Generic (unspecified) error */
#define IPCC_EMEM           -2 /**< Memory error */
#define IPCC_EARG           -3 /**< Argument error */
#define IPCC_EINUSE         -4 /**< Signal in-use error */
#define IPCC_EUNUSED        -5 /**< Signal not used error */
#define IPCC_ENOTFOUND      -6 /**< Signal not found error */
#define IPCC_ENOTSUPPORTED  -7 /**< Signal not supported error */

/** @} */ /* end_addtogroup constants_macros */



/*=========================================================================
      Interface Declarations
==========================================================================*/
/** @addtogroup ipcc_functions
@{ */


/* =========================================================================
**  Function : IPCC_Attach
** =========================================================================*/
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

IPCCErr
IPCC_Attach
(
  IPCC_Handle   *pH,
  IPCC_Protocol eProtocol
);


/* =========================================================================
**  Function : IPCC_Detach
** =========================================================================*/
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

IPCCErr
IPCC_Detach
(
  IPCC_Handle *pH
);


/* =========================================================================
**  Function : IPCC_RegisterInterrupt
** =========================================================================*/
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

IPCCErr 
IPCC_RegisterInterrupt
(
  IPCC_Handle       h,
  IPCC_Client       eSenderCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_CB           pfnCB,
  IPCC_CBData       nData
);


/* =========================================================================
**  Function : IPCC_DeregisterInterrupt
** =========================================================================*/
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

IPCCErr 
IPCC_DeregisterInterrupt
(
  IPCC_Handle       h,
  IPCC_Client       eSenderCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);


/* =========================================================================
**  Function : IPCC_Trigger
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
  IPCC_EOK -- Successfully trigger the signals to eTargetCID. \n
  IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/

IPCCErr
IPCC_Trigger
(
  IPCC_Handle       h,
  IPCC_Client       eTargetCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);

/** @} */ /* end_addtogroup ipcc_functions */

#endif /*__IPCC_H__*/
