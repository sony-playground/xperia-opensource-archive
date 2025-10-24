#ifndef __RSC_HWIO_H__
#define __RSC_HWIO_H__
/*
===========================================================================
*/
/**
    @file rsc_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8550 (Kailua) [kailua_v1.0_p3q3r10.0_rtl_partition_MTO]
 
    This file contains HWIO register definitions for the following modules:
        APSS_RSC_RSCC_RSCC_RSC


    Generation parameters: 
    { 'filename': 'rsc_hwio.h',
      'header': '#include "msmhwiobase.h"\n#include "HALhwio.h"',
      'modules': ['APSS_RSC_RSCC_RSCC_RSC']}
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

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Include/rsc_hwio.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"
#include "HALhwio.h"

/*----------------------------------------------------------------------------
 * MODULE: APSS_RSC_RSCC_RSCC_RSC
 *--------------------------------------------------------------------------*/

#define APSS_RSC_RSCC_RSCC_RSC_REG_BASE                                                                              (APSS_HM_BASE      + 0x00a00000)
#define APSS_RSC_RSCC_RSCC_RSC_REG_BASE_SIZE                                                                         0x40000
#define APSS_RSC_RSCC_RSCC_RSC_REG_BASE_USED                                                                         0x313f0

#define HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_ADDR(d)                                                                       (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X0 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_RMSK                                                                            0xffffff
#define HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_MAXd                                                                                   3
#define HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_MAJOR_VER_BMSK                                                                  0xff0000
#define HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_MAJOR_VER_SHFT                                                                        16
#define HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_MINOR_VER_BMSK                                                                    0xff00
#define HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_MINOR_VER_SHFT                                                                         8
#define HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_STEP_VER_BMSK                                                                       0xff
#define HWIO_APSS_RSC_RSCC_RSC_ID_DRVd_STEP_VER_SHFT                                                                          0

#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_ADDR(d)                                                      (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X4 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_RMSK                                                          0x71f1f1f
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_MAXd                                                                  3
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SEQ_EXTENDED_BMSK                                             0x4000000
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SEQ_EXTENDED_SHFT                                                    26
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_IS_CHILD_RSC_BMSK                                             0x2000000
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_IS_CHILD_RSC_SHFT                                                    25
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_HW_SOLVER_BMSK                                                0x1000000
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_HW_SOLVER_SHFT                                                       24
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_SLOTS_BMSK                                              0x1f0000
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_SLOTS_SHFT                                                    16
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_MODES_BMSK                                                0x1f00
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_MODES_SHFT                                                     8
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_NUM_TIMERS_BMSK                                                    0x1f
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_NUM_TIMERS_SHFT                                                       0

#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_ADDR(d)                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X8 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_RMSK                                                             0x7ff0f1f
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_MAXd                                                                     3
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_DRV_BMSK                                                     0x7000000
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_DRV_SHFT                                                            24
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_SEQ_CMD_WORDS_BMSK                                            0xff0000
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_SEQ_CMD_WORDS_SHFT                                                  16
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_TS_EVENTS_BMSK                                                   0xf00
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_TS_EVENTS_SHFT                                                       8
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_DELAY_CNTR_BITWIDTH_BMSK                                              0x1f
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_DELAY_CNTR_BITWIDTH_SHFT                                                 0

#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_ADDR(d)                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XC + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_RMSK                                                0xf8ffffff
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_MAXd                                                         3
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_CMDS_PER_TCS_BMSK                               0xf8000000
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_CMDS_PER_TCS_SHFT                                       27
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV3_BMSK                                     0xfc0000
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV3_SHFT                                           18
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV2_BMSK                                      0x3f000
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV2_SHFT                                           12
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV1_BMSK                                        0xfc0
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV1_SHFT                                            6
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV0_BMSK                                         0x3f
#define HWIO_APSS_RSC_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV0_SHFT                                            0

#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_ADDR(d)                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_RMSK                                                                      0x101ffff
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_MAXd                                                                              3
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_OUTI(d,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_ADDR(d),val)
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_ADDR(d),mask,val,HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_INI(d))
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_CLK_GATE_DISABLE_BMSK                                                     0x1000000
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_CLK_GATE_DISABLE_SHFT                                                            24
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_ENTRY_DONE_BMSK                                                0x10000
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_ENTRY_DONE_SHFT                                                     16
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_CTL_FSM_BMSK                                                    0xffff
#define HWIO_APSS_RSC_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_CTL_FSM_SHFT                                                         0

#define HWIO_APSS_RSC_RSCC_RSC_STATUS1_DRVd_ADDR(d)                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X14 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_STATUS1_DRVd_RMSK                                                                     0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_STATUS1_DRVd_MAXd                                                                              3
#define HWIO_APSS_RSC_RSCC_RSC_STATUS1_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_STATUS1_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_STATUS1_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_STATUS1_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_STATUS1_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_STATUS1_DRVd_PDC_MATCH_VALUE_LO_BMSK                                                  0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_STATUS1_DRVd_PDC_MATCH_VALUE_LO_SHFT                                                           0

#define HWIO_APSS_RSC_RSCC_RSC_STATUS2_DRVd_ADDR(d)                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X18 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_STATUS2_DRVd_RMSK                                                                       0xffffff
#define HWIO_APSS_RSC_RSCC_RSC_STATUS2_DRVd_MAXd                                                                              3
#define HWIO_APSS_RSC_RSCC_RSC_STATUS2_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_STATUS2_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_STATUS2_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_STATUS2_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_STATUS2_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_STATUS2_DRVd_PDC_MATCH_VALUE_HI_BMSK                                                    0xffffff
#define HWIO_APSS_RSC_RSCC_RSC_STATUS2_DRVd_PDC_MATCH_VALUE_HI_SHFT                                                           0

#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x1c)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_RMSK                                                                    0x10003
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_TRIGGER_BMSK                                                 0x10000
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_TRIGGER_SHFT                                                      16
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_PDC_TIMER_DRV_OWNER_BMSK                                         0x3
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_PDC_TIMER_DRV_OWNER_SHFT                                           0

#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRVd_ADDR(d)                                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X1C + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRVd_RMSK                                                                        0x3
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRVd_MAXd                                                                          3
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRVd_HIDDEN_TCS_PDC_TIMER_DRV_OWNER_BMSK                                         0x3
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CTRL_DRVd_HIDDEN_TCS_PDC_TIMER_DRV_OWNER_SHFT                                           0

#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR                                                   (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x20)
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_RMSK                                                       0xffff
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_PDC_SEQ_START_ADDR_REG_OFFSET_BMSK                         0xffff
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_PDC_SEQ_START_ADDR_REG_OFFSET_SHFT                              0

#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_ADDR(d)                                                (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_RMSK                                                       0xffff
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_MAXd                                                            3
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_PDC_SEQ_START_ADDR_REG_OFFSET_BMSK                         0xffff
#define HWIO_APSS_RSC_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_PDC_SEQ_START_ADDR_REG_OFFSET_SHFT                              0

#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR                                                   (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x24)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_RMSK                                                       0xffff
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_PDC_MATCH_VALUE_LO_REG_OFFSET_BMSK                         0xffff
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_PDC_MATCH_VALUE_LO_REG_OFFSET_SHFT                              0

#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_ADDR(d)                                                (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X24 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_RMSK                                                       0xffff
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_MAXd                                                            3
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_PDC_MATCH_VALUE_LO_REG_OFFSET_BMSK                         0xffff
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_PDC_MATCH_VALUE_LO_REG_OFFSET_SHFT                              0

#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR                                                   (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x28)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_RMSK                                                       0xffff
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_PDC_MATCH_VALUE_HI_REG_OFFSET_BMSK                         0xffff
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_PDC_MATCH_VALUE_HI_REG_OFFSET_SHFT                              0

#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_ADDR(d)                                                (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X28 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_RMSK                                                       0xffff
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_MAXd                                                            3
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_PDC_MATCH_VALUE_HI_REG_OFFSET_BMSK                         0xffff
#define HWIO_APSS_RSC_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_PDC_MATCH_VALUE_HI_REG_OFFSET_SHFT                              0

#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_ADDR                                                                    (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x2c)
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_RMSK                                                                           0x7
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_PDC_SLAVE_ID_BMSK                                                              0x7
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRV0_PDC_SLAVE_ID_SHFT                                                                0

#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRVd_ADDR(d)                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X2C + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRVd_RMSK                                                                           0x7
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRVd_MAXd                                                                             3
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRVd_PDC_SLAVE_ID_BMSK                                                              0x7
#define HWIO_APSS_RSC_RSCC_PDC_SLAVE_ID_DRVd_PDC_SLAVE_ID_SHFT                                                                0

#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_ADDR(d)                                                            (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_RMSK                                                                  0x70707
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_MAXd                                                                        3
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_COMPLETED_BMSK                                                        0x70000
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_COMPLETED_SHFT                                                             16
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_ISSUED_BMSK                                                             0x700
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_ISSUED_SHFT                                                                 8
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_TRIGGERED_BMSK                                                            0x7
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_STATUS_DRVd_TRIGGERED_SHFT                                                              0

#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR(d)                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X34 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_RMSK                                                            0xffffffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_MAXd                                                                     3
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR_BMSK                                                       0xffffffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR_SHFT                                                                0

#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d)                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X38 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_RMSK                                                            0x80ffffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_MAXd                                                                     3
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_OUTI(d,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d),val)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d),mask,val,HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_INI(d))
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_VALID_BMSK                                      0x80000000
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_VALID_SHFT                                              31
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_HI_BMSK                                           0xffffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_HI_SHFT                                                  0

#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR(d)                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X3C + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_RMSK                                                            0xffffffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_MAXd                                                                     3
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR_BMSK                                                       0xffffffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR_SHFT                                                                0

#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d)                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X40 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_RMSK                                                            0xffffffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_MAXd                                                                     3
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_OUTI(d,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d),val)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d),mask,val,HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_INI(d))
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_PDC_MATCH_VALUE_LO_BMSK                                         0xffffffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_PDC_MATCH_VALUE_LO_SHFT                                                  0

#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR(d)                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X44 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_RMSK                                                            0xffffffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_MAXd                                                                     3
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR_BMSK                                                       0xffffffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR_SHFT                                                                0

#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR                                                            (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x48)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_RMSK                                                            0x8000ffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_VALID_BMSK                                   0x80000000
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_VALID_SHFT                                           31
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_BMSK                                             0xffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_SHFT                                                  0

#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_ADDR(d)                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X48 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_RMSK                                                            0x8000ffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_MAXd                                                                     3
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_PDC_SEQ_START_ADDR_VALID_BMSK                                   0x80000000
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_PDC_SEQ_START_ADDR_VALID_SHFT                                           31
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_PDC_SEQ_START_ADDR_BMSK                                             0xffff
#define HWIO_APSS_RSC_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_PDC_SEQ_START_ADDR_SHFT                                                  0

#define HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_ADDR                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x4c)
#define HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_RMSK                                                                         0x3
#define HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_OWNER_BMSK                                                                   0x3
#define HWIO_APSS_RSC_RSCC_HW_EVENT_OWNER_DRV0_OWNER_SHFT                                                                     0

#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m)                                                       (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X50 + (0x10000*(d)) + (0x4*(m)))
#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_RMSK                                                            0x80000007
#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_MAXd                                                                     3
#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_MAXm                                                                    31
#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m), HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m), mask)
#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_OUTI2(d,m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m),val)
#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_OUTMI2(d,m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m),mask,val,HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_INI2(d,m))
#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ENABLE_BMSK                                                     0x80000000
#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ENABLE_SHFT                                                             31
#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_EVENT_SELECT_BMSK                                                      0x7
#define HWIO_APSS_RSC_RSCC_HW_EVENT_MUXm_SELECT_DRVd_EVENT_SELECT_SHFT                                                        0

#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_ADDR                                                            (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0xd0)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_RMSK                                                                   0x1
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_EPCB_TIMEOUT_IRQ_BMSK                                                  0x1
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_EPCB_TIMEOUT_IRQ_SHFT                                                    0

#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_ADDR(d)                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD0 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_RMSK                                                                   0x1
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_MAXd                                                                     3
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_EPCB_TIMEOUT_IRQ_BMSK                                                  0x1
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_EPCB_TIMEOUT_IRQ_SHFT                                                    0

#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_ADDR                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0xd4)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_RMSK                                                                    0x1
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_CLR_EPCB_TIMEOUT_IRQ_BMSK                                               0x1
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_CLR_EPCB_TIMEOUT_IRQ_SHFT                                                 0

#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR                                                            (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0xd8)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_RMSK                                                              0x10ffff
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_IRQ_EN_BMSK                                          0x100000
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_IRQ_EN_SHFT                                                20
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_THRESHOLD_BMSK                                         0xffff
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_THRESHOLD_SHFT                                              0

#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_ADDR(d)                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD8 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_RMSK                                                              0x10ffff
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_MAXd                                                                     3
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_EPCB_TIMEOUT_IRQ_EN_BMSK                                          0x100000
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_EPCB_TIMEOUT_IRQ_EN_SHFT                                                20
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_EPCB_TIMEOUT_THRESHOLD_BMSK                                         0xffff
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_EPCB_TIMEOUT_THRESHOLD_SHFT                                              0

#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x100)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_RMSK                                                                    0x1
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ERROR_RESP_FOR_INVALID_ADDR_BMSK                                        0x1
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ERROR_RESP_FOR_INVALID_ADDR_SHFT                                          0

#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRVd_ADDR(d)                                                          (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X100 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRVd_RMSK                                                                    0x1
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRVd_MAXd                                                                      3
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRVd_ERROR_RESP_FOR_INVALID_ADDR_BMSK                                        0x1
#define HWIO_APSS_RSC_RSCC_RSC_ERROR_RESP_CTRL_DRVd_ERROR_RESP_FOR_INVALID_ADDR_SHFT                                          0

#define HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x104)
#define HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_RMSK                                                                    0x1
#define HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_SECURE_OVERRIDE_BMSK                                                    0x1
#define HWIO_APSS_RSC_RSCC_RSC_SECURE_OVERRIDE_DRV0_SECURE_OVERRIDE_SHFT                                                      0

#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR                                                     (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x108)
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_RMSK                                                            0x1
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_RIF_CLK_GATING_OVERRIDE_BMSK                                    0x1
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_RIF_CLK_GATING_OVERRIDE_SHFT                                      0

#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_ADDR(d)                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X108 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_RMSK                                                            0x1
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_MAXd                                                              3
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_RIF_CLK_GATING_OVERRIDE_BMSK                                    0x1
#define HWIO_APSS_RSC_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_RIF_CLK_GATING_OVERRIDE_SHFT                                      0

#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_ADDR                                                      (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x10c)
#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_RMSK                                                             0x1
#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_SW_RESET_BMSK                                                    0x1
#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_SW_RESET_SHFT                                                      0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR                                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x110)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_RMSK                                                                     0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_EN_BMSK                                                                  0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_EN_SHFT                                                                    0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_ADDR                                                          (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x114)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_RMSK                                                                 0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_IRQ_BMSK                                                             0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_IRQ_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_ADDR                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x118)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_RMSK                                                                    0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_CLR_BMSK                                                                0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_CLR_SHFT                                                                  0

#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x11c)
#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_RMSK                                                         0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_THRESHOLD_BMSK                                               0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_PROFILING_THRESHOLD_DRV0_THRESHOLD_SHFT                                                        0

#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR                                                        (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x200)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_RMSK                                                               0x3
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OWNER_BMSK                                                         0x3
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OWNER_SHFT                                                           0

#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m)                                                     (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X204 + (0x10000*(d)) + (0x20*(m)))
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_RMSK                                                                 0x1
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_MAXd                                                                   3
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_MAXm                                                                   7
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m), HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m), mask)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_OUTI2(d,m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m),val)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_OUTMI2(d,m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m),mask,val,HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_INI2(d,m))
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ENABLE_BMSK                                                          0x1
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ENABLE_SHFT                                                            0

#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_ADDR(d,m)                                            (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X208 + (0x10000*(d)) + (0x20*(m)))
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_RMSK                                                 0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_MAXd                                                          3
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_MAXm                                                          7
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_ADDR(d,m), HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_ADDR(d,m), mask)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_TS_DATA_L_BMSK                                       0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_TS_DATA_L_SHFT                                                0

#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_ADDR(d,m)                                            (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20C + (0x10000*(d)) + (0x20*(m)))
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_RMSK                                                   0xffffff
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_MAXd                                                          3
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_MAXm                                                          7
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_ADDR(d,m), HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_ADDR(d,m), mask)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_TS_DATA_H_BMSK                                         0xffffff
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_TS_DATA_H_SHFT                                                0

#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_ADDR(d,m)                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X210 + (0x10000*(d)) + (0x20*(m)))
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_RMSK                                                           0x101
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_MAXd                                                               3
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_MAXm                                                               7
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_ADDR(d,m), HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_ADDR(d,m), mask)
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_OVERFLOW_BMSK                                               0x100
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_OVERFLOW_SHFT                                                   8
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_VALID_BMSK                                                    0x1
#define HWIO_APSS_RSC_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_VALID_SHFT                                                      0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR                                                     (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x400)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_RMSK                                                     0x800003ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_VALID_BMSK                                               0x80000000
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_VALID_SHFT                                                       31
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR_BMSK                                                     0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR_SHFT                                                         0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_ADDR(d)                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X400 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_RMSK                                                     0x800003ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_MAXd                                                              3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_VALID_BMSK                                               0x80000000
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_VALID_SHFT                                                       31
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_ADDR_BMSK                                                     0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_ADDR_SHFT                                                         0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRV0_ADDR                                                                    (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x404)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRV0_RMSK                                                                           0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRV0_BUSY_STAT_BMSK                                                                 0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRV0_BUSY_STAT_SHFT                                                                   0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRVd_ADDR(d)                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X404 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRVd_RMSK                                                                           0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRVd_MAXd                                                                             3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRVd_BUSY_STAT_BMSK                                                                 0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BUSY_DRVd_BUSY_STAT_SHFT                                                                   0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x408)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_RMSK                                                              0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_CURRENT_INSTR_ADDR_BMSK                                           0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_CURRENT_INSTR_ADDR_SHFT                                               0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_ADDR(d)                                                      (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X408 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_RMSK                                                              0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_MAXd                                                                  3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_CURRENT_INSTR_ADDR_BMSK                                           0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_CURRENT_INSTR_ADDR_SHFT                                               0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_ADDR                                               (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x40c)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_RMSK                                                    0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_CURRENT_INSTR_ADDR_BMSK                                 0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_CURRENT_INSTR_ADDR_SHFT                                     0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_ADDR                                                                    (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x410)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_RMSK                                                                    0x80000001
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_CLEAR_BMSK                                                              0x80000000
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_CLEAR_SHFT                                                                      31
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_COMP_STAT_BMSK                                                                 0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_COMP_DRV0_COMP_STAT_SHFT                                                                   0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i)                                                      (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X450 + (0x4*(i)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_RMSK                                                            0xfffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_MAXi                                                                  3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_INI(i)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i), HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_INMI(i,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_OUTI(i,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i),val)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_OUTMI(i,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i),mask,val,HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_INI(i))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_DELAY_VAL_BMSK                                                  0xfffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_DELAY_VAL_SHFT                                                        0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_ADDR(d,i)                                                    (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X450 + (0x10000*(d)) + (0x4*(i)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_RMSK                                                            0xfffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_MAXd                                                                  3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_MAXi                                                                  3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_INI2(d,i)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_ADDR(d,i), HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_INMI2(d,i,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_ADDR(d,i), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_DELAY_VAL_BMSK                                                  0xfffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_DELAY_VAL_SHFT                                                        0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR                                                        (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x460)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_RMSK                                                               0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_SEQ_OVERRIDE_TRIGGER_BMSK                                          0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_SEQ_OVERRIDE_TRIGGER_SHFT                                            0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_ADDR(d)                                                     (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X460 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_RMSK                                                               0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_MAXd                                                                 3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_SEQ_OVERRIDE_TRIGGER_BMSK                                          0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_SEQ_OVERRIDE_TRIGGER_SHFT                                            0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR                                          (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x464)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_RMSK                                               0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_SEQ_OVERRIDE_TRIGGER_START_ADDR_BMSK               0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_SEQ_OVERRIDE_TRIGGER_START_ADDR_SHFT                   0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_ADDR(d)                                       (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X464 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_RMSK                                               0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_MAXd                                                   3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_SEQ_OVERRIDE_TRIGGER_START_ADDR_BMSK               0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_SEQ_OVERRIDE_TRIGGER_START_ADDR_SHFT                   0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR                                                     (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x490)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_RMSK                                                     0x800003ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_VALID_BMSK                                0x80000000
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_VALID_SHFT                                        31
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_ADDR_BMSK                                      0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_ADDR_SHFT                                          0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR                                                                (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x494)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_RMSK                                                                       0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_DBG_STEP_TRIGGER_BMSK                                                      0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STEP_DRV0_DBG_STEP_TRIGGER_SHFT                                                        0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR                                                            (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x498)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_RMSK                                                                   0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_DBG_STEP_CONTINUE_BMSK                                                 0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_DBG_STEP_CONTINUE_SHFT                                                   0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STAT_DRV0_ADDR                                                                (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x49c)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STAT_DRV0_RMSK                                                                       0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STAT_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STAT_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STAT_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STAT_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STAT_DRV0_DBG_STEPPING_STATUS_BMSK                                                   0x1
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_DBG_STAT_DRV0_DBG_STEPPING_STATUS_SHFT                                                     0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x4a0)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_RMSK                                                       0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_SEQ_OVERRIDE_PWR_CNTRL_MASK_BMSK                           0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_SEQ_OVERRIDE_PWR_CNTRL_MASK_SHFT                              0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_ADDR(d)                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X4A0 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_RMSK                                                       0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_MAXd                                                          3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_SEQ_OVERRIDE_PWR_CNTRL_MASK_BMSK                           0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_SEQ_OVERRIDE_PWR_CNTRL_MASK_SHFT                              0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x4a4)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_RMSK                                                        0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_SEQ_OVERRIDE_PWR_CNTRL_VAL_BMSK                             0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_SEQ_OVERRIDE_PWR_CNTRL_VAL_SHFT                                0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_ADDR(d)                                               (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X4A4 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_RMSK                                                        0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_MAXd                                                           3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_SEQ_OVERRIDE_PWR_CNTRL_VAL_BMSK                             0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_SEQ_OVERRIDE_PWR_CNTRL_VAL_SHFT                                0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR                                                (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x4a8)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_RMSK                                                      0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_SEQ_OVERRIDE_WAIT_EVENT_MASK_BMSK                         0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_SEQ_OVERRIDE_WAIT_EVENT_MASK_SHFT                            0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_ADDR(d)                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X4A8 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_RMSK                                                      0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_MAXd                                                         3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_SEQ_OVERRIDE_WAIT_EVENT_MASK_BMSK                         0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_SEQ_OVERRIDE_WAIT_EVENT_MASK_SHFT                            0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x4ac)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_RMSK                                                       0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_SEQ_OVERRIDE_WAIT_EVENT_VAL_BMSK                           0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_SEQ_OVERRIDE_WAIT_EVENT_VAL_SHFT                              0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_ADDR(d)                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X4AC + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_RMSK                                                       0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_MAXd                                                          3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_SEQ_OVERRIDE_WAIT_EVENT_VAL_BMSK                           0x3f
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_SEQ_OVERRIDE_WAIT_EVENT_VAL_SHFT                              0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x4b0)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_RMSK                                                         0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_PWR_CTRL_STATUS_BMSK                                         0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_PWR_CTRL_STATUS_SHFT                                                  0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_ADDR(d)                                                      (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X4B0 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_RMSK                                                         0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_MAXd                                                                  3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_PWR_CTRL_STATUS_BMSK                                         0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_PWR_CTRL_STATUS_SHFT                                                  0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_ADDR                                                        (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x4b4)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_RMSK                                                        0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_PWR_EVENT_STATUS_BMSK                                       0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_PWR_EVENT_STATUS_SHFT                                                0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_ADDR(d)                                                     (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X4B4 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_RMSK                                                        0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_MAXd                                                                 3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_PWR_EVENT_STATUS_BMSK                                       0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_PWR_EVENT_STATUS_SHFT                                                0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x4b8)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_RMSK                                                         0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_BR_EVENT_STATUS_BMSK                                         0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_BR_EVENT_STATUS_SHFT                                                  0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_ADDR(d)                                                      (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X4B8 + (0x10000*(d)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_RMSK                                                         0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_MAXd                                                                  3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_INI(d)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_ADDR(d), HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_ADDR(d), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_BR_EVENT_STATUS_BMSK                                         0xffffffff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_BR_EVENT_STATUS_SHFT                                                  0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i)                                                        (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X4BC + (0x4*(i)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_RMSK                                                                0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_MAXi                                                                    3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_INI(i)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i), HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_INMI(i,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_OUTI(i,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i),val)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_OUTMI(i,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i),mask,val,HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_INI(i))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR_BMSK                                                           0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_ADDR(d,i)                                                      (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X4BC + (0x10000*(d)) + (0x4*(i)))
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_RMSK                                                                0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_MAXd                                                                    3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_MAXi                                                                    3
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_INI2(d,i)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_ADDR(d,i), HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_INMI2(d,i,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_ADDR(d,i), mask)
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_ADDR_BMSK                                                           0x3ff
#define HWIO_APSS_RSC_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_ADDR_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_ADDR(m)                                                                    (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X550 + (0x4*(m)))
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_RMSK                                                                       0xffffffff
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_MAXm                                                                              127
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_ADDR(m), HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_RMSK)
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_INI(m))
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_CMD_WORD_BMSK                                                              0xffffffff
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRV0_CMD_WORD_SHFT                                                                       0

#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRVd_ADDR(d,m)                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X550 + (0x10000*(d)) + (0x4*(m)))
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRVd_RMSK                                                                       0xffffffff
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRVd_MAXd                                                                                3
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRVd_MAXm                                                                              127
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRVd_ADDR(d,m), HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRVd_RMSK)
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRVd_ADDR(d,m), mask)
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRVd_CMD_WORD_BMSK                                                              0xffffffff
#define HWIO_APSS_RSC_RSCC_SEQ_MEM_m_DRVd_CMD_WORD_SHFT                                                                       0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0xd00)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_RMSK                                                                0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_AMC_COMPLETION_IRQ_ENABLE_BMSK                                      0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_AMC_COMPLETION_IRQ_ENABLE_SHFT                                        0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0xd04)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_RMSK                                                                0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_AMC_COMPLETION_IRQ_STATUS_BMSK                                      0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_AMC_COMPLETION_IRQ_STATUS_SHFT                                        0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_ADDR                                                          (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0xd08)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_RMSK                                                                 0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_AMC_COMPLETION_IRQ_CLEAR_BMSK                                        0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_AMC_COMPLETION_IRQ_CLEAR_SHFT                                          0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0xd10)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_RMSK                                                                         0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_EN_BMSK                                                                      0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV0_EN_SHFT                                                                        0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV0_ADDR                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0xd14)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV0_RMSK                                                                        0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV0_CLR_BMSK                                                                    0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV0_CLR_SHFT                                                                      0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV0_ADDR                                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0xd18)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV0_RMSK                                                                     0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV0_TIMEOUT_BMSK                                                             0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV0_TIMEOUT_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0xd1c)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_RMSK                                                                     0xffff
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR,m,v,HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_IN)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_TIMEOUT_VAL_BMSK                                                         0xffff
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV0_TIMEOUT_VAL_SHFT                                                              0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m)                                                       (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD20 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_RMSK                                                              0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_MAXm                                                                   3
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_BMSK                                            0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_SHFT                                                 0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_ADDR(m)                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD24 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_RMSK                                                                     0x1010000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_MAXm                                                                             3
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_TRIGGER_BMSK                                                    0x1000000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_TRIGGER_SHFT                                                           24
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_EN_BMSK                                                           0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_EN_SHFT                                                                16

#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_STATUS_ADDR(m)                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD28 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_STATUS_RMSK                                                                            0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_STATUS_MAXm                                                                              3
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_STATUS_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV0_STATUS_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV0_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV0_STATUS_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_STATUS_CONTROLLER_IDLE_BMSK                                                            0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_STATUS_CONTROLLER_IDLE_SHFT                                                              0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m)                                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD2C + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_RMSK                                                                     0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_MAXm                                                                          3
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_BMSK                                          0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_SHFT                                               0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_PROFILING_STATUS_ADDR(m)                                                        (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD30 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_PROFILING_STATUS_RMSK                                                                  0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_PROFILING_STATUS_MAXm                                                                    3
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_PROFILING_STATUS_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV0_PROFILING_STATUS_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV0_PROFILING_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_PROFILING_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV0_PROFILING_STATUS_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_PROFILING_STATUS_CONTROLLER_IDLE_BMSK                                                  0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV0_PROFILING_STATUS_CONTROLLER_IDLE_SHFT                                                    0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n)                                                            (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD34 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_RMSK                                                                    0x1010f
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_MAXm                                                                          3
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_MAXn                                                                         15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_READ_OR_WRITE_BMSK                                                      0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_READ_OR_WRITE_SHFT                                                           16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_RES_REQ_BMSK                                                              0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_RES_REQ_SHFT                                                                  8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_MSG_LENGTH_BMSK                                                             0xf
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_MSGID_MSG_LENGTH_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n)                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD38 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_RMSK                                                                     0x7ffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_MAXm                                                                           3
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_MAXn                                                                          15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_SLV_ID_BMSK                                                              0x70000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_SLV_ID_SHFT                                                                   16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_OFFSET_BMSK                                                               0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_ADDR_OFFSET_SHFT                                                                    0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n)                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD3C + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_RMSK                                                                  0xffffffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_MAXm                                                                           3
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_MAXn                                                                          15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_DATA_BMSK                                                             0xffffffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_DATA_DATA_SHFT                                                                      0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_ADDR(m,n)                                                           (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD40 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_RMSK                                                                   0x10101
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_MAXm                                                                         3
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_MAXn                                                                        15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_COMPLETED_BMSK                                                         0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_COMPLETED_SHFT                                                              16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_ISSUED_BMSK                                                              0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_ISSUED_SHFT                                                                  8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_TRIGGERED_BMSK                                                             0x1
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_STATUS_TRIGGERED_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_ADDR(n)                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD44 + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_RMSK                                                    0xffffffff
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_MAXn                                                            15
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_INI(n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_ADDR(n), HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_RMSK)
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_INMI(n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_ADDR(n), mask)
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_READ_RESPONSE_DATA_BMSK                                 0xffffffff
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_READ_RESPONSE_DATA_SHFT                                          0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ADDR(m,n)                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0XD48 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_RMSK                                                         0x10101
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_MAXm                                                               3
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_MAXn                                                              15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_COMPLETED_BMSK                                               0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_COMPLETED_SHFT                                                    16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ISSUED_BMSK                                                    0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ISSUED_SHFT                                                        8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_TRIGGERED_BMSK                                                   0x1
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_TRIGGERED_SHFT                                                     0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x10d00)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_RMSK                                                                0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_ADDR,m,v,HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_IN)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_AMC_COMPLETION_IRQ_ENABLE_BMSK                                      0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_AMC_COMPLETION_IRQ_ENABLE_SHFT                                        0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x10d04)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_RMSK                                                                0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_AMC_COMPLETION_IRQ_STATUS_BMSK                                      0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_AMC_COMPLETION_IRQ_STATUS_SHFT                                        0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_ADDR                                                          (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x10d08)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_RMSK                                                                 0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_AMC_COMPLETION_IRQ_CLEAR_BMSK                                        0xf
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_AMC_COMPLETION_IRQ_CLEAR_SHFT                                          0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_ADDR                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x10d10)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_RMSK                                                                         0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_ADDR,m,v,HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_IN)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_EN_BMSK                                                                      0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV1_EN_SHFT                                                                        0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV1_ADDR                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x10d14)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV1_RMSK                                                                        0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV1_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV1_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV1_CLR_BMSK                                                                    0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV1_CLR_SHFT                                                                      0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV1_ADDR                                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x10d18)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV1_RMSK                                                                     0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV1_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV1_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV1_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV1_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV1_TIMEOUT_BMSK                                                             0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV1_TIMEOUT_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV1_ADDR                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x10d1c)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV1_RMSK                                                                     0xffff
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV1_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV1_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV1_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV1_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV1_TIMEOUT_VAL_BMSK                                                         0xffff
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV1_TIMEOUT_VAL_SHFT                                                              0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_ADDR(m)                                                       (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10D20 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_RMSK                                                              0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_MAXm                                                                   3
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_BMSK                                            0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_SHFT                                                 0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_ADDR(m)                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10D24 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_RMSK                                                                     0x1010000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_MAXm                                                                             3
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_AMC_MODE_TRIGGER_BMSK                                                    0x1000000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_AMC_MODE_TRIGGER_SHFT                                                           24
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_AMC_MODE_EN_BMSK                                                           0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CONTROL_AMC_MODE_EN_SHFT                                                                16

#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_STATUS_ADDR(m)                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10D28 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_STATUS_RMSK                                                                            0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_STATUS_MAXm                                                                              3
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_STATUS_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV1_STATUS_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV1_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV1_STATUS_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_STATUS_CONTROLLER_IDLE_BMSK                                                            0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_STATUS_CONTROLLER_IDLE_SHFT                                                              0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_ADDR(m)                                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10D2C + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_RMSK                                                                     0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_MAXm                                                                          3
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_BMSK                                          0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_SHFT                                               0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_PROFILING_STATUS_ADDR(m)                                                        (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10D30 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_PROFILING_STATUS_RMSK                                                                  0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_PROFILING_STATUS_MAXm                                                                    3
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_PROFILING_STATUS_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV1_PROFILING_STATUS_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV1_PROFILING_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_PROFILING_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV1_PROFILING_STATUS_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_PROFILING_STATUS_CONTROLLER_IDLE_BMSK                                                  0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV1_PROFILING_STATUS_CONTROLLER_IDLE_SHFT                                                    0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_ADDR(m,n)                                                            (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10D34 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_RMSK                                                                    0x1010f
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_MAXm                                                                          3
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_MAXn                                                                         15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_READ_OR_WRITE_BMSK                                                      0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_READ_OR_WRITE_SHFT                                                           16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_RES_REQ_BMSK                                                              0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_RES_REQ_SHFT                                                                  8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_MSG_LENGTH_BMSK                                                             0xf
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_MSGID_MSG_LENGTH_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_ADDR(m,n)                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10D38 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_RMSK                                                                     0x7ffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_MAXm                                                                           3
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_MAXn                                                                          15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_SLV_ID_BMSK                                                              0x70000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_SLV_ID_SHFT                                                                   16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_OFFSET_BMSK                                                               0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_ADDR_OFFSET_SHFT                                                                    0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_ADDR(m,n)                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10D3C + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_RMSK                                                                  0xffffffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_MAXm                                                                           3
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_MAXn                                                                          15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_DATA_BMSK                                                             0xffffffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_DATA_DATA_SHFT                                                                      0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_ADDR(m,n)                                                           (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10D40 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_RMSK                                                                   0x10101
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_MAXm                                                                         3
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_MAXn                                                                        15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_COMPLETED_BMSK                                                         0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_COMPLETED_SHFT                                                              16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_ISSUED_BMSK                                                              0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_ISSUED_SHFT                                                                  8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_TRIGGERED_BMSK                                                             0x1
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_STATUS_TRIGGERED_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_ADDR(n)                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10D44 + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_RMSK                                                    0xffffffff
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_MAXn                                                            15
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_INI(n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_ADDR(n), HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_RMSK)
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_INMI(n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_ADDR(n), mask)
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_READ_RESPONSE_DATA_BMSK                                 0xffffffff
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_READ_RESPONSE_DATA_SHFT                                          0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ADDR(m,n)                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X10D48 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_RMSK                                                         0x10101
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_MAXm                                                               3
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_MAXn                                                              15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_COMPLETED_BMSK                                               0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_COMPLETED_SHFT                                                    16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ISSUED_BMSK                                                    0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ISSUED_SHFT                                                        8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_TRIGGERED_BMSK                                                   0x1
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_TRIGGERED_SHFT                                                     0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x20d00)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_RMSK                                                               0xff
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_ADDR,m,v,HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_IN)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_AMC_COMPLETION_IRQ_ENABLE_BMSK                                     0xff
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_AMC_COMPLETION_IRQ_ENABLE_SHFT                                        0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x20d04)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_RMSK                                                               0xff
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_AMC_COMPLETION_IRQ_STATUS_BMSK                                     0xff
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_AMC_COMPLETION_IRQ_STATUS_SHFT                                        0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_ADDR                                                          (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x20d08)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_RMSK                                                                0xff
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_AMC_COMPLETION_IRQ_CLEAR_BMSK                                       0xff
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_AMC_COMPLETION_IRQ_CLEAR_SHFT                                          0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_ADDR                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x20d10)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_RMSK                                                                         0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_ADDR,m,v,HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_IN)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_EN_BMSK                                                                      0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV2_EN_SHFT                                                                        0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV2_ADDR                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x20d14)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV2_RMSK                                                                        0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV2_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV2_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV2_CLR_BMSK                                                                    0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV2_CLR_SHFT                                                                      0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV2_ADDR                                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x20d18)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV2_RMSK                                                                     0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV2_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV2_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV2_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV2_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV2_TIMEOUT_BMSK                                                             0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV2_TIMEOUT_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV2_ADDR                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x20d1c)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV2_RMSK                                                                     0xffff
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV2_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV2_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV2_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV2_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV2_TIMEOUT_VAL_BMSK                                                         0xffff
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV2_TIMEOUT_VAL_SHFT                                                              0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_ADDR(m)                                                       (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20D20 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_RMSK                                                              0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_MAXm                                                                   7
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_BMSK                                            0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_SHFT                                                 0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_ADDR(m)                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20D24 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_RMSK                                                                     0x1010000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_MAXm                                                                             7
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_AMC_MODE_TRIGGER_BMSK                                                    0x1000000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_AMC_MODE_TRIGGER_SHFT                                                           24
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_AMC_MODE_EN_BMSK                                                           0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CONTROL_AMC_MODE_EN_SHFT                                                                16

#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_STATUS_ADDR(m)                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20D28 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_STATUS_RMSK                                                                            0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_STATUS_MAXm                                                                              7
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_STATUS_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV2_STATUS_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV2_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV2_STATUS_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_STATUS_CONTROLLER_IDLE_BMSK                                                            0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_STATUS_CONTROLLER_IDLE_SHFT                                                              0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_ADDR(m)                                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20D2C + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_RMSK                                                                     0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_MAXm                                                                          7
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_BMSK                                          0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_SHFT                                               0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_PROFILING_STATUS_ADDR(m)                                                        (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20D30 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_PROFILING_STATUS_RMSK                                                                  0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_PROFILING_STATUS_MAXm                                                                    7
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_PROFILING_STATUS_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV2_PROFILING_STATUS_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV2_PROFILING_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_PROFILING_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV2_PROFILING_STATUS_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_PROFILING_STATUS_CONTROLLER_IDLE_BMSK                                                  0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV2_PROFILING_STATUS_CONTROLLER_IDLE_SHFT                                                    0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_ADDR(m,n)                                                            (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20D34 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_RMSK                                                                    0x1010f
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_MAXm                                                                          7
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_MAXn                                                                         15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_READ_OR_WRITE_BMSK                                                      0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_READ_OR_WRITE_SHFT                                                           16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_RES_REQ_BMSK                                                              0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_RES_REQ_SHFT                                                                  8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_MSG_LENGTH_BMSK                                                             0xf
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID_MSG_LENGTH_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_ADDR(m,n)                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20D38 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_RMSK                                                                     0x7ffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_MAXm                                                                           7
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_MAXn                                                                          15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_SLV_ID_BMSK                                                              0x70000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_SLV_ID_SHFT                                                                   16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_OFFSET_BMSK                                                               0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR_OFFSET_SHFT                                                                    0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_ADDR(m,n)                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20D3C + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_RMSK                                                                  0xffffffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_MAXm                                                                           7
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_MAXn                                                                          15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_DATA_BMSK                                                             0xffffffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA_DATA_SHFT                                                                      0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_ADDR(m,n)                                                           (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20D40 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_RMSK                                                                   0x10101
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_MAXm                                                                         7
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_MAXn                                                                        15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_COMPLETED_BMSK                                                         0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_COMPLETED_SHFT                                                              16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_ISSUED_BMSK                                                              0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_ISSUED_SHFT                                                                  8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_TRIGGERED_BMSK                                                             0x1
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_STATUS_TRIGGERED_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_ADDR(n)                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20D44 + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_RMSK                                                    0xffffffff
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_MAXn                                                            15
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_INI(n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_ADDR(n), HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_RMSK)
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_INMI(n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_ADDR(n), mask)
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_READ_RESPONSE_DATA_BMSK                                 0xffffffff
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_READ_RESPONSE_DATA_SHFT                                          0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ADDR(m,n)                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X20D48 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_RMSK                                                         0x10101
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_MAXm                                                               7
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_MAXn                                                              15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_COMPLETED_BMSK                                               0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_COMPLETED_SHFT                                                    16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ISSUED_BMSK                                                    0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ISSUED_SHFT                                                        8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_TRIGGERED_BMSK                                                   0x1
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_TRIGGERED_SHFT                                                     0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x30d00)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_RMSK                                                                0x7
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_ADDR,m,v,HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_IN)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_AMC_COMPLETION_IRQ_ENABLE_BMSK                                      0x7
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV3_AMC_COMPLETION_IRQ_ENABLE_SHFT                                        0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV3_ADDR                                                         (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x30d04)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV3_RMSK                                                                0x7
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV3_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV3_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV3_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV3_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV3_AMC_COMPLETION_IRQ_STATUS_BMSK                                      0x7
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV3_AMC_COMPLETION_IRQ_STATUS_SHFT                                        0

#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV3_ADDR                                                          (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x30d08)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV3_RMSK                                                                 0x7
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV3_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV3_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV3_AMC_COMPLETION_IRQ_CLEAR_BMSK                                        0x7
#define HWIO_APSS_RSC_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV3_AMC_COMPLETION_IRQ_CLEAR_SHFT                                          0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_ADDR                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x30d10)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_RMSK                                                                         0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_ADDR,m,v,HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_IN)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_EN_BMSK                                                                      0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_EN_DRV3_EN_SHFT                                                                        0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV3_ADDR                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x30d14)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV3_RMSK                                                                        0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV3_OUT(v)            \
                out_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV3_ADDR,v)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV3_CLR_BMSK                                                                    0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_CLR_DRV3_CLR_SHFT                                                                      0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV3_ADDR                                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x30d18)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV3_RMSK                                                                     0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV3_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV3_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV3_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV3_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV3_TIMEOUT_BMSK                                                             0x1
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_STATUS_DRV3_TIMEOUT_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV3_ADDR                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0x30d1c)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV3_RMSK                                                                     0xffff
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV3_IN                    \
                in_dword(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV3_ADDR)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV3_INM(m)            \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV3_ADDR, m)
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV3_TIMEOUT_VAL_BMSK                                                         0xffff
#define HWIO_APSS_RSC_RSCC_TCS_TIMEOUT_VAL_DRV3_TIMEOUT_VAL_SHFT                                                              0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_ADDR(m)                                                       (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30D20 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_RMSK                                                              0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_MAXm                                                                   2
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_BMSK                                            0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_SHFT                                                 0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_ADDR(m)                                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30D24 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_RMSK                                                                     0x1010000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_MAXm                                                                             2
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_AMC_MODE_TRIGGER_BMSK                                                    0x1000000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_AMC_MODE_TRIGGER_SHFT                                                           24
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_AMC_MODE_EN_BMSK                                                           0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CONTROL_AMC_MODE_EN_SHFT                                                                16

#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_STATUS_ADDR(m)                                                                  (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30D28 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_STATUS_RMSK                                                                            0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_STATUS_MAXm                                                                              2
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_STATUS_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV3_STATUS_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV3_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV3_STATUS_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_STATUS_CONTROLLER_IDLE_BMSK                                                            0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_STATUS_CONTROLLER_IDLE_SHFT                                                              0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_ADDR(m)                                                              (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30D2C + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_RMSK                                                                     0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_MAXm                                                                          2
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_OUTI(m,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_ADDR(m),val)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_ADDR(m),mask,val,HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_INI(m))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_BMSK                                          0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_SHFT                                               0

#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_PROFILING_STATUS_ADDR(m)                                                        (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30D30 + (0x2A0*(m)))
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_PROFILING_STATUS_RMSK                                                                  0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_PROFILING_STATUS_MAXm                                                                    2
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_PROFILING_STATUS_INI(m)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV3_PROFILING_STATUS_ADDR(m), HWIO_APSS_RSC_RSCC_TCSm_DRV3_PROFILING_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_PROFILING_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_DRV3_PROFILING_STATUS_ADDR(m), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_PROFILING_STATUS_CONTROLLER_IDLE_BMSK                                                  0x1
#define HWIO_APSS_RSC_RSCC_TCSm_DRV3_PROFILING_STATUS_CONTROLLER_IDLE_SHFT                                                    0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_ADDR(m,n)                                                            (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30D34 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_RMSK                                                                    0x1010f
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_MAXm                                                                          2
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_MAXn                                                                         15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_READ_OR_WRITE_BMSK                                                      0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_READ_OR_WRITE_SHFT                                                           16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_RES_REQ_BMSK                                                              0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_RES_REQ_SHFT                                                                  8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_MSG_LENGTH_BMSK                                                             0xf
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_MSGID_MSG_LENGTH_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_ADDR(m,n)                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30D38 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_RMSK                                                                     0x7ffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_MAXm                                                                           2
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_MAXn                                                                          15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_SLV_ID_BMSK                                                              0x70000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_SLV_ID_SHFT                                                                   16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_OFFSET_BMSK                                                               0xffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_ADDR_OFFSET_SHFT                                                                    0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_ADDR(m,n)                                                             (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30D3C + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_RMSK                                                                  0xffffffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_MAXm                                                                           2
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_MAXn                                                                          15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_OUTI2(m,n,val)        \
                out_dword(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_ADDR(m,n),val)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_ADDR(m,n),mask,val,HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_INI2(m,n))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_DATA_BMSK                                                             0xffffffff
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_DATA_DATA_SHFT                                                                      0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_ADDR(m,n)                                                           (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30D40 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_RMSK                                                                   0x10101
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_MAXm                                                                         2
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_MAXn                                                                        15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_COMPLETED_BMSK                                                         0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_COMPLETED_SHFT                                                              16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_ISSUED_BMSK                                                              0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_ISSUED_SHFT                                                                  8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_TRIGGERED_BMSK                                                             0x1
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_STATUS_TRIGGERED_SHFT                                                               0

#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV3_READ_RESPONSE_DATA_ADDR(n)                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30D44 + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV3_READ_RESPONSE_DATA_RMSK                                                    0xffffffff
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV3_READ_RESPONSE_DATA_MAXn                                                            15
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV3_READ_RESPONSE_DATA_INI(n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV3_READ_RESPONSE_DATA_ADDR(n), HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV3_READ_RESPONSE_DATA_RMSK)
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV3_READ_RESPONSE_DATA_INMI(n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV3_READ_RESPONSE_DATA_ADDR(n), mask)
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV3_READ_RESPONSE_DATA_READ_RESPONSE_DATA_BMSK                                 0xffffffff
#define HWIO_APSS_RSC_RSCC_TCS0_CMDn_DRV3_READ_RESPONSE_DATA_READ_RESPONSE_DATA_SHFT                                          0

#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_ADDR(m,n)                                                 (APSS_RSC_RSCC_RSCC_RSC_REG_BASE      + 0X30D48 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_RMSK                                                         0x10101
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_MAXm                                                               2
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_MAXn                                                              15
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_ADDR(m,n), HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_RMSK)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_ADDR(m,n), mask)
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_COMPLETED_BMSK                                               0x10000
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_COMPLETED_SHFT                                                    16
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_ISSUED_BMSK                                                    0x100
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_ISSUED_SHFT                                                        8
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_TRIGGERED_BMSK                                                   0x1
#define HWIO_APSS_RSC_RSCC_TCSm_CMDn_DRV3_PROFILING_STATUS_TRIGGERED_SHFT                                                     0


#endif /* __RSC_HWIO_H__ */
