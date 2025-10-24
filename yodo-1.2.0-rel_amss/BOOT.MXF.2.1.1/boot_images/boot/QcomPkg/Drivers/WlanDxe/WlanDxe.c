/** @file

  Copyright (c) 2020, Qualcomm Technologies, Inc. All rights reserved.

  Wireless Connectivity power Driver 

**/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who         what, where, why
--------   ---         ----------------------------------------------------------
08/05/20   ohkeunow    initial edit
==============================================================================*/

/*==============================================================================

                       INCLUDE FILES FOR THIS MODULE

==============================================================================*/

#include <Uefi.h>
#include <WlanBsp.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>


/*==============================================================================

                         DEFINES FOR THIS MODULE

==============================================================================*/

/*==============================================================================

                     EXTERNAL DEFINES FOR THIS MODULE

==============================================================================*/


/*==============================================================================

                      PROTOTYPES USED IN THIS MODULE

==============================================================================*/


/*==============================================================================

                     GLOBAL VARIABLES FOR THIS MODULE

==============================================================================*/


/*==============================================================================

                             API IMPLEMENTATION

==============================================================================*/


EFI_STATUS
EFIAPI
WlanEntryPoint (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS                            Status = EFI_SUCCESS;

  Status = WlanPowerOn();
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a: Error powering up WLAN\r\n", __func__));
    return Status;
  }

  return Status;
}

