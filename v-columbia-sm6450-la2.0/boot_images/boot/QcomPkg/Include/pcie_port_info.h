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
                   Copyright (c) 2020 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/
#include "pcie_host.h"

typedef enum
{
   PCIE_PRIMARY_BOOT_DEVICE = 0,
   PCIE_ALTERNATE_BOOT_DEVICE = 1,

   PCIE_DEVICE_PORT_MAX = 2,
}pcie_device_port_type;

pcie_status_t pcie_get_device_port_index (pcie_device_port_type dev_type, uint32 *port_ptr);

#endif //__PCIE_PORT_INFO_H__

