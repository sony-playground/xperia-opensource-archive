#ifndef __CPR_FUSES_HWIO_H__
#define __CPR_FUSES_HWIO_H__
/*
===========================================================================
*/
/**
    @file cpr_fuses_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM4450 (Clarence) [clarence_v1.0_p3q3r41_MTO]
 
    This file contains HWIO register definitions for the following modules:
        FUSE_CONTROLLER_SW_RANGE4

    'Include' filters applied: CALIBRATION[FUSE_CONTROLLER_SW_RANGE4] 

    Generation parameters: 
    { 'filename': 'cpr_fuses_hwio.h',
      'generator': 'ciomacros',
      'header': '#include "msmhwiobase.h"',
      'module-filter-include': {'FUSE_CONTROLLER_SW_RANGE4': ['CALIBRATION']},
      'modules': ['FUSE_CONTROLLER_SW_RANGE4'],
      'output-attrs': True,
      'output-fvals': True,
      'output-offsets': True}

    Attribute definitions for the HWIO_*_ATTR macros are as follows:
        0x0: Command register
        0x1: Read-Only
        0x2: Write-Only
        0x3: Read/Write
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

    $Header: $
    $DateTime: $
    $Author: $

    ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: FUSE_CONTROLLER_SW_RANGE4
 *--------------------------------------------------------------------------*/

#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE                                                            (TMESS_BASE      + 0x021c8000)
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE                                                       0x1000
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_USED                                                       0xe14
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS                                                       0x021c8000

#define HWIO_CALIBRATION0_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd00)
#define HWIO_CALIBRATION0_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd00)
#define HWIO_CALIBRATION0_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION0_ATTR                                                                                     0x1
#define HWIO_CALIBRATION0_IN                    \
                in_dword(HWIO_CALIBRATION0_ADDR)
#define HWIO_CALIBRATION0_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION0_ADDR, m)
#define HWIO_CALIBRATION0_USB2PHY_RCAL_CODE_0_BMSK                                                    0x80000000
#define HWIO_CALIBRATION0_USB2PHY_RCAL_CODE_0_SHFT                                                            31
#define HWIO_CALIBRATION0_BANDGAP_TRIM_BMSK                                                           0x7f000000
#define HWIO_CALIBRATION0_BANDGAP_TRIM_SHFT                                                                   24
#define HWIO_CALIBRATION0_CALIBRATION_23_22_BMSK                                                        0xc00000
#define HWIO_CALIBRATION0_CALIBRATION_23_22_SHFT                                                              22
#define HWIO_CALIBRATION0_AOSS_TDOPCODE_BMSK                                                            0x380000
#define HWIO_CALIBRATION0_AOSS_TDOPCODE_SHFT                                                                  19
#define HWIO_CALIBRATION0_AOSS_RDOPCODE_BMSK                                                             0x70000
#define HWIO_CALIBRATION0_AOSS_RDOPCODE_SHFT                                                                  16
#define HWIO_CALIBRATION0_REFGEN0_BGV_TRIM_BMSK                                                           0xff00
#define HWIO_CALIBRATION0_REFGEN0_BGV_TRIM_SHFT                                                                8
#define HWIO_CALIBRATION0_REFGEN1_BGV_TRIM_BMSK                                                             0xff
#define HWIO_CALIBRATION0_REFGEN1_BGV_TRIM_SHFT                                                                0

#define HWIO_CALIBRATION1_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd04)
#define HWIO_CALIBRATION1_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd04)
#define HWIO_CALIBRATION1_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION1_ATTR                                                                                     0x1
#define HWIO_CALIBRATION1_IN                    \
                in_dword(HWIO_CALIBRATION1_ADDR)
#define HWIO_CALIBRATION1_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION1_ADDR, m)
#define HWIO_CALIBRATION1_AOSS_N1_12_0_BMSK                                                           0xfff80000
#define HWIO_CALIBRATION1_AOSS_N1_12_0_SHFT                                                                   19
#define HWIO_CALIBRATION1_AOSS_K_BMSK                                                                    0x7fff8
#define HWIO_CALIBRATION1_AOSS_K_SHFT                                                                          3
#define HWIO_CALIBRATION1_USB2PHY_RCAL_CODE_3_1_BMSK                                                         0x7
#define HWIO_CALIBRATION1_USB2PHY_RCAL_CODE_3_1_SHFT                                                           0

#define HWIO_CALIBRATION2_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd08)
#define HWIO_CALIBRATION2_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd08)
#define HWIO_CALIBRATION2_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION2_ATTR                                                                                     0x1
#define HWIO_CALIBRATION2_IN                    \
                in_dword(HWIO_CALIBRATION2_ADDR)
#define HWIO_CALIBRATION2_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION2_ADDR, m)
#define HWIO_CALIBRATION2_OPAMP_FUSE_CPURAIL_CPU6_FT_3_0_BMSK                                         0xf0000000
#define HWIO_CALIBRATION2_OPAMP_FUSE_CPURAIL_CPU6_FT_3_0_SHFT                                                 28
#define HWIO_CALIBRATION2_FACTOR_FUSE_CPURAIL_BMSK                                                     0xf800000
#define HWIO_CALIBRATION2_FACTOR_FUSE_CPURAIL_SHFT                                                            23
#define HWIO_CALIBRATION2_AOSS_P1_BMSK                                                                  0x7fffe0
#define HWIO_CALIBRATION2_AOSS_P1_SHFT                                                                         5
#define HWIO_CALIBRATION2_AOSS_N1_17_13_BMSK                                                                0x1f
#define HWIO_CALIBRATION2_AOSS_N1_17_13_SHFT                                                                   0

#define HWIO_CALIBRATION3_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd0c)
#define HWIO_CALIBRATION3_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd0c)
#define HWIO_CALIBRATION3_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION3_ATTR                                                                                     0x1
#define HWIO_CALIBRATION3_IN                    \
                in_dword(HWIO_CALIBRATION3_ADDR)
#define HWIO_CALIBRATION3_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION3_ADDR, m)
#define HWIO_CALIBRATION3_CALIBRATION_127_124_BMSK                                                    0xf0000000
#define HWIO_CALIBRATION3_CALIBRATION_127_124_SHFT                                                            28
#define HWIO_CALIBRATION3_ROCOUNT_FUSE_CPURAIL_BMSK                                                    0xff00000
#define HWIO_CALIBRATION3_ROCOUNT_FUSE_CPURAIL_SHFT                                                           20
#define HWIO_CALIBRATION3_OPAMP_FUSE_CPURAIL_CPU7_WS_BMSK                                                0xfc000
#define HWIO_CALIBRATION3_OPAMP_FUSE_CPURAIL_CPU7_WS_SHFT                                                     14
#define HWIO_CALIBRATION3_OPAMP_FUSE_CPURAIL_CPU7_FT_BMSK                                                 0x3f00
#define HWIO_CALIBRATION3_OPAMP_FUSE_CPURAIL_CPU7_FT_SHFT                                                      8
#define HWIO_CALIBRATION3_OPAMP_FUSE_CPURAIL_CPU6_WS_BMSK                                                   0xfc
#define HWIO_CALIBRATION3_OPAMP_FUSE_CPURAIL_CPU6_WS_SHFT                                                      2
#define HWIO_CALIBRATION3_OPAMP_FUSE_CPURAIL_CPU6_FT_5_4_BMSK                                                0x3
#define HWIO_CALIBRATION3_OPAMP_FUSE_CPURAIL_CPU6_FT_5_4_SHFT                                                  0

#define HWIO_CALIBRATION4_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd10)
#define HWIO_CALIBRATION4_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd10)
#define HWIO_CALIBRATION4_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION4_ATTR                                                                                     0x1
#define HWIO_CALIBRATION4_IN                    \
                in_dword(HWIO_CALIBRATION4_ADDR)
#define HWIO_CALIBRATION4_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION4_ADDR, m)
#define HWIO_CALIBRATION4_DDR_FUSE_MED_3_3_0_BMSK                                                     0xf0000000
#define HWIO_CALIBRATION4_DDR_FUSE_MED_3_3_0_SHFT                                                             28
#define HWIO_CALIBRATION4_DDR_FUSE_MED_2_BMSK                                                          0xf800000
#define HWIO_CALIBRATION4_DDR_FUSE_MED_2_SHFT                                                                 23
#define HWIO_CALIBRATION4_DDR_FUSE_MED_1_BMSK                                                           0x7c0000
#define HWIO_CALIBRATION4_DDR_FUSE_MED_1_SHFT                                                                 18
#define HWIO_CALIBRATION4_DDR_FUSE_BIG3_BMSK                                                             0x3f000
#define HWIO_CALIBRATION4_DDR_FUSE_BIG3_SHFT                                                                  12
#define HWIO_CALIBRATION4_DDR_FUSE_BIG2_BMSK                                                               0xfc0
#define HWIO_CALIBRATION4_DDR_FUSE_BIG2_SHFT                                                                   6
#define HWIO_CALIBRATION4_DDR_FUSE_BIG1_BMSK                                                                0x3f
#define HWIO_CALIBRATION4_DDR_FUSE_BIG1_SHFT                                                                   0

#define HWIO_CALIBRATION5_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd14)
#define HWIO_CALIBRATION5_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd14)
#define HWIO_CALIBRATION5_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION5_ATTR                                                                                     0x1
#define HWIO_CALIBRATION5_IN                    \
                in_dword(HWIO_CALIBRATION5_ADDR)
#define HWIO_CALIBRATION5_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION5_ADDR, m)
#define HWIO_CALIBRATION5_CALIBRATION_191_167_BMSK                                                    0xffffff80
#define HWIO_CALIBRATION5_CALIBRATION_191_167_SHFT                                                             7
#define HWIO_CALIBRATION5_DDR_FUSE_SMALL_3_BMSK                                                             0x60
#define HWIO_CALIBRATION5_DDR_FUSE_SMALL_3_SHFT                                                                5
#define HWIO_CALIBRATION5_DDR_FUSE_SMALL_2_BMSK                                                             0x18
#define HWIO_CALIBRATION5_DDR_FUSE_SMALL_2_SHFT                                                                3
#define HWIO_CALIBRATION5_DDR_FUSE_SMALL_1_BMSK                                                              0x6
#define HWIO_CALIBRATION5_DDR_FUSE_SMALL_1_SHFT                                                                1
#define HWIO_CALIBRATION5_DDR_FUSE_MED_3_4_BMSK                                                              0x1
#define HWIO_CALIBRATION5_DDR_FUSE_MED_3_4_SHFT                                                                0

#define HWIO_CALIBRATION6_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd18)
#define HWIO_CALIBRATION6_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd18)
#define HWIO_CALIBRATION6_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION6_ATTR                                                                                     0x1
#define HWIO_CALIBRATION6_IN                    \
                in_dword(HWIO_CALIBRATION6_ADDR)
#define HWIO_CALIBRATION6_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION6_ADDR, m)
#define HWIO_CALIBRATION6_CALIBRATION_223_192_BMSK                                                    0xffffffff
#define HWIO_CALIBRATION6_CALIBRATION_223_192_SHFT                                                             0

#define HWIO_CALIBRATION7_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd1c)
#define HWIO_CALIBRATION7_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd1c)
#define HWIO_CALIBRATION7_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION7_ATTR                                                                                     0x1
#define HWIO_CALIBRATION7_IN                    \
                in_dword(HWIO_CALIBRATION7_ADDR)
#define HWIO_CALIBRATION7_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION7_ADDR, m)
#define HWIO_CALIBRATION7_CALIBRATION_255_224_BMSK                                                    0xffffffff
#define HWIO_CALIBRATION7_CALIBRATION_255_224_SHFT                                                             0

#define HWIO_CALIBRATION8_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd20)
#define HWIO_CALIBRATION8_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd20)
#define HWIO_CALIBRATION8_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION8_ATTR                                                                                     0x1
#define HWIO_CALIBRATION8_IN                    \
                in_dword(HWIO_CALIBRATION8_ADDR)
#define HWIO_CALIBRATION8_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION8_ADDR, m)
#define HWIO_CALIBRATION8_CALIBRATION_287_256_BMSK                                                    0xffffffff
#define HWIO_CALIBRATION8_CALIBRATION_287_256_SHFT                                                             0

#define HWIO_CALIBRATION9_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd24)
#define HWIO_CALIBRATION9_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd24)
#define HWIO_CALIBRATION9_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION9_ATTR                                                                                     0x1
#define HWIO_CALIBRATION9_IN                    \
                in_dword(HWIO_CALIBRATION9_ADDR)
#define HWIO_CALIBRATION9_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION9_ADDR, m)
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_OFFSET_TURL1_3_0_BMSK                                        0xf0000000
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_OFFSET_TURL1_3_0_SHFT                                                28
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_TUR_BMSK                                                      0xfc00000
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_TUR_SHFT                                                             22
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_TURL1_BMSK                                                     0x3f0000
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_TURL1_SHFT                                                           16
#define HWIO_CALIBRATION9_CALIBRATION_303_288_BMSK                                                        0xffff
#define HWIO_CALIBRATION9_CALIBRATION_303_288_SHFT                                                             0

#define HWIO_CALIBRATION10_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd28)
#define HWIO_CALIBRATION10_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd28)
#define HWIO_CALIBRATION10_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION10_ATTR                                                                                    0x1
#define HWIO_CALIBRATION10_IN                    \
                in_dword(HWIO_CALIBRATION10_ADDR)
#define HWIO_CALIBRATION10_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION10_ADDR, m)
#define HWIO_CALIBRATION10_CPR4_TARG_VOLT_OFFSET_TURL1_0_BMSK                                         0x80000000
#define HWIO_CALIBRATION10_CPR4_TARG_VOLT_OFFSET_TURL1_0_SHFT                                                 31
#define HWIO_CALIBRATION10_CPR4_TARG_VOLT_SVS_BMSK                                                    0x7e000000
#define HWIO_CALIBRATION10_CPR4_TARG_VOLT_SVS_SHFT                                                            25
#define HWIO_CALIBRATION10_CPR4_TARG_VOLT_TURL1_BMSK                                                   0x1f80000
#define HWIO_CALIBRATION10_CPR4_TARG_VOLT_TURL1_SHFT                                                          19
#define HWIO_CALIBRATION10_CPR3_TARG_VOLT_SVS_BMSK                                                       0x7e000
#define HWIO_CALIBRATION10_CPR3_TARG_VOLT_SVS_SHFT                                                            13
#define HWIO_CALIBRATION10_CPR3_TARG_VOLT_TUR_BMSK                                                        0x1f80
#define HWIO_CALIBRATION10_CPR3_TARG_VOLT_TUR_SHFT                                                             7
#define HWIO_CALIBRATION10_CPR1_TARG_VOLT_NOML1_BMSK                                                        0x7e
#define HWIO_CALIBRATION10_CPR1_TARG_VOLT_NOML1_SHFT                                                           1
#define HWIO_CALIBRATION10_CPR0_TARG_VOLT_OFFSET_TURL1_4_BMSK                                                0x1
#define HWIO_CALIBRATION10_CPR0_TARG_VOLT_OFFSET_TURL1_4_SHFT                                                  0

#define HWIO_CALIBRATION11_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd2c)
#define HWIO_CALIBRATION11_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd2c)
#define HWIO_CALIBRATION11_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION11_ATTR                                                                                    0x1
#define HWIO_CALIBRATION11_IN                    \
                in_dword(HWIO_CALIBRATION11_ADDR)
#define HWIO_CALIBRATION11_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION11_ADDR, m)
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_SVS2_2_0_BMSK                                        0xe0000000
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_SVS2_2_0_SHFT                                                29
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_SVS_BMSK                                             0x1f000000
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_SVS_SHFT                                                     24
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_SVSL1_BMSK                                             0xf80000
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_SVSL1_SHFT                                                   19
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_NOM_BMSK                                                0x7c000
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_NOM_SHFT                                                     14
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_NOML1_BMSK                                               0x3e00
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_NOML1_SHFT                                                    9
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_TUR_BMSK                                                  0x1f0
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_TUR_SHFT                                                      4
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_TURL1_4_1_BMSK                                              0xf
#define HWIO_CALIBRATION11_CPR4_TARG_VOLT_OFFSET_TURL1_4_1_SHFT                                                0

#define HWIO_CALIBRATION12_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd30)
#define HWIO_CALIBRATION12_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd30)
#define HWIO_CALIBRATION12_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION12_ATTR                                                                                    0x1
#define HWIO_CALIBRATION12_IN                    \
                in_dword(HWIO_CALIBRATION12_ADDR)
#define HWIO_CALIBRATION12_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION12_ADDR, m)
#define HWIO_CALIBRATION12_CPR0_TARG_VOLT_NOM_0_BMSK                                                  0x80000000
#define HWIO_CALIBRATION12_CPR0_TARG_VOLT_NOM_0_SHFT                                                          31
#define HWIO_CALIBRATION12_CALIBRATION_414_408_BMSK                                                   0x7f000000
#define HWIO_CALIBRATION12_CALIBRATION_414_408_SHFT                                                           24
#define HWIO_CALIBRATION12_CPR6_TARG_VOLT_OFFSET_TUR_BMSK                                               0xf80000
#define HWIO_CALIBRATION12_CPR6_TARG_VOLT_OFFSET_TUR_SHFT                                                     19
#define HWIO_CALIBRATION12_CPR6_TARG_VOLT_SVS3_BMSK                                                      0x7e000
#define HWIO_CALIBRATION12_CPR6_TARG_VOLT_SVS3_SHFT                                                           13
#define HWIO_CALIBRATION12_CPR5_TARG_VOLT_SVSL1_BMSK                                                      0x1f80
#define HWIO_CALIBRATION12_CPR5_TARG_VOLT_SVSL1_SHFT                                                           7
#define HWIO_CALIBRATION12_CPR4_TARG_VOLT_OFFSET_SVS3_BMSK                                                  0x7c
#define HWIO_CALIBRATION12_CPR4_TARG_VOLT_OFFSET_SVS3_SHFT                                                     2
#define HWIO_CALIBRATION12_CPR4_TARG_VOLT_OFFSET_SVS2_4_3_BMSK                                               0x3
#define HWIO_CALIBRATION12_CPR4_TARG_VOLT_OFFSET_SVS2_4_3_SHFT                                                 0

#define HWIO_CALIBRATION13_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd34)
#define HWIO_CALIBRATION13_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd34)
#define HWIO_CALIBRATION13_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION13_ATTR                                                                                    0x1
#define HWIO_CALIBRATION13_IN                    \
                in_dword(HWIO_CALIBRATION13_ADDR)
#define HWIO_CALIBRATION13_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION13_ADDR, m)
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_OFFSET_NOML1_BMSK                                           0xf8000000
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_OFFSET_NOML1_SHFT                                                   27
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_OFFSET_TUR_BMSK                                              0x7c00000
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_OFFSET_TUR_SHFT                                                     22
#define HWIO_CALIBRATION13_CALIBRATION_437_433_BMSK                                                     0x3e0000
#define HWIO_CALIBRATION13_CALIBRATION_437_433_SHFT                                                           17
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_SVS2_BMSK                                                      0x1f800
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_SVS2_SHFT                                                           11
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_SVS_BMSK                                                         0x7e0
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_SVS_SHFT                                                             5
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_NOM_5_1_BMSK                                                      0x1f
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_NOM_5_1_SHFT                                                         0

#define HWIO_CALIBRATION14_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd38)
#define HWIO_CALIBRATION14_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd38)
#define HWIO_CALIBRATION14_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION14_ATTR                                                                                    0x1
#define HWIO_CALIBRATION14_IN                    \
                in_dword(HWIO_CALIBRATION14_ADDR)
#define HWIO_CALIBRATION14_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION14_ADDR, m)
#define HWIO_CALIBRATION14_CALIBRATION_479_476_BMSK                                                   0xf0000000
#define HWIO_CALIBRATION14_CALIBRATION_479_476_SHFT                                                           28
#define HWIO_CALIBRATION14_CPR0_AGING_BMSK                                                             0xff00000
#define HWIO_CALIBRATION14_CPR0_AGING_SHFT                                                                    20
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_SVS2_BMSK                                               0xf8000
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_SVS2_SHFT                                                    15
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_SVS_BMSK                                                 0x7c00
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_SVS_SHFT                                                     10
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_SVSL1_BMSK                                                0x3e0
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_SVSL1_SHFT                                                    5
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_NOM_BMSK                                                   0x1f
#define HWIO_CALIBRATION14_CPR0_TARG_VOLT_OFFSET_NOM_SHFT                                                      0

#define HWIO_CALIBRATION15_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd3c)
#define HWIO_CALIBRATION15_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd3c)
#define HWIO_CALIBRATION15_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION15_ATTR                                                                                    0x1
#define HWIO_CALIBRATION15_IN                    \
                in_dword(HWIO_CALIBRATION15_ADDR)
#define HWIO_CALIBRATION15_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION15_ADDR, m)
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_OFFSET_NOM_1_0_BMSK                                         0xc0000000
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_OFFSET_NOM_1_0_SHFT                                                 30
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_OFFSET_NOML1_BMSK                                           0x3e000000
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_OFFSET_NOML1_SHFT                                                   25
#define HWIO_CALIBRATION15_CALIBRATION_504_500_BMSK                                                    0x1f00000
#define HWIO_CALIBRATION15_CALIBRATION_504_500_SHFT                                                           20
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_SVS3_BMSK                                                      0xfc000
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_SVS3_SHFT                                                           14
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_SVS_BMSK                                                        0x3f00
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_SVS_SHFT                                                             8
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_NOM_BMSK                                                          0xfc
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_NOM_SHFT                                                             2
#define HWIO_CALIBRATION15_CALIBRATION_481_480_BMSK                                                          0x3
#define HWIO_CALIBRATION15_CALIBRATION_481_480_SHFT                                                            0

#define HWIO_CALIBRATION16_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd40)
#define HWIO_CALIBRATION16_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd40)
#define HWIO_CALIBRATION16_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION16_ATTR                                                                                    0x1
#define HWIO_CALIBRATION16_IN                    \
                in_dword(HWIO_CALIBRATION16_ADDR)
#define HWIO_CALIBRATION16_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION16_ADDR, m)
#define HWIO_CALIBRATION16_CALIBRATION_543_BMSK                                                       0x80000000
#define HWIO_CALIBRATION16_CALIBRATION_543_SHFT                                                               31
#define HWIO_CALIBRATION16_CPR1_AGING_BMSK                                                            0x7f800000
#define HWIO_CALIBRATION16_CPR1_AGING_SHFT                                                                    23
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_SVS3_BMSK                                              0x7c0000
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_SVS3_SHFT                                                    18
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_SVS2_BMSK                                               0x3e000
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_SVS2_SHFT                                                    13
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_SVS_BMSK                                                 0x1f00
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_SVS_SHFT                                                      8
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_SVSL1_BMSK                                                 0xf8
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_SVSL1_SHFT                                                    3
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_NOM_4_2_BMSK                                                0x7
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_NOM_4_2_SHFT                                                  0

#define HWIO_CALIBRATION17_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd44)
#define HWIO_CALIBRATION17_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd44)
#define HWIO_CALIBRATION17_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION17_ATTR                                                                                    0x1
#define HWIO_CALIBRATION17_IN                    \
                in_dword(HWIO_CALIBRATION17_ADDR)
#define HWIO_CALIBRATION17_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION17_ADDR, m)
#define HWIO_CALIBRATION17_CALIBRATION_575_544_BMSK                                                   0xffffffff
#define HWIO_CALIBRATION17_CALIBRATION_575_544_SHFT                                                            0

#define HWIO_CALIBRATION18_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd48)
#define HWIO_CALIBRATION18_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd48)
#define HWIO_CALIBRATION18_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION18_ATTR                                                                                    0x1
#define HWIO_CALIBRATION18_IN                    \
                in_dword(HWIO_CALIBRATION18_ADDR)
#define HWIO_CALIBRATION18_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION18_ADDR, m)
#define HWIO_CALIBRATION18_CALIBRATION_607_576_BMSK                                                   0xffffffff
#define HWIO_CALIBRATION18_CALIBRATION_607_576_SHFT                                                            0

#define HWIO_CALIBRATION19_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd4c)
#define HWIO_CALIBRATION19_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd4c)
#define HWIO_CALIBRATION19_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION19_ATTR                                                                                    0x1
#define HWIO_CALIBRATION19_IN                    \
                in_dword(HWIO_CALIBRATION19_ADDR)
#define HWIO_CALIBRATION19_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION19_ADDR, m)
#define HWIO_CALIBRATION19_CPR5_TARG_VOLT_NOM_4_0_BMSK                                                0xf8000000
#define HWIO_CALIBRATION19_CPR5_TARG_VOLT_NOM_4_0_SHFT                                                        27
#define HWIO_CALIBRATION19_CPR5_TARG_VOLT_TUR_BMSK                                                     0x7e00000
#define HWIO_CALIBRATION19_CPR5_TARG_VOLT_TUR_SHFT                                                            21
#define HWIO_CALIBRATION19_CALIBRATION_628_623_BMSK                                                     0x1f8000
#define HWIO_CALIBRATION19_CALIBRATION_628_623_SHFT                                                           15
#define HWIO_CALIBRATION19_CPR4_TARG_VOLT_NOM_BMSK                                                        0x7e00
#define HWIO_CALIBRATION19_CPR4_TARG_VOLT_NOM_SHFT                                                             9
#define HWIO_CALIBRATION19_CPR4_TARG_VOLT_NOML1_BMSK                                                       0x1f8
#define HWIO_CALIBRATION19_CPR4_TARG_VOLT_NOML1_SHFT                                                           3
#define HWIO_CALIBRATION19_CALIBRATION_610_608_BMSK                                                          0x7
#define HWIO_CALIBRATION19_CALIBRATION_610_608_SHFT                                                            0

#define HWIO_CALIBRATION20_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd50)
#define HWIO_CALIBRATION20_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd50)
#define HWIO_CALIBRATION20_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION20_ATTR                                                                                    0x1
#define HWIO_CALIBRATION20_IN                    \
                in_dword(HWIO_CALIBRATION20_ADDR)
#define HWIO_CALIBRATION20_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION20_ADDR, m)
#define HWIO_CALIBRATION20_CALIBRATION_671_641_BMSK                                                   0xfffffffe
#define HWIO_CALIBRATION20_CALIBRATION_671_641_SHFT                                                            1
#define HWIO_CALIBRATION20_CPR5_TARG_VOLT_NOM_5_BMSK                                                         0x1
#define HWIO_CALIBRATION20_CPR5_TARG_VOLT_NOM_5_SHFT                                                           0

#define HWIO_CALIBRATION21_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd54)
#define HWIO_CALIBRATION21_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd54)
#define HWIO_CALIBRATION21_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION21_ATTR                                                                                    0x1
#define HWIO_CALIBRATION21_IN                    \
                in_dword(HWIO_CALIBRATION21_ADDR)
#define HWIO_CALIBRATION21_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION21_ADDR, m)
#define HWIO_CALIBRATION21_AON_AGING_1_0_BMSK                                                         0xc0000000
#define HWIO_CALIBRATION21_AON_AGING_1_0_SHFT                                                                 30
#define HWIO_CALIBRATION21_CALIBRATION_701_688_BMSK                                                   0x3fff0000
#define HWIO_CALIBRATION21_CALIBRATION_701_688_SHFT                                                           16
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_OFFSET_SVS3_BMSK                                                0xf800
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_OFFSET_SVS3_SHFT                                                    11
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_OFFSET_SVS2_BMSK                                                 0x7c0
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_OFFSET_SVS2_SHFT                                                     6
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_OFFSET_SVS_BMSK                                                   0x3e
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_OFFSET_SVS_SHFT                                                      1
#define HWIO_CALIBRATION21_CALIBRATION_672_BMSK                                                              0x1
#define HWIO_CALIBRATION21_CALIBRATION_672_SHFT                                                                0

#define HWIO_CALIBRATION22_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd58)
#define HWIO_CALIBRATION22_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd58)
#define HWIO_CALIBRATION22_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION22_ATTR                                                                                    0x1
#define HWIO_CALIBRATION22_IN                    \
                in_dword(HWIO_CALIBRATION22_ADDR)
#define HWIO_CALIBRATION22_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION22_ADDR, m)
#define HWIO_CALIBRATION22_CALIBRATION_735_731_BMSK                                                   0xf8000000
#define HWIO_CALIBRATION22_CALIBRATION_735_731_SHFT                                                           27
#define HWIO_CALIBRATION22_CPR6_TARG_VOLT_SVS_BMSK                                                     0x7e00000
#define HWIO_CALIBRATION22_CPR6_TARG_VOLT_SVS_SHFT                                                            21
#define HWIO_CALIBRATION22_CPR6_TARG_VOLT_NOM_BMSK                                                      0x1f8000
#define HWIO_CALIBRATION22_CPR6_TARG_VOLT_NOM_SHFT                                                            15
#define HWIO_CALIBRATION22_CPR6_TARG_VOLT_TUR_BMSK                                                        0x7e00
#define HWIO_CALIBRATION22_CPR6_TARG_VOLT_TUR_SHFT                                                             9
#define HWIO_CALIBRATION22_CPR_GLOBAL_RC_BMSK                                                              0x1c0
#define HWIO_CALIBRATION22_CPR_GLOBAL_RC_SHFT                                                                  6
#define HWIO_CALIBRATION22_AON_AGING_7_2_BMSK                                                               0x3f
#define HWIO_CALIBRATION22_AON_AGING_7_2_SHFT                                                                  0

#define HWIO_CALIBRATION23_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd5c)
#define HWIO_CALIBRATION23_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd5c)
#define HWIO_CALIBRATION23_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION23_ATTR                                                                                    0x1
#define HWIO_CALIBRATION23_IN                    \
                in_dword(HWIO_CALIBRATION23_ADDR)
#define HWIO_CALIBRATION23_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION23_ADDR, m)
#define HWIO_CALIBRATION23_CALIBRATION_767_736_BMSK                                                   0xffffffff
#define HWIO_CALIBRATION23_CALIBRATION_767_736_SHFT                                                            0

#define HWIO_CALIBRATION24_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd60)
#define HWIO_CALIBRATION24_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd60)
#define HWIO_CALIBRATION24_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION24_ATTR                                                                                    0x1
#define HWIO_CALIBRATION24_IN                    \
                in_dword(HWIO_CALIBRATION24_ADDR)
#define HWIO_CALIBRATION24_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION24_ADDR, m)
#define HWIO_CALIBRATION24_CPR6_AGING_6_0_BMSK                                                        0xfe000000
#define HWIO_CALIBRATION24_CPR6_AGING_6_0_SHFT                                                                25
#define HWIO_CALIBRATION24_CALIBRATION_792_768_BMSK                                                    0x1ffffff
#define HWIO_CALIBRATION24_CALIBRATION_792_768_SHFT                                                            0

#define HWIO_CALIBRATION25_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd64)
#define HWIO_CALIBRATION25_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd64)
#define HWIO_CALIBRATION25_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION25_ATTR                                                                                    0x1
#define HWIO_CALIBRATION25_IN                    \
                in_dword(HWIO_CALIBRATION25_ADDR)
#define HWIO_CALIBRATION25_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION25_ADDR, m)
#define HWIO_CALIBRATION25_CALIBRATION_831_801_BMSK                                                   0xfffffffe
#define HWIO_CALIBRATION25_CALIBRATION_831_801_SHFT                                                            1
#define HWIO_CALIBRATION25_CPR6_AGING_7_BMSK                                                                 0x1
#define HWIO_CALIBRATION25_CPR6_AGING_7_SHFT                                                                   0

#define HWIO_CALIBRATION26_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd68)
#define HWIO_CALIBRATION26_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd68)
#define HWIO_CALIBRATION26_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION26_ATTR                                                                                    0x1
#define HWIO_CALIBRATION26_IN                    \
                in_dword(HWIO_CALIBRATION26_ADDR)
#define HWIO_CALIBRATION26_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION26_ADDR, m)
#define HWIO_CALIBRATION26_CALIBRATION_863_832_BMSK                                                   0xffffffff
#define HWIO_CALIBRATION26_CALIBRATION_863_832_SHFT                                                            0

#define HWIO_CALIBRATION27_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd6c)
#define HWIO_CALIBRATION27_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd6c)
#define HWIO_CALIBRATION27_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION27_ATTR                                                                                    0x1
#define HWIO_CALIBRATION27_IN                    \
                in_dword(HWIO_CALIBRATION27_ADDR)
#define HWIO_CALIBRATION27_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION27_ADDR, m)
#define HWIO_CALIBRATION27_CALIBRATION_895_864_BMSK                                                   0xffffffff
#define HWIO_CALIBRATION27_CALIBRATION_895_864_SHFT                                                            0

#define HWIO_CALIBRATION28_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd70)
#define HWIO_CALIBRATION28_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd70)
#define HWIO_CALIBRATION28_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION28_ATTR                                                                                    0x1
#define HWIO_CALIBRATION28_IN                    \
                in_dword(HWIO_CALIBRATION28_ADDR)
#define HWIO_CALIBRATION28_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION28_ADDR, m)
#define HWIO_CALIBRATION28_CALIBRATION_927_896_BMSK                                                   0xffffffff
#define HWIO_CALIBRATION28_CALIBRATION_927_896_SHFT                                                            0

#define HWIO_CALIBRATION29_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd74)
#define HWIO_CALIBRATION29_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd74)
#define HWIO_CALIBRATION29_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION29_ATTR                                                                                    0x1
#define HWIO_CALIBRATION29_IN                    \
                in_dword(HWIO_CALIBRATION29_ADDR)
#define HWIO_CALIBRATION29_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION29_ADDR, m)
#define HWIO_CALIBRATION29_CALIBRATION_959_928_BMSK                                                   0xffffffff
#define HWIO_CALIBRATION29_CALIBRATION_959_928_SHFT                                                            0

#define HWIO_CALIBRATION30_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd78)
#define HWIO_CALIBRATION30_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd78)
#define HWIO_CALIBRATION30_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION30_ATTR                                                                                    0x1
#define HWIO_CALIBRATION30_IN                    \
                in_dword(HWIO_CALIBRATION30_ADDR)
#define HWIO_CALIBRATION30_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION30_ADDR, m)
#define HWIO_CALIBRATION30_CPR_RESERVED_9_0_BMSK                                                      0xffc00000
#define HWIO_CALIBRATION30_CPR_RESERVED_9_0_SHFT                                                              22
#define HWIO_CALIBRATION30_CPR_APC0_MODE_DISABLE_BMSK                                                   0x380000
#define HWIO_CALIBRATION30_CPR_APC0_MODE_DISABLE_SHFT                                                         19
#define HWIO_CALIBRATION30_CALIBRATION_978_976_BMSK                                                      0x70000
#define HWIO_CALIBRATION30_CALIBRATION_978_976_SHFT                                                           16
#define HWIO_CALIBRATION30_CPR_LPIMX_MODE_DISABLE_BMSK                                                    0xe000
#define HWIO_CALIBRATION30_CPR_LPIMX_MODE_DISABLE_SHFT                                                        13
#define HWIO_CALIBRATION30_CPR_MX_MODE_DISABLE_BMSK                                                       0x1c00
#define HWIO_CALIBRATION30_CPR_MX_MODE_DISABLE_SHFT                                                           10
#define HWIO_CALIBRATION30_CPR_MSS_MODE_DISABLE_BMSK                                                       0x380
#define HWIO_CALIBRATION30_CPR_MSS_MODE_DISABLE_SHFT                                                           7
#define HWIO_CALIBRATION30_CPR_CX_MODE_DISABLE_BMSK                                                         0x70
#define HWIO_CALIBRATION30_CPR_CX_MODE_DISABLE_SHFT                                                            4
#define HWIO_CALIBRATION30_CPR_LOCAL_RC_BMSK                                                                 0xe
#define HWIO_CALIBRATION30_CPR_LOCAL_RC_SHFT                                                                   1
#define HWIO_CALIBRATION30_CALIBRATION_960_BMSK                                                              0x1
#define HWIO_CALIBRATION30_CALIBRATION_960_SHFT                                                                0

#define HWIO_CALIBRATION31_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd7c)
#define HWIO_CALIBRATION31_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd7c)
#define HWIO_CALIBRATION31_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION31_ATTR                                                                                    0x1
#define HWIO_CALIBRATION31_IN                    \
                in_dword(HWIO_CALIBRATION31_ADDR)
#define HWIO_CALIBRATION31_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION31_ADDR, m)
#define HWIO_CALIBRATION31_CPR_RESERVED_41_10_BMSK                                                    0xffffffff
#define HWIO_CALIBRATION31_CPR_RESERVED_41_10_SHFT                                                             0

#define HWIO_CALIBRATION32_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd80)
#define HWIO_CALIBRATION32_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd80)
#define HWIO_CALIBRATION32_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION32_ATTR                                                                                    0x1
#define HWIO_CALIBRATION32_IN                    \
                in_dword(HWIO_CALIBRATION32_ADDR)
#define HWIO_CALIBRATION32_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION32_ADDR, m)
#define HWIO_CALIBRATION32_CALIBRATION_1055_1044_BMSK                                                 0xfff00000
#define HWIO_CALIBRATION32_CALIBRATION_1055_1044_SHFT                                                         20
#define HWIO_CALIBRATION32_CPR9_TARG_VOLT_SVS_BMSK                                                       0xfc000
#define HWIO_CALIBRATION32_CPR9_TARG_VOLT_SVS_SHFT                                                            14
#define HWIO_CALIBRATION32_CPR9_TARG_VOLT_SVSL1_BMSK                                                      0x3f00
#define HWIO_CALIBRATION32_CPR9_TARG_VOLT_SVSL1_SHFT                                                           8
#define HWIO_CALIBRATION32_CPR_RESERVED_49_42_BMSK                                                          0xff
#define HWIO_CALIBRATION32_CPR_RESERVED_49_42_SHFT                                                             0

#define HWIO_CALIBRATION33_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd84)
#define HWIO_CALIBRATION33_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd84)
#define HWIO_CALIBRATION33_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION33_ATTR                                                                                    0x1
#define HWIO_CALIBRATION33_IN                    \
                in_dword(HWIO_CALIBRATION33_ADDR)
#define HWIO_CALIBRATION33_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION33_ADDR, m)
#define HWIO_CALIBRATION33_CPR10_TARG_VOLT_NOM_0_BMSK                                                 0x80000000
#define HWIO_CALIBRATION33_CPR10_TARG_VOLT_NOM_0_SHFT                                                         31
#define HWIO_CALIBRATION33_CPR10_TARG_VOLT_TURL1_BMSK                                                 0x7e000000
#define HWIO_CALIBRATION33_CPR10_TARG_VOLT_TURL1_SHFT                                                         25
#define HWIO_CALIBRATION33_CPR6_TARG_VOLT_OFFSET_SVS3_BMSK                                             0x1f00000
#define HWIO_CALIBRATION33_CPR6_TARG_VOLT_OFFSET_SVS3_SHFT                                                    20
#define HWIO_CALIBRATION33_CPR6_TARG_VOLT_OFFSET_SVS2_BMSK                                               0xf8000
#define HWIO_CALIBRATION33_CPR6_TARG_VOLT_OFFSET_SVS2_SHFT                                                    15
#define HWIO_CALIBRATION33_CPR6_TARG_VOLT_OFFSET_SVS_BMSK                                                 0x7c00
#define HWIO_CALIBRATION33_CPR6_TARG_VOLT_OFFSET_SVS_SHFT                                                     10
#define HWIO_CALIBRATION33_CPR6_TARG_VOLT_OFFSET_SVSL1_BMSK                                                0x3e0
#define HWIO_CALIBRATION33_CPR6_TARG_VOLT_OFFSET_SVSL1_SHFT                                                    5
#define HWIO_CALIBRATION33_CPR6_TARG_VOLT_OFFSET_NOM_BMSK                                                   0x1f
#define HWIO_CALIBRATION33_CPR6_TARG_VOLT_OFFSET_NOM_SHFT                                                      0

#define HWIO_CALIBRATION34_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd88)
#define HWIO_CALIBRATION34_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd88)
#define HWIO_CALIBRATION34_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION34_ATTR                                                                                    0x1
#define HWIO_CALIBRATION34_IN                    \
                in_dword(HWIO_CALIBRATION34_ADDR)
#define HWIO_CALIBRATION34_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION34_ADDR, m)
#define HWIO_CALIBRATION34_CPR10_TURL1_QUOT_MIN_6_0_BMSK                                              0xfe000000
#define HWIO_CALIBRATION34_CPR10_TURL1_QUOT_MIN_6_0_SHFT                                                      25
#define HWIO_CALIBRATION34_CPR10_QUOT_OFFSET_BMSK                                                      0x1fe0000
#define HWIO_CALIBRATION34_CPR10_QUOT_OFFSET_SHFT                                                             17
#define HWIO_CALIBRATION34_CPR10_TARG_VOLT_SVS2_BMSK                                                     0x1f800
#define HWIO_CALIBRATION34_CPR10_TARG_VOLT_SVS2_SHFT                                                          11
#define HWIO_CALIBRATION34_CPR10_TARG_VOLT_SVSL1_BMSK                                                      0x7e0
#define HWIO_CALIBRATION34_CPR10_TARG_VOLT_SVSL1_SHFT                                                          5
#define HWIO_CALIBRATION34_CPR10_TARG_VOLT_NOM_5_1_BMSK                                                     0x1f
#define HWIO_CALIBRATION34_CPR10_TARG_VOLT_NOM_5_1_SHFT                                                        0

#define HWIO_CALIBRATION35_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd8c)
#define HWIO_CALIBRATION35_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd8c)
#define HWIO_CALIBRATION35_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION35_ATTR                                                                                    0x1
#define HWIO_CALIBRATION35_IN                    \
                in_dword(HWIO_CALIBRATION35_ADDR)
#define HWIO_CALIBRATION35_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION35_ADDR, m)
#define HWIO_CALIBRATION35_CPR10_SVS2_QUOT_MIN_2_0_BMSK                                               0xe0000000
#define HWIO_CALIBRATION35_CPR10_SVS2_QUOT_MIN_2_0_SHFT                                                       29
#define HWIO_CALIBRATION35_CPR10_SVSL1_QUOT_MIN_BMSK                                                  0x1ffe0000
#define HWIO_CALIBRATION35_CPR10_SVSL1_QUOT_MIN_SHFT                                                          17
#define HWIO_CALIBRATION35_CPR10_NOM_QUOT_MIN_BMSK                                                       0x1ffe0
#define HWIO_CALIBRATION35_CPR10_NOM_QUOT_MIN_SHFT                                                             5
#define HWIO_CALIBRATION35_CPR10_TURL1_QUOT_MIN_11_7_BMSK                                                   0x1f
#define HWIO_CALIBRATION35_CPR10_TURL1_QUOT_MIN_11_7_SHFT                                                      0

#define HWIO_CALIBRATION36_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd90)
#define HWIO_CALIBRATION36_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd90)
#define HWIO_CALIBRATION36_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION36_ATTR                                                                                    0x1
#define HWIO_CALIBRATION36_IN                    \
                in_dword(HWIO_CALIBRATION36_ADDR)
#define HWIO_CALIBRATION36_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION36_ADDR, m)
#define HWIO_CALIBRATION36_CALIBRATION_1183_1182_BMSK                                                 0xc0000000
#define HWIO_CALIBRATION36_CALIBRATION_1183_1182_SHFT                                                         30
#define HWIO_CALIBRATION36_CPR_APC1_MODE_DISABLE_BMSK                                                 0x38000000
#define HWIO_CALIBRATION36_CPR_APC1_MODE_DISABLE_SHFT                                                         27
#define HWIO_CALIBRATION36_CPR11_TARG_VOLT_SVSL1_BMSK                                                  0x7e00000
#define HWIO_CALIBRATION36_CPR11_TARG_VOLT_SVSL1_SHFT                                                         21
#define HWIO_CALIBRATION36_CPR11_TARG_VOLT_NOM_BMSK                                                     0x1f8000
#define HWIO_CALIBRATION36_CPR11_TARG_VOLT_NOM_SHFT                                                           15
#define HWIO_CALIBRATION36_CPR11_TARG_VOLT_TUR_BMSK                                                       0x7e00
#define HWIO_CALIBRATION36_CPR11_TARG_VOLT_TUR_SHFT                                                            9
#define HWIO_CALIBRATION36_CPR10_SVS2_QUOT_MIN_11_3_BMSK                                                   0x1ff
#define HWIO_CALIBRATION36_CPR10_SVS2_QUOT_MIN_11_3_SHFT                                                       0

#define HWIO_CALIBRATION37_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd94)
#define HWIO_CALIBRATION37_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd94)
#define HWIO_CALIBRATION37_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION37_ATTR                                                                                    0x1
#define HWIO_CALIBRATION37_IN                    \
                in_dword(HWIO_CALIBRATION37_ADDR)
#define HWIO_CALIBRATION37_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION37_ADDR, m)
#define HWIO_CALIBRATION37_CALIBRATION_1215_1184_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION37_CALIBRATION_1215_1184_SHFT                                                          0

#define HWIO_CALIBRATION38_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd98)
#define HWIO_CALIBRATION38_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd98)
#define HWIO_CALIBRATION38_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION38_ATTR                                                                                    0x1
#define HWIO_CALIBRATION38_IN                    \
                in_dword(HWIO_CALIBRATION38_ADDR)
#define HWIO_CALIBRATION38_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION38_ADDR, m)
#define HWIO_CALIBRATION38_CALIBRATION_1247_1216_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION38_CALIBRATION_1247_1216_SHFT                                                          0

#define HWIO_CALIBRATION39_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd9c)
#define HWIO_CALIBRATION39_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd9c)
#define HWIO_CALIBRATION39_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION39_ATTR                                                                                    0x1
#define HWIO_CALIBRATION39_IN                    \
                in_dword(HWIO_CALIBRATION39_ADDR)
#define HWIO_CALIBRATION39_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION39_ADDR, m)
#define HWIO_CALIBRATION39_CALIBRATION_1279_1248_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION39_CALIBRATION_1279_1248_SHFT                                                          0

#define HWIO_CALIBRATION40_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xda0)
#define HWIO_CALIBRATION40_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xda0)
#define HWIO_CALIBRATION40_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION40_ATTR                                                                                    0x1
#define HWIO_CALIBRATION40_IN                    \
                in_dword(HWIO_CALIBRATION40_ADDR)
#define HWIO_CALIBRATION40_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION40_ADDR, m)
#define HWIO_CALIBRATION40_CALIBRATION_1311_1280_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION40_CALIBRATION_1311_1280_SHFT                                                          0

#define HWIO_CALIBRATION41_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xda4)
#define HWIO_CALIBRATION41_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xda4)
#define HWIO_CALIBRATION41_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION41_ATTR                                                                                    0x1
#define HWIO_CALIBRATION41_IN                    \
                in_dword(HWIO_CALIBRATION41_ADDR)
#define HWIO_CALIBRATION41_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION41_ADDR, m)
#define HWIO_CALIBRATION41_CALIBRATION_1343_1312_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION41_CALIBRATION_1343_1312_SHFT                                                          0

#define HWIO_CALIBRATION42_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xda8)
#define HWIO_CALIBRATION42_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xda8)
#define HWIO_CALIBRATION42_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION42_ATTR                                                                                    0x1
#define HWIO_CALIBRATION42_IN                    \
                in_dword(HWIO_CALIBRATION42_ADDR)
#define HWIO_CALIBRATION42_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION42_ADDR, m)
#define HWIO_CALIBRATION42_CALIBRATION_1375_1344_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION42_CALIBRATION_1375_1344_SHFT                                                          0

#define HWIO_CALIBRATION43_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdac)
#define HWIO_CALIBRATION43_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdac)
#define HWIO_CALIBRATION43_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION43_ATTR                                                                                    0x1
#define HWIO_CALIBRATION43_IN                    \
                in_dword(HWIO_CALIBRATION43_ADDR)
#define HWIO_CALIBRATION43_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION43_ADDR, m)
#define HWIO_CALIBRATION43_CALIBRATION_1407_1376_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION43_CALIBRATION_1407_1376_SHFT                                                          0

#define HWIO_CALIBRATION44_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdb0)
#define HWIO_CALIBRATION44_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdb0)
#define HWIO_CALIBRATION44_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION44_ATTR                                                                                    0x1
#define HWIO_CALIBRATION44_IN                    \
                in_dword(HWIO_CALIBRATION44_ADDR)
#define HWIO_CALIBRATION44_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION44_ADDR, m)
#define HWIO_CALIBRATION44_CALIBRATION_1439_1408_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION44_CALIBRATION_1439_1408_SHFT                                                          0

#define HWIO_CALIBRATION45_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdb4)
#define HWIO_CALIBRATION45_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdb4)
#define HWIO_CALIBRATION45_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION45_ATTR                                                                                    0x1
#define HWIO_CALIBRATION45_IN                    \
                in_dword(HWIO_CALIBRATION45_ADDR)
#define HWIO_CALIBRATION45_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION45_ADDR, m)
#define HWIO_CALIBRATION45_CALIBRATION_1471_1440_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION45_CALIBRATION_1471_1440_SHFT                                                          0

#define HWIO_CALIBRATION46_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdb8)
#define HWIO_CALIBRATION46_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdb8)
#define HWIO_CALIBRATION46_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION46_ATTR                                                                                    0x1
#define HWIO_CALIBRATION46_IN                    \
                in_dword(HWIO_CALIBRATION46_ADDR)
#define HWIO_CALIBRATION46_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION46_ADDR, m)
#define HWIO_CALIBRATION46_CALIBRATION_1503_1472_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION46_CALIBRATION_1503_1472_SHFT                                                          0

#define HWIO_CALIBRATION47_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdbc)
#define HWIO_CALIBRATION47_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdbc)
#define HWIO_CALIBRATION47_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION47_ATTR                                                                                    0x1
#define HWIO_CALIBRATION47_IN                    \
                in_dword(HWIO_CALIBRATION47_ADDR)
#define HWIO_CALIBRATION47_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION47_ADDR, m)
#define HWIO_CALIBRATION47_CALIBRATION_1535_1504_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION47_CALIBRATION_1535_1504_SHFT                                                          0

#define HWIO_CALIBRATION48_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdc0)
#define HWIO_CALIBRATION48_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdc0)
#define HWIO_CALIBRATION48_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION48_ATTR                                                                                    0x1
#define HWIO_CALIBRATION48_IN                    \
                in_dword(HWIO_CALIBRATION48_ADDR)
#define HWIO_CALIBRATION48_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION48_ADDR, m)
#define HWIO_CALIBRATION48_CALIBRATION_1567_1536_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION48_CALIBRATION_1567_1536_SHFT                                                          0

#define HWIO_CALIBRATION49_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdc4)
#define HWIO_CALIBRATION49_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdc4)
#define HWIO_CALIBRATION49_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION49_ATTR                                                                                    0x1
#define HWIO_CALIBRATION49_IN                    \
                in_dword(HWIO_CALIBRATION49_ADDR)
#define HWIO_CALIBRATION49_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION49_ADDR, m)
#define HWIO_CALIBRATION49_CALIBRATION_1599_1568_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION49_CALIBRATION_1599_1568_SHFT                                                          0

#define HWIO_CALIBRATION50_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdc8)
#define HWIO_CALIBRATION50_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdc8)
#define HWIO_CALIBRATION50_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION50_ATTR                                                                                    0x1
#define HWIO_CALIBRATION50_IN                    \
                in_dword(HWIO_CALIBRATION50_ADDR)
#define HWIO_CALIBRATION50_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION50_ADDR, m)
#define HWIO_CALIBRATION50_CALIBRATION_1631_1600_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION50_CALIBRATION_1631_1600_SHFT                                                          0

#define HWIO_CALIBRATION51_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdcc)
#define HWIO_CALIBRATION51_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdcc)
#define HWIO_CALIBRATION51_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION51_ATTR                                                                                    0x1
#define HWIO_CALIBRATION51_IN                    \
                in_dword(HWIO_CALIBRATION51_ADDR)
#define HWIO_CALIBRATION51_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION51_ADDR, m)
#define HWIO_CALIBRATION51_CALBIST_RESERVED_BMSK                                                      0xff000000
#define HWIO_CALIBRATION51_CALBIST_RESERVED_SHFT                                                              24
#define HWIO_CALIBRATION51_REFGEN_FT_BMSK                                                               0x800000
#define HWIO_CALIBRATION51_REFGEN_FT_SHFT                                                                     23
#define HWIO_CALIBRATION51_REFGEN_WS_BMSK                                                               0x400000
#define HWIO_CALIBRATION51_REFGEN_WS_SHFT                                                                     22
#define HWIO_CALIBRATION51_USB_FT_BMSK                                                                  0x200000
#define HWIO_CALIBRATION51_USB_FT_SHFT                                                                        21
#define HWIO_CALIBRATION51_USB_WS_BMSK                                                                  0x100000
#define HWIO_CALIBRATION51_USB_WS_SHFT                                                                        20
#define HWIO_CALIBRATION51_CPR_FT_BMSK                                                                   0x80000
#define HWIO_CALIBRATION51_CPR_FT_SHFT                                                                        19
#define HWIO_CALIBRATION51_CPR_WS_BMSK                                                                   0x40000
#define HWIO_CALIBRATION51_CPR_WS_SHFT                                                                        18
#define HWIO_CALIBRATION51_AOSS_FT_BMSK                                                                  0x20000
#define HWIO_CALIBRATION51_AOSS_FT_SHFT                                                                       17
#define HWIO_CALIBRATION51_AOSS_WS_BMSK                                                                  0x10000
#define HWIO_CALIBRATION51_AOSS_WS_SHFT                                                                       16
#define HWIO_CALIBRATION51_ISENS_FT_BMSK                                                                  0x8000
#define HWIO_CALIBRATION51_ISENS_FT_SHFT                                                                      15
#define HWIO_CALIBRATION51_ISENS_WS_BMSK                                                                  0x4000
#define HWIO_CALIBRATION51_ISENS_WS_SHFT                                                                      14
#define HWIO_CALIBRATION51_DDR_FT_BMSK                                                                    0x2000
#define HWIO_CALIBRATION51_DDR_FT_SHFT                                                                        13
#define HWIO_CALIBRATION51_DDR_WS_BMSK                                                                    0x1000
#define HWIO_CALIBRATION51_DDR_WS_SHFT                                                                        12
#define HWIO_CALIBRATION51_MRET_FT_BMSK                                                                    0x800
#define HWIO_CALIBRATION51_MRET_FT_SHFT                                                                       11
#define HWIO_CALIBRATION51_MRET_WS_BMSK                                                                    0x400
#define HWIO_CALIBRATION51_MRET_WS_SHFT                                                                       10
#define HWIO_CALIBRATION51_LRET_FT_BMSK                                                                    0x200
#define HWIO_CALIBRATION51_LRET_FT_SHFT                                                                        9
#define HWIO_CALIBRATION51_LRET_WS_BMSK                                                                    0x100
#define HWIO_CALIBRATION51_LRET_WS_SHFT                                                                        8
#define HWIO_CALIBRATION51_IDDQ_FT_BMSK                                                                     0x80
#define HWIO_CALIBRATION51_IDDQ_FT_SHFT                                                                        7
#define HWIO_CALIBRATION51_IDDQ_WS_BMSK                                                                     0x40
#define HWIO_CALIBRATION51_IDDQ_WS_SHFT                                                                        6
#define HWIO_CALIBRATION51_DVS_FT_BMSK                                                                      0x20
#define HWIO_CALIBRATION51_DVS_FT_SHFT                                                                         5
#define HWIO_CALIBRATION51_DVS_WS_BMSK                                                                      0x10
#define HWIO_CALIBRATION51_DVS_WS_SHFT                                                                         4
#define HWIO_CALIBRATION51_TSENS_FT_BMSK                                                                     0x8
#define HWIO_CALIBRATION51_TSENS_FT_SHFT                                                                       3
#define HWIO_CALIBRATION51_TSENS_WS_BMSK                                                                     0x4
#define HWIO_CALIBRATION51_TSENS_WS_SHFT                                                                       2
#define HWIO_CALIBRATION51_QFPROM_FT_BMSK                                                                    0x2
#define HWIO_CALIBRATION51_QFPROM_FT_SHFT                                                                      1
#define HWIO_CALIBRATION51_QFPROM_WS_BMSK                                                                    0x1
#define HWIO_CALIBRATION51_QFPROM_WS_SHFT                                                                      0

#define HWIO_CALIBRATION52_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdd0)
#define HWIO_CALIBRATION52_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdd0)
#define HWIO_CALIBRATION52_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION52_ATTR                                                                                    0x1
#define HWIO_CALIBRATION52_IN                    \
                in_dword(HWIO_CALIBRATION52_ADDR)
#define HWIO_CALIBRATION52_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION52_ADDR, m)
#define HWIO_CALIBRATION52_TSENS1_BASE1_1_0_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION52_TSENS1_BASE1_1_0_SHFT                                                              30
#define HWIO_CALIBRATION52_TSENS1_BASE0_BMSK                                                          0x3ff00000
#define HWIO_CALIBRATION52_TSENS1_BASE0_SHFT                                                                  20
#define HWIO_CALIBRATION52_TSENS0_BASE1_BMSK                                                             0xffc00
#define HWIO_CALIBRATION52_TSENS0_BASE1_SHFT                                                                  10
#define HWIO_CALIBRATION52_TSENS0_BASE0_BMSK                                                               0x3ff
#define HWIO_CALIBRATION52_TSENS0_BASE0_SHFT                                                                   0

#define HWIO_CALIBRATION53_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdd4)
#define HWIO_CALIBRATION53_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdd4)
#define HWIO_CALIBRATION53_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION53_ATTR                                                                                    0x1
#define HWIO_CALIBRATION53_IN                    \
                in_dword(HWIO_CALIBRATION53_ADDR)
#define HWIO_CALIBRATION53_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION53_ADDR, m)
#define HWIO_CALIBRATION53_TSENS4_OFFSET_3_0_BMSK                                                     0xf0000000
#define HWIO_CALIBRATION53_TSENS4_OFFSET_3_0_SHFT                                                             28
#define HWIO_CALIBRATION53_TSENS3_OFFSET_BMSK                                                          0xf800000
#define HWIO_CALIBRATION53_TSENS3_OFFSET_SHFT                                                                 23
#define HWIO_CALIBRATION53_TSENS2_OFFSET_BMSK                                                           0x7c0000
#define HWIO_CALIBRATION53_TSENS2_OFFSET_SHFT                                                                 18
#define HWIO_CALIBRATION53_TSENS1_OFFSET_BMSK                                                            0x3e000
#define HWIO_CALIBRATION53_TSENS1_OFFSET_SHFT                                                                 13
#define HWIO_CALIBRATION53_TSENS0_OFFSET_BMSK                                                             0x1f00
#define HWIO_CALIBRATION53_TSENS0_OFFSET_SHFT                                                                  8
#define HWIO_CALIBRATION53_TSENS1_BASE1_9_2_BMSK                                                            0xff
#define HWIO_CALIBRATION53_TSENS1_BASE1_9_2_SHFT                                                               0

#define HWIO_CALIBRATION54_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdd8)
#define HWIO_CALIBRATION54_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdd8)
#define HWIO_CALIBRATION54_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION54_ATTR                                                                                    0x1
#define HWIO_CALIBRATION54_IN                    \
                in_dword(HWIO_CALIBRATION54_ADDR)
#define HWIO_CALIBRATION54_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION54_ADDR, m)
#define HWIO_CALIBRATION54_TSENS11_OFFSET_0_BMSK                                                      0x80000000
#define HWIO_CALIBRATION54_TSENS11_OFFSET_0_SHFT                                                              31
#define HWIO_CALIBRATION54_TSENS10_OFFSET_BMSK                                                        0x7c000000
#define HWIO_CALIBRATION54_TSENS10_OFFSET_SHFT                                                                26
#define HWIO_CALIBRATION54_TSENS9_OFFSET_BMSK                                                          0x3e00000
#define HWIO_CALIBRATION54_TSENS9_OFFSET_SHFT                                                                 21
#define HWIO_CALIBRATION54_TSENS8_OFFSET_BMSK                                                           0x1f0000
#define HWIO_CALIBRATION54_TSENS8_OFFSET_SHFT                                                                 16
#define HWIO_CALIBRATION54_TSENS7_OFFSET_BMSK                                                             0xf800
#define HWIO_CALIBRATION54_TSENS7_OFFSET_SHFT                                                                 11
#define HWIO_CALIBRATION54_TSENS6_OFFSET_BMSK                                                              0x7c0
#define HWIO_CALIBRATION54_TSENS6_OFFSET_SHFT                                                                  6
#define HWIO_CALIBRATION54_TSENS5_OFFSET_BMSK                                                               0x3e
#define HWIO_CALIBRATION54_TSENS5_OFFSET_SHFT                                                                  1
#define HWIO_CALIBRATION54_TSENS4_OFFSET_4_BMSK                                                              0x1
#define HWIO_CALIBRATION54_TSENS4_OFFSET_4_SHFT                                                                0

#define HWIO_CALIBRATION55_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xddc)
#define HWIO_CALIBRATION55_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xddc)
#define HWIO_CALIBRATION55_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION55_ATTR                                                                                    0x1
#define HWIO_CALIBRATION55_IN                    \
                in_dword(HWIO_CALIBRATION55_ADDR)
#define HWIO_CALIBRATION55_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION55_ADDR, m)
#define HWIO_CALIBRATION55_TSENS17_OFFSET_2_0_BMSK                                                    0xe0000000
#define HWIO_CALIBRATION55_TSENS17_OFFSET_2_0_SHFT                                                            29
#define HWIO_CALIBRATION55_TSENS16_OFFSET_BMSK                                                        0x1f000000
#define HWIO_CALIBRATION55_TSENS16_OFFSET_SHFT                                                                24
#define HWIO_CALIBRATION55_TSENS15_OFFSET_BMSK                                                          0xf80000
#define HWIO_CALIBRATION55_TSENS15_OFFSET_SHFT                                                                19
#define HWIO_CALIBRATION55_TSENS14_OFFSET_BMSK                                                           0x7c000
#define HWIO_CALIBRATION55_TSENS14_OFFSET_SHFT                                                                14
#define HWIO_CALIBRATION55_TSENS13_OFFSET_BMSK                                                            0x3e00
#define HWIO_CALIBRATION55_TSENS13_OFFSET_SHFT                                                                 9
#define HWIO_CALIBRATION55_TSENS12_OFFSET_BMSK                                                             0x1f0
#define HWIO_CALIBRATION55_TSENS12_OFFSET_SHFT                                                                 4
#define HWIO_CALIBRATION55_TSENS11_OFFSET_4_1_BMSK                                                           0xf
#define HWIO_CALIBRATION55_TSENS11_OFFSET_4_1_SHFT                                                             0

#define HWIO_CALIBRATION56_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xde0)
#define HWIO_CALIBRATION56_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xde0)
#define HWIO_CALIBRATION56_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION56_ATTR                                                                                    0x1
#define HWIO_CALIBRATION56_IN                    \
                in_dword(HWIO_CALIBRATION56_ADDR)
#define HWIO_CALIBRATION56_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION56_ADDR, m)
#define HWIO_CALIBRATION56_CPR11_TARG_VOLT_SVS2_4_0_BMSK                                              0xf8000000
#define HWIO_CALIBRATION56_CPR11_TARG_VOLT_SVS2_4_0_SHFT                                                      27
#define HWIO_CALIBRATION56_CALIBRATION_1818_1817_BMSK                                                  0x6000000
#define HWIO_CALIBRATION56_CALIBRATION_1818_1817_SHFT                                                         25
#define HWIO_CALIBRATION56_TSENS_CAL_SEL_BMSK                                                          0x1c00000
#define HWIO_CALIBRATION56_TSENS_CAL_SEL_SHFT                                                                 22
#define HWIO_CALIBRATION56_TSENS21_OFFSET_BMSK                                                          0x3e0000
#define HWIO_CALIBRATION56_TSENS21_OFFSET_SHFT                                                                17
#define HWIO_CALIBRATION56_TSENS20_OFFSET_BMSK                                                           0x1f000
#define HWIO_CALIBRATION56_TSENS20_OFFSET_SHFT                                                                12
#define HWIO_CALIBRATION56_TSENS19_OFFSET_BMSK                                                             0xf80
#define HWIO_CALIBRATION56_TSENS19_OFFSET_SHFT                                                                 7
#define HWIO_CALIBRATION56_TSENS18_OFFSET_BMSK                                                              0x7c
#define HWIO_CALIBRATION56_TSENS18_OFFSET_SHFT                                                                 2
#define HWIO_CALIBRATION56_TSENS17_OFFSET_4_3_BMSK                                                           0x3
#define HWIO_CALIBRATION56_TSENS17_OFFSET_4_3_SHFT                                                             0

#define HWIO_CALIBRATION57_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xde4)
#define HWIO_CALIBRATION57_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xde4)
#define HWIO_CALIBRATION57_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION57_ATTR                                                                                    0x1
#define HWIO_CALIBRATION57_IN                    \
                in_dword(HWIO_CALIBRATION57_ADDR)
#define HWIO_CALIBRATION57_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION57_ADDR, m)
#define HWIO_CALIBRATION57_CPR11_NOM_QUOT_MIN_10_0_BMSK                                               0xffe00000
#define HWIO_CALIBRATION57_CPR11_NOM_QUOT_MIN_10_0_SHFT                                                       21
#define HWIO_CALIBRATION57_CPR11_TUR_QUOT_MIN_BMSK                                                      0x1ffe00
#define HWIO_CALIBRATION57_CPR11_TUR_QUOT_MIN_SHFT                                                             9
#define HWIO_CALIBRATION57_CPR11_QUOT_OFFSET_BMSK                                                          0x1fe
#define HWIO_CALIBRATION57_CPR11_QUOT_OFFSET_SHFT                                                              1
#define HWIO_CALIBRATION57_CPR11_TARG_VOLT_SVS2_5_BMSK                                                       0x1
#define HWIO_CALIBRATION57_CPR11_TARG_VOLT_SVS2_5_SHFT                                                         0

#define HWIO_CALIBRATION58_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xde8)
#define HWIO_CALIBRATION58_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xde8)
#define HWIO_CALIBRATION58_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION58_ATTR                                                                                    0x1
#define HWIO_CALIBRATION58_IN                    \
                in_dword(HWIO_CALIBRATION58_ADDR)
#define HWIO_CALIBRATION58_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION58_ADDR, m)
#define HWIO_CALIBRATION58_CPR12_TARG_VOLT_TURL1_0_BMSK                                               0x80000000
#define HWIO_CALIBRATION58_CPR12_TARG_VOLT_TURL1_0_SHFT                                                       31
#define HWIO_CALIBRATION58_CPR12_TARG_VOLT_TURL3_BMSK                                                 0x7e000000
#define HWIO_CALIBRATION58_CPR12_TARG_VOLT_TURL3_SHFT                                                         25
#define HWIO_CALIBRATION58_CPR11_SVS2_QUOT_MIN_BMSK                                                    0x1ffe000
#define HWIO_CALIBRATION58_CPR11_SVS2_QUOT_MIN_SHFT                                                           13
#define HWIO_CALIBRATION58_CPR11_SVSL1_QUOT_MIN_BMSK                                                      0x1ffe
#define HWIO_CALIBRATION58_CPR11_SVSL1_QUOT_MIN_SHFT                                                           1
#define HWIO_CALIBRATION58_CPR11_NOM_QUOT_MIN_11_BMSK                                                        0x1
#define HWIO_CALIBRATION58_CPR11_NOM_QUOT_MIN_11_SHFT                                                          0

#define HWIO_CALIBRATION59_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdec)
#define HWIO_CALIBRATION59_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdec)
#define HWIO_CALIBRATION59_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION59_ATTR                                                                                    0x1
#define HWIO_CALIBRATION59_IN                    \
                in_dword(HWIO_CALIBRATION59_ADDR)
#define HWIO_CALIBRATION59_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION59_ADDR, m)
#define HWIO_CALIBRATION59_CPR12_TURL3_QUOT_MIN_0_BMSK                                                0x80000000
#define HWIO_CALIBRATION59_CPR12_TURL3_QUOT_MIN_0_SHFT                                                        31
#define HWIO_CALIBRATION59_CPR12_QUOT_OFFSET_BMSK                                                     0x7f800000
#define HWIO_CALIBRATION59_CPR12_QUOT_OFFSET_SHFT                                                             23
#define HWIO_CALIBRATION59_CPR12_TARG_VOLT_SVS2_BMSK                                                    0x7e0000
#define HWIO_CALIBRATION59_CPR12_TARG_VOLT_SVS2_SHFT                                                          17
#define HWIO_CALIBRATION59_CPR12_TARG_VOLT_SVSL1_BMSK                                                    0x1f800
#define HWIO_CALIBRATION59_CPR12_TARG_VOLT_SVSL1_SHFT                                                         11
#define HWIO_CALIBRATION59_CPR12_TARG_VOLT_NOML1_BMSK                                                      0x7e0
#define HWIO_CALIBRATION59_CPR12_TARG_VOLT_NOML1_SHFT                                                          5
#define HWIO_CALIBRATION59_CPR12_TARG_VOLT_TURL1_5_1_BMSK                                                   0x1f
#define HWIO_CALIBRATION59_CPR12_TARG_VOLT_TURL1_5_1_SHFT                                                      0

#define HWIO_CALIBRATION60_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdf0)
#define HWIO_CALIBRATION60_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdf0)
#define HWIO_CALIBRATION60_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION60_ATTR                                                                                    0x1
#define HWIO_CALIBRATION60_IN                    \
                in_dword(HWIO_CALIBRATION60_ADDR)
#define HWIO_CALIBRATION60_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION60_ADDR, m)
#define HWIO_CALIBRATION60_CPR12_NOML1_QUOT_MIN_8_0_BMSK                                              0xff800000
#define HWIO_CALIBRATION60_CPR12_NOML1_QUOT_MIN_8_0_SHFT                                                      23
#define HWIO_CALIBRATION60_CPR12_TURL1_QUOT_MIN_BMSK                                                    0x7ff800
#define HWIO_CALIBRATION60_CPR12_TURL1_QUOT_MIN_SHFT                                                          11
#define HWIO_CALIBRATION60_CPR12_TURL3_QUOT_MIN_11_1_BMSK                                                  0x7ff
#define HWIO_CALIBRATION60_CPR12_TURL3_QUOT_MIN_11_1_SHFT                                                      0

#define HWIO_CALIBRATION61_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdf4)
#define HWIO_CALIBRATION61_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdf4)
#define HWIO_CALIBRATION61_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION61_ATTR                                                                                    0x1
#define HWIO_CALIBRATION61_IN                    \
                in_dword(HWIO_CALIBRATION61_ADDR)
#define HWIO_CALIBRATION61_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION61_ADDR, m)
#define HWIO_CALIBRATION61_CPR10_AGING_4_0_BMSK                                                       0xf8000000
#define HWIO_CALIBRATION61_CPR10_AGING_4_0_SHFT                                                               27
#define HWIO_CALIBRATION61_CPR12_SVS2_QUOT_MIN_BMSK                                                    0x7ff8000
#define HWIO_CALIBRATION61_CPR12_SVS2_QUOT_MIN_SHFT                                                           15
#define HWIO_CALIBRATION61_CPR12_SVSL1_QUOT_MIN_BMSK                                                      0x7ff8
#define HWIO_CALIBRATION61_CPR12_SVSL1_QUOT_MIN_SHFT                                                           3
#define HWIO_CALIBRATION61_CPR12_NOML1_QUOT_MIN_11_9_BMSK                                                    0x7
#define HWIO_CALIBRATION61_CPR12_NOML1_QUOT_MIN_11_9_SHFT                                                      0

#define HWIO_CALIBRATION62_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdf8)
#define HWIO_CALIBRATION62_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdf8)
#define HWIO_CALIBRATION62_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION62_ATTR                                                                                    0x1
#define HWIO_CALIBRATION62_IN                    \
                in_dword(HWIO_CALIBRATION62_ADDR)
#define HWIO_CALIBRATION62_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION62_ADDR, m)
#define HWIO_CALIBRATION62_ISENSE_FUSE_CURRENT_CPU7_F1_2_0_BMSK                                       0xe0000000
#define HWIO_CALIBRATION62_ISENSE_FUSE_CURRENT_CPU7_F1_2_0_SHFT                                               29
#define HWIO_CALIBRATION62_ISENSE_FUSE_CURRENT_CPU6_F2_BMSK                                           0x1ff80000
#define HWIO_CALIBRATION62_ISENSE_FUSE_CURRENT_CPU6_F2_SHFT                                                   19
#define HWIO_CALIBRATION62_ISENSE_FUSE_CURRENT_CPU6_F1_BMSK                                              0x7fe00
#define HWIO_CALIBRATION62_ISENSE_FUSE_CURRENT_CPU6_F1_SHFT                                                    9
#define HWIO_CALIBRATION62_AON_TARGE_VOLT_BMSK                                                             0x1f8
#define HWIO_CALIBRATION62_AON_TARGE_VOLT_SHFT                                                                 3
#define HWIO_CALIBRATION62_CPR10_AGING_7_5_BMSK                                                              0x7
#define HWIO_CALIBRATION62_CPR10_AGING_7_5_SHFT                                                                0

#define HWIO_CALIBRATION63_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdfc)
#define HWIO_CALIBRATION63_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdfc)
#define HWIO_CALIBRATION63_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION63_ATTR                                                                                    0x1
#define HWIO_CALIBRATION63_IN                    \
                in_dword(HWIO_CALIBRATION63_ADDR)
#define HWIO_CALIBRATION63_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION63_ADDR, m)
#define HWIO_CALIBRATION63_VSENSE_FUSE1_S0_0_BMSK                                                     0x80000000
#define HWIO_CALIBRATION63_VSENSE_FUSE1_S0_0_SHFT                                                             31
#define HWIO_CALIBRATION63_VSENSE_FUSE1_BMSK                                                          0x7f800000
#define HWIO_CALIBRATION63_VSENSE_FUSE1_SHFT                                                                  23
#define HWIO_CALIBRATION63_ISENSE_FUSE_REVISION_CONTROL_WS_BMSK                                         0x700000
#define HWIO_CALIBRATION63_ISENSE_FUSE_REVISION_CONTROL_WS_SHFT                                               20
#define HWIO_CALIBRATION63_ISENSE_FUSE_REVISION_CONTROL_FT_BMSK                                          0xe0000
#define HWIO_CALIBRATION63_ISENSE_FUSE_REVISION_CONTROL_FT_SHFT                                               17
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_CPU7_F2_BMSK                                              0x1ff80
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_CPU7_F2_SHFT                                                    7
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_CPU7_F1_9_3_BMSK                                             0x7f
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_CPU7_F1_9_3_SHFT                                                0

#define HWIO_CALIBRATION64_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe00)
#define HWIO_CALIBRATION64_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe00)
#define HWIO_CALIBRATION64_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION64_ATTR                                                                                    0x1
#define HWIO_CALIBRATION64_IN                    \
                in_dword(HWIO_CALIBRATION64_ADDR)
#define HWIO_CALIBRATION64_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION64_ADDR, m)
#define HWIO_CALIBRATION64_VSENSE_FUSE2_S0_0_BMSK                                                     0x80000000
#define HWIO_CALIBRATION64_VSENSE_FUSE2_S0_0_SHFT                                                             31
#define HWIO_CALIBRATION64_VSENSE_FUSE2_BMSK                                                          0x7f800000
#define HWIO_CALIBRATION64_VSENSE_FUSE2_SHFT                                                                  23
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S7_BMSK                                                         0x700000
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S7_SHFT                                                               20
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S6_BMSK                                                          0xe0000
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S6_SHFT                                                               17
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S5_BMSK                                                          0x1c000
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S5_SHFT                                                               14
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S4_BMSK                                                           0x3800
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S4_SHFT                                                               11
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S3_BMSK                                                            0x700
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S3_SHFT                                                                8
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S2_BMSK                                                             0xe0
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S2_SHFT                                                                5
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S1_BMSK                                                             0x1c
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S1_SHFT                                                                2
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S0_2_1_BMSK                                                          0x3
#define HWIO_CALIBRATION64_VSENSE_FUSE1_S0_2_1_SHFT                                                            0

#define HWIO_CALIBRATION65_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe04)
#define HWIO_CALIBRATION65_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe04)
#define HWIO_CALIBRATION65_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION65_ATTR                                                                                    0x1
#define HWIO_CALIBRATION65_IN                    \
                in_dword(HWIO_CALIBRATION65_ADDR)
#define HWIO_CALIBRATION65_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION65_ADDR, m)
#define HWIO_CALIBRATION65_CALIBRATION_2111_2110_BMSK                                                 0xc0000000
#define HWIO_CALIBRATION65_CALIBRATION_2111_2110_SHFT                                                         30
#define HWIO_CALIBRATION65_CPR_GFX_MODE_DISABLE_BMSK                                                  0x38000000
#define HWIO_CALIBRATION65_CPR_GFX_MODE_DISABLE_SHFT                                                          27
#define HWIO_CALIBRATION65_CPR_WCSS_CX_MODE_DISABLE_BMSK                                               0x7000000
#define HWIO_CALIBRATION65_CPR_WCSS_CX_MODE_DISABLE_SHFT                                                      24
#define HWIO_CALIBRATION65_CPR_LPICX_MODE_DISABLE_BMSK                                                  0xe00000
#define HWIO_CALIBRATION65_CPR_LPICX_MODE_DISABLE_SHFT                                                        21
#define HWIO_CALIBRATION65_CPR_DDR_MODE_DISABLE_BMSK                                                    0x1c0000
#define HWIO_CALIBRATION65_CPR_DDR_MODE_DISABLE_SHFT                                                          18
#define HWIO_CALIBRATION65_VSENSE_FUSE_REVISION_CONTROL_BMSK                                             0x38000
#define HWIO_CALIBRATION65_VSENSE_FUSE_REVISION_CONTROL_SHFT                                                  15
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S7_BMSK                                                           0x6000
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S7_SHFT                                                               13
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S6_BMSK                                                           0x1800
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S6_SHFT                                                               11
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S5_BMSK                                                            0x600
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S5_SHFT                                                                9
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S4_BMSK                                                            0x180
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S4_SHFT                                                                7
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S3_BMSK                                                             0x60
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S3_SHFT                                                                5
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S2_BMSK                                                             0x18
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S2_SHFT                                                                3
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S1_BMSK                                                              0x6
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S1_SHFT                                                                1
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S0_1_BMSK                                                            0x1
#define HWIO_CALIBRATION65_VSENSE_FUSE2_S0_1_SHFT                                                              0

// QFPROM - VPID Fuses
/*----------------------------------------------------------------------------
 * MODULE: QFPROM_CORR
 *--------------------------------------------------------------------------*/

#define QFPROM_CORR_REG_BASE                                                                                        (TMESS_BASE      + 0x021c2000)
#define QFPROM_CORR_REG_BASE_SIZE                                                                                   0x2000
#define QFPROM_CORR_REG_BASE_USED                                                                                   0xcdc
#define QFPROM_CORR_REG_BASE_OFFS                                                                                   0x021c2000

#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_ADDR                                                                        (QFPROM_CORR_REG_BASE      + 0x2c8)
#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_OFFS                                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x2c8)
#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_ATTR                                                                                     0x1
#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_0_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_QC_SPARE_0_31_8_BMSK                                                        0xffffff00
#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_QC_SPARE_0_31_8_SHFT                                                                 8
#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_SW_SPT_GLOBAL_RAILS_VPID_BMSK                                                     0xf0
#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_SW_SPT_GLOBAL_RAILS_VPID_SHFT                                                        4
#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_SW_SPT_LOCAL_RAILS_VPID_BMSK                                                       0xf
#define HWIO_QFPROM_CORR_QC_SPARE_0_LSB_SW_SPT_LOCAL_RAILS_VPID_SHFT                                                         0


#endif /* __CPR_FUSES_HWIO_H__ */
