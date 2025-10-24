#ifndef __HWIO_REFGEN_H__
#define __HWIO_REFGEN_H__
/*
===========================================================================
*/
/**
    @file hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SC8280XP (Makena) [makena_v1.0_p3q2r70_MTO_SWI]
 
    This file contains HWIO register definitions for the following modules:
        AHB2PHY_.*REFGEN.*

    'Exclude' filters applied: DUMMY RESERVED 

    Generation parameters: 
    { 'exclude-no-doc': True,
      'exclude-reserved': True,
      'explicit-addressing': True,
      'filename': 'hwio.h',
      'module-filter-exclude': {},
      'module-filter-include': {},
      'modules': ['AHB2PHY_.*REFGEN.*'],
      'output-offsets': True,
      'output-phys': True,
      'rmsk-input': True}
*/
/*
    ===========================================================================

    Copyright (c) 2020 Qualcomm Technologies, Inc.
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

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/Usb4Dxe/hwio_refgen_swi.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_0PHY_REFGEN_0_PHY_REFGEN_0_CM_PHY_REFGEN
 *--------------------------------------------------------------------------*/

#define AHB2PHY_0PHY_REFGEN_0_PHY_REFGEN_0_CM_PHY_REFGEN_REG_BASE                                   (AHB2PHY_0AHB2PHY_0_BASE            + 0x00000000)
#define AHB2PHY_0PHY_REFGEN_0_PHY_REFGEN_0_CM_PHY_REFGEN_REG_BASE_SIZE                              0x9c
#define AHB2PHY_0PHY_REFGEN_0_PHY_REFGEN_0_CM_PHY_REFGEN_REG_BASE_USED                              0x98
#define AHB2PHY_0PHY_REFGEN_0_PHY_REFGEN_0_CM_PHY_REFGEN_REG_BASE_PHYS                              (AHB2PHY_0AHB2PHY_0_BASE_PHYS + 0x00000000)
#define AHB2PHY_0PHY_REFGEN_0_PHY_REFGEN_0_CM_PHY_REFGEN_REG_BASE_OFFS                              0x00000000

#define HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_ADDR(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_PHYS(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_OFFS                                                     (0x0)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_RMSK                                                           0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_ATB_SEL_7_0_BMSK                                               0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ATB_SEL_ATB_SEL_7_0_SHFT                                                  0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_ADDR(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_PHYS(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_OFFS                                                    (0x4)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_RMSK                                                           0x7
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_BG_WAIT_TIME_BMSK                                              0x7
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_TIMER_BG_WAIT_TIME_SHFT                                                0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_ADDR(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_PHYS(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_OFFS                                                     (0x8)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_RMSK                                                           0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_REFGEN_STATUS_MUX_BMSK                                         0x40
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_REFGEN_STATUS_MUX_SHFT                                            6
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_REFGEN_STATUS_BMSK                                             0x20
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_REFGEN_STATUS_SHFT                                                5
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_IE_EN_MUX_BMSK                                                 0x10
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_IE_EN_MUX_SHFT                                                    4
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_IE_EN_BMSK                                                      0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_IE_EN_SHFT                                                        3
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_PWRDN_B_BMSK                                                    0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_PWRDN_B_SHFT                                                      2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_BIAS_EN_MUX_BMSK                                                0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_BIAS_EN_MUX_SHFT                                                  1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_BIAS_EN_BMSK                                                    0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BIAS_EN_BIAS_EN_SHFT                                                      0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_ADDR(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_PHYS(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_OFFS                                           (0xc)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_RMSK                                                  0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_BMSK                                0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_SHFT                                  3
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_IE_EN_OUT_BMSK                                        0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_IE_EN_OUT_SHFT                                          2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_BG_EN_OUT_BMSK                                        0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_BG_EN_OUT_SHFT                                          1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_BIAS_EN_OUT_BMSK                                      0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_STATUS_BIAS_EN_OUT_SHFT                                        0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_ADDR(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_PHYS(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_OFFS                                                    (0x10)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_BGT_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGT_TRIM_BGT_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_ADDR(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_PHYS(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_OFFS                                                    (0x14)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_BGV_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BGV_TRIM_BGV_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_ADDR(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_PHYS(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_OFFS                                                     (0x18)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_RMSK                                                           0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_BG_EN_SYNC_MUX_BMSK                                            0x20
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_BG_EN_SYNC_MUX_SHFT                                               5
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_BG_EN_SYNC_BMSK                                                0x10
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_BG_EN_SYNC_SHFT                                                   4
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_EFUSE_BYPASS_BMSK                                               0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_EFUSE_BYPASS_SHFT                                                 3
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_BANDGAP_EN_MUX_BMSK                                             0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_BANDGAP_EN_MUX_SHFT                                               2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_BANDGAP_EN_BMSK                                                 0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_BANDGAP_EN_SHFT                                                   1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_BANDGAP_BYPASS_BMSK                                             0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_BG_CTRL_BANDGAP_BYPASS_SHFT                                               0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_ADDR(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_PHYS(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_OFFS                                                   (0x1c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_RMSK                                                          0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_BYPASS_RSM_RESTRIM_BMSK                                       0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_BYPASS_RSM_RESTRIM_SHFT                                         3
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_BYPASS_RSM_BANDGAP_BMSK                                       0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_BYPASS_RSM_BANDGAP_SHFT                                         2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_RSM_START_MUX_BMSK                                            0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_RSM_START_MUX_SHFT                                              1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_RSM_START_BMSK                                                0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RSM_CNTRL_RSM_START_SHFT                                                  0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_ADDR(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_PHYS(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_OFFS                                           (0x20)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_RMSK                                                 0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_BMSK                               0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_SHFT                                  0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_ADDR(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_PHYS(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_OFFS                                         (0x24)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_RMSK                                               0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_BMSK                       0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_SHFT                          0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_ADDR(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_PHYS(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_OFFS                                            (0x28)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_RMSK                                                   0x3
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_RESTRIM_EN_MUX_BMSK                                    0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_RESTRIM_EN_MUX_SHFT                                      1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_RESTRIM_EN_BMSK                                        0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RES_TRIM_CONTROL_RESTRIM_EN_SHFT                                          0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_ADDR(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_PHYS(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_OFFS                                                     (0x2c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_RMSK                                                           0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_ADC_FROM_ATB_BMSK                                              0x40
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_ADC_FROM_ATB_SHFT                                                 6
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_ADC_ATB_MUXSEL_BMSK                                            0x20
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_ADC_ATB_MUXSEL_SHFT                                               5
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_DIGITAL_ECO_BKUP_BMSK                                          0x1e
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_DIGITAL_ECO_BKUP_SHFT                                             1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_ADC_EN_BMSK                                                     0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_SEL_ADC_EN_SHFT                                                       0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_ADDR(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_PHYS(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_OFFS                                                     (0x30)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_RMSK                                                           0x1f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_ADC_CLK_DIV_BMSK                                               0x1f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CLK_ADC_CLK_DIV_SHFT                                                  0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADDR(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_PHYS(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_OFFS                                                    (0x34)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_RMSK                                                           0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADC_FREEZE_CODE_BMSK                                           0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADC_FREEZE_CODE_SHFT                                             3
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADC_SIGNERR_POL_FLIP_BMSK                                      0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADC_SIGNERR_POL_FLIP_SHFT                                        2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADC_ENABLE_BMSK                                                0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADC_ENABLE_SHFT                                                  1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADC_CLK_ENABLE_BMSK                                            0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CTRL_ADC_CLK_ENABLE_SHFT                                              0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS0_ADDR(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS0_PHYS(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS0_OFFS                                        (0x38)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS0_RMSK                                              0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_BMSK                             0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_SHFT                                0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS1_ADDR(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS1_PHYS(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS1_OFFS                                        (0x3c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS1_RMSK                                             0x300
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_BMSK                            0x300
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_SHFT                                8

#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_ADDR(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_PHYS(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_OFFS                                             (0x40)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_RMSK                                                    0x7
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_RESCAL_ERR_BMSK                                         0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_RESCAL_ERR_SHFT                                           2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_RESETSM_BMSK                                            0x3
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESET_SM_STATUS_RESETSM_SHFT                                              0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_ADDR(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_PHYS(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_OFFS                                         (0x44)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_RMSK                                               0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_REFGEN_READY_BMSK                                  0x80
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_REFGEN_READY_SHFT                                     7
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_RESTRIM_CODE_BMSK                                  0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_RESTRIM_CODE_STATUS_RESTRIM_CODE_SHFT                                     0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_ADDR(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_PHYS(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_OFFS                                                    (0x48)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_RMSK                                                           0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_SW_RESET_BMSK                                                  0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_SW_RESET_SW_RESET_SHFT                                                    0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS0_ADDR(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS0_PHYS(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS0_OFFS                                                  (0x4c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS0_RMSK                                                        0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS0_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS0_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS0_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS0_DEBUG_BUS_7_0_BMSK                                          0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS0_DEBUG_BUS_7_0_SHFT                                             0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS1_ADDR(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS1_PHYS(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS1_OFFS                                                  (0x50)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS1_RMSK                                                        0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS1_DEBUG_BUS_15_8_BMSK                                         0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS1_DEBUG_BUS_15_8_SHFT                                            0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_ADDR(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_PHYS(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_OFFS                                               (0x54)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_RMSK                                                      0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_DEBUG_BUS_SEL_BMSK                                        0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_BUS_SEL_DEBUG_BUS_SEL_SHFT                                          0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_ADDR(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_PHYS(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_OFFS                                                  (0x58)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_RMSK                                                         0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_FORCE_REFGEN_READY_BMSK                                      0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_FORCE_REFGEN_READY_SHFT                                        3
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_BMSK                                   0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_SHFT                                     2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_RESTRIM_DEBUG_MODE_BMSK                                      0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_RESTRIM_DEBUG_MODE_SHFT                                        1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_DISABLE_CLOCK_GATING_BMSK                                    0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_DEBUG_CTRL_DISABLE_CLOCK_GATING_SHFT                                      0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_ADDR(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_PHYS(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_OFFS                                            (0x5c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_RMSK                                                  0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_REFGEN_CTRL1_BMSK                                     0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL1_REFGEN_CTRL1_SHFT                                        0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_ADDR(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_PHYS(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_OFFS                                            (0x60)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_RMSK                                                  0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_REFGEN_CTRL2_BMSK                                     0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CMN_REFGEN_CTRL2_REFGEN_CTRL2_SHFT                                        0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_ADDR(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_PHYS(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_OFFS                                                (0x64)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_RMSK                                                      0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_BMSK                                    0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_SHFT                                       0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_ADDR(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_PHYS(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_OFFS                                                (0x68)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_RMSK                                                      0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_BMSK                                   0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_SHFT                                      0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_ADDR(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_PHYS(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_OFFS                                                (0x6c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_RMSK                                                      0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_BMSK                                0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_SHFT                                   0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_ADDR(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_PHYS(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_OFFS                                                (0x70)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_RMSK                                                      0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_BMSK                               0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_SHFT                                  0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS1_ADDR(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS1_PHYS(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS1_OFFS                                              (0x74)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS1_RMSK                                                    0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_BMSK                                   0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_SHFT                                      0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS2_ADDR(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS2_PHYS(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS2_OFFS                                              (0x78)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS2_RMSK                                                    0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS2_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS2_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_BMSK                                  0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_SHFT                                     0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_ADDR(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_PHYS(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_OFFS                                                (0x7c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_RMSK                                                       0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_STATUS_WAIT_TIME_BMSK                                      0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_0_STATUS_TIMER_STATUS_WAIT_TIME_SHFT                                        0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_ADDR(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_PHYS(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_OFFS                                                (0x80)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_RMSK                                                       0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_PWRDWN_B_SW_BMSK                                           0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_0_PWRDWN_CTRL5_PWRDWN_B_SW_SHFT                                             0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADDR(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_PHYS(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_OFFS                                          (0x84)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_RMSK                                                0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADC_DSM_MISC_BMSK                                   0xc0
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADC_DSM_MISC_SHFT                                      6
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADC_ATT_EN_BMSK                                     0x20
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADC_ATT_EN_SHFT                                        5
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADC_DTH_SET_BMSK                                    0x10
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADC_DTH_SET_SHFT                                       4
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADC_DTH_DAC_BMSK                                     0xe
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADC_DTH_DAC_SHFT                                       1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADC_DTH_EN_BMSK                                      0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_ADC_MODULATOR_CTRL_ADC_DTH_EN_SHFT                                        0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_ADDR(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_PHYS(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_OFFS                                    (0x88)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_RMSK                                          0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_BMSK                        0x80
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_SHFT                           7
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_BMSK                              0x40
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_SHFT                                 6
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_BMSK                                0x20
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_SHFT                                   5
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_BMSK                       0x18
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_SHFT                          3
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_BMSK                 0x7
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_SHFT                   0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS0_PHYS(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS0_OFFS                                   (0x8c)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS0_RMSK                                         0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_BMSK                   0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_SHFT                      0

#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS1_PHYS(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS1_OFFS                                   (0x90)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS1_RMSK                                       0xff00
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_BMSK                0xff00
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_SHFT                     8

#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS2_PHYS(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS2_OFFS                                   (0x94)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS2_RMSK                                     0xff0000
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS2_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_BMSK             0xff0000
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_SHFT                   16

#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS3_PHYS(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS3_OFFS                                   (0x98)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS3_RMSK                                          0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS3_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_BMSK                  0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_0_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_SHFT                    0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_0PHY_REFGEN_1_PHY_REFGEN_1_CM_PHY_REFGEN
 *--------------------------------------------------------------------------*/

#define AHB2PHY_0PHY_REFGEN_1_PHY_REFGEN_1_CM_PHY_REFGEN_REG_BASE                                   (AHB2PHY_0AHB2PHY_0_BASE            + 0x00001000)
#define AHB2PHY_0PHY_REFGEN_1_PHY_REFGEN_1_CM_PHY_REFGEN_REG_BASE_SIZE                              0x9c
#define AHB2PHY_0PHY_REFGEN_1_PHY_REFGEN_1_CM_PHY_REFGEN_REG_BASE_USED                              0x98
#define AHB2PHY_0PHY_REFGEN_1_PHY_REFGEN_1_CM_PHY_REFGEN_REG_BASE_PHYS                              (AHB2PHY_0AHB2PHY_0_BASE_PHYS + 0x00001000)
#define AHB2PHY_0PHY_REFGEN_1_PHY_REFGEN_1_CM_PHY_REFGEN_REG_BASE_OFFS                              0x00001000

#define HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_ADDR(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_PHYS(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_OFFS                                                     (0x0)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_RMSK                                                           0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_ATB_SEL_7_0_BMSK                                               0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ATB_SEL_ATB_SEL_7_0_SHFT                                                  0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_ADDR(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_PHYS(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_OFFS                                                    (0x4)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_RMSK                                                           0x7
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_BG_WAIT_TIME_BMSK                                              0x7
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_TIMER_BG_WAIT_TIME_SHFT                                                0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_ADDR(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_PHYS(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_OFFS                                                     (0x8)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_RMSK                                                           0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_REFGEN_STATUS_MUX_BMSK                                         0x40
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_REFGEN_STATUS_MUX_SHFT                                            6
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_REFGEN_STATUS_BMSK                                             0x20
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_REFGEN_STATUS_SHFT                                                5
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_IE_EN_MUX_BMSK                                                 0x10
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_IE_EN_MUX_SHFT                                                    4
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_IE_EN_BMSK                                                      0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_IE_EN_SHFT                                                        3
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_PWRDN_B_BMSK                                                    0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_PWRDN_B_SHFT                                                      2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_BIAS_EN_MUX_BMSK                                                0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_BIAS_EN_MUX_SHFT                                                  1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_BIAS_EN_BMSK                                                    0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BIAS_EN_BIAS_EN_SHFT                                                      0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_ADDR(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_PHYS(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_OFFS                                           (0xc)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_RMSK                                                  0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_BMSK                                0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_SHFT                                  3
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_IE_EN_OUT_BMSK                                        0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_IE_EN_OUT_SHFT                                          2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_BG_EN_OUT_BMSK                                        0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_BG_EN_OUT_SHFT                                          1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_BIAS_EN_OUT_BMSK                                      0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_STATUS_BIAS_EN_OUT_SHFT                                        0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_ADDR(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_PHYS(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_OFFS                                                    (0x10)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_BGT_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGT_TRIM_BGT_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_ADDR(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_PHYS(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_OFFS                                                    (0x14)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_BGV_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BGV_TRIM_BGV_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_ADDR(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_PHYS(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_OFFS                                                     (0x18)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_RMSK                                                           0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_BG_EN_SYNC_MUX_BMSK                                            0x20
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_BG_EN_SYNC_MUX_SHFT                                               5
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_BG_EN_SYNC_BMSK                                                0x10
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_BG_EN_SYNC_SHFT                                                   4
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_EFUSE_BYPASS_BMSK                                               0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_EFUSE_BYPASS_SHFT                                                 3
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_BANDGAP_EN_MUX_BMSK                                             0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_BANDGAP_EN_MUX_SHFT                                               2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_BANDGAP_EN_BMSK                                                 0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_BANDGAP_EN_SHFT                                                   1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_BANDGAP_BYPASS_BMSK                                             0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_BG_CTRL_BANDGAP_BYPASS_SHFT                                               0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_ADDR(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_PHYS(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_OFFS                                                   (0x1c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_RMSK                                                          0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_BYPASS_RSM_RESTRIM_BMSK                                       0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_BYPASS_RSM_RESTRIM_SHFT                                         3
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_BYPASS_RSM_BANDGAP_BMSK                                       0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_BYPASS_RSM_BANDGAP_SHFT                                         2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_RSM_START_MUX_BMSK                                            0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_RSM_START_MUX_SHFT                                              1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_RSM_START_BMSK                                                0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RSM_CNTRL_RSM_START_SHFT                                                  0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_ADDR(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_PHYS(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_OFFS                                           (0x20)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_RMSK                                                 0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_BMSK                               0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_SHFT                                  0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_ADDR(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_PHYS(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_OFFS                                         (0x24)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_RMSK                                               0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_BMSK                       0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_SHFT                          0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_ADDR(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_PHYS(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_OFFS                                            (0x28)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_RMSK                                                   0x3
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_RESTRIM_EN_MUX_BMSK                                    0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_RESTRIM_EN_MUX_SHFT                                      1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_RESTRIM_EN_BMSK                                        0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RES_TRIM_CONTROL_RESTRIM_EN_SHFT                                          0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_ADDR(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_PHYS(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_OFFS                                                     (0x2c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_RMSK                                                           0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_ADC_FROM_ATB_BMSK                                              0x40
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_ADC_FROM_ATB_SHFT                                                 6
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_ADC_ATB_MUXSEL_BMSK                                            0x20
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_ADC_ATB_MUXSEL_SHFT                                               5
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_DIGITAL_ECO_BKUP_BMSK                                          0x1e
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_DIGITAL_ECO_BKUP_SHFT                                             1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_ADC_EN_BMSK                                                     0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_SEL_ADC_EN_SHFT                                                       0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_ADDR(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_PHYS(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_OFFS                                                     (0x30)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_RMSK                                                           0x1f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_ADC_CLK_DIV_BMSK                                               0x1f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CLK_ADC_CLK_DIV_SHFT                                                  0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADDR(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_PHYS(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_OFFS                                                    (0x34)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_RMSK                                                           0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADC_FREEZE_CODE_BMSK                                           0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADC_FREEZE_CODE_SHFT                                             3
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADC_SIGNERR_POL_FLIP_BMSK                                      0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADC_SIGNERR_POL_FLIP_SHFT                                        2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADC_ENABLE_BMSK                                                0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADC_ENABLE_SHFT                                                  1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADC_CLK_ENABLE_BMSK                                            0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CTRL_ADC_CLK_ENABLE_SHFT                                              0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS0_ADDR(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS0_PHYS(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS0_OFFS                                        (0x38)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS0_RMSK                                              0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_BMSK                             0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_SHFT                                0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS1_ADDR(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS1_PHYS(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS1_OFFS                                        (0x3c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS1_RMSK                                             0x300
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_BMSK                            0x300
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_SHFT                                8

#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_ADDR(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_PHYS(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_OFFS                                             (0x40)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_RMSK                                                    0x7
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_RESCAL_ERR_BMSK                                         0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_RESCAL_ERR_SHFT                                           2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_RESETSM_BMSK                                            0x3
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESET_SM_STATUS_RESETSM_SHFT                                              0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_ADDR(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_PHYS(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_OFFS                                         (0x44)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_RMSK                                               0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_REFGEN_READY_BMSK                                  0x80
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_REFGEN_READY_SHFT                                     7
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_RESTRIM_CODE_BMSK                                  0x7f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_RESTRIM_CODE_STATUS_RESTRIM_CODE_SHFT                                     0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_ADDR(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_PHYS(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_OFFS                                                    (0x48)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_RMSK                                                           0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_SW_RESET_BMSK                                                  0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_SW_RESET_SW_RESET_SHFT                                                    0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS0_ADDR(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS0_PHYS(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS0_OFFS                                                  (0x4c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS0_RMSK                                                        0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS0_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS0_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS0_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS0_DEBUG_BUS_7_0_BMSK                                          0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS0_DEBUG_BUS_7_0_SHFT                                             0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS1_ADDR(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS1_PHYS(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS1_OFFS                                                  (0x50)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS1_RMSK                                                        0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS1_DEBUG_BUS_15_8_BMSK                                         0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS1_DEBUG_BUS_15_8_SHFT                                            0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_ADDR(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_PHYS(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_OFFS                                               (0x54)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_RMSK                                                      0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_DEBUG_BUS_SEL_BMSK                                        0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_BUS_SEL_DEBUG_BUS_SEL_SHFT                                          0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_ADDR(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_PHYS(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_OFFS                                                  (0x58)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_RMSK                                                         0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_FORCE_REFGEN_READY_BMSK                                      0x8
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_FORCE_REFGEN_READY_SHFT                                        3
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_BMSK                                   0x4
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_SHFT                                     2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_RESTRIM_DEBUG_MODE_BMSK                                      0x2
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_RESTRIM_DEBUG_MODE_SHFT                                        1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_DISABLE_CLOCK_GATING_BMSK                                    0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_DEBUG_CTRL_DISABLE_CLOCK_GATING_SHFT                                      0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_ADDR(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_PHYS(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_OFFS                                            (0x5c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_RMSK                                                  0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_REFGEN_CTRL1_BMSK                                     0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL1_REFGEN_CTRL1_SHFT                                        0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_ADDR(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_PHYS(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_OFFS                                            (0x60)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_RMSK                                                  0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_REFGEN_CTRL2_BMSK                                     0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CMN_REFGEN_CTRL2_REFGEN_CTRL2_SHFT                                        0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_ADDR(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_PHYS(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_OFFS                                                (0x64)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_RMSK                                                      0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_BMSK                                    0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_SHFT                                       0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_ADDR(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_PHYS(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_OFFS                                                (0x68)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_RMSK                                                      0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_BMSK                                   0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_SHFT                                      0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_ADDR(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_PHYS(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_OFFS                                                (0x6c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_RMSK                                                      0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_BMSK                                0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_SHFT                                   0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_ADDR(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_PHYS(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_OFFS                                                (0x70)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_RMSK                                                      0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_BMSK                               0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_SHFT                                  0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS1_ADDR(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS1_PHYS(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS1_OFFS                                              (0x74)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS1_RMSK                                                    0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_BMSK                                   0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_SHFT                                      0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS2_ADDR(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS2_PHYS(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS2_OFFS                                              (0x78)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS2_RMSK                                                    0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS2_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS2_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_BMSK                                  0x3f
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_SHFT                                     0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_ADDR(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_PHYS(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_OFFS                                                (0x7c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_RMSK                                                       0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_STATUS_WAIT_TIME_BMSK                                      0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_1_STATUS_TIMER_STATUS_WAIT_TIME_SHFT                                        0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_ADDR(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_PHYS(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_OFFS                                                (0x80)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_RMSK                                                       0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_PWRDWN_B_SW_BMSK                                           0xf
#define HWIO_AHB2PHY_0PHY_REFGEN_1_PWRDWN_CTRL5_PWRDWN_B_SW_SHFT                                             0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADDR(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_PHYS(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_OFFS                                          (0x84)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_RMSK                                                0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADC_DSM_MISC_BMSK                                   0xc0
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADC_DSM_MISC_SHFT                                      6
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADC_ATT_EN_BMSK                                     0x20
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADC_ATT_EN_SHFT                                        5
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADC_DTH_SET_BMSK                                    0x10
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADC_DTH_SET_SHFT                                       4
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADC_DTH_DAC_BMSK                                     0xe
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADC_DTH_DAC_SHFT                                       1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADC_DTH_EN_BMSK                                      0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_ADC_MODULATOR_CTRL_ADC_DTH_EN_SHFT                                        0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_ADDR(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_PHYS(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_OFFS                                    (0x88)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_RMSK                                          0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_ADDR(x),v)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_ADDR(x),m,v,HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_IN(x))
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_BMSK                        0x80
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_SHFT                           7
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_BMSK                              0x40
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_SHFT                                 6
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_BMSK                                0x20
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_SHFT                                   5
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_BMSK                       0x18
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_SHFT                          3
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_BMSK                 0x7
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_SHFT                   0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS0_PHYS(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS0_OFFS                                   (0x8c)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS0_RMSK                                         0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_BMSK                   0xff
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_SHFT                      0

#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS1_PHYS(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS1_OFFS                                   (0x90)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS1_RMSK                                       0xff00
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_BMSK                0xff00
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_SHFT                     8

#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS2_PHYS(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS2_OFFS                                   (0x94)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS2_RMSK                                     0xff0000
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS2_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_BMSK             0xff0000
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_SHFT                   16

#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS3_PHYS(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS3_OFFS                                   (0x98)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS3_RMSK                                          0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS3_RMSK)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), m)
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_BMSK                  0x1
#define HWIO_AHB2PHY_0PHY_REFGEN_1_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_SHFT                    0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_2PHY_REFGEN_2_PHY_REFGEN_2_CM_PHY_REFGEN
 *--------------------------------------------------------------------------*/

#define AHB2PHY_2PHY_REFGEN_2_PHY_REFGEN_2_CM_PHY_REFGEN_REG_BASE                                   (AHB2PHY_2AHB2PHY_2_BASE            + 0x00000000)
#define AHB2PHY_2PHY_REFGEN_2_PHY_REFGEN_2_CM_PHY_REFGEN_REG_BASE_SIZE                              0x9c
#define AHB2PHY_2PHY_REFGEN_2_PHY_REFGEN_2_CM_PHY_REFGEN_REG_BASE_USED                              0x98
#define AHB2PHY_2PHY_REFGEN_2_PHY_REFGEN_2_CM_PHY_REFGEN_REG_BASE_PHYS                              (AHB2PHY_2AHB2PHY_2_BASE_PHYS + 0x00000000)
#define AHB2PHY_2PHY_REFGEN_2_PHY_REFGEN_2_CM_PHY_REFGEN_REG_BASE_OFFS                              0x00000000

#define HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_ADDR(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_PHYS(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_OFFS                                                     (0x0)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_RMSK                                                           0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_ATB_SEL_7_0_BMSK                                               0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ATB_SEL_ATB_SEL_7_0_SHFT                                                  0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_ADDR(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_PHYS(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_OFFS                                                    (0x4)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_RMSK                                                           0x7
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_BG_WAIT_TIME_BMSK                                              0x7
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_TIMER_BG_WAIT_TIME_SHFT                                                0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_ADDR(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_PHYS(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_OFFS                                                     (0x8)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_RMSK                                                           0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_REFGEN_STATUS_MUX_BMSK                                         0x40
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_REFGEN_STATUS_MUX_SHFT                                            6
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_REFGEN_STATUS_BMSK                                             0x20
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_REFGEN_STATUS_SHFT                                                5
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_IE_EN_MUX_BMSK                                                 0x10
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_IE_EN_MUX_SHFT                                                    4
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_IE_EN_BMSK                                                      0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_IE_EN_SHFT                                                        3
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_PWRDN_B_BMSK                                                    0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_PWRDN_B_SHFT                                                      2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_BIAS_EN_MUX_BMSK                                                0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_BIAS_EN_MUX_SHFT                                                  1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_BIAS_EN_BMSK                                                    0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BIAS_EN_BIAS_EN_SHFT                                                      0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_ADDR(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_PHYS(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_OFFS                                           (0xc)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_RMSK                                                  0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_BMSK                                0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_SHFT                                  3
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_IE_EN_OUT_BMSK                                        0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_IE_EN_OUT_SHFT                                          2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_BG_EN_OUT_BMSK                                        0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_BG_EN_OUT_SHFT                                          1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_BIAS_EN_OUT_BMSK                                      0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_STATUS_BIAS_EN_OUT_SHFT                                        0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_ADDR(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_PHYS(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_OFFS                                                    (0x10)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_BGT_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGT_TRIM_BGT_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_ADDR(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_PHYS(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_OFFS                                                    (0x14)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_BGV_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BGV_TRIM_BGV_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_ADDR(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_PHYS(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_OFFS                                                     (0x18)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_RMSK                                                           0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_BG_EN_SYNC_MUX_BMSK                                            0x20
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_BG_EN_SYNC_MUX_SHFT                                               5
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_BG_EN_SYNC_BMSK                                                0x10
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_BG_EN_SYNC_SHFT                                                   4
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_EFUSE_BYPASS_BMSK                                               0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_EFUSE_BYPASS_SHFT                                                 3
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_BANDGAP_EN_MUX_BMSK                                             0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_BANDGAP_EN_MUX_SHFT                                               2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_BANDGAP_EN_BMSK                                                 0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_BANDGAP_EN_SHFT                                                   1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_BANDGAP_BYPASS_BMSK                                             0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_BG_CTRL_BANDGAP_BYPASS_SHFT                                               0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_ADDR(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_PHYS(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_OFFS                                                   (0x1c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_RMSK                                                          0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_BYPASS_RSM_RESTRIM_BMSK                                       0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_BYPASS_RSM_RESTRIM_SHFT                                         3
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_BYPASS_RSM_BANDGAP_BMSK                                       0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_BYPASS_RSM_BANDGAP_SHFT                                         2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_RSM_START_MUX_BMSK                                            0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_RSM_START_MUX_SHFT                                              1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_RSM_START_BMSK                                                0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RSM_CNTRL_RSM_START_SHFT                                                  0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_ADDR(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_PHYS(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_OFFS                                           (0x20)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_RMSK                                                 0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_BMSK                               0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_SHFT                                  0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_ADDR(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_PHYS(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_OFFS                                         (0x24)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_RMSK                                               0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_BMSK                       0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_SHFT                          0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_ADDR(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_PHYS(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_OFFS                                            (0x28)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_RMSK                                                   0x3
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_RESTRIM_EN_MUX_BMSK                                    0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_RESTRIM_EN_MUX_SHFT                                      1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_RESTRIM_EN_BMSK                                        0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RES_TRIM_CONTROL_RESTRIM_EN_SHFT                                          0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_ADDR(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_PHYS(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_OFFS                                                     (0x2c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_RMSK                                                           0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_ADC_FROM_ATB_BMSK                                              0x40
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_ADC_FROM_ATB_SHFT                                                 6
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_ADC_ATB_MUXSEL_BMSK                                            0x20
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_ADC_ATB_MUXSEL_SHFT                                               5
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_DIGITAL_ECO_BKUP_BMSK                                          0x1e
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_DIGITAL_ECO_BKUP_SHFT                                             1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_ADC_EN_BMSK                                                     0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_SEL_ADC_EN_SHFT                                                       0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_ADDR(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_PHYS(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_OFFS                                                     (0x30)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_RMSK                                                           0x1f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_ADC_CLK_DIV_BMSK                                               0x1f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CLK_ADC_CLK_DIV_SHFT                                                  0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADDR(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_PHYS(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_OFFS                                                    (0x34)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_RMSK                                                           0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADC_FREEZE_CODE_BMSK                                           0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADC_FREEZE_CODE_SHFT                                             3
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADC_SIGNERR_POL_FLIP_BMSK                                      0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADC_SIGNERR_POL_FLIP_SHFT                                        2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADC_ENABLE_BMSK                                                0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADC_ENABLE_SHFT                                                  1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADC_CLK_ENABLE_BMSK                                            0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CTRL_ADC_CLK_ENABLE_SHFT                                              0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS0_ADDR(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS0_PHYS(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS0_OFFS                                        (0x38)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS0_RMSK                                              0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_BMSK                             0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_SHFT                                0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS1_ADDR(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS1_PHYS(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS1_OFFS                                        (0x3c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS1_RMSK                                             0x300
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_BMSK                            0x300
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_SHFT                                8

#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_ADDR(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_PHYS(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_OFFS                                             (0x40)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_RMSK                                                    0x7
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_RESCAL_ERR_BMSK                                         0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_RESCAL_ERR_SHFT                                           2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_RESETSM_BMSK                                            0x3
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESET_SM_STATUS_RESETSM_SHFT                                              0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_ADDR(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_PHYS(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_OFFS                                         (0x44)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_RMSK                                               0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_REFGEN_READY_BMSK                                  0x80
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_REFGEN_READY_SHFT                                     7
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_RESTRIM_CODE_BMSK                                  0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_RESTRIM_CODE_STATUS_RESTRIM_CODE_SHFT                                     0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_ADDR(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_PHYS(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_OFFS                                                    (0x48)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_RMSK                                                           0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_SW_RESET_BMSK                                                  0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_SW_RESET_SW_RESET_SHFT                                                    0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS0_ADDR(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS0_PHYS(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS0_OFFS                                                  (0x4c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS0_RMSK                                                        0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS0_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS0_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS0_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS0_DEBUG_BUS_7_0_BMSK                                          0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS0_DEBUG_BUS_7_0_SHFT                                             0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS1_ADDR(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS1_PHYS(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS1_OFFS                                                  (0x50)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS1_RMSK                                                        0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS1_DEBUG_BUS_15_8_BMSK                                         0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS1_DEBUG_BUS_15_8_SHFT                                            0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_ADDR(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_PHYS(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_OFFS                                               (0x54)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_RMSK                                                      0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_DEBUG_BUS_SEL_BMSK                                        0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_BUS_SEL_DEBUG_BUS_SEL_SHFT                                          0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_ADDR(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_PHYS(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_OFFS                                                  (0x58)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_RMSK                                                         0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_FORCE_REFGEN_READY_BMSK                                      0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_FORCE_REFGEN_READY_SHFT                                        3
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_BMSK                                   0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_SHFT                                     2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_RESTRIM_DEBUG_MODE_BMSK                                      0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_RESTRIM_DEBUG_MODE_SHFT                                        1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_DISABLE_CLOCK_GATING_BMSK                                    0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_DEBUG_CTRL_DISABLE_CLOCK_GATING_SHFT                                      0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_ADDR(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_PHYS(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_OFFS                                            (0x5c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_RMSK                                                  0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_REFGEN_CTRL1_BMSK                                     0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL1_REFGEN_CTRL1_SHFT                                        0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_ADDR(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_PHYS(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_OFFS                                            (0x60)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_RMSK                                                  0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_REFGEN_CTRL2_BMSK                                     0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CMN_REFGEN_CTRL2_REFGEN_CTRL2_SHFT                                        0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_ADDR(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_PHYS(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_OFFS                                                (0x64)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_RMSK                                                      0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_BMSK                                    0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_SHFT                                       0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_ADDR(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_PHYS(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_OFFS                                                (0x68)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_RMSK                                                      0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_BMSK                                   0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_SHFT                                      0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_ADDR(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_PHYS(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_OFFS                                                (0x6c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_RMSK                                                      0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_BMSK                                0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_SHFT                                   0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_ADDR(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_PHYS(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_OFFS                                                (0x70)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_RMSK                                                      0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_BMSK                               0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_SHFT                                  0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS1_ADDR(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS1_PHYS(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS1_OFFS                                              (0x74)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS1_RMSK                                                    0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_BMSK                                   0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_SHFT                                      0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS2_ADDR(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS2_PHYS(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS2_OFFS                                              (0x78)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS2_RMSK                                                    0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS2_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS2_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_BMSK                                  0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_SHFT                                     0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_ADDR(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_PHYS(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_OFFS                                                (0x7c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_RMSK                                                       0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_STATUS_WAIT_TIME_BMSK                                      0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_2_STATUS_TIMER_STATUS_WAIT_TIME_SHFT                                        0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_ADDR(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_PHYS(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_OFFS                                                (0x80)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_RMSK                                                       0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_PWRDWN_B_SW_BMSK                                           0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_2_PWRDWN_CTRL5_PWRDWN_B_SW_SHFT                                             0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADDR(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_PHYS(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_OFFS                                          (0x84)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_RMSK                                                0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADC_DSM_MISC_BMSK                                   0xc0
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADC_DSM_MISC_SHFT                                      6
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADC_ATT_EN_BMSK                                     0x20
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADC_ATT_EN_SHFT                                        5
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADC_DTH_SET_BMSK                                    0x10
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADC_DTH_SET_SHFT                                       4
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADC_DTH_DAC_BMSK                                     0xe
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADC_DTH_DAC_SHFT                                       1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADC_DTH_EN_BMSK                                      0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_ADC_MODULATOR_CTRL_ADC_DTH_EN_SHFT                                        0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_ADDR(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_PHYS(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_OFFS                                    (0x88)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_RMSK                                          0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_BMSK                        0x80
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_SHFT                           7
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_BMSK                              0x40
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_SHFT                                 6
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_BMSK                                0x20
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_SHFT                                   5
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_BMSK                       0x18
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_SHFT                          3
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_BMSK                 0x7
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_SHFT                   0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS0_PHYS(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS0_OFFS                                   (0x8c)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS0_RMSK                                         0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_BMSK                   0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_SHFT                      0

#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS1_PHYS(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS1_OFFS                                   (0x90)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS1_RMSK                                       0xff00
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_BMSK                0xff00
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_SHFT                     8

#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS2_PHYS(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS2_OFFS                                   (0x94)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS2_RMSK                                     0xff0000
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS2_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_BMSK             0xff0000
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_SHFT                   16

#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS3_PHYS(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS3_OFFS                                   (0x98)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS3_RMSK                                          0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS3_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_BMSK                  0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_2_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_SHFT                    0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_2PHY_REFGEN_3_PHY_REFGEN_3_CM_PHY_REFGEN
 *--------------------------------------------------------------------------*/

#define AHB2PHY_2PHY_REFGEN_3_PHY_REFGEN_3_CM_PHY_REFGEN_REG_BASE                                   (AHB2PHY_2AHB2PHY_2_BASE            + 0x00001000)
#define AHB2PHY_2PHY_REFGEN_3_PHY_REFGEN_3_CM_PHY_REFGEN_REG_BASE_SIZE                              0x9c
#define AHB2PHY_2PHY_REFGEN_3_PHY_REFGEN_3_CM_PHY_REFGEN_REG_BASE_USED                              0x98
#define AHB2PHY_2PHY_REFGEN_3_PHY_REFGEN_3_CM_PHY_REFGEN_REG_BASE_PHYS                              (AHB2PHY_2AHB2PHY_2_BASE_PHYS + 0x00001000)
#define AHB2PHY_2PHY_REFGEN_3_PHY_REFGEN_3_CM_PHY_REFGEN_REG_BASE_OFFS                              0x00001000

#define HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_ADDR(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_PHYS(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_OFFS                                                     (0x0)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_RMSK                                                           0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_ATB_SEL_7_0_BMSK                                               0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ATB_SEL_ATB_SEL_7_0_SHFT                                                  0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_ADDR(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_PHYS(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_OFFS                                                    (0x4)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_RMSK                                                           0x7
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_BG_WAIT_TIME_BMSK                                              0x7
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_TIMER_BG_WAIT_TIME_SHFT                                                0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_ADDR(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_PHYS(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_OFFS                                                     (0x8)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_RMSK                                                           0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_REFGEN_STATUS_MUX_BMSK                                         0x40
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_REFGEN_STATUS_MUX_SHFT                                            6
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_REFGEN_STATUS_BMSK                                             0x20
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_REFGEN_STATUS_SHFT                                                5
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_IE_EN_MUX_BMSK                                                 0x10
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_IE_EN_MUX_SHFT                                                    4
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_IE_EN_BMSK                                                      0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_IE_EN_SHFT                                                        3
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_PWRDN_B_BMSK                                                    0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_PWRDN_B_SHFT                                                      2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_BIAS_EN_MUX_BMSK                                                0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_BIAS_EN_MUX_SHFT                                                  1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_BIAS_EN_BMSK                                                    0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BIAS_EN_BIAS_EN_SHFT                                                      0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_ADDR(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_PHYS(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_OFFS                                           (0xc)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_RMSK                                                  0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_BMSK                                0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_SHFT                                  3
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_IE_EN_OUT_BMSK                                        0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_IE_EN_OUT_SHFT                                          2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_BG_EN_OUT_BMSK                                        0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_BG_EN_OUT_SHFT                                          1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_BIAS_EN_OUT_BMSK                                      0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_STATUS_BIAS_EN_OUT_SHFT                                        0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_ADDR(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_PHYS(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_OFFS                                                    (0x10)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_BGT_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGT_TRIM_BGT_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_ADDR(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_PHYS(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_OFFS                                                    (0x14)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_BGV_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BGV_TRIM_BGV_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_ADDR(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_PHYS(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_OFFS                                                     (0x18)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_RMSK                                                           0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_BG_EN_SYNC_MUX_BMSK                                            0x20
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_BG_EN_SYNC_MUX_SHFT                                               5
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_BG_EN_SYNC_BMSK                                                0x10
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_BG_EN_SYNC_SHFT                                                   4
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_EFUSE_BYPASS_BMSK                                               0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_EFUSE_BYPASS_SHFT                                                 3
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_BANDGAP_EN_MUX_BMSK                                             0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_BANDGAP_EN_MUX_SHFT                                               2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_BANDGAP_EN_BMSK                                                 0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_BANDGAP_EN_SHFT                                                   1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_BANDGAP_BYPASS_BMSK                                             0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_BG_CTRL_BANDGAP_BYPASS_SHFT                                               0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_ADDR(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_PHYS(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_OFFS                                                   (0x1c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_RMSK                                                          0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_BYPASS_RSM_RESTRIM_BMSK                                       0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_BYPASS_RSM_RESTRIM_SHFT                                         3
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_BYPASS_RSM_BANDGAP_BMSK                                       0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_BYPASS_RSM_BANDGAP_SHFT                                         2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_RSM_START_MUX_BMSK                                            0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_RSM_START_MUX_SHFT                                              1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_RSM_START_BMSK                                                0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RSM_CNTRL_RSM_START_SHFT                                                  0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_ADDR(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_PHYS(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_OFFS                                           (0x20)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_RMSK                                                 0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_BMSK                               0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_SHFT                                  0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_ADDR(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_PHYS(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_OFFS                                         (0x24)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_RMSK                                               0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_BMSK                       0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_SHFT                          0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_ADDR(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_PHYS(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_OFFS                                            (0x28)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_RMSK                                                   0x3
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_RESTRIM_EN_MUX_BMSK                                    0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_RESTRIM_EN_MUX_SHFT                                      1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_RESTRIM_EN_BMSK                                        0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RES_TRIM_CONTROL_RESTRIM_EN_SHFT                                          0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_ADDR(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_PHYS(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_OFFS                                                     (0x2c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_RMSK                                                           0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_ADC_FROM_ATB_BMSK                                              0x40
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_ADC_FROM_ATB_SHFT                                                 6
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_ADC_ATB_MUXSEL_BMSK                                            0x20
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_ADC_ATB_MUXSEL_SHFT                                               5
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_DIGITAL_ECO_BKUP_BMSK                                          0x1e
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_DIGITAL_ECO_BKUP_SHFT                                             1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_ADC_EN_BMSK                                                     0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_SEL_ADC_EN_SHFT                                                       0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_ADDR(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_PHYS(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_OFFS                                                     (0x30)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_RMSK                                                           0x1f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_ADC_CLK_DIV_BMSK                                               0x1f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CLK_ADC_CLK_DIV_SHFT                                                  0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADDR(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_PHYS(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_OFFS                                                    (0x34)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_RMSK                                                           0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADC_FREEZE_CODE_BMSK                                           0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADC_FREEZE_CODE_SHFT                                             3
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADC_SIGNERR_POL_FLIP_BMSK                                      0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADC_SIGNERR_POL_FLIP_SHFT                                        2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADC_ENABLE_BMSK                                                0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADC_ENABLE_SHFT                                                  1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADC_CLK_ENABLE_BMSK                                            0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CTRL_ADC_CLK_ENABLE_SHFT                                              0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS0_ADDR(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS0_PHYS(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS0_OFFS                                        (0x38)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS0_RMSK                                              0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_BMSK                             0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_SHFT                                0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS1_ADDR(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS1_PHYS(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS1_OFFS                                        (0x3c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS1_RMSK                                             0x300
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_BMSK                            0x300
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_SHFT                                8

#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_ADDR(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_PHYS(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_OFFS                                             (0x40)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_RMSK                                                    0x7
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_RESCAL_ERR_BMSK                                         0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_RESCAL_ERR_SHFT                                           2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_RESETSM_BMSK                                            0x3
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESET_SM_STATUS_RESETSM_SHFT                                              0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_ADDR(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_PHYS(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_OFFS                                         (0x44)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_RMSK                                               0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_REFGEN_READY_BMSK                                  0x80
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_REFGEN_READY_SHFT                                     7
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_RESTRIM_CODE_BMSK                                  0x7f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_RESTRIM_CODE_STATUS_RESTRIM_CODE_SHFT                                     0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_ADDR(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_PHYS(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_OFFS                                                    (0x48)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_RMSK                                                           0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_SW_RESET_BMSK                                                  0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_SW_RESET_SW_RESET_SHFT                                                    0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS0_ADDR(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS0_PHYS(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS0_OFFS                                                  (0x4c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS0_RMSK                                                        0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS0_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS0_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS0_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS0_DEBUG_BUS_7_0_BMSK                                          0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS0_DEBUG_BUS_7_0_SHFT                                             0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS1_ADDR(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS1_PHYS(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS1_OFFS                                                  (0x50)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS1_RMSK                                                        0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS1_DEBUG_BUS_15_8_BMSK                                         0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS1_DEBUG_BUS_15_8_SHFT                                            0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_ADDR(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_PHYS(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_OFFS                                               (0x54)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_RMSK                                                      0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_DEBUG_BUS_SEL_BMSK                                        0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_BUS_SEL_DEBUG_BUS_SEL_SHFT                                          0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_ADDR(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_PHYS(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_OFFS                                                  (0x58)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_RMSK                                                         0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_FORCE_REFGEN_READY_BMSK                                      0x8
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_FORCE_REFGEN_READY_SHFT                                        3
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_BMSK                                   0x4
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_SHFT                                     2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_RESTRIM_DEBUG_MODE_BMSK                                      0x2
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_RESTRIM_DEBUG_MODE_SHFT                                        1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_DISABLE_CLOCK_GATING_BMSK                                    0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_DEBUG_CTRL_DISABLE_CLOCK_GATING_SHFT                                      0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_ADDR(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_PHYS(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_OFFS                                            (0x5c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_RMSK                                                  0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_REFGEN_CTRL1_BMSK                                     0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL1_REFGEN_CTRL1_SHFT                                        0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_ADDR(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_PHYS(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_OFFS                                            (0x60)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_RMSK                                                  0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_REFGEN_CTRL2_BMSK                                     0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CMN_REFGEN_CTRL2_REFGEN_CTRL2_SHFT                                        0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_ADDR(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_PHYS(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_OFFS                                                (0x64)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_RMSK                                                      0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_BMSK                                    0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_SHFT                                       0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_ADDR(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_PHYS(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_OFFS                                                (0x68)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_RMSK                                                      0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_BMSK                                   0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_SHFT                                      0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_ADDR(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_PHYS(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_OFFS                                                (0x6c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_RMSK                                                      0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_BMSK                                0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_SHFT                                   0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_ADDR(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_PHYS(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_OFFS                                                (0x70)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_RMSK                                                      0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_BMSK                               0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_SHFT                                  0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS1_ADDR(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS1_PHYS(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS1_OFFS                                              (0x74)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS1_RMSK                                                    0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_BMSK                                   0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_SHFT                                      0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS2_ADDR(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS2_PHYS(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS2_OFFS                                              (0x78)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS2_RMSK                                                    0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS2_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS2_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_BMSK                                  0x3f
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_SHFT                                     0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_ADDR(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_PHYS(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_OFFS                                                (0x7c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_RMSK                                                       0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_STATUS_WAIT_TIME_BMSK                                      0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_3_STATUS_TIMER_STATUS_WAIT_TIME_SHFT                                        0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_ADDR(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_PHYS(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_OFFS                                                (0x80)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_RMSK                                                       0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_PWRDWN_B_SW_BMSK                                           0xf
#define HWIO_AHB2PHY_2PHY_REFGEN_3_PWRDWN_CTRL5_PWRDWN_B_SW_SHFT                                             0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADDR(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_PHYS(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_OFFS                                          (0x84)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_RMSK                                                0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADC_DSM_MISC_BMSK                                   0xc0
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADC_DSM_MISC_SHFT                                      6
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADC_ATT_EN_BMSK                                     0x20
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADC_ATT_EN_SHFT                                        5
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADC_DTH_SET_BMSK                                    0x10
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADC_DTH_SET_SHFT                                       4
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADC_DTH_DAC_BMSK                                     0xe
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADC_DTH_DAC_SHFT                                       1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADC_DTH_EN_BMSK                                      0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_ADC_MODULATOR_CTRL_ADC_DTH_EN_SHFT                                        0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_ADDR(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_PHYS(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_OFFS                                    (0x88)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_RMSK                                          0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_ADDR(x),v)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_ADDR(x),m,v,HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_IN(x))
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_BMSK                        0x80
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_SHFT                           7
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_BMSK                              0x40
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_SHFT                                 6
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_BMSK                                0x20
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_SHFT                                   5
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_BMSK                       0x18
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_SHFT                          3
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_BMSK                 0x7
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_SHFT                   0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS0_PHYS(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS0_OFFS                                   (0x8c)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS0_RMSK                                         0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_BMSK                   0xff
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_SHFT                      0

#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS1_PHYS(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS1_OFFS                                   (0x90)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS1_RMSK                                       0xff00
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_BMSK                0xff00
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_SHFT                     8

#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS2_PHYS(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS2_OFFS                                   (0x94)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS2_RMSK                                     0xff0000
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS2_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_BMSK             0xff0000
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_SHFT                   16

#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS3_PHYS(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS3_OFFS                                   (0x98)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS3_RMSK                                          0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS3_RMSK)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), m)
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_BMSK                  0x1
#define HWIO_AHB2PHY_2PHY_REFGEN_3_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_SHFT                    0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_1PHY_REFGEN_4_PHY_REFGEN_4_CM_PHY_REFGEN
 *--------------------------------------------------------------------------*/

#define AHB2PHY_1PHY_REFGEN_4_PHY_REFGEN_4_CM_PHY_REFGEN_REG_BASE                                   (AHB2PHY_1AHB2PHY_1_BASE            + 0x00000000)
#define AHB2PHY_1PHY_REFGEN_4_PHY_REFGEN_4_CM_PHY_REFGEN_REG_BASE_SIZE                              0x9c
#define AHB2PHY_1PHY_REFGEN_4_PHY_REFGEN_4_CM_PHY_REFGEN_REG_BASE_USED                              0x98
#define AHB2PHY_1PHY_REFGEN_4_PHY_REFGEN_4_CM_PHY_REFGEN_REG_BASE_PHYS                              (AHB2PHY_1AHB2PHY_1_BASE_PHYS + 0x00000000)
#define AHB2PHY_1PHY_REFGEN_4_PHY_REFGEN_4_CM_PHY_REFGEN_REG_BASE_OFFS                              0x00000000

#define HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_ADDR(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_PHYS(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_OFFS                                                     (0x0)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_RMSK                                                           0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_ATB_SEL_7_0_BMSK                                               0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ATB_SEL_ATB_SEL_7_0_SHFT                                                  0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_ADDR(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_PHYS(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_OFFS                                                    (0x4)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_RMSK                                                           0x7
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_BG_WAIT_TIME_BMSK                                              0x7
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_TIMER_BG_WAIT_TIME_SHFT                                                0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_ADDR(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_PHYS(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_OFFS                                                     (0x8)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_RMSK                                                           0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_REFGEN_STATUS_MUX_BMSK                                         0x40
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_REFGEN_STATUS_MUX_SHFT                                            6
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_REFGEN_STATUS_BMSK                                             0x20
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_REFGEN_STATUS_SHFT                                                5
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_IE_EN_MUX_BMSK                                                 0x10
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_IE_EN_MUX_SHFT                                                    4
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_IE_EN_BMSK                                                      0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_IE_EN_SHFT                                                        3
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_PWRDN_B_BMSK                                                    0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_PWRDN_B_SHFT                                                      2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_BIAS_EN_MUX_BMSK                                                0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_BIAS_EN_MUX_SHFT                                                  1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_BIAS_EN_BMSK                                                    0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BIAS_EN_BIAS_EN_SHFT                                                      0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_ADDR(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_PHYS(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_OFFS                                           (0xc)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_RMSK                                                  0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_BMSK                                0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_SHFT                                  3
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_IE_EN_OUT_BMSK                                        0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_IE_EN_OUT_SHFT                                          2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_BG_EN_OUT_BMSK                                        0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_BG_EN_OUT_SHFT                                          1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_BIAS_EN_OUT_BMSK                                      0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_STATUS_BIAS_EN_OUT_SHFT                                        0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_ADDR(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_PHYS(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_OFFS                                                    (0x10)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_BGT_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGT_TRIM_BGT_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_ADDR(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_PHYS(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_OFFS                                                    (0x14)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_BGV_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BGV_TRIM_BGV_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_ADDR(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_PHYS(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_OFFS                                                     (0x18)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_RMSK                                                           0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_BG_EN_SYNC_MUX_BMSK                                            0x20
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_BG_EN_SYNC_MUX_SHFT                                               5
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_BG_EN_SYNC_BMSK                                                0x10
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_BG_EN_SYNC_SHFT                                                   4
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_EFUSE_BYPASS_BMSK                                               0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_EFUSE_BYPASS_SHFT                                                 3
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_BANDGAP_EN_MUX_BMSK                                             0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_BANDGAP_EN_MUX_SHFT                                               2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_BANDGAP_EN_BMSK                                                 0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_BANDGAP_EN_SHFT                                                   1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_BANDGAP_BYPASS_BMSK                                             0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_BG_CTRL_BANDGAP_BYPASS_SHFT                                               0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_ADDR(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_PHYS(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_OFFS                                                   (0x1c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_RMSK                                                          0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_BYPASS_RSM_RESTRIM_BMSK                                       0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_BYPASS_RSM_RESTRIM_SHFT                                         3
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_BYPASS_RSM_BANDGAP_BMSK                                       0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_BYPASS_RSM_BANDGAP_SHFT                                         2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_RSM_START_MUX_BMSK                                            0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_RSM_START_MUX_SHFT                                              1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_RSM_START_BMSK                                                0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RSM_CNTRL_RSM_START_SHFT                                                  0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_ADDR(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_PHYS(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_OFFS                                           (0x20)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_RMSK                                                 0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_BMSK                               0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_SHFT                                  0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_ADDR(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_PHYS(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_OFFS                                         (0x24)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_RMSK                                               0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_BMSK                       0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_SHFT                          0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_ADDR(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_PHYS(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_OFFS                                            (0x28)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_RMSK                                                   0x3
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_RESTRIM_EN_MUX_BMSK                                    0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_RESTRIM_EN_MUX_SHFT                                      1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_RESTRIM_EN_BMSK                                        0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RES_TRIM_CONTROL_RESTRIM_EN_SHFT                                          0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_ADDR(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_PHYS(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_OFFS                                                     (0x2c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_RMSK                                                           0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_ADC_FROM_ATB_BMSK                                              0x40
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_ADC_FROM_ATB_SHFT                                                 6
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_ADC_ATB_MUXSEL_BMSK                                            0x20
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_ADC_ATB_MUXSEL_SHFT                                               5
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_DIGITAL_ECO_BKUP_BMSK                                          0x1e
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_DIGITAL_ECO_BKUP_SHFT                                             1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_ADC_EN_BMSK                                                     0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_SEL_ADC_EN_SHFT                                                       0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_ADDR(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_PHYS(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_OFFS                                                     (0x30)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_RMSK                                                           0x1f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_ADC_CLK_DIV_BMSK                                               0x1f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CLK_ADC_CLK_DIV_SHFT                                                  0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADDR(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_PHYS(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_OFFS                                                    (0x34)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_RMSK                                                           0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADC_FREEZE_CODE_BMSK                                           0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADC_FREEZE_CODE_SHFT                                             3
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADC_SIGNERR_POL_FLIP_BMSK                                      0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADC_SIGNERR_POL_FLIP_SHFT                                        2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADC_ENABLE_BMSK                                                0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADC_ENABLE_SHFT                                                  1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADC_CLK_ENABLE_BMSK                                            0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CTRL_ADC_CLK_ENABLE_SHFT                                              0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS0_ADDR(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS0_PHYS(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS0_OFFS                                        (0x38)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS0_RMSK                                              0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_BMSK                             0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_SHFT                                0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS1_ADDR(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS1_PHYS(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS1_OFFS                                        (0x3c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS1_RMSK                                             0x300
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_BMSK                            0x300
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_SHFT                                8

#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_ADDR(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_PHYS(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_OFFS                                             (0x40)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_RMSK                                                    0x7
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_RESCAL_ERR_BMSK                                         0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_RESCAL_ERR_SHFT                                           2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_RESETSM_BMSK                                            0x3
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESET_SM_STATUS_RESETSM_SHFT                                              0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_ADDR(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_PHYS(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_OFFS                                         (0x44)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_RMSK                                               0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_REFGEN_READY_BMSK                                  0x80
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_REFGEN_READY_SHFT                                     7
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_RESTRIM_CODE_BMSK                                  0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_RESTRIM_CODE_STATUS_RESTRIM_CODE_SHFT                                     0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_ADDR(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_PHYS(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_OFFS                                                    (0x48)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_RMSK                                                           0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_SW_RESET_BMSK                                                  0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_SW_RESET_SW_RESET_SHFT                                                    0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS0_ADDR(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS0_PHYS(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS0_OFFS                                                  (0x4c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS0_RMSK                                                        0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS0_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS0_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS0_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS0_DEBUG_BUS_7_0_BMSK                                          0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS0_DEBUG_BUS_7_0_SHFT                                             0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS1_ADDR(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS1_PHYS(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS1_OFFS                                                  (0x50)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS1_RMSK                                                        0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS1_DEBUG_BUS_15_8_BMSK                                         0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS1_DEBUG_BUS_15_8_SHFT                                            0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_ADDR(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_PHYS(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_OFFS                                               (0x54)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_RMSK                                                      0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_DEBUG_BUS_SEL_BMSK                                        0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_BUS_SEL_DEBUG_BUS_SEL_SHFT                                          0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_ADDR(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_PHYS(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_OFFS                                                  (0x58)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_RMSK                                                         0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_FORCE_REFGEN_READY_BMSK                                      0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_FORCE_REFGEN_READY_SHFT                                        3
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_BMSK                                   0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_SHFT                                     2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_RESTRIM_DEBUG_MODE_BMSK                                      0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_RESTRIM_DEBUG_MODE_SHFT                                        1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_DISABLE_CLOCK_GATING_BMSK                                    0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_DEBUG_CTRL_DISABLE_CLOCK_GATING_SHFT                                      0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_ADDR(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_PHYS(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_OFFS                                            (0x5c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_RMSK                                                  0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_REFGEN_CTRL1_BMSK                                     0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL1_REFGEN_CTRL1_SHFT                                        0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_ADDR(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_PHYS(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_OFFS                                            (0x60)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_RMSK                                                  0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_REFGEN_CTRL2_BMSK                                     0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CMN_REFGEN_CTRL2_REFGEN_CTRL2_SHFT                                        0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_ADDR(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_PHYS(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_OFFS                                                (0x64)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_RMSK                                                      0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_BMSK                                    0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_SHFT                                       0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_ADDR(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_PHYS(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_OFFS                                                (0x68)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_RMSK                                                      0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_BMSK                                   0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_SHFT                                      0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_ADDR(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_PHYS(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_OFFS                                                (0x6c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_RMSK                                                      0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_BMSK                                0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_SHFT                                   0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_ADDR(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_PHYS(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_OFFS                                                (0x70)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_RMSK                                                      0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_BMSK                               0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_SHFT                                  0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS1_ADDR(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS1_PHYS(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS1_OFFS                                              (0x74)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS1_RMSK                                                    0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_BMSK                                   0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_SHFT                                      0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS2_ADDR(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS2_PHYS(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS2_OFFS                                              (0x78)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS2_RMSK                                                    0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS2_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS2_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_BMSK                                  0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_SHFT                                     0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_ADDR(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_PHYS(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_OFFS                                                (0x7c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_RMSK                                                       0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_STATUS_WAIT_TIME_BMSK                                      0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_4_STATUS_TIMER_STATUS_WAIT_TIME_SHFT                                        0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_ADDR(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_PHYS(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_OFFS                                                (0x80)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_RMSK                                                       0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_PWRDWN_B_SW_BMSK                                           0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_4_PWRDWN_CTRL5_PWRDWN_B_SW_SHFT                                             0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADDR(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_PHYS(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_OFFS                                          (0x84)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_RMSK                                                0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADC_DSM_MISC_BMSK                                   0xc0
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADC_DSM_MISC_SHFT                                      6
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADC_ATT_EN_BMSK                                     0x20
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADC_ATT_EN_SHFT                                        5
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADC_DTH_SET_BMSK                                    0x10
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADC_DTH_SET_SHFT                                       4
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADC_DTH_DAC_BMSK                                     0xe
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADC_DTH_DAC_SHFT                                       1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADC_DTH_EN_BMSK                                      0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_ADC_MODULATOR_CTRL_ADC_DTH_EN_SHFT                                        0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_ADDR(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_PHYS(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_OFFS                                    (0x88)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_RMSK                                          0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_BMSK                        0x80
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_SHFT                           7
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_BMSK                              0x40
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_SHFT                                 6
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_BMSK                                0x20
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_SHFT                                   5
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_BMSK                       0x18
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_SHFT                          3
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_BMSK                 0x7
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_SHFT                   0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS0_PHYS(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS0_OFFS                                   (0x8c)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS0_RMSK                                         0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_BMSK                   0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_SHFT                      0

#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS1_PHYS(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS1_OFFS                                   (0x90)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS1_RMSK                                       0xff00
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_BMSK                0xff00
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_SHFT                     8

#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS2_PHYS(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS2_OFFS                                   (0x94)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS2_RMSK                                     0xff0000
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS2_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_BMSK             0xff0000
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_SHFT                   16

#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS3_PHYS(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS3_OFFS                                   (0x98)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS3_RMSK                                          0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS3_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_BMSK                  0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_4_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_SHFT                    0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_1PHY_REFGEN_5_PHY_REFGEN_5_CM_PHY_REFGEN
 *--------------------------------------------------------------------------*/

#define AHB2PHY_1PHY_REFGEN_5_PHY_REFGEN_5_CM_PHY_REFGEN_REG_BASE                                   (AHB2PHY_1AHB2PHY_1_BASE            + 0x00001000)
#define AHB2PHY_1PHY_REFGEN_5_PHY_REFGEN_5_CM_PHY_REFGEN_REG_BASE_SIZE                              0x9c
#define AHB2PHY_1PHY_REFGEN_5_PHY_REFGEN_5_CM_PHY_REFGEN_REG_BASE_USED                              0x98
#define AHB2PHY_1PHY_REFGEN_5_PHY_REFGEN_5_CM_PHY_REFGEN_REG_BASE_PHYS                              (AHB2PHY_1AHB2PHY_1_BASE_PHYS + 0x00001000)
#define AHB2PHY_1PHY_REFGEN_5_PHY_REFGEN_5_CM_PHY_REFGEN_REG_BASE_OFFS                              0x00001000

#define HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_ADDR(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_PHYS(x)                                                  ((x) + 0x0)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_OFFS                                                     (0x0)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_RMSK                                                           0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_ATB_SEL_7_0_BMSK                                               0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ATB_SEL_ATB_SEL_7_0_SHFT                                                  0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_ADDR(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_PHYS(x)                                                 ((x) + 0x4)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_OFFS                                                    (0x4)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_RMSK                                                           0x7
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_BG_WAIT_TIME_BMSK                                              0x7
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_TIMER_BG_WAIT_TIME_SHFT                                                0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_ADDR(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_PHYS(x)                                                  ((x) + 0x8)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_OFFS                                                     (0x8)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_RMSK                                                           0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_REFGEN_STATUS_MUX_BMSK                                         0x40
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_REFGEN_STATUS_MUX_SHFT                                            6
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_REFGEN_STATUS_BMSK                                             0x20
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_REFGEN_STATUS_SHFT                                                5
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_IE_EN_MUX_BMSK                                                 0x10
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_IE_EN_MUX_SHFT                                                    4
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_IE_EN_BMSK                                                      0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_IE_EN_SHFT                                                        3
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_PWRDN_B_BMSK                                                    0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_PWRDN_B_SHFT                                                      2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_BIAS_EN_MUX_BMSK                                                0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_BIAS_EN_MUX_SHFT                                                  1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_BIAS_EN_BMSK                                                    0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BIAS_EN_BIAS_EN_SHFT                                                      0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_ADDR(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_PHYS(x)                                        ((x) + 0xc)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_OFFS                                           (0xc)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_RMSK                                                  0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_BMSK                                0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_REFGEN_STATUS_OUT_SHFT                                  3
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_IE_EN_OUT_BMSK                                        0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_IE_EN_OUT_SHFT                                          2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_BG_EN_OUT_BMSK                                        0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_BG_EN_OUT_SHFT                                          1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_BIAS_EN_OUT_BMSK                                      0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_STATUS_BIAS_EN_OUT_SHFT                                        0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_ADDR(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_PHYS(x)                                                 ((x) + 0x10)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_OFFS                                                    (0x10)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_BGT_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGT_TRIM_BGT_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_ADDR(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_PHYS(x)                                                 ((x) + 0x14)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_OFFS                                                    (0x14)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_RMSK                                                          0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_BGV_TRIM_BMSK                                                 0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BGV_TRIM_BGV_TRIM_SHFT                                                    0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_ADDR(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_PHYS(x)                                                  ((x) + 0x18)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_OFFS                                                     (0x18)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_RMSK                                                           0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_BG_EN_SYNC_MUX_BMSK                                            0x20
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_BG_EN_SYNC_MUX_SHFT                                               5
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_BG_EN_SYNC_BMSK                                                0x10
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_BG_EN_SYNC_SHFT                                                   4
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_EFUSE_BYPASS_BMSK                                               0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_EFUSE_BYPASS_SHFT                                                 3
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_BANDGAP_EN_MUX_BMSK                                             0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_BANDGAP_EN_MUX_SHFT                                               2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_BANDGAP_EN_BMSK                                                 0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_BANDGAP_EN_SHFT                                                   1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_BANDGAP_BYPASS_BMSK                                             0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_BG_CTRL_BANDGAP_BYPASS_SHFT                                               0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_ADDR(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_PHYS(x)                                                ((x) + 0x1c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_OFFS                                                   (0x1c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_RMSK                                                          0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_BYPASS_RSM_RESTRIM_BMSK                                       0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_BYPASS_RSM_RESTRIM_SHFT                                         3
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_BYPASS_RSM_BANDGAP_BMSK                                       0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_BYPASS_RSM_BANDGAP_SHFT                                         2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_RSM_START_MUX_BMSK                                            0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_RSM_START_MUX_SHFT                                              1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_RSM_START_BMSK                                                0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RSM_CNTRL_RSM_START_SHFT                                                  0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_ADDR(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_PHYS(x)                                        ((x) + 0x20)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_OFFS                                           (0x20)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_RMSK                                                 0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_BMSK                               0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_INIT_CODE_RESTRIM_INIT_CODE_SHFT                                  0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_ADDR(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_PHYS(x)                                      ((x) + 0x24)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_OFFS                                         (0x24)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_RMSK                                               0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_BMSK                       0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_BYPASS_CODE_RESTRIM_CMN_BYPASS_CODE_SHFT                          0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_ADDR(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_PHYS(x)                                         ((x) + 0x28)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_OFFS                                            (0x28)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_RMSK                                                   0x3
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_RESTRIM_EN_MUX_BMSK                                    0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_RESTRIM_EN_MUX_SHFT                                      1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_RESTRIM_EN_BMSK                                        0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RES_TRIM_CONTROL_RESTRIM_EN_SHFT                                          0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_ADDR(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_PHYS(x)                                                  ((x) + 0x2c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_OFFS                                                     (0x2c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_RMSK                                                           0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_ADC_FROM_ATB_BMSK                                              0x40
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_ADC_FROM_ATB_SHFT                                                 6
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_ADC_ATB_MUXSEL_BMSK                                            0x20
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_ADC_ATB_MUXSEL_SHFT                                               5
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_DIGITAL_ECO_BKUP_BMSK                                          0x1e
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_DIGITAL_ECO_BKUP_SHFT                                             1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_ADC_EN_BMSK                                                     0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_SEL_ADC_EN_SHFT                                                       0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_ADDR(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_PHYS(x)                                                  ((x) + 0x30)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_OFFS                                                     (0x30)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_RMSK                                                           0x1f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_ADC_CLK_DIV_BMSK                                               0x1f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CLK_ADC_CLK_DIV_SHFT                                                  0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADDR(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_PHYS(x)                                                 ((x) + 0x34)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_OFFS                                                    (0x34)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_RMSK                                                           0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADC_FREEZE_CODE_BMSK                                           0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADC_FREEZE_CODE_SHFT                                             3
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADC_SIGNERR_POL_FLIP_BMSK                                      0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADC_SIGNERR_POL_FLIP_SHFT                                        2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADC_ENABLE_BMSK                                                0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADC_ENABLE_SHFT                                                  1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADC_CLK_ENABLE_BMSK                                            0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CTRL_ADC_CLK_ENABLE_SHFT                                              0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS0_ADDR(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS0_PHYS(x)                                     ((x) + 0x38)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS0_OFFS                                        (0x38)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS0_RMSK                                              0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_BMSK                             0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS0_ADC_CODE_OUT_7_0_SHFT                                0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS1_ADDR(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS1_PHYS(x)                                     ((x) + 0x3c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS1_OFFS                                        (0x3c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS1_RMSK                                             0x300
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_BMSK                            0x300
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_CODE_OUT_STATUS1_ADC_CODE_OUT_9_8_SHFT                                8

#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_ADDR(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_PHYS(x)                                          ((x) + 0x40)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_OFFS                                             (0x40)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_RMSK                                                    0x7
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_RESCAL_ERR_BMSK                                         0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_RESCAL_ERR_SHFT                                           2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_RESETSM_BMSK                                            0x3
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESET_SM_STATUS_RESETSM_SHFT                                              0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_ADDR(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_PHYS(x)                                      ((x) + 0x44)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_OFFS                                         (0x44)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_RMSK                                               0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_REFGEN_READY_BMSK                                  0x80
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_REFGEN_READY_SHFT                                     7
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_RESTRIM_CODE_BMSK                                  0x7f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_RESTRIM_CODE_STATUS_RESTRIM_CODE_SHFT                                     0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_ADDR(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_PHYS(x)                                                 ((x) + 0x48)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_OFFS                                                    (0x48)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_RMSK                                                           0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_SW_RESET_BMSK                                                  0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_SW_RESET_SW_RESET_SHFT                                                    0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS0_ADDR(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS0_PHYS(x)                                               ((x) + 0x4c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS0_OFFS                                                  (0x4c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS0_RMSK                                                        0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS0_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS0_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS0_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS0_DEBUG_BUS_7_0_BMSK                                          0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS0_DEBUG_BUS_7_0_SHFT                                             0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS1_ADDR(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS1_PHYS(x)                                               ((x) + 0x50)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS1_OFFS                                                  (0x50)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS1_RMSK                                                        0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS1_DEBUG_BUS_15_8_BMSK                                         0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS1_DEBUG_BUS_15_8_SHFT                                            0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_ADDR(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_PHYS(x)                                            ((x) + 0x54)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_OFFS                                               (0x54)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_RMSK                                                      0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_DEBUG_BUS_SEL_BMSK                                        0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_BUS_SEL_DEBUG_BUS_SEL_SHFT                                          0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_ADDR(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_PHYS(x)                                               ((x) + 0x58)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_OFFS                                                  (0x58)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_RMSK                                                         0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_FORCE_REFGEN_READY_BMSK                                      0x8
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_FORCE_REFGEN_READY_SHFT                                        3
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_BMSK                                   0x4
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_RESTRIM_DEBUG_ADVANCE_SHFT                                     2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_RESTRIM_DEBUG_MODE_BMSK                                      0x2
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_RESTRIM_DEBUG_MODE_SHFT                                        1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_DISABLE_CLOCK_GATING_BMSK                                    0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_DEBUG_CTRL_DISABLE_CLOCK_GATING_SHFT                                      0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_ADDR(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_PHYS(x)                                         ((x) + 0x5c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_OFFS                                            (0x5c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_RMSK                                                  0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_REFGEN_CTRL1_BMSK                                     0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL1_REFGEN_CTRL1_SHFT                                        0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_ADDR(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_PHYS(x)                                         ((x) + 0x60)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_OFFS                                            (0x60)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_RMSK                                                  0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_REFGEN_CTRL2_BMSK                                     0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CMN_REFGEN_CTRL2_REFGEN_CTRL2_SHFT                                        0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_ADDR(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_PHYS(x)                                             ((x) + 0x64)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_OFFS                                                (0x64)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_RMSK                                                      0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_BMSK                                    0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL1_PWRDWN_B_CTRL_7_0_SHFT                                       0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_ADDR(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_PHYS(x)                                             ((x) + 0x68)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_OFFS                                                (0x68)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_RMSK                                                      0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_BMSK                                   0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL2_PWRDWN_B_CTRL_13_8_SHFT                                      0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_ADDR(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_PHYS(x)                                             ((x) + 0x6c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_OFFS                                                (0x6c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_RMSK                                                      0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_BMSK                                0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL3_PWRDWN_B_CTRL_MUX_7_0_SHFT                                   0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_ADDR(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_PHYS(x)                                             ((x) + 0x70)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_OFFS                                                (0x70)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_RMSK                                                      0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_BMSK                               0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL4_PWRDWN_B_CTRL_MUX_13_8_SHFT                                  0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS1_ADDR(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS1_PHYS(x)                                           ((x) + 0x74)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS1_OFFS                                              (0x74)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS1_RMSK                                                    0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_BMSK                                   0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS1_PWRDWN_B_OUT_7_0_SHFT                                      0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS2_ADDR(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS2_PHYS(x)                                           ((x) + 0x78)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS2_OFFS                                              (0x78)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS2_RMSK                                                    0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS2_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS2_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_BMSK                                  0x3f
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_STATUS2_PWRDWN_B_OUT_13_8_SHFT                                     0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_ADDR(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_PHYS(x)                                             ((x) + 0x7c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_OFFS                                                (0x7c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_RMSK                                                       0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_STATUS_WAIT_TIME_BMSK                                      0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_5_STATUS_TIMER_STATUS_WAIT_TIME_SHFT                                        0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_ADDR(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_PHYS(x)                                             ((x) + 0x80)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_OFFS                                                (0x80)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_RMSK                                                       0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_PWRDWN_B_SW_BMSK                                           0xf
#define HWIO_AHB2PHY_1PHY_REFGEN_5_PWRDWN_CTRL5_PWRDWN_B_SW_SHFT                                             0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADDR(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_PHYS(x)                                       ((x) + 0x84)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_OFFS                                          (0x84)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_RMSK                                                0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADC_DSM_MISC_BMSK                                   0xc0
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADC_DSM_MISC_SHFT                                      6
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADC_ATT_EN_BMSK                                     0x20
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADC_ATT_EN_SHFT                                        5
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADC_DTH_SET_BMSK                                    0x10
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADC_DTH_SET_SHFT                                       4
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADC_DTH_DAC_BMSK                                     0xe
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADC_DTH_DAC_SHFT                                       1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADC_DTH_EN_BMSK                                      0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_ADC_MODULATOR_CTRL_ADC_DTH_EN_SHFT                                        0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_ADDR(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_PHYS(x)                                 ((x) + 0x88)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_OFFS                                    (0x88)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_RMSK                                          0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_OUT(x, v)            \
                out_dword(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_ADDR(x),v)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_ADDR(x),m,v,HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_IN(x))
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_BMSK                        0x80
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_LEGACY_IIR_ENABLE_SHFT                           7
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_BMSK                              0x40
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_CIC3_ENABLE_SHFT                                 6
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_BMSK                                0x20
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_ADC_RESET_SHFT                                   5
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_BMSK                       0x18
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_CIC3_MISC_SETTINGS_SHFT                          3
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_BMSK                 0x7
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_FILTER_SETTINGS_CIC3_DECIMATION_PARAMETER_SHFT                   0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS0_PHYS(x)                                ((x) + 0x8c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS0_OFFS                                   (0x8c)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS0_RMSK                                         0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS0_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS0_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS0_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_BMSK                   0xff
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS0_CIC3_ADC_CODE_OUT_7_0_SHFT                      0

#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS1_PHYS(x)                                ((x) + 0x90)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS1_OFFS                                   (0x90)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS1_RMSK                                       0xff00
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS1_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS1_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS1_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_BMSK                0xff00
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS1_CIC3_ADC_CODE_OUT_15_8_SHFT                     8

#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS2_PHYS(x)                                ((x) + 0x94)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS2_OFFS                                   (0x94)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS2_RMSK                                     0xff0000
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS2_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS2_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS2_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_BMSK             0xff0000
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS2_CIC3_ADC_CODE_OUT_23_16_SHFT                   16

#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS3_PHYS(x)                                ((x) + 0x98)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS3_OFFS                                   (0x98)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS3_RMSK                                          0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS3_IN(x)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS3_RMSK)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS3_INM(x, m)            \
                in_dword_masked(HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS3_ADDR(x), m)
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_BMSK                  0x1
#define HWIO_AHB2PHY_1PHY_REFGEN_5_CIC3_ADC_CODE_OUT_STATUS3_CIC3_ADC_CODE_OUT_24_24_SHFT                    0


#endif /* __HWIO_REFGEN_H__ */
