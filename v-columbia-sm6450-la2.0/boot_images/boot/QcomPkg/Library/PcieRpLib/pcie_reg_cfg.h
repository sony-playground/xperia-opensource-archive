#ifndef __PCIE_REG_CONFIG_H__
#define __PCIE_REG_CONFIG_H__
/**
 *
 *  Defines the Pcie Register configuration utility interface
*/
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   10/20/20   Yg      Created new

===============================================================================
         Copyright (c) 2020 - 2021 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
===============================================================================
*/

#include "pcie_cfg_types.h"

/* Apply the register write configuration */
pcie_status_t apply_reg_write_seq (const pcie_reg_write_val_t* reg_wr_seq, void* base_addr);

/* Poll for a field to attain a required provided value, with poll duration and timeout value */
BOOLEAN pcie_poll_field_val (uint64 addr, uint32 mask, uint32 match_val, uint32 poll_us, uint32 timeout_ms);

/* Apply register initialization configuration with multiple sequences. */
pcie_status_t apply_reg_init_cfg (const pcie_reg_init_cfg_t* reg_cfg_spec, const mem_region_t* mem_rgn);

/* Apply register initialization sequence. Base addr here should be VA */
pcie_status_t apply_reg_init_seq (const pcie_reg_op_t* reg_seq, void* base_addr);

#define ASSERT_PERST_PIN       0
#define DEASSERT_PERST_PIN     1

/* Drive the pin logic level to given state */
pcie_status_t pcie_drive_gpio_pin (uint32 pin, uint32 val);

#endif   /* __PCIE_REG_CONFIG_H__ */

