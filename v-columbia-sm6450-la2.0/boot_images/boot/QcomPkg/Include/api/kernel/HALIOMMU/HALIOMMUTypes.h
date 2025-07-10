#ifndef __HAL_IOMMU_TYPES_H__
#define __HAL_IOMMU_TYPES_H__
/*==============================================================================
@file HALIOMMUTypes.h


        Copyright (c) 2008,2010,2014,2020 Qualcomm Technologies, Inc.
        All Rights Reserved.
        Qualcomm Confidential and Proprietary

==============================================================================*/
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/19/17   amo     Created

=============================================================================*/
/*------------------------------------------------------------------------------
* Include Files
*-----------------------------------------------------------------------------*/
#include "Uefi.h"
#include "HALIOMMU.h"
/*----------------------------------------------------------------------------*/

// cache property
typedef enum {

    // device non-gathering, non-reordering, no early write acknowledgement
    HAL_IOMMU_CACHE_DEVICE_nGnRnE       = 0,   // b0000
    HAL_IOMMU_CACHE_DEVICE_nGnRE        = 1,   // b0001
    HAL_IOMMU_CACHE_DEVICE_nGRE         = 2,   // b0010
    HAL_IOMMU_CACHE_DEVICE_GRE          = 3,   // b0011
    // outer non-cacheable, inner non-cacheable
    HAL_IOMMU_CACHE_OUTER_NC_INNER_NC   = 5,   // b0101
    // outer non-cacheable, inner write-through
    HAL_IOMMU_CACHE_OUTER_NC_INNER_WT   = 6,   // b0110
    // outer non-cacheable, inner writeback
    HAL_IOMMU_CACHE_OUTER_NC_INNER_WB   = 7,   // b0111
    HAL_IOMMU_CACHE_OUTER_WT_INNER_NC   = 9,   // b1001
    HAL_IOMMU_CACHE_OUTER_WT_INNER_WT   = 10,  // b1010
    HAL_IOMMU_CACHE_OUTER_WT_INNER_WB   = 11,  // b1011
    HAL_IOMMU_CACHE_OUTER_WB_INNER_NC   = 13,  // b1101
    HAL_IOMMU_CACHE_OUTER_WB_INNER_WT   = 14,  // b1110
    HAL_IOMMU_CACHE_OUTER_WB_INNER_WB   = 15,  // b1111
    // use stage 1 or outer/inner WB
    HAL_IOMMU_CACHE_DEFAULT             = 15,  

    HAL_IOMMU_CACHE_FORCE_ENUM_32_BIT   = 0x7FFFFFFF  /* Force to 32 bit enum */
} HAL_IOMMUCache_t;

// sharability
typedef enum {
    HAL_IOMMU_SHARE_NONE         = 0,
    HAL_IOMMU_SHARE_OUTER        = 2,
    HAL_IOMMU_SHARE_INNER        = 3,
    // use stage 1 or non-cached 
    HAL_IOMMU_SHARE_DEFAULT      = 0,

    HAL_IOMMU_SHARE_FORCE_ENUM_32_BIT   = 0x7FFFFFFF   /* Force to 32 bit enum */
} HAL_IOMMUShare_t;

// permission
typedef enum {
    HAL_IOMMU_PERM_X      = 0x1,
    HAL_IOMMU_PERM_W      = 0x2,
    HAL_IOMMU_PERM_R      = 0x4,
    HAL_IOMMU_PERM_RWX    = HAL_IOMMU_PERM_R | HAL_IOMMU_PERM_W | HAL_IOMMU_PERM_X,
    HAL_IOMMU_PERM_RW     = HAL_IOMMU_PERM_R | HAL_IOMMU_PERM_W,
    HAL_IOMMU_PERM_RX     = HAL_IOMMU_PERM_R | HAL_IOMMU_PERM_X,
    HAL_IOMMU_PERM_WX     = HAL_IOMMU_PERM_W | HAL_IOMMU_PERM_X,
    // user stage 1 or RWX
    HAL_IOMMU_PERM_DEFAULT= HAL_IOMMU_PERM_RWX,

    HAL_IOMMU_PERM_FORCE_ENUM_32_BIT = 0x7FFFFFFF  /* Force to 32 bit enum */
} HAL_IOMMUPerm_t;

typedef enum {
    HAL_IOMMU_UNMAPPED,
    HAL_IOMMU_MAPPED,
    HAL_IOMMU_PARTIAL_MAPPED,
    HAL_IOMMU_INVALID_MAP_STATUS
} HAL_IOMMUMapStatus_t;

// memory map attributes
typedef struct {
    uint64_t     size;
    uint64_t     inputAddr;
    uint64_t     outputAddr;
    HAL_IOMMUPerm_t     perm;
    HAL_IOMMUShare_t    shareAttr;
    HAL_IOMMUCache_t    cacheAttr;
} HAL_IOMMUMapAttr_t;

typedef struct {
    uint32_t    inputBitSize;
    uint32_t    outputBitSize;
} HAL_IOMMUPageTableAttr_t;

typedef enum HAL_IOMMUCtxBankType
{
  HAL_IOMMU_CB_S2_CTX,
  HAL_IOMMU_CB_S1_CTX_S2_BYPASS,
  HAL_IOMMU_CB_S1_CTX_S2_FAULT,
  HAL_IOMMU_CB_S1_CTX_S2_NESTED,
} HAL_IOMMUCtxBankType;


enum hal_iommu_mmu_arch {
    HAL_IOMMU_ARCH_MMU500,
    HAL_IOMMU_ARCH_QSMMU,
    HAL_IOMMU_ARCH_INVALID
};

#define HAL_IOMMU_INVALID_ADDR 0xFFFFFFFF
#define HAL_IOMMU_INVALID_ARID ((uint32_t)0xFFFFFFFF)
#define HAL_IOMMU_INVALID_CB_IDX ((uint32_t)0xFFFFFFFF)

#define HAL_IOMMU_S2CR_TYPE_TRANSLATION_CONTEXT 0
#define HAL_IOMMU_S2CR_TYPE_BYPASS_MODE 1
#define HAL_IOMMU_S2CR_TYPE_FAULT_CONTEXT 2

#define HAL_IOMMU_VALID_MASK 0x80000000
#define HAL_IOMMU_SID_MASK_SHIFT 16
#define HAL_IOMMU_CB_UNUSED_VMID 0xFF

#define HAL_IOMMU_BYPASS_NON_CCA_SCTLR_VAL 0x000000E0
#define HAL_IOMMU_BYPASS_CCA_SCTLR_VAL 0x0A9F00E0
#define HAL_IOMMU_BYPASS_NON_CCA_TCR_VAL 0x0
#define HAL_IOMMU_BYPASS_CCA_TCR_VAL 0x0

#endif /* __HAL_IOMMU_TYPES_H__ */
