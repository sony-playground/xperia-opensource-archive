/** @file UEFIMinidump.c
  
  Copyright (c) 2020 Qualcomm Technologies, Inc. All rights reserved.

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
 07/20/20   ps      Add log region in minidump table

*/

#include <Library/DebugLib.h>
#include "boot_minidump.h"

/**
 
 @brief
   This function adds a new minidump region in boot sub-system minidump table
 
 @param
   CHAR8*  Name of the region
   UINT64 Region BaseAddr
   UINT64 Region Size
       
 @par Dependencies
   None
  
 @retval
   EFI_SUCCESS on success
   EFI_INVALID_PARAMS when params are not valid
 
 @par Side Effects
   None
 
**/

EFI_STATUS 
EFIAPI
AddUEFIMinidumpRegion(CHAR8* RegionName, UINTN* RegionBaseAddr, UINTN RegionSize)
{
  EFI_STATUS Status = EFI_SUCCESS;
  BOOLEAN MinidumpStatus = FALSE;
  if(RegionBaseAddr == NULL || RegionSize == 0)
    return EFI_INVALID_PARAMETER;

  MinidumpStatus = boot_add_minidump_region(MD_SS_BOOT, RegionName, (UINT64)RegionBaseAddr, (UINT64)RegionSize);
  if(!MinidumpStatus)
  {
    DEBUG((EFI_D_INFO, "%s region could not be added to Minidump table\n", RegionName)); 
    Status = EFI_NOT_FOUND;
  }

  return Status;
}
