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
#include "UsbRetimer.h"
#include "UsbRedriver.h"
#include "UsbRepeater.h"
#include "pm_gpio.h"

//----------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------
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


//============================================================================

/**
* @function  usb_shared_get_platform
*
* @brief Read platforminfo from DAL API and cache it.
*
* @Note : None.
*
* @param None.
*
* @return None.
*
*/
//============================================================================
usb_platform_ctx usb_shared_get_platform(void)
{
  static usb_platform_ctx usb_platform= {DALPLATFORMINFO_TYPE_32BITS, 0};  //init value will only get platform once
  if (usb_platform.platform == DALPLATFORMINFO_TYPE_32BITS)
  {
    usb_platform.platform = PlatformInfo_Platform();
    usb_platform.subtype  = PlatformInfo_PlatformSubtype();
    usb_shared_uart_log_error("platform: ", 
      ((usb_platform.platform * 10000) | usb_platform.subtype));
  }
  return usb_platform;
}


boolean usb_shared_retimer_init(uint32 core_num, uint32 usb_mode, uint8 lane)
{
  return usb_retimer_init(core_num, usb_mode, lane);
}

boolean usb_shared_repeater_init(uint32 core_num)
{
  return usb_repeater_init(core_num);
}

#if  USB_REPEATER_RESET_NULL
boolean usb_shared_repeater_reset(uint32 core_num)
{
  return TRUE;
}
#else

#define PMIC_INDEX_FOR_GPIO (2)
boolean usb_shared_repeater_reset(uint32 core_num)
{
  usb_shared_uart_log_error("repeater_reset: ",core_num);
  /* 
   * Reset eUSB repeater using PM_GPIO_7 on Palani PMIC
   * set GPIO07_DIG_OUT_SOURCE_CTL to 0x80 using set_output_level
   * set GPIO07_EN_CTL to 0x1 to enable gpio
   */
  pm_gpio_enable(PMIC_INDEX_FOR_GPIO, PM_GPIO_7, TRUE);
  pm_gpio_set_output_level(PMIC_INDEX_FOR_GPIO, PM_GPIO_7, PM_GPIO_LEVEL_HIGH);
  usb_shared_delay_us(20);
  return TRUE;
}
#endif  


boolean usb_shared_redriver_init(uint32 core_num, uint32 usb_mode, uint8 lane)
{
  return usb_redriver_init(core_num);
}
boolean usb_shared_redriver_set_usb_mode(uint32 core_num, uint32 usb_mode, uint8 lane)
{
  return usb_redriver_set_usb_mode(core_num, usb_mode);
}

