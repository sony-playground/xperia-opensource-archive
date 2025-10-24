#ifndef __PCIE_CAP_CONFIG_UTILS_H___
#define __PCIE_CAP_CONFIG_UTILS_H___
/*
 *  pcie_cap_config_utils.h
 *
 *  PCIe Capability configuration utility interface
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   10/20/20   Yg      Created new

*/
/*============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                 All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
============================================================================*/

#include <Uefi.h>
#include "pcie_dtypes.h"
#include "pcie_cfg_types.h"

// cap_config_utils also implements portions of pcie_rp.h interface related to capabilities
#include "pcie_rp.h"

/* Disable MSI's */
pcie_status_t pcie_cap_disable_MSIs (uint32 port_index);

/* Get link stats */
pcie_status_t pcie_cap_get_link_stat (uint32 port_index, uint32* widthp, uint32* speedp);

#endif    /* __PCIE_CAP_CONFIG_UTILS_H___ */

