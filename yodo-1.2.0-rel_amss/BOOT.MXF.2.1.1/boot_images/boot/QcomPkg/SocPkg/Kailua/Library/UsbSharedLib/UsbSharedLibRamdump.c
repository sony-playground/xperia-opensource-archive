/*=======================================================================*//**
 * @file        UsbSharedLoader.c
 * @author:     pmahajan
 * @date        03-feb-2017
 *
 * @brief       USB common & shared USB core init implementation.
 *
 * @details     This file contains API's the Init sequence for HS and SS core implementation.
 *
 * @note        
 *              Copyright 2017 QUALCOMM Technologies Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2016-2017,2021 Qualcomm Technologies, Inc. All rights reserved.
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
// when          who     what, where, why
// ----------   -----    ----------------------------------------------------------
// 02/03/17     pm 	     Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "UsbSharedLib.h"
#include "qusb_log.h"
#include "qusb_dci_common.h"
#include "DDIChipInfo.h"
#include "DDIPlatformInfo.h"
#include "UsbSharedLibI2c.h"

//----------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------
#define USB_SHARED_PLATFORM_QRD_SUBTYPE__RETIMER (0x3)

volatile boolean usb_shared_enable_retimer_support = FALSE;


void usb_shared_delay_us(uint32 usecs) {
  qusb_dci_delay_us(usecs);
}

void usb_shared_loop_here(void) {
  static volatile uint32 loop_here = 0x1; 
  while(loop_here);
}

void usb_shared_uart_log_info(char *message) {
  return;
}
void usb_shared_uart_log_info1(char *message, uint32 value) {
  return;
}

void usb_shared_uart_log_warn(char *message, uint32 value) {
  qusb_uart_log(message, value);
}

void usb_shared_uart_log_error(char *message, uint32 value) {
  qusb_uart_log(message, value);
}

void usb_shared_error_log(uint32 id_0, uint8 offset, uint32 param) {
  qusb_error_log((qusb_log_enum)id_0, offset, param);
}

uint32 usb_shared_get_chip_revision(void) {
  return (uint32)DalChipInfo_ChipVersion();
}


boolean usb_shared_retimer_init(uint32 core_num, uint32 usb_mode, uint8 lane)
{
  boolean                           retimer_result   = FALSE;
#if 0
  DalDeviceHandle                  *phPlatformInfo   = NULL;
  DALResult                         eResult; 
  DalPlatformInfoPlatformInfoType   platformInfo;
  platformInfo.platform = DALPLATFORMINFO_TYPE_UNKNOWN;
  platformInfo.subtype  = 0;

  eResult = DAL_DeviceAttach(DALDEVICEID_PLATFORMINFO, &phPlatformInfo);
  if (eResult != DAL_SUCCESS) 
  {
    usb_shared_uart_log_error("platform: attach failed", eResult);
  }
  else
  {
    eResult = DalPlatformInfo_GetPlatformInfo(phPlatformInfo, &platformInfo);
    if (eResult != DAL_SUCCESS)
    {
      usb_shared_uart_log_error("platform: get failed", eResult);
    }

    eResult = DAL_DeviceDetach(phPlatformInfo);
    if (eResult != DAL_SUCCESS)
    {
      usb_shared_uart_log_error("platform: detach failed", eResult);
    }
  }

  usb_shared_uart_log_error("retimer, platform", 
    ((platformInfo.platform * 10000) | platformInfo.subtype));
  
  if ( usb_shared_enable_retimer_support
    && (platformInfo.platform == DALPLATFORMINFO_TYPE_QRD) 
    && (platformInfo.subtype  == USB_SHARED_PLATFORM_QRD_SUBTYPE__RETIMER) )
  {
    if (USB_RETIMER_CORE_0 == core_num)
    {
      retimer_result = usb_shared_kb8001_init(USB_RETIMER_CORE_0, usb_mode, lane);
    }
    else if (USB_RETIMER_CORE_1 == core_num)
    {
      retimer_result = usb_shared_kb8001_init(USB_RETIMER_CORE_1, usb_mode, lane);
    }
  }
#endif
  return retimer_result;
}


boolean usb_shared_repeater_init(uint32 core_num)
{
  return TRUE;
}

