#ifndef MHI_H
#define MHI_H
/**
 *  @file mhi.h
 *
 *  @brief This header file defines the public interface to the MHI driver.
 */
/*============================================================================
               Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "com_dtypes.h"
#include <stddef.h>

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
/**
 *  This macro can be used to check if an operation is part of a class of
 *  operations. For example, MHI_OP_CLASS(MHI_WRITE) can be used to check
 *  if the operation was one of the different write operations.
 */
#define MHI_OP_CLASS(op) ((op) &~(_MHI_OP_PER_CLASS - 1))

/** The maximum number of memory sections per MHI device */
#define MHI_MAX_NUM_MEM_SECTIONS 6

/** Macros for node states */
#define MHI_NODE_STATE_ASSERTED 1
#define MHI_NODE_STATE_DEASSERTED 0

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/** Return codes used by MHI APIs **/
typedef enum
{
   MHI_SUCCESS             = 0x0,   /**< Operation was a success */
   MHI_ERROR               = 0x1,   /**< Generic internal error */
   MHI_INVALID_PARAM       = 0x2,   /**< Invalid parameters */
   MHI_CH_INVALID          = 0x3,   /**< Invalid channel specified */
   MHI_CH_NOT_IDLE         = 0x4,   /**< Channel not idle  */
   MHI_CH_INVALID_READ     = 0x5,   /**< Channel read operation is invalid */
   MHI_CH_INVALID_WRITE    = 0x6,   /**< Channel write operation is invalid */
   MHI_INVALID_ADDR        = 0x7,   /**< Invalid address */
   MHI_INVALID_TOKEN       = 0x8,   /**< Token is invalid */
   MHI_INVALID_EVENT       = 0x9,   /**< Invalid notification event */
   MHI_NOTIFY_FULL         = 0xA,   /**< MHI cannot accept any more notification requests */
   MHI_PENDING             = 0xB,   /**< Action is pending; a cb will be returned */
   MHI_ABORTED             = 0xC,   /**< Operation aborted */
   MHI_OP_FULL             = 0xD,   /**< MHI operation queue full; cannot accept more requests */
   MHI_AMSS_ENUMERATED     = 0xE,   /**< MHI stack enumerated in AMSS */
   MHI_BOOT_ENUMERATED     = 0xF,   /**< MHI stack enumerated in BOOT */
   MHI_DISABLED            = 0x10,  /**< MHI is disabled */
   MHI_NOT_SUPPORTED       = 0x11,  /**< Not supported */
   _MHI_CODE_I32	   = 0x7fffffff, /**< Force enum size to 32-bit */
} mhi_status_t;

/** MHI device IDs */
typedef enum
{
   /**< Device IDs for MHI devices */
   MHI_DEV_ID_SDX55        = 0x0306,
   MHI_DEV_ID_HSP          = 0x1103,
   MHI_DEV_ID_MOSELLE      = 0x1105,
   MHI_DEV_ID_HMT          = 0x1107,
   /**< Device ID corresponding to the host */
   MHI_DEV_ID_HOST         = 0x10000,
   /**< Device ID used to register for all IDs */
   MHI_DEV_ID_ALL          = 0xffffffff
} mhi_dev_id_t;

/** MHI operations **/
typedef enum
{
   _MHI_OP_PER_CLASS = 8, /* Define class grouping for common operations */
   MHI_INVALID = 0x0,
   MHI_OPEN = 0x1,
   MHI_CLOSE,
   MHI_NOTIFY,
   MHI_WRITE = _MHI_OP_PER_CLASS * 1,
   MHI_WRITEM,
   MHI_WRITEM_NOEOT,
   MHI_READ = _MHI_OP_PER_CLASS * 2,
   MHI_READ_NULL,
   MHI_READM,
   _MHI_OP_I32=0x7fffffff, /**< Force enum size to 32-bit */
} mhi_op_t;

/** MHI notification events */
typedef enum
{
   /**< An MHI device has been connected */
   MHI_DEV_CONNECTED = 0x0,

   /**< Execution environment has changed */
   MHI_DEV_EE_CHANGED,

   /**< Shutdown has been requested; clients must:
         - Immediately complete pending activity
         - Stop accessing the device
         - Release MHI resources
         - Close the device */
   MHI_DEV_SHUTDOWN_REQ,

   /**< A system error has occurred; clients must:
         - Immediately halt interacting with the device
         - Release MHI resources
         - Close the device */
   MHI_DEV_SYS_ERR,

   /**< All clients have closed their device handles */
   MHI_DEV_CLOSED,

   /**< An MHI channel has been disconnected */
   MHI_CH_DISCONNECTED,

   /**< An MHI channel has been reconnected */
   MHI_CH_RECONNECTED,

   /**< The number of events */
   _MHI_NUM_EVENTS,

   _MHI_EVENT_I32=0x7fffffff,    /**< Force enum size to 32-bit */
} mhi_event_t;

/** Memory configurations */
typedef enum
{
   MHI_MEM_CFG_DEFAULT  = 0x0,   /**< Default memory configuration */
   MHI_MEM_CFG_UNCACHED = 0x1,   /**< Uncached memory */
   MHI_MEM_CFG_CACHED   = 0x2,   /**< Cached memory */
   _MHI_NUM_MEM_CFGS,            /**< Number of configs */
   _MHI_MEM_TYPE_I32=0x7fffffff,    /**< Force enum size to 32-bit */
} mhi_mem_cfg_t;

/** MHI execution environments */
typedef enum
{
   MHI_EE_PBL  = 0x0,
   MHI_EE_SBL  = 0x1,
   MHI_EE_AMSS = 0x2,
   MHI_EE_RDDM = 0x3,
   _MHI_EE_ENV_I32=0x7fffffff,    /**< Force enum size to 32-bit */
} mhi_ee_t;

/** Defines the MHI states **/
typedef enum _mhi_state
{
   MHI_STATE_RESET=0x0,   /**< Reset or initial state of MHI device */
   MHI_STATE_READY=0x1,   /**< Ready state. Entered when device initializes MHI */
   MHI_STATE_M0=0x2,      /**< M0 state , entered when host sets MHISTATE = M0 */
   MHI_STATE_M1=0x3,      /**< M1 state , entered when device detects link inactivity */
   MHI_STATE_M2=0x4,      /**< M2 state , entered when host sets MHISTATE = M2 */
   MHI_STATE_M3=0x5,      /**< M3 state , entered when host sets MHISTATE = M3 */
   MHI_STATE_MAX,         /**< Number of valid M states */
   MHI_STATE_SYSERR=0xFF, /**< System Error state. Entered when device detects a system error */
   _MHI_STATE_I32=0x7fffffff, /**< Force enum size to 32-bit */
} mhi_state_t;

/** Resource nodes */
typedef enum
{
   /**< Device wake is used to keep the device in M0:
         - Asserted: keeps the device in M0
         - Deasserted / completed: MHI low power modes are allowed on the device */
   MHI_NODE_DEVICE_WAKE,

   /**< Bus vote is used to keep the bus in an active state, allowing direct access to
        the device's memory regions. Accessing the device's memory regions is not allowed
        unless the bus is in the active state. Votes include:
         - Asserted: the bus is enabled and latency is governed by MHI_NODE_ACTIVE_BUS_LATENCY_US
         - Deasserted / completed: the bus is in a low power state and latency is governed by
           MHI_NODE_BUS_RESUME_LATENCY_US; the device's memory region must not be accessed */
   MHI_NODE_BUS_VOTE,

   /**< Active bus latency, in us, is used to determine the deepest active-state
        low power mode the bus may enter, based on the latency clients can
        tolerate. Complete the vote to remove it */
   MHI_NODE_ACTIVE_BUS_LATENCY_US,

   /**< Bus resume latency, in us, is used to determine the deepest sleep state
        the bus can enter, based on how long clients can tolerate for bus resume.
        Complete the vote to remove it */
   MHI_NODE_BUS_RESUME_LATENCY_US,

   /**< Node for P1 entry delay */
   MHI_NODE_BUS_P1_ENTRY_DELAY,
  
   /**< Node for P2 entry delay */
   MHI_NODE_BUS_P2_ENTRY_DELAY,
   
   /* Maximum number of nodes supported */
   MHI_MAX_NUM_NODES,
   
   _MHI_RES_I32=0x7fffffff,    /**< Force enum size to 32-bit */
} mhi_node_t;

/** Device handle type */
typedef void *mhi_handle_t;

/** Device information */
typedef struct
{
   mhi_dev_id_t dev_id;  /**< Device ID */
   uint32 instance_id;   /**< Unique ID for this device instance */
} mhi_dev_info_t;

/** Payload for the callback function */
typedef struct
{
   void *user_data;          /**< User-supplied data */
   mhi_op_t op;              /**< Operation performed */
   mhi_status_t status;      /**< Status of the operation */
   mhi_dev_info_t dev_info;  /**< Device info */
   uint32 ch_id;             /**< Channel ID */
   /**< Operation-specific payload */
   union _mhi_op_payload
   {
      /**< For MHI_WRITE, MHI_READ, MHI_WRITEM & MHI_READM operations */
      struct _mhi_rw_payload
      {
         void *buffer;       /**< Buffer address */
         uint32 bytes_rw;    /**< Number of bytes read / written */
         boolean eot;        /**< Indicates EOT */
      } rw;
      /**< For MHI_NOTIFY operations */
      struct _mhi_notify_payload
      {
         mhi_event_t event;  /**< Notification event */
      } notify;
   } op_payload;
} mhi_cb_payload_t;

/**
 *  This is the type for user callback functions, which are called for
 *  asynchronous operations.
 *
 *  @param[in]  payload    Callback payload
 *
 *  @return None.
 */
typedef void (*mhi_cb_func_t)(mhi_cb_payload_t *payload);

/** MHI callback type supplied with some APIs to allow asynchronous
 *  notifications of the completion result */
typedef struct
{
   void *user_data;        /**< User-supplied data */
   mhi_cb_func_t cb_func;  /**< User-supplied callback function */
} mhi_cb_t;

/** Memory resource structure */
typedef struct
{
   uint64 pa;    /**< Memory region's physical address */
   void *va;     /**< Memory region's virtual address */
   size_t size;  /**< Memory region's size */
} mhi_mem_resource_t;

/** Resources structure */
typedef struct
{
   mhi_mem_resource_t mem_sections[MHI_MAX_NUM_MEM_SECTIONS];  /**< Memory resources */
} mhi_resources_t;

/** Interrupt trigger parameters */
typedef struct
{
   uint64 iova;    /**< IO virtual address used for triggering the interrupt */
   uint32 data;    /**< Data value to write to the IOVA to trigger the interrupt */
   uint32 vector;  /**< Vector index */
} mhi_int_trigger_params_t;

/**
 *  This is the type for the interrupt callback function.
 *
 *  @param[in]  vector  Vector index
 *  @param[in]  ctxt    Callback context
 *
 *  @return None.
 */
typedef void (*mhi_int_cb_t)(uint32 vector, void *ctxt);

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/**
 * This function initializes the MHI driver.
 *
 * @attention This function must not be called directly by clients.
 *
 * @return MHI_SUCCESS indicates the operation succeeded.
 */
mhi_status_t mhi_init(void);

/**
 * This function registers for MHI_DEV_CONNECTED events. Notifications occur
 * asynchronously through the callback provided.
 *
 * @param[in]  dev_id  Device ID for which to receive notifications
 * @param[in]  cb      Callback structure (callback function and context)
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_register(mhi_dev_id_t dev_id, mhi_cb_t *cb);

/**
 * This function unregisters for MHI_DEV_CONNECTED events.
 *
 * @param[in]  dev_id  Device ID for which to receive notifications
 * @param[in]  cb      Callback structure (callback function and context)
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_unregister(mhi_dev_id_t dev_id, mhi_cb_t *cb);

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
mhi_status_t mhi_dev_open(const mhi_dev_info_t *dev_info, mhi_cb_t *cb, mhi_handle_t *dev_h);

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
mhi_status_t mhi_dev_close(mhi_handle_t dev_h, mhi_cb_t *cb);

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
mhi_status_t mhi_channel_open(mhi_handle_t dev_h, uint32 ch_id, mhi_cb_t *cb);

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
 *         * MHI_CH_NOT_IDLE: the channel is not in DISABLED / ENABLED state
 */
mhi_status_t mhi_channel_close(mhi_handle_t dev_h, uint32 ch_id);

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
                                 void **buffer, uint32 size);

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
mhi_status_t mhi_buffer_free(mhi_handle_t dev_h, mhi_mem_cfg_t mem_cfg, void *buffer);

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
mhi_status_t mhi_channel_write(mhi_handle_t dev_h, uint32 ch_id, void *data, uint32 size,
                               uint32 *bytes_written, mhi_cb_t *cb);

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
mhi_status_t mhi_channel_read(mhi_handle_t dev_h, uint32 ch_id, void *data, uint32 size,
                              uint32 *bytes_read, boolean *eot, mhi_cb_t *cb);

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
                                   uint32 *bytes_read, mhi_cb_t *cb);

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
                                       uint32 *num_submitted, mhi_cb_t *cb);

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
                                        uint32 *num_submitted, mhi_cb_t *cb, boolean eot);

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
mhi_status_t mhi_channel_abort(mhi_handle_t dev_h, uint32 ch_id);

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
mhi_status_t mhi_get_ee(mhi_handle_t dev_h, mhi_ee_t *ee);

mhi_status_t mhi_get_state(mhi_handle_t dev_h, mhi_state_t *state);

/**
 * This function is used to transfer an image. The device must be in the appropriate
 * execution environment.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  image  Image start address
 * @param[in]  size   Image size
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_transfer_image(mhi_handle_t dev_h, void *image, size_t size);

/**
 * This function is used to transfer an image using the BHIe protocol. 
 * The device must be in the appropriate execution environment.
 *
 * @param[in]  dev_h  Device handle
 * @param[in]  image  Image start address
 * @param[in]  size   Image size
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_execute_bhie(mhi_handle_t dev_h, void *image, size_t size);


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
mhi_status_t mhi_get_resources(mhi_handle_t dev_h, mhi_resources_t *resources);

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
                              void *ctxt, mhi_int_trigger_params_t *trigger_params);

/**
 * This function is used to unregister an interrupt.
 *
 * @param[in]  dev_h  Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_int_unregister(mhi_handle_t dev_h, uint32 vector);

/**
 * This function is used to enable an interrupt. Interrupts are enabled by
 * default.
 *
 * @param[in]  dev_h  Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_int_enable(mhi_handle_t dev_h, uint32 vector);

/**
 * This function is used to disable an interrupt.
 *
 * @param[in]  dev_h  Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_int_disable(mhi_handle_t dev_h, uint32 vector);

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
mhi_status_t mhi_issue_request(mhi_handle_t dev_h, mhi_node_t node, uint32 state);

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
mhi_status_t mhi_complete_request(mhi_handle_t dev_h, mhi_node_t node);

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
mhi_status_t mhi_trigger_shutdown(mhi_handle_t dev_h);

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
mhi_status_t mhi_trigger_sys_err(mhi_handle_t dev_h, boolean notify_clients);

/**
 * This function is used to trigger a reset of the device.
 *
 * @param[in]  dev_h  Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
mhi_status_t mhi_trigger_device_reset(mhi_handle_t dev_h);

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
mhi_status_t mhi_sync_time(mhi_handle_t dev_h, uint64 *local_ticks, uint64 *dev_ticks);

#endif

