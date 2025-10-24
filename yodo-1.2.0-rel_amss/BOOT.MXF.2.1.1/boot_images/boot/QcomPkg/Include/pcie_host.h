#ifndef __PCIE_HOST_H__
#define __PCIE_HOST_H__

/**
  @file pcie_host.h
  @brief Public interface include file for the PCIe host driver.

  This file contains definitions of constants, data structures, and
  interfaces that provide operational control over a PCIe device.

*/
/*
===============================================================================

                             Edit History


  when       who     what, where, why
  --------   ---     ------------------------------------------------------------
  07/11/20   Yg      Ported to unified interface
  05/08/18   MK      Created

===============================================================================
                   Copyright (c) 2018 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "com_dtypes.h"
#include "Library/pcie_dtypes.h"

/**< Used as a wild card to capture all IDs in a category */
#define PCIE_ID_ANY         0xFFFFFFFF

/** PCI Config Header */
#define PCIE_CFG_DEVVENDID                       (0x0000)           /**< Device Vendor ID offset */
#define PCIE_CFG_CMDSTTS                         (0x0004)           /**< Command Status offset */
#define PCIE_CFG_REVCLASS                        (0x0008)           /**< Revision Class Code offset */
#define PCIE_CFG_HDRTYPE                         (0x000C)           /**< Header type offset */
#define PCIE_CFG_BAR(bar)                        (0x0010+4*(bar))   /**< BAR offset */
#define PCIE_CFG_TYPE1_BUS                       (0x0018)           /**< Bus config offset */
#define PCIE_CFG_TYPE1_MEMBASELIMIT              (0x0020)           /**< Memory Base and Limit offset */
#define PCIE_CFG_TYPE1_PREFETCH_MEMBASELIMIT     (0x0024)           /**< Prefetchable Base and Limit offset */
#define PCIE_CFG_TYPE1_PREFETCH_UPPER_MEMBASE    (0x0028)           /**< Prefetchable Memory Base Upper offset */
#define PCIE_CFG_TYPE1_PREFETCH_UPPER_MEMLIMIT   (0x002C)           /**< Prefetchable Memory Limit Upper offset */
#define PCIE_CFG_TYPE1_IOBASELIMIT               (0x0030)           /**< IO Base and Limit offset */
#define PCIE_CFG_CAPABILITY_PTR                  (0x0034)           /**< Capabilities ptr */
#define PCIE_CFG_EXTENDED_CAPABILITY_PTR         (0x0100)           /**< Ext Capabilities ptr */

#define MAX_DEVICES_PER_BUS       1  /**< Maximum number of devices on a single bus */
#define MAX_FUNCS_PER_DEVICE      1  /**< Maximum number of functions in a device */
#define PCIE_MAX_BARS             6  /**< Maximum number of BARs PCIe config space has */

#define PCIE_HOST_MAX_DRVNAME_LENGTH    12 /**< Maximum length of a driver name */


/** Config access mode */
typedef enum {
   PCIE_OPER_READ     = 0x0,     /**< Config Read operation */
   PCIE_OPER_WRITE    = 0x1      /**< Config Write operation */
}pcie_rw_mode_t;

/** Device ID structure the device can be identified with */
typedef struct {
   uint32  vendor_id; /**< Vendor ID. Use PCIE_ANY_ID if not required to match */
   uint32  device_id; /**< Device ID. Use PCIE_ANY_ID if not required to match */
   uint32  class_id;  /**< Class code (BCC+SCC+PI). Use PCIE_ANY_ID if not req to match */
   uint32  rbdf_info; /**< Root port + BDF info */
}pcie_device_info_t;    // TODO: Call it filter since its used only in that context?

/** Memory region descriptor*/
typedef struct {
   uint64  pa;                        /**< physical address of memory region */
   uint64  va;                        /**< virtual address of memory region */
   uint64  sz;                        /**< size of memory region */
   uint64  limit;                     /**< Limit of the region (pa + sz -1) */
}pcie_mem_region_t;

/** Opaque handle to the PCIe device */
struct __pcie_rc_dev;
typedef struct __pcie_rc_dev pcie_dev_t;

/** Opaque handle to the PCIe Root port */
struct __pcie_root_port;
typedef struct __pcie_root_port* pcie_root_port_t;

/** Resource descriptor capturing resources allocated
 *  to a given device
 */
typedef struct{
   /**< BARs assigned to this device's MMIO Space */
   pcie_mem_region_t      bars[PCIE_MAX_BARS];

   //Interrupts and other resources are not supported for now
}pcie_rsrc_t;

/** Probe payload descriptor. This will be passed back
 *  when the device registered for, is getting probed */
typedef struct
{
   pcie_rsrc_t              rsrc;
   pcie_device_info_t       dev_ids;
}pcie_dev_probe_cb_payload_t;

/**
 * User callback function to be called for probing the PCIe device
 */
typedef void (*pcie_probefn_t)(pcie_dev_t *pdev, const pcie_dev_probe_cb_payload_t *cb_data, void* user_data);


/**
   @brief
   Initializes the PCIe host driver

   @details
   Initializes the PCIe host driver and enumerates the devices seen on the
   PCIe bus.

   @return
   None. If any error occurs, this function may not return (or enter error handler
   path as appropriate)

*/
pcie_status_t pcie_rc_init (void);

/**
 * Enumerates the PCIe device(s) attached to the specified root port.
 *
 * @param[in]  rc_index    Root complex index on which the enumeration must be
 *                         performed.
 *
 * @return PCIE_SUCCESS       : the operation succeeded
 *         PCIE_ERROR         : the operation failed
 *         PCIE_INVALID_PARAM : an invalid parameter was passed
 */
pcie_status_t pcie_enumerate (uint32 rc_index);

/* This API essentially powers off the controller and Phy */
pcie_status_t pcie_reset (uint32 rc_index);

/**
   @brief
   Registers the client as  the owner of a PCIe device.

   @details
   This function will perform the following:
   1.	Register the client as the owner of the device that has the attributes as defined in the devid.
   2.	If the device is already present in the bus, invoke the corresponding probe


   @param[in]  device_id    Device ID of the device to be registered with.
   @param[in]  probe_info     Probe call back to be called when the device is found

   @sideeffects
   If the PCIe host driver stack was not initialized, it will get initialized,
   and controllers will be brought up.
   It is possible that the probe function can get called in the context of this
   function, and so the client drivers must ensure that register_device call
   doesn’t conflict with their probe function. Also, probe function will be
   called independently for each device found on the bus that match the devid
   attribute

   @return
   Status of the operation

*/
pcie_status_t pcie_register_device (const pcie_device_info_t *device_id,
                                    pcie_probefn_t probe_fn, void* user_data);

pcie_status_t pcie_unregister_device (const pcie_device_info_t *device_id,
                                      pcie_probefn_t probe_fn, void* user_data);
/**
   @brief
   Enables the PCIe device for operation

   @details
   Enables the PCIe device for
   a) BME - Bus Master Enable -- Allows the device to DMA to/from the host memory
   b) MSE - Memory Space Enable -- Allows the host to access device's MMIO space
   c) IE  - IO Space Enable -- Allows  the host to access device's IO space
   when (a/b/c) are provided via enable_options.
   In general, the clients are encouraged to set all these bits as part of the
   enable command.

   @param[in]  *pdev             Handle to the pcie device
   @param[in]  enable_options    Options to enable different operational modes

   @dependencies
   Device must have been probed, and pdev should be valid

*/
pcie_status_t pcie_enable_device (pcie_dev_t *pdev);

/**
   @brief
   Disables the device from all IO operations

   @details
   Disables the device from bus mastering as well as from MMIO accesses

   @param[in]  *pdev    Handle to the pcie device

   @dependencies
   Device must have been probed, and pdev should be valid

*/
pcie_status_t pcie_disable_device (pcie_dev_t *pdev);

#define LINK_SPEED_G1_MASK   0x1
#define LINK_SPEED_G2_MASK   0x2
#define LINK_SPEED_G3_MASK   0x4
#define LINK_SPEED_G4_MASK   0x8

typedef struct
{
   uint32     max_lane_width;
   uint32     link_speed_mask;
} pcie_port_capabilities_t;

typedef struct
{
   uint16     link_up;
   uint16     link_state;
   uint32     current_link_width;
   uint32     current_link_speed;
} pcie_link_status_t;

pcie_status_t pcie_get_port_capabilities (uint32 rc_index, pcie_port_capabilities_t* caps);
pcie_status_t pcie_get_link_status (uint32 rc_index, pcie_link_status_t* caps);

#endif //__PCIE_HOST_H__
