#ifndef __HWIO_TME_H__
#define __HWIO_TME_H__
/*
===========================================================================
*/
/**
    @file hwio_tme.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8450 (Waipio) [waipio_v1.0_p3q3r17.2_MTO_POST_SI]
 
    This file contains HWIO register definitions for the following modules:
        FUSE_CONTROLLER_SW_RANGE4


    Generation parameters: 
    { 'filename': 'hwio_tme.h',
      'header': '#include "msmhwiobase.h"',
      'module-filter-exclude': {},
      'module-filter-include': {},
      'modules': ['FUSE_CONTROLLER_SW_RANGE4']}
*/
/*
    ===========================================================================

    Copyright (c) 2021 Qualcomm Technologies, Inc.
    All Rights Reserved.
    Confidential and Proprietary - Qualcomm Technologies, Inc.

    Export of this technology or software is regulated by the U.S. Government.
    Diversion contrary to U.S. law prohibited.

    All ideas, data and information contained in or disclosed by
    this document are confidential and proprietary information of
    Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
    By accepting this material the recipient agrees that this material
    and the information contained therein are held in confidence and in
    trust and will not be used, copied, reproduced in whole or in part,
    nor its contents revealed in any manner to others without the express
    written permission of Qualcomm Technologies, Inc.

    ===========================================================================

    $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Waipio/Library/EUDTargetLib/hwio_fuse.h#1 $
    $DateTime: 2021/04/20 20:32:37 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"


#define TME_HWLAYER_BASE                                                                              (TMESS_BASE + 0x02100000)

#define TME_FUSECONTROLLER_BASE                                                                       (TME_HWLAYER_BASE + 0xC0000)

/*----------------------------------------------------------------------------
 * MODULE: FUSE_CONTROLLER_SW_RANGE4
 *--------------------------------------------------------------------------*/

#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE                                                            (TME_FUSECONTROLLER_BASE            + 0x00008000)
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE                                                       0x1000
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_USED                                                       0xb14

#define HWIO_RESET_JDR_STATUS_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x0)
#define HWIO_RESET_JDR_STATUS_RMSK                                                                           0x3
#define HWIO_RESET_JDR_STATUS_IN                    \
                in_dword(HWIO_RESET_JDR_STATUS_ADDR)
#define HWIO_RESET_JDR_STATUS_INM(m)            \
                in_dword_masked(HWIO_RESET_JDR_STATUS_ADDR, m)
#define HWIO_RESET_JDR_STATUS_FORCE_RESET_BMSK                                                               0x2
#define HWIO_RESET_JDR_STATUS_FORCE_RESET_SHFT                                                                 1
#define HWIO_RESET_JDR_STATUS_DISABLE_SYSTEM_RESET_BMSK                                                      0x1
#define HWIO_RESET_JDR_STATUS_DISABLE_SYSTEM_RESET_SHFT                                                        0

#define HWIO_ATPG_JDR_STATUS_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x4)
#define HWIO_ATPG_JDR_STATUS_RMSK                                                                            0x1
#define HWIO_ATPG_JDR_STATUS_IN                    \
                in_dword(HWIO_ATPG_JDR_STATUS_ADDR)
#define HWIO_ATPG_JDR_STATUS_INM(m)            \
                in_dword_masked(HWIO_ATPG_JDR_STATUS_ADDR, m)
#define HWIO_ATPG_JDR_STATUS_FUSE_SENSE_ATPG_CTL_BMSK                                                        0x1
#define HWIO_ATPG_JDR_STATUS_FUSE_SENSE_ATPG_CTL_SHFT                                                          0

#define HWIO_QFPROM_BLOW_STATUS_ADDR                                                                  (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x8)
#define HWIO_QFPROM_BLOW_STATUS_RMSK                                                                         0x3
#define HWIO_QFPROM_BLOW_STATUS_IN                    \
                in_dword(HWIO_QFPROM_BLOW_STATUS_ADDR)
#define HWIO_QFPROM_BLOW_STATUS_INM(m)            \
                in_dword_masked(HWIO_QFPROM_BLOW_STATUS_ADDR, m)
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_WR_ERR_BMSK                                                           0x2
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_WR_ERR_SHFT                                                             1
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_BUSY_BMSK                                                             0x1
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_BUSY_SHFT                                                               0

#define HWIO_QFPROM_ROM_ERROR_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xc)
#define HWIO_QFPROM_ROM_ERROR_RMSK                                                                           0x1
#define HWIO_QFPROM_ROM_ERROR_IN                    \
                in_dword(HWIO_QFPROM_ROM_ERROR_ADDR)
#define HWIO_QFPROM_ROM_ERROR_INM(m)            \
                in_dword_masked(HWIO_QFPROM_ROM_ERROR_ADDR, m)
#define HWIO_QFPROM_ROM_ERROR_ERROR_BMSK                                                                     0x1
#define HWIO_QFPROM_ROM_ERROR_ERROR_SHFT                                                                       0

#define HWIO_QFPROM_BIST_ERROR0_ADDR                                                                  (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x10)
#define HWIO_QFPROM_BIST_ERROR0_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_BIST_ERROR0_IN                    \
                in_dword(HWIO_QFPROM_BIST_ERROR0_ADDR)
#define HWIO_QFPROM_BIST_ERROR0_INM(m)            \
                in_dword_masked(HWIO_QFPROM_BIST_ERROR0_ADDR, m)
#define HWIO_QFPROM_BIST_ERROR0_ERROR_BMSK                                                            0xffffffff
#define HWIO_QFPROM_BIST_ERROR0_ERROR_SHFT                                                                     0

#define HWIO_QFPROM_BIST_ERROR1_ADDR                                                                  (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x14)
#define HWIO_QFPROM_BIST_ERROR1_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_BIST_ERROR1_IN                    \
                in_dword(HWIO_QFPROM_BIST_ERROR1_ADDR)
#define HWIO_QFPROM_BIST_ERROR1_INM(m)            \
                in_dword_masked(HWIO_QFPROM_BIST_ERROR1_ADDR, m)
#define HWIO_QFPROM_BIST_ERROR1_ERROR_BMSK                                                            0xffffffff
#define HWIO_QFPROM_BIST_ERROR1_ERROR_SHFT                                                                     0

#define HWIO_QFPROM0_MATCH_STATUS_ADDR                                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x18)
#define HWIO_QFPROM0_MATCH_STATUS_RMSK                                                                0xffffffff
#define HWIO_QFPROM0_MATCH_STATUS_IN                    \
                in_dword(HWIO_QFPROM0_MATCH_STATUS_ADDR)
#define HWIO_QFPROM0_MATCH_STATUS_INM(m)            \
                in_dword_masked(HWIO_QFPROM0_MATCH_STATUS_ADDR, m)
#define HWIO_QFPROM0_MATCH_STATUS_FLAG_BMSK                                                           0xffffffff
#define HWIO_QFPROM0_MATCH_STATUS_FLAG_SHFT                                                                    0

#define HWIO_QFPROM1_MATCH_STATUS_ADDR                                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x1c)
#define HWIO_QFPROM1_MATCH_STATUS_RMSK                                                                0xffffffff
#define HWIO_QFPROM1_MATCH_STATUS_IN                    \
                in_dword(HWIO_QFPROM1_MATCH_STATUS_ADDR)
#define HWIO_QFPROM1_MATCH_STATUS_INM(m)            \
                in_dword_masked(HWIO_QFPROM1_MATCH_STATUS_ADDR, m)
#define HWIO_QFPROM1_MATCH_STATUS_FLAG_BMSK                                                           0xffffffff
#define HWIO_QFPROM1_MATCH_STATUS_FLAG_SHFT                                                                    0

#define HWIO_FEC_EAR_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x24)
#define HWIO_FEC_EAR_RMSK                                                                             0xffffffff
#define HWIO_FEC_EAR_IN                    \
                in_dword(HWIO_FEC_EAR_ADDR)
#define HWIO_FEC_EAR_INM(m)            \
                in_dword_masked(HWIO_FEC_EAR_ADDR, m)
#define HWIO_FEC_EAR_CORR_ADDR_BMSK                                                                   0xffff0000
#define HWIO_FEC_EAR_CORR_ADDR_SHFT                                                                           16
#define HWIO_FEC_EAR_ERR_ADDR_BMSK                                                                        0xffff
#define HWIO_FEC_EAR_ERR_ADDR_SHFT                                                                             0

#define HWIO_FEAT_PROV_OUT_n_ADDR(n)                                                                  (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0X30 + (0x4*(n)))
#define HWIO_FEAT_PROV_OUT_n_RMSK                                                                     0xffffffff
#define HWIO_FEAT_PROV_OUT_n_MAXn                                                                              3
#define HWIO_FEAT_PROV_OUT_n_INI(n)                \
                in_dword_masked(HWIO_FEAT_PROV_OUT_n_ADDR(n), HWIO_FEAT_PROV_OUT_n_RMSK)
#define HWIO_FEAT_PROV_OUT_n_INMI(n,mask)        \
                in_dword_masked(HWIO_FEAT_PROV_OUT_n_ADDR(n), mask)
#define HWIO_FEAT_PROV_OUT_n_FEAT_PROV_OUT_VALUE_BMSK                                                 0xffffffff
#define HWIO_FEAT_PROV_OUT_n_FEAT_PROV_OUT_VALUE_SHFT                                                          0

#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_ADDR                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x40)
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_RMSK                                                0xffffffff
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_IN                    \
                in_dword(HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_ADDR)
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_ADDR, m)
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_OEM_SPARE_0_WRITE_DISABLE_BMSK                      0x80000000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_OEM_SPARE_0_WRITE_DISABLE_SHFT                              31
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_MEMORY_CONFIG_WRITE_DISABLE_BMSK                    0x40000000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_MEMORY_CONFIG_WRITE_DISABLE_SHFT                            30
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_CALIBRATION_WRITE_DISABLE_BMSK                      0x20000000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_CALIBRATION_WRITE_DISABLE_SHFT                              29
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_TME_CPU_ROM_PATCH_WRITE_DISABLE_BMSK                0x10000000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_TME_CPU_ROM_PATCH_WRITE_DISABLE_SHFT                        28
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_SOC_ROM_PATCH_WRITE_DISABLE_BMSK                     0x8000000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_SOC_ROM_PATCH_WRITE_DISABLE_SHFT                            27
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_OEM_PRODUCT_SEED_WRITE_DISABLE_BMSK                  0x4000000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_OEM_PRODUCT_SEED_WRITE_DISABLE_SHFT                         26
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_MARC_HASH_WRITE_DISABLE_BMSK                         0x2000000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_MARC_HASH_WRITE_DISABLE_SHFT                                25
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SPARE_4_WRITE_DISABLE_BMSK                        0x1000000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SPARE_4_WRITE_DISABLE_SHFT                               24
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SPARE_3_WRITE_DISABLE_BMSK                         0x800000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SPARE_3_WRITE_DISABLE_SHFT                               23
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SPARE_2_WRITE_DISABLE_BMSK                         0x400000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SPARE_2_WRITE_DISABLE_SHFT                               22
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SPARE_1_WRITE_DISABLE_BMSK                         0x200000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SPARE_1_WRITE_DISABLE_SHFT                               21
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SPARE_0_WRITE_DISABLE_BMSK                         0x100000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SPARE_0_WRITE_DISABLE_SHFT                               20
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_ECC_WRITE_DISABLE_BMSK                              0x80000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_ECC_WRITE_DISABLE_SHFT                                   19
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_TME_SEQUENCER_ROM_PATCH_WRITE_DISABLE_BMSK             0x40000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_TME_SEQUENCER_ROM_PATCH_WRITE_DISABLE_SHFT                  18
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_ANTI_ROLLBACK_WRITE_DISABLE_BMSK                       0x20000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_ANTI_ROLLBACK_WRITE_DISABLE_SHFT                            17
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_CONFIG_WRITE_DISABLE_BMSK                           0x10000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_CONFIG_WRITE_DISABLE_SHFT                                16
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_FEATURE_CONFIG_OVERRIDE_WRITE_DISABLE_BMSK              0x8000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_FEATURE_CONFIG_OVERRIDE_WRITE_DISABLE_SHFT                  15
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_FEATURE_CONFIG_WRITE_DISABLE_BMSK                       0x4000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_FEATURE_CONFIG_WRITE_DISABLE_SHFT                           14
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_OEM_CONFIG_WRITE_DISABLE_BMSK                           0x2000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_OEM_CONFIG_WRITE_DISABLE_SHFT                               13
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_DEBUG_TEST_REENABLE_WRITE_DISABLE_BMSK                  0x1000
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_DEBUG_TEST_REENABLE_WRITE_DISABLE_SHFT                      12
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_DEBUG_DISABLE_WRITE_DISABLE_BMSK                         0x800
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_DEBUG_DISABLE_WRITE_DISABLE_SHFT                            11
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_FUSE_REDUNDANCY_ENABLE_WRITE_DISABLE_BMSK                0x400
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_FUSE_REDUNDANCY_ENABLE_WRITE_DISABLE_SHFT                   10
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_READ_PERMISSIONS_WRITE_DISABLE_BMSK                      0x200
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_READ_PERMISSIONS_WRITE_DISABLE_SHFT                          9
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_WRITE_PERMISSIONS_WRITE_DISABLE_BMSK                     0x100
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_WRITE_PERMISSIONS_WRITE_DISABLE_SHFT                         8
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_PTE_WRITE_DISABLE_BMSK                                    0x80
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_PTE_WRITE_DISABLE_SHFT                                       7
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_OEM_SECURITY_POLICY_WRITE_DISABLE_BMSK                    0x40
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_OEM_SECURITY_POLICY_WRITE_DISABLE_SHFT                       6
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SECURITY_POLICY_WRITE_DISABLE_BMSK                     0x20
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_QC_SECURITY_POLICY_WRITE_DISABLE_SHFT                        5
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_MRC_WRITE_DISABLE_BMSK                                    0x10
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_MRC_WRITE_DISABLE_SHFT                                       4
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_TME_LCS_WRITE_DISABLE_BMSK                                 0x8
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_TME_LCS_WRITE_DISABLE_SHFT                                   3
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_TME_PRIVATE_WRITE_DISABLE_BMSK                             0x4
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_TME_PRIVATE_WRITE_DISABLE_SHFT                               2
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_TME_PCD_WRITE_DISABLE_BMSK                                 0x2
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_TME_PCD_WRITE_DISABLE_SHFT                                   1
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_CM_CORE_PRIVATE_OTP_WRITE_DISABLE_BMSK                     0x1
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_LSW_CM_CORE_PRIVATE_OTP_WRITE_DISABLE_SHFT                       0

#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_ADDR                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x44)
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_RMSK                                                0xffffffff
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_IN                    \
                in_dword(HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_ADDR)
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_ADDR, m)
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_WR_PERM_RSVD_BMSK                                   0xfffffff8
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_WR_PERM_RSVD_SHFT                                            3
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_OEM_SPARE_3_WRITE_DISABLE_BMSK                             0x4
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_OEM_SPARE_3_WRITE_DISABLE_SHFT                               2
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_OEM_SPARE_2_WRITE_DISABLE_BMSK                             0x2
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_OEM_SPARE_2_WRITE_DISABLE_SHFT                               1
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_OEM_SPARE_1_WRITE_DISABLE_BMSK                             0x1
#define HWIO_QFPROM_CONTROLLER_WR_PERMISSIONS_MSW_OEM_SPARE_1_WRITE_DISABLE_SHFT                               0

#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_ADDR                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x48)
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_RMSK                                                0xffffffff
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_IN                    \
                in_dword(HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_ADDR)
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_ADDR, m)
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_OEM_SPARE_0_READ_DISABLE_BMSK                       0x80000000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_OEM_SPARE_0_READ_DISABLE_SHFT                               31
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_MEMORY_CONFIG_READ_DISABLE_BMSK                     0x40000000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_MEMORY_CONFIG_READ_DISABLE_SHFT                             30
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_CALIBRATION_READ_DISABLE_BMSK                       0x20000000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_CALIBRATION_READ_DISABLE_SHFT                               29
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_TME_CPU_ROM_PATCH_READ_DISABLE_BMSK                 0x10000000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_TME_CPU_ROM_PATCH_READ_DISABLE_SHFT                         28
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_SOC_ROM_PATCH_READ_DISABLE_BMSK                      0x8000000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_SOC_ROM_PATCH_READ_DISABLE_SHFT                             27
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_OEM_PRODUCT_SEED_READ_DISABLE_BMSK                   0x4000000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_OEM_PRODUCT_SEED_READ_DISABLE_SHFT                          26
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_MARC_HASH_READ_DISABLE_BMSK                          0x2000000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_MARC_HASH_READ_DISABLE_SHFT                                 25
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SPARE_4_READ_DISABLE_BMSK                         0x1000000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SPARE_4_READ_DISABLE_SHFT                                24
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SPARE_3_READ_DISABLE_BMSK                          0x800000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SPARE_3_READ_DISABLE_SHFT                                23
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SPARE_2_READ_DISABLE_BMSK                          0x400000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SPARE_2_READ_DISABLE_SHFT                                22
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SPARE_1_READ_DISABLE_BMSK                          0x200000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SPARE_1_READ_DISABLE_SHFT                                21
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SPARE_0_READ_DISABLE_BMSK                          0x100000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SPARE_0_READ_DISABLE_SHFT                                20
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_ECC_READ_DISABLE_BMSK                               0x80000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_ECC_READ_DISABLE_SHFT                                    19
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_TME_SEQUENCER_ROM_PATCH_READ_DISABLE_BMSK              0x40000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_TME_SEQUENCER_ROM_PATCH_READ_DISABLE_SHFT                   18
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_ANTI_ROLLBACK_READ_DISABLE_BMSK                        0x20000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_ANTI_ROLLBACK_READ_DISABLE_SHFT                             17
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_CONFIG_READ_DISABLE_BMSK                            0x10000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_CONFIG_READ_DISABLE_SHFT                                 16
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_FEATURE_CONFIG_OVERRIDE_READ_DISABLE_BMSK               0x8000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_FEATURE_CONFIG_OVERRIDE_READ_DISABLE_SHFT                   15
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_FEATURE_CONFIG_READ_DISABLE_BMSK                        0x4000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_FEATURE_CONFIG_READ_DISABLE_SHFT                            14
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_OEM_CONFIG_READ_DISABLE_BMSK                            0x2000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_OEM_CONFIG_READ_DISABLE_SHFT                                13
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_DEBUG_TEST_REENABLE_READ_DISABLE_BMSK                   0x1000
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_DEBUG_TEST_REENABLE_READ_DISABLE_SHFT                       12
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_DEBUG_DISABLE_READ_DISABLE_BMSK                          0x800
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_DEBUG_DISABLE_READ_DISABLE_SHFT                             11
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_FUSE_REDUNDANCY_ENABLE_READ_DISABLE_BMSK                 0x400
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_FUSE_REDUNDANCY_ENABLE_READ_DISABLE_SHFT                    10
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_READ_PERMISSIONS_READ_DISABLE_BMSK                       0x200
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_READ_PERMISSIONS_READ_DISABLE_SHFT                           9
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_WRITE_PERMISSIONS_READ_DISABLE_BMSK                      0x100
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_WRITE_PERMISSIONS_READ_DISABLE_SHFT                          8
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_PTE_READ_DISABLE_BMSK                                     0x80
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_PTE_READ_DISABLE_SHFT                                        7
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_OEM_SECURITY_POLICY_READ_DISABLE_BMSK                     0x40
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_OEM_SECURITY_POLICY_READ_DISABLE_SHFT                        6
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SECURITY_POLICY_READ_DISABLE_BMSK                      0x20
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_QC_SECURITY_POLICY_READ_DISABLE_SHFT                         5
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_MRC_READ_DISABLE_BMSK                                     0x10
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_MRC_READ_DISABLE_SHFT                                        4
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_TME_LCS_READ_DISABLE_BMSK                                  0x8
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_TME_LCS_READ_DISABLE_SHFT                                    3
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_TME_PRIVATE_READ_DISABLE_BMSK                              0x4
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_TME_PRIVATE_READ_DISABLE_SHFT                                2
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_TME_PCD_READ_DISABLE_BMSK                                  0x2
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_TME_PCD_READ_DISABLE_SHFT                                    1
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_CM_CORE_PRIVATE_OTP_READ_DISABLE_BMSK                      0x1
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_LSW_CM_CORE_PRIVATE_OTP_READ_DISABLE_SHFT                        0

#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_ADDR                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x4c)
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_RMSK                                                0xffffffff
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_IN                    \
                in_dword(HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_ADDR)
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_ADDR, m)
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_RD_PERM_RSVD_BMSK                                   0xfffffff8
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_RD_PERM_RSVD_SHFT                                            3
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_OEM_SPARE_3_READ_DISABLE_BMSK                              0x4
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_OEM_SPARE_3_READ_DISABLE_SHFT                                2
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_OEM_SPARE_2_READ_DISABLE_BMSK                              0x2
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_OEM_SPARE_2_READ_DISABLE_SHFT                                1
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_OEM_SPARE_1_READ_DISABLE_BMSK                              0x1
#define HWIO_QFPROM_CONTROLLER_RD_PERMISSIONS_MSW_OEM_SPARE_1_READ_DISABLE_SHFT                                0

#define HWIO_FUSE_REDUNDANCY_ENABLE0_ADDR                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x50)
#define HWIO_FUSE_REDUNDANCY_ENABLE0_RMSK                                                             0xffffffff
#define HWIO_FUSE_REDUNDANCY_ENABLE0_IN                    \
                in_dword(HWIO_FUSE_REDUNDANCY_ENABLE0_ADDR)
#define HWIO_FUSE_REDUNDANCY_ENABLE0_INM(m)            \
                in_dword_masked(HWIO_FUSE_REDUNDANCY_ENABLE0_ADDR, m)
#define HWIO_FUSE_REDUNDANCY_ENABLE0_REDUN_EN_RSVD_31_BMSK                                            0x80000000
#define HWIO_FUSE_REDUNDANCY_ENABLE0_REDUN_EN_RSVD_31_SHFT                                                    31
#define HWIO_FUSE_REDUNDANCY_ENABLE0_MEMORY_CONFIG_ECC_ENABLE_BMSK                                    0x40000000
#define HWIO_FUSE_REDUNDANCY_ENABLE0_MEMORY_CONFIG_ECC_ENABLE_SHFT                                            30
#define HWIO_FUSE_REDUNDANCY_ENABLE0_CALIBRATION_ECC_ENABLE_BMSK                                      0x20000000
#define HWIO_FUSE_REDUNDANCY_ENABLE0_CALIBRATION_ECC_ENABLE_SHFT                                              29
#define HWIO_FUSE_REDUNDANCY_ENABLE0_TME_CPU_ROM_PATCH_FEC_ENABLE_BMSK                                0x10000000
#define HWIO_FUSE_REDUNDANCY_ENABLE0_TME_CPU_ROM_PATCH_FEC_ENABLE_SHFT                                        28
#define HWIO_FUSE_REDUNDANCY_ENABLE0_SOC_ROM_PATCH_FEC_ENABLE_BMSK                                     0x8000000
#define HWIO_FUSE_REDUNDANCY_ENABLE0_SOC_ROM_PATCH_FEC_ENABLE_SHFT                                            27
#define HWIO_FUSE_REDUNDANCY_ENABLE0_OEM_PRODUCT_SEED_FEC_ENABLE_BMSK                                  0x4000000
#define HWIO_FUSE_REDUNDANCY_ENABLE0_OEM_PRODUCT_SEED_FEC_ENABLE_SHFT                                         26
#define HWIO_FUSE_REDUNDANCY_ENABLE0_MRC_HASH_FEC_ENABLE_BMSK                                          0x2000000
#define HWIO_FUSE_REDUNDANCY_ENABLE0_MRC_HASH_FEC_ENABLE_SHFT                                                 25
#define HWIO_FUSE_REDUNDANCY_ENABLE0_REDUN_EN_RSVD_BMSK                                                0x1ffffff
#define HWIO_FUSE_REDUNDANCY_ENABLE0_REDUN_EN_RSVD_SHFT                                                        0

#define HWIO_FUSE_REDUNDANCY_ENABLE1_ADDR                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x54)
#define HWIO_FUSE_REDUNDANCY_ENABLE1_RMSK                                                             0xffffffff
#define HWIO_FUSE_REDUNDANCY_ENABLE1_IN                    \
                in_dword(HWIO_FUSE_REDUNDANCY_ENABLE1_ADDR)
#define HWIO_FUSE_REDUNDANCY_ENABLE1_INM(m)            \
                in_dword_masked(HWIO_FUSE_REDUNDANCY_ENABLE1_ADDR, m)
#define HWIO_FUSE_REDUNDANCY_ENABLE1_REDUN_EN_RSVD_63_32_BMSK                                         0xffffffff
#define HWIO_FUSE_REDUNDANCY_ENABLE1_REDUN_EN_RSVD_63_32_SHFT                                                  0

#define HWIO_QC_SECURITY_POLICY0_ADDR                                                                 (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x60)
#define HWIO_QC_SECURITY_POLICY0_RMSK                                                                 0xffffffff
#define HWIO_QC_SECURITY_POLICY0_IN                    \
                in_dword(HWIO_QC_SECURITY_POLICY0_ADDR)
#define HWIO_QC_SECURITY_POLICY0_INM(m)            \
                in_dword_masked(HWIO_QC_SECURITY_POLICY0_ADDR, m)
#define HWIO_QC_SECURITY_POLICY0_QC_SEC_POL_RSVD_31_4_BMSK                                            0xfffffff0
#define HWIO_QC_SECURITY_POLICY0_QC_SEC_POL_RSVD_31_4_SHFT                                                     4
#define HWIO_QC_SECURITY_POLICY0_QCSECURITYPOLICY_BMSK                                                       0xf
#define HWIO_QC_SECURITY_POLICY0_QCSECURITYPOLICY_SHFT                                                         0

#define HWIO_QC_SECURITY_POLICY1_ADDR                                                                 (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x64)
#define HWIO_QC_SECURITY_POLICY1_RMSK                                                                 0xffffffff
#define HWIO_QC_SECURITY_POLICY1_IN                    \
                in_dword(HWIO_QC_SECURITY_POLICY1_ADDR)
#define HWIO_QC_SECURITY_POLICY1_INM(m)            \
                in_dword_masked(HWIO_QC_SECURITY_POLICY1_ADDR, m)
#define HWIO_QC_SECURITY_POLICY1_QC_SEC_POL_RSVD_61_32_BMSK                                           0xfffffffc
#define HWIO_QC_SECURITY_POLICY1_QC_SEC_POL_RSVD_61_32_SHFT                                                    2
#define HWIO_QC_SECURITY_POLICY1_SEQUENCERROMBYPASSIMGVERIFYDISABLE_BMSK                                     0x2
#define HWIO_QC_SECURITY_POLICY1_SEQUENCERROMBYPASSIMGVERIFYDISABLE_SHFT                                       1
#define HWIO_QC_SECURITY_POLICY1_QC_SEC_POL_RSVD_32_BMSK                                                     0x1
#define HWIO_QC_SECURITY_POLICY1_QC_SEC_POL_RSVD_32_SHFT                                                       0

#define HWIO_DEBUG_DISABLE0_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x70)
#define HWIO_DEBUG_DISABLE0_RMSK                                                                      0xffffffff
#define HWIO_DEBUG_DISABLE0_IN                    \
                in_dword(HWIO_DEBUG_DISABLE0_ADDR)
#define HWIO_DEBUG_DISABLE0_INM(m)            \
                in_dword_masked(HWIO_DEBUG_DISABLE0_ADDR, m)
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_31_BMSK                                                          0x80000000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_31_SHFT                                                                  31
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_30_BMSK                                                          0x40000000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_30_SHFT                                                                  30
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_29_BMSK                                                          0x20000000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_29_SHFT                                                                  29
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_28_BMSK                                                          0x10000000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_28_SHFT                                                                  28
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_27_BMSK                                                           0x8000000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_27_SHFT                                                                  27
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_26_BMSK                                                           0x4000000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_26_SHFT                                                                  26
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_25_BMSK                                                           0x2000000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_25_SHFT                                                                  25
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_24_BMSK                                                           0x1000000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_24_SHFT                                                                  24
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_23_BMSK                                                            0x800000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_23_SHFT                                                                  23
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_22_BMSK                                                            0x400000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_22_SHFT                                                                  22
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_21_BMSK                                                            0x200000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_21_SHFT                                                                  21
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_20_BMSK                                                            0x100000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_20_SHFT                                                                  20
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_19_BMSK                                                             0x80000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_19_SHFT                                                                  19
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_18_BMSK                                                             0x40000
#define HWIO_DEBUG_DISABLE0_DBG_RSVD_18_SHFT                                                                  18
#define HWIO_DEBUG_DISABLE0_GPU_PRIVATE_DBGEN_DISABLE_BMSK                                               0x20000
#define HWIO_DEBUG_DISABLE0_GPU_PRIVATE_DBGEN_DISABLE_SHFT                                                    17
#define HWIO_DEBUG_DISABLE0_APB2JTAG_DISABLE_BMSK                                                        0x10000
#define HWIO_DEBUG_DISABLE0_APB2JTAG_DISABLE_SHFT                                                             16
#define HWIO_DEBUG_DISABLE0_PIMEM_NIDEN_DISABLE_BMSK                                                      0x8000
#define HWIO_DEBUG_DISABLE0_PIMEM_NIDEN_DISABLE_SHFT                                                          15
#define HWIO_DEBUG_DISABLE0_PIMEM_DBGEN_DISABLE_BMSK                                                      0x4000
#define HWIO_DEBUG_DISABLE0_PIMEM_DBGEN_DISABLE_SHFT                                                          14
#define HWIO_DEBUG_DISABLE0_QSEE_NIDEN_DISABLE_BMSK                                                       0x2000
#define HWIO_DEBUG_DISABLE0_QSEE_NIDEN_DISABLE_SHFT                                                           13
#define HWIO_DEBUG_DISABLE0_QSEE_DBGEN_DISABLE_BMSK                                                       0x1000
#define HWIO_DEBUG_DISABLE0_QSEE_DBGEN_DISABLE_SHFT                                                           12
#define HWIO_DEBUG_DISABLE0_MSS_VECTOR_NIDEN_DISABLE_BMSK                                                  0x800
#define HWIO_DEBUG_DISABLE0_MSS_VECTOR_NIDEN_DISABLE_SHFT                                                     11
#define HWIO_DEBUG_DISABLE0_MSS_VECTOR_DBGEN_DISABLE_BMSK                                                  0x400
#define HWIO_DEBUG_DISABLE0_MSS_VECTOR_DBGEN_DISABLE_SHFT                                                     10
#define HWIO_DEBUG_DISABLE0_CPUCP_NIDEN_DISABLE_BMSK                                                       0x200
#define HWIO_DEBUG_DISABLE0_CPUCP_NIDEN_DISABLE_SHFT                                                           9
#define HWIO_DEBUG_DISABLE0_CPUCP_DBGEN_DISABLE_BMSK                                                       0x100
#define HWIO_DEBUG_DISABLE0_CPUCP_DBGEN_DISABLE_SHFT                                                           8
#define HWIO_DEBUG_DISABLE0_SHRM_NIDEN_DISABLE_BMSK                                                         0x80
#define HWIO_DEBUG_DISABLE0_SHRM_NIDEN_DISABLE_SHFT                                                            7
#define HWIO_DEBUG_DISABLE0_SHRM_DBGEN_DISABLE_BMSK                                                         0x40
#define HWIO_DEBUG_DISABLE0_SHRM_DBGEN_DISABLE_SHFT                                                            6
#define HWIO_DEBUG_DISABLE0_AOP_NIDEN_DISABLE_BMSK                                                          0x20
#define HWIO_DEBUG_DISABLE0_AOP_NIDEN_DISABLE_SHFT                                                             5
#define HWIO_DEBUG_DISABLE0_AOP_DBGEN_DISABLE_BMSK                                                          0x10
#define HWIO_DEBUG_DISABLE0_AOP_DBGEN_DISABLE_SHFT                                                             4
#define HWIO_DEBUG_DISABLE0_TMERAM_NIDEN_DISABLE_BMSK                                                        0x8
#define HWIO_DEBUG_DISABLE0_TMERAM_NIDEN_DISABLE_SHFT                                                          3
#define HWIO_DEBUG_DISABLE0_TMERAM_DBGEN_DISABLE_BMSK                                                        0x4
#define HWIO_DEBUG_DISABLE0_TMERAM_DBGEN_DISABLE_SHFT                                                          2
#define HWIO_DEBUG_DISABLE0_TMEROM_NIDEN_DISABLE_BMSK                                                        0x2
#define HWIO_DEBUG_DISABLE0_TMEROM_NIDEN_DISABLE_SHFT                                                          1
#define HWIO_DEBUG_DISABLE0_TMEROM_DBGEN_DISABLE_BMSK                                                        0x1
#define HWIO_DEBUG_DISABLE0_TMEROM_DBGEN_DISABLE_SHFT                                                          0

#define HWIO_DEBUG_DISABLE1_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x74)
#define HWIO_DEBUG_DISABLE1_RMSK                                                                      0xffffffff
#define HWIO_DEBUG_DISABLE1_IN                    \
                in_dword(HWIO_DEBUG_DISABLE1_ADDR)
#define HWIO_DEBUG_DISABLE1_INM(m)            \
                in_dword_masked(HWIO_DEBUG_DISABLE1_ADDR, m)
#define HWIO_DEBUG_DISABLE1_MASTER_DEBUG_FUSE_DISABLE_BMSK                                            0x80000000
#define HWIO_DEBUG_DISABLE1_MASTER_DEBUG_FUSE_DISABLE_SHFT                                                    31
#define HWIO_DEBUG_DISABLE1_DBG_RSVD_62_BMSK                                                          0x40000000
#define HWIO_DEBUG_DISABLE1_DBG_RSVD_62_SHFT                                                                  30
#define HWIO_DEBUG_DISABLE1_DBG_RSVD_61_BMSK                                                          0x20000000
#define HWIO_DEBUG_DISABLE1_DBG_RSVD_61_SHFT                                                                  29
#define HWIO_DEBUG_DISABLE1_DBG_RSVD_60_BMSK                                                          0x10000000
#define HWIO_DEBUG_DISABLE1_DBG_RSVD_60_SHFT                                                                  28
#define HWIO_DEBUG_DISABLE1_SMMU_SCANDUMP_DISABLE_BMSK                                                 0x8000000
#define HWIO_DEBUG_DISABLE1_SMMU_SCANDUMP_DISABLE_SHFT                                                        27
#define HWIO_DEBUG_DISABLE1_EUD_DISABLE_BMSK                                                           0x4000000
#define HWIO_DEBUG_DISABLE1_EUD_DISABLE_SHFT                                                                  26
#define HWIO_DEBUG_DISABLE1_DCC_DISABLE_BMSK                                                           0x2000000
#define HWIO_DEBUG_DISABLE1_DCC_DISABLE_SHFT                                                                  25
#define HWIO_DEBUG_DISABLE1_DEBUGBUS_DISABLE_BMSK                                                      0x1000000
#define HWIO_DEBUG_DISABLE1_DEBUGBUS_DISABLE_SHFT                                                             24
#define HWIO_DEBUG_DISABLE1_DDRSS_SCANDUMP_DISABLE_BMSK                                                 0x800000
#define HWIO_DEBUG_DISABLE1_DDRSS_SCANDUMP_DISABLE_SHFT                                                       23
#define HWIO_DEBUG_DISABLE1_APPS_SCANDUMP_DISABLE_BMSK                                                  0x400000
#define HWIO_DEBUG_DISABLE1_APPS_SCANDUMP_DISABLE_SHFT                                                        22
#define HWIO_DEBUG_DISABLE1_DAP_NIDEN_DISABLE_BMSK                                                      0x200000
#define HWIO_DEBUG_DISABLE1_DAP_NIDEN_DISABLE_SHFT                                                            21
#define HWIO_DEBUG_DISABLE1_DAP_DBGEN_DISABLE_BMSK                                                      0x100000
#define HWIO_DEBUG_DISABLE1_DAP_DBGEN_DISABLE_SHFT                                                            20
#define HWIO_DEBUG_DISABLE1_GPU_NIDEN_DISABLE_BMSK                                                       0x80000
#define HWIO_DEBUG_DISABLE1_GPU_NIDEN_DISABLE_SHFT                                                            19
#define HWIO_DEBUG_DISABLE1_GPU_DBGEN_DISABLE_BMSK                                                       0x40000
#define HWIO_DEBUG_DISABLE1_GPU_DBGEN_DISABLE_SHFT                                                            18
#define HWIO_DEBUG_DISABLE1_DDRSS_NIDEN_DISABLE_BMSK                                                     0x20000
#define HWIO_DEBUG_DISABLE1_DDRSS_NIDEN_DISABLE_SHFT                                                          17
#define HWIO_DEBUG_DISABLE1_DDRSS_DBGEN_DISABLE_BMSK                                                     0x10000
#define HWIO_DEBUG_DISABLE1_DDRSS_DBGEN_DISABLE_SHFT                                                          16
#define HWIO_DEBUG_DISABLE1_MDSS_NIDEN_DISABLE_BMSK                                                       0x8000
#define HWIO_DEBUG_DISABLE1_MDSS_NIDEN_DISABLE_SHFT                                                           15
#define HWIO_DEBUG_DISABLE1_MDSS_DBGEN_DISABLE_BMSK                                                       0x4000
#define HWIO_DEBUG_DISABLE1_MDSS_DBGEN_DISABLE_SHFT                                                           14
#define HWIO_DEBUG_DISABLE1_IRIS_NIDEN_DISABLE_BMSK                                                       0x2000
#define HWIO_DEBUG_DISABLE1_IRIS_NIDEN_DISABLE_SHFT                                                           13
#define HWIO_DEBUG_DISABLE1_IRIS_DBGEN_DISABLE_BMSK                                                       0x1000
#define HWIO_DEBUG_DISABLE1_IRIS_DBGEN_DISABLE_SHFT                                                           12
#define HWIO_DEBUG_DISABLE1_TURING_NIDEN_DISABLE_BMSK                                                      0x800
#define HWIO_DEBUG_DISABLE1_TURING_NIDEN_DISABLE_SHFT                                                         11
#define HWIO_DEBUG_DISABLE1_TURING_DBGEN_DISABLE_BMSK                                                      0x400
#define HWIO_DEBUG_DISABLE1_TURING_DBGEN_DISABLE_SHFT                                                         10
#define HWIO_DEBUG_DISABLE1_LPASS_NIDEN_DISABLE_BMSK                                                       0x200
#define HWIO_DEBUG_DISABLE1_LPASS_NIDEN_DISABLE_SHFT                                                           9
#define HWIO_DEBUG_DISABLE1_LPASS_DBGEN_DISABLE_BMSK                                                       0x100
#define HWIO_DEBUG_DISABLE1_LPASS_DBGEN_DISABLE_SHFT                                                           8
#define HWIO_DEBUG_DISABLE1_TITAN_NIDEN_DISABLE_BMSK                                                        0x80
#define HWIO_DEBUG_DISABLE1_TITAN_NIDEN_DISABLE_SHFT                                                           7
#define HWIO_DEBUG_DISABLE1_TITAN_DBGEN_DISABLE_BMSK                                                        0x40
#define HWIO_DEBUG_DISABLE1_TITAN_DBGEN_DISABLE_SHFT                                                           6
#define HWIO_DEBUG_DISABLE1_SSC_NIDEN_DISABLE_BMSK                                                          0x20
#define HWIO_DEBUG_DISABLE1_SSC_NIDEN_DISABLE_SHFT                                                             5
#define HWIO_DEBUG_DISABLE1_SSC_DBGEN_DISABLE_BMSK                                                          0x10
#define HWIO_DEBUG_DISABLE1_SSC_DBGEN_DISABLE_SHFT                                                             4
#define HWIO_DEBUG_DISABLE1_MSS_SCALAR_NIDEN_DISABLE_BMSK                                                    0x8
#define HWIO_DEBUG_DISABLE1_MSS_SCALAR_NIDEN_DISABLE_SHFT                                                      3
#define HWIO_DEBUG_DISABLE1_MSS_SCALAR_DBGEN_DISABLE_BMSK                                                    0x4
#define HWIO_DEBUG_DISABLE1_MSS_SCALAR_DBGEN_DISABLE_SHFT                                                      2
#define HWIO_DEBUG_DISABLE1_APPS_NIDEN_DISABLE_BMSK                                                          0x2
#define HWIO_DEBUG_DISABLE1_APPS_NIDEN_DISABLE_SHFT                                                            1
#define HWIO_DEBUG_DISABLE1_APPS_DBGEN_DISABLE_BMSK                                                          0x1
#define HWIO_DEBUG_DISABLE1_APPS_DBGEN_DISABLE_SHFT                                                            0

#define HWIO_DEBUG_TEST_REENABLE0_ADDR                                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x80)
#define HWIO_DEBUG_TEST_REENABLE0_RMSK                                                                0xffffffff
#define HWIO_DEBUG_TEST_REENABLE0_IN                    \
                in_dword(HWIO_DEBUG_TEST_REENABLE0_ADDR)
#define HWIO_DEBUG_TEST_REENABLE0_INM(m)            \
                in_dword_masked(HWIO_DEBUG_TEST_REENABLE0_ADDR, m)
#define HWIO_DEBUG_TEST_REENABLE0_DEBUG_TEST_REENABLE_31_0_BMSK                                       0xffffffff
#define HWIO_DEBUG_TEST_REENABLE0_DEBUG_TEST_REENABLE_31_0_SHFT                                                0

#define HWIO_DEBUG_TEST_REENABLE1_ADDR                                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x84)
#define HWIO_DEBUG_TEST_REENABLE1_RMSK                                                                0xffffffff
#define HWIO_DEBUG_TEST_REENABLE1_IN                    \
                in_dword(HWIO_DEBUG_TEST_REENABLE1_ADDR)
#define HWIO_DEBUG_TEST_REENABLE1_INM(m)            \
                in_dword_masked(HWIO_DEBUG_TEST_REENABLE1_ADDR, m)
#define HWIO_DEBUG_TEST_REENABLE1_DEBUG_TEST_REENABLE_63_32_BMSK                                      0xffffffff
#define HWIO_DEBUG_TEST_REENABLE1_DEBUG_TEST_REENABLE_63_32_SHFT                                               0

#define HWIO_DEBUG_TEST_REENABLE2_ADDR                                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x88)
#define HWIO_DEBUG_TEST_REENABLE2_RMSK                                                                0xffffffff
#define HWIO_DEBUG_TEST_REENABLE2_IN                    \
                in_dword(HWIO_DEBUG_TEST_REENABLE2_ADDR)
#define HWIO_DEBUG_TEST_REENABLE2_INM(m)            \
                in_dword_masked(HWIO_DEBUG_TEST_REENABLE2_ADDR, m)
#define HWIO_DEBUG_TEST_REENABLE2_DEBUG_TEST_REENABLE_95_64_BMSK                                      0xffffffff
#define HWIO_DEBUG_TEST_REENABLE2_DEBUG_TEST_REENABLE_95_64_SHFT                                               0

#define HWIO_DEBUG_TEST_REENABLE3_ADDR                                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x8c)
#define HWIO_DEBUG_TEST_REENABLE3_RMSK                                                                0xffffffff
#define HWIO_DEBUG_TEST_REENABLE3_IN                    \
                in_dword(HWIO_DEBUG_TEST_REENABLE3_ADDR)
#define HWIO_DEBUG_TEST_REENABLE3_INM(m)            \
                in_dword_masked(HWIO_DEBUG_TEST_REENABLE3_ADDR, m)
#define HWIO_DEBUG_TEST_REENABLE3_DEBUG_TEST_REENABLE_127_96_BMSK                                     0xffffffff
#define HWIO_DEBUG_TEST_REENABLE3_DEBUG_TEST_REENABLE_127_96_SHFT                                              0

#define HWIO_FEATURE_CONFIG0_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x100)
#define HWIO_FEATURE_CONFIG0_RMSK                                                                     0xffffffff
#define HWIO_FEATURE_CONFIG0_IN                    \
                in_dword(HWIO_FEATURE_CONFIG0_ADDR)
#define HWIO_FEATURE_CONFIG0_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG0_ADDR, m)
#define HWIO_FEATURE_CONFIG0_MODEM_FEATURE_DISABLE_HARD_23_0_BMSK                                     0xffffff00
#define HWIO_FEATURE_CONFIG0_MODEM_FEATURE_DISABLE_HARD_23_0_SHFT                                              8
#define HWIO_FEATURE_CONFIG0_MODEM_FEATURE_DISABLE_SPARE_7_0_BMSK                                           0xff
#define HWIO_FEATURE_CONFIG0_MODEM_FEATURE_DISABLE_SPARE_7_0_SHFT                                              0

#define HWIO_FEATURE_CONFIG1_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x104)
#define HWIO_FEATURE_CONFIG1_RMSK                                                                     0xffffffff
#define HWIO_FEATURE_CONFIG1_IN                    \
                in_dword(HWIO_FEATURE_CONFIG1_ADDR)
#define HWIO_FEATURE_CONFIG1_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG1_ADDR, m)
#define HWIO_FEATURE_CONFIG1_MODEM_FEATURE_DISABLE_SOFT_1_23_0_BMSK                                   0xffffff00
#define HWIO_FEATURE_CONFIG1_MODEM_FEATURE_DISABLE_SOFT_1_23_0_SHFT                                            8
#define HWIO_FEATURE_CONFIG1_MODEM_FEATURE_DISABLE_HARD_31_24_BMSK                                          0xff
#define HWIO_FEATURE_CONFIG1_MODEM_FEATURE_DISABLE_HARD_31_24_SHFT                                             0

#define HWIO_FEATURE_CONFIG2_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x108)
#define HWIO_FEATURE_CONFIG2_RMSK                                                                     0xffffffff
#define HWIO_FEATURE_CONFIG2_IN                    \
                in_dword(HWIO_FEATURE_CONFIG2_ADDR)
#define HWIO_FEATURE_CONFIG2_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG2_ADDR, m)
#define HWIO_FEATURE_CONFIG2_MODEM_FEATURE_DISABLE_SOFT_2_23_0_BMSK                                   0xffffff00
#define HWIO_FEATURE_CONFIG2_MODEM_FEATURE_DISABLE_SOFT_2_23_0_SHFT                                            8
#define HWIO_FEATURE_CONFIG2_MODEM_FEATURE_DISABLE_SOFT_1_31_24_BMSK                                        0xff
#define HWIO_FEATURE_CONFIG2_MODEM_FEATURE_DISABLE_SOFT_1_31_24_SHFT                                           0

#define HWIO_FEATURE_CONFIG3_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x10c)
#define HWIO_FEATURE_CONFIG3_RMSK                                                                     0xffffffff
#define HWIO_FEATURE_CONFIG3_IN                    \
                in_dword(HWIO_FEATURE_CONFIG3_ADDR)
#define HWIO_FEATURE_CONFIG3_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG3_ADDR, m)
#define HWIO_FEATURE_CONFIG3_MODEM_FEATURE_DISABLE_SOFT_3_23_0_BMSK                                   0xffffff00
#define HWIO_FEATURE_CONFIG3_MODEM_FEATURE_DISABLE_SOFT_3_23_0_SHFT                                            8
#define HWIO_FEATURE_CONFIG3_MODEM_FEATURE_DISABLE_SOFT_2_31_24_BMSK                                        0xff
#define HWIO_FEATURE_CONFIG3_MODEM_FEATURE_DISABLE_SOFT_2_31_24_SHFT                                           0

#define HWIO_FEATURE_CONFIG4_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x110)
#define HWIO_FEATURE_CONFIG4_RMSK                                                                     0xffffffff
#define HWIO_FEATURE_CONFIG4_IN                    \
                in_dword(HWIO_FEATURE_CONFIG4_ADDR)
#define HWIO_FEATURE_CONFIG4_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG4_ADDR, m)
#define HWIO_FEATURE_CONFIG4_MODEM_FEATURE_DISABLE_SOFT_4_23_0_BMSK                                   0xffffff00
#define HWIO_FEATURE_CONFIG4_MODEM_FEATURE_DISABLE_SOFT_4_23_0_SHFT                                            8
#define HWIO_FEATURE_CONFIG4_MODEM_FEATURE_DISABLE_SOFT_3_31_24_BMSK                                        0xff
#define HWIO_FEATURE_CONFIG4_MODEM_FEATURE_DISABLE_SOFT_3_31_24_SHFT                                           0

#define HWIO_FEATURE_CONFIG5_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x114)
#define HWIO_FEATURE_CONFIG5_RMSK                                                                     0xffffffff
#define HWIO_FEATURE_CONFIG5_IN                    \
                in_dword(HWIO_FEATURE_CONFIG5_ADDR)
#define HWIO_FEATURE_CONFIG5_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG5_ADDR, m)
#define HWIO_FEATURE_CONFIG5_FEATURE_CONFIG_191_187_BMSK                                              0xf8000000
#define HWIO_FEATURE_CONFIG5_FEATURE_CONFIG_191_187_SHFT                                                      27
#define HWIO_FEATURE_CONFIG5_LPASS_Q6SS_TCM_BOOT_DISABLE_BMSK                                          0x4000000
#define HWIO_FEATURE_CONFIG5_LPASS_Q6SS_TCM_BOOT_DISABLE_SHFT                                                 26
#define HWIO_FEATURE_CONFIG5_FEATURE_CONFIG_BMSK                                                       0x3800000
#define HWIO_FEATURE_CONFIG5_FEATURE_CONFIG_SHFT                                                              23
#define HWIO_FEATURE_CONFIG5_SPR_DISABLE_BMSK                                                           0x400000
#define HWIO_FEATURE_CONFIG5_SPR_DISABLE_SHFT                                                                 22
#define HWIO_FEATURE_CONFIG5_DEMURA_DISABLE_BMSK                                                        0x200000
#define HWIO_FEATURE_CONFIG5_DEMURA_DISABLE_SHFT                                                              21
#define HWIO_FEATURE_CONFIG5_MST_DISABLE_BMSK                                                           0x100000
#define HWIO_FEATURE_CONFIG5_MST_DISABLE_SHFT                                                                 20
#define HWIO_FEATURE_CONFIG5_Q_CONFIG_FUSE_BMSK                                                          0x80000
#define HWIO_FEATURE_CONFIG5_Q_CONFIG_FUSE_SHFT                                                               19
#define HWIO_FEATURE_CONFIG5_DTPX0_EFUSE_DISABLE_BMSK                                                    0x40000
#define HWIO_FEATURE_CONFIG5_DTPX0_EFUSE_DISABLE_SHFT                                                         18
#define HWIO_FEATURE_CONFIG5_GC_SPLIT_DISABLE_BMSK                                                       0x20000
#define HWIO_FEATURE_CONFIG5_GC_SPLIT_DISABLE_SHFT                                                            17
#define HWIO_FEATURE_CONFIG5_DSI_1_DISABLE_BMSK                                                          0x10000
#define HWIO_FEATURE_CONFIG5_DSI_1_DISABLE_SHFT                                                               16
#define HWIO_FEATURE_CONFIG5_DSI_0_DISABLE_BMSK                                                           0x8000
#define HWIO_FEATURE_CONFIG5_DSI_0_DISABLE_SHFT                                                               15
#define HWIO_FEATURE_CONFIG5_MDP_EFUSE_LTC_DISABLE_BMSK                                                   0x4000
#define HWIO_FEATURE_CONFIG5_MDP_EFUSE_LTC_DISABLE_SHFT                                                       14
#define HWIO_FEATURE_CONFIG5_HDCP_DISABLE_BMSK                                                            0x2000
#define HWIO_FEATURE_CONFIG5_HDCP_DISABLE_SHFT                                                                13
#define HWIO_FEATURE_CONFIG5_MDSS_RESOLUTION_LIMIT_BMSK                                                   0x1800
#define HWIO_FEATURE_CONFIG5_MDSS_RESOLUTION_LIMIT_SHFT                                                       11
#define HWIO_FEATURE_CONFIG5_MSMC_NAV_EN_BMSK                                                              0x400
#define HWIO_FEATURE_CONFIG5_MSMC_NAV_EN_SHFT                                                                 10
#define HWIO_FEATURE_CONFIG5_MODEM_NO_MSA_BOOT_BMSK                                                        0x200
#define HWIO_FEATURE_CONFIG5_MODEM_NO_MSA_BOOT_SHFT                                                            9
#define HWIO_FEATURE_CONFIG5_MODEM_TCM_BOOT_DISABLE_BMSK                                                   0x100
#define HWIO_FEATURE_CONFIG5_MODEM_TCM_BOOT_DISABLE_SHFT                                                       8
#define HWIO_FEATURE_CONFIG5_MODEM_FEATURE_DISABLE_SOFT_4_31_24_BMSK                                        0xff
#define HWIO_FEATURE_CONFIG5_MODEM_FEATURE_DISABLE_SOFT_4_31_24_SHFT                                           0

#define HWIO_FEATURE_CONFIG6_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x118)
#define HWIO_FEATURE_CONFIG6_RMSK                                                                     0xffffffff
#define HWIO_FEATURE_CONFIG6_IN                    \
                in_dword(HWIO_FEATURE_CONFIG6_ADDR)
#define HWIO_FEATURE_CONFIG6_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG6_ADDR, m)
#define HWIO_FEATURE_CONFIG6_PCIE_0_DISABLE_BMSK                                                      0x80000000
#define HWIO_FEATURE_CONFIG6_PCIE_0_DISABLE_SHFT                                                              31
#define HWIO_FEATURE_CONFIG6_SSC_DISABLE_BMSK                                                         0x40000000
#define HWIO_FEATURE_CONFIG6_SSC_DISABLE_SHFT                                                                 30
#define HWIO_FEATURE_CONFIG6_SSC_Q6SS_L2TCM_EN_BMSK                                                   0x3f000000
#define HWIO_FEATURE_CONFIG6_SSC_Q6SS_L2TCM_EN_SHFT                                                           24
#define HWIO_FEATURE_CONFIG6_SSC_AON_CAM_DISABLE_BMSK                                                   0x800000
#define HWIO_FEATURE_CONFIG6_SSC_AON_CAM_DISABLE_SHFT                                                         23
#define HWIO_FEATURE_CONFIG6_SSC_ISLAND_MODE_Q6_CLK_DISABLE_BMSK                                        0x400000
#define HWIO_FEATURE_CONFIG6_SSC_ISLAND_MODE_Q6_CLK_DISABLE_SHFT                                              22
#define HWIO_FEATURE_CONFIG6_SSC_SW_ISLAND_MODE_DISABLE_BMSK                                            0x200000
#define HWIO_FEATURE_CONFIG6_SSC_SW_ISLAND_MODE_DISABLE_SHFT                                                  21
#define HWIO_FEATURE_CONFIG6_GPU_CC_FREQ_LIMIT_VAL_BMSK                                                 0x1fe000
#define HWIO_FEATURE_CONFIG6_GPU_CC_FREQ_LIMIT_VAL_SHFT                                                       13
#define HWIO_FEATURE_CONFIG6_FEATURE_CONFIG_204_BMSK                                                      0x1000
#define HWIO_FEATURE_CONFIG6_FEATURE_CONFIG_204_SHFT                                                          12
#define HWIO_FEATURE_CONFIG6_IRIS_DISABLE_8K_BMSK                                                          0x800
#define HWIO_FEATURE_CONFIG6_IRIS_DISABLE_8K_SHFT                                                             11
#define HWIO_FEATURE_CONFIG6_IRIS_DISABLE_AV1_BMSK                                                         0x400
#define HWIO_FEATURE_CONFIG6_IRIS_DISABLE_AV1_SHFT                                                            10
#define HWIO_FEATURE_CONFIG6_IRIS_DISABLE_10BIT_ENCODE_BMSK                                                0x200
#define HWIO_FEATURE_CONFIG6_IRIS_DISABLE_10BIT_ENCODE_SHFT                                                    9
#define HWIO_FEATURE_CONFIG6_IRIS_DISABLE_10BIT_DECODE_BMSK                                                0x100
#define HWIO_FEATURE_CONFIG6_IRIS_DISABLE_10BIT_DECODE_SHFT                                                    8
#define HWIO_FEATURE_CONFIG6_IRIS_MULTIPIPE_DISABLE_BMSK                                                    0x80
#define HWIO_FEATURE_CONFIG6_IRIS_MULTIPIPE_DISABLE_SHFT                                                       7
#define HWIO_FEATURE_CONFIG6_IRIS_HEVC_ENCODE_DISABLE_BMSK                                                  0x40
#define HWIO_FEATURE_CONFIG6_IRIS_HEVC_ENCODE_DISABLE_SHFT                                                     6
#define HWIO_FEATURE_CONFIG6_IRIS_HEVC_DECODE_DISABLE_BMSK                                                  0x20
#define HWIO_FEATURE_CONFIG6_IRIS_HEVC_DECODE_DISABLE_SHFT                                                     5
#define HWIO_FEATURE_CONFIG6_IRIS_4K_DISABLE_BMSK                                                           0x10
#define HWIO_FEATURE_CONFIG6_IRIS_4K_DISABLE_SHFT                                                              4
#define HWIO_FEATURE_CONFIG6_IRIS_CVP_DISABLE_BMSK                                                           0x8
#define HWIO_FEATURE_CONFIG6_IRIS_CVP_DISABLE_SHFT                                                             3
#define HWIO_FEATURE_CONFIG6_IRIS_DISABLE_VPX_BMSK                                                           0x4
#define HWIO_FEATURE_CONFIG6_IRIS_DISABLE_VPX_SHFT                                                             2
#define HWIO_FEATURE_CONFIG6_TITAN_CAM_SBI_DISABLE_IF_BMSK                                                   0x2
#define HWIO_FEATURE_CONFIG6_TITAN_CAM_SBI_DISABLE_IF_SHFT                                                     1
#define HWIO_FEATURE_CONFIG6_TITAN_AON_CAM_DISABLE_IF_BMSK                                                   0x1
#define HWIO_FEATURE_CONFIG6_TITAN_AON_CAM_DISABLE_IF_SHFT                                                     0

#define HWIO_FEATURE_CONFIG7_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x11c)
#define HWIO_FEATURE_CONFIG7_RMSK                                                                     0xffffffff
#define HWIO_FEATURE_CONFIG7_IN                    \
                in_dword(HWIO_FEATURE_CONFIG7_ADDR)
#define HWIO_FEATURE_CONFIG7_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG7_ADDR, m)
#define HWIO_FEATURE_CONFIG7_SYS_APSSCFGAPMBOOTONMX_BMSK                                              0x80000000
#define HWIO_FEATURE_CONFIG7_SYS_APSSCFGAPMBOOTONMX_SHFT                                                      31
#define HWIO_FEATURE_CONFIG7_SYS_APSSCFGCPUPRESENT_N_BMSK                                             0x7f800000
#define HWIO_FEATURE_CONFIG7_SYS_APSSCFGCPUPRESENT_N_SHFT                                                     23
#define HWIO_FEATURE_CONFIG7_APSS_PDXWRPNTRDELAY_BMSK                                                   0x600000
#define HWIO_FEATURE_CONFIG7_APSS_PDXWRPNTRDELAY_SHFT                                                         21
#define HWIO_FEATURE_CONFIG7_GATE_SRST_FUSE_BMSK                                                        0x100000
#define HWIO_FEATURE_CONFIG7_GATE_SRST_FUSE_SHFT                                                              20
#define HWIO_FEATURE_CONFIG7_AUTOMOTIVE_BIT_FUNCTIONAL_BMSK                                              0x80000
#define HWIO_FEATURE_CONFIG7_AUTOMOTIVE_BIT_FUNCTIONAL_SHFT                                                   19
#define HWIO_FEATURE_CONFIG7_AUTOMOTIVE_BIT_POWER_BMSK                                                   0x40000
#define HWIO_FEATURE_CONFIG7_AUTOMOTIVE_BIT_POWER_SHFT                                                        18
#define HWIO_FEATURE_CONFIG7_EMAC_DISABLE_BMSK                                                           0x20000
#define HWIO_FEATURE_CONFIG7_EMAC_DISABLE_SHFT                                                                17
#define HWIO_FEATURE_CONFIG7_NAV_EFUSE_DISABLE_BMSK                                                      0x10000
#define HWIO_FEATURE_CONFIG7_NAV_EFUSE_DISABLE_SHFT                                                           16
#define HWIO_FEATURE_CONFIG7_FUSE_CORTEX_M3_DISABLE_BMSK                                                  0x8000
#define HWIO_FEATURE_CONFIG7_FUSE_CORTEX_M3_DISABLE_SHFT                                                      15
#define HWIO_FEATURE_CONFIG7_APS_RESET_DISABLE_BMSK                                                       0x4000
#define HWIO_FEATURE_CONFIG7_APS_RESET_DISABLE_SHFT                                                           14
#define HWIO_FEATURE_CONFIG7_DOLBY_BIT_BMSK                                                               0x2000
#define HWIO_FEATURE_CONFIG7_DOLBY_BIT_SHFT                                                                   13
#define HWIO_FEATURE_CONFIG7_FEATURE_CONFIG_236_235_BMSK                                                  0x1800
#define HWIO_FEATURE_CONFIG7_FEATURE_CONFIG_236_235_SHFT                                                      11
#define HWIO_FEATURE_CONFIG7_SHRM1_DISABLE_BMSK                                                            0x400
#define HWIO_FEATURE_CONFIG7_SHRM1_DISABLE_SHFT                                                               10
#define HWIO_FEATURE_CONFIG7_PCIEPHY_DISABLE_UPPER_LANE_BMSK                                               0x200
#define HWIO_FEATURE_CONFIG7_PCIEPHY_DISABLE_UPPER_LANE_SHFT                                                   9
#define HWIO_FEATURE_CONFIG7_UFS_FUSE_ICE_DISABLE_BMSK                                                     0x100
#define HWIO_FEATURE_CONFIG7_UFS_FUSE_ICE_DISABLE_SHFT                                                         8
#define HWIO_FEATURE_CONFIG7_FEATURE_CONFIG_231_BMSK                                                        0x80
#define HWIO_FEATURE_CONFIG7_FEATURE_CONFIG_231_SHFT                                                           7
#define HWIO_FEATURE_CONFIG7_MOCHA_PART_BMSK                                                                0x40
#define HWIO_FEATURE_CONFIG7_MOCHA_PART_SHFT                                                                   6
#define HWIO_FEATURE_CONFIG7_QC_SP_DISABLE_BMSK                                                             0x20
#define HWIO_FEATURE_CONFIG7_QC_SP_DISABLE_SHFT                                                                5
#define HWIO_FEATURE_CONFIG7_SMMU_DISABLE_BMSK                                                              0x10
#define HWIO_FEATURE_CONFIG7_SMMU_DISABLE_SHFT                                                                 4
#define HWIO_FEATURE_CONFIG7_RSVD_BMSK                                                                       0x8
#define HWIO_FEATURE_CONFIG7_RSVD_SHFT                                                                         3
#define HWIO_FEATURE_CONFIG7_FEATURE_CONFIG_BMSK                                                             0x4
#define HWIO_FEATURE_CONFIG7_FEATURE_CONFIG_SHFT                                                               2
#define HWIO_FEATURE_CONFIG7_CM_FEAT_CONFIG_DISABLE_BMSK                                                     0x2
#define HWIO_FEATURE_CONFIG7_CM_FEAT_CONFIG_DISABLE_SHFT                                                       1
#define HWIO_FEATURE_CONFIG7_PCIE_1_DISABLE_BMSK                                                             0x1
#define HWIO_FEATURE_CONFIG7_PCIE_1_DISABLE_SHFT                                                               0

#define HWIO_FEATURE_CONFIG8_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x120)
#define HWIO_FEATURE_CONFIG8_RMSK                                                                     0xffffffff
#define HWIO_FEATURE_CONFIG8_IN                    \
                in_dword(HWIO_FEATURE_CONFIG8_ADDR)
#define HWIO_FEATURE_CONFIG8_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG8_ADDR, m)
#define HWIO_FEATURE_CONFIG8_SYS_CFG_GOLDPLUS_PLL_LVAL_4_0_BMSK                                       0xf8000000
#define HWIO_FEATURE_CONFIG8_SYS_CFG_GOLDPLUS_PLL_LVAL_4_0_SHFT                                               27
#define HWIO_FEATURE_CONFIG8_SYS_CFG_APC1PLL_LVAL_BMSK                                                 0x7f80000
#define HWIO_FEATURE_CONFIG8_SYS_CFG_APC1PLL_LVAL_SHFT                                                        19
#define HWIO_FEATURE_CONFIG8_APSS_KRYO_PP_DISABLE_BMSK                                                   0x40000
#define HWIO_FEATURE_CONFIG8_APSS_KRYO_PP_DISABLE_SHFT                                                        18
#define HWIO_FEATURE_CONFIG8_SYS_CFG_L3_SIZE_RED_BMSK                                                    0x20000
#define HWIO_FEATURE_CONFIG8_SYS_CFG_L3_SIZE_RED_SHFT                                                         17
#define HWIO_FEATURE_CONFIG8_SYS_APSS_APBDFDEN_BMSK                                                      0x10000
#define HWIO_FEATURE_CONFIG8_SYS_APSS_APBDFDEN_SHFT                                                           16
#define HWIO_FEATURE_CONFIG8_MIBU_PP_DISABLE_BMSK                                                         0x8000
#define HWIO_FEATURE_CONFIG8_MIBU_PP_DISABLE_SHFT                                                             15
#define HWIO_FEATURE_CONFIG8_BROADCAST_ATOMIC_MP_BMSK                                                     0x4000
#define HWIO_FEATURE_CONFIG8_BROADCAST_ATOMIC_MP_SHFT                                                         14
#define HWIO_FEATURE_CONFIG8_BROADCASTOUTERMP_BMSK                                                        0x2000
#define HWIO_FEATURE_CONFIG8_BROADCASTOUTERMP_SHFT                                                            13
#define HWIO_FEATURE_CONFIG8_DEVNRINTERLEAVE_BMSK                                                         0x1800
#define HWIO_FEATURE_CONFIG8_DEVNRINTERLEAVE_SHFT                                                             11
#define HWIO_FEATURE_CONFIG8_DEFAULT_MP_BMSK                                                               0x400
#define HWIO_FEATURE_CONFIG8_DEFAULT_MP_SHFT                                                                  10
#define HWIO_FEATURE_CONFIG8_BROADCAST_CACHE_MAINT_MP_BMSK                                                 0x200
#define HWIO_FEATURE_CONFIG8_BROADCAST_CACHE_MAINT_MP_SHFT                                                     9
#define HWIO_FEATURE_CONFIG8_BROADCAST_TLB_OUTER_BMSK                                                      0x100
#define HWIO_FEATURE_CONFIG8_BROADCAST_TLB_OUTER_SHFT                                                          8
#define HWIO_FEATURE_CONFIG8_BROADCAST_TLB_INNER_BMSK                                                       0x80
#define HWIO_FEATURE_CONFIG8_BROADCAST_TLB_INNER_SHFT                                                          7
#define HWIO_FEATURE_CONFIG8_BROADCASTICINVAL_BMSK                                                          0x40
#define HWIO_FEATURE_CONFIG8_BROADCASTICINVAL_SHFT                                                             6
#define HWIO_FEATURE_CONFIG8_APPS_BOOT_FSM_FUSE_BMSK                                                        0x3f
#define HWIO_FEATURE_CONFIG8_APPS_BOOT_FSM_FUSE_SHFT                                                           0

#define HWIO_FEATURE_CONFIG9_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x124)
#define HWIO_FEATURE_CONFIG9_RMSK                                                                     0xffffffff
#define HWIO_FEATURE_CONFIG9_IN                    \
                in_dword(HWIO_FEATURE_CONFIG9_ADDR)
#define HWIO_FEATURE_CONFIG9_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG9_ADDR, m)
#define HWIO_FEATURE_CONFIG9_TURING_Q6SS_L2TCM_EN_4_0_BMSK                                            0xf8000000
#define HWIO_FEATURE_CONFIG9_TURING_Q6SS_L2TCM_EN_4_0_SHFT                                                    27
#define HWIO_FEATURE_CONFIG9_TURING_Q6SS_HVX_EN_BMSK                                                   0x4000000
#define HWIO_FEATURE_CONFIG9_TURING_Q6SS_HVX_EN_SHFT                                                          26
#define HWIO_FEATURE_CONFIG9_TURING_Q6SS_HVX_HALF_BMSK                                                 0x2000000
#define HWIO_FEATURE_CONFIG9_TURING_Q6SS_HVX_HALF_SHFT                                                        25
#define HWIO_FEATURE_CONFIG9_TURING_Q6SS_PLL_L_MAX_BMSK                                                0x1fffe00
#define HWIO_FEATURE_CONFIG9_TURING_Q6SS_PLL_L_MAX_SHFT                                                        9
#define HWIO_FEATURE_CONFIG9_LEGACY_MBNV6_OVERRIDE_BMSK                                                    0x100
#define HWIO_FEATURE_CONFIG9_LEGACY_MBNV6_OVERRIDE_SHFT                                                        8
#define HWIO_FEATURE_CONFIG9_APSS_SPARE_NEW_IN_BMSK                                                         0xf8
#define HWIO_FEATURE_CONFIG9_APSS_SPARE_NEW_IN_SHFT                                                            3
#define HWIO_FEATURE_CONFIG9_SYS_CFG_GOLDPLUS_PLL_LVAL_7_5_BMSK                                              0x7
#define HWIO_FEATURE_CONFIG9_SYS_CFG_GOLDPLUS_PLL_LVAL_7_5_SHFT                                                0

#define HWIO_FEATURE_CONFIG10_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x128)
#define HWIO_FEATURE_CONFIG10_RMSK                                                                    0xffffffff
#define HWIO_FEATURE_CONFIG10_IN                    \
                in_dword(HWIO_FEATURE_CONFIG10_ADDR)
#define HWIO_FEATURE_CONFIG10_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG10_ADDR, m)
#define HWIO_FEATURE_CONFIG10_FEATURE_CONFIG_351_337_BMSK                                             0xfffe0000
#define HWIO_FEATURE_CONFIG10_FEATURE_CONFIG_351_337_SHFT                                                     17
#define HWIO_FEATURE_CONFIG10_MODEM_FEATURE_DISABLE_SPARE_14_8_BMSK                                      0x1fc00
#define HWIO_FEATURE_CONFIG10_MODEM_FEATURE_DISABLE_SPARE_14_8_SHFT                                           10
#define HWIO_FEATURE_CONFIG10_FEATURE_CONFIG_BMSK                                                          0x380
#define HWIO_FEATURE_CONFIG10_FEATURE_CONFIG_SHFT                                                              7
#define HWIO_FEATURE_CONFIG10_TURING_QDSP_HMX_FLTARRAYTHROTTLE_BMSK                                         0x60
#define HWIO_FEATURE_CONFIG10_TURING_QDSP_HMX_FLTARRAYTHROTTLE_SHFT                                            5
#define HWIO_FEATURE_CONFIG10_TURING_QDSP6_HMX_FXPARRAYTHROTTLE_BMSK                                        0x18
#define HWIO_FEATURE_CONFIG10_TURING_QDSP6_HMX_FXPARRAYTHROTTLE_SHFT                                           3
#define HWIO_FEATURE_CONFIG10_TURING_QDSP6_HVX_VTCMSIZE_BMSK                                                 0x6
#define HWIO_FEATURE_CONFIG10_TURING_QDSP6_HVX_VTCMSIZE_SHFT                                                   1
#define HWIO_FEATURE_CONFIG10_TURING_Q6SS_L2TCM_EN_5_BMSK                                                    0x1
#define HWIO_FEATURE_CONFIG10_TURING_Q6SS_L2TCM_EN_5_SHFT                                                      0

#define HWIO_FEATURE_CONFIG11_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x12c)
#define HWIO_FEATURE_CONFIG11_RMSK                                                                    0xffffffff
#define HWIO_FEATURE_CONFIG11_IN                    \
                in_dword(HWIO_FEATURE_CONFIG11_ADDR)
#define HWIO_FEATURE_CONFIG11_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG11_ADDR, m)
#define HWIO_FEATURE_CONFIG11_FEATURE_CONFIG_383_352_BMSK                                             0xffffffff
#define HWIO_FEATURE_CONFIG11_FEATURE_CONFIG_383_352_SHFT                                                      0

#define HWIO_FEATURE_CONFIG12_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x130)
#define HWIO_FEATURE_CONFIG12_RMSK                                                                    0xffffffff
#define HWIO_FEATURE_CONFIG12_IN                    \
                in_dword(HWIO_FEATURE_CONFIG12_ADDR)
#define HWIO_FEATURE_CONFIG12_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG12_ADDR, m)
#define HWIO_FEATURE_CONFIG12_FEATURE_CONFIG_415_384_BMSK                                             0xffffffff
#define HWIO_FEATURE_CONFIG12_FEATURE_CONFIG_415_384_SHFT                                                      0

#define HWIO_FEATURE_CONFIG13_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x134)
#define HWIO_FEATURE_CONFIG13_RMSK                                                                    0xffffffff
#define HWIO_FEATURE_CONFIG13_IN                    \
                in_dword(HWIO_FEATURE_CONFIG13_ADDR)
#define HWIO_FEATURE_CONFIG13_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG13_ADDR, m)
#define HWIO_FEATURE_CONFIG13_FEATURE_CONFIG_447_416_BMSK                                             0xffffffff
#define HWIO_FEATURE_CONFIG13_FEATURE_CONFIG_447_416_SHFT                                                      0

#define HWIO_FEATURE_CONFIG14_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x138)
#define HWIO_FEATURE_CONFIG14_RMSK                                                                    0xffffffff
#define HWIO_FEATURE_CONFIG14_IN                    \
                in_dword(HWIO_FEATURE_CONFIG14_ADDR)
#define HWIO_FEATURE_CONFIG14_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG14_ADDR, m)
#define HWIO_FEATURE_CONFIG14_FEATURE_CONFIG_479_448_BMSK                                             0xffffffff
#define HWIO_FEATURE_CONFIG14_FEATURE_CONFIG_479_448_SHFT                                                      0

#define HWIO_FEATURE_CONFIG15_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x13c)
#define HWIO_FEATURE_CONFIG15_RMSK                                                                    0xffffffff
#define HWIO_FEATURE_CONFIG15_IN                    \
                in_dword(HWIO_FEATURE_CONFIG15_ADDR)
#define HWIO_FEATURE_CONFIG15_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG15_ADDR, m)
#define HWIO_FEATURE_CONFIG15_FEATURE_CONFIG_511_480_BMSK                                             0xffffffff
#define HWIO_FEATURE_CONFIG15_FEATURE_CONFIG_511_480_SHFT                                                      0

#define HWIO_QC_CONFIG0_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x200)
#define HWIO_QC_CONFIG0_RMSK                                                                          0xffffffff
#define HWIO_QC_CONFIG0_IN                    \
                in_dword(HWIO_QC_CONFIG0_ADDR)
#define HWIO_QC_CONFIG0_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG0_ADDR, m)
#define HWIO_QC_CONFIG0_FUSE_SW_OVERRIDE_SOC_HW_VER_EN_BMSK                                           0x80000000
#define HWIO_QC_CONFIG0_FUSE_SW_OVERRIDE_SOC_HW_VER_EN_SHFT                                                   31
#define HWIO_QC_CONFIG0_PRNG_TESTMODE_DISABLE_BMSK                                                    0x40000000
#define HWIO_QC_CONFIG0_PRNG_TESTMODE_DISABLE_SHFT                                                            30
#define HWIO_QC_CONFIG0_TME_PRNG_TESTMODE_DISABLE_BMSK                                                0x20000000
#define HWIO_QC_CONFIG0_TME_PRNG_TESTMODE_DISABLE_SHFT                                                        29
#define HWIO_QC_CONFIG0_QC_CONFIG_27_28_BMSK                                                          0x18000000
#define HWIO_QC_CONFIG0_QC_CONFIG_27_28_SHFT                                                                  27
#define HWIO_QC_CONFIG0_TME_RSVD_BMSK                                                                  0x7f00000
#define HWIO_QC_CONFIG0_TME_RSVD_SHFT                                                                         20
#define HWIO_QC_CONFIG0_PROVANDDBGUNLOCKAUTHY_BMSK                                                       0xc0000
#define HWIO_QC_CONFIG0_PROVANDDBGUNLOCKAUTHY_SHFT                                                            18
#define HWIO_QC_CONFIG0_CRIPRGCHIPUNQIEIDEN_BMSK                                                         0x20000
#define HWIO_QC_CONFIG0_CRIPRGCHIPUNQIEIDEN_SHFT                                                              17
#define HWIO_QC_CONFIG0_CRED_THROTTLE_MAX_TIME_OUT_BMSK                                                  0x18000
#define HWIO_QC_CONFIG0_CRED_THROTTLE_MAX_TIME_OUT_SHFT                                                       15
#define HWIO_QC_CONFIG0_DISABLESEQCMDSLOT1_BMSK                                                           0x4000
#define HWIO_QC_CONFIG0_DISABLESEQCMDSLOT1_SHFT                                                               14
#define HWIO_QC_CONFIG0_TME_FREQ_PLAN_ID_BMSK                                                             0x3000
#define HWIO_QC_CONFIG0_TME_FREQ_PLAN_ID_SHFT                                                                 12
#define HWIO_QC_CONFIG0_CPUMODEDISABLE_BMSK                                                                0x800
#define HWIO_QC_CONFIG0_CPUMODEDISABLE_SHFT                                                                   11
#define HWIO_QC_CONFIG0_CPU_BYPASS_EN_BMSK                                                                 0x400
#define HWIO_QC_CONFIG0_CPU_BYPASS_EN_SHFT                                                                    10
#define HWIO_QC_CONFIG0_HWKEYPOLICYENFORCEMENT_BMSK                                                        0x200
#define HWIO_QC_CONFIG0_HWKEYPOLICYENFORCEMENT_SHFT                                                            9
#define HWIO_QC_CONFIG0_DEVICEINPERSOPHASE_BMSK                                                            0x100
#define HWIO_QC_CONFIG0_DEVICEINPERSOPHASE_SHFT                                                                8
#define HWIO_QC_CONFIG0_PBLTIMEOUTSETTING_BMSK                                                              0xff
#define HWIO_QC_CONFIG0_PBLTIMEOUTSETTING_SHFT                                                                 0

#define HWIO_QC_CONFIG1_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x204)
#define HWIO_QC_CONFIG1_RMSK                                                                          0xffffffff
#define HWIO_QC_CONFIG1_IN                    \
                in_dword(HWIO_QC_CONFIG1_ADDR)
#define HWIO_QC_CONFIG1_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG1_ADDR, m)
#define HWIO_QC_CONFIG1_APPS_BOOT_FROM_ROM_BMSK                                                       0x80000000
#define HWIO_QC_CONFIG1_APPS_BOOT_FROM_ROM_SHFT                                                               31
#define HWIO_QC_CONFIG1_ENABLE_DEVICE_IN_TEST_MODE_BMSK                                               0x40000000
#define HWIO_QC_CONFIG1_ENABLE_DEVICE_IN_TEST_MODE_SHFT                                                       30
#define HWIO_QC_CONFIG1_QTI_ROOT_SIG_FORMAT_SEL_BMSK                                                  0x20000000
#define HWIO_QC_CONFIG1_QTI_ROOT_SIG_FORMAT_SEL_SHFT                                                          29
#define HWIO_QC_CONFIG1_CE_BAM_DISABLE_BMSK                                                           0x10000000
#define HWIO_QC_CONFIG1_CE_BAM_DISABLE_SHFT                                                                   28
#define HWIO_QC_CONFIG1_LEGACY_MBNV6_OEM_AUTH_CTRL_SECBOOT_BMSK                                        0x8000000
#define HWIO_QC_CONFIG1_LEGACY_MBNV6_OEM_AUTH_CTRL_SECBOOT_SHFT                                               27
#define HWIO_QC_CONFIG1_ARM_CE_DISABLE_USAGE_BMSK                                                      0x4000000
#define HWIO_QC_CONFIG1_ARM_CE_DISABLE_USAGE_SHFT                                                             26
#define HWIO_QC_CONFIG1_BOOT_ROM_CFG_BMSK                                                              0x3fc0000
#define HWIO_QC_CONFIG1_BOOT_ROM_CFG_SHFT                                                                     18
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_7_BMSK                                                      0x20000
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_7_SHFT                                                           17
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_6_BMSK                                                      0x10000
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_6_SHFT                                                           16
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_5_BMSK                                                       0x8000
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_5_SHFT                                                           15
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_4_BMSK                                                       0x4000
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_4_SHFT                                                           14
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_3_BMSK                                                       0x2000
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_3_SHFT                                                           13
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_2_BMSK                                                       0x1000
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_2_SHFT                                                           12
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_1_BMSK                                                        0x800
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_1_SHFT                                                           11
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_0_BMSK                                                        0x400
#define HWIO_QC_CONFIG1_ACCU_RED_DEC_END_VAL_0_SHFT                                                           10
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE7_BMSK                                                0x200
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE7_SHFT                                                    9
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE6_BMSK                                                0x100
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE6_SHFT                                                    8
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE5_BMSK                                                 0x80
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE5_SHFT                                                    7
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE4_BMSK                                                 0x40
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE4_SHFT                                                    6
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE3_BMSK                                                 0x20
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE3_SHFT                                                    5
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE2_BMSK                                                 0x10
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE2_SHFT                                                    4
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE1_BMSK                                                  0x8
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE1_SHFT                                                    3
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE0_BMSK                                                  0x4
#define HWIO_QC_CONFIG1_P2S_ACCU_RED_DEC_END_VAL_FUSE0_SHFT                                                    2
#define HWIO_QC_CONFIG1_SM_BIST_DISABLE_BMSK                                                                 0x2
#define HWIO_QC_CONFIG1_SM_BIST_DISABLE_SHFT                                                                   1
#define HWIO_QC_CONFIG1_TIC_DISABLE_BMSK                                                                     0x1
#define HWIO_QC_CONFIG1_TIC_DISABLE_SHFT                                                                       0

#define HWIO_QC_CONFIG2_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x208)
#define HWIO_QC_CONFIG2_RMSK                                                                          0xffffffff
#define HWIO_QC_CONFIG2_IN                    \
                in_dword(HWIO_QC_CONFIG2_ADDR)
#define HWIO_QC_CONFIG2_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG2_ADDR, m)
#define HWIO_QC_CONFIG2_TAP_GEN_SPARE_INSTR_DISABLE_12_0_BMSK                                         0xfff80000
#define HWIO_QC_CONFIG2_TAP_GEN_SPARE_INSTR_DISABLE_12_0_SHFT                                                 19
#define HWIO_QC_CONFIG2_TAP_INSTR_DISABLE_BMSK                                                           0x7fffe
#define HWIO_QC_CONFIG2_TAP_INSTR_DISABLE_SHFT                                                                 1
#define HWIO_QC_CONFIG2_MODEM_PBL_BOOT_BMSK                                                                  0x1
#define HWIO_QC_CONFIG2_MODEM_PBL_BOOT_SHFT                                                                    0

#define HWIO_QC_CONFIG3_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x20c)
#define HWIO_QC_CONFIG3_RMSK                                                                          0xffffffff
#define HWIO_QC_CONFIG3_IN                    \
                in_dword(HWIO_QC_CONFIG3_ADDR)
#define HWIO_QC_CONFIG3_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG3_ADDR, m)
#define HWIO_QC_CONFIG3_SEC_TAP_ACCESS_DISABLE_12_0_BMSK                                              0xfff80000
#define HWIO_QC_CONFIG3_SEC_TAP_ACCESS_DISABLE_12_0_SHFT                                                      19
#define HWIO_QC_CONFIG3_TAP_GEN_SPARE_INSTR_DISABLE_31_13_BMSK                                           0x7ffff
#define HWIO_QC_CONFIG3_TAP_GEN_SPARE_INSTR_DISABLE_31_13_SHFT                                                 0

#define HWIO_QC_CONFIG4_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x210)
#define HWIO_QC_CONFIG4_RMSK                                                                          0xf003ffff
#define HWIO_QC_CONFIG4_IN                    \
                in_dword(HWIO_QC_CONFIG4_ADDR)
#define HWIO_QC_CONFIG4_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG4_ADDR, m)
#define HWIO_QC_CONFIG4_QC_CONFIG_159_146_BMSK                                                        0xf0000000
#define HWIO_QC_CONFIG4_QC_CONFIG_159_146_SHFT                                                                28
#define HWIO_QC_CONFIG4_APPS_PBL_BOOT_SPEED_BMSK                                                         0x30000
#define HWIO_QC_CONFIG4_APPS_PBL_BOOT_SPEED_SHFT                                                              16
#define HWIO_QC_CONFIG4_VENDOR_LOCK_BMSK                                                                  0xf000
#define HWIO_QC_CONFIG4_VENDOR_LOCK_SHFT                                                                      12
#define HWIO_QC_CONFIG4_FOUNDRY_ID_BMSK                                                                    0xf00
#define HWIO_QC_CONFIG4_FOUNDRY_ID_SHFT                                                                        8
#define HWIO_QC_CONFIG4_STACKED_MEMORY_ID_BMSK                                                              0xf8
#define HWIO_QC_CONFIG4_STACKED_MEMORY_ID_SHFT                                                                 3
#define HWIO_QC_CONFIG4_SEC_TAP_ACCESS_DISABLE_15_13_BMSK                                                    0x7
#define HWIO_QC_CONFIG4_SEC_TAP_ACCESS_DISABLE_15_13_SHFT                                                      0

#define HWIO_QC_CONFIG5_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x214)
#define HWIO_QC_CONFIG5_RMSK                                                                          0xffffffff
#define HWIO_QC_CONFIG5_IN                    \
                in_dword(HWIO_QC_CONFIG5_ADDR)
#define HWIO_QC_CONFIG5_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG5_ADDR, m)
#define HWIO_QC_CONFIG5_PAUSE_POINT_BMSK                                                              0x80000000
#define HWIO_QC_CONFIG5_PAUSE_POINT_SHFT                                                                      31
#define HWIO_QC_CONFIG5_PREVENT_FUSE_SENSE_ON_ERROR_BMSK                                              0x40000000
#define HWIO_QC_CONFIG5_PREVENT_FUSE_SENSE_ON_ERROR_SHFT                                                      30
#define HWIO_QC_CONFIG5_SEQ_BOOT_TIMEOUT_BMSK                                                         0x3c000000
#define HWIO_QC_CONFIG5_SEQ_BOOT_TIMEOUT_SHFT                                                                 26
#define HWIO_QC_CONFIG5_GCC_REFGEN_HANDSHAKE_DISABLE_BMSK                                              0x2000000
#define HWIO_QC_CONFIG5_GCC_REFGEN_HANDSHAKE_DISABLE_SHFT                                                     25
#define HWIO_QC_CONFIG5_SEQUENCERROMBYPASSEN_BMSK                                                      0x1000000
#define HWIO_QC_CONFIG5_SEQUENCERROMBYPASSEN_SHFT                                                             24
#define HWIO_QC_CONFIG5_SPU_MIRROR_IAR_STATE_BMSK                                                       0xe00000
#define HWIO_QC_CONFIG5_SPU_MIRROR_IAR_STATE_SHFT                                                             21
#define HWIO_QC_CONFIG5_ACCU_RED_DEC_END_VAL_MODEM_BMSK                                                 0x1fe000
#define HWIO_QC_CONFIG5_ACCU_RED_DEC_END_VAL_MODEM_SHFT                                                       13
#define HWIO_QC_CONFIG5_APCS_BOOT_TRIGGER_DISABLE_BMSK                                                    0x1000
#define HWIO_QC_CONFIG5_APCS_BOOT_TRIGGER_DISABLE_SHFT                                                        12
#define HWIO_QC_CONFIG5_PBL_QSEE_BOOT_FLOW_DISABLE_BMSK                                                    0x800
#define HWIO_QC_CONFIG5_PBL_QSEE_BOOT_FLOW_DISABLE_SHFT                                                       11
#define HWIO_QC_CONFIG5_TME_FW_XBL_SC_QTI_AUTH_DISABLE_BMSK                                                0x400
#define HWIO_QC_CONFIG5_TME_FW_XBL_SC_QTI_AUTH_DISABLE_SHFT                                                   10
#define HWIO_QC_CONFIG5_MSM_PKG_TYPE_BMSK                                                                  0x200
#define HWIO_QC_CONFIG5_MSM_PKG_TYPE_SHFT                                                                      9
#define HWIO_QC_CONFIG5_SPSS_CONFIG_MODE_BMSK                                                              0x180
#define HWIO_QC_CONFIG5_SPSS_CONFIG_MODE_SHFT                                                                  7
#define HWIO_QC_CONFIG5_PERIPH_DRV_STRENGTH_SETTING__BMSK                                                   0x70
#define HWIO_QC_CONFIG5_PERIPH_DRV_STRENGTH_SETTING__SHFT                                                      4
#define HWIO_QC_CONFIG5_APPS_PBL_PLL_CTRL_BMSK                                                               0xf
#define HWIO_QC_CONFIG5_APPS_PBL_PLL_CTRL_SHFT                                                                 0

#define HWIO_QC_CONFIG6_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x218)
#define HWIO_QC_CONFIG6_RMSK                                                                          0xffffffff
#define HWIO_QC_CONFIG6_IN                    \
                in_dword(HWIO_QC_CONFIG6_ADDR)
#define HWIO_QC_CONFIG6_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG6_ADDR, m)
#define HWIO_QC_CONFIG6_QC_CONFIG_223_207_BMSK                                                        0xffff8000
#define HWIO_QC_CONFIG6_QC_CONFIG_223_207_SHFT                                                                15
#define HWIO_QC_CONFIG6_TME_MROM_MEASURED_BOOT_DISABLE_BMSK                                               0x4000
#define HWIO_QC_CONFIG6_TME_MROM_MEASURED_BOOT_DISABLE_SHFT                                                   14
#define HWIO_QC_CONFIG6_MEMRED_CRC_CHECK_ENABLE_BMSK                                                      0x2000
#define HWIO_QC_CONFIG6_MEMRED_CRC_CHECK_ENABLE_SHFT                                                          13
#define HWIO_QC_CONFIG6_TME_PBL_SECURE_BOOT_BYPASS_ENABLE_BMSK                                            0x1000
#define HWIO_QC_CONFIG6_TME_PBL_SECURE_BOOT_BYPASS_ENABLE_SHFT                                                12
#define HWIO_QC_CONFIG6_TME_ROM_ACCESS_CONTROL_BYPASS_ENABLE_BMSK                                          0x800
#define HWIO_QC_CONFIG6_TME_ROM_ACCESS_CONTROL_BYPASS_ENABLE_SHFT                                             11
#define HWIO_QC_CONFIG6_APPS_PBL_EDL_IMG_LIST_SAME_AS_NO_EDL_BMSK                                          0x400
#define HWIO_QC_CONFIG6_APPS_PBL_EDL_IMG_LIST_SAME_AS_NO_EDL_SHFT                                             10
#define HWIO_QC_CONFIG6_PBL_SW_CONFIG_BMSK                                                                 0x3fc
#define HWIO_QC_CONFIG6_PBL_SW_CONFIG_SHFT                                                                     2
#define HWIO_QC_CONFIG6_DISABLE_SEC_BOOT_GPIO_BMSK                                                           0x2
#define HWIO_QC_CONFIG6_DISABLE_SEC_BOOT_GPIO_SHFT                                                             1
#define HWIO_QC_CONFIG6_TME_CPU_PBL_ROM_BYPASS_EN_BMSK                                                       0x1
#define HWIO_QC_CONFIG6_TME_CPU_PBL_ROM_BYPASS_EN_SHFT                                                         0

#define HWIO_QC_CONFIG7_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x21c)
#define HWIO_QC_CONFIG7_RMSK                                                                          0xffffffff
#define HWIO_QC_CONFIG7_IN                    \
                in_dword(HWIO_QC_CONFIG7_ADDR)
#define HWIO_QC_CONFIG7_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG7_ADDR, m)
#define HWIO_QC_CONFIG7_QC_CONFIG_255_229_BMSK                                                        0xffffffe0
#define HWIO_QC_CONFIG7_QC_CONFIG_255_229_SHFT                                                                 5
#define HWIO_QC_CONFIG7_APQ_SKU_BMSK                                                                        0x10
#define HWIO_QC_CONFIG7_APQ_SKU_SHFT                                                                           4
#define HWIO_QC_CONFIG7_XR_SKU_BMSK                                                                          0x8
#define HWIO_QC_CONFIG7_XR_SKU_SHFT                                                                            3
#define HWIO_QC_CONFIG7_TME_CPU_DBG_HALT_EN_IFC_PRIV_BMSK                                                    0x4
#define HWIO_QC_CONFIG7_TME_CPU_DBG_HALT_EN_IFC_PRIV_SHFT                                                      2
#define HWIO_QC_CONFIG7_TME_CPU_DBG_HALT_EN_CAUSE_COMMIT_BMSK                                                0x2
#define HWIO_QC_CONFIG7_TME_CPU_DBG_HALT_EN_CAUSE_COMMIT_SHFT                                                  1
#define HWIO_QC_CONFIG7_SEQ_DISABLE_CODE_RAM_WR_BMSK                                                         0x1
#define HWIO_QC_CONFIG7_SEQ_DISABLE_CODE_RAM_WR_SHFT                                                           0

#define HWIO_QC_CONFIG8_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x220)
#define HWIO_QC_CONFIG8_RMSK                                                                          0xffffffff
#define HWIO_QC_CONFIG8_IN                    \
                in_dword(HWIO_QC_CONFIG8_ADDR)
#define HWIO_QC_CONFIG8_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG8_ADDR, m)
#define HWIO_QC_CONFIG8_QC_CONFIG_287_256_BMSK                                                        0xffffffff
#define HWIO_QC_CONFIG8_QC_CONFIG_287_256_SHFT                                                                 0

#define HWIO_QC_CONFIG9_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x224)
#define HWIO_QC_CONFIG9_RMSK                                                                          0xffffffff
#define HWIO_QC_CONFIG9_IN                    \
                in_dword(HWIO_QC_CONFIG9_ADDR)
#define HWIO_QC_CONFIG9_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG9_ADDR, m)
#define HWIO_QC_CONFIG9_QC_CONFIG_319_288_BMSK                                                        0xffffffff
#define HWIO_QC_CONFIG9_QC_CONFIG_319_288_SHFT                                                                 0

#define HWIO_QC_CONFIG10_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x228)
#define HWIO_QC_CONFIG10_RMSK                                                                         0xffffffff
#define HWIO_QC_CONFIG10_IN                    \
                in_dword(HWIO_QC_CONFIG10_ADDR)
#define HWIO_QC_CONFIG10_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG10_ADDR, m)
#define HWIO_QC_CONFIG10_QC_CONFIG_351_320_BMSK                                                       0xffffffff
#define HWIO_QC_CONFIG10_QC_CONFIG_351_320_SHFT                                                                0

#define HWIO_QC_CONFIG11_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x22c)
#define HWIO_QC_CONFIG11_RMSK                                                                         0xffffffff
#define HWIO_QC_CONFIG11_IN                    \
                in_dword(HWIO_QC_CONFIG11_ADDR)
#define HWIO_QC_CONFIG11_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG11_ADDR, m)
#define HWIO_QC_CONFIG11_QC_CONFIG_383_352_BMSK                                                       0xffffffff
#define HWIO_QC_CONFIG11_QC_CONFIG_383_352_SHFT                                                                0

#define HWIO_QC_CONFIG12_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x230)
#define HWIO_QC_CONFIG12_RMSK                                                                         0xffffffff
#define HWIO_QC_CONFIG12_IN                    \
                in_dword(HWIO_QC_CONFIG12_ADDR)
#define HWIO_QC_CONFIG12_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG12_ADDR, m)
#define HWIO_QC_CONFIG12_QC_CONFIG_415_384_BMSK                                                       0xffffffff
#define HWIO_QC_CONFIG12_QC_CONFIG_415_384_SHFT                                                                0

#define HWIO_QC_CONFIG13_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x234)
#define HWIO_QC_CONFIG13_RMSK                                                                         0xffffffff
#define HWIO_QC_CONFIG13_IN                    \
                in_dword(HWIO_QC_CONFIG13_ADDR)
#define HWIO_QC_CONFIG13_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG13_ADDR, m)
#define HWIO_QC_CONFIG13_QC_CONFIG_447_416_BMSK                                                       0xffffffff
#define HWIO_QC_CONFIG13_QC_CONFIG_447_416_SHFT                                                                0

#define HWIO_QC_CONFIG14_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x238)
#define HWIO_QC_CONFIG14_RMSK                                                                         0xffffffff
#define HWIO_QC_CONFIG14_IN                    \
                in_dword(HWIO_QC_CONFIG14_ADDR)
#define HWIO_QC_CONFIG14_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG14_ADDR, m)
#define HWIO_QC_CONFIG14_QC_CONFIG_479_448_BMSK                                                       0xffffffff
#define HWIO_QC_CONFIG14_QC_CONFIG_479_448_SHFT                                                                0

#define HWIO_QC_CONFIG15_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x23c)
#define HWIO_QC_CONFIG15_RMSK                                                                         0xffffffff
#define HWIO_QC_CONFIG15_IN                    \
                in_dword(HWIO_QC_CONFIG15_ADDR)
#define HWIO_QC_CONFIG15_INM(m)            \
                in_dword_masked(HWIO_QC_CONFIG15_ADDR, m)
#define HWIO_QC_CONFIG15_QC_CONFIG_511_480_BMSK                                                       0xffffffff
#define HWIO_QC_CONFIG15_QC_CONFIG_511_480_SHFT                                                                0

#define HWIO_OEM_CONFIG0_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x300)
#define HWIO_OEM_CONFIG0_RMSK                                                                         0xffffffff
#define HWIO_OEM_CONFIG0_IN                    \
                in_dword(HWIO_OEM_CONFIG0_ADDR)
#define HWIO_OEM_CONFIG0_INM(m)            \
                in_dword_masked(HWIO_OEM_CONFIG0_ADDR, m)
#define HWIO_OEM_CONFIG0_OEM_CONFIG_31_BMSK                                                           0x80000000
#define HWIO_OEM_CONFIG0_OEM_CONFIG_31_SHFT                                                                   31
#define HWIO_OEM_CONFIG0_PBL_FDL_TIMEOUT_RESET_TO_VAL_BMSK                                            0x60000000
#define HWIO_OEM_CONFIG0_PBL_FDL_TIMEOUT_RESET_TO_VAL_SHFT                                                    29
#define HWIO_OEM_CONFIG0_DEBUG_POLICY_DISABLE_BMSK                                                    0x10000000
#define HWIO_OEM_CONFIG0_DEBUG_POLICY_DISABLE_SHFT                                                            28
#define HWIO_OEM_CONFIG0_SP_DISABLE_BMSK                                                               0x8000000
#define HWIO_OEM_CONFIG0_SP_DISABLE_SHFT                                                                      27
#define HWIO_OEM_CONFIG0_OEM_CONFIG_26_24_BMSK                                                         0x7000000
#define HWIO_OEM_CONFIG0_OEM_CONFIG_26_24_SHFT                                                                24
#define HWIO_OEM_CONFIG0_USB_PIPO_DISABLE_BMSK                                                          0x800000
#define HWIO_OEM_CONFIG0_USB_PIPO_DISABLE_SHFT                                                                23
#define HWIO_OEM_CONFIG0_USB_SS_DISABLE_BMSK                                                            0x400000
#define HWIO_OEM_CONFIG0_USB_SS_DISABLE_SHFT                                                                  22
#define HWIO_OEM_CONFIG0_OEM_CONFIG_21_20_BMSK                                                          0x300000
#define HWIO_OEM_CONFIG0_OEM_CONFIG_21_20_SHFT                                                                20
#define HWIO_OEM_CONFIG0_QSPI_DMA_DISABLE_BMSK                                                           0x80000
#define HWIO_OEM_CONFIG0_QSPI_DMA_DISABLE_SHFT                                                                19
#define HWIO_OEM_CONFIG0_ROOT_CERT_TOTAL_NUM_BMSK                                                        0x60000
#define HWIO_OEM_CONFIG0_ROOT_CERT_TOTAL_NUM_SHFT                                                             17
#define HWIO_OEM_CONFIG0_PBL_USB_TYPE_C_DISABLE_BMSK                                                     0x10000
#define HWIO_OEM_CONFIG0_PBL_USB_TYPE_C_DISABLE_SHFT                                                          16
#define HWIO_OEM_CONFIG0_PBL_LOG_DISABLE_BMSK                                                             0x8000
#define HWIO_OEM_CONFIG0_PBL_LOG_DISABLE_SHFT                                                                 15
#define HWIO_OEM_CONFIG0_WDOG_EN_BMSK                                                                     0x4000
#define HWIO_OEM_CONFIG0_WDOG_EN_SHFT                                                                         14
#define HWIO_OEM_CONFIG0_PBL_FDL_TIMEOUT_RESET_FEATURE_ENABLE_BMSK                                        0x2000
#define HWIO_OEM_CONFIG0_PBL_FDL_TIMEOUT_RESET_FEATURE_ENABLE_SHFT                                            13
#define HWIO_OEM_CONFIG0_SW_FUSE_PROG_DISABLE_BMSK                                                        0x1000
#define HWIO_OEM_CONFIG0_SW_FUSE_PROG_DISABLE_SHFT                                                            12
#define HWIO_OEM_CONFIG0_SPI_CLK_BOOT_FREQ_BMSK                                                            0x800
#define HWIO_OEM_CONFIG0_SPI_CLK_BOOT_FREQ_SHFT                                                               11
#define HWIO_OEM_CONFIG0_PBL_QSPI_BOOT_EDL_ENABLED_BMSK                                                    0x400
#define HWIO_OEM_CONFIG0_PBL_QSPI_BOOT_EDL_ENABLED_SHFT                                                       10
#define HWIO_OEM_CONFIG0_FAST_BOOT_BMSK                                                                    0x3e0
#define HWIO_OEM_CONFIG0_FAST_BOOT_SHFT                                                                        5
#define HWIO_OEM_CONFIG0_SDCC_ADMA_DISABLE_BMSK                                                             0x10
#define HWIO_OEM_CONFIG0_SDCC_ADMA_DISABLE_SHFT                                                                4
#define HWIO_OEM_CONFIG0_FORCE_USB_BOOT_GPIO_DISABLE_BMSK                                                    0x8
#define HWIO_OEM_CONFIG0_FORCE_USB_BOOT_GPIO_DISABLE_SHFT                                                      3
#define HWIO_OEM_CONFIG0_FORCE_DLOAD_DISABLE_BMSK                                                            0x4
#define HWIO_OEM_CONFIG0_FORCE_DLOAD_DISABLE_SHFT                                                              2
#define HWIO_OEM_CONFIG0_ENUM_TIMEOUT_BMSK                                                                   0x2
#define HWIO_OEM_CONFIG0_ENUM_TIMEOUT_SHFT                                                                     1
#define HWIO_OEM_CONFIG0_E_DLOAD_DISABLE_BMSK                                                                0x1
#define HWIO_OEM_CONFIG0_E_DLOAD_DISABLE_SHFT                                                                  0

#define HWIO_OEM_CONFIG1_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x304)
#define HWIO_OEM_CONFIG1_RMSK                                                                         0xffffffff
#define HWIO_OEM_CONFIG1_IN                    \
                in_dword(HWIO_OEM_CONFIG1_ADDR)
#define HWIO_OEM_CONFIG1_INM(m)            \
                in_dword_masked(HWIO_OEM_CONFIG1_ADDR, m)
#define HWIO_OEM_CONFIG1_OEM_CONFIG_63_32_BMSK                                                        0xffffffff
#define HWIO_OEM_CONFIG1_OEM_CONFIG_63_32_SHFT                                                                 0

#define HWIO_OEM_CONFIG2_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x308)
#define HWIO_OEM_CONFIG2_RMSK                                                                         0xffffffff
#define HWIO_OEM_CONFIG2_IN                    \
                in_dword(HWIO_OEM_CONFIG2_ADDR)
#define HWIO_OEM_CONFIG2_INM(m)            \
                in_dword_masked(HWIO_OEM_CONFIG2_ADDR, m)
#define HWIO_OEM_CONFIG2_DISABLE_RSA_BMSK                                                             0x80000000
#define HWIO_OEM_CONFIG2_DISABLE_RSA_SHFT                                                                     31
#define HWIO_OEM_CONFIG2_EKU_ENFORCEMENT_EN_BMSK                                                      0x40000000
#define HWIO_OEM_CONFIG2_EKU_ENFORCEMENT_EN_SHFT                                                              30
#define HWIO_OEM_CONFIG2_OEM_CONFIG_93_82_BMSK                                                        0x3ffc0000
#define HWIO_OEM_CONFIG2_OEM_CONFIG_93_82_SHFT                                                                18
#define HWIO_OEM_CONFIG2_SP_ARI_SUSPENSION_FEATURE_ENABLE_BMSK                                           0x20000
#define HWIO_OEM_CONFIG2_SP_ARI_SUSPENSION_FEATURE_ENABLE_SHFT                                                17
#define HWIO_OEM_CONFIG2_SP_ARI_TEST_MODE_FEATURE_ENABLE_BMSK                                            0x10000
#define HWIO_OEM_CONFIG2_SP_ARI_TEST_MODE_FEATURE_ENABLE_SHFT                                                 16
#define HWIO_OEM_CONFIG2_SPARE_REG3_SECURE_BMSK                                                           0x8000
#define HWIO_OEM_CONFIG2_SPARE_REG3_SECURE_SHFT                                                               15
#define HWIO_OEM_CONFIG2_SPARE_REG2_SECURE_BMSK                                                           0x4000
#define HWIO_OEM_CONFIG2_SPARE_REG2_SECURE_SHFT                                                               14
#define HWIO_OEM_CONFIG2_SPARE_REG1_SECURE_BMSK                                                           0x2000
#define HWIO_OEM_CONFIG2_SPARE_REG1_SECURE_SHFT                                                               13
#define HWIO_OEM_CONFIG2_SPARE_REG0_SECURE_BMSK                                                           0x1000
#define HWIO_OEM_CONFIG2_SPARE_REG0_SECURE_SHFT                                                               12
#define HWIO_OEM_CONFIG2_OEM_CONFIG_75_BMSK                                                                0x800
#define HWIO_OEM_CONFIG2_OEM_CONFIG_75_SHFT                                                                   11
#define HWIO_OEM_CONFIG2_SPU_IAR_ENABLED_BMSK                                                              0x400
#define HWIO_OEM_CONFIG2_SPU_IAR_ENABLED_SHFT                                                                 10
#define HWIO_OEM_CONFIG2_OEM_CONFIG_73_72_BMSK                                                             0x300
#define HWIO_OEM_CONFIG2_OEM_CONFIG_73_72_SHFT                                                                 8
#define HWIO_OEM_CONFIG2_TZ_SW_CRYPTO_FIPS_OVERRIDE_BMSK                                                    0x80
#define HWIO_OEM_CONFIG2_TZ_SW_CRYPTO_FIPS_OVERRIDE_SHFT                                                       7
#define HWIO_OEM_CONFIG2_SP_FIPS_OVERRIDE_BMSK                                                              0x40
#define HWIO_OEM_CONFIG2_SP_FIPS_OVERRIDE_SHFT                                                                 6
#define HWIO_OEM_CONFIG2_MODEM_CRYPTO_FIPS_ENABLE_BMSK                                                      0x20
#define HWIO_OEM_CONFIG2_MODEM_CRYPTO_FIPS_ENABLE_SHFT                                                         5
#define HWIO_OEM_CONFIG2_TZ_SW_CRYPTO_FIPS_ENABLE_BMSK                                                      0x10
#define HWIO_OEM_CONFIG2_TZ_SW_CRYPTO_FIPS_ENABLE_SHFT                                                         4
#define HWIO_OEM_CONFIG2_SP_FIPS_ENABLE_BMSK                                                                 0x8
#define HWIO_OEM_CONFIG2_SP_FIPS_ENABLE_SHFT                                                                   3
#define HWIO_OEM_CONFIG2_SPU_ENABLEMENT_OPTION_BMSK                                                          0x6
#define HWIO_OEM_CONFIG2_SPU_ENABLEMENT_OPTION_SHFT                                                            1
#define HWIO_OEM_CONFIG2_OEM_CONFIG_64_BMSK                                                                  0x1
#define HWIO_OEM_CONFIG2_OEM_CONFIG_64_SHFT                                                                    0

#define HWIO_OEM_CONFIG3_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x30c)
#define HWIO_OEM_CONFIG3_RMSK                                                                         0xffffffff
#define HWIO_OEM_CONFIG3_IN                    \
                in_dword(HWIO_OEM_CONFIG3_ADDR)
#define HWIO_OEM_CONFIG3_INM(m)            \
                in_dword_masked(HWIO_OEM_CONFIG3_ADDR, m)
#define HWIO_OEM_CONFIG3_OEM_PRODUCT_ID_BMSK                                                          0xffff0000
#define HWIO_OEM_CONFIG3_OEM_PRODUCT_ID_SHFT                                                                  16
#define HWIO_OEM_CONFIG3_OEM_HW_ID_BMSK                                                                   0xffff
#define HWIO_OEM_CONFIG3_OEM_HW_ID_SHFT                                                                        0

#define HWIO_OEM_CONFIG4_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x310)
#define HWIO_OEM_CONFIG4_RMSK                                                                         0xffffffff
#define HWIO_OEM_CONFIG4_IN                    \
                in_dword(HWIO_OEM_CONFIG4_ADDR)
#define HWIO_OEM_CONFIG4_INM(m)            \
                in_dword_masked(HWIO_OEM_CONFIG4_ADDR, m)
#define HWIO_OEM_CONFIG4_PERIPH_VID_BMSK                                                              0xffff0000
#define HWIO_OEM_CONFIG4_PERIPH_VID_SHFT                                                                      16
#define HWIO_OEM_CONFIG4_PERIPH_PID_BMSK                                                                  0xffff
#define HWIO_OEM_CONFIG4_PERIPH_PID_SHFT                                                                       0

#define HWIO_OEM_CONFIG5_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x314)
#define HWIO_OEM_CONFIG5_RMSK                                                                         0xffffffff
#define HWIO_OEM_CONFIG5_IN                    \
                in_dword(HWIO_OEM_CONFIG5_ADDR)
#define HWIO_OEM_CONFIG5_INM(m)            \
                in_dword_masked(HWIO_OEM_CONFIG5_ADDR, m)
#define HWIO_OEM_CONFIG5_OEM_CONFIG_191_168_BMSK                                                      0xffffff00
#define HWIO_OEM_CONFIG5_OEM_CONFIG_191_168_SHFT                                                               8
#define HWIO_OEM_CONFIG5_ANTI_ROLLBACK_FEATURE_EN_BMSK                                                      0xff
#define HWIO_OEM_CONFIG5_ANTI_ROLLBACK_FEATURE_EN_SHFT                                                         0

#define HWIO_OEM_CONFIG6_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x318)
#define HWIO_OEM_CONFIG6_RMSK                                                                         0xffffffff
#define HWIO_OEM_CONFIG6_IN                    \
                in_dword(HWIO_OEM_CONFIG6_ADDR)
#define HWIO_OEM_CONFIG6_INM(m)            \
                in_dword_masked(HWIO_OEM_CONFIG6_ADDR, m)
#define HWIO_OEM_CONFIG6_OEM_CONFIG_223_192_BMSK                                                      0xffffffff
#define HWIO_OEM_CONFIG6_OEM_CONFIG_223_192_SHFT                                                               0

#define HWIO_OEM_CONFIG7_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x31c)
#define HWIO_OEM_CONFIG7_RMSK                                                                         0xffffffff
#define HWIO_OEM_CONFIG7_IN                    \
                in_dword(HWIO_OEM_CONFIG7_ADDR)
#define HWIO_OEM_CONFIG7_INM(m)            \
                in_dword_masked(HWIO_OEM_CONFIG7_ADDR, m)
#define HWIO_OEM_CONFIG7_OEM_CONFIG_255_224_BMSK                                                      0xffffffff
#define HWIO_OEM_CONFIG7_OEM_CONFIG_255_224_SHFT                                                               0

#define HWIO_OEM_CONFIG8_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x320)
#define HWIO_OEM_CONFIG8_RMSK                                                                         0xffffffff
#define HWIO_OEM_CONFIG8_IN                    \
                in_dword(HWIO_OEM_CONFIG8_ADDR)
#define HWIO_OEM_CONFIG8_INM(m)            \
                in_dword_masked(HWIO_OEM_CONFIG8_ADDR, m)
#define HWIO_OEM_CONFIG8_OEM_CONFIG_287_256_BMSK                                                      0xffffffff
#define HWIO_OEM_CONFIG8_OEM_CONFIG_287_256_SHFT                                                               0

#define HWIO_OEM_CONFIG9_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x324)
#define HWIO_OEM_CONFIG9_RMSK                                                                         0xffffffff
#define HWIO_OEM_CONFIG9_IN                    \
                in_dword(HWIO_OEM_CONFIG9_ADDR)
#define HWIO_OEM_CONFIG9_INM(m)            \
                in_dword_masked(HWIO_OEM_CONFIG9_ADDR, m)
#define HWIO_OEM_CONFIG9_OEM_CONFIG_319_288_BMSK                                                      0xffffffff
#define HWIO_OEM_CONFIG9_OEM_CONFIG_319_288_SHFT                                                               0

#define HWIO_ANTI_ROLLBACK0_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x400)
#define HWIO_ANTI_ROLLBACK0_RMSK                                                                      0xffffffff
#define HWIO_ANTI_ROLLBACK0_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK0_ADDR)
#define HWIO_ANTI_ROLLBACK0_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK0_ADDR, m)
#define HWIO_ANTI_ROLLBACK0_ANTI_ROLLBACK_31_24_BMSK                                                  0xff000000
#define HWIO_ANTI_ROLLBACK0_ANTI_ROLLBACK_31_24_SHFT                                                          24
#define HWIO_ANTI_ROLLBACK0_QTI_TME_FW_BMSK                                                             0xffffff
#define HWIO_ANTI_ROLLBACK0_QTI_TME_FW_SHFT                                                                    0

#define HWIO_ANTI_ROLLBACK1_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x404)
#define HWIO_ANTI_ROLLBACK1_RMSK                                                                      0xffffffff
#define HWIO_ANTI_ROLLBACK1_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK1_ADDR)
#define HWIO_ANTI_ROLLBACK1_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK1_ADDR, m)
#define HWIO_ANTI_ROLLBACK1_DEVICE_PRGM_BMSK                                                          0xffff0000
#define HWIO_ANTI_ROLLBACK1_DEVICE_PRGM_SHFT                                                                  16
#define HWIO_ANTI_ROLLBACK1_QTI_XBL_SC_BMSK                                                               0xffff
#define HWIO_ANTI_ROLLBACK1_QTI_XBL_SC_SHFT                                                                    0

#define HWIO_ANTI_ROLLBACK2_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x408)
#define HWIO_ANTI_ROLLBACK2_RMSK                                                                      0xffffffff
#define HWIO_ANTI_ROLLBACK2_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK2_ADDR)
#define HWIO_ANTI_ROLLBACK2_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK2_ADDR, m)
#define HWIO_ANTI_ROLLBACK2_OEM_MISC_BMSK                                                             0xffff0000
#define HWIO_ANTI_ROLLBACK2_OEM_MISC_SHFT                                                                     16
#define HWIO_ANTI_ROLLBACK2_QTI_MISC_BMSK                                                                 0xffff
#define HWIO_ANTI_ROLLBACK2_QTI_MISC_SHFT                                                                      0

#define HWIO_ANTI_ROLLBACK3_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x40c)
#define HWIO_ANTI_ROLLBACK3_RMSK                                                                      0xffffffff
#define HWIO_ANTI_ROLLBACK3_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK3_ADDR)
#define HWIO_ANTI_ROLLBACK3_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK3_ADDR, m)
#define HWIO_ANTI_ROLLBACK3_XBL_CFG_BMSK                                                              0xffff0000
#define HWIO_ANTI_ROLLBACK3_XBL_CFG_SHFT                                                                      16
#define HWIO_ANTI_ROLLBACK3_ANTI_ROLLBACK_111_101_BMSK                                                    0xffe0
#define HWIO_ANTI_ROLLBACK3_ANTI_ROLLBACK_111_101_SHFT                                                         5
#define HWIO_ANTI_ROLLBACK3_QTI_DEBUG_POLICY_BMSK                                                           0x1f
#define HWIO_ANTI_ROLLBACK3_QTI_DEBUG_POLICY_SHFT                                                              0

#define HWIO_ANTI_ROLLBACK4_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x410)
#define HWIO_ANTI_ROLLBACK4_RMSK                                                                      0xffffffff
#define HWIO_ANTI_ROLLBACK4_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK4_ADDR)
#define HWIO_ANTI_ROLLBACK4_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK4_ADDR, m)
#define HWIO_ANTI_ROLLBACK4_ANTI_ROLLBACK_159_152_BMSK                                                0xff000000
#define HWIO_ANTI_ROLLBACK4_ANTI_ROLLBACK_159_152_SHFT                                                        24
#define HWIO_ANTI_ROLLBACK4_QTI_CPUCP_BMSK                                                              0xff0000
#define HWIO_ANTI_ROLLBACK4_QTI_CPUCP_SHFT                                                                    16
#define HWIO_ANTI_ROLLBACK4_ANTI_ROLLBACK_143_136_BMSK                                                    0xff00
#define HWIO_ANTI_ROLLBACK4_ANTI_ROLLBACK_143_136_SHFT                                                         8
#define HWIO_ANTI_ROLLBACK4_QTI_SHRM_BMSK                                                                   0xff
#define HWIO_ANTI_ROLLBACK4_QTI_SHRM_SHFT                                                                      0

#define HWIO_ANTI_ROLLBACK5_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x414)
#define HWIO_ANTI_ROLLBACK5_RMSK                                                                      0xffffffff
#define HWIO_ANTI_ROLLBACK5_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK5_ADDR)
#define HWIO_ANTI_ROLLBACK5_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK5_ADDR, m)
#define HWIO_ANTI_ROLLBACK5_QTI_QSEE_BMSK                                                             0xffff8000
#define HWIO_ANTI_ROLLBACK5_QTI_QSEE_SHFT                                                                     15
#define HWIO_ANTI_ROLLBACK5_ANTI_ROLLBACK_174_167_BMSK                                                    0x7f80
#define HWIO_ANTI_ROLLBACK5_ANTI_ROLLBACK_174_167_SHFT                                                         7
#define HWIO_ANTI_ROLLBACK5_QTI_AOP_FW_BMSK                                                                 0x7f
#define HWIO_ANTI_ROLLBACK5_QTI_AOP_FW_SHFT                                                                    0

#define HWIO_ANTI_ROLLBACK6_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x418)
#define HWIO_ANTI_ROLLBACK6_RMSK                                                                      0xffffffff
#define HWIO_ANTI_ROLLBACK6_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK6_ADDR)
#define HWIO_ANTI_ROLLBACK6_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK6_ADDR, m)
#define HWIO_ANTI_ROLLBACK6_ANTI_ROLLBACK_223_209_BMSK                                                0xfffe0000
#define HWIO_ANTI_ROLLBACK6_ANTI_ROLLBACK_223_209_SHFT                                                        17
#define HWIO_ANTI_ROLLBACK6_QTI_QHEE_BMSK                                                                0x1ffff
#define HWIO_ANTI_ROLLBACK6_QTI_QHEE_SHFT                                                                      0

#define HWIO_ANTI_ROLLBACK7_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x41c)
#define HWIO_ANTI_ROLLBACK7_RMSK                                                                      0xffffffff
#define HWIO_ANTI_ROLLBACK7_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK7_ADDR)
#define HWIO_ANTI_ROLLBACK7_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK7_ADDR, m)
#define HWIO_ANTI_ROLLBACK7_UEFI_BMSK                                                                 0xffffff00
#define HWIO_ANTI_ROLLBACK7_UEFI_SHFT                                                                          8
#define HWIO_ANTI_ROLLBACK7_VMS_BMSK                                                                        0xff
#define HWIO_ANTI_ROLLBACK7_VMS_SHFT                                                                           0

#define HWIO_ANTI_ROLLBACK8_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x420)
#define HWIO_ANTI_ROLLBACK8_RMSK                                                                      0xffffffff
#define HWIO_ANTI_ROLLBACK8_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK8_ADDR)
#define HWIO_ANTI_ROLLBACK8_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK8_ADDR, m)
#define HWIO_ANTI_ROLLBACK8_ANTI_ROLLBACK_287_283_BMSK                                                0xf8000000
#define HWIO_ANTI_ROLLBACK8_ANTI_ROLLBACK_287_283_SHFT                                                        27
#define HWIO_ANTI_ROLLBACK8_TZ_DEVCFG_BMSK                                                             0x7ff0000
#define HWIO_ANTI_ROLLBACK8_TZ_DEVCFG_SHFT                                                                    16
#define HWIO_ANTI_ROLLBACK8_ANTI_ROLLBACK_271_264_BMSK                                                    0xff00
#define HWIO_ANTI_ROLLBACK8_ANTI_ROLLBACK_271_264_SHFT                                                         8
#define HWIO_ANTI_ROLLBACK8_ABL_BMSK                                                                        0xff
#define HWIO_ANTI_ROLLBACK8_ABL_SHFT                                                                           0

#define HWIO_ANTI_ROLLBACK9_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x424)
#define HWIO_ANTI_ROLLBACK9_RMSK                                                                      0xffffffff
#define HWIO_ANTI_ROLLBACK9_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK9_ADDR)
#define HWIO_ANTI_ROLLBACK9_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK9_ADDR, m)
#define HWIO_ANTI_ROLLBACK9_ANTI_ROLLBACK_319_304_BMSK                                                0xffff0000
#define HWIO_ANTI_ROLLBACK9_ANTI_ROLLBACK_319_304_SHFT                                                        16
#define HWIO_ANTI_ROLLBACK9_MODEM_BMSK                                                                    0xffff
#define HWIO_ANTI_ROLLBACK9_MODEM_SHFT                                                                         0

#define HWIO_ANTI_ROLLBACK10_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x428)
#define HWIO_ANTI_ROLLBACK10_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK10_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK10_ADDR)
#define HWIO_ANTI_ROLLBACK10_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK10_ADDR, m)
#define HWIO_ANTI_ROLLBACK10_PIL_31_0_BMSK                                                            0xffffffff
#define HWIO_ANTI_ROLLBACK10_PIL_31_0_SHFT                                                                     0

#define HWIO_ANTI_ROLLBACK11_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x42c)
#define HWIO_ANTI_ROLLBACK11_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK11_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK11_ADDR)
#define HWIO_ANTI_ROLLBACK11_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK11_ADDR, m)
#define HWIO_ANTI_ROLLBACK11_ANTI_ROLLBACK_383_368_BMSK                                               0xffff0000
#define HWIO_ANTI_ROLLBACK11_ANTI_ROLLBACK_383_368_SHFT                                                       16
#define HWIO_ANTI_ROLLBACK11_PIL_47_32_BMSK                                                               0xffff
#define HWIO_ANTI_ROLLBACK11_PIL_47_32_SHFT                                                                    0

#define HWIO_ANTI_ROLLBACK12_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x430)
#define HWIO_ANTI_ROLLBACK12_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK12_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK12_ADDR)
#define HWIO_ANTI_ROLLBACK12_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK12_ADDR, m)
#define HWIO_ANTI_ROLLBACK12_GPU_MICROCODE_BMSK                                                       0xffff0000
#define HWIO_ANTI_ROLLBACK12_GPU_MICROCODE_SHFT                                                               16
#define HWIO_ANTI_ROLLBACK12_IPA_BMSK                                                                     0xffff
#define HWIO_ANTI_ROLLBACK12_IPA_SHFT                                                                          0

#define HWIO_ANTI_ROLLBACK13_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x434)
#define HWIO_ANTI_ROLLBACK13_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK13_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK13_ADDR)
#define HWIO_ANTI_ROLLBACK13_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK13_ADDR, m)
#define HWIO_ANTI_ROLLBACK13_XBL_SC_EXTENTION_BMSK                                                    0xffff0000
#define HWIO_ANTI_ROLLBACK13_XBL_SC_EXTENTION_SHFT                                                            16
#define HWIO_ANTI_ROLLBACK13_QTI_QUPV3_FW_BMSK                                                            0xffff
#define HWIO_ANTI_ROLLBACK13_QTI_QUPV3_FW_SHFT                                                                 0

#define HWIO_ANTI_ROLLBACK14_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x438)
#define HWIO_ANTI_ROLLBACK14_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK14_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK14_ADDR)
#define HWIO_ANTI_ROLLBACK14_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK14_ADDR, m)
#define HWIO_ANTI_ROLLBACK14_ANTI_ROLLBACK_479_464_BMSK                                               0xffff0000
#define HWIO_ANTI_ROLLBACK14_ANTI_ROLLBACK_479_464_SHFT                                                       16
#define HWIO_ANTI_ROLLBACK14_USB_FW_BMSK                                                                  0xffff
#define HWIO_ANTI_ROLLBACK14_USB_FW_SHFT                                                                       0

#define HWIO_ANTI_ROLLBACK15_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x43c)
#define HWIO_ANTI_ROLLBACK15_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK15_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK15_ADDR)
#define HWIO_ANTI_ROLLBACK15_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK15_ADDR, m)
#define HWIO_ANTI_ROLLBACK15_ANTI_ROLLBACK_511_504_BMSK                                               0xff000000
#define HWIO_ANTI_ROLLBACK15_ANTI_ROLLBACK_511_504_SHFT                                                       24
#define HWIO_ANTI_ROLLBACK15_OEM_TME_FW_BMSK                                                            0xffffff
#define HWIO_ANTI_ROLLBACK15_OEM_TME_FW_SHFT                                                                   0

#define HWIO_ANTI_ROLLBACK16_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x440)
#define HWIO_ANTI_ROLLBACK16_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK16_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK16_ADDR)
#define HWIO_ANTI_ROLLBACK16_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK16_ADDR, m)
#define HWIO_ANTI_ROLLBACK16_ANTI_ROLLBACK_543_533_BMSK                                               0xffe00000
#define HWIO_ANTI_ROLLBACK16_ANTI_ROLLBACK_543_533_SHFT                                                       21
#define HWIO_ANTI_ROLLBACK16_OEM_DEBUG_POLICY_BMSK                                                      0x1f0000
#define HWIO_ANTI_ROLLBACK16_OEM_DEBUG_POLICY_SHFT                                                            16
#define HWIO_ANTI_ROLLBACK16_OEM_XBL_SC_BMSK                                                              0xffff
#define HWIO_ANTI_ROLLBACK16_OEM_XBL_SC_SHFT                                                                   0

#define HWIO_ANTI_ROLLBACK17_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x444)
#define HWIO_ANTI_ROLLBACK17_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK17_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK17_ADDR)
#define HWIO_ANTI_ROLLBACK17_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK17_ADDR, m)
#define HWIO_ANTI_ROLLBACK17_ANTI_ROLLBACK_575_568_BMSK                                               0xff000000
#define HWIO_ANTI_ROLLBACK17_ANTI_ROLLBACK_575_568_SHFT                                                       24
#define HWIO_ANTI_ROLLBACK17_OEM_CPUCP_BMSK                                                             0xff0000
#define HWIO_ANTI_ROLLBACK17_OEM_CPUCP_SHFT                                                                   16
#define HWIO_ANTI_ROLLBACK17_ANTI_ROLLBACK_559_552_BMSK                                                   0xff00
#define HWIO_ANTI_ROLLBACK17_ANTI_ROLLBACK_559_552_SHFT                                                        8
#define HWIO_ANTI_ROLLBACK17_OEM_SHRM_BMSK                                                                  0xff
#define HWIO_ANTI_ROLLBACK17_OEM_SHRM_SHFT                                                                     0

#define HWIO_ANTI_ROLLBACK18_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x448)
#define HWIO_ANTI_ROLLBACK18_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK18_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK18_ADDR)
#define HWIO_ANTI_ROLLBACK18_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK18_ADDR, m)
#define HWIO_ANTI_ROLLBACK18_ANTI_ROLLBACK_607_583_BMSK                                               0xffffff80
#define HWIO_ANTI_ROLLBACK18_ANTI_ROLLBACK_607_583_SHFT                                                        7
#define HWIO_ANTI_ROLLBACK18_OEM_AOP_FW_BMSK                                                                0x7f
#define HWIO_ANTI_ROLLBACK18_OEM_AOP_FW_SHFT                                                                   0

#define HWIO_ANTI_ROLLBACK19_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x44c)
#define HWIO_ANTI_ROLLBACK19_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK19_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK19_ADDR)
#define HWIO_ANTI_ROLLBACK19_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK19_ADDR, m)
#define HWIO_ANTI_ROLLBACK19_OEM_QHEE_14_0_BMSK                                                       0xfffe0000
#define HWIO_ANTI_ROLLBACK19_OEM_QHEE_14_0_SHFT                                                               17
#define HWIO_ANTI_ROLLBACK19_OEM_QSEE_BMSK                                                               0x1ffff
#define HWIO_ANTI_ROLLBACK19_OEM_QSEE_SHFT                                                                     0

#define HWIO_ANTI_ROLLBACK20_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x450)
#define HWIO_ANTI_ROLLBACK20_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK20_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK20_ADDR)
#define HWIO_ANTI_ROLLBACK20_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK20_ADDR, m)
#define HWIO_ANTI_ROLLBACK20_OEM_QUPV3_FW_BMSK                                                        0xffff0000
#define HWIO_ANTI_ROLLBACK20_OEM_QUPV3_FW_SHFT                                                                16
#define HWIO_ANTI_ROLLBACK20_ANTI_ROLLBACK_655_642_BMSK                                                   0xfffc
#define HWIO_ANTI_ROLLBACK20_ANTI_ROLLBACK_655_642_SHFT                                                        2
#define HWIO_ANTI_ROLLBACK20_OEM_QHEE_16_15_BMSK                                                             0x3
#define HWIO_ANTI_ROLLBACK20_OEM_QHEE_16_15_SHFT                                                               0

#define HWIO_ANTI_ROLLBACK21_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x454)
#define HWIO_ANTI_ROLLBACK21_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK21_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK21_ADDR)
#define HWIO_ANTI_ROLLBACK21_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK21_ADDR, m)
#define HWIO_ANTI_ROLLBACK21_ANTI_ROLLBACK_703_672_BMSK                                               0xffffffff
#define HWIO_ANTI_ROLLBACK21_ANTI_ROLLBACK_703_672_SHFT                                                        0

#define HWIO_ANTI_ROLLBACK22_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x458)
#define HWIO_ANTI_ROLLBACK22_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK22_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK22_ADDR)
#define HWIO_ANTI_ROLLBACK22_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK22_ADDR, m)
#define HWIO_ANTI_ROLLBACK22_ANTI_ROLLBACK_735_706_BMSK                                               0xfffffffc
#define HWIO_ANTI_ROLLBACK22_ANTI_ROLLBACK_735_706_SHFT                                                        2
#define HWIO_ANTI_ROLLBACK22_RPMB_KEY_PROVISIONED_BMSK                                                       0x2
#define HWIO_ANTI_ROLLBACK22_RPMB_KEY_PROVISIONED_SHFT                                                         1
#define HWIO_ANTI_ROLLBACK22_SIMLOCK_BMSK                                                                    0x1
#define HWIO_ANTI_ROLLBACK22_SIMLOCK_SHFT                                                                      0

#define HWIO_ANTI_ROLLBACK23_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x45c)
#define HWIO_ANTI_ROLLBACK23_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK23_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK23_ADDR)
#define HWIO_ANTI_ROLLBACK23_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK23_ADDR, m)
#define HWIO_ANTI_ROLLBACK23_ANTI_ROLLBACK_767_736_BMSK                                               0xffffffff
#define HWIO_ANTI_ROLLBACK23_ANTI_ROLLBACK_767_736_SHFT                                                        0

#define HWIO_ANTI_ROLLBACK24_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x460)
#define HWIO_ANTI_ROLLBACK24_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK24_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK24_ADDR)
#define HWIO_ANTI_ROLLBACK24_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK24_ADDR, m)
#define HWIO_ANTI_ROLLBACK24_ANTI_ROLLBACK_799_768_BMSK                                               0xffffffff
#define HWIO_ANTI_ROLLBACK24_ANTI_ROLLBACK_799_768_SHFT                                                        0

#define HWIO_ANTI_ROLLBACK25_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x464)
#define HWIO_ANTI_ROLLBACK25_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK25_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK25_ADDR)
#define HWIO_ANTI_ROLLBACK25_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK25_ADDR, m)
#define HWIO_ANTI_ROLLBACK25_ANTI_ROLLBACK_831_800_BMSK                                               0xffffffff
#define HWIO_ANTI_ROLLBACK25_ANTI_ROLLBACK_831_800_SHFT                                                        0

#define HWIO_ANTI_ROLLBACK26_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x468)
#define HWIO_ANTI_ROLLBACK26_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK26_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK26_ADDR)
#define HWIO_ANTI_ROLLBACK26_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK26_ADDR, m)
#define HWIO_ANTI_ROLLBACK26_ANTI_ROLLBACK_863_832_BMSK                                               0xffffffff
#define HWIO_ANTI_ROLLBACK26_ANTI_ROLLBACK_863_832_SHFT                                                        0

#define HWIO_ANTI_ROLLBACK27_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x46c)
#define HWIO_ANTI_ROLLBACK27_RMSK                                                                     0xffffffff
#define HWIO_ANTI_ROLLBACK27_IN                    \
                in_dword(HWIO_ANTI_ROLLBACK27_ADDR)
#define HWIO_ANTI_ROLLBACK27_INM(m)            \
                in_dword_masked(HWIO_ANTI_ROLLBACK27_ADDR, m)
#define HWIO_ANTI_ROLLBACK27_ANTI_ROLLBACK_895_864_BMSK                                               0xffffffff
#define HWIO_ANTI_ROLLBACK27_ANTI_ROLLBACK_895_864_SHFT                                                        0

#define HWIO_PK_HASH0_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x500)
#define HWIO_PK_HASH0_RMSK                                                                            0xffffffff
#define HWIO_PK_HASH0_IN                    \
                in_dword(HWIO_PK_HASH0_ADDR)
#define HWIO_PK_HASH0_INM(m)            \
                in_dword_masked(HWIO_PK_HASH0_ADDR, m)
#define HWIO_PK_HASH0_PK_HASH_31_0_BMSK                                                               0xffffffff
#define HWIO_PK_HASH0_PK_HASH_31_0_SHFT                                                                        0

#define HWIO_PK_HASH1_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x504)
#define HWIO_PK_HASH1_RMSK                                                                              0xffffff
#define HWIO_PK_HASH1_IN                    \
                in_dword(HWIO_PK_HASH1_ADDR)
#define HWIO_PK_HASH1_INM(m)            \
                in_dword_masked(HWIO_PK_HASH1_ADDR, m)
#define HWIO_PK_HASH1_PK_HASH_55_32_BMSK                                                                0xffffff
#define HWIO_PK_HASH1_PK_HASH_55_32_SHFT                                                                       0

#define HWIO_PK_HASH2_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x508)
#define HWIO_PK_HASH2_RMSK                                                                            0xffffffff
#define HWIO_PK_HASH2_IN                    \
                in_dword(HWIO_PK_HASH2_ADDR)
#define HWIO_PK_HASH2_INM(m)            \
                in_dword_masked(HWIO_PK_HASH2_ADDR, m)
#define HWIO_PK_HASH2_PK_HASH_87_56_BMSK                                                              0xffffffff
#define HWIO_PK_HASH2_PK_HASH_87_56_SHFT                                                                       0

#define HWIO_PK_HASH3_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x50c)
#define HWIO_PK_HASH3_RMSK                                                                              0xffffff
#define HWIO_PK_HASH3_IN                    \
                in_dword(HWIO_PK_HASH3_ADDR)
#define HWIO_PK_HASH3_INM(m)            \
                in_dword_masked(HWIO_PK_HASH3_ADDR, m)
#define HWIO_PK_HASH3_PK_HASH_111_88_BMSK                                                               0xffffff
#define HWIO_PK_HASH3_PK_HASH_111_88_SHFT                                                                      0

#define HWIO_PK_HASH4_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x510)
#define HWIO_PK_HASH4_RMSK                                                                            0xffffffff
#define HWIO_PK_HASH4_IN                    \
                in_dword(HWIO_PK_HASH4_ADDR)
#define HWIO_PK_HASH4_INM(m)            \
                in_dword_masked(HWIO_PK_HASH4_ADDR, m)
#define HWIO_PK_HASH4_PK_HASH_143_112_BMSK                                                            0xffffffff
#define HWIO_PK_HASH4_PK_HASH_143_112_SHFT                                                                     0

#define HWIO_PK_HASH5_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x514)
#define HWIO_PK_HASH5_RMSK                                                                              0xffffff
#define HWIO_PK_HASH5_IN                    \
                in_dword(HWIO_PK_HASH5_ADDR)
#define HWIO_PK_HASH5_INM(m)            \
                in_dword_masked(HWIO_PK_HASH5_ADDR, m)
#define HWIO_PK_HASH5_PK_HASH_167_144_BMSK                                                              0xffffff
#define HWIO_PK_HASH5_PK_HASH_167_144_SHFT                                                                     0

#define HWIO_PK_HASH6_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x518)
#define HWIO_PK_HASH6_RMSK                                                                            0xffffffff
#define HWIO_PK_HASH6_IN                    \
                in_dword(HWIO_PK_HASH6_ADDR)
#define HWIO_PK_HASH6_INM(m)            \
                in_dword_masked(HWIO_PK_HASH6_ADDR, m)
#define HWIO_PK_HASH6_PK_HASH_199_168_BMSK                                                            0xffffffff
#define HWIO_PK_HASH6_PK_HASH_199_168_SHFT                                                                     0

#define HWIO_PK_HASH7_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x51c)
#define HWIO_PK_HASH7_RMSK                                                                              0xffffff
#define HWIO_PK_HASH7_IN                    \
                in_dword(HWIO_PK_HASH7_ADDR)
#define HWIO_PK_HASH7_INM(m)            \
                in_dword_masked(HWIO_PK_HASH7_ADDR, m)
#define HWIO_PK_HASH7_PK_HASH_223_200_BMSK                                                              0xffffff
#define HWIO_PK_HASH7_PK_HASH_223_200_SHFT                                                                     0

#define HWIO_PK_HASH8_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x520)
#define HWIO_PK_HASH8_RMSK                                                                            0xffffffff
#define HWIO_PK_HASH8_IN                    \
                in_dword(HWIO_PK_HASH8_ADDR)
#define HWIO_PK_HASH8_INM(m)            \
                in_dword_masked(HWIO_PK_HASH8_ADDR, m)
#define HWIO_PK_HASH8_PK_HASH_255_224_BMSK                                                            0xffffffff
#define HWIO_PK_HASH8_PK_HASH_255_224_SHFT                                                                     0

#define HWIO_PK_HASH9_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x524)
#define HWIO_PK_HASH9_RMSK                                                                              0xffffff
#define HWIO_PK_HASH9_IN                    \
                in_dword(HWIO_PK_HASH9_ADDR)
#define HWIO_PK_HASH9_INM(m)            \
                in_dword_masked(HWIO_PK_HASH9_ADDR, m)
#define HWIO_PK_HASH9_PK_HASH_279_256_BMSK                                                              0xffffff
#define HWIO_PK_HASH9_PK_HASH_279_256_SHFT                                                                     0

#define HWIO_PK_HASH10_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x528)
#define HWIO_PK_HASH10_RMSK                                                                           0xffffffff
#define HWIO_PK_HASH10_IN                    \
                in_dword(HWIO_PK_HASH10_ADDR)
#define HWIO_PK_HASH10_INM(m)            \
                in_dword_masked(HWIO_PK_HASH10_ADDR, m)
#define HWIO_PK_HASH10_PK_HASH_311_280_BMSK                                                           0xffffffff
#define HWIO_PK_HASH10_PK_HASH_311_280_SHFT                                                                    0

#define HWIO_PK_HASH11_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x52c)
#define HWIO_PK_HASH11_RMSK                                                                             0xffffff
#define HWIO_PK_HASH11_IN                    \
                in_dword(HWIO_PK_HASH11_ADDR)
#define HWIO_PK_HASH11_INM(m)            \
                in_dword_masked(HWIO_PK_HASH11_ADDR, m)
#define HWIO_PK_HASH11_PK_HASH_335_312_BMSK                                                             0xffffff
#define HWIO_PK_HASH11_PK_HASH_335_312_SHFT                                                                    0

#define HWIO_PK_HASH12_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x530)
#define HWIO_PK_HASH12_RMSK                                                                           0xffffffff
#define HWIO_PK_HASH12_IN                    \
                in_dword(HWIO_PK_HASH12_ADDR)
#define HWIO_PK_HASH12_INM(m)            \
                in_dword_masked(HWIO_PK_HASH12_ADDR, m)
#define HWIO_PK_HASH12_PK_HASH_367_336_BMSK                                                           0xffffffff
#define HWIO_PK_HASH12_PK_HASH_367_336_SHFT                                                                    0

#define HWIO_PK_HASH13_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x534)
#define HWIO_PK_HASH13_RMSK                                                                             0xffffff
#define HWIO_PK_HASH13_IN                    \
                in_dword(HWIO_PK_HASH13_ADDR)
#define HWIO_PK_HASH13_INM(m)            \
                in_dword_masked(HWIO_PK_HASH13_ADDR, m)
#define HWIO_PK_HASH13_PK_HASH_391_368_BMSK                                                             0xffffff
#define HWIO_PK_HASH13_PK_HASH_391_368_SHFT                                                                    0

#define HWIO_PK_HASH14_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x538)
#define HWIO_PK_HASH14_RMSK                                                                           0xffffffff
#define HWIO_PK_HASH14_IN                    \
                in_dword(HWIO_PK_HASH14_ADDR)
#define HWIO_PK_HASH14_INM(m)            \
                in_dword_masked(HWIO_PK_HASH14_ADDR, m)
#define HWIO_PK_HASH14_PK_HASH_423_392_BMSK                                                           0xffffffff
#define HWIO_PK_HASH14_PK_HASH_423_392_SHFT                                                                    0

#define HWIO_PK_HASH15_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x53c)
#define HWIO_PK_HASH15_RMSK                                                                             0xffffff
#define HWIO_PK_HASH15_IN                    \
                in_dword(HWIO_PK_HASH15_ADDR)
#define HWIO_PK_HASH15_INM(m)            \
                in_dword_masked(HWIO_PK_HASH15_ADDR, m)
#define HWIO_PK_HASH15_PK_HASH_447_424_BMSK                                                             0xffffff
#define HWIO_PK_HASH15_PK_HASH_447_424_SHFT                                                                    0

#define HWIO_PK_HASH16_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x540)
#define HWIO_PK_HASH16_RMSK                                                                           0xffffffff
#define HWIO_PK_HASH16_IN                    \
                in_dword(HWIO_PK_HASH16_ADDR)
#define HWIO_PK_HASH16_INM(m)            \
                in_dword_masked(HWIO_PK_HASH16_ADDR, m)
#define HWIO_PK_HASH16_PK_HASH_479_448_BMSK                                                           0xffffffff
#define HWIO_PK_HASH16_PK_HASH_479_448_SHFT                                                                    0

#define HWIO_PK_HASH17_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x544)
#define HWIO_PK_HASH17_RMSK                                                                             0xffffff
#define HWIO_PK_HASH17_IN                    \
                in_dword(HWIO_PK_HASH17_ADDR)
#define HWIO_PK_HASH17_INM(m)            \
                in_dword_masked(HWIO_PK_HASH17_ADDR, m)
#define HWIO_PK_HASH17_PK_HASH_503_480_BMSK                                                             0xffffff
#define HWIO_PK_HASH17_PK_HASH_503_480_SHFT                                                                    0

#define HWIO_PK_HASH18_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x548)
#define HWIO_PK_HASH18_RMSK                                                                           0xffffffff
#define HWIO_PK_HASH18_IN                    \
                in_dword(HWIO_PK_HASH18_ADDR)
#define HWIO_PK_HASH18_INM(m)            \
                in_dword_masked(HWIO_PK_HASH18_ADDR, m)
#define HWIO_PK_HASH18_RSVD0_BMSK                                                                     0xffffff00
#define HWIO_PK_HASH18_RSVD0_SHFT                                                                              8
#define HWIO_PK_HASH18_PK_HASH_511_504_BMSK                                                                 0xff
#define HWIO_PK_HASH18_PK_HASH_511_504_SHFT                                                                    0

#define HWIO_PK_HASH19_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x54c)
#define HWIO_PK_HASH19_RMSK                                                                             0xffffff
#define HWIO_PK_HASH19_IN                    \
                in_dword(HWIO_PK_HASH19_ADDR)
#define HWIO_PK_HASH19_INM(m)            \
                in_dword_masked(HWIO_PK_HASH19_ADDR, m)
#define HWIO_PK_HASH19_RSVD0_BMSK                                                                       0xffffff
#define HWIO_PK_HASH19_RSVD0_SHFT                                                                              0

#define HWIO_BOOT_CONFIG_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x600)
#define HWIO_BOOT_CONFIG_RMSK                                                                              0x1ff
#define HWIO_BOOT_CONFIG_IN                    \
                in_dword(HWIO_BOOT_CONFIG_ADDR)
#define HWIO_BOOT_CONFIG_INM(m)            \
                in_dword_masked(HWIO_BOOT_CONFIG_ADDR, m)
#define HWIO_BOOT_CONFIG_APPS_PBL_BOOT_SPEED_BMSK                                                          0x180
#define HWIO_BOOT_CONFIG_APPS_PBL_BOOT_SPEED_SHFT                                                              7
#define HWIO_BOOT_CONFIG_RSVD_BMSK                                                                          0x40
#define HWIO_BOOT_CONFIG_RSVD_SHFT                                                                             6
#define HWIO_BOOT_CONFIG_FAST_BOOT_BMSK                                                                     0x3e
#define HWIO_BOOT_CONFIG_FAST_BOOT_SHFT                                                                        1
#define HWIO_BOOT_CONFIG_WDOG_EN_BMSK                                                                        0x1
#define HWIO_BOOT_CONFIG_WDOG_EN_SHFT                                                                          0

#define HWIO_SECURE_BOOT_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x604)
#define HWIO_SECURE_BOOT_RMSK                                                                              0x1ff
#define HWIO_SECURE_BOOT_IN                    \
                in_dword(HWIO_SECURE_BOOT_ADDR)
#define HWIO_SECURE_BOOT_INM(m)            \
                in_dword_masked(HWIO_SECURE_BOOT_ADDR, m)
#define HWIO_SECURE_BOOT_FUSE_SRC_BMSK                                                                     0x100
#define HWIO_SECURE_BOOT_FUSE_SRC_SHFT                                                                         8
#define HWIO_SECURE_BOOT_RSVD_7_BMSK                                                                        0x80
#define HWIO_SECURE_BOOT_RSVD_7_SHFT                                                                           7
#define HWIO_SECURE_BOOT_USE_SERIAL_NUM_BMSK                                                                0x40
#define HWIO_SECURE_BOOT_USE_SERIAL_NUM_SHFT                                                                   6
#define HWIO_SECURE_BOOT_AUTH_EN_BMSK                                                                       0x20
#define HWIO_SECURE_BOOT_AUTH_EN_SHFT                                                                          5
#define HWIO_SECURE_BOOT_PK_HASH_IN_FUSE_BMSK                                                               0x10
#define HWIO_SECURE_BOOT_PK_HASH_IN_FUSE_SHFT                                                                  4
#define HWIO_SECURE_BOOT_ROM_PK_HASH_INDEX_BMSK                                                              0xf
#define HWIO_SECURE_BOOT_ROM_PK_HASH_INDEX_SHFT                                                                0

#define HWIO_CHIP_UNIQUE_ID_0_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x610)
#define HWIO_CHIP_UNIQUE_ID_0_RMSK                                                                    0xffffffff
#define HWIO_CHIP_UNIQUE_ID_0_IN                    \
                in_dword(HWIO_CHIP_UNIQUE_ID_0_ADDR)
#define HWIO_CHIP_UNIQUE_ID_0_INM(m)            \
                in_dword_masked(HWIO_CHIP_UNIQUE_ID_0_ADDR, m)
#define HWIO_CHIP_UNIQUE_ID_0_SERIAL_NUM_BMSK                                                         0xffffffff
#define HWIO_CHIP_UNIQUE_ID_0_SERIAL_NUM_SHFT                                                                  0

#define HWIO_CHIP_UNIQUE_ID_1_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x614)
#define HWIO_CHIP_UNIQUE_ID_1_RMSK                                                                    0xffffffff
#define HWIO_CHIP_UNIQUE_ID_1_IN                    \
                in_dword(HWIO_CHIP_UNIQUE_ID_1_ADDR)
#define HWIO_CHIP_UNIQUE_ID_1_INM(m)            \
                in_dword_masked(HWIO_CHIP_UNIQUE_ID_1_ADDR, m)
#define HWIO_CHIP_UNIQUE_ID_1_CHIP_ID_BMSK                                                            0xffffffff
#define HWIO_CHIP_UNIQUE_ID_1_CHIP_ID_SHFT                                                                     0

#define HWIO_MRC_0_ADDR                                                                               (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x630)
#define HWIO_MRC_0_RMSK                                                                               0xffffffff
#define HWIO_MRC_0_IN                    \
                in_dword(HWIO_MRC_0_ADDR)
#define HWIO_MRC_0_INM(m)            \
                in_dword_masked(HWIO_MRC_0_ADDR, m)
#define HWIO_MRC_0_MRC_31_25_BMSK                                                                     0xfe000000
#define HWIO_MRC_0_MRC_31_25_SHFT                                                                             25
#define HWIO_MRC_0_OEM_ROOT_CERT_REVOCATION_LIST_BMSK                                                  0x1e00000
#define HWIO_MRC_0_OEM_ROOT_CERT_REVOCATION_LIST_SHFT                                                         21
#define HWIO_MRC_0_OEM_ROOT_CERT_ACTIVATION_LIST_BMSK                                                   0x1e0000
#define HWIO_MRC_0_OEM_ROOT_CERT_ACTIVATION_LIST_SHFT                                                         17
#define HWIO_MRC_0_MRC_BMSK                                                                              0x1ff00
#define HWIO_MRC_0_MRC_SHFT                                                                                    8
#define HWIO_MRC_0_QC_ROOT_CERT_REVOCATION_LIST_BMSK                                                        0xf0
#define HWIO_MRC_0_QC_ROOT_CERT_REVOCATION_LIST_SHFT                                                           4
#define HWIO_MRC_0_QC_ROOT_CERT_ACTIVATION_LIST_BMSK                                                         0xf
#define HWIO_MRC_0_QC_ROOT_CERT_ACTIVATION_LIST_SHFT                                                           0

#define HWIO_MRC_1_ADDR                                                                               (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x634)
#define HWIO_MRC_1_RMSK                                                                               0xffffffff
#define HWIO_MRC_1_IN                    \
                in_dword(HWIO_MRC_1_ADDR)
#define HWIO_MRC_1_INM(m)            \
                in_dword_masked(HWIO_MRC_1_ADDR, m)
#define HWIO_MRC_1_MRC_63_32_BMSK                                                                     0xffffffff
#define HWIO_MRC_1_MRC_63_32_SHFT                                                                              0

#define HWIO_OEM_HW_ID_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x700)
#define HWIO_OEM_HW_ID_RMSK                                                                               0xffff
#define HWIO_OEM_HW_ID_IN                    \
                in_dword(HWIO_OEM_HW_ID_ADDR)
#define HWIO_OEM_HW_ID_INM(m)            \
                in_dword_masked(HWIO_OEM_HW_ID_ADDR, m)
#define HWIO_OEM_HW_ID_OEM_ID_BMSK                                                                        0xffff
#define HWIO_OEM_HW_ID_OEM_ID_SHFT                                                                             0

#define HWIO_OEM_PRODUCT_ID_ADDR                                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x704)
#define HWIO_OEM_PRODUCT_ID_RMSK                                                                          0xffff
#define HWIO_OEM_PRODUCT_ID_IN                    \
                in_dword(HWIO_OEM_PRODUCT_ID_ADDR)
#define HWIO_OEM_PRODUCT_ID_INM(m)            \
                in_dword_masked(HWIO_OEM_PRODUCT_ID_ADDR, m)
#define HWIO_OEM_PRODUCT_ID_OEM_PRODUCT_ID_BMSK                                                           0xffff
#define HWIO_OEM_PRODUCT_ID_OEM_PRODUCT_ID_SHFT                                                                0

#define HWIO_PROVATTEMPTCOUNTER_ADDR                                                                  (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x708)
#define HWIO_PROVATTEMPTCOUNTER_RMSK                                                                        0xff
#define HWIO_PROVATTEMPTCOUNTER_IN                    \
                in_dword(HWIO_PROVATTEMPTCOUNTER_ADDR)
#define HWIO_PROVATTEMPTCOUNTER_INM(m)            \
                in_dword_masked(HWIO_PROVATTEMPTCOUNTER_ADDR, m)
#define HWIO_PROVATTEMPTCOUNTER_PROVATTEMPTCOUNTER_BMSK                                                     0xff
#define HWIO_PROVATTEMPTCOUNTER_PROVATTEMPTCOUNTER_SHFT                                                        0

#define HWIO_CHIPPROVKEYVERSION_ADDR                                                                  (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x70c)
#define HWIO_CHIPPROVKEYVERSION_RMSK                                                                        0xff
#define HWIO_CHIPPROVKEYVERSION_IN                    \
                in_dword(HWIO_CHIPPROVKEYVERSION_ADDR)
#define HWIO_CHIPPROVKEYVERSION_INM(m)            \
                in_dword_masked(HWIO_CHIPPROVKEYVERSION_ADDR, m)
#define HWIO_CHIPPROVKEYVERSION_CHIPPROVKEYVERSION_BMSK                                                     0xff
#define HWIO_CHIPPROVKEYVERSION_CHIPPROVKEYVERSION_SHFT                                                        0

#define HWIO_QCCHIPFAMPROVROOTKEYSETVECTOR_ADDR                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x710)
#define HWIO_QCCHIPFAMPROVROOTKEYSETVECTOR_RMSK                                                             0xff
#define HWIO_QCCHIPFAMPROVROOTKEYSETVECTOR_IN                    \
                in_dword(HWIO_QCCHIPFAMPROVROOTKEYSETVECTOR_ADDR)
#define HWIO_QCCHIPFAMPROVROOTKEYSETVECTOR_INM(m)            \
                in_dword_masked(HWIO_QCCHIPFAMPROVROOTKEYSETVECTOR_ADDR, m)
#define HWIO_QCCHIPFAMPROVROOTKEYSETVECTOR_QCCHIPFAMPROVROOTKEYSETVECTOR_BMSK                               0xff
#define HWIO_QCCHIPFAMPROVROOTKEYSETVECTOR_QCCHIPFAMPROVROOTKEYSETVECTOR_SHFT                                  0

#define HWIO_PROVKEYIDUSED_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x714)
#define HWIO_PROVKEYIDUSED_RMSK                                                                             0xff
#define HWIO_PROVKEYIDUSED_IN                    \
                in_dword(HWIO_PROVKEYIDUSED_ADDR)
#define HWIO_PROVKEYIDUSED_INM(m)            \
                in_dword_masked(HWIO_PROVKEYIDUSED_ADDR, m)
#define HWIO_PROVKEYIDUSED_PROVKEYIDUSED_BMSK                                                               0xff
#define HWIO_PROVKEYIDUSED_PROVKEYIDUSED_SHFT                                                                  0

#define HWIO_OEM_SECURE_DEBUG_POLICY1_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x718)
#define HWIO_OEM_SECURE_DEBUG_POLICY1_RMSK                                                                   0x1
#define HWIO_OEM_SECURE_DEBUG_POLICY1_IN                    \
                in_dword(HWIO_OEM_SECURE_DEBUG_POLICY1_ADDR)
#define HWIO_OEM_SECURE_DEBUG_POLICY1_INM(m)            \
                in_dword_masked(HWIO_OEM_SECURE_DEBUG_POLICY1_ADDR, m)
#define HWIO_OEM_SECURE_DEBUG_POLICY1_DISALLOWSOCDEBUG_BMSK                                                  0x1
#define HWIO_OEM_SECURE_DEBUG_POLICY1_DISALLOWSOCDEBUG_SHFT                                                    0

#define HWIO_OEM_SECURE_DEBUG_POLICY2_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x71c)
#define HWIO_OEM_SECURE_DEBUG_POLICY2_RMSK                                                                   0x1
#define HWIO_OEM_SECURE_DEBUG_POLICY2_IN                    \
                in_dword(HWIO_OEM_SECURE_DEBUG_POLICY2_ADDR)
#define HWIO_OEM_SECURE_DEBUG_POLICY2_INM(m)            \
                in_dword_masked(HWIO_OEM_SECURE_DEBUG_POLICY2_ADDR, m)
#define HWIO_OEM_SECURE_DEBUG_POLICY2_ENFORCEOEMAUTHZONSOCDEBUG_BMSK                                         0x1
#define HWIO_OEM_SECURE_DEBUG_POLICY2_ENFORCEOEMAUTHZONSOCDEBUG_SHFT                                           0

#define HWIO_OEM_SECURE_UPDATE_POLICY1_ADDR                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x720)
#define HWIO_OEM_SECURE_UPDATE_POLICY1_RMSK                                                                  0x1
#define HWIO_OEM_SECURE_UPDATE_POLICY1_IN                    \
                in_dword(HWIO_OEM_SECURE_UPDATE_POLICY1_ADDR)
#define HWIO_OEM_SECURE_UPDATE_POLICY1_INM(m)            \
                in_dword_masked(HWIO_OEM_SECURE_UPDATE_POLICY1_ADDR, m)
#define HWIO_OEM_SECURE_UPDATE_POLICY1_DISABLEROMPATCH_BMSK                                                  0x1
#define HWIO_OEM_SECURE_UPDATE_POLICY1_DISABLEROMPATCH_SHFT                                                    0

#define HWIO_OEM_SECURE_UPDATE_POLICY2_ADDR                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x724)
#define HWIO_OEM_SECURE_UPDATE_POLICY2_RMSK                                                                  0x1
#define HWIO_OEM_SECURE_UPDATE_POLICY2_IN                    \
                in_dword(HWIO_OEM_SECURE_UPDATE_POLICY2_ADDR)
#define HWIO_OEM_SECURE_UPDATE_POLICY2_INM(m)            \
                in_dword_masked(HWIO_OEM_SECURE_UPDATE_POLICY2_ADDR, m)
#define HWIO_OEM_SECURE_UPDATE_POLICY2_ENFORCEOEMAUTHZONFUSEOVERRIDES_BMSK                                   0x1
#define HWIO_OEM_SECURE_UPDATE_POLICY2_ENFORCEOEMAUTHZONFUSEOVERRIDES_SHFT                                     0

#define HWIO_OEM_SECURE_UPADATE_POLICY3_ADDR                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x728)
#define HWIO_OEM_SECURE_UPADATE_POLICY3_RMSK                                                                 0x1
#define HWIO_OEM_SECURE_UPADATE_POLICY3_IN                    \
                in_dword(HWIO_OEM_SECURE_UPADATE_POLICY3_ADDR)
#define HWIO_OEM_SECURE_UPADATE_POLICY3_INM(m)            \
                in_dword_masked(HWIO_OEM_SECURE_UPADATE_POLICY3_ADDR, m)
#define HWIO_OEM_SECURE_UPADATE_POLICY3_ENFORCEOEMAUTHZONROMPATCH_BMSK                                       0x1
#define HWIO_OEM_SECURE_UPADATE_POLICY3_ENFORCEOEMAUTHZONROMPATCH_SHFT                                         0

#define HWIO_OEM_SECURE_BOOT_POLICY1_ADDR                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x72c)
#define HWIO_OEM_SECURE_BOOT_POLICY1_RMSK                                                                    0x1
#define HWIO_OEM_SECURE_BOOT_POLICY1_IN                    \
                in_dword(HWIO_OEM_SECURE_BOOT_POLICY1_ADDR)
#define HWIO_OEM_SECURE_BOOT_POLICY1_INM(m)            \
                in_dword_masked(HWIO_OEM_SECURE_BOOT_POLICY1_ADDR, m)
#define HWIO_OEM_SECURE_BOOT_POLICY1_ACTIVATESECURITYPOLICY_BMSK                                             0x1
#define HWIO_OEM_SECURE_BOOT_POLICY1_ACTIVATESECURITYPOLICY_SHFT                                               0

#define HWIO_OEM_SECURE_BOOT_POLICY2_ADDR                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x730)
#define HWIO_OEM_SECURE_BOOT_POLICY2_RMSK                                                                    0x1
#define HWIO_OEM_SECURE_BOOT_POLICY2_IN                    \
                in_dword(HWIO_OEM_SECURE_BOOT_POLICY2_ADDR)
#define HWIO_OEM_SECURE_BOOT_POLICY2_INM(m)            \
                in_dword_masked(HWIO_OEM_SECURE_BOOT_POLICY2_ADDR, m)
#define HWIO_OEM_SECURE_BOOT_POLICY2_ENFORCEOEMAUTHZONSOCBOOT_BMSK                                           0x1
#define HWIO_OEM_SECURE_BOOT_POLICY2_ENFORCEOEMAUTHZONSOCBOOT_SHFT                                             0

#define HWIO_OEM_SECURE_BOOT_POLICY3_ADDR                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x734)
#define HWIO_OEM_SECURE_BOOT_POLICY3_RMSK                                                                    0x1
#define HWIO_OEM_SECURE_BOOT_POLICY3_IN                    \
                in_dword(HWIO_OEM_SECURE_BOOT_POLICY3_ADDR)
#define HWIO_OEM_SECURE_BOOT_POLICY3_INM(m)            \
                in_dword_masked(HWIO_OEM_SECURE_BOOT_POLICY3_ADDR, m)
#define HWIO_OEM_SECURE_BOOT_POLICY3_PREVENTFULLMRCREVOCATION_BMSK                                           0x1
#define HWIO_OEM_SECURE_BOOT_POLICY3_PREVENTFULLMRCREVOCATION_SHFT                                             0

#define HWIO_TME_LCS_0_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x73c)
#define HWIO_TME_LCS_0_RMSK                                                                           0xffffffff
#define HWIO_TME_LCS_0_IN                    \
                in_dword(HWIO_TME_LCS_0_ADDR)
#define HWIO_TME_LCS_0_INM(m)            \
                in_dword_masked(HWIO_TME_LCS_0_ADDR, m)
#define HWIO_TME_LCS_0_TME_LCS_RSVD_31_8_BMSK                                                         0xffffff00
#define HWIO_TME_LCS_0_TME_LCS_RSVD_31_8_SHFT                                                                  8
#define HWIO_TME_LCS_0_LCS_RSVD_BMSK                                                                        0xf0
#define HWIO_TME_LCS_0_LCS_RSVD_SHFT                                                                           4
#define HWIO_TME_LCS_0_LCS_BMSK                                                                              0xf
#define HWIO_TME_LCS_0_LCS_SHFT                                                                                0

#define HWIO_TME_LCS_1_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x740)
#define HWIO_TME_LCS_1_RMSK                                                                           0xffffffff
#define HWIO_TME_LCS_1_IN                    \
                in_dword(HWIO_TME_LCS_1_ADDR)
#define HWIO_TME_LCS_1_INM(m)            \
                in_dword_masked(HWIO_TME_LCS_1_ADDR, m)
#define HWIO_TME_LCS_1_TME_LCS_63_32_BMSK                                                             0xffffffff
#define HWIO_TME_LCS_1_TME_LCS_63_32_SHFT                                                                      0

#define HWIO_JTAG_ID_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x744)
#define HWIO_JTAG_ID_RMSK                                                                             0xffffffff
#define HWIO_JTAG_ID_IN                    \
                in_dword(HWIO_JTAG_ID_ADDR)
#define HWIO_JTAG_ID_INM(m)            \
                in_dword_masked(HWIO_JTAG_ID_ADDR, m)
#define HWIO_JTAG_ID_JTAG_ID_BMSK                                                                     0xffffffff
#define HWIO_JTAG_ID_JTAG_ID_SHFT                                                                              0

#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x770)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RMSK                                                            0xffffffff
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_IN                    \
                in_dword(HWIO_SEQ_DEBUG_VECTOR_REMAP_0_ADDR)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_INM(m)            \
                in_dword_masked(HWIO_SEQ_DEBUG_VECTOR_REMAP_0_ADDR, m)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD31_BMSK                                                     0x80000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD31_SHFT                                                             31
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_APPS_NIDEN_BMSK                                                 0x40000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_APPS_NIDEN_SHFT                                                         30
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_APPS_DBGEN_BMSK                                                 0x20000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_APPS_DBGEN_SHFT                                                         29
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_GPU_PRIVATE_DBGEN_BMSK                                          0x10000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_GPU_PRIVATE_DBGEN_SHFT                                                  28
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_APB2JTAG_REENABLE_BMSK                                           0x8000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_APB2JTAG_REENABLE_SHFT                                                  27
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_PIMEM_NIDEN_BMSK                                                 0x4000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_PIMEM_NIDEN_SHFT                                                        26
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_PIMEM_DBGEN_BMSK                                                 0x2000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_PIMEM_DBGEN_SHFT                                                        25
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_QSEE_NIDEN_BMSK                                                  0x1000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_QSEE_NIDEN_SHFT                                                         24
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_QSEE_DBGEN_BMSK                                                   0x800000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_QSEE_DBGEN_SHFT                                                         23
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_MSS_VECTOR_NIDEN_BMSK                                             0x400000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_MSS_VECTOR_NIDEN_SHFT                                                   22
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_MSS_VECTOR_DBGEN_BMSK                                             0x200000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_MSS_VECTOR_DBGEN_SHFT                                                   21
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_CPUCP_NIDEN_BMSK                                                  0x100000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_CPUCP_NIDEN_SHFT                                                        20
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_CPUCP_DBGEN_BMSK                                                   0x80000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_CPUCP_DBGEN_SHFT                                                        19
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_SHRM_NIDEN_BMSK                                                    0x40000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_SHRM_NIDEN_SHFT                                                         18
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_SHRM_DBGEN_BMSK                                                    0x20000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_SHRM_DBGEN_SHFT                                                         17
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_AOP_NIDEN_BMSK                                                     0x10000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_AOP_NIDEN_SHFT                                                          16
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_AOP_DBGEN_BMSK                                                      0x8000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_AOP_DBGEN_SHFT                                                          15
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_TMERAM_NIDEN_BMSK                                                   0x4000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_TMERAM_NIDEN_SHFT                                                       14
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_TMERAM_DBGEN_BMSK                                                   0x2000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_TMERAM_DBGEN_SHFT                                                       13
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_TMEROM_NIDEN_BMSK                                                   0x1000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_TMEROM_NIDEN_SHFT                                                       12
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_TMEROM_DBGEN_BMSK                                                    0x800
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_TMEROM_DBGEN_SHFT                                                       11
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD10_BMSK                                                          0x400
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD10_SHFT                                                             10
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD9_BMSK                                                           0x200
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD9_SHFT                                                               9
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD8_BMSK                                                           0x100
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD8_SHFT                                                               8
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD7_BMSK                                                            0x80
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD7_SHFT                                                               7
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_TIC_REENABLE_BMSK                                                     0x40
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_TIC_REENABLE_SHFT                                                        6
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD5_BMSK                                                            0x20
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD5_SHFT                                                               5
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD4_BMSK                                                            0x10
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD4_SHFT                                                               4
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD3_BMSK                                                             0x8
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD3_SHFT                                                               3
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_SECURE_BOOT_AUTH_EN_DISABLE_BMSK                                       0x4
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_SECURE_BOOT_AUTH_EN_DISABLE_SHFT                                         2
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD1_BMSK                                                             0x2
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD1_SHFT                                                               1
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD0_BMSK                                                             0x1
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_0_RSVD0_SHFT                                                               0

#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x774)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_RMSK                                                            0xffffffff
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_IN                    \
                in_dword(HWIO_SEQ_DEBUG_VECTOR_REMAP_1_ADDR)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_INM(m)            \
                in_dword_masked(HWIO_SEQ_DEBUG_VECTOR_REMAP_1_ADDR, m)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_JTAG_INSTR_DISABLE_3_BMSK                                       0x80000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_JTAG_INSTR_DISABLE_3_SHFT                                               31
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_JTAG_INSTR_DISABLE_2_BMSK                                       0x40000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_JTAG_INSTR_DISABLE_2_SHFT                                               30
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_JTAG_INSTR_DISABLE_1_BMSK                                       0x20000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_JTAG_INSTR_DISABLE_1_SHFT                                               29
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_JTAG_INSTR_DISABLE_0_BMSK                                       0x10000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_JTAG_INSTR_DISABLE_0_SHFT                                               28
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DISABLE_SEC_BOOT_GPIO_BMSK                                       0x8000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DISABLE_SEC_BOOT_GPIO_SHFT                                              27
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_SP_DISABLE_BMSK                                                  0x4000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_SP_DISABLE_SHFT                                                         26
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_SMMU_SCANDUMP_BMSK                                               0x2000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_SMMU_SCANDUMP_SHFT                                                      25
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_EUD_DISABLE_BMSK                                                 0x1000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_EUD_DISABLE_SHFT                                                        24
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DCC_DISABLE_BMSK                                                  0x800000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DCC_DISABLE_SHFT                                                        23
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DEBUGBUS_DISABLE_BMSK                                             0x400000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DEBUGBUS_DISABLE_SHFT                                                   22
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DDRSS_SCANDUMP_BMSK                                               0x200000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DDRSS_SCANDUMP_SHFT                                                     21
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_APPS_SCANDUMP_BMSK                                                0x100000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_APPS_SCANDUMP_SHFT                                                      20
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DAP_NIDEN_BMSK                                                     0x80000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DAP_NIDEN_SHFT                                                          19
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DAP_DBGEN_BMSK                                                     0x40000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DAP_DBGEN_SHFT                                                          18
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_GPU_NIDEN_BMSK                                                     0x20000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_GPU_NIDEN_SHFT                                                          17
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_GPU_DBGEN_BMSK                                                     0x10000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_GPU_DBGEN_SHFT                                                          16
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DDRSS_NIDEN_BMSK                                                    0x8000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DDRSS_NIDEN_SHFT                                                        15
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DDRSS_DBGEN_BMSK                                                    0x4000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_DDRSS_DBGEN_SHFT                                                        14
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_MDSS_NIDEN_BMSK                                                     0x2000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_MDSS_NIDEN_SHFT                                                         13
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_MDSS_DBGEN_BMSK                                                     0x1000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_MDSS_DBGEN_SHFT                                                         12
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_IRIS_NIDEN_BMSK                                                      0x800
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_IRIS_NIDEN_SHFT                                                         11
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_IRIS_DBGEN_BMSK                                                      0x400
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_IRIS_DBGEN_SHFT                                                         10
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_TURINR_NIDEN_BMSK                                                    0x200
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_TURINR_NIDEN_SHFT                                                        9
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_TURING_DBGEN_BMSK                                                    0x100
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_TURING_DBGEN_SHFT                                                        8
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_LPASS_NIDEN_BMSK                                                      0x80
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_LPASS_NIDEN_SHFT                                                         7
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_LPASS_DBGEN_BMSK                                                      0x40
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_LPASS_DBGEN_SHFT                                                         6
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_TITAN_NIDEN_BMSK                                                      0x20
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_TITAN_NIDEN_SHFT                                                         5
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_TITAN_DBGEN_BMSK                                                      0x10
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_TITAN_DBGEN_SHFT                                                         4
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_SSC_NIDEN_BMSK                                                         0x8
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_SSC_NIDEN_SHFT                                                           3
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_SSC_DBGEN_BMSK                                                         0x4
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_SSC_DBGEN_SHFT                                                           2
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_MSS_SCALAR_NIDEN_BMSK                                                  0x2
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_MSS_SCALAR_NIDEN_SHFT                                                    1
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_MSS_SCALAR_DBGEN_BMSK                                                  0x1
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_1_MSS_SCALAR_DBGEN_SHFT                                                    0

#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x778)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_RMSK                                                            0xffffffff
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_IN                    \
                in_dword(HWIO_SEQ_DEBUG_VECTOR_REMAP_2_ADDR)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_INM(m)            \
                in_dword_masked(HWIO_SEQ_DEBUG_VECTOR_REMAP_2_ADDR, m)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_17_BMSK                              0x80000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_17_SHFT                                      31
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_16_BMSK                              0x40000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_16_SHFT                                      30
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_15_BMSK                              0x20000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_15_SHFT                                      29
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_14_BMSK                              0x10000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_14_SHFT                                      28
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_13_BMSK                               0x8000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_13_SHFT                                      27
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_12_BMSK                               0x4000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_12_SHFT                                      26
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_11_BMSK                               0x2000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_11_SHFT                                      25
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_10_BMSK                               0x1000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_10_SHFT                                      24
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_9_BMSK                                 0x800000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_9_SHFT                                       23
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_8_BMSK                                 0x400000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_8_SHFT                                       22
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_7_BMSK                                 0x200000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_7_SHFT                                       21
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_6_BMSK                                 0x100000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_6_SHFT                                       20
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_5_BMSK                                  0x80000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_5_SHFT                                       19
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_4_BMSK                                  0x40000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_4_SHFT                                       18
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_3_BMSK                                  0x20000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_3_SHFT                                       17
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_2_BMSK                                  0x10000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_2_SHFT                                       16
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_1_BMSK                                   0x8000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_1_SHFT                                       15
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_0_BMSK                                   0x4000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_GENERIC_INSTR_DISABLE_0_SHFT                                       14
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_17_BMSK                                          0x2000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_17_SHFT                                              13
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_16_BMSK                                          0x1000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_16_SHFT                                              12
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_15_BMSK                                           0x800
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_15_SHFT                                              11
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_14_BMSK                                           0x400
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_14_SHFT                                              10
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_13_BMSK                                           0x200
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_13_SHFT                                               9
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_12_BMSK                                           0x100
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_12_SHFT                                               8
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_11_BMSK                                            0x80
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_11_SHFT                                               7
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_10_BMSK                                            0x40
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_10_SHFT                                               6
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_9_BMSK                                             0x20
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_9_SHFT                                                5
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_8_BMSK                                             0x10
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_8_SHFT                                                4
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_7_BMSK                                              0x8
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_7_SHFT                                                3
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_6_BMSK                                              0x4
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_6_SHFT                                                2
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_5_BMSK                                              0x2
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_5_SHFT                                                1
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_4_BMSK                                              0x1
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_2_JTAG_INSTR_DISABLE_4_SHFT                                                0

#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x77c)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_RMSK                                                            0xffffffff
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_IN                    \
                in_dword(HWIO_SEQ_DEBUG_VECTOR_REMAP_3_ADDR)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_INM(m)            \
                in_dword_masked(HWIO_SEQ_DEBUG_VECTOR_REMAP_3_ADDR, m)
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_RSVD127_BMSK                                                    0x80000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_RSVD127_SHFT                                                            31
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_FEATURE_CONFIG_GLOBAL_ENABLE_BMSK                               0x40000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_FEATURE_CONFIG_GLOBAL_ENABLE_SHFT                                       30
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_15_BMSK                             0x20000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_15_SHFT                                     29
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_14_BMSK                             0x10000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_14_SHFT                                     28
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_13_BMSK                              0x8000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_13_SHFT                                     27
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_12_BMSK                              0x4000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_12_SHFT                                     26
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_11_BMSK                              0x2000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_11_SHFT                                     25
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_10_BMSK                              0x1000000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_10_SHFT                                     24
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_9_BMSK                                0x800000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_9_SHFT                                      23
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_8_BMSK                                0x400000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_8_SHFT                                      22
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_7_BMSK                                0x200000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_7_SHFT                                      21
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_6_BMSK                                0x100000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_6_SHFT                                      20
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_5_BMSK                                 0x80000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_5_SHFT                                      19
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_4_BMSK                                 0x40000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_4_SHFT                                      18
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_3_BMSK                                 0x20000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_3_SHFT                                      17
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_2_BMSK                                 0x10000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_2_SHFT                                      16
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_1_BMSK                                  0x8000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_1_SHFT                                      15
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_0_BMSK                                  0x4000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_SEC_TAP_ACCESS_DISABLE_0_SHFT                                      14
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_31_BMSK                                  0x2000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_31_SHFT                                      13
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_30_BMSK                                  0x1000
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_30_SHFT                                      12
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_29_BMSK                                   0x800
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_29_SHFT                                      11
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_28_BMSK                                   0x400
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_28_SHFT                                      10
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_27_BMSK                                   0x200
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_27_SHFT                                       9
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_26_BMSK                                   0x100
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_26_SHFT                                       8
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_25_BMSK                                    0x80
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_25_SHFT                                       7
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_24_BMSK                                    0x40
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_24_SHFT                                       6
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_23_BMSK                                    0x20
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_23_SHFT                                       5
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_22_BMSK                                    0x10
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_22_SHFT                                       4
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_21_BMSK                                     0x8
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_21_SHFT                                       3
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_20_BMSK                                     0x4
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_20_SHFT                                       2
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_19_BMSK                                     0x2
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_19_SHFT                                       1
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_18_BMSK                                     0x1
#define HWIO_SEQ_DEBUG_VECTOR_REMAP_3_JTAG_GENERIC_INSTR_DISABLE_18_SHFT                                       0

#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_ADDR                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x780)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RMSK                                                     0xffffffff
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_IN                    \
                in_dword(HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_ADDR)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_INM(m)            \
                in_dword_masked(HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_ADDR, m)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD31_BMSK                                              0x80000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD31_SHFT                                                      31
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_APPS_NIDEN_BMSK                                          0x40000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_APPS_NIDEN_SHFT                                                  30
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_APPS_DBGEN_BMSK                                          0x20000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_APPS_DBGEN_SHFT                                                  29
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_GPU_PRIVATE_DBGEN_BMSK                                   0x10000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_GPU_PRIVATE_DBGEN_SHFT                                           28
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_APB2JTAG_REENABLE_BMSK                                    0x8000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_APB2JTAG_REENABLE_SHFT                                           27
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_PIMEM_NIDEN_BMSK                                          0x4000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_PIMEM_NIDEN_SHFT                                                 26
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_PIMEM_DBGEN_BMSK                                          0x2000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_PIMEM_DBGEN_SHFT                                                 25
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_QSEE_NIDEN_BMSK                                           0x1000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_QSEE_NIDEN_SHFT                                                  24
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_QSEE_DBGEN_BMSK                                            0x800000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_QSEE_DBGEN_SHFT                                                  23
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_MSS_VECTOR_NIDEN_BMSK                                      0x400000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_MSS_VECTOR_NIDEN_SHFT                                            22
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_MSS_VECTOR_DBGEN_BMSK                                      0x200000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_MSS_VECTOR_DBGEN_SHFT                                            21
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_CPUCP_NIDEN_BMSK                                           0x100000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_CPUCP_NIDEN_SHFT                                                 20
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_CPUCP_DBGEN_BMSK                                            0x80000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_CPUCP_DBGEN_SHFT                                                 19
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_SHRM_NIDEN_BMSK                                             0x40000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_SHRM_NIDEN_SHFT                                                  18
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_SHRM_DBGEN_BMSK                                             0x20000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_SHRM_DBGEN_SHFT                                                  17
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_AOP_NIDEN_BMSK                                              0x10000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_AOP_NIDEN_SHFT                                                   16
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_AOP_DBGEN_BMSK                                               0x8000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_AOP_DBGEN_SHFT                                                   15
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_TMERAM_NIDEN_BMSK                                            0x4000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_TMERAM_NIDEN_SHFT                                                14
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_TMERAM_DBGEN_BMSK                                            0x2000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_TMERAM_DBGEN_SHFT                                                13
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_TMEROM_NIDEN_BMSK                                            0x1000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_TMEROM_NIDEN_SHFT                                                12
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_TMEROM_DBGEN_BMSK                                             0x800
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_TMEROM_DBGEN_SHFT                                                11
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD10_BMSK                                                   0x400
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD10_SHFT                                                      10
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD9_BMSK                                                    0x200
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD9_SHFT                                                        9
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD8_BMSK                                                    0x100
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD8_SHFT                                                        8
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD7_BMSK                                                     0x80
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD7_SHFT                                                        7
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_TIC_REENABLE_BMSK                                              0x40
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_TIC_REENABLE_SHFT                                                 6
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD5_BMSK                                                     0x20
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD5_SHFT                                                        5
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD4_BMSK                                                     0x10
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD4_SHFT                                                        4
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD3_BMSK                                                      0x8
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD3_SHFT                                                        3
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_SECURE_BOOT_AUTH_EN_DISABLE_BMSK                                0x4
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_SECURE_BOOT_AUTH_EN_DISABLE_SHFT                                  2
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD1_BMSK                                                      0x2
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD1_SHFT                                                        1
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD0_BMSK                                                      0x1
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_0_RSVD0_SHFT                                                        0

#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_ADDR                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x784)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_RMSK                                                     0xffffffff
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_IN                    \
                in_dword(HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_ADDR)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_INM(m)            \
                in_dword_masked(HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_ADDR, m)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_JTAG_INSTR_DISABLE_3_BMSK                                0x80000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_JTAG_INSTR_DISABLE_3_SHFT                                        31
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_JTAG_INSTR_DISABLE_2_BMSK                                0x40000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_JTAG_INSTR_DISABLE_2_SHFT                                        30
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_JTAG_INSTR_DISABLE_1_BMSK                                0x20000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_JTAG_INSTR_DISABLE_1_SHFT                                        29
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_JTAG_INSTR_DISABLE_0_BMSK                                0x10000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_JTAG_INSTR_DISABLE_0_SHFT                                        28
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DISABLE_SEC_BOOT_GPIO_BMSK                                0x8000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DISABLE_SEC_BOOT_GPIO_SHFT                                       27
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_SP_DISABLE_BMSK                                           0x4000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_SP_DISABLE_SHFT                                                  26
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_SMMU_SCANDUMP_BMSK                                        0x2000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_SMMU_SCANDUMP_SHFT                                               25
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_EUD_DISABLE_BMSK                                          0x1000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_EUD_DISABLE_SHFT                                                 24
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DCC_DISABLE_BMSK                                           0x800000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DCC_DISABLE_SHFT                                                 23
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DEBUGBUS_DISABLE_BMSK                                      0x400000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DEBUGBUS_DISABLE_SHFT                                            22
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DDRSS_SCANDUMP_BMSK                                        0x200000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DDRSS_SCANDUMP_SHFT                                              21
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_APPS_SCANDUMP_BMSK                                         0x100000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_APPS_SCANDUMP_SHFT                                               20
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DAP_NIDEN_BMSK                                              0x80000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DAP_NIDEN_SHFT                                                   19
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DAP_DBGEN_BMSK                                              0x40000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DAP_DBGEN_SHFT                                                   18
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_GPU_NIDEN_BMSK                                              0x20000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_GPU_NIDEN_SHFT                                                   17
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_GPU_DBGEN_BMSK                                              0x10000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_GPU_DBGEN_SHFT                                                   16
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DDRSS_NIDEN_BMSK                                             0x8000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DDRSS_NIDEN_SHFT                                                 15
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DDRSS_DBGEN_BMSK                                             0x4000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_DDRSS_DBGEN_SHFT                                                 14
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_MDSS_NIDEN_BMSK                                              0x2000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_MDSS_NIDEN_SHFT                                                  13
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_MDSS_DBGEN_BMSK                                              0x1000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_MDSS_DBGEN_SHFT                                                  12
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_IRIS_NIDEN_BMSK                                               0x800
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_IRIS_NIDEN_SHFT                                                  11
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_IRIS_DBGEN_BMSK                                               0x400
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_IRIS_DBGEN_SHFT                                                  10
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_TURINR_NIDEN_BMSK                                             0x200
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_TURINR_NIDEN_SHFT                                                 9
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_TURING_DBGEN_BMSK                                             0x100
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_TURING_DBGEN_SHFT                                                 8
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_LPASS_NIDEN_BMSK                                               0x80
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_LPASS_NIDEN_SHFT                                                  7
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_LPASS_DBGEN_BMSK                                               0x40
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_LPASS_DBGEN_SHFT                                                  6
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_TITAN_NIDEN_BMSK                                               0x20
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_TITAN_NIDEN_SHFT                                                  5
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_TITAN_DBGEN_BMSK                                               0x10
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_TITAN_DBGEN_SHFT                                                  4
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_SSC_NIDEN_BMSK                                                  0x8
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_SSC_NIDEN_SHFT                                                    3
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_SSC_DBGEN_BMSK                                                  0x4
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_SSC_DBGEN_SHFT                                                    2
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_MSS_SCALAR_NIDEN_BMSK                                           0x2
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_MSS_SCALAR_NIDEN_SHFT                                             1
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_MSS_SCALAR_DBGEN_BMSK                                           0x1
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_1_MSS_SCALAR_DBGEN_SHFT                                             0

#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_ADDR                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x788)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_RMSK                                                     0xffffffff
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_IN                    \
                in_dword(HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_ADDR)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_INM(m)            \
                in_dword_masked(HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_ADDR, m)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_17_BMSK                       0x80000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_17_SHFT                               31
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_16_BMSK                       0x40000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_16_SHFT                               30
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_15_BMSK                       0x20000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_15_SHFT                               29
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_14_BMSK                       0x10000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_14_SHFT                               28
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_13_BMSK                        0x8000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_13_SHFT                               27
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_12_BMSK                        0x4000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_12_SHFT                               26
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_11_BMSK                        0x2000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_11_SHFT                               25
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_10_BMSK                        0x1000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_10_SHFT                               24
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_9_BMSK                          0x800000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_9_SHFT                                23
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_8_BMSK                          0x400000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_8_SHFT                                22
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_7_BMSK                          0x200000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_7_SHFT                                21
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_6_BMSK                          0x100000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_6_SHFT                                20
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_5_BMSK                           0x80000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_5_SHFT                                19
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_4_BMSK                           0x40000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_4_SHFT                                18
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_3_BMSK                           0x20000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_3_SHFT                                17
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_2_BMSK                           0x10000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_2_SHFT                                16
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_1_BMSK                            0x8000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_1_SHFT                                15
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_0_BMSK                            0x4000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_GENERIC_INSTR_DISABLE_0_SHFT                                14
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_17_BMSK                                   0x2000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_17_SHFT                                       13
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_16_BMSK                                   0x1000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_16_SHFT                                       12
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_15_BMSK                                    0x800
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_15_SHFT                                       11
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_14_BMSK                                    0x400
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_14_SHFT                                       10
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_13_BMSK                                    0x200
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_13_SHFT                                        9
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_12_BMSK                                    0x100
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_12_SHFT                                        8
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_11_BMSK                                     0x80
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_11_SHFT                                        7
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_10_BMSK                                     0x40
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_10_SHFT                                        6
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_9_BMSK                                      0x20
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_9_SHFT                                         5
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_8_BMSK                                      0x10
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_8_SHFT                                         4
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_7_BMSK                                       0x8
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_7_SHFT                                         3
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_6_BMSK                                       0x4
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_6_SHFT                                         2
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_5_BMSK                                       0x2
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_5_SHFT                                         1
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_4_BMSK                                       0x1
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_2_JTAG_INSTR_DISABLE_4_SHFT                                         0

#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_ADDR                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x78c)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_RMSK                                                     0xffffffff
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_IN                    \
                in_dword(HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_ADDR)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_INM(m)            \
                in_dword_masked(HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_ADDR, m)
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_RSVD127_BMSK                                             0x80000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_RSVD127_SHFT                                                     31
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_FEATURE_CONFIG_GLOBAL_ENABLE_BMSK                        0x40000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_FEATURE_CONFIG_GLOBAL_ENABLE_SHFT                                30
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_15_BMSK                      0x20000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_15_SHFT                              29
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_14_BMSK                      0x10000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_14_SHFT                              28
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_13_BMSK                       0x8000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_13_SHFT                              27
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_12_BMSK                       0x4000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_12_SHFT                              26
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_11_BMSK                       0x2000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_11_SHFT                              25
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_10_BMSK                       0x1000000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_10_SHFT                              24
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_9_BMSK                         0x800000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_9_SHFT                               23
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_8_BMSK                         0x400000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_8_SHFT                               22
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_7_BMSK                         0x200000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_7_SHFT                               21
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_6_BMSK                         0x100000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_6_SHFT                               20
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_5_BMSK                          0x80000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_5_SHFT                               19
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_4_BMSK                          0x40000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_4_SHFT                               18
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_3_BMSK                          0x20000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_3_SHFT                               17
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_2_BMSK                          0x10000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_2_SHFT                               16
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_1_BMSK                           0x8000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_1_SHFT                               15
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_0_BMSK                           0x4000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_SEC_TAP_ACCESS_DISABLE_0_SHFT                               14
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_31_BMSK                           0x2000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_31_SHFT                               13
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_30_BMSK                           0x1000
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_30_SHFT                               12
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_29_BMSK                            0x800
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_29_SHFT                               11
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_28_BMSK                            0x400
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_28_SHFT                               10
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_27_BMSK                            0x200
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_27_SHFT                                9
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_26_BMSK                            0x100
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_26_SHFT                                8
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_25_BMSK                             0x80
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_25_SHFT                                7
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_24_BMSK                             0x40
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_24_SHFT                                6
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_23_BMSK                             0x20
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_23_SHFT                                5
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_22_BMSK                             0x10
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_22_SHFT                                4
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_21_BMSK                              0x8
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_21_SHFT                                3
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_20_BMSK                              0x4
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_20_SHFT                                2
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_19_BMSK                              0x2
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_19_SHFT                                1
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_18_BMSK                              0x1
#define HWIO_TME_CONSOLIDATED_DEBUG_VECTOR_3_JTAG_GENERIC_INSTR_DISABLE_18_SHFT                                0

#define HWIO_QC_ECC0_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x790)
#define HWIO_QC_ECC0_RMSK                                                                             0xffffffff
#define HWIO_QC_ECC0_IN                    \
                in_dword(HWIO_QC_ECC0_ADDR)
#define HWIO_QC_ECC0_INM(m)            \
                in_dword_masked(HWIO_QC_ECC0_ADDR, m)
#define HWIO_QC_ECC0_QC_ECC_31_0_BMSK                                                                 0xffffffff
#define HWIO_QC_ECC0_QC_ECC_31_0_SHFT                                                                          0

#define HWIO_QC_ECC1_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x794)
#define HWIO_QC_ECC1_RMSK                                                                             0xffffffff
#define HWIO_QC_ECC1_IN                    \
                in_dword(HWIO_QC_ECC1_ADDR)
#define HWIO_QC_ECC1_INM(m)            \
                in_dword_masked(HWIO_QC_ECC1_ADDR, m)
#define HWIO_QC_ECC1_QC_ECC_63_32_BMSK                                                                0xffffffff
#define HWIO_QC_ECC1_QC_ECC_63_32_SHFT                                                                         0

#define HWIO_QC_ECC2_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x798)
#define HWIO_QC_ECC2_RMSK                                                                             0xffffffff
#define HWIO_QC_ECC2_IN                    \
                in_dword(HWIO_QC_ECC2_ADDR)
#define HWIO_QC_ECC2_INM(m)            \
                in_dword_masked(HWIO_QC_ECC2_ADDR, m)
#define HWIO_QC_ECC2_QC_ECC_95_64_BMSK                                                                0xffffffff
#define HWIO_QC_ECC2_QC_ECC_95_64_SHFT                                                                         0

#define HWIO_QC_ECC3_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x79c)
#define HWIO_QC_ECC3_RMSK                                                                             0xffffffff
#define HWIO_QC_ECC3_IN                    \
                in_dword(HWIO_QC_ECC3_ADDR)
#define HWIO_QC_ECC3_INM(m)            \
                in_dword_masked(HWIO_QC_ECC3_ADDR, m)
#define HWIO_QC_ECC3_QC_ECC_127_96_BMSK                                                               0xffffffff
#define HWIO_QC_ECC3_QC_ECC_127_96_SHFT                                                                        0

#define HWIO_QC_ECC4_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7a0)
#define HWIO_QC_ECC4_RMSK                                                                             0xffffffff
#define HWIO_QC_ECC4_IN                    \
                in_dword(HWIO_QC_ECC4_ADDR)
#define HWIO_QC_ECC4_INM(m)            \
                in_dword_masked(HWIO_QC_ECC4_ADDR, m)
#define HWIO_QC_ECC4_QC_ECC_159_128_BMSK                                                              0xffffffff
#define HWIO_QC_ECC4_QC_ECC_159_128_SHFT                                                                       0

#define HWIO_QC_ECC5_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7a4)
#define HWIO_QC_ECC5_RMSK                                                                             0xffffffff
#define HWIO_QC_ECC5_IN                    \
                in_dword(HWIO_QC_ECC5_ADDR)
#define HWIO_QC_ECC5_INM(m)            \
                in_dword_masked(HWIO_QC_ECC5_ADDR, m)
#define HWIO_QC_ECC5_QC_ECC_191_160_BMSK                                                              0xffffffff
#define HWIO_QC_ECC5_QC_ECC_191_160_SHFT                                                                       0

#define HWIO_QC_ECC6_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7a8)
#define HWIO_QC_ECC6_RMSK                                                                             0xffffffff
#define HWIO_QC_ECC6_IN                    \
                in_dword(HWIO_QC_ECC6_ADDR)
#define HWIO_QC_ECC6_INM(m)            \
                in_dword_masked(HWIO_QC_ECC6_ADDR, m)
#define HWIO_QC_ECC6_QC_ECC_223_192_BMSK                                                              0xffffffff
#define HWIO_QC_ECC6_QC_ECC_223_192_SHFT                                                                       0

#define HWIO_QC_ECC7_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7ac)
#define HWIO_QC_ECC7_RMSK                                                                             0xffffffff
#define HWIO_QC_ECC7_IN                    \
                in_dword(HWIO_QC_ECC7_ADDR)
#define HWIO_QC_ECC7_INM(m)            \
                in_dword_masked(HWIO_QC_ECC7_ADDR, m)
#define HWIO_QC_ECC7_QC_ECC_255_224_BMSK                                                              0xffffffff
#define HWIO_QC_ECC7_QC_ECC_255_224_SHFT                                                                       0

#define HWIO_QC_ECC8_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7b0)
#define HWIO_QC_ECC8_RMSK                                                                             0xffffffff
#define HWIO_QC_ECC8_IN                    \
                in_dword(HWIO_QC_ECC8_ADDR)
#define HWIO_QC_ECC8_INM(m)            \
                in_dword_masked(HWIO_QC_ECC8_ADDR, m)
#define HWIO_QC_ECC8_QC_ECC_287_256_BMSK                                                              0xffffffff
#define HWIO_QC_ECC8_QC_ECC_287_256_SHFT                                                                       0

#define HWIO_QC_ECC9_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7b4)
#define HWIO_QC_ECC9_RMSK                                                                             0xffffffff
#define HWIO_QC_ECC9_IN                    \
                in_dword(HWIO_QC_ECC9_ADDR)
#define HWIO_QC_ECC9_INM(m)            \
                in_dword_masked(HWIO_QC_ECC9_ADDR, m)
#define HWIO_QC_ECC9_QC_ECC_319_288_BMSK                                                              0xffffffff
#define HWIO_QC_ECC9_QC_ECC_319_288_SHFT                                                                       0

#define HWIO_QC_ECC10_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7b8)
#define HWIO_QC_ECC10_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC10_IN                    \
                in_dword(HWIO_QC_ECC10_ADDR)
#define HWIO_QC_ECC10_INM(m)            \
                in_dword_masked(HWIO_QC_ECC10_ADDR, m)
#define HWIO_QC_ECC10_QC_ECC_351_320_BMSK                                                             0xffffffff
#define HWIO_QC_ECC10_QC_ECC_351_320_SHFT                                                                      0

#define HWIO_QC_ECC11_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7bc)
#define HWIO_QC_ECC11_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC11_IN                    \
                in_dword(HWIO_QC_ECC11_ADDR)
#define HWIO_QC_ECC11_INM(m)            \
                in_dword_masked(HWIO_QC_ECC11_ADDR, m)
#define HWIO_QC_ECC11_QC_ECC_383_352_BMSK                                                             0xffffffff
#define HWIO_QC_ECC11_QC_ECC_383_352_SHFT                                                                      0

#define HWIO_QC_ECC12_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7c0)
#define HWIO_QC_ECC12_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC12_IN                    \
                in_dword(HWIO_QC_ECC12_ADDR)
#define HWIO_QC_ECC12_INM(m)            \
                in_dword_masked(HWIO_QC_ECC12_ADDR, m)
#define HWIO_QC_ECC12_QC_ECC_415_384_BMSK                                                             0xffffffff
#define HWIO_QC_ECC12_QC_ECC_415_384_SHFT                                                                      0

#define HWIO_QC_ECC13_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7c4)
#define HWIO_QC_ECC13_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC13_IN                    \
                in_dword(HWIO_QC_ECC13_ADDR)
#define HWIO_QC_ECC13_INM(m)            \
                in_dword_masked(HWIO_QC_ECC13_ADDR, m)
#define HWIO_QC_ECC13_QC_ECC_447_416_BMSK                                                             0xffffffff
#define HWIO_QC_ECC13_QC_ECC_447_416_SHFT                                                                      0

#define HWIO_QC_ECC14_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7c8)
#define HWIO_QC_ECC14_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC14_IN                    \
                in_dword(HWIO_QC_ECC14_ADDR)
#define HWIO_QC_ECC14_INM(m)            \
                in_dword_masked(HWIO_QC_ECC14_ADDR, m)
#define HWIO_QC_ECC14_QC_ECC_479_448_BMSK                                                             0xffffffff
#define HWIO_QC_ECC14_QC_ECC_479_448_SHFT                                                                      0

#define HWIO_QC_ECC15_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7cc)
#define HWIO_QC_ECC15_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC15_IN                    \
                in_dword(HWIO_QC_ECC15_ADDR)
#define HWIO_QC_ECC15_INM(m)            \
                in_dword_masked(HWIO_QC_ECC15_ADDR, m)
#define HWIO_QC_ECC15_QC_ECC_511_480_BMSK                                                             0xffffffff
#define HWIO_QC_ECC15_QC_ECC_511_480_SHFT                                                                      0

#define HWIO_QC_ECC16_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7d0)
#define HWIO_QC_ECC16_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC16_IN                    \
                in_dword(HWIO_QC_ECC16_ADDR)
#define HWIO_QC_ECC16_INM(m)            \
                in_dword_masked(HWIO_QC_ECC16_ADDR, m)
#define HWIO_QC_ECC16_QC_ECC_543_512_BMSK                                                             0xffffffff
#define HWIO_QC_ECC16_QC_ECC_543_512_SHFT                                                                      0

#define HWIO_QC_ECC17_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7d4)
#define HWIO_QC_ECC17_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC17_IN                    \
                in_dword(HWIO_QC_ECC17_ADDR)
#define HWIO_QC_ECC17_INM(m)            \
                in_dword_masked(HWIO_QC_ECC17_ADDR, m)
#define HWIO_QC_ECC17_QC_ECC_575_544_BMSK                                                             0xffffffff
#define HWIO_QC_ECC17_QC_ECC_575_544_SHFT                                                                      0

#define HWIO_QC_ECC18_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7d8)
#define HWIO_QC_ECC18_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC18_IN                    \
                in_dword(HWIO_QC_ECC18_ADDR)
#define HWIO_QC_ECC18_INM(m)            \
                in_dword_masked(HWIO_QC_ECC18_ADDR, m)
#define HWIO_QC_ECC18_QC_ECC_607_576_BMSK                                                             0xffffffff
#define HWIO_QC_ECC18_QC_ECC_607_576_SHFT                                                                      0

#define HWIO_QC_ECC19_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7dc)
#define HWIO_QC_ECC19_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC19_IN                    \
                in_dword(HWIO_QC_ECC19_ADDR)
#define HWIO_QC_ECC19_INM(m)            \
                in_dword_masked(HWIO_QC_ECC19_ADDR, m)
#define HWIO_QC_ECC19_QC_ECC_639_608_BMSK                                                             0xffffffff
#define HWIO_QC_ECC19_QC_ECC_639_608_SHFT                                                                      0

#define HWIO_QC_ECC20_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7e0)
#define HWIO_QC_ECC20_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC20_IN                    \
                in_dword(HWIO_QC_ECC20_ADDR)
#define HWIO_QC_ECC20_INM(m)            \
                in_dword_masked(HWIO_QC_ECC20_ADDR, m)
#define HWIO_QC_ECC20_QC_ECC_671_640_BMSK                                                             0xffffffff
#define HWIO_QC_ECC20_QC_ECC_671_640_SHFT                                                                      0

#define HWIO_QC_ECC21_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x7e4)
#define HWIO_QC_ECC21_RMSK                                                                            0xffffffff
#define HWIO_QC_ECC21_IN                    \
                in_dword(HWIO_QC_ECC21_ADDR)
#define HWIO_QC_ECC21_INM(m)            \
                in_dword_masked(HWIO_QC_ECC21_ADDR, m)
#define HWIO_QC_ECC21_QC_ECC_703_672_BMSK                                                             0xffffffff
#define HWIO_QC_ECC21_QC_ECC_703_672_SHFT                                                                      0

#define HWIO_SEQ_HASH0_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x800)
#define HWIO_SEQ_HASH0_RMSK                                                                           0xffffffff
#define HWIO_SEQ_HASH0_IN                    \
                in_dword(HWIO_SEQ_HASH0_ADDR)
#define HWIO_SEQ_HASH0_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH0_ADDR, m)
#define HWIO_SEQ_HASH0_SEQ_HASH_31_0_BMSK                                                             0xffffffff
#define HWIO_SEQ_HASH0_SEQ_HASH_31_0_SHFT                                                                      0

#define HWIO_SEQ_HASH1_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x804)
#define HWIO_SEQ_HASH1_RMSK                                                                           0xffffffff
#define HWIO_SEQ_HASH1_IN                    \
                in_dword(HWIO_SEQ_HASH1_ADDR)
#define HWIO_SEQ_HASH1_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH1_ADDR, m)
#define HWIO_SEQ_HASH1_SEQ_HASH_63_32_BMSK                                                            0xffffffff
#define HWIO_SEQ_HASH1_SEQ_HASH_63_32_SHFT                                                                     0

#define HWIO_SEQ_HASH2_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x808)
#define HWIO_SEQ_HASH2_RMSK                                                                           0xffffffff
#define HWIO_SEQ_HASH2_IN                    \
                in_dword(HWIO_SEQ_HASH2_ADDR)
#define HWIO_SEQ_HASH2_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH2_ADDR, m)
#define HWIO_SEQ_HASH2_SEQ_HASH_95_64_BMSK                                                            0xffffffff
#define HWIO_SEQ_HASH2_SEQ_HASH_95_64_SHFT                                                                     0

#define HWIO_SEQ_HASH3_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x80c)
#define HWIO_SEQ_HASH3_RMSK                                                                           0xffffffff
#define HWIO_SEQ_HASH3_IN                    \
                in_dword(HWIO_SEQ_HASH3_ADDR)
#define HWIO_SEQ_HASH3_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH3_ADDR, m)
#define HWIO_SEQ_HASH3_SEQ_HASH_127_96_BMSK                                                           0xffffffff
#define HWIO_SEQ_HASH3_SEQ_HASH_127_96_SHFT                                                                    0

#define HWIO_SEQ_HASH4_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x810)
#define HWIO_SEQ_HASH4_RMSK                                                                           0xffffffff
#define HWIO_SEQ_HASH4_IN                    \
                in_dword(HWIO_SEQ_HASH4_ADDR)
#define HWIO_SEQ_HASH4_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH4_ADDR, m)
#define HWIO_SEQ_HASH4_SEQ_HASH_159_128_BMSK                                                          0xffffffff
#define HWIO_SEQ_HASH4_SEQ_HASH_159_128_SHFT                                                                   0

#define HWIO_SEQ_HASH5_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x814)
#define HWIO_SEQ_HASH5_RMSK                                                                           0xffffffff
#define HWIO_SEQ_HASH5_IN                    \
                in_dword(HWIO_SEQ_HASH5_ADDR)
#define HWIO_SEQ_HASH5_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH5_ADDR, m)
#define HWIO_SEQ_HASH5_SEQ_HASH_191_160_BMSK                                                          0xffffffff
#define HWIO_SEQ_HASH5_SEQ_HASH_191_160_SHFT                                                                   0

#define HWIO_SEQ_HASH6_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x818)
#define HWIO_SEQ_HASH6_RMSK                                                                           0xffffffff
#define HWIO_SEQ_HASH6_IN                    \
                in_dword(HWIO_SEQ_HASH6_ADDR)
#define HWIO_SEQ_HASH6_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH6_ADDR, m)
#define HWIO_SEQ_HASH6_SEQ_HASH_223_192_BMSK                                                          0xffffffff
#define HWIO_SEQ_HASH6_SEQ_HASH_223_192_SHFT                                                                   0

#define HWIO_SEQ_HASH7_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x81c)
#define HWIO_SEQ_HASH7_RMSK                                                                           0xffffffff
#define HWIO_SEQ_HASH7_IN                    \
                in_dword(HWIO_SEQ_HASH7_ADDR)
#define HWIO_SEQ_HASH7_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH7_ADDR, m)
#define HWIO_SEQ_HASH7_SEQ_HASH_255_224_BMSK                                                          0xffffffff
#define HWIO_SEQ_HASH7_SEQ_HASH_255_224_SHFT                                                                   0

#define HWIO_SEQ_HASH8_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x820)
#define HWIO_SEQ_HASH8_RMSK                                                                           0xffffffff
#define HWIO_SEQ_HASH8_IN                    \
                in_dword(HWIO_SEQ_HASH8_ADDR)
#define HWIO_SEQ_HASH8_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH8_ADDR, m)
#define HWIO_SEQ_HASH8_SEQ_HASH_287_256_BMSK                                                          0xffffffff
#define HWIO_SEQ_HASH8_SEQ_HASH_287_256_SHFT                                                                   0

#define HWIO_SEQ_HASH9_ADDR                                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x824)
#define HWIO_SEQ_HASH9_RMSK                                                                           0xffffffff
#define HWIO_SEQ_HASH9_IN                    \
                in_dword(HWIO_SEQ_HASH9_ADDR)
#define HWIO_SEQ_HASH9_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH9_ADDR, m)
#define HWIO_SEQ_HASH9_SEQ_HASH_319_288_BMSK                                                          0xffffffff
#define HWIO_SEQ_HASH9_SEQ_HASH_319_288_SHFT                                                                   0

#define HWIO_SEQ_HASH10_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x828)
#define HWIO_SEQ_HASH10_RMSK                                                                          0xffffffff
#define HWIO_SEQ_HASH10_IN                    \
                in_dword(HWIO_SEQ_HASH10_ADDR)
#define HWIO_SEQ_HASH10_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH10_ADDR, m)
#define HWIO_SEQ_HASH10_SEQ_HASH_351_320_BMSK                                                         0xffffffff
#define HWIO_SEQ_HASH10_SEQ_HASH_351_320_SHFT                                                                  0

#define HWIO_SEQ_HASH11_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x82c)
#define HWIO_SEQ_HASH11_RMSK                                                                          0xffffffff
#define HWIO_SEQ_HASH11_IN                    \
                in_dword(HWIO_SEQ_HASH11_ADDR)
#define HWIO_SEQ_HASH11_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH11_ADDR, m)
#define HWIO_SEQ_HASH11_SEQ_HASH_383_352_BMSK                                                         0xffffffff
#define HWIO_SEQ_HASH11_SEQ_HASH_383_352_SHFT                                                                  0

#define HWIO_SEQ_HASH12_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x830)
#define HWIO_SEQ_HASH12_RMSK                                                                          0xffffffff
#define HWIO_SEQ_HASH12_IN                    \
                in_dword(HWIO_SEQ_HASH12_ADDR)
#define HWIO_SEQ_HASH12_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH12_ADDR, m)
#define HWIO_SEQ_HASH12_SEQ_HASH_415_384_BMSK                                                         0xffffffff
#define HWIO_SEQ_HASH12_SEQ_HASH_415_384_SHFT                                                                  0

#define HWIO_SEQ_HASH13_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x834)
#define HWIO_SEQ_HASH13_RMSK                                                                          0xffffffff
#define HWIO_SEQ_HASH13_IN                    \
                in_dword(HWIO_SEQ_HASH13_ADDR)
#define HWIO_SEQ_HASH13_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH13_ADDR, m)
#define HWIO_SEQ_HASH13_SEQ_HASH_447_416_BMSK                                                         0xffffffff
#define HWIO_SEQ_HASH13_SEQ_HASH_447_416_SHFT                                                                  0

#define HWIO_SEQ_HASH14_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x838)
#define HWIO_SEQ_HASH14_RMSK                                                                          0xffffffff
#define HWIO_SEQ_HASH14_IN                    \
                in_dword(HWIO_SEQ_HASH14_ADDR)
#define HWIO_SEQ_HASH14_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH14_ADDR, m)
#define HWIO_SEQ_HASH14_SEQ_HASH_479_448_BMSK                                                         0xffffffff
#define HWIO_SEQ_HASH14_SEQ_HASH_479_448_SHFT                                                                  0

#define HWIO_SEQ_HASH15_ADDR                                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x83c)
#define HWIO_SEQ_HASH15_RMSK                                                                          0xffffffff
#define HWIO_SEQ_HASH15_IN                    \
                in_dword(HWIO_SEQ_HASH15_ADDR)
#define HWIO_SEQ_HASH15_INM(m)            \
                in_dword_masked(HWIO_SEQ_HASH15_ADDR, m)
#define HWIO_SEQ_HASH15_SEQ_HASH_511_480_BMSK                                                         0xffffffff
#define HWIO_SEQ_HASH15_SEQ_HASH_511_480_SHFT                                                                  0

#define HWIO_QFPROM_CONTROLLER_ARBITER_ERROR_STATUS_REGISTER_ADDR                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x840)
#define HWIO_QFPROM_CONTROLLER_ARBITER_ERROR_STATUS_REGISTER_RMSK                                     0xffffffff
#define HWIO_QFPROM_CONTROLLER_ARBITER_ERROR_STATUS_REGISTER_IN                    \
                in_dword(HWIO_QFPROM_CONTROLLER_ARBITER_ERROR_STATUS_REGISTER_ADDR)
#define HWIO_QFPROM_CONTROLLER_ARBITER_ERROR_STATUS_REGISTER_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CONTROLLER_ARBITER_ERROR_STATUS_REGISTER_ADDR, m)
#define HWIO_QFPROM_CONTROLLER_ARBITER_ERROR_STATUS_REGISTER_QFPROM_ARBITER_ESR_BMSK                  0xffffffff
#define HWIO_QFPROM_CONTROLLER_ARBITER_ERROR_STATUS_REGISTER_QFPROM_ARBITER_ESR_SHFT                           0

#define HWIO_CRASH_DUMP_ENABLE_VECTOR_REMAP_ADDR                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x844)
#define HWIO_CRASH_DUMP_ENABLE_VECTOR_REMAP_RMSK                                                      0xffffffff
#define HWIO_CRASH_DUMP_ENABLE_VECTOR_REMAP_IN                    \
                in_dword(HWIO_CRASH_DUMP_ENABLE_VECTOR_REMAP_ADDR)
#define HWIO_CRASH_DUMP_ENABLE_VECTOR_REMAP_INM(m)            \
                in_dword_masked(HWIO_CRASH_DUMP_ENABLE_VECTOR_REMAP_ADDR, m)
#define HWIO_CRASH_DUMP_ENABLE_VECTOR_REMAP_CRASH_DUMP_ENABLE_VECTOR_BMSK                             0xffffffff
#define HWIO_CRASH_DUMP_ENABLE_VECTOR_REMAP_CRASH_DUMP_ENABLE_VECTOR_SHFT                                      0

#define HWIO_SEQ_STATE_REMAP_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x848)
#define HWIO_SEQ_STATE_REMAP_RMSK                                                                     0xffffffff
#define HWIO_SEQ_STATE_REMAP_IN                    \
                in_dword(HWIO_SEQ_STATE_REMAP_ADDR)
#define HWIO_SEQ_STATE_REMAP_INM(m)            \
                in_dword_masked(HWIO_SEQ_STATE_REMAP_ADDR, m)
#define HWIO_SEQ_STATE_REMAP_SEQ_STATE_BMSK                                                           0xffffffff
#define HWIO_SEQ_STATE_REMAP_SEQ_STATE_SHFT                                                                    0

#define HWIO_IMAGE_VALID_REMAP_ADDR                                                                   (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x84c)
#define HWIO_IMAGE_VALID_REMAP_RMSK                                                                   0xffffffff
#define HWIO_IMAGE_VALID_REMAP_IN                    \
                in_dword(HWIO_IMAGE_VALID_REMAP_ADDR)
#define HWIO_IMAGE_VALID_REMAP_INM(m)            \
                in_dword_masked(HWIO_IMAGE_VALID_REMAP_ADDR, m)
#define HWIO_IMAGE_VALID_REMAP_IMAGE_VALID_BMSK                                                       0xffffffff
#define HWIO_IMAGE_VALID_REMAP_IMAGE_VALID_SHFT                                                                0

#define HWIO_SEQ_IMG_AUTH_STATE_REMAP_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x850)
#define HWIO_SEQ_IMG_AUTH_STATE_REMAP_RMSK                                                            0xffffffff
#define HWIO_SEQ_IMG_AUTH_STATE_REMAP_IN                    \
                in_dword(HWIO_SEQ_IMG_AUTH_STATE_REMAP_ADDR)
#define HWIO_SEQ_IMG_AUTH_STATE_REMAP_INM(m)            \
                in_dword_masked(HWIO_SEQ_IMG_AUTH_STATE_REMAP_ADDR, m)
#define HWIO_SEQ_IMG_AUTH_STATE_REMAP_SEQ_IMG_AUTH_STATE_BMSK                                         0xffffffff
#define HWIO_SEQ_IMG_AUTH_STATE_REMAP_SEQ_IMG_AUTH_STATE_SHFT                                                  0

#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_ADDR                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x854)
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_IN                    \
                in_dword(HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_ADDR)
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_ADDR, m)
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_OEM_SPARE_0_MASK_READ_OVRD_BMSK                           0x80000000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_OEM_SPARE_0_MASK_READ_OVRD_SHFT                                   31
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_MEMORY_CONFIG_MASK_READ_OVRD_BMSK                         0x40000000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_MEMORY_CONFIG_MASK_READ_OVRD_SHFT                                 30
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_CALIBRATION_MASK_READ_OVRD_BMSK                           0x20000000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_CALIBRATION_MASK_READ_OVRD_SHFT                                   29
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_TME_CPU_ROM_PATCH_MASK_READ_OVRD_BMSK                     0x10000000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_TME_CPU_ROM_PATCH_MASK_READ_OVRD_SHFT                             28
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_SOC_ROM_PATCH_MASK_READ_OVRD_BMSK                          0x8000000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_SOC_ROM_PATCH_MASK_READ_OVRD_SHFT                                 27
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_OEM_PRODUCT_SEED_MASK_READ_OVRD_BMSK                       0x4000000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_OEM_PRODUCT_SEED_MASK_READ_OVRD_SHFT                              26
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_MARC_HASH_MASK_READ_OVRD_BMSK                              0x2000000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_MARC_HASH_MASK_READ_OVRD_SHFT                                     25
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SPARE_4_MASK_READ_OVRD_BMSK                             0x1000000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SPARE_4_MASK_READ_OVRD_SHFT                                    24
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SPARE_3_MASK_READ_OVRD_BMSK                              0x800000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SPARE_3_MASK_READ_OVRD_SHFT                                    23
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SPARE_2_MASK_READ_OVRD_BMSK                              0x400000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SPARE_2_MASK_READ_OVRD_SHFT                                    22
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SPARE_1_MASK_READ_OVRD_BMSK                              0x200000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SPARE_1_MASK_READ_OVRD_SHFT                                    21
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SPARE_0_MASK_READ_OVRD_BMSK                              0x100000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SPARE_0_MASK_READ_OVRD_SHFT                                    20
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_ECC_MASK_READ_OVRD_BMSK                                   0x80000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_ECC_MASK_READ_OVRD_SHFT                                        19
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_TME_SEQUENCER_ROM_PATCH_MASK_READ_OVRD_BMSK                  0x40000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_TME_SEQUENCER_ROM_PATCH_MASK_READ_OVRD_SHFT                       18
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_ANTI_ROLLBACK_MASK_READ_OVRD_BMSK                            0x20000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_ANTI_ROLLBACK_MASK_READ_OVRD_SHFT                                 17
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_CONFIG_MASK_READ_OVRD_BMSK                                0x10000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_CONFIG_MASK_READ_OVRD_SHFT                                     16
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_FEATURE_CONFIG_OVERRIDE_MASK_READ_OVRD_BMSK                   0x8000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_FEATURE_CONFIG_OVERRIDE_MASK_READ_OVRD_SHFT                       15
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_FEATURE_CONFIG_MASK_READ_OVRD_BMSK                            0x4000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_FEATURE_CONFIG_MASK_READ_OVRD_SHFT                                14
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_OEM_CONFIG_MASK_READ_OVRD_BMSK                                0x2000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_OEM_CONFIG_MASK_READ_OVRD_SHFT                                    13
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_DEBUG_TEST_REENABLE_MASK_READ_OVRD_BMSK                       0x1000
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_DEBUG_TEST_REENABLE_MASK_READ_OVRD_SHFT                           12
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_DEBUG_DISABLE_MASK_READ_OVRD_BMSK                              0x800
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_DEBUG_DISABLE_MASK_READ_OVRD_SHFT                                 11
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_FUSE_REDUNDANCY_ENABLE_MASK_READ_OVRD_BMSK                     0x400
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_FUSE_REDUNDANCY_ENABLE_MASK_READ_OVRD_SHFT                        10
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_READ_PERMISSIONS_MASK_READ_OVRD_BMSK                           0x200
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_READ_PERMISSIONS_MASK_READ_OVRD_SHFT                               9
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_WRITE_PERMISSIONS_MASK_READ_OVRD_BMSK                          0x100
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_WRITE_PERMISSIONS_MASK_READ_OVRD_SHFT                              8
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_PTE_MASK_READ_OVRD_BMSK                                         0x80
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_PTE_MASK_READ_OVRD_SHFT                                            7
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_OEM_SECURITY_POLICY_MASK_READ_OVRD_BMSK                         0x40
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_OEM_SECURITY_POLICY_MASK_READ_OVRD_SHFT                            6
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SECURITY_POLICY_MASK_READ_OVRD_BMSK                          0x20
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_QC_SECURITY_POLICY_MASK_READ_OVRD_SHFT                             5
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_MRC_MASK_READ_OVRD_BMSK                                         0x10
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_MRC_MASK_READ_OVRD_SHFT                                            4
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_TME_LCS_MASK_READ_OVRD_BMSK                                      0x8
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_TME_LCS_MASK_READ_OVRD_SHFT                                        3
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_TME_PRIVATE_MASK_READ_OVRD_BMSK                                  0x4
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_TME_PRIVATE_MASK_READ_OVRD_SHFT                                    2
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_TME_PCD_MASK_READ_OVRD_BMSK                                      0x2
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_TME_PCD_MASK_READ_OVRD_SHFT                                        1
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_CM_CORE_PRIVATE_OTP_MASK_READ_OVRD_BMSK                          0x1
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_LSB_CM_CORE_PRIVATE_OTP_MASK_READ_OVRD_SHFT                            0

#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_ADDR                                                      (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x858)
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_IN                    \
                in_dword(HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_ADDR)
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_ADDR, m)
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_MASK_RD_OVRD_RSVD_BMSK                                    0xfffffff8
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_MASK_RD_OVRD_RSVD_SHFT                                             3
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_OEM_SPARE_3_MASK_READ_OVRD_BMSK                                  0x4
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_OEM_SPARE_3_MASK_READ_OVRD_SHFT                                    2
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_OEM_SPARE_2_MASK_READ_OVRD_BMSK                                  0x2
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_OEM_SPARE_2_MASK_READ_OVRD_SHFT                                    1
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_OEM_SPARE_1_MASK_READ_OVRD_BMSK                                  0x1
#define HWIO_QFPROM_MASK_READ_PERM_OVRD_MSB_OEM_SPARE_1_MASK_READ_OVRD_SHFT                                    0

#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_ADDR                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x85c)
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_IN                    \
                in_dword(HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_ADDR)
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_ADDR, m)
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_OEM_SPARE_0_MASK_WRITE_OVRD_BMSK                         0x80000000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_OEM_SPARE_0_MASK_WRITE_OVRD_SHFT                                 31
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_MEMORY_CONFIG_MASK_WRITE_OVRD_BMSK                       0x40000000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_MEMORY_CONFIG_MASK_WRITE_OVRD_SHFT                               30
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_CALIBRATION_MASK_WRITE_OVRD_BMSK                         0x20000000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_CALIBRATION_MASK_WRITE_OVRD_SHFT                                 29
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_TME_CPU_ROM_PATCH_MASK_WRITE_OVRD_BMSK                   0x10000000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_TME_CPU_ROM_PATCH_MASK_WRITE_OVRD_SHFT                           28
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_SOC_ROM_PATCH_MASK_WRITE_OVRD_BMSK                        0x8000000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_SOC_ROM_PATCH_MASK_WRITE_OVRD_SHFT                               27
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_OEM_PRODUCT_SEED_MASK_WRITE_OVRD_BMSK                     0x4000000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_OEM_PRODUCT_SEED_MASK_WRITE_OVRD_SHFT                            26
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_MARC_HASH_MASK_WRITE_OVRD_BMSK                            0x2000000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_MARC_HASH_MASK_WRITE_OVRD_SHFT                                   25
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SPARE_4_MASK_WRITE_OVRD_BMSK                           0x1000000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SPARE_4_MASK_WRITE_OVRD_SHFT                                  24
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SPARE_3_MASK_WRITE_OVRD_BMSK                            0x800000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SPARE_3_MASK_WRITE_OVRD_SHFT                                  23
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SPARE_2_MASK_WRITE_OVRD_BMSK                            0x400000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SPARE_2_MASK_WRITE_OVRD_SHFT                                  22
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SPARE_1_MASK_WRITE_OVRD_BMSK                            0x200000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SPARE_1_MASK_WRITE_OVRD_SHFT                                  21
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SPARE_0_MASK_WRITE_OVRD_BMSK                            0x100000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SPARE_0_MASK_WRITE_OVRD_SHFT                                  20
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_ECC_MASK_WRITE_OVRD_BMSK                                 0x80000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_ECC_MASK_WRITE_OVRD_SHFT                                      19
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_TME_SEQUENCER_ROM_PATCH_MASK_WRITE_OVRD_BMSK                0x40000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_TME_SEQUENCER_ROM_PATCH_MASK_WRITE_OVRD_SHFT                     18
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_ANTI_ROLLBACK_MASK_WRITE_OVRD_BMSK                          0x20000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_ANTI_ROLLBACK_MASK_WRITE_OVRD_SHFT                               17
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_CONFIG_MASK_WRITE_OVRD_BMSK                              0x10000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_CONFIG_MASK_WRITE_OVRD_SHFT                                   16
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_FEATURE_CONFIG_OVERRIDE_MASK_WRITE_OVRD_BMSK                 0x8000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_FEATURE_CONFIG_OVERRIDE_MASK_WRITE_OVRD_SHFT                     15
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_FEATURE_CONFIG_MASK_WRITE_OVRD_BMSK                          0x4000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_FEATURE_CONFIG_MASK_WRITE_OVRD_SHFT                              14
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_OEM_CONFIG_MASK_WRITE_OVRD_BMSK                              0x2000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_OEM_CONFIG_MASK_WRITE_OVRD_SHFT                                  13
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_DEBUG_TEST_REENABLE_MASK_WRITE_OVRD_BMSK                     0x1000
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_DEBUG_TEST_REENABLE_MASK_WRITE_OVRD_SHFT                         12
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_DEBUG_DISABLE_MASK_WRITE_OVRD_BMSK                            0x800
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_DEBUG_DISABLE_MASK_WRITE_OVRD_SHFT                               11
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_FUSE_REDUNDANCY_ENABLE_MASK_WRITE_OVRD_BMSK                   0x400
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_FUSE_REDUNDANCY_ENABLE_MASK_WRITE_OVRD_SHFT                      10
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_READ_PERMISSIONS_MASK_WRITE_OVRD_BMSK                         0x200
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_READ_PERMISSIONS_MASK_WRITE_OVRD_SHFT                             9
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_WRITE_PERMISSIONS_MASK_WRITE_OVRD_BMSK                        0x100
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_WRITE_PERMISSIONS_MASK_WRITE_OVRD_SHFT                            8
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_PTE_MASK_WRITE_OVRD_BMSK                                       0x80
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_PTE_MASK_WRITE_OVRD_SHFT                                          7
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_OEM_SECURITY_POLICY_MASK_WRITE_OVRD_BMSK                       0x40
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_OEM_SECURITY_POLICY_MASK_WRITE_OVRD_SHFT                          6
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SECURITY_POLICY_MASK_WRITE_OVRD_BMSK                        0x20
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_QC_SECURITY_POLICY_MASK_WRITE_OVRD_SHFT                           5
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_MRC_MASK_WRITE_OVRD_BMSK                                       0x10
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_MRC_MASK_WRITE_OVRD_SHFT                                          4
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_TME_LCS_MASK_WRITE_OVRD_BMSK                                    0x8
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_TME_LCS_MASK_WRITE_OVRD_SHFT                                      3
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_TME_PRIVATE_MASK_WRITE_OVRD_BMSK                                0x4
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_TME_PRIVATE_MASK_WRITE_OVRD_SHFT                                  2
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_TME_PCD_MASK_WRITE_OVRD_BMSK                                    0x2
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_TME_PCD_MASK_WRITE_OVRD_SHFT                                      1
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_CM_CORE_PRIVATE_OTP_MASK_WRITE_OVRD_BMSK                        0x1
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_LSB_CM_CORE_PRIVATE_OTP_MASK_WRITE_OVRD_SHFT                          0

#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_ADDR                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x860)
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_IN                    \
                in_dword(HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_ADDR)
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_ADDR, m)
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_MASK_WR_OVRD_RSVD_BMSK                                   0xfffffff8
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_MASK_WR_OVRD_RSVD_SHFT                                            3
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_OEM_SPARE_3_MASK_WRITE_OVRD_BMSK                                0x4
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_OEM_SPARE_3_MASK_WRITE_OVRD_SHFT                                  2
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_OEM_SPARE_2_MASK_WRITE_OVRD_BMSK                                0x2
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_OEM_SPARE_2_MASK_WRITE_OVRD_SHFT                                  1
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_OEM_SPARE_1_MASK_WRITE_OVRD_BMSK                                0x1
#define HWIO_QFPROM_MASK_WRITE_PERM_OVRD_MSB_OEM_SPARE_1_MASK_WRITE_OVRD_SHFT                                  0

#define HWIO_QAD_VECT_PERSIST_ON_RST_ADDR                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x864)
#define HWIO_QAD_VECT_PERSIST_ON_RST_RMSK                                                             0xffffffff
#define HWIO_QAD_VECT_PERSIST_ON_RST_IN                    \
                in_dword(HWIO_QAD_VECT_PERSIST_ON_RST_ADDR)
#define HWIO_QAD_VECT_PERSIST_ON_RST_INM(m)            \
                in_dword_masked(HWIO_QAD_VECT_PERSIST_ON_RST_ADDR, m)
#define HWIO_QAD_VECT_PERSIST_ON_RST_QAD_VECTOR_BMSK                                                  0xffffffff
#define HWIO_QAD_VECT_PERSIST_ON_RST_QAD_VECTOR_SHFT                                                           0

#define HWIO_QAD_VECT_NO_PERSIST_ON_RST_ADDR                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x868)
#define HWIO_QAD_VECT_NO_PERSIST_ON_RST_RMSK                                                          0xffffffff
#define HWIO_QAD_VECT_NO_PERSIST_ON_RST_IN                    \
                in_dword(HWIO_QAD_VECT_NO_PERSIST_ON_RST_ADDR)
#define HWIO_QAD_VECT_NO_PERSIST_ON_RST_INM(m)            \
                in_dword_masked(HWIO_QAD_VECT_NO_PERSIST_ON_RST_ADDR, m)
#define HWIO_QAD_VECT_NO_PERSIST_ON_RST_QAD_VECTOR_BMSK                                               0xffffffff
#define HWIO_QAD_VECT_NO_PERSIST_ON_RST_QAD_VECTOR_SHFT                                                        0

#define HWIO_DAP_PROXY_QAD_ENABLE_ADDR                                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x86c)
#define HWIO_DAP_PROXY_QAD_ENABLE_RMSK                                                                0xffffffff
#define HWIO_DAP_PROXY_QAD_ENABLE_IN                    \
                in_dword(HWIO_DAP_PROXY_QAD_ENABLE_ADDR)
#define HWIO_DAP_PROXY_QAD_ENABLE_INM(m)            \
                in_dword_masked(HWIO_DAP_PROXY_QAD_ENABLE_ADDR, m)
#define HWIO_DAP_PROXY_QAD_ENABLE_DAP_PROXY_QAD_ENABLE_BMSK                                           0xffffffff
#define HWIO_DAP_PROXY_QAD_ENABLE_DAP_PROXY_QAD_ENABLE_SHFT                                                    0

#define HWIO_QC_SECURITY_POLICY_ADDR                                                                  (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x870)
#define HWIO_QC_SECURITY_POLICY_RMSK                                                                         0x1
#define HWIO_QC_SECURITY_POLICY_IN                    \
                in_dword(HWIO_QC_SECURITY_POLICY_ADDR)
#define HWIO_QC_SECURITY_POLICY_INM(m)            \
                in_dword_masked(HWIO_QC_SECURITY_POLICY_ADDR, m)
#define HWIO_QC_SECURITY_POLICY_DISABLE_ROM_PATCH_BMSK                                                       0x1
#define HWIO_QC_SECURITY_POLICY_DISABLE_ROM_PATCH_SHFT                                                         0

#define HWIO_CRI_DEBUG_VECTOR_PERSIST_0_ADDR                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x874)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_0_RMSK                                                          0xffffffff
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_0_IN                    \
                in_dword(HWIO_CRI_DEBUG_VECTOR_PERSIST_0_ADDR)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_0_INM(m)            \
                in_dword_masked(HWIO_CRI_DEBUG_VECTOR_PERSIST_0_ADDR, m)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_0_CRI_DEBUG_VECTOR_0_BMSK                                       0xffffffff
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_0_CRI_DEBUG_VECTOR_0_SHFT                                                0

#define HWIO_CRI_DEBUG_VECTOR_PERSIST_1_ADDR                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x878)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_1_RMSK                                                          0xffffffff
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_1_IN                    \
                in_dword(HWIO_CRI_DEBUG_VECTOR_PERSIST_1_ADDR)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_1_INM(m)            \
                in_dword_masked(HWIO_CRI_DEBUG_VECTOR_PERSIST_1_ADDR, m)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_1_CRI_DEBUG_VECTOR_1_BMSK                                       0xffffffff
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_1_CRI_DEBUG_VECTOR_1_SHFT                                                0

#define HWIO_CRI_DEBUG_VECTOR_PERSIST_2_ADDR                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x87c)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_2_RMSK                                                          0xffffffff
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_2_IN                    \
                in_dword(HWIO_CRI_DEBUG_VECTOR_PERSIST_2_ADDR)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_2_INM(m)            \
                in_dword_masked(HWIO_CRI_DEBUG_VECTOR_PERSIST_2_ADDR, m)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_2_CRI_DEBUG_VECTOR_2_BMSK                                       0xffffffff
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_2_CRI_DEBUG_VECTOR_2_SHFT                                                0

#define HWIO_CRI_DEBUG_VECTOR_PERSIST_3_ADDR                                                          (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x880)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_3_RMSK                                                          0xffffffff
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_3_IN                    \
                in_dword(HWIO_CRI_DEBUG_VECTOR_PERSIST_3_ADDR)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_3_INM(m)            \
                in_dword_masked(HWIO_CRI_DEBUG_VECTOR_PERSIST_3_ADDR, m)
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_3_CRI_DEBUG_VECTOR_3_BMSK                                       0xffffffff
#define HWIO_CRI_DEBUG_VECTOR_PERSIST_3_CRI_DEBUG_VECTOR_3_SHFT                                                0

#define HWIO_OEM_SECURE_BOOT_POLICY4_ADDR                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0x884)
#define HWIO_OEM_SECURE_BOOT_POLICY4_RMSK                                                                    0x1
#define HWIO_OEM_SECURE_BOOT_POLICY4_IN                    \
                in_dword(HWIO_OEM_SECURE_BOOT_POLICY4_ADDR)
#define HWIO_OEM_SECURE_BOOT_POLICY4_INM(m)            \
                in_dword_masked(HWIO_OEM_SECURE_BOOT_POLICY4_ADDR, m)
#define HWIO_OEM_SECURE_BOOT_POLICY4_ENABLE_SECURE_BOOT_BMSK                                                 0x1
#define HWIO_OEM_SECURE_BOOT_POLICY4_ENABLE_SECURE_BOOT_SHFT                                                   0

#define HWIO_FEATURE_CONFIG_OVERRIDE0_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa00)
#define HWIO_FEATURE_CONFIG_OVERRIDE0_RMSK                                                            0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE0_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE0_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE0_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE0_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE0_MODEM_FEATURE_DISABLE_HARD_23_0_BMSK                            0xffffff00
#define HWIO_FEATURE_CONFIG_OVERRIDE0_MODEM_FEATURE_DISABLE_HARD_23_0_SHFT                                     8
#define HWIO_FEATURE_CONFIG_OVERRIDE0_MODEM_FEATURE_DISABLE_SPARE_7_0_BMSK                                  0xff
#define HWIO_FEATURE_CONFIG_OVERRIDE0_MODEM_FEATURE_DISABLE_SPARE_7_0_SHFT                                     0

#define HWIO_FEATURE_CONFIG_OVERRIDE1_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa04)
#define HWIO_FEATURE_CONFIG_OVERRIDE1_RMSK                                                            0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE1_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE1_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE1_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE1_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE1_MODEM_FEATURE_DISABLE_SOFT_1_23_0_BMSK                          0xffffff00
#define HWIO_FEATURE_CONFIG_OVERRIDE1_MODEM_FEATURE_DISABLE_SOFT_1_23_0_SHFT                                   8
#define HWIO_FEATURE_CONFIG_OVERRIDE1_MODEM_FEATURE_DISABLE_HARD_31_24_BMSK                                 0xff
#define HWIO_FEATURE_CONFIG_OVERRIDE1_MODEM_FEATURE_DISABLE_HARD_31_24_SHFT                                    0

#define HWIO_FEATURE_CONFIG_OVERRIDE2_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa08)
#define HWIO_FEATURE_CONFIG_OVERRIDE2_RMSK                                                            0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE2_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE2_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE2_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE2_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE2_MODEM_FEATURE_DISABLE_SOFT_2_23_0_BMSK                          0xffffff00
#define HWIO_FEATURE_CONFIG_OVERRIDE2_MODEM_FEATURE_DISABLE_SOFT_2_23_0_SHFT                                   8
#define HWIO_FEATURE_CONFIG_OVERRIDE2_MODEM_FEATURE_DISABLE_SOFT_1_31_24_BMSK                               0xff
#define HWIO_FEATURE_CONFIG_OVERRIDE2_MODEM_FEATURE_DISABLE_SOFT_1_31_24_SHFT                                  0

#define HWIO_FEATURE_CONFIG_OVERRIDE3_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa0c)
#define HWIO_FEATURE_CONFIG_OVERRIDE3_RMSK                                                            0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE3_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE3_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE3_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE3_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE3_MODEM_FEATURE_DISABLE_SOFT_3_23_0_BMSK                          0xffffff00
#define HWIO_FEATURE_CONFIG_OVERRIDE3_MODEM_FEATURE_DISABLE_SOFT_3_23_0_SHFT                                   8
#define HWIO_FEATURE_CONFIG_OVERRIDE3_MODEM_FEATURE_DISABLE_SOFT_2_31_24_BMSK                               0xff
#define HWIO_FEATURE_CONFIG_OVERRIDE3_MODEM_FEATURE_DISABLE_SOFT_2_31_24_SHFT                                  0

#define HWIO_FEATURE_CONFIG_OVERRIDE4_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa10)
#define HWIO_FEATURE_CONFIG_OVERRIDE4_RMSK                                                            0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE4_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE4_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE4_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE4_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE4_MODEM_FEATURE_DISABLE_SOFT_4_23_0_BMSK                          0xffffff00
#define HWIO_FEATURE_CONFIG_OVERRIDE4_MODEM_FEATURE_DISABLE_SOFT_4_23_0_SHFT                                   8
#define HWIO_FEATURE_CONFIG_OVERRIDE4_MODEM_FEATURE_DISABLE_SOFT_3_31_24_BMSK                               0xff
#define HWIO_FEATURE_CONFIG_OVERRIDE4_MODEM_FEATURE_DISABLE_SOFT_3_31_24_SHFT                                  0

#define HWIO_FEATURE_CONFIG_OVERRIDE5_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa14)
#define HWIO_FEATURE_CONFIG_OVERRIDE5_RMSK                                                            0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE5_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE5_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE5_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE5_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE5_FEATURE_CONFIG_191_187_BMSK                                     0xf8000000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_FEATURE_CONFIG_191_187_SHFT                                             27
#define HWIO_FEATURE_CONFIG_OVERRIDE5_LPASS_Q6SS_TCM_BOOT_DISABLE_BMSK                                 0x4000000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_LPASS_Q6SS_TCM_BOOT_DISABLE_SHFT                                        26
#define HWIO_FEATURE_CONFIG_OVERRIDE5_FEATURE_CONFIG_185_183_BMSK                                      0x3800000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_FEATURE_CONFIG_185_183_SHFT                                             23
#define HWIO_FEATURE_CONFIG_OVERRIDE5_SPR_DISABLE_BMSK                                                  0x400000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_SPR_DISABLE_SHFT                                                        22
#define HWIO_FEATURE_CONFIG_OVERRIDE5_DEMURA_DISABLE_BMSK                                               0x200000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_DEMURA_DISABLE_SHFT                                                     21
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MST_DISABLE_BMSK                                                  0x100000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MST_DISABLE_SHFT                                                        20
#define HWIO_FEATURE_CONFIG_OVERRIDE5_Q_CONFIG_FUSE_BMSK                                                 0x80000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_Q_CONFIG_FUSE_SHFT                                                      19
#define HWIO_FEATURE_CONFIG_OVERRIDE5_DTPX0_EFUSE_DISABLE_BMSK                                           0x40000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_DTPX0_EFUSE_DISABLE_SHFT                                                18
#define HWIO_FEATURE_CONFIG_OVERRIDE5_GC_SPLIT_DISABLE_BMSK                                              0x20000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_GC_SPLIT_DISABLE_SHFT                                                   17
#define HWIO_FEATURE_CONFIG_OVERRIDE5_DSI_1_DISABLE_BMSK                                                 0x10000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_DSI_1_DISABLE_SHFT                                                      16
#define HWIO_FEATURE_CONFIG_OVERRIDE5_DSI_0_DISABLE_BMSK                                                  0x8000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_DSI_0_DISABLE_SHFT                                                      15
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MDP_EFUSE_LTC_DISABLE_BMSK                                          0x4000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MDP_EFUSE_LTC_DISABLE_SHFT                                              14
#define HWIO_FEATURE_CONFIG_OVERRIDE5_HDCP_DISABLE_BMSK                                                   0x2000
#define HWIO_FEATURE_CONFIG_OVERRIDE5_HDCP_DISABLE_SHFT                                                       13
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MDSS_RESOLUTION_LIMIT_BMSK                                          0x1800
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MDSS_RESOLUTION_LIMIT_SHFT                                              11
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MSMC_NAV_EN_BMSK                                                     0x400
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MSMC_NAV_EN_SHFT                                                        10
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MODEM_NO_MSA_BOOT_BMSK                                               0x200
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MODEM_NO_MSA_BOOT_SHFT                                                   9
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MODEM_TCM_BOOT_DISABLE_BMSK                                          0x100
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MODEM_TCM_BOOT_DISABLE_SHFT                                              8
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MODEM_FEATURE_DISABLE_SOFT_4_31_24_BMSK                               0xff
#define HWIO_FEATURE_CONFIG_OVERRIDE5_MODEM_FEATURE_DISABLE_SOFT_4_31_24_SHFT                                  0

#define HWIO_FEATURE_CONFIG_OVERRIDE6_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa18)
#define HWIO_FEATURE_CONFIG_OVERRIDE6_RMSK                                                            0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE6_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE6_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE6_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE6_PCIE_0_DISABLE_BMSK                                             0x80000000
#define HWIO_FEATURE_CONFIG_OVERRIDE6_PCIE_0_DISABLE_SHFT                                                     31
#define HWIO_FEATURE_CONFIG_OVERRIDE6_SSC_DISABLE_BMSK                                                0x40000000
#define HWIO_FEATURE_CONFIG_OVERRIDE6_SSC_DISABLE_SHFT                                                        30
#define HWIO_FEATURE_CONFIG_OVERRIDE6_SSC_Q6SS_L2TCM_EN_BMSK                                          0x3f000000
#define HWIO_FEATURE_CONFIG_OVERRIDE6_SSC_Q6SS_L2TCM_EN_SHFT                                                  24
#define HWIO_FEATURE_CONFIG_OVERRIDE6_SSC_AON_CAM_DISABLE_BMSK                                          0x800000
#define HWIO_FEATURE_CONFIG_OVERRIDE6_SSC_AON_CAM_DISABLE_SHFT                                                23
#define HWIO_FEATURE_CONFIG_OVERRIDE6_SSC_ISLAND_MODE_Q6_CLK_DISABLE_BMSK                               0x400000
#define HWIO_FEATURE_CONFIG_OVERRIDE6_SSC_ISLAND_MODE_Q6_CLK_DISABLE_SHFT                                     22
#define HWIO_FEATURE_CONFIG_OVERRIDE6_SSC_SW_ISLAND_MODE_DISABLE_BMSK                                   0x200000
#define HWIO_FEATURE_CONFIG_OVERRIDE6_SSC_SW_ISLAND_MODE_DISABLE_SHFT                                         21
#define HWIO_FEATURE_CONFIG_OVERRIDE6_GPU_CC_FREQ_LIMIT_VAL_BMSK                                        0x1fe000
#define HWIO_FEATURE_CONFIG_OVERRIDE6_GPU_CC_FREQ_LIMIT_VAL_SHFT                                              13
#define HWIO_FEATURE_CONFIG_OVERRIDE6_FEATURE_CONFIG_204_BMSK                                             0x1000
#define HWIO_FEATURE_CONFIG_OVERRIDE6_FEATURE_CONFIG_204_SHFT                                                 12
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_DISABLE_8K_BMSK                                                 0x800
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_DISABLE_8K_SHFT                                                    11
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_DISABLE_AV1_BMSK                                                0x400
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_DISABLE_AV1_SHFT                                                   10
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_DISABLE_10BIT_ENCODE_BMSK                                       0x200
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_DISABLE_10BIT_ENCODE_SHFT                                           9
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_DISABLE_10BIT_DECODE_BMSK                                       0x100
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_DISABLE_10BIT_DECODE_SHFT                                           8
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_MULTIPIPE_DISABLE_BMSK                                           0x80
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_MULTIPIPE_DISABLE_SHFT                                              7
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_HEVC_ENCODE_DISABLE_BMSK                                         0x40
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_HEVC_ENCODE_DISABLE_SHFT                                            6
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_HEVC_DECODE_DISABLE_BMSK                                         0x20
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_HEVC_DECODE_DISABLE_SHFT                                            5
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_4K_DISABLE_BMSK                                                  0x10
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_4K_DISABLE_SHFT                                                     4
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_CVP_DISABLE_BMSK                                                  0x8
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_CVP_DISABLE_SHFT                                                    3
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_DISABLE_VPX_BMSK                                                  0x4
#define HWIO_FEATURE_CONFIG_OVERRIDE6_IRIS_DISABLE_VPX_SHFT                                                    2
#define HWIO_FEATURE_CONFIG_OVERRIDE6_TITAN_CAM_SBI_DISABLE_IF_BMSK                                          0x2
#define HWIO_FEATURE_CONFIG_OVERRIDE6_TITAN_CAM_SBI_DISABLE_IF_SHFT                                            1
#define HWIO_FEATURE_CONFIG_OVERRIDE6_TITAN_AON_CAM_DISABLE_IF_BMSK                                          0x1
#define HWIO_FEATURE_CONFIG_OVERRIDE6_TITAN_AON_CAM_DISABLE_IF_SHFT                                            0

#define HWIO_FEATURE_CONFIG_OVERRIDE7_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa1c)
#define HWIO_FEATURE_CONFIG_OVERRIDE7_RMSK                                                            0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE7_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE7_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE7_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE7_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE7_SYS_APSSCFGAPMBOOTONMX_BMSK                                     0x80000000
#define HWIO_FEATURE_CONFIG_OVERRIDE7_SYS_APSSCFGAPMBOOTONMX_SHFT                                             31
#define HWIO_FEATURE_CONFIG_OVERRIDE7_SYS_APSSCFGCPUPRESENT_N_BMSK                                    0x7f800000
#define HWIO_FEATURE_CONFIG_OVERRIDE7_SYS_APSSCFGCPUPRESENT_N_SHFT                                            23
#define HWIO_FEATURE_CONFIG_OVERRIDE7_APSS_PDXWRPNTRDELAY_BMSK                                          0x600000
#define HWIO_FEATURE_CONFIG_OVERRIDE7_APSS_PDXWRPNTRDELAY_SHFT                                                21
#define HWIO_FEATURE_CONFIG_OVERRIDE7_GATE_SRST_FUSE_BMSK                                               0x100000
#define HWIO_FEATURE_CONFIG_OVERRIDE7_GATE_SRST_FUSE_SHFT                                                     20
#define HWIO_FEATURE_CONFIG_OVERRIDE7_AUTOMOTIVE_BIT_FUNCTIONAL_BMSK                                     0x80000
#define HWIO_FEATURE_CONFIG_OVERRIDE7_AUTOMOTIVE_BIT_FUNCTIONAL_SHFT                                          19
#define HWIO_FEATURE_CONFIG_OVERRIDE7_AUTOMOTIVE_BIT_POWER_BMSK                                          0x40000
#define HWIO_FEATURE_CONFIG_OVERRIDE7_AUTOMOTIVE_BIT_POWER_SHFT                                               18
#define HWIO_FEATURE_CONFIG_OVERRIDE7_EMAC_DISABLE_BMSK                                                  0x20000
#define HWIO_FEATURE_CONFIG_OVERRIDE7_EMAC_DISABLE_SHFT                                                       17
#define HWIO_FEATURE_CONFIG_OVERRIDE7_NAV_EFUSE_DISABLE_BMSK                                             0x10000
#define HWIO_FEATURE_CONFIG_OVERRIDE7_NAV_EFUSE_DISABLE_SHFT                                                  16
#define HWIO_FEATURE_CONFIG_OVERRIDE7_FUSE_CORTEX_M3_DISABLE_BMSK                                         0x8000
#define HWIO_FEATURE_CONFIG_OVERRIDE7_FUSE_CORTEX_M3_DISABLE_SHFT                                             15
#define HWIO_FEATURE_CONFIG_OVERRIDE7_APS_RESET_DISABLE_BMSK                                              0x4000
#define HWIO_FEATURE_CONFIG_OVERRIDE7_APS_RESET_DISABLE_SHFT                                                  14
#define HWIO_FEATURE_CONFIG_OVERRIDE7_DOLBY_BIT_BMSK                                                      0x2000
#define HWIO_FEATURE_CONFIG_OVERRIDE7_DOLBY_BIT_SHFT                                                          13
#define HWIO_FEATURE_CONFIG_OVERRIDE7_FEATURE_CONFIG_236_235_BMSK                                         0x1800
#define HWIO_FEATURE_CONFIG_OVERRIDE7_FEATURE_CONFIG_236_235_SHFT                                             11
#define HWIO_FEATURE_CONFIG_OVERRIDE7_SHRM1_DISABLE_BMSK                                                   0x400
#define HWIO_FEATURE_CONFIG_OVERRIDE7_SHRM1_DISABLE_SHFT                                                      10
#define HWIO_FEATURE_CONFIG_OVERRIDE7_PCIEPHY_DISABLE_UPPER_LANE_BMSK                                      0x200
#define HWIO_FEATURE_CONFIG_OVERRIDE7_PCIEPHY_DISABLE_UPPER_LANE_SHFT                                          9
#define HWIO_FEATURE_CONFIG_OVERRIDE7_UFS_FUSE_ICE_DISABLE_BMSK                                            0x100
#define HWIO_FEATURE_CONFIG_OVERRIDE7_UFS_FUSE_ICE_DISABLE_SHFT                                                8
#define HWIO_FEATURE_CONFIG_OVERRIDE7_FEATURE_CONFIG_231_BMSK                                               0x80
#define HWIO_FEATURE_CONFIG_OVERRIDE7_FEATURE_CONFIG_231_SHFT                                                  7
#define HWIO_FEATURE_CONFIG_OVERRIDE7_MOCHA_PART_BMSK                                                       0x40
#define HWIO_FEATURE_CONFIG_OVERRIDE7_MOCHA_PART_SHFT                                                          6
#define HWIO_FEATURE_CONFIG_OVERRIDE7_QC_SP_DISABLE_BMSK                                                    0x20
#define HWIO_FEATURE_CONFIG_OVERRIDE7_QC_SP_DISABLE_SHFT                                                       5
#define HWIO_FEATURE_CONFIG_OVERRIDE7_SMMU_DISABLE_BMSK                                                     0x10
#define HWIO_FEATURE_CONFIG_OVERRIDE7_SMMU_DISABLE_SHFT                                                        4
#define HWIO_FEATURE_CONFIG_OVERRIDE7_RSVD_BMSK                                                              0x8
#define HWIO_FEATURE_CONFIG_OVERRIDE7_RSVD_SHFT                                                                3
#define HWIO_FEATURE_CONFIG_OVERRIDE7_FEATURE_CONFIG_BMSK                                                    0x4
#define HWIO_FEATURE_CONFIG_OVERRIDE7_FEATURE_CONFIG_SHFT                                                      2
#define HWIO_FEATURE_CONFIG_OVERRIDE7_CM_FEAT_CONFIG_DISABLE_BMSK                                            0x2
#define HWIO_FEATURE_CONFIG_OVERRIDE7_CM_FEAT_CONFIG_DISABLE_SHFT                                              1
#define HWIO_FEATURE_CONFIG_OVERRIDE7_PCIE_1_DISABLE_BMSK                                                    0x1
#define HWIO_FEATURE_CONFIG_OVERRIDE7_PCIE_1_DISABLE_SHFT                                                      0

#define HWIO_FEATURE_CONFIG_OVERRIDE8_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa20)
#define HWIO_FEATURE_CONFIG_OVERRIDE8_RMSK                                                            0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE8_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE8_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE8_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE8_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE8_SYS_CFG_GOLDPLUS_PLL_LVAL_4_0_BMSK                              0xf8000000
#define HWIO_FEATURE_CONFIG_OVERRIDE8_SYS_CFG_GOLDPLUS_PLL_LVAL_4_0_SHFT                                      27
#define HWIO_FEATURE_CONFIG_OVERRIDE8_SYS_CFG_APC1PLL_LVAL_BMSK                                        0x7f80000
#define HWIO_FEATURE_CONFIG_OVERRIDE8_SYS_CFG_APC1PLL_LVAL_SHFT                                               19
#define HWIO_FEATURE_CONFIG_OVERRIDE8_APSS_KRYO_PP_DISABLE_BMSK                                          0x40000
#define HWIO_FEATURE_CONFIG_OVERRIDE8_APSS_KRYO_PP_DISABLE_SHFT                                               18
#define HWIO_FEATURE_CONFIG_OVERRIDE8_SYS_CFG_L3_SIZE_RED_BMSK                                           0x20000
#define HWIO_FEATURE_CONFIG_OVERRIDE8_SYS_CFG_L3_SIZE_RED_SHFT                                                17
#define HWIO_FEATURE_CONFIG_OVERRIDE8_SYS_APSS_APBDFDEN_BMSK                                             0x10000
#define HWIO_FEATURE_CONFIG_OVERRIDE8_SYS_APSS_APBDFDEN_SHFT                                                  16
#define HWIO_FEATURE_CONFIG_OVERRIDE8_MIBU_PP_DISABLE_BMSK                                                0x8000
#define HWIO_FEATURE_CONFIG_OVERRIDE8_MIBU_PP_DISABLE_SHFT                                                    15
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCAST_ATOMIC_MP_BMSK                                            0x4000
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCAST_ATOMIC_MP_SHFT                                                14
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCASTOUTERMP_BMSK                                               0x2000
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCASTOUTERMP_SHFT                                                   13
#define HWIO_FEATURE_CONFIG_OVERRIDE8_DEVNRINTERLEAVE_BMSK                                                0x1800
#define HWIO_FEATURE_CONFIG_OVERRIDE8_DEVNRINTERLEAVE_SHFT                                                    11
#define HWIO_FEATURE_CONFIG_OVERRIDE8_DEFAULT_MP_BMSK                                                      0x400
#define HWIO_FEATURE_CONFIG_OVERRIDE8_DEFAULT_MP_SHFT                                                         10
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCAST_CACHE_MAINT_MP_BMSK                                        0x200
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCAST_CACHE_MAINT_MP_SHFT                                            9
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCAST_TLB_OUTER_BMSK                                             0x100
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCAST_TLB_OUTER_SHFT                                                 8
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCAST_TLB_INNER_BMSK                                              0x80
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCAST_TLB_INNER_SHFT                                                 7
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCASTICINVAL_BMSK                                                 0x40
#define HWIO_FEATURE_CONFIG_OVERRIDE8_BROADCASTICINVAL_SHFT                                                    6
#define HWIO_FEATURE_CONFIG_OVERRIDE8_APPS_BOOT_FSM_FUSE_BMSK                                               0x3f
#define HWIO_FEATURE_CONFIG_OVERRIDE8_APPS_BOOT_FSM_FUSE_SHFT                                                  0

#define HWIO_FEATURE_CONFIG_OVERRIDE9_ADDR                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa24)
#define HWIO_FEATURE_CONFIG_OVERRIDE9_RMSK                                                            0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE9_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE9_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE9_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE9_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE9_TURING_Q6SS_L2TCM_EN_4_0_BMSK                                   0xf8000000
#define HWIO_FEATURE_CONFIG_OVERRIDE9_TURING_Q6SS_L2TCM_EN_4_0_SHFT                                           27
#define HWIO_FEATURE_CONFIG_OVERRIDE9_TURING_Q6SS_HVX_EN_BMSK                                          0x4000000
#define HWIO_FEATURE_CONFIG_OVERRIDE9_TURING_Q6SS_HVX_EN_SHFT                                                 26
#define HWIO_FEATURE_CONFIG_OVERRIDE9_TURING_Q6SS_HVX_HALF_BMSK                                        0x2000000
#define HWIO_FEATURE_CONFIG_OVERRIDE9_TURING_Q6SS_HVX_HALF_SHFT                                               25
#define HWIO_FEATURE_CONFIG_OVERRIDE9_TURING_Q6SS_PLL_L_MAX_BMSK                                       0x1fffe00
#define HWIO_FEATURE_CONFIG_OVERRIDE9_TURING_Q6SS_PLL_L_MAX_SHFT                                               9
#define HWIO_FEATURE_CONFIG_OVERRIDE9_LEGACY_MBNV6_OVERRIDE_BMSK                                           0x100
#define HWIO_FEATURE_CONFIG_OVERRIDE9_LEGACY_MBNV6_OVERRIDE_SHFT                                               8
#define HWIO_FEATURE_CONFIG_OVERRIDE9_APSS_SPARE_NEW_IN_BMSK                                                0xf8
#define HWIO_FEATURE_CONFIG_OVERRIDE9_APSS_SPARE_NEW_IN_SHFT                                                   3
#define HWIO_FEATURE_CONFIG_OVERRIDE9_SYS_CFG_GOLDPLUS_PLL_LVAL_7_5_BMSK                                     0x7
#define HWIO_FEATURE_CONFIG_OVERRIDE9_SYS_CFG_GOLDPLUS_PLL_LVAL_7_5_SHFT                                       0

#define HWIO_FEATURE_CONFIG_OVERRIDE10_ADDR                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa28)
#define HWIO_FEATURE_CONFIG_OVERRIDE10_RMSK                                                           0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE10_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE10_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE10_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE10_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE10_FEATURE_CONFIG_351_337_BMSK                                    0xfffe0000
#define HWIO_FEATURE_CONFIG_OVERRIDE10_FEATURE_CONFIG_351_337_SHFT                                            17
#define HWIO_FEATURE_CONFIG_OVERRIDE10_MODEM_FEATURE_DISABLE_SPARE_14_8_BMSK                             0x1fc00
#define HWIO_FEATURE_CONFIG_OVERRIDE10_MODEM_FEATURE_DISABLE_SPARE_14_8_SHFT                                  10
#define HWIO_FEATURE_CONFIG_OVERRIDE10_FEATURE_CONFIG_BMSK                                                 0x380
#define HWIO_FEATURE_CONFIG_OVERRIDE10_FEATURE_CONFIG_SHFT                                                     7
#define HWIO_FEATURE_CONFIG_OVERRIDE10_TURING_QDSP_HMX_FLTARRAYTHROTTLE_BMSK                                0x60
#define HWIO_FEATURE_CONFIG_OVERRIDE10_TURING_QDSP_HMX_FLTARRAYTHROTTLE_SHFT                                   5
#define HWIO_FEATURE_CONFIG_OVERRIDE10_TURING_QDSP6_HMX_FXPARRAYTHROTTLE_BMSK                               0x18
#define HWIO_FEATURE_CONFIG_OVERRIDE10_TURING_QDSP6_HMX_FXPARRAYTHROTTLE_SHFT                                  3
#define HWIO_FEATURE_CONFIG_OVERRIDE10_TURING_QDSP6_HVX_VTCMSIZE_BMSK                                        0x6
#define HWIO_FEATURE_CONFIG_OVERRIDE10_TURING_QDSP6_HVX_VTCMSIZE_SHFT                                          1
#define HWIO_FEATURE_CONFIG_OVERRIDE10_TURING_Q6SS_L2TCM_EN_5_BMSK                                           0x1
#define HWIO_FEATURE_CONFIG_OVERRIDE10_TURING_Q6SS_L2TCM_EN_5_SHFT                                             0

#define HWIO_FEATURE_CONFIG_OVERRIDE11_ADDR                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa2c)
#define HWIO_FEATURE_CONFIG_OVERRIDE11_RMSK                                                           0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE11_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE11_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE11_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE11_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE11_FEATURE_CONFIG_383_352_BMSK                                    0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE11_FEATURE_CONFIG_383_352_SHFT                                             0

#define HWIO_FEATURE_CONFIG_OVERRIDE12_ADDR                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa30)
#define HWIO_FEATURE_CONFIG_OVERRIDE12_RMSK                                                           0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE12_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE12_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE12_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE12_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE12_FEATURE_CONFIG_415_384_BMSK                                    0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE12_FEATURE_CONFIG_415_384_SHFT                                             0

#define HWIO_FEATURE_CONFIG_OVERRIDE13_ADDR                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa34)
#define HWIO_FEATURE_CONFIG_OVERRIDE13_RMSK                                                           0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE13_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE13_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE13_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE13_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE13_FEATURE_CONFIG_447_416_BMSK                                    0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE13_FEATURE_CONFIG_447_416_SHFT                                             0

#define HWIO_FEATURE_CONFIG_OVERRIDE14_ADDR                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa38)
#define HWIO_FEATURE_CONFIG_OVERRIDE14_RMSK                                                           0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE14_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE14_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE14_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE14_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE14_FEATURE_CONFIG_479_448_BMSK                                    0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE14_FEATURE_CONFIG_479_448_SHFT                                             0

#define HWIO_FEATURE_CONFIG_OVERRIDE15_ADDR                                                           (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xa3c)
#define HWIO_FEATURE_CONFIG_OVERRIDE15_RMSK                                                           0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE15_IN                    \
                in_dword(HWIO_FEATURE_CONFIG_OVERRIDE15_ADDR)
#define HWIO_FEATURE_CONFIG_OVERRIDE15_INM(m)            \
                in_dword_masked(HWIO_FEATURE_CONFIG_OVERRIDE15_ADDR, m)
#define HWIO_FEATURE_CONFIG_OVERRIDE15_FEATURE_CONFIG_511_480_BMSK                                    0xffffffff
#define HWIO_FEATURE_CONFIG_OVERRIDE15_FEATURE_CONFIG_511_480_SHFT                                             0

#define HWIO_QFPROM2_MATCH_STATUS_ADDR                                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xb00)
#define HWIO_QFPROM2_MATCH_STATUS_RMSK                                                                0xffffffff
#define HWIO_QFPROM2_MATCH_STATUS_IN                    \
                in_dword(HWIO_QFPROM2_MATCH_STATUS_ADDR)
#define HWIO_QFPROM2_MATCH_STATUS_INM(m)            \
                in_dword_masked(HWIO_QFPROM2_MATCH_STATUS_ADDR, m)
#define HWIO_QFPROM2_MATCH_STATUS_FLAG_BMSK                                                           0xffffffff
#define HWIO_QFPROM2_MATCH_STATUS_FLAG_SHFT                                                                    0

#define HWIO_QFPROM3_MATCH_STATUS_ADDR                                                                (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xb04)
#define HWIO_QFPROM3_MATCH_STATUS_RMSK                                                                0xffffffff
#define HWIO_QFPROM3_MATCH_STATUS_IN                    \
                in_dword(HWIO_QFPROM3_MATCH_STATUS_ADDR)
#define HWIO_QFPROM3_MATCH_STATUS_INM(m)            \
                in_dword_masked(HWIO_QFPROM3_MATCH_STATUS_ADDR, m)
#define HWIO_QFPROM3_MATCH_STATUS_FLAG_BMSK                                                           0xffffffff
#define HWIO_QFPROM3_MATCH_STATUS_FLAG_SHFT                                                                    0

#define HWIO_QCCHIPFAMSVCSROOTKEYSETVECTOR_ADDR                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xb10)
#define HWIO_QCCHIPFAMSVCSROOTKEYSETVECTOR_RMSK                                                             0xff
#define HWIO_QCCHIPFAMSVCSROOTKEYSETVECTOR_IN                    \
                in_dword(HWIO_QCCHIPFAMSVCSROOTKEYSETVECTOR_ADDR)
#define HWIO_QCCHIPFAMSVCSROOTKEYSETVECTOR_INM(m)            \
                in_dword_masked(HWIO_QCCHIPFAMSVCSROOTKEYSETVECTOR_ADDR, m)
#define HWIO_QCCHIPFAMSVCSROOTKEYSETVECTOR_QCCHIPFAMSVCSROOTKEYSETVECTOR_BMSK                               0xff
#define HWIO_QCCHIPFAMSVCSROOTKEYSETVECTOR_QCCHIPFAMSVCSROOTKEYSETVECTOR_SHFT                                  0

#define HWIO_TME_DEBUG_STATE_ADDR                                                                     (FUSE_CONTROLLER_SW_RANGE4_REG_BASE            + 0xb14)
#define HWIO_TME_DEBUG_STATE_RMSK                                                                            0x1
#define HWIO_TME_DEBUG_STATE_IN                    \
                in_dword(HWIO_TME_DEBUG_STATE_ADDR)
#define HWIO_TME_DEBUG_STATE_INM(m)            \
                in_dword_masked(HWIO_TME_DEBUG_STATE_ADDR, m)
#define HWIO_TME_DEBUG_STATE_TME_DEBUG_STATE_BMSK                                                            0x1
#define HWIO_TME_DEBUG_STATE_TME_DEBUG_STATE_SHFT                                                              0


#endif /* __HWIO_TME_H__ */
