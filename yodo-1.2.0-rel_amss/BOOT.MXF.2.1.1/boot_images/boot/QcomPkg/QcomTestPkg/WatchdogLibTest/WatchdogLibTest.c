/** @file WatchdogLibTest.c
   
  Test Application for the WatchdogLib Test and supporting libraries

  Copyright (c) 2012,2021 Qualcomm Technologies, Inc. All rights reserved.

  Copyright (c) 2006 -2008, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials                          
  are licensed and made available under the terms and conditions of the BSD License         
  which accompanies this distribution.  The full text of the license may be found at        
  http://opensource.org/licenses/bsd-license.php                                            

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
01/22/21    ka      Updates to WatchdogLib Test
12/16/20    cm      Updated WatchdogLib Test
07/07/12    rks     Created test WatchdogLib

=============================================================================*/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/TestInterface.h>

#include <Library/WatchdogLib.h>


#define SEC_TO_MSEC(x)   ((x) * 1000)
#define SEC_TO_MICROSEC(x)        MultU64x32((UINT64)(x), 1000000)
#define BITE_TIMER_SEC            3

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

EFI_STATUS
EFIAPI
WDLTestMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  
  TEST_START("WatchDogLibTest"); 
  Status = gBS->SetWatchdogTimer(0, 0, 0, NULL);
  if(Status != EFI_SUCCESS)
  {
    goto Exit;
  }
  
  Status = WatchDogSetBiteTimeout(SEC_TO_MSEC(BITE_TIMER_SEC));
  if(EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR,"WatchDogSetBiteTimeout failed: %r \n", Status));
    goto Exit;
  }
  AsciiPrint("BiteTime Register value set to %d Seconds\n", BITE_TIMER_SEC);

  AsciiPrint("Start : Enable Watchdog\n");
  WatchDogEnable();
  AsciiPrint("Finish : Enable Watchdog\n");
  
  AsciiPrint("Start : Disable Watchdog\n");
  WatchDogDisable();
  AsciiPrint("Finish : Disable Watchdog\n");

  AsciiPrint("Stall for %d seconds, should not crash after this!\n", BITE_TIMER_SEC);
  gBS->Stall(SEC_TO_MICROSEC(BITE_TIMER_SEC));
  
  Status = WatchDogSetBiteTimeout(SEC_TO_MSEC(BITE_TIMER_SEC));
  if(EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR,"WatchDogSetBiteTimeout failed: %r \n", Status));
    goto Exit;
  }
  AsciiPrint("BiteTime Register value set to %d Seconds\n", BITE_TIMER_SEC);
  
  AsciiPrint("Start : Enable Watchdog\n");
  WatchDogEnable();
  AsciiPrint("Finish : Enable Watchdog\n");
  
  AsciiPrint("Stall for %d seconds, expect a crash after this!\n", BITE_TIMER_SEC);
  gBS->Stall(SEC_TO_MICROSEC(BITE_TIMER_SEC));

Exit:
  /* Should not reach here */
  TestStatus("WatchDogLibTest", EFI_DEVICE_ERROR);
  TEST_STOP("WatchDogLibTest");
  return EFI_DEVICE_ERROR;
  
  return Status;
}
