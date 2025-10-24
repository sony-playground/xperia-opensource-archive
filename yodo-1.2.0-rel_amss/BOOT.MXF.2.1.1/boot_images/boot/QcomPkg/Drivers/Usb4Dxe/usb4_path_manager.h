/**---------------------------------------------------------------------------
 *   @file        usb4_path_manager.h
 *
 *   @brief   Header file for a paths manager
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#ifndef __USB4_PATH_MANAGER_H_
#define __USB4_PATH_MANAGER_H_

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include "usb4_platform_defs.h"
// #include "VVHAL_usb4_comdef.h"
#include "usb4_router.h"
#include "usb4_path.h"
/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/

/* Max paths is 21 */
#define USB4_MAX_SUPPORTED_PATHS 21

/* Used in an IOCTL through CM */
typedef struct
{
    USB4_portType portType;         /**< Type of the adapter used in the path */
    UINT32 interdomainRouterIndex;  /**< index of the interdomain router (0 to count of interdomain routers - 1) */
    UINT32 interdomainAdapterIndex; /**< index of the interdomain adapter (0 to count of interdomain adapters - 1)*/
    BOOLEAN bSetUpPath;                /**< Set up or tear down the path */
    BOOLEAN bEnableSegments;           /**< Only construct path, or enable it as well */

    /* Out parameters */
    UINT32 path_index_in;            /**< Established path, in case need to enable segments separately, together with the relevant adapter */
    UINT32 path_index_out;         /**< Established path, in case need to enable segments separately, together with the relevant adapter */
} USB4_adapter_path_config_t;

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

typedef struct
{
    usb4_router_ctx_t* m_routers;
    usb4_path_ctx_t m_paths[USB4_MAX_SUPPORTED_PATHS];
    UINT32 m_InterdomainPathCounter;
    USB4_pathParamsOverrideType m_paramsOverrides[USB4_pathType_MAX_VALUE];

    BOOLEAN m_bSkipDpPathBuild;
    BOOLEAN m_bSkipPciePathBuild;
    BOOLEAN m_bSkipUsbPathBuild;
} usb4_path_manager_ctx_t;



/**
 * @brief Create single path according to the parameters
 * @param[in] pPathConstructionParams - Completely defines the path to be created
 * @return 0 on success, other on failure
 */
int Usb4PathManagerCreateSinglePath(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_pathConstructionParamsType* pPathConstructionParams);

/**
 * @brief Create all paths supported by the currently enumerated routers
 * @return 0 on success, other on failure
 */
int Usb4PathManagerCreatePaths(usb4_path_manager_ctx_t* usb4_path_manager_ctx);


/**
 * @brief This function initializes object members
 * @param [in] pHIA - pointer to the control port transport
 * @return 0 on success other on failure
 */
int Usb4PathManagerInit(usb4_path_manager_ctx_t* usb4_path_manager_ctx, usb4_router_ctx_t* pRouters);

/**
 * @brief Check if specific router is covered by a path of the relevant type
 * @param[in] pPathConstructionParams - Completely defines the path to be created
 * @return TRUE if router is covered by a relevant path
 */
BOOLEAN Usb4PathManagerIsRouterCovered(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_pathConstructionParamsType* pPathConstructionParams);

//
//     * @brief Check if specific router is covered by any path
//     * @param[in] topologyID - Topology of the router of interest
//     * @return TRUE if router is covered by a relevant path
//
//    BOOLEAN IsRouterCovered(UINT64 topologyID);

/**
 * @brief Find a free path in the array of paths
 * @param[out] pathIndex - index of the first free path
 * @return 0 on success, other on failure
 */
int Usb4PathManagerFindFreePath(usb4_path_manager_ctx_t* usb4_path_manager_ctx, UINT32* pathIndex);

/**
 * @brief Find a free path in the array of paths
 * @param[in] pathType - Path type
 * @param[out] pathIndex - index of the relevant path in path manager
 * @return 0 on success, other on failure
 */
int Usb4PathManagerFindPathByType(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_pathType pathType, UINT32* pathIndex);

/**
 * @brief Discover a topology change and construct paths as needed
 * @return 0 on success, other on failure
 */
int Usb4PathManagerUpdatePaths(usb4_path_manager_ctx_t* usb4_path_manager_ctx);

/**
 * @brief Establish a path to interdomain router (and adapter)
 * @param[In] pPathConf - path configuration
 * @return 0 on success, other on failure
 */
int Usb4PathManagerSetUpInterdomainPath(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_adapter_path_config_t* pPathConf);

/**
 * @brief Control path segments enable/disable
 * @param[In] path_index - segments to apply the action to
 * @return 0 on success, other on failure
 */
int Usb4PathManagerEnablePathSegments(usb4_path_manager_ctx_t* usb4_path_manager_ctx, UINT32 path_index, BOOLEAN bEnable);

/**
 * @brief Identify all paths that were impacted by hot un-plug event.
 * Invalidate all the path segments on all the remaining routers.
 * @param[in] router_topologyID - Topology of the router which was unplugged
 * @return 0 on success, other on failure
 */
int Usb4PathManagerInvalidatePathsBeyondTopology(usb4_path_manager_ctx_t* usb4_path_manager_ctx, UINT64 router_topologyID);

/**
 * @brief Handles hot un-plug on a port other than USB4,
 * or on inter-domain USB4 port
 * @param[in] router_topologyID - Topology of the router which was unplugged
 * @param[in] adapter - Inter-domain adapter
 * @return 0 on success, other on failure
 */
int Usb4PathManagerInvalidatePathFromPort(usb4_path_manager_ctx_t* usb4_path_manager_ctx, UINT64 router_topologyID, UINT32 adapter);

/**
 * @brief Selectively delete paths of a specific type
 * @param[in] router_topologyID - Topology of the router which was unplugged
 * @param[in] adapter - Inter-domain adapter
 * @param[in] pathType - Path type
 * @return 0 on success, other on failure
 */
int Usb4PathManagerInvalidatePathFromPortByType(usb4_path_manager_ctx_t* usb4_path_manager_ctx, UINT64 router_topologyID, UINT32 adapter, USB4_pathType pathType);

/**
 * @brief Selectively delete paths of a specific type
 * @param[in] pathType - Path type
 * @return 0 on success, other on failure
 */
int Usb4PathManagerInvalidatePathByType(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_pathType pathType);

/**
 * @brief Delete all pathes, while updating routers
 * @return 0 on success, other on failure
 */
int Usb4PathManagerDestroyPaths(usb4_path_manager_ctx_t* usb4_path_manager_ctx);

int Usb4PathManagerOverridePathParameters(usb4_path_manager_ctx_t* usb4_path_manager_ctx, USB4_pathParamsOverrideType params);

#endif /* __USB4_PATH_MANAGER_H_ */
