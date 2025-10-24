#ifndef __FLASH_QPIC_XPU_H__
#define __FLASH_QPIC_XPU_H__
/*
===========================================================================
*/
/**
    @file flash_qpic_xpu.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SDX75 (Pinnacles) [pinnacles_v1.0_p3q1r64]
 
    This file contains HWIO register definitions for the following modules:
        QPIC_XPU4


    Generation parameters: 
    { 'filename': 'flash_qpic_xpu.h',
      'header': '#include "msmhwiobase.h"',
      'modules': ['QPIC_XPU4']}
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
 * MODULE: QPIC_XPU4
 *--------------------------------------------------------------------------*/

#define QPIC_XPU4_REG_BASE                                     (QPIC_QPIC_BASE      + 0x00001000)
#define QPIC_XPU4_REG_BASE_SIZE                                0x3000
#define QPIC_XPU4_REG_BASE_USED                                0x15b0

#define HWIO_QPIC_XPU4_IDR0_ADDR                               (QPIC_XPU4_REG_BASE      + 0x0)
#define HWIO_QPIC_XPU4_IDR0_RMSK                                0x3ff0073
#define HWIO_QPIC_XPU4_IDR0_IN                    \
                in_dword(HWIO_QPIC_XPU4_IDR0_ADDR)
#define HWIO_QPIC_XPU4_IDR0_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_IDR0_ADDR, m)
#define HWIO_QPIC_XPU4_IDR0_NRG_BMSK                            0x3ff0000
#define HWIO_QPIC_XPU4_IDR0_NRG_SHFT                                   16
#define HWIO_QPIC_XPU4_IDR0_BLED_BMSK                                0x40
#define HWIO_QPIC_XPU4_IDR0_BLED_SHFT                                   6
#define HWIO_QPIC_XPU4_IDR0_CLIENT_HALTREQACK_EN_BMSK                0x20
#define HWIO_QPIC_XPU4_IDR0_CLIENT_HALTREQACK_EN_SHFT                   5
#define HWIO_QPIC_XPU4_IDR0_CLIENT_PIPELINE_EN_BMSK                  0x10
#define HWIO_QPIC_XPU4_IDR0_CLIENT_PIPELINE_EN_SHFT                     4
#define HWIO_QPIC_XPU4_IDR0_XPU_TYPE_BMSK                             0x3
#define HWIO_QPIC_XPU4_IDR0_XPU_TYPE_SHFT                               0

#define HWIO_QPIC_XPU4_IDR1_ADDR                               (QPIC_XPU4_REG_BASE      + 0x4)
#define HWIO_QPIC_XPU4_IDR1_RMSK                               0x3f3f3f3f
#define HWIO_QPIC_XPU4_IDR1_IN                    \
                in_dword(HWIO_QPIC_XPU4_IDR1_ADDR)
#define HWIO_QPIC_XPU4_IDR1_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_IDR1_ADDR, m)
#define HWIO_QPIC_XPU4_IDR1_CLIENT_ADDR_WIDTH_BMSK             0x3f000000
#define HWIO_QPIC_XPU4_IDR1_CLIENT_ADDR_WIDTH_SHFT                     24
#define HWIO_QPIC_XPU4_IDR1_CONFIG_ADDR_WIDTH_BMSK               0x3f0000
#define HWIO_QPIC_XPU4_IDR1_CONFIG_ADDR_WIDTH_SHFT                     16
#define HWIO_QPIC_XPU4_IDR1_ADDR_MSB_BMSK                          0x3f00
#define HWIO_QPIC_XPU4_IDR1_ADDR_MSB_SHFT                               8
#define HWIO_QPIC_XPU4_IDR1_ADDR_LSB_BMSK                            0x3f
#define HWIO_QPIC_XPU4_IDR1_ADDR_LSB_SHFT                               0

#define HWIO_QPIC_XPU4_IDR2_ADDR                               (QPIC_XPU4_REG_BASE      + 0x8)
#define HWIO_QPIC_XPU4_IDR2_RMSK                                    0x11f
#define HWIO_QPIC_XPU4_IDR2_IN                    \
                in_dword(HWIO_QPIC_XPU4_IDR2_ADDR)
#define HWIO_QPIC_XPU4_IDR2_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_IDR2_ADDR, m)
#define HWIO_QPIC_XPU4_IDR2_USELEGACYINTF_BMSK                      0x100
#define HWIO_QPIC_XPU4_IDR2_USELEGACYINTF_SHFT                          8
#define HWIO_QPIC_XPU4_IDR2_NQAD_BMSK                                0x1f
#define HWIO_QPIC_XPU4_IDR2_NQAD_SHFT                                   0

#define HWIO_QPIC_XPU4_REV_ADDR                                (QPIC_XPU4_REG_BASE      + 0xc)
#define HWIO_QPIC_XPU4_REV_RMSK                                0xffffffff
#define HWIO_QPIC_XPU4_REV_IN                    \
                in_dword(HWIO_QPIC_XPU4_REV_ADDR)
#define HWIO_QPIC_XPU4_REV_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_REV_ADDR, m)
#define HWIO_QPIC_XPU4_REV_MAJOR_BMSK                          0xf0000000
#define HWIO_QPIC_XPU4_REV_MAJOR_SHFT                                  28
#define HWIO_QPIC_XPU4_REV_MINOR_BMSK                           0xfff0000
#define HWIO_QPIC_XPU4_REV_MINOR_SHFT                                  16
#define HWIO_QPIC_XPU4_REV_STEP_BMSK                               0xffff
#define HWIO_QPIC_XPU4_REV_STEP_SHFT                                    0

#define HWIO_QPIC_XPU4_GCR_ADDR                                (QPIC_XPU4_REG_BASE      + 0x100)
#define HWIO_QPIC_XPU4_GCR_RMSK                                       0x3
#define HWIO_QPIC_XPU4_GCR_IN                    \
                in_dword(HWIO_QPIC_XPU4_GCR_ADDR)
#define HWIO_QPIC_XPU4_GCR_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_GCR_ADDR, m)
#define HWIO_QPIC_XPU4_GCR_OUT(v)            \
                out_dword(HWIO_QPIC_XPU4_GCR_ADDR,v)
#define HWIO_QPIC_XPU4_GCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QPIC_XPU4_GCR_ADDR,m,v,HWIO_QPIC_XPU4_GCR_IN)
#define HWIO_QPIC_XPU4_GCR_DYNAMIC_CLK_EN_BMSK                        0x2
#define HWIO_QPIC_XPU4_GCR_DYNAMIC_CLK_EN_SHFT                          1
#define HWIO_QPIC_XPU4_GCR_APNSPE_BMSK                                0x1
#define HWIO_QPIC_XPU4_GCR_APNSPE_SHFT                                  0

#define HWIO_QPIC_XPU4_RSR_ADDR                                (QPIC_XPU4_REG_BASE      + 0x104)
#define HWIO_QPIC_XPU4_RSR_RMSK                                0xffffffff
#define HWIO_QPIC_XPU4_RSR_IN                    \
                in_dword(HWIO_QPIC_XPU4_RSR_ADDR)
#define HWIO_QPIC_XPU4_RSR_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_RSR_ADDR, m)
#define HWIO_QPIC_XPU4_RSR_NXTFRG_BMSK                         0xffff0000
#define HWIO_QPIC_XPU4_RSR_NXTFRG_SHFT                                 16
#define HWIO_QPIC_XPU4_RSR_NUMFRG_BMSK                             0xffff
#define HWIO_QPIC_XPU4_RSR_NUMFRG_SHFT                                  0

#define HWIO_QPIC_XPU4_CFGERE_ADDR                             (QPIC_XPU4_REG_BASE      + 0x208)
#define HWIO_QPIC_XPU4_CFGERE_RMSK                             0xc000007f
#define HWIO_QPIC_XPU4_CFGERE_IN                    \
                in_dword(HWIO_QPIC_XPU4_CFGERE_ADDR)
#define HWIO_QPIC_XPU4_CFGERE_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_CFGERE_ADDR, m)
#define HWIO_QPIC_XPU4_CFGERE_OUT(v)            \
                out_dword(HWIO_QPIC_XPU4_CFGERE_ADDR,v)
#define HWIO_QPIC_XPU4_CFGERE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QPIC_XPU4_CFGERE_ADDR,m,v,HWIO_QPIC_XPU4_CFGERE_IN)
#define HWIO_QPIC_XPU4_CFGERE_CFGERE_S_BMSK                    0x80000000
#define HWIO_QPIC_XPU4_CFGERE_CFGERE_S_SHFT                            31
#define HWIO_QPIC_XPU4_CFGERE_CFGERE_NS_BMSK                   0x40000000
#define HWIO_QPIC_XPU4_CFGERE_CFGERE_NS_SHFT                           30
#define HWIO_QPIC_XPU4_CFGERE_CFGERE_QAD_BMSK                        0x7f
#define HWIO_QPIC_XPU4_CFGERE_CFGERE_QAD_SHFT                           0

#define HWIO_QPIC_XPU4_CLERE_ADDR                              (QPIC_XPU4_REG_BASE      + 0x20c)
#define HWIO_QPIC_XPU4_CLERE_RMSK                              0xc000007f
#define HWIO_QPIC_XPU4_CLERE_IN                    \
                in_dword(HWIO_QPIC_XPU4_CLERE_ADDR)
#define HWIO_QPIC_XPU4_CLERE_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_CLERE_ADDR, m)
#define HWIO_QPIC_XPU4_CLERE_OUT(v)            \
                out_dword(HWIO_QPIC_XPU4_CLERE_ADDR,v)
#define HWIO_QPIC_XPU4_CLERE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QPIC_XPU4_CLERE_ADDR,m,v,HWIO_QPIC_XPU4_CLERE_IN)
#define HWIO_QPIC_XPU4_CLERE_CLERE_S_BMSK                      0x80000000
#define HWIO_QPIC_XPU4_CLERE_CLERE_S_SHFT                              31
#define HWIO_QPIC_XPU4_CLERE_CLERE_NS_BMSK                     0x40000000
#define HWIO_QPIC_XPU4_CLERE_CLERE_NS_SHFT                             30
#define HWIO_QPIC_XPU4_CLERE_CLERE_QAD_BMSK                          0x7f
#define HWIO_QPIC_XPU4_CLERE_CLERE_QAD_SHFT                             0

#define HWIO_QPIC_XPU4_DBGAR_ADDR                              (QPIC_XPU4_REG_BASE      + 0x304)
#define HWIO_QPIC_XPU4_DBGAR_RMSK                              0xc000007f
#define HWIO_QPIC_XPU4_DBGAR_IN                    \
                in_dword(HWIO_QPIC_XPU4_DBGAR_ADDR)
#define HWIO_QPIC_XPU4_DBGAR_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_DBGAR_ADDR, m)
#define HWIO_QPIC_XPU4_DBGAR_OUT(v)            \
                out_dword(HWIO_QPIC_XPU4_DBGAR_ADDR,v)
#define HWIO_QPIC_XPU4_DBGAR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QPIC_XPU4_DBGAR_ADDR,m,v,HWIO_QPIC_XPU4_DBGAR_IN)
#define HWIO_QPIC_XPU4_DBGAR_DBGA_S_BMSK                       0x80000000
#define HWIO_QPIC_XPU4_DBGAR_DBGA_S_SHFT                               31
#define HWIO_QPIC_XPU4_DBGAR_DBGA_NS_BMSK                      0x40000000
#define HWIO_QPIC_XPU4_DBGAR_DBGA_NS_SHFT                              30
#define HWIO_QPIC_XPU4_DBGAR_DBGA_QAD_BMSK                           0x7f
#define HWIO_QPIC_XPU4_DBGAR_DBGA_QAD_SHFT                              0

#define HWIO_QPIC_XPU4_ESR_ADDR                                (QPIC_XPU4_REG_BASE      + 0x500)
#define HWIO_QPIC_XPU4_ESR_RMSK                                       0xf
#define HWIO_QPIC_XPU4_ESR_IN                    \
                in_dword(HWIO_QPIC_XPU4_ESR_ADDR)
#define HWIO_QPIC_XPU4_ESR_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_ESR_ADDR, m)
#define HWIO_QPIC_XPU4_ESR_OUT(v)            \
                out_dword(HWIO_QPIC_XPU4_ESR_ADDR,v)
#define HWIO_QPIC_XPU4_ESR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QPIC_XPU4_ESR_ADDR,m,v,HWIO_QPIC_XPU4_ESR_IN)
#define HWIO_QPIC_XPU4_ESR_CLMULTI_BMSK                               0x8
#define HWIO_QPIC_XPU4_ESR_CLMULTI_SHFT                                 3
#define HWIO_QPIC_XPU4_ESR_CFGMULTI_BMSK                              0x4
#define HWIO_QPIC_XPU4_ESR_CFGMULTI_SHFT                                2
#define HWIO_QPIC_XPU4_ESR_CLERR_BMSK                                 0x2
#define HWIO_QPIC_XPU4_ESR_CLERR_SHFT                                   1
#define HWIO_QPIC_XPU4_ESR_CFGERR_BMSK                                0x1
#define HWIO_QPIC_XPU4_ESR_CFGERR_SHFT                                  0

#define HWIO_QPIC_XPU4_SYNAR0_ADDR                             (QPIC_XPU4_REG_BASE      + 0x504)
#define HWIO_QPIC_XPU4_SYNAR0_RMSK                             0xffffffff
#define HWIO_QPIC_XPU4_SYNAR0_IN                    \
                in_dword(HWIO_QPIC_XPU4_SYNAR0_ADDR)
#define HWIO_QPIC_XPU4_SYNAR0_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_SYNAR0_ADDR, m)
#define HWIO_QPIC_XPU4_SYNAR0_SYNADDR_BMSK                     0xffffffff
#define HWIO_QPIC_XPU4_SYNAR0_SYNADDR_SHFT                              0

#define HWIO_QPIC_XPU4_SYNAR1_ADDR                             (QPIC_XPU4_REG_BASE      + 0x508)
#define HWIO_QPIC_XPU4_SYNAR1_RMSK                             0xffffffff
#define HWIO_QPIC_XPU4_SYNAR1_IN                    \
                in_dword(HWIO_QPIC_XPU4_SYNAR1_ADDR)
#define HWIO_QPIC_XPU4_SYNAR1_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_SYNAR1_ADDR, m)
#define HWIO_QPIC_XPU4_SYNAR1_SYNADDR_BMSK                     0xffffffff
#define HWIO_QPIC_XPU4_SYNAR1_SYNADDR_SHFT                              0

#define HWIO_QPIC_XPU4_SYNR0_ADDR                              (QPIC_XPU4_REG_BASE      + 0x50c)
#define HWIO_QPIC_XPU4_SYNR0_RMSK                              0xffff9f7f
#define HWIO_QPIC_XPU4_SYNR0_IN                    \
                in_dword(HWIO_QPIC_XPU4_SYNR0_ADDR)
#define HWIO_QPIC_XPU4_SYNR0_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_SYNR0_ADDR, m)
#define HWIO_QPIC_XPU4_SYNR0_PH_BMSK                           0x80000000
#define HWIO_QPIC_XPU4_SYNR0_PH_SHFT                                   31
#define HWIO_QPIC_XPU4_SYNR0_AC_CFG_BMSK                       0x40000000
#define HWIO_QPIC_XPU4_SYNR0_AC_CFG_SHFT                               30
#define HWIO_QPIC_XPU4_SYNR0_AC_CL_BMSK                        0x20000000
#define HWIO_QPIC_XPU4_SYNR0_AC_CL_SHFT                                29
#define HWIO_QPIC_XPU4_SYNR0_BURSTLEN_BMSK                     0x10000000
#define HWIO_QPIC_XPU4_SYNR0_BURSTLEN_SHFT                             28
#define HWIO_QPIC_XPU4_SYNR0_QADERR_BMSK                        0x8000000
#define HWIO_QPIC_XPU4_SYNR0_QADERR_SHFT                               27
#define HWIO_QPIC_XPU4_SYNR0_APUDECERR_BMSK                     0x4000000
#define HWIO_QPIC_XPU4_SYNR0_APUDECERR_SHFT                            26
#define HWIO_QPIC_XPU4_SYNR0_SSIZE_BMSK                         0x3800000
#define HWIO_QPIC_XPU4_SYNR0_SSIZE_SHFT                                23
#define HWIO_QPIC_XPU4_SYNR0_LEN_BMSK                            0x7f8000
#define HWIO_QPIC_XPU4_SYNR0_LEN_SHFT                                  15
#define HWIO_QPIC_XPU4_SYNR0_QAD_BMSK                              0x1f00
#define HWIO_QPIC_XPU4_SYNR0_QAD_SHFT                                   8
#define HWIO_QPIC_XPU4_SYNR0_REQ_OPC_BMSK                            0x78
#define HWIO_QPIC_XPU4_SYNR0_REQ_OPC_SHFT                               3
#define HWIO_QPIC_XPU4_SYNR0_PRIV_BMSK                                0x4
#define HWIO_QPIC_XPU4_SYNR0_PRIV_SHFT                                  2
#define HWIO_QPIC_XPU4_SYNR0_INST_BMSK                                0x2
#define HWIO_QPIC_XPU4_SYNR0_INST_SHFT                                  1
#define HWIO_QPIC_XPU4_SYNR0_XPROTNS_BMSK                             0x1
#define HWIO_QPIC_XPU4_SYNR0_XPROTNS_SHFT                               0

#define HWIO_QPIC_XPU4_SYNR1_ADDR                              (QPIC_XPU4_REG_BASE      + 0x510)
#define HWIO_QPIC_XPU4_SYNR1_RMSK                              0xff07ffff
#define HWIO_QPIC_XPU4_SYNR1_IN                    \
                in_dword(HWIO_QPIC_XPU4_SYNR1_ADDR)
#define HWIO_QPIC_XPU4_SYNR1_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_SYNR1_ADDR, m)
#define HWIO_QPIC_XPU4_SYNR1_TID_BMSK                          0xff000000
#define HWIO_QPIC_XPU4_SYNR1_TID_SHFT                                  24
#define HWIO_QPIC_XPU4_SYNR1_TRTYPE_BMSK                          0x70000
#define HWIO_QPIC_XPU4_SYNR1_TRTYPE_SHFT                               16
#define HWIO_QPIC_XPU4_SYNR1_BID_BMSK                              0xe000
#define HWIO_QPIC_XPU4_SYNR1_BID_SHFT                                  13
#define HWIO_QPIC_XPU4_SYNR1_PID_BMSK                              0x1f00
#define HWIO_QPIC_XPU4_SYNR1_PID_SHFT                                   8
#define HWIO_QPIC_XPU4_SYNR1_MID_BMSK                                0xff
#define HWIO_QPIC_XPU4_SYNR1_MID_SHFT                                   0

#define HWIO_QPIC_XPU4_SYNR2_ADDR                              (QPIC_XPU4_REG_BASE      + 0x514)
#define HWIO_QPIC_XPU4_SYNR2_RMSK                               0x3ffffff
#define HWIO_QPIC_XPU4_SYNR2_IN                    \
                in_dword(HWIO_QPIC_XPU4_SYNR2_ADDR)
#define HWIO_QPIC_XPU4_SYNR2_INM(m)            \
                in_dword_masked(HWIO_QPIC_XPU4_SYNR2_ADDR, m)
#define HWIO_QPIC_XPU4_SYNR2_APSVIOE_BMSK                       0x2000000
#define HWIO_QPIC_XPU4_SYNR2_APSVIOE_SHFT                              25
#define HWIO_QPIC_XPU4_SYNR2_SLE_BMSK                           0x1000000
#define HWIO_QPIC_XPU4_SYNR2_SLE_SHFT                                  24
#define HWIO_QPIC_XPU4_SYNR2_CFG_OWNER_BMSK                      0x800000
#define HWIO_QPIC_XPU4_SYNR2_CFG_OWNER_SHFT                            23
#define HWIO_QPIC_XPU4_SYNR2_APNSEE_BMSK                         0x400000
#define HWIO_QPIC_XPU4_SYNR2_APNSEE_SHFT                               22
#define HWIO_QPIC_XPU4_SYNR2_CESDE_BMSK                          0x200000
#define HWIO_QPIC_XPU4_SYNR2_CESDE_SHFT                                21
#define HWIO_QPIC_XPU4_SYNR2_OPTRW_EN_BMSK                       0x100000
#define HWIO_QPIC_XPU4_SYNR2_OPTRW_EN_SHFT                             20
#define HWIO_QPIC_XPU4_SYNR2_ATOPC_BMSK                           0xf0000
#define HWIO_QPIC_XPU4_SYNR2_ATOPC_SHFT                                16
#define HWIO_QPIC_XPU4_SYNR2_REDIRBITS_BMSK                        0xf000
#define HWIO_QPIC_XPU4_SYNR2_REDIRBITS_SHFT                            12
#define HWIO_QPIC_XPU4_SYNR2_INNERCACHEABLE_BMSK                    0x800
#define HWIO_QPIC_XPU4_SYNR2_INNERCACHEABLE_SHFT                       11
#define HWIO_QPIC_XPU4_SYNR2_MEMTYPE_BMSK                           0x700
#define HWIO_QPIC_XPU4_SYNR2_MEMTYPE_SHFT                               8
#define HWIO_QPIC_XPU4_SYNR2_TRANSIENT_BMSK                          0x80
#define HWIO_QPIC_XPU4_SYNR2_TRANSIENT_SHFT                             7
#define HWIO_QPIC_XPU4_SYNR2_NOALLOCATE_BMSK                         0x40
#define HWIO_QPIC_XPU4_SYNR2_NOALLOCATE_SHFT                            6
#define HWIO_QPIC_XPU4_SYNR2_WRITETHROUGH_BMSK                       0x20
#define HWIO_QPIC_XPU4_SYNR2_WRITETHROUGH_SHFT                          5
#define HWIO_QPIC_XPU4_SYNR2_CACHEALLOCATION_BMSK                    0x1e
#define HWIO_QPIC_XPU4_SYNR2_CACHEALLOCATION_SHFT                       1
#define HWIO_QPIC_XPU4_SYNR2_DIRTYINFO_BMSK                           0x1
#define HWIO_QPIC_XPU4_SYNR2_DIRTYINFO_SHFT                             0

#define HWIO_QPIC_XPU4_RGCR0n_ADDR(n)                          (QPIC_XPU4_REG_BASE      + 0X1000 + (0x40*(n)))
#define HWIO_QPIC_XPU4_RGCR0n_RMSK                                    0x1
#define HWIO_QPIC_XPU4_RGCR0n_MAXn                                     22
#define HWIO_QPIC_XPU4_RGCR0n_INI(n)                \
                in_dword_masked(HWIO_QPIC_XPU4_RGCR0n_ADDR(n), HWIO_QPIC_XPU4_RGCR0n_RMSK)
#define HWIO_QPIC_XPU4_RGCR0n_INMI(n,mask)        \
                in_dword_masked(HWIO_QPIC_XPU4_RGCR0n_ADDR(n), mask)
#define HWIO_QPIC_XPU4_RGCR0n_OUTI(n,val)        \
                out_dword(HWIO_QPIC_XPU4_RGCR0n_ADDR(n),val)
#define HWIO_QPIC_XPU4_RGCR0n_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_QPIC_XPU4_RGCR0n_ADDR(n),mask,val,HWIO_QPIC_XPU4_RGCR0n_INI(n))
#define HWIO_QPIC_XPU4_RGCR0n_RGWOWP_BMSK                             0x1
#define HWIO_QPIC_XPU4_RGCR0n_RGWOWP_SHFT                               0

#define HWIO_QPIC_XPU4_RGCR1n_ADDR(n)                          (QPIC_XPU4_REG_BASE      + 0X1004 + (0x40*(n)))
#define HWIO_QPIC_XPU4_RGCR1n_RMSK                                    0x1
#define HWIO_QPIC_XPU4_RGCR1n_MAXn                                     22
#define HWIO_QPIC_XPU4_RGCR1n_INI(n)                \
                in_dword_masked(HWIO_QPIC_XPU4_RGCR1n_ADDR(n), HWIO_QPIC_XPU4_RGCR1n_RMSK)
#define HWIO_QPIC_XPU4_RGCR1n_INMI(n,mask)        \
                in_dword_masked(HWIO_QPIC_XPU4_RGCR1n_ADDR(n), mask)
#define HWIO_QPIC_XPU4_RGCR1n_OUTI(n,val)        \
                out_dword(HWIO_QPIC_XPU4_RGCR1n_ADDR(n),val)
#define HWIO_QPIC_XPU4_RGCR1n_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_QPIC_XPU4_RGCR1n_ADDR(n),mask,val,HWIO_QPIC_XPU4_RGCR1n_INI(n))
#define HWIO_QPIC_XPU4_RGCR1n_RGE_BMSK                                0x1
#define HWIO_QPIC_XPU4_RGCR1n_RGE_SHFT                                  0

#define HWIO_QPIC_XPU4_RGRDRn_ADDR(n)                          (QPIC_XPU4_REG_BASE      + 0X1018 + (0x40*(n)))
#define HWIO_QPIC_XPU4_RGRDRn_RMSK                             0xc000007f
#define HWIO_QPIC_XPU4_RGRDRn_MAXn                                     22
#define HWIO_QPIC_XPU4_RGRDRn_INI(n)                \
                in_dword_masked(HWIO_QPIC_XPU4_RGRDRn_ADDR(n), HWIO_QPIC_XPU4_RGRDRn_RMSK)
#define HWIO_QPIC_XPU4_RGRDRn_INMI(n,mask)        \
                in_dword_masked(HWIO_QPIC_XPU4_RGRDRn_ADDR(n), mask)
#define HWIO_QPIC_XPU4_RGRDRn_OUTI(n,val)        \
                out_dword(HWIO_QPIC_XPU4_RGRDRn_ADDR(n),val)
#define HWIO_QPIC_XPU4_RGRDRn_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_QPIC_XPU4_RGRDRn_ADDR(n),mask,val,HWIO_QPIC_XPU4_RGRDRn_INI(n))
#define HWIO_QPIC_XPU4_RGRDRn_RDA_S_BMSK                       0x80000000
#define HWIO_QPIC_XPU4_RGRDRn_RDA_S_SHFT                               31
#define HWIO_QPIC_XPU4_RGRDRn_RDA_NS_BMSK                      0x40000000
#define HWIO_QPIC_XPU4_RGRDRn_RDA_NS_SHFT                              30
#define HWIO_QPIC_XPU4_RGRDRn_RDA_QAD_BMSK                           0x7f
#define HWIO_QPIC_XPU4_RGRDRn_RDA_QAD_SHFT                              0

#define HWIO_QPIC_XPU4_RGWRRn_ADDR(n)                          (QPIC_XPU4_REG_BASE      + 0X101C + (0x40*(n)))
#define HWIO_QPIC_XPU4_RGWRRn_RMSK                             0xc000007f
#define HWIO_QPIC_XPU4_RGWRRn_MAXn                                     22
#define HWIO_QPIC_XPU4_RGWRRn_INI(n)                \
                in_dword_masked(HWIO_QPIC_XPU4_RGWRRn_ADDR(n), HWIO_QPIC_XPU4_RGWRRn_RMSK)
#define HWIO_QPIC_XPU4_RGWRRn_INMI(n,mask)        \
                in_dword_masked(HWIO_QPIC_XPU4_RGWRRn_ADDR(n), mask)
#define HWIO_QPIC_XPU4_RGWRRn_OUTI(n,val)        \
                out_dword(HWIO_QPIC_XPU4_RGWRRn_ADDR(n),val)
#define HWIO_QPIC_XPU4_RGWRRn_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_QPIC_XPU4_RGWRRn_ADDR(n),mask,val,HWIO_QPIC_XPU4_RGWRRn_INI(n))
#define HWIO_QPIC_XPU4_RGWRRn_WRA_S_BMSK                       0x80000000
#define HWIO_QPIC_XPU4_RGWRRn_WRA_S_SHFT                               31
#define HWIO_QPIC_XPU4_RGWRRn_WRA_NS_BMSK                      0x40000000
#define HWIO_QPIC_XPU4_RGWRRn_WRA_NS_SHFT                              30
#define HWIO_QPIC_XPU4_RGWRRn_WRA_QAD_BMSK                           0x7f
#define HWIO_QPIC_XPU4_RGWRRn_WRA_QAD_SHFT                              0

#define HWIO_QPIC_XPU4_QADRGLn_ADDR(n)                         (QPIC_XPU4_REG_BASE      + 0X1030 + (0x40*(n)))
#define HWIO_QPIC_XPU4_QADRGLn_RMSK                            0xc000007f
#define HWIO_QPIC_XPU4_QADRGLn_MAXn                                    22
#define HWIO_QPIC_XPU4_QADRGLn_INI(n)                \
                in_dword_masked(HWIO_QPIC_XPU4_QADRGLn_ADDR(n), HWIO_QPIC_XPU4_QADRGLn_RMSK)
#define HWIO_QPIC_XPU4_QADRGLn_INMI(n,mask)        \
                in_dword_masked(HWIO_QPIC_XPU4_QADRGLn_ADDR(n), mask)
#define HWIO_QPIC_XPU4_QADRGLn_OUTI(n,val)        \
                out_dword(HWIO_QPIC_XPU4_QADRGLn_ADDR(n),val)
#define HWIO_QPIC_XPU4_QADRGLn_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_QPIC_XPU4_QADRGLn_ADDR(n),mask,val,HWIO_QPIC_XPU4_QADRGLn_INI(n))
#define HWIO_QPIC_XPU4_QADRGLn_RGL_S_BMSK                      0x80000000
#define HWIO_QPIC_XPU4_QADRGLn_RGL_S_SHFT                              31
#define HWIO_QPIC_XPU4_QADRGLn_RGL_NS_BMSK                     0x40000000
#define HWIO_QPIC_XPU4_QADRGLn_RGL_NS_SHFT                             30
#define HWIO_QPIC_XPU4_QADRGLn_RGL_QAD_BMSK                          0x7f
#define HWIO_QPIC_XPU4_QADRGLn_RGL_QAD_SHFT                             0


#endif /* __FLASH_QPIC_XPU_H__ */
