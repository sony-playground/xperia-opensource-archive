/**---------------------------------------------------------------------------
 *   @file usb4_dp_aux.h
 *
 *   @brief   Implements DP Aux APIs
 *
 *   Copyright (c) 2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#ifndef __USB4_DP_AUX_H__
#define __USB4_DP_AUX_H__

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include "VVHAL_usb4_comdef.h"

#define USB4_DP_AUX_MAX_PACKET_BYTES 20


#define USB4_DP_AUX_STATUS_NONE                     (0x0)
#define USB4_DP_AUX_STATUS_TX_PKT_DONE_IRQ          (1 << 0)
#define USB4_DP_AUX_STATUS_RX_PKT_RECEIVED_IRQ      (1 << 1)
#define USB4_DP_AUX_STATUS_ACK_TIMEOUT_IRQ          (1 << 2)
#define USB4_DP_AUX_STATUS_CLK_SYNC_N_PKTS_IRQ      (1 << 3)
#define USB4_DP_AUX_STATUS_RST_ACK_IRQ              (1 << 4)
#define USB4_DP_AUX_STATUS_BLOCK_TX_ACK_IRQ	        (1 << 5)
#define USB4_DP_AUX_STATUS_PATH_TEARDOWN_IRQ        (1 << 6)
#define USB4_DP_AUX_STATUS_ACK_RECEIVED_IRQ	        (1 << 7)
#define USB4_DP_AUX_STATUS_HPD_UNPLUG_RECEIVED_IRQ  (1 << 8)
#define USB4_DP_AUX_STATUS_HPD_PLUG_RECEIVED_IRQ    (1 << 9)
#define USB4_DP_AUX_STATUS_HPD_IRQ_RECEIVED_IRQ  (1 << 10)
#define USB4_DP_AUX_STATUS_UNCORRECT_ERROR 	        (1 << 11)

#define USB4_DP_AUX_STATUS_CLEAR_ALL                (0xFFFFFFFF)

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/
/** @brief USB1.0 Table 10-3. AUX Path Tunneled Packet Types */
typedef enum
{
    USB4_DP_AUX_PACKET_TYPE_AUX         = 0x0,
    USB4_DP_AUX_PACKET_TYPE_HPD_STATUS  = 0x1,
    USB4_DP_AUX_PACKET_TYPE_SET_CONFIG  = 0x2,
    USB4_DP_AUX_PACKET_TYPE_ACK_PACKET  = 0x3,  
    USB4_DP_AUX_PACKET_TYPE_RES0  = 0x4,  
    USB4_DP_AUX_PACKET_TYPE_RES1  = 0x5,  
    USB4_DP_AUX_PACKET_TYPE_RES2  = 0x6,  
    USB4_DP_AUX_PACKET_TYPE_RES3  = 0x7,  
    USB4_DP_AUX_PACKET_TYPE_RES4  = 0x8,  
    USB4_DP_AUX_PACKET_TYPE_RES5  = 0x9,  
    USB4_DP_AUX_PACKET_TYPE_RES6  = 0xA,  
    USB4_DP_AUX_PACKET_TYPE_RES7  = 0xB,  
    USB4_DP_AUX_PACKET_TYPE_RES8  = 0xC,  
    USB4_DP_AUX_PACKET_TYPE_RES9  = 0xD,  
    USB4_DP_AUX_PACKET_TYPE_RES10  = 0xE,  
    USB4_DP_AUX_PACKET_TYPE_RES11  = 0xF,  
} USB4_DP_AUX_PACKET_TYPE;

typedef enum
{
    USB4_DP_AUX_ACK_TYPE_HPD_STATUS     = 0x0,
    USB4_DP_AUX_ACK_TYPE_SET_CONFIG     = 0x8,
} USB4_DP_AUX_ACK_TYPE;

/** @brief USB1.0 Figure 10-9. SET_CONFIG Packet Format */
typedef enum
{
    USB4_DP_AUX_SET_CFG_LINK_RATE_162   = 0x0,
    USB4_DP_AUX_SET_CFG_LINK_RATE_270   = 0x1,
    USB4_DP_AUX_SET_CFG_LINK_RATE_540   = 0x2,
    USB4_DP_AUX_SET_CFG_LINK_RATE_810   = 0x3,
} USB4_DP_AUX_SET_CFG_LINK_RATE;

/** @brief USB1.0 Figure 10-9. SET_CONFIG Packet Format */
typedef enum
{
    USB4_DP_AUX_SET_CFG_LANE_CNT_LINK_DOWN  = 0x0,
    USB4_DP_AUX_SET_CFG_LANE_CNT_1          = 0x1,
    USB4_DP_AUX_SET_CFG_LANE_CNT_2          = 0x2,
    USB4_DP_AUX_SET_CFG_LANE_CNT_4          = 0x4,
} USB4_DP_AUX_SET_CFG_LANE_CNT;

/** @brief USB1.0 Table 10-5. SET_CONFIG Message */
typedef enum
{
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_LINK                   = 0x01,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_STATUS_TRAINING_FAIL       = 0x02,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_STATUS_LOST_CONNECTION     = 0x03,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_DOWNSPREAD             = 0x07,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_POWER                  = 0x08,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_MFDP                   = 0x09,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_FEC_READY              = 0x0A,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_SINK_COUNT             = 0x0C,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_IRQ                        = 0x0D,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_STREAM_MODE            = 0x0F,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_AUX_INIT               = 0x12,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_CMN_DPRX               = 0x13,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_LTTPR_AWARE            = 0x17,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_TRAINING               = 0x18,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_VSPE                   = 0x19,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_STATUS_CR_DONE             = 0x1D,
    USB4_DP_AUX_SET_CFG_MSG_TYPE_SET_PHY_TEST_MODE          = 0x05,
} USB4_DP_AUX_SET_CFG_MSG_TYPE;

/** @brief USB1.0 Figure 10-9. SET_CONFIG Packet Format */
typedef enum
{
    USB4_DP_AUX_SET_CFG_TPS_TPS2       = 0x0,
    USB4_DP_AUX_SET_CFG_TPS_TPS3       = 0x1,
    USB4_DP_AUX_SET_CFG_TPS_TPS4       = 0x2,
    USB4_DP_AUX_SET_CFG_TPS_TPS3_TPS4  = 0x3,
} USB4_DP_AUX_SET_CFG_TPS;

typedef enum
{
    USB4_DP_AUX_RX_STATUS_UNCORRECTABLE_ERROR   = -1,
    USB4_DP_AUX_RX_STATUS_NOT_PENDING           = 0,
    USB4_DP_AUX_RX_STATUS_PENDING               = 1,
} USB4_DP_AUX_RX_STATUS;

typedef struct
{
    USB4_DP_AUX_PACKET_TYPE type;   /* type of the packet */
    UINT8 buff[USB4_DP_AUX_MAX_PACKET_BYTES];   /* buff to send or rcv data */
    UINT32 size_bytes;              /* size in bytes to send / rvc */
    UINT32 timeout_ms;              /* wait for tx to complete or new rx data */
} USB4_dp_aux_xfer;

typedef struct
{
    USB4_DP_AUX_SET_CFG_MSG_TYPE msg_type;  /* see table 10-5 in usb4 v1 spec */
    USB4_DP_AUX_SET_CFG_LINK_RATE link_rate;
    USB4_DP_AUX_SET_CFG_LANE_CNT lane_cnt;
    USB4_DP_AUX_SET_CFG_TPS tps; 
    UINT8 msg_data;
    UINT32 timeout_ms;                  /* timeout to wait for transmit done */
} USB4_dp_aux_set_config;

typedef struct
{
    BOOLEAN interrupt_mode;
    BOOLEAN auto_ack;
    BOOLEAN hw_ctrl_hpd_status;
} USB4_dp_aux_cfg;



typedef struct
{
    UINT8* m_moduleBase;    /* DP AUX module base address (not HI) */
    UINT32 m_coreId;        /* USB4 core index */
    UINT32 m_swIntStatus;   /* Shadow of status register in ISR mode */
    USB4_dp_aux_cfg m_cfg;  /* configuration */
} usb4_dp_aux_ctx_t;


/* --------------------------------------------------------------------------
 * Global Functions
 *--------------------------------------------------------------------------*/
int Usb4DpAuxInit(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT8* dutWrapperBase, UINT32 coreId);

/**
 * @brief Configuration of the aux module
 * @param [in] pCfg see #USB4_dp_aux_cfg for details
 * @return 0 on succes, other on failure
*/
int Usb4DpAuxConfig(usb4_dp_aux_ctx_t* usb4_dp_aux, const USB4_dp_aux_cfg* pCfg);

/**
 * @brief Get the configuration of the aux module
 * @param [out] pCfg see #USB4_dp_aux_cfg for details
 * @return 0 on succes, other on failure
*/
int Usb4DpAuxGetConfig(usb4_dp_aux_ctx_t* usb4_dp_aux, USB4_dp_aux_cfg* pCfg);

/**
 * @brief Read from the AUX recieved packet
 * @param [in/ out] pXfer see #USB4_dp_aux_xfer for details
 * @return 0 on succes, other on failure
 */
int Usb4DpAuxWrite(usb4_dp_aux_ctx_t* usb4_dp_aux, USB4_dp_aux_xfer* pXfer);

/**
 * @brief Wait for write done status and clears it
 * @param [in] timeout_ms timeout in ms to wait for write done
 * @return 0 on succes, other on failure
 */
int Usb4DpAuxWaitWriteDone(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT32 timeout_ms);

/**
 * @deprecated use #GetStatus() instead
 * @brief Checks if there is a receive pending
 * @param [out] pPending see #USB4_DP_AUX_RX_STATUS
 * @return 0 on succes, other on failure
 */
int Usb4DpAuxIsRcvPending(usb4_dp_aux_ctx_t* usb4_dp_aux, USB4_DP_AUX_RX_STATUS* pPending);

/**
 * @brief Wait for recieved packet and read from the AUX recieved packet
 * @param [in/ out] pXfer see #USB4_dp_aux_xfer for details
 * @return 0 on succes, other on failure
 */
int Usb4DpAuxRead(usb4_dp_aux_ctx_t* usb4_dp_aux, USB4_dp_aux_xfer* pXfer);

/**
 * @brief Build the packet and #Write() it to TX, 
 *        than wait for ack on RX and verify ack received
 * @param [in] pCfg see #USB4_dp_aux_set_config for details
 * @return 0 on succes, other on failure
 */
int Usb4DpAuxSendSetConfig(usb4_dp_aux_ctx_t* usb4_dp_aux, const USB4_dp_aux_set_config* pCfg);

/**
 * @brief Parse set config from buffer
 * @param [in] pBuff buffer to parse (holds set config)
 * @param [out] pCfg configuration
 * @return 0 on succes, other on failure
 */ 
int Usb4DpAuxParseSetConfig(usb4_dp_aux_ctx_t* usb4_dp_aux, const UINT8* pBuff, USB4_dp_aux_set_config* pCfg);

/**
 * @brief Parse HPD status from buffer
 * @param [in] pBuff buffer to parse (holds hpd status message)
 * @param [out] pPlug TRUE if plug received, FALSE otherwise
 * @return 0 on succes, other on failure
 */ 
int Usb4DpAuxParseHpdEvent(usb4_dp_aux_ctx_t* usb4_dp_aux, const UINT8* pBuff, BOOLEAN* pPlug);

/**
 * @brief Parse HPD status from buffer
 * @param [in] pBuff buffer to parse (holds hpd status message)
 * @param [out] pType SET_CFG or HPD_STATUS, see #USB4_DP_AUX_ACK_TYPE
 * @return 0 on succes, other on failure
 */ 
int Usb4DpAuxParseAckPacket(usb4_dp_aux_ctx_t* usb4_dp_aux, const UINT8* pBuff, USB4_DP_AUX_ACK_TYPE* pType);

/**
 * @brief Get latest HPD status
 * @param [out] pPlug TRUE if plugged received, FALSE otherwise
 * @return 0 on succes, other on failure
 */
int Usb4DpAuxGetHpdStatus(usb4_dp_aux_ctx_t* usb4_dp_aux, BOOLEAN* pPlug);

/**
 * @brief return the current status of the aux channel
 * @param [out] pStatus will hold the latest not cleaned status, 
* 				see #USB4_DP_AUX_STATUS for bitmask
 * @return 0 on success, other on failure
 */
int Usb4DpAuxGetStatus(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT32 *pStatus);

/**
 * @brief clear the driver status events
 * @param [in] mask mask to clean, see #USB4_DP_AUX_STATUS for bitmask
 * @return 0 on success, other on failure
 */
int Usb4DpAuxClearStatus(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT32 mask);

/**
 * @brief Called from the IRQ context and updates the shaddow status
 * @param [in] int_source is the interrupt number
 * @return 0 on success, other on failure
 */
int Usb4DpAuxIsrHandler(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT32 int_source);

/**
 * @deprecated please use #GetStatus() instead
* @brief Wait for expected status
 * @param [in] mask mask to wait for, see #USB4_DP_AUX_STATUS
 * @param [in] timeout_ms timeout in ms for waiting
 * @return 0 on succes, other on failure
 */ 
int Usb4DpAuxWaitForStatus(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT32 mask, UINT32 timeout_ms);

/**
* @brief Pop an entry from the rx buffer
 * @return 0 on succes, other on failure
 */ 
int Usb4DpAuxClearRxBuffer(usb4_dp_aux_ctx_t* usb4_dp_aux);   

/**
* @brief  Enable the adapter
 * @return 0 on succes, other on failure
 */ 
int Usb4DpAuxEnableAdapter(usb4_dp_aux_ctx_t* usb4_dp_aux);

#endif /* __USB4_DP_AUX_H__ */
                       
