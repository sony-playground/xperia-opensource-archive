#ifndef __AOSS_MISC_HWIO_H__
#define __AOSS_MISC_HWIO_H__
/*
===========================================================================
*/
/**
    @file aoss_misc_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8550 (Kailua) [kailua_v1.0_p3q2r9.4_rtl_partition_M01]
 
    This file contains HWIO register definitions for the following modules:
        AOSS_MISC

    'Include' filters applied: ACC_COMP_DATA[AOSS_MISC] 

    Generation parameters: 
    { 'filename': 'aoss_misc_hwio.h',
      'header': '#include "msmhwiobase.h"\n#include "msmhwio.h"',
      'module-filter-include': {'AOSS_MISC': ['ACC_COMP_DATA']},
      'modules': ['AOSS_MISC'],
      'output-fvals': True,
      'output-offsets': True,
      'output-phys': True}
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

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/RailwayTargetLib/aoss_misc_hwio.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"
#include "msmhwio.h"

/*----------------------------------------------------------------------------
 * MODULE: AOSS_MISC
 *--------------------------------------------------------------------------*/

#define AOSS_MISC_REG_BASE                                                                          (AOSS_BASE      + 0x01260000)
#define AOSS_MISC_REG_BASE_SIZE                                                                     0x3000
#define AOSS_MISC_REG_BASE_USED                                                                     0x314
#define AOSS_MISC_REG_BASE_PHYS                                                                     (AOSS_BASE_PHYS + 0x01260000)
#define AOSS_MISC_REG_BASE_OFFS                                                                     0x01260000

#define HWIO_MXA_HMX_ACC_COMP_DATA_ADDR                                                             (AOSS_MISC_REG_BASE      + 0x304)
#define HWIO_MXA_HMX_ACC_COMP_DATA_PHYS                                                             (AOSS_MISC_REG_BASE_PHYS + 0x304)
#define HWIO_MXA_HMX_ACC_COMP_DATA_OFFS                                                             (AOSS_MISC_REG_BASE_OFFS + 0x304)
#define HWIO_MXA_HMX_ACC_COMP_DATA_RMSK                                                             0xcfffffff
#define HWIO_MXA_HMX_ACC_COMP_DATA_IN                    \
                in_dword(HWIO_MXA_HMX_ACC_COMP_DATA_ADDR)
#define HWIO_MXA_HMX_ACC_COMP_DATA_INM(m)            \
                in_dword_masked(HWIO_MXA_HMX_ACC_COMP_DATA_ADDR, m)
#define HWIO_MXA_HMX_ACC_COMP_DATA_OUT(v)            \
                out_dword(HWIO_MXA_HMX_ACC_COMP_DATA_ADDR,v)
#define HWIO_MXA_HMX_ACC_COMP_DATA_OUTM(m,v) \
                out_dword_masked_ns(HWIO_MXA_HMX_ACC_COMP_DATA_ADDR,m,v,HWIO_MXA_HMX_ACC_COMP_DATA_IN)
#define HWIO_MXA_HMX_ACC_COMP_DATA_COMP_OUTPUT_RAW_BMSK                                             0x80000000
#define HWIO_MXA_HMX_ACC_COMP_DATA_COMP_OUTPUT_RAW_SHFT                                                     31
#define HWIO_MXA_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_BMSK                                           0x40000000
#define HWIO_MXA_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_SHFT                                                   30
#define HWIO_MXA_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_OVERRIDE_VAL_BMSK                               0x8000000
#define HWIO_MXA_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_OVERRIDE_VAL_SHFT                                      27
#define HWIO_MXA_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_OVERRIDE_EN_BMSK                                0x4000000
#define HWIO_MXA_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_OVERRIDE_EN_SHFT                                       26
#define HWIO_MXA_HMX_ACC_COMP_DATA_ATEST_EN_BMSK                                                     0x2000000
#define HWIO_MXA_HMX_ACC_COMP_DATA_ATEST_EN_SHFT                                                            25
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_ATEST0_PATH_SEL_BUF_OR_BYPSW_BMSK                          0x1000000
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_ATEST0_PATH_SEL_BUF_OR_BYPSW_SHFT                                 24
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_ATEST1_PATH_SEL_BUF_OR_BYPSW_BMSK                           0x800000
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_ATEST1_PATH_SEL_BUF_OR_BYPSW_SHFT                                 23
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_VREF_SEL_BMSK                                               0x7e0000
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_VREF_SEL_SHFT                                                     17
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_HYST_SEL_BMSK                                                0x1c000
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_HYST_SEL_SHFT                                                     14
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_ATEST_VINPATH_DIS_BMSK                                        0x2000
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_ATEST_VINPATH_DIS_SHFT                                            13
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_ATEST0_MUX_SEL_BMSK                                           0x1800
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_ATEST0_MUX_SEL_SHFT                                               11
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_ATEST1_MUX_SEL_BMSK                                            0x600
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_ATEST1_MUX_SEL_SHFT                                                9
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_VREF_DIS_BYFORCE_BMSK                                          0x100
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_VREF_DIS_BYFORCE_SHFT                                              8
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_VIN_DIS_BYFORCE_BMSK                                            0x80
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_VIN_DIS_BYFORCE_SHFT                                               7
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_HYST_UP_EN_BMSK                                                 0x40
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_HYST_UP_EN_SHFT                                                    6
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_HYST_DN_EN_BMSK                                                 0x20
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_HYST_DN_EN_SHFT                                                    5
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_IBIAS1_BMSK                                                     0x1c
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_IBIAS1_SHFT                                                        2
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_IBIAS2_BMSK                                                      0x2
#define HWIO_MXA_HMX_ACC_COMP_DATA_CONFIG_IBIAS2_SHFT                                                        1
#define HWIO_MXA_HMX_ACC_COMP_DATA_COMP_EN_BMSK                                                            0x1
#define HWIO_MXA_HMX_ACC_COMP_DATA_COMP_EN_SHFT                                                              0

#define HWIO_MXC_HMX_ACC_COMP_DATA_ADDR                                                             (AOSS_MISC_REG_BASE      + 0x308)
#define HWIO_MXC_HMX_ACC_COMP_DATA_PHYS                                                             (AOSS_MISC_REG_BASE_PHYS + 0x308)
#define HWIO_MXC_HMX_ACC_COMP_DATA_OFFS                                                             (AOSS_MISC_REG_BASE_OFFS + 0x308)
#define HWIO_MXC_HMX_ACC_COMP_DATA_RMSK                                                             0xefffffff
#define HWIO_MXC_HMX_ACC_COMP_DATA_IN                    \
                in_dword(HWIO_MXC_HMX_ACC_COMP_DATA_ADDR)
#define HWIO_MXC_HMX_ACC_COMP_DATA_INM(m)            \
                in_dword_masked(HWIO_MXC_HMX_ACC_COMP_DATA_ADDR, m)
#define HWIO_MXC_HMX_ACC_COMP_DATA_OUT(v)            \
                out_dword(HWIO_MXC_HMX_ACC_COMP_DATA_ADDR,v)
#define HWIO_MXC_HMX_ACC_COMP_DATA_OUTM(m,v) \
                out_dword_masked_ns(HWIO_MXC_HMX_ACC_COMP_DATA_ADDR,m,v,HWIO_MXC_HMX_ACC_COMP_DATA_IN)
#define HWIO_MXC_HMX_ACC_COMP_DATA_COMP_OUTPUT_RAW_BMSK                                             0x80000000
#define HWIO_MXC_HMX_ACC_COMP_DATA_COMP_OUTPUT_RAW_SHFT                                                     31
#define HWIO_MXC_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_BMSK                                           0x40000000
#define HWIO_MXC_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_SHFT                                                   30
#define HWIO_MXC_HMX_ACC_COMP_DATA_MXC_RAIL_MERGED_BMSK                                             0x20000000
#define HWIO_MXC_HMX_ACC_COMP_DATA_MXC_RAIL_MERGED_SHFT                                                     29
#define HWIO_MXC_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_OVERRIDE_VAL_BMSK                               0x8000000
#define HWIO_MXC_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_OVERRIDE_VAL_SHFT                                      27
#define HWIO_MXC_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_OVERRIDE_EN_BMSK                                0x4000000
#define HWIO_MXC_HMX_ACC_COMP_DATA_HMX_RA_SEL_OUTPUT_OVERRIDE_EN_SHFT                                       26
#define HWIO_MXC_HMX_ACC_COMP_DATA_ATEST_EN_BMSK                                                     0x2000000
#define HWIO_MXC_HMX_ACC_COMP_DATA_ATEST_EN_SHFT                                                            25
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_ATEST0_PATH_SEL_BUF_OR_BYPSW_BMSK                          0x1000000
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_ATEST0_PATH_SEL_BUF_OR_BYPSW_SHFT                                 24
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_ATEST1_PATH_SEL_BUF_OR_BYPSW_BMSK                           0x800000
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_ATEST1_PATH_SEL_BUF_OR_BYPSW_SHFT                                 23
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_VREF_SEL_BMSK                                               0x7e0000
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_VREF_SEL_SHFT                                                     17
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_HYST_SEL_BMSK                                                0x1c000
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_HYST_SEL_SHFT                                                     14
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_ATEST_VINPATH_DIS_BMSK                                        0x2000
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_ATEST_VINPATH_DIS_SHFT                                            13
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_ATEST0_MUX_SEL_BMSK                                           0x1800
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_ATEST0_MUX_SEL_SHFT                                               11
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_ATEST1_MUX_SEL_BMSK                                            0x600
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_ATEST1_MUX_SEL_SHFT                                                9
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_VREF_DIS_BYFORCE_BMSK                                          0x100
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_VREF_DIS_BYFORCE_SHFT                                              8
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_VIN_DIS_BYFORCE_BMSK                                            0x80
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_VIN_DIS_BYFORCE_SHFT                                               7
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_HYST_UP_EN_BMSK                                                 0x40
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_HYST_UP_EN_SHFT                                                    6
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_HYST_DN_EN_BMSK                                                 0x20
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_HYST_DN_EN_SHFT                                                    5
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_IBIAS1_BMSK                                                     0x1c
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_IBIAS1_SHFT                                                        2
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_IBIAS2_BMSK                                                      0x2
#define HWIO_MXC_HMX_ACC_COMP_DATA_CONFIG_IBIAS2_SHFT                                                        1
#define HWIO_MXC_HMX_ACC_COMP_DATA_COMP_EN_BMSK                                                            0x1
#define HWIO_MXC_HMX_ACC_COMP_DATA_COMP_EN_SHFT                                                              0

#define HWIO_MXA_LMX_ACC_COMP_DATA_ADDR                                                             (AOSS_MISC_REG_BASE      + 0x310)
#define HWIO_MXA_LMX_ACC_COMP_DATA_PHYS                                                             (AOSS_MISC_REG_BASE_PHYS + 0x310)
#define HWIO_MXA_LMX_ACC_COMP_DATA_OFFS                                                             (AOSS_MISC_REG_BASE_OFFS + 0x310)
#define HWIO_MXA_LMX_ACC_COMP_DATA_RMSK                                                             0xffffffff
#define HWIO_MXA_LMX_ACC_COMP_DATA_IN                    \
                in_dword(HWIO_MXA_LMX_ACC_COMP_DATA_ADDR)
#define HWIO_MXA_LMX_ACC_COMP_DATA_INM(m)            \
                in_dword_masked(HWIO_MXA_LMX_ACC_COMP_DATA_ADDR, m)
#define HWIO_MXA_LMX_ACC_COMP_DATA_OUT(v)            \
                out_dword(HWIO_MXA_LMX_ACC_COMP_DATA_ADDR,v)
#define HWIO_MXA_LMX_ACC_COMP_DATA_OUTM(m,v) \
                out_dword_masked_ns(HWIO_MXA_LMX_ACC_COMP_DATA_ADDR,m,v,HWIO_MXA_LMX_ACC_COMP_DATA_IN)
#define HWIO_MXA_LMX_ACC_COMP_DATA_COMP_OUTPUT_RAW_BMSK                                             0x80000000
#define HWIO_MXA_LMX_ACC_COMP_DATA_COMP_OUTPUT_RAW_SHFT                                                     31
#define HWIO_MXA_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_BMSK                                          0x60000000
#define HWIO_MXA_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_SHFT                                                  29
#define HWIO_MXA_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_OVERRIDE_VAL_BMSK                             0x18000000
#define HWIO_MXA_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_OVERRIDE_VAL_SHFT                                     27
#define HWIO_MXA_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_OVERRIDE_EN_BMSK                               0x4000000
#define HWIO_MXA_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_OVERRIDE_EN_SHFT                                      26
#define HWIO_MXA_LMX_ACC_COMP_DATA_ATEST_EN_BMSK                                                     0x2000000
#define HWIO_MXA_LMX_ACC_COMP_DATA_ATEST_EN_SHFT                                                            25
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_ATEST0_PATH_SEL_BUF_OR_BYPSW_BMSK                          0x1000000
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_ATEST0_PATH_SEL_BUF_OR_BYPSW_SHFT                                 24
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_ATEST1_PATH_SEL_BUF_OR_BYPSW_BMSK                           0x800000
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_ATEST1_PATH_SEL_BUF_OR_BYPSW_SHFT                                 23
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_VREF_SEL_BMSK                                               0x7e0000
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_VREF_SEL_SHFT                                                     17
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_HYST_SEL_BMSK                                                0x1c000
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_HYST_SEL_SHFT                                                     14
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_ATEST_VINPATH_DIS_BMSK                                        0x2000
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_ATEST_VINPATH_DIS_SHFT                                            13
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_ATEST0_MUX_SEL_BMSK                                           0x1800
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_ATEST0_MUX_SEL_SHFT                                               11
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_ATEST1_MUX_SEL_BMSK                                            0x600
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_ATEST1_MUX_SEL_SHFT                                                9
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_VREF_DIS_BYFORCE_BMSK                                          0x100
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_VREF_DIS_BYFORCE_SHFT                                              8
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_VIN_DIS_BYFORCE_BMSK                                            0x80
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_VIN_DIS_BYFORCE_SHFT                                               7
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_HYST_UP_EN_BMSK                                                 0x40
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_HYST_UP_EN_SHFT                                                    6
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_HYST_DN_EN_BMSK                                                 0x20
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_HYST_DN_EN_SHFT                                                    5
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_IBIAS1_BMSK                                                     0x1c
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_IBIAS1_SHFT                                                        2
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_IBIAS2_BMSK                                                      0x2
#define HWIO_MXA_LMX_ACC_COMP_DATA_CONFIG_IBIAS2_SHFT                                                        1
#define HWIO_MXA_LMX_ACC_COMP_DATA_COMP_EN_BMSK                                                            0x1
#define HWIO_MXA_LMX_ACC_COMP_DATA_COMP_EN_SHFT                                                              0

#define HWIO_MXC_LMX_ACC_COMP_DATA_ADDR                                                             (AOSS_MISC_REG_BASE      + 0x314)
#define HWIO_MXC_LMX_ACC_COMP_DATA_PHYS                                                             (AOSS_MISC_REG_BASE_PHYS + 0x314)
#define HWIO_MXC_LMX_ACC_COMP_DATA_OFFS                                                             (AOSS_MISC_REG_BASE_OFFS + 0x314)
#define HWIO_MXC_LMX_ACC_COMP_DATA_RMSK                                                             0xffffffff
#define HWIO_MXC_LMX_ACC_COMP_DATA_IN                    \
                in_dword(HWIO_MXC_LMX_ACC_COMP_DATA_ADDR)
#define HWIO_MXC_LMX_ACC_COMP_DATA_INM(m)            \
                in_dword_masked(HWIO_MXC_LMX_ACC_COMP_DATA_ADDR, m)
#define HWIO_MXC_LMX_ACC_COMP_DATA_OUT(v)            \
                out_dword(HWIO_MXC_LMX_ACC_COMP_DATA_ADDR,v)
#define HWIO_MXC_LMX_ACC_COMP_DATA_OUTM(m,v) \
                out_dword_masked_ns(HWIO_MXC_LMX_ACC_COMP_DATA_ADDR,m,v,HWIO_MXC_LMX_ACC_COMP_DATA_IN)
#define HWIO_MXC_LMX_ACC_COMP_DATA_COMP_OUTPUT_RAW_BMSK                                             0x80000000
#define HWIO_MXC_LMX_ACC_COMP_DATA_COMP_OUTPUT_RAW_SHFT                                                     31
#define HWIO_MXC_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_BMSK                                          0x60000000
#define HWIO_MXC_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_SHFT                                                  29
#define HWIO_MXC_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_OVERRIDE_VAL_BMSK                             0x18000000
#define HWIO_MXC_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_OVERRIDE_VAL_SHFT                                     27
#define HWIO_MXC_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_OVERRIDE_EN_BMSK                               0x4000000
#define HWIO_MXC_LMX_ACC_COMP_DATA_LMX_ACC_9_8_OUTPUT_OVERRIDE_EN_SHFT                                      26
#define HWIO_MXC_LMX_ACC_COMP_DATA_ATEST_EN_BMSK                                                     0x2000000
#define HWIO_MXC_LMX_ACC_COMP_DATA_ATEST_EN_SHFT                                                            25
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_ATEST0_PATH_SEL_BUF_OR_BYPSW_BMSK                          0x1000000
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_ATEST0_PATH_SEL_BUF_OR_BYPSW_SHFT                                 24
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_ATEST1_PATH_SEL_BUF_OR_BYPSW_BMSK                           0x800000
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_ATEST1_PATH_SEL_BUF_OR_BYPSW_SHFT                                 23
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_VREF_SEL_BMSK                                               0x7e0000
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_VREF_SEL_SHFT                                                     17
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_HYST_SEL_BMSK                                                0x1c000
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_HYST_SEL_SHFT                                                     14
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_ATEST_VINPATH_DIS_BMSK                                        0x2000
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_ATEST_VINPATH_DIS_SHFT                                            13
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_ATEST0_MUX_SEL_BMSK                                           0x1800
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_ATEST0_MUX_SEL_SHFT                                               11
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_ATEST1_MUX_SEL_BMSK                                            0x600
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_ATEST1_MUX_SEL_SHFT                                                9
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_VREF_DIS_BYFORCE_BMSK                                          0x100
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_VREF_DIS_BYFORCE_SHFT                                              8
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_VIN_DIS_BYFORCE_BMSK                                            0x80
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_VIN_DIS_BYFORCE_SHFT                                               7
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_HYST_UP_EN_BMSK                                                 0x40
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_HYST_UP_EN_SHFT                                                    6
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_HYST_DN_EN_BMSK                                                 0x20
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_HYST_DN_EN_SHFT                                                    5
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_IBIAS1_BMSK                                                     0x1c
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_IBIAS1_SHFT                                                        2
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_IBIAS2_BMSK                                                      0x2
#define HWIO_MXC_LMX_ACC_COMP_DATA_CONFIG_IBIAS2_SHFT                                                        1
#define HWIO_MXC_LMX_ACC_COMP_DATA_COMP_EN_BMSK                                                            0x1
#define HWIO_MXC_LMX_ACC_COMP_DATA_COMP_EN_SHFT                                                              0


#endif /* __AOSS_MISC_HWIO_H__ */