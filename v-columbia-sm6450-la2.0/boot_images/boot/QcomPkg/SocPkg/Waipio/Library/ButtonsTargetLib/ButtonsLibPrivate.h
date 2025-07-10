#ifndef __BUTTONSLIBPRIVATE_H__
#define __BUTTONSLIBPRIVATE_H__

/** @file
ButtonsLibPrivate.h

  Buttons library internal defines

  Copyright (c) 2012-2020 Qualcomm Technologies, Inc. All rights reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/04/16   ma      Port to 8998
===========================================================================*/

#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/SimpleTextInEx.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFIPmicPwrOn.h>
#include <api/pmic/pm/pm_version.h> 

// GPIO Numbers
#define NOT_SUPPORTED                    0
#define VOLUME_UP_BUTTON_GPIO            6
#define HOME_BUTTON_GPIO                 NOT_SUPPORTED
#define CAMERA_SNAPSHOT_BUTTON_GPIO      NOT_SUPPORTED

// SDAM storage location for the button press
#define BUTTONS_LIB_SDAM_PMIDX           0
#define BUTTONS_LIB_SDAM_NUM             2
#define BUTTONS_LIB_SDAM_ADDR            76


const UINT16 ButtonsGPIOMap[] = {
   NOT_SUPPORTED,
   VOLUME_UP_BUTTON_GPIO,
   HOME_BUTTON_GPIO,
   CAMERA_SNAPSHOT_BUTTON_GPIO};

const UINT16 ButtonsPmicIdxMap[] = {
   PMIC_B,
   PMIC_B,
   PMIC_B,
   PMIC_B};


typedef struct{
  IN UINT32                                     PmicDeviceIndex;
  IN EFI_PM_GPIO_PERIPH_INDEX                   Gpio;
  IN EFI_PM_GPIO_I_SRC_PULL_TYPE                ISourcePulls;
  IN EFI_PM_GPIO_VOLT_SRC_TYPE                  VoltageSource;
  IN EFI_PM_GPIO_OUT_DRV_STR_TYPE               OutBufferStrength;
  IN EFI_PM_GPIO_SRC_CFG_TYPE                   Source;
}ButtonPmicGpioCfg;

ButtonPmicGpioCfg VolUpButton = {
    .PmicDeviceIndex   = PMIC_B,
    .Gpio              = EFI_PM_GPIO_6,
    .ISourcePulls      = EFI_PM_GPIO_I_SRC_PULL_UP_30uA,
    .VoltageSource     = EFI_PM_GPIO_VIN1,
    .OutBufferStrength = EFI_PM_GPIO_OUT_DRV_STR_LOW,
    .Source            = EFI_PM_GPIO_SRC_GND,
};

ButtonPmicGpioCfg HomeButton = {
    .PmicDeviceIndex   = PMIC_B,
    .Gpio              = EFI_PM_GPIO_1,
    .ISourcePulls      = EFI_PM_GPIO_I_SRC_PULL_UP_30uA,
    .VoltageSource     = EFI_PM_GPIO_VIN1,
    .OutBufferStrength = EFI_PM_GPIO_OUT_DRV_STR_LOW,
    .Source            = EFI_PM_GPIO_SRC_GND,
};

ButtonPmicGpioCfg CameraButton = {
    .PmicDeviceIndex   = PMIC_B,
    .Gpio              = EFI_PM_GPIO_INVALID,
    .ISourcePulls      = EFI_PM_GPIO_I_SRC_PULL_UP_30uA,
    .VoltageSource     = EFI_PM_GPIO_VIN1,
    .OutBufferStrength = EFI_PM_GPIO_OUT_DRV_STR_LOW,
    .Source            = EFI_PM_GPIO_SRC_GND,
};


#endif /* __BUTTONSLIBPRIVATE_H__ */
