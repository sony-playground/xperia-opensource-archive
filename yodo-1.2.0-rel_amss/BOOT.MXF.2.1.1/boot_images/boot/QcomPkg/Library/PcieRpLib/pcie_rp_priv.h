#ifndef __PCIE_RP_PRIV_H___
#define __PCIE_RP_PRIV_H___
/*
 *  pcie_rp_priv.h
 *
 *  PCIe root port internal private shared API's interface
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   08/02/21   Yg      Created New

*/
/*============================================================================
               Copyright (c) 2021 - 2022 Qualcomm Technologies, Inc.
                 All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/


#include "pcie_dtypes.h"
#include "pcie_rp.h"
#include "pcie_cfg_types.h"

/* Get port config */
const pcie_port_config_t * pcie_rp_get_port_config (uint32 port_index);

const mem_region_t * pcie_rp_get_port_mem_config (uint32 port_index);

/* Get port handle required for the APIs that require it */
pcie_rp_handle* pcie_rp_get_port_handle (uint32 port_index);

uint32 pcie_rp_get_ltr_th_scale (uint32 port_index);
uint32 pcie_rp_get_ltr_th_val (uint32 port_index);


#endif    /* __PCIE_RP_PRIV_H___ */

