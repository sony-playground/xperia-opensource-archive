#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__


/*=============================================================================   
    @file  i2c_config.h
    @brief interface to device configuration
   
    Copyright (c) 2017, 2019, 2021-2022 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/25/22   bn      Added I2C hub changes
 05/07/19   bn      Added Se_index to i2c_device_config
 31/05/17   vg      Copyright updated 
=============================================================================*/


#include "i2c_types.h"

#define MAX_I2C_FREQ_CNT 6
#define MAX_I2C_COMMON_CLK_CNT 4

typedef struct plat_clock_config 
{
    //uint8   se_clock_dfs_index;
    uint32  se_clock_frequency_khz;
    uint32  bus_speed_khz;
    uint8   clk_div;
    uint8   t_cycle;
    uint8   t_high;
    uint8   t_low;

} plat_clock_config;

/* The order of entries in this structure and DT file should be same else 
  there will be a compatibility mismatch */
typedef struct plat_device_config
{
    uint8      *core_base_addr;
    uint8      *common_base_addr;
    uint32      core_offset;
    uint8       qupv3_instance;
    uint8       core_index;
    uint8       se_index;
    uint8       gpi_index;
    uint32      core_irq;
    uint8       polled_mode;
    uint8       i2c_hub;
    uint32      min_data_length_for_dma;
   

    uint32      scl_encoding;
    uint32      sda_encoding;

    uint32      tcsr_reg_offset;
    uint8      *tcsr_base_addr;
    uint32      tcsr_reg_value;
	
    uint8     **common_clocks;
    uint8     **se_clock;

    plat_clock_config   *clock_config;

} plat_device_config;

#endif
