#ifndef MHI_TGT_CONFIG_H
#define MHI_TGT_CONFIG_H
/**
 *  @file mhi_tgt_config.h
 *
 *  @brief This file contains target config types.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi.h"
#include "pcie_osal.h"
#include "com_dtypes.h"
#include <stddef.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
/** Value used to indicate an invalid memory region */
#define INVALID_MEM_REGION 0xff

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/** Log configuration type */
typedef struct
{
   const char *name;                   /**< Log name */
   size_t size;                        /**< Log size in bytes */
   pcie_osal_log_level_t filter_level; /**< Run-time filter level */
} mhi_log_config_t;

/** MHI device-level configuration */
typedef struct
{
   const char *thread_name;               /**< Worker thread name */
   uint32 thread_priority;                /**< Worker thread priority */
   mhi_dev_id_t dev_id;                   /**< MHI device ID */
   uint32 pcie_vendor_id;                 /**< PCIe vendor ID */
   uint32 pcie_device_id;                 /**< PCIe device ID */
   uint32 mhi_bar_idx;                    /**< Which BAR */
   uintptr_t mhi_bar_va;                  /**< BAR virtual address */
   uint32 mhi_offset;                     /**< Offset into the BAR for MHI */
   uint32 mhi_msi_vector;			         /**< MSI bit assigned for MHI */
   uint32 bhi_msi_vector;			         /**< MSI bit assigned for BHI */
   uint32 m0_event_wait_time_out;		   /**< m0 event wait time out in us */
   uint32 num_cr_elems;                   /**< Number of command ring elements */
   uint32 num_tr_elems;                   /**< Number of transfer ring elements */
   uint32 num_er_elems;                   /**< Number of event ring elements */
   uint32 num_ers;                        /**< Number of event rings */
   uint32 num_chans;                      /**< Number of channel configs */
   uint32 chan_write_ack_time_out;        /**< m0 event wait time out in us */
   boolean uses_bhie;
} mhi_dev_cfg_t;

/** MHI driver-level configuration */
typedef struct
{
   /* Atleast one of these should be given for filtering */
   uint32                target_chip_id;
   uint32                target_chip_family;

   mhi_log_config_t log;                        /**< Log configuration */
   mhi_log_config_t profile_log;                /**< Profiling log configuration */
   const char *drv_thread_name;                 /**< Worker thread name */
   uint32 drv_thread_priority;                  /**< Worker thread priority */
   const mhi_dev_cfg_t *dev_cfgs;               /**< Device configs */
   uint32 num_devs;                             /**< Number of devices */
} mhi_tgt_config_t;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/**
   @brief
   Initializes target specific config data

   @details
   Initializes target specific configuration data to be used by the PCIe host
   driver

   @return
   PCIE_SUCCESS on Successfully finding the config, otherwise returns PCIE_ERROR

*/
mhi_tgt_config_t* mhi_get_tgt_cfg(void);

#endif

