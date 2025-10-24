/*=======================================================================*//**
 * @file        UsbSharedInit.c
 * @author:     pmahajan
 * @date        03-feb-2017
 *
 * @brief       USB common & shared USB core init implementation.
 *
 * @details     This file contains API's the Init sequence for HS and SS core implementation.
 *
 * @note        Copyright (c) 2017,2021, Qualcomm Technologies, Inc. All rights reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/

// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// 
// when          who     what, where, why
// ----------   -----    ----------------------------------------------------------
// 05/18/17     vk       Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "UsbSharedLib.h"

// ===========================================================================
/**
 * @function    usb_shared_lib_process_phy_reg_array
 * 
 * @brief   This function reads from array which define list of hwio writes for
 *          USB PHY
 * 
 * @param   address_array   - array holding address of HW register
 *          value_array     - array holding values to be written to HW register
 *          start_index     - starting index for array processing
 *          array_entry_cnt - number of entries in the array
 * 
 * @return  None
 * 
 */
// ===========================================================================
static void usb_shared_lib_process_phy_reg_array
(
  const uint32 *address_array, 
  const uint8  *value_array, 
  uint32        start_index, 
  uint32        array_entry_cnt
)
{
}

//============================================================================

/**
* @function USB_SHARED_HS_PHY_INIT
*
* @brief    API used to initialize the High Speed Primary PHY 
*
*/
//============================================================================
boolean usb_shared_hs_phy_init()
{
    return FALSE;
}


//============================================================================

/**
* @function USB_SHARED_HS_PHY_INIT_SEC
*
* @brief    API used to initialize the High Speed Secondary PHY 
*
*/
//============================================================================
boolean usb_shared_hs_phy_init_sec()
{
    return FALSE;
}


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
boolean usb_shared_hs_phy_rumi_init(uint32 core_num, uint32 phy_num)
{
  return FALSE;
}

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
boolean usb_shared_ss_phy_init(uint32 usb_ss_phy_lane)
{
  return FALSE;
}
// ===========================================================================
/**
 * @function    qusb_dci_usbdp_mode_reset
 * 
 * @brief   API to reset usbdp mux to usb
 * 
 * @param   usb_ss_phy_lane: 0 - LANE_A and nonzero = LANE_B
 * 
 * @return  None
 * 
 */
// ===========================================================================
void qusb_dci_usbdp_mode_reset(uint32 usb_ss_phy_lane)
{
  return;
}
// ===========================================================================
/**
 * @function    qusb_dci_eud_recovery
 * 
 * @brief   API used recover EUD, by resetting EUD.
 *  
 * @details Trigger EUD reset using USB 3p1 rising edge.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_eud_recovery(void)
{
    return;
}

//============================================================================

/**
* @function USB_SHARED_SS_PHY_INIT_SEC
*
* @brief    API used to initialize the Super Speed Secondary PHY 
*
*/
//============================================================================
boolean usb_shared_ss_phy_init_sec()
{
  return FALSE;
}


//============================================================================
/**
* @function  usb_dci_get_chip_serial_number
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
uint32 usb_shared_get_chip_serial_number(void)
{
  return 0;
}


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
uint32 usb_shared_get_chip_id(void)
{
  return 0;
}

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
uint32 usb_shared_get_product_str_desc_with_chip_serial(char* product_str, char* prod_str_desc, uint32 desc_len)
{
  return 0;
}


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
void usb_shared_dp_high(void)
{
  return;
}


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
void usb_shared_dp_default_state(void)
{ 
  return;
}


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
void usb_shared_dp_toggle(uint32 interval_ms)
{
  return;
}

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
boolean usb_shared_is_run_stop_active(void)
{
  return FALSE;
}

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
void usb_shared_refclk_enable(boolean bEnable)
{
  return;
} // end usb_shared_refclk_enable



