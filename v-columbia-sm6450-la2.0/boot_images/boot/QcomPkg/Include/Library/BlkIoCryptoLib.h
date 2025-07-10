/** 

@file BlkIoCryptoLib.h
   
  This file provides Inline Cryptographic Interface Protocol definitions.

  Copyright (c) 2021 Qualcomm Technologies, Inc. 
  All Rights Reserved. 
  Qualcomm Technologies Proprietary and Confidential

**/

/*=============================================================================
                              EDIT HISTORY
 when       who           what, where, why
 --------   ---           ----------------------------------------------------
 04/28/21   gaurkash      Initial revision
=============================================================================*/

#ifndef _BLKIO_CRYPTO_LIB_H_
#define _BLKIO_CRYPTO_LIB_H_

typedef union {
	UINT32 regval[2];
	struct {
		UINT8 dusize;
		UINT8 capidx;
		UINT8 nop;
		UINT8 cfge;
		UINT8 reserved[4];
	};
} CryptoConfig;

EFI_STATUS EFIAPI SetICEConfiguration (			
    IN CHAR8                                              *Id,
    IN UINT64                                             ConfigurationCount, 
    IN EFI_BLOCK_IO_CRYPTO_CONFIGURATION_TABLE_ENTRY      *ConfigurationTable, 
    OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY  *ResultingTable
    );

#endif

