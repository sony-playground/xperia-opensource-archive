/*=======================================================================*//**
 * @file        qusb_dci_common.h
 * @author:     kameya
 * @date        13-Mar-2012
 *
 * @brief       QUSB (Qualcomm High-Speed USB) Logging implementation.
 *
 * @details     This file contains the implementation of the APIs to be used by
 *              the boot Sahara downloader.
 *
 * @note        
 *
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2012-2015, 2017-2018,2021 Qualcomm Technologies, Inc. All rights reserved.
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
// 02/13/18	gk	   Port changes from boot.xf.2.0 and boot.xf.2.2
// 02/06/17	  pm			Add UsbSharedLib
// 06/13/12   shreyasr 		Initial revision
//
// ===========================================================================

#ifndef _QUSB_DCI_COMMON__H_
#define _QUSB_DCI_COMMON__H_

#include "UsbSharedLib.h"
#include "qusb_common.h"
#define QUSB_DLOAD_INFO_ADDR_IN_IMEM            (SHARED_IMEM_USB_BASE)

typedef enum 
{
  QUSB_DCI_PLATFORM_UNKNOWN,
  QUSB_DCI_PLATFORM_RUMI,
  QUSB_DCI_PLATFORM_VIRTIO,
  QUSB_DCI_PLATFORM_SILICON,
  QUSB_DCI_PLATFORM_MAX,
} qusb_dci_platform_type;

//============================================================================

/**
* @function  qusb_dci_get_platform
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
qusb_dci_platform_type qusb_dci_get_platform(void);

//============================================================================

/**
* @function  qusb_dci_delay_ms
*
* @brief Perform delay in milliseconds.
*
* @Note : The USB Timers can not be used before the core is initialized.
*
* @param milliseconds
*
* @return none
*
*/
//============================================================================
void qusb_dci_delay_ms(uint32 msecs);

//============================================================================
/**
* @function  qusb_dci_delay_us
*
* @brief Perform delay in microseconds.
*
* @Note : The USB Timers can not be used before the core is initialized.
*
* @param microseconds
*
* @return none
*
*/
//============================================================================
void qusb_dci_delay_us(uint32 usecs);

// ===========================================================================
/**
 * @function    qusb_hs_phy_gcc_reset
 * 
 * @brief   API used for resetting High Speed QUSB2 PHY using GCC control
 *  
 * @details API is used for resetting High Speed QUSB2 PHY using GCC control
 * 
 * @param   None.
 *
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_hs_phy_gcc_reset(void);

// ===========================================================================
/**
 * @function    qusb_dci_usb30_gcc_reset
 * 
 * @brief   API used for resetting the Link and PHYs using GCC control
 *  
 * @details This API is used for resetting the Link and PHYs using clock control 
 * 
 * @param   boolean is_eud_active - pass if EUD is active, so PHY reset can
 *                                  be skipped.
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_usb30_gcc_reset(boolean is_eud_active);

// ===========================================================================
/**
 * @function    qusb_hs_phy_refclk_enable
 * 
 * @brief   This function will be used to enable / disable HS PHY reference clock.
 * 
 * @param  TRUE or FALSE depending on enable or disable.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_hs_phy_refclk_enable(boolean enable);

// ===========================================================================
/**
 * @function    qusb_dci_select_utmi_clk
 * 
 * @brief   This is used for configuring the core to UTMI clock instead of pipe
 *          clock.  This needs to be called when there is no SS USB PHY.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_select_utmi_clk(void);

// ===========================================================================
/**
 * @function    qusb_dci_hs_phy_update_hstx_trim
 * 
 * @brief   This function will update TUNE2 HSTX_TRIM register bits if feature is enabled.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_hs_phy_update_hstx_trim(void);

// ===========================================================================
/**
 * @function    qusb_dci_ahb2phy_cfg
 * 
 * @brief   Configures AHB2PHY read/write states to be 1 wait cycle each.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_ahb2phy_cfg(void);

// ===========================================================================
/**
 * @function    qusb_hs_phy_init
 * 
 * @brief   API used to initialize the High Speed PHY.
 * 
 * @param   None.
 * 
 * @return  TRUE if PHY initializes successfully, FALSE otherwise.
 * 
 */
// ===========================================================================
boolean qusb_hs_phy_init(void);

// =============================================================================
/**
 * @function    qusb_dci_dp_gnd_check
 * 
 * @brief   API used to check if D+ is grounded.
 *
 * @param   check_dp_high   -  [IN] Check DP High for Force EDL
 *
 * @param   check_dp_timeout_ms   -  [IN] timeout for Checking DP high
 *
 * 
 * @return  None.
 * 
 */
// =============================================================================
boolean qusb_dci_dp_gnd_check(boolean check_dp_high, uint32 check_dp_timeout_ms);

// ===========================================================================
/**
 * @function    qusb_dci_dp_toggle
 * 
 * @brief   API used to toggle D+ high then low for interval in milliseconds
 * 
 * @param   interval_ms   interval in milliseconds
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_dp_toggle(uint32 interval_ms);

// =============================================================================
/**
 * @function    qusb_hs_phy_nondrive_cfg
 * 
 * @brief   Function used to configure High Speed PHY in non-drive mode.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// =============================================================================
void qusb_hs_phy_nondrive_cfg(void);

// ===========================================================================
/**
 * @function    qusb_dci_eud_phy_tune
 * 
 * @brief       This function will populate QUSB2PHY registers onto EUD mode 
 *              manager CSR.
 * 
 * @param   none.
 * 
 * @return  TRUE if the tune was written to EUD regier successfuly.
 *          FALSE otherwise.
 * 
 */
// ===========================================================================
void qusb_dci_eud_phy_tune(void);

// ===========================================================================
/**
 * @function    qusb_dci_eud_init
 * 
 * @brief       This function wirte to sw_attch bit of EUD to prevent 
 *              transition to safe mode.
 * 
 * @param   none.
 * 
 * @return  none.
 * 
 */
// ===========================================================================
void qusb_dci_eud_init(void);

// ===========================================================================
/**
 * @function    qusb_dci_enable_usb2_ldo
 * 
 * @brief   This function will be used to turn ON the USB2 LDO
 * 
 * @param   None
 * 
 * @return  TRUE or FALSE depending on success or failure.
 * 
 */
// ===========================================================================
void qusb_dci_enable_usb2_ldo(boolean enable);

// ===========================================================================
/**
 * @function    usb_dci_mem_free
 * 
 * @brief   This function free memory
 * 
 * @param   void* mem_ptr - pointer to free memory
 * 
 * @return  TRUE or FALSE depending on success or failure.
 * 
 */
// ===========================================================================
boolean usb_dci_mem_free(void* mem_ptr);

// ===========================================================================
/**
 * @function    usb_dci_mem_allocate
 * 
 * @brief   This function allocate memory from align uncached memory
 * 
 * @param   void** mem_ptr - pointer for allocate memory
 *          uint32 size    - size of memory to allocate
 * 
 * @return  TRUE or FALSE depending on success or failure.
 
 * 
 */
// ===========================================================================
boolean usb_dci_mem_allocate(void** mem_ptr, uint32 size);

// ===========================================================================
/**
 * @function    usb_dci_mem_debug
 * 
 * @brief   This function print all the memory that is allocate
 * 
 * @param   None
 * 
 * @return  
 * 
 */
// ===========================================================================
void usb_dci_mem_debug(void);

// ===========================================================================
/**
 * @function    usb_dci_mem_handle_free
 * 
 * @brief   This function init memory handle
 * 
 * @param   None
 * 
 * @return  
 * 
 */
// ===========================================================================
void usb_dci_mem_handle_init(void);
  
// ===========================================================================
/**
 * @function    usb_dci_mem_handle_free
 * 
 * @brief   This function free all memory and clean memory handle
 * 
 * @param   None
 * 
 * @return  
 * 
 */
// ===========================================================================
boolean usb_dci_mem_handle_free(void);

//============================================================================
/**
 * @function  qusb_dci_get_speed
 *
 * @brief Report the USB connection speed.
 *
 * @Note : Although the device is high-speed, the Host might be full-speed.
 *
 * @Note : The USB HW can be forced to Full-Speed.
 *
 * @param None 
 * @return Speed
 *              QUSB_SPEED_FULL        
 *              QUSB_SPEED_LOW         
 *              QUSB_SPEED_HIGH        
 *              QUSB_SPEED_FULL
 *              QUSB_SPEED_UNKNOWN     
 *
 * @ref SNPS spec 
 *       Chapter 6.3.1.4 DSTS ( bits 0-2)
 *
 */
//============================================================================
qusb_device_connect_speed_t qusb_dci_get_speed(void);

#endif /*_QUSB_DCI_COMMON__H_*/
