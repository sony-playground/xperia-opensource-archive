#ifndef __PCIE_HOST_R_H__
#define __PCIE_HOST_R_H__

/*
  @file pcie_host_r.h
  @brief Restricted interface include file for the PCIe host driver.

  This file contains definitions of constants, data structures, and
  interfaces that provide operational control over a PCIe device.

*/
/*
 ==============================================================================

          Edit History


  when       who     what, where, why
  --------   ---     ---------------------------------------------------------
  03/08/21   Yg      Adapted to new interface
  11/15/19   Yg      Ported to ADSP
  05/08/18   MK      Created

 ==============================================================================
     Copyright (c) 2018 - 2021 QUALCOMM Technologies Incorporated
     All Rights Reserved.  Qualcomm Confidential and Proprietary.
 ==============================================================================
*/

#include "pcie_dtypes.h"
#include "pcie_host.h"

/* Used as a wild card to capture all IDs in a category */
#define PCIE_ID_ANY         0xFFFFFFFF

#define PCIE_MAX_BARS                   6

#define ENABLE_MSI_SUPPORT

/*******************************************************************************
 *        Interface data type declarations
 ******************************************************************************/

typedef enum {
   PCIE_OPER_READ     = 0x0,
   PCIE_OPER_WRITE    = 0x1,
}pcie_rw_op_t;

/* Device ID structure the device can be identified with */
typedef struct {
   uint32        vendor_id;
   uint32        device_id;
   uint32        class_id;
   uint32        rbdf_info;
}pcie_device_info_t;    // TODO: Call it filter since its used only in that context?

/* Memory region descriptor*/
typedef struct {
   uint64        pa;
   uint64        va;
   uint64        sz;
   uint64        limit; /* TODO: Is this really needed when Limit = (pa + sz -1) */
}pcie_mem_region_t;

/* Opaque handle to the PCIe device */
struct __pcie_dev;
typedef struct __pcie_dev pcie_dev_t;

/* Resource descriptor capturing resources allocated to a given device */
typedef struct{
   pcie_mem_region_t      bars[PCIE_MAX_BARS];

   /* TODO: Add MSI resources here */
}pcie_rsrc_t;

/*  Probe payload descriptor. This will be passed back to the callback function
 *  as a result of probe */
typedef struct
{
   pcie_rsrc_t              rsrc;
   pcie_device_info_t       dev_ids;
   uint32                  *cfg_space;
}pcie_dev_probe_cb_payload_t;

/* User callback function to be called for probing the PCIe device */
typedef void (*pcie_probefn_t)(pcie_dev_t                           *pdev,
                               const pcie_dev_probe_cb_payload_t    *cb_data,
                               void                                 *user_data);

typedef void (*pcie_msi_callback_fn_t) (uint32 msi_vect, void* arg);

/*******************************************************************************
 *    Host root complex services interface function API's
 ******************************************************************************/

/* Initializes the PCIe host driver */
pcie_status_t pcie_rc_init (void);

/* This API powers off the controller and Phy */
pcie_status_t pcie_reset (uint32 rc_index);

/*
 *    Register the client as  the owner of a PCIe device.
 *
 *    This function will perform the following:
 *    1.	Register the client as the owner of the device with device_id
 *    2.	If the device is already present in the bus, invoke the corresponding probe
*/
pcie_status_t pcie_register_device (const pcie_device_info_t *device_id,
                                    pcie_probefn_t probe_fn, void* user_data);

/*    Unregister the client */
pcie_status_t pcie_unregister_device (const pcie_device_info_t *device_id,
                                      pcie_probefn_t probe_fn, void* user_data);

/* Enables the PCIe device for MEM IO operation (Enable BME/MSE) */
pcie_status_t pcie_enable_device (pcie_dev_t *pdev);

/* Disables the device from all IO operations (BME/MSE Disabled) */
pcie_status_t pcie_disable_device (pcie_dev_t *pdev);

/* Performs an access to the config space of the PCIe device */
pcie_status_t pcie_config_rw (pcie_dev_t          *pdev,
                              pcie_rw_op_t         operation,
                              uint32               offset,
                              uint32              *val);


/* Register for MSI callback, also provide the trigger addr and data to configure PCIe MSI capability */
pcie_status_t pcie_register_msi_callback (pcie_dev_t                 *pdev,
                                          uint32                      msi_vector,
                                          pcie_msi_callback_fn_t      msi_cb_fn,
                                          void                       *arg,
                                          uint64                     *trig_addr_ptr,
                                          uint32                     *trig_data_ptr);

/* Unregister MSI callback */
pcie_status_t pcie_unregister_msi_callback (pcie_dev_t             *pdev,
                                            uint32                  msi_vector,
                                            pcie_msi_callback_fn_t  msi_cb_fn);

/* Enable MSI interrupt */
pcie_status_t pcie_msi_enable_int (pcie_dev_t *pdev, uint32 msi_vector);

/* Disable MSI interrupt */
pcie_status_t pcie_msi_disable_int (pcie_dev_t *pdev, uint32 msi_vector);

/* Debug function to print capabilities */
pcie_status_t pcie_print_capabilities (pcie_dev_t *pdev);

/* Get parent device handle (returns host dev handle when EP device handle used) */
pcie_dev_t *pcie_get_parent (pcie_dev_t *pdev);

/*******************************************************************************
 *    Loopback test functions 
 ******************************************************************************/

/* Opaque handle to the PCIe Root port */
struct __pcie_root_port;
typedef struct __pcie_root_port  pcie_root_port_t;

typedef struct
{
   uint16 rc_index;
   uint16 link_width;
   uint16 link_speed;
   uint16 rsrv;
   uint64 mem_base;
   uint64 mem_size;
}loopback_req_t;

//pcie_status_t pcie_enable_loopback (loopback_req_t     *req_info,
//                                    uint64            **pcie_space_ptr,
//                                    pcie_root_port_t   *port_handle_ptr,
//                                    pcie_loopback_type  loopback_type);

pcie_status_t pcie_enable_local_digital_loopback (loopback_req_t     *req_info,
                                                  uint64            **pcie_space_ptr,
                                                  pcie_root_port_t  **port_handle_ptr);

pcie_status_t pcie_enable_local_analog_loopback (loopback_req_t     *req_info,
                                                 uint64            **pcie_space_ptr,
                                                 pcie_root_port_t  **port_handle_ptr);

pcie_status_t pcie_enable_remote_digital_loopback (loopback_req_t     *req_info,
                                                   uint64            **pcie_space_ptr,
                                                   pcie_root_port_t  **port_handle_ptr);

pcie_status_t pcie_disable_loopback (pcie_root_port_t* port_handle);

#define LINK_SPEED_GEN1_MASK   0x1
#define LINK_SPEED_GEN2_MASK   0x2
#define LINK_SPEED_GEN3_MASK   0x4
#define LINK_SPEED_GEN4_MASK   0x8

typedef struct
{
   uint32   max_lane_width;
   uint32   link_speed_mask;
} pcie_port_info_t;

typedef struct
{
   uint16   link_up;
   uint16   link_state;
   uint32   current_link_width;
   uint32   current_link_speed;
   uint32   LPM_counters[3];
} pcie_link_status_t;

pcie_status_t pcie_get_port_info (uint32 rc_index, pcie_port_info_t* port_info);
pcie_status_t pcie_get_link_status (uint32 rc_index, pcie_link_status_t* caps);
pcie_status_t pcie_set_lane_width (uint32 rc_index, uint32 width);
pcie_status_t pcie_set_link_width (uint32 rc_index, uint32 width);
pcie_status_t pcie_set_link_speed (uint32 rc_index, uint32 speed);

pcie_status_t pcie_set_allowed_link_speeds (uint32 rc_index, uint32 speed_mask);
pcie_status_t pcie_set_allowed_lpm_states (uint32 rc_index, uint32 lpm_mask);

pcie_status_t pcie_bus_initialize (uint32 rc_index);
pcie_status_t pcie_enable_test_environment (void);

pcie_status_t pcie_get_cfg_space_addr (uint32 rc_index, uint16 bdf, uint32** ptr);

pcie_status_t pcie_setup_aspm (uint32 rc_index);
pcie_status_t pcie_setup_l1ss (uint32 rc_index);
pcie_status_t pcie_print_aer_logs (uint32 rc_index, uint16 bdf_val);

#endif //__PCIE_H__

