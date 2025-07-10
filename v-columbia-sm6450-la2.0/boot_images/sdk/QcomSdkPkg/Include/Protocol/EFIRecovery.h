/**
@file  EFIRecovery.h
@brief UEFI Recovery Protocol definitions.
*/
/*=============================================================================
Copyright (c) 2021 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
02/13/21   dm      Initial revision

=============================================================================*/
#ifndef __EFI_RECOVERY_H_
#define __EFI_RECOVERY_H_

/*===========================================================================
MACRO DECLARATIONS
===========================================================================*/
/* Protocol version. */
#define EFI_RECOVERY_PROTOCOL_REVISION 0x00010000

/* Protocol GUID definition */
#define EFI_RECOVERY_PROTOCOL_GUID \
        { 0xe485f989, 0x9cd4, 0x47b9, {0x8f, 0x19, 0x8e, 0xb8, 0xba, 0x1f, 0xd4, 0xdf } };

#define RECOVERY_FAILED_NV                   L"RECOVERY_FAILED_GUID"

/*===========================================================================
EXTERNAL VARIABLES
===========================================================================*/
/* External reference to the Recovery Protocol GUID. */
extern EFI_GUID gEfiRecoveryProtocolGuid;

/*===========================================================================
TYPE DEFINITIONS
===========================================================================*/
/* Recovery status enum type */
typedef enum {
    RECOVERY_UNKNOWN,
    RECOVERY_NOT_ATTEMPTED,
    RECOVERY_FAILED,
    RECOVERY_COMPLETE,
}RECOVERY_STATUS_TYPE;

/* Protocol declaration */
typedef struct _EFI_RECOVERY_PROTOCOL EFI_RECOVERY_PROTOCOL;


/*===========================================================================
FUNCTION DEFINITIONS
===========================================================================*/
/* EFI_RECOVERY_CHECK_IF_RECOVERY_FAILED */
/** @ingroup efi_recovery_check_if_recovery_failed
@par Summary
Check recovery status of partitions under update for any failure.

@param[in]  This                    Pointer to EFI_RECOVERY_PROTOCOL
@param[in]  CapsulePendingList      List of partition guids pending for update
@param[in]  CapsulePendingListSize  Size of CapsulePendingList
@param[out] IsRecoveryFailed        TRUE if recovery failed
                                    and FALSE otherwise.

@par Description
Function that verifies if recovery failed for any partitions under update.

@return
EFI_SUCCESS           -- Function completed successfully.
EFI_INVALID_PARAMETER -- Invalid arguments.
EFI_DEVICE_ERROR      -- Recovery entries not filled-in to validate the
                         recovery status.
EFI_XXXX              -- Other errors.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_RECOVERY_CHECK_IF_RECOVERY_FAILED)(
  IN EFI_RECOVERY_PROTOCOL      *This,
  IN EFI_GUID                   *CapsulePendingList,
  IN UINTN                       CapsulePendingListSize,
  OUT BOOLEAN                   *IsRecoveryFailed
  );

/* EFI_SET_PARTITIONS_UNDER_UPDATE */
/** @ingroup efi_set_partitions_under_update
@par Summary
Set partitions pending for capsule update.

@param[in]  CapsulePendingList      List of partition guids pending for update
@param[in]  CapsulePendingListSize  Size of CapsulePendingList

@par Description
Function that registers partitions pending for capsule update.

@return
EFI_SUCCESS           -- Function completed successfully.
EFI_INVALID_PARAMETER -- Invalid arguments.
EFI_XXXX              -- Other errors.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_SET_PARTITIONS_UNDER_UPDATE)(
  IN EFI_GUID              *CapsulePendingList,
  IN UINTN                  CapsulePendingListSize
  );

/* EFI_CLEAR_PARTITIONS_UNDER_UPDATE */
/** @ingroup efi_CLEAR_partitions_under_update
@par Summary
  Clears list of partitions pending for capsule update.

  @param[in]  CapsulePendingList      List of partition guids pending for update
  @param[in]  CapsulePendingListSize  Size of CapsulePendingList

  @par Description
  Function that clears partitions pending for capsule update.

  @return
  EFI_SUCCESS           -- Clears CapsulePendingList in NVRAM.
  EFI_INVALID_PARAMETER -- Invalid arguments.
  EFI_XXXX              -- Other errors
*/
typedef
EFI_STATUS
(EFIAPI *EFI_CLEAR_PARTITIONS_UNDER_UPDATE)(
  IN EFI_GUID                  *CapsulePendingList,
  IN UINTN                      CapsulePendingListSize
  );

/*===========================================================================
PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup EFI_RECOVERY_PROTOCOL
@par Summary
EFI_RECOVERY_PROTOCOL interface.
*/
struct _EFI_RECOVERY_PROTOCOL {
  UINT64                                      Revision;
  EFI_RECOVERY_CHECK_IF_RECOVERY_FAILED       CheckIfRecoveryFailed;
  EFI_SET_PARTITIONS_UNDER_UPDATE             SetPartitionsUnderUpdate;
  EFI_CLEAR_PARTITIONS_UNDER_UPDATE           ClearPartitionsUnderUpdate;
};

#endif  /* __EFI_RECOVERY_H_ */

