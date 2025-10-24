/**---------------------------------------------------------------------------
 *   @file        usb4_cm_hotplug.c
 *
 *   @brief   Hot plug handler for a Connection Manager
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#include "Usb4Utils.h"
#include "usb4_cm.h"
#include "usb4_ctrl_packet.h"
#include "Usb4Log.h"   // Logging utilities
#include "usb4_port.h"
#include "usb4_platform_target.h"
// #include "usb4_logger.h"   // Logging utilities
// #include "VVHAL_usb4_timer.h"
// #include "VVHAL_usb4_utils.h"
// #include <new>


/*----------------------------------------------------------------------------
 * Global data structures
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Local variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * VVDRV_usb4_cm Class methods
 *--------------------------------------------------------------------------*/

int Usb4CmParseHpe(usb4_cm_ctx_t* usb4_cm_ctx)
{
    USB4_cpDescriptorType desc_type;
    UINT32 unplug_flag = 0;
    UINT64 router_topologyID = 0;
    UINT32 adapter;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetType(Usb4CmControl(usb4_cm_ctx), &desc_type));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetUPG(Usb4CmControl(usb4_cm_ctx), &unplug_flag));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(Usb4CmControl(usb4_cm_ctx), &router_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetAdapter(Usb4CmControl(usb4_cm_ctx), &adapter));

    USB4_ASSERT(USB4_cpDescriptorType_HOT_PLUG_EVENT == desc_type);
    usb4_cm_ctx->m_pHotplug->record_was_updated = FALSE;

    if (0 == usb4_cm_ctx->m_pHotplug->adapter_first)
    {
        USB4_ASSERT_MSG(USB4_MAX_PORTS_PER_ROUTER > adapter,
                "Wrong adapter number received in a hot plug event")

        /* Check for HPE from upstream adapter of the enumerated router. Need to discard those. */
        if ((usb4_cm_ctx->m_router_index > 0) && Usb4RouterIsEnumerated(Usb4CmRouter(usb4_cm_ctx)))
        {
            /* First two adapters of the device router are upstream */
            if ((adapter == Usb4CmRouter(usb4_cm_ctx)->m_cs.ROUTER_CS_1.upstreamAdapter) ||
                (adapter == Usb4CmRouter(usb4_cm_ctx)->m_cs.ROUTER_CS_1.upstreamAdapter + 1UL))
            {
                /* Nothing to do but ACK those notifications from upstream port.... */
                USB4_ASSERT(0 == Usb4CtrlIfaceSendAck(Usb4CmControl(usb4_cm_ctx)));
                goto ExitNoAck;
            }
        }
 
        /* Handling of the first HPE in a sequence */
        usb4_cm_ctx->m_pHotplug->router_index = usb4_cm_ctx->m_router_index;
        usb4_cm_ctx->m_pHotplug->record_was_updated = TRUE;
        usb4_cm_ctx->m_pHotplug->router_topologyID = router_topologyID;
        usb4_cm_ctx->m_pHotplug->adapter_first = adapter;
        usb4_cm_ctx->m_pHotplug->modifiedAdapter = adapter;
        if (0 == unplug_flag)
        {
            usb4_cm_ctx->m_pHotplug->adapter_first_action = USB4_HPE_IN;
        }
        else
        {
            usb4_cm_ctx->m_pHotplug->adapter_first_action = USB4_HPE_OUT;
        }
        USB4_ASSERT(0 == Usb4CmLoggerStoreHpe(&usb4_cm_ctx->m_logger));
    }
    else //m_hotplug.adapter_second was assigned after enumeration
    {
        if (router_topologyID != usb4_cm_ctx->m_pHotplug->router_topologyID)
        {
            /* Some other router got an event, defer handling
             * since event will be resent. */
            goto ExitNoAck;
        }

        if (usb4_cm_ctx->m_pHotplug->adapter_first == adapter)
        {
            if (0 == unplug_flag)
            {
                if (USB4_HPE_IN != usb4_cm_ctx->m_pHotplug->adapter_first_action)
                {
                    usb4_cm_ctx->m_pHotplug->adapter_first_action = USB4_HPE_IN;
                    usb4_cm_ctx->m_pHotplug->record_was_updated = TRUE;
                    usb4_cm_ctx->m_pHotplug->modifiedAdapter = usb4_cm_ctx->m_pHotplug->adapter_first;
                    USB4_ASSERT(0 == Usb4CmLoggerStoreHpe(&usb4_cm_ctx->m_logger));
                }

            }
            else
            {
                if (USB4_HPE_OUT != usb4_cm_ctx->m_pHotplug->adapter_first_action)
                {
                    usb4_cm_ctx->m_pHotplug->adapter_first_action = USB4_HPE_OUT;
                    usb4_cm_ctx->m_pHotplug->record_was_updated = TRUE;
                    usb4_cm_ctx->m_pHotplug->modifiedAdapter = usb4_cm_ctx->m_pHotplug->adapter_first;
                    USB4_ASSERT(0 == Usb4CmLoggerStoreHpe(&usb4_cm_ctx->m_logger));
                }
            }
        }
        else if (usb4_cm_ctx->m_pHotplug->adapter_second == adapter)
        {
            if (0 == unplug_flag)
            {
                if (USB4_HPE_IN != usb4_cm_ctx->m_pHotplug->adapter_second_action)
                {
                    usb4_cm_ctx->m_pHotplug->adapter_second_action = USB4_HPE_IN;
                    usb4_cm_ctx->m_pHotplug->record_was_updated = TRUE;
                    usb4_cm_ctx->m_pHotplug->modifiedAdapter = usb4_cm_ctx->m_pHotplug->adapter_second;
                    USB4_ASSERT(0 == Usb4CmLoggerStoreHpe(&usb4_cm_ctx->m_logger));
                }
            }
            else
            {
                if (USB4_HPE_OUT != usb4_cm_ctx->m_pHotplug->adapter_second_action)
                {
                    usb4_cm_ctx->m_pHotplug->adapter_second_action = USB4_HPE_OUT;
                    usb4_cm_ctx->m_pHotplug->record_was_updated = TRUE;
                    usb4_cm_ctx->m_pHotplug->modifiedAdapter = usb4_cm_ctx->m_pHotplug->adapter_second;
                    USB4_ASSERT(0 == Usb4CmLoggerStoreHpe(&usb4_cm_ctx->m_logger));
                }
            }
        }
        else
        {
            Usb4Log2(USB4_LOG_CM, Usb4CmParseHpeERROR_Params__TopologyID_Adapter, 0, (unsigned long long)(usb4_cm_ctx->m_pHotplug->router_topologyID), adapter);
            // USB4_LOG_INFO("WTF??? topolgyid: 0x%08llX, adapter= 0x%02X\n", 
            //                (unsigned long long)(usb4_cm_ctx->m_pHotplug->router_topologyID), adapter);
            //Need to assign second lane
            usb4_cm_ctx->m_pHotplug->record_was_updated = TRUE;
            goto ExitNoAck;
        }
    }
//ExitAck:
    if (usb4_cm_ctx->m_pHotplug->record_was_updated) /* Don't send ACKs on duplicate packets */
    {
        USB4_ASSERT(0 == Usb4CtrlIfaceSendAck(Usb4CmControl(usb4_cm_ctx)));
    }
ExitNoAck:
    USB4_ASSERT(0 == Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));
    return 0;
}


int Usb4CmParseErrLink(usb4_cm_ctx_t* usb4_cm_ctx)
{
    UINT64 router_topologyID = 0;
    UINT32 adapter;
    USB4_cpNotificationEvent event;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(Usb4CmControl(usb4_cm_ctx), &router_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetAdapter(Usb4CmControl(usb4_cm_ctx), &adapter));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetEventCode(Usb4CmControl(usb4_cm_ctx), &event));
    USB4_ASSERT(0 == Usb4CtrlIfaceSendAck(Usb4CmControl(usb4_cm_ctx)));
    USB4_ASSERT(0 == Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));

    USB4_ASSERT(USB4_cpNotificationEvent_ERR_LINK == event);
    usb4_cm_ctx->m_pHotplug->record_was_updated = FALSE;

    if (router_topologyID != usb4_cm_ctx->m_pHotplug->router_topologyID)
    {
        /* Some other router got an event, defer handling
         * since event will be resent. */
        return 0;
    }

    /* ERR_LINK will be treated as un-plug of the specific lane since similar handling is needed */
    if (usb4_cm_ctx->m_pHotplug->adapter_first == adapter)
    {
        if (USB4_HPE_OUT != usb4_cm_ctx->m_pHotplug->adapter_first_action)
        {
            usb4_cm_ctx->m_pHotplug->adapter_first_action = USB4_HPE_OUT;
            usb4_cm_ctx->m_pHotplug->record_was_updated = TRUE;
            usb4_cm_ctx->m_pHotplug->modifiedAdapter = usb4_cm_ctx->m_pHotplug->adapter_first;
            USB4_ASSERT(0 == Usb4CmLoggerStoreHpe(&usb4_cm_ctx->m_logger));
        }
    }

    if (usb4_cm_ctx->m_pHotplug->adapter_second == adapter)
    {
        if (USB4_HPE_OUT != usb4_cm_ctx->m_pHotplug->adapter_second_action)
        {
            usb4_cm_ctx->m_pHotplug->adapter_second_action = USB4_HPE_OUT;
            usb4_cm_ctx->m_pHotplug->record_was_updated = TRUE;
            usb4_cm_ctx->m_pHotplug->modifiedAdapter = usb4_cm_ctx->m_pHotplug->adapter_second;
            USB4_ASSERT(0 == Usb4CmLoggerStoreHpe(&usb4_cm_ctx->m_logger));
        }
    }

    return 0;
}


int Usb4CmHandleLaneUnplug(usb4_cm_ctx_t* usb4_cm_ctx)
{
    usb4_port_ctx_t* pPort;
    usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_L0_IN_CLd;
    USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger));

    if (usb4_cm_ctx->m_pHotplug->next_router_topologyID > usb4_cm_ctx->m_pHotplug->router_topologyID)
    {
        USB4_ASSERT(0 == Usb4CmRemoveRoutersBeyondTopology(usb4_cm_ctx, usb4_cm_ctx->m_pHotplug->next_router_topologyID));
        USB4_ASSERT(0 == Usb4PathManagerInvalidatePathsBeyondTopology(&usb4_cm_ctx->m_path_manager,
                                usb4_cm_ctx->m_pHotplug->next_router_topologyID))
    }
    pPort = Usb4RouterGetAdapterPortByNumber(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_first);
    if ((NULL != pPort)&&(pPort->m_bIsInterdomain))
    {
        USB4_ASSERT(0 == Usb4PathManagerInvalidatePathFromPort(&usb4_cm_ctx->m_path_manager, 
                                usb4_cm_ctx->m_pHotplug->router_topologyID,
                                usb4_cm_ctx->m_pHotplug->adapter_first))
        USB4_ASSERT(0 == Usb4RouterInterdomainAdapter(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_first, FALSE));
    }
    /* Enable lane 1 if it was disabled */
    //TODO: Consult with Yiftach regarding reconnecting lane without DPR
    //USB4_ASSERT(0 == Router().ReconnectAdapter(m_pHotplug->adapter_second));

    /* Update paths given a new topology */
    USB4_ASSERT(0 == Usb4PathManagerUpdatePaths(&usb4_cm_ctx->m_path_manager));

    /* Update local port configuration */
    USB4_ASSERT(0 == Usb4PortReadCS(pPort));
    pPort->m_bIsBound = FALSE; /* Disconnected port can't be bonded */

    /* Update TMU of the unplugged adapter */
    USB4_ASSERT(0 == Usb4RouterTMUSetPortUnidirectionalMode(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_first, TRUE));

    return 0;
}


int Usb4CmCheckBondingIsPossible(usb4_cm_ctx_t* usb4_cm_ctx, BOOLEAN* p_bIsPossible)
{
//    bool DownstreamDualLaneSupported = FALSE;
//    bool UpstreamDualLaneSupported = FALSE;
    BOOLEAN dfp0_inCL0 = FALSE, dfp1_inCL0 = FALSE;
    usb4_port_ctx_t *downstreamPort;//, *upstreamPort;
//    UINT32 upstreamAdapterNumber = 0;
    USB4_ASSERT(NULL != p_bIsPossible);
//    upstreamAdapterNumber = m_routers[m_hotplug.next_router_index].m_cs.ROUTER_CS_1.upstreamAdapter;
//    USB4_ASSERT(0 != upstreamAdapterNumber);
//    upstreamPort = m_routers[m_hotplug.next_router_index].GetAdapterPortByNumber(upstreamAdapterNumber);
//    USB4_ASSERT(NULL != upstreamPort);

    downstreamPort = Usb4RouterGetAdapterPortByNumber(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->router_index], usb4_cm_ctx->m_pHotplug->adapter_first);
    USB4_ASSERT(NULL != downstreamPort);

//    If bonding enabled bit is set, links necessarily support dual lane - according to Yiftach.
//    if (0 != upstreamPort->IsDualLaneSupported(&UpstreamDualLaneSupported))
//    {
//        USB4_ERROR_STACK(-1);
//        return -1;
//    }
//
//    if (0 != downstreamPort->IsDualLaneSupported(&DownstreamDualLaneSupported))
//    {
//        USB4_ERROR_STACK(-1);
//        return -1;
//    }
//
//    if (UpstreamDualLaneSupported && DownstreamDualLaneSupported)
//    {
//        USB4_ASSERT(0 == downstreamPort->IsBondingEnabled(bIsPossible));
//    }
//    else
//    {
//        *bIsPossible = FALSE;
//    }

    if (0 != usb4_cm_ctx->m_pHotplug->adapter_second)
    {
        USB4_ASSERT(0 == Usb4RouterDfpInCL0(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_first, &dfp0_inCL0));
        USB4_ASSERT(0 == Usb4RouterDfpInCL0(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_second, &dfp1_inCL0));
        if ((FALSE == dfp0_inCL0) || (FALSE == dfp1_inCL0))
        {
            /* L0 or L1 is not in CL0 (low power or disconnected states will prevent bonding too) */
            *p_bIsPossible = FALSE;
            return 0;
        }
    }

    USB4_ASSERT(0 == Usb4PortIsBondingEnabled(downstreamPort, p_bIsPossible));

    return 0;
}

int Usb4CmHandleLaneBonding(usb4_cm_ctx_t* usb4_cm_ctx)
{
    usb4_port_ctx_t *upstreamLane, *downstreamLane;
    usb4_port_ctx_t *upstreamLane_1, *downstreamLane_1;

    if (0 != usb4_cm_ctx->m_pHotplug->next_router_index)
    {
        UINT32 upstreamAdapterNumber = 0;
        upstreamAdapterNumber = usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->next_router_index].m_cs.ROUTER_CS_1.upstreamAdapter;
        USB4_ASSERT(0 != upstreamAdapterNumber);
        upstreamLane = Usb4RouterGetAdapterPortByNumber(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->next_router_index], upstreamAdapterNumber);
        upstreamLane_1 = Usb4RouterGetAdapterPortByNumber(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->next_router_index], upstreamAdapterNumber+1);
        USB4_ASSERT(NULL != upstreamLane_1);
    }
    else
    {
        upstreamLane = NULL;
        upstreamLane_1 = NULL;
    }

    downstreamLane = Usb4RouterGetAdapterPortByNumber(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->router_index], usb4_cm_ctx->m_pHotplug->adapter_first);
    USB4_ASSERT(NULL != downstreamLane);
    downstreamLane_1 = Usb4RouterGetAdapterPortByNumber(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->router_index], usb4_cm_ctx->m_pHotplug->adapter_second);
    USB4_ASSERT(NULL != downstreamLane_1);


    if ((NULL != upstreamLane) && (0 != Usb4PortConfigureDualLane(upstreamLane)) &&
        (NULL != upstreamLane_1) && (0 != Usb4PortConfigureDualLane(upstreamLane_1)))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    if ((0 != Usb4PortConfigureDualLane(downstreamLane)) || (0 != Usb4PortConfigureDualLane(downstreamLane_1)))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    if ((NULL != upstreamLane) &&(NULL != upstreamLane_1))
    {
        /* MSFT prefers to initiate bonding from upstream port */
        if (0 != Usb4RouterBondLanes(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->next_router_index], upstreamLane->m_Number,
                upstreamLane_1->m_Number))
        {
            USB4_ERROR_STACK(-1);
            return -1;
        }
    }
    else
    {
        if (0 != Usb4RouterBondLanes(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->router_index], usb4_cm_ctx->m_pHotplug->adapter_first,
                usb4_cm_ctx->m_pHotplug->adapter_second))
        {
            USB4_ERROR_STACK(-1);
            return -1;
        }
    }
    return 0;
}

int Usb4CmCheckBondingSuceeded(usb4_cm_ctx_t* usb4_cm_ctx, BOOLEAN* bondingSuceeded)
{
    UINT32 linkWidth = 1;
    usb4_port_ctx_t *downstreamPort;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    UINT32 elapsed_us;

    USB4_ASSERT(NULL != bondingSuceeded);

    downstreamPort = Usb4RouterGetAdapterPortByNumber(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->router_index], usb4_cm_ctx->m_pHotplug->adapter_first);
    USB4_ASSERT(NULL != downstreamPort);

    *bondingSuceeded = FALSE;
    elapsed_us = 0;
    /* Bonding should take up to 500usec. */
    while (elapsed_us < 501)
    {
        USB4_ASSERT(0 == Usb4PortGetNegotiatedLinkWidth(downstreamPort, &linkWidth));

        if (2 == linkWidth)
        {
            *bondingSuceeded = TRUE;
            break;
        }
        usb4_timer_Sleep_us(&timer, 100);
        elapsed_us += 100;
    }

    return 0;
}

int Usb4CmUpdatePortParametersAfterLanesBonded(usb4_cm_ctx_t* usb4_cm_ctx)
{
    usb4_port_ctx_t *upstreamLane, *downstreamLane;

    if (0 != usb4_cm_ctx->m_pHotplug->next_router_index)
    {
        UINT32 upstreamAdapterNumber = 0;
        upstreamAdapterNumber = usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->next_router_index].m_cs.ROUTER_CS_1.upstreamAdapter;
        USB4_ASSERT(0 != upstreamAdapterNumber);
        upstreamLane = Usb4RouterGetAdapterPortByNumber(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->next_router_index], upstreamAdapterNumber);
        if(NULL != upstreamLane)
        {
            USB4_ASSERT(0 == Usb4PortReadCS(upstreamLane));
            USB4_ASSERT(0 == Usb4PortUpdateTotalBuffers(upstreamLane));
            upstreamLane->m_bIsBound = TRUE;
        }
    }

    downstreamLane = Usb4RouterGetAdapterPortByNumber(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->router_index], usb4_cm_ctx->m_pHotplug->adapter_first);
    if(NULL != downstreamLane)
    {
        USB4_ASSERT(0 == Usb4PortReadCS(downstreamLane));
        USB4_ASSERT(0 == Usb4PortUpdateTotalBuffers(downstreamLane));
        if (USB4_HPE_OUT == downstreamLane->m_hotplug.adapter_second_action)
        {
            downstreamLane->m_hotplug.adapter_second_action = USB4_HPE_NO_ACTION; /* Need to handle unplug at a later time */
        }
        downstreamLane->m_bIsBound = TRUE;
    }
    return 0;
}

/* By default this is disabled since it causes link doesn't rach CL0 */
#if defined(RUMI)
    static BOOLEAN s_bUpdateTmuPolicy = FALSE; 
#else /* !RUMI */
    static BOOLEAN s_bUpdateTmuPolicy = TRUE; 
#endif /* !RUMI */

int Usb4CmUSB4PortHotPlugHandler(usb4_cm_ctx_t* usb4_cm_ctx)
{
    while(1)/* Multiple states may be traversed for a single received packet */
    {
        if (usb4_cm_ctx->m_pParams->bPollingMode)
        {
            Usb4PlatformUcHandleUcEvents(usb4_cm_ctx->m_pQdrv->m_Platform->m_uC); /* Handle uC events to prevent overflow and capture all of them */
        }

        switch(usb4_cm_ctx->m_pHotplug->hotplug_state)
        {
            default:
                Usb4Log1(USB4_LOG_CM, Usb4CmUSB4PortHotPlugHandlerCalledFromUnsupportedStateWARNING__Params, 0, usb4_cm_ctx->m_pHotplug->hotplug_state);
                // USB4_LOG_WARNING("USB4PortHotPlugHandler called from unsupported state %d\n", usb4_cm_ctx->m_pHotplug->hotplug_state);
                return 0;
            case USB4_L0_IN_CLd:
            case USB4_SINGLE_LANE_CL0:
                usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_SINGLE_LANE_CL0; /* We are not in CLd anymore... */
                USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger));

                /* Need to wait for the HPE on first adapter */
                if((0 != usb4_cm_ctx->m_pHotplug->adapter_second)&&(USB4_HPE_IN == usb4_cm_ctx->m_pHotplug->adapter_second_action))
                {
                    usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_L1_IN_CL0;
                    return 0;/* To wait for the second HPE, need to exit this function */
                }
                if (USB4_HPE_IN != usb4_cm_ctx->m_pHotplug->adapter_first_action)
                {
                    goto ExitToIdle;
                }
                usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_ENUMERATE_NEW_ROUTER;
                break;
            case USB4_L1_IN_CL0:
                USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger));
                if ((USB4_HPE_IN != usb4_cm_ctx->m_pHotplug->adapter_second_action) && (USB4_HPE_IN != usb4_cm_ctx->m_pHotplug->adapter_first_action))
                {
                    /* No adapter has a plug-in state, so update paths and exit */
                    goto UpdatePathAndExitToIdle;
                }
                if (USB4_HPE_IN != usb4_cm_ctx->m_pHotplug->adapter_first_action)
                {
                    /* First adapter has to have an HPE_IN state, or can't enumerate router */
                    return 0;
                }
                usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_ENUMERATE_NEW_ROUTER;
                break; /* Immediately transition to the next state */
            case USB4_HOTPLUG_ENUMERATE_NEW_ROUTER:
            {
                BOOLEAN dfp0_connected = FALSE, bondingPossible;

                UINT32 parent_router_index = usb4_cm_ctx->m_router_index;

                USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger));
                if ((usb4_cm_ctx->m_pHotplug->adapter_second == usb4_cm_ctx->m_pHotplug->modifiedAdapter) &&
                    (USB4_HPE_IN == usb4_cm_ctx->m_pHotplug->adapter_second_action))
                {
                    /* Nothing to do on Re-entry, before handling an enumeration error */
                    return 0;
                }

                /* Check for valid connection on L0 at least */
                USB4_ASSERT(0 == Usb4RouterUnlockAdapter(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_first));
                USB4_ASSERT(0 == Usb4RouterDfpConnected(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_first, &dfp0_connected));
                USB4_ASSERT(TRUE == dfp0_connected);
                if (0 == usb4_cm_ctx->m_pHotplug->next_router_topologyID) /* Happens if lane was un-plugged/re-plugged */
                {
                    usb4_cm_ctx->m_pHotplug->next_router_topologyID = usb4_next_router_topology(usb4_cm_ctx->m_pHotplug->router_topologyID, usb4_cm_ctx->m_pHotplug->adapter_first);
                }
                USB4_ASSERT(0 == Usb4CmPlaceRouterByTopology(usb4_cm_ctx, usb4_cm_ctx->m_pHotplug->next_router_topologyID));
                usb4_cm_ctx->m_pHotplug->next_router_index = usb4_cm_ctx->m_router_index;
                //Enumerate next router - if more routers are chained, more HPEs will arrive.
                //So only do a single step at this time
                if (0 != Usb4RouterEnumerate(Usb4CmRouter(usb4_cm_ctx)))
                {
                    Usb4Log(USB4_LOG_CM, Usb4CmUSB4PortHotPlugHandlerEnumerationOfTheRouterFailedExpectErrEnumOrErrNua__Info, 0);
                    // USB4_LOG_INFO("Enumeration of the router failed. Expect ERR_ENUM or ERR_NUA.\n");
                    Usb4CmRouter(usb4_cm_ctx)->m_bEnumerationError = TRUE;
                    usb4_cm_ctx->m_router_index = parent_router_index;
                    //goto ExitToIdle;
                    //Will re-use the same m_hotplug structure for inter-domain state machine, so don't zero it.
                    //TODO: If enumeration error happened for device router, need a way to fail....
                    return 0;
                }

                /* Move current router back to parent */
                usb4_cm_ctx->m_router_index = parent_router_index;

                if (usb4_cm_ctx->m_pHotplug->retries < USB4_MAX_BONDING_RETRIES)
                {
                    /* Normal flow */
                    usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_BOND_LANES;
                }
                else
                {
                    /* Will not attempt bonding, disable Lane 1 */
                    usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_DISABLE_LANE1;
                    break;
                }

                USB4_ASSERT(0 == Usb4CmCheckBondingIsPossible(usb4_cm_ctx, &bondingPossible));
                if (FALSE == bondingPossible)
                {
                    /* Bonding is not possible */
                    usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_DISABLE_LANE1;
                }
                else
                {
                    /* Expect to receive and handle HP IN on Lane 1 */
                    return 0;
                }
                break;
            }
            case USB4_HOTPLUG_DISABLE_LANE1:
                USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger));
                USB4_ASSERT(0 == Usb4RouterDisconnectAdapter(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_second));
                if (0 != usb4_cm_ctx->m_pHotplug->next_router_index)
                {
                    UINT32 upstreamAdapterNumber = usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->next_router_index].m_cs.ROUTER_CS_1.upstreamAdapter;
                    USB4_ASSERT(0 != upstreamAdapterNumber);
                    USB4_ASSERT(0 == Usb4RouterDisconnectAdapter(&usb4_cm_ctx->m_routers[usb4_cm_ctx->m_pHotplug->next_router_index], upstreamAdapterNumber+1));
                }
                usb4_cm_ctx->m_pHotplug->adapter_second_action = USB4_HPE_NO_ACTION;
                usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_BUILD_PATHS;
                break;
            case USB4_HOTPLUG_BOND_LANES:
                USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger));
                if (0 != Usb4CmHandleLaneBonding(usb4_cm_ctx))
                {
                    USB4_ERROR_STACK(-1);
                    return -1;
                }
                usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_CHECK_LANES_BONDED;
                return 0; /* Expect HPG OUT on one or more lines */
            case USB4_HOTPLUG_CHECK_LANES_BONDED:
            {
                BOOLEAN bondingSuceeded;

                USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger));
                USB4_ASSERT(0 == Usb4CmCheckBondingSuceeded(usb4_cm_ctx, &bondingSuceeded));
                if(bondingSuceeded)
                {
                    USB4_ASSERT(0 == Usb4CmUpdatePortParametersAfterLanesBonded(usb4_cm_ctx));
                    usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_BUILD_PATHS;
                }
                else
                {
                    usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_DOWNSTREAM_PORT_RESET;
                }
                break;
            }
            case USB4_HOTPLUG_BUILD_PATHS:
                if ((usb4_cm_ctx->m_pHotplug->modifiedAdapter == usb4_cm_ctx->m_pHotplug->adapter_second)&&(USB4_HPE_OUT == usb4_cm_ctx->m_pHotplug->adapter_second_action))
                {
                    usb4_cm_ctx->m_pHotplug->adapter_second_action = USB4_HPE_NO_ACTION;
                    return 0;
                }
                USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger));
                USB4_ASSERT(0 == Usb4CmEnableTunneling(usb4_cm_ctx));
                goto UpdatePathAndExitToIdle;

            case USB4_HOTPLUG_DOWNSTREAM_PORT_RESET:
                USB4_ASSERT(0 == Usb4CmLoggerStoreHotPlugStateMachineState(&usb4_cm_ctx->m_logger));
                usb4_cm_ctx->m_pHotplug->retries++;
                usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_SINGLE_LANE_CL0;
                usb4_cm_ctx->m_pHotplug->adapter_first_action = USB4_HPE_NO_ACTION;
                usb4_cm_ctx->m_pHotplug->adapter_second_action = USB4_HPE_NO_ACTION;

                //TODO: Add code to ignore any notifications packets and interrupts during port reset flow.
                //It re-initializes a link so control transfers will not come through
                USB4_ASSERT(0 == Usb4RouterResetAdapter(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_first));
                return 0; /* Wait for HPG event... */
        }
    }

UpdatePathAndExitToIdle:
    if (FALSE != s_bUpdateTmuPolicy)
    {
        USB4_ASSERT(0 == Usb4CmUpdateDomainTMUPolicy(usb4_cm_ctx));
    }

    if (0 !=  Usb4PathManagerUpdatePaths(&usb4_cm_ctx->m_path_manager))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

//    if (FALSE != s_bUpdateTmuPolicy)
//    {
//        USB4_ASSERT(0 == PollForTMUSync());
//    }

ExitToIdle:
    return 0;
}

/*-------------------------------------------------------*/

int Usb4CmDPAdaptersExchangeCapabilities(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 sinkAdapterRouterIndex,
                                                  UINT32 sinkAdapter)
{ 
    usb4_router_ctx_t* pRouter;
    usb4_port_ctx_t* pDpInAdapter;
    usb4_port_ctx_t* pDpOutAdapter;
    usb4_adp_dp_in_cs dpInCs;
    usb4_adp_dp_out_cs dpOutCs;
    BOOLEAN isUSB4Device;

    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    UINT32 timeout_ms;
    UINT32 elapsed_ms;   
    usb4_router_operation_params opParams = {0};

    /*-------------------------------------*/
    /*        === Get Endpointes ===       */
    /*-------------------------------------*/

    /* Get remote router */
    USB4_ASSERT(0 == Usb4CmGetRouterByIdx(usb4_cm_ctx, sinkAdapterRouterIndex, &pRouter));

    /* Get DP out adapter */
    pDpOutAdapter = Usb4RouterGetAdapterPortByType(pRouter, USB4_portType_DP_OUT, sinkAdapter);
   
    /* Validate remote adapter was found */
    USB4_ASSERT(NULL != pDpOutAdapter);

    /* Get the type of sink */
    isUSB4Device = (pRouter->m_cs.ROUTER_CS_4.usb4Version >= 0x20);

    /* Get host router */ 
    USB4_ASSERT(0 == Usb4CmGetRouterByIdx(usb4_cm_ctx, 0, &pRouter));

    /* Get DP In adapter */
    pDpInAdapter =  Usb4RouterGetAdapterPortByType(pRouter, USB4_portType_DP_IN, 0);

    /* Validate adapter was found */
    USB4_ASSERT(NULL != pDpInAdapter);

    /*-------------------------------------*/

    /* Query DP resource */
    opParams.opcode = USB4_ROUTER_OPERATION_QUERY_DP_RESOURCE_AVAILABILITY;
    opParams.metaData = pDpInAdapter->m_Number;
    USB4_ASSERT(0 == Usb4RouterIssueRouterOperation(pRouter, &opParams, 1000));
    USB4_ASSERT(0 == opParams.status);

    /* Allocte DP resource to the host router*/
    opParams.opcode = USB4_ROUTER_OPERATION_ALLOCATE_DP_RESOURCE;
    opParams.metaData = pDpInAdapter->m_Number;
    USB4_ASSERT(0 == Usb4RouterIssueRouterOperation(pRouter, &opParams, 1000));
    USB4_ASSERT(0 == opParams.status );


    /* Read the DP out adapter configuration space */
    USB4_ASSERT(0 == Usb4PortSearchCapability(pDpOutAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
    USB4_ASSERT(0 == Usb4PortReadCapability(pDpOutAdapter,
        (UINT8*)(&dpOutCs),
        sizeof(dpOutCs)));
    
    if (isUSB4Device)
    {
        /* Set to USB4 mode */
        dpOutCs.DP_STATUS_CTRL.DPInAdapterUSB4Flag_UF = 1;

        /* Initiate CM handshake */
        dpOutCs.DP_STATUS_CTRL.CMHandshake_CMHS = 1;

        USB4_ASSERT(0 == Usb4PortSearchCapability(pDpOutAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
        USB4_ASSERT(0 == Usb4PortWriteCapability(pDpOutAdapter, (UINT8*)(&dpOutCs),
                                                        sizeof(dpOutCs)));

        elapsed_ms = 0;
        timeout_ms = 500;
        USB4_ASSERT(0 == usb4_timer_Start(&timer));

        USB4_ASSERT(0 == Usb4PortSearchCapability(pDpOutAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));

        //////////////////
        /* Poll DP out adapter */
        do
        {
            USB4_ASSERT(0 == Usb4PortReadCapability(pDpOutAdapter, (UINT8*)(&dpOutCs), 
                                                           sizeof(dpOutCs)));
            /* Check for reset timeout */
            USB4_ASSERT(0 == usb4_timer_GetElapsed_ms(&timer, &elapsed_ms));
            USB4_ASSERT(elapsed_ms < timeout_ms);
            usb4_timer_Sleep_ms(&timer, 10);
        }
        while(0 != dpOutCs.DP_STATUS_CTRL.CMHandshake_CMHS);
    }
    else /* TBT3 device */
    {
        USB4_ASSERT(0 == Usb4PortSearchCapability(pDpOutAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
        USB4_ASSERT(0 == Usb4PortReadCapability(pDpOutAdapter, (UINT8*)(&dpOutCs), 
                                                                        sizeof(dpOutCs)));
        /* Initiate tbt3 handshake */
        dpOutCs.DP_STATUS_CTRL.CMHandshake_CMHS = 0x0;
        dpOutCs.DP_STATUS_CTRL.DPInAdapterUSB4Flag_UF = 0x0;                                          
        dpOutCs.DP_REMOTE_CAP.ProtocolAdapterVersion = 0x3;   

        USB4_ASSERT(0 == Usb4PortSearchCapability(pDpOutAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
        USB4_ASSERT(0 == Usb4PortWriteCapability(pDpOutAdapter, (UINT8*)(&dpOutCs), 
                                                                        sizeof(dpOutCs)));                                                             
    }
    
    /* Read the DP in adapter configuration space */
    USB4_ASSERT(0 == Usb4PortSearchCapability(pDpInAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
    USB4_ASSERT(0 == Usb4PortReadCapability(pDpInAdapter, 
        (UINT8*)(&dpInCs),
        sizeof(dpInCs)));

    /* Copy capabilites to DP OUT adapter */
    usb4_mem_memcpy(&dpOutCs.DP_REMOTE_CAP, &dpInCs.DP_LOCAL_CAP, sizeof(dpOutCs.DP_REMOTE_CAP));

    USB4_ASSERT(0 == Usb4PortSearchCapability(pDpOutAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
    USB4_ASSERT(0 == Usb4PortWriteCapability(pDpOutAdapter, 
        (UINT8*)(&dpOutCs),
        sizeof(dpOutCs)));

    /* Copy capabilites to DP IN adapter */
    usb4_mem_memcpy(&dpInCs.DP_REMOTE_CAP, &dpOutCs.DP_LOCAL_CAP, sizeof(dpOutCs.DP_REMOTE_CAP));
    USB4_ASSERT(0 == Usb4PortSearchCapability(pDpInAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
    USB4_ASSERT(0 == Usb4PortWriteCapability(pDpInAdapter, 
        (UINT8*)(&dpInCs),
        sizeof(dpInCs)));
    
    return 0;
}

/*-------------------------------------------------------*/

int Usb4CmUpdateDomainTMUPolicyTmuMode(usb4_cm_ctx_t* usb4_cm_ctx, USB4_tmu_mode tmuMode)
{
    UINT32 routerIdx;
    int rv;
    USB4_ASSERT(NULL != usb4_cm_ctx->m_pParams);
    usb4_cm_ctx->m_domainTmuMode = tmuMode;

    while (0 != Usb4CmTryLockCm(usb4_cm_ctx))
    {};

    for (routerIdx = 0; routerIdx < USB4_MAX_SUPPORTED_ROUTERS; routerIdx++)
    {
        if (FALSE == Usb4RouterIsEnumerated(&usb4_cm_ctx->m_routers[routerIdx]))
        {
            continue;
        }
        usb4_cm_ctx->m_routers[routerIdx].m_tmuCurrentMode = USB4_TMU_MODE_NOT_SET;
    }

    rv = Usb4CmUpdateDomainTMUPolicy(usb4_cm_ctx);
    USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
    return rv;
}

/*-------------------------------------------------------*/

int Usb4CmUpdateDomainTMUPolicy(usb4_cm_ctx_t* usb4_cm_ctx)
{
    UINT32 routerIdx;
    USB4_router_tmu_capability routerTmuCap;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    if (USB4_TMU_MODE_NOT_SET == usb4_cm_ctx->m_routers[0].m_tmuCurrentMode)
    {
        switch (usb4_cm_ctx->m_domainTmuMode)
        {
            case USB4_TMU_MODE_NOT_SET:
                USB4_ASSERT(0 == Usb4RouterTMUSetMode(&usb4_cm_ctx->m_routers[0], USB4_TMU_MODE_BI_DIRECTIONAL_HIFI));
                USB4_ASSERT(0 == Usb4RouterTMUTimeSync(&usb4_cm_ctx->m_routers[0], TRUE));
                break;
            case USB4_TMU_MODE_OFF:
                USB4_ASSERT(0 == Usb4RouterTMUSetMode(&usb4_cm_ctx->m_routers[0], USB4_TMU_MODE_OFF));
                break;
            default:
                USB4_ASSERT(0 == Usb4RouterTMUSetMode(&usb4_cm_ctx->m_routers[0], usb4_cm_ctx->m_domainTmuMode));
                USB4_ASSERT(0 == Usb4RouterTMUTimeSync(&usb4_cm_ctx->m_routers[0], TRUE));
                break;
        }
    }

//    for (routerIdx = USB4_MAX_SUPPORTED_ROUTERS-1; routerIdx > 0 /* Skip Host router */; routerIdx--)
    for (routerIdx = 1; routerIdx < USB4_MAX_SUPPORTED_ROUTERS; routerIdx++)
    {

        if (FALSE == Usb4RouterIsEnumerated(&usb4_cm_ctx->m_routers[routerIdx]))
        {
            continue;
        }

        if (USB4_TMU_MODE_NOT_SET != usb4_cm_ctx->m_routers[routerIdx].m_tmuCurrentMode)
        {
            USB4_ASSERT(0 == Usb4RouterTMUTimeSync(&usb4_cm_ctx->m_routers[routerIdx], TRUE)); /* Some additional ports could have been connected */
            continue;
        }

        /* Write  tmu setup values for TBT3. USB4 has correct defulat values */
        USB4_ASSERT(0 == Usb4RouterSearchCapability(&usb4_cm_ctx->m_routers[routerIdx], USB4_ROUTER_CAP_TMU, NULL));
        USB4_ASSERT(0 == Usb4RouterReadCapability(&usb4_cm_ctx->m_routers[routerIdx],
                     (UINT8*)(&routerTmuCap),
                     sizeof(routerTmuCap)));
        /* Set universal settings */
        routerTmuCap.TMU_RTR_CS_0.FreqMeasurementWindow = 0x320;
        routerTmuCap.TMU_RTR_CS_0.InterDomainEnable_IDE = 0x0;
        routerTmuCap.TMU_RTR_CS_0.TimeDisruption_TD = 0x1;

        routerTmuCap.TMU_RTR_CS_15.DelayAvgConst = 0x8;
        routerTmuCap.TMU_RTR_CS_15.ErrorAvgConst = 0x8;
        routerTmuCap.TMU_RTR_CS_15.FreqAvgConst = 0x8;
        routerTmuCap.TMU_RTR_CS_15.OffsetAvgConst = 0x8;
        routerTmuCap.TMU_RTR_CS_15.TSInterDomainInterval = 0x0;

        USB4_ASSERT(0 == Usb4RouterSearchCapability(&usb4_cm_ctx->m_routers[routerIdx], USB4_ROUTER_CAP_TMU, NULL));
        USB4_ASSERT(0 == Usb4RouterWriteCapability(&usb4_cm_ctx->m_routers[routerIdx],
                     (UINT8*)(&routerTmuCap),
                    sizeof(routerTmuCap)));

        switch (usb4_cm_ctx->m_domainTmuMode)
        {
            case USB4_TMU_MODE_NOT_SET:
                USB4_ASSERT(0 == Usb4RouterTMUSetMode(&usb4_cm_ctx->m_routers[routerIdx], USB4_TMU_MODE_BI_DIRECTIONAL_HIFI));
                USB4_ASSERT(0 == Usb4RouterTMUTimeSync(&usb4_cm_ctx->m_routers[routerIdx], TRUE));
                break;
            case USB4_TMU_MODE_OFF:
                USB4_ASSERT(0 == Usb4RouterTMUSetMode(&usb4_cm_ctx->m_routers[routerIdx], USB4_TMU_MODE_OFF));
                break;
            default:
                USB4_ASSERT(0 == Usb4RouterTMUSetMode(&usb4_cm_ctx->m_routers[routerIdx], usb4_cm_ctx->m_domainTmuMode));
                USB4_ASSERT(0 == Usb4RouterTMUTimeSync(&usb4_cm_ctx->m_routers[routerIdx], TRUE));
                break;
        }
        //Moved outside of enumeration path
#ifdef USB4_LOAD_VENDOR_SETTINGS_ON_LENOVO_DOCK 
        /* This will break any other TBT3 device
         * Display need to be connected on the USB4 downstream receptacle with adapter - not on a regular DP port */
        USB4_ASSERT(0 == Usb4RouterLoadVendorSettings(&usb4_cm_ctx->m_routers[routerIdx]));
#endif
    }



    return 0;
}

int Usb4CmPollForTMUSync(usb4_cm_ctx_t* usb4_cm_ctx)
{
    //UINT64 nano_seconds;
    //uint16 fraq_nano_seconds;
    UINT32 elapsed_ms;
    UINT32 i;
    UINT32 routerIdx;
    USB4_router_tmu_capability routerTmuCap;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    static UINT32 current_max_router = 0;

    for (routerIdx = USB4_MAX_SUPPORTED_ROUTERS-1; routerIdx > 0 /* Skip Host router */; routerIdx--)
    {
        if (FALSE == Usb4RouterIsEnumerated(&usb4_cm_ctx->m_routers[routerIdx]))
        {
            continue;
        }

        if(current_max_router >= routerIdx)
        {
            break;
        }
        else
        {
            if (current_max_router < routerIdx)
            {
                current_max_router = routerIdx;
            }
        }
        USB4_ASSERT(0 == Usb4RouterSearchCapability(&usb4_cm_ctx->m_routers[routerIdx], USB4_ROUTER_CAP_TMU, NULL));
        USB4_ASSERT(0 == usb4_timer_Start(&timer));
        for (i = 0; i < 10; i++)
        {
            int val;
            USB4_ASSERT(0 == Usb4RouterReadCapability(&usb4_cm_ctx->m_routers[routerIdx],
                         (UINT8*)(&routerTmuCap),
                        sizeof(routerTmuCap)));
            val = (int)(routerTmuCap.TMU_RTR_CS_9.FreqOffsetFromMaster);
            Usb4Log2(USB4_LOG_CM, Usb4CmPollForTMUSync__Params__NewRouterFreqOffsetFromMaster_Val, 0, 
                routerTmuCap.TMU_RTR_CS_9.FreqOffsetFromMaster, val);
            Usb4Log2(USB4_LOG_CM, Usb4CmPollForTMUSync__Params__LowLimit_HighLimit, 0, 
                (int)(0xF2E48E40), (int)(0xD1B71C0));
            // USB4_LOG_INFO("New router FRequencyOffsetFromMaster 0x%x, (%d) Low limit: %d, high limit %d \n", routerTmuCap.TMU_RTR_CS_9.FreqOffsetFromMaster, val,
            //        (int)(0xF2E48E40), (int)(0xD1B71C0));
            if ((val < (int)(0xF2E48E40)) || (val > (int)(0xD1B71C0)))
            {
                //goto RetryTMU;
                i = 0;
            }
        }
        USB4_ASSERT(0 == usb4_timer_GetElapsed_ms(&timer, &elapsed_ms));
        Usb4Log1(USB4_LOG_CM, Usb4CmPollForTMUSyncSyncTook__Params__msec, 0, elapsed_ms);
        // USB4_LOG_INFO("Sync took %u msec\n", USB4_LOWER32(elapsed_ms));

    }
    
    return 0;
}

int Usb4CmAdapterPortHotPlugHandler(usb4_cm_ctx_t* usb4_cm_ctx)
{ 
    USB4_cpDescriptorType desc_type;
    UINT32 unplug_flag = 0;
    UINT64 router_topologyID = 0;
    UINT32 adapter;
    UINT32 router_index;

    adapter = usb4_cm_ctx->m_pHotplug->adapter_first;
    router_topologyID = usb4_cm_ctx->m_pHotplug->router_topologyID;
    unplug_flag = (USB4_HPE_OUT == usb4_cm_ctx->m_pHotplug->adapter_first_action);
    USB4_ASSERT(0 == Usb4CtrlIfaceGetType(Usb4CmControl(usb4_cm_ctx), &desc_type));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetUPG(Usb4CmControl(usb4_cm_ctx), &unplug_flag));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(Usb4CmControl(usb4_cm_ctx), &router_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetAdapter(Usb4CmControl(usb4_cm_ctx), &adapter));

    if (0 != Usb4RouterAdapterHotPlug(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_first, unplug_flag))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    if (unplug_flag)
    {
        if (0 != Usb4PathManagerInvalidatePathFromPort(&usb4_cm_ctx->m_path_manager, router_topologyID,
                        adapter))
        {
            USB4_ERROR_STACK(-1);
            return -1;
        }
    }
    else
    {
        if (FALSE != s_bUpdateTmuPolicy)
        {
            USB4_ASSERT(0 == Usb4CmUpdateDomainTMUPolicy(usb4_cm_ctx));
        }

        /* Find the index of the router */
        USB4_ASSERT(0 == Usb4CmFindRouterByTopologyByIndex(usb4_cm_ctx, router_topologyID, &router_index));

        /* Start DP link bring up */
        if (0 == Usb4CmDPAdaptersExchangeCapabilities(usb4_cm_ctx, router_index, adapter))
        {
          /* Build DP path */
          if (2 == usb4_cm_ctx->m_pParams->numLanes)
          {
            USB4_pathParamsOverrideType params = {0};
            params.pathType = USB4_pathType_DP_MAIN;
            params.bOverrideActive = TRUE;
            params.bRouterIndexValid = TRUE;
            params.routerIndex = router_index;;
            params.bNumOfBuffersValid = TRUE;
            params.numOfBuffers = 0x38;
            /* Modify number of credits in case of dual lane initialization */
            USB4_ASSERT(0 == Usb4PathManagerOverridePathParameters(&usb4_cm_ctx->m_path_manager, params));
          }
          USB4_ASSERT(0 == Usb4PathManagerUpdatePaths(&usb4_cm_ctx->m_path_manager));
        }
    }

    /* Enable paths */
    //USB4_ASSERT(0 == DPAdaptersEnablePaths(router_index, adapter));
    return 0;
}

int Usb4CmDPAdaptersEnablePaths(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 sinkAdapterRouterIndex,
                                         UINT32 sinkAdapter)
{

    usb4_router_ctx_t* pRouter;
    usb4_port_ctx_t* pDpInAdapter;
    usb4_port_ctx_t* pDpOutAdapter;
    usb4_adp_dp_in_cs dpInCs;
    usb4_adp_dp_out_cs dpOutCs;

    /* Get remote router */
    USB4_ASSERT(0 == Usb4CmGetRouterByIdx(usb4_cm_ctx, sinkAdapterRouterIndex, &pRouter));

    /* Get DP out adapter */
    pDpOutAdapter = Usb4RouterGetAdapterPortByType(pRouter, USB4_portType_DP_OUT, sinkAdapter);

    /* Validate remote adapter was found */
    if(NULL == pDpOutAdapter)
    {
        return -1;
    }

    /* Get host router */ 
    USB4_ASSERT(0 == Usb4CmGetRouterByIdx(usb4_cm_ctx, 0, &pRouter));

    /* Get DP In adapter */
    pDpInAdapter =  Usb4RouterGetAdapterPortByType(pRouter, USB4_portType_DP_IN, 0);

    /* Validate adapter was found */
    USB4_ASSERT(NULL != pDpInAdapter);

    USB4_ASSERT(0 == Usb4PortSearchCapability(pDpInAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
    USB4_ASSERT(0 == Usb4PortReadCapability(pDpInAdapter, 
        (UINT8*)(&dpInCs),
        sizeof(dpInCs)));

    USB4_ASSERT(0 == Usb4PortSearchCapability(pDpOutAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
    USB4_ASSERT(0 == Usb4PortReadCapability(pDpOutAdapter, 
        (UINT8*)(&dpOutCs),
        sizeof(dpOutCs)));

    /* Write video and aux HOP id */
    dpOutCs.ADP_DP_CS_0.videoHopId = 0x9;
    dpOutCs.ADP_DP_CS_1.auxRxHopId = 0x8;
    dpOutCs.ADP_DP_CS_1.auxTxHopId = 0x8;

    USB4_ASSERT(0 == Usb4PortSearchCapability(pDpOutAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
    USB4_ASSERT(0 == Usb4PortWriteCapability(pDpOutAdapter, 
        (UINT8*)(&dpOutCs),
        sizeof(dpOutCs)));

    /* Enable DP In */
    dpInCs.ADP_DP_CS_0.auxEnable = 1;
    dpInCs.ADP_DP_CS_0.videoEnable = 1;
    USB4_ASSERT(0 == Usb4PortSearchCapability(pDpInAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
    USB4_ASSERT(0 == Usb4PortWriteCapability(pDpInAdapter, 
        (UINT8*)(&dpInCs),
        sizeof(dpInCs)));

    /* Enable DP Out*/
    dpOutCs.ADP_DP_CS_0.auxEnable = 1;
    dpOutCs.ADP_DP_CS_0.videoEnable = 1;
    USB4_ASSERT(0 == Usb4PortSearchCapability(pDpOutAdapter, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
    USB4_ASSERT(0 == Usb4PortWriteCapability(pDpOutAdapter, 
        (UINT8*)(&dpOutCs),
        sizeof(dpOutCs)));

    return 0;
}


int Usb4CmStatelessPacketsHandler(usb4_cm_ctx_t* usb4_cm_ctx)
{
    USB4_cpDescriptorType desc_type=USB4_cpDescriptorType_UNKNOWN_DESCRIPTOR;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetType(Usb4CmControl(usb4_cm_ctx), &desc_type));
    switch (desc_type)
    {
        case USB4_cpDescriptorType_NOTIFICATION:
        {
            UINT64 router_topologyID;
            USB4_cpNotificationEvent event;
            UINT32 adapter;

            USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(Usb4CmControl(usb4_cm_ctx), &router_topologyID));
            USB4_ASSERT(0 == Usb4CtrlIfaceGetAdapter(Usb4CmControl(usb4_cm_ctx), &adapter));
            USB4_ASSERT(0 == Usb4CtrlIfaceGetEventCode(Usb4CmControl(usb4_cm_ctx), &event));

            switch(event)
            {
                case USB4_cpNotificationEvent_ERR_CONN:
                    USB4_ASSERT(0 == Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));
                    /* Specify current router which will undergo operations */
                    USB4_ASSERT(0 == Usb4CmFindRouterByTopology(usb4_cm_ctx, router_topologyID));
                    USB4_ASSERT(0 == Usb4RouterDisconnectAdapter(Usb4CmRouter(usb4_cm_ctx), adapter));
                    if (0 != Usb4PathManagerUpdatePaths(&usb4_cm_ctx->m_path_manager))
                    {
                        USB4_ERROR_STACK(-1);
                        return -1;
                    }
                    break;
                case USB4_cpNotificationEvent_ERR_ADDR:
                    Usb4Log(USB4_LOG_CM, Usb4CmStatelessPacketsHandlerERR_ADDRreceived__Warn, 0);
                    // USB4_LOG_WARNING("ERR_ADDR Received\n");
                    USB4_ASSERT(0 == Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));
                    break;
                case USB4_cpNotificationEvent_ERR_ADP :
                    Usb4Log(USB4_LOG_CM, Usb4CmStatelessPacketsHandlerERR_ADPreceived__Warn, 0);
                    // USB4_LOG_WARNING("ERR_ADP Received\n");
                    USB4_ASSERT(0 == Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));
                    break;
                case USB4_cpNotificationEvent_ERR_LEN :
                    Usb4Log(USB4_LOG_CM, Usb4CmStatelessPacketsHandlerERR_LENreceived__Warn, 0);
                    // USB4_LOG_WARNING("ERR_LEN Received\n");
                    USB4_ASSERT(0 == Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));
                    break;
                case USB4_cpNotificationEvent_ERR_HEC :
                    Usb4Log(USB4_LOG_CM, Usb4CmStatelessPacketsHandlerERR_HECreceived__Warn, 0);
                    // USB4_LOG_WARNING("ERR_HEC Received\n");
                    USB4_ASSERT(0 == Usb4CtrlIfaceSendAck(Usb4CmControl(usb4_cm_ctx)));
                    USB4_ASSERT(0 == Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));
                    break;
                case USB4_cpNotificationEvent_ERR_FC  :
                    Usb4Log(USB4_LOG_CM, Usb4CmStatelessPacketsHandlerERR_FCreceived__Warn, 0);
                    // USB4_LOG_WARNING("ERR_FC Received\n");
                    USB4_ASSERT(0 == Usb4CtrlIfaceSendAck(Usb4CmControl(usb4_cm_ctx)));
                    USB4_ASSERT(0 == Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));
                    break;
                case USB4_cpNotificationEvent_ERR_PLUG:
                    Usb4Log(USB4_LOG_CM, Usb4CmStatelessPacketsHandlerERR_PLUGreceived__Warn, 0);
                    // USB4_LOG_WARNING("ERR_PLUG Received\n");
                    USB4_ASSERT(0 == Usb4CtrlIfaceSendAck(Usb4CmControl(usb4_cm_ctx)));
                    USB4_ASSERT(0 == Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));
                    {   /* Attempt to re-launch uC */
                        UINT32 LastErr,  ProgramCounter, Num;

                        USB4_ASSERT(0 == Usb4PlatformUcGetPropreitryError(usb4_cm_ctx->m_pQdrv->m_Platform->m_uC, &LastErr, &ProgramCounter, &Num));
                        if (Num > 0)
                        {
                            Usb4Log2(USB4_LOG_CM, Usb4CmStatelessPacketsHandler__Params__Core_uCSignalledError, 0, 
                                Usb4PlatformGetCoreIndex(usb4_cm_ctx->m_pQdrv->m_Platform), LastErr);
                            // USB4_LOG_WARNING("Core[%u] uC signalled error %u\n", Usb4PlatformGetCoreIndex(usb4_cm_ctx->m_pQdrv->m_Platform), LastErr);
                            if (5 == LastErr)
                            {
                                static uint32 total_retries = 0;
                                if ((0 == (usb4_cm_ctx->m_quirks & USB4_CM_QUIRK_ERR_PLUG_IS_FATAL_NO_RETRY))&&(total_retries++ < 2))
                                {
                                    /* HSE establishment failed - Attempt again */
                                    USB4_ASSERT(0 == Usb4QDrvEstablishHsConnection(usb4_cm_ctx->m_pQdrv, &usb4_cm_ctx->m_pdInfo));
                                    if ((0 != usb4_cm_ctx->m_pParams->controlPacketsTimeout_ms)&&(TRUE == usb4_cm_ctx->m_pParams->bPollingMode))
                                    {
                                        USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
                                        USB4_ASSERT(0 == Usb4CmWaitForCl0(usb4_cm_ctx, usb4_cm_ctx->m_pParams->controlPacketsTimeout_ms));
                                        while (0 != Usb4CmTryLockCm(usb4_cm_ctx));
                                    }
                                }
                                else
                                {
                                    Usb4Log(USB4_LOG_CM, Usb4CmStatelessPacketsHandlerNoRetryProhibitedByUSB4_CM_QUIRK_ERR_PLUG_IS_FATAL_NO_RETRY__Warn, 0);
                                    // USB4_LOG_WARNING("No retry, prohibited by USB4_CM_QUIRK_ERR_PLUG_IS_FATAL_NO_RETRY\n");
                                }
                            }
                        }
                    }
                    break;
                case USB4_cpNotificationEvent_ERR_LOCK:
                    USB4_ASSERT(Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));
                    USB4_ASSERT(0 == Usb4CmFindRouterByTopology(usb4_cm_ctx, router_topologyID));
                    USB4_ASSERT(0 == Usb4RouterUnlockAdapter(Usb4CmRouter(usb4_cm_ctx), adapter));
                    break;
                default:
                    USB4_ERROR_STACK_MSG(-1, "Un-handled notification Event");
                    USB4_ASSERT(Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));
                    goto ErrorHandling;
            }
            break;
        }
        default:
            USB4_ERROR_STACK_MSG(-1, "Un-handled Event");
            
            /* Clear junk */
            USB4_ASSERT(0 == Usb4CtrlIfacePop(Usb4CmControl(usb4_cm_ctx)));

            goto ErrorHandling;
    }

    return 0;
ErrorHandling:
    return -1;
}

/* --------------------------------------------------------------------------
 * Static Functions
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Functions
 *--------------------------------------------------------------------------*/

