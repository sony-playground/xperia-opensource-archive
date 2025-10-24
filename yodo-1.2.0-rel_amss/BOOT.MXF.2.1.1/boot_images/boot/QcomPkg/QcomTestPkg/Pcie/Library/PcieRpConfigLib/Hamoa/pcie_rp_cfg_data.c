/**
  @file pcie_rp_cfg_data.c
  @brief Pcie Root Port configuration instance for the target

  This file implements QC specific PCIe root port controller configuration

*/
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   10/20/20   Yg      Created new

===============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
===============================================================================
*/

#include "pcie_cfg_types.h"
#include "pcie_host_log.h"
#include "pcie_osal.h"
#include "PcieHwioRegs.h"
#include "rp_cfg.h"
#include "Library/pcie_rp.h"
#include "pcie_rp_cfg_svc.h"

pcie_target_config_t hamoa_pcie_rp_cfg_data = 
{
//    .config_data_version = PCIE_CONFIG_DATA_VERSION,
    .target_chip_id = PCIE_TARGET_CHIP_ID_IGNORE,
    .target_chip_family = EFICHIPINFO_FAMILY_MAKENA,    //  Makena family
    .target_platform_type = 0, // EFI_PLATFORMINFO_TYPE_CDP,  //   CDP

    .target_port_option_cnt = ARRAY_LENGTH(target_port_options),
    .target_port_option_list = target_port_options,
    .entp_mgmt_addr = (const uint32*)HWIO_ENTP_MGMT2_PCIE_EN_ADDR,
    .max_port_index = TARGET_MAX_PORT_INDEX,
    .common_mem_regions = target_common_mem_regions,
};

pcie_status_t pcie_rp_set_hw_port_lanes_config (uint32 port, uint32 option)
{
   const pcie_reg_field_val_t* reg_spec = NULL;
   pcie_status_t pstatus = PCIE_INVALID_PARAM;
   const char *cfg_name = NULL;

   if ((port >= 7) || (option > 4))
      return PCIE_INVALID_PARAM;

   if (port == PCIE_PORT_2A_INDEX)
   {
      if (option == 4)
         cfg_name = RP_CONFIG_2A_X4;
      else if (option == 2)
         cfg_name = RP_CONFIG_2A_X2;
   }

   if (port == PCIE_PORT_3A_INDEX)
   {
      if (option == 4)
         cfg_name = RP_CONFIG_3A_X4;
      else if (option == 2)
         cfg_name = RP_CONFIG_3A_X2;
   }

   if (cfg_name != NULL)
      pstatus = pcie_rp_cfg_get_hw_config_info (cfg_name, &reg_spec);

   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   if ((reg_spec != NULL) && (reg_spec->reg_base_addr != NULL))
   {
      uint32* reg_addr = (uint32*)((void*)reg_spec->reg_base_addr + reg_spec->reg_offset);
      uint32 reg_val = *reg_addr;
      uint32 mask, shift, new_val;

      mask = reg_spec->fld_mask;  // Mask is aligned to LSB, need to be shifted
      shift = reg_spec->fld_shift;

      new_val = reg_spec->fld_val;
      new_val = new_val & mask;
      new_val = new_val << shift;

      mask = mask << shift;
      reg_val = reg_val & (~(mask)); // Clear the value
      new_val = reg_val | new_val;

      pstatus = write_secure_tcsr_reg_val (reg_addr, new_val);
      if (pstatus != PCIE_SUCCESS)
         PCIE_HOST_LOG_ERROR ("Failed to set new HW Lane config reg val\r\n");
   }

   return pstatus;
}

pcie_status_t pcie_rp_set_default_target_config (uint32 option)
{
   pcie_status_t        pstatus;

   /* Based on HW board layout if the PCIe device is connected to 4 Lanes of 2A and or 3A
    * set that config, failing to do so will result into link failure. If 4 lane config
    * is not desired, then just disabling the upper lane controllers will make sure the
    * link comes up with just 2 lanes. */

   pstatus = pcie_rp_set_hw_port_lanes_config (PCIE_PORT_2A_INDEX, 4); // 2A 4 Lanes
   if (pstatus != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Failed to set Lane config for 2A\r\n");
      return pstatus;
   }

   pstatus = pcie_rp_set_hw_port_lanes_config (PCIE_PORT_3A_INDEX, 4); // 3A 4 Lanes
   if (pstatus != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Failed to set Lane config for 3A\r\n");
      return pstatus;
   }

   /* Disable 2B,3B since the hardware board has been connected as lanes for both 2A and 3A
    * so, B ports cannot be used. In this case if we do the following above TCSR reg value
    * wouldn't matter (but enumerating in 4 lanes requires that setting) if we just want
    * to enumerate in 2 lane configuration. */
//   pcie_rp_disable_port_config (PCIE_PORT_2B_INDEX);
//   pcie_rp_disable_port_config (PCIE_PORT_3B_INDEX); // Disable port if A option set to 2 Lane

   return PCIE_SUCCESS;
}

#include "pcie_port_info.h"

pcie_status_t pcie_get_device_port_index (pcie_device_port_type dev_type, uint32 *port_ptr)
{
    if ((port_ptr == NULL) || (dev_type >= PCIE_DEVICE_PORT_MAX))
	  return PCIE_INVALID_PARAM;
	  
	switch (dev_type)
	{
	case PCIE_PRIMARY_BOOT_DEVICE:
	   *port_ptr = 2;     // Port 2A
	   break;
	   
	case PCIE_ALTERNATE_BOOT_DEVICE:
	   *port_ptr = 4;     // Port 3A
	   break;

	default:
	   return PCIE_UNSUPPORTED;
	}
	
	return PCIE_SUCCESS;
}


