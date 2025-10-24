/**
 * @file usb4_api.h
 *
 * @brief Header file for a basic USB4 APIs
 *
 * Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 */
#ifndef __USB4_API_H__
#define __USB4_API_H__

/*-----------------------------------------------------------------------------
 * Include Files
 *---------------------------------------------------------------------------*/
// #include "VVHAL_usb4_comdef.h"

/*-----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/
/** @brief max number of bytes in DP aux packet */
#define USB4_API_DP_AUX_MAX_PACKET_BYTES 20

#define USB4_API_DP_AUX_STATUS_NONE                     (0x0)
#define USB4_API_DP_AUX_STATUS_TX_PKT_DONE_IRQ          (1 << 0)
#define USB4_API_DP_AUX_STATUS_RX_PKT_RECEIVED_IRQ      (1 << 1)
#define USB4_API_DP_AUX_STATUS_ACK_TIMEOUT_IRQ          (1 << 2)
#define USB4_API_DP_AUX_STATUS_CLK_SYNC_N_PKTS_IRQ      (1 << 3)
#define USB4_API_DP_AUX_STATUS_RST_ACK_IRQ              (1 << 4)
#define USB4_API_DP_AUX_STATUS_BLOCK_TX_ACK_IRQ	        (1 << 5)
#define USB4_API_DP_AUX_STATUS_PATH_TEARDOWN_IRQ        (1 << 6)
#define USB4_API_DP_AUX_STATUS_ACK_RECEIVED_IRQ	        (1 << 7)
#define USB4_API_DP_AUX_STATUS_HPD_UNPLUG_RECEIVED_IRQ  (1 << 8)
#define USB4_API_DP_AUX_STATUS_HPD_PLUG_RECEIVED_IRQ    (1 << 9)
#define USB4_API_DP_AUX_STATUS_HPD_IRQ_RECEIVED_IRQ     (1 << 10)

#define USB4_API_DP_AUX_STATUS_UNCORRECT_ERROR 	        (1 << 11) /* not clearable, need to reset ? */

#define USB4_API_DP_AUX_STATUS_CLEAR_ALL                (0xFFFFFFFF)

/*-----------------------------------------------------------------------------
 * Type Definitions
 *---------------------------------------------------------------------------*/

/** @brief identifier for each of the subsytem cores */
typedef enum USB4_API_SUBSYSTEM_t
{
    USB4_API_SUBSYSTEM_USB,
    USB4_API_SUBSYSTEM_PCIE,
    USB4_API_SUBSYSTEM_DP,
    USB4_API_SUBSYSTEM_CNT,
} USB4_API_SUBSYSTEM;

/** @brief tunneled mode - usb4 or tbt3 */
typedef enum USB4_API_MODE_t
{
    USB4_API_MODE_USB4,
    USB4_API_MODE_TBT3,
    USB4_API_MODE_LOCALROUTER,
} USB4_API_MODE;

typedef enum USB4_API_DP_AUX_PACKET_TYPE_t
{
    USB4_API_DP_AUX_PACKET_TYPE_AUX,
    USB4_API_DP_AUX_PACKET_TYPE_HPD_STATUS,
    USB4_API_DP_AUX_PACKET_TYPE_SET_CONFIG,
    USB4_API_DP_AUX_PACKET_TYPE_ACK_PACKET,
} USB4_API_DP_AUX_PACKET_TYPE;

typedef enum USB4_API_DP_AUX_ACK_TYPE_t
{
    USB4_API_DP_AUX_ACK_TYPE_SET_CONFIG     = 0x0,
    USB4_API_DP_AUX_ACK_TYPE_HPD_STATUS     = 0x8,
} USB4_API_DP_AUX_ACK_TYPE;

typedef enum USB4_API_DP_AUX_SET_CFG_MSG_TYPE_t
{
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_LINK                   = 0x01,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_STATUS_TRAINING_FAIL       = 0x02,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_STATUS_LOST_CONNECTION     = 0x03,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_DOWNSPREAD             = 0x07,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_POWER                  = 0x08,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_MFDP                   = 0x09,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_FEC_READY              = 0x0A,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_SINK_COUNT             = 0x0C,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_IRQ                        = 0x0D,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_STREAM_MODE            = 0x0F,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_AUX_INIT               = 0x12,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_CMN_DPRX               = 0x13,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_LTTPR_AWARE            = 0x17,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_TRAINING               = 0x18,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_VSPE                   = 0x19,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_STATUS_CR_DONE             = 0x1D,
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE_SET_PHY_TEST_MODE          = 0x05,
} USB4_API_DP_AUX_SET_CFG_MSG_TYPE;

typedef enum USB4_API_DP_LINK_RATE_t
{   
    USB4_API_DP_LINK_RATE_162 = 0, /* RBR  */
    USB4_API_DP_LINK_RATE_270 = 1, /* HBR1 */
    USB4_API_DP_LINK_RATE_540 = 2, /* HBR2 */
    USB4_API_DP_LINK_RATE_810 = 3, /* HBR3 */
} USB4_API_DP_LINK_RATE;

typedef enum USB4_API_DP_AUX_SET_CFG_LANE_CNT_t
{
    USB4_API_DP_AUX_SET_CFG_LANE_CNT_LINK_DOWN      = 0x0,
    USB4_API_DP_AUX_SET_CFG_LANE_CNT_1              = 0x1,
    USB4_API_DP_AUX_SET_CFG_LANE_CNT_2              = 0x2,
    USB4_API_DP_AUX_SET_CFG_LANE_CNT_4              = 0x4,
} USB4_API_DP_AUX_SET_CFG_LANE_CNT;

typedef enum USB4_API_DP_AUX_SET_CFG_TPS_t
{
    USB4_API_DP_AUX_SET_CFG_TPS_TPS2                   = 0x0,
    USB4_API_DP_AUX_SET_CFG_TPS_TPS3                   = 0x1,
    USB4_API_DP_AUX_SET_CFG_TPS_TPS4                   = 0x2,
    USB4_API_DP_AUX_SET_CFG_TPS_TPS3_TPS4              = 0x3,
} USB4_API_DP_AUX_SET_CFG_TPS;

typedef enum USB4_API_DP_AUX_RX_STATUS_t
{
    USB4_API_DP_AUX_RX_STATUS_UNCORRECTABLE_ERROR   = -1,
    USB4_API_DP_AUX_RX_STATUS_NOT_PENDING           = 0,
    USB4_API_DP_AUX_RX_STATUS_PENDING               = 1,
} USB4_API_DP_AUX_RX_STATUS;

typedef struct USB4_api_dp_aux_xfer_t
{
    USB4_API_DP_AUX_PACKET_TYPE type;   /* type of the packet */
    UINT8 buff[USB4_API_DP_AUX_MAX_PACKET_BYTES];   /* buff to send or rcv data */
    UINT32 size_bytes;              /* size in bytes to send / rvc */
    UINT32 timeout_ms;              /* wait for tx to complete or new rx data */
} USB4_api_dp_aux_xfer;

typedef struct USB4_api_dp_aux_set_config_t
{
    USB4_API_DP_AUX_SET_CFG_MSG_TYPE msg_type;  /* see table 10-5 in usb4 v1 spec */
    USB4_API_DP_LINK_RATE link_rate;
    USB4_API_DP_AUX_SET_CFG_LANE_CNT lane_cnt;
    USB4_API_DP_AUX_SET_CFG_TPS tps; 
    UINT8 msg_data;
    UINT32 timeout_ms;                  /* timeout to wait for transmit done */
} USB4_api_dp_aux_set_config;

/*-----------------------------------------------------------------------------
 * Function Declarations
 *---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct  USB4_dp_capability_t
{
    UINT32 ProtocolAdapterVersion;
    UINT32 MaximalDPCDRev;
    UINT32 MaximalLinkRate;
    UINT32 MaximalLaneCount;
    UINT32 MSTCapability;
    UINT32 TPS3Capability;
    UINT32 TPS4Capability;
    UINT32 FECNotSupported;
    UINT32 SecondarySplitCapability;
    UINT32 LTTPRNotSupported;
    UINT32 DSCNotSupported;
} USB4_dp_capability;

typedef struct  USB4_dp_common_capability_t
{
    UINT32 ProtocolAdapterVersion;
    UINT32 MaximalDPCDRev;
    UINT32 MaximalLinkRate;
    UINT32 MaximalLaneCount;
    UINT32 MSTCapability;
    UINT32 TPS3Capability;
    UINT32 TPS4Capability;
    UINT32 FECNotSupported;
    UINT32 SecondarySplitCapability;
    UINT32 LTTPRNotSupported;
    UINT32 DSCNotSupported;
    UINT32 DPRXCapabilitiesReadDone;
} USB4_dp_common_capability;

typedef enum USB4_DP_CONFIG_STREAM_MODE_t
{
    USB4_DP_CONFIG_STREAM_MODE_SST = 0,
    USB4_DP_CONFIG_STREAM_MODE_MST = 1,
} USB4_DP_CONFIG_STREAM_MODE;

/** @brief USB4 open api configuration */
typedef struct USB4_api_open_t
{
    UINT32 coreId;          /**< core instance id */   
    USB4_API_MODE mode;     /**< mode USB4 or TBT3 */
    USB4_API_SUBSYSTEM ss;  /**< ss sub-system core, see #USB4_API_SUBSYSTEM  */
    UINT32 numLanes;        /**< number of phy lanes */
} USB4_api_open;

/** @brief USB4 open h2h api configuration */
typedef struct USB4_api_open_h2h_t
{
    UINT32 hostId;          /**< host instance id */   
    UINT32 devId;           /**< device instance id */   
    USB4_API_MODE mode;     /**< mode USB4 or TBT3 */
    USB4_API_SUBSYSTEM ss;  /**< ss sub-system core, see #USB4_API_SUBSYSTEM  */
    UINT32 numLanes;        /**< number of phy lanes */
} USB4_api_open_h2h;

typedef struct USB4_api_dp_config_t
{
    USB4_DP_CONFIG_STREAM_MODE mode;

    /* 
     * When working in SST mode has no meaning
     * When working in MST mode value defines NUM_ALOC_SIZE 0 - 63 
     */
    UINT8 num_alloc_size;

    USB4_API_DP_LINK_RATE rate;

} USB4_api_dp_config;

/**
 * @brief configures DP IN and enables arming
 * @param pCfg[in] pointer to configuratoin
 * @param coreId the core number to apply to configuration to
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_config_and_arm(UINT32 coreId, USB4_api_dp_config* pCfg);

/**
 * 
 * @brief Force clear the RX buffer without clearing..
 * @param [in] pCap the pointer to the capability to read 
 * @return 0 on success, other on failure
 */

int VVDRV_usb4_api_dp_aux_clear_rx(UINT32 coreId);

/**
 * @brief Read the capabilities of the DP in adapter
 * @param [in] pCap the pointer to the capability to read 
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_read_caps(UINT32 coreId,
                                USB4_dp_capability* pLocalCap, 
                                USB4_dp_capability* pRemoteCap);
/**
 * @brief Reset DP subsystem
 * @param [in] coreId the target core
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_mdp_reset(UINT32 coreId);

/**
 * @brief Write the DP common capabilities
 * @param [in] pCap the pointer to the capability to write 
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_write_common_cap(UINT32 coreId,
                                       const USB4_dp_common_capability* cap);


/**
 * @brief read the DP common capabilities
 * @param [in] pCap the pointer to the capability to write 
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_read_common_cap(UINT32 coreId,
                                      USB4_dp_common_capability* cap);

/**
 * @brief reset the DP IN AP, should be called before the DP send video stream
 * @param [in] coreId
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_reset(UINT32 coreId);

/**
 * @brief resetc all DP core
 * @param [in] coreId
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_core_reset(UINT32 coreId);

/**
 * @brief Get the status according to according to the USB4_API_DP_AUX_STATUS_*
 * defines
 * @param timeout_ms timeout in msec
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_aux_get_status(UINT32 coreId, UINT32* pStatus);

/**
 * @brief Clear the status bits according to the USB4_API_DP_AUX_STATUS_*
 * defines
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_aux_clr_status(UINT32 coreId, UINT32 mask);


/**
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_init(void);

/**
 * @brief Enumerate and build the USB4 path for the SS
 * @param [in] pCfg see #USB4_api_open for additional details
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_open(const USB4_api_open* pCfg);

/**
 * @brief Enumerate and build the USB4 path between host and device
 * @param [in] inPCfg see #USB4_api_open_h2h for additional details
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_open_h2h(const USB4_api_open_h2h* inPCfg);

/**
 * @brief Vote to tear down the USB4 path for the subsytem
 * @param [in] coreId core instance id
 * @param [in] ss sub-system core, see #USB4_API_SUBSYSTEM for details
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_close(UINT32 coreId, USB4_API_SUBSYSTEM ss);

/**
 * @brief Prepare USB3 & USB4 system for sleep
 * @param [in] coreId core instance id
 * @param [in] TBD - wake-up sources?
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_prepare_for_USB3_sleep(UINT32 coreId);

/**
 * @brief Wake USB4 system from sleep based on USB3 event
 * @param [in] coreId core instance id
 * @param [in] TBD - wake-up sources?
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_prepare_for_USB3_wake(UINT32 coreId);

/**
 * @brief Prepare USB4 system for sleep
 * @param [in] coreId core instance id
 * @param [in] TBD - wake-up sources?
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_prepare_for_sleep(UINT32 coreId);


/**
 * @brief Put USB4 system to sleep
 * @param [in] coreId core instance id
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_activate_sleep(UINT32 coreId);

/**
 * @brief Check if device have woken the system from sleep
 * @param [in] coreId core instance id
 * @param [out] pbWakeHappened True if wake interrupt took place
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_check_wake_status(UINT32 coreId, BOOLEAN* pbWakeHappened);

/**
 * @brief Wake USB4 system from sleep
 * @param [in] coreId core instance id
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_wake(UINT32 coreId);


#if 0 /* Not used at this time */
/**
 * @brief Enable/Disable PCIE adapters (coreID relates to USB4 Core)
 * @param [in] coreId core instance id
 * @param [in] bEnable - Enable or disable the adapter
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_enable_PCIE_adapter(UINT32 coreId, BOOLEAN bEnable);
#endif

/**
 * @brief Send PERST active/inactive packets over PCIE path. PCIE Adapter need to be configured as RC,
 * and, PCIE path needs to be valid and enabled
 * @param [in] coreId core instance id
 * @param [in] val - 0 - PERST# Asserted, 1 - De-Asserted
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_set_perst(UINT32 coreIdx, UINT32 val);

/**
 * @brief Get PERST active/inactive status.
 * 0 - PERST# Asserted, 1 - De-Asserted
 * @return perst value
 */
UINT32 VVDRV_usb4_api_get_perst(UINT32 coreIdx);

/**
 * @brief Writes a buffer to AUX TX and waits for success indication
 * @param [in] coreId usb4 instance id
 * @param [in/out] pXfer see #USB4_dp_aux_xfer for details
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_aux_write(UINT32 coreId, USB4_api_dp_aux_xfer* pXfer);

/**
 * @brief Checks if there is some recieve pending data
 * @param [in] coreId usb4 instance id
 * @param [out] pPending see #USB4_API_DP_AUX_RX_STATUS
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_aux_is_rcv_pending(UINT32 coreId, USB4_API_DP_AUX_RX_STATUS* pPending);

/**
 * @brief Waits for reciving data from AUX RX and read it to buffer
 * @param [in] coreId usb4 instance id
 * @param [in/out] pXfer see #USB4_dp_aux_xfer for details
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_aux_read(UINT32 coreId, USB4_api_dp_aux_xfer* pXfer);

/**
 * @brief Build the packet and #Write() it to TX, not waiting for ack
 * @param [in] coreId usb4 instance id 
 * @param [in] pCfg see #USB4_api_dp_aux_set_config for details
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_aux_set_config(UINT32 coreId, 
                                     const USB4_api_dp_aux_set_config* pCfg);

/**
 * @brief Gets the current HPD status from HW
 * @param [in] coreId usb4 instance id 
 * @param [in] pStatus TRUE if HPD status is 1, FALSE otherwise
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_aux_get_hpd_status(UINT32 coreId, BOOLEAN* pStatus);

/**
 * @brief Wait for HPD status to arrive
 * @param [in] coreId usb4 instance id 
 * @param [in] timeout_ms is the time to wait for rx packet
 * @return 0 on success, other on failure
 */
// int VVDRV_usb4_api_dp_ap_set_common(UINT32 coreId, 
//                                     const USB4_api_dp_ap_set_common* pCommon);

/**
 * @brief Translate a buffer to get config
 * @param [in] buff recieved from the #VVDRV_usb4_api_dp_aux_read function with 
 *                  status of type of #USB4_API_DP_AUX_PACKET_TYPE_SET_CONFIG
 * @param [out] pCfg is the parsed configuration from the buffer 
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_aux_parse_set_config(UINT32 coreId,
                                           const UINT8* buff, 
                                           USB4_api_dp_aux_set_config* pCfg);

/**
 * @brief Parse HPD status from buffer
 * @param [in] buff recieved from the #VVDRV_usb4_api_dp_aux_read function with 
 *                  status of type of #USB4_API_DP_AUX_PACKET_TYPE_HPD_STATUS
 * @param [out] pPlug is the parsed configuration from the buffer 
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_aux_parse_hpd_event(UINT32 coreId,
                                          const UINT8* buff,
                                          BOOLEAN* pPlug);

/**
 * @brief Parse ack type from buffer
 * @param [in] buff recieved from the #VVDRV_usb4_api_dp_aux_read function with 
 *                  status of type of #USB4_API_DP_AUX_ACK_TYPE
 * @param [out] pType see #USB4_API_DP_AUX_ACK_TYPE for details
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_aux_parse_ack(UINT32 coreId,
                                    const UINT8* buff, 
                                    USB4_API_DP_AUX_ACK_TYPE* pType);

/**
 * @brief Assert/DeAssert PCIE adapter reset
 * and, PCIE path needs to be valid and enabled
 * @param [in] coreId core instance id
 * @param [in] val - 1 - Asserted, 0 - De-Asserted
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_pcie_ap_reset(UINT32 coreIdx, UINT32 val);

/**
 * @brief Assert/DeAssert USB adapter reset
 * and, PCIE path needs to be valid and enabled
 * @param [in] coreId core instance id
 * @param [in] val - 1 - Asserted, 0 - De-Asserted
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_usb_ap_reset(UINT32 coreIdx, UINT32 val);

/**
 * @brief Re-init DP link (DP OUT or DP OUT and DP IN)
 * DP path needs to be valid and enabled
 * @param [in] coreId core instance id
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_dp_swli(UINT32 coreIdx);

/**
 *  @brief Vote for USB4 sleep
 *  Not to be called while holding CM Lock
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_vote_sleep(UINT32 coreId, USB4_API_SUBSYSTEM ss);

/**
 *  @brief Vote for USB4 wake
 *  Not to be called while holding CM Lock
 * @return 0 on success, other on failure
 */
int VVDRV_usb4_api_vote_wake(UINT32 coreId, USB4_API_SUBSYSTEM ss);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __USB4_API_H__ */

