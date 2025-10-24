/**---------------------------------------------------------------------------
 *   @file        usb4_ctrl_iface.h
 *
 *   @brief   Interface to the control ring
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/
#ifndef _USB4_CTRL_IFACE_H_
#define _USB4_CTRL_IFACE_H_

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include "VVDRV_usb4_ctrl_packet.h"
// #include "VVDRV_usb4_hi_ring.h"
// #include "VVDRV_usb4_HIA.h"
#include "usb4_ctrl_packet.h"
#include "usb4_hi_ring.h"
#include "usb4_HIA.h"

#define USB4_CONTROL_TRANSMIT_RING_SIZE 10
#define USB4_CONTROL_TRANSMIT_BUFFERS 4
#define USB4_CONTROL_RECEIVE_RING_SIZE 16
#define USB4_CONTROL_RECEIVE_BUFFERS 12
#define USB4_CONTROL_SEND_BUFFERS 6
#define USB4_CONTROL_DESCRIPTOR_MAX_SIZE (64*4)/* Doesn't take inter-domain into account!!!*/
#define USB4_HIA_DESCRIPTOR_MAX_SIZE (4096)
/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/

#define USB4_SEND_CTRL_PACKET_TIMEOUT_US (1000000)

typedef struct
{
  UINT64 topologyId;          /*< transfer topology id */
  UINT64 timeout_us;          /*< timeout to wait in us, 0 for non-blocking */
  UINT8* pBuff;               /*< in/out buffer, depends on write/read */
  UINT32 size_bytes;          /*< transfer size in bytes */
  UINT32 resp_bytes;          /*< response size in bytes */
  UINT32 adapterNum;          /*< adapter number in topology */
  UINT32 address;             /*< register address */
  USB4_cpDescriptorType type; /*< transfer type */
  USB4_cpConfigSpace cs;      /*< configuration space type */
} usb4_ctrl_iface_trn;

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
/** Enum used to index control port errors */
typedef enum
{
  USB4_CP_ERR_CONN = 0 ,
  USB4_CP_ERR_LINK, 
  USB4_CP_ERR_ADDR,
  USB4_CP_ERR_ADP ,
  USB4_CP_ERR_ENUM,
  USB4_CP_ERR_NUA ,
  USB4_CP_ERR_LEN ,
  USB4_CP_ERR_HEC ,
  USB4_CP_ERR_FC  ,
  USB4_CP_ERR_PLUG,
  USB4_CP_ERR_LOCK,
  USB4_CP_ERR_NUMBER
} USB4_cp_errors;



/* defined in spec */
typedef enum
{
  USB4_SB_CS_1_OFFS = 24,
  USB4_SB_CS_2_OFFS = 25 
} USB4_sb_regs_offs;


typedef struct
{
  UINT32 numDescRx;
} USB4_ctrl_ring_cfg;


#define USB4_NUMBER_OF_DEFERRED_PACKETS 10
typedef struct
{
  usb4_hia_ctx_t* m_HIA;
  USB4_hi_xfer m_sndXfer[USB4_CONTROL_SEND_BUFFERS]; /* For future extension */
  USB4_hi_xfer m_rcvXfer[USB4_CONTROL_RECEIVE_BUFFERS];
  UINT32 m_rcvXferIndexToProcess;
  UINT32 m_numRcvXferToProcess;

  USB4_hi_xfer_status m_xferStatus;
  BOOLEAN  m_blockISRInSend;
  BOOLEAN  m_transmitAck;
  UINT32 m_blockedAckCounter;
  BOOLEAN m_blockedNotificationsTable[12];


  UINT8* m_txData;
  UINT32 m_sequenceNumberRead;
  UINT32 m_sequenceNumberWrite;

  /* Control error counter */
  UINT32 USB4_cp_error_counters[USB4_CP_ERR_NUMBER];

  /* Information about current received descriptor */
  usb4_control_packet_ctx_t m_rxPacket;

  /* Implementation of FIFO of deferred packets */
  usb4_control_packet_ctx_t m_rxRacketDeferred[USB4_NUMBER_OF_DEFERRED_PACKETS];
  UINT8 m_deferredData[USB4_NUMBER_OF_DEFERRED_PACKETS][USB4_CONTROL_DESCRIPTOR_MAX_SIZE];
  UINT32 m_nextFreeDefPacket;
  UINT32 m_currentDefPacket;
  BOOLEAN m_bProcessedDeferredPacket;

  /* Information about descriptor to be transmitted */
  usb4_control_packet_ctx_t m_txPacket;
} usb4_ctrl_iface_ctx_t;



void Usb4CtrlIfaceInit(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, usb4_hia_ctx_t* hia_ctx); // HIA is created by layer above

void Usb4CtrlIfaceDeInit(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief clear all error counters 
 * @return 0 on success 
 */
int Usb4CtrlIfaceClearAllErrors(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief Clears the counter for a specific type of error
 * @param[in] error_type - the type of error to clear
 * @return 0 on success 
 */
int Usb4CtrlIfaceClearErrorsOfType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cp_errors error_type);

/**
 * @brief Get the counter for a specific type of error
 * @param[in] error_type - the type of error counter to return
 * @return 0 on success 
 */
int Usb4CtrlIfaceGetErrorsOfType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cp_errors error_type, UINT32 *p_counter);


/**
 * @brief Configure RX and TX rings
 * @param[in] baseAddress - base address of the host control registers
 * @return 0 on success, other on failure
 */
int Usb4CtrlIfaceEnable(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT8* baseAddress);

/**
 * @brief Re-configure RX and TX rings
 * @param[in] ctrlRingCfg - parameters to change
 * @return 0 on success, other on failure
 */
int Usb4CtrlIfaceReConfigure(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_ctrl_ring_cfg* pCtrlRingCfg);

/**
 * @brief UnConfigure RX and TX rings
 * @return 0 on success, other on failure
 */
int Usb4CtrlIfaceUnInit(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief Peek into RX control ring
 * @return 0 if new descriptor is present, other if not present.
 */
int Usb4CtrlIfacePeek(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief Process deferred packet
 * @return 0 if new descriptor is present, other if not present.
 */
int Usb4CtrlIfaceProcessDeferred(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief Pop descriptor from RX control ring
 * @return 0 on success other on failure
 */
int Usb4CtrlIfacePop(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief Send ACK to a notification packet
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSendAck(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief Send slef initiated hot plug dummy packet for testing
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSendHotPlugDummyPacket(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief Send pre-filled data blob. Has to be a valid packet inside.
 * @param[in] dataBuffer - Data buffer to parse into packet header and data;
 * @param[in] dataLength - Length of available data
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSendPreFilledCtrlPacket(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT8* dataBuffer, UINT32 dataLength);

/**
 * @brief Get type of the RX packet
 * @return Descriptor type currently present in the RX control ring.
 */
int Usb4CtrlIfaceGetType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpDescriptorType* type);

/**
 * @brief Get inter-domain packet type
 * @param[out] type - Type of received request
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceGetInterdomainType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpInterdomainPacketType* type);

/**
 * @brief Set TX packet type
 * @param[in] type - Type of request to send, see #USB4_cpDescriptorType
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSetType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpDescriptorType type);

/**
 * @brief Set inter-domain packet type
 * @param[in] type - Type of request to send
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSetInterdomainType(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpInterdomainPacketType type);

/**
 * @brief Set routing string (Topology ID)
 * @param[in] route - route string
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSetRoute(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT64 route);

/**
 * @brief Set address
 * @param[in] address - address
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSetAddress(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32 address);

/**
 * @brief Set adapter
 * @param[in] adapter
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSetAdapter(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32 adapter);

/**
 * @brief Set configuration space
 * @param [in] eCS - configuration space see #USB4_CTRL_IFACE_CS
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSetCS(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpConfigSpace eCS);

/**
 * @brief Set serial number
 * @param[in] SN - serial number
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSetSN(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32 SN);

/**
 * @brief Set the TX Packet configuration see #USB4_ctrl_iface_txPacket_cfg for additional details
 *        this will not set the route
 * @param [in/out] pTrn transfer see #usb4_ctrl_iface_trn for details
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceTransfer(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, usb4_ctrl_iface_trn* pTrn);

/**
 * @brief Set data
 * @param[in] data - pointer to data buffer
 * @param[in] size_bytes - Size of the data buffer
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSetData(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT8* data, UINT32 size_bytes);

/**
 * @brief Get routing string (Topology ID)
 * @param[out] route - route string
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceGetRoute(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT64* route);

/**
 * @brief Get address
 * @param[out] address - router string
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceGetAddress(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* address);

/**
 * @brief Get address from the previous TX packet
 * @param[out] address - router string
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceGetTxAddress(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* address);

/**
 * @brief Get configuration space
 * @param[out] CS - configuration space
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceGetCS(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* CS);

/**
 * @brief Get serial number
 * @param[out] SN - serial number
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceGetSN(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* SN);

/**
 * @brief Get adapter number
 * @param[out] UPG - 1 for unplug
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceGetAdapter(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* adapter);

/**
 * @brief Get plug/unplug indication
 * @param[out] UPG - 1 for unplug
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceGetUPG(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT32* UPG);

/**
 * @brief Get data
 * @param[out] data - pointer to data buffer to fill
 * @param[out] size_bytes - Size of the data buffer received
 * @param[in]  max_size_bytes - Max size of data to be copied out (limiter)
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceGetData(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT8* data, UINT32* size_bytes, UINT32 max_size_bytes);

/**
 * @brief Get event code (table 6-11 spec 0.95)
 * @param[out] - event code
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceGetEventCode(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpNotificationEvent* event);

/**
 * @brief Wait for arrival of any RX packet
 * @param[in] usTimeout Timeout in us
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceWaitForRxPacket(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT64 usTimeout);

/**
 * @brief Send TX packet with timeout on response
 * @param[in] usTimeout Timeout in us
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceSend(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, UINT64 usTimeout);

/**
 * @brief Compare a current received packet to a list of deferred packets
 * @return TRUE if found, FALSE if not
 */
BOOLEAN Usb4CtrlIfaceRxIsDuplicateToDeferredPacket(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief Store packet for later processing
 * @return 0 on success other on failure
 */
int Usb4CtrlIfaceDeferPacketProcessing(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief Handles send related error notifications
 * @param[out] p_bNotification - Notification received
 * @return 0 on success
 */
int Usb4CtrlIfaceHandleErrorNotifications(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, BOOLEAN *p_bNotification);

/**
 * @brief Pass TX packet information to the TX ring for transmission;
 * May be especially needed once multiple TX packets are defined
 * @return 0 on success, other on failure
 */
int Usb4CtrlIfacePostPacketToTX(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief verifies write reponse has expected values
 * @param[out] p_result pointer to the verification result
 * @return 0 on success
 */
int Usb4CtrlIfaceVerifyReadWriteResponse(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, BOOLEAN *p_result);

/**
 * @brief Check if RX packet is a response to the TX packet
 * @param[out] p_bNotification - Notification received
 * @return TRUE on match, FALSE otherwise
 */
BOOLEAN Usb4CtrlIfaceRxMatchesTx(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, BOOLEAN *p_bNotification);

/**
 * @brief blocks a given notification used in case of re-transmisstion
 *        ack will not be sent for the notification once it arrives
 */
int Usb4CtrlIfaceBlockNotification(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpNotificationEvent notification_id);

/**
 * @brief unblocks a given notification used in case of re-transmisstion
 *        ack will be sent for the notification once it arrives
 */
int Usb4CtrlIfaceUnblockNotifcation(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpNotificationEvent notification_id);

/**
 * @brief unblocks all blocked notifications, used in case of re-transmisstion
 *        ack will be sent for the notification once it arrives
 */
int Usb4CtrlIfaceUnblockAllNotifcations(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

/**
 * @brief Check if notification is blocked or unblocked
 * @param [out] pResult TRUE if blocked, FALSE if unblocked
 */
int Usb4CtrlIfaceIsNotificationBlocked(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx, USB4_cpNotificationEvent notification_id, BOOLEAN *pResult);

/**
 * @brief Verify that HW finished sending all m_sndXfer
 */
int Usb4CtrlIfaceVerifyTransmissionComplete(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

UINT32 Usb4CtrlIfaceGetCoreIndex(usb4_ctrl_iface_ctx_t* ctrl_iface_ctx);

#endif /* _USB4_CTRL_IFACE_H_ */
