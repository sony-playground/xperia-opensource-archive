/** 
 * MHI Host Protocol Interface
 *  
 * Copyright (c) 2021-2022 Qualcomm Technologies, Inc. All rights reserved.
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/21/21   nr      Initial version

=============================================================================*/

#include <Uefi.h>

#ifndef ___EFI_QC_MHI_PROTOCOL_H__
#define ___EFI_QC_MHI_PROTOCOL_H__

/* External global reference to the Kernel Protocol GUID */
extern EFI_GUID gEfiQcMhiDxeProtocolGuid;

/* Protocol GUID definition. { 715325D2-24A0-4FA2-B93A-6580C4D40E15 } */
#define EFI_QC_MHI_DXE_PROTOCOL_GUID \
         { 0x715325D2, 0x24A0, 0x4FA2, { 0xB9, 0x3A, 0x65, 0x80, 0xC4, 0xD4, 0x0E, 0x15 } }

/*
 *   Document the version changes here
 *   V 1.0
 *      Initial version
 *
 * */
#define EFI_QC_MHI_PROTOCOL_VER               0x00010000

/* Current protocol version */
#define EFI_QC_MHI_PROTOCOL_VERSION      EFI_QC_MHI_PROTOCOL_VER

/** The maximum number of memory sections per MHI device */
#define MHI_MAX_NUM_MEM_SECTIONS 6

/*******************************************************************************
 *
 *   Interface type definitions
 *
 ******************************************************************************/
#include "com_dtypes.h"

/** Return codes used by MHI APIs **/
typedef enum
{
   MHI_STATUS_SUCCESS             = 0x0,   /**< Operation was a success */
   MHI_STATUS_ERROR               = 0x1,   /**< Generic internal error */
   MHI_STATUS_INVALID_PARAM       = 0x2,   /**< Invalid parameters */
   MHI_STATUS_CH_INVALID          = 0x3,   /**< Invalid channel specified */
   MHI_STATUS_CH_NOT_IDLE         = 0x4,   /**< Channel not idle  */
   MHI_STATUS_CH_INVALID_READ     = 0x5,   /**< Channel read operation is invalid */
   MHI_STATUS_CH_INVALID_WRITE    = 0x6,   /**< Channel write operation is invalid */
   MHI_STATUS_INVALID_ADDR        = 0x7,   /**< Invalid address */
   MHI_STATUS_INVALID_TOKEN       = 0x8,   /**< Token is invalid */
   MHI_STATUS_INVALID_EVENT       = 0x9,   /**< Invalid notification event */
   MHI_STATUS_NOTIFY_FULL         = 0xA,   /**< MHI cannot accept any more notification requests */
   MHI_STATUS_PENDING             = 0xB,   /**< Action is pending; a cb will be returned */
   MHI_STATUS_ABORTED             = 0xC,   /**< Operation aborted */
   MHI_STATUS_OP_FULL             = 0xD,   /**< MHI operation queue full; cannot accept more requests */
   MHI_STATUS_AMSS_ENUMERATED     = 0xE,   /**< MHI stack enumerated in AMSS */
   MHI_STATUS_BOOT_ENUMERATED     = 0xF,   /**< MHI stack enumerated in BOOT */
   MHI_STATUS_DISABLED            = 0x10,  /**< MHI is disabled */
   MHI_STATUS_NOT_SUPPORTED       = 0x11,  /**< Not supported */
   _MHI_STATUS_CODE_MAX	          = 0x7fffffff, /**< Force enum size to 32-bit */
} MHI_STATUS;

/** MHI device IDs */
typedef enum
{
   /**< Device IDs for MHI devices */
   MHI_DEVICE_ID_SDX55        = 0x0306,
   MHI_DEVICE_ID_MOSELLE      = 0x1105,
   /**< Device ID corresponding to the host */
   MHI_DEVICE_ID_HOST         = 0x10000,
   /**< Device ID used to register for all IDs */
   MHI_DEVICE_ID_ALL          = 0xffffffff
} MHI_DEVICE_ID;

/** MHI operations **/
typedef enum
{
   MHI_OP_INVALID = 0x0,
   MHI_OP_OPEN = 0x1,
   MHI_OP_CLOSE,
   MHI_OP_NOTIFY,
   MHI_OP_WRITE,
   MHI_OP_WRITEM,
   MHI_OP_WRITEM_NOEOT,
   MHI_OP_READ,
   MHI_OP_READ_NULL,
   MHI_OP_READM,
   _MHI_OP_MAX = 0x7fffffff, /**< Force enum size to 32-bit */
} MHI_OP;

/** MHI notification events */
typedef enum
{
   /**< An MHI device has been connected */
   MHI_EVENT_DEV_CONNECTED = 0x0,

   /**< Execution environment has changed */
   MHI_EVENT_DEV_EE_CHANGED,

   /**< Shutdown has been requested; clients must:
         - Immediately complete pending activity
         - Stop accessing the device
         - Release MHI resources
         - Close the device */
   MHI_EVENT_DEV_SHUTDOWN_REQ,

   /**< A system error has occurred; clients must:
         - Immediately halt interacting with the device
         - Release MHI resources
         - Close the device */
   MHI_EVENT_DEV_SYS_ERR,

   /**< All clients have closed their device handles */
   MHI_EVENT_DEV_CLOSED,

   /**< An MHI channel has been disconnected */
   MHI_EVENT_CH_DISCONNECTED,

   /**< An MHI channel has been reconnected */
   MHI_EVENT_CH_RECONNECTED,

   _MHI_EVENT_MAX = 0x7fffffff,    /**< Force enum size to 32-bit */
} MHI_EVENT;

/** Memory configurations */
typedef enum
{
   MHI_MEM_CONFIG_DEFAULT  = 0x0,   /**< Default memory configuration */
   MHI_MEM_CONFIG_UNCACHED = 0x1,   /**< Uncached memory */
   MHI_MEM_CONFIG_CACHED   = 0x2,   /**< Cached memory */
   _MHI_MEM_CONFIG_MAX = 0x7fffffff,    /**< Force enum size to 32-bit */
} MHI_MEM_CONFIG;

/** MHI execution environments */
typedef enum
{
   MHI_EXEC_ENV_PBL  = 0x0,
   MHI_EXEC_ENV_SBL  = 0x1,
   MHI_EXEC_ENV_AMSS = 0x2,
   MHI_EXEC_ENV_RDDM = 0x3,
   _MHI_EXEC_ENV_ENV_I32=0x7fffffff,    /**< Force enum size to 32-bit */
} MHI_EXEC_ENV;

/** Defines the MHI states **/
typedef enum
{
   STATE_RESET=0x0,   /**< Reset or initial state of MHI device */
   STATE_READY=0x1,   /**< Ready state. Entered when device initializes MHI */
   STATE_M0=0x2,      /**< M0 state , entered when host sets MHISTATE = M0 */
   STATE_M1=0x3,      /**< M1 state , entered when device detects link inactivity */
   STATE_M2=0x4,      /**< M2 state , entered when host sets MHISTATE = M2 */
   STATE_M3=0x5,      /**< M3 state , entered when host sets MHISTATE = M3 */
   STATE_MAX,         /**< Number of valid M states */
   STATE_SYSERR=0xFF, /**< System Error state. Entered when device detects a system error */
   _STATE_I32=0x7fffffff, /**< Force enum size to 32-bit */
} MHI_STATE;


/** Device handle type */
typedef void *MHI_HANDLE;

/** Device information */
typedef struct
{
   MHI_DEVICE_ID dev_id;  /**< Device ID */
   uint32 instance_id;   /**< Unique ID for this device instance */
} MHI_DEV_INFO;

/** Payload for the callback function */
typedef struct
{
   void *user_data;          /**< User-supplied data */
   MHI_OP op;              /**< Operation performed */
   MHI_STATUS status;      /**< Status of the operation */
   MHI_DEV_INFO dev_info;  /**< Device info */
   uint32 ch_id;             /**< Channel ID */
   /**< Operation-specific payload */
   union _MHI_OPER_PAYLOAD
   {
      /**< For MHI_WRITE, MHI_READ, MHI_WRITEM & MHI_READM operations */
      struct _MHI_READWRITE_PAYLOAD
      {
         void *buffer;       /**< Buffer address */
         uint32 bytes_rw;    /**< Number of bytes read / written */
         boolean eot;        /**< Indicates EOT */
      } rw;
      /**< For MHI_NOTIFY operations */
      struct _MHI_NOTIF_PAYLOAD
      {
         MHI_EVENT event;  /**< Notification event */
      } notify;
   } op_payload;
} MHI_CB_PAYLOAD;

/**
 *  This is the type for user callback functions, which are called for
 *  asynchronous operations.
 *
 *  @param[in]  payload    Callback payload
 *
 *  @return None.
 */
typedef void (*MHI_CB_FN)(MHI_CB_PAYLOAD *payload);

/** MHI callback type supplied with some APIs to allow asynchronous
 *  notifications of the completion result */
typedef struct
{
   void *user_data;        /**< User-supplied data */
   MHI_CB_FN cb_func;  /**< User-supplied callback function */
} MHI_CB;

/** Memory resource structure */
typedef struct
{
   uint64 pa;    /**< Memory region's physical address */
   void *va;     /**< Memory region's virtual address */
   size_t size;  /**< Memory region's size */
} MHI_MEM_RESOURCE;

/** Resources structure */
typedef struct
{
   MHI_MEM_RESOURCE mem_sections[MHI_MAX_NUM_MEM_SECTIONS];  /**< Memory resources */
} MHI_RESOURCES;

/** Interrupt trigger parameters */
typedef struct
{
   uint64 iova;    /**< IO virtual address used for triggering the interrupt */
   uint32 data;    /**< Data value to write to the IOVA to trigger the interrupt */
   uint32 vector;  /**< Vector index */
} MHI_INT_TRIGGER_PARAMS;

/**
 *  This is the type for the interrupt callback function.
 *
 *  @param[in]  vector  Vector index
 *  @param[in]  ctxt    Callback context
 *
 *  @return None.
 */
typedef void (*MHI_INT_CB)(uint32 vector, void *ctxt);

/********************************************************************************
      API Prototypes
********************************************************************************/

typedef
MHI_STATUS (*MHI_REGISTER) (MHI_DEVICE_ID dev_id, MHI_CB *cb);

typedef
MHI_STATUS (*MHI_UNREGISTER) (MHI_DEVICE_ID dev_id, MHI_CB *cb);

typedef
MHI_STATUS (*MHI_DEV_OPEN) 
(
   const MHI_DEV_INFO *dev_info, 
   MHI_CB *cb, 
   MHI_HANDLE *dev_h
);

typedef
MHI_STATUS (*MHI_DEV_CLOSE)
(
   MHI_HANDLE dev_h, 
   MHI_CB *cb
);

typedef
MHI_STATUS (*MHI_TRANSFER_IMAGE)
(
   MHI_HANDLE dev_h,
   void *image,
   size_t size
);

typedef
MHI_STATUS (*MHI_EXECUTE_BHIE)
(
   MHI_HANDLE dev_h,
   void *image,
   size_t size
);

typedef
MHI_STATUS (*MHI_GET_EE)
(
   MHI_HANDLE dev_h,
   MHI_EXEC_ENV *current_env
);

typedef
MHI_STATUS (*MHI_GET_STATE)
(
   MHI_HANDLE dev_h,
   MHI_STATE *current_state
);

typedef
MHI_STATUS (*MHI_CHANNEL_OPEN)
(
   MHI_HANDLE dev_h,
   uint32 channel_id,
   MHI_CB *cb
);

typedef
MHI_STATUS (*MHI_CHANNEL_CLOSE)
(
   MHI_HANDLE dev_h,
   uint32 channel_id
);

typedef
MHI_STATUS (*MHI_CHANNEL_WRITE)
(
   MHI_HANDLE dev_h,
   uint32 channel_id,
   void* buf,
   uint32 size,
   uint32 *bytes_written,
   MHI_CB *cb
);

typedef
MHI_STATUS (*MHI_CHANNEL_READ)
(
   MHI_HANDLE dev_h,
   uint32 channel_id,
   void* buf,
   uint32 size,
   uint32 *bytes_read,
   boolean *eot,
   MHI_CB *cb
);

/* TBD - will add these later 
MHI_STATUS mhi_channel_open(mhi_handle_t dev_h, uint32 ch_id, mhi_cb_t *cb);

MHI_STATUS mhi_channel_close(mhi_handle_t dev_h, uint32 ch_id);

MHI_STATUS mhi_buffer_allocate(mhi_handle_t dev_h, MHI_MEM_CONFIG_t mem_cfg,
                                 void **buffer, uint32 size);

MHI_STATUS mhi_buffer_free(mhi_handle_t dev_h, MHI_MEM_CONFIG_t mem_cfg, void *buffer);

MHI_STATUS mhi_channel_write(mhi_handle_t dev_h, uint32 ch_id, void *data, uint32 size,
                               uint32 *bytes_written, mhi_cb_t *cb);

MHI_STATUS mhi_channel_read(mhi_handle_t dev_h, uint32 ch_id, void *data, uint32 size,
                              uint32 *bytes_read, boolean *eot, mhi_cb_t *cb);

MHI_STATUS mhi_channel_read_null(mhi_handle_t dev_h, uint32 ch_id, uint32 size,
                                   uint32 *bytes_read, mhi_cb_t *cb);

MHI_STATUS mhi_channel_read_multiple(mhi_handle_t dev_h, uint32 ch_id, void **data_array,
                                       const uint32 *size_array, uint32 num_elements,
                                       uint32 *num_submitted, mhi_cb_t *cb);

MHI_STATUS mhi_channel_write_multiple(mhi_handle_t dev_h, uint32 ch_id, const void **data_array,
                                        const uint32 *size_array, uint32 num_elements,
                                        uint32 *num_submitted, mhi_cb_t *cb, boolean eot);

MHI_STATUS mhi_channel_abort(mhi_handle_t dev_h, uint32 ch_id);

MHI_STATUS mhi_get_ee(mhi_handle_t dev_h, MHI_EXEC_ENV_t *ee);

MHI_STATUS mhi_get_resources(mhi_handle_t dev_h, mhi_resources_t *resources);

MHI_STATUS mhi_int_register(mhi_handle_t dev_h, uint32 vector, mhi_int_cb_t cb,
                              void *ctxt, mhi_int_trigger_params_t *trigger_params);

MHI_STATUS mhi_int_unregister(mhi_handle_t dev_h, uint32 vector);

MHI_STATUS mhi_int_enable(mhi_handle_t dev_h, uint32 vector);

MHI_STATUS mhi_int_disable(mhi_handle_t dev_h, uint32 vector);

MHI_STATUS mhi_issue_request(mhi_handle_t dev_h, mhi_node_t node, uint32 state);

MHI_STATUS mhi_complete_request(mhi_handle_t dev_h, mhi_node_t node);

MHI_STATUS mhi_trigger_shutdown(mhi_handle_t dev_h);

MHI_STATUS mhi_trigger_sys_err(mhi_handle_t dev_h, boolean notify_clients);

MHI_STATUS mhi_trigger_device_reset(mhi_handle_t dev_h);

MHI_STATUS mhi_sync_time(mhi_handle_t dev_h, uint64 *local_ticks, uint64 *dev_ticks);
*/

/*===========================================================================
                    PROTOCOL INTERFACE
===========================================================================*/

typedef struct {
   UINT64                   Version;

   MHI_REGISTER             Register;
   MHI_UNREGISTER           Unregister;
   MHI_DEV_OPEN             OpenDevice;
   MHI_DEV_CLOSE            CloseDevice;
   MHI_TRANSFER_IMAGE       TransferImage;
   MHI_EXECUTE_BHIE         ExecuteBhie;
   MHI_GET_EE               GetExecEnv;
   MHI_GET_STATE            GetState;
   MHI_CHANNEL_OPEN         ChannelOpen;
   MHI_CHANNEL_CLOSE        ChannelClose;
   MHI_CHANNEL_WRITE        ChannelWrite;
   MHI_CHANNEL_READ         ChannelRead;

}EFI_QC_MHI_DXE_PROTOCOL;

extern EFI_QC_MHI_DXE_PROTOCOL* gQcMhi;

#endif  /* ___EFI_QC_MHI_PROTOCOL_H__ */
