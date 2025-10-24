#ifndef __HALGCCUSB_H__
#define __HALGCCUSB_H__
/*
===========================================================================
*/
/**
    @file HalGccUsb.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8550 (Kailua) [kailua_v1.0_p3q3r10.0_rtl_partition_MTO]
 
    This file contains HWIO register definitions for the following modules:
        GCC_CLK_CTL_REG
        TCSR_TCSR_REGS

    'Include' filters applied: USB.*._BCR.*[GCC_CLK_CTL_REG] USB.*._GDSCR.*[GCC_CLK_CTL_REG] USB.*._PIPE_CBCR.*[GCC_CLK_CTL_REG] USB.*._CLKREF[GCC_CLK_CTL_REG] GCC.*.[TCSR_TCSR_REGS] 

    Generation parameters: 
    { 'filename': 'HalGccUsb.h',
      'header': '#include "msmhwiobase.h"\n#include "HALhwio.h"',
      'module-filter-include': { 'GCC_CLK_CTL_REG': [ 'USB.*._BCR.*',
                                                      'USB.*._GDSCR.*',
                                                      'USB.*._PIPE_CBCR.*',
                                                      'USB.*._CLKREF'],
                                 'TCSR_TCSR_REGS': ['GCC.*.']},
      'modules': ['GCC_CLK_CTL_REG', 'TCSR_TCSR_REGS'],
      'output-attrs': True,
      'output-fvals': True,
      'output-offsets': True,
      'output-phys': True,
      'output-resets': True}

    Attribute definitions for the HWIO_*_ATTR macros are as follows:
        0x0: Command register
        0x1: Read-Only
        0x2: Write-Only
        0x3: Read/Write
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

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Include/HalGccUsb.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"
#include "HALhwio.h"

/*----------------------------------------------------------------------------
 * MODULE: GCC_CLK_CTL_REG
 *--------------------------------------------------------------------------*/

#define GCC_CLK_CTL_REG_REG_BASE                                                                       (CLK_CTL_BASE      + 0x00010000)
#define GCC_CLK_CTL_REG_REG_BASE_SIZE                                                                  0x1e0000
#define GCC_CLK_CTL_REG_REG_BASE_USED                                                                  0x8f01c
#define GCC_CLK_CTL_REG_REG_BASE_PHYS                                                                  (CLK_CTL_BASE_PHYS + 0x00010000)
#define GCC_CLK_CTL_REG_REG_BASE_OFFS                                                                  0x00010000

#define HWIO_GCC_QUSB2PHY_PRIM_BCR_ADDR                                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x2000)
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_PHYS                                                                (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x2000)
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_OFFS                                                                (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x2000)
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_RMSK                                                                       0x1
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_POR                                                                 0x00000000
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_POR_RMSK                                                            0xffffffff
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_ATTR                                                                             0x3
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_IN                    \
                in_dword(HWIO_GCC_QUSB2PHY_PRIM_BCR_ADDR)
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_QUSB2PHY_PRIM_BCR_ADDR, m)
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_OUT(v)            \
                out_dword(HWIO_GCC_QUSB2PHY_PRIM_BCR_ADDR,v)
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_QUSB2PHY_PRIM_BCR_ADDR,m,v,HWIO_GCC_QUSB2PHY_PRIM_BCR_IN)
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK                                                              0x1
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_SHFT                                                                0
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_DISABLE_FVAL                                                      0x0
#define HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_ENABLE_FVAL                                                       0x1

#define HWIO_GCC_QUSB2PHY_SEC_BCR_ADDR                                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x2004)
#define HWIO_GCC_QUSB2PHY_SEC_BCR_PHYS                                                                 (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x2004)
#define HWIO_GCC_QUSB2PHY_SEC_BCR_OFFS                                                                 (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x2004)
#define HWIO_GCC_QUSB2PHY_SEC_BCR_RMSK                                                                        0x1
#define HWIO_GCC_QUSB2PHY_SEC_BCR_POR                                                                  0x00000000
#define HWIO_GCC_QUSB2PHY_SEC_BCR_POR_RMSK                                                             0xffffffff
#define HWIO_GCC_QUSB2PHY_SEC_BCR_ATTR                                                                              0x3
#define HWIO_GCC_QUSB2PHY_SEC_BCR_IN                    \
                in_dword(HWIO_GCC_QUSB2PHY_SEC_BCR_ADDR)
#define HWIO_GCC_QUSB2PHY_SEC_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_QUSB2PHY_SEC_BCR_ADDR, m)
#define HWIO_GCC_QUSB2PHY_SEC_BCR_OUT(v)            \
                out_dword(HWIO_GCC_QUSB2PHY_SEC_BCR_ADDR,v)
#define HWIO_GCC_QUSB2PHY_SEC_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_QUSB2PHY_SEC_BCR_ADDR,m,v,HWIO_GCC_QUSB2PHY_SEC_BCR_IN)
#define HWIO_GCC_QUSB2PHY_SEC_BCR_BLK_ARES_BMSK                                                               0x1
#define HWIO_GCC_QUSB2PHY_SEC_BCR_BLK_ARES_SHFT                                                                 0
#define HWIO_GCC_QUSB2PHY_SEC_BCR_BLK_ARES_DISABLE_FVAL                                                       0x0
#define HWIO_GCC_QUSB2PHY_SEC_BCR_BLK_ARES_ENABLE_FVAL                                                        0x1

#define HWIO_GCC_USB30_PRIM_BCR_ADDR                                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x29000)
#define HWIO_GCC_USB30_PRIM_BCR_PHYS                                                                   (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x29000)
#define HWIO_GCC_USB30_PRIM_BCR_OFFS                                                                   (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x29000)
#define HWIO_GCC_USB30_PRIM_BCR_RMSK                                                                          0x1
#define HWIO_GCC_USB30_PRIM_BCR_POR                                                                    0x00000000
#define HWIO_GCC_USB30_PRIM_BCR_POR_RMSK                                                               0xffffffff
#define HWIO_GCC_USB30_PRIM_BCR_ATTR                                                                                0x3
#define HWIO_GCC_USB30_PRIM_BCR_IN                    \
                in_dword(HWIO_GCC_USB30_PRIM_BCR_ADDR)
#define HWIO_GCC_USB30_PRIM_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB30_PRIM_BCR_ADDR, m)
#define HWIO_GCC_USB30_PRIM_BCR_OUT(v)            \
                out_dword(HWIO_GCC_USB30_PRIM_BCR_ADDR,v)
#define HWIO_GCC_USB30_PRIM_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB30_PRIM_BCR_ADDR,m,v,HWIO_GCC_USB30_PRIM_BCR_IN)
#define HWIO_GCC_USB30_PRIM_BCR_BLK_ARES_BMSK                                                                 0x1
#define HWIO_GCC_USB30_PRIM_BCR_BLK_ARES_SHFT                                                                   0
#define HWIO_GCC_USB30_PRIM_BCR_BLK_ARES_DISABLE_FVAL                                                         0x0
#define HWIO_GCC_USB30_PRIM_BCR_BLK_ARES_ENABLE_FVAL                                                          0x1

#define HWIO_GCC_USB30_PRIM_GDSCR_ADDR                                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x29004)
#define HWIO_GCC_USB30_PRIM_GDSCR_PHYS                                                                 (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x29004)
#define HWIO_GCC_USB30_PRIM_GDSCR_OFFS                                                                 (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x29004)
#define HWIO_GCC_USB30_PRIM_GDSCR_RMSK                                                                 0xf8ffffff
#define HWIO_GCC_USB30_PRIM_GDSCR_POR                                                                  0x0022f801
#define HWIO_GCC_USB30_PRIM_GDSCR_POR_RMSK                                                             0xffffffff
#define HWIO_GCC_USB30_PRIM_GDSCR_ATTR                                                                              0x3
#define HWIO_GCC_USB30_PRIM_GDSCR_IN                    \
                in_dword(HWIO_GCC_USB30_PRIM_GDSCR_ADDR)
#define HWIO_GCC_USB30_PRIM_GDSCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB30_PRIM_GDSCR_ADDR, m)
#define HWIO_GCC_USB30_PRIM_GDSCR_OUT(v)            \
                out_dword(HWIO_GCC_USB30_PRIM_GDSCR_ADDR,v)
#define HWIO_GCC_USB30_PRIM_GDSCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB30_PRIM_GDSCR_ADDR,m,v,HWIO_GCC_USB30_PRIM_GDSCR_IN)
#define HWIO_GCC_USB30_PRIM_GDSCR_PWR_ON_BMSK                                                          0x80000000
#define HWIO_GCC_USB30_PRIM_GDSCR_PWR_ON_SHFT                                                                  31
#define HWIO_GCC_USB30_PRIM_GDSCR_GDSC_STATE_BMSK                                                      0x78000000
#define HWIO_GCC_USB30_PRIM_GDSCR_GDSC_STATE_SHFT                                                              27
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_REST_WAIT_BMSK                                                      0xf00000
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_REST_WAIT_SHFT                                                            20
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_FEW_WAIT_BMSK                                                        0xf0000
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_FEW_WAIT_SHFT                                                             16
#define HWIO_GCC_USB30_PRIM_GDSCR_CLK_DIS_WAIT_BMSK                                                        0xf000
#define HWIO_GCC_USB30_PRIM_GDSCR_CLK_DIS_WAIT_SHFT                                                            12
#define HWIO_GCC_USB30_PRIM_GDSCR_RETAIN_FF_ENABLE_BMSK                                                     0x800
#define HWIO_GCC_USB30_PRIM_GDSCR_RETAIN_FF_ENABLE_SHFT                                                        11
#define HWIO_GCC_USB30_PRIM_GDSCR_RETAIN_FF_ENABLE_DISABLE_FVAL                                               0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_RETAIN_FF_ENABLE_ENABLE_FVAL                                                0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_RESTORE_BMSK                                                              0x400
#define HWIO_GCC_USB30_PRIM_GDSCR_RESTORE_SHFT                                                                 10
#define HWIO_GCC_USB30_PRIM_GDSCR_RESTORE_DISABLE_FVAL                                                        0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_RESTORE_ENABLE_FVAL                                                         0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_SAVE_BMSK                                                                 0x200
#define HWIO_GCC_USB30_PRIM_GDSCR_SAVE_SHFT                                                                     9
#define HWIO_GCC_USB30_PRIM_GDSCR_SAVE_DISABLE_FVAL                                                           0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_SAVE_ENABLE_FVAL                                                            0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_RETAIN_BMSK                                                               0x100
#define HWIO_GCC_USB30_PRIM_GDSCR_RETAIN_SHFT                                                                   8
#define HWIO_GCC_USB30_PRIM_GDSCR_RETAIN_DISABLE_FVAL                                                         0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_RETAIN_ENABLE_FVAL                                                          0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_REST_BMSK                                                               0x80
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_REST_SHFT                                                                  7
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_REST_DISABLE_FVAL                                                        0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_REST_ENABLE_FVAL                                                         0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_FEW_BMSK                                                                0x40
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_FEW_SHFT                                                                   6
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_FEW_DISABLE_FVAL                                                         0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_EN_FEW_ENABLE_FVAL                                                          0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_CLAMP_IO_BMSK                                                              0x20
#define HWIO_GCC_USB30_PRIM_GDSCR_CLAMP_IO_SHFT                                                                 5
#define HWIO_GCC_USB30_PRIM_GDSCR_CLAMP_IO_DISABLE_FVAL                                                       0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_CLAMP_IO_ENABLE_FVAL                                                        0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_CLK_DISABLE_BMSK                                                           0x10
#define HWIO_GCC_USB30_PRIM_GDSCR_CLK_DISABLE_SHFT                                                              4
#define HWIO_GCC_USB30_PRIM_GDSCR_CLK_DISABLE_CLK_NOT_DISABLE_FVAL                                            0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_CLK_DISABLE_CLK_IS_DISABLE_FVAL                                             0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_PD_ARES_BMSK                                                                0x8
#define HWIO_GCC_USB30_PRIM_GDSCR_PD_ARES_SHFT                                                                  3
#define HWIO_GCC_USB30_PRIM_GDSCR_PD_ARES_NO_RESET_FVAL                                                       0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_PD_ARES_RESET_FVAL                                                          0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_SW_OVERRIDE_BMSK                                                            0x4
#define HWIO_GCC_USB30_PRIM_GDSCR_SW_OVERRIDE_SHFT                                                              2
#define HWIO_GCC_USB30_PRIM_GDSCR_SW_OVERRIDE_DISABLE_FVAL                                                    0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_SW_OVERRIDE_ENABLE_FVAL                                                     0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_HW_CONTROL_BMSK                                                             0x2
#define HWIO_GCC_USB30_PRIM_GDSCR_HW_CONTROL_SHFT                                                               1
#define HWIO_GCC_USB30_PRIM_GDSCR_HW_CONTROL_DISABLE_FVAL                                                     0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_HW_CONTROL_ENABLE_FVAL                                                      0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_SW_COLLAPSE_BMSK                                                            0x1
#define HWIO_GCC_USB30_PRIM_GDSCR_SW_COLLAPSE_SHFT                                                              0
#define HWIO_GCC_USB30_PRIM_GDSCR_SW_COLLAPSE_DISABLE_FVAL                                                    0x0
#define HWIO_GCC_USB30_PRIM_GDSCR_SW_COLLAPSE_ENABLE_FVAL                                                     0x1

#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_ADDR                                                             (GCC_CLK_CTL_REG_REG_BASE      + 0x29008)
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_PHYS                                                             (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x29008)
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_OFFS                                                             (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x29008)
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_RMSK                                                              0x7ffffff
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_POR                                                              0x04088000
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_POR_RMSK                                                         0xffffffff
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_ATTR                                                                          0x3
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_IN                    \
                in_dword(HWIO_GCC_USB30_PRIM_CFG_GDSCR_ADDR)
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB30_PRIM_CFG_GDSCR_ADDR, m)
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_OUT(v)            \
                out_dword(HWIO_GCC_USB30_PRIM_CFG_GDSCR_ADDR,v)
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB30_PRIM_CFG_GDSCR_ADDR,m,v,HWIO_GCC_USB30_PRIM_CFG_GDSCR_IN)
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_BMSK                                   0x4000000
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_SHFT                                          26
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_DISABLE_FVAL                                 0x0
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_ENABLE_FVAL                                  0x1
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_PWR_DWN_START_BMSK                                           0x2000000
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_PWR_DWN_START_SHFT                                                  25
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_PWR_UP_START_BMSK                                            0x1000000
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_PWR_UP_START_SHFT                                                   24
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_CFG_FSM_STATE_STATUS_BMSK                                     0xf00000
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_CFG_FSM_STATE_STATUS_SHFT                                           20
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_MEM_PWR_ACK_STATUS_BMSK                                        0x80000
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_MEM_PWR_ACK_STATUS_SHFT                                             19
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_ENR_ACK_STATUS_BMSK                                            0x40000
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_ENR_ACK_STATUS_SHFT                                                 18
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_ENF_ACK_STATUS_BMSK                                            0x20000
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_ENF_ACK_STATUS_SHFT                                                 17
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_POWER_UP_COMPLETE_BMSK                                         0x10000
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_POWER_UP_COMPLETE_SHFT                                              16
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_POWER_DOWN_COMPLETE_BMSK                                        0x8000
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_POWER_DOWN_COMPLETE_SHFT                                            15
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_SOFTWARE_CONTROL_OVERRIDE_BMSK                                       0x7800
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_SOFTWARE_CONTROL_OVERRIDE_SHFT                                           11
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_HANDSHAKE_DIS_BMSK                                               0x400
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_HANDSHAKE_DIS_SHFT                                                  10
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_MEM_PERI_FORCE_IN_SW_BMSK                                        0x200
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_MEM_PERI_FORCE_IN_SW_SHFT                                            9
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_MEM_CORE_FORCE_IN_SW_BMSK                                        0x100
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_MEM_CORE_FORCE_IN_SW_SHFT                                            8
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_PHASE_RESET_EN_SW_BMSK                                            0x80
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_PHASE_RESET_EN_SW_SHFT                                               7
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_PHASE_RESET_DELAY_COUNT_SW_BMSK                                   0x60
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_PHASE_RESET_DELAY_COUNT_SW_SHFT                                      5
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_PSCBC_PWR_DWN_SW_BMSK                                             0x10
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_GDSC_PSCBC_PWR_DWN_SW_SHFT                                                4
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_UNCLAMP_IO_SOFTWARE_OVERRIDE_BMSK                                       0x8
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_UNCLAMP_IO_SOFTWARE_OVERRIDE_SHFT                                         3
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_SAVE_RESTORE_SOFTWARE_OVERRIDE_BMSK                                     0x4
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_SAVE_RESTORE_SOFTWARE_OVERRIDE_SHFT                                       2
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_CLAMP_IO_SOFTWARE_OVERRIDE_BMSK                                         0x2
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_CLAMP_IO_SOFTWARE_OVERRIDE_SHFT                                           1
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_DISABLE_CLK_SOFTWARE_OVERRIDE_BMSK                                      0x1
#define HWIO_GCC_USB30_PRIM_CFG_GDSCR_DISABLE_CLK_SOFTWARE_OVERRIDE_SHFT                                        0

#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_ADDR                                                            (GCC_CLK_CTL_REG_REG_BASE      + 0x2900c)
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_PHYS                                                            (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x2900c)
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_OFFS                                                            (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x2900c)
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_RMSK                                                               0x7ffff
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_POR                                                             0x0002022a
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_POR_RMSK                                                        0xffffffff
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_ATTR                                                                         0x3
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_IN                    \
                in_dword(HWIO_GCC_USB30_PRIM_CFG2_GDSCR_ADDR)
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB30_PRIM_CFG2_GDSCR_ADDR, m)
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_OUT(v)            \
                out_dword(HWIO_GCC_USB30_PRIM_CFG2_GDSCR_ADDR,v)
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB30_PRIM_CFG2_GDSCR_ADDR,m,v,HWIO_GCC_USB30_PRIM_CFG2_GDSCR_IN)
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_GDSC_MEM_PWRUP_ACK_OVERRIDE_BMSK                                   0x40000
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_GDSC_MEM_PWRUP_ACK_OVERRIDE_SHFT                                        18
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_GDSC_PWRDWN_ENABLE_ACK_OVERRIDE_BMSK                               0x20000
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_GDSC_PWRDWN_ENABLE_ACK_OVERRIDE_SHFT                                    17
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_GDSC_CLAMP_MEM_SW_BMSK                                             0x10000
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_GDSC_CLAMP_MEM_SW_SHFT                                                  16
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_DLY_MEM_PWR_UP_BMSK                                                 0xf000
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_DLY_MEM_PWR_UP_SHFT                                                     12
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_DLY_DEASSERT_CLAMP_MEM_BMSK                                          0xf00
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_DLY_DEASSERT_CLAMP_MEM_SHFT                                              8
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_DLY_ASSERT_CLAMP_MEM_BMSK                                             0xf0
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_DLY_ASSERT_CLAMP_MEM_SHFT                                                4
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_MEM_PWR_DWN_TIMEOUT_BMSK                                               0xf
#define HWIO_GCC_USB30_PRIM_CFG2_GDSCR_MEM_PWR_DWN_TIMEOUT_SHFT                                                 0

#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_ADDR                                                            (GCC_CLK_CTL_REG_REG_BASE      + 0x29010)
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_PHYS                                                            (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x29010)
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_OFFS                                                            (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x29010)
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_RMSK                                                             0x7ffffff
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_POR                                                             0x00f00000
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_POR_RMSK                                                        0xffffffff
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_ATTR                                                                         0x3
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_IN                    \
                in_dword(HWIO_GCC_USB30_PRIM_CFG3_GDSCR_ADDR)
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB30_PRIM_CFG3_GDSCR_ADDR, m)
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_OUT(v)            \
                out_dword(HWIO_GCC_USB30_PRIM_CFG3_GDSCR_ADDR,v)
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB30_PRIM_CFG3_GDSCR_ADDR,m,v,HWIO_GCC_USB30_PRIM_CFG3_GDSCR_IN)
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_STATUS_BMSK                           0x4000000
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_STATUS_SHFT                                  26
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_ENABLE_BMSK                                        0x2000000
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_ENABLE_SHFT                                               25
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_ENABLE_DISABLE_FVAL                                      0x0
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_ENABLE_ENABLE_FVAL                                       0x1
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_DLY_ACCU_RED_SHIFTER_DONE_BMSK                                   0x1e00000
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_DLY_ACCU_RED_SHIFTER_DONE_SHFT                                          21
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_TIMER_EN_SW_BMSK                                    0x100000
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_TIMER_EN_SW_SHFT                                          20
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_TIMER_EN_SW_DISABLE_FVAL                                 0x0
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_TIMER_EN_SW_ENABLE_FVAL                                  0x1
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_OVERRIDE_BMSK                           0x80000
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_OVERRIDE_SHFT                                19
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_OVERRIDE_DISABLE_FVAL                       0x0
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_OVERRIDE_ENABLE_FVAL                        0x1
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_CLK_EN_SW_BMSK                               0x40000
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_CLK_EN_SW_SHFT                                    18
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_CLK_EN_SW_DISABLE_FVAL                           0x0
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_CLK_EN_SW_ENABLE_FVAL                            0x1
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_START_SW_BMSK                                0x20000
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_START_SW_SHFT                                     17
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_START_SW_DISABLE_FVAL                            0x0
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_START_SW_ENABLE_FVAL                             0x1
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SW_OVERRIDE_BMSK                                     0x10000
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SW_OVERRIDE_SHFT                                          16
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SW_OVERRIDE_DISABLE_FVAL                                 0x0
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_ACCU_RED_SW_OVERRIDE_ENABLE_FVAL                                  0x1
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_SPARE_CTRL_IN_BMSK                                             0xff00
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_SPARE_CTRL_IN_SHFT                                                  8
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_SPARE_CTRL_OUT_BMSK                                              0xff
#define HWIO_GCC_USB30_PRIM_CFG3_GDSCR_GDSC_SPARE_CTRL_OUT_SHFT                                                 0

#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_ADDR                                                            (GCC_CLK_CTL_REG_REG_BASE      + 0x29014)
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_PHYS                                                            (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x29014)
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_OFFS                                                            (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x29014)
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_RMSK                                                              0xffffff
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_POR                                                             0x00222222
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_POR_RMSK                                                        0xffffffff
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_ATTR                                                                         0x3
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_IN                    \
                in_dword(HWIO_GCC_USB30_PRIM_CFG4_GDSCR_ADDR)
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB30_PRIM_CFG4_GDSCR_ADDR, m)
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_OUT(v)            \
                out_dword(HWIO_GCC_USB30_PRIM_CFG4_GDSCR_ADDR,v)
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB30_PRIM_CFG4_GDSCR_ADDR,m,v,HWIO_GCC_USB30_PRIM_CFG4_GDSCR_IN)
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_UNCLAMPIO_BMSK                                                0xf00000
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_UNCLAMPIO_SHFT                                                      20
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_RESTOREFF_BMSK                                                 0xf0000
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_RESTOREFF_SHFT                                                      16
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_NORETAINFF_BMSK                                                 0xf000
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_NORETAINFF_SHFT                                                     12
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_DEASSERTARES_BMSK                                                0xf00
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_DEASSERTARES_SHFT                                                    8
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_CLAMPIO_BMSK                                                      0xf0
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_CLAMPIO_SHFT                                                         4
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_RETAINFF_BMSK                                                      0xf
#define HWIO_GCC_USB30_PRIM_CFG4_GDSCR_DLY_RETAINFF_SHFT                                                        0

#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_ADDR                                                          (GCC_CLK_CTL_REG_REG_BASE      + 0x29068)
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_PHYS                                                          (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x29068)
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_OFFS                                                          (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x29068)
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_RMSK                                                          0x81c0000f
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_POR                                                           0x80000000
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_POR_RMSK                                                      0xffffffff
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_ATTR                                                                       0x3
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_IN                    \
                in_dword(HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_ADDR)
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_ADDR, m)
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_ADDR,v)
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_ADDR,m,v,HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_IN)
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_OFF_BMSK                                                  0x80000000
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_OFF_SHFT                                                          31
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_IGNORE_ALL_ARES_BMSK                                           0x1000000
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_IGNORE_ALL_ARES_SHFT                                                  24
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                         0x800000
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                               23
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_DIS_BMSK                                                    0x400000
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_DIS_SHFT                                                          22
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_SW_ONLY_EN_BMSK                                                      0x8
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_SW_ONLY_EN_SHFT                                                        3
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_ARES_BMSK                                                        0x4
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_ARES_SHFT                                                          2
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_ARES_NO_RESET_FVAL                                               0x0
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_ARES_RESET_FVAL                                                  0x1
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_HW_CTL_BMSK                                                          0x2
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_HW_CTL_SHFT                                                            1
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_HW_CTL_DISABLE_FVAL                                                  0x0
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_HW_CTL_ENABLE_FVAL                                                   0x1
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_ENABLE_SHFT                                                        0
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_ENABLE_DISABLE_FVAL                                              0x0
#define HWIO_GCC_USB3_PRIM_PHY_PIPE_CBCR_CLK_ENABLE_ENABLE_FVAL                                               0x1

#define HWIO_GCC_USB3_PHY_PRIM_BCR_ADDR                                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x40000)
#define HWIO_GCC_USB3_PHY_PRIM_BCR_PHYS                                                                (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x40000)
#define HWIO_GCC_USB3_PHY_PRIM_BCR_OFFS                                                                (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x40000)
#define HWIO_GCC_USB3_PHY_PRIM_BCR_RMSK                                                                       0x1
#define HWIO_GCC_USB3_PHY_PRIM_BCR_POR                                                                 0x00000001
#define HWIO_GCC_USB3_PHY_PRIM_BCR_POR_RMSK                                                            0xffffffff
#define HWIO_GCC_USB3_PHY_PRIM_BCR_ATTR                                                                             0x3
#define HWIO_GCC_USB3_PHY_PRIM_BCR_IN                    \
                in_dword(HWIO_GCC_USB3_PHY_PRIM_BCR_ADDR)
#define HWIO_GCC_USB3_PHY_PRIM_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3_PHY_PRIM_BCR_ADDR, m)
#define HWIO_GCC_USB3_PHY_PRIM_BCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3_PHY_PRIM_BCR_ADDR,v)
#define HWIO_GCC_USB3_PHY_PRIM_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3_PHY_PRIM_BCR_ADDR,m,v,HWIO_GCC_USB3_PHY_PRIM_BCR_IN)
#define HWIO_GCC_USB3_PHY_PRIM_BCR_BLK_ARES_BMSK                                                              0x1
#define HWIO_GCC_USB3_PHY_PRIM_BCR_BLK_ARES_SHFT                                                                0
#define HWIO_GCC_USB3_PHY_PRIM_BCR_BLK_ARES_DISABLE_FVAL                                                      0x0
#define HWIO_GCC_USB3_PHY_PRIM_BCR_BLK_ARES_ENABLE_FVAL                                                       0x1

#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_ADDR                                                             (GCC_CLK_CTL_REG_REG_BASE      + 0x40004)
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_PHYS                                                             (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x40004)
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_OFFS                                                             (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x40004)
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_RMSK                                                                    0x1
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_POR                                                              0x00000000
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_POR_RMSK                                                         0xffffffff
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_ATTR                                                                          0x3
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_IN                    \
                in_dword(HWIO_GCC_USB3PHY_PHY_PRIM_BCR_ADDR)
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3PHY_PHY_PRIM_BCR_ADDR, m)
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3PHY_PHY_PRIM_BCR_ADDR,v)
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3PHY_PHY_PRIM_BCR_ADDR,m,v,HWIO_GCC_USB3PHY_PHY_PRIM_BCR_IN)
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_BLK_ARES_BMSK                                                           0x1
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_BLK_ARES_SHFT                                                             0
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_BLK_ARES_DISABLE_FVAL                                                   0x0
#define HWIO_GCC_USB3PHY_PHY_PRIM_BCR_BLK_ARES_ENABLE_FVAL                                                    0x1

#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_ADDR                                                             (GCC_CLK_CTL_REG_REG_BASE      + 0x40008)
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_PHYS                                                             (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x40008)
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_OFFS                                                             (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x40008)
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_RMSK                                                                    0x1
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_POR                                                              0x00000000
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_POR_RMSK                                                         0xffffffff
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_ATTR                                                                          0x3
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_IN                    \
                in_dword(HWIO_GCC_USB3_DP_PHY_PRIM_BCR_ADDR)
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3_DP_PHY_PRIM_BCR_ADDR, m)
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3_DP_PHY_PRIM_BCR_ADDR,v)
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3_DP_PHY_PRIM_BCR_ADDR,m,v,HWIO_GCC_USB3_DP_PHY_PRIM_BCR_IN)
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_BLK_ARES_BMSK                                                           0x1
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_BLK_ARES_SHFT                                                             0
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_BLK_ARES_DISABLE_FVAL                                                   0x0
#define HWIO_GCC_USB3_DP_PHY_PRIM_BCR_BLK_ARES_ENABLE_FVAL                                                    0x1

#define HWIO_GCC_USB3_PHY_SEC_BCR_ADDR                                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x4000c)
#define HWIO_GCC_USB3_PHY_SEC_BCR_PHYS                                                                 (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x4000c)
#define HWIO_GCC_USB3_PHY_SEC_BCR_OFFS                                                                 (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x4000c)
#define HWIO_GCC_USB3_PHY_SEC_BCR_RMSK                                                                        0x1
#define HWIO_GCC_USB3_PHY_SEC_BCR_POR                                                                  0x00000000
#define HWIO_GCC_USB3_PHY_SEC_BCR_POR_RMSK                                                             0xffffffff
#define HWIO_GCC_USB3_PHY_SEC_BCR_ATTR                                                                              0x3
#define HWIO_GCC_USB3_PHY_SEC_BCR_IN                    \
                in_dword(HWIO_GCC_USB3_PHY_SEC_BCR_ADDR)
#define HWIO_GCC_USB3_PHY_SEC_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3_PHY_SEC_BCR_ADDR, m)
#define HWIO_GCC_USB3_PHY_SEC_BCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3_PHY_SEC_BCR_ADDR,v)
#define HWIO_GCC_USB3_PHY_SEC_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3_PHY_SEC_BCR_ADDR,m,v,HWIO_GCC_USB3_PHY_SEC_BCR_IN)
#define HWIO_GCC_USB3_PHY_SEC_BCR_BLK_ARES_BMSK                                                               0x1
#define HWIO_GCC_USB3_PHY_SEC_BCR_BLK_ARES_SHFT                                                                 0
#define HWIO_GCC_USB3_PHY_SEC_BCR_BLK_ARES_DISABLE_FVAL                                                       0x0
#define HWIO_GCC_USB3_PHY_SEC_BCR_BLK_ARES_ENABLE_FVAL                                                        0x1

#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x40010)
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_PHYS                                                              (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x40010)
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_OFFS                                                              (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x40010)
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_RMSK                                                                     0x1
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_POR                                                               0x00000000
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_POR_RMSK                                                          0xffffffff
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_ATTR                                                                           0x3
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_IN                    \
                in_dword(HWIO_GCC_USB3PHY_PHY_SEC_BCR_ADDR)
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3PHY_PHY_SEC_BCR_ADDR, m)
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3PHY_PHY_SEC_BCR_ADDR,v)
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3PHY_PHY_SEC_BCR_ADDR,m,v,HWIO_GCC_USB3PHY_PHY_SEC_BCR_IN)
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_BLK_ARES_BMSK                                                            0x1
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_BLK_ARES_SHFT                                                              0
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_BLK_ARES_DISABLE_FVAL                                                    0x0
#define HWIO_GCC_USB3PHY_PHY_SEC_BCR_BLK_ARES_ENABLE_FVAL                                                     0x1

#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x40014)
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_PHYS                                                              (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x40014)
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_OFFS                                                              (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x40014)
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_RMSK                                                                     0x1
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_POR                                                               0x00000000
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_POR_RMSK                                                          0xffffffff
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_ATTR                                                                           0x3
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_IN                    \
                in_dword(HWIO_GCC_USB3_DP_PHY_SEC_BCR_ADDR)
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3_DP_PHY_SEC_BCR_ADDR, m)
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3_DP_PHY_SEC_BCR_ADDR,v)
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3_DP_PHY_SEC_BCR_ADDR,m,v,HWIO_GCC_USB3_DP_PHY_SEC_BCR_IN)
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_BLK_ARES_BMSK                                                            0x1
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_BLK_ARES_SHFT                                                              0
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_BLK_ARES_DISABLE_FVAL                                                    0x0
#define HWIO_GCC_USB3_DP_PHY_SEC_BCR_BLK_ARES_ENABLE_FVAL                                                     0x1

#define HWIO_GCC_USB3_PHY_GDSCR_ADDR                                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x40018)
#define HWIO_GCC_USB3_PHY_GDSCR_PHYS                                                                   (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x40018)
#define HWIO_GCC_USB3_PHY_GDSCR_OFFS                                                                   (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x40018)
#define HWIO_GCC_USB3_PHY_GDSCR_RMSK                                                                   0xf8ffffff
#define HWIO_GCC_USB3_PHY_GDSCR_POR                                                                    0xf8222800
#define HWIO_GCC_USB3_PHY_GDSCR_POR_RMSK                                                               0xffffffff
#define HWIO_GCC_USB3_PHY_GDSCR_ATTR                                                                                0x3
#define HWIO_GCC_USB3_PHY_GDSCR_IN                    \
                in_dword(HWIO_GCC_USB3_PHY_GDSCR_ADDR)
#define HWIO_GCC_USB3_PHY_GDSCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3_PHY_GDSCR_ADDR, m)
#define HWIO_GCC_USB3_PHY_GDSCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3_PHY_GDSCR_ADDR,v)
#define HWIO_GCC_USB3_PHY_GDSCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3_PHY_GDSCR_ADDR,m,v,HWIO_GCC_USB3_PHY_GDSCR_IN)
#define HWIO_GCC_USB3_PHY_GDSCR_PWR_ON_BMSK                                                            0x80000000
#define HWIO_GCC_USB3_PHY_GDSCR_PWR_ON_SHFT                                                                    31
#define HWIO_GCC_USB3_PHY_GDSCR_GDSC_STATE_BMSK                                                        0x78000000
#define HWIO_GCC_USB3_PHY_GDSCR_GDSC_STATE_SHFT                                                                27
#define HWIO_GCC_USB3_PHY_GDSCR_EN_REST_WAIT_BMSK                                                        0xf00000
#define HWIO_GCC_USB3_PHY_GDSCR_EN_REST_WAIT_SHFT                                                              20
#define HWIO_GCC_USB3_PHY_GDSCR_EN_FEW_WAIT_BMSK                                                          0xf0000
#define HWIO_GCC_USB3_PHY_GDSCR_EN_FEW_WAIT_SHFT                                                               16
#define HWIO_GCC_USB3_PHY_GDSCR_CLK_DIS_WAIT_BMSK                                                          0xf000
#define HWIO_GCC_USB3_PHY_GDSCR_CLK_DIS_WAIT_SHFT                                                              12
#define HWIO_GCC_USB3_PHY_GDSCR_RETAIN_FF_ENABLE_BMSK                                                       0x800
#define HWIO_GCC_USB3_PHY_GDSCR_RETAIN_FF_ENABLE_SHFT                                                          11
#define HWIO_GCC_USB3_PHY_GDSCR_RETAIN_FF_ENABLE_DISABLE_FVAL                                                 0x0
#define HWIO_GCC_USB3_PHY_GDSCR_RETAIN_FF_ENABLE_ENABLE_FVAL                                                  0x1
#define HWIO_GCC_USB3_PHY_GDSCR_RESTORE_BMSK                                                                0x400
#define HWIO_GCC_USB3_PHY_GDSCR_RESTORE_SHFT                                                                   10
#define HWIO_GCC_USB3_PHY_GDSCR_RESTORE_DISABLE_FVAL                                                          0x0
#define HWIO_GCC_USB3_PHY_GDSCR_RESTORE_ENABLE_FVAL                                                           0x1
#define HWIO_GCC_USB3_PHY_GDSCR_SAVE_BMSK                                                                   0x200
#define HWIO_GCC_USB3_PHY_GDSCR_SAVE_SHFT                                                                       9
#define HWIO_GCC_USB3_PHY_GDSCR_SAVE_DISABLE_FVAL                                                             0x0
#define HWIO_GCC_USB3_PHY_GDSCR_SAVE_ENABLE_FVAL                                                              0x1
#define HWIO_GCC_USB3_PHY_GDSCR_RETAIN_BMSK                                                                 0x100
#define HWIO_GCC_USB3_PHY_GDSCR_RETAIN_SHFT                                                                     8
#define HWIO_GCC_USB3_PHY_GDSCR_RETAIN_DISABLE_FVAL                                                           0x0
#define HWIO_GCC_USB3_PHY_GDSCR_RETAIN_ENABLE_FVAL                                                            0x1
#define HWIO_GCC_USB3_PHY_GDSCR_EN_REST_BMSK                                                                 0x80
#define HWIO_GCC_USB3_PHY_GDSCR_EN_REST_SHFT                                                                    7
#define HWIO_GCC_USB3_PHY_GDSCR_EN_REST_DISABLE_FVAL                                                          0x0
#define HWIO_GCC_USB3_PHY_GDSCR_EN_REST_ENABLE_FVAL                                                           0x1
#define HWIO_GCC_USB3_PHY_GDSCR_EN_FEW_BMSK                                                                  0x40
#define HWIO_GCC_USB3_PHY_GDSCR_EN_FEW_SHFT                                                                     6
#define HWIO_GCC_USB3_PHY_GDSCR_EN_FEW_DISABLE_FVAL                                                           0x0
#define HWIO_GCC_USB3_PHY_GDSCR_EN_FEW_ENABLE_FVAL                                                            0x1
#define HWIO_GCC_USB3_PHY_GDSCR_CLAMP_IO_BMSK                                                                0x20
#define HWIO_GCC_USB3_PHY_GDSCR_CLAMP_IO_SHFT                                                                   5
#define HWIO_GCC_USB3_PHY_GDSCR_CLAMP_IO_DISABLE_FVAL                                                         0x0
#define HWIO_GCC_USB3_PHY_GDSCR_CLAMP_IO_ENABLE_FVAL                                                          0x1
#define HWIO_GCC_USB3_PHY_GDSCR_CLK_DISABLE_BMSK                                                             0x10
#define HWIO_GCC_USB3_PHY_GDSCR_CLK_DISABLE_SHFT                                                                4
#define HWIO_GCC_USB3_PHY_GDSCR_CLK_DISABLE_CLK_NOT_DISABLE_FVAL                                              0x0
#define HWIO_GCC_USB3_PHY_GDSCR_CLK_DISABLE_CLK_IS_DISABLE_FVAL                                               0x1
#define HWIO_GCC_USB3_PHY_GDSCR_PD_ARES_BMSK                                                                  0x8
#define HWIO_GCC_USB3_PHY_GDSCR_PD_ARES_SHFT                                                                    3
#define HWIO_GCC_USB3_PHY_GDSCR_PD_ARES_NO_RESET_FVAL                                                         0x0
#define HWIO_GCC_USB3_PHY_GDSCR_PD_ARES_RESET_FVAL                                                            0x1
#define HWIO_GCC_USB3_PHY_GDSCR_SW_OVERRIDE_BMSK                                                              0x4
#define HWIO_GCC_USB3_PHY_GDSCR_SW_OVERRIDE_SHFT                                                                2
#define HWIO_GCC_USB3_PHY_GDSCR_SW_OVERRIDE_DISABLE_FVAL                                                      0x0
#define HWIO_GCC_USB3_PHY_GDSCR_SW_OVERRIDE_ENABLE_FVAL                                                       0x1
#define HWIO_GCC_USB3_PHY_GDSCR_HW_CONTROL_BMSK                                                               0x2
#define HWIO_GCC_USB3_PHY_GDSCR_HW_CONTROL_SHFT                                                                 1
#define HWIO_GCC_USB3_PHY_GDSCR_HW_CONTROL_DISABLE_FVAL                                                       0x0
#define HWIO_GCC_USB3_PHY_GDSCR_HW_CONTROL_ENABLE_FVAL                                                        0x1
#define HWIO_GCC_USB3_PHY_GDSCR_SW_COLLAPSE_BMSK                                                              0x1
#define HWIO_GCC_USB3_PHY_GDSCR_SW_COLLAPSE_SHFT                                                                0
#define HWIO_GCC_USB3_PHY_GDSCR_SW_COLLAPSE_DISABLE_FVAL                                                      0x0
#define HWIO_GCC_USB3_PHY_GDSCR_SW_COLLAPSE_ENABLE_FVAL                                                       0x1

#define HWIO_GCC_USB3_PHY_CFG_GDSCR_ADDR                                                               (GCC_CLK_CTL_REG_REG_BASE      + 0x4001c)
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_PHYS                                                               (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x4001c)
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_OFFS                                                               (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x4001c)
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_RMSK                                                                0x7ffffff
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_POR                                                                0x04070000
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_POR_RMSK                                                           0xffffffff
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_ATTR                                                                            0x3
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_IN                    \
                in_dword(HWIO_GCC_USB3_PHY_CFG_GDSCR_ADDR)
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3_PHY_CFG_GDSCR_ADDR, m)
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3_PHY_CFG_GDSCR_ADDR,v)
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3_PHY_CFG_GDSCR_ADDR,m,v,HWIO_GCC_USB3_PHY_CFG_GDSCR_IN)
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_BMSK                                     0x4000000
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_SHFT                                            26
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_DISABLE_FVAL                                   0x0
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_ENABLE_FVAL                                    0x1
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_PWR_DWN_START_BMSK                                             0x2000000
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_PWR_DWN_START_SHFT                                                    25
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_PWR_UP_START_BMSK                                              0x1000000
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_PWR_UP_START_SHFT                                                     24
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_CFG_FSM_STATE_STATUS_BMSK                                       0xf00000
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_CFG_FSM_STATE_STATUS_SHFT                                             20
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_MEM_PWR_ACK_STATUS_BMSK                                          0x80000
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_MEM_PWR_ACK_STATUS_SHFT                                               19
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_ENR_ACK_STATUS_BMSK                                              0x40000
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_ENR_ACK_STATUS_SHFT                                                   18
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_ENF_ACK_STATUS_BMSK                                              0x20000
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_ENF_ACK_STATUS_SHFT                                                   17
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_POWER_UP_COMPLETE_BMSK                                           0x10000
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_POWER_UP_COMPLETE_SHFT                                                16
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_POWER_DOWN_COMPLETE_BMSK                                          0x8000
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_POWER_DOWN_COMPLETE_SHFT                                              15
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_SOFTWARE_CONTROL_OVERRIDE_BMSK                                         0x7800
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_SOFTWARE_CONTROL_OVERRIDE_SHFT                                             11
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_HANDSHAKE_DIS_BMSK                                                 0x400
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_HANDSHAKE_DIS_SHFT                                                    10
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_MEM_PERI_FORCE_IN_SW_BMSK                                          0x200
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_MEM_PERI_FORCE_IN_SW_SHFT                                              9
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_MEM_CORE_FORCE_IN_SW_BMSK                                          0x100
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_MEM_CORE_FORCE_IN_SW_SHFT                                              8
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_PHASE_RESET_EN_SW_BMSK                                              0x80
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_PHASE_RESET_EN_SW_SHFT                                                 7
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_PHASE_RESET_DELAY_COUNT_SW_BMSK                                     0x60
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_PHASE_RESET_DELAY_COUNT_SW_SHFT                                        5
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_PSCBC_PWR_DWN_SW_BMSK                                               0x10
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_GDSC_PSCBC_PWR_DWN_SW_SHFT                                                  4
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_UNCLAMP_IO_SOFTWARE_OVERRIDE_BMSK                                         0x8
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_UNCLAMP_IO_SOFTWARE_OVERRIDE_SHFT                                           3
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_SAVE_RESTORE_SOFTWARE_OVERRIDE_BMSK                                       0x4
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_SAVE_RESTORE_SOFTWARE_OVERRIDE_SHFT                                         2
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_CLAMP_IO_SOFTWARE_OVERRIDE_BMSK                                           0x2
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_CLAMP_IO_SOFTWARE_OVERRIDE_SHFT                                             1
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_DISABLE_CLK_SOFTWARE_OVERRIDE_BMSK                                        0x1
#define HWIO_GCC_USB3_PHY_CFG_GDSCR_DISABLE_CLK_SOFTWARE_OVERRIDE_SHFT                                          0

#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x40020)
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_PHYS                                                              (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x40020)
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_OFFS                                                              (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x40020)
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_RMSK                                                                 0x7ffff
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_POR                                                               0x0002022a
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_POR_RMSK                                                          0xffffffff
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_ATTR                                                                           0x3
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_IN                    \
                in_dword(HWIO_GCC_USB3_PHY_CFG2_GDSCR_ADDR)
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3_PHY_CFG2_GDSCR_ADDR, m)
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3_PHY_CFG2_GDSCR_ADDR,v)
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3_PHY_CFG2_GDSCR_ADDR,m,v,HWIO_GCC_USB3_PHY_CFG2_GDSCR_IN)
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_GDSC_MEM_PWRUP_ACK_OVERRIDE_BMSK                                     0x40000
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_GDSC_MEM_PWRUP_ACK_OVERRIDE_SHFT                                          18
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_GDSC_PWRDWN_ENABLE_ACK_OVERRIDE_BMSK                                 0x20000
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_GDSC_PWRDWN_ENABLE_ACK_OVERRIDE_SHFT                                      17
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_GDSC_CLAMP_MEM_SW_BMSK                                               0x10000
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_GDSC_CLAMP_MEM_SW_SHFT                                                    16
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_DLY_MEM_PWR_UP_BMSK                                                   0xf000
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_DLY_MEM_PWR_UP_SHFT                                                       12
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_DLY_DEASSERT_CLAMP_MEM_BMSK                                            0xf00
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_DLY_DEASSERT_CLAMP_MEM_SHFT                                                8
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_DLY_ASSERT_CLAMP_MEM_BMSK                                               0xf0
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_DLY_ASSERT_CLAMP_MEM_SHFT                                                  4
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_MEM_PWR_DWN_TIMEOUT_BMSK                                                 0xf
#define HWIO_GCC_USB3_PHY_CFG2_GDSCR_MEM_PWR_DWN_TIMEOUT_SHFT                                                   0

#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x40024)
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_PHYS                                                              (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x40024)
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_OFFS                                                              (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x40024)
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_RMSK                                                               0x7ffffff
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_POR                                                               0x00f00000
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_POR_RMSK                                                          0xffffffff
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_ATTR                                                                           0x3
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_IN                    \
                in_dword(HWIO_GCC_USB3_PHY_CFG3_GDSCR_ADDR)
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3_PHY_CFG3_GDSCR_ADDR, m)
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3_PHY_CFG3_GDSCR_ADDR,v)
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3_PHY_CFG3_GDSCR_ADDR,m,v,HWIO_GCC_USB3_PHY_CFG3_GDSCR_IN)
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_STATUS_BMSK                             0x4000000
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_STATUS_SHFT                                    26
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_ENABLE_BMSK                                          0x2000000
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_ENABLE_SHFT                                                 25
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_ENABLE_DISABLE_FVAL                                        0x0
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_ENABLE_ENABLE_FVAL                                         0x1
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_DLY_ACCU_RED_SHIFTER_DONE_BMSK                                     0x1e00000
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_DLY_ACCU_RED_SHIFTER_DONE_SHFT                                            21
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_TIMER_EN_SW_BMSK                                      0x100000
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_TIMER_EN_SW_SHFT                                            20
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_TIMER_EN_SW_DISABLE_FVAL                                   0x0
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_TIMER_EN_SW_ENABLE_FVAL                                    0x1
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_OVERRIDE_BMSK                             0x80000
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_OVERRIDE_SHFT                                  19
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_OVERRIDE_DISABLE_FVAL                         0x0
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_OVERRIDE_ENABLE_FVAL                          0x1
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_CLK_EN_SW_BMSK                                 0x40000
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_CLK_EN_SW_SHFT                                      18
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_CLK_EN_SW_DISABLE_FVAL                             0x0
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_CLK_EN_SW_ENABLE_FVAL                              0x1
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_START_SW_BMSK                                  0x20000
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_START_SW_SHFT                                       17
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_START_SW_DISABLE_FVAL                              0x0
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_START_SW_ENABLE_FVAL                               0x1
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SW_OVERRIDE_BMSK                                       0x10000
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SW_OVERRIDE_SHFT                                            16
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SW_OVERRIDE_DISABLE_FVAL                                   0x0
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_ACCU_RED_SW_OVERRIDE_ENABLE_FVAL                                    0x1
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_SPARE_CTRL_IN_BMSK                                               0xff00
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_SPARE_CTRL_IN_SHFT                                                    8
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_SPARE_CTRL_OUT_BMSK                                                0xff
#define HWIO_GCC_USB3_PHY_CFG3_GDSCR_GDSC_SPARE_CTRL_OUT_SHFT                                                   0

#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x40028)
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_PHYS                                                              (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x40028)
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_OFFS                                                              (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x40028)
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_RMSK                                                                0xffffff
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_POR                                                               0x00222222
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_POR_RMSK                                                          0xffffffff
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_ATTR                                                                           0x3
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_IN                    \
                in_dword(HWIO_GCC_USB3_PHY_CFG4_GDSCR_ADDR)
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB3_PHY_CFG4_GDSCR_ADDR, m)
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_OUT(v)            \
                out_dword(HWIO_GCC_USB3_PHY_CFG4_GDSCR_ADDR,v)
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB3_PHY_CFG4_GDSCR_ADDR,m,v,HWIO_GCC_USB3_PHY_CFG4_GDSCR_IN)
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_UNCLAMPIO_BMSK                                                  0xf00000
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_UNCLAMPIO_SHFT                                                        20
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_RESTOREFF_BMSK                                                   0xf0000
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_RESTOREFF_SHFT                                                        16
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_NORETAINFF_BMSK                                                   0xf000
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_NORETAINFF_SHFT                                                       12
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_DEASSERTARES_BMSK                                                  0xf00
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_DEASSERTARES_SHFT                                                      8
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_CLAMPIO_BMSK                                                        0xf0
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_CLAMPIO_SHFT                                                           4
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_RETAINFF_BMSK                                                        0xf
#define HWIO_GCC_USB3_PHY_CFG4_GDSCR_DLY_RETAINFF_SHFT                                                          0

#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_ADDR                                                          (GCC_CLK_CTL_REG_REG_BASE      + 0x5a000)
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_PHYS                                                          (GCC_CLK_CTL_REG_REG_BASE_PHYS + 0x5a000)
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_OFFS                                                          (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x5a000)
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_RMSK                                                                 0x1
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_POR                                                           0x00000000
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_POR_RMSK                                                      0xffffffff
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_ATTR                                                                       0x3
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_IN                    \
                in_dword(HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_ADDR)
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_ADDR, m)
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_OUT(v)            \
                out_dword(HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_ADDR,v)
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_ADDR,m,v,HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_IN)
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_BLK_ARES_BMSK                                                        0x1
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_BLK_ARES_SHFT                                                          0
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_BLK_ARES_DISABLE_FVAL                                                0x0
#define HWIO_GCC_USB_PHY_CFG_AHB2PHY_BCR_BLK_ARES_ENABLE_FVAL                                                 0x1

/*----------------------------------------------------------------------------
 * MODULE: TCSR_TCSR_REGS
 *--------------------------------------------------------------------------*/

#define TCSR_TCSR_REGS_REG_BASE                                                                                                              (CORE_TOP_CSR_BASE      + 0x000c0000)
#define TCSR_TCSR_REGS_REG_BASE_SIZE                                                                                                         0x30000
#define TCSR_TCSR_REGS_REG_BASE_USED                                                                                                         0x2f000
#define TCSR_TCSR_REGS_REG_BASE_PHYS                                                                                                         (CORE_TOP_CSR_BASE_PHYS + 0x000c0000)
#define TCSR_TCSR_REGS_REG_BASE_OFFS                                                                                                         0x000c0000

#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_ADDR                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x15100)
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_PHYS                                                                                     (TCSR_TCSR_REGS_REG_BASE_PHYS + 0x15100)
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_OFFS                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x15100)
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_RMSK                                                                                            0x1
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_POR                                                                                      0x00000000
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_POR_RMSK                                                                                 0xffffffff
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_ATTR                                                                                                  0x3
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_IN                    \
                in_dword(HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_ADDR)
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_INM(m)            \
                in_dword_masked(HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_ADDR, m)
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_OUT(v)            \
                out_dword(HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_ADDR,v)
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_ADDR,m,v,HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_IN)
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_BMSK                                                          0x1
#define HWIO_TCSR_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_GCC_PCIE_0_CLKREF_EN__PCIE_ENABLE_SHFT                                                            0

#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_ADDR                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x15104)
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_PHYS                                                                                 (TCSR_TCSR_REGS_REG_BASE_PHYS + 0x15104)
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_OFFS                                                                                 (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x15104)
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_RMSK                                                                                        0x1
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_POR                                                                                  0x00000000
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_POR_RMSK                                                                             0xffffffff
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_ATTR                                                                                              0x3
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_IN                    \
                in_dword(HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_ADDR)
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_INM(m)            \
                in_dword_masked(HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_ADDR, m)
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_OUT(v)            \
                out_dword(HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_ADDR,v)
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_ADDR,m,v,HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_IN)
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_BMSK                                                  0x1
#define HWIO_TCSR_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_GCC_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE_SHFT                                                    0

#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_ADDR                                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x15108)
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_PHYS                                                                                       (TCSR_TCSR_REGS_REG_BASE_PHYS + 0x15108)
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_OFFS                                                                                       (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x15108)
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_RMSK                                                                                              0x1
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_POR                                                                                        0x00000000
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_POR_RMSK                                                                                   0xffffffff
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_ATTR                                                                                                    0x3
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_IN                    \
                in_dword(HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_ADDR)
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_INM(m)            \
                in_dword_masked(HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_ADDR, m)
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_OUT(v)            \
                out_dword(HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_ADDR,v)
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_ADDR,m,v,HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_IN)
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_GCC_USB3_CLKREF_EN__USB3_ENABLE_BMSK                                                              0x1
#define HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_GCC_USB3_CLKREF_EN__USB3_ENABLE_SHFT                                                                0

#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_ADDR                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x1510c)
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_PHYS                                                                                     (TCSR_TCSR_REGS_REG_BASE_PHYS + 0x1510c)
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_OFFS                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x1510c)
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_RMSK                                                                                            0x1
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_POR                                                                                      0x00000000
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_POR_RMSK                                                                                 0xffffffff
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_ATTR                                                                                                  0x3
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_IN                    \
                in_dword(HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_ADDR)
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_INM(m)            \
                in_dword_masked(HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_ADDR, m)
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_OUT(v)            \
                out_dword(HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_ADDR,v)
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_ADDR,m,v,HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_IN)
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_BMSK                                                          0x1
#define HWIO_TCSR_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_GCC_QLINK_CLKREF_EN__QLINK_ENABLE_SHFT                                                            0

#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_ADDR                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x15110)
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_PHYS                                                                                         (TCSR_TCSR_REGS_REG_BASE_PHYS + 0x15110)
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_OFFS                                                                                         (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x15110)
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_RMSK                                                                                                0x1
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_POR                                                                                          0x00000000
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_POR_RMSK                                                                                     0xffffffff
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_ATTR                                                                                                      0x3
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_IN                    \
                in_dword(HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_ADDR)
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_INM(m)            \
                in_dword_masked(HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_ADDR, m)
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_OUT(v)            \
                out_dword(HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_ADDR,v)
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_ADDR,m,v,HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_IN)
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_GCC_UFS_CLKREF_EN__UFS_ENABLE_BMSK                                                                  0x1
#define HWIO_TCSR_GCC_UFS_CLKREF_EN__UFS_ENABLE_GCC_UFS_CLKREF_EN__UFS_ENABLE_SHFT                                                                    0

#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_ADDR                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x15114)
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_PHYS                                                                                     (TCSR_TCSR_REGS_REG_BASE_PHYS + 0x15114)
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_OFFS                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x15114)
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_RMSK                                                                                            0x1
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_POR                                                                                      0x00000000
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_POR_RMSK                                                                                 0xffffffff
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_ATTR                                                                                                  0x3
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_IN                    \
                in_dword(HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_ADDR)
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_INM(m)            \
                in_dword_masked(HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_ADDR, m)
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_OUT(v)            \
                out_dword(HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_ADDR,v)
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_ADDR,m,v,HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_IN)
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_BMSK                                                          0x1
#define HWIO_TCSR_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_GCC_PCIE_1_CLKREF_EN__PCIE_ENABLE_SHFT                                                            0

#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_ADDR                                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x15118)
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_PHYS                                                                                       (TCSR_TCSR_REGS_REG_BASE_PHYS + 0x15118)
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_OFFS                                                                                       (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x15118)
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_RMSK                                                                                              0x1
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_POR                                                                                        0x00000000
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_POR_RMSK                                                                                   0xffffffff
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_ATTR                                                                                                    0x3
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_IN                    \
                in_dword(HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_ADDR)
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_INM(m)            \
                in_dword_masked(HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_ADDR, m)
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_OUT(v)            \
                out_dword(HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_ADDR,v)
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_ADDR,m,v,HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_IN)
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_GCC_USB2_CLKREF_EN__USB2_ENABLE_BMSK                                                              0x1
#define HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_GCC_USB2_CLKREF_EN__USB2_ENABLE_SHFT                                                                0

#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_ADDR                                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x1511c)
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_PHYS                                                                                   (TCSR_TCSR_REGS_REG_BASE_PHYS + 0x1511c)
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_OFFS                                                                                   (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x1511c)
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_RMSK                                                                                          0x1
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_POR                                                                                    0x00000001
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_POR_RMSK                                                                               0xffffffff
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_ATTR                                                                                                0x3
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_IN                    \
                in_dword(HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_ADDR)
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_INM(m)            \
                in_dword_masked(HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_ADDR, m)
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_OUT(v)            \
                out_dword(HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_ADDR,v)
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_ADDR,m,v,HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_IN)
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_BMSK                                                      0x1
#define HWIO_TCSR_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_GCC_CXO_REFGEN_BIAS_SEL__SEL_REFGEN_SHFT                                                        0


#endif /* __HALGCCUSB_H__ */
