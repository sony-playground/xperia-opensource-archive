/** 
    @file  i2c_config.c
    @brief device configuration implementation
 */
/*=============================================================================
            Copyright (c) 2017, 2021, 2022 Qualcomm Technologies, Incorporated.
                              All rights reserved.
              Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

#include "i2c_plat.h"
#include "DALSys.h"
#include "i2c_api.h"
#include "i2c_log.h"    // logging
#include "DTBExtnLib.h"
#include "string.h"
#include "stdio.h"
#include "qup_address_ranges.h"

#define I2C_NODE_NAME       "/soc/i2c"

/* I2C device config node  */
#define I2C_DEVICE_CONFIG_NODE     "/soc/i2c/i2c_device_config_"
#define DT_NODE_BUF_SIZE 100

#define I2C_DT_CHECK_ERROR(x)                                         \
{                                                                     \
    if (ret_value) {                                                  \
      I2C_LOG(LEVEL_ERROR, "%s, ret Value = %d\n", u##x, ret_value);  \
      goto ON_EXIT;                                                   \
    }                                                                 \
}

#define I2C_MAX_CLK_CFG_COUNT 20

int i2c_read_clk_cfg(void *fdt_handle, char *node, plat_clock_config *pClk)
{
  int ret_value;
  fdt_node_handle hNode;


  ret_value = fdt_get_node_handle(&hNode, fdt_handle, node);
  I2C_DT_CHECK_ERROR("Unable to get node handle");

  ret_value = fdt_get_uint32_prop(&hNode, "se_clock_frequency_khz", (uint32 *)&pClk->se_clock_frequency_khz);
  I2C_DT_CHECK_ERROR("Unable to get se_clock_frequency_khz");
  ret_value = fdt_get_uint32_prop(&hNode, "bus_speed_khz", (uint32 *)&pClk->bus_speed_khz);
  I2C_DT_CHECK_ERROR("Unable to get bus_speed_khz");
  ret_value = fdt_get_uint8_prop(&hNode, "clk_div", (uint8 *)&pClk->clk_div);
  I2C_DT_CHECK_ERROR("Unable to get clk_div");
  ret_value = fdt_get_uint8_prop(&hNode, "t_cycle", (uint8 *)&pClk->t_cycle);
  I2C_DT_CHECK_ERROR("Unable to get t_cycle");
  ret_value = fdt_get_uint8_prop(&hNode, "t_high", (uint8 *)&pClk->t_high);
  I2C_DT_CHECK_ERROR("Unable to get t_high");
  ret_value = fdt_get_uint8_prop(&hNode, "t_low", (uint8 *)&pClk->t_low);
  I2C_DT_CHECK_ERROR("Unable to get t_low");

  I2C_LOG(LEVEL_INFO, "[I2C] se_clock_frequency_khz        = 0x%08x\n", pClk->se_clock_frequency_khz);
  I2C_LOG(LEVEL_INFO, "[I2C] bus_speed_khz                 = 0x%08x\n", pClk->bus_speed_khz);
  I2C_LOG(LEVEL_INFO, "[I2C] clk_div                 = 0x%08x\n", pClk->clk_div);
  I2C_LOG(LEVEL_INFO, "[I2C] t_cycle                 = 0x%08x\n", pClk->t_cycle);
  I2C_LOG(LEVEL_INFO, "[I2C] t_high                 = 0x%08x\n", pClk->t_high);
  I2C_LOG(LEVEL_INFO, "[I2C] t_low                 = 0x%08x\n", pClk->t_low);


  ON_EXIT:
    return ret_value;

}

static boolean validate_qup_configurations(plat_device_config *dcfg)
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

plat_device_config *plat_get_device_config (uint8 core_index)
{
    plat_device_config              *dcfg  = NULL;
    void* blob = NULL;
    int ret_value = -1;
    fdt_node_handle hNode, pNode, cNode;
    uint32 size =0;
    uint32 phandle =0;
    char dev_name[DT_NODE_BUF_SIZE];
    char* common_clock = NULL;
    char clk_cfg[DT_NODE_BUF_SIZE];
    char temp_buf[DT_NODE_BUF_SIZE];
    uint32 count =0;
    uint32* ptr = NULL;
    uint32* ptr_cnt = NULL;
    

    ret_value = fdt_get_blob_handle(&blob, DEFAULT_BLOB_ID);
    I2C_DT_CHECK_ERROR("Unable to get blob handle");

    ret_value = fdt_get_node_handle(&hNode, blob, I2C_NODE_NAME);
    I2C_DT_CHECK_ERROR("Unable to get node handle");

    snprintf(dev_name, DT_NODE_BUF_SIZE, "%s%d", I2C_DEVICE_CONFIG_NODE, core_index);


    ret_value = fdt_get_node_handle(&hNode, blob, dev_name);
    I2C_DT_CHECK_ERROR("Unable to get i2c device config handle");

    dcfg = plat_sys_mem_alloc(sizeof(plat_device_config));
    if(!dcfg)
    {
      ret_value = -1;
      goto ON_EXIT;
    }

    //ret_value = DALSYS_Malloc(sizeof(plat_device_config), (void *)&dcfg);

    DALSYS_memset((void *)dcfg, 0, sizeof(plat_device_config));

	

    ret_value = fdt_get_uint32_prop(&hNode, "core_base_addr", (uint32 *)&dcfg->core_base_addr);
    I2C_DT_CHECK_ERROR("Unable to get core_base_addr");

    ret_value = fdt_get_uint32_prop(&hNode, "common_base_addr", (uint32 *)&dcfg->common_base_addr);
    I2C_DT_CHECK_ERROR("Unable to get common_base_addr");

    ret_value = fdt_get_uint32_prop(&hNode, "core_offset", (uint32 *)&dcfg->core_offset);
    I2C_DT_CHECK_ERROR("Unable to get core_offset");

    ret_value = fdt_get_uint8_prop(&hNode, "qupv3_instance", (uint8 *)&dcfg->qupv3_instance);
    I2C_DT_CHECK_ERROR("Unable to get qupv3_instance");

    ret_value = fdt_get_uint8_prop(&hNode, "core_index", (uint8 *)&dcfg->core_index);
    I2C_DT_CHECK_ERROR("Unable to get core_index");

    ret_value = fdt_get_uint8_prop(&hNode, "se_index", (uint8 *)&dcfg->se_index);
    I2C_DT_CHECK_ERROR("Unable to get se_index");

    ret_value = fdt_get_uint32_prop(&hNode, "core_irq", (uint32 *)&dcfg->core_irq);
    I2C_DT_CHECK_ERROR("Unable to get core_irq");

    ret_value = fdt_get_uint32_prop(&hNode, "polled_mode", (uint32 *)&dcfg->polled_mode);
    I2C_DT_CHECK_ERROR("Unable to get polled_mode");

    ret_value = fdt_get_uint32_prop(&hNode, "min_data_length_for_dma", (uint32 *)&dcfg->min_data_length_for_dma);
    I2C_DT_CHECK_ERROR("Unable to get min_data_length_for_dma");

    ret_value = fdt_get_uint8_prop(&hNode, "gpi_index", (uint8 *)&dcfg->gpi_index);
    I2C_DT_CHECK_ERROR("Unable to get gpi_index");

    ret_value = fdt_get_uint32_prop(&hNode, "scl_encoding", (uint32 *)&dcfg->scl_encoding);
    I2C_DT_CHECK_ERROR("Unable to get scl_encoding");

    ret_value = fdt_get_uint32_prop(&hNode, "sda_encoding", (uint32 *)&dcfg->sda_encoding);
    I2C_DT_CHECK_ERROR("Unable to get sda_encoding");

    ret_value = fdt_get_uint32_prop(&hNode, "tcsr_base_addr", (uint32 *)&dcfg->tcsr_base_addr);
    I2C_DT_CHECK_ERROR("Unable to get tcsr_base_addr");

    ret_value = fdt_get_uint32_prop(&hNode, "tcsr_reg_offset", (uint32 *)&dcfg->tcsr_reg_offset);
    I2C_DT_CHECK_ERROR("Unable to get tcsr_reg_offset");

    ret_value = fdt_get_uint32_prop(&hNode, "tcsr_reg_value", (uint32 *)&dcfg->tcsr_reg_value);
    I2C_DT_CHECK_ERROR("Unable to get tcsr_reg_value");

    if( !validate_qup_configurations(dcfg) )
    {
      ret_value = -1;
      goto ON_EXIT;
    }

    dcfg->se_clock = plat_sys_mem_alloc(sizeof(uint8*));

    if(!dcfg->se_clock)
    {
      ret_value = -1;
      goto ON_EXIT;
    }

    DALSYS_memset((void *)dcfg->se_clock, 0, sizeof(uint8*));

    ret_value = fdt_get_prop_size(&hNode, "se_clock", &size);
    I2C_DT_CHECK_ERROR("Unable to get size of se_clock");

    *(dcfg->se_clock) = plat_sys_mem_alloc(size+1);
    if(! *(dcfg->se_clock))
    {
      ret_value = -1;
      goto ON_EXIT;
    }
    DALSYS_memset((void *)*(dcfg->se_clock), 0, (size+1));

    ret_value = fdt_get_string_prop_list(&hNode, "se_clock", (void *)*(dcfg->se_clock), size);

    I2C_DT_CHECK_ERROR("Unable to get string list in se_clock");

    ret_value = fdt_get_uint32_prop(&hNode, "common_clocks", &phandle);
    I2C_DT_CHECK_ERROR("Unable to get common clocks ");

    ret_value = fdt_get_phandle_node(&hNode, phandle, &pNode);
    I2C_DT_CHECK_ERROR("Unable to get phandle node ");

    ret_value = fdt_get_prop_size(&pNode, "clocks", &size);
    I2C_DT_CHECK_ERROR("Unable to get node clocks size");

    common_clock = plat_sys_mem_alloc(size+1);
    if(!common_clock)
    {
      ret_value = -1;
      goto ON_EXIT;
    }

    DALSYS_memset((void *)common_clock, 0, (size+1));

    ret_value = fdt_get_string_prop_list(&pNode, "clocks", (void *)common_clock, size);
    I2C_DT_CHECK_ERROR("Unable to get common clock list");

    uint32 i =0, len= 0, clock_len =0;
    uint32 comn_clk_count = 0;
    char* walk = common_clock;

    while(len <size )
    {
      clock_len = strlen(walk);

      len+= clock_len + 1;
      walk+= clock_len + 1;
      comn_clk_count++;
    }

    dcfg->common_clocks = plat_sys_mem_alloc((comn_clk_count + 1) * sizeof(uint8*));
    if(!(dcfg->common_clocks))
    {
      ret_value = -1;
      goto ON_EXIT;
    }

    DALSYS_memset((void *)dcfg->common_clocks, 0, (comn_clk_count + 1 ) * sizeof(uint8*));

    len =0;
    walk = common_clock;
    while(len <size )
    {
      clock_len = strlen(walk);

      dcfg->common_clocks[i] = (uint8 *)walk;

      len+= clock_len + 1;
      walk+= clock_len + 1;
      i++;
    }

    dcfg->common_clocks[i] = NULL;

    walk = NULL;

    snprintf(clk_cfg, DT_NODE_BUF_SIZE, "%s/clock_config", I2C_NODE_NAME);
    ret_value = fdt_get_node_handle(&cNode, blob, clk_cfg);
    I2C_DT_CHECK_ERROR("Unable to get node handle for clock config ");

    ret_value = fdt_get_count_of_subnodes(&cNode, &count);
    I2C_DT_CHECK_ERROR("Unable to get count of nodes for clock config ");
    
    
    if(count > I2C_MAX_CLK_CFG_COUNT)
    {
      ret_value = -1;
      goto ON_EXIT;
    }

    ptr_cnt = plat_sys_mem_alloc(count * sizeof(uint32));

    if(!ptr_cnt)
    {
      ret_value = -1;
        goto ON_EXIT;
    }
    DALSYS_memset((void *)ptr_cnt, 0, (count * sizeof(uint32)));

    dcfg->clock_config = plat_sys_mem_alloc(count * sizeof (plat_clock_config));

    if(!dcfg->clock_config)
    {
      ret_value = -1;
        goto ON_EXIT;
    }
    DALSYS_memset((void *)dcfg->clock_config, 0, (count * sizeof (plat_clock_config)));

    ret_value = fdt_get_size_of_subnode_names(&cNode, ptr_cnt, count);
    I2C_DT_CHECK_ERROR("Unable to get size of subnode names ");

    for (i=0,size=0; i<count; i++)
    {
      size += ptr_cnt[i];
    }

    ptr = plat_sys_mem_alloc(size);

    if(!ptr)
    {
      ret_value = -1;
        goto ON_EXIT;
    }

    DALSYS_memset((void *)ptr, 0, size);
    walk = (char *)ptr;

    ret_value = fdt_get_subnode_names(&cNode, ptr, size);
    I2C_DT_CHECK_ERROR("get submode names failed");

    for (i=0; i<count; i++)
    {
      int walk_len = strlen(walk) + 1;

      snprintf(temp_buf, DT_NODE_BUF_SIZE, "%s/%s", clk_cfg, walk);
      ret_value = i2c_read_clk_cfg(blob, temp_buf, &dcfg->clock_config[i]);
      I2C_DT_CHECK_ERROR("i2c_read_clk_cfg failed");

      // Next node
      walk += walk_len;
    }

	I2C_LOG(LEVEL_INFO, "[I2C] core_base_addr           = 0x%08x\n", dcfg->core_base_addr);
    I2C_LOG(LEVEL_INFO, "[I2C] common_base_addr         = 0x%08x\n", dcfg->common_base_addr);
	I2C_LOG(LEVEL_INFO, "[I2C] core_offset              = 0x%08x\n", dcfg->core_offset);
    I2C_LOG(LEVEL_INFO, "[I2C] qupv3_instance           = 0x%08x\n", dcfg->qupv3_instance);
    I2C_LOG(LEVEL_INFO, "[I2C] core_index               = 0x%08x\n", dcfg->core_index);
    I2C_LOG(LEVEL_INFO, "[I2C] core_irq                 = 0x%08x\n", dcfg->core_irq);
    I2C_LOG(LEVEL_INFO, "[I2C] polled_mode              = 0x%08x\n", dcfg->polled_mode);
    I2C_LOG(LEVEL_INFO, "[I2C] min_data_length_for_dma  = 0x%08x\n", dcfg->min_data_length_for_dma);
    I2C_LOG(LEVEL_INFO, "[I2C] gpi_index                = 0x%08x\n", dcfg->gpi_index);
    I2C_LOG(LEVEL_INFO, "[I2C] scl_encoding             = 0x%08x\n", dcfg->scl_encoding);
    I2C_LOG(LEVEL_INFO, "[I2C] sda_encoding             = 0x%08x\n", dcfg->sda_encoding);
    I2C_LOG(LEVEL_INFO, "[I2C] tcsr_base_addr           = 0x%08x\n", dcfg->tcsr_base_addr);
    I2C_LOG(LEVEL_INFO, "[I2C] tcsr_reg_offset          = 0x%08x\n", dcfg->tcsr_reg_offset);
    I2C_LOG(LEVEL_INFO, "[I2C] tcsr_reg_value           = 0x%08x\n", dcfg->tcsr_reg_value);
    I2C_LOG(LEVEL_INFO, "[I2C] clock_config             = 0x%08x\n", dcfg->clock_config);
	
ON_EXIT:
  if (ret_value)
  {
    if(dcfg)
    {
      plat_release_device_config(dcfg);
      dcfg = NULL;
    }
  }
  if (ptr_cnt)
  {
    plat_sys_mem_dealloc(ptr_cnt);
  }

  if(ptr)
  {
    plat_sys_mem_dealloc(ptr);
  }
    return dcfg;
}

void plat_release_device_config (plat_device_config *dcfg)
{

  if(dcfg)
  {
    if(dcfg->common_clocks)
    {
      if(*(dcfg->common_clocks))
      {
        plat_sys_mem_dealloc(*(dcfg->common_clocks));
      }
      plat_sys_mem_dealloc(dcfg->common_clocks);
    }

    if(dcfg->se_clock)
    {
      if(*(dcfg->se_clock))
      {
        plat_sys_mem_dealloc(*(dcfg->se_clock));
      }
      plat_sys_mem_dealloc(dcfg->se_clock);
    }
    if(dcfg->clock_config)
    {
      plat_sys_mem_dealloc(dcfg->clock_config);
    }
    plat_sys_mem_dealloc(dcfg);
  }
}

