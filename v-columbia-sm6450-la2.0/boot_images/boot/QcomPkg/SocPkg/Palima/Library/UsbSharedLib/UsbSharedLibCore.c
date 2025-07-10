/*=======================================================================*//**
 * @file        UsbSharedCore.c
 * @author:     Pmahajan
 * @date        03-feb-2017
 *
 * @brief       USB common & shared USB core init implementation.
 *
 * @details     This file contains API's the Init sequence for HS and SS core implementation.
 *
 * @note        
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2016-2018,2021 Qualcomm Technologies, Inc. All rights reserved.
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
//06/14/17      amitg    Cleanup
// 02/03/17     pm 	     Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include "UsbSharedLib.h"
#include "DDIChipInfo.h"
#include "DDIPlatformInfo.h"
#include "UsbSharedLibI2c.h"
#include "UsbRetimer.h"
#include "UsbRedriver.h"
#include "UsbRepeater.h"

//#include "UsbPwrCtrlLibPmGpio.h"
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/UsbPwrCtrlLib.h>
#include <Protocol/EFIUsbPwrCtrl.h>
#include <Protocol/EFIPmicGpio.h>


//----------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------
void usb_shared_delay_us(uint32 usecs) {
  gBS->Stall (MICRO_STALL_UNITS(usecs));
}

void usb_shared_loop_here(void) { 
  static volatile uint32 loop_here = 0x1; 

  while(loop_here);
}

void usb_shared_uart_log_info(char *message) { 
  DebugPrint(EFI_D_INFO,"%a\n", message);
}

void usb_shared_uart_log_info1(char *message, uint32 value) {
  DebugPrint(EFI_D_INFO,"%a, %d\n", message, value);
}

void usb_shared_uart_log_warn(char *message, uint32 value) { 
  DebugPrint(EFI_D_ERROR, "%a: %d\n", message, value);
}

void usb_shared_uart_log_error(char *message, uint32 value) { 
  DebugPrint(EFI_D_ERROR, "%a: %d\n", message, value);
}

void usb_shared_error_log(uint32 id_0, uint8 offset, uint32 param) {
  return;
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
  DalDeviceHandle                  *phPlatformInfo   = NULL;
  DALResult                         eResult; 
  DalPlatformInfoPlatformInfoType   platformInfo;
  static usb_platform_ctx usb_platform= {DALPLATFORMINFO_TYPE_32BITS, 0};  //init value will only get platform once
  
  if (usb_platform.platform == DALPLATFORMINFO_TYPE_32BITS)
  {
    /* Initialize DALSYS and attach to the DAL TLMM driver. */
    DALSYS_InitMod(NULL);

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
        usb_platform.platform = DALPLATFORMINFO_TYPE_UNKNOWN;
        usb_platform.subtype = 0;
      }
      else
      {
        usb_platform.platform = platformInfo.platform;
        usb_platform.subtype = platformInfo.subtype;
      }

      eResult = DAL_DeviceDetach(phPlatformInfo);
      if (eResult != DAL_SUCCESS)
      {
        usb_shared_uart_log_error("platform: detach failed", eResult);
      }
    }
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
STATIC EFI_QCOM_PMIC_GPIO_PROTOCOL *PmicGpioProtocol = NULL;

boolean usb_shared_repeater_reset(uint32 core_num)
{

  EFI_STATUS Status = EFI_SUCCESS;
  usb_shared_uart_log_error("usb_shared_repeater_reset", core_num);

  if (!PmicGpioProtocol)
  {
    Status = gBS->LocateProtocol(&gQcomPmicGpioProtocolGuid, NULL, (void **)&PmicGpioProtocol);
    if (EFI_ERROR(Status))
    {
      PmicGpioProtocol = NULL;
      usb_shared_uart_log_error("Failed to open PMIC GPIO protocol Status", core_num);
      return FALSE;
    }
  }
  if (PmicGpioProtocol)
  {
    /* Reset eUSB repeater using PM_GPIO_7 on Palani PMIC */
    Status = PmicGpioProtocol->Enable(PMIC_INDEX_FOR_GPIO, EFI_PM_GPIO_7, FALSE);
    usb_shared_delay_us(20);  
    Status = PmicGpioProtocol->Enable(PMIC_INDEX_FOR_GPIO, EFI_PM_GPIO_7, TRUE);
  }
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

