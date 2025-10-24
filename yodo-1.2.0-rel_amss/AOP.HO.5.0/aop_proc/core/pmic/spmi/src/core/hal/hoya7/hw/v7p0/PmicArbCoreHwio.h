#ifndef __PMICARBCOREHWIO_H__
#define __PMICARBCOREHWIO_H__
/*
===========================================================================
*/
/**
    @file PmicArbCoreHwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8450 (Waipio) [waipio_v1.0_p3q2r14.6_rtl_partition_M01]
 
    This file contains HWIO register definitions for the following modules:
        PMIC_ARB_CORE
        PMIC_ARB_CORE_REGISTERS
        PMIC_ARB_CORE_REGISTERS_OBS
        PMIC_ARB_MGPI
        QDSS_AOSS_APB_AOSS_PMIC_ARB_DEBUG_CSR_AOSS_PMIC_ARB_DEBUG_CSR_PMIC_ARB_DEBUG


    Generation parameters: 
    { 'explicit-addressing': True,
      'filename': 'PmicArbCoreHwio.h',
      'module-filter-exclude': {},
      'module-filter-include': {},
      'modules': [ 'PMIC_ARB_CORE',
                   'PMIC_ARB_CORE_REGISTERS',
                   'PMIC_ARB_CORE_REGISTERS_OBS',
                   'PMIC_ARB_MGPI',
                   'QDSS_AOSS_APB_AOSS_PMIC_ARB_DEBUG_CSR_AOSS_PMIC_ARB_DEBUG_CSR_PMIC_ARB_DEBUG'],
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

    $Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/spmi/src/core/hal/hoya7/hw/v7p0/PmicArbCoreHwio.h#1 $
    $DateTime: 2021/10/26 22:03:12 $
    $Author: pwbldsvc $

    ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: PMIC_ARB_CORE
 *--------------------------------------------------------------------------*/
#define PMIC_ARB_BASE_OFFS                                                                  0x1400000


#define PMIC_ARB_CORE_REG_BASE_OFFS                                                         (PMIC_ARB_BASE_OFFS + 0x00000)

#define HWIO_PMIC_ARB_HW_VERSION_ADDR(x)                                                    ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x0)
#define HWIO_PMIC_ARB_HW_VERSION_OFFS                                                       (0x0)
#define HWIO_PMIC_ARB_HW_VERSION_RMSK                                                       0xffffffff
#define HWIO_PMIC_ARB_HW_VERSION_IN(x)            \
                in_dword(HWIO_PMIC_ARB_HW_VERSION_ADDR(x))
#define HWIO_PMIC_ARB_HW_VERSION_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB_HW_VERSION_ADDR(x), m)
#define HWIO_PMIC_ARB_HW_VERSION_MAJOR_BMSK                                                 0xf0000000
#define HWIO_PMIC_ARB_HW_VERSION_MAJOR_SHFT                                                         28
#define HWIO_PMIC_ARB_HW_VERSION_MINOR_BMSK                                                  0xfff0000
#define HWIO_PMIC_ARB_HW_VERSION_MINOR_SHFT                                                         16
#define HWIO_PMIC_ARB_HW_VERSION_STEP_BMSK                                                      0xffff
#define HWIO_PMIC_ARB_HW_VERSION_STEP_SHFT                                                           0

#define HWIO_PMIC_ARB_FEATURES_ADDR(x)                                                      ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x4)
#define HWIO_PMIC_ARB_FEATURES_OFFS                                                         (0x4)
#define HWIO_PMIC_ARB_FEATURES_RMSK                                                         0xffff07ff
#define HWIO_PMIC_ARB_FEATURES_IN(x)            \
                in_dword(HWIO_PMIC_ARB_FEATURES_ADDR(x))
#define HWIO_PMIC_ARB_FEATURES_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB_FEATURES_ADDR(x), m)
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PIC_ACC_ENABLES_BMSK                               0xffe00000
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PIC_ACC_ENABLES_SHFT                                       21
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PVC_PORTS_SPMI0_BMSK                                 0x1f0000
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PVC_PORTS_SPMI0_SHFT                                       16
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PMIC_PERIPHERALS_SPMI0_BMSK                             0x7ff
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PMIC_PERIPHERALS_SPMI0_SHFT                                 0

#define HWIO_PMIC_ARB_FEATURES_1_ADDR(x)                                                    ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x8)
#define HWIO_PMIC_ARB_FEATURES_1_OFFS                                                       (0x8)
#define HWIO_PMIC_ARB_FEATURES_1_RMSK                                                            0x7ff
#define HWIO_PMIC_ARB_FEATURES_1_IN(x)            \
                in_dword(HWIO_PMIC_ARB_FEATURES_1_ADDR(x))
#define HWIO_PMIC_ARB_FEATURES_1_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB_FEATURES_1_ADDR(x), m)
#define HWIO_PMIC_ARB_FEATURES_1_NUMBER_OF_PMIC_PERIPHERALS_SPMI1_BMSK                           0x7ff
#define HWIO_PMIC_ARB_FEATURES_1_NUMBER_OF_PMIC_PERIPHERALS_SPMI1_SHFT                               0

#define HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x)                                                   ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x10)
#define HWIO_PMIC_ARB_MISC_CONFIG_OFFS                                                      (0x10)
#define HWIO_PMIC_ARB_MISC_CONFIG_RMSK                                                        0x3de5c7
#define HWIO_PMIC_ARB_MISC_CONFIG_IN(x)            \
                in_dword(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x))
#define HWIO_PMIC_ARB_MISC_CONFIG_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x), m)
#define HWIO_PMIC_ARB_MISC_CONFIG_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x),v)
#define HWIO_PMIC_ARB_MISC_CONFIG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x),m,v,HWIO_PMIC_ARB_MISC_CONFIG_IN(x))
#define HWIO_PMIC_ARB_MISC_CONFIG_WDT_RST_DUMMY_DONE_EN_BMSK                                  0x200000
#define HWIO_PMIC_ARB_MISC_CONFIG_WDT_RST_DUMMY_DONE_EN_SHFT                                        21
#define HWIO_PMIC_ARB_MISC_CONFIG_XPU_SILENT_LOGGING_EN_BMSK                                  0x100000
#define HWIO_PMIC_ARB_MISC_CONFIG_XPU_SILENT_LOGGING_EN_SHFT                                        20
#define HWIO_PMIC_ARB_MISC_CONFIG_AOSS_BCST_RPMH_CLK_REQ_EN_BMSK                               0xc0000
#define HWIO_PMIC_ARB_MISC_CONFIG_AOSS_BCST_RPMH_CLK_REQ_EN_SHFT                                    18
#define HWIO_PMIC_ARB_MISC_CONFIG_PMIC_ARB_TEST_BUS_SELECT_BMSK                                0x10000
#define HWIO_PMIC_ARB_MISC_CONFIG_PMIC_ARB_TEST_BUS_SELECT_SHFT                                     16
#define HWIO_PMIC_ARB_MISC_CONFIG_DBG_SPMI_SW_CHAN_EN_BMSK                                      0xc000
#define HWIO_PMIC_ARB_MISC_CONFIG_DBG_SPMI_SW_CHAN_EN_SHFT                                          14
#define HWIO_PMIC_ARB_MISC_CONFIG_ECO_EE_FWD_PATH_FIX_CHKN_BIT0_BMSK                            0x2000
#define HWIO_PMIC_ARB_MISC_CONFIG_ECO_EE_FWD_PATH_FIX_CHKN_BIT0_SHFT                                13
#define HWIO_PMIC_ARB_MISC_CONFIG_SW_CHNL_CONC_ACC_ECO_FIX_CHICKEN_BIT_BMSK                      0x400
#define HWIO_PMIC_ARB_MISC_CONFIG_SW_CHNL_CONC_ACC_ECO_FIX_CHICKEN_BIT_SHFT                         10
#define HWIO_PMIC_ARB_MISC_CONFIG_MISC_CONFIG_SPARE_BMSK                                         0x100
#define HWIO_PMIC_ARB_MISC_CONFIG_MISC_CONFIG_SPARE_SHFT                                             8
#define HWIO_PMIC_ARB_MISC_CONFIG_ECO_EE_FWD_PATH_FIX_CHKN_BIT1_BMSK                              0x80
#define HWIO_PMIC_ARB_MISC_CONFIG_ECO_EE_FWD_PATH_FIX_CHKN_BIT1_SHFT                                 7
#define HWIO_PMIC_ARB_MISC_CONFIG_SPMI_TEST_BUS_SELECT_BMSK                                       0x40
#define HWIO_PMIC_ARB_MISC_CONFIG_SPMI_TEST_BUS_SELECT_SHFT                                          6
#define HWIO_PMIC_ARB_MISC_CONFIG_TEST_BUS_EN_BMSK                                                 0x4
#define HWIO_PMIC_ARB_MISC_CONFIG_TEST_BUS_EN_SHFT                                                   2
#define HWIO_PMIC_ARB_MISC_CONFIG_CLK_GATE_EN_BMSK                                                 0x2
#define HWIO_PMIC_ARB_MISC_CONFIG_CLK_GATE_EN_SHFT                                                   1
#define HWIO_PMIC_ARB_MISC_CONFIG_DONE_IRQ_EN_BMSK                                                 0x1
#define HWIO_PMIC_ARB_MISC_CONFIG_DONE_IRQ_EN_SHFT                                                   0

#define HWIO_PMIC_ARB_XBL_STATUS_ADDR(x)                                                    ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x14)
#define HWIO_PMIC_ARB_XBL_STATUS_OFFS                                                       (0x14)
#define HWIO_PMIC_ARB_XBL_STATUS_RMSK                                                          0xfffff
#define HWIO_PMIC_ARB_XBL_STATUS_IN(x)            \
                in_dword(HWIO_PMIC_ARB_XBL_STATUS_ADDR(x))
#define HWIO_PMIC_ARB_XBL_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB_XBL_STATUS_ADDR(x), m)
#define HWIO_PMIC_ARB_XBL_STATUS_DEBUG_CNT_SPMI1_BMSK                                          0xffc00
#define HWIO_PMIC_ARB_XBL_STATUS_DEBUG_CNT_SPMI1_SHFT                                               10
#define HWIO_PMIC_ARB_XBL_STATUS_DEBUG_CNT_SPMI0_BMSK                                            0x3ff
#define HWIO_PMIC_ARB_XBL_STATUS_DEBUG_CNT_SPMI0_SHFT                                                0

#define HWIO_PMIC_ARBm_SW_RST_CTRL_ADDR(base,m)                                             ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0X1C + (0x4*(m)))
#define HWIO_PMIC_ARBm_SW_RST_CTRL_OFFS(m)                                                  (0X1C + (0x4*(m)))
#define HWIO_PMIC_ARBm_SW_RST_CTRL_RMSK                                                            0x1
#define HWIO_PMIC_ARBm_SW_RST_CTRL_INI(base,m)                \
                in_dword_masked(HWIO_PMIC_ARBm_SW_RST_CTRL_ADDR(base,m), HWIO_PMIC_ARBm_SW_RST_CTRL_RMSK)
#define HWIO_PMIC_ARBm_SW_RST_CTRL_INMI(base,m,mask)        \
                in_dword_masked(HWIO_PMIC_ARBm_SW_RST_CTRL_ADDR(base,m), mask)
#define HWIO_PMIC_ARBm_SW_RST_CTRL_OUTI(base,m,val)        \
                out_dword(HWIO_PMIC_ARBm_SW_RST_CTRL_ADDR(base,m),val)
#define HWIO_PMIC_ARBm_SW_RST_CTRL_OUTMI(base,m,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARBm_SW_RST_CTRL_ADDR(base,m),mask,val,HWIO_PMIC_ARBm_SW_RST_CTRL_INI(base,m))
#define HWIO_PMIC_ARBm_SW_RST_CTRL_SW_RST_ENABLE_BMSK                                              0x1
#define HWIO_PMIC_ARBm_SW_RST_CTRL_SW_RST_ENABLE_SHFT                                                0

#define HWIO_PMIC_ARB_WDT_CBC_CTRL_ADDR(x)                                                  ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x40)
#define HWIO_PMIC_ARB_WDT_CBC_CTRL_OFFS                                                     (0x40)
#define HWIO_PMIC_ARB_WDT_CBC_CTRL_RMSK                                                            0x3
#define HWIO_PMIC_ARB_WDT_CBC_CTRL_IN(x)            \
                in_dword(HWIO_PMIC_ARB_WDT_CBC_CTRL_ADDR(x))
#define HWIO_PMIC_ARB_WDT_CBC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB_WDT_CBC_CTRL_ADDR(x), m)
#define HWIO_PMIC_ARB_WDT_CBC_CTRL_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB_WDT_CBC_CTRL_ADDR(x),v)
#define HWIO_PMIC_ARB_WDT_CBC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB_WDT_CBC_CTRL_ADDR(x),m,v,HWIO_PMIC_ARB_WDT_CBC_CTRL_IN(x))
#define HWIO_PMIC_ARB_WDT_CBC_CTRL_WDT_CBCR_SW_CLK_EN_BMSK                                         0x2
#define HWIO_PMIC_ARB_WDT_CBC_CTRL_WDT_CBCR_SW_CLK_EN_SHFT                                           1
#define HWIO_PMIC_ARB_WDT_CBC_CTRL_WDT_CBCR_HW_CLK_CTL_BMSK                                        0x1
#define HWIO_PMIC_ARB_WDT_CBC_CTRL_WDT_CBCR_HW_CLK_CTL_SHFT                                          0

#define HWIO_PMIC_ARB_AOSS_BCST_CONFIG_ADDR(x)                                              ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x80)
#define HWIO_PMIC_ARB_AOSS_BCST_CONFIG_OFFS                                                 (0x80)
#define HWIO_PMIC_ARB_AOSS_BCST_CONFIG_RMSK                                                        0x1
#define HWIO_PMIC_ARB_AOSS_BCST_CONFIG_IN(x)            \
                in_dword(HWIO_PMIC_ARB_AOSS_BCST_CONFIG_ADDR(x))
#define HWIO_PMIC_ARB_AOSS_BCST_CONFIG_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB_AOSS_BCST_CONFIG_ADDR(x), m)
#define HWIO_PMIC_ARB_AOSS_BCST_CONFIG_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB_AOSS_BCST_CONFIG_ADDR(x),v)
#define HWIO_PMIC_ARB_AOSS_BCST_CONFIG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB_AOSS_BCST_CONFIG_ADDR(x),m,v,HWIO_PMIC_ARB_AOSS_BCST_CONFIG_IN(x))
#define HWIO_PMIC_ARB_AOSS_BCST_CONFIG_AOSS_BCST_PRIORITY_BMSK                                     0x1
#define HWIO_PMIC_ARB_AOSS_BCST_CONFIG_AOSS_BCST_PRIORITY_SHFT                                       0

#define HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_ADDR(x)                                      ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x84)
#define HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_OFFS                                         (0x84)
#define HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_RMSK                                                0xf
#define HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_IN(x)            \
                in_dword(HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_ADDR(x))
#define HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_ADDR(x), m)
#define HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_ADDR(x),v)
#define HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_ADDR(x),m,v,HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_IN(x))
#define HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_AOSS_BCST_VALID_WIDTH_CNTR_MAX_BMSK                 0xf
#define HWIO_PMIC_ARB_AOSS_BCST_COUNTER_CONFIG_AOSS_BCST_VALID_WIDTH_CNTR_MAX_SHFT                   0

#define HWIO_PMIC_ARB0_PRIORITIES0_ADDR(x)                                                  ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x100)
#define HWIO_PMIC_ARB0_PRIORITIES0_OFFS                                                     (0x100)
#define HWIO_PMIC_ARB0_PRIORITIES0_RMSK                                                           0x1f
#define HWIO_PMIC_ARB0_PRIORITIES0_IN(x)            \
                in_dword(HWIO_PMIC_ARB0_PRIORITIES0_ADDR(x))
#define HWIO_PMIC_ARB0_PRIORITIES0_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB0_PRIORITIES0_ADDR(x), m)
#define HWIO_PMIC_ARB0_PRIORITIES0_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB0_PRIORITIES0_ADDR(x),v)
#define HWIO_PMIC_ARB0_PRIORITIES0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB0_PRIORITIES0_ADDR(x),m,v,HWIO_PMIC_ARB0_PRIORITIES0_IN(x))
#define HWIO_PMIC_ARB0_PRIORITIES0_PORT_PRIORITY_BMSK                                             0x1f
#define HWIO_PMIC_ARB0_PRIORITIES0_PORT_PRIORITY_SHFT                                                0

#define HWIO_PMIC_ARB0_PRIORITIES1_ADDR(x)                                                  ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x104)
#define HWIO_PMIC_ARB0_PRIORITIES1_OFFS                                                     (0x104)
#define HWIO_PMIC_ARB0_PRIORITIES1_RMSK                                                           0x1f
#define HWIO_PMIC_ARB0_PRIORITIES1_IN(x)            \
                in_dword(HWIO_PMIC_ARB0_PRIORITIES1_ADDR(x))
#define HWIO_PMIC_ARB0_PRIORITIES1_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB0_PRIORITIES1_ADDR(x), m)
#define HWIO_PMIC_ARB0_PRIORITIES1_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB0_PRIORITIES1_ADDR(x),v)
#define HWIO_PMIC_ARB0_PRIORITIES1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB0_PRIORITIES1_ADDR(x),m,v,HWIO_PMIC_ARB0_PRIORITIES1_IN(x))
#define HWIO_PMIC_ARB0_PRIORITIES1_PORT_PRIORITY_BMSK                                             0x1f
#define HWIO_PMIC_ARB0_PRIORITIES1_PORT_PRIORITY_SHFT                                                0

#define HWIO_PMIC_ARB0_PRIORITIES2_ADDR(x)                                                  ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x108)
#define HWIO_PMIC_ARB0_PRIORITIES2_OFFS                                                     (0x108)
#define HWIO_PMIC_ARB0_PRIORITIES2_RMSK                                                           0x1f
#define HWIO_PMIC_ARB0_PRIORITIES2_IN(x)            \
                in_dword(HWIO_PMIC_ARB0_PRIORITIES2_ADDR(x))
#define HWIO_PMIC_ARB0_PRIORITIES2_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB0_PRIORITIES2_ADDR(x), m)
#define HWIO_PMIC_ARB0_PRIORITIES2_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB0_PRIORITIES2_ADDR(x),v)
#define HWIO_PMIC_ARB0_PRIORITIES2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB0_PRIORITIES2_ADDR(x),m,v,HWIO_PMIC_ARB0_PRIORITIES2_IN(x))
#define HWIO_PMIC_ARB0_PRIORITIES2_PORT_PRIORITY_BMSK                                             0x1f
#define HWIO_PMIC_ARB0_PRIORITIES2_PORT_PRIORITY_SHFT                                                0

#define HWIO_PMIC_ARB0_PRIORITIES3_ADDR(x)                                                  ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x10c)
#define HWIO_PMIC_ARB0_PRIORITIES3_OFFS                                                     (0x10c)
#define HWIO_PMIC_ARB0_PRIORITIES3_RMSK                                                           0x1f
#define HWIO_PMIC_ARB0_PRIORITIES3_IN(x)            \
                in_dword(HWIO_PMIC_ARB0_PRIORITIES3_ADDR(x))
#define HWIO_PMIC_ARB0_PRIORITIES3_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB0_PRIORITIES3_ADDR(x), m)
#define HWIO_PMIC_ARB0_PRIORITIES3_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB0_PRIORITIES3_ADDR(x),v)
#define HWIO_PMIC_ARB0_PRIORITIES3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB0_PRIORITIES3_ADDR(x),m,v,HWIO_PMIC_ARB0_PRIORITIES3_IN(x))
#define HWIO_PMIC_ARB0_PRIORITIES3_PORT_PRIORITY_BMSK                                             0x1f
#define HWIO_PMIC_ARB0_PRIORITIES3_PORT_PRIORITY_SHFT                                                0

#define HWIO_PMIC_ARB0_PRIORITIES4_ADDR(x)                                                  ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x110)
#define HWIO_PMIC_ARB0_PRIORITIES4_OFFS                                                     (0x110)
#define HWIO_PMIC_ARB0_PRIORITIES4_RMSK                                                           0x1f
#define HWIO_PMIC_ARB0_PRIORITIES4_IN(x)            \
                in_dword(HWIO_PMIC_ARB0_PRIORITIES4_ADDR(x))
#define HWIO_PMIC_ARB0_PRIORITIES4_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB0_PRIORITIES4_ADDR(x), m)
#define HWIO_PMIC_ARB0_PRIORITIES4_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB0_PRIORITIES4_ADDR(x),v)
#define HWIO_PMIC_ARB0_PRIORITIES4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB0_PRIORITIES4_ADDR(x),m,v,HWIO_PMIC_ARB0_PRIORITIES4_IN(x))
#define HWIO_PMIC_ARB0_PRIORITIES4_PORT_PRIORITY_BMSK                                             0x1f
#define HWIO_PMIC_ARB0_PRIORITIES4_PORT_PRIORITY_SHFT                                                0

#define HWIO_PMIC_ARB0_PRIORITIES5_ADDR(x)                                                  ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x114)
#define HWIO_PMIC_ARB0_PRIORITIES5_OFFS                                                     (0x114)
#define HWIO_PMIC_ARB0_PRIORITIES5_RMSK                                                           0x1f
#define HWIO_PMIC_ARB0_PRIORITIES5_IN(x)            \
                in_dword(HWIO_PMIC_ARB0_PRIORITIES5_ADDR(x))
#define HWIO_PMIC_ARB0_PRIORITIES5_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB0_PRIORITIES5_ADDR(x), m)
#define HWIO_PMIC_ARB0_PRIORITIES5_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB0_PRIORITIES5_ADDR(x),v)
#define HWIO_PMIC_ARB0_PRIORITIES5_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB0_PRIORITIES5_ADDR(x),m,v,HWIO_PMIC_ARB0_PRIORITIES5_IN(x))
#define HWIO_PMIC_ARB0_PRIORITIES5_PORT_PRIORITY_BMSK                                             0x1f
#define HWIO_PMIC_ARB0_PRIORITIES5_PORT_PRIORITY_SHFT                                                0

#define HWIO_PMIC_ARB0_PRIORITIES6_ADDR(x)                                                  ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x118)
#define HWIO_PMIC_ARB0_PRIORITIES6_OFFS                                                     (0x118)
#define HWIO_PMIC_ARB0_PRIORITIES6_RMSK                                                           0x1f
#define HWIO_PMIC_ARB0_PRIORITIES6_IN(x)            \
                in_dword(HWIO_PMIC_ARB0_PRIORITIES6_ADDR(x))
#define HWIO_PMIC_ARB0_PRIORITIES6_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB0_PRIORITIES6_ADDR(x), m)
#define HWIO_PMIC_ARB0_PRIORITIES6_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB0_PRIORITIES6_ADDR(x),v)
#define HWIO_PMIC_ARB0_PRIORITIES6_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB0_PRIORITIES6_ADDR(x),m,v,HWIO_PMIC_ARB0_PRIORITIES6_IN(x))
#define HWIO_PMIC_ARB0_PRIORITIES6_PORT_PRIORITY_BMSK                                             0x1f
#define HWIO_PMIC_ARB0_PRIORITIES6_PORT_PRIORITY_SHFT                                                0

#define HWIO_PMIC_ARB1_PRIORITIES0_ADDR(x)                                                  ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x180)
#define HWIO_PMIC_ARB1_PRIORITIES0_OFFS                                                     (0x180)
#define HWIO_PMIC_ARB1_PRIORITIES0_RMSK                                                            0x3
#define HWIO_PMIC_ARB1_PRIORITIES0_IN(x)            \
                in_dword(HWIO_PMIC_ARB1_PRIORITIES0_ADDR(x))
#define HWIO_PMIC_ARB1_PRIORITIES0_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB1_PRIORITIES0_ADDR(x), m)
#define HWIO_PMIC_ARB1_PRIORITIES0_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB1_PRIORITIES0_ADDR(x),v)
#define HWIO_PMIC_ARB1_PRIORITIES0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB1_PRIORITIES0_ADDR(x),m,v,HWIO_PMIC_ARB1_PRIORITIES0_IN(x))
#define HWIO_PMIC_ARB1_PRIORITIES0_PORT_PRIORITY_BMSK                                              0x3
#define HWIO_PMIC_ARB1_PRIORITIES0_PORT_PRIORITY_SHFT                                                0

#define HWIO_PMIC_ARB1_PRIORITIES1_ADDR(x)                                                  ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x184)
#define HWIO_PMIC_ARB1_PRIORITIES1_OFFS                                                     (0x184)
#define HWIO_PMIC_ARB1_PRIORITIES1_RMSK                                                            0x3
#define HWIO_PMIC_ARB1_PRIORITIES1_IN(x)            \
                in_dword(HWIO_PMIC_ARB1_PRIORITIES1_ADDR(x))
#define HWIO_PMIC_ARB1_PRIORITIES1_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB1_PRIORITIES1_ADDR(x), m)
#define HWIO_PMIC_ARB1_PRIORITIES1_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB1_PRIORITIES1_ADDR(x),v)
#define HWIO_PMIC_ARB1_PRIORITIES1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB1_PRIORITIES1_ADDR(x),m,v,HWIO_PMIC_ARB1_PRIORITIES1_IN(x))
#define HWIO_PMIC_ARB1_PRIORITIES1_PORT_PRIORITY_BMSK                                              0x3
#define HWIO_PMIC_ARB1_PRIORITIES1_PORT_PRIORITY_SHFT                                                0

#define HWIO_PMIC_ARB1_PRIORITIES2_ADDR(x)                                                  ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x188)
#define HWIO_PMIC_ARB1_PRIORITIES2_OFFS                                                     (0x188)
#define HWIO_PMIC_ARB1_PRIORITIES2_RMSK                                                            0x3
#define HWIO_PMIC_ARB1_PRIORITIES2_IN(x)            \
                in_dword(HWIO_PMIC_ARB1_PRIORITIES2_ADDR(x))
#define HWIO_PMIC_ARB1_PRIORITIES2_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB1_PRIORITIES2_ADDR(x), m)
#define HWIO_PMIC_ARB1_PRIORITIES2_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB1_PRIORITIES2_ADDR(x),v)
#define HWIO_PMIC_ARB1_PRIORITIES2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB1_PRIORITIES2_ADDR(x),m,v,HWIO_PMIC_ARB1_PRIORITIES2_IN(x))
#define HWIO_PMIC_ARB1_PRIORITIES2_PORT_PRIORITY_BMSK                                              0x3
#define HWIO_PMIC_ARB1_PRIORITIES2_PORT_PRIORITY_SHFT                                                0

#define HWIO_PMIC_ARBm_PVC_INTF_CTL_ADDR(base,m)                                            ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0X200 + (0x100*(m)))
#define HWIO_PMIC_ARBm_PVC_INTF_CTL_OFFS(m)                                                 (0X200 + (0x100*(m)))
#define HWIO_PMIC_ARBm_PVC_INTF_CTL_RMSK                                                           0x1
#define HWIO_PMIC_ARBm_PVC_INTF_CTL_INI(base,m)                \
                in_dword_masked(HWIO_PMIC_ARBm_PVC_INTF_CTL_ADDR(base,m), HWIO_PMIC_ARBm_PVC_INTF_CTL_RMSK)
#define HWIO_PMIC_ARBm_PVC_INTF_CTL_INMI(base,m,mask)        \
                in_dword_masked(HWIO_PMIC_ARBm_PVC_INTF_CTL_ADDR(base,m), mask)
#define HWIO_PMIC_ARBm_PVC_INTF_CTL_OUTI(base,m,val)        \
                out_dword(HWIO_PMIC_ARBm_PVC_INTF_CTL_ADDR(base,m),val)
#define HWIO_PMIC_ARBm_PVC_INTF_CTL_OUTMI(base,m,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARBm_PVC_INTF_CTL_ADDR(base,m),mask,val,HWIO_PMIC_ARBm_PVC_INTF_CTL_INI(base,m))
#define HWIO_PMIC_ARBm_PVC_INTF_CTL_PVC_INTF_EN_BMSK                                               0x1
#define HWIO_PMIC_ARBm_PVC_INTF_CTL_PVC_INTF_EN_SHFT                                                 0

#define HWIO_PMIC_ARBm_PVC_INTF_STATUS_ADDR(base,m)                                         ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0X204 + (0x100*(m)))
#define HWIO_PMIC_ARBm_PVC_INTF_STATUS_OFFS(m)                                              (0X204 + (0x100*(m)))
#define HWIO_PMIC_ARBm_PVC_INTF_STATUS_RMSK                                                        0x1
#define HWIO_PMIC_ARBm_PVC_INTF_STATUS_INI(base,m)                \
                in_dword_masked(HWIO_PMIC_ARBm_PVC_INTF_STATUS_ADDR(base,m), HWIO_PMIC_ARBm_PVC_INTF_STATUS_RMSK)
#define HWIO_PMIC_ARBm_PVC_INTF_STATUS_INMI(base,m,mask)        \
                in_dword_masked(HWIO_PMIC_ARBm_PVC_INTF_STATUS_ADDR(base,m), mask)
#define HWIO_PMIC_ARBm_PVC_INTF_STATUS_PVC_INTF_BUSY_BMSK                                          0x1
#define HWIO_PMIC_ARBm_PVC_INTF_STATUS_PVC_INTF_BUSY_SHFT                                            0

#define HWIO_PMIC_ARB0_PVC_PORTn_CTL_ADDR(base,n)                                           ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0X208 + (0x4*(n)))
#define HWIO_PMIC_ARB0_PVC_PORTn_CTL_OFFS(n)                                                (0X208 + (0x4*(n)))
#define HWIO_PMIC_ARB0_PVC_PORTn_CTL_RMSK                                                          0x3
#define HWIO_PMIC_ARB0_PVC_PORTn_CTL_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_ARB0_PVC_PORTn_CTL_ADDR(base,n), HWIO_PMIC_ARB0_PVC_PORTn_CTL_RMSK)
#define HWIO_PMIC_ARB0_PVC_PORTn_CTL_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB0_PVC_PORTn_CTL_ADDR(base,n), mask)
#define HWIO_PMIC_ARB0_PVC_PORTn_CTL_OUTI(base,n,val)        \
                out_dword(HWIO_PMIC_ARB0_PVC_PORTn_CTL_ADDR(base,n),val)
#define HWIO_PMIC_ARB0_PVC_PORTn_CTL_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARB0_PVC_PORTn_CTL_ADDR(base,n),mask,val,HWIO_PMIC_ARB0_PVC_PORTn_CTL_INI(base,n))
#define HWIO_PMIC_ARB0_PVC_PORTn_CTL_SPMI_PRIORITY_BMSK                                            0x2
#define HWIO_PMIC_ARB0_PVC_PORTn_CTL_SPMI_PRIORITY_SHFT                                              1
#define HWIO_PMIC_ARB0_PVC_PORTn_CTL_PVC_PORT_EN_BMSK                                              0x1
#define HWIO_PMIC_ARB0_PVC_PORTn_CTL_PVC_PORT_EN_SHFT                                                0

#define HWIO_PMIC_ARB0_PVC_PORTn_STATUS_ADDR(base,n)                                        ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0X288 + (0x4*(n)))
#define HWIO_PMIC_ARB0_PVC_PORTn_STATUS_OFFS(n)                                             (0X288 + (0x4*(n)))
#define HWIO_PMIC_ARB0_PVC_PORTn_STATUS_RMSK                                                       0x3
#define HWIO_PMIC_ARB0_PVC_PORTn_STATUS_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_ARB0_PVC_PORTn_STATUS_ADDR(base,n), HWIO_PMIC_ARB0_PVC_PORTn_STATUS_RMSK)
#define HWIO_PMIC_ARB0_PVC_PORTn_STATUS_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB0_PVC_PORTn_STATUS_ADDR(base,n), mask)
#define HWIO_PMIC_ARB0_PVC_PORTn_STATUS_PVC_PORT_FAILURE_BMSK                                      0x2
#define HWIO_PMIC_ARB0_PVC_PORTn_STATUS_PVC_PORT_FAILURE_SHFT                                        1
#define HWIO_PMIC_ARB0_PVC_PORTn_STATUS_PVC_PORT_BUSY_BMSK                                         0x1
#define HWIO_PMIC_ARB0_PVC_PORTn_STATUS_PVC_PORT_BUSY_SHFT                                           0

#define HWIO_PMIC_ARB0_PVCn_ADDRm_ADDR(base,n,m)                                            ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0X400 + (0x40*(n)) + (0x4*(m)))
#define HWIO_PMIC_ARB0_PVCn_ADDRm_OFFS(n,m)                                                 (0X400 + (0x40*(n)) + (0x4*(m)))
#define HWIO_PMIC_ARB0_PVCn_ADDRm_RMSK                                                         0xfffff
#define HWIO_PMIC_ARB0_PVCn_ADDRm_INI2(base,n,m)                \
                in_dword_masked(HWIO_PMIC_ARB0_PVCn_ADDRm_ADDR(base,n,m), HWIO_PMIC_ARB0_PVCn_ADDRm_RMSK)
#define HWIO_PMIC_ARB0_PVCn_ADDRm_INMI2(base,n,m,mask)        \
                in_dword_masked(HWIO_PMIC_ARB0_PVCn_ADDRm_ADDR(base,n,m), mask)
#define HWIO_PMIC_ARB0_PVCn_ADDRm_OUTI2(base,n,m,val)        \
                out_dword(HWIO_PMIC_ARB0_PVCn_ADDRm_ADDR(base,n,m),val)
#define HWIO_PMIC_ARB0_PVCn_ADDRm_OUTMI2(base,n,m,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARB0_PVCn_ADDRm_ADDR(base,n,m),mask,val,HWIO_PMIC_ARB0_PVCn_ADDRm_INI2(base,n,m))
#define HWIO_PMIC_ARB0_PVCn_ADDRm_SID_BMSK                                                     0xf0000
#define HWIO_PMIC_ARB0_PVCn_ADDRm_SID_SHFT                                                          16
#define HWIO_PMIC_ARB0_PVCn_ADDRm_ADDRESS_BMSK                                                  0xffff
#define HWIO_PMIC_ARB0_PVCn_ADDRm_ADDRESS_SHFT                                                       0

#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_ADDR(x)                                                ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x1000)
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_OFFS                                                   (0x1000)
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_RMSK                                                          0x1
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_IN(x)            \
                in_dword(HWIO_PMIC_ARB_VRM_S_INTF_CTL_ADDR(x))
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_ARB_VRM_S_INTF_CTL_ADDR(x), m)
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_OUT(x, v)            \
                out_dword(HWIO_PMIC_ARB_VRM_S_INTF_CTL_ADDR(x),v)
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB_VRM_S_INTF_CTL_ADDR(x),m,v,HWIO_PMIC_ARB_VRM_S_INTF_CTL_IN(x))
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_VRM_S_INTF_EN_BMSK                                            0x1
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_VRM_S_INTF_EN_SHFT                                              0

#define HWIO_PMIC_ARBm_VRM_S_INTF_STATUS_ADDR(base,m)                                       ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0X1004 + (0x100*(m)))
#define HWIO_PMIC_ARBm_VRM_S_INTF_STATUS_OFFS(m)                                            (0X1004 + (0x100*(m)))
#define HWIO_PMIC_ARBm_VRM_S_INTF_STATUS_RMSK                                                      0x1
#define HWIO_PMIC_ARBm_VRM_S_INTF_STATUS_INI(base,m)                \
                in_dword_masked(HWIO_PMIC_ARBm_VRM_S_INTF_STATUS_ADDR(base,m), HWIO_PMIC_ARBm_VRM_S_INTF_STATUS_RMSK)
#define HWIO_PMIC_ARBm_VRM_S_INTF_STATUS_INMI(base,m,mask)        \
                in_dword_masked(HWIO_PMIC_ARBm_VRM_S_INTF_STATUS_ADDR(base,m), mask)
#define HWIO_PMIC_ARBm_VRM_S_INTF_STATUS_VRM_S_INTF_BUSY_BMSK                                      0x1
#define HWIO_PMIC_ARBm_VRM_S_INTF_STATUS_VRM_S_INTF_BUSY_SHFT                                        0

#define HWIO_PMIC_ARBm_VRM_S_PORT_CTL_ADDR(base,m)                                          ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0X1008 + (0x100*(m)))
#define HWIO_PMIC_ARBm_VRM_S_PORT_CTL_OFFS(m)                                               (0X1008 + (0x100*(m)))
#define HWIO_PMIC_ARBm_VRM_S_PORT_CTL_RMSK                                                         0x3
#define HWIO_PMIC_ARBm_VRM_S_PORT_CTL_INI(base,m)                \
                in_dword_masked(HWIO_PMIC_ARBm_VRM_S_PORT_CTL_ADDR(base,m), HWIO_PMIC_ARBm_VRM_S_PORT_CTL_RMSK)
#define HWIO_PMIC_ARBm_VRM_S_PORT_CTL_INMI(base,m,mask)        \
                in_dword_masked(HWIO_PMIC_ARBm_VRM_S_PORT_CTL_ADDR(base,m), mask)
#define HWIO_PMIC_ARBm_VRM_S_PORT_CTL_OUTI(base,m,val)        \
                out_dword(HWIO_PMIC_ARBm_VRM_S_PORT_CTL_ADDR(base,m),val)
#define HWIO_PMIC_ARBm_VRM_S_PORT_CTL_OUTMI(base,m,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARBm_VRM_S_PORT_CTL_ADDR(base,m),mask,val,HWIO_PMIC_ARBm_VRM_S_PORT_CTL_INI(base,m))
#define HWIO_PMIC_ARBm_VRM_S_PORT_CTL_SPMI_PRIORITY_BMSK                                           0x2
#define HWIO_PMIC_ARBm_VRM_S_PORT_CTL_SPMI_PRIORITY_SHFT                                             1
#define HWIO_PMIC_ARBm_VRM_S_PORT_CTL_VRM_S_PORT_EN_BMSK                                           0x1
#define HWIO_PMIC_ARBm_VRM_S_PORT_CTL_VRM_S_PORT_EN_SHFT                                             0

#define HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_ADDR(base,m)                                       ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0X100C + (0x100*(m)))
#define HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_OFFS(m)                                            (0X100C + (0x100*(m)))
#define HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_RMSK                                                      0x3
#define HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_INI(base,m)                \
                in_dword_masked(HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_ADDR(base,m), HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_RMSK)
#define HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_INMI(base,m,mask)        \
                in_dword_masked(HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_ADDR(base,m), mask)
#define HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_VRM_S_PORT_FAILURE_BMSK                                   0x2
#define HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_VRM_S_PORT_FAILURE_SHFT                                     1
#define HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_VRM_S_PORT_BUSY_BMSK                                      0x1
#define HWIO_PMIC_ARBm_VRM_S_PORT_STATUS_VRM_S_PORT_BUSY_SHFT                                        0

#define HWIO_PMIC_ARB_VRM_S_ADDRw_ADDR(base,w)                                              ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0X1400 + (0x4*(w)))
#define HWIO_PMIC_ARB_VRM_S_ADDRw_OFFS(w)                                                   (0X1400 + (0x4*(w)))
#define HWIO_PMIC_ARB_VRM_S_ADDRw_RMSK                                                        0x1fff00
#define HWIO_PMIC_ARB_VRM_S_ADDRw_INI(base,w)                \
                in_dword_masked(HWIO_PMIC_ARB_VRM_S_ADDRw_ADDR(base,w), HWIO_PMIC_ARB_VRM_S_ADDRw_RMSK)
#define HWIO_PMIC_ARB_VRM_S_ADDRw_INMI(base,w,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_VRM_S_ADDRw_ADDR(base,w), mask)
#define HWIO_PMIC_ARB_VRM_S_ADDRw_OUTI(base,w,val)        \
                out_dword(HWIO_PMIC_ARB_VRM_S_ADDRw_ADDR(base,w),val)
#define HWIO_PMIC_ARB_VRM_S_ADDRw_OUTMI(base,w,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARB_VRM_S_ADDRw_ADDR(base,w),mask,val,HWIO_PMIC_ARB_VRM_S_ADDRw_INI(base,w))
#define HWIO_PMIC_ARB_VRM_S_ADDRw_BUS_INST_BMSK                                               0x100000
#define HWIO_PMIC_ARB_VRM_S_ADDRw_BUS_INST_SHFT                                                     20
#define HWIO_PMIC_ARB_VRM_S_ADDRw_SID_BMSK                                                     0xf0000
#define HWIO_PMIC_ARB_VRM_S_ADDRw_SID_SHFT                                                          16
#define HWIO_PMIC_ARB_VRM_S_ADDRw_PPID_BMSK                                                     0xff00
#define HWIO_PMIC_ARB_VRM_S_ADDRw_PPID_SHFT                                                          8

#define HWIO_PMIC_ARB_REG_ADDRp_ADDR(base,p)                                                ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0X2000 + (0x4*(p)))
#define HWIO_PMIC_ARB_REG_ADDRp_OFFS(p)                                                     (0X2000 + (0x4*(p)))
#define HWIO_PMIC_ARB_REG_ADDRp_RMSK                                                         0x10fff00
#define HWIO_PMIC_ARB_REG_ADDRp_INI(base,p)                \
                in_dword_masked(HWIO_PMIC_ARB_REG_ADDRp_ADDR(base,p), HWIO_PMIC_ARB_REG_ADDRp_RMSK)
#define HWIO_PMIC_ARB_REG_ADDRp_INMI(base,p,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_REG_ADDRp_ADDR(base,p), mask)
#define HWIO_PMIC_ARB_REG_ADDRp_OUTI(base,p,val)        \
                out_dword(HWIO_PMIC_ARB_REG_ADDRp_ADDR(base,p),val)
#define HWIO_PMIC_ARB_REG_ADDRp_OUTMI(base,p,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARB_REG_ADDRp_ADDR(base,p),mask,val,HWIO_PMIC_ARB_REG_ADDRp_INI(base,p))
#define HWIO_PMIC_ARB_REG_ADDRp_IRQ_OWN_BMSK                                                 0x1000000
#define HWIO_PMIC_ARB_REG_ADDRp_IRQ_OWN_SHFT                                                        24
#define HWIO_PMIC_ARB_REG_ADDRp_SID_BMSK                                                       0xf0000
#define HWIO_PMIC_ARB_REG_ADDRp_SID_SHFT                                                            16
#define HWIO_PMIC_ARB_REG_ADDRp_ADDRESS_BMSK                                                    0xff00
#define HWIO_PMIC_ARB_REG_ADDRp_ADDRESS_SHFT                                                         8

/*----------------------------------------------------------------------------
 * MODULE: PMIC_ARB_CORE_REGISTERS
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS                                          (PMIC_ARB_BASE_OFFS + 0x0100000)

#define HWIO_PMIC_ARB_CHNLn_CMD_ADDR(base,n)                                           ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X0 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_CMD_OFFS(n)                                                (0X0 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_CMD_RMSK                                                   0xfc000ff7
#define HWIO_PMIC_ARB_CHNLn_CMD_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_CMD_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_CMD_RMSK)
#define HWIO_PMIC_ARB_CHNLn_CMD_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_CMD_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_CMD_OUTI(base,n,val)        \
                out_dword(HWIO_PMIC_ARB_CHNLn_CMD_ADDR(base,n),val)
#define HWIO_PMIC_ARB_CHNLn_CMD_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARB_CHNLn_CMD_ADDR(base,n),mask,val,HWIO_PMIC_ARB_CHNLn_CMD_INI(base,n))
#define HWIO_PMIC_ARB_CHNLn_CMD_OPCODE_BMSK                                            0xf8000000
#define HWIO_PMIC_ARB_CHNLn_CMD_OPCODE_SHFT                                                    27
#define HWIO_PMIC_ARB_CHNLn_CMD_PRIORITY_BMSK                                           0x4000000
#define HWIO_PMIC_ARB_CHNLn_CMD_PRIORITY_SHFT                                                  26
#define HWIO_PMIC_ARB_CHNLn_CMD_ADDRESS_OFFSET_BMSK                                         0xff0
#define HWIO_PMIC_ARB_CHNLn_CMD_ADDRESS_OFFSET_SHFT                                             4
#define HWIO_PMIC_ARB_CHNLn_CMD_BYTE_CNT_BMSK                                                 0x7
#define HWIO_PMIC_ARB_CHNLn_CMD_BYTE_CNT_SHFT                                                   0

#define HWIO_PMIC_ARB_CHNLn_CONFIG_ADDR(base,n)                                        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X4 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_CONFIG_OFFS(n)                                             (0X4 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_CONFIG_RMSK                                                       0x1
#define HWIO_PMIC_ARB_CHNLn_CONFIG_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_CONFIG_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_CONFIG_RMSK)
#define HWIO_PMIC_ARB_CHNLn_CONFIG_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_CONFIG_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_CONFIG_OUTI(base,n,val)        \
                out_dword(HWIO_PMIC_ARB_CHNLn_CONFIG_ADDR(base,n),val)
#define HWIO_PMIC_ARB_CHNLn_CONFIG_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARB_CHNLn_CONFIG_ADDR(base,n),mask,val,HWIO_PMIC_ARB_CHNLn_CONFIG_INI(base,n))
#define HWIO_PMIC_ARB_CHNLn_CONFIG_IRQ_EN_BMSK                                                0x1
#define HWIO_PMIC_ARB_CHNLn_CONFIG_IRQ_EN_SHFT                                                  0

#define HWIO_PMIC_ARB_CHNLn_STATUS_ADDR(base,n)                                        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X8 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_STATUS_OFFS(n)                                             (0X8 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_STATUS_RMSK                                                      0x1f
#define HWIO_PMIC_ARB_CHNLn_STATUS_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_STATUS_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_STATUS_RMSK)
#define HWIO_PMIC_ARB_CHNLn_STATUS_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_STATUS_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_STATUS_SW_WDT_RST_BMSK                                           0x10
#define HWIO_PMIC_ARB_CHNLn_STATUS_SW_WDT_RST_SHFT                                              4
#define HWIO_PMIC_ARB_CHNLn_STATUS_DROPPED_BMSK                                               0x8
#define HWIO_PMIC_ARB_CHNLn_STATUS_DROPPED_SHFT                                                 3
#define HWIO_PMIC_ARB_CHNLn_STATUS_DENIED_BMSK                                                0x4
#define HWIO_PMIC_ARB_CHNLn_STATUS_DENIED_SHFT                                                  2
#define HWIO_PMIC_ARB_CHNLn_STATUS_FAILURE_BMSK                                               0x2
#define HWIO_PMIC_ARB_CHNLn_STATUS_FAILURE_SHFT                                                 1
#define HWIO_PMIC_ARB_CHNLn_STATUS_DONE_BMSK                                                  0x1
#define HWIO_PMIC_ARB_CHNLn_STATUS_DONE_SHFT                                                    0

#define HWIO_PMIC_ARB_CHNLn_WDATA0_ADDR(base,n)                                        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X10 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_WDATA0_OFFS(n)                                             (0X10 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_WDATA0_RMSK                                                0xffffffff
#define HWIO_PMIC_ARB_CHNLn_WDATA0_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_WDATA0_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_WDATA0_RMSK)
#define HWIO_PMIC_ARB_CHNLn_WDATA0_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_WDATA0_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_WDATA0_OUTI(base,n,val)        \
                out_dword(HWIO_PMIC_ARB_CHNLn_WDATA0_ADDR(base,n),val)
#define HWIO_PMIC_ARB_CHNLn_WDATA0_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARB_CHNLn_WDATA0_ADDR(base,n),mask,val,HWIO_PMIC_ARB_CHNLn_WDATA0_INI(base,n))
#define HWIO_PMIC_ARB_CHNLn_WDATA0_DATA_BMSK                                           0xffffffff
#define HWIO_PMIC_ARB_CHNLn_WDATA0_DATA_SHFT                                                    0

#define HWIO_PMIC_ARB_CHNLn_WDATA1_ADDR(base,n)                                        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X14 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_WDATA1_OFFS(n)                                             (0X14 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_WDATA1_RMSK                                                0xffffffff
#define HWIO_PMIC_ARB_CHNLn_WDATA1_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_WDATA1_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_WDATA1_RMSK)
#define HWIO_PMIC_ARB_CHNLn_WDATA1_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_WDATA1_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_WDATA1_OUTI(base,n,val)        \
                out_dword(HWIO_PMIC_ARB_CHNLn_WDATA1_ADDR(base,n),val)
#define HWIO_PMIC_ARB_CHNLn_WDATA1_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARB_CHNLn_WDATA1_ADDR(base,n),mask,val,HWIO_PMIC_ARB_CHNLn_WDATA1_INI(base,n))
#define HWIO_PMIC_ARB_CHNLn_WDATA1_DATA_BMSK                                           0xffffffff
#define HWIO_PMIC_ARB_CHNLn_WDATA1_DATA_SHFT                                                    0

#define HWIO_PMIC_ARB_CHNLn_RDATA0_ADDR(base,n)                                        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X18 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_RDATA0_OFFS(n)                                             (0X18 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_RDATA0_RMSK                                                0xffffffff
#define HWIO_PMIC_ARB_CHNLn_RDATA0_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA0_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_RDATA0_RMSK)
#define HWIO_PMIC_ARB_CHNLn_RDATA0_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA0_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_RDATA0_DATA_BMSK                                           0xffffffff
#define HWIO_PMIC_ARB_CHNLn_RDATA0_DATA_SHFT                                                    0

#define HWIO_PMIC_ARB_CHNLn_RDATA1_ADDR(base,n)                                        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X1C + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_RDATA1_OFFS(n)                                             (0X1C + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_RDATA1_RMSK                                                0xffffffff
#define HWIO_PMIC_ARB_CHNLn_RDATA1_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA1_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_RDATA1_RMSK)
#define HWIO_PMIC_ARB_CHNLn_RDATA1_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA1_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_RDATA1_DATA_BMSK                                           0xffffffff
#define HWIO_PMIC_ARB_CHNLn_RDATA1_DATA_SHFT                                                    0

#define HWIO_PMIC_ARB_CHNLn_RDATA2_ADDR(base,n)                                        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X20 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_RDATA2_OFFS(n)                                             (0X20 + (0x1000*(n)))
#define HWIO_PMIC_ARB_CHNLn_RDATA2_RMSK                                                    0xffff
#define HWIO_PMIC_ARB_CHNLn_RDATA2_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA2_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_RDATA2_RMSK)
#define HWIO_PMIC_ARB_CHNLn_RDATA2_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA2_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_RDATA2_DATA_BMSK                                               0xffff
#define HWIO_PMIC_ARB_CHNLn_RDATA2_DATA_SHFT                                                    0

#define HWIO_SPMI_PIC_ACC_ENABLEn_ADDR(base,n)                                         ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X100 + (0x1000*(n)))
#define HWIO_SPMI_PIC_ACC_ENABLEn_OFFS(n)                                              (0X100 + (0x1000*(n)))
#define HWIO_SPMI_PIC_ACC_ENABLEn_RMSK                                                        0x1
#define HWIO_SPMI_PIC_ACC_ENABLEn_INI(base,n)                \
                in_dword_masked(HWIO_SPMI_PIC_ACC_ENABLEn_ADDR(base,n), HWIO_SPMI_PIC_ACC_ENABLEn_RMSK)
#define HWIO_SPMI_PIC_ACC_ENABLEn_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI_PIC_ACC_ENABLEn_ADDR(base,n), mask)
#define HWIO_SPMI_PIC_ACC_ENABLEn_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI_PIC_ACC_ENABLEn_ADDR(base,n),val)
#define HWIO_SPMI_PIC_ACC_ENABLEn_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SPMI_PIC_ACC_ENABLEn_ADDR(base,n),mask,val,HWIO_SPMI_PIC_ACC_ENABLEn_INI(base,n))
#define HWIO_SPMI_PIC_ACC_ENABLEn_INT_ACC_ENABLE_BMSK                                         0x1
#define HWIO_SPMI_PIC_ACC_ENABLEn_INT_ACC_ENABLE_SHFT                                           0

#define HWIO_SPMI_PIC_IRQ_STATUSn_ADDR(base,n)                                         ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X104 + (0x1000*(n)))
#define HWIO_SPMI_PIC_IRQ_STATUSn_OFFS(n)                                              (0X104 + (0x1000*(n)))
#define HWIO_SPMI_PIC_IRQ_STATUSn_RMSK                                                       0xff
#define HWIO_SPMI_PIC_IRQ_STATUSn_INI(base,n)                \
                in_dword_masked(HWIO_SPMI_PIC_IRQ_STATUSn_ADDR(base,n), HWIO_SPMI_PIC_IRQ_STATUSn_RMSK)
#define HWIO_SPMI_PIC_IRQ_STATUSn_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SPMI_PIC_IRQ_STATUSn_ADDR(base,n), mask)
#define HWIO_SPMI_PIC_IRQ_STATUSn_INT_STATUS_BMSK                                            0xff
#define HWIO_SPMI_PIC_IRQ_STATUSn_INT_STATUS_SHFT                                               0

#define HWIO_SPMI_PIC_IRQ_CLEARn_ADDR(base,n)                                          ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X108 + (0x1000*(n)))
#define HWIO_SPMI_PIC_IRQ_CLEARn_OFFS(n)                                               (0X108 + (0x1000*(n)))
#define HWIO_SPMI_PIC_IRQ_CLEARn_RMSK                                                        0xff
#define HWIO_SPMI_PIC_IRQ_CLEARn_OUTI(base,n,val)        \
                out_dword(HWIO_SPMI_PIC_IRQ_CLEARn_ADDR(base,n),val)
#define HWIO_SPMI_PIC_IRQ_CLEARn_INT_CLEAR_BMSK                                              0xff
#define HWIO_SPMI_PIC_IRQ_CLEARn_INT_CLEAR_SHFT                                                 0

#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ADDR(base,n)                                  ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0X10C + (0x1000*(n)))
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_OFFS(n)                                       (0X10C + (0x1000*(n)))
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_RMSK                                               0xfff
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_INI(base,n)                \
                in_dword_masked(HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ADDR(base,n), HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_RMSK)
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ADDR(base,n), mask)
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ARBITER_DISCONNECTED_BMSK                          0x800
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ARBITER_DISCONNECTED_SHFT                             11
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ARBITER_CONNECTED_BMSK                             0x400
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ARBITER_CONNECTED_SHFT                                10
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_PERIPH_IRQ_LOST_BMSK                               0x200
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_PERIPH_IRQ_LOST_SHFT                                   9
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_UNEXPECTED_SSC_BMSK                                0x100
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_UNEXPECTED_SSC_SHFT                                    8
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                0x80
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                   7
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                 0x40
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                    6
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_FALSE_MASTER_ARBITRATION_WIN_BMSK                   0x20
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_FALSE_MASTER_ARBITRATION_WIN_SHFT                      5
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_FALSE_BUS_REQ_BMSK                                  0x10
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_FALSE_BUS_REQ_SHFT                                     4
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_UNSUPPORTED_COMMAND_BMSK                             0x8
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_UNSUPPORTED_COMMAND_SHFT                               3
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                    0x4
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                      2
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                    0x2
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                      1
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                   0x1
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                     0

/*----------------------------------------------------------------------------
 * MODULE: PMIC_ARB_CORE_REGISTERS_OBS
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS                                        (PMIC_ARB_BASE_OFFS + 0x40000)

#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n)                                      ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0X0 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OFFS(q,n)                                           (0X0 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_RMSK                                                0xfc000ff7
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_INI2(base,q,n)                \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_CMD_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_INMI2(base,q,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OUTI2(base,q,n,val)        \
                out_dword(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n),val)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OUTMI2(base,q,n,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n),mask,val,HWIO_PMIC_ARB_OBSq_CHNLn_CMD_INI2(base,q,n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OPCODE_BMSK                                         0xf8000000
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OPCODE_SHFT                                                 27
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_PRIORITY_BMSK                                        0x4000000
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_PRIORITY_SHFT                                               26
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDRESS_BMSK                                             0xff0
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDRESS_SHFT                                                 4
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_BYTE_CNT_BMSK                                              0x7
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_BYTE_CNT_SHFT                                                0

#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n)                                   ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0X4 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_OFFS(q,n)                                        (0X4 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_RMSK                                                    0x1
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_INI2(base,q,n)                \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_INMI2(base,q,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_OUTI2(base,q,n,val)        \
                out_dword(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n),val)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_OUTMI2(base,q,n,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n),mask,val,HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_INI2(base,q,n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_IRQ_EN_BMSK                                             0x1
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_IRQ_EN_SHFT                                               0

#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR(base,q,n)                                   ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0X8 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_OFFS(q,n)                                        (0X8 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_RMSK                                                   0x1f
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_INI2(base,q,n)                \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_INMI2(base,q,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_SW_WDT_RST_BMSK                                        0x10
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_SW_WDT_RST_SHFT                                           4
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DROPPED_BMSK                                            0x8
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DROPPED_SHFT                                              3
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DENIED_BMSK                                             0x4
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DENIED_SHFT                                               2
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_FAILURE_BMSK                                            0x2
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_FAILURE_SHFT                                              1
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DONE_BMSK                                               0x1
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DONE_SHFT                                                 0

#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ADDR(base,q,n)                                ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0XC + (0x8000*(q)) + (0x20*(n)))
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_OFFS(q,n)                                     (0XC + (0x8000*(q)) + (0x20*(n)))
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_RMSK                                               0xfff
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_INI2(base,q,n)                \
                in_dword_masked(HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ADDR(base,q,n), HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_RMSK)
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_INMI2(base,q,n,mask)        \
                in_dword_masked(HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ADDR(base,q,n), mask)
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ARBITER_DISCONNECTED_BMSK                          0x800
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ARBITER_DISCONNECTED_SHFT                             11
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ARBITER_CONNECTED_BMSK                             0x400
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ARBITER_CONNECTED_SHFT                                10
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_PERIPH_IRQ_LOST_BMSK                               0x200
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_PERIPH_IRQ_LOST_SHFT                                   9
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_UNEXPECTED_SSC_BMSK                                0x100
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_UNEXPECTED_SSC_SHFT                                    8
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                0x80
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                   7
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                 0x40
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                    6
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_FALSE_MASTER_ARBITRATION_WIN_BMSK                   0x20
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_FALSE_MASTER_ARBITRATION_WIN_SHFT                      5
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_FALSE_BUS_REQ_BMSK                                  0x10
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_FALSE_BUS_REQ_SHFT                                     4
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_UNSUPPORTED_COMMAND_BMSK                             0x8
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_UNSUPPORTED_COMMAND_SHFT                               3
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                    0x4
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                      2
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                    0x2
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                      1
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                   0x1
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                     0

#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA0_ADDR(base,q,n)                                   ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0X10 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA0_OFFS(q,n)                                        (0X10 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA0_RMSK                                             0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA0_INI2(base,q,n)                \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_WDATA0_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_WDATA0_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA0_INMI2(base,q,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_WDATA0_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA0_DATA_BMSK                                        0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA0_DATA_SHFT                                                 0

#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA1_ADDR(base,q,n)                                   ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0X14 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA1_OFFS(q,n)                                        (0X14 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA1_RMSK                                             0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA1_INI2(base,q,n)                \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_WDATA1_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_WDATA1_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA1_INMI2(base,q,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_WDATA1_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA1_DATA_BMSK                                        0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_WDATA1_DATA_SHFT                                                 0

#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR(base,q,n)                                   ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0X18 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_OFFS(q,n)                                        (0X18 + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_RMSK                                             0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_INI2(base,q,n)                \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_INMI2(base,q,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_DATA_BMSK                                        0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_DATA_SHFT                                                 0

#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR(base,q,n)                                   ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0X1C + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_OFFS(q,n)                                        (0X1C + (0x8000*(q)) + (0x20*(n)))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_RMSK                                             0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_INI2(base,q,n)                \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_INMI2(base,q,n,mask)        \
                in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_DATA_BMSK                                        0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_DATA_SHFT                                                 0

/*----------------------------------------------------------------------------
 * MODULE: PMIC_ARB_MGPI
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_MGPI_REG_BASE_OFFS                                   (PMIC_ARB_BASE_OFFS + 0x06000)

#define HWIO_PMIC_MGPI_TRIG_CONFIGn_ADDR(base,n)                      ((base) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0X0 + (0x8*(n)))
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_OFFS(n)                           (0X0 + (0x8*(n)))
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_RMSK                               0xfff0fff
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_CONFIGn_ADDR(base,n), HWIO_PMIC_MGPI_TRIG_CONFIGn_RMSK)
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_CONFIGn_ADDR(base,n), mask)
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_OUTI(base,n,val)        \
                out_dword(HWIO_PMIC_MGPI_TRIG_CONFIGn_ADDR(base,n),val)
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_TRIG_CONFIGn_ADDR(base,n),mask,val,HWIO_PMIC_MGPI_TRIG_CONFIGn_INI(base,n))
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_ADDR_IDX_NEG_BMSK                  0xf000000
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_ADDR_IDX_NEG_SHFT                         24
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_DATA_NEG_BMSK                       0xff0000
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_DATA_NEG_SHFT                             16
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_ADDR_IDX_POS_BMSK                      0xf00
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_ADDR_IDX_POS_SHFT                          8
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_DATA_POS_BMSK                           0xff
#define HWIO_PMIC_MGPI_TRIG_CONFIGn_DATA_POS_SHFT                              0




#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_ADDR(x,n)                        ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0x4 + (0x8*n))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_OFFS                           (0x4)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_RMSK                               0x1f33
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_ADDR(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_ADDR(x), m)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_OUT(x, v)            \
                out_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_ADDR(x),v)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_ADDR(x),m,v,HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_IN(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_NEXT_TRIGGER_BMSK                  0x1f00
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_NEXT_TRIGGER_SHFT                       8
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_INTERRUPT_EN_BMSK                    0x20
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_INTERRUPT_EN_SHFT                       5
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_DUAL_EDGE_ERR_EN_BMSK                0x10
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_DUAL_EDGE_ERR_EN_SHFT                   4
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_MGPI_NEG_EN_BMSK                      0x2
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_MGPI_NEG_EN_SHFT                        1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_MGPI_POS_EN_BMSK                      0x1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_ENn_MGPI_POS_EN_SHFT                        0






#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_ADDR(x)                        ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0x4)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_OFFS                           (0x4)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_RMSK                               0x1f33
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_ADDR(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_ADDR(x), m)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_OUT(x, v)            \
                out_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_ADDR(x),v)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_ADDR(x),m,v,HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_IN(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_NEXT_TRIGGER_BMSK                  0x1f00
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_NEXT_TRIGGER_SHFT                       8
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_INTERRUPT_EN_BMSK                    0x20
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_INTERRUPT_EN_SHFT                       5
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_DUAL_EDGE_ERR_EN_BMSK                0x10
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_DUAL_EDGE_ERR_EN_SHFT                   4
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_MGPI_NEG_EN_BMSK                      0x2
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_MGPI_NEG_EN_SHFT                        1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_MGPI_POS_EN_BMSK                      0x1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN0_MGPI_POS_EN_SHFT                        0

#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_ADDR(x)                        ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0xc)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_OFFS                           (0xc)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_RMSK                               0x1f33
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_ADDR(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_ADDR(x), m)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_OUT(x, v)            \
                out_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_ADDR(x),v)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_ADDR(x),m,v,HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_IN(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_NEXT_TRIGGER_BMSK                  0x1f00
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_NEXT_TRIGGER_SHFT                       8
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_INTERRUPT_EN_BMSK                    0x20
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_INTERRUPT_EN_SHFT                       5
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_DUAL_EDGE_ERR_EN_BMSK                0x10
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_DUAL_EDGE_ERR_EN_SHFT                   4
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_MGPI_NEG_EN_BMSK                      0x2
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_MGPI_NEG_EN_SHFT                        1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_MGPI_POS_EN_BMSK                      0x1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN1_MGPI_POS_EN_SHFT                        0

#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_ADDR(x)                        ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0x14)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_OFFS                           (0x14)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_RMSK                               0x1f33
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_ADDR(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_ADDR(x), m)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_OUT(x, v)            \
                out_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_ADDR(x),v)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_ADDR(x),m,v,HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_IN(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_NEXT_TRIGGER_BMSK                  0x1f00
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_NEXT_TRIGGER_SHFT                       8
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_INTERRUPT_EN_BMSK                    0x20
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_INTERRUPT_EN_SHFT                       5
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_DUAL_EDGE_ERR_EN_BMSK                0x10
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_DUAL_EDGE_ERR_EN_SHFT                   4
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_MGPI_NEG_EN_BMSK                      0x2
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_MGPI_NEG_EN_SHFT                        1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_MGPI_POS_EN_BMSK                      0x1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN2_MGPI_POS_EN_SHFT                        0

#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_ADDR(x)                        ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0x1c)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_OFFS                           (0x1c)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_RMSK                               0x1f33
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_ADDR(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_ADDR(x), m)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_OUT(x, v)            \
                out_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_ADDR(x),v)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_ADDR(x),m,v,HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_IN(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_NEXT_TRIGGER_BMSK                  0x1f00
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_NEXT_TRIGGER_SHFT                       8
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_INTERRUPT_EN_BMSK                    0x20
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_INTERRUPT_EN_SHFT                       5
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_DUAL_EDGE_ERR_EN_BMSK                0x10
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_DUAL_EDGE_ERR_EN_SHFT                   4
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_MGPI_NEG_EN_BMSK                      0x2
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_MGPI_NEG_EN_SHFT                        1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_MGPI_POS_EN_BMSK                      0x1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN3_MGPI_POS_EN_SHFT                        0

#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_ADDR(x)                        ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0x24)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_OFFS                           (0x24)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_RMSK                               0x1f33
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_ADDR(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_ADDR(x), m)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_OUT(x, v)            \
                out_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_ADDR(x),v)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_ADDR(x),m,v,HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_IN(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_NEXT_TRIGGER_BMSK                  0x1f00
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_NEXT_TRIGGER_SHFT                       8
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_INTERRUPT_EN_BMSK                    0x20
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_INTERRUPT_EN_SHFT                       5
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_DUAL_EDGE_ERR_EN_BMSK                0x10
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_DUAL_EDGE_ERR_EN_SHFT                   4
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_MGPI_NEG_EN_BMSK                      0x2
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_MGPI_NEG_EN_SHFT                        1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_MGPI_POS_EN_BMSK                      0x1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN4_MGPI_POS_EN_SHFT                        0

#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_ADDR(x)                        ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0x2c)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_OFFS                           (0x2c)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_RMSK                               0x1f33
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_ADDR(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_ADDR(x), m)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_OUT(x, v)            \
                out_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_ADDR(x),v)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_ADDR(x),m,v,HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_IN(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_NEXT_TRIGGER_BMSK                  0x1f00
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_NEXT_TRIGGER_SHFT                       8
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_INTERRUPT_EN_BMSK                    0x20
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_INTERRUPT_EN_SHFT                       5
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_DUAL_EDGE_ERR_EN_BMSK                0x10
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_DUAL_EDGE_ERR_EN_SHFT                   4
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_MGPI_NEG_EN_BMSK                      0x2
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_MGPI_NEG_EN_SHFT                        1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_MGPI_POS_EN_BMSK                      0x1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN5_MGPI_POS_EN_SHFT                        0

#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_ADDR(x)                        ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0x34)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_OFFS                           (0x34)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_RMSK                               0x1f33
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_ADDR(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_ADDR(x), m)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_OUT(x, v)            \
                out_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_ADDR(x),v)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_ADDR(x),m,v,HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_IN(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_NEXT_TRIGGER_BMSK                  0x1f00
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_NEXT_TRIGGER_SHFT                       8
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_INTERRUPT_EN_BMSK                    0x20
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_INTERRUPT_EN_SHFT                       5
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_DUAL_EDGE_ERR_EN_BMSK                0x10
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_DUAL_EDGE_ERR_EN_SHFT                   4
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_MGPI_NEG_EN_BMSK                      0x2
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_MGPI_NEG_EN_SHFT                        1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_MGPI_POS_EN_BMSK                      0x1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN6_MGPI_POS_EN_SHFT                        0

#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_ADDR(x)                        ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0x3c)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_OFFS                           (0x3c)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_RMSK                               0x1f33
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_ADDR(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_ADDR(x), m)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_OUT(x, v)            \
                out_dword(HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_ADDR(x),v)
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_ADDR(x),m,v,HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_IN(x))
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_NEXT_TRIGGER_BMSK                  0x1f00
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_NEXT_TRIGGER_SHFT                       8
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_INTERRUPT_EN_BMSK                    0x20
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_INTERRUPT_EN_SHFT                       5
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_DUAL_EDGE_ERR_EN_BMSK                0x10
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_DUAL_EDGE_ERR_EN_SHFT                   4
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_MGPI_NEG_EN_BMSK                      0x2
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_MGPI_NEG_EN_SHFT                        1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_MGPI_POS_EN_BMSK                      0x1
#define HWIO_PMIC_MGPI_TRIG_CONFIG_EN7_MGPI_POS_EN_SHFT                        0

#define HWIO_PMIC_MGPI_MASTER_CSR_ADDR(x)                             ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0x100)
#define HWIO_PMIC_MGPI_MASTER_CSR_OFFS                                (0x100)
#define HWIO_PMIC_MGPI_MASTER_CSR_RMSK                                  0x1f1f73
#define HWIO_PMIC_MGPI_MASTER_CSR_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_MASTER_CSR_ADDR(x))
#define HWIO_PMIC_MGPI_MASTER_CSR_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_MASTER_CSR_ADDR(x), m)
#define HWIO_PMIC_MGPI_MASTER_CSR_OUT(x, v)            \
                out_dword(HWIO_PMIC_MGPI_MASTER_CSR_ADDR(x),v)
#define HWIO_PMIC_MGPI_MASTER_CSR_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_MASTER_CSR_ADDR(x),m,v,HWIO_PMIC_MGPI_MASTER_CSR_IN(x))
#define HWIO_PMIC_MGPI_MASTER_CSR_TRIG_CUR_BMSK                         0x1f0000
#define HWIO_PMIC_MGPI_MASTER_CSR_TRIG_CUR_SHFT                               16
#define HWIO_PMIC_MGPI_MASTER_CSR_TRIG_START_BMSK                         0x1f00
#define HWIO_PMIC_MGPI_MASTER_CSR_TRIG_START_SHFT                              8
#define HWIO_PMIC_MGPI_MASTER_CSR_MGPI_IRQ_BMSK                             0x40
#define HWIO_PMIC_MGPI_MASTER_CSR_MGPI_IRQ_SHFT                                6
#define HWIO_PMIC_MGPI_MASTER_CSR_MGPI_ERROR_BMSK                           0x20
#define HWIO_PMIC_MGPI_MASTER_CSR_MGPI_ERROR_SHFT                              5
#define HWIO_PMIC_MGPI_MASTER_CSR_MGPI_ACTIVE_BMSK                          0x10
#define HWIO_PMIC_MGPI_MASTER_CSR_MGPI_ACTIVE_SHFT                             4
#define HWIO_PMIC_MGPI_MASTER_CSR_MGPI_RESET_BMSK                            0x2
#define HWIO_PMIC_MGPI_MASTER_CSR_MGPI_RESET_SHFT                              1
#define HWIO_PMIC_MGPI_MASTER_CSR_MGPI_ENABLE_BMSK                           0x1
#define HWIO_PMIC_MGPI_MASTER_CSR_MGPI_ENABLE_SHFT                             0

#define HWIO_PMIC_MGPI_HW_VERSION_ADDR(x)                             ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0x104)
#define HWIO_PMIC_MGPI_HW_VERSION_OFFS                                (0x104)
#define HWIO_PMIC_MGPI_HW_VERSION_RMSK                                0xffffffff
#define HWIO_PMIC_MGPI_HW_VERSION_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_HW_VERSION_ADDR(x))
#define HWIO_PMIC_MGPI_HW_VERSION_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_HW_VERSION_ADDR(x), m)
#define HWIO_PMIC_MGPI_HW_VERSION_MAJOR_BMSK                          0xf0000000
#define HWIO_PMIC_MGPI_HW_VERSION_MAJOR_SHFT                                  28
#define HWIO_PMIC_MGPI_HW_VERSION_MINOR_BMSK                           0xfff0000
#define HWIO_PMIC_MGPI_HW_VERSION_MINOR_SHFT                                  16
#define HWIO_PMIC_MGPI_HW_VERSION_STEP_BMSK                               0xffff
#define HWIO_PMIC_MGPI_HW_VERSION_STEP_SHFT                                    0

#define HWIO_PMIC_MGPI_RESERVED_ADDR(x)                               ((x) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0x108)
#define HWIO_PMIC_MGPI_RESERVED_OFFS                                  (0x108)
#define HWIO_PMIC_MGPI_RESERVED_RMSK                                  0xffffffff
#define HWIO_PMIC_MGPI_RESERVED_IN(x)            \
                in_dword(HWIO_PMIC_MGPI_RESERVED_ADDR(x))
#define HWIO_PMIC_MGPI_RESERVED_INM(x, m)            \
                in_dword_masked(HWIO_PMIC_MGPI_RESERVED_ADDR(x), m)
#define HWIO_PMIC_MGPI_RESERVED_OUT(x, v)            \
                out_dword(HWIO_PMIC_MGPI_RESERVED_ADDR(x),v)
#define HWIO_PMIC_MGPI_RESERVED_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_RESERVED_ADDR(x),m,v,HWIO_PMIC_MGPI_RESERVED_IN(x))
#define HWIO_PMIC_MGPI_RESERVED_SPARE_31_0_BMSK                       0xffffffff
#define HWIO_PMIC_MGPI_RESERVED_SPARE_31_0_SHFT                                0

#define HWIO_PMIC_MGPI_TRIG_STATUSn_ADDR(base,n)                      ((base) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0X1000 + (0x1000*(n)))
#define HWIO_PMIC_MGPI_TRIG_STATUSn_OFFS(n)                           (0X1000 + (0x1000*(n)))
#define HWIO_PMIC_MGPI_TRIG_STATUSn_RMSK                               0x3fb0000
#define HWIO_PMIC_MGPI_TRIG_STATUSn_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_STATUSn_ADDR(base,n), HWIO_PMIC_MGPI_TRIG_STATUSn_RMSK)
#define HWIO_PMIC_MGPI_TRIG_STATUSn_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_MGPI_TRIG_STATUSn_ADDR(base,n), mask)
#define HWIO_PMIC_MGPI_TRIG_STATUSn_OUTI(base,n,val)        \
                out_dword(HWIO_PMIC_MGPI_TRIG_STATUSn_ADDR(base,n),val)
#define HWIO_PMIC_MGPI_TRIG_STATUSn_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_TRIG_STATUSn_ADDR(base,n),mask,val,HWIO_PMIC_MGPI_TRIG_STATUSn_INI(base,n))
#define HWIO_PMIC_MGPI_TRIG_STATUSn_SUCCESS_NEG_BMSK                   0x2000000
#define HWIO_PMIC_MGPI_TRIG_STATUSn_SUCCESS_NEG_SHFT                          25
#define HWIO_PMIC_MGPI_TRIG_STATUSn_SUCCESS_POS_BMSK                   0x1000000
#define HWIO_PMIC_MGPI_TRIG_STATUSn_SUCCESS_POS_SHFT                          24
#define HWIO_PMIC_MGPI_TRIG_STATUSn_ERROR_WRT_BMSK                      0x800000
#define HWIO_PMIC_MGPI_TRIG_STATUSn_ERROR_WRT_SHFT                            23
#define HWIO_PMIC_MGPI_TRIG_STATUSn_OVERFLOW_ERROR_NEG_BMSK             0x400000
#define HWIO_PMIC_MGPI_TRIG_STATUSn_OVERFLOW_ERROR_NEG_SHFT                   22
#define HWIO_PMIC_MGPI_TRIG_STATUSn_OVERFLOW_ERROR_POS_BMSK             0x200000
#define HWIO_PMIC_MGPI_TRIG_STATUSn_OVERFLOW_ERROR_POS_SHFT                   21
#define HWIO_PMIC_MGPI_TRIG_STATUSn_DUAL_EDGE_ERROR_BMSK                0x100000
#define HWIO_PMIC_MGPI_TRIG_STATUSn_DUAL_EDGE_ERROR_SHFT                      20
#define HWIO_PMIC_MGPI_TRIG_STATUSn_EVENT_WRT_BMSK                       0x80000
#define HWIO_PMIC_MGPI_TRIG_STATUSn_EVENT_WRT_SHFT                            19
#define HWIO_PMIC_MGPI_TRIG_STATUSn_NEG_EVENT_FLAG_BMSK                  0x20000
#define HWIO_PMIC_MGPI_TRIG_STATUSn_NEG_EVENT_FLAG_SHFT                       17
#define HWIO_PMIC_MGPI_TRIG_STATUSn_POS_EVENT_FLAG_BMSK                  0x10000
#define HWIO_PMIC_MGPI_TRIG_STATUSn_POS_EVENT_FLAG_SHFT                       16

#define HWIO_PMIC_MGPI_MUX_SELn_ADDR(base,n)                          ((base) + PMIC_ARB_MGPI_REG_BASE_OFFS + 0X1004 + (0x1000*(n)))
#define HWIO_PMIC_MGPI_MUX_SELn_OFFS(n)                               (0X1004 + (0x1000*(n)))
#define HWIO_PMIC_MGPI_MUX_SELn_RMSK                                         0x7
#define HWIO_PMIC_MGPI_MUX_SELn_INI(base,n)                \
                in_dword_masked(HWIO_PMIC_MGPI_MUX_SELn_ADDR(base,n), HWIO_PMIC_MGPI_MUX_SELn_RMSK)
#define HWIO_PMIC_MGPI_MUX_SELn_INMI(base,n,mask)        \
                in_dword_masked(HWIO_PMIC_MGPI_MUX_SELn_ADDR(base,n), mask)
#define HWIO_PMIC_MGPI_MUX_SELn_OUTI(base,n,val)        \
                out_dword(HWIO_PMIC_MGPI_MUX_SELn_ADDR(base,n),val)
#define HWIO_PMIC_MGPI_MUX_SELn_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_PMIC_MGPI_MUX_SELn_ADDR(base,n),mask,val,HWIO_PMIC_MGPI_MUX_SELn_INI(base,n))
#define HWIO_PMIC_MGPI_MUX_SELn_MUX_SEL_BMSK                                 0x7
#define HWIO_PMIC_MGPI_MUX_SELn_MUX_SEL_SHFT                                   0


/**********************************************************
* Module PMIC_ARB_PRIORITIES
***********************************************************/
#define HWIO_PMIC_ARB_PRIORITIESn_ADDR(x,bid,n)                                                  ((x) + (bid*0x80) + PMIC_ARB_CORE_REG_BASE_OFFS + (0x100+(n*0x4)))
#define HWIO_PMIC_ARB_PRIORITIESn_OFFS                                                     (0x100)
#define HWIO_PMIC_ARB_PRIORITIESn_RMSK                                                           0x1f
#define HWIO_PMIC_ARB_PRIORITIESn_IN(x,bid,n)            \
                in_dword(HWIO_PMIC_ARB_PRIORITIESn_ADDR(x,bid,n))
#define HWIO_PMIC_ARB_PRIORITIESn_INM(x,bid,n, m)            \
                in_dword_masked(HWIO_PMIC_ARB_PRIORITIESn_ADDR(x,bid,n), m)
#define HWIO_PMIC_ARB_PRIORITIESn_OUT(x,bid,n,v)            \
                out_dword(HWIO_PMIC_ARB_PRIORITIESn_ADDR(x,bid,n),v)
#define HWIO_PMIC_ARB_PRIORITIESn_OUTM(x,bid,n,m,v) \
                out_dword_masked_ns(HWIO_PMIC_ARB_PRIORITIESn_ADDR(x,bid,n),m,v,HWIO_PMIC_ARB_PRIORITIESn_IN(x))
#define HWIO_PMIC_ARB_PRIORITIESn_PORT_PRIORITY_BMSK                                             0x1f
#define HWIO_PMIC_ARB_PRIORITIESn_PORT_PRIORITY_SHFT                                                0
















#endif /* __PMICARBCOREHWIO_H__ */
