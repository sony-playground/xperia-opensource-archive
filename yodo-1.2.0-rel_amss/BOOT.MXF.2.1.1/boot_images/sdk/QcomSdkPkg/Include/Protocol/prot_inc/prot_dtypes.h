#ifndef __PROT_DTYPES_H__
#define __PROT_DTYPES_H__
/*==============================================================================
@file prot_dtypes.h


        Copyright (c) 2020 Qualcomm Technologies, Inc.
        All Rights Reserved.
        Qualcomm Confidential and Proprietary

==============================================================================*/
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/18/20   da      Created

=============================================================================*/
/*------------------------------------------------------------------------------
* Include Files
*-----------------------------------------------------------------------------*/
#include "Uefi.h"

/*----------------------------------------------------------------------------*/

/** @defgroup efi_glink_protocol EFI_GLINK_PROTOCOL
 *  @ingroup tech_core
 */
 /** @defgroup  efi_glink_protocol_prot PROTOCOL
 *  @ingroup efi_glink_protocol 
 */ 
 /** @defgroup  efi_glink_protocol_apis APIs
 *  @ingroup efi_glink_protocol 
 */ 

/** @defgroup  efi_glink_protocol_data DATA_STRUCTURES
 *  @ingroup efi_glink_protocol 
 */ 

/*----------------------------------------------------------------------------
* Common DataType Defines [dont use com_dtpyes.h for EDK complience]
*----------------------------------------------------------------------------*/
typedef  UINT16     uint16_t;
typedef  UINT32     uint32_t;
typedef  UINT64     uint64_t;
typedef  INT16      int16_t;
typedef  INT32      int32_t;
typedef  INT64      int64_t;
typedef  UINT8      uint8_t;
typedef  INT8       int8_t; 
typedef  UINTN      size_t;

typedef  UINT32     uint32;
typedef  UINT16     uint16;
typedef  UINT64     uint64;
typedef  UINT8      uint8;
typedef  INT16      int16;
typedef  INT32      int32;
typedef  INT64      int64;
typedef  INT8       int8; 

typedef  BOOLEAN    boolean; 

/*----------------------------------------------------------------------------*/

#endif // __PROT_DTYPES_H__
