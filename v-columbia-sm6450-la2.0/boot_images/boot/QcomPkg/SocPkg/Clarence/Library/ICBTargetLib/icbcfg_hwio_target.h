#ifndef __ICBCFG_HWIO_TARGET_H__
#define __ICBCFG_HWIO_TARGET_H__
/*
===========================================================================
*/
/**
    @file icbcfg_hwio_target.h
    @brief Auto-generated HWIO interface include file.

    This file contains HWIO register definitions for the following modules:
        MC0_MC_COMMON_ISU
        MC1_MC_COMMON_ISU

    'Include' filters applied: ADDR_TRANSLATOR_CFG[MC1_MC_COMMON_ISU] ADDR_TRANSLATOR_CFG[MC0_MC_COMMON_ISU] 

    Generation parameters: 
    { u'filename': u'icbcfg_hwio_target.h',
      u'header': u'#include "../../Include/msmhwiobase.h"',
      u'module-filter-exclude': { },
      u'module-filter-include': { u'MC0_MC_COMMON_ISU': [u'ADDR_TRANSLATOR_CFG'],
                                  u'MC1_MC_COMMON_ISU': [u'ADDR_TRANSLATOR_CFG']},
      u'modules': [u'MC0_MC_COMMON_ISU', u'MC1_MC_COMMON_ISU']}
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

    $Header: //components/dev/core.boot/6.0/aravapal.core.boot.6.0.tip_dev/QcomPkg/SocPkg/Clarence/Library/ICBTargetLib/icbcfg_hwio_target.h#1 $
    $DateTime: 2022/04/30 21:50:34 $
    $Author: aravapal $

    ===========================================================================
*/

#include "../../Include/msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: MC0_MC_COMMON_ISU
 *--------------------------------------------------------------------------*/

#define MC0_MC_COMMON_ISU_REG_BASE                                                                      (DDR_SS_BASE      + 0x00243000)
#define MC0_MC_COMMON_ISU_REG_BASE_SIZE                                                                 0x1000
#define MC0_MC_COMMON_ISU_REG_BASE_USED                                                                 0x920

#define HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ADDR                                                 (MC0_MC_COMMON_ISU_REG_BASE      + 0x200)
#define HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_RMSK                                                      0x3f1
#define HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_IN                    \
                in_dword(HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ADDR)
#define HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_INM(m)            \
                in_dword_masked(HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ADDR, m)
#define HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_OUT(v)            \
                out_dword(HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ADDR,v)
#define HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ADDR,m,v,HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_IN)
#define HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ERROR_BMSK                                                0x3f0
#define HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ERROR_SHFT                                                    4
#define HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ENABLE_BMSK                                                 0x1
#define HWIO_MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ENABLE_SHFT                                                   0

/*----------------------------------------------------------------------------
 * MODULE: MC1_MC_COMMON_ISU
 *--------------------------------------------------------------------------*/

#define MC1_MC_COMMON_ISU_REG_BASE                                                                      (DDR_SS_BASE      + 0x00343000)
#define MC1_MC_COMMON_ISU_REG_BASE_SIZE                                                                 0x1000
#define MC1_MC_COMMON_ISU_REG_BASE_USED                                                                 0x920

#define HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ADDR                                                 (MC1_MC_COMMON_ISU_REG_BASE      + 0x200)
#define HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_RMSK                                                      0x3f1
#define HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_IN                    \
                in_dword(HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ADDR)
#define HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_INM(m)            \
                in_dword_masked(HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ADDR, m)
#define HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_OUT(v)            \
                out_dword(HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ADDR,v)
#define HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ADDR,m,v,HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_IN)
#define HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ERROR_BMSK                                                0x3f0
#define HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ERROR_SHFT                                                    4
#define HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ENABLE_BMSK                                                 0x1
#define HWIO_MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG_ENABLE_SHFT                                                   0

#endif /* __ICBCFG_HWIO_TARGET_H__ */
