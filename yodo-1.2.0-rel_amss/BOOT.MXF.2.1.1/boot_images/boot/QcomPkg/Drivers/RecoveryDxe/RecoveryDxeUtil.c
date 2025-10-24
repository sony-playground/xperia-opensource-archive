/** @file RecoveryDxeUtil.c
   
  Recovery SMEM utility functions.

  Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when           who         what, where, why
 --------       ---         --------------------------------------------------
 2021/03/16     dmohan      Initial version
=============================================================================*/

#include <Library/BaseMemoryLib.h>
#include "smem.h"
#include "boot_recovery_partition.h"
#include "RecoveryDxe.h"

EFI_STATUS
GetSmemRecoveryItemCount (
  OUT UINT8                   *Count
  )
{
  EFI_STATUS                     status            = EFI_SUCCESS;
  smem_recovery_partitions_info *pSmemRecoveryInfo = NULL;
  UINT32                         buf_size          = 0;

  pSmemRecoveryInfo = (smem_recovery_partitions_info *)smem_get_addr(
    RECOVERY_PARTITION_SMEM_ID,
    &buf_size
    );
  if(pSmemRecoveryInfo == NULL)
  {
    DEBUG((EFI_D_ERROR, "SMEM Recovery buffer in NULL "));
    status = EFI_NOT_READY;
    goto GetSmemRecoveryItemCountExit;
  }

  *Count = pSmemRecoveryInfo->num_of_entries;

GetSmemRecoveryItemCountExit:
  return status;
}

EFI_STATUS
GetRecoveryPartitionInfoFromSmem(
  OUT void                   *PartitionInfo,
  IN OUT UINTN               *PartitionInfoSize
  )
{
  EFI_STATUS                     status                = EFI_SUCCESS;
  smem_recovery_partitions_info *pSmemRecoveryInfo     = NULL;
  UINT32                         buf_size              = 0;
  UINT8                          idx                   = 0;
  UINTN                          sizeOfRecoveryEntries = 0;

  pSmemRecoveryInfo = (smem_recovery_partitions_info *)smem_get_addr(
    RECOVERY_PARTITION_SMEM_ID,
    &buf_size
    );
  if (pSmemRecoveryInfo == NULL)
  {
    DEBUG((EFI_D_ERROR, "SMEM Recovery buffer in NULL "));
    status = EFI_NOT_READY;
    goto GetRecoveryPartitionInfoFromSmemExit;
  }

  DEBUG((EFI_D_INFO, "magic_cookie: 0x%x  max_entries: %d version: %d num_of_entries: %d\n",
    pSmemRecoveryInfo->magic_cookie,
    pSmemRecoveryInfo->max_entries,
    pSmemRecoveryInfo->version,
    pSmemRecoveryInfo->num_of_entries
    ));

  sizeOfRecoveryEntries = (pSmemRecoveryInfo->num_of_entries * sizeof(RECOVERY_DATA_ENTRY));

  if (*PartitionInfoSize < sizeOfRecoveryEntries)
  {
    status = EFI_BUFFER_TOO_SMALL;
    *PartitionInfoSize = sizeOfRecoveryEntries;
    goto GetRecoveryPartitionInfoFromSmemExit;
  }

  PRECOVERY_DATA_ENTRY pRecoveryEntries = (PRECOVERY_DATA_ENTRY)PartitionInfo;

  for (idx = 0; idx < pSmemRecoveryInfo->num_of_entries; idx++)
  {
    DEBUG((
      EFI_D_INFO, "corrupted_partition_id[%d]: %g  recovery_partition_id[%d]: %g\n",
      idx, &pSmemRecoveryInfo->partition_info[idx].corrupted_partition_id,
      idx, &pSmemRecoveryInfo->partition_info[idx].recovery_partition_id
      ));

    CopyMem(
      &pRecoveryEntries[idx].PrimaryGuid,
      &pSmemRecoveryInfo->partition_info[idx].corrupted_partition_id,
      sizeof(EFI_GUID)
      );

    CopyMem(
      &pRecoveryEntries[idx].SecondaryGuid,
      &pSmemRecoveryInfo->partition_info[idx].recovery_partition_id,
      sizeof(EFI_GUID)
      );

    DEBUG((
      EFI_D_INFO, "PrimaryGuid[%d]: %g  SecondaryGuid[%d]: %g\n",
      idx, &pRecoveryEntries[idx].PrimaryGuid,
      idx, &pRecoveryEntries[idx].SecondaryGuid
      ));
  }

GetRecoveryPartitionInfoFromSmemExit:
  return status;
}
