/** @file EFINandIo.h
	@brief Nand IO Driver EFI Protocol.
*/
/*=============================================================================
  Copyright (c) 2017,2020, 2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when        who     what, where, why
 --------    ---    -----------------------------------------------------------
 01/08/22    eo     Porting Nand support to XBL Core(Kuno)
 06/09/20    eo     Porting Nand support to XBL Core
 03/03/17    eo     Initial version
=============================================================================*/


#ifndef __NAND_IO_PROTOCOL_H__
#define __NAND_IO_PROTOCOL_H__

#include "nand_api.h"

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @cond */
typedef struct _EFI_NAND_IO_PROTOCOL EFI_NAND_IO_PROTOCOL;
/** @endcond */

/** @addtogroup efi_nand_io_constants
@{ */
/** Protocol version. */
#define EFI_NAND_IO_PROTOCOL_REVISION 0x000000010000000
/** @} */ /* end_addtogroup efi_nand_io_constants */

/* Protocol GUID definition */
/** @ingroup efi_nand_io_protocol */
#define EFI_QCOM_NAND_IO_PROTOCOL_GUID \
   { 0x8d12919d, 0xb55a, 0x4324, { 0xba, 0x9b, 0x1d, 0x4c, 0xd7, 0xec, 0xcd, 0xfe } }
/** @cond */

/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the EFINandIo Protocol GUID.
 */
/** @ingroup efi_nand_io_protocol */
extern EFI_GUID gEfiNandIoProtocolGuid;

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* 
  @par Summary
  Open and initialize a nand io protocol instance. 

  @param NandDevId [IN]
    Device ID that specifies a FLASH NAND device.
  
  @param PartitionName [IN]
    Name of the partition to open. requires null terminated string name

  @param NandHandle [OUT]
    Pointer to the handle of the nand driver's partition instance.

  @retval     EFI_SUCCESS       Operation succeeded
  @retval     Others            Operation failed
*/
typedef
NAND_STATUS
(EFIAPI *EFI_NAND_IO_OPEN)(
  IN  UINT32                     NandDevId,
  IN  const UINT8               *PartitionName,
  OUT nand_handle_t             *NandHandle
);

/* 
  @par Summary
  Get nand device information. Nand driver assumes its clients have allocated
  the buffer to store the returned information.

  @param[in]   NandHandle       Pointer to the handle of the nand driver's partition instance.
  @param[out] NandInfo          Pointer to the client's nand device info data.

  @retval     EFI_SUCCESS       Operation succeeded
  @retval     Others            Operation failed
*/
typedef
NAND_STATUS
(EFIAPI *EFI_NAND_IO_GET_INFO)(
  IN  nand_handle_t              NandHandle,
  OUT struct nand_info          *NandInfo 
);

/* 
  @par Summary
  Erase a number of blocks in the Nand device. 

  @param[in]  NandHandle       Pointer to the handle of the nand driver's partition instance.
  @param[in] EraseBlock         Starting block to erase in the NAND device.
  @param[in] EraseBlockCount    Number of blocks to erase in the NAND device.

  @retval     EFI_SUCCESS       Operation succeeded
  @retval     Others            Operation failed
*/
typedef
NAND_STATUS
(EFIAPI *EFI_NAND_IO_ERASE_BLOCKS)(
  IN  nand_handle_t              NandHandle,
  IN  UINT32                     EraseBlock,
  IN  UINT32                     EraseBlockCount 
);

/* 
  @par Summary
  Sets the block state in a given block. 

  @param[in] NandHandle       Pointer to the handle of the nand driver's partition instance.
  @param[in] Block               The given block in the NAND device.
  @param[in] BlockState        The block state to set in the given block.

  @retval     EFI_SUCCESS       Operation succeeded
  @retval     Others            Operation failed
*/
typedef
NAND_STATUS
(EFIAPI *EFI_NAND_IO_SET_STATE)(
  IN  nand_handle_t              NandHandle,
  IN  UINT32                     Block,
  IN  enum nand_block_state      BlockState 
);

/* 
  @par Summary
  Gets the block state from a given block. 

  @param[in]  NandHandle       Pointer to the handle of the nand driver's partition instance.
  @param[in]  Block             The given block in the NAND device.
  @param[out] BlockState        Pointer to the block state of the given block.

  @retval     EFI_SUCCESS       Operation succeeded
  @retval     Others            Operation failed
*/
typedef
NAND_STATUS
(EFIAPI *EFI_NAND_IO_GET_STATE)(
  IN  nand_handle_t              NandHandle,
  IN  UINT32                     Block,
  OUT enum nand_block_state     *BlockState 
);

/* 
  @par Summary
  Write client's data to a number of pages in the NAND device. 

  @param[in]  NandHandle    Pointer to the handle of the nand driver's partition instance.
  @param[in]  Page             Starting page in the NAND device.
  @param[in]  PageCount     Number of pages to write in the NAND device.
  @param[in]  Buffer            Pointer to the client's data buffer.
  @param[in]  BufferSize      Data buffer size in bytes for NAND write pages.

  @retval     EFI_SUCCESS   Operation succeeded
  @retval     Others            Operation failed
*/
typedef
NAND_STATUS
(EFIAPI *EFI_NAND_IO_WRITE_PAGES)(
  IN  nand_handle_t              NandHandle,
  IN  enum page_access_opcode    Opcode,
  IN  UINT32                     Page,
  IN  UINT32                     PageCount,
  IN  void                      *Buffer,
  IN  UINT32                     BufferSize
);

/* 
  @par Summary
  Read data to client's buffer from a number of pages in the NAND device. 

  @param[in]  NandHandle    Pointer to the handle of the nand driver's partition instance.
  @param[in]  Page             Starting page in the NAND device.
  @param[in]  PageCount     Number of pages to read from the NAND device.
  @param[Out] Buffer          Pointer to the client's data buffer.
  @param[in]  BufferSize      Data buffer size in bytes for NAND read pages.

  @retval     EFI_SUCCESS       Operation succeeded
  @retval     Others            Operation failed
*/
typedef
NAND_STATUS
(EFIAPI *EFI_NAND_IO_READ_PAGES)(
  IN  nand_handle_t              NandHandle,
  IN  enum page_access_opcode    Opcode,
  IN  UINT32                     Page,
  IN  UINT32                     PageCount,
  OUT void                      *Buffer,        
  IN  UINT32                     BufferSize
);

/* 
  @par Summary
  Close a partition via nand io protocol instance. 

  @param[in]  NandHandle    Pointer to the handle of the nand driver's partition instance.

  @retval     EFI_SUCCESS       Operation succeeded
  @retval     Others            Operation failed

  @dependencies  none.
*/
typedef
NAND_STATUS
(EFIAPI *EFI_NAND_IO_CLOSE)(
  IN nand_handle_t               NandHandle
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_nand_io_protocol
  @par Summary
  This protocol provides an interface to access the NAND device.

  @par Parameters
  @inputprotoparams{nand_io_params.tex}
*/
struct _EFI_NAND_IO_PROTOCOL {
  UINTN                          Revision;
  EFI_NAND_IO_OPEN               Open;
  EFI_NAND_IO_GET_INFO           GetInfo;
  EFI_NAND_IO_ERASE_BLOCKS       EraseBlocks;
  EFI_NAND_IO_SET_STATE          BlockSetState;
  EFI_NAND_IO_GET_STATE          BlockGetState;
  EFI_NAND_IO_WRITE_PAGES        WritePages;
  EFI_NAND_IO_READ_PAGES         ReadPages;
  EFI_NAND_IO_CLOSE              Close;
};

#endif //ifndef __NAND_IO_PROTOCOL_H__

