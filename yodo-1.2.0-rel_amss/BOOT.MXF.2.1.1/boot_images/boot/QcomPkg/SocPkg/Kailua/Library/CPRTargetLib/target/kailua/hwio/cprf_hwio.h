#ifndef __CPRF_HWIO_H__
#define __CPRF_HWIO_H__
/*
===========================================================================
*/
/**
    @file cprf_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8550 (Kailua) [kailua_v1.0_p3q1r7.3_rtl_partition]
 
    This file contains HWIO register definitions for the following modules:
        RPMH_CPRF_CPRF


    Generation parameters: 
    { 'filename': 'cprf_hwio.h',
      'header': '#include "msmhwiobase.h"\n#include "msmhwio.h"',
      'modules': ['RPMH_CPRF_CPRF'],
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

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/CPRTargetLib/target/kailua/hwio/cprf_hwio.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"
#include "msmhwio.h"

/*----------------------------------------------------------------------------
 * MODULE: RPMH_CPRF_CPRF
 *--------------------------------------------------------------------------*/

#define RPMH_CPRF_CPRF_REG_BASE                                                      (AOSS_BASE            + 0x01200000)
#define RPMH_CPRF_CPRF_REG_BASE_SIZE                                                 0x10000
#define RPMH_CPRF_CPRF_REG_BASE_USED                                                 0xf000
#define RPMH_CPRF_CPRF_REG_BASE_PHYS                                                 (AOSS_BASE_PHYS + 0x01200000)
#define RPMH_CPRF_CPRF_REG_BASE_OFFS                                                 0x01200000

#define HWIO_RPMH_CPRF_HW_VERSION_ADDR                                               (RPMH_CPRF_CPRF_REG_BASE            + 0x0)
#define HWIO_RPMH_CPRF_HW_VERSION_PHYS                                               (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x0)
#define HWIO_RPMH_CPRF_HW_VERSION_OFFS                                               (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x0)
#define HWIO_RPMH_CPRF_HW_VERSION_RMSK                                               0xffffffff
#define HWIO_RPMH_CPRF_HW_VERSION_IN                    \
                in_dword(HWIO_RPMH_CPRF_HW_VERSION_ADDR)
#define HWIO_RPMH_CPRF_HW_VERSION_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_HW_VERSION_ADDR, m)
#define HWIO_RPMH_CPRF_HW_VERSION_MAJOR_BMSK                                         0xf0000000
#define HWIO_RPMH_CPRF_HW_VERSION_MAJOR_SHFT                                                 28
#define HWIO_RPMH_CPRF_HW_VERSION_MINOR_BMSK                                          0xfff0000
#define HWIO_RPMH_CPRF_HW_VERSION_MINOR_SHFT                                                 16
#define HWIO_RPMH_CPRF_HW_VERSION_STEP_BMSK                                              0xffff
#define HWIO_RPMH_CPRF_HW_VERSION_STEP_SHFT                                                   0

#define HWIO_RPMH_CPRF_AOSS_SETTINGS_ADDR                                            (RPMH_CPRF_CPRF_REG_BASE            + 0x4)
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_PHYS                                            (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x4)
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_OFFS                                            (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x4)
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_RMSK                                                0xffff
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_IN                    \
                in_dword(HWIO_RPMH_CPRF_AOSS_SETTINGS_ADDR)
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_AOSS_SETTINGS_ADDR, m)
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_AOSS_SETTINGS_ADDR,v)
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_AOSS_SETTINGS_ADDR,m,v,HWIO_RPMH_CPRF_AOSS_SETTINGS_IN)
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_SID_BMSK                                            0xe000
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_SID_SHFT                                                13
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_DRVID_BMSK                                          0x1f00
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_DRVID_SHFT                                               8
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_ADDRESS_BMSK                                          0xff
#define HWIO_RPMH_CPRF_AOSS_SETTINGS_ADDRESS_SHFT                                             0

#define HWIO_RPMH_CPRF_INTERRUPT_STATUS_ADDR                                         (RPMH_CPRF_CPRF_REG_BASE            + 0x8)
#define HWIO_RPMH_CPRF_INTERRUPT_STATUS_PHYS                                         (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x8)
#define HWIO_RPMH_CPRF_INTERRUPT_STATUS_OFFS                                         (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x8)
#define HWIO_RPMH_CPRF_INTERRUPT_STATUS_RMSK                                            0xfffff
#define HWIO_RPMH_CPRF_INTERRUPT_STATUS_IN                    \
                in_dword(HWIO_RPMH_CPRF_INTERRUPT_STATUS_ADDR)
#define HWIO_RPMH_CPRF_INTERRUPT_STATUS_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_INTERRUPT_STATUS_ADDR, m)
#define HWIO_RPMH_CPRF_INTERRUPT_STATUS_CPRF_VSENSE_INTERRUPT_STATUS_BMSK               0xffc00
#define HWIO_RPMH_CPRF_INTERRUPT_STATUS_CPRF_VSENSE_INTERRUPT_STATUS_SHFT                    10
#define HWIO_RPMH_CPRF_INTERRUPT_STATUS_CPRF_INTERRUPT_STATUS_BMSK                        0x3ff
#define HWIO_RPMH_CPRF_INTERRUPT_STATUS_CPRF_INTERRUPT_STATUS_SHFT                            0

#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_ADDR                                        (RPMH_CPRF_CPRF_REG_BASE            + 0xc)
#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_PHYS                                        (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0xc)
#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_OFFS                                        (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0xc)
#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_RMSK                                           0x1ffff
#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_IN                    \
                in_dword(HWIO_RPMH_CPRF_VRM_COMPLETION_WA_ADDR)
#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_VRM_COMPLETION_WA_ADDR, m)
#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_VRM_COMPLETION_WA_ADDR,v)
#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_VRM_COMPLETION_WA_ADDR,m,v,HWIO_RPMH_CPRF_VRM_COMPLETION_WA_IN)
#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_SW_COMPLETION_BMSK                             0x1fffe
#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_SW_COMPLETION_SHFT                                   1
#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_COMPLETION_WA_EN_BMSK                              0x1
#define HWIO_RPMH_CPRF_VRM_COMPLETION_WA_COMPLETION_WA_EN_SHFT                                0

#define HWIO_RPMH_CPRF_VRM_BRCST_WA_ADDR                                             (RPMH_CPRF_CPRF_REG_BASE            + 0x10)
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_PHYS                                             (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x10)
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_OFFS                                             (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x10)
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_RMSK                                              0xfffffff
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_IN                    \
                in_dword(HWIO_RPMH_CPRF_VRM_BRCST_WA_ADDR)
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_VRM_BRCST_WA_ADDR, m)
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_VRM_BRCST_WA_ADDR,v)
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_VRM_BRCST_WA_ADDR,m,v,HWIO_RPMH_CPRF_VRM_BRCST_WA_IN)
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_SW_BRCST_VALID_BMSK                               0x8000000
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_SW_BRCST_VALID_SHFT                                      27
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_SW_BRCST_CHANGE_DATA_BMSK                         0x7ffc000
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_SW_BRCST_CHANGE_DATA_SHFT                                14
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_SW_BRCST_TASK_TYPE_BMSK                              0x3e00
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_SW_BRCST_TASK_TYPE_SHFT                                   9
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_SW_BRCST_RESOURCE_ID_BMSK                             0x1fe
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_SW_BRCST_RESOURCE_ID_SHFT                                 1
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_BRCST_WA_EN_BMSK                                        0x1
#define HWIO_RPMH_CPRF_VRM_BRCST_WA_BRCST_WA_EN_SHFT                                          0

#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_ADDR                                         (RPMH_CPRF_CPRF_REG_BASE            + 0x14)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_PHYS                                         (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x14)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_OFFS                                         (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x14)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_RMSK                                         0xffffffff
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_IN                    \
                in_dword(HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_ADDR)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_ADDR, m)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_ADDR,v)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_ADDR,m,v,HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_IN)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_DEBUG_SEL_BMSK                               0xfffffffe
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_DEBUG_SEL_SHFT                                        1
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_SELECT_CTRL_BMSK                                    0x1
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_0_SELECT_CTRL_SHFT                                      0

#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_ADDR                                         (RPMH_CPRF_CPRF_REG_BASE            + 0x18)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_PHYS                                         (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x18)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_OFFS                                         (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x18)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_RMSK                                         0xffffffff
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_IN                    \
                in_dword(HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_ADDR)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_ADDR, m)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_ADDR,v)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_ADDR,m,v,HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_IN)
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_DEBUG_SEL_BMSK                               0xffffffff
#define HWIO_RPMH_CPRF_DEBUG_BUS_CTRL_1_DEBUG_SEL_SHFT                                        0

#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_0_ADDR                                       (RPMH_CPRF_CPRF_REG_BASE            + 0x1c)
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_0_PHYS                                       (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x1c)
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_0_OFFS                                       (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x1c)
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_0_RMSK                                       0xffffffff
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_0_IN                    \
                in_dword(HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_0_ADDR)
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_0_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_0_ADDR, m)
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_0_DEBUG_BUS_BMSK                             0xffffffff
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_0_DEBUG_BUS_SHFT                                      0

#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_1_ADDR                                       (RPMH_CPRF_CPRF_REG_BASE            + 0x20)
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_1_PHYS                                       (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x20)
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_1_OFFS                                       (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x20)
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_1_RMSK                                       0xffffffff
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_1_IN                    \
                in_dword(HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_1_ADDR)
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_1_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_1_ADDR, m)
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_1_DEBUG_BUS_BMSK                             0xffffffff
#define HWIO_RPMH_CPRF_DEBUG_BUS_OUTPUT_1_DEBUG_BUS_SHFT                                      0

#define HWIO_RPMH_CPRF_CXO_ON_SETTINGS_ADDR                                          (RPMH_CPRF_CPRF_REG_BASE            + 0x24)
#define HWIO_RPMH_CPRF_CXO_ON_SETTINGS_PHYS                                          (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x24)
#define HWIO_RPMH_CPRF_CXO_ON_SETTINGS_OFFS                                          (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x24)
#define HWIO_RPMH_CPRF_CXO_ON_SETTINGS_RMSK                                                0x1f
#define HWIO_RPMH_CPRF_CXO_ON_SETTINGS_IN                    \
                in_dword(HWIO_RPMH_CPRF_CXO_ON_SETTINGS_ADDR)
#define HWIO_RPMH_CPRF_CXO_ON_SETTINGS_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CXO_ON_SETTINGS_ADDR, m)
#define HWIO_RPMH_CPRF_CXO_ON_SETTINGS_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_CXO_ON_SETTINGS_ADDR,v)
#define HWIO_RPMH_CPRF_CXO_ON_SETTINGS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CXO_ON_SETTINGS_ADDR,m,v,HWIO_RPMH_CPRF_CXO_ON_SETTINGS_IN)
#define HWIO_RPMH_CPRF_CXO_ON_SETTINGS_OL_ON_BMSK                                          0x1f
#define HWIO_RPMH_CPRF_CXO_ON_SETTINGS_OL_ON_SHFT                                             0

#define HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_ADDR                                         (RPMH_CPRF_CPRF_REG_BASE            + 0x28)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_PHYS                                         (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x28)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_OFFS                                         (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x28)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_RMSK                                                0x1
#define HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_IN                    \
                in_dword(HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_ADDR)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_ADDR, m)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_ADDR,v)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_ADDR,m,v,HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_IN)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_SW_RESET_BMSK                                       0x1
#define HWIO_RPMH_CPRF_CLOCK_MGMT_RESET_SW_RESET_SHFT                                         0

#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_ADDR                                        (RPMH_CPRF_CPRF_REG_BASE            + 0x2c)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_PHYS                                        (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x2c)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_OFFS                                        (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x2c)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_RMSK                                               0x3
#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_IN                    \
                in_dword(HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_ADDR)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_ADDR, m)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_ADDR,v)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_ADDR,m,v,HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_IN)
#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_CXO_OFF_POST_BOOT_BMSK                             0x2
#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_CXO_OFF_POST_BOOT_SHFT                               1
#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_EN_BMSK                                            0x1
#define HWIO_RPMH_CPRF_CLOCK_MGMT_ENABLE_EN_SHFT                                              0

#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_ADDR                                     (RPMH_CPRF_CPRF_REG_BASE            + 0x30)
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_PHYS                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x30)
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_OFFS                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x30)
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_RMSK                                            0x7
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_IN                    \
                in_dword(HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_ADDR)
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_ADDR, m)
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_ADDR,v)
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_ADDR,m,v,HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_IN)
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_CHANGE_DATA_BMSK                                0x4
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_CHANGE_DATA_SHFT                                  2
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_TASK_TYPE_BMSK                                  0x2
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_TASK_TYPE_SHFT                                    1
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_RESOURCE_ID_BMSK                                0x1
#define HWIO_RPMH_CPRF_VRM_BRCST_ENDIANNESS_RESOURCE_ID_SHFT                                  0

#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_ADDR                                        (RPMH_CPRF_CPRF_REG_BASE            + 0x34)
#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_PHYS                                        (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x34)
#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_OFFS                                        (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x34)
#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_RMSK                                               0x3
#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_IN                    \
                in_dword(HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_ADDR)
#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_ADDR, m)
#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_ADDR,v)
#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_ADDR,m,v,HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_IN)
#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_ENDIANNESS_BMSK                                    0x2
#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_ENDIANNESS_SHFT                                      1
#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_SWAP_BMSK                                          0x1
#define HWIO_RPMH_CPRF_ARC_CXO_BIT_ORDER_SWAP_SHFT                                            0

#define HWIO_RPMH_CPRF_MISC_RESET_ADDR                                               (RPMH_CPRF_CPRF_REG_BASE            + 0x38)
#define HWIO_RPMH_CPRF_MISC_RESET_PHYS                                               (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x38)
#define HWIO_RPMH_CPRF_MISC_RESET_OFFS                                               (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x38)
#define HWIO_RPMH_CPRF_MISC_RESET_RMSK                                                      0x1
#define HWIO_RPMH_CPRF_MISC_RESET_IN                    \
                in_dword(HWIO_RPMH_CPRF_MISC_RESET_ADDR)
#define HWIO_RPMH_CPRF_MISC_RESET_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_MISC_RESET_ADDR, m)
#define HWIO_RPMH_CPRF_MISC_RESET_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_MISC_RESET_ADDR,v)
#define HWIO_RPMH_CPRF_MISC_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_MISC_RESET_ADDR,m,v,HWIO_RPMH_CPRF_MISC_RESET_IN)
#define HWIO_RPMH_CPRF_MISC_RESET_SW_RESET_BMSK                                             0x1
#define HWIO_RPMH_CPRF_MISC_RESET_SW_RESET_SHFT                                               0

#define HWIO_RPMH_CPRF_MISC_CTRL_ADDR                                                (RPMH_CPRF_CPRF_REG_BASE            + 0x3c)
#define HWIO_RPMH_CPRF_MISC_CTRL_PHYS                                                (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x3c)
#define HWIO_RPMH_CPRF_MISC_CTRL_OFFS                                                (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x3c)
#define HWIO_RPMH_CPRF_MISC_CTRL_RMSK                                                       0x1
#define HWIO_RPMH_CPRF_MISC_CTRL_IN                    \
                in_dword(HWIO_RPMH_CPRF_MISC_CTRL_ADDR)
#define HWIO_RPMH_CPRF_MISC_CTRL_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_MISC_CTRL_ADDR, m)
#define HWIO_RPMH_CPRF_MISC_CTRL_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_MISC_CTRL_ADDR,v)
#define HWIO_RPMH_CPRF_MISC_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_MISC_CTRL_ADDR,m,v,HWIO_RPMH_CPRF_MISC_CTRL_IN)
#define HWIO_RPMH_CPRF_MISC_CTRL_HW_CTRL_CGC_DIS_BMSK                                       0x1
#define HWIO_RPMH_CPRF_MISC_CTRL_HW_CTRL_CGC_DIS_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_ADDR                                          (RPMH_CPRF_CPRF_REG_BASE            + 0x40)
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_PHYS                                          (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x40)
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_OFFS                                          (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x40)
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_RMSK                                                0x1f
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_ADDR)
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_ADDR,v)
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_ADDR,m,v,HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_IN)
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_OL_CAPTURE_RESET_BMSK                               0x10
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_OL_CAPTURE_RESET_SHFT                                  4
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_VFSM_CAPTURE_RESET_BMSK                              0x8
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_VFSM_CAPTURE_RESET_SHFT                                3
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_OL_CAPTURE_EN_BMSK                                   0x4
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_OL_CAPTURE_EN_SHFT                                     2
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_VFSM_CAPTURE_EN_BMSK                                 0x2
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_VFSM_CAPTURE_EN_SHFT                                   1
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_DEBUG_SELECT_BIT64_BMSK                              0x1
#define HWIO_RPMH_CPRF_CPRF_DEBUG_CTRL_DEBUG_SELECT_BIT64_SHFT                                0

#define HWIO_RPMH_CPRF_CPRF_WRAPPER_DEBUG_BUS_ADDR                                   (RPMH_CPRF_CPRF_REG_BASE            + 0x44)
#define HWIO_RPMH_CPRF_CPRF_WRAPPER_DEBUG_BUS_PHYS                                   (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x44)
#define HWIO_RPMH_CPRF_CPRF_WRAPPER_DEBUG_BUS_OFFS                                   (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x44)
#define HWIO_RPMH_CPRF_CPRF_WRAPPER_DEBUG_BUS_RMSK                                   0xffffffff
#define HWIO_RPMH_CPRF_CPRF_WRAPPER_DEBUG_BUS_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_WRAPPER_DEBUG_BUS_ADDR)
#define HWIO_RPMH_CPRF_CPRF_WRAPPER_DEBUG_BUS_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_WRAPPER_DEBUG_BUS_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_WRAPPER_DEBUG_BUS_CPRF_WRAPPER_DEBUG_BMSK                0xffffffff
#define HWIO_RPMH_CPRF_CPRF_WRAPPER_DEBUG_BUS_CPRF_WRAPPER_DEBUG_SHFT                         0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC0_ADDR                                     (RPMH_CPRF_CPRF_REG_BASE            + 0x48)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC0_PHYS                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x48)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC0_OFFS                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x48)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC0_RMSK                                          0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC0_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC0_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC0_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC0_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC0_LOC0_BMSK                                     0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC0_LOC0_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC1_ADDR                                     (RPMH_CPRF_CPRF_REG_BASE            + 0x4c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC1_PHYS                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x4c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC1_OFFS                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x4c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC1_RMSK                                          0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC1_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC1_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC1_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC1_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC1_LOC1_BMSK                                     0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC1_LOC1_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC2_ADDR                                     (RPMH_CPRF_CPRF_REG_BASE            + 0x50)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC2_PHYS                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x50)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC2_OFFS                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x50)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC2_RMSK                                          0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC2_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC2_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC2_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC2_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC2_LOC2_BMSK                                     0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC2_LOC2_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC3_ADDR                                     (RPMH_CPRF_CPRF_REG_BASE            + 0x54)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC3_PHYS                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x54)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC3_OFFS                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x54)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC3_RMSK                                          0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC3_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC3_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC3_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC3_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC3_LOC3_BMSK                                     0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC3_LOC3_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC4_ADDR                                     (RPMH_CPRF_CPRF_REG_BASE            + 0x58)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC4_PHYS                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x58)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC4_OFFS                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x58)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC4_RMSK                                          0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC4_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC4_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC4_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC4_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC4_LOC4_BMSK                                     0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC4_LOC4_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC5_ADDR                                     (RPMH_CPRF_CPRF_REG_BASE            + 0x5c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC5_PHYS                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x5c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC5_OFFS                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x5c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC5_RMSK                                          0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC5_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC5_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC5_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC5_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC5_LOC5_BMSK                                     0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC5_LOC5_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC6_ADDR                                     (RPMH_CPRF_CPRF_REG_BASE            + 0x60)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC6_PHYS                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x60)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC6_OFFS                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x60)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC6_RMSK                                          0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC6_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC6_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC6_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC6_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC6_LOC6_BMSK                                     0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC6_LOC6_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC7_ADDR                                     (RPMH_CPRF_CPRF_REG_BASE            + 0x64)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC7_PHYS                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x64)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC7_OFFS                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x64)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC7_RMSK                                          0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC7_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC7_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC7_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC7_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC7_LOC7_BMSK                                     0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC7_LOC7_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC8_ADDR                                     (RPMH_CPRF_CPRF_REG_BASE            + 0x68)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC8_PHYS                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x68)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC8_OFFS                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x68)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC8_RMSK                                          0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC8_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC8_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC8_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC8_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC8_LOC8_BMSK                                     0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC8_LOC8_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC9_ADDR                                     (RPMH_CPRF_CPRF_REG_BASE            + 0x6c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC9_PHYS                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x6c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC9_OFFS                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x6c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC9_RMSK                                          0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC9_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC9_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC9_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC9_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC9_LOC9_BMSK                                     0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC9_LOC9_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC10_ADDR                                    (RPMH_CPRF_CPRF_REG_BASE            + 0x70)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC10_PHYS                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x70)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC10_OFFS                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x70)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC10_RMSK                                         0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC10_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC10_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC10_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC10_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC10_LOC10_BMSK                                   0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC10_LOC10_SHFT                                       0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC11_ADDR                                    (RPMH_CPRF_CPRF_REG_BASE            + 0x74)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC11_PHYS                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x74)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC11_OFFS                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x74)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC11_RMSK                                         0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC11_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC11_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC11_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC11_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC11_LOC11_BMSK                                   0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC11_LOC11_SHFT                                       0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC12_ADDR                                    (RPMH_CPRF_CPRF_REG_BASE            + 0x78)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC12_PHYS                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x78)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC12_OFFS                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x78)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC12_RMSK                                         0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC12_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC12_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC12_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC12_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC12_LOC12_BMSK                                   0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC12_LOC12_SHFT                                       0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC13_ADDR                                    (RPMH_CPRF_CPRF_REG_BASE            + 0x7c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC13_PHYS                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x7c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC13_OFFS                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x7c)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC13_RMSK                                         0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC13_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC13_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC13_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC13_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC13_LOC13_BMSK                                   0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC13_LOC13_SHFT                                       0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC14_ADDR                                    (RPMH_CPRF_CPRF_REG_BASE            + 0x80)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC14_PHYS                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x80)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC14_OFFS                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x80)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC14_RMSK                                         0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC14_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC14_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC14_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC14_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC14_LOC14_BMSK                                   0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC14_LOC14_SHFT                                       0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC15_ADDR                                    (RPMH_CPRF_CPRF_REG_BASE            + 0x84)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC15_PHYS                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x84)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC15_OFFS                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x84)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC15_RMSK                                         0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC15_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC15_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC15_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC15_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC15_LOC15_BMSK                                   0x1ff
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_LOC15_LOC15_SHFT                                       0

#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_WRPTR_ADDR                                    (RPMH_CPRF_CPRF_REG_BASE            + 0x88)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_WRPTR_PHYS                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x88)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_WRPTR_OFFS                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x88)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_WRPTR_RMSK                                           0xf
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_WRPTR_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_WRPTR_ADDR)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_WRPTR_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_WRPTR_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_WRPTR_WRPTR_BMSK                                     0xf
#define HWIO_RPMH_CPRF_CPRF_OL_CAPTURE_WRPTR_WRPTR_SHFT                                       0

#define HWIO_RPMH_CPRF_CPRF_IDLE_STATUS_ADDR                                         (RPMH_CPRF_CPRF_REG_BASE            + 0x8c)
#define HWIO_RPMH_CPRF_CPRF_IDLE_STATUS_PHYS                                         (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0x8c)
#define HWIO_RPMH_CPRF_CPRF_IDLE_STATUS_OFFS                                         (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0x8c)
#define HWIO_RPMH_CPRF_CPRF_IDLE_STATUS_RMSK                                              0x3ff
#define HWIO_RPMH_CPRF_CPRF_IDLE_STATUS_IN                    \
                in_dword(HWIO_RPMH_CPRF_CPRF_IDLE_STATUS_ADDR)
#define HWIO_RPMH_CPRF_CPRF_IDLE_STATUS_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_IDLE_STATUS_ADDR, m)
#define HWIO_RPMH_CPRF_CPRF_IDLE_STATUS_IDLE_STATUS_BMSK                                  0x3ff
#define HWIO_RPMH_CPRF_CPRF_IDLE_STATUS_IDLE_STATUS_SHFT                                      0

#define HWIO_RPMH_CPRF_CPRFm_RESET_ADDR(m)                                           (RPMH_CPRF_CPRF_REG_BASE            + 0X1000 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_RESET_PHYS(m)                                           (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1000 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_RESET_OFFS(m)                                           (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1000 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_RESET_RMSK                                                     0x1
#define HWIO_RPMH_CPRF_CPRFm_RESET_MAXm                                                       9
#define HWIO_RPMH_CPRF_CPRFm_RESET_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_RESET_ADDR(m), HWIO_RPMH_CPRF_CPRFm_RESET_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_RESET_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_RESET_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_RESET_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_RESET_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_RESET_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_RESET_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_RESET_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_RESET_SW_RESET_BMSK                                            0x1
#define HWIO_RPMH_CPRF_CPRFm_RESET_SW_RESET_SHFT                                              0

#define HWIO_RPMH_CPRF_CPRFm_CTRL_ADDR(m)                                            (RPMH_CPRF_CPRF_REG_BASE            + 0X1004 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_CTRL_PHYS(m)                                            (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1004 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_CTRL_OFFS(m)                                            (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1004 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_CTRL_RMSK                                                   0x1eff
#define HWIO_RPMH_CPRF_CPRFm_CTRL_MAXm                                                        9
#define HWIO_RPMH_CPRF_CPRFm_CTRL_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_CTRL_ADDR(m), HWIO_RPMH_CPRF_CPRFm_CTRL_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_CTRL_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_CTRL_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_CTRL_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_CTRL_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_CTRL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_CTRL_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_CTRL_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_CTRL_OL_CHANGE_VOL_COMPARE_MODE_BMSK                        0x1000
#define HWIO_RPMH_CPRF_CPRFm_CTRL_OL_CHANGE_VOL_COMPARE_MODE_SHFT                            12
#define HWIO_RPMH_CPRF_CPRFm_CTRL_DISABLE_WAIT4BRCST_ABORT_BMSK                           0x800
#define HWIO_RPMH_CPRF_CPRFm_CTRL_DISABLE_WAIT4BRCST_ABORT_SHFT                              11
#define HWIO_RPMH_CPRF_CPRFm_CTRL_OFFACK_DEPEND_ON_COMPLETION_BMSK                        0x400
#define HWIO_RPMH_CPRF_CPRFm_CTRL_OFFACK_DEPEND_ON_COMPLETION_SHFT                           10
#define HWIO_RPMH_CPRF_CPRFm_CTRL_VOTE_OPENLOOP_CPRC_OFF_BMSK                             0x200
#define HWIO_RPMH_CPRF_CPRFm_CTRL_VOTE_OPENLOOP_CPRC_OFF_SHFT                                 9
#define HWIO_RPMH_CPRF_CPRFm_CTRL_NOT_VOTE_EQUAL_VOLTAGE_BMSK                              0x80
#define HWIO_RPMH_CPRF_CPRFm_CTRL_NOT_VOTE_EQUAL_VOLTAGE_SHFT                                 7
#define HWIO_RPMH_CPRF_CPRFm_CTRL_RE_ENABLE_STARVATION_BMSK                                0x40
#define HWIO_RPMH_CPRF_CPRFm_CTRL_RE_ENABLE_STARVATION_SHFT                                   6
#define HWIO_RPMH_CPRF_CPRFm_CTRL_COMPLETION_REQ_CPRC_BMSK                                 0x20
#define HWIO_RPMH_CPRF_CPRFm_CTRL_COMPLETION_REQ_CPRC_SHFT                                    5
#define HWIO_RPMH_CPRF_CPRFm_CTRL_COMPLETION_REQ_DCVS_BMSK                                 0x10
#define HWIO_RPMH_CPRF_CPRFm_CTRL_COMPLETION_REQ_DCVS_SHFT                                    4
#define HWIO_RPMH_CPRF_CPRFm_CTRL_PR_HANDSHAKE_EN_BMSK                                      0x8
#define HWIO_RPMH_CPRF_CPRFm_CTRL_PR_HANDSHAKE_EN_SHFT                                        3
#define HWIO_RPMH_CPRF_CPRFm_CTRL_CTRL_INTERACTION_EN_BMSK                                  0x4
#define HWIO_RPMH_CPRF_CPRFm_CTRL_CTRL_INTERACTION_EN_SHFT                                    2
#define HWIO_RPMH_CPRF_CPRFm_CTRL_CLOCK_MGMT_EN_BMSK                                        0x2
#define HWIO_RPMH_CPRF_CPRFm_CTRL_CLOCK_MGMT_EN_SHFT                                          1
#define HWIO_RPMH_CPRF_CPRFm_CTRL_VOLTAGE_VOTE_EN_BMSK                                      0x1
#define HWIO_RPMH_CPRF_CPRFm_CTRL_VOLTAGE_VOTE_EN_SHFT                                        0

#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_ADDR(m)                                    (RPMH_CPRF_CPRF_REG_BASE            + 0X1008 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_PHYS(m)                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1008 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_OFFS(m)                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1008 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_RMSK                                       0x1fffffff
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_MAXm                                                9
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_ADDR(m), HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_VOLTAGE_ADDRESS_OFFSET_BMSK                0x1fffe000
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_VOLTAGE_ADDRESS_OFFSET_SHFT                        13
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_TASK_TYPE_BMSK                                 0x1f00
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_TASK_TYPE_SHFT                                      8
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_RESOURCE_ID_BMSK                                 0xff
#define HWIO_RPMH_CPRF_CPRFm_VRM_SETTINGS_RESOURCE_ID_SHFT                                    0

#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_ADDR(m,n)                              (RPMH_CPRF_CPRF_REG_BASE            + 0X100C + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_PHYS(m,n)                              (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X100C + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_OFFS(m,n)                              (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X100C + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_RMSK                                   0x1fff1fff
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_MAXm                                            9
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_MAXn                                           15
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_INI2(m,n)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_ADDR(m,n), HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_ADDR(m,n), mask)
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_OUTI2(m,n,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_ADDR(m,n),val)
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_ADDR(m,n),mask,val,HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_INI2(m,n))
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_VMAX_BMSK                              0x1fff0000
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_VMAX_SHFT                                      16
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_VMIN_BMSK                                  0x1fff
#define HWIO_RPMH_CPRF_CPRFm_VOLTAGE_LIMITS_n_VMIN_SHFT                                       0

#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_ADDR(m,n)                                (RPMH_CPRF_CPRF_REG_BASE            + 0X108C + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_PHYS(m,n)                                (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X108C + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_OFFS(m,n)                                (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X108C + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_RMSK                                         0x1fff
#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_MAXm                                              9
#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_MAXn                                             15
#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_INI2(m,n)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_ADDR(m,n), HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_ADDR(m,n), mask)
#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_OUTI2(m,n,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_ADDR(m,n),val)
#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_ADDR(m,n),mask,val,HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_INI2(m,n))
#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_VSAFE_BMSK                                   0x1fff
#define HWIO_RPMH_CPRF_CPRFm_SAFE_VOLTAGE_n_VSAFE_SHFT                                        0

#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_ADDR(m)                                      (RPMH_CPRF_CPRF_REG_BASE            + 0X1110 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_PHYS(m)                                      (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1110 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_OFFS(m)                                      (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1110 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_RMSK                                         0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_MAXm                                                  9
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_ADDR(m), HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_COUNT_BMSK                                   0xfffffffe
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_COUNT_SHFT                                            1
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_ENABLE_BMSK                                         0x1
#define HWIO_RPMH_CPRF_CPRFm_DELAY_CPRC_ENABLE_SHFT                                           0

#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_ADDR(m)                                (RPMH_CPRF_CPRF_REG_BASE            + 0X1114 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_PHYS(m)                                (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1114 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_OFFS(m)                                (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1114 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_RMSK                                      0x7ffff
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_MAXm                                            9
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_ADDR(m), HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_INITIAL_VOLTAGE_BMSK                      0x7ffc0
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_INITIAL_VOLTAGE_SHFT                            6
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_INIT_VOLTAGE_EN_BMSK                         0x20
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_INIT_VOLTAGE_EN_SHFT                            5
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_INITIAL_OL_BMSK                              0x1f
#define HWIO_RPMH_CPRF_CPRFm_INITIAL_SETTINGS_INITIAL_OL_SHFT                                 0

#define HWIO_RPMH_CPRF_CPRFm_ENABLE_ADDR(m)                                          (RPMH_CPRF_CPRF_REG_BASE            + 0X1118 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ENABLE_PHYS(m)                                          (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1118 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ENABLE_OFFS(m)                                          (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1118 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ENABLE_RMSK                                                    0x1
#define HWIO_RPMH_CPRF_CPRFm_ENABLE_MAXm                                                      9
#define HWIO_RPMH_CPRF_CPRFm_ENABLE_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_ENABLE_ADDR(m), HWIO_RPMH_CPRF_CPRFm_ENABLE_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_ENABLE_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_ENABLE_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_ENABLE_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_ENABLE_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_ENABLE_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_ENABLE_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_ENABLE_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_ENABLE_EN_BMSK                                                 0x1
#define HWIO_RPMH_CPRF_CPRFm_ENABLE_EN_SHFT                                                   0

#define HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_ADDR(m)                                  (RPMH_CPRF_CPRF_REG_BASE            + 0X111C + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_PHYS(m)                                  (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X111C + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_OFFS(m)                                  (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X111C + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_RMSK                                            0x1
#define HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_MAXm                                              9
#define HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_ADDR(m), HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_FORCE_INITIAL_0_BMSK                            0x1
#define HWIO_RPMH_CPRF_CPRFm_FORCE_SETTINGS_FORCE_INITIAL_0_SHFT                              0

#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_ADDR(m,n)                          (RPMH_CPRF_CPRF_REG_BASE            + 0X1120 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_PHYS(m,n)                          (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1120 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_OFFS(m,n)                          (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1120 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_RMSK                                     0xff
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_MAXm                                        9
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_MAXn                                       15
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_INI2(m,n)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_ADDR(m,n), HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_ADDR(m,n), mask)
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_OUTI2(m,n,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_ADDR(m,n),val)
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_ADDR(m,n),mask,val,HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_INI2(m,n))
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_CONT_MID_COUNTER_BMSK                    0x80
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_CONT_MID_COUNTER_SHFT                       7
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_MID_COUNT_BMSK                           0x78
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_MID_COUNT_SHFT                              3
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_MODE_SEL_BMSK                             0x7
#define HWIO_RPMH_CPRF_CPRFm_RECORDING_SETTINGS_n_MODE_SEL_SHFT                               0

#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_ADDR(m,n)                           (RPMH_CPRF_CPRF_REG_BASE            + 0X11A0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_PHYS(m,n)                           (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X11A0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_OFFS(m,n)                           (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X11A0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_RMSK                                      0xff
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_MAXm                                         9
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_MAXn                                        15
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_INI2(m,n)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_ADDR(m,n), HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_ADDR(m,n), mask)
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_OUTI2(m,n,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_ADDR(m,n),val)
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_ADDR(m,n),mask,val,HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_INI2(m,n))
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_CAP_UP_BMSK                               0xf0
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_CAP_UP_SHFT                                  4
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_CAP_DOWN_BMSK                              0xf
#define HWIO_RPMH_CPRF_CPRFm_CAP_STEP_SETTINGS_n_CAP_DOWN_SHFT                                0

#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_ADDR(m)                                (RPMH_CPRF_CPRF_REG_BASE            + 0X1220 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_PHYS(m)                                (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1220 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_OFFS(m)                                (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1220 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_RMSK                                        0x7ff
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_MAXm                                            9
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_ADDR(m), HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_CPRC_SUCCESS_INT_BMSK                       0x400
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_CPRC_SUCCESS_INT_SHFT                          10
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_DCVS_SUCCESS_INT_BMSK                       0x200
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_DCVS_SUCCESS_INT_SHFT                           9
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_TIMEOUT_INT_BMSK                            0x100
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_TIMEOUT_INT_SHFT                                8
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_FLOOR_UPDATED_INT_BMSK                       0x80
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_FLOOR_UPDATED_INT_SHFT                          7
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_ERROR_VMIN_INT_BMSK                          0x40
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_ERROR_VMIN_INT_SHFT                             6
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_ERROR_VMAX_INT_BMSK                          0x20
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_ERROR_VMAX_INT_SHFT                             5
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_NEW_CPRC_RECOMM_INT_BMSK                     0x10
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_NEW_CPRC_RECOMM_INT_SHFT                        4
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_NEW_VOLTAGE_VOTE_INT_BMSK                     0x8
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_NEW_VOLTAGE_VOTE_INT_SHFT                       3
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_PR_OL_CHANGED_INT_BMSK                        0x4
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_PR_OL_CHANGED_INT_SHFT                          2
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_CXO_ENABLED_INT_BMSK                          0x2
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_CXO_ENABLED_INT_SHFT                            1
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_CXO_DISABLED_INT_BMSK                         0x1
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_STATUS_CXO_DISABLED_INT_SHFT                           0

#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_ADDR(m)                                   (RPMH_CPRF_CPRF_REG_BASE            + 0X1220 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_PHYS(m)                                   (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1220 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_OFFS(m)                                   (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1220 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_RMSK                                           0x7ff
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_MAXm                                               9
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_CPRC_SUCCESS_ACK_BMSK                          0x400
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_CPRC_SUCCESS_ACK_SHFT                             10
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_DCVS_SUCCESS_ACK_BMSK                          0x200
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_DCVS_SUCCESS_ACK_SHFT                              9
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_TIMEOUT_ACK_BMSK                               0x100
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_TIMEOUT_ACK_SHFT                                   8
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_FLOOR_UPDATED_ACK_BMSK                          0x80
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_FLOOR_UPDATED_ACK_SHFT                             7
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_ERROR_VMIN_ACK_BMSK                             0x40
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_ERROR_VMIN_ACK_SHFT                                6
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_ERROR_VMAX_ACK_BMSK                             0x20
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_ERROR_VMAX_ACK_SHFT                                5
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_NEW_CPRC_RECOMM_ACK_BMSK                        0x10
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_NEW_CPRC_RECOMM_ACK_SHFT                           4
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_NEW_VOLTAGE_VOTE_ACK_BMSK                        0x8
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_NEW_VOLTAGE_VOTE_ACK_SHFT                          3
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_PR_OL_CHANGED_ACK_BMSK                           0x4
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_PR_OL_CHANGED_ACK_SHFT                             2
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_CXO_ENABLED_ACK_BMSK                             0x2
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_CXO_ENABLED_ACK_SHFT                               1
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_CXO_DISABLED_ACK_BMSK                            0x1
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_ACK_CXO_DISABLED_ACK_SHFT                              0

#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_ADDR(m)                                  (RPMH_CPRF_CPRF_REG_BASE            + 0X1224 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_PHYS(m)                                  (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1224 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_OFFS(m)                                  (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1224 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_RMSK                                          0x7ff
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_MAXm                                              9
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_ADDR(m), HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_CPRC_SUCCESS_MASK_BMSK                        0x400
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_CPRC_SUCCESS_MASK_SHFT                           10
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_DCVS_SUCCESS_MASK_BMSK                        0x200
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_DCVS_SUCCESS_MASK_SHFT                            9
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_TIMEOUT_MASK_BMSK                             0x100
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_TIMEOUT_MASK_SHFT                                 8
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_FLOOR_UPDATED_MASK_BMSK                        0x80
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_FLOOR_UPDATED_MASK_SHFT                           7
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_ERROR_VMIN_MASK_BMSK                           0x40
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_ERROR_VMIN_MASK_SHFT                              6
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_ERROR_VMAX_MASK_BMSK                           0x20
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_ERROR_VMAX_MASK_SHFT                              5
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_NEW_CPRC_RECOMM_MASK_BMSK                      0x10
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_NEW_CPRC_RECOMM_MASK_SHFT                         4
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_NEW_VOLTAGE_VOTE_MASK_BMSK                      0x8
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_NEW_VOLTAGE_VOTE_MASK_SHFT                        3
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_PR_OL_CHANGED_MASK_BMSK                         0x4
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_PR_OL_CHANGED_MASK_SHFT                           2
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_CXO_ENABLED_MASK_BMSK                           0x2
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_CXO_ENABLED_MASK_SHFT                             1
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_CXO_DISABLED_MASK_BMSK                          0x1
#define HWIO_RPMH_CPRF_CPRFm_INTERRUPT_MASK_CXO_DISABLED_MASK_SHFT                            0

#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_ADDR(m)                                       (RPMH_CPRF_CPRF_REG_BASE            + 0X1228 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_PHYS(m)                                       (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1228 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_OFFS(m)                                       (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1228 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_RMSK                                              0x3fff
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_MAXm                                                   9
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_ADDR(m), HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_SW_PR_POST_REQ_BMSK                               0x2000
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_SW_PR_POST_REQ_SHFT                                   13
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_SW_PR_CHANGE_REQ_BMSK                             0x1000
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_SW_PR_CHANGE_REQ_SHFT                                 12
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_SW_PR_PRE_REQ_BMSK                                 0x800
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_SW_PR_PRE_REQ_SHFT                                    11
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_SW_PR_DEST_OL_BMSK                                 0x7c0
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_SW_PR_DEST_OL_SHFT                                     6
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_SW_PR_CUR_OL_BMSK                                   0x3e
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_SW_PR_CUR_OL_SHFT                                      1
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_PR_ARC_WA_EN_BMSK                                    0x1
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_WA_PR_ARC_WA_EN_SHFT                                      0

#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_ADDR(m)                                      (RPMH_CPRF_CPRF_REG_BASE            + 0X122C + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_PHYS(m)                                      (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X122C + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_OFFS(m)                                      (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X122C + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_RMSK                                                0x7
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_MAXm                                                  9
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_ADDR(m), HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_CLOCK_CHANGED_BMSK                                  0x4
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_CLOCK_CHANGED_SHFT                                    2
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_SW_CLOCK_STATE_BMSK                                 0x2
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_SW_CLOCK_STATE_SHFT                                   1
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_CXO_ARC_WA_EN_BMSK                                  0x1
#define HWIO_RPMH_CPRF_CPRFm_ARC_CXO_WA_CXO_ARC_WA_EN_SHFT                                    0

#define HWIO_RPMH_CPRF_CPRFm_VALUES_ADDR(m)                                          (RPMH_CPRF_CPRF_REG_BASE            + 0X1230 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_PHYS(m)                                          (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1230 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_OFFS(m)                                          (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1230 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_RMSK                                              0x3ff1fff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_MAXm                                                      9
#define HWIO_RPMH_CPRF_CPRFm_VALUES_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_ADDR(m), HWIO_RPMH_CPRF_CPRFm_VALUES_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_ERROR_STEPS_BMSK                                  0x3e00000
#define HWIO_RPMH_CPRF_CPRFm_VALUES_ERROR_STEPS_SHFT                                         21
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CUR_OL_BMSK                                        0x1f0000
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CUR_OL_SHFT                                              16
#define HWIO_RPMH_CPRF_CPRFm_VALUES_TENT_VOL_BMSK                                        0x1fff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_TENT_VOL_SHFT                                             0

#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_ADDR(m)                                   (RPMH_CPRF_CPRF_REG_BASE            + 0X1234 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_PHYS(m)                                   (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1234 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_OFFS(m)                                   (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1234 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_RMSK                                           0x3ff
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_MAXm                                               9
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_ADDR(m), HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_TOLERANCE_BMSK                                 0x3e0
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_TOLERANCE_SHFT                                     5
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_STEP_BMSK                                       0x1f
#define HWIO_RPMH_CPRF_CPRFm_STEP_SETTINGS_STEP_SHFT                                          0

#define HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_ADDR(m)                                  (RPMH_CPRF_CPRF_REG_BASE            + 0X1238 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_PHYS(m)                                  (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1238 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_OFFS(m)                                  (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1238 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_RMSK                                         0x1fff
#define HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_MAXm                                              9
#define HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_ADDR(m), HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_RUNNING_FLOOR_BMSK                           0x1fff
#define HWIO_RPMH_CPRF_CPRFm_FLOOR_SETTINGS_RUNNING_FLOOR_SHFT                                0

#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_ADDR(m)                                         (RPMH_CPRF_CPRF_REG_BASE            + 0X123C + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_PHYS(m)                                         (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X123C + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_OFFS(m)                                         (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X123C + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_RMSK                                            0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_MAXm                                                     9
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_TIMEOUT_ADDR(m), HWIO_RPMH_CPRF_CPRFm_TIMEOUT_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_TIMEOUT_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_TIMEOUT_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_TIMEOUT_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_TIMEOUT_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_COUNT_BMSK                                      0xfffffffe
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_COUNT_SHFT                                               1
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_ENABLE_BMSK                                            0x1
#define HWIO_RPMH_CPRF_CPRFm_TIMEOUT_ENABLE_SHFT                                              0

#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_ADDR(m)                                     (RPMH_CPRF_CPRF_REG_BASE            + 0X1240 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_PHYS(m)                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1240 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_OFFS(m)                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1240 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_RMSK                                             0x3ff
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_MAXm                                                 9
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_ADDR(m), HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_OL_ON_VOTE_BMSK                                  0x3e0
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_OL_ON_VOTE_SHFT                                      5
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_OL_ON_BMSK                                        0x1f
#define HWIO_RPMH_CPRF_CPRFm_ON_SETTINGS_OL_ON_SHFT                                           0

#define HWIO_RPMH_CPRF_CPRFm_VALUES_1_ADDR(m)                                        (RPMH_CPRF_CPRF_REG_BASE            + 0X1244 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_1_PHYS(m)                                        (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1244 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_1_OFFS(m)                                        (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1244 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_1_RMSK                                           0x1fff1fff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_1_MAXm                                                    9
#define HWIO_RPMH_CPRF_CPRFm_VALUES_1_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_1_ADDR(m), HWIO_RPMH_CPRF_CPRFm_VALUES_1_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_1_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_1_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_1_CURRENT_VOL_BMSK                               0x1fff0000
#define HWIO_RPMH_CPRF_CPRFm_VALUES_1_CURRENT_VOL_SHFT                                       16
#define HWIO_RPMH_CPRF_CPRFm_VALUES_1_VOL_VOTE_BMSK                                      0x1fff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_1_VOL_VOTE_SHFT                                           0

#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_ADDR(m)                                (RPMH_CPRF_CPRF_REG_BASE            + 0X1248 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_PHYS(m)                                (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1248 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_OFFS(m)                                (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1248 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_RMSK                                          0x3
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_MAXm                                            9
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_ADDR(m), HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_ENDIANNESS_BMSK                               0x2
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_ENDIANNESS_SHFT                                 1
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_SWAP_BMSK                                     0x1
#define HWIO_RPMH_CPRF_CPRFm_ARC_PR_BIT_ORDER_SWAP_SHFT                                       0

#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_ADDR(m,n)                                       (RPMH_CPRF_CPRF_REG_BASE            + 0X124C + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_PHYS(m,n)                                       (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X124C + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_OFFS(m,n)                                       (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X124C + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_RMSK                                                 0x1ff
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_MAXm                                                     9
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_MAXn                                                    15
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_INI2(m,n)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DELTA_n_ADDR(m,n), HWIO_RPMH_CPRF_CPRFm_DELTA_n_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DELTA_n_ADDR(m,n), mask)
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_OUTI2(m,n,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_DELTA_n_ADDR(m,n),val)
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_DELTA_n_ADDR(m,n),mask,val,HWIO_RPMH_CPRF_CPRFm_DELTA_n_INI2(m,n))
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_MAX_BMSK                                             0x1fe
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_MAX_SHFT                                                 1
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_EN_BMSK                                                0x1
#define HWIO_RPMH_CPRF_CPRFm_DELTA_n_EN_SHFT                                                  0

#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_ADDR(m)                                  (RPMH_CPRF_CPRF_REG_BASE            + 0X12CC + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_PHYS(m)                                  (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X12CC + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_OFFS(m)                                  (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X12CC + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_RMSK                                            0x3
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_MAXm                                              9
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_ADDR(m), HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_INI(m))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_RESET_UD_COUNT_BMSK                             0x2
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_RESET_UD_COUNT_SHFT                               1
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_RESET_OL_COUNT_BMSK                             0x1
#define HWIO_RPMH_CPRF_CPRFm_VALUES_CONTROL_RESET_OL_COUNT_SHFT                               0

#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_ADDR(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE            + 0X12D0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_PHYS(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X12D0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_OFFS(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X12D0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_RMSK                                         0x1fff1fff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_MAXm                                                  9
#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_MAXn                                                 15
#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_INI2(m,n)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_ADDR(m,n), HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_ADDR(m,n), mask)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_MAX_VOL_BMSK                                 0x1fff0000
#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_MAX_VOL_SHFT                                         16
#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_MIN_VOL_BMSK                                     0x1fff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_2_n_MIN_VOL_SHFT                                          0

#define HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_ADDR(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE            + 0X1350 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_PHYS(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1350 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_OFFS(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1350 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_RMSK                                             0x1fff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_MAXm                                                  9
#define HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_MAXn                                                 15
#define HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_INI2(m,n)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_ADDR(m,n), HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_ADDR(m,n), mask)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_LAST_VOL_BMSK                                    0x1fff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_3_n_LAST_VOL_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_ADDR(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE            + 0X13D0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_PHYS(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X13D0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_OFFS(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X13D0 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_RMSK                                               0xff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_MAXm                                                  9
#define HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_MAXn                                                 15
#define HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_INI2(m,n)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_ADDR(m,n), HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_ADDR(m,n), mask)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_OL_COUNT_BMSK                                      0xff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_4_n_OL_COUNT_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_ADDR(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE            + 0X1450 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_PHYS(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1450 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_OFFS(m,n)                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1450 + (0x1000*(m)) + (0x4*(n)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_RMSK                                           0xff00ff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_MAXm                                                  9
#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_MAXn                                                 15
#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_INI2(m,n)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_ADDR(m,n), HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_ADDR(m,n), mask)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_DOWN_COUNT_BMSK                                0xff0000
#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_DOWN_COUNT_SHFT                                      16
#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_UP_COUNT_BMSK                                      0xff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_5_n_UP_COUNT_SHFT                                         0

#define HWIO_RPMH_CPRF_CPRFm_VALUES_6_ADDR(m)                                        (RPMH_CPRF_CPRF_REG_BASE            + 0X1550 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_6_PHYS(m)                                        (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0X1550 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_6_OFFS(m)                                        (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0X1550 + (0x1000*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VALUES_6_RMSK                                               0x1fff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_6_MAXm                                                    9
#define HWIO_RPMH_CPRF_CPRFm_VALUES_6_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_6_ADDR(m), HWIO_RPMH_CPRF_CPRFm_VALUES_6_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_6_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VALUES_6_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_VALUES_6_LAST_VOTED_VOL_BMSK                                0x1fff
#define HWIO_RPMH_CPRF_CPRFm_VALUES_6_LAST_VOTED_VOL_SHFT                                     0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_ADDR(m)                                    (RPMH_CPRF_CPRF_REG_BASE            + 0XC000 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_PHYS(m)                                    (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC000 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_OFFS(m)                                    (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC000 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_RMSK                                              0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_MAXm                                                9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_INI(m))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_SW_RESET_BMSK                                     0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_RESET_SW_RESET_SHFT                                       0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_ADDR(m)                                     (RPMH_CPRF_CPRF_REG_BASE            + 0XC004 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_PHYS(m)                                     (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC004 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_OFFS(m)                                     (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC004 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_RMSK                                               0x7
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_MAXm                                                 9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_INI(m))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_PR_HANDSHAKE_EN_BMSK                               0x4
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_PR_HANDSHAKE_EN_SHFT                                 2
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_CTRL_INTERACTION_EN_BMSK                           0x2
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_CTRL_INTERACTION_EN_SHFT                             1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_CLOCK_MGMT_EN_BMSK                                 0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_CTRL_CLOCK_MGMT_EN_SHFT                                   0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_ADDR(m)                         (RPMH_CPRF_CPRF_REG_BASE            + 0XC008 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_PHYS(m)                         (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC008 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_OFFS(m)                         (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC008 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_RMSK                                  0x1f
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_MAXm                                     9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_INI(m))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_INITIAL_OL_BMSK                       0x1f
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INITIAL_SETTINGS_INITIAL_OL_SHFT                          0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_ADDR(m)                                   (RPMH_CPRF_CPRF_REG_BASE            + 0XC00C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_PHYS(m)                                   (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC00C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_OFFS(m)                                   (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC00C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_RMSK                                             0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_MAXm                                               9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_INI(m))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_EN_BMSK                                          0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ENABLE_EN_SHFT                                            0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_ADDR(m)                           (RPMH_CPRF_CPRF_REG_BASE            + 0XC010 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_PHYS(m)                           (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC010 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_OFFS(m)                           (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC010 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_RMSK                                     0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_MAXm                                       9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_INI(m))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_FORCE_INITIAL_0_BMSK                     0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_FORCE_SETTINGS_FORCE_INITIAL_0_SHFT                       0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_ADDR(m)                         (RPMH_CPRF_CPRF_REG_BASE            + 0XC014 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_PHYS(m)                         (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC014 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_OFFS(m)                         (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC014 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_RMSK                                   0x7
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_MAXm                                     9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_PR_OL_CHANGED_INT_BMSK                 0x4
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_PR_OL_CHANGED_INT_SHFT                   2
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_CXO_ENABLED_INT_BMSK                   0x2
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_CXO_ENABLED_INT_SHFT                     1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_CXO_DISABLED_INT_BMSK                  0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_STATUS_CXO_DISABLED_INT_SHFT                    0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_ADDR(m)                            (RPMH_CPRF_CPRF_REG_BASE            + 0XC014 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_PHYS(m)                            (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC014 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_OFFS(m)                            (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC014 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_RMSK                                      0x7
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_MAXm                                        9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_PR_OL_CHANGED_ACK_BMSK                    0x4
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_PR_OL_CHANGED_ACK_SHFT                      2
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_CXO_ENABLED_ACK_BMSK                      0x2
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_CXO_ENABLED_ACK_SHFT                        1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_CXO_DISABLED_ACK_BMSK                     0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_ACK_CXO_DISABLED_ACK_SHFT                       0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_ADDR(m)                           (RPMH_CPRF_CPRF_REG_BASE            + 0XC018 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_PHYS(m)                           (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC018 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_OFFS(m)                           (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC018 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_RMSK                                     0x7
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_MAXm                                       9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_INI(m))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_PR_OL_CHANGED_MASK_BMSK                  0x4
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_PR_OL_CHANGED_MASK_SHFT                    2
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_CXO_ENABLED_MASK_BMSK                    0x2
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_CXO_ENABLED_MASK_SHFT                      1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_CXO_DISABLED_MASK_BMSK                   0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_INTERRUPT_MASK_CXO_DISABLED_MASK_SHFT                     0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_ADDR(m)                                (RPMH_CPRF_CPRF_REG_BASE            + 0XC01C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_PHYS(m)                                (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC01C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_OFFS(m)                                (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC01C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_RMSK                                       0x3fff
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_MAXm                                            9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_INI(m))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_SW_PR_POST_REQ_BMSK                        0x2000
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_SW_PR_POST_REQ_SHFT                            13
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_SW_PR_CHANGE_REQ_BMSK                      0x1000
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_SW_PR_CHANGE_REQ_SHFT                          12
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_SW_PR_PRE_REQ_BMSK                          0x800
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_SW_PR_PRE_REQ_SHFT                             11
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_SW_PR_DEST_OL_BMSK                          0x7c0
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_SW_PR_DEST_OL_SHFT                              6
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_SW_PR_CUR_OL_BMSK                            0x3e
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_SW_PR_CUR_OL_SHFT                               1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_PR_ARC_WA_EN_BMSK                             0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_WA_PR_ARC_WA_EN_SHFT                               0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_ADDR(m)                               (RPMH_CPRF_CPRF_REG_BASE            + 0XC020 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_PHYS(m)                               (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC020 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_OFFS(m)                               (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC020 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_RMSK                                         0x7
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_MAXm                                           9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_INI(m))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_CLOCK_CHANGED_BMSK                           0x4
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_CLOCK_CHANGED_SHFT                             2
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_SW_CLOCK_STATE_BMSK                          0x2
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_SW_CLOCK_STATE_SHFT                            1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_CXO_ARC_WA_EN_BMSK                           0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_CXO_WA_CXO_ARC_WA_EN_SHFT                             0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_ADDR(m)                                   (RPMH_CPRF_CPRF_REG_BASE            + 0XC024 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_PHYS(m)                                   (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC024 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_OFFS(m)                                   (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC024 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_RMSK                                            0x1f
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_MAXm                                               9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_CUR_OL_BMSK                                     0x1f
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_VALUES_CUR_OL_SHFT                                        0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_ADDR(m)                              (RPMH_CPRF_CPRF_REG_BASE            + 0XC028 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_PHYS(m)                              (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC028 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_OFFS(m)                              (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC028 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_RMSK                                       0x1f
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_MAXm                                          9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_INI(m))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_OL_ON_BMSK                                 0x1f
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ON_SETTINGS_OL_ON_SHFT                                    0

#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_ADDR(m)                         (RPMH_CPRF_CPRF_REG_BASE            + 0XC02C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_PHYS(m)                         (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC02C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_OFFS(m)                         (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC02C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_RMSK                                   0x3
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_MAXm                                     9
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_ADDR(m), HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_RMSK)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_OUTI(m,val)        \
                out_dword(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_ADDR(m),val)
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_ADDR(m),mask,val,HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_INI(m))
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_ENDIANNESS_BMSK                        0x2
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_ENDIANNESS_SHFT                          1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_SWAP_BMSK                              0x1
#define HWIO_RPMH_CPRF_CPRF_VSENSEm_ARC_PR_BIT_ORDER_SWAP_SHFT                                0

#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_ADDR(m)                               (RPMH_CPRF_CPRF_REG_BASE            + 0XC030 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_PHYS(m)                               (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC030 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_OFFS(m)                               (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC030 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_RMSK                                  0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_MAXm                                           9
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_ADDR(m), HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_DEBUG_VECTOR_BMSK                     0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS0_DEBUG_VECTOR_SHFT                              0

#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_ADDR(m)                               (RPMH_CPRF_CPRF_REG_BASE            + 0XC034 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_PHYS(m)                               (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC034 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_OFFS(m)                               (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC034 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_RMSK                                  0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_MAXm                                           9
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_ADDR(m), HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_DEBUG_VECTOR_BMSK                     0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED0_BUS1_DEBUG_VECTOR_SHFT                              0

#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_ADDR(m)                               (RPMH_CPRF_CPRF_REG_BASE            + 0XC038 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_PHYS(m)                               (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC038 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_OFFS(m)                               (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC038 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_RMSK                                  0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_MAXm                                           9
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_ADDR(m), HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_DEBUG_VECTOR_BMSK                     0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS0_DEBUG_VECTOR_SHFT                              0

#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_ADDR(m)                               (RPMH_CPRF_CPRF_REG_BASE            + 0XC03C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_PHYS(m)                               (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC03C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_OFFS(m)                               (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC03C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_RMSK                                  0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_MAXm                                           9
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_ADDR(m), HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_DEBUG_VECTOR_BMSK                     0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED1_BUS1_DEBUG_VECTOR_SHFT                              0

#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_ADDR(m)                               (RPMH_CPRF_CPRF_REG_BASE            + 0XC040 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_PHYS(m)                               (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC040 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_OFFS(m)                               (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC040 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_RMSK                                  0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_MAXm                                           9
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_ADDR(m), HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_DEBUG_VECTOR_BMSK                     0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS0_DEBUG_VECTOR_SHFT                              0

#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_ADDR(m)                               (RPMH_CPRF_CPRF_REG_BASE            + 0XC044 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_PHYS(m)                               (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC044 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_OFFS(m)                               (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC044 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_RMSK                                  0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_MAXm                                           9
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_ADDR(m), HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_DEBUG_VECTOR_BMSK                     0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED2_BUS1_DEBUG_VECTOR_SHFT                              0

#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_ADDR(m)                               (RPMH_CPRF_CPRF_REG_BASE            + 0XC048 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_PHYS(m)                               (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC048 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_OFFS(m)                               (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC048 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_RMSK                                  0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_MAXm                                           9
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_ADDR(m), HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_DEBUG_VECTOR_BMSK                     0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS0_DEBUG_VECTOR_SHFT                              0

#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_ADDR(m)                               (RPMH_CPRF_CPRF_REG_BASE            + 0XC04C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_PHYS(m)                               (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC04C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_OFFS(m)                               (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC04C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_RMSK                                  0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_MAXm                                           9
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_ADDR(m), HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_DEBUG_VECTOR_BMSK                     0xffffffff
#define HWIO_RPMH_CPRF_CPRFm_DEBUG_MUXED3_BUS1_DEBUG_VECTOR_SHFT                              0

#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_ADDR(m)                                 (RPMH_CPRF_CPRF_REG_BASE            + 0XC050 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_PHYS(m)                                 (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC050 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_OFFS(m)                                 (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC050 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_RMSK                                        0x3fff
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_MAXm                                             9
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_ADDR(m), HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_DEBUG_CAPTURE_BMSK                          0x3fff
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC0_DEBUG_CAPTURE_SHFT                               0

#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_ADDR(m)                                 (RPMH_CPRF_CPRF_REG_BASE            + 0XC054 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_PHYS(m)                                 (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC054 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_OFFS(m)                                 (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC054 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_RMSK                                        0x3fff
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_MAXm                                             9
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_ADDR(m), HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_DEBUG_CAPTURE_BMSK                          0x3fff
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC1_DEBUG_CAPTURE_SHFT                               0

#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_ADDR(m)                                 (RPMH_CPRF_CPRF_REG_BASE            + 0XC058 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_PHYS(m)                                 (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC058 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_OFFS(m)                                 (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC058 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_RMSK                                        0x3fff
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_MAXm                                             9
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_ADDR(m), HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_DEBUG_CAPTURE_BMSK                          0x3fff
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC2_DEBUG_CAPTURE_SHFT                               0

#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_ADDR(m)                                 (RPMH_CPRF_CPRF_REG_BASE            + 0XC05C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_PHYS(m)                                 (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC05C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_OFFS(m)                                 (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC05C + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_RMSK                                        0x3fff
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_MAXm                                             9
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_ADDR(m), HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_DEBUG_CAPTURE_BMSK                          0x3fff
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC3_DEBUG_CAPTURE_SHFT                               0

#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_ADDR(m)                                 (RPMH_CPRF_CPRF_REG_BASE            + 0XC060 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_PHYS(m)                                 (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC060 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_OFFS(m)                                 (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC060 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_RMSK                                        0x3fff
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_MAXm                                             9
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_ADDR(m), HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_DEBUG_CAPTURE_BMSK                          0x3fff
#define HWIO_RPMH_CPRF_CPRFm_VFSM_DEBUG_LOC4_DEBUG_CAPTURE_SHFT                               0

#define HWIO_RPMH_CPRF_CPRFm_VFSM_REG_ADDR(m)                                        (RPMH_CPRF_CPRF_REG_BASE            + 0XC064 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_REG_PHYS(m)                                        (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0XC064 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_REG_OFFS(m)                                        (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0XC064 + (0x200*(m)))
#define HWIO_RPMH_CPRF_CPRFm_VFSM_REG_RMSK                                                  0x7
#define HWIO_RPMH_CPRF_CPRFm_VFSM_REG_MAXm                                                    9
#define HWIO_RPMH_CPRF_CPRFm_VFSM_REG_INI(m)                \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_REG_ADDR(m), HWIO_RPMH_CPRF_CPRFm_VFSM_REG_RMSK)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_REG_INMI(m,mask)        \
                in_dword_masked(HWIO_RPMH_CPRF_CPRFm_VFSM_REG_ADDR(m), mask)
#define HWIO_RPMH_CPRF_CPRFm_VFSM_REG_WR_PTR_BMSK                                           0x7
#define HWIO_RPMH_CPRF_CPRFm_VFSM_REG_WR_PTR_SHFT                                             0

#define HWIO_RPMH_CPRF_VRM_MESSAGE_ADDR                                              (RPMH_CPRF_CPRF_REG_BASE            + 0xf000)
#define HWIO_RPMH_CPRF_VRM_MESSAGE_PHYS                                              (RPMH_CPRF_CPRF_REG_BASE_PHYS + 0xf000)
#define HWIO_RPMH_CPRF_VRM_MESSAGE_OFFS                                              (RPMH_CPRF_CPRF_REG_BASE_OFFS + 0xf000)
#define HWIO_RPMH_CPRF_VRM_MESSAGE_RMSK                                                  0xffff
#define HWIO_RPMH_CPRF_VRM_MESSAGE_IN                    \
                in_dword(HWIO_RPMH_CPRF_VRM_MESSAGE_ADDR)
#define HWIO_RPMH_CPRF_VRM_MESSAGE_INM(m)            \
                in_dword_masked(HWIO_RPMH_CPRF_VRM_MESSAGE_ADDR, m)
#define HWIO_RPMH_CPRF_VRM_MESSAGE_OUT(v)            \
                out_dword(HWIO_RPMH_CPRF_VRM_MESSAGE_ADDR,v)
#define HWIO_RPMH_CPRF_VRM_MESSAGE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_CPRF_VRM_MESSAGE_ADDR,m,v,HWIO_RPMH_CPRF_VRM_MESSAGE_IN)
#define HWIO_RPMH_CPRF_VRM_MESSAGE_COMPLETION_BMSK                                       0xffff
#define HWIO_RPMH_CPRF_VRM_MESSAGE_COMPLETION_SHFT                                            0


#endif /* __CPRF_HWIO_H__ */
