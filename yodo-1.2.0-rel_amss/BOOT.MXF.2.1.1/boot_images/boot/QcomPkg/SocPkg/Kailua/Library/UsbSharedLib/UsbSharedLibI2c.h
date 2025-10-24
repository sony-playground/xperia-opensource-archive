/** @file UsbSharedLibI2c.h

  The public header file for UsbSharedLibI2c.c
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
 12/30/20   pw       Init Check-in
=============================================================================*/

#ifndef _USB_SHAREDLIB_I2C_H_
#define _USB_SHAREDLIB_I2C_H_


#include "i2c_api.h"
#include "UsbSharedLib.h"

typedef struct
{
    // member variables
    i2c_instance instance;
    i2c_slave_config config;
    boolean opened;
    void *i2c_handle;
} usb_i2c_ctx_type;

typedef enum
{
  USB_RETIMER_CORE_0,
  USB_RETIMER_CORE_1,
  USB_RETIMER_CORE_NUM_MAX
} usb_retimer_core_num_type;

typedef enum
{
  QUSB_TYPE_C_LANE_A = 0x0,
  QUSB_TYPE_C_LANE_B = 0x1,
  QUSB_TYPE_C_NO_LANE = 0x7FFFFFFF, 
} qusb_dci_type_c_lane_type;


boolean usb_shared_i2c_read(uint8 core_num, uint16 reg, uint8 *buffer);
boolean usb_shared_i2c_write(uint8 core_num, uint16 reg, uint8 data);

boolean usb_shared_kb8001_deinit(uint8 core_num);
boolean usb_shared_kb8001_init(uint8 core_num, USB4_MODE_TYPE usb_mode, uint32 cc_lane);

#endif /* _USB_SHAREDLIB_I2C_H_ */

