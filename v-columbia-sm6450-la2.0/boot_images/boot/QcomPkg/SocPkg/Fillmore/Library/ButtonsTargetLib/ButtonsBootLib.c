/** @file
ButtonsBootLib.c

Boot Button driver is responsible for detecting key press/release through PMIC HW
and service. The key press is recorded into SMEM so UEFI can read it back.


Copyright (c) 2019-2020 Qualcomm Technologies, Inc. All rights reserved.
Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
EDIT HISTORY

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when        who      what, where, why
----------  ---      ----------------------------------------------------------
2019-10-07  rh       Create a BOOT version of the ButtonsLib
=============================================================================*/

#include <Base.h>
#include <stdio.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

#include <api/pmic/pm/pm_version.h> 
#include <api/pmic/pm/pm_pon.h> 
#include <api/pmic/pm/pm_gpio.h> 
#include <api/pmic/pm/pm_resources_and_types.h>
#include <api/pmic/pm/pm_sdam.h>
#include <smem.h>
#include "busywait.h"

#include "boot_logger.h"

static uint8 g_ButtonsBootLibKeyCode;

/* Error message wrapper */
#define STATUS_MSG_LEN 300
#define STATUS_MSG_HEAD_LEN 5
static char status_message[STATUS_MSG_LEN + STATUS_MSG_HEAD_LEN]="BTN: ";

#define log_message(...)      \
  snprintf((status_message+STATUS_MSG_HEAD_LEN), STATUS_MSG_LEN,__VA_ARGS__); \
  boot_log_message(status_message);

#define SDAM1_MEM_123 123
#define SDAM3_MEM_076 76

// Buttons Bit map
#define POWER_BUTTON_BMAP                (1 << 0)
#define VOLUME_UP_BUTTON_BMAP            (1 << 1)
#define VOLUME_DN_BUTTON_BMAP            (1 << 2)
#define HOME_BUTTON_BMAP                 (1 << 3)

// GPIO Numbers
#define NOT_SUPPORTED                    0
#define VOLUME_UP_BUTTON_GPIO            6
#define HOME_BUTTON_GPIO                 1

#define GPIO_PM_DEVICE_INDEX             1

/* GPIO configuration */
typedef struct{
  pm_gpio_perph_index                    Gpio;
  pm_gpio_volt_src_type                  VoltageSource;
}ButtonBootPmicGpioCfg;

const ButtonBootPmicGpioCfg VolUpButton = {
    .Gpio              = PM_GPIO_6,
    .VoltageSource     = PM_GPIO_VIN1,
};

const ButtonBootPmicGpioCfg HomeButton = {
    .Gpio              = PM_GPIO_1,
    .VoltageSource     = PM_GPIO_VIN1,
};

/**
Enable the GPIO for Input
**/
pm_err_flag_type BootEnableInput (const ButtonBootPmicGpioCfg * PmicGpioCfg )
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;
   
   Status |= pm_gpio_cfg_mode(GPIO_PM_DEVICE_INDEX,
                              PmicGpioCfg->Gpio,
                              PM_GPIO_DIG_IN);
   
   Status |= pm_gpio_set_voltage_source(GPIO_PM_DEVICE_INDEX,
                                        PmicGpioCfg->Gpio,
                                        PmicGpioCfg->VoltageSource);
   
   Status |= pm_gpio_set_out_drv_str(GPIO_PM_DEVICE_INDEX,
                                     PmicGpioCfg->Gpio,
                                     PM_GPIO_OUT_DRV_STR_LOW);
   
   Status |= pm_gpio_set_out_src_cfg(GPIO_PM_DEVICE_INDEX,
                                     PmicGpioCfg->Gpio,
                                     PM_GPIO_SRC_GND);      

   Status |= pm_gpio_set_pull_sel(GPIO_PM_DEVICE_INDEX, 
                                  PmicGpioCfg->Gpio,
                                  PM_GPIO_PULL_UP_30UA);
    
   if ( Status != PM_ERR_FLAG_SUCCESS ) {
       // Print error message
       log_message ("Error enabling GPIO lines");
       goto ErrorExit;
   }

ErrorExit:
   return Status;
}


/**
Initialize all button GPIOs on PMIC for input based
on platform
**/
pm_err_flag_type BootConfigureButtonGPIOs ( VOID )
{

   pm_err_flag_type Status;

   // volume up
   Status = BootEnableInput(&VolUpButton);
   if ( Status != PM_ERR_FLAG_SUCCESS ) {
      log_message ("Error enabling GPIO lines for VOL+ btn");
      goto ErrorExit;
   }

#ifdef BUTTONS_LIB_USES_HOME_BUTTON
   // home
   Status = BootEnableInput(&HomeButton);
   if ( Status != PM_ERR_FLAG_SUCCESS ) {
      log_message ("Error enabling GPIO lines for HOME btn");
      goto ErrorExit;
   }
#endif

ErrorExit:
   return Status;
}


/**
Read gpio status on PMIC.
**/
pm_err_flag_type BootReadGpioStatus( UINT16 GpioNumber, BOOLEAN *pGpioButtonPressed )
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;
   BOOLEAN GpioStatus = FALSE;

   Status = pm_gpio_irq_status( GPIO_PM_DEVICE_INDEX,
                                (pm_gpio_perph_index)(GpioNumber-1),
                                PM_IRQ_STATUS_RT,
                                &GpioStatus
                               );

   if ( Status != PM_ERR_FLAG_SUCCESS ) {
       log_message ("Error getting GPIO status, GPIO %d", GpioNumber);
   } else {
       // this is because we initially have pull-ups on the GPIOs
       *pGpioButtonPressed =  ( GpioStatus == TRUE ) ? FALSE : TRUE;
   }

   return Status;
}

pm_err_flag_type BootPollPowerKey(BOOLEAN *pPowerKey)
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;

   Status = pm_pon_irq_status(0, PM_PON_IRQ_KPD_PWR_N_DEB, PM_IRQ_STATUS_RT, pPowerKey);

   if ( Status != PM_ERR_FLAG_SUCCESS ) {
      log_message ("Error getting PWR button status");
   }
   return Status;
}

pm_err_flag_type BootPollVolDwnKey(BOOLEAN *pKey)
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;

   Status = pm_pon_irq_status(0, PM_PON_IRQ_RESIN_N_DEB, PM_IRQ_STATUS_RT, pKey);

   if ( Status != PM_ERR_FLAG_SUCCESS ) {
      log_message ("Error getting VOL- button status");
   }
   return Status;
}

/* Public API, capture button status */
void CaptureBootButtonsState()
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;
   BOOLEAN KeyState;
   uint8 ButtonsBitMap = 0;

   Status = BootConfigureButtonGPIOs ();
   if (Status != PM_ERR_FLAG_SUCCESS) {
      log_message ("Error configure buttons GPIO");
      return;        
   }
   /* Wait for pull up after GPIO configuration */
   busywait(200);

   Status = BootPollVolDwnKey(&KeyState);
   ButtonsBitMap |= KeyState ? VOLUME_DN_BUTTON_BMAP : 0;
   Status |= BootPollPowerKey(&KeyState);
   ButtonsBitMap |= KeyState ? POWER_BUTTON_BMAP : 0;
   Status |= BootReadGpioStatus(VOLUME_UP_BUTTON_GPIO, &KeyState);
   ButtonsBitMap |= KeyState ? VOLUME_UP_BUTTON_BMAP : 0;

   if (Status != PM_ERR_FLAG_SUCCESS) {
      log_message ("Error reading button status, Error code %d", Status);
   } else {
      /* Write the content of ButtonBitMap into shared memory */
      g_ButtonsBootLibKeyCode = ButtonsBitMap;
   }

   /* Save the result to the SDAM also */
   Status = pm_sdam_mem_write(PMIC_A, PM_SDAM_3, SDAM3_MEM_076, 1, &g_ButtonsBootLibKeyCode);
   if (Status != PM_ERR_FLAG_SUCCESS) {
      log_message ("Error writing to SDAM");
   }
}

/* Public API, Return button status */
int32 BootButtonsStateRead(uint32 *ButtonState)
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;
   BOOLEAN KeyState = FALSE;
   uint32 ButtonsBitMap = 0;

   if (ButtonState == NULL) {
      return -1;
   }

   Status = BootPollVolDwnKey(&KeyState);
   ButtonsBitMap |= KeyState ? VOLUME_DN_BUTTON_BMAP : 0;
   Status |= BootPollPowerKey(&KeyState);
   ButtonsBitMap |= KeyState ? POWER_BUTTON_BMAP : 0;
   Status |= BootReadGpioStatus(VOLUME_UP_BUTTON_GPIO, &KeyState);
   ButtonsBitMap |= KeyState ? VOLUME_UP_BUTTON_BMAP : 0;

   *ButtonState = ButtonsBitMap;

   if (Status == PM_ERR_FLAG_SUCCESS) {
      return 0;
   } else {
      return -1;
   }
}
