#ifndef __DEV_FLASH_PARAMS_H__
#define __DEV_FLASH_PARAMS_H__

/*=============================================================================

                                DDR device Flash PARAMETERS
                                Header File
GENERAL DESCRIPTION
This file defines the DDR parameters stored in DDR Flash partition
=============================================================================*/
/*******************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2013-2018,2022 Qualcomm Technologies Incorporated.
 All rights reserved.
 ******************************************************************************/
/*==============================================================================
$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/DSFTargetLib/interface/header/itf_ds/dev_flash_params.h#1 $
$DateTime: 2022/08/18 10:15:46 $
$Author: pwbldsvc $
================================================================================*/
/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "HALcomdef.h"
/*==============================================================================
                                  TYPES & DEFINES
==============================================================================*/

#define TRAINING_DATA_SIZE_IN_BYTES (256 * (100 + 16))
#define TRAINING_DATA_SIZE_IN_BYTES_FACTORY (256 * 2)

/******************************************************/
/*** DDR Parameter partition datastructure ***/
/******************************************************/

struct ddr_params_partition
{
    uint32 magic_number;
    uint32 dsf_code_mainline_version;
    uint32 dsf_code_major_version;
    uint32 dsf_code_minor_version;
    uint32 training_data_size;
    uint32 training_log_size;
    uint32 checksum;
    uint32 checksum_factory_data;
    uint8  hmac[64];
    size_t hmac_size;
    
    uint8 training_data[TRAINING_DATA_SIZE_IN_BYTES]; // training data which can be cleared to force retraining for new DSF versions
    uint8 training_data_factory[TRAINING_DATA_SIZE_IN_BYTES_FACTORY]; // training data which must be retained to permit OTA DSF updates
};
#endif /* __DEV_FLASH_PARAMS_H__ */
