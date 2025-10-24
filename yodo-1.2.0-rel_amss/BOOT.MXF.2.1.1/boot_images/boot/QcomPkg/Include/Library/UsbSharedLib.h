/*=======================================================================*//**
 * @file        UsbSharedLib.h
 * @author:     pmahajan
 * @date        01-feb-2017
 *
 * @brief       USB common USB core init implementation Header.
 *
 * @details     This file contains API's the Init sequence for HS and SS core implementation.
 *
 * @note        
 *
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2016-2018,2021-2022 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
//============================================================================
// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// 
// when         who        what, where, why
// --------     ---        ----------------------------------------------------------
// 04/19/18     amitg  Poipu Multi-Port Support
// 03/19/18		  gk	   Updated SS and HS Phy sequence for Multiport from latest HPG 
// 04/26/17     amitg  Updated QUSB2 Phy confirguration for Host mode low speed devices
// 03/30/17     pm     Added configuration for sec Clock and core
// 02/01/17     pm 	   Initial revision
//
// ===========================================================================

#ifndef _USB_SHARED_LIB__H_
#define _USB_SHARED_LIB__H_

#include "comdef.h"    // basic types as byte word uint32 etc
#include <stdint.h>
#include <DebugLib.h>
#include "UsbError.h"
#include "PlatformInfo.h"  //platform type

#define QUSB_HWIO_ADDR_EMPTY                    (0xFFFFFFFF)
#define QUSB_HWIO_ADDR_END                      (0x0)

//----------------------------------------------------------------------------
// Static Variable Definitions
//----------------------------------------------------------------------------

// Assume a 300 ohm SMB charger resistor on D+/D- which corresponds to HSTX_TRIM offset of value 2
// Subtract QUSB_HSTX_TRIM_OFFSET to make amplitude overshoot by 400mV to account for longer cables and hubs.

#define QUSB_HSTX_TRIM_OFFSET                     (0)
#define QUSB_HS_PHY_PLL_BMSK                      (0x1)
#define QUSB_HS_PHY_PLL_MAX_CNT                   (20000)
#define QUSB_HS_PHY_PLL_CHECK_DELAY_PER_LOOP      (5)

#define MICRO_STALL_UNITS(x)  ((x) * 10)

#define USB_SHARED_ASSERT(val)  usb_shared_error_log(val, 0, __LINE__);

#define QUSB_FD_PRODUCT_STRING_LENGTH_MAX (60)
#define USB_DESCTYPE_STRING               (3)

#define USB_SHARED_CHIP_REVISION(major, minor)  (((major) << 16) | (minor))

typedef enum
{
  USB4_MODE_TYPE_USB3,
  USB4_MODE_TYPE_USB3DP,
  USB4_MODE_TYPE_DP4LANE,
  USB4_MODE_TYPE_TBT3,
  USB4_MODE_TYPE_USB4,
  USB4_MODE_TYPE_MAX,
}USB4_MODE_TYPE;

typedef struct 
{
  uint32 address;
  uint8  value;
} qusb_phy_cfg_type;

typedef struct 
{
  uint32 address;
  uint32  value;
} usb_dtb_phy_cfg_type;

typedef enum
{
  USB_DTB_STATUS_SUCCESS,
  USB_DTB_STATUS_WRONG_NAME,
  USB_DTB_STATUS_FAILED_GET_BLOB,
  USB_DTB_STATUS_FAILED_GET_NODE,
  USB_DTB_STATUS_FAILED_GET_PROP_SIZE,
  USB_DTB_STATUS_FAILED_ALLOC,
  USB_DTB_STATUS_FAILED_GET_PROP_LIST,
  USB_DTB_STATUS_FAILED_PROCESS_LIST,
  USB_DTB_STATUS_FAILED_FREE,
  USB_DTB_STATUS_INVALID_ADDR,
  USB_DTB_STATUS_MAX
}USB_DTB_STATUS_TYPE;

typedef struct
{
  DalPlatformInfoPlatformType platform;
  uint32 subtype;
} usb_platform_ctx;

typedef enum
{
  USB_TYPE_C_LANE_A = 0x0,
  USB_TYPE_C_LANE_B = 0x1,
  USB_TYPE_C_NO_LANE = 0x7FFFFFFF, 
} USB_TYPE_C_LANE_TYPE;

//============================================================================
/**
* @function  usb_shared_xbl_dtb_node_init
*
* @brief  Get USB phy registers programming table from device tree binary node
          and program phy table
*
* @Note : None
*
* @param : pdtb_node_name - name of device tree node to get for phy programming table 
  
*
* @return : USB_DTB_STATUS_TYPE 0 succssful else error
*
*/
//============================================================================
USB_DTB_STATUS_TYPE usb_shared_xbl_dtb_node_init(char *pdtb_node_name);

//============================================================================
/**
* @function  usb_shared_process_phy_reg_dtb_list
*
* @brief Programming phy registers for provided dtb node, dtb list proerty name 
          and size
*
* @Note : None
*
* @param : pphy_table - pointer handle for usb_dtb_phy_cfg_type dtb node property value
           prop_size - byte size of property to program
*
* @return : TRUE if programming registers is SUCCESS else FALSE
*
*/
//============================================================================
boolean usb_shared_process_phy_reg_dtb_list(const usb_dtb_phy_cfg_type* pphy_table, uint32 prop_size);

//============================================================================
/**
* @function USB_SHARED_HS_PHY_INIT
*
* @brief API used to initialize the High Speed Primary PHY
*
* @Note : 
*
* @param    None 
*
* @return   None
*
*/
//============================================================================
boolean usb_shared_hs_phy_init(void);

//============================================================================
/**
* @function USB_SHARED_HS_PHY_INIT_SEC
*
* @brief API used to initialize the High Speed Secondary PHY
*
* @Note : 
*
* @param    None 
*
* @return   None
*
*/
//============================================================================
boolean usb_shared_hs_phy_init_sec(void);

//============================================================================
/**
* @function USB_SHARED_HS_PHY_INIT_MP0
*
* @brief API used to initialize the High Speed MultiPort 0 PHY
*
* @Note : 
*
* @param    None 
*
* @return   None
*
*/
//============================================================================
boolean usb_shared_hs_phy_init_MP0(void);

//============================================================================
/**
* @function USB_SHARED_HS_PHY_INIT_MP1
*
* @brief API used to initialize the High Speed MultiPort 1 PHY
*
* @Note : 
*
* @param    None 
*
* @return   None
*
*/
//============================================================================
boolean usb_shared_hs_phy_init_MP1(void);


//============================================================================
/**
* @function USB_SHARED_HS_PHY_INIT
*
* @brief API used to initialize the High Speed RUMI PHY
*
* @Note : 
*
* @param    core_num
*               1st core (primary) = 0, 2nd = 1, etc
*           port_num
*               If core supports multiple ports, 0..4. (0 default)
*
* @return   None
*
*/
//============================================================================
boolean usb_shared_hs_phy_rumi_init(uint32 core_num, uint32 phy_num);

//============================================================================
/**
* @function USB_SHARED_SS_PHY_INIT  
*
* @brief API used to initialize the Super Speed Primary PHY
*
* @Note : 
*
* @param    usb_ss_phy_lane: 0 - LANE_A and nonzero = LANE_B
*
* @return   None
*
*/
//============================================================================
boolean usb_shared_ss_phy_init(uint32 usb_ss_phy_lane);

//============================================================================
/**
* @function USB_SHARED_SS_PHY_INIT_SEC  
*
* @brief API used to initialize the Super Speed Secondary UNI_PHY
*
* @Note : 
*
* @param    None 
*
* @return   None
*
*/
//============================================================================
boolean usb_shared_ss_phy_init_sec();

//============================================================================
/**
* @function USB_SHARED_SS_PHY_INIT_SECDP  
*
* @brief API used to initialize the Super Speed Secondary DP_PHY 
*
* @Note : 
*
* @param    None 
*
* @return   None
*
*/
//============================================================================
boolean usb_shared_ss_phy_init_secDP(uint32 usb_ss_phy_lane);

/**
* @function USB_SHARED_SS_PHY_INIT_MP0  
*
* @brief API used to initialize the Super Speed MultiPort 1 PHY
*
* @Note : 
*
* @param    None 
*
* @return   None
*
*/
//============================================================================
boolean usb_shared_ss_phy_init_MP0();

/**
* @function USB_SHARED_SS_PHY_INIT_MP1  
*
* @brief API used to initialize the Super Speed MultiPort 1 PHY
*
* @Note : 
*
* @param    None 
*
* @return   None
*
*/
//============================================================================
boolean usb_shared_ss_phy_init_MP1();

//============================================================================
/**
* @function usb_shared_poll_ss_phy_training
*
* @brief    Polls USB SS PHY for training
*
*/
//============================================================================
void usb_shared_poll_ss_phy_training(void);

//============================================================================
/**
* @function usb_shared_poll_ss_phy_training_sec
*
* @brief    Polls USB SS PHY for training
*
*/
//============================================================================
void usb_shared_poll_ss_phy_training_sec(void);

//============================================================================
/**
* @function  usb_shared_get_chip_serial_number
*
* @brief Call API to uint32 unique MSM serial string
*
* @Note : None
*
* @param  None 
*
* @return uint32: Chip serial number
*
*/
//============================================================================
uint32 usb_shared_get_chip_serial_number(void);

//============================================================================
/**
* @function  usb_shared_get_chip_id
*
* @brief Call API to uint32 unique chip id
*
* @Note : None
*
* @param  None 
*
* @return uint32: Chip id number
*
*/
//============================================================================
uint32 usb_shared_get_chip_id(void);

//============================================================================
/** 
 * API is used to add chip serial number to the string and return 
 * Product String Descriptor
 * 
 * @param pointer to product string
 *              Pointer to the buffer to be updated with Product string desc
 *              Length of the buffer
 *
 * @return Appended string length
 */ 
//============================================================================ 
uint32 usb_shared_get_product_str_desc_with_chip_serial(char* product_str, char* prod_str_desc, uint32 desc_len);

//============================================================================
/**
* @function  usb_shared_is_eud_active
*
* @brief Returns status whether EUD is active 
*        and has already initialized High Speed PHY
*
* @Note : None
*
* @param  None 
*
* @return boolean: TRUE is EUD is active, FALSE otherwise
*
*/
//============================================================================
boolean usb_shared_is_eud_active(void);

// ===========================================================================
/**
 * @function    usb_shared_eud_update_serial_number
 * 
 * @brief   This function update device ID to EUD_CTL_DEV_ID
 *          So each device can have unique ID
 * 
 * @param   uin32 device_id - new ID number
 * 
 * @return  
 * 
 */
// ===========================================================================
void usb_shared_eud_update_serial_number(uint32 serial_number);

// ===========================================================================
/**
 * @function    usb_shared_is_run_stop_active
 * 
 * @brief   	This API determines whether USB run stop bit is active
 * 
 * @note    	This API will read usb regisiter for run_stop bit status        
 *  
 * @param   	TRUE signifies if run_stop bit is 1.
 *
 */
// ===========================================================================
boolean usb_shared_is_run_stop_active(void);

// ===========================================================================
/**
 * @function    usb_shared_refclk_enable
 * 
 * @brief   	This API enable/disable usb refclk
 * 
 * @param     boolean bEnable - enable/disable ref clk
 *  
 *
 */
// ===========================================================================
void usb_shared_refclk_enable(boolean bEnable);

//============================================================================
/** 
 * API is used to check if EP MaxPaxketSize has to be limited in Fastboot
 * @param Endpoint Address
 *		  Endpoint Attribute
 *		  Endpoint MaxPacketSize
 *
 *
 * @return TRUE if EUD is active and the EP is BULK type OUT EP 
 *		   Otherwise FALSE
 */ 
//============================================================================ 
boolean usb_shared_is_eud_bulk_out_ep_limit_required(uint8 ep_addr, uint8 ep_attr, uint16 mps);


// Wrapper functions for Core/Loader specific implementaion
void usb_shared_delay_us(uint32 usecs);
void usb_shared_loop_here(void); 
void usb_shared_uart_log_info(char *message);
void usb_shared_uart_log_error(char *message, uint32 value);
void usb_shared_error_log(uint32 id_0, uint8 offset, uint32 param);
uint32 usb_shared_get_chip_revision(void);

// ===========================================================================
/**
 * @function    usb_shared_dp_toggle
 * 
 * @brief   API used to toggle D+ high then low for interval in milliseconds
 * 
 * @param   interval_ms   interval in milliseconds
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_shared_dp_toggle(uint32 interval_ms);

// ===========================================================================
/**
 * @function    usb_shared_dp_default_state
 * 
 * @brief   API used to set D+ to default state
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_shared_dp_default_state(void);

// ===========================================================================
/**
 * @function    usb_shared_dp_high
 * 
 * @brief   API used to set D+ high
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_shared_dp_high(void);





// ===========================================================================
/**
 * @function    usb_shared_uint32add_ovrflw
 * 
 * @brief   API used to detect unsigned 32bit int addition overflow
 * 
 * @param   None.
 * 
 * @return  TRUE.if overlfow is detected else FALSE
 * 
 */
// ===========================================================================

boolean usb_shared_uint32add_ovrflw(uint32 a, uint32 b);


//============================================================================

/**
* @function  usb_shared_get_platform
*
* @brief Read platforminfo from DAL API and cache it.
*
* @Note : None.
*
* @param None.
*
* @return None.
*
*/
//============================================================================
usb_platform_ctx usb_shared_get_platform(void);

boolean usb_shared_apb_read(uint8 addr, uint16* value);
boolean usb_shared_apb_write(uint8 addr, uint16 value);

boolean usb_shared_retimer_init(uint32 core_num, uint32 usb_mode, uint8 lane);
boolean usb_shared_repeater_init(uint32 core_num);
boolean usb_shared_repeater_reset(uint32 core_num);



#endif /*_USB_SHARED_LIB__H_*/
