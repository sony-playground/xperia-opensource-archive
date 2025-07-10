/** @file DTBTest.c

  Test DTB functionality

  Copyright (c) 2021 Qualcomm Technologies Inc. All rights reserved.
  Portions Copyright (c) 2006 - 2008, Intel Corporation. All rights reserved.
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
 03/24/21   tmt     Update to use new Protocol wrapper library
 01/28/21   ai      Sample DTB usecase
=============================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/TestInterface.h>
#include <Protocol/EFIDtbExtn.h>
#include <Library/DTBExtnUEFILib.h>
#include "comdef.h"
#include "DTBExtnLib.h"

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
DTBTestMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  fdt_node_handle      Node;
  UINT32               DTBConfig[3];
  EFI_STATUS           Status           = EFI_DEVICE_ERROR;
  INTN                 Ret              = -1;

  TEST_START("DTBTest");
  
  Ret = fdt_get_node_handle(&Node, NULL, "/sw/boot");
  //Ret = FdtGetNodeHandle(&Node, "/sw/boot");

  if (Ret) {
    DEBUG((EFI_D_ERROR, "FdtGetNodeHandle: [%d]%r\n", Ret, Status));
    goto Exit;
  }

  /* extract properties from node */
  //Ret = FdtGetUint32PropList(&Node, "config", (VOID *)&DTBConfig, sizeof(DTBConfig));
  Ret = fdt_get_uint32_prop_list(&Node, "config", (VOID *)&DTBConfig, sizeof(DTBConfig));

  if (Ret) {
	 DEBUG((EFI_D_ERROR, "fdt_get_uint32_prop_list: %r\n", Status));
    //DEBUG((EFI_D_ERROR, "FdtGetUint32PropList: %r\n", Status));
    goto Exit;
  }

  DEBUG((EFI_D_ERROR, "/sw/boot/config : client[%x]..trace[%x]..verbose[%x]\n",
           DTBConfig[0], DTBConfig[1], DTBConfig[2]));

  Status = EFI_SUCCESS;

Exit:
  TestStatus("DTBTest", Status);
  TEST_STOP("DTBTest");
  return Status;
}
