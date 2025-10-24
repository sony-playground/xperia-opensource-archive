/**
  @file pcie_rp_cfg_data.c
  @brief Pcie Root Port configuration instance for the target

  This file implements QC specific PCIe root port controller configuration
===============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
===============================================================================
*/

#include "pcie_hwio_base.h"
#include "pcie_cfg_types.h"
#include "pcie_host_log.h"
#include "pcie_osal.h"
#include "Library/pcie_rp.h"
#include "pcie_rp_cfg_svc.h"

#define STR_ID(a,b,c,d)     (a | (b << 8) | (c << 16) | (d << 24))

/*******************************************************************************
 *               Kailua port configurations for public
 ******************************************************************************/
extern const pcie_port_config_t kailua_port_0_cfg[];
extern const pcie_port_config_t kailua_port_1_cfg[];

extern const uint8_t kailua_port_0_cfg_len;
extern const uint8_t kailua_port_1_cfg_len;

pcie_port_options_config_t kailua_target_port_options[] = 
{
   {
      .port_config_name = "P0x2Gen3",
      .exclusive_key = STR_ID('x', '2', 'G', '3'),
      .default_enable = 1,   // No HW conditional, so enable it by default
      .config_select_condition = NULL,
      .ports_config_cnt = &kailua_port_0_cfg_len,
      .ports_config_list = kailua_port_0_cfg,
   },

   {
      .port_config_name = "P1x2Gen4",
      .exclusive_key = STR_ID('x', '2', 'G', '4'),
      .default_enable = 1,   // No HW conditional, so enable it by default
      .config_select_condition = NULL,
      .ports_config_cnt = &kailua_port_1_cfg_len,
      .ports_config_list = kailua_port_1_cfg,
   },
};

static mem_region_t kailua_target_common_mem_regions[] =
{
  /* TCSR register space */
//  {.pa=TCSR_TCSR_REGS_REG_BASE, .sz=TCSR_TCSR_REGS_REG_BASE_SIZE},
  {.pa=0, .sz=0},
};

#define TARGET_MAX_PORT_INDEX    1

pcie_target_config_t kailua_pcie_rp_cfg_data = 
{
//    .config_data_version = PCIE_CONFIG_DATA_VERSION,
    .target_chip_id = PCIE_TARGET_CHIP_ID_IGNORE,
    .target_chip_family = EFICHIPINFO_FAMILY_KAILUA,    //  Kailua family
    .target_platform_type = 0, // EFI_PLATFORMINFO_TYPE_CDP,  //   CDP

    .target_port_option_cnt = ARRAY_LENGTH(kailua_target_port_options),
    .target_port_option_list = kailua_target_port_options,
    .entp_mgmt_addr = 0, //(const uint32*)HWIO_ENTP_MGMT2_PCIE_EN_ADDR,
    .max_port_index = TARGET_MAX_PORT_INDEX,
    .common_mem_regions = kailua_target_common_mem_regions,
};

pcie_status_t kailua_pcie_rp_set_hw_port_lanes_config (uint32 port, uint32 option)
{
   return PCIE_SUCCESS;
}

pcie_status_t kailua_pcie_rp_set_default_target_config (uint32 option)
{
   return PCIE_SUCCESS;
}
