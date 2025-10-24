#ifndef __PCIE_TARGET_ROOT_PORT_CONFIG_SVC_H__
#define __PCIE_TARGET_ROOT_PORT_CONFIG_SVC_H__
/*

  PCIe configuration mgmt service interface
===============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
===============================================================================
*/

#include "com_dtypes.h"
#include "pcie_dtypes.h"
#include "pcie_cfg_types.h"

/* Root ports related configuration */

/*******************************************************************************
 *          Public API interface
 *******************************************************************************/


/*******************************************************************************
 *          Config service API's
 *  These API's only alter the port masks and config data structures available.
 *  Actual port init/deinit will need to be handled by the port mgmt services
 *******************************************************************************/

/* Initialize configuration sevice and load the default enabled port
 * configurations.
 * This API need to be called first before any other API's in this interface */
pcie_status_t pcie_rp_cfg_load_config (void);

/* Get the current selected configuration data version. Helps with managing
 * backward compatibility */
uint32 pcie_rp_cfg_get_version (void);

/* Get max root port count, this helps to enumerate through the ports to get
 * config data per port basis */
uint32 pcie_rp_cfg_get_max_port_count (void);

/* Get target chip family */
uint32 pcie_rp_cfg_get_target_chip_family (void);

/* Disable port by index */
pcie_status_t pcie_rp_cfg_disable_port (uint32 port_index);

/* Disable ports. This API can only disable an already enabled port
 * Any bit set to 1 will disable that port, 0 leaves unaffected */
pcie_status_t pcie_rp_cfg_disable_ports_mask (uint32 disable_mask);

/* Get the mask of enabled/available ports */
uint32 pcie_rp_cfg_get_enabled_ports_mask (VOID);

/* Get the port config data for a particular port index. Ignore filter
 * allows internal module to get the config ignoring the masked status */
pcie_status_t pcie_rp_cfg_get_config (uint32_t rp_index, const pcie_port_config_t** rp_cfg_ptr);

pcie_status_t
pcie_rp_cfg_get_hw_config_info (const char * name,
                                const pcie_reg_field_val_t** select_conditional_ptr);

#endif   /* __PCIE_TARGET_ROOT_PORT_CONFIG_SVC_H__ */

