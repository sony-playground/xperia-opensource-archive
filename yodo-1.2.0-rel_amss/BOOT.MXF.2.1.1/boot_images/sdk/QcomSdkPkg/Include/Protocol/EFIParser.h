/**
  @file  EFIParser.h
  @brief Parser Protocol for UEFI.
*/

/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/05/20  yw      init version.
=============================================================================*/
#ifndef __EFI_PARSER_H__
#define __EFI_PARSER_H__

#include <ParserType.h>
/** @ingroup efi_parser_protocol_data */
#define EFI_PARSER_PROTOCOL_VERSION_V1 0x0000000000010001
/** @ingroup efi_parser_protocol_data */
#define EFI_PARSER_PROTOCOL_GUID \
  { 0x612fabcb, 0x480c, 0x4d49, { 0xbc, 0x89, 0x71, 0x79, 0x4c, 0x99, 0x02, 0xf8 } }
  
extern EFI_GUID gEfiParserProtocolGuid;


/** @ingroup efi_parser_protocol_apis 
 *  Open Parser for the buffer passed in
 * If ParseOptions pointer is NULL then default values are used (ie # is comment char)
 *
 * @param
 * @param[IN]  Buffer     : Buffer containing the data to be parsed
 * @param[IN]  BufferSize : Size of the data in buffer
 * @param[IN]  Popt       : ParseOptions (Only comment char is supported now)
 * @param[OUT] Pd         : Ptr to parser descriptor
 *
 * @retval EFI_SUCCESS      Parser opened successfully.
 * */
typedef
EFI_STATUS
(EFIAPI *EFI_PARSER_OPEN) (
   IN  UINT8*             Buffer,
   IN  UINT32             BufferSize,
   IN  ParseOptionsType*  Popt OPTIONAL,
   OUT INTN*			  Pd
   );

/** @ingroup efi_parser_protocol_apis 
 * Close the parser context and release the resources.
 *
 * @param[IN] Pd  : Parser Descriptor
 *
 * @retval EFI_SUCCESS      Parser closed successfully.
 * */
typedef
EFI_STATUS
(EFIAPI *EFI_PARSER_CLOSE) (
   IN  INTN            Pd
   );
   
/** @ingroup efi_parser_protocol_apis 
 * Enumerate the key values by getting callback for each item. Optional Section string can
 * be specified to get the values only for the specified section. If the Section pointer is
 * NULL then all values with their Section string is returned.
 *
 * @param[IN] Pd            : Parser Descriptor
 * @param[IN] Section       : Optional Section, if specified, only key-value pairs for the specified section are returned.
 * @param[IN] CallBackFunc  : Callback function to get the callback with all the enumerated values.
 *
 * @retval EFI_SUCCESS      
 * */
typedef
EFI_STATUS
(EFIAPI *EFI_PARSER_ENUM_KEY_VALUES) (
   IN  INTN                      Pd,
   IN  UINT8*                    Section   OPTIONAL,
   IN  KeyValueCallBackFuncType  CallBackFunc
   ); 
 
/** @ingroup efi_parser_protocol_apis 
 * Re-open parser for repeated further processing
 *
 * @param[IN] Pd            : Parser Descriptor
 *
 * @retval EFI_SUCCESS      Parser re-opened successfully.
 * */
typedef
EFI_STATUS
(EFIAPI *EFI_PARSER_REOPEN) (
   IN INTN Pd
   );

/** @ingroup efi_parser_protocol_prot */ 
typedef struct _EFI_PARSER_PROTOCOL {
   UINT64                           Revision;
   EFI_PARSER_OPEN            		OpenParser;
   EFI_PARSER_CLOSE        			CloseParser;
   EFI_PARSER_ENUM_KEY_VALUES       EnumKeyValues;
   EFI_PARSER_REOPEN                ReopenParser;
}EFI_PARSER_PROTOCOL;

#endif
