/**---------------------------------------------------------------------------
 *   @file        usb4_path_segment.h
 *
 *   @brief   Path router class
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/
#ifndef _USB4_path_segment_H_
#define _USB4_path_segment_H_

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include "VVDRV_usb4_HIA.h"
// #include "VVHAL_usb4_comdef.h"
// #include "VVHAL_usb4_platform_defs.h"

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/
typedef enum
{
    USB4_pathType_NOT_VALID = 0,
    USB4_pathType_CONTROL,
    USB4_pathType_PCIE_IN,
    USB4_pathType_PCIE_OUT,
    USB4_pathType_DP_MAIN,
    USB4_pathType_DP_IN_AUX,
    USB4_pathType_DP_OUT_AUX,
    USB4_pathType_USB3_IN,
    USB4_pathType_USB3_OUT,
    USB4_pathType_HIA_IN,
    USB4_pathType_HIA_OUT,
//    USB4_pathType_HIA_IN_1,
//    USB4_pathType_HIA_OUT_1,
//    USB4_pathType_HIA_IN_2,
//    USB4_pathType_HIA_OUT_2,
    USB4_pathType_H2H_PCIE_IN,
    USB4_pathType_H2H_PCIE_OUT,
    USB4_pathType_H2H_DP_IN_AUX,
    USB4_pathType_H2H_DP_OUT_AUX,
    USB4_pathType_H2H_USB3_IN,
    USB4_pathType_H2H_USB3_OUT,
    USB4_pathType_MAX_VALUE
} USB4_pathType;

typedef struct
{
    BOOLEAN bValid;
    UINT32 HopID;    /**< Optional entry into the routing table of the adapter; 0 - default would not be modified */
    USB4_portType portType;
    usb4_pathN_cs pathCs;
} USB4_pathCsParamsType;

//struct USB4_usb3BandwidthParamsType {
//    BOOLEAN bValid;
//
//
//    // A Connection Manager needs to configure all of the Path Configuration Spaces for a USB
//    // Path before setting the Path Enable bit to 1b in the USB Adapters at either end of the Path.
//    base = m_coreBaseAddress + USB_ADAPTER_PORT_REG_BASE_OFFS;
//
//    // CM should write to the SCALE field. For device router this should be Hardwired to 0
//    HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_3_STANDARD, SCALE, 0x2);
//
//    // CM should write to Allocated bandwidth field for ISoC transfers. This field shall be hardwired to 0 for a Device Router
//    HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_2_STANDARD, ALLOCATED_DOWNSTREAM_BANDWIDTH, 0x1);
//    HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_2_STANDARD, ALLOCATED_UPSTREAM_BANDWIDTH, 0x1);
//}

typedef enum
{
    INVALID = 0,
    LANE_2_LANE,
    LANE_2_ADAPTER
} USB4_SEGMENT_TYPE_T;

typedef struct
{
  usb4_router_ctx_t* m_pRouters;

  /* Auxiliary data members */
  UINT32 m_routerIndex;
  UINT32 m_usb4DowstreamPortNumber;

  /* Path build time optimization */
  usb4_port_ctx_t* m_adapterPort;
  usb4_port_ctx_t* m_usb4DN;
  usb4_port_ctx_t* m_usb4UP;
  USB4_portType m_adapterPortType;

  /* Actual segment description */
  usb4_port_ctx_t* m_srcPort;
  usb4_port_ctx_t* m_dstPort;
  UINT32 m_egressHopID;
  UINT32 m_ingressHopID;
  UINT32 m_pathCreditsAllocated; /* Dedicated path credits */
  UINT32 m_linkCreditsAllocated; /* Shared Link credits */

  USB4_pathType m_pathType;
  BOOLEAN m_bDirectionOut;
  BOOLEAN m_bAux;

  /* These parameters are used on the srcPort configuration */
  usb4_pathN_cs pathCs;

  USB4_pathCsParamsType m_pathCsParamsOverride;
} usb4_path_segment_ctx_t;

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
 * @brief Configure path according to the allocated bandwidth
 * and hard-coded values
 * @param[in] pRoutingParameters - Entry to the routing table
 * @param[out] path - path CS data
 * @return 0 on success other on failure
 */
int Usb4PathSegmentFIllPathCs(usb4_path_segment_ctx_t* usb4_path_segment_ctx);

/**
 * @brief This function initializes object members
 * @param [in] pRouters - pointer to the array of routers in CM
 * @return 0 on success other on failure
 */
int Usb4PathSegmentInit(usb4_path_segment_ctx_t* usb4_path_segment_ctx, usb4_router_ctx_t* pRouters);

/**
 * @brief Allocate or update the path CS entry
 * @param[in] pRoutingParameters - Describe the path CS entry
 * port specific single entry
 * @return 0 on success other on failure
 */
int Usb4PathSegmentWriteSegmentToRouter(usb4_path_segment_ctx_t* usb4_path_segment_ctx);

/**
 * @brief Invalidate path segment on router
 * @return 0 on success other on failure
 */
int Usb4PathSegmentInvalidateSegment(usb4_path_segment_ctx_t* usb4_path_segment_ctx);

/**
 * @brief Identify adapter DN port that corresponds to the
 * USB4 DN port in this path
 * @param[in] pathSegmentIndex - path router index
 * @return 0 on success other on failure
 */
int Usb4PathSegmentFindAdapterDnPort(usb4_path_segment_ctx_t* usb4_path_segment_ctx);

/**
 * @brief Identify adapter ports that will participate in building routing segments
 * @param[in] pathSegmentIndex - path router index
 * @return 0 on success other on failure
 */
int Usb4PathSegmentIdentifySegmentActors(usb4_path_segment_ctx_t* usb4_path_segment_ctx);

/**
 * @brief Configure path segment from adapter DN
 * @return 0 on success other on failure
 */
int Usb4PathSegmentConfigureSegmentAdapterDN(usb4_path_segment_ctx_t* usb4_path_segment_ctx);

/**
 * @brief Configure path segment from adapter UP
 * @return 0 on success other on failure
 */
int Usb4PathSegmentConfigureSegmentAdapterUP(usb4_path_segment_ctx_t* usb4_path_segment_ctx);

/**
 * @brief Configure path segment between USB4 ports
 * @return 0 on success other on failure
 */
int Usb4PathSegmentConfigureSegmentLane2Lane(usb4_path_segment_ctx_t* usb4_path_segment_ctx);

/**
 * @brief Configure path segment according to actors
 * @return 0 on success other on failure
 */
int Usb4PathSegmentConfigureSegment(usb4_path_segment_ctx_t* usb4_path_segment_ctx, USB4_pathType pathType);

/**
 * @brief Set Enable bit in the adapter configuration space.
 * @param[in] enable - Enable/Disable segment
 * @return 0 on success other on failure
 */
int Usb4PathSegmentEnableSegment(usb4_path_segment_ctx_t* usb4_path_segment_ctx, BOOLEAN bEnable);

/**
 * @brief Get minimum number of free buffers available in USB4 Ports involved in a segment
 * @param[in] proposedCredits - Amount of credits proposed by specification
 * @param[in] proposedSharedBuffers - Amount of shared buffers proposed by specification
 * @return 0 on success other on failure
 */
int Usb4PathSegmentCalculateSegmentCredits(usb4_path_segment_ctx_t* usb4_path_segment_ctx, UINT32 proposedCredits, UINT32 proposedLinkCredits);

#endif /* _USB4_path_segment_H_ */
