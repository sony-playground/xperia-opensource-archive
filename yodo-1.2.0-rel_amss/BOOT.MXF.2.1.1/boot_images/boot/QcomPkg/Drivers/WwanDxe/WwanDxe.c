/** @file

  Copyright (c) 2020, Qualcomm Technologies, Inc. All rights reserved.

  Wireless WAN  power Driver 

**/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who         what, where, why
--------   ---         ----------------------------------------------------------
09/15/20   skgupta    initial edit
==============================================================================*/

/*==============================================================================

                       INCLUDE FILES FOR THIS MODULE

==============================================================================*/

#include <Uefi.h>
#include <WwanBsp.h>
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
WwanEntryPoint (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS                            Status = EFI_SUCCESS;

  Status = ActivateWwan();
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a: Error activating  WWAN\r\n", __func__));
    return Status;
  }

  return Status;
}
