/*=============================================================================

                            SLVCOM CORE

 Slave Communication Core.

 Copyright 2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/dev/core.boot/6.1/batta.core.boot.6.1.tip/QcomPkg/Library/SlvcomLib/src/slvcom_core.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/


/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "com_dtypes.h"
#include "slvcom.h"

/**
 * Operation type
 */
typedef enum
{
  SLVCOM_OPERATION_REG  = 1,
  SLVCOM_OPERATION_FIFO = 2,
  SLVCOM_OPERATION_AHB  = 3,
} slvcom_operation_type;

/*=============================================================================

                     LOCAL FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
  FUNCTION  slvcom_update_activity
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static void slvcom_update_activity(void)
{
	return;
}

/*=============================================================================
  FUNCTION  slvcom_internal_write
=============================================================================*/
/**
 * Common write
 *
 */
/*===========================================================================*/
static slvcom_err_type slvcom_internal_write
(
  slvcom_operation_type operation,
  uint8                reg_start_addr,
  slvcom_ahb_addr_type  ahb_addr,
  uint32               num_words,
  uint8                *write_buf,
  uint32               write_buf_size,
  boolean              update_activity
)
{
  return 0;
}

/*=============================================================================
  FUNCTION  slvcom_internal_read
=============================================================================*/
/**
 * Common read
 *
 */
/*===========================================================================*/
static slvcom_err_type slvcom_internal_read
(
  slvcom_operation_type operation,
  uint8                reg_start_addr,
  slvcom_ahb_addr_type  ahb_addr,
  uint32               num_words,
  uint8                *read_buf,
  uint32               read_buf_size,
  boolean              update_activity
)
{
  return 0;
}

/*=============================================================================
  FUNCTION  slvcom_slave_wakeup
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static slvcom_err_type slvcom_slave_wakeup(void)
{
  return 0;
  
}

#if defined(SLVCOM_FEATURE_FULL_SUPPORT)
/*=============================================================================
  FUNCTION  slvcom_queue_notify_event
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static void slvcom_queue_notify_event
(
  slvcom_event_type      event,
  slvcom_event_data_type *event_data
)
{
	return;
}

/*=============================================================================
  FUNCTION  slvcom_notify_client_events
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static void slvcom_notify_client_events(void)
{
	return;
}

/*=============================================================================
  FUNCTION  slvcom_inactivity_timer_cb
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static void slvcom_inactivity_timer_cb(void *unused)
{
	return;
}

/*=============================================================================
FUNCTION  slvcom_slave_status_auto_clear_handler
=============================================================================*/
/**
*
*
*/
/*===========================================================================*/
static void slvcom_slave_status_auto_clear_handler
(
  slvcom_reg_slave_status_auto_clear_type slave_status_auto_clear
)
{
	return;
}

/*=============================================================================
FUNCTION  slvcom_fifo_fill_handler
=============================================================================*/
/**
*
*
*/
/*===========================================================================*/
static void slvcom_fifo_fill_handler
(
  slvcom_reg_fifo_fill_type fifo_fill
)
{
	return;
}

/*=============================================================================
FUNCTION  slvcom_timestamp_handler
=============================================================================*/
/**
*
*
*/
/*===========================================================================*/
static void slvcom_timestamp_handler
(
  uint64 msm_timetick,
  uint32 slv_timestamp
)
{
	return;
}

/*=============================================================================
FUNCTION  slvcom_slave_status_handler
=============================================================================*/
/**
*
*
*/
/*===========================================================================*/
static void slvcom_slave_status_handler
(
  slvcom_reg_slave_status_type slave_status
)
{
	return;
}

/*=============================================================================
  FUNCTION  slvcom_slv_isr
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static void slvcom_slv_isr(void *unused)
{
	return;
}
#endif /* SLVCOM_FEATURE_FULL_SUPPORT */

/*=============================================================================
  FUNCTION  slvcom_client_write
=============================================================================*/
/**
 * Common write
 *
 */
/*===========================================================================*/
static slvcom_err_type slvcom_client_write
(
  slvcom_handle_type    handle,
  slvcom_operation_type operation,
  uint8                reg_start_addr,
  slvcom_ahb_addr_type  ahb_addr,
  uint32               num_words,
  uint8                *write_buf,
  uint32               write_buf_size
)
{
	return 0;
}

/*=============================================================================
  FUNCTION  slvcom_client_read
=============================================================================*/
/**
 * Common read
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_client_read
(
  slvcom_handle_type    handle,
  slvcom_operation_type operation,
  uint8                reg_start_addr,
  slvcom_ahb_addr_type  ahb_addr,
  uint32               num_words,
  uint8                *read_buf,
  uint32               read_buf_size
)
{
	return 0;
}

/*=============================================================================

                     PUBLIC FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
  FUNCTION  slvcom_init
=============================================================================*/
/**
 * Initializes the SLVCOM driver
 *
 */
/*===========================================================================*/
void slvcom_init(void)
{
	return;
}

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
)
{
	return 0;
}

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
)
{
  /* TODO */
  return 0;
}

/*=============================================================================
  FUNCTION  slvcom_deinit
=============================================================================*/
/**
 * De-Initializes the SLVCOM driver
 *
 */
/*===========================================================================*/
void slvcom_deinit(void)
{
	return;
} /* slvcom_deinit */

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
)
{
	return 0;
}

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
)
{
	return 0;
}

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
)
{
	return 0;
}

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
)
{
	return 0;
}

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
)
{
	return 0;
}

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
)
{
	return 0;
}

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
slvcom_err_type slvcom_secmode_enable(slvcom_handle_type handle)
{
	return 0;
}

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
slvcom_err_type slvcom_secmode_disable(slvcom_handle_type handle)
{
	return 0;
}
