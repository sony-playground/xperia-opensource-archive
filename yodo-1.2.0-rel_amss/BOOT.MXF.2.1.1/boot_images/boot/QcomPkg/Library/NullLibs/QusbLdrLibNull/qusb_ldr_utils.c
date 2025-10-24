/*=======================================================================*//**
 * @file        qusb_ldr_utils.c
 * @author:     kameya
 * @date        11-Sept-2015
 *
 * @brief       Stub implementation to check forced PBL DLOAD mode 
 *              when D+ is grounded and to put USB PHY non-drive mode.
 *
 * @details     This file contains the implementation of the APIs to be used by
 *              as stub by device programmer.
 *
 * @note        
 *
 *              Copyright 2015,2020-2021 Qualcomm Technologies, Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Technologies, Inc Confidential and Proprietary
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
// 2021-03-15   pohanw   update ldr_utils api
// 2015-09-11   kameya   First Draft
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "com_dtypes.h"           // common defines - basic types as uint32 etc
#include "qusb_ldr_utils.h"
// ===========================================================================
/**
 * @function     qusb_ldr_utils_fedl_check
 * 
 * @brief   This function will check if usb_opt to enter FEDL is met. 
 *          And if condition met then we go into EDL.
 * 
 * @param   check_usb_opt - [IN] Check usb type for Force EDL
 *
 * @param   check_dp_timeout_ms   -  [IN] timeout for Checking DP high
 *
 * @return  TRUE: if it is connected to GND
 *          FALSE: if it is not connected to GND. 
 * 
 */
// ===========================================================================
boolean qusb_ldr_utils_fedl_check(uint32 check_usb_opt, uint32 check_dp_timeout_ms)
{
  return FALSE;
}
// ===========================================================================
/**
 * @function     qusb_ldr_utils_handle_charger
 * 
 * @brief   This function will check connection charger type and EUD status
 *          and proper enable EUD or toggle dp line for charger
 * 
 * @return  None
 * 
 */
// ===========================================================================
void qusb_ldr_utils_handle_charger(void)
{
  return;
}

// ===========================================================================
/**
 * @function    qusb_ldr_utils_update_serial
 * 
 * @brief   This function will update ram dump cookie to UFS/EMMC serial number 
 *          if ram dump cookie is not set.
 * 
 * @param   None
 * 
 * @return  None 
 * 
 */
// ===========================================================================
void qusb_ldr_utils_update_serial(void)
{
  return;
}

// ===========================================================================
/**
 * @function    qusb_ldr_utils_hs_phy_nondrive_mode_set
 * 
 * @brief   This function will put High Speed QUSB2.0 PHY 
 *          into non-drive state / mode.
 * 
 * @param   None
 * 
 * @return  None
 * 
 */
// ===========================================================================
void qusb_ldr_utils_hs_phy_nondrive_mode_set(void)
{
  return;
}


// ===========================================================================
/**
 * @function    qusb_ldr_eud_init
 * 
 * @brief   This function update serial number and Setup permission flag EUD
 *
 * 
 * @param   None.
 * 
 *
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_ldr_eud_init(void)
{
  return;
}

// ===========================================================================
/**
 * @function    qusb_ldr_get_eud_permission
 * 
 * @brief   This function return if EUD is allow to enumeration
 *
 * 
 * @param   None.
 * 
 *
 * @return  USB_EUD_PERMISSION_TYPE.
 * 
 */
// ===========================================================================
USB_EUD_PERMISSION_TYPE qusb_ldr_get_eud_permission(void)
{
  return USB_EUD_PERMISSION_ALLOW;
}


