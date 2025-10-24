/**
  @file EFIEraseBlock.h
  @brief Erase Block Protocol definitions
*/
/*=============================================================================
  Copyright (c) 2012-2016 Qualcomm Technologies, Inc.
  All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when        who     what, where, why
 --------    ---     -----------------------------------------------------------
 2/22/16     rh      Adapt for Erase Block protocol
 10/19/12    llg     (Tech Pubs) Edited/added Doxygen comments and markup.
 10/04/12    sb      Initial version.
 
=============================================================================*/
#ifndef __EFI_ERASE_BLOCK_H__
#define __EFI_ERASE_BLOCK_H__

#include <Protocol/BlockIo.h>

/** @cond */
typedef struct _EFI_ERASE_BLOCK_PROTOCOL   EFI_ERASE_BLOCK_PROTOCOL;
/** @endcond */

/** @ingroup efi_EraseBlock_constants
  Protocol version.
*/
#define EFI_ERASE_BLOCK_PROTOCOL_REVISION      ((2<<16) | (60))

/* Protocol GUID definition */

/** @defgroup efi_erase_block_protocol EFI_ERASE_BLOCK_PROTOCOL
 *  @ingroup PERIPHERALS 
 */
 
  /** @defgroup  efi_erase_block_protocol_prot PROTOCOL
 *  @ingroup efi_erase_block_protocol 
 */ 
 /** @defgroup  efi_erase_block_protocol_apis APIs
 *  @ingroup efi_erase_block_protocol 
 */ 

/** @defgroup  efi_erase_block_protocol_data DATA_STRUCTURES
 *  @ingroup efi_erase_block_protocol 
 */
/** @ingroup efi_emmc_secure_erase_protocol_data */
#define EFI_ERASE_BLOCK_PROTOCOL_GUID \
	{0x95A9A93E, 0xA86E, 0x4926, {0xaa, 0xef, 0x99, 0x18, 0xe7, 0x72, 0xd9, 0x87}}
/**@ingroup EFI_ERASE_BLOCK_TOKEN
@ingroup efi_erase_block_protocol_data
**/
typedef struct {
	EFI_EVENT Event;
	EFI_STATUS TransactionStatus;
} EFI_ERASE_BLOCK_TOKEN; 

/* External reference to the Emmc Erase Protocol GUID */
/** @cond */
extern EFI_GUID gEfiEraseBlockProtocolGuid;
/** @endcond */


/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/

/* EFI_ERASE_BLOCKS */ 
/** @ingroup efi_erase_block_protocol_apis
  @par Summary
  Performs the erase operation on the specified sectors. 

  @param[in] This         Indicates a pointer to the calling context. 
  								  Type is defined in the EFI_ERASE_BLOCK_PROTOCOL 
								  description
  @param[in] MediaId      The media ID that the erase request is for
  @param[in] LBA          Start LBA for the erase operation
  @param[in] Token        A pointer to the token associated with the transaction
  @param[in] Size         The size in bytes to be erased. This must be a multiple 
                          of the physical block size of the device

  @par Description
  This function erases the blocks specified by the LBA and 
  Size parameters.  If the parameters are valid, this 
  function sends the commands to the storage device to apply the erase operation 
  on the specified blocks.
  
  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- Parameter is invalid, including an invalid
                           alignment of the start and count values. \n
  EFI_WRITE_PROTECTED   -- Device cannot be erased due to write protection. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_ERASE) (
	IN EFI_BLOCK_IO_PROTOCOL *This,
	IN UINT32 MediaId,
	IN EFI_LBA LBA,
	IN OUT EFI_ERASE_BLOCK_TOKEN *Token,
	IN UINTN Size
); 

#ifdef FEATURE_XBOOT
/* EFI_BLOCK_NON_SECURE_ERASE */
/**@ingroup efi_non_secure_erase_Block_block_erase_secure_non
  @par Summary
  Performs the erase operation on the specified sectors.

  @param[in] This         Indicates a pointer to the calling context.
                          Type is defined in the EFI_ERASE_BLOCK_PROTOCOL
                          description
  @param[in] MediaId      The media ID that the erase request is for
  @param[in] LBA          Start LBA for the erase operation
  @param[in] Size         The size in bytes to be erased. This must be a multiple
                          of the physical block size of the device

  @par Description
  This function erases the blocks specified by the LBA and
  Size parameters.  If the parameters are valid, this
  function sends the commands to the storage device to apply the erase operation
  on the specified blocks.

  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- Parameter is invalid, including an invalid
                           alignment of the start and count values. \n
  EFI_WRITE_PROTECTED   -- Device cannot be erased due to write protection. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_NON_SECURE_ERASE) (
	IN EFI_BLOCK_IO_PROTOCOL *This,
	IN UINT32 MediaId,
	IN EFI_LBA LBA,
	IN UINTN Size
);

/* EFI_PURGE_BLOCKS */
/**@ingroup efi_Purge_Block_block_purge
  @par Summary
  Performs the purge operation on the specified sectors.

  @param[in] This         Indicates a pointer to the calling context.
                          Type is defined in the EFI_ERASE_BLOCK_PROTOCOL
                          description
  @param[in] Token        A pointer to the token associated with the transaction

  @par Description
  This function purge the blocks specified by the LBA and
  Size parameters.  If the parameters are valid, this
  function sends the commands to the storage device to apply the purge operation
  on the specified blocks.

  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- Parameter is invalid, including an invalid
                           alignment of the start and count values. \n
  EFI_WRITE_PROTECTED   -- Device cannot be erased due to write protection. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_PURGE) (
	IN EFI_BLOCK_IO_PROTOCOL *This,
	IN OUT EFI_ERASE_BLOCK_TOKEN *Token
);
#endif /* FEATURE_XBOOT */

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_erase_block_protocol_prot
  @par Summary
  Erase Block Protocol interface.

  @par Parameters
  @inputprotoparams{erase_block_proto_params.tex} 
*/
struct _EFI_ERASE_BLOCK_PROTOCOL {
		UINT64 Revision;
		UINT32 EraseLengthGranularity; 
		EFI_BLOCK_ERASE EraseBlocks; 
#ifdef FEATURE_XBOOT
		EFI_BLOCK_NON_SECURE_ERASE NonSecureEraseBlocks;
		EFI_BLOCK_PURGE PurgeBlocks;
#endif /* FEATURE_XBOOT */
};


#endif	/* __EFI_ERASE_BLOCK_H__ */
