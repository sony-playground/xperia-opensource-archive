#ifndef __PCIE_PORT_INFO_H__
#define __PCIE_PORT_INFO_H__

/**
  @file pcie_port_info.h
  @brief Public interface include file to get the PCIe port info.

*/
/*
===============================================================================

                             Edit History


  when       who     what, where, why
  --------   ---     ------------------------------------------------------------
  09/14/20   Yg      Created

===============================================================================
                   Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/
#include "pcie_host.h"
#include "Library/pcie_dtypes.h"

pcie_status_t pcie_get_device_port_index (pcie_device_port_type dev_type, uint32 *port_ptr);

#endif //__PCIE_PORT_INFO_H__

