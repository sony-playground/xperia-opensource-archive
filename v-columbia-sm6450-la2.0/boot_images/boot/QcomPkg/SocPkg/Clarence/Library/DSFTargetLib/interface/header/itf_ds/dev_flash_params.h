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
 Copyright (c) 2013-2018, Qualcomm Technologies Incorporated.
 All rights reserved.
 ******************************************************************************/
/*==============================================================================
$Header: //sve/convex/release/clarence/v1/convex_2022_05_27_ver_04.00/convex/drivers/ddr/platform/clarence/src/DDRSS_SNS_V4/interface/header/itf_ds/dev_flash_params.h#1 $
$DateTime: 2022/05/27 05:44:57 $
$Author: bhagavat $
================================================================================*/
/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "HALcomdef.h"
/*==============================================================================
                                  TYPES & DEFINES
==============================================================================*/

#define TRAINING_DATA_SIZE_IN_BYTES (256 * (84 + 16))
#define TRAINING_DATA_SIZE_IN_BYTES_FACTORY (256 * 2)

/******************************************************/
/*** DDR Parameter partition datastructure ***/
/******************************************************/

struct ddr_params_partition
{
    uint32 magic_number;
    uint32 version;
    uint32 training_data_size;
    uint32 training_log_size;
    uint32 checksum;
    uint32 checksum_factory_data;
    
    uint8 training_data[TRAINING_DATA_SIZE_IN_BYTES]; // training data which can be cleared to force retraining for new DSF versions
    uint8 training_data_factory[TRAINING_DATA_SIZE_IN_BYTES_FACTORY]; // training data which must be retained to permit OTA DSF updates
};
#endif /* __DEV_FLASH_PARAMS_H__ */
