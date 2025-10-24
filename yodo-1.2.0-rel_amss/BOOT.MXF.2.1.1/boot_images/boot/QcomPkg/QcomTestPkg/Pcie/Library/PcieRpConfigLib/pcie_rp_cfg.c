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

#include "pcie_cfg_types.h"

extern pcie_target_config_t kailua_pcie_rp_cfg_data;
extern pcie_target_config_t hamoa_pcie_rp_cfg_data;

pcie_target_config_t *pcie_tgt_config_ptrs[] = 
{
   &kailua_pcie_rp_cfg_data,
   &hamoa_pcie_rp_cfg_data,
};

uint32 pcie_tgt_config_ptr_cnt = ARRAY_SIZE(pcie_tgt_config_ptrs);


