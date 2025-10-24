#ifndef __ARC_RM_HWIO_H__
#define __ARC_RM_HWIO_H__
/*
===========================================================================
*/
/**
  @file arc_rm_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    RPMH_ARC_ARC_RM


  Generation parameters: 
  { u'filename': u'arc_rm_hwio.h',
    u'module-filter-exclude': { },
    u'module-filter-include': { },
    u'modules': ['RPMH_ARC_ARC_RM']}
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

  $Header: //components/rel/aop.ho/5.0/aop_proc/core/api/power/kailua/arc_rm_hwio.h#1 $
  $DateTime: 2021/10/26 22:03:12 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: RPMH_ARC_ARC_RM
 *--------------------------------------------------------------------------*/

#define RPMH_ARC_ARC_RM_REG_BASE                                                                 (AOSS_BASE      + 0x007f0000)
#define RPMH_ARC_ARC_RM_REG_BASE_SIZE                                                            0xb000
#define RPMH_ARC_ARC_RM_REG_BASE_USED                                                            0x7074

#define HWIO_RPMH_ARC_RMm_CTRL_ADDR(m)                                                           (RPMH_ARC_ARC_RM_REG_BASE      + 0x00000000 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_CTRL_RMSK                                                                 0xf0f01
#define HWIO_RPMH_ARC_RMm_CTRL_MAXm                                                                      12
#define HWIO_RPMH_ARC_RMm_CTRL_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_CTRL_ADDR(m), HWIO_RPMH_ARC_RMm_CTRL_RMSK)
#define HWIO_RPMH_ARC_RMm_CTRL_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_CTRL_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_CTRL_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_CTRL_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_CTRL_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_CTRL_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_CTRL_INI(m))
#define HWIO_RPMH_ARC_RMm_CTRL_MOL_BMSK                                                             0xf0000
#define HWIO_RPMH_ARC_RMm_CTRL_MOL_SHFT                                                                0x10
#define HWIO_RPMH_ARC_RMm_CTRL_RET_OL_BMSK                                                            0xf00
#define HWIO_RPMH_ARC_RMm_CTRL_RET_OL_SHFT                                                              0x8
#define HWIO_RPMH_ARC_RMm_CTRL_RM_EN_BMSK                                                               0x1
#define HWIO_RPMH_ARC_RMm_CTRL_RM_EN_SHFT                                                               0x0

#define HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_ADDR(m)                                                  (RPMH_ARC_ARC_RM_REG_BASE      + 0x00000040 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_RMSK                                                            0x1
#define HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_MAXm                                                             12
#define HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_ADDR(m), HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_RMSK)
#define HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_INI(m))
#define HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_AGGR_BLOCK_EN_BMSK                                              0x1
#define HWIO_RPMH_ARC_RMm_AGGR_BLOCK_EN_AGGR_BLOCK_EN_SHFT                                              0x0

#define HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_ADDR(m)                                                   (RPMH_ARC_ARC_RM_REG_BASE      + 0x00000080 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_RMSK                                                             0xf
#define HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_MAXm                                                              12
#define HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_ADDR(m), HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_RMSK)
#define HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_INI(m))
#define HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_RM_AGGR_UNBLOCK_DATA_BMSK                                        0xf
#define HWIO_RPMH_ARC_RMm_AGGR_UNBLOCK_RM_AGGR_UNBLOCK_DATA_SHFT                                        0x0

#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_ADDR(m)                                              (RPMH_ARC_ARC_RM_REG_BASE      + 0x000000c0 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_RMSK                                                 0xfffff000
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_MAXm                                                         12
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_ADDR(m), HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_RMSK)
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_INI(m))
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_DESTINATION_OL_BMSK                                  0xf0000000
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_DESTINATION_OL_SHFT                                        0x1c
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_SEQUENCE_OL_BMSK                                      0xf000000
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_SEQUENCE_OL_SHFT                                           0x18
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_AGGREGATED_OL_BMSK                                     0xf00000
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_AGGREGATED_OL_SHFT                                         0x14
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_SOLVED_OL_BMSK                                          0xf0000
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_SOLVED_OL_SHFT                                             0x10
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_CURRENT_OL_BMSK                                          0xf000
#define HWIO_RPMH_ARC_RMm_OPERATIONAL_LEVEL_CURRENT_OL_SHFT                                             0xc

#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_LOW_ADDR(m)                                      (RPMH_ARC_ARC_RM_REG_BASE      + 0x00000100 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_LOW_RMSK                                         0xffffffff
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_LOW_MAXm                                                 12
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_LOW_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_LOW_ADDR(m), HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_LOW_RMSK)
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_LOW_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_LOW_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_LOW_MIN_IDLE_TIME_LOW_BMSK                       0xffffffff
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_LOW_MIN_IDLE_TIME_LOW_SHFT                              0x0

#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_HIGH_ADDR(m)                                     (RPMH_ARC_ARC_RM_REG_BASE      + 0x00000140 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_HIGH_RMSK                                          0xffffff
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_HIGH_MAXm                                                12
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_HIGH_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_HIGH_ADDR(m), HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_HIGH_RMSK)
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_HIGH_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_HIGH_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_HIGH_MIN_IDLE_TIME_HIGH_BMSK                       0xffffff
#define HWIO_RPMH_ARC_RMm_MIN_IDLE_TIME_SOLVING_HIGH_MIN_IDLE_TIME_HIGH_SHFT                            0x0

#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_LOW_ADDR(m)                                        (RPMH_ARC_ARC_RM_REG_BASE      + 0x00000180 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_LOW_RMSK                                           0xffffffff
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_LOW_MAXm                                                   12
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_LOW_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_LOW_ADDR(m), HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_LOW_RMSK)
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_LOW_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_LOW_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_LOW_WAKEUP_TIMER_VALUE_LOW_BMSK                    0xffffffff
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_LOW_WAKEUP_TIMER_VALUE_LOW_SHFT                           0x0

#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_ADDR(m)                                       (RPMH_ARC_ARC_RM_REG_BASE      + 0x000001c0 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_RMSK                                          0xe0ffffff
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_MAXm                                                  12
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_ADDR(m), HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_RMSK)
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_WAKEUP_TIMER_ENABLE_BMSK                      0x80000000
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_WAKEUP_TIMER_ENABLE_SHFT                            0x1f
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_WAKEUP_TIMER_EXPIRE_BMSK                      0x40000000
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_WAKEUP_TIMER_EXPIRE_SHFT                            0x1e
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_WAKEUP_TIMER_CONSIDERED_BMSK                  0x20000000
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_WAKEUP_TIMER_CONSIDERED_SHFT                        0x1d
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_WAKEUP_TIMER_VALUE_HIGH_BMSK                    0xffffff
#define HWIO_RPMH_ARC_RMm_WAKEUP_TIMER_STATUS_HIGH_WAKEUP_TIMER_VALUE_HIGH_SHFT                         0x0

#define HWIO_RPMH_ARC_RMm_SEQ_UP_BR_EVENT_ADDR(m)                                                (RPMH_ARC_ARC_RM_REG_BASE      + 0x00002240 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_SEQ_UP_BR_EVENT_RMSK                                                       0xffff
#define HWIO_RPMH_ARC_RMm_SEQ_UP_BR_EVENT_MAXm                                                           12
#define HWIO_RPMH_ARC_RMm_SEQ_UP_BR_EVENT_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQ_UP_BR_EVENT_ADDR(m), HWIO_RPMH_ARC_RMm_SEQ_UP_BR_EVENT_RMSK)
#define HWIO_RPMH_ARC_RMm_SEQ_UP_BR_EVENT_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQ_UP_BR_EVENT_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_SEQ_UP_BR_EVENT_HW_UP_BR_EVENT_BMSK                                        0xffff
#define HWIO_RPMH_ARC_RMm_SEQ_UP_BR_EVENT_HW_UP_BR_EVENT_SHFT                                           0x0

#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_BR_EVENT_ADDR(m)                                              (RPMH_ARC_ARC_RM_REG_BASE      + 0x000022c0 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_BR_EVENT_RMSK                                                     0xffff
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_BR_EVENT_MAXm                                                         12
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_BR_EVENT_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQ_DOWN_BR_EVENT_ADDR(m), HWIO_RPMH_ARC_RMm_SEQ_DOWN_BR_EVENT_RMSK)
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_BR_EVENT_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQ_DOWN_BR_EVENT_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_BR_EVENT_HW_DOWN_BR_EVENT_BMSK                                    0xffff
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_BR_EVENT_HW_DOWN_BR_EVENT_SHFT                                       0x0

#define HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_ADDR(m)                                              (RPMH_ARC_ARC_RM_REG_BASE      + 0x00002340 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_RMSK                                                     0xffff
#define HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_MAXm                                                         12
#define HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_ADDR(m), HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_RMSK)
#define HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_INI(m))
#define HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_SW_CONF_EVENT_BMSK                                       0xffff
#define HWIO_RPMH_ARC_RMm_SEQ_SW_CONF_EVENT_SW_CONF_EVENT_SHFT                                          0x0

#define HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_ADDR(m)                                              (RPMH_ARC_ARC_RM_REG_BASE      + 0x00002440 + 0x40 * (m))
#define HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_RMSK                                                      0xfff
#define HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_MAXm                                                         12
#define HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_ADDR(m), HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_RMSK)
#define HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_INI(m))
#define HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_UP_START_ADDR_BMSK                                        0xfff
#define HWIO_RPMH_ARC_RMm_SEQ_UP_START_ADDR_UP_START_ADDR_SHFT                                          0x0

#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_ADDR(m)                                            (RPMH_ARC_ARC_RM_REG_BASE      + 0x00002900 + 0x40 * (m))
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_RMSK                                                    0xfff
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_MAXm                                                       12
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_ADDR(m), HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_RMSK)
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_INI(m))
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_DOWN_START_ADDR_BMSK                                    0xfff
#define HWIO_RPMH_ARC_RMm_SEQ_DOWN_START_ADDR_DOWN_START_ADDR_SHFT                                      0x0

#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_ADDR(m,i)                                           (RPMH_ARC_ARC_RM_REG_BASE      + 0x00003a00 + 0x40 * (m) + 0x4 * (i))
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_RMSK                                                   0xfffff
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_MAXm                                                        12
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_MAXi                                                         5
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_INI2(m,i)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_ADDR(m,i), HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_RMSK)
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_INMI2(m,i,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_ADDR(m,i), mask)
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_OUTI2(m,i,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_ADDR(m,i),val)
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_OUTMI2(m,i,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_ADDR(m,i),mask,val,HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_INI2(m,i))
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_SOLVER_TABLE_SOLVER_MODE_BMSK                          0xf0000
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_SOLVER_TABLE_SOLVER_MODE_SHFT                             0x10
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_SOLVER_TABLE_BACKOFF_TIME_BMSK                          0xffff
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MODEi_SOLVER_TABLE_BACKOFF_TIME_SHFT                             0x0

#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_ADDR(m,i)                                 (RPMH_ARC_ARC_RM_REG_BASE      + 0x00004100 + 0x40 * (m) + 0x4 * (i))
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_RMSK                                      0xffffffff
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_MAXm                                              12
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_MAXi                                               5
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_INI2(m,i)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_ADDR(m,i), HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_RMSK)
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_INMI2(m,i,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_ADDR(m,i), mask)
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_OUTI2(m,i,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_ADDR(m,i),val)
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_OUTMI2(m,i,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_ADDR(m,i),mask,val,HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_INI2(m,i))
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_SOLVER_TABLE_MIN_SLEEP_TIME_BMSK          0xffffffff
#define HWIO_RPMH_ARC_RMm_SOLVER_TABLE_MIN_SLEEP_TIMEi_SOLVER_TABLE_MIN_SLEEP_TIME_SHFT                 0x0

#define HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_ADDR(m)                                           (RPMH_ARC_ARC_RM_REG_BASE      + 0x00004500 + 0x40 * (m))
#define HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_RMSK                                              0x80000fff
#define HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_MAXm                                                      12
#define HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_ADDR(m), HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_RMSK)
#define HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_SEQUENCER_BUSY_BMSK                               0x80000000
#define HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_SEQUENCER_BUSY_SHFT                                     0x1f
#define HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_SEQUENCER_PC_BMSK                                      0xfff
#define HWIO_RPMH_ARC_RMm_SEQUENCER_STATUS_CSR_SEQUENCER_PC_SHFT                                        0x0

#define HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_ADDR(m)                                        (RPMH_ARC_ARC_RM_REG_BASE      + 0x00005000 + 0x40 * (m))
#define HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_RMSK                                               0xffff
#define HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_MAXm                                                   12
#define HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_ADDR(m), HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_RMSK)
#define HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_INI(m))
#define HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_ALLOWED_THERMAL_OL_MASK_BMSK                       0xffff
#define HWIO_RPMH_ARC_RMm_ALLOWED_THERMAL_OL_MASK_ALLOWED_THERMAL_OL_MASK_SHFT                          0x0

#define HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_ADDR(m)                                         (RPMH_ARC_ARC_RM_REG_BASE      + 0x00005004 + 0x40 * (m))
#define HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_RMSK                                                0xffff
#define HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_MAXm                                                    12
#define HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_ADDR(m), HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_RMSK)
#define HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_INI(m))
#define HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_ALLOWED_NORMAL_OL_MASK_BMSK                         0xffff
#define HWIO_RPMH_ARC_RMm_ALLOWED_NORMAL_OL_MASK_ALLOWED_NORMAL_OL_MASK_SHFT                            0x0

#define HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_ADDR(m)                                                (RPMH_ARC_ARC_RM_REG_BASE      + 0x00005008 + 0x40 * (m))
#define HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_RMSK                                                          0x1
#define HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_MAXm                                                           12
#define HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_ADDR(m), HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_RMSK)
#define HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_INI(m))
#define HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_ALLOWED_OL_MODE_BMSK                                          0x1
#define HWIO_RPMH_ARC_RMm_ALLOWED_OL_MODE_ALLOWED_OL_MODE_SHFT                                          0x0

#define HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_ADDR(m)                                               (RPMH_ARC_ARC_RM_REG_BASE      + 0x0000500c + 0x40 * (m))
#define HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_RMSK                                                         0x1
#define HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_MAXm                                                          12
#define HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_ADDR(m), HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_RMSK)
#define HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_INI(m))
#define HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_THERMAL_MODE_SEL_BMSK                                        0x1
#define HWIO_RPMH_ARC_RMm_THERMAL_MODE_SEL_THERMAL_MODE_SEL_SHFT                                        0x0

#define HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_ADDR(m)                                        (RPMH_ARC_ARC_RM_REG_BASE      + 0x00005010 + 0x40 * (m))
#define HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_RMSK                                               0xffff
#define HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_MAXm                                                   12
#define HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_ADDR(m), HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_RMSK)
#define HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_INI(m))
#define HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_ADDITIONAL_BACKOFF_TIME_BMSK                       0xffff
#define HWIO_RPMH_ARC_RMm_ADDITIONAL_BACKOFF_TIME_ADDITIONAL_BACKOFF_TIME_SHFT                          0x0

#define HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_ADDR(m)                                             (RPMH_ARC_ARC_RM_REG_BASE      + 0x00005014 + 0x40 * (m))
#define HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_RMSK                                                    0xffff
#define HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_MAXm                                                        12
#define HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_ADDR(m), HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_RMSK)
#define HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_INI(m))
#define HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_VCOMP_HIGH_OL_MASK_BMSK                                 0xffff
#define HWIO_RPMH_ARC_RMm_VCOMP_HIGH_OL_MASK_VCOMP_HIGH_OL_MASK_SHFT                                    0x0

#define HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_ADDR(m)                                              (RPMH_ARC_ARC_RM_REG_BASE      + 0x00005018 + 0x40 * (m))
#define HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_RMSK                                                     0xffff
#define HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_MAXm                                                         12
#define HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_ADDR(m), HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_RMSK)
#define HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_INI(m))
#define HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_VCOMP_LOW_OL_MASK_BMSK                                   0xffff
#define HWIO_RPMH_ARC_RMm_VCOMP_LOW_OL_MASK_VCOMP_LOW_OL_MASK_SHFT                                      0x0

#define HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_ADDR(m)                                                   (RPMH_ARC_ARC_RM_REG_BASE      + 0x00006000 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_RMSK                                                             0xf
#define HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_MAXm                                                              12
#define HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_ADDR(m), HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_RMSK)
#define HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_INI(m))
#define HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_RAIL_MUX_SEL_BMSK                                                0xf
#define HWIO_RPMH_ARC_RMm_RAIL_MUX_SEL_RAIL_MUX_SEL_SHFT                                                0x0

#define HWIO_RPMH_ARC_RMm_MODEc_TH_ADDR(m,c)                                                     (RPMH_ARC_ARC_RM_REG_BASE      + 0x00006100 + 0x20 * (m) + 0x4 * (c))
#define HWIO_RPMH_ARC_RMm_MODEc_TH_RMSK                                                                 0xf
#define HWIO_RPMH_ARC_RMm_MODEc_TH_MAXm                                                                  12
#define HWIO_RPMH_ARC_RMm_MODEc_TH_MAXc                                                                   3
#define HWIO_RPMH_ARC_RMm_MODEc_TH_INI2(m,c)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_MODEc_TH_ADDR(m,c), HWIO_RPMH_ARC_RMm_MODEc_TH_RMSK)
#define HWIO_RPMH_ARC_RMm_MODEc_TH_INMI2(m,c,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_MODEc_TH_ADDR(m,c), mask)
#define HWIO_RPMH_ARC_RMm_MODEc_TH_OUTI2(m,c,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_MODEc_TH_ADDR(m,c),val)
#define HWIO_RPMH_ARC_RMm_MODEc_TH_OUTMI2(m,c,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_MODEc_TH_ADDR(m,c),mask,val,HWIO_RPMH_ARC_RMm_MODEc_TH_INI2(m,c))
#define HWIO_RPMH_ARC_RMm_MODEc_TH_OL_THRESHOLD_BMSK                                                    0xf
#define HWIO_RPMH_ARC_RMm_MODEc_TH_OL_THRESHOLD_SHFT                                                    0x0

#define HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_ADDR(m)                                                  (RPMH_ARC_ARC_RM_REG_BASE      + 0x00007000 + 0x4 * (m))
#define HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_RMSK                                                         0xffff
#define HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_MAXm                                                             12
#define HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_ADDR(m), HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_RMSK)
#define HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_ADDR(m), mask)
#define HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_ADDR(m),val)
#define HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_ADDR(m),mask,val,HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_INI(m))
#define HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_CPRF_DEP_MASK_BMSK                                           0xffff
#define HWIO_RPMH_ARC_RMm_CPRF_DEP_MASK_CPRF_DEP_MASK_SHFT                                              0x0

#define HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_ADDR(m)                                          (RPMH_ARC_ARC_RM_REG_BASE      + 0x00007040 + 0x4 * (m))
#define HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_RMSK                                                 0xffff
#define HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_MAXm                                                      1
#define HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_INI(m)        \
        in_dword_masked(HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_ADDR(m), HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_RMSK)
#define HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_INMI(m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_ADDR(m), mask)
#define HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_OUTI(m,val)    \
        out_dword(HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_ADDR(m),val)
#define HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_ADDR(m),mask,val,HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_INI(m))
#define HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_CPRF_DEP_MASK_BMSK                                   0xffff
#define HWIO_RPMH_ARC_EXT_NON_OPm_CPRF_DEP_MASK_CPRF_DEP_MASK_SHFT                                      0x0

#define HWIO_RPMH_ARC_RM_NON_OP_REQ_STATUS_ADDR                                                  (RPMH_ARC_ARC_RM_REG_BASE      + 0x00007060)
#define HWIO_RPMH_ARC_RM_NON_OP_REQ_STATUS_RMSK                                                      0x1fff
#define HWIO_RPMH_ARC_RM_NON_OP_REQ_STATUS_IN          \
        in_dword(HWIO_RPMH_ARC_RM_NON_OP_REQ_STATUS_ADDR)
#define HWIO_RPMH_ARC_RM_NON_OP_REQ_STATUS_INM(m)      \
        in_dword_masked(HWIO_RPMH_ARC_RM_NON_OP_REQ_STATUS_ADDR, m)
#define HWIO_RPMH_ARC_RM_NON_OP_REQ_STATUS_RM_NON_OP_REQ_STATUS_BMSK                                 0x1fff
#define HWIO_RPMH_ARC_RM_NON_OP_REQ_STATUS_RM_NON_OP_REQ_STATUS_SHFT                                    0x0

#define HWIO_RPMH_ARC_RM_NON_OP_ACK_STATUS_ADDR                                                  (RPMH_ARC_ARC_RM_REG_BASE      + 0x00007064)
#define HWIO_RPMH_ARC_RM_NON_OP_ACK_STATUS_RMSK                                                      0x1fff
#define HWIO_RPMH_ARC_RM_NON_OP_ACK_STATUS_IN          \
        in_dword(HWIO_RPMH_ARC_RM_NON_OP_ACK_STATUS_ADDR)
#define HWIO_RPMH_ARC_RM_NON_OP_ACK_STATUS_INM(m)      \
        in_dword_masked(HWIO_RPMH_ARC_RM_NON_OP_ACK_STATUS_ADDR, m)
#define HWIO_RPMH_ARC_RM_NON_OP_ACK_STATUS_RM_NON_OP_ACK_STATUS_BMSK                                 0x1fff
#define HWIO_RPMH_ARC_RM_NON_OP_ACK_STATUS_RM_NON_OP_ACK_STATUS_SHFT                                    0x0

#define HWIO_RPMH_ARC_EXT_NON_OP_REQ_STATUS_ADDR                                                 (RPMH_ARC_ARC_RM_REG_BASE      + 0x00007068)
#define HWIO_RPMH_ARC_EXT_NON_OP_REQ_STATUS_RMSK                                                        0x3
#define HWIO_RPMH_ARC_EXT_NON_OP_REQ_STATUS_IN          \
        in_dword(HWIO_RPMH_ARC_EXT_NON_OP_REQ_STATUS_ADDR)
#define HWIO_RPMH_ARC_EXT_NON_OP_REQ_STATUS_INM(m)      \
        in_dword_masked(HWIO_RPMH_ARC_EXT_NON_OP_REQ_STATUS_ADDR, m)
#define HWIO_RPMH_ARC_EXT_NON_OP_REQ_STATUS_EXT_NON_OP_REQ_STATUS_BMSK                                  0x3
#define HWIO_RPMH_ARC_EXT_NON_OP_REQ_STATUS_EXT_NON_OP_REQ_STATUS_SHFT                                  0x0

#define HWIO_RPMH_ARC_EXT_NON_OP_ACK_STATUS_ADDR                                                 (RPMH_ARC_ARC_RM_REG_BASE      + 0x0000706c)
#define HWIO_RPMH_ARC_EXT_NON_OP_ACK_STATUS_RMSK                                                        0x3
#define HWIO_RPMH_ARC_EXT_NON_OP_ACK_STATUS_IN          \
        in_dword(HWIO_RPMH_ARC_EXT_NON_OP_ACK_STATUS_ADDR)
#define HWIO_RPMH_ARC_EXT_NON_OP_ACK_STATUS_INM(m)      \
        in_dword_masked(HWIO_RPMH_ARC_EXT_NON_OP_ACK_STATUS_ADDR, m)
#define HWIO_RPMH_ARC_EXT_NON_OP_ACK_STATUS_EXT_NON_OP_ACK_STATUS_BMSK                                  0x3
#define HWIO_RPMH_ARC_EXT_NON_OP_ACK_STATUS_EXT_NON_OP_ACK_STATUS_SHFT                                  0x0

#define HWIO_RPMH_ARC_CPRF_CL_OFF_REQ_STATUS_ADDR                                                (RPMH_ARC_ARC_RM_REG_BASE      + 0x00007070)
#define HWIO_RPMH_ARC_CPRF_CL_OFF_REQ_STATUS_RMSK                                                    0xffff
#define HWIO_RPMH_ARC_CPRF_CL_OFF_REQ_STATUS_IN          \
        in_dword(HWIO_RPMH_ARC_CPRF_CL_OFF_REQ_STATUS_ADDR)
#define HWIO_RPMH_ARC_CPRF_CL_OFF_REQ_STATUS_INM(m)      \
        in_dword_masked(HWIO_RPMH_ARC_CPRF_CL_OFF_REQ_STATUS_ADDR, m)
#define HWIO_RPMH_ARC_CPRF_CL_OFF_REQ_STATUS_CL_OFF_REQ_STATUS_BMSK                                  0xffff
#define HWIO_RPMH_ARC_CPRF_CL_OFF_REQ_STATUS_CL_OFF_REQ_STATUS_SHFT                                     0x0

#define HWIO_RPMH_ARC_CPRF_CL_OFF_ACK_STATUS_ADDR                                                (RPMH_ARC_ARC_RM_REG_BASE      + 0x00007074)
#define HWIO_RPMH_ARC_CPRF_CL_OFF_ACK_STATUS_RMSK                                                    0xffff
#define HWIO_RPMH_ARC_CPRF_CL_OFF_ACK_STATUS_IN          \
        in_dword(HWIO_RPMH_ARC_CPRF_CL_OFF_ACK_STATUS_ADDR)
#define HWIO_RPMH_ARC_CPRF_CL_OFF_ACK_STATUS_INM(m)      \
        in_dword_masked(HWIO_RPMH_ARC_CPRF_CL_OFF_ACK_STATUS_ADDR, m)
#define HWIO_RPMH_ARC_CPRF_CL_OFF_ACK_STATUS_CL_OFF_ACK_STATUS_BMSK                                  0xffff
#define HWIO_RPMH_ARC_CPRF_CL_OFF_ACK_STATUS_CL_OFF_ACK_STATUS_SHFT                                     0x0


#endif /* __ARC_RM_HWIO_H__ */
