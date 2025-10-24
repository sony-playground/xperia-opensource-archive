/*===========================================================================

                    BOOT USB DLOAD IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external usb dload drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2019,2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who      what, where, why
--------    ---      ----------------------------------------------------------
03/15/2021  pw       update usb_ldr_utils api
08/05/2019  ep       Created the file.

===========================================================================*/

/*
  Note: Only qusb_pbl_dload_check api from USB driver to be used in XBL loader
  to check if USB D+ line is grounded. Rest of the USB driver is in
  XBL ramdump image.
*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"
#include "com_dtypes.h"           // common defines - basic types as uint32 etc
#include "boot_qusb_ldr_if.h"
#include "qusb_ldr_utils.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

/*===========================================================================

**  Function :  boot_qusb_ldr_utils_update_serial

** ==========================================================================
*/
/*!
 *
 * @function    boot_qusb_ldr_utils_update_serial
 *
 * @brief   This function will update ram dump cookie to UFS/EMMC serial number
 *          if ram dump cookie is not set.
 *
 * @param   None
 *
 * @return
 *
 */
void boot_qusb_ldr_utils_update_serial(void)
{
  qusb_ldr_utils_update_serial();
}

/*===========================================================================

**  Function :  boot_qusb_ldr_utils_handle_charger

** ==========================================================================
*/
/*!
 *
 * @function     boot_qusb_ldr_utils_handle_charger
 *
 * @brief   This function will check connection charger type and EUD status
 *          and proper enable EUD or toggle dp line for charger
 *
 * @return  None
 *
 */
void boot_qusb_ldr_utils_handle_charger(void)
{
  qusb_ldr_utils_handle_charger();
}

/*===========================================================================

**  Function :  boot_qusb_ldr_utils_fedl_check

** ==========================================================================
*/
/*!
 *
 * @brief   This function checks if the USB D+ line is grounded.
 *
 * @param check_usb_opt - [IN] Check usb opt for Force EDL
 *
 * @param check_dp_timeout_ms - [IN] timeout for Checking DP high
 *
 * @return  boolean - returns whether we should enter PBL EDL mode.
 *
 */
boolean boot_qusb_ldr_utils_fedl_check(uint32 check_usb_opt, uint32 check_dp_timeout_ms)
{
   return qusb_ldr_utils_fedl_check(check_usb_opt, check_dp_timeout_ms);
}

/*===========================================================================

**  Function :  boot_qusb_ldr_utils_hs_phy_nondrive_mode_set

** ==========================================================================
*/
/*!
 *
 * @brief   This function puts USB phy in nondrive mode.
 *
 *
 * @param   None.
 *
 *
 * @return  None.
 *
 */
void boot_qusb_ldr_utils_hs_phy_nondrive_mode_set(void)
{
  qusb_ldr_utils_hs_phy_nondrive_mode_set();
}


/*===========================================================================
**  Function :  boot_clk_get_interface
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes a boot_qusb_ldr_get_interface
*
* @par Dependencies
*   None
*
*/
/*
bl_error_boot_type boot_qusb_ldr_get_interface(boot_qusb_ldr_if_type *qusb_ldr_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(qusb_ldr_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_QUSB_LDR, BL_ERR_INVALID_PARAMETER);
      break;
    }

    qusb_ldr_if->utils_fedl_check = qusb_ldr_utils_fedl_check;
    qusb_ldr_if->utils_hs_phy_nondrive_mode_set = qusb_ldr_utils_hs_phy_nondrive_mode_set;

  } while(FALSE);

  return return_status;
}
*/


boot_qusb_ldr_if_type qusb_ldr_if =
{
  .utils_update_serial = qusb_ldr_utils_update_serial,
  .utils_handle_charger = qusb_ldr_utils_handle_charger,
  .utils_fedl_check = qusb_ldr_utils_fedl_check,
  .utils_hs_phy_nondrive_mode_set = qusb_ldr_utils_hs_phy_nondrive_mode_set,
  .eud_init = qusb_ldr_eud_init
};

