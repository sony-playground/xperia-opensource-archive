/**
 * @file    NvmePowerControlDxe.c
 * @brief   NvmePowerControl Dxe Driver
 *
 * Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
 * All rights reserved.
 **/


/*=============================================================================
EDIT HISTORY


when            who   what, where, why
----------      ---   ----------------------------------------------------------
2022-06-13      sc    Add check for offmode charging.
2021-04-07      wek   Initial Version.
=============================================================================*/

#include <Library/BaseMemoryLib.h>
#include <Library/BootConfig.h>
#include <NvmeBsp.h>
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIChargerEx.h>
 
 
BOOLEAN IsDeviceInOffModeCharging (VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;
  BOOLEAN OffModeChg = FALSE;
  EFI_CHARGER_EX_PROTOCOL *ChgExIntf = NULL;

  Status = gBS->LocateProtocol (&gChargerExProtocolGuid, NULL, (void**)&ChgExIntf);

  if ((Status != EFI_SUCCESS) || (ChgExIntf == NULL))
    return FALSE;

  Status = ChgExIntf->IsOffModeCharging (&OffModeChg);
  if (Status != EFI_SUCCESS)
    return FALSE;

  DEBUG ((EFI_D_ERROR, "NvmePowerControlDxe: IsDeviceInOffModeCharging: %d\n", OffModeChg));
  return OffModeChg;
}

/**
   Driver initialization entry point.
**/
EFI_STATUS EFIAPI NvmePowerControlDxeEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable)
{
  DEBUG((DEBUG_VERBOSE, "%a\n", __FUNCTION__));
  if (boot_from_nvme() && IsDeviceInOffModeCharging() == FALSE)
  {
    INTN result;
    result = nvme_core_target_power_on(0);
    if (result != 0)
    {
      DEBUG ((EFI_D_ERROR, "NvmePowerControlEntry: Failed to turn on NVMe power rail!\n"));
      return EFI_DEVICE_ERROR;
    }
  }

  return EFI_SUCCESS;
}
