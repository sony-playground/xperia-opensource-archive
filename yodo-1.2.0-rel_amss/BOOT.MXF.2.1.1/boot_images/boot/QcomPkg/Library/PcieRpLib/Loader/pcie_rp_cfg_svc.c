/**

  This file implements QC specific PCIe root port controller configuration

         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
*/

#include "pcie_rp_cfg_svc.h"
#include "pcie_host_log.h"
#include "pcie_osal.h"
#include "string.h"

extern const pcie_port_options_config_t loader_port_options;

/* Keep default values as enabled, code had dependency on this. These are
 * bitwise fields cached in memory for ease of access and eval */
static uint32 pcie_available_ports = 0;

const uint32_t max_ports_count;

#ifndef MAX_SUPPORTED_PORTS_CFG
#define MAX_SUPPORTED_PORTS_CFG     8
#endif

static const pcie_port_config_t* enabled_ports_config[MAX_SUPPORTED_PORTS_CFG];

/******************************************************************************
 *         Private functions
 ******************************************************************************/
static uint32 set_reg_val_data (const pcie_reg_field_val_t* reg_spec)
{
   uint32 rval, new_val, mask;
   volatile uint32* reg_addr;

   /* If Reg_spec is not given then we can consider condition failed
    * might simplify caller's code */
   if (reg_spec == NULL)
      return 0;

   reg_addr = (volatile uint32*)reg_spec->reg_base_addr;
   reg_addr += (reg_spec->reg_offset / sizeof (*reg_spec->reg_base_addr)); // Ptr math

   rval = *reg_addr;

   mask = reg_spec->fld_mask << reg_spec->fld_shift;
   mask = ~mask;

   rval = rval & mask;

   new_val = reg_spec->fld_val;
   new_val = (new_val & reg_spec->fld_mask);
   new_val = new_val << reg_spec->fld_shift;

   rval = rval | new_val;

   *reg_addr = rval;

   return rval;
}

/******************************************************************************
 *         Public functions
 ******************************************************************************/
pcie_status_t pcie_rp_cfg_load_config (void)
{
   int i, rp_idx;
   const pcie_port_config_t* port_config_ptr;

   if (((uint64)loader_port_options.ports_config_list == 0)
         || (*(loader_port_options.ports_config_cnt) < 1))
      return PCIE_ERROR;

   port_config_ptr = loader_port_options.ports_config_list;

   set_reg_val_data (loader_port_options.config_select_condition);

   for (i = 0; i < *(loader_port_options.ports_config_cnt); ++i)
   {
      rp_idx = port_config_ptr[i].hw_rp_index;
      pcie_available_ports |= (1 << rp_idx);
      enabled_ports_config[rp_idx] = &port_config_ptr[i];
   }

   return PCIE_SUCCESS;
}

uint32 pcie_rp_cfg_get_max_port_count (void)
{
   return max_ports_count;
}

uint32 pcie_rp_cfg_get_enabled_ports_mask (void)
{
   uint32 enabled_ports;

   enabled_ports = pcie_available_ports;

   return enabled_ports;
}

pcie_status_t pcie_rp_cfg_get_config (uint32 rp_index, const pcie_port_config_t** rp_cfg_ptr)
{
   if ((rp_cfg_ptr == NULL) || (rp_index >= MAX_SUPPORTED_PORTS_CFG))
      return PCIE_INVALID_PARAM;

   *rp_cfg_ptr = NULL;

   if ((pcie_available_ports & (1 << rp_index)) == 0)
      return PCIE_NOT_FOUND;

   *rp_cfg_ptr = enabled_ports_config[rp_index];

   return PCIE_SUCCESS;
}

