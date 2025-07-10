/** @file FeatureEnablerToggleApp.c

  FeatureEnabler Toggle Application

  Arguments passed in as Unicode Wide-characters:

     /FeatureEnablerEnable    :   Enables FeatureEnabler
     /FeatureEnablerDisable   :   Disables FeatureEnabler

  If no arguments are provided, then enters interactive menu to
  perform the same functions through key presses.

  Copyright (c) 2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.


**/

/*=============================================================================
                              EDIT HISTORY


  when         who     what, where, why
  ----------   ---     -----------------------------------------------------------
  2020-08-121  zwy     Initial version
=============================================================================*/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>
#include <Protocol/LoadedImage.h>

/**
  Print APP usage.
**/
VOID
PrintUsage (
  VOID
  )
{
  AsciiPrint("FeatureEnablerToggleApp usage: Arguments passed in as Unicode Wide-characters\n"
             "    FeatureEnablerToggleApp L\"/FeatureEnablerEnable\"\n"
             "    FeatureEnablerToggleApp L\"/FeatureEnablerDisable\"\n");
}


/**
  This function prompts the user to confirm or cancel enabling UEFI FeatureEnbaler,
  and performs the action if requested.

  @retval  EFI_SUCCESS Successfully enabled or canceled
**/
EFI_STATUS
PerformFeatureEnablerEnable(
  BOOLEAN bOn
  )
{
  EFI_STATUS     Status;
  EFI_INPUT_KEY  Key;
  UINTN          uVarSize = sizeof(bOn);

  Status = gST->ConOut->ClearScreen(gST->ConOut);

  AsciiPrint ("UEFI FeatureEnablerDxe\n"
              "-----------------------\n\n"
              "This operation %a UEFI FeatureEnablerDxe\n"
              "Press [Volume-Up] to confirm\n"
              "Press [Any other key] to cancel\n", bOn ? "Enable" : "Disable");

  Status = ReadAnyKey (&Key, 0);
  if (EFI_ERROR(Status))
  {
   AsciiPrint ("Error: Failed key detection, return code %r\n", Status);
   return Status;
  }

  if (Key.ScanCode == SCAN_UP)
  {
    if (EFI_SUCCESS == (Status = gRT->SetVariable (L"EnableFeatureDxe", &gQcomTokenSpaceGuid, (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE), uVarSize, (UINT8*)&bOn)))
    {
      AsciiPrint ("\nFeatureEnablerDxe is:%a\n", bOn ? "On" : "Off");
    }
    else
    {
      AsciiPrint ("\nFail to update EnableFeatureDxe Variable\n");
    }
  }
  else
  {
   AsciiPrint ("\nRESULT: Cancel\n");
  }

  AsciiPrint ("\nPress any key to return...\n");

  (VOID)ReadAnyKey (NULL, 0);

  return Status;
}

/**
  Entry point for Security Toggle Application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       Application performed the requested function
                            successfully
  @retval EFI_INVALID_PARAMETER  Invalid command argument
  @retval EFI_DEVICE_ERROR  Application failed
**/
EFI_STATUS
EFIAPI
FeatureEnablerToggleAppMain (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                 Status = EFI_SUCCESS;
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage  = NULL;
  CHAR16                    *ArgStr = NULL;

  Status = gBS->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (VOID *)&LoadedImage);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  if ( (LoadedImage->LoadOptions == NULL) || (LoadedImage->LoadOptionsSize == 0) )
  {
    Status = gST->ConOut->ClearScreen(gST->ConOut);
    AsciiPrint ("LoadOptions not valid\n");
    return EFI_UNSUPPORTED;
  }

  ArgStr = (CHAR16 *)LoadedImage->LoadOptions;

  /* Parse command-line arguments */
  if (StrCmp(ArgStr, L"/FeatureEnablerEnable") == 0)
  {
    Status = PerformFeatureEnablerEnable(TRUE);
  }
  else if (StrCmp(ArgStr, L"/FeatureEnablerDisable") == 0)
  {
    Status = PerformFeatureEnablerEnable(FALSE);
  }
  else
  {
    PrintUsage();
    Status = EFI_INVALID_PARAMETER;
  }

  return Status;
}
