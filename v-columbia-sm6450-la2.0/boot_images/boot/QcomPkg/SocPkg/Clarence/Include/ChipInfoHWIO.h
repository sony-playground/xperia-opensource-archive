#ifndef __CHIPINFOHWIO_NETRANI_H__
#define __CHIPINFOHWIO_NETRANI_H__
/*
===========================================================================
*/
/**
    @file ChipInfoHWIO_Clarence.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM4450 (Clarence) [clarence_v1.0_p3q3r41_MTO]
 
    This file contains HWIO register definitions for the following modules:
        FUSE_CONTROLLER_SW_RANGE4
        QFPROM_CORR
        TCSR_TCSR_REGS
        TLMM_REG

    'Include' filters applied: CHIP_UNIQUE_ID_.*[FUSE_CONTROLLER_SW_RANGE4] QFPROM_CORR_PTE_ROW1_(MSB|LSB)[QFPROM_CORR] QFPROM_CORR_QC_CONFIG_ROW2_LSB[QFPROM_CORR] QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB[QFPROM_CORR] TCSR_SOC_HW_VERSION[TCSR_TCSR_REGS] TLMM_HW_REVISION_NUM.*[TLMM_REG] 

    Generation parameters: 
    { 'filename': 'ChipInfoHWIO_Clarence.h',
      'header': '#include "msmhwiobase.h"\n'
                '\n'
                '#define CHIPINFO_QCOM_MFG_ID_REG            '
                'TLMM_HW_REVISION_NUMBER_0\n'
                '#define CHIPINFO_JTAG_ID_REG                '
                'TLMM_HW_REVISION_NUMBER_1\n'
                '#define CHIPINFO_REVISION_NUMBER_REG        '
                'TLMM_HW_REVISION_NUMBER_2\n'
                '#define CHIPINFO_TCSR_SOC_HW_VERSION_REG    TCSR_SOC_HW_VERSION\n'
                '#define CHIPINFO_FOUNDRY_ID_REG             '
                'QFPROM_CORR_QC_CONFIG_ROW2_LSB\n'
                '#define CHIPINFO_SERIAL_NUM_REG             CHIP_UNIQUE_ID_0\n'
                '#define CHIPINFO_QFPROM_CHIP_ID_REG         CHIP_UNIQUE_ID_1\n'
                '#define CHIPINFO_SKU_ID_REG                 '
                'QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB\n'
                '#define CHIPINFO_P_CODE_REG                 '
                'QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB',
      'module-filter-include': { 'FUSE_CONTROLLER_SW_RANGE4': ['CHIP_UNIQUE_ID_.*'],
                                 'QFPROM_CORR': [ 'QFPROM_CORR_PTE_ROW1_(MSB|LSB)',
                                                  'QFPROM_CORR_QC_CONFIG_ROW2_LSB',
                                                  'QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB'],
                                 'TCSR_TCSR_REGS': ['TCSR_SOC_HW_VERSION'],
                                 'TLMM_REG': ['TLMM_HW_REVISION_NUM.*']},
      'modules': [ 'FUSE_CONTROLLER_SW_RANGE4',
                   'QFPROM_CORR',
                   'TCSR_TCSR_REGS',
                   'TLMM_REG']}
*/
/*
    ===========================================================================

    Copyright (c) 2022 Qualcomm Technologies, Inc.
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

    $Header: //components/dev/core.boot/6.0/aravapal.core.boot.6.0.tip_dev/QcomPkg/SocPkg/Clarence/Include/ChipInfoHWIO.h#1 $
    $DateTime: 2022/04/30 21:50:34 $
    $Author: aravapal $

    ===========================================================================
*/

#include "msmhwiobase.h"

#define CHIPINFO_QCOM_MFG_ID_REG            TLMM_HW_REVISION_NUMBER_0
#define CHIPINFO_JTAG_ID_REG                TLMM_HW_REVISION_NUMBER_1
#define CHIPINFO_REVISION_NUMBER_REG        TLMM_HW_REVISION_NUMBER_2
#define CHIPINFO_TCSR_SOC_HW_VERSION_REG    TCSR_SOC_HW_VERSION
#define CHIPINFO_FOUNDRY_ID_REG             QFPROM_CORR_QC_CONFIG_ROW2_LSB
#define CHIPINFO_SERIAL_NUM_REG             CHIP_UNIQUE_ID_0
#define CHIPINFO_QFPROM_CHIP_ID_REG         CHIP_UNIQUE_ID_1
#define CHIPINFO_SKU_ID_REG                 QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB
#define CHIPINFO_P_CODE_REG                 QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB

/*----------------------------------------------------------------------------
 * MODULE: FUSE_CONTROLLER_SW_RANGE4
 *--------------------------------------------------------------------------*/

#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE                                                            (TMESS_BASE      + 0x021c8000)
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE                                                       0x1000
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_USED                                                       0xe14

#define HWIO_CHIP_UNIQUE_ID_0_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x610)
#define HWIO_CHIP_UNIQUE_ID_0_RMSK                                                                    0xffffffff
#define HWIO_CHIP_UNIQUE_ID_0_IN                    \
                in_dword(HWIO_CHIP_UNIQUE_ID_0_ADDR)
#define HWIO_CHIP_UNIQUE_ID_0_INM(m)            \
                in_dword_masked(HWIO_CHIP_UNIQUE_ID_0_ADDR, m)
#define HWIO_CHIP_UNIQUE_ID_0_SERIAL_NUM_BMSK                                                         0xffffffff
#define HWIO_CHIP_UNIQUE_ID_0_SERIAL_NUM_SHFT                                                                  0

#define HWIO_CHIP_UNIQUE_ID_1_ADDR                                                                    (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x614)
#define HWIO_CHIP_UNIQUE_ID_1_RMSK                                                                    0xffffffff
#define HWIO_CHIP_UNIQUE_ID_1_IN                    \
                in_dword(HWIO_CHIP_UNIQUE_ID_1_ADDR)
#define HWIO_CHIP_UNIQUE_ID_1_INM(m)            \
                in_dword_masked(HWIO_CHIP_UNIQUE_ID_1_ADDR, m)
#define HWIO_CHIP_UNIQUE_ID_1_CHIP_ID_BMSK                                                            0xffffffff
#define HWIO_CHIP_UNIQUE_ID_1_CHIP_ID_SHFT                                                                     0


/*----------------------------------------------------------------------------
 * MODULE: QFPROM_CORR
 *--------------------------------------------------------------------------*/

#define QFPROM_CORR_REG_BASE                                                                                        (TMESS_BASE      + 0x021c2000)
#define QFPROM_CORR_REG_BASE_SIZE                                                                                   0x2000
#define QFPROM_CORR_REG_BASE_USED                                                                                   0xcdc


#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x2f8)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_QC_SPARE_3_31_30_BMSK                                                  0xc0000000
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_QC_SPARE_3_31_30_SHFT                                                          30
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_SUBBINE_BMSK                                                           0x3e000000
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_SUBBINE_SHFT                                                                   25
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_SUBBIND_BMSK                                                            0x1f00000
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_SUBBIND_SHFT                                                                   20
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_SUBBINC_BMSK                                                              0xf8000
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_SUBBINC_SHFT                                                                   15
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_PARTIAL_BIN_BMSK                                                           0x7c00
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_PARTIAL_BIN_SHFT                                                               10
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_SUBBINB_BMSK                                                                0x3e0
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_SUBBINB_SHFT                                                                    5
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_SUBBINA_BMSK                                                                 0x1f
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_LSB_SUBBINA_SHFT                                                                    0

#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x2fc)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_QC_SPARE_3_63_48_BMSK                                                  0xffff0000
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_QC_SPARE_3_63_48_SHFT                                                          16
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_CPUSS_BOOT_FSM_CORE_BMSK                                                   0xff00
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_CPUSS_BOOT_FSM_CORE_SHFT                                                        8
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_SUBBINA_CORE_BMSK                                                            0xff
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW0_MSB_SUBBINA_CORE_SHFT                                                               0

#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x300)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_QC_SPARE_3_95_92_BMSK                                                  0xf0000000
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_QC_SPARE_3_95_92_SHFT                                                          28
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_NSP_UNSUPPORTED_FEATURE_BMSK                                            0xfff0000
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_NSP_UNSUPPORTED_FEATURE_SHFT                                                   16
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_CAMERA_UNSUPPORTED_FEATURE_BMSK                                            0xffff
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_LSB_CAMERA_UNSUPPORTED_FEATURE_SHFT                                                 0

#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x304)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_MSB_QC_SPARE_3_127_104_BMSK                                                0xffffff00
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_MSB_QC_SPARE_3_127_104_SHFT                                                         8
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_MSB_MODEM_UNSUPPORTED_FEATURE_BMSK                                               0xff
#define HWIO_QFPROM_CORR_QC_SPARE_3_ROW1_MSB_MODEM_UNSUPPORTED_FEATURE_SHFT                                                  0

#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_ADDR                                                                    (QFPROM_CORR_REG_BASE      + 0x1a8)
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_TME_PBL_PATCH_VERSION_BMSK                                              0xfe000000
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_TME_PBL_PATCH_VERSION_SHFT                                                      25
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_APPS_PBL_PATCH_VERSION_BMSK                                              0x1fc0000
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_APPS_PBL_PATCH_VERSION_SHFT                                                     18
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_APPS_PBL_BOOT_SPEED_BMSK                                                   0x30000
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_APPS_PBL_BOOT_SPEED_SHFT                                                        16
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_VENDOR_LOCK_BMSK                                                            0xf000
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_VENDOR_LOCK_SHFT                                                                12
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_FOUNDRY_ID_BMSK                                                              0xf00
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_FOUNDRY_ID_SHFT                                                                  8
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_STACKED_MEMORY_ID_BMSK                                                        0xf8
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_STACKED_MEMORY_ID_SHFT                                                           3
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_SEC_TAP_ACCESS_DISABLE_15_13_BMSK                                              0x7
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_SEC_TAP_ACCESS_DISABLE_15_13_SHFT                                                0
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_ADDR                                                               (QFPROM_CORR_REG_BASE      + 0x150)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_RMSK                                                               0xffffffff
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_ADDR)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_FEATURE_CONFIG_351_347_BMSK                                        0xf8000000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_FEATURE_CONFIG_351_347_SHFT                                                27
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_PCIE_PHY_BYPASS_BMSK                                                0x4000000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_PCIE_PHY_BYPASS_SHFT                                                       26
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_DSI_PHY_BYPASS_BMSK                                                 0x2000000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_DSI_PHY_BYPASS_SHFT                                                        25
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_CSI_PHY_BYPASS_BMSK                                                 0x1000000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_CSI_PHY_BYPASS_SHFT                                                        24
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_DP_DISABLE_BMSK                                                      0x800000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_DP_DISABLE_SHFT                                                            23
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_FEATURE_CONFIG_342_BMSK                                              0x400000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_FEATURE_CONFIG_342_SHFT                                                    22
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_EFUSE_CAMERA_DISABLE_IF_BMSK                                         0x200000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_EFUSE_CAMERA_DISABLE_IF_SHFT                                               21
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_EFUSE_CAMERA_PHY_2_DISABLE_BMSK                                      0x100000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_EFUSE_CAMERA_PHY_2_DISABLE_SHFT                                            20
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_EFUSE_CAMERA_OPE_VID_OUT_8_BPP_LIMIT_ENABLE_BMSK                      0x80000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_EFUSE_CAMERA_OPE_VID_OUT_8_BPP_LIMIT_ENABLE_SHFT                           19
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_EFUSE_CAMERA_MP_LIMIT_ENABLE_BMSK                                     0x60000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_EFUSE_CAMERA_MP_LIMIT_ENABLE_SHFT                                          17
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_MODEM_FEATURE_DISABLE_SPARE_14_8_BMSK                                 0x1fc00
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_MODEM_FEATURE_DISABLE_SPARE_14_8_SHFT                                      10
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_SDCC_FUSE_ICE_DISABLE_BMSK                                              0x200
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_SDCC_FUSE_ICE_DISABLE_SHFT                                                  9
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_FEATURE_CONFIG_328_321_BMSK                                             0x1fe
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_FEATURE_CONFIG_328_321_SHFT                                                 1
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_TURING_Q6SS_L2TCM_EN_5_BMSK                                               0x1
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB_TURING_Q6SS_L2TCM_EN_5_SHFT                                                 0

#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_ADDR                                                               (QFPROM_CORR_REG_BASE      + 0x154)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_RMSK                                                               0xffffffff
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_ADDR)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_PIMEM_MEM_SIZE_BMSK                                                0xc0000000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_PIMEM_MEM_SIZE_SHFT                                                        30
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_FEATURE_CONFIG_381_376_BMSK                                        0x3f000000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_FEATURE_CONFIG_381_376_SHFT                                                24
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_SKU_ID_BMSK                                                          0xff0000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_SKU_ID_SHFT                                                                16
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_P_CODE_BMSK                                                            0xff00
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_P_CODE_SHFT                                                                 8
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_FEATURE_CONFIG_359_352_BMSK                                              0xff
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB_FEATURE_CONFIG_359_352_SHFT                                                 0


/*----------------------------------------------------------------------------
 * MODULE: TCSR_TCSR_REGS
 *--------------------------------------------------------------------------*/

#define TCSR_TCSR_REGS_REG_BASE                                                                                                              (CORE_TOP_CSR_BASE      + 0x000c0000)
#define TCSR_TCSR_REGS_REG_BASE_SIZE                                                                                                         0x30000
#define TCSR_TCSR_REGS_REG_BASE_USED                                                                                                         0x2f000

#define HWIO_TCSR_SOC_HW_VERSION_ADDR                                                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x8000)
#define HWIO_TCSR_SOC_HW_VERSION_RMSK                                                                                                        0xffffffff
#define HWIO_TCSR_SOC_HW_VERSION_IN                    \
                in_dword(HWIO_TCSR_SOC_HW_VERSION_ADDR)
#define HWIO_TCSR_SOC_HW_VERSION_INM(m)            \
                in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_ADDR, m)
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_BMSK                                                                                          0xf0000000
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_SHFT                                                                                                  28
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_BMSK                                                                                           0xfff0000
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_SHFT                                                                                                  16
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_BMSK                                                                                              0xff00
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_SHFT                                                                                                   8
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_BMSK                                                                                                0xff
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_SHFT                                                                                                   0

/*----------------------------------------------------------------------------
 * MODULE: TLMM_REG
 *--------------------------------------------------------------------------*/

#define TLMM_REG_REG_BASE                                                                    (TLMM_BASE      + 0x00100000)
#define TLMM_REG_REG_BASE_SIZE                                                               0xf00000
#define TLMM_REG_REG_BASE_USED                                                               0xa601c

#define HWIO_TLMM_HW_REVISION_NUMBER_0_ADDR                                                  (TLMM_REG_REG_BASE      + 0x8a010)
#define HWIO_TLMM_HW_REVISION_NUMBER_0_RMSK                                                       0xfff
#define HWIO_TLMM_HW_REVISION_NUMBER_0_IN                    \
                in_dword(HWIO_TLMM_HW_REVISION_NUMBER_0_ADDR)
#define HWIO_TLMM_HW_REVISION_NUMBER_0_INM(m)            \
                in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_0_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_0_QUALCOMM_MFG_ID_BMSK                                       0xffe
#define HWIO_TLMM_HW_REVISION_NUMBER_0_QUALCOMM_MFG_ID_SHFT                                           1
#define HWIO_TLMM_HW_REVISION_NUMBER_0_START_BIT_BMSK                                               0x1
#define HWIO_TLMM_HW_REVISION_NUMBER_0_START_BIT_SHFT                                                 0

#define HWIO_TLMM_HW_REVISION_NUMBER_1_ADDR                                                  (TLMM_REG_REG_BASE      + 0x8a014)
#define HWIO_TLMM_HW_REVISION_NUMBER_1_RMSK                                                      0xffff
#define HWIO_TLMM_HW_REVISION_NUMBER_1_IN                    \
                in_dword(HWIO_TLMM_HW_REVISION_NUMBER_1_ADDR)
#define HWIO_TLMM_HW_REVISION_NUMBER_1_INM(m)            \
                in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_1_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_1_PRODUCT_DEVICE_ID_BMSK                                    0xffff
#define HWIO_TLMM_HW_REVISION_NUMBER_1_PRODUCT_DEVICE_ID_SHFT                                         0

#define HWIO_TLMM_HW_REVISION_NUMBER_2_ADDR                                                  (TLMM_REG_REG_BASE      + 0x8a018)
#define HWIO_TLMM_HW_REVISION_NUMBER_2_RMSK                                                         0xf
#define HWIO_TLMM_HW_REVISION_NUMBER_2_IN                    \
                in_dword(HWIO_TLMM_HW_REVISION_NUMBER_2_ADDR)
#define HWIO_TLMM_HW_REVISION_NUMBER_2_INM(m)            \
                in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_2_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_2_VERSION_ID_BMSK                                              0xf
#define HWIO_TLMM_HW_REVISION_NUMBER_2_VERSION_ID_SHFT                                                0


#endif /* __CHIPINFOHWIO_NETRANI_H__ */
