/** @file SysSleep.c
  SysSleep library stub.

  Copyright (c) 2018,2020,2021 Qualcomm Technologies, Inc.  All Rights Reserved.

  Qualcomm Technologies Proprietary and Confidential.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/7/20    ai      Updated
 04/19/18   yg      Created
 
=============================================================================*/

#include <Uefi.h>
#include "Library/SysSleepLib.h"

VOID SystemSleepInit (UINTN MaxCoreCnt)
{
}

INT32 CoreSleepCpu (UINT64 DurationMs)
{
  return 0;
}

UINTN BackupRestoreSystemCtxt (UINTN Operation)
{
  /* Unsupported */
  return RESTORE_SYSTEM_CONTEXT;
}

VOID CoreSleepLoggingControl (sleep_logging_state Control)
{
}

EFI_STATUS RegisterDevicePowerTransitionCallback (PwrTxnNotifyFn CbFn, VOID* Arg)
{
  return EFI_UNSUPPORTED;
}


EFI_STATUS UnRegisterDevicePowerTransitionCallback (PwrTxnNotifyFn CbFn)
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS WDogMonitorStart (VOID)
{
  return EFI_UNSUPPORTED;
}

VOID WDogMonitorStop (VOID)
{
}

VOID WDogMonitorForcePet (VOID)
{
}

VOID WDogMonitorForceBite (VOID)
{
}

EFI_STATUS WDogMonitorSetPetTimerPeriod (UINT32 TimerPeriodms)
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS WDogMonitorSetBiteTimeout (UINT32 WDogTimeoutms)
{
  return EFI_UNSUPPORTED;
}
