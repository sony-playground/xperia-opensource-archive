/** @file RscDxe.c

  This file inits RSC driver.

  Copyright (c) 2020, 2021, Qualcomm Technologies Inc. All rights
  reserved.

**/

/*=========================================================================
      Include Files
==========================================================================*/

#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIScm.h>

#include <object.h>
#include "IClientEnv.h"
#include "CPeripheralRetainState.h"
#include "IPeripheralRetainState.h"

/**
 * Entry point for the PsState DXE driver.
 */
EFI_STATUS EFIAPI PsStateDxeEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  QCOM_SCM_PROTOCOL *QcomScmProtocol = NULL;
  EFI_STATUS         Status          = EFI_SUCCESS;
  Object             ClientEnv       = Object_NULL;
  Object             PsObj           = Object_NULL;
  INT32              Ret             = Object_OK;

  Status = gBS->LocateProtocol (&gQcomScmProtocolGuid, NULL, (VOID**)&QcomScmProtocol);
  if (Status != EFI_SUCCESS)
    return Status;

  Status = QcomScmProtocol->ScmGetClientEnv(QcomScmProtocol, &ClientEnv);
  if (Status != EFI_SUCCESS)
     return Status;

  if (Object_isNull(ClientEnv))
  {
     Status = EFI_DEVICE_ERROR;
     return Status;
  }

  Ret = IClientEnv_open(ClientEnv, CPeripheralRetainState_UID, &PsObj);
  if (Ret || Object_isNull(PsObj))
  {
     Object_RELEASE_IF(ClientEnv);
     Status = EFI_DEVICE_ERROR;
     return Status;
  }

  Ret = IPeripheralRetainState_notifyBootEvent(PsObj);
  if (Ret)
     Status = EFI_DEVICE_ERROR;

  Object_RELEASE_IF(PsObj);
  Object_RELEASE_IF(ClientEnv);
  return Status;
}
