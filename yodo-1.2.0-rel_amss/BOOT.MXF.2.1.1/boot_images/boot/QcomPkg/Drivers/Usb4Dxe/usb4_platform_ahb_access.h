/**---------------------------------------------------------------------------
 *
 *  @file  :  usb4_platform_ahb_access.h
 *
 *  @brief :  usb4 ahb access functions
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#ifndef __USB4_PLATFORM_AHB_ACCESS_H_
#define __USB4_PLATFORM_AHB_ACCESS_H_

#include "usb4_port.h"
#include "usb4_api.h"

typedef struct
{
    UINT8* m_coreBaseAddress;

    /* Data that has to persist through sleep */
    UINT32 m_USBAP_CFG_RXTERM_BACKDOOR_STS;
} usb4_platform_ahb_access_ctx_t;


void Usb4PlatformAhbAccessInit(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT8* coreBaseAddress, UINT32 USBAP_CFG_RXTERM_BACKDOOR_STS);
void Usb4PlatformAhbAccessDeInit(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/**
* @brief Disable lane1 of the host router
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_disable_lane1(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/**
* @brief Wait for lane 0 to reach CL0
* @param[in] timeout_ms - Timeout value in ms
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_lane0_wait_for_cl0(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 timeout_ms);

/**
* @brief Configur Nth inbound path from Lane0
* @param[in] path_index - Path index
* @param[in] pPath - Path parameters
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_configure_L0_path(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 path_index, usb4_pathN_cs* pPath);

/**
* @brief Configure outbound path from DPIN AUX adapter
* @param[in] pPath - Path parameters
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_configure_dpinap_aux_path(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, usb4_pathN_cs* pPath);

/**
* @brief Configure outbound path from PCIe adapter
* @param[in] pPath - Path parameters
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_configure_pcieap_path(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, usb4_pathN_cs* pPath, BOOLEAN bEp);

/**
* @brief Configure EP mode for PCIe adapter
* @param[in] bEp - Is this adapter EP?
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_configure_pcieap_ep_mode(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, BOOLEAN bEp);

/**
* @brief Configure outbound path from PCIe adapter
* @param[in] pPath - Path parameters
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_configure_hiaap_path(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, usb4_pathN_cs* pPath);

/**
* @brief Configure VBUS state for USB internal conntroller
* @param[in] CoreId - USB3 coreId
* @param[in] State - VBUS enabled (1), Disabled(0)
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_USB3_VBUS_on_off(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 CoreId, BOOLEAN State);

/**
* @brief Mask USB4 credits for USB adapter
* @param[in] Credit - Maksed (TRUE), UNMASKED(FALSE)
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_USB4_USBAP_mask_credits(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, BOOLEAN Credit);

/**
* @brief Read/Write USB4 USBAP TX & RX Buffer
* @param[in] R_W - WRITE (TRUE), READ (FALSE)
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_USB4_USBAP_BUF_access(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, BOOLEAN R_W);

/**
* @brief Assert/De-assert USBAP reset
* @param[in] assert - 1 (TRUE), 0 (FALSE)
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccessAssertUSBAPReset(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, BOOLEAN assert);

/**
* @brief USBAP PHY status Enable/Disable
* @param[in] assert - 1 (TRUE), 0 (FALSE)
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccessUSBAPPHYStatusEnable(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, boolean bEnable);


/**
* @brief Configure outbound path from USB adapter
* @param[in] ACK - XHCI ACK
* @param[in] BW - Allocated BW to be written
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_enable_usbap_XHCI_BW_negotiation(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, BOOLEAN CMR, UINT32 scale, UINT32 BW); 

/**
* @brief Configure outbound path from USB adapter
* @param[in] RxTerm - RxTerm value to be set
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_set_usbap_local_rxterm_Req(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT8 RxTerm);

/**
* @brief Get link rate of USB3 Tunneling
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_get_usbap_link_rate(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/**
* @brief Get num of DP packets/bytes
* @param[in] Pkt_byte - 0 - Get num_of_bytes, 1 - Get num_of_Packets
* @return numDP packets value
*/
UINT32 Usb4PlatformAhbAccess_get_usbap_num_DP_packets(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, BOOLEAN Pkt_byte);

/**
* @brief Prepare USB3 sleep 
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_PrepareUSB3Sleep(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/**
* @brief Prepare USB3 Wakeup 
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_PrepareUSB3Wakeup(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

// TODO: AC Deprecated
/**
* @brief Assert USB3 sub-system reset
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_AssertDeassertUSBReset(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/**
* @brief Configure USB AP in device mode
* @param[in] bDevice - Enable device mode in AP CONFIG PROP registers
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_configure_usbap_device_mode(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, BOOLEAN bDevice);

/**
* @brief Configure USB4 mode of USB adapter
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_configure_usbap_usb4_mode(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/**
* @brief Configure outbound path from USB adapter
* @param[in] pPath - Path parameters
* @param[in] bEnable - Enable/Disable Path Enable
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_configure_usbap_path(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, usb4_pathN_cs* pPath, BOOLEAN bEnable);

/**
* @brief Configure HPE retransmission on a router - 0 means disabled
* @param[in] interval_ms - msec between retransmissions, up to 255
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_configure_HPE_retransmission_interval(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 interval_ms);

/**
* @brief Send PERST active/inactive packets over PCIE path. PCIE Adapter need to be configured as RC,
* and, PCIE path needs to be valid and enabled
* @param [in] coreId core instance id
* @param [in] val - 0 - PERST# Asserted, 1 - De-Asserted
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_pcieap_set_perst(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 val);

/**
* @brief Get PERST active/inactive status.
* 0 - PERST# Asserted, 1 - De-Asserted
* @return perst value
*/
UINT32 Usb4PlatformAhbAccess_pcieap_get_perst(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/**
* @brief write common capabilities filed in DP IN adpater
* @param cap the common capcabilieis
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_dpin_write_common_cap(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, const USB4_dp_common_capability *cap);

/**
* @brief  reset dp in adapter
* @return 0 on success, other on failure
*/ 
int Usb4PlatformAhbAccess_dpin_reset(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/** 
* @brief  reset dp in dropped packet counter
* @return 0 on success, other on failure
*/ 
int Usb4PlatformAhbAccess_dpin_reset_dropped_packet_counter(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/** 
* @brief  get dp in dropped packet counter
* @param pCount[out] pointer the number of packets
* @return 0 on success, other on failure
*/ 
int Usb4PlatformAhbAccess_dpin_get_dropped_packet_counter(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 * pCount);


/**
* @brief  reset dptx controller
* @return 0 on success, other on failure
*/ 
int Usb4PlatformAhbAccess_dptx_reset(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/**
* @brief  reset mdp 
* @return 0 on success, other on failure
*/ 
int Usb4PlatformAhbAccess_mdp_reset(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/**
* @brief  Configure DPIN in prepeare for operation
* @param  pCfg pointer to configuration
* @return 0 on success, other on failure
*/     
int Usb4PlatformAhbAccess_dpin_config_and_arm(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, USB4_api_dp_config* pCfg);

/**
* @brief  Configure DPIN hot plug generation
* @param  bEnable - Enable/Disable generation
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_dpin_configure_hot_plug_notification(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, BOOLEAN bEnable);

#ifdef RUMI
/**
* @brief Issue cable disconnect through user register
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_GE_issue_disconnect(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/**
* @brief Remove disconnected state in the user register
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_GE_cancel_disconnect(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

#endif /* RUMI */

#ifdef USB4_COMPILING_GEN_EMU

/**
* @brief Set PHY rate for GE
* @param[in] rate - PHY parameter
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_GE_set_PHY_rate(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 val);

/**
* @brief Issue cable disconnect through user register
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_GE_issue_disconnect(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

/**
* @brief Remove disconnected state in the user register
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_GE_cancel_disconnect(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);

int Usb4PlatformAhbAccess_cp_fcm_send_perst(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, BOOLEAN bActive);
#endif /* USB4_COMPILING_GEN_EMU */


/**
* @brief Configure TMU clocks
* @return 0 on success, other on failure
*/
int Usb4PlatformAhbAccess_configure_tmu_clocks(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx);


#if 0 // Absorb the target specific class
class VVHAL_usb4_platform_ahb_access
{
public:

    /**
    * @brief Disable lane1 of the host router
    * @param[in] pBaseDut - Base address of the usb4 core
    * @return 0 on success, other on failure
    */
    virtual int disable_lane1() { return -1;}

    /**
    * @brief Wait for lane 0 to reach CL0
    * @param[in] pBaseDut - Base address of the usb4 core
    * @param[in] timeout_ms - Timeout value in ms
    * @return 0 on success, other on failure
    */
    virtual int lane0_wait_for_cl0(UINT32 timeout_ms) { return -1;}

    /**
    * @brief Configur Nth inbound path from Lane0
    * @param[in] pBaseDut - Base address of the usb4 core
    * @param[in] path_index - Path index
    * @param[in] pPath - Path parameters
    * @return 0 on success, other on failure
    */
    virtual int configure_L0_path(UINT32 path_index, usb4_pathN_cs* pPath) { return -1;}

    /**
    * @brief Configure outbound path from DPIN AUX adapter
    * @param[in] pBaseDut - Base address of the usb4 core
    * @param[in] pPath - Path parameters
    * @return 0 on success, other on failure
    */
    virtual int configure_dpinap_aux_path(usb4_pathN_cs* pPath) { return -1;}

    /**
     * @brief Configure outbound path from PCIe adapter
     * @param[in] pPath - Path parameters
     * @return 0 on success, other on failure
     */
    virtual int configure_pcieap_path(usb4_pathN_cs* pPath, BOOLEAN bEp) { return -1; }

    /**
     * @brief Configure EP mode for PCIe adapter
     * @param[in] bEp - Is this adapter EP?
     * @return 0 on success, other on failure
     */
    virtual int configure_pcieap_ep_mode(BOOLEAN bEp) { return -1; }

    /**
     * @brief Configure outbound path from PCIe adapter
     * @param[in] pPath - Path parameters
     * @return 0 on success, other on failure
     */
    virtual int configure_hiaap_path(usb4_pathN_cs* pPath) { return -1; }

    /**
     * @brief Configure outbound path from USB adapter
     * @param[in] CoreId - USB3 coreId
     * @param[in] State - VBUS enabled (1), Disabled(0)
     * @return 0 on success, other on failure
     */
    virtual int USB3_VBUS_on_off(UINT32 CoreId, BOOLEAN State) { return -1; }

    /**
     * @brief Mask USB4 credits for USB adapter
     * @param[in] Credit - Maksed (TRUE), UNMASKED(FALSE)
     * @return 0 on success, other on failure
     */
    virtual int USB4_USBAP_mask_credits( BOOLEAN Credit) { return -1; }

     /**
     * @brief Read/Write USB4 USBAP TX & RX Buffer
     * @param[in] R_W - WRITE (TRUE), READ (FALSE)
     * @return 0 on success, other on failure
     */
     virtual int USB4_USBAP_BUF_access(BOOLEAN R_W) { return -1; }

     /**
     * @brief Assert/De-assert USBAP reset
     * @param[in] assert - 1 (TRUE), 0 (FALSE)
     * @return 0 on success, other on failure
     */
     virtual int assert_USBAP_reset(BOOLEAN assert) { return -1; }

    /**
     * @brief Configure outbound path from USB adapter
     * @param[in] ACK - XHCI ACK
     * @param[in] BW - Allocated BW to be written
     * @return 0 on success, other on failure
     */
     virtual int enable_usbap_XHCI_BW_negotiation(BOOLEAN CMR, UINT32 scale, UINT32 BW) { return -1; }

      /**
     * @brief Configure outbound path from USB adapter
     * @param[in] RxTerm - RxTerm value to be set
     * @return 0 on success, other on failure
     */
    virtual int set_usbap_local_rxterm_Req(UINT8 RxTerm) { return -1; }
    
     /**
     * @brief Get link rate of USB3 Tunneling
     * @return 0 on success, other on failure
     */
    virtual int get_usbap_link_rate() { return -1; }

    /**
     * @brief Get num of DP packets/bytes
     * @param[in] Pkt_byte - 0 - Get num_of_bytes, 1 - Get num_of_Packets
     * @return numDP packets value
     */
    virtual UINT32 get_usbap_num_DP_packets(BOOLEAN Pkt_byte) { return 0;}

    /**
     * @brief Prepare USB3 sleep 
     * @return 0 on success, other on failure
     */
    virtual int PrepareUSB3Sleep() { return -1; }

    /**
     * @brief Prepare USB3 Wakeup 
     * @return 0 on success, other on failure
     */
    virtual int PrepareUSB3Wakeup() { return -1; }

    /**
     * @brief Assert USB3 sub-system reset
     * @return 0 on success, other on failure
     */
    virtual int AssertDeassertUSBReset() { return -1; }

    /**
     * @brief Configure USB adapter in Device mode
     * @param[in] bDevice - Enable device mode in AP PROP registers
     * @return 0 on success, other on failure
     */
    virtual int configure_usbap_device_mode( BOOLEAN bDevice) { return -1; }

    /**
     * @brief Configure USB4 mode of USB adapter
     * @return 0 on success, other on failure
     */
    virtual int configure_usbap_usb4_mode() { return -1; }

    /**
     * @brief Configure outbound path from USB adapter
     * @param[in] pPath - Path parameters
     * @param[in] bEnable - Enable/Disable USSBAP Path Enable
     * @return 0 on success, other on failure
     */
    virtual int configure_usbap_path(usb4_pathN_cs* pPath, BOOLEAN bEnable) { return -1; }

    /**
    * @brief Set PHY rate for GE
    * @param[in] rate - PHY parameter
    * @return 0 on success, other on failure
    */
    virtual int GE_set_PHY_rate(UINT32 val) {return -1;}

    /**
    * @brief Issue cable disconnect through user register
    * @return 0 on success, other on failure
    */
    virtual int GE_issue_disconnect(){return -1;}

    /**
    * @brief Remove disconnected state in the user register
    * @return 0 on success, other on failure
    */
    virtual int GE_cancel_disconnect(){return -1;}

    /**
    * @brief Configure HPE retransmission on a router - 0 means disabled
    * @param[in] interval_ms - msec between retransmissions, up to 255
    * @return 0 on success, other on failure
    */
    virtual int configure_HPE_retransmission_interval(UINT32 interval_ms){return -1;}

    /**
     * @brief Send PERST active/inactive packets over PCIE path. PCIE Adapter need to be configured as RC,
     * and, PCIE path needs to be valid and enabled
     * @param [in] val - 0 - PERST# Asserted, 1 - De-Asserted
     * @return 0 on success, other on failure
     */
    virtual int pcieap_set_perst(UINT32 val){return -1;};

    /**
     * @brief Get PERST active/inactive status.
     * 0 - PERST# Asserted, 1 - De-Asserted
     * @return perst value
     */
    virtual UINT32 pcieap_get_perst(){return 0;};

    /**
     * @brief write common capabilities filed in DP IN adpater
     * @param cap the common capcabilieis
     * @return 0 on success, other on failure
     */
    virtual int dpin_write_common_cap(const USB4_dp_common_capability *cap) {return -1;}
   
    /**
     * @brief  reset dptx controller
     * @return 0 on success, other on failure
     */ 
    virtual int dptx_reset() {return -1;}

    /**
     * @brief  reset dp in adapter
     * @return 0 on success, other on failure
     */ 
    virtual int dpin_reset() {return -1;}

    /**
     * @brief  reset mdp 
     * @return 0 on success, other on failure
     */ 
    virtual int mdp_reset() {return -1;}

    /**
     * @brief  Configure DPIN in prepeare for operation
     * @param  pCfg pointer to configuration
     * @return 0 on success, other on failure
     */     
    virtual int dpin_config_and_arm(USB4_api_dp_config* pCfg) {return -1;}
    
    /**
     * @brief FCM and CP added a feature to enable the CP to send any packet 
     *        for any active path, send perst through path 0
     * @param [in] bActive TRUE to active, FALSE for inactive
     * @return 0 on success, other on failure
     */     
    virtual int cp_fcm_send_perst(BOOLEAN bActive) { return -1; }

    /**
     * @brief  Configure DPIN hot plug generation
     * @param  bEnable - Enable/Disable generation
     * @return 0 on success, other on failure
     */
    virtual int dpin_configure_hot_plug_notification(BOOLEAN bEnable) {return -1;}

     /** 
     * @brief  reset dp in dropped packet counter
     * @return 0 on success, other on failure
     */ 
    virtual int dpin_reset_dropped_packet_counter() {return -1;}

    /** 
     * @brief  get dp in dropped packet counter
     * @param pCount[out] pointer the number of packets
     * @return 0 on success, other on failure
     */ 
    virtual int dpin_get_dropped_packet_counter(UINT32 *pCount) {return -1;}

    /**
    * @brief Configure TMU clocks
    * @return 0 on success, other on failure
    */
    virtual int configure_tmu_clocks() {return 0;};
};
#endif // Absorb the target specific class

#endif /*__USB4_PLATFORM_AHB_ACCESS_H_ */
