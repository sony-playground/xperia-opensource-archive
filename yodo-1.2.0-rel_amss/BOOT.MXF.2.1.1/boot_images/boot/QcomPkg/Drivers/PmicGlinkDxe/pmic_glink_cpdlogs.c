/******************************************************************************
  @file    pmic_glink_cpdlog.c
  @brief   Glink communication layer between ChargerPD and APPS to read ChargerPD logs

  DESCRIPTION
  Implemetnation of communication layer between ChargerPD and APPS to read ChargerPD logs

  ---------------------------------------------------------------------------
  Copyright (c) 2018 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
  *******************************************************************************
  EDIT HISTORY

  when           who     what, where, why
  --------       ---     -----------------------------------------------------------

=============================================================================*/

// always include this header file at the top

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomLib.h>
#include "Library/SerialPortShLib.h"
#include <Library/QcomTargetLib.h>
#include <api/pmic/pm/pm_uefi.h>
#include <Library/QcomBaseLib.h>
#include <PrintShLib.h>

#include <Library/BaseMemoryLib.h>
#include <string.h>

#include "pmic_glink.h"

// glink handle instance
static glink_handle_type pmic_glink_cpdlog_handle;
static glink_open_config_type pmic_glink_cpdlog_cfg_ptr;
static EFI_GLINK_PROTOCOL* g_pmic_glink_cpdlog_protocol;
static glink_link_id_type pmic_glink_cpdlog_id;
static PMIC_GLINK_CONTEXT  pmic_glink_cpdlog_context = { 0 };

#define PMIC_GLINK_MAX_WAIT_COUNT              200//200
#define PMIC_GLINK_WAIT_TIME                   1000 * 10//1000 //1 MSEC 
#define PMIC_GLINK_CPDLOG_PKT_SIZE             0x3000   //for now big enough to accomodate upto 12KB of logs
#define LogLevelMax                            5
#define LogCategoriesMax                       0xFFFFFFFFFFFFFFFF   

static battman_get_log_resp_msg* get_log_respMsg = NULL;
static battman_get_qbg_dump_resp_msg* get_dump_respMsg = NULL;
static battman_get_log_resp_msg* get_init_log_respMsg = NULL;

/* ============================================================================
**� Function : GlinkCpdlogLocateProtocol
** ========================================================================== */
/**
@brief
GlinkCpdlogLocateProtocol function locates the glink protocol.
*/
EFI_STATUS GlinkCpdlogLocateProtocol()
{
  EFI_STATUS  Status = EFI_SUCCESS;

  if (g_pmic_glink_cpdlog_protocol == NULL)
  {
    Status = gBS->LocateProtocol(&gEfiGLINKProtocolGuid,
      NULL, (VOID**)&g_pmic_glink_cpdlog_protocol);
  }

  return Status;
}

/*=============================================================================
  FUNCTION pmic_glink_cpdlog_state_change
  =============================================================================*/

static void pmic_glink_cpdlog_state_change
(
glink_handle_type         handle,
const void                *priv,
glink_channel_event_type  event
)
{
  glink_err_type          ret = GLINK_STATUS_FAILURE;
  UINT32 i = 0;
  EFI_STATUS status = EFI_SUCCESS;

  DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_state_change:: got state_change event = %d  \r\n", event));
  if (GLINK_CONNECTED == event)
  {
    pmic_glink_cpdlog_context.IsPMICChannelOpen = TRUE;
    DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_state_change:: IsPMICChannelOpen = %d  \r\n", event));
    // initialize the rx buffer pool with rx buffers
    for (i = 0; i < PMIC_GLINK_RX_FIFO_DEPTH; i++)
    {
      status = g_pmic_glink_cpdlog_protocol->GlinkQueueRxIntent(pmic_glink_cpdlog_handle, (void*)(&pmic_glink_cpdlog_context), PMIC_GLINK_CPDLOG_PKT_SIZE, &ret);
      if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
      {
        DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_state_change:: queue Rx Intent failed. status = %r \r\n", status));
        //return EFI_DEVICE_ERROR;
      }
      else
      {
        DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_state_change:: queue Rx Intent success. status = %r \r\n", status));
      }
    }
  }
  else
  {
    pmic_glink_cpdlog_context.IsPMICChannelOpen = FALSE;
    if (event == GLINK_LOCAL_DISCONNECTED)
    {
      //error msg
      DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_state_change:: glink channel local disconnected.  \r\n"));
    }
    else
    {
      g_pmic_glink_cpdlog_protocol->GlinkClose(pmic_glink_cpdlog_handle, &ret);
    }

  }
}

/*=============================================================================
  FUNCTION pmic_glink_cpdlog_rx_done
  =============================================================================*/

EFI_STATUS pmic_glink_cpdlog_rx_done(const void *data, BOOLEAN refill)
{
  glink_err_type  ret;
  EFI_STATUS status = EFI_SUCCESS;
  if (g_pmic_glink_cpdlog_protocol == NULL)
  {
    return EFI_DEVICE_ERROR;
  }
  status = g_pmic_glink_cpdlog_protocol->GlinkRxDone(pmic_glink_cpdlog_handle, data, refill, &ret);

  if (EFI_ERROR(status) || (GLINK_STATUS_SUCCESS != ret))
  {
    //chargerPD todo error msg
    DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_rx_done:: failure status = %x, glink_ret = %d.  \r\n", status, ret));
    return EFI_DEVICE_ERROR;

  }
  return status;
}

/*=============================================================================
  FUNCTION pmic_glink_cpdlog_deinit
  =============================================================================*/

void pmic_glink_cpdlog_deinit()
{
  UINT8 count = 0;
  glink_err_type ret;
  EFI_STATUS status = EFI_SUCCESS;
  
  if (g_pmic_glink_cpdlog_protocol == NULL)
  {
    return;
  }
  if (pmic_glink_cpdlog_context.IsPMICChannelOpen)
  {
    g_pmic_glink_cpdlog_protocol->GlinkClose(pmic_glink_cpdlog_handle, &ret);
	if (ret) 
	{
      DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_deinit:: failure glink_ret = %d.  \r\n", ret));
      return;
    }
    while (count < PMIC_GLINK_MAX_WAIT_COUNT)
    {
      gBS->Stall(PMIC_GLINK_WAIT_TIME);
	
      status = g_pmic_glink_cpdlog_protocol->GlinkRxPoll(pmic_glink_cpdlog_handle, &ret);
	
      if (!pmic_glink_cpdlog_context.IsPMICChannelOpen && GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
      {
        break;
      }
      count++;
    }
    if (pmic_glink_cpdlog_context.IsPMICChannelOpen)
    {
      DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_deinit:: GlinkClose failed. Polling timeout.\r\n"));
      return;
    }
  }
  
  //chargerpd todo find out when to call this deregister.
  g_pmic_glink_cpdlog_protocol->GlinkDeregisterLinkStateCB(pmic_glink_cpdlog_id.handle, &ret);

}

/*=============================================================================
  FUNCTION pmic_glink_cpdlog_notify_rx
  =============================================================================*/

static void pmic_glink_cpdlog_notify_rx
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
  uint32 indicationType = 0;
    
  (void)pmic_glink_cpdlog_process_rx_data((PMIC_GLINK_HEADER_TYPE*)ptr, size, &indicationType);
  
  pmic_glink_cpdlog_context.RxNotified = TRUE;
}

static void pmic_glink_cpdlog_Link_State_NotifCb(glink_link_info_type *link_info, void *priv)
{
  EFI_STATUS status = EFI_SUCCESS;

  if (AsciiStrLen(PMIC_GLINK_REMOTE_SS_NAME) == AsciiStrLen(link_info->remote_ss) ||
    0 == AsciiStrnCmp(PMIC_GLINK_REMOTE_SS_NAME, link_info->remote_ss, AsciiStrLen(link_info->remote_ss)))
  {
    /* Process the notification */
    if (GLINK_LINK_STATE_UP == link_info->link_state)
    {
      DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_Link_State_NotifCb:: GLINK_LINK_STATE_UP remote ss = %a transport name = %a \r\n", status, link_info->remote_ss, link_info->xport));
      pmic_glink_cpdlog_context.IsPMICLINKUP = TRUE;
    }
    else if (GLINK_LINK_STATE_DOWN == link_info->link_state)
    {
      //send signal to exit thread
      pmic_glink_cpdlog_context.IsPMICLINKUP = FALSE;
    }
    else
    {
      //
    }
  }
  else
  {
    //DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_Link_State_NotifCb:: remote ss = %s transport name = %s IGNORE \r\n", status, link_info->remote_ss, link_info->xport));
    return;
  }
}

/*===========================================================================
FUNCTION  glinkTestTxNotificationCb
===========================================================================*/
/**
glinkTestTxNotificationCb

@param[in] handle

@return
*/
/*==========================================================================*/
void pmic_glink_cpdlog_notify_tx_done(glink_handle_type handle,
  const void        *priv,
  const void        *pkt_priv,
  const void        *ptr,
  size_t            size)
{
  pmic_glink_cpdlog_context.TxDone = TRUE;
}


/*=============================================================================
FUNCTION pmic_glink_open
=============================================================================*/

EFI_STATUS pmic_glink_cpdlog_open(void *context)
{
  glink_err_type         ret;
  UINT8                  count = 0;
  EFI_STATUS             status = EFI_SUCCESS;

  if (NULL == g_pmic_glink_cpdlog_protocol)
  {
    return EFI_DEVICE_ERROR;
  }

  status = g_pmic_glink_cpdlog_protocol->GlinkOpen(&pmic_glink_cpdlog_cfg_ptr, &pmic_glink_cpdlog_handle, &ret);
  if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
  {
    DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_open:: GlinkOpen failed\r\n"));
    return EFI_DEVICE_ERROR;
  }
  
  while (count < PMIC_GLINK_MAX_WAIT_COUNT)
  {
    gBS->Stall(PMIC_GLINK_WAIT_TIME);
	
    status = g_pmic_glink_cpdlog_protocol->GlinkRxPoll(pmic_glink_cpdlog_handle, &ret);
	
    if (pmic_glink_cpdlog_context.IsPMICChannelOpen && GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
    {
      break;
    }
    count++;
  }
  if (!pmic_glink_cpdlog_context.IsPMICChannelOpen)
  {
	DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_open:: GlinkOpen failed. Polling timeout.\r\n"));
    return EFI_DEVICE_ERROR;
  }

  return status;
}

/*=============================================================================
  FUNCTION pmic_glink_cpdlog_Init
  =============================================================================*/

EFI_STATUS pmic_glink_cpdlog_Init()
{
  EFI_STATUS status = EFI_SUCCESS;
  glink_err_type ret = GLINK_STATUS_FAILURE;
  UINT8 count = 0;

  status = GlinkCpdlogLocateProtocol();
  if (EFI_ERROR(status))
  {
    return status;
  }
  memset(&pmic_glink_cpdlog_cfg_ptr, 0, sizeof(glink_open_config_type));
  pmic_glink_cpdlog_cfg_ptr.name = PMIC_GLINK_CPDLOG_COMM_PORT_NAME;
  pmic_glink_cpdlog_cfg_ptr.remote_ss = PMIC_GLINK_REMOTE_SS_NAME;
  pmic_glink_cpdlog_cfg_ptr.transport = PMIC_GLINK_XPORT_NAME;
  pmic_glink_cpdlog_cfg_ptr.notify_rx = pmic_glink_cpdlog_notify_rx;
  pmic_glink_cpdlog_cfg_ptr.notify_tx_done = pmic_glink_cpdlog_notify_tx_done;
  pmic_glink_cpdlog_cfg_ptr.notify_state = pmic_glink_cpdlog_state_change;

  GLINK_LINK_ID_STRUCT_INIT(pmic_glink_cpdlog_id);
  pmic_glink_cpdlog_id.version = GLINK_LINK_ID_VER; 
  pmic_glink_cpdlog_id.xport = pmic_glink_cpdlog_cfg_ptr.transport;
  pmic_glink_cpdlog_id.remote_ss = pmic_glink_cpdlog_cfg_ptr.remote_ss;
  pmic_glink_cpdlog_id.link_notifier = pmic_glink_cpdlog_Link_State_NotifCb;
  pmic_glink_cpdlog_id.handle = NULL;

  pmic_glink_cpdlog_context.IsPMICLINKUP = FALSE;
  pmic_glink_cpdlog_context.IsPMICChannelOpen = FALSE;

  /*Register link state callback*/
  status = g_pmic_glink_cpdlog_protocol->GlinkRegisterLinkStateCB(&pmic_glink_cpdlog_id, (void*)(&pmic_glink_cpdlog_context), &ret);
  if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
  {
    DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_Init:: registerLinkStateCB failed status = %x, glinkRet = %d. \r\n", status, ret));
    return EFI_DEVICE_ERROR;

  }

  glink_link_state_type link_state = GLINK_LINK_STATE_DOWN;

  while (count < PMIC_GLINK_MAX_WAIT_COUNT)
  {
    gBS->Stall(PMIC_GLINK_WAIT_TIME);
	
    status = g_pmic_glink_cpdlog_protocol->GlinkLinkStatePoll(pmic_glink_cpdlog_id.handle, &link_state, &ret);

    if (pmic_glink_cpdlog_context.IsPMICLINKUP && GLINK_LINK_STATE_UP == link_state && GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
    {
      DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_Init:: glink is up.  \r\n"));
      break;
    }
    count++;
  }
  if (!pmic_glink_cpdlog_context.IsPMICLINKUP)
  {
    DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_Init:: wait for glink up in wait timed out. \r\n"));
    return EFI_DEVICE_ERROR;
  }

  status = pmic_glink_cpdlog_open(NULL);
  if (EFI_SUCCESS != status)
  {
    DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_Init:: open glink channel failed during Init %r \r\n", status));
  }
  else
  {
    DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_Init:: open glink channel success \r\n"));
  }

  return status;
}



/*=============================================================================
  FUNCTION pmic_glink_cpdlog_tx
  =============================================================================*/

EFI_STATUS pmic_glink_cpdlog_tx(const void *priv,
  const void *data, const size_t size)
{
  glink_err_type         ret;
  EFI_STATUS status = EFI_SUCCESS;
  UINT8 count = 0, i = 0;

  if (NULL == g_pmic_glink_cpdlog_protocol)
  {
    return EFI_DEVICE_ERROR;
  }
  pmic_glink_cpdlog_context.TxDone = FALSE;
  
  for(i = 0; i < PMIC_GLINK_MAX_WAIT_COUNT; i++)
  {
    glink_err_type         rxpoll_ret;
    status = g_pmic_glink_cpdlog_protocol->GlinkTx(pmic_glink_cpdlog_handle, priv, data, size, 0, &ret);
    if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
    {
      gBS->Stall(PMIC_GLINK_WAIT_TIME);
      //chargerPD todo error msg
      DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_tx:: glink tx failed status = %r.ret = %d \r\n", status, ret));
      g_pmic_glink_cpdlog_protocol->GlinkRxPoll(pmic_glink_cpdlog_handle, &rxpoll_ret);
    }
    else
    {
      break;
    }    
  }
  if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret)) { return EFI_DEVICE_ERROR;}

  while (count < PMIC_GLINK_MAX_WAIT_COUNT)
  {
    gBS->Stall(PMIC_GLINK_WAIT_TIME);

	  status = g_pmic_glink_cpdlog_protocol->GlinkRxPoll(pmic_glink_cpdlog_handle, &ret);
	
    if (pmic_glink_cpdlog_context.TxDone && GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
    {
      break;
    }
    count++;
  }

  if (!pmic_glink_cpdlog_context.TxDone)
  {
    return EFI_DEVICE_ERROR;
  }
  return status;
}


/*=============================================================================
FUNCTION  pmic_glink_cpdlog_sync_send_receive
=============================================================================*/

EFI_STATUS pmic_glink_cpdlog_sync_send_receive(uint32 opcode, void* inputBuffer, size_t inputSize)
{
  EFI_STATUS status = EFI_SUCCESS;
  glink_err_type         ret;
  uint32                 count = 0;
  EFI_TPL                OrigTPL;

  /* Raise TPL to avoid interrupt */
  OrigTPL = gBS->RaiseTPL(TPL_CALLBACK);
  
  if(pmic_glink_cpdlog_context.IsPMICChannelOpen == TRUE)
  {
    pmic_glink_cpdlog_context.RxNotified = FALSE;
    //send the inputBuffer
    status = pmic_glink_cpdlog_tx(&pmic_glink_cpdlog_context, inputBuffer, inputSize);

    if (EFI_ERROR(status))
    {
      DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_sync_send_receive:: glink tx failed status = %r.  \r\n", status));
	  goto Exit;
    }
    while (count < PMIC_GLINK_MAX_WAIT_COUNT)
    {
      gBS->Stall(PMIC_GLINK_WAIT_TIME);
      if (!(pmic_glink_cpdlog_context.IsPMICLINKUP) || !(pmic_glink_cpdlog_context.IsPMICChannelOpen))
      {
        DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_sync_send_receive:: glink disconnected isPmicLinkUp = %d, isPmicChannelOpen = %d.  \r\n", pmic_glink_cpdlog_context.IsPMICLINKUP, pmic_glink_cpdlog_context.IsPMICChannelOpen));
        status = EFI_DEVICE_ERROR;
        break;
      }
	  
      status = g_pmic_glink_cpdlog_protocol->GlinkRxPoll(pmic_glink_cpdlog_handle, &ret);
	  
      if (pmic_glink_cpdlog_context.RxNotified && GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
      {
        break;
      }
      count++;
    }
    if (!pmic_glink_cpdlog_context.RxNotified)
    {
      DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_sync_send_receive:: wait for Rx Notification timed out. \r\n"));
      status = EFI_DEVICE_ERROR;
    }

    pmic_glink_cpdlog_context.RxNotified = FALSE;
  }

  Exit: 
    gBS->RestoreTPL(OrigTPL);
    return status;
}


/*=============================================================================
  FUNCTION pmic_glink_cpdlog_process_rx_data
  =============================================================================*/

EFI_STATUS pmic_glink_cpdlog_process_rx_data(PMIC_GLINK_HEADER_TYPE* rxData, size_t size, uint32* indicationReceived)
{
  EFI_STATUS             status = EFI_SUCCESS;

  if ((NULL == g_pmic_glink_cpdlog_protocol ) || (rxData == NULL) || (indicationReceived == NULL))
  {
    return EFI_DEVICE_ERROR;
  }

  if (rxData->msg_owner == PMIC_GLINK_MSG_OWNER_CHARGER)
  {
    DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_process_rx_data:: got rx data for battery manager.  \r\n"));
    //handle battmngr requests
    switch (rxData->opcode)
    {
    case BATT_MNGR_SET_LOGGING_PROP_REQ:
      DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_process_rx_data:: got rx data for BATT_MNGR_SET_LOGGING_PROP_REQ.  \r\n"));
      pmic_glink_cpdlog_context.SetLoggingProperties = FALSE;

      if(size == sizeof(batt_mngr_generic_resp_msg)){
        batt_mngr_generic_resp_msg* respMsg = (batt_mngr_generic_resp_msg*)rxData;
        if (respMsg != NULL)
        {
          pmic_glink_cpdlog_context.SetLoggingProperties = TRUE;
          DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_process_rx_data:: ChargerPD Logging category and level is set\r\n"));   
        }  
      }
      break;

    case BATT_MNGR_GET_ULOG_REQ:   
      DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_process_rx_data:: got rx data for BATT_MNGR_GET_ULOG_REQ.  \r\n"));
      pmic_glink_cpdlog_context.GetChargerPDLogs = FALSE;

      if (size == sizeof(battman_get_log_resp_msg))
      {
        get_log_respMsg = (battman_get_log_resp_msg*)rxData;
        if (get_log_respMsg != NULL)
        {
          pmic_glink_cpdlog_context.GetChargerPDLogs = TRUE;
          DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_process_rx_data:: ChargerPd logs fetched. \r\n"));    
        }
      }
      break;
    
    case BATT_MNGR_GET_INIT_ULOG_REQ:   
      DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_process_rx_data:: got rx data for BATT_MNGR_GET_INIT_ULOG_REQ.  \r\n"));
      pmic_glink_cpdlog_context.GetChargerPDInitLogs = FALSE;

      if (size == sizeof(battman_get_log_resp_msg))
      {
        get_init_log_respMsg = (battman_get_log_resp_msg*)rxData;
        if (get_init_log_respMsg != NULL)
        {
          pmic_glink_cpdlog_context.GetChargerPDInitLogs = TRUE;
          DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_process_rx_data:: ChargerPd init logs fetched. \r\n"));    
        }
      }
      break;
    
    default:
      status = EFI_INVALID_PARAMETER;
      break;
    }
  }
    
  else if (rxData->msg_owner == PMIC_GLINK_MSG_OWNER_QBG_DEBUG)
  {
    DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_process_rx_data:: got rx data for Qbg debug.  \r\n"));
    //handle battmngr requests
    switch (rxData->opcode)
    {
    case BATT_MNGR_GET_QBG_DUMP_REQ:   
      DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_process_rx_data:: got rx data for BATT_MNGR_GET_QBG_DUMP_REQ.  \r\n"));
      pmic_glink_cpdlog_context.GetQBGDump = FALSE;
      
      if (size == sizeof(battman_get_qbg_dump_resp_msg))
      {
        get_dump_respMsg = (battman_get_qbg_dump_resp_msg*)rxData;
        if (get_dump_respMsg != NULL)
        {
          pmic_glink_cpdlog_context.GetQBGDump = TRUE;
          DEBUG((EFI_D_INFO, "pmic_glink_cpdlog_process_rx_data:: QBG Dump fetched. \r\n"));    
        }
      }
      break;

    default:
      status = EFI_INVALID_PARAMETER;
      break;
    }
  }
    
  else
  {
    //not correct msg owner
    DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_process_rx_data:: got rx data of unknown owner.  \r\n"));
  }
  
  //rx done to free evt_buf and requeue rx intent.
  status |= pmic_glink_cpdlog_rx_done(rxData, TRUE);

  return status;
}

EFI_STATUS pmic_glink_cpdlog_get_link_status(  EFI_PM_GLINK_LINK_STATUS *PmicGLinkStatus)
{
  if(NULL == PmicGLinkStatus)
    return EFI_INVALID_PARAMETER;

  PmicGLinkStatus->IsPMICChannelOpen = pmic_glink_cpdlog_context.IsPMICChannelOpen;

  return EFI_SUCCESS;
}

EFI_STATUS pmic_glink_cpdlog_set_properties(UINT64 LogCategories, UINT32 LogLevel){
  EFI_STATUS status = EFI_SUCCESS;
  battman_set_log_properties_req_msg reqMsg = { { 0 }, 0, 0 };
  
  if (LogCategories > LogCategoriesMax || LogLevel > LogLevelMax)
    return EFI_INVALID_PARAMETER;

  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_CHARGER;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = BATT_MNGR_SET_LOGGING_PROP_REQ; 
  reqMsg.categories = LogCategories;
  reqMsg.level = LogLevel;
  status = pmic_glink_cpdlog_sync_send_receive(BATT_MNGR_SET_LOGGING_PROP_REQ, &reqMsg, sizeof(battman_set_log_properties_req_msg));
  if (EFI_SUCCESS == status && pmic_glink_cpdlog_context.SetLoggingProperties)
    return status;
  else
    return EFI_DEVICE_ERROR;
}


EFI_STATUS pmic_glink_cpdlog_get_buffer(UINT32 LogMaxSize, CHAR8* ReceivedBuffer){
  EFI_STATUS status = EFI_SUCCESS;
  battman_get_log_req_msg reqMsg = { { 0 }, 0 };

  size_t received_buff_size=0;

  if (LogMaxSize == 0 || LogMaxSize > MAX_ULOG_READ_BUFFER_SIZE)
    return EFI_INVALID_PARAMETER;
  
  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_CHARGER;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = BATT_MNGR_GET_ULOG_REQ; 
  reqMsg.max_logsize = LogMaxSize;
  
  status = pmic_glink_cpdlog_sync_send_receive(BATT_MNGR_GET_ULOG_REQ, &reqMsg, sizeof(battman_get_log_req_msg));
  if (EFI_SUCCESS == status && pmic_glink_cpdlog_context.GetChargerPDLogs){
    received_buff_size = strlen(get_log_respMsg->read_buffer); 
    memscpy(ReceivedBuffer, MAX_ULOG_READ_BUFFER_SIZE, get_log_respMsg->read_buffer, received_buff_size);
    return status;
  }
  else
    return EFI_DEVICE_ERROR;
}



EFI_STATUS pmic_glink_cpdlog_get_qbg_dump(UINT32 *ReceivedQbgDumpSize, UINT32 *ReceivedQbgDump, UINT32 battery_cell_id){
  EFI_STATUS status = EFI_SUCCESS;
  battman_get_qbg_dump_req_msg reqMsg = { { 0 } };
 
  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_QBG_DEBUG;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = BATT_MNGR_GET_QBG_DUMP_REQ; 
  reqMsg.battery_cell_id = battery_cell_id;
  
  status = pmic_glink_cpdlog_sync_send_receive(BATT_MNGR_GET_QBG_DUMP_REQ, &reqMsg, sizeof(battman_get_qbg_dump_req_msg));
  
  if (EFI_SUCCESS == status && pmic_glink_cpdlog_context.GetQBGDump){
    
    *ReceivedQbgDumpSize = (get_dump_respMsg->dump_size)/sizeof(uint32);   //Changed ADSP code to send total number of bytes to HLOS instead of sending total number of uint32. Dividing it by 4, I am changing it back to total uint32 count for easy parsing the dump

    if((*ReceivedQbgDumpSize) < 1)
    {
        DEBUG((EFI_D_WARN, "pmic_glink_cpdlog_process_rx_data:: Received QBG device context dump is empty\r\n"));
        return status;
    }

    memcpy(ReceivedQbgDump, get_dump_respMsg->data_buffer, sizeof(uint32)*(*ReceivedQbgDumpSize)); 
    
    return status;
  }
  else
    return EFI_DEVICE_ERROR;
}


EFI_STATUS pmic_glink_cpdlog_get_init_buffer(UINT32 LogMaxSize, CHAR8* ReceivedBuffer){
  EFI_STATUS status = EFI_SUCCESS;
  battman_get_log_req_msg reqMsg = { { 0 }, 0 };

  size_t received_buff_size=0;

  if (LogMaxSize == 0 || LogMaxSize > MAX_ULOG_READ_BUFFER_SIZE)
    return EFI_INVALID_PARAMETER;
  
  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_CHARGER;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = BATT_MNGR_GET_INIT_ULOG_REQ; 
  reqMsg.max_logsize = LogMaxSize;
  
  status = pmic_glink_cpdlog_sync_send_receive(BATT_MNGR_GET_INIT_ULOG_REQ, &reqMsg, sizeof(battman_get_log_req_msg));
  if (EFI_SUCCESS == status && pmic_glink_cpdlog_context.GetChargerPDInitLogs){
    received_buff_size = strlen(get_init_log_respMsg->read_buffer); 
    memscpy(ReceivedBuffer, LogMaxSize, get_init_log_respMsg->read_buffer, received_buff_size);
    return status;
  }
  else
    return EFI_DEVICE_ERROR;
}
