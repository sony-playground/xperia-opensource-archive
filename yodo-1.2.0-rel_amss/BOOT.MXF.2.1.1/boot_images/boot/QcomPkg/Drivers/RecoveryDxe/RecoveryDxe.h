/**
@file  RecoveryDxe.h
@brief Qualcomm UEFI Recovery protocol declarations.
*/
/*=============================================================================
Copyright (c) 2021 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when           who         what, where, why
--------       ---         --------------------------------------------------
2021/03/15     dmohan      Initial revision
=============================================================================*/
#ifndef _RECOVERY_H_
#define _RECOVERY_H_

#include <Protocol/EFIRecovery.h>
#include <Protocol/FirmwareManagementProgress.h>

#define RECOVERY_PRIVATE_DATA_SIGNATURE SIGNATURE_32 ('r','e','c','v')

#define RECOVERY_PRIVATE_DATA_FROM_THIS(this) \
  CR (this, RECOVERY_PRIVATE_DATA, Recovery, RECOVERY_PRIVATE_DATA_SIGNATURE)

// Recovery Progress bar values
#define RECOVERY_PROCESS_START               01
#define RECOVERY_PROCESS_END                 100
#define MAX_RECOVERY_ATTEMPTS                2

typedef struct _RECOVERY_DATA_ENTRY
{
  EFI_GUID                         PrimaryGuid;
  EFI_GUID                         SecondaryGuid;
  RECOVERY_STATUS_TYPE             RecoveryStatus;
  EFI_HANDLE                       PrimaryPartitionHandle;
}RECOVERY_DATA_ENTRY, *PRECOVERY_DATA_ENTRY;

typedef struct _RECOVERY_PRIVATE_DATA{
  UINTN                                         Signature;
  EFI_RECOVERY_PROTOCOL                         Recovery;
  EDKII_FIRMWARE_MANAGEMENT_PROGRESS_PROTOCOL   RecoveryProgress;
  CHAR16*                                       RecoveryProgressString;
  UINT32                                        RecoveryTextColour;
  EFI_EVENT                                     RecoveryEvent;
  UINT8                                         RecoveryItemCount;
  UINT8                                         PartitionsUnderUpdateCount;
  UINTN                                         TotalRecoveryPartitionSize;
  PRECOVERY_DATA_ENTRY                          RecoveryEntries;
}RECOVERY_PRIVATE_DATA, *PRECOVERY_PRIVATE_DATA;

/**
  Get list of partitions pending for capsule update.

  @param[out]  CapsulePendingList      List of partition guids pending for update
  @param[out]  CapsulePendingListSize  Size of CapsulePendingList

  @retval  EFI_SUCCESS              Read CapsulePendingList from NVRAM successfully.
  @retval  EFI_INVALID_PARAMETER    Invalid arguments.
  @retval  EFI_NOT_FOUND            Empty CapsulePendingList.
  @retval  EFI_XXXX                 Other errors.

**/
EFI_STATUS
GetPartitionsUnderUpdate (
  OUT EFI_GUID                 **CapsulePendingList,
  OUT UINTN                     *CapsulePendingListSize
  );

/**
  Initializes Recovery status for partitions under update to NOT_ATTEMPTED and
  rest of the partitions to default value specified by DefaultRecoveryStatus parameter.

  @param[in]  This                    Pointer to EFI_RECOVERY_PROTOCOL.
  @param[in]  CapsulePendingList      List of partition guids pending for update
  @param[in]  CapsulePendingListSize  Size of CapsulePendingList
  @param[in]  DefaultRecoveryStatus   Recovery status that need to be set for
                                      partitions not marked for capsule update.

  @retval  EFI_SUCCESS              Initialized Recovery status for corrupted partition list
                                    to appropriate values.
  @retval  EFI_INVALID_PARAMETER    Invalid arguments.

**/
EFI_STATUS
InitRecoveryStatus (
  IN EFI_RECOVERY_PROTOCOL       *This,
  IN EFI_GUID                    *CapsulePendingList,
  IN UINTN                        CapsulePendingListSize,
  IN RECOVERY_STATUS_TYPE         DefaultRecoveryStatus
  );

/**
  Get partition handle for items in recovery list.

  @param[in]   PartGuid     Pointer to partition GUID.
  @param[out]  PartHandle   Return partition handle.
  @param[out]  PartSize     Size of partition (optional).

  @retval  EFI_SUCCESS            Found a unique partition handle for a given partition GUID.
  @retval  EFI_INVALID_PARAMETER  Invalid arguments.
  @retval  EFI_NOT_FOUND          Matching partition handle not found.
  @retval  EFI_UNSUPPORTED        More than one matching handle found for a given partition GUID.
  @retval  EFI_XXXX               Other errors

**/
EFI_STATUS
GetRecoveryPartitionHandle (
  IN EFI_GUID                 *PartGuid,
  OUT EFI_HANDLE              *PartHandle,
  OUT UINTN                   *PartSize      OPTIONAL
  );

/**
  Calculate total size of partitions marked for recovery.

  @param[in]  This                Pointer to EFI_RECOVERY_PROTOCOL.

  @retval  EFI_SUCCESS            Retrieved total size of partitions under recovery successfully.
  @retval  EFI_XXXX               Other errors.

**/
EFI_STATUS
CalculateTotalSizeOfPartitionsUnderRecovery (
  IN EFI_RECOVERY_PROTOCOL       *This
  );

/**
  Function to indicate the current recovery progress.

  @param[in]  This        Pointer to EFI_RECOVERY_PROTOCOL.
  @param[in]  Completion  Value between 1 and 100 indicating the recovery progress.

  @retval  EFI_SUCESS             Recovery progress bar updated successfully.
  @retval  EFI_INVALID_PARAMETER  Completion is greater than 100%.
**/
EFI_STATUS
UpdateRecoveryProgress (
  IN EFI_RECOVERY_PROTOCOL       *This,
  IN UINTN                        Completion
  );

/**
  Function to indicate recovery is in progress using text display.

  @param[in]  This        Pointer to EFI_RECOVERY_PROTOCOL.

  @retval  EFI_SUCESS      Recovery text display updated successfully.
  @retval  EFI_XXXX        Other errors.
**/
EFI_STATUS
UpdateRecoveryTextDisplay (
  IN EFI_RECOVERY_PROTOCOL       *This
  );

/**
  Validate entries in recovery list.

  @param[in]  This        Pointer to EFI_RECOVERY_PROTOCOL.

  @retval  EFI_SUCCESS    All entries are valid.
  @retval  EFI_XXXX       Other errors.

**/
EFI_STATUS
ValidateRecoveryList (
  IN EFI_RECOVERY_PROTOCOL       *This
  );

/**
  Get GPT partition entry for a partition handle.

  @param[in]   Handle        Pointer to partition handle.
  @param[out]  PartEntry     Pointer to Gpt partition entry.

  @retval  EFI_SUCCESS    All entries are valid.
  @retval  EFI_XXXX       Other errors.

**/
EFI_STATUS
GetPartitionEntry (
  IN EFI_HANDLE                 Handle,
  OUT EFI_PARTITION_ENTRY     **PartEntry
  );

/**
  Validate if primary and secondary partition names are appropriate.
  Eg: primary partition name -> XXX, backup partition name -> backup_XXX

  @param[in]   PrimaryHandle        Pointer to primary partition handle.
  @param[in]   SecondaryHandle      Pointer to secondary partition handle.

  @retval  EFI_SUCCESS              Validation for partition names passed.
  @retval  EFI_INVALID_PARAMETER    Invalid arguments.
  @retval  EFI_XXXX                 Other errors.

**/
EFI_STATUS
ValidatePartitionName (
  IN EFI_HANDLE                 PrimaryHandle,
  IN EFI_HANDLE                 SecondaryHandle
  );

/**
  Validate if primary and secondary partition guids exist and their sizes match.

  @param[in]   PrimaryGuid        Pointer to primary partition guid.
  @param[in]   SecondaryGuid      Pointer to secondary partition guid.

  @retval  EFI_SUCCESS              Validation for partition guids passed.
  @retval  EFI_INVALID_PARAMETER    Invalid arguments.
  @retval  EFI_XXXX                 Other errors.

**/
EFI_STATUS
ValidatePartitionGuidPairs (
  IN EFI_GUID                 *PrimaryGuid,
  IN EFI_GUID                 *SecondaryGuid
  );

/**
  Function to restore corrupted partitions in recovery list.

  @param[in]  This        Pointer to EFI_RECOVERY_PROTOCOL.

  @retval  EFI_SUCCESS    Successfuly restored corrupted partition with
                          good partition content.
  @retval  EFI_XXXX       Other errors.

**/
EFI_STATUS
RestoreCorruptedPartitions (
  IN EFI_RECOVERY_PROTOCOL       *This
  );

/**
  Function to check if there are any pending capsules.

  @retval  TRUE    Capsule pending.
  @retval  FALSE   No pending capsules.

**/
BOOLEAN
CheckIfCapsulePending (VOID);

/**
  Function that processes the recovery list when 
  recovery event notification function is invoked.

  @param[in]  This        Pointer to EFI_RECOVERY_PROTOCOL.

  @retval  EFI_SUCCESS            Sucessfully processed all items in recovery list.
  @retval  EFI_OUT_OF_RESOURCES   Not enough resources to allocate memory.
  @retval  EFI_XXXX               Other errors.

**/
EFI_STATUS
ProcessRecoveryList (
  IN EFI_RECOVERY_PROTOCOL       *This
  );

#endif // #ifndef _RECOVERY_H_
