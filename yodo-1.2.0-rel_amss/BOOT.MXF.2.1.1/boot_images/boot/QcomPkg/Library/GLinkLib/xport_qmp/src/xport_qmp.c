/*===========================================================================

              QMP native transport for Glink Driver Source File


   Copyright (c) 2016 - 2018, 2020 Qualcomm Technologies, Inc.
   All Rights Reserved.
   Qualcomm Technologies, Inc. Confidential and Proprietary.
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/04/17   mad      Added validity checks for local and remote mailbox addresses 
                    and local mailbox size
08/17/16   dks      Initial version.
===========================================================================*/


/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "smem_list.h"
#include "glink.h"
#include "glink_core_if.h"
#include "glink_transport_if.h"
#include "glink_os_utils.h"
#include "glink_internal.h"
#include "glink_vector.h"
#include "xport_qmp_config.h"
#include "xport_qmp.h"
#include "smem.h"
//#include "glink_tracer.h"
//#include "glink_tracer_internal.h"
#include "DalDevice.h"

extern const uint32 xport_qmp_num_configs;

#if XPORT_QMP_DEBUG_ENABLED
DalDeviceHandle* glink_device_handle;

/*end debug*/

typedef enum
{
XPORT_QMP_DEBUG_ISR_START,
XPORT_QMP_DEBUG_ISR_END,
XPORT_QMP_DEBUG_PROCESS_RX_DATA_START,
XPORT_QMP_DEBUG_PROCESS_RX_DATA_END,
XPORT_QMP_DEBUG_ALLOCATE_RX_INTENT,
XPORT_QMP_DEBUG_TX_CMD_LOCAL_RX_INTENT,
XPORT_QMP_DEBUG_SET_UP_MASTER_MAILBOX_INT_SEND,
XPORT_QMP_DEBUG_LINK_NEGOTIATION,
XPORT_QMP_DEBUG_LINK_NEGOTIATION_INT_SEND,
XPORT_QMP_DEBUG_LINK_UP_ENTER,
XPORT_QMP_DEBUG_LINK_UP_INT_SEND,
XPORT_QMP_DEBUG_GLINK_OPEN,
XPORT_QMP_DEBUG_GLINK_OPEN_INT_SEND,
XPORT_QMP_DEBUG_LOCAL_CONNECTING,
XPORT_QMP_DEBUG_LOCAL_CONNECTING_INT_SEND,
XPORT_QMP_DEBUG_LOCAL_CONNECTING_RX_CMD_REMOTE_OPEN, 
XPORT_QMP_DEBUG_LOCAL_CONNECTED, 
XPORT_QMP_DEBUG_LOCAL_CONNECTED_INT_SEND,
XPORT_QMP_DEBUG_E2ECONNECTED,
XPORT_QMP_DEBUG_E2ECONNECTED_INT_SEND,
XPORT_QMP_DEBUG_GLINK_CLOSE,
XPORT_QMP_DEBUG_GLINK_CLOSE_INT_SEND,
XPORT_QMP_DEBUG_LOCAL_DISCONNECTING,
XPORT_QMP_DEBUG_LOCAL_DISCONNECTING_INT_SEND,
XPORT_QMP_DEBUG_TX,
XPORT_QMP_DEBUG_TX_INT_SEND,
XPORT_QMP_DEBUG_RX_DONE,
XPORT_QMP_DEBUG_RX_DONE_INT_SEND,
XPORT_QMP_DEBUG_TX_CMD_CH_OPEN,
XPORT_QMP_DEBUG_TX_CMD_CH_OPEN_INT_SEND,
XPORT_QMP_DEBUG_TX_CMD_CH_CLOSE,
XPORT_QMP_DEBUG_TX_CMD_CH_CLOSE_INT_SEND,
XPORT_QMP_DEBUG_TX_CMD_CH_REMOTE_OPEN_ACK,
XPORT_QMP_DEBUG_TX_CMD_CH_REMOTE_OPEN_ACK_INT_SEND,
XPORT_QMP_DEBUG_TX_CMD_CH_REMOTE_CLOSE_ACK,
XPORT_QMP_DEBUG_TX_CMD_CH_REMOTE_CLOSE_ACK_INT_SEND,
XPORT_QMP_DEBUG_TX_CMD_LOCAL_RX_DONE,
XPORT_QMP_DEBUG_TX_CMD_LOCAL_RX_DONE_INT_SEND,
XPORT_QMP_CHECK_LINK,
XPORT_QMP_CHECK_LINK_INT_SEND,
XPORT_QMP_DEBUG_TX_VERSION_START,
XPORT_QMP_DEBUG_TX_VERSION_END

}xport_qmp_debug_event;

typedef struct 
{
  xport_qmp_debug_event event;
  uint8 state;
  uint32 local_ch_link_state;
  uint32 local_ch_link_state_ack;
  uint32 remote_ch_link_state;
  uint32 remote_ch_link_state_ack;
  uint32 local_ch_state;
  uint32 local_ch_state_ack;
  uint32 remote_ch_state;
  uint32 remote_ch_state_ack;
  uint64 ts; 
}xport_qmp_debug_type;

#define MAX_XPORT_QMP_CNTR 30
static volatile xport_qmp_debug_type xport_qmp_debug[MAX_XPORT_QMP_CNTR];
static uint32 xport_qmp_debug_cntr = 0;
static os_cs_type *xport_qmp_debug_lock;

void xport_debug_log(xport_qmp_ctx_type *ctx_ptr, xport_qmp_debug_event event, uint8 state)
{
    glink_os_cs_acquire(xport_qmp_debug_lock);

    xport_qmp_debug[xport_qmp_debug_cntr].event = event;  
    xport_qmp_debug[xport_qmp_debug_cntr].state = state;
    xport_qmp_debug[xport_qmp_debug_cntr].local_ch_link_state = ctx_ptr->local_ch_desc->link_state;
    xport_qmp_debug[xport_qmp_debug_cntr].local_ch_link_state_ack = ctx_ptr->local_ch_desc->link_state_ack;
    xport_qmp_debug[xport_qmp_debug_cntr].remote_ch_link_state = ctx_ptr->remote_ch_desc->link_state;
    xport_qmp_debug[xport_qmp_debug_cntr].remote_ch_link_state_ack = ctx_ptr->remote_ch_desc->link_state_ack;
    xport_qmp_debug[xport_qmp_debug_cntr].local_ch_state = ctx_ptr->local_ch_desc->ch_state;
    xport_qmp_debug[xport_qmp_debug_cntr].local_ch_state_ack = ctx_ptr->local_ch_desc->ch_state_ack;
    xport_qmp_debug[xport_qmp_debug_cntr].remote_ch_state = ctx_ptr->remote_ch_desc->ch_state;
    xport_qmp_debug[xport_qmp_debug_cntr].remote_ch_state_ack = ctx_ptr->remote_ch_desc->ch_state_ack;
    DalTimetick_GetTimetick64(glink_device_handle, (unsigned long long*)&xport_qmp_debug[xport_qmp_debug_cntr].ts);
    xport_qmp_debug_cntr = (xport_qmp_debug_cntr+1)%MAX_XPORT_QMP_CNTR;

    glink_os_cs_release(xport_qmp_debug_lock);
}
#endif
/*===========================================================================
                           MACRO DEFINITIONS
===========================================================================*/
#define XPORT_QMP_NAME "qmp"
#define XPORT_QMP_MAILBOX_MAGIC 0x4d41494c /* MAIL */
#define XPORT_QMP_VERSION 1
#define XPORT_QMP_FEATURES 0x0
#define XPORT_QMP_RCID 0xCD


#define XPORT_QMP_LINK_DOWN 0xFFFF0000
#define XPORT_QMP_LINK_UP 0x0000FFFF

#define XPORT_QMP_CH_DISCONNECTED 0xFFFF0000
#define XPORT_QMP_CH_CONNECTED 0x0000FFFF

typedef enum _xport_qmp_local_state{
  LINK_DOWN, // Before init
  LINK_NEGOTIATION, //Fifo setup, INT Sent
  LINK_UP, //remote acked link up
  LOCAL_CONNECTING, //local connected, INT sent
  LOCAL_CONNECTED, //remote acked local connected
  E2ECONNECTED, //local connected acked by reomote and remote connected acked by local
  LOCAL_DISCONNECTING, //local disconnected
}xport_qmp_local_state;

/*Check for xport logging filter mask bit and edge before logging*/
#define XPORT_QMP_LOG_MSG(host_id, msg, remote_host_name, param)                                  \
  if (((log_filter_cfg.xport_filter_mask &                                   \
        (1<<GLINK_XPORT_QMP_MASK_BIT)) != 0) &&                             \
       ((log_filter_cfg.ch_filter_status == FALSE) ||                        \
        ((uint32)(uintptr_t)host_id == log_filter_cfg.remote_host)))                    \
  {                                                                          \
    GLINK_LOG_EVENT_NO_FILTER( GLINK_EVENT_XPORT_INTERNAL, msg,              \
                               XPORT_QMP_NAME, remote_host_name,            \
                               (uint32)param);                               \
  }

#define XPORT_QMP_LOG_ERROR(msg, remote_host_name, param)                \
  GLINK_LOG_ERROR_EVENT(GLINK_EVENT_XPORT_INTERNAL, msg, XPORT_QMP_NAME, \
			            remote_host_name, (uint32)param);

#define ROUNDUP64(d) ((d + 7) & (~7))

#define XPORT_QMP_READ_BACK(addr) \
  do { \
    volatile uint32 read_back = *((uint32 *)(addr)); \
    read_back = read_back; \
  } while(0)

/*===========================================================================
                              GLOBAL DATA DECLARATIONS
===========================================================================*/
smem_host_type xport_qmp_this_host = SMEM_APPS;

extern const uint32 xport_qmp_config_num;
static xport_qmp_ctx_type *xport_qmp_ctx = NULL;
static glink_core_version_type *xport_qmp_version = NULL;


/*===========================================================================
FUNCTION      xport_qmp_process_rx_data
===========================================================================*/
/**

  read a data packet or a fragment of it and notifies core

  @param[in]  ctx_ptr            Pointer to smem xport context
  @param[in]  cmd                command received
  @param[in]  rx_ind             rx index of fifo
  @param[in]  log_tracer_packet  tells you whether to log tracer packek event

  @return     Returns error code.

  @sideeffects  None.

  @dependencies None.
*/
/*=========================================================================*/
static void xport_qmp_process_rx_data
(
  xport_qmp_ctx_type     *ctx_ptr,
  size_t                  read_len
)
{
  glink_rx_intent_type* pdesc;

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_PROCESS_RX_DATA_START,ctx_ptr->current_state);
  #endif

  pdesc = ctx_ptr->xport_if.glink_core_if_ptr->rx_get_pkt_ctx(
    (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID, 0);

  pdesc->used = ctx_ptr->remote_mailbox->msg_len;
  pdesc->pkt_sz = ctx_ptr->remote_mailbox->msg_len;

  ctx_ptr->xport_if.glink_core_if_ptr->rx_put_pkt_ctx(
    (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID, pdesc, TRUE);

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_PROCESS_RX_DATA_END, ctx_ptr->current_state);
  #endif
} 

/************************ BASE FEATURE Functions ************************
 * These functions are base feature functions ( 0 )  
 */
 
/*===========================================================================
FUNCTION      xport_qmp_tx_cmd_version
===========================================================================*/
/**

  Transmit a version command for local negotiation - 
  expected response is to be delivered via glink_rx_cmd_version_ack().

  @param[in]  if_ptr    Pointer to transport interface instance.
  @param[in]  version   Version to be sent.
  @param[in]  feature   Features to be sent.

  @return     None.

  @sideeffects  None.
*/
/*=========================================================================*/
void xport_qmp_tx_cmd_version
(
  glink_transport_if_type *if_ptr,
  uint32 version,
  uint32 features
)
{
  xport_qmp_ctx_type *ctx_ptr = (xport_qmp_ctx_type *)if_ptr;
  glink_os_cs_acquire(&ctx_ptr->rx_link_lock);
  glink_os_cs_acquire(&ctx_ptr->tx_link_lock);

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_VERSION_START, ctx_ptr->current_state);
  #endif
  ctx_ptr->local_ch_desc->link_state = XPORT_QMP_LINK_UP;
  ctx_ptr->local_ch_desc->ch_state = XPORT_QMP_CH_DISCONNECTED;
  ctx_ptr->local_mailbox->msg_len = 0;
  ctx_ptr->current_state = LINK_NEGOTIATION;

  /* ACK remote state */
  ctx_ptr->remote_ch_desc->link_state_ack =
           ctx_ptr->remote_ch_desc->link_state;
  ctx_ptr->remote_ch_desc->ch_state_ack = ctx_ptr->remote_ch_desc->ch_state;
  
  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_VERSION_END, ctx_ptr->current_state);
  #endif

  glink_os_cs_release(&ctx_ptr->tx_link_lock);
  glink_os_cs_release(&ctx_ptr->rx_link_lock);
}

/*===========================================================================
FUNCTION      xport_qmp_tx_cmd_version_ack
===========================================================================*/
/**

  Transmit a version ack for remote negotiation.

  @param[in]  if_ptr    Pointer to transport interface instance.
  @param[in]  version   Version to be sent.
  @param[in]  feature   Features to be sent.

  @return     None.

  @sideeffects  None.
*/
/*=========================================================================*/
void xport_qmp_tx_cmd_version_ack
(
  glink_transport_if_type *if_ptr,
  uint32 version,
  uint32 features
)
{
  xport_qmp_ctx_type *ctx_ptr = (xport_qmp_ctx_type *)if_ptr;

  if (version != ctx_ptr->ch_desc->core_version)
  {
    XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Mailbox version mismatch",ctx_ptr->pcfg->remote_ss, ctx_ptr->ch_desc->core_version);
    ASSERT (version == ctx_ptr->ch_desc->core_version);
  }
  if (features != ctx_ptr->ch_desc->core_features)
  {
    XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Mailbox features mismatch",ctx_ptr->pcfg->remote_ss, ctx_ptr->ch_desc->core_features);
    ASSERT (features == ctx_ptr->ch_desc->core_features);
  }
}


/*===========================================================================
FUNCTION      xport_qmp_tx_cmd_ch_open
===========================================================================*/
/**

  Sends the open command - expected response is to be delivered 
  via glink_rx_cmd_ch_open_ack().

  @param[in]  if_ptr   Pointer to transport interface instance.
  @param[in]  lcid     Local channel ID.
  @param[in]  name     Channel name.
  @param[in]  prio     xport priority requested by channel

  @return     Returns error code.

  @sideeffects  None.
*/
/*=========================================================================*/
glink_err_type xport_qmp_tx_cmd_ch_open
(
  glink_transport_if_type *if_ptr,
  uint32 lcid,
  const char *name,
  glink_xport_priority prio
)
{
  xport_qmp_ctx_type *ctx_ptr = (xport_qmp_ctx_type *)if_ptr;

  glink_os_cs_acquire(&ctx_ptr->rx_link_lock);
  glink_os_cs_acquire(&ctx_ptr->tx_link_lock);

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_CMD_CH_OPEN, ctx_ptr->current_state);
  #endif
  if (ctx_ptr->current_state != LINK_UP)
  {
    XPORT_QMP_LOG_ERROR("Open when ch state %d", ctx_ptr->pcfg->remote_ss,
                         ctx_ptr->current_state);
    glink_os_cs_release(&ctx_ptr->tx_link_lock);
    glink_os_cs_release(&ctx_ptr->rx_link_lock);
    return GLINK_STATUS_OUT_OF_RESOURCES;
  }
  if (glink_os_string_compare(ctx_ptr->pcfg->ch_name,name) != 0)
  {
    XPORT_QMP_LOG_ERROR("Open ch_name mismatch", ctx_ptr->pcfg->remote_ss, 0);
    glink_os_cs_release(&ctx_ptr->tx_link_lock);
    glink_os_cs_release(&ctx_ptr->rx_link_lock);
    return GLINK_STATUS_INVALID_PARAM;
  }

  ctx_ptr->lcid = lcid;

  ctx_ptr->local_ch_desc->ch_state = XPORT_QMP_CH_CONNECTED;
  ctx_ptr->current_state = LOCAL_CONNECTING;

  glink_os_send_interrupt((os_ipc_intr_type *)&ctx_ptr->pcfg->irq);
  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_CMD_CH_OPEN_INT_SEND, ctx_ptr->current_state);
  #endif

  glink_os_cs_release(&ctx_ptr->tx_link_lock);
  glink_os_cs_release(&ctx_ptr->rx_link_lock);

  return GLINK_STATUS_SUCCESS;
}

/*===========================================================================
FUNCTION      xport_qmp_tx_cmd_ch_close
===========================================================================*/
/**

  Sends the close command - expected response is to be delivered 
  via glink_rx_cmd_ch_close_ack().

  @param[in]  if_ptr   Pointer to transport interface instance.
  @param[in]  lcid     Local channel ID.

  @return     Returns error code.

  @sideeffects  None.
*/
/*=========================================================================*/
glink_err_type xport_qmp_tx_cmd_ch_close
(
  glink_transport_if_type *if_ptr,
  uint32 lcid
)
{
  xport_qmp_ctx_type *ctx_ptr = (xport_qmp_ctx_type *)if_ptr;

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_CMD_CH_CLOSE, ctx_ptr->current_state);
  #endif
  //glink_os_cs_acquire(ctx_ptr->rx_link_lock);
  glink_os_cs_acquire(&ctx_ptr->tx_link_lock);
  
  if (ctx_ptr->current_state != LOCAL_CONNECTED &&
      ctx_ptr->current_state != E2ECONNECTED)
  {
    XPORT_QMP_LOG_ERROR("Close when ch state %d", ctx_ptr->pcfg->remote_ss,
                         ctx_ptr->current_state);
    glink_os_cs_release(&ctx_ptr->tx_link_lock);
    //glink_os_cs_release(ctx_ptr->rx_link_lock);
    return GLINK_STATUS_OUT_OF_RESOURCES;
  }

  ASSERT (lcid == ctx_ptr->lcid);

  ctx_ptr->local_ch_desc->ch_state = XPORT_QMP_CH_DISCONNECTED;
  ctx_ptr->current_state = LOCAL_DISCONNECTING;

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_CMD_CH_CLOSE_INT_SEND, ctx_ptr->current_state);
  #endif
  glink_os_send_interrupt((os_ipc_intr_type *)&ctx_ptr->pcfg->irq);

  glink_os_cs_release(&ctx_ptr->tx_link_lock);
  //glink_os_cs_release(ctx_ptr->rx_link_lock);

  return GLINK_STATUS_SUCCESS;
}

/*===========================================================================
FUNCTION      xport_qmp_tx_cmd_ch_remote_open_ack
===========================================================================*/
/**

  Sends the remote open ACK command.

  @param[in]  if_ptr   Pointer to transport interface instance.
  @param[in]  rcid     Remote channel ID.
  @param[in]  prio     Negotiated xport priority to be sent to remote side

  @return     None.

  @sideeffects  None.
*/
/*=========================================================================*/
void xport_qmp_tx_cmd_ch_remote_open_ack
(
  glink_transport_if_type *if_ptr,
  uint32 rcid,
  glink_xport_priority prio
)
{
  xport_qmp_ctx_type *ctx_ptr = (xport_qmp_ctx_type *)if_ptr;

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_CMD_CH_REMOTE_OPEN_ACK, ctx_ptr->current_state);
  #endif

  glink_os_cs_acquire(&ctx_ptr->rx_link_lock);
  glink_os_cs_acquire(&ctx_ptr->tx_link_lock);

  ASSERT (rcid == XPORT_QMP_RCID);

  ctx_ptr->remote_ch_desc->ch_state_ack = XPORT_QMP_CH_CONNECTED;

  glink_os_send_interrupt((os_ipc_intr_type *)&ctx_ptr->pcfg->irq);
  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_CMD_CH_REMOTE_OPEN_ACK_INT_SEND, ctx_ptr->current_state);
  #endif

  glink_os_cs_release(&ctx_ptr->tx_link_lock);
  glink_os_cs_release(&ctx_ptr->rx_link_lock);
}

/*===========================================================================
FUNCTION      xport_qmp_tx_cmd_ch_remote_close_ack
===========================================================================*/
/**

  Sends the remote close ACK command.

  @param[in]  if_ptr   Pointer to transport interface instance.
  @param[in]  rcid     Remote channel ID.

  @return     None.

  @sideeffects  None.
*/
/*=========================================================================*/
void xport_qmp_tx_cmd_ch_remote_close_ack
(
  glink_transport_if_type *if_ptr,
  uint32 rcid
)
{
  xport_qmp_ctx_type *ctx_ptr = (xport_qmp_ctx_type *)if_ptr;

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_CMD_CH_REMOTE_CLOSE_ACK, ctx_ptr->current_state);
  #endif

  glink_os_cs_acquire(&ctx_ptr->rx_link_lock);
  glink_os_cs_acquire(&ctx_ptr->tx_link_lock);

  ASSERT (rcid == XPORT_QMP_RCID);

  ctx_ptr->remote_ch_desc->ch_state_ack = XPORT_QMP_CH_DISCONNECTED;

  glink_os_send_interrupt((os_ipc_intr_type *)&ctx_ptr->pcfg->irq);
  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_CMD_CH_REMOTE_CLOSE_ACK_INT_SEND, ctx_ptr->current_state);
  #endif

  glink_os_cs_release(&ctx_ptr->tx_link_lock);
  glink_os_cs_release(&ctx_ptr->rx_link_lock);
}


/*===========================================================================
FUNCTION      xport_qmp_tx_cmd_rx_intent_req
===========================================================================*/
/**

  Sends the intent request command.

  @param[in]  if_ptr   Pointer to transport interface instance.
  @param[in]  lcid     Local channel ID.
  @param[in]  size     size of requested intent.

  @return     Returns error code.

  @sideeffects  None.
*/
/*=========================================================================*/
glink_err_type xport_qmp_tx_cmd_rx_intent_req
(
  glink_transport_if_type *if_ptr,
  uint32 lcid,
  size_t size
)
{
  xport_qmp_ctx_type *ctx_ptr = (xport_qmp_ctx_type *)if_ptr;
  glink_err_type result;

  //glink_os_cs_acquire(ctx_ptr->rx_link_lock);
  glink_os_cs_acquire(&ctx_ptr->tx_link_lock);

  if (ctx_ptr->tx_pending_count == ctx_ptr->pcfg->max_tx_pending_items ||
      size > ctx_ptr->local_mailbox_size)
  {
    result = GLINK_STATUS_NO_REMOTE_INTENT_FOUND;
    glink_os_cs_release(&ctx_ptr->tx_link_lock);
  }
  else
  {
    ctx_ptr->free_iid++;
    glink_os_cs_release(&ctx_ptr->tx_link_lock);
    ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_remote_rx_intent_put(
      (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID,
      ctx_ptr->free_iid, ctx_ptr->local_mailbox_size);

    result = GLINK_STATUS_SUCCESS;
  }

  //glink_os_cs_release(ctx_ptr->tx_link_lock);
  //glink_os_cs_release(ctx_ptr->rx_link_lock);

  return result;
}


/*===========================================================================
FUNCTION      xport_qmp_tx_cmd_local_rx_done
===========================================================================*/
/**

  Send receive-done command.

  @param[in]  if_ptr   Pointer to transport interface instance.
  @param[in]  lcid     Local channel ID.
  @param[in]  liid     Local intent ID.
  @param[in]  reuse    Reuse intent.

  @return     None.

  @sideeffects  None.
*/
/*=========================================================================*/
void xport_qmp_tx_cmd_local_rx_done
(
  glink_transport_if_type *if_ptr,
  uint32 lcid,
  uint32 liid,
  boolean reuse
)
{
  xport_qmp_ctx_type *ctx_ptr = (xport_qmp_ctx_type *)if_ptr;

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_CMD_LOCAL_RX_DONE, ctx_ptr->current_state);
  #endif
  glink_os_cs_acquire(&ctx_ptr->rx_link_lock);
  glink_os_cs_acquire(&ctx_ptr->tx_link_lock);

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_RX_DONE, ctx_ptr->current_state);
  #endif

  ctx_ptr->receiving = FALSE;
  ctx_ptr->remote_mailbox->msg_len = 0;
  XPORT_QMP_READ_BACK(&ctx_ptr->remote_mailbox->msg_len);
 
  glink_os_send_interrupt((os_ipc_intr_type *)&ctx_ptr->pcfg->irq);
  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_CMD_LOCAL_RX_DONE_INT_SEND, ctx_ptr->current_state);
  #endif
  
  glink_os_cs_release(&ctx_ptr->tx_link_lock);
  glink_os_cs_release(&ctx_ptr->rx_link_lock);
}


/*===========================================================================
FUNCTION      xport_qmp_allocate_rx_intent
===========================================================================*/
/**

  Allocates a receive buffer for the local rx intent.

  @param[in]  if_ptr        Pointer to transport interface.
  @param[in]  size          Size of Rx intent.
  @param[in]  intent_ptr    intent pointer to be filled with allocated vector.

  @return     Returns error code.

  @sideeffects  None.

  @dependencies None.
*/
/*=========================================================================*/
glink_err_type xport_qmp_allocate_rx_intent(
  glink_transport_if_type *if_ptr,    
  size_t                  size,       
  glink_rx_intent_type    *intent_ptr
)
{
  glink_iovector_type* iovec;
  xport_qmp_ctx_type *ctx_ptr = (xport_qmp_ctx_type *)if_ptr;

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_ALLOCATE_RX_INTENT, ctx_ptr->current_state);
  #endif

  iovec = (glink_iovector_type*)glink_os_malloc(sizeof(glink_iovector_type) + 
                                  sizeof(glink_iovector_element_type));

  if (iovec == NULL)
  {
    return GLINK_STATUS_OUT_OF_RESOURCES;
  }

  iovec->vlist = (glink_iovector_element_type*)(iovec + 1);
  iovec->vlist->next = NULL;
  iovec->vlast = NULL;
  iovec->vlist->data = (void*)(ctx_ptr->remote_mailbox->msg);
  iovec->vlist->start_offset = 0;
  iovec->vlist->size = ctx_ptr->local_mailbox_size;
  iovec->plist = NULL;
  iovec->plast = NULL;

  intent_ptr->iovec = iovec;
  intent_ptr->vprovider = &glink_iovec_vprovider;
  intent_ptr->pprovider = &glink_iovec_pprovider;

  return GLINK_STATUS_SUCCESS;
}


/*===========================================================================
FUNCTION      xport_qmp_deallocate_rx_intent
===========================================================================*/
/**

  Deallocates a receive buffer for the local rx intent.

  @param[in]  if_ptr        Pointer to transport interface.
  @param[in]  intent_ptr    intent pointer with allocated vector to be freed.

  @return     Returns error code.

  @sideeffects  None.

  @dependencies None.
*/
/*=========================================================================*/
glink_err_type xport_qmp_deallocate_rx_intent(
  glink_transport_if_type *if_ptr,    
  glink_rx_intent_type    *intent_ptr
)
{
  glink_os_free(intent_ptr->iovec);

  return GLINK_STATUS_SUCCESS;
}


/*===========================================================================
FUNCTION      xport_qmp_write_msg
===========================================================================*/
/**

  Copies data from local buffer to mailbox memory 

  @param[in]  ctx_ptr   Pointer to transport context.
  @param[in]  pctx       packet context whose data we need to copy

  @sideeffects  None.

  @dependencies It should be invoked within tx_link_lock protection.
*/
/*=========================================================================*/
static void xport_qmp_write_msg
(
  xport_qmp_ctx_type *ctx_ptr,
  glink_core_tx_pkt_type *pctx
)
{
  uint32 *buffer;
  uint32 *buffer_end;
  volatile uint32 *write_ptr;
  buffer = (uint32*)pctx->data;
  buffer_end = (uint32*)((char*)pctx->data + pctx->size_remaining);
  write_ptr = (volatile uint32*)ctx_ptr->local_mailbox->msg;

  while (buffer < buffer_end)
  {
    *write_ptr++ = *buffer++;
  }

  ctx_ptr->local_mailbox->msg_len = pctx->size_remaining;
  XPORT_QMP_READ_BACK(&ctx_ptr->local_mailbox->msg_len);

  pctx->size_remaining = 0;
}


/*===========================================================================
FUNCTION      xport_qmp_tx
===========================================================================*/
/**

  Send a data packet or a fragment of it.

  @param[in]  if_ptr   Pointer to transport interface instance.
  @param[in]  lcid     Local channel ID.
  @param[in]  pctx     Packet TX context.

  @return     Returns error code.

  @sideeffects  None.
*/
/*=========================================================================*/
glink_err_type xport_qmp_tx
(
  glink_transport_if_type *if_ptr,
  uint32 lcid,
  glink_core_tx_pkt_type *pctx
)
{
  xport_qmp_ctx_type *ctx_ptr = (xport_qmp_ctx_type *)if_ptr;

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX, ctx_ptr->current_state);
  #endif

  //glink_os_cs_acquire(ctx_ptr->rx_link_lock);
  glink_os_cs_acquire(&ctx_ptr->tx_link_lock);
  
  if (ctx_ptr->transmitting == FALSE)
  {
    ctx_ptr->transmitting = TRUE;
    ctx_ptr->current_in_transmit_intent_iid = pctx->iid;

    glink_os_cs_acquire(&ctx_ptr->tx_list_lock);   
    /* Doing the next tx now */
    if (ctx_ptr->tx_pending_count)
    {
      ctx_ptr->tx_pending_count--;
    }
    glink_os_cs_release(&ctx_ptr->tx_list_lock);

    xport_qmp_write_msg(ctx_ptr, pctx);
    glink_os_send_interrupt((os_ipc_intr_type *)&ctx_ptr->pcfg->irq);
	#if XPORT_QMP_DEBUG_ENABLED
    xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_INT_SEND, ctx_ptr->current_state);
	#endif
  }
  else
  {
    glink_os_cs_acquire(&ctx_ptr->tx_list_lock);   
    ctx_ptr->tx_pending_count++;
    glink_os_cs_release(&ctx_ptr->tx_list_lock);
  }

  glink_os_cs_release(&ctx_ptr->tx_link_lock);
  //glink_os_cs_release(ctx_ptr->rx_link_lock);

  return GLINK_STATUS_SUCCESS;  
}


/*===========================================================================
FUNCTION      xport_qmp_tx_cmd_local_rx_intent
===========================================================================*/
/**

  Send receive intent command.

  @param[in]  if_ptr   Pointer to transport interface instance.
  @param[in]  lcid     Local channel ID.
  @param[in]  size     Size of receive intent.
  @param[in]  liid     Local intent ID.

  @return     Returns error code.

  @sideeffects  None.
*/
/*=========================================================================*/
glink_err_type xport_qmp_tx_cmd_local_rx_intent
(
  glink_transport_if_type *if_ptr,
  uint32 lcid,
  size_t size,
  uint32 liid
)
{
  xport_qmp_ctx_type *ctx_ptr = (xport_qmp_ctx_type *)if_ptr;
  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_TX_CMD_LOCAL_RX_INTENT, ctx_ptr->current_state);
  #endif
  /* remove below unreference when adding back the debug_log */
  GLINK_OS_UNREFERENCED_PARAM(ctx_ptr);
  GLINK_OS_UNREFERENCED_PARAM(if_ptr);
  GLINK_OS_UNREFERENCED_PARAM(lcid);
  GLINK_OS_UNREFERENCED_PARAM(size);
  GLINK_OS_UNREFERENCED_PARAM(liid);

  return GLINK_STATUS_SUCCESS;
}


/*===========================================================================
FUNCTION      xport_qmp_ssr
===========================================================================*/
/**

  Handle SSR for the transport

  @param[in]  if_ptr        Pointer to transport interface.

  @return     Returns error code.

  @sideeffects  None.

  @dependencies None.
*/
/*=========================================================================*/
glink_err_type xport_qmp_ssr
(
  glink_transport_if_type *if_ptr
)
{
  /* Core doesn't really know of SSR. So we don't expect this call */
  ASSERT (0);
  return GLINK_STATUS_SUCCESS;
}


/*===========================================================================
FUNCTION      xport_qmp_set_version
===========================================================================*/
/**

  Signals that negotiation is complete and the transport can now 
  do version-specific initialization.

  @param[in]  if_ptr    Pointer to transport interface instance.
  @param[in]  version   Version to be used.
  @param[in]  feature   Features to be used.

  @return     None.

  @sideeffects  None.
*/
/*=========================================================================*/
uint32 xport_qmp_set_version
(
  glink_transport_if_type *if_ptr,
  uint32 version,
  uint32 features
)
{
  xport_qmp_ctx_type *ctx = (xport_qmp_ctx_type *)if_ptr; 
  ctx->negotiated_version.version  = version;
  ctx->negotiated_version.features = features;
  return 0; 
}


/*===========================================================================
FUNCTION      xport_qmp_negotiate_features
===========================================================================*/
/**

  Callback to verify feature set.

  @param[in]  if_ptr        Pointer to transport interface.
  @param[in]  version_ptr   Pointer to version descriptor.
  @param[in]  features      Proposed feature set.

  @return     negotiated feature.

  @sideeffects  None.

  @dependencies None.
*/
/*=========================================================================*/
uint32 xport_qmp_negotiate_features
(
  glink_transport_if_type *if_ptr,
  const glink_core_version_type *version_ptr,
  uint32 features
)
{
  return version_ptr->features & features;
}


/*===========================================================================
FUNCTION      xport_qmp_check_link
===========================================================================*/
/**

  Checks if qmp transport on remote host is ready.

  @param[in]  ctx_ptr   Pointer to transport context.

  @return     None.

  @dependencies None.
*/
/*=========================================================================*/

void xport_qmp_check_link(xport_qmp_ctx_type *ctx_ptr)
{
  glink_os_cs_acquire(&ctx_ptr->rx_link_lock);

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_CHECK_LINK, ctx_ptr->current_state);
  #endif
  if (ctx_ptr->ch_desc->magic == XPORT_QMP_MAILBOX_MAGIC)
  {
    if (ctx_ptr->current_state == LINK_DOWN)
    {
      ctx_ptr->local_mailbox_size = ctx_ptr->local_ch_desc->mailbox_size - 
                                    sizeof(ctx_ptr->local_mailbox->msg_len);
      ASSERT(ctx_ptr->local_mailbox_size < ctx_ptr->pcfg->mailbox_area_size_bytes);

      ctx_ptr->local_mailbox = (xport_qmp_mailbox*)((uint64)ctx_ptr->ch_desc + 
                                ctx_ptr->local_ch_desc->mailbox_offset);

      ASSERT(ctx_ptr->local_mailbox < 
             ((xport_qmp_mailbox*)(ctx_ptr->ch_desc + ctx_ptr->pcfg->mailbox_area_size_bytes)));
      ASSERT(ctx_ptr->local_mailbox > (xport_qmp_mailbox*)(ctx_ptr->ch_desc));

      ctx_ptr->remote_mailbox = (xport_qmp_mailbox*)((uint64)ctx_ptr->ch_desc + 
                                ctx_ptr->remote_ch_desc->mailbox_offset);
  
      ASSERT(ctx_ptr->remote_mailbox < 
             ((xport_qmp_mailbox*)(ctx_ptr->ch_desc + ctx_ptr->pcfg->mailbox_area_size_bytes)));
      ASSERT(ctx_ptr->remote_mailbox > (xport_qmp_mailbox*)(ctx_ptr->ch_desc));
  
      ctx_ptr->xport_if.glink_core_if_ptr->link_up((glink_transport_if_type *)ctx_ptr);
  
      glink_os_send_interrupt((os_ipc_intr_type *)&ctx_ptr->pcfg->irq);
	  #if XPORT_QMP_DEBUG_ENABLED
      xport_debug_log(ctx_ptr, XPORT_QMP_CHECK_LINK_INT_SEND, ctx_ptr->current_state);
	  #endif
    }
  }
  glink_os_cs_release(&ctx_ptr->rx_link_lock);  
}

void xport_qmp_alloc_fifo (xport_qmp_ctx_type *ctx_ptr)
{
  //ctx_ptr->ch_desc = (xport_qmp_ch_desc_type*)ctx_ptr->pcfg->mailbox_desc_start;
  ctx_ptr->local_ch_desc = &(ctx_ptr->ch_desc->sCore_desc);
  ctx_ptr->remote_ch_desc = &(ctx_ptr->ch_desc->mCore_desc);
  ctx_ptr->current_state = LINK_DOWN;
}

/*===========================================================================
                    LOCAL FUNCTION DECLARATIONS
===========================================================================*/


/*===========================================================================
FUNCTION      xport_qmp_isr
===========================================================================*/
/**

  ISR of qmp transport.

  @param[in]  ctx_ptr   Pointer to transport context.

  @return     None.

  @sideeffects  None.

  @dependencies None.
*/
/*=========================================================================*/
void xport_qmp_isr(xport_qmp_ctx_type *ctx_ptr)
{

  (void)ctx_ptr;
  uint32 transition_from_local_connecting_to_local_connected = 0;

  /* If edge specifies an explicit clear interrupt (is level triggered), 
   * invoke it */
  if ( ctx_ptr->pcfg->clear_interrupt)
  {
    ctx_ptr->pcfg->clear_interrupt();
  }

  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_ISR_START, ctx_ptr->current_state);
  #endif
  
  glink_os_cs_acquire(&ctx_ptr->rx_link_lock);
  
  switch(ctx_ptr->current_state){
    case LINK_DOWN:
    {
      xport_qmp_check_link(ctx_ptr);
    }
    break;

    case LINK_NEGOTIATION:
    {
      #if XPORT_QMP_DEBUG_ENABLED
	  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_LINK_NEGOTIATION, ctx_ptr->current_state);
	  #endif
      
      /* Check if local state was ack-ed */
      if (ctx_ptr->local_ch_desc->link_state == ctx_ptr->local_ch_desc->link_state_ack
         && ctx_ptr->local_ch_desc->ch_state == ctx_ptr->local_ch_desc->ch_state_ack)
      {
        /* Remote ack-ed local state. Complete initialization */
        ctx_ptr->current_state = LINK_UP;
        ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_version_ack(
                                                (glink_transport_if_type *)ctx_ptr,
                                                ctx_ptr->ch_desc->core_version,
                                                ctx_ptr->ch_desc->core_features);
      }
      else
      {
        break; //wait for isr to indicate remote has acked local state
      }
    }
    /* Fall through to check for more events */

    case LINK_UP:
    {
      #if XPORT_QMP_DEBUG_ENABLED
	  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_LINK_UP_ENTER, ctx_ptr->current_state);
	  #endif
      if (ctx_ptr->remote_ch_desc->ch_state != 
          ctx_ptr->remote_ch_desc->ch_state_ack)
      {
        ctx_ptr->remote_ch_desc->ch_state_ack = ctx_ptr->remote_ch_desc->ch_state;
        
        if (ctx_ptr->remote_ch_desc->ch_state == XPORT_QMP_CH_CONNECTED)
        {
          ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_ch_remote_open(
                       (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID,
                       ctx_ptr->pcfg->ch_name, GLINK_XPORT_QMP);
        }
        else        
        {
          ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_ch_remote_close(
                       (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID);
        }
        XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Remote Ch st changed",ctx_ptr->pcfg->remote_ss, ctx_ptr->remote_ch_desc->ch_state);
        
        glink_os_send_interrupt((os_ipc_intr_type *)&ctx_ptr->pcfg->irq);
      }
    }
    break;

    case LOCAL_CONNECTING:
    {
      #if XPORT_QMP_DEBUG_ENABLED
	  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_LOCAL_CONNECTING, ctx_ptr->current_state);
	  #endif
      /* Remote has acked our state */
      if (ctx_ptr->local_ch_desc->ch_state == ctx_ptr->local_ch_desc->ch_state_ack)
      {
        XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Recvd Open ack",ctx_ptr->pcfg->remote_ss, ctx_ptr->local_ch_desc->ch_state_ack);
        ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_ch_open_ack(
          (glink_transport_if_type *)ctx_ptr, ctx_ptr->lcid, GLINK_XPORT_QMP);
        ctx_ptr->current_state = LOCAL_CONNECTED;
        transition_from_local_connecting_to_local_connected = 1;
      }

      /* Check if we need to ack remote's state */
      if (ctx_ptr->remote_ch_desc->ch_state != ctx_ptr->remote_ch_desc->ch_state_ack)
      {
        /* If channel previously connected */
        if (ctx_ptr->remote_ch_desc->ch_state_ack == XPORT_QMP_CH_CONNECTED)
        {
          ctx_ptr->remote_ch_desc->ch_state_ack = XPORT_QMP_CH_DISCONNECTED;
          XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Remote ch close",ctx_ptr->pcfg->remote_ss, ctx_ptr->remote_ch_desc->ch_state);
          ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_ch_remote_close(
                  (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID);
        }
        else /* If previosuly disconnected */
        {
          ctx_ptr->remote_ch_desc->ch_state_ack = XPORT_QMP_CH_CONNECTED;
          XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Remote ch open", ctx_ptr->pcfg->remote_ss,ctx_ptr->remote_ch_desc->ch_state);
          ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_ch_remote_open(
                  (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID,
                  ctx_ptr->pcfg->ch_name, GLINK_XPORT_QMP);
        }
      }

      /* if both states are connected */
      if ((ctx_ptr->local_ch_desc->ch_state == ctx_ptr->remote_ch_desc->ch_state_ack)
           && transition_from_local_connecting_to_local_connected
           && (ctx_ptr->local_ch_desc->ch_state == XPORT_QMP_CH_CONNECTED))
      {
        XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Both sides opened",ctx_ptr->pcfg->remote_ss, 0);
        ctx_ptr->current_state = E2ECONNECTED;
      }
    }

    if(ctx_ptr->current_state == LOCAL_CONNECTING)
    {
      break;
    }

    case LOCAL_CONNECTED:
    {
      #if XPORT_QMP_DEBUG_ENABLED
	  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_LOCAL_CONNECTED, ctx_ptr->current_state);
	  #endif
      if (ctx_ptr->remote_ch_desc->ch_state != ctx_ptr->remote_ch_desc->ch_state_ack)
      {
        if (ctx_ptr->remote_ch_desc->ch_state == XPORT_QMP_CH_CONNECTED)
        {
          XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Remote ch open",ctx_ptr->pcfg->remote_ss, ctx_ptr->remote_ch_desc->ch_state);
          ctx_ptr->remote_ch_desc->ch_state_ack = XPORT_QMP_CH_CONNECTED;
          ctx_ptr->current_state = E2ECONNECTED;
          ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_ch_remote_open(
                  (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID,
                  ctx_ptr->pcfg->ch_name, GLINK_XPORT_QMP);
        }
      }
    }

    if (ctx_ptr->current_state != E2ECONNECTED)
    {
      break;
    }
    
    /* Fall through to check for more events */

    case E2ECONNECTED:
    {
      #if XPORT_QMP_DEBUG_ENABLED
	  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_E2ECONNECTED, ctx_ptr->current_state);
	  #endif
      if (ctx_ptr->remote_ch_desc->ch_state != ctx_ptr->remote_ch_desc->ch_state_ack)
      {
        /* Inform core of disconnect */
        ctx_ptr->remote_ch_desc->ch_state_ack = XPORT_QMP_CH_DISCONNECTED;
        XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Remote disconnected", ctx_ptr->pcfg->remote_ss,ctx_ptr->remote_ch_desc->ch_state);        
        ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_ch_remote_close(
                (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID);
        ctx_ptr->current_state = LOCAL_CONNECTED;
      }
      else
      {
        /* Check for data */
        size_t read_size = ctx_ptr->remote_mailbox->msg_len;
        if (read_size > 0 && !ctx_ptr-> receiving )
        {
          XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Rcvd data", ctx_ptr->pcfg->remote_ss, ctx_ptr->remote_mailbox->msg_len);
          ctx_ptr->receiving = TRUE;
          xport_qmp_process_rx_data(ctx_ptr, read_size);
        }
        
		glink_os_cs_acquire(&ctx_ptr->tx_link_lock);
		uint32 transmitted_intent_id = -1;
		
        if (ctx_ptr->transmitting && ctx_ptr->local_mailbox->msg_len == 0)
        {
          ctx_ptr->transmitting = FALSE;
		  		  
		  transmitted_intent_id = ctx_ptr->current_in_transmit_intent_iid;
          /*At this point the curr_intent_iid intent in local_intent_client_q should have been
            moved to local_intent_q, so we can set the curr_intent_iid = -1*/
		  ctx_ptr->current_in_transmit_intent_iid = -1;
		  glink_os_cs_release(&ctx_ptr->tx_link_lock);
		  
          XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Remote Rx done %d", ctx_ptr->pcfg->remote_ss,ctx_ptr->tx_pending_count);
          ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_tx_done(
          (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID, transmitted_intent_id, TRUE);

          ctx_ptr->xport_if.glink_core_if_ptr->tx_resume(
            (glink_transport_if_type *)ctx_ptr);
        }
		else 
		{
		  glink_os_cs_release(&ctx_ptr->tx_link_lock);
		}
      }
    }
    break;

    case LOCAL_DISCONNECTING:
    {
      #if XPORT_QMP_DEBUG_ENABLED
	  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_LOCAL_DISCONNECTING, ctx_ptr->current_state);
	  #endif
      if (ctx_ptr->remote_ch_desc->ch_state != ctx_ptr->remote_ch_desc->ch_state_ack)
      {
        XPORT_QMP_LOG_MSG(ctx_ptr, "Remote state chage %d", ctx_ptr->pcfg->remote_ss,ctx_ptr->remote_ch_desc->ch_state);

        if (ctx_ptr->remote_ch_desc->ch_state == XPORT_QMP_CH_DISCONNECTED)
        {
          ctx_ptr->remote_ch_desc->ch_state_ack = XPORT_QMP_CH_DISCONNECTED; 
          ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_ch_remote_close(
                             (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID);
        }
        else
        {
          ctx_ptr->remote_ch_desc->ch_state_ack = XPORT_QMP_CH_CONNECTED;
          ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_ch_remote_open(
                  (glink_transport_if_type *)ctx_ptr, XPORT_QMP_RCID,
                  ctx_ptr->pcfg->ch_name, GLINK_XPORT_QMP);
        }
      }
    
      if (ctx_ptr->local_ch_desc->ch_state == ctx_ptr->local_ch_desc->ch_state_ack)
      {
        XPORT_QMP_LOG_MSG(ctx_ptr->pcfg->remote_host, "Local close Ack",ctx_ptr->pcfg->remote_ss, ctx_ptr->tx_pending_count);
        ctx_ptr->xport_if.glink_core_if_ptr->rx_cmd_ch_close_ack(
                           (glink_transport_if_type *)ctx_ptr, ctx_ptr->lcid);
		ctx_ptr->current_state = LINK_UP;
      }
    }
    break;    
  }
  #if XPORT_QMP_DEBUG_ENABLED
  xport_debug_log(ctx_ptr, XPORT_QMP_DEBUG_ISR_END, ctx_ptr->current_state);
  #endif
  glink_os_cs_release(&ctx_ptr->rx_link_lock);
}


/*===========================================================================
FUNCTION      xport_qmp_init
===========================================================================*/
/**

  Initializes qmp transport.
  Must be called before any other operations are done.

  @param[in]  arg   The argument.

  @return     Returns error code.

  @sideeffects  None.
*/
/*=========================================================================*/
glink_err_type xport_qmp_init(void *arg)
{
  uint32 ind, size = 0;
  glink_core_transport_cfg_type xport_qmp_cfg = { 0 };

  //xport_qmp_debug_lock = glink_os_cs_create();
  
  if (xport_qmp_num_configs == 0)
  {
    return GLINK_STATUS_SUCCESS;
  }
  xport_qmp_ctx = glink_os_calloc(sizeof(*xport_qmp_ctx)*xport_qmp_num_configs);

  ASSERT(xport_qmp_ctx != NULL);

  /* Initialize supported version and features */
  xport_qmp_version = glink_os_calloc( sizeof( glink_core_version_type ) );
  
  ASSERT( xport_qmp_version );

  xport_qmp_version->version  = XPORT_QMP_VERSION;
  xport_qmp_version->features = XPORT_QMP_FEATURES;
  xport_qmp_version->negotiate_features = &xport_qmp_negotiate_features;
  
  /* Initialize edges */
  for (ind = 0; ind < xport_qmp_num_configs; ind++)
  {
    xport_qmp_ctx[ind].pcfg = xport_qmp_get_config(ind);
    
    /* Initialize context */
    xport_qmp_ctx[ind].tx_link_lock = glink_os_cs_create();
    xport_qmp_ctx[ind].rx_link_lock = glink_os_cs_create();
    xport_qmp_ctx[ind].tx_list_lock = glink_os_cs_create();

    xport_qmp_ctx[ind].ch_desc = (xport_qmp_ch_desc_type*) 
                         xport_qmp_alloc_mailbox(ind, &size);

    ASSERT(NULL != xport_qmp_ctx[ind].ch_desc);

    /* Initialize GLink transport interface */
    xport_qmp_ctx[ind].xport_if.tx_cmd_version = &xport_qmp_tx_cmd_version;
    xport_qmp_ctx[ind].xport_if.tx_cmd_version_ack = &xport_qmp_tx_cmd_version_ack;
    xport_qmp_ctx[ind].xport_if.set_version = &xport_qmp_set_version;
    xport_qmp_ctx[ind].xport_if.tx_cmd_ch_open = &xport_qmp_tx_cmd_ch_open;
    xport_qmp_ctx[ind].xport_if.tx_cmd_ch_remote_open_ack = &xport_qmp_tx_cmd_ch_remote_open_ack;
    xport_qmp_ctx[ind].xport_if.tx_cmd_ch_close = &xport_qmp_tx_cmd_ch_close;
    xport_qmp_ctx[ind].xport_if.tx_cmd_ch_remote_close_ack = &xport_qmp_tx_cmd_ch_remote_close_ack;
    xport_qmp_ctx[ind].xport_if.tx_cmd_rx_intent_req = &xport_qmp_tx_cmd_rx_intent_req;
    xport_qmp_ctx[ind].xport_if.tx_cmd_local_rx_intent = &xport_qmp_tx_cmd_local_rx_intent;
    xport_qmp_ctx[ind].xport_if.tx_cmd_local_rx_done = &xport_qmp_tx_cmd_local_rx_done;
    xport_qmp_ctx[ind].xport_if.allocate_rx_intent = &xport_qmp_allocate_rx_intent;
    xport_qmp_ctx[ind].xport_if.deallocate_rx_intent = &xport_qmp_deallocate_rx_intent;
    xport_qmp_ctx[ind].xport_if.tx = &xport_qmp_tx;
    xport_qmp_ctx[ind].xport_if.ssr = &xport_qmp_ssr;

    /* TODO: glink transport priority */
    xport_qmp_ctx[ind].xport_if.glink_priority = GLINK_XPORT_QMP;

    /*initialization*/
    xport_qmp_ctx[ind].current_in_transmit_intent_iid = -1;
    xport_qmp_ctx[ind].transmitting = FALSE;
    xport_qmp_ctx[ind].receiving = FALSE;
    xport_qmp_ctx[ind].free_iid = 0;
  
    /* Setup GLink configuration */
    xport_qmp_cfg.name = XPORT_QMP_NAME;
    xport_qmp_cfg.remote_ss = xport_qmp_ctx[ind].pcfg->remote_ss;
    xport_qmp_cfg.version   = xport_qmp_version;
    xport_qmp_cfg.version_count = 1;
    xport_qmp_cfg.max_cid = 0xFF;
    xport_qmp_cfg.max_iid = 0xFFFFFFFF;

    if (glink_core_register_transport(&xport_qmp_ctx[ind].xport_if, &xport_qmp_cfg) !=
        GLINK_STATUS_SUCCESS)
    {
      /* Registration failed, set index to invalid. */
      xport_qmp_ctx[ind].pcfg = NULL;
      continue;
    }

    xport_qmp_alloc_fifo (&xport_qmp_ctx[ind]);

    if (!glink_os_register_isr((os_ipc_intr_type *)&xport_qmp_ctx[ind].pcfg->irq, (os_isr_cb_fn)xport_qmp_isr,
                            &xport_qmp_ctx[ind]))
    {
      /* ISR registration failed, set index to invalid. */
      xport_qmp_ctx[ind].pcfg = NULL;
      continue;
    }

    xport_qmp_check_link (&xport_qmp_ctx[ind]);
  }

  return GLINK_STATUS_SUCCESS;
}

