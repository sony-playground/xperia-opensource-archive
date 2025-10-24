/**---------------------------------------------------------------------------
 *   @file        usb4_cm_interdomain.c
 *
 *   @brief   Interdomain protocol implementation file for a Connection Manager
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#include "usb4_cm.h"
#include "usb4_ctrl_packet.h"
#include "Usb4Log.h"   // Logging utilities

// #include "VVHAL_usb4_logger.h"   // Logging utilities
// #include "VVHAL_usb4_timer.h"
// #include "VVHAL_usb4_utils.h"
// #include <new>


static int usb4_compare_UUID(UINT32 UUID1[4], UINT32 UUID2[4]);

/*----------------------------------------------------------------------------
 * Global data structures
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Local variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * VVDRV_usb4_cm Class methods
 *--------------------------------------------------------------------------*/
int Usb4CmInterdomainProtocolHandler(usb4_cm_ctx_t* usb4_cm_ctx)
{
    USB4_cpDescriptorType desc_type=USB4_cpDescriptorType_UNKNOWN_DESCRIPTOR;
    USB4_cpInterdomainPacketType packetType;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetType(&usb4_cm_ctx->m_control, &desc_type))
    USB4_ASSERT(0 == Usb4CtrlIfaceGetInterdomainType(&usb4_cm_ctx->m_control, &packetType))

    switch (desc_type)
    {
        case USB4_cpDescriptorType_INTERDOMAIN_REQUEST:
        {
            switch(packetType)
            {
                case USB4_cpInterdomainPacket_UUID_Request_V1:
                case USB4_cpInterdomainPacket_UUID_Request_V2:
                    if (0 != Usb4CmSendXDomainResponseUUID(usb4_cm_ctx))
                    {
                        USB4_ERROR_STACK(-1);
                        goto ErrorHandling;
                    }
                    break;
                case USB4_cpInterdomainPacket_Properties_Read_Request:
                    USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control));
                    break;
                case USB4_cpInterdomainPacket_Properties_Changed_Notificatio:
                    USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control));
                    break;
                case USB4_cpInterdomainPacket_Link_State_Status_Request:
                    if (0 != Usb4CmHandleXDomainLinkStateStatusReq(usb4_cm_ctx))
                    {
                        USB4_ERROR_STACK(-1);
                        goto ErrorHandling;
                    }
                    break;
                case USB4_cpInterdomainPacket_Link_State_Change_Request:
                    if (0 != Usb4CmHandleXDomainLinkStateChangeReq(usb4_cm_ctx))
                    {
                        USB4_ERROR_STACK(-1);
                        goto ErrorHandling;
                    }
                    break;
                default:
                    Usb4CtrlIfacePop(&usb4_cm_ctx->m_control);
                    USB4_ERROR_STACK_MSG(-1, "Un-handled Event");
                    goto ErrorHandling;
            }
            break;
        }
        case USB4_cpDescriptorType_INTERDOMAIN_RESPONSE:
        {
            Usb4CtrlIfacePop(&usb4_cm_ctx->m_control);
            USB4_ASSERT_MSG(-1, "Responses should be handled by a ID state machine")
            break;
        }
        default:
            Usb4CtrlIfacePop(&usb4_cm_ctx->m_control);
            USB4_ERROR_STACK_MSG(-1, "Un-handled Event");
            goto ErrorHandling;
    }
    return 0;
ErrorHandling:
    Usb4CtrlIfacePop(&usb4_cm_ctx->m_control); // TODO: AC Not sure about this second pop
    return -1;
}

int Usb4CmRequestXDomainUUID(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 interdomain_route)
{
    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(&usb4_cm_ctx->m_control, USB4_cpDescriptorType_INTERDOMAIN_REQUEST))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(&usb4_cm_ctx->m_control, interdomain_route))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetInterdomainType(&usb4_cm_ctx->m_control, USB4_cpInterdomainPacket_UUID_Request_V2))

    if(0 != Usb4CtrlIfaceSend(&usb4_cm_ctx->m_control, 0)) /* Don't wait for any response */
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }
    return 0;
ErrorHandling:
    return -1;
}

int Usb4CmSendXDomainResponseUUID(usb4_cm_ctx_t* usb4_cm_ctx)
{
    UINT64 interdomain_route;
    UINT32 sequenceNumber;
    USB4_cpInterdomainPacketType interdomainType;
    UINT8 buffer[sizeof(usb4_cm_ctx->m_localUUID) + sizeof(UINT64)];
    UINT32* dwBuffer = (UINT32*)(buffer);

    USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(&usb4_cm_ctx->m_control, &interdomain_route))
    if (0 == interdomain_route)
    {
    	// USB4_LOG_WARNING("Warning: got interdomain_route = 0; using hard coded value.\n");
      Usb4Log(USB4_LOG_CM, Usb4CmSendXDomainResponseUUIDGotInterdomainRoute0UsingHardCodedValue__Warn, 0);
    	interdomain_route = 0x2;
    }
    USB4_ASSERT(0 == Usb4CtrlIfaceGetSN(&usb4_cm_ctx->m_control, &sequenceNumber))
    USB4_ASSERT(0 == Usb4CtrlIfaceGetInterdomainType(&usb4_cm_ctx->m_control, &interdomainType))
    USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control))

    /* Check that downstream adapter is connected and unlocked - May encounter race while working in interrupt mode */
    if (FALSE == usb4_cm_ctx->m_routers[0].m_bInterdomainRouter) /* Enumeration not done yet, so at least unlock adapter */
    {
        USB4_ASSERT(0 == Usb4RouterUnlockAdapter(&usb4_cm_ctx->m_routers[0], 2)) /* This is a hack..... */
    }

    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(&usb4_cm_ctx->m_control, USB4_cpDescriptorType_INTERDOMAIN_RESPONSE))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetSN(&usb4_cm_ctx->m_control, sequenceNumber))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(&usb4_cm_ctx->m_control, interdomain_route))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetInterdomainType(&usb4_cm_ctx->m_control, USB4_cpInterdomainPacket_UUID_Response))
    dwBuffer[0] = usb4_cm_ctx->m_localUUID[3];
    dwBuffer[1] = usb4_cm_ctx->m_localUUID[2];
    dwBuffer[2] = usb4_cm_ctx->m_localUUID[1];
    dwBuffer[3] = usb4_cm_ctx->m_localUUID[0];
    if(USB4_cpInterdomainPacket_UUID_Request_V1 == interdomainType)
    {
        /* Send local UUID */
        USB4_ASSERT(0 == Usb4CtrlIfaceSetData(&usb4_cm_ctx->m_control, buffer, sizeof(usb4_cm_ctx->m_localUUID)))
    }
    else
    {
        /* TODO: Clarify what is the use of this topology ID */
        usb4_mem_memcpy(&buffer[sizeof(usb4_cm_ctx->m_localUUID)], (UINT8*)(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_router_index].m_topologyID), sizeof(UINT64));
        /* Send local UUID */
        USB4_ASSERT(0 == Usb4CtrlIfaceSetData(&usb4_cm_ctx->m_control, buffer, sizeof(usb4_cm_ctx->m_localUUID)+sizeof(UINT64)))
    }

    if(0 != Usb4CtrlIfaceSend(&usb4_cm_ctx->m_control, 0)) /* Don't wait for any response */
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    // Static Analysis, ensure the local buffer cannot be inadvertently used outside of scope
    usb4_cm_ctx->m_control.m_txPacket.m_packetData = NULL;
    usb4_cm_ctx->m_control.m_txPacket.m_packetDataLength = 0;

    return 0;
ErrorHandling:
    // Static Analysis, ensure the local buffer cannot be inadvertently used outside of scope
    usb4_cm_ctx->m_control.m_txPacket.m_packetData = NULL;
    usb4_cm_ctx->m_control.m_txPacket.m_packetDataLength = 0;

    Usb4CtrlIfacePop(&usb4_cm_ctx->m_control);
    return -1;
}

int Usb4CmHandleInterdomainTopology(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 interdomain_route, UINT32 remote_UUID[4])
{
    UINT32 adapter;
    UINT64 router_topologyID;

    USB4_ASSERT(0 == usb4_get_router_and_port(interdomain_route, &router_topologyID, &adapter))
    USB4_ASSERT(0 == Usb4CmFindRouterByTopology(usb4_cm_ctx, router_topologyID))

    if (0 == usb4_compare_UUID(usb4_cm_ctx->m_localUUID, remote_UUID))
    {
        USB4_ASSERT(0 == Usb4RouterLoopingTopologyAdapter(Usb4CmRouter(usb4_cm_ctx), adapter))
    }
    else
    {
        USB4_ASSERT(0 == Usb4RouterInterdomainAdapter(Usb4CmRouter(usb4_cm_ctx), adapter, TRUE))
    }

    return 0;
}

int Usb4CmHandleXDomainUUIDResponse(usb4_cm_ctx_t* usb4_cm_ctx)
{
    UINT32 remote_UUID[4];
    UINT8 buffer[sizeof(usb4_cm_ctx->m_localUUID) + sizeof(UINT64)];
    UINT32* dwBuffer = (UINT32*)(buffer);
    UINT64 interdomain_route;
    UINT32 len;
    USB4_cpInterdomainPacketType packetType;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetInterdomainType(&usb4_cm_ctx->m_control, &packetType))
    USB4_ASSERT(USB4_cpInterdomainPacket_UUID_Response == packetType);

    USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(&usb4_cm_ctx->m_control, &interdomain_route))
    if (0 == interdomain_route)
    {
    	// USB4_LOG_WARNING("Warning: got interdomain_route = 0; using hard coded value.\n");
      Usb4Log(USB4_LOG_CM, Usb4CmHandleXDomainUUIDResponseGotInterdomainRoute0UsingHardCodedValue__Warn, 0);
    	interdomain_route = 0x2;
    }
    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(&usb4_cm_ctx->m_control, buffer, &len, sizeof(usb4_cm_ctx->m_localUUID) + sizeof(UINT64)))
    USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control))
    USB4_ASSERT_MSG(len >= 16, "Didn't read a complete remote UUID")
    remote_UUID[3] = dwBuffer[0];
    remote_UUID[2] = dwBuffer[1];
    remote_UUID[1] = dwBuffer[2];
    remote_UUID[0] = dwBuffer[3];

    if (usb4_cm_ctx->m_interdomainData.interdomainTopologyID == interdomain_route)
    {
        usb4_mem_memcpy(usb4_cm_ctx->m_interdomainData.remoteUUID, remote_UUID, sizeof(remote_UUID));
    }

    if (0 != Usb4CmHandleInterdomainTopology(usb4_cm_ctx, interdomain_route, remote_UUID))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }
    return 0;
ErrorHandling:
    Usb4CtrlIfacePop(&usb4_cm_ctx->m_control);
    return -1;
}

int Usb4CmSendXDomainLinkStateStatusReq(usb4_cm_ctx_t* usb4_cm_ctx)
{

    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(&usb4_cm_ctx->m_control, USB4_cpDescriptorType_INTERDOMAIN_REQUEST))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(&usb4_cm_ctx->m_control, usb4_cm_ctx->m_interdomainData.interdomainTopologyID))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetInterdomainType(&usb4_cm_ctx->m_control, USB4_cpInterdomainPacket_Link_State_Status_Request))

    if(0 != Usb4CtrlIfaceSend(&usb4_cm_ctx->m_control, 0))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }
    return 0;
ErrorHandling:
    return -1;
}

int Usb4CmHandleXDomainLinkStateStatusReq(usb4_cm_ctx_t* usb4_cm_ctx)
{
    usb4_interdomain_link_state_status_response_t response = {0};
    UINT8* buf = (UINT8*)(&response);
    UINT64 interdomain_route;
    UINT32 sequenceNumber;
    UINT64 router_topologyID;
    UINT32 adapter;
    usb4_port_ctx_t *downstreamPort;
    usb4_lane_adp_cs lane_adp_cs;
    USB4_cpInterdomainPacketType packetType;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetInterdomainType(&usb4_cm_ctx->m_control, &packetType))
    USB4_ASSERT(USB4_cpInterdomainPacket_Link_State_Status_Request == packetType);

    USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(&usb4_cm_ctx->m_control, &interdomain_route))
    if (0 == interdomain_route)
    {
    	// USB4_LOG_WARNING("Warning: got interdomain_route = 0; using hard coded value.\n");
    	Usb4Log(USB4_LOG_CM, Usb4CmHandleXDomainLinkStateStatusReqGotInterdomainRoute0UsingHardCodedValue__Warn, 0);
    	interdomain_route = 0x2;
    }
    USB4_ASSERT(0 == Usb4CtrlIfaceGetSN(&usb4_cm_ctx->m_control, &sequenceNumber))
    USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control))


    USB4_ASSERT(0 == usb4_get_router_and_port(interdomain_route, &router_topologyID, &adapter))
    USB4_ASSERT(0 == Usb4CmFindRouterByTopology(usb4_cm_ctx, router_topologyID))
    downstreamPort = Usb4RouterGetAdapterPortByNumber(Usb4CmRouter(usb4_cm_ctx), adapter);

    if (0 != Usb4PortReadLaneAdpCS(downstreamPort, &lane_adp_cs))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    response.status = 0;
    response.supportedLinkSpeeds = lane_adp_cs.LANE_ADP_CS_0.SupportedLinkSpeeds;
    response.supportedLinkWidth = lane_adp_cs.LANE_ADP_CS_0.SupportedLinkWidths;
    response.targetLinkSpeed = lane_adp_cs.LANE_ADP_CS_1.TargetLinkSpeed;
    response.targetLinkWidth = lane_adp_cs.LANE_ADP_CS_1.TargetLinkWidth;

    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(&usb4_cm_ctx->m_control, USB4_cpDescriptorType_INTERDOMAIN_RESPONSE))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetSN(&usb4_cm_ctx->m_control, sequenceNumber))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(&usb4_cm_ctx->m_control, interdomain_route))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetInterdomainType(&usb4_cm_ctx->m_control, USB4_cpInterdomainPacket_Link_State_Status_Response))

    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(&usb4_cm_ctx->m_control, buf, sizeof(usb4_interdomain_link_state_status_response_t)))

    if(0 != Usb4CtrlIfaceSend(&usb4_cm_ctx->m_control, 0))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    // Static Analysis, ensure the local buffer cannot be inadvertently used outside of scope
    usb4_cm_ctx->m_control.m_txPacket.m_packetData = NULL;
    usb4_cm_ctx->m_control.m_txPacket.m_packetDataLength = 0;

    return 0;
ErrorHandling:
    // Static Analysis, ensure the local buffer cannot be inadvertently used outside of scope
    usb4_cm_ctx->m_control.m_txPacket.m_packetData = NULL;
    usb4_cm_ctx->m_control.m_txPacket.m_packetDataLength = 0;

    Usb4CtrlIfacePop(&usb4_cm_ctx->m_control);
    return -1;
}

int Usb4CmHandleXDomainLinkStateStatusResp(usb4_cm_ctx_t* usb4_cm_ctx)
{
    usb4_interdomain_link_state_status_response_t response = {0};
    UINT8* buf = (UINT8*)(&response);
    UINT64 interdomain_route;
    UINT32 len;
    USB4_cpInterdomainPacketType packetType;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetInterdomainType(&usb4_cm_ctx->m_control, &packetType))
    USB4_ASSERT(USB4_cpInterdomainPacket_Link_State_Status_Response == packetType);

    USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(&usb4_cm_ctx->m_control, &interdomain_route))
    if (0 == interdomain_route)
    {
    	// USB4_LOG_WARNING("Warning: got interdomain_route = 0; using hard coded value.\n");
    	Usb4Log(USB4_LOG_CM, Usb4CmHandleXDomainLinkStateStatusRespGotInterdomainRoute0UsingHardCodedValue__Warn, 0);
    	interdomain_route = 0x2;
    }
    USB4_ASSERT(interdomain_route == usb4_cm_ctx->m_interdomainData.interdomainTopologyID)
    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(&usb4_cm_ctx->m_control, buf, &len, sizeof(usb4_interdomain_link_state_status_response_t)))
    USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control))
    USB4_ASSERT_MSG(len == sizeof(usb4_interdomain_link_state_status_response_t), "Didn't read a complete remote UUID")
    usb4_mem_memcpy((UINT8*)(&usb4_cm_ctx->m_interdomainData.lssr), buf, sizeof(usb4_interdomain_link_state_status_response_t));
    return 0;
}


int Usb4CmSendXDomainLinkStateChangeReq(usb4_cm_ctx_t* usb4_cm_ctx)
{
    usb4_interdomain_link_state_change_request_t request = {0};
    UINT8* buf = (UINT8*)(&request);
    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(&usb4_cm_ctx->m_control, USB4_cpDescriptorType_INTERDOMAIN_REQUEST))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(&usb4_cm_ctx->m_control, usb4_cm_ctx->m_interdomainData.interdomainTopologyID))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetInterdomainType(&usb4_cm_ctx->m_control, USB4_cpInterdomainPacket_Link_State_Change_Request))
    request.targetLinkSpeed = (usb4_cm_ctx->m_pParams->bLimitToGen2)?8:0xC;
    request.targetLinkWidth = (usb4_cm_ctx->m_pParams->numLanes < 2)?1:3;
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(&usb4_cm_ctx->m_control, buf, sizeof(usb4_interdomain_link_state_change_request_t)))

    if(0 != Usb4CtrlIfaceSend(&usb4_cm_ctx->m_control, 0))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    // Static Analysis, ensure the local buffer cannot be inadvertently used outside of scope
    usb4_cm_ctx->m_control.m_txPacket.m_packetData = NULL;
    usb4_cm_ctx->m_control.m_txPacket.m_packetDataLength = 0;

    return 0;
ErrorHandling:
    // Static Analysis, ensure the local buffer cannot be inadvertently used outside of scope
    usb4_cm_ctx->m_control.m_txPacket.m_packetData = NULL;
    usb4_cm_ctx->m_control.m_txPacket.m_packetDataLength = 0;

    return -1;
}


int Usb4CmHandleXDomainLinkStateChangeReq(usb4_cm_ctx_t* usb4_cm_ctx)
{
    usb4_interdomain_link_state_change_request_t request = {0};
    UINT8* buf = (UINT8*)(&request);

    usb4_interdomain_link_state_change_response_t response = {0};
    UINT8* buf_resp = (UINT8*)(&response);

    UINT64 interdomain_route;
    UINT32 sequenceNumber;
    UINT64 router_topologyID;
    UINT32 adapter, len;
    usb4_port_ctx_t *downstreamPort, *subordinateLane;
    usb4_lane_adp_cs lane_adp_cs;
    USB4_cpInterdomainPacketType packetType;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetInterdomainType(&usb4_cm_ctx->m_control, &packetType))
    USB4_ASSERT(USB4_cpInterdomainPacket_Link_State_Change_Request == packetType);


    USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(&usb4_cm_ctx->m_control, &interdomain_route))
    if (0 == interdomain_route)
    {
    	// USB4_LOG_WARNING("Warning: got interdomain_route = 0; using hard coded value.\n");
    	Usb4Log(USB4_LOG_CM, Usb4CmHandleXDomainLinkStateChangeReqGotInterdomainRoute0UsingHardCodedValue__Warn, 0);
    	interdomain_route = 0x2;
    }
    USB4_ASSERT(0 == Usb4CtrlIfaceGetSN(&usb4_cm_ctx->m_control, &sequenceNumber))
    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(&usb4_cm_ctx->m_control, buf, &len, sizeof(usb4_interdomain_link_state_change_request_t)))
    USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control))

    USB4_ASSERT(0 == usb4_get_router_and_port(interdomain_route, &router_topologyID, &adapter))
    USB4_ASSERT(0 == Usb4CmFindRouterByTopology(usb4_cm_ctx, router_topologyID))
    downstreamPort = Usb4RouterGetAdapterPortByNumber(Usb4CmRouter(usb4_cm_ctx), adapter);

    USB4_ASSERT(0 == Usb4PortReadLaneAdpCS(downstreamPort, &lane_adp_cs))
    lane_adp_cs.LANE_ADP_CS_1.TargetLinkSpeed = request.targetLinkSpeed;
    lane_adp_cs.LANE_ADP_CS_1.TargetLinkWidth = request.targetLinkWidth;
    USB4_ASSERT(0 == Usb4PortWriteLaneAdpCS(downstreamPort, &lane_adp_cs))

    if(0 != downstreamPort->m_OtherLaneGroupNumber)
    {
        subordinateLane = Usb4RouterGetAdapterPortByNumber(Usb4CmRouter(usb4_cm_ctx), downstreamPort->m_OtherLaneGroupNumber);
        USB4_ASSERT(USB4_portType_LANE1 == Usb4PortGetPortType(subordinateLane))
        USB4_ASSERT(0 == Usb4PortReadLaneAdpCS(subordinateLane, &lane_adp_cs))
        lane_adp_cs.LANE_ADP_CS_1.TargetLinkSpeed = request.targetLinkSpeed;
        lane_adp_cs.LANE_ADP_CS_1.TargetLinkWidth = request.targetLinkWidth;
        USB4_ASSERT(0 == Usb4PortWriteLaneAdpCS(subordinateLane, &lane_adp_cs))
    }

    response.status = 0;
    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(&usb4_cm_ctx->m_control, USB4_cpDescriptorType_INTERDOMAIN_RESPONSE))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetSN(&usb4_cm_ctx->m_control, sequenceNumber))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(&usb4_cm_ctx->m_control, interdomain_route))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetInterdomainType(&usb4_cm_ctx->m_control, USB4_cpInterdomainPacket_Link_State_Change_Response))
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(&usb4_cm_ctx->m_control, buf_resp, sizeof(usb4_interdomain_link_state_change_response_t)))

    if(0 != Usb4CtrlIfaceSend(&usb4_cm_ctx->m_control, 0))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    
    // Static Analysis, ensure the local buffer cannot be inadvertently used outside of scope
    usb4_cm_ctx->m_control.m_txPacket.m_packetData = NULL;
    usb4_cm_ctx->m_control.m_txPacket.m_packetDataLength = 0;

    return 0;
ErrorHandling:
    // Static Analysis, ensure the local buffer cannot be inadvertently used outside of scope
    usb4_cm_ctx->m_control.m_txPacket.m_packetData = NULL;
    usb4_cm_ctx->m_control.m_txPacket.m_packetDataLength = 0;

    Usb4CtrlIfacePop(&usb4_cm_ctx->m_control);
    return -1;
}


int Usb4CmHandleXDomainLinkStateChangeResp(usb4_cm_ctx_t* usb4_cm_ctx)
{
    usb4_interdomain_link_state_change_response_t response = {0};
    UINT8* buf = (UINT8*)(&response);
    UINT64 interdomain_route;
    UINT32 len;
    USB4_cpInterdomainPacketType packetType;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetInterdomainType(&usb4_cm_ctx->m_control, &packetType))
    USB4_ASSERT(USB4_cpInterdomainPacket_Link_State_Change_Response == packetType);

    USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(&usb4_cm_ctx->m_control, &interdomain_route))
    if (0 == interdomain_route)
    {
    	// USB4_LOG_WARNING("Warning: got interdomain_route = 0; using hard coded value.\n");
      Usb4Log(USB4_LOG_CM, Usb4CmHandleXDomainLinkStateChangeRespGotInterdomainRoute0UsingHardCodedValue__Warn, 0);
      interdomain_route = 0x2;
    }
    USB4_ASSERT(interdomain_route == usb4_cm_ctx->m_interdomainData.interdomainTopologyID)
    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(&usb4_cm_ctx->m_control, buf, &len, sizeof(usb4_interdomain_link_state_change_response_t)))
    USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control))
    USB4_ASSERT_MSG(len == sizeof(usb4_interdomain_link_state_change_response_t),
            "Didn't read a complete remote UUID")
    usb4_mem_memcpy((UINT8*)(&usb4_cm_ctx->m_interdomainData.lscr), buf,
            sizeof(usb4_interdomain_link_state_change_response_t));
    return 0;
}


int Usb4CmHandleErrEnum(usb4_cm_ctx_t* usb4_cm_ctx)
{
	//ERR_ENUM doesn't require acknowledge
    USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control))

    /* The target Router is already enumerated and a DFP of the
     * Router is newly connected to the Domain. See if the
     * Router belongs to a different domain or if the loop exists */
    /* Each ERR_ENUM will zero out existing state machine. If multiple concurrent inter-domain enumerations are needed, write handling */
    if (0 !=  usb4_cm_ctx->m_interdomainData.interdomainTopologyID)
    {
        // USB4_LOG_WARNING("Zeroing out interdomain state machine; Interdomain topology 0x%llux\n", (unsigned long long)(usb4_cm_ctx->m_interdomainData.interdomainTopologyID));
        Usb4Log1(USB4_LOG_CM, Usb4CmHandleErrEnumZeroingOutInterdomainStateMachine__Params__InterdomainTopology, 0, (UINT64)(usb4_cm_ctx->m_interdomainData.interdomainTopologyID));
        usb4_mem_memset((UINT8*)(&usb4_cm_ctx->m_interdomainData), 0, sizeof(usb4_cm_ctx->m_interdomainData));
    }
    usb4_cm_ctx->m_interdomainData.interdomainTopologyID = usb4_next_router_topology(usb4_cm_ctx->m_pHotplug->router_topologyID, usb4_cm_ctx->m_pHotplug->adapter_first);

    USB4_ASSERT_MSG (TRUE == usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->next_router_index].m_bEnumerationError,
            "Next router is supposed to have failed enumeration. Hence ERR_ENUM")
    Usb4RouterInit(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->next_router_index], &usb4_cm_ctx->m_control); /* Clear this router from an array */
    usb4_cm_ctx->m_pHotplug->next_router_index = 0;
    usb4_cm_ctx->m_pHotplug->next_router_topologyID = 0;
    //USB4_LOG_WARNING("--- RequestXDomainUUID ---, Core %d\n", m_pQdrv->m_Platform->GetCoreIndex());
    USB4_ASSERT(0 == Usb4CmRequestXDomainUUID(usb4_cm_ctx, usb4_cm_ctx->m_interdomainData.interdomainTopologyID))
    return 0;
}

int Usb4CmInterdomainHotPlugHandlerProcessUUIDS(usb4_cm_ctx_t* usb4_cm_ctx)
{
    BOOLEAN bBondingIsPossible, bBondingSuceeded;
    USB4_cpInterdomainPacketType packetType;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetInterdomainType(&usb4_cm_ctx->m_control, &packetType))
    /* In case there is a stale response, discard it */
    if (USB4_cpInterdomainPacket_UUID_Response != packetType)
    {
        // USB4_LOG_WARNING("InterdomainHotPlugHandler: Wrong packet type: %d, "
        //         "instead USB4_cpInterdomainPacket_UUID_Response\n", packetType);
        Usb4Log1(USB4_LOG_CM, Usb4CmInterdomainHotPlugHandlerProcessUUIDS__Params__WrongPacketTypeExpectingUSB4cpInterdomainPacketUUIDResponse, 0, (UINT32)(packetType));
        USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control))
        return 0;
    }

    //USB4_LOG_WARNING("-- HandleXDomainUUIDResponse ---, Core %d\n", m_pQdrv->m_Platform->GetCoreIndex());
    if (0 != Usb4CmHandleXDomainUUIDResponse(usb4_cm_ctx)) /* Configure port as inter-domain */
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    if(Usb4RouterGetAdapterPortByNumber(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_first)->m_bIsInterdomain)
    {
    	//USB4_LOG_WARNING("-- RequestXDCheckBondingIsPossibleomainUUID ---, Core %d\n", m_pQdrv->m_Platform->GetCoreIndex());
        USB4_ASSERT(0 == Usb4CmCheckBondingIsPossible(usb4_cm_ctx, &bBondingIsPossible))
        if (bBondingIsPossible)
        {
            /* Check if bonding has happened already */
            USB4_ASSERT(0 == Usb4CmCheckBondingSuceeded(usb4_cm_ctx, &bBondingSuceeded))
            if (bBondingSuceeded)
            {
            	USB4_ASSERT(0 == Usb4CmUpdatePortParametersAfterLanesBonded(usb4_cm_ctx))
                usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_CHECK_LANES_BONDED;
                USB4_ASSERT(0 == Usb4CmUSB4PortHotPlugHandler(usb4_cm_ctx))
                return 0;
            }
            else
            {
                /* Proceed with inter-domain bonding protocol */
            	//USB4_LOG_WARNING("-- SendXDomainLinkStateStatusReq ---, Core %d\n", m_pQdrv->m_Platform->GetCoreIndex());
                if (0 != Usb4CmSendXDomainLinkStateStatusReq(usb4_cm_ctx))
                {
                    USB4_ERROR_STACK(-1);
                    goto ErrorHandling;
                }
                usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_INTDOM_CHECK_X2_SUPPORT;
                return 0;
            }
        }
        else
        {
            /* Local host doesn't support x2 link */
            usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_DISABLE_LANE1;
            USB4_ASSERT(0 == Usb4CmUSB4PortHotPlugHandler(usb4_cm_ctx))
            return 0;
        }
    }
    else
    {
        /* This is not a valid inter-domain connection - may be a loop */
        USB4_ASSERT_MSG(-1, "Looks like a topology loop")
    }
    return 0;
ErrorHandling:
    return -1;
}


int Usb4CmInterdomainHotPlugHandlerCheckX2Support(usb4_cm_ctx_t* usb4_cm_ctx)
{
    USB4_cpInterdomainPacketType packetType;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetInterdomainType(&usb4_cm_ctx->m_control, &packetType))

    /* In case there is a stale response, discard it */
    if (USB4_cpInterdomainPacket_Link_State_Status_Response != packetType)
    {
        // USB4_LOG_WARNING("InterdomainHotPlugHandler: Wrong packet type: %d, "
        //         "instead USB4_cpInterdomainPacket_Link_State_Status_Response\n", packetType);
        Usb4Log1(USB4_LOG_CM, Usb4CmInterdomainHotPlugHandlerCheckX2Support__Params__WrongPacketTypeExpectingUSB4cpInterdomainPacketLinkStateStatusResponse, 0, (UINT32)(packetType));
        USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control))
        return 0;
    }

    //USB4_LOG_WARNING("-- HandleXDomainLinkStateStatusResp ---, Core %d\n", m_pQdrv->m_Platform->GetCoreIndex());
    if (0 != Usb4CmHandleXDomainLinkStateStatusResp(usb4_cm_ctx)) //Fill in m_hotplug.lssr
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }
    if (0x2 == (0x2 & usb4_cm_ctx->m_interdomainData.lssr.supportedLinkWidth))
    {
        if (-1 == usb4_compare_UUID(usb4_cm_ctx->m_localUUID, usb4_cm_ctx->m_interdomainData.remoteUUID))
        {
            /* Master CM */
        	//USB4_LOG_WARNING("-- SendXDomainLinkStateChangeReq ---, Core %d\n", m_pQdrv->m_Platform->GetCoreIndex());
            if (0 != Usb4CmSendXDomainLinkStateChangeReq(usb4_cm_ctx))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
            usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_INTDOM_MASTER;
            //USB4_LOG_WARNING("-- Master, Do bonding ---, Core %d\n", m_pQdrv->m_Platform->GetCoreIndex());
            return 0;

        }
        else
        {
            /* Slave CM */
            /* Expect Lx Out on bonding, so next state will be to check for bonded lanes */
            usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_CHECK_LANES_BONDED;
            //USB4_LOG_WARNING("-- Slave, Expect Plug Out on Lane 1 ---, Core %d\n", m_pQdrv->m_Platform->GetCoreIndex());
            return 0;
        }
    }
    else
    {
        /* Remote host doesn't support x2 link */
        usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_DISABLE_LANE1;
        USB4_ASSERT(0 == Usb4CmUSB4PortHotPlugHandler(usb4_cm_ctx))
        return 0;
    }
    return 0;
ErrorHandling:
    return -1;
}

int Usb4CmInterdomainHotPlugHandlerMeasureIterations(usb4_cm_ctx_t* usb4_cm_ctx)
{
    /* Measure how long 100 iterations take */
    static usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    
    UINT32 elapsed_us;
    if (0 == usb4_cm_ctx->m_interdomainData.interdomainRetries)
    {
        usb4_timer_Start(&timer);
    }
    else
    {
        if (100 == usb4_cm_ctx->m_interdomainData.interdomainRetries)
        {
            USB4_ASSERT(0 == usb4_timer_GetElapsed_us(&timer, &elapsed_us))
            //USB4_LOG_WARNING("Waiting while the other host is busy. 100 iterations took %llu usec. "
            //        "Adjust iterations to take several seconds.\n",
            //        (unsigned long long)(elapsed_us));
            Usb4Log1(USB4_LOG_CM, Usb4CmInterdomainHotPlugHandlerMeasureIterationsWaitingWhileTheOtherHostIsBusyIterationTookLongTime__Params__100IterationsTookuSec, 0, (UINT32)(elapsed_us));
        }
    }
    return 0;
}

int Usb4CmInterdomainHotPlugHandlerMasterFlow(usb4_cm_ctx_t* usb4_cm_ctx)
{
    USB4_cpInterdomainPacketType packetType;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetInterdomainType(&usb4_cm_ctx->m_control, &packetType))

    /* In case there is a stale response, discard it */
    if (USB4_cpInterdomainPacket_Link_State_Change_Response != packetType)
    {
        //USB4_LOG_WARNING("InterdomainHotPlugHandler: Wrong packet type: %d, "
        //        "instead USB4_cpInterdomainPacket_Link_State_Change_Response\n", packetType);
        Usb4Log1(USB4_LOG_CM, Usb4CmInterdomainHotPlugHandlerMasterFlow__Params__100IterationsTookuSec, 0, (UINT32)(packetType));
        USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control))
        return 0;
    }

    USB4_ASSERT(0 ==  Usb4CmHandleXDomainLinkStateChangeResp(usb4_cm_ctx)) /* update m_hotplug.lscr */
    switch(usb4_cm_ctx->m_interdomainData.lscr.status)
    {
        case 0: /* Success */
            if (0 != Usb4CmSendXDomainLinkStateStatusReq(usb4_cm_ctx))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
            usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_INTDOM_MASTER_BOND;
            usb4_cm_ctx->m_interdomainData.interdomainRetries = 0;
            return 0;
        case 4: /* Not ready */
            USB4_ASSERT_MSG(usb4_cm_ctx->m_interdomainData.interdomainRetries <= 100, "The other host is not ready")
            USB4_ASSERT(0 == Usb4CmInterdomainHotPlugHandlerMeasureIterations(usb4_cm_ctx))

            usb4_cm_ctx->m_interdomainData.interdomainRetries++;
            if (0 != Usb4CmSendXDomainLinkStateChangeReq(usb4_cm_ctx))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
            return 0;
        default:
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
    }

    return 0;
ErrorHandling:
    return -1;
}

int Usb4CmInterdomainHotPlugHandlerMasterFlowBond(usb4_cm_ctx_t* usb4_cm_ctx)
{
    USB4_cpInterdomainPacketType packetType;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetInterdomainType(&usb4_cm_ctx->m_control, &packetType))

    /* In case there is a stale response, discard it */
    if (USB4_cpInterdomainPacket_Link_State_Status_Response != packetType)
    {
        //USB4_LOG_WARNING(
        //        "InterdomainHotPlugHandler: Wrong packet type: %d, "
        //        "instead USB4_cpInterdomainPacket_Link_State_Status_Response\n", packetType);
        Usb4Log1(USB4_LOG_CM, Usb4CmInterdomainHotPlugHandlerMasterFlowBond__Params__WrongPacketTypeExpectingUSB4cpInterdomainPacketLinkStateStatusResponse, 0, (UINT32)(packetType));
        USB4_ASSERT(0 == Usb4CtrlIfacePop(&usb4_cm_ctx->m_control))
        return 0;
    }

    if (0 != Usb4CmHandleXDomainLinkStateStatusResp(usb4_cm_ctx)) //Fill in m_hotplug.lssr
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }
    switch (usb4_cm_ctx->m_interdomainData.lssr.status)
    {
        case 0: /* Success */
            usb4_cm_ctx->m_interdomainData.interdomainRetries = 0;
            if (0x2 != (0x2 & usb4_cm_ctx->m_interdomainData.lssr.targetLinkWidth))
            {
                /* Remote host failed to configure x2 link */
                usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_DISABLE_LANE1;
                USB4_ASSERT(0 == Usb4CmUSB4PortHotPlugHandler(usb4_cm_ctx))
            }
            else
            {
                if (0 != Usb4CmHandleLaneBonding(usb4_cm_ctx))
                {
                    USB4_ERROR_STACK(-1);
                    return -1;
                }
                usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_CHECK_LANES_BONDED;
            }
            return 0;
        case 4: /* Not ready */
            USB4_ASSERT_MSG(usb4_cm_ctx->m_interdomainData.interdomainRetries <= 100, "The other host is not ready")
            USB4_ASSERT(0 == Usb4CmInterdomainHotPlugHandlerMeasureIterations(usb4_cm_ctx))

            usb4_cm_ctx->m_interdomainData.interdomainRetries++;
            if (0 != Usb4CmSendXDomainLinkStateStatusReq(usb4_cm_ctx))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
            return 0;
        default:
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
    }


    return 0;
ErrorHandling:
    return -1;
}


int Usb4CmInterdomainHotPlugHandler(usb4_cm_ctx_t* usb4_cm_ctx)
{
    switch (usb4_cm_ctx->m_pHotplug->hotplug_state)
    {
        case USB4_HOTPLUG_INTDOM_HANDLE_ERR_ENUM:
            USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger))
            USB4_ASSERT(0 == Usb4CmHandleErrEnum(usb4_cm_ctx)) /* Get UUID from remote host */
            usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_INTDOM_PROCESS_UUIDS;
            return 0;
        case USB4_HOTPLUG_INTDOM_PROCESS_UUIDS:
            USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger))
            return Usb4CmInterdomainHotPlugHandlerProcessUUIDS(usb4_cm_ctx);
        case USB4_HOTPLUG_INTDOM_CHECK_X2_SUPPORT:
            USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger))
            return Usb4CmInterdomainHotPlugHandlerCheckX2Support(usb4_cm_ctx);
        case USB4_HOTPLUG_INTDOM_MASTER:
            USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger))
            return Usb4CmInterdomainHotPlugHandlerMasterFlow(usb4_cm_ctx);
        case USB4_HOTPLUG_INTDOM_MASTER_BOND:
            USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger))
            return Usb4CmInterdomainHotPlugHandlerMasterFlowBond(usb4_cm_ctx);
        default:
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
    }
    return 0;
ErrorHandling:
    return -1;
}
/* --------------------------------------------------------------------------
 * Static Functions
 *--------------------------------------------------------------------------*/

static int usb4_compare_UUID(UINT32 UUID1[4], UINT32 UUID2[4])
{
    UINT32 i;
    unsigned char *p1 = (unsigned char *)(UUID1);
    unsigned char *p2 = (unsigned char *)(UUID2);
    for(i=0; i<16; i++)
    {
        if(p1[i] != p2[i])
        {
            if (p1[i] < p2[i])
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;


}

/* --------------------------------------------------------------------------
 * Global Functions
 *--------------------------------------------------------------------------*/

