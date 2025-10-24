/**---------------------------------------------------------------------------
 *   @file        usb4_path_manager.c
 *
 *   @brief       Implementation of Path Manager methods
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include <Usb4Log.h>
#include "usb4_router.h"
#include "usb4_path_segment.h"
#include "usb4_path.h"
// #include "VVHAL_usb4_utils.h"
#include <string.h>
#include "usb4_path_manager.h"


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

int Usb4PathManagerInit(usb4_path_manager_ctx_t* usb4_path_manager_ctx, usb4_router_ctx_t* pRouters)
{
    UINT32 i;

    if (NULL == pRouters)
    {
        USB4_ERROR_STACK_MSG(-1, "Pointer to routers can't be null");
        return -1;
    }
    usb4_path_manager_ctx->m_routers = NULL;
    // m_paths()
    usb4_path_manager_ctx->m_InterdomainPathCounter = 0;
    // m_paramsOverrides()
    usb4_path_manager_ctx->m_bSkipDpPathBuild = TRUE;
    usb4_path_manager_ctx->m_bSkipPciePathBuild = TRUE;
    usb4_path_manager_ctx->m_bSkipUsbPathBuild = TRUE;

    usb4_path_manager_ctx->m_routers = pRouters;
    usb4_path_manager_ctx->m_InterdomainPathCounter = 0;

    for (i = 0; i < USB4_MAX_SUPPORTED_PATHS; i++)
    {
        if (0 != Usb4PathInit(&usb4_path_manager_ctx->m_paths[i], usb4_path_manager_ctx->m_routers))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }
    memset((UINT8*)(usb4_path_manager_ctx->m_paramsOverrides), 0, sizeof(usb4_path_manager_ctx->m_paramsOverrides));

    usb4_path_manager_ctx->m_bSkipDpPathBuild = TRUE;
    usb4_path_manager_ctx->m_bSkipPciePathBuild = TRUE;
    usb4_path_manager_ctx->m_bSkipUsbPathBuild = TRUE;
    return 0;
ErrorHandling:
    return -1;
};

int Usb4PathManagerDestroyPaths(usb4_path_manager_ctx_t* usb4_path_manager_ctx)
{
    UINT32 path_index;

    for (path_index = 0; path_index < USB4_MAX_SUPPORTED_PATHS; path_index++)
    {
        if (USB4_pathType_NOT_VALID != usb4_path_manager_ctx->m_paths[path_index].m_Type)
        {
            if (0 != Usb4PathEnableSegments(&usb4_path_manager_ctx->m_paths[path_index], FALSE))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
        }
    }

    for (path_index = 0; path_index < USB4_MAX_SUPPORTED_PATHS; path_index++)
    {
        if (USB4_pathType_NOT_VALID != usb4_path_manager_ctx->m_paths[path_index].m_Type)
        {
            if (0 != Usb4PathInvalidateSegments(&usb4_path_manager_ctx->m_paths[path_index]))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
            USB4_ASSERT(0 == Usb4PathClear(&usb4_path_manager_ctx->m_paths[path_index]));
        }
    }
    return 0;
ErrorHandling:
    return -1;
}

BOOLEAN Usb4PathManagerIsRouterCovered(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_pathConstructionParamsType* pPathConstructionParams)
{
    UINT32 path_index;
    UINT64 topologyID = pPathConstructionParams->topologyID;
    USB4_pathType pathType = pPathConstructionParams->pathType;

    for (path_index = 0; path_index < USB4_MAX_SUPPORTED_PATHS; path_index++)
    {
        if (pPathConstructionParams->pathType == usb4_path_manager_ctx->m_paths[path_index].m_Type)
        {
            switch (pathType)
            {
                default:
                    /* Current router is on a topological hierarchy and path mandatory goes up to a host router */
                    if (topologyID == (topologyID & usb4_path_manager_ctx->m_paths[path_index].m_leafTopologyID))
                    {
                        return TRUE;
                    }
                    break;
                case USB4_pathType_HIA_IN:
                case USB4_pathType_HIA_OUT:
                case USB4_pathType_H2H_PCIE_IN:
                case USB4_pathType_H2H_PCIE_OUT:
                case USB4_pathType_H2H_DP_IN_AUX:
                case USB4_pathType_H2H_DP_OUT_AUX:
                case USB4_pathType_H2H_USB3_IN:
                case USB4_pathType_H2H_USB3_OUT:
                {
                    if (topologyID == (topologyID & usb4_path_manager_ctx->m_paths[path_index].m_leafTopologyID))
                    {
                        return TRUE;
                    }
                    break;
                }
                case USB4_pathType_PCIE_IN:
                case USB4_pathType_PCIE_OUT:
                case USB4_pathType_USB3_IN:
                case USB4_pathType_USB3_OUT:
                    /* Routers may be covered by downstream and upstream segments of separate paths,
                     * so router is covered only if it actually a leaf of the path */
                    if (topologyID == usb4_path_manager_ctx->m_paths[path_index].m_leafTopologyID)
                    {
                        return TRUE;
                    }
                    break;
            }
        }
    }
    return FALSE;
}

//BOOLEAN Usb4PathManagerIsRouterCovered(UINT64 topologyID)
//{
//    UINT32 path_index;
//
//    for (path_index = 0; path_index < USB4_MAX_SUPPORTED_PATHS; path_index++)
//    {
//        // Current router is on a sub-path
//        if (topologyID == (topologyID & usb4_path_manager_ctx->m_paths[path_index].m_leafTopologyID))
//        {
//            return TRUE;
//        }
//    }
//    return FALSE;
//}

int Usb4PathManagerFindFreePath(usb4_path_manager_ctx_t* usb4_path_manager_ctx, UINT32* pathIndex)
{
    UINT32 freePathIndex = 0;

    while(freePathIndex < USB4_MAX_SUPPORTED_PATHS)
    {
        if (USB4_pathType_NOT_VALID == usb4_path_manager_ctx->m_paths[freePathIndex].m_Type)
        {
            break;
        }
        freePathIndex++;
    }
    USB4_ASSERT_MSG(freePathIndex < USB4_MAX_SUPPORTED_PATHS, "No free paths left");

    *pathIndex = freePathIndex;

    return 0;
}


int Usb4PathManagerFindPathByType(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_pathType pathType, UINT32* pathIndex)
{
    UINT32 index = 0;

    USB4_ASSERT(NULL != pathIndex);

    while(index < USB4_MAX_SUPPORTED_PATHS)
    {
        if (pathType == usb4_path_manager_ctx->m_paths[index].m_Type)
        {
            break;
        }
        index++;
    }
    USB4_ASSERT_MSG(index < USB4_MAX_SUPPORTED_PATHS, "No path of the requested type found");

    *pathIndex = index;

    return 0;
}

int Usb4PathManagerCreateSinglePath(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_pathConstructionParamsType* pPathConstructionParams)
{
    UINT32 path_index;

    pPathConstructionParams->pPathParamsOverride = &usb4_path_manager_ctx->m_paramsOverrides[(UINT8)(pPathConstructionParams->pathType)];

    if (FALSE == Usb4PathManagerIsRouterCovered(usb4_path_manager_ctx, pPathConstructionParams))
    {
        USB4_ASSERT(0 == Usb4PathManagerFindFreePath(usb4_path_manager_ctx, &path_index));
        pPathConstructionParams->path_index = path_index;

        if (0 != Usb4PathConstruct(&usb4_path_manager_ctx->m_paths[path_index], pPathConstructionParams))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }
    else
    {
        USB4_ASSERT(0 == Usb4PathManagerFindPathByType(usb4_path_manager_ctx, pPathConstructionParams->pathType, &pPathConstructionParams->path_index));
    }
    return 0;
ErrorHandling:
    return -1;
}

int Usb4PathManagerCreatePaths(usb4_path_manager_ctx_t* usb4_path_manager_ctx)
{
    UINT32 i;
    USB4_pathConstructionParamsType pathConstructionParams = {};

    /* Farthest router is added last. Routers bay be on different branches, but a sub-path
     * has a lower index that a path to the leafדכ
     * So, the longest path will be created first.
     * Previously, all paths were deleted, so any duplication will be avoided.
     */
    for (i = USB4_MAX_SUPPORTED_ROUTERS - 1; i > 0 /* Skip Host router */; i--)
    {
        if (FALSE == Usb4RouterIsEnumerated(&usb4_path_manager_ctx->m_routers[i]))
        {
            continue;
        }
        pathConstructionParams.topologyID = usb4_path_manager_ctx->m_routers[i].m_topologyID;
        pathConstructionParams.interdomainPathCounter = usb4_path_manager_ctx->m_InterdomainPathCounter;
        
        /* Has to happen after configuration valid bit was written */
        if (usb4_path_manager_ctx->m_routers[i].m_bPcieTunneling)
        {
            if (FALSE == usb4_path_manager_ctx->m_bSkipPciePathBuild)
            {
                UINT32 in, out;
                // USB4_LOG_INFO("Building USB4_pathType_PCIE_IN path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerCreatePathsBuildingUSB4PathTypePCIEINpath__Info, 0);
                pathConstructionParams.pathType = USB4_pathType_PCIE_IN;
                USB4_ASSERT(0 == Usb4PathManagerCreateSinglePath(usb4_path_manager_ctx, &pathConstructionParams));
                in = pathConstructionParams.path_index;
                // USB4_LOG_INFO("Building USB4_pathType_PCIE_OUT path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerCreatePathsBuildingUSB4PathTypePCIEOUTpath__Info, 0);
                pathConstructionParams.pathType = USB4_pathType_PCIE_OUT;
                USB4_ASSERT(0 == Usb4PathManagerCreateSinglePath(usb4_path_manager_ctx, &pathConstructionParams));
                out = pathConstructionParams.path_index;
                // USB4_LOG_INFO("Enable USB4_pathType_PCIE_IN path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerCreatePathsEnableUSB4PathTypePCIEINpath__Info, 0);
                USB4_ASSERT(0 == Usb4PathManagerEnablePathSegments(usb4_path_manager_ctx, in, TRUE));
                // USB4_LOG_INFO("Enable USB4_pathType_PCIE_OUT path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerCreatePathsEnableUSB4PathTypePCIEOUTpath__Info, 0);
                USB4_ASSERT(0 == Usb4PathManagerEnablePathSegments(usb4_path_manager_ctx, out, TRUE));
            }
            else
            {
                USB4_ASSERT(0 == Usb4PathManagerInvalidatePathByType(usb4_path_manager_ctx, USB4_pathType_PCIE_OUT));
                USB4_ASSERT(0 == Usb4PathManagerInvalidatePathByType(usb4_path_manager_ctx, USB4_pathType_PCIE_IN));
            }
        }
        
        if (usb4_path_manager_ctx->m_routers[i].m_bUsb3Tunneling)
        {
            if (FALSE == usb4_path_manager_ctx->m_bSkipUsbPathBuild)
            {
                UINT32 in, out;
                // USB4_LOG_INFO("Building USB4_pathType_USB3_IN path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerCreatePathsBuildingUSB4PathTypeUSB3INpath__Info, 0);
                pathConstructionParams.pathType = USB4_pathType_USB3_IN;
                USB4_ASSERT(0 == Usb4PathManagerCreateSinglePath(usb4_path_manager_ctx, &pathConstructionParams));
                in = pathConstructionParams.path_index;
                // USB4_LOG_INFO("Building USB4_pathType_USB3_OUT path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerCreatePathsBuildingUSB4PathTypeUSB3OUTpath__Info, 0);
                pathConstructionParams.pathType = USB4_pathType_USB3_OUT;
                USB4_ASSERT(0 == Usb4PathManagerCreateSinglePath(usb4_path_manager_ctx, &pathConstructionParams));
                out = pathConstructionParams.path_index;
                // USB4_LOG_INFO("Enable USB4_pathType_USB3_IN path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerCreatePathsEnableUSB4PathTypeUSB3INpath__Info, 0);
                USB4_ASSERT(0 == Usb4PathManagerEnablePathSegments(usb4_path_manager_ctx, in, TRUE));
                // USB4_LOG_INFO("Enable USB4_pathType_USB3_OUT path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerCreatePathsEnableUSB4PathTypeUSB3OUTpath__Info, 0);
                USB4_ASSERT(0 == Usb4PathManagerEnablePathSegments(usb4_path_manager_ctx, out, TRUE));
            }
            else
            {
                USB4_ASSERT(0 == Usb4PathManagerInvalidatePathByType(usb4_path_manager_ctx, USB4_pathType_USB3_OUT));
                USB4_ASSERT(0 == Usb4PathManagerInvalidatePathByType(usb4_path_manager_ctx, USB4_pathType_USB3_IN));
            }
        }

        if (usb4_path_manager_ctx->m_routers[i].m_bDpTunneling &&
           (0 != usb4_path_manager_ctx->m_routers[i].m_displayPortAdapter))
        {
		    if (FALSE == usb4_path_manager_ctx->m_bSkipDpPathBuild) /* Build path only if one of the DP_OUT adapter has received a plug-in even */
            {
                UINT32 in, out;
                // USB4_LOG_INFO("Building USB4_pathType_DP_MAIN path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerBuildingUSB4PathTypeDPMAINpath__Info, 0);
                pathConstructionParams.pathType = USB4_pathType_DP_MAIN;
                USB4_ASSERT(0 == Usb4PathManagerCreateSinglePath(usb4_path_manager_ctx, &pathConstructionParams));

                // USB4_LOG_INFO("Building USB4_pathType_DP_IN_AUX path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerBuildingUSB4PathTypeDPINAUXpath__Info, 0);
                pathConstructionParams.pathType = USB4_pathType_DP_IN_AUX;
                USB4_ASSERT(0 == Usb4PathManagerCreateSinglePath(usb4_path_manager_ctx, &pathConstructionParams));
                in = pathConstructionParams.path_index;

                // USB4_LOG_INFO("Building USB4_pathType_DP_OUT_AUX path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerBuildingUSB4_PathTypeDPOUTAUXpath__Info, 0);
                pathConstructionParams.pathType = USB4_pathType_DP_OUT_AUX;
                USB4_ASSERT(0 == Usb4PathManagerCreateSinglePath(usb4_path_manager_ctx, &pathConstructionParams));
                out = pathConstructionParams.path_index;

                // USB4_LOG_INFO("Enable USB4_pathType_DP_OUT_AUX path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerEnableUSB4PathTypeDPOUTAUXpath__Info, 0);
                USB4_ASSERT(0 == Usb4PathManagerEnablePathSegments(usb4_path_manager_ctx, out, TRUE));

                // USB4_LOG_INFO("Enable USB4_pathType_DP_IN_AUX path\n");
                Usb4Log(USB4_LOG_CM, Usb4PathManagerEnableUSB4PathTypeDPINAUXpath__Info, 0);
                USB4_ASSERT(0 == Usb4PathManagerEnablePathSegments(usb4_path_manager_ctx, in, TRUE));
            }
		   else
		   {
		       USB4_ASSERT(0 == Usb4PathManagerInvalidatePathByType(usb4_path_manager_ctx, USB4_pathType_DP_OUT_AUX));
		       USB4_ASSERT(0 == Usb4PathManagerInvalidatePathByType(usb4_path_manager_ctx, USB4_pathType_DP_IN_AUX));
		       USB4_ASSERT(0 == Usb4PathManagerInvalidatePathByType(usb4_path_manager_ctx, USB4_pathType_DP_MAIN));
		   }
        }
    }
    return 0;
}

int Usb4PathManagerUpdatePaths(usb4_path_manager_ctx_t* usb4_path_manager_ctx)
{
//    UINT32 path_index;

    /* Delete all path - will not update routers, so as not to interrupt active traffic
     * Bandwidth will be re-assigned.*/
    //TODO: See if no resource leakage happens without this step. This code was introduced before
    //each un-plug action was processed correctly.
//    for (path_index = 0; path_index < USB4_MAX_SUPPORTED_PATHS; path_index++)
//    {
//        USB4_ASSERT(0==m_paths[path_index].Clear());
//    }

    if (0!=Usb4PathManagerCreatePaths(usb4_path_manager_ctx))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    return 0;
ErrorHandling:
    return -1;
}

int Usb4PathManagerSetUpInterdomainPath(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_adapter_path_config_t* pPathConf)
{
    UINT32 router, adapter;
    UINT32 interdomaAdapterCounter = 0, interdomainRouterCounter = 0;
    USB4_pathType inPath = USB4_pathType_HIA_IN, outPath = USB4_pathType_HIA_OUT;

    usb4_port_ctx_t* interdomainPort;

    pPathConf->path_index_in = USB4_MAX_SUPPORTED_PATHS;
    pPathConf->path_index_out = USB4_MAX_SUPPORTED_PATHS;

    for (router = 0; router < USB4_MAX_SUPPORTED_ROUTERS; router++)
    {
        if (usb4_path_manager_ctx->m_routers[router].m_bInterdomainRouter)
        {
            if (interdomainRouterCounter == pPathConf->interdomainRouterIndex)
            {
                break;
            }
            interdomainRouterCounter++;
        }
    }
    USB4_ASSERT(router < USB4_MAX_SUPPORTED_ROUTERS);


    USB4_ASSERT(Usb4RouterGetNumberOfAdapters(&usb4_path_manager_ctx->m_routers[router]) > 0);
    for (adapter = 0; adapter < Usb4RouterGetNumberOfAdapters(&usb4_path_manager_ctx->m_routers[router]); adapter++)
    {
        interdomainPort = Usb4RouterGetInterdomainAdapter(&usb4_path_manager_ctx->m_routers[router], adapter);
        if (NULL != interdomainPort)
        {
            adapter = interdomainPort->m_Number;
            if (interdomaAdapterCounter == pPathConf->interdomainAdapterIndex)
            {
                break;
            }
            interdomaAdapterCounter++;
        }
        else
        {
            break;
        }
    }
    USB4_ASSERT(NULL != interdomainPort);

    switch(pPathConf->portType)
   {
	   case USB4_portType_HIA:
		   inPath = USB4_pathType_HIA_IN;
		   outPath = USB4_pathType_HIA_OUT;
		   break;
	   case USB4_portType_DOWNSTREAM_PCIE_ADAPTER:
		   inPath = USB4_pathType_H2H_PCIE_IN;
		   outPath = USB4_pathType_H2H_PCIE_OUT;
		   break;
	   case USB4_portType_DOWNSTREAM_USB3_ADAPTER:
		   inPath = USB4_pathType_H2H_USB3_IN;
		   outPath = USB4_pathType_H2H_USB3_OUT;
		   break;
	   case USB4_portType_DP_IN:
		   inPath = USB4_pathType_H2H_DP_OUT_AUX;
		   outPath = USB4_pathType_H2H_DP_IN_AUX;
		   break;
	   default:
		   USB4_ASSERT_MSG(0, "Wrong path type\n");
		   break;
   }

    if (pPathConf->bSetUpPath)
    {
        USB4_pathParamsOverrideType pathParamsOverride = {};
        USB4_pathConstructionParamsType pathConstructionParams = {};
        UINT64 interdomainTopologyID = usb4_next_router_topology(usb4_path_manager_ctx->m_routers[router].m_topologyID, adapter);

        pathConstructionParams.pPathParamsOverride = &pathParamsOverride;
        pathConstructionParams.topologyID = interdomainTopologyID;
        pathConstructionParams.interdomainPathCounter = usb4_path_manager_ctx->m_InterdomainPathCounter;
        pathConstructionParams.pathType = inPath;

        USB4_ASSERT(0 == Usb4PathManagerCreateSinglePath(usb4_path_manager_ctx, &pathConstructionParams));
        pPathConf->path_index_in = pathConstructionParams.path_index;

        pathConstructionParams.pathType = outPath;
        pathConstructionParams.interdomainEgressHopID = Usb4PathGetInterdomainIngressHopID(&usb4_path_manager_ctx->m_paths[pPathConf->path_index_in]);
        USB4_ASSERT(0 == Usb4PathManagerCreateSinglePath(usb4_path_manager_ctx, &pathConstructionParams));
        pPathConf->path_index_out = pathConstructionParams.path_index;

        if (pPathConf->bEnableSegments)
        {

            USB4_ASSERT(0 == Usb4PathManagerEnablePathSegments(usb4_path_manager_ctx, pPathConf->path_index_in, TRUE));
            USB4_ASSERT(0 == Usb4PathManagerEnablePathSegments(usb4_path_manager_ctx, pPathConf->path_index_out, TRUE));
        }
        /* Increment by 1 for both directions, by convention */
        (usb4_path_manager_ctx->m_InterdomainPathCounter)++;
    }
    else
    {
        USB4_ASSERT(0 == Usb4PathManagerInvalidatePathFromPortByType(usb4_path_manager_ctx, usb4_path_manager_ctx->m_routers[router].m_topologyID, adapter, inPath));
        USB4_ASSERT(0 == Usb4PathManagerInvalidatePathFromPortByType(usb4_path_manager_ctx, usb4_path_manager_ctx->m_routers[router].m_topologyID, adapter, outPath));
        if (usb4_path_manager_ctx->m_InterdomainPathCounter > 0)
        {
          usb4_path_manager_ctx->m_InterdomainPathCounter--;
        }
    }

    return 0;
}

int Usb4PathManagerEnablePathSegments(usb4_path_manager_ctx_t* usb4_path_manager_ctx, UINT32 path_index, BOOLEAN bEnable)
{
    /* Same segments are involved, so don't need to enable both */
    if (USB4_MAX_SUPPORTED_PATHS > path_index)
    {
        return Usb4PathEnableSegments(&usb4_path_manager_ctx->m_paths[path_index], bEnable);
    }
    return -1;
}

int Usb4PathManagerInvalidatePathsBeyondTopology(usb4_path_manager_ctx_t* usb4_path_manager_ctx, UINT64 router_topologyID)
{
    UINT32 pathIndex;
    //UINT32 pathSegmentIndex;
    usb4_path_ctx_t* path;

    for (pathIndex = 0; pathIndex < USB4_MAX_SUPPORTED_PATHS; pathIndex++)
    {
        if ((USB4_pathType_NOT_VALID != usb4_path_manager_ctx->m_paths[pathIndex].m_Type) &&
            (router_topologyID == (router_topologyID & usb4_path_manager_ctx->m_paths[pathIndex].m_leafTopologyID)))
        {
            if (0 != Usb4PathEnableSegments(&usb4_path_manager_ctx->m_paths[pathIndex], FALSE))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
        }
    }

    for (pathIndex = 0; pathIndex < USB4_MAX_SUPPORTED_PATHS; pathIndex++)
    {
        /* Removed router is on a sub-path */
        if ((USB4_pathType_NOT_VALID != usb4_path_manager_ctx->m_paths[pathIndex].m_Type) &&
            (router_topologyID == (router_topologyID & usb4_path_manager_ctx->m_paths[pathIndex].m_leafTopologyID)))
        {
            path = &usb4_path_manager_ctx->m_paths[pathIndex];
            USB4_ASSERT(0 == Usb4PathInvalidateSegments(path));
            USB4_ASSERT(0 == Usb4PathClear(path));
        }
    }
    return 0;
ErrorHandling:
    return -1;
}


int Usb4PathManagerInvalidatePathFromPortByType(usb4_path_manager_ctx_t* usb4_path_manager_ctx, UINT64 router_topologyID, UINT32 adapter, USB4_pathType pathType)
{
    UINT32 pathIndex;
    usb4_path_ctx_t* path;

    for (pathIndex = 0; pathIndex < USB4_MAX_SUPPORTED_PATHS; pathIndex++)
    {
        /* Unplug happened on inter-domain boundary */
        if ((router_topologyID == usb4_path_manager_ctx->m_paths[pathIndex].m_leafTopologyID)&&
                (adapter == Usb4PathGetUsb4DnPortNumber(&usb4_path_manager_ctx->m_paths[pathIndex], 0))&&
                (pathType == usb4_path_manager_ctx->m_paths[pathIndex].m_Type))
        {
            if (0 != Usb4PathEnableSegments(&usb4_path_manager_ctx->m_paths[pathIndex], FALSE))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
        }
    }

    for (pathIndex = 0; pathIndex < USB4_MAX_SUPPORTED_PATHS; pathIndex++)
    {
        /* Unplug happened on inter-domain boundary */
        if ((router_topologyID == usb4_path_manager_ctx->m_paths[pathIndex].m_leafTopologyID)&&
                (adapter == Usb4PathGetUsb4DnPortNumber(&usb4_path_manager_ctx->m_paths[pathIndex], 0))&&
				(pathType == usb4_path_manager_ctx->m_paths[pathIndex].m_Type))
        {
            path = &usb4_path_manager_ctx->m_paths[pathIndex];

            if (0 != Usb4PathInvalidateSegments(path))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
            USB4_ASSERT(0 == Usb4PathClear(path));
        }
    }
    return 0;
ErrorHandling:
    return -1;
}

int Usb4PathManagerInvalidatePathByType(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_pathType pathType)
{
    UINT32 pathIndex;

    for (pathIndex = 0; pathIndex < USB4_MAX_SUPPORTED_PATHS; pathIndex++)
    {
        if (pathType == usb4_path_manager_ctx->m_paths[pathIndex].m_Type)
        {
            USB4_ASSERT(0 == Usb4PathEnableSegments(&usb4_path_manager_ctx->m_paths[pathIndex], FALSE));
        }
    }

    for (pathIndex = 0; pathIndex < USB4_MAX_SUPPORTED_PATHS; pathIndex++)
    {
        if (pathType == usb4_path_manager_ctx->m_paths[pathIndex].m_Type)
        {
            USB4_ASSERT(0 == Usb4PathInvalidateSegments(&usb4_path_manager_ctx->m_paths[pathIndex]));
            USB4_ASSERT(0 == Usb4PathClear(&usb4_path_manager_ctx->m_paths[pathIndex]));
        }
    }
    return 0;
}

int Usb4PathManagerInvalidatePathFromPort(usb4_path_manager_ctx_t* usb4_path_manager_ctx, UINT64 router_topologyID, UINT32 adapter)
{
    UINT32 pathIndex;
    UINT64 next_topology = 0;
    UINT32 i;
    usb4_router_ctx_t* router;
    usb4_port_ctx_t* port;

    for (i=0; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        if (router_topologyID == usb4_path_manager_ctx->m_routers[i].m_topologyID)
        {
            break;
        }
    }
    USB4_ASSERT(i < USB4_MAX_SUPPORTED_ROUTERS);
    router = &usb4_path_manager_ctx->m_routers[i];
    port = Usb4RouterGetAdapterPortByNumber(router, adapter);
    USB4_ASSERT(NULL != port);

    if ((USB4_portType_LANE0 == Usb4PortGetPortType(port))||
        (USB4_portType_LANE1 == Usb4PortGetPortType(port)))
    {
        next_topology = usb4_next_router_topology(router_topologyID, adapter);
        USB4_ASSERT(0 == Usb4PathManagerInvalidatePathsBeyondTopology(usb4_path_manager_ctx, next_topology));
    }

    if (USB4_portType_DP_OUT == Usb4PortGetPortType(port))
    {

        for (pathIndex = 0; pathIndex < USB4_MAX_SUPPORTED_PATHS; pathIndex++)
        {
            if (USB4_pathType_DP_OUT_AUX == usb4_path_manager_ctx->m_paths[pathIndex].m_Type)
            {
                USB4_ASSERT(0 == Usb4PathEnableSegments(&usb4_path_manager_ctx->m_paths[pathIndex], FALSE));
            }
        }

        for (pathIndex = 0; pathIndex < USB4_MAX_SUPPORTED_PATHS; pathIndex++)
        {
            if (USB4_pathType_DP_IN_AUX == usb4_path_manager_ctx->m_paths[pathIndex].m_Type)
            {
                USB4_ASSERT(0 == Usb4PathEnableSegments(&usb4_path_manager_ctx->m_paths[pathIndex], FALSE));
            }
        }

        for (pathIndex = 0; pathIndex < USB4_MAX_SUPPORTED_PATHS; pathIndex++)
        {
            if (USB4_pathType_DP_MAIN == usb4_path_manager_ctx->m_paths[pathIndex].m_Type)
            {
                USB4_ASSERT(0 == Usb4PathEnableSegments(&usb4_path_manager_ctx->m_paths[pathIndex], FALSE));
            }
        }

        for (pathIndex = 0; pathIndex < USB4_MAX_SUPPORTED_PATHS; pathIndex++)
        {
            if ((USB4_pathType_DP_IN_AUX == usb4_path_manager_ctx->m_paths[pathIndex].m_Type)||
                (USB4_pathType_DP_OUT_AUX == usb4_path_manager_ctx->m_paths[pathIndex].m_Type)||
                (USB4_pathType_DP_MAIN == usb4_path_manager_ctx->m_paths[pathIndex].m_Type))
            {
                USB4_ASSERT(0 == Usb4PathInvalidateSegments(&usb4_path_manager_ctx->m_paths[pathIndex]));
                USB4_ASSERT(0 == Usb4PathClear(&usb4_path_manager_ctx->m_paths[pathIndex]));
            }
        }

        /* De-allocate DP resource */
        //port = m_routers[0].GetAdapterPortByType(USB4_portType_DP_IN, 0);
        //USB4_ASSERT(0 != m_routers[0].AllocateDeAllocateDpResource(port->m_Number, FALSE));
    }

    return 0;
}

int Usb4PathManagerOverridePathParameters(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_pathParamsOverrideType params)
{
    USB4_ASSERT(params.routerIndex < USB4_MAX_SUPPORTED_ROUTERS);
    USB4_ASSERT(TRUE == Usb4RouterIsEnumerated(&usb4_path_manager_ctx->m_routers[params.routerIndex]));

    /* Store overrides for future use during path construction */
    usb4_path_manager_ctx->m_paramsOverrides[(UINT8)(params.pathType)] = params;

    return 0;
}
