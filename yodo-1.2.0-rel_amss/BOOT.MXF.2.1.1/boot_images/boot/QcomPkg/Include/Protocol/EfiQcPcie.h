/** 
 * Qualcomm specific PCIE Protocol interface
 *  
 * Copyright (c) 2020 Qualcomm Technologies, Inc. All rights reserved.
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/13/20   yg      Initial version

=============================================================================*/

#include <Uefi.h>

#ifndef ___EFI_QC_PCIE_PROTOCOL_H__
#define ___EFI_QC_PCIE_PROTOCOL_H__

/* External global reference to the Kernel Protocol GUID */
extern EFI_GUID gEfiQcPcieDxeProtocolGuid;

/* Protocol GUID definition. { 496D8C8E-7397-472C-9E6C-77BFC4580F72 } */
#define EFI_QC_PCIE_DXE_PROTOCOL_GUID \
         { 0x496D8C8E, 0x7397, 0x472C, { 0x9E, 0x6C, 0x77, 0xBF, 0xC4, 0x58, 0x0F, 0x72 } }

/*
 *   Document the version changes here
 *   V 1.0
 *      Initial version
 *
 *   V 2.0
 *      Newer interface, removed some unused fields and API's
 *      Since API's are not used backward compatibility is not affected
 *
 *   V 3.0
 *      Added DMA buffer mapping/unmapping API's
 *
 *   V 4.0
 *      Added HW lane config API
 *      Added Config reload API
 *
 *   V 5.0
 *      Added Get Config Space address API
 *      Added ASPM related API's
 *
 *   V 6.0
 *      Added AER related API's
 *
 * */

#define EFI_QC_PCIE_PROTOCOL_AER_SUPPORT_API   0x00060000
#define EFI_QC_PCIE_PROTOCOL_ASPM_SUPPORT_API  0x00050000
#define EFI_QC_PCIE_PROTOCOL_GET_CFG_ADDR_API  0x00050000
#define EFI_QC_PCIE_PROTOCOL_CFG_RELOAD_API    0x00040000
#define EFI_QC_PCIE_PROTOCOL_HW_LANE_CFG_API   0x00040000
#define EFI_QC_PCIE_PROTOCOL_DMA_MAP_API       0x00030000
#define EFI_QC_PCIE_PROTOCOL_NEW_INTF          0x00020000
#define EFI_QC_PCIE_PROTOCOL_FIRST_VER         0x00010000

/* Current protocol version */
#define EFI_QC_PCIE_PROTOCOL_VERSION      EFI_QC_PCIE_PROTOCOL_AER_SUPPORT_API


#define PCIE_ID_ANY         0xFFFFFFFF

#define PCIE_MAX_BARS             6

/*******************************************************************************
 *
 *   Interface type definitions
 *
 ******************************************************************************/
#include "com_dtypes.h"

//typedef unsigned int uint32;
// typedef unsigned long long uint64;

/*******************************************************************************
 *      PCIe host driver interface data types
 ******************************************************************************/
/* Opaque handle to the PCIe EP device */
struct __pcie_dev;
typedef struct __pcie_dev pcie_dev_t;

typedef enum
{
   PCIE_STATUS_SUCCESS       = 0,
   PCIE_STATUS_ERROR         = 1,
   PCIE_STATUS_INVALID_PARAM = 2,
} PCIE_STATUS;

typedef enum {
   PCIE_CONFIG_READ     = 0x0,
   PCIE_CONFIG_WRITE    = 0x1,
}PCIE_CONFIG_RW_TYPE;

typedef struct {
   uint32  vendor_id;
   uint32  device_id;
   uint32  class_id;
   uint32  rbdf_info;
}PCIE_DEVICE_INFO;

typedef struct {
   uint64  pa;
   uint64  va;
   uint64  sz;
   uint64  rsrv;
}PCIE_MEM_REGION;

typedef struct{
   PCIE_MEM_REGION      bars[PCIE_MAX_BARS];

   /* TODO: Add MSI info here */
}PCIE_RSRC;

typedef struct
{
   PCIE_RSRC              rsrc;
   PCIE_DEVICE_INFO       dev_ids;
   uint32                *cfg_space;
}PCIE_DEV_PROBE_PAYLOAD;

typedef void (*PCIE_PROBE_FN_TYPE)(pcie_dev_t *pdev, const PCIE_DEV_PROBE_PAYLOAD *cb_data, void* user_data);

typedef void (*PCIE_MSI_CB_FN_TYPE) (uint32 msi_vect, void* arg);

/********************************************************************************
      API Prototypes
********************************************************************************/


typedef
PCIE_STATUS (*PCIE_ENUMERATE) (uint32 rc_index);

typedef
PCIE_STATUS (*PCIE_RESET) (uint32 rc_index);

typedef
PCIE_STATUS (*PCIE_REGISTER_DEVICE) 
(
    const PCIE_DEVICE_INFO           *device_id,
    PCIE_PROBE_FN_TYPE                probe_fn, 
    void                             *user_data
);

typedef 
PCIE_STATUS (*PCIE_UNREGISTER_DEVICE) 
(
    const PCIE_DEVICE_INFO           *device_id,                         
    PCIE_PROBE_FN_TYPE                probe_fn, 
    void                             *user_data
);

typedef 
PCIE_STATUS (*PCIE_ENABLE_DEVICE) (pcie_dev_t *pdev);

typedef 
PCIE_STATUS (*PCIE_DISABLE_DEVICE) (pcie_dev_t *pdev);

typedef 
PCIE_STATUS (*PCIE_CONFIG_RW)
(
   pcie_dev_t                       *pdev, 
   PCIE_CONFIG_RW_TYPE               rw_type, 
   uint32                            offset, 
   uint32                           *val
);

typedef 
PCIE_STATUS  (*PCIE_REGISTER_MSI_CALLBACK)
(
   pcie_dev_t                        *pdev, 
   uint32                             msi_vector, 
   PCIE_MSI_CB_FN_TYPE                msi_cb_fn, 
   void                              *arg, 
   uint64                            *trig_addr_ptr, 
   uint32                            *trig_data_ptr
);

typedef 
PCIE_STATUS (*PCIE_UNREGISTER_MSI_CALLBACK) 
(
   pcie_dev_t                       *pdev, 
   uint32                            msi_vector, 
   PCIE_MSI_CB_FN_TYPE               msi_cb_fn
);

typedef 
PCIE_STATUS (*PCIE_MSI_ENABLE_INT)
(
   pcie_dev_t                       *pdev, 
   uint32                            msi_vector
);

typedef 
PCIE_STATUS (*PCIE_MSI_DISABLE_INT) 
(
   pcie_dev_t                       *pdev, 
   uint32                            msi_vector
);

/*******************************************************************************
 *       Test related data types and API's
 ******************************************************************************/
/* Opaque handle to the PCIe Root port */
struct __pcie_root_port;
typedef struct __pcie_root_port   pcie_root_port_t;

typedef struct
{
   uint32 max_lane_width;
   uint32 link_speed_mask;
} PCIE_PORT_INFO;

typedef struct
{
   uint16   link_up;
   uint16   link_state;
   uint32   current_link_width;
   uint32   current_link_speed;
   uint32   LPM_counters[3];
} PCIE_LINK_STATUS;

typedef struct
{
   uint16 rc_index;
   uint16 link_width;
   uint16 link_speed;
   uint16 rsrv;
   uint64 mem_base;
   uint64 mem_size;
}PCIE_LOOPBACK_REQ;

typedef 
pcie_dev_t* (*PCIE_GET_PARENT) (pcie_dev_t *pdev);

typedef 
EFI_STATUS (*PCIE_START_TEST_ENV) (void);

typedef 
PCIE_STATUS (*PCIE_GET_PORT_INFO) (uint32 rc_index, PCIE_PORT_INFO* caps);

typedef 
PCIE_STATUS (*PCIE_GET_LINK_STATUS) (uint32 rc_index, PCIE_LINK_STATUS* stats);

typedef 
PCIE_STATUS (*PCIE_ENABLE_LOCAL_DIGITAL_LOOPBACK) 
(
   PCIE_LOOPBACK_REQ                *req_info,
   uint64                          **pcie_space_ptr, 
   pcie_root_port_t                **port_handle_ptr
);

typedef 
PCIE_STATUS (*PCIE_ENABLE_LOCAL_ANALOG_LOOPBACK) 
(
   PCIE_LOOPBACK_REQ                *req_info,
   uint64                          **pcie_space_ptr, 
   pcie_root_port_t                **port_handle_ptr
);

typedef 
PCIE_STATUS (*PCIE_ENABLE_REMOTE_DIGITAL_LOOPBACK) 
(
   PCIE_LOOPBACK_REQ                *req_info,
   uint64                          **pcie_space_ptr, 
   pcie_root_port_t                **port_handle_ptr
);

typedef 
PCIE_STATUS (*PCIE_DISABLE_LOOPBACK) (pcie_root_port_t* port_handle);

typedef 
PCIE_STATUS (*PCIE_SET_LANE_WIDTH) (uint32 rc_index, uint32 width);
typedef 
PCIE_STATUS (*PCIE_SET_LINK_WIDTH) (uint32 rc_index, uint32 width);

typedef 
PCIE_STATUS (*PCIE_SET_GEN_SPEED) (uint32 rc_index, uint32 speed);

typedef 
PCIE_STATUS (*PCIE_SET_ALLOWED_GEN_SPEEDS) (uint32 rc_index, uint32 speed_mask);

typedef 
PCIE_STATUS (*PCIE_SET_ALLOWED_LPM_STATES) (uint32 rc_index, uint32 lpm_mask);

typedef 
PCIE_STATUS (*PCIE_MAP_DMA_BUFFER) (uint32 rc_index, uint32 bdf, void* addr, uint64 size_bytes, void** map_handle_ptr);

typedef 
PCIE_STATUS (*PCIE_UNMAP_DMA_BUFFER) (void* map_handle_ptr);

typedef 
PCIE_STATUS (*PCIE_SET_HW_LANES_CONFIG) (uint32 rc_index, uint32 max_lanes);

typedef 
PCIE_STATUS (*PCIE_RELOAD_PORTS_CONFIG) (void);

typedef 
PCIE_STATUS (*PCIE_GET_CFG_SPACE_ADDR) (uint32 rc_index, uint16 bdf, uint32** addr_ptr);

typedef 
PCIE_STATUS (*PCIE_SETUP_ASPM) (uint32 rc_index);

typedef 
PCIE_STATUS (*PCIE_SETUP_L1SS) (uint32 rc_index);

/* For the following 2 API's bdf arg value can be 0xFFFF that covers from Host through all EPs */
typedef 
PCIE_STATUS (*PCIE_SETUP_AER) (uint32 rc_index, uint16 bdf, int enable);

typedef 
PCIE_STATUS (*PCIE_PRINT_AER_LOGS) (uint32 rc_index, uint16 bdf);

/*===========================================================================
                    PROTOCOL INTERFACE
===========================================================================*/

typedef struct {
   UINT64                                Version;

   PCIE_ENUMERATE                        Enumerate;
   PCIE_RESET                            Reset;

   PCIE_REGISTER_DEVICE                  RegisterForDevice;
   PCIE_UNREGISTER_DEVICE                UnregisterForDevice;

   PCIE_ENABLE_DEVICE                    EnableDevice;
   PCIE_DISABLE_DEVICE                   DisableDevice;

   PCIE_CONFIG_RW                        ConfigRw;

   PCIE_REGISTER_MSI_CALLBACK            RegisterMsiCb;
   PCIE_UNREGISTER_MSI_CALLBACK          UnregisterMsiCb;
   PCIE_MSI_ENABLE_INT                   MsiEnableInt;
   PCIE_MSI_DISABLE_INT                  MsiDisableInt;

   /* Loopback test related  */
   PCIE_START_TEST_ENV                   StartTestEnvironment;

   PCIE_ENABLE_LOCAL_DIGITAL_LOOPBACK    EnableLocalDigitalLoopback;
   PCIE_ENABLE_LOCAL_ANALOG_LOOPBACK     EnableLocalAnalogLoopback;
   PCIE_ENABLE_REMOTE_DIGITAL_LOOPBACK   EnableRemoteDigitalLoopback;
   PCIE_DISABLE_LOOPBACK                 DisableLoopback;

   PCIE_GET_PARENT                       GetParent;

   PCIE_GET_PORT_INFO                    GetPortInfo;
   PCIE_GET_LINK_STATUS                  GetLinkStatus;

   PCIE_SET_LANE_WIDTH                   SetLaneWidth;
   PCIE_SET_LINK_WIDTH                   SetLinkWidth;

   PCIE_SET_GEN_SPEED                    SetLinkSpeed;

   PCIE_SET_ALLOWED_GEN_SPEEDS           SetAllowedLinkSpeeds;
   PCIE_SET_ALLOWED_LPM_STATES           SetAllowedLpmStates;

   PCIE_MAP_DMA_BUFFER                   MapDmaBuffer;
   PCIE_UNMAP_DMA_BUFFER                 UnMapDmaBuffer;

   PCIE_SET_HW_LANES_CONFIG              SetHwPortLanesConfig;

   PCIE_RELOAD_PORTS_CONFIG              ReloadPortsConfig;

   PCIE_GET_CFG_SPACE_ADDR               PcieGetCfgSpaceAddr;

   PCIE_SETUP_ASPM                       PcieSetupASPM;
   PCIE_SETUP_L1SS                       PcieSetupL1ss;

   PCIE_SETUP_AER                        SetupAER;
   PCIE_PRINT_AER_LOGS                   PrintAERLogs;

}EFI_QC_PCIE_DXE_PROTOCOL;

extern EFI_QC_PCIE_DXE_PROTOCOL* gQcPcie;

#endif  /* ___EFI_QC_PCIE_PROTOCOL_H__ */

