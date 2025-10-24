/**---------------------------------------------------------------------------
 *   @file       usb4_path_segment.c
 *
 *   @brief      Implementation of Path Router methods
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/

#include <Usb4Log.h>
#include <Usb4Utils.h>
#include "usb4_router.h"
#include "usb4_path_segment.h"
// #include "VVDRV_usb4_path.h"
#include <string.h>

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/

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


int Usb4PathSegmentInit(usb4_path_segment_ctx_t* usb4_path_segment_ctx, usb4_router_ctx_t* pRouters)
{
    usb4_path_segment_ctx->m_routerIndex = 0;
    usb4_path_segment_ctx->m_usb4DowstreamPortNumber = 0;
    usb4_path_segment_ctx->m_egressHopID = 0;
    usb4_path_segment_ctx->m_ingressHopID = 0;

    usb4_path_segment_ctx->m_adapterPort = NULL;
    usb4_path_segment_ctx->m_usb4DN = NULL;
    usb4_path_segment_ctx->m_usb4UP = NULL;
    usb4_path_segment_ctx->m_adapterPortType = USB4_portType_NOT_VALID;
    usb4_path_segment_ctx->m_pRouters = pRouters;

    usb4_path_segment_ctx->m_srcPort = NULL;
    usb4_path_segment_ctx->m_dstPort = NULL;
    usb4_path_segment_ctx->m_pathCreditsAllocated = 0;
    usb4_path_segment_ctx->m_linkCreditsAllocated = 0; /* If not 0, the segment is H2H, with shared flow control */
    usb4_path_segment_ctx->m_bDirectionOut = FALSE;
    usb4_path_segment_ctx->m_bAux = FALSE;

    memset((UINT8*)(&usb4_path_segment_ctx->pathCs), 0, sizeof(usb4_path_segment_ctx->pathCs));
    memset((UINT8*)(&usb4_path_segment_ctx->m_pathCsParamsOverride), 0, sizeof(usb4_path_segment_ctx->m_pathCsParamsOverride));

    return 0;
}

// #define USB4_CR_QCTDD06588513_HIA_SHARED_BUFFERS_VALIDATION

int Usb4PathSegmentFIllPathCs(usb4_path_segment_ctx_t* usb4_path_segment_ctx)
{
    usb4_path_segment_ctx->pathCs.PATH_CS_0.OutputAdapter = usb4_path_segment_ctx->m_dstPort->m_Number;
    usb4_path_segment_ctx->pathCs.PATH_CS_0.OutputHopID = usb4_path_segment_ctx->m_egressHopID;
    usb4_path_segment_ctx->pathCs.PATH_CS_0.Valid = 1;

    /* Ingress adapter type */
    USB4_portType type = Usb4PortGetPortType(usb4_path_segment_ctx->m_srcPort);
    
    if (0 == usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated)
    {
        usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = usb4_path_segment_ctx->m_pathCreditsAllocated;
    }

    if (0 == usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight)
    {
        usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;
    }

    switch(type)
    {
        case USB4_portType_DOWNSTREAM_USB3_ADAPTER:
        case USB4_portType_UPSTREAM_USB3_ADAPTER:
        {
            /* Table 5.4, CM */
            usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 3;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 3;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 1;/* NA */
            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 1;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;/* NA */
            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;
            break;
        }
        case USB4_portType_DOWNSTREAM_PCIE_ADAPTER:
        case USB4_portType_UPSTREAM_PCIE_ADAPTER:
        {
            /* Table 5.1, CM */
            usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 3;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 3;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 1;/* NA */
            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 1;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;/* NA */
            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;
            break;
        }

        case USB4_portType_DP_IN:
             /* We don't check the egress adapter type because we assume 
             it will always be lane adapter */ 
            if (TRUE == usb4_path_segment_ctx->m_bAux)
            {

                usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = 0;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 2;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 0;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 1;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;
            }
            else 
            {
                usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = 0;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 1;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1; 
                usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 0;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 0;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0; 
                usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0; 
            }
            break;

        case USB4_portType_DP_OUT:
        {
            if (TRUE == usb4_path_segment_ctx->m_bAux)
            {
                //Need to write the same credits as were present on the read path.
                if (0 == usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated)
                {
                    usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = 1;
                }
                usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 2;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 1;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 1;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;
                usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;
            }
            else
            {
                // USB4_LOG_ERROR("Tried setup Video path from sink to source. Check path setup\n");
                Usb4Log(USB4_LOG_CM, Usb4PathSegmentFIllPathCsTriedSetupVideoPathFromSinkToSourceCheckPathSetup__Error, 0);
            }

            break;
        }
        case USB4_portType_HIA:
        {
            usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = 0;//TODO: Check value - Egress shared flow control - link credits are allocated...
            usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 4;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 0;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 1;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;
#if defined(USB4_CR_QCTDD06588513_HIA_SHARED_BUFFERS_VALIDATION)
            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 0;
            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 1;
#endif /* USB4_CR_QCTDD06588513_HIA_SHARED_BUFFERS_VALIDATION */
            break;
        }
        case USB4_portType_LANE0:
        {
            USB4_portType dsttype = Usb4PortGetPortType(usb4_path_segment_ctx->m_dstPort);
            switch(dsttype)
            {
                case USB4_portType_DOWNSTREAM_USB3_ADAPTER:
                case USB4_portType_UPSTREAM_USB3_ADAPTER:
                {
                    /* Table 5.4, CM */
                    usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = usb4_path_segment_ctx->m_pathCreditsAllocated;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 3;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 1;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 0;/* NA */
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;/* NA */
                    break;
                }
                case USB4_portType_DOWNSTREAM_PCIE_ADAPTER:
                case USB4_portType_UPSTREAM_PCIE_ADAPTER:
                {
                    /* Table 5.1, CM */
                    usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = usb4_path_segment_ctx->m_pathCreditsAllocated;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 3;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 1;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 0;/* NA */
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;/* NA */
                    break;
                }

                case USB4_portType_DP_IN:
                    /* DP Out to DP In Aux path */
                    usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = 1;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 2;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 1;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 0;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;                  
                    break;
                
                case USB4_portType_DP_OUT:
                { 
                    if (TRUE == usb4_path_segment_ctx->m_bAux)
                    {
                        usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = 1;
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 2;
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 1;
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 1;
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;
                    }
                    else
                    {
                        /* Intel Hub HACK */
                        //USB4_ASSERT(usb4_path_segment_ctx->m_pathCreditsAllocated == 0x38)
                        usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = usb4_path_segment_ctx->m_pathCreditsAllocated;
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 1;
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;  
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 0; 
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 0; 
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0; 
                        usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0; 
                    }
                    break;
                }

                case USB4_portType_HIA:
                {
                    usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = usb4_path_segment_ctx->m_pathCreditsAllocated;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 4;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 1;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 0;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;
#if defined(USB4_CR_QCTDD06588513_HIA_SHARED_BUFFERS_VALIDATION)
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 0;
                    usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 1;
#endif /* USB4_CR_QCTDD06588513_HIA_SHARED_BUFFERS_VALIDATION */
                    break;
                } 
                case USB4_portType_LANE0:
                {
                    switch (usb4_path_segment_ctx->m_pathType)
                    {
                        case USB4_pathType_DP_MAIN:
                            usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = usb4_path_segment_ctx->m_pathCreditsAllocated;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 1;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 0;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 0;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;
                            break;
                        case USB4_pathType_DP_IN_AUX:
                            usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = usb4_path_segment_ctx->m_pathCreditsAllocated;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 2;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 1;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 0;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;
                            break;
                        case USB4_pathType_DP_OUT_AUX:
                            usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = usb4_path_segment_ctx->m_pathCreditsAllocated;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 2;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 1;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 1;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 0;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;
                            break;
                        case USB4_pathType_HIA_IN:
                        case USB4_pathType_HIA_OUT:
                            usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = usb4_path_segment_ctx->m_pathCreditsAllocated;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.Priority = 4;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.Weight = 1;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl = 0;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressFlowControl = 0;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable = 1;
                            usb4_path_segment_ctx->pathCs.PATH_CS_1.EgressSharedBufferingEnable = 0;
                            break;
                        default:
                            USB4_ERROR_STACK_MSG(-1, "Failed to fill in path parameters Lane2Lane");
                            goto ErrorHandling;
                    }
                    break;
                }
                default:
                    USB4_ERROR_STACK_MSG(-1, "Failed to fill in path parameters");
                    goto ErrorHandling;
            }
            break;
        }
        default:
            USB4_ERROR_STACK_MSG(-1, "Failed to fill in path parameters");
            goto ErrorHandling;
    }

    /* If ingress flow control is enabled we need to assign credits */
    if ((0 != usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressFlowControl) &&
       (0 == usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated))
       {
           usb4_path_segment_ctx->pathCs.PATH_CS_0.PathCreditsAllocated = 1;
       }

    return 0;

ErrorHandling:
    return -1;
}

int Usb4PathSegmentWriteSegmentToRouter(usb4_path_segment_ctx_t* usb4_path_segment_ctx)
{
    if (0 != Usb4PortReadSegment(usb4_path_segment_ctx->m_srcPort, usb4_path_segment_ctx->m_ingressHopID, &usb4_path_segment_ctx->pathCs))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    if (usb4_path_segment_ctx->pathCs.PATH_CS_0.Valid)
    {
        if ((usb4_path_segment_ctx->m_egressHopID == usb4_path_segment_ctx->pathCs.PATH_CS_0.OutputHopID)&&
            (usb4_path_segment_ctx->m_dstPort->m_Number == usb4_path_segment_ctx->pathCs.PATH_CS_0.OutputAdapter))
        {
            usb4_pathN_cs path_new;
            path_new = usb4_path_segment_ctx->pathCs;
            USB4_ASSERT(0 == Usb4PathSegmentFIllPathCs(usb4_path_segment_ctx));
            if (0 == memcmp((UINT8*)(&path_new),
                    (UINT8*)(&usb4_path_segment_ctx->pathCs),
                    sizeof(usb4_pathN_cs)))
            {
                return 0;
            }
            // USB4_LOG_WARNING("Active path undergoes a change of parameters\n");
            Usb4Log(USB4_LOG_CM, Usb4PathSegmentWriteSegmentToRouterActivePathUndergoesAChangeOfParameters__Warn, 0);
        }
        else
        {
            // USB4_LOG_WARNING("Active path undergoes a change of destination\n");
            Usb4Log(USB4_LOG_CM, Usb4PathSegmentWriteSegmentToRouterActivePathUndergoesAChangeOfDestination__Warn, 0);
        }

        /* Will do something on adapter ports only. Exit with success on Lane and HIA ports */
        if (0 != Usb4PortEnableSegment(usb4_path_segment_ctx->m_srcPort, FALSE))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }

        if (0 != Usb4PortInvalidateSegment(usb4_path_segment_ctx->m_srcPort, usb4_path_segment_ctx->m_ingressHopID))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }

    }

    USB4_ASSERT(0 == Usb4PathSegmentFIllPathCs(usb4_path_segment_ctx));

    /* Apply override as needed */
    if (usb4_path_segment_ctx->m_pathCsParamsOverride.bValid)
    {
        if (Usb4PortGetPortType(usb4_path_segment_ctx->m_srcPort) == usb4_path_segment_ctx->m_pathCsParamsOverride.portType)
        {
            usb4_path_segment_ctx->pathCs = usb4_path_segment_ctx->m_pathCsParamsOverride.pathCs;
            if (usb4_path_segment_ctx->m_ingressHopID > 0)
            {
                usb4_path_segment_ctx->m_ingressHopID = usb4_path_segment_ctx->m_pathCsParamsOverride.HopID;
            }
        }
    }

    /* Need to update link credits prior to enabling any path with shared flow control.
     * Will not do anything if current value equals new value */
    if (usb4_path_segment_ctx->pathCs.PATH_CS_1.IngressSharedBufferingEnable)
    {
        if (0 != Usb4PortUpdateLinkCreditsAllocated(usb4_path_segment_ctx->m_srcPort, usb4_path_segment_ctx->m_linkCreditsAllocated))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }

    if (0 != Usb4PortWriteSegment(usb4_path_segment_ctx->m_srcPort, usb4_path_segment_ctx->m_ingressHopID, &usb4_path_segment_ctx->pathCs))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    return 0;
ErrorHandling:
    return -1;
}

int Usb4PathSegmentInvalidateSegment(usb4_path_segment_ctx_t* usb4_path_segment_ctx)
{

    USB4_ASSERT(0 == Usb4RouterSetRoute(&usb4_path_segment_ctx->m_pRouters[usb4_path_segment_ctx->m_routerIndex]));
    USB4_ASSERT(NULL != usb4_path_segment_ctx->m_srcPort);
    USB4_ASSERT(0 == Usb4PortInvalidateSegment(usb4_path_segment_ctx->m_srcPort, usb4_path_segment_ctx->m_ingressHopID));

    // USB4_LOG_INFO("ClearSegment: Adapter %u has %u total buffers\n", usb4_path_segment_ctx->m_srcPort->m_Number, Usb4PortGetFreeBuffers(usb4_path_segment_ctx->m_srcPort));
    Usb4Log2(USB4_LOG_CM, Usb4PathSegmentInvalidateSegmentClearSegmentAdapterHasTotalBuffers__Info, 0, 
        usb4_path_segment_ctx->m_srcPort->m_Number, Usb4PortGetFreeBuffers(usb4_path_segment_ctx->m_srcPort));

    return 0;
}

int Usb4PathSegmentIdentifySegmentActors(usb4_path_segment_ctx_t* usb4_path_segment_ctx)
{
    usb4_router_ctx_t* router;

    router = &usb4_path_segment_ctx->m_pRouters[usb4_path_segment_ctx->m_routerIndex];

    if (router->m_topologyID) /* Device router */
    {
        /* Lowest numbers are upstream */
        //For TBT3 Compatibility, use router CS to identify current upstream adapter
        usb4_path_segment_ctx->m_usb4UP = Usb4RouterGetAdapterPortByNumber(router, router->m_cs.ROUTER_CS_1.upstreamAdapter);
        USB4_ASSERT(NULL != usb4_path_segment_ctx->m_usb4UP);
    }

    if (0 != usb4_path_segment_ctx->m_usb4DowstreamPortNumber)
    {
        usb4_path_segment_ctx->m_usb4DN = Usb4RouterGetAdapterPortByNumber(router, usb4_path_segment_ctx->m_usb4DowstreamPortNumber);
        USB4_ASSERT(NULL != usb4_path_segment_ctx->m_usb4DN);
        USB4_ASSERT_MSG(USB4_portType_LANE0 == Usb4PortGetPortType(usb4_path_segment_ctx->m_usb4DN),
                        "USB4 DN Port has a wrong type");

        USB4_ASSERT(0==Usb4PathSegmentFindAdapterDnPort(usb4_path_segment_ctx));
        if (NULL != usb4_path_segment_ctx->m_adapterPort)
        {
            /* This is a downstream segment, so clear m_usb4UP to avoid confusion */
            usb4_path_segment_ctx->m_usb4UP = NULL;
        }
    }
    else
    {
        /* adapter port is an upstream port */
        if (USB4_portType_DP_OUT == usb4_path_segment_ctx->m_adapterPortType)
        {
            /* Use the adapter that has a plugged event */
            /* TODO: Understand what happens when multiple ports were plugged */
            USB4_ASSERT_MSG(0 != router->m_displayPortAdapter, "Don't have a display out adapter in a plugged state");
            usb4_path_segment_ctx->m_adapterPort = Usb4RouterGetAdapterPortByNumber(router, router->m_displayPortAdapter);
        }
        else
        {
            usb4_path_segment_ctx->m_adapterPort = Usb4RouterGetAdapterPortByType(router, usb4_path_segment_ctx->m_adapterPortType, 0);
        }
    }

    if (NULL == usb4_path_segment_ctx->m_adapterPort)
    {
        /* Need to connect USB4 ports to each other */
        USB4_ASSERT(NULL != usb4_path_segment_ctx->m_usb4UP);
        USB4_ASSERT(NULL != usb4_path_segment_ctx->m_usb4DN);

        if(usb4_path_segment_ctx->m_bDirectionOut)
        {
            usb4_path_segment_ctx->m_srcPort = usb4_path_segment_ctx->m_usb4UP;
            usb4_path_segment_ctx->m_dstPort = usb4_path_segment_ctx->m_usb4DN;
        }
        else
        {
            usb4_path_segment_ctx->m_srcPort = usb4_path_segment_ctx->m_usb4DN;
            usb4_path_segment_ctx->m_dstPort = usb4_path_segment_ctx->m_usb4UP;
        }
    }
    else
    {
        if (NULL != usb4_path_segment_ctx->m_usb4UP)
        {
            if (usb4_path_segment_ctx->m_bDirectionOut)
            {
                usb4_path_segment_ctx->m_srcPort = usb4_path_segment_ctx->m_usb4UP;
                usb4_path_segment_ctx->m_dstPort = usb4_path_segment_ctx->m_adapterPort;
            }
            else
            {
                usb4_path_segment_ctx->m_srcPort = usb4_path_segment_ctx->m_adapterPort;
                usb4_path_segment_ctx->m_dstPort = usb4_path_segment_ctx->m_usb4UP;
            }

        }
        else if (NULL != usb4_path_segment_ctx->m_usb4DN)
        {
            if (usb4_path_segment_ctx->m_bDirectionOut)
            {
                usb4_path_segment_ctx->m_srcPort = usb4_path_segment_ctx->m_adapterPort;
                usb4_path_segment_ctx->m_dstPort = usb4_path_segment_ctx->m_usb4DN;
            }
            else
            {
                usb4_path_segment_ctx->m_srcPort = usb4_path_segment_ctx->m_usb4DN;
                usb4_path_segment_ctx->m_dstPort = usb4_path_segment_ctx->m_adapterPort;
            }

        }
        else
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }

    return 0;
ErrorHandling:
    return -1;
}

int Usb4PathSegmentFindAdapterDnPort(usb4_path_segment_ctx_t* usb4_path_segment_ctx)
{
    usb4_router_ctx_t* router;
    UINT32 adapterDnNumber = 0;
    UINT32 usb4UpNumber = 0;
    UINT32 i, usb4DnCount = 0;

    router = &usb4_path_segment_ctx->m_pRouters[usb4_path_segment_ctx->m_routerIndex];

    if (USB4_portType_NOT_VALID == usb4_path_segment_ctx->m_adapterPortType)
    {
        return 0;
    }

    if (NULL != usb4_path_segment_ctx->m_usb4UP)
    {
        usb4UpNumber = usb4_path_segment_ctx->m_usb4UP->m_Number;
    }

    /* Count USB4 DN ports untill and usb4_path_segment_ctx->m_usb4DowstreamPortNumber */
    for (i = 1; i <= usb4_path_segment_ctx->m_usb4DowstreamPortNumber; i++)
    {
        if (USB4_portType_LANE0 == Usb4RouterGetPortType(router, i))
        {
            if (i != usb4UpNumber)
            {
                usb4DnCount++;
            }
        }
    }

    /* Get appropriate adapter DN port (each adapter DN port corresponds to specific USB4 DN port*/
    for(i=0; i < usb4DnCount; i++)
    {
        usb4_path_segment_ctx->m_adapterPort = Usb4RouterGetAdapterPortByType(router, usb4_path_segment_ctx->m_adapterPortType, adapterDnNumber);
        if (NULL != usb4_path_segment_ctx->m_adapterPort)
        {
            adapterDnNumber = usb4_path_segment_ctx->m_adapterPort->m_Number + 1;
        }
        else
        {
            break;
        }
    }

    /* Sanity check - new validation, may need to debug on chained topologies */
    USB4_ASSERT(NULL != usb4_path_segment_ctx->m_adapterPort);

    return 0;
}

int Usb4PathSegmentConfigureSegmentLane2Lane(usb4_path_segment_ctx_t* usb4_path_segment_ctx)
{
    USB4_ASSERT(0 != usb4_path_segment_ctx->m_egressHopID); /* Assigned at a higher level */
    USB4_ASSERT(0 == Usb4PortGetFreeHopID(usb4_path_segment_ctx->m_srcPort, &usb4_path_segment_ctx->m_ingressHopID));

    return 0;
}

int Usb4PathSegmentConfigureSegmentAdapterUP(usb4_path_segment_ctx_t* usb4_path_segment_ctx)
{
    if(usb4_path_segment_ctx->m_bDirectionOut)
    {
        USB4_ASSERT(0 == Usb4PortGetAdapterHopID(usb4_path_segment_ctx->m_dstPort, &usb4_path_segment_ctx->m_egressHopID, usb4_path_segment_ctx->m_bAux));
        USB4_ASSERT(0 == Usb4PortGetFreeHopID(usb4_path_segment_ctx->m_srcPort, &usb4_path_segment_ctx->m_ingressHopID));
    }
    else
    {
        USB4_ASSERT(0 != usb4_path_segment_ctx->m_egressHopID); /* Assigned at a higher level */
        USB4_ASSERT(0 == Usb4PortGetAdapterHopID(usb4_path_segment_ctx->m_srcPort, &usb4_path_segment_ctx->m_ingressHopID, usb4_path_segment_ctx->m_bAux));
    }

    return 0;
}


int Usb4PathSegmentConfigureSegmentAdapterDN(usb4_path_segment_ctx_t* usb4_path_segment_ctx)
{
    if(usb4_path_segment_ctx->m_bDirectionOut)
    {
        USB4_ASSERT(0 == Usb4PortGetAdapterHopID(usb4_path_segment_ctx->m_adapterPort, &usb4_path_segment_ctx->m_ingressHopID, usb4_path_segment_ctx->m_bAux));
        USB4_ASSERT(0 != usb4_path_segment_ctx->m_egressHopID); /* Assigned at a higher level */
    }
    else
    {
        USB4_ASSERT(0 == Usb4PortGetAdapterHopID(usb4_path_segment_ctx->m_adapterPort, &usb4_path_segment_ctx->m_egressHopID, usb4_path_segment_ctx->m_bAux));
        USB4_ASSERT(0 == Usb4PortGetFreeHopID(usb4_path_segment_ctx->m_srcPort, &usb4_path_segment_ctx->m_ingressHopID));
    }

    return 0;
}

int Usb4PathSegmentConfigureSegment(usb4_path_segment_ctx_t* usb4_path_segment_ctx, USB4_pathType pathType)
{
    usb4_router_ctx_t* router;

    usb4_path_segment_ctx->m_pathType = pathType;

    router = &usb4_path_segment_ctx->m_pRouters[usb4_path_segment_ctx->m_routerIndex];
    USB4_ASSERT(0 == Usb4RouterSetRoute(router));

    if (NULL == usb4_path_segment_ctx->m_adapterPort)
    {
        /* Need to connect USB4 ports to each other */
        USB4_ASSERT(NULL != usb4_path_segment_ctx->m_usb4UP);
        USB4_ASSERT(NULL != usb4_path_segment_ctx->m_usb4DN);

        /**/
        if (0 != Usb4PathSegmentConfigureSegmentLane2Lane(usb4_path_segment_ctx))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }
    else
    {
        if (NULL != usb4_path_segment_ctx->m_usb4UP)
        {
            if (0 != Usb4PathSegmentConfigureSegmentAdapterUP(usb4_path_segment_ctx))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
        }
        else if (NULL != usb4_path_segment_ctx->m_usb4DN)
        {
            if (0 != Usb4PathSegmentConfigureSegmentAdapterDN(usb4_path_segment_ctx))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
        }
        else
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }

    if (0 != Usb4PathSegmentWriteSegmentToRouter(usb4_path_segment_ctx))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }
    return 0;
ErrorHandling:
    return -1;
}

int Usb4PathSegmentEnableSegment(usb4_path_segment_ctx_t* usb4_path_segment_ctx, BOOLEAN bEnable)
{
    if (NULL != usb4_path_segment_ctx->m_adapterPort)
    {
        return Usb4PortEnableSegment(usb4_path_segment_ctx->m_adapterPort, bEnable);
    }
    return 0;
}

int Usb4PathSegmentCalculateSegmentCredits(usb4_path_segment_ctx_t* usb4_path_segment_ctx, UINT32 proposedCredits, UINT32 proposedLinkCredits)
{
    usb4_router_ctx_t* router;

    router = &usb4_path_segment_ctx->m_pRouters[usb4_path_segment_ctx->m_routerIndex];
    if (usb4_path_segment_ctx->m_srcPort == usb4_path_segment_ctx->m_adapterPort)
    {
        usb4_path_segment_ctx->m_pathCreditsAllocated = 0;
        usb4_path_segment_ctx->m_linkCreditsAllocated = proposedLinkCredits;
        return 0;
    }
    usb4_path_segment_ctx->m_pathCreditsAllocated = proposedCredits;
    usb4_path_segment_ctx->m_linkCreditsAllocated = proposedLinkCredits;

    if (router->m_bufferAllocationRequestSuceeded)
    {
        switch(usb4_path_segment_ctx->m_adapterPortType)
        {
            case USB4_portType_CONTROL:
            case USB4_portType_HIA:
                if ((router->m_baMaxHI > 0) && (usb4_path_segment_ctx->m_pathCreditsAllocated > router->m_baMaxHI))
                {
                    // USB4_LOG_WARNING("Router allocation: Limiting path credits from %u to %u, router %u\n",
                    //                     usb4_path_segment_ctx->m_pathCreditsAllocated, router->m_baMaxHI, usb4_path_segment_ctx->m_routerIndex);
                    Usb4Log3(USB4_LOG_CM, Usb4PathSegmentCalculateSegmentCreditsRouterAllocationLimitingPathCredits__Params__From_To_router, 0,
                                        usb4_path_segment_ctx->m_pathCreditsAllocated, router->m_baMaxHI, usb4_path_segment_ctx->m_routerIndex);

                    usb4_path_segment_ctx->m_pathCreditsAllocated = router->m_baMaxHI;
                }
                break;
            case USB4_portType_UPSTREAM_PCIE_ADAPTER:
            case USB4_portType_DOWNSTREAM_PCIE_ADAPTER:
                if ((router->m_baMaxPCIe > 0) && (usb4_path_segment_ctx->m_pathCreditsAllocated > router->m_baMaxPCIe))
                {
                    // USB4_LOG_WARNING("Router allocation: Limiting path credits from %u to %u, router %u\n",
                    //                   usb4_path_segment_ctx->m_pathCreditsAllocated, router->m_baMaxPCIe, usb4_path_segment_ctx->m_routerIndex);
                    Usb4Log3(USB4_LOG_CM, Usb4PathSegmentCalculateSegmentCreditsRouterAllocationLimitingPathCredits__Params__From_To_router, 0,
                                      usb4_path_segment_ctx->m_pathCreditsAllocated, router->m_baMaxPCIe, usb4_path_segment_ctx->m_routerIndex);

                    usb4_path_segment_ctx->m_pathCreditsAllocated = router->m_baMaxPCIe;
                }
                break;
            case USB4_portType_DP_IN:
            case USB4_portType_DP_OUT:
                if (usb4_path_segment_ctx->m_bAux)
                {
                    if ((router->m_baMinDPaux > 0) && (usb4_path_segment_ctx->m_pathCreditsAllocated > router->m_baMinDPaux))
                    {
                        // USB4_LOG_WARNING("Router allocation: Limiting path credits from %u to %u, router %u\n",
                        //                  usb4_path_segment_ctx->m_pathCreditsAllocated, router->m_baMinDPaux, usb4_path_segment_ctx->m_routerIndex);
                        Usb4Log3(USB4_LOG_CM, Usb4PathSegmentCalculateSegmentCreditsRouterAllocationLimitingPathCredits__Params__From_To_router, 0,
                                          usb4_path_segment_ctx->m_pathCreditsAllocated, router->m_baMinDPaux, usb4_path_segment_ctx->m_routerIndex);

                        usb4_path_segment_ctx->m_pathCreditsAllocated = router->m_baMinDPaux;
                    }
                }
                else
                {
                    if ((router->m_baMinDPmain > 0) && (usb4_path_segment_ctx->m_pathCreditsAllocated > router->m_baMinDPmain))
                    {
                        // USB4_LOG_WARNING("Router allocation: Limiting path credits from %u to %u, router %u\n",
                        //                   usb4_path_segment_ctx->m_pathCreditsAllocated, router->m_baMinDPaux, usb4_path_segment_ctx->m_routerIndex);
                        Usb4Log3(USB4_LOG_CM, Usb4PathSegmentCalculateSegmentCreditsRouterAllocationLimitingPathCredits__Params__From_To_router, 0,
                                          usb4_path_segment_ctx->m_pathCreditsAllocated, router->m_baMinDPaux, usb4_path_segment_ctx->m_routerIndex);

                        usb4_path_segment_ctx->m_pathCreditsAllocated = router->m_baMinDPmain;
                    }
                }
                break;
            case USB4_portType_UPSTREAM_USB3_ADAPTER:
            case USB4_portType_DOWNSTREAM_USB3_ADAPTER:
                if (router->m_baMaxUSB3 > 0)
                {
                    usb4_path_segment_ctx->m_pathCreditsAllocated =
                            MIN(usb4_path_segment_ctx->m_pathCreditsAllocated, router->m_baMaxUSB3);
                }
                break;
            default:
                break;
        }
    }

    /* Limit expectation by what is actually left on a port */
    if (Usb4PortGetFreeBuffers(usb4_path_segment_ctx->m_srcPort) < usb4_path_segment_ctx->m_pathCreditsAllocated)
    {
        // USB4_LOG_WARNING("CalculateSegmentCreditsPort: Limiting path credits from %u to %u, router %u\n",
        //        usb4_path_segment_ctx->m_pathCreditsAllocated, Usb4PortGetFreeBuffers(usb4_path_segment_ctx->m_srcPort), usb4_path_segment_ctx->m_routerIndex);
        Usb4Log3(USB4_LOG_CM, Usb4PathSegmentCalculateSegmentCreditsCalculateSegmentCreditsPortLimitingPathCredits__Params__From_To_router, 0,
                usb4_path_segment_ctx->m_pathCreditsAllocated, Usb4PortGetFreeBuffers(usb4_path_segment_ctx->m_srcPort), usb4_path_segment_ctx->m_routerIndex);
        usb4_path_segment_ctx->m_pathCreditsAllocated = Usb4PortGetFreeBuffers(usb4_path_segment_ctx->m_srcPort);
        // USB4_LOG_INFO("CalculateSegmentCredits: Router %u, m_pathCreditsAllocated %u; Adapter %u has %u total buffers\n",
        //         usb4_path_segment_ctx->m_routerIndex, usb4_path_segment_ctx->m_pathCreditsAllocated, usb4_path_segment_ctx->m_srcPort->m_Number, Usb4PortGetFreeBuffers(usb4_path_segment_ctx->m_srcPort));
        Usb4Log2(USB4_LOG_CM, Usb4PathSegmentCalculateSegmentCreditsCalculateSegmentCredits__Params__Router_pathCreditsAllocated, 0,
           usb4_path_segment_ctx->m_routerIndex, usb4_path_segment_ctx->m_pathCreditsAllocated);
        Usb4Log2(USB4_LOG_CM, Usb4PathSegmentCalculateSegmentCreditsCalculateSegmentCredits__Params__Adapter_hasTotalBuffers, 0,
           usb4_path_segment_ctx->m_srcPort->m_Number, Usb4PortGetFreeBuffers(usb4_path_segment_ctx->m_srcPort));
    }
    return 0;
}
