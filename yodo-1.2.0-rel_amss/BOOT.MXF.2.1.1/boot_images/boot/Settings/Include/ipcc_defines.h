#ifndef IPCC_DEFINES_H
#define IPCC_DEFINES_H

/*!
 * @file ipcc_defines.h
 * This file defines symbolic constants that are part of public API to the IPCC
 * driver.
 *
 * Copyright (c) 2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
 */

/*
when        who     what, where, why
--------    ---     ----------------------------------------------------------
02/15/2022  mad     Carved out constants from EFIIPCC.h to include in DTS
===========================================================================*/
 /**
 * Protocol constants based on IPCC specification.
 */
  /**< MPROC Protocol */
#define IPCC_P_MPROC  		0

/**< Compute Level 0 Protocol */
#define IPCC_P_COMPUTEL0  	1

/**< Compute Level 1 Protocol */
#define IPCC_P_COMPUTEL1 	2

/**< PCIe Message Signal Interrupt / Peripheral Protocol */
#define  IPCC_P_PCIEMSI 	3
#define  IPCC_P_PERIPH      IPCC_P_PCIEMSI

#define IPCC_P_FENCE 		4

/**< Total number of supported protocols */
#define  IPCC_P_TOTAL  		5


/**
 * Client constants based on IPCC specification.
 */
/**< Always-On Processor */
#define IPCC_C_AOP 			0

/**< Trustzone (Secure Application Processor) */
#define IPCC_C_TZ			1

/**< Modem DSP */
#define IPCC_C_MPSS			2

/**< Low-Power Audio DSP */
#define IPCC_C_LPASS 		3

/**< Sensors Low Power Island DSP */
#define IPCC_C_SLPI 		4

  /**< Sensors Co-Processor */
#define IPCC_C_SDC    		5

  /**< Neuro System Processor (0) / Turing */
#define IPCC_C_NSP0 		6
#define IPCC_C_CDSP 		IPCC_C_NSP0

  /**< Neuro Processing Unit */
#define IPCC_C_NPU 			7

  /**< Application Processor (Non-Secure) */
#define IPCC_C_APPS 		8

  /**< Graphics Processing Unit */
#define IPCC_C_GPU 			9

  /**< Computer Vision Processor */
#define IPCC_C_CVP 			10

  /**< Camera Processor */
#define IPCC_C_CAM 			11

  /**< Video Processing Unit */
#define IPCC_C_VPU 			12

  /**< PCIe Client 0 */
#define IPCC_C_PCIE0 		13

  /**< PCIe Client 1 */
#define IPCC_C_PCIE1 		14

  /**< PCIe Client 2 */
#define IPCC_C_PCIE2 		15

  /**< Secure Processor */
#define IPCC_C_SPSS  		16

  /**< Safety Management Subsystem */
#define IPCC_C_SMSS  		17

  /**< Neuro System Processor */
#define IPCC_C_NSP1  		18

  /**< PCIe Client 3 */
#define IPCC_C_PCIE3  		19

  /**< PCIe Client 4 */
#define IPCC_C_PCIE4  		20

  /**< PCIe Client 5 */
#define IPCC_C_PCIE5  		21

  /**< PCIe Client 6 */
#define IPCC_C_PCIE6  		22
  
  /**< TMESS Client */
#define IPCC_C_TMESS  		23
  
  /**< WPSS Client */
#define IPCC_C_WPSS  		24

  /**< DPU Client */
#define IPCC_C_DPU  		25

  /**< IPA Client */
#define IPCC_C_IPA  		26

  /**< SAIL0 Client */
#define IPCC_C_SAIL0  		27

  /**< SAIL1 Client */
#define IPCC_C_SAIL1  		28

  /**< SAIL2 Client */
#define IPCC_C_SAIL2  		29

  /**< SAIL3 Client */
#define IPCC_C_SAIL3  		30

  /**< GPDSP0 Client */
#define IPCC_C_GPDSP0  		31

  /**< GPDSP1 Client */
#define IPCC_C_GPDSP1  		32

  /**< APSS_NS1 Client */
#define IPCC_C_APSS_NS1  	33

  /**< APSS_NS2 Client */
#define IPCC_C_APSS_NS2  	34

  /**< APSS_NS3 Client */
#define IPCC_C_APSS_NS3  	35

/**< APSS_NS4 Client */
#define IPCC_C_APSS_NS4  	36

/**< APSS_NS5 Client */
#define IPCC_C_APSS_NS5  	37

/**< APSS_NS6 Client */
#define IPCC_C_APSS_NS6  	38

/**< APSS_NS7 Client */
#define IPCC_C_APSS_NS7  	39

/**< TENX Client */
 #define IPCC_C_TENX        40

/**< ORAN Client */
#define IPCC_C_ORAN  		41

/**< Message Verification Module Subsystem */
#define  IPCC_C_MVMSS 		42

/**< (Second) Display Processing Unit */
#define  IPCC_C_DPU1 		43

/**< PCIe Client 7 */
#define IPCC_C_PCIE7 		44

/**< Debug Client */
#define IPCC_C_DBG 			45

/**< Imaging Front End Client 0 */
#define  IPCC_C_IFE0 		128

/**< Imaging Front End Client 1 */
#define  IPCC_C_IFE1 		129

/**< Imaging Front End Client 2 */
#define IPCC_C_IFE2 		130

/**< Imaging Front End Client 3 */
#define IPCC_C_IFE3 		131

/**< Imaging Front End Client 4 */
#define IPCC_C_IFE4 		132

  /**< Imaging Front End Client 5 */
#define  IPCC_C_IFE5 		133

  /**< Imaging Front End Client 6 */
#define  IPCC_C_IFE6 		134

  /**< Imaging Front End Client 7 */
#define  IPCC_C_IFE7 		135

  /**< Total number of supported clients */
#define  IPCC_C_TOTAL		136

#endif /* IPCC_DEFINES_H */