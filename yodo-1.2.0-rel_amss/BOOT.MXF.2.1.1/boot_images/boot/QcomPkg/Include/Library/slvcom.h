/*=============================================================================

                            SLVCOM APIs

 Slave Communication Interface.

 Copyright  2021 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/Library/slvcom.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/

#ifndef SLVCOM_H
#define SLVCOM_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "com_dtypes.h"
#include "stddef.h"
#include "string.h"  /* For Memset */

/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/
/**
 * Initializes the slvcom_open_config_type structure with default values.
 * Client should call this macro before setting the any structure members
 * of slvcom_open_config_type.
 */
#define SLVCOM_OPEN_CONFIG_INIT(open_config_ptr) \
  do{ \
    if(open_config_ptr) \
    { \
      memset((open_config_ptr), 0, sizeof(slvcom_open_config_type)); \
      (open_config_ptr)->events_required = 0xFFFFFFFF; \
    } \
  }while(0)

/** SLVCOM open configuration options */
#define SLVCOM_OPEN_OPT_NONE                  0x00000000

/** Slave Registers */
#define SLVCOM_REG_MSG_RD_REG_0                          0x00
#define SLVCOM_REG_MSG_RD_REG_1                          0x01
#define SLVCOM_REG_MSG_RD_REG_2                          0x02
#define SLVCOM_REG_MSG_RD_REG_3                          0x03
#define SLVCOM_REG_MSG_RD_REG_SPCL                       0x04
#define SLVCOM_REG_FIFO_FILL                             0x05
#define SLVCOM_REG_FIFO_SIZE                             0x06
#define SLVCOM_REG_MSG_WR_REG_0                          0x07
#define SLVCOM_REG_MSG_WR_REG_1                          0x08
#define SLVCOM_REG_MSG_WR_REG_2                          0x09
#define SLVCOM_REG_MSG_WR_REG_3                          0x0A
#define SLVCOM_REG_MSG_WR_REG_4                          0x0B
#define SLVCOM_REG_TO_SLAVE_FIFO                         0x20
#define SLVCOM_REG_TO_MASTER_FIFO                        0x20
#define SLVCOM_REG_TO_SLAVE_AHB                          0x21
#define SLVCOM_REG_TO_MASTER_AHB                         0x21

/** Redefinition of above macros to keep less changes in software */
#define SLVCOM_REG_TZ_TO_MASTER_STATUS        SLVCOM_REG_MSG_RD_REG_0
#define SLVCOM_REG_TZ_TO_MASTER_DATA          SLVCOM_REG_MSG_RD_REG_1
#define SLVCOM_REG_SLAVE_STATUS               SLVCOM_REG_MSG_RD_REG_2
#define SLVCOM_REG_TIMESTAMP                  SLVCOM_REG_MSG_RD_REG_3
#define SLVCOM_REG_SLAVE_STATUS_AUTO_CLEAR    SLVCOM_REG_MSG_RD_REG_SPCL
#define SLVCOM_REG_TZ_TO_SLAVE_COMMAND        SLVCOM_REG_MSG_WR_REG_0
#define SLVCOM_REG_TZ_TO_SLAVE_DATA           SLVCOM_REG_MSG_WR_REG_1
#define SLVCOM_REG_MASTER_STATUS              SLVCOM_REG_MSG_WR_REG_2
#define SLVCOM_REG_MASTER_COMMAND             SLVCOM_REG_MSG_WR_REG_3

/* Pass-through registers - defined above already */

/* Max Client name length */
#define SLVCOM_MAX_CLIENT_NAME_LENGTH         16       /* Including NULL */

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/
/**
 * Opaque handle returned by slvcom_open(). Client uses this handle to call into
 * SLVCOM API for any further operations.
 *
 * Client must not modify or try to interpret this value.
 */
typedef void* slvcom_handle_type;

/** SLVCOM status/return codes */
typedef enum {
  /* Success */
  SLVCOM_ERR_NONE = 0,

  /* Slave is reset */
  SLVCOM_ERR_RESET = -1,
  
  /* Invalid parameter is passed to SLVCOM functions */
  SLVCOM_ERR_INVALID_PARAM = -2,
  
  /* Error returned if slvcom client present with same name already */
  SLVCOM_ERR_DUPLICATE_CLIENT = -3,
  
  /* Out of resources */
  SLVCOM_ERR_OUT_OF_RESOURCES = -4,
  
  /* Slave is not responding to power up request */
  SLVCOM_ERR_NOT_RESPONSIVE = -5,
  
  /* GPIO Api error */
  SLVCOM_ERR_GPIO_ERR = -6,
  
  /* SPI Api error */
  SLVCOM_ERR_SPI_ERR = -7,
  
  /* This is returned if client tries to disable without enabling */
  SLVCOM_ERR_INVALID_SECMODE_ERR = -8,
  
  /* This is returned if client tries to disable without enabling */
  SLVCOM_ERR_SECMODE_NOT_ENABLED = -9,

  /* API or functionality is not supported */
  SLVCOM_ERR_NOT_SUPPORTED  = -10,
  
  /* SLVCOM Not Initialized */
  SLVCOM_ERR_NOT_INITIALIZED  = -11,
  
} slvcom_err_type;

/** Enums to identify Slave events */
typedef enum {
  SLVCOM_EVENT_NONE                          = 0,
  SLVCOM_EVENT_APPLICATION_RUNNING           = 1, /* event_data.application_running */
  SLVCOM_EVENT_TO_SLAVE_FIFO_READY           = 2, /* event_data.to_slave_fifo_ready */
  SLVCOM_EVENT_TO_MASTER_FIFO_READY          = 3, /* event_data.to_master_fifo_ready */
  SLVCOM_EVENT_AHB_READY                     = 4, /* event_data.ahb_ready */
  SLVCOM_EVENT_TO_MASTER_FIFO_USED           = 5, /* event_data.to_master_fifo_used */
  SLVCOM_EVENT_TO_SLAVE_FIFO_FREE            = 6, /* event_data.to_slave_fifo_free */
  SLVCOM_EVENT_TIMESTAMP                     = 7, /* event_data.timestamp */
  SLVCOM_EVENT_RESET_OCCURRED                = 8,
  SLVCOM_EVENT_ERROR_WRITE_FIFO_OVERRUN      = 9,
  SLVCOM_EVENT_ERROR_WRITE_FIFO_BUS_ERR      = 10,
  SLVCOM_EVENT_ERROR_WRITE_FIFO_ACCESS       = 11,
  SLVCOM_EVENT_ERROR_READ_FIFO_UNDERUN       = 12,
  SLVCOM_EVENT_ERROR_READ_FIFO_BUS_ERR       = 13,
  SLVCOM_EVENT_ERROR_READ_FIFO_ACCESS        = 14,
  SLVCOM_EVENT_ERROR_TRUNCATED_READ          = 15,
  SLVCOM_EVENT_ERROR_TRUNCATED_WRITE         = 16,
  SLVCOM_EVENT_ERROR_AHB_ILLEGAL_ADDRESS     = 17,
  SLVCOM_EVENT_ERROR_AHB_BUS_ERR             = 18,
  SLVCOM_EVENT_TO_MASTER_FIFO_RESET_COMPLETE = 19,
  SLVCOM_EVENT_TO_SLAVE_FIFO_RESET_COMPLETE  = 20,
  SLVCOM_EVENT_SLAVE_ERROR                   = 21,
  // SLVCOM_EVENT_BT_ERROR                      = 22,

  SLVCOM_EVENT_LAST = SLVCOM_EVENT_SLAVE_ERROR,
} slvcom_event_type;

/** Event specific data */
typedef union {
  uint32 unused;
  
  boolean application_running;      /* SLVCOM_EVENT_APPLICATION_RUNNING */
  boolean to_slave_fifo_ready;      /* SLVCOM_EVENT_TO_SLAVE_FIFO_READY */
  boolean to_master_fifo_ready;     /* SLVCOM_EVENT_TO_MASTER_FIFO_READY */
  boolean ahb_ready;                /* SLVCOM_EVENT_AHB_READY */
  // boolean dsp_error;                /* SLVCOM_EVENT_DSP_ERROR */
  // boolean bt_error;                 /* SLVCOM_EVENT_BT_ERROR */
  uint32 reserved : 2;
  
  uint16 to_master_fifo_used;       /* SLVCOM_EVENT_TO_MASTER_FIFO_USED */
  uint16 to_slave_fifo_free;        /* SLVCOM_EVENT_TO_SLAVE_FIFO_FREE */

  struct {
    uint64 msm_timetick;
    uint32 slv_timestamp;
  } timestamp;                      /* SLVCOM_EVENT_TIMESTAMP */
} slvcom_event_data_type;

/** 
 * This callback function is called by the SLVCOM to notify the 
 * Slave events
 * 
 * @note
 * This callback function may be called from interrupt context; clients must
 * not block or call any functions that block. Clients can call SLVCOM APIs. 
 */
typedef void (*slvcom_notification_cb)
(
  slvcom_handle_type     handle,     /* Client handle */
  void                  *priv,      /* Client private data pointer that was 
                                     * mentioned in the open configuration structure */
  slvcom_event_type      event,      /* Event (see slvcom_event_type enumeration) */
  slvcom_event_data_type *event_data /* Event specific data, 
                                     * see slvcom_event_data_type union */
);

/**
 * SLVCOM open configuration structure
 *
 * This structure is used by the clients to open a SLVCOM handle
 * when calling slvcom_open()
 */
typedef struct {
  /* Private data pointer for client to maintain context. 
   * This data is passed back to client in the notification callbacks */
  void                  *priv;
  
  /* string name for the slvcom client. Max SLVCOM_MAX_CLIENT_NAME_LENGTH length */
  const char            *name;
  
  /* Notification callbacks to notify the SLV events */
  slvcom_notification_cb notify_cb;

  /* Bitfield for specifying various required events */
  uint32                events_required;
  
  /* Bitfield for specifying various options, see SLVCOM_OPEN_OPT_### defines above */ 
  uint32                options;

} slvcom_open_config_type;

/** AHB address datatype */
typedef uint32 slvcom_ahb_addr_type;

/*=============================================================================

                    PUBLIC FUNCTION DECLARATIONS

=============================================================================*/

/*=============================================================================
  FUNCTION  slvcom_open
=============================================================================*/
/**
 * Opens/creates a handle to interact with Slave.
 *
 * @param[in]  open_config   Pointer to the open configuration structure.
 *                           This structure must filled by the clients.
 *                           Use SLVCOM_OPEN_CONFIG_INIT() macro function to 
 *                           initialize the structure before setting any 
 *                           member of structure.
 * @param[out]  handle       The handle to be used to interact with Slave.
 *
 * @return
 * Sets the handle and returns SLVCOM_ERR_NONE if function is successful,
 * otherwise returns status code (see slvcom_err_type enumeration).
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_open
(
  slvcom_open_config_type *open_config,
  slvcom_handle_type      *handle
);

/*=============================================================================
  FUNCTION  slvcom_close
=============================================================================*/
/**
 * Closes the specified handle. No further operation are allowed with Slave.
 *
 * @param[in/out]  handle     Client handle return by slvcom_open()..
 *
 * @return
 * Sets the handle to NULL and returns SLVCOM_ERR_NONE if function is
 * successful, otherwise returns status code (see slvcom_err_type enumeration).
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_close
(
  slvcom_handle_type *handle
);

/*=============================================================================
  FUNCTION  slvcom_reg_read
=============================================================================*/
/**
 * Read from the one or more contiguous registers.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  reg_start_addr 7bit start address of the registers to read from.
 * @param[in]  num_regs       Number of contiguous registers to read, starting
 *                            from reg_start_addr.
 * @param[out] read_buf       Buffer to read from the registers.
 * @param[in]  read_buf_size  Read Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_regs.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_reg_read
(
  slvcom_handle_type handle,
  uint8             reg_start_addr,
  uint8             num_regs,
  void              *read_buf,
  uint32            read_buf_size
);

/*=============================================================================
  FUNCTION  slvcom_reg_write
=============================================================================*/
/**
 * Write into the one or more contiguous registers.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  reg_start_addr 7bit start address of the registers to write into.
 * @param[in]  num_regs       Number of contiguous registers to write, starting
 *                            from reg_start_addr.
 * @param[in]  write_buf      Buffer to write into the registers.
 * @param[in]  write_buf_size Write Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_regs.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_reg_write
(
  slvcom_handle_type handle,
  uint8             reg_start_addr,
  uint8             num_regs,
  void              *write_buf,
  uint32            write_buf_size
);

/*=============================================================================
  FUNCTION  slvcom_fifo_read
=============================================================================*/
/**
 * Read data from the TO_MASTER_FIFO.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  num_words      Number of words(32bits) to read from the
 *                            TO_MASTER_FIFO.
 * @param[out] read_buf       Buffer to read from the TO_MASTER_FIFO.
 * @param[in]  read_buf_size  Read Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_words.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_fifo_read
(
  slvcom_handle_type handle,
  uint32            num_words,
  void              *read_buf,
  uint32            read_buf_size
);

/*=============================================================================
  FUNCTION  slvcom_fifo_write
=============================================================================*/
/**
 * Write data to the TO_SLAVE_FIFO.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  num_words      Number of words(32bits) to write to the
 *                            TO_SLAVE_FIFO.
 * @param[in]  write_buf      Buffer to write into the TO_SLAVE_FIFO.
 * @param[in]  write_buf_size Write Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_words.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_fifo_write
(
  slvcom_handle_type handle,
  uint32            num_words,
  void              *write_buf,
  uint32            write_buf_size
);

/*=============================================================================
  FUNCTION  slvcom_ahb_read
=============================================================================*/
/**
 * Slave AHB memory read.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  ahb_start_addr 32bit AHB start address.
 * @param[in]  num_words      Number of words(32bits) to read.
 * @param[out] read_buf       Buffer to read from the AHB memory.
 * @param[in]  read_buf_size  Read Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_words.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_ahb_read
(
  slvcom_handle_type   handle,
  slvcom_ahb_addr_type ahb_start_addr,
  uint32              num_words,
  void                *read_buf,
  uint32              read_buf_size
);

/*=============================================================================
  FUNCTION  slvcom_ahb_write
=============================================================================*/
/**
 * Slave AHB memory write.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  ahb_start_addr 32bit AHB start address.
 * @param[in]  num_words      Number of words(32bits) to write.
 * @param[in]  write_buf      Buffer to write into the AHB memory.
 * @param[in]  write_buf_size Write Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_words.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_ahb_write
(
  slvcom_handle_type   handle,
  slvcom_ahb_addr_type ahb_start_addr,
  uint32              num_words,
  void                *write_buf,
  uint32              write_buf_size
);

/*=============================================================================
  FUNCTION  slvcom_secmode_enable
=============================================================================*/
/**
 * THIS API IS ONLY AVAILABLE IN THE TZ
 *
 * Makes the NS(S=Secure) to Active low to indicate SECURE(TZ) communication
 * mode is active.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 */
/*===========================================================================*/
slvcom_err_type slvcom_secmode_enable(slvcom_handle_type handle);

/*=============================================================================
  FUNCTION  slvcom_secmode_disable
=============================================================================*/
/**
 * THIS API IS ONLY AVAILABLE IN THE TZ
 *
 * Makes the NS(S=Secure) to Active high to indicate SECURE(TZ) communication
 * mode is *not* active.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 */
/*===========================================================================*/
slvcom_err_type slvcom_secmode_disable(slvcom_handle_type handle);

/*=============================================================================
  FUNCTION  slvcom_init
=============================================================================*/
/**
 * Initializes SLVCOM Module.
 *
 * @return None
 * 
 * @sideeffects Fatals in case of any error.
 */
/*===========================================================================*/
void slvcom_init(void);

/*=============================================================================
  FUNCTION  slvcom_deinit
=============================================================================*/
/**
 * De-Initializes SLVCOM Module.
 *
 * @return None
 * 
 * @sideeffects Fatals in case of any error.
 */
/*===========================================================================*/
void slvcom_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* SLVCOM_H */
