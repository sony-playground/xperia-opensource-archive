/*
 * @file PASRQMP.c
 *
 * @brief PASRQMP functions
 *
 * Copyright (c) 2022 by Qualcomm Technologies, Inc. 
 * All Rights Reserved.
 *
 */
 /*
=====================================================================================
*/
/*
======================================================================================
                        Edit History

when       who     what, where, why
--------   ----    --------------------------------------------------- 
05/14/22   ddk     Initital Version
======================================================================================
*/
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <PrintShLib.h>
#include <Library/BaseMemoryLib.h>
#include "string.h"
#include "PASRQMP.h"

//glink handle instance
static glink_handle_type qmp_glink_handle;
static glink_open_config_type qmp_glink_cfg_ptr;
static EFI_GLINK_PROTOCOL* g_glink_protocol;
static glink_link_id_type qmp_glink_id;
static QMP_GLINK_CONTEXT  qmp_glink_context = { 0 };

#define QMP_GLINK_MAX_WAIT_COUNT    200
#define QMP_GLINK_WAIT_TIME         10

EFI_STATUS PASR_QmpOpen(void *context);

/* ============================================================================
** Function : PASR_QmpLocateProtocol
** ============================================================================ */
/**
@brief
PASR_QmpLocateProtocol function locates the glink protocol.
*/
EFI_STATUS PASR_QmpLocateProtocol(void)
{
  EFI_STATUS  Status = EFI_SUCCESS;

  if (g_glink_protocol == NULL)
  {
    Status = gBS->LocateProtocol(&gEfiGLINKProtocolGuid,
      NULL, (VOID**)&g_glink_protocol);
  }

  return Status;
}

/*=============================================================================
  FUNCTION PASR_QmpStateChange
  =============================================================================*/

static void PASR_QmpStateChange(glink_handle_type handle, const void *priv, glink_channel_event_type event)
{
  glink_err_type ret = GLINK_STATUS_FAILURE;
  //DEBUG((EFI_D_WARN, "PASR_QmpStateChange:: got state_change event = %d  \r\n", event));
  if (GLINK_CONNECTED == event)
  {
    qmp_glink_context.is_channel_open = TRUE;
    //DEBUG((EFI_D_WARN, "PASR_QmpStateChange:: is_channel_open = %d  \r\n", TRUE));
  }
  else
  {
    qmp_glink_context.is_channel_open = FALSE;
    if (event == GLINK_LOCAL_DISCONNECTED)
    {
      //error msg
      //DEBUG((EFI_D_WARN, "PASR_QmpStateChange:: glink channel local disconnected.  \r\n"));
    }
    else
    {
      g_glink_protocol->GlinkClose(qmp_glink_handle, &ret);
    }
  }
}

/*=============================================================================
  FUNCTION PASR_QmpDeInit
  =============================================================================*/

EFI_STATUS PASR_QmpDeInit()
{
  UINT8 count = 0;
  glink_err_type ret;
  EFI_STATUS             status = EFI_SUCCESS;
  if (g_glink_protocol == NULL)
  {
    return EFI_DEVICE_ERROR;
  }
  if (qmp_glink_context.is_channel_open)
  {
    status = g_glink_protocol->GlinkClose(qmp_glink_handle, &ret);
    if ((ret || EFI_ERROR(status))) 
    {
      DEBUG((EFI_D_ERROR, "PASR_QmpDeInit:: failure glink_ret = %d.  \r\n", ret));
      return EFI_DEVICE_ERROR;
    }
    while (count < QMP_GLINK_MAX_WAIT_COUNT)
    {
      if (!qmp_glink_context.is_channel_open)
      {
        break;
      }
      gBS->Stall(QMP_GLINK_WAIT_TIME);
      count++;
    }
    if (qmp_glink_context.is_channel_open)
    {
      DEBUG((EFI_D_ERROR, "PASR_QmpDeInit:: GlinkClose failed. Polling timeout.\r\n"));
      return EFI_DEVICE_ERROR;
    }
  }
  g_glink_protocol->GlinkDeregisterLinkStateCB(qmp_glink_id.handle, &ret);
  return status;
}

/*=============================================================================
  FUNCTION PASR_QmpNotifyRx
  =============================================================================*/

static void PASR_QmpNotifyRx
(
    glink_handle_type handle,     /* handle for the glink channel */
    const void        *priv,      /* priv client data passed in glink_open */
    const void        *pkt_priv,  /* private client data assiciated with the
                                    rx intent that client queued earlier */
    const void        *ptr,       /* pointer to the received buffer */
    size_t            size,       /* size of the packet */
    size_t            intent_used /* size of the intent used for this packet */
)
{
    qmp_glink_context.rx_notified = TRUE;
}

static void PASR_QmpLinkStateNotifCb(glink_link_info_type *link_info, void *priv)
{
  if (AsciiStrLen(QMP_GLINK_REMOTE_SS_NAME) == AsciiStrLen(link_info->remote_ss) ||
    0 == AsciiStrnCmp(QMP_GLINK_REMOTE_SS_NAME, link_info->remote_ss, AsciiStrLen(link_info->remote_ss)))
  {
    /* Process the notification */
    if (GLINK_LINK_STATE_UP == link_info->link_state)
    {
      //DEBUG((EFI_D_WARN, "PASR_QmpLinkStateNotifCb:: GLINK_LINK_STATE_UP remote ss = %s transport name = %s \r\n", link_info->remote_ss, link_info->xport));
      qmp_glink_context.is_link_up = TRUE;
    }
    else if (GLINK_LINK_STATE_DOWN == link_info->link_state)
    {
      //send signal to exit thread
      qmp_glink_context.is_link_up = FALSE;
    }
  }
  else
  {
    //DEBUG((EFI_D_WARN, "PASR_QmpLinkStateNotifCb:: remote ss = %s transport name = %s IGNORE \r\n", status, link_info->remote_ss, link_info->xport));
    return;
  }
}

/*===========================================================================
FUNCTION  PASR_QmpNotifyTxDone
===========================================================================*/
/**
PASR_QmpNotifyTxDone


@param[in] handle

@return
*/
/*==========================================================================*/
void PASR_QmpNotifyTxDone(glink_handle_type handle,
  const void        *priv,
  const void        *pkt_priv,
  const void        *ptr,
  size_t            size)
{
  qmp_glink_context.tx_done = TRUE;
}


/*=============================================================================
FUNCTION PASR_QmpOpen
=============================================================================*/

EFI_STATUS PASR_QmpOpen(void *context)
{
  glink_err_type         ret;
  UINT8                  count = 0;
  EFI_STATUS             status = EFI_SUCCESS;

  if (NULL == g_glink_protocol)
  {
    return EFI_DEVICE_ERROR;
  }

  status = g_glink_protocol->GlinkOpen(&qmp_glink_cfg_ptr, &qmp_glink_handle, &ret);
  if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
  {
    DEBUG((EFI_D_ERROR, "PASR_QmpOpen:: GlinkOpen failed\r\n"));
    return EFI_DEVICE_ERROR;
  }
  
  while (count < QMP_GLINK_MAX_WAIT_COUNT)
  {
    //status = g_glink_protocol->GlinkRxPoll(qmp_glink_handle, &ret);//looks like there is no GlinkRxPoll registered for qmp
    //poll GlinkOpen result
    if (qmp_glink_context.is_channel_open)
    {
      break;
    }

    gBS->Stall(QMP_GLINK_WAIT_TIME);//wait for 10ms
    count++;
  }
  if (!qmp_glink_context.is_channel_open)
  {
    DEBUG((EFI_D_ERROR, "glink_open:: GlinkOpen failed. Polling timeout.\r\n"));
    return EFI_DEVICE_ERROR;
  }
  return status;
}

/*=============================================================================
  FUNCTION PASR_QmpInit
  =============================================================================*/
//char* aop_msg = "{class: clock, res: qdss, val: 1}";

EFI_STATUS PASR_QmpInit(void)
{
  EFI_STATUS status = EFI_SUCCESS;
  glink_err_type ret = GLINK_STATUS_FAILURE;
  UINT8 count = 0;

  status = PASR_QmpLocateProtocol();
  if (EFI_ERROR(status))
  {
    return status;
  }
  memset(&qmp_glink_cfg_ptr, 0, sizeof(glink_open_config_type));
  qmp_glink_cfg_ptr.name = "aop_apps";//must be "aop_apps"
  qmp_glink_cfg_ptr.remote_ss = "rpm";
  qmp_glink_cfg_ptr.transport = "qmp";
  qmp_glink_cfg_ptr.notify_rx = PASR_QmpNotifyRx;
  qmp_glink_cfg_ptr.notify_tx_done = PASR_QmpNotifyTxDone;
  qmp_glink_cfg_ptr.notify_state = PASR_QmpStateChange;

  GLINK_LINK_ID_STRUCT_INIT(qmp_glink_id);
  qmp_glink_id.version = GLINK_LINK_ID_VER;
  qmp_glink_id.xport = qmp_glink_cfg_ptr.transport;
  qmp_glink_id.remote_ss = qmp_glink_cfg_ptr.remote_ss;
  qmp_glink_id.link_notifier = PASR_QmpLinkStateNotifCb;
  qmp_glink_id.handle = NULL;

  qmp_glink_context.is_link_up = FALSE;
  qmp_glink_context.is_channel_open = FALSE;

  /*Register link state callback*/
  status = g_glink_protocol->GlinkRegisterLinkStateCB(&qmp_glink_id, (void*)(&qmp_glink_context), &ret);
  if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
  {
    DEBUG((EFI_D_ERROR, "PASR_QmpInit:: registerLinkStateCB failed status = 0x%x, glinkRet = %d. \r\n", status, ret));
    return EFI_DEVICE_ERROR;

  }

  glink_link_state_type link_state = GLINK_LINK_STATE_DOWN;

  while (count < 200)
  {
    status = g_glink_protocol->GlinkLinkStatePoll(qmp_glink_id.handle, &link_state, &ret);

    if (qmp_glink_context.is_link_up && GLINK_LINK_STATE_UP == link_state && GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
    {
       //DEBUG((EFI_D_ERROR, "PASR_QmpInit:: glink is up.  \r\n"));
       break;
    }

    gBS->Stall(QMP_GLINK_WAIT_TIME);
    count++;
  }
  if (!qmp_glink_context.is_link_up)
  {
    DEBUG((EFI_D_ERROR, "PASR_QmpInit:: wait for glink up in wait timed out. \r\n"));
    return EFI_DEVICE_ERROR;
  }

  status = PASR_QmpOpen(NULL);
  
  if (EFI_SUCCESS != status)
  {
    DEBUG((EFI_D_WARN, "PASR_QmpInit:: open glink channel failed during Init %r \r\n", status));
  }
  else
  {
    //DEBUG((EFI_D_INFO, "PASR_QmpInit:: open glink channel success \r\n"));
  }

  // initialize the rx buffer pool with rx buffers
  status = g_glink_protocol->GlinkQueueRxIntent(qmp_glink_handle, "ut", QMP_GLINK_PKT_SIZE, &ret);
  if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
  {
    DEBUG((EFI_D_ERROR, "PASR_QmpInit:: queue Rx Intent failed. status = %r \r\n", status));
    //return EFI_DEVICE_ERROR;
  }
  else
  {
    //DEBUG((EFI_D_WARN, "PASR_QmpInit:: queue Rx Intent success. status = %r \r\n", status));
  }
  //status = PASR_QmpTx(&qmp_glink_context, copy_json_str, __str_size);
  return status;
}



/*=============================================================================
  FUNCTION PASR_QmpTx
  =============================================================================*/

EFI_STATUS PASR_QmpTx(const void *priv, const void *data, const size_t size)
{
  glink_err_type         ret;
  EFI_STATUS status = EFI_SUCCESS;
  UINT8 count = 0;

  if (NULL == g_glink_protocol)
  {
    return EFI_DEVICE_ERROR;
  }

  qmp_glink_context.tx_done = FALSE;

  status = g_glink_protocol->GlinkTx(qmp_glink_handle, priv, data, size, GLINK_TX_REQ_INTENT, &ret);//option must be GLINK_TX_REQ_INTENT
  if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
  {
    DEBUG((EFI_D_ERROR, "qmp_glink_sync_send_receive:: glink tx failed status = %r.ret = %d \r\n", status, ret));
  }    

  while (count < QMP_GLINK_MAX_WAIT_COUNT)
  {
    //status = g_glink_protocol->GlinkRxPoll(qmp_glink_handle, &ret);
    if (qmp_glink_context.tx_done)
    {
      //DEBUG((EFI_D_WARN, "PASR_QmpTx:: tx done \r\n"));
      break;
    }

    gBS->Stall(QMP_GLINK_WAIT_TIME);
    count++;
  }

  if (!qmp_glink_context.tx_done)
  {
    return EFI_DEVICE_ERROR;
  }

  return status;
}

EFI_STATUS PASR_QmpSendMsg(const void *data, const size_t size)
{
  EFI_STATUS status = PASR_QmpTx(&qmp_glink_context, data, size);
  return status;
}



