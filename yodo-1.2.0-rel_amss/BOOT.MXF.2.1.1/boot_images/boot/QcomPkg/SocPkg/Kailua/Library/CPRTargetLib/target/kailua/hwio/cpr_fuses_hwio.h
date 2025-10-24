#ifndef __CPR_FUSES_HWIO_H__
#define __CPR_FUSES_HWIO_H__
/*
===========================================================================
*/
/**
    @file cpr_fuses_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8550 (Kailua) [z_tme_fusecontroller_kailua_p3q2r41]
 
    This file contains HWIO register definitions for the following modules:
        FUSE_CONTROLLER_SW_RANGE4
        QFPROM_CORR

    'Include' filters applied: CALIBRATION[FUSE_CONTROLLER_SW_RANGE4] QFPROM_CORR_CALIBRATION[QFPROM_CORR] QFPROM_CORR_PTE[QFPROM_CORR] 

    Generation parameters: 
    { 'filename': 'cpr_fuses_hwio.h',
      'header': '#include "msmhwiobase.h"',
      'module-filter-include': { 'FUSE_CONTROLLER_SW_RANGE4': ['CALIBRATION'],
                                 'QFPROM_CORR': [ 'QFPROM_CORR_CALIBRATION',
                                                  'QFPROM_CORR_PTE']},
      'modules': ['FUSE_CONTROLLER_SW_RANGE4', 'QFPROM_CORR'],
      'output-fvals': True,
      'output-offsets': True}
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

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/CPRTargetLib/target/kailua/hwio/cpr_fuses_hwio.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"
#define TME_FUSECONTROLLER_BASE (TMESS_BASE            + 0x021c0000)

/*----------------------------------------------------------------------------
 * MODULE: FUSE_CONTROLLER_SW_RANGE4
 *--------------------------------------------------------------------------*/

#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE                                                            (TME_FUSECONTROLLER_BASE      + 0x00008000)
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE                                                       0x1000
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_USED                                                       0xc78
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS                                                       0x00008000

#define HWIO_CALIBRATION0_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb18)
#define HWIO_CALIBRATION0_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb18)
#define HWIO_CALIBRATION0_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION0_IN                    \
                in_dword(HWIO_CALIBRATION0_ADDR)
#define HWIO_CALIBRATION0_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION0_ADDR, m)
#define HWIO_CALIBRATION0_USB2PHY_RCAL_CODE_0_BMSK                                                    0x80000000
#define HWIO_CALIBRATION0_USB2PHY_RCAL_CODE_0_SHFT                                                            31
#define HWIO_CALIBRATION0_BANDGAP_TRIM_BMSK                                                           0x7f000000
#define HWIO_CALIBRATION0_BANDGAP_TRIM_SHFT                                                                   24
#define HWIO_CALIBRATION0_REFGEN_2_NORTH_BGV_TRIM_BMSK                                                  0xff0000
#define HWIO_CALIBRATION0_REFGEN_2_NORTH_BGV_TRIM_SHFT                                                        16
#define HWIO_CALIBRATION0_REFGEN_0_NORTH_BGV_TRIM_BMSK                                                    0xff00
#define HWIO_CALIBRATION0_REFGEN_0_NORTH_BGV_TRIM_SHFT                                                         8
#define HWIO_CALIBRATION0_REFGEN_1_SOUTH_BGV_TRIM_BMSK                                                      0xff
#define HWIO_CALIBRATION0_REFGEN_1_SOUTH_BGV_TRIM_SHFT                                                         0

#define HWIO_CALIBRATION1_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb1c)
#define HWIO_CALIBRATION1_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb1c)
#define HWIO_CALIBRATION1_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION1_IN                    \
                in_dword(HWIO_CALIBRATION1_ADDR)
#define HWIO_CALIBRATION1_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION1_ADDR, m)
#define HWIO_CALIBRATION1_CALIBRATION_63_44_BMSK                                                      0xfffff000
#define HWIO_CALIBRATION1_CALIBRATION_63_44_SHFT                                                              12
#define HWIO_CALIBRATION1_APSS_CS_ADC_VREFP_CTRL_IN_BMSK                                                   0xf00
#define HWIO_CALIBRATION1_APSS_CS_ADC_VREFP_CTRL_IN_SHFT                                                       8
#define HWIO_CALIBRATION1_GFX_CS_ADC_VREFP_CTRL_IN_BMSK                                                     0x80
#define HWIO_CALIBRATION1_GFX_CS_ADC_VREFP_CTRL_IN_SHFT                                                        7
#define HWIO_CALIBRATION1_ISENSE_CS_ADC_VREFP_CTRL_BMSK                                                     0x78
#define HWIO_CALIBRATION1_ISENSE_CS_ADC_VREFP_CTRL_SHFT                                                        3
#define HWIO_CALIBRATION1_USB2PHY_RCAL_CODE_3_1_BMSK                                                         0x7
#define HWIO_CALIBRATION1_USB2PHY_RCAL_CODE_3_1_SHFT                                                           0

#define HWIO_CALIBRATION2_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb20)
#define HWIO_CALIBRATION2_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb20)
#define HWIO_CALIBRATION2_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION2_IN                    \
                in_dword(HWIO_CALIBRATION2_ADDR)
#define HWIO_CALIBRATION2_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION2_ADDR, m)
#define HWIO_CALIBRATION2_CALIBRATION_95_64_BMSK                                                      0xffffffff
#define HWIO_CALIBRATION2_CALIBRATION_95_64_SHFT                                                               0

#define HWIO_CALIBRATION3_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb24)
#define HWIO_CALIBRATION3_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb24)
#define HWIO_CALIBRATION3_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION3_IN                    \
                in_dword(HWIO_CALIBRATION3_ADDR)
#define HWIO_CALIBRATION3_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION3_ADDR, m)
#define HWIO_CALIBRATION3_CALIBRATION_127_96_BMSK                                                     0xffffffff
#define HWIO_CALIBRATION3_CALIBRATION_127_96_SHFT                                                              0

#define HWIO_CALIBRATION4_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb28)
#define HWIO_CALIBRATION4_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb28)
#define HWIO_CALIBRATION4_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION4_IN                    \
                in_dword(HWIO_CALIBRATION4_ADDR)
#define HWIO_CALIBRATION4_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION4_ADDR, m)
#define HWIO_CALIBRATION4_DDRSS_CH3DQ0_PNTUNE_HT_BMSK                                                 0xc0000000
#define HWIO_CALIBRATION4_DDRSS_CH3DQ0_PNTUNE_HT_SHFT                                                         30
#define HWIO_CALIBRATION4_DDRSS_CH3CA_PNTUNE_HT_BMSK                                                  0x30000000
#define HWIO_CALIBRATION4_DDRSS_CH3CA_PNTUNE_HT_SHFT                                                          28
#define HWIO_CALIBRATION4_DDRSS_CH2DQ1_PNTUNE_HT_BMSK                                                  0xc000000
#define HWIO_CALIBRATION4_DDRSS_CH2DQ1_PNTUNE_HT_SHFT                                                         26
#define HWIO_CALIBRATION4_DDRSS_CH2DQ0_PNTUNE_HT_BMSK                                                  0x3000000
#define HWIO_CALIBRATION4_DDRSS_CH2DQ0_PNTUNE_HT_SHFT                                                         24
#define HWIO_CALIBRATION4_CPR8_TARG_VOLT_SVS2_BMSK                                                      0xfc0000
#define HWIO_CALIBRATION4_CPR8_TARG_VOLT_SVS2_SHFT                                                            18
#define HWIO_CALIBRATION4_CPR5_TARG_VOLT_SVS_BMSK                                                        0x3f000
#define HWIO_CALIBRATION4_CPR5_TARG_VOLT_SVS_SHFT                                                             12
#define HWIO_CALIBRATION4_CPR3_TARG_VOLT_NOM_BMSK                                                          0xfc0
#define HWIO_CALIBRATION4_CPR3_TARG_VOLT_NOM_SHFT                                                              6
#define HWIO_CALIBRATION4_CPR3_TARG_VOLT_TUR_BMSK                                                           0x3f
#define HWIO_CALIBRATION4_CPR3_TARG_VOLT_TUR_SHFT                                                              0

#define HWIO_CALIBRATION5_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb2c)
#define HWIO_CALIBRATION5_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb2c)
#define HWIO_CALIBRATION5_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION5_IN                    \
                in_dword(HWIO_CALIBRATION5_ADDR)
#define HWIO_CALIBRATION5_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION5_ADDR, m)
#define HWIO_CALIBRATION5_ISENSE_FUSE_CURRENT_CPU4_F2_7_0_BMSK                                        0xff000000
#define HWIO_CALIBRATION5_ISENSE_FUSE_CURRENT_CPU4_F2_7_0_SHFT                                                24
#define HWIO_CALIBRATION5_ISENSE_FUSE_CURRENT_CPU4_F1_BMSK                                              0xffc000
#define HWIO_CALIBRATION5_ISENSE_FUSE_CURRENT_CPU4_F1_SHFT                                                    14
#define HWIO_CALIBRATION5_OPAMP_FUSE_CPURAIL_CPU8_FT_BMSK                                                 0x3f00
#define HWIO_CALIBRATION5_OPAMP_FUSE_CPURAIL_CPU8_FT_SHFT                                                      8
#define HWIO_CALIBRATION5_OPAMP_FUSE_CPURAIL_CPU8_WS_BMSK                                                   0xfc
#define HWIO_CALIBRATION5_OPAMP_FUSE_CPURAIL_CPU8_WS_SHFT                                                      2
#define HWIO_CALIBRATION5_DDRSS_CH3DQ1_PNTUNE_HT_BMSK                                                        0x3
#define HWIO_CALIBRATION5_DDRSS_CH3DQ1_PNTUNE_HT_SHFT                                                          0

#define HWIO_CALIBRATION6_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb30)
#define HWIO_CALIBRATION6_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb30)
#define HWIO_CALIBRATION6_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION6_IN                    \
                in_dword(HWIO_CALIBRATION6_ADDR)
#define HWIO_CALIBRATION6_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION6_ADDR, m)
#define HWIO_CALIBRATION6_ISENSE_FUSE_CURRENT_CPU6_F1_BMSK                                            0xffc00000
#define HWIO_CALIBRATION6_ISENSE_FUSE_CURRENT_CPU6_F1_SHFT                                                    22
#define HWIO_CALIBRATION6_ISENSE_FUSE_CURRENT_CPU5_F2_BMSK                                              0x3ff000
#define HWIO_CALIBRATION6_ISENSE_FUSE_CURRENT_CPU5_F2_SHFT                                                    12
#define HWIO_CALIBRATION6_ISENSE_FUSE_CURRENT_CPU5_F1_BMSK                                                 0xffc
#define HWIO_CALIBRATION6_ISENSE_FUSE_CURRENT_CPU5_F1_SHFT                                                     2
#define HWIO_CALIBRATION6_ISENSE_FUSE_CURRENT_CPU4_F2_9_8_BMSK                                               0x3
#define HWIO_CALIBRATION6_ISENSE_FUSE_CURRENT_CPU4_F2_9_8_SHFT                                                 0

#define HWIO_CALIBRATION7_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb34)
#define HWIO_CALIBRATION7_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb34)
#define HWIO_CALIBRATION7_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION7_IN                    \
                in_dword(HWIO_CALIBRATION7_ADDR)
#define HWIO_CALIBRATION7_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION7_ADDR, m)
#define HWIO_CALIBRATION7_ISENSE_FUSE_CURRENT_CPU8_F1_1_0_BMSK                                        0xc0000000
#define HWIO_CALIBRATION7_ISENSE_FUSE_CURRENT_CPU8_F1_1_0_SHFT                                                30
#define HWIO_CALIBRATION7_ISENSE_FUSE_CURRENT_CPU7_F2_BMSK                                            0x3ff00000
#define HWIO_CALIBRATION7_ISENSE_FUSE_CURRENT_CPU7_F2_SHFT                                                    20
#define HWIO_CALIBRATION7_ISENSE_FUSE_CURRENT_CPU7_F1_BMSK                                               0xffc00
#define HWIO_CALIBRATION7_ISENSE_FUSE_CURRENT_CPU7_F1_SHFT                                                    10
#define HWIO_CALIBRATION7_ISENSE_FUSE_CURRENT_CPU6_F2_BMSK                                                 0x3ff
#define HWIO_CALIBRATION7_ISENSE_FUSE_CURRENT_CPU6_F2_SHFT                                                     0

#define HWIO_CALIBRATION8_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb38)
#define HWIO_CALIBRATION8_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb38)
#define HWIO_CALIBRATION8_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION8_IN                    \
                in_dword(HWIO_CALIBRATION8_ADDR)
#define HWIO_CALIBRATION8_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION8_ADDR, m)
#define HWIO_CALIBRATION8_ACC_HV_APC0_1_0_BMSK                                                        0xc0000000
#define HWIO_CALIBRATION8_ACC_HV_APC0_1_0_SHFT                                                                30
#define HWIO_CALIBRATION8_ACC_LV_MXC_BMSK                                                             0x3f000000
#define HWIO_CALIBRATION8_ACC_LV_MXC_SHFT                                                                     24
#define HWIO_CALIBRATION8_CPR5_TARG_VOLT_TUR_BMSK                                                       0xfc0000
#define HWIO_CALIBRATION8_CPR5_TARG_VOLT_TUR_SHFT                                                             18
#define HWIO_CALIBRATION8_ISENSE_FUSE_CURRENT_CPU8_F2_BMSK                                               0x3ff00
#define HWIO_CALIBRATION8_ISENSE_FUSE_CURRENT_CPU8_F2_SHFT                                                     8
#define HWIO_CALIBRATION8_ISENSE_FUSE_CURRENT_CPU8_F1_9_2_BMSK                                              0xff
#define HWIO_CALIBRATION8_ISENSE_FUSE_CURRENT_CPU8_F1_9_2_SHFT                                                 0

#define HWIO_CALIBRATION9_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb3c)
#define HWIO_CALIBRATION9_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb3c)
#define HWIO_CALIBRATION9_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION9_IN                    \
                in_dword(HWIO_CALIBRATION9_ADDR)
#define HWIO_CALIBRATION9_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION9_ADDR, m)
#define HWIO_CALIBRATION9_CPR2_TARG_VOLT_OFFSET_LSVS_BMSK                                             0xf8000000
#define HWIO_CALIBRATION9_CPR2_TARG_VOLT_OFFSET_LSVS_SHFT                                                     27
#define HWIO_CALIBRATION9_CPR1_TARG_VOLT_NOML1_BMSK                                                    0x7e00000
#define HWIO_CALIBRATION9_CPR1_TARG_VOLT_NOML1_SHFT                                                           21
#define HWIO_CALIBRATION9_CALIBRATION_308_304_BMSK                                                      0x1f0000
#define HWIO_CALIBRATION9_CALIBRATION_308_304_SHFT                                                            16
#define HWIO_CALIBRATION9_ACC_LV_APC0_BMSK                                                                0xfc00
#define HWIO_CALIBRATION9_ACC_LV_APC0_SHFT                                                                    10
#define HWIO_CALIBRATION9_ACC_HV_APC1_BMSK                                                                 0x3f0
#define HWIO_CALIBRATION9_ACC_HV_APC1_SHFT                                                                     4
#define HWIO_CALIBRATION9_ACC_HV_APC0_5_2_BMSK                                                               0xf
#define HWIO_CALIBRATION9_ACC_HV_APC0_5_2_SHFT                                                                 0

#define HWIO_CALIBRATION10_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb40)
#define HWIO_CALIBRATION10_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb40)
#define HWIO_CALIBRATION10_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION10_IN                    \
                in_dword(HWIO_CALIBRATION10_ADDR)
#define HWIO_CALIBRATION10_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION10_ADDR, m)
#define HWIO_CALIBRATION10_CALIBRATION_351_325_BMSK                                                   0xffffffe0
#define HWIO_CALIBRATION10_CALIBRATION_351_325_SHFT                                                            5
#define HWIO_CALIBRATION10_CPR2_TARG_VOLT_OFFSET_LSVSD0_BMSK                                                0x1f
#define HWIO_CALIBRATION10_CPR2_TARG_VOLT_OFFSET_LSVSD0_SHFT                                                   0

#define HWIO_CALIBRATION11_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb44)
#define HWIO_CALIBRATION11_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb44)
#define HWIO_CALIBRATION11_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION11_IN                    \
                in_dword(HWIO_CALIBRATION11_ADDR)
#define HWIO_CALIBRATION11_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION11_ADDR, m)
#define HWIO_CALIBRATION11_CALIBRATION_383_352_BMSK                                                   0xffffffff
#define HWIO_CALIBRATION11_CALIBRATION_383_352_SHFT                                                            0

#define HWIO_CALIBRATION12_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb48)
#define HWIO_CALIBRATION12_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb48)
#define HWIO_CALIBRATION12_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION12_IN                    \
                in_dword(HWIO_CALIBRATION12_ADDR)
#define HWIO_CALIBRATION12_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION12_ADDR, m)
#define HWIO_CALIBRATION12_CPR0_TARG_VOLT_OFFSET_SVS1_1_0_BMSK                                        0xc0000000
#define HWIO_CALIBRATION12_CPR0_TARG_VOLT_OFFSET_SVS1_1_0_SHFT                                                30
#define HWIO_CALIBRATION12_CALIBRATION_413_384_BMSK                                                   0x3fffffff
#define HWIO_CALIBRATION12_CALIBRATION_413_384_SHFT                                                            0

#define HWIO_CALIBRATION13_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb4c)
#define HWIO_CALIBRATION13_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb4c)
#define HWIO_CALIBRATION13_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION13_IN                    \
                in_dword(HWIO_CALIBRATION13_ADDR)
#define HWIO_CALIBRATION13_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION13_ADDR, m)
#define HWIO_CALIBRATION13_CALIBRATION_447_BMSK                                                       0x80000000
#define HWIO_CALIBRATION13_CALIBRATION_447_SHFT                                                               31
#define HWIO_CALIBRATION13_CPR2_TARG_VOLT_OFFSET_LSVSL1_BMSK                                          0x7c000000
#define HWIO_CALIBRATION13_CPR2_TARG_VOLT_OFFSET_LSVSL1_SHFT                                                  26
#define HWIO_CALIBRATION13_CPR2_TARG_VOLT_OFFSET_SVSL0_BMSK                                            0x3e00000
#define HWIO_CALIBRATION13_CPR2_TARG_VOLT_OFFSET_SVSL0_SHFT                                                   21
#define HWIO_CALIBRATION13_CALIBRATION_436_434_BMSK                                                     0x1c0000
#define HWIO_CALIBRATION13_CALIBRATION_436_434_SHFT                                                           18
#define HWIO_CALIBRATION13_CPR2_TARG_VOLT_OFFSET_LSVSD3_BMSK                                             0x3e000
#define HWIO_CALIBRATION13_CPR2_TARG_VOLT_OFFSET_LSVSD3_SHFT                                                  13
#define HWIO_CALIBRATION13_CPR2_TARG_VOLT_OFFSET_LSVSD2_BMSK                                              0x1f00
#define HWIO_CALIBRATION13_CPR2_TARG_VOLT_OFFSET_LSVSD2_SHFT                                                   8
#define HWIO_CALIBRATION13_CPR2_TARG_VOLT_OFFSET_LSVSD1_BMSK                                                0xf8
#define HWIO_CALIBRATION13_CPR2_TARG_VOLT_OFFSET_LSVSD1_SHFT                                                   3
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_OFFSET_SVS1_4_2_BMSK                                               0x7
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_OFFSET_SVS1_4_2_SHFT                                                 0

#define HWIO_CALIBRATION14_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb50)
#define HWIO_CALIBRATION14_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb50)
#define HWIO_CALIBRATION14_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION14_IN                    \
                in_dword(HWIO_CALIBRATION14_ADDR)
#define HWIO_CALIBRATION14_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION14_ADDR, m)
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_TUR_2_0_BMSK                                         0xe0000000
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_TUR_2_0_SHFT                                                 29
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_SUT_BMSK                                             0x1f000000
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_SUT_SHFT                                                     24
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_SVS2_BMSK                                                     0xfc0000
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_SVS2_SHFT                                                           18
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_SVS_BMSK                                                       0x3f000
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_SVS_SHFT                                                            12
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_NOM_BMSK                                                         0xfc0
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_NOM_SHFT                                                             6
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_SUT_BMSK                                                          0x3f
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_SUT_SHFT                                                             0

#define HWIO_CALIBRATION15_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb54)
#define HWIO_CALIBRATION15_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb54)
#define HWIO_CALIBRATION15_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION15_IN                    \
                in_dword(HWIO_CALIBRATION15_ADDR)
#define HWIO_CALIBRATION15_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION15_ADDR, m)
#define HWIO_CALIBRATION15_CPR0_AGING_4_0_BMSK                                                        0xf8000000
#define HWIO_CALIBRATION15_CPR0_AGING_4_0_SHFT                                                                27
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_SVS2_BMSK                                             0x7c00000
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_SVS2_SHFT                                                    22
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_SVS_BMSK                                               0x3e0000
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_SVS_SHFT                                                     17
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_SVSL1_BMSK                                              0x1f000
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_SVSL1_SHFT                                                   12
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_NOM_BMSK                                                  0xf80
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_NOM_SHFT                                                      7
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_NOML1_BMSK                                                 0x7c
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_NOML1_SHFT                                                    2
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_TUR_4_3_BMSK                                                0x3
#define HWIO_CALIBRATION15_CPR0_TARG_VOLT_OFFSET_TUR_4_3_SHFT                                                  0

#define HWIO_CALIBRATION16_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb58)
#define HWIO_CALIBRATION16_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb58)
#define HWIO_CALIBRATION16_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION16_IN                    \
                in_dword(HWIO_CALIBRATION16_ADDR)
#define HWIO_CALIBRATION16_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION16_ADDR, m)
#define HWIO_CALIBRATION16_CALIBRATION_543_539_BMSK                                                   0xf8000000
#define HWIO_CALIBRATION16_CALIBRATION_543_539_SHFT                                                           27
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_SVS3_BMSK                                                    0x7e00000
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_SVS3_SHFT                                                           21
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_SVS_BMSK                                                      0x1f8000
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_SVS_SHFT                                                            15
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_NOM_BMSK                                                        0x7e00
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_NOM_SHFT                                                             9
#define HWIO_CALIBRATION16_CALIBRATION_520_515_BMSK                                                        0x1f8
#define HWIO_CALIBRATION16_CALIBRATION_520_515_SHFT                                                            3
#define HWIO_CALIBRATION16_CPR0_AGING_7_5_BMSK                                                               0x7
#define HWIO_CALIBRATION16_CPR0_AGING_7_5_SHFT                                                                 0

#define HWIO_CALIBRATION17_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb5c)
#define HWIO_CALIBRATION17_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb5c)
#define HWIO_CALIBRATION17_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION17_IN                    \
                in_dword(HWIO_CALIBRATION17_ADDR)
#define HWIO_CALIBRATION17_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION17_ADDR, m)
#define HWIO_CALIBRATION17_CPR1_AGING_1_0_BMSK                                                        0xc0000000
#define HWIO_CALIBRATION17_CPR1_AGING_1_0_SHFT                                                                30
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_SVS3_BMSK                                            0x3e000000
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_SVS3_SHFT                                                    25
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_SVS2_BMSK                                             0x1f00000
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_SVS2_SHFT                                                    20
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_SVS_BMSK                                                0xf8000
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_SVS_SHFT                                                     15
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_SVSL1_BMSK                                               0x7c00
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_SVSL1_SHFT                                                   10
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                                  0x3e0
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                                      5
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_NOML1_BMSK                                                 0x1f
#define HWIO_CALIBRATION17_CPR1_TARG_VOLT_OFFSET_NOML1_SHFT                                                    0

#define HWIO_CALIBRATION18_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb60)
#define HWIO_CALIBRATION18_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb60)
#define HWIO_CALIBRATION18_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION18_IN                    \
                in_dword(HWIO_CALIBRATION18_ADDR)
#define HWIO_CALIBRATION18_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION18_ADDR, m)
#define HWIO_CALIBRATION18_CPR2_TARG_VOLT_SVS3_1_0_BMSK                                               0xc0000000
#define HWIO_CALIBRATION18_CPR2_TARG_VOLT_SVS3_1_0_SHFT                                                       30
#define HWIO_CALIBRATION18_CPR2_TARG_VOLT_SVSL1_BMSK                                                  0x3f000000
#define HWIO_CALIBRATION18_CPR2_TARG_VOLT_SVSL1_SHFT                                                          24
#define HWIO_CALIBRATION18_CPR2_TARG_VOLT_NOM_BMSK                                                      0xfc0000
#define HWIO_CALIBRATION18_CPR2_TARG_VOLT_NOM_SHFT                                                            18
#define HWIO_CALIBRATION18_CPR2_TARG_VOLT_NOML1_BMSK                                                     0x3f000
#define HWIO_CALIBRATION18_CPR2_TARG_VOLT_NOML1_SHFT                                                          12
#define HWIO_CALIBRATION18_CPR2_TARG_VOLT_SUT_BMSK                                                         0xfc0
#define HWIO_CALIBRATION18_CPR2_TARG_VOLT_SUT_SHFT                                                             6
#define HWIO_CALIBRATION18_CPR1_AGING_7_2_BMSK                                                              0x3f
#define HWIO_CALIBRATION18_CPR1_AGING_7_2_SHFT                                                                 0

#define HWIO_CALIBRATION19_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb64)
#define HWIO_CALIBRATION19_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb64)
#define HWIO_CALIBRATION19_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION19_IN                    \
                in_dword(HWIO_CALIBRATION19_ADDR)
#define HWIO_CALIBRATION19_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION19_ADDR, m)
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_SVSL1_2_0_BMSK                                       0xe0000000
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_SVSL1_2_0_SHFT                                               29
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_SVSL2_BMSK                                           0x1f000000
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_SVSL2_SHFT                                                   24
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                                               0xf80000
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                                     19
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_NOML1_BMSK                                              0x7c000
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_NOML1_SHFT                                                   14
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_TUR_BMSK                                                 0x3e00
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_TUR_SHFT                                                      9
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_SUT_BMSK                                                  0x1f0
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_SUT_SHFT                                                      4
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_SVS3_5_2_BMSK                                                      0xf
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_SVS3_5_2_SHFT                                                        0

#define HWIO_CALIBRATION20_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb68)
#define HWIO_CALIBRATION20_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb68)
#define HWIO_CALIBRATION20_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION20_IN                    \
                in_dword(HWIO_CALIBRATION20_ADDR)
#define HWIO_CALIBRATION20_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION20_ADDR, m)
#define HWIO_CALIBRATION20_CPR3_TARG_VOLT_SVS_0_BMSK                                                  0x80000000
#define HWIO_CALIBRATION20_CPR3_TARG_VOLT_SVS_0_SHFT                                                          31
#define HWIO_CALIBRATION20_CALIBRATION_670_665_BMSK                                                   0x7e000000
#define HWIO_CALIBRATION20_CALIBRATION_670_665_SHFT                                                           25
#define HWIO_CALIBRATION20_CPR2_AGING_BMSK                                                             0x1fe0000
#define HWIO_CALIBRATION20_CPR2_AGING_SHFT                                                                    17
#define HWIO_CALIBRATION20_CALIBRATION_656_647_BMSK                                                      0x1ff80
#define HWIO_CALIBRATION20_CALIBRATION_656_647_SHFT                                                            7
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVS_BMSK                                                   0x7c
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVS_SHFT                                                      2
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVSL1_4_3_BMSK                                              0x3
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVSL1_4_3_SHFT                                                0

#define HWIO_CALIBRATION21_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb6c)
#define HWIO_CALIBRATION21_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb6c)
#define HWIO_CALIBRATION21_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION21_IN                    \
                in_dword(HWIO_CALIBRATION21_ADDR)
#define HWIO_CALIBRATION21_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION21_ADDR, m)
#define HWIO_CALIBRATION21_CALIBRATION_703_701_BMSK                                                   0xe0000000
#define HWIO_CALIBRATION21_CALIBRATION_703_701_SHFT                                                           29
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_NOM_BMSK                                                    0x1f800000
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_NOM_SHFT                                                            23
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_SVS_BMSK                                                      0x7e0000
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_SVS_SHFT                                                            17
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_SUT_BMSK                                                       0x1f800
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_SUT_SHFT                                                            11
#define HWIO_CALIBRATION21_CALIBRATION_682_677_BMSK                                                        0x7e0
#define HWIO_CALIBRATION21_CALIBRATION_682_677_SHFT                                                            5
#define HWIO_CALIBRATION21_CPR3_TARG_VOLT_SVS_5_1_BMSK                                                      0x1f
#define HWIO_CALIBRATION21_CPR3_TARG_VOLT_SVS_5_1_SHFT                                                         0

#define HWIO_CALIBRATION22_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb70)
#define HWIO_CALIBRATION22_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb70)
#define HWIO_CALIBRATION22_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION22_IN                    \
                in_dword(HWIO_CALIBRATION22_ADDR)
#define HWIO_CALIBRATION22_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION22_ADDR, m)
#define HWIO_CALIBRATION22_CALIBRATION_735_733_BMSK                                                   0xe0000000
#define HWIO_CALIBRATION22_CALIBRATION_735_733_SHFT                                                           29
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_SUT_BMSK                                                    0x1f800000
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_SUT_SHFT                                                            23
#define HWIO_CALIBRATION22_CPR4_TARG_VOLT_OFFSET_SVSL1_BMSK                                             0x7c0000
#define HWIO_CALIBRATION22_CPR4_TARG_VOLT_OFFSET_SVSL1_SHFT                                                   18
#define HWIO_CALIBRATION22_CPR4_TARG_VOLT_OFFSET_NOM_BMSK                                                0x3e000
#define HWIO_CALIBRATION22_CPR4_TARG_VOLT_OFFSET_NOM_SHFT                                                     13
#define HWIO_CALIBRATION22_CPR4_TARG_VOLT_OFFSET_NOML1_BMSK                                               0x1f00
#define HWIO_CALIBRATION22_CPR4_TARG_VOLT_OFFSET_NOML1_SHFT                                                    8
#define HWIO_CALIBRATION22_CPR4_TARG_VOLT_OFFSET_SUT_BMSK                                                   0xf8
#define HWIO_CALIBRATION22_CPR4_TARG_VOLT_OFFSET_SUT_SHFT                                                      3
#define HWIO_CALIBRATION22_CALIBRATION_706_704_BMSK                                                          0x7
#define HWIO_CALIBRATION22_CALIBRATION_706_704_SHFT                                                            0

#define HWIO_CALIBRATION23_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb74)
#define HWIO_CALIBRATION23_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb74)
#define HWIO_CALIBRATION23_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION23_IN                    \
                in_dword(HWIO_CALIBRATION23_ADDR)
#define HWIO_CALIBRATION23_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION23_ADDR, m)
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_SVSL1_1_0_BMSK                                       0xc0000000
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_SVSL1_1_0_SHFT                                               30
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_NOM_BMSK                                             0x3e000000
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_NOM_SHFT                                                     25
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_NOML1_BMSK                                            0x1f00000
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_NOML1_SHFT                                                   20
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_SUT_BMSK                                                0xf8000
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_SUT_SHFT                                                     15
#define HWIO_CALIBRATION23_CALIBRATION_750_745_BMSK                                                       0x7e00
#define HWIO_CALIBRATION23_CALIBRATION_750_745_SHFT                                                            9
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_NOM_BMSK                                                         0x1f8
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_NOM_SHFT                                                             3
#define HWIO_CALIBRATION23_CALIBRATION_738_736_BMSK                                                          0x7
#define HWIO_CALIBRATION23_CALIBRATION_738_736_SHFT                                                            0

#define HWIO_CALIBRATION24_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb78)
#define HWIO_CALIBRATION24_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb78)
#define HWIO_CALIBRATION24_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION24_IN                    \
                in_dword(HWIO_CALIBRATION24_ADDR)
#define HWIO_CALIBRATION24_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION24_ADDR, m)
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_TUR_4_0_BMSK                                                0xf8000000
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_TUR_4_0_SHFT                                                        27
#define HWIO_CALIBRATION24_CALIBRATION_794_789_BMSK                                                    0x7e00000
#define HWIO_CALIBRATION24_CALIBRATION_794_789_SHFT                                                           21
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_NOM_BMSK                                                      0x1f8000
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_NOM_SHFT                                                            15
#define HWIO_CALIBRATION24_CALIBRATION_782_777_BMSK                                                       0x7e00
#define HWIO_CALIBRATION24_CALIBRATION_782_777_SHFT                                                            9
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_TUR_BMSK                                                         0x1f8
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_TUR_SHFT                                                             3
#define HWIO_CALIBRATION24_CPR5_TARG_VOLT_OFFSET_SVSL1_4_2_BMSK                                              0x7
#define HWIO_CALIBRATION24_CPR5_TARG_VOLT_OFFSET_SVSL1_4_2_SHFT                                                0

#define HWIO_CALIBRATION25_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb7c)
#define HWIO_CALIBRATION25_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb7c)
#define HWIO_CALIBRATION25_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION25_IN                    \
                in_dword(HWIO_CALIBRATION25_ADDR)
#define HWIO_CALIBRATION25_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION25_ADDR, m)
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_OFFSET_NOM_2_0_BMSK                                         0xe0000000
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_OFFSET_NOM_2_0_SHFT                                                 29
#define HWIO_CALIBRATION25_CALIBRATION_828_824_BMSK                                                   0x1f000000
#define HWIO_CALIBRATION25_CALIBRATION_828_824_SHFT                                                           24
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_OFFSET_TUR_BMSK                                               0xf80000
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_OFFSET_TUR_SHFT                                                     19
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_SVS3_BMSK                                                      0x7e000
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_SVS3_SHFT                                                           13
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_SVS_BMSK                                                        0x1f80
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_SVS_SHFT                                                             7
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_NOM_BMSK                                                          0x7e
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_NOM_SHFT                                                             1
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_TUR_5_BMSK                                                         0x1
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_TUR_5_SHFT                                                           0

#define HWIO_CALIBRATION26_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb80)
#define HWIO_CALIBRATION26_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb80)
#define HWIO_CALIBRATION26_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION26_IN                    \
                in_dword(HWIO_CALIBRATION26_ADDR)
#define HWIO_CALIBRATION26_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION26_ADDR, m)
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_TUR_1_0_BMSK                                                0xc0000000
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_TUR_1_0_SHFT                                                        30
#define HWIO_CALIBRATION26_CPR7_AGING_BMSK                                                            0x3fc00000
#define HWIO_CALIBRATION26_CPR7_AGING_SHFT                                                                    22
#define HWIO_CALIBRATION26_CPR7_TARG_VOLT_OFFSET_SVS3_BMSK                                              0x3e0000
#define HWIO_CALIBRATION26_CPR7_TARG_VOLT_OFFSET_SVS3_SHFT                                                    17
#define HWIO_CALIBRATION26_CPR7_TARG_VOLT_OFFSET_SVS2_BMSK                                               0x1f000
#define HWIO_CALIBRATION26_CPR7_TARG_VOLT_OFFSET_SVS2_SHFT                                                    12
#define HWIO_CALIBRATION26_CPR7_TARG_VOLT_OFFSET_SVS_BMSK                                                  0xf80
#define HWIO_CALIBRATION26_CPR7_TARG_VOLT_OFFSET_SVS_SHFT                                                      7
#define HWIO_CALIBRATION26_CPR7_TARG_VOLT_OFFSET_SVSL1_BMSK                                                 0x7c
#define HWIO_CALIBRATION26_CPR7_TARG_VOLT_OFFSET_SVSL1_SHFT                                                    2
#define HWIO_CALIBRATION26_CPR7_TARG_VOLT_OFFSET_NOM_4_3_BMSK                                                0x3
#define HWIO_CALIBRATION26_CPR7_TARG_VOLT_OFFSET_NOM_4_3_SHFT                                                  0

#define HWIO_CALIBRATION27_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb84)
#define HWIO_CALIBRATION27_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb84)
#define HWIO_CALIBRATION27_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION27_IN                    \
                in_dword(HWIO_CALIBRATION27_ADDR)
#define HWIO_CALIBRATION27_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION27_ADDR, m)
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_NOM_BMSK                                             0xf8000000
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_NOM_SHFT                                                     27
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_TUR_BMSK                                              0x7c00000
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_TUR_SHFT                                                     22
#define HWIO_CALIBRATION27_CALIBRATION_885_880_BMSK                                                     0x3f0000
#define HWIO_CALIBRATION27_CALIBRATION_885_880_SHFT                                                           16
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_SVS_BMSK                                                        0xfc00
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_SVS_SHFT                                                            10
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_NOM_BMSK                                                         0x3f0
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_NOM_SHFT                                                             4
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_TUR_5_2_BMSK                                                       0xf
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_TUR_5_2_SHFT                                                         0

#define HWIO_CALIBRATION28_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb88)
#define HWIO_CALIBRATION28_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb88)
#define HWIO_CALIBRATION28_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION28_IN                    \
                in_dword(HWIO_CALIBRATION28_ADDR)
#define HWIO_CALIBRATION28_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION28_ADDR, m)
#define HWIO_CALIBRATION28_CALIBRATION_927_924_BMSK                                                   0xf0000000
#define HWIO_CALIBRATION28_CALIBRATION_927_924_SHFT                                                           28
#define HWIO_CALIBRATION28_CPR8_AGING_BMSK                                                             0xff00000
#define HWIO_CALIBRATION28_CPR8_AGING_SHFT                                                                    20
#define HWIO_CALIBRATION28_CALIBATION_BMSK                                                               0xf8000
#define HWIO_CALIBRATION28_CALIBATION_SHFT                                                                    15
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVS2_BMSK                                                0x7c00
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVS2_SHFT                                                    10
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVS_BMSK                                                  0x3e0
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVS_SHFT                                                      5
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVSL1_BMSK                                                 0x1f
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVSL1_SHFT                                                    0

#define HWIO_CALIBRATION29_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb8c)
#define HWIO_CALIBRATION29_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb8c)
#define HWIO_CALIBRATION29_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION29_IN                    \
                in_dword(HWIO_CALIBRATION29_ADDR)
#define HWIO_CALIBRATION29_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION29_ADDR, m)
#define HWIO_CALIBRATION29_CALIBRATION_959_942_BMSK                                                   0xffffc000
#define HWIO_CALIBRATION29_CALIBRATION_959_942_SHFT                                                           14
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_SVS_BMSK                                                        0x3f00
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_SVS_SHFT                                                             8
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_NOM_BMSK                                                          0xfc
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_NOM_SHFT                                                             2
#define HWIO_CALIBRATION29_CALIBRATION_929_928_BMSK                                                          0x3
#define HWIO_CALIBRATION29_CALIBRATION_929_928_SHFT                                                            0

#define HWIO_CALIBRATION30_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb90)
#define HWIO_CALIBRATION30_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb90)
#define HWIO_CALIBRATION30_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION30_IN                    \
                in_dword(HWIO_CALIBRATION30_ADDR)
#define HWIO_CALIBRATION30_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION30_ADDR, m)
#define HWIO_CALIBRATION30_CALIBRATION_991_960_BMSK                                                   0xffffffff
#define HWIO_CALIBRATION30_CALIBRATION_991_960_SHFT                                                            0

#define HWIO_CALIBRATION31_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb94)
#define HWIO_CALIBRATION31_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb94)
#define HWIO_CALIBRATION31_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION31_IN                    \
                in_dword(HWIO_CALIBRATION31_ADDR)
#define HWIO_CALIBRATION31_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION31_ADDR, m)
#define HWIO_CALIBRATION31_CPR10_TARG_VOLT_NOM_BMSK                                                   0xfc000000
#define HWIO_CALIBRATION31_CPR10_TARG_VOLT_NOM_SHFT                                                           26
#define HWIO_CALIBRATION31_CPR10_TARG_VOLT_TUR_BMSK                                                    0x3f00000
#define HWIO_CALIBRATION31_CPR10_TARG_VOLT_TUR_SHFT                                                           20
#define HWIO_CALIBRATION31_CPR9_AGING_BMSK                                                               0xff000
#define HWIO_CALIBRATION31_CPR9_AGING_SHFT                                                                    12
#define HWIO_CALIBRATION31_CALIBRATION_1003_992_BMSK                                                       0xfff
#define HWIO_CALIBRATION31_CALIBRATION_1003_992_SHFT                                                           0

#define HWIO_CALIBRATION32_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb98)
#define HWIO_CALIBRATION32_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb98)
#define HWIO_CALIBRATION32_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION32_IN                    \
                in_dword(HWIO_CALIBRATION32_ADDR)
#define HWIO_CALIBRATION32_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION32_ADDR, m)
#define HWIO_CALIBRATION32_CPR10_NOMINAL_QUOT_MIN_7_0_BMSK                                            0xff000000
#define HWIO_CALIBRATION32_CPR10_NOMINAL_QUOT_MIN_7_0_SHFT                                                    24
#define HWIO_CALIBRATION32_CPR10_TURBO_QUOT_MIN_BMSK                                                    0xfff000
#define HWIO_CALIBRATION32_CPR10_TURBO_QUOT_MIN_SHFT                                                          12
#define HWIO_CALIBRATION32_CPR10_TARG_VOLT_SVS2_BMSK                                                       0xfc0
#define HWIO_CALIBRATION32_CPR10_TARG_VOLT_SVS2_SHFT                                                           6
#define HWIO_CALIBRATION32_CPR10_TARG_VOLT_SVS_BMSK                                                         0x3f
#define HWIO_CALIBRATION32_CPR10_TARG_VOLT_SVS_SHFT                                                            0

#define HWIO_CALIBRATION33_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xb9c)
#define HWIO_CALIBRATION33_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xb9c)
#define HWIO_CALIBRATION33_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION33_IN                    \
                in_dword(HWIO_CALIBRATION33_ADDR)
#define HWIO_CALIBRATION33_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION33_ADDR, m)
#define HWIO_CALIBRATION33_CPR10_QUOT_OFFSET_3_0_BMSK                                                 0xf0000000
#define HWIO_CALIBRATION33_CPR10_QUOT_OFFSET_3_0_SHFT                                                         28
#define HWIO_CALIBRATION33_CPR10_SVS2_QUOT_MIN_BMSK                                                    0xfff0000
#define HWIO_CALIBRATION33_CPR10_SVS2_QUOT_MIN_SHFT                                                           16
#define HWIO_CALIBRATION33_CPR10_SVS_QUOT_MIN_BMSK                                                        0xfff0
#define HWIO_CALIBRATION33_CPR10_SVS_QUOT_MIN_SHFT                                                             4
#define HWIO_CALIBRATION33_CPR10_NOMINAL_QUOT_MIN_11_8_BMSK                                                  0xf
#define HWIO_CALIBRATION33_CPR10_NOMINAL_QUOT_MIN_11_8_SHFT                                                    0

#define HWIO_CALIBRATION34_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xba0)
#define HWIO_CALIBRATION34_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xba0)
#define HWIO_CALIBRATION34_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION34_IN                    \
                in_dword(HWIO_CALIBRATION34_ADDR)
#define HWIO_CALIBRATION34_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION34_ADDR, m)
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_SVS2_3_0_BMSK                                              0xf0000000
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_SVS2_3_0_SHFT                                                      28
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_SVS_BMSK                                                    0xfc00000
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_SVS_SHFT                                                           22
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_NOM_BMSK                                                     0x3f0000
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_NOM_SHFT                                                           16
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_TUR_BMSK                                                       0xfc00
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_TUR_SHFT                                                           10
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_BOOST_BMSK                                                      0x3f0
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_BOOST_SHFT                                                          4
#define HWIO_CALIBRATION34_CPR10_QUOT_OFFSET_7_4_BMSK                                                        0xf
#define HWIO_CALIBRATION34_CPR10_QUOT_OFFSET_7_4_SHFT                                                          0

#define HWIO_CALIBRATION35_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xba4)
#define HWIO_CALIBRATION35_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xba4)
#define HWIO_CALIBRATION35_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION35_IN                    \
                in_dword(HWIO_CALIBRATION35_ADDR)
#define HWIO_CALIBRATION35_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION35_ADDR, m)
#define HWIO_CALIBRATION35_CPR11_NOMINAL_QUOT_MIN_5_0_BMSK                                            0xfc000000
#define HWIO_CALIBRATION35_CPR11_NOMINAL_QUOT_MIN_5_0_SHFT                                                    26
#define HWIO_CALIBRATION35_CPR11_TURBO_QUOT_MIN_BMSK                                                   0x3ffc000
#define HWIO_CALIBRATION35_CPR11_TURBO_QUOT_MIN_SHFT                                                          14
#define HWIO_CALIBRATION35_CPR11_BOOST_QUOT_MIN_BMSK                                                      0x3ffc
#define HWIO_CALIBRATION35_CPR11_BOOST_QUOT_MIN_SHFT                                                           2
#define HWIO_CALIBRATION35_CPR11_TARG_VOLT_SVS2_5_4_BMSK                                                     0x3
#define HWIO_CALIBRATION35_CPR11_TARG_VOLT_SVS2_5_4_SHFT                                                       0

#define HWIO_CALIBRATION36_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xba8)
#define HWIO_CALIBRATION36_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xba8)
#define HWIO_CALIBRATION36_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION36_IN                    \
                in_dword(HWIO_CALIBRATION36_ADDR)
#define HWIO_CALIBRATION36_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION36_ADDR, m)
#define HWIO_CALIBRATION36_CPR11_QUOT_OFFSET_1_0_BMSK                                                 0xc0000000
#define HWIO_CALIBRATION36_CPR11_QUOT_OFFSET_1_0_SHFT                                                         30
#define HWIO_CALIBRATION36_CPR11_SVS2_QUOT_MIN_BMSK                                                   0x3ffc0000
#define HWIO_CALIBRATION36_CPR11_SVS2_QUOT_MIN_SHFT                                                           18
#define HWIO_CALIBRATION36_CPR11_SVS_QUOT_MIN_BMSK                                                       0x3ffc0
#define HWIO_CALIBRATION36_CPR11_SVS_QUOT_MIN_SHFT                                                             6
#define HWIO_CALIBRATION36_CPR11_NOMINAL_QUOT_MIN_11_6_BMSK                                                 0x3f
#define HWIO_CALIBRATION36_CPR11_NOMINAL_QUOT_MIN_11_6_SHFT                                                    0

#define HWIO_CALIBRATION37_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbac)
#define HWIO_CALIBRATION37_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbac)
#define HWIO_CALIBRATION37_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION37_IN                    \
                in_dword(HWIO_CALIBRATION37_ADDR)
#define HWIO_CALIBRATION37_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION37_ADDR, m)
#define HWIO_CALIBRATION37_CPR12_TARG_VOLT_NOM_BMSK                                                   0xfc000000
#define HWIO_CALIBRATION37_CPR12_TARG_VOLT_NOM_SHFT                                                           26
#define HWIO_CALIBRATION37_CPR12_TARG_VOLT_TUR_BMSK                                                    0x3f00000
#define HWIO_CALIBRATION37_CPR12_TARG_VOLT_TUR_SHFT                                                           20
#define HWIO_CALIBRATION37_CPR12_TARG_VOLT_BOOST_BMSK                                                    0xfc000
#define HWIO_CALIBRATION37_CPR12_TARG_VOLT_BOOST_SHFT                                                         14
#define HWIO_CALIBRATION37_CALIBRATION_1197_1190_BMSK                                                     0x3fc0
#define HWIO_CALIBRATION37_CALIBRATION_1197_1190_SHFT                                                          6
#define HWIO_CALIBRATION37_CPR11_QUOT_OFFSET_7_2_BMSK                                                       0x3f
#define HWIO_CALIBRATION37_CPR11_QUOT_OFFSET_7_2_SHFT                                                          0

#define HWIO_CALIBRATION38_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbb0)
#define HWIO_CALIBRATION38_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbb0)
#define HWIO_CALIBRATION38_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION38_IN                    \
                in_dword(HWIO_CALIBRATION38_ADDR)
#define HWIO_CALIBRATION38_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION38_ADDR, m)
#define HWIO_CALIBRATION38_CPR12_TURBO_QUOT_MIN_7_0_BMSK                                              0xff000000
#define HWIO_CALIBRATION38_CPR12_TURBO_QUOT_MIN_7_0_SHFT                                                      24
#define HWIO_CALIBRATION38_CPR12_BOOST_QUOT_MIN_BMSK                                                    0xfff000
#define HWIO_CALIBRATION38_CPR12_BOOST_QUOT_MIN_SHFT                                                          12
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_SVS2_BMSK                                                       0xfc0
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_SVS2_SHFT                                                           6
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_SVS_BMSK                                                         0x3f
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_SVS_SHFT                                                            0

#define HWIO_CALIBRATION39_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbb4)
#define HWIO_CALIBRATION39_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbb4)
#define HWIO_CALIBRATION39_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION39_IN                    \
                in_dword(HWIO_CALIBRATION39_ADDR)
#define HWIO_CALIBRATION39_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION39_ADDR, m)
#define HWIO_CALIBRATION39_CPR12_SVS2_QUOT_MIN_3_0_BMSK                                               0xf0000000
#define HWIO_CALIBRATION39_CPR12_SVS2_QUOT_MIN_3_0_SHFT                                                       28
#define HWIO_CALIBRATION39_CPR12_SVS_QUOT_MIN_BMSK                                                     0xfff0000
#define HWIO_CALIBRATION39_CPR12_SVS_QUOT_MIN_SHFT                                                            16
#define HWIO_CALIBRATION39_CPR12_NOMINAL_QUOT_MIN_BMSK                                                    0xfff0
#define HWIO_CALIBRATION39_CPR12_NOMINAL_QUOT_MIN_SHFT                                                         4
#define HWIO_CALIBRATION39_CPR12_TURBO_QUOT_MIN_11_8_BMSK                                                    0xf
#define HWIO_CALIBRATION39_CPR12_TURBO_QUOT_MIN_11_8_SHFT                                                      0

#define HWIO_CALIBRATION40_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbb8)
#define HWIO_CALIBRATION40_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbb8)
#define HWIO_CALIBRATION40_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION40_IN                    \
                in_dword(HWIO_CALIBRATION40_ADDR)
#define HWIO_CALIBRATION40_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION40_ADDR, m)
#define HWIO_CALIBRATION40_CPR_MXC_MODE_DISABLE_0_BMSK                                                0x80000000
#define HWIO_CALIBRATION40_CPR_MXC_MODE_DISABLE_0_SHFT                                                        31
#define HWIO_CALIBRATION40_CPR_MX_MODE_DISABLE_BMSK                                                   0x70000000
#define HWIO_CALIBRATION40_CPR_MX_MODE_DISABLE_SHFT                                                           28
#define HWIO_CALIBRATION40_CPR_GFX_MODE_DISABLE_BMSK                                                   0xe000000
#define HWIO_CALIBRATION40_CPR_GFX_MODE_DISABLE_SHFT                                                          25
#define HWIO_CALIBRATION40_CPR_MSS_MODE_DISABLE_BMSK                                                   0x1c00000
#define HWIO_CALIBRATION40_CPR_MSS_MODE_DISABLE_SHFT                                                          22
#define HWIO_CALIBRATION40_CPR_CX_MODE_DISABLE_BMSK                                                     0x380000
#define HWIO_CALIBRATION40_CPR_CX_MODE_DISABLE_SHFT                                                           19
#define HWIO_CALIBRATION40_CPR_LOCAL_RC_2_0_BMSK                                                         0x70000
#define HWIO_CALIBRATION40_CPR_LOCAL_RC_2_0_SHFT                                                              16
#define HWIO_CALIBRATION40_CPR12_QUOT_OFFSET_BMSK                                                         0xff00
#define HWIO_CALIBRATION40_CPR12_QUOT_OFFSET_SHFT                                                              8
#define HWIO_CALIBRATION40_CPR12_SVS2_QUOT_MIN_11_4_BMSK                                                    0xff
#define HWIO_CALIBRATION40_CPR12_SVS2_QUOT_MIN_11_4_SHFT                                                       0

#define HWIO_CALIBRATION41_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbbc)
#define HWIO_CALIBRATION41_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbbc)
#define HWIO_CALIBRATION41_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION41_IN                    \
                in_dword(HWIO_CALIBRATION41_ADDR)
#define HWIO_CALIBRATION41_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION41_ADDR, m)
#define HWIO_CALIBRATION41_CPR_GLOBAL_RC_0_BMSK                                                       0x80000000
#define HWIO_CALIBRATION41_CPR_GLOBAL_RC_0_SHFT                                                               31
#define HWIO_CALIBRATION41_AON_AGING_BMSK                                                             0x7f800000
#define HWIO_CALIBRATION41_AON_AGING_SHFT                                                                     23
#define HWIO_CALIBRATION41_AON_TARG_VOLT_BMSK                                                           0x7e0000
#define HWIO_CALIBRATION41_AON_TARG_VOLT_SHFT                                                                 17
#define HWIO_CALIBRATION41_CPR_APC1_MODE_DISABLE_BMSK                                                    0x1c000
#define HWIO_CALIBRATION41_CPR_APC1_MODE_DISABLE_SHFT                                                         14
#define HWIO_CALIBRATION41_CPR_APC0_MODE_DISABLE_BMSK                                                     0x3800
#define HWIO_CALIBRATION41_CPR_APC0_MODE_DISABLE_SHFT                                                         11
#define HWIO_CALIBRATION41_CPR_MMCX_MODE_DISABLE_BMSK                                                      0x700
#define HWIO_CALIBRATION41_CPR_MMCX_MODE_DISABLE_SHFT                                                          8
#define HWIO_CALIBRATION41_CPR_SSCCX_MODE_DISABLE_BMSK                                                      0xe0
#define HWIO_CALIBRATION41_CPR_SSCCX_MODE_DISABLE_SHFT                                                         5
#define HWIO_CALIBRATION41_CPR_LPIMX_MODE_DISABLE_BMSK                                                      0x1c
#define HWIO_CALIBRATION41_CPR_LPIMX_MODE_DISABLE_SHFT                                                         2
#define HWIO_CALIBRATION41_CPR_MXC_MODE_DISABLE_2_1_BMSK                                                     0x3
#define HWIO_CALIBRATION41_CPR_MXC_MODE_DISABLE_2_1_SHFT                                                       0

#define HWIO_CALIBRATION42_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbc0)
#define HWIO_CALIBRATION42_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbc0)
#define HWIO_CALIBRATION42_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION42_IN                    \
                in_dword(HWIO_CALIBRATION42_ADDR)
#define HWIO_CALIBRATION42_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION42_ADDR, m)
#define HWIO_CALIBRATION42_CPR12_BOOSTP_QUOT_MIN_5_0_BMSK                                             0xfc000000
#define HWIO_CALIBRATION42_CPR12_BOOSTP_QUOT_MIN_5_0_SHFT                                                     26
#define HWIO_CALIBRATION42_CPR12_TARG_VOLT_BOOSTP_BMSK                                                 0x3f00000
#define HWIO_CALIBRATION42_CPR12_TARG_VOLT_BOOSTP_SHFT                                                        20
#define HWIO_CALIBRATION42_CALIBRATION_1363_1346_BMSK                                                    0xffffc
#define HWIO_CALIBRATION42_CALIBRATION_1363_1346_SHFT                                                          2
#define HWIO_CALIBRATION42_CPR_GLOBAL_RC_2_1_BMSK                                                            0x3
#define HWIO_CALIBRATION42_CPR_GLOBAL_RC_2_1_SHFT                                                              0

#define HWIO_CALIBRATION43_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbc4)
#define HWIO_CALIBRATION43_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbc4)
#define HWIO_CALIBRATION43_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION43_IN                    \
                in_dword(HWIO_CALIBRATION43_ADDR)
#define HWIO_CALIBRATION43_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION43_ADDR, m)
#define HWIO_CALIBRATION43_CALIBRATION_1407_1403_BMSK                                                 0xf8000000
#define HWIO_CALIBRATION43_CALIBRATION_1407_1403_SHFT                                                         27
#define HWIO_CALIBRATION43_APC0_PEAK_THROTTLE_FREQ_BMSK                                                0x6000000
#define HWIO_CALIBRATION43_APC0_PEAK_THROTTLE_FREQ_SHFT                                                       25
#define HWIO_CALIBRATION43_APC0_PEAK_THROTTLE_TJ_BMSK                                                  0x1f00000
#define HWIO_CALIBRATION43_APC0_PEAK_THROTTLE_TJ_SHFT                                                         20
#define HWIO_CALIBRATION43_CPR_GLOBAL_RC_3_BMSK                                                          0x80000
#define HWIO_CALIBRATION43_CPR_GLOBAL_RC_3_SHFT                                                               19
#define HWIO_CALIBRATION43_CPR_RESERVED_12_0_BMSK                                                        0x7ffc0
#define HWIO_CALIBRATION43_CPR_RESERVED_12_0_SHFT                                                              6
#define HWIO_CALIBRATION43_CPR12_BOOSTP_QUOT_MIN_11_6_BMSK                                                  0x3f
#define HWIO_CALIBRATION43_CPR12_BOOSTP_QUOT_MIN_11_6_SHFT                                                     0

#define HWIO_CALIBRATION44_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbc8)
#define HWIO_CALIBRATION44_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbc8)
#define HWIO_CALIBRATION44_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION44_IN                    \
                in_dword(HWIO_CALIBRATION44_ADDR)
#define HWIO_CALIBRATION44_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION44_ADDR, m)
#define HWIO_CALIBRATION44_CALIBRATION_1439_1408_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION44_CALIBRATION_1439_1408_SHFT                                                          0

#define HWIO_CALIBRATION45_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbcc)
#define HWIO_CALIBRATION45_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbcc)
#define HWIO_CALIBRATION45_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION45_IN                    \
                in_dword(HWIO_CALIBRATION45_ADDR)
#define HWIO_CALIBRATION45_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION45_ADDR, m)
#define HWIO_CALIBRATION45_AOSS_K_5_0_BMSK                                                            0xfc000000
#define HWIO_CALIBRATION45_AOSS_K_5_0_SHFT                                                                    26
#define HWIO_CALIBRATION45_CALIBRATION_1465_1440_BMSK                                                  0x3ffffff
#define HWIO_CALIBRATION45_CALIBRATION_1465_1440_SHFT                                                          0

#define HWIO_CALIBRATION46_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbd0)
#define HWIO_CALIBRATION46_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbd0)
#define HWIO_CALIBRATION46_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION46_IN                    \
                in_dword(HWIO_CALIBRATION46_ADDR)
#define HWIO_CALIBRATION46_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION46_ADDR, m)
#define HWIO_CALIBRATION46_AOSS_P1_3_0_BMSK                                                           0xf0000000
#define HWIO_CALIBRATION46_AOSS_P1_3_0_SHFT                                                                   28
#define HWIO_CALIBRATION46_AOSS_N1_BMSK                                                                0xffffc00
#define HWIO_CALIBRATION46_AOSS_N1_SHFT                                                                       10
#define HWIO_CALIBRATION46_AOSS_K_15_6_BMSK                                                                0x3ff
#define HWIO_CALIBRATION46_AOSS_K_15_6_SHFT                                                                    0

#define HWIO_CALIBRATION47_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbd4)
#define HWIO_CALIBRATION47_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbd4)
#define HWIO_CALIBRATION47_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION47_IN                    \
                in_dword(HWIO_CALIBRATION47_ADDR)
#define HWIO_CALIBRATION47_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION47_ADDR, m)
#define HWIO_CALIBRATION47_CALIBRATION_1535_1532_BMSK                                                 0xf0000000
#define HWIO_CALIBRATION47_CALIBRATION_1535_1532_SHFT                                                         28
#define HWIO_CALIBRATION47_CPR4_TARG_VOLT_TUR_BMSK                                                     0xfc00000
#define HWIO_CALIBRATION47_CPR4_TARG_VOLT_TUR_SHFT                                                            22
#define HWIO_CALIBRATION47_AOSS_TDOPCODE_BMSK                                                           0x3e0000
#define HWIO_CALIBRATION47_AOSS_TDOPCODE_SHFT                                                                 17
#define HWIO_CALIBRATION47_AOSS_RDOPCODE_2_0_BMSK                                                        0x1c000
#define HWIO_CALIBRATION47_AOSS_RDOPCODE_2_0_SHFT                                                             14
#define HWIO_CALIBRATION47_AOSS_P1_17_4_BMSK                                                              0x3fff
#define HWIO_CALIBRATION47_AOSS_P1_17_4_SHFT                                                                   0

#define HWIO_CALIBRATION48_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbd8)
#define HWIO_CALIBRATION48_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbd8)
#define HWIO_CALIBRATION48_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION48_IN                    \
                in_dword(HWIO_CALIBRATION48_ADDR)
#define HWIO_CALIBRATION48_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION48_ADDR, m)
#define HWIO_CALIBRATION48_TSENS1_BASE1_1_0_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION48_TSENS1_BASE1_1_0_SHFT                                                              30
#define HWIO_CALIBRATION48_TSENS1_BASE0_BMSK                                                          0x3ff00000
#define HWIO_CALIBRATION48_TSENS1_BASE0_SHFT                                                                  20
#define HWIO_CALIBRATION48_TSENS0_BASE1_BMSK                                                             0xffc00
#define HWIO_CALIBRATION48_TSENS0_BASE1_SHFT                                                                  10
#define HWIO_CALIBRATION48_TSENS0_BASE0_BMSK                                                               0x3ff
#define HWIO_CALIBRATION48_TSENS0_BASE0_SHFT                                                                   0

#define HWIO_CALIBRATION49_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbdc)
#define HWIO_CALIBRATION49_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbdc)
#define HWIO_CALIBRATION49_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION49_IN                    \
                in_dword(HWIO_CALIBRATION49_ADDR)
#define HWIO_CALIBRATION49_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION49_ADDR, m)
#define HWIO_CALIBRATION49_TSENS4_OFFSET_3_0_BMSK                                                     0xf0000000
#define HWIO_CALIBRATION49_TSENS4_OFFSET_3_0_SHFT                                                             28
#define HWIO_CALIBRATION49_TSENS3_OFFSET_BMSK                                                          0xf800000
#define HWIO_CALIBRATION49_TSENS3_OFFSET_SHFT                                                                 23
#define HWIO_CALIBRATION49_TSENS2_OFFSET_BMSK                                                           0x7c0000
#define HWIO_CALIBRATION49_TSENS2_OFFSET_SHFT                                                                 18
#define HWIO_CALIBRATION49_TSENS1_OFFSET_BMSK                                                            0x3e000
#define HWIO_CALIBRATION49_TSENS1_OFFSET_SHFT                                                                 13
#define HWIO_CALIBRATION49_TSENS0_OFFSET_BMSK                                                             0x1f00
#define HWIO_CALIBRATION49_TSENS0_OFFSET_SHFT                                                                  8
#define HWIO_CALIBRATION49_TSENS1_BASE1_9_2_BMSK                                                            0xff
#define HWIO_CALIBRATION49_TSENS1_BASE1_9_2_SHFT                                                               0

#define HWIO_CALIBRATION50_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbe0)
#define HWIO_CALIBRATION50_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbe0)
#define HWIO_CALIBRATION50_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION50_IN                    \
                in_dword(HWIO_CALIBRATION50_ADDR)
#define HWIO_CALIBRATION50_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION50_ADDR, m)
#define HWIO_CALIBRATION50_TSENS11_OFFSET_0_BMSK                                                      0x80000000
#define HWIO_CALIBRATION50_TSENS11_OFFSET_0_SHFT                                                              31
#define HWIO_CALIBRATION50_TSENS10_OFFSET_BMSK                                                        0x7c000000
#define HWIO_CALIBRATION50_TSENS10_OFFSET_SHFT                                                                26
#define HWIO_CALIBRATION50_TSENS9_OFFSET_BMSK                                                          0x3e00000
#define HWIO_CALIBRATION50_TSENS9_OFFSET_SHFT                                                                 21
#define HWIO_CALIBRATION50_TSENS8_OFFSET_BMSK                                                           0x1f0000
#define HWIO_CALIBRATION50_TSENS8_OFFSET_SHFT                                                                 16
#define HWIO_CALIBRATION50_TSENS7_OFFSET_BMSK                                                             0xf800
#define HWIO_CALIBRATION50_TSENS7_OFFSET_SHFT                                                                 11
#define HWIO_CALIBRATION50_TSENS6_OFFSET_BMSK                                                              0x7c0
#define HWIO_CALIBRATION50_TSENS6_OFFSET_SHFT                                                                  6
#define HWIO_CALIBRATION50_TSENS5_OFFSET_BMSK                                                               0x3e
#define HWIO_CALIBRATION50_TSENS5_OFFSET_SHFT                                                                  1
#define HWIO_CALIBRATION50_TSENS4_OFFSET_4_BMSK                                                              0x1
#define HWIO_CALIBRATION50_TSENS4_OFFSET_4_SHFT                                                                0

#define HWIO_CALIBRATION51_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbe4)
#define HWIO_CALIBRATION51_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbe4)
#define HWIO_CALIBRATION51_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION51_IN                    \
                in_dword(HWIO_CALIBRATION51_ADDR)
#define HWIO_CALIBRATION51_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION51_ADDR, m)
#define HWIO_CALIBRATION51_TSENS17_OFFSET_2_0_BMSK                                                    0xe0000000
#define HWIO_CALIBRATION51_TSENS17_OFFSET_2_0_SHFT                                                            29
#define HWIO_CALIBRATION51_TSENS16_OFFSET_BMSK                                                        0x1f000000
#define HWIO_CALIBRATION51_TSENS16_OFFSET_SHFT                                                                24
#define HWIO_CALIBRATION51_TSENS15_OFFSET_BMSK                                                          0xf80000
#define HWIO_CALIBRATION51_TSENS15_OFFSET_SHFT                                                                19
#define HWIO_CALIBRATION51_TSENS14_OFFSET_BMSK                                                           0x7c000
#define HWIO_CALIBRATION51_TSENS14_OFFSET_SHFT                                                                14
#define HWIO_CALIBRATION51_TSENS13_OFFSET_BMSK                                                            0x3e00
#define HWIO_CALIBRATION51_TSENS13_OFFSET_SHFT                                                                 9
#define HWIO_CALIBRATION51_TSENS12_OFFSET_BMSK                                                             0x1f0
#define HWIO_CALIBRATION51_TSENS12_OFFSET_SHFT                                                                 4
#define HWIO_CALIBRATION51_TSENS11_OFFSET_4_1_BMSK                                                           0xf
#define HWIO_CALIBRATION51_TSENS11_OFFSET_4_1_SHFT                                                             0

#define HWIO_CALIBRATION52_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbe8)
#define HWIO_CALIBRATION52_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbe8)
#define HWIO_CALIBRATION52_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION52_IN                    \
                in_dword(HWIO_CALIBRATION52_ADDR)
#define HWIO_CALIBRATION52_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION52_ADDR, m)
#define HWIO_CALIBRATION52_TSENS23_OFFSET_BMSK                                                        0xf8000000
#define HWIO_CALIBRATION52_TSENS23_OFFSET_SHFT                                                                27
#define HWIO_CALIBRATION52_TSENS22_OFFSET_BMSK                                                         0x7c00000
#define HWIO_CALIBRATION52_TSENS22_OFFSET_SHFT                                                                22
#define HWIO_CALIBRATION52_TSENS21_OFFSET_BMSK                                                          0x3e0000
#define HWIO_CALIBRATION52_TSENS21_OFFSET_SHFT                                                                17
#define HWIO_CALIBRATION52_TSENS20_OFFSET_BMSK                                                           0x1f000
#define HWIO_CALIBRATION52_TSENS20_OFFSET_SHFT                                                                12
#define HWIO_CALIBRATION52_TSENS19_OFFSET_BMSK                                                             0xf80
#define HWIO_CALIBRATION52_TSENS19_OFFSET_SHFT                                                                 7
#define HWIO_CALIBRATION52_TSENS18_OFFSET_BMSK                                                              0x7c
#define HWIO_CALIBRATION52_TSENS18_OFFSET_SHFT                                                                 2
#define HWIO_CALIBRATION52_TSENS17_OFFSET_4_3_BMSK                                                           0x3
#define HWIO_CALIBRATION52_TSENS17_OFFSET_4_3_SHFT                                                             0

#define HWIO_CALIBRATION53_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbec)
#define HWIO_CALIBRATION53_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbec)
#define HWIO_CALIBRATION53_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION53_IN                    \
                in_dword(HWIO_CALIBRATION53_ADDR)
#define HWIO_CALIBRATION53_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION53_ADDR, m)
#define HWIO_CALIBRATION53_TSENS30_OFFSET_1_0_BMSK                                                    0xc0000000
#define HWIO_CALIBRATION53_TSENS30_OFFSET_1_0_SHFT                                                            30
#define HWIO_CALIBRATION53_TSENS29_OFFSET_BMSK                                                        0x3e000000
#define HWIO_CALIBRATION53_TSENS29_OFFSET_SHFT                                                                25
#define HWIO_CALIBRATION53_TSENS28_OFFSET_BMSK                                                         0x1f00000
#define HWIO_CALIBRATION53_TSENS28_OFFSET_SHFT                                                                20
#define HWIO_CALIBRATION53_TSENS27_OFFSET_BMSK                                                           0xf8000
#define HWIO_CALIBRATION53_TSENS27_OFFSET_SHFT                                                                15
#define HWIO_CALIBRATION53_TSENS26_OFFSET_BMSK                                                            0x7c00
#define HWIO_CALIBRATION53_TSENS26_OFFSET_SHFT                                                                10
#define HWIO_CALIBRATION53_TSENS25_OFFSET_BMSK                                                             0x3e0
#define HWIO_CALIBRATION53_TSENS25_OFFSET_SHFT                                                                 5
#define HWIO_CALIBRATION53_TSENS24_OFFSET_BMSK                                                              0x1f
#define HWIO_CALIBRATION53_TSENS24_OFFSET_SHFT                                                                 0

#define HWIO_CALIBRATION54_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbf0)
#define HWIO_CALIBRATION54_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbf0)
#define HWIO_CALIBRATION54_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION54_IN                    \
                in_dword(HWIO_CALIBRATION54_ADDR)
#define HWIO_CALIBRATION54_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION54_ADDR, m)
#define HWIO_CALIBRATION54_TSENS36_OFFSET_0_BMSK                                                      0x80000000
#define HWIO_CALIBRATION54_TSENS36_OFFSET_0_SHFT                                                              31
#define HWIO_CALIBRATION54_TSENS35_OFFSET_BMSK                                                        0x7c000000
#define HWIO_CALIBRATION54_TSENS35_OFFSET_SHFT                                                                26
#define HWIO_CALIBRATION54_TSENS34_OFFSET_BMSK                                                         0x3e00000
#define HWIO_CALIBRATION54_TSENS34_OFFSET_SHFT                                                                21
#define HWIO_CALIBRATION54_TSENS33_OFFSET_BMSK                                                          0x1f0000
#define HWIO_CALIBRATION54_TSENS33_OFFSET_SHFT                                                                16
#define HWIO_CALIBRATION54_TSENS32_OFFSET_BMSK                                                            0xf800
#define HWIO_CALIBRATION54_TSENS32_OFFSET_SHFT                                                                11
#define HWIO_CALIBRATION54_TSENS_CAL_SEL_BMSK                                                              0x700
#define HWIO_CALIBRATION54_TSENS_CAL_SEL_SHFT                                                                  8
#define HWIO_CALIBRATION54_TSENS31_OFFSET_BMSK                                                              0xf8
#define HWIO_CALIBRATION54_TSENS31_OFFSET_SHFT                                                                 3
#define HWIO_CALIBRATION54_TSENS30_OFFSET_4_2_BMSK                                                           0x7
#define HWIO_CALIBRATION54_TSENS30_OFFSET_4_2_SHFT                                                             0

#define HWIO_CALIBRATION55_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbf4)
#define HWIO_CALIBRATION55_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbf4)
#define HWIO_CALIBRATION55_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION55_IN                    \
                in_dword(HWIO_CALIBRATION55_ADDR)
#define HWIO_CALIBRATION55_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION55_ADDR, m)
#define HWIO_CALIBRATION55_CALIBRATION_1791_1790_BMSK                                                 0xc0000000
#define HWIO_CALIBRATION55_CALIBRATION_1791_1790_SHFT                                                         30
#define HWIO_CALIBRATION55_CPR4_TARG_VOLT_OFFSET_TUR_BMSK                                             0x3e000000
#define HWIO_CALIBRATION55_CPR4_TARG_VOLT_OFFSET_TUR_SHFT                                                     25
#define HWIO_CALIBRATION55_TSENS_REV_CTRL_BMSK                                                         0x1000000
#define HWIO_CALIBRATION55_TSENS_REV_CTRL_SHFT                                                                24
#define HWIO_CALIBRATION55_TSENS40_OFFSET_BMSK                                                          0xf80000
#define HWIO_CALIBRATION55_TSENS40_OFFSET_SHFT                                                                19
#define HWIO_CALIBRATION55_TSENS39_OFFSET_BMSK                                                           0x7c000
#define HWIO_CALIBRATION55_TSENS39_OFFSET_SHFT                                                                14
#define HWIO_CALIBRATION55_TSENS38_OFFSET_BMSK                                                            0x3e00
#define HWIO_CALIBRATION55_TSENS38_OFFSET_SHFT                                                                 9
#define HWIO_CALIBRATION55_TSENS37_OFFSET_BMSK                                                             0x1f0
#define HWIO_CALIBRATION55_TSENS37_OFFSET_SHFT                                                                 4
#define HWIO_CALIBRATION55_TSENS36_OFFSET_4_1_BMSK                                                           0xf
#define HWIO_CALIBRATION55_TSENS36_OFFSET_4_1_SHFT                                                             0

#define HWIO_CALIBRATION56_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbf8)
#define HWIO_CALIBRATION56_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbf8)
#define HWIO_CALIBRATION56_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION56_IN                    \
                in_dword(HWIO_CALIBRATION56_ADDR)
#define HWIO_CALIBRATION56_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION56_ADDR, m)
#define HWIO_CALIBRATION56_CALIBRATION_1823_1792_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION56_CALIBRATION_1823_1792_SHFT                                                          0

#define HWIO_CALIBRATION57_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xbfc)
#define HWIO_CALIBRATION57_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xbfc)
#define HWIO_CALIBRATION57_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION57_IN                    \
                in_dword(HWIO_CALIBRATION57_ADDR)
#define HWIO_CALIBRATION57_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION57_ADDR, m)
#define HWIO_CALIBRATION57_CALIBRATION_1855_1852_BMSK                                                 0xf0000000
#define HWIO_CALIBRATION57_CALIBRATION_1855_1852_SHFT                                                         28
#define HWIO_CALIBRATION57_CPR4_TARG_VOLT_OFFSET_SVS2_BMSK                                             0xf800000
#define HWIO_CALIBRATION57_CPR4_TARG_VOLT_OFFSET_SVS2_SHFT                                                    23
#define HWIO_CALIBRATION57_CALIBRATION_1846_1824_BMSK                                                   0x7fffff
#define HWIO_CALIBRATION57_CALIBRATION_1846_1824_SHFT                                                          0

#define HWIO_CALIBRATION58_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc00)
#define HWIO_CALIBRATION58_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc00)
#define HWIO_CALIBRATION58_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION58_IN                    \
                in_dword(HWIO_CALIBRATION58_ADDR)
#define HWIO_CALIBRATION58_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION58_ADDR, m)
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU6_FT_1_0_BMSK                                        0xc0000000
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU6_FT_1_0_SHFT                                                30
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU6_WS_BMSK                                            0x3f000000
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU6_WS_SHFT                                                    24
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU5_FT_BMSK                                              0xfc0000
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU5_FT_SHFT                                                    18
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU5_WS_BMSK                                               0x3f000
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU5_WS_SHFT                                                    12
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU4_FT_BMSK                                                 0xfc0
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU4_FT_SHFT                                                     6
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU4_WS_BMSK                                                  0x3f
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU4_WS_SHFT                                                     0

#define HWIO_CALIBRATION59_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc04)
#define HWIO_CALIBRATION59_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc04)
#define HWIO_CALIBRATION59_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION59_IN                    \
                in_dword(HWIO_CALIBRATION59_ADDR)
#define HWIO_CALIBRATION59_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION59_ADDR, m)
#define HWIO_CALIBRATION59_OPAMP_FUSE_NSPRAIL_HMX_WS_3_0_BMSK                                         0xf0000000
#define HWIO_CALIBRATION59_OPAMP_FUSE_NSPRAIL_HMX_WS_3_0_SHFT                                                 28
#define HWIO_CALIBRATION59_OPAMP_FUSE_NSPRAIL_HVX_FT_BMSK                                              0xfc00000
#define HWIO_CALIBRATION59_OPAMP_FUSE_NSPRAIL_HVX_FT_SHFT                                                     22
#define HWIO_CALIBRATION59_OPAMP_FUSE_NSPRAIL_HVX_WS_BMSK                                               0x3f0000
#define HWIO_CALIBRATION59_OPAMP_FUSE_NSPRAIL_HVX_WS_SHFT                                                     16
#define HWIO_CALIBRATION59_OPAMP_FUSE_CPURAIL_CPU7_FT_BMSK                                                0xfc00
#define HWIO_CALIBRATION59_OPAMP_FUSE_CPURAIL_CPU7_FT_SHFT                                                    10
#define HWIO_CALIBRATION59_OPAMP_FUSE_CPURAIL_CPU7_WS_BMSK                                                 0x3f0
#define HWIO_CALIBRATION59_OPAMP_FUSE_CPURAIL_CPU7_WS_SHFT                                                     4
#define HWIO_CALIBRATION59_OPAMP_FUSE_CPURAIL_CPU6_FT_5_2_BMSK                                               0xf
#define HWIO_CALIBRATION59_OPAMP_FUSE_CPURAIL_CPU6_FT_5_2_SHFT                                                 0

#define HWIO_CALIBRATION60_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc08)
#define HWIO_CALIBRATION60_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc08)
#define HWIO_CALIBRATION60_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION60_IN                    \
                in_dword(HWIO_CALIBRATION60_ADDR)
#define HWIO_CALIBRATION60_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION60_ADDR, m)
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU4_FT_7_0_BMSK                                       0xff000000
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU4_FT_7_0_SHFT                                               24
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU4_WS_BMSK                                             0xffc000
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU4_WS_SHFT                                                   14
#define HWIO_CALIBRATION60_CALIBRATION_1933_1922_BMSK                                                     0x3ffc
#define HWIO_CALIBRATION60_CALIBRATION_1933_1922_SHFT                                                          2
#define HWIO_CALIBRATION60_OPAMP_FUSE_NSPRAIL_HMX_WS_5_4_BMSK                                                0x3
#define HWIO_CALIBRATION60_OPAMP_FUSE_NSPRAIL_HMX_WS_5_4_SHFT                                                  0

#define HWIO_CALIBRATION61_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc0c)
#define HWIO_CALIBRATION61_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc0c)
#define HWIO_CALIBRATION61_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION61_IN                    \
                in_dword(HWIO_CALIBRATION61_ADDR)
#define HWIO_CALIBRATION61_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION61_ADDR, m)
#define HWIO_CALIBRATION61_CALIBRATION_1983_1974_BMSK                                                 0xffc00000
#define HWIO_CALIBRATION61_CALIBRATION_1983_1974_SHFT                                                         22
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_CPU5_FT_BMSK                                             0x3ff000
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_CPU5_FT_SHFT                                                   12
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_CPU5_WS_BMSK                                                0xffc
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_CPU5_WS_SHFT                                                    2
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_CPU4_FT_9_8_BMSK                                              0x3
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_CPU4_FT_9_8_SHFT                                                0

#define HWIO_CALIBRATION62_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc10)
#define HWIO_CALIBRATION62_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc10)
#define HWIO_CALIBRATION62_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION62_IN                    \
                in_dword(HWIO_CALIBRATION62_ADDR)
#define HWIO_CALIBRATION62_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION62_ADDR, m)
#define HWIO_CALIBRATION62_CALIBRATION_2015_2014_BMSK                                                 0xc0000000
#define HWIO_CALIBRATION62_CALIBRATION_2015_2014_SHFT                                                         30
#define HWIO_CALIBRATION62_GFX_PEAK_VOLTAGE_DELTA_BMSK                                                0x3e000000
#define HWIO_CALIBRATION62_GFX_PEAK_VOLTAGE_DELTA_SHFT                                                        25
#define HWIO_CALIBRATION62_GFX_PEAK_VOLTAGE_H_LF_BMSK                                                  0x1ff8000
#define HWIO_CALIBRATION62_GFX_PEAK_VOLTAGE_H_LF_SHFT                                                         15
#define HWIO_CALIBRATION62_GFX_PEAK_CURRENT_DELTA_BMSK                                                    0x7ff8
#define HWIO_CALIBRATION62_GFX_PEAK_CURRENT_DELTA_SHFT                                                         3
#define HWIO_CALIBRATION62_CALIBRATION_1986_1984_BMSK                                                        0x7
#define HWIO_CALIBRATION62_CALIBRATION_1986_1984_SHFT                                                          0

#define HWIO_CALIBRATION63_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc14)
#define HWIO_CALIBRATION63_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc14)
#define HWIO_CALIBRATION63_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION63_IN                    \
                in_dword(HWIO_CALIBRATION63_ADDR)
#define HWIO_CALIBRATION63_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION63_ADDR, m)
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_HVX_F1_1_0_BMSK                                        0xc0000000
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_HVX_F1_1_0_SHFT                                                30
#define HWIO_CALIBRATION63_ACC_LV_MXA_BMSK                                                            0x3f000000
#define HWIO_CALIBRATION63_ACC_LV_MXA_SHFT                                                                    24
#define HWIO_CALIBRATION63_ACC_HV_MXC_BMSK                                                              0xfc0000
#define HWIO_CALIBRATION63_ACC_HV_MXC_SHFT                                                                    18
#define HWIO_CALIBRATION63_ACC_HV_MXA_BMSK                                                               0x3f000
#define HWIO_CALIBRATION63_ACC_HV_MXA_SHFT                                                                    12
#define HWIO_CALIBRATION63_CALIBRATION_2027_2016_BMSK                                                      0xfff
#define HWIO_CALIBRATION63_CALIBRATION_2027_2016_SHFT                                                          0

#define HWIO_CALIBRATION64_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc18)
#define HWIO_CALIBRATION64_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc18)
#define HWIO_CALIBRATION64_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION64_IN                    \
                in_dword(HWIO_CALIBRATION64_ADDR)
#define HWIO_CALIBRATION64_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION64_ADDR, m)
#define HWIO_CALIBRATION64_ISENSE_FUSE_CURRENT_HMX_F2_3_0_BMSK                                        0xf0000000
#define HWIO_CALIBRATION64_ISENSE_FUSE_CURRENT_HMX_F2_3_0_SHFT                                                28
#define HWIO_CALIBRATION64_ISENSE_FUSE_CURRENT_HMX_F1_BMSK                                             0xffc0000
#define HWIO_CALIBRATION64_ISENSE_FUSE_CURRENT_HMX_F1_SHFT                                                    18
#define HWIO_CALIBRATION64_ISENSE_FUSE_CURRENT_HVX_F2_BMSK                                               0x3ff00
#define HWIO_CALIBRATION64_ISENSE_FUSE_CURRENT_HVX_F2_SHFT                                                     8
#define HWIO_CALIBRATION64_ISENSE_FUSE_CURRENT_HVX_F1_9_2_BMSK                                              0xff
#define HWIO_CALIBRATION64_ISENSE_FUSE_CURRENT_HVX_F1_9_2_SHFT                                                 0

#define HWIO_CALIBRATION65_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc1c)
#define HWIO_CALIBRATION65_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc1c)
#define HWIO_CALIBRATION65_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION65_IN                    \
                in_dword(HWIO_CALIBRATION65_ADDR)
#define HWIO_CALIBRATION65_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION65_ADDR, m)
#define HWIO_CALIBRATION65_OPAMP_FUSE_NSPRAIL_HMX_FT_0_BMSK                                           0x80000000
#define HWIO_CALIBRATION65_OPAMP_FUSE_NSPRAIL_HMX_FT_0_SHFT                                                   31
#define HWIO_CALIBRATION65_CALIBRATION_2110_2107_BMSK                                                 0x78000000
#define HWIO_CALIBRATION65_CALIBRATION_2110_2107_SHFT                                                         27
#define HWIO_CALIBRATION65_CPR4_TARG_VOLT_OFFSET_SVS_BMSK                                              0x7c00000
#define HWIO_CALIBRATION65_CPR4_TARG_VOLT_OFFSET_SVS_SHFT                                                     22
#define HWIO_CALIBRATION65_CALIBRATION_2101_2098_BMSK                                                   0x3c0000
#define HWIO_CALIBRATION65_CALIBRATION_2101_2098_SHFT                                                         18
#define HWIO_CALIBRATION65_ACC_LV_APC1_BMSK                                                              0x3f000
#define HWIO_CALIBRATION65_ACC_LV_APC1_SHFT                                                                   12
#define HWIO_CALIBRATION65_ISENSE_FUSE_REVISION_CONTROL_WS_BMSK                                            0xe00
#define HWIO_CALIBRATION65_ISENSE_FUSE_REVISION_CONTROL_WS_SHFT                                                9
#define HWIO_CALIBRATION65_ISENSE_FUSE_REVISION_CONTROL_FT_BMSK                                            0x1c0
#define HWIO_CALIBRATION65_ISENSE_FUSE_REVISION_CONTROL_FT_SHFT                                                6
#define HWIO_CALIBRATION65_ISENSE_FUSE_CURRENT_HMX_F2_9_4_BMSK                                              0x3f
#define HWIO_CALIBRATION65_ISENSE_FUSE_CURRENT_HMX_F2_9_4_SHFT                                                 0

#define HWIO_CALIBRATION66_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc20)
#define HWIO_CALIBRATION66_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc20)
#define HWIO_CALIBRATION66_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION66_IN                    \
                in_dword(HWIO_CALIBRATION66_ADDR)
#define HWIO_CALIBRATION66_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION66_ADDR, m)
#define HWIO_CALIBRATION66_CALIBRATION_2143_2127_BMSK                                                 0xffff8000
#define HWIO_CALIBRATION66_CALIBRATION_2143_2127_SHFT                                                         15
#define HWIO_CALIBRATION66_CPR5_TARG_VOLT_OFFSET_SVS_BMSK                                                 0x7c00
#define HWIO_CALIBRATION66_CPR5_TARG_VOLT_OFFSET_SVS_SHFT                                                     10
#define HWIO_CALIBRATION66_CPR5_TARG_VOLT_OFFSET_TUR_BMSK                                                  0x3e0
#define HWIO_CALIBRATION66_CPR5_TARG_VOLT_OFFSET_TUR_SHFT                                                      5
#define HWIO_CALIBRATION66_OPAMP_FUSE_NSPRAIL_HMX_FT_5_1_BMSK                                               0x1f
#define HWIO_CALIBRATION66_OPAMP_FUSE_NSPRAIL_HMX_FT_5_1_SHFT                                                  0

#define HWIO_CALIBRATION67_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc24)
#define HWIO_CALIBRATION67_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc24)
#define HWIO_CALIBRATION67_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION67_IN                    \
                in_dword(HWIO_CALIBRATION67_ADDR)
#define HWIO_CALIBRATION67_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION67_ADDR, m)
#define HWIO_CALIBRATION67_GFX_CURRENT_REVISION_BMSK                                                  0xc0000000
#define HWIO_CALIBRATION67_GFX_CURRENT_REVISION_SHFT                                                          30
#define HWIO_CALIBRATION67_CALIBRATION_2173_BMSK                                                      0x20000000
#define HWIO_CALIBRATION67_CALIBRATION_2173_SHFT                                                              29
#define HWIO_CALIBRATION67_CPR6_TARG_VOLT_SVS_BMSK                                                    0x1f800000
#define HWIO_CALIBRATION67_CPR6_TARG_VOLT_SVS_SHFT                                                            23
#define HWIO_CALIBRATION67_CPR5_TARG_VOLT_OFFSET_SVS2_BMSK                                              0x7c0000
#define HWIO_CALIBRATION67_CPR5_TARG_VOLT_OFFSET_SVS2_SHFT                                                    18
#define HWIO_CALIBRATION67_CALIBRATION_2161_2157_BMSK                                                    0x3e000
#define HWIO_CALIBRATION67_CALIBRATION_2161_2157_SHFT                                                         13
#define HWIO_CALIBRATION67_GFX_PEAK_CURRENT_I_LF_BMSK                                                     0x1fff
#define HWIO_CALIBRATION67_GFX_PEAK_CURRENT_I_LF_SHFT                                                          0

#define HWIO_CALIBRATION68_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc28)
#define HWIO_CALIBRATION68_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc28)
#define HWIO_CALIBRATION68_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION68_IN                    \
                in_dword(HWIO_CALIBRATION68_ADDR)
#define HWIO_CALIBRATION68_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION68_ADDR, m)
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_OFFSET_NOM_1_0_BMSK                                         0xc0000000
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_OFFSET_NOM_1_0_SHFT                                                 30
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_OFFSET_NOML1_BMSK                                           0x3e000000
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_OFFSET_NOML1_SHFT                                                   25
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_OFFSET_TUR_BMSK                                              0x1f00000
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_OFFSET_TUR_SHFT                                                     20
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_OFFSET_SUT_BMSK                                                0xf8000
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_OFFSET_SUT_SHFT                                                     15
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_SVS3_BMSK                                                       0x7e00
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_SVS3_SHFT                                                            9
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_SUT_BMSK                                                         0x1f8
#define HWIO_CALIBRATION68_CPR9_TARG_VOLT_SUT_SHFT                                                             3
#define HWIO_CALIBRATION68_CALIBRATION_2178_2176_BMSK                                                        0x7
#define HWIO_CALIBRATION68_CALIBRATION_2178_2176_SHFT                                                          0

#define HWIO_CALIBRATION69_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc2c)
#define HWIO_CALIBRATION69_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc2c)
#define HWIO_CALIBRATION69_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION69_IN                    \
                in_dword(HWIO_CALIBRATION69_ADDR)
#define HWIO_CALIBRATION69_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION69_ADDR, m)
#define HWIO_CALIBRATION69_CPR10_BOOST_QUOT_MIN_1_0_BMSK                                              0xc0000000
#define HWIO_CALIBRATION69_CPR10_BOOST_QUOT_MIN_1_0_SHFT                                                      30
#define HWIO_CALIBRATION69_CPR10_TARG_VOLT_BOOST_BMSK                                                 0x3f000000
#define HWIO_CALIBRATION69_CPR10_TARG_VOLT_BOOST_SHFT                                                         24
#define HWIO_CALIBRATION69_CALIBRATION_2231_BMSK                                                        0x800000
#define HWIO_CALIBRATION69_CALIBRATION_2231_SHFT                                                              23
#define HWIO_CALIBRATION69_CPR9_TARG_VOLT_OFFSET_SVS3_BMSK                                              0x7c0000
#define HWIO_CALIBRATION69_CPR9_TARG_VOLT_OFFSET_SVS3_SHFT                                                    18
#define HWIO_CALIBRATION69_CPR9_TARG_VOLT_OFFSET_SVS2_BMSK                                               0x3e000
#define HWIO_CALIBRATION69_CPR9_TARG_VOLT_OFFSET_SVS2_SHFT                                                    13
#define HWIO_CALIBRATION69_CPR9_TARG_VOLT_OFFSET_SVS_BMSK                                                 0x1f00
#define HWIO_CALIBRATION69_CPR9_TARG_VOLT_OFFSET_SVS_SHFT                                                      8
#define HWIO_CALIBRATION69_CPR9_TARG_VOLT_OFFSET_SVSL1_BMSK                                                 0xf8
#define HWIO_CALIBRATION69_CPR9_TARG_VOLT_OFFSET_SVSL1_SHFT                                                    3
#define HWIO_CALIBRATION69_CPR9_TARG_VOLT_OFFSET_NOM_4_2_BMSK                                                0x7
#define HWIO_CALIBRATION69_CPR9_TARG_VOLT_OFFSET_NOM_4_2_SHFT                                                  0

#define HWIO_CALIBRATION70_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc30)
#define HWIO_CALIBRATION70_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc30)
#define HWIO_CALIBRATION70_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION70_IN                    \
                in_dword(HWIO_CALIBRATION70_ADDR)
#define HWIO_CALIBRATION70_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION70_ADDR, m)
#define HWIO_CALIBRATION70_CPR13_TARG_VOLT_BOOSTP_BMSK                                                0xfc000000
#define HWIO_CALIBRATION70_CPR13_TARG_VOLT_BOOSTP_SHFT                                                        26
#define HWIO_CALIBRATION70_CPR12_AGING_BMSK                                                            0x3fc0000
#define HWIO_CALIBRATION70_CPR12_AGING_SHFT                                                                   18
#define HWIO_CALIBRATION70_CPR10_AGING_BMSK                                                              0x3fc00
#define HWIO_CALIBRATION70_CPR10_AGING_SHFT                                                                   10
#define HWIO_CALIBRATION70_CPR10_BOOST_QUOT_MIN_11_2_BMSK                                                  0x3ff
#define HWIO_CALIBRATION70_CPR10_BOOST_QUOT_MIN_11_2_SHFT                                                      0

#define HWIO_CALIBRATION71_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc34)
#define HWIO_CALIBRATION71_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc34)
#define HWIO_CALIBRATION71_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION71_IN                    \
                in_dword(HWIO_CALIBRATION71_ADDR)
#define HWIO_CALIBRATION71_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION71_ADDR, m)
#define HWIO_CALIBRATION71_CPR13_BOOSTP_QUOT_MIN_1_0_BMSK                                             0xc0000000
#define HWIO_CALIBRATION71_CPR13_BOOSTP_QUOT_MIN_1_0_SHFT                                                     30
#define HWIO_CALIBRATION71_CPR13_TARG_VOLT_SVS2_BMSK                                                  0x3f000000
#define HWIO_CALIBRATION71_CPR13_TARG_VOLT_SVS2_SHFT                                                          24
#define HWIO_CALIBRATION71_CPR13_TARG_VOLT_SVS_BMSK                                                     0xfc0000
#define HWIO_CALIBRATION71_CPR13_TARG_VOLT_SVS_SHFT                                                           18
#define HWIO_CALIBRATION71_CPR13_TARG_VOLT_NOM_BMSK                                                      0x3f000
#define HWIO_CALIBRATION71_CPR13_TARG_VOLT_NOM_SHFT                                                           12
#define HWIO_CALIBRATION71_CPR13_TARG_VOLT_TUR_BMSK                                                        0xfc0
#define HWIO_CALIBRATION71_CPR13_TARG_VOLT_TUR_SHFT                                                            6
#define HWIO_CALIBRATION71_CPR13_TARG_VOLT_BOOST_BMSK                                                       0x3f
#define HWIO_CALIBRATION71_CPR13_TARG_VOLT_BOOST_SHFT                                                          0

#define HWIO_CALIBRATION72_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc38)
#define HWIO_CALIBRATION72_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc38)
#define HWIO_CALIBRATION72_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION72_IN                    \
                in_dword(HWIO_CALIBRATION72_ADDR)
#define HWIO_CALIBRATION72_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION72_ADDR, m)
#define HWIO_CALIBRATION72_CPR13_TURBO_QUOT_MIN_9_0_BMSK                                              0xffc00000
#define HWIO_CALIBRATION72_CPR13_TURBO_QUOT_MIN_9_0_SHFT                                                      22
#define HWIO_CALIBRATION72_CPR13_BOOST_QUOT_MIN_BMSK                                                    0x3ffc00
#define HWIO_CALIBRATION72_CPR13_BOOST_QUOT_MIN_SHFT                                                          10
#define HWIO_CALIBRATION72_CPR13_BOOSTP_QUOT_MIN_11_2_BMSK                                                 0x3ff
#define HWIO_CALIBRATION72_CPR13_BOOSTP_QUOT_MIN_11_2_SHFT                                                     0

#define HWIO_CALIBRATION73_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc3c)
#define HWIO_CALIBRATION73_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc3c)
#define HWIO_CALIBRATION73_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION73_IN                    \
                in_dword(HWIO_CALIBRATION73_ADDR)
#define HWIO_CALIBRATION73_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION73_ADDR, m)
#define HWIO_CALIBRATION73_CPR13_SVS2_QUOT_MIN_5_0_BMSK                                               0xfc000000
#define HWIO_CALIBRATION73_CPR13_SVS2_QUOT_MIN_5_0_SHFT                                                       26
#define HWIO_CALIBRATION73_CPR13_SVS_QUOT_MIN_BMSK                                                     0x3ffc000
#define HWIO_CALIBRATION73_CPR13_SVS_QUOT_MIN_SHFT                                                            14
#define HWIO_CALIBRATION73_CPR13_NOMINAL_QUOT_MIN_BMSK                                                    0x3ffc
#define HWIO_CALIBRATION73_CPR13_NOMINAL_QUOT_MIN_SHFT                                                         2
#define HWIO_CALIBRATION73_CPR13_TURBO_QUOT_MIN_11_10_BMSK                                                   0x3
#define HWIO_CALIBRATION73_CPR13_TURBO_QUOT_MIN_11_10_SHFT                                                     0

#define HWIO_CALIBRATION74_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc40)
#define HWIO_CALIBRATION74_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc40)
#define HWIO_CALIBRATION74_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION74_IN                    \
                in_dword(HWIO_CALIBRATION74_ADDR)
#define HWIO_CALIBRATION74_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION74_ADDR, m)
#define HWIO_CALIBRATION74_CPR_RESERVED_26_13_BMSK                                                    0xfffc0000
#define HWIO_CALIBRATION74_CPR_RESERVED_26_13_SHFT                                                            18
#define HWIO_CALIBRATION74_CPR_NSPCX_MODE_DISABLE_BMSK                                                   0x38000
#define HWIO_CALIBRATION74_CPR_NSPCX_MODE_DISABLE_SHFT                                                        15
#define HWIO_CALIBRATION74_CPR_LOCAL_RC_3_BMSK                                                            0x4000
#define HWIO_CALIBRATION74_CPR_LOCAL_RC_3_SHFT                                                                14
#define HWIO_CALIBRATION74_CPR13_QUOT_OFFSET_BMSK                                                         0x3fc0
#define HWIO_CALIBRATION74_CPR13_QUOT_OFFSET_SHFT                                                              6
#define HWIO_CALIBRATION74_CPR13_SVS2_QUOT_MIN_11_6_BMSK                                                    0x3f
#define HWIO_CALIBRATION74_CPR13_SVS2_QUOT_MIN_11_6_SHFT                                                       0

#define HWIO_CALIBRATION75_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc44)
#define HWIO_CALIBRATION75_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc44)
#define HWIO_CALIBRATION75_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION75_IN                    \
                in_dword(HWIO_CALIBRATION75_ADDR)
#define HWIO_CALIBRATION75_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION75_ADDR, m)
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS98_AUP1_BMSK                                           0x80000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS98_AUP1_SHFT                                                   31
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AG2_BMSK                                            0x40000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AG2_SHFT                                                    30
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AG1_BMSK                                            0x20000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AG1_SHFT                                                    29
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU_BMSK                                             0x10000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU_SHFT                                                     28
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU2_BMSK                                             0x8000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU2_SHFT                                                    27
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU1_BMSK                                             0x4000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU1_SHFT                                                    26
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP_BMSK                                             0x2000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP_SHFT                                                    25
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP2_BMSK                                            0x1000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP2_SHFT                                                   24
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP1_BMSK                                             0x800000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP1_SHFT                                                   23
#define HWIO_CALIBRATION75_CPR_RESERVED_49_27_BMSK                                                      0x7fffff
#define HWIO_CALIBRATION75_CPR_RESERVED_49_27_SHFT                                                             0

#define HWIO_CALIBRATION76_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc48)
#define HWIO_CALIBRATION76_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc48)
#define HWIO_CALIBRATION76_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION76_IN                    \
                in_dword(HWIO_CALIBRATION76_ADDR)
#define HWIO_CALIBRATION76_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION76_ADDR, m)
#define HWIO_CALIBRATION76_TSENS2_BASE0_4_0_BMSK                                                      0xf8000000
#define HWIO_CALIBRATION76_TSENS2_BASE0_4_0_SHFT                                                              27
#define HWIO_CALIBRATION76_CALIBRATION_2458_2457_BMSK                                                  0x6000000
#define HWIO_CALIBRATION76_CALIBRATION_2458_2457_SHFT                                                         25
#define HWIO_CALIBRATION76_AOSS_RDOPCODE_4_3_BMSK                                                      0x1800000
#define HWIO_CALIBRATION76_AOSS_RDOPCODE_4_3_SHFT                                                             23
#define HWIO_CALIBRATION76_EUSB2PHY_RCAL_CODE_BMSK                                                      0x780000
#define HWIO_CALIBRATION76_EUSB2PHY_RCAL_CODE_SHFT                                                            19
#define HWIO_CALIBRATION76_CALIBRATION_2450_2441_BMSK                                                    0x7fe00
#define HWIO_CALIBRATION76_CALIBRATION_2450_2441_SHFT                                                          9
#define HWIO_CALIBRATION76_GFX_CDYN_REVISION_BMSK                                                          0x180
#define HWIO_CALIBRATION76_GFX_CDYN_REVISION_SHFT                                                              7
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP8_BMSK                                                 0x40
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP8_SHFT                                                    6
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP7_BMSK                                                 0x20
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP7_SHFT                                                    5
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP6_BMSK                                                 0x10
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP6_SHFT                                                    4
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP5_BMSK                                                  0x8
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP5_SHFT                                                    3
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP4_BMSK                                                  0x4
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP4_SHFT                                                    2
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP3_BMSK                                                  0x2
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP3_SHFT                                                    1
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP2_BMSK                                                  0x1
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP2_SHFT                                                    0

#define HWIO_CALIBRATION77_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc4c)
#define HWIO_CALIBRATION77_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc4c)
#define HWIO_CALIBRATION77_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION77_IN                    \
                in_dword(HWIO_CALIBRATION77_ADDR)
#define HWIO_CALIBRATION77_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION77_ADDR, m)
#define HWIO_CALIBRATION77_NSP_ACD_DVM_VAL0_7_0_BMSK                                                  0xff000000
#define HWIO_CALIBRATION77_NSP_ACD_DVM_VAL0_7_0_SHFT                                                          24
#define HWIO_CALIBRATION77_NSP_ACD_DVM_ENABLE_BMSK                                                      0xff8000
#define HWIO_CALIBRATION77_NSP_ACD_DVM_ENABLE_SHFT                                                            15
#define HWIO_CALIBRATION77_TSENS2_BASE1_BMSK                                                              0x7fe0
#define HWIO_CALIBRATION77_TSENS2_BASE1_SHFT                                                                   5
#define HWIO_CALIBRATION77_TSENS2_BASE0_9_5_BMSK                                                            0x1f
#define HWIO_CALIBRATION77_TSENS2_BASE0_9_5_SHFT                                                               0

#define HWIO_CALIBRATION78_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc50)
#define HWIO_CALIBRATION78_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc50)
#define HWIO_CALIBRATION78_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION78_IN                    \
                in_dword(HWIO_CALIBRATION78_ADDR)
#define HWIO_CALIBRATION78_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION78_ADDR, m)
#define HWIO_CALIBRATION78_NSP_ACD_DVM_VAL1_15_0_BMSK                                                 0xffff0000
#define HWIO_CALIBRATION78_NSP_ACD_DVM_VAL1_15_0_SHFT                                                         16
#define HWIO_CALIBRATION78_NSP_ACD_DVM_VAL0_23_8_BMSK                                                     0xffff
#define HWIO_CALIBRATION78_NSP_ACD_DVM_VAL0_23_8_SHFT                                                          0

#define HWIO_CALIBRATION79_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc54)
#define HWIO_CALIBRATION79_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc54)
#define HWIO_CALIBRATION79_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION79_IN                    \
                in_dword(HWIO_CALIBRATION79_ADDR)
#define HWIO_CALIBRATION79_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION79_ADDR, m)
#define HWIO_CALIBRATION79_NSP_ACD_DVM_VAL2_BMSK                                                      0xffffff00
#define HWIO_CALIBRATION79_NSP_ACD_DVM_VAL2_SHFT                                                               8
#define HWIO_CALIBRATION79_NSP_ACD_DVM_VAL1_23_16_BMSK                                                      0xff
#define HWIO_CALIBRATION79_NSP_ACD_DVM_VAL1_23_16_SHFT                                                         0

#define HWIO_CALIBRATION80_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc58)
#define HWIO_CALIBRATION80_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc58)
#define HWIO_CALIBRATION80_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION80_IN                    \
                in_dword(HWIO_CALIBRATION80_ADDR)
#define HWIO_CALIBRATION80_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION80_ADDR, m)
#define HWIO_CALIBRATION80_NSP_ACD_DVM_VAL4_7_0_BMSK                                                  0xff000000
#define HWIO_CALIBRATION80_NSP_ACD_DVM_VAL4_7_0_SHFT                                                          24
#define HWIO_CALIBRATION80_NSP_ACD_DVM_VAL3_BMSK                                                        0xffffff
#define HWIO_CALIBRATION80_NSP_ACD_DVM_VAL3_SHFT                                                               0

#define HWIO_CALIBRATION81_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc5c)
#define HWIO_CALIBRATION81_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc5c)
#define HWIO_CALIBRATION81_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION81_IN                    \
                in_dword(HWIO_CALIBRATION81_ADDR)
#define HWIO_CALIBRATION81_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION81_ADDR, m)
#define HWIO_CALIBRATION81_NSP_ACD_DVM_VAL5_15_0_BMSK                                                 0xffff0000
#define HWIO_CALIBRATION81_NSP_ACD_DVM_VAL5_15_0_SHFT                                                         16
#define HWIO_CALIBRATION81_NSP_ACD_DVM_VAL4_23_8_BMSK                                                     0xffff
#define HWIO_CALIBRATION81_NSP_ACD_DVM_VAL4_23_8_SHFT                                                          0

#define HWIO_CALIBRATION82_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc60)
#define HWIO_CALIBRATION82_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc60)
#define HWIO_CALIBRATION82_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION82_IN                    \
                in_dword(HWIO_CALIBRATION82_ADDR)
#define HWIO_CALIBRATION82_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION82_ADDR, m)
#define HWIO_CALIBRATION82_NSP_ACD_DVM_VAL6_BMSK                                                      0xffffff00
#define HWIO_CALIBRATION82_NSP_ACD_DVM_VAL6_SHFT                                                               8
#define HWIO_CALIBRATION82_NSP_ACD_DVM_VAL5_23_16_BMSK                                                      0xff
#define HWIO_CALIBRATION82_NSP_ACD_DVM_VAL5_23_16_SHFT                                                         0

#define HWIO_CALIBRATION83_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc64)
#define HWIO_CALIBRATION83_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc64)
#define HWIO_CALIBRATION83_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION83_IN                    \
                in_dword(HWIO_CALIBRATION83_ADDR)
#define HWIO_CALIBRATION83_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION83_ADDR, m)
#define HWIO_CALIBRATION83_DDRSS_EW_FUSE_2_0_BMSK                                                     0x80000000
#define HWIO_CALIBRATION83_DDRSS_EW_FUSE_2_0_SHFT                                                             31
#define HWIO_CALIBRATION83_DDRSS_EW_FUSE_1_BMSK                                                       0x7f000000
#define HWIO_CALIBRATION83_DDRSS_EW_FUSE_1_SHFT                                                               24
#define HWIO_CALIBRATION83_NSP_ACD_DVM_VAL7_BMSK                                                        0xffffff
#define HWIO_CALIBRATION83_NSP_ACD_DVM_VAL7_SHFT                                                               0

#define HWIO_CALIBRATION84_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc68)
#define HWIO_CALIBRATION84_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc68)
#define HWIO_CALIBRATION84_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION84_IN                    \
                in_dword(HWIO_CALIBRATION84_ADDR)
#define HWIO_CALIBRATION84_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION84_ADDR, m)
#define HWIO_CALIBRATION84_DDRSS_CH1CA_PNTUNE_RT_0_BMSK                                               0x80000000
#define HWIO_CALIBRATION84_DDRSS_CH1CA_PNTUNE_RT_0_SHFT                                                       31
#define HWIO_CALIBRATION84_DDRSS_CH0DQ1_PNTUNE_RT_BMSK                                                0x60000000
#define HWIO_CALIBRATION84_DDRSS_CH0DQ1_PNTUNE_RT_SHFT                                                        29
#define HWIO_CALIBRATION84_DDRSS_CH0DQ0_PNTUNE_RT_BMSK                                                0x18000000
#define HWIO_CALIBRATION84_DDRSS_CH0DQ0_PNTUNE_RT_SHFT                                                        27
#define HWIO_CALIBRATION84_DDRSS_CH0CA_PNTUNE_RT_BMSK                                                  0x6000000
#define HWIO_CALIBRATION84_DDRSS_CH0CA_PNTUNE_RT_SHFT                                                         25
#define HWIO_CALIBRATION84_DDRSS_TP_REV_CTRL_BMSK                                                      0x1f00000
#define HWIO_CALIBRATION84_DDRSS_TP_REV_CTRL_SHFT                                                             20
#define HWIO_CALIBRATION84_DDRSS_EH_FUSE_2_BMSK                                                          0xfe000
#define HWIO_CALIBRATION84_DDRSS_EH_FUSE_2_SHFT                                                               13
#define HWIO_CALIBRATION84_DDRSS_EH_FUSE_1_BMSK                                                           0x1fc0
#define HWIO_CALIBRATION84_DDRSS_EH_FUSE_1_SHFT                                                                6
#define HWIO_CALIBRATION84_DDRSS_EW_FUSE_2_6_1_BMSK                                                         0x3f
#define HWIO_CALIBRATION84_DDRSS_EW_FUSE_2_6_1_SHFT                                                            0

#define HWIO_CALIBRATION85_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xc6c)
#define HWIO_CALIBRATION85_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xc6c)
#define HWIO_CALIBRATION85_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION85_IN                    \
                in_dword(HWIO_CALIBRATION85_ADDR)
#define HWIO_CALIBRATION85_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION85_ADDR, m)
#define HWIO_CALIBRATION85_CALIBRATION_2751_BMSK                                                      0x80000000
#define HWIO_CALIBRATION85_CALIBRATION_2751_SHFT                                                              31
#define HWIO_CALIBRATION85_DDRSS_CH2CA_PNTUNE_HT_BMSK                                                 0x60000000
#define HWIO_CALIBRATION85_DDRSS_CH2CA_PNTUNE_HT_SHFT                                                         29
#define HWIO_CALIBRATION85_DDRSS_CH1DQ1_PNTUNE_HT_BMSK                                                0x18000000
#define HWIO_CALIBRATION85_DDRSS_CH1DQ1_PNTUNE_HT_SHFT                                                        27
#define HWIO_CALIBRATION85_DDRSS_CH1DQ0_PNTUNE_HT_BMSK                                                 0x6000000
#define HWIO_CALIBRATION85_DDRSS_CH1DQ0_PNTUNE_HT_SHFT                                                        25
#define HWIO_CALIBRATION85_DDRSS_CH1CA_PNTUNE_HT_BMSK                                                  0x1800000
#define HWIO_CALIBRATION85_DDRSS_CH1CA_PNTUNE_HT_SHFT                                                         23
#define HWIO_CALIBRATION85_DDRSS_CH0DQ1_PNTUNE_HT_BMSK                                                  0x600000
#define HWIO_CALIBRATION85_DDRSS_CH0DQ1_PNTUNE_HT_SHFT                                                        21
#define HWIO_CALIBRATION85_DDRSS_CH0DQ0_PNTUNE_HT_BMSK                                                  0x180000
#define HWIO_CALIBRATION85_DDRSS_CH0DQ0_PNTUNE_HT_SHFT                                                        19
#define HWIO_CALIBRATION85_DDRSS_CH0CA_PNTUNE_HT_BMSK                                                    0x60000
#define HWIO_CALIBRATION85_DDRSS_CH0CA_PNTUNE_HT_SHFT                                                         17
#define HWIO_CALIBRATION85_DDRSS_CH3DQ1_PNTUNE_RT_BMSK                                                   0x18000
#define HWIO_CALIBRATION85_DDRSS_CH3DQ1_PNTUNE_RT_SHFT                                                        15
#define HWIO_CALIBRATION85_DDRSS_CH3DQ0_PNTUNE_RT_BMSK                                                    0x6000
#define HWIO_CALIBRATION85_DDRSS_CH3DQ0_PNTUNE_RT_SHFT                                                        13
#define HWIO_CALIBRATION85_DDRSS_CH3CA_PNTUNE_RT_BMSK                                                     0x1800
#define HWIO_CALIBRATION85_DDRSS_CH3CA_PNTUNE_RT_SHFT                                                         11
#define HWIO_CALIBRATION85_DDRSS_CH2DQ1_PNTUNE_RT_BMSK                                                     0x600
#define HWIO_CALIBRATION85_DDRSS_CH2DQ1_PNTUNE_RT_SHFT                                                         9
#define HWIO_CALIBRATION85_DDRSS_CH2DQ0_PNTUNE_RT_BMSK                                                     0x180
#define HWIO_CALIBRATION85_DDRSS_CH2DQ0_PNTUNE_RT_SHFT                                                         7
#define HWIO_CALIBRATION85_DDRSS_CH2CA_PNTUNE_RT_BMSK                                                       0x60
#define HWIO_CALIBRATION85_DDRSS_CH2CA_PNTUNE_RT_SHFT                                                          5
#define HWIO_CALIBRATION85_DDRSS_CH1DQ1_PNTUNE_RT_BMSK                                                      0x18
#define HWIO_CALIBRATION85_DDRSS_CH1DQ1_PNTUNE_RT_SHFT                                                         3
#define HWIO_CALIBRATION85_DDRSS_CH1DQ0_PNTUNE_RT_BMSK                                                       0x6
#define HWIO_CALIBRATION85_DDRSS_CH1DQ0_PNTUNE_RT_SHFT                                                         1
#define HWIO_CALIBRATION85_DDRSS_CH1CA_PNTUNE_RT_1_BMSK                                                      0x1
#define HWIO_CALIBRATION85_DDRSS_CH1CA_PNTUNE_RT_1_SHFT                                                        0

/*----------------------------------------------------------------------------
 * MODULE: QFPROM_CORR
 *--------------------------------------------------------------------------*/

#define QFPROM_CORR_REG_BASE                                                                               (TME_FUSECONTROLLER_BASE      + 0x00002000)
#define QFPROM_CORR_REG_BASE_SIZE                                                                          0x2000
#define QFPROM_CORR_REG_BASE_USED                                                                          0xfdc
#define QFPROM_CORR_REG_BASE_OFFS                                                                          0x00002000

#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x98)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0x98)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_SPEED_BIN_BMSK                                                       0xf0000000
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_SPEED_BIN_SHFT                                                               28
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_FEATURE_ID_BMSK                                                       0xff00000
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_FEATURE_ID_SHFT                                                              20
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_JTAG_ID_BMSK                                                            0xfffff
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_JTAG_ID_SHFT                                                                  0

#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x9c)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0x9c)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_BIN_V_IDENTIFIER_BMSK                                                0xc0000000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_BIN_V_IDENTIFIER_SHFT                                                        30
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_MINOR_REV_BMSK                                                       0x30000000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_MINOR_REV_SHFT                                                               28
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_LOGIC_RETENTION_BMSK                                                  0xe000000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_LOGIC_RETENTION_SHFT                                                         25
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_REVISION_CONTROL_BMSK                                            0x1c00000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_REVISION_CONTROL_SHFT                                                   22
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_PTE_DATA_53_44_BMSK                                                    0x3ff000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_PTE_DATA_53_44_SHFT                                                          12
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_CX_ACTIVE_BMSK                                                       0xffc
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_CX_ACTIVE_SHFT                                                           2
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_MULTIPLIER_BMSK                                                        0x3
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_MULTIPLIER_SHFT                                                          0

#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xa0)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xa0)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MXC_ACTIVE_6_0_BMSK                                             0xfe000000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MXC_ACTIVE_6_0_SHFT                                                     25
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MM_ACTIVE_BMSK                                                   0x1ff8000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MM_ACTIVE_SHFT                                                          15
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_WS_RT_BMSK                                                            0x4000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_WS_RT_SHFT                                                                14
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_WS_HT_BMSK                                                            0x2000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_WS_HT_SHFT                                                                13
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_FT_RT_BMSK                                                            0x1000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_FT_RT_SHFT                                                                12
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_FT_HT_BMSK                                                             0x800
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_FT_HT_SHFT                                                                11
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUBBINA_BMSK                                                              0x7c0
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUBBINA_SHFT                                                                  6
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_PTE_MCN_IDENTIFIER_BMSK                                                    0x20
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_PTE_MCN_IDENTIFIER_SHFT                                                       5
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_RETENTION_FAIL_BMSK                                                        0x10
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_RETENTION_FAIL_SHFT                                                           4
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_HV_ONLY_BMSK                                                                0x8
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_HV_ONLY_SHFT                                                                  3
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_WAFER_ZONE_BMSK                                                             0x7
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_WAFER_ZONE_SHFT                                                               0

#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xa4)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xa4)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_APC1_ACTIVE_8_0_BMSK                                            0xff800000
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_APC1_ACTIVE_8_0_SHFT                                                    23
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_APC0_ACTIVE_BMSK                                                  0x7fe000
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_APC0_ACTIVE_SHFT                                                        13
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_PTE_DATA_108_105_BMSK                                                    0x1e00
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_PTE_DATA_108_105_SHFT                                                         9
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_PARTIAL_BIN_BMSK                                                          0x1f0
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_PARTIAL_BIN_SHFT                                                              4
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_INT_SECURE_MCN_IDENTIFIER_BMSK                                              0x8
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_INT_SECURE_MCN_IDENTIFIER_SHFT                                                3
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_MXC_ACTIVE_9_7_BMSK                                                    0x7
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_MXC_ACTIVE_9_7_SHFT                                                      0

#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xa8)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xa8)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW2_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_PTE_DATA_159_157_BMSK                                                0xe0000000
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_PTE_DATA_159_157_SHFT                                                        29
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IDDQ_MODEM_ACTIVE_BMSK                                               0x1ff80000
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IDDQ_MODEM_ACTIVE_SHFT                                                       19
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_PTE_DATA_146_142_BMSK                                                   0x7c000
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_PTE_DATA_146_142_SHFT                                                        14
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_CPU_BASE_PRO_DIFF_BMSK                                                   0x3000
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_CPU_BASE_PRO_DIFF_SHFT                                                       12
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_DDR_FREQ_DIFF_BMSK                                                        0x800
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_DDR_FREQ_DIFF_SHFT                                                           11
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_RBSC_TOTAL_MW_BMSK                                                        0x7fe
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_RBSC_TOTAL_MW_SHFT                                                            1
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IDDQ_APC1_ACTIVE_9_BMSK                                                     0x1
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IDDQ_APC1_ACTIVE_9_SHFT                                                       0

#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xac)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xac)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW2_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA_191_BMSK                                                    0x80000000
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA_191_SHFT                                                            31
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IDDQ_CX_OFF_BMSK                                                     0x7f800000
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IDDQ_CX_OFF_SHFT                                                             23
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA_182_171_BMSK                                                  0x7ff800
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA_182_171_SHFT                                                        11
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IDDQ_GFX_ACTIVE_BMSK                                                      0x7fe
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IDDQ_GFX_ACTIVE_SHFT                                                          1
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA_160_BMSK                                                           0x1
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA_160_SHFT                                                             0

#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xb0)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xb0)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_223_221_BMSK                                                0xe0000000
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_223_221_SHFT                                                        29
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_WAFER_ID_BMSK                                                        0x1f000000
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_WAFER_ID_SHFT                                                                24
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_X_BMSK                                                             0xff0000
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_X_SHFT                                                                   16
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_Y_BMSK                                                               0xff00
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_Y_SHFT                                                                    8
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_MEM_RETENTION_BMSK                                                         0xe0
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_MEM_RETENTION_SHFT                                                            5
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_196_192_BMSK                                                      0x1f
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_196_192_SHFT                                                         0

#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xb4)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xb4)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW3_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_IDDQ_MXA_ACTIVE_7_0_BMSK                                             0xff000000
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_IDDQ_MXA_ACTIVE_7_0_SHFT                                                     24
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_PTE_DATA_247_238_BMSK                                                  0xffc000
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_PTE_DATA_247_238_SHFT                                                        14
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_BONE_PILE_BMSK                                                           0x3000
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_BONE_PILE_SHFT                                                               12
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_PTE_DATA_235_230_BMSK                                                     0xfc0
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_PTE_DATA_235_230_SHFT                                                         6
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_DVS_PREVIOUSLY_RUN_BMSK                                                    0x20
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_DVS_PREVIOUSLY_RUN_SHFT                                                       5
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_APC1_WC_ID_BMSK                                                            0x18
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_APC1_WC_ID_SHFT                                                               3
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_PTE_DATA_226_224_BMSK                                                       0x7
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_PTE_DATA_226_224_SHFT                                                         0

#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xb8)
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xb8)
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW4_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_RBSC_MXA_MA_3_0_BMSK                                                 0xf0000000
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_RBSC_MXA_MA_3_0_SHFT                                                         28
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_RBSC_NO_PX_MW_BMSK                                                    0xffc0000
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_RBSC_NO_PX_MW_SHFT                                                           18
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IDDQ_MXC_OFF_BMSK                                                       0x3fc00
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IDDQ_MXC_OFF_SHFT                                                            10
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IDDQ_MXA_OFF_BMSK                                                         0x3fc
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IDDQ_MXA_OFF_SHFT                                                             2
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IDDQ_MXA_ACTIVE_9_8_BMSK                                                    0x3
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IDDQ_MXA_ACTIVE_9_8_SHFT                                                      0

#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xbc)
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xbc)
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW4_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_NSP_ACTIVE_BMSK                                                 0xffc00000
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_NSP_ACTIVE_SHFT                                                         22
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_LPIMX_ACTIVE_BMSK                                                 0x3fc000
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_LPIMX_ACTIVE_SHFT                                                       14
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_LPICX_ACTIVE_BMSK                                                   0x3fc0
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_LPICX_ACTIVE_SHFT                                                        6
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_RBSC_MXA_MA_9_4_BMSK                                                       0x3f
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_RBSC_MXA_MA_9_4_SHFT                                                          0

#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xc0)
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xc0)
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW5_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW5_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_PTE_DATA_351_345_BMSK                                                0xfe000000
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_PTE_DATA_351_345_SHFT                                                        25
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_XO_SHUTDOWN_DISABLE_BMSK                                              0x1000000
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_XO_SHUTDOWN_DISABLE_SHFT                                                     24
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_TURBO_MODE_ONLY_BMSK                                                   0x800000
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_TURBO_MODE_ONLY_SHFT                                                         23
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_SUBBIND_BMSK                                                           0x7c0000
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_SUBBIND_SHFT                                                                 18
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_SUBBINC_BMSK                                                            0x3e000
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_SUBBINC_SHFT                                                                 13
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_SUBBINB_BMSK                                                             0x1f00
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_SUBBINB_SHFT                                                                  8
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_SP_PARTIAL_BMSK                                                            0x80
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_SP_PARTIAL_SHFT                                                               7
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_SP_BLANK_BMSK                                                              0x40
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_SP_BLANK_SHFT                                                                 6
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_ROW_IDENTIFIER_BMSK                                                        0x20
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_ROW_IDENTIFIER_SHFT                                                           5
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_MINSVS_FAIL_BMSK                                                           0x10
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_MINSVS_FAIL_SHFT                                                              4
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_DOU_BINNING_BMSK                                                            0xf
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_DOU_BINNING_SHFT                                                              0

#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xc4)
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xc4)
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW5_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_PTE_DATA_383_352_BMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_PTE_DATA_383_352_SHFT                                                         0

#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xc8)
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xc8)
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW6_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW6_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_PTE_DATA_415_384_BMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_PTE_DATA_415_384_SHFT                                                         0

#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xcc)
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xcc)
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW6_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW6_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_PTE_DATA_447_416_BMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_PTE_DATA_447_416_SHFT                                                         0

#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xd0)
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xd0)
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW7_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW7_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_PTE_DATA_479_448_BMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_PTE_DATA_479_448_SHFT                                                         0

#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xd4)
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xd4)
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW7_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW7_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_PTE_DATA_511_480_BMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_PTE_DATA_511_480_SHFT                                                         0

#define HWIO_QFPROM_CORR_PTE_ROW8_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xd8)
#define HWIO_QFPROM_CORR_PTE_ROW8_LSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xd8)
#define HWIO_QFPROM_CORR_PTE_ROW8_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW8_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW8_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW8_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW8_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW8_LSB_PTE_DATA_543_512_BMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW8_LSB_PTE_DATA_543_512_SHFT                                                         0

#define HWIO_QFPROM_CORR_PTE_ROW8_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0xdc)
#define HWIO_QFPROM_CORR_PTE_ROW8_MSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0xdc)
#define HWIO_QFPROM_CORR_PTE_ROW8_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW8_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW8_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW8_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW8_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW8_MSB_PTE_DATA_575_544_BMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW8_MSB_PTE_DATA_575_544_SHFT                                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7a8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7a8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_USB2PHY_RCAL_CODE_0_BMSK                                     0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_USB2PHY_RCAL_CODE_0_SHFT                                             31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_BANDGAP_TRIM_BMSK                                            0x7f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_BANDGAP_TRIM_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_2_NORTH_BGV_TRIM_BMSK                                   0xff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_2_NORTH_BGV_TRIM_SHFT                                         16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_0_NORTH_BGV_TRIM_BMSK                                     0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_0_NORTH_BGV_TRIM_SHFT                                          8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_1_SOUTH_BGV_TRIM_BMSK                                       0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_1_SOUTH_BGV_TRIM_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7ac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7ac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBRATION_63_44_BMSK                                       0xfffff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBRATION_63_44_SHFT                                               12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_APSS_CS_ADC_VREFP_CTRL_IN_BMSK                                    0xf00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_APSS_CS_ADC_VREFP_CTRL_IN_SHFT                                        8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_GFX_CS_ADC_VREFP_CTRL_IN_BMSK                                      0x80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_GFX_CS_ADC_VREFP_CTRL_IN_SHFT                                         7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ISENSE_CS_ADC_VREFP_CTRL_BMSK                                      0x78
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ISENSE_CS_ADC_VREFP_CTRL_SHFT                                         3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY_RCAL_CODE_3_1_BMSK                                          0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY_RCAL_CODE_3_1_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7b0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7b0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_64_BMSK                                       0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_64_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7b4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7b4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_127_96_BMSK                                      0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_127_96_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7b8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7b8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3DQ0_PNTUNE_HT_BMSK                                  0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3DQ0_PNTUNE_HT_SHFT                                          30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3CA_PNTUNE_HT_BMSK                                   0x30000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3CA_PNTUNE_HT_SHFT                                           28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ1_PNTUNE_HT_BMSK                                   0xc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ1_PNTUNE_HT_SHFT                                          26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ0_PNTUNE_HT_BMSK                                   0x3000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ0_PNTUNE_HT_SHFT                                          24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR8_TARG_VOLT_SVS2_BMSK                                       0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR8_TARG_VOLT_SVS2_SHFT                                             18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR5_TARG_VOLT_SVS_BMSK                                         0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR5_TARG_VOLT_SVS_SHFT                                              12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR3_TARG_VOLT_NOM_BMSK                                           0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR3_TARG_VOLT_NOM_SHFT                                               6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR3_TARG_VOLT_TUR_BMSK                                            0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR3_TARG_VOLT_TUR_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7bc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7bc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ISENSE_FUSE_CURRENT_CPU4_F2_7_0_BMSK                         0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ISENSE_FUSE_CURRENT_CPU4_F2_7_0_SHFT                                 24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ISENSE_FUSE_CURRENT_CPU4_F1_BMSK                               0xffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ISENSE_FUSE_CURRENT_CPU4_F1_SHFT                                     14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_OPAMP_FUSE_CPURAIL_CPU8_FT_BMSK                                  0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_OPAMP_FUSE_CPURAIL_CPU8_FT_SHFT                                       8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_OPAMP_FUSE_CPURAIL_CPU8_WS_BMSK                                    0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_OPAMP_FUSE_CPURAIL_CPU8_WS_SHFT                                       2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_DDRSS_CH3DQ1_PNTUNE_HT_BMSK                                         0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_DDRSS_CH3DQ1_PNTUNE_HT_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7c0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7c0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ISENSE_FUSE_CURRENT_CPU6_F1_BMSK                             0xffc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ISENSE_FUSE_CURRENT_CPU6_F1_SHFT                                     22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ISENSE_FUSE_CURRENT_CPU5_F2_BMSK                               0x3ff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ISENSE_FUSE_CURRENT_CPU5_F2_SHFT                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ISENSE_FUSE_CURRENT_CPU5_F1_BMSK                                  0xffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ISENSE_FUSE_CURRENT_CPU5_F1_SHFT                                      2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ISENSE_FUSE_CURRENT_CPU4_F2_9_8_BMSK                                0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ISENSE_FUSE_CURRENT_CPU4_F2_9_8_SHFT                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7c4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7c4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_CURRENT_CPU8_F1_1_0_BMSK                         0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_CURRENT_CPU8_F1_1_0_SHFT                                 30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_CURRENT_CPU7_F2_BMSK                             0x3ff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_CURRENT_CPU7_F2_SHFT                                     20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_CURRENT_CPU7_F1_BMSK                                0xffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_CURRENT_CPU7_F1_SHFT                                     10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_CURRENT_CPU6_F2_BMSK                                  0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_CURRENT_CPU6_F2_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7c8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7c8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ACC_HV_APC0_1_0_BMSK                                         0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ACC_HV_APC0_1_0_SHFT                                                 30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ACC_LV_MXC_BMSK                                              0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ACC_LV_MXC_SHFT                                                      24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR5_TARG_VOLT_TUR_BMSK                                        0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR5_TARG_VOLT_TUR_SHFT                                              18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ISENSE_FUSE_CURRENT_CPU8_F2_BMSK                                0x3ff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ISENSE_FUSE_CURRENT_CPU8_F2_SHFT                                      8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ISENSE_FUSE_CURRENT_CPU8_F1_9_2_BMSK                               0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ISENSE_FUSE_CURRENT_CPU8_F1_9_2_SHFT                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7cc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7cc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_LSVS_BMSK                              0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_LSVS_SHFT                                      27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR1_TARG_VOLT_NOML1_BMSK                                     0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR1_TARG_VOLT_NOML1_SHFT                                            21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CALIBRATION_308_304_BMSK                                       0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CALIBRATION_308_304_SHFT                                             16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_LV_APC0_BMSK                                                 0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_LV_APC0_SHFT                                                     10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_HV_APC1_BMSK                                                  0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_HV_APC1_SHFT                                                      4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_HV_APC0_5_2_BMSK                                                0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_HV_APC0_5_2_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7d0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7d0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CALIBRATION_351_325_BMSK                                     0xffffffe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CALIBRATION_351_325_SHFT                                              5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVSD0_BMSK                                  0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVSD0_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7d4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7d4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CALIBRATION_383_352_BMSK                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CALIBRATION_383_352_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7d8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7d8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR0_TARG_VOLT_OFFSET_SVS1_1_0_BMSK                          0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR0_TARG_VOLT_OFFSET_SVS1_1_0_SHFT                                  30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CALIBRATION_413_384_BMSK                                     0x3fffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CALIBRATION_413_384_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7dc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7dc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CALIBRATION_447_BMSK                                         0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CALIBRATION_447_SHFT                                                 31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR2_TARG_VOLT_OFFSET_LSVSL1_BMSK                            0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR2_TARG_VOLT_OFFSET_LSVSL1_SHFT                                    26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR2_TARG_VOLT_OFFSET_SVSL0_BMSK                              0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR2_TARG_VOLT_OFFSET_SVSL0_SHFT                                     21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CALIBRATION_436_434_BMSK                                       0x1c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CALIBRATION_436_434_SHFT                                             18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD3_BMSK                               0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD3_SHFT                                    13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD2_BMSK                                0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD2_SHFT                                     8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD1_BMSK                                  0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD1_SHFT                                     3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS1_4_2_BMSK                                 0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS1_4_2_SHFT                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7e0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7e0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_TUR_2_0_BMSK                           0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_TUR_2_0_SHFT                                   29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_SUT_BMSK                               0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_SUT_SHFT                                       24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SVS2_BMSK                                       0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SVS2_SHFT                                             18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SVS_BMSK                                         0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SVS_SHFT                                              12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_NOM_BMSK                                           0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_NOM_SHFT                                               6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SUT_BMSK                                            0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SUT_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7e4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7e4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_AGING_4_0_BMSK                                          0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_AGING_4_0_SHFT                                                  27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVS2_BMSK                               0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVS2_SHFT                                      22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVS_BMSK                                 0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVS_SHFT                                       17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVSL1_BMSK                                0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVSL1_SHFT                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_NOM_BMSK                                    0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_NOM_SHFT                                        7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_BMSK                                   0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_SHFT                                      2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_TUR_4_3_BMSK                                  0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_TUR_4_3_SHFT                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7e8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7e8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CALIBRATION_543_539_BMSK                                     0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CALIBRATION_543_539_SHFT                                             27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_SVS3_BMSK                                      0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_SVS3_SHFT                                             21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_SVS_BMSK                                        0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_SVS_SHFT                                              15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_NOM_BMSK                                          0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_NOM_SHFT                                               9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CALIBRATION_520_515_BMSK                                          0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CALIBRATION_520_515_SHFT                                              3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR0_AGING_7_5_BMSK                                                 0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR0_AGING_7_5_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7ec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7ec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_AGING_1_0_BMSK                                          0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_AGING_1_0_SHFT                                                  30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS3_BMSK                              0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS3_SHFT                                      25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS2_BMSK                               0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS2_SHFT                                      20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS_BMSK                                  0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS_SHFT                                       15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVSL1_BMSK                                 0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVSL1_SHFT                                     10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                    0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                        5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_NOML1_BMSK                                   0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_NOML1_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7f0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7f0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SVS3_1_0_BMSK                                 0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SVS3_1_0_SHFT                                         30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SVSL1_BMSK                                    0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SVSL1_SHFT                                            24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_NOM_BMSK                                        0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_NOM_SHFT                                              18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_NOML1_BMSK                                       0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_NOML1_SHFT                                            12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SUT_BMSK                                           0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SUT_SHFT                                               6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR1_AGING_7_2_BMSK                                                0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR1_AGING_7_2_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7f4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x7f4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_2_0_BMSK                         0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_2_0_SHFT                                 29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_BMSK                             0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_SHFT                                     24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                                 0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                       19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_NOML1_BMSK                                0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_NOML1_SHFT                                     14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_TUR_BMSK                                   0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_TUR_SHFT                                        9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SUT_BMSK                                    0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SUT_SHFT                                        4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_SVS3_5_2_BMSK                                        0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_SVS3_5_2_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x7f8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x7f8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR3_TARG_VOLT_SVS_0_BMSK                                   0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR3_TARG_VOLT_SVS_0_SHFT                                           31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CALIBRATION_670_665_BMSK                                    0x7e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CALIBRATION_670_665_SHFT                                            25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_AGING_BMSK                                              0x1fe0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_AGING_SHFT                                                     17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CALIBRATION_656_647_BMSK                                       0x1ff80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CALIBRATION_656_647_SHFT                                             7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVS_BMSK                                    0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVS_SHFT                                       2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVSL1_4_3_BMSK                               0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVSL1_4_3_SHFT                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x7fc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x7fc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CALIBRATION_703_701_BMSK                                    0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CALIBRATION_703_701_SHFT                                            29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_NOM_BMSK                                     0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_NOM_SHFT                                             23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_SVS_BMSK                                       0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_SVS_SHFT                                             17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_SUT_BMSK                                        0x1f800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_SUT_SHFT                                             11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CALIBRATION_682_677_BMSK                                         0x7e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CALIBRATION_682_677_SHFT                                             5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR3_TARG_VOLT_SVS_5_1_BMSK                                       0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR3_TARG_VOLT_SVS_5_1_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x800)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x800)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CALIBRATION_735_733_BMSK                                    0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CALIBRATION_735_733_SHFT                                            29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_SUT_BMSK                                     0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_SUT_SHFT                                             23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_SVSL1_BMSK                              0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_SVSL1_SHFT                                    18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_NOM_BMSK                                 0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_NOM_SHFT                                      13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_NOML1_BMSK                                0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_NOML1_SHFT                                     8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_SUT_BMSK                                    0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_SUT_SHFT                                       3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CALIBRATION_706_704_BMSK                                           0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CALIBRATION_706_704_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x804)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x804)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_SVSL1_1_0_BMSK                        0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_SVSL1_1_0_SHFT                                30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_NOM_BMSK                              0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_NOM_SHFT                                      25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_NOML1_BMSK                             0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_NOML1_SHFT                                    20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_SUT_BMSK                                 0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_SUT_SHFT                                      15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CALIBRATION_750_745_BMSK                                        0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CALIBRATION_750_745_SHFT                                             9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_NOM_BMSK                                          0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_NOM_SHFT                                              3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CALIBRATION_738_736_BMSK                                           0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CALIBRATION_738_736_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x808)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x808)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_TUR_4_0_BMSK                                 0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_TUR_4_0_SHFT                                         27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CALIBRATION_794_789_BMSK                                     0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CALIBRATION_794_789_SHFT                                            21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_NOM_BMSK                                       0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_NOM_SHFT                                             15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CALIBRATION_782_777_BMSK                                        0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CALIBRATION_782_777_SHFT                                             9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_TUR_BMSK                                          0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_TUR_SHFT                                              3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR5_TARG_VOLT_OFFSET_SVSL1_4_2_BMSK                               0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR5_TARG_VOLT_OFFSET_SVSL1_4_2_SHFT                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x80c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x80c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_NOM_2_0_BMSK                          0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_NOM_2_0_SHFT                                  29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CALIBRATION_828_824_BMSK                                    0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CALIBRATION_828_824_SHFT                                            24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_TUR_BMSK                                0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_TUR_SHFT                                      19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_SVS3_BMSK                                       0x7e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_SVS3_SHFT                                            13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_SVS_BMSK                                         0x1f80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_SVS_SHFT                                              7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_NOM_BMSK                                           0x7e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_NOM_SHFT                                              1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_TUR_5_BMSK                                          0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_TUR_5_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x810)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x810)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_TUR_1_0_BMSK                                 0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_TUR_1_0_SHFT                                         30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_AGING_BMSK                                             0x3fc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_AGING_SHFT                                                     22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS3_BMSK                               0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS3_SHFT                                     17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS2_BMSK                                0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS2_SHFT                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS_BMSK                                   0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS_SHFT                                       7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVSL1_BMSK                                  0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVSL1_SHFT                                     2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_NOM_4_3_BMSK                                 0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_NOM_4_3_SHFT                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x814)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x814)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_NOM_BMSK                              0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_NOM_SHFT                                      27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_TUR_BMSK                               0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_TUR_SHFT                                      22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CALIBRATION_885_880_BMSK                                      0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CALIBRATION_885_880_SHFT                                            16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_SVS_BMSK                                         0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_SVS_SHFT                                             10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_NOM_BMSK                                          0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_NOM_SHFT                                              4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_TUR_5_2_BMSK                                        0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_TUR_5_2_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x818)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x818)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CALIBRATION_927_924_BMSK                                    0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CALIBRATION_927_924_SHFT                                            28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_AGING_BMSK                                              0xff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_AGING_SHFT                                                     20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CALIBATION_BMSK                                                0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CALIBATION_SHFT                                                     15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVS2_BMSK                                 0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVS2_SHFT                                     10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVS_BMSK                                   0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVS_SHFT                                       5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVSL1_BMSK                                  0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVSL1_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x81c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x81c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CALIBRATION_959_942_BMSK                                    0xffffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CALIBRATION_959_942_SHFT                                            14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_SVS_BMSK                                         0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_SVS_SHFT                                              8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_NOM_BMSK                                           0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_NOM_SHFT                                              2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CALIBRATION_929_928_BMSK                                           0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CALIBRATION_929_928_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x820)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x820)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CALIBRATION_991_960_BMSK                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CALIBRATION_991_960_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x824)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x824)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_NOM_BMSK                                    0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_NOM_SHFT                                            26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_TUR_BMSK                                     0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_TUR_SHFT                                            20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR9_AGING_BMSK                                                0xff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR9_AGING_SHFT                                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CALIBRATION_1003_992_BMSK                                        0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CALIBRATION_1003_992_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x828)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x828)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_NOMINAL_QUOT_MIN_7_0_BMSK                             0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_NOMINAL_QUOT_MIN_7_0_SHFT                                     24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TURBO_QUOT_MIN_BMSK                                     0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TURBO_QUOT_MIN_SHFT                                           12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TARG_VOLT_SVS2_BMSK                                        0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TARG_VOLT_SVS2_SHFT                                            6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TARG_VOLT_SVS_BMSK                                          0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TARG_VOLT_SVS_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x82c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x82c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_QUOT_OFFSET_3_0_BMSK                                  0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_QUOT_OFFSET_3_0_SHFT                                          28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS2_QUOT_MIN_BMSK                                     0xfff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS2_QUOT_MIN_SHFT                                            16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS_QUOT_MIN_BMSK                                         0xfff0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS_QUOT_MIN_SHFT                                              4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_NOMINAL_QUOT_MIN_11_8_BMSK                                   0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_NOMINAL_QUOT_MIN_11_8_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x830)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x830)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_SVS2_3_0_BMSK                               0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_SVS2_3_0_SHFT                                       28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_SVS_BMSK                                     0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_SVS_SHFT                                            22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_NOM_BMSK                                      0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_NOM_SHFT                                            16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_TUR_BMSK                                        0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_TUR_SHFT                                            10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_BOOST_BMSK                                       0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_BOOST_SHFT                                           4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR10_QUOT_OFFSET_7_4_BMSK                                         0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR10_QUOT_OFFSET_7_4_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x834)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x834)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_NOMINAL_QUOT_MIN_5_0_BMSK                             0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_NOMINAL_QUOT_MIN_5_0_SHFT                                     26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TURBO_QUOT_MIN_BMSK                                    0x3ffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TURBO_QUOT_MIN_SHFT                                           14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_BOOST_QUOT_MIN_BMSK                                       0x3ffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_BOOST_QUOT_MIN_SHFT                                            2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS2_5_4_BMSK                                      0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS2_5_4_SHFT                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x838)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x838)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_QUOT_OFFSET_1_0_BMSK                                  0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_QUOT_OFFSET_1_0_SHFT                                          30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS2_QUOT_MIN_BMSK                                    0x3ffc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS2_QUOT_MIN_SHFT                                            18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS_QUOT_MIN_BMSK                                        0x3ffc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS_QUOT_MIN_SHFT                                              6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_NOMINAL_QUOT_MIN_11_6_BMSK                                  0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_NOMINAL_QUOT_MIN_11_6_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x83c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x83c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_NOM_BMSK                                    0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_NOM_SHFT                                            26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_TUR_BMSK                                     0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_TUR_SHFT                                            20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOST_BMSK                                     0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOST_SHFT                                          14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CALIBRATION_1197_1190_BMSK                                      0x3fc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CALIBRATION_1197_1190_SHFT                                           6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR11_QUOT_OFFSET_7_2_BMSK                                        0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR11_QUOT_OFFSET_7_2_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x840)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x840)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TURBO_QUOT_MIN_7_0_BMSK                               0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TURBO_QUOT_MIN_7_0_SHFT                                       24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_BOOST_QUOT_MIN_BMSK                                     0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_BOOST_QUOT_MIN_SHFT                                           12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS2_BMSK                                        0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS2_SHFT                                            6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS_BMSK                                          0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x844)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x844)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_SVS2_QUOT_MIN_3_0_BMSK                                0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_SVS2_QUOT_MIN_3_0_SHFT                                        28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_SVS_QUOT_MIN_BMSK                                      0xfff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_SVS_QUOT_MIN_SHFT                                             16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_NOMINAL_QUOT_MIN_BMSK                                     0xfff0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_NOMINAL_QUOT_MIN_SHFT                                          4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_TURBO_QUOT_MIN_11_8_BMSK                                     0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_TURBO_QUOT_MIN_11_8_SHFT                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x848)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x848)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MXC_MODE_DISABLE_0_BMSK                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MXC_MODE_DISABLE_0_SHFT                                         31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MX_MODE_DISABLE_BMSK                                    0x70000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MX_MODE_DISABLE_SHFT                                            28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_GFX_MODE_DISABLE_BMSK                                    0xe000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_GFX_MODE_DISABLE_SHFT                                           25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MSS_MODE_DISABLE_BMSK                                    0x1c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MSS_MODE_DISABLE_SHFT                                           22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_CX_MODE_DISABLE_BMSK                                      0x380000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_CX_MODE_DISABLE_SHFT                                            19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_LOCAL_RC_2_0_BMSK                                          0x70000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_LOCAL_RC_2_0_SHFT                                               16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_QUOT_OFFSET_BMSK                                          0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_QUOT_OFFSET_SHFT                                               8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_SVS2_QUOT_MIN_11_4_BMSK                                     0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_SVS2_QUOT_MIN_11_4_SHFT                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x84c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x84c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_GLOBAL_RC_0_BMSK                                        0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_GLOBAL_RC_0_SHFT                                                31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_AON_AGING_BMSK                                              0x7f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_AON_AGING_SHFT                                                      23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_AON_TARG_VOLT_BMSK                                            0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_AON_TARG_VOLT_SHFT                                                  17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_APC1_MODE_DISABLE_BMSK                                     0x1c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_APC1_MODE_DISABLE_SHFT                                          14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_APC0_MODE_DISABLE_BMSK                                      0x3800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_APC0_MODE_DISABLE_SHFT                                          11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MMCX_MODE_DISABLE_BMSK                                       0x700
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MMCX_MODE_DISABLE_SHFT                                           8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_SSCCX_MODE_DISABLE_BMSK                                       0xe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_SSCCX_MODE_DISABLE_SHFT                                          5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPIMX_MODE_DISABLE_BMSK                                       0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPIMX_MODE_DISABLE_SHFT                                          2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MXC_MODE_DISABLE_2_1_BMSK                                      0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MXC_MODE_DISABLE_2_1_SHFT                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x850)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x850)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_BOOSTP_QUOT_MIN_5_0_BMSK                              0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_BOOSTP_QUOT_MIN_5_0_SHFT                                      26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_TARG_VOLT_BOOSTP_BMSK                                  0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_TARG_VOLT_BOOSTP_SHFT                                         20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CALIBRATION_1363_1346_BMSK                                     0xffffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CALIBRATION_1363_1346_SHFT                                           2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_GLOBAL_RC_2_1_BMSK                                             0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_GLOBAL_RC_2_1_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x854)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x854)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CALIBRATION_1407_1403_BMSK                                  0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CALIBRATION_1407_1403_SHFT                                          27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_FREQ_BMSK                                 0x6000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_FREQ_SHFT                                        25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_TJ_BMSK                                   0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_TJ_SHFT                                          20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_GLOBAL_RC_3_BMSK                                           0x80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_GLOBAL_RC_3_SHFT                                                19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_RESERVED_12_0_BMSK                                         0x7ffc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_RESERVED_12_0_SHFT                                               6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR12_BOOSTP_QUOT_MIN_11_6_BMSK                                   0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR12_BOOSTP_QUOT_MIN_11_6_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x858)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x858)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CALIBRATION_1439_1408_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CALIBRATION_1439_1408_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x85c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x85c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_AOSS_K_5_0_BMSK                                             0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_AOSS_K_5_0_SHFT                                                     26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CALIBRATION_1465_1440_BMSK                                   0x3ffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CALIBRATION_1465_1440_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x860)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x860)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_P1_3_0_BMSK                                            0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_P1_3_0_SHFT                                                    28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_N1_BMSK                                                 0xffffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_N1_SHFT                                                        10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_K_15_6_BMSK                                                 0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_K_15_6_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x864)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x864)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_CALIBRATION_1535_1532_BMSK                                  0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_CALIBRATION_1535_1532_SHFT                                          28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_CPR4_TARG_VOLT_TUR_BMSK                                      0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_CPR4_TARG_VOLT_TUR_SHFT                                             22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_TDOPCODE_BMSK                                            0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_TDOPCODE_SHFT                                                  17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_RDOPCODE_2_0_BMSK                                         0x1c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_RDOPCODE_2_0_SHFT                                              14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_P1_17_4_BMSK                                               0x3fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_P1_17_4_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x868)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x868)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE1_1_0_BMSK                                       0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE1_1_0_SHFT                                               30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE0_BMSK                                           0x3ff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE0_SHFT                                                   20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE1_BMSK                                              0xffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE1_SHFT                                                   10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE0_BMSK                                                0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE0_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x86c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x86c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS4_OFFSET_3_0_BMSK                                      0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS4_OFFSET_3_0_SHFT                                              28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS3_OFFSET_BMSK                                           0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS3_OFFSET_SHFT                                                  23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS2_OFFSET_BMSK                                            0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS2_OFFSET_SHFT                                                  18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_OFFSET_BMSK                                             0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_OFFSET_SHFT                                                  13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS0_OFFSET_BMSK                                              0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS0_OFFSET_SHFT                                                   8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_BASE1_9_2_BMSK                                             0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_BASE1_9_2_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x870)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x870)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS11_OFFSET_0_BMSK                                       0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS11_OFFSET_0_SHFT                                               31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS10_OFFSET_BMSK                                         0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS10_OFFSET_SHFT                                                 26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS9_OFFSET_BMSK                                           0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS9_OFFSET_SHFT                                                  21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS8_OFFSET_BMSK                                            0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS8_OFFSET_SHFT                                                  16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS7_OFFSET_BMSK                                              0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS7_OFFSET_SHFT                                                  11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS6_OFFSET_BMSK                                               0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS6_OFFSET_SHFT                                                   6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS5_OFFSET_BMSK                                                0x3e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS5_OFFSET_SHFT                                                   1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS4_OFFSET_4_BMSK                                               0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS4_OFFSET_4_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x874)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x874)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS17_OFFSET_2_0_BMSK                                     0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS17_OFFSET_2_0_SHFT                                             29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS16_OFFSET_BMSK                                         0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS16_OFFSET_SHFT                                                 24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS15_OFFSET_BMSK                                           0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS15_OFFSET_SHFT                                                 19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS14_OFFSET_BMSK                                            0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS14_OFFSET_SHFT                                                 14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS13_OFFSET_BMSK                                             0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS13_OFFSET_SHFT                                                  9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS12_OFFSET_BMSK                                              0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS12_OFFSET_SHFT                                                  4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS11_OFFSET_4_1_BMSK                                            0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS11_OFFSET_4_1_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x878)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x878)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS23_OFFSET_BMSK                                         0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS23_OFFSET_SHFT                                                 27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS22_OFFSET_BMSK                                          0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS22_OFFSET_SHFT                                                 22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS21_OFFSET_BMSK                                           0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS21_OFFSET_SHFT                                                 17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS20_OFFSET_BMSK                                            0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS20_OFFSET_SHFT                                                 12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS19_OFFSET_BMSK                                              0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS19_OFFSET_SHFT                                                  7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS18_OFFSET_BMSK                                               0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS18_OFFSET_SHFT                                                  2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS17_OFFSET_4_3_BMSK                                            0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS17_OFFSET_4_3_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x87c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x87c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS30_OFFSET_1_0_BMSK                                     0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS30_OFFSET_1_0_SHFT                                             30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS29_OFFSET_BMSK                                         0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS29_OFFSET_SHFT                                                 25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS28_OFFSET_BMSK                                          0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS28_OFFSET_SHFT                                                 20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS27_OFFSET_BMSK                                            0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS27_OFFSET_SHFT                                                 15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS26_OFFSET_BMSK                                             0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS26_OFFSET_SHFT                                                 10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS25_OFFSET_BMSK                                              0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS25_OFFSET_SHFT                                                  5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS24_OFFSET_BMSK                                               0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS24_OFFSET_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x880)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x880)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS36_OFFSET_0_BMSK                                       0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS36_OFFSET_0_SHFT                                               31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS35_OFFSET_BMSK                                         0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS35_OFFSET_SHFT                                                 26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS34_OFFSET_BMSK                                          0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS34_OFFSET_SHFT                                                 21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS33_OFFSET_BMSK                                           0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS33_OFFSET_SHFT                                                 16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS32_OFFSET_BMSK                                             0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS32_OFFSET_SHFT                                                 11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS_CAL_SEL_BMSK                                               0x700
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS_CAL_SEL_SHFT                                                   8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS31_OFFSET_BMSK                                               0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS31_OFFSET_SHFT                                                  3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS30_OFFSET_4_2_BMSK                                            0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS30_OFFSET_4_2_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x884)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x884)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CALIBRATION_1791_1790_BMSK                                  0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CALIBRATION_1791_1790_SHFT                                          30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CPR4_TARG_VOLT_OFFSET_TUR_BMSK                              0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CPR4_TARG_VOLT_OFFSET_TUR_SHFT                                      25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS_REV_CTRL_BMSK                                          0x1000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS_REV_CTRL_SHFT                                                 24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS40_OFFSET_BMSK                                           0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS40_OFFSET_SHFT                                                 19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS39_OFFSET_BMSK                                            0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS39_OFFSET_SHFT                                                 14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS38_OFFSET_BMSK                                             0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS38_OFFSET_SHFT                                                  9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS37_OFFSET_BMSK                                              0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS37_OFFSET_SHFT                                                  4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS36_OFFSET_4_1_BMSK                                            0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS36_OFFSET_4_1_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x888)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x888)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CALIBRATION_1823_1792_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CALIBRATION_1823_1792_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x88c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x88c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CALIBRATION_1855_1852_BMSK                                  0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CALIBRATION_1855_1852_SHFT                                          28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CPR4_TARG_VOLT_OFFSET_SVS2_BMSK                              0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CPR4_TARG_VOLT_OFFSET_SVS2_SHFT                                     23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CALIBRATION_1846_1824_BMSK                                    0x7fffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CALIBRATION_1846_1824_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x890)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x890)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU6_FT_1_0_BMSK                         0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU6_FT_1_0_SHFT                                 30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU6_WS_BMSK                             0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU6_WS_SHFT                                     24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU5_FT_BMSK                               0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU5_FT_SHFT                                     18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU5_WS_BMSK                                0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU5_WS_SHFT                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU4_FT_BMSK                                  0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU4_FT_SHFT                                      6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU4_WS_BMSK                                   0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU4_WS_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x894)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x894)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_NSPRAIL_HMX_WS_3_0_BMSK                          0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_NSPRAIL_HMX_WS_3_0_SHFT                                  28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_NSPRAIL_HVX_FT_BMSK                               0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_NSPRAIL_HVX_FT_SHFT                                      22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_NSPRAIL_HVX_WS_BMSK                                0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_NSPRAIL_HVX_WS_SHFT                                      16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_CPURAIL_CPU7_FT_BMSK                                 0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_CPURAIL_CPU7_FT_SHFT                                     10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_CPURAIL_CPU7_WS_BMSK                                  0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_CPURAIL_CPU7_WS_SHFT                                      4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_CPURAIL_CPU6_FT_5_2_BMSK                                0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_CPURAIL_CPU6_FT_5_2_SHFT                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x898)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x898)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU4_FT_7_0_BMSK                        0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU4_FT_7_0_SHFT                                24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU4_WS_BMSK                              0xffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU4_WS_SHFT                                    14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CALIBRATION_1933_1922_BMSK                                      0x3ffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CALIBRATION_1933_1922_SHFT                                           2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_OPAMP_FUSE_NSPRAIL_HMX_WS_5_4_BMSK                                 0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_OPAMP_FUSE_NSPRAIL_HMX_WS_5_4_SHFT                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x89c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x89c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CALIBRATION_1983_1974_BMSK                                  0xffc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CALIBRATION_1983_1974_SHFT                                          22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_CPU5_FT_BMSK                              0x3ff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_CPU5_FT_SHFT                                    12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_CPU5_WS_BMSK                                 0xffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_CPU5_WS_SHFT                                     2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_CPU4_FT_9_8_BMSK                               0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_CPU4_FT_9_8_SHFT                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8a0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8a0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_2015_2014_BMSK                                  0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_2015_2014_SHFT                                          30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_DELTA_BMSK                                 0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_DELTA_SHFT                                         25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_H_LF_BMSK                                   0x1ff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_H_LF_SHFT                                          15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_CURRENT_DELTA_BMSK                                     0x7ff8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_CURRENT_DELTA_SHFT                                          3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_1986_1984_BMSK                                         0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_1986_1984_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8a4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8a4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ISENSE_FUSE_CURRENT_HVX_F1_1_0_BMSK                         0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ISENSE_FUSE_CURRENT_HVX_F1_1_0_SHFT                                 30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACC_LV_MXA_BMSK                                             0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACC_LV_MXA_SHFT                                                     24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACC_HV_MXC_BMSK                                               0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACC_HV_MXC_SHFT                                                     18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACC_HV_MXA_BMSK                                                0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACC_HV_MXA_SHFT                                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CALIBRATION_2027_2016_BMSK                                       0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CALIBRATION_2027_2016_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8a8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8a8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ISENSE_FUSE_CURRENT_HMX_F2_3_0_BMSK                         0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ISENSE_FUSE_CURRENT_HMX_F2_3_0_SHFT                                 28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ISENSE_FUSE_CURRENT_HMX_F1_BMSK                              0xffc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ISENSE_FUSE_CURRENT_HMX_F1_SHFT                                     18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ISENSE_FUSE_CURRENT_HVX_F2_BMSK                                0x3ff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ISENSE_FUSE_CURRENT_HVX_F2_SHFT                                      8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ISENSE_FUSE_CURRENT_HVX_F1_9_2_BMSK                               0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ISENSE_FUSE_CURRENT_HVX_F1_9_2_SHFT                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8ac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8ac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_OPAMP_FUSE_NSPRAIL_HMX_FT_0_BMSK                            0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_OPAMP_FUSE_NSPRAIL_HMX_FT_0_SHFT                                    31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2110_2107_BMSK                                  0x78000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2110_2107_SHFT                                          27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CPR4_TARG_VOLT_OFFSET_SVS_BMSK                               0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CPR4_TARG_VOLT_OFFSET_SVS_SHFT                                      22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2101_2098_BMSK                                    0x3c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2101_2098_SHFT                                          18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ACC_LV_APC1_BMSK                                               0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ACC_LV_APC1_SHFT                                                    12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ISENSE_FUSE_REVISION_CONTROL_WS_BMSK                             0xe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ISENSE_FUSE_REVISION_CONTROL_WS_SHFT                                 9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ISENSE_FUSE_REVISION_CONTROL_FT_BMSK                             0x1c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ISENSE_FUSE_REVISION_CONTROL_FT_SHFT                                 6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ISENSE_FUSE_CURRENT_HMX_F2_9_4_BMSK                               0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ISENSE_FUSE_CURRENT_HMX_F2_9_4_SHFT                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8b0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8b0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2143_2127_BMSK                                  0xffff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2143_2127_SHFT                                          15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CPR5_TARG_VOLT_OFFSET_SVS_BMSK                                  0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CPR5_TARG_VOLT_OFFSET_SVS_SHFT                                      10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CPR5_TARG_VOLT_OFFSET_TUR_BMSK                                   0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CPR5_TARG_VOLT_OFFSET_TUR_SHFT                                       5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_OPAMP_FUSE_NSPRAIL_HMX_FT_5_1_BMSK                                0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_OPAMP_FUSE_NSPRAIL_HMX_FT_5_1_SHFT                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8b4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8b4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_CURRENT_REVISION_BMSK                                   0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_CURRENT_REVISION_SHFT                                           30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CALIBRATION_2173_BMSK                                       0x20000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CALIBRATION_2173_SHFT                                               29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CPR6_TARG_VOLT_SVS_BMSK                                     0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CPR6_TARG_VOLT_SVS_SHFT                                             23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CPR5_TARG_VOLT_OFFSET_SVS2_BMSK                               0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CPR5_TARG_VOLT_OFFSET_SVS2_SHFT                                     18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CALIBRATION_2161_2157_BMSK                                     0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CALIBRATION_2161_2157_SHFT                                          13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_PEAK_CURRENT_I_LF_BMSK                                      0x1fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_PEAK_CURRENT_I_LF_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8b8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8b8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_OFFSET_NOM_1_0_BMSK                          0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_OFFSET_NOM_1_0_SHFT                                  30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_OFFSET_NOML1_BMSK                            0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_OFFSET_NOML1_SHFT                                    25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_OFFSET_TUR_BMSK                               0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_OFFSET_TUR_SHFT                                      20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_OFFSET_SUT_BMSK                                 0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_OFFSET_SUT_SHFT                                      15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_SVS3_BMSK                                        0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_SVS3_SHFT                                             9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_SUT_BMSK                                          0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CPR9_TARG_VOLT_SUT_SHFT                                              3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBRATION_2178_2176_BMSK                                         0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBRATION_2178_2176_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8bc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8bc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR10_BOOST_QUOT_MIN_1_0_BMSK                               0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR10_BOOST_QUOT_MIN_1_0_SHFT                                       30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR10_TARG_VOLT_BOOST_BMSK                                  0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR10_TARG_VOLT_BOOST_SHFT                                          24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CALIBRATION_2231_BMSK                                         0x800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CALIBRATION_2231_SHFT                                               23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR9_TARG_VOLT_OFFSET_SVS3_BMSK                               0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR9_TARG_VOLT_OFFSET_SVS3_SHFT                                     18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR9_TARG_VOLT_OFFSET_SVS2_BMSK                                0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR9_TARG_VOLT_OFFSET_SVS2_SHFT                                     13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR9_TARG_VOLT_OFFSET_SVS_BMSK                                  0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR9_TARG_VOLT_OFFSET_SVS_SHFT                                       8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR9_TARG_VOLT_OFFSET_SVSL1_BMSK                                  0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR9_TARG_VOLT_OFFSET_SVSL1_SHFT                                     3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR9_TARG_VOLT_OFFSET_NOM_4_2_BMSK                                 0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CPR9_TARG_VOLT_OFFSET_NOM_4_2_SHFT                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8c0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8c0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CPR13_TARG_VOLT_BOOSTP_BMSK                                 0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CPR13_TARG_VOLT_BOOSTP_SHFT                                         26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CPR12_AGING_BMSK                                             0x3fc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CPR12_AGING_SHFT                                                    18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CPR10_AGING_BMSK                                               0x3fc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CPR10_AGING_SHFT                                                    10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CPR10_BOOST_QUOT_MIN_11_2_BMSK                                   0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CPR10_BOOST_QUOT_MIN_11_2_SHFT                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8c4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8c4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_BOOSTP_QUOT_MIN_1_0_BMSK                              0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_BOOSTP_QUOT_MIN_1_0_SHFT                                      30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_TARG_VOLT_SVS2_BMSK                                   0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_TARG_VOLT_SVS2_SHFT                                           24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_TARG_VOLT_SVS_BMSK                                      0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_TARG_VOLT_SVS_SHFT                                            18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_TARG_VOLT_NOM_BMSK                                       0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_TARG_VOLT_NOM_SHFT                                            12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_TARG_VOLT_TUR_BMSK                                         0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_TARG_VOLT_TUR_SHFT                                             6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_TARG_VOLT_BOOST_BMSK                                        0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CPR13_TARG_VOLT_BOOST_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8c8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8c8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CPR13_TURBO_QUOT_MIN_9_0_BMSK                               0xffc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CPR13_TURBO_QUOT_MIN_9_0_SHFT                                       22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CPR13_BOOST_QUOT_MIN_BMSK                                     0x3ffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CPR13_BOOST_QUOT_MIN_SHFT                                           10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CPR13_BOOSTP_QUOT_MIN_11_2_BMSK                                  0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CPR13_BOOSTP_QUOT_MIN_11_2_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8cc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8cc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR13_SVS2_QUOT_MIN_5_0_BMSK                                0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR13_SVS2_QUOT_MIN_5_0_SHFT                                        26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR13_SVS_QUOT_MIN_BMSK                                      0x3ffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR13_SVS_QUOT_MIN_SHFT                                             14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR13_NOMINAL_QUOT_MIN_BMSK                                     0x3ffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR13_NOMINAL_QUOT_MIN_SHFT                                          2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR13_TURBO_QUOT_MIN_11_10_BMSK                                    0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR13_TURBO_QUOT_MIN_11_10_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8d0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8d0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR_RESERVED_26_13_BMSK                                     0xfffc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR_RESERVED_26_13_SHFT                                             18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR_NSPCX_MODE_DISABLE_BMSK                                    0x38000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR_NSPCX_MODE_DISABLE_SHFT                                         15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR_LOCAL_RC_3_BMSK                                             0x4000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR_LOCAL_RC_3_SHFT                                                 14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR13_QUOT_OFFSET_BMSK                                          0x3fc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR13_QUOT_OFFSET_SHFT                                               6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR13_SVS2_QUOT_MIN_11_6_BMSK                                     0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR13_SVS2_QUOT_MIN_11_6_SHFT                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8d4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8d4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS98_AUP1_BMSK                            0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS98_AUP1_SHFT                                    31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG2_BMSK                             0x40000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG2_SHFT                                     30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG1_BMSK                             0x20000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG1_SHFT                                     29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU_BMSK                              0x10000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU_SHFT                                      28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU2_BMSK                              0x8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU2_SHFT                                     27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU1_BMSK                              0x4000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU1_SHFT                                     26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP_BMSK                              0x2000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP_SHFT                                     25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP2_BMSK                             0x1000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP2_SHFT                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP1_BMSK                              0x800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP1_SHFT                                    23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPR_RESERVED_49_27_BMSK                                       0x7fffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPR_RESERVED_49_27_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8d8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8d8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_TSENS2_BASE0_4_0_BMSK                                       0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_TSENS2_BASE0_4_0_SHFT                                               27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CALIBRATION_2458_2457_BMSK                                   0x6000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CALIBRATION_2458_2457_SHFT                                          25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_AOSS_RDOPCODE_4_3_BMSK                                       0x1800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_AOSS_RDOPCODE_4_3_SHFT                                              23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_EUSB2PHY_RCAL_CODE_BMSK                                       0x780000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_EUSB2PHY_RCAL_CODE_SHFT                                             19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CALIBRATION_2450_2441_BMSK                                     0x7fe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CALIBRATION_2450_2441_SHFT                                           9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_GFX_CDYN_REVISION_BMSK                                           0x180
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_GFX_CDYN_REVISION_SHFT                                               7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP8_BMSK                                  0x40
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP8_SHFT                                     6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP7_BMSK                                  0x20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP7_SHFT                                     5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP6_BMSK                                  0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP6_SHFT                                     4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP5_BMSK                                   0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP5_SHFT                                     3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP4_BMSK                                   0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP4_SHFT                                     2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP3_BMSK                                   0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP3_SHFT                                     1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP2_BMSK                                   0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP2_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8dc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8dc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_NSP_ACD_DVM_VAL0_7_0_BMSK                                   0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_NSP_ACD_DVM_VAL0_7_0_SHFT                                           24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_NSP_ACD_DVM_ENABLE_BMSK                                       0xff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_NSP_ACD_DVM_ENABLE_SHFT                                             15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_TSENS2_BASE1_BMSK                                               0x7fe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_TSENS2_BASE1_SHFT                                                    5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_TSENS2_BASE0_9_5_BMSK                                             0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_TSENS2_BASE0_9_5_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8e0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8e0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_NSP_ACD_DVM_VAL1_15_0_BMSK                                  0xffff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_NSP_ACD_DVM_VAL1_15_0_SHFT                                          16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_NSP_ACD_DVM_VAL0_23_8_BMSK                                      0xffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_NSP_ACD_DVM_VAL0_23_8_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8e4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8e4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_NSP_ACD_DVM_VAL2_BMSK                                       0xffffff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_NSP_ACD_DVM_VAL2_SHFT                                                8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_NSP_ACD_DVM_VAL1_23_16_BMSK                                       0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_NSP_ACD_DVM_VAL1_23_16_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8e8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8e8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_NSP_ACD_DVM_VAL4_7_0_BMSK                                   0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_NSP_ACD_DVM_VAL4_7_0_SHFT                                           24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_NSP_ACD_DVM_VAL3_BMSK                                         0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_NSP_ACD_DVM_VAL3_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8ec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8ec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_NSP_ACD_DVM_VAL5_15_0_BMSK                                  0xffff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_NSP_ACD_DVM_VAL5_15_0_SHFT                                          16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_NSP_ACD_DVM_VAL4_23_8_BMSK                                      0xffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_NSP_ACD_DVM_VAL4_23_8_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8f0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8f0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_NSP_ACD_DVM_VAL6_BMSK                                       0xffffff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_NSP_ACD_DVM_VAL6_SHFT                                                8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_NSP_ACD_DVM_VAL5_23_16_BMSK                                       0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_NSP_ACD_DVM_VAL5_23_16_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8f4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8f4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_DDRSS_EW_FUSE_2_0_BMSK                                      0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_DDRSS_EW_FUSE_2_0_SHFT                                              31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_DDRSS_EW_FUSE_1_BMSK                                        0x7f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_DDRSS_EW_FUSE_1_SHFT                                                24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_NSP_ACD_DVM_VAL7_BMSK                                         0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_NSP_ACD_DVM_VAL7_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8f8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8f8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH1CA_PNTUNE_RT_0_BMSK                                0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH1CA_PNTUNE_RT_0_SHFT                                        31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ1_PNTUNE_RT_BMSK                                 0x60000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ1_PNTUNE_RT_SHFT                                         29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ0_PNTUNE_RT_BMSK                                 0x18000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ0_PNTUNE_RT_SHFT                                         27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0CA_PNTUNE_RT_BMSK                                   0x6000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0CA_PNTUNE_RT_SHFT                                          25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_TP_REV_CTRL_BMSK                                       0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_TP_REV_CTRL_SHFT                                              20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_2_BMSK                                           0xfe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_2_SHFT                                                13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_1_BMSK                                            0x1fc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_1_SHFT                                                 6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EW_FUSE_2_6_1_BMSK                                          0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EW_FUSE_2_6_1_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8fc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8fc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CALIBRATION_2751_BMSK                                       0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CALIBRATION_2751_SHFT                                               31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH2CA_PNTUNE_HT_BMSK                                  0x60000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH2CA_PNTUNE_HT_SHFT                                          29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1DQ1_PNTUNE_HT_BMSK                                 0x18000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1DQ1_PNTUNE_HT_SHFT                                         27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1DQ0_PNTUNE_HT_BMSK                                  0x6000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1DQ0_PNTUNE_HT_SHFT                                         25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1CA_PNTUNE_HT_BMSK                                   0x1800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1CA_PNTUNE_HT_SHFT                                          23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH0DQ1_PNTUNE_HT_BMSK                                   0x600000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH0DQ1_PNTUNE_HT_SHFT                                         21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH0DQ0_PNTUNE_HT_BMSK                                   0x180000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH0DQ0_PNTUNE_HT_SHFT                                         19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH0CA_PNTUNE_HT_BMSK                                     0x60000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH0CA_PNTUNE_HT_SHFT                                          17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH3DQ1_PNTUNE_RT_BMSK                                    0x18000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH3DQ1_PNTUNE_RT_SHFT                                         15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH3DQ0_PNTUNE_RT_BMSK                                     0x6000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH3DQ0_PNTUNE_RT_SHFT                                         13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH3CA_PNTUNE_RT_BMSK                                      0x1800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH3CA_PNTUNE_RT_SHFT                                          11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH2DQ1_PNTUNE_RT_BMSK                                      0x600
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH2DQ1_PNTUNE_RT_SHFT                                          9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH2DQ0_PNTUNE_RT_BMSK                                      0x180
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH2DQ0_PNTUNE_RT_SHFT                                          7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH2CA_PNTUNE_RT_BMSK                                        0x60
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH2CA_PNTUNE_RT_SHFT                                           5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1DQ1_PNTUNE_RT_BMSK                                       0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1DQ1_PNTUNE_RT_SHFT                                          3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1DQ0_PNTUNE_RT_BMSK                                        0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1DQ0_PNTUNE_RT_SHFT                                          1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1CA_PNTUNE_RT_1_BMSK                                       0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDRSS_CH1CA_PNTUNE_RT_1_SHFT                                         0


#endif /* __CPR_FUSES_HWIO_H__ */
