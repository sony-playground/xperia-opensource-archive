/**---------------------------------------------------------------------------
 *   @file        usb4_path.h
 *
 *   @brief       Path class
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#ifndef __USB4_PATH_H_
#define __USB4_PATH_H_

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include "VVDRV_usb4_HIA.h"
// #include "VVHAL_usb4_comdef.h"
#include "usb4_platform_defs.h"
#include "usb4_path_segment.h"

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/

typedef struct
{
    BOOLEAN        bOverrideActive;
    USB4_pathType  pathType;
    BOOLEAN        bRouterIndexValid;
    UINT32         routerIndex; /* Modify only the part of path going through the specific router */
    BOOLEAN        bNumOfBuffersValid;
    UINT32         numOfBuffers;
    USB4_pathCsParamsType  pathCsParams;

} USB4_pathParamsOverrideType;

typedef struct
{
    USB4_pathType pathType;
    UINT64 topologyID;
    UINT32 interdomainPathCounter;
    UINT32 interdomainEgressHopID; /**< We want to point Interdomain OUT path to the same entry as was used for the IN path;
                                        0 - default would not be modified */
    USB4_pathParamsOverrideType* pPathParamsOverride;

    /* Output param */
    UINT32 path_index;
} USB4_pathConstructionParamsType;

#define USB4_MAX_PATH_LENGTH (USB4_MAX_SUPPORTED_ROUTERS)

typedef struct
{
    usb4_router_ctx_t* m_pRouters;

    /* indexes of the routers present in the topology ID
     * in reverse order. Last attached router
     * (with leafTopologyID = router topologyID) is the first in the array*/
    usb4_path_segment_ctx_t m_pathSegments[USB4_MAX_PATH_LENGTH];

    BOOLEAN m_bDirectionOut;
    BOOLEAN m_bAux;
    BOOLEAN m_bPathEnabled;
    USB4_pathType m_Type;
    UINT64 m_leafTopologyID;
    UINT32 m_interdomainAdapterNumber;
    UINT32 m_pathLength;
    UINT32 m_InterdomainPathCounter;
} usb4_path_ctx_t;


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
 * @brief Identify adapter ports types that will participate in
 * building routing segments
 * @param[in] topologyID - Specify topology ID of the segment router
 * @param[in] bIsLeaf - Specify if the segment is a leaf segment
 * @return port type
 */
USB4_portType Usb4PathIdentifySegmentAdapterType(usb4_path_ctx_t* usb4_path_ctx, UINT64 topologyID, BOOLEAN bIsLeaf);

/**
 * @brief Identify and populate routers participating in a path
 * @return 0 on success other on failure
 */
int Usb4PathIdentifyRouters(usb4_path_ctx_t* usb4_path_ctx);

/**
 * @brief Calculate the number of buffers this path can consume
 * @return 0 on success other on failure
 */
int Usb4PathCalculateBuffers(usb4_path_ctx_t* usb4_path_ctx);

/**
 * @brief Calculate the number of buffers this path can consume
 * @param[in] pPathParamsOverride - Modify path parameters according to the test
 * @return 0 on success other on failure
 */
int Usb4PathOverrideSegmentParams(usb4_path_ctx_t* usb4_path_ctx, USB4_pathParamsOverrideType* pPathParamsOverride);

/**
 * @brief Translate path type into a direction
 * @return 0 on success other on failure
 */
int Usb4PathAssignDirection(usb4_path_ctx_t* usb4_path_ctx);


/**
 * @brief This function initializes object members
 * @param [in] pRouters - pointer to the array of routers in CM
 * @return 0 on success other on failure
 */
int Usb4PathInit(usb4_path_ctx_t* usb4_path_ctx, usb4_router_ctx_t* pRouters);

/**
 * @brief Get index of a router with the requested ID
 * @param[in] router_topologyID
 * @param[out] index
 * @return 0 on success other on failure
 */
int Usb4PathFindRouterByTopology(usb4_path_ctx_t* usb4_path_ctx, UINT64 router_topologyID, UINT32* index);

/**
 * @brief Get path index of a router with the requested ID
 * @param[in] router_topologyID
 * @param[out] pathSegmentIndex
 * @return 0 on success other on failure
 */
int Usb4PathFindpathSegmentByTopology(usb4_path_ctx_t* usb4_path_ctx, UINT64 router_topologyID, UINT32* pathSegmentIndex);

/**
 * @brief Construct path to a specific, newly found upstream
 * port of the device router
 * @param [in] pPathConstructionParams - Completely describes the path to be constructed
 * @return 0 on success other on failure
 */
int Usb4PathConstruct(usb4_path_ctx_t* usb4_path_ctx, USB4_pathConstructionParamsType* pPathConstructionParams);

/**
 * @brief Enable adapters involved in this path. Need to do it after both directions have been configured.
 * @return 0 on success other on failure
 */
int Usb4PathEnableSegments(usb4_path_ctx_t* usb4_path_ctx, BOOLEAN bEnable);

/**
 * @brief Delete path data structures, without accessing actual routers
 * @return 0 on success other on failure
 */
int Usb4PathClear(usb4_path_ctx_t* usb4_path_ctx);

/**
 * @brief Return USB4 DN port number for the router in this path
 * @param[in] pathSegmentIndex - path router index
 * @return port number (0 stands for invalid value)
 */
UINT32 Usb4PathGetUsb4DnPortNumber(usb4_path_ctx_t* usb4_path_ctx, UINT32 pathSegmentIndex);

/**
 * @brief Clear (disable and invalidate) path segments on routers
 * in this path starting with the pathSegmentIndex
 * @return 0 on success other on failure
 */
int Usb4PathInvalidateSegments(usb4_path_ctx_t* usb4_path_ctx);

/**
 * @brief Configure path segments according to actors
 * @param[in] interdomainEgressHopID - We want to point Interdomain OUT path to the same entry as was used for the IN path;
 *                                     0 - default would not be modified
 * @return 0 on success other on failure
 */
int Usb4PathConfigureSegments(usb4_path_ctx_t* usb4_path_ctx, UINT32 interdomainEgressHopID);

/**
 * @brief In case of inter-domain IN path, get inbound Hop ID
 * @return Return inbount Hop ID, or 0 if not applicable
 */
UINT32 Usb4PathGetInterdomainIngressHopID(usb4_path_ctx_t* usb4_path_ctx);

#endif /* __USB4_PATH_H_ */
