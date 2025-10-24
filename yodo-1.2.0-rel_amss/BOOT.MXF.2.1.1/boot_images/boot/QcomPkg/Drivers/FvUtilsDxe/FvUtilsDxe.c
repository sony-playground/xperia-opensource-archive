/** @file FvUtilsDxe.c

Implementation for Qualcomm FV Utils protocol.

Copyright (c) 2019-2020 Qualcomm Technologies, Inc. All rights
reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/04/20   cm      added API LoadFileFromFv
 08/16/19   md      Initial revision. 

=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomLib.h>
#include <Library/GuidedFvLib.h>
#include <Library/MountFvLib.h>
#include <Library/UefiBootServicesTableLib.h>

/**
FV PROTOCOL interfaces
*/
#include <Protocol/EFIFVUtils.h>

BOOLEAN
CheckIfFvMounted (IN EFI_FV_PROTOCOL *This,
                  EFI_GUID           *FvGuid)
{
    DEBUG((EFI_D_INFO, "[FVUtilsProtocol]: GuidedFvIsMounted Invoked\n"));
    return GuidedFvIsMounted(FvGuid);
}


EFI_STATUS
LaunchAppFromFv (IN EFI_FV_PROTOCOL *This,
                 EFI_GUID           *FvGuid,
                 CHAR8              *AppName,
                 CHAR8              *Args OPTIONAL)
{
    DEBUG((EFI_D_INFO, "[FVUtilsProtocol]: LaunchAppFromGuidedFv Invoked\n"));
    return LaunchAppFromGuidedFv(FvGuid, AppName, Args);
}

EFI_STATUS
LoadFileFromFv (IN EFI_FV_PROTOCOL *This,
                EFI_GUID           *FvGuid,
				CHAR8      		   *FileName,
				OUT UINT8 		   **FileBuffer,
                OUT UINTN  		   *FileSize)
{
    DEBUG((EFI_D_INFO, "[FVUtilsProtocol]: LoadFileFromGuidedFv Invoked\n"));
    return LoadFileFromGuidedFv(FvGuid, FileName, FileBuffer, FileSize);
}


EFI_STATUS
MountFVFromPartition (IN EFI_FV_PROTOCOL *This,
                      IN  CONST CHAR8 *FvPartitionName, 
                      IN  EFI_GUID *PartitionGuid, 
                      IN  EFI_GUID *DesiredFvGuid,
                      IN  EFI_GUID *DesiredFVFileGUID)
{
    DEBUG((EFI_D_INFO, "[FVUtilsProtocol]: MountFvFromPartition Invoked\n"));
    return MountDesiredFVFromPartition(FvPartitionName, PartitionGuid, DesiredFvGuid, DesiredFVFileGUID);
}



/**
EFI_FV Protocol implementation
*/
EFI_FV_PROTOCOL gEfiFVUtilsProtocol =
{
    EFI_FV_UTILS_PROTOCOL_VERSION,
    MountFVFromPartition,
    CheckIfFvMounted,
    LaunchAppFromFv,
	LoadFileFromFv
};


/* Initializes FVUtils driver */
EFI_STATUS
EFIAPI
FVUtilsEntryPoint (IN EFI_HANDLE         ImageHandle,
                   IN EFI_SYSTEM_TABLE   *SystemTable)
{
  EFI_STATUS Status;
  
   // Install protocol
    Status = gBS->InstallMultipleProtocolInterfaces(&ImageHandle,
        &gEfiFVUtilsProtocolGuid,
        (void *)&gEfiFVUtilsProtocol,
        NULL);

  if (EFI_ERROR(Status)) {
        DEBUG((EFI_D_ERROR, "[FVUtilsDxe]FVEntryPoint: Failed to Install gFVUtilsProtocol protocol \r\n"));
    }

    return Status;
}
