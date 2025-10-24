#ifndef __HALHWIOTSENSFUSES_H__
#define __HALHWIOTSENSFUSES_H__
/*
===========================================================================
*/
/**
    @file HALhwioTsensFuses.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8550 (Kailua) [z_tme_fusecontroller_kailua_p3q2r37]
 
    This file contains HWIO register definitions for the following modules:
        QFPROM_CORR

    'Include' filters applied: QFPROM_CORR_CALIB.*[QFPROM_CORR] 

    Generation parameters: 
    { 'filename': 'HALhwioTsensFuses.h',
      'header': '#include "msmhwiobase.h"',
      'module-filter-include': {'QFPROM_CORR': ['QFPROM_CORR_CALIB.*']},
      'modules': ['QFPROM_CORR']}
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

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/TsensTargetLib/HALhwioTsensFuses.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: QFPROM_CORR
 *--------------------------------------------------------------------------*/

#define QFPROM_CORR_REG_BASE                                                                               (TMESS_BASE      + 0x021c2000)
#define QFPROM_CORR_REG_BASE_SIZE                                                                          0x2000
#define QFPROM_CORR_REG_BASE_USED                                                                          0xfdc

#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7a8)
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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_64_BMSK                                       0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_64_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7b4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_127_96_BMSK                                      0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_127_96_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7b8)
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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CALIBRATION_383_352_BMSK                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CALIBRATION_383_352_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x7d8)
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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_NOML1_2_0_BMSK                               0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_NOML1_2_0_SHFT                                       29
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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_NOML1_5_3_BMSK                                      0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_NOML1_5_3_SHFT                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x808)
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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_NOM_2_0_BMSK                          0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_NOM_2_0_SHFT                                  29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_NOML1_BMSK                            0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_NOML1_SHFT                                    24
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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CALIBRATION_991_960_BMSK                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CALIBRATION_991_960_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x824)
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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CALIBRATION_1439_1408_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CALIBRATION_1439_1408_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x85c)
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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CALIBRATION_1823_1792_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CALIBRATION_1823_1792_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x88c)
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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2143_2127_BMSK                                  0xffff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2143_2127_SHFT                                          15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CPR5_TARG_VOLT_OFFSET_SVS_BMSK                                  0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CPR5_TARG_VOLT_OFFSET_SVS_SHFT                                      10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CPR5_TARG_VOLT_OFFSET_TUR__BMSK                                  0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CPR5_TARG_VOLT_OFFSET_TUR__SHFT                                      5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_OPAMP_FUSE_NSPRAIL_HMX_FT_5_1_BMSK                                0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_OPAMP_FUSE_NSPRAIL_HMX_FT_5_1_SHFT                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8b4)
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


#endif /* __HALHWIOTSENSFUSES_H__ */
