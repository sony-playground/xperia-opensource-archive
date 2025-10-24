#ifndef MHI_DRIVER_H
#define MHI_DRIVER_H
/**
 *  @file mhi_driver.h
 *
 *  @brief This file contains the driver-level MHI interface.
 */
/*============================================================================
               Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi_i.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/**
 * This function performs driver-level initialization.
 *
 * @param[in]  tgt_config  Target configuration
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_init(const mhi_tgt_config_t *tgt_config);

/**
 * This function performs driver-level deinitialization.
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_deinit(void);

/**
 * This function registers a callback to receive notifications for a given
 * device ID.
 *
 * @param[in]  dev_id  Device ID
 * @param[in]  cb      Client-supplied callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_register(mhi_dev_id_t dev_id, mhi_cb_t *cb);

/**
 * This function unregisters a callback to receive notifications for a given
 * device ID.
 *
 * @param[in]  dev_id  Device ID
 * @param[in]  cb      Client-supplied callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_unregister(mhi_dev_id_t dev_id, mhi_cb_t *cb);

/**
 * This function opens a specific device and registers a device-specific callback.
 *
 * @param[in]  dev_info     Device info
 * @param[in]  cb           Client-supplied callback
 * @param[out] client_ctxt  Client context
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_open_dev(const mhi_dev_info_t *dev_info, mhi_cb_t *cb,
                       mhi_client_ctxt_t **client_ctxt);

/**
 * This function closed a specific device and registers an optional device-specific callback.
 *
 * @param[in]  client_ctxt  Client context
 * @param[in]  cb           Client-supplied callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_close_dev(mhi_client_ctxt_t *client_ctxt, mhi_cb_t *cb);

/**
 * This function returns the minimum value present in the list
 *
 * @param[in]  node 		Node requested by the client     
 *
 * @return Minimum calculated value
 */
uint32 mhi_drv_get_min_val(uint32 node);

/**
 * This function returns the minimum value present in the list
 *
 * @param[in]  node 		Node requested by the client     
 * @param[in]  instm 		if the execution is in stm
 *
 * @return Minimum calculated value
 */
int32 mhi_drv_issue_request_stm(mhi_client_ctxt_t *client_ctxt, uint32 instm);

/**
 * This function adds a new client in the sorted client list or modifies and rearranges
 * the new value in sorted list and get the 
 * first element of the list.
 *
 * @param[in]  client_ctxt 	Client Context
 * @param[in]  node         Node requested by the client
 * @param[in]  val          Value corresponding to the node
 *
 * @return Minimum calculated value
 */
uint32 mhi_drv_node_bus_min_latency(mhi_client_ctxt_t *client_ctxt, mhi_node_t node, uint32 val);

int32 mhi_drv_issue_request(mhi_client_ctxt_t *client_ctxt, mhi_node_t node, uint32 state);

int32 mhi_drv_complete_request(mhi_client_ctxt_t *client_ctxt , mhi_node_t node);

int32 mhi_drv_trigger_shutdown(mhi_dev_t *dev);
#endif

