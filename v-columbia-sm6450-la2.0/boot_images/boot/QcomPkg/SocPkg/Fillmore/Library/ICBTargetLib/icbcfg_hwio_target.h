#ifndef __ICBCFG_HWIO_TARGET_H__
#define __ICBCFG_HWIO_TARGET_H__
/*
===========================================================================
*/
/**
    @file icbcfg_hwio_target.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM7xxx (Fillmore) [fillmore_v1.0_p3q1r50]
 
    This file contains HWIO register definitions for the following modules:
        LLCC0_LLCC_BEAC0
        LLCC1_LLCC_BEAC0

    'Include' filters applied: ADDR_TRANSLATOR_CFG[LLCC0_LLCC_BEAC0] ADDR_TRANSLATOR_CFG[LLCC1_LLCC_BEAC0] 

    Generation parameters: 
    { 'filename': 'icbcfg_hwio_target.h',
      'header': '#include "../../Include/msmhwiobase.h"',
      'module-filter-exclude': {},
      'module-filter-include': { 'LLCC0_LLCC_BEAC0': ['ADDR_TRANSLATOR_CFG'],
                                 'LLCC1_LLCC_BEAC0': ['ADDR_TRANSLATOR_CFG']},
      'modules': ['LLCC0_LLCC_BEAC0', 'LLCC1_LLCC_BEAC0']}
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

    $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Fillmore/Library/ICBTargetLib/icbcfg_hwio_target.h#4 $
    $DateTime: 2021/04/19 07:32:10 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "../../Include/msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: LLCC0_LLCC_BEAC0
 *--------------------------------------------------------------------------*/

#define LLCC0_LLCC_BEAC0_REG_BASE                                                                       (DDR_SS_BASE            + 0x00260000)
#define LLCC0_LLCC_BEAC0_REG_BASE_SIZE                                                                  0xa000
#define LLCC0_LLCC_BEAC0_REG_BASE_USED                                                                  0x806c

#define HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ADDR                                        (LLCC0_LLCC_BEAC0_REG_BASE            + 0x8000)
#define HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_RMSK                                             0x3f1
#define HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_IN                    \
                in_dword(HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ADDR)
#define HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_INM(m)            \
                in_dword_masked(HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ADDR, m)
#define HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_OUT(v)            \
                out_dword(HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ADDR,v)
#define HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ADDR,m,v,HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_IN)
#define HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ERROR_BMSK                                       0x3f0
#define HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ERROR_SHFT                                           4
#define HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ENABLE_BMSK                                        0x1
#define HWIO_LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ENABLE_SHFT                                          0

/*----------------------------------------------------------------------------
 * MODULE: LLCC1_LLCC_BEAC0
 *--------------------------------------------------------------------------*/

#define LLCC1_LLCC_BEAC0_REG_BASE                                                                       (DDR_SS_BASE            + 0x00360000)
#define LLCC1_LLCC_BEAC0_REG_BASE_SIZE                                                                  0xa000
#define LLCC1_LLCC_BEAC0_REG_BASE_USED                                                                  0x806c

#define HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ADDR                                        (LLCC1_LLCC_BEAC0_REG_BASE            + 0x8000)
#define HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_RMSK                                             0x3f1
#define HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_IN                    \
                in_dword(HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ADDR)
#define HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_INM(m)            \
                in_dword_masked(HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ADDR, m)
#define HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_OUT(v)            \
                out_dword(HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ADDR,v)
#define HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ADDR,m,v,HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_IN)
#define HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ERROR_BMSK                                       0x3f0
#define HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ERROR_SHFT                                           4
#define HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ENABLE_BMSK                                        0x1
#define HWIO_LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG_ENABLE_SHFT                                          0


#endif /* __ICBCFG_HWIO_TARGET_H__ */
