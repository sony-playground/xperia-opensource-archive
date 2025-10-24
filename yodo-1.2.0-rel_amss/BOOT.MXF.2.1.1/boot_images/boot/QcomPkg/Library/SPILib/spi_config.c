/** 
    @file  SPI_config.c
    @brief device configuration implementation
 */
/*=============================================================================
            Copyright (c) 2019, 2021-2022 Qualcomm Technologies, Incorporated.
                              All rights reserved.
              Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

#include "spi_plat.h"
#include "DALSys.h"
#include "SpiApi.h"
#include "spi_log.h"    // logging
#include "spi_api.h"
#include "DTBExtnLib.h"
#include "string.h"
#include "stdio.h"
#include "spi_fw_load.h"
#include "qup_address_ranges.h"

#define SPI_NODE_NAME       "/soc/spi"

/* SPI device config node  */
#define SPI_DEVICE_CONFIG_NODE     "/soc/spi/spi_device_config_"
#define DT_NODE_BUF_SIZE 100

#define SPI_DT_CHECK_ERROR(x)                                         \
{                                                                     \
    if (ret_value) {                                                  \
      SPI_LOG(LEVEL_ERROR, "%s, ret Value = %d\n", u##x, ret_value);  \
      goto ON_EXIT;                                                   \
    }                                                                 \
}

/*
int spi_read_clk_cfg(void *fdt_handle, char *node, spi_plat_clock_config *pClk)
{
  int ret_value;
  fdt_node_handle hNode;


  ret_value = fdt_get_node_handle(&hNode, fdt_handle, node);
  SPI_DT_CHECK_ERROR("Unable to get node handle");

  ret_value = fdt_get_uint32_prop(&hNode, "se_clock_frequency_khz", (uint32 *)&pClk->se_clock_frequency_khz);
  SPI_DT_CHECK_ERROR("Unable to get se_clock_frequency_khz");
  ret_value = fdt_get_uint32_prop(&hNode, "bus_speed_khz", (uint32 *)&pClk->bus_speed_khz);
  SPI_DT_CHECK_ERROR("Unable to get bus_speed_khz");
  ret_value = fdt_get_uint8_prop(&hNode, "clk_div", (uint8 *)&pClk->clk_div);
  SPI_DT_CHECK_ERROR("Unable to get clk_div");

  SPI_LOG(LEVEL_INFO, "[SPI] se_clock_frequency_khz        = 0x%08x\n", pClk->se_clock_frequency_khz);
  SPI_LOG(LEVEL_INFO, "[SPI] bus_speed_khz                 = 0x%08x\n", pClk->bus_speed_khz);
  SPI_LOG(LEVEL_INFO, "[SPI] clk_div                 = 0x%08x\n", pClk->clk_div);

  ON_EXIT:
  return ret_value;

}
*/
static boolean validate_qup_configurations(spi_plat_device_config *dcfg)
{
    boolean is_valid = TRUE;

    if(!dcfg)
    {
      return FALSE;
    }

    switch(dcfg->qupv3_instance)
    {
      case QUP_0:
        if( ((uint32*) dcfg->core_base_addr != (uint32*)QUP0_BASE_ADDRESS_START) ||
            ((uint32*) dcfg->common_base_addr != (uint32*) QUP0_COMMON_ADDRESS) ||
            ( dcfg->core_offset > (QUP0_BASE_ADDRESS_END - QUP0_BASE_ADDRESS_START)) )
        {
          is_valid = FALSE;
	    }
        break;

      case QUP_1:
        if( ((uint32*) dcfg->core_base_addr != (uint32*) QUP1_BASE_ADDRESS_START)||
            ((uint32*) dcfg->common_base_addr != (uint32*) QUP1_COMMON_ADDRESS)  ||
            ( dcfg->core_offset > (QUP1_BASE_ADDRESS_END - QUP1_BASE_ADDRESS_START)) )
        {
          is_valid = FALSE;
        }
        break;

      case QUP_2:
        if( ((uint32*) dcfg->core_base_addr != (uint32*) QUP2_BASE_ADDRESS_START)||
            ((uint32*) dcfg->common_base_addr != (uint32*) QUP2_COMMON_ADDRESS)  ||
            ( dcfg->core_offset > (QUP2_BASE_ADDRESS_END - QUP2_BASE_ADDRESS_START)) )
        {
          is_valid = FALSE;
	    }
        break;

      default:
        is_valid = FALSE;
		break;
    }

    if(is_valid)
    {
      if( ((uint32*) dcfg->tcsr_base_addr != (uint32*) TCSR_TCSR_REG_ADDRESS_START) ||
          ( dcfg->tcsr_reg_offset > (TCSR_TCSR_REG_ADDRESS_END - TCSR_TCSR_REG_ADDRESS_START)) )
      {
        is_valid = FALSE;
      }
    }

    return is_valid;
}

spi_plat_device_config *spi_plat_get_device_config (uint8 core_index)
{
    spi_plat_device_config              *dcfg  = NULL;
    void* blob = NULL;
    int ret_value = -1;
    fdt_node_handle hNode;
    uint32 size =0;

    char dev_name[DT_NODE_BUF_SIZE];

    uint32* ptr = NULL;
    uint32* ptr_cnt = NULL;

    ret_value = fdt_get_node_handle(&hNode, blob, SPI_NODE_NAME);
    SPI_DT_CHECK_ERROR("Unable to get node handle for soc/spi");

    snprintf(dev_name, DT_NODE_BUF_SIZE, "%s%d", SPI_DEVICE_CONFIG_NODE, core_index+1);


    ret_value = fdt_get_node_handle(&hNode, blob, dev_name);
    SPI_DT_CHECK_ERROR("Unable to get SPI device config handle");

    dcfg = spi_plat_sys_mem_alloc(sizeof(spi_plat_device_config));

    if(!dcfg)
    {
      ret_value = -1;
      goto ON_EXIT;
    }

    DALSYS_memset((void *)dcfg, 0, sizeof(spi_plat_device_config));
    
    
    ret_value = fdt_get_uint32_prop(&hNode, "core_base_addr", (uint32 *)&dcfg->core_base_addr);
    SPI_DT_CHECK_ERROR("Unable to get core_base_addr");
    
    ret_value = fdt_get_uint32_prop(&hNode, "common_base_addr", (uint32 *)&dcfg->common_base_addr);
    SPI_DT_CHECK_ERROR("Unable to get common_base_addr");
    
    ret_value = fdt_get_uint32_prop(&hNode, "core_offset", (uint32 *)&dcfg->core_offset);
    SPI_DT_CHECK_ERROR("Unable to get core_offset");
    
    ret_value = fdt_get_uint8_prop(&hNode, "qupv3_instance", (uint8 *)&dcfg->qupv3_instance);
    SPI_DT_CHECK_ERROR("Unable to get qupv3_instance");
    
    ret_value = fdt_get_uint8_prop(&hNode, "core_index", (uint8 *)&dcfg->core_index);
    SPI_DT_CHECK_ERROR("Unable to get core_index");
    
    ret_value = fdt_get_uint8_prop(&hNode, "se_index", (uint8 *)&dcfg->se_index);
    SPI_DT_CHECK_ERROR("Unable to get se_index");
    
    ret_value = fdt_get_uint32_prop(&hNode, "core_irq", (uint32 *)&dcfg->core_irq);
    SPI_DT_CHECK_ERROR("Unable to get core_irq");
    
    ret_value = fdt_get_uint8_prop(&hNode, "polled_mode", (uint8 *)&dcfg->polled_mode);
    SPI_DT_CHECK_ERROR("Unable to get polled_mode");
    
    ret_value = fdt_get_uint32_prop(&hNode, "min_data_length_for_dma", (uint32 *)&dcfg->min_data_length_for_dma);
    SPI_DT_CHECK_ERROR("Unable to get min_data_length_for_dma");
    
    ret_value = fdt_get_uint8_prop(&hNode, "gpi_index", (uint8 *)&dcfg->gpi_index);
    SPI_DT_CHECK_ERROR("Unable to get gpi_index");
    
    ret_value = fdt_get_uint8_prop(&hNode, "se_clock_dfs_index", (uint8 *)&dcfg->se_clock_dfs_index);
    SPI_DT_CHECK_ERROR("Unable to get se_clock_dfs_index");
    
    ret_value = fdt_get_uint32_prop(&hNode, "se_clock_frequency", (uint32 *)&dcfg->se_clock_frequency);
    SPI_DT_CHECK_ERROR("Unable to get se_clock_frequency");
    
    ret_value = fdt_get_uint32_prop(&hNode, "miso_encoding", (uint32 *)&dcfg->miso_encoding);
    SPI_DT_CHECK_ERROR("Unable to get miso_encoding");
    
    ret_value = fdt_get_uint32_prop(&hNode, "mosi_encoding", (uint32 *)&dcfg->mosi_encoding);
    SPI_DT_CHECK_ERROR("Unable to get mosi_encoding");
    
    ret_value = fdt_get_uint32_prop(&hNode, "cs_encoding", (uint32 *)&dcfg->cs_encoding);
    SPI_DT_CHECK_ERROR("Unable to get cs_encoding");
    
    ret_value = fdt_get_uint32_prop(&hNode, "clk_encoding", (uint32 *)&dcfg->clk_encoding);
    SPI_DT_CHECK_ERROR("Unable to get clk_encoding");
    
    ret_value = fdt_get_uint32_prop(&hNode, "tcsr_base_addr", (uint32 *)&dcfg->tcsr_base_addr);
    SPI_DT_CHECK_ERROR("Unable to get tcsr_base_addr");
    
    ret_value = fdt_get_uint32_prop(&hNode, "tcsr_reg_offset", (uint32 *)&dcfg->tcsr_reg_offset);
    SPI_DT_CHECK_ERROR("Unable to get tcsr_reg_offset");
    
    ret_value = fdt_get_uint32_prop(&hNode, "tcsr_reg_value", (uint32 *)&dcfg->tcsr_reg_value);
    SPI_DT_CHECK_ERROR("Unable to get tcsr_reg_value");
    
    if( !validate_qup_configurations(dcfg) )
    {
      ret_value = -1;
      goto ON_EXIT;
    }

    dcfg->se_clock = spi_plat_sys_mem_alloc(sizeof(uint8*));

    if(!dcfg->se_clock)
    {
      ret_value = -1;
      goto ON_EXIT;
    }

    DALSYS_memset((void *)dcfg->se_clock, 0, sizeof(uint8*));

    ret_value = fdt_get_prop_size(&hNode, "se_clock", &size);
    SPI_DT_CHECK_ERROR("Unable to get sizeof se_clock");

    *(dcfg->se_clock) = spi_plat_sys_mem_alloc(size+1);
    if(! *(dcfg->se_clock))
    {
      ret_value = -1;
      goto ON_EXIT;
    }
    DALSYS_memset((void *)*(dcfg->se_clock), 0, (size+1));

    ret_value = fdt_get_string_prop_list(&hNode, "se_clock", (void *)*(dcfg->se_clock), size);
    SPI_DT_CHECK_ERROR("Unable to get string list in se_clock");



    dcfg->common_clocks = spi_plat_sys_mem_alloc((MAX_SPI_COMMON_CLK_CNT + 1) * sizeof(uint8*));
    if(!(dcfg->common_clocks))
    {
      ret_value = -1;
      goto ON_EXIT;
    }

    DALSYS_memset((void *)dcfg->common_clocks, 0, (MAX_SPI_COMMON_CLK_CNT + 1 ) * sizeof(uint8*));

    if (spi_fetch_common_clock(dcfg) != SPI_SUCCESS)
    {
      ret_value = -1;
      goto ON_EXIT;
    }

    dcfg->clock_config = spi_plat_sys_mem_alloc(MAX_SPI_FREQ_CNT * sizeof (spi_plat_clock_config));

    if(!dcfg->clock_config)
    {
      ret_value = -1;
        goto ON_EXIT;
    }
    DALSYS_memset((void *)dcfg->clock_config, 0, (MAX_SPI_FREQ_CNT * sizeof (spi_plat_clock_config)));

    spi_fetch_clk_cfg(dcfg);



	SPI_LOG(LEVEL_INFO, "[SPI] core_base_addr           = 0x%08x\n", dcfg->core_base_addr);
    SPI_LOG(LEVEL_INFO, "[SPI] common_base_addr         = 0x%08x\n", dcfg->common_base_addr);
	SPI_LOG(LEVEL_INFO, "[SPI] core_offset              = 0x%08x\n", dcfg->core_offset);
    SPI_LOG(LEVEL_INFO, "[SPI] qupv3_instance           = 0x%08x\n", dcfg->qupv3_instance);
    SPI_LOG(LEVEL_INFO, "[SPI] core_index               = 0x%08x\n", dcfg->core_index);
    SPI_LOG(LEVEL_INFO, "[SPI] core_irq                 = 0x%08x\n", dcfg->core_irq);
    SPI_LOG(LEVEL_INFO, "[SPI] polled_mode              = 0x%08x\n", dcfg->polled_mode);
    SPI_LOG(LEVEL_INFO, "[SPI] min_data_length_for_dma  = 0x%08x\n", dcfg->min_data_length_for_dma);
    SPI_LOG(LEVEL_INFO, "[SPI] gpi_index                = 0x%08x\n", dcfg->gpi_index);
    SPI_LOG(LEVEL_INFO, "[SPI] tcsr_base_addr           = 0x%08x\n", dcfg->tcsr_base_addr);
    SPI_LOG(LEVEL_INFO, "[SPI] tcsr_reg_offset          = 0x%08x\n", dcfg->tcsr_reg_offset);
    SPI_LOG(LEVEL_INFO, "[SPI] tcsr_reg_value           = 0x%08x\n", dcfg->tcsr_reg_value);
    SPI_LOG(LEVEL_INFO, "[SPI] clock_config             = 0x%08x\n", dcfg->clock_config);
	
ON_EXIT:
  if (ret_value)
  {
    if(dcfg)
    {
      spi_plat_release_device_config(dcfg);
      dcfg = NULL;
    }
  }
  if (ptr_cnt)
  {
    spi_plat_sys_mem_dealloc(ptr_cnt);
  }

  if(ptr)
  {
    spi_plat_sys_mem_dealloc(ptr);
  }

    return dcfg;
}

void spi_plat_release_device_config (spi_plat_device_config *dcfg)
{
    if(dcfg)
    {
      if(dcfg->common_clocks)
      {
        spi_plat_sys_mem_dealloc(dcfg->common_clocks);
      }
      if(dcfg->se_clock)
      {
        if(*(dcfg->se_clock))
        {
          spi_plat_sys_mem_dealloc(*(dcfg->se_clock));
        }
        spi_plat_sys_mem_dealloc(dcfg->se_clock);
      }
      if(dcfg->clock_config)
      {
        spi_plat_sys_mem_dealloc(dcfg->clock_config);
      }
      spi_plat_sys_mem_dealloc(dcfg);
    }

  return;

}

