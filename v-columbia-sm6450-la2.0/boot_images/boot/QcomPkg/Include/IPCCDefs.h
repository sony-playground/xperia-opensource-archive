#ifndef IPCC_DEFS_H
#define IPCC_DEFS_H

/*!
 * @file IPCCDefs.h
 * This file defines the public API definitions for the IPCC
 * driver.
 *
 * Copyright (c) 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
 */
/* $Header: //components/rel/core.boot/6.0/QcomPkg/Include/IPCCDefs.h#4 $ */

/*when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/07/2020  cpaulo   Initial Split
09/12/2020  dsundriy added IPCC_ConfigType structure
02/05/2021  dsundriy added additional clients required for fillmore
09/15/2021  dsundriy added additional clients required for aurora 

===========================================================================*/


#ifdef __cplusplus
extern "C" {
#endif


/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include <stdint.h>


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
 * Return value is a number.  They generally take form 
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

  /**< PCIe Message Signal Interrupt Protocol */
  IPCC_P_PCIEMSI = 3,

  /**< Total number of supported protocols */
  IPCC_P_TOTAL
}
IPCC_Protocol;

/**
 * Client enumeration based on IPCC specification.
 */
typedef enum
{
  /**< Resource Power manager */
  IPCC_C_RPM = 0, 
  
  /**< Always-On Processor */
  IPCC_C_AOP = IPCC_C_RPM,

  /**< Trustzone (Secure Application Processor) */
  IPCC_C_TZ = 1,

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
  
  /**< TMESS Client */
  IPCC_C_TMESS = 23,

  /**< WPSS Client */
  IPCC_C_WPSS = 24,

  /**< DPU Client */
  IPCC_C_DPU = 25,

  /**< IPA Client */
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



/**
 * Config keys for getting/setting configuration for IPCC 
 * signals 
 */
typedef enum
{
  /**< Configure priority value */
  IPCC_CT_PRIORITY = 0,

  /**< Configure interrupt as an island interrupt */
  IPCC_CT_ISLAND = 1,
}
IPCC_ConfigType;


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


#ifdef __cplusplus
}
#endif

#endif /* IPCC_DEFS_H */
