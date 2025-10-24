/**---------------------------------------------------------------------------
 *   @file        usb4_ctrl_iface.cpp
 *
 *   @brief   
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include <Usb4Utils.h>
#include <Usb4Log.h>

//#include "VVDRV_usb4_cm.h"

#include "usb4_mem.h"
#include "usb4_ctrl_iface.h"
#include "usb4_HIA.h"

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/

#define USB4_CTRL_TRANSMIT_TIMEOUT (1000)

/* --------------------------------------------------------------------------
 * Static Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Static Functions
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Functions
 *--------------------------------------------------------------------------*/

void Usb4CtrlIfaceInit(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, usb4_hia_ctx_t* hia_ctx)
{
  ctrl_iface_ctx->m_HIA = hia_ctx;
//  m_sndXfer(), // {};
//  m_rcvXfer(), // {};
  ctrl_iface_ctx->m_rcvXferIndexToProcess = 0;
  ctrl_iface_ctx->m_numRcvXferToProcess = 0;
//  m_xferStatus(),
  ctrl_iface_ctx->m_blockISRInSend = TRUE;
  ctrl_iface_ctx->m_transmitAck = TRUE;
  ctrl_iface_ctx->m_blockedAckCounter = 0;
//  m_blockedNotificationsTable(), //{}
  ctrl_iface_ctx->m_txData = NULL;
  ctrl_iface_ctx->m_sequenceNumberRead = 0;
  ctrl_iface_ctx->m_sequenceNumberWrite = 0;
//  ctrl_iface_ctx->USB4_cp_error_counters(),// {},
//  m_rxPacket(),
//  m_rxRacketDeferred(), // {},
//  m_deferredData(), // {},
  ctrl_iface_ctx->m_nextFreeDefPacket = 0;
  ctrl_iface_ctx->m_currentDefPacket = 0;
  ctrl_iface_ctx->m_bProcessedDeferredPacket = FALSE;
//  m_pLogger = usb4_cm_logger_ctx;
//  m_txPacket()

  // usb4_mem_memset(ctrl_iface_ctx->m_blockedNotificationsTable, 0x0, sizeof(ctrl_iface_ctx->m_blockedNotificationsTable));
  // usb4_mem_memset((UINT8*)(ctrl_iface_ctx->m_sndXfer), 0, sizeof(ctrl_iface_ctx->m_sndXfer));
  // usb4_mem_memset((UINT8*)(ctrl_iface_ctx->m_rcvXfer), 0, sizeof(ctrl_iface_ctx->m_rcvXfer));
  // ClearAllErrors(); // usb4_mem_memset(ctrl_iface_ctx->USB4_cp_error_counters)
  // usb4_mem_memset(&ctrl_iface_ctx->m_deferredData, 0x0, sizeof(ctrl_iface_ctx->m_deferredData));
}


int Usb4CtrlIfaceEnable(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT8* baseAddress)
{
  UINT32 i;
  {
    USB4_hi_ring_cfg ringCfg;

    ringCfg.mode = USB4_HI_RING_MODE_RAW;
    ringCfg.sof_pdf_bmsk = 0x0;
    ringCfg.eof_pdf_bmsk = 0x0;

    ringCfg.b_e2e_flow_ontrol_enabled = FALSE;
    ringCfg.b_no_snoop_flag = FALSE;
    ringCfg.b_ring_valid = TRUE; // enable the ring
    ringCfg.rcv_transmit_e2e_hopid = 0x0; // for receieve ring only if b_e2e_flow_ontrol_enabled
    ringCfg.rcv_data_buffer_size_bytes = USB4_CONTROL_DESCRIPTOR_MAX_SIZE;
    ringCfg.ring_size = USB4_CONTROL_TRANSMIT_RING_SIZE;
    USB4_ASSERT(0 == Usb4HiaConfigRing(ctrl_iface_ctx->m_HIA, 0, USB4_HI_RING_TYPE_TRANSMIT, &ringCfg));
    ringCfg.ring_size = USB4_CONTROL_RECEIVE_RING_SIZE;
    USB4_ASSERT(0 == Usb4HiaConfigRing(ctrl_iface_ctx->m_HIA, 0, USB4_HI_RING_TYPE_RECEIVE, &ringCfg));

    usb4_mem_memset((UINT8*)(&ctrl_iface_ctx->m_rcvXfer), 0, sizeof(ctrl_iface_ctx->m_rcvXfer));
    ctrl_iface_ctx->m_rcvXferIndexToProcess = 0;
    ctrl_iface_ctx->m_numRcvXferToProcess = 0;
    usb4_mem_memset((UINT8*)(&ctrl_iface_ctx->m_sndXfer), 0, sizeof(ctrl_iface_ctx->m_sndXfer));

    for (i = 0; i < USB4_CONTROL_RECEIVE_BUFFERS; i++)
    {
      //Init and allocate
      ctrl_iface_ctx->m_rcvXfer[i].ringIdx = 0;
      ctrl_iface_ctx->m_rcvXfer[i].size_bytes = USB4_CONTROL_DESCRIPTOR_MAX_SIZE; /* transfer size bytes */
      ctrl_iface_ctx->m_rcvXfer[i].timeout_ms = 0; /* timeout to wait for blocking transfers */
      ctrl_iface_ctx->m_rcvXfer[i].buff.size_bytes = ctrl_iface_ctx->m_rcvXfer[i].size_bytes;
      USB4_ASSERT(0 == usb4_mem_dma_alloc(&ctrl_iface_ctx->m_rcvXfer[i].buff));
      ctrl_iface_ctx->m_rcvXfer[i].sof_pdf = 0; /* sof should match ring configuration */
      ctrl_iface_ctx->m_rcvXfer[i].eof_pdf = 0; /* eof should match ring configuration */
      ctrl_iface_ctx->m_rcvXfer[i].rs = TRUE; /* request status */
      ctrl_iface_ctx->m_rcvXfer[i].ie = TRUE; /* interrupt enable */
      ctrl_iface_ctx->m_rcvXfer[i].offset = 0; /* transfer offset from buffer */
      ctrl_iface_ctx->m_rcvXfer[i].bInUseBySW = FALSE;
      ctrl_iface_ctx->m_rcvXfer[i].bReferenceDone = FALSE;
      USB4_ASSERT(0 == Usb4HiaQueueReceive(ctrl_iface_ctx->m_HIA, &ctrl_iface_ctx->m_rcvXfer[i]));
    }
    for (i = 0; i < USB4_CONTROL_SEND_BUFFERS; i++)
    {
      ctrl_iface_ctx->m_sndXfer[i].buff.size_bytes = USB4_CONTROL_DESCRIPTOR_MAX_SIZE;
      USB4_ASSERT(0 == usb4_mem_dma_alloc(&ctrl_iface_ctx->m_sndXfer[i].buff));

    }
  }


  ctrl_iface_ctx->m_sequenceNumberRead = 0;
  ctrl_iface_ctx->m_sequenceNumberWrite = 0;

  Usb4CtrlPacketInit(&ctrl_iface_ctx->m_txPacket);
  Usb4CtrlPacketInit(&ctrl_iface_ctx->m_rxPacket);

  for (i = 0; i < USB4_NUMBER_OF_DEFERRED_PACKETS; i++)
  {
    Usb4CtrlPacketInit(&ctrl_iface_ctx->m_rxRacketDeferred[i]);
  }
  ctrl_iface_ctx->m_bProcessedDeferredPacket = FALSE;
  ctrl_iface_ctx->m_nextFreeDefPacket = 0;
  ctrl_iface_ctx->m_currentDefPacket = 0;
  {
    UINT32 mask = 1<<3; /* RX ring 0 */
    USB4_ASSERT(0 == Usb4HiaSetIntMaskSet(ctrl_iface_ctx->m_HIA, mask));
    USB4_ASSERT(0 == Usb4HiaGetIntMask(ctrl_iface_ctx->m_HIA, &mask)); /* Validation inside */
  }

  USB4_ASSERT(0 == Usb4HiaReceive(ctrl_iface_ctx->m_HIA, 0, USB4_CONTROL_RECEIVE_BUFFERS));
  return 0;
};

int Usb4CtrlIfaceReConfigure(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_ctrl_ring_cfg* pCtrlRingCfg)
{
  UINT32 i;
  USB4_ASSERT(NULL != pCtrlRingCfg);
  USB4_ASSERT(pCtrlRingCfg->numDescRx >= USB4_CONTROL_RECEIVE_BUFFERS)
  USB4_ASSERT(0 == Usb4HiaChangeRingSizeConfig(ctrl_iface_ctx->m_HIA, pCtrlRingCfg->numDescRx, 0, USB4_HI_RING_TYPE_RECEIVE));

//  usb4_mem_memset((UINT8*)(&ctrl_iface_ctx->m_rcvXfer), 0, sizeof(ctrl_iface_ctx->m_rcvXfer));
  ctrl_iface_ctx->m_rcvXferIndexToProcess = 0;
  ctrl_iface_ctx->m_numRcvXferToProcess = 0;

  for (i = 0; i < USB4_CONTROL_RECEIVE_BUFFERS; i++)
  {
    //Init but not allocate, since already allocated
    ctrl_iface_ctx->m_rcvXfer[i].ringIdx = 0;
//    ctrl_iface_ctx->m_rcvXfer[i].size_bytes = USB4_CONTROL_DESCRIPTOR_MAX_SIZE; /* transfer size bytes */
    ctrl_iface_ctx->m_rcvXfer[i].timeout_ms = 0; /* timeout to wait for blocking transfers */
//    ctrl_iface_ctx->m_rcvXfer[i].buff.size_bytes = ctrl_iface_ctx->m_rcvXfer[i].size_bytes;
//    USB4_ASSERT(0 == usb4_mem_dma_alloc(&ctrl_iface_ctx->m_rcvXfer[i].buff));
    ctrl_iface_ctx->m_rcvXfer[i].sof_pdf = 0; /* sof should match ring configuration */
    ctrl_iface_ctx->m_rcvXfer[i].eof_pdf = 0; /* eof should match ring configuration */
    ctrl_iface_ctx->m_rcvXfer[i].rs = TRUE; /* request status */
    ctrl_iface_ctx->m_rcvXfer[i].ie = TRUE; /* interrupt enable */
    ctrl_iface_ctx->m_rcvXfer[i].offset = 0; /* transfer offset from buffer */
    ctrl_iface_ctx->m_rcvXfer[i].bInUseBySW = FALSE;
    ctrl_iface_ctx->m_rcvXfer[i].bReferenceDone = FALSE;
    USB4_ASSERT(0 == Usb4HiaQueueReceive(ctrl_iface_ctx->m_HIA, &ctrl_iface_ctx->m_rcvXfer[i]));
  }
  USB4_ASSERT(0 == Usb4HiaReceive(ctrl_iface_ctx->m_HIA, 0, USB4_CONTROL_RECEIVE_BUFFERS));

  return 0;
}

int Usb4CtrlIfaceUnInit(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  UINT32 i;
  USB4_ASSERT(0 == Usb4HiaStopRing(ctrl_iface_ctx->m_HIA, 0, USB4_HI_RING_TYPE_TRANSMIT, USB4_HI_RING_STOP_TIMEOUT_MS));
  USB4_ASSERT(0 == Usb4HiaStopRing(ctrl_iface_ctx->m_HIA, 0, USB4_HI_RING_TYPE_RECEIVE, USB4_HI_RING_STOP_TIMEOUT_MS));

    for (i = 0; i < USB4_CONTROL_RECEIVE_BUFFERS; i++)
    {
      (void)usb4_mem_dma_free(&ctrl_iface_ctx->m_rcvXfer[i].buff);
    }
  usb4_mem_memset((UINT8*)(&ctrl_iface_ctx->m_rcvXfer), 0, sizeof(ctrl_iface_ctx->m_rcvXfer));
  ctrl_iface_ctx->m_rcvXferIndexToProcess = 0;
  ctrl_iface_ctx->m_numRcvXferToProcess = 0;

  for (i = 0; i < USB4_CONTROL_SEND_BUFFERS; i++)
  {
    (void)usb4_mem_dma_free(&ctrl_iface_ctx->m_sndXfer[i].buff);
  }
  usb4_mem_memset((UINT8*)(&ctrl_iface_ctx->m_sndXfer), 0, sizeof(ctrl_iface_ctx->m_sndXfer));

  ctrl_iface_ctx->m_sequenceNumberRead = 0;
  ctrl_iface_ctx->m_sequenceNumberWrite = 0;
  return 0;
};

int Usb4CtrlIfacePeek(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  UINT32 slotId = 0, num = 0, i;
  int rs;
  UINT32 rcvIndex;

  if (0 == ctrl_iface_ctx->m_numRcvXferToProcess)
  {
    rs = Usb4HiaPeek(ctrl_iface_ctx->m_HIA, 0, &slotId, &num);
    if (0 == rs)
    {
      for (i = 0; i < USB4_CONTROL_RECEIVE_BUFFERS; i++)
      {
        if ((TRUE == ctrl_iface_ctx->m_rcvXfer[i].bInUseByHW)&&(ctrl_iface_ctx->m_rcvXfer[i].slotId == slotId))
        {
          ctrl_iface_ctx->m_rcvXferIndexToProcess = i;
          ctrl_iface_ctx->m_numRcvXferToProcess = num;
          break;
        }
      }
      for (i = 0; i < ctrl_iface_ctx->m_numRcvXferToProcess; i++)
      {
        rcvIndex = (ctrl_iface_ctx->m_rcvXferIndexToProcess + i) % USB4_CONTROL_RECEIVE_BUFFERS;
        if (TRUE != ctrl_iface_ctx->m_rcvXfer[rcvIndex].bInUseByHW)
        {
          USB4_ERROR_STACK(-1);
          goto ErrorHandling;
        }
        USB4_ASSERT(0 == Usb4HiaVerifyRecieved(ctrl_iface_ctx->m_HIA, ctrl_iface_ctx->m_rcvXfer + rcvIndex, &ctrl_iface_ctx->m_xferStatus));
        ctrl_iface_ctx->m_rcvXfer[rcvIndex].bInUseBySW = TRUE;
      }
    }
    else
    {
      return rs;
    }
  }

  /* Copy packet header, routing and addressing, but not data */
  if ((TRUE == ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].bInUseBySW)&&
      (FALSE == ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].bReferenceDone))
  {
    USB4_ASSERT(0 == Usb4CtrlPacketReferenceBufferToPacket(&ctrl_iface_ctx->m_rxPacket,
          ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].buff.vaddr + ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].offset,
          ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].size_bytes,
          ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].eof_pdf));
    ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].bReferenceDone = TRUE;
    return 0;
  }
ErrorHandling:
  return -1;
}

int Usb4CtrlIfaceProcessDeferred(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  if (ctrl_iface_ctx->m_currentDefPacket != ctrl_iface_ctx->m_nextFreeDefPacket)
  {
    ctrl_iface_ctx->m_rxPacket = ctrl_iface_ctx->m_rxRacketDeferred[ctrl_iface_ctx->m_currentDefPacket];
    ctrl_iface_ctx->m_rxPacket.m_packetData = ctrl_iface_ctx->m_rxRacketDeferred[ctrl_iface_ctx->m_currentDefPacket].m_packetData;
    Usb4CtrlPacketInit(&ctrl_iface_ctx->m_rxRacketDeferred[ctrl_iface_ctx->m_currentDefPacket]);
    ctrl_iface_ctx->m_bProcessedDeferredPacket = TRUE;
    ctrl_iface_ctx->m_currentDefPacket = (ctrl_iface_ctx->m_currentDefPacket + 1) % USB4_NUMBER_OF_DEFERRED_PACKETS;
    return 0;
  }
  return -1;
}

int Usb4CtrlIfacePop(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  if (ctrl_iface_ctx->m_bProcessedDeferredPacket)
  {
    ctrl_iface_ctx->m_bProcessedDeferredPacket = FALSE;
    return 0;
  }

  if (0 == ctrl_iface_ctx->m_numRcvXferToProcess)
  {
    return 0;
  }
  /* Pop a single descriptor at a time */
  USB4_ASSERT(TRUE == ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].bInUseBySW);
  USB4_ASSERT(TRUE == ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].bReferenceDone);
  USB4_ASSERT(ctrl_iface_ctx->m_numRcvXferToProcess > 0);
  ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].bInUseByHW = FALSE;
  ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].size_bytes = USB4_CONTROL_DESCRIPTOR_MAX_SIZE; /* transfer size bytes */
  ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].sof_pdf = 0; /* sof should match ring configuration */
  ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].eof_pdf = 0; /* eof should match ring configuration */
  ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].rs = TRUE; /* request status */
  ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].ie = TRUE; /* interrupt enable */
  ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].bInUseBySW = FALSE;
  ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess].bReferenceDone = FALSE;
  USB4_ASSERT(0 == Usb4HiaQueueReceive(ctrl_iface_ctx->m_HIA, &ctrl_iface_ctx->m_rcvXfer[ctrl_iface_ctx->m_rcvXferIndexToProcess]));
  USB4_ASSERT(0 == Usb4HiaReceive(ctrl_iface_ctx->m_HIA, 0, 1));
  ctrl_iface_ctx->m_rcvXferIndexToProcess = (ctrl_iface_ctx->m_rcvXferIndexToProcess + 1) % USB4_CONTROL_RECEIVE_BUFFERS;
  ctrl_iface_ctx->m_numRcvXferToProcess--;
  return 0;
}

int Usb4CtrlIfacePostPacketToTX(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  UINT32 i;
  UINT8* dataBuffer = NULL;
  UINT32 dataLength = 0;
  USB4_hi_xfer* pSndXfr = NULL;

  for (i = 0; i < USB4_CONTROL_SEND_BUFFERS; i++)
  {
    if ((FALSE == ctrl_iface_ctx->m_sndXfer[i].bInUseByHW) && (FALSE == ctrl_iface_ctx->m_sndXfer[i].bInUseBySW))
    {
      pSndXfr = ctrl_iface_ctx->m_sndXfer + i;
      break;
    }
  }

  USB4_ASSERT(NULL != pSndXfr); /* No free TX XFR, so wait */
  USB4_ASSERT(pSndXfr->offset < pSndXfr->buff.size_bytes);
  dataBuffer = pSndXfr->buff.vaddr + pSndXfr->offset;
  dataLength = pSndXfr->buff.size_bytes;
  USB4_ASSERT(0 == Usb4CtrlPacketCopyPacketToBuffer(&ctrl_iface_ctx->m_txPacket, dataBuffer, &dataLength));

  pSndXfr->size_bytes = dataLength;
  pSndXfr->eof_pdf = Usb4CtrlPacketGetPDF(&ctrl_iface_ctx->m_txPacket);

  USB4_ASSERT(0 == Usb4HiaQueueTransmit(ctrl_iface_ctx->m_HIA, pSndXfr)); /* Update the state of the TX ring */
    if (FALSE == pSndXfr->bPostingPostponed)
    {
      USB4_ASSERT(0 == Usb4HiaTransmit(ctrl_iface_ctx->m_HIA, 0, 1, 0));
      //TODO: Optimize to check only once all free transfers were exhausted
      USB4_ASSERT(0 == Usb4HiaWaitTransmited(ctrl_iface_ctx->m_HIA, 0, USB4_CTRL_TRANSMIT_TIMEOUT));
      USB4_ASSERT(0 == Usb4HiaVerifyTransmited(ctrl_iface_ctx->m_HIA, pSndXfr, &ctrl_iface_ctx->m_xferStatus));
    }
  return 0;
}


int Usb4CtrlIfaceVerifyTransmissionComplete(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  USB4_hi_xfer *pSndXfr;
  UINT32 i;
  for (i = 0; i < USB4_CONTROL_SEND_BUFFERS; i++)
  {
    pSndXfr = ctrl_iface_ctx->m_sndXfer + i;
    if (pSndXfr->bInUseByHW)
    {
      USB4_ASSERT(0 == Usb4HiaVerifyTransmited(ctrl_iface_ctx->m_HIA, pSndXfr, &ctrl_iface_ctx->m_xferStatus));
      USB4_ASSERT(0 == pSndXfr->bInUseByHW);
    }
  }
  return 0;
}

int Usb4CtrlIfaceSendAck(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  usb4_control_packet_t *ackPckt;
  usb4_control_packet_t *notifPckt;
  USB4_cpDescriptorType  rxDescType=USB4_cpDescriptorType_UNKNOWN_DESCRIPTOR;

  notifPckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);
  USB4_ASSERT_MSG(0x80000000 & notifPckt->routeStringHigh, "Received packet with CM bit clear");

    ackPckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  ackPckt->routeStringLow = notifPckt->routeStringLow;
  ackPckt->routeStringHigh = (notifPckt->routeStringHigh & 0x7FFFFFFF);

  USB4_ASSERT(0 == Usb4CtrlIfaceGetType(ctrl_iface_ctx, &rxDescType));
  switch(rxDescType)
  {
    case USB4_cpDescriptorType_NOTIFICATION:
      USB4_ASSERT(0 == Usb4CtrlPacketAssignPDF(&ctrl_iface_ctx->m_txPacket, 0x4));
      break;
    case USB4_cpDescriptorType_HOT_PLUG_EVENT:
      USB4_ASSERT(0 == Usb4CtrlPacketAssignPDF(&ctrl_iface_ctx->m_txPacket, 0x3));
      ackPckt->controlData.notificationPacket.rsvd = 0;
      ackPckt->controlData.notificationPacket.eventCode = USB4_cpNotificationEvent_HP_ACK;
      ackPckt->controlData.notificationPacket.adapterNum =
        notifPckt->controlData.hotPlugEventPacket.adapterNum;
      if (notifPckt->controlData.hotPlugEventPacket.UPG)
      {
        /* Acknowledge Plug-Out */
        ackPckt->controlData.notificationPacket.PG = 0x3;
        // USB4_LOG_INFO("=====ACK PLG-OUT routeLow: 0x%08X adapter: 0x%02X\n", 
        //    ackPckt->routeStringLow, ackPckt->controlData.notificationPacket.adapterNum);
        Usb4Log2(USB4_LOG_CM, Usb4CtrlIfaceSendAckPlgOut__Params__RouteLow_Adapter, 0, ackPckt->routeStringLow, ackPckt->controlData.notificationPacket.adapterNum);
      }
      else
      {
        /* Acknowledge Plug-In */
        ackPckt->controlData.notificationPacket.PG = 0x2;
        // USB4_LOG_INFO("=====ACK PLG-IN routeLow: 0x%08X adapter: 0x%02X\n", 
        //     ackPckt->routeStringLow, ackPckt->controlData.notificationPacket.adapterNum);
        Usb4Log2(USB4_LOG_CM, Usb4CtrlIfaceSendAckPlgIn__Params__RouteLow_Adapter, 0, ackPckt->routeStringLow, ackPckt->controlData.notificationPacket.adapterNum);
      }
      break;
    default:
      USB4_ASSERT_MSG(0,
          "Wrong header in the current RX packet");
      break;
  }

  /* Block error notification */
  if (USB4_cpDescriptorType_NOTIFICATION == rxDescType)
  {   
    BOOLEAN isBlocked;
    USB4_cpNotificationEvent eventCode;

    eventCode = (USB4_cpNotificationEvent)(notifPckt->controlData.notificationPacket.eventCode);
    int result = Usb4CtrlIfaceIsNotificationBlocked(ctrl_iface_ctx, eventCode, &isBlocked);
    USB4_ASSERT(0 == result);

    if (!isBlocked)
    {
      USB4_ASSERT(0 == Usb4CtrlIfacePostPacketToTX(ctrl_iface_ctx));
    }
    else
    {
      /*Count the number of blocked events */
      ctrl_iface_ctx->m_blockedAckCounter++;
    }
  }
  else
  {
    USB4_ASSERT(0 == Usb4CtrlIfacePostPacketToTX(ctrl_iface_ctx));
  }
  return 0;
}



int Usb4CtrlIfaceBlockNotification(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpNotificationEvent notification_id)
{
  ctrl_iface_ctx->m_blockedNotificationsTable[notification_id] = TRUE;
  return 0;
}

int Usb4CtrlIfaceUnblockNotifcation(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpNotificationEvent notification_id)
{
  ctrl_iface_ctx->m_blockedNotificationsTable[notification_id] = FALSE;
  return 0;
}

int Usb4CtrlIfaceUnblockAllNotifcations(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  for (UINT32 i = 0; i  < ARR_SIZE(ctrl_iface_ctx->m_blockedNotificationsTable); i++)
  {
    ctrl_iface_ctx->m_blockedNotificationsTable[i] = FALSE;
  }
  return 0;
}

int Usb4CtrlIfaceIsNotificationBlocked(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpNotificationEvent notification_id,
    BOOLEAN* pResult)
{
  *pResult = (ctrl_iface_ctx->m_blockedNotificationsTable[notification_id] == TRUE);
  return 0;
}

/*-----------------------------------------------------------------------------*/

int Usb4CtrlIfaceSendHotPlugDummyPacket(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  usb4_control_packet_t *hotPlugDummyPacket;

  hotPlugDummyPacket = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  USB4_ASSERT(0 == Usb4CtrlPacketAssignPDF(&ctrl_iface_ctx->m_txPacket, 0x5));

  hotPlugDummyPacket->routeStringLow = 0x0;
  hotPlugDummyPacket->routeStringHigh = 0x0;

  hotPlugDummyPacket->controlData.hotPlugEventPacket.adapterNum = 0x0;
  hotPlugDummyPacket->controlData.hotPlugEventPacket.UPG = 0x0;

  USB4_ASSERT(0 == Usb4CtrlIfacePostPacketToTX(ctrl_iface_ctx));
  Usb4CtrlPacketInit(&ctrl_iface_ctx->m_txPacket);
  return 0;
}

/*-----------------------------------------------------------------------------*/

int Usb4CtrlIfaceSendPreFilledCtrlPacket(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT8* dataBuffer, UINT32 dataLength)
{
  usb4_control_packet_ctx_t* pPkt;
  USB4_ASSERT(sizeof(usb4_control_packet_ctx_t)==dataLength);
  pPkt = (usb4_control_packet_ctx_t*)(dataBuffer);
  ctrl_iface_ctx->m_txPacket = *pPkt;
  USB4_ASSERT(0 == Usb4CtrlIfacePostPacketToTX(ctrl_iface_ctx));
  Usb4CtrlPacketInit(&ctrl_iface_ctx->m_txPacket);
  return 0;
}

/*-----------------------------------------------------------------------------*/

int Usb4CtrlIfaceGetType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpDescriptorType* type)
{
  USB4_ASSERT(type != NULL);
  switch(Usb4CtrlPacketGetPDF(&ctrl_iface_ctx->m_rxPacket))
  {
    case 1:
      *type = USB4_cpDescriptorType_READ_RESPONSE;
      break;
    case 2:
      *type = USB4_cpDescriptorType_WRITE_RESPONSE;
      break;
    case 3:
      *type = USB4_cpDescriptorType_NOTIFICATION;
      break;
    case 4:
      *type = USB4_cpDescriptorType_NOTIFICATION_ACK;
      break;
    case 5:
      *type = USB4_cpDescriptorType_HOT_PLUG_EVENT;
      break;
    case 6:
      *type = USB4_cpDescriptorType_INTERDOMAIN_REQUEST;
      break;
    case 7:
      *type = USB4_cpDescriptorType_INTERDOMAIN_RESPONSE;
      break;
    }
  return 0;
};

int Usb4CtrlIfaceGetInterdomainType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpInterdomainPacketType* type)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);
  USB4_ASSERT(NULL != type);
  *type = (USB4_cpInterdomainPacketType)(pckt->controlData.interdomainReqResp.packetType);
  return 0;
}

int Usb4CtrlIfaceSetType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpDescriptorType type)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  ctrl_iface_ctx->m_txPacket.m_packetData = NULL;
  ctrl_iface_ctx->m_txPacket.m_packetDataLength = 0;
  switch (type)
  {
    case USB4_cpDescriptorType_READ_REQUEST:
      USB4_ASSERT(0 == Usb4CtrlPacketAssignPDF(&ctrl_iface_ctx->m_txPacket, 1));
      pckt->controlData.readWriteRequest.rsvd = 0;
      break;
    case USB4_cpDescriptorType_WRITE_REQUEST:
      USB4_ASSERT(0 == Usb4CtrlPacketAssignPDF(&ctrl_iface_ctx->m_txPacket, 2));
      pckt->controlData.readWriteRequest.rsvd = 0;
      break;
    case USB4_cpDescriptorType_NOTIFICATION_ACK:
      USB4_ASSERT(0 == Usb4CtrlPacketAssignPDF(&ctrl_iface_ctx->m_txPacket, 4));
      pckt->controlData.notificationPacket.rsvd = 0;
      break;
    case USB4_cpDescriptorType_INTERDOMAIN_REQUEST:
      USB4_ASSERT(0 == Usb4CtrlPacketAssignPDF(&ctrl_iface_ctx->m_txPacket, 6));
      pckt->controlData.interdomainReqResp.XDDP_UUID0 = 0xB638D70E;
      pckt->controlData.interdomainReqResp.XDDP_UUID1 = 0x42FF40BB;
      pckt->controlData.interdomainReqResp.XDDP_UUID2 = 0x97C290E2;
      pckt->controlData.interdomainReqResp.XDDP_UUID3 = 0xC0B2FF07;
      pckt->controlData.interdomainReqResp.rsvd = 0;
      pckt->controlData.interdomainReqResp.rsvd1 = 0;
      break;
    case USB4_cpDescriptorType_INTERDOMAIN_RESPONSE:
      USB4_ASSERT(0 == Usb4CtrlPacketAssignPDF(&ctrl_iface_ctx->m_txPacket, 7));
      pckt->controlData.interdomainReqResp.XDDP_UUID0 = 0xB638D70E;
      pckt->controlData.interdomainReqResp.XDDP_UUID1 = 0x42FF40BB;
      pckt->controlData.interdomainReqResp.XDDP_UUID2 = 0x97C290E2;
      pckt->controlData.interdomainReqResp.XDDP_UUID3 = 0xC0B2FF07;
      pckt->controlData.interdomainReqResp.rsvd = 0;
      pckt->controlData.interdomainReqResp.rsvd1 = 0;
      break;
    default:
      USB4_ASSERT_MSG(0, "Unsupported descriptor type");
  }
  return 0;
};

int Usb4CtrlIfaceSetInterdomainType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpInterdomainPacketType type)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  pckt->controlData.interdomainReqResp.packetType = (UINT32)(type);
  return 0;
}

int Usb4CtrlIfaceSetRoute(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT64 route)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  pckt->routeStringLow = USB4_LOWER32(route);
  pckt->routeStringHigh = USB4_UPPER32(route);
  return 0;
}

int Usb4CtrlIfaceSetAddress(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32 address)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  /* Same for read and write requests */
  pckt->controlData.readWriteRequest.address = address;
  return 0;
}

int Usb4CtrlIfaceGetTxAddress(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* address)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  /* Same for read and write requests */
  *address = pckt->controlData.readWriteRequest.address;
  return 0;
}

int Usb4CtrlIfaceSetAdapter(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32 adapter)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  /* Same for read and write requests */
  pckt->controlData.readWriteRequest.adapterNum = adapter;
  return 0;
}

int Usb4CtrlIfaceSetCS(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpConfigSpace eCS)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);

  /* Same for read and write requests */
  pckt->controlData.readWriteRequest.configurationSpace = 
    (UINT32)(eCS);

  return 0;
}

int Usb4CtrlIfaceSetSN(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32 SN)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  /* Same for read and write requests */
  pckt->controlData.readWriteRequest.sequenceNumber = SN;
  return 0;
}

/**
 * @brief verifies 
 * @return 0 valid, other for failure 
 **/
static int Usb4CtrlIfaceverifyTransfer(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, const usb4_ctrl_iface_trn* pTrn)
{
  switch (pTrn->type)
  {
    case USB4_cpDescriptorType_READ_REQUEST:
    case USB4_cpDescriptorType_WRITE_REQUEST:
      break;

    case USB4_cpDescriptorType_NOTIFICATION:
    case USB4_cpDescriptorType_HOT_PLUG_EVENT:
    case USB4_cpDescriptorType_INTERDOMAIN_REQUEST:
    case USB4_cpDescriptorType_INTERDOMAIN_RESPONSE:
    case USB4_cpDescriptorType_WRITE_RESPONSE:
    case USB4_cpDescriptorType_READ_RESPONSE:
    case USB4_cpDescriptorType_NOTIFICATION_ACK:
    case USB4_cpDescriptorType_UNKNOWN_DESCRIPTOR:
    default:
      USB4_ERROR_STACK_MSG(-1, "Invalid type");
      return -1;
  }

  if ((0x0 == pTrn->size_bytes) || (NULL == pTrn->pBuff))
  {
    USB4_ERROR_STACK_MSG(-1, "Ivalid buffer (or size)");
    return -1;
  }

  return 0;
}

int Usb4CtrlIfaceTransfer(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, usb4_ctrl_iface_trn* pTrn)
{
  UINT8* pData = NULL;

  if (0 != Usb4CtrlIfaceverifyTransfer(ctrl_iface_ctx, pTrn))
  {
    USB4_ERROR_STACK(-1);
    return -1;
  }

  pData = (USB4_cpDescriptorType_READ_REQUEST == pTrn->type) ? 
    NULL : pTrn->pBuff;
  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(ctrl_iface_ctx, pTrn->type));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(ctrl_iface_ctx, pTrn->address));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(ctrl_iface_ctx, pTrn->adapterNum));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(ctrl_iface_ctx, pTrn->topologyId));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(ctrl_iface_ctx, pTrn->cs));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(ctrl_iface_ctx, pData, pTrn->size_bytes));

  if(0 != Usb4CtrlIfaceSend(ctrl_iface_ctx, pTrn->timeout_us))
  {
    USB4_ERROR_STACK(-1);
    return -1;
  }

  if (0 == pTrn->timeout_us)
  {
    return 0; // This is a non blocking transfer, exit
  }

  // if timeout > 0 send will do the peek and we can do get
  if (USB4_cpDescriptorType_READ_REQUEST == pTrn->type)
  {    
    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(ctrl_iface_ctx, pTrn->pBuff, &pTrn->resp_bytes, pTrn->size_bytes));
    USB4_ASSERT(0 == Usb4CtrlIfacePop(ctrl_iface_ctx));
  }
  else if (USB4_cpDescriptorType_WRITE_REQUEST == pTrn->type)
  {
    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(ctrl_iface_ctx, NULL, &pTrn->resp_bytes, pTrn->size_bytes));
    USB4_ASSERT(0 == Usb4CtrlIfacePop(ctrl_iface_ctx));
    USB4_ASSERT_MSG(pTrn->resp_bytes == pTrn->size_bytes, "Didn't write a complete buffer");
  }

  return 0;
}

int Usb4CtrlIfaceSetData(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT8* data, UINT32 size_bytes)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  /* Same for read and write requests */
  pckt->controlData.readWriteRequest.readWriteDwords = (size_bytes+3)>>2;
  ctrl_iface_ctx->m_txPacket.m_packetData = data;
  if (NULL != data)
  {
    ctrl_iface_ctx->m_txPacket.m_packetDataLength = pckt->controlData.readWriteRequest.readWriteDwords<<2;
  }
  else
  {
    ctrl_iface_ctx->m_txPacket.m_packetDataLength =  0;

  }
  return 0;
}

int Usb4CtrlIfaceGetRoute(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT64* route)
{
  usb4_control_packet_t *pckt;

  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);
  USB4_ASSERT_MSG(0x80000000 & pckt->routeStringHigh, "Received packet with CM bit clear");
  *route = USB4_GET_UINT64(pckt->routeStringHigh & 0x7FFFFFFF, pckt->routeStringLow);
  return 0;
}

int Usb4CtrlIfaceGetAddress(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* address)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);
  *address = pckt->controlData.readWriteRequest.address;
  return 0;
}

int Usb4CtrlIfaceGetCS(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* CS)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);
  *CS = pckt->controlData.readWriteRequest.configurationSpace;
  return 0;
}

int Usb4CtrlIfaceGetSN(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* SN)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);
  *SN = pckt->controlData.readWriteRequest.sequenceNumber;
  return 0;
}

int Usb4CtrlIfaceGetAdapter(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* adapter)
{
  usb4_control_packet_t *pckt;
  USB4_cpDescriptorType desc_type=USB4_cpDescriptorType_UNKNOWN_DESCRIPTOR;

  USB4_ASSERT(0 == Usb4CtrlIfaceGetType(ctrl_iface_ctx, &desc_type));
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);

  switch (desc_type)
  {

    case USB4_cpDescriptorType_READ_RESPONSE:
    case USB4_cpDescriptorType_WRITE_RESPONSE:
      *adapter = pckt->controlData.readWriteRequest.adapterNum;
      break;
    case USB4_cpDescriptorType_NOTIFICATION:
    case USB4_cpDescriptorType_NOTIFICATION_ACK:
      *adapter = pckt->controlData.notificationPacket.adapterNum;
      break;
    case USB4_cpDescriptorType_HOT_PLUG_EVENT:
      *adapter = pckt->controlData.hotPlugEventPacket.adapterNum;
      break;
    case USB4_cpDescriptorType_INTERDOMAIN_REQUEST:
    case USB4_cpDescriptorType_INTERDOMAIN_RESPONSE:
      *adapter = 0;
      break;
    default:
      USB4_ASSERT(0);
      break;
  }
  return 0;
}

int Usb4CtrlIfaceGetUPG(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* UPG)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);
  *UPG = pckt->controlData.hotPlugEventPacket.UPG;
  return 0;
}

int Usb4CtrlIfaceGetData(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT8* data, UINT32* size_bytes, UINT32 max_size_bytes)
{
  usb4_control_packet_t *pckt;
  UINT32 dataLength;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);
  dataLength = MIN(pckt->controlData.readWriteRequest.readWriteDwords, max_size_bytes >> 2) << 2;
  if (NULL != data)
  {
    usb4_mem_memcpy(data, ctrl_iface_ctx->m_rxPacket.m_packetData, dataLength);
  }
  *size_bytes = dataLength;
  return 0;
};

int Usb4CtrlIfaceGetEventCode(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpNotificationEvent* event)
{
  usb4_control_packet_t *pckt;
  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);
  *event = (USB4_cpNotificationEvent)(pckt->controlData.notificationPacket.eventCode);
  return 0;
}

/*----------------------------------------------------*/

int Usb4CtrlIfaceVerifyReadWriteResponse(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, BOOLEAN *p_result)
{
  usb4_control_packet_t *pcktTx;
  usb4_control_packet_t *pcktRx;

  USB4_ASSERT(NULL != p_result);

  /* Set result to false by default */
  *p_result = FALSE;

  /* Get transmited packet */
  pcktTx = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);

  /* Get recieved packet */
  pcktRx = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);

  /* Verify route string */
  if ((pcktTx->routeStringHigh != (pcktRx->routeStringHigh & 0x7FFFFF))||
      (pcktTx->routeStringLow  != pcktRx->routeStringLow))
  {
    return 0; /* Not a match, but not an error either */
  }

  /* Verify address */
  USB4_ASSERT(pcktTx->controlData.readWriteRequest.address ==
      pcktRx->controlData.readWriteRequest.address);

  /* Verify write size */
  USB4_ASSERT(pcktTx->controlData.readWriteRequest.readWriteDwords ==
      pcktRx->controlData.readWriteRequest.readWriteDwords);

  /* Verify adapter number*/
  USB4_ASSERT(pcktTx->controlData.readWriteRequest.adapterNum ==
      pcktRx->controlData.readWriteRequest.adapterNum);

  /* Verify CS */
  USB4_ASSERT(pcktTx->controlData.readWriteRequest.configurationSpace ==
      pcktRx->controlData.readWriteRequest.configurationSpace);

  /* */
  USB4_ASSERT(pcktTx->controlData.readWriteRequest.sequenceNumber ==
      pcktRx->controlData.readWriteRequest.sequenceNumber);

  *p_result = TRUE;
  return 0;
}

/*----------------------------------------------------*/

BOOLEAN Usb4CtrlIfaceRxMatchesTx(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, BOOLEAN* p_bNotification)
{
  usb4_control_packet_t *pcktTx, *pcktRx;
  pcktTx = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  pcktRx = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_rxPacket);

  if ((1 == Usb4CtrlPacketGetPDF(&ctrl_iface_ctx->m_txPacket)) || (2 == Usb4CtrlPacketGetPDF(&ctrl_iface_ctx->m_txPacket)))
  {
    if ((Usb4CtrlPacketGetPDF(&ctrl_iface_ctx->m_txPacket) == Usb4CtrlPacketGetPDF(&ctrl_iface_ctx->m_rxPacket))&&
        (pcktTx->controlData.readWriteRequest.sequenceNumber ==
         pcktRx->controlData.readWriteRequest.sequenceNumber))
    {
      return TRUE;
    }
  }
  if ((6 == Usb4CtrlPacketGetPDF(&ctrl_iface_ctx->m_txPacket)) && (7 == Usb4CtrlPacketGetPDF(&ctrl_iface_ctx->m_rxPacket)) &&
      (pcktTx->controlData.interdomainReqResp.sequenceNumber ==
       pcktRx->controlData.interdomainReqResp.sequenceNumber))
  {
    return TRUE;
  }

  if (NULL != p_bNotification)
  {
    *p_bNotification = FALSE;

    if (3 == Usb4CtrlPacketGetPDF(&ctrl_iface_ctx->m_rxPacket)) /* USB4_cpDescriptorType_NOTIFICATION */
    {
      if (  (pcktRx->routeStringLow == pcktTx->routeStringLow)
          &&((pcktRx->routeStringHigh & 0x7FFFFFFF) == (pcktTx->routeStringHigh & 0x7FFFFFFF))
          && (pcktRx->controlData.notificationPacket.adapterNum == pcktTx->controlData.readWriteRequest.adapterNum))
      {
        *p_bNotification = TRUE;
      }
    }
  }
  return FALSE;
}
/*-----------------------------------------------------*/

int Usb4CtrlIfaceWaitForRxPacket(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT64 usTimeout)
{
  UINT32 timeout = 0;
  UINT32 step; /* Increment uSec; Don't use 1, sine entry to function takes a lot of time */
  usb4_utils_timer timer;
  timer.m_source = USB4_TIMER_SOURCE_QTIMER;

  USB4_ASSERT(0 != usTimeout);
  step = (usTimeout+9)/10;
  while ((0 != Usb4CtrlIfacePeek(ctrl_iface_ctx)) && (timeout < usTimeout))
  {
    usb4_timer_Sleep_us(&timer, step);
    timeout = timeout + step;
  }
  USB4_ASSERT(timeout < usTimeout);
  return 0;
}

int Usb4CtrlIfaceClearAllErrors(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  int i;
  for (i = 0; i < USB4_CP_ERR_NUMBER; ++i)
  {
    ctrl_iface_ctx->USB4_cp_error_counters[i] = 0;
  }

  return 0;
}

/*-----------------------------------------------------*/

int Usb4CtrlIfaceClearErrorsOfType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cp_errors error_type)
{
  USB4_ASSERT(error_type < USB4_CP_ERR_NUMBER);
  ctrl_iface_ctx->USB4_cp_error_counters[error_type] = 0;

  return 0;
}

/*-----------------------------------------------------*/

int Usb4CtrlIfaceGetErrorsOfType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cp_errors error_type,
    UINT32 *p_counter)
{
  USB4_ASSERT(error_type < USB4_CP_ERR_NUMBER);
  *p_counter = ctrl_iface_ctx->USB4_cp_error_counters[error_type];
  return 0;
}

/*-----------------------------------------------------*/

int Usb4CtrlIfaceHandleErrorNotifications(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, BOOLEAN* p_bNotification)
{
  USB4_cpDescriptorType desc_type=USB4_cpDescriptorType_UNKNOWN_DESCRIPTOR;
  USB4_cpNotificationEvent event;
  UINT64 router;
  UINT32 adapter;

  /* Check  for transaction  errors */
  USB4_ASSERT(0 == Usb4CtrlIfaceGetType(ctrl_iface_ctx, &desc_type));

    /* If the router recieved a notification */
    if (USB4_cpDescriptorType_NOTIFICATION == desc_type)
    {
      USB4_ASSERT(0 == Usb4CtrlIfaceGetEventCode(ctrl_iface_ctx, &event));

      if (NULL != p_bNotification)
      {
        *p_bNotification = TRUE;
      }

      USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(ctrl_iface_ctx, &router));
      USB4_ASSERT(0 == Usb4CtrlIfaceGetAdapter(ctrl_iface_ctx, &adapter));

      // USB4_LOG_INFO("Notification from: router(%llu) adapter(%d) ", (unsigned long long)(router), adapter);
      Usb4Log2(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotifications__Params__Router_Adapter, 0, (unsigned long long)(router), adapter);

      /* Check event type */
      switch (event)
      {
        /*---------------------------------------------------------*/
        /* (Router receives downstream packet (CM = 0) on its upstream adapter) and
           (TopologyId Valid bit  in router config space = 1) and
           (The adapter extracted from ToplogyId is disconnected or disabled)
           */
        case USB4_cpNotificationEvent_ERR_CONN:

          // USB4_LOG_INFO("USB4_cpNotificationEvent_ERR_CONN\n");
          Usb4Log(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRCONN__Info, 0);

          /* Increase error counter */
          ctrl_iface_ctx->USB4_cp_error_counters[USB4_CP_ERR_CONN]++;
          break;

          /*---------------------------------------------------------*/
          /*
             Scenario 1 (Alignment Lock Error)
             Adapter received a symbol with illegal Sync Bits value.

             Scenario 2 (Order Set Error)
             Adapter received 2 back-to-back symbols that are
             not part of an ordered Set defined in this specification
             and/or have an uncorrectable error in the SCR field.

             Scenario 3 (Timeout Error)
             Adapter did not transition from training state to
             CL0 state within tTrainingError after
             achieving Symbol alignment.

             Scenario 4 (De-skew Buffer Error)
             Skew is too large, resulting in overflow in the de
             skew buffer.

             Scenario 5 (RS-FEC Decoder Error)
             The RS-FEC decoder identified an uncorrectable error.

             Scenario 6 (RX Sync Timeout)
             While in LOCK1 sub-state of the training state, the
             receiver could not lock on Sync Bits for
             an implementation specific period of time.
             */
        case USB4_cpNotificationEvent_ERR_LINK:
          // USB4_LOG_INFO("USB4_cpNotificationEvent_ERR_LINK\n");
          Usb4Log(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRLINK__Info, 0);
          /* Increase error counter */
          ctrl_iface_ctx->USB4_cp_error_counters[USB4_CP_ERR_LINK]++;
          break;

          /*---------------------------------------------------------*/
          /*
             (Write or read request ) and
             (Address + Write size extend outside supported address range)
             */
        case USB4_cpNotificationEvent_ERR_ADDR:

          // USB4_LOG_INFO("USB4_cpNotificationEvent_ERR_ADDR\n");
          Usb4Log(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRADDR__Info, 0);
          /* Increase error counter */
          ctrl_iface_ctx->USB4_cp_error_counters[USB4_CP_ERR_ADDR]++;
          break;

          /*---------------------------------------------------------*/
          /*
             Scenario 1
             (Received control packet) and
             (It is a downstream packet (CM = 0)) and
             (Packet arrived on upstream adapter) and
             (TopologyID Valid = 1) and
             (Extracted adapter is a protocol adapter)

             Scenario 2
             (Read/Write request) and
             (adapter num > Max Adapter)
             */
        case USB4_cpNotificationEvent_ERR_ADP:

          // USB4_LOG_INFO("USB4_cpNotificationEvent_ERR_ADP\n");
          Usb4Log(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRADP__Info, 0);

          /* Increase error counter */
          ctrl_iface_ctx->USB4_cp_error_counters[USB4_CP_ERR_ADP]++;
          break;

          /*---------------------------------------------------------*/
          /*
             (Downstream Read/Write request (CM = 0)) and
             (Control packet arrived to a downstream adapter ) and
             (Upstream Adapter field != 0 in Router's CS) and
             (ToplogyId Valid = 1)
             */
        case USB4_cpNotificationEvent_ERR_ENUM:

          // USB4_LOG_INFO("USB4_cpNotificationEvent_ERR_ENUM\n");
          Usb4Log(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRENUM__Info, 0);

          /* Increase error counter */
          ctrl_iface_ctx->USB4_cp_error_counters[USB4_CP_ERR_ENUM]++;
          break;

          /*---------------------------------------------------------*/
          /*
             Scenario 1
             (Router is host) and
             (Downstream Read/Write request (CM = 0)) and
             (Control packet arrived to a downstream adapter ) and
             (Upstream Adapter field != 0 in Router's CS) and
             (ToplogyId Valid = 0 )
             */
        case USB4_cpNotificationEvent_ERR_NUA:

          // USB4_LOG_INFO("USB4_cpNotificationEvent_ERR_NUA\n");
          Usb4Log(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRNUA__Info, 0);

          /* Increase error counter */
          ctrl_iface_ctx->USB4_cp_error_counters[USB4_CP_ERR_NUA]++;
          break;

          /*---------------------------------------------------------*/
          /*
             Scenario 1 (write request)
             (Adapter num < Max Adapter) and
             (Length filed != [Write Size + 4] * 4])

             Scenario 2 (read request)
             (read size > 60)
             */
        case USB4_cpNotificationEvent_ERR_LEN:

          // USB4_LOG_INFO("USB4_cpNotificationEvent_ERR_LEN\n");
          Usb4Log(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRLEN__Info, 0);

          /* Increase error counter */
          ctrl_iface_ctx->USB4_cp_error_counters[USB4_CP_ERR_LEN]++;
          break;

          /*---------------------------------------------------------*/
          /*
             Ingress lane adapter detected uncorrectable HEC error
             */
        case USB4_cpNotificationEvent_ERR_HEC:

          // USB4_LOG_INFO("USB4_cpNotificationEvent_ERR_HEC\n");
          Usb4Log(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRHEC__Info, 0);

          /* Increase error counter */
          ctrl_iface_ctx->USB4_cp_error_counters[USB4_CP_ERR_HEC]++;
          break;

          /*---------------------------------------------------------*/
          /*
             Ingress adapter received packet on flow controlled path
             and the appropriate buffer has no space
             */
        case USB4_cpNotificationEvent_ERR_FC:

          // USB4_LOG_INFO("USB4_cpNotificationEvent_ERR_FC\n");
          Usb4Log(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRFC__Info, 0);

          /* Increase error counter */
          ctrl_iface_ctx->USB4_cp_error_counters[USB4_CP_ERR_FC]++;
          break;

          /*---------------------------------------------------------*/
          /*
             (None of USB4 lane adapters reaches CL0 within tTrainingAbort1/2 after entering training) and
             (Hot Plug Failure Indication capability is enabled)
             */
        case USB4_cpNotificationEvent_ERR_PLUG:

          // USB4_LOG_INFO("USB4_cpNotificationEvent_ERR_PLUG\n");
          Usb4Log(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRPLUG__Info, 0);

          /* Increase error counter */
          ctrl_iface_ctx->USB4_cp_error_counters[USB4_CP_ERR_PLUG]++;
          break;

          /*---------------------------------------------------------*/
          /*
             (Downstream Control packet (CM=0)) and
             (Arrived on upstream adapter) and
             (TopologyId Valid = 1) and
             (Extracted adapter is connected) and
             (Lock bit  = 1)
             */
        case USB4_cpNotificationEvent_ERR_LOCK:

          // USB4_LOG_INFO("USB4_cpNotificationEvent_ERR_LOCK\n");
          Usb4Log(USB4_LOG_CM, Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRLOCK__Info, 0);

          /* Increase error counter */
          ctrl_iface_ctx->USB4_cp_error_counters[USB4_CP_ERR_LOCK]++;
          break;

          /*---------------------------------------------------------*/

        default:
          break;
      }
    }
    else
    {
      if (NULL != p_bNotification)
      {
        *p_bNotification = FALSE;
      }
    }

  return 0;
}

/*-----------------------------------------------------*/
BOOLEAN Usb4CtrlIfaceRxIsDuplicateToDeferredPacket(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  UINT32 i;

  if (ctrl_iface_ctx->m_currentDefPacket < ctrl_iface_ctx->m_nextFreeDefPacket)
  {
    for (i = ctrl_iface_ctx->m_currentDefPacket; i < ctrl_iface_ctx->m_nextFreeDefPacket ; i++)
    {
      // if(ctrl_iface_ctx->m_rxRacketDeferred[i] == ctrl_iface_ctx->m_rxPacket) Operator overloading
      if (Usb4CtrlPacketIsPacketSame(&ctrl_iface_ctx->m_rxRacketDeferred[i], &ctrl_iface_ctx->m_rxPacket))
      {
        return TRUE;
      }
    }
  }
  else
  {
    for (i = ctrl_iface_ctx->m_currentDefPacket; i < USB4_NUMBER_OF_DEFERRED_PACKETS ; i++)
    {
      // if(ctrl_iface_ctx->m_rxRacketDeferred[i] == ctrl_iface_ctx->m_rxPacket) Operator overloading
      if (Usb4CtrlPacketIsPacketSame(&ctrl_iface_ctx->m_rxRacketDeferred[i], &ctrl_iface_ctx->m_rxPacket))
      {
        return TRUE;
      }
    }
    for (i = 0; i < ctrl_iface_ctx->m_nextFreeDefPacket ; i++)
    {
      // if(ctrl_iface_ctx->m_rxRacketDeferred[i] == ctrl_iface_ctx->m_rxPacket) Operator overloading
      if (Usb4CtrlPacketIsPacketSame(&ctrl_iface_ctx->m_rxRacketDeferred[i], &ctrl_iface_ctx->m_rxPacket))
      {
        return TRUE;
      }
    }
  }

  return FALSE;
}

/*-----------------------------------------------------*/
int Usb4CtrlIfaceDeferPacketProcessing(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  UINT32 i;

  if (!Usb4CtrlIfaceRxIsDuplicateToDeferredPacket(ctrl_iface_ctx))
  {
    i = (ctrl_iface_ctx->m_nextFreeDefPacket + 1) % USB4_NUMBER_OF_DEFERRED_PACKETS;
    USB4_ASSERT_MSG(i != ctrl_iface_ctx->m_currentDefPacket, "No free space to store deferred packets");
    ctrl_iface_ctx->m_rxRacketDeferred[ctrl_iface_ctx->m_nextFreeDefPacket] = ctrl_iface_ctx->m_rxPacket;
    if (ctrl_iface_ctx->m_rxPacket.m_packetDataLength > 0)
    {
      USB4_ASSERT(USB4_CONTROL_DESCRIPTOR_MAX_SIZE >= ctrl_iface_ctx->m_rxPacket.m_packetDataLength);
      usb4_mem_memcpy(&ctrl_iface_ctx->m_deferredData[ctrl_iface_ctx->m_nextFreeDefPacket], ctrl_iface_ctx->m_rxPacket.m_packetData, ctrl_iface_ctx->m_rxPacket.m_packetDataLength);
      ctrl_iface_ctx->m_rxRacketDeferred[ctrl_iface_ctx->m_nextFreeDefPacket].m_packetData = ctrl_iface_ctx->m_deferredData[ctrl_iface_ctx->m_nextFreeDefPacket];
    }
    ctrl_iface_ctx->m_nextFreeDefPacket = i;
  }
  USB4_ASSERT(0 == Usb4CtrlIfacePop(ctrl_iface_ctx));

  return 0;
}
/*-----------------------------------------------------*/

int Usb4CtrlIfaceSend(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT64 usTimeout)
{
  usb4_control_packet_t *pckt;
  UINT32 timeout = 0, step;
  UINT32 pdf;
  BOOLEAN bErrorNotification;
  usb4_utils_timer timer;
  timer.m_source = USB4_TIMER_SOURCE_QTIMER;
  //    UINT32 cloreIndex = -1;

  //    if (NULL != ctrl_iface_ctx->m_pLogger)
  //    {
  //        USB4_ASSERT(0 == ctrl_iface_ctx->m_pLogger->PrintUcEvents());
  //        cloreIndex = ctrl_iface_ctx->m_pLogger->GetCoreIndex();
  //    }

  pckt = Usb4CtrlPacketGetControlPacket(&ctrl_iface_ctx->m_txPacket);
  pdf = Usb4CtrlPacketGetPDF(&ctrl_iface_ctx->m_txPacket);
  if (1 == pdf)
  {
    pckt->controlData.readWriteRequest.sequenceNumber = ctrl_iface_ctx->m_sequenceNumberRead;
    /* Read/Write request has to have sequence number updated */
    ctrl_iface_ctx->m_sequenceNumberRead = (ctrl_iface_ctx->m_sequenceNumberRead + 1) & 0x3;
    //        USB4_LOG_INFO_BLUE("TX RD [%u]: PDF=%u, AN%u, CS%u, addr=0x%x, lenDW=0x%x\n",
    //                cloreIndex, pdf,
    //                pckt->controlData.readWriteRequest.adapterNum,
    //                pckt->controlData.readWriteRequest.configurationSpace,
    //                pckt->controlData.readWriteRequest.address,
    //                pckt->controlData.readWriteRequest.readWriteDwords);
  }
  else if (2 == pdf)
  {
    pckt->controlData.readWriteRequest.sequenceNumber = ctrl_iface_ctx->m_sequenceNumberWrite;
    /* Read/Write request has to have sequence number updated */
    ctrl_iface_ctx->m_sequenceNumberWrite = (ctrl_iface_ctx->m_sequenceNumberWrite + 1) & 0x3;
    //        USB4_LOG_INFO_BLUE("TX WR [%u]: PDF=%u, AN%u, CS%u, addr=0x%x, lenDW=0x%x\n",
    //                 cloreIndex, pdf,
    //                 pckt->controlData.readWriteRequest.adapterNum,
    //                 pckt->controlData.readWriteRequest.configurationSpace,
    //                 pckt->controlData.readWriteRequest.address,
    //                 pckt->controlData.readWriteRequest.readWriteDwords);
  }
  else if (6 == pdf)
  {
    pckt->controlData.interdomainReqResp.sequenceNumber = ctrl_iface_ctx->m_sequenceNumberRead;
    /* Read/Write request has to have sequence number updated */
    ctrl_iface_ctx->m_sequenceNumberRead = (ctrl_iface_ctx->m_sequenceNumberRead + 1) & 0x3;

    //        USB4_LOG_INFO_BLUE("TX ID [%u]: PDF=%u, Type=0x%x, lenDW=0x%x\n",
    //                  cloreIndex, pdf,
    //                  pckt->controlData.interdomainReqResp.packetType,
    //                  pckt->controlData.interdomainReqResp.dataDwords);
  }

  if (ctrl_iface_ctx->m_blockISRInSend)
  {
    {
      UINT32 mask = 1<<3;
      USB4_ASSERT(0 == Usb4HiaSetIntMaskClear(ctrl_iface_ctx->m_HIA, mask));
      USB4_ASSERT(0 == Usb4HiaGetIntMask(ctrl_iface_ctx->m_HIA, &mask)); /* Validation happens inside */
    }
  }

  /* Handle aggregated hot-plug packets */
  while (0 == Usb4CtrlIfacePeek(ctrl_iface_ctx))
  {
    USB4_ASSERT(0 == Usb4CtrlIfaceDeferPacketProcessing(ctrl_iface_ctx));
  }

  USB4_ASSERT(0 == Usb4CtrlIfacePostPacketToTX(ctrl_iface_ctx));

    if (0 == usTimeout)
    {
      if (ctrl_iface_ctx->m_blockISRInSend)
      {
        {
          UINT32 mask = 1<<3;
          USB4_ASSERT(0 == Usb4HiaSetIntMaskSet(ctrl_iface_ctx->m_HIA, mask));
          USB4_ASSERT(0 == Usb4HiaGetIntMask(ctrl_iface_ctx->m_HIA, &mask)); /* Validation happens inside */
        }
      }
      return 0;
    }

  step = (usTimeout+99)/100;
  while  (timeout < usTimeout)
  {
    while ((0 != Usb4CtrlIfacePeek(ctrl_iface_ctx)) && (timeout < usTimeout))
    {
      usb4_timer_Sleep_us(&timer, step);
      timeout = timeout + step;
    }

    if (timeout >= usTimeout)
    {
      USB4_ERROR_STACK(-1);
      if (ctrl_iface_ctx->m_blockISRInSend)
      {
        {
          UINT32 mask = 1<<3;
          USB4_ASSERT(0 == Usb4HiaSetIntMaskSet(ctrl_iface_ctx->m_HIA, mask))
          USB4_ASSERT(0 == Usb4HiaGetIntMask(ctrl_iface_ctx->m_HIA, &mask)); /* Validation happens inside */
        }
      }
      goto ErrorHandling;
    }        

    if(Usb4CtrlIfaceRxMatchesTx(ctrl_iface_ctx, &bErrorNotification))
    {
      if (ctrl_iface_ctx->m_blockISRInSend)
      {
        {
          UINT32 mask = 1<<3;
          USB4_ASSERT(0 == Usb4HiaSetIntMaskSet(ctrl_iface_ctx->m_HIA, mask));
          USB4_ASSERT(0 == Usb4HiaGetIntMask(ctrl_iface_ctx->m_HIA, &mask)); /* Validation happens inside */
        }
      }
      return 0;
    }
    else
    {
      USB4_ASSERT(0 == Usb4CtrlIfaceDeferPacketProcessing(ctrl_iface_ctx));
      if (TRUE == bErrorNotification)
      {
        break; /* No use waiting for another response */
      }
    }
  }

  /* Re-enable interrupts */
  if (ctrl_iface_ctx->m_blockISRInSend)
  {
    {
      UINT32 mask = 1<<3;
      USB4_ASSERT(0 == Usb4HiaSetIntMaskSet(ctrl_iface_ctx->m_HIA, mask));
      USB4_ASSERT(0 == Usb4HiaGetIntMask(ctrl_iface_ctx->m_HIA, &mask)); /* Validation happens inside */
    }
  }
ErrorHandling:
  return -1;
}

UINT32 UsbCtrlIfaceGetCoreIndex(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx)
{
  // TODO: AC CRITICAL, must fix port logger in future
  return 0;
  #if 0
    if (NULL != ctrl_iface_ctx->m_pLogger)
    {
        return Usb4CmLoggerGetCoreIndex(ctrl_iface_ctx->m_pLogger);
    }
    else
    {
        return 0;
    }
  #endif
}