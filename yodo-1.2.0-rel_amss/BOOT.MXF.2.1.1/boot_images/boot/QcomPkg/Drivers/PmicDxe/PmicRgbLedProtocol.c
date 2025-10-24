/*! @file PmicRgbLed.c 

 *  PMIC-RGB LED MODULE RELATED DECLARATION
 *  This file contains functions and variable declarations to support 
 *  the PMIC RGB Led module.
 *
 *  Copyright (c) 2012 - 2020  by QUALCOMM Technologies, Inc.  All Rights Reserved.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
08/05/16   va      Adding Charger led toggle protocol
07/01/14   al      Adding get_status 
06/20/14   al      Updated coypright info 
06/09/14   al      Arch update
13/12/13   aa      PmicLib Dec Addition
03/15/13   al	   Adding for 8974
08/09/12   sm      New file.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
/**
  EFI interfaces
 */
#include <Library/UefiLib.h>

/**
  PMIC Lib interfaces
 */
#include "pm_uefi.h"
#include "pm_app_rgb.h"

/**
  PMIC RGB LED interface
 */
#include "Protocol/EFIPmicRgbLed.h"

/*===========================================================================
                  EXTERNAL FUNCTION DECLARATIONS
===========================================================================*/
EFI_STATUS
EFIAPI
EFI_PmicRgbLedEnableLedDriver
(
   IN UINT32                          PmicDeviceIndex,
   IN EFI_PM_RGB_WHICH_TYPE           Rgb,
   IN UINT8                           Color,
   IN BOOLEAN                         Enable
   )
{
  return EFI_UNSUPPORTED;
}



EFI_STATUS
EFIAPI
EFI_PmicRgbLedGetStatus
(
  IN  UINT32                          PmicDeviceIndex,
  IN  EFI_PM_RGB_WHICH_TYPE           Rgb,
  OUT EFI_PM_RGB_STATUS_TYPE          *RgbStatus
)
{
  return EFI_UNSUPPORTED;
}


EFI_STATUS
EFIAPI
EFI_PmicConfigRgbLed
(
  IN  UINT32                          PmicDeviceIndex,
  IN  EFI_PM_RGB_WHICH_TYPE           Rgb,
  IN  UINT32                          RbgMask,
  IN  UINT32                          DimLevel,
  IN  BOOLEAN                         EnableRgb
)
{
  pm_err_flag_type  errFlag = PM_ERR_FLAG_SUCCESS;

  errFlag = pm_rgb_led_config(RbgMask, DimLevel, EnableRgb);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicBlinkLed
(
  IN UINT32 RgbMask,
  IN UINT32 DimLevel
)
{
  pm_err_flag_type  errFlag = PM_ERR_FLAG_SUCCESS;

  errFlag = pm_rgb_led_blink(RgbMask, DimLevel);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
  
}

/**
  PMIC RGB Led UEFI Protocol implementation
 */
EFI_QCOM_PMIC_RGB_LED_PROTOCOL PmicRgbLedProtocolImplementation =
{
  .Revision = PMIC_RGB_LED_REVISION,
  .EnableLedDriver = EFI_PmicRgbLedEnableLedDriver,
  .GetStatus = EFI_PmicRgbLedGetStatus,
  .ConfigRgbLed = EFI_PmicConfigRgbLed,
  .BlinkLed = EFI_PmicBlinkLed
};
