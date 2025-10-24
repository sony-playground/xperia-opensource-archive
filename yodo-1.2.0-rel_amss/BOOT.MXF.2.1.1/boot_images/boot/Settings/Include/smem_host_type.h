#ifndef SMEM_HOST_TYPE_H
#define SMEM_HOST_TYPE_H

/**
 * @file smem_host_type.h
 *
 * HOST values used by SMEM
 */

/*==============================================================================
  Copyright (c) 2021 Qualcomm Technologies, Inc.
           All Rights Reserved.
  Qualcomm Technologies, Inc. Confidential and Proprietary.
==============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/Settings/Include/smem_host_type.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/24/21   mad     Carved out from smem_type.h
===========================================================================*/

/*===========================================================================
                               TYPE DEFINITIONS
===========================================================================*/

/** 
 * A list of hosts supported in SMEM.
 * IMPORTANT NOTE:
 * SMEM host enumeration constants had to be replicated as symbolic constants, to enable usage in device-tree source.
 * (Since Device-tree source does not support C constructs.)
 * So, any change in smem_host_type enum needs to be replicated in this file. 
*/

#define SMEM_APPS   		0                     /**< Apps Processor */
#define SMEM_MODEM          1                     /**< Modem processor */
#define SMEM_ADSP           2                     /**< ADSP processor */
#define SMEM_SSC            3                     /**< Sensor processor */
#define SMEM_WCN            4                     /**< WCN processor */
#define SMEM_CDSP           5                     /**< Reserved */
#define SMEM_RPM            6                     /**< RPM processor */
#define SMEM_TZ             7                     /**< TZ processor */
#define SMEM_SPSS           8                     /**< Secure processor */
#define SMEM_HYP            9                     /**< Hypervisor */
#define SMEM_NPU			10                    /**< NPU processor */
#define SMEM_SPSS_SP		11  				  /**< SPSS Host that shares partition with TZ*/
#define SMEM_NSP1           12                    /**< NSP1 processor */
#define SMEM_WPSS           13                    /**< WPSS processor */
#define SMEM_TME            14                    /**< TME processor */
#define SMEM_NUM_HOSTS      15                    /**< Max number of host in target */

#define SMEM_Q6             SMEM_ADSP             /**< Kept for legacy purposes.
                                                  **  New code should use SMEM_ADSP */
#define SMEM_RIVA           SMEM_WCN              /**< Kept for legacy purposes.
                                                  **  New code should use SMEM_WCN */
#define SMEM_DSPS           SMEM_SSC              /**< Kept for legacy purposes.
                                                  **  New code should use SMEM_SSC */
#define SMEM_SPSS_NONSP      SMEM_SPSS            /**< SPSS host that shares partition with HLOS */
#define SMEM_NSP             SMEM_CDSP
#define SMEM_CMDDB           0xFFFD               /**< Reserverd partition for command DB usecase */
#define SMEM_COMMON_HOST     0xFFFE               /**< Common host */
#define SMEM_INVALID_HOST    0xFFFF  


#endif /* SMEM_HOST_TYPE_H */
