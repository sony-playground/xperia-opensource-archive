#ifndef MHI_DEVICE_H
#define MHI_DEVICE_H
/**
 *  @file mhi_device.h
 *
 *  @brief This file contains the device-level MHI interface
 */
/*=============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

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
 * This function initializes an MHI device.
 *
 * // TODO
 * Accessing the device is not allowed in this function, since these accesses
 * may fail if the device crashes or is not in the correct state. Similarly,
 * no IPC messages to the base driver are allowed in this function for the
 * same reasons.
 *
 * @param[in]  drv          Driver context
 * @param[in]  dev_info     Device info
 * @param[in]  cfg          Configuration
 * @param[in]  pcie_dev_h   PCIe device handle
 * @param[in]  pcie_res     PCIe resources
 * @param[out] dev_ctxt     Device context
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_init(mhi_drv_t *drv, const mhi_dev_info_t *dev_info, const mhi_dev_cfg_t *cfg,
                   pcie_dev_t *pcie_dev_h, const pcie_rsrc_t *pcie_res, mhi_dev_t **dev_ctxt);

/**
 * This function deinitializes an MHI device.
 *
 * @param[in]  dev  Device context
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_deinit(mhi_dev_t *dev);

/**
 * This function queues a channel open request.
 *
 * @param[in]  client_ctxt  Client context
 * @param[in]  ch_id        Channel ID
 * @param[in]  cb           Callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_queue_chan_open(mhi_client_ctxt_t *client_ctxt, uint32 ch_id, mhi_cb_t *cb);

/**
 * This function queues a channel close request.
 *
 * @param[in]  client_ctxt  Client context
 * @param[in]  ch_id        Channel ID
 * @param[in]  cb           Callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_queue_chan_close(mhi_client_ctxt_t *client_ctxt, uint32 ch_id, mhi_cb_t *cb);

/**
 * This function queues a transfer.
 *
 * @param[in]  client_ctxt  Client context
 * @param[in]  ch_id        Channel ID
 * @param[in]  op           Which transfer operation
 * @param[in]  data         Transfer buffer
 * @param[in]  size         Buffer size
 * @param[in]  cb           Callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_queue_transfer(mhi_client_ctxt_t *client_ctxt, uint32 ch_id,
                             mhi_op_t op, void *data, size_t size, mhi_cb_t *cb);

/**
 * This function allocates an MHI buffer.
 *
 * @param[in]  dev      Device context
 * @param[in]  mem_cfg  Which memory config
 * @param[out] buffer   Allocated buffer
 * @param[in]  size     Desired buffer size
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_buffer_allocate(mhi_dev_t *dev, mhi_mem_cfg_t mem_cfg,
                              void **buffer, size_t size);

/**
 * This function frees an MHI buffer.
 *
 * @param[in]  dev      Device context
 * @param[in]  mem_cfg  Which memory config
 * @param[in]  buffer   Allocated buffer
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_buffer_free(mhi_dev_t *dev, mhi_mem_cfg_t mem_cfg, void *buffer);

// TODO: ADD DOCUMENTATION
/**
 * This function transfers the the image to the device
 *
 * @param[in]  dev     Device context
 * @param[in]  image   Image to be transfered
 * @param[in]  size    Size of the image transferred 
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_transfer_image(mhi_dev_t *dev, void *image, size_t size);

/**
 * This function transfers the the image to the device
 *
 * @param[in]  dev     Device context
 * @param[in]  image   Image to be transfered
 * @param[in]  size    Size of the image transferred 
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_execute_bhie(mhi_dev_t *dev, void *image, size_t size);

/**
 * This function rings the DEVICE_WAKE doorbell
 *
 * @param[in]  client_ctxt  Client context
 * @param[in]  state        value requested by client to be written
 *             (0-de-assert, 1-assert)
 *
 * @return SUCCESS or an error code
 */
void mhi_drv_device_wake(mhi_handle_t dev_h, uint32 state);


/**
 * This function extract ther resources from the device handle
 *
 * @param[in]  dev        Device context
 * @param[in]  resources  Device's resources
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_trigger_sys_error(mhi_dev_t *dev, boolean notify_clients);

int32 mhi_dev_get_resources(mhi_dev_t *dev, mhi_resources_t *resources);

/**
 * This function registers a particular interrupt vector corresponding to every client
 *
 * @param[in]  dev              Device context
 * @param[in]  vector           Vector number
 * @param[in]  cb               Callback
 * @param[in]  ctxt             Context
 * @param[in]  trigger_params   Interrupt trigger parameters
 *
 * @return SUCCESS 
 */
int32 mhi_dev_int_register(mhi_dev_t *dev, uint32 vector, mhi_int_cb_t cb,
                           void *ctxt, mhi_int_trigger_params_t *trigger_params);
/**
 * This function is used to unregister an interrupt.
 *
 * @param[in]  dev    MHI Device handle
 * @param[in]  vector Interrupt vector number
 *
 * @return SUCCESS indicates the operation succeeded. Other values include:
 *       * NOT_SUPPORTED: If invalid vector number is passed
 */
int32 mhi_dev_int_unregister(mhi_dev_t *dev, uint32 vector);

/**
 * This function gets the current execution environment.
 *
 * @param[in]  dev    MHI Device handle
 * @param[out] ee     Execution environment
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
int32 mhi_dev_get_ee(mhi_dev_t *dev, mhi_ee_t *ee);

/**
 * This function gets the curent MHI device state.
 *
 * @attention Context: worker thread only
 *
 * @param[in]  dev        Device context
 * @param[out] state      Current MHI device state
 *
 * @return New state (may not match requested state, e.g. SYSERR occurred)
 */
int32 mhi_get_device_state(mhi_dev_t *dev, mhi_state_t *state);

/**
 * This function updates the current execution environment in dev structure.
 *
 * @param[in]  dev       MHI Device handle
 * @param[in]  exec_env  Execution environment
 *
 * @return none
 */
void mhi_dev_update_exev_env(mhi_dev_t *dev, mhi_exec_env_t exec_env);

/**
 * This function aggregates the votes for device wake
 *
 * @param[in]  dev    MHI Device handle
 * @param[in]  state  requesting state of the device wake
 *
 * @return none
 */
void mhi_drv_vote_device_wake(mhi_handle_t dev_h, uint32 state);

 /**
 * This function is used to trigger an MHI reset on the device. 
 *
 * @param[in]  dev_h           Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
int32 mhi_dev_trigger_device_reset(mhi_dev_t *dev);

 /**
 * This function is used to process the latency request from the client of this device. 
 *
 * @param[in]  dev_h           Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
uint32 mhi_dev_process_bus_latency(mhi_dev_t *dev);

/**
 * This function is used to synchronize time between host and device by capturing
 * the corresponding timestamps.
 *
 * @param[in]  dev    MHI Device handle
 * @param[out] local_ticks  Host time in ticks
 * @param[out] dev_ticks    Device time in ticks
 *
 * @return SUCCESS indicates the operation succeeded. Other values include:
 *       * NOT_SUPPORTED: If invalid vector number is passed
 */
int32 mhi_dev_sync_time(mhi_dev_t *dev, uint64 *local_ticks, uint64 *dev_ticks);

/**
 * This function is used to assert the device wake in pre_STM and STM context
 * and poll for MHI_M0 or MHI_SYS_ERROR.
 *
 * @param[in]  dev    MHI Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *       * MHI_ERROR: If operaton failed.
 */
int32 mhi_dev_wake_device_stm(mhi_dev_t *dev);

/**
 * This function closes an MHI channel.
 *
 * @param[in]  dev_h   Device handle
 * @param[in]  ch_work mhi channel work
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
int32 mhi_dev_channel_close(mhi_dev_t *dev, mhi_ch_work_t *ch_work);

/**
 * This function opens an MHI channel.
 *
 * @param[in]  dev_h   Device handle
 * @param[in]  ch_work mhi channel work
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
int32 mhi_dev_channel_open(mhi_dev_t *dev, mhi_ch_work_t *ch_work);

/**
 * This function writes data over an MHI channel.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  ch_id  Channel ID
 * @param[in]  data   Address of data to send
 * @param[in]  size   Number of bytes to write
 * @param[in]  cb     Callback type for asynchronous operation
 *
 * @dependencies mhi_channel_open must be called first.
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
int32 mhi_dev_channel_write(mhi_dev_t *dev, uint32 ch_id, void *data, size_t size, mhi_cb_t *cb);

/**
 * This function reads data over an MHI channel.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  ch_id  Channel ID
 * @param[in]  data   Address of buffer where the data will be read in
 * @param[in]  size   Number of bytes to read in
 * @param[in]  cb     Callback type for asynchronous operation
 *
 * @dependencies mhi_channel_open must be called first.
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
int32 mhi_dev_channel_read(mhi_dev_t *dev, uint32 ch_id, void *data, size_t size, uint32 *bytes_read, mhi_cb_t *cb);

#endif
