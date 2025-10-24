/**---------------------------------------------------------------------------
 *   @file        usb4_router.h
 *
 *   @brief
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/
#ifndef __USB4_ROUTER_H_
#define __USB4_ROUTER_H_

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include "usb4_ctrl_iface.h"
// #include "VVHAL_usb4_comdef.h"
#include "usb4_port.h"
/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/
#define USB4_INVALID_TOPOLOGY_ID 0xFFFFFFFFFFFFFFFFUL
#define USB4_MAX_PORTS_PER_ROUTER (20)
#define USB4_POLL_RR_TIMEOUT_US (1000000)


typedef enum
{
    USB4_ROUTER_OPERATION_QUERY_DP_RESOURCE_AVAILABILITY    = 0x10,
    USB4_ROUTER_OPERATION_ALLOCATE_DP_RESOURCE              = 0x11,
    USB4_ROUTER_OPERATION_DE_ALLOCATE_DP_RESOURCE           = 0x12,
    USB4_ROUTER_OPERATION_NVM_WRITE                         = 0x20,
    USB4_ROUTER_OPERATION_NVM_AUTHENTICATE_WRITE            = 0x21,
    USB4_ROUTER_OPERATION_NVM_READ                          = 0x22,
    USB4_ROUTER_OPERATION_NVM_SET_OFFSET                    = 0x23,
    USB4_ROUTER_OPERATION_DROM_READ                         = 0x24,
    USB4_ROUTER_OPERATION_GET_NVM_SECTOR_SIZE               = 0x25,
    USB4_ROUTER_OPERATION_GET_PCIE_DOWNSTREAM_ENTRY_MAPPING = 0x30,
    USB4_ROUTER_OPERATION_GET_CAPABILITIES                  = 0x31,
    USB4_ROUTER_OPERATION_SET_CAPABILITIES                  = 0x32,
    USB4_ROUTER_OPERATION_BUFFER_ALLOCATION_REQUEST         = 0x33,
    USB4_ROUTER_OPERATION_BLOCK_SIDEBAND_PORT_OPERATIONS    = 0X34,
    USB4_ROUTER_OPERATION_UNBLOCK_SIDEBAND_PORT_OPERATIONS  = 0X35,
    USB4_ROUTER_OPERATION_GET_CONTAINER_ID                  = 0X36,
    USB4_ROUTER_OPERATION_VENDOR_SPECIFIC_ROUTER_OPERATIONS = 0xFFFF
} USB4_ROUTER_OPERATION;

#pragma pack(push)
#pragma pack(1)

typedef enum
{
    USB4_ROUTER_CAP_TMU = 0x3,
    USB4_ROUTER_CAP_VENDOR = 0x5,
} USB4_ROUTER_CAP;

typedef enum
{
    USB4_ROUTER_VSEC_CAP_1 = 0x1,
    USB4_ROUTER_VSEC_CAP_3 = 0x3,
    USB4_ROUTER_VSEC_CAP_4 = 0x4,
    USB4_ROUTER_VSEC_CAP_6 = 0x6,
} USB4_ROUTER_VSEC_CAP;

typedef struct
{
    struct
    {

        UINT32 NextCapabilityPointer:8;
        UINT32 CapabilityID:8;
        UINT32 FreqMeasurementWindow:11;
        UINT32 TimeDisruption_TD:1;
        UINT32 res1:2;
        UINT32 UniDirectionalCapability_UCAP:1;
        UINT32 InterDomainEnable_IDE:1;
    } TMU_RTR_CS_0;

    struct
    {
        UINT32 LocalTimeLow:32;
    } TMU_RTR_CS_1;

    struct
    {
        UINT32 LocalTimeMiddle:32;
    } TMU_RTR_CS_2;

    struct
    {
        UINT32 LocalTimeHigh:16;
        UINT32 TSPacketInterval:16;
    } TMU_RTR_CS_3;

    struct
    {
        UINT32 TimeOffsetFromGMLow :32;
    } TMU_RTR_CS_4;
        struct
    {
        UINT32 TimeOffsetFromGMHigh :32;
    } TMU_RTR_CS_5;
        struct
    {
        UINT32 TimeOffsetFromMasterLow :32;
    } TMU_RTR_CS_6;
    struct
    {
        UINT32 TimeOffsetFromMasterHigh :32;
    } TMU_RTR_CS_7;

    struct
    {
        UINT32 FreqOffsetFromGM :32;
    } TMU_RTR_CS_8;

    struct
    {
        UINT32 FreqOffsetFromMaster :32;
    } TMU_RTR_CS_9;

    struct
    {
        UINT32 PropagationDelayLow :32;
    } TMU_RTR_CS_10;

    struct
    {
        UINT32 PropagationDelayHigh :16;
        UINT32 resl: 16;
    } TMU_RTR_CS_11;

    struct
    {
        UINT32 ComputationTimeStampLow :32;
    } TMU_RTR_CS_12;
    struct
    {
        UINT32 ComputationTimeStampMiddle :32;
    } TMU_RTR_CS_13;

    struct
    {
        UINT32 ComputationTimeStampHigh :16;
        UINT32 res1: 16;
    } TMU_RTR_CS_14;

    struct
    {
        UINT32 FreqAvgConst :6;
        UINT32 DelayAvgConst:6;
        UINT32 OffsetAvgConst:6;
        UINT32 ErrorAvgConst:6;
        UINT32 TSInterDomainInterval:8;
    } TMU_RTR_CS_15;

    struct
    {
        UINT32 InterDomainTimeStampLow :32;
    } TMU_RTR_CS_16;

    struct
    {
        UINT32 InterDomainTimeStampMiddle :32;
    } TMU_RTR_CS_17;

    struct
    {
        UINT32 InterDomainTimeStampHigh :16;
        UINT32 res1:16;
    } TMU_RTR_CS_18;

    struct
    {
        UINT32 TimeOffsetFromInterDomainGMLow :32;
    } TMU_RTR_CS_19;

    struct
    {
        UINT32 TimeOffsetFromInterDomainGMHigh :32;
    } TMU_RTR_CS_20;

    struct
    {
        UINT32 TimeOffsetFromInterDomainGMLow :32;
    } TMU_RTR_CS_21;

    struct
    {
        UINT32 PostLocalTimeLow :32;
    } TMU_RTR_CS_22;

    struct
    {
        UINT32 PostLocalTimeHigh :32;
    } TMU_RTR_CS_23;

    struct
    {
        UINT32 PostTimeLow :32;
    } TMU_RTR_CS_24;

    struct
    {
        UINT32 PostTimeHigh :32;
    } TMU_RTR_CS_25;
} USB4_router_tmu_capability;

typedef struct
{
    // DW6
    UINT32 sleepReady_SLPR :1;
    UINT32 tbt3NotSupported :1;
    UINT32 wakeOnPCIeStat :1;
    UINT32 wakeOnUSBStat :1;
    UINT32 resCs6_1 :14;
    UINT32 usbHostControllerImplemented :1;
    UINT32 resCs6_2 :5;
    UINT32 routerReady :1;
    UINT32 configurationReady :1;
    UINT32 resCs6_3 :6;
} usb4_router_cs_6;

typedef struct
{
    struct
    {
        // DW0
        UINT32 vendorID :16;
        UINT32 productID :16;
    } ROUTER_CS_0;
    struct
    {
        // DW1
        UINT32 nextCapabilityPointer :8;
        UINT32 upstreamAdapter :6;
        UINT32 maxAdapter :6;
        UINT32 depth :3;
        UINT32 revisionNumber :8;
    } ROUTER_CS_1;
    struct
    {
        // DW2
        UINT32 topologyIdLow :32;
    } ROUTER_CS_2;
    struct
    {
        // DW3
        UINT32 topologyIdHigh :24;
        UINT32 resCs2 :7;
        UINT32 tolpologyIdValid :1;
    } ROUTER_CS_3;
    struct
    {
        // DW4
        UINT32 notificationTimeout :8;
        UINT32 cmUsb4Ver :8;
        UINT32 resCs3 :8;
        UINT32 usb4Version :8;
    } ROUTER_CS_4;
    struct
    {
        // DW5
        UINT32 enterSleep :1;
        UINT32 enableWakeonPCIe :1;
        UINT32 enableWakeonUSB3 :1;
        UINT32 enableWakeonDP :1;
        UINT32 resCs5 :19;
        UINT32 cmTbt3Support :1;
        UINT32 pcieTunnelingOn :1;
        UINT32 usb3TunnelingOn :1;
        UINT32 usbHostControllerOn :1;
        UINT32 resCs5_1 :4;
        UINT32 configurationValid :1;
    } ROUTER_CS_5;
    usb4_router_cs_6 ROUTER_CS_6;
//    These fields are present in USB4 router only, on TBT3 these addresses belong to TMU.
//    Therefore CM doesn't read them, until there is a need to do something with them.
//    struct
//    {
//        // DW7
//        UINT32 uuidHigh :32;
//    } ROUTER_CS_7;
//    struct
//    {
//        // DW8
//        UINT32 uuidLow :32;
//    } ROUTER_CS_8;
} usb4_router_cs;

//Starting with ROUTER_CS_9
typedef struct
{
    UINT32 data[16];
    UINT32 Metadata;
    struct
    {
        UINT32 Opcode    :16;
        UINT32 resCs26   : 8;
        UINT32 Status    : 6;
        UINT32 Error     : 1;
        UINT32 OpValid   : 1;
    }ROUTER_CS_26;
} usb4_router_operations_cs;


typedef struct
{
    UINT32 index0:16;
    UINT32 bufferAllocation0:16;
    UINT32 index1:16;
    UINT32 bufferAllocation1:16;
    UINT32 index2:16;
    UINT32 bufferAllocation2:16;
    UINT32 index3:16;
    UINT32 bufferAllocation3:16;
    UINT32 index4:16;
    UINT32 bufferAllocation4:16;
} usb4_buffer_allocation_request;


typedef struct
{
    UINT32 data[16];
    UINT32 metaData;
    USB4_ROUTER_OPERATION opcode;
    UINT8  status;
} usb4_router_operation_params;

typedef struct
{
    UINT32 nextCapabilityPointer :8;
    UINT32 capabilityID          :8;
    UINT32 VSEC_ID               :8;
    UINT32 VSEC_LENGTH           :8;
} usb4_router_VSEC_CS0_TYPE ;

typedef struct
{
    usb4_router_VSEC_CS0_TYPE VSEC_CS0;
    struct
    {
        UINT32 res_0                 :3;
        UINT32 plugEventDisable      :4;
        UINT32 res_1                 :(32-7);
    } VSEC_CS1;
} usb4_router_TBT3_VSEC1;

typedef struct
{
    struct
    {
        UINT32 nextCapabilityPointer :8;
        UINT32 capabilityID          :8;
        UINT32 VSEC_ID               :8;
        UINT32 VSEC_LENGTH           :8;
    } VSEC6_CS0;
    struct
    {
        UINT32 nextCapabilityPointer :16;
        UINT32 VSEC_LENGTH           :16;
    } VSEC6_CS1;
    struct
    {
        UINT32 usb4Ports             :4;
        UINT32 nextCapabilityPointer                 :4;
        UINT32 commonRegLen          :8; /* 0x14 for usb4 router - in DWORDS */
        UINT32 usb4PortRegLen        :12;/* 0x100 for usb4 router - in DWORDS, single USB4 port region size */
        UINT32 VSEC_LENGTH                 :4;
    }VSEC6_CS2;
} usb4_router_TBT3_VSEC6;

#pragma pack(pop)

typedef enum {
    INVALID_COMMAND = 0x0L,
    WRITE,
    READ,
    SET_DPR,
    CLEAR_DPR,
    SET_EWI,
    SET_IDD,
    READ_BE,
    SET_ENABLE_WAKE_EVENTS,
    SET_L0C,
    SET_L0D,
    SET_L1C,
    SET_L1D,
    SET_SLI,
    CLEAR_SLI,
    SET_SLP,
    SET_RS2,
    CLEAR_RS2,
    SET_RRS3,
    CLEAR_RRS3
} usb4_vse6_commands;

typedef struct
{
    UINT32 portNumber;
    UINT32 offsetDwords;
    UINT32 numDwords;
    usb4_vse6_commands command;
    UINT8* buff;    /* Provide pointer to read/write DWORDS to/from */
    UINT32* pNumberOfPorts; /* Provides a number of port regions in VSEC capability */
} usb4_router_access_vsec6;


typedef enum
{
    usb4_baReserved      = 0,
    usb4_baMaxUSB3       = 0x1,
    usb4_baMinDPaux      = 0x2,
    usb4_baMinDPmain     = 0x3,
    usb4_baMaxPCIe       = 0x4,
    usb4_baMaxHI         = 0x5
} usb4_buffer_allocation_index;

/* Supported modes for the TMU unit */
typedef enum
{
    USB4_TMU_MODE_NOT_SET,
    USB4_TMU_MODE_OFF,
    USB4_TMU_MODE_BI_DIRECTIONAL_HIFI,
    USB4_TMU_MODE_UNI_DIRECTIONAL_HIFI,
    USB4_TMU_MODE_UNI_DIRECTIONAL_LOW,

} USB4_tmu_mode;

/* Supported link configurations */
typedef enum
{
    USB4_CL0,
    USB4_CL0s,
    USB4_CL1,
    USB4_CL2,
} USB4_CLx_mode;

typedef enum
{
    USB4_TMU_PACKET_INTERVAL_OFF = 0,
    USB4_TMU_PACKET_INTERVAL_HIFI = 16,
    USB4_TMU_PACKET_INTERVAL_LOWRES = 1000,
} USB4_tmu_packet_interval;


typedef struct
{
    usb4_ctrl_iface_ctx_t* m_pControl;
    usb4_port_ctx_t m_Ports[USB4_MAX_PORTS_PER_ROUTER];

    /* Configuration space info */
    usb4_router_cs m_cs;
    UINT64 m_topologyID;
    BOOLEAN m_bEnumerationError;

    BOOLEAN m_bInterdomainRouter;

    BOOLEAN m_bPcieTunneling;
    BOOLEAN m_bUsb3Tunneling;
    BOOLEAN m_bDpTunneling;

    UINT32 m_displayPortAdapter;

    UINT32 m_baMaxUSB3;
    UINT32 m_baMinDPaux;
    UINT32 m_baMinDPmain;
    UINT32 m_baMaxPCIe;
    UINT32 m_baMaxHI;
    BOOLEAN m_bufferAllocationRequestSuceeded;

    /* Current mode of the router's TMU*/
    USB4_tmu_mode m_tmuCurrentMode;

    /* Cache uni-directional mode support */
    INT8 m_tmuCachedUniSupport;

    BOOLEAN m_configurationFileLoaded;

    BOOLEAN m_bDisableWakeOnConnect;
    BOOLEAN m_bDisableWakeOnDisconnect;
    BOOLEAN m_bDisableWakeOnUsb4;
    BOOLEAN m_bDisableWakeOnInterdomain;
} usb4_router_ctx_t;



/**
 * @brief This function initializes object members
 * @param [in] pControl - pointer to the control port interface
 * @return 0 on success other on failure
 */
int Usb4RouterInit(usb4_router_ctx_t* router_ctx, usb4_ctrl_iface_ctx_t* pControl);

#if 0 // TODO: AC check later to see if implemented
/**
 * @brief Reverse lanes
 * @return 0 on success other on failure
 */
int ConfigLaneReversal() {return 0;};//TODO: Implement

/**
 * @brief Configure router to work in a TBT3 mode
 * @return 0 on success other on failure
 */
int ConfigTBT3() {return 0;};//TODO: Implement

/**
 * @brief Configure rlink speed
 * @return 0 on success other on failure
 */
int ConfigGen3() {return 0;};//TODO: Implement
#endif

/**
 * @brief Returns pointer to a device adapter port
 * @param [in] type - Type of the port to search for
 * @param [in] startFromAdapter - Start search from this number
 * @return pointer to port, or NULL if not found
 */
usb4_port_ctx_t* Usb4RouterGetAdapterPortByType(usb4_router_ctx_t* router_ctx, USB4_portType type, UINT32 startFromAdapter);

/**
 * @brief Returns pointer to an interdomain port
 * @param [in] startFromAdapter - Start search from this number
 * @return pointer to port, or NULL if not found
 */
usb4_port_ctx_t* Usb4RouterGetInterdomainAdapter(usb4_router_ctx_t* router_ctx, UINT32 startFromAdapter);

/**
 * @brief Returns pointer to an un-configured device adapter port
 * @param [in] adapter - number of the adapter
 * @return pointer to port, or NULL if not found
 */
usb4_port_ctx_t* Usb4RouterGetAdapterPortByNumber(usb4_router_ctx_t* router_ctx, UINT32 adapter);


/**
 * @brief Returns number of router adapters
 * @return field from m_cs
 */
UINT32 Usb4RouterGetNumberOfAdapters(usb4_router_ctx_t* router_ctx);

/**
 * @brief Assign topology ID to router
 * @return 0 on success other on failure
 */
int Usb4RouterAssignTopologyID(usb4_router_ctx_t* router_ctx, UINT64 topologyID);

/**
 * @brief Get route parameter to be used on ctrl iface operations
 * @param [out] pRoute will hold the router topology id on success
 * @return 0 on success other on failure
 */
int Usb4RouterGetTopologyId(usb4_router_ctx_t* router_ctx, UINT64* pRoute);

/**
 * @brief Set route parameter for the following control port operations
 * @return 0 on success other on failure
 */
int Usb4RouterSetRoute(usb4_router_ctx_t* router_ctx);

/**
 * @brief Read configuration space
 * @return 0 on success other on failure
 */
int Usb4RouterReadCS(usb4_router_ctx_t* router_ctx);

/**
 * @brief Loads vendor specific settings to the router
 * @return 0 on success other on failure
 */
int Usb4RouterLoadVendorSettings(usb4_router_ctx_t* router_ctx);

/**
 * @brief Read through router's configuration space capabilities and until an ID matches
 * a requested capability. Read a single DWORD only
 * @param[in] capIdRequested - ID of the requested capability
 * @param[in] pCapLength - Length of the found capability
 * @return 0 on success other on failure
 */
int Usb4RouterSearchCapability(usb4_router_ctx_t* router_ctx, USB4_ROUTER_CAP capIdRequested, UINT32* pCapLength);

/**
 * @brief Read through router's configuration space capabilities and until an ID matches
 * a requested capability. Read a single DWORD only
 * @param[in] vsecCapIdRequested - ID of the requested capability
 * @param[in] pCapLength - Length of the found capability
 * @return 0 on success other on failure
 */
int Usb4RouterSearchVsecCapability(usb4_router_ctx_t* router_ctx, USB4_ROUTER_VSEC_CAP vsecCapIdRequested, UINT32* pCapLength, UINT32* pCapAddress);

/**
 * @brief Read a complete capability once SearchCapability() succeeded (mandatory)
 * @param[out] pBuff - Buffer to read the capability into (at least one dword)
 * @param[in] capSize - Buffer size
 * @return 0 on success other on failure
 */
int Usb4RouterReadCapability(usb4_router_ctx_t* router_ctx, UINT8* pBuff, UINT32 capSize);

/**
 * @brief Write capability to the same address as the one used in a previous read command
 * @param[in] pBuff - Buffer to write
 * @param[in] write_len - buffer length
 * @return 0 on success other on failure
 */
int Usb4RouterWriteCapability(usb4_router_ctx_t* router_ctx, UINT8* pBuff, UINT32 write_len);

/**
 * @brief Read configuration space
 * @return 0 on success other on failure
 */

#if 0 // TODO: AC unused
int Usb4RouterReadCS(usb4_router_ctx_t* router_ctx, UINT32 offset_dwords,
        UINT32 num_dwords,
        UINT64 timeout_ms,
        UINT8* buff);
#endif

/**
 * @brief Write configuration space
 * @return 0 on success other on failure
 */
int Usb4RouterWriteCS(usb4_router_ctx_t* router_ctx);

/**
 * @brief Write configuration space
 * @param [in] start_dword - Write starting from DWORD
 * @param [in] number_of_dwords - Write number of DWORDS
 * @return 0 on success other on failure
 */
int Usb4RouterWriteCSDword(usb4_router_ctx_t* router_ctx, UINT32 start_dword, UINT32 number_of_dwords);

/**
 * @brief Write configuration space
 * @param [in] start_dword - Write starting from DWORD
 * @param [in] number_of_dwords - Write number of DWORDS
 * @param [in] pBuff - Data to write
 * @return 0 on success other on failure
 */
int Usb4RouterWriteCSData(usb4_router_ctx_t* router_ctx, UINT32 start_dword, UINT32 number_of_dwords, UINT8* pBuff);

/**
 * @brief Poll for specific mask being set
 * @param [in] usTimeout - Operation timeout (usec)
 * @param [in] mask - bit mask to test
 * @return 0 on success other on failure
 */
int Usb4RouterPollCS_6_Mask(usb4_router_ctx_t* router_ctx, UINT64 usTimeout, UINT32 mask);

/**
 * @brief Poll for router ready bit
 * @param [in] usTimeout - Operation timeout (usec)
 * @return 0 on success other on failure
 */
int Usb4RouterPollRR(usb4_router_ctx_t* router_ctx, UINT64 usTimeout);

/**
 * @brief Poll for configuration ready bit
 * @param [in] usTimeout - Operation timeout (usec)
 * @return 0 on success other on failure
 */
int Usb4RouterPollCR(usb4_router_ctx_t* router_ctx, UINT64 usTimeout);

/**
 * @brief Checks if router is enumerated
 * @return TRUE if enumerated, FALSE otherwise
 */
BOOLEAN Usb4RouterIsEnumerated(usb4_router_ctx_t* router_ctx);

/**
 * @brief Poll for sleep ready bit
 * @param [in] usTimeout - Operation timeout (usec)
 * @return 0 on success other on failure
 */
int Usb4RouterPollSLRP(usb4_router_ctx_t* router_ctx, UINT64 usTimeout);

/**
 * @brief Enumerate router
 * @return 0 on success other on failure
 */
int Usb4RouterEnumerate(usb4_router_ctx_t* router_ctx);

/**
 * @brief Enumerate ports of the router
 * @return 0 on success other on failure
 */
int Usb4RouterEnumeratePorts(usb4_router_ctx_t* router_ctx);

/**
 * @brief Execute Buffer Allocation Request - this is optionally supported command
 * which impacts buffer allocations during path construction
 * @return 0 on success other on failure
 */
int Usb4RouterGetBufferAllocations(usb4_router_ctx_t* router_ctx);

/**
 * @brief Bond USB4 lane0 and lane1, or disable lane1; Unlock primary port.
 * @param[in] adapter_first, adapter_second - adapters that got hot plug event
 * @return 0 on success other on failure
 */
int Usb4RouterBondLanes(usb4_router_ctx_t* router_ctx, UINT32 adapter_first, UINT32 adapter_second);

/**
 * @brief Check if port is primary and bonded
 * @param[in] adapter - adapters to check
 * @return 0 on success other on failure
 */
BOOLEAN Usb4RouterIsBonded(usb4_router_ctx_t* router_ctx, UINT32 adapter);

/**
 * @brief Validate that specific DFP pair is connected (in CL0 or valid LPM)
 * and can handle control transfers at least
 * @param[in] adapter - adapter of the DFP pair (or single)
 * @param[out] bConnected - true if the DFP is connected
 *
 * @return 0 on success other on failure
 */
int Usb4RouterDfpConnected(usb4_router_ctx_t* router_ctx, UINT32 adapter, BOOLEAN* bConnected);

/**
 * @brief Validate that specific DFP pair is in CL0
 * and can handle control transfers at least
 * @param[in] adapter - adapter of the DFP pair (or single)
 * @param[out] connected - true if the DFP is in CL0
 *
 * @return 0 on success other on failure
 */
int Usb4RouterDfpInCL0(usb4_router_ctx_t* router_ctx, UINT32 adapter, BOOLEAN* bInCL0);

/**
 * @brief Handle disconnect on the specific adapter port
 * @param[in] adapter - adapter number that got disconnect request
 *
 * @return 0 on success other on failure
 */
int Usb4RouterDisconnectAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter);

/**
 * @brief Handle Lane enable on the specific adapter port
 * @param[in] adapter - adapter number that got disconnect request
 *
 * @return 0 on success other on failure
 */
int Usb4RouterReconnectAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter);

/**
 * @brief Handle reset on the specific adapter port
 * @param[in] adapter - adapter number that got disconnect request
 *
 * @return 0 on success other on failure
 */
int Usb4RouterResetAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter);

/**
 * @brief Handle hot plug on the specific adapter port
 * which is not USB4 port
 * @param[in] adapter - adapter number that got disconnect request
 *
 * @return 0 on success other on failure
 */
int Usb4RouterAdapterHotPlug(usb4_router_ctx_t* router_ctx, UINT32 adapter, UINT32 unplug_flag);

/**
 * @brief Unlock the specific adapter port
 * @param[in] adapter - adapter number that got disconnect request
 *
 * @return 0 on success other on failure
 */
int Usb4RouterUnlockAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter);

/**
 * @brief Mark port as leading to topological loop. Will not be used in a path
 * @param[in] adapter - adapter number that got disconnect request
 *
 * @return 0 on success other on failure
 */
int Usb4RouterLoopingTopologyAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter);

/**
 * @brief Mark port as interdomain (or not); Set interdomain bit to 1 (or 0).
 * @param[in] adapter - adapter number that got disconnect request
 * @param[in] isInterdomain - Is/Is not inter-domain
 *
 * @return 0 on success other on failure
 */
int Usb4RouterInterdomainAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter, BOOLEAN isInterdomain);

/**
 * @brief Return port type - to control the logic of hot-plug handling
 * @param[in] adapter - adapter number that got disconnect request
 *
 * @return 0 on success other on failure
 */
USB4_portType Usb4RouterGetPortType(usb4_router_ctx_t* router_ctx, UINT32 adapter);

/**
 * @brief Enable PCIE tunneling by a device router
 * @return 0 on success other on failure
 */
int Usb4RouterEnablePcieTunneling(usb4_router_ctx_t* router_ctx);

/**
 * @brief Enable USB3 tunneling by a device router
 * @return 0 on success other on failure
 */
int Usb4RouterEnableUsb3Tunneling(usb4_router_ctx_t* router_ctx);

/**
 * @brief Set configuration valid bit of the device router,
 * and polls for configuration ready
 * @return 0 on success other on failure
 */
int Usb4RouterSetConfigurationValid(usb4_router_ctx_t* router_ctx);

/**
 * @brief Set timeout in ms for hotplug events and notifications,
 * @return 0 on success other on failure
 */
int Usb4RouterSetNotificationTimeout(usb4_router_ctx_t* router_ctx, UINT8 timeout);

/**
 * @brief Issue router command and wait for completion
 * @param [in] routerOperation - Structure which will contain router operation
 *                               and return values
 * @param [in] msTimeout - Timeout after which the function will fail
 * @return 0 on success other on failure
 */
int Usb4RouterIssueCommand(usb4_router_ctx_t* router_ctx, usb4_router_operations_cs* routerOperation, UINT64 usTimeout);

/**
 * @brief Instruct router to issue a router Operation
 * @param [in] operationData - struct that contain data metadata and opcode
 * @return 0 on success other on failure
 */
int Usb4RouterIssueRouterOperation(usb4_router_ctx_t* router_ctx, usb4_router_operation_params* routerOperation, UINT64 usTimeout);

/**
 * @brief check DP source is available to be allocated using router oprations
 * @param [in] dpNumber - adapter number to get his DP resources status
 * @return 0 on success other on failure
 */
int Usb4RouterQueryDpResource(usb4_router_ctx_t* router_ctx, UINT32 dpNumber);

/**
 * @brief allocate or deallocate DP resouces
 * @param [in] dpNumber - adapter number to allocate its DP resources
 * @param [in] allocate - true = allocate, false = deallocate
 * @return 0 on success other on failure
 */
int Usb4RouterAllocateDeAllocateDpResource(usb4_router_ctx_t* router_ctx, UINT32 dpNumber, BOOLEAN allocate);

/**
 * @brief Instruct router to enter sleep on sleep event
 * @return 0 on success other on failure
 */
int Usb4RouterPrepareSleep(usb4_router_ctx_t* router_ctx);

/**
 * @brief Check router is ready to enter sleep on sleep event
 * @return 0 on success other on failure
 */
int Usb4RouterCheckSleepReady(usb4_router_ctx_t* router_ctx);

/**
 * @brief Set EnterSleep bit and wake sources bits
 * @return 0 on success other on failure
 */
int Usb4RouterSetEnterSleep(usb4_router_ctx_t* router_ctx);

/*---------------------------------------------------------------------------*/
/**
 * @brief Write dword sequnce to router
 * @param fnmae[in] file name of the file to load
 * @return 0 on success other on failure
 */
/*---------------------------------------------------------------------------*/
int Usb4RouterWriteFileToRouter(usb4_router_ctx_t* router_ctx, const char* fname);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Set the current mode of the router's TMU unit
 *  @param mode the requested mode of operation
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUSetMode(usb4_router_ctx_t* router_ctx, USB4_tmu_mode mode);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Get the current mode of the router's TMU unit
 *  @param pMode[out] Pointer to the returned mode
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUGetCurrentMode(usb4_router_ctx_t* router_ctx, USB4_tmu_mode *pMode);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Check if the router supports working in uni-directional mode
 *  @param pIsSupported[out] Pointer to the query result
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUCheckUniModeSupported(usb4_router_ctx_t* router_ctx, BOOLEAN *pIsSupported);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Set the router's local time
 *  @param localTime local time value to set in nano seconds
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUPostLocalTime(usb4_router_ctx_t* router_ctx, UINT64 localTime);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Get the router's local time
 *  @param pNanoSeconds[out] number of whole nanoseconds.
 *  @param pFractionalNanoSeconds[out] number of fractional nanoseconds.
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUGetLocalTime(usb4_router_ctx_t* router_ctx, UINT64* pNanoSeconds, UINT16* pFractionalNanoSeconds);

/*---------------------------------------------------------------------------*/
/**
 *  @brief enables or disables unidirecctional mode for the given port
 *  @param lane0Number the lane0 of the target port
 *  @param enabled enable/disable setting
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUSetPortUnidirectionalMode(usb4_router_ctx_t* router_ctx, UINT32 lane0Number, BOOLEAN enabled);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Enables/Disable interdomain operat
 *  @param enable requested insterdomain state
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUEnableInterdomain(usb4_router_ctx_t* router_ctx, BOOLEAN enable);

/*---------------------------------------------------------------------------*/
/**
 *  @brief set the freuqncy divider for interdomain packets.
 *  The provided value is used with TSPacketInterval settings using
 *  the formula (TSInterDomainInterval + 1) * TSPacketInterval to produce
 *  the new interval
 *  @param interval requested insterdomain state
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUSetInterdomainInterval(usb4_router_ctx_t* router_ctx, UINT32 TSInterDomainInterval);

/*---------------------------------------------------------------------------*/
/**
 * @brief Disable/Enable time sync on the connected ports
 * @param[in] bEnable - Enable/Disable of time sync
 * @return 0 on success other on failure
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUTimeSync(usb4_router_ctx_t* router_ctx, BOOLEAN enabled);

/*---------------------------------------------------------------------------*/
/**
 * @brief Set all interdomain ports as TMU master ports
 * @return 0 on success other on failure
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUSetAllInterdomainPortsAsMaster(usb4_router_ctx_t* router_ctx);

/*---------------------------------------------------------------------------*/
/**
 * @brief Set all interdomain ports as TMU slave ports
 * @return 0 on success other on failure
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUSetAllInterdomainPortsAsSlave(usb4_router_ctx_t* router_ctx);

/**
 *  @brief Perform command on the specific port within VSEC6 capability
 *  @param[in/out]  pAccessVsec6 - struct that defines the address and action
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterVsec6AcceessPort(usb4_router_ctx_t* router_ctx, usb4_router_access_vsec6* pAccessVsec6);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Request to enable/disable RSFEC during link establishment
 * @param[in] bDisableRsFec - Request to disable / enable RS FEC
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterConfigureRequestRsFec(usb4_router_ctx_t* router_ctx, BOOLEAN bDisableRsFec);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Limit link speed to Gen2 during link establishment
 *  @param[in] bLimitToGen2 - True - limit to Gen2, False - Return to Gen3
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterLimitTargetLinkSpeedToGen2(usb4_router_ctx_t* router_ctx, BOOLEAN bLimitToGen2);

/**
 *  @brief Verifies the current negotiated link width/speed are as expected
 *  @return 0 on success other when link is not as expected or failure
 */
int Usb4RouterVerifyLinkSpeedWidth(usb4_router_ctx_t* router_ctx);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Limit link to single lane
 *  @param[in] bLimitToSingleLane - True - limit, False - Use both lanes
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterLimitToSingleLane(usb4_router_ctx_t* router_ctx, BOOLEAN bLimitToSingleLane);

/*---------------------------------------------------------------------------*/
/**
*  @brief Enable one or two lanes
*  @param[in] bLimitToSingleLane - True - limit, False - Use both lanes
*  @return 0 on success
*---------------------------------------------------------------------------*/
int Usb4RouterEnableLanes(usb4_router_ctx_t* router_ctx, BOOLEAN bLimitToSingleLane);


/*---------------------------------------------------------------------------*/
/**
 * @brief Configure CLx mode of the domain - impacts entry to low power link states
 * @param[in] CLxMode - Maximum low power mode to configure
 * @return 0 on success other on failure
 *---------------------------------------------------------------------------*/
int Usb4RouterConfigureCLx(usb4_router_ctx_t* router_ctx, USB4_CLx_mode CLxMode);

/*---------------------------------------------------------------------------*/
/**
 * @brief Check the possibility to configure CLx mode of the domain on all ports
 * @param[in] CLxMode - Maximum low power mode to configure
 * @param[out] pbIncompatible - If TRUE, indicates that configuration can't be applied
 * @return 0 on success other on failure
 *---------------------------------------------------------------------------*/
int Usb4RouterCheckCLxCompatibility(usb4_router_ctx_t* router_ctx, USB4_CLx_mode CLxMode, BOOLEAN* pbIncompatible);

/*---------------------------------------------------------------------------*/
/**
 * @brief Set the provided port to be interdomain master port
 * @param[in] lane0AdapterNumber - lane0 of the port
 * @return 0 on success other on failure
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUAssignInterdomainMasterPort(usb4_router_ctx_t* router_ctx, UINT32 lane0AdapterNumber);

/*---------------------------------------------------------------------------*/
/**
 * @brief Set the provided port to be interdomain slave port
 * @param[in] lane0AdapterNumber - lane0 of the port
 * @return 0 on success other on failure
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUAssignInterdomainSlavePort(usb4_router_ctx_t* router_ctx, UINT32 lane0AdapterNumber);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Notifies the system the time is not reliable. Must be called before:
 *
 *       * TMU mode changes (TSPacketInterval,
 *                Direction, Filters, Frequency Measurement Window)
 *       * Inter-Domain time sync is enabled
 *       * Time Posting is applied
 *  @param enable enable / disable time disruption
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUSetTimeDisruption(usb4_router_ctx_t* router_ctx, BOOLEAN enable);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Set the router's transmission interval
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUSetRate(usb4_router_ctx_t* router_ctx, USB4_tmu_packet_interval interval);

/*---------------------------------------------------------------------------*/
/**
 *  @brief Set the router's handshake type
 *  @return 0 on success
 *---------------------------------------------------------------------------*/
int Usb4RouterTMUSetRouterUnidirectionalMode(usb4_router_ctx_t* router_ctx, BOOLEAN enableUnidirectionalMode);

#endif /* __USB4_ROUTER_H_ */
