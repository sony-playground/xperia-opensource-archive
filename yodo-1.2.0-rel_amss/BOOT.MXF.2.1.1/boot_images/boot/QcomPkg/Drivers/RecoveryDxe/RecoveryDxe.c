/** @file RecoveryDxe.c

Implementation for Qualcomm UEFI Recovery protocol

Copyright (c) 2021 Qualcomm Technologies, Inc.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.

**/

/*=============================================================================
EDIT HISTORY


when           who         what, where, why
--------       ---         --------------------------------------------------
2021/09/15     dmohan      Removed temporary hack added to skip APDP recovery
2021/08/27     dmohan      Added changes to skip APDP partition recovery as 
                           temporary hack to avoid boot delay
2021/08/24     dmohan      Fixed Klocwork issues
2021/02/13     dmohan      Initial revision
=============================================================================*/

#include <Library/UefiBootServicesTableLib.h>
#include <Library/FwCommonLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/QcomLib.h>
#include <Library/DisplayUpdateProgressLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/GenericBdsLib.h>
#include <Library/TargetResetLib.h>
#include <Protocol/BlockIo.h>
#include <Protocol/GraphicsOutput.h>
#include <RecoveryDxe.h>
#include <RecoveryDxeUtil.h>
#include "BootConfig.h"

/**
EFI_RECOVERY PROTOCOL interfaces
*/
#include <Protocol/EFIRecovery.h>

#define     BACKUP_PARTITION_PREFIX         L"BACKUP_"

const CHAR16 *RecoveryStatusStr[RECOVERY_COMPLETE+1] = 
{
  L"Unknown",
  L"Not Attempted",
  L"Failed",
  L"Complete"
};

//Internal functions
EFI_STATUS
GetPartitionsUnderUpdate (
  OUT EFI_GUID                 **CapsulePendingList,
  OUT UINTN                     *CapsulePendingListSize
  )
{
  EFI_STATUS      status                    = EFI_SUCCESS;
  UINT8           maxItems                  = 0;
  UINT8           idx                       = 0;

  // Input parameter validation
  if ((NULL == CapsulePendingList) ||
      (NULL == CapsulePendingListSize))
  {
    DEBUG((EFI_D_ERROR, "GetPartitionsUnderUpdate: Invalid input parameters.\n"));
    status = EFI_INVALID_PARAMETER;
    goto GetPartitionsUnderUpdateExit;
  }

  status = GetCapsulePendingList (
    QCOM_FW_UPDATE_NV_PARTITIONS_UNDER_UPDATE,
    (VOID **)CapsulePendingList,
    CapsulePendingListSize
    );
  if (status == EFI_NOT_FOUND)
  {
    DEBUG((EFI_D_WARN, "GetPartitionsUnderUpdate: CapsulePendingList is empty.\n"));
    status = EFI_SUCCESS;
    goto GetPartitionsUnderUpdateExit;
  }
  HANDLE_ERROR_LABEL(status, GetCapsulePendingList, GetPartitionsUnderUpdateExit);

  maxItems = (*CapsulePendingListSize)/sizeof(EFI_GUID);

  for (idx = 0; idx < maxItems; idx++)
  {
    DEBUG((
      EFI_D_INFO,
      "GetPartitionsUnderUpdate: CapsulePendingList[%d]: %g\n", 
      idx, 
      (*CapsulePendingList + idx)));
  }

GetPartitionsUnderUpdateExit:
  return status;

}

EFI_STATUS
ClearPartitionsUnderUpdate (
  IN EFI_GUID                  *CapsulePendingList,
  IN UINTN                      CapsulePendingListSize
  )
{
  EFI_STATUS      status                    = EFI_SUCCESS;

  // Input parameter validation
  if (NULL == CapsulePendingList)
  {
    DEBUG((EFI_D_ERROR, "ClearPartitionsUnderUpdate: Invalid input parameters.\n"));
    status = EFI_INVALID_PARAMETER;
    goto ClearPartitionsUnderUpdateExit;
  }

  // Clear capsule pending list
  ZeroMem(CapsulePendingList, CapsulePendingListSize);
  CapsulePendingListSize = 0;

  status = SetCapsulePendingList (
    QCOM_FW_UPDATE_NV_PARTITIONS_UNDER_UPDATE,
    CapsulePendingList,
    CapsulePendingListSize
    );
  HANDLE_ERROR_LABEL(status, SetCapsulePendingList, ClearPartitionsUnderUpdateExit);

ClearPartitionsUnderUpdateExit:
  return status;

}

EFI_STATUS
InitRecoveryStatus (
  IN EFI_RECOVERY_PROTOCOL       *This,
  IN EFI_GUID                    *CapsulePendingList,
  IN UINTN                        CapsulePendingListSize,
  IN RECOVERY_STATUS_TYPE         DefaultRecoveryStatus
  )
{
  EFI_STATUS               status                 = EFI_SUCCESS;
  PRECOVERY_PRIVATE_DATA   pPrivate               = NULL;
  UINT8                    i                      = 0;
  UINT8                    j                      = 0;
  UINT8                    count                  = 0;

  // Retrieve the private context structure
  pPrivate = RECOVERY_PRIVATE_DATA_FROM_THIS(This);

  if (CapsulePendingListSize != 0)
  {
    count = (CapsulePendingListSize/sizeof(EFI_GUID));
  }

  pPrivate->PartitionsUnderUpdateCount = 0;

  for (i = 0; i < pPrivate->RecoveryItemCount; i++)
  {
    DEBUG((
      EFI_D_INFO,
      "InitRecoveryStatus: PrimaryGuid[%d]: %g.SecondaryGuid[%d]: %g\n",
      i, &pPrivate->RecoveryEntries[i].PrimaryGuid,
      i, &pPrivate->RecoveryEntries[i].SecondaryGuid
      ));

    pPrivate->RecoveryEntries[i].RecoveryStatus = DefaultRecoveryStatus;

    for (j = 0; j < count; j++)
    {
      if ((CompareGuid (&pPrivate->RecoveryEntries[i].PrimaryGuid, &CapsulePendingList[j])) ||
          (CompareGuid (&pPrivate->RecoveryEntries[i].SecondaryGuid, &CapsulePendingList[j])))
      {
        pPrivate->RecoveryEntries[i].RecoveryStatus = RECOVERY_NOT_ATTEMPTED;
        pPrivate->PartitionsUnderUpdateCount++;
        break;
      }
    }
  }

  return status;
}

EFI_STATUS
GetRecoveryPartitionHandle (
  IN EFI_GUID                 *PartGuid,
  OUT EFI_HANDLE              *PartHandle,
  OUT UINTN                   *PartSize      OPTIONAL
  )
{
  EFI_STATUS                status                     = EFI_SUCCESS;
  UINT32                    attribs                    = 0;
  PartiSelectFilter         handleFilter[2]            = {0};
  HandleInfo                handleInfoList[2]          = {0};
  EFI_BLOCK_IO_PROTOCOL    *blockIo                    = NULL;
  UINT32                    maxHandles                 = 0;
  EFI_GUID                  boot_guid                  = {0};
  EFI_GUID                  gpp_guid                   = {0};
  UINT32                    numFilters                 = 1;

  // Input parameter validation
  if ((NULL == PartGuid) ||
      (NULL == PartHandle))
  {
    DEBUG((EFI_D_ERROR, "GetRecoveryPartitionHandle: Invalid input parameters.\n"));
    status = EFI_INVALID_PARAMETER;
    goto GetRecoveryPartitionHandleExit;
  }

  attribs |= BLK_IO_SEL_MEDIA_TYPE_NON_REMOVABLE;
  attribs |= BLK_IO_SEL_PARTITIONED_GPT;
  attribs |= BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID;
  attribs |= BLK_IO_SEL_STRING_CASE_INSENSITIVE;

  handleFilter[0].PartitionType = PartGuid;
  handleFilter[0].VolumeName = NULL;
  handleFilter[0].RootDeviceType = NULL;
  handleFilter[0].PartitionLabel = NULL;

  if (boot_from_ufs())
  {
    attribs |= BLK_IO_SEL_MATCH_ROOT_DEVICE;
    status = GetPartitionGUIDs(&boot_guid, &gpp_guid);
    HANDLE_ERROR_LABEL(status, GetPartitionGUIDs, GetRecoveryPartitionHandleExit);

    handleFilter[0].RootDeviceType = &boot_guid;
    handleFilter[1].RootDeviceType = &gpp_guid;
    handleFilter[1].PartitionType = PartGuid;
    numFilters++;
  }

  for (UINT8 i = 0; i < numFilters; i++)
  {
    status = GetBlkIOHandles (attribs, &handleFilter[i], handleInfoList, &maxHandles);
    DEBUG(( EFI_D_INFO, "GetRecoveryPartitionHandle: RootDeviceType: %g\n", handleFilter[i].RootDeviceType));
    DEBUG(( EFI_D_INFO, "GetRecoveryPartitionHandle: maxHandles: %d\n", maxHandles));
    if ((status == EFI_SUCCESS) && (maxHandles == 1))
    {
      break;
    }
  }

  if(maxHandles == 0)
  {
    status = EFI_NOT_FOUND;
    DEBUG(( EFI_D_WARN, "GetRecoveryPartitionHandle: No handles found.\n"));
    goto GetRecoveryPartitionHandleExit;
  }
  else if(maxHandles != 1)
  {
    status = EFI_UNSUPPORTED;
    DEBUG((
      EFI_D_WARN,
      "GetRecoveryPartitionHandle: More than one handle found.\n",
      status
      ));
    goto GetRecoveryPartitionHandleExit;
  }

  *PartHandle = handleInfoList[0].Handle;

  if (PartSize)
  {
    blockIo = handleInfoList[0].BlkIo;
    *PartSize = (blockIo->Media->LastBlock + 1) * blockIo->Media->BlockSize;
    DEBUG(( EFI_D_INFO, "GetRecoveryPartitionHandle: PartSize = %d\n", *PartSize));
  }

GetRecoveryPartitionHandleExit:
  return status;
}

EFI_STATUS
CalculateTotalSizeOfPartitionsUnderRecovery (
  IN EFI_RECOVERY_PROTOCOL       *This
  )
{
  EFI_STATUS               status                 = EFI_SUCCESS;
  PRECOVERY_PRIVATE_DATA   pPrivate               = NULL;
  UINT8                    idx                    = 0;
  UINTN                    sizeOfPartition        = 0;

  // Retrieve the private context structure
  pPrivate = RECOVERY_PRIVATE_DATA_FROM_THIS(This);

  for (idx = 0; idx < pPrivate->RecoveryItemCount; idx++)
  {
    // Partition size will not be calculated for those pending for capsule update.
    if (pPrivate->RecoveryEntries[idx].RecoveryStatus == RECOVERY_NOT_ATTEMPTED)
    {
      continue;
    }

    status = GetRecoveryPartitionHandle (
      &pPrivate->RecoveryEntries[idx].PrimaryGuid,
      &pPrivate->RecoveryEntries[idx].PrimaryPartitionHandle,
      &sizeOfPartition
      );
    HANDLE_ERROR_LABEL(status, GetRecoveryPartitionHandle, CalculateTotalSizeOfPartitionsUnderRecoveryExit);

    pPrivate->TotalRecoveryPartitionSize += sizeOfPartition;
  }

  DEBUG((
    EFI_D_WARN,
    "CalculateTotalSizeOfPartitionsUnderRecovery: TotalRecoveryPartitionSize = %d\n",
    pPrivate->TotalRecoveryPartitionSize
    ));

CalculateTotalSizeOfPartitionsUnderRecoveryExit:
  return status;
}

EFI_STATUS
UpdateRecoveryProgress (
  IN EFI_RECOVERY_PROTOCOL       *This,
  IN UINTN                        Completion
  )
{
  EFI_STATUS                            status     = EFI_SUCCESS;
  static UINTN                          seconds    = 0;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL_UNION  *pColor     = NULL;
  PRECOVERY_PRIVATE_DATA                pPrivate   = NULL;

  if (Completion > 100)
  {
    DEBUG((EFI_D_ERROR, "UpdateRecoveryProgress: Invalid input parameters.\n"));
    return EFI_INVALID_PARAMETER;
  }

  DEBUG((EFI_D_WARN, "UpdateRecoveryProgress: Progress - %d%%\n", Completion));

  if (seconds == 0)
  {
    // Retrieve the private context structure
    pPrivate = RECOVERY_PRIVATE_DATA_FROM_THIS(This);

    seconds = pPrivate->RecoveryProgress.WatchdogSeconds;
    pColor = &pPrivate->RecoveryProgress.ProgressBarForegroundColor;
  }

  // Cancel the watchdog timer
  gBS->SetWatchdogTimer (0, 0x0000, 0, NULL);

  if (Completion != 100)
  {
    // Arm the watchdog timer from PCD setting
    if (seconds != 0)
    {
      DEBUG ((
        EFI_D_INFO,
        "UpdateRecoveryProgress: Arm watchdog timer %d seconds\n",
        seconds
        ));
      gBS->SetWatchdogTimer (seconds, 0x0000, 0, NULL);
    }
  }

  status = DisplayUpdateProgress (Completion, pColor);

  return status;
}

EFI_STATUS
UpdateRecoveryTextDisplay (
  IN EFI_RECOVERY_PROTOCOL       *This
  )
{
  EFI_STATUS                           status           = EFI_SUCCESS;
  PRECOVERY_PRIVATE_DATA               pPrivate         = NULL;
  EFI_GRAPHICS_OUTPUT_PROTOCOL        *pGop             = NULL;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL_UNION  foregroundcolour = {0};
  UINT32                               offsetX          = 0;
  UINT32                               offsetY          = 0;
  UINT32                               startX           = 0;
  UINT32                               startY           = 0;
  UINTN                                numOfChars       = 0;

  // Retrieve the private context structure
  pPrivate = RECOVERY_PRIVATE_DATA_FROM_THIS(This);
  foregroundcolour.Raw = pPrivate->RecoveryTextColour;

  status = gBS->LocateProtocol (
    &gEfiGraphicsOutputProtocolGuid,
    NULL,
    (VOID **)&pGop
    );
  if (EFI_ERROR (status))
  {
    DEBUG ((
      EFI_D_ERROR,
      "UpdateRecoveryTextDisplay: Could not locate GOP. Status = %r\n",
      status
      ));
    status = EFI_NOT_READY;
    goto UpdateRecoveryTextDisplayExit;
  }

  offsetX = pGop->Mode->Info->HorizontalResolution;
  offsetY = pGop->Mode->Info->VerticalResolution;
  DEBUG((EFI_D_INFO, "UpdateRecoveryTextDisplay: offsetX: %d\n", offsetX));
  DEBUG((EFI_D_INFO, "UpdateRecoveryTextDisplay: offsetY: %d\n", offsetY));

  startX = ((offsetX - StrLen(pPrivate->RecoveryProgressString) * EFI_GLYPH_WIDTH) / 2);
  DEBUG((EFI_D_INFO, "UpdateRecoveryTextDisplay: startX: %d\n", startX));

  startY = ((offsetY * 80) / 100);
  DEBUG((EFI_D_INFO, "UpdateRecoveryTextDisplay: startY: %d\n", startY));

  numOfChars = PrintXY(
    startX,
    startY,
    &foregroundcolour.Pixel,
    NULL,
    pPrivate->RecoveryProgressString
    );
  DEBUG((EFI_D_INFO, "UpdateRecoveryTextDisplay: numOfChars: %d\n", numOfChars));

UpdateRecoveryTextDisplayExit:
  return status;
}

EFI_STATUS
ValidateRecoveryList (
  IN EFI_RECOVERY_PROTOCOL       *This
  )
{
  EFI_STATUS               status                 = EFI_SUCCESS;
  PRECOVERY_PRIVATE_DATA   pPrivate               = NULL;
  UINT8                    i                      = 0;
  UINT8                    j                      = 0;

  // Retrieve the private context structure
  pPrivate = RECOVERY_PRIVATE_DATA_FROM_THIS(This);

  for (i = 0; i < (pPrivate->RecoveryItemCount-1); i++)
  {
    DEBUG((
      EFI_D_WARN,
      "ValidateRecoveryList: PrimaryGuid[%d]: %g.SecondaryGuid[%d]: %g\n",
      i, &pPrivate->RecoveryEntries[i].PrimaryGuid,
      i, &pPrivate->RecoveryEntries[i].SecondaryGuid
      ));

    for (j = i+1; j < pPrivate->RecoveryItemCount; j++)
    {
      // Call target panic when SMEM variable contains both <primary_A,secondary_A>
      // and (<X, primary_A> or <secondary_A, X>)
      if ((CompareGuid (
            &pPrivate->RecoveryEntries[i].PrimaryGuid,
            &pPrivate->RecoveryEntries[j].SecondaryGuid)) ||
          (CompareGuid (
            &pPrivate->RecoveryEntries[i].SecondaryGuid,
            &pPrivate->RecoveryEntries[j].PrimaryGuid)))
      {
        TargetPanic();
      }
    }
  }

  return status;
}

EFI_STATUS
GetPartitionEntry (
  IN EFI_HANDLE                 Handle,
  OUT EFI_PARTITION_ENTRY     **PartEntry
  )
{
  EFI_STATUS               status                   = EFI_SUCCESS;

  status = gBS->HandleProtocol(
    Handle,
    &gEfiPartitionRecordGuid,
    (VOID **) PartEntry
    );
  if (EFI_ERROR(status))
  {
    DEBUG((
      EFI_D_WARN,
      "GetPartitionEntry: HandleProtocol returned status: %r\n",
      status
      ));
    goto GetPartitionEntryExit;
  }

GetPartitionEntryExit:
  return status;
}

EFI_STATUS
ValidatePartitionName (
  IN EFI_HANDLE                 PrimaryHandle,
  IN EFI_HANDLE                 SecondaryHandle
  )
{
  EFI_STATUS               status                   = EFI_SUCCESS;
  EFI_PARTITION_ENTRY     *primaryEntry             = {0};
  EFI_PARTITION_ENTRY     *secondaryEntry           = {0};
  CHAR16                  *tempStr                  = NULL;
  CHAR16                  *primaryPartitionName     = NULL;
  CHAR16                  *backupPartitionName      = NULL;
  INTN                     diff                     = 0;

  // Input parameter validation
  if ((NULL == PrimaryHandle) ||
      (NULL == SecondaryHandle))
  {
    DEBUG((EFI_D_ERROR, "ValidatePartitionName: Invalid input parameters.\n"));
    status = EFI_INVALID_PARAMETER;
    goto ValidatePartitionNameExit;
  }

  status = GetPartitionEntry(
    PrimaryHandle,
    &primaryEntry
    );
  if (EFI_ERROR(status))
  {
    DEBUG((
      EFI_D_WARN,
      "ValidatePartitionName: GetPartitionEntry returned status: %r\n",
      status
      ));
    goto ValidatePartitionNameExit;
  }

  DEBUG((
    EFI_D_INFO,
    "ValidatePartitionName: primaryPartitionName: %s\n",
    primaryEntry->PartitionName
    ));

  status = GetPartitionEntry(
    SecondaryHandle,
    &secondaryEntry
    );
  if (EFI_ERROR(status))
  {
    DEBUG((
      EFI_D_WARN,
      "ValidatePartitionName: GetPartitionEntry returned status: %r\n",
      status
      ));
    goto ValidatePartitionNameExit;
  }

  DEBUG((
    EFI_D_INFO,
    "ValidatePartitionName: secondaryPartitionName: %s\n",
    secondaryEntry->PartitionName
    ));

  tempStr = AllocateZeroPool(sizeof(secondaryEntry->PartitionName));
  if (tempStr == NULL)
  {
    status = EFI_OUT_OF_RESOURCES;
    DEBUG((EFI_D_WARN, "ValidatePartitionName: Memory allocation failed.\n"));
    goto ValidatePartitionNameExit;
  }

  if (StrLen(secondaryEntry->PartitionName) > StrLen(primaryEntry->PartitionName))
  {
    backupPartitionName = secondaryEntry->PartitionName;
    primaryPartitionName = primaryEntry->PartitionName;
  }
  else
  {
    backupPartitionName = primaryEntry->PartitionName;
    primaryPartitionName = secondaryEntry->PartitionName;
  }

  StrnCpyS (
    tempStr,
    (sizeof(secondaryEntry->PartitionName) / sizeof (CHAR16)),
    BACKUP_PARTITION_PREFIX,
    (StrLen (BACKUP_PARTITION_PREFIX) + 1)
    );
  StrnCatS (
    tempStr,
    (sizeof(secondaryEntry->PartitionName) / sizeof (CHAR16)),
    primaryPartitionName,
    (StrLen (primaryPartitionName) + 1)
    );

  diff = StriCmp(backupPartitionName, tempStr);
  if (diff)
  {
    status = EFI_INVALID_PARAMETER;
    DEBUG((
      EFI_D_WARN,
      "ValidatePartitionName: primaryPartitionName: %s secondaryPartitionName: %s\n",
      primaryEntry->PartitionName,
      secondaryEntry->PartitionName
      ));
    DEBUG((EFI_D_WARN, "ValidatePartitionName: Invalid <primary,secondary> pairs\n"));
    goto ValidatePartitionNameExit;
  }

ValidatePartitionNameExit:
  if (tempStr != NULL)
  {
    FreePool(tempStr);
    tempStr = NULL;
  }

  return status;
}

EFI_STATUS
ValidatePartitionGuidPairs (
  IN EFI_GUID                 *PrimaryGuid,
  IN EFI_GUID                 *SecondaryGuid
  )
{
  EFI_STATUS               status                   = EFI_SUCCESS;
  EFI_HANDLE               primaryHandle            = NULL;
  EFI_HANDLE               secondaryHandle          = NULL;
  UINTN                    primaryPartitionSize     = 0;
  UINTN                    secondaryPartitionSize   = 0;

  // Input parameter validation
  if ((NULL == PrimaryGuid) ||
      (NULL == SecondaryGuid) ||
      (IsZeroGuid(PrimaryGuid)) ||
      (IsZeroGuid(SecondaryGuid)) ||
      (CompareGuid(PrimaryGuid, SecondaryGuid)))
  {
    DEBUG((EFI_D_ERROR, "ValidatePartitionGuidPairs: Invalid input parameters.\n"));
    status = EFI_INVALID_PARAMETER;
    goto ValidatePartitionGuidPairsExit;
  }

  status = GetRecoveryPartitionHandle (
    PrimaryGuid,
    &primaryHandle,
    &primaryPartitionSize
    );
  HANDLE_ERROR_LABEL(status, GetRecoveryPartitionHandle, ValidatePartitionGuidPairsExit);

  status = GetRecoveryPartitionHandle (
    SecondaryGuid,
    &secondaryHandle,
    &secondaryPartitionSize
    );
  HANDLE_ERROR_LABEL(status, GetRecoveryPartitionHandle, ValidatePartitionGuidPairsExit);

  // Primary/backup partition sizes should match
  if (secondaryPartitionSize != primaryPartitionSize)
  {
    status = EFI_INVALID_PARAMETER;
    DEBUG((
      EFI_D_WARN,
      "ValidatePartitionGuidPairs: primaryPartitionSize = %d secondaryPartitionSize = %d\n",
      primaryPartitionSize,
      secondaryPartitionSize
      ));
    DEBUG((EFI_D_WARN, "ValidatePartitionName: Mismatch in partition sizes\n"));
    goto ValidatePartitionGuidPairsExit;
  }

  // Backup partition name should always contain BACKUP_XXX,
  // where XXX is the primary partition name.
  status = ValidatePartitionName (
    primaryHandle,
    secondaryHandle
    );
  HANDLE_ERROR_LABEL(status, ValidatePartitionName, ValidatePartitionGuidPairsExit);

ValidatePartitionGuidPairsExit:
  return status;
}

EFI_STATUS
RestoreCorruptedPartitions (
  IN EFI_RECOVERY_PROTOCOL       *This
  )
{
  EFI_STATUS               status                 = EFI_SUCCESS;
  PRECOVERY_PRIVATE_DATA   pPrivate               = NULL;
  UINT8                    idx                    = 0;
  EFI_HANDLE               handle                 = NULL;
  VOID                    *buffer                 = NULL;
  UINTN                    bufferSize             = 0;
  VOID                    *readBuffer             = NULL;
  UINTN                    readBufferSize         = 0;
  UINTN                    currentProgressRate    = 0;
  UINT8                    loopCount              = 0;

  // Retrieve the private context structure
  pPrivate = RECOVERY_PRIVATE_DATA_FROM_THIS(This);

  UpdateRecoveryProgress(This, RECOVERY_PROCESS_START);
  UpdateRecoveryTextDisplay(This);

  for (idx = 0; idx < pPrivate->RecoveryItemCount; idx++)
  {
    // Skip partitions pending for capsule update.
    if (pPrivate->RecoveryEntries[idx].RecoveryStatus == RECOVERY_NOT_ATTEMPTED)
    {
      continue;
    }

    DEBUG((
      EFI_D_WARN,
      "RestoreCorruptedPartitions: PrimaryGuid[%d]: %g.SecondaryGuid[%d]: %g\n",
      idx, &pPrivate->RecoveryEntries[idx].PrimaryGuid,
      idx, &pPrivate->RecoveryEntries[idx].SecondaryGuid
      ));

    status = ValidatePartitionGuidPairs (
      &pPrivate->RecoveryEntries[idx].PrimaryGuid,
      &pPrivate->RecoveryEntries[idx].SecondaryGuid
      );
    if (EFI_ERROR(status))
    {
      DEBUG((
        EFI_D_WARN,
        "RestoreCorruptedPartitions: ValidatePartitionGuidPairs failed. Status: %r\n",
        status
        ));
      continue;
    }

    status = GetRecoveryPartitionHandle (
      &pPrivate->RecoveryEntries[idx].SecondaryGuid,
      &handle,
      NULL
      );
    if (EFI_ERROR(status))
    {
      DEBUG((
        EFI_D_WARN,
        "RestoreCorruptedPartitions: GetRecoveryPartitionHandle failed. Status: %r\n",
        status
        ));
      continue;
    }

    for (loopCount = 0; loopCount < MAX_RECOVERY_ATTEMPTS; loopCount++)
    {
      // FwUpdatePartitionRead will allocate memory for buffer and readBuffer. 
      // So, clearing these buffers before start of every iteartion.
      if (buffer != NULL)
      {
        FreePool(buffer);
        buffer = NULL;
      }

      if (readBuffer != NULL)
      {
        FreePool(readBuffer);
        readBuffer = NULL;
      }

      status = FwUpdatePartitionRead (
        handle,
        &buffer,
        &bufferSize
        );
      if (EFI_ERROR(status))
      {
        DEBUG((
          EFI_D_WARN,
          "RestoreCorruptedPartitions: FwUpdatePartitionRead failed. LoopCount: %d, Status: %r\n",
          loopCount,
          status
          ));
        continue;
      }

      status = FwUpdatePartitionWrite (
        pPrivate->RecoveryEntries[idx].PrimaryPartitionHandle,
        buffer,
        bufferSize
        );
      if (EFI_ERROR(status))
      {
        DEBUG((
          EFI_D_WARN,
          "RestoreCorruptedPartitions: FwUpdatePartitionWrite failed. LoopCount: %d, Status: %r\n",
          loopCount,
          status
          ));
        continue;
      }

      status = FwUpdatePartitionRead (
        pPrivate->RecoveryEntries[idx].PrimaryPartitionHandle,
        &readBuffer,
        &readBufferSize
        );
      if (EFI_ERROR(status))
      {
        DEBUG((
          EFI_D_WARN,
          "RestoreCorruptedPartitions: FwUpdatePartitionRead back failed. LoopCount: %d, Status: %r\n",
          loopCount,
          status
          ));
        continue;
      }
      else if (CompareMem (readBuffer,buffer,bufferSize) != 0)
      {
        DEBUG((
          EFI_D_WARN,
          "RestoreCorruptedPartitions: Mismatch in buffer written and buffer read back. LoopCount: %d\n",
          loopCount
          ));
        continue;
      }
      else
      {
        // On success, we will reach this condition.
        break;
      }
    }

    // Continue to process other items in RecoveryList even on failure.
    if (EFI_ERROR(status))
    {
      DEBUG((
        EFI_D_ERROR,
        "RestoreCorruptedPartitions: All retry attempts to recover partition failed. Will continue to process other items."
        ));
      continue;
    }

    // Mark recovery status = COMPLETE on success.
    pPrivate->RecoveryEntries[idx].RecoveryStatus = RECOVERY_COMPLETE;

    currentProgressRate += ((bufferSize*100)/pPrivate->TotalRecoveryPartitionSize);
    UpdateRecoveryProgress(This, currentProgressRate);
  }

  UpdateRecoveryProgress(This, RECOVERY_PROCESS_END);

  return status;
}

BOOLEAN
CheckIfCapsulePending (VOID)
{
  BOOLEAN                isCapsulePending                 = FALSE;
  UINTN                  bufferSize                       = 0;
  BOOLEAN               *isCapsulePendingInPersistedMedia = NULL;
  UINT64                *osIndications                    = NULL;

  isCapsulePendingInPersistedMedia = BdsLibGetVariableAndSize (
    L"IsCapsulePendingInPersistedMedia",
    &gEfiGlobalVariableGuid,
    &bufferSize
    );
  DEBUG((
    EFI_D_INFO,
    "isCapsulePendingInPersistedMedia: %d\n",
    *isCapsulePendingInPersistedMedia
    ));
  if ((isCapsulePendingInPersistedMedia != NULL) &&
      (*isCapsulePendingInPersistedMedia))
  {
    isCapsulePending = TRUE;
    goto CheckIfCapsulePendingExit;
  }
  else
  {
    osIndications = BdsLibGetVariableAndSize (
      L"OsIndications",
      &gEfiGlobalVariableGuid,
      &bufferSize
      );
    DEBUG((EFI_D_INFO, "osIndications: %d\n", *osIndications));
    if ((osIndications != NULL) &&
        (*osIndications & EFI_OS_INDICATIONS_FILE_CAPSULE_DELIVERY_SUPPORTED))
    {
      isCapsulePending = TRUE;
      goto CheckIfCapsulePendingExit;
    }
  }

CheckIfCapsulePendingExit:
  return isCapsulePending;
}

EFI_STATUS
ProcessRecoveryList (
  IN EFI_RECOVERY_PROTOCOL       *This
  )
{
  EFI_STATUS                     status                 = EFI_SUCCESS;
  PRECOVERY_PRIVATE_DATA         pPrivate               = NULL;
  EFI_GUID                      *pCapsulePendingList    = NULL;
  UINTN                          capsulePendingListSize = 0;
  UINTN                          sizeOfRecoveryEntries  = 0;

  // Read capsule pending list
  status = GetPartitionsUnderUpdate (&pCapsulePendingList, &capsulePendingListSize);
  HANDLE_ERROR_LABEL(status, GetPartitionsUnderUpdate, ProcessRecoveryListExit);

  if (capsulePendingListSize != 0)
  {
    DEBUG((
      EFI_D_WARN,
      "ProcessRecoveryList: capsulePendingListSize: %d\n",
      capsulePendingListSize
      ));

    //Clear partitions under update if no pending capsules
    if (CheckIfCapsulePending() == FALSE)
    {
      DEBUG((EFI_D_INFO, "ProcessRecoveryList: Clearing partitions under update\n"));
      status = ClearPartitionsUnderUpdate (pCapsulePendingList, capsulePendingListSize);
      HANDLE_ERROR_LABEL(status, ClearPartitionsUnderUpdate, ProcessRecoveryListExit);
    }
  }

  // Retrieve the private context structure
  pPrivate = RECOVERY_PRIVATE_DATA_FROM_THIS(This);

  status = GetSmemRecoveryItemCount (&pPrivate->RecoveryItemCount);
  HANDLE_ERROR_LABEL(status, GetSmemRecoveryItemCount, ProcessRecoveryListExit);

  // Recovery list is empty
  if (pPrivate->RecoveryItemCount == 0)
  {
    DEBUG((EFI_D_INFO, "ProcessRecoveryList: Recovery list is empty.\n"));
    goto ProcessRecoveryListExit;
  }

  DEBUG((EFI_D_WARN, "ProcessRecoveryList: Recovery count: %d\n", pPrivate->RecoveryItemCount));

  // Allocate memory to store Recovery data entries
  sizeOfRecoveryEntries = (pPrivate->RecoveryItemCount * sizeof(RECOVERY_DATA_ENTRY));
  pPrivate->RecoveryEntries = AllocateZeroPool (sizeOfRecoveryEntries);
  if (pPrivate->RecoveryEntries == NULL)
  {
    status = EFI_OUT_OF_RESOURCES;
    DEBUG((EFI_D_WARN, "ProcessRecoveryList: RecoveryEntries memory allocation failed.\n"));
    goto ProcessRecoveryListExit;
  }

  // Read SMEM to initialize corrupted data entries
  status = GetRecoveryPartitionInfoFromSmem (
    pPrivate->RecoveryEntries,
    &sizeOfRecoveryEntries
    );
  HANDLE_ERROR_LABEL(status, GetRecoveryPartitionInfoFromSmem, ProcessRecoveryListExit);

  status = ValidateRecoveryList(This);
  HANDLE_ERROR_LABEL(status, ValidateRecoveryList, ProcessRecoveryListExit);

  // Initialize recovery status with RECOVERY_FAILED
  status = InitRecoveryStatus (
    This,
    pCapsulePendingList,
    capsulePendingListSize,
    RECOVERY_FAILED
    );
  HANDLE_ERROR_LABEL(status, InitRecoveryStatus, ProcessRecoveryListExit);

  // Checking if partitions pending for capsule update are all marked for recovery.
  if (pPrivate->PartitionsUnderUpdateCount == pPrivate->RecoveryItemCount)
  {
    DEBUG((
      EFI_D_WARN,
      "ProcessRecoveryList: Skipping recovery as all partitions are marked for update.\n"
      ));
    goto ProcessRecoveryListExit;
  }

  // Calculate total size of partitions under recovery
  status = CalculateTotalSizeOfPartitionsUnderRecovery (This);
  HANDLE_ERROR_LABEL(status, CalculateTotalSizeOfPartitionsUnderRecovery, ProcessRecoveryListExit);

  // Restore corrupted partitions
  status = RestoreCorruptedPartitions (This);
  HANDLE_ERROR_LABEL(status, RestoreCorruptedPartitions, ProcessRecoveryListExit);

ProcessRecoveryListExit:
  return status;
}

BOOLEAN
TestRecoveryFailurePath (
  IN EFI_GUID                   *CapsulePendingList,
  IN UINT8                       CapsulePendingListCount
  )
{
  EFI_STATUS              status                     = EFI_SUCCESS;
  EFI_GUID               *pRecoveryFailedNVItem      = NULL;
  UINTN                   recoveryNVSize             = 0;
  BOOLEAN                 recoveryFailed             = FALSE;
  UINT8                   j                          = 0;

  // Changes to verify recovery failure path in capsule update.
  // Reads the NV variable to check if partition is marked for update.
  // If yes, we will mark IsRecoveryFailed = TRUE.
  status = GetVariable2(
    RECOVERY_FAILED_NV,
    &gQcomTokenSpaceGuid,
    (VOID **)&pRecoveryFailedNVItem,
    &recoveryNVSize
    );
  if (EFI_ERROR(status))
  {
    DEBUG((EFI_D_ERROR, "TestRecoveryFailurePath: Fail to get RECOVERY_FAILED_NV.\n"));
    status = EFI_SUCCESS;
  }

  DEBUG((
    EFI_D_INFO,
    "TestRecoveryFailurePath: pRecoveryFailedNVItem : %g.\n",
    pRecoveryFailedNVItem
    ));
  if (pRecoveryFailedNVItem != NULL)
  {
    for (j = 0; j < CapsulePendingListCount; j++)
    {
      if (CompareGuid (pRecoveryFailedNVItem, &CapsulePendingList[j]))
      {
        recoveryFailed = TRUE;
        DEBUG((EFI_D_WARN, "TestRecoveryFailurePath: Setting recoveryFailed = TRUE.\n"));
        break;
      }
    }

    // Clear pRecoveryFailedNVItem configured from test app
    ZeroMem(pRecoveryFailedNVItem, recoveryNVSize);

    status = gRT->SetVariable (
      RECOVERY_FAILED_NV,
      &gQcomTokenSpaceGuid,
      (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS),
      0,
      &pRecoveryFailedNVItem
      );
    if (EFI_ERROR(status))
    {
      DEBUG((EFI_D_ERROR, "TestRecoveryFailurePath: Failed to clear NV variable.\n"));
      status = EFI_SUCCESS;
    }
  }

  return recoveryFailed;
}

// Protocol functions
EFI_STATUS
CheckIfRecoveryFailed (
  IN EFI_RECOVERY_PROTOCOL      *This,
  IN EFI_GUID                   *CapsulePendingList,
  IN UINTN                       CapsulePendingListSize,
  OUT BOOLEAN                   *IsRecoveryFailed
  )
{
  EFI_STATUS                status                     = EFI_SUCCESS;
  UINT8                     capsulePendingListCount    = 0;
  PRECOVERY_PRIVATE_DATA    pPrivate                   = NULL;
  UINT8                     i                          = 0;
  UINT8                     j                          = 0;
  PRECOVERY_DATA_ENTRY      pRecoveryitem              = NULL;

  // Input parameter validation
  if ((NULL == CapsulePendingList) ||
      (NULL == IsRecoveryFailed))
  {
    DEBUG((EFI_D_ERROR, "CheckIfRecoveryFailed: Invalid input parameters.\n"));
    status = EFI_INVALID_PARAMETER;
    goto CheckIfRecoveryFailedExit;
  }

  // Retrieve the private context structure
  pPrivate = RECOVERY_PRIVATE_DATA_FROM_THIS(This);

  capsulePendingListCount = (CapsulePendingListSize/sizeof(EFI_GUID));

#if !defined(PRODMODE)
  *IsRecoveryFailed = TestRecoveryFailurePath(CapsulePendingList, capsulePendingListCount);
  if (*IsRecoveryFailed)
  {
    goto CheckIfRecoveryFailedExit;
  }
#endif // end of !defined(PRODMODE)

  if ((pPrivate->RecoveryItemCount != 0) && (pPrivate->RecoveryEntries == NULL))
  {
    DEBUG((EFI_D_ERROR, "CheckIfRecoveryFailed: RecoveryEntries = NULL.\n"));
    // Here, device error indicates that recovery entries are not filled in 
    // to validate the recovery status.
    status = EFI_DEVICE_ERROR;
    goto CheckIfRecoveryFailedExit;
  }

  for (i = 0; i < pPrivate->RecoveryItemCount; i++)
  {
    pRecoveryitem = &pPrivate->RecoveryEntries[i];
    DEBUG((
      EFI_D_WARN,
      "CheckIfRecoveryFailed: Partition GUID: %g\n\n",
      &pRecoveryitem->PrimaryGuid
      ));
    for (j = 0; j < capsulePendingListCount; j++)
    {
      if ((CompareGuid (&pRecoveryitem->PrimaryGuid, &CapsulePendingList[j])) ||
          (CompareGuid (&pRecoveryitem->SecondaryGuid, &CapsulePendingList[j])))
      {
        DEBUG((
          EFI_D_WARN,
          "CheckIfRecoveryFailed: Partition GUID: %g RecoveryStatus: %s\n\n",
          &CapsulePendingList[j],
          RecoveryStatusStr[pRecoveryitem->RecoveryStatus]
          ));

        // Mark IsRecoveryFailed=TRUE if recovery failed for a partition.
        if (pRecoveryitem->RecoveryStatus == RECOVERY_FAILED)
        {
          *IsRecoveryFailed = TRUE;
          goto CheckIfRecoveryFailedExit;
        }
        break;
      }
    }
  }

  *IsRecoveryFailed = FALSE;

CheckIfRecoveryFailedExit:
  return status;
}

EFI_STATUS
SetPartitionsUnderUpdate (
  IN EFI_GUID                  *CapsulePendingList,
  IN UINTN                      CapsulePendingListSize
  )
{
  EFI_STATUS                status                     = EFI_SUCCESS;

  status = SetCapsulePendingList (
    QCOM_FW_UPDATE_NV_PARTITIONS_UNDER_UPDATE,
    CapsulePendingList,
    CapsulePendingListSize
    );
  HANDLE_ERROR_LABEL(status, SetCapsulePendingList, SetPartitionsUnderUpdateExit);

SetPartitionsUnderUpdateExit:
  return status;
}

/**
  Template for EFI_RECOVERY Private Data structure.
**/

RECOVERY_PRIVATE_DATA mRecoveryPrivateDataTemplate = {
  RECOVERY_PRIVATE_DATA_SIGNATURE,        //Signature
  {                                       //Recovery Protocol
    EFI_RECOVERY_PROTOCOL_REVISION,
    CheckIfRecoveryFailed,
    SetPartitionsUnderUpdate,
    ClearPartitionsUnderUpdate
  },
  {                                       //Recovery Progressbar protocol
    0x00000001,
    {0},                                  //default foreground colour
    0                                     //default watchdog timeout
  },
  NULL,                                   //default progress text
  0,                                      //default progress text foregorund colour
  NULL,                                   //RecoveryEvent
  0,                                      //RecoveryItemCount
  0,                                      //PartitionsUnderUpdateCount
  0,                                      //TotalRecoveryPartitionSize
  NULL                                    //RecoveryDataEntries
};

/**
  Notification function that gets invoked when gEfiRecoveryEventGuid is signaled.

  @param[in]  Event    Event whose notification function is being invoked.
  @param[in]  Context  Pointer to the notification function's context,
                       which is implementation-dependent.

  @retval  EFI_SUCCESS            Processed recovery list successfully.
  @retval  EFI_INVALID_PARAMETER  Notification function's context is NULL.
  @retval  EFI_XXXX               Other errors.

**/
VOID
ProcessRecoveryEventNotify (
  IN EFI_EVENT      Event,
  IN VOID          *Context
  )
{
  EFI_STATUS                status         = EFI_SUCCESS;
  PRECOVERY_PRIVATE_DATA    pPrivate       = NULL;

  if (Context == NULL)
  {
    DEBUG((EFI_D_ERROR, "ProcessRecoveryEventNotify: Context = NULL.\n"));
    status = EFI_INVALID_PARAMETER;
  }
  ASSERT_EFI_ERROR(status);

  pPrivate = (PRECOVERY_PRIVATE_DATA)Context;

  status = ProcessRecoveryList (&pPrivate->Recovery);
  if (EFI_ERROR(status))
  {
    DEBUG((
      EFI_D_ERROR,
      "ProcessRecoveryEventNotify: ProcessRecoveryList failed. Status: %r\n",
      status));
    goto ProcessRecoveryEventNotifyExit;
  }

ProcessRecoveryEventNotifyExit:
  if ((pPrivate != NULL) && (pPrivate->RecoveryEvent != NULL))
  {
    gBS->CloseEvent (pPrivate->RecoveryEvent);
    pPrivate->RecoveryEvent = NULL;
  }
}

/**
  Function to install Recovery instance.

  @param[in]  Handle  The device handle to install a Recovery instance.

  @retval  EFI_SUCCESS            Recovery instance installed.
  @retval  EFI_OUT_OF_RESOURCES   Not enough resources to allocate memory.
  @retval  EFI_XXXX               Other errors.

**/
EFI_STATUS
InstallRecoveryInstance (
  IN EFI_HANDLE  Handle
  )
{
  EFI_STATUS                status            = EFI_SUCCESS;
  PRECOVERY_PRIVATE_DATA    pPrivate          = NULL;

  // Allocate Recovery Protocol instance
  pPrivate = AllocateCopyPool (
    sizeof (mRecoveryPrivateDataTemplate),
    &mRecoveryPrivateDataTemplate
    );
  if (pPrivate == NULL)
  {
    DEBUG ((
      EFI_D_ERROR,
      "InstallRecoveryInstance: Private data memory allocation failed.\n"
      ));
    status = EFI_OUT_OF_RESOURCES;
    goto InstallRecoveryInstanceExit;
  }

  status = gBS->CreateEventEx (
    EVT_NOTIFY_SIGNAL,
    TPL_CALLBACK,
    ProcessRecoveryEventNotify,
    pPrivate,
    &gEfiRecoveryEventGuid,
    &pPrivate->RecoveryEvent
    );
  if (EFI_ERROR (status))
  {
    DEBUG ((
      EFI_D_ERROR,
      "InstallRecoveryInstance: Failed to register notification.  Status = %r.\n",
      status
      ));
    goto InstallRecoveryInstanceExit;
  }

  // Fill in Recovery Progress Protocol fields for Version 1
  pPrivate->RecoveryProgress.Version                        = 1;
  pPrivate->RecoveryProgress.ProgressBarForegroundColor.Raw = PcdGet32(PcdRecoveryDxeProgressColor);
  pPrivate->RecoveryProgress.WatchdogSeconds                = PcdGet8(PcdRecoveryDxeWatchdogTimeInSeconds);

  // Fill in Recovery Text display variables
  pPrivate->RecoveryTextColour = PcdGet32(PcdRecoveryDxeForeGroundTextColor);
  pPrivate->RecoveryProgressString = (CHAR16*)PcdGetPtr(PcdRecoveryDxeProgressString);

  // Install Recovery Protocol
  status = gBS->InstallMultipleProtocolInterfaces (
    &Handle,
    &gEfiRecoveryProtocolGuid,
    &pPrivate->Recovery,
    &gEdkiiFirmwareManagementProgressProtocolGuid,
    &pPrivate->RecoveryProgress,
    NULL
    );

  if (EFI_ERROR (status))
  {
    DEBUG ((
      EFI_D_ERROR,
      "InstallRecoveryInstance: Protocol install error. Status = %r.\n",
      status
      ));
    goto InstallRecoveryInstanceExit;
  }

InstallRecoveryInstanceExit:
  return status;
}

/**
  Initializes EFI_RECOVERY protocol

  @param[in]  ImageHandle  Firmware allocated handle for the EFI image.
  @param[in]  SystemTable  Pointer to the EFI System Table.

  @retval  EFI_SUCCESS    Recovery protocol initialized successfully.
  @retval  EFI_XXXXXX     Failure occured.

**/
EFI_STATUS
RecoveryDxeEntryPoint (
  IN EFI_HANDLE          ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS   status = EFI_SUCCESS;

  status = InstallRecoveryInstance (ImageHandle);
  if (EFI_ERROR(status))
  {
    DEBUG((
      EFI_D_WARN,
      "RecoveryDxeEntryPoint: InstallRecoveryInstance failed.\r\n"
      ));
    goto RecoveryDxeEntryPointExit;
  }

RecoveryDxeEntryPointExit:
  return status;
}
