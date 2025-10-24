/*=======================================================================*//**
 * @file        qusb_al_bulk.c
 * @author:     dpatnaik
 * @date        12-Feb-2011
 *
 * @brief       QUSB (Qualcomm High-Speed USB) AL (Adaptation-Layer) implementation.
 *
 * @details     This file contains the implementation of the APIs to be used by
 *              the boot Sahara downloader.
 *
 * @note        
 *
 *              Copyright 2011,2022 Qualcomm Technologies, Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/


// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// 
// when         who        what, where, why
// --------   ---        ----------------------------------------------------------
// 03/28/11   niting     Added callback support
// 02/12/11   dpatnaik Initial revision
//
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include <string.h>
#include "comdef.h"           // common defines - basic types as byte word uint32 etc
#include "qusb_al_bulk.h"
#include "qusb_fd.h"
#include "qusb_dcd.h"
#include "qusb_dci_api.h"
#include "qusb_log.h"
#include "qusb_ldr_utils.h"
#include "qusb_dci_common.h"
#include "qusb_common.h"


//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
// -------------------------------------------------------------------------*/

//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Static Function Declarations and Definitions
//----------------------------------------------------------------------------

// USB enumeration timeout to perform recovery
#define QUSB_BULK_ENUM_TIMER_VAL_USEC                     (5000 * 1000)

//Maximum Bulk transfer size 
#define QUSB_BULK_LAYER_MAX_TRANSFER_SIZE_IN_BYTES        (1024*1024)
#define QUSB_BULK_ZLP_TIMER_VAL_USEC                      50000  //50 milliseconds 

// iProduct
static char qusb_bulk_str_product[] = "QUSB_BULK";

//For synchronous read within QUSB
//Client does not pass completion callback 
//and rely on QUSB to poll until transfer completion 
typedef struct
{
  uint32 actual_length;
  boolean pending_read;
} qusb_synch_read_ctx;

typedef enum
{
  QUSB_CHECK_FOR_ZLP,
  QUSB_LACKS_ZLP,
  QUSB_SENDS_ZLP
} qusb_zlp_mode_e;


typedef struct
{
  //@TODO During Bring Up Enable CHECK_FOR_ZLP
  //static qusb_zlp_mode_e zlp_mode = QUSB_CHECK_FOR_ZLP;
  qusb_zlp_mode_e zlp_mode;
  boolean pending_rx_zlp;
  
  boolean waiting_for_zlp; //Used to indicate that we are waiting for a ZLP 
  uint32 cached_zlp_data_length; // Length of data received from the host instead of the impending ZLP
  uint32 no_zlp_count; //Number of times host sent data instead of ZLP. Used for tracking / debug.
  
  struct qusb_urb* tx_urb;
  struct qusb_dcd_dsc_device* dev;
  boolean enumerated;
  
  qusb_bulk_rx_cb_type rx_cb; //hold the callback for propagation to upper layer
  qusb_synch_read_ctx synch_rx_ctx;
  
  
 
  /*__QUSB_DMA_ZI__ */ uint8 zlp_read_buf[QUSB_MAX_PKT_SIZE_SUPER];
  /*__QUSB_DMA_ZI__ */ uint8 non_max_pkt_buffer[QUSB_MAX_PKT_SIZE_SUPER];
  uint32 non_max_pkt_transfer_size; 
  uint8* client_buffer_iter;
  
  boolean is_disconnected;
  boolean is_rx_in_progress;
  boolean enum_timeout_flag;
} qusb_xbl_al_ctx_t;

static qusb_xbl_al_ctx_t* qusb_al_ctx;

static void qusb_al_ctx_free(void)
{
  if (qusb_al_ctx)
  {
     if (FALSE == usb_dci_mem_free((void*)qusb_al_ctx))
     {
       qusb_error_log(AL_CTX_FREE_FAIL_LOG, 0, (uint32)(uintptr_t)qusb_al_ctx);
       return;
     }
     else
     {
       qusb_log(AL_CTX_FREE_LOG, 0, (uint32)(uintptr_t)qusb_al_ctx);
       qusb_al_ctx = NULL;
     }
  }
  else
  {
     qusb_error_log(AL_CTX_FREE_REDUNDANT_LOG, 0, 0);
  }
}


static boolean qusb_al_ctx_init(void)
{
  usb_dci_mem_handle_init();
  if (NULL == qusb_al_ctx)
  {
    if (FALSE == usb_dci_mem_allocate((void**)&qusb_al_ctx, sizeof(qusb_xbl_al_ctx_t)))
    {
      qusb_error_log(AL_CTX_INIT_FAIL_LOG, 0, 0);
      return FALSE;
    }
    qusb_log(AL_CTX_INIT_LOG, 0, (uint32)(uintptr_t)qusb_al_ctx);
  }
  else
  {
    qusb_error_log(AL_CTX_INIT_AGAIN_LOG, 0, (uint32)(uintptr_t)qusb_al_ctx);
    memset(qusb_al_ctx, 0, sizeof(qusb_xbl_al_ctx_t));
  }

  //@TODO During Bring Up Enable CHECK_FOR_ZLP
  //static qusb_zlp_mode_e zlp_mode = QUSB_CHECK_FOR_ZLP;
  qusb_al_ctx->zlp_mode                   = QUSB_SENDS_ZLP;
  qusb_al_ctx->pending_rx_zlp             = FALSE;
  
  qusb_al_ctx->waiting_for_zlp            = FALSE; //Used to indicate that we are waiting for a ZLP 
  qusb_al_ctx->cached_zlp_data_length     = 0; // Length of data received from the host instead of the impending ZLP
  qusb_al_ctx->no_zlp_count               = 0; //Number of times host sent data instead of ZLP. Used for tracking / debug.
  
  qusb_al_ctx->tx_urb                     = NULL;
  qusb_al_ctx->dev                        = NULL;
  qusb_al_ctx->enumerated                 = FALSE;
  
  qusb_al_ctx->rx_cb                      = NULL; //hold the callback for propagation to upper layer
  qusb_al_ctx->synch_rx_ctx.actual_length = 0;
  qusb_al_ctx->synch_rx_ctx.pending_read  = FALSE;
 
  qusb_al_ctx->is_disconnected            = FALSE;
  qusb_al_ctx->is_rx_in_progress          = FALSE;
  qusb_al_ctx->enum_timeout_flag          = FALSE;
  qusb_al_ctx->non_max_pkt_transfer_size  = 0;
  qusb_al_ctx->client_buffer_iter         = NULL;

  return TRUE;
}

boolean qusb_al_check_for_fedl(uint32 core_id, uint32 check_usb_opt, uint32 check_dp_timeout_ms)
{
  return  qusb_ldr_utils_fedl_check(check_usb_opt, check_dp_timeout_ms);
}


uint32 qusb_al_bulk_receive_zlp(void)
{
  uint32 err_code = FD_SUCCESS;
  if (NULL == qusb_al_ctx)
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return AL_CTX_NULL_LOG;
  }

  qusb_log(AL_BULK_RECEIVE_ZLP_LOG,0,0);
  //prepare an empty TD to read ZLP 
  err_code = qusb_fd_rx_pkt(qusb_al_ctx->zlp_read_buf, qusb_al_bulk_get_max_packet_size());
  if (err_code != FD_SUCCESS)
  {
    qusb_error_log(AL_BULK_RECEIVE_ZLP_ERROR_LOG, 0, 0);
  }
  else
  {
    if(qusb_al_ctx->zlp_mode == QUSB_CHECK_FOR_ZLP)
    {
      qusb_al_ctx->pending_rx_zlp = TRUE; 
      qusb_timer_start(QUSB_BULK_ZLP_TIMER_VAL_USEC); 
      //return flow control and let the next iteration of qusb_al_bulk_rx_complete handle the ZLP
    }
    //else for optimization don't prime start timer for ZLP
  }
  return err_code;
}

uint32 qusb_al_bulk_handle_rx_zlp_mode(void)
{
  uint32 err_code = FD_SUCCESS;
  if (NULL == qusb_al_ctx)
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return AL_CTX_NULL_LOG;
  }

  qusb_log(AL_BULK_HANDLE_RX_ZLP_MODE_LOG,0,qusb_al_ctx->zlp_mode);
  switch(qusb_al_ctx->zlp_mode)
  {
    case QUSB_CHECK_FOR_ZLP:
    case QUSB_SENDS_ZLP:
      qusb_al_ctx->waiting_for_zlp = TRUE;
      err_code = qusb_al_bulk_receive_zlp();
    break;
    case QUSB_LACKS_ZLP:
      //host is determined to not send ZLP
      break;
    default:
    break;
  }
  return err_code;
}

// ===========================================================================
/**
 * @function    qusb_al_bulk_set_zlp_mode
 * 
 * @brief   Sets the ZLP mode based on host type.
 *
 * @param   [IN] Whether host supports ZLP
 *
 *          
 * @return  None
 * 
 */
 // ===========================================================================
void qusb_al_bulk_set_zlp_mode(boolean host_sends_zlp)
{
  if (NULL == qusb_al_ctx)
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return;
  }

  //if this API is not called then by default it is QUSB_CHECK_FOR_ZLP
  // but for now it is QUSB_SENDS_ZLP
  if(TRUE == host_sends_zlp)
  {
    qusb_al_ctx->zlp_mode = QUSB_SENDS_ZLP;
    qusb_uart_log("host sends ZLP", 0);
  }
  else
  {
    qusb_al_ctx->zlp_mode = QUSB_LACKS_ZLP;
    qusb_uart_log("host lacks ZLP", 0);
  }
  qusb_log(AL_BULK_SET_ZLP_MODE_LOG, 0, qusb_al_ctx->zlp_mode);
}

// ===========================================================================
/**
 * @function    qusb_al_bulk_rx_complete
 * 
 * @brief   This function will be a called after each URB receive is complete.
 *
 * @details This function will be a called after each URB receive is complete.
 * 
 * @param   *urb   -  [IN/OUT] URB corresponding to the current reception
 * 
 * @return  None.
 * 
 */
// ===========================================================================
static void qusb_al_bulk_rx_complete(struct qusb_urb* urb)
{
  static uint32 total_bytes_received = 0;
  boolean short_packet_received = FALSE;
  uint32 err_code = FD_SUCCESS;

  if (NULL == qusb_al_ctx)
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return;
  }

  if(NULL == urb)
  {
    //this is not possible @rx_complete
    qusb_error_log(AL_NULL_POINTER_ERROR_LOG, 0, __LINE__);
    return;
  }

  qusb_log(AL_BULK_RX_COMPLETE_LOG,0,0);
  if (QUSB_URB_STATUS_COMPLETE_OK == urb->transfer_status)
  {
    if (urb->actual_length == 0) //ZLP 
    {
      qusb_log(AL_BULK_ZLP_ARRIVED_LOG,0,0);
      qusb_al_ctx->waiting_for_zlp = FALSE;      
      short_packet_received = TRUE; //ZLP coming anytime from the host

      //also look for ZLP that is pending from last iteration of priming buffers to trap ZLP
      if (qusb_al_ctx->pending_rx_zlp)
      {
        //host confirmed to send ZLP, can optimize and remov subsequent ZLP timer activation
        qusb_al_ctx->zlp_mode = QUSB_SENDS_ZLP;
        qusb_al_ctx->pending_rx_zlp = FALSE;
      }
    }
    if ((urb->actual_length % qusb_al_bulk_get_max_packet_size()) > 0) //check for short packet
    { 
      short_packet_received = TRUE; //end of transfer, return to upper layer
      qusb_log(AL_BULK_SHORT_PACKET_RECVD_LOG,0,total_bytes_received);
    }

    // urb completed with non_max_pkt_buffer (inner buffer) copy to client buffer
	if (((uint8*)(urb->transfer_buffer_ptr)) == (qusb_al_ctx->non_max_pkt_buffer))
	{
	  //qusb_bus_log(AL_NON_MAX_PKT_BUF_RX_COMPLETE_LOG, 0, urb->actual_length);

	  // if Host send more, dont copy and return read_error with total size host sent
	  if (qusb_al_ctx->non_max_pkt_transfer_size < urb->actual_length)
	  {
		qusb_error_log(AL_NON_MAX_PKT_BUF_RX_COMPLETE_EXTRA_DATA_LOG, 0, urb->actual_length);
		err_code = BULK_ERR_READ;
	  }
	  else
	  {
	    if (qusb_al_ctx->non_max_pkt_transfer_size > urb->actual_length)
	    {
		  qusb_error_log(AL_NON_MAX_PKT_BUF_RX_COMPLETE_LESS_DATA_LOG, 0, urb->actual_length); 
	    }
	    memscpy((void*)(qusb_al_ctx->client_buffer_iter), qusb_al_ctx->non_max_pkt_transfer_size, (void*)(qusb_al_ctx->non_max_pkt_buffer), urb->actual_length);
	  }
	  
	  qusb_al_ctx->non_max_pkt_transfer_size =0;
 	  qusb_al_ctx->client_buffer_iter = 0;	  
	}

    total_bytes_received += urb->actual_length;
    qusb_al_ctx->is_rx_in_progress = FALSE;
    qusb_log(TRANSFER_DONE_LOG,0,total_bytes_received);
  }
  else
  {
    //TODO handle other exceptional cases from lower layer 
    //signature of ZLP being missing from the host 
    if (QUSB_URB_STATUS_COMPLETE_ERROR == urb->transfer_status)
    {
      qusb_log(TRANSFER_ERROR_LOG,0,0);
      if (qusb_al_ctx->pending_rx_zlp)
      {
        short_packet_received = TRUE;
        qusb_al_ctx->pending_rx_zlp = FALSE;
      }
    }
  }

  //For short packets, transfer is complete, return the number of bytes transferred to the upper layer.
  //Otherwise, prime buffers to handle ZLP as needed.
  if (urb->transfer_length == urb->actual_length || short_packet_received)
  {

    //We expected a ZLP but received data from the host, then call the callback into client layer
    if (qusb_al_ctx->waiting_for_zlp && (urb->actual_length != 0))
    {
      qusb_log(AL_BULK_DATA_RECVD_INSTEAD_OF_ZLP_LOG,0,urb->actual_length);        
      qusb_al_ctx->rx_cb(total_bytes_received - urb->actual_length, BULK_SUCCESS); //Adjust bytes received and callback
      qusb_al_ctx->rx_cb = NULL; 
      total_bytes_received = urb->actual_length; //Update bytes received 
      qusb_al_ctx->cached_zlp_data_length = urb->actual_length; //Update count of how many bytes we are holding on to
      qusb_al_ctx->no_zlp_count++; //Increment count that keeps track of no ZLP condition
      return;
    }
    
    if ((urb->transfer_length == urb->actual_length) &&
      ((urb->transfer_length % qusb_al_bulk_get_max_packet_size()) == 0))
    {
	  //Extra data need to transfer for non max pkt size buffer
	  if (qusb_al_ctx->non_max_pkt_transfer_size >0)
	  {
		  if (((uint8*)(urb->transfer_buffer_ptr)) == (qusb_al_ctx->non_max_pkt_buffer))
		  {
			  qusb_error_log(AL_NON_MAX_PKT_BUF_USED_TWICE_LOG, 0, qusb_al_ctx->non_max_pkt_transfer_size);
              qusb_al_ctx->client_buffer_iter = (uint8*)(qusb_al_ctx->client_buffer_iter) + urb->actual_length;
		  }
		  else
		  {
			  // move the iterator to new destination address and store them in ctx
              qusb_al_ctx->client_buffer_iter = (uint8*)(urb->transfer_buffer_ptr) + urb->actual_length;
		  }
		  //qusb_log(AL_NON_MAX_PKT_BUF_RECIEVE_RX_LOG, 0, qusb_al_ctx->non_max_pkt_transfer_size);

		  err_code = qusb_fd_rx_pkt((void *)qusb_al_ctx->non_max_pkt_buffer, qusb_al_bulk_get_max_packet_size());
		  if (FD_SUCCESS != err_code)
		  {
			// error setting up subsequent reads, return error condition immediately
			if (qusb_al_ctx->rx_cb != NULL)
			{
			  qusb_al_ctx->rx_cb(total_bytes_received, BULK_SUCCESS);
			  qusb_al_ctx->rx_cb = NULL; //use only once 
			  total_bytes_received = 0;
			  qusb_al_ctx->is_rx_in_progress = FALSE;
			}
			else // synchronous read 
			{
			  qusb_al_ctx->synch_rx_ctx.actual_length = total_bytes_received;
			  qusb_al_ctx->synch_rx_ctx.pending_read = FALSE;
			  total_bytes_received = 0;
			}
		  }
		  else
		  {
			// TODO reset the timer if there is more to read 
			// otherwise let the read proceed 
		  }
	  }
      else if (qusb_al_ctx->zlp_mode == QUSB_LACKS_ZLP) // No ZLP is expected
      {
        //transfer is complete, return bytes transferred to upper layer immediately 
        if (qusb_al_ctx->rx_cb != NULL)
        {
          qusb_log(AL_BULK_RX_CB_RX_DONE_LOG,0,total_bytes_received);
          qusb_al_ctx->rx_cb(total_bytes_received, BULK_SUCCESS);
          qusb_al_ctx->rx_cb = NULL; // use only once 
          qusb_al_ctx->is_rx_in_progress = FALSE;

          total_bytes_received = 0;
        }
        else // synchronous read 
        {
          qusb_al_ctx->synch_rx_ctx.actual_length = total_bytes_received;
          qusb_al_ctx->synch_rx_ctx.pending_read = FALSE;

          total_bytes_received = 0;
        }
      }
      else
      { 
        // Handle ZLP only when necessary 
        err_code = qusb_al_bulk_handle_rx_zlp_mode();
        if (FD_SUCCESS != err_code) //error condition 
        {
          //error setting up subsequent priming, return error condition immediately 
          if (qusb_al_ctx->rx_cb != NULL)
          {
            qusb_al_ctx->rx_cb(total_bytes_received, BULK_ERR_READ);
            qusb_al_ctx->rx_cb = NULL; /* use only once */
            total_bytes_received = 0;
          }
          else // synchronous read 
          {
            qusb_al_ctx->synch_rx_ctx.actual_length = total_bytes_received;
            qusb_al_ctx->synch_rx_ctx.pending_read = FALSE;
            total_bytes_received = 0;
          }
        }
      }
      // return and let the next iteration handle ZLP 
    }
    else
    {
      if (qusb_al_ctx->rx_cb != NULL)
      {
        qusb_log(AL_BULK_RX_CB_SHORT_PACKET_LOG,0,total_bytes_received);
        qusb_al_ctx->rx_cb(total_bytes_received, err_code);
        qusb_al_ctx->rx_cb = NULL; // use only once 

        qusb_al_ctx->is_rx_in_progress = FALSE;

        total_bytes_received = 0;
      }
      else //synchronous read 
      {
        qusb_al_ctx->synch_rx_ctx.actual_length = total_bytes_received;
        qusb_al_ctx->synch_rx_ctx.pending_read = FALSE;

        total_bytes_received = 0;
      }
    }
  }
  else if(urb->actual_length > urb->transfer_length)
  {
    qusb_log(TRANSFER_ERROR_LOG,0,total_bytes_received);
  }
  else // more data to read 
  {
    uint32 remaining_read_size = urb->transfer_length - urb->actual_length;
    uint32 current_read_size = 0;

    // move the iterator to new destination address 
    uint8 *transfer_buffer_iter = (uint8*)(urb->transfer_buffer_ptr);
    qusb_log(AL_BULK_RX_MORE_DATA_LOG,0,remaining_read_size);

	if (((uint8*)(urb->transfer_buffer_ptr)) == (qusb_al_ctx->non_max_pkt_buffer))
	{
		qusb_error_log(AL_NON_MAX_PKT_BUF_MORE_DATA_ERROR_LOG, 0, urb->transfer_length);
	}

    transfer_buffer_iter += urb->actual_length;

    current_read_size = (remaining_read_size <= qusb_al_bulk_get_max_raw_data_size()) 
        ? remaining_read_size : qusb_al_bulk_get_max_raw_data_size();

    err_code = qusb_fd_rx_pkt((void *)transfer_buffer_iter, current_read_size);
    if (FD_SUCCESS != err_code)
    {
      // error setting up subsequent reads, return error condition immediately
      if (qusb_al_ctx->rx_cb != NULL)
      {
        qusb_al_ctx->rx_cb(total_bytes_received, BULK_SUCCESS);
        qusb_al_ctx->rx_cb = NULL; //use only once 
        total_bytes_received = 0;
        qusb_al_ctx->is_rx_in_progress = FALSE;
      }
      else // synchronous read 
      {
        qusb_al_ctx->synch_rx_ctx.actual_length = total_bytes_received;
        qusb_al_ctx->synch_rx_ctx.pending_read = FALSE;
        total_bytes_received = 0;
      }
    }
    else
    {
      // TODO reset the timer if there is more to read 
      // otherwise let the read proceed 
    }
  }
}

// ===========================================================================
/**
 * @function    qusb_al_bulk_tx_complete
 * 
 * @brief   This function will be a called after each URB transmit is complete.
 *
 * @details This function will be a called after each URB transmit is complete.
 * 
 * @param   *urb   -  [IN/OUT] URB corresponding to the current transmission
 * 
 * @return  None.
 * 
 */
// ===========================================================================
static void qusb_al_bulk_tx_complete(struct qusb_urb* urb)
{

  if (NULL == qusb_al_ctx)
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return;
  }

  //When TX complete happens, urb can't be NULL, so check for NULL status 
  if(NULL == urb)
  {
    qusb_error_log(AL_NULL_POINTER_ERROR_LOG, 0, 0);
  }
  else
  {
    qusb_log(AL_BULK_TX_COMPLETE_LOG,0,urb->transfer_status);
    qusb_al_ctx->tx_urb = urb;
  }
}

// ===========================================================================
/**
 * @function    qusb_al_enum_complete
 * 
 * @brief   This function is registered to be called when enumeration is
 *          complete.
 *
 * @details This function will set a static variable to indicate enumeration has
 *          completed.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
static void qusb_al_enum_complete(boolean enum_flag)
{

  if (NULL == qusb_al_ctx)
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return;
  }

  qusb_log(AL_ENUM_COMPLETE_LOG,0,enum_flag);
  qusb_al_ctx->enumerated = enum_flag;
}

// ===========================================================================
/**
 * @function    qusb_al_disconnect_handler
 * 
 * @brief   This function will be called if there is a disconnect or bus reset
 *			during transfer
 *
 * @details This function will set a static variable to indicate the error.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
static void qusb_al_disconnect_handler(void)
{

  if (NULL == qusb_al_ctx)
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return;
  }

  qusb_al_ctx->is_disconnected = TRUE;
  qusb_al_ctx->enumerated       = FALSE;

  qusb_uart_log("DISCONNECT", 0);
  qusb_log(AL_DISCONNECT_HANDLER_LOG, 0, 0);
  qusb_dci_eud_recovery();
}


//----------------------------------------------------------------------------
// Externalized Function Definitions
//----------------------------------------------------------------------------
// ===========================================================================
/**
 * @function    qusb_al_bulk_init
 * 
 * @brief   This function initializes the USB core and keeps polling until
 *          enumeration is complete.
 *
 * @details This function initializes the USB core and keeps polling until
 *          enumeration is complete.
 * 
 * @param   speed_required   -  [IN] The maximum speed at which USB should be
 *                            configured
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_al_bulk_init(qusb_max_speed_required_t speed_required)
{
  uint32 retry_enum_usb2_speed_cnt = 0;
  qusb_uart_log("init start", 0);
  if (FALSE == qusb_al_ctx_init())
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return;
  }


  if (QUSB_MAX_SPEED_SUPER < speed_required)
  {
    speed_required = QUSB_MAX_SPEED_SUPER;
  }

  // Uncomment to override to High Speed only
  //qusb_uart_log("bulk_init_usb2_override", 0);
  //speed_required = QUSB_MAX_SPEED_HIGH;

  qusb_al_ctx->tx_urb = NULL;
  qusb_al_ctx->enumerated = FALSE;

  qusb_al_ctx->synch_rx_ctx.actual_length = 0;
  qusb_al_ctx->synch_rx_ctx.pending_read = FALSE;

  qusb_log(AL_BULK_INIT_ENTRY_LOG,0,speed_required);

  qusb_al_ctx->dev = qusb_fd_init(qusb_al_bulk_rx_complete,
                                qusb_bulk_str_product,
                                qusb_al_bulk_tx_complete,
                                qusb_al_enum_complete,
                                qusb_al_disconnect_handler,
                                USB_PRODUCT_DIAG_ONLY,
                                speed_required,
                                DCI_SNPS_CORE,
                                FD_CLIENT_SUPPLIED_BUFFER_MODE
                                );
  if (NULL == qusb_al_ctx->dev)
  {
    qusb_error_log(AL_BULK_INIT_EXIT_LOG,0,0);
    return;
  }

#ifndef FEATURE_QUSB_COMP_TEST

  // Start enumeration timeout after VBUS is detected
  // Note that timer assumes that qusb_fd_init() is synchronous API that only returns if the VBUS is detected,
  // otherwise it will internally loop waiting for USB VBUS to go high.
  qusb_timer_start(QUSB_BULK_ENUM_TIMER_VAL_USEC);

  while ( FALSE == qusb_al_ctx->dev->qusb_is_configured )
  {
    if (qusb_timer_check_for_expiry())
    {
      // Enumeration timer has expired. 
      // If Usb is enumerate in SS, we will try one more time in HS.
      if ((qusb_al_ctx->dev->speed >= QUSB_SUPER_SPEED) && (0 == retry_enum_usb2_speed_cnt))
      {
          if (qusb_dci_retry_highspeed())
          {
            qusb_uart_log("enum_timeout, retry in HS", retry_enum_usb2_speed_cnt);
            qusb_timer_start(QUSB_BULK_ENUM_TIMER_VAL_USEC);
          }
          retry_enum_usb2_speed_cnt++;  //This block only will run once
      }
      else
      {
        // Enumeration timer has expired, so return for bulk_transmit to return BULK_ERR_CABLE_DISCONNECT
        qusb_uart_log("enum_tiemout", QUSB_BULK_ENUM_TIMER_VAL_USEC);
        qusb_al_ctx->is_disconnected = TRUE;
        qusb_al_ctx->enum_timeout_flag = TRUE;
      }  
    }
    
    if (TRUE == qusb_al_ctx->is_disconnected)
    {
      qusb_uart_log("Disconnect no enum", 0);
      qusb_log(AL_BULK_INIT_EXIT_LOG,0,0);
      qusb_dci_eud_recovery();
      return;
    }
    
    qusb_al_bulk_poll();
  }
  qusb_al_ctx->enumerated = TRUE;
  qusb_uart_log("ENUM success", 0);

  qusb_log(SNPS_CONTROLLER_ENUM_COMPLETE_LOG,0,0);
  qusb_log(AL_BULK_INIT_EXIT_LOG,0,0);
#else
  while (TRUE)
  {
    if (TRUE == qusb_al_ctx->is_disconnected)
    {
      qusb_al_bulk_shutdown();
      qusb_al_ctx->is_disconnected = FALSE;
      qusb_al_ctx->dev = qusb_fd_init(qusb_al_bulk_rx_complete,
                                    qusb_bulk_str_product,
                                    qusb_al_bulk_tx_complete,
                                    qusb_al_enum_complete,
                                    qusb_al_disconnect_handler,
                                    USB_PRODUCT_DIAG_ONLY,
                                    speed_required,
                                    DCI_SNPS_CORE,
                                    FD_CLIENT_SUPPLIED_BUFFER_MODE);
      if (NULL == qusb_al_ctx->dev)
      {
        qusb_error_log(AL_BULK_INIT_EXIT_LOG,0,0);
        return;
      }
    }
    qusb_al_bulk_poll();
  }

#endif
}

// ===========================================================================
/**
 * @function    qusb_al_bulk_poll
 * 
 * @brief   This function polls the hardware for events.
 *
 * @details This function polls the hardware for events.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_al_bulk_poll(void)
{
  uint32 total_bytes_received = 0x0; 

  if (NULL == qusb_al_ctx)
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return;
  }

  qusb_dcd_poll(qusb_al_ctx->dev);

  //Now polling is controlled by application while we receive the data
  //Now if cable is disconnected in the RX path inform the application
  if (TRUE == qusb_al_ctx->is_disconnected)
  {
    if (TRUE == qusb_al_ctx->is_rx_in_progress)
  {
    //call their callback and tell higher layers of a disconnect
    if (qusb_al_ctx->rx_cb != NULL)
    {
      qusb_al_ctx->rx_cb(total_bytes_received, BULK_ERR_CABLE_DISCONNECT);
      qusb_al_ctx->rx_cb = NULL; /* use only once */
    }
    //Clear all the flags used
    qusb_al_ctx->is_rx_in_progress = FALSE;
    qusb_al_ctx->is_disconnected = FALSE;
  }
    else
    {
      // For TX path, return.
      return;
    }
  }
  //determine whether the host will send the ZLP or timeout
  if(qusb_al_ctx->pending_rx_zlp)
  {
    if(qusb_timer_check_for_expiry())
    {
      //now the timer is stopped and cleared at this point
      //handling the time out now
      switch(qusb_al_ctx->zlp_mode)
      {
        case QUSB_CHECK_FOR_ZLP:
          //even after a time out we didn't get a ZLP
          qusb_al_ctx->zlp_mode= QUSB_LACKS_ZLP; 
          qusb_al_ctx->pending_rx_zlp = FALSE; 
          qusb_al_ctx->waiting_for_zlp = FALSE; 
          qusb_dci_cancel_transfer(0x1,QUSB_EP_DIR_RX);
          break;
        case QUSB_SENDS_ZLP:
          //host times out by then 
          qusb_error_log(ZLP_TIMEOUT_ERROR_LOG, 0, 0); 
          break;
        case QUSB_LACKS_ZLP: 
          //shouldn't come here as pending_rx_zlp would not be set_new_handler
          break; 
        default: 
          break; 
      }
    }
    //allow the polling mechanism to continue as timer has not expired
  }
}
// ===========================================================================
/**
 * @function    qusb_al_bulk_set_shutdown_mode
 * 
 * @brief   This function sets shutdown mode of the hardware.
 *
 * @details This function sets shutdown mode of the hardware.
 * 
 * @param   Shutdown mode.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_al_bulk_set_shutdown_mode(qusb_shutdown_mode_t mode)
{
  qusb_fd_set_shutdown_mode(mode);
}
// ===========================================================================
/**
 * @function    qusb_al_bulk_get_shutdown_mode
 * 
 * @brief   This function reads shutdown mode of the hardware.
 *
 * @details This function reads shutdown mode of the hardware.
 * 
 * @param   None.
 * 
 * @return  Shutdown mode.
 * 
 */
// ===========================================================================
static qusb_shutdown_mode_t  qusb_al_bulk_get_shutdown_mode(void)
{
  return qusb_fd_get_shutdown_mode();
}

// ===========================================================================
/**
 * @function    qusb_al_bulk_shutdown
 * 
 * @brief   This function performs a shutdown of the hardware.
 *
 * @details This function performs a shutdown of the hardware.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_al_bulk_shutdown(void)
{
  qusb_log(AL_BULK_SHUTDOWN_LOG,0,0);
  qusb_uart_log("bulk_shutdown", 0);

  switch(qusb_al_bulk_get_shutdown_mode())
  {
    case QUSB_SINGLE_ENUM_MODE:
    {
      qusb_dci_write_enum_cookie(QUSB_SINGLE_ENUM_COOKIE);
      qusb_fd_shutdown();
    }
    break;

    case QUSB_COMPLETE_SHUTDOWN_MODE:
    default:
      qusb_al_bulk_snps_shutdown();
  }
  if (qusb_al_ctx->enum_timeout_flag)
  {
    qusb_dci_eud_recovery();
    qusb_al_ctx->enum_timeout_flag = FALSE;
  }
  qusb_al_ctx_free();
}
// ===========================================================================
/**
 * @function    qusb_al_bulk_snps_shutdown
 * 
 * @brief   This function performs a shutdown of the SNPS hardware.
 *
 * @details This function performs a shutdown of the SNPS hardware.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_al_bulk_snps_shutdown(void)
{
  qusb_dci_set_run_stop(FALSE);

  //Delay for spoof disconnect( SNPS QUSB - Table 6-62 )
  qusb_dci_delay_ms(30);
  //@TODO we need to check if the shutdown procedure works 
  //shutdown the stack properly
  qusb_dci_deinit_phy();
  qusb_fd_shutdown();
}

// ===========================================================================
/**
 * @function    qusb_al_bulk_receive
 * 
 * @brief   This function receives a bulk of data upto the input length.
 *
 * @details This function will continue to poll the hardware until the receive
 *          URB is not NULL, upon which the data will be copied to the
 *          input receive buffer.
 * 
 * @param   *rx_buf     -  [IN/OUT] Receive buffer for data
 * @param   len         -  [IN    ] Length of buffer
 * @param   rx_cb       -  [IN    ] Return callback function
 * @param   *err_code   -  [IN/OUT] Any error that occurs during transfer
 * 
 * @return  Number of bytes receieved.
 * 
 */
uint32 qusb_al_bulk_receive(byte *rx_buf,   // must be 4 byte aligned       
                              uint32 len,   // read buffer size                             
                              qusb_bulk_rx_cb_type rx_cb, // completion callback 
                              uint32 * err_code)     // error code returned
{
  uint32 current_read_size = 0;

  uint8 *transfer_buffer_iter = (uint8*)(rx_buf);
  uint32 remaining_read_size = len;

  if (NULL == qusb_al_ctx)
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return AL_CTX_NULL_LOG;
  }

  qusb_log(AL_BULK_RECEIVE_LOG,0,len);

  if (err_code == NULL || len == 0)
  {
    return 0;
  }

  if (qusb_al_ctx->waiting_for_zlp) // The ZLP buffer has received data due to host skipping sending ZLP
  {
    qusb_al_ctx->waiting_for_zlp = FALSE; // Clear flag 

    if(len < qusb_al_ctx->cached_zlp_data_length) // If FH layer asks for less than what host sent us instead of the ZLP 
    {
      qusb_al_ctx->cached_zlp_data_length = len;
    }

    qusb_log(AL_BULK_RX_ZLP_COPY_LOG ,0, qusb_al_ctx->cached_zlp_data_length);
    memscpy((void*)(rx_buf), qusb_al_ctx->cached_zlp_data_length, (void*)(qusb_al_ctx->zlp_read_buf), qusb_al_ctx->cached_zlp_data_length);

    if (qusb_al_ctx->cached_zlp_data_length < qusb_al_bulk_get_max_packet_size()) // We received a short packet instead of the ZLP so we are done.
    {
      if(rx_cb)
      {
        qusb_log(AL_BULK_RX_CB_NO_ZLP_BUT_SHORT_PACKET_LOG,0,qusb_al_ctx->cached_zlp_data_length);
        rx_cb(qusb_al_ctx->cached_zlp_data_length, BULK_SUCCESS);
      } 

      qusb_al_ctx->rx_cb = NULL; // use only once 
      qusb_al_ctx->cached_zlp_data_length = 0;
      return 0 ;
    }

    remaining_read_size = len - qusb_al_ctx->cached_zlp_data_length;

    // move the iterator to new destination address 
    transfer_buffer_iter += qusb_al_ctx->cached_zlp_data_length;

    qusb_al_ctx->cached_zlp_data_length = 0;
  }    

  
  qusb_al_ctx->non_max_pkt_transfer_size = remaining_read_size % qusb_al_bulk_get_max_packet_size();
  // Not multiple of max packet size, last date (non max pkt size) will use internal buffer and copy over.
  if (qusb_al_ctx->non_max_pkt_transfer_size)
  {
    //qusb_log(AL_NON_MAX_PKT_BUF_RX_TRANSFER_SIZE_LOG, 0, remaining_read_size);
    //qusb_log(AL_NON_MAX_PKT_BUF_MAX_PKT_SIZE_LOG, 0, qusb_al_bulk_get_max_packet_size());
    //qusb_log(AL_NON_MAX_PKT_BUF_EXTRA_SIZE_LOG, 0, qusb_al_ctx->non_max_pkt_transfer_size);

    remaining_read_size = remaining_read_size - qusb_al_ctx->non_max_pkt_transfer_size;
	// Whole transfer is less than max packet size, submit internal buffer directly
	if (remaining_read_size==0)
	{
		qusb_bus_log(AL_NON_MAX_PKT_BUF_RECIEVE_RX_LOG, 0, qusb_al_ctx->non_max_pkt_transfer_size);
		qusb_al_ctx->client_buffer_iter = transfer_buffer_iter;
		transfer_buffer_iter = qusb_al_ctx->non_max_pkt_buffer;
		remaining_read_size = qusb_al_bulk_get_max_packet_size();
	}
  }

  //enforce read only upto qusb_al_bulk_get_max_raw_data_size( ) 
  current_read_size = ((remaining_read_size <= qusb_al_bulk_get_max_raw_data_size()) ?
  remaining_read_size : qusb_al_bulk_get_max_raw_data_size());

  //setup read 

  qusb_log(AL_BULK_RECEIVE_LOG,0,current_read_size);
  *err_code = qusb_fd_rx_pkt((void *)transfer_buffer_iter, current_read_size);

  if (FD_SUCCESS != *err_code)
  {
    return 0; // error condition 
  }

  if (rx_cb == NULL)
  {
    //Synchronous read when client does not pass callback.
    // Poll in USB layer until completion 

    // safe to set flag here on the assumption that there is no polling in between packet setup and here 
    qusb_al_ctx->synch_rx_ctx.pending_read = TRUE;
    while (qusb_al_ctx->synch_rx_ctx.pending_read)
    {
      qusb_al_bulk_poll();
    }
    return qusb_al_ctx->synch_rx_ctx.actual_length;
  }
  else
  {
    //client layer will perform the polling 
    // transfer completes when client's cb is invoked 
    qusb_al_ctx->rx_cb = rx_cb;
    qusb_al_ctx->is_rx_in_progress = TRUE;
    *err_code = BULK_SUCCESS;
    return 0;
  }
}

// ===========================================================================
/**
 * @function    qusb_al_bulk_transmit
 * 
 * @brief   This function receives a bulk of data upto the input length.
 *
 * @details This function will continue to poll the hardware until the transmit
 *          URB transfer is complete.
 * 
 * @param   *tx_buf     -  [IN/OUT] Transmit buffer for data
 * @param   len         -  [IN    ] Length of data to trasmit in bytes
 * @param   tx_cb       -  [IN    ] Transmit complete callback
 * @param   *err_code   -  [IN/OUT] Any error that occurs during transfer
 * 
 * @return  Number of bytes transmitted.
 * 
 */
uint32 qusb_al_bulk_transmit(byte *tx_buf,        // must be 4 byte aligned   
                               uint32 len,        // number of bytes to send  
                               qusb_bulk_tx_cb_type tx_cb, // completion callback 
                               uint32 * err_code)     // returned error code 
{
  uint32 tx_length;
  *err_code = BULK_SUCCESS;
  if (NULL == qusb_al_ctx)
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return AL_CTX_NULL_LOG;
  }

  qusb_log(AL_BULK_TRANSMIT_LOG,0,(uint32)(uintptr_t)tx_buf);
  qusb_log(TRANSFER_LENGTH_LOG,0,len);

  if (FALSE == qusb_al_ctx->is_disconnected)
  {
    // Check for enumeration to complete before submission ( to cater disconnect usecase ) 
    while ( !qusb_al_ctx->enumerated )
    {
      qusb_al_bulk_poll();
    }
    qusb_fd_tx_pkt(tx_buf, len);
  }

  while (qusb_al_ctx->tx_urb == NULL)
  {  
    if(TRUE == qusb_al_ctx->is_disconnected)
    {
      qusb_al_ctx->is_disconnected = FALSE;
      *err_code = BULK_ERR_CABLE_DISCONNECT;
      //Doesn't really matter how much was transferred, in anycase sahara has to begin 
      //again
      tx_length = 0x0; 
      if ( tx_cb != NULL )
      {
        tx_cb(tx_length, *err_code);
      }
      qusb_fd_shutdown();
      return tx_length;
    }
    qusb_al_bulk_poll();
  }
  tx_length = qusb_al_ctx->tx_urb->actual_length;
  if ( qusb_al_ctx->tx_urb->transfer_status == QUSB_URB_STATUS_COMPLETE_OK )
  {
    qusb_al_ctx->tx_urb = NULL;
  }
  else
  {
    qusb_log(AL_BULK_ERR_WRITE_LOG,0,0);
    qusb_al_ctx->tx_urb = NULL;
    *err_code = BULK_ERR_WRITE;

    // Override to disconnected status for better error handling     
    if(TRUE == qusb_al_ctx->is_disconnected)     
    {     
      qusb_al_ctx->is_disconnected = FALSE;           
      *err_code = BULK_ERR_CABLE_DISCONNECT;           
      tx_length = 0x0;      
    }     
    qusb_dci_delay_ms(1000); 

  }

  if ( tx_cb != NULL )
  {
    tx_cb(tx_length, *err_code);
  }
  return tx_length;
}

// ===========================================================================
/**
 * @function    qusb_al_bulk_get_max_packet_size
 * 
 * @brief   This function returns whether USB spec defined max packet sizes
 *          for FS USB or HS USB
 *
 * @details Correct packet sizes are determined internally and will be
 *          returned to external interface
 *          
 * @return  Max packet sizes
 * 
 */
uint32 qusb_al_bulk_get_max_packet_size(void)
{
  if (NULL == qusb_al_ctx)
  {
    qusb_error_log(AL_CTX_NULL_LOG, 0, __LINE__);
    return AL_CTX_NULL_LOG;
  }

  if(NULL != qusb_al_ctx->dev )
  {
    if ((qusb_al_ctx->dev->speed == QUSB_SUPER_SPEED) || (qusb_al_ctx->dev->speed == QUSB_SUPER_SPEED_PLUS))
    {
      return QUSB_MAX_PKT_SIZE_SUPER; 
    }
    else
    {
      return QUSB_MAX_PKT_SIZE_HIGH; 
    }

  }
  return QUSB_MAX_PKT_SIZE_HIGH;
}

// ===========================================================================
/**
 * @function    qusb_al_bulk_get_max_raw_data_size
 * 
 * @brief   Returns the maximum bulk transfer level size that can be requested
 *          by the client
 *
 * @details Windows only support maximum bulk transfer size of 1MB, whereas
 *          Linux supports a larger maximum 
 *          
 * @return  Max USB bulk transfer level size
 * 
 */
uint32 qusb_al_bulk_get_max_raw_data_size(void)
{
  //Maximum bulk transfer size
  return QUSB_BULK_LAYER_MAX_TRANSFER_SIZE_IN_BYTES;
}

