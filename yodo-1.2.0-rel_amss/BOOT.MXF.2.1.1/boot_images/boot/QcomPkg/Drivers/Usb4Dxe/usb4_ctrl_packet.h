/**---------------------------------------------------------------------------
 *   @file        usb4_ctrl_packet.h
 *
 *   @brief   
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#ifndef __USB4_CTRL_PACKET_H_
#define __USB4_CTRL_PACKET_H_

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include "VVHAL_usb4_comdef.h"
// #include "VVDRV_usb4_hi_packet.h"

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/
 
/** @brief CS field in control data (USB4 ver1.0 6.4.2.3-6) */
typedef enum
{
    USB4_cpConfigSpace_PATH      = 0x0,
    USB4_cpConfigSpace_ADAPTER   = 0x1,
    USB4_cpConfigSpace_ROUTER    = 0x2,
    USB4_cpConfigSpace_COUNTERS  = 0x3,
} USB4_cpConfigSpace;

typedef enum
{
    USB4_cpHandlingMethod_ADAPTER_PORT_SM,
    USB4_cpHandlingMethod_USB4_PORT_SM,
    USB4_cpHandlingMethod_INTERDOMAIN_SM,
    USB4_cpHandlingMethod_INTERDOMAIN_PROTOCOL,
    USB4_cpHandlingMethod_STATELESS,
    USB4_cpHandlingMethod_NO_ACTION,
} USB4_cpHandlingMethod;

/** @brief Types of control port descriptors */
typedef enum
{
    USB4_cpDescriptorType_UNKNOWN_DESCRIPTOR,
    USB4_cpDescriptorType_READ_REQUEST,
    USB4_cpDescriptorType_READ_RESPONSE,
    USB4_cpDescriptorType_WRITE_REQUEST,
    USB4_cpDescriptorType_WRITE_RESPONSE,
    USB4_cpDescriptorType_NOTIFICATION,
    USB4_cpDescriptorType_NOTIFICATION_ACK,
    USB4_cpDescriptorType_HOT_PLUG_EVENT,
    USB4_cpDescriptorType_INTERDOMAIN_REQUEST,
    USB4_cpDescriptorType_INTERDOMAIN_RESPONSE
} USB4_cpDescriptorType;

/** @brief Types of control port descriptors */
typedef enum
{
    USB4_cpNotificationEvent_ERR_CONN = 0 ,
    USB4_cpNotificationEvent_ERR_LINK = 1 ,
    USB4_cpNotificationEvent_ERR_ADDR = 2 ,
    USB4_cpNotificationEvent_ERR_ADP  = 4 ,
    USB4_cpNotificationEvent_ERR_ENUM = 8 ,
    USB4_cpNotificationEvent_ERR_NUA  = 9 ,
    USB4_cpNotificationEvent_ERR_LEN  = 11,
    USB4_cpNotificationEvent_ERR_HEC  = 12,
    USB4_cpNotificationEvent_ERR_FC   = 13,
    USB4_cpNotificationEvent_ERR_PLUG = 14,
    USB4_cpNotificationEvent_ERR_LOCK = 15,
    USB4_cpNotificationEvent_HP_ACK   = 7 ,
} USB4_cpNotificationEvent;

typedef enum
{
    USB4_cpInterdomainPacket_Invalid                        = 0,
    USB4_cpInterdomainPacket_UUID_Request_V1                = 1,
    USB4_cpInterdomainPacket_UUID_Response                  = 2,
    USB4_cpInterdomainPacket_Properties_Read_Request        = 3,
    USB4_cpInterdomainPacket_Properties_Read_Response       = 4,
    USB4_cpInterdomainPacket_Properties_Changed_Notificatio = 5,
    USB4_cpInterdomainPacket_Properties_Changed_Response    = 6,
    USB4_cpInterdomainPacket_Error_Response                 = 7,
    USB4_cpInterdomainPacket_UUID_Request_V2                = 12,
    USB4_cpInterdomainPacket_Link_State_Status_Request      = 15,
    USB4_cpInterdomainPacket_Link_State_Status_Response     = 16,
    USB4_cpInterdomainPacket_Link_State_Change_Request      = 17,
    USB4_cpInterdomainPacket_Link_State_Change_Response     = 18,
} USB4_cpInterdomainPacketType;


#pragma pack(push)
#pragma pack(1)


typedef struct {
    UINT32 routeStringHigh;
    UINT32 routeStringLow;
    union {
        struct {
            UINT32 address:13;
            UINT32 readWriteDwords:6;
            UINT32 adapterNum:6;
            UINT32 configurationSpace:2;
            UINT32 sequenceNumber:2;
            UINT32 rsvd:3;
        } readWriteRequest;
        struct {
            UINT32 eventCode:8;
            UINT32 adapterNum:6;
            UINT32 rsvd:16;
            UINT32 PG:2;
        } notificationPacket;
        struct {
            UINT32 adapterNum:6;
            UINT32 rsvd:25;
            UINT32 UPG:1;
        } hotPlugEventPacket;
        struct {
            UINT32 dataDwords:6;
            UINT32 rsvd:21;
            UINT32 sequenceNumber:2;
            UINT32 rsvd1:3;
            UINT32 XDDP_UUID0;/* XDomain Discovery Protocol UUID */
            UINT32 XDDP_UUID1;
            UINT32 XDDP_UUID2;
            UINT32 XDDP_UUID3;
            UINT32 packetType;
        }interdomainReqResp;
    }controlData;
} usb4_control_packet_t;

typedef struct {
    UINT32 status;
    UINT32 supportedLinkWidth:8;
    UINT32 targetLinkWidth:8;
    UINT32 supportedLinkSpeeds:8;
    UINT32 targetLinkSpeed:8;
} usb4_interdomain_link_state_status_response_t;

typedef struct {
    UINT32 targetLinkWidth:8;
    UINT32 targetLinkSpeed:8;
    UINT32 rsvd:16;
} usb4_interdomain_link_state_change_request_t;

typedef struct {
    UINT32 status;
} usb4_interdomain_link_state_change_response_t;

typedef struct {
  usb4_control_packet_t m_controlPacket;
  UINT32 m_CRC;
  UINT32 m_PDF;

  UINT8* m_prefix;
  UINT32 m_prefixLength;
  UINT8* m_packetData;
  UINT32 m_packetDataLength;
} usb4_control_packet_ctx_t; // Equivalent to VI usb4_ctrl_packet.  Notice the subtle "ctrl", not "control" for the class object.
                             // Renamed usb4_ctrl_packet to usb4_control_packet_ctx_t to avoid confusion

#pragma pack(pop)
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

/**
 * @brief Zero initialize internal data structures
 * @return none
 */
void Usb4CtrlPacketInit(usb4_control_packet_ctx_t *control_packet_ctx);

/**
 * @brief Return pointer to the internal data structure of
 * control packet header
 * @return Pointer to the internal data structure
 */
usb4_control_packet_t* Usb4CtrlPacketGetControlPacket(usb4_control_packet_ctx_t *control_packet_ctx);

/**
 * @brief Construct packet in a destination buffer, including CRC calculation if needed
 * Length of the packet is spec defined and limited by 4KB
 * @param[in] dataBuffer - Data buffer to fill with data for transmission;
 * @param[in/out] pDataLength - Return length of data copied; If not zero,
 * it limits it is used to limit the size of output buffer.
 * @return 0 on success other on failure
 */
int Usb4CtrlPacketCopyPacketToBuffer(usb4_control_packet_ctx_t *control_packet_ctx, UINT8* dataBuffer, UINT32* pDataLength);

/**
 * @brief Parse data blob into a packet. Copy header and routing information.
 * Keep pointer to data
 * @param[in] dataBuffer - Data buffer to parse;
 * @param[in] dataLength - Length of available data
 * @return 0 on success other on failure
 */
int Usb4CtrlPacketReferenceBufferToPacket(usb4_control_packet_ctx_t *control_packet_ctx, UINT8* dataBuffer, UINT32 dataLength, UINT32 EOF_PDF);

/**
 * @brief Assign packet type and consequently, prefix length
 * Keep pointer to data
 * @param[in] PDF - Packet type
 * @return 0 on success other on failure
 */
int Usb4CtrlPacketAssignPDF(usb4_control_packet_ctx_t *control_packet_ctx, UINT32 PDF);

/**
 * @brief Return value of packet PDF
 * @return PDF
 */
UINT32 Usb4CtrlPacketGetPDF(usb4_control_packet_ctx_t *control_packet_ctx);

/**
 * @brief Return value of packet CRC
 * @return CRC
 */
UINT32 Usb4CtrlPacketGetCRC(usb4_control_packet_ctx_t *control_packet_ctx);

/**
 * @brief reflects the lower 'bitnum' bits of 'crc'
 */
UINT32 Usb4CtrlPacketReflect(UINT32 crc, int bitnum);

/**
 * @brief Calculate CRC according to spec
 */
void Usb4CtrlPacketCalculateCRC(usb4_control_packet_ctx_t *control_packet_ctx, UINT8* p, UINT32 len);

// usb4_ctrl_packet& operator= (const VVDRV_usb4_ctrl_packet &pckt);
usb4_control_packet_ctx_t* Usb4CtrlPacketSet(usb4_control_packet_ctx_t *control_packet_ctx, const usb4_control_packet_ctx_t *pckt);

// bool operator== (VVDRV_usb4_ctrl_packet& lhs, VVDRV_usb4_ctrl_packet& rhs);
BOOLEAN Usb4CtrlPacketIsPacketSame(usb4_control_packet_ctx_t* lhs, usb4_control_packet_ctx_t* rhs);

// bool operator!=(VVDRV_usb4_ctrl_packet& lhs, VVDRV_usb4_ctrl_packet& rhs);
BOOLEAN Usb4CtrlPacketIsPacketNotSame(usb4_control_packet_ctx_t* lhs, usb4_control_packet_ctx_t* rhs);

#endif /* __USB4_CTRL_PACKET_H_ */
