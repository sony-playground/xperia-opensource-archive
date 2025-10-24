#ifndef __PCIE_RP_H___
#define __PCIE_RP_H___
/*
 *  pcie_rp.h
 *
 *  PCIe root port management library interface
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   10/20/20   Yg      Created New

*/
/*============================================================================
               Copyright (c) 2020 - 2022 Qualcomm Technologies, Inc.
                 All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/


#include "pcie_dtypes.h"

struct __pcie_rp_ctxt;
typedef struct __pcie_rp_ctxt pcie_rp_handle;

typedef struct
{
   uint64  pa;
   uint64  va;
   uint64  sz;
}pcie_mem_resource_t;

#define HOST_BDF_VAL   0x000

/* Note that EP BDF value will change based on any switch/bridges present
 * in the PCIe bus topology, need a proper solution for such cases which
 * are not supported today */
#define EP_BDF_VAL     0x100

typedef enum {
   PCIE_RESOURCE_NONE                     = 0,
   PCIE_RESOURCE_CONFIG_SPACE             = 1,
   PCIE_RESOURCE_IO_SPACE                 = 2,
   PCIE_RESOURCE_NON_PREFETCH_MEM_SPACE   = 3,
   PCIE_RESOURCE_PREFETCHABLE_MEM_SPACE   = 4,
   PCIE_RESOURCE_DBI_BASE                 = 5,
   PCIE_RESOURCE_PARF_BASE                = 6,

   PCIE_RESOURCE_MAX
}pcie_resource_type;

/*******************************************************************************
 *      PCIe RP Lib public API's
 ******************************************************************************/

/* Initialize Lib before calling any other API */
pcie_status_t pcie_rp_lib_init (void);

/* Get max root port count */
uint32 pcie_rp_get_max_port_count (void);

/* Get enabled root ports mask */
uint32 pcie_rp_get_enabled_ports_mask (void);

/* Reload all the config after a HW port config change */
pcie_status_t pcie_rp_cfg_reload_config (void);

/* Disable port configuration by index */
pcie_status_t pcie_rp_disable_port_config (uint32 port_index);

/* Initialize and bring the root ports link up */
pcie_status_t pcie_rp_enumerate_ports (uint32 ports_mask);

/* Powerdown specified root ports for LPM */
pcie_status_t pcie_rp_powerdown_ports (uint32 ports_mask);

/* Check if the port's link is up */
uint32 pcie_rp_is_port_link_up (uint32 port_index);

/* Get the HW port index for the given port at a specific port index.
 * HW port index may not be same as port index which represents config index */
pcie_status_t pcie_rp_get_hw_idx (uint32 port_index, uint32* hw_idx_ptr);

/* Setup IO space config. Only if absolutely required. */
pcie_status_t pcie_rp_setup_io_space_ATU (uint32   port_index,
                                          uint64   BaseAddr,
                                          uint64   BaseLimit,
                                          uint64   TranslationAddr);

/* Get PCIe config space address */
pcie_status_t pcie_rp_get_cfg_space_addr (uint32 port_index, uint16 bdf, uint32** ptr);

/* Get Capabilities from a specific config space on a port. Currently only
 *  Host BDF(0x000) and EP BDF(0x100) are supported
 *  Value returned in Address Ptr is virtual address that can be accessed
 *  directly reading the capability structure.
 *  Reg_offset is the Config space byte offset for the requested capability.  */
pcie_status_t pcie_rp_get_capability (uint32    port_index,
                                      uint16    bdf,
                                      uint32    cap_id,
                                      uint64*   addrp,
                                      uint32*   reg_offsetp);

pcie_status_t pcie_rp_get_ext_capability (uint32   port_index,
                                          uint16   bdf,
                                          uint32   cap_id,
                                          uint64*  addrp,
                                          uint32*  reg_offsetp);

/* Setup L1ss/aspm options */
pcie_status_t pcie_rp_setup_l1ss (uint32 port_index);
pcie_status_t pcie_rp_setup_aspm (uint32 port_index);

/* Get a specific memory resource for the port */
pcie_status_t pcie_rp_get_mem_resources (uint32                port_index,
                                         pcie_resource_type    rsrc,
                                         pcie_mem_resource_t*  res);

/* SMMU Map/unmap for a particular PCIe port BDF value */
pcie_status_t pcie_rp_map_mem_smmu_sid (uint32    port_index,
                                        uint32    bdf,
                                        void*     base_addr,
                                        uint64    size_bytes,
                                        void**    map_handle_ptr);

pcie_status_t pcie_rp_unmap_smmu_sid (void* map_handle);

/*******************************************************************************
 *  Target settings API Interface (implemented in target RP config lib)
 ******************************************************************************/
pcie_status_t pcie_rp_set_default_target_config (uint32 option);
pcie_status_t pcie_rp_set_hw_port_lanes_config (uint32 port, uint32 option);

/*******************************************************************************
 *      Test infrastructure related API's
 ******************************************************************************/
#define ENABLE_TEST_INFRASTRUCTURE
#ifdef ENABLE_TEST_INFRASTRUCTURE

uint32 pcie_rp_get_ltssm_state (uint32 port_index);

/* Initialize and bring the root ports link up */
pcie_status_t pcie_rp_enable_loopback (uint32 port_index, pcie_loopback_type type);
pcie_status_t pcie_rp_disable_loopback (uint32 port_index);

pcie_status_t pcie_rp_setup_mem_rw_ATU (uint32    port_index,
                                        uint64    BaseAddr,
                                        uint64    BaseLimit,
                                        uint64    TranslationAddr);
pcie_status_t pcie_rp_unmap_mem_rw_ATU (uint32 port_index);

pcie_status_t pcie_rp_init_controller (uint32 port_index);
pcie_status_t pcie_rp_init_phy (uint32 port_index);
pcie_status_t pcie_rp_train_link (uint32 port_index);

static inline pcie_status_t pcie_rp_powerdown_port (uint32 port_index)
{
   return pcie_rp_powerdown_ports (1 << port_index);
}

uint32 pcie_rp_read_parf_reg (uint32 port_index, uint32 reg_index);
pcie_status_t pcie_rp_write_parf_reg (uint32 port_index, uint32 reg_index, uint32 val);

uint32 pcie_rp_read_config_reg (uint32 port_index, uint16 bdf, uint32 reg_index);
pcie_status_t pcie_rp_write_config_reg (uint32 port_index, uint16 bdf, uint32 reg_index, uint32 val);

pcie_status_t pcie_rp_setup_aer (uint32 port_index, uint16 bdf_val, int enable);
pcie_status_t pcie_rp_print_aer_logs (uint32 port_index, uint16 bdf_val);
#endif

#endif    /* __PCIE_RP_H___ */

