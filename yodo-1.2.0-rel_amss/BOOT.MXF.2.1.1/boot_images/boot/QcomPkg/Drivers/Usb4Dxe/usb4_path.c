/**---------------------------------------------------------------------------
 *   @file        usb4_path.c
 *
 *   @brief       Implementation of Path methods
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
#include "usb4_path.h"
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

int Usb4PathInit(usb4_path_ctx_t* usb4_path_ctx, usb4_router_ctx_t* pRouters)
{
    UINT32 i;
    if (NULL == pRouters)
    {
        USB4_ERROR_STACK_MSG(-1, "Pointer to routers can't be null");
        return -1;
    }

    usb4_path_ctx->m_pRouters = NULL;
    // m_pathSegments();
    usb4_path_ctx->m_bDirectionOut = FALSE;
    usb4_path_ctx->m_bAux = FALSE;
    usb4_path_ctx->m_bPathEnabled = 0;
    usb4_path_ctx->m_Type = USB4_pathType_NOT_VALID;
    usb4_path_ctx->m_leafTopologyID = 0;
    usb4_path_ctx->m_interdomainAdapterNumber = 0;
    usb4_path_ctx->m_pathLength = 0;
    usb4_path_ctx->m_InterdomainPathCounter = 0;

    usb4_path_ctx->m_pRouters = pRouters;
    for (i = 0; i < USB4_MAX_PATH_LENGTH; i++)
    {
       USB4_ASSERT(0 == Usb4PathSegmentInit(&usb4_path_ctx->m_pathSegments[i], usb4_path_ctx->m_pRouters));
    }

    usb4_path_ctx->m_Type = USB4_pathType_NOT_VALID;
    usb4_path_ctx->m_leafTopologyID = 0;
    usb4_path_ctx->m_interdomainAdapterNumber = 0;
    usb4_path_ctx->m_pathLength = 0;
    usb4_path_ctx->m_bPathEnabled = 0;

    return 0;
}

int Usb4PathFindRouterByTopology(usb4_path_ctx_t* usb4_path_ctx, UINT64 router_topologyID, UINT32* index)
{
    UINT32 i;
    for (i = 0; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        if (router_topologyID == usb4_path_ctx->m_pRouters[i].m_topologyID)
        {
            *index = i;
            return 0;
        }
    }
    return -1;
}

int Usb4PathFindpathSegmentByTopology(usb4_path_ctx_t* usb4_path_ctx, UINT64 router_topologyID, UINT32* pathSegmentIndex)
{
    UINT32 i;
    for (i = 0; i < usb4_path_ctx->m_pathLength; i++)
    {
        if (router_topologyID == usb4_path_ctx->m_pRouters[usb4_path_ctx->m_pathSegments[i].m_routerIndex].m_topologyID)
        {
            *pathSegmentIndex = i;
            return 0;
        }
    }
    return -1;
}

int Usb4PathConstruct(usb4_path_ctx_t* usb4_path_ctx, USB4_pathConstructionParamsType* pPathConstructionParams)
{
    USB4_ASSERT(0 != pPathConstructionParams->topologyID);
    usb4_path_ctx->m_Type = pPathConstructionParams->pathType;
    usb4_path_ctx->m_InterdomainPathCounter = pPathConstructionParams->interdomainPathCounter;

    switch (usb4_path_ctx->m_Type)
    {
        case USB4_pathType_HIA_OUT:
        case USB4_pathType_HIA_IN:
        case USB4_pathType_H2H_PCIE_IN:
        case USB4_pathType_H2H_PCIE_OUT:
        case USB4_pathType_H2H_DP_IN_AUX:
        case USB4_pathType_H2H_DP_OUT_AUX:
        case USB4_pathType_H2H_USB3_IN:
        case USB4_pathType_H2H_USB3_OUT:
            USB4_ASSERT(0 == usb4_get_router_and_port(pPathConstructionParams->topologyID, &usb4_path_ctx->m_leafTopologyID, &usb4_path_ctx->m_interdomainAdapterNumber));
            break;
        default:
            usb4_path_ctx->m_leafTopologyID = pPathConstructionParams->topologyID;
            break;
    }

    /* Configure the path as upstream or downstream */
    USB4_ASSERT(0 == Usb4PathAssignDirection(usb4_path_ctx));

    /* Identify the segments endpoints ( can be port or adapter ) that create the path */
    USB4_ASSERT(0 == Usb4PathIdentifyRouters(usb4_path_ctx));

    /* Calculate how many credits to grant for each path's segment */
    USB4_ASSERT(0 == Usb4PathCalculateBuffers(usb4_path_ctx));

    /* Limit the number of calculated credits by number of buffers + ???*/
    USB4_ASSERT(0 == Usb4PathOverrideSegmentParams(usb4_path_ctx, pPathConstructionParams->pPathParamsOverride));

    USB4_ASSERT(0 == Usb4PathConfigureSegments(usb4_path_ctx, pPathConstructionParams->interdomainEgressHopID));

    return 0;
}

int Usb4PathEnableSegments(usb4_path_ctx_t* usb4_path_ctx, BOOLEAN bEnable)
{
    UINT32 i, pathSegmentIndex;
    if (bEnable == usb4_path_ctx->m_bPathEnabled)
    {
        return 0;
    }

    /* It is recommended to enable paths from destination to source */
    /* It is recommended to disable paths from source to destination */
    /* Out Enable Direction */
    /* F   F      Start from Leaf */
    /* F   T      Start from Host */
    /* T   F      Start from Host */
    /* T   T      Start from Leaf */

    for (pathSegmentIndex = 0; pathSegmentIndex < usb4_path_ctx->m_pathLength; pathSegmentIndex++)
    {
        if (usb4_path_ctx->m_bDirectionOut != bEnable)
        {
            i = usb4_path_ctx->m_pathLength - pathSegmentIndex - 1; /* Start from Host */
        }
        else
        {
            i = pathSegmentIndex; /* Start from Leaf */
        }

        /* In case router was removed by unplug */
        if (FALSE == Usb4RouterIsEnumerated(&usb4_path_ctx->m_pRouters[usb4_path_ctx->m_pathSegments[i].m_routerIndex]))
        {
            continue;
        }

        if (0 != Usb4PathSegmentEnableSegment(&usb4_path_ctx->m_pathSegments[i], bEnable))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }


    usb4_path_ctx->m_bPathEnabled = bEnable;
    return 0;
ErrorHandling:
    return -1;
}

int Usb4PathClear(usb4_path_ctx_t* usb4_path_ctx)
{
    UINT32 i;
    usb4_path_ctx->m_Type = USB4_pathType_NOT_VALID;
    usb4_path_ctx->m_leafTopologyID = 0;
    usb4_path_ctx->m_interdomainAdapterNumber = 0;
    for (i = 0; i < usb4_path_ctx->m_pathLength; i++)
    {
       USB4_ASSERT(0 == Usb4PathSegmentInit(&usb4_path_ctx->m_pathSegments[i], usb4_path_ctx->m_pRouters));
    }
    usb4_path_ctx->m_pathLength = 0;
    usb4_path_ctx->m_bPathEnabled = 0;
    return 0;
}

int Usb4PathAssignDirection(usb4_path_ctx_t* usb4_path_ctx)
{
    UINT32 i;
    switch (usb4_path_ctx->m_Type)
    {
        case USB4_pathType_PCIE_OUT:
        case USB4_pathType_USB3_OUT:
        case USB4_pathType_HIA_OUT:
        case USB4_pathType_DP_MAIN:
        case USB4_pathType_DP_IN_AUX:
        case USB4_pathType_H2H_PCIE_OUT:
        case USB4_pathType_H2H_DP_IN_AUX:
        case USB4_pathType_H2H_USB3_OUT:
            usb4_path_ctx->m_bDirectionOut = TRUE;
            break;
        default:
            break;
    }

    if ((USB4_pathType_DP_IN_AUX == usb4_path_ctx->m_Type) ||
        (USB4_pathType_DP_OUT_AUX == usb4_path_ctx->m_Type)||
        (USB4_pathType_H2H_DP_IN_AUX == usb4_path_ctx->m_Type) ||
        (USB4_pathType_H2H_DP_OUT_AUX == usb4_path_ctx->m_Type))
    {
        usb4_path_ctx->m_bAux = TRUE;
    }

    for (i = 0; i < USB4_MAX_PATH_LENGTH; i++)
    {
        usb4_path_ctx->m_pathSegments[i].m_bDirectionOut = usb4_path_ctx->m_bDirectionOut;
        usb4_path_ctx->m_pathSegments[i].m_bAux = usb4_path_ctx->m_bAux;
    }

    return 0;
}


USB4_portType Usb4PathIdentifySegmentAdapterType(usb4_path_ctx_t* usb4_path_ctx, UINT64 topologyID, BOOLEAN bIsLeaf)
{
    switch (usb4_path_ctx->m_Type)
    {
        case USB4_pathType_PCIE_OUT:
        case USB4_pathType_PCIE_IN:
            if (bIsLeaf) /* This is a leaf path router */
            {
                return USB4_portType_UPSTREAM_PCIE_ADAPTER;
            }
            else
            {
                return USB4_portType_DOWNSTREAM_PCIE_ADAPTER;
            }
        case USB4_pathType_H2H_PCIE_IN:
        case USB4_pathType_H2H_PCIE_OUT:
            return USB4_portType_DOWNSTREAM_PCIE_ADAPTER;
        case USB4_pathType_USB3_OUT:
        case USB4_pathType_USB3_IN:
            if (bIsLeaf) /* This is a leaf path router */
            {
                return USB4_portType_UPSTREAM_USB3_ADAPTER;
            }
            else
            {
                return USB4_portType_DOWNSTREAM_USB3_ADAPTER;
            }
        case USB4_pathType_H2H_USB3_IN:
        case USB4_pathType_H2H_USB3_OUT:
            return USB4_portType_DOWNSTREAM_USB3_ADAPTER;
        case USB4_pathType_HIA_OUT:
        case USB4_pathType_HIA_IN:
            if (bIsLeaf)
            {
                return USB4_portType_HIA;
            }
            else
            {
                return USB4_portType_NOT_VALID;
            }
        case USB4_pathType_DP_MAIN:
        case USB4_pathType_DP_IN_AUX:
        case USB4_pathType_DP_OUT_AUX:
            if (0 == topologyID)
            {
                return USB4_portType_DP_IN;
            }
            else if (bIsLeaf)
            {
                return USB4_portType_DP_OUT;
            }
            else
            {
                return USB4_portType_NOT_VALID;
            }
        case USB4_pathType_H2H_DP_IN_AUX:
        case USB4_pathType_H2H_DP_OUT_AUX:
            if (0 == topologyID)
            {
                return USB4_portType_DP_IN;
            }
            else
            {
                return USB4_portType_NOT_VALID;
            }
        default:
            return USB4_portType_NOT_VALID;
    }
}

UINT32 Usb4PathGetUsb4DnPortNumber(usb4_path_ctx_t* usb4_path_ctx, UINT32 pathSegmentIndex)
{
    return usb4_path_ctx->m_pathSegments[pathSegmentIndex].m_usb4DowstreamPortNumber;
}

int Usb4PathIdentifyRouters(usb4_path_ctx_t* usb4_path_ctx)
{
    UINT32 i, port;
    UINT64 topologyID = usb4_path_ctx->m_leafTopologyID;
    USB4_ASSERT(0 == Usb4PathFindRouterByTopology(usb4_path_ctx, usb4_path_ctx->m_leafTopologyID, &usb4_path_ctx->m_pathSegments[0].m_routerIndex));

    switch (usb4_path_ctx->m_Type)
    {
        case USB4_pathType_HIA_OUT:
        case USB4_pathType_HIA_IN:
        case USB4_pathType_H2H_PCIE_IN:
        case USB4_pathType_H2H_PCIE_OUT:
        case USB4_pathType_H2H_DP_IN_AUX:
        case USB4_pathType_H2H_DP_OUT_AUX:
        case USB4_pathType_H2H_USB3_IN:
        case USB4_pathType_H2H_USB3_OUT:
            usb4_path_ctx->m_pathSegments[0].m_usb4DowstreamPortNumber = usb4_path_ctx->m_interdomainAdapterNumber;
            break;
        default:
            usb4_path_ctx->m_pathSegments[0].m_usb4DowstreamPortNumber = 0; /* This is a leaf router */
            break;
    }

    /* Assign the protocol adapter located in this router (PCIE USB3 DP, or none (not valid type)) */
    usb4_path_ctx->m_pathSegments[0].m_adapterPortType = Usb4PathIdentifySegmentAdapterType(usb4_path_ctx, topologyID, TRUE);
   
    /* Set pointers to the edges of the segment (port to port, port to adapter or adapter to port)*/
    USB4_ASSERT(0 == Usb4PathSegmentIdentifySegmentActors(&usb4_path_ctx->m_pathSegments[0]));
   
    i = 1;
    
    /* Go upstream on the path */
    while (topologyID && (i < USB4_MAX_PATH_LENGTH))
    {
        /* Get parent topologyID and downstream adapter number */
        USB4_ASSERT(0 == usb4_get_router_and_port(topologyID, &topologyID, &port));
        
        /**< Assign parent router topology
         to the same variable */
        USB4_ASSERT(0 == Usb4PathFindRouterByTopology(usb4_path_ctx, topologyID, &usb4_path_ctx->m_pathSegments[i].m_routerIndex));
        usb4_path_ctx->m_pathSegments[i].m_usb4DowstreamPortNumber = port;

        /* Assign the protocol adapter located in this router (PCIE USB3 DP, or none (not valid type)) */
        usb4_path_ctx->m_pathSegments[i].m_adapterPortType = Usb4PathIdentifySegmentAdapterType(usb4_path_ctx, topologyID, FALSE);

        /* Set source and destination adapters of the segment 
          (port to port, port to adapter or adapter to port)*/
        USB4_ASSERT(0 == Usb4PathSegmentIdentifySegmentActors(&usb4_path_ctx->m_pathSegments[i]));
        
        if(NULL != usb4_path_ctx->m_pathSegments[i].m_adapterPort) /* Path always terminates at adapter */
        {
            i++;
            break;
        }
        i++;
    }
    usb4_path_ctx->m_pathLength = i;
    USB4_ASSERT(i < USB4_MAX_PATH_LENGTH);
    return 0;
}

#define USB4_PATH_USE_CONSERVATIVE_ALLOCATION 1

int Usb4PathCalculateBuffers(usb4_path_ctx_t* usb4_path_ctx)
{
    UINT32 i, consumedBuffers = 0, sharedBuffers = 0;

    /* This is how much we would like to use for USB4 port;
     * Adapters themselves don't consume credits  */
    switch(usb4_path_ctx->m_Type)
    {
        case USB4_pathType_CONTROL:
            consumedBuffers = 2;
            break;
        case USB4_pathType_PCIE_IN:
        case USB4_pathType_PCIE_OUT:
        case USB4_pathType_H2H_PCIE_IN:
        case USB4_pathType_H2H_PCIE_OUT:
            /* Per USB4 Link:
                10Gbps: 16
                20Gbps: 24
                40Gbps: 32
            Request maximum */
#ifndef USB4_PATH_USE_CONSERVATIVE_ALLOCATION
            consumedBuffers = 32;
#else
            consumedBuffers  = 8;
#endif
            break;
        case USB4_pathType_DP_MAIN:
            consumedBuffers = 0x20;
            break;
        case USB4_pathType_DP_IN_AUX:
        case USB4_pathType_H2H_DP_IN_AUX:
            consumedBuffers = 1; //was 8?
            break;
        case USB4_pathType_DP_OUT_AUX:
        case USB4_pathType_H2H_DP_OUT_AUX:
            consumedBuffers = 1;
            break;
        case USB4_pathType_USB3_IN:
        case USB4_pathType_USB3_OUT:
        case USB4_pathType_H2H_USB3_IN:
        case USB4_pathType_H2H_USB3_OUT:
            /* Per USB4 Link:
            10Gbps: 16
            20Gbps: 24
            40Gbps: 32
            Request maximum */
#ifndef USB4_PATH_USE_CONSERVATIVE_ALLOCATION
            consumedBuffers = 32;
#else
            consumedBuffers  = 8;
#endif
            break;
        case USB4_pathType_HIA_IN:
        case USB4_pathType_HIA_OUT:
             sharedBuffers = 32;
            // consumedBuffers = m_sharedBuffers; // Same or lower value
            consumedBuffers = 8; //andreyb: In case a dedicated buffers are used, be conservative, to allow other paths establishment.
            break;
        default:
            consumedBuffers = 0;
            break;
    }

    /* Limit expectation by router HW configuration */
    for (i=0; i < usb4_path_ctx->m_pathLength; i++)
    {
        USB4_ASSERT(0 == Usb4PathSegmentCalculateSegmentCredits(&usb4_path_ctx->m_pathSegments[i], consumedBuffers, sharedBuffers));
    }

    return 0;
}

int Usb4PathOverrideSegmentParams(usb4_path_ctx_t* usb4_path_ctx, USB4_pathParamsOverrideType* pPathParamsOverride)
{
    UINT32 i;
    usb4_path_segment_ctx_t* pathSegment;

    if (NULL == pPathParamsOverride)
    {
        return 0;
    }

    for (i=0; i < usb4_path_ctx->m_pathLength; i++)
    {
        pathSegment = &usb4_path_ctx->m_pathSegments[i];

        /* Apply parameters override */
        if (pPathParamsOverride->bOverrideActive)
        {
            if (pPathParamsOverride->bRouterIndexValid)
            {
               if (pPathParamsOverride->routerIndex != pathSegment->m_routerIndex)
               {
                   continue;
               }
            }
            else
            {
                continue;
            }
        }

        if (pPathParamsOverride->bNumOfBuffersValid)
        {
            pathSegment->m_pathCreditsAllocated = pPathParamsOverride->numOfBuffers;
        }

        if (pPathParamsOverride->pathCsParams.bValid)
        {
            pathSegment->m_pathCsParamsOverride = pPathParamsOverride->pathCsParams;
        }
    }
    return 0;

}

int Usb4PathConfigureSegments(usb4_path_ctx_t* usb4_path_ctx, UINT32 interdomainEgressHopID)
{
    UINT32 i;
    if (usb4_path_ctx->m_bDirectionOut)
    {
        /* Perform allocation in the upstream routing table. So traverse from leaf to root. */
        for (i=0; i < usb4_path_ctx->m_pathLength; i++)
        {
            if (i > 0)
            {
                usb4_path_ctx->m_pathSegments[i].m_egressHopID = usb4_path_ctx->m_pathSegments[i-1].m_ingressHopID;
            }
            else
            {
                /* For an inter-domain path, use the same hop ID as was assigned for the IN path;
                 * Presume complete symmetry, and IN path constructed first */
                if (0 != interdomainEgressHopID)
                {
                    usb4_path_ctx->m_pathSegments[i].m_egressHopID = interdomainEgressHopID;
                }
                else
                {
                    usb4_path_ctx->m_pathSegments[i].m_egressHopID = 0; /* Should be overwritten at a lower level */
                }
            }

            if (0 != Usb4PathSegmentConfigureSegment(&usb4_path_ctx->m_pathSegments[i], usb4_path_ctx->m_Type))
            {
                USB4_ERROR_STACK(-1);
                return -1;
            }
        }
    }
    else
    {
        /* Perform allocation in the downstream routing table. So traverse from root to leaf. */
        for (i=0; i < usb4_path_ctx->m_pathLength; i++)
        {
            UINT32 k = usb4_path_ctx->m_pathLength-i-1;

            if (k < usb4_path_ctx->m_pathLength - 1)
            {
                usb4_path_ctx->m_pathSegments[k].m_egressHopID = usb4_path_ctx->m_pathSegments[k + 1].m_ingressHopID;
            }

            if (0 != Usb4PathSegmentConfigureSegment(&usb4_path_ctx->m_pathSegments[k], usb4_path_ctx->m_Type))
            {
                USB4_ERROR_STACK(-1);
                return -1;
            }
        }
    }

    return 0;
}

int Usb4PathInvalidateSegments(usb4_path_ctx_t* usb4_path_ctx)
{
    UINT32 pathSegmentIndex;
    /* It is recommended to clear paths from source to destination, so inbound paths are cleared from leaf, and outbound, from Host */

    UINT32 i;
    for (pathSegmentIndex = 0; pathSegmentIndex < usb4_path_ctx->m_pathLength; pathSegmentIndex++)
    {
        if (usb4_path_ctx->m_bDirectionOut)
        {
            i = usb4_path_ctx->m_pathLength - pathSegmentIndex - 1; /* Start from Host */
        }
        else
        {
            i = pathSegmentIndex; /* Start from leaf */
        }

        /* In case router was removed by unplug */
        if (FALSE == Usb4RouterIsEnumerated(&usb4_path_ctx->m_pRouters[usb4_path_ctx->m_pathSegments[i].m_routerIndex]))
        {
            continue;
        }

        if (0 != Usb4PathSegmentInvalidateSegment(&usb4_path_ctx->m_pathSegments[i]))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }

#ifdef USB4_WA_CR_QCTDD06911734_FCM_junk_credit_grant
        {
            usb4_utils_timer timer;
            timer.m_source = USB4_TIMER_SOURCE_QTIMER;
            usb4_timer_Sleep_us(&timer, 3); /* Wait 3uS (tTeardown + 1us Guardband) */
        }
#endif
    }

    return 0;
ErrorHandling:
    return -1;
}


UINT32 Usb4PathGetInterdomainIngressHopID(usb4_path_ctx_t* usb4_path_ctx)
{
    if ((usb4_path_ctx->m_bDirectionOut) || (0 == usb4_path_ctx->m_interdomainAdapterNumber))
    {
        return 0;
    }

    if (usb4_path_ctx->m_pathSegments[0].m_usb4DowstreamPortNumber == usb4_path_ctx->m_interdomainAdapterNumber)
    {
        return usb4_path_ctx->m_pathSegments[0].m_ingressHopID; /* Leaf segment */
    }
    return 0;
}
