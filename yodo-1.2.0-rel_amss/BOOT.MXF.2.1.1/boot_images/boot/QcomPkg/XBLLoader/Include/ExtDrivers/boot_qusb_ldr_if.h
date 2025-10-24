#ifndef BOOT_QUSB_EDL_IF_H
#define BOOT_QUSB_EDL_IF_H
/*===========================================================================

                    BOOT QUSB IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external QUSB drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

    
when        who      what, where, why
--------    ---      ----------------------------------------------------------
03/15/2021  pw       seperate the FEDL api
08/05/2019  ep       Created the file
===========================================================================*/

/*
  Note: Only qusb_pbl_dload_check api from USB driver to be used in XBL loader
  to check if USB D+ line is grounded. Rest of the USB driver is in
  XBL ramdump image.
*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/


typedef struct boot_qusb_ldr_if_type
{
  void (*utils_update_serial)(void);
  void (*utils_handle_charger)(void);
  boolean (*utils_fedl_check)(uint32 check_usb_opt, uint32 check_dp_timeout_ms);
  void (*utils_hs_phy_nondrive_mode_set)(void);
  void (*eud_init)(void);
} boot_qusb_ldr_if_type;


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

//bl_error_boot_type boot_qusb_ldr_get_interface(boot_qusb_ldr_if_type *qusb_ldr_if);


extern boot_qusb_ldr_if_type qusb_ldr_if;


#endif /* BOOT_QUSB_EDL_IF_H*/
