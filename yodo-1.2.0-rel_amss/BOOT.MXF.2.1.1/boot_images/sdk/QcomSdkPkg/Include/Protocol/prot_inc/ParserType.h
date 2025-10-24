/** 
  @file  ParserType.h
  @brief Parser protocol shared structure interface.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who       what, where, why
 --------   ---       -----------------------------------------------------------
 05/27/20   yanw      init version
=============================================================================*/

#ifndef _PARSER_TYPE_H_
#define _PARSER_TYPE_H_

/** @defgroup efi_parser_protocol EFI_PRASER_PROTOCOL
 *  @ingroup UEFI_CORE 
 */
 /** @defgroup  efi_parser_protocol_prot PROTOCOL
 *  @ingroup efi_parser_protocol 
 */ 
 /** @defgroup  efi_parser_protocol_apis APIs
 *  @ingroup efi_parser_protocol 
 */ 

/** @defgroup  efi_parser_protocol_data DATA_STRUCTURES
 *  @ingroup efi_parser_protocol 
 */

/** @ingroup efi_parser_protocol_data */
typedef struct {
  UINT8     CommentChar;
  UINT8     Res1;
  UINT16    Res2;
  UINT32    Options;
}ParseOptionsType;

/** @ingroup efi_parser_protocol_apis 
*  Callback function type for separated Tokens and section string.
*  Token_ptr_array contains pointers to individual token strings. The Callback
*  Function must interprete the parsed tokens 
*  The SectionOffset returns the running count of the sections to handle duplicate
*  sections
* */
typedef void(*TokenSectionCallBackFuncType)(UINT8* Section, UINTN SectionOffset, UINT8* TokenPtrArray[], UINTN MaxTokens);

/** @ingroup efi_parser_protocol_apis 
*  Callback function type for separated Tokens. token_ptr_array contains pointers
*  to individual token strings. The Callback Function must interprete the parsed
*  tokens 
*
* */
typedef void(*TokenCallBackFuncType)(UINT8* TokenPtrArray[], UINTN MaxTokens);

/** @ingroup efi_parser_protocol_apis 
 *  Callback function type to get enumerated Key Value Pairs
 * If Success 0 is returned then the enumeration will continue
 * If failure -1 is returned then enumeration will stop */
typedef void(*KeyValueCallBackFuncType)(UINT8* Section, UINT8* Key, UINT8* Value);



#endif