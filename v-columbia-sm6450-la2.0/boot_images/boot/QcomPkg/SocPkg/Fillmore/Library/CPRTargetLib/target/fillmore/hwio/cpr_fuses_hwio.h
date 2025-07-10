#ifndef __CPR_FUSES_HWIO_H__
#define __CPR_FUSES_HWIO_H__
/*
===========================================================================
*/
/**
    @file cpr_fuses_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM7450 (Fillmore) [fillmore_v1.0_p3q3r83_MTO_qref_ddrphy_tmeblk]
 
    This file contains HWIO register definitions for the following modules:
        FUSE_CONTROLLER_SW_RANGE4

    'Include' filters applied: CALIBRATION[FUSE_CONTROLLER_SW_RANGE4] 

    Generation parameters: 
    { 'filename': 'cpr_fuses_hwio.h',
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

    $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Fillmore/Library/CPRTargetLib/target/fillmore/hwio/cpr_fuses_hwio.h#7 $
    $DateTime: 2022/03/23 04:56:53 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h" 

/*----------------------------------------------------------------------------
 * MODULE: FUSE_CONTROLLER_SW_RANGE4
 *--------------------------------------------------------------------------*/
#define QFPROM_CORR_REG_BASE                                                                               (TMESS_BASE      + 0x021c2000)
#define QFPROM_CORR_REG_BASE_SIZE                                                                          0x2000
#define QFPROM_CORR_REG_BASE_USED                                                                          0x101c
#define QFPROM_CORR_REG_BASE_OFFS                                                                          0x021c2000

#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR                                                          (QFPROM_CORR_REG_BASE      + 0x428)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_OFFS                                                          (QFPROM_CORR_REG_BASE_OFFS + 0x428)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_RMSK                                                          0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ATTR                                                                       0x1
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_QC_SPARE_0_31_8_BMSK                                          0xffffff00
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_QC_SPARE_0_31_8_SHFT                                                   8
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SW_SPT_LOCAL_RAILS_VPID_BMSK                                        0xf0
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SW_SPT_LOCAL_RAILS_VPID_SHFT                                           4
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SW_SPT_GLOBAL_RAILS_VPID_BMSK                                        0xf
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SW_SPT_GLOBAL_RAILS_VPID_SHFT                                          0

#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE                                                            (TMESS_BASE      + 0x021c8000)
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE                                                       0x1000
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_USED                                                       0xe54
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
#define HWIO_CALIBRATION0_CALIBRATION_30_16_BMSK                                                      0x7fff0000
#define HWIO_CALIBRATION0_CALIBRATION_30_16_SHFT                                                              16
#define HWIO_CALIBRATION0_REFGEN_NORTH_BGV_TRIM_BMSK                                                      0xff00
#define HWIO_CALIBRATION0_REFGEN_NORTH_BGV_TRIM_SHFT                                                           8
#define HWIO_CALIBRATION0_REFGEN_SOUTH_BGV_TRIM_BMSK                                                        0xff
#define HWIO_CALIBRATION0_REFGEN_SOUTH_BGV_TRIM_SHFT                                                           0

#define HWIO_CALIBRATION1_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd04)
#define HWIO_CALIBRATION1_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd04)
#define HWIO_CALIBRATION1_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION1_ATTR                                                                                     0x1
#define HWIO_CALIBRATION1_IN                    \
                in_dword(HWIO_CALIBRATION1_ADDR)
#define HWIO_CALIBRATION1_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION1_ADDR, m)
#define HWIO_CALIBRATION1_CALIBRATION_63_35_BMSK                                                      0xfffffff8
#define HWIO_CALIBRATION1_CALIBRATION_63_35_SHFT                                                               3
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
#define HWIO_CALIBRATION2_CALIBRATION_95_64_BMSK                                                      0xffffffff
#define HWIO_CALIBRATION2_CALIBRATION_95_64_SHFT                                                               0

#define HWIO_CALIBRATION3_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd0c)
#define HWIO_CALIBRATION3_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd0c)
#define HWIO_CALIBRATION3_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION3_ATTR                                                                                     0x1
#define HWIO_CALIBRATION3_IN                    \
                in_dword(HWIO_CALIBRATION3_ADDR)
#define HWIO_CALIBRATION3_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION3_ADDR, m)
#define HWIO_CALIBRATION3_CALIBRATION_127_96_BMSK                                                     0xffffffff
#define HWIO_CALIBRATION3_CALIBRATION_127_96_SHFT                                                              0

#define HWIO_CALIBRATION4_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd10)
#define HWIO_CALIBRATION4_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd10)
#define HWIO_CALIBRATION4_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION4_ATTR                                                                                     0x1
#define HWIO_CALIBRATION4_IN                    \
                in_dword(HWIO_CALIBRATION4_ADDR)
#define HWIO_CALIBRATION4_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION4_ADDR, m)
#define HWIO_CALIBRATION4_Q6_ACD_DVM_VAL1_7_0_BMSK                                                    0xff000000
#define HWIO_CALIBRATION4_Q6_ACD_DVM_VAL1_7_0_SHFT                                                            24
#define HWIO_CALIBRATION4_Q6_ACD_DVM_VAL0_BMSK                                                          0xffffff
#define HWIO_CALIBRATION4_Q6_ACD_DVM_VAL0_SHFT                                                                 0

#define HWIO_CALIBRATION5_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd14)
#define HWIO_CALIBRATION5_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd14)
#define HWIO_CALIBRATION5_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION5_ATTR                                                                                     0x1
#define HWIO_CALIBRATION5_IN                    \
                in_dword(HWIO_CALIBRATION5_ADDR)
#define HWIO_CALIBRATION5_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION5_ADDR, m)
#define HWIO_CALIBRATION5_Q6_ACD_DVM_VAL2_15_0_BMSK                                                   0xffff0000
#define HWIO_CALIBRATION5_Q6_ACD_DVM_VAL2_15_0_SHFT                                                           16
#define HWIO_CALIBRATION5_Q6_ACD_DVM_VAL1_23_8_BMSK                                                       0xffff
#define HWIO_CALIBRATION5_Q6_ACD_DVM_VAL1_23_8_SHFT                                                            0

#define HWIO_CALIBRATION6_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd18)
#define HWIO_CALIBRATION6_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd18)
#define HWIO_CALIBRATION6_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION6_ATTR                                                                                     0x1
#define HWIO_CALIBRATION6_IN                    \
                in_dword(HWIO_CALIBRATION6_ADDR)
#define HWIO_CALIBRATION6_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION6_ADDR, m)
#define HWIO_CALIBRATION6_Q6_ACD_DVM_VAL3_BMSK                                                        0xffffff00
#define HWIO_CALIBRATION6_Q6_ACD_DVM_VAL3_SHFT                                                                 8
#define HWIO_CALIBRATION6_Q6_ACD_DVM_VAL2_23_16_BMSK                                                        0xff
#define HWIO_CALIBRATION6_Q6_ACD_DVM_VAL2_23_16_SHFT                                                           0

#define HWIO_CALIBRATION7_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd1c)
#define HWIO_CALIBRATION7_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd1c)
#define HWIO_CALIBRATION7_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION7_ATTR                                                                                     0x1
#define HWIO_CALIBRATION7_IN                    \
                in_dword(HWIO_CALIBRATION7_ADDR)
#define HWIO_CALIBRATION7_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION7_ADDR, m)
#define HWIO_CALIBRATION7_Q6_ACD_DVM_VAL5_7_0_BMSK                                                    0xff000000
#define HWIO_CALIBRATION7_Q6_ACD_DVM_VAL5_7_0_SHFT                                                            24
#define HWIO_CALIBRATION7_Q6_ACD_DVM_VAL4_BMSK                                                          0xffffff
#define HWIO_CALIBRATION7_Q6_ACD_DVM_VAL4_SHFT                                                                 0

#define HWIO_CALIBRATION8_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd20)
#define HWIO_CALIBRATION8_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd20)
#define HWIO_CALIBRATION8_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION8_ATTR                                                                                     0x1
#define HWIO_CALIBRATION8_IN                    \
                in_dword(HWIO_CALIBRATION8_ADDR)
#define HWIO_CALIBRATION8_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION8_ADDR, m)
#define HWIO_CALIBRATION8_Q6_ACD_DVM_VAL6_15_0_BMSK                                                   0xffff0000
#define HWIO_CALIBRATION8_Q6_ACD_DVM_VAL6_15_0_SHFT                                                           16
#define HWIO_CALIBRATION8_Q6_ACD_DVM_VAL5_23_8_BMSK                                                       0xffff
#define HWIO_CALIBRATION8_Q6_ACD_DVM_VAL5_23_8_SHFT                                                            0

#define HWIO_CALIBRATION9_ADDR                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd24)
#define HWIO_CALIBRATION9_OFFS                                                                        (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd24)
#define HWIO_CALIBRATION9_RMSK                                                                        0xffffffff
#define HWIO_CALIBRATION9_ATTR                                                                                     0x1
#define HWIO_CALIBRATION9_IN                    \
                in_dword(HWIO_CALIBRATION9_ADDR)
#define HWIO_CALIBRATION9_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION9_ADDR, m)
#define HWIO_CALIBRATION9_CALIBRATION_319_305_BMSK                                                    0xfffe0000
#define HWIO_CALIBRATION9_CALIBRATION_319_305_SHFT                                                            17
#define HWIO_CALIBRATION9_MEM_Q6S_NEED_ACC_BMSK                                                          0x10000
#define HWIO_CALIBRATION9_MEM_Q6S_NEED_ACC_SHFT                                                               16
#define HWIO_CALIBRATION9_Q6_ACD_DVM_ENABLE_BMSK                                                          0xff00
#define HWIO_CALIBRATION9_Q6_ACD_DVM_ENABLE_SHFT                                                               8
#define HWIO_CALIBRATION9_Q6_ACD_DVM_VAL6_23_16_BMSK                                                        0xff
#define HWIO_CALIBRATION9_Q6_ACD_DVM_VAL6_23_16_SHFT                                                           0

#define HWIO_CALIBRATION10_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd28)
#define HWIO_CALIBRATION10_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd28)
#define HWIO_CALIBRATION10_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION10_ATTR                                                                                    0x1
#define HWIO_CALIBRATION10_IN                    \
                in_dword(HWIO_CALIBRATION10_ADDR)
#define HWIO_CALIBRATION10_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION10_ADDR, m)
#define HWIO_CALIBRATION10_VOLTAGE_SENSOR_CALIB_31_0_BMSK                                             0xffffffff
#define HWIO_CALIBRATION10_VOLTAGE_SENSOR_CALIB_31_0_SHFT                                                      0

#define HWIO_CALIBRATION11_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd2c)
#define HWIO_CALIBRATION11_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd2c)
#define HWIO_CALIBRATION11_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION11_ATTR                                                                                    0x1
#define HWIO_CALIBRATION11_IN                    \
                in_dword(HWIO_CALIBRATION11_ADDR)
#define HWIO_CALIBRATION11_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION11_ADDR, m)
#define HWIO_CALIBRATION11_VOLTAGE_SENSOR_CALIB_63_32_BMSK                                            0xffffffff
#define HWIO_CALIBRATION11_VOLTAGE_SENSOR_CALIB_63_32_SHFT                                                     0

#define HWIO_CALIBRATION12_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd30)
#define HWIO_CALIBRATION12_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd30)
#define HWIO_CALIBRATION12_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION12_ATTR                                                                                    0x1
#define HWIO_CALIBRATION12_IN                    \
                in_dword(HWIO_CALIBRATION12_ADDR)
#define HWIO_CALIBRATION12_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION12_ADDR, m)
#define HWIO_CALIBRATION12_CALIBRATION_415_409_BMSK                                                   0xfe000000
#define HWIO_CALIBRATION12_CALIBRATION_415_409_SHFT                                                           25
#define HWIO_CALIBRATION12_VOLTAGE_SENSOR_CALIB_88_64_BMSK                                             0x1ffffff
#define HWIO_CALIBRATION12_VOLTAGE_SENSOR_CALIB_88_64_SHFT                                                     0

#define HWIO_CALIBRATION13_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd34)
#define HWIO_CALIBRATION13_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd34)
#define HWIO_CALIBRATION13_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION13_ATTR                                                                                    0x1
#define HWIO_CALIBRATION13_IN                    \
                in_dword(HWIO_CALIBRATION13_ADDR)
#define HWIO_CALIBRATION13_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION13_ADDR, m)
#define HWIO_CALIBRATION13_CALIBRATION_447_416_BMSK                                                   0xffffffff
#define HWIO_CALIBRATION13_CALIBRATION_447_416_SHFT                                                            0

#define HWIO_CALIBRATION14_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd38)
#define HWIO_CALIBRATION14_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd38)
#define HWIO_CALIBRATION14_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION14_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION15_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd3c)
#define HWIO_CALIBRATION15_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd3c)
#define HWIO_CALIBRATION15_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION15_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION16_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd40)
#define HWIO_CALIBRATION16_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd40)
#define HWIO_CALIBRATION16_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION16_ATTR                                                                                    0x1
#define HWIO_CALIBRATION16_IN                    \
                in_dword(HWIO_CALIBRATION16_ADDR)
#define HWIO_CALIBRATION16_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION16_ADDR, m)
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_TUR_BMSK                                             0xf8000000
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_OFFSET_TUR_SHFT                                                     27
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_SVS3_BMSK                                                    0x7e00000
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_SVS3_SHFT                                                           21
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_SVS_BMSK                                                      0x1f8000
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_SVS_SHFT                                                            15
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_NOM_BMSK                                                        0x7e00
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_NOM_SHFT                                                             9
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_TUR_BMSK                                                         0x1f8
#define HWIO_CALIBRATION16_CPR1_TARG_VOLT_TUR_SHFT                                                             3
#define HWIO_CALIBRATION16_CPR0_AGING_7_5_BMSK                                                               0x7
#define HWIO_CALIBRATION16_CPR0_AGING_7_5_SHFT                                                                 0

#define HWIO_CALIBRATION17_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd44)
#define HWIO_CALIBRATION17_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd44)
#define HWIO_CALIBRATION17_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION17_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION18_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd48)
#define HWIO_CALIBRATION18_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd48)
#define HWIO_CALIBRATION18_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION18_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION19_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd4c)
#define HWIO_CALIBRATION19_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd4c)
#define HWIO_CALIBRATION19_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION19_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION20_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd50)
#define HWIO_CALIBRATION20_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd50)
#define HWIO_CALIBRATION20_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION20_ATTR                                                                                    0x1
#define HWIO_CALIBRATION20_IN                    \
                in_dword(HWIO_CALIBRATION20_ADDR)
#define HWIO_CALIBRATION20_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION20_ADDR, m)
#define HWIO_CALIBRATION20_CPR3_TARG_VOLT_SVS_0_BMSK                                                  0x80000000
#define HWIO_CALIBRATION20_CPR3_TARG_VOLT_SVS_0_SHFT                                                          31
#define HWIO_CALIBRATION20_CPR3_TARG_VOLT_SUT_BMSK                                                    0x7e000000
#define HWIO_CALIBRATION20_CPR3_TARG_VOLT_SUT_SHFT                                                            25
#define HWIO_CALIBRATION20_CPR2_AGING_BMSK                                                             0x1fe0000
#define HWIO_CALIBRATION20_CPR2_AGING_SHFT                                                                    17
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVS3_BMSK                                               0x1f000
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVS3_SHFT                                                    12
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVS2_BMSK                                                 0xf80
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVS2_SHFT                                                     7
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVS_BMSK                                                   0x7c
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVS_SHFT                                                      2
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVSL1_4_3_BMSK                                              0x3
#define HWIO_CALIBRATION20_CPR2_TARG_VOLT_OFFSET_SVSL1_4_3_SHFT                                                0

#define HWIO_CALIBRATION21_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd54)
#define HWIO_CALIBRATION21_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd54)
#define HWIO_CALIBRATION21_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION21_ATTR                                                                                    0x1
#define HWIO_CALIBRATION21_IN                    \
                in_dword(HWIO_CALIBRATION21_ADDR)
#define HWIO_CALIBRATION21_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION21_ADDR, m)
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_SVSL1_2_0_BMSK                                              0xe0000000
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_SVSL1_2_0_SHFT                                                      29
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_NOM_BMSK                                                    0x1f800000
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_NOM_SHFT                                                            23
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_NOML1_BMSK                                                    0x7e0000
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_NOML1_SHFT                                                          17
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_SUT_BMSK                                                       0x1f800
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_SUT_SHFT                                                            11
#define HWIO_CALIBRATION21_CPR3_TARG_VOLT_SVS2_BMSK                                                        0x7e0
#define HWIO_CALIBRATION21_CPR3_TARG_VOLT_SVS2_SHFT                                                            5
#define HWIO_CALIBRATION21_CPR3_TARG_VOLT_SVS_5_1_BMSK                                                      0x1f
#define HWIO_CALIBRATION21_CPR3_TARG_VOLT_SVS_5_1_SHFT                                                         0

#define HWIO_CALIBRATION22_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd58)
#define HWIO_CALIBRATION22_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd58)
#define HWIO_CALIBRATION22_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION22_ATTR                                                                                    0x1
#define HWIO_CALIBRATION22_IN                    \
                in_dword(HWIO_CALIBRATION22_ADDR)
#define HWIO_CALIBRATION22_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION22_ADDR, m)
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_NOML1_2_0_BMSK                                              0xe0000000
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_NOML1_2_0_SHFT                                                      29
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
#define HWIO_CALIBRATION22_CPR4_TARG_VOLT_SVSL1_5_3_BMSK                                                     0x7
#define HWIO_CALIBRATION22_CPR4_TARG_VOLT_SVSL1_5_3_SHFT                                                       0

#define HWIO_CALIBRATION23_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd5c)
#define HWIO_CALIBRATION23_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd5c)
#define HWIO_CALIBRATION23_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION23_ATTR                                                                                    0x1
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
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_SVSL1_BMSK                                                      0x7e00
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_SVSL1_SHFT                                                           9
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_NOM_BMSK                                                         0x1f8
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_NOM_SHFT                                                             3
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_NOML1_5_3_BMSK                                                     0x7
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_NOML1_5_3_SHFT                                                       0

#define HWIO_CALIBRATION24_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd60)
#define HWIO_CALIBRATION24_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd60)
#define HWIO_CALIBRATION24_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION24_ATTR                                                                                    0x1
#define HWIO_CALIBRATION24_IN                    \
                in_dword(HWIO_CALIBRATION24_ADDR)
#define HWIO_CALIBRATION24_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION24_ADDR, m)
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_TUR_4_0_BMSK                                                0xf8000000
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_TUR_4_0_SHFT                                                        27
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_SVSL1_BMSK                                                   0x7e00000
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_SVSL1_SHFT                                                          21
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_NOM_BMSK                                                      0x1f8000
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_NOM_SHFT                                                            15
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_NOML1_BMSK                                                      0x7e00
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_NOML1_SHFT                                                           9
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_TUR_BMSK                                                         0x1f8
#define HWIO_CALIBRATION24_CPR6_TARG_VOLT_TUR_SHFT                                                             3
#define HWIO_CALIBRATION24_CPR5_TARG_VOLT_OFFSET_SVSL1_4_2_BMSK                                              0x7
#define HWIO_CALIBRATION24_CPR5_TARG_VOLT_OFFSET_SVSL1_4_2_SHFT                                                0

#define HWIO_CALIBRATION25_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd64)
#define HWIO_CALIBRATION25_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd64)
#define HWIO_CALIBRATION25_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION25_ATTR                                                                                    0x1
#define HWIO_CALIBRATION25_IN                    \
                in_dword(HWIO_CALIBRATION25_ADDR)
#define HWIO_CALIBRATION25_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION25_ADDR, m)
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_OFFSET_NOM_2_0_BMSK                                         0xe0000000
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_OFFSET_NOM_2_0_SHFT                                                 29
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_OFFSET_NOML1_BMSK                                           0x1f000000
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_OFFSET_NOML1_SHFT                                                   24
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

#define HWIO_CALIBRATION26_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd68)
#define HWIO_CALIBRATION26_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd68)
#define HWIO_CALIBRATION26_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION26_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION27_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd6c)
#define HWIO_CALIBRATION27_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd6c)
#define HWIO_CALIBRATION27_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION27_ATTR                                                                                    0x1
#define HWIO_CALIBRATION27_IN                    \
                in_dword(HWIO_CALIBRATION27_ADDR)
#define HWIO_CALIBRATION27_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION27_ADDR, m)
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_NOM_BMSK                                             0xf8000000
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_NOM_SHFT                                                     27
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_TUR_BMSK                                              0x7c00000
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_TUR_SHFT                                                     22
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_SVS2_BMSK                                                     0x3f0000
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_SVS2_SHFT                                                           16
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_SVS_BMSK                                                        0xfc00
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_SVS_SHFT                                                            10
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_NOM_BMSK                                                         0x3f0
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_NOM_SHFT                                                             4
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_TUR_5_2_BMSK                                                       0xf
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_TUR_5_2_SHFT                                                         0

#define HWIO_CALIBRATION28_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd70)
#define HWIO_CALIBRATION28_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd70)
#define HWIO_CALIBRATION28_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION28_ATTR                                                                                    0x1
#define HWIO_CALIBRATION28_IN                    \
                in_dword(HWIO_CALIBRATION28_ADDR)
#define HWIO_CALIBRATION28_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION28_ADDR, m)
#define HWIO_CALIBRATION28_CPR9_TARG_VOLT_TUR_3_0_BMSK                                                0xf0000000
#define HWIO_CALIBRATION28_CPR9_TARG_VOLT_TUR_3_0_SHFT                                                        28
#define HWIO_CALIBRATION28_CPR8_AGING_BMSK                                                             0xff00000
#define HWIO_CALIBRATION28_CPR8_AGING_SHFT                                                                    20
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVS3_BMSK                                               0xf8000
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVS3_SHFT                                                    15
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVS2_BMSK                                                0x7c00
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVS2_SHFT                                                    10
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVS_BMSK                                                  0x3e0
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVS_SHFT                                                      5
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVSL1_BMSK                                                 0x1f
#define HWIO_CALIBRATION28_CPR8_TARG_VOLT_OFFSET_SVSL1_SHFT                                                    0

#define HWIO_CALIBRATION29_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd74)
#define HWIO_CALIBRATION29_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd74)
#define HWIO_CALIBRATION29_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION29_ATTR                                                                                    0x1
#define HWIO_CALIBRATION29_IN                    \
                in_dword(HWIO_CALIBRATION29_ADDR)
#define HWIO_CALIBRATION29_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION29_ADDR, m)
#define HWIO_CALIBRATION29_CPR9_TURBO_QUOT_MIN_BMSK                                                   0xfff00000
#define HWIO_CALIBRATION29_CPR9_TURBO_QUOT_MIN_SHFT                                                           20
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_SVS2_BMSK                                                      0xfc000
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_SVS2_SHFT                                                           14
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_SVS_BMSK                                                        0x3f00
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_SVS_SHFT                                                             8
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_NOM_BMSK                                                          0xfc
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_NOM_SHFT                                                             2
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_TUR_5_4_BMSK                                                       0x3
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_TUR_5_4_SHFT                                                         0

#define HWIO_CALIBRATION30_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd78)
#define HWIO_CALIBRATION30_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd78)
#define HWIO_CALIBRATION30_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION30_ATTR                                                                                    0x1
#define HWIO_CALIBRATION30_IN                    \
                in_dword(HWIO_CALIBRATION30_ADDR)
#define HWIO_CALIBRATION30_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION30_ADDR, m)
#define HWIO_CALIBRATION30_CPR9_SVS2_QUOT_MIN_7_0_BMSK                                                0xff000000
#define HWIO_CALIBRATION30_CPR9_SVS2_QUOT_MIN_7_0_SHFT                                                        24
#define HWIO_CALIBRATION30_CPR9_SVS_QUOT_MIN_BMSK                                                       0xfff000
#define HWIO_CALIBRATION30_CPR9_SVS_QUOT_MIN_SHFT                                                             12
#define HWIO_CALIBRATION30_CPR9_NOMINAL_QUOT_MIN_BMSK                                                      0xfff
#define HWIO_CALIBRATION30_CPR9_NOMINAL_QUOT_MIN_SHFT                                                          0

#define HWIO_CALIBRATION31_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd7c)
#define HWIO_CALIBRATION31_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd7c)
#define HWIO_CALIBRATION31_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION31_ATTR                                                                                    0x1
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
#define HWIO_CALIBRATION31_CPR9_QUOT_OFFSET_BMSK                                                           0xff0
#define HWIO_CALIBRATION31_CPR9_QUOT_OFFSET_SHFT                                                               4
#define HWIO_CALIBRATION31_CPR9_SVS2_QUOT_MIN_11_8_BMSK                                                      0xf
#define HWIO_CALIBRATION31_CPR9_SVS2_QUOT_MIN_11_8_SHFT                                                        0

#define HWIO_CALIBRATION32_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd80)
#define HWIO_CALIBRATION32_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd80)
#define HWIO_CALIBRATION32_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION32_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION33_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd84)
#define HWIO_CALIBRATION33_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd84)
#define HWIO_CALIBRATION33_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION33_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION34_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd88)
#define HWIO_CALIBRATION34_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd88)
#define HWIO_CALIBRATION34_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION34_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION35_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd8c)
#define HWIO_CALIBRATION35_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd8c)
#define HWIO_CALIBRATION35_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION35_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION36_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd90)
#define HWIO_CALIBRATION36_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd90)
#define HWIO_CALIBRATION36_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION36_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION37_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd94)
#define HWIO_CALIBRATION37_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd94)
#define HWIO_CALIBRATION37_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION37_ATTR                                                                                    0x1
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
#define HWIO_CALIBRATION37_CPR11_AGING_BMSK                                                               0x3fc0
#define HWIO_CALIBRATION37_CPR11_AGING_SHFT                                                                    6
#define HWIO_CALIBRATION37_CPR11_QUOT_OFFSET_7_2_BMSK                                                       0x3f
#define HWIO_CALIBRATION37_CPR11_QUOT_OFFSET_7_2_SHFT                                                          0

#define HWIO_CALIBRATION38_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd98)
#define HWIO_CALIBRATION38_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd98)
#define HWIO_CALIBRATION38_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION38_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION39_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xd9c)
#define HWIO_CALIBRATION39_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xd9c)
#define HWIO_CALIBRATION39_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION39_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION40_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xda0)
#define HWIO_CALIBRATION40_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xda0)
#define HWIO_CALIBRATION40_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION40_ATTR                                                                                    0x1
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
#define HWIO_CALIBRATION40_CPR_LOCAL_RC_BMSK                                                             0x70000
#define HWIO_CALIBRATION40_CPR_LOCAL_RC_SHFT                                                                  16
#define HWIO_CALIBRATION40_CPR12_QUOT_OFFSET_BMSK                                                         0xff00
#define HWIO_CALIBRATION40_CPR12_QUOT_OFFSET_SHFT                                                              8
#define HWIO_CALIBRATION40_CPR12_SVS2_QUOT_MIN_11_4_BMSK                                                    0xff
#define HWIO_CALIBRATION40_CPR12_SVS2_QUOT_MIN_11_4_SHFT                                                       0

#define HWIO_CALIBRATION41_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xda4)
#define HWIO_CALIBRATION41_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xda4)
#define HWIO_CALIBRATION41_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION41_ATTR                                                                                    0x1
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
#define HWIO_CALIBRATION41_CPR_LPICX_MODE_DISABLE_BMSK                                                     0x700
#define HWIO_CALIBRATION41_CPR_LPICX_MODE_DISABLE_SHFT                                                         8
#define HWIO_CALIBRATION41_CPR_DDR_MODE_DISABLE_BMSK                                                        0xe0
#define HWIO_CALIBRATION41_CPR_DDR_MODE_DISABLE_SHFT                                                           5
#define HWIO_CALIBRATION41_CPR_LPIMX_MODE_DISABLE_BMSK                                                      0x1c
#define HWIO_CALIBRATION41_CPR_LPIMX_MODE_DISABLE_SHFT                                                         2
#define HWIO_CALIBRATION41_CPR_MXC_MODE_DISABLE_2_1_BMSK                                                     0x3
#define HWIO_CALIBRATION41_CPR_MXC_MODE_DISABLE_2_1_SHFT                                                       0

#define HWIO_CALIBRATION42_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xda8)
#define HWIO_CALIBRATION42_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xda8)
#define HWIO_CALIBRATION42_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION42_ATTR                                                                                    0x1
#define HWIO_CALIBRATION42_IN                    \
                in_dword(HWIO_CALIBRATION42_ADDR)
#define HWIO_CALIBRATION42_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION42_ADDR, m)
#define HWIO_CALIBRATION42_CPR12_TURL3_QUOT_MIN_10_0_BMSK                                             0xffe00000
#define HWIO_CALIBRATION42_CPR12_TURL3_QUOT_MIN_10_0_SHFT                                                     21
#define HWIO_CALIBRATION42_CPR12_TARG_VOLT_TURL3_BMSK                                                   0x1f8000
#define HWIO_CALIBRATION42_CPR12_TARG_VOLT_TURL3_SHFT                                                         15
#define HWIO_CALIBRATION42_CPR5_TARG_VOLT_OFFSET_SVSL2_BMSK                                               0x7c00
#define HWIO_CALIBRATION42_CPR5_TARG_VOLT_OFFSET_SVSL2_SHFT                                                   10
#define HWIO_CALIBRATION42_CPR4_TARG_VOLT_OFFSET_SVSL2_BMSK                                                0x3e0
#define HWIO_CALIBRATION42_CPR4_TARG_VOLT_OFFSET_SVSL2_SHFT                                                    5
#define HWIO_CALIBRATION42_CPR_MMCX_MODE_DISABLE_BMSK                                                       0x1c
#define HWIO_CALIBRATION42_CPR_MMCX_MODE_DISABLE_SHFT                                                          2
#define HWIO_CALIBRATION42_CPR_GLOBAL_RC_2_1_BMSK                                                            0x3
#define HWIO_CALIBRATION42_CPR_GLOBAL_RC_2_1_SHFT                                                              0

#define HWIO_CALIBRATION43_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdac)
#define HWIO_CALIBRATION43_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdac)
#define HWIO_CALIBRATION43_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION43_ATTR                                                                                    0x1
#define HWIO_CALIBRATION43_IN                    \
                in_dword(HWIO_CALIBRATION43_ADDR)
#define HWIO_CALIBRATION43_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION43_ADDR, m)
#define HWIO_CALIBRATION43_CALIBRATION_1407_1406_BMSK                                                 0xc0000000
#define HWIO_CALIBRATION43_CALIBRATION_1407_1406_SHFT                                                         30
#define HWIO_CALIBRATION43_CPR5_TARG_VOLT_OFFSET_SVS3_BMSK                                            0x3e000000
#define HWIO_CALIBRATION43_CPR5_TARG_VOLT_OFFSET_SVS3_SHFT                                                    25
#define HWIO_CALIBRATION43_CPR4_TARG_VOLT_OFFSET_SVS3_BMSK                                             0x1f00000
#define HWIO_CALIBRATION43_CPR4_TARG_VOLT_OFFSET_SVS3_SHFT                                                    20
#define HWIO_CALIBRATION43_CPR_RESERVED_BMSK                                                             0xffffe
#define HWIO_CALIBRATION43_CPR_RESERVED_SHFT                                                                   1
#define HWIO_CALIBRATION43_CPR12_TURL3_QUOT_MIN_11_BMSK                                                      0x1
#define HWIO_CALIBRATION43_CPR12_TURL3_QUOT_MIN_11_SHFT                                                        0

#define HWIO_CALIBRATION44_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdb0)
#define HWIO_CALIBRATION44_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdb0)
#define HWIO_CALIBRATION44_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION44_ATTR                                                                                    0x1
#define HWIO_CALIBRATION44_IN                    \
                in_dword(HWIO_CALIBRATION44_ADDR)
#define HWIO_CALIBRATION44_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION44_ADDR, m)
#define HWIO_CALIBRATION44_CALIBRATION_1439_1438_BMSK                                                 0xc0000000
#define HWIO_CALIBRATION44_CALIBRATION_1439_1438_SHFT                                                         30
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_SVS3_BMSK                                            0x3e000000
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_SVS3_SHFT                                                    25
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_SVS2_BMSK                                             0x1f00000
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_SVS2_SHFT                                                    20
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_SVS_BMSK                                                0xf8000
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_SVS_SHFT                                                     15
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_SVSL1_BMSK                                               0x7c00
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_SVSL1_SHFT                                                   10
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_NOM_BMSK                                                  0x3e0
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_NOM_SHFT                                                      5
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_TUR_BMSK                                                   0x1f
#define HWIO_CALIBRATION44_CPR6_TARG_VOLT_OFFSET_TUR_SHFT                                                      0

#define HWIO_CALIBRATION45_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdb4)
#define HWIO_CALIBRATION45_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdb4)
#define HWIO_CALIBRATION45_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION45_ATTR                                                                                    0x1
#define HWIO_CALIBRATION45_IN                    \
                in_dword(HWIO_CALIBRATION45_ADDR)
#define HWIO_CALIBRATION45_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION45_ADDR, m)
#define HWIO_CALIBRATION45_AOSS_K_5_0_BMSK                                                            0xfc000000
#define HWIO_CALIBRATION45_AOSS_K_5_0_SHFT                                                                    26
#define HWIO_CALIBRATION45_CALIBRATION_1465_1460_BMSK                                                  0x3f00000
#define HWIO_CALIBRATION45_CALIBRATION_1465_1460_SHFT                                                         20
#define HWIO_CALIBRATION45_CPR5_TARG_VOLT_OFFSET_SVS2_BMSK                                               0xf8000
#define HWIO_CALIBRATION45_CPR5_TARG_VOLT_OFFSET_SVS2_SHFT                                                    15
#define HWIO_CALIBRATION45_CPR5_TARG_VOLT_OFFSET_SVS_BMSK                                                 0x7c00
#define HWIO_CALIBRATION45_CPR5_TARG_VOLT_OFFSET_SVS_SHFT                                                     10
#define HWIO_CALIBRATION45_CPR4_TARG_VOLT_OFFSET_SVS2_BMSK                                                 0x3e0
#define HWIO_CALIBRATION45_CPR4_TARG_VOLT_OFFSET_SVS2_SHFT                                                     5
#define HWIO_CALIBRATION45_CPR4_TARG_VOLT_OFFSET_SVS_BMSK                                                   0x1f
#define HWIO_CALIBRATION45_CPR4_TARG_VOLT_OFFSET_SVS_SHFT                                                      0

#define HWIO_CALIBRATION46_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdb8)
#define HWIO_CALIBRATION46_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdb8)
#define HWIO_CALIBRATION46_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION46_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION47_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdbc)
#define HWIO_CALIBRATION47_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdbc)
#define HWIO_CALIBRATION47_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION47_ATTR                                                                                    0x1
#define HWIO_CALIBRATION47_IN                    \
                in_dword(HWIO_CALIBRATION47_ADDR)
#define HWIO_CALIBRATION47_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION47_ADDR, m)
#define HWIO_CALIBRATION47_CALIBRATION_1535_1524_BMSK                                                 0xfff00000
#define HWIO_CALIBRATION47_CALIBRATION_1535_1524_SHFT                                                         20
#define HWIO_CALIBRATION47_AOSS_TDOPCODE_BMSK                                                            0xe0000
#define HWIO_CALIBRATION47_AOSS_TDOPCODE_SHFT                                                                 17
#define HWIO_CALIBRATION47_AOSS_RDOPCODE_BMSK                                                            0x1c000
#define HWIO_CALIBRATION47_AOSS_RDOPCODE_SHFT                                                                 14
#define HWIO_CALIBRATION47_AOSS_P1_17_4_BMSK                                                              0x3fff
#define HWIO_CALIBRATION47_AOSS_P1_17_4_SHFT                                                                   0

#define HWIO_CALIBRATION48_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdc0)
#define HWIO_CALIBRATION48_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdc0)
#define HWIO_CALIBRATION48_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION48_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION49_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdc4)
#define HWIO_CALIBRATION49_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdc4)
#define HWIO_CALIBRATION49_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION49_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION50_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdc8)
#define HWIO_CALIBRATION50_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdc8)
#define HWIO_CALIBRATION50_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION50_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION51_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdcc)
#define HWIO_CALIBRATION51_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdcc)
#define HWIO_CALIBRATION51_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION51_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION52_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdd0)
#define HWIO_CALIBRATION52_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdd0)
#define HWIO_CALIBRATION52_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION52_ATTR                                                                                    0x1
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

#define HWIO_CALIBRATION53_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdd4)
#define HWIO_CALIBRATION53_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdd4)
#define HWIO_CALIBRATION53_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION53_ATTR                                                                                    0x1
#define HWIO_CALIBRATION53_IN                    \
                in_dword(HWIO_CALIBRATION53_ADDR)
#define HWIO_CALIBRATION53_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION53_ADDR, m)
#define HWIO_CALIBRATION53_CALIBRATION_1727_1724_BMSK                                                 0xf0000000
#define HWIO_CALIBRATION53_CALIBRATION_1727_1724_SHFT                                                         28
#define HWIO_CALIBRATION53_TSENS_CAL_SEL_BMSK                                                          0xe000000
#define HWIO_CALIBRATION53_TSENS_CAL_SEL_SHFT                                                                 25
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

#define HWIO_CALIBRATION54_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdd8)
#define HWIO_CALIBRATION54_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdd8)
#define HWIO_CALIBRATION54_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION54_ATTR                                                                                    0x1
#define HWIO_CALIBRATION54_IN                    \
                in_dword(HWIO_CALIBRATION54_ADDR)
#define HWIO_CALIBRATION54_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION54_ADDR, m)
#define HWIO_CALIBRATION54_CALIBRATION_1759_1728_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION54_CALIBRATION_1759_1728_SHFT                                                          0

#define HWIO_CALIBRATION55_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xddc)
#define HWIO_CALIBRATION55_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xddc)
#define HWIO_CALIBRATION55_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION55_ATTR                                                                                    0x1
#define HWIO_CALIBRATION55_IN                    \
                in_dword(HWIO_CALIBRATION55_ADDR)
#define HWIO_CALIBRATION55_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION55_ADDR, m)
#define HWIO_CALIBRATION55_CALIBRATION_1791_1770_BMSK                                                 0xfffffc00
#define HWIO_CALIBRATION55_CALIBRATION_1791_1770_SHFT                                                         10
#define HWIO_CALIBRATION55_FACTOR_FUSE_NSPRAIL_BMSK                                                        0x3e0
#define HWIO_CALIBRATION55_FACTOR_FUSE_NSPRAIL_SHFT                                                            5
#define HWIO_CALIBRATION55_FACTOR_FUSE_CPURAIL_BMSK                                                         0x1f
#define HWIO_CALIBRATION55_FACTOR_FUSE_CPURAIL_SHFT                                                            0

#define HWIO_CALIBRATION56_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xde0)
#define HWIO_CALIBRATION56_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xde0)
#define HWIO_CALIBRATION56_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION56_ATTR                                                                                    0x1
#define HWIO_CALIBRATION56_IN                    \
                in_dword(HWIO_CALIBRATION56_ADDR)
#define HWIO_CALIBRATION56_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION56_ADDR, m)
#define HWIO_CALIBRATION56_DDR_FUSE_BIG3_3_0_BMSK                                                     0xf0000000
#define HWIO_CALIBRATION56_DDR_FUSE_BIG3_3_0_SHFT                                                             28
#define HWIO_CALIBRATION56_DDR_FUSE_BIG2_BMSK                                                          0xfc00000
#define HWIO_CALIBRATION56_DDR_FUSE_BIG2_SHFT                                                                 22
#define HWIO_CALIBRATION56_DDR_FUSE_BIG1_BMSK                                                           0x3f0000
#define HWIO_CALIBRATION56_DDR_FUSE_BIG1_SHFT                                                                 16
#define HWIO_CALIBRATION56_DACC_COMP_VREF_SEL_FUSE2_BMSK                                                  0xff00
#define HWIO_CALIBRATION56_DACC_COMP_VREF_SEL_FUSE2_SHFT                                                       8
#define HWIO_CALIBRATION56_DACC_COMP_VREF_SEL_FUSE1_BMSK                                                    0xff
#define HWIO_CALIBRATION56_DACC_COMP_VREF_SEL_FUSE1_SHFT                                                       0

#define HWIO_CALIBRATION57_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xde4)
#define HWIO_CALIBRATION57_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xde4)
#define HWIO_CALIBRATION57_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION57_ATTR                                                                                    0x1
#define HWIO_CALIBRATION57_IN                    \
                in_dword(HWIO_CALIBRATION57_ADDR)
#define HWIO_CALIBRATION57_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION57_ADDR, m)
#define HWIO_CALIBRATION57_ISENSE_FUSE_CURRENT_NSP_RESTCX_BMSK                                        0xff800000
#define HWIO_CALIBRATION57_ISENSE_FUSE_CURRENT_NSP_RESTCX_SHFT                                                23
#define HWIO_CALIBRATION57_DDR_FUSE_SMALL_3_BMSK                                                        0x600000
#define HWIO_CALIBRATION57_DDR_FUSE_SMALL_3_SHFT                                                              21
#define HWIO_CALIBRATION57_DDR_FUSE_SMALL_2_BMSK                                                        0x180000
#define HWIO_CALIBRATION57_DDR_FUSE_SMALL_2_SHFT                                                              19
#define HWIO_CALIBRATION57_DDR_FUSE_SMALL_1_BMSK                                                         0x60000
#define HWIO_CALIBRATION57_DDR_FUSE_SMALL_1_SHFT                                                              17
#define HWIO_CALIBRATION57_DDR_FUSE_MED_3_BMSK                                                           0x1f000
#define HWIO_CALIBRATION57_DDR_FUSE_MED_3_SHFT                                                                12
#define HWIO_CALIBRATION57_DDR_FUSE_MED_2_BMSK                                                             0xf80
#define HWIO_CALIBRATION57_DDR_FUSE_MED_2_SHFT                                                                 7
#define HWIO_CALIBRATION57_DDR_FUSE_MED_1_BMSK                                                              0x7c
#define HWIO_CALIBRATION57_DDR_FUSE_MED_1_SHFT                                                                 2
#define HWIO_CALIBRATION57_DDR_FUSE_BIG3_5_4_BMSK                                                            0x3
#define HWIO_CALIBRATION57_DDR_FUSE_BIG3_5_4_SHFT                                                              0

#define HWIO_CALIBRATION58_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xde8)
#define HWIO_CALIBRATION58_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xde8)
#define HWIO_CALIBRATION58_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION58_ATTR                                                                                    0x1
#define HWIO_CALIBRATION58_IN                    \
                in_dword(HWIO_CALIBRATION58_ADDR)
#define HWIO_CALIBRATION58_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION58_ADDR, m)
#define HWIO_CALIBRATION58_OPAMP_FUSE_NSPRAIL_HMX_WS_1_0_BMSK                                         0xc0000000
#define HWIO_CALIBRATION58_OPAMP_FUSE_NSPRAIL_HMX_WS_1_0_SHFT                                                 30
#define HWIO_CALIBRATION58_OPAMP_FUSE_NSPRAIL_HVX_WS_BMSK                                             0x3f000000
#define HWIO_CALIBRATION58_OPAMP_FUSE_NSPRAIL_HVX_WS_SHFT                                                     24
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU7_WS_BMSK                                              0xfc0000
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU7_WS_SHFT                                                    18
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU6_WS_BMSK                                               0x3f000
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU6_WS_SHFT                                                    12
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU5_WS_BMSK                                                 0xfc0
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU5_WS_SHFT                                                     6
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU4_WS_BMSK                                                  0x3f
#define HWIO_CALIBRATION58_OPAMP_FUSE_CPURAIL_CPU4_WS_SHFT                                                     0

#define HWIO_CALIBRATION59_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdec)
#define HWIO_CALIBRATION59_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdec)
#define HWIO_CALIBRATION59_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION59_ATTR                                                                                    0x1
#define HWIO_CALIBRATION59_IN                    \
                in_dword(HWIO_CALIBRATION59_ADDR)
#define HWIO_CALIBRATION59_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION59_ADDR, m)
#define HWIO_CALIBRATION59_ISENSE_FUSE_CURRENT_CPU5_F1_7_0_BMSK                                       0xff000000
#define HWIO_CALIBRATION59_ISENSE_FUSE_CURRENT_CPU5_F1_7_0_SHFT                                               24
#define HWIO_CALIBRATION59_ISENSE_FUSE_CURRENT_CPU4_F2_BMSK                                             0xffc000
#define HWIO_CALIBRATION59_ISENSE_FUSE_CURRENT_CPU4_F2_SHFT                                                   14
#define HWIO_CALIBRATION59_ISENSE_FUSE_CURRENT_CPU4_F1_BMSK                                               0x3ff0
#define HWIO_CALIBRATION59_ISENSE_FUSE_CURRENT_CPU4_F1_SHFT                                                    4
#define HWIO_CALIBRATION59_OPAMP_FUSE_NSPRAIL_HMX_WS_5_2_BMSK                                                0xf
#define HWIO_CALIBRATION59_OPAMP_FUSE_NSPRAIL_HMX_WS_5_2_SHFT                                                  0

#define HWIO_CALIBRATION60_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdf0)
#define HWIO_CALIBRATION60_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdf0)
#define HWIO_CALIBRATION60_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION60_ATTR                                                                                    0x1
#define HWIO_CALIBRATION60_IN                    \
                in_dword(HWIO_CALIBRATION60_ADDR)
#define HWIO_CALIBRATION60_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION60_ADDR, m)
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU6_F2_BMSK                                           0xffc00000
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU6_F2_SHFT                                                   22
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU6_F1_BMSK                                             0x3ff000
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU6_F1_SHFT                                                   12
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU5_F2_BMSK                                                0xffc
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU5_F2_SHFT                                                    2
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU5_F1_9_8_BMSK                                              0x3
#define HWIO_CALIBRATION60_ISENSE_FUSE_CURRENT_CPU5_F1_9_8_SHFT                                                0

#define HWIO_CALIBRATION61_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdf4)
#define HWIO_CALIBRATION61_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdf4)
#define HWIO_CALIBRATION61_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION61_ATTR                                                                                    0x1
#define HWIO_CALIBRATION61_IN                    \
                in_dword(HWIO_CALIBRATION61_ADDR)
#define HWIO_CALIBRATION61_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION61_ADDR, m)
#define HWIO_CALIBRATION61_CALIBRATION_1983_1982_BMSK                                                 0xc0000000
#define HWIO_CALIBRATION61_CALIBRATION_1983_1982_SHFT                                                         30
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_HVX_F1_BMSK                                            0x3ff00000
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_HVX_F1_SHFT                                                    20
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_CPU7_F2_BMSK                                              0xffc00
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_CPU7_F2_SHFT                                                   10
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_CPU7_F1_BMSK                                                0x3ff
#define HWIO_CALIBRATION61_ISENSE_FUSE_CURRENT_CPU7_F1_SHFT                                                    0

#define HWIO_CALIBRATION62_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdf8)
#define HWIO_CALIBRATION62_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdf8)
#define HWIO_CALIBRATION62_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION62_ATTR                                                                                    0x1
#define HWIO_CALIBRATION62_IN                    \
                in_dword(HWIO_CALIBRATION62_ADDR)
#define HWIO_CALIBRATION62_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION62_ADDR, m)
#define HWIO_CALIBRATION62_GFX_FUSE_CDYN_REVISON_BIT_BMSK                                             0xc0000000
#define HWIO_CALIBRATION62_GFX_FUSE_CDYN_REVISON_BIT_SHFT                                                     30
#define HWIO_CALIBRATION62_GFX_FUSE_CDYN_BUMP_VOLT_V_LF_BMSK                                          0x3e000000
#define HWIO_CALIBRATION62_GFX_FUSE_CDYN_BUMP_VOLT_V_LF_SHFT                                                  25
#define HWIO_CALIBRATION62_GFX_FUSE_CDYN_BUMP_VOLT_V_HF_BMSK                                           0x1ff0000
#define HWIO_CALIBRATION62_GFX_FUSE_CDYN_BUMP_VOLT_V_HF_SHFT                                                  16
#define HWIO_CALIBRATION62_GFX_FUSE_CDYN_CURRENT_I_LF_BMSK                                                0xff00
#define HWIO_CALIBRATION62_GFX_FUSE_CDYN_CURRENT_I_LF_SHFT                                                     8
#define HWIO_CALIBRATION62_GFX_FUSE_CDYN_CURRENT_I_HF_BMSK                                                  0xff
#define HWIO_CALIBRATION62_GFX_FUSE_CDYN_CURRENT_I_HF_SHFT                                                     0

#define HWIO_CALIBRATION63_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xdfc)
#define HWIO_CALIBRATION63_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xdfc)
#define HWIO_CALIBRATION63_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION63_ATTR                                                                                    0x1
#define HWIO_CALIBRATION63_IN                    \
                in_dword(HWIO_CALIBRATION63_ADDR)
#define HWIO_CALIBRATION63_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION63_ADDR, m)
#define HWIO_CALIBRATION63_ROCOUNT_FUSE_CPURAIL_1_0_BMSK                                              0xc0000000
#define HWIO_CALIBRATION63_ROCOUNT_FUSE_CPURAIL_1_0_SHFT                                                      30
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_HMX_F2_BMSK                                            0x3ff00000
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_HMX_F2_SHFT                                                    20
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_HMX_F1_BMSK                                               0xffc00
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_HMX_F1_SHFT                                                    10
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_HVX_F2_BMSK                                                 0x3ff
#define HWIO_CALIBRATION63_ISENSE_FUSE_CURRENT_HVX_F2_SHFT                                                     0

#define HWIO_CALIBRATION64_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe00)
#define HWIO_CALIBRATION64_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe00)
#define HWIO_CALIBRATION64_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION64_ATTR                                                                                    0x1
#define HWIO_CALIBRATION64_IN                    \
                in_dword(HWIO_CALIBRATION64_ADDR)
#define HWIO_CALIBRATION64_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION64_ADDR, m)
#define HWIO_CALIBRATION64_OPAMP_FUSE_CPURAIL_CPU5_FT_4_0_BMSK                                        0xf8000000
#define HWIO_CALIBRATION64_OPAMP_FUSE_CPURAIL_CPU5_FT_4_0_SHFT                                                27
#define HWIO_CALIBRATION64_OPAMP_FUSE_CPURAIL_CPU4_FT_BMSK                                             0x7e00000
#define HWIO_CALIBRATION64_OPAMP_FUSE_CPURAIL_CPU4_FT_SHFT                                                    21
#define HWIO_CALIBRATION64_ISENSE_FUSE_REVISION_CONTROL_WS_BMSK                                         0x1c0000
#define HWIO_CALIBRATION64_ISENSE_FUSE_REVISION_CONTROL_WS_SHFT                                               18
#define HWIO_CALIBRATION64_CALIBRATION_2065_2064_BMSK                                                    0x30000
#define HWIO_CALIBRATION64_CALIBRATION_2065_2064_SHFT                                                         16
#define HWIO_CALIBRATION64_ROCOUNT_FUSE_NSPRAIL_BMSK                                                      0xff00
#define HWIO_CALIBRATION64_ROCOUNT_FUSE_NSPRAIL_SHFT                                                           8
#define HWIO_CALIBRATION64_CALIBRATION_2055_2054_BMSK                                                       0xc0
#define HWIO_CALIBRATION64_CALIBRATION_2055_2054_SHFT                                                          6
#define HWIO_CALIBRATION64_ROCOUNT_FUSE_CPURAIL_7_2_BMSK                                                    0x3f
#define HWIO_CALIBRATION64_ROCOUNT_FUSE_CPURAIL_7_2_SHFT                                                       0

#define HWIO_CALIBRATION65_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe04)
#define HWIO_CALIBRATION65_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe04)
#define HWIO_CALIBRATION65_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION65_ATTR                                                                                    0x1
#define HWIO_CALIBRATION65_IN                    \
                in_dword(HWIO_CALIBRATION65_ADDR)
#define HWIO_CALIBRATION65_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION65_ADDR, m)
#define HWIO_CALIBRATION65_VSENSE_FUSE1_3_0_BMSK                                                      0xf0000000
#define HWIO_CALIBRATION65_VSENSE_FUSE1_3_0_SHFT                                                              28
#define HWIO_CALIBRATION65_ISENSE_FUSE_REVISION_CONTROL_FT_BMSK                                        0xe000000
#define HWIO_CALIBRATION65_ISENSE_FUSE_REVISION_CONTROL_FT_SHFT                                               25
#define HWIO_CALIBRATION65_OPAMP_FUSE_NSPRAIL_HMX_FT_BMSK                                              0x1f80000
#define HWIO_CALIBRATION65_OPAMP_FUSE_NSPRAIL_HMX_FT_SHFT                                                     19
#define HWIO_CALIBRATION65_OPAMP_FUSE_NSPRAIL_HVX_FT_BMSK                                                0x7e000
#define HWIO_CALIBRATION65_OPAMP_FUSE_NSPRAIL_HVX_FT_SHFT                                                     13
#define HWIO_CALIBRATION65_OPAMP_FUSE_CPURAIL_CPU7_FT_BMSK                                                0x1f80
#define HWIO_CALIBRATION65_OPAMP_FUSE_CPURAIL_CPU7_FT_SHFT                                                     7
#define HWIO_CALIBRATION65_OPAMP_FUSE_CPURAIL_CPU6_FT_BMSK                                                  0x7e
#define HWIO_CALIBRATION65_OPAMP_FUSE_CPURAIL_CPU6_FT_SHFT                                                     1
#define HWIO_CALIBRATION65_OPAMP_FUSE_CPURAIL_CPU5_FT_5_BMSK                                                 0x1
#define HWIO_CALIBRATION65_OPAMP_FUSE_CPURAIL_CPU5_FT_5_SHFT                                                   0

#define HWIO_CALIBRATION66_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe08)
#define HWIO_CALIBRATION66_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe08)
#define HWIO_CALIBRATION66_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION66_ATTR                                                                                    0x1
#define HWIO_CALIBRATION66_IN                    \
                in_dword(HWIO_CALIBRATION66_ADDR)
#define HWIO_CALIBRATION66_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION66_ADDR, m)
#define HWIO_CALIBRATION66_VSENSE_FUSE2_0_BMSK                                                        0x80000000
#define HWIO_CALIBRATION66_VSENSE_FUSE2_0_SHFT                                                                31
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S8_BMSK                                                       0x70000000
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S8_SHFT                                                               28
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S7_BMSK                                                        0xe000000
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S7_SHFT                                                               25
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S6_BMSK                                                        0x1c00000
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S6_SHFT                                                               22
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S5_BMSK                                                         0x380000
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S5_SHFT                                                               19
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S4_BMSK                                                          0x70000
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S4_SHFT                                                               16
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S3_BMSK                                                           0xe000
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S3_SHFT                                                               13
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S2_BMSK                                                           0x1c00
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S2_SHFT                                                               10
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S1_BMSK                                                            0x380
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S1_SHFT                                                                7
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S0_BMSK                                                             0x70
#define HWIO_CALIBRATION66_VSENSE_FUSE1_S0_SHFT                                                                4
#define HWIO_CALIBRATION66_VSENSE_FUSE1_7_4_BMSK                                                             0xf
#define HWIO_CALIBRATION66_VSENSE_FUSE1_7_4_SHFT                                                               0

#define HWIO_CALIBRATION67_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe0c)
#define HWIO_CALIBRATION67_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe0c)
#define HWIO_CALIBRATION67_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION67_ATTR                                                                                    0x1
#define HWIO_CALIBRATION67_IN                    \
                in_dword(HWIO_CALIBRATION67_ADDR)
#define HWIO_CALIBRATION67_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION67_ADDR, m)
#define HWIO_CALIBRATION67_DDR_CH0_LP4_DCC_PLL0_2133_3_0_BMSK                                         0xf0000000
#define HWIO_CALIBRATION67_DDR_CH0_LP4_DCC_PLL0_2133_3_0_SHFT                                                 28
#define HWIO_CALIBRATION67_VSENSE_FUSE_REVISION_CONTROL_BMSK                                           0xe000000
#define HWIO_CALIBRATION67_VSENSE_FUSE_REVISION_CONTROL_SHFT                                                  25
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S8_BMSK                                                        0x1800000
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S8_SHFT                                                               23
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S7_BMSK                                                         0x600000
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S7_SHFT                                                               21
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S6_BMSK                                                         0x180000
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S6_SHFT                                                               19
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S5_BMSK                                                          0x60000
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S5_SHFT                                                               17
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S4_BMSK                                                          0x18000
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S4_SHFT                                                               15
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S3_BMSK                                                           0x6000
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S3_SHFT                                                               13
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S2_BMSK                                                           0x1800
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S2_SHFT                                                               11
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S1_BMSK                                                            0x600
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S1_SHFT                                                                9
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S0_BMSK                                                            0x180
#define HWIO_CALIBRATION67_VSENSE_FUSE2_S0_SHFT                                                                7
#define HWIO_CALIBRATION67_VSENSE_FUSE2_7_1_BMSK                                                            0x7f
#define HWIO_CALIBRATION67_VSENSE_FUSE2_7_1_SHFT                                                               0

#define HWIO_CALIBRATION68_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe10)
#define HWIO_CALIBRATION68_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe10)
#define HWIO_CALIBRATION68_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION68_ATTR                                                                                    0x1
#define HWIO_CALIBRATION68_IN                    \
                in_dword(HWIO_CALIBRATION68_ADDR)
#define HWIO_CALIBRATION68_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION68_ADDR, m)
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DQ1_DCC_IO_DQS_2133_BMSK                                       0xfc000000
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DQ1_DCC_IO_DQS_2133_SHFT                                               26
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DQ1_DCC_CLK_ADJ_2133_BMSK                                       0x3f00000
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DQ1_DCC_CLK_ADJ_2133_SHFT                                              20
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DQ0_DCC_IO_DQS_2133_BMSK                                          0xfc000
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DQ0_DCC_IO_DQS_2133_SHFT                                               14
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DQ0_DCC_CLK_ADJ_2133_BMSK                                          0x3f00
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DQ0_DCC_CLK_ADJ_2133_SHFT                                               8
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DCC_PLL1_2133_BMSK                                                   0xfc
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DCC_PLL1_2133_SHFT                                                      2
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DCC_PLL0_2133_5_4_BMSK                                                0x3
#define HWIO_CALIBRATION68_DDR_CH0_LP4_DCC_PLL0_2133_5_4_SHFT                                                  0

#define HWIO_CALIBRATION69_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe14)
#define HWIO_CALIBRATION69_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe14)
#define HWIO_CALIBRATION69_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION69_ATTR                                                                                    0x1
#define HWIO_CALIBRATION69_IN                    \
                in_dword(HWIO_CALIBRATION69_ADDR)
#define HWIO_CALIBRATION69_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION69_ADDR, m)
#define HWIO_CALIBRATION69_DDR_CH1_LP4_DQ0_DCC_IO_DQS_2133_1_0_BMSK                                   0xc0000000
#define HWIO_CALIBRATION69_DDR_CH1_LP4_DQ0_DCC_IO_DQS_2133_1_0_SHFT                                           30
#define HWIO_CALIBRATION69_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_2133_BMSK                                      0x3f000000
#define HWIO_CALIBRATION69_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_2133_SHFT                                              24
#define HWIO_CALIBRATION69_DDR_CH1_LP4_DCC_PLL1_2133_BMSK                                               0xfc0000
#define HWIO_CALIBRATION69_DDR_CH1_LP4_DCC_PLL1_2133_SHFT                                                     18
#define HWIO_CALIBRATION69_DDR_CH1_LP4_DCC_PLL0_2133_BMSK                                                0x3f000
#define HWIO_CALIBRATION69_DDR_CH1_LP4_DCC_PLL0_2133_SHFT                                                     12
#define HWIO_CALIBRATION69_DDR_CH0_LP4_CA_DCC_IO_CK_2133_BMSK                                              0xfc0
#define HWIO_CALIBRATION69_DDR_CH0_LP4_CA_DCC_IO_CK_2133_SHFT                                                  6
#define HWIO_CALIBRATION69_DDR_CH0_LP4_CA_DCC_CLK_ADJ_2133_BMSK                                             0x3f
#define HWIO_CALIBRATION69_DDR_CH0_LP4_CA_DCC_CLK_ADJ_2133_SHFT                                                0

#define HWIO_CALIBRATION70_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe18)
#define HWIO_CALIBRATION70_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe18)
#define HWIO_CALIBRATION70_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION70_ATTR                                                                                    0x1
#define HWIO_CALIBRATION70_IN                    \
                in_dword(HWIO_CALIBRATION70_ADDR)
#define HWIO_CALIBRATION70_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION70_ADDR, m)
#define HWIO_CALIBRATION70_DDR_CH0_LP5_DCC_PLL0_3197_3_0_BMSK                                         0xf0000000
#define HWIO_CALIBRATION70_DDR_CH0_LP5_DCC_PLL0_3197_3_0_SHFT                                                 28
#define HWIO_CALIBRATION70_DDR_CH1_LP4_CA_DCC_IO_CK_2133_BMSK                                          0xfc00000
#define HWIO_CALIBRATION70_DDR_CH1_LP4_CA_DCC_IO_CK_2133_SHFT                                                 22
#define HWIO_CALIBRATION70_DDR_CH1_LP4_CA_DCC_CLK_ADJ_2133_BMSK                                         0x3f0000
#define HWIO_CALIBRATION70_DDR_CH1_LP4_CA_DCC_CLK_ADJ_2133_SHFT                                               16
#define HWIO_CALIBRATION70_DDR_CH1_LP4_DQ1_DCC_IO_DQS_2133_BMSK                                           0xfc00
#define HWIO_CALIBRATION70_DDR_CH1_LP4_DQ1_DCC_IO_DQS_2133_SHFT                                               10
#define HWIO_CALIBRATION70_DDR_CH1_LP4_DQ1_DCC_CLK_ADJ_2133_BMSK                                           0x3f0
#define HWIO_CALIBRATION70_DDR_CH1_LP4_DQ1_DCC_CLK_ADJ_2133_SHFT                                               4
#define HWIO_CALIBRATION70_DDR_CH1_LP4_DQ0_DCC_IO_DQS_2133_5_2_BMSK                                          0xf
#define HWIO_CALIBRATION70_DDR_CH1_LP4_DQ0_DCC_IO_DQS_2133_5_2_SHFT                                            0

#define HWIO_CALIBRATION71_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe1c)
#define HWIO_CALIBRATION71_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe1c)
#define HWIO_CALIBRATION71_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION71_ATTR                                                                                    0x1
#define HWIO_CALIBRATION71_IN                    \
                in_dword(HWIO_CALIBRATION71_ADDR)
#define HWIO_CALIBRATION71_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION71_ADDR, m)
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DQ0_DCC_RDT4_3197_BMSK                                         0xfc000000
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DQ0_DCC_RDT4_3197_SHFT                                                 26
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DQ0_DCC_IO_DQS_3197_BMSK                                        0x3f00000
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DQ0_DCC_IO_DQS_3197_SHFT                                               20
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DQ0_DCC_IO_WCK_3197_BMSK                                          0xfc000
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DQ0_DCC_IO_WCK_3197_SHFT                                               14
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DQ0_DCC_CLK_ADJ_3197_BMSK                                          0x3f00
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DQ0_DCC_CLK_ADJ_3197_SHFT                                               8
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DCC_PLL1_3197_BMSK                                                   0xfc
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DCC_PLL1_3197_SHFT                                                      2
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DCC_PLL0_3197_5_4_BMSK                                                0x3
#define HWIO_CALIBRATION71_DDR_CH0_LP5_DCC_PLL0_3197_5_4_SHFT                                                  0

#define HWIO_CALIBRATION72_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe20)
#define HWIO_CALIBRATION72_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe20)
#define HWIO_CALIBRATION72_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION72_ATTR                                                                                    0x1
#define HWIO_CALIBRATION72_IN                    \
                in_dword(HWIO_CALIBRATION72_ADDR)
#define HWIO_CALIBRATION72_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION72_ADDR, m)
#define HWIO_CALIBRATION72_DDR_CH1_LP5_DCC_PLL0_3197_1_0_BMSK                                         0xc0000000
#define HWIO_CALIBRATION72_DDR_CH1_LP5_DCC_PLL0_3197_1_0_SHFT                                                 30
#define HWIO_CALIBRATION72_DDR_CH0_LP5_CA_DCC_IO_CK_3197_BMSK                                         0x3f000000
#define HWIO_CALIBRATION72_DDR_CH0_LP5_CA_DCC_IO_CK_3197_SHFT                                                 24
#define HWIO_CALIBRATION72_DDR_CH0_LP5_DQ1_DCC_RDT4_3197_BMSK                                           0xfc0000
#define HWIO_CALIBRATION72_DDR_CH0_LP5_DQ1_DCC_RDT4_3197_SHFT                                                 18
#define HWIO_CALIBRATION72_DDR_CH0_LP5_DQ1_DCC_IO_DQS_3197_BMSK                                          0x3f000
#define HWIO_CALIBRATION72_DDR_CH0_LP5_DQ1_DCC_IO_DQS_3197_SHFT                                               12
#define HWIO_CALIBRATION72_DDR_CH0_LP5_DQ1_DCC_IO_WCK_3197_BMSK                                            0xfc0
#define HWIO_CALIBRATION72_DDR_CH0_LP5_DQ1_DCC_IO_WCK_3197_SHFT                                                6
#define HWIO_CALIBRATION72_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_3197_BMSK                                            0x3f
#define HWIO_CALIBRATION72_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_3197_SHFT                                               0

#define HWIO_CALIBRATION73_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe24)
#define HWIO_CALIBRATION73_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe24)
#define HWIO_CALIBRATION73_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION73_ATTR                                                                                    0x1
#define HWIO_CALIBRATION73_IN                    \
                in_dword(HWIO_CALIBRATION73_ADDR)
#define HWIO_CALIBRATION73_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION73_ADDR, m)
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DQ0_DCC_RDT4_3197_3_0_BMSK                                     0xf0000000
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DQ0_DCC_RDT4_3197_3_0_SHFT                                             28
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DQ0_DCC_IO_DQS_3197_BMSK                                        0xfc00000
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DQ0_DCC_IO_DQS_3197_SHFT                                               22
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DQ0_DCC_IO_WCK_3197_BMSK                                         0x3f0000
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DQ0_DCC_IO_WCK_3197_SHFT                                               16
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DQ0_DCC_CLK_ADJ_3197_BMSK                                          0xfc00
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DQ0_DCC_CLK_ADJ_3197_SHFT                                              10
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DCC_PLL1_3197_BMSK                                                  0x3f0
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DCC_PLL1_3197_SHFT                                                      4
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DCC_PLL0_3197_5_2_BMSK                                                0xf
#define HWIO_CALIBRATION73_DDR_CH1_LP5_DCC_PLL0_3197_5_2_SHFT                                                  0

#define HWIO_CALIBRATION74_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe28)
#define HWIO_CALIBRATION74_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe28)
#define HWIO_CALIBRATION74_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION74_ATTR                                                                                    0x1
#define HWIO_CALIBRATION74_IN                    \
                in_dword(HWIO_CALIBRATION74_ADDR)
#define HWIO_CALIBRATION74_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION74_ADDR, m)
#define HWIO_CALIBRATION74_DDR_CH1_LP5_CA_DCC_IO_CK_3197_BMSK                                         0xfc000000
#define HWIO_CALIBRATION74_DDR_CH1_LP5_CA_DCC_IO_CK_3197_SHFT                                                 26
#define HWIO_CALIBRATION74_DDR_CH1_LP5_DQ1_DCC_RDT4_3197_BMSK                                          0x3f00000
#define HWIO_CALIBRATION74_DDR_CH1_LP5_DQ1_DCC_RDT4_3197_SHFT                                                 20
#define HWIO_CALIBRATION74_DDR_CH1_LP5_DQ1_DCC_IO_DQS_3197_BMSK                                          0xfc000
#define HWIO_CALIBRATION74_DDR_CH1_LP5_DQ1_DCC_IO_DQS_3197_SHFT                                               14
#define HWIO_CALIBRATION74_DDR_CH1_LP5_DQ1_DCC_IO_WCK_3197_BMSK                                           0x3f00
#define HWIO_CALIBRATION74_DDR_CH1_LP5_DQ1_DCC_IO_WCK_3197_SHFT                                                8
#define HWIO_CALIBRATION74_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_3197_BMSK                                            0xfc
#define HWIO_CALIBRATION74_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_3197_SHFT                                               2
#define HWIO_CALIBRATION74_DDR_CH1_LP5_DQ0_DCC_RDT4_3197_5_4_BMSK                                            0x3
#define HWIO_CALIBRATION74_DDR_CH1_LP5_DQ0_DCC_RDT4_3197_5_4_SHFT                                              0

#define HWIO_CALIBRATION75_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe2c)
#define HWIO_CALIBRATION75_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe2c)
#define HWIO_CALIBRATION75_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION75_ATTR                                                                                    0x1
#define HWIO_CALIBRATION75_IN                    \
                in_dword(HWIO_CALIBRATION75_ADDR)
#define HWIO_CALIBRATION75_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION75_ADDR, m)
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DQ1_DCC_IO_DQS_547_1_0_BMSK                                    0xc0000000
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DQ1_DCC_IO_DQS_547_1_0_SHFT                                            30
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DQ1_DCC_CLK_ADJ_547_BMSK                                       0x3f000000
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DQ1_DCC_CLK_ADJ_547_SHFT                                               24
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DQ0_DCC_IO_DQS_547_BMSK                                          0xfc0000
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DQ0_DCC_IO_DQS_547_SHFT                                                18
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DQ0_DCC_CLK_ADJ_547_BMSK                                          0x3f000
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DQ0_DCC_CLK_ADJ_547_SHFT                                               12
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DCC_PLL1_547_BMSK                                                   0xfc0
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DCC_PLL1_547_SHFT                                                       6
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DCC_PLL0_547_BMSK                                                    0x3f
#define HWIO_CALIBRATION75_DDR_CH0_LP4_DCC_PLL0_547_SHFT                                                       0

#define HWIO_CALIBRATION76_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe30)
#define HWIO_CALIBRATION76_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe30)
#define HWIO_CALIBRATION76_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION76_ATTR                                                                                    0x1
#define HWIO_CALIBRATION76_IN                    \
                in_dword(HWIO_CALIBRATION76_ADDR)
#define HWIO_CALIBRATION76_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION76_ADDR, m)
#define HWIO_CALIBRATION76_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_547_3_0_BMSK                                   0xf0000000
#define HWIO_CALIBRATION76_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_547_3_0_SHFT                                           28
#define HWIO_CALIBRATION76_DDR_CH1_LP4_DCC_PLL1_547_BMSK                                               0xfc00000
#define HWIO_CALIBRATION76_DDR_CH1_LP4_DCC_PLL1_547_SHFT                                                      22
#define HWIO_CALIBRATION76_DDR_CH1_LP4_DCC_PLL0_547_BMSK                                                0x3f0000
#define HWIO_CALIBRATION76_DDR_CH1_LP4_DCC_PLL0_547_SHFT                                                      16
#define HWIO_CALIBRATION76_DDR_CH0_LP4_CA_DCC_IO_CK_547_BMSK                                              0xfc00
#define HWIO_CALIBRATION76_DDR_CH0_LP4_CA_DCC_IO_CK_547_SHFT                                                  10
#define HWIO_CALIBRATION76_DDR_CH0_LP4_CA_DCC_CLK_ADJ_547_BMSK                                             0x3f0
#define HWIO_CALIBRATION76_DDR_CH0_LP4_CA_DCC_CLK_ADJ_547_SHFT                                                 4
#define HWIO_CALIBRATION76_DDR_CH0_LP4_DQ1_DCC_IO_DQS_547_5_2_BMSK                                           0xf
#define HWIO_CALIBRATION76_DDR_CH0_LP4_DQ1_DCC_IO_DQS_547_5_2_SHFT                                             0

#define HWIO_CALIBRATION77_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe34)
#define HWIO_CALIBRATION77_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe34)
#define HWIO_CALIBRATION77_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION77_ATTR                                                                                    0x1
#define HWIO_CALIBRATION77_IN                    \
                in_dword(HWIO_CALIBRATION77_ADDR)
#define HWIO_CALIBRATION77_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION77_ADDR, m)
#define HWIO_CALIBRATION77_DDR_CH1_LP4_CA_DCC_IO_CK_547_BMSK                                          0xfc000000
#define HWIO_CALIBRATION77_DDR_CH1_LP4_CA_DCC_IO_CK_547_SHFT                                                  26
#define HWIO_CALIBRATION77_DDR_CH1_LP4_CA_DCC_CLK_ADJ_547_BMSK                                         0x3f00000
#define HWIO_CALIBRATION77_DDR_CH1_LP4_CA_DCC_CLK_ADJ_547_SHFT                                                20
#define HWIO_CALIBRATION77_DDR_CH1_LP4_DQ1_DCC_IO_DQS_547_BMSK                                           0xfc000
#define HWIO_CALIBRATION77_DDR_CH1_LP4_DQ1_DCC_IO_DQS_547_SHFT                                                14
#define HWIO_CALIBRATION77_DDR_CH1_LP4_DQ1_DCC_CLK_ADJ_547_BMSK                                           0x3f00
#define HWIO_CALIBRATION77_DDR_CH1_LP4_DQ1_DCC_CLK_ADJ_547_SHFT                                                8
#define HWIO_CALIBRATION77_DDR_CH1_LP4_DQ0_DCC_IO_DQS_547_BMSK                                              0xfc
#define HWIO_CALIBRATION77_DDR_CH1_LP4_DQ0_DCC_IO_DQS_547_SHFT                                                 2
#define HWIO_CALIBRATION77_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_547_5_4_BMSK                                          0x3
#define HWIO_CALIBRATION77_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_547_5_4_SHFT                                            0

#define HWIO_CALIBRATION78_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe38)
#define HWIO_CALIBRATION78_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe38)
#define HWIO_CALIBRATION78_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION78_ATTR                                                                                    0x1
#define HWIO_CALIBRATION78_IN                    \
                in_dword(HWIO_CALIBRATION78_ADDR)
#define HWIO_CALIBRATION78_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION78_ADDR, m)
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DQ0_DCC_RDT4_768_1_0_BMSK                                      0xc0000000
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DQ0_DCC_RDT4_768_1_0_SHFT                                              30
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DQ0_DCC_IO_DQS_768_BMSK                                        0x3f000000
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DQ0_DCC_IO_DQS_768_SHFT                                                24
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DQ0_DCC_IO_WCK_768_BMSK                                          0xfc0000
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DQ0_DCC_IO_WCK_768_SHFT                                                18
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DQ0_DCC_CLK_ADJ_768_BMSK                                          0x3f000
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DQ0_DCC_CLK_ADJ_768_SHFT                                               12
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DCC_PLL1_768_BMSK                                                   0xfc0
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DCC_PLL1_768_SHFT                                                       6
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DCC_PLL0_768_BMSK                                                    0x3f
#define HWIO_CALIBRATION78_DDR_CH0_LP5_DCC_PLL0_768_SHFT                                                       0

#define HWIO_CALIBRATION79_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe3c)
#define HWIO_CALIBRATION79_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe3c)
#define HWIO_CALIBRATION79_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION79_ATTR                                                                                    0x1
#define HWIO_CALIBRATION79_IN                    \
                in_dword(HWIO_CALIBRATION79_ADDR)
#define HWIO_CALIBRATION79_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION79_ADDR, m)
#define HWIO_CALIBRATION79_DDR_CH0_LP5_CA_DCC_IO_CK_768_3_0_BMSK                                      0xf0000000
#define HWIO_CALIBRATION79_DDR_CH0_LP5_CA_DCC_IO_CK_768_3_0_SHFT                                              28
#define HWIO_CALIBRATION79_DDR_CH0_LP5_DQ1_DCC_RDT4_768_BMSK                                           0xfc00000
#define HWIO_CALIBRATION79_DDR_CH0_LP5_DQ1_DCC_RDT4_768_SHFT                                                  22
#define HWIO_CALIBRATION79_DDR_CH0_LP5_DQ1_DCC_IO_DQS_768_BMSK                                          0x3f0000
#define HWIO_CALIBRATION79_DDR_CH0_LP5_DQ1_DCC_IO_DQS_768_SHFT                                                16
#define HWIO_CALIBRATION79_DDR_CH0_LP5_DQ1_DCC_IO_WCK_768_BMSK                                            0xfc00
#define HWIO_CALIBRATION79_DDR_CH0_LP5_DQ1_DCC_IO_WCK_768_SHFT                                                10
#define HWIO_CALIBRATION79_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_768_BMSK                                            0x3f0
#define HWIO_CALIBRATION79_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_768_SHFT                                                4
#define HWIO_CALIBRATION79_DDR_CH0_LP5_DQ0_DCC_RDT4_768_5_2_BMSK                                             0xf
#define HWIO_CALIBRATION79_DDR_CH0_LP5_DQ0_DCC_RDT4_768_5_2_SHFT                                               0

#define HWIO_CALIBRATION80_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe40)
#define HWIO_CALIBRATION80_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe40)
#define HWIO_CALIBRATION80_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION80_ATTR                                                                                    0x1
#define HWIO_CALIBRATION80_IN                    \
                in_dword(HWIO_CALIBRATION80_ADDR)
#define HWIO_CALIBRATION80_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION80_ADDR, m)
#define HWIO_CALIBRATION80_DDR_CH1_LP5_DQ0_DCC_IO_DQS_768_BMSK                                        0xfc000000
#define HWIO_CALIBRATION80_DDR_CH1_LP5_DQ0_DCC_IO_DQS_768_SHFT                                                26
#define HWIO_CALIBRATION80_DDR_CH1_LP5_DQ0_DCC_IO_WCK_768_BMSK                                         0x3f00000
#define HWIO_CALIBRATION80_DDR_CH1_LP5_DQ0_DCC_IO_WCK_768_SHFT                                                20
#define HWIO_CALIBRATION80_DDR_CH1_LP5_DQ0_DCC_CLK_ADJ_768_BMSK                                          0xfc000
#define HWIO_CALIBRATION80_DDR_CH1_LP5_DQ0_DCC_CLK_ADJ_768_SHFT                                               14
#define HWIO_CALIBRATION80_DDR_CH1_LP5_DCC_PLL1_768_BMSK                                                  0x3f00
#define HWIO_CALIBRATION80_DDR_CH1_LP5_DCC_PLL1_768_SHFT                                                       8
#define HWIO_CALIBRATION80_DDR_CH1_LP5_DCC_PLL0_768_BMSK                                                    0xfc
#define HWIO_CALIBRATION80_DDR_CH1_LP5_DCC_PLL0_768_SHFT                                                       2
#define HWIO_CALIBRATION80_DDR_CH0_LP5_CA_DCC_IO_CK_768_5_4_BMSK                                             0x3
#define HWIO_CALIBRATION80_DDR_CH0_LP5_CA_DCC_IO_CK_768_5_4_SHFT                                               0

#define HWIO_CALIBRATION81_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe44)
#define HWIO_CALIBRATION81_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe44)
#define HWIO_CALIBRATION81_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION81_ATTR                                                                                    0x1
#define HWIO_CALIBRATION81_IN                    \
                in_dword(HWIO_CALIBRATION81_ADDR)
#define HWIO_CALIBRATION81_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION81_ADDR, m)
#define HWIO_CALIBRATION81_DDR_CH1_LP5_CA_DCC_IO_CK_768_1_0_BMSK                                      0xc0000000
#define HWIO_CALIBRATION81_DDR_CH1_LP5_CA_DCC_IO_CK_768_1_0_SHFT                                              30
#define HWIO_CALIBRATION81_DDR_CH1_LP5_DQ1_DCC_RDT4_768_BMSK                                          0x3f000000
#define HWIO_CALIBRATION81_DDR_CH1_LP5_DQ1_DCC_RDT4_768_SHFT                                                  24
#define HWIO_CALIBRATION81_DDR_CH1_LP5_DQ1_DCC_IO_DQS_768_BMSK                                          0xfc0000
#define HWIO_CALIBRATION81_DDR_CH1_LP5_DQ1_DCC_IO_DQS_768_SHFT                                                18
#define HWIO_CALIBRATION81_DDR_CH1_LP5_DQ1_DCC_IO_WCK_768_BMSK                                           0x3f000
#define HWIO_CALIBRATION81_DDR_CH1_LP5_DQ1_DCC_IO_WCK_768_SHFT                                                12
#define HWIO_CALIBRATION81_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_768_BMSK                                            0xfc0
#define HWIO_CALIBRATION81_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_768_SHFT                                                6
#define HWIO_CALIBRATION81_DDR_CH1_LP5_DQ0_DCC_RDT4_768_BMSK                                                0x3f
#define HWIO_CALIBRATION81_DDR_CH1_LP5_DQ0_DCC_RDT4_768_SHFT                                                   0

#define HWIO_CALIBRATION82_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe48)
#define HWIO_CALIBRATION82_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe48)
#define HWIO_CALIBRATION82_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION82_ATTR                                                                                    0x1
#define HWIO_CALIBRATION82_IN                    \
                in_dword(HWIO_CALIBRATION82_ADDR)
#define HWIO_CALIBRATION82_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION82_ADDR, m)
#define HWIO_CALIBRATION82_CALIBRATION_2655_2628_BMSK                                                 0xfffffff0
#define HWIO_CALIBRATION82_CALIBRATION_2655_2628_SHFT                                                          4
#define HWIO_CALIBRATION82_DDR_CH1_LP5_CA_DCC_IO_CK_768_5_2_BMSK                                             0xf
#define HWIO_CALIBRATION82_DDR_CH1_LP5_CA_DCC_IO_CK_768_5_2_SHFT                                               0

#define HWIO_CALIBRATION83_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe4c)
#define HWIO_CALIBRATION83_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe4c)
#define HWIO_CALIBRATION83_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION83_ATTR                                                                                    0x1
#define HWIO_CALIBRATION83_IN                    \
                in_dword(HWIO_CALIBRATION83_ADDR)
#define HWIO_CALIBRATION83_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION83_ADDR, m)
#define HWIO_CALIBRATION83_CALIBRATION_2687_2656_BMSK                                                 0xffffffff
#define HWIO_CALIBRATION83_CALIBRATION_2687_2656_SHFT                                                          0

#define HWIO_CALIBRATION84_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe50)
#define HWIO_CALIBRATION84_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe50)
#define HWIO_CALIBRATION84_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION84_ATTR                                                                                    0x1
#define HWIO_CALIBRATION84_IN                    \
                in_dword(HWIO_CALIBRATION84_ADDR)
#define HWIO_CALIBRATION84_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION84_ADDR, m)
#define HWIO_CALIBRATION84_DDR_FT_BMSK                                                                0x80000000
#define HWIO_CALIBRATION84_DDR_FT_SHFT                                                                        31
#define HWIO_CALIBRATION84_DDR_WS_BMSK                                                                0x40000000
#define HWIO_CALIBRATION84_DDR_WS_SHFT                                                                        30
#define HWIO_CALIBRATION84_VSENS_FT_BMSK                                                              0x20000000
#define HWIO_CALIBRATION84_VSENS_FT_SHFT                                                                      29
#define HWIO_CALIBRATION84_VSENS_WS_BMSK                                                              0x10000000
#define HWIO_CALIBRATION84_VSENS_WS_SHFT                                                                      28
#define HWIO_CALIBRATION84_ISENS_FT_BMSK                                                               0x8000000
#define HWIO_CALIBRATION84_ISENS_FT_SHFT                                                                      27
#define HWIO_CALIBRATION84_ISENS_WS_BMSK                                                               0x4000000
#define HWIO_CALIBRATION84_ISENS_WS_SHFT                                                                      26
#define HWIO_CALIBRATION84_Q6_FT_BMSK                                                                  0x2000000
#define HWIO_CALIBRATION84_Q6_FT_SHFT                                                                         25
#define HWIO_CALIBRATION84_Q6_WS_BMSK                                                                  0x1000000
#define HWIO_CALIBRATION84_Q6_WS_SHFT                                                                         24
#define HWIO_CALIBRATION84_BANDGAP_FT_BMSK                                                              0x800000
#define HWIO_CALIBRATION84_BANDGAP_FT_SHFT                                                                    23
#define HWIO_CALIBRATION84_BANDGAP_WS_BMSK                                                              0x400000
#define HWIO_CALIBRATION84_BANDGAP_WS_SHFT                                                                    22
#define HWIO_CALIBRATION84_DACC_FT_BMSK                                                                 0x200000
#define HWIO_CALIBRATION84_DACC_FT_SHFT                                                                       21
#define HWIO_CALIBRATION84_DACC_WS_BMSK                                                                 0x100000
#define HWIO_CALIBRATION84_DACC_WS_SHFT                                                                       20
#define HWIO_CALIBRATION84_AOSS_FT_BMSK                                                                  0x80000
#define HWIO_CALIBRATION84_AOSS_FT_SHFT                                                                       19
#define HWIO_CALIBRATION84_AOSS_WS_BMSK                                                                  0x40000
#define HWIO_CALIBRATION84_AOSS_WS_SHFT                                                                       18
#define HWIO_CALIBRATION84_USB_FT_BMSK                                                                   0x20000
#define HWIO_CALIBRATION84_USB_FT_SHFT                                                                        17
#define HWIO_CALIBRATION84_USB_WS_BMSK                                                                   0x10000
#define HWIO_CALIBRATION84_USB_WS_SHFT                                                                        16
#define HWIO_CALIBRATION84_REFGEN_FT_BMSK                                                                 0x8000
#define HWIO_CALIBRATION84_REFGEN_FT_SHFT                                                                     15
#define HWIO_CALIBRATION84_REFGEN_WS_BMSK                                                                 0x4000
#define HWIO_CALIBRATION84_REFGEN_WS_SHFT                                                                     14
#define HWIO_CALIBRATION84_IDDQ_FT_BMSK                                                                   0x2000
#define HWIO_CALIBRATION84_IDDQ_FT_SHFT                                                                       13
#define HWIO_CALIBRATION84_IDDQ_WS_BMSK                                                                   0x1000
#define HWIO_CALIBRATION84_IDDQ_WS_SHFT                                                                       12
#define HWIO_CALIBRATION84_MRET_FT_BMSK                                                                    0x800
#define HWIO_CALIBRATION84_MRET_FT_SHFT                                                                       11
#define HWIO_CALIBRATION84_MRET_WS_BMSK                                                                    0x400
#define HWIO_CALIBRATION84_MRET_WS_SHFT                                                                       10
#define HWIO_CALIBRATION84_LRET_FT_BMSK                                                                    0x200
#define HWIO_CALIBRATION84_LRET_FT_SHFT                                                                        9
#define HWIO_CALIBRATION84_LRET_WS_BMSK                                                                    0x100
#define HWIO_CALIBRATION84_LRET_WS_SHFT                                                                        8
#define HWIO_CALIBRATION84_DVS_FT_BMSK                                                                      0x80
#define HWIO_CALIBRATION84_DVS_FT_SHFT                                                                         7
#define HWIO_CALIBRATION84_DVS_WS_BMSK                                                                      0x40
#define HWIO_CALIBRATION84_DVS_WS_SHFT                                                                         6
#define HWIO_CALIBRATION84_CPR_FT_BMSK                                                                      0x20
#define HWIO_CALIBRATION84_CPR_FT_SHFT                                                                         5
#define HWIO_CALIBRATION84_CPR_WS_BMSK                                                                      0x10
#define HWIO_CALIBRATION84_CPR_WS_SHFT                                                                         4
#define HWIO_CALIBRATION84_TSENS_FT_BMSK                                                                     0x8
#define HWIO_CALIBRATION84_TSENS_FT_SHFT                                                                       3
#define HWIO_CALIBRATION84_TSENS_WS_BMSK                                                                     0x4
#define HWIO_CALIBRATION84_TSENS_WS_SHFT                                                                       2
#define HWIO_CALIBRATION84_QFPROM_FT_BMSK                                                                    0x2
#define HWIO_CALIBRATION84_QFPROM_FT_SHFT                                                                      1
#define HWIO_CALIBRATION84_QFPROM_WS_BMSK                                                                    0x1
#define HWIO_CALIBRATION84_QFPROM_WS_SHFT                                                                      0

#define HWIO_CALIBRATION85_ADDR                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0xe54)
#define HWIO_CALIBRATION85_OFFS                                                                       (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0xe54)
#define HWIO_CALIBRATION85_RMSK                                                                       0xffffffff
#define HWIO_CALIBRATION85_ATTR                                                                                    0x1
#define HWIO_CALIBRATION85_IN                    \
                in_dword(HWIO_CALIBRATION85_ADDR)
#define HWIO_CALIBRATION85_INM(m)            \
                in_dword_masked(HWIO_CALIBRATION85_ADDR, m)
#define HWIO_CALIBRATION85_QFPROM_MCN_ATTRIBUTE_BMSK                                                  0x80000000
#define HWIO_CALIBRATION85_QFPROM_MCN_ATTRIBUTE_SHFT                                                          31
#define HWIO_CALIBRATION85_CALIBRATION_2750_2720_BMSK                                                 0x7fffffff
#define HWIO_CALIBRATION85_CALIBRATION_2750_2720_SHFT                                                          0


#endif /* __CPR_FUSES_HWIO_H__ */
