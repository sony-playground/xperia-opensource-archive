#ifndef __SPMICOREHWIO_H__
#define __SPMICOREHWIO_H__
/*
===========================================================================
*/
/**
    @file SpmiCoreHwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8450 (Waipio) [waipio_v1.0_p3q2r14.6_rtl_partition_M01]
 
    This file contains HWIO register definitions for the following modules:
        SPMI0_SPMI_CFG
        SPMI0_SPMI_PIC_OWNER
        SPMI0_SPMI_SPMI_GENI_CFG
        SPMI1_SPMI_CFG
        SPMI1_SPMI_PIC_OWNER
        SPMI1_SPMI_SPMI_GENI_CFG
        SPMI0_SPMI_CFG_TOP
        SPMI1_SPMI_CFG_TOP


    Generation parameters: 
    { 'explicit-addressing': True,
      'filename': 'SpmiCoreHwio.h',
      'module-filter-exclude': {},
      'module-filter-include': {},
      'modules': [ 'SPMI0_SPMI_CFG',
                   'SPMI0_SPMI_PIC_OWNER',
                   'SPMI0_SPMI_SPMI_GENI_CFG',
                   'SPMI1_SPMI_CFG',
                   'SPMI1_SPMI_PIC_OWNER',
                   'SPMI1_SPMI_SPMI_GENI_CFG',
                   'SPMI0_SPMI_CFG_TOP',
                   'SPMI1_SPMI_CFG_TOP'],
      'output-offsets': True}
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

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SPMILib/src/core/hal/hoya7/hw/v7p0/SpmiCoreHwio.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: SPMI0_SPMI_CFG
 *--------------------------------------------------------------------------*/
#define SPMI0_SPMI_CFG_REG_BASE_OFFS                                                        0x2D000

#define HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,m)                               ((base) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0X0 + (0x4*(m)))
#define HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_OFFS(m)                                    (0X0 + (0x4*(m)))
#define HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_RMSK                                        0xfff000f
#define HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_INI(base,m)                \
                in_dword_masked(HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,m), HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_RMSK)
#define HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_INMI(base,m,mask)        \
                in_dword_masked(HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,m), mask)
#define HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_OUTI(base,m,val)        \
                out_dword(HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,m),val)
#define HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_OUTMI(base,m,mask,val) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,m),mask,val,HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_INI(base,m))
#define HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_APID2PPID_BMSK                              0xfff0000
#define HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_APID2PPID_SHFT                                     16
#define HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_PERIPH2OWNER_BMSK                                 0xf
#define HWIO_SPMI0_SPMI_PERIPHm_2OWNER_TABLE_REG_PERIPH2OWNER_SHFT                                   0

#define HWIO_SPMI0_SPMI_MID_REG_ADDR(x)                                                     ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1800)
#define HWIO_SPMI0_SPMI_MID_REG_OFFS                                                        (0x1800)
#define HWIO_SPMI0_SPMI_MID_REG_RMSK                                                               0x3
#define HWIO_SPMI0_SPMI_MID_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_MID_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_MID_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_MID_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_MID_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_MID_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_MID_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_MID_REG_ADDR(x),m,v,HWIO_SPMI0_SPMI_MID_REG_IN(x))
#define HWIO_SPMI0_SPMI_MID_REG_MID_BMSK                                                           0x3
#define HWIO_SPMI0_SPMI_MID_REG_MID_SHFT                                                             0

#define HWIO_SPMI0_SPMI_CFG_REG_ADDR(x)                                                     ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1804)
#define HWIO_SPMI0_SPMI_CFG_REG_OFFS                                                        (0x1804)
#define HWIO_SPMI0_SPMI_CFG_REG_RMSK                                                         0x3ffffff
#define HWIO_SPMI0_SPMI_CFG_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_CFG_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_CFG_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_CFG_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_CFG_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_CFG_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_CFG_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_CFG_REG_ADDR(x),m,v,HWIO_SPMI0_SPMI_CFG_REG_IN(x))
#define HWIO_SPMI0_SPMI_CFG_REG_LATENCY_CNTR_BMSK                                            0x3800000
#define HWIO_SPMI0_SPMI_CFG_REG_LATENCY_CNTR_SHFT                                                   23
#define HWIO_SPMI0_SPMI_CFG_REG_SCLK_OE_EXTEND_BMSK                                           0x400000
#define HWIO_SPMI0_SPMI_CFG_REG_SCLK_OE_EXTEND_SHFT                                                 22
#define HWIO_SPMI0_SPMI_CFG_REG_RPMH_CLK_REQ_EN_BMSK                                          0x200000
#define HWIO_SPMI0_SPMI_CFG_REG_RPMH_CLK_REQ_EN_SHFT                                                21
#define HWIO_SPMI0_SPMI_CFG_REG_WDT_CFG_BMSK                                                  0x1e0000
#define HWIO_SPMI0_SPMI_CFG_REG_WDT_CFG_SHFT                                                        17
#define HWIO_SPMI0_SPMI_CFG_REG_ARBITER_CTRL_BMSK                                              0x1e000
#define HWIO_SPMI0_SPMI_CFG_REG_ARBITER_CTRL_SHFT                                                   13
#define HWIO_SPMI0_SPMI_CFG_REG_GENI_SPMI_BUS_IN_MASK_DIS_BMSK                                  0x1000
#define HWIO_SPMI0_SPMI_CFG_REG_GENI_SPMI_BUS_IN_MASK_DIS_SHFT                                      12
#define HWIO_SPMI0_SPMI_CFG_REG_ASYNC_SSC_DET_INT_DIS_BMSK                                       0x800
#define HWIO_SPMI0_SPMI_CFG_REG_ASYNC_SSC_DET_INT_DIS_SHFT                                          11
#define HWIO_SPMI0_SPMI_CFG_REG_SSC_Q1_DELAY_DIS_BMSK                                            0x400
#define HWIO_SPMI0_SPMI_CFG_REG_SSC_Q1_DELAY_DIS_SHFT                                               10
#define HWIO_SPMI0_SPMI_CFG_REG_ARB_UNKNOWN_EN_BMSK                                              0x200
#define HWIO_SPMI0_SPMI_CFG_REG_ARB_UNKNOWN_EN_SHFT                                                  9
#define HWIO_SPMI0_SPMI_CFG_REG_SSC_WINDOW_EN_BMSK                                               0x100
#define HWIO_SPMI0_SPMI_CFG_REG_SSC_WINDOW_EN_SHFT                                                   8
#define HWIO_SPMI0_SPMI_CFG_REG_SSC_DET_INT_DIS_BMSK                                              0x80
#define HWIO_SPMI0_SPMI_CFG_REG_SSC_DET_INT_DIS_SHFT                                                 7
#define HWIO_SPMI0_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_IMM_BMSK                                        0x40
#define HWIO_SPMI0_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_IMM_SHFT                                           6
#define HWIO_SPMI0_SPMI_CFG_REG_FORCE_ARB_AFTER_MASTER_TO_BMSK                                    0x20
#define HWIO_SPMI0_SPMI_CFG_REG_FORCE_ARB_AFTER_MASTER_TO_SHFT                                       5
#define HWIO_SPMI0_SPMI_CFG_REG_BUS_IDLE_CONN_MODE_BMSK                                           0x10
#define HWIO_SPMI0_SPMI_CFG_REG_BUS_IDLE_CONN_MODE_SHFT                                              4
#define HWIO_SPMI0_SPMI_CFG_REG_FORCE_MASTER_WRITE_ON_ERROR_BMSK                                   0x8
#define HWIO_SPMI0_SPMI_CFG_REG_FORCE_MASTER_WRITE_ON_ERROR_SHFT                                     3
#define HWIO_SPMI0_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_BMSK                                             0x4
#define HWIO_SPMI0_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_SHFT                                               2
#define HWIO_SPMI0_SPMI_CFG_REG_ARBITER_BYPASS_BMSK                                                0x2
#define HWIO_SPMI0_SPMI_CFG_REG_ARBITER_BYPASS_SHFT                                                  1
#define HWIO_SPMI0_SPMI_CFG_REG_ARBITER_ENABLE_BMSK                                                0x1
#define HWIO_SPMI0_SPMI_CFG_REG_ARBITER_ENABLE_SHFT                                                  0

#define HWIO_SPMI0_SPMI_SEC_DISABLE_REG_ADDR(x)                                             ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1808)
#define HWIO_SPMI0_SPMI_SEC_DISABLE_REG_OFFS                                                (0x1808)
#define HWIO_SPMI0_SPMI_SEC_DISABLE_REG_RMSK                                                       0x1
#define HWIO_SPMI0_SPMI_SEC_DISABLE_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_SEC_DISABLE_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_SEC_DISABLE_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_SEC_DISABLE_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_SEC_DISABLE_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_SEC_DISABLE_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_SEC_DISABLE_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_SEC_DISABLE_REG_ADDR(x),m,v,HWIO_SPMI0_SPMI_SEC_DISABLE_REG_IN(x))
#define HWIO_SPMI0_SPMI_SEC_DISABLE_REG_DISABLE_SECURITY_BMSK                                      0x1
#define HWIO_SPMI0_SPMI_SEC_DISABLE_REG_DISABLE_SECURITY_SHFT                                        0

#define HWIO_SPMI0_SPMI_HW_VERSION_ADDR(x)                                                  ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x180c)
#define HWIO_SPMI0_SPMI_HW_VERSION_OFFS                                                     (0x180c)
#define HWIO_SPMI0_SPMI_HW_VERSION_RMSK                                                     0xff000fff
#define HWIO_SPMI0_SPMI_HW_VERSION_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_HW_VERSION_ADDR(x))
#define HWIO_SPMI0_SPMI_HW_VERSION_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_HW_VERSION_ADDR(x), m)
#define HWIO_SPMI0_SPMI_HW_VERSION_HW_VERSION_RUNNING_R_BMSK                                0xff000000
#define HWIO_SPMI0_SPMI_HW_VERSION_HW_VERSION_RUNNING_R_SHFT                                        24
#define HWIO_SPMI0_SPMI_HW_VERSION_HW_VERSION_MAJOR_BMSK                                         0xf00
#define HWIO_SPMI0_SPMI_HW_VERSION_HW_VERSION_MAJOR_SHFT                                             8
#define HWIO_SPMI0_SPMI_HW_VERSION_HW_VERSION_MINOR_BMSK                                          0xf0
#define HWIO_SPMI0_SPMI_HW_VERSION_HW_VERSION_MINOR_SHFT                                             4
#define HWIO_SPMI0_SPMI_HW_VERSION_HW_VERSION_STEP_BMSK                                            0xf
#define HWIO_SPMI0_SPMI_HW_VERSION_HW_VERSION_STEP_SHFT                                              0

#define HWIO_SPMI0_SPMI_CGC_CTRL_ADDR(x)                                                    ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1810)
#define HWIO_SPMI0_SPMI_CGC_CTRL_OFFS                                                       (0x1810)
#define HWIO_SPMI0_SPMI_CGC_CTRL_RMSK                                                             0x7f
#define HWIO_SPMI0_SPMI_CGC_CTRL_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_CGC_CTRL_ADDR(x))
#define HWIO_SPMI0_SPMI_CGC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_CGC_CTRL_ADDR(x), m)
#define HWIO_SPMI0_SPMI_CGC_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_CGC_CTRL_ADDR(x),v)
#define HWIO_SPMI0_SPMI_CGC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_CGC_CTRL_ADDR(x),m,v,HWIO_SPMI0_SPMI_CGC_CTRL_IN(x))
#define HWIO_SPMI0_SPMI_CGC_CTRL_MAP_LOGIC_CLK_CGC_ON_BMSK                                        0x40
#define HWIO_SPMI0_SPMI_CGC_CTRL_MAP_LOGIC_CLK_CGC_ON_SHFT                                           6
#define HWIO_SPMI0_SPMI_CGC_CTRL_RPU_CLK_CGC_ON_BMSK                                              0x20
#define HWIO_SPMI0_SPMI_CGC_CTRL_RPU_CLK_CGC_ON_SHFT                                                 5
#define HWIO_SPMI0_SPMI_CGC_CTRL_MWB_CLK_CGC_ON_BMSK                                              0x10
#define HWIO_SPMI0_SPMI_CGC_CTRL_MWB_CLK_CGC_ON_SHFT                                                 4
#define HWIO_SPMI0_SPMI_CGC_CTRL_PIC_CLK_CGC_ON_BMSK                                               0x8
#define HWIO_SPMI0_SPMI_CGC_CTRL_PIC_CLK_CGC_ON_SHFT                                                 3
#define HWIO_SPMI0_SPMI_CGC_CTRL_PAC_CLK_CGC_ON_BMSK                                               0x4
#define HWIO_SPMI0_SPMI_CGC_CTRL_PAC_CLK_CGC_ON_SHFT                                                 2
#define HWIO_SPMI0_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_WR_CLK_CGC_ON_BMSK                                 0x2
#define HWIO_SPMI0_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_WR_CLK_CGC_ON_SHFT                                   1
#define HWIO_SPMI0_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_CLK_CGC_ON_BMSK                                    0x1
#define HWIO_SPMI0_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_CLK_CGC_ON_SHFT                                      0

#define HWIO_SPMI0_SPMI_MWB_ENABLE_REG_ADDR(x)                                              ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1814)
#define HWIO_SPMI0_SPMI_MWB_ENABLE_REG_OFFS                                                 (0x1814)
#define HWIO_SPMI0_SPMI_MWB_ENABLE_REG_RMSK                                                        0x1
#define HWIO_SPMI0_SPMI_MWB_ENABLE_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_MWB_ENABLE_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_MWB_ENABLE_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_MWB_ENABLE_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_MWB_ENABLE_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_MWB_ENABLE_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_MWB_ENABLE_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_MWB_ENABLE_REG_ADDR(x),m,v,HWIO_SPMI0_SPMI_MWB_ENABLE_REG_IN(x))
#define HWIO_SPMI0_SPMI_MWB_ENABLE_REG_MWB_ENABLE_BMSK                                             0x1
#define HWIO_SPMI0_SPMI_MWB_ENABLE_REG_MWB_ENABLE_SHFT                                               0

#define HWIO_SPMI0_SPMI_CHAR_CFG_ADDR(x)                                                    ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1840)
#define HWIO_SPMI0_SPMI_CHAR_CFG_OFFS                                                       (0x1840)
#define HWIO_SPMI0_SPMI_CHAR_CFG_RMSK                                                          0xfff11
#define HWIO_SPMI0_SPMI_CHAR_CFG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_CHAR_CFG_ADDR(x))
#define HWIO_SPMI0_SPMI_CHAR_CFG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_CHAR_CFG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_CHAR_CFG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_CHAR_CFG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_CHAR_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_CHAR_CFG_ADDR(x),m,v,HWIO_SPMI0_SPMI_CHAR_CFG_IN(x))
#define HWIO_SPMI0_SPMI_CHAR_CFG_CHAR_MODE_BMSK                                                0xff000
#define HWIO_SPMI0_SPMI_CHAR_CFG_CHAR_MODE_SHFT                                                     12
#define HWIO_SPMI0_SPMI_CHAR_CFG_CHAR_STATUS_BMSK                                                0xf00
#define HWIO_SPMI0_SPMI_CHAR_CFG_CHAR_STATUS_SHFT                                                    8
#define HWIO_SPMI0_SPMI_CHAR_CFG_DIRECTION_BMSK                                                   0x10
#define HWIO_SPMI0_SPMI_CHAR_CFG_DIRECTION_SHFT                                                      4
#define HWIO_SPMI0_SPMI_CHAR_CFG_ENABLE_BMSK                                                       0x1
#define HWIO_SPMI0_SPMI_CHAR_CFG_ENABLE_SHFT                                                         0

#define HWIO_SPMI0_SPMI_CHAR_DATA_n_ADDR(base,n)                                            ((base) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0X1844 + (0x4*(n)))
#define HWIO_SPMI0_SPMI_CHAR_DATA_n_OFFS(n)                                                 (0X1844 + (0x4*(n)))
#define HWIO_SPMI0_SPMI_CHAR_DATA_n_RMSK                                                        0xffff
#define HWIO_SPMI0_SPMI_CHAR_DATA_n_INI(base,n)                \
                in_dword_masked(HWIO_SPMI0_SPMI_CHAR_DATA_n_ADDR(base,n), HWIO_SPMI0_SPMI_CHAR_DATA_n_RMSK)
#define HWIO_SPMI0_SPMI_CHAR_DATA_n_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI0_SPMI_CHAR_DATA_n_ADDR(base,n), mask)
#define HWIO_SPMI0_SPMI_CHAR_DATA_n_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI0_SPMI_CHAR_DATA_n_ADDR(base,n),val)
#define HWIO_SPMI0_SPMI_CHAR_DATA_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_CHAR_DATA_n_ADDR(base,n),mask,val,HWIO_SPMI0_SPMI_CHAR_DATA_n_INI(base,n))
#define HWIO_SPMI0_SPMI_CHAR_DATA_n_DIN_ACTUAL_BMSK                                             0xff00
#define HWIO_SPMI0_SPMI_CHAR_DATA_n_DIN_ACTUAL_SHFT                                                  8
#define HWIO_SPMI0_SPMI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_BMSK                                        0xff
#define HWIO_SPMI0_SPMI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_SHFT                                           0

#define HWIO_SPMI0_SPMI_CMPR_EN_REG_ADDR(x)                                                 ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1854)
#define HWIO_SPMI0_SPMI_CMPR_EN_REG_OFFS                                                    (0x1854)
#define HWIO_SPMI0_SPMI_CMPR_EN_REG_RMSK                                                           0x1
#define HWIO_SPMI0_SPMI_CMPR_EN_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_CMPR_EN_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_CMPR_EN_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_CMPR_EN_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_CMPR_EN_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_CMPR_EN_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_CMPR_EN_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_CMPR_EN_REG_ADDR(x),m,v,HWIO_SPMI0_SPMI_CMPR_EN_REG_IN(x))
#define HWIO_SPMI0_SPMI_CMPR_EN_REG_CMPR_ENABLE_BMSK                                               0x1
#define HWIO_SPMI0_SPMI_CMPR_EN_REG_CMPR_ENABLE_SHFT                                                 0

#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_ADDR(x)                                             ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1858)
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_OFFS                                                (0x1858)
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_RMSK                                                     0x3ff
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_ADDR(x),m,v,HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_IN(x))
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_BMSK                                 0x200
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_SHFT                                     9
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_SM_MM_MODE_BMSK                      0x100
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_SM_MM_MODE_SHFT                          8
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SNOOPER_SW_RST_EN_BMSK                                    0x80
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SNOOPER_SW_RST_EN_SHFT                                       7
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_FROM_SPMI_M_EN_BMSK                   0x40
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_FROM_SPMI_M_EN_SHFT                      6
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_TEST_BUS_SELECT_BMSK                   0x38
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_TEST_BUS_SELECT_SHFT                      3
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_MODE_BMSK                                     0x4
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_MODE_SHFT                                       2
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_SSC_DET_CFG_BMSK                        0x3
#define HWIO_SPMI0_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_SSC_DET_CFG_SHFT                          0

#define HWIO_SPMI0_SPMI_STATUS_REG_ADDR(x)                                                  ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x185c)
#define HWIO_SPMI0_SPMI_STATUS_REG_OFFS                                                     (0x185c)
#define HWIO_SPMI0_SPMI_STATUS_REG_RMSK                                                            0x1
#define HWIO_SPMI0_SPMI_STATUS_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_STATUS_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_STATUS_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_STATUS_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_STATUS_REG_ARB_IS_BOM_BMSK                                                 0x1
#define HWIO_SPMI0_SPMI_STATUS_REG_ARB_IS_BOM_SHFT                                                   0

#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,n)                                       ((base) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0X1A00 + (0x4*(n)))
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_OFFS(n)                                            (0X1A00 + (0x4*(n)))
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_RMSK                                               0xff8fffff
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_INI(base,n)                \
                in_dword_masked(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,n), HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_RMSK)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,n), mask)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,n),val)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,n),mask,val,HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_INI(base,n))
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_MSG_MASK_BMSK                                      0xff000000
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_MSG_MASK_SHFT                                              24
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_VIOCTL_EN_BMSK                                       0x800000
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_VIOCTL_EN_SHFT                                             23
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_SID_BMSK                                              0xf0000
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_SID_SHFT                                                   16
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_PID_BMSK                                               0xff00
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_PID_SHFT                                                    8
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_RCS_MSG_BMSK                                             0xff
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_n_RCS_MSG_SHFT                                                0

#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,n)                        ((base) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0X1A80 + (0x4*(n)))
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_OFFS(n)                             (0X1A80 + (0x4*(n)))
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_RMSK                                       0x1
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_INI(base,n)                \
                in_dword_masked(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,n), HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_RMSK)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,n), mask)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,n),val)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,n),mask,val,HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_INI(base,n))
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ENABLE_BMSK                                0x1
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ENABLE_SHFT                                  0

#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x)                               ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1b00)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_OFFS                                  (0x1b00)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_RMSK                                        0xff
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x))
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x), m)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x),v)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x),m,v,HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_IN(x))
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_CTR_CFG_BMSK                                0xff
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_CTR_CFG_SHFT                                   0

#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,n)                                     ((base) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0X1B80 + (0x4*(n)))
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_OFFS(n)                                          (0X1B80 + (0x4*(n)))
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_RMSK                                             0xff8fffff
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_INI(base,n)                \
                in_dword_masked(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,n), HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_RMSK)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,n), mask)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,n),val)
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,n),mask,val,HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_INI(base,n))
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_MSG_MASK_BMSK                                    0xff000000
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_MSG_MASK_SHFT                                            24
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_VIOCTL_EN_BMSK                                     0x800000
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_VIOCTL_EN_SHFT                                           23
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_SID_BMSK                                            0xf0000
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_SID_SHFT                                                 16
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_PID_BMSK                                             0xff00
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_PID_SHFT                                                  8
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_RCS_MSG_BMSK                                           0xff
#define HWIO_SPMI0_SPMI_PIC_RCS_VIOCTL_N_n_RCS_MSG_SHFT                                              0

#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_ADDR(x)                                              ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1c00)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_OFFS                                                 (0x1c00)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_RMSK                                                    0x3ffff
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_ADDR(x))
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_ADDR(x), m)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_ADDR(x),v)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_ADDR(x),m,v,HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_IN(x))
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_WDT_ARB_EN_CRTL_BMSK                                    0x20000
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_WDT_ARB_EN_CRTL_SHFT                                         17
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_PMIC_ARB_ARST_EN_BMSK                                   0x10000
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_PMIC_ARB_ARST_EN_SHFT                                        16
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_M_ARB_ARST_EN_BMSK                                  0x8000
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_M_ARB_ARST_EN_SHFT                                      15
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_GENI_ARST_EN_BMSK                                        0x4000
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_GENI_ARST_EN_SHFT                                            14
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_ARST_ASSERT_BMSK                            0x2000
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_ARST_ASSERT_SHFT                                13
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_ARST_ASSERT_BMSK                            0x1000
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_ARST_ASSERT_SHFT                                12
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_SCLK_ARES_ASSERT_BMSK                                0x800
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_SCLK_ARES_ASSERT_SHFT                                   11
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_ARST_ASSERT_BMSK                         0x400
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_ARST_ASSERT_SHFT                            10
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_BUS_CLK_GATE_EN_BMSK                                 0x200
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_BUS_CLK_GATE_EN_SHFT                                     9
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_GATE_EN_BMSK                                 0x100
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_GATE_EN_SHFT                                     8
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_PMIC_ARB_CLK_GATE_EN_BMSK                                  0x80
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_PMIC_ARB_CLK_GATE_EN_SHFT                                     7
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_GATE_EN_BMSK                                  0x40
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_GATE_EN_SHFT                                     6
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SLEEP_CLK_GATE_EN_BMSK                                     0x20
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SLEEP_CLK_GATE_EN_SHFT                                        5
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_GATE_EN_BMSK                              0x10
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_GATE_EN_SHFT                                 4
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_EN_BMSK                                       0x8
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_EN_SHFT                                         3
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_CLR_BMSK                                      0x4
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_CLR_SHFT                                        2
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_WDT_AUTO_HW_EN_BMSK                                         0x2
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_WDT_AUTO_HW_EN_SHFT                                           1
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_WDT_CNT_EN_BMSK                                             0x1
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_0_WDT_CNT_EN_SHFT                                               0

#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_ADDR(x)                                              ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1c04)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_OFFS                                                 (0x1c04)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_RMSK                                                   0xfff00f
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_ADDR(x))
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_ADDR(x), m)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_ADDR(x),v)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_ADDR(x),m,v,HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_IN(x))
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_RESET_ASSERT_INTERVAL_BMSK                             0xf00000
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_RESET_ASSERT_INTERVAL_SHFT                                   20
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_CLK_GATE_EN_TO_RST_ASSERT_INTERVAL_BMSK                 0xf0000
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_CLK_GATE_EN_TO_RST_ASSERT_INTERVAL_SHFT                      16
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_ARB_EN_TO_CLK_GATE_EN_INTERVAL_BMSK                      0xf000
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_ARB_EN_TO_CLK_GATE_EN_INTERVAL_SHFT                          12
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_WDT_CTR_EXPIRY_VALUE_BMSK                                   0xf
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_1_WDT_CTR_EXPIRY_VALUE_SHFT                                     0

#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_ADDR(x)                                              ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1c08)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_OFFS                                                 (0x1c08)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_RMSK                                                        0x3
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_ADDR(x))
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_ADDR(x), m)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_ADDR(x),v)
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_ADDR(x),m,v,HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_IN(x))
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_WDT_SCLK_RST_MODE_BMSK                                      0x2
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_WDT_SCLK_RST_MODE_SHFT                                        1
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_WDT_SW_RST_BMSK                                             0x1
#define HWIO_SPMI0_SPMI_WDT_CTRL_REG_2_WDT_SW_RST_SHFT                                               0

#define HWIO_SPMI0_SPMI_WDT_STATUS_REG_ADDR(x)                                              ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1c0c)
#define HWIO_SPMI0_SPMI_WDT_STATUS_REG_OFFS                                                 (0x1c0c)
#define HWIO_SPMI0_SPMI_WDT_STATUS_REG_RMSK                                                        0x1
#define HWIO_SPMI0_SPMI_WDT_STATUS_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_WDT_STATUS_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_WDT_STATUS_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_WDT_STATUS_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_WDT_STATUS_REG_WDT_DONE_BMSK                                               0x1
#define HWIO_SPMI0_SPMI_WDT_STATUS_REG_WDT_DONE_SHFT                                                 0

#define HWIO_SPMI0_SPMI_WDT_DEBUG_CNT_REG_ADDR(x)                                           ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x1c10)
#define HWIO_SPMI0_SPMI_WDT_DEBUG_CNT_REG_OFFS                                              (0x1c10)
#define HWIO_SPMI0_SPMI_WDT_DEBUG_CNT_REG_RMSK                                                  0xffff
#define HWIO_SPMI0_SPMI_WDT_DEBUG_CNT_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_WDT_DEBUG_CNT_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_WDT_DEBUG_CNT_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_WDT_DEBUG_CNT_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_WDT_DEBUG_CNT_REG_WDT_DEBUG_CNT_BMSK                                    0xffff
#define HWIO_SPMI0_SPMI_WDT_DEBUG_CNT_REG_WDT_DEBUG_CNT_SHFT                                         0

#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_ADDR(x)                                         ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x2000)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_OFFS                                            (0x2000)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_RMSK                                                0x3fff
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_ADDR(x))
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_ADDR(x), m)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_WDT_RST_COMPLETION_BMSK                             0x2000
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_WDT_RST_COMPLETION_SHFT                                 13
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_WDT_EXPIRY_BMSK                                     0x1000
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_WDT_EXPIRY_SHFT                                         12
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_DISCONNECTED_BMSK                            0x800
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_DISCONNECTED_SHFT                               11
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_CONNECTED_BMSK                               0x400
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_CONNECTED_SHFT                                  10
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_PERIH_IRQ_LOST_BMSK                                  0x200
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_PERIH_IRQ_LOST_SHFT                                      9
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_UNEXPECTED_SSC_BMSK                                  0x100
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_UNEXPECTED_SSC_SHFT                                      8
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                  0x80
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                     7
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                   0x40
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                      6
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_FALSE_MASTER_ARBITRATION_WIN_BMSK                     0x20
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_FALSE_MASTER_ARBITRATION_WIN_SHFT                        5
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_FALSE_BUS_REQUEST_BMSK                                0x10
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_FALSE_BUS_REQUEST_SHFT                                   4
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_UNSUPPORTED_COMMAND_BMSK                               0x8
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_UNSUPPORTED_COMMAND_SHFT                                 3
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                      0x4
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                        2
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                      0x2
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                        1
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                     0x1
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_STATUS_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                       0

#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x)                                         ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x2004)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_OFFS                                            (0x2004)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_RMSK                                                0x3fff
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x))
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x), m)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x),v)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x),m,v,HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_IN(x))
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_WDT_RST_COMPLETION_BMSK                             0x2000
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_WDT_RST_COMPLETION_SHFT                                 13
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_WDT_EXPIRY_BMSK                                     0x1000
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_WDT_EXPIRY_SHFT                                         12
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_DISCONNECTED_BMSK                            0x800
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_DISCONNECTED_SHFT                               11
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_CONNECTED_BMSK                               0x400
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_CONNECTED_SHFT                                  10
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_PERIH_IRQ_LOST_BMSK                                  0x200
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_PERIH_IRQ_LOST_SHFT                                      9
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_UNEXPECTED_SSC_BMSK                                  0x100
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_UNEXPECTED_SSC_SHFT                                      8
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                  0x80
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                     7
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                   0x40
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                      6
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_MASTER_ARBITRATION_WIN_BMSK                     0x20
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_MASTER_ARBITRATION_WIN_SHFT                        5
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_BUS_REQUEST_BMSK                                0x10
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_BUS_REQUEST_SHFT                                   4
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_UNSUPPORTED_COMMAND_BMSK                               0x8
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_UNSUPPORTED_COMMAND_SHFT                                 3
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                      0x4
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                        2
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                      0x2
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                        1
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                     0x1
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_ENABLE_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                       0

#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_ADDR(x)                                          ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x2008)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_OFFS                                             (0x2008)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_RMSK                                                 0x3fff
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_ADDR(x),v)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_WDT_RST_COMPLETION_BMSK                              0x2000
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_WDT_RST_COMPLETION_SHFT                                  13
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_WDT_EXPIRY_BMSK                                      0x1000
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_WDT_EXPIRY_SHFT                                          12
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_DISCONNECTED_BMSK                             0x800
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_DISCONNECTED_SHFT                                11
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_CONNECTED_BMSK                                0x400
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_CONNECTED_SHFT                                   10
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_PERIH_IRQ_LOST_BMSK                                   0x200
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_PERIH_IRQ_LOST_SHFT                                       9
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_UNEXPECTED_SSC_BMSK                                   0x100
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_UNEXPECTED_SSC_SHFT                                       8
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                   0x80
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                      7
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                    0x40
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                       6
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_MASTER_ARBITRATION_WIN_BMSK                      0x20
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_MASTER_ARBITRATION_WIN_SHFT                         5
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_BUS_REQUEST_BMSK                                 0x10
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_BUS_REQUEST_SHFT                                    4
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_UNSUPPORTED_COMMAND_BMSK                                0x8
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_UNSUPPORTED_COMMAND_SHFT                                  3
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                       0x4
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                         2
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                       0x2
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                         1
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                      0x1
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                        0

#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_ADDR(x)                                         ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x200c)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_OFFS                                            (0x200c)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_RMSK                                                0x3fff
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_ADDR(x),v)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_WDT_RST_COMPLETION_BMSK                             0x2000
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_WDT_RST_COMPLETION_SHFT                                 13
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_WDT_EXPIRY_BMSK                                     0x1000
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_WDT_EXPIRY_SHFT                                         12
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_DISCONNECTED_BMSK                            0x800
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_DISCONNECTED_SHFT                               11
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_CONNECTED_BMSK                               0x400
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_CONNECTED_SHFT                                  10
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_PERIH_IRQ_LOST_BMSK                                  0x200
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_PERIH_IRQ_LOST_SHFT                                      9
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_UNEXPECTED_SSC_BMSK                                  0x100
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_UNEXPECTED_SSC_SHFT                                      8
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                  0x80
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                     7
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                   0x40
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                      6
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_MASTER_ARBITRATION_WIN_BMSK                     0x20
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_MASTER_ARBITRATION_WIN_SHFT                        5
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_BUS_REQUEST_BMSK                                0x10
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_BUS_REQUEST_SHFT                                   4
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_UNSUPPORTED_COMMAND_BMSK                               0x8
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_UNSUPPORTED_COMMAND_SHFT                                 3
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                      0x4
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                        2
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                      0x2
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                        1
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                     0x1
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_SET_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                       0

#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_ADDR(x)                                       ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x2010)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_OFFS                                          (0x2010)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_RMSK                                              0x3fff
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_ADDR(x),v)
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_RST_COMPLETION_BMSK                           0x2000
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_RST_COMPLETION_SHFT                               13
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_EXPIRY_BMSK                                   0x1000
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_EXPIRY_SHFT                                       12
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_DISCONNECTED_BMSK                          0x800
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_DISCONNECTED_SHFT                             11
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_CONNECTED_BMSK                             0x400
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_CONNECTED_SHFT                                10
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_PERIH_IRQ_LOST_BMSK                                0x200
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_PERIH_IRQ_LOST_SHFT                                    9
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNEXPECTED_SSC_BMSK                                0x100
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNEXPECTED_SSC_SHFT                                    8
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                0x80
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                   7
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                 0x40
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                    6
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_MASTER_ARBITRATION_WIN_BMSK                   0x20
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_MASTER_ARBITRATION_WIN_SHFT                      5
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_BUS_REQUEST_BMSK                              0x10
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_BUS_REQUEST_SHFT                                 4
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNSUPPORTED_COMMAND_BMSK                             0x8
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNSUPPORTED_COMMAND_SHFT                               3
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                    0x4
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                      2
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                    0x2
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                      1
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                   0x1
#define HWIO_SPMI0_SPMI_PROTOCOL_IRQ_EN_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                     0

#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_ADDR(x)                                               ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x3000)
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_OFFS                                                  (0x3000)
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_RMSK                                                       0x3ff
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_TEST_BUS_CTRL_ADDR(x))
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_TEST_BUS_CTRL_ADDR(x), m)
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_TEST_BUS_CTRL_ADDR(x),v)
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_TEST_BUS_CTRL_ADDR(x),m,v,HWIO_SPMI0_SPMI_TEST_BUS_CTRL_IN(x))
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_TEST_BUS_ARB_SEL_BMSK                                      0x3c0
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_TEST_BUS_ARB_SEL_SHFT                                          6
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_TEST_BUS_INT_SEL_BMSK                                       0x3c
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_TEST_BUS_INT_SEL_SHFT                                          2
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_TEST_BUS_SEL_BMSK                                            0x3
#define HWIO_SPMI0_SPMI_TEST_BUS_CTRL_TEST_BUS_SEL_SHFT                                              0

#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_ADDR(x)                                           ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x3004)
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_OFFS                                              (0x3004)
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_RMSK                                                     0x7
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_ADDR(x))
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_ADDR(x), m)
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_ADDR(x),v)
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_ADDR(x),m,v,HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_IN(x))
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_HW_SW_EVENTS_SEL_BMSK                                    0x7
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_CTRL_HW_SW_EVENTS_SEL_SHFT                                      0

#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,j)                              ((base) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0X3008 + (0x4*(j)))
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_OFFS(j)                                   (0X3008 + (0x4*(j)))
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_RMSK                                      0x81818181
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_INI(base,j)                \
                in_dword_masked(HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,j), HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_RMSK)
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_INMI(base,j,mask)        \
                in_dword_masked(HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,j), mask)
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_OUTI(base,j,val)        \
                out_dword(HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,j),val)
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_OUTMI(base,j,mask,val) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,j),mask,val,HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_INI(base,j))
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_D_BMSK                       0x80000000
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_D_SHFT                               31
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_D_BMSK                       0x1000000
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_D_SHFT                              24
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_C_BMSK                         0x800000
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_C_SHFT                               23
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_C_BMSK                         0x10000
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_C_SHFT                              16
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_B_BMSK                           0x8000
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_B_SHFT                               15
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_B_BMSK                           0x100
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_B_SHFT                               8
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_A_BMSK                             0x80
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_A_SHFT                                7
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_A_BMSK                             0x1
#define HWIO_SPMI0_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_A_SHFT                               0

#define HWIO_SPMI0_SPMI_DEBUG_REG_ADDR(x)                                                   ((x) + SPMI0_SPMI_CFG_REG_BASE_OFFS + 0x3028)
#define HWIO_SPMI0_SPMI_DEBUG_REG_OFFS                                                      (0x3028)
#define HWIO_SPMI0_SPMI_DEBUG_REG_RMSK                                                      0xffffffff
#define HWIO_SPMI0_SPMI_DEBUG_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_DEBUG_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_DEBUG_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_DEBUG_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_DEBUG_REG_TEST_BUS_BMSK                                             0xffffffff
#define HWIO_SPMI0_SPMI_DEBUG_REG_TEST_BUS_SHFT                                                      0

/*----------------------------------------------------------------------------
 * MODULE: SPMI0_SPMI_PIC_OWNER
 *--------------------------------------------------------------------------*/

#define SPMI0_SPMI_PIC_OWNER_REG_BASE_OFFS                                  0xc0000

#define HWIO_SPMI0_SPMI_PIC_OWNERm_ACC_STATUSn_ADDR(base,m,n)               ((base) + SPMI0_SPMI_PIC_OWNER_REG_BASE_OFFS + 0X0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_SPMI0_SPMI_PIC_OWNERm_ACC_STATUSn_OFFS(m,n)                    (0X0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_SPMI0_SPMI_PIC_OWNERm_ACC_STATUSn_RMSK                         0xffffffff
#define HWIO_SPMI0_SPMI_PIC_OWNERm_ACC_STATUSn_INI2(base,m,n)                \
                in_dword_masked(HWIO_SPMI0_SPMI_PIC_OWNERm_ACC_STATUSn_ADDR(base,m,n), HWIO_SPMI0_SPMI_PIC_OWNERm_ACC_STATUSn_RMSK)
#define HWIO_SPMI0_SPMI_PIC_OWNERm_ACC_STATUSn_INMI2(base,m,n,mask)        \
                in_dword_masked(HWIO_SPMI0_SPMI_PIC_OWNERm_ACC_STATUSn_ADDR(base,m,n), mask)
#define HWIO_SPMI0_SPMI_PIC_OWNERm_ACC_STATUSn_INT_ACC_STATUS_BMSK          0xffffffff
#define HWIO_SPMI0_SPMI_PIC_OWNERm_ACC_STATUSn_INT_ACC_STATUS_SHFT                   0

/*----------------------------------------------------------------------------
 * MODULE: SPMI0_SPMI_SPMI_GENI_CFG
 *--------------------------------------------------------------------------*/

#define SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS                                   0x02c000

#define HWIO_SPMI0_SPMI_GENI_CLK_CTRL_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x0)
#define HWIO_SPMI0_SPMI_GENI_CLK_CTRL_OFFS                                       (0x0)
#define HWIO_SPMI0_SPMI_GENI_CLK_CTRL_RMSK                                              0x1
#define HWIO_SPMI0_SPMI_GENI_CLK_CTRL_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CLK_CTRL_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CLK_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CLK_CTRL_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CLK_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CLK_CTRL_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CLK_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CLK_CTRL_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CLK_CTRL_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CLK_CTRL_SER_CLK_SEL_BMSK                                  0x1
#define HWIO_SPMI0_SPMI_GENI_CLK_CTRL_SER_CLK_SEL_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_HW_VERSION_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4)
#define HWIO_SPMI0_SPMI_GENI_HW_VERSION_OFFS                                     (0x4)
#define HWIO_SPMI0_SPMI_GENI_HW_VERSION_RMSK                                     0xffffffff
#define HWIO_SPMI0_SPMI_GENI_HW_VERSION_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_HW_VERSION_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_HW_VERSION_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_HW_VERSION_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_HW_VERSION_MAJOR_BMSK                               0xf0000000
#define HWIO_SPMI0_SPMI_GENI_HW_VERSION_MAJOR_SHFT                                       28
#define HWIO_SPMI0_SPMI_GENI_HW_VERSION_MINOR_BMSK                                0xfff0000
#define HWIO_SPMI0_SPMI_GENI_HW_VERSION_MINOR_SHFT                                       16
#define HWIO_SPMI0_SPMI_GENI_HW_VERSION_STEP_BMSK                                    0xffff
#define HWIO_SPMI0_SPMI_GENI_HW_VERSION_STEP_SHFT                                         0

#define HWIO_SPMI0_SPMI_GENI_FW_REVISION_ADDR(x)                                 ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x8)
#define HWIO_SPMI0_SPMI_GENI_FW_REVISION_OFFS                                    (0x8)
#define HWIO_SPMI0_SPMI_GENI_FW_REVISION_RMSK                                        0xffff
#define HWIO_SPMI0_SPMI_GENI_FW_REVISION_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_FW_REVISION_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_FW_REVISION_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_FW_REVISION_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_FW_REVISION_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_FW_REVISION_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_FW_REVISION_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_FW_REVISION_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_FW_REVISION_IN(x))
#define HWIO_SPMI0_SPMI_GENI_FW_REVISION_PROTOCOL_BMSK                               0xffc0
#define HWIO_SPMI0_SPMI_GENI_FW_REVISION_PROTOCOL_SHFT                                    6
#define HWIO_SPMI0_SPMI_GENI_FW_REVISION_VERSION_BMSK                                  0x3f
#define HWIO_SPMI0_SPMI_GENI_FW_REVISION_VERSION_SHFT                                     0

#define HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_ADDR(x)                               ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0xc)
#define HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_OFFS                                  (0xc)
#define HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_RMSK                                      0xffff
#define HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_IN(x))
#define HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_PROTOCOL_BMSK                             0xffc0
#define HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_PROTOCOL_SHFT                                  6
#define HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_VERSION_BMSK                                0x3f
#define HWIO_SPMI0_SPMI_GENI_S_FW_REVISION_VERSION_SHFT                                   0

#define HWIO_SPMI0_SPMI_GENI_FORCE_DEFAULT_REG_ADDR(x)                           ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x10)
#define HWIO_SPMI0_SPMI_GENI_FORCE_DEFAULT_REG_OFFS                              (0x10)
#define HWIO_SPMI0_SPMI_GENI_FORCE_DEFAULT_REG_RMSK                                     0x1
#define HWIO_SPMI0_SPMI_GENI_FORCE_DEFAULT_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_FORCE_DEFAULT_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_FORCE_DEFAULT_REG_FORCE_DEFAULT_BMSK                       0x1
#define HWIO_SPMI0_SPMI_GENI_FORCE_DEFAULT_REG_FORCE_DEFAULT_SHFT                         0

#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_ADDR(x)                                 ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x14)
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_OFFS                                    (0x14)
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_RMSK                                           0x7
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_IN(x))
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_SOE2_EN_BMSK                                   0x4
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_SOE2_EN_SHFT                                     2
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_SOE1_EN_BMSK                                   0x2
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_SOE1_EN_SHFT                                     1
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_SOE0_EN_BMSK                                   0x1
#define HWIO_SPMI0_SPMI_GENI_OUTPUT_CTRL_SOE0_EN_SHFT                                     0

#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x18)
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_OFFS                                       (0x18)
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_RMSK                                            0x37f
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CGC_CTRL_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CGC_CTRL_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CGC_CTRL_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CGC_CTRL_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CGC_CTRL_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_PROG_RAM_SCLK_OFF_BMSK                          0x200
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_PROG_RAM_SCLK_OFF_SHFT                              9
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_PROG_RAM_HCLK_OFF_BMSK                          0x100
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_PROG_RAM_HCLK_OFF_SHFT                              8
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_EXT_CLK_CGC_ON_BMSK                              0x40
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_EXT_CLK_CGC_ON_SHFT                                 6
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_RX_CLK_CGC_ON_BMSK                               0x20
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_RX_CLK_CGC_ON_SHFT                                  5
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_TX_CLK_CGC_ON_BMSK                               0x10
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_TX_CLK_CGC_ON_SHFT                                  4
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_SCLK_CGC_ON_BMSK                                  0x8
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_SCLK_CGC_ON_SHFT                                    3
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_DATA_AHB_CLK_CGC_ON_BMSK                          0x4
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_DATA_AHB_CLK_CGC_ON_SHFT                            2
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_CFG_AHB_WR_CLK_CGC_ON_BMSK                        0x2
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_CFG_AHB_WR_CLK_CGC_ON_SHFT                          1
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_CFG_AHB_CLK_CGC_ON_BMSK                           0x1
#define HWIO_SPMI0_SPMI_GENI_CGC_CTRL_CFG_AHB_CLK_CGC_ON_SHFT                             0

#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x1c)
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_OFFS                                       (0x1c)
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_RMSK                                          0xfff11
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CHAR_CFG_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CHAR_CFG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CHAR_CFG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CHAR_CFG_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CHAR_CFG_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_CHAR_MODE_BMSK                                0xff000
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_CHAR_MODE_SHFT                                     12
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_CHAR_STATUS_BMSK                                0xf00
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_CHAR_STATUS_SHFT                                    8
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_DIRECTION_BMSK                                   0x10
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_DIRECTION_SHFT                                      4
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_ENABLE_BMSK                                       0x1
#define HWIO_SPMI0_SPMI_GENI_CHAR_CFG_ENABLE_SHFT                                         0

#define HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_ADDR(base,n)                            ((base) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0X20 + (0x4*(n)))
#define HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_OFFS(n)                                 (0X20 + (0x4*(n)))
#define HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_RMSK                                        0xffff
#define HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_INI(base,n)                \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_ADDR(base,n), HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_RMSK)
#define HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_ADDR(base,n), mask)
#define HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_ADDR(base,n),val)
#define HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_ADDR(base,n),mask,val,HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_INI(base,n))
#define HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_DIN_ACTUAL_BMSK                             0xff00
#define HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_DIN_ACTUAL_SHFT                                  8
#define HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_BMSK                        0xff
#define HWIO_SPMI0_SPMI_GENI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_CTRL_ADDR(x)                                        ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x28)
#define HWIO_SPMI0_SPMI_GENI_CTRL_OFFS                                           (0x28)
#define HWIO_SPMI0_SPMI_GENI_CTRL_RMSK                                                  0x3
#define HWIO_SPMI0_SPMI_GENI_CTRL_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CTRL_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CTRL_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CTRL_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CTRL_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CTRL_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CTRL_S_GENI_DISABLE_BMSK                                   0x2
#define HWIO_SPMI0_SPMI_GENI_CTRL_S_GENI_DISABLE_SHFT                                     1
#define HWIO_SPMI0_SPMI_GENI_CTRL_M_GENI_DISABLE_BMSK                                   0x1
#define HWIO_SPMI0_SPMI_GENI_CTRL_M_GENI_DISABLE_SHFT                                     0

#define HWIO_SPMI0_SPMI_GENI_STATUS_ADDR(x)                                      ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2c)
#define HWIO_SPMI0_SPMI_GENI_STATUS_OFFS                                         (0x2c)
#define HWIO_SPMI0_SPMI_GENI_STATUS_RMSK                                           0x1fffff
#define HWIO_SPMI0_SPMI_GENI_STATUS_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_STATUS_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_STATUS_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_STATUS_S_GENI_CMD_FSM_STATE_BMSK                      0x1f0000
#define HWIO_SPMI0_SPMI_GENI_STATUS_S_GENI_CMD_FSM_STATE_SHFT                            16
#define HWIO_SPMI0_SPMI_GENI_STATUS_NOT_USED_BITS_3_BMSK                             0xe000
#define HWIO_SPMI0_SPMI_GENI_STATUS_NOT_USED_BITS_3_SHFT                                 13
#define HWIO_SPMI0_SPMI_GENI_STATUS_S_GENI_CMD_ACTIVE_BMSK                           0x1000
#define HWIO_SPMI0_SPMI_GENI_STATUS_S_GENI_CMD_ACTIVE_SHFT                               12
#define HWIO_SPMI0_SPMI_GENI_STATUS_NOT_USED_BITS_2_BMSK                              0xe00
#define HWIO_SPMI0_SPMI_GENI_STATUS_NOT_USED_BITS_2_SHFT                                  9
#define HWIO_SPMI0_SPMI_GENI_STATUS_M_GENI_CMD_FSM_STATE_BMSK                         0x1f0
#define HWIO_SPMI0_SPMI_GENI_STATUS_M_GENI_CMD_FSM_STATE_SHFT                             4
#define HWIO_SPMI0_SPMI_GENI_STATUS_NOT_USED_BITS_1_BMSK                                0xe
#define HWIO_SPMI0_SPMI_GENI_STATUS_NOT_USED_BITS_1_SHFT                                  1
#define HWIO_SPMI0_SPMI_GENI_STATUS_M_GENI_CMD_ACTIVE_BMSK                              0x1
#define HWIO_SPMI0_SPMI_GENI_STATUS_M_GENI_CMD_ACTIVE_SHFT                                0

#define HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_ADDR(x)                               ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x30)
#define HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_OFFS                                  (0x30)
#define HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_RMSK                                        0x1f
#define HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_IN(x))
#define HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_TEST_BUS_SEL_BMSK                           0x1f
#define HWIO_SPMI0_SPMI_GENI_TEST_BUS_CTRL_TEST_BUS_SEL_SHFT                              0

#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_ADDR(x)                                 ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x34)
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_OFFS                                    (0x34)
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_RMSK                                     0x3ffffff
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_IN(x))
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_TX_CLK_DIV_VALUE_BMSK                    0x3ffc000
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_TX_CLK_DIV_VALUE_SHFT                           14
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_RX_CLK_DIV_VALUE_BMSK                       0x3ffc
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_RX_CLK_DIV_VALUE_SHFT                            2
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_TX_SER_CLK_EN_BMSK                             0x2
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_TX_SER_CLK_EN_SHFT                               1
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_RX_SER_CLK_EN_BMSK                             0x1
#define HWIO_SPMI0_SPMI_GENI_SER_CLK_CFG_RX_SER_CLK_EN_SHFT                               0

#define HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_ADDR(x)                            ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x38)
#define HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_OFFS                               (0x38)
#define HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_RMSK                                      0xf
#define HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_IN(x))
#define HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_TX_WATERMARK_BMSK                         0xf
#define HWIO_SPMI0_SPMI_GENI_TX_WATERMARK_REG_TX_WATERMARK_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_ADDR(x)                            ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3c)
#define HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_OFFS                               (0x3c)
#define HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_RMSK                                      0xf
#define HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_IN(x))
#define HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_RX_WATERMARK_BMSK                         0xf
#define HWIO_SPMI0_SPMI_GENI_RX_WATERMARK_REG_RX_WATERMARK_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_STOP_REG_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x40)
#define HWIO_SPMI0_SPMI_GENI_STOP_REG_OFFS                                       (0x40)
#define HWIO_SPMI0_SPMI_GENI_STOP_REG_RMSK                                              0x3
#define HWIO_SPMI0_SPMI_GENI_STOP_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_STOP_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_STOP_REG_S_GENI_STOP_BMSK                                  0x2
#define HWIO_SPMI0_SPMI_GENI_STOP_REG_S_GENI_STOP_SHFT                                    1
#define HWIO_SPMI0_SPMI_GENI_STOP_REG_M_GENI_STOP_BMSK                                  0x1
#define HWIO_SPMI0_SPMI_GENI_STOP_REG_M_GENI_STOP_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_ADDR(x)                                 ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x44)
#define HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_OFFS                                    (0x44)
#define HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_RMSK                                           0x7
#define HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_IN(x))
#define HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_SW_COMP_BMSK                                   0x7
#define HWIO_SPMI0_SPMI_GENI_SW_COMP_REG_SW_COMP_SHFT                                     0

#define HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x)                           ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x48)
#define HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_OFFS                              (0x48)
#define HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_RMSK                                     0x1
#define HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_IN(x))
#define HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_PROG_ROM_EN_BMSK                         0x1
#define HWIO_SPMI0_SPMI_GENI_PROG_ROM_CTRL_REG_PROG_ROM_EN_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x100)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_OFFS                                       (0x100)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_RMSK                                       0x3ffff9ff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG0_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG0_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG0_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG0_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG0_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_GENI_TX_MODE_BMSK                          0x20000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_GENI_TX_MODE_SHFT                                  29
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_COND_COMP_IN_0_SEL_RST_VAL_BMSK            0x1fe00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_COND_COMP_IN_0_SEL_RST_VAL_SHFT                    21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_COND_COMP_IN_VEC_BMSK                        0x1fe000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_COND_COMP_IN_VEC_SHFT                              13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_M_DATA_CNT_INIT_VALUE_INCR_BMSK                0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_M_DATA_CNT_INIT_VALUE_INCR_SHFT                    12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_DATA_CNT_MODE_BMSK                              0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_DATA_CNT_MODE_SHFT                                 11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_M_DATA_CNT_EN_BITS_BMSK                         0x1f8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_M_DATA_CNT_EN_BITS_SHFT                             3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_EXT_SECURITY_EN_BMSK                              0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_EXT_SECURITY_EN_SHFT                                2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_EXT_ARB_EN_BMSK                                   0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_EXT_ARB_EN_SHFT                                     1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_M_PROG_RAM_SEC_WORD_EN_BMSK                       0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG0_M_PROG_RAM_SEC_WORD_EN_SHFT                         0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG1_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x104)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG1_OFFS                                       (0x104)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG1_RMSK                                          0x3ffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG1_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG1_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG1_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG1_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG1_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG1_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG1_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG1_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG1_TX_PARAM_TABLE_VEC_1_BMSK                     0x3fe00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG1_TX_PARAM_TABLE_VEC_1_SHFT                           9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG1_TX_PARAM_TABLE_VEC_0_BMSK                       0x1ff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG1_TX_PARAM_TABLE_VEC_0_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG2_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x108)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG2_OFFS                                       (0x108)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG2_RMSK                                          0x3ffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG2_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG2_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG2_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG2_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG2_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG2_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG2_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG2_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG2_TX_PARAM_TABLE_VEC_3_BMSK                     0x3fe00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG2_TX_PARAM_TABLE_VEC_3_SHFT                           9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG2_TX_PARAM_TABLE_VEC_2_BMSK                       0x1ff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG2_TX_PARAM_TABLE_VEC_2_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG3_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x10c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG3_OFFS                                       (0x10c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG3_RMSK                                          0xfffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG3_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG3_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG3_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG3_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG3_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG3_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG3_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG3_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG3_TX_DATA_TABLE_VEC_1_BMSK                      0xffc00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG3_TX_DATA_TABLE_VEC_1_SHFT                           10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG3_TX_DATA_TABLE_VEC_0_BMSK                        0x3ff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG3_TX_DATA_TABLE_VEC_0_SHFT                            0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG4_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x110)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG4_OFFS                                       (0x110)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG4_RMSK                                          0xfffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG4_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG4_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG4_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG4_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG4_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG4_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG4_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG4_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG4_TX_DATA_TABLE_VEC_3_BMSK                      0xffc00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG4_TX_DATA_TABLE_VEC_3_SHFT                           10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG4_TX_DATA_TABLE_VEC_2_BMSK                        0x3ff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG4_TX_DATA_TABLE_VEC_2_SHFT                            0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x114)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_OFFS                                       (0x114)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_RMSK                                       0x3fdc03ff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG5_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG5_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG5_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG5_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG5_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_DRIVE_DEFAULT_ON_START_EN_BMSK             0x20000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_DRIVE_DEFAULT_ON_START_EN_SHFT                     29
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_BP_MODE_BMSK                            0x10000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_BP_MODE_SHFT                                    28
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_SOE_EDGE_SEL_BMSK                        0x8000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_SOE_EDGE_SEL_SHFT                               27
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_SOUT_EDGE_SEL_BMSK                       0x4000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_SOUT_EDGE_SEL_SHFT                              26
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_DEFAULT_PRIM_SOE_VALUE_BMSK              0x2000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_DEFAULT_PRIM_SOE_VALUE_SHFT                     25
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_DEFAULT_PRIM_SOUT_VALUE_BMSK             0x1000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_DEFAULT_PRIM_SOUT_VALUE_SHFT                    24
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_DEFAULT_SOE_VALUE_BMSK                    0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_DEFAULT_SOE_VALUE_SHFT                          23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_DEFAULT_SOUT_VALUE_BMSK                   0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_DEFAULT_SOUT_VALUE_SHFT                         22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_CONST1_EFF_SIZE_BMSK                      0x1c0000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_CONST1_EFF_SIZE_SHFT                            18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_CONST1_REG_BMSK                              0x3fc
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_CONST1_REG_SHFT                                  2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_PAR_MODE_BMSK                                  0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_PAR_MODE_SHFT                                    1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_PAR_CALC_EN_BMSK                               0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG5_TX_PAR_CALC_EN_SHFT                                 0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x118)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_OFFS                                       (0x118)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_RMSK                                       0xe3fbfd3f
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG6_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG6_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG6_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG6_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG6_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_M_TIME_CNT_FR_DIV_BMSK                     0xc0000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_M_TIME_CNT_FR_DIV_SHFT                             30
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_M_TIME_CNT_EN_FR_SEL_BMSK                  0x20000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_M_TIME_CNT_EN_FR_SEL_SHFT                          29
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_M_GP_CNT_INIT_VAL_BMSK                      0x3e00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_M_GP_CNT_INIT_VAL_SHFT                             21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_M_GP_CNT_DIRECTION_BMSK                      0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_M_GP_CNT_DIRECTION_SHFT                            20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_START_VAL_BMSK                  0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_START_VAL_SHFT                       19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_STOP_DUR_BMSK                   0x30000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_STOP_DUR_SHFT                        16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_EN_BMSK                          0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_EN_SHFT                              15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_LOAD_PAR_EN_BMSK                            0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_LOAD_PAR_EN_SHFT                                14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_PARAM_DUMMY_PAR_EN_BMSK                     0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_PARAM_DUMMY_PAR_EN_SHFT                         13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_PARAM_PAR_EN_BMSK                           0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_PARAM_PAR_EN_SHFT                               12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_FIFO_DUMMY_PAR_EN_BMSK                       0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_FIFO_DUMMY_PAR_EN_SHFT                          11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_FIFO_PAR_EN_BMSK                             0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_TX_FIFO_PAR_EN_SHFT                                10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_CONST_EFF_SIZE_BMSK                         0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_CONST_EFF_SIZE_SHFT                             8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_CONST_REG_BMSK                               0x30
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_CONST_REG_SHFT                                  4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_DEFAULT_PRIM_SOE_VALUE_BMSK                   0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_DEFAULT_PRIM_SOE_VALUE_SHFT                     3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_DEFAULT_PRIM_SOUT_VALUE_BMSK                  0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_DEFAULT_PRIM_SOUT_VALUE_SHFT                    2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_DEFAULT_SOE_VALUE_BMSK                        0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_DEFAULT_SOE_VALUE_SHFT                          1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_DEFAULT_SOUT_VALUE_BMSK                       0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG6_IO2_DEFAULT_SOUT_VALUE_SHFT                         0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x11c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_OFFS                                       (0x11c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_RMSK                                        0x7efffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG7_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG7_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG7_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG7_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG7_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_GENI_RX_MODE_BMSK                           0x4000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_GENI_RX_MODE_SHFT                                  26
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_RX_PAR_MODE_BMSK                            0x2000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_RX_PAR_MODE_SHFT                                   25
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_RX_PAR_CALC_EN_BMSK                         0x1000000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_RX_PAR_CALC_EN_SHFT                                24
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_RX_IO_SIN_SEL_BMSK                           0xe00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_RX_IO_SIN_SEL_SHFT                                 21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_RX_SIN_SEL_BMSK                               0xc0000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_RX_SIN_SEL_SHFT                                    18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_RX_DATA_SRC_BMSK                              0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_RX_DATA_SRC_SHFT                                   17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_S_COND_COMP_IN_0_SEL_RST_VAL_BMSK             0x1fe00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_S_COND_COMP_IN_0_SEL_RST_VAL_SHFT                   9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_S_COND_COMP_IN_VEC_BMSK                         0x1fe
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_S_COND_COMP_IN_VEC_SHFT                             1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_S_DATA_CNT_MODE_BMSK                              0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG7_S_DATA_CNT_MODE_SHFT                                0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x120)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_OFFS                                       (0x120)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_RMSK                                           0xfe7f
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG8_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG8_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG8_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG8_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG8_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_S_GP_CNT_INIT_VAL_BMSK                         0xf800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_S_GP_CNT_INIT_VAL_SHFT                             11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_S_GP_CNT_DIRECTION_BMSK                         0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_S_GP_CNT_DIRECTION_SHFT                            10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_S_DATA_CNT_INIT_VALUE_INCR_BMSK                 0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_S_DATA_CNT_INIT_VALUE_INCR_SHFT                     9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_S_DATA_CNT_EN_BITS_BMSK                          0x7e
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_S_DATA_CNT_EN_BITS_SHFT                             1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_S_PROG_RAM_SEC_WORD_EN_BMSK                       0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG8_S_PROG_RAM_SEC_WORD_EN_SHFT                         0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG9_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x124)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG9_OFFS                                       (0x124)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG9_RMSK                                          0xfffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG9_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG9_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG9_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG9_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG9_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG9_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG9_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG9_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG9_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG9_RX_DATA_TABLE_VEC_1_BMSK                      0xffc00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG9_RX_DATA_TABLE_VEC_1_SHFT                           10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG9_RX_DATA_TABLE_VEC_0_BMSK                        0x3ff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG9_RX_DATA_TABLE_VEC_0_SHFT                            0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG10_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x128)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG10_OFFS                                      (0x128)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG10_RMSK                                         0xfffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG10_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG10_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG10_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG10_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG10_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG10_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG10_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG10_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG10_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG10_RX_DATA_TABLE_VEC_3_BMSK                     0xffc00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG10_RX_DATA_TABLE_VEC_3_SHFT                          10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG10_RX_DATA_TABLE_VEC_2_BMSK                       0x3ff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG10_RX_DATA_TABLE_VEC_2_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x12c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_OFFS                                      (0x12c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG11_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG11_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG11_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG11_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG11_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_11_TX_DURATION_BMSK                    0xc00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_11_TX_DURATION_SHFT                          22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_10_TX_DURATION_BMSK                    0x300000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_10_TX_DURATION_SHFT                          20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_9_TX_DURATION_BMSK                      0xc0000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_9_TX_DURATION_SHFT                           18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_8_TX_DURATION_BMSK                      0x30000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_8_TX_DURATION_SHFT                           16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_7_TX_DURATION_BMSK                       0xc000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_7_TX_DURATION_SHFT                           14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_6_TX_DURATION_BMSK                       0x3000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_6_TX_DURATION_SHFT                           12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_5_TX_DURATION_BMSK                        0xc00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_5_TX_DURATION_SHFT                           10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_4_TX_DURATION_BMSK                        0x300
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_4_TX_DURATION_SHFT                            8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_3_TX_DURATION_BMSK                         0xc0
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_3_TX_DURATION_SHFT                            6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_2_TX_DURATION_BMSK                         0x30
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_2_TX_DURATION_SHFT                            4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_1_TX_DURATION_BMSK                          0xc
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_1_TX_DURATION_SHFT                            2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_0_TX_DURATION_BMSK                          0x3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG11_PRIM_0_TX_DURATION_SHFT                            0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x130)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_OFFS                                      (0x130)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG12_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG12_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG12_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG12_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG12_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_23_TX_DURATION_BMSK                    0xc00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_23_TX_DURATION_SHFT                          22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_22_TX_DURATION_BMSK                    0x300000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_22_TX_DURATION_SHFT                          20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_21_TX_DURATION_BMSK                     0xc0000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_21_TX_DURATION_SHFT                          18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_20_TX_DURATION_BMSK                     0x30000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_20_TX_DURATION_SHFT                          16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_19_TX_DURATION_BMSK                      0xc000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_19_TX_DURATION_SHFT                          14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_18_TX_DURATION_BMSK                      0x3000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_18_TX_DURATION_SHFT                          12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_17_TX_DURATION_BMSK                       0xc00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_17_TX_DURATION_SHFT                          10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_16_TX_DURATION_BMSK                       0x300
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_16_TX_DURATION_SHFT                           8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_15_TX_DURATION_BMSK                        0xc0
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_15_TX_DURATION_SHFT                           6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_14_TX_DURATION_BMSK                        0x30
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_14_TX_DURATION_SHFT                           4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_13_TX_DURATION_BMSK                         0xc
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_13_TX_DURATION_SHFT                           2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_12_TX_DURATION_BMSK                         0x3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG12_PRIM_12_TX_DURATION_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x134)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_OFFS                                      (0x134)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG13_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG13_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG13_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG13_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG13_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_11_RX_DURATION_BMSK                    0xc00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_11_RX_DURATION_SHFT                          22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_10_RX_DURATION_BMSK                    0x300000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_10_RX_DURATION_SHFT                          20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_9_RX_DURATION_BMSK                      0xc0000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_9_RX_DURATION_SHFT                           18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_8_RX_DURATION_BMSK                      0x30000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_8_RX_DURATION_SHFT                           16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_7_RX_DURATION_BMSK                       0xc000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_7_RX_DURATION_SHFT                           14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_6_RX_DURATION_BMSK                       0x3000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_6_RX_DURATION_SHFT                           12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_5_RX_DURATION_BMSK                        0xc00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_5_RX_DURATION_SHFT                           10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_4_RX_DURATION_BMSK                        0x300
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_4_RX_DURATION_SHFT                            8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_3_RX_DURATION_BMSK                         0xc0
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_3_RX_DURATION_SHFT                            6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_2_RX_DURATION_BMSK                         0x30
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_2_RX_DURATION_SHFT                            4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_1_RX_DURATION_BMSK                          0xc
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_1_RX_DURATION_SHFT                            2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_0_RX_DURATION_BMSK                          0x3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG13_PRIM_0_RX_DURATION_SHFT                            0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x138)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_OFFS                                      (0x138)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG14_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG14_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG14_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG14_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG14_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_23_RX_DURATION_BMSK                    0xc00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_23_RX_DURATION_SHFT                          22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_22_RX_DURATION_BMSK                    0x300000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_22_RX_DURATION_SHFT                          20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_21_RX_DURATION_BMSK                     0xc0000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_21_RX_DURATION_SHFT                          18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_20_RX_DURATION_BMSK                     0x30000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_20_RX_DURATION_SHFT                          16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_19_RX_DURATION_BMSK                      0xc000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_19_RX_DURATION_SHFT                          14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_18_RX_DURATION_BMSK                      0x3000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_18_RX_DURATION_SHFT                          12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_17_RX_DURATION_BMSK                       0xc00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_17_RX_DURATION_SHFT                          10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_16_RX_DURATION_BMSK                       0x300
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_16_RX_DURATION_SHFT                           8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_15_RX_DURATION_BMSK                        0xc0
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_15_RX_DURATION_SHFT                           6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_14_RX_DURATION_BMSK                        0x30
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_14_RX_DURATION_SHFT                           4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_13_RX_DURATION_BMSK                         0xc
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_13_RX_DURATION_SHFT                           2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_12_RX_DURATION_BMSK                         0x3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG14_PRIM_12_RX_DURATION_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x13c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_OFFS                                      (0x13c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG15_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG15_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG15_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG15_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG15_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_7_TX_FUNC_SEL_BMSK                     0xe00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_7_TX_FUNC_SEL_SHFT                           21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_6_TX_FUNC_SEL_BMSK                     0x1c0000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_6_TX_FUNC_SEL_SHFT                           18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_5_TX_FUNC_SEL_BMSK                      0x38000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_5_TX_FUNC_SEL_SHFT                           15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_4_TX_FUNC_SEL_BMSK                       0x7000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_4_TX_FUNC_SEL_SHFT                           12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_3_TX_FUNC_SEL_BMSK                        0xe00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_3_TX_FUNC_SEL_SHFT                            9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_2_TX_FUNC_SEL_BMSK                        0x1c0
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_2_TX_FUNC_SEL_SHFT                            6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_1_TX_FUNC_SEL_BMSK                         0x38
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_1_TX_FUNC_SEL_SHFT                            3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_0_TX_FUNC_SEL_BMSK                          0x7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG15_PRIM_0_TX_FUNC_SEL_SHFT                            0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x140)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_OFFS                                      (0x140)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG16_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG16_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG16_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG16_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG16_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_15_TX_FUNC_SEL_BMSK                    0xe00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_15_TX_FUNC_SEL_SHFT                          21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_14_TX_FUNC_SEL_BMSK                    0x1c0000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_14_TX_FUNC_SEL_SHFT                          18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_13_TX_FUNC_SEL_BMSK                     0x38000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_13_TX_FUNC_SEL_SHFT                          15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_12_TX_FUNC_SEL_BMSK                      0x7000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_12_TX_FUNC_SEL_SHFT                          12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_11_TX_FUNC_SEL_BMSK                       0xe00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_11_TX_FUNC_SEL_SHFT                           9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_10_TX_FUNC_SEL_BMSK                       0x1c0
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_10_TX_FUNC_SEL_SHFT                           6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_9_TX_FUNC_SEL_BMSK                         0x38
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_9_TX_FUNC_SEL_SHFT                            3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_8_TX_FUNC_SEL_BMSK                          0x7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG16_PRIM_8_TX_FUNC_SEL_SHFT                            0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x144)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_OFFS                                      (0x144)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG17_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG17_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG17_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG17_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG17_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_23_TX_FUNC_SEL_BMSK                    0xe00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_23_TX_FUNC_SEL_SHFT                          21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_22_TX_FUNC_SEL_BMSK                    0x1c0000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_22_TX_FUNC_SEL_SHFT                          18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_21_TX_FUNC_SEL_BMSK                     0x38000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_21_TX_FUNC_SEL_SHFT                          15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_20_TX_FUNC_SEL_BMSK                      0x7000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_20_TX_FUNC_SEL_SHFT                          12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_19_TX_FUNC_SEL_BMSK                       0xe00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_19_TX_FUNC_SEL_SHFT                           9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_18_TX_FUNC_SEL_BMSK                       0x1c0
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_18_TX_FUNC_SEL_SHFT                           6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_17_TX_FUNC_SEL_BMSK                        0x38
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_17_TX_FUNC_SEL_SHFT                           3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_16_TX_FUNC_SEL_BMSK                         0x7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG17_PRIM_16_TX_FUNC_SEL_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x148)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_OFFS                                      (0x148)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG18_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG18_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG18_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG18_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG18_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_23_TX_PAR_FIRST_BMSK                   0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_23_TX_PAR_FIRST_SHFT                         23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_22_TX_PAR_FIRST_BMSK                   0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_22_TX_PAR_FIRST_SHFT                         22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_21_TX_PAR_FIRST_BMSK                   0x200000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_21_TX_PAR_FIRST_SHFT                         21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_20_TX_PAR_FIRST_BMSK                   0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_20_TX_PAR_FIRST_SHFT                         20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_19_TX_PAR_FIRST_BMSK                    0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_19_TX_PAR_FIRST_SHFT                         19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_18_TX_PAR_FIRST_BMSK                    0x40000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_18_TX_PAR_FIRST_SHFT                         18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_17_TX_PAR_FIRST_BMSK                    0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_17_TX_PAR_FIRST_SHFT                         17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_16_TX_PAR_FIRST_BMSK                    0x10000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_16_TX_PAR_FIRST_SHFT                         16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_15_TX_PAR_FIRST_BMSK                     0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_15_TX_PAR_FIRST_SHFT                         15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_14_TX_PAR_FIRST_BMSK                     0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_14_TX_PAR_FIRST_SHFT                         14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_13_TX_PAR_FIRST_BMSK                     0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_13_TX_PAR_FIRST_SHFT                         13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_12_TX_PAR_FIRST_BMSK                     0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_12_TX_PAR_FIRST_SHFT                         12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_11_TX_PAR_FIRST_BMSK                      0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_11_TX_PAR_FIRST_SHFT                         11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_10_TX_PAR_FIRST_BMSK                      0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_10_TX_PAR_FIRST_SHFT                         10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_9_TX_PAR_FIRST_BMSK                       0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_9_TX_PAR_FIRST_SHFT                           9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_8_TX_PAR_FIRST_BMSK                       0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_8_TX_PAR_FIRST_SHFT                           8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_7_TX_PAR_FIRST_BMSK                        0x80
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_7_TX_PAR_FIRST_SHFT                           7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_6_TX_PAR_FIRST_BMSK                        0x40
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_6_TX_PAR_FIRST_SHFT                           6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_5_TX_PAR_FIRST_BMSK                        0x20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_5_TX_PAR_FIRST_SHFT                           5
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_4_TX_PAR_FIRST_BMSK                        0x10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_4_TX_PAR_FIRST_SHFT                           4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_3_TX_PAR_FIRST_BMSK                         0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_3_TX_PAR_FIRST_SHFT                           3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_2_TX_PAR_FIRST_BMSK                         0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_2_TX_PAR_FIRST_SHFT                           2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_1_TX_PAR_FIRST_BMSK                         0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_1_TX_PAR_FIRST_SHFT                           1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_0_TX_PAR_FIRST_BMSK                         0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG18_PRIM_0_TX_PAR_FIRST_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x14c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_OFFS                                      (0x14c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG19_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG19_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG19_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG19_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG19_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_23_TX_DUMMY_DATA_EN_BMSK               0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_23_TX_DUMMY_DATA_EN_SHFT                     23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_22_TX_DUMMY_DATA_EN_BMSK               0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_22_TX_DUMMY_DATA_EN_SHFT                     22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_21_TX_DUMMY_DATA_EN_BMSK               0x200000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_21_TX_DUMMY_DATA_EN_SHFT                     21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_20_TX_DUMMY_DATA_EN_BMSK               0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_20_TX_DUMMY_DATA_EN_SHFT                     20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_19_TX_DUMMY_DATA_EN_BMSK                0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_19_TX_DUMMY_DATA_EN_SHFT                     19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_18_TX_DUMMY_DATA_EN_BMSK                0x40000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_18_TX_DUMMY_DATA_EN_SHFT                     18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_17_TX_DUMMY_DATA_EN_BMSK                0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_17_TX_DUMMY_DATA_EN_SHFT                     17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_16_TX_DUMMY_DATA_EN_BMSK                0x10000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_16_TX_DUMMY_DATA_EN_SHFT                     16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_15_TX_DUMMY_DATA_EN_BMSK                 0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_15_TX_DUMMY_DATA_EN_SHFT                     15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_14_TX_DUMMY_DATA_EN_BMSK                 0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_14_TX_DUMMY_DATA_EN_SHFT                     14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_13_TX_DUMMY_DATA_EN_BMSK                 0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_13_TX_DUMMY_DATA_EN_SHFT                     13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_12_TX_DUMMY_DATA_EN_BMSK                 0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_12_TX_DUMMY_DATA_EN_SHFT                     12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_11_TX_DUMMY_DATA_EN_BMSK                  0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_11_TX_DUMMY_DATA_EN_SHFT                     11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_10_TX_DUMMY_DATA_EN_BMSK                  0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_10_TX_DUMMY_DATA_EN_SHFT                     10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_9_TX_DUMMY_DATA_EN_BMSK                   0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_9_TX_DUMMY_DATA_EN_SHFT                       9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_8_TX_DUMMY_DATA_EN_BMSK                   0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_8_TX_DUMMY_DATA_EN_SHFT                       8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_7_TX_DUMMY_DATA_EN_BMSK                    0x80
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_7_TX_DUMMY_DATA_EN_SHFT                       7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_6_TX_DUMMY_DATA_EN_BMSK                    0x40
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_6_TX_DUMMY_DATA_EN_SHFT                       6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_5_TX_DUMMY_DATA_EN_BMSK                    0x20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_5_TX_DUMMY_DATA_EN_SHFT                       5
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_4_TX_DUMMY_DATA_EN_BMSK                    0x10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_4_TX_DUMMY_DATA_EN_SHFT                       4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_3_TX_DUMMY_DATA_EN_BMSK                     0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_3_TX_DUMMY_DATA_EN_SHFT                       3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_2_TX_DUMMY_DATA_EN_BMSK                     0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_2_TX_DUMMY_DATA_EN_SHFT                       2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_1_TX_DUMMY_DATA_EN_BMSK                     0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_1_TX_DUMMY_DATA_EN_SHFT                       1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_0_TX_DUMMY_DATA_EN_BMSK                     0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG19_PRIM_0_TX_DUMMY_DATA_EN_SHFT                       0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x150)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_OFFS                                      (0x150)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG20_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG20_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG20_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG20_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG20_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_23_TX_DUMMY_PARAM_EN_BMSK              0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_23_TX_DUMMY_PARAM_EN_SHFT                    23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_22_TX_DUMMY_PARAM_EN_BMSK              0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_22_TX_DUMMY_PARAM_EN_SHFT                    22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_21_TX_DUMMY_PARAM_EN_BMSK              0x200000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_21_TX_DUMMY_PARAM_EN_SHFT                    21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_20_TX_DUMMY_PARAM_EN_BMSK              0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_20_TX_DUMMY_PARAM_EN_SHFT                    20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_19_TX_DUMMY_PARAM_EN_BMSK               0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_19_TX_DUMMY_PARAM_EN_SHFT                    19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_18_TX_DUMMY_PARAM_EN_BMSK               0x40000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_18_TX_DUMMY_PARAM_EN_SHFT                    18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_17_TX_DUMMY_PARAM_EN_BMSK               0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_17_TX_DUMMY_PARAM_EN_SHFT                    17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_16_TX_DUMMY_PARAM_EN_BMSK               0x10000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_16_TX_DUMMY_PARAM_EN_SHFT                    16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_15_TX_DUMMY_PARAM_EN_BMSK                0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_15_TX_DUMMY_PARAM_EN_SHFT                    15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_14_TX_DUMMY_PARAM_EN_BMSK                0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_14_TX_DUMMY_PARAM_EN_SHFT                    14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_13_TX_DUMMY_PARAM_EN_BMSK                0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_13_TX_DUMMY_PARAM_EN_SHFT                    13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_12_TX_DUMMY_PARAM_EN_BMSK                0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_12_TX_DUMMY_PARAM_EN_SHFT                    12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_11_TX_DUMMY_PARAM_EN_BMSK                 0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_11_TX_DUMMY_PARAM_EN_SHFT                    11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_10_TX_DUMMY_PARAM_EN_BMSK                 0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_10_TX_DUMMY_PARAM_EN_SHFT                    10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_9_TX_DUMMY_PARAM_EN_BMSK                  0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_9_TX_DUMMY_PARAM_EN_SHFT                      9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_8_TX_DUMMY_PARAM_EN_BMSK                  0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_8_TX_DUMMY_PARAM_EN_SHFT                      8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_7_TX_DUMMY_PARAM_EN_BMSK                   0x80
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_7_TX_DUMMY_PARAM_EN_SHFT                      7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_6_TX_DUMMY_PARAM_EN_BMSK                   0x40
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_6_TX_DUMMY_PARAM_EN_SHFT                      6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_5_TX_DUMMY_PARAM_EN_BMSK                   0x20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_5_TX_DUMMY_PARAM_EN_SHFT                      5
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_4_TX_DUMMY_PARAM_EN_BMSK                   0x10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_4_TX_DUMMY_PARAM_EN_SHFT                      4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_3_TX_DUMMY_PARAM_EN_BMSK                    0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_3_TX_DUMMY_PARAM_EN_SHFT                      3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_2_TX_DUMMY_PARAM_EN_BMSK                    0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_2_TX_DUMMY_PARAM_EN_SHFT                      2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_1_TX_DUMMY_PARAM_EN_BMSK                    0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_1_TX_DUMMY_PARAM_EN_SHFT                      1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_0_TX_DUMMY_PARAM_EN_BMSK                    0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG20_PRIM_0_TX_DUMMY_PARAM_EN_SHFT                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x154)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_OFFS                                      (0x154)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG21_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG21_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG21_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG21_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG21_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_23_RX_SI_EN_BMSK                       0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_23_RX_SI_EN_SHFT                             23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_22_RX_SI_EN_BMSK                       0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_22_RX_SI_EN_SHFT                             22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_21_RX_SI_EN_BMSK                       0x200000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_21_RX_SI_EN_SHFT                             21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_20_RX_SI_EN_BMSK                       0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_20_RX_SI_EN_SHFT                             20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_19_RX_SI_EN_BMSK                        0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_19_RX_SI_EN_SHFT                             19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_18_RX_SI_EN_BMSK                        0x40000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_18_RX_SI_EN_SHFT                             18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_17_RX_SI_EN_BMSK                        0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_17_RX_SI_EN_SHFT                             17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_16_RX_SI_EN_BMSK                        0x10000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_16_RX_SI_EN_SHFT                             16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_15_RX_SI_EN_BMSK                         0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_15_RX_SI_EN_SHFT                             15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_14_RX_SI_EN_BMSK                         0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_14_RX_SI_EN_SHFT                             14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_13_RX_SI_EN_BMSK                         0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_13_RX_SI_EN_SHFT                             13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_12_RX_SI_EN_BMSK                         0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_12_RX_SI_EN_SHFT                             12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_11_RX_SI_EN_BMSK                          0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_11_RX_SI_EN_SHFT                             11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_10_RX_SI_EN_BMSK                          0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_10_RX_SI_EN_SHFT                             10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_9_RX_SI_EN_BMSK                           0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_9_RX_SI_EN_SHFT                               9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_8_RX_SI_EN_BMSK                           0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_8_RX_SI_EN_SHFT                               8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_7_RX_SI_EN_BMSK                            0x80
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_7_RX_SI_EN_SHFT                               7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_6_RX_SI_EN_BMSK                            0x40
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_6_RX_SI_EN_SHFT                               6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_5_RX_SI_EN_BMSK                            0x20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_5_RX_SI_EN_SHFT                               5
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_4_RX_SI_EN_BMSK                            0x10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_4_RX_SI_EN_SHFT                               4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_3_RX_SI_EN_BMSK                             0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_3_RX_SI_EN_SHFT                               3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_2_RX_SI_EN_BMSK                             0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_2_RX_SI_EN_SHFT                               2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_1_RX_SI_EN_BMSK                             0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_1_RX_SI_EN_SHFT                               1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_0_RX_SI_EN_BMSK                             0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG21_PRIM_0_RX_SI_EN_SHFT                               0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x158)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_OFFS                                      (0x158)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG22_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG22_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG22_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG22_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG22_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_23_RX_PAR_EN_BMSK                      0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_23_RX_PAR_EN_SHFT                            23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_22_RX_PAR_EN_BMSK                      0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_22_RX_PAR_EN_SHFT                            22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_21_RX_PAR_EN_BMSK                      0x200000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_21_RX_PAR_EN_SHFT                            21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_20_RX_PAR_EN_BMSK                      0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_20_RX_PAR_EN_SHFT                            20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_19_RX_PAR_EN_BMSK                       0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_19_RX_PAR_EN_SHFT                            19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_18_RX_PAR_EN_BMSK                       0x40000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_18_RX_PAR_EN_SHFT                            18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_17_RX_PAR_EN_BMSK                       0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_17_RX_PAR_EN_SHFT                            17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_16_RX_PAR_EN_BMSK                       0x10000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_16_RX_PAR_EN_SHFT                            16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_15_RX_PAR_EN_BMSK                        0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_15_RX_PAR_EN_SHFT                            15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_14_RX_PAR_EN_BMSK                        0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_14_RX_PAR_EN_SHFT                            14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_13_RX_PAR_EN_BMSK                        0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_13_RX_PAR_EN_SHFT                            13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_12_RX_PAR_EN_BMSK                        0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_12_RX_PAR_EN_SHFT                            12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_11_RX_PAR_EN_BMSK                         0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_11_RX_PAR_EN_SHFT                            11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_10_RX_PAR_EN_BMSK                         0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_10_RX_PAR_EN_SHFT                            10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_9_RX_PAR_EN_BMSK                          0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_9_RX_PAR_EN_SHFT                              9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_8_RX_PAR_EN_BMSK                          0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_8_RX_PAR_EN_SHFT                              8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_7_RX_PAR_EN_BMSK                           0x80
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_7_RX_PAR_EN_SHFT                              7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_6_RX_PAR_EN_BMSK                           0x40
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_6_RX_PAR_EN_SHFT                              6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_5_RX_PAR_EN_BMSK                           0x20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_5_RX_PAR_EN_SHFT                              5
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_4_RX_PAR_EN_BMSK                           0x10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_4_RX_PAR_EN_SHFT                              4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_3_RX_PAR_EN_BMSK                            0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_3_RX_PAR_EN_SHFT                              3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_2_RX_PAR_EN_BMSK                            0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_2_RX_PAR_EN_SHFT                              2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_1_RX_PAR_EN_BMSK                            0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_1_RX_PAR_EN_SHFT                              1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_0_RX_PAR_EN_BMSK                            0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG22_PRIM_0_RX_PAR_EN_SHFT                              0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x15c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_OFFS                                      (0x15c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG23_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG23_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG23_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG23_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG23_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_23_RX_PAR_FIRST_BMSK                   0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_23_RX_PAR_FIRST_SHFT                         23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_22_RX_PAR_FIRST_BMSK                   0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_22_RX_PAR_FIRST_SHFT                         22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_21_RX_PAR_FIRST_BMSK                   0x200000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_21_RX_PAR_FIRST_SHFT                         21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_20_RX_PAR_FIRST_BMSK                   0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_20_RX_PAR_FIRST_SHFT                         20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_19_RX_PAR_FIRST_BMSK                    0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_19_RX_PAR_FIRST_SHFT                         19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_18_RX_PAR_FIRST_BMSK                    0x40000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_18_RX_PAR_FIRST_SHFT                         18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_17_RX_PAR_FIRST_BMSK                    0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_17_RX_PAR_FIRST_SHFT                         17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_16_RX_PAR_FIRST_BMSK                    0x10000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_16_RX_PAR_FIRST_SHFT                         16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_15_RX_PAR_FIRST_BMSK                     0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_15_RX_PAR_FIRST_SHFT                         15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_14_RX_PAR_FIRST_BMSK                     0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_14_RX_PAR_FIRST_SHFT                         14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_13_RX_PAR_FIRST_BMSK                     0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_13_RX_PAR_FIRST_SHFT                         13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_12_RX_PAR_FIRST_BMSK                     0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_12_RX_PAR_FIRST_SHFT                         12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_11_RX_PAR_FIRST_BMSK                      0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_11_RX_PAR_FIRST_SHFT                         11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_10_RX_PAR_FIRST_BMSK                      0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_10_RX_PAR_FIRST_SHFT                         10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_9_RX_PAR_FIRST_BMSK                       0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_9_RX_PAR_FIRST_SHFT                           9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_8_RX_PAR_FIRST_BMSK                       0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_8_RX_PAR_FIRST_SHFT                           8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_7_RX_PAR_FIRST_BMSK                        0x80
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_7_RX_PAR_FIRST_SHFT                           7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_6_RX_PAR_FIRST_BMSK                        0x40
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_6_RX_PAR_FIRST_SHFT                           6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_5_RX_PAR_FIRST_BMSK                        0x20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_5_RX_PAR_FIRST_SHFT                           5
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_4_RX_PAR_FIRST_BMSK                        0x10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_4_RX_PAR_FIRST_SHFT                           4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_3_RX_PAR_FIRST_BMSK                         0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_3_RX_PAR_FIRST_SHFT                           3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_2_RX_PAR_FIRST_BMSK                         0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_2_RX_PAR_FIRST_SHFT                           2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_1_RX_PAR_FIRST_BMSK                         0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_1_RX_PAR_FIRST_SHFT                           1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_0_RX_PAR_FIRST_BMSK                         0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG23_PRIM_0_RX_PAR_FIRST_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x160)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_OFFS                                      (0x160)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG24_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG24_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG24_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG24_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG24_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_23_ACC_PAR_EN_BMSK                     0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_23_ACC_PAR_EN_SHFT                           23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_22_ACC_PAR_EN_BMSK                     0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_22_ACC_PAR_EN_SHFT                           22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_21_ACC_PAR_EN_BMSK                     0x200000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_21_ACC_PAR_EN_SHFT                           21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_20_ACC_PAR_EN_BMSK                     0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_20_ACC_PAR_EN_SHFT                           20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_19_ACC_PAR_EN_BMSK                      0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_19_ACC_PAR_EN_SHFT                           19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_18_ACC_PAR_EN_BMSK                      0x40000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_18_ACC_PAR_EN_SHFT                           18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_17_ACC_PAR_EN_BMSK                      0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_17_ACC_PAR_EN_SHFT                           17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_16_ACC_PAR_EN_BMSK                      0x10000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_16_ACC_PAR_EN_SHFT                           16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_15_ACC_PAR_EN_BMSK                       0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_15_ACC_PAR_EN_SHFT                           15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_14_ACC_PAR_EN_BMSK                       0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_14_ACC_PAR_EN_SHFT                           14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_13_ACC_PAR_EN_BMSK                       0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_13_ACC_PAR_EN_SHFT                           13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_12_ACC_PAR_EN_BMSK                       0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_12_ACC_PAR_EN_SHFT                           12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_11_ACC_PAR_EN_BMSK                        0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_11_ACC_PAR_EN_SHFT                           11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_10_ACC_PAR_EN_BMSK                        0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_10_ACC_PAR_EN_SHFT                           10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_9_ACC_PAR_EN_BMSK                         0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_9_ACC_PAR_EN_SHFT                             9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_8_ACC_PAR_EN_BMSK                         0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_8_ACC_PAR_EN_SHFT                             8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_7_ACC_PAR_EN_BMSK                          0x80
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_7_ACC_PAR_EN_SHFT                             7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_6_ACC_PAR_EN_BMSK                          0x40
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_6_ACC_PAR_EN_SHFT                             6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_5_ACC_PAR_EN_BMSK                          0x20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_5_ACC_PAR_EN_SHFT                             5
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_4_ACC_PAR_EN_BMSK                          0x10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_4_ACC_PAR_EN_SHFT                             4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_3_ACC_PAR_EN_BMSK                           0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_3_ACC_PAR_EN_SHFT                             3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_2_ACC_PAR_EN_BMSK                           0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_2_ACC_PAR_EN_SHFT                             2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_1_ACC_PAR_EN_BMSK                           0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_1_ACC_PAR_EN_SHFT                             1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_0_ACC_PAR_EN_BMSK                           0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG24_PRIM_0_ACC_PAR_EN_SHFT                             0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x164)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_OFFS                                      (0x164)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG25_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG25_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG25_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG25_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG25_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_11_IO2_FUNC_SEL_BMSK                   0xc00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_11_IO2_FUNC_SEL_SHFT                         22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_10_IO2_FUNC_SEL_BMSK                   0x300000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_10_IO2_FUNC_SEL_SHFT                         20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_9_IO2_FUNC_SEL_BMSK                     0xc0000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_9_IO2_FUNC_SEL_SHFT                          18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_8_IO2_FUNC_SEL_BMSK                     0x30000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_8_IO2_FUNC_SEL_SHFT                          16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_7_IO2_FUNC_SEL_BMSK                      0xc000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_7_IO2_FUNC_SEL_SHFT                          14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_6_IO2_FUNC_SEL_BMSK                      0x3000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_6_IO2_FUNC_SEL_SHFT                          12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_5_IO2_FUNC_SEL_BMSK                       0xc00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_5_IO2_FUNC_SEL_SHFT                          10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_4_IO2_FUNC_SEL_BMSK                       0x300
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_4_IO2_FUNC_SEL_SHFT                           8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_3_IO2_FUNC_SEL_BMSK                        0xc0
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_3_IO2_FUNC_SEL_SHFT                           6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_2_IO2_FUNC_SEL_BMSK                        0x30
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_2_IO2_FUNC_SEL_SHFT                           4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_1_IO2_FUNC_SEL_BMSK                         0xc
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_1_IO2_FUNC_SEL_SHFT                           2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_0_IO2_FUNC_SEL_BMSK                         0x3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG25_PRIM_0_IO2_FUNC_SEL_SHFT                           0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x168)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_OFFS                                      (0x168)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG26_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG26_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG26_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG26_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG26_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_23_IO2_FUNC_SEL_BMSK                   0xc00000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_23_IO2_FUNC_SEL_SHFT                         22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_22_IO2_FUNC_SEL_BMSK                   0x300000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_22_IO2_FUNC_SEL_SHFT                         20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_21_IO2_FUNC_SEL_BMSK                    0xc0000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_21_IO2_FUNC_SEL_SHFT                         18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_20_IO2_FUNC_SEL_BMSK                    0x30000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_20_IO2_FUNC_SEL_SHFT                         16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_19_IO2_FUNC_SEL_BMSK                     0xc000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_19_IO2_FUNC_SEL_SHFT                         14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_18_IO2_FUNC_SEL_BMSK                     0x3000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_18_IO2_FUNC_SEL_SHFT                         12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_17_IO2_FUNC_SEL_BMSK                      0xc00
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_17_IO2_FUNC_SEL_SHFT                         10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_16_IO2_FUNC_SEL_BMSK                      0x300
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_16_IO2_FUNC_SEL_SHFT                          8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_15_IO2_FUNC_SEL_BMSK                       0xc0
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_15_IO2_FUNC_SEL_SHFT                          6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_14_IO2_FUNC_SEL_BMSK                       0x30
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_14_IO2_FUNC_SEL_SHFT                          4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_13_IO2_FUNC_SEL_BMSK                        0xc
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_13_IO2_FUNC_SEL_SHFT                          2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_12_IO2_FUNC_SEL_BMSK                        0x3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG26_PRIM_12_IO2_FUNC_SEL_SHFT                          0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x16c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_OFFS                                      (0x16c)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG27_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG27_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG27_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG27_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG27_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_23_TX_FORCE_DATA_VALUE_BMSK            0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_23_TX_FORCE_DATA_VALUE_SHFT                  23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_22_TX_FORCE_DATA_VALUE_BMSK            0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_22_TX_FORCE_DATA_VALUE_SHFT                  22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_21_TX_FORCE_DATA_VALUE_BMSK            0x200000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_21_TX_FORCE_DATA_VALUE_SHFT                  21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_20_TX_FORCE_DATA_VALUE_BMSK            0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_20_TX_FORCE_DATA_VALUE_SHFT                  20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_19_TX_FORCE_DATA_VALUE_BMSK             0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_19_TX_FORCE_DATA_VALUE_SHFT                  19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_18_TX_FORCE_DATA_VALUE_BMSK             0x40000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_18_TX_FORCE_DATA_VALUE_SHFT                  18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_17_TX_FORCE_DATA_VALUE_BMSK             0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_17_TX_FORCE_DATA_VALUE_SHFT                  17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_16_TX_FORCE_DATA_VALUE_BMSK             0x10000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_16_TX_FORCE_DATA_VALUE_SHFT                  16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_15_TX_FORCE_DATA_VALUE_BMSK              0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_15_TX_FORCE_DATA_VALUE_SHFT                  15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_14_TX_FORCE_DATA_VALUE_BMSK              0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_14_TX_FORCE_DATA_VALUE_SHFT                  14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_13_TX_FORCE_DATA_VALUE_BMSK              0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_13_TX_FORCE_DATA_VALUE_SHFT                  13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_12_TX_FORCE_DATA_VALUE_BMSK              0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_12_TX_FORCE_DATA_VALUE_SHFT                  12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_11_TX_FORCE_DATA_VALUE_BMSK               0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_11_TX_FORCE_DATA_VALUE_SHFT                  11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_10_TX_FORCE_DATA_VALUE_BMSK               0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_10_TX_FORCE_DATA_VALUE_SHFT                  10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_9_TX_FORCE_DATA_VALUE_BMSK                0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_9_TX_FORCE_DATA_VALUE_SHFT                    9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_8_TX_FORCE_DATA_VALUE_BMSK                0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_8_TX_FORCE_DATA_VALUE_SHFT                    8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_7_TX_FORCE_DATA_VALUE_BMSK                 0x80
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_7_TX_FORCE_DATA_VALUE_SHFT                    7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_6_TX_FORCE_DATA_VALUE_BMSK                 0x40
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_6_TX_FORCE_DATA_VALUE_SHFT                    6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_5_TX_FORCE_DATA_VALUE_BMSK                 0x20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_5_TX_FORCE_DATA_VALUE_SHFT                    5
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_4_TX_FORCE_DATA_VALUE_BMSK                 0x10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_4_TX_FORCE_DATA_VALUE_SHFT                    4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_3_TX_FORCE_DATA_VALUE_BMSK                  0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_3_TX_FORCE_DATA_VALUE_SHFT                    3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_2_TX_FORCE_DATA_VALUE_BMSK                  0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_2_TX_FORCE_DATA_VALUE_SHFT                    2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_1_TX_FORCE_DATA_VALUE_BMSK                  0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_1_TX_FORCE_DATA_VALUE_SHFT                    1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_0_TX_FORCE_DATA_VALUE_BMSK                  0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG27_PRIM_0_TX_FORCE_DATA_VALUE_SHFT                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x170)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_OFFS                                      (0x170)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG28_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG28_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG28_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG28_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG28_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_23_RX_FORCE_DATA_VALUE_BMSK            0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_23_RX_FORCE_DATA_VALUE_SHFT                  23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_22_RX_FORCE_DATA_VALUE_BMSK            0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_22_RX_FORCE_DATA_VALUE_SHFT                  22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_21_RX_FORCE_DATA_VALUE_BMSK            0x200000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_21_RX_FORCE_DATA_VALUE_SHFT                  21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_20_RX_FORCE_DATA_VALUE_BMSK            0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_20_RX_FORCE_DATA_VALUE_SHFT                  20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_19_RX_FORCE_DATA_VALUE_BMSK             0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_19_RX_FORCE_DATA_VALUE_SHFT                  19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_18_RX_FORCE_DATA_VALUE_BMSK             0x40000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_18_RX_FORCE_DATA_VALUE_SHFT                  18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_17_RX_FORCE_DATA_VALUE_BMSK             0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_17_RX_FORCE_DATA_VALUE_SHFT                  17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_16_RX_FORCE_DATA_VALUE_BMSK             0x10000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_16_RX_FORCE_DATA_VALUE_SHFT                  16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_15_RX_FORCE_DATA_VALUE_BMSK              0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_15_RX_FORCE_DATA_VALUE_SHFT                  15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_14_RX_FORCE_DATA_VALUE_BMSK              0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_14_RX_FORCE_DATA_VALUE_SHFT                  14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_13_RX_FORCE_DATA_VALUE_BMSK              0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_13_RX_FORCE_DATA_VALUE_SHFT                  13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_12_RX_FORCE_DATA_VALUE_BMSK              0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_12_RX_FORCE_DATA_VALUE_SHFT                  12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_11_RX_FORCE_DATA_VALUE_BMSK               0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_11_RX_FORCE_DATA_VALUE_SHFT                  11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_10_RX_FORCE_DATA_VALUE_BMSK               0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_10_RX_FORCE_DATA_VALUE_SHFT                  10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_9_RX_FORCE_DATA_VALUE_BMSK                0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_9_RX_FORCE_DATA_VALUE_SHFT                    9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_8_RX_FORCE_DATA_VALUE_BMSK                0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_8_RX_FORCE_DATA_VALUE_SHFT                    8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_7_RX_FORCE_DATA_VALUE_BMSK                 0x80
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_7_RX_FORCE_DATA_VALUE_SHFT                    7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_6_RX_FORCE_DATA_VALUE_BMSK                 0x40
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_6_RX_FORCE_DATA_VALUE_SHFT                    6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_5_RX_FORCE_DATA_VALUE_BMSK                 0x20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_5_RX_FORCE_DATA_VALUE_SHFT                    5
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_4_RX_FORCE_DATA_VALUE_BMSK                 0x10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_4_RX_FORCE_DATA_VALUE_SHFT                    4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_3_RX_FORCE_DATA_VALUE_BMSK                  0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_3_RX_FORCE_DATA_VALUE_SHFT                    3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_2_RX_FORCE_DATA_VALUE_BMSK                  0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_2_RX_FORCE_DATA_VALUE_SHFT                    2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_1_RX_FORCE_DATA_VALUE_BMSK                  0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_1_RX_FORCE_DATA_VALUE_SHFT                    1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_0_RX_FORCE_DATA_VALUE_BMSK                  0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG28_PRIM_0_RX_FORCE_DATA_VALUE_SHFT                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x174)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_OFFS                                      (0x174)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG29_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG29_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG29_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG29_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG29_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_23_TX_TIME_COUNTER_EN_BMSK             0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_23_TX_TIME_COUNTER_EN_SHFT                   23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_22_TX_TIME_COUNTER_EN_BMSK             0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_22_TX_TIME_COUNTER_EN_SHFT                   22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_21_TX_TIME_COUNTER_EN_BMSK             0x200000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_21_TX_TIME_COUNTER_EN_SHFT                   21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_20_TX_TIME_COUNTER_EN_BMSK             0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_20_TX_TIME_COUNTER_EN_SHFT                   20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_19_TX_TIME_COUNTER_EN_BMSK              0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_19_TX_TIME_COUNTER_EN_SHFT                   19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_18_TX_TIME_COUNTER_EN_BMSK              0x40000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_18_TX_TIME_COUNTER_EN_SHFT                   18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_17_TX_TIME_COUNTER_EN_BMSK              0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_17_TX_TIME_COUNTER_EN_SHFT                   17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_16_TX_TIME_COUNTER_EN_BMSK              0x10000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_16_TX_TIME_COUNTER_EN_SHFT                   16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_15_TX_TIME_COUNTER_EN_BMSK               0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_15_TX_TIME_COUNTER_EN_SHFT                   15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_14_TX_TIME_COUNTER_EN_BMSK               0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_14_TX_TIME_COUNTER_EN_SHFT                   14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_13_TX_TIME_COUNTER_EN_BMSK               0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_13_TX_TIME_COUNTER_EN_SHFT                   13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_12_TX_TIME_COUNTER_EN_BMSK               0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_12_TX_TIME_COUNTER_EN_SHFT                   12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_11_TX_TIME_COUNTER_EN_BMSK                0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_11_TX_TIME_COUNTER_EN_SHFT                   11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_10_TX_TIME_COUNTER_EN_BMSK                0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_10_TX_TIME_COUNTER_EN_SHFT                   10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_9_TX_TIME_COUNTER_EN_BMSK                 0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_9_TX_TIME_COUNTER_EN_SHFT                     9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_8_TX_TIME_COUNTER_EN_BMSK                 0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_8_TX_TIME_COUNTER_EN_SHFT                     8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_7_TX_TIME_COUNTER_EN_BMSK                  0x80
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_7_TX_TIME_COUNTER_EN_SHFT                     7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_6_TX_TIME_COUNTER_EN_BMSK                  0x40
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_6_TX_TIME_COUNTER_EN_SHFT                     6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_5_TX_TIME_COUNTER_EN_BMSK                  0x20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_5_TX_TIME_COUNTER_EN_SHFT                     5
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_4_TX_TIME_COUNTER_EN_BMSK                  0x10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_4_TX_TIME_COUNTER_EN_SHFT                     4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_3_TX_TIME_COUNTER_EN_BMSK                   0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_3_TX_TIME_COUNTER_EN_SHFT                     3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_2_TX_TIME_COUNTER_EN_BMSK                   0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_2_TX_TIME_COUNTER_EN_SHFT                     2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_1_TX_TIME_COUNTER_EN_BMSK                   0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_1_TX_TIME_COUNTER_EN_SHFT                     1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_0_TX_TIME_COUNTER_EN_BMSK                   0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG29_PRIM_0_TX_TIME_COUNTER_EN_SHFT                     0

#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x178)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_OFFS                                      (0x178)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_RMSK                                        0xffffff
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG30_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_REG30_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_OUT(x, v)            \
                out_dword(HWIO_SPMI0_SPMI_GENI_CFG_REG30_ADDR(x),v)
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI0_SPMI_GENI_CFG_REG30_ADDR(x),m,v,HWIO_SPMI0_SPMI_GENI_CFG_REG30_IN(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_23_RX_TIME_COUNTER_EN_BMSK             0x800000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_23_RX_TIME_COUNTER_EN_SHFT                   23
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_22_RX_TIME_COUNTER_EN_BMSK             0x400000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_22_RX_TIME_COUNTER_EN_SHFT                   22
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_21_RX_TIME_COUNTER_EN_BMSK             0x200000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_21_RX_TIME_COUNTER_EN_SHFT                   21
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_20_RX_TIME_COUNTER_EN_BMSK             0x100000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_20_RX_TIME_COUNTER_EN_SHFT                   20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_19_RX_TIME_COUNTER_EN_BMSK              0x80000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_19_RX_TIME_COUNTER_EN_SHFT                   19
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_18_RX_TIME_COUNTER_EN_BMSK              0x40000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_18_RX_TIME_COUNTER_EN_SHFT                   18
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_17_RX_TIME_COUNTER_EN_BMSK              0x20000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_17_RX_TIME_COUNTER_EN_SHFT                   17
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_16_RX_TIME_COUNTER_EN_BMSK              0x10000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_16_RX_TIME_COUNTER_EN_SHFT                   16
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_15_RX_TIME_COUNTER_EN_BMSK               0x8000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_15_RX_TIME_COUNTER_EN_SHFT                   15
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_14_RX_TIME_COUNTER_EN_BMSK               0x4000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_14_RX_TIME_COUNTER_EN_SHFT                   14
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_13_RX_TIME_COUNTER_EN_BMSK               0x2000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_13_RX_TIME_COUNTER_EN_SHFT                   13
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_12_RX_TIME_COUNTER_EN_BMSK               0x1000
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_12_RX_TIME_COUNTER_EN_SHFT                   12
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_11_RX_TIME_COUNTER_EN_BMSK                0x800
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_11_RX_TIME_COUNTER_EN_SHFT                   11
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_10_RX_TIME_COUNTER_EN_BMSK                0x400
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_10_RX_TIME_COUNTER_EN_SHFT                   10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_9_RX_TIME_COUNTER_EN_BMSK                 0x200
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_9_RX_TIME_COUNTER_EN_SHFT                     9
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_8_RX_TIME_COUNTER_EN_BMSK                 0x100
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_8_RX_TIME_COUNTER_EN_SHFT                     8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_7_RX_TIME_COUNTER_EN_BMSK                  0x80
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_7_RX_TIME_COUNTER_EN_SHFT                     7
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_6_RX_TIME_COUNTER_EN_BMSK                  0x40
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_6_RX_TIME_COUNTER_EN_SHFT                     6
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_5_RX_TIME_COUNTER_EN_BMSK                  0x20
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_5_RX_TIME_COUNTER_EN_SHFT                     5
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_4_RX_TIME_COUNTER_EN_BMSK                  0x10
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_4_RX_TIME_COUNTER_EN_SHFT                     4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_3_RX_TIME_COUNTER_EN_BMSK                   0x8
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_3_RX_TIME_COUNTER_EN_SHFT                     3
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_2_RX_TIME_COUNTER_EN_BMSK                   0x4
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_2_RX_TIME_COUNTER_EN_SHFT                     2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_1_RX_TIME_COUNTER_EN_BMSK                   0x2
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_1_RX_TIME_COUNTER_EN_SHFT                     1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_0_RX_TIME_COUNTER_EN_BMSK                   0x1
#define HWIO_SPMI0_SPMI_GENI_CFG_REG30_PRIM_0_RX_TIME_COUNTER_EN_SHFT                     0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM0_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x200)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM0_OFFS                                       (0x200)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM0_RMSK                                         0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM0_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM0_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM0_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM0_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM0_IMAGE_0_BMSK                                 0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM0_IMAGE_0_SHFT                                        0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM1_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x204)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM1_OFFS                                       (0x204)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM1_RMSK                                         0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM1_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM1_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM1_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM1_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM1_IMAGE_1_BMSK                                 0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM1_IMAGE_1_SHFT                                        0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM2_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x208)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM2_OFFS                                       (0x208)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM2_RMSK                                         0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM2_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM2_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM2_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM2_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM2_IMAGE_2_BMSK                                 0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM2_IMAGE_2_SHFT                                        0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM3_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x20c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM3_OFFS                                       (0x20c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM3_RMSK                                         0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM3_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM3_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM3_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM3_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM3_IMAGE_3_BMSK                                 0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM3_IMAGE_3_SHFT                                        0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM4_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x210)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM4_OFFS                                       (0x210)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM4_RMSK                                         0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM4_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM4_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM4_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM4_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM4_IMAGE_4_BMSK                                 0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM4_IMAGE_4_SHFT                                        0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM5_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x214)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM5_OFFS                                       (0x214)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM5_RMSK                                         0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM5_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM5_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM5_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM5_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM5_IMAGE_5_BMSK                                 0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM5_IMAGE_5_SHFT                                        0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM6_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x218)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM6_OFFS                                       (0x218)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM6_RMSK                                         0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM6_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM6_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM6_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM6_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM6_IMAGE_6_BMSK                                 0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM6_IMAGE_6_SHFT                                        0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM7_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x21c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM7_OFFS                                       (0x21c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM7_RMSK                                         0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM7_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM7_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM7_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM7_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM7_IMAGE_7_BMSK                                 0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM7_IMAGE_7_SHFT                                        0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM8_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x220)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM8_OFFS                                       (0x220)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM8_RMSK                                         0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM8_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM8_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM8_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM8_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM8_IMAGE_8_BMSK                                 0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM8_IMAGE_8_SHFT                                        0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM9_ADDR(x)                                    ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x224)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM9_OFFS                                       (0x224)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM9_RMSK                                         0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM9_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM9_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM9_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM9_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM9_IMAGE_9_BMSK                                 0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM9_IMAGE_9_SHFT                                        0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM10_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x228)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM10_OFFS                                      (0x228)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM10_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM10_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM10_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM10_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM10_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM10_IMAGE_10_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM10_IMAGE_10_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM11_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x22c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM11_OFFS                                      (0x22c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM11_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM11_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM11_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM11_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM11_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM11_IMAGE_11_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM11_IMAGE_11_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM12_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x230)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM12_OFFS                                      (0x230)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM12_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM12_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM12_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM12_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM12_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM12_IMAGE_12_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM12_IMAGE_12_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM13_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x234)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM13_OFFS                                      (0x234)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM13_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM13_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM13_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM13_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM13_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM13_IMAGE_13_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM13_IMAGE_13_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM14_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x238)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM14_OFFS                                      (0x238)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM14_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM14_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM14_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM14_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM14_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM14_IMAGE_14_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM14_IMAGE_14_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM15_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x23c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM15_OFFS                                      (0x23c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM15_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM15_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM15_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM15_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM15_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM15_IMAGE_15_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM15_IMAGE_15_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM16_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x240)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM16_OFFS                                      (0x240)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM16_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM16_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM16_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM16_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM16_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM16_IMAGE_16_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM16_IMAGE_16_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM17_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x244)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM17_OFFS                                      (0x244)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM17_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM17_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM17_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM17_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM17_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM17_IMAGE_17_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM17_IMAGE_17_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM18_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x248)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM18_OFFS                                      (0x248)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM18_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM18_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM18_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM18_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM18_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM18_IMAGE_18_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM18_IMAGE_18_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM19_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x24c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM19_OFFS                                      (0x24c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM19_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM19_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM19_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM19_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM19_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM19_IMAGE_19_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM19_IMAGE_19_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM20_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x250)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM20_OFFS                                      (0x250)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM20_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM20_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM20_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM20_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM20_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM20_IMAGE_20_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM20_IMAGE_20_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM21_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x254)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM21_OFFS                                      (0x254)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM21_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM21_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM21_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM21_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM21_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM21_IMAGE_21_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM21_IMAGE_21_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM22_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x258)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM22_OFFS                                      (0x258)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM22_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM22_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM22_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM22_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM22_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM22_IMAGE_22_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM22_IMAGE_22_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM23_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x25c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM23_OFFS                                      (0x25c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM23_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM23_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM23_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM23_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM23_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM23_IMAGE_23_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM23_IMAGE_23_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM24_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x260)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM24_OFFS                                      (0x260)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM24_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM24_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM24_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM24_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM24_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM24_IMAGE_24_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM24_IMAGE_24_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM25_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x264)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM25_OFFS                                      (0x264)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM25_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM25_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM25_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM25_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM25_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM25_IMAGE_25_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM25_IMAGE_25_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM26_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x268)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM26_OFFS                                      (0x268)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM26_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM26_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM26_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM26_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM26_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM26_IMAGE_26_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM26_IMAGE_26_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM27_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x26c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM27_OFFS                                      (0x26c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM27_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM27_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM27_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM27_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM27_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM27_IMAGE_27_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM27_IMAGE_27_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM28_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x270)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM28_OFFS                                      (0x270)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM28_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM28_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM28_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM28_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM28_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM28_IMAGE_28_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM28_IMAGE_28_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM29_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x274)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM29_OFFS                                      (0x274)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM29_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM29_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM29_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM29_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM29_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM29_IMAGE_29_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM29_IMAGE_29_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM30_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x278)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM30_OFFS                                      (0x278)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM30_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM30_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM30_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM30_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM30_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM30_IMAGE_30_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM30_IMAGE_30_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM31_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x27c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM31_OFFS                                      (0x27c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM31_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM31_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM31_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM31_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM31_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM31_IMAGE_31_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM31_IMAGE_31_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM32_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x280)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM32_OFFS                                      (0x280)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM32_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM32_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM32_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM32_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM32_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM32_IMAGE_32_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM32_IMAGE_32_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM33_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x284)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM33_OFFS                                      (0x284)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM33_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM33_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM33_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM33_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM33_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM33_IMAGE_33_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM33_IMAGE_33_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM34_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x288)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM34_OFFS                                      (0x288)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM34_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM34_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM34_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM34_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM34_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM34_IMAGE_34_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM34_IMAGE_34_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM35_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x28c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM35_OFFS                                      (0x28c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM35_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM35_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM35_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM35_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM35_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM35_IMAGE_35_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM35_IMAGE_35_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM36_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x290)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM36_OFFS                                      (0x290)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM36_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM36_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM36_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM36_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM36_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM36_IMAGE_36_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM36_IMAGE_36_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM37_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x294)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM37_OFFS                                      (0x294)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM37_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM37_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM37_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM37_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM37_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM37_IMAGE_37_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM37_IMAGE_37_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM38_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x298)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM38_OFFS                                      (0x298)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM38_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM38_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM38_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM38_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM38_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM38_IMAGE_38_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM38_IMAGE_38_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM39_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x29c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM39_OFFS                                      (0x29c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM39_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM39_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM39_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM39_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM39_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM39_IMAGE_39_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM39_IMAGE_39_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM40_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2a0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM40_OFFS                                      (0x2a0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM40_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM40_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM40_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM40_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM40_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM40_IMAGE_40_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM40_IMAGE_40_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM41_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2a4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM41_OFFS                                      (0x2a4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM41_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM41_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM41_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM41_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM41_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM41_IMAGE_41_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM41_IMAGE_41_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM42_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2a8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM42_OFFS                                      (0x2a8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM42_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM42_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM42_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM42_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM42_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM42_IMAGE_42_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM42_IMAGE_42_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM43_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2ac)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM43_OFFS                                      (0x2ac)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM43_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM43_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM43_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM43_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM43_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM43_IMAGE_43_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM43_IMAGE_43_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM44_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2b0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM44_OFFS                                      (0x2b0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM44_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM44_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM44_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM44_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM44_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM44_IMAGE_44_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM44_IMAGE_44_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM45_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2b4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM45_OFFS                                      (0x2b4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM45_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM45_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM45_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM45_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM45_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM45_IMAGE_45_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM45_IMAGE_45_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM46_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2b8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM46_OFFS                                      (0x2b8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM46_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM46_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM46_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM46_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM46_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM46_IMAGE_46_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM46_IMAGE_46_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM47_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2bc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM47_OFFS                                      (0x2bc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM47_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM47_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM47_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM47_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM47_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM47_IMAGE_47_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM47_IMAGE_47_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM48_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2c0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM48_OFFS                                      (0x2c0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM48_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM48_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM48_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM48_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM48_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM48_IMAGE_48_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM48_IMAGE_48_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM49_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2c4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM49_OFFS                                      (0x2c4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM49_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM49_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM49_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM49_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM49_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM49_IMAGE_49_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM49_IMAGE_49_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM50_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2c8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM50_OFFS                                      (0x2c8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM50_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM50_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM50_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM50_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM50_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM50_IMAGE_50_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM50_IMAGE_50_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM51_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2cc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM51_OFFS                                      (0x2cc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM51_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM51_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM51_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM51_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM51_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM51_IMAGE_51_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM51_IMAGE_51_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM52_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2d0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM52_OFFS                                      (0x2d0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM52_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM52_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM52_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM52_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM52_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM52_IMAGE_52_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM52_IMAGE_52_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM53_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2d4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM53_OFFS                                      (0x2d4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM53_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM53_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM53_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM53_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM53_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM53_IMAGE_53_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM53_IMAGE_53_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM54_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2d8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM54_OFFS                                      (0x2d8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM54_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM54_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM54_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM54_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM54_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM54_IMAGE_54_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM54_IMAGE_54_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM55_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2dc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM55_OFFS                                      (0x2dc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM55_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM55_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM55_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM55_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM55_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM55_IMAGE_55_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM55_IMAGE_55_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM56_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2e0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM56_OFFS                                      (0x2e0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM56_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM56_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM56_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM56_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM56_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM56_IMAGE_56_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM56_IMAGE_56_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM57_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2e4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM57_OFFS                                      (0x2e4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM57_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM57_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM57_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM57_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM57_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM57_IMAGE_57_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM57_IMAGE_57_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM58_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2e8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM58_OFFS                                      (0x2e8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM58_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM58_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM58_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM58_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM58_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM58_IMAGE_58_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM58_IMAGE_58_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM59_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2ec)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM59_OFFS                                      (0x2ec)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM59_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM59_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM59_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM59_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM59_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM59_IMAGE_59_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM59_IMAGE_59_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM60_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2f0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM60_OFFS                                      (0x2f0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM60_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM60_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM60_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM60_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM60_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM60_IMAGE_60_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM60_IMAGE_60_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM61_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2f4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM61_OFFS                                      (0x2f4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM61_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM61_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM61_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM61_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM61_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM61_IMAGE_61_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM61_IMAGE_61_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM62_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2f8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM62_OFFS                                      (0x2f8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM62_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM62_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM62_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM62_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM62_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM62_IMAGE_62_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM62_IMAGE_62_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM63_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2fc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM63_OFFS                                      (0x2fc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM63_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM63_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM63_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM63_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM63_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM63_IMAGE_63_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM63_IMAGE_63_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM64_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x300)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM64_OFFS                                      (0x300)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM64_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM64_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM64_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM64_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM64_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM64_IMAGE_64_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM64_IMAGE_64_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM65_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x304)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM65_OFFS                                      (0x304)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM65_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM65_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM65_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM65_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM65_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM65_IMAGE_65_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM65_IMAGE_65_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM66_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x308)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM66_OFFS                                      (0x308)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM66_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM66_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM66_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM66_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM66_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM66_IMAGE_66_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM66_IMAGE_66_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM67_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x30c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM67_OFFS                                      (0x30c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM67_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM67_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM67_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM67_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM67_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM67_IMAGE_67_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM67_IMAGE_67_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM68_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x310)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM68_OFFS                                      (0x310)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM68_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM68_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM68_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM68_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM68_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM68_IMAGE_68_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM68_IMAGE_68_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM69_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x314)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM69_OFFS                                      (0x314)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM69_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM69_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM69_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM69_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM69_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM69_IMAGE_69_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM69_IMAGE_69_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM70_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x318)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM70_OFFS                                      (0x318)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM70_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM70_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM70_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM70_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM70_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM70_IMAGE_70_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM70_IMAGE_70_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM71_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x31c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM71_OFFS                                      (0x31c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM71_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM71_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM71_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM71_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM71_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM71_IMAGE_71_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM71_IMAGE_71_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM72_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x320)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM72_OFFS                                      (0x320)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM72_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM72_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM72_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM72_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM72_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM72_IMAGE_72_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM72_IMAGE_72_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM73_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x324)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM73_OFFS                                      (0x324)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM73_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM73_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM73_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM73_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM73_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM73_IMAGE_73_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM73_IMAGE_73_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM74_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x328)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM74_OFFS                                      (0x328)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM74_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM74_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM74_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM74_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM74_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM74_IMAGE_74_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM74_IMAGE_74_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM75_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x32c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM75_OFFS                                      (0x32c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM75_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM75_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM75_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM75_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM75_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM75_IMAGE_75_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM75_IMAGE_75_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM76_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x330)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM76_OFFS                                      (0x330)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM76_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM76_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM76_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM76_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM76_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM76_IMAGE_76_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM76_IMAGE_76_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM77_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x334)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM77_OFFS                                      (0x334)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM77_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM77_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM77_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM77_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM77_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM77_IMAGE_77_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM77_IMAGE_77_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM78_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x338)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM78_OFFS                                      (0x338)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM78_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM78_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM78_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM78_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM78_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM78_IMAGE_78_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM78_IMAGE_78_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM79_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x33c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM79_OFFS                                      (0x33c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM79_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM79_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM79_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM79_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM79_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM79_IMAGE_79_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM79_IMAGE_79_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM80_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x340)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM80_OFFS                                      (0x340)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM80_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM80_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM80_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM80_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM80_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM80_IMAGE_80_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM80_IMAGE_80_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM81_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x344)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM81_OFFS                                      (0x344)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM81_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM81_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM81_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM81_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM81_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM81_IMAGE_81_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM81_IMAGE_81_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM82_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x348)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM82_OFFS                                      (0x348)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM82_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM82_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM82_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM82_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM82_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM82_IMAGE_82_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM82_IMAGE_82_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM83_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x34c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM83_OFFS                                      (0x34c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM83_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM83_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM83_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM83_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM83_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM83_IMAGE_83_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM83_IMAGE_83_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM84_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x350)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM84_OFFS                                      (0x350)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM84_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM84_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM84_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM84_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM84_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM84_IMAGE_84_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM84_IMAGE_84_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM85_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x354)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM85_OFFS                                      (0x354)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM85_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM85_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM85_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM85_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM85_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM85_IMAGE_85_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM85_IMAGE_85_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM86_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x358)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM86_OFFS                                      (0x358)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM86_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM86_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM86_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM86_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM86_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM86_IMAGE_86_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM86_IMAGE_86_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM87_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x35c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM87_OFFS                                      (0x35c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM87_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM87_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM87_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM87_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM87_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM87_IMAGE_87_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM87_IMAGE_87_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM88_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x360)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM88_OFFS                                      (0x360)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM88_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM88_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM88_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM88_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM88_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM88_IMAGE_88_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM88_IMAGE_88_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM89_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x364)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM89_OFFS                                      (0x364)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM89_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM89_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM89_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM89_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM89_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM89_IMAGE_89_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM89_IMAGE_89_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM90_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x368)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM90_OFFS                                      (0x368)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM90_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM90_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM90_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM90_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM90_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM90_IMAGE_90_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM90_IMAGE_90_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM91_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x36c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM91_OFFS                                      (0x36c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM91_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM91_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM91_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM91_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM91_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM91_IMAGE_91_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM91_IMAGE_91_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM92_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x370)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM92_OFFS                                      (0x370)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM92_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM92_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM92_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM92_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM92_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM92_IMAGE_92_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM92_IMAGE_92_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM93_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x374)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM93_OFFS                                      (0x374)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM93_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM93_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM93_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM93_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM93_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM93_IMAGE_93_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM93_IMAGE_93_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM94_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x378)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM94_OFFS                                      (0x378)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM94_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM94_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM94_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM94_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM94_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM94_IMAGE_94_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM94_IMAGE_94_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM95_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x37c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM95_OFFS                                      (0x37c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM95_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM95_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM95_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM95_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM95_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM95_IMAGE_95_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM95_IMAGE_95_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM96_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x380)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM96_OFFS                                      (0x380)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM96_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM96_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM96_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM96_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM96_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM96_IMAGE_96_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM96_IMAGE_96_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM97_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x384)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM97_OFFS                                      (0x384)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM97_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM97_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM97_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM97_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM97_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM97_IMAGE_97_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM97_IMAGE_97_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM98_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x388)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM98_OFFS                                      (0x388)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM98_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM98_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM98_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM98_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM98_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM98_IMAGE_98_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM98_IMAGE_98_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM99_ADDR(x)                                   ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x38c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM99_OFFS                                      (0x38c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM99_RMSK                                        0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM99_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM99_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM99_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM99_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM99_IMAGE_99_BMSK                               0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM99_IMAGE_99_SHFT                                      0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM100_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x390)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM100_OFFS                                     (0x390)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM100_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM100_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM100_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM100_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM100_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM100_IMAGE_100_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM100_IMAGE_100_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM101_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x394)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM101_OFFS                                     (0x394)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM101_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM101_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM101_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM101_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM101_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM101_IMAGE_101_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM101_IMAGE_101_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM102_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x398)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM102_OFFS                                     (0x398)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM102_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM102_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM102_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM102_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM102_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM102_IMAGE_102_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM102_IMAGE_102_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM103_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x39c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM103_OFFS                                     (0x39c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM103_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM103_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM103_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM103_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM103_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM103_IMAGE_103_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM103_IMAGE_103_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM104_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3a0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM104_OFFS                                     (0x3a0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM104_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM104_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM104_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM104_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM104_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM104_IMAGE_104_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM104_IMAGE_104_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM105_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3a4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM105_OFFS                                     (0x3a4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM105_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM105_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM105_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM105_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM105_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM105_IMAGE_105_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM105_IMAGE_105_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM106_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3a8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM106_OFFS                                     (0x3a8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM106_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM106_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM106_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM106_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM106_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM106_IMAGE_106_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM106_IMAGE_106_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM107_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3ac)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM107_OFFS                                     (0x3ac)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM107_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM107_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM107_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM107_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM107_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM107_IMAGE_107_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM107_IMAGE_107_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM108_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3b0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM108_OFFS                                     (0x3b0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM108_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM108_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM108_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM108_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM108_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM108_IMAGE_108_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM108_IMAGE_108_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM109_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3b4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM109_OFFS                                     (0x3b4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM109_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM109_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM109_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM109_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM109_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM109_IMAGE_109_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM109_IMAGE_109_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM110_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3b8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM110_OFFS                                     (0x3b8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM110_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM110_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM110_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM110_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM110_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM110_IMAGE_110_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM110_IMAGE_110_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM111_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3bc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM111_OFFS                                     (0x3bc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM111_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM111_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM111_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM111_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM111_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM111_IMAGE_111_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM111_IMAGE_111_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM112_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3c0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM112_OFFS                                     (0x3c0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM112_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM112_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM112_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM112_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM112_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM112_IMAGE_112_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM112_IMAGE_112_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM113_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3c4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM113_OFFS                                     (0x3c4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM113_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM113_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM113_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM113_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM113_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM113_IMAGE_113_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM113_IMAGE_113_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM114_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3c8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM114_OFFS                                     (0x3c8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM114_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM114_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM114_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM114_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM114_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM114_IMAGE_114_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM114_IMAGE_114_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM115_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3cc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM115_OFFS                                     (0x3cc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM115_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM115_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM115_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM115_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM115_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM115_IMAGE_115_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM115_IMAGE_115_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM116_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3d0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM116_OFFS                                     (0x3d0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM116_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM116_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM116_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM116_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM116_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM116_IMAGE_116_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM116_IMAGE_116_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM117_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3d4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM117_OFFS                                     (0x3d4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM117_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM117_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM117_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM117_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM117_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM117_IMAGE_117_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM117_IMAGE_117_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM118_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3d8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM118_OFFS                                     (0x3d8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM118_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM118_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM118_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM118_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM118_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM118_IMAGE_118_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM118_IMAGE_118_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM119_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3dc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM119_OFFS                                     (0x3dc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM119_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM119_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM119_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM119_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM119_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM119_IMAGE_119_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM119_IMAGE_119_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM120_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3e0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM120_OFFS                                     (0x3e0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM120_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM120_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM120_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM120_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM120_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM120_IMAGE_120_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM120_IMAGE_120_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM121_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3e4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM121_OFFS                                     (0x3e4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM121_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM121_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM121_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM121_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM121_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM121_IMAGE_121_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM121_IMAGE_121_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM122_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3e8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM122_OFFS                                     (0x3e8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM122_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM122_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM122_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM122_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM122_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM122_IMAGE_122_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM122_IMAGE_122_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM123_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3ec)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM123_OFFS                                     (0x3ec)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM123_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM123_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM123_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM123_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM123_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM123_IMAGE_123_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM123_IMAGE_123_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM124_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3f0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM124_OFFS                                     (0x3f0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM124_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM124_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM124_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM124_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM124_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM124_IMAGE_124_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM124_IMAGE_124_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM125_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3f4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM125_OFFS                                     (0x3f4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM125_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM125_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM125_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM125_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM125_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM125_IMAGE_125_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM125_IMAGE_125_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM126_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3f8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM126_OFFS                                     (0x3f8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM126_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM126_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM126_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM126_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM126_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM126_IMAGE_126_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM126_IMAGE_126_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM127_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3fc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM127_OFFS                                     (0x3fc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM127_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM127_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM127_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM127_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM127_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM127_IMAGE_127_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM127_IMAGE_127_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM128_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x400)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM128_OFFS                                     (0x400)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM128_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM128_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM128_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM128_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM128_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM128_IMAGE_128_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM128_IMAGE_128_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM129_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x404)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM129_OFFS                                     (0x404)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM129_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM129_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM129_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM129_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM129_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM129_IMAGE_129_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM129_IMAGE_129_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM130_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x408)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM130_OFFS                                     (0x408)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM130_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM130_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM130_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM130_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM130_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM130_IMAGE_130_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM130_IMAGE_130_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM131_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x40c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM131_OFFS                                     (0x40c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM131_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM131_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM131_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM131_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM131_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM131_IMAGE_131_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM131_IMAGE_131_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM132_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x410)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM132_OFFS                                     (0x410)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM132_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM132_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM132_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM132_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM132_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM132_IMAGE_132_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM132_IMAGE_132_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM133_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x414)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM133_OFFS                                     (0x414)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM133_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM133_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM133_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM133_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM133_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM133_IMAGE_133_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM133_IMAGE_133_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM134_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x418)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM134_OFFS                                     (0x418)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM134_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM134_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM134_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM134_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM134_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM134_IMAGE_134_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM134_IMAGE_134_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM135_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x41c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM135_OFFS                                     (0x41c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM135_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM135_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM135_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM135_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM135_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM135_IMAGE_135_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM135_IMAGE_135_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM136_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x420)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM136_OFFS                                     (0x420)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM136_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM136_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM136_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM136_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM136_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM136_IMAGE_136_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM136_IMAGE_136_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM137_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x424)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM137_OFFS                                     (0x424)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM137_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM137_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM137_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM137_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM137_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM137_IMAGE_137_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM137_IMAGE_137_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM138_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x428)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM138_OFFS                                     (0x428)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM138_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM138_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM138_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM138_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM138_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM138_IMAGE_138_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM138_IMAGE_138_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM139_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x42c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM139_OFFS                                     (0x42c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM139_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM139_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM139_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM139_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM139_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM139_IMAGE_139_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM139_IMAGE_139_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM140_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x430)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM140_OFFS                                     (0x430)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM140_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM140_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM140_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM140_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM140_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM140_IMAGE_140_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM140_IMAGE_140_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM141_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x434)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM141_OFFS                                     (0x434)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM141_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM141_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM141_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM141_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM141_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM141_IMAGE_141_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM141_IMAGE_141_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM142_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x438)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM142_OFFS                                     (0x438)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM142_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM142_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM142_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM142_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM142_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM142_IMAGE_142_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM142_IMAGE_142_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM143_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x43c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM143_OFFS                                     (0x43c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM143_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM143_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM143_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM143_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM143_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM143_IMAGE_143_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM143_IMAGE_143_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM144_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x440)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM144_OFFS                                     (0x440)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM144_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM144_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM144_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM144_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM144_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM144_IMAGE_144_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM144_IMAGE_144_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM145_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x444)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM145_OFFS                                     (0x444)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM145_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM145_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM145_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM145_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM145_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM145_IMAGE_145_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM145_IMAGE_145_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM146_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x448)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM146_OFFS                                     (0x448)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM146_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM146_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM146_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM146_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM146_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM146_IMAGE_146_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM146_IMAGE_146_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM147_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x44c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM147_OFFS                                     (0x44c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM147_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM147_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM147_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM147_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM147_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM147_IMAGE_147_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM147_IMAGE_147_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM148_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x450)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM148_OFFS                                     (0x450)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM148_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM148_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM148_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM148_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM148_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM148_IMAGE_148_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM148_IMAGE_148_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM149_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x454)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM149_OFFS                                     (0x454)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM149_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM149_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM149_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM149_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM149_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM149_IMAGE_149_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM149_IMAGE_149_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM150_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x458)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM150_OFFS                                     (0x458)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM150_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM150_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM150_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM150_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM150_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM150_IMAGE_150_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM150_IMAGE_150_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM151_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x45c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM151_OFFS                                     (0x45c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM151_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM151_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM151_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM151_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM151_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM151_IMAGE_151_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM151_IMAGE_151_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM152_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x460)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM152_OFFS                                     (0x460)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM152_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM152_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM152_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM152_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM152_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM152_IMAGE_152_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM152_IMAGE_152_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM153_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x464)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM153_OFFS                                     (0x464)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM153_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM153_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM153_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM153_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM153_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM153_IMAGE_153_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM153_IMAGE_153_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM154_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x468)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM154_OFFS                                     (0x468)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM154_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM154_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM154_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM154_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM154_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM154_IMAGE_154_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM154_IMAGE_154_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM155_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x46c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM155_OFFS                                     (0x46c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM155_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM155_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM155_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM155_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM155_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM155_IMAGE_155_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM155_IMAGE_155_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM156_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x470)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM156_OFFS                                     (0x470)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM156_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM156_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM156_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM156_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM156_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM156_IMAGE_156_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM156_IMAGE_156_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM157_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x474)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM157_OFFS                                     (0x474)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM157_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM157_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM157_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM157_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM157_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM157_IMAGE_157_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM157_IMAGE_157_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM158_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x478)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM158_OFFS                                     (0x478)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM158_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM158_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM158_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM158_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM158_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM158_IMAGE_158_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM158_IMAGE_158_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM159_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x47c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM159_OFFS                                     (0x47c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM159_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM159_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM159_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM159_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM159_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM159_IMAGE_159_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM159_IMAGE_159_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM160_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x480)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM160_OFFS                                     (0x480)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM160_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM160_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM160_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM160_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM160_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM160_IMAGE_160_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM160_IMAGE_160_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM161_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x484)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM161_OFFS                                     (0x484)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM161_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM161_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM161_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM161_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM161_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM161_IMAGE_161_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM161_IMAGE_161_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM162_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x488)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM162_OFFS                                     (0x488)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM162_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM162_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM162_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM162_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM162_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM162_IMAGE_162_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM162_IMAGE_162_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM163_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x48c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM163_OFFS                                     (0x48c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM163_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM163_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM163_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM163_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM163_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM163_IMAGE_163_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM163_IMAGE_163_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM164_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x490)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM164_OFFS                                     (0x490)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM164_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM164_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM164_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM164_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM164_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM164_IMAGE_164_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM164_IMAGE_164_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM165_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x494)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM165_OFFS                                     (0x494)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM165_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM165_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM165_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM165_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM165_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM165_IMAGE_165_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM165_IMAGE_165_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM166_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x498)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM166_OFFS                                     (0x498)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM166_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM166_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM166_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM166_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM166_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM166_IMAGE_166_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM166_IMAGE_166_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM167_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x49c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM167_OFFS                                     (0x49c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM167_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM167_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM167_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM167_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM167_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM167_IMAGE_167_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM167_IMAGE_167_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM168_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4a0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM168_OFFS                                     (0x4a0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM168_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM168_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM168_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM168_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM168_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM168_IMAGE_168_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM168_IMAGE_168_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM169_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4a4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM169_OFFS                                     (0x4a4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM169_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM169_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM169_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM169_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM169_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM169_IMAGE_169_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM169_IMAGE_169_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM170_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4a8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM170_OFFS                                     (0x4a8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM170_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM170_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM170_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM170_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM170_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM170_IMAGE_170_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM170_IMAGE_170_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM171_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4ac)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM171_OFFS                                     (0x4ac)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM171_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM171_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM171_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM171_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM171_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM171_IMAGE_171_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM171_IMAGE_171_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM172_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4b0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM172_OFFS                                     (0x4b0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM172_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM172_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM172_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM172_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM172_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM172_IMAGE_172_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM172_IMAGE_172_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM173_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4b4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM173_OFFS                                     (0x4b4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM173_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM173_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM173_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM173_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM173_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM173_IMAGE_173_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM173_IMAGE_173_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM174_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4b8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM174_OFFS                                     (0x4b8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM174_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM174_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM174_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM174_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM174_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM174_IMAGE_174_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM174_IMAGE_174_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM175_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4bc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM175_OFFS                                     (0x4bc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM175_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM175_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM175_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM175_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM175_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM175_IMAGE_175_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM175_IMAGE_175_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM176_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4c0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM176_OFFS                                     (0x4c0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM176_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM176_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM176_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM176_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM176_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM176_IMAGE_176_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM176_IMAGE_176_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM177_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4c4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM177_OFFS                                     (0x4c4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM177_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM177_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM177_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM177_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM177_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM177_IMAGE_177_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM177_IMAGE_177_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM178_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4c8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM178_OFFS                                     (0x4c8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM178_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM178_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM178_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM178_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM178_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM178_IMAGE_178_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM178_IMAGE_178_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM179_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4cc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM179_OFFS                                     (0x4cc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM179_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM179_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM179_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM179_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM179_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM179_IMAGE_179_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM179_IMAGE_179_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM180_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4d0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM180_OFFS                                     (0x4d0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM180_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM180_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM180_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM180_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM180_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM180_IMAGE_180_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM180_IMAGE_180_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM181_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4d4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM181_OFFS                                     (0x4d4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM181_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM181_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM181_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM181_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM181_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM181_IMAGE_181_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM181_IMAGE_181_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM182_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4d8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM182_OFFS                                     (0x4d8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM182_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM182_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM182_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM182_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM182_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM182_IMAGE_182_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM182_IMAGE_182_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM183_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4dc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM183_OFFS                                     (0x4dc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM183_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM183_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM183_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM183_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM183_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM183_IMAGE_183_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM183_IMAGE_183_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM184_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4e0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM184_OFFS                                     (0x4e0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM184_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM184_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM184_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM184_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM184_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM184_IMAGE_184_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM184_IMAGE_184_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM185_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4e4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM185_OFFS                                     (0x4e4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM185_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM185_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM185_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM185_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM185_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM185_IMAGE_185_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM185_IMAGE_185_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM186_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4e8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM186_OFFS                                     (0x4e8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM186_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM186_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM186_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM186_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM186_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM186_IMAGE_186_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM186_IMAGE_186_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM187_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4ec)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM187_OFFS                                     (0x4ec)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM187_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM187_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM187_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM187_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM187_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM187_IMAGE_187_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM187_IMAGE_187_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM188_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4f0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM188_OFFS                                     (0x4f0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM188_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM188_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM188_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM188_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM188_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM188_IMAGE_188_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM188_IMAGE_188_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM189_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4f4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM189_OFFS                                     (0x4f4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM189_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM189_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM189_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM189_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM189_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM189_IMAGE_189_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM189_IMAGE_189_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM190_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4f8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM190_OFFS                                     (0x4f8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM190_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM190_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM190_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM190_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM190_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM190_IMAGE_190_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM190_IMAGE_190_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM191_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4fc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM191_OFFS                                     (0x4fc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM191_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM191_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM191_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM191_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM191_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM191_IMAGE_191_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM191_IMAGE_191_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM192_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x500)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM192_OFFS                                     (0x500)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM192_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM192_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM192_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM192_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM192_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM192_IMAGE_192_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM192_IMAGE_192_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM193_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x504)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM193_OFFS                                     (0x504)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM193_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM193_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM193_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM193_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM193_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM193_IMAGE_193_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM193_IMAGE_193_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM194_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x508)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM194_OFFS                                     (0x508)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM194_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM194_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM194_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM194_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM194_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM194_IMAGE_194_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM194_IMAGE_194_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM195_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x50c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM195_OFFS                                     (0x50c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM195_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM195_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM195_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM195_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM195_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM195_IMAGE_195_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM195_IMAGE_195_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM196_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x510)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM196_OFFS                                     (0x510)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM196_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM196_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM196_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM196_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM196_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM196_IMAGE_196_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM196_IMAGE_196_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM197_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x514)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM197_OFFS                                     (0x514)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM197_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM197_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM197_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM197_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM197_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM197_IMAGE_197_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM197_IMAGE_197_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM198_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x518)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM198_OFFS                                     (0x518)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM198_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM198_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM198_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM198_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM198_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM198_IMAGE_198_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM198_IMAGE_198_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM199_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x51c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM199_OFFS                                     (0x51c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM199_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM199_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM199_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM199_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM199_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM199_IMAGE_199_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM199_IMAGE_199_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM200_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x520)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM200_OFFS                                     (0x520)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM200_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM200_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM200_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM200_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM200_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM200_IMAGE_200_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM200_IMAGE_200_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM201_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x524)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM201_OFFS                                     (0x524)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM201_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM201_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM201_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM201_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM201_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM201_IMAGE_201_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM201_IMAGE_201_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM202_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x528)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM202_OFFS                                     (0x528)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM202_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM202_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM202_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM202_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM202_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM202_IMAGE_202_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM202_IMAGE_202_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM203_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x52c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM203_OFFS                                     (0x52c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM203_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM203_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM203_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM203_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM203_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM203_IMAGE_203_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM203_IMAGE_203_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM204_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x530)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM204_OFFS                                     (0x530)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM204_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM204_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM204_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM204_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM204_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM204_IMAGE_204_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM204_IMAGE_204_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM205_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x534)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM205_OFFS                                     (0x534)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM205_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM205_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM205_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM205_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM205_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM205_IMAGE_205_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM205_IMAGE_205_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM206_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x538)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM206_OFFS                                     (0x538)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM206_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM206_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM206_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM206_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM206_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM206_IMAGE_206_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM206_IMAGE_206_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM207_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x53c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM207_OFFS                                     (0x53c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM207_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM207_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM207_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM207_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM207_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM207_IMAGE_207_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM207_IMAGE_207_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM208_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x540)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM208_OFFS                                     (0x540)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM208_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM208_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM208_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM208_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM208_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM208_IMAGE_208_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM208_IMAGE_208_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM209_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x544)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM209_OFFS                                     (0x544)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM209_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM209_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM209_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM209_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM209_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM209_IMAGE_209_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM209_IMAGE_209_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM210_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x548)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM210_OFFS                                     (0x548)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM210_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM210_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM210_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM210_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM210_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM210_IMAGE_210_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM210_IMAGE_210_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM211_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x54c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM211_OFFS                                     (0x54c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM211_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM211_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM211_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM211_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM211_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM211_IMAGE_211_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM211_IMAGE_211_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM212_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x550)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM212_OFFS                                     (0x550)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM212_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM212_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM212_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM212_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM212_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM212_IMAGE_212_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM212_IMAGE_212_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM213_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x554)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM213_OFFS                                     (0x554)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM213_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM213_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM213_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM213_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM213_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM213_IMAGE_213_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM213_IMAGE_213_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM214_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x558)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM214_OFFS                                     (0x558)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM214_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM214_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM214_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM214_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM214_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM214_IMAGE_214_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM214_IMAGE_214_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM215_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x55c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM215_OFFS                                     (0x55c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM215_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM215_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM215_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM215_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM215_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM215_IMAGE_215_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM215_IMAGE_215_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM216_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x560)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM216_OFFS                                     (0x560)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM216_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM216_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM216_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM216_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM216_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM216_IMAGE_216_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM216_IMAGE_216_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM217_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x564)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM217_OFFS                                     (0x564)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM217_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM217_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM217_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM217_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM217_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM217_IMAGE_217_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM217_IMAGE_217_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM218_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x568)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM218_OFFS                                     (0x568)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM218_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM218_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM218_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM218_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM218_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM218_IMAGE_218_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM218_IMAGE_218_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM219_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x56c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM219_OFFS                                     (0x56c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM219_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM219_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM219_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM219_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM219_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM219_IMAGE_219_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM219_IMAGE_219_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM220_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x570)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM220_OFFS                                     (0x570)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM220_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM220_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM220_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM220_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM220_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM220_IMAGE_220_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM220_IMAGE_220_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM221_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x574)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM221_OFFS                                     (0x574)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM221_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM221_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM221_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM221_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM221_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM221_IMAGE_221_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM221_IMAGE_221_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM222_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x578)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM222_OFFS                                     (0x578)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM222_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM222_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM222_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM222_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM222_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM222_IMAGE_222_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM222_IMAGE_222_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM223_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x57c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM223_OFFS                                     (0x57c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM223_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM223_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM223_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM223_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM223_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM223_IMAGE_223_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM223_IMAGE_223_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM224_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x580)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM224_OFFS                                     (0x580)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM224_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM224_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM224_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM224_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM224_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM224_IMAGE_224_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM224_IMAGE_224_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM225_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x584)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM225_OFFS                                     (0x584)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM225_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM225_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM225_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM225_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM225_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM225_IMAGE_225_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM225_IMAGE_225_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM226_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x588)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM226_OFFS                                     (0x588)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM226_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM226_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM226_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM226_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM226_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM226_IMAGE_226_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM226_IMAGE_226_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM227_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x58c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM227_OFFS                                     (0x58c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM227_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM227_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM227_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM227_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM227_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM227_IMAGE_227_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM227_IMAGE_227_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM228_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x590)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM228_OFFS                                     (0x590)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM228_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM228_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM228_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM228_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM228_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM228_IMAGE_228_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM228_IMAGE_228_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM229_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x594)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM229_OFFS                                     (0x594)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM229_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM229_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM229_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM229_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM229_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM229_IMAGE_229_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM229_IMAGE_229_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM230_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x598)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM230_OFFS                                     (0x598)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM230_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM230_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM230_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM230_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM230_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM230_IMAGE_230_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM230_IMAGE_230_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM231_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x59c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM231_OFFS                                     (0x59c)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM231_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM231_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM231_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM231_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM231_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM231_IMAGE_231_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM231_IMAGE_231_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM232_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5a0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM232_OFFS                                     (0x5a0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM232_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM232_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM232_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM232_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM232_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM232_IMAGE_232_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM232_IMAGE_232_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM233_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5a4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM233_OFFS                                     (0x5a4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM233_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM233_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM233_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM233_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM233_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM233_IMAGE_233_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM233_IMAGE_233_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM234_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5a8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM234_OFFS                                     (0x5a8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM234_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM234_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM234_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM234_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM234_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM234_IMAGE_234_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM234_IMAGE_234_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM235_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5ac)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM235_OFFS                                     (0x5ac)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM235_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM235_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM235_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM235_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM235_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM235_IMAGE_235_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM235_IMAGE_235_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM236_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5b0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM236_OFFS                                     (0x5b0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM236_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM236_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM236_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM236_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM236_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM236_IMAGE_236_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM236_IMAGE_236_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM237_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5b4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM237_OFFS                                     (0x5b4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM237_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM237_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM237_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM237_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM237_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM237_IMAGE_237_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM237_IMAGE_237_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM238_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5b8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM238_OFFS                                     (0x5b8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM238_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM238_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM238_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM238_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM238_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM238_IMAGE_238_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM238_IMAGE_238_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM239_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5bc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM239_OFFS                                     (0x5bc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM239_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM239_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM239_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM239_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM239_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM239_IMAGE_239_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM239_IMAGE_239_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM240_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5c0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM240_OFFS                                     (0x5c0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM240_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM240_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM240_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM240_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM240_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM240_IMAGE_240_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM240_IMAGE_240_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM241_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5c4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM241_OFFS                                     (0x5c4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM241_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM241_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM241_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM241_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM241_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM241_IMAGE_241_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM241_IMAGE_241_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM242_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5c8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM242_OFFS                                     (0x5c8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM242_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM242_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM242_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM242_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM242_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM242_IMAGE_242_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM242_IMAGE_242_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM243_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5cc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM243_OFFS                                     (0x5cc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM243_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM243_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM243_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM243_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM243_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM243_IMAGE_243_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM243_IMAGE_243_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM244_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5d0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM244_OFFS                                     (0x5d0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM244_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM244_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM244_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM244_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM244_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM244_IMAGE_244_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM244_IMAGE_244_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM245_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5d4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM245_OFFS                                     (0x5d4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM245_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM245_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM245_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM245_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM245_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM245_IMAGE_245_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM245_IMAGE_245_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM246_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5d8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM246_OFFS                                     (0x5d8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM246_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM246_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM246_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM246_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM246_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM246_IMAGE_246_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM246_IMAGE_246_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM247_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5dc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM247_OFFS                                     (0x5dc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM247_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM247_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM247_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM247_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM247_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM247_IMAGE_247_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM247_IMAGE_247_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM248_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5e0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM248_OFFS                                     (0x5e0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM248_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM248_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM248_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM248_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM248_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM248_IMAGE_248_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM248_IMAGE_248_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM249_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5e4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM249_OFFS                                     (0x5e4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM249_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM249_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM249_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM249_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM249_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM249_IMAGE_249_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM249_IMAGE_249_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM250_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5e8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM250_OFFS                                     (0x5e8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM250_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM250_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM250_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM250_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM250_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM250_IMAGE_250_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM250_IMAGE_250_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM251_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5ec)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM251_OFFS                                     (0x5ec)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM251_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM251_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM251_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM251_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM251_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM251_IMAGE_251_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM251_IMAGE_251_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM252_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5f0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM252_OFFS                                     (0x5f0)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM252_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM252_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM252_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM252_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM252_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM252_IMAGE_252_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM252_IMAGE_252_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM253_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5f4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM253_OFFS                                     (0x5f4)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM253_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM253_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM253_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM253_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM253_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM253_IMAGE_253_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM253_IMAGE_253_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM254_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5f8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM254_OFFS                                     (0x5f8)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM254_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM254_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM254_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM254_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM254_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM254_IMAGE_254_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM254_IMAGE_254_SHFT                                    0

#define HWIO_SPMI0_SPMI_GENI_CFG_RAM255_ADDR(x)                                  ((x) + SPMI0_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5fc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM255_OFFS                                     (0x5fc)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM255_RMSK                                       0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM255_IN(x)            \
                in_dword(HWIO_SPMI0_SPMI_GENI_CFG_RAM255_ADDR(x))
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM255_INM(x, m)            \
                in_dword_masked(HWIO_SPMI0_SPMI_GENI_CFG_RAM255_ADDR(x), m)
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM255_IMAGE_255_BMSK                             0x1fffff
#define HWIO_SPMI0_SPMI_GENI_CFG_RAM255_IMAGE_255_SHFT                                    0

/*----------------------------------------------------------------------------
 * MODULE: SPMI1_SPMI_CFG
 *--------------------------------------------------------------------------*/

#define SPMI1_SPMI_CFG_REG_BASE_OFFS                                                        0x32000

#define HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,m)                               ((base) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0X0 + (0x4*(m)))
#define HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_OFFS(m)                                    (0X0 + (0x4*(m)))
#define HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_RMSK                                        0xfff000f
#define HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_INI(base,m)                \
                in_dword_masked(HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,m), HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_RMSK)
#define HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_INMI(base,m,mask)        \
                in_dword_masked(HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,m), mask)
#define HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_OUTI(base,m,val)        \
                out_dword(HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,m),val)
#define HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_OUTMI(base,m,mask,val) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,m),mask,val,HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_INI(base,m))
#define HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_APID2PPID_BMSK                              0xfff0000
#define HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_APID2PPID_SHFT                                     16
#define HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_PERIPH2OWNER_BMSK                                 0xf
#define HWIO_SPMI1_SPMI_PERIPHm_2OWNER_TABLE_REG_PERIPH2OWNER_SHFT                                   0

#define HWIO_SPMI1_SPMI_MID_REG_ADDR(x)                                                     ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1800)
#define HWIO_SPMI1_SPMI_MID_REG_OFFS                                                        (0x1800)
#define HWIO_SPMI1_SPMI_MID_REG_RMSK                                                               0x3
#define HWIO_SPMI1_SPMI_MID_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_MID_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_MID_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_MID_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_MID_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_MID_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_MID_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_MID_REG_ADDR(x),m,v,HWIO_SPMI1_SPMI_MID_REG_IN(x))
#define HWIO_SPMI1_SPMI_MID_REG_MID_BMSK                                                           0x3
#define HWIO_SPMI1_SPMI_MID_REG_MID_SHFT                                                             0

#define HWIO_SPMI1_SPMI_CFG_REG_ADDR(x)                                                     ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1804)
#define HWIO_SPMI1_SPMI_CFG_REG_OFFS                                                        (0x1804)
#define HWIO_SPMI1_SPMI_CFG_REG_RMSK                                                         0x3ffffff
#define HWIO_SPMI1_SPMI_CFG_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_CFG_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_CFG_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_CFG_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_CFG_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_CFG_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_CFG_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_CFG_REG_ADDR(x),m,v,HWIO_SPMI1_SPMI_CFG_REG_IN(x))
#define HWIO_SPMI1_SPMI_CFG_REG_LATENCY_CNTR_BMSK                                            0x3800000
#define HWIO_SPMI1_SPMI_CFG_REG_LATENCY_CNTR_SHFT                                                   23
#define HWIO_SPMI1_SPMI_CFG_REG_SCLK_OE_EXTEND_BMSK                                           0x400000
#define HWIO_SPMI1_SPMI_CFG_REG_SCLK_OE_EXTEND_SHFT                                                 22
#define HWIO_SPMI1_SPMI_CFG_REG_RPMH_CLK_REQ_EN_BMSK                                          0x200000
#define HWIO_SPMI1_SPMI_CFG_REG_RPMH_CLK_REQ_EN_SHFT                                                21
#define HWIO_SPMI1_SPMI_CFG_REG_WDT_CFG_BMSK                                                  0x1e0000
#define HWIO_SPMI1_SPMI_CFG_REG_WDT_CFG_SHFT                                                        17
#define HWIO_SPMI1_SPMI_CFG_REG_ARBITER_CTRL_BMSK                                              0x1e000
#define HWIO_SPMI1_SPMI_CFG_REG_ARBITER_CTRL_SHFT                                                   13
#define HWIO_SPMI1_SPMI_CFG_REG_GENI_SPMI_BUS_IN_MASK_DIS_BMSK                                  0x1000
#define HWIO_SPMI1_SPMI_CFG_REG_GENI_SPMI_BUS_IN_MASK_DIS_SHFT                                      12
#define HWIO_SPMI1_SPMI_CFG_REG_ASYNC_SSC_DET_INT_DIS_BMSK                                       0x800
#define HWIO_SPMI1_SPMI_CFG_REG_ASYNC_SSC_DET_INT_DIS_SHFT                                          11
#define HWIO_SPMI1_SPMI_CFG_REG_SSC_Q1_DELAY_DIS_BMSK                                            0x400
#define HWIO_SPMI1_SPMI_CFG_REG_SSC_Q1_DELAY_DIS_SHFT                                               10
#define HWIO_SPMI1_SPMI_CFG_REG_ARB_UNKNOWN_EN_BMSK                                              0x200
#define HWIO_SPMI1_SPMI_CFG_REG_ARB_UNKNOWN_EN_SHFT                                                  9
#define HWIO_SPMI1_SPMI_CFG_REG_SSC_WINDOW_EN_BMSK                                               0x100
#define HWIO_SPMI1_SPMI_CFG_REG_SSC_WINDOW_EN_SHFT                                                   8
#define HWIO_SPMI1_SPMI_CFG_REG_SSC_DET_INT_DIS_BMSK                                              0x80
#define HWIO_SPMI1_SPMI_CFG_REG_SSC_DET_INT_DIS_SHFT                                                 7
#define HWIO_SPMI1_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_IMM_BMSK                                        0x40
#define HWIO_SPMI1_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_IMM_SHFT                                           6
#define HWIO_SPMI1_SPMI_CFG_REG_FORCE_ARB_AFTER_MASTER_TO_BMSK                                    0x20
#define HWIO_SPMI1_SPMI_CFG_REG_FORCE_ARB_AFTER_MASTER_TO_SHFT                                       5
#define HWIO_SPMI1_SPMI_CFG_REG_BUS_IDLE_CONN_MODE_BMSK                                           0x10
#define HWIO_SPMI1_SPMI_CFG_REG_BUS_IDLE_CONN_MODE_SHFT                                              4
#define HWIO_SPMI1_SPMI_CFG_REG_FORCE_MASTER_WRITE_ON_ERROR_BMSK                                   0x8
#define HWIO_SPMI1_SPMI_CFG_REG_FORCE_MASTER_WRITE_ON_ERROR_SHFT                                     3
#define HWIO_SPMI1_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_BMSK                                             0x4
#define HWIO_SPMI1_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_SHFT                                               2
#define HWIO_SPMI1_SPMI_CFG_REG_ARBITER_BYPASS_BMSK                                                0x2
#define HWIO_SPMI1_SPMI_CFG_REG_ARBITER_BYPASS_SHFT                                                  1
#define HWIO_SPMI1_SPMI_CFG_REG_ARBITER_ENABLE_BMSK                                                0x1
#define HWIO_SPMI1_SPMI_CFG_REG_ARBITER_ENABLE_SHFT                                                  0

#define HWIO_SPMI1_SPMI_SEC_DISABLE_REG_ADDR(x)                                             ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1808)
#define HWIO_SPMI1_SPMI_SEC_DISABLE_REG_OFFS                                                (0x1808)
#define HWIO_SPMI1_SPMI_SEC_DISABLE_REG_RMSK                                                       0x1
#define HWIO_SPMI1_SPMI_SEC_DISABLE_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_SEC_DISABLE_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_SEC_DISABLE_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_SEC_DISABLE_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_SEC_DISABLE_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_SEC_DISABLE_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_SEC_DISABLE_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_SEC_DISABLE_REG_ADDR(x),m,v,HWIO_SPMI1_SPMI_SEC_DISABLE_REG_IN(x))
#define HWIO_SPMI1_SPMI_SEC_DISABLE_REG_DISABLE_SECURITY_BMSK                                      0x1
#define HWIO_SPMI1_SPMI_SEC_DISABLE_REG_DISABLE_SECURITY_SHFT                                        0

#define HWIO_SPMI1_SPMI_HW_VERSION_ADDR(x)                                                  ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x180c)
#define HWIO_SPMI1_SPMI_HW_VERSION_OFFS                                                     (0x180c)
#define HWIO_SPMI1_SPMI_HW_VERSION_RMSK                                                     0xff000fff
#define HWIO_SPMI1_SPMI_HW_VERSION_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_HW_VERSION_ADDR(x))
#define HWIO_SPMI1_SPMI_HW_VERSION_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_HW_VERSION_ADDR(x), m)
#define HWIO_SPMI1_SPMI_HW_VERSION_HW_VERSION_RUNNING_R_BMSK                                0xff000000
#define HWIO_SPMI1_SPMI_HW_VERSION_HW_VERSION_RUNNING_R_SHFT                                        24
#define HWIO_SPMI1_SPMI_HW_VERSION_HW_VERSION_MAJOR_BMSK                                         0xf00
#define HWIO_SPMI1_SPMI_HW_VERSION_HW_VERSION_MAJOR_SHFT                                             8
#define HWIO_SPMI1_SPMI_HW_VERSION_HW_VERSION_MINOR_BMSK                                          0xf0
#define HWIO_SPMI1_SPMI_HW_VERSION_HW_VERSION_MINOR_SHFT                                             4
#define HWIO_SPMI1_SPMI_HW_VERSION_HW_VERSION_STEP_BMSK                                            0xf
#define HWIO_SPMI1_SPMI_HW_VERSION_HW_VERSION_STEP_SHFT                                              0

#define HWIO_SPMI1_SPMI_CGC_CTRL_ADDR(x)                                                    ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1810)
#define HWIO_SPMI1_SPMI_CGC_CTRL_OFFS                                                       (0x1810)
#define HWIO_SPMI1_SPMI_CGC_CTRL_RMSK                                                             0x7f
#define HWIO_SPMI1_SPMI_CGC_CTRL_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_CGC_CTRL_ADDR(x))
#define HWIO_SPMI1_SPMI_CGC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_CGC_CTRL_ADDR(x), m)
#define HWIO_SPMI1_SPMI_CGC_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_CGC_CTRL_ADDR(x),v)
#define HWIO_SPMI1_SPMI_CGC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_CGC_CTRL_ADDR(x),m,v,HWIO_SPMI1_SPMI_CGC_CTRL_IN(x))
#define HWIO_SPMI1_SPMI_CGC_CTRL_MAP_LOGIC_CLK_CGC_ON_BMSK                                        0x40
#define HWIO_SPMI1_SPMI_CGC_CTRL_MAP_LOGIC_CLK_CGC_ON_SHFT                                           6
#define HWIO_SPMI1_SPMI_CGC_CTRL_RPU_CLK_CGC_ON_BMSK                                              0x20
#define HWIO_SPMI1_SPMI_CGC_CTRL_RPU_CLK_CGC_ON_SHFT                                                 5
#define HWIO_SPMI1_SPMI_CGC_CTRL_MWB_CLK_CGC_ON_BMSK                                              0x10
#define HWIO_SPMI1_SPMI_CGC_CTRL_MWB_CLK_CGC_ON_SHFT                                                 4
#define HWIO_SPMI1_SPMI_CGC_CTRL_PIC_CLK_CGC_ON_BMSK                                               0x8
#define HWIO_SPMI1_SPMI_CGC_CTRL_PIC_CLK_CGC_ON_SHFT                                                 3
#define HWIO_SPMI1_SPMI_CGC_CTRL_PAC_CLK_CGC_ON_BMSK                                               0x4
#define HWIO_SPMI1_SPMI_CGC_CTRL_PAC_CLK_CGC_ON_SHFT                                                 2
#define HWIO_SPMI1_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_WR_CLK_CGC_ON_BMSK                                 0x2
#define HWIO_SPMI1_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_WR_CLK_CGC_ON_SHFT                                   1
#define HWIO_SPMI1_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_CLK_CGC_ON_BMSK                                    0x1
#define HWIO_SPMI1_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_CLK_CGC_ON_SHFT                                      0

#define HWIO_SPMI1_SPMI_MWB_ENABLE_REG_ADDR(x)                                              ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1814)
#define HWIO_SPMI1_SPMI_MWB_ENABLE_REG_OFFS                                                 (0x1814)
#define HWIO_SPMI1_SPMI_MWB_ENABLE_REG_RMSK                                                        0x1
#define HWIO_SPMI1_SPMI_MWB_ENABLE_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_MWB_ENABLE_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_MWB_ENABLE_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_MWB_ENABLE_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_MWB_ENABLE_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_MWB_ENABLE_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_MWB_ENABLE_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_MWB_ENABLE_REG_ADDR(x),m,v,HWIO_SPMI1_SPMI_MWB_ENABLE_REG_IN(x))
#define HWIO_SPMI1_SPMI_MWB_ENABLE_REG_MWB_ENABLE_BMSK                                             0x1
#define HWIO_SPMI1_SPMI_MWB_ENABLE_REG_MWB_ENABLE_SHFT                                               0

#define HWIO_SPMI1_SPMI_CHAR_CFG_ADDR(x)                                                    ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1840)
#define HWIO_SPMI1_SPMI_CHAR_CFG_OFFS                                                       (0x1840)
#define HWIO_SPMI1_SPMI_CHAR_CFG_RMSK                                                          0xfff11
#define HWIO_SPMI1_SPMI_CHAR_CFG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_CHAR_CFG_ADDR(x))
#define HWIO_SPMI1_SPMI_CHAR_CFG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_CHAR_CFG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_CHAR_CFG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_CHAR_CFG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_CHAR_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_CHAR_CFG_ADDR(x),m,v,HWIO_SPMI1_SPMI_CHAR_CFG_IN(x))
#define HWIO_SPMI1_SPMI_CHAR_CFG_CHAR_MODE_BMSK                                                0xff000
#define HWIO_SPMI1_SPMI_CHAR_CFG_CHAR_MODE_SHFT                                                     12
#define HWIO_SPMI1_SPMI_CHAR_CFG_CHAR_STATUS_BMSK                                                0xf00
#define HWIO_SPMI1_SPMI_CHAR_CFG_CHAR_STATUS_SHFT                                                    8
#define HWIO_SPMI1_SPMI_CHAR_CFG_DIRECTION_BMSK                                                   0x10
#define HWIO_SPMI1_SPMI_CHAR_CFG_DIRECTION_SHFT                                                      4
#define HWIO_SPMI1_SPMI_CHAR_CFG_ENABLE_BMSK                                                       0x1
#define HWIO_SPMI1_SPMI_CHAR_CFG_ENABLE_SHFT                                                         0

#define HWIO_SPMI1_SPMI_CHAR_DATA_n_ADDR(base,n)                                            ((base) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0X1844 + (0x4*(n)))
#define HWIO_SPMI1_SPMI_CHAR_DATA_n_OFFS(n)                                                 (0X1844 + (0x4*(n)))
#define HWIO_SPMI1_SPMI_CHAR_DATA_n_RMSK                                                        0xffff
#define HWIO_SPMI1_SPMI_CHAR_DATA_n_INI(base,n)                \
                in_dword_masked(HWIO_SPMI1_SPMI_CHAR_DATA_n_ADDR(base,n), HWIO_SPMI1_SPMI_CHAR_DATA_n_RMSK)
#define HWIO_SPMI1_SPMI_CHAR_DATA_n_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI1_SPMI_CHAR_DATA_n_ADDR(base,n), mask)
#define HWIO_SPMI1_SPMI_CHAR_DATA_n_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI1_SPMI_CHAR_DATA_n_ADDR(base,n),val)
#define HWIO_SPMI1_SPMI_CHAR_DATA_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_CHAR_DATA_n_ADDR(base,n),mask,val,HWIO_SPMI1_SPMI_CHAR_DATA_n_INI(base,n))
#define HWIO_SPMI1_SPMI_CHAR_DATA_n_DIN_ACTUAL_BMSK                                             0xff00
#define HWIO_SPMI1_SPMI_CHAR_DATA_n_DIN_ACTUAL_SHFT                                                  8
#define HWIO_SPMI1_SPMI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_BMSK                                        0xff
#define HWIO_SPMI1_SPMI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_SHFT                                           0

#define HWIO_SPMI1_SPMI_CMPR_EN_REG_ADDR(x)                                                 ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1854)
#define HWIO_SPMI1_SPMI_CMPR_EN_REG_OFFS                                                    (0x1854)
#define HWIO_SPMI1_SPMI_CMPR_EN_REG_RMSK                                                           0x1
#define HWIO_SPMI1_SPMI_CMPR_EN_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_CMPR_EN_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_CMPR_EN_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_CMPR_EN_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_CMPR_EN_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_CMPR_EN_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_CMPR_EN_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_CMPR_EN_REG_ADDR(x),m,v,HWIO_SPMI1_SPMI_CMPR_EN_REG_IN(x))
#define HWIO_SPMI1_SPMI_CMPR_EN_REG_CMPR_ENABLE_BMSK                                               0x1
#define HWIO_SPMI1_SPMI_CMPR_EN_REG_CMPR_ENABLE_SHFT                                                 0

#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_ADDR(x)                                             ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1858)
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_OFFS                                                (0x1858)
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_RMSK                                                     0x3ff
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_ADDR(x),m,v,HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_IN(x))
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_BMSK                                 0x200
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_SHFT                                     9
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_SM_MM_MODE_BMSK                      0x100
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_SM_MM_MODE_SHFT                          8
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SNOOPER_SW_RST_EN_BMSK                                    0x80
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SNOOPER_SW_RST_EN_SHFT                                       7
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_FROM_SPMI_M_EN_BMSK                   0x40
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_FROM_SPMI_M_EN_SHFT                      6
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_TEST_BUS_SELECT_BMSK                   0x38
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_TEST_BUS_SELECT_SHFT                      3
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_MODE_BMSK                                     0x4
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_MODE_SHFT                                       2
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_SSC_DET_CFG_BMSK                        0x3
#define HWIO_SPMI1_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_SSC_DET_CFG_SHFT                          0

#define HWIO_SPMI1_SPMI_STATUS_REG_ADDR(x)                                                  ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x185c)
#define HWIO_SPMI1_SPMI_STATUS_REG_OFFS                                                     (0x185c)
#define HWIO_SPMI1_SPMI_STATUS_REG_RMSK                                                            0x1
#define HWIO_SPMI1_SPMI_STATUS_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_STATUS_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_STATUS_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_STATUS_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_STATUS_REG_ARB_IS_BOM_BMSK                                                 0x1
#define HWIO_SPMI1_SPMI_STATUS_REG_ARB_IS_BOM_SHFT                                                   0

#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,n)                                       ((base) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0X1A00 + (0x4*(n)))
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_OFFS(n)                                            (0X1A00 + (0x4*(n)))
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_RMSK                                               0xff8fffff
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_INI(base,n)                \
                in_dword_masked(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,n), HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_RMSK)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,n), mask)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,n),val)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,n),mask,val,HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_INI(base,n))
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_MSG_MASK_BMSK                                      0xff000000
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_MSG_MASK_SHFT                                              24
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_VIOCTL_EN_BMSK                                       0x800000
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_VIOCTL_EN_SHFT                                             23
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_SID_BMSK                                              0xf0000
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_SID_SHFT                                                   16
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_PID_BMSK                                               0xff00
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_PID_SHFT                                                    8
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_RCS_MSG_BMSK                                             0xff
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_n_RCS_MSG_SHFT                                                0

#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,n)                        ((base) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0X1A80 + (0x4*(n)))
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_OFFS(n)                             (0X1A80 + (0x4*(n)))
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_RMSK                                       0x1
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_INI(base,n)                \
                in_dword_masked(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,n), HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_RMSK)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,n), mask)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,n),val)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,n),mask,val,HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_INI(base,n))
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ENABLE_BMSK                                0x1
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ENABLE_SHFT                                  0

#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x)                               ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1b00)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_OFFS                                  (0x1b00)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_RMSK                                        0xff
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x))
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x), m)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x),v)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x),m,v,HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_IN(x))
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_CTR_CFG_BMSK                                0xff
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_CTR_CFG_SHFT                                   0

#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,n)                                     ((base) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0X1B80 + (0x4*(n)))
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_OFFS(n)                                          (0X1B80 + (0x4*(n)))
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_RMSK                                             0xff8fffff
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_INI(base,n)                \
                in_dword_masked(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,n), HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_RMSK)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,n), mask)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,n),val)
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,n),mask,val,HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_INI(base,n))
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_MSG_MASK_BMSK                                    0xff000000
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_MSG_MASK_SHFT                                            24
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_VIOCTL_EN_BMSK                                     0x800000
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_VIOCTL_EN_SHFT                                           23
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_SID_BMSK                                            0xf0000
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_SID_SHFT                                                 16
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_PID_BMSK                                             0xff00
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_PID_SHFT                                                  8
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_RCS_MSG_BMSK                                           0xff
#define HWIO_SPMI1_SPMI_PIC_RCS_VIOCTL_N_n_RCS_MSG_SHFT                                              0

#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_ADDR(x)                                              ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1c00)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_OFFS                                                 (0x1c00)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_RMSK                                                    0x3ffff
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_ADDR(x))
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_ADDR(x), m)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_ADDR(x),v)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_ADDR(x),m,v,HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_IN(x))
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_WDT_ARB_EN_CRTL_BMSK                                    0x20000
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_WDT_ARB_EN_CRTL_SHFT                                         17
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_PMIC_ARB_ARST_EN_BMSK                                   0x10000
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_PMIC_ARB_ARST_EN_SHFT                                        16
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_M_ARB_ARST_EN_BMSK                                  0x8000
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_M_ARB_ARST_EN_SHFT                                      15
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_GENI_ARST_EN_BMSK                                        0x4000
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_GENI_ARST_EN_SHFT                                            14
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_ARST_ASSERT_BMSK                            0x2000
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_ARST_ASSERT_SHFT                                13
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_ARST_ASSERT_BMSK                            0x1000
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_ARST_ASSERT_SHFT                                12
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_SCLK_ARES_ASSERT_BMSK                                0x800
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_SCLK_ARES_ASSERT_SHFT                                   11
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_ARST_ASSERT_BMSK                         0x400
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_ARST_ASSERT_SHFT                            10
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_BUS_CLK_GATE_EN_BMSK                                 0x200
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_BUS_CLK_GATE_EN_SHFT                                     9
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_GATE_EN_BMSK                                 0x100
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_GATE_EN_SHFT                                     8
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_PMIC_ARB_CLK_GATE_EN_BMSK                                  0x80
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_PMIC_ARB_CLK_GATE_EN_SHFT                                     7
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_GATE_EN_BMSK                                  0x40
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_GATE_EN_SHFT                                     6
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SLEEP_CLK_GATE_EN_BMSK                                     0x20
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SLEEP_CLK_GATE_EN_SHFT                                        5
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_GATE_EN_BMSK                              0x10
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_GATE_EN_SHFT                                 4
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_EN_BMSK                                       0x8
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_EN_SHFT                                         3
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_CLR_BMSK                                      0x4
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_CLR_SHFT                                        2
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_WDT_AUTO_HW_EN_BMSK                                         0x2
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_WDT_AUTO_HW_EN_SHFT                                           1
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_WDT_CNT_EN_BMSK                                             0x1
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_0_WDT_CNT_EN_SHFT                                               0

#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_ADDR(x)                                              ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1c04)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_OFFS                                                 (0x1c04)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_RMSK                                                   0xfff00f
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_ADDR(x))
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_ADDR(x), m)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_ADDR(x),v)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_ADDR(x),m,v,HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_IN(x))
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_RESET_ASSERT_INTERVAL_BMSK                             0xf00000
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_RESET_ASSERT_INTERVAL_SHFT                                   20
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_CLK_GATE_EN_TO_RST_ASSERT_INTERVAL_BMSK                 0xf0000
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_CLK_GATE_EN_TO_RST_ASSERT_INTERVAL_SHFT                      16
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_ARB_EN_TO_CLK_GATE_EN_INTERVAL_BMSK                      0xf000
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_ARB_EN_TO_CLK_GATE_EN_INTERVAL_SHFT                          12
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_WDT_CTR_EXPIRY_VALUE_BMSK                                   0xf
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_1_WDT_CTR_EXPIRY_VALUE_SHFT                                     0

#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_ADDR(x)                                              ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1c08)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_OFFS                                                 (0x1c08)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_RMSK                                                        0x3
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_ADDR(x))
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_ADDR(x), m)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_ADDR(x),v)
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_ADDR(x),m,v,HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_IN(x))
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_WDT_SCLK_RST_MODE_BMSK                                      0x2
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_WDT_SCLK_RST_MODE_SHFT                                        1
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_WDT_SW_RST_BMSK                                             0x1
#define HWIO_SPMI1_SPMI_WDT_CTRL_REG_2_WDT_SW_RST_SHFT                                               0

#define HWIO_SPMI1_SPMI_WDT_STATUS_REG_ADDR(x)                                              ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1c0c)
#define HWIO_SPMI1_SPMI_WDT_STATUS_REG_OFFS                                                 (0x1c0c)
#define HWIO_SPMI1_SPMI_WDT_STATUS_REG_RMSK                                                        0x1
#define HWIO_SPMI1_SPMI_WDT_STATUS_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_WDT_STATUS_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_WDT_STATUS_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_WDT_STATUS_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_WDT_STATUS_REG_WDT_DONE_BMSK                                               0x1
#define HWIO_SPMI1_SPMI_WDT_STATUS_REG_WDT_DONE_SHFT                                                 0

#define HWIO_SPMI1_SPMI_WDT_DEBUG_CNT_REG_ADDR(x)                                           ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x1c10)
#define HWIO_SPMI1_SPMI_WDT_DEBUG_CNT_REG_OFFS                                              (0x1c10)
#define HWIO_SPMI1_SPMI_WDT_DEBUG_CNT_REG_RMSK                                                  0xffff
#define HWIO_SPMI1_SPMI_WDT_DEBUG_CNT_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_WDT_DEBUG_CNT_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_WDT_DEBUG_CNT_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_WDT_DEBUG_CNT_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_WDT_DEBUG_CNT_REG_WDT_DEBUG_CNT_BMSK                                    0xffff
#define HWIO_SPMI1_SPMI_WDT_DEBUG_CNT_REG_WDT_DEBUG_CNT_SHFT                                         0

#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_ADDR(x)                                         ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x2000)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_OFFS                                            (0x2000)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_RMSK                                                0x3fff
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_ADDR(x))
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_ADDR(x), m)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_WDT_RST_COMPLETION_BMSK                             0x2000
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_WDT_RST_COMPLETION_SHFT                                 13
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_WDT_EXPIRY_BMSK                                     0x1000
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_WDT_EXPIRY_SHFT                                         12
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_DISCONNECTED_BMSK                            0x800
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_DISCONNECTED_SHFT                               11
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_CONNECTED_BMSK                               0x400
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_CONNECTED_SHFT                                  10
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_PERIH_IRQ_LOST_BMSK                                  0x200
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_PERIH_IRQ_LOST_SHFT                                      9
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_UNEXPECTED_SSC_BMSK                                  0x100
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_UNEXPECTED_SSC_SHFT                                      8
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                  0x80
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                     7
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                   0x40
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                      6
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_FALSE_MASTER_ARBITRATION_WIN_BMSK                     0x20
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_FALSE_MASTER_ARBITRATION_WIN_SHFT                        5
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_FALSE_BUS_REQUEST_BMSK                                0x10
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_FALSE_BUS_REQUEST_SHFT                                   4
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_UNSUPPORTED_COMMAND_BMSK                               0x8
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_UNSUPPORTED_COMMAND_SHFT                                 3
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                      0x4
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                        2
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                      0x2
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                        1
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                     0x1
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_STATUS_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                       0

#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x)                                         ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x2004)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_OFFS                                            (0x2004)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_RMSK                                                0x3fff
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x))
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x), m)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x),v)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x),m,v,HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_IN(x))
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_WDT_RST_COMPLETION_BMSK                             0x2000
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_WDT_RST_COMPLETION_SHFT                                 13
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_WDT_EXPIRY_BMSK                                     0x1000
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_WDT_EXPIRY_SHFT                                         12
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_DISCONNECTED_BMSK                            0x800
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_DISCONNECTED_SHFT                               11
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_CONNECTED_BMSK                               0x400
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_CONNECTED_SHFT                                  10
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_PERIH_IRQ_LOST_BMSK                                  0x200
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_PERIH_IRQ_LOST_SHFT                                      9
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_UNEXPECTED_SSC_BMSK                                  0x100
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_UNEXPECTED_SSC_SHFT                                      8
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                  0x80
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                     7
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                   0x40
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                      6
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_MASTER_ARBITRATION_WIN_BMSK                     0x20
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_MASTER_ARBITRATION_WIN_SHFT                        5
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_BUS_REQUEST_BMSK                                0x10
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_BUS_REQUEST_SHFT                                   4
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_UNSUPPORTED_COMMAND_BMSK                               0x8
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_UNSUPPORTED_COMMAND_SHFT                                 3
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                      0x4
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                        2
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                      0x2
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                        1
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                     0x1
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_ENABLE_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                       0

#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_ADDR(x)                                          ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x2008)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_OFFS                                             (0x2008)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_RMSK                                                 0x3fff
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_ADDR(x),v)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_WDT_RST_COMPLETION_BMSK                              0x2000
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_WDT_RST_COMPLETION_SHFT                                  13
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_WDT_EXPIRY_BMSK                                      0x1000
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_WDT_EXPIRY_SHFT                                          12
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_DISCONNECTED_BMSK                             0x800
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_DISCONNECTED_SHFT                                11
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_CONNECTED_BMSK                                0x400
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_CONNECTED_SHFT                                   10
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_PERIH_IRQ_LOST_BMSK                                   0x200
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_PERIH_IRQ_LOST_SHFT                                       9
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_UNEXPECTED_SSC_BMSK                                   0x100
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_UNEXPECTED_SSC_SHFT                                       8
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                   0x80
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                      7
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                    0x40
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                       6
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_MASTER_ARBITRATION_WIN_BMSK                      0x20
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_MASTER_ARBITRATION_WIN_SHFT                         5
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_BUS_REQUEST_BMSK                                 0x10
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_BUS_REQUEST_SHFT                                    4
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_UNSUPPORTED_COMMAND_BMSK                                0x8
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_UNSUPPORTED_COMMAND_SHFT                                  3
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                       0x4
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                         2
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                       0x2
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                         1
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                      0x1
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                        0

#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_ADDR(x)                                         ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x200c)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_OFFS                                            (0x200c)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_RMSK                                                0x3fff
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_ADDR(x),v)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_WDT_RST_COMPLETION_BMSK                             0x2000
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_WDT_RST_COMPLETION_SHFT                                 13
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_WDT_EXPIRY_BMSK                                     0x1000
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_WDT_EXPIRY_SHFT                                         12
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_DISCONNECTED_BMSK                            0x800
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_DISCONNECTED_SHFT                               11
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_CONNECTED_BMSK                               0x400
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_CONNECTED_SHFT                                  10
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_PERIH_IRQ_LOST_BMSK                                  0x200
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_PERIH_IRQ_LOST_SHFT                                      9
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_UNEXPECTED_SSC_BMSK                                  0x100
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_UNEXPECTED_SSC_SHFT                                      8
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                  0x80
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                     7
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                   0x40
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                      6
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_MASTER_ARBITRATION_WIN_BMSK                     0x20
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_MASTER_ARBITRATION_WIN_SHFT                        5
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_BUS_REQUEST_BMSK                                0x10
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_BUS_REQUEST_SHFT                                   4
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_UNSUPPORTED_COMMAND_BMSK                               0x8
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_UNSUPPORTED_COMMAND_SHFT                                 3
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                      0x4
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                        2
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                      0x2
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                        1
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                     0x1
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_SET_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                       0

#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_ADDR(x)                                       ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x2010)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_OFFS                                          (0x2010)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_RMSK                                              0x3fff
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_ADDR(x),v)
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_RST_COMPLETION_BMSK                           0x2000
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_RST_COMPLETION_SHFT                               13
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_EXPIRY_BMSK                                   0x1000
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_EXPIRY_SHFT                                       12
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_DISCONNECTED_BMSK                          0x800
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_DISCONNECTED_SHFT                             11
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_CONNECTED_BMSK                             0x400
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_CONNECTED_SHFT                                10
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_PERIH_IRQ_LOST_BMSK                                0x200
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_PERIH_IRQ_LOST_SHFT                                    9
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNEXPECTED_SSC_BMSK                                0x100
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNEXPECTED_SSC_SHFT                                    8
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                0x80
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                   7
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                 0x40
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                    6
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_MASTER_ARBITRATION_WIN_BMSK                   0x20
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_MASTER_ARBITRATION_WIN_SHFT                      5
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_BUS_REQUEST_BMSK                              0x10
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_BUS_REQUEST_SHFT                                 4
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNSUPPORTED_COMMAND_BMSK                             0x8
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNSUPPORTED_COMMAND_SHFT                               3
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                    0x4
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                      2
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                    0x2
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                      1
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                   0x1
#define HWIO_SPMI1_SPMI_PROTOCOL_IRQ_EN_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                     0

#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_ADDR(x)                                               ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x3000)
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_OFFS                                                  (0x3000)
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_RMSK                                                       0x3ff
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_TEST_BUS_CTRL_ADDR(x))
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_TEST_BUS_CTRL_ADDR(x), m)
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_TEST_BUS_CTRL_ADDR(x),v)
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_TEST_BUS_CTRL_ADDR(x),m,v,HWIO_SPMI1_SPMI_TEST_BUS_CTRL_IN(x))
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_TEST_BUS_ARB_SEL_BMSK                                      0x3c0
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_TEST_BUS_ARB_SEL_SHFT                                          6
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_TEST_BUS_INT_SEL_BMSK                                       0x3c
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_TEST_BUS_INT_SEL_SHFT                                          2
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_TEST_BUS_SEL_BMSK                                            0x3
#define HWIO_SPMI1_SPMI_TEST_BUS_CTRL_TEST_BUS_SEL_SHFT                                              0

#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_ADDR(x)                                           ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x3004)
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_OFFS                                              (0x3004)
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_RMSK                                                     0x7
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_ADDR(x))
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_ADDR(x), m)
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_ADDR(x),v)
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_ADDR(x),m,v,HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_IN(x))
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_HW_SW_EVENTS_SEL_BMSK                                    0x7
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_CTRL_HW_SW_EVENTS_SEL_SHFT                                      0

#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,j)                              ((base) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0X3008 + (0x4*(j)))
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_OFFS(j)                                   (0X3008 + (0x4*(j)))
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_RMSK                                      0x81818181
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_INI(base,j)                \
                in_dword_masked(HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,j), HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_RMSK)
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_INMI(base,j,mask)        \
                in_dword_masked(HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,j), mask)
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_OUTI(base,j,val)        \
                out_dword(HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,j),val)
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_OUTMI(base,j,mask,val) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,j),mask,val,HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_INI(base,j))
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_D_BMSK                       0x80000000
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_D_SHFT                               31
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_D_BMSK                       0x1000000
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_D_SHFT                              24
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_C_BMSK                         0x800000
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_C_SHFT                               23
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_C_BMSK                         0x10000
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_C_SHFT                              16
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_B_BMSK                           0x8000
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_B_SHFT                               15
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_B_BMSK                           0x100
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_B_SHFT                               8
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_A_BMSK                             0x80
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_A_SHFT                                7
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_A_BMSK                             0x1
#define HWIO_SPMI1_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_A_SHFT                               0

#define HWIO_SPMI1_SPMI_DEBUG_REG_ADDR(x)                                                   ((x) + SPMI1_SPMI_CFG_REG_BASE_OFFS + 0x3028)
#define HWIO_SPMI1_SPMI_DEBUG_REG_OFFS                                                      (0x3028)
#define HWIO_SPMI1_SPMI_DEBUG_REG_RMSK                                                      0xffffffff
#define HWIO_SPMI1_SPMI_DEBUG_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_DEBUG_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_DEBUG_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_DEBUG_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_DEBUG_REG_TEST_BUS_BMSK                                             0xffffffff
#define HWIO_SPMI1_SPMI_DEBUG_REG_TEST_BUS_SHFT                                                      0

/*----------------------------------------------------------------------------
 * MODULE: SPMI1_SPMI_PIC_OWNER
 *--------------------------------------------------------------------------*/

#define SPMI1_SPMI_PIC_OWNER_REG_BASE_OFFS                                  0xd0000

#define HWIO_SPMI1_SPMI_PIC_OWNERm_ACC_STATUSn_ADDR(base,m,n)               ((base) + SPMI1_SPMI_PIC_OWNER_REG_BASE_OFFS + 0X0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_SPMI1_SPMI_PIC_OWNERm_ACC_STATUSn_OFFS(m,n)                    (0X0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_SPMI1_SPMI_PIC_OWNERm_ACC_STATUSn_RMSK                         0xffffffff
#define HWIO_SPMI1_SPMI_PIC_OWNERm_ACC_STATUSn_INI2(base,m,n)                \
                in_dword_masked(HWIO_SPMI1_SPMI_PIC_OWNERm_ACC_STATUSn_ADDR(base,m,n), HWIO_SPMI1_SPMI_PIC_OWNERm_ACC_STATUSn_RMSK)
#define HWIO_SPMI1_SPMI_PIC_OWNERm_ACC_STATUSn_INMI2(base,m,n,mask)        \
                in_dword_masked(HWIO_SPMI1_SPMI_PIC_OWNERm_ACC_STATUSn_ADDR(base,m,n), mask)
#define HWIO_SPMI1_SPMI_PIC_OWNERm_ACC_STATUSn_INT_ACC_STATUS_BMSK          0xffffffff
#define HWIO_SPMI1_SPMI_PIC_OWNERm_ACC_STATUSn_INT_ACC_STATUS_SHFT                   0

/*----------------------------------------------------------------------------
 * MODULE: SPMI1_SPMI_SPMI_GENI_CFG
 *--------------------------------------------------------------------------*/

#define SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS                                   0x31000

#define HWIO_SPMI1_SPMI_GENI_CLK_CTRL_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x0)
#define HWIO_SPMI1_SPMI_GENI_CLK_CTRL_OFFS                                       (0x0)
#define HWIO_SPMI1_SPMI_GENI_CLK_CTRL_RMSK                                              0x1
#define HWIO_SPMI1_SPMI_GENI_CLK_CTRL_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CLK_CTRL_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CLK_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CLK_CTRL_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CLK_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CLK_CTRL_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CLK_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CLK_CTRL_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CLK_CTRL_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CLK_CTRL_SER_CLK_SEL_BMSK                                  0x1
#define HWIO_SPMI1_SPMI_GENI_CLK_CTRL_SER_CLK_SEL_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_HW_VERSION_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4)
#define HWIO_SPMI1_SPMI_GENI_HW_VERSION_OFFS                                     (0x4)
#define HWIO_SPMI1_SPMI_GENI_HW_VERSION_RMSK                                     0xffffffff
#define HWIO_SPMI1_SPMI_GENI_HW_VERSION_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_HW_VERSION_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_HW_VERSION_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_HW_VERSION_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_HW_VERSION_MAJOR_BMSK                               0xf0000000
#define HWIO_SPMI1_SPMI_GENI_HW_VERSION_MAJOR_SHFT                                       28
#define HWIO_SPMI1_SPMI_GENI_HW_VERSION_MINOR_BMSK                                0xfff0000
#define HWIO_SPMI1_SPMI_GENI_HW_VERSION_MINOR_SHFT                                       16
#define HWIO_SPMI1_SPMI_GENI_HW_VERSION_STEP_BMSK                                    0xffff
#define HWIO_SPMI1_SPMI_GENI_HW_VERSION_STEP_SHFT                                         0

#define HWIO_SPMI1_SPMI_GENI_FW_REVISION_ADDR(x)                                 ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x8)
#define HWIO_SPMI1_SPMI_GENI_FW_REVISION_OFFS                                    (0x8)
#define HWIO_SPMI1_SPMI_GENI_FW_REVISION_RMSK                                        0xffff
#define HWIO_SPMI1_SPMI_GENI_FW_REVISION_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_FW_REVISION_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_FW_REVISION_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_FW_REVISION_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_FW_REVISION_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_FW_REVISION_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_FW_REVISION_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_FW_REVISION_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_FW_REVISION_IN(x))
#define HWIO_SPMI1_SPMI_GENI_FW_REVISION_PROTOCOL_BMSK                               0xffc0
#define HWIO_SPMI1_SPMI_GENI_FW_REVISION_PROTOCOL_SHFT                                    6
#define HWIO_SPMI1_SPMI_GENI_FW_REVISION_VERSION_BMSK                                  0x3f
#define HWIO_SPMI1_SPMI_GENI_FW_REVISION_VERSION_SHFT                                     0

#define HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_ADDR(x)                               ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0xc)
#define HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_OFFS                                  (0xc)
#define HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_RMSK                                      0xffff
#define HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_IN(x))
#define HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_PROTOCOL_BMSK                             0xffc0
#define HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_PROTOCOL_SHFT                                  6
#define HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_VERSION_BMSK                                0x3f
#define HWIO_SPMI1_SPMI_GENI_S_FW_REVISION_VERSION_SHFT                                   0

#define HWIO_SPMI1_SPMI_GENI_FORCE_DEFAULT_REG_ADDR(x)                           ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x10)
#define HWIO_SPMI1_SPMI_GENI_FORCE_DEFAULT_REG_OFFS                              (0x10)
#define HWIO_SPMI1_SPMI_GENI_FORCE_DEFAULT_REG_RMSK                                     0x1
#define HWIO_SPMI1_SPMI_GENI_FORCE_DEFAULT_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_FORCE_DEFAULT_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_FORCE_DEFAULT_REG_FORCE_DEFAULT_BMSK                       0x1
#define HWIO_SPMI1_SPMI_GENI_FORCE_DEFAULT_REG_FORCE_DEFAULT_SHFT                         0

#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_ADDR(x)                                 ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x14)
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_OFFS                                    (0x14)
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_RMSK                                           0x7
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_IN(x))
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_SOE2_EN_BMSK                                   0x4
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_SOE2_EN_SHFT                                     2
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_SOE1_EN_BMSK                                   0x2
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_SOE1_EN_SHFT                                     1
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_SOE0_EN_BMSK                                   0x1
#define HWIO_SPMI1_SPMI_GENI_OUTPUT_CTRL_SOE0_EN_SHFT                                     0

#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x18)
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_OFFS                                       (0x18)
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_RMSK                                            0x37f
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CGC_CTRL_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CGC_CTRL_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CGC_CTRL_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CGC_CTRL_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CGC_CTRL_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_PROG_RAM_SCLK_OFF_BMSK                          0x200
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_PROG_RAM_SCLK_OFF_SHFT                              9
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_PROG_RAM_HCLK_OFF_BMSK                          0x100
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_PROG_RAM_HCLK_OFF_SHFT                              8
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_EXT_CLK_CGC_ON_BMSK                              0x40
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_EXT_CLK_CGC_ON_SHFT                                 6
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_RX_CLK_CGC_ON_BMSK                               0x20
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_RX_CLK_CGC_ON_SHFT                                  5
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_TX_CLK_CGC_ON_BMSK                               0x10
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_TX_CLK_CGC_ON_SHFT                                  4
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_SCLK_CGC_ON_BMSK                                  0x8
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_SCLK_CGC_ON_SHFT                                    3
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_DATA_AHB_CLK_CGC_ON_BMSK                          0x4
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_DATA_AHB_CLK_CGC_ON_SHFT                            2
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_CFG_AHB_WR_CLK_CGC_ON_BMSK                        0x2
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_CFG_AHB_WR_CLK_CGC_ON_SHFT                          1
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_CFG_AHB_CLK_CGC_ON_BMSK                           0x1
#define HWIO_SPMI1_SPMI_GENI_CGC_CTRL_CFG_AHB_CLK_CGC_ON_SHFT                             0

#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x1c)
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_OFFS                                       (0x1c)
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_RMSK                                          0xfff11
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CHAR_CFG_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CHAR_CFG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CHAR_CFG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CHAR_CFG_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CHAR_CFG_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_CHAR_MODE_BMSK                                0xff000
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_CHAR_MODE_SHFT                                     12
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_CHAR_STATUS_BMSK                                0xf00
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_CHAR_STATUS_SHFT                                    8
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_DIRECTION_BMSK                                   0x10
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_DIRECTION_SHFT                                      4
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_ENABLE_BMSK                                       0x1
#define HWIO_SPMI1_SPMI_GENI_CHAR_CFG_ENABLE_SHFT                                         0

#define HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_ADDR(base,n)                            ((base) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0X20 + (0x4*(n)))
#define HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_OFFS(n)                                 (0X20 + (0x4*(n)))
#define HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_RMSK                                        0xffff
#define HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_INI(base,n)                \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_ADDR(base,n), HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_RMSK)
#define HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_ADDR(base,n), mask)
#define HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_ADDR(base,n),val)
#define HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_ADDR(base,n),mask,val,HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_INI(base,n))
#define HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_DIN_ACTUAL_BMSK                             0xff00
#define HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_DIN_ACTUAL_SHFT                                  8
#define HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_BMSK                        0xff
#define HWIO_SPMI1_SPMI_GENI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_CTRL_ADDR(x)                                        ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x28)
#define HWIO_SPMI1_SPMI_GENI_CTRL_OFFS                                           (0x28)
#define HWIO_SPMI1_SPMI_GENI_CTRL_RMSK                                                  0x3
#define HWIO_SPMI1_SPMI_GENI_CTRL_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CTRL_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CTRL_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CTRL_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CTRL_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CTRL_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CTRL_S_GENI_DISABLE_BMSK                                   0x2
#define HWIO_SPMI1_SPMI_GENI_CTRL_S_GENI_DISABLE_SHFT                                     1
#define HWIO_SPMI1_SPMI_GENI_CTRL_M_GENI_DISABLE_BMSK                                   0x1
#define HWIO_SPMI1_SPMI_GENI_CTRL_M_GENI_DISABLE_SHFT                                     0

#define HWIO_SPMI1_SPMI_GENI_STATUS_ADDR(x)                                      ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2c)
#define HWIO_SPMI1_SPMI_GENI_STATUS_OFFS                                         (0x2c)
#define HWIO_SPMI1_SPMI_GENI_STATUS_RMSK                                           0x1fffff
#define HWIO_SPMI1_SPMI_GENI_STATUS_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_STATUS_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_STATUS_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_STATUS_S_GENI_CMD_FSM_STATE_BMSK                      0x1f0000
#define HWIO_SPMI1_SPMI_GENI_STATUS_S_GENI_CMD_FSM_STATE_SHFT                            16
#define HWIO_SPMI1_SPMI_GENI_STATUS_NOT_USED_BITS_3_BMSK                             0xe000
#define HWIO_SPMI1_SPMI_GENI_STATUS_NOT_USED_BITS_3_SHFT                                 13
#define HWIO_SPMI1_SPMI_GENI_STATUS_S_GENI_CMD_ACTIVE_BMSK                           0x1000
#define HWIO_SPMI1_SPMI_GENI_STATUS_S_GENI_CMD_ACTIVE_SHFT                               12
#define HWIO_SPMI1_SPMI_GENI_STATUS_NOT_USED_BITS_2_BMSK                              0xe00
#define HWIO_SPMI1_SPMI_GENI_STATUS_NOT_USED_BITS_2_SHFT                                  9
#define HWIO_SPMI1_SPMI_GENI_STATUS_M_GENI_CMD_FSM_STATE_BMSK                         0x1f0
#define HWIO_SPMI1_SPMI_GENI_STATUS_M_GENI_CMD_FSM_STATE_SHFT                             4
#define HWIO_SPMI1_SPMI_GENI_STATUS_NOT_USED_BITS_1_BMSK                                0xe
#define HWIO_SPMI1_SPMI_GENI_STATUS_NOT_USED_BITS_1_SHFT                                  1
#define HWIO_SPMI1_SPMI_GENI_STATUS_M_GENI_CMD_ACTIVE_BMSK                              0x1
#define HWIO_SPMI1_SPMI_GENI_STATUS_M_GENI_CMD_ACTIVE_SHFT                                0

#define HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_ADDR(x)                               ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x30)
#define HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_OFFS                                  (0x30)
#define HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_RMSK                                        0x1f
#define HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_IN(x))
#define HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_TEST_BUS_SEL_BMSK                           0x1f
#define HWIO_SPMI1_SPMI_GENI_TEST_BUS_CTRL_TEST_BUS_SEL_SHFT                              0

#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_ADDR(x)                                 ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x34)
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_OFFS                                    (0x34)
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_RMSK                                     0x3ffffff
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_IN(x))
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_TX_CLK_DIV_VALUE_BMSK                    0x3ffc000
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_TX_CLK_DIV_VALUE_SHFT                           14
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_RX_CLK_DIV_VALUE_BMSK                       0x3ffc
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_RX_CLK_DIV_VALUE_SHFT                            2
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_TX_SER_CLK_EN_BMSK                             0x2
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_TX_SER_CLK_EN_SHFT                               1
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_RX_SER_CLK_EN_BMSK                             0x1
#define HWIO_SPMI1_SPMI_GENI_SER_CLK_CFG_RX_SER_CLK_EN_SHFT                               0

#define HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_ADDR(x)                            ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x38)
#define HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_OFFS                               (0x38)
#define HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_RMSK                                      0xf
#define HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_IN(x))
#define HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_TX_WATERMARK_BMSK                         0xf
#define HWIO_SPMI1_SPMI_GENI_TX_WATERMARK_REG_TX_WATERMARK_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_ADDR(x)                            ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3c)
#define HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_OFFS                               (0x3c)
#define HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_RMSK                                      0xf
#define HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_IN(x))
#define HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_RX_WATERMARK_BMSK                         0xf
#define HWIO_SPMI1_SPMI_GENI_RX_WATERMARK_REG_RX_WATERMARK_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_STOP_REG_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x40)
#define HWIO_SPMI1_SPMI_GENI_STOP_REG_OFFS                                       (0x40)
#define HWIO_SPMI1_SPMI_GENI_STOP_REG_RMSK                                              0x3
#define HWIO_SPMI1_SPMI_GENI_STOP_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_STOP_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_STOP_REG_S_GENI_STOP_BMSK                                  0x2
#define HWIO_SPMI1_SPMI_GENI_STOP_REG_S_GENI_STOP_SHFT                                    1
#define HWIO_SPMI1_SPMI_GENI_STOP_REG_M_GENI_STOP_BMSK                                  0x1
#define HWIO_SPMI1_SPMI_GENI_STOP_REG_M_GENI_STOP_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_ADDR(x)                                 ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x44)
#define HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_OFFS                                    (0x44)
#define HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_RMSK                                           0x7
#define HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_IN(x))
#define HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_SW_COMP_BMSK                                   0x7
#define HWIO_SPMI1_SPMI_GENI_SW_COMP_REG_SW_COMP_SHFT                                     0

#define HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x)                           ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x48)
#define HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_OFFS                              (0x48)
#define HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_RMSK                                     0x1
#define HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_IN(x))
#define HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_PROG_ROM_EN_BMSK                         0x1
#define HWIO_SPMI1_SPMI_GENI_PROG_ROM_CTRL_REG_PROG_ROM_EN_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x100)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_OFFS                                       (0x100)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_RMSK                                       0x3ffff9ff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG0_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG0_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG0_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG0_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG0_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_GENI_TX_MODE_BMSK                          0x20000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_GENI_TX_MODE_SHFT                                  29
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_COND_COMP_IN_0_SEL_RST_VAL_BMSK            0x1fe00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_COND_COMP_IN_0_SEL_RST_VAL_SHFT                    21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_COND_COMP_IN_VEC_BMSK                        0x1fe000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_COND_COMP_IN_VEC_SHFT                              13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_M_DATA_CNT_INIT_VALUE_INCR_BMSK                0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_M_DATA_CNT_INIT_VALUE_INCR_SHFT                    12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_DATA_CNT_MODE_BMSK                              0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_DATA_CNT_MODE_SHFT                                 11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_M_DATA_CNT_EN_BITS_BMSK                         0x1f8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_M_DATA_CNT_EN_BITS_SHFT                             3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_EXT_SECURITY_EN_BMSK                              0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_EXT_SECURITY_EN_SHFT                                2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_EXT_ARB_EN_BMSK                                   0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_EXT_ARB_EN_SHFT                                     1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_M_PROG_RAM_SEC_WORD_EN_BMSK                       0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG0_M_PROG_RAM_SEC_WORD_EN_SHFT                         0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG1_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x104)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG1_OFFS                                       (0x104)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG1_RMSK                                          0x3ffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG1_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG1_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG1_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG1_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG1_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG1_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG1_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG1_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG1_TX_PARAM_TABLE_VEC_1_BMSK                     0x3fe00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG1_TX_PARAM_TABLE_VEC_1_SHFT                           9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG1_TX_PARAM_TABLE_VEC_0_BMSK                       0x1ff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG1_TX_PARAM_TABLE_VEC_0_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG2_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x108)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG2_OFFS                                       (0x108)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG2_RMSK                                          0x3ffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG2_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG2_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG2_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG2_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG2_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG2_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG2_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG2_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG2_TX_PARAM_TABLE_VEC_3_BMSK                     0x3fe00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG2_TX_PARAM_TABLE_VEC_3_SHFT                           9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG2_TX_PARAM_TABLE_VEC_2_BMSK                       0x1ff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG2_TX_PARAM_TABLE_VEC_2_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG3_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x10c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG3_OFFS                                       (0x10c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG3_RMSK                                          0xfffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG3_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG3_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG3_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG3_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG3_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG3_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG3_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG3_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG3_TX_DATA_TABLE_VEC_1_BMSK                      0xffc00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG3_TX_DATA_TABLE_VEC_1_SHFT                           10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG3_TX_DATA_TABLE_VEC_0_BMSK                        0x3ff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG3_TX_DATA_TABLE_VEC_0_SHFT                            0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG4_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x110)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG4_OFFS                                       (0x110)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG4_RMSK                                          0xfffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG4_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG4_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG4_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG4_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG4_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG4_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG4_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG4_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG4_TX_DATA_TABLE_VEC_3_BMSK                      0xffc00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG4_TX_DATA_TABLE_VEC_3_SHFT                           10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG4_TX_DATA_TABLE_VEC_2_BMSK                        0x3ff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG4_TX_DATA_TABLE_VEC_2_SHFT                            0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x114)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_OFFS                                       (0x114)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_RMSK                                       0x3fdc03ff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG5_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG5_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG5_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG5_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG5_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_DRIVE_DEFAULT_ON_START_EN_BMSK             0x20000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_DRIVE_DEFAULT_ON_START_EN_SHFT                     29
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_BP_MODE_BMSK                            0x10000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_BP_MODE_SHFT                                    28
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_SOE_EDGE_SEL_BMSK                        0x8000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_SOE_EDGE_SEL_SHFT                               27
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_SOUT_EDGE_SEL_BMSK                       0x4000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_SOUT_EDGE_SEL_SHFT                              26
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_DEFAULT_PRIM_SOE_VALUE_BMSK              0x2000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_DEFAULT_PRIM_SOE_VALUE_SHFT                     25
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_DEFAULT_PRIM_SOUT_VALUE_BMSK             0x1000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_DEFAULT_PRIM_SOUT_VALUE_SHFT                    24
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_DEFAULT_SOE_VALUE_BMSK                    0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_DEFAULT_SOE_VALUE_SHFT                          23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_DEFAULT_SOUT_VALUE_BMSK                   0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_DEFAULT_SOUT_VALUE_SHFT                         22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_CONST1_EFF_SIZE_BMSK                      0x1c0000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_CONST1_EFF_SIZE_SHFT                            18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_CONST1_REG_BMSK                              0x3fc
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_CONST1_REG_SHFT                                  2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_PAR_MODE_BMSK                                  0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_PAR_MODE_SHFT                                    1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_PAR_CALC_EN_BMSK                               0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG5_TX_PAR_CALC_EN_SHFT                                 0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x118)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_OFFS                                       (0x118)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_RMSK                                       0xe3fbfd3f
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG6_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG6_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG6_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG6_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG6_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_M_TIME_CNT_FR_DIV_BMSK                     0xc0000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_M_TIME_CNT_FR_DIV_SHFT                             30
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_M_TIME_CNT_EN_FR_SEL_BMSK                  0x20000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_M_TIME_CNT_EN_FR_SEL_SHFT                          29
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_M_GP_CNT_INIT_VAL_BMSK                      0x3e00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_M_GP_CNT_INIT_VAL_SHFT                             21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_M_GP_CNT_DIRECTION_BMSK                      0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_M_GP_CNT_DIRECTION_SHFT                            20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_START_VAL_BMSK                  0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_START_VAL_SHFT                       19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_STOP_DUR_BMSK                   0x30000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_STOP_DUR_SHFT                        16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_EN_BMSK                          0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_SOUT_MODUL_EN_SHFT                              15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_LOAD_PAR_EN_BMSK                            0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_LOAD_PAR_EN_SHFT                                14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_PARAM_DUMMY_PAR_EN_BMSK                     0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_PARAM_DUMMY_PAR_EN_SHFT                         13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_PARAM_PAR_EN_BMSK                           0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_PARAM_PAR_EN_SHFT                               12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_FIFO_DUMMY_PAR_EN_BMSK                       0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_FIFO_DUMMY_PAR_EN_SHFT                          11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_FIFO_PAR_EN_BMSK                             0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_TX_FIFO_PAR_EN_SHFT                                10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_CONST_EFF_SIZE_BMSK                         0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_CONST_EFF_SIZE_SHFT                             8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_CONST_REG_BMSK                               0x30
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_CONST_REG_SHFT                                  4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_DEFAULT_PRIM_SOE_VALUE_BMSK                   0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_DEFAULT_PRIM_SOE_VALUE_SHFT                     3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_DEFAULT_PRIM_SOUT_VALUE_BMSK                  0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_DEFAULT_PRIM_SOUT_VALUE_SHFT                    2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_DEFAULT_SOE_VALUE_BMSK                        0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_DEFAULT_SOE_VALUE_SHFT                          1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_DEFAULT_SOUT_VALUE_BMSK                       0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG6_IO2_DEFAULT_SOUT_VALUE_SHFT                         0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x11c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_OFFS                                       (0x11c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_RMSK                                        0x7efffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG7_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG7_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG7_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG7_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG7_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_GENI_RX_MODE_BMSK                           0x4000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_GENI_RX_MODE_SHFT                                  26
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_RX_PAR_MODE_BMSK                            0x2000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_RX_PAR_MODE_SHFT                                   25
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_RX_PAR_CALC_EN_BMSK                         0x1000000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_RX_PAR_CALC_EN_SHFT                                24
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_RX_IO_SIN_SEL_BMSK                           0xe00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_RX_IO_SIN_SEL_SHFT                                 21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_RX_SIN_SEL_BMSK                               0xc0000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_RX_SIN_SEL_SHFT                                    18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_RX_DATA_SRC_BMSK                              0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_RX_DATA_SRC_SHFT                                   17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_S_COND_COMP_IN_0_SEL_RST_VAL_BMSK             0x1fe00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_S_COND_COMP_IN_0_SEL_RST_VAL_SHFT                   9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_S_COND_COMP_IN_VEC_BMSK                         0x1fe
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_S_COND_COMP_IN_VEC_SHFT                             1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_S_DATA_CNT_MODE_BMSK                              0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG7_S_DATA_CNT_MODE_SHFT                                0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x120)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_OFFS                                       (0x120)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_RMSK                                           0xfe7f
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG8_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG8_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG8_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG8_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG8_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_S_GP_CNT_INIT_VAL_BMSK                         0xf800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_S_GP_CNT_INIT_VAL_SHFT                             11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_S_GP_CNT_DIRECTION_BMSK                         0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_S_GP_CNT_DIRECTION_SHFT                            10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_S_DATA_CNT_INIT_VALUE_INCR_BMSK                 0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_S_DATA_CNT_INIT_VALUE_INCR_SHFT                     9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_S_DATA_CNT_EN_BITS_BMSK                          0x7e
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_S_DATA_CNT_EN_BITS_SHFT                             1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_S_PROG_RAM_SEC_WORD_EN_BMSK                       0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG8_S_PROG_RAM_SEC_WORD_EN_SHFT                         0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG9_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x124)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG9_OFFS                                       (0x124)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG9_RMSK                                          0xfffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG9_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG9_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG9_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG9_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG9_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG9_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG9_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG9_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG9_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG9_RX_DATA_TABLE_VEC_1_BMSK                      0xffc00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG9_RX_DATA_TABLE_VEC_1_SHFT                           10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG9_RX_DATA_TABLE_VEC_0_BMSK                        0x3ff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG9_RX_DATA_TABLE_VEC_0_SHFT                            0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG10_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x128)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG10_OFFS                                      (0x128)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG10_RMSK                                         0xfffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG10_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG10_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG10_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG10_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG10_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG10_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG10_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG10_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG10_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG10_RX_DATA_TABLE_VEC_3_BMSK                     0xffc00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG10_RX_DATA_TABLE_VEC_3_SHFT                          10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG10_RX_DATA_TABLE_VEC_2_BMSK                       0x3ff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG10_RX_DATA_TABLE_VEC_2_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x12c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_OFFS                                      (0x12c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG11_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG11_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG11_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG11_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG11_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_11_TX_DURATION_BMSK                    0xc00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_11_TX_DURATION_SHFT                          22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_10_TX_DURATION_BMSK                    0x300000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_10_TX_DURATION_SHFT                          20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_9_TX_DURATION_BMSK                      0xc0000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_9_TX_DURATION_SHFT                           18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_8_TX_DURATION_BMSK                      0x30000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_8_TX_DURATION_SHFT                           16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_7_TX_DURATION_BMSK                       0xc000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_7_TX_DURATION_SHFT                           14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_6_TX_DURATION_BMSK                       0x3000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_6_TX_DURATION_SHFT                           12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_5_TX_DURATION_BMSK                        0xc00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_5_TX_DURATION_SHFT                           10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_4_TX_DURATION_BMSK                        0x300
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_4_TX_DURATION_SHFT                            8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_3_TX_DURATION_BMSK                         0xc0
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_3_TX_DURATION_SHFT                            6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_2_TX_DURATION_BMSK                         0x30
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_2_TX_DURATION_SHFT                            4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_1_TX_DURATION_BMSK                          0xc
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_1_TX_DURATION_SHFT                            2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_0_TX_DURATION_BMSK                          0x3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG11_PRIM_0_TX_DURATION_SHFT                            0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x130)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_OFFS                                      (0x130)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG12_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG12_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG12_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG12_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG12_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_23_TX_DURATION_BMSK                    0xc00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_23_TX_DURATION_SHFT                          22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_22_TX_DURATION_BMSK                    0x300000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_22_TX_DURATION_SHFT                          20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_21_TX_DURATION_BMSK                     0xc0000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_21_TX_DURATION_SHFT                          18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_20_TX_DURATION_BMSK                     0x30000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_20_TX_DURATION_SHFT                          16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_19_TX_DURATION_BMSK                      0xc000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_19_TX_DURATION_SHFT                          14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_18_TX_DURATION_BMSK                      0x3000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_18_TX_DURATION_SHFT                          12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_17_TX_DURATION_BMSK                       0xc00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_17_TX_DURATION_SHFT                          10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_16_TX_DURATION_BMSK                       0x300
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_16_TX_DURATION_SHFT                           8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_15_TX_DURATION_BMSK                        0xc0
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_15_TX_DURATION_SHFT                           6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_14_TX_DURATION_BMSK                        0x30
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_14_TX_DURATION_SHFT                           4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_13_TX_DURATION_BMSK                         0xc
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_13_TX_DURATION_SHFT                           2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_12_TX_DURATION_BMSK                         0x3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG12_PRIM_12_TX_DURATION_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x134)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_OFFS                                      (0x134)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG13_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG13_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG13_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG13_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG13_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_11_RX_DURATION_BMSK                    0xc00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_11_RX_DURATION_SHFT                          22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_10_RX_DURATION_BMSK                    0x300000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_10_RX_DURATION_SHFT                          20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_9_RX_DURATION_BMSK                      0xc0000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_9_RX_DURATION_SHFT                           18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_8_RX_DURATION_BMSK                      0x30000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_8_RX_DURATION_SHFT                           16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_7_RX_DURATION_BMSK                       0xc000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_7_RX_DURATION_SHFT                           14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_6_RX_DURATION_BMSK                       0x3000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_6_RX_DURATION_SHFT                           12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_5_RX_DURATION_BMSK                        0xc00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_5_RX_DURATION_SHFT                           10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_4_RX_DURATION_BMSK                        0x300
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_4_RX_DURATION_SHFT                            8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_3_RX_DURATION_BMSK                         0xc0
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_3_RX_DURATION_SHFT                            6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_2_RX_DURATION_BMSK                         0x30
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_2_RX_DURATION_SHFT                            4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_1_RX_DURATION_BMSK                          0xc
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_1_RX_DURATION_SHFT                            2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_0_RX_DURATION_BMSK                          0x3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG13_PRIM_0_RX_DURATION_SHFT                            0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x138)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_OFFS                                      (0x138)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG14_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG14_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG14_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG14_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG14_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_23_RX_DURATION_BMSK                    0xc00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_23_RX_DURATION_SHFT                          22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_22_RX_DURATION_BMSK                    0x300000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_22_RX_DURATION_SHFT                          20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_21_RX_DURATION_BMSK                     0xc0000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_21_RX_DURATION_SHFT                          18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_20_RX_DURATION_BMSK                     0x30000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_20_RX_DURATION_SHFT                          16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_19_RX_DURATION_BMSK                      0xc000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_19_RX_DURATION_SHFT                          14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_18_RX_DURATION_BMSK                      0x3000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_18_RX_DURATION_SHFT                          12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_17_RX_DURATION_BMSK                       0xc00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_17_RX_DURATION_SHFT                          10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_16_RX_DURATION_BMSK                       0x300
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_16_RX_DURATION_SHFT                           8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_15_RX_DURATION_BMSK                        0xc0
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_15_RX_DURATION_SHFT                           6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_14_RX_DURATION_BMSK                        0x30
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_14_RX_DURATION_SHFT                           4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_13_RX_DURATION_BMSK                         0xc
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_13_RX_DURATION_SHFT                           2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_12_RX_DURATION_BMSK                         0x3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG14_PRIM_12_RX_DURATION_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x13c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_OFFS                                      (0x13c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG15_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG15_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG15_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG15_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG15_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_7_TX_FUNC_SEL_BMSK                     0xe00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_7_TX_FUNC_SEL_SHFT                           21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_6_TX_FUNC_SEL_BMSK                     0x1c0000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_6_TX_FUNC_SEL_SHFT                           18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_5_TX_FUNC_SEL_BMSK                      0x38000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_5_TX_FUNC_SEL_SHFT                           15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_4_TX_FUNC_SEL_BMSK                       0x7000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_4_TX_FUNC_SEL_SHFT                           12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_3_TX_FUNC_SEL_BMSK                        0xe00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_3_TX_FUNC_SEL_SHFT                            9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_2_TX_FUNC_SEL_BMSK                        0x1c0
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_2_TX_FUNC_SEL_SHFT                            6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_1_TX_FUNC_SEL_BMSK                         0x38
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_1_TX_FUNC_SEL_SHFT                            3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_0_TX_FUNC_SEL_BMSK                          0x7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG15_PRIM_0_TX_FUNC_SEL_SHFT                            0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x140)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_OFFS                                      (0x140)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG16_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG16_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG16_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG16_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG16_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_15_TX_FUNC_SEL_BMSK                    0xe00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_15_TX_FUNC_SEL_SHFT                          21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_14_TX_FUNC_SEL_BMSK                    0x1c0000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_14_TX_FUNC_SEL_SHFT                          18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_13_TX_FUNC_SEL_BMSK                     0x38000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_13_TX_FUNC_SEL_SHFT                          15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_12_TX_FUNC_SEL_BMSK                      0x7000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_12_TX_FUNC_SEL_SHFT                          12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_11_TX_FUNC_SEL_BMSK                       0xe00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_11_TX_FUNC_SEL_SHFT                           9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_10_TX_FUNC_SEL_BMSK                       0x1c0
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_10_TX_FUNC_SEL_SHFT                           6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_9_TX_FUNC_SEL_BMSK                         0x38
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_9_TX_FUNC_SEL_SHFT                            3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_8_TX_FUNC_SEL_BMSK                          0x7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG16_PRIM_8_TX_FUNC_SEL_SHFT                            0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x144)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_OFFS                                      (0x144)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG17_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG17_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG17_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG17_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG17_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_23_TX_FUNC_SEL_BMSK                    0xe00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_23_TX_FUNC_SEL_SHFT                          21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_22_TX_FUNC_SEL_BMSK                    0x1c0000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_22_TX_FUNC_SEL_SHFT                          18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_21_TX_FUNC_SEL_BMSK                     0x38000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_21_TX_FUNC_SEL_SHFT                          15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_20_TX_FUNC_SEL_BMSK                      0x7000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_20_TX_FUNC_SEL_SHFT                          12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_19_TX_FUNC_SEL_BMSK                       0xe00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_19_TX_FUNC_SEL_SHFT                           9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_18_TX_FUNC_SEL_BMSK                       0x1c0
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_18_TX_FUNC_SEL_SHFT                           6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_17_TX_FUNC_SEL_BMSK                        0x38
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_17_TX_FUNC_SEL_SHFT                           3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_16_TX_FUNC_SEL_BMSK                         0x7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG17_PRIM_16_TX_FUNC_SEL_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x148)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_OFFS                                      (0x148)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG18_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG18_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG18_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG18_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG18_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_23_TX_PAR_FIRST_BMSK                   0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_23_TX_PAR_FIRST_SHFT                         23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_22_TX_PAR_FIRST_BMSK                   0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_22_TX_PAR_FIRST_SHFT                         22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_21_TX_PAR_FIRST_BMSK                   0x200000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_21_TX_PAR_FIRST_SHFT                         21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_20_TX_PAR_FIRST_BMSK                   0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_20_TX_PAR_FIRST_SHFT                         20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_19_TX_PAR_FIRST_BMSK                    0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_19_TX_PAR_FIRST_SHFT                         19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_18_TX_PAR_FIRST_BMSK                    0x40000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_18_TX_PAR_FIRST_SHFT                         18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_17_TX_PAR_FIRST_BMSK                    0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_17_TX_PAR_FIRST_SHFT                         17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_16_TX_PAR_FIRST_BMSK                    0x10000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_16_TX_PAR_FIRST_SHFT                         16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_15_TX_PAR_FIRST_BMSK                     0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_15_TX_PAR_FIRST_SHFT                         15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_14_TX_PAR_FIRST_BMSK                     0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_14_TX_PAR_FIRST_SHFT                         14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_13_TX_PAR_FIRST_BMSK                     0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_13_TX_PAR_FIRST_SHFT                         13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_12_TX_PAR_FIRST_BMSK                     0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_12_TX_PAR_FIRST_SHFT                         12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_11_TX_PAR_FIRST_BMSK                      0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_11_TX_PAR_FIRST_SHFT                         11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_10_TX_PAR_FIRST_BMSK                      0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_10_TX_PAR_FIRST_SHFT                         10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_9_TX_PAR_FIRST_BMSK                       0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_9_TX_PAR_FIRST_SHFT                           9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_8_TX_PAR_FIRST_BMSK                       0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_8_TX_PAR_FIRST_SHFT                           8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_7_TX_PAR_FIRST_BMSK                        0x80
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_7_TX_PAR_FIRST_SHFT                           7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_6_TX_PAR_FIRST_BMSK                        0x40
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_6_TX_PAR_FIRST_SHFT                           6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_5_TX_PAR_FIRST_BMSK                        0x20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_5_TX_PAR_FIRST_SHFT                           5
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_4_TX_PAR_FIRST_BMSK                        0x10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_4_TX_PAR_FIRST_SHFT                           4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_3_TX_PAR_FIRST_BMSK                         0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_3_TX_PAR_FIRST_SHFT                           3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_2_TX_PAR_FIRST_BMSK                         0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_2_TX_PAR_FIRST_SHFT                           2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_1_TX_PAR_FIRST_BMSK                         0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_1_TX_PAR_FIRST_SHFT                           1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_0_TX_PAR_FIRST_BMSK                         0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG18_PRIM_0_TX_PAR_FIRST_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x14c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_OFFS                                      (0x14c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG19_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG19_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG19_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG19_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG19_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_23_TX_DUMMY_DATA_EN_BMSK               0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_23_TX_DUMMY_DATA_EN_SHFT                     23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_22_TX_DUMMY_DATA_EN_BMSK               0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_22_TX_DUMMY_DATA_EN_SHFT                     22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_21_TX_DUMMY_DATA_EN_BMSK               0x200000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_21_TX_DUMMY_DATA_EN_SHFT                     21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_20_TX_DUMMY_DATA_EN_BMSK               0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_20_TX_DUMMY_DATA_EN_SHFT                     20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_19_TX_DUMMY_DATA_EN_BMSK                0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_19_TX_DUMMY_DATA_EN_SHFT                     19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_18_TX_DUMMY_DATA_EN_BMSK                0x40000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_18_TX_DUMMY_DATA_EN_SHFT                     18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_17_TX_DUMMY_DATA_EN_BMSK                0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_17_TX_DUMMY_DATA_EN_SHFT                     17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_16_TX_DUMMY_DATA_EN_BMSK                0x10000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_16_TX_DUMMY_DATA_EN_SHFT                     16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_15_TX_DUMMY_DATA_EN_BMSK                 0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_15_TX_DUMMY_DATA_EN_SHFT                     15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_14_TX_DUMMY_DATA_EN_BMSK                 0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_14_TX_DUMMY_DATA_EN_SHFT                     14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_13_TX_DUMMY_DATA_EN_BMSK                 0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_13_TX_DUMMY_DATA_EN_SHFT                     13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_12_TX_DUMMY_DATA_EN_BMSK                 0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_12_TX_DUMMY_DATA_EN_SHFT                     12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_11_TX_DUMMY_DATA_EN_BMSK                  0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_11_TX_DUMMY_DATA_EN_SHFT                     11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_10_TX_DUMMY_DATA_EN_BMSK                  0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_10_TX_DUMMY_DATA_EN_SHFT                     10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_9_TX_DUMMY_DATA_EN_BMSK                   0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_9_TX_DUMMY_DATA_EN_SHFT                       9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_8_TX_DUMMY_DATA_EN_BMSK                   0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_8_TX_DUMMY_DATA_EN_SHFT                       8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_7_TX_DUMMY_DATA_EN_BMSK                    0x80
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_7_TX_DUMMY_DATA_EN_SHFT                       7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_6_TX_DUMMY_DATA_EN_BMSK                    0x40
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_6_TX_DUMMY_DATA_EN_SHFT                       6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_5_TX_DUMMY_DATA_EN_BMSK                    0x20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_5_TX_DUMMY_DATA_EN_SHFT                       5
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_4_TX_DUMMY_DATA_EN_BMSK                    0x10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_4_TX_DUMMY_DATA_EN_SHFT                       4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_3_TX_DUMMY_DATA_EN_BMSK                     0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_3_TX_DUMMY_DATA_EN_SHFT                       3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_2_TX_DUMMY_DATA_EN_BMSK                     0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_2_TX_DUMMY_DATA_EN_SHFT                       2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_1_TX_DUMMY_DATA_EN_BMSK                     0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_1_TX_DUMMY_DATA_EN_SHFT                       1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_0_TX_DUMMY_DATA_EN_BMSK                     0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG19_PRIM_0_TX_DUMMY_DATA_EN_SHFT                       0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x150)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_OFFS                                      (0x150)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG20_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG20_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG20_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG20_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG20_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_23_TX_DUMMY_PARAM_EN_BMSK              0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_23_TX_DUMMY_PARAM_EN_SHFT                    23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_22_TX_DUMMY_PARAM_EN_BMSK              0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_22_TX_DUMMY_PARAM_EN_SHFT                    22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_21_TX_DUMMY_PARAM_EN_BMSK              0x200000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_21_TX_DUMMY_PARAM_EN_SHFT                    21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_20_TX_DUMMY_PARAM_EN_BMSK              0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_20_TX_DUMMY_PARAM_EN_SHFT                    20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_19_TX_DUMMY_PARAM_EN_BMSK               0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_19_TX_DUMMY_PARAM_EN_SHFT                    19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_18_TX_DUMMY_PARAM_EN_BMSK               0x40000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_18_TX_DUMMY_PARAM_EN_SHFT                    18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_17_TX_DUMMY_PARAM_EN_BMSK               0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_17_TX_DUMMY_PARAM_EN_SHFT                    17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_16_TX_DUMMY_PARAM_EN_BMSK               0x10000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_16_TX_DUMMY_PARAM_EN_SHFT                    16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_15_TX_DUMMY_PARAM_EN_BMSK                0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_15_TX_DUMMY_PARAM_EN_SHFT                    15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_14_TX_DUMMY_PARAM_EN_BMSK                0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_14_TX_DUMMY_PARAM_EN_SHFT                    14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_13_TX_DUMMY_PARAM_EN_BMSK                0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_13_TX_DUMMY_PARAM_EN_SHFT                    13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_12_TX_DUMMY_PARAM_EN_BMSK                0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_12_TX_DUMMY_PARAM_EN_SHFT                    12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_11_TX_DUMMY_PARAM_EN_BMSK                 0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_11_TX_DUMMY_PARAM_EN_SHFT                    11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_10_TX_DUMMY_PARAM_EN_BMSK                 0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_10_TX_DUMMY_PARAM_EN_SHFT                    10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_9_TX_DUMMY_PARAM_EN_BMSK                  0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_9_TX_DUMMY_PARAM_EN_SHFT                      9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_8_TX_DUMMY_PARAM_EN_BMSK                  0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_8_TX_DUMMY_PARAM_EN_SHFT                      8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_7_TX_DUMMY_PARAM_EN_BMSK                   0x80
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_7_TX_DUMMY_PARAM_EN_SHFT                      7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_6_TX_DUMMY_PARAM_EN_BMSK                   0x40
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_6_TX_DUMMY_PARAM_EN_SHFT                      6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_5_TX_DUMMY_PARAM_EN_BMSK                   0x20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_5_TX_DUMMY_PARAM_EN_SHFT                      5
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_4_TX_DUMMY_PARAM_EN_BMSK                   0x10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_4_TX_DUMMY_PARAM_EN_SHFT                      4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_3_TX_DUMMY_PARAM_EN_BMSK                    0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_3_TX_DUMMY_PARAM_EN_SHFT                      3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_2_TX_DUMMY_PARAM_EN_BMSK                    0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_2_TX_DUMMY_PARAM_EN_SHFT                      2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_1_TX_DUMMY_PARAM_EN_BMSK                    0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_1_TX_DUMMY_PARAM_EN_SHFT                      1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_0_TX_DUMMY_PARAM_EN_BMSK                    0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG20_PRIM_0_TX_DUMMY_PARAM_EN_SHFT                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x154)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_OFFS                                      (0x154)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG21_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG21_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG21_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG21_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG21_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_23_RX_SI_EN_BMSK                       0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_23_RX_SI_EN_SHFT                             23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_22_RX_SI_EN_BMSK                       0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_22_RX_SI_EN_SHFT                             22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_21_RX_SI_EN_BMSK                       0x200000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_21_RX_SI_EN_SHFT                             21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_20_RX_SI_EN_BMSK                       0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_20_RX_SI_EN_SHFT                             20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_19_RX_SI_EN_BMSK                        0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_19_RX_SI_EN_SHFT                             19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_18_RX_SI_EN_BMSK                        0x40000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_18_RX_SI_EN_SHFT                             18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_17_RX_SI_EN_BMSK                        0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_17_RX_SI_EN_SHFT                             17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_16_RX_SI_EN_BMSK                        0x10000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_16_RX_SI_EN_SHFT                             16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_15_RX_SI_EN_BMSK                         0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_15_RX_SI_EN_SHFT                             15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_14_RX_SI_EN_BMSK                         0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_14_RX_SI_EN_SHFT                             14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_13_RX_SI_EN_BMSK                         0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_13_RX_SI_EN_SHFT                             13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_12_RX_SI_EN_BMSK                         0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_12_RX_SI_EN_SHFT                             12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_11_RX_SI_EN_BMSK                          0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_11_RX_SI_EN_SHFT                             11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_10_RX_SI_EN_BMSK                          0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_10_RX_SI_EN_SHFT                             10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_9_RX_SI_EN_BMSK                           0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_9_RX_SI_EN_SHFT                               9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_8_RX_SI_EN_BMSK                           0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_8_RX_SI_EN_SHFT                               8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_7_RX_SI_EN_BMSK                            0x80
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_7_RX_SI_EN_SHFT                               7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_6_RX_SI_EN_BMSK                            0x40
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_6_RX_SI_EN_SHFT                               6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_5_RX_SI_EN_BMSK                            0x20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_5_RX_SI_EN_SHFT                               5
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_4_RX_SI_EN_BMSK                            0x10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_4_RX_SI_EN_SHFT                               4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_3_RX_SI_EN_BMSK                             0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_3_RX_SI_EN_SHFT                               3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_2_RX_SI_EN_BMSK                             0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_2_RX_SI_EN_SHFT                               2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_1_RX_SI_EN_BMSK                             0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_1_RX_SI_EN_SHFT                               1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_0_RX_SI_EN_BMSK                             0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG21_PRIM_0_RX_SI_EN_SHFT                               0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x158)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_OFFS                                      (0x158)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG22_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG22_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG22_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG22_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG22_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_23_RX_PAR_EN_BMSK                      0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_23_RX_PAR_EN_SHFT                            23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_22_RX_PAR_EN_BMSK                      0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_22_RX_PAR_EN_SHFT                            22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_21_RX_PAR_EN_BMSK                      0x200000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_21_RX_PAR_EN_SHFT                            21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_20_RX_PAR_EN_BMSK                      0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_20_RX_PAR_EN_SHFT                            20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_19_RX_PAR_EN_BMSK                       0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_19_RX_PAR_EN_SHFT                            19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_18_RX_PAR_EN_BMSK                       0x40000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_18_RX_PAR_EN_SHFT                            18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_17_RX_PAR_EN_BMSK                       0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_17_RX_PAR_EN_SHFT                            17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_16_RX_PAR_EN_BMSK                       0x10000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_16_RX_PAR_EN_SHFT                            16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_15_RX_PAR_EN_BMSK                        0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_15_RX_PAR_EN_SHFT                            15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_14_RX_PAR_EN_BMSK                        0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_14_RX_PAR_EN_SHFT                            14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_13_RX_PAR_EN_BMSK                        0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_13_RX_PAR_EN_SHFT                            13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_12_RX_PAR_EN_BMSK                        0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_12_RX_PAR_EN_SHFT                            12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_11_RX_PAR_EN_BMSK                         0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_11_RX_PAR_EN_SHFT                            11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_10_RX_PAR_EN_BMSK                         0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_10_RX_PAR_EN_SHFT                            10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_9_RX_PAR_EN_BMSK                          0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_9_RX_PAR_EN_SHFT                              9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_8_RX_PAR_EN_BMSK                          0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_8_RX_PAR_EN_SHFT                              8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_7_RX_PAR_EN_BMSK                           0x80
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_7_RX_PAR_EN_SHFT                              7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_6_RX_PAR_EN_BMSK                           0x40
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_6_RX_PAR_EN_SHFT                              6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_5_RX_PAR_EN_BMSK                           0x20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_5_RX_PAR_EN_SHFT                              5
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_4_RX_PAR_EN_BMSK                           0x10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_4_RX_PAR_EN_SHFT                              4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_3_RX_PAR_EN_BMSK                            0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_3_RX_PAR_EN_SHFT                              3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_2_RX_PAR_EN_BMSK                            0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_2_RX_PAR_EN_SHFT                              2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_1_RX_PAR_EN_BMSK                            0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_1_RX_PAR_EN_SHFT                              1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_0_RX_PAR_EN_BMSK                            0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG22_PRIM_0_RX_PAR_EN_SHFT                              0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x15c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_OFFS                                      (0x15c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG23_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG23_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG23_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG23_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG23_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_23_RX_PAR_FIRST_BMSK                   0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_23_RX_PAR_FIRST_SHFT                         23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_22_RX_PAR_FIRST_BMSK                   0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_22_RX_PAR_FIRST_SHFT                         22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_21_RX_PAR_FIRST_BMSK                   0x200000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_21_RX_PAR_FIRST_SHFT                         21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_20_RX_PAR_FIRST_BMSK                   0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_20_RX_PAR_FIRST_SHFT                         20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_19_RX_PAR_FIRST_BMSK                    0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_19_RX_PAR_FIRST_SHFT                         19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_18_RX_PAR_FIRST_BMSK                    0x40000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_18_RX_PAR_FIRST_SHFT                         18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_17_RX_PAR_FIRST_BMSK                    0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_17_RX_PAR_FIRST_SHFT                         17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_16_RX_PAR_FIRST_BMSK                    0x10000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_16_RX_PAR_FIRST_SHFT                         16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_15_RX_PAR_FIRST_BMSK                     0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_15_RX_PAR_FIRST_SHFT                         15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_14_RX_PAR_FIRST_BMSK                     0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_14_RX_PAR_FIRST_SHFT                         14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_13_RX_PAR_FIRST_BMSK                     0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_13_RX_PAR_FIRST_SHFT                         13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_12_RX_PAR_FIRST_BMSK                     0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_12_RX_PAR_FIRST_SHFT                         12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_11_RX_PAR_FIRST_BMSK                      0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_11_RX_PAR_FIRST_SHFT                         11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_10_RX_PAR_FIRST_BMSK                      0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_10_RX_PAR_FIRST_SHFT                         10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_9_RX_PAR_FIRST_BMSK                       0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_9_RX_PAR_FIRST_SHFT                           9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_8_RX_PAR_FIRST_BMSK                       0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_8_RX_PAR_FIRST_SHFT                           8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_7_RX_PAR_FIRST_BMSK                        0x80
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_7_RX_PAR_FIRST_SHFT                           7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_6_RX_PAR_FIRST_BMSK                        0x40
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_6_RX_PAR_FIRST_SHFT                           6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_5_RX_PAR_FIRST_BMSK                        0x20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_5_RX_PAR_FIRST_SHFT                           5
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_4_RX_PAR_FIRST_BMSK                        0x10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_4_RX_PAR_FIRST_SHFT                           4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_3_RX_PAR_FIRST_BMSK                         0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_3_RX_PAR_FIRST_SHFT                           3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_2_RX_PAR_FIRST_BMSK                         0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_2_RX_PAR_FIRST_SHFT                           2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_1_RX_PAR_FIRST_BMSK                         0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_1_RX_PAR_FIRST_SHFT                           1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_0_RX_PAR_FIRST_BMSK                         0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG23_PRIM_0_RX_PAR_FIRST_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x160)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_OFFS                                      (0x160)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG24_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG24_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG24_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG24_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG24_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_23_ACC_PAR_EN_BMSK                     0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_23_ACC_PAR_EN_SHFT                           23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_22_ACC_PAR_EN_BMSK                     0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_22_ACC_PAR_EN_SHFT                           22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_21_ACC_PAR_EN_BMSK                     0x200000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_21_ACC_PAR_EN_SHFT                           21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_20_ACC_PAR_EN_BMSK                     0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_20_ACC_PAR_EN_SHFT                           20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_19_ACC_PAR_EN_BMSK                      0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_19_ACC_PAR_EN_SHFT                           19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_18_ACC_PAR_EN_BMSK                      0x40000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_18_ACC_PAR_EN_SHFT                           18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_17_ACC_PAR_EN_BMSK                      0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_17_ACC_PAR_EN_SHFT                           17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_16_ACC_PAR_EN_BMSK                      0x10000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_16_ACC_PAR_EN_SHFT                           16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_15_ACC_PAR_EN_BMSK                       0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_15_ACC_PAR_EN_SHFT                           15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_14_ACC_PAR_EN_BMSK                       0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_14_ACC_PAR_EN_SHFT                           14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_13_ACC_PAR_EN_BMSK                       0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_13_ACC_PAR_EN_SHFT                           13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_12_ACC_PAR_EN_BMSK                       0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_12_ACC_PAR_EN_SHFT                           12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_11_ACC_PAR_EN_BMSK                        0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_11_ACC_PAR_EN_SHFT                           11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_10_ACC_PAR_EN_BMSK                        0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_10_ACC_PAR_EN_SHFT                           10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_9_ACC_PAR_EN_BMSK                         0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_9_ACC_PAR_EN_SHFT                             9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_8_ACC_PAR_EN_BMSK                         0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_8_ACC_PAR_EN_SHFT                             8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_7_ACC_PAR_EN_BMSK                          0x80
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_7_ACC_PAR_EN_SHFT                             7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_6_ACC_PAR_EN_BMSK                          0x40
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_6_ACC_PAR_EN_SHFT                             6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_5_ACC_PAR_EN_BMSK                          0x20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_5_ACC_PAR_EN_SHFT                             5
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_4_ACC_PAR_EN_BMSK                          0x10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_4_ACC_PAR_EN_SHFT                             4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_3_ACC_PAR_EN_BMSK                           0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_3_ACC_PAR_EN_SHFT                             3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_2_ACC_PAR_EN_BMSK                           0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_2_ACC_PAR_EN_SHFT                             2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_1_ACC_PAR_EN_BMSK                           0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_1_ACC_PAR_EN_SHFT                             1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_0_ACC_PAR_EN_BMSK                           0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG24_PRIM_0_ACC_PAR_EN_SHFT                             0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x164)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_OFFS                                      (0x164)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG25_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG25_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG25_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG25_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG25_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_11_IO2_FUNC_SEL_BMSK                   0xc00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_11_IO2_FUNC_SEL_SHFT                         22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_10_IO2_FUNC_SEL_BMSK                   0x300000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_10_IO2_FUNC_SEL_SHFT                         20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_9_IO2_FUNC_SEL_BMSK                     0xc0000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_9_IO2_FUNC_SEL_SHFT                          18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_8_IO2_FUNC_SEL_BMSK                     0x30000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_8_IO2_FUNC_SEL_SHFT                          16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_7_IO2_FUNC_SEL_BMSK                      0xc000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_7_IO2_FUNC_SEL_SHFT                          14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_6_IO2_FUNC_SEL_BMSK                      0x3000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_6_IO2_FUNC_SEL_SHFT                          12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_5_IO2_FUNC_SEL_BMSK                       0xc00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_5_IO2_FUNC_SEL_SHFT                          10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_4_IO2_FUNC_SEL_BMSK                       0x300
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_4_IO2_FUNC_SEL_SHFT                           8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_3_IO2_FUNC_SEL_BMSK                        0xc0
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_3_IO2_FUNC_SEL_SHFT                           6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_2_IO2_FUNC_SEL_BMSK                        0x30
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_2_IO2_FUNC_SEL_SHFT                           4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_1_IO2_FUNC_SEL_BMSK                         0xc
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_1_IO2_FUNC_SEL_SHFT                           2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_0_IO2_FUNC_SEL_BMSK                         0x3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG25_PRIM_0_IO2_FUNC_SEL_SHFT                           0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x168)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_OFFS                                      (0x168)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG26_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG26_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG26_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG26_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG26_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_23_IO2_FUNC_SEL_BMSK                   0xc00000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_23_IO2_FUNC_SEL_SHFT                         22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_22_IO2_FUNC_SEL_BMSK                   0x300000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_22_IO2_FUNC_SEL_SHFT                         20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_21_IO2_FUNC_SEL_BMSK                    0xc0000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_21_IO2_FUNC_SEL_SHFT                         18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_20_IO2_FUNC_SEL_BMSK                    0x30000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_20_IO2_FUNC_SEL_SHFT                         16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_19_IO2_FUNC_SEL_BMSK                     0xc000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_19_IO2_FUNC_SEL_SHFT                         14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_18_IO2_FUNC_SEL_BMSK                     0x3000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_18_IO2_FUNC_SEL_SHFT                         12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_17_IO2_FUNC_SEL_BMSK                      0xc00
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_17_IO2_FUNC_SEL_SHFT                         10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_16_IO2_FUNC_SEL_BMSK                      0x300
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_16_IO2_FUNC_SEL_SHFT                          8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_15_IO2_FUNC_SEL_BMSK                       0xc0
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_15_IO2_FUNC_SEL_SHFT                          6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_14_IO2_FUNC_SEL_BMSK                       0x30
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_14_IO2_FUNC_SEL_SHFT                          4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_13_IO2_FUNC_SEL_BMSK                        0xc
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_13_IO2_FUNC_SEL_SHFT                          2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_12_IO2_FUNC_SEL_BMSK                        0x3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG26_PRIM_12_IO2_FUNC_SEL_SHFT                          0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x16c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_OFFS                                      (0x16c)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG27_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG27_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG27_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG27_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG27_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_23_TX_FORCE_DATA_VALUE_BMSK            0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_23_TX_FORCE_DATA_VALUE_SHFT                  23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_22_TX_FORCE_DATA_VALUE_BMSK            0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_22_TX_FORCE_DATA_VALUE_SHFT                  22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_21_TX_FORCE_DATA_VALUE_BMSK            0x200000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_21_TX_FORCE_DATA_VALUE_SHFT                  21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_20_TX_FORCE_DATA_VALUE_BMSK            0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_20_TX_FORCE_DATA_VALUE_SHFT                  20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_19_TX_FORCE_DATA_VALUE_BMSK             0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_19_TX_FORCE_DATA_VALUE_SHFT                  19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_18_TX_FORCE_DATA_VALUE_BMSK             0x40000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_18_TX_FORCE_DATA_VALUE_SHFT                  18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_17_TX_FORCE_DATA_VALUE_BMSK             0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_17_TX_FORCE_DATA_VALUE_SHFT                  17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_16_TX_FORCE_DATA_VALUE_BMSK             0x10000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_16_TX_FORCE_DATA_VALUE_SHFT                  16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_15_TX_FORCE_DATA_VALUE_BMSK              0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_15_TX_FORCE_DATA_VALUE_SHFT                  15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_14_TX_FORCE_DATA_VALUE_BMSK              0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_14_TX_FORCE_DATA_VALUE_SHFT                  14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_13_TX_FORCE_DATA_VALUE_BMSK              0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_13_TX_FORCE_DATA_VALUE_SHFT                  13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_12_TX_FORCE_DATA_VALUE_BMSK              0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_12_TX_FORCE_DATA_VALUE_SHFT                  12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_11_TX_FORCE_DATA_VALUE_BMSK               0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_11_TX_FORCE_DATA_VALUE_SHFT                  11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_10_TX_FORCE_DATA_VALUE_BMSK               0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_10_TX_FORCE_DATA_VALUE_SHFT                  10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_9_TX_FORCE_DATA_VALUE_BMSK                0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_9_TX_FORCE_DATA_VALUE_SHFT                    9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_8_TX_FORCE_DATA_VALUE_BMSK                0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_8_TX_FORCE_DATA_VALUE_SHFT                    8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_7_TX_FORCE_DATA_VALUE_BMSK                 0x80
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_7_TX_FORCE_DATA_VALUE_SHFT                    7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_6_TX_FORCE_DATA_VALUE_BMSK                 0x40
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_6_TX_FORCE_DATA_VALUE_SHFT                    6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_5_TX_FORCE_DATA_VALUE_BMSK                 0x20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_5_TX_FORCE_DATA_VALUE_SHFT                    5
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_4_TX_FORCE_DATA_VALUE_BMSK                 0x10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_4_TX_FORCE_DATA_VALUE_SHFT                    4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_3_TX_FORCE_DATA_VALUE_BMSK                  0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_3_TX_FORCE_DATA_VALUE_SHFT                    3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_2_TX_FORCE_DATA_VALUE_BMSK                  0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_2_TX_FORCE_DATA_VALUE_SHFT                    2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_1_TX_FORCE_DATA_VALUE_BMSK                  0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_1_TX_FORCE_DATA_VALUE_SHFT                    1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_0_TX_FORCE_DATA_VALUE_BMSK                  0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG27_PRIM_0_TX_FORCE_DATA_VALUE_SHFT                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x170)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_OFFS                                      (0x170)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG28_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG28_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG28_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG28_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG28_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_23_RX_FORCE_DATA_VALUE_BMSK            0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_23_RX_FORCE_DATA_VALUE_SHFT                  23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_22_RX_FORCE_DATA_VALUE_BMSK            0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_22_RX_FORCE_DATA_VALUE_SHFT                  22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_21_RX_FORCE_DATA_VALUE_BMSK            0x200000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_21_RX_FORCE_DATA_VALUE_SHFT                  21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_20_RX_FORCE_DATA_VALUE_BMSK            0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_20_RX_FORCE_DATA_VALUE_SHFT                  20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_19_RX_FORCE_DATA_VALUE_BMSK             0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_19_RX_FORCE_DATA_VALUE_SHFT                  19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_18_RX_FORCE_DATA_VALUE_BMSK             0x40000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_18_RX_FORCE_DATA_VALUE_SHFT                  18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_17_RX_FORCE_DATA_VALUE_BMSK             0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_17_RX_FORCE_DATA_VALUE_SHFT                  17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_16_RX_FORCE_DATA_VALUE_BMSK             0x10000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_16_RX_FORCE_DATA_VALUE_SHFT                  16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_15_RX_FORCE_DATA_VALUE_BMSK              0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_15_RX_FORCE_DATA_VALUE_SHFT                  15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_14_RX_FORCE_DATA_VALUE_BMSK              0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_14_RX_FORCE_DATA_VALUE_SHFT                  14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_13_RX_FORCE_DATA_VALUE_BMSK              0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_13_RX_FORCE_DATA_VALUE_SHFT                  13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_12_RX_FORCE_DATA_VALUE_BMSK              0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_12_RX_FORCE_DATA_VALUE_SHFT                  12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_11_RX_FORCE_DATA_VALUE_BMSK               0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_11_RX_FORCE_DATA_VALUE_SHFT                  11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_10_RX_FORCE_DATA_VALUE_BMSK               0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_10_RX_FORCE_DATA_VALUE_SHFT                  10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_9_RX_FORCE_DATA_VALUE_BMSK                0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_9_RX_FORCE_DATA_VALUE_SHFT                    9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_8_RX_FORCE_DATA_VALUE_BMSK                0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_8_RX_FORCE_DATA_VALUE_SHFT                    8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_7_RX_FORCE_DATA_VALUE_BMSK                 0x80
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_7_RX_FORCE_DATA_VALUE_SHFT                    7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_6_RX_FORCE_DATA_VALUE_BMSK                 0x40
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_6_RX_FORCE_DATA_VALUE_SHFT                    6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_5_RX_FORCE_DATA_VALUE_BMSK                 0x20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_5_RX_FORCE_DATA_VALUE_SHFT                    5
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_4_RX_FORCE_DATA_VALUE_BMSK                 0x10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_4_RX_FORCE_DATA_VALUE_SHFT                    4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_3_RX_FORCE_DATA_VALUE_BMSK                  0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_3_RX_FORCE_DATA_VALUE_SHFT                    3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_2_RX_FORCE_DATA_VALUE_BMSK                  0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_2_RX_FORCE_DATA_VALUE_SHFT                    2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_1_RX_FORCE_DATA_VALUE_BMSK                  0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_1_RX_FORCE_DATA_VALUE_SHFT                    1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_0_RX_FORCE_DATA_VALUE_BMSK                  0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG28_PRIM_0_RX_FORCE_DATA_VALUE_SHFT                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x174)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_OFFS                                      (0x174)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG29_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG29_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG29_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG29_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG29_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_23_TX_TIME_COUNTER_EN_BMSK             0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_23_TX_TIME_COUNTER_EN_SHFT                   23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_22_TX_TIME_COUNTER_EN_BMSK             0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_22_TX_TIME_COUNTER_EN_SHFT                   22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_21_TX_TIME_COUNTER_EN_BMSK             0x200000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_21_TX_TIME_COUNTER_EN_SHFT                   21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_20_TX_TIME_COUNTER_EN_BMSK             0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_20_TX_TIME_COUNTER_EN_SHFT                   20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_19_TX_TIME_COUNTER_EN_BMSK              0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_19_TX_TIME_COUNTER_EN_SHFT                   19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_18_TX_TIME_COUNTER_EN_BMSK              0x40000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_18_TX_TIME_COUNTER_EN_SHFT                   18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_17_TX_TIME_COUNTER_EN_BMSK              0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_17_TX_TIME_COUNTER_EN_SHFT                   17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_16_TX_TIME_COUNTER_EN_BMSK              0x10000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_16_TX_TIME_COUNTER_EN_SHFT                   16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_15_TX_TIME_COUNTER_EN_BMSK               0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_15_TX_TIME_COUNTER_EN_SHFT                   15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_14_TX_TIME_COUNTER_EN_BMSK               0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_14_TX_TIME_COUNTER_EN_SHFT                   14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_13_TX_TIME_COUNTER_EN_BMSK               0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_13_TX_TIME_COUNTER_EN_SHFT                   13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_12_TX_TIME_COUNTER_EN_BMSK               0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_12_TX_TIME_COUNTER_EN_SHFT                   12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_11_TX_TIME_COUNTER_EN_BMSK                0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_11_TX_TIME_COUNTER_EN_SHFT                   11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_10_TX_TIME_COUNTER_EN_BMSK                0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_10_TX_TIME_COUNTER_EN_SHFT                   10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_9_TX_TIME_COUNTER_EN_BMSK                 0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_9_TX_TIME_COUNTER_EN_SHFT                     9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_8_TX_TIME_COUNTER_EN_BMSK                 0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_8_TX_TIME_COUNTER_EN_SHFT                     8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_7_TX_TIME_COUNTER_EN_BMSK                  0x80
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_7_TX_TIME_COUNTER_EN_SHFT                     7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_6_TX_TIME_COUNTER_EN_BMSK                  0x40
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_6_TX_TIME_COUNTER_EN_SHFT                     6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_5_TX_TIME_COUNTER_EN_BMSK                  0x20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_5_TX_TIME_COUNTER_EN_SHFT                     5
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_4_TX_TIME_COUNTER_EN_BMSK                  0x10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_4_TX_TIME_COUNTER_EN_SHFT                     4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_3_TX_TIME_COUNTER_EN_BMSK                   0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_3_TX_TIME_COUNTER_EN_SHFT                     3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_2_TX_TIME_COUNTER_EN_BMSK                   0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_2_TX_TIME_COUNTER_EN_SHFT                     2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_1_TX_TIME_COUNTER_EN_BMSK                   0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_1_TX_TIME_COUNTER_EN_SHFT                     1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_0_TX_TIME_COUNTER_EN_BMSK                   0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG29_PRIM_0_TX_TIME_COUNTER_EN_SHFT                     0

#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x178)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_OFFS                                      (0x178)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_RMSK                                        0xffffff
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG30_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_REG30_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_OUT(x, v)            \
                out_dword(HWIO_SPMI1_SPMI_GENI_CFG_REG30_ADDR(x),v)
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SPMI1_SPMI_GENI_CFG_REG30_ADDR(x),m,v,HWIO_SPMI1_SPMI_GENI_CFG_REG30_IN(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_23_RX_TIME_COUNTER_EN_BMSK             0x800000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_23_RX_TIME_COUNTER_EN_SHFT                   23
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_22_RX_TIME_COUNTER_EN_BMSK             0x400000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_22_RX_TIME_COUNTER_EN_SHFT                   22
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_21_RX_TIME_COUNTER_EN_BMSK             0x200000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_21_RX_TIME_COUNTER_EN_SHFT                   21
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_20_RX_TIME_COUNTER_EN_BMSK             0x100000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_20_RX_TIME_COUNTER_EN_SHFT                   20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_19_RX_TIME_COUNTER_EN_BMSK              0x80000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_19_RX_TIME_COUNTER_EN_SHFT                   19
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_18_RX_TIME_COUNTER_EN_BMSK              0x40000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_18_RX_TIME_COUNTER_EN_SHFT                   18
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_17_RX_TIME_COUNTER_EN_BMSK              0x20000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_17_RX_TIME_COUNTER_EN_SHFT                   17
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_16_RX_TIME_COUNTER_EN_BMSK              0x10000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_16_RX_TIME_COUNTER_EN_SHFT                   16
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_15_RX_TIME_COUNTER_EN_BMSK               0x8000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_15_RX_TIME_COUNTER_EN_SHFT                   15
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_14_RX_TIME_COUNTER_EN_BMSK               0x4000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_14_RX_TIME_COUNTER_EN_SHFT                   14
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_13_RX_TIME_COUNTER_EN_BMSK               0x2000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_13_RX_TIME_COUNTER_EN_SHFT                   13
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_12_RX_TIME_COUNTER_EN_BMSK               0x1000
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_12_RX_TIME_COUNTER_EN_SHFT                   12
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_11_RX_TIME_COUNTER_EN_BMSK                0x800
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_11_RX_TIME_COUNTER_EN_SHFT                   11
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_10_RX_TIME_COUNTER_EN_BMSK                0x400
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_10_RX_TIME_COUNTER_EN_SHFT                   10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_9_RX_TIME_COUNTER_EN_BMSK                 0x200
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_9_RX_TIME_COUNTER_EN_SHFT                     9
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_8_RX_TIME_COUNTER_EN_BMSK                 0x100
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_8_RX_TIME_COUNTER_EN_SHFT                     8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_7_RX_TIME_COUNTER_EN_BMSK                  0x80
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_7_RX_TIME_COUNTER_EN_SHFT                     7
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_6_RX_TIME_COUNTER_EN_BMSK                  0x40
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_6_RX_TIME_COUNTER_EN_SHFT                     6
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_5_RX_TIME_COUNTER_EN_BMSK                  0x20
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_5_RX_TIME_COUNTER_EN_SHFT                     5
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_4_RX_TIME_COUNTER_EN_BMSK                  0x10
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_4_RX_TIME_COUNTER_EN_SHFT                     4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_3_RX_TIME_COUNTER_EN_BMSK                   0x8
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_3_RX_TIME_COUNTER_EN_SHFT                     3
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_2_RX_TIME_COUNTER_EN_BMSK                   0x4
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_2_RX_TIME_COUNTER_EN_SHFT                     2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_1_RX_TIME_COUNTER_EN_BMSK                   0x2
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_1_RX_TIME_COUNTER_EN_SHFT                     1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_0_RX_TIME_COUNTER_EN_BMSK                   0x1
#define HWIO_SPMI1_SPMI_GENI_CFG_REG30_PRIM_0_RX_TIME_COUNTER_EN_SHFT                     0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM0_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x200)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM0_OFFS                                       (0x200)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM0_RMSK                                         0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM0_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM0_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM0_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM0_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM0_IMAGE_0_BMSK                                 0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM0_IMAGE_0_SHFT                                        0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM1_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x204)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM1_OFFS                                       (0x204)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM1_RMSK                                         0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM1_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM1_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM1_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM1_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM1_IMAGE_1_BMSK                                 0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM1_IMAGE_1_SHFT                                        0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM2_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x208)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM2_OFFS                                       (0x208)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM2_RMSK                                         0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM2_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM2_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM2_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM2_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM2_IMAGE_2_BMSK                                 0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM2_IMAGE_2_SHFT                                        0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM3_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x20c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM3_OFFS                                       (0x20c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM3_RMSK                                         0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM3_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM3_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM3_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM3_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM3_IMAGE_3_BMSK                                 0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM3_IMAGE_3_SHFT                                        0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM4_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x210)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM4_OFFS                                       (0x210)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM4_RMSK                                         0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM4_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM4_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM4_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM4_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM4_IMAGE_4_BMSK                                 0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM4_IMAGE_4_SHFT                                        0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM5_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x214)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM5_OFFS                                       (0x214)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM5_RMSK                                         0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM5_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM5_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM5_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM5_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM5_IMAGE_5_BMSK                                 0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM5_IMAGE_5_SHFT                                        0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM6_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x218)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM6_OFFS                                       (0x218)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM6_RMSK                                         0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM6_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM6_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM6_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM6_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM6_IMAGE_6_BMSK                                 0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM6_IMAGE_6_SHFT                                        0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM7_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x21c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM7_OFFS                                       (0x21c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM7_RMSK                                         0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM7_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM7_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM7_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM7_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM7_IMAGE_7_BMSK                                 0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM7_IMAGE_7_SHFT                                        0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM8_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x220)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM8_OFFS                                       (0x220)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM8_RMSK                                         0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM8_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM8_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM8_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM8_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM8_IMAGE_8_BMSK                                 0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM8_IMAGE_8_SHFT                                        0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM9_ADDR(x)                                    ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x224)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM9_OFFS                                       (0x224)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM9_RMSK                                         0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM9_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM9_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM9_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM9_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM9_IMAGE_9_BMSK                                 0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM9_IMAGE_9_SHFT                                        0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM10_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x228)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM10_OFFS                                      (0x228)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM10_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM10_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM10_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM10_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM10_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM10_IMAGE_10_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM10_IMAGE_10_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM11_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x22c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM11_OFFS                                      (0x22c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM11_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM11_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM11_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM11_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM11_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM11_IMAGE_11_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM11_IMAGE_11_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM12_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x230)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM12_OFFS                                      (0x230)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM12_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM12_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM12_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM12_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM12_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM12_IMAGE_12_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM12_IMAGE_12_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM13_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x234)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM13_OFFS                                      (0x234)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM13_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM13_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM13_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM13_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM13_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM13_IMAGE_13_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM13_IMAGE_13_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM14_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x238)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM14_OFFS                                      (0x238)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM14_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM14_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM14_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM14_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM14_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM14_IMAGE_14_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM14_IMAGE_14_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM15_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x23c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM15_OFFS                                      (0x23c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM15_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM15_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM15_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM15_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM15_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM15_IMAGE_15_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM15_IMAGE_15_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM16_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x240)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM16_OFFS                                      (0x240)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM16_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM16_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM16_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM16_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM16_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM16_IMAGE_16_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM16_IMAGE_16_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM17_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x244)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM17_OFFS                                      (0x244)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM17_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM17_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM17_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM17_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM17_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM17_IMAGE_17_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM17_IMAGE_17_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM18_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x248)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM18_OFFS                                      (0x248)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM18_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM18_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM18_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM18_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM18_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM18_IMAGE_18_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM18_IMAGE_18_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM19_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x24c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM19_OFFS                                      (0x24c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM19_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM19_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM19_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM19_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM19_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM19_IMAGE_19_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM19_IMAGE_19_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM20_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x250)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM20_OFFS                                      (0x250)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM20_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM20_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM20_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM20_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM20_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM20_IMAGE_20_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM20_IMAGE_20_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM21_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x254)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM21_OFFS                                      (0x254)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM21_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM21_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM21_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM21_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM21_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM21_IMAGE_21_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM21_IMAGE_21_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM22_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x258)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM22_OFFS                                      (0x258)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM22_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM22_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM22_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM22_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM22_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM22_IMAGE_22_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM22_IMAGE_22_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM23_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x25c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM23_OFFS                                      (0x25c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM23_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM23_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM23_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM23_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM23_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM23_IMAGE_23_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM23_IMAGE_23_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM24_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x260)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM24_OFFS                                      (0x260)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM24_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM24_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM24_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM24_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM24_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM24_IMAGE_24_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM24_IMAGE_24_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM25_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x264)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM25_OFFS                                      (0x264)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM25_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM25_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM25_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM25_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM25_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM25_IMAGE_25_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM25_IMAGE_25_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM26_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x268)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM26_OFFS                                      (0x268)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM26_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM26_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM26_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM26_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM26_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM26_IMAGE_26_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM26_IMAGE_26_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM27_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x26c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM27_OFFS                                      (0x26c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM27_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM27_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM27_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM27_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM27_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM27_IMAGE_27_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM27_IMAGE_27_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM28_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x270)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM28_OFFS                                      (0x270)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM28_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM28_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM28_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM28_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM28_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM28_IMAGE_28_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM28_IMAGE_28_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM29_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x274)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM29_OFFS                                      (0x274)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM29_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM29_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM29_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM29_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM29_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM29_IMAGE_29_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM29_IMAGE_29_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM30_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x278)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM30_OFFS                                      (0x278)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM30_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM30_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM30_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM30_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM30_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM30_IMAGE_30_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM30_IMAGE_30_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM31_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x27c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM31_OFFS                                      (0x27c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM31_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM31_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM31_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM31_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM31_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM31_IMAGE_31_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM31_IMAGE_31_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM32_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x280)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM32_OFFS                                      (0x280)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM32_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM32_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM32_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM32_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM32_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM32_IMAGE_32_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM32_IMAGE_32_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM33_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x284)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM33_OFFS                                      (0x284)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM33_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM33_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM33_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM33_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM33_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM33_IMAGE_33_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM33_IMAGE_33_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM34_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x288)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM34_OFFS                                      (0x288)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM34_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM34_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM34_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM34_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM34_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM34_IMAGE_34_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM34_IMAGE_34_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM35_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x28c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM35_OFFS                                      (0x28c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM35_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM35_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM35_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM35_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM35_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM35_IMAGE_35_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM35_IMAGE_35_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM36_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x290)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM36_OFFS                                      (0x290)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM36_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM36_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM36_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM36_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM36_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM36_IMAGE_36_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM36_IMAGE_36_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM37_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x294)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM37_OFFS                                      (0x294)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM37_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM37_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM37_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM37_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM37_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM37_IMAGE_37_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM37_IMAGE_37_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM38_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x298)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM38_OFFS                                      (0x298)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM38_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM38_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM38_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM38_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM38_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM38_IMAGE_38_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM38_IMAGE_38_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM39_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x29c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM39_OFFS                                      (0x29c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM39_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM39_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM39_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM39_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM39_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM39_IMAGE_39_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM39_IMAGE_39_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM40_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2a0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM40_OFFS                                      (0x2a0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM40_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM40_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM40_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM40_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM40_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM40_IMAGE_40_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM40_IMAGE_40_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM41_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2a4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM41_OFFS                                      (0x2a4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM41_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM41_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM41_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM41_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM41_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM41_IMAGE_41_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM41_IMAGE_41_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM42_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2a8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM42_OFFS                                      (0x2a8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM42_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM42_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM42_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM42_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM42_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM42_IMAGE_42_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM42_IMAGE_42_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM43_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2ac)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM43_OFFS                                      (0x2ac)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM43_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM43_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM43_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM43_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM43_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM43_IMAGE_43_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM43_IMAGE_43_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM44_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2b0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM44_OFFS                                      (0x2b0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM44_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM44_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM44_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM44_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM44_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM44_IMAGE_44_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM44_IMAGE_44_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM45_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2b4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM45_OFFS                                      (0x2b4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM45_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM45_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM45_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM45_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM45_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM45_IMAGE_45_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM45_IMAGE_45_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM46_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2b8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM46_OFFS                                      (0x2b8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM46_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM46_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM46_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM46_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM46_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM46_IMAGE_46_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM46_IMAGE_46_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM47_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2bc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM47_OFFS                                      (0x2bc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM47_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM47_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM47_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM47_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM47_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM47_IMAGE_47_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM47_IMAGE_47_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM48_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2c0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM48_OFFS                                      (0x2c0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM48_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM48_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM48_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM48_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM48_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM48_IMAGE_48_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM48_IMAGE_48_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM49_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2c4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM49_OFFS                                      (0x2c4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM49_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM49_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM49_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM49_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM49_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM49_IMAGE_49_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM49_IMAGE_49_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM50_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2c8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM50_OFFS                                      (0x2c8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM50_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM50_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM50_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM50_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM50_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM50_IMAGE_50_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM50_IMAGE_50_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM51_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2cc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM51_OFFS                                      (0x2cc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM51_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM51_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM51_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM51_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM51_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM51_IMAGE_51_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM51_IMAGE_51_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM52_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2d0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM52_OFFS                                      (0x2d0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM52_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM52_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM52_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM52_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM52_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM52_IMAGE_52_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM52_IMAGE_52_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM53_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2d4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM53_OFFS                                      (0x2d4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM53_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM53_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM53_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM53_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM53_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM53_IMAGE_53_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM53_IMAGE_53_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM54_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2d8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM54_OFFS                                      (0x2d8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM54_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM54_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM54_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM54_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM54_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM54_IMAGE_54_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM54_IMAGE_54_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM55_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2dc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM55_OFFS                                      (0x2dc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM55_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM55_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM55_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM55_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM55_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM55_IMAGE_55_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM55_IMAGE_55_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM56_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2e0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM56_OFFS                                      (0x2e0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM56_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM56_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM56_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM56_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM56_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM56_IMAGE_56_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM56_IMAGE_56_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM57_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2e4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM57_OFFS                                      (0x2e4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM57_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM57_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM57_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM57_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM57_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM57_IMAGE_57_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM57_IMAGE_57_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM58_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2e8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM58_OFFS                                      (0x2e8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM58_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM58_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM58_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM58_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM58_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM58_IMAGE_58_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM58_IMAGE_58_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM59_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2ec)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM59_OFFS                                      (0x2ec)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM59_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM59_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM59_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM59_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM59_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM59_IMAGE_59_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM59_IMAGE_59_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM60_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2f0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM60_OFFS                                      (0x2f0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM60_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM60_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM60_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM60_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM60_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM60_IMAGE_60_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM60_IMAGE_60_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM61_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2f4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM61_OFFS                                      (0x2f4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM61_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM61_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM61_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM61_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM61_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM61_IMAGE_61_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM61_IMAGE_61_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM62_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2f8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM62_OFFS                                      (0x2f8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM62_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM62_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM62_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM62_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM62_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM62_IMAGE_62_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM62_IMAGE_62_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM63_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x2fc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM63_OFFS                                      (0x2fc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM63_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM63_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM63_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM63_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM63_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM63_IMAGE_63_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM63_IMAGE_63_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM64_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x300)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM64_OFFS                                      (0x300)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM64_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM64_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM64_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM64_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM64_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM64_IMAGE_64_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM64_IMAGE_64_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM65_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x304)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM65_OFFS                                      (0x304)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM65_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM65_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM65_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM65_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM65_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM65_IMAGE_65_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM65_IMAGE_65_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM66_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x308)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM66_OFFS                                      (0x308)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM66_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM66_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM66_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM66_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM66_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM66_IMAGE_66_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM66_IMAGE_66_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM67_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x30c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM67_OFFS                                      (0x30c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM67_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM67_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM67_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM67_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM67_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM67_IMAGE_67_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM67_IMAGE_67_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM68_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x310)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM68_OFFS                                      (0x310)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM68_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM68_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM68_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM68_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM68_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM68_IMAGE_68_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM68_IMAGE_68_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM69_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x314)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM69_OFFS                                      (0x314)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM69_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM69_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM69_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM69_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM69_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM69_IMAGE_69_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM69_IMAGE_69_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM70_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x318)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM70_OFFS                                      (0x318)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM70_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM70_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM70_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM70_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM70_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM70_IMAGE_70_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM70_IMAGE_70_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM71_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x31c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM71_OFFS                                      (0x31c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM71_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM71_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM71_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM71_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM71_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM71_IMAGE_71_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM71_IMAGE_71_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM72_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x320)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM72_OFFS                                      (0x320)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM72_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM72_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM72_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM72_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM72_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM72_IMAGE_72_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM72_IMAGE_72_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM73_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x324)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM73_OFFS                                      (0x324)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM73_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM73_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM73_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM73_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM73_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM73_IMAGE_73_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM73_IMAGE_73_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM74_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x328)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM74_OFFS                                      (0x328)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM74_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM74_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM74_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM74_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM74_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM74_IMAGE_74_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM74_IMAGE_74_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM75_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x32c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM75_OFFS                                      (0x32c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM75_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM75_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM75_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM75_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM75_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM75_IMAGE_75_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM75_IMAGE_75_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM76_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x330)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM76_OFFS                                      (0x330)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM76_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM76_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM76_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM76_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM76_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM76_IMAGE_76_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM76_IMAGE_76_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM77_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x334)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM77_OFFS                                      (0x334)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM77_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM77_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM77_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM77_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM77_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM77_IMAGE_77_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM77_IMAGE_77_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM78_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x338)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM78_OFFS                                      (0x338)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM78_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM78_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM78_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM78_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM78_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM78_IMAGE_78_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM78_IMAGE_78_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM79_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x33c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM79_OFFS                                      (0x33c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM79_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM79_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM79_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM79_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM79_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM79_IMAGE_79_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM79_IMAGE_79_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM80_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x340)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM80_OFFS                                      (0x340)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM80_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM80_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM80_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM80_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM80_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM80_IMAGE_80_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM80_IMAGE_80_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM81_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x344)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM81_OFFS                                      (0x344)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM81_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM81_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM81_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM81_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM81_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM81_IMAGE_81_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM81_IMAGE_81_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM82_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x348)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM82_OFFS                                      (0x348)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM82_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM82_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM82_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM82_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM82_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM82_IMAGE_82_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM82_IMAGE_82_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM83_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x34c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM83_OFFS                                      (0x34c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM83_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM83_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM83_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM83_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM83_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM83_IMAGE_83_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM83_IMAGE_83_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM84_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x350)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM84_OFFS                                      (0x350)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM84_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM84_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM84_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM84_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM84_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM84_IMAGE_84_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM84_IMAGE_84_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM85_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x354)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM85_OFFS                                      (0x354)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM85_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM85_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM85_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM85_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM85_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM85_IMAGE_85_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM85_IMAGE_85_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM86_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x358)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM86_OFFS                                      (0x358)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM86_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM86_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM86_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM86_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM86_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM86_IMAGE_86_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM86_IMAGE_86_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM87_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x35c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM87_OFFS                                      (0x35c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM87_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM87_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM87_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM87_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM87_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM87_IMAGE_87_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM87_IMAGE_87_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM88_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x360)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM88_OFFS                                      (0x360)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM88_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM88_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM88_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM88_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM88_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM88_IMAGE_88_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM88_IMAGE_88_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM89_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x364)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM89_OFFS                                      (0x364)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM89_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM89_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM89_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM89_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM89_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM89_IMAGE_89_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM89_IMAGE_89_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM90_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x368)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM90_OFFS                                      (0x368)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM90_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM90_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM90_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM90_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM90_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM90_IMAGE_90_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM90_IMAGE_90_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM91_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x36c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM91_OFFS                                      (0x36c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM91_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM91_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM91_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM91_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM91_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM91_IMAGE_91_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM91_IMAGE_91_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM92_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x370)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM92_OFFS                                      (0x370)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM92_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM92_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM92_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM92_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM92_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM92_IMAGE_92_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM92_IMAGE_92_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM93_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x374)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM93_OFFS                                      (0x374)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM93_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM93_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM93_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM93_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM93_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM93_IMAGE_93_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM93_IMAGE_93_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM94_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x378)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM94_OFFS                                      (0x378)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM94_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM94_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM94_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM94_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM94_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM94_IMAGE_94_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM94_IMAGE_94_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM95_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x37c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM95_OFFS                                      (0x37c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM95_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM95_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM95_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM95_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM95_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM95_IMAGE_95_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM95_IMAGE_95_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM96_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x380)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM96_OFFS                                      (0x380)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM96_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM96_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM96_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM96_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM96_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM96_IMAGE_96_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM96_IMAGE_96_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM97_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x384)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM97_OFFS                                      (0x384)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM97_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM97_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM97_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM97_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM97_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM97_IMAGE_97_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM97_IMAGE_97_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM98_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x388)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM98_OFFS                                      (0x388)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM98_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM98_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM98_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM98_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM98_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM98_IMAGE_98_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM98_IMAGE_98_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM99_ADDR(x)                                   ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x38c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM99_OFFS                                      (0x38c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM99_RMSK                                        0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM99_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM99_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM99_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM99_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM99_IMAGE_99_BMSK                               0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM99_IMAGE_99_SHFT                                      0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM100_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x390)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM100_OFFS                                     (0x390)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM100_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM100_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM100_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM100_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM100_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM100_IMAGE_100_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM100_IMAGE_100_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM101_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x394)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM101_OFFS                                     (0x394)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM101_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM101_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM101_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM101_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM101_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM101_IMAGE_101_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM101_IMAGE_101_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM102_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x398)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM102_OFFS                                     (0x398)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM102_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM102_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM102_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM102_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM102_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM102_IMAGE_102_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM102_IMAGE_102_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM103_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x39c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM103_OFFS                                     (0x39c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM103_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM103_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM103_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM103_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM103_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM103_IMAGE_103_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM103_IMAGE_103_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM104_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3a0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM104_OFFS                                     (0x3a0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM104_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM104_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM104_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM104_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM104_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM104_IMAGE_104_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM104_IMAGE_104_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM105_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3a4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM105_OFFS                                     (0x3a4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM105_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM105_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM105_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM105_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM105_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM105_IMAGE_105_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM105_IMAGE_105_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM106_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3a8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM106_OFFS                                     (0x3a8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM106_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM106_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM106_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM106_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM106_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM106_IMAGE_106_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM106_IMAGE_106_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM107_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3ac)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM107_OFFS                                     (0x3ac)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM107_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM107_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM107_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM107_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM107_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM107_IMAGE_107_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM107_IMAGE_107_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM108_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3b0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM108_OFFS                                     (0x3b0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM108_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM108_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM108_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM108_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM108_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM108_IMAGE_108_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM108_IMAGE_108_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM109_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3b4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM109_OFFS                                     (0x3b4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM109_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM109_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM109_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM109_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM109_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM109_IMAGE_109_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM109_IMAGE_109_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM110_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3b8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM110_OFFS                                     (0x3b8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM110_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM110_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM110_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM110_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM110_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM110_IMAGE_110_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM110_IMAGE_110_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM111_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3bc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM111_OFFS                                     (0x3bc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM111_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM111_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM111_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM111_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM111_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM111_IMAGE_111_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM111_IMAGE_111_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM112_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3c0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM112_OFFS                                     (0x3c0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM112_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM112_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM112_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM112_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM112_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM112_IMAGE_112_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM112_IMAGE_112_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM113_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3c4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM113_OFFS                                     (0x3c4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM113_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM113_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM113_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM113_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM113_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM113_IMAGE_113_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM113_IMAGE_113_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM114_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3c8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM114_OFFS                                     (0x3c8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM114_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM114_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM114_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM114_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM114_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM114_IMAGE_114_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM114_IMAGE_114_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM115_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3cc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM115_OFFS                                     (0x3cc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM115_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM115_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM115_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM115_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM115_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM115_IMAGE_115_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM115_IMAGE_115_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM116_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3d0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM116_OFFS                                     (0x3d0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM116_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM116_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM116_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM116_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM116_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM116_IMAGE_116_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM116_IMAGE_116_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM117_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3d4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM117_OFFS                                     (0x3d4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM117_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM117_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM117_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM117_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM117_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM117_IMAGE_117_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM117_IMAGE_117_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM118_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3d8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM118_OFFS                                     (0x3d8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM118_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM118_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM118_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM118_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM118_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM118_IMAGE_118_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM118_IMAGE_118_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM119_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3dc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM119_OFFS                                     (0x3dc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM119_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM119_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM119_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM119_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM119_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM119_IMAGE_119_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM119_IMAGE_119_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM120_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3e0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM120_OFFS                                     (0x3e0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM120_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM120_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM120_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM120_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM120_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM120_IMAGE_120_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM120_IMAGE_120_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM121_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3e4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM121_OFFS                                     (0x3e4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM121_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM121_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM121_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM121_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM121_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM121_IMAGE_121_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM121_IMAGE_121_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM122_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3e8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM122_OFFS                                     (0x3e8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM122_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM122_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM122_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM122_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM122_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM122_IMAGE_122_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM122_IMAGE_122_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM123_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3ec)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM123_OFFS                                     (0x3ec)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM123_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM123_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM123_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM123_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM123_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM123_IMAGE_123_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM123_IMAGE_123_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM124_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3f0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM124_OFFS                                     (0x3f0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM124_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM124_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM124_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM124_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM124_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM124_IMAGE_124_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM124_IMAGE_124_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM125_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3f4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM125_OFFS                                     (0x3f4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM125_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM125_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM125_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM125_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM125_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM125_IMAGE_125_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM125_IMAGE_125_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM126_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3f8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM126_OFFS                                     (0x3f8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM126_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM126_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM126_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM126_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM126_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM126_IMAGE_126_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM126_IMAGE_126_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM127_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x3fc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM127_OFFS                                     (0x3fc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM127_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM127_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM127_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM127_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM127_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM127_IMAGE_127_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM127_IMAGE_127_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM128_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x400)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM128_OFFS                                     (0x400)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM128_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM128_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM128_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM128_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM128_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM128_IMAGE_128_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM128_IMAGE_128_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM129_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x404)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM129_OFFS                                     (0x404)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM129_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM129_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM129_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM129_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM129_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM129_IMAGE_129_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM129_IMAGE_129_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM130_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x408)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM130_OFFS                                     (0x408)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM130_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM130_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM130_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM130_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM130_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM130_IMAGE_130_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM130_IMAGE_130_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM131_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x40c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM131_OFFS                                     (0x40c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM131_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM131_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM131_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM131_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM131_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM131_IMAGE_131_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM131_IMAGE_131_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM132_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x410)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM132_OFFS                                     (0x410)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM132_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM132_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM132_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM132_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM132_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM132_IMAGE_132_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM132_IMAGE_132_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM133_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x414)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM133_OFFS                                     (0x414)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM133_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM133_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM133_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM133_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM133_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM133_IMAGE_133_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM133_IMAGE_133_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM134_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x418)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM134_OFFS                                     (0x418)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM134_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM134_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM134_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM134_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM134_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM134_IMAGE_134_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM134_IMAGE_134_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM135_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x41c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM135_OFFS                                     (0x41c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM135_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM135_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM135_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM135_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM135_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM135_IMAGE_135_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM135_IMAGE_135_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM136_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x420)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM136_OFFS                                     (0x420)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM136_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM136_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM136_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM136_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM136_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM136_IMAGE_136_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM136_IMAGE_136_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM137_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x424)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM137_OFFS                                     (0x424)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM137_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM137_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM137_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM137_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM137_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM137_IMAGE_137_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM137_IMAGE_137_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM138_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x428)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM138_OFFS                                     (0x428)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM138_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM138_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM138_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM138_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM138_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM138_IMAGE_138_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM138_IMAGE_138_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM139_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x42c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM139_OFFS                                     (0x42c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM139_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM139_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM139_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM139_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM139_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM139_IMAGE_139_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM139_IMAGE_139_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM140_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x430)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM140_OFFS                                     (0x430)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM140_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM140_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM140_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM140_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM140_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM140_IMAGE_140_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM140_IMAGE_140_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM141_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x434)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM141_OFFS                                     (0x434)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM141_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM141_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM141_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM141_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM141_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM141_IMAGE_141_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM141_IMAGE_141_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM142_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x438)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM142_OFFS                                     (0x438)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM142_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM142_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM142_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM142_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM142_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM142_IMAGE_142_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM142_IMAGE_142_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM143_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x43c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM143_OFFS                                     (0x43c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM143_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM143_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM143_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM143_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM143_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM143_IMAGE_143_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM143_IMAGE_143_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM144_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x440)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM144_OFFS                                     (0x440)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM144_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM144_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM144_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM144_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM144_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM144_IMAGE_144_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM144_IMAGE_144_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM145_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x444)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM145_OFFS                                     (0x444)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM145_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM145_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM145_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM145_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM145_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM145_IMAGE_145_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM145_IMAGE_145_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM146_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x448)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM146_OFFS                                     (0x448)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM146_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM146_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM146_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM146_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM146_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM146_IMAGE_146_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM146_IMAGE_146_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM147_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x44c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM147_OFFS                                     (0x44c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM147_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM147_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM147_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM147_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM147_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM147_IMAGE_147_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM147_IMAGE_147_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM148_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x450)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM148_OFFS                                     (0x450)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM148_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM148_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM148_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM148_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM148_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM148_IMAGE_148_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM148_IMAGE_148_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM149_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x454)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM149_OFFS                                     (0x454)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM149_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM149_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM149_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM149_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM149_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM149_IMAGE_149_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM149_IMAGE_149_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM150_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x458)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM150_OFFS                                     (0x458)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM150_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM150_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM150_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM150_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM150_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM150_IMAGE_150_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM150_IMAGE_150_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM151_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x45c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM151_OFFS                                     (0x45c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM151_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM151_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM151_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM151_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM151_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM151_IMAGE_151_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM151_IMAGE_151_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM152_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x460)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM152_OFFS                                     (0x460)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM152_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM152_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM152_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM152_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM152_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM152_IMAGE_152_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM152_IMAGE_152_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM153_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x464)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM153_OFFS                                     (0x464)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM153_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM153_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM153_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM153_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM153_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM153_IMAGE_153_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM153_IMAGE_153_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM154_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x468)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM154_OFFS                                     (0x468)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM154_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM154_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM154_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM154_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM154_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM154_IMAGE_154_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM154_IMAGE_154_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM155_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x46c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM155_OFFS                                     (0x46c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM155_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM155_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM155_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM155_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM155_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM155_IMAGE_155_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM155_IMAGE_155_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM156_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x470)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM156_OFFS                                     (0x470)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM156_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM156_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM156_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM156_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM156_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM156_IMAGE_156_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM156_IMAGE_156_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM157_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x474)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM157_OFFS                                     (0x474)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM157_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM157_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM157_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM157_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM157_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM157_IMAGE_157_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM157_IMAGE_157_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM158_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x478)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM158_OFFS                                     (0x478)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM158_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM158_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM158_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM158_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM158_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM158_IMAGE_158_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM158_IMAGE_158_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM159_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x47c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM159_OFFS                                     (0x47c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM159_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM159_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM159_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM159_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM159_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM159_IMAGE_159_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM159_IMAGE_159_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM160_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x480)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM160_OFFS                                     (0x480)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM160_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM160_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM160_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM160_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM160_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM160_IMAGE_160_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM160_IMAGE_160_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM161_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x484)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM161_OFFS                                     (0x484)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM161_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM161_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM161_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM161_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM161_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM161_IMAGE_161_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM161_IMAGE_161_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM162_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x488)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM162_OFFS                                     (0x488)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM162_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM162_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM162_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM162_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM162_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM162_IMAGE_162_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM162_IMAGE_162_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM163_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x48c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM163_OFFS                                     (0x48c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM163_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM163_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM163_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM163_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM163_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM163_IMAGE_163_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM163_IMAGE_163_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM164_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x490)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM164_OFFS                                     (0x490)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM164_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM164_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM164_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM164_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM164_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM164_IMAGE_164_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM164_IMAGE_164_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM165_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x494)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM165_OFFS                                     (0x494)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM165_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM165_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM165_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM165_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM165_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM165_IMAGE_165_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM165_IMAGE_165_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM166_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x498)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM166_OFFS                                     (0x498)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM166_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM166_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM166_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM166_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM166_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM166_IMAGE_166_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM166_IMAGE_166_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM167_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x49c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM167_OFFS                                     (0x49c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM167_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM167_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM167_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM167_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM167_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM167_IMAGE_167_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM167_IMAGE_167_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM168_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4a0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM168_OFFS                                     (0x4a0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM168_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM168_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM168_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM168_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM168_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM168_IMAGE_168_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM168_IMAGE_168_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM169_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4a4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM169_OFFS                                     (0x4a4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM169_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM169_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM169_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM169_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM169_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM169_IMAGE_169_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM169_IMAGE_169_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM170_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4a8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM170_OFFS                                     (0x4a8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM170_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM170_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM170_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM170_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM170_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM170_IMAGE_170_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM170_IMAGE_170_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM171_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4ac)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM171_OFFS                                     (0x4ac)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM171_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM171_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM171_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM171_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM171_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM171_IMAGE_171_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM171_IMAGE_171_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM172_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4b0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM172_OFFS                                     (0x4b0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM172_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM172_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM172_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM172_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM172_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM172_IMAGE_172_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM172_IMAGE_172_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM173_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4b4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM173_OFFS                                     (0x4b4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM173_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM173_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM173_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM173_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM173_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM173_IMAGE_173_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM173_IMAGE_173_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM174_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4b8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM174_OFFS                                     (0x4b8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM174_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM174_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM174_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM174_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM174_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM174_IMAGE_174_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM174_IMAGE_174_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM175_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4bc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM175_OFFS                                     (0x4bc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM175_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM175_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM175_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM175_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM175_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM175_IMAGE_175_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM175_IMAGE_175_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM176_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4c0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM176_OFFS                                     (0x4c0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM176_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM176_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM176_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM176_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM176_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM176_IMAGE_176_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM176_IMAGE_176_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM177_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4c4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM177_OFFS                                     (0x4c4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM177_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM177_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM177_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM177_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM177_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM177_IMAGE_177_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM177_IMAGE_177_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM178_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4c8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM178_OFFS                                     (0x4c8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM178_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM178_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM178_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM178_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM178_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM178_IMAGE_178_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM178_IMAGE_178_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM179_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4cc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM179_OFFS                                     (0x4cc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM179_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM179_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM179_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM179_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM179_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM179_IMAGE_179_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM179_IMAGE_179_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM180_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4d0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM180_OFFS                                     (0x4d0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM180_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM180_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM180_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM180_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM180_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM180_IMAGE_180_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM180_IMAGE_180_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM181_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4d4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM181_OFFS                                     (0x4d4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM181_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM181_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM181_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM181_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM181_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM181_IMAGE_181_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM181_IMAGE_181_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM182_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4d8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM182_OFFS                                     (0x4d8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM182_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM182_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM182_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM182_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM182_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM182_IMAGE_182_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM182_IMAGE_182_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM183_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4dc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM183_OFFS                                     (0x4dc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM183_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM183_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM183_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM183_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM183_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM183_IMAGE_183_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM183_IMAGE_183_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM184_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4e0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM184_OFFS                                     (0x4e0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM184_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM184_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM184_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM184_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM184_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM184_IMAGE_184_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM184_IMAGE_184_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM185_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4e4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM185_OFFS                                     (0x4e4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM185_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM185_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM185_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM185_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM185_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM185_IMAGE_185_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM185_IMAGE_185_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM186_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4e8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM186_OFFS                                     (0x4e8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM186_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM186_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM186_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM186_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM186_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM186_IMAGE_186_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM186_IMAGE_186_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM187_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4ec)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM187_OFFS                                     (0x4ec)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM187_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM187_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM187_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM187_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM187_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM187_IMAGE_187_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM187_IMAGE_187_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM188_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4f0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM188_OFFS                                     (0x4f0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM188_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM188_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM188_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM188_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM188_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM188_IMAGE_188_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM188_IMAGE_188_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM189_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4f4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM189_OFFS                                     (0x4f4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM189_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM189_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM189_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM189_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM189_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM189_IMAGE_189_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM189_IMAGE_189_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM190_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4f8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM190_OFFS                                     (0x4f8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM190_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM190_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM190_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM190_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM190_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM190_IMAGE_190_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM190_IMAGE_190_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM191_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x4fc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM191_OFFS                                     (0x4fc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM191_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM191_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM191_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM191_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM191_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM191_IMAGE_191_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM191_IMAGE_191_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM192_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x500)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM192_OFFS                                     (0x500)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM192_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM192_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM192_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM192_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM192_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM192_IMAGE_192_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM192_IMAGE_192_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM193_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x504)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM193_OFFS                                     (0x504)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM193_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM193_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM193_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM193_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM193_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM193_IMAGE_193_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM193_IMAGE_193_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM194_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x508)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM194_OFFS                                     (0x508)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM194_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM194_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM194_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM194_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM194_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM194_IMAGE_194_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM194_IMAGE_194_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM195_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x50c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM195_OFFS                                     (0x50c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM195_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM195_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM195_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM195_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM195_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM195_IMAGE_195_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM195_IMAGE_195_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM196_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x510)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM196_OFFS                                     (0x510)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM196_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM196_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM196_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM196_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM196_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM196_IMAGE_196_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM196_IMAGE_196_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM197_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x514)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM197_OFFS                                     (0x514)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM197_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM197_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM197_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM197_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM197_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM197_IMAGE_197_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM197_IMAGE_197_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM198_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x518)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM198_OFFS                                     (0x518)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM198_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM198_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM198_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM198_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM198_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM198_IMAGE_198_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM198_IMAGE_198_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM199_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x51c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM199_OFFS                                     (0x51c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM199_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM199_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM199_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM199_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM199_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM199_IMAGE_199_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM199_IMAGE_199_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM200_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x520)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM200_OFFS                                     (0x520)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM200_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM200_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM200_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM200_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM200_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM200_IMAGE_200_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM200_IMAGE_200_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM201_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x524)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM201_OFFS                                     (0x524)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM201_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM201_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM201_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM201_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM201_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM201_IMAGE_201_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM201_IMAGE_201_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM202_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x528)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM202_OFFS                                     (0x528)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM202_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM202_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM202_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM202_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM202_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM202_IMAGE_202_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM202_IMAGE_202_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM203_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x52c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM203_OFFS                                     (0x52c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM203_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM203_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM203_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM203_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM203_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM203_IMAGE_203_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM203_IMAGE_203_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM204_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x530)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM204_OFFS                                     (0x530)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM204_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM204_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM204_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM204_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM204_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM204_IMAGE_204_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM204_IMAGE_204_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM205_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x534)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM205_OFFS                                     (0x534)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM205_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM205_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM205_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM205_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM205_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM205_IMAGE_205_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM205_IMAGE_205_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM206_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x538)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM206_OFFS                                     (0x538)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM206_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM206_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM206_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM206_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM206_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM206_IMAGE_206_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM206_IMAGE_206_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM207_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x53c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM207_OFFS                                     (0x53c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM207_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM207_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM207_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM207_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM207_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM207_IMAGE_207_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM207_IMAGE_207_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM208_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x540)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM208_OFFS                                     (0x540)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM208_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM208_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM208_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM208_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM208_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM208_IMAGE_208_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM208_IMAGE_208_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM209_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x544)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM209_OFFS                                     (0x544)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM209_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM209_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM209_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM209_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM209_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM209_IMAGE_209_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM209_IMAGE_209_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM210_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x548)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM210_OFFS                                     (0x548)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM210_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM210_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM210_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM210_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM210_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM210_IMAGE_210_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM210_IMAGE_210_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM211_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x54c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM211_OFFS                                     (0x54c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM211_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM211_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM211_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM211_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM211_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM211_IMAGE_211_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM211_IMAGE_211_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM212_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x550)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM212_OFFS                                     (0x550)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM212_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM212_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM212_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM212_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM212_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM212_IMAGE_212_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM212_IMAGE_212_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM213_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x554)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM213_OFFS                                     (0x554)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM213_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM213_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM213_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM213_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM213_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM213_IMAGE_213_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM213_IMAGE_213_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM214_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x558)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM214_OFFS                                     (0x558)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM214_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM214_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM214_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM214_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM214_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM214_IMAGE_214_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM214_IMAGE_214_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM215_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x55c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM215_OFFS                                     (0x55c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM215_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM215_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM215_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM215_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM215_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM215_IMAGE_215_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM215_IMAGE_215_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM216_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x560)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM216_OFFS                                     (0x560)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM216_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM216_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM216_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM216_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM216_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM216_IMAGE_216_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM216_IMAGE_216_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM217_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x564)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM217_OFFS                                     (0x564)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM217_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM217_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM217_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM217_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM217_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM217_IMAGE_217_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM217_IMAGE_217_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM218_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x568)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM218_OFFS                                     (0x568)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM218_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM218_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM218_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM218_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM218_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM218_IMAGE_218_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM218_IMAGE_218_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM219_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x56c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM219_OFFS                                     (0x56c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM219_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM219_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM219_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM219_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM219_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM219_IMAGE_219_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM219_IMAGE_219_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM220_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x570)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM220_OFFS                                     (0x570)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM220_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM220_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM220_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM220_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM220_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM220_IMAGE_220_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM220_IMAGE_220_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM221_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x574)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM221_OFFS                                     (0x574)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM221_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM221_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM221_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM221_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM221_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM221_IMAGE_221_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM221_IMAGE_221_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM222_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x578)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM222_OFFS                                     (0x578)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM222_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM222_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM222_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM222_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM222_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM222_IMAGE_222_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM222_IMAGE_222_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM223_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x57c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM223_OFFS                                     (0x57c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM223_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM223_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM223_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM223_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM223_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM223_IMAGE_223_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM223_IMAGE_223_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM224_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x580)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM224_OFFS                                     (0x580)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM224_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM224_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM224_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM224_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM224_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM224_IMAGE_224_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM224_IMAGE_224_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM225_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x584)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM225_OFFS                                     (0x584)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM225_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM225_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM225_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM225_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM225_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM225_IMAGE_225_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM225_IMAGE_225_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM226_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x588)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM226_OFFS                                     (0x588)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM226_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM226_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM226_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM226_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM226_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM226_IMAGE_226_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM226_IMAGE_226_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM227_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x58c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM227_OFFS                                     (0x58c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM227_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM227_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM227_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM227_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM227_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM227_IMAGE_227_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM227_IMAGE_227_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM228_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x590)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM228_OFFS                                     (0x590)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM228_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM228_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM228_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM228_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM228_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM228_IMAGE_228_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM228_IMAGE_228_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM229_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x594)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM229_OFFS                                     (0x594)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM229_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM229_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM229_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM229_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM229_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM229_IMAGE_229_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM229_IMAGE_229_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM230_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x598)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM230_OFFS                                     (0x598)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM230_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM230_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM230_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM230_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM230_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM230_IMAGE_230_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM230_IMAGE_230_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM231_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x59c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM231_OFFS                                     (0x59c)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM231_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM231_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM231_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM231_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM231_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM231_IMAGE_231_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM231_IMAGE_231_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM232_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5a0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM232_OFFS                                     (0x5a0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM232_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM232_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM232_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM232_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM232_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM232_IMAGE_232_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM232_IMAGE_232_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM233_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5a4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM233_OFFS                                     (0x5a4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM233_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM233_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM233_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM233_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM233_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM233_IMAGE_233_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM233_IMAGE_233_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM234_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5a8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM234_OFFS                                     (0x5a8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM234_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM234_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM234_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM234_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM234_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM234_IMAGE_234_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM234_IMAGE_234_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM235_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5ac)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM235_OFFS                                     (0x5ac)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM235_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM235_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM235_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM235_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM235_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM235_IMAGE_235_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM235_IMAGE_235_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM236_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5b0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM236_OFFS                                     (0x5b0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM236_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM236_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM236_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM236_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM236_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM236_IMAGE_236_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM236_IMAGE_236_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM237_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5b4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM237_OFFS                                     (0x5b4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM237_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM237_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM237_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM237_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM237_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM237_IMAGE_237_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM237_IMAGE_237_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM238_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5b8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM238_OFFS                                     (0x5b8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM238_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM238_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM238_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM238_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM238_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM238_IMAGE_238_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM238_IMAGE_238_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM239_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5bc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM239_OFFS                                     (0x5bc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM239_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM239_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM239_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM239_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM239_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM239_IMAGE_239_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM239_IMAGE_239_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM240_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5c0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM240_OFFS                                     (0x5c0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM240_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM240_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM240_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM240_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM240_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM240_IMAGE_240_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM240_IMAGE_240_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM241_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5c4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM241_OFFS                                     (0x5c4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM241_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM241_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM241_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM241_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM241_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM241_IMAGE_241_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM241_IMAGE_241_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM242_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5c8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM242_OFFS                                     (0x5c8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM242_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM242_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM242_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM242_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM242_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM242_IMAGE_242_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM242_IMAGE_242_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM243_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5cc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM243_OFFS                                     (0x5cc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM243_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM243_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM243_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM243_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM243_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM243_IMAGE_243_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM243_IMAGE_243_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM244_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5d0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM244_OFFS                                     (0x5d0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM244_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM244_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM244_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM244_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM244_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM244_IMAGE_244_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM244_IMAGE_244_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM245_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5d4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM245_OFFS                                     (0x5d4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM245_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM245_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM245_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM245_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM245_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM245_IMAGE_245_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM245_IMAGE_245_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM246_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5d8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM246_OFFS                                     (0x5d8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM246_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM246_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM246_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM246_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM246_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM246_IMAGE_246_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM246_IMAGE_246_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM247_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5dc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM247_OFFS                                     (0x5dc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM247_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM247_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM247_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM247_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM247_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM247_IMAGE_247_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM247_IMAGE_247_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM248_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5e0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM248_OFFS                                     (0x5e0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM248_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM248_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM248_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM248_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM248_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM248_IMAGE_248_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM248_IMAGE_248_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM249_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5e4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM249_OFFS                                     (0x5e4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM249_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM249_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM249_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM249_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM249_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM249_IMAGE_249_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM249_IMAGE_249_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM250_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5e8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM250_OFFS                                     (0x5e8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM250_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM250_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM250_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM250_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM250_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM250_IMAGE_250_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM250_IMAGE_250_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM251_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5ec)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM251_OFFS                                     (0x5ec)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM251_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM251_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM251_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM251_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM251_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM251_IMAGE_251_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM251_IMAGE_251_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM252_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5f0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM252_OFFS                                     (0x5f0)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM252_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM252_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM252_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM252_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM252_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM252_IMAGE_252_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM252_IMAGE_252_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM253_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5f4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM253_OFFS                                     (0x5f4)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM253_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM253_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM253_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM253_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM253_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM253_IMAGE_253_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM253_IMAGE_253_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM254_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5f8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM254_OFFS                                     (0x5f8)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM254_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM254_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM254_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM254_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM254_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM254_IMAGE_254_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM254_IMAGE_254_SHFT                                    0

#define HWIO_SPMI1_SPMI_GENI_CFG_RAM255_ADDR(x)                                  ((x) + SPMI1_SPMI_SPMI_GENI_CFG_REG_BASE_OFFS + 0x5fc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM255_OFFS                                     (0x5fc)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM255_RMSK                                       0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM255_IN(x)            \
                in_dword(HWIO_SPMI1_SPMI_GENI_CFG_RAM255_ADDR(x))
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM255_INM(x, m)            \
                in_dword_masked(HWIO_SPMI1_SPMI_GENI_CFG_RAM255_ADDR(x), m)
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM255_IMAGE_255_BMSK                             0x1fffff
#define HWIO_SPMI1_SPMI_GENI_CFG_RAM255_IMAGE_255_SHFT                                    0


//Generic SPMI 0 and 1 Registers based on bus index
/*----------------------------------------------------------------------------
 * MODULE: SPMI_CFG
 *--------------------------------------------------------------------------*/
#define SPMI_CFG_REG_BASE_OFFS                                       0x2D000
#define SPMI_CFG_TOP_BUS_OFFSET                                      0x5000


#define HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,bid,m)                               ((base) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0X0 + (0x4*(m)))
#define HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_OFFS(m)                                    (0X0 + (0x4*(m)))
#define HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_RMSK                                        0xfff000f
#define HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_INI(base,bid,m)                \
                in_dword_masked(HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,bid,m), HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_RMSK)
#define HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_INMI(base,bid,m,mask)        \
                in_dword_masked(HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,bid,m), mask)
#define HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_OUTI(base,bid,m,val)        \
                out_dword(HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,bid,m),val)
#define HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_OUTMI(base,bid,m,mask,val) \
                out_dword_masked_ns(HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base,bid,m),mask,val,HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_INI(base,bid,m))
#define HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_APID2PPID_BMSK                              0xfff0000
#define HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_APID2PPID_SHFT                                     16
#define HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_PERIPH2OWNER_BMSK                                 0xf
#define HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_PERIPH2OWNER_SHFT                                   0

#define HWIO_SPMI_MID_REG_ADDR(x,bid)                                                     ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1800)
#define HWIO_SPMI_MID_REG_OFFS                                                        (0x1800)
#define HWIO_SPMI_MID_REG_RMSK                                                               0x3
#define HWIO_SPMI_MID_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_MID_REG_ADDR(x,bid))
#define HWIO_SPMI_MID_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_MID_REG_ADDR(x,bid), m)
#define HWIO_SPMI_MID_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_MID_REG_ADDR(x,bid),v)
#define HWIO_SPMI_MID_REG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_MID_REG_ADDR(x,bid),m,v,HWIO_SPMI_MID_REG_IN(x,bid))
#define HWIO_SPMI_MID_REG_MID_BMSK                                                           0x3
#define HWIO_SPMI_MID_REG_MID_SHFT                                                             0

#define HWIO_SPMI_CFG_REG_ADDR(x,bid)                                                     ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1804)
#define HWIO_SPMI_CFG_REG_OFFS                                                        (0x1804)
#define HWIO_SPMI_CFG_REG_RMSK                                                         0x3ffffff
#define HWIO_SPMI_CFG_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_CFG_REG_ADDR(x,bid))
#define HWIO_SPMI_CFG_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_CFG_REG_ADDR(x,bid), m)
#define HWIO_SPMI_CFG_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_CFG_REG_ADDR(x,bid),v)
#define HWIO_SPMI_CFG_REG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_CFG_REG_ADDR(x,bid),m,v,HWIO_SPMI_CFG_REG_IN(x,bid))
#define HWIO_SPMI_CFG_REG_LATENCY_CNTR_BMSK                                            0x3800000
#define HWIO_SPMI_CFG_REG_LATENCY_CNTR_SHFT                                                   23
#define HWIO_SPMI_CFG_REG_SCLK_OE_EXTEND_BMSK                                           0x400000
#define HWIO_SPMI_CFG_REG_SCLK_OE_EXTEND_SHFT                                                 22
#define HWIO_SPMI_CFG_REG_RPMH_CLK_REQ_EN_BMSK                                          0x200000
#define HWIO_SPMI_CFG_REG_RPMH_CLK_REQ_EN_SHFT                                                21
#define HWIO_SPMI_CFG_REG_WDT_CFG_BMSK                                                  0x1e0000
#define HWIO_SPMI_CFG_REG_WDT_CFG_SHFT                                                        17
#define HWIO_SPMI_CFG_REG_ARBITER_CTRL_BMSK                                              0x1e000
#define HWIO_SPMI_CFG_REG_ARBITER_CTRL_SHFT                                                   13
#define HWIO_SPMI_CFG_REG_GENI_SPMI_BUS_IN_MASK_DIS_BMSK                                  0x1000
#define HWIO_SPMI_CFG_REG_GENI_SPMI_BUS_IN_MASK_DIS_SHFT                                      12
#define HWIO_SPMI_CFG_REG_ASYNC_SSC_DET_INT_DIS_BMSK                                       0x800
#define HWIO_SPMI_CFG_REG_ASYNC_SSC_DET_INT_DIS_SHFT                                          11
#define HWIO_SPMI_CFG_REG_SSC_Q1_DELAY_DIS_BMSK                                            0x400
#define HWIO_SPMI_CFG_REG_SSC_Q1_DELAY_DIS_SHFT                                               10
#define HWIO_SPMI_CFG_REG_ARB_UNKNOWN_EN_BMSK                                              0x200
#define HWIO_SPMI_CFG_REG_ARB_UNKNOWN_EN_SHFT                                                  9
#define HWIO_SPMI_CFG_REG_SSC_WINDOW_EN_BMSK                                               0x100
#define HWIO_SPMI_CFG_REG_SSC_WINDOW_EN_SHFT                                                   8
#define HWIO_SPMI_CFG_REG_SSC_DET_INT_DIS_BMSK                                              0x80
#define HWIO_SPMI_CFG_REG_SSC_DET_INT_DIS_SHFT                                                 7
#define HWIO_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_IMM_BMSK                                        0x40
#define HWIO_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_IMM_SHFT                                           6
#define HWIO_SPMI_CFG_REG_FORCE_ARB_AFTER_MASTER_TO_BMSK                                    0x20
#define HWIO_SPMI_CFG_REG_FORCE_ARB_AFTER_MASTER_TO_SHFT                                       5
#define HWIO_SPMI_CFG_REG_BUS_IDLE_CONN_MODE_BMSK                                           0x10
#define HWIO_SPMI_CFG_REG_BUS_IDLE_CONN_MODE_SHFT                                              4
#define HWIO_SPMI_CFG_REG_FORCE_MASTER_WRITE_ON_ERROR_BMSK                                   0x8
#define HWIO_SPMI_CFG_REG_FORCE_MASTER_WRITE_ON_ERROR_SHFT                                     3
#define HWIO_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_BMSK                                             0x4
#define HWIO_SPMI_CFG_REG_FORCE_MPM_CLK_REQ_SHFT                                               2
#define HWIO_SPMI_CFG_REG_ARBITER_BYPASS_BMSK                                                0x2
#define HWIO_SPMI_CFG_REG_ARBITER_BYPASS_SHFT                                                  1
#define HWIO_SPMI_CFG_REG_ARBITER_ENABLE_BMSK                                                0x1
#define HWIO_SPMI_CFG_REG_ARBITER_ENABLE_SHFT                                                  0

#define HWIO_SPMI_SEC_DISABLE_REG_ADDR(x,bid)                                             ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1808)
#define HWIO_SPMI_SEC_DISABLE_REG_OFFS                                                (0x1808)
#define HWIO_SPMI_SEC_DISABLE_REG_RMSK                                                       0x1
#define HWIO_SPMI_SEC_DISABLE_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_SEC_DISABLE_REG_ADDR(x,bid))
#define HWIO_SPMI_SEC_DISABLE_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_SEC_DISABLE_REG_ADDR(x,bid), m)
#define HWIO_SPMI_SEC_DISABLE_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_SEC_DISABLE_REG_ADDR(x,bid),v)
#define HWIO_SPMI_SEC_DISABLE_REG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_SEC_DISABLE_REG_ADDR(x,bid),m,v,HWIO_SPMI_SEC_DISABLE_REG_IN(x,bid))
#define HWIO_SPMI_SEC_DISABLE_REG_DISABLE_SECURITY_BMSK                                      0x1
#define HWIO_SPMI_SEC_DISABLE_REG_DISABLE_SECURITY_SHFT                                        0

#define HWIO_SPMI_HW_VERSION_ADDR(x,bid)                                                  ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x180c)
#define HWIO_SPMI_HW_VERSION_OFFS                                                     (0x180c)
#define HWIO_SPMI_HW_VERSION_RMSK                                                     0xff000fff
#define HWIO_SPMI_HW_VERSION_IN(x,bid)            \
                in_dword(HWIO_SPMI_HW_VERSION_ADDR(x,bid))
#define HWIO_SPMI_HW_VERSION_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_HW_VERSION_ADDR(x,bid), m)
#define HWIO_SPMI_HW_VERSION_HW_VERSION_RUNNING_R_BMSK                                0xff000000
#define HWIO_SPMI_HW_VERSION_HW_VERSION_RUNNING_R_SHFT                                        24
#define HWIO_SPMI_HW_VERSION_HW_VERSION_MAJOR_BMSK                                         0xf00
#define HWIO_SPMI_HW_VERSION_HW_VERSION_MAJOR_SHFT                                             8
#define HWIO_SPMI_HW_VERSION_HW_VERSION_MINOR_BMSK                                          0xf0
#define HWIO_SPMI_HW_VERSION_HW_VERSION_MINOR_SHFT                                             4
#define HWIO_SPMI_HW_VERSION_HW_VERSION_STEP_BMSK                                            0xf
#define HWIO_SPMI_HW_VERSION_HW_VERSION_STEP_SHFT                                              0

#define HWIO_SPMI_CGC_CTRL_ADDR(x,bid)                                                    ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1810)
#define HWIO_SPMI_CGC_CTRL_OFFS                                                       (0x1810)
#define HWIO_SPMI_CGC_CTRL_RMSK                                                             0x7f
#define HWIO_SPMI_CGC_CTRL_IN(x,bid)            \
                in_dword(HWIO_SPMI_CGC_CTRL_ADDR(x,bid))
#define HWIO_SPMI_CGC_CTRL_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_CGC_CTRL_ADDR(x,bid), m)
#define HWIO_SPMI_CGC_CTRL_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_CGC_CTRL_ADDR(x,bid),v)
#define HWIO_SPMI_CGC_CTRL_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_CGC_CTRL_ADDR(x,bid),m,v,HWIO_SPMI_CGC_CTRL_IN(x,bid))
#define HWIO_SPMI_CGC_CTRL_MAP_LOGIC_CLK_CGC_ON_BMSK                                        0x40
#define HWIO_SPMI_CGC_CTRL_MAP_LOGIC_CLK_CGC_ON_SHFT                                           6
#define HWIO_SPMI_CGC_CTRL_RPU_CLK_CGC_ON_BMSK                                              0x20
#define HWIO_SPMI_CGC_CTRL_RPU_CLK_CGC_ON_SHFT                                                 5
#define HWIO_SPMI_CGC_CTRL_MWB_CLK_CGC_ON_BMSK                                              0x10
#define HWIO_SPMI_CGC_CTRL_MWB_CLK_CGC_ON_SHFT                                                 4
#define HWIO_SPMI_CGC_CTRL_PIC_CLK_CGC_ON_BMSK                                               0x8
#define HWIO_SPMI_CGC_CTRL_PIC_CLK_CGC_ON_SHFT                                                 3
#define HWIO_SPMI_CGC_CTRL_PAC_CLK_CGC_ON_BMSK                                               0x4
#define HWIO_SPMI_CGC_CTRL_PAC_CLK_CGC_ON_SHFT                                                 2
#define HWIO_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_WR_CLK_CGC_ON_BMSK                                 0x2
#define HWIO_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_WR_CLK_CGC_ON_SHFT                                   1
#define HWIO_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_CLK_CGC_ON_BMSK                                    0x1
#define HWIO_SPMI_CGC_CTRL_CFG_AHB_BRIDGE_CLK_CGC_ON_SHFT                                      0

#define HWIO_SPMI_MWB_ENABLE_REG_ADDR(x,bid)                                              ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1814)
#define HWIO_SPMI_MWB_ENABLE_REG_OFFS                                                 (0x1814)
#define HWIO_SPMI_MWB_ENABLE_REG_RMSK                                                        0x1
#define HWIO_SPMI_MWB_ENABLE_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_MWB_ENABLE_REG_ADDR(x,bid))
#define HWIO_SPMI_MWB_ENABLE_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_MWB_ENABLE_REG_ADDR(x,bid), m)
#define HWIO_SPMI_MWB_ENABLE_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_MWB_ENABLE_REG_ADDR(x,bid),v)
#define HWIO_SPMI_MWB_ENABLE_REG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_MWB_ENABLE_REG_ADDR(x,bid),m,v,HWIO_SPMI_MWB_ENABLE_REG_IN(x,bid))
#define HWIO_SPMI_MWB_ENABLE_REG_MWB_ENABLE_BMSK                                             0x1
#define HWIO_SPMI_MWB_ENABLE_REG_MWB_ENABLE_SHFT                                               0

#define HWIO_SPMI_CHAR_CFG_ADDR(x,bid)                                                    ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1840)
#define HWIO_SPMI_CHAR_CFG_OFFS                                                       (0x1840)
#define HWIO_SPMI_CHAR_CFG_RMSK                                                          0xfff11
#define HWIO_SPMI_CHAR_CFG_IN(x,bid)            \
                in_dword(HWIO_SPMI_CHAR_CFG_ADDR(x,bid))
#define HWIO_SPMI_CHAR_CFG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_CHAR_CFG_ADDR(x,bid), m)
#define HWIO_SPMI_CHAR_CFG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_CHAR_CFG_ADDR(x,bid),v)
#define HWIO_SPMI_CHAR_CFG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_CHAR_CFG_ADDR(x,bid),m,v,HWIO_SPMI_CHAR_CFG_IN(x,bid))
#define HWIO_SPMI_CHAR_CFG_CHAR_MODE_BMSK                                                0xff000
#define HWIO_SPMI_CHAR_CFG_CHAR_MODE_SHFT                                                     12
#define HWIO_SPMI_CHAR_CFG_CHAR_STATUS_BMSK                                                0xf00
#define HWIO_SPMI_CHAR_CFG_CHAR_STATUS_SHFT                                                    8
#define HWIO_SPMI_CHAR_CFG_DIRECTION_BMSK                                                   0x10
#define HWIO_SPMI_CHAR_CFG_DIRECTION_SHFT                                                      4
#define HWIO_SPMI_CHAR_CFG_ENABLE_BMSK                                                       0x1
#define HWIO_SPMI_CHAR_CFG_ENABLE_SHFT                                                         0

#define HWIO_SPMI_CHAR_DATA_n_ADDR(base,bid,n)                                            ((base) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0X1844 + (0x4*(n)))
#define HWIO_SPMI_CHAR_DATA_n_OFFS(n)                                                 (0X1844 + (0x4*(n)))
#define HWIO_SPMI_CHAR_DATA_n_RMSK                                                        0xffff
#define HWIO_SPMI_CHAR_DATA_n_INI(base,bid,n)                \
                in_dword_masked(HWIO_SPMI_CHAR_DATA_n_ADDR(base,bid,n), HWIO_SPMI_CHAR_DATA_n_RMSK)
#define HWIO_SPMI_CHAR_DATA_n_INMI(base,bid,n,mask)        \
                in_dword_masked(HWIO_SPMI_CHAR_DATA_n_ADDR(base,bid,n), mask)
#define HWIO_SPMI_CHAR_DATA_n_OUTI(base,bid,n,val)        \
                out_dword(HWIO_SPMI_CHAR_DATA_n_ADDR(base,bid,n),val)
#define HWIO_SPMI_CHAR_DATA_n_OUTMI(base,bid,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI_CHAR_DATA_n_ADDR(base,bid,n),mask,val,HWIO_SPMI_CHAR_DATA_n_INI(base,bid,n))
#define HWIO_SPMI_CHAR_DATA_n_DIN_ACTUAL_BMSK                                             0xff00
#define HWIO_SPMI_CHAR_DATA_n_DIN_ACTUAL_SHFT                                                  8
#define HWIO_SPMI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_BMSK                                        0xff
#define HWIO_SPMI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_SHFT                                           0

#define HWIO_SPMI_CMPR_EN_REG_ADDR(x,bid)                                                 ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1854)
#define HWIO_SPMI_CMPR_EN_REG_OFFS                                                    (0x1854)
#define HWIO_SPMI_CMPR_EN_REG_RMSK                                                           0x1
#define HWIO_SPMI_CMPR_EN_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_CMPR_EN_REG_ADDR(x,bid))
#define HWIO_SPMI_CMPR_EN_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_CMPR_EN_REG_ADDR(x,bid), m)
#define HWIO_SPMI_CMPR_EN_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_CMPR_EN_REG_ADDR(x,bid),v)
#define HWIO_SPMI_CMPR_EN_REG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_CMPR_EN_REG_ADDR(x,bid),m,v,HWIO_SPMI_CMPR_EN_REG_IN(x,bid))
#define HWIO_SPMI_CMPR_EN_REG_CMPR_ENABLE_BMSK                                               0x1
#define HWIO_SPMI_CMPR_EN_REG_CMPR_ENABLE_SHFT                                                 0

#define HWIO_SPMI_SNOOPER_CFG_REG_ADDR(x,bid)                                             ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1858)
#define HWIO_SPMI_SNOOPER_CFG_REG_OFFS                                                (0x1858)
#define HWIO_SPMI_SNOOPER_CFG_REG_RMSK                                                     0x3ff
#define HWIO_SPMI_SNOOPER_CFG_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_SNOOPER_CFG_REG_ADDR(x,bid))
#define HWIO_SPMI_SNOOPER_CFG_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_SNOOPER_CFG_REG_ADDR(x,bid), m)
#define HWIO_SPMI_SNOOPER_CFG_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_SNOOPER_CFG_REG_ADDR(x,bid),v)
#define HWIO_SPMI_SNOOPER_CFG_REG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_SNOOPER_CFG_REG_ADDR(x,bid),m,v,HWIO_SPMI_SNOOPER_CFG_REG_IN(x,bid))
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_BMSK                                 0x200
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_SHFT                                     9
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_SM_MM_MODE_BMSK                      0x100
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_SM_MM_MODE_SHFT                          8
#define HWIO_SPMI_SNOOPER_CFG_REG_SNOOPER_SW_RST_EN_BMSK                                    0x80
#define HWIO_SPMI_SNOOPER_CFG_REG_SNOOPER_SW_RST_EN_SHFT                                       7
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_FROM_SPMI_M_EN_BMSK                   0x40
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SW_RST_FROM_SPMI_M_EN_SHFT                      6
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_TEST_BUS_SELECT_BMSK                   0x38
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_TEST_BUS_SELECT_SHFT                      3
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_MODE_BMSK                                     0x4
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_MODE_SHFT                                       2
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_SSC_DET_CFG_BMSK                        0x3
#define HWIO_SPMI_SNOOPER_CFG_REG_SPMI_SNOOPER_SLAVE_SSC_DET_CFG_SHFT                          0

#define HWIO_SPMI_STATUS_REG_ADDR(x,bid)                                                  ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x185c)
#define HWIO_SPMI_STATUS_REG_OFFS                                                     (0x185c)
#define HWIO_SPMI_STATUS_REG_RMSK                                                            0x1
#define HWIO_SPMI_STATUS_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_STATUS_REG_ADDR(x,bid))
#define HWIO_SPMI_STATUS_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_STATUS_REG_ADDR(x,bid), m)
#define HWIO_SPMI_STATUS_REG_ARB_IS_BOM_BMSK                                                 0x1
#define HWIO_SPMI_STATUS_REG_ARB_IS_BOM_SHFT                                                   0

#define HWIO_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,bid,n)                                       ((base) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0X1A00 + (0x4*(n)))
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_OFFS(n)                                            (0X1A00 + (0x4*(n)))
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_RMSK                                               0xff8fffff
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_INI(base,bid,n)                \
                in_dword_masked(HWIO_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,bid,n), HWIO_SPMI_PIC_RCS_VIOCTL_n_RMSK)
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_INMI(base,bid,n,mask)        \
                in_dword_masked(HWIO_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,bid,n), mask)
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_OUTI(base,bid,n,val)        \
                out_dword(HWIO_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,bid,n),val)
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_OUTMI(base,bid,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI_PIC_RCS_VIOCTL_n_ADDR(base,bid,n),mask,val,HWIO_SPMI_PIC_RCS_VIOCTL_n_INI(base,bid,n))
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_MSG_MASK_BMSK                                      0xff000000
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_MSG_MASK_SHFT                                              24
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_VIOCTL_EN_BMSK                                       0x800000
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_VIOCTL_EN_SHFT                                             23
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_SID_BMSK                                              0xf0000
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_SID_SHFT                                                   16
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_PID_BMSK                                               0xff00
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_PID_SHFT                                                    8
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_RCS_MSG_BMSK                                             0xff
#define HWIO_SPMI_PIC_RCS_VIOCTL_n_RCS_MSG_SHFT                                                0

#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,bid,n)                        ((base) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0X1A80 + (0x4*(n)))
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_OFFS(n)                             (0X1A80 + (0x4*(n)))
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_RMSK                                       0x1
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_INI(base,bid,n)                \
                in_dword_masked(HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,bid,n), HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_RMSK)
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_INMI(base,bid,n,mask)        \
                in_dword_masked(HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,bid,n), mask)
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_OUTI(base,bid,n,val)        \
                out_dword(HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,bid,n),val)
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_OUTMI(base,bid,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ADDR(base,bid,n),mask,val,HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_INI(base,bid,n))
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ENABLE_BMSK                                0x1
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CFG_n_ENABLE_SHFT                                  0

#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x,bid)                               ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1b00)
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_OFFS                                  (0x1b00)
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_RMSK                                        0xff
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_IN(x,bid)            \
                in_dword(HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x,bid))
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x,bid), m)
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x,bid),v)
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_ADDR(x,bid),m,v,HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_IN(x,bid))
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_CTR_CFG_BMSK                                0xff
#define HWIO_SPMI_PIC_RCS_VIOCTL_SELF_CLEAR_CTR_CTR_CFG_SHFT                                   0

#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,bid,n)                                     ((base) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0X1B80 + (0x4*(n)))
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_OFFS(n)                                          (0X1B80 + (0x4*(n)))
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_RMSK                                             0xff8fffff
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_INI(base,bid,n)                \
                in_dword_masked(HWIO_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,bid,n), HWIO_SPMI_PIC_RCS_VIOCTL_N_n_RMSK)
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_INMI(base,bid,n,mask)        \
                in_dword_masked(HWIO_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,bid,n), mask)
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_OUTI(base,bid,n,val)        \
                out_dword(HWIO_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,bid,n),val)
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_OUTMI(base,bid,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI_PIC_RCS_VIOCTL_N_n_ADDR(base,bid,n),mask,val,HWIO_SPMI_PIC_RCS_VIOCTL_N_n_INI(base,bid,n))
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_MSG_MASK_BMSK                                    0xff000000
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_MSG_MASK_SHFT                                            24
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_VIOCTL_EN_BMSK                                     0x800000
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_VIOCTL_EN_SHFT                                           23
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_SID_BMSK                                            0xf0000
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_SID_SHFT                                                 16
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_PID_BMSK                                             0xff00
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_PID_SHFT                                                  8
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_RCS_MSG_BMSK                                           0xff
#define HWIO_SPMI_PIC_RCS_VIOCTL_N_n_RCS_MSG_SHFT                                              0

#define HWIO_SPMI_WDT_CTRL_REG_0_ADDR(x,bid)                                              ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1c00)
#define HWIO_SPMI_WDT_CTRL_REG_0_OFFS                                                 (0x1c00)
#define HWIO_SPMI_WDT_CTRL_REG_0_RMSK                                                    0x3ffff
#define HWIO_SPMI_WDT_CTRL_REG_0_IN(x,bid)            \
                in_dword(HWIO_SPMI_WDT_CTRL_REG_0_ADDR(x,bid))
#define HWIO_SPMI_WDT_CTRL_REG_0_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_WDT_CTRL_REG_0_ADDR(x,bid), m)
#define HWIO_SPMI_WDT_CTRL_REG_0_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_WDT_CTRL_REG_0_ADDR(x,bid),v)
#define HWIO_SPMI_WDT_CTRL_REG_0_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_WDT_CTRL_REG_0_ADDR(x,bid),m,v,HWIO_SPMI_WDT_CTRL_REG_0_IN(x,bid))
#define HWIO_SPMI_WDT_CTRL_REG_0_WDT_ARB_EN_CRTL_BMSK                                    0x20000
#define HWIO_SPMI_WDT_CTRL_REG_0_WDT_ARB_EN_CRTL_SHFT                                         17
#define HWIO_SPMI_WDT_CTRL_REG_0_PMIC_ARB_ARST_EN_BMSK                                   0x10000
#define HWIO_SPMI_WDT_CTRL_REG_0_PMIC_ARB_ARST_EN_SHFT                                        16
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_M_ARB_ARST_EN_BMSK                                  0x8000
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_M_ARB_ARST_EN_SHFT                                      15
#define HWIO_SPMI_WDT_CTRL_REG_0_GENI_ARST_EN_BMSK                                        0x4000
#define HWIO_SPMI_WDT_CTRL_REG_0_GENI_ARST_EN_SHFT                                            14
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_ARST_ASSERT_BMSK                            0x2000
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_ARST_ASSERT_SHFT                                13
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_ARST_ASSERT_BMSK                            0x1000
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_ARST_ASSERT_SHFT                                12
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_SCLK_ARES_ASSERT_BMSK                                0x800
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_SCLK_ARES_ASSERT_SHFT                                   11
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_ARST_ASSERT_BMSK                         0x400
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_ARST_ASSERT_SHFT                            10
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_BUS_CLK_GATE_EN_BMSK                                 0x200
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_BUS_CLK_GATE_EN_SHFT                                     9
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_GATE_EN_BMSK                                 0x100
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_AHB_CLK_GATE_EN_SHFT                                     8
#define HWIO_SPMI_WDT_CTRL_REG_0_PMIC_ARB_CLK_GATE_EN_BMSK                                  0x80
#define HWIO_SPMI_WDT_CTRL_REG_0_PMIC_ARB_CLK_GATE_EN_SHFT                                     7
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_GATE_EN_BMSK                                  0x40
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_SER_CLK_GATE_EN_SHFT                                     6
#define HWIO_SPMI_WDT_CTRL_REG_0_SLEEP_CLK_GATE_EN_BMSK                                     0x20
#define HWIO_SPMI_WDT_CTRL_REG_0_SLEEP_CLK_GATE_EN_SHFT                                        5
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_GATE_EN_BMSK                              0x10
#define HWIO_SPMI_WDT_CTRL_REG_0_SPMI_AOD_SER_CLK_GATE_EN_SHFT                                 4
#define HWIO_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_EN_BMSK                                       0x8
#define HWIO_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_EN_SHFT                                         3
#define HWIO_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_CLR_BMSK                                      0x4
#define HWIO_SPMI_WDT_CTRL_REG_0_WDT_DEBUG_CNT_CLR_SHFT                                        2
#define HWIO_SPMI_WDT_CTRL_REG_0_WDT_AUTO_HW_EN_BMSK                                         0x2
#define HWIO_SPMI_WDT_CTRL_REG_0_WDT_AUTO_HW_EN_SHFT                                           1
#define HWIO_SPMI_WDT_CTRL_REG_0_WDT_CNT_EN_BMSK                                             0x1
#define HWIO_SPMI_WDT_CTRL_REG_0_WDT_CNT_EN_SHFT                                               0

#define HWIO_SPMI_WDT_CTRL_REG_1_ADDR(x,bid)                                              ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1c04)
#define HWIO_SPMI_WDT_CTRL_REG_1_OFFS                                                 (0x1c04)
#define HWIO_SPMI_WDT_CTRL_REG_1_RMSK                                                   0xfff00f
#define HWIO_SPMI_WDT_CTRL_REG_1_IN(x,bid)            \
                in_dword(HWIO_SPMI_WDT_CTRL_REG_1_ADDR(x,bid))
#define HWIO_SPMI_WDT_CTRL_REG_1_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_WDT_CTRL_REG_1_ADDR(x,bid), m)
#define HWIO_SPMI_WDT_CTRL_REG_1_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_WDT_CTRL_REG_1_ADDR(x,bid),v)
#define HWIO_SPMI_WDT_CTRL_REG_1_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_WDT_CTRL_REG_1_ADDR(x,bid),m,v,HWIO_SPMI_WDT_CTRL_REG_1_IN(x,bid))
#define HWIO_SPMI_WDT_CTRL_REG_1_RESET_ASSERT_INTERVAL_BMSK                             0xf00000
#define HWIO_SPMI_WDT_CTRL_REG_1_RESET_ASSERT_INTERVAL_SHFT                                   20
#define HWIO_SPMI_WDT_CTRL_REG_1_CLK_GATE_EN_TO_RST_ASSERT_INTERVAL_BMSK                 0xf0000
#define HWIO_SPMI_WDT_CTRL_REG_1_CLK_GATE_EN_TO_RST_ASSERT_INTERVAL_SHFT                      16
#define HWIO_SPMI_WDT_CTRL_REG_1_ARB_EN_TO_CLK_GATE_EN_INTERVAL_BMSK                      0xf000
#define HWIO_SPMI_WDT_CTRL_REG_1_ARB_EN_TO_CLK_GATE_EN_INTERVAL_SHFT                          12
#define HWIO_SPMI_WDT_CTRL_REG_1_WDT_CTR_EXPIRY_VALUE_BMSK                                   0xf
#define HWIO_SPMI_WDT_CTRL_REG_1_WDT_CTR_EXPIRY_VALUE_SHFT                                     0

#define HWIO_SPMI_WDT_CTRL_REG_2_ADDR(x,bid)                                              ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1c08)
#define HWIO_SPMI_WDT_CTRL_REG_2_OFFS                                                 (0x1c08)
#define HWIO_SPMI_WDT_CTRL_REG_2_RMSK                                                        0x3
#define HWIO_SPMI_WDT_CTRL_REG_2_IN(x,bid)            \
                in_dword(HWIO_SPMI_WDT_CTRL_REG_2_ADDR(x,bid))
#define HWIO_SPMI_WDT_CTRL_REG_2_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_WDT_CTRL_REG_2_ADDR(x,bid), m)
#define HWIO_SPMI_WDT_CTRL_REG_2_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_WDT_CTRL_REG_2_ADDR(x,bid),v)
#define HWIO_SPMI_WDT_CTRL_REG_2_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_WDT_CTRL_REG_2_ADDR(x,bid),m,v,HWIO_SPMI_WDT_CTRL_REG_2_IN(x,bid))
#define HWIO_SPMI_WDT_CTRL_REG_2_WDT_SCLK_RST_MODE_BMSK                                      0x2
#define HWIO_SPMI_WDT_CTRL_REG_2_WDT_SCLK_RST_MODE_SHFT                                        1
#define HWIO_SPMI_WDT_CTRL_REG_2_WDT_SW_RST_BMSK                                             0x1
#define HWIO_SPMI_WDT_CTRL_REG_2_WDT_SW_RST_SHFT                                               0

#define HWIO_SPMI_WDT_STATUS_REG_ADDR(x,bid)                                              ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1c0c)
#define HWIO_SPMI_WDT_STATUS_REG_OFFS                                                 (0x1c0c)
#define HWIO_SPMI_WDT_STATUS_REG_RMSK                                                        0x1
#define HWIO_SPMI_WDT_STATUS_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_WDT_STATUS_REG_ADDR(x,bid))
#define HWIO_SPMI_WDT_STATUS_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_WDT_STATUS_REG_ADDR(x,bid), m)
#define HWIO_SPMI_WDT_STATUS_REG_WDT_DONE_BMSK                                               0x1
#define HWIO_SPMI_WDT_STATUS_REG_WDT_DONE_SHFT                                                 0

#define HWIO_SPMI_WDT_DEBUG_CNT_REG_ADDR(x,bid)                                           ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x1c10)
#define HWIO_SPMI_WDT_DEBUG_CNT_REG_OFFS                                              (0x1c10)
#define HWIO_SPMI_WDT_DEBUG_CNT_REG_RMSK                                                  0xffff
#define HWIO_SPMI_WDT_DEBUG_CNT_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_WDT_DEBUG_CNT_REG_ADDR(x,bid))
#define HWIO_SPMI_WDT_DEBUG_CNT_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_WDT_DEBUG_CNT_REG_ADDR(x,bid), m)
#define HWIO_SPMI_WDT_DEBUG_CNT_REG_WDT_DEBUG_CNT_BMSK                                    0xffff
#define HWIO_SPMI_WDT_DEBUG_CNT_REG_WDT_DEBUG_CNT_SHFT                                         0

#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_ADDR(x,bid)                                         ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x2000)
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_OFFS                                            (0x2000)
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_RMSK                                                0x3fff
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_IN(x,bid)            \
                in_dword(HWIO_SPMI_PROTOCOL_IRQ_STATUS_ADDR(x,bid))
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_PROTOCOL_IRQ_STATUS_ADDR(x,bid), m)
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_WDT_RST_COMPLETION_BMSK                             0x2000
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_WDT_RST_COMPLETION_SHFT                                 13
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_WDT_EXPIRY_BMSK                                     0x1000
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_WDT_EXPIRY_SHFT                                         12
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_DISCONNECTED_BMSK                            0x800
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_DISCONNECTED_SHFT                               11
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_CONNECTED_BMSK                               0x400
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_ARBITER_CONNECTED_SHFT                                  10
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_PERIH_IRQ_LOST_BMSK                                  0x200
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_PERIH_IRQ_LOST_SHFT                                      9
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_UNEXPECTED_SSC_BMSK                                  0x100
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_UNEXPECTED_SSC_SHFT                                      8
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                  0x80
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                     7
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                   0x40
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                      6
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_FALSE_MASTER_ARBITRATION_WIN_BMSK                     0x20
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_FALSE_MASTER_ARBITRATION_WIN_SHFT                        5
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_FALSE_BUS_REQUEST_BMSK                                0x10
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_FALSE_BUS_REQUEST_SHFT                                   4
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_UNSUPPORTED_COMMAND_BMSK                               0x8
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_UNSUPPORTED_COMMAND_SHFT                                 3
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                      0x4
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                        2
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                      0x2
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                        1
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                     0x1
#define HWIO_SPMI_PROTOCOL_IRQ_STATUS_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                       0

#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x,bid)                                         ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x2004)
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_OFFS                                            (0x2004)
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_RMSK                                                0x3fff
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_IN(x,bid)            \
                in_dword(HWIO_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x,bid))
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x,bid), m)
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x,bid),v)
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_PROTOCOL_IRQ_ENABLE_ADDR(x,bid),m,v,HWIO_SPMI_PROTOCOL_IRQ_ENABLE_IN(x,bid))
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_WDT_RST_COMPLETION_BMSK                             0x2000
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_WDT_RST_COMPLETION_SHFT                                 13
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_WDT_EXPIRY_BMSK                                     0x1000
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_WDT_EXPIRY_SHFT                                         12
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_DISCONNECTED_BMSK                            0x800
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_DISCONNECTED_SHFT                               11
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_CONNECTED_BMSK                               0x400
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_ARBITER_CONNECTED_SHFT                                  10
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_PERIH_IRQ_LOST_BMSK                                  0x200
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_PERIH_IRQ_LOST_SHFT                                      9
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_UNEXPECTED_SSC_BMSK                                  0x100
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_UNEXPECTED_SSC_SHFT                                      8
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                  0x80
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                     7
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                   0x40
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                      6
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_MASTER_ARBITRATION_WIN_BMSK                     0x20
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_MASTER_ARBITRATION_WIN_SHFT                        5
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_BUS_REQUEST_BMSK                                0x10
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_FALSE_BUS_REQUEST_SHFT                                   4
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_UNSUPPORTED_COMMAND_BMSK                               0x8
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_UNSUPPORTED_COMMAND_SHFT                                 3
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                      0x4
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                        2
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                      0x2
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                        1
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                     0x1
#define HWIO_SPMI_PROTOCOL_IRQ_ENABLE_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                       0

#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_ADDR(x,bid)                                          ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x2008)
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_OFFS                                             (0x2008)
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_RMSK                                                 0x3fff
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_PROTOCOL_IRQ_CLEAR_ADDR(x,bid),v)
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_WDT_RST_COMPLETION_BMSK                              0x2000
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_WDT_RST_COMPLETION_SHFT                                  13
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_WDT_EXPIRY_BMSK                                      0x1000
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_WDT_EXPIRY_SHFT                                          12
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_DISCONNECTED_BMSK                             0x800
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_DISCONNECTED_SHFT                                11
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_CONNECTED_BMSK                                0x400
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_ARBITER_CONNECTED_SHFT                                   10
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_PERIH_IRQ_LOST_BMSK                                   0x200
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_PERIH_IRQ_LOST_SHFT                                       9
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_UNEXPECTED_SSC_BMSK                                   0x100
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_UNEXPECTED_SSC_SHFT                                       8
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                   0x80
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                      7
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                    0x40
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                       6
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_MASTER_ARBITRATION_WIN_BMSK                      0x20
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_MASTER_ARBITRATION_WIN_SHFT                         5
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_BUS_REQUEST_BMSK                                 0x10
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_FALSE_BUS_REQUEST_SHFT                                    4
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_UNSUPPORTED_COMMAND_BMSK                                0x8
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_UNSUPPORTED_COMMAND_SHFT                                  3
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                       0x4
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                         2
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                       0x2
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                         1
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                      0x1
#define HWIO_SPMI_PROTOCOL_IRQ_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                        0

#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_ADDR(x,bid)                                         ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x200c)
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_OFFS                                            (0x200c)
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_RMSK                                                0x3fff
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_PROTOCOL_IRQ_EN_SET_ADDR(x,bid),v)
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_WDT_RST_COMPLETION_BMSK                             0x2000
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_WDT_RST_COMPLETION_SHFT                                 13
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_WDT_EXPIRY_BMSK                                     0x1000
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_WDT_EXPIRY_SHFT                                         12
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_DISCONNECTED_BMSK                            0x800
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_DISCONNECTED_SHFT                               11
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_CONNECTED_BMSK                               0x400
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_ARBITER_CONNECTED_SHFT                                  10
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_PERIH_IRQ_LOST_BMSK                                  0x200
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_PERIH_IRQ_LOST_SHFT                                      9
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_UNEXPECTED_SSC_BMSK                                  0x100
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_UNEXPECTED_SSC_SHFT                                      8
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                  0x80
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                     7
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                   0x40
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                      6
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_MASTER_ARBITRATION_WIN_BMSK                     0x20
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_MASTER_ARBITRATION_WIN_SHFT                        5
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_BUS_REQUEST_BMSK                                0x10
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_FALSE_BUS_REQUEST_SHFT                                   4
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_UNSUPPORTED_COMMAND_BMSK                               0x8
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_UNSUPPORTED_COMMAND_SHFT                                 3
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                      0x4
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                        2
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                      0x2
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                        1
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                     0x1
#define HWIO_SPMI_PROTOCOL_IRQ_EN_SET_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                       0

#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_ADDR(x,bid)                                       ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x2010)
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_OFFS                                          (0x2010)
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_RMSK                                              0x3fff
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_ADDR(x,bid),v)
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_RST_COMPLETION_BMSK                           0x2000
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_RST_COMPLETION_SHFT                               13
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_EXPIRY_BMSK                                   0x1000
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_WDT_EXPIRY_SHFT                                       12
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_DISCONNECTED_BMSK                          0x800
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_DISCONNECTED_SHFT                             11
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_CONNECTED_BMSK                             0x400
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_ARBITER_CONNECTED_SHFT                                10
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_PERIH_IRQ_LOST_BMSK                                0x200
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_PERIH_IRQ_LOST_SHFT                                    9
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNEXPECTED_SSC_BMSK                                0x100
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNEXPECTED_SSC_SHFT                                    8
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                0x80
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                   7
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                 0x40
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                    6
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_MASTER_ARBITRATION_WIN_BMSK                   0x20
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_MASTER_ARBITRATION_WIN_SHFT                      5
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_BUS_REQUEST_BMSK                              0x10
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_FALSE_BUS_REQUEST_SHFT                                 4
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNSUPPORTED_COMMAND_BMSK                             0x8
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_UNSUPPORTED_COMMAND_SHFT                               3
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                    0x4
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                      2
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                    0x2
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                      1
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                   0x1
#define HWIO_SPMI_PROTOCOL_IRQ_EN_CLEAR_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                     0

#define HWIO_SPMI_TEST_BUS_CTRL_ADDR(x,bid)                                               ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x3000)
#define HWIO_SPMI_TEST_BUS_CTRL_OFFS                                                  (0x3000)
#define HWIO_SPMI_TEST_BUS_CTRL_RMSK                                                       0x3ff
#define HWIO_SPMI_TEST_BUS_CTRL_IN(x,bid)            \
                in_dword(HWIO_SPMI_TEST_BUS_CTRL_ADDR(x,bid))
#define HWIO_SPMI_TEST_BUS_CTRL_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_TEST_BUS_CTRL_ADDR(x,bid), m)
#define HWIO_SPMI_TEST_BUS_CTRL_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_TEST_BUS_CTRL_ADDR(x,bid),v)
#define HWIO_SPMI_TEST_BUS_CTRL_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_TEST_BUS_CTRL_ADDR(x,bid),m,v,HWIO_SPMI_TEST_BUS_CTRL_IN(x,bid))
#define HWIO_SPMI_TEST_BUS_CTRL_TEST_BUS_ARB_SEL_BMSK                                      0x3c0
#define HWIO_SPMI_TEST_BUS_CTRL_TEST_BUS_ARB_SEL_SHFT                                          6
#define HWIO_SPMI_TEST_BUS_CTRL_TEST_BUS_INT_SEL_BMSK                                       0x3c
#define HWIO_SPMI_TEST_BUS_CTRL_TEST_BUS_INT_SEL_SHFT                                          2
#define HWIO_SPMI_TEST_BUS_CTRL_TEST_BUS_SEL_BMSK                                            0x3
#define HWIO_SPMI_TEST_BUS_CTRL_TEST_BUS_SEL_SHFT                                              0

#define HWIO_SPMI_HW_SW_EVENTS_CTRL_ADDR(x,bid)                                           ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x3004)
#define HWIO_SPMI_HW_SW_EVENTS_CTRL_OFFS                                              (0x3004)
#define HWIO_SPMI_HW_SW_EVENTS_CTRL_RMSK                                                     0x7
#define HWIO_SPMI_HW_SW_EVENTS_CTRL_IN(x,bid)            \
                in_dword(HWIO_SPMI_HW_SW_EVENTS_CTRL_ADDR(x,bid))
#define HWIO_SPMI_HW_SW_EVENTS_CTRL_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_HW_SW_EVENTS_CTRL_ADDR(x,bid), m)
#define HWIO_SPMI_HW_SW_EVENTS_CTRL_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_HW_SW_EVENTS_CTRL_ADDR(x,bid),v)
#define HWIO_SPMI_HW_SW_EVENTS_CTRL_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_HW_SW_EVENTS_CTRL_ADDR(x,bid),m,v,HWIO_SPMI_HW_SW_EVENTS_CTRL_IN(x,bid))
#define HWIO_SPMI_HW_SW_EVENTS_CTRL_HW_SW_EVENTS_SEL_BMSK                                    0x7
#define HWIO_SPMI_HW_SW_EVENTS_CTRL_HW_SW_EVENTS_SEL_SHFT                                      0

#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,bid,j)                              ((base) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0X3008 + (0x4*(j)))
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_OFFS(j)                                   (0X3008 + (0x4*(j)))
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_RMSK                                      0x81818181
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_INI(base,bid,j)                \
                in_dword_masked(HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,bid,j), HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_RMSK)
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_INMI(base,bid,j,mask)        \
                in_dword_masked(HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,bid,j), mask)
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_OUTI(base,bid,j,val)        \
                out_dword(HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,bid,j),val)
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_OUTMI(base,bid,j,mask,val) \
                out_dword_masked_ns(HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_ADDR(base,bid,j),mask,val,HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_INI(base,bid,j))
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_D_BMSK                       0x80000000
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_D_SHFT                               31
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_D_BMSK                       0x1000000
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_D_SHFT                              24
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_C_BMSK                         0x800000
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_C_SHFT                               23
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_C_BMSK                         0x10000
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_C_SHFT                              16
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_B_BMSK                           0x8000
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_B_SHFT                               15
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_B_BMSK                           0x100
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_B_SHFT                               8
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_A_BMSK                             0x80
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_EN_A_SHFT                                7
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_A_BMSK                             0x1
#define HWIO_SPMI_HW_SW_EVENTS_BITWISE_REGj_HW_EVENTS_SEL_A_SHFT                               0

#define HWIO_SPMI_DEBUG_REG_ADDR(x,bid)                                                   ((x) + ((bid)*SPMI_CFG_TOP_BUS_OFFSET) + SPMI_CFG_REG_BASE_OFFS + 0x3028)
#define HWIO_SPMI_DEBUG_REG_OFFS                                                      (0x3028)
#define HWIO_SPMI_DEBUG_REG_RMSK                                                      0xffffffff
#define HWIO_SPMI_DEBUG_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_DEBUG_REG_ADDR(x,bid))
#define HWIO_SPMI_DEBUG_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_DEBUG_REG_ADDR(x,bid), m)
#define HWIO_SPMI_DEBUG_REG_TEST_BUS_BMSK                                             0xffffffff
#define HWIO_SPMI_DEBUG_REG_TEST_BUS_SHFT                                                      0



/*----------------------------------------------------------------------------
 * MODULE: SPMI_GENI_CFG
 *--------------------------------------------------------------------------*/
#define SPMI_GENI_CFG_REG_BASE_OFFS                                   0x02c000

#define HWIO_SPMI_GENI_CLK_CTRL_ADDR(x,bid)                                    ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x0)
#define HWIO_SPMI_GENI_CLK_CTRL_OFFS                                       (0x0)
#define HWIO_SPMI_GENI_CLK_CTRL_RMSK                                              0x1
#define HWIO_SPMI_GENI_CLK_CTRL_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_CLK_CTRL_ADDR(x,bid))
#define HWIO_SPMI_GENI_CLK_CTRL_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_CLK_CTRL_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_CLK_CTRL_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_CLK_CTRL_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_CLK_CTRL_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_CLK_CTRL_ADDR(x,bid),m,v,HWIO_SPMI_GENI_CLK_CTRL_IN(x,bid))
#define HWIO_SPMI_GENI_CLK_CTRL_SER_CLK_SEL_BMSK                                  0x1
#define HWIO_SPMI_GENI_CLK_CTRL_SER_CLK_SEL_SHFT                                    0

#define HWIO_SPMI_GENI_HW_VERSION_ADDR(x,bid)                                  ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x4)
#define HWIO_SPMI_GENI_HW_VERSION_OFFS                                         (0x4)
#define HWIO_SPMI_GENI_HW_VERSION_RMSK                                         0xffffffff
#define HWIO_SPMI_GENI_HW_VERSION_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_HW_VERSION_ADDR(x,bid))
#define HWIO_SPMI_GENI_HW_VERSION_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_HW_VERSION_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_HW_VERSION_MAJOR_BMSK                               0xf0000000
#define HWIO_SPMI_GENI_HW_VERSION_MAJOR_SHFT                                       28
#define HWIO_SPMI_GENI_HW_VERSION_MINOR_BMSK                                0xfff0000
#define HWIO_SPMI_GENI_HW_VERSION_MINOR_SHFT                                       16
#define HWIO_SPMI_GENI_HW_VERSION_STEP_BMSK                                    0xffff
#define HWIO_SPMI_GENI_HW_VERSION_STEP_SHFT                                         0

#define HWIO_SPMI_GENI_FW_REVISION_ADDR(x,bid)                                 ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x8)
#define HWIO_SPMI_GENI_FW_REVISION_OFFS                                    (0x8)
#define HWIO_SPMI_GENI_FW_REVISION_RMSK                                        0xffff
#define HWIO_SPMI_GENI_FW_REVISION_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_FW_REVISION_ADDR(x,bid))
#define HWIO_SPMI_GENI_FW_REVISION_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_FW_REVISION_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_FW_REVISION_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_FW_REVISION_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_FW_REVISION_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_FW_REVISION_ADDR(x,bid),m,v,HWIO_SPMI_GENI_FW_REVISION_IN(x,bid))
#define HWIO_SPMI_GENI_FW_REVISION_PROTOCOL_BMSK                               0xffc0
#define HWIO_SPMI_GENI_FW_REVISION_PROTOCOL_SHFT                                    6
#define HWIO_SPMI_GENI_FW_REVISION_VERSION_BMSK                                  0x3f
#define HWIO_SPMI_GENI_FW_REVISION_VERSION_SHFT                                     0

#define HWIO_SPMI_GENI_S_FW_REVISION_ADDR(x,bid)                               ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0xc)
#define HWIO_SPMI_GENI_S_FW_REVISION_OFFS                                  (0xc)
#define HWIO_SPMI_GENI_S_FW_REVISION_RMSK                                      0xffff
#define HWIO_SPMI_GENI_S_FW_REVISION_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_S_FW_REVISION_ADDR(x,bid))
#define HWIO_SPMI_GENI_S_FW_REVISION_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_S_FW_REVISION_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_S_FW_REVISION_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_S_FW_REVISION_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_S_FW_REVISION_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_S_FW_REVISION_ADDR(x,bid),m,v,HWIO_SPMI_GENI_S_FW_REVISION_IN(x,bid))
#define HWIO_SPMI_GENI_S_FW_REVISION_PROTOCOL_BMSK                             0xffc0
#define HWIO_SPMI_GENI_S_FW_REVISION_PROTOCOL_SHFT                                  6
#define HWIO_SPMI_GENI_S_FW_REVISION_VERSION_BMSK                                0x3f
#define HWIO_SPMI_GENI_S_FW_REVISION_VERSION_SHFT                                   0

#define HWIO_SPMI_GENI_FORCE_DEFAULT_REG_ADDR(x,bid)                           ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x10)
#define HWIO_SPMI_GENI_FORCE_DEFAULT_REG_OFFS                              (0x10)
#define HWIO_SPMI_GENI_FORCE_DEFAULT_REG_RMSK                                     0x1
#define HWIO_SPMI_GENI_FORCE_DEFAULT_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_FORCE_DEFAULT_REG_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_FORCE_DEFAULT_REG_FORCE_DEFAULT_BMSK                       0x1
#define HWIO_SPMI_GENI_FORCE_DEFAULT_REG_FORCE_DEFAULT_SHFT                         0

#define HWIO_SPMI_GENI_OUTPUT_CTRL_ADDR(x,bid)                                 ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x14)
#define HWIO_SPMI_GENI_OUTPUT_CTRL_OFFS                                    (0x14)
#define HWIO_SPMI_GENI_OUTPUT_CTRL_RMSK                                           0x7
#define HWIO_SPMI_GENI_OUTPUT_CTRL_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_OUTPUT_CTRL_ADDR(x,bid))
#define HWIO_SPMI_GENI_OUTPUT_CTRL_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_OUTPUT_CTRL_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_OUTPUT_CTRL_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_OUTPUT_CTRL_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_OUTPUT_CTRL_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_OUTPUT_CTRL_ADDR(x,bid),m,v,HWIO_SPMI_GENI_OUTPUT_CTRL_IN(x,bid))
#define HWIO_SPMI_GENI_OUTPUT_CTRL_SOE2_EN_BMSK                                   0x4
#define HWIO_SPMI_GENI_OUTPUT_CTRL_SOE2_EN_SHFT                                     2
#define HWIO_SPMI_GENI_OUTPUT_CTRL_SOE1_EN_BMSK                                   0x2
#define HWIO_SPMI_GENI_OUTPUT_CTRL_SOE1_EN_SHFT                                     1
#define HWIO_SPMI_GENI_OUTPUT_CTRL_SOE0_EN_BMSK                                   0x1
#define HWIO_SPMI_GENI_OUTPUT_CTRL_SOE0_EN_SHFT                                     0

#define HWIO_SPMI_GENI_CGC_CTRL_ADDR(x,bid)                                    ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x18)
#define HWIO_SPMI_GENI_CGC_CTRL_OFFS                                       (0x18)
#define HWIO_SPMI_GENI_CGC_CTRL_RMSK                                            0x37f
#define HWIO_SPMI_GENI_CGC_CTRL_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_CGC_CTRL_ADDR(x,bid))
#define HWIO_SPMI_GENI_CGC_CTRL_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_CGC_CTRL_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_CGC_CTRL_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_CGC_CTRL_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_CGC_CTRL_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_CGC_CTRL_ADDR(x,bid),m,v,HWIO_SPMI_GENI_CGC_CTRL_IN(x,bid))
#define HWIO_SPMI_GENI_CGC_CTRL_PROG_RAM_SCLK_OFF_BMSK                          0x200
#define HWIO_SPMI_GENI_CGC_CTRL_PROG_RAM_SCLK_OFF_SHFT                              9
#define HWIO_SPMI_GENI_CGC_CTRL_PROG_RAM_HCLK_OFF_BMSK                          0x100
#define HWIO_SPMI_GENI_CGC_CTRL_PROG_RAM_HCLK_OFF_SHFT                              8
#define HWIO_SPMI_GENI_CGC_CTRL_EXT_CLK_CGC_ON_BMSK                              0x40
#define HWIO_SPMI_GENI_CGC_CTRL_EXT_CLK_CGC_ON_SHFT                                 6
#define HWIO_SPMI_GENI_CGC_CTRL_RX_CLK_CGC_ON_BMSK                               0x20
#define HWIO_SPMI_GENI_CGC_CTRL_RX_CLK_CGC_ON_SHFT                                  5
#define HWIO_SPMI_GENI_CGC_CTRL_TX_CLK_CGC_ON_BMSK                               0x10
#define HWIO_SPMI_GENI_CGC_CTRL_TX_CLK_CGC_ON_SHFT                                  4
#define HWIO_SPMI_GENI_CGC_CTRL_SCLK_CGC_ON_BMSK                                  0x8
#define HWIO_SPMI_GENI_CGC_CTRL_SCLK_CGC_ON_SHFT                                    3
#define HWIO_SPMI_GENI_CGC_CTRL_DATA_AHB_CLK_CGC_ON_BMSK                          0x4
#define HWIO_SPMI_GENI_CGC_CTRL_DATA_AHB_CLK_CGC_ON_SHFT                            2
#define HWIO_SPMI_GENI_CGC_CTRL_CFG_AHB_WR_CLK_CGC_ON_BMSK                        0x2
#define HWIO_SPMI_GENI_CGC_CTRL_CFG_AHB_WR_CLK_CGC_ON_SHFT                          1
#define HWIO_SPMI_GENI_CGC_CTRL_CFG_AHB_CLK_CGC_ON_BMSK                           0x1
#define HWIO_SPMI_GENI_CGC_CTRL_CFG_AHB_CLK_CGC_ON_SHFT                             0

#define HWIO_SPMI_GENI_CHAR_CFG_ADDR(x,bid)                                    ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x1c)
#define HWIO_SPMI_GENI_CHAR_CFG_OFFS                                       (0x1c)
#define HWIO_SPMI_GENI_CHAR_CFG_RMSK                                          0xfff11
#define HWIO_SPMI_GENI_CHAR_CFG_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_CHAR_CFG_ADDR(x,bid))
#define HWIO_SPMI_GENI_CHAR_CFG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_CHAR_CFG_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_CHAR_CFG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_CHAR_CFG_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_CHAR_CFG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_CHAR_CFG_ADDR(x,bid),m,v,HWIO_SPMI_GENI_CHAR_CFG_IN(x,bid))
#define HWIO_SPMI_GENI_CHAR_CFG_CHAR_MODE_BMSK                                0xff000
#define HWIO_SPMI_GENI_CHAR_CFG_CHAR_MODE_SHFT                                     12
#define HWIO_SPMI_GENI_CHAR_CFG_CHAR_STATUS_BMSK                                0xf00
#define HWIO_SPMI_GENI_CHAR_CFG_CHAR_STATUS_SHFT                                    8
#define HWIO_SPMI_GENI_CHAR_CFG_DIRECTION_BMSK                                   0x10
#define HWIO_SPMI_GENI_CHAR_CFG_DIRECTION_SHFT                                      4
#define HWIO_SPMI_GENI_CHAR_CFG_ENABLE_BMSK                                       0x1
#define HWIO_SPMI_GENI_CHAR_CFG_ENABLE_SHFT                                         0

#define HWIO_SPMI_GENI_CHAR_DATA_n_ADDR(base,n)                            ((base) + SPMI_GENI_CFG_REG_BASE_OFFS + 0X20 + (0x4*(n)))
#define HWIO_SPMI_GENI_CHAR_DATA_n_OFFS(n)                                 (0X20 + (0x4*(n)))
#define HWIO_SPMI_GENI_CHAR_DATA_n_RMSK                                        0xffff
#define HWIO_SPMI_GENI_CHAR_DATA_n_INI(base,n)                \
                in_dword_masked(HWIO_SPMI_GENI_CHAR_DATA_n_ADDR(base,n), HWIO_SPMI_GENI_CHAR_DATA_n_RMSK)
#define HWIO_SPMI_GENI_CHAR_DATA_n_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI_GENI_CHAR_DATA_n_ADDR(base,n), mask)
#define HWIO_SPMI_GENI_CHAR_DATA_n_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI_GENI_CHAR_DATA_n_ADDR(base,n),val)
#define HWIO_SPMI_GENI_CHAR_DATA_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI_GENI_CHAR_DATA_n_ADDR(base,n),mask,val,HWIO_SPMI_GENI_CHAR_DATA_n_INI(base,n))
#define HWIO_SPMI_GENI_CHAR_DATA_n_DIN_ACTUAL_BMSK                             0xff00
#define HWIO_SPMI_GENI_CHAR_DATA_n_DIN_ACTUAL_SHFT                                  8
#define HWIO_SPMI_GENI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_BMSK                        0xff
#define HWIO_SPMI_GENI_CHAR_DATA_n_DOUT_DATA_DIN_EXP_SHFT                           0

#define HWIO_SPMI_GENI_CTRL_ADDR(x,bid)                                        ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x28)
#define HWIO_SPMI_GENI_CTRL_OFFS                                           (0x28)
#define HWIO_SPMI_GENI_CTRL_RMSK                                                  0x3
#define HWIO_SPMI_GENI_CTRL_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_CTRL_ADDR(x,bid))
#define HWIO_SPMI_GENI_CTRL_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_CTRL_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_CTRL_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_CTRL_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_CTRL_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_CTRL_ADDR(x,bid),m,v,HWIO_SPMI_GENI_CTRL_IN(x,bid))
#define HWIO_SPMI_GENI_CTRL_S_GENI_DISABLE_BMSK                                   0x2
#define HWIO_SPMI_GENI_CTRL_S_GENI_DISABLE_SHFT                                     1
#define HWIO_SPMI_GENI_CTRL_M_GENI_DISABLE_BMSK                                   0x1
#define HWIO_SPMI_GENI_CTRL_M_GENI_DISABLE_SHFT                                     0

#define HWIO_SPMI_GENI_STATUS_ADDR(x,bid)                                      ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x2c)
#define HWIO_SPMI_GENI_STATUS_OFFS                                         (0x2c)
#define HWIO_SPMI_GENI_STATUS_RMSK                                           0x1fffff
#define HWIO_SPMI_GENI_STATUS_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_STATUS_ADDR(x,bid))
#define HWIO_SPMI_GENI_STATUS_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_STATUS_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_STATUS_S_GENI_CMD_FSM_STATE_BMSK                      0x1f0000
#define HWIO_SPMI_GENI_STATUS_S_GENI_CMD_FSM_STATE_SHFT                            16
#define HWIO_SPMI_GENI_STATUS_NOT_USED_BITS_3_BMSK                             0xe000
#define HWIO_SPMI_GENI_STATUS_NOT_USED_BITS_3_SHFT                                 13
#define HWIO_SPMI_GENI_STATUS_S_GENI_CMD_ACTIVE_BMSK                           0x1000
#define HWIO_SPMI_GENI_STATUS_S_GENI_CMD_ACTIVE_SHFT                               12
#define HWIO_SPMI_GENI_STATUS_NOT_USED_BITS_2_BMSK                              0xe00
#define HWIO_SPMI_GENI_STATUS_NOT_USED_BITS_2_SHFT                                  9
#define HWIO_SPMI_GENI_STATUS_M_GENI_CMD_FSM_STATE_BMSK                         0x1f0
#define HWIO_SPMI_GENI_STATUS_M_GENI_CMD_FSM_STATE_SHFT                             4
#define HWIO_SPMI_GENI_STATUS_NOT_USED_BITS_1_BMSK                                0xe
#define HWIO_SPMI_GENI_STATUS_NOT_USED_BITS_1_SHFT                                  1
#define HWIO_SPMI_GENI_STATUS_M_GENI_CMD_ACTIVE_BMSK                              0x1
#define HWIO_SPMI_GENI_STATUS_M_GENI_CMD_ACTIVE_SHFT                                0

#define HWIO_SPMI_GENI_TEST_BUS_CTRL_ADDR(x,bid)                               ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x30)
#define HWIO_SPMI_GENI_TEST_BUS_CTRL_OFFS                                  (0x30)
#define HWIO_SPMI_GENI_TEST_BUS_CTRL_RMSK                                        0x1f
#define HWIO_SPMI_GENI_TEST_BUS_CTRL_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_TEST_BUS_CTRL_ADDR(x,bid))
#define HWIO_SPMI_GENI_TEST_BUS_CTRL_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_TEST_BUS_CTRL_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_TEST_BUS_CTRL_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_TEST_BUS_CTRL_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_TEST_BUS_CTRL_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_TEST_BUS_CTRL_ADDR(x,bid),m,v,HWIO_SPMI_GENI_TEST_BUS_CTRL_IN(x,bid))
#define HWIO_SPMI_GENI_TEST_BUS_CTRL_TEST_BUS_SEL_BMSK                           0x1f
#define HWIO_SPMI_GENI_TEST_BUS_CTRL_TEST_BUS_SEL_SHFT                              0

#define HWIO_SPMI_GENI_SER_CLK_CFG_ADDR(x,bid)                                 ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x34)
#define HWIO_SPMI_GENI_SER_CLK_CFG_OFFS                                    (0x34)
#define HWIO_SPMI_GENI_SER_CLK_CFG_RMSK                                     0x3ffffff
#define HWIO_SPMI_GENI_SER_CLK_CFG_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_SER_CLK_CFG_ADDR(x,bid))
#define HWIO_SPMI_GENI_SER_CLK_CFG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_SER_CLK_CFG_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_SER_CLK_CFG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_SER_CLK_CFG_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_SER_CLK_CFG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_SER_CLK_CFG_ADDR(x,bid),m,v,HWIO_SPMI_GENI_SER_CLK_CFG_IN(x,bid))
#define HWIO_SPMI_GENI_SER_CLK_CFG_TX_CLK_DIV_VALUE_BMSK                    0x3ffc000
#define HWIO_SPMI_GENI_SER_CLK_CFG_TX_CLK_DIV_VALUE_SHFT                           14
#define HWIO_SPMI_GENI_SER_CLK_CFG_RX_CLK_DIV_VALUE_BMSK                       0x3ffc
#define HWIO_SPMI_GENI_SER_CLK_CFG_RX_CLK_DIV_VALUE_SHFT                            2
#define HWIO_SPMI_GENI_SER_CLK_CFG_TX_SER_CLK_EN_BMSK                             0x2
#define HWIO_SPMI_GENI_SER_CLK_CFG_TX_SER_CLK_EN_SHFT                               1
#define HWIO_SPMI_GENI_SER_CLK_CFG_RX_SER_CLK_EN_BMSK                             0x1
#define HWIO_SPMI_GENI_SER_CLK_CFG_RX_SER_CLK_EN_SHFT                               0

#define HWIO_SPMI_GENI_TX_WATERMARK_REG_ADDR(x,bid)                            ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x38)
#define HWIO_SPMI_GENI_TX_WATERMARK_REG_OFFS                               (0x38)
#define HWIO_SPMI_GENI_TX_WATERMARK_REG_RMSK                                      0xf
#define HWIO_SPMI_GENI_TX_WATERMARK_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_TX_WATERMARK_REG_ADDR(x,bid))
#define HWIO_SPMI_GENI_TX_WATERMARK_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_TX_WATERMARK_REG_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_TX_WATERMARK_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_TX_WATERMARK_REG_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_TX_WATERMARK_REG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_TX_WATERMARK_REG_ADDR(x,bid),m,v,HWIO_SPMI_GENI_TX_WATERMARK_REG_IN(x,bid))
#define HWIO_SPMI_GENI_TX_WATERMARK_REG_TX_WATERMARK_BMSK                         0xf
#define HWIO_SPMI_GENI_TX_WATERMARK_REG_TX_WATERMARK_SHFT                           0

#define HWIO_SPMI_GENI_RX_WATERMARK_REG_ADDR(x,bid)                               ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x3c)
#define HWIO_SPMI_GENI_RX_WATERMARK_REG_OFFS                                      (0x3c)
#define HWIO_SPMI_GENI_RX_WATERMARK_REG_RMSK                                      0xf
#define HWIO_SPMI_GENI_RX_WATERMARK_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_RX_WATERMARK_REG_ADDR(x,bid))
#define HWIO_SPMI_GENI_RX_WATERMARK_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_RX_WATERMARK_REG_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_RX_WATERMARK_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_RX_WATERMARK_REG_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_RX_WATERMARK_REG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_RX_WATERMARK_REG_ADDR(x,bid),m,v,HWIO_SPMI_GENI_RX_WATERMARK_REG_IN(x,bid))
#define HWIO_SPMI_GENI_RX_WATERMARK_REG_RX_WATERMARK_BMSK                         0xf
#define HWIO_SPMI_GENI_RX_WATERMARK_REG_RX_WATERMARK_SHFT                           0

#define HWIO_SPMI_GENI_STOP_REG_ADDR(x,bid)                                    ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x40)
#define HWIO_SPMI_GENI_STOP_REG_OFFS                                       (0x40)
#define HWIO_SPMI_GENI_STOP_REG_RMSK                                              0x3
#define HWIO_SPMI_GENI_STOP_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_STOP_REG_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_STOP_REG_S_GENI_STOP_BMSK                                  0x2
#define HWIO_SPMI_GENI_STOP_REG_S_GENI_STOP_SHFT                                    1
#define HWIO_SPMI_GENI_STOP_REG_M_GENI_STOP_BMSK                                  0x1
#define HWIO_SPMI_GENI_STOP_REG_M_GENI_STOP_SHFT                                    0

#define HWIO_SPMI_GENI_SW_COMP_REG_ADDR(x,bid)                                 ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x44)
#define HWIO_SPMI_GENI_SW_COMP_REG_OFFS                                    (0x44)
#define HWIO_SPMI_GENI_SW_COMP_REG_RMSK                                           0x7
#define HWIO_SPMI_GENI_SW_COMP_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_SW_COMP_REG_ADDR(x,bid))
#define HWIO_SPMI_GENI_SW_COMP_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_SW_COMP_REG_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_SW_COMP_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_SW_COMP_REG_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_SW_COMP_REG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_SW_COMP_REG_ADDR(x,bid),m,v,HWIO_SPMI_GENI_SW_COMP_REG_IN(x,bid))
#define HWIO_SPMI_GENI_SW_COMP_REG_SW_COMP_BMSK                                   0x7
#define HWIO_SPMI_GENI_SW_COMP_REG_SW_COMP_SHFT                                     0

#define HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x,bid)                           ((x) + (SPMI_CFG_TOP_BUS_OFFSET*bid) + SPMI_GENI_CFG_REG_BASE_OFFS + 0x48)
#define HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_OFFS                              (0x48)
#define HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_RMSK                                     0x1
#define HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_IN(x,bid)            \
                in_dword(HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x,bid))
#define HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_INM(x,bid, m)            \
                in_dword_masked(HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x,bid), m)
#define HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_OUT(x,bid, v)            \
                out_dword(HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x,bid),v)
#define HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_OUTM(x,bid,m,v) \
                out_dword_masked_ns(HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR(x,bid),m,v,HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_IN(x,bid))
#define HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_PROG_ROM_EN_BMSK                         0x1
#define HWIO_SPMI_GENI_PROG_ROM_CTRL_REG_PROG_ROM_EN_SHFT                           0


/*----------------------------------------------------------------------------
 * MODULE: SPMI_PIC_OWNER
 *--------------------------------------------------------------------------*/

#define SPMI_PIC_OWNER_REG_BASE_OFFS                                  0xc0000
#define SPMI_PIC_OWNER_BUS_OFFSET                                     0x10000

#define HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_ADDR(base,bid,m,n)               ((base) + ((bid)*SPMI_PIC_OWNER_BUS_OFFSET) + SPMI_PIC_OWNER_REG_BASE_OFFS + 0X0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_OFFS(m,n)                    (0X0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_RMSK                         0xffffffff
#define HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_INI2(base,bid,m,n)                \
                in_dword_masked(HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_ADDR(base,bid,m,n), HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_RMSK)
#define HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_INMI2(base,bid,m,n,mask)        \
                in_dword_masked(HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_ADDR(base,bid,m,n), mask)
#define HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_INT_ACC_STATUS_BMSK          0xffffffff
#define HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_INT_ACC_STATUS_SHFT                   0


#endif /* __SPMICOREHWIO_H__ */
