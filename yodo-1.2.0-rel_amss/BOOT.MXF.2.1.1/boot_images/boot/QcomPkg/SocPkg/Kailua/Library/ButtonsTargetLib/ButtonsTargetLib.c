/** @file
ButtonsLib.c

Button driver is responsible for detecting key press/release through PMIC HW
and service. It implements the interfaces of simple text input protocol.

This file is platform dependent, it supports ButtonsDxe based on the platform.

Copyright (c) 2012-2022 Qualcomm Technologies, Inc. All rights reserved.
Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
EDIT HISTORY

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who      what, where, why
--------   ---      ----------------------------------------------------------
10/19/18   px       Fix the combo key not able to detect issue
01/22/17   ma       Clamshell support 845
09/13/16   ma       Support QRD845
04/04/16   ma       Change GPIO PULL UP source to VIN0
02/04/16   ma       Port to 845
=============================================================================*/

#include <Base.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PcdLib.h>
#include <Library/ButtonsLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/OfflineCrashDump.h>

#include "ButtonsLibPrivate.h"

#define NUMBER_OF_KEYS   5
// Button Index 
#define VOLUME_UP_BUTTON_IDX             1
#define HOME_BUTTON_IDX                  2
#define CAMERA_SNAPSHOT_BUTTON_IDX       3

extern EFI_PLATFORMINFO_PLATFORM_TYPE  PlatformType ;
extern EFI_QCOM_PMIC_GPIO_PROTOCOL *PmicGpioProtocol;
extern EFI_GUID gQcomTokenSpaceGuid;

struct StructPlatformKeyMap {
   EFI_PLATFORMINFO_PLATFORM_TYPE Platform;
   KEY_TYPE KeyMap[NUMBER_OF_KEYS];
};

/*** Define the Key Map for all Platforms ***/
struct StructPlatformKeyMap g_KeyMaps[] = {
   {
      .Platform = EFI_PLATFORMINFO_TYPE_CDP,
      .KeyMap = { PWR, VOL_UP, VOL_DOWN, NONE, NONE }
   },
   {
      .Platform = EFI_PLATFORMINFO_TYPE_MTP,
      .KeyMap = { PWR, VOL_UP, VOL_DOWN, NONE, NONE }
   },
   {
      .Platform = EFI_PLATFORMINFO_TYPE_FLUID,
      .KeyMap = { PWR, VOL_UP, VOL_DOWN, NONE, NONE }
   },
   {
      .Platform = EFI_PLATFORMINFO_TYPE_ADP,
      .KeyMap = { PWR, VOL_UP, VOL_DOWN, NONE, NONE }
   },
   {
      .Platform = EFI_PLATFORMINFO_TYPE_QRD,
      .KeyMap = { PWR, VOL_UP, VOL_DOWN, NONE, NONE }
   },
   {
      .Platform = EFI_PLATFORMINFO_TYPE_HDK,
      .KeyMap = { PWR, VOL_UP, VOL_DOWN, NONE, NONE }
   },
   {
      .Platform = EFI_PLATFORMINFO_TYPE_CLS,
      .KeyMap = { PWR, VOL_UP, VOL_DOWN, NONE, NONE }
   },
   {
      .Platform = EFI_PLATFORMINFO_TYPE_RCM,
      .KeyMap = { PWR, VOL_UP, VOL_DOWN, NONE, NONE }
   },
   {
      .Platform = EFI_PLATFORMINFO_TYPE_UNKNOWN,
      .KeyMap = { NONE, NONE, NONE, NONE, NONE }
   }
};

UINT16 g_sdam_pmic_idx = BUTTONS_LIB_SDAM_PMIDX;
UINT16 g_sdam_number = BUTTONS_LIB_SDAM_NUM;
UINT16 g_sdam_address = BUTTONS_LIB_SDAM_ADDR;

/**
Enable the GPIO for Input

@param  GpioNumber               GPIO Number
@retval EFI_SUCCESS              Enable successful
@retval non EFI_SUCCESS          Enable failed

**/
EFI_STATUS EnableInput ( ButtonPmicGpioCfg * PmicGpioCfg )
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(PmicGpioProtocol)
  {
     Status |= PmicGpioProtocol->CfgMode(PmicGpioCfg->PmicDeviceIndex,
                                                   PmicGpioCfg->Gpio,
                                                   EFI_PM_GPIO_DIG_IN);
    
    Status |= PmicGpioProtocol->SetVoltageSource(PmicGpioCfg->PmicDeviceIndex,
                                                   PmicGpioCfg->Gpio,
                                                   PmicGpioCfg->VoltageSource);
    
    Status |= PmicGpioProtocol->SetOutDrvStr(PmicGpioCfg->PmicDeviceIndex,
                                                   PmicGpioCfg->Gpio,
                                                   PmicGpioCfg->OutBufferStrength);
    
    Status |= PmicGpioProtocol->SetOutSrcCfg(PmicGpioCfg->PmicDeviceIndex,
                                                   PmicGpioCfg->Gpio,
                                                   PmicGpioCfg->Source);      
     
     if ( EFI_ERROR (Status) )
     {
         DEBUG(( EFI_D_ERROR, "EnableInput: ConfigDigitalInput failed Status = (0x%x)\r\n", Status));
         return Status;
     }
  }

   return Status;
}



/**
Initialize all button GPIOs on PMIC for input based
on platform

@param  None
@retval EFI_SUCCESS              Configuration successful
@retval non EFI_SUCCESS          Configuration failed

**/
EFI_STATUS ConfigureButtonGPIOs ( VOID )
{

   EFI_STATUS Status;

#if 0 /* this block is orignai code, but sony modification is not used volup settings*/
   // volume up
   Status = EnableInput(&VolUpButton);
   if ( EFI_ERROR (Status) )
   {
      DEBUG(( EFI_D_ERROR, "ConfigureButtonGPIOs: EnableInput failed for VOL+ button, Status = (0x%x)\r\n", Status));
      return Status;
   }
#endif

/* SONY_BEGIN (Add Enable Setting for Volume Down Button) */
   // volume down
   Status = EnableInput(&VolDownButton);
   if ( EFI_ERROR (Status) )
   {
      DEBUG(( EFI_D_ERROR, "ConfigureButtonGPIOs: EnableInput failed for VOL- button, Status = (0x%x)\r\n", Status));
      return Status;
   }
/* SONY_END (Add Enable Setting for Volume Down Button) */

   if( (PlatformType == EFI_PLATFORMINFO_TYPE_MTP)||
       (PlatformType == EFI_PLATFORMINFO_TYPE_FLUID)||
       (PlatformType == EFI_PLATFORMINFO_TYPE_ADP)||
       (PlatformType == EFI_PLATFORMINFO_TYPE_CDP))
   {
     // Camera Snapshot
     if (CAMERA_SNAPSHOT_BUTTON_GPIO != NOT_SUPPORTED) 
     {
       Status = EnableInput(&CameraButton);
       if ( EFI_ERROR (Status) )
       {
          DEBUG(( EFI_D_ERROR, "ConfigureButtonGPIOs: EnableInput failed for Snapshot button, Status = (0x%x)\r\n", Status));
          return Status;
       }
     }
   }

   if( (PlatformType == EFI_PLATFORMINFO_TYPE_ADP)||
       (PlatformType == EFI_PLATFORMINFO_TYPE_CDP) )
   {
     if (HOME_BUTTON_GPIO != NOT_SUPPORTED) 
     {
        //home
        Status = EnableInput(&HomeButton);
        if ( EFI_ERROR (Status) )
        {
           DEBUG(( EFI_D_ERROR, "ConfigureButtonGPIOs: EnableInput failed for home button, Status = (0x%x)\r\n", Status));
           return Status;
        }
     }
  }

   return Status;

}


/**
Read gpio status on PMIC.

@param  GpioNumber               GPIO number..
@param  pGpioButtonPressed       Pointer storing the value of button activity (press).

@retval EFI_SUCCESS              Retrieve status successfully
@retval non EFI_SUCCESS          Retrieve status failed

**/
EFI_STATUS ReadGpioStatus( UINT16 KeyIndex, BOOLEAN *pGpioButtonPressed )
{
   EFI_STATUS Status = EFI_SUCCESS;
   BOOLEAN GpioStatus = FALSE;
   UINT16 GpioNumber = ButtonsGPIOMap[KeyIndex];
   UINT16 PmicIndex = ButtonsPmicIdxMap[KeyIndex];

   // Detect if key is supported
   if(KeyIndex == HOME_BUTTON_IDX) 
   {
      if(!((PlatformType == EFI_PLATFORMINFO_TYPE_ADP) ||
           (PlatformType == EFI_PLATFORMINFO_TYPE_CDP) )) 
      {
         return EFI_NOT_FOUND;
      }
   }

   if(KeyIndex == CAMERA_SNAPSHOT_BUTTON_IDX) 
   {
      if((CAMERA_SNAPSHOT_BUTTON_GPIO == NOT_SUPPORTED) ||
         !((PlatformType == EFI_PLATFORMINFO_TYPE_MTP) ||
          (PlatformType == EFI_PLATFORMINFO_TYPE_FLUID)||
          (PlatformType == EFI_PLATFORMINFO_TYPE_ADP)  ||
          (PlatformType == EFI_PLATFORMINFO_TYPE_CDP)))
      {
         return EFI_NOT_FOUND;
      }
   }

   if(PmicGpioProtocol)
   {
      if (GpioNumber == NOT_SUPPORTED) {
         return EFI_NOT_FOUND;
      }

      Status = PmicGpioProtocol->IrqStatus( PmicIndex,
                                            (EFI_PM_GPIO_PERIPH_INDEX)(GpioNumber-1),
                                            EFI_PM_IRQ_STATUS_RT,
                                            &GpioStatus
                                          );
      if ( EFI_ERROR (Status) )
      {
         DEBUG(( EFI_D_ERROR, "ReadGpioStatus: IrqStatus failed Status = (0x%x)\r\n", Status));
      }
      else
      {
         //
         // this is because we initially have pull-ups on the GPIOs
         //
         *pGpioButtonPressed =  ( GpioStatus == TRUE ) ? FALSE : TRUE;
      }
   }

   return Status;
}


