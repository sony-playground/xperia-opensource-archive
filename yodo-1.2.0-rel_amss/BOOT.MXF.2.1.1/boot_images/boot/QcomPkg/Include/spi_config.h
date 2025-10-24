#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__


/*=============================================================================   
    @file  spi_config.h
    @brief interface to device configuration
   
    Copyright (c) 2019, 2021-2022 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/25/22   bn       Updated polled_mode data type
 01/10/19    bng      created
=============================================================================*/


#include "spi_types.h"


#define MAX_SPI_FREQ_CNT 7
#define MAX_SPI_COMMON_CLK_CNT 4

typedef struct spi_plat_clock_config 
{
    //uint8   se_clock_dfs_index;
    uint32  se_clock_frequency_khz;
    uint32  bus_speed_khz;
    uint8   clk_div;

} spi_plat_clock_config;

/* The order of entries in this structure and DT file should be same else 
  there will be a compatibility mismatch */
typedef struct spi_plat_device_config
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
    uint32      min_data_length_for_dma;
    
    uint32      miso_encoding;
    uint32      mosi_encoding;
    uint32      cs_encoding;
    uint32      clk_encoding;

    uint32      sleep_miso_encoding;
    uint32      sleep_mosi_encoding;
    uint32      sleep_cs_encoding;
    uint32      sleep_clk_encoding;


    uint32      tcsr_reg_offset;
    uint8      *tcsr_base_addr;
    uint32      tcsr_reg_value;

    uint32      se_clock_frequency;
    uint8       se_clock_dfs_index;

    uint8     **common_clocks;
    uint8     **se_clock;

    spi_plat_clock_config   *clock_config;

} spi_plat_device_config;

#endif
