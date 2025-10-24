/*========================================================================
SecNvmDef.h
This file describes the daemon types and defines.

Copyright (c) 2020 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=========================================================================*/
/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/09/20   ll      initial release
=============================================================================*/
#ifndef SECNVMDEFS_H_
#define SECNVMDEFS_H_

#include "osCommon.h"

#ifdef OFFSET_OF
# undef OFFSET_OF
#endif
#define OFFSET_OF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

#define SIZE_4K  0x1000
#ifndef ROUND_UP
    #define ROUND_UP(N, S) ((((N) + (S) - 1) / (S)) * (S))
#endif

/* Maximum size (including null) for channel names - match glink (from spcom.h) */
#define SPCOM_CHANNEL_NAME_SIZE         32

// Basic sizes
#define  UUID_SIZE             16
#define  MAX_SEGS              5
#define  MAX_SB_SEGS           3
#define  HASH_BLOCK_SIZE       32
#define  CMAC_SIZE             16
#define  ARC_SIZE              32
#define  IV_SIZE               16
#define  COMMIT_CONTROL_SIZE   1
#define  MAX_BLOCKS_IN_SEGMENT 32
#define  MAX_BYTEMAP_SIZE      MAX_BLOCKS_IN_SEGMENT

// Data
#define   DATA_BLOCK_SIZE 1024 

// L2
#define   L2_BLOCK_SIZE   (HASH_BLOCK_SIZE + IV_SIZE) // 48 bytes
#define   BLOCKS_IN_SLICE 32
#define   SLICE_SIZE      L2_BLOCK_SIZE * BLOCKS_IN_SLICE

// L1
#define    SEG_NUM_SIZE        1
#define    RESERVED_META_DATA  15
#define    MAJOR_VER_SIZE      1
#define    MINOR_VER_SIZE      1
#define    VER_SIZE            (MAJOR_VER_SIZE + MINOR_VER_SIZE)

#define    L1_BLOCKS_IN_SLICE 32

#define    ROOT_HASH_SIZE     CMAC_SIZE

#pragma pack(push, 1)
// actual data block
typedef struct {
    uint8_t d[DATA_BLOCK_SIZE]; // 1Kb
} data_block_t;

// (hash,iv) values of data_block
typedef struct {
    uint8_t hash_block[HASH_BLOCK_SIZE]; // 32 byte
    uint8_t iv[IV_SIZE];                 // 16 byte
} l2_slice_t;

// same as l2_block
typedef struct {
    uint8_t hash_block[HASH_BLOCK_SIZE]; // 32 byte
} l1_block_t;

#pragma pack(pop)

#endif /* SECNVMDEFS_H_ */
