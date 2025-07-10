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
   04/20/23   Ms      Porting Config for clarence target
   03/07/22   Ps      Config data separated for targets
   01/03/22   Ps      Support for multiple targets
   10/20/20   Yg      Created new

===============================================================================
         Copyright (c) 2020, 2022 - 2023 Qualcomm Technologies, Inc. 
                          All Rights Reserved.
          Confidential and Proprietary – Qualcomm Technologies, Inc.
===============================================================================
*/

#include "pcie_cfg_types.h"
#include "pcie_host_log.h"
#include "pcie_osal.h"
#include "Library/pcie_rp.h"
#include "pcie_rp_cfg_svc.h"


extern pcie_target_config_t fillmore_pcie_tgt_config_data;

extern pcie_target_config_t netrani_pcie_tgt_config_data;

extern pcie_target_config_t palima_pcie_tgt_config_data;

extern pcie_target_config_t waipio_pcie_tgt_config_data;

extern pcie_target_config_t clarence_pcie_tgt_config_data;

pcie_target_config_t *pcie_tgt_config_data[] = 
{
   &fillmore_pcie_tgt_config_data,
   &netrani_pcie_tgt_config_data,
   &palima_pcie_tgt_config_data,
   &waipio_pcie_tgt_config_data,
   &clarence_pcie_tgt_config_data,
};

uint32 pcie_tgt_config_data_cnt = ARRAY_SIZE(pcie_tgt_config_data);

pcie_status_t pcie_rp_set_hw_port_lanes_config (uint32 port, uint32 option)
{
   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_set_default_target_config (uint32 option)
{
   return PCIE_SUCCESS;
}

