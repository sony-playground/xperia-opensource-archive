/*******************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2013-2018,2022 Qualcomm Technologies Incorporated.
 All rights reserved.
 ******************************************************************************/
/*==============================================================================
$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/DSFTargetLib/interface/header/itf_ds/HAL_SNS_DDR.h#2 $
$DateTime: 2022/08/22 18:19:18 $
$Author: pwbldsvc $
================================================================================*/
#ifndef __HAL_SNS_DDR_H__
#define __HAL_SNS_DDR_H__

/**---------------------------------------------------------------------------
* @file     HAL_sns_DDR.h
*
* @brief    DDR HW abstraction layer
*--------------------------------------------------------------------------*/

/*=============================================================================

                                   DDR HAL
                            H e a d e r  F i l e
GENERAL DESCRIPTION
This is the header file for ddr HAL. This file is shared across targets

EXTERNALIZED FUNCTIONS
  
INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/DSFTargetLib/interface/header/itf_ds/HAL_SNS_DDR.h#2 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/015/14  tw      Modified clockplan structure to add new fields to support
                   dynamic clockplan sharing
12/01/13   dp      Initial revision.
=============================================================================*/


/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "HALhwio.h"
#include "HALcomdef.h"
#include "seq_hwio.h"

#include "ddr_cores.h"
#if !(SOC_DDRSS_DV) && !(DDRPHY_CHAR)
#include "ddr_common.h"
#include "ddr_aop_params.h"
#include "dev_cdt_params.h"
#endif
#if !(SOC_DDRSS_DV) && !(PHY_DV) && !(DDRPHY_CHAR)
#include "dev_flash_params.h"
#include "ddr_status_reg.h"
#endif
#ifdef BUILD_BOOT_CHAIN
#include "ddr_external.h"
#endif

#include "ddr_ioctl.h"
#ifdef BUILD_BOOT_CHAIN
#include "ddr_log.h"
#endif
#include <stdarg.h>

// Modes for Power Collapse.
typedef enum {
    DDR_POWER_CLPS_MODE_BIMC_ONLY = 0,
    DDR_POWER_CLPS_MODE_PHY_ONLY,
    DDR_POWER_CLPS_MODE_MAX = 0x7F
} DDR_POWER_CLPS_MODE;

typedef enum
{
    PHY_POWER_CLPS_SAVE         = 0x0,
    PHY_POWER_CLPS_RESTORE      = 0x1,
    PHY_POWER_CLPS_SAVE_RESTORE = 0x2
} PCC_MODE;

#define MSM_VERSION_NAPALI  0X6000
#define MSM_VERSION_NAPALIQ 0X6001 
#define MSM_VERSION_HANA    0X6003 
#define MSM_VERSION_POIPU   0X6006 
#define MSM_VERSION_KONA    0X6008 
#define MSM_VERSION_LAHAINA 0X600F
#define MSM_VERSION_CEDROS  0X6017
#define MSM_VERSION_KODIAK  0X6018
#define MSM_VERSION_WAIPIO  0XA001
#define MSM_VERSION_KAILUA  0XA003

/** Encodes vendor-specific pre-standard support for LPDDR4Y features. */
typedef enum
{
    LPDDR4Y_LOW_SPEED_CA_BUFFER = 1 << 0,
    LPDDR4Y_SINGLE_ENDED_CLOCK = 1 << 1,
    LPDDR4Y_SINGLE_ENDED_WRITE_DQS = 1 << 2,
    LPDDR4Y_SINGLE_ENDED_READ_DQS = 1 << 3
} LPDDR4Y_SUPPORT_TYPE;

/**********************/
/*** DDR Debug ***/
/**********************/
/**
 * ddr_dbg: DDR Debug Data Structure.
 * If this element is zero, it means that there is no debug
 * structure that the DDR System Firmware needs to process.
 * A non-zero value in this element will be used by the DDR System Firmware as a
 * pointer to a debug structure whose contents will be determined by debug requirements
 * as they come up.
 */
union ddr_dbg
{
  uint32 ptr32;   /**< Store pointer to DDR Debug Structure */
  uint64 ptr64;   /**< Store pointer to DDR Debug Structure */
};



// DSF V4 New Structs to replace BOOT_DDR_STRUCT and SHRM_DDR_STRUCT
// New Structs starts here..........
// Runtime Structs.............





//Testing for Global DDR_FW_STRUCT for code size comparison use only
//static DDR_FW_STRUCT *DDR_FW_PTR = (DDR_FW_STRUCT *)SEQ_DDR_SS_SHRM_MEM_SHRM_OFFSET;

// New Structs Ends here......................




/****************************************/
/******* For LLCC Cacheable Modes *******/
/****************************************/
typedef enum
{
    NO_OVERRIDE    = 0x0 ,
    NON_CACHEABLE  = 0x1 ,
    CACHEABLE      = 0x2
} CACHEABLE_MODE;

#endif /* __HAL_SNS_DDR_H__ */
