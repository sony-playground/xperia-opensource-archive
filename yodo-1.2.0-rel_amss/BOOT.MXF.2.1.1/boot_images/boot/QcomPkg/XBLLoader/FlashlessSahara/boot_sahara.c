/*=============================================================================

                               Boot Sahara
                               Source File
GENERAL DESCRIPTION
  This file provides the implementation to enter the Sahara Protocol.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2019-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
02/11/22   rama    Support for enabling sahara logging feature
10/11/21   rhy     Media hw deinit (shutdown) removed from boot_sahara_exit
07/09/21   rhy     Added SAHARA_NAK_CABLE_DISCONNECT_ERROR as return status in transport layer disconnect
06/04/21   rhy     Removed packet size dependency on MAX PACKET SIZE from transport layer
04/27/21   rhy     Calculate bytes read from boot_sahara_handle_rx in boot_sahara_read
03/26/21   ck      Reduced number of boot_sahara_handle_read_data calls
02/12/21   vk      Add 64 bit handling
02/01/21   rhy     Enabled non blocking loading
09/25/20   rhy     Enabled memory debug
06/02/20   rhy     Added Blocking condition for max raw packet buffer
05/15/20   rhy     Removed static allocation of sahara buffers.
11/25/19   rhy     Initial revision.
=============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include <string.h>
#include "boot_sahara.h"
#include "boot_sahara_internal.h"
#include "boot_sahara_logging.h"
#include "boot_flashless_sahara_internal.h"


/**
 * Infinite loop
 */
#define INFINITE_LOOP() while(1)

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/
boot_sahara_info* curr_boot_sahara_info_pointer = NULL;

//===========================================================================
// Type declarations
//===========================================================================


//===========================================================================
//
//                      LOCAL FUNCTION DECLARATIONS
//
//===========================================================================
static void boot_sahara_handle_done( boot_sahara_info * const,
                                     uint32 );
static void boot_sahara_handle_done_resp( boot_sahara_info * const );
static void boot_sahara_handle_end_image_tx( boot_sahara_info * const );
static void boot_sahara_handle_hello( boot_sahara_info * const );
static void boot_sahara_handle_hello_resp( boot_sahara_info * const,
    uint32 length );
static uint32 boot_sahara_handle_rx( boot_sahara_info * const,
                                     uint8*,
                                     uint32,
                                     enum boot_sahara_bulk_error *,
                                     enum boot_sahara_packet_type,
                                     enum boot_sahara_is_blocking_flag );
static uint32 boot_sahara_handle_tx( boot_sahara_info * const,
                                     uint8* packet_buffer,
                                     uint32 length,
                                     enum boot_sahara_bulk_error *err_code);
static void boot_sahara_handle_read_data( boot_sahara_info * const,
                                          uint32 data_offset,
                                          uint32 data_length );
static void boot_sahara_handle_reset( boot_sahara_info * const,
                                      uint32 length );
static void boot_sahara_handle_reset_resp( boot_sahara_info * const );
static void boot_sahara_handle_cmd_ready( boot_sahara_info * const );
static void boot_sahara_handle_cmd_exec( boot_sahara_info * const,
                                         uint32 length );
static void boot_sahara_handle_cmd_exec_resp( boot_sahara_info * const );
static void boot_sahara_handle_cmd_exec_data( boot_sahara_info * const,
                                              uint32 length );
static void boot_sahara_handle_cmd_switch_mode( boot_sahara_info * const,
                                                uint32 length );
static void boot_sahara_handle_memory_read( boot_sahara_info * const,
                                            uint32 length);
static void boot_sahara_reset( boot_sahara_info * const );
static void boot_sahara_process_packets( boot_sahara_info * const,
                                         enum boot_sahara_context_flag);
static void boot_sahara_rx_cb ( uint32 bytes_read,
                                uint32 err_code );
static void boot_sahara_tx_cb ( uint32 bytes_written,
                                uint32 err_code );
static void boot_sahara_exec_cmd( boot_sahara_info * const,
                                  uint32);
static void boot_sahara_handle_memory_debug( boot_sahara_info * const );
static void boot_sahara_handle_memory_debug_64bit( boot_sahara_info * const );
static bl_error_boot_type boot_sahara_mem_debug_copy_restricted ( boot_sahara_info *,
                                                                  uintnt, uintnt,
                                                                  boot_boolean *);


/*===========================================================================

                      FUNCTION DEFINITIONS

===========================================================================*/

/*=========================================================================

**  Function :  _set_boot_sahara_info_pointer

** ==========================================================================
*/
/*!
*
* @brief
*   set the global handle pointer for sahara
*
* @param[in] boot device,device location pointer
*
*/
static void _set_boot_sahara_info_pointer(boot_sahara_info * const boot_sahara_info_ptr)
{
  curr_boot_sahara_info_pointer = boot_sahara_info_ptr;
}

/*=========================================================================

**  Function :  _get_boot_sahara_info_pointer

** ==========================================================================
*/
/*!
*
* @brief
*   return the global handle pointer for sahara
*
* @param[in] boot device,device location pointer
*
*/
static boot_sahara_info* _get_boot_sahara_info_pointer(void)
{
  return curr_boot_sahara_info_pointer;
}

/* ============================================================================
**  Function : Getter Functions from boot_sahara_info
** ============================================================================
*/
static boot_sahara_data*  _get_boot_sahara_data(boot_sahara_info *boot_sahara_info_ptr)
{
  return &(boot_sahara_info_ptr->sahara_data);
}

static boot_sahara_callback_parameters* _get_boot_sahara_callback_parameters (boot_sahara_info *boot_sahara_info_ptr)
{
  return &(boot_sahara_info_ptr->sahara_cb_parameters);
}

static boot_sahara_command_handler_if* _get_boot_sahara_command_handler_if (boot_sahara_info *boot_sahara_info_ptr)
{
  return (boot_sahara_info_ptr->sahara_cmd_handler_tbl);
}

static boot_sahara_cmd_exec_data* _get_boot_sahara_cmd_exec_data (boot_sahara_info *boot_sahara_info_ptr)
{
  return &(boot_sahara_info_ptr->sahara_cmd_data);
}

static boot_sahara_dispatch_tbl* _get_boot_sahara_dispatch_tbl (boot_sahara_info *boot_sahara_info_ptr)
{
  return boot_sahara_info_ptr->dispatch_tbl;
}

static ramdump_table_if* _get_boot_sahara_mem_debug_tbl (boot_sahara_info *boot_sahara_info_ptr)
{
  return (boot_sahara_info_ptr->mem_debug_handle).mem_debug_tbl;
}

static void* _get_boot_sahara_ramdump_dload_handle (boot_sahara_info *boot_sahara_info_ptr)
{
  return (boot_sahara_info_ptr->mem_debug_handle).ramdump_table_handle;
}

/* ============================================================================
**  Function : boot_sahara_get_boot_sahara_data_status
** ============================================================================
*/
/*!
*   @brief
*   Function to return Status of the protocol in boot_sahara_data
*
*   @param boot_sahara_info   -  [IN] Sahara Info tbl
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  boot_sahara_status
*
*   @sa None
*/
/*boot_sahara_status boot_sahara_get_boot_sahara_data_status(
                                        boot_sahara_info * const boot_sahara_info_ptr)
{
    return (boot_sahara_info_ptr->sahara_data).status;
}*/


/* ============================================================================
**  Function : boot_sahara_enumeration_init
** ============================================================================
*/
/*!
*   @brief
*   Function to enumerate transport layer for SAHARA
*
*   @param boot_sahara_dispatch_tbl   -  [IN] Sahara Dispatch tbl
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  bl_error_boot_type
*
*   @sa None
*/

bl_error_boot_type boot_sahara_enumeration_init(boot_sahara_dispatch_tbl* sahara_dispatch_tbl)
{
  bl_error_boot_type error = BL_ERR_NONE;

  if (sahara_dispatch_tbl == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }

  /* return for init() is void */
  sahara_dispatch_tbl->init();

  return error;
}

/* ============================================================================
**  Function : boot_sahara_enumeration_deinit
** ============================================================================
*/
/*!
*   @brief
*   Function to enumerate transport layer for SAHARA
*
*   @param boot_sahara_dispatch_tbl   -  [IN] Sahara Dispatch tbl
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  bl_error_boot_type
*
*   @sa None
*/

bl_error_boot_type boot_sahara_enumeration_deinit(boot_sahara_dispatch_tbl* sahara_dispatch_tbl)
{
  bl_error_boot_type error = BL_ERR_NONE;

  if (sahara_dispatch_tbl == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }

  /* return for shutdown() is void */
  sahara_dispatch_tbl->shutdown();

  return error;
}

void boot_sahara_set_last_image(boot_sahara_info *boot_sahara_info_ptr, boolean is_last_image)
{
  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  boot_sahara_data_ptr->is_last_image = is_last_image;
}



/* ============================================================================
**  Function : boot_sahara_rx_cb
** ============================================================================
*/
/*!
*   @brief
*   Callback for driver bulk receive. Sets the number of bytes read, error
*   code (if any), and completion flag.
*
*   @details
*   Callback for driver bulk receive. Sets the number of bytes read, error
*   code (if any), and completion flag.
*
*   @param bytes_read   -  [IN] Number of bytes read by driver
*   @param err_code     -  [IN] Error code returned by driver
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_rx_cb
(
  uint32 bytes_read,
  uint32 err_code
)
{
  boot_sahara_info *boot_sahara_info_ptr = _get_boot_sahara_info_pointer();

  /* Get callback parameters pointer from boot sahara info */
  boot_sahara_callback_parameters* callback_parameters_ptr =
    _get_boot_sahara_callback_parameters(boot_sahara_info_ptr);

  callback_parameters_ptr->sahara_rx_bytes_read = bytes_read;
  callback_parameters_ptr->sahara_rx_err_code = (enum boot_sahara_bulk_error) err_code;
  callback_parameters_ptr->sahara_rx_complete = TRUE;
}

/* ============================================================================
**  Function : boot_sahara_tx_cb
** ============================================================================
*/
/*!
*   @brief
*   Callback for driver bulk transmit. Sets the number of bytes sent, error
*   code (if any), and completion flag.
*
*   @details
*   Callback for driver bulk transmit. Sets the number of bytes sent, error
*   code (if any), and completion flag.
*
*   @param bytes_written   -  [IN] Number of bytes written by driver
*   @param err_code        -  [IN] Error code returned by driver
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_tx_cb
(
  uint32 bytes_written,
  uint32 err_code
)
{
  boot_sahara_info *boot_sahara_info_ptr = _get_boot_sahara_info_pointer();

  // Get callback parameters pointer from boot sahara info
  boot_sahara_callback_parameters* callback_parameters_ptr =
    _get_boot_sahara_callback_parameters(boot_sahara_info_ptr);

  // Update Callback paramters in boot_sahara_info
  callback_parameters_ptr->sahara_tx_bytes_read =  bytes_written;
  callback_parameters_ptr->sahara_tx_err_code =     (enum boot_sahara_bulk_error) err_code;
  callback_parameters_ptr->sahara_tx_complete =     TRUE;
}

/* ============================================================================
**  Function : boot_sahara_exit
** ============================================================================
*/
/*!
*   @brief
*   This function shuts down the Sahara protocol and the hardware interface
*
*   @details
*   This function uses the dispatch table to shutdown the driver and to
*   reset the state machine. The dispatch table pointer is also set to NULL.
*
*   @param  None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_exit ( boot_sahara_info *boot_sahara_info_ptr )
{
  /* Get the pointer to sahara_data in boot_sahara_info */
  boot_sahara_data *boot_sahara_data_ptr = _get_boot_sahara_data(boot_sahara_info_ptr);

  /* Shut down transport layer */
  boot_sahara_data_ptr->sahara_state = SAHARA_STATE_ENTRY;

  /* Set state to allow sahara_process_packets to exit in case
     boot_sahara_reset returns - this allows Sahara client
     to regain control
  */
  boot_sahara_data_ptr->sahara_done = TRUE;
}

/* ============================================================================
**  Function : boot_sahara_handle_rx
** ============================================================================
*/
/*!
*   @brief
*   Receives a single packet of size length.
*
*   @details
*   This function uses the dispatch table to receive a bulk of data into
*   the input packet buffer. The buffer size passed to the driver is passed
*   as a multiple of the bulk_min_buffer_size stored in the dispatch table.
*
*   @param *packet_buffer   -  [IN/OUT] Buffer that contains the packet
*   @param length           -  [IN    ] Length of packet
*   @param *err_code        -  [IN/OUT] Reception error code
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval returns number of bytes received in RAW_DATA packet
*
*   @sa None
*/
static uint32 boot_sahara_handle_rx
(
  boot_sahara_info *boot_sahara_info_ptr,
  uint8* packet_buffer,
  uint32 length,
  enum boot_sahara_bulk_error *err_code,
  enum boot_sahara_packet_type type,
  enum boot_sahara_is_blocking_flag is_blocking
)
{
  // Get Dispatch table from boot sahara info
  struct boot_sahara_dispatch_tbl *sahara_dispatch_tbl =
  _get_boot_sahara_dispatch_tbl(boot_sahara_info_ptr);

  // Get callback parameters from boot sahara info
  boot_sahara_callback_parameters* callback_parameters_ptr =
  _get_boot_sahara_callback_parameters(boot_sahara_info_ptr);

  uint32 rx_length = 0;

  // Initialize callback parameters
  callback_parameters_ptr->sahara_rx_bytes_read = 0;
  callback_parameters_ptr->sahara_rx_err_code = BULK_SUCCESS;
  callback_parameters_ptr->sahara_rx_complete = FALSE;

  // Receive packet
  sahara_dispatch_tbl->rx_bulk(packet_buffer,
                               length,
                               boot_sahara_rx_cb,
                               (uint32*)err_code,
                               type
                              );

  if (is_blocking == SAHARA_READ_BLOCKING)
  {
    while (!callback_parameters_ptr->sahara_rx_complete)
    {
      sahara_dispatch_tbl->poll();
    }

    rx_length = callback_parameters_ptr->sahara_rx_bytes_read;
    *err_code = callback_parameters_ptr->sahara_rx_err_code;
  }

  return rx_length;
}

/* ============================================================================
**  Function : boot_sahara_handle_tx
** ============================================================================
*/
/*!
*   @brief
*   Transmits a single packet of size length.
*
*   @details
*   This function uses the dispatch table to transmit a bulk of data passed in
*   the input packet buffer. The length of data to be transmitted is based
*   on the size of the input packet length. This function also logs the
*   transmitted packet.
*
*   @param *packet_buffer   -  [IN/OUT] Buffer that contains the packet
*   @param length           -  [IN    ] Length of packet
*   @param *err_code        -  [IN/OUT] Transmission error code
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval returns number of bytes transmitted
*
*   @sa None
*/
static uint32 boot_sahara_handle_tx
(
  boot_sahara_info * const boot_sahara_info_ptr,
  uint8* packet_buffer,
  uint32 length,
  enum boot_sahara_bulk_error *err_code
)
{
  // Get sahara dispatch table from boot sahara info
  boot_sahara_dispatch_tbl *sahara_dispatch_tbl =
  _get_boot_sahara_dispatch_tbl(boot_sahara_info_ptr);

  uint32 tx_length = 0;

  // Get callback parameters from boot sahara info
  boot_sahara_callback_parameters* callback_parameters_ptr =
  _get_boot_sahara_callback_parameters(boot_sahara_info_ptr);

  // Initialize callback parameters
  callback_parameters_ptr->sahara_tx_bytes_read = 0;
  callback_parameters_ptr->sahara_tx_err_code =   BULK_SUCCESS;
  callback_parameters_ptr->sahara_tx_complete =   FALSE;

  // Send packet
  sahara_dispatch_tbl->tx_bulk(packet_buffer,
                               length,
                               boot_sahara_tx_cb,
                               (uint32*)err_code
                              );

  while (!callback_parameters_ptr->sahara_tx_complete)
  {
    sahara_dispatch_tbl->poll();
  }

  tx_length = callback_parameters_ptr->sahara_tx_bytes_read;
  *err_code = callback_parameters_ptr->sahara_tx_err_code;

  return tx_length;
}

/* ============================================================================
**  Function : boot_sahara_handle_end_image_tx
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for END_IMAGE_TX packet.
*
*   @details
*   This function fills the fields in the command packet buffer for the
*   END_IMAGE_TX packet and transmits the packet. If there is any error,
*   the target will try to send another END_IMAGE_TX packet with the
*   corresponding error.
*
*   @param status   -  [IN] Status of image transfer to be sent to host
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_end_image_tx
(
  boot_sahara_info * const boot_sahara_info_ptr
)
{
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;
  uint32 tx_length;
  boot_sahara_status tx_status = SAHARA_STATUS_SUCCESS;

  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  struct sahara_packet_end_image_tx* packet_end_image_tx =
    (struct sahara_packet_end_image_tx*)boot_sahara_data_ptr->sahara_packet_buffer;

  boot_sahara_status status = boot_sahara_data_ptr->status;

  // Setup END_IMAGE_TX packet
  packet_end_image_tx->command = SAHARA_END_IMAGE_TX_ID;
  packet_end_image_tx->length = sizeof(struct sahara_packet_end_image_tx);
  packet_end_image_tx->image_id = boot_sahara_data_ptr->image_id;
  packet_end_image_tx->status = status;

  // Log transmitted packet
  boot_sahara_log_packet_buffer((uint8 *)packet_end_image_tx,
                                packet_end_image_tx->length,
                                SAHARA_PACKET_TRANSMIT);

  // Transmit END_IMAGE_TX packet
  tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                    (uint8 *)packet_end_image_tx,
                                    packet_end_image_tx->length,
                                    &err_code);

  // Check for error in transmission of END_IMAGE_TX packet
  if (err_code == BULK_ERR_TIMEOUT)
  {
    // ERROR: Timeout while transmitting data
    tx_status = SAHARA_NAK_TIMEOUT_TX;
  }
  else if (err_code == BULK_ERR_CABLE_DISCONNECT)
  {
    // ERROR: General transmission or reception error
    tx_status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
  }
  else if (err_code != BULK_SUCCESS)
  {
    // ERROR: General transmission or reception error
    tx_status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
  }
  else if (tx_length != packet_end_image_tx->length)
  {
    // ERROR: Invalid tranmission length
    tx_status = SAHARA_NAK_INVALID_TX_LENGTH;
  }

  // Switch to WAIT_RESET state if error
  if ((status != SAHARA_STATUS_SUCCESS) ||
      (tx_status != SAHARA_STATUS_SUCCESS))
  {
    boot_sahara_data_ptr->sahara_state = SAHARA_STATE_WAIT_RESET;
  }
  else
  {
    boot_sahara_data_ptr->sahara_state = SAHARA_STATE_WAIT_DONE;
  }

  /* Reset if END_IMAGE_TX transmission failed */
  /* Do not wait for RESET command */
  if (tx_status != SAHARA_STATUS_SUCCESS)
  {
    // Update sahara interface status
    boot_sahara_data_ptr->status = tx_status;

    boot_sahara_reset(boot_sahara_info_ptr);
  }
}

/* ============================================================================
**  Function : boot_sahara_handle_read_data
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for READ_DATA packet
*
*   @details
*   This function fills the fields in the command packet buffer for the
*   READ_DATA packet and transmits the packet. If there is any error,
*   the target will try to send an END_IMAGE_TX packet with the
*   corresponding error.
*
*   @param image_id      -  [IN] ID of image to read data from
*   @param data_offset   -  [IN] Offset into image file to start reading data
*                                from
*   @param data_length   -  [IN] Length of data to read
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_read_data
(
  boot_sahara_info * const boot_sahara_info_ptr,
  uint32 data_offset,
  uint32 data_length
)
{

  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;
  uint32 tx_length;
  boot_sahara_status status = SAHARA_STATUS_SUCCESS;

  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  struct sahara_packet_read_data* packet_read_data =
    (struct sahara_packet_read_data*)boot_sahara_data_ptr->sahara_packet_buffer;

  // Setup READ_DATA packet
  packet_read_data->command =       SAHARA_READ_DATA_ID;
  packet_read_data->length =        sizeof(struct sahara_packet_read_data);
  packet_read_data->image_id =      boot_sahara_data_ptr->image_id;
  packet_read_data->data_offset =   data_offset;
  packet_read_data->data_length =   data_length;

  // Log transmitted packet
  boot_sahara_log_packet_buffer((uint8 *)packet_read_data,
                                packet_read_data->length,
                                SAHARA_PACKET_TRANSMIT);

  // Transmit READ_DATA packet
  tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                    (uint8 *)packet_read_data,
                                    packet_read_data->length,
                                    &err_code);

  // Check for error in transmission of READ_DATA packet
  if (err_code == BULK_ERR_TIMEOUT)
  {
    // ERROR: Timeout while transmitting data
    status = SAHARA_NAK_TIMEOUT_TX;
  }
  else if (err_code == BULK_ERR_CABLE_DISCONNECT)
  {
    // ERROR: Cable disconnected
    status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
  }
  else if (err_code != BULK_SUCCESS)
  {
    // ERROR: General transmission or reception error
    status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
  }
  else if (tx_length != packet_read_data->length)
  {
    // ERROR: Invalid tranmission length
    status = SAHARA_NAK_INVALID_TX_LENGTH;
  }

  boot_sahara_data_ptr->status = status;
}


/* ============================================================================
**  Function : boot_sahara_handle_hello_resp
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for HELLO_RESP packet
*
*   @details
*   This function parses the fields in the HELLO_RESP packet. If there is any
*   error or mismatch of protocol between the target and the host,
*   the target will send an END_IMAGE_TX packet with the corresponding error.
*   Otherwise, the target will proceed to receive the expected image.
*
*   @param *packet_buffer   -  [IN/OUT] Buffer that contains the packet
*   @param length           -  [IN    ] Length of packet
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_hello_resp
(
  boot_sahara_info * const boot_sahara_info_ptr,
  uint32 length
)
{
  boot_sahara_status status = SAHARA_STATUS_SUCCESS;

  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  struct sahara_packet_hello_resp* packet_hello_resp =
    (struct sahara_packet_hello_resp*)boot_sahara_data_ptr->sahara_packet_buffer;

  do
  {
    //boot_log_message("Sahara: Hello Response Received");

    if ((length != sizeof(struct sahara_packet_hello_resp)) ||
        (length != packet_hello_resp->length))
    {
      // Check if length corresponds to V1
      if (length != SAHARA_PACKET_HELLO_RESP_LENGTH_V1)
      {
        // ERROR: Invalid packet size received
        status = SAHARA_NAK_INVALID_PACKET_SIZE;
        break;
      }
      else if (packet_hello_resp->version != 0x1)  // TODO: This CANNOT be hardcoded
      {
        // Host is not running version 1 of protocol
        // ERROR: Invalid packet size received
        //status = SAHARA_NAK_INVALID_PACKET_SIZE;
        status = SAHARA_NAK_INVALID_HOST_PROTOCOL;
        break;
      }
    }

    // Check host status
    if (SAHARA_STATUS_SUCCESS != packet_hello_resp->status)
    {
      if (status < SAHARA_NAK_LAST_CODE)
      {
        // ERROR: Error on host
        status = (boot_sahara_status)packet_hello_resp->status;
        break;
      }
      else
      {
        // ERROR: Unknown host error received in HELLO_RESP
        status = SAHARA_NAK_UNKNOWN_HOST_ERROR;
        break;
      }
    }

    // Check protocol version running on host
    if (packet_hello_resp->version < packet_hello_resp->version_supported)
    {
      // ERROR: Invalid host protocol version
      status = SAHARA_NAK_INVALID_HOST_PROTOCOL;
      break;
    }
    else if ((packet_hello_resp->version > boot_sahara_data_ptr->sahara_major_version) ||
             (packet_hello_resp->version < boot_sahara_data_ptr->sahara_major_version_supported))
    {
      // ERROR: Protocol mismatch between host and target
      status = SAHARA_NAK_PROTOCOL_MISMATCH;
      break;
    }

    // Check if valid mode is returned
    if (length != SAHARA_PACKET_HELLO_RESP_LENGTH_V1)
    {
      if (packet_hello_resp->mode < SAHARA_MODE_LAST)
      {
        boot_sahara_data_ptr->sahara_mode = (enum boot_sahara_mode) packet_hello_resp->mode;

      }
      else
      {
        // ERROR: Invalid mode received from host
        status = SAHARA_NAK_INVALID_HOST_MODE;
        break;
      }
    }
  } while (0);

  boot_sahara_data_ptr->status = status;

  if (status == SAHARA_STATUS_SUCCESS)
  {
    if (boot_sahara_data_ptr->sahara_mode == SAHARA_MODE_MEMORY_DEBUG)
    {
      /* Check for mem debug enabled */
      if (!boot_sahara_data_ptr->sahara_mem_debug_enabled)
      {
        boot_sahara_data_ptr->status = SAHARA_NAK_MEMORY_DEBUG_NOT_SUPPORTED;
      }
      else
      {
        if (sizeof(uintnt) == 0x4)
          boot_sahara_handle_memory_debug(boot_sahara_info_ptr);
        else
          boot_sahara_handle_memory_debug_64bit(boot_sahara_info_ptr);
      }
    }
    else if (boot_sahara_data_ptr->sahara_mode == SAHARA_MODE_COMMAND)
    {
      // Send CMD_READY packet to host
      boot_sahara_handle_cmd_ready(boot_sahara_info_ptr);

    }
    else
    {
      // state to get packet in _read()
      boot_sahara_data_ptr->sahara_state = SAHARA_STATE_DATA_READ_PAYLOAD;
    }
  }
}

/* ============================================================================
**  Function : boot_sahara_handle_hello
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for HELLO packet
*
*   @details
*   This function fills the fields in the command packet buffer for the
*   HELLO packet and transmits the packet. If there is any error,
*   the target will attempt to keep resending the HELLO packet until
*   a successful transmission is complete.
*
*   @param  None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_hello( boot_sahara_info * const boot_sahara_info_ptr )
{

  // error code returned from raw data read
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;

  uint32 tx_length;
  boot_sahara_status status = SAHARA_STATUS_SUCCESS;

  // Get the pointer to sahara_data in boot_sahara_info
  boot_sahara_data *boot_sahara_data_ptr = _get_boot_sahara_data(boot_sahara_info_ptr);

  struct sahara_packet_hello* packet_hello =
    (struct sahara_packet_hello*)boot_sahara_data_ptr->sahara_packet_buffer;

  boot_sahara_dispatch_tbl* sahara_dispatch_tbl = _get_boot_sahara_dispatch_tbl(boot_sahara_info_ptr);

  // Setup HELLO packet
  packet_hello->command =           SAHARA_HELLO_ID;
  packet_hello->length =            sizeof(struct sahara_packet_hello);
  packet_hello->version =           boot_sahara_data_ptr->sahara_major_version;
  packet_hello->version_supported = boot_sahara_data_ptr->sahara_major_version_supported;
  packet_hello->cmd_packet_length = SAHARA_MAX_PACKET_SIZE_IN_BYTES;
  packet_hello->mode =              boot_sahara_data_ptr->sahara_mode;
  packet_hello->reserved0 = 0;
  packet_hello->reserved1 = 0;
  packet_hello->reserved2 = 0;
  packet_hello->reserved3 = 0;
  packet_hello->reserved4 = 0;
  packet_hello->reserved5 = 0;

  // Continue to send HELLO packets until successful transmission
  do
  {
    // Log transmitted packet
    boot_sahara_log_packet_buffer((uint8 *)packet_hello,
                                  packet_hello->length,
                                  SAHARA_PACKET_TRANSMIT);

    // Transmit HELLO packet
    tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                      (uint8 *)packet_hello,
                                      packet_hello->length,
                                      &err_code);

    // Check for transmission error of HELLO
    if (err_code == BULK_ERR_TIMEOUT)
    {
      // ERROR: Timeout while receiving data
      status = SAHARA_NAK_TIMEOUT_RX;
    }
    else if (err_code == BULK_ERR_CABLE_DISCONNECT)
    {
      // ERROR: Cable disconnected
      /* Call hw init again */
      status = SAHARA_NAK_TARGET_INIT_FAILURE;
      sahara_dispatch_tbl->init();
    }
    else if (err_code != BULK_SUCCESS)
    {
      // ERROR: General transmission or reception error
      status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
    }
    else if (tx_length != packet_hello->length)
    {
      // ERROR: Invalid tranmission length
      status = SAHARA_NAK_INVALID_TX_LENGTH;
    }
    else
    {
      status = SAHARA_STATUS_SUCCESS;
    }
  } while (status != SAHARA_STATUS_SUCCESS);

  boot_sahara_data_ptr->status =        SAHARA_STATUS_SUCCESS;
  boot_sahara_data_ptr->sahara_state =  SAHARA_STATE_WAIT_HELLO_RESP;
  //boot_log_message("Sahara: Hello pkt sent");
}

/* ============================================================================
**  Function : boot_sahara_handle_done_resp
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for DONE_RESP packet
*
*   @details
*   This function fills the fields in the command packet buffer for the
*   DONE_RESP packet and transmits the packet. If there is any error,
*   the target will attempt to keep resending the DONE_RESP packet until
*   a successful transmission is complete. Once complete, if all images have
*   been transferred, the hardware driver will be shutdown.
*
*   @param  None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_done_resp( boot_sahara_info * const boot_sahara_info_ptr )
{
  // error code returned from raw data read
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;

  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  uint32 tx_length;

  struct sahara_packet_done_resp* packet_done_resp =
    (struct sahara_packet_done_resp*)boot_sahara_data_ptr->sahara_packet_buffer;

  boot_sahara_data_ptr->status = SAHARA_STATUS_SUCCESS;

  if ( TRUE == boot_sahara_data_ptr->is_last_image)
  {
    boot_sahara_data_ptr->sahara_mode = SAHARA_MODE_IMAGE_TX_COMPLETE;
  }
  // Setup DONE_RESP packet
  packet_done_resp->command = SAHARA_DONE_RESP_ID;
  packet_done_resp->length = sizeof(struct sahara_packet_done_resp);
  packet_done_resp->image_tx_status = boot_sahara_data_ptr->sahara_mode;

  // Keep transmitting DONE_RESP packet until transmission is successful
  do
  {
    // Log transmitted packet
    boot_sahara_log_packet_buffer((uint8 *)packet_done_resp,
                                  packet_done_resp->length,
                                  SAHARA_PACKET_TRANSMIT);

    // Transmit DONE_RESP packet
    tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                      (uint8 *)packet_done_resp,
                                      packet_done_resp->length,
                                      &err_code);

    // Check for transmission error of DONE_RESP
    if (err_code == BULK_ERR_TIMEOUT)
    {
      // ERROR: Timeout while receiving data
      boot_sahara_data_ptr->status = SAHARA_NAK_TIMEOUT_RX;

      // Reset if timeout occurs - no return
      boot_sahara_data_ptr->sahara_state = SAHARA_STATE_WAIT_RESET;
      boot_sahara_reset(boot_sahara_info_ptr);

      /* boot_sahara_reset() calls boot_sahara_exit(). Connection is closed. */
      break;
    }
    else if (err_code == BULK_ERR_CABLE_DISCONNECT)
    {
      // ERROR: Cable disconnected
      boot_sahara_data_ptr->status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
    }
    else if (err_code != BULK_SUCCESS)
    {
      // ERROR: General transmission or reception error
      boot_sahara_data_ptr->status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
    }
    else if (tx_length != packet_done_resp->length)
    {
      // ERROR: Invalid tranmission length
      boot_sahara_data_ptr->status = SAHARA_NAK_INVALID_TX_LENGTH;
    }
    else
    {
      boot_sahara_data_ptr->status = SAHARA_STATUS_SUCCESS;
    }
  } while (boot_sahara_data_ptr->status != SAHARA_STATUS_SUCCESS);

  if (boot_sahara_data_ptr->sahara_mode == SAHARA_MODE_IMAGE_TX_COMPLETE)
  {
    // Shutdown Sahara if all images have been transferred
    boot_sahara_exit(boot_sahara_info_ptr);
  }
}

/* ============================================================================
**  Function : boot_sahara_handle_done
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for DONE packet
*
*   @details
*   This function parses the fields in the DONE packet. If there is any
*   error in the packet, the target will send an END_IMAGE_TX packet
*   with the corresponding error. Otherwise, the target will proceed to
*   send a DONE_RESP.
*
*   @param *packet_buffer   -  [IN/OUT] Buffer that contains the packet
*   @param length           -  [IN    ] Length of packet
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_done
(
  boot_sahara_info * const boot_sahara_info_ptr,
  uint32 length
)
{

  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  struct sahara_packet_done* packet_done =
    (struct sahara_packet_done*)boot_sahara_data_ptr->sahara_packet_buffer;

  boot_sahara_data_ptr->status = SAHARA_STATUS_SUCCESS;

  if ((length != sizeof(struct sahara_packet_done)) ||
      (length != packet_done->length))
  {
    // ERROR: Invalid packet size received
    boot_sahara_data_ptr->status = SAHARA_NAK_INVALID_PACKET_SIZE;
  }
  else
  {
    // end of image tranfer
    boot_sahara_handle_done_resp(boot_sahara_info_ptr);
  }

}

/* ============================================================================
**  Function : boot_sahara_handle_reset_resp
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for RESET_RESP packet
*
*   @details
*   This function fills the fields in the command packet buffer for the
*   RESET_RESP packet and transmits the packet. If there is any error,
*   the target does not attempt to resend. The target will proceed to
*   shutdown the hardware driver and then reset.
*
*   @param  None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_reset_resp( boot_sahara_info * const boot_sahara_info_ptr )
{
  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  // error code returned from raw data read
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;

  struct sahara_packet_reset_resp* packet_reset_resp =
    (struct sahara_packet_reset_resp*)boot_sahara_data_ptr->sahara_packet_buffer;

  // Setup RESET_RESP packet
  packet_reset_resp->command = SAHARA_RESET_RESP_ID;
  packet_reset_resp->length = sizeof(struct sahara_packet_reset_resp);

  // Log transmitted packet
  boot_sahara_log_packet_buffer((uint8 *)packet_reset_resp,
                                packet_reset_resp->length,
                                SAHARA_PACKET_TRANSMIT);

  // Transmit RESET_RESP packet - do not check if transmission was valid
  boot_sahara_handle_tx(boot_sahara_info_ptr,
                        (uint8 *)packet_reset_resp,
                        packet_reset_resp->length,
                        &err_code);

  // Reset the target
  boot_sahara_reset(boot_sahara_info_ptr);
}

/* ============================================================================
**  Function : boot_sahara_handle_reset
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for RESET packet
*
*   @details
*   This function parses the fields in the RESET packet. If there is any
*   error in the packet, the target will send an END_IMAGE_TX packet
*   with the corresponding error. Otherwise, the target will proceed to
*   send a RESET_RESP.
*
*   @param *packet_buffer   -  [IN/OUT] Buffer that contains the packet
*   @param length           -  [IN    ] Length of packet
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_reset
(
  boot_sahara_info * const boot_sahara_info_ptr,
  uint32 length
)
{

  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  struct sahara_packet_reset* packet_reset =
    (struct sahara_packet_reset*)boot_sahara_data_ptr->sahara_packet_buffer;

  if ((length != sizeof(struct sahara_packet_reset)) ||
      (length != packet_reset->length))
  {
    // ERROR: Invalid packet size received
    boot_sahara_data_ptr->status = SAHARA_NAK_INVALID_PACKET_SIZE;
  }
  else
  {
    /* reset target - No return. Return if status is not SAHARA_STATUS_SUCCESS */
    boot_sahara_handle_reset_resp(boot_sahara_info_ptr);
  }
}


/* ============================================================================
**  Function : boot_sahara_handle_cmd_ready
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for CMD_READY packet.
*
*   @details
*   This function sends the CMD_READY packet to the host and transitions
*   to the WAIT_CMD_EXEC state to await command execution packets.
*
*   @param  None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_cmd_ready( boot_sahara_info * const boot_sahara_info_ptr )
{
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;
  uint32 tx_length;

  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  struct sahara_packet_cmd_ready* packet_cmd_ready =
    (struct sahara_packet_cmd_ready*)boot_sahara_data_ptr->sahara_packet_buffer;

  boot_sahara_status status = SAHARA_STATUS_SUCCESS;

  /* Setup RESET_RESP packet */
  packet_cmd_ready->command = SAHARA_CMD_READY_ID;
  packet_cmd_ready->length = sizeof(struct sahara_packet_cmd_ready);

  /* Log transmitted packet */
  boot_sahara_log_packet_buffer((uint8 *)packet_cmd_ready,
                                packet_cmd_ready->length,
                                SAHARA_PACKET_TRANSMIT);  /* TODO: Might be removed */

  /* Transmit CMD_READY packet */
  tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                    (uint8 *)packet_cmd_ready,
                                    packet_cmd_ready->length,
                                    &err_code);

  /* Check for error in transmission of CMD_READY packet */
  if (err_code == BULK_ERR_TIMEOUT)
  {
    /* ERROR: Timeout while transmitting data */
    status = SAHARA_NAK_TIMEOUT_TX;
  }
  else if (err_code == BULK_ERR_CABLE_DISCONNECT )
  {
    /* ERROR: Cable disconnected */
    status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
  }
  else if (err_code != BULK_SUCCESS)
  {
    /* ERROR: General transmission or reception error */
    status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
  }
  else if (tx_length != packet_cmd_ready->length)
  {
    /* ERROR: Invalid tranmission length */
    status = SAHARA_NAK_INVALID_TX_LENGTH;
  }

  if (status == SAHARA_STATUS_SUCCESS)
  {
    /* Wait for CMD_EXEC packets */
    boot_sahara_data_ptr->sahara_state = SAHARA_STATE_WAIT_CMD_EXEC;
  }

  boot_sahara_data_ptr->status = status;
}

/* ============================================================================
**  Function : boot_sahara_handle_memory_read
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for MEMORY_READ packet
*
*   @details
*   This function parses the incoming MEMORY_READ packet and extracts the
*   memory location and length of data to read and send to host. The address
*   and length validity are checked before sending the data. If invalid
*   address or length is received, then an END_IMAGE_TX with the corresponding
*   error is sent.
*
*   @param *packet_buffer   -  [IN/OUT] Buffer that contains the packet
*   @param length           -  [IN    ] Length of packet
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_memory_read
(
  boot_sahara_info * const boot_sahara_info_ptr,
  uint32 length
)
{
  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  ramdump_table_if *sahara_mem_debug_tbl_ptr =
    _get_boot_sahara_mem_debug_tbl(boot_sahara_info_ptr);


  struct sahara_packet_memory_read* packet_memory_read =
    (struct sahara_packet_memory_read*)boot_sahara_data_ptr->sahara_packet_buffer;

  boot_sahara_status status  =   SAHARA_STATUS_SUCCESS;
  boot_boolean verified_address   =   FALSE;
  bl_error_boot_type return_status =  BL_ERR_NONE;
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;

  uintnt tx_length;
  uintnt memory_transfer_size;      /* used when memory region is restricted */
  uintnt memory_transfer_size_left; /* used when memory region is restricted */
  uintnt memory_transfer_addr;      /* used when memory region is restricted */

  boot_boolean is_copy_success = FALSE;


  do
  {
    if ((length != sizeof(struct sahara_packet_memory_read)) ||
        (length != packet_memory_read->length))
    {
      /* ERROR: Invalid packet size received */
      status = SAHARA_NAK_INVALID_PACKET_SIZE;
      break;
    }
    else
    {

      /* Check for valid address */
      return_status = sahara_mem_debug_tbl_ptr->verify_addr(
                        (boot_sahara_info_ptr->mem_debug_handle).ramdump_table_handle,
                        packet_memory_read->memory_addr,
                        packet_memory_read->memory_length,
                        &verified_address);

      if (verified_address == FALSE || return_status != BL_ERR_NONE)
      {
        /* Invalid memory read access */
        status = SAHARA_NAK_INVALID_MEMORY_READ;
        break;
      }

      /* Check for restricted address or unrestricted address */
      return_status = sahara_mem_debug_tbl_ptr->verify_restricted_addr(
                        (boot_sahara_info_ptr->mem_debug_handle).ramdump_table_handle,
                        packet_memory_read->memory_addr,
                        packet_memory_read->memory_length,
                        &verified_address);

      if (return_status != BL_ERR_NONE)
      {
        /* Invalid memory read access */
        status = SAHARA_NAK_INVALID_MEMORY_READ;
        break;
      }

      if (verified_address == TRUE)
      {
        /* Restricted address */

        memory_transfer_size_left = packet_memory_read->memory_length;
        memory_transfer_addr =      packet_memory_read->memory_addr;

        while ((status == SAHARA_STATUS_SUCCESS) && (memory_transfer_size_left != 0))
        {
          // Determine transfer size
          if (memory_transfer_size_left > SAHARA_MAX_MEMORY_DATA_SIZE_IN_BYTES)
          {
            memory_transfer_size = SAHARA_MAX_MEMORY_DATA_SIZE_IN_BYTES;
          }
          else
          {
            memory_transfer_size = memory_transfer_size_left;
          }

          /* Copies the data to a temporary buffer for a restricted region */
          return_status = boot_sahara_mem_debug_copy_restricted(boot_sahara_info_ptr,
                          memory_transfer_addr,
                          memory_transfer_size,
                          &is_copy_success);
          if (return_status != BL_ERR_NONE || is_copy_success == FALSE)
          {
            status = SAHARA_NAK_INVALID_MEMORY_READ;
            break;
          }

          /* Transmit memory from mem debug buffer */
          tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                            (uint8 *)((boot_sahara_info_ptr->mem_debug_handle).sahara_mem_debug_buffer),
                                            memory_transfer_size,
                                            &err_code);

          /* Check for error in transmission of CMD_EXEC_RESP packet */
          if (err_code == BULK_ERR_TIMEOUT)
          {
            /* ERROR: Timeout while transmitting data and break from loop */
            status = SAHARA_NAK_TIMEOUT_TX;
            break;
          }
          else if (err_code == BULK_ERR_CABLE_DISCONNECT )
          {
            /* ERROR: Cable disconnected */
            status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
            break;
          }
          else if (err_code != BULK_SUCCESS)
          {
            /* ERROR: General transmission or reception error and break from loop */
            status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
            break;
          }
          else if (tx_length != memory_transfer_size)
          {
            /* ERROR: Invalid tranmission length and break from loop */
            status = SAHARA_NAK_INVALID_TX_LENGTH;
            break;
          }
          else
          {
            /* Update parameters for next transfer */
            memory_transfer_addr += memory_transfer_size;
            memory_transfer_size_left -= memory_transfer_size;
          }
        } /* End of while */
      }
      else
      {
        /* Unrestricted address */
        // Transmit memory
        tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                          (uint8 *)((uintnt)packet_memory_read->memory_addr),
                                          packet_memory_read->memory_length,
                                          &err_code);

        /* Check for error in transmission of CMD_EXEC_RESP packet */
        if (err_code == BULK_ERR_TIMEOUT)
        {
          /* ERROR: Timeout while transmitting data */
          status = SAHARA_NAK_TIMEOUT_TX;
        }
        else if (err_code == BULK_ERR_CABLE_DISCONNECT )
        {
          /* ERROR: Cable disconnected */
          status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
        }
        else if (err_code != BULK_SUCCESS)
        {
          /* ERROR: General transmission or reception error */
          status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
        }
        else if (tx_length != packet_memory_read->memory_length)
        {
          /* ERROR: Invalid tranmission length */
          status = SAHARA_NAK_INVALID_TX_LENGTH;
        }
      }

    }

  } while (FALSE);

  boot_sahara_data_ptr->status = status;
}

/* ============================================================================
**  Function : boot_sahara_handle_memory_read_64
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for MEMORY_READ packet
*
*   @details
*   This function parses the incoming MEMORY_READ packet and extracts the
*   memory location and length of data to read and send to host. The address
*   and length validity are checked before sending the data. If invalid
*   address or length is received, then an END_IMAGE_TX with the corresponding
*   error is sent.
*
*   @param *packet_buffer   -  [IN/OUT] Buffer that contains the packet
*   @param length           -  [IN    ] Length of packet
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/



void boot_sahara_handle_memory_64bits_read
(
  boot_sahara_info * const boot_sahara_info_ptr,
  uint32 length
)
{
  uint64 memory_transfer_size;      /* used when memory region is restricted */
  uint64 memory_transfer_size_left; /* used when memory region is restricted */
  uint64 memory_transfer_addr;      /* used when memory region is restricted */
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;
  uint32 tx_length;

  boot_boolean is_copy_success = FALSE;

  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  ramdump_table_if *sahara_mem_debug_tbl_ptr =
    _get_boot_sahara_mem_debug_tbl(boot_sahara_info_ptr);


  struct sahara_packet_memory_read_64bit* packet_memory_read =
    (struct sahara_packet_memory_read_64bit*)boot_sahara_data_ptr->sahara_packet_buffer;

  boot_sahara_status status  =   SAHARA_STATUS_SUCCESS;
  boot_boolean verified_address   =   FALSE;
  bl_error_boot_type return_status =  BL_ERR_NONE;

  do
  {
    if ((length != sizeof(struct sahara_packet_memory_read_64bit)) ||
        (length != packet_memory_read->length))
    {
      /* ERROR: Invalid packet size received */
      status = SAHARA_NAK_INVALID_PACKET_SIZE;
      break;
    }
    else
    {

      /* Check for valid address */
      return_status = sahara_mem_debug_tbl_ptr->verify_addr(
                        (boot_sahara_info_ptr->mem_debug_handle).ramdump_table_handle,
                        packet_memory_read->memory_addr,
                        packet_memory_read->memory_length,
                        &verified_address);

      if (verified_address == FALSE || return_status != BL_ERR_NONE)
      {
        /* Invalid memory read access */
        status = SAHARA_NAK_INVALID_MEMORY_READ;
        break;
      }

      /* Check for restricted address or unrestricted address 64*/
      return_status = sahara_mem_debug_tbl_ptr->verify_restricted_addr(
                        (boot_sahara_info_ptr->mem_debug_handle).ramdump_table_handle,
                        packet_memory_read->memory_addr,
                        packet_memory_read->memory_length,
                        &verified_address);

      if (return_status != BL_ERR_NONE)
      {
        /* Invalid memory read access */
        break;
      }

      if (verified_address == TRUE)
      {
        /* Restricted address */

        memory_transfer_size_left = packet_memory_read->memory_length;
        memory_transfer_addr =      packet_memory_read->memory_addr;

        while ((status == SAHARA_STATUS_SUCCESS) && (memory_transfer_size_left != 0))
        {
          // Determine transfer size
          if (memory_transfer_size_left > SAHARA_MAX_MEMORY_DATA_SIZE_IN_BYTES)
          {
            memory_transfer_size = SAHARA_MAX_MEMORY_DATA_SIZE_IN_BYTES;
          }
          else
          {
            memory_transfer_size = memory_transfer_size_left;
          }
          /* Copies the data to a temporary buffer for a restricted region */
          return_status = boot_sahara_mem_debug_copy_restricted(boot_sahara_info_ptr,
                          memory_transfer_addr,
                          memory_transfer_size,
                          &is_copy_success);
          if (return_status != BL_ERR_NONE || is_copy_success == FALSE)
          {
            status = SAHARA_NAK_INVALID_MEMORY_READ;
            break;
          }

          /* Transmit memory from mem debug buffer */
          tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                            (uint8 *)((boot_sahara_info_ptr->mem_debug_handle).sahara_mem_debug_buffer),
                                            memory_transfer_size,
                                            &err_code);

          /* Check for error in transmission of CMD_EXEC_RESP packet */
          if (err_code == BULK_ERR_TIMEOUT)
          {
            /* ERROR: Timeout while transmitting data and break from loop */
            status = SAHARA_NAK_TIMEOUT_TX;
            break;
          }
          else if (err_code == BULK_ERR_CABLE_DISCONNECT )
          {
            // ERROR: Cable disconnected
            status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
            break;
          }
          else if (err_code != BULK_SUCCESS)
          {
            /* ERROR: General transmission or reception error and break from loop */
            status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
            break;
          }
          else if (tx_length != memory_transfer_size)
          {
            /* ERROR: Invalid tranmission length and break from loop */
            status = SAHARA_NAK_INVALID_TX_LENGTH;
            break;
          }
          else
          {
            /* Update parameters for next transfer */
            memory_transfer_addr += memory_transfer_size;
            memory_transfer_size_left -= memory_transfer_size;
          }
        } /* End of while */
      }
      else
      {
        /* Unrestricted address */
        // Transmit memory
        tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                          ((uint8 *)(uintnt)packet_memory_read->memory_addr),
                                          packet_memory_read->memory_length,
                                          &err_code);

        /* Check for error in transmission of CMD_EXEC_RESP packet */
        if (err_code == BULK_ERR_TIMEOUT)
        {
          /* ERROR: Timeout while transmitting data */
          status = SAHARA_NAK_TIMEOUT_TX;
        }
        else if (err_code == BULK_ERR_CABLE_DISCONNECT)
        {
          /* ERROR: Cable disconnected */
          status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
        }
        else if (err_code != BULK_SUCCESS)
        {
          /* ERROR: General transmission or reception error */
          status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
        }
        else if (tx_length != packet_memory_read->memory_length)
        {
          /* ERROR: Invalid tranmission length */
          status = SAHARA_NAK_INVALID_TX_LENGTH;
        }
      }

    }

  } while (FALSE);

  boot_sahara_data_ptr->status = status;
}

/* ============================================================================
**  Function : boot_sahara_mem_debug_copy_restricted
** ============================================================================
*
*   @brief
*   Copies the restricted data to a memory debug buffer. Returns FALSE if error, else TRUE
*
*/
static bl_error_boot_type boot_sahara_mem_debug_copy_restricted(boot_sahara_info * const boot_sahara_info_ptr,
    const uintnt addr,
    const uintnt len,
    boot_boolean *is_copy_success)
{
  bl_error_boot_type return_status =  BL_ERR_NONE;
  ramdump_table_if *sahara_mem_debug_tbl_ptr = NULL;

  if (boot_sahara_info_ptr == NULL || is_copy_success == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }

  sahara_mem_debug_tbl_ptr = _get_boot_sahara_mem_debug_tbl(boot_sahara_info_ptr);

  do
  {
    *is_copy_success = FALSE;

    if ( sahara_mem_debug_tbl_ptr == NULL ||
         ((boot_sahara_info_ptr->mem_debug_handle).sahara_mem_debug_buffer) == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Clear memory debug buffer */
    memset((void *)((boot_sahara_info_ptr->mem_debug_handle).sahara_mem_debug_buffer), 0x0, SAHARA_MAX_MEMORY_DATA_SIZE_IN_BYTES);

    if (addr < 0 || len > SAHARA_MAX_MEMORY_DATA_SIZE_IN_BYTES)
    {
      /* Return FALSE for out of bound memory */
      break;
    }

    /* Copy over data to mem debug buffer */
    return_status = sahara_mem_debug_tbl_ptr->copy_restricted((uint8*)((boot_sahara_info_ptr->mem_debug_handle).sahara_mem_debug_buffer),
                    addr,
                    len);
    if (return_status != BL_ERR_NONE)
    {
      /* Return FALSE for copy failing */
      break;
    }

    *is_copy_success = TRUE;
  } while (FALSE);

  return return_status;
}

/* ============================================================================
**  Function : boot_sahara_handle_cmd_switch_mode
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for CMD_SWITCH_MODE packet.
*
*   @details
*   This function switches to the given mode specified in the packet
*   if the current state is WAIT_CMD_EXEC. The target then enters
*   WAIT_HELLO_RESP state and returns to process_packets. At this point
*   the target will send a HELLO packet to the host -- see implementation
*   details of process_packets.
*
*   @param *packet_buffer   -  [IN/OUT] Buffer that contains the packet
*   @param length           -  [IN    ] Length of packet
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_cmd_switch_mode
(
  boot_sahara_info * const boot_sahara_info_ptr,
  uint32 length
)
{
  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  struct sahara_packet_cmd_switch_mode* packet_cmd_switch_mode =
    (struct sahara_packet_cmd_switch_mode*)boot_sahara_data_ptr->sahara_packet_buffer;

  boot_sahara_status status = SAHARA_STATUS_SUCCESS;

  if ((length != sizeof(struct sahara_packet_cmd_switch_mode)) ||
      (length != packet_cmd_switch_mode->length))
  {
    // ERROR: Invalid packet size received
    status = SAHARA_NAK_INVALID_PACKET_SIZE;

    // End of while loop in Process Packets
    //handle->sahara_done = TRUE;
  }
  else
  {
    // Set mode
    if (packet_cmd_switch_mode->mode < SAHARA_MODE_LAST)
    {
      boot_sahara_data_ptr->sahara_mode =
        (enum boot_sahara_mode) packet_cmd_switch_mode->mode;
    }

    // process_packets will automatically send HELLO
    boot_sahara_data_ptr->sahara_state = SAHARA_STATE_WAIT_HELLO_RESP;
  }

  boot_sahara_data_ptr->status = status;
}

/* ============================================================================
**  Function : boot_sahara_handle_cmd_exec
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for CMD_EXEC packet.
*
*   @details
*   This function parses out the client_command to execute from the packet
*   and executes the given command via the dispatch table exec_cmd API.
*   The response buffer is filled by this call and then sent to the host.
*   Host should be aware of the expected response length for a given
*   command since this information is not transmitted by the target.
*   If there is a mismatch of response length, the host should handle it
*   appropriately.
*
*   @param *packet_buffer   -  [IN/OUT] Buffer that contains the packet
*   @param length           -  [IN    ] Length of packet
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_cmd_exec
(
  boot_sahara_info * const boot_sahara_info_ptr,
  uint32 length
)
{
  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  boot_sahara_cmd_exec_data* boot_sahara_cmd_exec_data_ptr =
    _get_boot_sahara_cmd_exec_data(boot_sahara_info_ptr);

  struct sahara_packet_cmd_exec* packet_cmd_exec =
    (struct sahara_packet_cmd_exec*)boot_sahara_data_ptr->sahara_packet_buffer;

  if ((length != sizeof(struct sahara_packet_cmd_exec)) ||
      (length != packet_cmd_exec->length))
  {
    // ERROR: Invalid packet size received
    boot_sahara_data_ptr->status = SAHARA_NAK_INVALID_PACKET_SIZE;
  }
  else
  {
    // Execute command
    boot_sahara_exec_cmd( boot_sahara_info_ptr,
                          packet_cmd_exec->client_command);

    boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_client_command =
      packet_cmd_exec->client_command;

    if (boot_sahara_data_ptr->status == SAHARA_STATUS_SUCCESS)
    {
      // Send CMD_EXEC_RESP with corresponding response length
      boot_sahara_handle_cmd_exec_resp(boot_sahara_info_ptr);
    }
  }
}

/* ============================================================================
**  Function : boot_sahara_exec_cmd
** ============================================================================
*/
/*!
*   @brief
*   Executes a command based on the input client_command and set the
*   resp_buffer with the corresponding response.
*
*   @details
*   This function decodes the client_command and executes the corresponding
*   functions that are supported by SBL. The pointer to the response data
*   is returned, along with the length and status of execution.
*
*   @param client_command   -  [IN    ] ID of command to execute
*   @param *resp_length     -  [IN/OUT] Response length for executed command
*   @param *status          -  [IN/OUT] Status of executed command
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval returns pointer to response data.
*
*   @sa None
*/
static void boot_sahara_exec_cmd
(
  boot_sahara_info * const boot_sahara_info_ptr,
  uint32 client_command
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_sahara_status exec_status = SAHARA_STATUS_SUCCESS;
  uint32 resp_length = 0;
  uint32 resp_buff = 0;

  boot_sahara_command_handler_if* boot_sahara_command_handler_ptr =
    _get_boot_sahara_command_handler_if(boot_sahara_info_ptr);

  boot_sahara_cmd_exec_data* boot_sahara_cmd_exec_data_ptr =
    _get_boot_sahara_cmd_exec_data(boot_sahara_info_ptr);

  boot_sahara_data* boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  /* Store client command responses */
  void* boot_sahara_cmd_exec_data_resp_buf = boot_sahara_cmd_exec_data_ptr->
      sahara_cmd_temp_data_resp_buf;

  if (boot_sahara_cmd_exec_data_resp_buf == NULL)
  {
    exec_status = SAHARA_NAK_EXEC_CMD_INVALID_PARAM;
    goto exit;
  }

  /* Check for maximum size required for current commands supported
      and input parameters */

  /* Execute command based on input client_command */
  switch (client_command)
  {
  case SAHARA_EXEC_CMD_SERIAL_NUM_READ:
    return_status = boot_sahara_command_handler_ptr->read_serial_number(&resp_buff);
    if (return_status != BL_ERR_NONE)
    {
      exec_status = SAHARA_NAK_CMD_EXEC_FAILURE;
    }
    else
    {
      resp_length = sizeof(resp_buff);
      memcpy(boot_sahara_cmd_exec_data_resp_buf, &resp_buff, resp_length);

      boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data =
        boot_sahara_cmd_exec_data_resp_buf;
    }
    break;

  case SAHARA_EXEC_CMD_GET_COMMAND_ID_LIST:
    resp_buff = SAHARA_EXEC_CMD_GET_TRAINING_DATA;
    resp_length = sizeof(resp_buff);
    memcpy(boot_sahara_cmd_exec_data_resp_buf, &resp_buff, resp_length);

    boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data =
      boot_sahara_cmd_exec_data_resp_buf;
    break;

  case SAHARA_EXEC_CMD_GET_TRAINING_DATA:
    return_status = boot_sahara_command_handler_ptr->get_ddr_training(
                      &resp_length,
                      &(boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data));
    if (return_status != BL_ERR_NONE)
    {
      exec_status = SAHARA_NAK_CMD_EXEC_FAILURE;
    }
    break;

  default:
    resp_length = 0;
    /* ERROR: Unsupported client command received */
    exec_status = SAHARA_NAK_EXEC_CMD_UNSUPPORTED;
    break;
  }

exit:
  boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data_length = resp_length;
  boot_sahara_data_ptr->status = exec_status;

  return;
}

/* ============================================================================
**  Function : boot_sahara_handle_cmd_exec_resp
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for CMD_EXEC_RESP packet.
*
*   @details
*   This function sends a CMD_EXEC_RESP packet to the host based on the
*   executed client_command. The response length field is set based on the
*   actual command executed. If the response length is > 0, then the target
*   will expect a CMD_EXEC_DATA packet from the host before sending out the
*   response data.
*
*   @param  None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_cmd_exec_resp(
  boot_sahara_info * const boot_sahara_info_ptr )
{
  // error code returned from raw data read
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;

  uint32 tx_length;

  boot_sahara_cmd_exec_data *boot_sahara_cmd_exec_data_ptr =
    _get_boot_sahara_cmd_exec_data(boot_sahara_info_ptr);

  boot_sahara_data* boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  boot_sahara_status status = SAHARA_STATUS_SUCCESS;
  struct sahara_packet_cmd_exec_resp* packet_cmd_exec_resp =
    (struct sahara_packet_cmd_exec_resp*)boot_sahara_data_ptr->sahara_packet_buffer;

  packet_cmd_exec_resp->command = SAHARA_CMD_EXEC_RESP_ID;
  packet_cmd_exec_resp->length = sizeof(struct sahara_packet_cmd_exec_resp);
  packet_cmd_exec_resp->client_command = boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_client_command;
  packet_cmd_exec_resp->resp_length = boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data_length;

  // Log transmitted packet
  boot_sahara_log_packet_buffer((uint8 *)packet_cmd_exec_resp,
                                packet_cmd_exec_resp->length,
                                SAHARA_PACKET_TRANSMIT);

  tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                    (uint8 *)packet_cmd_exec_resp,
                                    packet_cmd_exec_resp->length,
                                    &err_code);

  // Check for error in transmission of CMD_EXEC_RESP packet
  if (err_code == BULK_ERR_TIMEOUT)
  {
    // ERROR: Timeout while transmitting data
    status = SAHARA_NAK_TIMEOUT_TX;
  }
  else if (err_code == BULK_ERR_CABLE_DISCONNECT)
  {
    // ERROR: Cable disconnected
    status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
  }
  else if (err_code != BULK_SUCCESS)
  {
    // ERROR: General transmission or reception error
    status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
  }
  else if (tx_length != packet_cmd_exec_resp->length)
  {
    // ERROR: Invalid tranmission length
    status = SAHARA_NAK_INVALID_TX_LENGTH;
  }

  if (status == SAHARA_STATUS_SUCCESS && boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data_length > 0)
  {
    // Wait for CMD_EXEC_DATA packet before sending response data
    boot_sahara_data_ptr->sahara_state = SAHARA_STATE_WAIT_CMD_EXEC_DATA;
  }

  boot_sahara_data_ptr->status = status;
}

/* ============================================================================
**  Function : boot_sahara_handle_cmd_exec_data
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for CMD_EXEC_DATA packet.
*
*   @details
*   This function sends the RAW_DATA response for the last executed command.
*   Once complete, the target will then transition to a state to wait for
*   another command.
*
*   @param *packet_buffer   -  [IN/OUT] Param_description_goes_here
*   @param length           -  [IN    ] Param_description_goes_here
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_cmd_exec_data
(
  boot_sahara_info * const boot_sahara_info_ptr,
  uint32 length
)
{
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;
  uint32 tx_length;

  boot_sahara_data* boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  boot_sahara_cmd_exec_data* boot_sahara_cmd_exec_data_ptr =
    _get_boot_sahara_cmd_exec_data(boot_sahara_info_ptr);

  struct sahara_packet_cmd_exec_data* packet_cmd_exec_data =
    (struct sahara_packet_cmd_exec_data*)boot_sahara_data_ptr->sahara_packet_buffer;
  boot_sahara_status status = SAHARA_STATUS_SUCCESS;

  if ((length != sizeof(struct sahara_packet_cmd_exec_data)) ||
      (length != packet_cmd_exec_data->length))
  {
    // ERROR: Invalid packet size received
    status = SAHARA_NAK_INVALID_PACKET_SIZE;
  }
  else if (packet_cmd_exec_data->client_command !=
           boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_client_command)
  {
    // ERROR: Invalid client command received for data response
    status = SAHARA_NAK_EXEC_DATA_INVALID_CLIENT_CMD;
  }
  else
  {
    // Log transmitted packet
    boot_sahara_log_packet_buffer((uint8*)boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data,
                                  boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data_length,
                                  SAHARA_PACKET_TRANSMIT);

    // Transmit command execution response data
    tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                      (uint8*)boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data,
                                      boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data_length,
                                      &err_code);

    // Check for error in transmission of response data
    if (err_code == BULK_ERR_TIMEOUT)
    {
      // ERROR: Timeout while transmitting data
      status = SAHARA_NAK_TIMEOUT_TX;
    }
    else if (err_code == BULK_ERR_CABLE_DISCONNECT)
    {
      // ERROR: Cable disconnected
      status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
    }
    else if (err_code != BULK_SUCCESS)
    {
      // ERROR: General transmission or reception error
      status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
    }
    else if (tx_length != boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data_length)
    {
      // ERROR: Invalid tranmission length
      status = SAHARA_NAK_INVALID_TX_LENGTH;
    }

    if (status == SAHARA_STATUS_SUCCESS)
    {
      // Wait to receive another command
      boot_sahara_data_ptr->sahara_state = SAHARA_STATE_WAIT_CMD_EXEC;
    }
  }

  boot_sahara_data_ptr->status = status;

  /*if(status != SAHARA_STATUS_SUCCESS)
  {
    // End of while loop in Process Packets
    //handle->sahara_done = TRUE;
  }*/
}

/* ============================================================================
**  Function : boot_sahara_handle_memory_debug
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for MEMORY_DEBUG packet.
*
*   @details
*   This function sends the memory region table and table length in the
*   MEMORY_DEBUG packet to the host. The state then transitions to wait
*   for MEMORY_READ packets.
*
*   @param  None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_memory_debug( boot_sahara_info * const boot_sahara_info_ptr )
{
  uint32 tx_length;
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_sahara_status exec_status = SAHARA_STATUS_SUCCESS;

  boot_sahara_data* boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  ramdump_table_if *sahara_mem_debug_tbl_ptr =
    _get_boot_sahara_mem_debug_tbl(boot_sahara_info_ptr);

  // Setup MEMORY_DEBUG packet
  struct sahara_packet_memory_debug* packet_memory_debug =
    (struct sahara_packet_memory_debug*)boot_sahara_data_ptr->sahara_packet_buffer;
  packet_memory_debug->command = SAHARA_MEMORY_DEBUG_ID;
  packet_memory_debug->length = sizeof(struct sahara_packet_memory_debug);

  do
  {
    return_status = sahara_mem_debug_tbl_ptr->get_table_addr(
                      (boot_sahara_info_ptr->mem_debug_handle).ramdump_table_handle,
                      (uintnt *)&packet_memory_debug->memory_table_addr);
    if (return_status != BL_ERR_NONE)
    {
      exec_status = SAHARA_NAK_MEMORY_DEBUG_NOT_SUPPORTED;
      break;
    }

    return_status = sahara_mem_debug_tbl_ptr->get_table_len(
                      (boot_sahara_info_ptr->mem_debug_handle).ramdump_table_handle,
                      (uintnt *)&packet_memory_debug->memory_table_length);
    if (return_status != BL_ERR_NONE)
    {
      exec_status = SAHARA_NAK_MEMORY_DEBUG_NOT_SUPPORTED;
      break;
    }

    /* Send the Memory Debug */
    tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                      (uint8 *)packet_memory_debug,
                                      packet_memory_debug->length,
                                      &err_code);

    // Check for error in transmission of CMD_READY packet
    if (err_code == BULK_ERR_TIMEOUT)
    {
      // ERROR: Timeout while transmitting data
      exec_status = SAHARA_NAK_TIMEOUT_TX;
    }
    else if (err_code == BULK_ERR_CABLE_DISCONNECT)
    {
      // ERROR: Cable disconnected
      exec_status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
    }
    else if (err_code != BULK_SUCCESS)
    {
      // ERROR: General transmission or reception error
      exec_status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
    }
    else if (tx_length != packet_memory_debug->length)
    {
      // ERROR: Invalid tranmission length
      exec_status = SAHARA_NAK_INVALID_TX_LENGTH;
    }
    else
    {
      boot_sahara_data_ptr->sahara_state = SAHARA_STATE_WAIT_MEMORY_READ;
    }
  } while (FALSE);

  boot_sahara_data_ptr->status = exec_status;

}

/* ============================================================================
**  Function : boot_sahara_handle_memory_debug_64bit
** ============================================================================
*/
/*!
*   @brief
*   Packet handler for MEMORY_DEBUG packet.
*
*   @details
*   This function sends the memory region table and table length in the
*   MEMORY_DEBUG packet to the host. The state then transitions to wait
*   for MEMORY_READ packets.
*
*   @param  None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_handle_memory_debug_64bit( boot_sahara_info * const boot_sahara_info_ptr )
{
  uint32 tx_length;
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_sahara_status exec_status = SAHARA_STATUS_SUCCESS;

  boot_sahara_data* boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  ramdump_table_if *sahara_mem_debug_tbl_ptr =
    _get_boot_sahara_mem_debug_tbl(boot_sahara_info_ptr);

  // Setup MEMORY_DEBUG packet
  struct sahara_packet_memory_debug_64bit* packet_memory_debug =
    (struct sahara_packet_memory_debug_64bit*)boot_sahara_data_ptr->sahara_packet_buffer;
  packet_memory_debug->command = SAHARA_64_BITS_MEMORY_DEBUG_ID;
  packet_memory_debug->length = sizeof(struct sahara_packet_memory_debug_64bit);

  do
  {
    return_status = sahara_mem_debug_tbl_ptr->get_table_addr(
                      (boot_sahara_info_ptr->mem_debug_handle).ramdump_table_handle,
                      (uintnt *)&packet_memory_debug->memory_table_addr);
    if (return_status != BL_ERR_NONE)
    {
      exec_status = SAHARA_NAK_MEMORY_DEBUG_NOT_SUPPORTED;
      break;
    }

    return_status = sahara_mem_debug_tbl_ptr->get_table_len(
                      (boot_sahara_info_ptr->mem_debug_handle).ramdump_table_handle,
                      (uintnt *)&packet_memory_debug->memory_table_length);
    if (return_status != BL_ERR_NONE)
    {
      exec_status = SAHARA_NAK_MEMORY_DEBUG_NOT_SUPPORTED;
      break;
    }

    /* Send the Memory Debug */
    tx_length = boot_sahara_handle_tx(boot_sahara_info_ptr,
                                      (uint8 *)packet_memory_debug,
                                      packet_memory_debug->length,
                                      &err_code);

    // Check for error in transmission of CMD_READY packet
    if (err_code == BULK_ERR_TIMEOUT)
    {
      // ERROR: Timeout while transmitting data
      exec_status = SAHARA_NAK_TIMEOUT_TX;
    }
    else if (err_code == BULK_ERR_CABLE_DISCONNECT)
    {
      // ERROR: Cable disconnected
      exec_status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
    }
    else if (err_code != BULK_SUCCESS)
    {
      // ERROR: General transmission or reception error
      exec_status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
    }
    else if (tx_length != packet_memory_debug->length)
    {
      // ERROR: Invalid tranmission length
      exec_status = SAHARA_NAK_INVALID_TX_LENGTH;
    }
    else
    {
      boot_sahara_data_ptr->sahara_state = SAHARA_STATE_WAIT_MEMORY_READ;
    }
  } while (FALSE);

  boot_sahara_data_ptr->status = exec_status;

}

/* ============================================================================
**  Function : boot_sahara_process_packets
** ============================================================================
*/
/*!
*   @brief
*   This function processes incoming Sahara command packets and calls the
*   corresponding packet handler
*
*   @details
*   This function continually loops until a DONE packet is received and a
*   DONE_RESP is successfully sent to the host. Incoming packets will
*   continually be processed and forwarded to the appropriate packet handler.
*   Each handler will appropriately process the packet, respond, and update
*   the internal state machine. If the incoming packet is unnrecognized, an
*   END_IMAGE_TX will be sent with the corresponding error code.
*
*   @param  None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_process_packets(
  boot_sahara_info * const boot_sahara_info_ptr,
  enum boot_sahara_context_flag context_flag )
{
  uint32 length;
  // Get the pointer to sahara_data in boot_sahara_info
  boot_sahara_data *boot_sahara_data_ptr = _get_boot_sahara_data(boot_sahara_info_ptr);

  // Get packet buffer to receive packet
  uint8 *sahara_packet_buffer = boot_sahara_data_ptr->sahara_packet_buffer;

  // Get sahara State from sahara data
  volatile enum boot_sahara_state *sahara_state = &(boot_sahara_data_ptr->sahara_state);

  // Set sahara done to false
  boot_sahara_data_ptr->sahara_done = FALSE;

  // error code returned from raw data read
  enum boot_sahara_bulk_error err_code = BULK_SUCCESS;
  boolean sahara_valid_state;


  while (!(boot_sahara_data_ptr->sahara_done))
  {
    // Set state as invalid
    sahara_valid_state = FALSE;

    length = boot_sahara_handle_rx(
               boot_sahara_info_ptr,
               (uint8 *)sahara_packet_buffer,
               SAHARA_MAX_PACKET_SIZE_IN_BYTES,
               &err_code,
               SAHARA_PACKET_TYPE_COMMAND,
               SAHARA_READ_BLOCKING);

    if (length > 0 && err_code == BULK_SUCCESS)
    {
      // Log incoming command packet
      boot_sahara_log_packet_buffer((uint8 *)sahara_packet_buffer,
                                    length,
                                    SAHARA_PACKET_RECEIVE);

      /* Decode command packet */
      switch (sahara_packet_buffer[0])
      {
      case SAHARA_HELLO_RESP_ID:
        if (*sahara_state == SAHARA_STATE_WAIT_HELLO_RESP)
        {
          /*  Return SAHARA STATE is
              1.  SAHARA_STATE_DATA_READ_PAYLOAD  **the new state
              2.  SAHARA_STATE_WAIT_CMD_EXEC
              3.  SAHARA_STATE_WAIT_RESET.... _open calls _close()

          */
          boot_sahara_handle_hello_resp(boot_sahara_info_ptr, length);
          sahara_valid_state = TRUE;
        }
        break;

      case SAHARA_DONE_ID:
        if (*sahara_state == SAHARA_STATE_WAIT_DONE)
        {
          boot_sahara_handle_done(boot_sahara_info_ptr, length);
          sahara_valid_state = TRUE;
        }
        break;

      case SAHARA_RESET_ID:
        if ((*sahara_state == SAHARA_STATE_WAIT_HELLO_RESP) ||
            (*sahara_state == SAHARA_STATE_WAIT_RESET) ||
            (*sahara_state == SAHARA_STATE_WAIT_MEMORY_READ) ||
            (*sahara_state == SAHARA_STATE_WAIT_CMD_EXEC))
        {
          /* If Status is not SAHARA_STATUS_SUCCESS then State it
             will return to is SAHARA_STATE_RESET_RCVD_WITH_STATUS_EQ_ERR
          */
          boot_sahara_handle_reset(boot_sahara_info_ptr, length);
          sahara_valid_state = TRUE;
        }
        break;

      case SAHARA_MEMORY_READ_ID:
        if (*sahara_state == SAHARA_STATE_WAIT_MEMORY_READ)
        {
          boot_sahara_handle_memory_read(boot_sahara_info_ptr, length);
          sahara_valid_state = TRUE;
        }
        break;

      case SAHARA_64_BITS_MEMORY_READ_ID:
        if (*sahara_state == SAHARA_STATE_WAIT_MEMORY_READ)
        {
          boot_sahara_handle_memory_64bits_read((boot_sahara_info*)boot_sahara_info_ptr, length);
          sahara_valid_state = TRUE;
        }
        break;

      case SAHARA_CMD_SWITCH_MODE_ID:
        if ((*sahara_state == SAHARA_STATE_WAIT_CMD_EXEC) ||
            (*sahara_state == SAHARA_STATE_WAIT_MEMORY_READ))
        {
          boot_sahara_handle_cmd_switch_mode(boot_sahara_info_ptr, length);
          sahara_valid_state = TRUE;
        }
        break;

      case SAHARA_CMD_EXEC_ID:
        if (*sahara_state == SAHARA_STATE_WAIT_CMD_EXEC)
        {
          /* Return SAHARA STATE is SAHARA_STATE_WAIT_CMD_EXEC_DATA
          */
          boot_sahara_handle_cmd_exec(boot_sahara_info_ptr, length);
          sahara_valid_state = TRUE;
        }
        break;

      case SAHARA_CMD_EXEC_DATA_ID:
        if (*sahara_state == SAHARA_STATE_WAIT_CMD_EXEC_DATA)
        {
          boot_sahara_handle_cmd_exec_data(boot_sahara_info_ptr, length);
          sahara_valid_state = TRUE;
        }
        break;

      default:
        break;
      } // end of switch case
    } // end of if-else

    /* If sahara is not waiting for hello response and
     it receives invalid command, send NAK */

    if (FALSE  == sahara_valid_state &&
        SAHARA_STATE_WAIT_HELLO_RESP != *sahara_state)
    {
      // Check for reception error of data
      if (err_code == BULK_ERR_TIMEOUT)
      {
        // ERROR: Timeout while receiving data
        boot_sahara_data_ptr->status = SAHARA_NAK_TIMEOUT_RX;
      }
      else if (err_code == BULK_ERR_CABLE_DISCONNECT)
      {
        // ERROR: General transmission or reception error
        boot_sahara_data_ptr->status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
      }
      else if (err_code != BULK_SUCCESS)
      {
        // ERROR: General transmission or reception error
        boot_sahara_data_ptr->status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
      }
      else
      {
        // set the STATUS to SAHARA_NAK_INVALID_CMD and send it to _close()
        boot_sahara_data_ptr->status = SAHARA_NAK_INVALID_CMD;
      }
    }


    if (SAHARA_OPEN_READ_ASYNCH_CONTEXT == context_flag)
    {
      /* From _Open() or _Read or _AsynchRead() context */
      if (SAHARA_STATUS_SUCCESS != boot_sahara_data_ptr->status ||
          SAHARA_STATE_DATA_READ_PAYLOAD == boot_sahara_data_ptr->sahara_state )
      {
        boot_sahara_data_ptr->sahara_done = TRUE;
      }
    }
    else if (SAHARA_CLOSE_CONTEXT == context_flag)
    {
      /* From Close() context */
      if (SAHARA_STATUS_SUCCESS != boot_sahara_data_ptr->status &&
          boot_sahara_data_ptr->sahara_state != SAHARA_STATE_RESET_RCVD_WITH_STATUS_EQ_ERR)
      {
        boot_sahara_handle_end_image_tx(boot_sahara_info_ptr);

        /* If boot_sahara_handle_end_image_tx fails, state will be set to
            SAHARA_STATE_RESET_RCVD_WITH_STATUS_EQ_ERR. Break the loop to return
        */
        if (boot_sahara_data_ptr->sahara_state == SAHARA_STATE_RESET_RCVD_WITH_STATUS_EQ_ERR)
        {
          boot_sahara_data_ptr->sahara_done = TRUE;
        }
      }
      else
      {
        boot_sahara_data_ptr->sahara_done = TRUE;
      }
    }

    /* If sahara is waiting for hello response and
       it receives invalid command, resend hello */
    if (SAHARA_STATE_WAIT_HELLO_RESP == boot_sahara_data_ptr->sahara_state &&
        SAHARA_STATUS_SUCCESS == boot_sahara_data_ptr->status)
    {
      boot_sahara_handle_hello(boot_sahara_info_ptr);
    }

  } /* end of while (!boot_sahara_data_ptr->sahara_done) */

  return;
} /* End of boot_sahara_process_packets */


/* ============================================================================
**  Function : boot_sahara_reset
** ============================================================================
*/
/*!
*   @brief
*   Shutdown Sahara protocol and driver, and reset the target.
*
*   @details
*   Shutdown Sahara protocol and driver, and reset the target.
*
*  @param  None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
static void boot_sahara_reset ( boot_sahara_info * const boot_sahara_info_ptr )
{

  boot_sahara_command_handler_if *boot_sahara_command_handler_ptr =
    _get_boot_sahara_command_handler_if(boot_sahara_info_ptr);

  bl_error_boot_type (*sahara_reset)(void) = boot_sahara_command_handler_ptr->reset;

  /* Get the pointer to sahara_data in boot_sahara_info */
  boot_sahara_data *boot_sahara_data_ptr = _get_boot_sahara_data(boot_sahara_info_ptr);

  /* Shutdown Sahara */
  boot_sahara_exit(boot_sahara_info_ptr);

  /*  if status != success then avoid hardware reset in sahara,
      instead return error code to client, which will enter
      error-handler and reset eventually
  */
  if (boot_sahara_data_ptr->status != SAHARA_STATUS_SUCCESS)
  {
    /* Set the State to Return Status so that it can return to upper layers */
    boot_sahara_data_ptr->sahara_state = SAHARA_STATE_RESET_RCVD_WITH_STATUS_EQ_ERR;
    return;
  }

  // Reset target
  sahara_reset();

  // Reset should not return. Make sure this would be in while 1 loop
  // if it returns
  INFINITE_LOOP();
}

/* ============================================================================
**  Function : boot_sahara_entry
** ============================================================================
*/
/*!
*   @brief
*   This function provides an entry into the Sahara protocol and jumps into
*   the protocol.
*
*   @details
*   This function initializes the Sahara protocol followed by sending a HELLO
*   packet to the host. After that, the target will proceed to wait for
*   incoming packets and handle them appropriately.
*
*   @param sahara_interface      -  [IN/OUT] Interface to be used by protocol
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   boot_sahara_init() will be called which calls the dispatch table's init()
*   routine - this is intended to initialize any hardware that is required
*   for the protocol to execute.
*
*   @retval  Boolean
*
*   @sa None
*/
boot_sahara_status boot_sahara_entry
(
  boot_sahara_info *boot_sahara_info_ptr
)
{
  // Set Global boot sahara info Pointer (for tx & rx callback functions
  _set_boot_sahara_info_pointer(boot_sahara_info_ptr);

  // Send hello packet
  boot_sahara_handle_hello(boot_sahara_info_ptr);

  // Enter Sahara packet handler
  boot_sahara_process_packets(boot_sahara_info_ptr,
                              SAHARA_OPEN_READ_ASYNCH_CONTEXT);

  return (_get_boot_sahara_data(boot_sahara_info_ptr))->status;
}

boot_sahara_status boot_sahara_read
(
  boot_sahara_info *boot_sahara_info_ptr,
  void *ram_addr,
  uint64 src_offset,
  uint32 bytes_to_read
)
{
  enum boot_sahara_bulk_error error = BULK_SUCCESS;
  boot_sahara_status status = SAHARA_STATUS_SUCCESS;
  uint32 image_transfer_size_left = bytes_to_read;
  uint32 image_size_read = 0;
  uint32 image_transfer_size = 0;
  uint8 *dest_address = (uint8 *)ram_addr;

  boot_sahara_dispatch_tbl* sahara_dispatch_tbl =
    _get_boot_sahara_dispatch_tbl(boot_sahara_info_ptr);

  // Get Maximum data size from transport layer
  uint32 max_raw_data_size =  sahara_dispatch_tbl->get_max_raw_data_size();

  boot_sahara_data* boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  // Send READ_DATA request to read data
  boot_sahara_handle_read_data(boot_sahara_info_ptr,
                               src_offset,
                               bytes_to_read);

  // Check whether Read Data Packet Tx was a success
  if (boot_sahara_data_ptr->status != SAHARA_STATUS_SUCCESS)
  {
    return boot_sahara_data_ptr->status;
  }

  /* Dividing the data requested to raw data size that Transport layer supports */
  while (status == SAHARA_STATUS_SUCCESS &&
         image_transfer_size_left != 0)
  {
    if (image_transfer_size_left > max_raw_data_size)
    {
      image_transfer_size = max_raw_data_size;
    }
    else
    {
      image_transfer_size = image_transfer_size_left;
    }

    // Set Global boot sahara info Pointer (for tx & rx callback functions)
    _set_boot_sahara_info_pointer(boot_sahara_info_ptr);

    /* Forcing Blocking call for all boot_sahara_rx */
    image_size_read = boot_sahara_handle_rx(boot_sahara_info_ptr,
                                            dest_address,
                                            image_transfer_size,
                                            &error, SAHARA_PACKET_TYPE_DATA,
                                            SAHARA_READ_BLOCKING);

    if (error == BULK_ERR_TIMEOUT)
    {
      // ERROR: Timeout while receiving data
      status = SAHARA_NAK_TIMEOUT_RX;
    }
    else if (error == BULK_ERR_CABLE_DISCONNECT)
    {
      // ERROR: General transmission or reception error
      status = SAHARA_NAK_CABLE_DISCONNECT_ERROR;
    }
    else if (error != BULK_SUCCESS)
    {
      // ERROR: General transmission or reception error
      status = SAHARA_NAK_GENERAL_TX_RX_ERROR;
    }

    image_transfer_size_left -= image_size_read;
    dest_address += image_size_read;
  }

  return status;
}

boot_sahara_status boot_sahara_poll
(
  boot_sahara_info *boot_sahara_info_ptr
)
{
  boot_sahara_status status = SAHARA_STATUS_SUCCESS;
  // Get Dispatch table from boot sahara info
  boot_sahara_dispatch_tbl *sahara_dispatch_tbl =
    _get_boot_sahara_dispatch_tbl(boot_sahara_info_ptr);

  // Get callback parameters pointer from boot sahara info
  boot_sahara_callback_parameters* callback_parameters_ptr =
    _get_boot_sahara_callback_parameters(boot_sahara_info_ptr);

  while (!callback_parameters_ptr->sahara_rx_complete)
  {
    sahara_dispatch_tbl->poll();
  }

  if (BULK_SUCCESS != callback_parameters_ptr->sahara_rx_err_code)
  {
    status = SAHARA_NAK_BULK_TRANSFER_ERROR;
  }

  return status;
}

/* ============================================================================
**  Function : boot_sahara_end
** ============================================================================
*/
/*!
*   @brief
*   This function provides an entry into the Sahara protocol and jumps into
*   the protocol.
*
*   @details
*   This function initializes the Sahara protocol followed by sending a HELLO
*   packet to the host. After that, the target will proceed to wait for
*   incoming packets and handle them appropriately.
*
*   @param sahara_interface      -  [IN/OUT] Interface to be used by protocol
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   boot_sahara_init() will be called which calls the dispatch table's init()
*   routine - this is intended to initialize any hardware that is required
*   for the protocol to execute.
*
*   @retval  Boolean
*
*   @sa None
*/
boot_sahara_status boot_sahara_end
(
  boot_sahara_info *boot_sahara_info_ptr
)
{
  /* Set Global boot sahara info Pointer (for tx & rx callback functions) */
  _set_boot_sahara_info_pointer(boot_sahara_info_ptr);

  /* Get sahara data table pointer from boot sahara info */
  boot_sahara_data *boot_sahara_data_ptr =
    _get_boot_sahara_data(boot_sahara_info_ptr);

  boot_sahara_handle_end_image_tx(boot_sahara_info_ptr);

  /* If boot_sahara_handle_end_image_tx fails, state will be set to
     SAHARA_STATE_RESET_RCVD_WITH_STATUS_EQ_ERR. Skip calling boot_sahara_process_packets
     and return the status.
  */
  if (boot_sahara_data_ptr->sahara_state != SAHARA_STATE_RESET_RCVD_WITH_STATUS_EQ_ERR)
  {
    boot_sahara_process_packets(boot_sahara_info_ptr,
                                SAHARA_CLOSE_CONTEXT);
  }

  return boot_sahara_data_ptr->status;
}
