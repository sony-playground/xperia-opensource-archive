#ifndef __LLCC_TRP_REG_OR_KAILUA1_H__
#define __LLCC_TRP_REG_OR_KAILUA1_H__
/*
===========================================================================
*/
/**
    @file llcc_trp_reg_or_kailua1.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8550 (Kailua) [kailua_v1.0_p3q1r7.8_rtl_partition]
 
    This file contains HWIO register definitions for the following modules:
        LLCC_BROADCAST_ORLLCC
        LLCC_BROADCAST_ORTRP
        LLCC_BROADCAST_ORLPI_SHARED


    Generation parameters: 
    { 'explicit-addressing': True,
      'filename': 'llcc_trp_reg_or_kailua1.h',
      'header': '#include <msmhwiobase.h>\n#include <HALhwio.h>',
      'modules': [ 'LLCC_BROADCAST_ORLLCC',
                   'LLCC_BROADCAST_ORTRP',
                   'LLCC_BROADCAST_ORLPI_SHARED'],
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

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/SystemCacheTargetLib/llcc_trp_reg_or.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include <msmhwiobase.h>
#include <HALhwio.h>

/*----------------------------------------------------------------------------
 * MODULE: LLCC_BROADCAST_ORLLCC
 *--------------------------------------------------------------------------*/

#define LLCC_BROADCAST_ORLLCC_REG_BASE (DDR_SS_BASE            + 0x01800000)
#define LLCC_BROADCAST_ORLLCC_REG_BASE_SIZE 0x200000
#define LLCC_BROADCAST_ORLLCC_REG_BASE_USED 0x0
#define LLCC_BROADCAST_ORLLCC_REG_BASE_PHYS (DDR_SS_BASE_PHYS + 0x01800000)
#define LLCC_BROADCAST_ORLLCC_REG_BASE_OFFS 0x01800000

/*----------------------------------------------------------------------------
 * MODULE: LLCC_BROADCAST_ORTRP
 *--------------------------------------------------------------------------*/

#define LLCC_BROADCAST_ORTRP_REG_BASE                                                                            (DDR_SS_BASE            + 0x01800000)
#define LLCC_BROADCAST_ORTRP_REG_BASE_SIZE                                                                       0x30000
#define LLCC_BROADCAST_ORTRP_REG_BASE_USED                                                                       0x25018
#define LLCC_BROADCAST_ORTRP_REG_BASE_PHYS                                                                       (DDR_SS_BASE_PHYS + 0x01800000)
#define LLCC_BROADCAST_ORTRP_REG_BASE_OFFS                                                                       0x01800000

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_ADDR(base,n)                                              ((base) + 0X0 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_PHYS(base,n)                                              ((base) + 0X0 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OFFS(n)                                                   (0X0 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_RMSK                                                             0x7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_MAXn                                                              31
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OUTI(base,n,val)        \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_ADDR(base,n),val)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_ADDR(base,n),mask,val,HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_INI(base,n))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_BMSK                                                      0x6
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_SHFT                                                        1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_ACT_TRIG_BMSK                                                    0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_ACT_TRIG_SHFT                                                      0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ADDR(base,n)                                                ((base) + 0X4 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_PHYS(base,n)                                                ((base) + 0X4 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_OFFS(n)                                                     (0X4 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_RMSK                                                        0x7fff0013
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_MAXn                                                                31
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_CURRENT_CAP_BMSK                                            0x7fff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_CURRENT_CAP_SHFT                                                    16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACT_COMPLETE_BMSK                                                 0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACT_COMPLETE_SHFT                                                    4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_DEACTIVE_BMSK                                                      0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_DEACTIVE_SHFT                                                        1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACTIVE_BMSK                                                        0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACTIVE_SHFT                                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CLEAR_ADDR(base,n)                                             ((base) + 0X8 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CLEAR_PHYS(base,n)                                             ((base) + 0X8 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CLEAR_OFFS(n)                                                  (0X8 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CLEAR_RMSK                                                            0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CLEAR_MAXn                                                             31
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CLEAR_OUTI(base,n,val)        \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CLEAR_ADDR(base,n),val)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CLEAR_ACT_COMPLETE_CLEAR_BMSK                                         0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CLEAR_ACT_COMPLETE_CLEAR_SHFT                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_ADDR(base,n)                                        ((base) + 0X20000 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_PHYS(base,n)                                        ((base) + 0X20000 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_OFFS(n)                                             (0X20000 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_RMSK                                                0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_MAXn                                                        23
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_ECC_MASK_BMSK                                       0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN7_ECC_MASK_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_ADDR(base,n)                                        ((base) + 0X20060 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_PHYS(base,n)                                        ((base) + 0X20060 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_OFFS(n)                                             (0X20060 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_RMSK                                                0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_MAXn                                                        23
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_ECC_MASK_BMSK                                       0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_WAY_n_SYN8_ECC_MASK_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_ADDR(base,n)                                        ((base) + 0X20100 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_PHYS(base,n)                                        ((base) + 0X20100 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_OFFS(n)                                             (0X20100 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_RMSK                                                0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_MAXn                                                        23
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_ECC_MASK_BMSK                                       0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN7_ECC_MASK_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_ADDR(base,n)                                        ((base) + 0X20160 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_PHYS(base,n)                                        ((base) + 0X20160 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_OFFS(n)                                             (0X20160 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_RMSK                                                0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_MAXn                                                        23
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_ECC_MASK_BMSK                                       0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_WAY_n_SYN8_ECC_MASK_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_ADDR(x)                                                        ((x) + 0x20334)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_PHYS(x)                                                        ((x) + 0x20334)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_OFFS                                                           (0x20334)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_RMSK                                                             0xff13ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_BLK_OFF_BMSK                                                     0xe00000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_BLK_OFF_SHFT                                                           21
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_TARGET_WAY_BMSK                                                  0x1f0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_TARGET_WAY_SHFT                                                        16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_DCRSW_TRIG_BMSK                                                    0x1000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_DCRSW_TRIG_SHFT                                                        12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_SET_NDX_BMSK                                                        0x3ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_CFG0_SET_NDX_SHFT                                                            0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_ADDR(x)                                                     ((x) + 0x20338)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_PHYS(x)                                                     ((x) + 0x20338)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_OFFS                                                        (0x20338)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_RMSK                                                        0x100fffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_DONE_BMSK                                                   0x10000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_DONE_SHFT                                                           28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_TAG_BMSK                                                       0xfffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS0_TAG_SHFT                                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_ADDR(x)                                                     ((x) + 0x2033c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_PHYS(x)                                                     ((x) + 0x2033c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_OFFS                                                        (0x2033c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_RMSK                                                           0x7ffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_PROTNS_BMSK                                                    0x40000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_PROTNS_SHFT                                                         18
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_ACRYPT_BMSK                                                    0x20000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_ACRYPT_SHFT                                                         17
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_AECC_BMSK                                                      0x10000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_AECC_SHFT                                                           16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_AAUTH_BMSK                                                      0x8000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_AAUTH_SHFT                                                          15
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_AARCMD_BMSK                                                     0x4000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_AARCMD_SHFT                                                         14
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_EWD_BMSK                                                        0x2000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_EWD_SHFT                                                            13
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_HASPLD_N_BMSK                                                   0x1000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_HASPLD_N_SHFT                                                       12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_VZID_BMSK                                                        0xe00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_VZID_SHFT                                                            9
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_SCID_BMSK                                                        0x1f0
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_SCID_SHFT                                                            4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_G1_DTY_BMSK                                                        0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_G1_DTY_SHFT                                                          3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_G1_VLD_BMSK                                                        0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_G1_VLD_SHFT                                                          2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_G0_DTY_BMSK                                                        0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_G0_DTY_SHFT                                                          1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_G0_VLD_BMSK                                                        0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS1_G0_VLD_SHFT                                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_ADDR(x)                                                     ((x) + 0x20340)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_PHYS(x)                                                     ((x) + 0x20340)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_OFFS                                                        (0x20340)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_RMSK                                                        0xff00ff30
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_SB_ERROR_INTERRUPT_THRESHOLD_BMSK                           0xff000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_SB_ERROR_INTERRUPT_THRESHOLD_SHFT                                   24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_SB_ERROR_DEBUG_EVENT_THRESHOLD_BIT_BMSK                         0xff00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_SB_ERROR_DEBUG_EVENT_THRESHOLD_BIT_SHFT                              8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_DB_QDSS_EVENT_LOGGING_EN_BMSK                                     0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_DB_QDSS_EVENT_LOGGING_EN_SHFT                                        5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_SB_QDSS_EVENT_LOGGING_EN_BMSK                                     0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CFG_SB_QDSS_EVENT_LOGGING_EN_SHFT                                        4

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS0_ADDR(x)                                                 ((x) + 0x20344)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS0_PHYS(x)                                                 ((x) + 0x20344)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS0_OFFS                                                    (0x20344)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS0_RMSK                                                      0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS0_WAYS_SB_ERROR_OCCURRED_BMSK                               0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS0_WAYS_SB_ERROR_OCCURRED_SHFT                                      0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS1_ADDR(x)                                                 ((x) + 0x20348)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS1_PHYS(x)                                                 ((x) + 0x20348)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS1_OFFS                                                    (0x20348)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS1_RMSK                                                      0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS1_WAYS_DB_ERROR_OCCURRED_BMSK                               0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS1_WAYS_DB_ERROR_OCCURRED_SHFT                                      0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_ADDR(x)                                                   ((x) + 0x2034c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_PHYS(x)                                                   ((x) + 0x2034c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_OFFS                                                      (0x2034c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_RMSK                                                          0x3371
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_RWI_BMSK                                                      0x2000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_RWI_SHFT                                                          13
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_RWE_BMSK                                                      0x1000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_RWE_SHFT                                                          12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_ALFOM_BMSK                                                     0x200
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_ALFOM_SHFT                                                         9
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_ALFOP_BMSK                                                     0x100
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_ALFOP_SHFT                                                         8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_CMO_CLEAN_BMSK                                                  0x40
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_CMO_CLEAN_SHFT                                                     6
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_CMO_INVAL_BMSK                                                  0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_CMO_INVAL_SHFT                                                     5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_CMO_READ_BMSK                                                   0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_CMO_READ_SHFT                                                      4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_TCM_BMSK                                                         0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN0_TCM_SHFT                                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_ADDR(x)                                                   ((x) + 0x20350)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_PHYS(x)                                                   ((x) + 0x20350)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_OFFS                                                      (0x20350)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_RMSK                                                      0xffffffdf
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_MID_BMSK                                                  0xffff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_MID_SHFT                                                          16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_TID_BMSK                                                      0xffc0
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_TID_SHFT                                                           6
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_SCID_BMSK                                                       0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN1_SCID_SHFT                                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN2_ADDR(x)                                                   ((x) + 0x20354)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN2_PHYS(x)                                                   ((x) + 0x20354)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN2_OFFS                                                      (0x20354)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN2_RMSK                                                        0x3ff000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN2_SET_NDX_BMSK                                                0x3ff000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN2_SET_NDX_SHFT                                                      12

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_ADDR(x)                                                   ((x) + 0x20358)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_PHYS(x)                                                   ((x) + 0x20358)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_OFFS                                                      (0x20358)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_RMSK                                                      0x1f0fffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_WAY_LOGGED_BMSK                                           0x1f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_WAY_LOGGED_SHFT                                                   24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_UNCORRECTED_TAG_BMSK                                         0xfffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN3_UNCORRECTED_TAG_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_ADDR(x)                                                   ((x) + 0x2035c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_PHYS(x)                                                   ((x) + 0x2035c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_OFFS                                                      (0x2035c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_RMSK                                                      0xffff1f33
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_PARITY_BITS_BMSK                              0xff000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_PARITY_BITS_SHFT                                      24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_PROTNS_BMSK                                     0x800000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_PROTNS_SHFT                                           23
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_ACRYPT_BMSK                                     0x400000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_ACRYPT_SHFT                                           22
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_AECC_BMSK                                       0x200000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_AECC_SHFT                                             21
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_ADDITIONAL_BIT_BMSK                             0x100000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_ADDITIONAL_BIT_SHFT                                   20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_HASPLD_N_BMSK                                    0x80000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_HASPLD_N_SHFT                                         19
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_VZID_BMSK                                        0x70000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_VZID_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_SCID_BMSK                                         0x1f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_SCID_SHFT                                              8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_DIRTY_1_BMSK                                        0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_DIRTY_1_SHFT                                           5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_VLD_1_BMSK                                          0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_VLD_1_SHFT                                             4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_DIRTY_0_BMSK                                         0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_DIRTY_0_SHFT                                           1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_VLD_0_BMSK                                           0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN4_UNCORRECTED_VLD_0_SHFT                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN5_ADDR(x)                                                   ((x) + 0x20360)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN5_PHYS(x)                                                   ((x) + 0x20360)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN5_OFFS                                                      (0x20360)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN5_RMSK                                                      0x3fffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN5_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN5_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN5_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN5_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN5_ADDR_BMSK                                                 0x3fffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN5_ADDR_SHFT                                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_ADDR(x)                                                   ((x) + 0x20364)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_PHYS(x)                                                   ((x) + 0x20364)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_OFFS                                                      (0x20364)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_RMSK                                                        0x3fffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_AAUTH_BMSK                                      0x200000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_AAUTH_SHFT                                            21
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_AARC_BMSK                                       0x100000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_AARC_SHFT                                             20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_MT1_DIRTY_BMSK                                   0x80000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_MT1_DIRTY_SHFT                                        19
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_MT1_VALID_BMSK                                   0x40000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_MT1_VALID_SHFT                                        18
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_MT0_DIRTY_BMSK                                   0x20000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_MT0_DIRTY_SHFT                                        17
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_MT0_VALID_BMSK                                   0x10000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_MT0_VALID_SHFT                                        16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_MEMTAG_BMSK                                       0xffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_SB_ERR_SYN6_UNCORRECTED_MEMTAG_SHFT                                            0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_ADDR(x)                                                 ((x) + 0x20368)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_PHYS(x)                                                 ((x) + 0x20368)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_OFFS                                                    (0x20368)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_RMSK                                                      0xff003f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_SB_ERROR_COUNTER_BMSK                                     0xff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_SB_ERROR_COUNTER_SHFT                                           16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_DB_ERROR_COUNTER_BMSK                                         0x3f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_STATUS2_DB_ERROR_COUNTER_SHFT                                            0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_ADDR(x)                                                   ((x) + 0x20370)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_PHYS(x)                                                   ((x) + 0x20370)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_OFFS                                                      (0x20370)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_RMSK                                                          0x3371
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_RWI_BMSK                                                      0x2000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_RWI_SHFT                                                          13
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_RWE_BMSK                                                      0x1000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_RWE_SHFT                                                          12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_ALFOM_BMSK                                                     0x200
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_ALFOM_SHFT                                                         9
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_ALFOP_BMSK                                                     0x100
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_ALFOP_SHFT                                                         8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_CMO_CLEAN_BMSK                                                  0x40
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_CMO_CLEAN_SHFT                                                     6
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_CMO_INVAL_BMSK                                                  0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_CMO_INVAL_SHFT                                                     5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_CMO_READ_BMSK                                                   0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_CMO_READ_SHFT                                                      4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_TCM_BMSK                                                         0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN0_TCM_SHFT                                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_ADDR(x)                                                   ((x) + 0x20374)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_PHYS(x)                                                   ((x) + 0x20374)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_OFFS                                                      (0x20374)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_RMSK                                                      0xffffffdf
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_MID_BMSK                                                  0xffff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_MID_SHFT                                                          16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_TID_BMSK                                                      0xffc0
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_TID_SHFT                                                           6
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_SCID_BMSK                                                       0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN1_SCID_SHFT                                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN2_ADDR(x)                                                   ((x) + 0x20378)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN2_PHYS(x)                                                   ((x) + 0x20378)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN2_OFFS                                                      (0x20378)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN2_RMSK                                                        0x3ff000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN2_SET_NDX_BMSK                                                0x3ff000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN2_SET_NDX_SHFT                                                      12

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_ADDR(x)                                                   ((x) + 0x2037c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_PHYS(x)                                                   ((x) + 0x2037c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_OFFS                                                      (0x2037c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_RMSK                                                      0x1f0fffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_WAY_LOGGED_BMSK                                           0x1f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_WAY_LOGGED_SHFT                                                   24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_UNCORRECTED_TAG_BMSK                                         0xfffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN3_UNCORRECTED_TAG_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_ADDR(x)                                                   ((x) + 0x20380)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_PHYS(x)                                                   ((x) + 0x20380)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_OFFS                                                      (0x20380)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_RMSK                                                      0xffff1f33
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_PARITY_BITS_BMSK                              0xff000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_PARITY_BITS_SHFT                                      24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_PROTNS_BMSK                                     0x800000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_PROTNS_SHFT                                           23
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_ACRYPT_BMSK                                     0x400000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_ACRYPT_SHFT                                           22
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_AECC_BMSK                                       0x200000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_AECC_SHFT                                             21
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_ADDITIONAL_BIT_BMSK                             0x100000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_ADDITIONAL_BIT_SHFT                                   20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_HASPLD_N_BMSK                                    0x80000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_HASPLD_N_SHFT                                         19
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_VZID_BMSK                                        0x70000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_VZID_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_SCID_BMSK                                         0x1f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_SCID_SHFT                                              8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_DIRTY_1_BMSK                                        0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_DIRTY_1_SHFT                                           5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_VLD_1_BMSK                                          0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_VLD_1_SHFT                                             4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_DIRTY_0_BMSK                                         0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_DIRTY_0_SHFT                                           1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_VLD_0_BMSK                                           0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN4_UNCORRECTED_VLD_0_SHFT                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN5_ADDR(x)                                                   ((x) + 0x20384)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN5_PHYS(x)                                                   ((x) + 0x20384)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN5_OFFS                                                      (0x20384)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN5_RMSK                                                      0x3fffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN5_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN5_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN5_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN5_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN5_ADDR_BMSK                                                 0x3fffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN5_ADDR_SHFT                                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_ADDR(x)                                                   ((x) + 0x20388)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_PHYS(x)                                                   ((x) + 0x20388)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_OFFS                                                      (0x20388)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_RMSK                                                        0x3fffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_AAUTH_BMSK                                      0x200000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_AAUTH_SHFT                                            21
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_AARC_BMSK                                       0x100000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_AARC_SHFT                                             20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_MT1_DIRTY_BMSK                                   0x80000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_MT1_DIRTY_SHFT                                        19
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_MT1_VALID_BMSK                                   0x40000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_MT1_VALID_SHFT                                        18
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_MT0_DIRTY_BMSK                                   0x20000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_MT0_DIRTY_SHFT                                        17
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_MT0_VALID_BMSK                                   0x10000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_MT0_VALID_SHFT                                        16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_MEMTAG_BMSK                                       0xffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_DB_ERR_SYN6_UNCORRECTED_MEMTAG_SHFT                                            0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_ADDR(x)                                             ((x) + 0x20400)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_PHYS(x)                                             ((x) + 0x20400)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_OFFS                                                (0x20400)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_RMSK                                                0xe0000003
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_DOWN_COUNTER_EN_BMSK                                0x80000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_DOWN_COUNTER_EN_SHFT                                        31
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_REPEAT_BMSK                                         0x40000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_REPEAT_SHFT                                                 30
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_INJECT_ERROR_ON_ACCESS_BMSK                         0x20000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_INJECT_ERROR_ON_ACCESS_SHFT                                 29
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_DB_ERR_BMSK                                                0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_DB_ERR_SHFT                                                  1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_SB_ERR_BMSK                                                0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_0_SB_ERR_SHFT                                                  0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_ADDR(x)                                             ((x) + 0x20404)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_PHYS(x)                                             ((x) + 0x20404)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_OFFS                                                (0x20404)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_RMSK                                                0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_DOWN_COUNTER_VAL_BMSK                               0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_INJECTION_1_DOWN_COUNTER_VAL_SHFT                                        0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CNTR_CLEAR_ADDR(x)                                              ((x) + 0x20440)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CNTR_CLEAR_PHYS(x)                                              ((x) + 0x20440)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CNTR_CLEAR_OFFS                                                 (0x20440)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CNTR_CLEAR_RMSK                                                        0x3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CNTR_CLEAR_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CNTR_CLEAR_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CNTR_CLEAR_DB_COUNTER_CLEAR_BMSK                                       0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CNTR_CLEAR_DB_COUNTER_CLEAR_SHFT                                         1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CNTR_CLEAR_SB_COUNTER_CLEAR_BMSK                                       0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ECC_ERROR_CNTR_CLEAR_SB_COUNTER_CLEAR_SHFT                                         0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_ADDR(x)                                                     ((x) + 0x20450)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_PHYS(x)                                                     ((x) + 0x20450)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_OFFS                                                        (0x20450)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_RMSK                                                           0xfffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_AMT1_DIRTY_BMSK                                                0x80000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_AMT1_DIRTY_SHFT                                                     19
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_AMT1_VALID_BMSK                                                0x40000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_AMT1_VALID_SHFT                                                     18
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_AMT0_DIRTY_BMSK                                                0x20000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_AMT0_DIRTY_SHFT                                                     17
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_AMT0_VALID_BMSK                                                0x10000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_AMT0_VALID_SHFT                                                     16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_AMEMTAG_BMSK                                                    0xffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS2_AMEMTAG_SHFT                                                         0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS3_ADDR(x)                                                     ((x) + 0x20454)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS3_PHYS(x)                                                     ((x) + 0x20454)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS3_OFFS                                                        (0x20454)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS3_RMSK                                                              0xff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS3_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS3_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS3_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS3_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS3_ECC_BITS_BMSK                                                     0xff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DCRSW_STATUS3_ECC_BITS_SHFT                                                        0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_ADDR(x)                                                ((x) + 0x20480)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_PHYS(x)                                                ((x) + 0x20480)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_OFFS                                                   (0x20480)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_RMSK                                                         0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_FLUSH_ABORT_DONE_BMSK                                        0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_FLUSH_ABORT_DONE_SHFT                                           4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_FLUSH_DONE_BMSK                                               0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_FLUSH_DONE_SHFT                                                 3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_INIT_DONE_BMSK                                                0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_INIT_DONE_SHFT                                                  2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_DB_ECC_ERROR_BMSK                                             0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_DB_ECC_ERROR_SHFT                                               1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_SB_ECC_ERROR_BMSK                                             0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_STATUS_SB_ECC_ERROR_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_ADDR(x)                                                 ((x) + 0x20484)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_PHYS(x)                                                 ((x) + 0x20484)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_OFFS                                                    (0x20484)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_RMSK                                                          0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_FLUSH_ABORT_DONE_BMSK                                         0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_FLUSH_ABORT_DONE_SHFT                                            4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_FLUSH_DONE_BMSK                                                0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_FLUSH_DONE_SHFT                                                  3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_INIT_DONE_BMSK                                                 0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_INIT_DONE_SHFT                                                   2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_DB_ECC_ERROR_BMSK                                              0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_DB_ECC_ERROR_SHFT                                                1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_SB_ECC_ERROR_BMSK                                              0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_CLEAR_SB_ECC_ERROR_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_ADDR(x)                                                ((x) + 0x20488)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_PHYS(x)                                                ((x) + 0x20488)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_OFFS                                                   (0x20488)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_RMSK                                                         0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_FLUSH_ABORT_DONE_BMSK                                        0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_FLUSH_ABORT_DONE_SHFT                                           4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_FLUSH_DONE_BMSK                                               0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_FLUSH_DONE_SHFT                                                 3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_INIT_DONE_BMSK                                                0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_INIT_DONE_SHFT                                                  2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_DB_ECC_ERROR_BMSK                                             0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_DB_ECC_ERROR_SHFT                                               1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_SB_ECC_ERROR_BMSK                                             0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_0_ENABLE_SB_ECC_ERROR_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_ADDR(base,n)                                         ((base) + 0X21000 + (0x8*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_PHYS(base,n)                                         ((base) + 0X21000 + (0x8*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_OFFS(n)                                              (0X21000 + (0x8*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_RMSK                                                   0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_MAXn                                                         31
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_OUTI(base,n,val)        \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_ADDR(base,n),val)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_ADDR(base,n),mask,val,HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_INI(base,n))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_RESRVED_WAYS_BMSK                                      0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_RESRVED_WAYS_SHFT                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_ADDR(base,n)                                         ((base) + 0X21004 + (0x8*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PHYS(base,n)                                         ((base) + 0X21004 + (0x8*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_OFFS(n)                                              (0X21004 + (0x8*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_RMSK                                                 0x7fff9f7f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_MAXn                                                         31
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_OUTI(base,n,val)        \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_ADDR(base,n),val)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_ADDR(base,n),mask,val,HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_INI(base,n))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_MAX_CAP_BMSK                                         0x7fff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_MAX_CAP_SHFT                                                 16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_IN_A_GROUP_BMSK                                          0x8000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_IN_A_GROUP_SHFT                                              15
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PARENT_SCID_BMSK                                         0x1f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PARENT_SCID_SHFT                                              8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PRIORITY_BMSK                                              0x70
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PRIORITY_SHFT                                                 4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_FIXEDSIZE_BMSK                                              0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_FIXEDSIZE_SHFT                                                3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PROBE_TARGET_WAYS_ONLY_BMSK                                 0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PROBE_TARGET_WAYS_ONLY_SHFT                                   2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_CACHING_MODE_BMSK                                           0x3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_CACHING_MODE_SHFT                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_ADDR(base,n)                                         ((base) + 0X21100 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_PHYS(base,n)                                         ((base) + 0X21100 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_OFFS(n)                                              (0X21100 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_RMSK                                                   0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_MAXn                                                         31
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_OUTI(base,n,val)        \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_ADDR(base,n),val)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_ADDR(base,n),mask,val,HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_INI(base,n))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_BONUS_WAYS_BMSK                                        0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_BONUS_WAYS_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_ADDR(x)                                            ((x) + 0x21f00)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_PHYS(x)                                            ((x) + 0x21f00)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_OFFS                                               (0x21f00)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_RMSK                                               0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_CAP_ALLOC_DISABLE_BMSK                             0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_CAP_ALLOC_DISABLE_SHFT                                      0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_ADDR(x)                                                         ((x) + 0x21f0c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_PHYS(x)                                                         ((x) + 0x21f0c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_OFFS                                                            (0x21f0c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_RMSK                                                            0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_SCT_STALE_EN_BMSK                                               0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG1_SCT_STALE_EN_SHFT                                                        0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_ADDR(x)                                                         ((x) + 0x21f10)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_PHYS(x)                                                         ((x) + 0x21f10)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_OFFS                                                            (0x21f10)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_RMSK                                                            0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_STALE_ONLY_ON_OC_BMSK                                           0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG2_STALE_ONLY_ON_OC_SHFT                                                    0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_ADDR(x)                                                         ((x) + 0x21f14)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_PHYS(x)                                                         ((x) + 0x21f14)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_OFFS                                                            (0x21f14)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_RMSK                                                            0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_MRU_RO_ON_TWAYS_IF_UC_BMSK                                      0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG3_MRU_RO_ON_TWAYS_IF_UC_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_ADDR(x)                                                         ((x) + 0x21f18)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_PHYS(x)                                                         ((x) + 0x21f18)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_OFFS                                                            (0x21f18)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_RMSK                                                            0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_MRU_ROLLOVER_ONLY_ON_TWAYS_BMSK                                 0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG4_MRU_ROLLOVER_ONLY_ON_TWAYS_SHFT                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_ADDR(x)                                                         ((x) + 0x21f1c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_PHYS(x)                                                         ((x) + 0x21f1c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_OFFS                                                            (0x21f1c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_RMSK                                                            0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_ALWAYS_ALLOC_ONE_WAY_ON_OC_BMSK                                 0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5_ALWAYS_ALLOC_ONE_WAY_ON_OC_SHFT                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_ADDR(x)                                                      ((x) + 0x21f20)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_PHYS(x)                                                      ((x) + 0x21f20)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_OFFS                                                         (0x21f20)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_RMSK                                                         0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_SCID_EN_BMSK                                                 0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_EN_SCID_EN_SHFT                                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_ADDR(x)                                                         ((x) + 0x21f24)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_PHYS(x)                                                         ((x) + 0x21f24)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_OFFS                                                            (0x21f24)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_RMSK                                                            0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_ALLOC_OTHER_OC_ON_OC_BMSK                                       0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG6_ALLOC_OTHER_OC_ON_OC_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_ADDR(x)                                                         ((x) + 0x21f28)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_PHYS(x)                                                         ((x) + 0x21f28)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_OFFS                                                            (0x21f28)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_RMSK                                                            0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_ALLOC_OTHER_LP_OC_ON_OC_BMSK                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG7_ALLOC_OTHER_LP_OC_ON_OC_SHFT                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_ADDR(x)                                            ((x) + 0x21f2c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_PHYS(x)                                            ((x) + 0x21f2c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_OFFS                                               (0x21f2c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_RMSK                                               0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_SCID_EN_BMSK                                       0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_WRSC_CACHEABLE_EN_SCID_EN_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_ADDR(x)                                                         ((x) + 0x21f30)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_PHYS(x)                                                         ((x) + 0x21f30)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_OFFS                                                            (0x21f30)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_RMSK                                                            0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_ALLOC_VICTIM_PL_ON_UC_BMSK                                      0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG8_ALLOC_VICTIM_PL_ON_UC_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_ADDR(base,n)                                                  ((base) + 0X22000 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_PHYS(base,n)                                                  ((base) + 0X22000 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_OFFS(n)                                                       (0X22000 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_RMSK                                                          0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_MAXn                                                                   2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_OUTI(base,n,val)        \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_ADDR(base,n),val)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_ADDR(base,n),mask,val,HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_INI(base,n))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_SR_31_0_BMSK                                                  0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SPARE_n_CFG_SR_31_0_SHFT                                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ADDR(x)                                                          ((x) + 0x22300)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_PHYS(x)                                                          ((x) + 0x22300)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_OFFS                                                             (0x22300)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_RMSK                                                             0xbf3ffffe
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_MRU_DISABLE_BMSK                                                 0x80000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_MRU_DISABLE_SHFT                                                         31
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_NO_BKID_UPDATE_ON_HIT_BMSK                                       0x20000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_NO_BKID_UPDATE_ON_HIT_SHFT                                               29
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_SCID_UPDATE_ON_WR_HIT_BMSK                                       0x10000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_SCID_UPDATE_ON_WR_HIT_SHFT                                               28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_TCM_REISSUE_ON_NO_WAY_BMSK                                        0x8000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_TCM_REISSUE_ON_NO_WAY_SHFT                                               27
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_DEVICE_MISS_ON_EWD_LINE_BMSK                                      0x4000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_DEVICE_MISS_ON_EWD_LINE_SHFT                                             26
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_PA_CMO_ONLY_ON_EWD_LINE_BMSK                                      0x2000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_PA_CMO_ONLY_ON_EWD_LINE_SHFT                                             25
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_HASH_EN_BMSK                                                      0x1000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_HASH_EN_SHFT                                                             24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ZEROPLD_ALLOCATION_DISABLE_BMSK                                    0x200000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ZEROPLD_ALLOCATION_DISABLE_SHFT                                          21
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_DEVICE_PA_CMO_ON_EWD_LINE_BMSK                                     0x100000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_DEVICE_PA_CMO_ON_EWD_LINE_SHFT                                           20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_WRBUF_THLD_BMSK                                                     0xf0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_WRBUF_THLD_SHFT                                                          16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_HP_WR_THLD_BMSK                                                      0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_HP_WR_THLD_SHFT                                                          12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_LP_WR_THLD_BMSK                                                       0xf00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_LP_WR_THLD_SHFT                                                           8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ET_DISABLE_QOS_BMSK                                                    0x80
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ET_DISABLE_QOS_SHFT                                                       7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ET_HP_DEPTH_BMSK                                                       0x70
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ET_HP_DEPTH_SHFT                                                          4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ET_HP_DEPTH_UPDATE_BMSK                                                 0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_ET_HP_DEPTH_UPDATE_SHFT                                                   3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_CMD_NOT_STALL_ON_ET_FULL_BMSK                                           0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_CMD_NOT_STALL_ON_ET_FULL_SHFT                                             2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_TAG_RAM_ECC_DISABLE_BMSK                                                0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_TAG_RAM_ECC_DISABLE_SHFT                                                  1

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_ADDR(x)                                                          ((x) + 0x22304)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_PHYS(x)                                                          ((x) + 0x22304)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_OFFS                                                             (0x22304)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_RMSK                                                             0x7f3ffff7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_WRSC_SCB_DEPTH_HIGH_THRESHOLD_BMSK                               0x7f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_WRSC_SCB_DEPTH_HIGH_THRESHOLD_SHFT                                       24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_WRSC_SCB_DEPTH_LOW_THRESHOLD_BMSK                                  0x3f0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_WRSC_SCB_DEPTH_LOW_THRESHOLD_SHFT                                        16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_WRSC_DEPTH_BMSK                                                      0xfff0
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_WRSC_DEPTH_SHFT                                                           4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_WRSC_FT_DEPTH_BMSK                                                      0x7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG_WRSC_FT_DEPTH_SHFT                                                        0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_ADDR(x)                                                         ((x) + 0x22308)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_PHYS(x)                                                         ((x) + 0x22308)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_OFFS                                                            (0x22308)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_RMSK                                                              0x700110
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_VICTIM_PL_THRESHOLD_BMSK                                          0x700000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_VICTIM_PL_THRESHOLD_SHFT                                                20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_MRU_RR_ENABLE_BMSK                                                   0x100
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_MRU_RR_ENABLE_SHFT                                                       8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_SAME_PL_VICTIM_DISABLE_BMSK                                           0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0_SAME_PL_VICTIM_DISABLE_SHFT                                              4

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_ADDR(x)                                                        ((x) + 0x22310)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_PHYS(x)                                                        ((x) + 0x22310)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_OFFS                                                           (0x22310)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_RMSK                                                           0x800018f8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_ENABLE_BEAC_FAST_PATH_BMSK                                     0x80000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_ENABLE_BEAC_FAST_PATH_SHFT                                             31
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_ALLOC_CLEAN_ON_WR_BMSK                                             0x1000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_ALLOC_CLEAN_ON_WR_SHFT                                                 12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_ALLOC_CLEAN_ON_RD_BMSK                                              0x800
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_ALLOC_CLEAN_ON_RD_SHFT                                                 11
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_LCPB_ET_DISABLE_QOS_BMSK                                             0x80
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_LCPB_ET_DISABLE_QOS_SHFT                                                7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_LCPB_ET_HP_DEPTH_BMSK                                                0x70
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_LCPB_ET_HP_DEPTH_SHFT                                                   4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_LCPB_ET_HP_DEPTH_UPDATE_BMSK                                          0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_MISC_CFG_1_LCPB_ET_HP_DEPTH_UPDATE_SHFT                                            3

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_ADDR(x)                                     ((x) + 0x2231c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_PHYS(x)                                     ((x) + 0x2231c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_OFFS                                        (0x2231c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_RMSK                                        0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_DISABLE_SELF_EVICT_ON_OVERCAP_BMSK          0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_SELF_EVICT_ON_OC_DISABLE_SELF_EVICT_ON_OVERCAP_SHFT                   0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_ADDR(x)                                             ((x) + 0x22320)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_PHYS(x)                                             ((x) + 0x22320)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_OFFS                                                (0x22320)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_RMSK                                                0x7f7f7f7f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_PRIORITYLVL_3_BMSK                                  0x7f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_PRIORITYLVL_3_SHFT                                          24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_PRIORITYLVL_2_BMSK                                    0x7f0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_PRIORITYLVL_2_SHFT                                          16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_PRIORITYLVL_1_BMSK                                      0x7f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_PRIORITYLVL_1_SHFT                                           8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_PRIORITYLVL_0_BMSK                                        0x7f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG0_PRIORITYLVL_0_SHFT                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_ADDR(x)                                             ((x) + 0x22324)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_PHYS(x)                                             ((x) + 0x22324)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_OFFS                                                (0x22324)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_RMSK                                                0x7f7f7f7f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_PRIORITYLVL_3_BMSK                                  0x7f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_PRIORITYLVL_3_SHFT                                          24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_PRIORITYLVL_2_BMSK                                    0x7f0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_PRIORITYLVL_2_SHFT                                          16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_PRIORITYLVL_1_BMSK                                      0x7f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_PRIORITYLVL_1_SHFT                                           8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_PRIORITYLVL_0_BMSK                                        0x7f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG1_PRIORITYLVL_0_SHFT                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_ADDR(x)                                             ((x) + 0x22328)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_PHYS(x)                                             ((x) + 0x22328)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_OFFS                                                (0x22328)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_RMSK                                                0x7f7f7f7f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_PRIORITYLVL_3_BMSK                                  0x7f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_PRIORITYLVL_3_SHFT                                          24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_PRIORITYLVL_2_BMSK                                    0x7f0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_PRIORITYLVL_2_SHFT                                          16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_PRIORITYLVL_1_BMSK                                      0x7f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_PRIORITYLVL_1_SHFT                                           8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_PRIORITYLVL_0_BMSK                                        0x7f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG2_PRIORITYLVL_0_SHFT                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_ADDR(x)                                             ((x) + 0x2232c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_PHYS(x)                                             ((x) + 0x2232c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_OFFS                                                (0x2232c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_RMSK                                                0x7f7f7f7f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_PRIORITYLVL_3_BMSK                                  0x7f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_PRIORITYLVL_3_SHFT                                          24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_PRIORITYLVL_2_BMSK                                    0x7f0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_PRIORITYLVL_2_SHFT                                          16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_PRIORITYLVL_1_BMSK                                      0x7f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_PRIORITYLVL_1_SHFT                                           8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_PRIORITYLVL_0_BMSK                                        0x7f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_PRIORITYLVL_CFG3_PRIORITYLVL_0_SHFT                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS0_ADDR(x)                                                  ((x) + 0x22330)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS0_PHYS(x)                                                  ((x) + 0x22330)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS0_OFFS                                                     (0x22330)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS0_RMSK                                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS0_STATUS_BMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS0_STATUS_SHFT                                                       0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS1_ADDR(x)                                                  ((x) + 0x22334)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS1_PHYS(x)                                                  ((x) + 0x22334)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS1_OFFS                                                     (0x22334)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS1_RMSK                                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS1_STATUS_BMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERNAL_STATUS1_STATUS_SHFT                                                       0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_ADDR(x)                                                ((x) + 0x22398)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_PHYS(x)                                                ((x) + 0x22398)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_OFFS                                                   (0x22398)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_RMSK                                                         0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_FLUSH_ABORT_DONE_BMSK                                        0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_FLUSH_ABORT_DONE_SHFT                                           4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_FLUSH_DONE_BMSK                                               0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_FLUSH_DONE_SHFT                                                 3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_INIT_DONE_BMSK                                                0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_INIT_DONE_SHFT                                                  2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_DB_ECC_ERROR_BMSK                                             0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_DB_ECC_ERROR_SHFT                                               1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_SB_ECC_ERROR_BMSK                                             0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_STATUS_SB_ECC_ERROR_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_ADDR(x)                                                 ((x) + 0x2239c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_PHYS(x)                                                 ((x) + 0x2239c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_OFFS                                                    (0x2239c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_RMSK                                                          0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_FLUSH_ABORT_DONE_BMSK                                         0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_FLUSH_ABORT_DONE_SHFT                                            4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_FLUSH_DONE_BMSK                                                0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_FLUSH_DONE_SHFT                                                  3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_INIT_DONE_BMSK                                                 0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_INIT_DONE_SHFT                                                   2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_DB_ECC_ERROR_BMSK                                              0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_DB_ECC_ERROR_SHFT                                                1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_SB_ECC_ERROR_BMSK                                              0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_CLEAR_SB_ECC_ERROR_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_ADDR(x)                                                ((x) + 0x223a0)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_PHYS(x)                                                ((x) + 0x223a0)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_OFFS                                                   (0x223a0)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_RMSK                                                         0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_FLUSH_ABORT_DONE_BMSK                                        0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_FLUSH_ABORT_DONE_SHFT                                           4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_FLUSH_DONE_BMSK                                               0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_FLUSH_DONE_SHFT                                                 3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_INIT_DONE_BMSK                                                0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_INIT_DONE_SHFT                                                  2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_DB_ECC_ERROR_BMSK                                             0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_DB_ECC_ERROR_SHFT                                               1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_SB_ECC_ERROR_BMSK                                             0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_2_ENABLE_SB_ECC_ERROR_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_ADDR(x)                                                ((x) + 0x223a4)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_PHYS(x)                                                ((x) + 0x223a4)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_OFFS                                                   (0x223a4)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_RMSK                                                         0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_FLUSH_ABORT_DONE_BMSK                                        0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_FLUSH_ABORT_DONE_SHFT                                           4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_FLUSH_DONE_BMSK                                               0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_FLUSH_DONE_SHFT                                                 3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_INIT_DONE_BMSK                                                0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_INIT_DONE_SHFT                                                  2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_DB_ECC_ERROR_BMSK                                             0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_DB_ECC_ERROR_SHFT                                               1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_SB_ECC_ERROR_BMSK                                             0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_STATUS_SB_ECC_ERROR_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_ADDR(x)                                                 ((x) + 0x223a8)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_PHYS(x)                                                 ((x) + 0x223a8)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_OFFS                                                    (0x223a8)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_RMSK                                                          0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_FLUSH_ABORT_DONE_BMSK                                         0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_FLUSH_ABORT_DONE_SHFT                                            4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_FLUSH_DONE_BMSK                                                0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_FLUSH_DONE_SHFT                                                  3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_INIT_DONE_BMSK                                                 0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_INIT_DONE_SHFT                                                   2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_DB_ECC_ERROR_BMSK                                              0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_DB_ECC_ERROR_SHFT                                                1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_SB_ECC_ERROR_BMSK                                              0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_CLEAR_SB_ECC_ERROR_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_ADDR(x)                                                ((x) + 0x223ac)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_PHYS(x)                                                ((x) + 0x223ac)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_OFFS                                                   (0x223ac)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_RMSK                                                         0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_FLUSH_ABORT_DONE_BMSK                                        0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_FLUSH_ABORT_DONE_SHFT                                           4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_FLUSH_DONE_BMSK                                               0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_FLUSH_DONE_SHFT                                                 3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_INIT_DONE_BMSK                                                0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_INIT_DONE_SHFT                                                  2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_DB_ECC_ERROR_BMSK                                             0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_DB_ECC_ERROR_SHFT                                               1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_SB_ECC_ERROR_BMSK                                             0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_3_ENABLE_SB_ECC_ERROR_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_ADDR(x)                                                         ((x) + 0x22400)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_PHYS(x)                                                         ((x) + 0x22400)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_OFFS                                                            (0x22400)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_RMSK                                                              0xff00ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_LCPB_EVICT_VLD_BMSK                                               0xff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_LCPB_EVICT_VLD_SHFT                                                     16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_EVICT_VLD_BMSK                                                        0xff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ET_STATUS_EVICT_VLD_SHFT                                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FT_STATUS_ADDR(x)                                                         ((x) + 0x22404)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FT_STATUS_PHYS(x)                                                         ((x) + 0x22404)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FT_STATUS_OFFS                                                            (0x22404)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FT_STATUS_RMSK                                                                  0xff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FT_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_FT_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FT_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_FT_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FT_STATUS_FT_VLD_BMSK                                                           0xff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FT_STATUS_FT_VLD_SHFT                                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_ADDR(x)                                                       ((x) + 0x22408)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_PHYS(x)                                                       ((x) + 0x22408)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_OFFS                                                          (0x22408)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_RMSK                                                          0x1fff3333
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_WRSC_LLQ_INIT_DONE_BMSK                                       0x10000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_WRSC_LLQ_INIT_DONE_SHFT                                               28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_WRSC_DEPTH_BMSK                                                0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_WRSC_DEPTH_SHFT                                                       16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_WRSC_LLQ_FULL_BMSK                                                0x2000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_WRSC_LLQ_FULL_SHFT                                                    13
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_WRSC_LLQ_EMPTY_BMSK                                               0x1000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_WRSC_LLQ_EMPTY_SHFT                                                   12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_MRU_FIFO_FULL_BMSK                                                 0x200
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_MRU_FIFO_FULL_SHFT                                                     9
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_MRU_FIFO_EMPTY_BMSK                                                0x100
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_MRU_FIFO_EMPTY_SHFT                                                    8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_HQ_FIFO_FULL_BMSK                                                   0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_HQ_FIFO_FULL_SHFT                                                      5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_HQ_FIFO_EMPTY_BMSK                                                  0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_HQ_FIFO_EMPTY_SHFT                                                     4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_RWIQ_FIFO_FULL_BMSK                                                  0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_RWIQ_FIFO_FULL_SHFT                                                    1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_RWIQ_FIFO_EMPTY_BMSK                                                 0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FIFO_STATUS_RWIQ_FIFO_EMPTY_SHFT                                                   0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_ADDR(x)                                                        ((x) + 0x2240c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_PHYS(x)                                                        ((x) + 0x2240c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_OFFS                                                           (0x2240c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_RMSK                                                              0x31f1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_DRIE_STATE_BMSK                                                   0x30000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_DRIE_STATE_SHFT                                                        16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_FLUSH_STATE_BMSK                                                   0x1f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_FLUSH_STATE_SHFT                                                        8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_INIT_STATE_BMSK                                                      0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FSM_STATUS_INIT_STATE_SHFT                                                         0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_ADDR(x)                                                  ((x) + 0x22410)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_PHYS(x)                                                  ((x) + 0x22410)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_OFFS                                                     (0x22410)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_RMSK                                                      0xff7ffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_LCPB_HP_CNTR_BMSK                                         0xf000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_LCPB_HP_CNTR_SHFT                                                24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_LCPB_LP_CNTR_BMSK                                          0xf00000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_LCPB_LP_CNTR_SHFT                                                20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_MRU_FIFO_CNTR_BMSK                                          0x7e000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_MRU_FIFO_CNTR_SHFT                                               13
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_HQ_CNTR_BMSK                                                 0x1f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_HQ_CNTR_SHFT                                                      8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_ET_HP_CNTR_BMSK                                                0xf0
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_ET_HP_CNTR_SHFT                                                   4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_ET_LP_CNTR_BMSK                                                 0xf
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_FLOW_CTRL_STATUS_ET_LP_CNTR_SHFT                                                   0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_ADDR(x)                                                 ((x) + 0x22414)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_PHYS(x)                                                 ((x) + 0x22414)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_OFFS                                                    (0x22414)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_RMSK                                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_RDY_VEC_BMSK                                            0xffff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_RDY_VEC_SHFT                                                    16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_VLD_VEC_BMSK                                                0xffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERFACES_STATUS_VLD_VEC_SHFT                                                     0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_ADDR(x)                                                 ((x) + 0x22418)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_PHYS(x)                                                 ((x) + 0x22418)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_OFFS                                                    (0x22418)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_RMSK                                                     0x1131f1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_WRSC_SCB_EN_RIFB_TH_BMSK                                 0x1000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_WRSC_SCB_EN_RIFB_TH_SHFT                                        24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_WRSC_THRESHOLD_SCB_EN_BMSK                                0x100000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_WRSC_THRESHOLD_SCB_EN_SHFT                                      20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_CURRENT_RANK_BMSK                                          0x30000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_CURRENT_RANK_SHFT                                               16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_LL_SPREAD_COUNT_RANK1_BMSK                                  0x1f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_LL_SPREAD_COUNT_RANK1_SHFT                                       8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_LL_SPREAD_COUNT_RANK0_BMSK                                    0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_1_LL_SPREAD_COUNT_RANK0_SHFT                                       0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_ADDR(x)                                                 ((x) + 0x2241c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_PHYS(x)                                                 ((x) + 0x2241c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_OFFS                                                    (0x2241c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_RMSK                                                     0x7ff07ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_DATA_RAM_RD_ADDR_BMSK                                    0x7ff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_DATA_RAM_RD_ADDR_SHFT                                           16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_DATA_RAM_WR_ADDR_BMSK                                        0x7ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_2_DATA_RAM_WR_ADDR_SHFT                                            0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_3_ADDR(x)                                                 ((x) + 0x22420)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_3_PHYS(x)                                                 ((x) + 0x22420)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_3_OFFS                                                    (0x22420)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_3_RMSK                                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_3_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_3_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_3_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_3_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_3_LL_WR_VALID_VEC_BMSK                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_3_LL_WR_VALID_VEC_SHFT                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_4_ADDR(x)                                                 ((x) + 0x22424)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_4_PHYS(x)                                                 ((x) + 0x22424)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_4_OFFS                                                    (0x22424)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_4_RMSK                                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_4_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_4_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_4_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_4_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_4_LL_RD_VALID_VEC_BMSK                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_4_LL_RD_VALID_VEC_SHFT                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_ADDR(x)                                                 ((x) + 0x22428)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_PHYS(x)                                                 ((x) + 0x22428)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_OFFS                                                    (0x22428)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_RMSK                                                     0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_NODE_COUNT_1_BMSK                                        0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_NODE_COUNT_1_SHFT                                               16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_NODE_COUNT_0_BMSK                                            0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_5_NODE_COUNT_0_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_ADDR(x)                                                 ((x) + 0x2242c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_PHYS(x)                                                 ((x) + 0x2242c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_OFFS                                                    (0x2242c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_RMSK                                                     0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_NODE_COUNT_3_BMSK                                        0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_NODE_COUNT_3_SHFT                                               16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_NODE_COUNT_2_BMSK                                            0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_6_NODE_COUNT_2_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_ADDR(x)                                                 ((x) + 0x22430)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_PHYS(x)                                                 ((x) + 0x22430)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_OFFS                                                    (0x22430)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_RMSK                                                     0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_NODE_COUNT_5_BMSK                                        0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_NODE_COUNT_5_SHFT                                               16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_NODE_COUNT_4_BMSK                                            0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_7_NODE_COUNT_4_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_ADDR(x)                                                 ((x) + 0x22434)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_PHYS(x)                                                 ((x) + 0x22434)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_OFFS                                                    (0x22434)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_RMSK                                                     0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_NODE_COUNT_7_BMSK                                        0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_NODE_COUNT_7_SHFT                                               16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_NODE_COUNT_6_BMSK                                            0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_8_NODE_COUNT_6_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_ADDR(x)                                                 ((x) + 0x22438)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_PHYS(x)                                                 ((x) + 0x22438)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_OFFS                                                    (0x22438)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_RMSK                                                     0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_NODE_COUNT_9_BMSK                                        0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_NODE_COUNT_9_SHFT                                               16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_NODE_COUNT_8_BMSK                                            0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_9_NODE_COUNT_8_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_ADDR(x)                                                ((x) + 0x2243c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_PHYS(x)                                                ((x) + 0x2243c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_OFFS                                                   (0x2243c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_RMSK                                                    0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_NODE_COUNT_11_BMSK                                      0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_NODE_COUNT_11_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_NODE_COUNT_10_BMSK                                          0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_10_NODE_COUNT_10_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_ADDR(x)                                                ((x) + 0x22440)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_PHYS(x)                                                ((x) + 0x22440)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_OFFS                                                   (0x22440)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_RMSK                                                    0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_NODE_COUNT_13_BMSK                                      0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_NODE_COUNT_13_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_NODE_COUNT_12_BMSK                                          0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_11_NODE_COUNT_12_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_ADDR(x)                                                ((x) + 0x22444)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_PHYS(x)                                                ((x) + 0x22444)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_OFFS                                                   (0x22444)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_RMSK                                                    0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_NODE_COUNT_15_BMSK                                      0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_NODE_COUNT_15_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_NODE_COUNT_14_BMSK                                          0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_12_NODE_COUNT_14_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_ADDR(x)                                                ((x) + 0x22448)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_PHYS(x)                                                ((x) + 0x22448)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_OFFS                                                   (0x22448)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_RMSK                                                    0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_NODE_COUNT_17_BMSK                                      0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_NODE_COUNT_17_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_NODE_COUNT_16_BMSK                                          0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_13_NODE_COUNT_16_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_ADDR(x)                                                ((x) + 0x2244c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_PHYS(x)                                                ((x) + 0x2244c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_OFFS                                                   (0x2244c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_RMSK                                                    0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_NODE_COUNT_19_BMSK                                      0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_NODE_COUNT_19_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_NODE_COUNT_18_BMSK                                          0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_14_NODE_COUNT_18_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_ADDR(x)                                                ((x) + 0x22450)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_PHYS(x)                                                ((x) + 0x22450)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_OFFS                                                   (0x22450)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_RMSK                                                    0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_NODE_COUNT_21_BMSK                                      0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_NODE_COUNT_21_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_NODE_COUNT_20_BMSK                                          0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_15_NODE_COUNT_20_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_ADDR(x)                                                ((x) + 0x22454)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_PHYS(x)                                                ((x) + 0x22454)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_OFFS                                                   (0x22454)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_RMSK                                                    0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_NODE_COUNT_23_BMSK                                      0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_NODE_COUNT_23_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_NODE_COUNT_22_BMSK                                          0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_16_NODE_COUNT_22_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_ADDR(x)                                                ((x) + 0x22458)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_PHYS(x)                                                ((x) + 0x22458)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_OFFS                                                   (0x22458)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_RMSK                                                    0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_NODE_COUNT_25_BMSK                                      0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_NODE_COUNT_25_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_NODE_COUNT_24_BMSK                                          0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_17_NODE_COUNT_24_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_ADDR(x)                                                ((x) + 0x2245c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_PHYS(x)                                                ((x) + 0x2245c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_OFFS                                                   (0x2245c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_RMSK                                                    0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_NODE_COUNT_27_BMSK                                      0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_NODE_COUNT_27_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_NODE_COUNT_26_BMSK                                          0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_18_NODE_COUNT_26_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_ADDR(x)                                                ((x) + 0x22460)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_PHYS(x)                                                ((x) + 0x22460)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_OFFS                                                   (0x22460)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_RMSK                                                    0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_NODE_COUNT_29_BMSK                                      0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_NODE_COUNT_29_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_NODE_COUNT_28_BMSK                                          0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_19_NODE_COUNT_28_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_ADDR(x)                                                ((x) + 0x22464)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_PHYS(x)                                                ((x) + 0x22464)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_OFFS                                                   (0x22464)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_RMSK                                                    0xfff0fff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_NODE_COUNT_31_BMSK                                      0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_NODE_COUNT_31_SHFT                                             16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_NODE_COUNT_30_BMSK                                          0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_LLQ_STATUS_20_NODE_COUNT_30_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS0_ADDR(x)                                                      ((x) + 0x22470)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS0_PHYS(x)                                                      ((x) + 0x22470)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS0_OFFS                                                         (0x22470)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS0_RMSK                                                         0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS0_NAWT_RIFB_VLD_31_0_BMSK                                      0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS0_NAWT_RIFB_VLD_31_0_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS1_ADDR(x)                                                      ((x) + 0x22474)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS1_PHYS(x)                                                      ((x) + 0x22474)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS1_OFFS                                                         (0x22474)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS1_RMSK                                                         0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS1_NAWT_RIFB_VLD_63_32_BMSK                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS1_NAWT_RIFB_VLD_63_32_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_ADDR(x)                                                      ((x) + 0x22478)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_PHYS(x)                                                      ((x) + 0x22478)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_OFFS                                                         (0x22478)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_RMSK                                                         0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_NAWT_WIFB_VLD_11_0_BMSK                                      0xfff00000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_NAWT_WIFB_VLD_11_0_SHFT                                              20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_NAWT_HIFB_VLD_BMSK                                              0xf0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_NAWT_HIFB_VLD_SHFT                                                   16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_NAWT_RIFB_VLD_79_64_BMSK                                         0xffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS2_NAWT_RIFB_VLD_79_64_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_ADDR(x)                                                      ((x) + 0x2247c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_PHYS(x)                                                      ((x) + 0x2247c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_OFFS                                                         (0x2247c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_RMSK                                                          0xfffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_NAWT_FT_VLD_BMSK                                              0xff00000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_NAWT_FT_VLD_SHFT                                                     20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_NAWT_WIFB_VLD_31_12_BMSK                                        0xfffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_STATUS3_NAWT_WIFB_VLD_31_12_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_WRSC_STATUS_ADDR(x)                                                  ((x) + 0x22480)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_WRSC_STATUS_PHYS(x)                                                  ((x) + 0x22480)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_WRSC_STATUS_OFFS                                                     (0x22480)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_WRSC_STATUS_RMSK                                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_WRSC_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_WRSC_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_WRSC_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_WRSC_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_WRSC_STATUS_NAWT_WRSC_VLD_BMSK                                       0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NAWT_WRSC_STATUS_NAWT_WRSC_VLD_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_ADDR(x)                                                        ((x) + 0x22500)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_PHYS(x)                                                        ((x) + 0x22500)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_OFFS                                                           (0x22500)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_RMSK                                                                0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_ECC_ERR_LOG_CLK_EN_BMSK                                             0x800
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_ECC_ERR_LOG_CLK_EN_SHFT                                                11
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_ECC_ENCODER_CLK_EN_BMSK                                             0x400
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_ECC_ENCODER_CLK_EN_SHFT                                                10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_PIPE_STAGE_CLK_EN_BMSK                                              0x200
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_PIPE_STAGE_CLK_EN_SHFT                                                  9
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_NAWT_CLK_EN_BMSK                                                    0x100
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_NAWT_CLK_EN_SHFT                                                        8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_ET_CLK_EN_BMSK                                                       0x80
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_ET_CLK_EN_SHFT                                                          7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_RWIQ_CLK_EN_BMSK                                                     0x40
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_RWIQ_CLK_EN_SHFT                                                        6
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_HQ_CLK_EN_BMSK                                                       0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_HQ_CLK_EN_SHFT                                                          5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_FLOW_CTRL_CLK_EN_BMSK                                                0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_FLOW_CTRL_CLK_EN_SHFT                                                   4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_PROF_CLK_EN_BMSK                                                      0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_PROF_CLK_EN_SHFT                                                        3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_MRU_CLK_EN_BMSK                                                       0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_MRU_CLK_EN_SHFT                                                         2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_TAGRAM_CLK_EN_BMSK                                                    0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_TAGRAM_CLK_EN_SHFT                                                      1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_HKE_CLK_EN_BMSK                                                       0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CLK_EN_CFG_HKE_CLK_EN_SHFT                                                         0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_ADDR(x)                                                           ((x) + 0x22504)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_PHYS(x)                                                           ((x) + 0x22504)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_OFFS                                                              (0x22504)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_RMSK                                                                    0x33
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_RWIQ_DPG_CLK_EN_BMSK                                                    0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_RWIQ_DPG_CLK_EN_SHFT                                                       5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_RWIQ_DPG_EN_BMSK                                                        0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_RWIQ_DPG_EN_SHFT                                                           4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_HQ_DPG_CLK_EN_BMSK                                                       0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_HQ_DPG_CLK_EN_SHFT                                                         1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_HQ_DPG_EN_BMSK                                                           0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DPG_CFG_HQ_DPG_EN_SHFT                                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_ADDR(x)                                                        ((x) + 0x22510)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_PHYS(x)                                                        ((x) + 0x22510)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_OFFS                                                           (0x22510)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_RMSK                                                           0xffff01ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_ARB_DEBUG_SELECT_BMSK                                          0xffff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_ARB_DEBUG_SELECT_SHFT                                                  16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_DEBUG_SELECT_BMSK                                                   0x1ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DEBUG_CTRL_DEBUG_SELECT_SHFT                                                       0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_ADDR(x)                                                     ((x) + 0x22520)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_PHYS(x)                                                     ((x) + 0x22520)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_OFFS                                                        (0x22520)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_RMSK                                                            0x1f1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_SCT_DEACT_SELECT_BMSK                                           0x1f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_SCT_DEACT_SELECT_SHFT                                                8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_SCT_ACT_SELECT_BMSK                                               0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_HW_EVENT_CTRL_SCT_ACT_SELECT_SHFT                                                  0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_ADDR(x)                                                    ((x) + 0x22600)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_PHYS(x)                                                    ((x) + 0x22600)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_OFFS                                                       (0x22600)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_RMSK                                                            0x1ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_UIMAGE_RD_ALLOC_ON_NAWT_MATCH_BMSK                              0x100
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_UIMAGE_RD_ALLOC_ON_NAWT_MATCH_SHFT                                  8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_ALL_ACT_SCID_DEACT_BMSK                                          0x80
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_ALL_ACT_SCID_DEACT_SHFT                                             7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_GLOBAL_SCID_DEACT_BMSK                                           0x40
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_GLOBAL_SCID_DEACT_SHFT                                              6
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_PARTIAL_AT_HIT_BMSK                                              0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_PARTIAL_AT_HIT_SHFT                                                 5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_FC_CREDIT_UF_BMSK                                                0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_FC_CREDIT_UF_SHFT                                                   4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_SCT_ACT_ZERO_WAY_BMSK                                             0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_SCT_ACT_ZERO_WAY_SHFT                                               3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_HKE_BUSY_TRIGGER_BMSK                                             0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_HKE_BUSY_TRIGGER_SHFT                                               2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_ECC_ERR_BMSK                                                      0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_ECC_ERR_SHFT                                                        1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_FIFO_OVERFLOW_BMSK                                                0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_STATUS_FIFO_OVERFLOW_SHFT                                                  0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_ADDR(x)                                                     ((x) + 0x22604)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_PHYS(x)                                                     ((x) + 0x22604)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_OFFS                                                        (0x22604)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_RMSK                                                             0x1ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_UIMAGE_RD_ALLOC_ON_NAWT_MATCH_BMSK                               0x100
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_UIMAGE_RD_ALLOC_ON_NAWT_MATCH_SHFT                                   8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_ALL_ACT_SCID_DEACT_BMSK                                           0x80
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_ALL_ACT_SCID_DEACT_SHFT                                              7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_GLOBAL_SCID_DEACT_BMSK                                            0x40
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_GLOBAL_SCID_DEACT_SHFT                                               6
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_PARTIAL_AT_HIT_BMSK                                               0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_PARTIAL_AT_HIT_SHFT                                                  5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_FC_CREDIT_UF_BMSK                                                 0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_FC_CREDIT_UF_SHFT                                                    4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_SCT_ACT_ZERO_WAY_BMSK                                              0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_SCT_ACT_ZERO_WAY_SHFT                                                3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_HKE_BUSY_TRIGGER_BMSK                                              0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_HKE_BUSY_TRIGGER_SHFT                                                2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_ECC_ERR_BMSK                                                       0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_ECC_ERR_SHFT                                                         1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_FIFO_OVERFLOW_BMSK                                                 0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_CLEAR_FIFO_OVERFLOW_SHFT                                                   0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_ADDR(x)                                                       ((x) + 0x22608)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_PHYS(x)                                                       ((x) + 0x22608)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_OFFS                                                          (0x22608)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_RMSK                                                               0x1ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_UIMAGE_RD_ALLOC_ON_NAWT_MATCH_BMSK                                 0x100
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_UIMAGE_RD_ALLOC_ON_NAWT_MATCH_SHFT                                     8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_ALL_ACT_SCID_DEACT_BMSK                                             0x80
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_ALL_ACT_SCID_DEACT_SHFT                                                7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_GLOBAL_SCID_DEACT_BMSK                                              0x40
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_GLOBAL_SCID_DEACT_SHFT                                                 6
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_PARTIAL_AT_HIT_BMSK                                                 0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_PARTIAL_AT_HIT_SHFT                                                    5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_FC_CREDIT_UF_BMSK                                                   0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_FC_CREDIT_UF_SHFT                                                      4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_SCT_ACT_ZERO_WAY_BMSK                                                0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_SCT_ACT_ZERO_WAY_SHFT                                                  3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_HKE_BUSY_TRIGGER_BMSK                                                0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_HKE_BUSY_TRIGGER_SHFT                                                  2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_ECC_ERR_BMSK                                                         0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_ECC_ERR_SHFT                                                           1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_FIFO_OVERFLOW_BMSK                                                   0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DBG_EVT_FWD_FIFO_OVERFLOW_SHFT                                                     0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_ADDR(x)                                              ((x) + 0x2284c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_PHYS(x)                                              ((x) + 0x2284c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_OFFS                                                 (0x2284c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_RMSK                                                 0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_OVERRIDE_EN_BMSK                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI2RWE_OVERRIDE_CFG_OVERRIDE_EN_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_ADDR(x)                                                 ((x) + 0x22850)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_PHYS(x)                                                 ((x) + 0x22850)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_OFFS                                                    (0x22850)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_RMSK                                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_OVERRIDE_EN_BMSK                                        0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG0_OVERRIDE_EN_SHFT                                                 0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_ADDR(x)                                                 ((x) + 0x22854)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_PHYS(x)                                                 ((x) + 0x22854)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_OFFS                                                    (0x22854)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_RMSK                                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_OVERRIDE_VAL_BMSK                                       0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWI_OVERRIDE_CFG1_OVERRIDE_VAL_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_ADDR(x)                                                 ((x) + 0x22858)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_PHYS(x)                                                 ((x) + 0x22858)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_OFFS                                                    (0x22858)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_RMSK                                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_OVERRIDE_EN_BMSK                                        0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0_OVERRIDE_EN_SHFT                                                 0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_ADDR(x)                                                 ((x) + 0x2285c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_PHYS(x)                                                 ((x) + 0x2285c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_OFFS                                                    (0x2285c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_RMSK                                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_OVERRIDE_VAL_BMSK                                       0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG1_OVERRIDE_VAL_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_ADDR(x)                                                 ((x) + 0x22860)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_PHYS(x)                                                 ((x) + 0x22860)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_OFFS                                                    (0x22860)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_RMSK                                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_OVERRIDE_EN_BMSK                                        0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG0_OVERRIDE_EN_SHFT                                                 0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_ADDR(x)                                                 ((x) + 0x22864)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_PHYS(x)                                                 ((x) + 0x22864)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_OFFS                                                    (0x22864)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_RMSK                                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_OVERRIDE_VAL_BMSK                                       0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_EWD_OVERRIDE_CFG1_OVERRIDE_VAL_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_ADDR(x)                                       ((x) + 0x22868)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_PHYS(x)                                       ((x) + 0x22868)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_OFFS                                          (0x22868)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_RMSK                                          0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_OVERRIDE_EN_BMSK                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG0_OVERRIDE_EN_SHFT                                       0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_ADDR(x)                                       ((x) + 0x2286c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_PHYS(x)                                       ((x) + 0x2286c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_OFFS                                          (0x2286c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_RMSK                                          0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_OVERRIDE_VAL_BMSK                             0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRITE_THROUGH_OVERRIDE_CFG1_OVERRIDE_VAL_SHFT                                      0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_ADDR(x)                                  ((x) + 0x22870)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_PHYS(x)                                  ((x) + 0x22870)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_OFFS                                     (0x22870)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_RMSK                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_OVERRIDE_EN_BMSK                         0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0_OVERRIDE_EN_SHFT                                  0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_ADDR(x)                                  ((x) + 0x22874)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_PHYS(x)                                  ((x) + 0x22874)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_OFFS                                     (0x22874)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_RMSK                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_OVERRIDE_VAL_BMSK                        0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG1_OVERRIDE_VAL_SHFT                                 0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_ADDR(x)                                  ((x) + 0x22878)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_PHYS(x)                                  ((x) + 0x22878)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_OFFS                                     (0x22878)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_RMSK                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_OVERRIDE_EN_BMSK                         0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG0_OVERRIDE_EN_SHFT                                  0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_ADDR(x)                                  ((x) + 0x2287c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_PHYS(x)                                  ((x) + 0x2287c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_OFFS                                     (0x2287c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_RMSK                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_OVERRIDE_VAL_BMSK                        0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_NOALLOC_ON_MISS_OVERRIDE_CFG1_OVERRIDE_VAL_SHFT                                 0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_ADDR(x)                                              ((x) + 0x22880)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_PHYS(x)                                              ((x) + 0x22880)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_OFFS                                                 (0x22880)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_RMSK                                                 0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_OVERRIDE_EN_BMSK                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG0_OVERRIDE_EN_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_ADDR(x)                                              ((x) + 0x22884)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_PHYS(x)                                              ((x) + 0x22884)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_OFFS                                                 (0x22884)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_RMSK                                                 0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_OVERRIDE_VAL_BMSK                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_RD_GFO_OVERRIDE_CFG1_OVERRIDE_VAL_SHFT                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_ADDR(x)                                              ((x) + 0x22888)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_PHYS(x)                                              ((x) + 0x22888)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_OFFS                                                 (0x22888)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_RMSK                                                 0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_OVERRIDE_EN_BMSK                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG0_OVERRIDE_EN_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_ADDR(x)                                              ((x) + 0x2288c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_PHYS(x)                                              ((x) + 0x2288c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_OFFS                                                 (0x2288c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_RMSK                                                 0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_OVERRIDE_VAL_BMSK                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WR_GFO_OVERRIDE_CFG1_OVERRIDE_VAL_SHFT                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_ADDR(x)                                              ((x) + 0x22890)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_PHYS(x)                                              ((x) + 0x22890)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_OFFS                                                 (0x22890)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_RMSK                                                 0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_OVERRIDE_EN_BMSK                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_C_AS_NC_OVERRIDE_CFG_OVERRIDE_EN_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_ADDR(x)                                              ((x) + 0x22894)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_PHYS(x)                                              ((x) + 0x22894)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_OFFS                                                 (0x22894)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_RMSK                                                 0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_OVERRIDE_EN_BMSK                                     0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG_OVERRIDE_EN_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_ADDR(x)                                           ((x) + 0x228a0)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_PHYS(x)                                           ((x) + 0x228a0)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_OFFS                                              (0x228a0)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_OVERRIDE_EN_BMSK                                  0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG0_OVERRIDE_EN_SHFT                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_ADDR(x)                                           ((x) + 0x228a4)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_PHYS(x)                                           ((x) + 0x228a4)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_OFFS                                              (0x228a4)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_OVERRIDE_VAL_BMSK                                 0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WT_W_WRSC_OVERRIDE_CFG1_OVERRIDE_VAL_SHFT                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_ADDR(x)                                                         ((x) + 0x228b0)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_PHYS(x)                                                         ((x) + 0x228b0)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_OFFS                                                            (0x228b0)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_RMSK                                                            0x3f111f11
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_LPDDR5_BG_MODE_EN_BMSK                                 0x20000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_LPDDR5_BG_MODE_EN_SHFT                                         29
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_BG_MODE_BANK_SPREAD_TH_BMSK                            0x1f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_BG_MODE_BANK_SPREAD_TH_SHFT                                    24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_SCB_EN_ON_RD_CREDIT_OT_CNT_LT_THRSHLD_BMSK                   0x100000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_SCB_EN_ON_RD_CREDIT_OT_CNT_LT_THRSHLD_SHFT                         20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_FIFO_MODE_EN_BMSK                                         0x10000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_FIFO_MODE_EN_SHFT                                              16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_BANK_SPREAD_TH_BMSK                                        0x1f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_BANK_SPREAD_TH_SHFT                                             8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_OPT_RANK_SWITCH_LPDDR4_EN_BMSK                               0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_OPT_RANK_SWITCH_LPDDR4_EN_SHFT                                  4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_INIT_START_BMSK                                               0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG2_WRSC_LLQ_INIT_START_SHFT                                                 0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_ADDR(x)                                                         ((x) + 0x228b4)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_PHYS(x)                                                         ((x) + 0x228b4)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_OFFS                                                            (0x228b4)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_RMSK                                                               0x1f1f1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WIFB_PL_PROPAGATION_ON_WRSC_FULL_EN_BMSK                           0x10000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WIFB_PL_PROPAGATION_ON_WRSC_FULL_EN_SHFT                                16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_FLUSH_WR_HIT_ON_CLEAN_BMSK                                     0x8000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_FLUSH_WR_HIT_ON_CLEAN_SHFT                                         15
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_FLUSH_C_WR_ALLOC_BMSK                                          0x4000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_FLUSH_C_WR_ALLOC_SHFT                                              14
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_FLUSH_NC_WR_ALLOC_BMSK                                         0x2000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_FLUSH_NC_WR_ALLOC_SHFT                                             13
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_C_AS_NC_ON_FULL_BMSK                                           0x1000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_C_AS_NC_ON_FULL_SHFT                                               12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_LLQ_BANK_SPREAD_TH2_BMSK                                        0x1f0
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_LLQ_BANK_SPREAD_TH2_SHFT                                            4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_LLQ_FLUSH_DISABLE_BMSK                                            0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_WRSC_CFG3_WRSC_LLQ_FLUSH_DISABLE_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_ADDR(x)                                                  ((x) + 0x23000)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_PHYS(x)                                                  ((x) + 0x23000)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_OFFS                                                     (0x23000)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_RMSK                                                       0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_ACTIVE_WAY_VEC_BMSK                                        0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_0_ACTIVE_WAY_VEC_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_ADDR(x)                                                  ((x) + 0x23004)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_PHYS(x)                                                  ((x) + 0x23004)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_OFFS                                                     (0x23004)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_RMSK                                                            0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_UPDATE_TRIG_BMSK                                                0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_1_UPDATE_TRIG_SHFT                                                  0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_ADDR(x)                                                  ((x) + 0x23008)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_PHYS(x)                                                  ((x) + 0x23008)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_OFFS                                                     (0x23008)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_RMSK                                                       0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_ALLOC_WAY_VEC_BMSK                                         0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_UPDATE_2_ALLOC_WAY_VEC_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_STATUS_ADDR(x)                                                    ((x) + 0x2320c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_STATUS_PHYS(x)                                                    ((x) + 0x2320c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_STATUS_OFFS                                                       (0x2320c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_STATUS_RMSK                                                         0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_STATUS_PCB_ACT_VEC_BMSK                                             0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_STATUS_PCB_ACT_VEC_SHFT                                                    0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_PCB_ACT_STATUS_ADDR(x)                                             ((x) + 0x23210)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_PCB_ACT_STATUS_PHYS(x)                                             ((x) + 0x23210)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_PCB_ACT_STATUS_OFFS                                                (0x23210)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_PCB_ACT_STATUS_RMSK                                                  0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_PCB_ACT_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_PCB_ACT_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_PCB_ACT_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_PCB_ACT_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_PCB_ACT_STATUS_PCB_ACT_VEC_BMSK                                      0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_PCB_ACT_STATUS_PCB_ACT_VEC_SHFT                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS_ADDR(x)                                                    ((x) + 0x23214)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS_PHYS(x)                                                    ((x) + 0x23214)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS_OFFS                                                       (0x23214)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS_RMSK                                                         0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS_ACTIVE_WAY_VEC_BMSK                                          0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS_ACTIVE_WAY_VEC_SHFT                                                 0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_ACT_STATUS_ADDR(x)                                                   ((x) + 0x23218)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_ACT_STATUS_PHYS(x)                                                   ((x) + 0x23218)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_ACT_STATUS_OFFS                                                      (0x23218)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_ACT_STATUS_RMSK                                                      0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_ACT_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_ACT_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_ACT_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_ACT_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_ACT_STATUS_SCID_ACT_VEC_BMSK                                         0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_ACT_STATUS_SCID_ACT_VEC_SHFT                                                  0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PERSISTENT_PCB_ACT_STATUS_ADDR(x)                                         ((x) + 0x2321c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PERSISTENT_PCB_ACT_STATUS_PHYS(x)                                         ((x) + 0x2321c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PERSISTENT_PCB_ACT_STATUS_OFFS                                            (0x2321c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PERSISTENT_PCB_ACT_STATUS_RMSK                                              0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PERSISTENT_PCB_ACT_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PERSISTENT_PCB_ACT_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PERSISTENT_PCB_ACT_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PERSISTENT_PCB_ACT_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PERSISTENT_PCB_ACT_STATUS_PCB_ACT_VEC_BMSK                                  0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PERSISTENT_PCB_ACT_STATUS_PCB_ACT_VEC_SHFT                                         0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_ADDR(x)                                           ((x) + 0x23220)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_PHYS(x)                                           ((x) + 0x23220)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_OFFS                                              (0x23220)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_PCB1_DIRTY_LEVEL_BMSK                             0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_PCB1_DIRTY_LEVEL_SHFT                                     28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_PCB1_DIRTY_COUNT_BMSK                              0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_PCB1_DIRTY_COUNT_SHFT                                     16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_PCB0_DIRTY_LEVEL_BMSK                                 0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_PCB0_DIRTY_LEVEL_SHFT                                     12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_PCB0_DIRTY_COUNT_BMSK                                  0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS0_PCB0_DIRTY_COUNT_SHFT                                      0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_ADDR(x)                                           ((x) + 0x23224)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_PHYS(x)                                           ((x) + 0x23224)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_OFFS                                              (0x23224)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_PCB3_DIRTY_LEVEL_BMSK                             0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_PCB3_DIRTY_LEVEL_SHFT                                     28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_PCB3_DIRTY_COUNT_BMSK                              0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_PCB3_DIRTY_COUNT_SHFT                                     16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_PCB2_DIRTY_LEVEL_BMSK                                 0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_PCB2_DIRTY_LEVEL_SHFT                                     12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_PCB2_DIRTY_COUNT_BMSK                                  0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS1_PCB2_DIRTY_COUNT_SHFT                                      0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_ADDR(x)                                           ((x) + 0x23228)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_PHYS(x)                                           ((x) + 0x23228)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_OFFS                                              (0x23228)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_PCB5_DIRTY_LEVEL_BMSK                             0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_PCB5_DIRTY_LEVEL_SHFT                                     28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_PCB5_DIRTY_COUNT_BMSK                              0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_PCB5_DIRTY_COUNT_SHFT                                     16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_PCB4_DIRTY_LEVEL_BMSK                                 0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_PCB4_DIRTY_LEVEL_SHFT                                     12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_PCB4_DIRTY_COUNT_BMSK                                  0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS2_PCB4_DIRTY_COUNT_SHFT                                      0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_ADDR(x)                                           ((x) + 0x2322c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_PHYS(x)                                           ((x) + 0x2322c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_OFFS                                              (0x2322c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_PCB7_DIRTY_LEVEL_BMSK                             0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_PCB7_DIRTY_LEVEL_SHFT                                     28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_PCB7_DIRTY_COUNT_BMSK                              0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_PCB7_DIRTY_COUNT_SHFT                                     16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_PCB6_DIRTY_LEVEL_BMSK                                 0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_PCB6_DIRTY_LEVEL_SHFT                                     12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_PCB6_DIRTY_COUNT_BMSK                                  0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS3_PCB6_DIRTY_COUNT_SHFT                                      0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS1_ADDR(x)                                                   ((x) + 0x23230)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS1_PHYS(x)                                                   ((x) + 0x23230)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS1_OFFS                                                      (0x23230)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS1_RMSK                                                        0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS1_ALLOC_WAY_VEC_BMSK                                          0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ACT_WAY_STATUS1_ALLOC_WAY_VEC_SHFT                                                 0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_ADDR(x)                                           ((x) + 0x23240)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_PHYS(x)                                           ((x) + 0x23240)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_OFFS                                              (0x23240)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_PCB9_DIRTY_LEVEL_BMSK                             0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_PCB9_DIRTY_LEVEL_SHFT                                     28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_PCB9_DIRTY_COUNT_BMSK                              0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_PCB9_DIRTY_COUNT_SHFT                                     16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_PCB8_DIRTY_LEVEL_BMSK                                 0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_PCB8_DIRTY_LEVEL_SHFT                                     12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_PCB8_DIRTY_COUNT_BMSK                                  0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS4_PCB8_DIRTY_COUNT_SHFT                                      0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_ADDR(x)                                           ((x) + 0x23244)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_PHYS(x)                                           ((x) + 0x23244)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_OFFS                                              (0x23244)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_PCB11_DIRTY_LEVEL_BMSK                            0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_PCB11_DIRTY_LEVEL_SHFT                                    28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_PCB11_DIRTY_COUNT_BMSK                             0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_PCB11_DIRTY_COUNT_SHFT                                    16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_PCB10_DIRTY_LEVEL_BMSK                                0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_PCB10_DIRTY_LEVEL_SHFT                                    12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_PCB10_DIRTY_COUNT_BMSK                                 0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS5_PCB10_DIRTY_COUNT_SHFT                                     0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_ADDR(x)                                           ((x) + 0x23248)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_PHYS(x)                                           ((x) + 0x23248)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_OFFS                                              (0x23248)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_PCB13_DIRTY_LEVEL_BMSK                            0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_PCB13_DIRTY_LEVEL_SHFT                                    28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_PCB13_DIRTY_COUNT_BMSK                             0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_PCB13_DIRTY_COUNT_SHFT                                    16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_PCB12_DIRTY_LEVEL_BMSK                                0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_PCB12_DIRTY_LEVEL_SHFT                                    12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_PCB12_DIRTY_COUNT_BMSK                                 0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS6_PCB12_DIRTY_COUNT_SHFT                                     0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_ADDR(x)                                           ((x) + 0x2324c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_PHYS(x)                                           ((x) + 0x2324c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_OFFS                                              (0x2324c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_PCB15_DIRTY_LEVEL_BMSK                            0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_PCB15_DIRTY_LEVEL_SHFT                                    28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_PCB15_DIRTY_COUNT_BMSK                             0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_PCB15_DIRTY_COUNT_SHFT                                    16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_PCB14_DIRTY_LEVEL_BMSK                                0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_PCB14_DIRTY_LEVEL_SHFT                                    12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_PCB14_DIRTY_COUNT_BMSK                                 0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS7_PCB14_DIRTY_COUNT_SHFT                                     0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_ADDR(x)                                           ((x) + 0x23250)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_PHYS(x)                                           ((x) + 0x23250)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_OFFS                                              (0x23250)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_PCB17_DIRTY_LEVEL_BMSK                            0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_PCB17_DIRTY_LEVEL_SHFT                                    28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_PCB17_DIRTY_COUNT_BMSK                             0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_PCB17_DIRTY_COUNT_SHFT                                    16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_PCB16_DIRTY_LEVEL_BMSK                                0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_PCB16_DIRTY_LEVEL_SHFT                                    12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_PCB16_DIRTY_COUNT_BMSK                                 0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS8_PCB16_DIRTY_COUNT_SHFT                                     0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_ADDR(x)                                           ((x) + 0x23254)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_PHYS(x)                                           ((x) + 0x23254)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_OFFS                                              (0x23254)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_RMSK                                              0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_PCB19_DIRTY_LEVEL_BMSK                            0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_PCB19_DIRTY_LEVEL_SHFT                                    28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_PCB19_DIRTY_COUNT_BMSK                             0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_PCB19_DIRTY_COUNT_SHFT                                    16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_PCB18_DIRTY_LEVEL_BMSK                                0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_PCB18_DIRTY_LEVEL_SHFT                                    12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_PCB18_DIRTY_COUNT_BMSK                                 0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS9_PCB18_DIRTY_COUNT_SHFT                                     0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_ADDR(x)                                          ((x) + 0x23258)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_PHYS(x)                                          ((x) + 0x23258)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_OFFS                                             (0x23258)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_RMSK                                             0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_PCB21_DIRTY_LEVEL_BMSK                           0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_PCB21_DIRTY_LEVEL_SHFT                                   28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_PCB21_DIRTY_COUNT_BMSK                            0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_PCB21_DIRTY_COUNT_SHFT                                   16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_PCB20_DIRTY_LEVEL_BMSK                               0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_PCB20_DIRTY_LEVEL_SHFT                                   12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_PCB20_DIRTY_COUNT_BMSK                                0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS10_PCB20_DIRTY_COUNT_SHFT                                    0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_ADDR(x)                                          ((x) + 0x2325c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_PHYS(x)                                          ((x) + 0x2325c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_OFFS                                             (0x2325c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_RMSK                                             0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_PCB23_DIRTY_LEVEL_BMSK                           0xf0000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_PCB23_DIRTY_LEVEL_SHFT                                   28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_PCB23_DIRTY_COUNT_BMSK                            0xfff0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_PCB23_DIRTY_COUNT_SHFT                                   16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_PCB22_DIRTY_LEVEL_BMSK                               0xf000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_PCB22_DIRTY_LEVEL_SHFT                                   12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_PCB22_DIRTY_COUNT_BMSK                                0xfff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_DIRTY_COUNT_STATUS11_PCB22_DIRTY_COUNT_SHFT                                    0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_ADDR(x)                                                      ((x) + 0x23300)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_PHYS(x)                                                      ((x) + 0x23300)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_OFFS                                                         (0x23300)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_RMSK                                                         0x7f3ff3ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_INIT_PRIOLVL_BMSK                                            0x7f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_INIT_PRIOLVL_SHFT                                                    24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_SET_NDX_END_BMSK                                               0x3ff000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_SET_NDX_END_SHFT                                                     12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_SET_NDX_START_BMSK                                                0x3ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_0_SET_NDX_START_SHFT                                                    0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_ADDR(x)                                                      ((x) + 0x23304)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_PHYS(x)                                                      ((x) + 0x23304)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_OFFS                                                         (0x23304)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_RMSK                                                         0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_ALL_SETS_BMSK                                                0x80000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_ALL_SETS_SHFT                                                        31
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_DTY_VAL_BMSK                                                 0x40000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_DTY_VAL_SHFT                                                         30
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_VLD_VAL_BMSK                                                 0x20000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_VLD_VAL_SHFT                                                         29
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_PER_WAY_BMSK                                                 0x10000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_PER_WAY_SHFT                                                         28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_DRIE_EN_BMSK                                                  0x8000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_DRIE_EN_SHFT                                                         27
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_KEEP_WAY_OFF_BMSK                                             0x4000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_KEEP_WAY_OFF_SHFT                                                    26
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_INIT_NO_WALKER_BMSK                                           0x2000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_INIT_NO_WALKER_SHFT                                                  25
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_INIT_TRIG_BMSK                                                0x1000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_INIT_TRIG_SHFT                                                       24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_WAY_EN_VEC_BMSK                                                0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_CTRL_1_WAY_EN_VEC_SHFT                                                       0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_ADDR(x)                                                      ((x) + 0x23308)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_PHYS(x)                                                      ((x) + 0x23308)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_OFFS                                                         (0x23308)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_RMSK                                                                0x3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_DCI_BUSY_BMSK                                                       0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_DCI_BUSY_SHFT                                                         1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_DCI_DONE_BMSK                                                       0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CINIT_STATUS_DCI_DONE_SHFT                                                         0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_ADDR(x)                                                          ((x) + 0x2330c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_PHYS(x)                                                          ((x) + 0x2330c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_OFFS                                                             (0x2330c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_RMSK                                                             0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_DRIE_VAL_BMSK                                                    0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_DRIE_VAL_DRIE_VAL_SHFT                                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_ADDR(x)                                                     ((x) + 0x23310)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_PHYS(x)                                                     ((x) + 0x23310)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_OFFS                                                        (0x23310)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_RMSK                                                        0x7f3ff3ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_CLEAN_PRIOLVL_BMSK                                          0x7f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_CLEAN_PRIOLVL_SHFT                                                  24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_CLEAN_SET_NDX_END_BMSK                                        0x3ff000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_CLEAN_SET_NDX_END_SHFT                                              12
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_CLEAN_SET_NDX_START_BMSK                                         0x3ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_0_CLEAN_SET_NDX_START_SHFT                                             0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_ADDR(x)                                                     ((x) + 0x23314)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_PHYS(x)                                                     ((x) + 0x23314)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_OFFS                                                        (0x23314)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_RMSK                                                          0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_CLEAN_WAY_VEC_BMSK                                            0xffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_1_CLEAN_WAY_VEC_SHFT                                                   0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_ADDR(x)                                                     ((x) + 0x23318)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_PHYS(x)                                                     ((x) + 0x23318)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_OFFS                                                        (0x23318)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_RMSK                                                              0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_DCC_ABORT_BUSY_BMSK                                               0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_DCC_ABORT_BUSY_SHFT                                                  4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_DCC_ABORT_DONE_BMSK                                                0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_DCC_ABORT_DONE_SHFT                                                  3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_DCC_WAIT_BMSK                                                      0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_DCC_WAIT_SHFT                                                        2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_DCC_BUSY_BMSK                                                      0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_DCC_BUSY_SHFT                                                        1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_DCC_DONE_BMSK                                                      0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_STATUS_DCC_DONE_SHFT                                                        0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_2_ADDR(x)                                                     ((x) + 0x2331c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_2_PHYS(x)                                                     ((x) + 0x2331c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_2_OFFS                                                        (0x2331c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_2_RMSK                                                               0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_2_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_2_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_2_ABORT_BMSK                                                         0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_2_ABORT_SHFT                                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_ADDR(x)                                                     ((x) + 0x23320)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_PHYS(x)                                                     ((x) + 0x23320)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_OFFS                                                        (0x23320)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_RMSK                                                        0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_SCID_FLUSH_VEC_BMSK                                         0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_3_SCID_FLUSH_VEC_SHFT                                                  0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_ADDR(x)                                                     ((x) + 0x23324)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_PHYS(x)                                                     ((x) + 0x23324)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_OFFS                                                        (0x23324)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_RMSK                                                           0x101ff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_CLEAN_TRIG_BMSK                                                0x10000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_CLEAN_TRIG_SHFT                                                     16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_KEEP_WAY_ON_BMSK                                                 0x100
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_KEEP_WAY_ON_SHFT                                                     8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_OP_CLEAN_BMSK                                                     0x80
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_OP_CLEAN_SHFT                                                        7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_OP_PXI_BMSK                                                       0x40
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_OP_PXI_SHFT                                                          6
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_PER_WAY_BMSK                                                      0x20
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_PER_WAY_SHFT                                                         5
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_ALL_SETS_BMSK                                                     0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_ALL_SETS_SHFT                                                        4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_PXI_REPEAT_BMSK                                                    0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_PXI_REPEAT_SHFT                                                      3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_PXI_SIDEBAND_TRIG_EN_BMSK                                          0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_PXI_SIDEBAND_TRIG_EN_SHFT                                            2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_SCID_FILTER_EN_BMSK                                                0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_SCID_FILTER_EN_SHFT                                                  1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_PXI_FLUSH_ORDER_EN_BMSK                                            0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_CFLUSH_CTRL_4_PXI_FLUSH_ORDER_EN_SHFT                                              0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_ADDR(x)                                                ((x) + 0x2358c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_PHYS(x)                                                ((x) + 0x2358c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_OFFS                                                   (0x2358c)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_RMSK                                                         0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_FLUSH_ABORT_DONE_BMSK                                        0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_FLUSH_ABORT_DONE_SHFT                                           4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_FLUSH_DONE_BMSK                                               0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_FLUSH_DONE_SHFT                                                 3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_INIT_DONE_BMSK                                                0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_INIT_DONE_SHFT                                                  2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_DB_ECC_ERROR_BMSK                                             0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_DB_ECC_ERROR_SHFT                                               1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_SB_ECC_ERROR_BMSK                                             0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_STATUS_SB_ECC_ERROR_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_ADDR(x)                                                 ((x) + 0x23590)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_PHYS(x)                                                 ((x) + 0x23590)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_OFFS                                                    (0x23590)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_RMSK                                                          0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_FLUSH_ABORT_DONE_BMSK                                         0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_FLUSH_ABORT_DONE_SHFT                                            4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_FLUSH_DONE_BMSK                                                0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_FLUSH_DONE_SHFT                                                  3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_INIT_DONE_BMSK                                                 0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_INIT_DONE_SHFT                                                   2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_DB_ECC_ERROR_BMSK                                              0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_DB_ECC_ERROR_SHFT                                                1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_SB_ECC_ERROR_BMSK                                              0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_CLEAR_SB_ECC_ERROR_SHFT                                                0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_ADDR(x)                                                ((x) + 0x23594)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_PHYS(x)                                                ((x) + 0x23594)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_OFFS                                                   (0x23594)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_RMSK                                                         0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_FLUSH_ABORT_DONE_BMSK                                        0x10
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_FLUSH_ABORT_DONE_SHFT                                           4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_FLUSH_DONE_BMSK                                               0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_FLUSH_DONE_SHFT                                                 3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_INIT_DONE_BMSK                                                0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_INIT_DONE_SHFT                                                  2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_DB_ECC_ERROR_BMSK                                             0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_DB_ECC_ERROR_SHFT                                               1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_SB_ECC_ERROR_BMSK                                             0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_INTERRUPT_1_ENABLE_SB_ECC_ERROR_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_ADDR(x)                                                ((x) + 0x24000)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_PHYS(x)                                                ((x) + 0x24000)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_OFFS                                                   (0x24000)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_RMSK                                                   0x1f1f000e
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_VICTIM_SCID_MASK_BMSK                                  0x1f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_VICTIM_SCID_MASK_SHFT                                          24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_VICTIM_SCID_MATCH_BMSK                                   0x1f0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_VICTIM_SCID_MATCH_SHFT                                         16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_VICTIM_SCID_INV_MATCH_BMSK                                    0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_VICTIM_SCID_INV_MATCH_SHFT                                      3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_PROFTAG_INV_MATCH_BMSK                                        0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_PROFTAG_INV_MATCH_SHFT                                          2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_WAY_ID_INV_MATCH_BMSK                                         0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG0_WAY_ID_INV_MATCH_SHFT                                           1

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_ADDR(x)                                                ((x) + 0x24004)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_PHYS(x)                                                ((x) + 0x24004)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_OFFS                                                   (0x24004)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_RMSK                                                   0x33001f1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_PROFTAG_MASK_BMSK                                      0x30000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_PROFTAG_MASK_SHFT                                              28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_PROFTAG_MATCH_BMSK                                      0x3000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_PROFTAG_MATCH_SHFT                                             24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_WAY_ID_MASK_BMSK                                           0x1f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_WAY_ID_MASK_SHFT                                                8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_WAY_ID_MATCH_BMSK                                            0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG1_WAY_ID_MATCH_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_ADDR(x)                                                ((x) + 0x24008)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_PHYS(x)                                                ((x) + 0x24008)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_OFFS                                                   (0x24008)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_RMSK                                                   0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_SCID_MULTI_MATCH_BMSK                                  0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_0_CFG2_SCID_MULTI_MATCH_SHFT                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_ADDR(x)                                                ((x) + 0x24010)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_PHYS(x)                                                ((x) + 0x24010)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_OFFS                                                   (0x24010)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_RMSK                                                   0x1f1f000e
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_VICTIM_SCID_MASK_BMSK                                  0x1f000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_VICTIM_SCID_MASK_SHFT                                          24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_VICTIM_SCID_MATCH_BMSK                                   0x1f0000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_VICTIM_SCID_MATCH_SHFT                                         16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_VICTIM_SCID_INV_MATCH_BMSK                                    0x8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_VICTIM_SCID_INV_MATCH_SHFT                                      3
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_PROFTAG_INV_MATCH_BMSK                                        0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_PROFTAG_INV_MATCH_SHFT                                          2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_WAY_ID_INV_MATCH_BMSK                                         0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG0_WAY_ID_INV_MATCH_SHFT                                           1

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_ADDR(x)                                                ((x) + 0x24014)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_PHYS(x)                                                ((x) + 0x24014)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_OFFS                                                   (0x24014)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_RMSK                                                   0x33001f1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_PROFTAG_MASK_BMSK                                      0x30000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_PROFTAG_MASK_SHFT                                              28
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_PROFTAG_MATCH_BMSK                                      0x3000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_PROFTAG_MATCH_SHFT                                             24
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_WAY_ID_MASK_BMSK                                           0x1f00
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_WAY_ID_MASK_SHFT                                                8
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_WAY_ID_MATCH_BMSK                                            0x1f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG1_WAY_ID_MATCH_SHFT                                               0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_ADDR(x)                                                ((x) + 0x24018)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_PHYS(x)                                                ((x) + 0x24018)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_OFFS                                                   (0x24018)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_RMSK                                                   0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_SCID_MULTI_MATCH_BMSK                                  0xffffffff
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_FILTER_1_CFG2_SCID_MULTI_MATCH_SHFT                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_ADDR(base,n)                                             ((base) + 0X24020 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_PHYS(base,n)                                             ((base) + 0X24020 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_OFFS(n)                                                  (0X24020 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_RMSK                                                     0x8001007f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_MAXn                                                             15
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_OUTI(base,n,val)        \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_ADDR(base,n),val)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_ADDR(base,n),mask,val,HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_INI(base,n))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_FILTER_EN_BMSK                                           0x80000000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_FILTER_EN_SHFT                                                   31
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_FILTER_SEL_BMSK                                             0x10000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_FILTER_SEL_SHFT                                                  16
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_EVENT_SEL_BMSK                                                 0x7f
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_PROF_EVENT_n_CFG_EVENT_SEL_SHFT                                                    0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_STATUS_ADDR(x)                                        ((x) + 0x25000)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_STATUS_PHYS(x)                                        ((x) + 0x25000)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_STATUS_OFFS                                           (0x25000)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_STATUS_RMSK                                                  0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_STATUS_ISLAND_OK_BMSK                                        0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_STATUS_ISLAND_OK_SHFT                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_ADDR(base,n)                                           ((base) + 0X25000 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_PHYS(base,n)                                           ((base) + 0X25000 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_OFFS(n)                                                (0X25000 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_RMSK                                                      0x10000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_MAXn                                                            7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_OUTI(base,n,val)        \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_ADDR(base,n),val)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_ADDR(base,n),mask,val,HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_INI(base,n))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_CLEAN_TRIG_BMSK                                           0x10000
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_CTRL_1_CLEAN_TRIG_SHFT                                                16

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_CLEAR_ADDR(x)                                         ((x) + 0x25004)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_CLEAR_PHYS(x)                                         ((x) + 0x25004)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_CLEAR_OFFS                                            (0x25004)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_CLEAR_RMSK                                                   0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_CLEAR_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_CLEAR_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_CLEAR_ISLAND_OK_BMSK                                         0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_CLEAR_ISLAND_OK_SHFT                                           0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_ADDR(x)                                        ((x) + 0x25008)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_PHYS(x)                                        ((x) + 0x25008)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_OFFS                                           (0x25008)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_RMSK                                                  0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_ISLAND_OK_BMSK                                        0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_OK_INTERRUPT_ENABLE_ISLAND_OK_SHFT                                          0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_STATUS_ADDR(x)                                      ((x) + 0x25010)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_STATUS_PHYS(x)                                      ((x) + 0x25010)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_STATUS_OFFS                                         (0x25010)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_STATUS_RMSK                                                0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_STATUS_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_STATUS_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_STATUS_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_STATUS_ISLAND_EXIT_BMSK                                    0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_STATUS_ISLAND_EXIT_SHFT                                      0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_ADDR(base,n)                                           ((base) + 0X25010 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_PHYS(base,n)                                           ((base) + 0X25010 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_OFFS(n)                                                (0X25010 + (0x1000*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_RMSK                                                          0x7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_MAXn                                                            7
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_DCC_WAIT_BMSK                                                 0x4
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_DCC_WAIT_SHFT                                                   2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_DCC_BUSY_BMSK                                                 0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_DCC_BUSY_SHFT                                                   1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_DCC_DONE_BMSK                                                 0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_VZ_n_CFLUSH_STATUS_DCC_DONE_SHFT                                                   0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_CLEAR_ADDR(x)                                       ((x) + 0x25014)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_CLEAR_PHYS(x)                                       ((x) + 0x25014)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_CLEAR_OFFS                                          (0x25014)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_CLEAR_RMSK                                                 0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_CLEAR_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_CLEAR_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_CLEAR_ISLAND_EXIT_BMSK                                     0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_CLEAR_ISLAND_EXIT_SHFT                                       0

#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_ADDR(x)                                      ((x) + 0x25018)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_PHYS(x)                                      ((x) + 0x25018)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_OFFS                                         (0x25018)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_RMSK                                                0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_ISLAND_EXIT_BMSK                                    0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_TRP_ISLAND_EXIT_INTERRUPT_ENABLE_ISLAND_EXIT_SHFT                                      0

/*----------------------------------------------------------------------------
 * MODULE: LLCC_BROADCAST_ORLPI_SHARED
 *--------------------------------------------------------------------------*/

#define LLCC_BROADCAST_ORLPI_SHARED_REG_BASE                                            (DDR_SS_BASE            + 0x01874000)
#define LLCC_BROADCAST_ORLPI_SHARED_REG_BASE_SIZE                                       0x1000
#define LLCC_BROADCAST_ORLPI_SHARED_REG_BASE_USED                                       0x17c
#define LLCC_BROADCAST_ORLPI_SHARED_REG_BASE_PHYS                                       (DDR_SS_BASE_PHYS + 0x01874000)
#define LLCC_BROADCAST_ORLPI_SHARED_REG_BASE_OFFS                                       0x01874000

#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_ADDR(x)                 ((x) + 0x0)
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_PHYS(x)                 ((x) + 0x0)
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_OFFS                    (0x0)
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_RMSK                      0x1ffff8
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_IN(x)            \
                in_dword(HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_ADDR(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_INM(x, m)            \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_ADDR(x), m)
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_OUT(x, v)            \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_ADDR(x),v)
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_ADDR(x),m,v,HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_IN(x))
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_SIZE_BMSK                 0x1f0000
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_SIZE_SHFT                       16
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_BASE_ADDR_BMSK              0xfff8
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG_BASE_ADDR_SHFT                   3

#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_ADDR(base,n)               ((base) + 0X100 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_PHYS(base,n)               ((base) + 0X100 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_OFFS(n)                    (0X100 + (0x4*(n)))
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_RMSK                              0x3
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_MAXn                               31
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_INI(base,n)                \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_ADDR(base,n), HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_RMSK)
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_INMI(base,n,mask)        \
                in_dword_masked(HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_ADDR(base,n), mask)
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_OUTI(base,n,val)        \
                out_dword(HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_ADDR(base,n),val)
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_ADDR(base,n),mask,val,HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_INI(base,n))
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_SCID_TYPE_BMSK                    0x3
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_SCID_TYPE_SHFT                      0
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_SCID_TYPE_ACTIVE_FVAL             0x0
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_SCID_TYPE_GLOBAL_FVAL             0x1
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_SCID_TYPE_PERSISTENT_FVAL         0x2
#define HWIO_LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG_SCID_TYPE_ISLAND_FVAL             0x3


#endif /* __LLCC_TRP_REG_OR_KAILUA1_H__ */
