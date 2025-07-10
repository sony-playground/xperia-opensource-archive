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
   03/07/22   Ps      Fillmore specific cfg data separated from other tgt
   01/03/22   Ps      Support for multiple targets
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
#include "rp_cfg.h"
#include "Library/pcie_rp.h"
#include "pcie_rp_cfg_svc.h"

pcie_target_config_t fillmore_pcie_tgt_config_data = 
{ 
    .config_data_version = PCIE_CONFIG_DATA_VERSION,
    .target_chip_id = PCIE_TARGET_CHIP_ID_IGNORE,
    .target_chip_family = EFICHIPINFO_FAMILY_FILLMORE,
    .target_platform_type = 0, // EFI_PLATFORMINFO_TYPE_CDP,  //   CDP

    .target_port_option_cnt = ARRAY_LENGTH(fillmore_target_port_options),
    .target_port_option_list = fillmore_target_port_options,
    .entp_mgmt_addr = 0,
    .max_port_index = TARGET_MAX_PORT_INDEX,
    .common_mem_regions = NULL, 
};

