/** @file UsbRedriver.h

  The public header file for UsbSharedLibRedriver.c
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

#ifndef _USB_REDRIVER_H_
#define _USB_REDRIVER_H_

// ===========================================================================
/**
 * @function    usb_redriver_init
 * 
 * @brief   This function start redriver driver
 * 
 * @param   core_num   -  which core redriver locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_redriver_init(uint32 core_num);

// ===========================================================================
/**
 * @function    usb_redriver_set_usb_mode
 * 
 * @brief   This function set usb mode for redriver
 * 
 * @param   core_num   -  which core redriver locate
 * @param   usb_mode   -  which mode usb should set to.
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_redriver_set_usb_mode(uint32 core_num, uint32 usb_mode);


#endif /* _USB_REDRIVER_H_ */


