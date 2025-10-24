/**---------------------------------------------------------------------------
 *   @file        usb4_cm.h
 *
 *   @brief   Header file for a Connection Manager
 *
 *   Copyright (c) 2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/


#ifndef __USB4_CM_H_
#define __USB4_CM_H_

#include "usb4_port.h"
#include "usb4_HIA.h"
#include "usb4_ctrl_iface.h"
#include "usb4_platform_defs.h"
// #include "VVHAL_usb4_comdef.h"
#include "usb4_qdrv.h"
// #include "VVDRV_usb4_pd.h"
#include "usb4_router.h"
// #include "VVDRV_usb4_path_segment.h"
// #include "VVDRV_usb4_path.h"
#include "usb4_path_manager.h"
#include "usb4_drv_subsystem.h"
// #include "VVDRV_usb4_power_manager.h"

/*----------------------------------------------------------------------------
 * Defines
 *--------------------------------------------------------------------------*/

//TODO: Validate the value with Yiftah
#define USB4_MAX_INTERVAL_BETWEEN_HOT_PLUG_EVENTS (500) /**< If training is going to succeed, it should be time bound */
#define USB4_MAX_BONDING_RETRIES (3)

/*----------------------------------------------------------------------------
 * Type Definitions
 *--------------------------------------------------------------------------*/

/** @brief Parameters to the driver open function */
typedef struct
{
    UINT32 coreIndex;                   /**< USB4 Core Index */
    USB4_DRV_SUBSYSTEM ss;               /**< subsystem */

    BOOLEAN bPollingMode;               /**< TRUE/FALSE Polling/Interrupt mode. */
    BOOLEAN bUseTBT3Mode;               /**< TRUE/FALSE Configure PHY into TBT3 mode */
    BOOLEAN bEnumerateLocalRouterOnly;  /**< TRUE/FALSE driver mode for the unconnected core; If TRUE: Don't wait for hot plug events, since there wouldn't be any*/
    BOOLEAN bUseRealPD;                 /**< TRUE/FALSE use real physical PD HW; If TRUE, use PD, Else: Specify that USB4 cable is already connected. No detection operation. */
    BOOLEAN bToggleTypeC;               /**< TRUE/FALSE When using real PD, issue this toggle to disconnect/reconnect cable
                                             Can be used instead of bUseRealPD, in a H2H scenario*/
    UINT64  controlPacketsTimeout_ms;   /**< msec duration to poll for control packets; If 0: allow immediate exit from VVDRV_usb4_container_open. Control packets will be handled later.
                                             If not 0, handle control packets for the duration.*/
    UINT32 numLanes;                    /**< number of phy lanes, 1 or 2 */
    BOOLEAN bDisableRS_FEC;             /**< RS FEC Disable (Enabled POR) for Gen2 and 3 */
    BOOLEAN bLimitToGen2;               /**< Limit attempted link establishment speed to Gen2 */
    UINT32  tmuMode;                    /**< Choose between USB4_TMU_MODE_NOT_SET (=0) (No impact - default operating mode, equal to USB4_TMU_MODE_BI_DIRECTIONAL_HIFI),
                                                            USB4_TMU_MODE_OFF (=1),
                                                            USB4_TMU_MODE_BI_DIRECTIONAL_HIFI (=2),
                                                            USB4_TMU_MODE_UNI_DIRECTIONAL_HIFI (=3),
                                                            USB4_TMU_MODE_UNI_DIRECTIONAL_LOW (=4) */
    BOOLEAN bPCIeEP;                    /**< If true, configure PCIe AP as EP */
    BOOLEAN bUSB3Device;                /**< If true, configure USB3 AP as device */
    BOOLEAN bSkipH2HHIArings;           /**< If true, SkipH2HHIA Rings */
    BOOLEAN bForceOpen;                 /**< If true, Force openning instead of return current opened ... */

    // +++ Deprecated
    BOOLEAN bUSB3DriverLoaded;          /**< If true, build USB3 path, and update PM that initialization done from this SS */
    BOOLEAN bPCIeDriverLoaded;          /**< If true, build PCIe path, and update PM that initialization done from this SS  */
    BOOLEAN bDPDriverLoaded;            /**< If true, build DP path, and update PM that initialization done from this SS  */
    BOOLEAN bUSB4DriverLoaded;          /**< If true, update PM that initialization done from USB4 test  */
    // --- Deprecated
} USB4_cfgParams_t;

/** @brief Parameters to the ioctl function */
typedef enum
{
    USB4_IOCTL_QUERY_NUMBER_OF_INTERDOMAIN_ROUTERS,
    USB4_IOCTL_SEND_HOT_PLUG_TEST_PACKET,
    USB4_IOCTL_CONFIGURE_INTERDOMAIN_ADAPTER_PATH,
} USB4_ioctl_actions_t;

typedef struct
{
    UINT32 interdomainRouterIndex; /**< [In] Inter-domain router index - 0 to count of interdomain routers - 1 */
    UINT32 interdomainAdapterIndex; /**< [In] Inter-domain adapter index within a specific router - 0 to count of interdomain adapters - 1
                                         TODO: Add query to find out max interdomain adapters within a specific router */
    UINT32 ifaceIndex; /**< [In] Host interface index - 0 or 1 */
    BOOLEAN bRawMode;   /**< [In] Raw or Frame mode */
} USB4_host_iface_config_t;

typedef struct
{
    USB4_ioctl_actions_t ioctl;     /**< USB4 IOCTL */
    UINT8* in_data;                  /**< [in] pointer to input data */
    UINT32 in_size;                 /**< [in] size of input data buffer */
    UINT8* out_data;                 /**< [out] pointer to output data */
    UINT32 out_size;                /**< [out] size of output data buffer */
} USB4_ioctl_t;

#pragma pack(push)
#pragma pack(1)

typedef enum
{
    USB4_CM_EVENT_HPE = 0,
    USB4_CM_EVENT_NOTIFICATION = 1,
    USB4_CM_EVENT_SM_TRANSITION = 2,
    USB4_CM_EVENT_CONTROL_ADAPTER_FAIL = 3,
    USB4_CM_EVENT_WAKE_ISR = 4,
} USB4_cm_event_type;

typedef struct
{
    UINT8 router_index;
    UINT8 adapter_number;
    USB4_cm_event_type eventType;
    union 
    {
        USB4_hotplug_state hpState;
        USB4_HPE_parsed hpParsed;
        USB4_cpNotificationEvent notificationEvent;
        UINT8 raw;
    } event;
} USB4_cm_event;

#pragma pack(pop)

typedef struct
{
    /* For inter-domain protocol */
    UINT32 interdomainRetries;
    UINT64 interdomainTopologyID;
    UINT32 remoteUUID[4];
    usb4_interdomain_link_state_status_response_t lssr;
    usb4_interdomain_link_state_change_response_t lscr;
} USB4_cm_interdomain_data_t;


#define USB4_MAX_CM_LOGGER_EVENTS 100

typedef struct
{
    USB4_HPE_parsed hotplugState;
    UINT8 router;
    UINT8 adapter;
} USB4_cm_hotlug_event_params;


typedef struct
{
    // Circular Reference usb4_cm_ctx_t* m_pCm;
    void* m_pCm; // Cast to usb4_cm_ctx_t* within the C file
    USB4_cm_event m_cmEvents[USB4_MAX_CM_LOGGER_EVENTS];
    UINT32 m_prevFreeIndex; /* To see if the logger is idle */
    UINT32 m_freeIndex;
    UINT32 m_printIndex;
} usb4_cm_logger_ctx_t;



// +++++++++++++ Usb 4 CM Logging
int Usb4CmLoggerLockMutex(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx);
int Usb4CmLoggerUnlockMutex(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx);

int Usb4CmLoggerIsIdle(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, BOOLEAN* bIdle);
int Usb4CmLoggerInit(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, void* pCm, UINT8 coreIndex);
int Usb4CmLoggerDeInit(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx);
int Usb4CmLoggerStoreEvent(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, USB4_cm_event_type type);
int Usb4CmLoggerStoreHotPlugStateMachineState(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx);
int Usb4CmLoggerStoreHpe(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx);
int Usb4CmLoggerStoreNotification(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx);
int Usb4CmLoggerPrintEvents(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, BOOLEAN bResetLogger);
int Usb4CmLoggerFindTransition(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, USB4_cm_event* pEvent, UINT32* pIndex);
int Usb4CmLoggerReset(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx);
UINT32 Usb4CmLoggerGetCoreIndex(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx);

/**
 * @brief Count number of hot plug/unplug events 
 * @param USB4_cm_hotlug_event_params hotplug event description
 * @param counter [out] - pointer to event counter
 * @return 0 on success 
 */
int Usb4CmLoggerCountHotplugEvent(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, USB4_cm_hotlug_event_params* pParams, UINT32* pCounter);

/**
 * @brief Find an event of a given type 
 * @param type  the event type to search for
 * @param pEvent [out] - pointer to event
 * @param ptartFromIndex [in/out] the first index to search,
 *                        updated to the last found index
 * @return 0 on success 
 */
int Usb4CmLoggerFindEventByType(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, USB4_cm_event_type type, USB4_cm_event* pEvent, UINT32* pStartFromIndex);
int Usb4CmLoggerPrintUcEvents(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx);
// ------------- Usb 4 CM Logging



typedef struct
{
    UINT32 WakeonConnectStatus    ;
    UINT32 WakeonDisconnectStatus ;
    UINT32 WakeonUSB4WakeStatus   ;
    UINT32 WakeonInterDomainStatus;
} usb4_cm_wake_reason;

/* For USB4_cm_quirk - Mask to specify HS establishment modifiers */
typedef enum /* This is a bitmask */
{
    USB4_CM_QUIRK_DISABLE_HPE_L0   = 0x1,
    USB4_CM_QUIRK_DISABLE_HPE_L1 = 0x2,
    USB4_CM_QUIRK_DISABLE_HPE_DPIN = 0x4,
    USB4_CM_QUIRK_DISABLE_WAKE_ON_CONNECT = 0x10,
    USB4_CM_QUIRK_DISABLE_WAKE_ON_DISCONNECT = 0x20,
    USB4_CM_QUIRK_DISABLE_WAKE_ON_USB4_EVENT = 0x40,
    USB4_CM_QUIRK_DISABLE_WAKE_ON_INTERDOMAIN = 0x80,
    // free for new quirk USB4_CM_QUIRK_REGISTER_PD_INTERRUPT = 0x100,
    USB4_CM_QUIRK_REGISTER_PD_INTERRUPT = 0x100,
    USB4_CM_QUIRK_ERR_PLUG_IS_FATAL_NO_RETRY = 0x200,
    USB4_CM_QUIRK_RELAXED_DISCONNECT_DETECTION = 0x400,
    USB4_CM_QUIRK_MEASURE_HEC_ERRORS_RATE=0x800
} USB4_cm_quirk;

/*----------------------------------------------------------------------------
 * Connection Manager
 *--------------------------------------------------------------------------*/

typedef struct
{
    const USB4_cfgParams_t* m_pParams;

    UINT8* m_pHI_Base;
    usb4_hia_ctx_t m_HIA;
    usb4_ctrl_iface_ctx_t m_control;

    UINT32 m_router_index;/**< select router for undergoing operations */
    usb4_router_ctx_t m_routers[USB4_MAX_SUPPORTED_ROUTERS];
    USB4_hotplug_t* m_pHotplug; /**< Hotplug parameters, allow implementing state
                                   machine for handling packets from 2 lanes */
    UINT32 m_localUUID[4];
    USB4_cm_interdomain_data_t m_interdomainData;

    usb4_path_manager_ctx_t m_path_manager;
    BOOLEAN m_bUsePollingForControlPackets;

    BOOLEAN m_bCmTreadLocked;

    USB4_tmu_mode m_domainTmuMode;

    BOOLEAN m_bInitialized;

    BOOLEAN m_bWakeInterruptHappened;
    usb4_cm_wake_reason m_wakeReason;

    usb4_qdrv_ctx_t* m_pQdrv;
    USB4_PD_INFO m_pdInfo;
    usb4_cm_logger_ctx_t m_logger;
    
    // friend class VVDRV_usb4_cm_logger;

    /* Testing extension */
    UINT32 m_quirks; /* Mask buit of of USB4_cm_quirk */

    // ControlPacketHandler Additional Parameters
    BOOLEAN m_bYieldControl;
    BOOLEAN m_pbIdle;
} usb4_cm_ctx_t;


/* Testing extension */
int Usb4CmPreHostRouterEnumeration(usb4_cm_ctx_t* usb4_cm_ctx);
int Usb4CmPreHsEstablishment(usb4_cm_ctx_t* usb4_cm_ctx);



/**
 * @brief This function constructs all the dynamically allocated objects
 * @param[in] pParams - Configure CM instance behaviour
 * @return 0 on success other on failure
 */
int Usb4CmInit(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 coreId);

/**
 * @brief This function destroys all the dynamically allocated objects
 * @return 0 on success other on failure
 */
int Usb4CmDeInit(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Reset the Host Interface registers and the
 * E2E flow control counters to their default values.
 * Also Re-initialize all the rings
 * @return 0 on success, other on failure
 */
int Usb4CmResetHostInterface(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function processes all incoming control packerts;
 * @param[in] bYieldControl - Don't process all accumulated packets, but allow some other code to execute.
 * 			Use it when running two state machines in a loop in a single thread.
 * @param[in] pbIdle - Indication if there are packets to process
 * @return 0 on success, other on failure
 */
int Usb4CmControlPacketHandler(usb4_cm_ctx_t* usb4_cm_ctx); // BOOLEAN bYieldControl, BOOLEAN* pbIdle absorbed into usb4_cm_ctx

/**
 * @brief This function configures HW and SW to be able to accept Hot Plug events
 * @return 0 on success, other on failure
 */
int Usb4CmEnable(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function disables previous enablment
 * @return 0 on success, other on failure
 */
int Usb4CmDisable(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function updates the driver to operate in proper CFG
 * This function may be called at any time, it will read the configuration parameters from the container and
 * apply the changes
 * @return 0 on success, other on failure
 */
int Usb4CmConfig(usb4_cm_ctx_t* usb4_cm_ctx, const USB4_cfgParams_t* pParams);

// +++ Deprecated
/**
 * @brief This function attempts to establish a HS connection,
 *        enumerates local router and
 *        handles control packets, with timeout.
 * @return 0 on success, other on failure
 */
int Usb4CmHandleHostRouterCableConnect(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 msTimeout, const USB4_PD_INFO* pInfo);
// --- Deprecated

/**
 * @brief This function requests that all enumerated routers enter sleep.
 * @return 0 on success, other on failure
 */
int Usb4CmPrepareSleep(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function puts host router to sleep
 * @return 0 on success, other on failure
 */
int Usb4CmActivateSleep(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function wakes router from sleep'
 * @param[in] wakeStage - stage to perform
 * @param[in] reason - uC need to know who woke the system
 * @return 0 on success, other on failure
 */
int Usb4CmWake(usb4_cm_ctx_t* usb4_cm_ctx, USB4_cm_wake_stage_type wakeStage, USB4_uc_wake_reason reason);

/**
 * @brief This function aggregates multiple CM calls to create a complete flow
 * @param[in] reason - uC need to know who woke the system
 * @return 0 on success, other on failure
 */
int Usb4CmWakeFlow(usb4_cm_ctx_t* usb4_cm_ctx, USB4_uc_wake_reason reason);

/**
 * @brief Allow clients to communicate with CM
 * @param[in/out] driver_ioctl - Struct that describes the action and returns result
 * @return 0 on success other on failure
 */
int Usb4CmIoctl(usb4_cm_ctx_t* usb4_cm_ctx, USB4_ioctl_t* pIoctl);

/**
 * @brief Get reference to the control interface
 * @return reference to a control interface
 */
usb4_ctrl_iface_ctx_t* Usb4CmControl(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Get reference to the path manager
 * @return reference to a path manager
 */
usb4_path_manager_ctx_t* Usb4CmPathManager(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Get reference to HIA
 * @return reference to HIA
 */
usb4_hia_ctx_t* Usb4CmHIA(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Get the matching router
 * @param [in] idx is the router index
 * @param [out] ppRouter holds a valid pointer in case of success
 * @return 0 on success other on failure
 */
int Usb4CmGetRouterByIdx(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 idx, usb4_router_ctx_t** ppRouter);

/**
 * @brief Update current router index to be router with specified topology
 * @param[in] router_topologyID
 * @return 0 on success other on failure
 */
int Usb4CmFindRouterByTopology(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 router_topologyID);

/**
 * @brief Inform CM of the cable status change (Connect or disconnect)
 * @param [in] pInfo PD information, see #USB4_pd_info for details
 * @return 0 on success other on failure
 */
int Usb4CmNotifyUsb4CableEvent(usb4_cm_ctx_t* usb4_cm_ctx, const USB4_PD_INFO* pInfo);

/**
 * @brief Waits for state machine to proceed while control packets are sent
 *        and received. function will stop after timeout_ms or if 
 *        no new packet is received/sent for maxidle_ms
 *        function is required to be called whenever we want to make sure
 *        the state machine is completed
 * @param [in] timeout_ms maximum time to run the checks loop
 * @param [in] maxidle_ms premature exit in case there are no packets for
 *                        this amount of time (which indicates we are idle)
 * @return 0 on success other on failure
 */
int Usb4CmWaitForHostConnectStateMachine(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 timeout_ms, UINT32 maxidle_ms);

/**
 * @brief Get reference to the router which is currently undergoes operations
 * @return reference to an element in the routers array.
 */
usb4_router_ctx_t* Usb4CmRouter(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Check how many routers are interdomain routers
 * @param [out] pNum will hold the number of interdomain routers on success
 * @return 0 on success, other on failure
 */
int Usb4CmCheckNumberInterdomainRouters(usb4_cm_ctx_t* usb4_cm_ctx, UINT32* pNum);

/**
 * @brief Configure and enable the interdomain data path
 * @param [in] pCfg see #USB4_host_iface_config_t for additional details
 *                  no usage of pHostIface
 * @return 0 on success, other on failure
 */
int Usb4CmActivateInterdmainDataPath(usb4_cm_ctx_t* usb4_cm_ctx, const USB4_host_iface_config_t* pCfg);

/**
 * @brief Check and provide which instance has Cfg_Params.bUSB3Device
 * @return TRUE for bUSB3Device, FALSE for not
 */
BOOLEAN Usb4CmIsUSB3Device(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Get index of a router with the requested ID
 * @param[in] router_topologyID
 * @param[out] index
 * @return 0 on success other on failure
 */
int Usb4CmFindRouterByTopologyByIndex(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 router_topologyID, UINT32* index);

/**
 * @brief Find active DP In/Out and toggle SWLI bit to re-initialize the link
 * @param[in] portType - DP In/Out
 * @return 0 on success other on failure
 */
int Usb4CmToggleSwliOnDpInOut(usb4_cm_ctx_t* usb4_cm_ctx, USB4_portType portType);

/**
 * @brief Try lock the CM for execution from a single thread
 * @return 0 on successful lock tacking other on failure
 */
int Usb4CmTryLockCm(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Free CM lock
 * @return 0 on successful lock tacking other on failure
 */
int Usb4CmUnlockCm(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Update TMU mode of the domain - impacts entry to low power link states
 * @param[in] tmuMode - TMU mode to configure
 * @return 0 on success other on failure
 */
int Usb4CmUpdateDomainTMUPolicyTmuMode(usb4_cm_ctx_t* usb4_cm_ctx, USB4_tmu_mode tmuMode);

/**
 * @brief Configure CLx mode of the domain - impacts entry to low power link states
 * @param[in] CLxMode - Maximum low power mode to configure
 * @param[out] pbIncompatible - If TRUE, indicates that configuration couldn't be applied and no changes were made
 * @return 0 on success other on failure
 */
int Usb4CmConfigureCLx(usb4_cm_ctx_t* usb4_cm_ctx, USB4_CLx_mode CLxMode, BOOLEAN* pbIncompatible);

/*---------------------------------------------------------------------------*/
/**
 * @brief Check if link from host router has reached CL0
 * @param[in] timeout_ms - Maximum time to poll for the CL0 state
 * @return 0 on success other on failure
 *---------------------------------------------------------------------------*/
int Usb4CmWaitForCl0(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 timeout_ms);

/* ---------------  Router operations ---------------- */

/**
 * @brief Update current router index to a router with the requested ID, or the first uninitialized
 * router (and assign topology ID)
 * @param[in] router_topologyID
 * @return 0 on success other on failure
 */
int Usb4CmPlaceRouterByTopology(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 router_topologyID);

/**
 * @brief Remove all routers which have topologies beyond (and including) the argument
 * router
 * @param[in] router_topologyID
 * @return 0 on success other on failure
 */
int Usb4CmRemoveRoutersBeyondTopology(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 router_topologyID);

/**
 * @brief Enable tunneling on all routers where it hasn't been done before
 * @return 0 on success, other on failure
 */
int Usb4CmEnableTunneling(usb4_cm_ctx_t* usb4_cm_ctx);

/* ---------------  Control packet handling ---------------- */

/**
 * @brief Examine incoming packet and switch CM to look at the appropriate hotplug state machine
 * @return 0 on success, other on failure
 */
int Usb4CmSwitchHotplugSmInstance(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function sorts incoming control packets to appropriate handlers
 * @param[out] method - type of handler to use
 * @return 0 on success, other on failure
 */
int Usb4CmRouteControlPacket(usb4_cm_ctx_t* usb4_cm_ctx, USB4_cpHandlingMethod* method);

/**
 * @brief This function parses control packets which are not handled by the appropriate
 * state machine;
 * @return 0 on success, other on failure
 */
int Usb4CmStatelessPacketsHandler(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function parses adapter hot plug event and handles it appropriately
 * @return 0 on success, other on failure
 */
int Usb4CmAdapterPortHotPlugHandler(usb4_cm_ctx_t* usb4_cm_ctx);


int Usb4CmDPAdaptersExchangeCapabilities(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 sinkAdapterRouterIndex, UINT32 sinkAdapter);

int Usb4CmDPAdaptersEnablePaths(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 sinkAdapterRouterIndex, UINT32 sinkAdapter);

int Usb4CmUpdateDomainTMUPolicy(usb4_cm_ctx_t* usb4_cm_ctx);

int Usb4CmPollForTMUSync(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function parses hot plug event and handles it appropriately;
 * @return 0 on success, other on failure
 */
int Usb4CmUSB4PortHotPlugHandler(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This auxiliary function parses hot plug event details
 * @return 0 on success, other on failure
 */
int Usb4CmParseHpe(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This auxiliary function parses ERROR_LINK notification
 * @return 0 on success, other on failure
 */
int Usb4CmParseErrLink(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Perform housekeeping on a router un-plug
 * @return 0 on success, other on failure
 */
int Usb4CmHandleLaneUnplug(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Check if lane bonding is possible on the pair of routers
 * @param[out] bIsPossible - Specifies if the bonding shoudl be attempted
 * @return 0 on success, other on failure
 */
int Usb4CmCheckBondingIsPossible(usb4_cm_ctx_t* usb4_cm_ctx, BOOLEAN* bIsPossible);

/**
 * @brief Perform lane bonding on the pair of routers
 * @return 0 on success, other on failure
 */
int Usb4CmHandleLaneBonding(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Check if bonding succeeded
 * @param[out] bondingSuceeded - Specifies if the bonding succeeded
 * @return 0 on success, other on failure
 */
int Usb4CmCheckBondingSuceeded(usb4_cm_ctx_t* usb4_cm_ctx, BOOLEAN* bondingSuceeded);

/* ---------------  Interdomain ---------------- */
/**
 * @brief Identify router port which is on the domain boundary and configure it as such
 * @param[in] interdomain_route - parameters of inter-domain response
 * @param[in] remote_UUID - Remote UUID to compare local UUID to
 * @return 0 on success, other on failure
 */
int Usb4CmHandleInterdomainTopology(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 interdomain_route, UINT32 remote_UUID[4]);

/**
 * @brief This function parses interdomain packets and handle them appropriately;
 * @return 0 on success, other on failure
 */
int Usb4CmInterdomainProtocolHandler(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function implements interdomain hot plug flow
 * @return 0 on success, other on failure
 */
int Usb4CmInterdomainHotPlugHandler(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function implements interdomain hot plug flow
 * @return 0 on success, other on failure
 */
int Usb4CmInterdomainHotPlugHandlerProcessUUIDS(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function implements interdomain hot plug flow
 * @return 0 on success, other on failure
 */
int Usb4CmInterdomainHotPlugHandlerCheckX2Support(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function implements interdomain hot plug flow
 * @return 0 on success, other on failure
 */
int Usb4CmInterdomainHotPlugHandlerMasterFlow(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief This function implements interdomain hot plug flow
 * @return 0 on success, other on failure
 */
int Usb4CmInterdomainHotPlugHandlerMasterFlowBond(usb4_cm_ctx_t* usb4_cm_ctx);
/**
 * @brief This function implements interdomain hot plug flow
 * @return 0 on success, other on failure
 */
int Usb4CmInterdomainHotPlugHandlerMeasureIterations(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Sent interdomain UUID request
 * @param[in] interdomain_route - Route to send the request
 * @return 0 on success, other on failure
 */
int Usb4CmRequestXDomainUUID(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 interdomain_route);

/**
 * @brief This auxiliary parses response to UUID request
 * @return 0 on success, other on failure
 */
int Usb4CmHandleXDomainUUIDResponse(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Sent interdomain UUID response
 * Path is stored in the request
 * @return 0 on success, other on failure
 */
int Usb4CmSendXDomainResponseUUID(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Issue request
 * @return 0 on success, other on failure
 */
int Usb4CmSendXDomainLinkStateStatusReq(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Handle request
 * @return 0 on success, other on failure
 */
int Usb4CmHandleXDomainLinkStateStatusReq(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Handle response
 * @return 0 on success, other on failure
 */
int Usb4CmHandleXDomainLinkStateStatusResp(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Issue request
 * @return 0 on success, other on failure
 */
int Usb4CmSendXDomainLinkStateChangeReq(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Handle request
 * @return 0 on success, other on failure
 */
int Usb4CmHandleXDomainLinkStateChangeReq(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Handle response
 * @return 0 on success, other on failure
 */
int Usb4CmHandleXDomainLinkStateChangeResp(usb4_cm_ctx_t* usb4_cm_ctx);

/**
 * @brief Handle ERR_ENUM notification
 * @return 0 on success, other on failure
 */
int Usb4CmHandleErrEnum(usb4_cm_ctx_t* usb4_cm_ctx);

/*
 * @brief Bonding lanes may change the number of total buffers asigned ot the port
 * Call this function to update the memeber variable
 */
int Usb4CmUpdatePortParametersAfterLanesBonded(usb4_cm_ctx_t* usb4_cm_ctx);

/*----------------------------------------------------------------------------
 * Function Declarations
 *--------------------------------------------------------------------------*/

#endif /* __USB4_CM_H_ */
