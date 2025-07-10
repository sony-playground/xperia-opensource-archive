/** @file UsbRepeater.h

  The public header file for UsbRepeater.c
  Copyright (c) 2016-2019 QUALCOMM Technologies Inc. All rights reserved.

**/
//============================================================================
/**
  Copyright (c) 2021 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
//============================================================================

/*=============================================================================
                              EDIT HISTORY

 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 09/09/21   pw       Init Check-in
=============================================================================*/

#ifndef _USB_REPEATER_H_
#define _USB_REPEATER_H_

// ===========================================================================
/**
 * @function    usb_repeater_init
 * 
 * @brief   This function start repeater driver
 * 
 * @param   core_num   -  which core repeater locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_repeater_init(uint8 core_num);

// ===========================================================================
/**
 * @function    usb_repeater_phy_tune
 * 
 * @brief   This function start repeater driver
 * 
 * @param   core_num   -  which core repeater locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_repeater_phy_tune(uint8 core_num, uint8 usb_mode);

// ===========================================================================
/**
 * @function    usb_repeater_reset
 * 
 * @brief   This function reset repeater driver
 * 
 * @param   core_num   -  which core repeater locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_repeater_reset(uint8 core_num);


#endif /* _USB_REPEATER_H_ */

