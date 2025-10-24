#ifndef __HAL_IOMMUv3_REG_H__
#define __HAL_IOMMUv3_REG_H__
/*=============================================================================

                       S M M U  H A L  L I B R A R Y

FILE:      HALIOMMUReg.h
   System MMU Hardware Abstraction Layer (HAL)

GENERAL DESCRIPTION
  This file contains data structures needed internall by the HAL IOMMU library

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
 
===============================================================================
Copyright (c) 2010 - 2015
Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/HALIOMMUv3Dxe/HALIOMMUv3Reg.h#1 $
$DateTime: 2022/08/18 10:15:46 $
$Author: pwbldsvc $
$Change: 39147961 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
10/09/10   kcr     Initial Version
=============================================================================*/

/*-----------------------------------------------------------------------------
 * Include Files
 *---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
#include "HALIOMMUTypes.h"

/*-----------------------------------------------------------------------------
 * Definitions
 *---------------------------------------------------------------------------*/
 
#define HAL_IOMMUv3_GLOBAL_PAGE0_OFFSET     0x0     // global page 0
#define HAL_IOMMUv3_GLOBAL_PAGE_SIZE        0x10000 // 64KB

#define HAL_IOMMUv3_NON_SECURE_OFFSET       0x0
#define HAL_IOMMUv3_SECURE_OFFSET           0x8000

#define HAL_IOMMUv3_STE_SIZE                0x40 // 64B
#define HAL_IOMMUv3_CD_SIZE                 0x40 // 64B

/*-----------------------------------------------------------------------------
 * Register Offsets inside the global region 0 
 *---------------------------------------------------------------------------*/
#define HAL_IOMMUv3_IDR0_OFFSET                 0x00000000
#define HAL_IOMMUv3_IDR1_OFFSET                 0x00000004
#define HAL_IOMMUv3_IDR2_OFFSET                 0x00000008
#define HAL_IOMMUv3_IDR3_OFFSET                 0x0000000C
#define HAL_IOMMUv3_IDR4_OFFSET                 0x00000010
#define HAL_IOMMUv3_IDR5_OFFSET                 0x00000014
#define HAL_IOMMUv3_IIDR_OFFSET                 0x00000018
#define HAL_IOMMUv3_AIDR_OFFSET                 0x0000001C
#define HAL_IOMMUv3_CR0_OFFSET                  0x00000020
#define HAL_IOMMUv3_CR0ACK_OFFSET               0x00000024
#define HAL_IOMMUv3_CR1_OFFSET                  0x00000028
#define HAL_IOMMUv3_CR2_OFFSET                  0x0000002C
#define HAL_IOMMUv3_S_INIT_OFFSET               0x0000003C
#define HAL_IOMMUv3_STATUSR_OFFSET              0x00000040
#define HAL_IOMMUv3_GBPA_OFFSET                 0x00000044
#define HAL_IOMMUv3_AGBPA_OFFSET                0x00000048
#define HAL_IOMMUv3_IRQ_CTRL_OFFSET             0x00000050
#define HAL_IOMMUv3_IRQ_CTRLACK_OFFSET          0x00000054
#define HAL_IOMMUv3_GERROR_OFFSET               0x00000060
#define HAL_IOMMUv3_GERRORN_OFFSET              0x00000064
#define HAL_IOMMUv3_GERROR__IRQ_CFG0_OFFSET     0x00000068
#define HAL_IOMMUv3_GERROR__IRQ_CFG1_OFFSET     0x00000070
#define HAL_IOMMUv3_GERROR__IRQ_CFG2_OFFSET     0x00000074
#define HAL_IOMMUv3_STRTAB_BASE_OFFSET          0x00000080
#define HAL_IOMMUv3_STRTAB_BASE_CFG_OFFSET      0x00000088
#define HAL_IOMMUv3_CMDQ_BASE_OFFSET            0x00000090
#define HAL_IOMMUv3_CMDQ_PROD_OFFSET            0x00000098
#define HAL_IOMMUv3_CMDQ_CONS_OFFSET            0x0000009C
#define HAL_IOMMUv3_EVENTQ_BASE_OFFSET          0x000000A0
#define HAL_IOMMUv3_EVENTQ_PROD_OFFSET          0x000100A8
#define HAL_IOMMUv3_EVENTQ_CONS_OFFSET          0x000100AC
#define HAL_IOMMUv3_EVENTQ_IRQ_CFG0_OFFSET      0x000000B0
#define HAL_IOMMUv3_EVENTQ_IRQ_CFG1_OFFSET      0x000000B8
#define HAL_IOMMUv3_EVENTQ_IRQ_CFG2_OFFSET      0x000000BC
#define HAL_IOMMUv3_PRIQ_BASE_OFFSET            0x000000C0
#define HAL_IOMMUv3_PRIQ_PROD_OFFSET            0x000100C8
#define HAL_IOMMUv3_PRIQ_CONS_OFFSET            0x000100CC
#define HAL_IOMMUv3_PRIQ_IRQ_CFG0_OFFSET        0x000000D0
#define HAL_IOMMUv3_PRIQ_IRQ_CFG1_OFFSET        0x000000D8
#define HAL_IOMMUv3_PRIQ_IRQ_CFG2_OFFSET        0x000000DC
#define HAL_IOMMUv3_GATOS_CTRL_OFFSET           0x00000100
#define HAL_IOMMUv3_GATOS_SID_OFFSET            0x00000108
#define HAL_IOMMUv3_GATOS_ADDR_OFFSET           0x00000110
#define HAL_IOMMUv3_GATOS_PAR_OFFSET            0x00000118
#define HAL_IOMMUv3_MPAMIDR_OFFSET              0x00000130
#define HAL_IOMMUv3_GMPAM_OFFSET                0x00000138
#define HAL_IOMMUv3_GBPMPAM_OFFSET              0x0000013C
#define HAL_IOMMUv3_VATOS_SEL_OFFSET            0x00000180

#define GERROR_CMDQ_ERR_MASK                    0x1

#define STE_CONFIG_S1B_S2B                      0x4
#define STE_CONFIG_S1T_S2B                      0x5
#define STE_CONFIG_S1B_S2T                      0x6
#define STE_CONFIG_S1T_S2T                      0x7

#define HAL_IOMMUv3_MAX_SID                     ((1 << 20) - 1) // Only support 19 bits

/*-----------------------------------------------------------------------------
 * Type Declarations (Add more as needed)
 * --------------------------------------------------------------------------*/
 
// Stream Table Entry Fields
typedef enum STE_Field_t {
// S1 Fields + Valid    
    STE_V = 0,
    STE_Config, // 1
    STE_S1_Fmt, // 2
    STE_S1ContextPtr, // 3
    STE_S1CDMax, // 4
    STE_S1_DSS, // 5
    STE_S1_CIR, // 6
    STE_S1_COR,
    STE_S1_CSH,
    STE_S1_S2HWU59,
    STE_S1_S2HWU60,
    STE_S1_S2HWU61,
    STE_S1_S2HWU62,
    STE_DRE,
    STE_CONT,
    STE_DCP,
    STE_PPAR,
    STE_MEV,
    STE_Reserved0,
    STE_S2FWB,
    STE_S1_MPAM,
    STE_S1_STALLD,
    STE_EATS,
    STE_STRW,
    STE_MemAttr,
    STE_MTCFG,
    STE_ALLOCCFG,
    STE_SH_CFG,
    STE_NS_CFG,
    STE_PRIV_CFG,
    STE_INST_CFG,
    STE_ImplDef0,   
// S2 Fields Begin
    STE_S2VMID,
    STE_ImplDef1,
    STE_S2T0SZ,
    STE_S2_SL0,
    STE_S2_IR0,
    STE_S2_OR0,
    STE_S2_SH0,
    STE_S2_TG,
    STE_S2PS,
    STE_S2AA64,
    STE_S2ENDI,
    STE_S2AFFD,
    STE_S2PTW,
    STE_S2HD,
    STE_S2HA,
    STE_S2S,
    STE_S2R,
    STE_S2NSW,
    STE_S2NSA,
    STE_S2TTB,
    STE_ImplDef2,
    STE_PARTID,
    STE_S_S2T0SZ,
    STE_S_S2_SL0,
    STE_S_S2_TG,
    STE_PMG,
    STE_VMSPtr,
    STE_S2SW,
    STE_S2SA,
    STE_S2_S2TTB,
// END Fields
    STE_NUM_FIELDS,
    STE_MAX_FIELD = 0x7FFFFFFF,    
}STE_Field_t;

#define SIZEOF_STE 64
typedef uint32 hal_iommuv3_ste_t[SIZEOF_STE/sizeof(uint32)]; //[16]

// Context Descriptor Fields 
typedef enum CD_Field_t {
    CD_T0SZ = 0,
    CD_TG0,
    CD_IR0,
    CD_OR0,
    CD_SH0,
    CD_EPD0,
    CD_ENDI,
    CD_T1SZ,
    CD_TG1,
    CD_IR1,
    CD_OR1,
    CD_SH1,
    CD_EPD1,
    CD_V,
    CD_IPS,
    CD_AFFD,
    CD_WXN,
    CD_UWXN,
    CD_TBI,
    CD_PAN,
    CD_AA64,
    CD_HD,
    CD_HA,
    CD_S,
    CD_R,
    CD_A,
    CD_ASET,
    CD_ASID,
    CD_NSCFG0,
    CD_HAD0,
    CD_TTB0,
    CD_HWU059,
    CD_HWU060,
    CD_HWU061,
    CD_HWU062,
    CD_NSCFG1,
    CD_HAD1,
    CD_TTB1,
    CD_HWU159,
    CD_HWU160,
    CD_HWU161,
    CD_HWU162,
    CD_MAIR,
    CD_AMAIR,
    CD_ImplDef0,
    CD_PARTID,
    CD_PMG,
// End Fields
    CD_NUM_FIELDS,
    CD_MAX_FIELD = 0x7FFFFFFF,
}CD_Field_t;

#define SIZEOF_CD   64
typedef uint32 hal_iommuv3_cd_t[SIZEOF_CD/sizeof(uint32)]; // [16]

struct hal_iommuv3_field_info_s {
    int index;
    int offset;
    int width;
};

typedef union HAL_IOMMUv3_IDR0_t
{
  struct {
    unsigned S2P:1; // S2 Translation Supported
    unsigned S1P:1; // S1 Translation Supported
    unsigned TTF:2; // Translation Sormat(s) Supported
    unsigned COHACC:1; // CCA supported 
    unsigned BTM:1;
    unsigned HTTU:2;
    unsigned DORMHINT:1;
    unsigned HYPZ:1;
    unsigned ATS:1;
    unsigned NS1ATS:1;
    unsigned ASID16:1;
    unsigned MSI:1;
    unsigned SEV:1;
    unsigned ATOS:1;
    unsigned PRI:1;
    unsigned VMD:1;
    unsigned VMID16:1;
    unsigned CD2L:1;
    unsigned VATOS:1;
    unsigned TTENDIAN:2;
    unsigned Reserved:1;
    unsigned STALL_MODEL:2;
    unsigned TERM_MODEL:1;
    unsigned ST_LEVEL:2;
    unsigned Reserved2:3;
  } formatted;
  unsigned raw;
} HAL_IOMMUv3_IDR0_t;

typedef union HAL_IOMMUv3_CR0_t
{
  struct {
    unsigned SMMUEN:1;
    unsigned PRIQEN:1;
    unsigned EVENTQEN:1;
    unsigned CMDQEN:1;
    unsigned ATSCHK:1;
    unsigned Reserved:1;
    unsigned VMW:3;
    unsigned Reserved2:23;
  } formatted;
  unsigned raw;
} HAL_IOMMUv3_CR0_t;

typedef union HAL_IOMMUv3_CR1_t
{
  struct {
    unsigned QUEUE_IC:2;
    unsigned QUEUE_OC:2;
    unsigned QUEUE_SH:2;
    unsigned TABLE_IC:2;
    unsigned TABLE_OC:2;
    unsigned TABLE_SH:2;
    unsigned Reserved:20;
  } formatted;
  unsigned raw;
} HAL_IOMMUv3_CR1_t;

typedef union HAL_IOMMUv3_CR2_t
{
  struct {
    unsigned E2H:1;
    unsigned RECINVSID:1;
    unsigned PTM:1;
    unsigned Reserved:29;
  } formatted;
  unsigned raw;
} HAL_IOMMUv3_CR2_t;

typedef union HAL_IOMMUv3_GBPA_t
{
  struct {
    unsigned MemAttr:4;
    unsigned MTCFG:1;
    unsigned Reserved:3;
    unsigned ALLOCCFG:4;
    unsigned SHCFG:2;
    unsigned NSCFG:2;
    unsigned PRIVCFG:2;
    unsigned INSTCFG:2;
    unsigned ABORT:1;
    unsigned Reserved2:10;
    unsigned Update:1;
  } formatted;
  unsigned raw;
} HAL_IOMMUv3_GBPA_t;

typedef union HAL_IOMMUv3_IRQ_CTRL_t
{
  struct {
    unsigned GERROR_IRQEN:1;
    unsigned PRIQ_IRQEN:1;
    unsigned EVENTQ_IRQEN:1;
  } formatted;
  unsigned raw;
} HAL_IOMMUv3_IRQ_CTRL_t;

typedef union HAL_IOMMUv3_STRTAB_BASE_CFG_t
{
  struct {
    unsigned LOG2SIZE:6;
    unsigned SPLIT:5;
    unsigned Reserved:5;
    unsigned FMT:2;
    unsigned Reserved2:14;
  } formatted;
  unsigned raw;
} HAL_IOMMUv3_STRTAB_BASE_CFG_t;



/**
* HAL IOMMU API Handle definition
*/

HAL_IOMMUResult_t HAL_IOMMUv3_REG_READ32(uint64 base_addr, int ns, uint32 reg_offset, uint32 *out);
HAL_IOMMUResult_t HAL_IOMMUv3_REG_WRITE32(uint64 base_addr, int ns, uint32 reg_offset, uint32 val);

HAL_IOMMUResult_t HAL_IOMMUv3_REG_READ64(uint64 base_addr, int ns, uint32 reg_offset, uint64 *out);
HAL_IOMMUResult_t HAL_IOMMUv3_REG_WRITE64(uint64 base_addr, int ns, uint32 reg_offset, uint64 val);

/* Global context bank HAL APIs */
HAL_IOMMUResult_t   HAL_IOMMUv3_GetIDR0(uint64 base_addr, int ns, HAL_IOMMUv3_IDR0_t *idr0);
HAL_IOMMUResult_t   HAL_IOMMUv3_SetIDR0(uint64 base_addr, int ns, HAL_IOMMUv3_IDR0_t idr0);
HAL_IOMMUResult_t   HAL_IOMMUv3_GetCR0(uint64 base_addr, int ns, HAL_IOMMUv3_CR0_t *cr0);
HAL_IOMMUResult_t   HAL_IOMMUv3_SetCR0(uint64 base_addr, int ns, HAL_IOMMUv3_CR0_t cr0);
HAL_IOMMUResult_t   HAL_IOMMUv3_GetCR1(uint64 base_addr, int ns, HAL_IOMMUv3_CR1_t *cr1);
HAL_IOMMUResult_t   HAL_IOMMUv3_SetCR1(uint64 base_addr, int ns, HAL_IOMMUv3_CR1_t cr1);
HAL_IOMMUResult_t   HAL_IOMMUv3_GetCR2(uint64 base_addr, int ns, HAL_IOMMUv3_CR2_t *cr2);
HAL_IOMMUResult_t   HAL_IOMMUv3_SetCR2(uint64 base_addr, int ns, HAL_IOMMUv3_CR2_t cr2);
HAL_IOMMUResult_t   HAL_IOMMUv3_GetSTRTABCFG(uint64 base_addr, int ns, HAL_IOMMUv3_STRTAB_BASE_CFG_t *strtab_cfg);
HAL_IOMMUResult_t   HAL_IOMMUv3_SetSTRTABCFG(uint64 base_addr, int ns, HAL_IOMMUv3_STRTAB_BASE_CFG_t strtab_cfg);
HAL_IOMMUResult_t   HAL_IOMMUv3_GetGBPA(uint64 base_addr, int ns, HAL_IOMMUv3_GBPA_t *gbpa);
HAL_IOMMUResult_t   HAL_IOMMUv3_SetGBPA(uint64 base_addr, int ns, HAL_IOMMUv3_GBPA_t gbpa);
HAL_IOMMUResult_t   HAL_IOMMUv3_GetIRQCTRL(uint64 base_addr, int ns, HAL_IOMMUv3_IRQ_CTRL_t *irq_ctrl);
HAL_IOMMUResult_t   HAL_IOMMUv3_SetIRQCTRL(uint64 base_addr, int ns, HAL_IOMMUv3_IRQ_CTRL_t irq_ctrl);

HAL_IOMMUResult_t   HAL_IOMMUv3_ProgramSTEField(STE_Field_t field, void *ste_addr, uint64 val);
HAL_IOMMUResult_t   HAL_IOMMUv3_ProgramSTEFieldInPlace(uint64 smmu_base_addr, int ns, uint32 sid, STE_Field_t field, uint64 val);
HAL_IOMMUResult_t   HAL_IOMMUv3_InstallSTE(uint64 smmu_base_addr, int ns, hal_iommuv3_ste_t *ste, uint32 sid);

HAL_IOMMUResult_t   HAL_IOMMUv3_ProgramCDField(CD_Field_t field, void *cd_addr, uint64 val);
HAL_IOMMUResult_t   HAL_IOMMUv3_InstallCD(uint64 smmu_base_addr, int ns, hal_iommuv3_cd_t *cd, uint32 sid);

/*-----------------------------------------------------------------------------
 * Inline Helper Functions
 *---------------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __HAL_IOMMUv3_REG_H__ */
