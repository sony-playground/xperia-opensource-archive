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
/* SONY_BEGIN (Change PMIC pin assignment for key detection) */
#if 1
#define VOLUME_UP_BUTTON_GPIO            NOT_SUPPORTED
#define VOLUME_DOWN_BUTTON_GPIO          6
#else
#define VOLUME_UP_BUTTON_GPIO            6
#endif
/* SONY_END (Change PMIC pin assignment for key detection) */
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
/* SONY_BEGIN (Add Index for Volume Down Button) */
#if 1
   CAMERA_SNAPSHOT_BUTTON_GPIO,
   VOLUME_DOWN_BUTTON_GPIO};
#else
   CAMERA_SNAPSHOT_BUTTON_GPIO};
#endif
/* SONY_END (Add Index for Volume Down Button) */

const UINT16 ButtonsPmicIdxMap[] = {
   PMIC_B,
   PMIC_B,
   PMIC_B,
/* SONY_BEGIN (Add Pmic Index for Volume Down Button) */
#if 1
   PMIC_B,
   PMIC_B};
#else
   PMIC_B};
#endif
/* SONY_END (Add Pmic Index for Volume Down Button) */


typedef struct{
  IN UINT32                                     PmicDeviceIndex;
  IN EFI_PM_GPIO_PERIPH_INDEX                   Gpio;
  IN EFI_PM_GPIO_I_SRC_PULL_TYPE                ISourcePulls;
  IN EFI_PM_GPIO_VOLT_SRC_TYPE                  VoltageSource;
  IN EFI_PM_GPIO_OUT_DRV_STR_TYPE               OutBufferStrength;
  IN EFI_PM_GPIO_SRC_CFG_TYPE                   Source;
}ButtonPmicGpioCfg;

#if 0 /* this block is orignai code, but sony modification is not used volup settings*/
ButtonPmicGpioCfg VolUpButton = {
    .PmicDeviceIndex   = PMIC_B,
    .Gpio              = EFI_PM_GPIO_6,
    .ISourcePulls      = EFI_PM_GPIO_I_SRC_PULL_UP_30uA,
    .VoltageSource     = EFI_PM_GPIO_VIN1,
    .OutBufferStrength = EFI_PM_GPIO_OUT_DRV_STR_LOW,
    .Source            = EFI_PM_GPIO_SRC_GND,
};
#endif

/* SONY_BEGIN (Add Config for vol down button) */
ButtonPmicGpioCfg VolDownButton = {
    .PmicDeviceIndex   = PMIC_B,
    .Gpio              = EFI_PM_GPIO_6,
    .ISourcePulls      = EFI_PM_GPIO_I_SRC_PULL_UP_30uA,
    .VoltageSource     = EFI_PM_GPIO_VIN0,
    .OutBufferStrength = EFI_PM_GPIO_OUT_DRV_STR_LOW,
    .Source            = EFI_PM_GPIO_SRC_GND,
};
/* SONY_END (Add Config for vol down button) */


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
