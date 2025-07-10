/** @file UsbSharedLibRetimer.h

  The public header file for UsbSharedLibRetimer.c
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

#ifndef _USB_SHAREDLIB_RETIMER_H_
#define _USB_SHAREDLIB_RETIMER_H_


boolean usb_shared_kb8001_deinit(uint8 core_num);
boolean usb_shared_kb8001_init(uint8 core_num, USB4_MODE_TYPE usb_mode, uint32 cc_lane);

boolean usb_retimer_init(uint32 core_num, uint32 usb_mode, uint8 lane);

#endif /* _USB_SHAREDLIB_RETIMER_H_ */

