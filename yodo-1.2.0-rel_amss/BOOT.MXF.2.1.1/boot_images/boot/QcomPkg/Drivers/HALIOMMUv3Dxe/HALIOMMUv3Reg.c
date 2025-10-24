/*=========================================================================

                       S M M U  H A L  L I B R A R Y

FILE:      HALHAL_IOMMU.c
   System HAL_IOMMU Hardware Abstraction Layer (HAL)

GENERAL DESCRIPTION
  This file contains hardware abstraction layer routines for managing HAL_IOMMU instances
  for multimedia 

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
 
Copyright (c) 2010 - 2015
Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
==========================================================================*/
/*==========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/HALIOMMUv3Dxe/HALIOMMUv3Reg.c#1 $
$DateTime: 2022/08/18 10:15:46 $
$Author: pwbldsvc $
$Change: 39147961 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------
03/06/12   spa     Initial Version
==========================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/
#include <string.h>
#include "HALIOMMUv3Reg.h"
#include "HALIOMMUTypes.h"
//#include "SMMUUtils.h" TODO
// TODO
void *SMMU_Alloc_Pages_Aligned(uint64 size)
{
    return NULL;
}
void SMMU_memory_barrier(void)
{
    __asm("DSB sy");
}


static struct hal_iommuv3_field_info_s g_ste_field_info[STE_NUM_FIELDS] = {
    {0, 0, 1}, // V: {index = 0, offset = 0, width = 1}
    {0, 1, 3}, // Config
    {0, 4, 2}, // S1_Fmt
    {0, 6, 46}, // S1ContextPtr
    {1, 27, 5}, // S1CDMax
    {2, 0, 2}, // S1_DSS
    {2, 2, 2}, // S1_CIR
    {2, 4, 2}, // S1_COR
    {2, 6, 2}, // S1_CSH
    {2, 8, 1}, // S1_S2HWU59
    {2, 9, 1}, // S1_S2HWU60
    {2, 10, 1}, // S1_S2HWU61
    {2, 11, 1}, // S2_S2HWU62
    {2, 12, 1}, // DRE
    {2, 13, 4}, // CONT
    {2, 17, 1}, // DCP
    {2, 18, 1}, // PPAR
    {2, 19, 1}, // MEV
    {2, 20, 4}, // Reserved0
    {2, 25, 1}, // S2FWB
    {2, 26, 1}, // S1_MPAM
    {2, 27, 1}, // S1_STALLD
    {2, 28, 2}, // EATS
    {2, 30, 2}, // STRW
    {3, 0, 4}, // MemAttr
    {3, 4, 1}, // MTCFG
    {3, 5, 4}, // ALLOCCFG
    {3, 12, 2}, // SH_CFG
    {3, 14, 2}, // NS_CFG
    {3, 16, 2}, // PRIV_CFG
    {3, 18, 2}, // INST_CFG
    {3, 20, 12}, // ImplDef0
    {4, 0, 16}, // S2_VMID,
    {4, 16, 16}, // ImplDef1
    {5, 0, 6}, // S2T0SZ
    {5, 6, 2}, // S2_SL0
    {5, 8, 2}, // S2_IR0
    {5, 10, 2}, // S2_OR0
    {5, 12, 2}, // S2_SH0
    {5, 14, 2}, // S2_TG
    {5, 16, 3}, // S2PS
    {5, 19, 1}, // S2AA64
    {5, 20, 1}, // S2ENDI
    {5, 21, 1}, // S2AFFD
    {5, 22, 1}, // S2PTW
    {5, 23, 1}, // S22HD
    {5, 24, 1}, // S2HA
    {5, 25, 1}, // S2S
    {5, 26, 1}, // S2R
    {6, 0, 1}, // S2NSW
    {6, 1, 1}, // S2NSA
    {6, 4, 48}, // S2TTB
    {8, 0, 16}, // ImplDef2
    {8, 16, 16}, // PARTID
    {9, 0, 6}, // S_S2T0SZ
    {9, 6, 2}, // S_S2_SL0
    {9, 14, 2}, // S_S2_TG
    {10, 0, 8}, // PMG
    {10, 12, 40}, // VMSPtr
    {12, 0, 1}, // S2SW
    {12, 1, 1}, // S2SA
    {12, 4, 48}, // S2_S2_S2TTB    
};

static struct hal_iommuv3_field_info_s g_cd_field_info[CD_NUM_FIELDS] = {
    {0, 0, 6}, // CD_T0SZ {index = 0, offset = 0, width = 6}
    {0, 6, 2}, // CD_TG0,
    {0, 8, 2}, // CD_IR0,
    {0, 10, 2}, // CD_OR0,
    {0, 12, 2}, // CD_SH0,
    {0, 14, 1}, // CD_EPD0,
    {0, 15, 1}, // CD_ENDI,
    {0, 16, 6}, // CD_T1SZ,
    {0, 22, 2}, // CD_TG1,
    {0, 24, 2}, // CD_IR1,
    {0, 26, 2}, // CD_OR1,
    {0, 28, 2}, // CD_SH1,
    {0, 30, 1}, // CD_EPD1,
    {0, 31, 1}, // CD_V,
    {1, 0, 3}, // CD_IPS,
    {1, 3, 1}, // CD_AFFD,
    {1, 4, 1}, // CD_WXN,
    {1, 5, 1}, // CD_UWXN,
    {1, 6, 2}, // CD_TBI,
    {1, 8, 1}, // CD_PAN,
    {1, 9, 1}, // CD_AA64,
    {1, 10, 1}, // CD_HD,
    {1, 11, 1}, // CD_HA,
    {1, 12, 1}, // CD_S,
    {1, 13, 1}, // CD_R,
    {1, 14, 1}, // CD_A,
    {1, 15, 1}, // CD_ASET,
    {1, 16, 16}, // CD_ASID,
    {2, 0, 1}, // CD_NSCFG0,
    {2, 1, 1}, // CD_HAD0,
    {2, 4, 48}, // CD_TTB0,
    {3, 28, 1}, // CD_HWU059,
    {3, 29, 1}, // CD_HWU060,
    {3, 30, 1}, // CD_HWU061,
    {3, 31, 1}, // CD_HWU062,
    {4, 0, 1}, // CD_NSCFG1,
    {4, 1, 1}, // CD_HAD1,
    {4, 4, 48}, // CD_TTB1,
    {5, 28, 1}, // CD_HWU159,
    {5, 29, 1}, // CD_HWU160,
    {5, 30, 1}, // CD_HWU161,
    {5, 31, 1}, // CD_HWU162,
    {6, 0, 64}, // CD_MAIR,
    {8, 0, 64}, // CD_AMAIR,
    {10, 0, 32}, // CD_ImplDef0,
    {11, 0, 16}, // CD_PARTID,
    {11, 16, 8}, // CD_PMG,
};


/**
* HAL_IOMMU IO Functions 
*/

uint32 HAL_IOMMUv3_IN32(uint64 hal_iommu_base, uint32 reg_space_offset, uint32 offset) 
{
	return (*((volatile uint32 *)((uint64)(hal_iommu_base + reg_space_offset + offset))));
}

void
HAL_IOMMUv3_OUT32(uint64 hal_iommu_base, uint32 reg_space_offset, uint32 offset, uint32 value) 
{
	*((uint32 *)((uint64)(hal_iommu_base + reg_space_offset + offset))) = value;
}

uint64 HAL_IOMMUv3_IN64(uint64 hal_iommu_base, uint32 reg_space_offset, uint32 offset) 
{
	return (*((volatile uint64 *)((uint64)(hal_iommu_base + reg_space_offset + offset))));
}

void
HAL_IOMMUv3_OUT64(uint64 hal_iommu_base, uint32 reg_space_offset, uint32 offset, uint64 value)
{
	*((uint64 *)((uint64)(hal_iommu_base + reg_space_offset + offset))) = value;
}

HAL_IOMMUResult_t HAL_IOMMUv3_REG_READ32(uint64 base_addr, int ns, uint32 reg_offset, uint32 *out)
{
    if(!out)
        return HAL_IOMMU_ERR_NULL_POINTER;
    
    uint32 reg_space_offset = ns ? HAL_IOMMUv3_NON_SECURE_OFFSET : HAL_IOMMUv3_SECURE_OFFSET;
    *out = HAL_IOMMUv3_IN32(base_addr, reg_space_offset, reg_offset);
    return HAL_IOMMU_ERR_HAL_SUCCESS;
}

HAL_IOMMUResult_t HAL_IOMMUv3_REG_WRITE32(uint64 base_addr, int ns, uint32 reg_offset, uint32 val)
{
    uint32 reg_space_offset = ns ? HAL_IOMMUv3_NON_SECURE_OFFSET : HAL_IOMMUv3_SECURE_OFFSET;
    HAL_IOMMUv3_OUT32(base_addr, reg_space_offset, reg_offset, val);
    return HAL_IOMMU_ERR_HAL_SUCCESS;
}

HAL_IOMMUResult_t HAL_IOMMUv3_REG_READ64(uint64 base_addr, int ns, uint32 reg_offset, uint64 *out)
{
    if(!out)
        return HAL_IOMMU_ERR_NULL_POINTER;
    
    uint32 reg_space_offset = ns ? HAL_IOMMUv3_NON_SECURE_OFFSET : HAL_IOMMUv3_SECURE_OFFSET;
    *out = HAL_IOMMUv3_IN64(base_addr, reg_space_offset, reg_offset);
    return HAL_IOMMU_ERR_HAL_SUCCESS;
}

HAL_IOMMUResult_t HAL_IOMMUv3_REG_WRITE64(uint64 base_addr, int ns, uint32 reg_offset, uint64 val)
{
    uint32 reg_space_offset = ns ? HAL_IOMMUv3_NON_SECURE_OFFSET : HAL_IOMMUv3_SECURE_OFFSET;
    HAL_IOMMUv3_OUT64(base_addr, reg_space_offset, reg_offset, val);
    return HAL_IOMMU_ERR_HAL_SUCCESS;
}

/* ============================================================================= */
/**
* HAL_IOMMU IO API Handle definition
*/
HAL_IOMMUResult_t   HAL_IOMMUv3_GetIDR0(uint64 base_addr, int ns, HAL_IOMMUv3_IDR0_t *idr0)
{
    return HAL_IOMMUv3_REG_READ32(base_addr, ns, HAL_IOMMUv3_IDR0_OFFSET, (uint32 *)idr0);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_SetIDR0(uint64 base_addr, int ns, HAL_IOMMUv3_IDR0_t idr0)
{
    return HAL_IOMMUv3_REG_WRITE32(base_addr, ns, HAL_IOMMUv3_IDR0_OFFSET, idr0.raw);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_GetCR0(uint64 base_addr, int ns, HAL_IOMMUv3_CR0_t *cr0)
{
    return HAL_IOMMUv3_REG_READ32(base_addr, ns, HAL_IOMMUv3_CR0_OFFSET, (uint32 *)cr0);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_SetCR0(uint64 base_addr, int ns, HAL_IOMMUv3_CR0_t cr0)
{
    return HAL_IOMMUv3_REG_WRITE32(base_addr, ns, HAL_IOMMUv3_CR0_OFFSET, cr0.raw);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_GetCR1(uint64 base_addr, int ns, HAL_IOMMUv3_CR1_t *cr1)
{
    return HAL_IOMMUv3_REG_READ32(base_addr, ns, HAL_IOMMUv3_CR1_OFFSET, (uint32 *)cr1);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_SetCR1(uint64 base_addr, int ns, HAL_IOMMUv3_CR1_t cr1)
{
    return HAL_IOMMUv3_REG_WRITE32(base_addr, ns, HAL_IOMMUv3_CR1_OFFSET, cr1.raw);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_GetCR2(uint64 base_addr, int ns, HAL_IOMMUv3_CR2_t *cr2)
{
    return HAL_IOMMUv3_REG_READ32(base_addr, ns, HAL_IOMMUv3_CR2_OFFSET, (uint32 *)cr2);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_SetCR2(uint64 base_addr, int ns, HAL_IOMMUv3_CR2_t cr2)
{
    return HAL_IOMMUv3_REG_WRITE32(base_addr, ns, HAL_IOMMUv3_CR2_OFFSET, cr2.raw);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_GetSTRTABCFG(uint64 base_addr, int ns, HAL_IOMMUv3_STRTAB_BASE_CFG_t *strtab_cfg)
{
    return HAL_IOMMUv3_REG_READ32(base_addr, ns, HAL_IOMMUv3_STRTAB_BASE_CFG_OFFSET, (uint32 *)strtab_cfg);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_SetSTRTABCFG(uint64 base_addr, int ns, HAL_IOMMUv3_STRTAB_BASE_CFG_t strtab_cfg)
{
    return HAL_IOMMUv3_REG_WRITE32(base_addr, ns, HAL_IOMMUv3_STRTAB_BASE_CFG_OFFSET, strtab_cfg.raw);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_GetGBPA(uint64 base_addr, int ns, HAL_IOMMUv3_GBPA_t *gbpa)
{
    return HAL_IOMMUv3_REG_READ32(base_addr, ns, HAL_IOMMUv3_GBPA_OFFSET, (uint32 *)gbpa);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_SetGBPA(uint64 base_addr, int ns, HAL_IOMMUv3_GBPA_t gbpa)
{
    return HAL_IOMMUv3_REG_WRITE32(base_addr, ns, HAL_IOMMUv3_GBPA_OFFSET, gbpa.raw);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_GetIRQCTRL(uint64 base_addr, int ns, HAL_IOMMUv3_IRQ_CTRL_t *irq_ctrl)
{
    return HAL_IOMMUv3_REG_READ32(base_addr, ns, HAL_IOMMUv3_IRQ_CTRL_OFFSET, (uint32 *)irq_ctrl);
}

HAL_IOMMUResult_t   HAL_IOMMUv3_SetIRQCTRL(uint64 base_addr, int ns, HAL_IOMMUv3_IRQ_CTRL_t irq_ctrl)
{
    return HAL_IOMMUv3_REG_WRITE32(base_addr, ns, HAL_IOMMUv3_IRQ_CTRL_OFFSET, irq_ctrl.raw);
}


// STE Management APIs
HAL_IOMMUResult_t   HAL_IOMMUv3_ProgramSTEField(STE_Field_t field, void *ste_addr, uint64 val)
{
    uint32  mask32 = 0, result32 = 0;
    uint64  mask64 = 0, result64 = 0;
    
    if(g_ste_field_info[field].width > 32) {
        // Obtain mask
        mask64 = ((1 << g_ste_field_info[field].width) - 1) << g_ste_field_info[field].offset;
        // Read existing STE field(s)
        result64 = ((uint64 *)ste_addr)[g_ste_field_info[field].index/2];
        // Clear Field to Program
        result64 &= ~mask64; 
        // Program Field in Local Copy
        result64 |= val << g_ste_field_info[field].offset;
        // Install Field
        ((uint64 *)ste_addr)[g_ste_field_info[field].index/2] = result64;
    }
    else {
        // Obtain mask
        mask32 = ((1 << g_ste_field_info[field].width) - 1) << g_ste_field_info[field].offset;
        // Read existing STE field(s)
        result32 = ((uint32 *)ste_addr)[g_ste_field_info[field].index];
        // Clear Field to Program
        result32 &= ~mask32; 
        // Program Field in Local Copy
        result32 |= val << g_ste_field_info[field].offset;
        // Install Field
        ((uint32 *)ste_addr)[g_ste_field_info[field].index] = result32;
    }
    
    return HAL_IOMMU_ERR_HAL_SUCCESS;
}

HAL_IOMMUResult_t   HAL_IOMMUv3_ProgramSTEFieldInPlace(uint64 smmu_base_addr, int ns, uint32 sid, STE_Field_t field, uint64 val)
{
    HAL_IOMMUv3_STRTAB_BASE_CFG_t strtab_cfg = {0};
    void *strtab_base;
    
    if(smmu_base_addr == 0) {
        return HAL_IOMMU_ERR_NULL_POINTER;
    }
    
    // Read STRTAB Configuration Register
    HAL_IOMMUv3_GetSTRTABCFG(smmu_base_addr, ns, &strtab_cfg);
    HAL_IOMMUv3_REG_READ64(smmu_base_addr, ns, HAL_IOMMUv3_STRTAB_BASE_OFFSET, (uint64 *)&strtab_base);
    
    if(!strtab_base) {
        return HAL_IOMMU_ERR_NULL_POINTER;
    }
    
    // Check SID is within MAX
    if(sid >= (1 << strtab_cfg.formatted.LOG2SIZE) || sid >= HAL_IOMMUv3_MAX_SID) {
        return HAL_IOMMU_ERR_OUT_OF_RANGE;
    }
    
    // Determine STRTAB Configuration
    if(strtab_cfg.formatted.FMT == 0) {
        // Table is Linear
        hal_iommuv3_ste_t *linear_tab = (hal_iommuv3_ste_t *)strtab_base;
        
        // Update Field
        HAL_IOMMUv3_ProgramSTEField(field, (void *)&linear_tab[sid], val);
        
        // CMO ? TODO
    }
    else {
        // Table is Split
        uint64 *split_table = (uint64 *)strtab_base;
        uint64 l1_descriptor;
        uint32 sids_per_leaf, index_l1, index_l2;
        hal_iommuv3_ste_t *l2_table;
        
        
        switch(strtab_cfg.formatted.SPLIT) {
            case 10:
                // 64KB leaf tables, 1024 SIDs per table (1024 * 64B)
                sids_per_leaf = 1024;
                break;
            case 8:
                // 16KB leaf tables, 256 SIDs per table (256 * 64B)
                sids_per_leaf = 256;
                break;
            case 6:
            default: // all other values behave as 6
                // 4KB leaf tables, 64 SIDs per table (64 * 64B)
                sids_per_leaf = 64;
                break;
        }
        
        index_l1 = sid / sids_per_leaf;
        index_l2 = sid % sids_per_leaf;
        
        // Get L1 Descriptor
        l1_descriptor = split_table[index_l1];
        // Get L2 table and validate
        l2_table = (hal_iommuv3_ste_t *)(l1_descriptor & ~0x3F);
        
        if(!l2_table) {
            // No Table Present, Allocate One and setup SPAN
            l2_table = (hal_iommuv3_ste_t *)SMMU_Alloc_Pages_Aligned(sids_per_leaf * sizeof(hal_iommuv3_ste_t));
            if(!l2_table) {
                return HAL_IOMMU_ERR_MALLOC_FAILED;
            }
            
            // Update L1 descriptor
            l1_descriptor = (uint64)l2_table | (strtab_cfg.formatted.SPLIT + 1);
            split_table[index_l1] = l1_descriptor;
        }
        
        // Update Field
        HAL_IOMMUv3_ProgramSTEField(field, (void *)&l2_table[index_l2], val);

        // CMO? TODO
    }
    
    // Ensure SMMU can see STE
    SMMU_memory_barrier();
    
    return HAL_IOMMU_ERR_HAL_SUCCESS;
}

HAL_IOMMUResult_t   HAL_IOMMUv3_InstallSTE(uint64 smmu_base_addr, int ns, hal_iommuv3_ste_t *ste, uint32 sid)
{
    HAL_IOMMUv3_STRTAB_BASE_CFG_t strtab_cfg = {0};
    void *strtab_base;
    
    if(!ste || smmu_base_addr == 0) {
        return HAL_IOMMU_ERR_NULL_POINTER;
    }
    
    // Read STRTAB Configuration Register
    HAL_IOMMUv3_GetSTRTABCFG(smmu_base_addr, ns, &strtab_cfg);
    HAL_IOMMUv3_REG_READ64(smmu_base_addr, ns, HAL_IOMMUv3_STRTAB_BASE_OFFSET, (uint64 *)&strtab_base);
    
    if(!strtab_base) {
        return HAL_IOMMU_ERR_NULL_POINTER;
    }
    
    // Check SID is within MAX
    if(sid >= (1 << strtab_cfg.formatted.LOG2SIZE) || sid >= HAL_IOMMUv3_MAX_SID) {
        return HAL_IOMMU_ERR_OUT_OF_RANGE;
    }
    
    // Determine STRTAB Configuration
    if(strtab_cfg.formatted.FMT == 0) {
        // Table is Linear
        hal_iommuv3_ste_t *linear_tab = (hal_iommuv3_ste_t *)strtab_base;
        
        // Install STE
        memscpy((void *)&linear_tab[sid], sizeof(hal_iommuv3_ste_t), (void *)ste, sizeof(hal_iommuv3_ste_t));
        
        // CMO ? TODO
    }
    else {
        // Table is Split
        uint64 *split_table = (uint64 *)strtab_base;
        uint64 l1_descriptor;
        uint32 sids_per_leaf, index_l1, index_l2;
        hal_iommuv3_ste_t *l2_table;
        
        
        switch(strtab_cfg.formatted.SPLIT) {
            case 10:
                // 64KB leaf tables, 1024 SIDs per table (1024 * 64B)
                sids_per_leaf = 1024;
                break;
            case 8:
                // 16KB leaf tables, 256 SIDs per table (256 * 64B)
                sids_per_leaf = 256;
                break;
            case 6:
            default: // all other values behave as 6
                // 4KB leaf tables, 64 SIDs per table (64 * 64B)
                sids_per_leaf = 64;
                break;
        }
        
        index_l1 = sid / sids_per_leaf;
        index_l2 = sid % sids_per_leaf;
        
        // Get L1 Descriptor
        l1_descriptor = split_table[index_l1];
        // Get L2 table and validate
        l2_table = (hal_iommuv3_ste_t *)(l1_descriptor & ~0x3F);
        
        if(!l2_table) {
            // No Table Present, Allocate One and setup SPAN
            l2_table = (hal_iommuv3_ste_t *)SMMU_Alloc_Pages_Aligned(sids_per_leaf * sizeof(hal_iommuv3_ste_t));
            if(!l2_table) {
                return HAL_IOMMU_ERR_MALLOC_FAILED;
            }
            
            // Update L1 descriptor
            l1_descriptor = (uint64)l2_table | (strtab_cfg.formatted.SPLIT + 1);
            split_table[index_l1] = l1_descriptor;
        }
        
        // install STE
        memscpy(&l2_table[index_l2], sizeof(hal_iommuv3_ste_t), ste, sizeof(hal_iommuv3_ste_t));

        // CMO? TODO
    }
    
    // Ensure SMMU can see STE
    SMMU_memory_barrier();
    
    return HAL_IOMMU_ERR_HAL_SUCCESS;
}

// CD Management APIs
HAL_IOMMUResult_t   HAL_IOMMUv3_ProgramCDField(CD_Field_t field, void *cd_addr, uint64 val)
{
    uint32  mask32 = 0, result32 = 0;
    uint64  mask64 = 0, result64 = 0;
    
    if(g_cd_field_info[field].width > 32) {
        // Obtain mask
        mask64 = ((1 << g_cd_field_info[field].width) - 1) << g_cd_field_info[field].offset;
        // Read existing CD field(s)
        result64 = ((uint64 *)cd_addr)[g_cd_field_info[field].index/2];
        // Clear Field to Program
        result64 &= ~mask64; 
        // Program Field in Local Copy
        result64 |= val << g_cd_field_info[field].offset;
        // Install Field
        ((uint64 *)cd_addr)[g_cd_field_info[field].index/2] = result64;
    }
    else {
        // Obtain mask
        mask32 = ((1 << g_cd_field_info[field].width) - 1) << g_cd_field_info[field].offset;
        // Read existing CD field(s)
        result32 = ((uint32 *)cd_addr)[g_cd_field_info[field].index];
        // Clear Field to Program
        result32 &= ~mask32; 
        // Program Field in Local Copy
        result32 |= val << g_cd_field_info[field].offset;
        // Install Field
        ((uint32 *)cd_addr)[g_cd_field_info[field].index] = result32;
    }
    
    return HAL_IOMMU_ERR_HAL_SUCCESS;
}

HAL_IOMMUResult_t   HAL_IOMMUv3_InstallCD(uint64 smmu_base_addr, int ns, hal_iommuv3_cd_t *cd, uint32 sid)
{
    HAL_IOMMUv3_STRTAB_BASE_CFG_t strtab_cfg = {0};
    void *strtab_base;
    
    // Read STRTAB Configuration Register
    HAL_IOMMUv3_GetSTRTABCFG(smmu_base_addr, ns, &strtab_cfg);
    HAL_IOMMUv3_REG_READ64(smmu_base_addr, ns, HAL_IOMMUv3_STRTAB_BASE_OFFSET, (uint64 *)&strtab_base);
    
    if(!cd || !strtab_base || smmu_base_addr == 0) {
        return HAL_IOMMU_ERR_NULL_POINTER;
    }
    
    // Check that CD is 64 byte aligned
    if((uint64)cd & 0x3F) {
        return HAL_IOMMU_ERR_INVALID_PARAM;
    }
    
    // Check SID is within MAX
    if(sid >= (2 << strtab_cfg.formatted.LOG2SIZE)) {
        return HAL_IOMMU_ERR_OUT_OF_RANGE;
    }
    
    // Determine STRTAB Configuration
    if(strtab_cfg.formatted.FMT == 0) {
        // Table is Linear
        hal_iommuv3_ste_t *linear_tab = (hal_iommuv3_ste_t *)strtab_base;
        
        // Install CD into STE
        HAL_IOMMUv3_ProgramSTEField(STE_S1ContextPtr, (void *)&linear_tab[sid], (uint64)cd >> 6);
        
        // CMO ? TODO
    }
    else {
        // Table is Split
        uint64 *split_table = (uint64 *)strtab_base;
        uint64 l1_descriptor;
        uint32 sids_per_leaf, index_l1, index_l2;
        hal_iommuv3_ste_t *l2_table;
        
        
        switch(strtab_cfg.formatted.SPLIT) {
            case 10:
                // 64KB leaf tables, 1024 SIDs per table (1024 * 64B)
                sids_per_leaf = 1024;
                break;
            case 8:
                // 16KB leaf tables, 256 SIDs per table (256 * 64B)
                sids_per_leaf = 256;
                break;
            case 6:
            default: // all other values behave as 6
                // 4KB leaf tables, 64 SIDs per table (64 * 64B)
                sids_per_leaf = 64;
                break;
        }
        
        index_l1 = sid / sids_per_leaf;
        index_l2 = sid % sids_per_leaf;
        
        // Get L1 Descriptor
        l1_descriptor = split_table[index_l1];
        // Get L2 table and validate
        l2_table = (hal_iommuv3_ste_t *)(l1_descriptor & ~0x3F);
        
        // Check if descriptor is valid (SPAN != 0)
        if(((l1_descriptor & 0xF) == 0) || !l2_table ) {
            // Descriptor is invalid
            return HAL_IOMMU_ERR_PAGETABLE_NOT_INIT;
        }
        
        // Install CD into STE
        HAL_IOMMUv3_ProgramSTEField(STE_S1ContextPtr, (void *)&l2_table[index_l2], (uint64)cd >> 6);

        // CMO? TODO
    }
    
    // Ensure SMMU can see CD
    SMMU_memory_barrier();
    
    return HAL_IOMMU_ERR_HAL_SUCCESS;
}


