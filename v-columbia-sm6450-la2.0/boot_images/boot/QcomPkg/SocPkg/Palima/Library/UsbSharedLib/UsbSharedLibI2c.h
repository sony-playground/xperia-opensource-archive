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

#define USB_ONSEMI_REDRIVER_FLAG (1)
#define USB_KB8001_RETIMER_FLAG  (0)

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
  USB_I2C_CORE_0,
#ifdef USB_SEC_FLAG
  USB_I2C_CORE_1,
#endif
  USB_I2C_CORE_NUM_MAX
} usb_i2c_core_num_type;


boolean usb_shared_i2c_write(usb_i2c_ctx_type* i2c_ctx, uint8 reg, uint8 data, uint8 reg_size);

boolean usb_shared_i2c_read(usb_i2c_ctx_type* i2c_ctx, uint8 reg, uint8 *buffer, uint8 reg_size);

void usb_i2c_ctx_init(usb_i2c_ctx_type* i2c_ctx);


#endif /* _USB_SHAREDLIB_I2C_H_ */

