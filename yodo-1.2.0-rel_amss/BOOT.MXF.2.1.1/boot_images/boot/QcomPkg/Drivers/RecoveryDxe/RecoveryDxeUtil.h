/** @file RecoveryDxeUtil.c
   
  Header for RecoveryDxeUtil.c

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

#ifndef _RECOVERYDXEUTIL_H_
#define _RECOVERYDXEUTIL_H_

/**
  Get number of entries in SMEM recovery list.

  @param[out]  Count      Number of entries in SMEM recovery list

  @retval  EFI_SUCCESS    Read SMEM ID to fetch number of entries in recovery list.
  @retval  EFI_NOT_READY  SMEM ID not initialized.
  @retval  EFI_XXXX       Other errors.

**/
EFI_STATUS
GetSmemRecoveryItemCount (
  OUT UINT8                   *Count
  );

/**
  Get Recovery partition info from SMEM and store it in RECOVERY_PRIVATE_DATA structure.

  @param[out]      PartitionInfo         Pointer to recovery data entries.
  @param[in, out]  PartitionInfoSize     On input, holds the size of PartitionInfo.
                                         If buffer is too small, returns the 
                                         size of PartitionInfo as output.

  @retval  EFI_SUCCESS             Successfully copied recovery partition info
                                   from SMEM to RECOVERY_PRIVATE_DATA structure.
  @retval  EFI_NOT_READY           SMEM ID not initialized.
  @retval  EFI_BUFFER_TOO_SMALL    Input buffer too small.
  @retval  EFI_XXXX                Other errors.

**/
EFI_STATUS
GetRecoveryPartitionInfoFromSmem (
  OUT void                   *PartitionInfo,
  IN OUT UINTN               *PartitionInfoSize
  );

#endif // #ifndef _RECOVERYDXEUTIL_H_

