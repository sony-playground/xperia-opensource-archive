#ifndef __HALHWIOTSENSFUSES_H__
#define __HALHWIOTSENSFUSES_H__
/*
===========================================================================
*/
/**
    @file HALhwioTsensFuses.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM6450 (Netrani) [z_tme_fusecontroller_5lpe_netrani_p3q3r35]
 
    This file contains HWIO register definitions for the following modules:
        QFPROM_CORR

    'Include' filters applied: QFPROM_CORR_CALIB.*[QFPROM_CORR] 

    Generation parameters: 
    { 'filename': 'HALhwioTsensFuses.h',
      'header': '#include "msmhwiobase.h"',
      'module-filter-exclude': {},
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

    $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Netrani/Library/TsensTargetLib/HALhwioTsensFuses.h#2 $
    $DateTime: 2022/04/18 01:31:22 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: QFPROM_CORR
 *--------------------------------------------------------------------------*/
 
#define TME_FUSECONTROLLER_BASE                                                                                     0x221C0000 

#define QFPROM_CORR_REG_BASE                                                                                        (TME_FUSECONTROLLER_BASE      + 0x00002000)
#define QFPROM_CORR_REG_BASE_SIZE                                                                                   0x2000
#define QFPROM_CORR_REG_BASE_USED                                                                                   0xcdc

#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6a8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_USB2PHY_RCAL_CODE_0_BMSK                                              0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_USB2PHY_RCAL_CODE_0_SHFT                                                      31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_CALIBRATION_30_BMSK                                                   0x40000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_CALIBRATION_30_SHFT                                                           30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_AOSS_TDOPCODE_BMSK                                                    0x38000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_AOSS_TDOPCODE_SHFT                                                            27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_AOSS_RDOPCODE_BMSK                                                     0x7000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_AOSS_RDOPCODE_SHFT                                                            24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_SOUTH_EAST_BGV_TRIM_BMSK                                         0xe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_SOUTH_EAST_BGV_TRIM_SHFT                                               21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_TSENS27_OFFSET_BMSK                                                     0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_TSENS27_OFFSET_SHFT                                                           16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_NOUTH_BGV_TRIM_BMSK                                                0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_NOUTH_BGV_TRIM_SHFT                                                     8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_SOUTH_BGV_TRIM_BMSK                                                  0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_SOUTH_BGV_TRIM_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6ac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_AOSS_N1_12_0_BMSK                                                     0xfff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_AOSS_N1_12_0_SHFT                                                             19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_AOSS_K_BMSK                                                              0x7fff8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_AOSS_K_SHFT                                                                    3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY_RCAL_CODE_3_1_BMSK                                                   0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY_RCAL_CODE_3_1_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6b0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_92_BMSK                                                0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_92_SHFT                                                        28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_FACTOR_FUSE_CPURAIL_BMSK                                               0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_FACTOR_FUSE_CPURAIL_SHFT                                                      23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_AOSS_P1_BMSK                                                            0x7fffe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_AOSS_P1_SHFT                                                                   5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_AOSS_N1_17_13_BMSK                                                          0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_AOSS_N1_17_13_SHFT                                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6b4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ISENSE_FUSE_CURRENT_CPU5_F2_0_BMSK                                    0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ISENSE_FUSE_CURRENT_CPU5_F2_0_SHFT                                            31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ISENSE_FUSE_CURRENT_CPU5_F1_BMSK                                      0x7fe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ISENSE_FUSE_CURRENT_CPU5_F1_SHFT                                              21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ISENSE_FUSE_CURRENT_CPU4_F2_BMSK                                        0x1ff800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ISENSE_FUSE_CURRENT_CPU4_F2_SHFT                                              11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ISENSE_FUSE_CURRENT_CPU4_F1_BMSK                                           0x7fe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ISENSE_FUSE_CURRENT_CPU4_F1_SHFT                                               1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_96_BMSK                                                          0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_96_SHFT                                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6b8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ISENSE_FUSE_CURRENT_CPU7_F1_2_0_BMSK                                  0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ISENSE_FUSE_CURRENT_CPU7_F1_2_0_SHFT                                          29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ISENSE_FUSE_CURRENT_CPU6_F2_BMSK                                      0x1ff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ISENSE_FUSE_CURRENT_CPU6_F2_SHFT                                              19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ISENSE_FUSE_CURRENT_CPU6_F1_BMSK                                         0x7fe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ISENSE_FUSE_CURRENT_CPU6_F1_SHFT                                               9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ISENSE_FUSE_CURRENT_CPU5_F2_9_1_BMSK                                       0x1ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ISENSE_FUSE_CURRENT_CPU5_F2_9_1_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6bc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CALIBRATION_191_177_BMSK                                              0xfffe0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CALIBRATION_191_177_SHFT                                                      17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ISENSE_FUSE_CURRENT_CPU7_F2_BMSK                                         0x1ff80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ISENSE_FUSE_CURRENT_CPU7_F2_SHFT                                               7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ISENSE_FUSE_CURRENT_CPU7_F1_9_3_BMSK                                        0x7f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ISENSE_FUSE_CURRENT_CPU7_F1_9_3_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6c0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CALIBRATION_223_192_BMSK                                              0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CALIBRATION_223_192_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6c4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_OPAMP_FUSE_CPURAIL_CPU5_WS_BMSK                                       0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_OPAMP_FUSE_CPURAIL_CPU5_WS_SHFT                                               26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_OPAMP_FUSE_CPURAIL_CPU5_FT_BMSK                                        0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_OPAMP_FUSE_CPURAIL_CPU5_FT_SHFT                                               20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_OPAMP_FUSE_CPURAIL_CPU4_WS_BMSK                                          0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_OPAMP_FUSE_CPURAIL_CPU4_WS_SHFT                                               14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_OPAMP_FUSE_CPURAIL_CPU4_FT_BMSK                                           0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_OPAMP_FUSE_CPURAIL_CPU4_FT_SHFT                                                8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_REVISION_CONTROL_WS_BMSK                                        0xe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_REVISION_CONTROL_WS_SHFT                                           5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_REVISION_CONTROL_FT_BMSK                                        0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ISENSE_FUSE_REVISION_CONTROL_FT_SHFT                                           2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CALIBRATION_225_224_BMSK                                                     0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CALIBRATION_225_224_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6c8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CALIBRATION_287_280_BMSK                                              0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CALIBRATION_287_280_SHFT                                                      24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_OPAMP_FUSE_CPURAIL_CPU7_WS_BMSK                                         0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_OPAMP_FUSE_CPURAIL_CPU7_WS_SHFT                                               18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_OPAMP_FUSE_CPURAIL_CPU7_FT_BMSK                                          0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_OPAMP_FUSE_CPURAIL_CPU7_FT_SHFT                                               12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_OPAMP_FUSE_CPURAIL_CPU6_WS_BMSK                                            0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_OPAMP_FUSE_CPURAIL_CPU6_WS_SHFT                                                6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_OPAMP_FUSE_CPURAIL_CPU6_FT_BMSK                                             0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_OPAMP_FUSE_CPURAIL_CPU6_FT_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6cc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CALIBRATION_319_312_BMSK                                              0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CALIBRATION_319_312_SHFT                                                      24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ROCOUNT_FUSE_CPURAIL_BMSK                                               0xff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ROCOUNT_FUSE_CPURAIL_SHFT                                                     16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CALIBRATION_303_288_BMSK                                                  0xffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CALIBRATION_303_288_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6d0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S7_BMSK                                                  0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S7_SHFT                                                          29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S6_BMSK                                                  0x1c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S6_SHFT                                                          26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S5_BMSK                                                   0x3800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S5_SHFT                                                          23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S4_BMSK                                                    0x700000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S4_SHFT                                                          20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S3_BMSK                                                     0xe0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S3_SHFT                                                          17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S2_BMSK                                                     0x1c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S2_SHFT                                                          14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S1_BMSK                                                      0x3800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S1_SHFT                                                          11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S0_BMSK                                                       0x700
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S0_SHFT                                                           8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_BMSK                                                           0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_SHFT                                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6d4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE_REVISION_CONTROL_BMSK                                     0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE_REVISION_CONTROL_SHFT                                             29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S8_BMSK                                                  0x18000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S8_SHFT                                                          27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S7_BMSK                                                   0x6000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S7_SHFT                                                          25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S6_BMSK                                                   0x1800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S6_SHFT                                                          23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S5_BMSK                                                    0x600000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S5_SHFT                                                          21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S4_BMSK                                                    0x180000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S4_SHFT                                                          19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S3_BMSK                                                     0x60000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S3_SHFT                                                          17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S2_BMSK                                                     0x18000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S2_SHFT                                                          15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S1_BMSK                                                      0x6000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S1_SHFT                                                          13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S0_BMSK                                                      0x1800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S0_SHFT                                                          11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_BMSK                                                          0x7f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_SHFT                                                              3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S8_BMSK                                                         0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S8_SHFT                                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6d8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR0_CPR_AGING_1_0_BMSK                                               0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR0_CPR_AGING_1_0_SHFT                                                       30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR_LOCAL_RC_BMSK                                                     0x38000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR_LOCAL_RC_SHFT                                                             27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR_GLOBAL_RC_BMSK                                                     0x7000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR_GLOBAL_RC_SHFT                                                            24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_SW_SPT_GLOBAL_RAILS_VPID_BMSK                                           0xff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_SW_SPT_GLOBAL_RAILS_VPID_SHFT                                                 16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_SW_SPT_LOCAL_RAILS_VPID_BMSK                                              0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_SW_SPT_LOCAL_RAILS_VPID_SHFT                                                   8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_NSP_ACD_DVM_ENABLE_BMSK                                                     0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_NSP_ACD_DVM_ENABLE_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6dc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS_0_BMSK                                      0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS_0_SHFT                                              31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVSL1_BMSK                                      0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVSL1_SHFT                                              26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_NOM_BMSK                                         0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_NOM_SHFT                                                21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_BMSK                                        0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_SHFT                                              16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_TUR_BMSK                                            0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_TUR_SHFT                                                11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SUT_BMSK                                             0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SUT_SHFT                                                 6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_CPR_AGING_7_2_BMSK                                                     0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_CPR_AGING_7_2_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6e0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SVS_4_0_BMSK                                           0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SVS_4_0_SHFT                                                   27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_NOM_BMSK                                                0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_NOM_SHFT                                                       21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_TUR_BMSK                                                 0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_TUR_SHFT                                                       15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SUT_BMSK                                                   0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SUT_SHFT                                                        9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_SVS2_BMSK                                            0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_SVS2_SHFT                                                4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_SVS_4_1_BMSK                                           0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_SVS_4_1_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6e4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR10_QUOT_MIN_TUR_4_0_BMSK                                           0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR10_QUOT_MIN_TUR_4_0_SHFT                                                   27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR10_QUOT_MIN_SUT_BMSK                                                0x7ff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR10_QUOT_MIN_SUT_SHFT                                                       15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR10_CPR_AGING_BMSK                                                      0x7f80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR10_CPR_AGING_SHFT                                                           7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_SVS2_BMSK                                                    0x7e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_SVS2_SHFT                                                       1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_SVS_5_BMSK                                                    0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_SVS_5_SHFT                                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6e8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR10_QUOT_MIN_SVS2_0_BMSK                                            0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR10_QUOT_MIN_SVS2_0_SHFT                                                    31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR10_QUOT_MIN_SVS_BMSK                                               0x7ff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR10_QUOT_MIN_SVS_SHFT                                                       19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR10_QUOT_MIN_NOM_BMSK                                                  0x7ff80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR10_QUOT_MIN_NOM_SHFT                                                        7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR10_QUOT_MIN_TUR_11_5_BMSK                                                0x7f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR10_QUOT_MIN_TUR_11_5_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6ec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_QF_CPR10_TARG_VOLT_SVS_2_0_BMSK                                       0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_QF_CPR10_TARG_VOLT_SVS_2_0_SHFT                                               29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_QF_CPR10_TARG_VOLT_NOM_BMSK                                           0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_QF_CPR10_TARG_VOLT_NOM_SHFT                                                   23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_QF_CPR10_TARG_VOLT_TUR_BMSK                                             0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_QF_CPR10_TARG_VOLT_TUR_SHFT                                                   17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_QF_CPR10_TARG_VOLT_SUT_BMSK                                              0x1f800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_QF_CPR10_TARG_VOLT_SUT_SHFT                                                   11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR10_QUOT_MIN_SVS2_11_1_BMSK                                              0x7ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR10_QUOT_MIN_SVS2_11_1_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6f0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR11_QUOT_MIN_TUR_10_0_BMSK                                          0xffe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR11_QUOT_MIN_TUR_10_0_SHFT                                                  21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR11_QUOT_MIN_SUT_BMSK                                                 0x1ffe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR11_QUOT_MIN_SUT_SHFT                                                        9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_QF_CPR10_TARG_VOLT_SVS2_BMSK                                               0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_QF_CPR10_TARG_VOLT_SVS2_SHFT                                                   3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_QF_CPR10_TARG_VOLT_SVS_5_3_BMSK                                              0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_QF_CPR10_TARG_VOLT_SVS_5_3_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x6f4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR11_QUOT_MIN_SVS2_6_0_BMSK                                          0xfe000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR11_QUOT_MIN_SVS2_6_0_SHFT                                                  25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR11_QUOT_MIN_SVS_BMSK                                                0x1ffe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR11_QUOT_MIN_SVS_SHFT                                                       13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR11_QUOT_MIN_NOM_BMSK                                                   0x1ffe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR11_QUOT_MIN_NOM_SHFT                                                        1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR11_QUOT_MIN_TUR_11_BMSK                                                   0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR11_QUOT_MIN_TUR_11_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x6f8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_QF_CPR11_TARG_VOLT_SVS2_2_0_BMSK                                     0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_QF_CPR11_TARG_VOLT_SVS2_2_0_SHFT                                             29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_QF_CPR11_TARG_VOLT_SVS_BMSK                                          0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_QF_CPR11_TARG_VOLT_SVS_SHFT                                                  23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_QF_CPR11_TARG_VOLT_NOM_BMSK                                            0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_QF_CPR11_TARG_VOLT_NOM_SHFT                                                  17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_QF_CPR11_TARG_VOLT_TUR_BMSK                                             0x1f800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_QF_CPR11_TARG_VOLT_TUR_SHFT                                                  11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_QF_CPR11_TARG_VOLT_SUT_BMSK                                               0x7e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_QF_CPR11_TARG_VOLT_SUT_SHFT                                                   5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR11_QUOT_MIN_SVS2_11_7_BMSK                                              0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR11_QUOT_MIN_SVS2_11_7_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x6fc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_TARG_VOLT_OFFSET_SVS2_0_BMSK                                    0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_TARG_VOLT_OFFSET_SVS2_0_SHFT                                            31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_TARG_VOLT_OFFSET_SVS_BMSK                                       0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_TARG_VOLT_OFFSET_SVS_SHFT                                               26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_TARG_VOLT_OFFSET_SVSL1_BMSK                                      0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_TARG_VOLT_OFFSET_SVSL1_SHFT                                             21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                         0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                               16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_TARG_VOLT_OFFSET_NOML1_BMSK                                         0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_TARG_VOLT_OFFSET_NOML1_SHFT                                             11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_CPR_AGING_BMSK                                                       0x7f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR1_CPR_AGING_SHFT                                                           3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_QF_CPR11_TARG_VOLT_SVS2_5_3_BMSK                                            0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_QF_CPR11_TARG_VOLT_SVS2_5_3_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x700)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_SVS3_4_0_BMSK                                         0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_SVS3_4_0_SHFT                                                 27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_SVS_BMSK                                               0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_SVS_SHFT                                                      21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_NOM_BMSK                                                0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_NOM_SHFT                                                      15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_NOML1_BMSK                                                0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_NOML1_SHFT                                                     9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_OFFSET_SVS3_BMSK                                           0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_OFFSET_SVS3_SHFT                                               4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_OFFSET_SVS2_4_1_BMSK                                         0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR1_TARG_VOLT_OFFSET_SVS2_4_1_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x704)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CALIBRATION_767_765_BMSK                                             0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CALIBRATION_767_765_SHFT                                                     29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                                       0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                               24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR2_TARG_VOLT_OFFSET_NOML1_BMSK                                       0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR2_TARG_VOLT_OFFSET_NOML1_SHFT                                             19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR2_TARG_VOLT_OFFSET_TUR_BMSK                                          0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR2_TARG_VOLT_OFFSET_TUR_SHFT                                               14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR2_TARG_VOLT_OFFSET_SUT_BMSK                                           0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR2_TARG_VOLT_OFFSET_SUT_SHFT                                                9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR2_CPR_AGING_BMSK                                                       0x1fe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR2_CPR_AGING_SHFT                                                           1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR1_TARG_VOLT_SVS3_5_BMSK                                                  0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR1_TARG_VOLT_SVS3_5_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x708)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CALIBRATION_799_768_BMSK                                             0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CALIBRATION_799_768_SHFT                                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x70c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR2_TARG_VOLT_OFFSET_SVS_2_0_BMSK                                   0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR2_TARG_VOLT_OFFSET_SVS_2_0_SHFT                                           29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_BMSK                                     0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_SHFT                                             24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_BMSK                                       0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_SHFT                                             19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CALIBRATION_818_800_BMSK                                                0x7ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CALIBRATION_818_800_SHFT                                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x710)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_SVS_1_0_BMSK                                          0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_SVS_1_0_SHFT                                                  30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_NOM_BMSK                                              0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_NOM_SHFT                                                      24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_TUR_BMSK                                                0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_TUR_SHFT                                                      18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_SUT_BMSK                                                 0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_SUT_SHFT                                                      12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_OFFSET_SVS3_BMSK                                           0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_OFFSET_SVS3_SHFT                                               7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_OFFSET_SVS2_BMSK                                            0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_OFFSET_SVS2_SHFT                                               2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_OFFSET_SVS_4_3_BMSK                                          0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR2_TARG_VOLT_OFFSET_SVS_4_3_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x714)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR4_CPR_AGING_1_0_BMSK                                              0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR4_CPR_AGING_1_0_SHFT                                                      30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR3_TARG_VOLT_SVS2_BMSK                                             0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR3_TARG_VOLT_SVS2_SHFT                                                     24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR3_TARG_VOLT_SUT_BMSK                                                0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR3_TARG_VOLT_SUT_SHFT                                                      18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR10_QUOT_OFFSET_BMSK                                                  0x3fc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR10_QUOT_OFFSET_SHFT                                                       10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR2_TARG_VOLT_SVS3_BMSK                                                  0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR2_TARG_VOLT_SVS3_SHFT                                                      4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR2_TARG_VOLT_SVS_5_2_BMSK                                                 0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR2_TARG_VOLT_SVS_5_2_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x718)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR4_TARG_VOLT_SUT_BMSK                                              0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR4_TARG_VOLT_SUT_SHFT                                                      26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_QF_CPR4_TARG_VOLT_OFFSET_SVSL1_BMSK                                   0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_QF_CPR4_TARG_VOLT_OFFSET_SVSL1_SHFT                                          21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_QF_CPR4_TARG_VOLT_OFFSET_NOM_BMSK                                      0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_QF_CPR4_TARG_VOLT_OFFSET_NOM_SHFT                                            16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_QF_CPR4_TARG_VOLT_OFFSET_NOML1_BMSK                                      0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_QF_CPR4_TARG_VOLT_OFFSET_NOML1_SHFT                                          11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_QF_CPR4_TARG_VOLT_OFFSET_SUT_BMSK                                         0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_QF_CPR4_TARG_VOLT_OFFSET_SUT_SHFT                                             6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR4_CPR_AGING_7_2_BMSK                                                    0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR4_CPR_AGING_7_2_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x71c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR5_TARG_VOLT_SVSL1_1_0_BMSK                                        0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR5_TARG_VOLT_SVSL1_1_0_SHFT                                                30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR5_TARG_VOLT_NOM_BMSK                                              0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR5_TARG_VOLT_NOM_SHFT                                                      24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR5_TARG_VOLT_TUR_BMSK                                                0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR5_TARG_VOLT_TUR_SHFT                                                      18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR4_TARG_VOLT_SVSL1_BMSK                                               0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR4_TARG_VOLT_SVSL1_SHFT                                                    12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR4_TARG_VOLT_NOM_BMSK                                                   0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR4_TARG_VOLT_NOM_SHFT                                                       6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR4_TARG_VOLT_NOML1_BMSK                                                  0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR4_TARG_VOLT_NOML1_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x720)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR6_TARG_VOLT_OFFSET_SVSL1_1_0_BMSK                                 0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR6_TARG_VOLT_OFFSET_SVSL1_1_0_SHFT                                         30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR6_TARG_VOLT_OFFSET_NOM_BMSK                                       0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR6_TARG_VOLT_OFFSET_NOM_SHFT                                               25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR6_TARG_VOLT_OFFSET_TUR_BMSK                                        0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR6_TARG_VOLT_OFFSET_TUR_SHFT                                               20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR11_QUOT_OFFSET_BMSK                                                  0xff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR11_QUOT_OFFSET_SHFT                                                       12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR6_CPR_AGING_BMSK                                                       0xff0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR6_CPR_AGING_SHFT                                                           4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR5_TARG_VOLT_SVSL1_5_2_BMSK                                               0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR5_TARG_VOLT_SVSL1_5_2_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x724)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR6_TARG_VOLT_TUR_1_0_BMSK                                          0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR6_TARG_VOLT_TUR_1_0_SHFT                                                  30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR_MSS_MODE_DISABLE_BMSK                                            0x38000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR_MSS_MODE_DISABLE_SHFT                                                    27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR_DDR_MODE_DISABLE_BMSK                                             0x7000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR_DDR_MODE_DISABLE_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR_GFX_MODE_DISABLE_BMSK                                              0xe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR_GFX_MODE_DISABLE_SHFT                                                    21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR_CX_MODE_DISABLE_BMSK                                               0x1c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR_CX_MODE_DISABLE_SHFT                                                     18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR6_TARG_VOLT_OFFSET_SVS3_BMSK                                         0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR6_TARG_VOLT_OFFSET_SVS3_SHFT                                              13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR6_TARG_VOLT_OFFSET_SVS2_BMSK                                          0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR6_TARG_VOLT_OFFSET_SVS2_SHFT                                               8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR6_TARG_VOLT_OFFSET_SVS_BMSK                                             0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR6_TARG_VOLT_OFFSET_SVS_SHFT                                                3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR6_TARG_VOLT_OFFSET_SVSL1_4_2_BMSK                                        0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR6_TARG_VOLT_OFFSET_SVSL1_4_2_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x728)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR9_TARG_VOLT_SVS_3_0_BMSK                                          0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR9_TARG_VOLT_SVS_3_0_SHFT                                                  28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR9_TARG_VOLT_SCSL1_BMSK                                             0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR9_TARG_VOLT_SCSL1_SHFT                                                    22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR6_TARG_VOLT_SVS3_BMSK                                               0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR6_TARG_VOLT_SVS3_SHFT                                                     16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR6_TARG_VOLT_SVS_BMSK                                                  0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR6_TARG_VOLT_SVS_SHFT                                                      10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR6_TARG_VOLT_NOM_BMSK                                                   0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR6_TARG_VOLT_NOM_SHFT                                                       4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR6_TARG_VOLT_TUR_5_2_BMSK                                                 0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR6_TARG_VOLT_TUR_5_2_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x72c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR12_QUOT_MIN_BOOST_9_0_BMSK                                        0xffc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR12_QUOT_MIN_BOOST_9_0_SHFT                                                22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR12_QUOT_MIN_BOOSTP_BMSK                                             0x3ffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR12_QUOT_MIN_BOOSTP_SHFT                                                   10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR12_CPR_AGING_BMSK                                                      0x3fc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR12_CPR_AGING_SHFT                                                          2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR9_TARG_VOLT_SVS_5_4_BMSK                                                 0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR9_TARG_VOLT_SVS_5_4_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x730)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR_RESERVED_29_0_BMSK                                               0xfffffffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR_RESERVED_29_0_SHFT                                                        2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR12_QUOT_MIN_BOOST_11_10_BMSK                                             0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR12_QUOT_MIN_BOOST_11_10_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x734)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_NSP_ACD_DVM_VAL0_11_0_BMSK                                           0xfff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_NSP_ACD_DVM_VAL0_11_0_SHFT                                                   20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR_RESERVED_49_30_BMSK                                                 0xfffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR_RESERVED_49_30_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x738)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_DDR_CH0_LP5_DCC_PLL1_3197_1_0_BMSK                                   0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_DDR_CH0_LP5_DCC_PLL1_3197_1_0_SHFT                                           30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_DDR_CH0_LP5_DCC_PLL0_3197_BMSK                                       0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_DDR_CH0_LP5_DCC_PLL0_3197_SHFT                                               24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR12_QUOT_MIN_TUR_BMSK                                                0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR12_QUOT_MIN_TUR_SHFT                                                      12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_NSP_ACD_DVM_VAL0_23_12_BMSK                                               0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_NSP_ACD_DVM_VAL0_23_12_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x73c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_3197_3_0_BMSK                            0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_3197_3_0_SHFT                                    28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DQ0_DCC_RDT4_3197_BMSK                                    0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DQ0_DCC_RDT4_3197_SHFT                                           22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DQ0_DCC_IO_DQS_3197_BMSK                                   0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DQ0_DCC_IO_DQS_3197_SHFT                                         16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DQ0_DCC_IO_WCK_3197_BMSK                                     0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DQ0_DCC_IO_WCK_3197_SHFT                                         10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DQ0_DCC_CLK_ADJ_3197_BMSK                                     0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DQ0_DCC_CLK_ADJ_3197_SHFT                                         4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DCC_PLL1_3197_5_2_BMSK                                          0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_DDR_CH0_LP5_DCC_PLL1_3197_5_2_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x740)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH1_LP5_DCC_PLL0_3197_BMSK                                       0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH1_LP5_DCC_PLL0_3197_SHFT                                               26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH0_LP5_CA_DCC_IO_CK_3197_BMSK                                    0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH0_LP5_CA_DCC_IO_CK_3197_SHFT                                           20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH0_LP5_DQ1_DCC_RDT4_3197_BMSK                                      0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH0_LP5_DQ1_DCC_RDT4_3197_SHFT                                           14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH0_LP5_DQ1_DCC_IO_DQS_3197_BMSK                                     0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH0_LP5_DQ1_DCC_IO_DQS_3197_SHFT                                          8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH0_LP5_DQ1_DCC_IO_WCK_3197_BMSK                                       0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH0_LP5_DQ1_DCC_IO_WCK_3197_SHFT                                          2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_3197_5_4_BMSK                                   0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_3197_5_4_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x744)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_3197_1_0_BMSK                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_3197_1_0_SHFT                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DQ0_DCC_RDT4_3197_BMSK                                   0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DQ0_DCC_RDT4_3197_SHFT                                           24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DQ0_DCC_IO_DQS_3197_BMSK                                   0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DQ0_DCC_IO_DQS_3197_SHFT                                         18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DQ0_DCC_IO_WCK_3197_BMSK                                    0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DQ0_DCC_IO_WCK_3197_SHFT                                         12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DQ0_DCC_CLK_ADJ_3197_BMSK                                     0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DQ0_DCC_CLK_ADJ_3197_SHFT                                         6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DCC_PLL1_3197_BMSK                                             0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_DDR_CH1_LP5_DCC_PLL1_3197_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x748)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH0_LP5_DCC_PLL0_547_3_0_BMSK                                    0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH0_LP5_DCC_PLL0_547_3_0_SHFT                                            28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH1_LP5_CA_DCC_IO_CK_3197_BMSK                                    0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH1_LP5_CA_DCC_IO_CK_3197_SHFT                                           22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH1_LP5_DQ1_DCC_RDT4_3197_BMSK                                     0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH1_LP5_DQ1_DCC_RDT4_3197_SHFT                                           16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH1_LP5_DQ1_DCC_IO_DQS_3197_BMSK                                     0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH1_LP5_DQ1_DCC_IO_DQS_3197_SHFT                                         10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH1_LP5_DQ1_DCC_IO_WCK_3197_BMSK                                      0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH1_LP5_DQ1_DCC_IO_WCK_3197_SHFT                                          4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_3197_5_2_BMSK                                   0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_3197_5_2_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x74c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DQ0_DCC_RDT4_547_BMSK                                    0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DQ0_DCC_RDT4_547_SHFT                                            26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DQ0_DCC_IO_DQS_547_BMSK                                   0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DQ0_DCC_IO_DQS_547_SHFT                                          20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DQ0_DCC_IO_WCK_547_BMSK                                     0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DQ0_DCC_IO_WCK_547_SHFT                                          14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DQ0_DCC_CLK_ADJ_547_BMSK                                     0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DQ0_DCC_CLK_ADJ_547_SHFT                                          8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DCC_PLL1_547_BMSK                                              0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DCC_PLL1_547_SHFT                                                 2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DCC_PLL0_547_5_4_BMSK                                           0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_DDR_CH0_LP5_DCC_PLL0_547_5_4_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x750)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH1_LP5_DCC_PLL0_547_1_0_BMSK                                    0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH1_LP5_DCC_PLL0_547_1_0_SHFT                                            30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH0_LP5_CA_DCC_IO_CK_547_BMSK                                    0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH0_LP5_CA_DCC_IO_CK_547_SHFT                                            24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH0_LP5_DQ1_DCC_RDT4_547_BMSK                                      0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH0_LP5_DQ1_DCC_RDT4_547_SHFT                                            18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH0_LP5_DQ1_DCC_IO_DQS_547_BMSK                                     0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH0_LP5_DQ1_DCC_IO_DQS_547_SHFT                                          12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH0_LP5_DQ1_DCC_IO_WCK_547_BMSK                                       0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH0_LP5_DQ1_DCC_IO_WCK_547_SHFT                                           6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_547_BMSK                                       0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_547_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x754)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DQ0_DCC_RDT4_547_3_0_BMSK                                0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DQ0_DCC_RDT4_547_3_0_SHFT                                        28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DQ0_DCC_IO_DQS_547_BMSK                                   0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DQ0_DCC_IO_DQS_547_SHFT                                          22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DQ0_DCC_IO_WCK_547_BMSK                                    0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DQ0_DCC_IO_WCK_547_SHFT                                          16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DQ0_DCC_CLK_ADJ_547_BMSK                                     0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DQ0_DCC_CLK_ADJ_547_SHFT                                         10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DCC_PLL1_547_BMSK                                             0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DCC_PLL1_547_SHFT                                                 4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DCC_PLL0_547_5_2_BMSK                                           0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_DDR_CH1_LP5_DCC_PLL0_547_5_2_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x758)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_CA_DCC_IO_CK_547_BMSK                                    0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_CA_DCC_IO_CK_547_SHFT                                            26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_DQ1_DCC_RDT4_547_BMSK                                     0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_DQ1_DCC_RDT4_547_SHFT                                            20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_DQ1_DCC_IO_DQS_547_BMSK                                     0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_DQ1_DCC_IO_DQS_547_SHFT                                          14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_DQ1_DCC_IO_WCK_547_BMSK                                      0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_DQ1_DCC_IO_WCK_547_SHFT                                           8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_547_BMSK                                       0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_547_SHFT                                          2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_DQ0_DCC_RDT4_547_5_4_BMSK                                       0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_DDR_CH1_LP5_DQ0_DCC_RDT4_547_5_4_SHFT                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x75c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DQ1_DCC_IO_DQS_2133_1_0_BMSK                             0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DQ1_DCC_IO_DQS_2133_1_0_SHFT                                     30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DQ1_DCC_CLK_ADJ_2133_BMSK                                0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DQ1_DCC_CLK_ADJ_2133_SHFT                                        24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DQ0_DCC_IO_DQS_2133_BMSK                                   0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DQ0_DCC_IO_DQS_2133_SHFT                                         18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DQ0_DCC_CLK_ADJ_2133_BMSK                                   0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DQ0_DCC_CLK_ADJ_2133_SHFT                                        12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DCC_PLL1_2133_BMSK                                            0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DCC_PLL1_2133_SHFT                                                6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DCC_PLL0_2133_BMSK                                             0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DDR_CH0_LP4_DCC_PLL0_2133_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x760)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_2133_3_0_BMSK                            0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_2133_3_0_SHFT                                    28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH1_LP4_DCC_PLL1_2133_BMSK                                        0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH1_LP4_DCC_PLL1_2133_SHFT                                               22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH1_LP4_DCC_PLL0_2133_BMSK                                         0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH1_LP4_DCC_PLL0_2133_SHFT                                               16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH0_LP4_CA_DCC_IO_CK_2133_BMSK                                       0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH0_LP4_CA_DCC_IO_CK_2133_SHFT                                           10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH0_LP4_CA_DCC_CLK_ADJ_2133_BMSK                                      0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH0_LP4_CA_DCC_CLK_ADJ_2133_SHFT                                          4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH0_LP4_DQ1_DCC_IO_DQS_2133_5_2_BMSK                                    0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_DDR_CH0_LP4_DQ1_DCC_IO_DQS_2133_5_2_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x764)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_CA_DCC_IO_CK_2133_BMSK                                   0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_CA_DCC_IO_CK_2133_SHFT                                           26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_CA_DCC_CLK_ADJ_2133_BMSK                                  0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_CA_DCC_CLK_ADJ_2133_SHFT                                         20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_DQ1_DCC_IO_DQS_2133_BMSK                                    0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_DQ1_DCC_IO_DQS_2133_SHFT                                         14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_DQ1_DCC_CLK_ADJ_2133_BMSK                                    0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_DQ1_DCC_CLK_ADJ_2133_SHFT                                         8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_DQ0_DCC_IO_DQS_2133_BMSK                                       0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_DQ0_DCC_IO_DQS_2133_SHFT                                          2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_2133_5_4_BMSK                                   0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_2133_5_4_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x768)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DQ1_DCC_IO_DQS_547_1_0_BMSK                              0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DQ1_DCC_IO_DQS_547_1_0_SHFT                                      30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DQ1_DCC_CLK_ADJ_547_BMSK                                 0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DQ1_DCC_CLK_ADJ_547_SHFT                                         24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DQ0_DCC_IO_DQS_547_BMSK                                    0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DQ0_DCC_IO_DQS_547_SHFT                                          18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DQ0_DCC_CLK_ADJ_547_BMSK                                    0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DQ0_DCC_CLK_ADJ_547_SHFT                                         12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DCC_PLL1_547_BMSK                                             0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DCC_PLL1_547_SHFT                                                 6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DCC_PLL0_547_BMSK                                              0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_DDR_CH0_LP4_DCC_PLL0_547_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x76c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_547_3_0_BMSK                             0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_547_3_0_SHFT                                     28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH1_LP4_DCC_PLL1_547_BMSK                                         0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH1_LP4_DCC_PLL1_547_SHFT                                                22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH1_LP4_DCC_PLL0_547_BMSK                                          0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH1_LP4_DCC_PLL0_547_SHFT                                                16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH0_LP4_CA_DCC_IO_CK_547_BMSK                                        0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH0_LP4_CA_DCC_IO_CK_547_SHFT                                            10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH0_LP4_CA_DCC_CLK_ADJ_547_BMSK                                       0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH0_LP4_CA_DCC_CLK_ADJ_547_SHFT                                           4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH0_LP4_DQ1_DCC_IO_DQS_547_5_2_BMSK                                     0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_DDR_CH0_LP4_DQ1_DCC_IO_DQS_547_5_2_SHFT                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x770)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_CA_DCC_IO_CK_547_BMSK                                    0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_CA_DCC_IO_CK_547_SHFT                                            26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_CA_DCC_CLK_ADJ_547_BMSK                                   0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_CA_DCC_CLK_ADJ_547_SHFT                                          20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_DQ1_DCC_IO_DQS_547_BMSK                                     0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_DQ1_DCC_IO_DQS_547_SHFT                                          14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_DQ1_DCC_CLK_ADJ_547_BMSK                                     0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_DQ1_DCC_CLK_ADJ_547_SHFT                                          8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_DQ0_DCC_IO_DQS_547_BMSK                                        0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_DQ0_DCC_IO_DQS_547_SHFT                                           2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_547_5_4_BMSK                                    0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_DDR_CH1_LP4_DQ0_DCC_CLK_ADJ_547_5_4_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x774)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS0_BASE0_7_0_BMSK                                                0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS0_BASE0_7_0_SHFT                                                        24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CPR12_QUOT_MIN_SVS_BMSK                                                0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CPR12_QUOT_MIN_SVS_SHFT                                                      12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CPR12_QUOT_MIN_NOM_BMSK                                                   0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CPR12_QUOT_MIN_NOM_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x778)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS1_BASE1_BMSK                                                    0xffc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS1_BASE1_SHFT                                                            22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS1_BASE0_BMSK                                                      0x3ff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS1_BASE0_SHFT                                                            12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS0_BASE1_BMSK                                                         0xffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS0_BASE1_SHFT                                                             2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS0_BASE0_9_8_BMSK                                                       0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS0_BASE0_9_8_SHFT                                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x77c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS6_OFFSET_1_0_BMSK                                               0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS6_OFFSET_1_0_SHFT                                                       30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS5_OFFSET_BMSK                                                   0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS5_OFFSET_SHFT                                                           25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS4_OFFSET_BMSK                                                    0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS4_OFFSET_SHFT                                                           20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS3_OFFSET_BMSK                                                      0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS3_OFFSET_SHFT                                                           15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS2_OFFSET_BMSK                                                       0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS2_OFFSET_SHFT                                                           10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS1_OFFSET_BMSK                                                        0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS1_OFFSET_SHFT                                                            5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS0_OFFSET_BMSK                                                         0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS0_OFFSET_SHFT                                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x780)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS12_OFFSET_3_0_BMSK                                              0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS12_OFFSET_3_0_SHFT                                                      28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS11_OFFSET_BMSK                                                   0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS11_OFFSET_SHFT                                                          23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS10_OFFSET_BMSK                                                    0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS10_OFFSET_SHFT                                                          18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS9_OFFSET_BMSK                                                      0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS9_OFFSET_SHFT                                                           13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS8_OFFSET_BMSK                                                       0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS8_OFFSET_SHFT                                                            8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS7_OFFSET_BMSK                                                         0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS7_OFFSET_SHFT                                                            3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS6_OFFSET_4_2_BMSK                                                      0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS6_OFFSET_4_2_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x784)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS19_OFFSET_0_BMSK                                                0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS19_OFFSET_0_SHFT                                                        31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS18_OFFSET_BMSK                                                  0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS18_OFFSET_SHFT                                                          26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS17_OFFSET_BMSK                                                   0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS17_OFFSET_SHFT                                                          21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS16_OFFSET_BMSK                                                    0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS16_OFFSET_SHFT                                                          16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS15_OFFSET_BMSK                                                      0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS15_OFFSET_SHFT                                                          11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS14_OFFSET_BMSK                                                       0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS14_OFFSET_SHFT                                                           6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS13_OFFSET_BMSK                                                        0x3e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS13_OFFSET_SHFT                                                           1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS12_OFFSET_4_BMSK                                                       0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS12_OFFSET_4_SHFT                                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x788)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS25_OFFSET_2_0_BMSK                                              0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS25_OFFSET_2_0_SHFT                                                      29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS24_OFFSET_BMSK                                                  0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS24_OFFSET_SHFT                                                          24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS23_OFFSET_BMSK                                                    0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS23_OFFSET_SHFT                                                          19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS22_OFFSET_BMSK                                                     0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS22_OFFSET_SHFT                                                          14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS21_OFFSET_BMSK                                                      0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS21_OFFSET_SHFT                                                           9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS20_OFFSET_BMSK                                                       0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS20_OFFSET_SHFT                                                           4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS19_OFFSET_4_1_BMSK                                                     0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS19_OFFSET_4_1_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x78c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_NSP_ACD_DVM_VAL1_21_0_BMSK                                           0xfffffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_NSP_ACD_DVM_VAL1_21_0_SHFT                                                   10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS_CAL_SEL_BMSK                                                        0x380
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS_CAL_SEL_SHFT                                                            7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS26_OFFSET_BMSK                                                        0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS26_OFFSET_SHFT                                                           2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS25_OFFSET_4_3_BMSK                                                     0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS25_OFFSET_4_3_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x790)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_NSP_ACD_DVM_VAL3_5_0_BMSK                                            0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_NSP_ACD_DVM_VAL3_5_0_SHFT                                                    26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_NSP_ACD_DVM_VAL2_BMSK                                                 0x3fffffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_NSP_ACD_DVM_VAL2_SHFT                                                         2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_NSP_ACD_DVM_VAL1_23_22_BMSK                                                 0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_NSP_ACD_DVM_VAL1_23_22_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x794)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_NSP_ACD_DVM_VAL4_13_0_BMSK                                           0xfffc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_NSP_ACD_DVM_VAL4_13_0_SHFT                                                   18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_NSP_ACD_DVM_VAL3_23_6_BMSK                                              0x3ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_NSP_ACD_DVM_VAL3_23_6_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x798)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_NSP_ACD_DVM_VAL5_21_0_BMSK                                           0xfffffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_NSP_ACD_DVM_VAL5_21_0_SHFT                                                   10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_NSP_ACD_DVM_VAL4_23_14_BMSK                                               0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_NSP_ACD_DVM_VAL4_23_14_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x79c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CPR_APC1_MODE_DISABLE_BMSK                                           0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CPR_APC1_MODE_DISABLE_SHFT                                                   29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CPR_APC0_MODE_DISABLE_BMSK                                           0x1c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CPR_APC0_MODE_DISABLE_SHFT                                                   26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_NSP_ACD_DVM_VAL6_BMSK                                                 0x3fffffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_NSP_ACD_DVM_VAL6_SHFT                                                         2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_NSP_ACD_DVM_VAL5_23_22_BMSK                                                 0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_NSP_ACD_DVM_VAL5_23_22_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x7a0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_DDR_FUSE_MED_1_BMSK                                                  0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_DDR_FUSE_MED_1_SHFT                                                          27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_DDR_FUSE_BIG_3_BMSK                                                   0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_DDR_FUSE_BIG_3_SHFT                                                          21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_DDR_FUSE_BIG_2_BMSK                                                    0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_DDR_FUSE_BIG_2_SHFT                                                          15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_DDR_FUSE_BIG_1_BMSK                                                      0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_DDR_FUSE_BIG_1_SHFT                                                           9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CPR_MX_MODE_DISABLE_BMSK                                                  0x1c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CPR_MX_MODE_DISABLE_SHFT                                                      6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CPR_LPIMX_MODE_DISABLE_BMSK                                                0x38
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CPR_LPIMX_MODE_DISABLE_SHFT                                                   3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CPR_LPICX_MODE_DISABLE_BMSK                                                 0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CPR_LPICX_MODE_DISABLE_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x7a4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR12_QUOT_OFFSET_3_0_BMSK                                           0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR12_QUOT_OFFSET_3_0_SHFT                                                   28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR12_QUOT_MIN_SVS2_BMSK                                              0xfff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR12_QUOT_MIN_SVS2_SHFT                                                     16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_DDR_FUSE_SMALL_3_BMSK                                                    0xc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_DDR_FUSE_SMALL_3_SHFT                                                        14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_DDR_FUSE_SMALL_2_BMSK                                                    0x3000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_DDR_FUSE_SMALL_2_SHFT                                                        12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_DDR_FUSE_SMALL_1_BMSK                                                     0xc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_DDR_FUSE_SMALL_1_SHFT                                                        10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_DDR_FUSE_MED_3_BMSK                                                       0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_DDR_FUSE_MED_3_SHFT                                                           5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_DDR_FUSE_MED_2_BMSK                                                        0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_DDR_FUSE_MED_2_SHFT                                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x7a8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_QF_CPR12_TARG_VOLT_SVS_3_0_BMSK                                      0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_QF_CPR12_TARG_VOLT_SVS_3_0_SHFT                                              28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_QF_CPR12_TARG_VOLT_NOM_BMSK                                           0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_QF_CPR12_TARG_VOLT_NOM_SHFT                                                  22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_QF_CPR12_TARG_VOLT_TUR_BMSK                                            0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_QF_CPR12_TARG_VOLT_TUR_SHFT                                                  16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_QF_CPR12_TARG_VOLT_BOOST_BMSK                                            0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_QF_CPR12_TARG_VOLT_BOOST_SHFT                                                10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_QF_CPR12_TARG_VOLT_BOOSTP_BMSK                                            0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_QF_CPR12_TARG_VOLT_BOOSTP_SHFT                                                4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_CPR12_QUOT_OFFSET_7_4_BMSK                                                  0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_CPR12_QUOT_OFFSET_7_4_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x7ac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2111_2102_BMSK                                           0xffc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2111_2102_SHFT                                                   22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_AON_TARG_VOLT_BMSK                                                     0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_AON_TARG_VOLT_SHFT                                                           16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_AON_AGING_BMSK                                                           0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_AON_AGING_SHFT                                                                8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_QF_CPR12_TARG_VOLT_SVS2_BMSK                                               0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_QF_CPR12_TARG_VOLT_SVS2_SHFT                                                  2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_QF_CPR12_TARG_VOLT_SVS_5_4_BMSK                                             0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_QF_CPR12_TARG_VOLT_SVS_5_4_SHFT                                               0


#endif /* __HALHWIOTSENSFUSES_H__ */
