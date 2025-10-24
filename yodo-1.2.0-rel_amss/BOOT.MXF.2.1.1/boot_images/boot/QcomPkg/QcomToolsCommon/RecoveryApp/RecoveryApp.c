/** @file RecoveryApp.c

Test Application for EFI_RECOVERY protocol

Copyright (c) 2021 Qualcomm Technologies, Inc.
Portions Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
EDIT HISTORY


when           who         what, where, why
--------       ---         --------------------------------------------------
2021/08/24     dmohan      Fixed Klocwork issues
2021/04/12     dmohan      Initial revision
=============================================================================*/

#include <Library/QcomLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/FwCommonLib.h>
#include <Guid/ZeroGuid.h>
#include <Protocol/Shell.h>
#include <Protocol/EFIRecovery.h>
#include <Protocol/EFISmem.h>
#include "boot_recovery_partition.h"

/**
  Print APP usage.
**/
VOID
PrintUsage (VOID)
{
  AsciiPrint("RecoveryApp:  usage\n");
  AsciiPrint("  RecoveryApp <option> <args>\n");
  AsciiPrint("Usage:\n");
  AsciiPrint("  RecoveryApp.efi -SetRecoverySMEM Fail <primary_guid>\n");
  AsciiPrint("  RecoveryApp.efi -SetRecoverySMEM Pass <primary_guid> <secondary_guid>\n");
  AsciiPrint("  RecoveryApp.efi -SetRecoveryFail <primary_guid>\n");
  AsciiPrint("  RecoveryApp.efi -SetPartitionsUnderUpdate <filename.txt>\n");
  AsciiPrint("  RecoveryApp.efi -ClearPartitionsUnderUpdate\n");
}

/**
  Read a file.

  @param[in]  FileName        The file to be read.
  @param[out] BufferSize      The file buffer size
  @param[out] Buffer          The file buffer

  @retval EFI_SUCCESS    Read file successfully
  @retval EFI_NOT_FOUND  Shell protocol or file not found
  @retval others         Read file failed
**/
EFI_STATUS
ReadFileToBuffer (
  IN  CHAR16            *FileName,
  OUT UINTN             *BufferSize,
  OUT VOID             **Buffer
  )
{
  EFI_STATUS                        status = EFI_SUCCESS;
  EFI_SHELL_PROTOCOL               *mShellProtocol = NULL;
  SHELL_FILE_HANDLE                 handle = NULL;
  UINT64                            fileSize= 0;
  UINTN                             tempBufferSize= 0;
  VOID                             *tempBuffer = NULL;

  status = gBS->LocateProtocol (
                  &gEfiShellProtocolGuid,
                  NULL,
                  (VOID **) &mShellProtocol
                  );
  if (EFI_ERROR (status))
  {
    mShellProtocol = NULL;
    return EFI_NOT_FOUND;
  }

  // Open file by FileName.
  status = mShellProtocol->OpenFileByName (
    FileName,
    &handle,
    EFI_FILE_MODE_READ
    );
  if (EFI_ERROR (status))
  {
    return status;
  }

  // Get the file size.
  status = mShellProtocol->GetFileSize (handle, &fileSize);
  if (EFI_ERROR (status))
  {
    mShellProtocol->CloseFile (handle);
    return status;
  }

  tempBufferSize = (UINTN) fileSize;
  tempBuffer = AllocateZeroPool (tempBufferSize);
  if (tempBuffer == NULL)
  {
    mShellProtocol->CloseFile (handle);
    return EFI_OUT_OF_RESOURCES;
  }

  // Read the file data to the buffer
  status = mShellProtocol->ReadFile (
    handle,
    &tempBufferSize,
    tempBuffer
    );
  if (EFI_ERROR (status))
  {
    mShellProtocol->CloseFile (handle);
    return status;
  }

  mShellProtocol->CloseFile (handle);

  *BufferSize = tempBufferSize;
  *Buffer     = tempBuffer;
  return EFI_SUCCESS;
}

EFI_STATUS
WriteToRecoverySmemVariable(
  EFI_GUID    PrimaryGuid,
  EFI_GUID    SecondaryGuid
  )
{
  EFI_STATUS                     status            = EFI_SUCCESS;
  smem_recovery_partitions_info *pSmemRecoveryInfo = NULL;
  EFI_SMEM_PROTOCOL             *smem_protocol     = NULL;
  UINT32                         buf_size          = 0;
  UINT8                          indexToWrite      = 0;

  status = gBS->LocateProtocol(
    &gEfiSMEMProtocolGuid,
    NULL,
    (void**)&smem_protocol
    );
  if (EFI_ERROR(status))
  {
    AsciiPrint("Failed to locate SMEM protocol\n.");
    goto WriteToRecoverySmemVariableExit;
  }

  AsciiPrint("smem protocol = %p\n", smem_protocol);

  status = smem_protocol->SmemGetAddr(
    RECOVERY_PARTITION_SMEM_ID,
    &buf_size,
    (void **)&pSmemRecoveryInfo);
  if (EFI_ERROR(status))
  {
    AsciiPrint("SmemGetAddr failed with status: %r\n.", status);
    goto WriteToRecoverySmemVariableExit;
  }

  if(pSmemRecoveryInfo == NULL)
  {
    AsciiPrint("SMEM Recovery buffer in NULL.\n");
    status= EFI_NOT_READY;
    goto WriteToRecoverySmemVariableExit;
  }

  if (pSmemRecoveryInfo->num_of_entries < pSmemRecoveryInfo->max_entries)
  {
    indexToWrite = pSmemRecoveryInfo->num_of_entries;

    CopyMem(
      pSmemRecoveryInfo->partition_info[indexToWrite].corrupted_partition_id,
      &PrimaryGuid,
      sizeof(EFI_GUID)
      );
    AsciiPrint(
      "Setting corrupted_partition_id: %g.\n", 
      pSmemRecoveryInfo->partition_info[indexToWrite].corrupted_partition_id
    );

    CopyMem(
      pSmemRecoveryInfo->partition_info[indexToWrite].recovery_partition_id,
      &SecondaryGuid,
      sizeof(EFI_GUID)
      );
    AsciiPrint(
      "Setting recovery_partition_id: %g.\n", 
      pSmemRecoveryInfo->partition_info[indexToWrite].recovery_partition_id
    );

    pSmemRecoveryInfo->num_of_entries++;
  }

WriteToRecoverySmemVariableExit:
  return status;
}

EFI_STATUS
GetRecoveryProtocol(
  EFI_RECOVERY_PROTOCOL    **hRecoveryProtocol
  )
{
  EFI_STATUS    status = EFI_SUCCESS;

  // Get Recovery protocol interface
  status = gBS->LocateProtocol(
    &gEfiRecoveryProtocolGuid,
    NULL,
    (VOID **)hRecoveryProtocol
    );
  if (EFI_ERROR(status))
  {
    DEBUG((EFI_D_ERROR, "Failed to locate Recovery Protocol.\n"));
    return status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
ConfigurePartitionsUnderUpdate(
  UINTN       Argc,
  CHAR8     **Argv
  )
{
  EFI_STATUS              status = EFI_SUCCESS;
  EFI_RECOVERY_PROTOCOL  *hRecoveryProtocol = NULL;
  EFI_GUID               *capsulePendingList = NULL;
  UINTN                   capsulePendingListSize =0;
  UINTN                   guidBufferSize = 0;
  VOID                   *guidBuffer = NULL;
  CHAR16                  fileName[256] = {0};
  UINTN                   numOfGuidEntries = 0;
  UINT8                   i = 0;
  UINT8                   j = 0;

  if (Argc < 3)
  {
    PrintUsage();
    status = EFI_NOT_FOUND;
    goto ConfigurePartitionsUnderUpdateExit;
  }

  AsciiStrToUnicodeStr(Argv[2], fileName);
  AsciiPrint("fileName: %s\n", fileName);

  status = GetRecoveryProtocol(&hRecoveryProtocol);
  if (EFI_ERROR(status))
  {
    AsciiPrint ("GetRecoveryProtocol failed with status: %r\n", status);
    goto ConfigurePartitionsUnderUpdateExit;
  }

  status = ReadFileToBuffer (
    fileName,
    &guidBufferSize,
    &guidBuffer
    );
  if (EFI_ERROR(status))
  {
    AsciiPrint ("ReadFileToBuffer failed with status: %r\n", status);
    goto ConfigurePartitionsUnderUpdateExit;
  }

  numOfGuidEntries = (guidBufferSize/GUID_STRING_LENGTH);
  AsciiPrint("numOfGuidEntries: %d\n", numOfGuidEntries);

  capsulePendingListSize = (numOfGuidEntries * (sizeof(EFI_GUID)));
  AsciiPrint("capsulePendingListSize: %d\n", capsulePendingListSize);

  capsulePendingList = AllocateZeroPool (capsulePendingListSize);
  if (capsulePendingList == NULL)
  {
    status =  EFI_OUT_OF_RESOURCES;
    goto ConfigurePartitionsUnderUpdateExit;
  }

  CHAR8 *tempBuf = (CHAR8 *)guidBuffer;

  for (i = 0; i < numOfGuidEntries; i++)
  {
    //AsciiPrint("guidBuffer[%d]: %a\n", j, &tempBuf[j]);
    AsciiStrToGuid(&tempBuf[j], &capsulePendingList[i]);
    AsciiPrint("Input capsulePendingList[%d]: %g\n", i, &capsulePendingList[i]);

    // Incrementing by 2 for '\r\n' added at the end of the line in text file.
    j += (GUID_STRING_LENGTH + 2);
  }

  // Register paritions pending for update.
  status = hRecoveryProtocol->SetPartitionsUnderUpdate (
    capsulePendingList,
    capsulePendingListSize
    );
  if (EFI_ERROR(status))
  {
    AsciiPrint ("SetPartitionsUnderUpdate failed with status: %r\n", status);
    goto ConfigurePartitionsUnderUpdateExit;
  }

ConfigurePartitionsUnderUpdateExit:
  if (capsulePendingList != NULL)
  {
    FreePool(capsulePendingList);
    capsulePendingList = NULL;
  }

  return status;
}

EFI_STATUS
ClearPartitionsUnderUpdate(VOID)
{
  EFI_STATUS              status = EFI_SUCCESS;
  EFI_RECOVERY_PROTOCOL  *hRecoveryProtocol = NULL;
  EFI_GUID               *capsulePendingList = NULL;
  UINTN                   capsulePendingListSize =0;

  status = GetRecoveryProtocol(&hRecoveryProtocol);
  if (EFI_ERROR(status))
  {
    AsciiPrint ("GetRecoveryProtocol failed\n");
    goto ClearPartitionsUnderUpdateExit;
  }

  status = GetVariable2(
    QCOM_FW_UPDATE_NV_PARTITIONS_UNDER_UPDATE_NAME,
    &gQcomTokenSpaceGuid,
    (VOID **)&capsulePendingList,
    &capsulePendingListSize
    );
  if (EFI_ERROR(status))
  {
    AsciiPrint(
      "Failed to get partitions under update from NV. Status: %r\n",
      status
      );
    goto ClearPartitionsUnderUpdateExit;
  }

  // Clear paritions pending for update.
  status = hRecoveryProtocol->ClearPartitionsUnderUpdate(
    capsulePendingList,
    capsulePendingListSize
    );
  if (EFI_ERROR(status))
  {
    AsciiPrint ("ClearPartitionsUnderUpdate failed with status: %r\n", status);
    goto ClearPartitionsUnderUpdateExit;
  }
  AsciiPrint ("ClearPartitionsUnderUpdate completed.\n");

ClearPartitionsUnderUpdateExit:
  if (capsulePendingList != NULL)
  {
    FreePool(capsulePendingList);
    capsulePendingList = NULL;
  }

  return status;
}

EFI_STATUS
SetRecoverySMEM (
  UINTN       Argc,
  CHAR8     **Argv
  )
{
  EFI_STATUS              status = EFI_SUCCESS;
  EFI_GUID                primaryGuid = ZERO_GUID;
  EFI_GUID                secondaryGuid = ZERO_GUID;

  if (Argc < 4)
  {
    PrintUsage();
    status = EFI_INVALID_PARAMETER;
    goto SetRecoverySMEMExit;
  }

  if (0 == AsciiStriCmp(Argv[2], "Fail"))
  {
    AsciiStrToGuid(Argv[3], &primaryGuid);
  }
  else if ((0 == AsciiStriCmp(Argv[2], "Pass")) &&
           (5 == Argc))
  {
    AsciiStrToGuid(Argv[3], &primaryGuid);
    AsciiStrToGuid(Argv[4], &secondaryGuid);
  }
  else
  {
    PrintUsage();
    status = EFI_INVALID_PARAMETER;
    goto SetRecoverySMEMExit;
  }

  status = WriteToRecoverySmemVariable(primaryGuid, secondaryGuid);
  if (EFI_ERROR(status))
  {
    AsciiPrint("WriteToRecoverySmemVariable failed with status: %r\n", status);
    goto SetRecoverySMEMExit;
  }

SetRecoverySMEMExit:
  return status;
}

EFI_STATUS
SetRecoveryFailed (
  UINTN       Argc,
  CHAR8     **Argv
  )
{
  EFI_STATUS              status = EFI_SUCCESS;
  EFI_GUID                primaryGuid = ZERO_GUID;
  EFI_GUID               *pRecoveryNVItem = NULL;
  UINTN                   recoveryNVSize = 0;

  if (Argc < 3)
  {
    PrintUsage();
    status = EFI_INVALID_PARAMETER;
    goto SetRecoveryFailedExit;
  }

  AsciiStrToGuid(Argv[2], &primaryGuid);

  recoveryNVSize = (sizeof(EFI_GUID));
  pRecoveryNVItem = AllocateZeroPool (recoveryNVSize);
  if (pRecoveryNVItem == NULL)
  {
    status =  EFI_OUT_OF_RESOURCES;
    AsciiPrint(
      "SetRecoveryFailed: Memory allocation failed with status: %r\n",
      status);
    goto SetRecoveryFailedExit;
  }

  CopyMem(pRecoveryNVItem, &primaryGuid, recoveryNVSize);

  status = gRT->SetVariable (
    RECOVERY_FAILED_NV,
    &gQcomTokenSpaceGuid,
    (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS),
    recoveryNVSize,
    pRecoveryNVItem
    );
  if (EFI_ERROR(status))
  {
    AsciiPrint("Failed to configure Recovery NV.\n");
    goto SetRecoveryFailedExit;
  }

  status = GetVariable2(
    RECOVERY_FAILED_NV,
    &gQcomTokenSpaceGuid,
    (VOID **)&pRecoveryNVItem,
    &recoveryNVSize
    );
  if (EFI_ERROR(status))
  {
    AsciiPrint("Failed to get RECOVERY_FAILED_NV.\n");
    goto SetRecoveryFailedExit;
  }

  if (pRecoveryNVItem == NULL)
  {
    AsciiPrint("pRecoveryNVItem returned from GetVariable2 is NULL.\n");
    status = EFI_DEVICE_ERROR;
    goto SetRecoveryFailedExit;
  }

  if ((recoveryNVSize != sizeof(primaryGuid)) ||
      (!CompareGuid(&primaryGuid,pRecoveryNVItem)))
  {
    AsciiPrint("pRecoveryNVItem: %g.\n", pRecoveryNVItem);
    AsciiPrint("Recovery NV is configured with incorrect value.\n");
    goto SetRecoveryFailedExit;
  }

SetRecoveryFailedExit:
  return status;
}

/**
  Recovery test application entry point

  @param[in]  ImageHandle     The image handle.
  @param[in]  SystemTable     The system table.

  @retval EFI_SUCCESS            Command completed successfully.
  @retval EFI_INVALID_PARAMETER  Command usage error.
  @retval EFI_NOT_FOUND          The input file can't be found.
**/
EFI_STATUS
EFIAPI
RecoveryAppMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS              status = EFI_SUCCESS;
  UINTN                   Argc = 0;
  CHAR8                 **Argv = NULL;

  status = GetCmdLineArgs (ImageHandle, &Argc, &Argv);
  if (EFI_ERROR(status))
  {
    AsciiPrint("Failed to get commmand line arguments! Status: %r\n",status);
    goto Exit;
  }

  if (Argc < 2)
  {
    PrintUsage();
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if ( 0 == AsciiStriCmp(Argv[1], "-SetRecoverySMEM"))
  {
    AsciiPrint ("SetRecoverySMEM entry\n");
    status = SetRecoverySMEM (Argc, Argv);
    if (EFI_ERROR(status))
    {
      AsciiPrint ("SetRecoverySMEM failed\n");
      goto Exit;
    }
    AsciiPrint ("SetRecoverySMEM exit\n");
  }
  else if ( 0 == AsciiStriCmp(Argv[1], "-SetRecoveryFail"))
  {
    AsciiPrint ("SetRecoveryFail entry\n");
    status = SetRecoveryFailed (Argc, Argv);
    if (EFI_ERROR(status))
    {
      AsciiPrint ("SetRecoveryFail failed\n");
      goto Exit;
    }
    AsciiPrint ("SetRecoveryFail exit\n");
  }
  else if ( 0 == AsciiStriCmp(Argv[1], "-SetPartitionsUnderUpdate"))
  {
    AsciiPrint ("SetPartitionsUnderUpdate entry\n");
    status = ConfigurePartitionsUnderUpdate (Argc, Argv);
    if (EFI_ERROR(status))
    {
      AsciiPrint ("SetPartitionsUnderUpdate failed\n");
      goto Exit;
    }
    AsciiPrint ("SetPartitionsUnderUpdate exit\n");
  }
  else if ( 0 == AsciiStriCmp(Argv[1], "-ClearPartitionsUnderUpdate"))
  {
    AsciiPrint ("ClearPartitionsUnderUpdate entry\n");
    status = ClearPartitionsUnderUpdate();
    if (EFI_ERROR(status))
    {
      AsciiPrint ("ClearPartitionsUnderUpdate failed\n");
      goto Exit;
    }
    AsciiPrint ("ClearPartitionsUnderUpdate exit\n");
  }
  else
  {
    AsciiPrint ("Not supported option.\n");
  }

  status = EFI_SUCCESS;

Exit:
  return status;
}
