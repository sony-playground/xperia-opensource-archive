/**
 *  @file mhi.c
 *
 *  @brief This file implements the MHI APIs.
 */
/*============================================================================
               Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi.h"
#include "mhi_i.h"
#include "mhi_tgt_config.h"
#include "mhi_driver.h"
#include "mhi_device.h"
#include "mhi_utils.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define IS_NULL(X) (NULL == (X))

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
/**
 * This function converts internal status codes to MHI status codes.
 *
 * @param[in]  status  Internal status code
 *
 * @return Corresponding mhi_status_t code
 */
static mhi_status_t mhi_convert_internal_status(int32 status)
{
   switch (status)
   {
      case SUCCESS:
         return MHI_SUCCESS;
      case PENDING:
         return MHI_PENDING;
      case INVALIDCH:
         return MHI_CH_INVALID;
      case RING_FULL:
         return MHI_OP_FULL;
      case ABORT:
         return MHI_ABORTED;
      case DISCONNECTED:
         return MHI_DISABLED;
      default:
         return MHI_ERROR;
   }
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
/**
 * This function initializes the MHI driver.
 *
 * @attention This function must not be called directly by clients.
 *
 * @return MHI_SUCCESS indicates the operation succeeded.
 */
mhi_status_t mhi_init(void)
{
   const mhi_tgt_config_t *tgt_config;
   int32 status;

   tgt_config = mhi_get_tgt_cfg();
   if (IS_NULL(tgt_config))
   {
      MHI_LOG_FATAL("Failed to get MHI settings");
      return MHI_ERROR;
   }

   pcie_osal_log_init(PCIE_OSAL_LOG_MHI,
                      tgt_config->log.name,
                      tgt_config->log.size,
                      tgt_config->log.filter_level);

#ifdef MHI_PROFILING_ENABLED
   pcie_osal_log_init(PCIE_OSAL_LOG_MHI_PROFILING,
                      tgt_config->profile_log.name,
                      tgt_config->profile_log.size,
                      tgt_config->profile_log.filter_level);
#endif

   status = mhi_drv_init(tgt_config);
   if (status != SUCCESS)
   {
      return mhi_convert_internal_status(status);
   }

   return MHI_SUCCESS;
}

/**
 * This function deinitializes the MHI driver.
 *
 * @attention This function must not be called directly by clients.
 *
 * @param[in]  reset  Whether or not to perform a reset
 *
 * @dependencies mhi_init must be called first.
 *
 * @return MHI_SUCCESS indicates the operation succeeded.
 */
mhi_status_t mhi_deinit(boolean reset)
{
   return MHI_NOT_SUPPORTED;
}

/**
 * This function registers for MHI notification events, which are specified
 * in mhi_event_t. Notifications occur asynchronously through the callback
 * provided.
 *
 * @param[in]  dev_id  Device ID for which to receive notifications
 * @param[in]  cb      Callback structure (callback function and context)
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_register(mhi_dev_id_t dev_id, mhi_cb_t *cb)
{
   int32 status;

   if (IS_NULL(cb) || IS_NULL(cb->cb_func))
   {
      return MHI_INVALID_PARAM;
   }

   status = mhi_drv_register(dev_id, cb);

   return mhi_convert_internal_status(status);
}

/**
 * This function unregisters for MHI notification events, which are specified
 * in mhi_event_t.
 *
 * @param[in]  dev_id  Device ID for which to receive notifications
 * @param[in]  cb      Callback structure (callback function and context)
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_unregister(mhi_dev_id_t dev_id, mhi_cb_t *cb)
{
   int32 status;

   if (IS_NULL(cb) || IS_NULL(cb->cb_func))
   {
      return MHI_INVALID_PARAM;
   }

   status = mhi_drv_unregister(dev_id, cb);

   return mhi_convert_internal_status(status);
}

/**
 * This function opens a device and gets a handle to it. The callback specified
 * is used for notifications specific to this device.
 *
 * @param[in]  dev_info  Device info
 * @param[in]  cb        Callback structure (callback function and context)
 * @param[out] dev_h     Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_dev_open(const mhi_dev_info_t *dev_info, mhi_cb_t *cb,
                          mhi_handle_t *dev_h)
{
   int32 status;

   if (IS_NULL(dev_info) || IS_NULL(cb) || IS_NULL(cb->cb_func) || IS_NULL(dev_h))
   {
      return MHI_INVALID_PARAM;
   }

   status = mhi_drv_open_dev(dev_info, cb, (mhi_client_ctxt_t **)dev_h);

   return mhi_convert_internal_status(status);
}

/**
 * This function closes a device. It is up to the client to ensure all resources
 * were released prior to closing a device. After closing the device, clients
 * must NOT access the device through any previously obtained resources.
 *
 * If the optional callback is provided, it will be issued with MHI_DEV_CLOSED
 * event when all clients have closed the device.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  cb     Optional callback issued when all clients have closed the device
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_dev_close(mhi_handle_t dev_h, mhi_cb_t *cb)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;

   if (IS_NULL(dev_h) || IS_NULL(cb))
   {
      return MHI_INVALID_PARAM;
   }

   status = mhi_drv_close_dev(client_ctxt, cb);

   return mhi_convert_internal_status(status);
}

/**
 * This function opens an MHI channel. This must be called before doing any
 * read / write operations on the channel. If a callback is not specified then
 * the function will block.
 *
 * @param[in]  dev_h   Device handle
 * @param[in]  ch_id   Channel ID to open (obtained from the MHI specification)
 * @param[in]  cb      Callback type for asynchronous operation
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 *         * MHI_CH_INVALID: the channel is invalid or not enabled
 *         * MHI_PENDING: a result will be notified asynchronously
 */
mhi_status_t mhi_channel_open(mhi_handle_t dev_h, uint32 ch_id, mhi_cb_t *cb)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;
   mhi_ch_work_t ch_work;

   if (IS_NULL(dev_h))
   {
      return MHI_INVALID_PARAM;
   }

   /* We do not support asynchronous notifications, so callback should be null */
   if (!IS_NULL(cb))
   {
      MHI_LOG_LOW("mhi_channel_open : Invalid argument cb != NULL");
      return MHI_NOT_SUPPORTED;
   }

   ch_work.ch_id = ch_id;
   ch_work.client_ctxt = client_ctxt;

   status = mhi_dev_channel_open(client_ctxt->dev, &ch_work);

   return mhi_convert_internal_status(status);
}

/**
 * This function closes an MHI channel that was previously opened. The channel
 * must be in DISABLED / ENABLED state. If it is not, the channel will be set
 * to ERROR state, and an error condition will be generated to the host. This
 * function is not expected to be called unless we are doing a total cleanup.
 *
 * @param[in]  dev_h   Device handle
 * @param[in]  ch_id   Channel ID to open (obtained from the MHI specification)
 *
 * @dependencies mhi_channel_open must be called first.
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 *         * MHI_CH_INVALID: the channel is invalid or not enabled
 *         * MHI_PENDING: a result will be notified asynchronously
 *         * MHI_CH_NOT_IDLE: the channel is not in DISABLED / ENABLED state
 */
mhi_status_t mhi_channel_close(mhi_handle_t dev_h, uint32 ch_id)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;
   mhi_ch_work_t ch_work;

   if (IS_NULL(dev_h))
   {
      return MHI_INVALID_PARAM;
   }

   ch_work.ch_id = ch_id;
   ch_work.client_ctxt = client_ctxt;

   status = mhi_dev_channel_close(client_ctxt->dev, &ch_work);

   return mhi_convert_internal_status(status);
}

/**
 * This function allocates a buffer to be used for reads and writes. All
 * transfers must use buffers provided by this function. Once the buffer is
 * no longer needed, it must be freed using mhi_buffer_free.
 *
 * Different memory configurations can be specified when allocating a buffer.
 * The configuration must match that of the channel(s) that the buffer will
 * be used with.
 *
 * Since this function internally handles alignment requirements, do not
 * carve up the buffer into smaller buffers and pass them to MHI.
 *
 * @param[in]  dev_h    Device handle
 * @param[in]  mem_cfg  Desired memory configuration
 * @param[out] buffer   Buffer address
 * @param[in]  size     Buffer size
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 *         * MHI_CH_INVALID: the channel is invalid
 */
mhi_status_t mhi_buffer_allocate(mhi_handle_t dev_h, mhi_mem_cfg_t mem_cfg,
                                 void **buffer, uint32 size)
{
   return MHI_NOT_SUPPORTED;
}

/**
 * This function frees a buffer that was previously allocated by
 * mhi_buffer_allocate. Do not free buffers being actively used for
 * transfers.
 *
 * @param[in]  dev_h    Device handle
 * @param[in]  mem_cfg  Memory configuration
 * @param[in]  buffer   Buffer address
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 *         * MHI_CH_INVALID: the channel is invalid
 */
mhi_status_t mhi_buffer_free(mhi_handle_t dev_h, mhi_mem_cfg_t mem_cfg, void *buffer)
{
   return MHI_NOT_SUPPORTED;
}

/**
 * This function writes data over an MHI channel. If a callback is specified
 * the function will return with MHI_PENDING and perform an async notification
 * once the write is completed. Otherwise, this function will block until
 * completion of the write.
 *
 * In asynchronous mode, the callback's payload will contain the actual number
 * of bytes written in bytes_rw. In synchronous mode, bytes_written will be set
 * to the actual size written.
 *
 * End of transfer is always set when using this function.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  ch_id  Channel ID
 * @param[in]  data   Address of data to send
 * @param[in]  size   Number of bytes to write
 * @param[out] bytes_written  Actual amount of bytes written
 * @param[in]  cb     Callback type for asynchronous operation
 *
 * @dependencies mhi_channel_open must be called first.
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 *         * MHI_CH_INVALID: the channel is invalid
 *         * MHI_CH_INVALID_WRITE: channel direction does not permit a write
 *         * MHI_INVALID_ADDR: the data address is invalid
 *         * MHI_PENDING: a result will be notified asynchronously
 */
mhi_status_t mhi_channel_write(mhi_handle_t dev_h, uint32 ch_id, void *data,
                               uint32 size, uint32 *bytes_written, mhi_cb_t *cb)
{
   mhi_client_ctxt_t *client_ctxt;
   int32 status;

   if (IS_NULL(dev_h) || IS_NULL(data) || IS_NULL(bytes_written))
   {
      return MHI_INVALID_PARAM;
   }

   /* We do not support asynchronous notifications, so callback should be null */
   if (!IS_NULL(cb))
   {
      MHI_LOG_LOW("mhi_channel_write : Invalid argument cb != NULL");
      return MHI_NOT_SUPPORTED;
   }

   client_ctxt = (mhi_client_ctxt_t *)dev_h;

   *bytes_written = 0; /*initialize to zero */

   status = mhi_dev_channel_write(client_ctxt->dev, ch_id, data, size, cb);
   if (status == MHI_SUCCESS)
      *bytes_written = size;

   return mhi_convert_internal_status(status);
}

/**
 * This function reads data over an MHI channel. If a callback is specified
 * the function will return with MHI_PENDING and perform an async notification
 * once the read is completed. Otherwise, this function will block until
 * completion of the read.
 *
 * In asynchronous mode, the callback's payload will contain the actual number
 * of bytes read in bytes_rw. In synchronous mode, bytes_read will be set to
 * the actual size read.
 *
 * Always check eot to determine if this read was the end of a transfer or
 * if there is more data to read.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  ch_id  Channel ID
 * @param[in]  data   Address to receive data
 * @param[in]  size   Size of the data buffer in bytes
 * @param[out] bytes_read  Number of bytes actually read
 * @param[out] eot    Whether or not end of transfer occurred
 * @param[in]  cb     Callback type for asynchronous operation
 *
 * @dependencies mhi_channel_open must be called first.
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 *         * MHI_CH_INVALID: the channel is invalid
 *         * MHI_CH_INVALID_READ: channel direction does not permit a read
 *         * MHI_INVALID_ADDR: the data address is invalid
 *         * MHI_PENDING: a result will be notified asynchronously
 */
mhi_status_t mhi_channel_read(mhi_handle_t dev_h, uint32 ch_id, void *data,
                              uint32 size, uint32 *bytes_read,
                              boolean *eot, mhi_cb_t *cb)
{
   mhi_client_ctxt_t *client_ctxt;
   int32 status;

   if (IS_NULL(dev_h) || IS_NULL(data) || IS_NULL(bytes_read)
       || IS_NULL(eot))
   {
      return MHI_INVALID_PARAM;
   }

   /* We do not support asynchronous notifications, so callback should be null */
   if (!IS_NULL(cb))
   {
      MHI_LOG_LOW("mhi_channel_write : Invalid argument cb != NULL");
      return MHI_NOT_SUPPORTED;
   }

   client_ctxt = (mhi_client_ctxt_t *)dev_h;

   *bytes_read = 0; /*initialize to zero */

   status = mhi_dev_channel_read(client_ctxt->dev, ch_id, data, size, bytes_read, cb);
   if (status == MHI_SUCCESS)
   {
      *eot = TRUE;
   }

   return mhi_convert_internal_status(status);
}

/**
 * This function reads null data. As an optimization, no actual read is
 * performed. Instead, only the ring TRB is consumed by the size specified.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  ch_id  Channel ID
 * @param[in]  size   Size to consume
 * @param[out] bytes_read  Number of bytes actually consumed
 * @param[in]  cb     Callback type for asynchronous operation
 *
 * @dependencies mhi_channel_open must be called first.
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 *         * MHI_CH_INVALID: the channel is invalid
 *         * MHI_CH_INVALID_READ: channel direction does not permit a read
 *         * MHI_INVALID_ADDR: the data address is invalid
 *         * MHI_PENDING: a result will be notified asynchronously
 */
mhi_status_t mhi_channel_read_null(mhi_handle_t dev_h, uint32 ch_id, uint32 size,
                                   uint32 *bytes_read, mhi_cb_t *cb)
{
   return MHI_NOT_SUPPORTED;
}

/**
 * This function reads multiple data requests over an MHI channel. The operation
 * of this request will be asynchronous.
 *
 * The callback's payload will contain the actual number of bytes read in
 * bytes_rw.
 *
 * Always check eot to determine if this read was the end of a transfer or
 * if there is more data to read.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  ch_id  Channel ID
 * @param[in]  data_array     Array of addresses to receive the read data
 * @param[in]  size_array     Array of sizes of the data buffers in bytes
 * @param[in]  num_elements   Number of buffers in data and size arrays
 * @param[out] num_submitted  Number of buffers that were actually submitted
 * @param[in]  cb     Callback type for asynchronous operation
 *
 * @dependencies mhi_channel_open must be called first.
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 *         * MHI_CH_INVALID: the channel is invalid
 *         * MHI_CH_INVALID_READ: channel direction does not permit a read
 *         * MHI_INVALID_ADDR: the data address is invalid
 *         * MHI_PENDING: a result will be notified asynchronously; all buffers
 *                        accepted
 *         * MHI_OP_FULL: internal queue full and not all buffers accepted;
 *                        check num_submitted
 */
mhi_status_t mhi_channel_read_multiple(mhi_handle_t dev_h, uint32 ch_id, void **data_array,
                                       const uint32 *size_array, uint32 num_elements,
                                       uint32 *num_submitted, mhi_cb_t *cb)
{
   return MHI_NOT_SUPPORTED;
}

/**
 * This function writes multiple data requests over an MHI channel. The operation
 * of this request will be asynchronous.
 *
 * The callback's payload will contain the actual number of bytes written in
 * bytes_rw.

 * @param[in]  dev_h  Device handle
 * @param[in]  ch_id  Channel ID
 * @param[in]  data_array     Array of write buffer addresses
 * @param[in]  size_array     Array of sizes of the data buffers in bytes
 * @param[in]  num_elements   Number of buffers in data and size arrays
 * @param[out] num_submitted  Number of buffers that were actually submitted
 * @param[in]  cb     Callback type for asynchronous operation
 * @param[in]  eot    Whether or not this is the end of a transfer
 *
 * @dependencies mhi_channel_open must be called first.
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 *         * MHI_CH_INVALID: the channel is invalid
 *         * MHI_CH_INVALID_WRITE: channel direction does not permit a write
 *         * MHI_INVALID_ADDR: the data address is invalid
 *         * MHI_PENDING: a result will be notified asynchronously; all buffers
 *                        accepted
 *         * MHI_OP_FULL: internal queue full and not all buffers accepted;
 *                        check num_submitted
 */
mhi_status_t mhi_channel_write_multiple(mhi_handle_t dev_h, uint32 ch_id, const void **data_array,
                                        const uint32 *size_array, uint32 num_elements,
                                        uint32 *num_submitted, mhi_cb_t *cb, boolean eot)
{
   return MHI_NOT_SUPPORTED;
}

/**
 * This function aborts channel operations that have not been completed.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  ch_id  Channel ID
 *
 * @dependencies mhi_channel_open must be called first.
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 *         * MHI_CH_INVALID: the channel is invalid
 */
mhi_status_t mhi_channel_abort(mhi_handle_t dev_h, uint32 ch_id)
{
   return MHI_NOT_SUPPORTED;
}

/**
 * This function gets the current execution environment.
 *
 * @param[in]  dev_h  Device handle
 * @param[out] ee     Execution environment
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_get_ee(mhi_handle_t dev_h, mhi_ee_t *ee)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;

   if (IS_NULL(dev_h))
   {
      return MHI_INVALID_PARAM;
   }
   status = mhi_dev_get_ee(client_ctxt->dev, ee);

   return mhi_convert_internal_status(status);
}

mhi_status_t mhi_get_state(mhi_handle_t dev_h, mhi_state_t *state)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;

   if (IS_NULL(dev_h))
   {
      return MHI_INVALID_PARAM;
   }
   status = mhi_get_device_state(client_ctxt->dev, state);

   return mhi_convert_internal_status(status);
}

/**
 * This function is used to transfer an image. The device must be in the appropriate
 * execution environment.
 *
 * The image address must be a 4K-aligned physical address.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  image  Image start address
 * @param[in]  size   Image size
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_transfer_image(mhi_handle_t dev_h, void *image, size_t size)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;

   if (IS_NULL(dev_h) || IS_NULL(image) || size == 0)
   {
      MHI_LOG_ERROR("mhi_transfer_image: Invalid parameters");
      return MHI_INVALID_PARAM;
   }

   if (!MHI_IS_ALIGNED((uint64)image, 4096))
   {
      /* Address is not 4K aligned */
      MHI_LOG_ERROR("mhi_transfer_image: Address is not 4k aligned");
      return MHI_INVALID_PARAM;
   }

   status = mhi_dev_transfer_image(client_ctxt->dev, image, size);

   return mhi_convert_internal_status(status);
}

mhi_status_t mhi_execute_bhie(mhi_handle_t dev_h, void *image, size_t size)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;

   if (IS_NULL(dev_h) || IS_NULL(image) || size == 0)
   {
      MHI_LOG_ERROR("mhi_transfer_image: Invalid parameters");
      return MHI_INVALID_PARAM;
   }

   status =  mhi_dev_execute_bhie(client_ctxt->dev, image, size);

   return mhi_convert_internal_status(status);
}


/**
 * This function places a vote on a resource node.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  node   Resource node
 * @param[in]  state  Desired state (aggregated with votes from other clients)
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_issue_request(mhi_handle_t dev_h, mhi_node_t node, uint32 state)
{
    mhi_status_t status = 0;
	mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
#ifdef MHI_PROFILING_ENABLED
        uint64 start_time;
        uint64 end_time;
        uint64 pcycle_start;
        uint64 pcycle_end;
#endif
	
	if (IS_NULL(dev_h) || (node >= MHI_MAX_NUM_NODES))
	{
		return MHI_INVALID_PARAM;
	}
   
#ifdef MHI_PROFILING_ENABLED
       //start_time = pcie_osal_get_systime_ticks();
	pcycle_start = qurt_get_core_pcycles();
#endif

	status = mhi_drv_issue_request(client_ctxt, node, state);

#ifdef MHI_PROFILING_ENABLED
        pcycle_end = qurt_get_core_pcycles();
        pcycle_end = pcycle_end - pcycle_start;
        //end_time = pcie_osal_get_systime_ticks();
        //end_time = pcie_osal_get_elapsed_time(start_time, end_time, PCIE_OSAL_TIME_UNIT_US);
        //MHI_PROFILE_MED("mhi_issue_request : time elapsed %d us and %d pcycles", pcie_osal_get_elapsed_time(start_time, end_time, PCIE_OSAL_TIME_UNIT_US), (pcycle_end - pcycle_start));
        MHI_PROFILE_MED("mhi_issue_request :  %d pcycles", pcycle_end);
#endif
	return mhi_convert_internal_status(status);
}

/**
 * This function releases the current vote on a resource node.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  node   Resource node
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_complete_request(mhi_handle_t dev_h, mhi_node_t node)
{
    mhi_status_t status = 0;
	mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;

	if (IS_NULL(dev_h) || (node >= MHI_MAX_NUM_NODES))
	{
		return MHI_INVALID_PARAM;
	}
	
	status = mhi_drv_complete_request(client_ctxt, node);
	return mhi_convert_internal_status(status);
}
 
/**
 * This function is used to trigger a shutdown of the device. The procedure is:
 *  - Callback MHI_DEV_SHUTDOWN_REQ will be issued to all clients
 *  - Clients finish up activity then release MHI resources
 *  - Clients call mhi_dev_close after they have stopped accessing the device
 *    and released MHI resources
 *  - Power can be removed only after the callback specified in mhi_dev_close
 *    has been issued
 *
 * @param[in]  dev_h  Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_trigger_shutdown(mhi_handle_t dev_h)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;

   if (IS_NULL(dev_h))
   {
      return MHI_INVALID_PARAM;
   }

   status = mhi_drv_trigger_shutdown(client_ctxt->dev);

   return mhi_convert_internal_status(status);
}

 /**
 * This function is used to trigger an MHI SYS ERR on the device. If clients
 * should be notified, they must immediately stop accessing the device, release
 * MHI resources, and close the device.
 *
 * @param[in]  dev_h           Device handle
 * @param[in]  notify_clients  Whether to notify clients a SYS ERR has occurred
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_trigger_sys_err(mhi_handle_t dev_h, boolean notify_clients)
{
    mhi_status_t status = SUCCESS;
	mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;

	if (IS_NULL(dev_h)) 
	{
		MHI_LOG_ERROR("ERROR : mhi.c : mhi_trigger_sys_err : NULL Param");
		return MHI_INVALID_PARAM;
	}

	MHI_LOG_HIGH("mhi_trigger_sys_err : Triggering sys error on device");	
	status = mhi_dev_trigger_sys_error(client_ctxt->dev, notify_clients);
	if(status != MHI_SUCCESS)
	{
		MHI_LOG_ERROR("ERROR : mhi.c : mhi_trigger_sys_err : errno : %d",status);
	}
	
	return mhi_convert_internal_status(status);
}

 /**
 * This function is used to trigger an MHI reset on the device. 
 *
 * @param[in]  dev_h           Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_trigger_device_reset(mhi_handle_t dev_h)
{
    mhi_status_t status = SUCCESS;
	mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;

	if (IS_NULL(dev_h)) 
	{
		MHI_LOG_ERROR("ERROR : mhi.c : mhi_trigger_device_reset : NULL Param");
		return MHI_INVALID_PARAM;
	}
	
	status = mhi_dev_trigger_device_reset(client_ctxt->dev);
	if(status != MHI_SUCCESS)
	{
		MHI_LOG_ERROR("ERROR : mhi.c : mhi_trigger_device_reset : errno : %d",status);
	}
	
	return mhi_convert_internal_status(status);
}

/**
 * This function is used to get the resources for a particular device.
 *
 * @param[in]  dev_h      Device handle
 * @param[out] resources  Device's resources
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_get_resources(mhi_handle_t dev_h, mhi_resources_t *resources)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;

   if (IS_NULL(dev_h) || IS_NULL(resources))
   {
      return MHI_INVALID_PARAM;
   }

   status = mhi_dev_get_resources(client_ctxt->dev, resources);

   return mhi_convert_internal_status(status);
}

/**
 * This function is used to register an interrupt.
 *
 * @param[in]  dev_h           Device handle
 * @param[in]  vector          Vector index
 * @param[in]  cb              Interrupt callback
 * @param[in]  ctxt            Callback context
 * @param[out] trigger_params  Parameters used to trigger the interrupt
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_int_register(mhi_handle_t dev_h, uint32 vector, mhi_int_cb_t cb,
                              void *ctxt, mhi_int_trigger_params_t *trigger_params)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;

   if (IS_NULL(dev_h) || IS_NULL(cb) || IS_NULL(trigger_params))
   {
      return MHI_INVALID_PARAM;
   }

   status = mhi_dev_int_register(client_ctxt->dev, vector, cb, ctxt, trigger_params);

   return mhi_convert_internal_status(status);
}

/**
 * This function is used to unregister an interrupt.
 *
 * @param[in]  dev_h  Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_int_unregister(mhi_handle_t dev_h, uint32 vector)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;

   if (IS_NULL(dev_h))
   {
      return MHI_INVALID_PARAM;
   }

   status = mhi_dev_int_unregister(client_ctxt->dev, vector);

   return mhi_convert_internal_status(status);
}

/**
 * This function is used to synchronize time between host and device by capturing
 * the corresponding timestamps.
 *
 * @param[in]  dev_h        Device handle
 * @param[out] local_ticks  Host time in ticks
 * @param[out] dev_ticks    Device time in ticks
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_sync_time(mhi_handle_t dev_h, uint64 *local_ticks, uint64 *dev_ticks)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   int32 status;

   if (IS_NULL(dev_h))
   {
      return MHI_INVALID_PARAM;
   }

   status = mhi_dev_sync_time(client_ctxt->dev, local_ticks, dev_ticks);

   return mhi_convert_internal_status(status);
}
