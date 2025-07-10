/*++

Copyright (c) 2017,2020 Qualcomm Technologies, Inc. All rights reserved
Confidential and Proprietary - Qualcomm Technologies, Inc.
Portions:
Copyright (c) 2013-2014, ARM Ltd. All rights reserved.<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

Module Name:

  ArmGicDxe.c

Abstract:

  Driver implementing the GIC interrupt controller protocol

--*/

#include <PiDxe.h>

#include "ArmGicDxe.h"

/**
  Initialize the state information for the CPU Architectural Protocol

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems
  @retval EFI_UNSUPPORTED       GIC version not supported

**/
EFI_STATUS
InterruptDxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS            Status;
  ARM_GIC_ARCH_REVISION Revision;
#if defined(QCOM_EDK2_PATCH)
  VOID  *Intf;

  if (gBS->LocateProtocol ((EFI_GUID *)&gHardwareInterruptProtocolGuid, NULL, &Intf) == EFI_SUCCESS)
    return EFI_SUCCESS;
#endif

  Revision = ArmGicGetSupportedArchRevision ();

  if (Revision == ARM_GIC_ARCH_REVISION_2) {
    Status = GicV2DxeInitialize (ImageHandle, SystemTable);
  } else if (Revision == ARM_GIC_ARCH_REVISION_3) {
    Status = GicV3DxeInitialize (ImageHandle, SystemTable);
  } else {
    Status = EFI_UNSUPPORTED;
  }

  return Status;
}
