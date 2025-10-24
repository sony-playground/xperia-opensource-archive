/**@file

Copyright (c) 2015 - 2021 Qualcomm Technologies Inc. All rights reserved.<BR>
Portions Copyright (c) 2006 - 2009, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiDxe.h>
#include <Library/PeCoffLib.h>
#include <Library/DebugLib.h>
#include <Library/PeCoffExtraActionLib.h>
#include <Library/DepLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/ImagePathUtilsLib.h>

VOID ProcessImageLoad (IN PE_COFF_LOADER_IMAGE_CONTEXT  *ImageContext);
VOID ProcessImageUnload (IN PE_COFF_LOADER_IMAGE_CONTEXT  *ImageContext);

STATIC VOID 
PrintEfiImageInfo(PE_COFF_LOADER_IMAGE_CONTEXT  *ImageContext)
{
  EFI_STATUS Status;
  UINTN Index;
  CHAR8 EfiFileName[256], *ImageName;

  DEBUG((EFI_D_WARN, " - 0x%9p [%5d] ",
        (VOID *) (UINTN) ImageContext->ImageAddress, GetTimerCountms ()));

  //
  // Print Module Name by Pdb file path.
  // Windows and Unix style file path are all trimmed correctly.
  //
  if (ImageContext->PdbPointer != NULL)
  {
    Status = GetImageNameFromPath(ImageContext->PdbPointer, &ImageName);
    if (Status != EFI_SUCCESS || ImageName == NULL)
    { 
      DEBUG((EFI_D_WARN, "Warn: Could not extract Filename"));
      return;
    }
    
    //
    // Copy the PDB file name to our temporary string, and replace .pdb with .efi
    // The PDB file name is limited in the range of 0~255.
    // If the length is bigger than 255, trim the redudant characters to avoid overflow in array boundary.
    //
    for (Index = 0; Index < sizeof (EfiFileName) - 4; Index++)
    {
      EfiFileName[Index] = ImageName[Index];

      if (EfiFileName[Index] == 0)
        EfiFileName[Index] = '.';

      if (EfiFileName[Index] == '.')
      {
        EfiFileName[Index + 1] = 'e';
        EfiFileName[Index + 2] = 'f';
        EfiFileName[Index + 3] = 'i';
        EfiFileName[Index + 4] = 0;
        break;
      }
    }

    if (Index == sizeof (EfiFileName) - 4)
      EfiFileName[Index] = 0;

    DEBUG ((EFI_D_WARN, "%a", EfiFileName)); // &ImageContext->PdbPointer[StartIndex]));
  }

  DEBUG ((EFI_D_WARN, "\n"));
}

/**
  Performs additional actions after a PE/COFF image has been loaded and relocated.

  If ImageContext is NULL, then ASSERT().

  @param  ImageContext  Pointer to the image context structure that describes the
                        PE/COFF image that has already been loaded and relocated.

**/
VOID
EFIAPI
PeCoffLoaderRelocateImageExtraAction (IN PE_COFF_LOADER_IMAGE_CONTEXT  *ImageContext)
{
  if (ImageContext == NULL)
    return;

  PrintEfiImageInfo (ImageContext);

  ProcessImageLoad (ImageContext);

#if (defined (ENABLE_DEP_64) || defined (ENABLE_DEP_32))
  EFI_STATUS Status;
  Status = SetupDep (ImageContext);
  {
    if (Status != EFI_SUCCESS)
      DEBUG ((EFI_D_ERROR, "ERROR: Failed to enable DEP\n"));
  }
#endif
}

/**
  Performs additional actions just before a PE/COFF image is unloaded.  Any resources
  that were allocated by PeCoffLoaderRelocateImageExtraAction() must be freed.
  
  If ImageContext is NULL, then ASSERT().
  
  @param  ImageContext  Pointer to the image context structure that describes the
                        PE/COFF image that is being unloaded.

**/
VOID
EFIAPI
PeCoffLoaderUnloadImageExtraAction (
  IN OUT PE_COFF_LOADER_IMAGE_CONTEXT  *ImageContext
  )
{
  if ((ImageContext == NULL) ||  (ImageContext->ImageSize == 0x0))
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Encountered NULL ImageContext\n"));
    return;
  }


#if (defined (ENABLE_DEP_64) || defined (ENABLE_DEP_32))
  EFI_STATUS Status;
  Status = ClearDep (ImageContext);
  {
    if (Status != EFI_SUCCESS)
      DEBUG ((EFI_D_ERROR, "ERROR: Failed to enable DEP\n"));
  }
#endif  

  ProcessImageUnload (ImageContext);
}
