#ifndef __MSMHWIOXREG_DUT0_H__
#define __MSMHWIOXREG_DUT0_H__
/*
===========================================================================
*/
/**
  @file msmhwioxreg_dut0.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following bases:
    .*

  'Exclude' filters applied: RESERVED 

  Generation parameters: 
  { 'bases': ['.*'],
    'explicit-addressing': True,
    'filename': 'msmhwioxreg_dut0.h',
    'filter-exclude': ['RESERVED'],
    'ignore-prefixes': False,
    'output-attrs': True,
    'output-fvals': True,
    'output-offsets': True,
    'output-phys': True,
    'output-resets': True,
    'rmsk-input': False,
    'shadow-filename': 'msmxshadow_dut0.h'}

  Attribute definitions for the HWIO_*_ATTR macros are as follows:
    0x0: Command register
    0x1: Read-Only
    0x2: Write-Only
    0x3: Read/Write
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

  Baseline: cio_1.0_2020_04_23_stobia_HIA_teardown_test
  Date: 2020-04-23T04:23:23-07:00
  

  ===========================================================================
*/
#include <HALhwio.h>
#include "usb4_hwio.h"    // required for in_dword, out_dword only

// TODO: AC add Usb4Log

/*----------------------------------------------------------------------------
 * MODULE: GE_DUT_USER_REGS
 *--------------------------------------------------------------------------*/

#define GE_DUT_USER_REGS_REG_BASE                                                              (DUT0_BASE      + 0x01f80000)
#define GE_DUT_USER_REGS_REG_BASE_SIZE                                                         0x8000
#define GE_DUT_USER_REGS_REG_BASE_USED                                                         0x1c0
#define GE_DUT_USER_REGS_REG_BASE_PHYS                                                         (DUT0_BASE_PHYS + 0x01f80000)
#define GE_DUT_USER_REGS_REG_BASE_OFFS                                                         0x01f80000

#define HWIO_GE_DUT_VERSION_ADDR(x)                                                            ((x) + 0x00000000)
#define HWIO_GE_DUT_VERSION_PHYS(x)                                                            ((x) + 0x00000000)
#define HWIO_GE_DUT_VERSION_OFFS                                                               (0x00000000)
#define HWIO_GE_DUT_VERSION_RMSK                                                               0xffffffff
#define HWIO_GE_DUT_VERSION_POR                                                                0x00000000
#define HWIO_GE_DUT_VERSION_POR_RMSK                                                           0xffffffff
#define HWIO_GE_DUT_VERSION_ATTR                                                                      0x1
#define HWIO_GE_DUT_VERSION_IN(x)      \
        in_dword(HWIO_GE_DUT_VERSION_ADDR(x))
#define HWIO_GE_DUT_VERSION_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_VERSION_ADDR(x), m)
#define HWIO_GE_DUT_VERSION_SETUP_BMSK                                                         0xff000000
#define HWIO_GE_DUT_VERSION_SETUP_SHFT                                                               0x18
#define HWIO_GE_DUT_VERSION_MAJOR_BMSK                                                           0xff0000
#define HWIO_GE_DUT_VERSION_MAJOR_SHFT                                                               0x10
#define HWIO_GE_DUT_VERSION_MINOR_BMSK                                                             0xfff0
#define HWIO_GE_DUT_VERSION_MINOR_SHFT                                                                0x4
#define HWIO_GE_DUT_VERSION_STEP_BMSK                                                                 0xf
#define HWIO_GE_DUT_VERSION_STEP_SHFT                                                                 0x0

#define HWIO_GE_DUT_RESET_REG_ADDR(x)                                                          ((x) + 0x00000004)
#define HWIO_GE_DUT_RESET_REG_PHYS(x)                                                          ((x) + 0x00000004)
#define HWIO_GE_DUT_RESET_REG_OFFS                                                             (0x00000004)
#define HWIO_GE_DUT_RESET_REG_RMSK                                                                 0x3fff
#define HWIO_GE_DUT_RESET_REG_POR                                                              0x00000000
#define HWIO_GE_DUT_RESET_REG_POR_RMSK                                                         0xffffffff
#define HWIO_GE_DUT_RESET_REG_ATTR                                                                    0x3
#define HWIO_GE_DUT_RESET_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_RESET_REG_ADDR(x))
#define HWIO_GE_DUT_RESET_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_RESET_REG_ADDR(x), m)
#define HWIO_GE_DUT_RESET_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_RESET_REG_ADDR(x),v)
#define HWIO_GE_DUT_RESET_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_RESET_REG_ADDR(x),m,v,HWIO_GE_DUT_RESET_REG_IN(x))
#define HWIO_GE_DUT_RESET_REG_USB4_PHY_FLL_ARES_BMSK                                               0x2000
#define HWIO_GE_DUT_RESET_REG_USB4_PHY_FLL_ARES_SHFT                                                  0xd
#define HWIO_GE_DUT_RESET_REG_USB4_CTRL_PIPE_ARES_BMSK                                             0x1000
#define HWIO_GE_DUT_RESET_REG_USB4_CTRL_PIPE_ARES_SHFT                                                0xc
#define HWIO_GE_DUT_RESET_REG_USB4_USB_PIPE_ARES_BMSK                                               0x800
#define HWIO_GE_DUT_RESET_REG_USB4_USB_PIPE_ARES_SHFT                                                 0xb
#define HWIO_GE_DUT_RESET_REG_USB4_PCIE_PIPE_ARES_BMSK                                              0x400
#define HWIO_GE_DUT_RESET_REG_USB4_PCIE_PIPE_ARES_SHFT                                                0xa
#define HWIO_GE_DUT_RESET_REG_DP_PRLL_ARES_BMSK                                                     0x200
#define HWIO_GE_DUT_RESET_REG_DP_PRLL_ARES_SHFT                                                       0x9
#define HWIO_GE_DUT_RESET_REG_USB4_TMU_ARES_BMSK                                                    0x100
#define HWIO_GE_DUT_RESET_REG_USB4_TMU_ARES_SHFT                                                      0x8
#define HWIO_GE_DUT_RESET_REG_USB4_DP_PCLK_ARES_BMSK                                                 0x80
#define HWIO_GE_DUT_RESET_REG_USB4_DP_PCLK_ARES_SHFT                                                  0x7
#define HWIO_GE_DUT_RESET_REG_USB4_PDPHY_AHB_RESET_BMSK                                              0x40
#define HWIO_GE_DUT_RESET_REG_USB4_PDPHY_AHB_RESET_SHFT                                               0x6
#define HWIO_GE_DUT_RESET_REG_USB4_HIA_MSTR_RESET_BMSK                                               0x20
#define HWIO_GE_DUT_RESET_REG_USB4_HIA_MSTR_RESET_SHFT                                                0x5
#define HWIO_GE_DUT_RESET_REG_USB4_SYS_RESET_BMSK                                                    0x10
#define HWIO_GE_DUT_RESET_REG_USB4_SYS_RESET_SHFT                                                     0x4
#define HWIO_GE_DUT_RESET_REG_USB4_RX0_RESET_BMSK                                                     0x8
#define HWIO_GE_DUT_RESET_REG_USB4_RX0_RESET_SHFT                                                     0x3
#define HWIO_GE_DUT_RESET_REG_USB4_RX1_RESET_BMSK                                                     0x4
#define HWIO_GE_DUT_RESET_REG_USB4_RX1_RESET_SHFT                                                     0x2
#define HWIO_GE_DUT_RESET_REG_USB4_AHB_RESET_BMSK                                                     0x2
#define HWIO_GE_DUT_RESET_REG_USB4_AHB_RESET_SHFT                                                     0x1
#define HWIO_GE_DUT_RESET_REG_USB4_SB_RESET_BMSK                                                      0x1
#define HWIO_GE_DUT_RESET_REG_USB4_SB_RESET_SHFT                                                      0x0

#define HWIO_GE_DUT_LO_IRQ_TEST_REG_ADDR(x)                                                    ((x) + 0x00000008)
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_PHYS(x)                                                    ((x) + 0x00000008)
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_OFFS                                                       (0x00000008)
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_RMSK                                                       0xffffffff
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_POR                                                        0x00000000
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_POR_RMSK                                                   0xffffffff
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_ATTR                                                              0x3
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_LO_IRQ_TEST_REG_ADDR(x))
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_LO_IRQ_TEST_REG_ADDR(x), m)
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_LO_IRQ_TEST_REG_ADDR(x),v)
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_LO_IRQ_TEST_REG_ADDR(x),m,v,HWIO_GE_DUT_LO_IRQ_TEST_REG_IN(x))
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_IRQ_LSB_BMSK                                               0xffffffff
#define HWIO_GE_DUT_LO_IRQ_TEST_REG_IRQ_LSB_SHFT                                                      0x0

#define HWIO_GE_DUT_HI_IRQ_TEST_REG_ADDR(x)                                                    ((x) + 0x0000000c)
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_PHYS(x)                                                    ((x) + 0x0000000c)
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_OFFS                                                       (0x0000000c)
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_RMSK                                                       0xffffffff
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_POR                                                        0x00000000
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_POR_RMSK                                                   0xffffffff
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_ATTR                                                              0x3
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_HI_IRQ_TEST_REG_ADDR(x))
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_HI_IRQ_TEST_REG_ADDR(x), m)
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_HI_IRQ_TEST_REG_ADDR(x),v)
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_HI_IRQ_TEST_REG_ADDR(x),m,v,HWIO_GE_DUT_HI_IRQ_TEST_REG_IN(x))
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_IRQ_MSB_BMSK                                               0xffffffff
#define HWIO_GE_DUT_HI_IRQ_TEST_REG_IRQ_MSB_SHFT                                                      0x0

#define HWIO_GE_DUT_CLK_STATUS_REG_ADDR(x)                                                     ((x) + 0x00000010)
#define HWIO_GE_DUT_CLK_STATUS_REG_PHYS(x)                                                     ((x) + 0x00000010)
#define HWIO_GE_DUT_CLK_STATUS_REG_OFFS                                                        (0x00000010)
#define HWIO_GE_DUT_CLK_STATUS_REG_RMSK                                                           0xfffff
#define HWIO_GE_DUT_CLK_STATUS_REG_POR                                                         0x00000000
#define HWIO_GE_DUT_CLK_STATUS_REG_POR_RMSK                                                    0xffffffff
#define HWIO_GE_DUT_CLK_STATUS_REG_ATTR                                                               0x1
#define HWIO_GE_DUT_CLK_STATUS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_CLK_STATUS_REG_ADDR(x))
#define HWIO_GE_DUT_CLK_STATUS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_CLK_STATUS_REG_ADDR(x), m)
#define HWIO_GE_DUT_CLK_STATUS_REG_FREQUENCY_IN_KHZ_BMSK                                          0xfffff
#define HWIO_GE_DUT_CLK_STATUS_REG_FREQUENCY_IN_KHZ_SHFT                                              0x0

#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_ADDR(x)                                                 ((x) + 0x00000014)
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_PHYS(x)                                                 ((x) + 0x00000014)
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_OFFS                                                    (0x00000014)
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_RMSK                                                           0xf
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_POR                                                     0x00000000
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_POR_RMSK                                                0xffffffff
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_ATTR                                                           0x3
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_CLK_STATUS_SEL_REG_ADDR(x))
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_CLK_STATUS_SEL_REG_ADDR(x), m)
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_CLK_STATUS_SEL_REG_ADDR(x),v)
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_CLK_STATUS_SEL_REG_ADDR(x),m,v,HWIO_GE_DUT_CLK_STATUS_SEL_REG_IN(x))
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_BMSK                                                   0xf
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_SHFT                                                   0x0
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLK0_FVAL                                              0x0
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLK1_FVAL                                              0x1
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLK2_FVAL                                              0x2
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLK3_FVAL                                              0x3
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLK4_FVAL                                              0x4
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLK5_FVAL                                              0x5
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLK6_FVAL                                              0x6
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLK7_FVAL                                              0x7
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLK8_FVAL                                              0x8
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLK9_FVAL                                              0x9
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLKA_FVAL                                              0xa
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLKB_FVAL                                              0xb
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLKC_FVAL                                              0xc
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLKD_FVAL                                              0xd
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_CLK_NUM_CLKE_FVAL                                              0xe

#define HWIO_GE_DUT_USB4_CTRL_REG_ADDR(x)                                                      ((x) + 0x00000018)
#define HWIO_GE_DUT_USB4_CTRL_REG_PHYS(x)                                                      ((x) + 0x00000018)
#define HWIO_GE_DUT_USB4_CTRL_REG_OFFS                                                         (0x00000018)
#define HWIO_GE_DUT_USB4_CTRL_REG_RMSK                                                             0x3ff0
#define HWIO_GE_DUT_USB4_CTRL_REG_POR                                                          0x00001880
#define HWIO_GE_DUT_USB4_CTRL_REG_POR_RMSK                                                     0xffffffff
#define HWIO_GE_DUT_USB4_CTRL_REG_ATTR                                                                0x3
#define HWIO_GE_DUT_USB4_CTRL_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_USB4_CTRL_REG_ADDR(x))
#define HWIO_GE_DUT_USB4_CTRL_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_USB4_CTRL_REG_ADDR(x), m)
#define HWIO_GE_DUT_USB4_CTRL_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_USB4_CTRL_REG_ADDR(x),v)
#define HWIO_GE_DUT_USB4_CTRL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_USB4_CTRL_REG_ADDR(x),m,v,HWIO_GE_DUT_USB4_CTRL_REG_IN(x))
#define HWIO_GE_DUT_USB4_CTRL_REG_USB31_CTRL_MODE_BMSK                                             0x2000
#define HWIO_GE_DUT_USB4_CTRL_REG_USB31_CTRL_MODE_SHFT                                                0xd
#define HWIO_GE_DUT_USB4_CTRL_REG_SBTX_LVL_SHFTR_DIR_BMSK                                          0x1000
#define HWIO_GE_DUT_USB4_CTRL_REG_SBTX_LVL_SHFTR_DIR_SHFT                                             0xc
#define HWIO_GE_DUT_USB4_CTRL_REG_SBTX_GPIO_FUNC_SEL_BMSK                                           0x800
#define HWIO_GE_DUT_USB4_CTRL_REG_SBTX_GPIO_FUNC_SEL_SHFT                                             0xb
#define HWIO_GE_DUT_USB4_CTRL_REG_SBTX_GPIO_OE_BMSK                                                 0x400
#define HWIO_GE_DUT_USB4_CTRL_REG_SBTX_GPIO_OE_SHFT                                                   0xa
#define HWIO_GE_DUT_USB4_CTRL_REG_SBTX_GPIO_OUT_BMSK                                                0x200
#define HWIO_GE_DUT_USB4_CTRL_REG_SBTX_GPIO_OUT_SHFT                                                  0x9
#define HWIO_GE_DUT_USB4_CTRL_REG_SBTX_GPIO_IN_BMSK                                                 0x100
#define HWIO_GE_DUT_USB4_CTRL_REG_SBTX_GPIO_IN_SHFT                                                   0x8
#define HWIO_GE_DUT_USB4_CTRL_REG_SBRX_GPIO_FUNC_SEL_BMSK                                            0x80
#define HWIO_GE_DUT_USB4_CTRL_REG_SBRX_GPIO_FUNC_SEL_SHFT                                             0x7
#define HWIO_GE_DUT_USB4_CTRL_REG_SBRX_GPIO_OE_BMSK                                                  0x40
#define HWIO_GE_DUT_USB4_CTRL_REG_SBRX_GPIO_OE_SHFT                                                   0x6
#define HWIO_GE_DUT_USB4_CTRL_REG_SBRX_GPIO_OUT_BMSK                                                 0x20
#define HWIO_GE_DUT_USB4_CTRL_REG_SBRX_GPIO_OUT_SHFT                                                  0x5
#define HWIO_GE_DUT_USB4_CTRL_REG_SBRX_GPIO_IN_BMSK                                                  0x10
#define HWIO_GE_DUT_USB4_CTRL_REG_SBRX_GPIO_IN_SHFT                                                   0x4

#define HWIO_GE_DUT_USB4_LAST_ADDR_REG_ADDR(x)                                                 ((x) + 0x0000001c)
#define HWIO_GE_DUT_USB4_LAST_ADDR_REG_PHYS(x)                                                 ((x) + 0x0000001c)
#define HWIO_GE_DUT_USB4_LAST_ADDR_REG_OFFS                                                    (0x0000001c)
#define HWIO_GE_DUT_USB4_LAST_ADDR_REG_RMSK                                                          0xff
#define HWIO_GE_DUT_USB4_LAST_ADDR_REG_POR                                                     0x00000000
#define HWIO_GE_DUT_USB4_LAST_ADDR_REG_POR_RMSK                                                0xffffffff
#define HWIO_GE_DUT_USB4_LAST_ADDR_REG_ATTR                                                           0x1
#define HWIO_GE_DUT_USB4_LAST_ADDR_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_USB4_LAST_ADDR_REG_ADDR(x))
#define HWIO_GE_DUT_USB4_LAST_ADDR_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_USB4_LAST_ADDR_REG_ADDR(x), m)
#define HWIO_GE_DUT_USB4_LAST_ADDR_REG_TOP_BITS_BMSK                                                 0xff
#define HWIO_GE_DUT_USB4_LAST_ADDR_REG_TOP_BITS_SHFT                                                  0x0

#define HWIO_GE_DUT_USB4_QTIMER_LSB_REG_ADDR(x)                                                ((x) + 0x00000020)
#define HWIO_GE_DUT_USB4_QTIMER_LSB_REG_PHYS(x)                                                ((x) + 0x00000020)
#define HWIO_GE_DUT_USB4_QTIMER_LSB_REG_OFFS                                                   (0x00000020)
#define HWIO_GE_DUT_USB4_QTIMER_LSB_REG_RMSK                                                   0xffffffff
#define HWIO_GE_DUT_USB4_QTIMER_LSB_REG_POR                                                    0x00000000
#define HWIO_GE_DUT_USB4_QTIMER_LSB_REG_POR_RMSK                                               0xffffffff
#define HWIO_GE_DUT_USB4_QTIMER_LSB_REG_ATTR                                                          0x1
#define HWIO_GE_DUT_USB4_QTIMER_LSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_USB4_QTIMER_LSB_REG_ADDR(x))
#define HWIO_GE_DUT_USB4_QTIMER_LSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_USB4_QTIMER_LSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_USB4_QTIMER_LSB_REG_GRAY_LSB_BMSK                                          0xffffffff
#define HWIO_GE_DUT_USB4_QTIMER_LSB_REG_GRAY_LSB_SHFT                                                 0x0

#define HWIO_GE_DUT_USB4_QTIMER_MSB_REG_ADDR(x)                                                ((x) + 0x00000024)
#define HWIO_GE_DUT_USB4_QTIMER_MSB_REG_PHYS(x)                                                ((x) + 0x00000024)
#define HWIO_GE_DUT_USB4_QTIMER_MSB_REG_OFFS                                                   (0x00000024)
#define HWIO_GE_DUT_USB4_QTIMER_MSB_REG_RMSK                                                     0xffffff
#define HWIO_GE_DUT_USB4_QTIMER_MSB_REG_POR                                                    0x00000000
#define HWIO_GE_DUT_USB4_QTIMER_MSB_REG_POR_RMSK                                               0xffffffff
#define HWIO_GE_DUT_USB4_QTIMER_MSB_REG_ATTR                                                          0x1
#define HWIO_GE_DUT_USB4_QTIMER_MSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_USB4_QTIMER_MSB_REG_ADDR(x))
#define HWIO_GE_DUT_USB4_QTIMER_MSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_USB4_QTIMER_MSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_USB4_QTIMER_MSB_REG_GRAY_MSB_BMSK                                            0xffffff
#define HWIO_GE_DUT_USB4_QTIMER_MSB_REG_GRAY_MSB_SHFT                                                 0x0

#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_ADDR(x)                                              ((x) + 0x00000050)
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_PHYS(x)                                              ((x) + 0x00000050)
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_OFFS                                                 (0x00000050)
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_RMSK                                                      0x111
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_POR                                                  0x00000000
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_POR_RMSK                                             0xffffffff
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_ATTR                                                        0x3
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_ADDR(x))
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_ADDR(x), m)
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_ADDR(x),v)
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_ADDR(x),m,v,HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_IN(x))
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_EX_RESET_BMSK                                             0x100
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_EX_RESET_SHFT                                               0x8
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_GEN_MODE_BMSK                                              0x10
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_GEN_MODE_SHFT                                               0x4
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_COMP_MODE_BMSK                                              0x1
#define HWIO_GE_DUT_L0_SERDES_EX_CTRL_REG_COMP_MODE_SHFT                                              0x0

#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_ADDR(x)                                               ((x) + 0x00000054)
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_PHYS(x)                                               ((x) + 0x00000054)
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_OFFS                                                  (0x00000054)
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_RMSK                                                  0x11000000
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_POR                                                   0x00000000
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_POR_RMSK                                              0xffffffff
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_ATTR                                                         0x1
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L0_SERDES_EX_STS_REG_ADDR(x))
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L0_SERDES_EX_STS_REG_ADDR(x), m)
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_COMP_DATA_ERROR_BMSK                                  0x10000000
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_COMP_DATA_ERROR_SHFT                                        0x1c
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_COMP_DATA_LOCK_BMSK                                    0x1000000
#define HWIO_GE_DUT_L0_SERDES_EX_STS_REG_COMP_DATA_LOCK_SHFT                                         0x18

#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_ADDR(x)                                      ((x) + 0x00000058)
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_PHYS(x)                                      ((x) + 0x00000058)
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_OFFS                                         (0x00000058)
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_RMSK                                         0x7fffffff
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_POR                                          0x00000000
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_POR_RMSK                                     0xffffffff
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_ATTR                                                0x3
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_ADDR(x))
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_ADDR(x),v)
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_ADDR(x),m,v,HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_IN(x))
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_GEN_SEED_MSB_BMSK                            0x7fffffff
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_MSB_REG_GEN_SEED_MSB_SHFT                                   0x0

#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_ADDR(x)                                      ((x) + 0x0000005c)
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_PHYS(x)                                      ((x) + 0x0000005c)
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_OFFS                                         (0x0000005c)
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_RMSK                                         0xffffffff
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_POR                                          0x00000000
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_POR_RMSK                                     0xffffffff
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_ATTR                                                0x3
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_ADDR(x))
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_ADDR(x),v)
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_ADDR(x),m,v,HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_IN(x))
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_GEN_SEED_LSB_BMSK                            0xffffffff
#define HWIO_GE_DUT_L0_SERDES_EX_GEN_SEED_LSB_REG_GEN_SEED_LSB_SHFT                                   0x0

#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_ADDR(x)                                     ((x) + 0x00000060)
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_PHYS(x)                                     ((x) + 0x00000060)
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_OFFS                                        (0x00000060)
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_RMSK                                        0x7fffffff
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_POR                                         0x00000000
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_POR_RMSK                                    0xffffffff
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_ATTR                                               0x3
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_ADDR(x))
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_ADDR(x),v)
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_ADDR(x),m,v,HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_IN(x))
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_COMP_SEED_MSB_BMSK                          0x7fffffff
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_MSB_REG_COMP_SEED_MSB_SHFT                                 0x0

#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_ADDR(x)                                     ((x) + 0x00000064)
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_PHYS(x)                                     ((x) + 0x00000064)
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_OFFS                                        (0x00000064)
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_RMSK                                        0xffffffff
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_POR                                         0x00000000
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_POR_RMSK                                    0xffffffff
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_ATTR                                               0x3
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_ADDR(x))
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_ADDR(x),v)
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_ADDR(x),m,v,HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_IN(x))
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_COMP_SEED_LSB_BMSK                          0xffffffff
#define HWIO_GE_DUT_L0_SERDES_EX_COMP_SEED_LSB_REG_COMP_SEED_LSB_SHFT                                 0x0

#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_ADDR(x)                                              ((x) + 0x00000070)
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_PHYS(x)                                              ((x) + 0x00000070)
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_OFFS                                                 (0x00000070)
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_RMSK                                                      0x111
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_POR                                                  0x00000000
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_POR_RMSK                                             0xffffffff
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_ATTR                                                        0x3
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_ADDR(x))
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_ADDR(x), m)
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_ADDR(x),v)
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_ADDR(x),m,v,HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_IN(x))
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_EX_RESET_BMSK                                             0x100
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_EX_RESET_SHFT                                               0x8
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_GEN_MODE_BMSK                                              0x10
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_GEN_MODE_SHFT                                               0x4
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_COMP_MODE_BMSK                                              0x1
#define HWIO_GE_DUT_L1_SERDES_EX_CTRL_REG_COMP_MODE_SHFT                                              0x0

#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_ADDR(x)                                               ((x) + 0x00000074)
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_PHYS(x)                                               ((x) + 0x00000074)
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_OFFS                                                  (0x00000074)
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_RMSK                                                  0x11000000
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_POR                                                   0x00000000
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_POR_RMSK                                              0xffffffff
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_ATTR                                                         0x1
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L1_SERDES_EX_STS_REG_ADDR(x))
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L1_SERDES_EX_STS_REG_ADDR(x), m)
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_COMP_DATA_ERROR_BMSK                                  0x10000000
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_COMP_DATA_ERROR_SHFT                                        0x1c
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_COMP_DATA_LOCK_BMSK                                    0x1000000
#define HWIO_GE_DUT_L1_SERDES_EX_STS_REG_COMP_DATA_LOCK_SHFT                                         0x18

#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_ADDR(x)                                      ((x) + 0x00000078)
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_PHYS(x)                                      ((x) + 0x00000078)
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_OFFS                                         (0x00000078)
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_RMSK                                         0x7fffffff
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_POR                                          0x00000000
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_POR_RMSK                                     0xffffffff
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_ATTR                                                0x3
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_ADDR(x))
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_ADDR(x),v)
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_ADDR(x),m,v,HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_IN(x))
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_GEN_SEED_MSB_BMSK                            0x7fffffff
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_MSB_REG_GEN_SEED_MSB_SHFT                                   0x0

#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_ADDR(x)                                      ((x) + 0x0000007c)
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_PHYS(x)                                      ((x) + 0x0000007c)
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_OFFS                                         (0x0000007c)
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_RMSK                                         0xffffffff
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_POR                                          0x00000000
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_POR_RMSK                                     0xffffffff
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_ATTR                                                0x3
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_ADDR(x))
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_ADDR(x),v)
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_ADDR(x),m,v,HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_IN(x))
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_GEN_SEED_LSB_BMSK                            0xffffffff
#define HWIO_GE_DUT_L1_SERDES_EX_GEN_SEED_LSB_REG_GEN_SEED_LSB_SHFT                                   0x0

#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_ADDR(x)                                     ((x) + 0x00000080)
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_PHYS(x)                                     ((x) + 0x00000080)
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_OFFS                                        (0x00000080)
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_RMSK                                        0x7fffffff
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_POR                                         0x00000000
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_POR_RMSK                                    0xffffffff
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_ATTR                                               0x3
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_ADDR(x))
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_ADDR(x),v)
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_ADDR(x),m,v,HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_IN(x))
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_COMP_SEED_MSB_BMSK                          0x7fffffff
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_MSB_REG_COMP_SEED_MSB_SHFT                                 0x0

#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_ADDR(x)                                     ((x) + 0x00000084)
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_PHYS(x)                                     ((x) + 0x00000084)
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_OFFS                                        (0x00000084)
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_RMSK                                        0xffffffff
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_POR                                         0x00000000
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_POR_RMSK                                    0xffffffff
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_ATTR                                               0x3
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_ADDR(x))
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_ADDR(x),v)
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_ADDR(x),m,v,HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_IN(x))
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_COMP_SEED_LSB_BMSK                          0xffffffff
#define HWIO_GE_DUT_L1_SERDES_EX_COMP_SEED_LSB_REG_COMP_SEED_LSB_SHFT                                 0x0

#define HWIO_GE_DUT_PHY_CONTROL_REG_ADDR(x)                                                    ((x) + 0x00000090)
#define HWIO_GE_DUT_PHY_CONTROL_REG_PHYS(x)                                                    ((x) + 0x00000090)
#define HWIO_GE_DUT_PHY_CONTROL_REG_OFFS                                                       (0x00000090)
#define HWIO_GE_DUT_PHY_CONTROL_REG_RMSK                                                       0x3fffffff
#define HWIO_GE_DUT_PHY_CONTROL_REG_POR                                                        0x20000012
#define HWIO_GE_DUT_PHY_CONTROL_REG_POR_RMSK                                                   0xffffffff
#define HWIO_GE_DUT_PHY_CONTROL_REG_ATTR                                                              0x3
#define HWIO_GE_DUT_PHY_CONTROL_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PHY_CONTROL_REG_ADDR(x))
#define HWIO_GE_DUT_PHY_CONTROL_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PHY_CONTROL_REG_ADDR(x), m)
#define HWIO_GE_DUT_PHY_CONTROL_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_PHY_CONTROL_REG_ADDR(x),v)
#define HWIO_GE_DUT_PHY_CONTROL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_PHY_CONTROL_REG_ADDR(x),m,v,HWIO_GE_DUT_PHY_CONTROL_REG_IN(x))
#define HWIO_GE_DUT_PHY_CONTROL_REG_PHY_RESET_BMSK                                             0x20000000
#define HWIO_GE_DUT_PHY_CONTROL_REG_PHY_RESET_SHFT                                                   0x1d
#define HWIO_GE_DUT_PHY_CONTROL_REG_LOOPBACK_MODE_BMSK                                         0x1c000000
#define HWIO_GE_DUT_PHY_CONTROL_REG_LOOPBACK_MODE_SHFT                                               0x1a
#define HWIO_GE_DUT_PHY_CONTROL_REG_TX_DATAPATH_RESET_BMSK                                      0x2000000
#define HWIO_GE_DUT_PHY_CONTROL_REG_TX_DATAPATH_RESET_SHFT                                           0x19
#define HWIO_GE_DUT_PHY_CONTROL_REG_RX_DATAPATH_RESET_BMSK                                      0x1000000
#define HWIO_GE_DUT_PHY_CONTROL_REG_RX_DATAPATH_RESET_SHFT                                           0x18
#define HWIO_GE_DUT_PHY_CONTROL_REG_RX_CDR_RESET_BMSK                                            0x800000
#define HWIO_GE_DUT_PHY_CONTROL_REG_RX_CDR_RESET_SHFT                                                0x17
#define HWIO_GE_DUT_PHY_CONTROL_REG_RX_CDR_HOLD_BMSK                                             0x400000
#define HWIO_GE_DUT_PHY_CONTROL_REG_RX_CDR_HOLD_SHFT                                                 0x16
#define HWIO_GE_DUT_PHY_CONTROL_REG_RX_CDR_OVRDEN_BMSK                                           0x200000
#define HWIO_GE_DUT_PHY_CONTROL_REG_RX_CDR_OVRDEN_SHFT                                               0x15
#define HWIO_GE_DUT_PHY_CONTROL_REG_TXELECIDLE_MUX_BMSK                                          0x100000
#define HWIO_GE_DUT_PHY_CONTROL_REG_TXELECIDLE_MUX_SHFT                                              0x14
#define HWIO_GE_DUT_PHY_CONTROL_REG_TXELECIDLE_BMSK                                               0xc0000
#define HWIO_GE_DUT_PHY_CONTROL_REG_TXELECIDLE_SHFT                                                  0x12
#define HWIO_GE_DUT_PHY_CONTROL_REG_TXDETECTRX_MUX_BMSK                                           0x20000
#define HWIO_GE_DUT_PHY_CONTROL_REG_TXDETECTRX_MUX_SHFT                                              0x11
#define HWIO_GE_DUT_PHY_CONTROL_REG_TXDETECTRX_BMSK                                               0x18000
#define HWIO_GE_DUT_PHY_CONTROL_REG_TXDETECTRX_SHFT                                                   0xf
#define HWIO_GE_DUT_PHY_CONTROL_REG_POWERDOWN_MUX_BMSK                                             0x4000
#define HWIO_GE_DUT_PHY_CONTROL_REG_POWERDOWN_MUX_SHFT                                                0xe
#define HWIO_GE_DUT_PHY_CONTROL_REG_POWERDOWN_BMSK                                                 0x3800
#define HWIO_GE_DUT_PHY_CONTROL_REG_POWERDOWN_SHFT                                                    0xb
#define HWIO_GE_DUT_PHY_CONTROL_REG_TBT3_MODE_BMSK                                                  0x400
#define HWIO_GE_DUT_PHY_CONTROL_REG_TBT3_MODE_SHFT                                                    0xa
#define HWIO_GE_DUT_PHY_CONTROL_REG_LFPS_TX_RESET_BMSK                                              0x300
#define HWIO_GE_DUT_PHY_CONTROL_REG_LFPS_TX_RESET_SHFT                                                0x8
#define HWIO_GE_DUT_PHY_CONTROL_REG_LFPS_RX_RESET_BMSK                                               0xc0
#define HWIO_GE_DUT_PHY_CONTROL_REG_LFPS_RX_RESET_SHFT                                                0x6
#define HWIO_GE_DUT_PHY_CONTROL_REG_LFPS_CNT_BMSK                                                    0x38
#define HWIO_GE_DUT_PHY_CONTROL_REG_LFPS_CNT_SHFT                                                     0x3
#define HWIO_GE_DUT_PHY_CONTROL_REG_LFPS_DET_CNT_BMSK                                                 0x7
#define HWIO_GE_DUT_PHY_CONTROL_REG_LFPS_DET_CNT_SHFT                                                 0x0

#define HWIO_GE_DUT_PHY_CONTROL2_REG_ADDR(x)                                                   ((x) + 0x00000094)
#define HWIO_GE_DUT_PHY_CONTROL2_REG_PHYS(x)                                                   ((x) + 0x00000094)
#define HWIO_GE_DUT_PHY_CONTROL2_REG_OFFS                                                      (0x00000094)
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RMSK                                                      0xcf33f707
#define HWIO_GE_DUT_PHY_CONTROL2_REG_POR                                                       0x00000701
#define HWIO_GE_DUT_PHY_CONTROL2_REG_POR_RMSK                                                  0xffffffff
#define HWIO_GE_DUT_PHY_CONTROL2_REG_ATTR                                                             0x3
#define HWIO_GE_DUT_PHY_CONTROL2_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PHY_CONTROL2_REG_ADDR(x))
#define HWIO_GE_DUT_PHY_CONTROL2_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PHY_CONTROL2_REG_ADDR(x), m)
#define HWIO_GE_DUT_PHY_CONTROL2_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_PHY_CONTROL2_REG_ADDR(x),v)
#define HWIO_GE_DUT_PHY_CONTROL2_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_PHY_CONTROL2_REG_ADDR(x),m,v,HWIO_GE_DUT_PHY_CONTROL2_REG_IN(x))
#define HWIO_GE_DUT_PHY_CONTROL2_REG_TXPRBSFORCEERR_BMSK                                       0xc0000000
#define HWIO_GE_DUT_PHY_CONTROL2_REG_TXPRBSFORCEERR_SHFT                                             0x1e
#define HWIO_GE_DUT_PHY_CONTROL2_REG_TXPRBSSEL_BMSK                                             0xf000000
#define HWIO_GE_DUT_PHY_CONTROL2_REG_TXPRBSSEL_SHFT                                                  0x18
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RXPRBSERR_BMSK                                              0x300000
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RXPRBSERR_SHFT                                                  0x14
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RXPRBSCNTRESET_BMSK                                          0x30000
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RXPRBSCNTRESET_SHFT                                             0x10
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RXPRBSSEL_BMSK                                                0xf000
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RXPRBSSEL_SHFT                                                   0xc
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RXVALID_MUX_BMSK                                               0x400
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RXVALID_MUX_SHFT                                                 0xa
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RXVALID_BMSK                                                   0x300
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RXVALID_SHFT                                                     0x8
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RATE_BMSK                                                        0x7
#define HWIO_GE_DUT_PHY_CONTROL2_REG_RATE_SHFT                                                        0x0

#define HWIO_GE_DUT_PHY_CONTROL3_REG_ADDR(x)                                                   ((x) + 0x00000098)
#define HWIO_GE_DUT_PHY_CONTROL3_REG_PHYS(x)                                                   ((x) + 0x00000098)
#define HWIO_GE_DUT_PHY_CONTROL3_REG_OFFS                                                      (0x00000098)
#define HWIO_GE_DUT_PHY_CONTROL3_REG_RMSK                                                       0xfffffff
#define HWIO_GE_DUT_PHY_CONTROL3_REG_POR                                                       0x0bb00000
#define HWIO_GE_DUT_PHY_CONTROL3_REG_POR_RMSK                                                  0xffffffff
#define HWIO_GE_DUT_PHY_CONTROL3_REG_ATTR                                                             0x3
#define HWIO_GE_DUT_PHY_CONTROL3_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PHY_CONTROL3_REG_ADDR(x))
#define HWIO_GE_DUT_PHY_CONTROL3_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PHY_CONTROL3_REG_ADDR(x), m)
#define HWIO_GE_DUT_PHY_CONTROL3_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_PHY_CONTROL3_REG_ADDR(x),v)
#define HWIO_GE_DUT_PHY_CONTROL3_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_PHY_CONTROL3_REG_ADDR(x),m,v,HWIO_GE_DUT_PHY_CONTROL3_REG_IN(x))
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXDIFFCTRL_L1_BMSK                                         0xf000000
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXDIFFCTRL_L1_SHFT                                              0x18
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXDIFFCTRL_L0_BMSK                                          0xf00000
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXDIFFCTRL_L0_SHFT                                              0x14
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXPRECURSOR_L1_BMSK                                          0xf8000
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXPRECURSOR_L1_SHFT                                              0xf
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXPRECURSOR_L0_BMSK                                           0x7c00
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXPRECURSOR_L0_SHFT                                              0xa
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXPOSTCURSOR_L1_BMSK                                           0x3e0
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXPOSTCURSOR_L1_SHFT                                             0x5
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXPOSTCURSOR_L0_BMSK                                            0x1f
#define HWIO_GE_DUT_PHY_CONTROL3_REG_TXPOSTCURSOR_L0_SHFT                                             0x0

#define HWIO_GE_DUT_PHY_STATUS_REG_ADDR(x)                                                     ((x) + 0x00000110)
#define HWIO_GE_DUT_PHY_STATUS_REG_PHYS(x)                                                     ((x) + 0x00000110)
#define HWIO_GE_DUT_PHY_STATUS_REG_OFFS                                                        (0x00000110)
#define HWIO_GE_DUT_PHY_STATUS_REG_RMSK                                                          0x1ff000
#define HWIO_GE_DUT_PHY_STATUS_REG_POR                                                         0x00000000
#define HWIO_GE_DUT_PHY_STATUS_REG_POR_RMSK                                                    0xffffffff
#define HWIO_GE_DUT_PHY_STATUS_REG_ATTR                                                               0x1
#define HWIO_GE_DUT_PHY_STATUS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PHY_STATUS_REG_ADDR(x))
#define HWIO_GE_DUT_PHY_STATUS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PHY_STATUS_REG_ADDR(x), m)
#define HWIO_GE_DUT_PHY_STATUS_REG_PHYSTATUS_BMSK                                                0x180000
#define HWIO_GE_DUT_PHY_STATUS_REG_PHYSTATUS_SHFT                                                    0x13
#define HWIO_GE_DUT_PHY_STATUS_REG_LFPS_RX_DETECT_BMSK                                            0x60000
#define HWIO_GE_DUT_PHY_STATUS_REG_LFPS_RX_DETECT_SHFT                                               0x11
#define HWIO_GE_DUT_PHY_STATUS_REG_RX_CDR_STABLE_BMSK                                             0x10000
#define HWIO_GE_DUT_PHY_STATUS_REG_RX_CDR_STABLE_SHFT                                                0x10
#define HWIO_GE_DUT_PHY_STATUS_REG_RX_CDR_LOCKED_BMSK                                              0xc000
#define HWIO_GE_DUT_PHY_STATUS_REG_RX_CDR_LOCKED_SHFT                                                 0xe
#define HWIO_GE_DUT_PHY_STATUS_REG_QPLL0_LOCKED_BMSK                                               0x2000
#define HWIO_GE_DUT_PHY_STATUS_REG_QPLL0_LOCKED_SHFT                                                  0xd
#define HWIO_GE_DUT_PHY_STATUS_REG_QPLL1_LOCKED_BMSK                                               0x1000
#define HWIO_GE_DUT_PHY_STATUS_REG_QPLL1_LOCKED_SHFT                                                  0xc

#define HWIO_GE_DUT_PE277_CTRL_STS_REG_ADDR(x)                                                 ((x) + 0x00000114)
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_PHYS(x)                                                 ((x) + 0x00000114)
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_OFFS                                                    (0x00000114)
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_RMSK                                                         0xfff
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_POR                                                     0x00000023
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_POR_RMSK                                                0xffffffff
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_ATTR                                                           0x3
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PE277_CTRL_STS_REG_ADDR(x))
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PE277_CTRL_STS_REG_ADDR(x), m)
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_PE277_CTRL_STS_REG_ADDR(x),v)
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_PE277_CTRL_STS_REG_ADDR(x),m,v,HWIO_GE_DUT_PE277_CTRL_STS_REG_IN(x))
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_MGT_FS_SEL_EN_BMSK                                           0x800
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_MGT_FS_SEL_EN_SHFT                                             0xb
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_SB_FROM_NEU_BMSK                                             0x400
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_SB_FROM_NEU_SHFT                                               0xa
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_TYPEC_SB_SWAP_BMSK                                           0x200
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_TYPEC_SB_SWAP_SHFT                                             0x9
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_SB_SWAP_BMSK                                                 0x100
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_SB_SWAP_SHFT                                                   0x8
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_MGT_FS_SEL_BMSK                                               0xe0
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_MGT_FS_SEL_SHFT                                                0x5
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_BRD_5V_SRC_GEN_EN_BMSK                                        0x10
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_BRD_5V_SRC_GEN_EN_SHFT                                         0x4
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_VBUS_SRC_SEL_BMSK                                              0x8
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_VBUS_SRC_SEL_SHFT                                              0x3
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_VBUS_EN_BMSK                                                   0x4
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_VBUS_EN_SHFT                                                   0x2
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_VBUS_5V_FAULT_N_BMSK                                           0x2
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_VBUS_5V_FAULT_N_SHFT                                           0x1
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_VBUS_20V_ACK_BMSK                                              0x1
#define HWIO_GE_DUT_PE277_CTRL_STS_REG_VBUS_20V_ACK_SHFT                                              0x0

#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_ADDR(x)                                            ((x) + 0x00000120)
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_PHYS(x)                                            ((x) + 0x00000120)
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_OFFS                                               (0x00000120)
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_RMSK                                               0xffffffff
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_POR                                                0x00000000
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_POR_RMSK                                           0xffffffff
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_ATTR                                                      0x3
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_ADDR(x))
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_ADDR(x),v)
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_ADDR(x),m,v,HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_IN(x))
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_WR_DATA_MSB_BMSK                                   0xffffffff
#define HWIO_GE_DUT_I2C_MST_WR_DATA_MSB_REG_WR_DATA_MSB_SHFT                                          0x0

#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_ADDR(x)                                            ((x) + 0x00000124)
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_PHYS(x)                                            ((x) + 0x00000124)
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_OFFS                                               (0x00000124)
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_RMSK                                               0xffffffff
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_POR                                                0x00000000
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_POR_RMSK                                           0xffffffff
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_ATTR                                                      0x3
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_ADDR(x))
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_ADDR(x),v)
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_ADDR(x),m,v,HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_IN(x))
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_WR_DATA_LSB_BMSK                                   0xffffffff
#define HWIO_GE_DUT_I2C_MST_WR_DATA_LSB_REG_WR_DATA_LSB_SHFT                                          0x0

#define HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_ADDR(x)                                            ((x) + 0x00000128)
#define HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_PHYS(x)                                            ((x) + 0x00000128)
#define HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_OFFS                                               (0x00000128)
#define HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_RMSK                                               0xffffffff
#define HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_POR                                                0x00000000
#define HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_POR_RMSK                                           0xffffffff
#define HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_ATTR                                                      0x1
#define HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_ADDR(x))
#define HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_RD_DATA_MSB_BMSK                                   0xffffffff
#define HWIO_GE_DUT_I2C_MST_RD_DATA_MSB_REG_RD_DATA_MSB_SHFT                                          0x0

#define HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_ADDR(x)                                            ((x) + 0x0000012c)
#define HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_PHYS(x)                                            ((x) + 0x0000012c)
#define HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_OFFS                                               (0x0000012c)
#define HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_RMSK                                               0xffffffff
#define HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_POR                                                0x00000000
#define HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_POR_RMSK                                           0xffffffff
#define HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_ATTR                                                      0x1
#define HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_ADDR(x))
#define HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_ADDR(x), m)
#define HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_RD_DATA_LSB_BMSK                                   0xffffffff
#define HWIO_GE_DUT_I2C_MST_RD_DATA_LSB_REG_RD_DATA_LSB_SHFT                                          0x0

#define HWIO_GE_DUT_I2C_MST_CTRL_REG_ADDR(x)                                                   ((x) + 0x00000130)
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_PHYS(x)                                                   ((x) + 0x00000130)
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_OFFS                                                      (0x00000130)
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_RMSK                                                      0xff7f0f01
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_POR                                                       0x00200800
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_POR_RMSK                                                  0xffffffff
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_ATTR                                                             0x3
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_I2C_MST_CTRL_REG_ADDR(x))
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_I2C_MST_CTRL_REG_ADDR(x), m)
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_I2C_MST_CTRL_REG_ADDR(x),v)
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_I2C_MST_CTRL_REG_ADDR(x),m,v,HWIO_GE_DUT_I2C_MST_CTRL_REG_IN(x))
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_REG_ADDR_BMSK                                             0xff000000
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_REG_ADDR_SHFT                                                   0x18
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_SLV_ADDR_BMSK                                               0x7f0000
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_SLV_ADDR_SHFT                                                   0x10
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_NUM_BYTES_BMSK                                                 0xf00
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_NUM_BYTES_SHFT                                                   0x8
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_CMD_BMSK                                                         0x1
#define HWIO_GE_DUT_I2C_MST_CTRL_REG_CMD_SHFT                                                         0x0

#define HWIO_GE_DUT_I2C_MST_STS_REG_ADDR(x)                                                    ((x) + 0x00000134)
#define HWIO_GE_DUT_I2C_MST_STS_REG_PHYS(x)                                                    ((x) + 0x00000134)
#define HWIO_GE_DUT_I2C_MST_STS_REG_OFFS                                                       (0x00000134)
#define HWIO_GE_DUT_I2C_MST_STS_REG_RMSK                                                            0x101
#define HWIO_GE_DUT_I2C_MST_STS_REG_POR                                                        0x00000000
#define HWIO_GE_DUT_I2C_MST_STS_REG_POR_RMSK                                                   0xffffffff
#define HWIO_GE_DUT_I2C_MST_STS_REG_ATTR                                                              0x1
#define HWIO_GE_DUT_I2C_MST_STS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_I2C_MST_STS_REG_ADDR(x))
#define HWIO_GE_DUT_I2C_MST_STS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_I2C_MST_STS_REG_ADDR(x), m)
#define HWIO_GE_DUT_I2C_MST_STS_REG_CMD_DONE_BMSK                                                   0x100
#define HWIO_GE_DUT_I2C_MST_STS_REG_CMD_DONE_SHFT                                                     0x8
#define HWIO_GE_DUT_I2C_MST_STS_REG_NACK_BMSK                                                         0x1
#define HWIO_GE_DUT_I2C_MST_STS_REG_NACK_SHFT                                                         0x0

#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_ADDR(x)                                          ((x) + 0x00000140)
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_PHYS(x)                                          ((x) + 0x00000140)
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_OFFS                                             (0x00000140)
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_RMSK                                                 0x110f
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_POR                                              0x00000000
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_POR_RMSK                                         0xffffffff
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_ATTR                                                    0x3
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_ADDR(x))
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_ADDR(x), m)
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_ADDR(x),v)
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_ADDR(x),m,v,HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_IN(x))
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_RESET_BMSK                                           0x1000
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_RESET_SHFT                                              0xc
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_ADAPTER_STATE_VALID_BMSK                              0x100
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_ADAPTER_STATE_VALID_SHFT                                0x8
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_ADAPTER_STATE_BMSK                                      0xf
#define HWIO_GE_DUT_L0_ADAPTER_STATE_FIFO_REG_ADAPTER_STATE_SHFT                                      0x0

#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_ADDR(x)                                            ((x) + 0x00000144)
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_PHYS(x)                                            ((x) + 0x00000144)
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_OFFS                                               (0x00000144)
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_RMSK                                                   0x111f
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_POR                                                0x00000000
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_POR_RMSK                                           0xffffffff
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_ATTR                                                      0x3
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_ADDR(x))
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_ADDR(x), m)
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_ADDR(x),v)
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_ADDR(x),m,v,HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_IN(x))
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_RESET_BMSK                                             0x1000
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_RESET_SHFT                                                0xc
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_TRAIN_STATE_VALID_BMSK                                  0x100
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_TRAIN_STATE_VALID_SHFT                                    0x8
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_TRAIN_STATE_BMSK                                         0x1f
#define HWIO_GE_DUT_L0_TRAIN_STATE_FIFO_REG_TRAIN_STATE_SHFT                                          0x0

#define HWIO_GE_DUT_PCIE_RESET_REG_ADDR(x)                                                     ((x) + 0x00000160)
#define HWIO_GE_DUT_PCIE_RESET_REG_PHYS(x)                                                     ((x) + 0x00000160)
#define HWIO_GE_DUT_PCIE_RESET_REG_OFFS                                                        (0x00000160)
#define HWIO_GE_DUT_PCIE_RESET_REG_RMSK                                                              0xff
#define HWIO_GE_DUT_PCIE_RESET_REG_POR                                                         0x00000000
#define HWIO_GE_DUT_PCIE_RESET_REG_POR_RMSK                                                    0xffffffff
#define HWIO_GE_DUT_PCIE_RESET_REG_ATTR                                                               0x3
#define HWIO_GE_DUT_PCIE_RESET_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PCIE_RESET_REG_ADDR(x))
#define HWIO_GE_DUT_PCIE_RESET_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PCIE_RESET_REG_ADDR(x), m)
#define HWIO_GE_DUT_PCIE_RESET_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_PCIE_RESET_REG_ADDR(x),v)
#define HWIO_GE_DUT_PCIE_RESET_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_PCIE_RESET_REG_ADDR(x),m,v,HWIO_GE_DUT_PCIE_RESET_REG_IN(x))
#define HWIO_GE_DUT_PCIE_RESET_REG_SLV_AXI_ARES_BMSK                                                 0x80
#define HWIO_GE_DUT_PCIE_RESET_REG_SLV_AXI_ARES_SHFT                                                  0x7
#define HWIO_GE_DUT_PCIE_RESET_REG_SLV_AXI_STICKY_ARES_BMSK                                          0x40
#define HWIO_GE_DUT_PCIE_RESET_REG_SLV_AXI_STICKY_ARES_SHFT                                           0x6
#define HWIO_GE_DUT_PCIE_RESET_REG_MSTR_AXI_ARES_BMSK                                                0x20
#define HWIO_GE_DUT_PCIE_RESET_REG_MSTR_AXI_ARES_SHFT                                                 0x5
#define HWIO_GE_DUT_PCIE_RESET_REG_MSTR_AXI_STICKY_ARES_BMSK                                         0x10
#define HWIO_GE_DUT_PCIE_RESET_REG_MSTR_AXI_STICKY_ARES_SHFT                                          0x4
#define HWIO_GE_DUT_PCIE_RESET_REG_AHB_ARES_BMSK                                                      0x8
#define HWIO_GE_DUT_PCIE_RESET_REG_AHB_ARES_SHFT                                                      0x3
#define HWIO_GE_DUT_PCIE_RESET_REG_CORE_ARES_BMSK                                                     0x4
#define HWIO_GE_DUT_PCIE_RESET_REG_CORE_ARES_SHFT                                                     0x2
#define HWIO_GE_DUT_PCIE_RESET_REG_CORE_STICKY_ARES_BMSK                                              0x2
#define HWIO_GE_DUT_PCIE_RESET_REG_CORE_STICKY_ARES_SHFT                                              0x1
#define HWIO_GE_DUT_PCIE_RESET_REG_PWR_ARES_BMSK                                                      0x1
#define HWIO_GE_DUT_PCIE_RESET_REG_PWR_ARES_SHFT                                                      0x0

#define HWIO_GE_DUT_PCIE_LAST_ADDR_REG_ADDR(x)                                                 ((x) + 0x00000164)
#define HWIO_GE_DUT_PCIE_LAST_ADDR_REG_PHYS(x)                                                 ((x) + 0x00000164)
#define HWIO_GE_DUT_PCIE_LAST_ADDR_REG_OFFS                                                    (0x00000164)
#define HWIO_GE_DUT_PCIE_LAST_ADDR_REG_RMSK                                                          0xff
#define HWIO_GE_DUT_PCIE_LAST_ADDR_REG_POR                                                     0x00000000
#define HWIO_GE_DUT_PCIE_LAST_ADDR_REG_POR_RMSK                                                0xffffffff
#define HWIO_GE_DUT_PCIE_LAST_ADDR_REG_ATTR                                                           0x1
#define HWIO_GE_DUT_PCIE_LAST_ADDR_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PCIE_LAST_ADDR_REG_ADDR(x))
#define HWIO_GE_DUT_PCIE_LAST_ADDR_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PCIE_LAST_ADDR_REG_ADDR(x), m)
#define HWIO_GE_DUT_PCIE_LAST_ADDR_REG_TOP_BITS_BMSK                                                 0xff
#define HWIO_GE_DUT_PCIE_LAST_ADDR_REG_TOP_BITS_SHFT                                                  0x0

#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_ADDR(x)                                              ((x) + 0x00000168)
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_PHYS(x)                                              ((x) + 0x00000168)
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_OFFS                                                 (0x00000168)
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_RMSK                                                   0x3f003f
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_POR                                                  0x00000000
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_POR_RMSK                                             0xffffffff
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_ATTR                                                        0x1
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_ADDR(x))
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_ADDR(x), m)
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_REG_BMSK                                         0x3f0000
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_REG_SHFT                                             0x10
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_BMSK                                                 0x3f
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_SHFT                                                  0x0
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_DETECT_QUIET_FVAL                                   0x0
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_DETECT_ACT_FVAL                                     0x1
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_POLL_ACTIVE_FVAL                                    0x2
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_POLL_COMPLIANCE_FVAL                                0x3
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_POLL_CONFIG_FVAL                                    0x4
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_PRE_DETECT_QUIET_FVAL                               0x5
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_DETECT_WAIT_FVAL                                    0x6
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_CFG_LINKWD_START_FVAL                               0x7
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_CFG_LINKWD_ACEPT_FVAL                               0x8
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_CFG_LANENUM_WAIT_FVAL                               0x9
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_CFG_LANENUM_ACEPT_FVAL                              0xa
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_CFG_COMPLETE_FVAL                                   0xb
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_CFG_IDLE_FVAL                                       0xc
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_RCVRY_LOCK_FVAL                                     0xd
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_RCVRY_SPEED_FVAL                                    0xe
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_RCVRY_RCVRCFG_FVAL                                  0xf
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_RCVRY_IDLE_FVAL                                    0x10
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_L0_FVAL                                            0x11
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_L0S_FVAL                                           0x12
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_L123_SEND_EIDLE_FVAL                               0x13
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_L1_IDLE_FVAL                                       0x14
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_L2_IDLE_FVAL                                       0x15
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_L2_WAKE_FVAL                                       0x16
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_DISABLED_ENTRY_FVAL                                0x17
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_DISABLED_IDLE_FVAL                                 0x18
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_DISABLED_FVAL                                      0x19
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_LPBK_ENTRY_FVAL                                    0x1a
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_LPBK_ACTIVE_FVAL                                   0x1b
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_LPBK_EXIT_FVAL                                     0x1c
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_LPBK_EXIT_TIMEOUT_FVAL                             0x1d
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_HOT_RESET_ENTRY_FVAL                               0x1e
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_HOT_RESET_FVAL                                     0x1f
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_RCVRY_EQ0_FVAL                                     0x20
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_RCVRY_EQ1_FVAL                                     0x21
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_RCVRY_EQ2_FVAL                                     0x22
#define HWIO_GE_DUT_PCIE_LTSSM_STATUS_REG_STATE_S_RCVRY_EQ3_FVAL                                     0x23

#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_ADDR(x)                                           ((x) + 0x0000016c)
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_PHYS(x)                                           ((x) + 0x0000016c)
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_OFFS                                              (0x0000016c)
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_RMSK                                                    0x33
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_POR                                               0x00000000
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_POR_RMSK                                          0xffffffff
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_ATTR                                                     0x3
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_ADDR(x))
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_ADDR(x), m)
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_ADDR(x),v)
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_ADDR(x),m,v,HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_IN(x))
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_RELAXED_ORDER_FORCE_VAL_BMSK                            0x20
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_RELAXED_ORDER_FORCE_VAL_SHFT                             0x5
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_RELAXED_ORDER_SW_FORCE_BMSK                             0x10
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_RELAXED_ORDER_SW_FORCE_SHFT                              0x4
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_BIT40_FORCE_VAL_BMSK                                     0x2
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_BIT40_FORCE_VAL_SHFT                                     0x1
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_BIT40_SW_FORCE_BMSK                                      0x1
#define HWIO_GE_DUT_PCIE_REL_ORDER_TRANS_REG_BIT40_SW_FORCE_SHFT                                      0x0

#define HWIO_GE_DUT_PCIE_DEBUG_REG_ADDR(x)                                                     ((x) + 0x00000170)
#define HWIO_GE_DUT_PCIE_DEBUG_REG_PHYS(x)                                                     ((x) + 0x00000170)
#define HWIO_GE_DUT_PCIE_DEBUG_REG_OFFS                                                        (0x00000170)
#define HWIO_GE_DUT_PCIE_DEBUG_REG_RMSK                                                               0x7
#define HWIO_GE_DUT_PCIE_DEBUG_REG_POR                                                         0x00000000
#define HWIO_GE_DUT_PCIE_DEBUG_REG_POR_RMSK                                                    0xffffffff
#define HWIO_GE_DUT_PCIE_DEBUG_REG_ATTR                                                               0x3
#define HWIO_GE_DUT_PCIE_DEBUG_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PCIE_DEBUG_REG_ADDR(x))
#define HWIO_GE_DUT_PCIE_DEBUG_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PCIE_DEBUG_REG_ADDR(x), m)
#define HWIO_GE_DUT_PCIE_DEBUG_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_PCIE_DEBUG_REG_ADDR(x),v)
#define HWIO_GE_DUT_PCIE_DEBUG_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_PCIE_DEBUG_REG_ADDR(x),m,v,HWIO_GE_DUT_PCIE_DEBUG_REG_IN(x))
#define HWIO_GE_DUT_PCIE_DEBUG_REG_PCIE_READ_THROTTLE_BMSK                                            0x4
#define HWIO_GE_DUT_PCIE_DEBUG_REG_PCIE_READ_THROTTLE_SHFT                                            0x2
#define HWIO_GE_DUT_PCIE_DEBUG_REG_FUSE_PCIE_RC_ONLY_BMSK                                             0x2
#define HWIO_GE_DUT_PCIE_DEBUG_REG_FUSE_PCIE_RC_ONLY_SHFT                                             0x1
#define HWIO_GE_DUT_PCIE_DEBUG_REG_FUSE_DEBUGBUS_DISABLE_BMSK                                         0x1
#define HWIO_GE_DUT_PCIE_DEBUG_REG_FUSE_DEBUGBUS_DISABLE_SHFT                                         0x0

#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_ADDR(x)                                               ((x) + 0x00000174)
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_PHYS(x)                                               ((x) + 0x00000174)
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_OFFS                                                  (0x00000174)
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_RMSK                                                   0x1111110
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_POR                                                   0x00000000
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_POR_RMSK                                              0xffffffff
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_ATTR                                                         0x3
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_ADDR(x))
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_ADDR(x), m)
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_ADDR(x),v)
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_ADDR(x),m,v,HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_IN(x))
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_CC_SLV_BRIDGE_CLK_REQ_BMSK                             0x1000000
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_CC_SLV_BRIDGE_CLK_REQ_SHFT                                  0x18
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_CC_CLK_REQ_N_BMSK                                       0x100000
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_CC_CLK_REQ_N_SHFT                                           0x14
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_L1SS_CLKREQN_IN_BMSK                                     0x10000
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_L1SS_CLKREQN_IN_SHFT                                        0x10
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_L1SS_CLKREQN_OE_BMSK                                      0x1000
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_L1SS_CLKREQN_OE_SHFT                                         0xc
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_L1SS_CLKREQN_IN_MUX_BMSK                                   0x100
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_L1SS_CLKREQN_IN_MUX_SHFT                                     0x8
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_PHY_MAC_PHYCLK_REQ_N_BMSK                                   0x10
#define HWIO_GE_DUT_PCIE_CLK_DISABLE_REG_PHY_MAC_PHYCLK_REQ_N_SHFT                                    0x4

#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_ADDR(x)                                                  ((x) + 0x00000178)
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_PHYS(x)                                                  ((x) + 0x00000178)
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_OFFS                                                     (0x00000178)
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_RMSK                                                           0xfe
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_POR                                                      0x000000f0
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_POR_RMSK                                                 0xffffffff
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_ATTR                                                            0x3
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PCIE_AXI_BASE_REG_ADDR(x))
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PCIE_AXI_BASE_REG_ADDR(x), m)
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_PCIE_AXI_BASE_REG_ADDR(x),v)
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_PCIE_AXI_BASE_REG_ADDR(x),m,v,HWIO_GE_DUT_PCIE_AXI_BASE_REG_IN(x))
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_ADDR_MSB_31_25_BMSK                                            0xfe
#define HWIO_GE_DUT_PCIE_AXI_BASE_REG_ADDR_MSB_31_25_SHFT                                             0x1

#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_ADDR(x)                                                ((x) + 0x0000017c)
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_PHYS(x)                                                ((x) + 0x0000017c)
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_OFFS                                                   (0x0000017c)
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_RMSK                                                   0xffffffff
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_POR                                                    0x00000000
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_POR_RMSK                                               0xffffffff
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_ATTR                                                          0x1
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PCIE_B2S_STATUS_REG_ADDR(x))
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PCIE_B2S_STATUS_REG_ADDR(x), m)
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_LAST_AR_SID_BMSK                                       0xffff0000
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_LAST_AR_SID_SHFT                                             0x10
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_LAST_AW_SID_BMSK                                           0xffff
#define HWIO_GE_DUT_PCIE_B2S_STATUS_REG_LAST_AW_SID_SHFT                                              0x0

#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_ADDR(x)                                                ((x) + 0x00000180)
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_PHYS(x)                                                ((x) + 0x00000180)
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_OFFS                                                   (0x00000180)
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_RMSK                                                         0xff
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_POR                                                    0x00000000
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_POR_RMSK                                               0xffffffff
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_ATTR                                                          0x3
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_ADDR(x))
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_ADDR(x), m)
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_ADDR(x),v)
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_ADDR(x),m,v,HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_IN(x))
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_AR_QOS_BMSK                                                  0xf0
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_AR_QOS_SHFT                                                   0x4
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_AW_QOS_BMSK                                                   0xf
#define HWIO_GE_DUT_PCIE_AXI_S_CTRL_REG_AW_QOS_SHFT                                                   0x0

#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_ADDR(x)                                              ((x) + 0x00000184)
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_PHYS(x)                                              ((x) + 0x00000184)
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_OFFS                                                 (0x00000184)
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_RMSK                                                       0xff
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_POR                                                  0x00000000
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_POR_RMSK                                             0xffffffff
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_ATTR                                                        0x1
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_ADDR(x))
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_ADDR(x), m)
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_AR_QOS_BMSK                                                0xf0
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_AR_QOS_SHFT                                                 0x4
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_AW_QOS_BMSK                                                 0xf
#define HWIO_GE_DUT_PCIE_AXI_M_STATUS_REG_AW_QOS_SHFT                                                 0x0

#define HWIO_GE_DUT_USB31_CTRL_REG_ADDR(x)                                                     ((x) + 0x0000018c)
#define HWIO_GE_DUT_USB31_CTRL_REG_PHYS(x)                                                     ((x) + 0x0000018c)
#define HWIO_GE_DUT_USB31_CTRL_REG_OFFS                                                        (0x0000018c)
#define HWIO_GE_DUT_USB31_CTRL_REG_RMSK                                                              0x11
#define HWIO_GE_DUT_USB31_CTRL_REG_POR                                                         0x00000011
#define HWIO_GE_DUT_USB31_CTRL_REG_POR_RMSK                                                    0xffffffff
#define HWIO_GE_DUT_USB31_CTRL_REG_ATTR                                                               0x3
#define HWIO_GE_DUT_USB31_CTRL_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_USB31_CTRL_REG_ADDR(x))
#define HWIO_GE_DUT_USB31_CTRL_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_USB31_CTRL_REG_ADDR(x), m)
#define HWIO_GE_DUT_USB31_CTRL_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_USB31_CTRL_REG_ADDR(x),v)
#define HWIO_GE_DUT_USB31_CTRL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_USB31_CTRL_REG_ADDR(x),m,v,HWIO_GE_DUT_USB31_CTRL_REG_IN(x))
#define HWIO_GE_DUT_USB31_CTRL_REG_PIPE_CLK_EN_BMSK                                                  0x10
#define HWIO_GE_DUT_USB31_CTRL_REG_PIPE_CLK_EN_SHFT                                                   0x4
#define HWIO_GE_DUT_USB31_CTRL_REG_SLEEP_CLK_EN_BMSK                                                  0x1
#define HWIO_GE_DUT_USB31_CTRL_REG_SLEEP_CLK_EN_SHFT                                                  0x0

#define HWIO_GE_DUT_USB31_RESET_REG_ADDR(x)                                                    ((x) + 0x00000190)
#define HWIO_GE_DUT_USB31_RESET_REG_PHYS(x)                                                    ((x) + 0x00000190)
#define HWIO_GE_DUT_USB31_RESET_REG_OFFS                                                       (0x00000190)
#define HWIO_GE_DUT_USB31_RESET_REG_RMSK                                                              0x3
#define HWIO_GE_DUT_USB31_RESET_REG_POR                                                        0x00000000
#define HWIO_GE_DUT_USB31_RESET_REG_POR_RMSK                                                   0xffffffff
#define HWIO_GE_DUT_USB31_RESET_REG_ATTR                                                              0x3
#define HWIO_GE_DUT_USB31_RESET_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_USB31_RESET_REG_ADDR(x))
#define HWIO_GE_DUT_USB31_RESET_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_USB31_RESET_REG_ADDR(x), m)
#define HWIO_GE_DUT_USB31_RESET_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_USB31_RESET_REG_ADDR(x),v)
#define HWIO_GE_DUT_USB31_RESET_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_USB31_RESET_REG_ADDR(x),m,v,HWIO_GE_DUT_USB31_RESET_REG_IN(x))
#define HWIO_GE_DUT_USB31_RESET_REG_SLEEP_ARES_BMSK                                                   0x2
#define HWIO_GE_DUT_USB31_RESET_REG_SLEEP_ARES_SHFT                                                   0x1
#define HWIO_GE_DUT_USB31_RESET_REG_MASTER_ARES_BMSK                                                  0x1
#define HWIO_GE_DUT_USB31_RESET_REG_MASTER_ARES_SHFT                                                  0x0

#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_ADDR(x)                                ((x) + 0x00000194)
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_PHYS(x)                                ((x) + 0x00000194)
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_OFFS                                   (0x00000194)
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_RMSK                                   0x77f7ffff
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_POR                                    0x02c01001
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_POR_RMSK                               0xffffffff
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_ATTR                                          0x3
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_ADDR(x))
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_ADDR(x), m)
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_ADDR(x),v)
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_ADDR(x),m,v,HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_IN(x))
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_CLKFBOUT_MULT_FRAC_BMSK                0x70000000
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_CLKFBOUT_MULT_FRAC_SHFT                      0x1c
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_CLKFBOUT_MULT_INT_BMSK                  0x7f00000
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_CLKFBOUT_MULT_INT_SHFT                       0x14
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_CLKOUT0_DIV_FRAC_BMSK                     0x70000
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_CLKOUT0_DIV_FRAC_SHFT                        0x10
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_CLKOUT0_DIV_INT_BMSK                       0xff00
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_CLKOUT0_DIV_INT_SHFT                          0x8
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_DIVCLK_DIV_BMSK                              0xff
#define HWIO_GE_DUT_DP_PCLK_MMCM_MULT_DIV_CLK0_CTRL_REG_DIVCLK_DIV_SHFT                               0x0

#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_ADDR(x)                                    ((x) + 0x00000198)
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_PHYS(x)                                    ((x) + 0x00000198)
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_OFFS                                       (0x00000198)
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_RMSK                                       0xffffffff
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_POR                                        0x10101010
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_POR_RMSK                                   0xffffffff
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_ATTR                                              0x3
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_ADDR(x))
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_ADDR(x), m)
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_ADDR(x),v)
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_ADDR(x),m,v,HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_IN(x))
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_CLKOUT1_DIV_BMSK                           0xff000000
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_CLKOUT1_DIV_SHFT                                 0x18
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_CLKOUT2_DIV_BMSK                             0xff0000
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_CLKOUT2_DIV_SHFT                                 0x10
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_CLKOUT3_DIV_BMSK                               0xff00
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_CLKOUT3_DIV_SHFT                                  0x8
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_CLKOUT4_DIV_BMSK                                 0xff
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK1_TO_4_CTRL_REG_CLKOUT4_DIV_SHFT                                  0x0

#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_ADDR(x)                         ((x) + 0x0000019c)
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_PHYS(x)                         ((x) + 0x0000019c)
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_OFFS                            (0x0000019c)
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_RMSK                            0x1000ffff
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_POR                             0x10000c0c
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_POR_RMSK                        0xffffffff
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_ATTR                                   0x3
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_ADDR(x))
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_ADDR(x), m)
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_ADDR(x),v)
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_ADDR(x),m,v,HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_IN(x))
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_MMCM_READY_TO_CFG_BMSK          0x10000000
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_MMCM_READY_TO_CFG_SHFT                0x1c
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_CLKOUT5_DIV_BMSK                    0xff00
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_CLKOUT5_DIV_SHFT                       0x8
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_CLKOUT6_DIV_BMSK                      0xff
#define HWIO_GE_DUT_DP_PCLK_MMCM_CLK5_TO_6_CTRL_AND_STATUS_REG_CLKOUT6_DIV_SHFT                       0x0

#define HWIO_GE_DUT_DP_CTRL_STS_REG_ADDR(x)                                                    ((x) + 0x000001c0)
#define HWIO_GE_DUT_DP_CTRL_STS_REG_PHYS(x)                                                    ((x) + 0x000001c0)
#define HWIO_GE_DUT_DP_CTRL_STS_REG_OFFS                                                       (0x000001c0)
#define HWIO_GE_DUT_DP_CTRL_STS_REG_RMSK                                                              0xf
#define HWIO_GE_DUT_DP_CTRL_STS_REG_POR                                                        0x00000000
#define HWIO_GE_DUT_DP_CTRL_STS_REG_POR_RMSK                                                   0xffffffff
#define HWIO_GE_DUT_DP_CTRL_STS_REG_ATTR                                                              0x3
#define HWIO_GE_DUT_DP_CTRL_STS_REG_IN(x)      \
        in_dword(HWIO_GE_DUT_DP_CTRL_STS_REG_ADDR(x))
#define HWIO_GE_DUT_DP_CTRL_STS_REG_INM(x, m)      \
        in_dword_masked(HWIO_GE_DUT_DP_CTRL_STS_REG_ADDR(x), m)
#define HWIO_GE_DUT_DP_CTRL_STS_REG_OUT(x, v)      \
        out_dword(HWIO_GE_DUT_DP_CTRL_STS_REG_ADDR(x),v)
#define HWIO_GE_DUT_DP_CTRL_STS_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GE_DUT_DP_CTRL_STS_REG_ADDR(x),m,v,HWIO_GE_DUT_DP_CTRL_STS_REG_IN(x))
#define HWIO_GE_DUT_DP_CTRL_STS_REG_DP_HPD_BMSK                                                       0x8
#define HWIO_GE_DUT_DP_CTRL_STS_REG_DP_HPD_SHFT                                                       0x3
#define HWIO_GE_DUT_DP_CTRL_STS_REG_MDP_RST_BMSK                                                      0x4
#define HWIO_GE_DUT_DP_CTRL_STS_REG_MDP_RST_SHFT                                                      0x2
#define HWIO_GE_DUT_DP_CTRL_STS_REG_DP_PCLK_MMCM_LOCKED_BMSK                                          0x2
#define HWIO_GE_DUT_DP_CTRL_STS_REG_DP_PCLK_MMCM_LOCKED_SHFT                                          0x1
#define HWIO_GE_DUT_DP_CTRL_STS_REG_DP_MMCM_LOCKED_BMSK                                               0x1
#define HWIO_GE_DUT_DP_CTRL_STS_REG_DP_MMCM_LOCKED_SHFT                                               0x0

#endif /* __MSMHWIOXREG_DUT0_H__ */
