#ifndef QUSB_LDR_UTILS_H
#define QUSB_LDR_UTILS_H

/*=======================================================================*//**
 * @file        qusb_pbl_dload_check.h
 * @author:     kameya
 * @date        13-Feb-2015
 *
 * @brief       QUSB check to enter PBL DLOAD mode when D+ is grounded.
 *
 * @details     This file contains the declaration of PBL DLOAD check API.
 *
 *
 * @note        
 *
 *              Copyright 2015,2022 QUALCOMM Technologies Incorporated.
 *              All Rights Reserved.
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
// when          who        what, where, why
// --------   ---        ----------------------------------------------------------
// 02/13/15   kameya  Initial revision
//
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "com_dtypes.h"           // common defines - basic types as uint32 etc

//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------
#define USB_EUD_MIN_DELAY (1)


typedef enum
{
  CHECK_USB_D_PLUS_GROUND,
  CHECK_USB_D_PLUS_HIGH_WITH_TIMEOUT,
  CHECK_USB_REGULAR_CABLE,
  CHECK_USB_OPT_MAX
}qusb_ldr_fedl_usb_opt_type;



//----------------------------------------------------------------------------
// Function Declarations and Documentation
//----------------------------------------------------------------------------

// ===========================================================================
/**
 * @function    qusb_ldr_utils_fedl_check
 * 
 * @brief   This function will check if usb_opt to enter FEDL is met. 
 *          And if condition met then we go into EDL.
 *
 * @param   check_usb_opt  -  [IN] check usb type to enter edl
 *
 * @param   check_dp_timeout_ms  -  [IN] timeout for Checking DP high
 *
 * @return  boolean - returns whether we should enter PBL EDL mode.
 * 
 */
// ===========================================================================
boolean  qusb_ldr_utils_fedl_check(uint32 check_usb_opt, uint32 check_dp_timeout_ms);

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
void qusb_ldr_utils_handle_charger(void);

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
void qusb_ldr_utils_update_serial(void);

// ===========================================================================
/**
 * @function    qusb_ldr_utils_hs_phy_nondrive_mode_set
 * 
 * @brief   This function puts the HS PHY into non-drive mode with
 *          pull-up and pull-down on data lines disabled.
 *
 * 
 * @param   None.
 * 
 *
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_ldr_utils_hs_phy_nondrive_mode_set(void);

// ===========================================================================
/**
 * @function    qusb_ldr_eud_init
 * 
 * @brief   This function update serial number and enable EUD
 *
 * 
 * @param   None.
 * 
 *
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_ldr_eud_init(void);
typedef enum{
  USB_EUD_PERMISSION_NOT_ALLOW,

  // This is case where PBL enumerated in Super Speed for Flashless Boot or DevPrg.
  // If the EUD enumeration wait delay is too long (more than 3s) then even Super Speed
  // USB enumeration will get lost due to not handling CONTROL TRANSFER in time.
  USB_EUD_PERMISSION_ALLOW_WITH_MIN_DELAY,
  USB_EUD_PERMISSION_ALLOW,
  USB_EUD_PERMISSION_MAX,
}USB_EUD_PERMISSION_TYPE;

// ===========================================================================
/**
 * @function qusb_ldr_get_eud_permission
 * 
 * @brief This function return if EUD is allow to enumeration
 * 
 * @param None
 * 
 * @return USB_EUD_PERMISSION_TYPE 
 */
// ===========================================================================
USB_EUD_PERMISSION_TYPE qusb_ldr_get_eud_permission(void);


// ===========================================================================
/**
 * @function qusb_ldr_eud_reset_repeater
 * 
 * @brief This function return if EUD is allow to enumeration
 * 
 * @param None
 * 
 * @return None
 */
// ===========================================================================
void qusb_ldr_eud_reset_repeater(void);

#endif /* QUSB_PBL_DLOAD_CHECK_H */
