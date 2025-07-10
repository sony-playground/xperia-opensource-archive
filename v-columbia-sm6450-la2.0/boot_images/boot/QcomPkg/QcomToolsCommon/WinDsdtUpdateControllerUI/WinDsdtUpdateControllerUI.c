/** @file WinDsdtUpdateControllerUI.c
   
  Application to launch configurable menu. The menu cfg file can be
  Passed in as param.
  
  Copyright 2016-2018,2020 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
   
**/

/*=============================================================================
                              EDIT HISTORY


  when         who     what, where, why
  ----------   ---     -----------------------------------------------------------
  06/11/2020   rchriste Added partial binning support for MK
  02/26/2018   ltg     Added options for feature/cpu bitmask
  02/17/2017   vinitb  Added qccdi option related changes
  01/30/2017   vinitb  Added sensors/gpu option related changes
  09/23/2016   ssumit      Initial version
=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomUtilsLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/EfiWinAcpiUpdate.h>
#include <Protocol/AcpiSystemDescriptionTable.h>


/* FeatureBitmask : mask indicating features to disable
*/

EFI_STATUS
SetDefectivePartsBitmask (UINT32 FeatureBitmask)
{
    EFI_STATUS                              Status;
    static EFI_WIN_ACPI_UPDATE_PROTOCOL     *gWinAcpi = NULL;
    BOOLEAN                                 configuration = FALSE;

    // Locate Win ACPI update protocol
    Status = gBS->LocateProtocol(
      &gEfiWinAcpiUpdateProtocolGuid,
      NULL,
      (VOID**) &gWinAcpi
    );

    if (EFI_ERROR (Status))
    {
        DEBUG((EFI_D_ERROR, "Failed to Locate WinAcpiUpdate protocol \r\n"));
        return EFI_LOAD_ERROR;
    }
    for (int i = 0; i < EFI_WIN_ACPI_PART_MAX; i++)
    {
        if (FeatureBitmask & (UINT32)(0x1 << i))
        {
            configuration = TRUE;
        }
        else
        {
            configuration = FALSE;
        }

        Status = gWinAcpi->SetDefectivePartsVariable(
            gWinAcpi,
            i,
            configuration
            );
        if (EFI_ERROR (Status))
        {
            AsciiPrint("\r\nSetFeatureBitmask: gWinAcpi->SetDefectivePartsVariable failed\n");
            return EFI_PROTOCOL_ERROR;
        }
    }

    AsciiPrint("\r\nSet bitmask: \"0x%x\"\r\n\r\n", FeatureBitmask);
    return EFI_SUCCESS;
}

/**
  Entry point for WinDsdtUpdateControllerUI APP

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS           Erase successfully.
  @retval EFI_DEVICE_ERROR      Failed to program
  @retval EFI_OUT_OF_RESOURCES  Failed to allocate memory for 
                                the buffers
**/

EFI_STATUS
EFIAPI
ControllerUIMain ( 
                IN EFI_HANDLE         ImageHandle,
                IN EFI_SYSTEM_TABLE   *SystemTable
                )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    UINTN                       ErrorCode = 0;
    UINTN                       Argc;
    CHAR8                      **Argv, **TempArgv;
    UINTN                      DefectiveBitmask = 0;

    Status = GetCmdLineArgs (
                  ImageHandle,
                  &Argc,
                  &Argv
                  );

    if (EFI_ERROR(Status))
    {
        AsciiPrint ("Failed to get cmd line args with status 0x%x\r\n", Status);
        return Status;  
    }

    TempArgv = Argv;

    /* Check if the app was launched by shell and the WinDsdtUpdateControllerUI str is actually the
    * WinDsdtUpdateControllerUI app name itself, ie it would be "WinDsdtUpdateControllerUI" or "WinDsdtUpdateControllerUI.efi", then again process
    * to split, this is because Ebl doesn't pass the name of app, but shell does
    * other methods could yeild mixed results (like BDS launching apps via Menu, etc) */
    if (Argc &&
        ((AsciiStriCmp (Argv[0], "WinDsdtUpdateControllerUI") == 0) ||
        (AsciiStriCmp (Argv[0], "WinDsdtUpdateControllerUI.efi") == 0)))
    { 
        --Argc;
        ++Argv;
    }

    /* Now both cmdStr and ArgStr have proper values. If no argument, then we can launch
    * BDS Menu by default */
    if (Argc == 0)
    {
        ErrorCode = LaunchMenu ("DriverList.cfg");
    }
    else
    {
        if (Argc == 2)
        {
            if ( ( AsciiStriCmp ((CHAR8*)Argv[0], "SetDefectiveBitmask") == 0 ))
            {
                DefectiveBitmask = AsciiStrDecimalToUintn((CHAR8 *)Argv[1]);
                if (SetDefectivePartsBitmask (DefectiveBitmask) != EFI_SUCCESS)
                {
                    AsciiPrint ("Failed to set feature bitmask\r\n");
                    return EFI_SUCCESS;
                }
            }
        }
        else
        {
            AsciiPrint ("Improper arguments passed \r\n");
        }
    }

    if (TempArgv)
      FreePool (TempArgv);

    return Status;
}
