/**
 * @file    BlkCryptoLibNull.c
 * @brief   Stubs for Blk crypto Library
 *
 *  Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
 */

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Protocol/BlockIoCrypto.h>
#include "BlkIoCryptoLib.h"

EFI_STATUS EFIAPI SetICEConfiguration (			
    IN CHAR8                                              *Id,
    IN UINT64                                             ConfigurationCount, 
    IN EFI_BLOCK_IO_CRYPTO_CONFIGURATION_TABLE_ENTRY      *ConfigurationTable, 
    OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY  *ResultingTable)
{
    return EFI_SUCCESS;
}
