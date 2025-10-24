/**@file VirtualWatchDogLib.c

  Copyright (c) 2020-2021, Qualcomm Technologies Inc. All rights reserved.<BR>

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 
 --------   ---     -----------------------------------------------------------
 10/07/21   rbv     Added Validation check for WatchDogEnable
 08/13/20   ai      Initial version
=============================================================================*/
#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/WatchdogLib.h>

#define MAX_WDOG_BITE_VAL_MS      0x8000
#define FORCED_BITE_TIME_MS       4

#define SMC_ID_WDOG_CTL           0x86000005
#define SMC_ID_WDOG_STATUS        0x86000006
#define SMC_ID_WDOG_PET           0x86000007
#define SMC_ID_WDOG_SET           0x86000008

extern INT32 WdogHypCall(UINT32 SmcId, UINT32 Arg1, UINT32 Arg2, VOID* Resp1, VOID* Resp2);

/*==============================================================================
  FUNCTION      WatchDogEnable
==============================================================================*/
VOID
WatchDogEnable (VOID)
{
#define WDOG_CTL_ENABLE_MASK          0x3
#define WDOG_STATUS_ENABLED			  0x1

  UINT64 WdogEnable;
  INT32 Status;
  Status = WdogHypCall(SMC_ID_WDOG_STATUS,0,0,(UINT64*)&WdogEnable,NULL);
  //If WatchDog is already Enabled,Dont Enable Again
  if (!Status && !(WdogEnable & WDOG_STATUS_ENABLED)){
	Status = WdogHypCall(SMC_ID_WDOG_CTL, WDOG_CTL_ENABLE_MASK, 0, NULL, NULL);
	if (Status) {
		DEBUG((EFI_D_ERROR, "ERROR: SMC_ID_WDOG_CTL Enable failed - (%d)\n", Status));
	}
  }
}


/*==============================================================================
  FUNCTION      WatchDogDisable
==============================================================================*/
VOID
WatchDogDisable (VOID)
{
#define WDOG_CTL_DISABLE_MASK         0x2

  INT32 Status = WdogHypCall(SMC_ID_WDOG_CTL, WDOG_CTL_DISABLE_MASK, 0, NULL, NULL);
  if (Status) {
    DEBUG((EFI_D_ERROR, "ERROR: SMC_ID_WDOG_CTL Disable failed - (%d)\n", Status));
  }
}

/*==============================================================================
  FUNCTION      WatchDogSetBiteTimeout

  BITETIME      IN PARAM - time in msec

  RETVAL        EFI_SUCCESS upon success
                EFI_INVALID_PARAMTER if BITETIME > max time
                EFI_DEVICE_ERROR cannot set BiteTimeMSec

  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/
EFI_STATUS
WatchDogSetBiteTimeout (UINT32 BiteTimeMSec)
{
  INT32 Status;

  if ((BiteTimeMSec == 0) || (BiteTimeMSec > MAX_WDOG_BITE_VAL_MS)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = WdogHypCall(SMC_ID_WDOG_SET, BiteTimeMSec, BiteTimeMSec, NULL, NULL);
  if (Status) {
    DEBUG((EFI_D_ERROR, "ERROR: SMC_ID_WDOG_SET failed - (%d)\n", Status));
    return EFI_DEVICE_ERROR;
  }

  WatchDogPet ();

  return EFI_SUCCESS;

}

/*==============================================================================
  FUNCTION      WatchDogPet

  DESCRIPTION   Reset watchdog counter
==============================================================================*/
VOID
WatchDogPet (VOID)
{
  INT32 Status = WdogHypCall(SMC_ID_WDOG_PET, 0, 0, NULL, NULL);
  if (Status) {
    DEBUG((EFI_D_ERROR, "ERROR: SMC_ID_WDOG_PET failed - (%d)\n", Status));
  }
}

/*==============================================================================
  FUNCTION      TriggerWatchDogReboot

  DESCRIPTION   Enable WatchDog and force immediate target reboot
==============================================================================*/
EFI_STATUS
WatchDogTriggerBite (VOID)
{
  WatchDogSetBiteTimeout (FORCED_BITE_TIME_MS);

  /* CTL, Enable */
  WatchDogEnable();

  //WatchDogSetBiteTimeout (FORCED_BITE_TIME_MS);

  while (1);
}

EFI_STATUS WatchDogSetPetTimerPeriod (UINT32 PeriodMSec)
{
  return EFI_UNSUPPORTED;
}

VOID WatchDogForcePet (VOID)
{
  WatchDogPet ();
}

VOID WatchDogForceBite (VOID)
{
  WatchDogTriggerBite ();
}

