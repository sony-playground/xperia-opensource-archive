#ifndef __BCM_HWIO_H__
#define __BCM_HWIO_H__
/*
===========================================================================
*/
/**
  @file bcm_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    .*RPMH_BCM.*

  'Exclude' filters applied: CD0_CPn[RPMH] CD1_CPn[RPMH] CD2_CPn[RPMH] CD3_CPn[RPMH] CD4_CPn[RPMH] CD5_CPn[RPMH] CD6_CPn[RPMH] CD7_CPn[RPMH] CD8_CPn[RPMH] CD9_CPn[RPMH] CD10_CPn[RPMH] CD11_CPn[RPMH] CD12_CPn[RPMH] CD13_CPn[RPMH] CD14_CPn[RPMH] CD15_CPn[RPMH] 

  Generation parameters: 
  { 'check-for-overlaps': True,
    'check-sizes': True,
    'create-array': [ [ 'CD_TH_CD0_CPn',
                        { 'arg': 'm',
                          'arg_pos': 8,
                          'array_offset': 64,
                          'max_index': 15}],
                      [ 'TCS_CFG_VOTE_DATA_CD0_CPn',
                        { 'arg': 'm',
                          'arg_pos': 20,
                          'array_offset': 64,
                          'max_index': 15}]],
    'filename': 'bcm_hwio.h',
    'header': '\n#include <HALhwio.h>\n#include <msmhwiobase.h>\n',
    'ignore-prefixes': True,
    'map-type': 'physical',
    'module-filter-exclude': { 'RPMH': [ 'CD0_CPn',
                                         'CD1_CPn',
                                         'CD2_CPn',
                                         'CD3_CPn',
                                         'CD4_CPn',
                                         'CD5_CPn',
                                         'CD6_CPn',
                                         'CD7_CPn',
                                         'CD8_CPn',
                                         'CD9_CPn',
                                         'CD10_CPn',
                                         'CD11_CPn',
                                         'CD12_CPn',
                                         'CD13_CPn',
                                         'CD14_CPn',
                                         'CD15_CPn']},
    'modules': ['.*RPMH_BCM.*'],
    'trailer': '\n'
               '#define '
               'HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d)                                                   '
               '(BCM_VOTETABLE_REG_BASE      + 0x00000000 + 0x10000 * (r) + 0x4 '
               '* (d))\n'
               '#define '
               'HWIO_VOTETABLE_DRVr_NDd_RMSK                                                        '
               '0xefffffff\n'
               '#define '
               'HWIO_VOTETABLE_DRVr_NDd_MAXd                                                                '
               '63\n'
               '#define HWIO_VOTETABLE_DRVr_NDd_INI2(r,d)        \\\n'
               '        in_dword_masked(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d), '
               'HWIO_VOTETABLE_DRVr_NDd_RMSK)\n'
               '#define HWIO_VOTETABLE_DRVr_NDd_INMI2(r,d,mask)    \\\n'
               '        in_dword_masked(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d), '
               'mask)\n'
               '#define HWIO_VOTETABLE_DRVr_NDd_OUTI2(r,d,val)    \\\n'
               '        out_dword(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d),val)\n'
               '#define HWIO_VOTETABLE_DRVr_NDd_OUTMI2(r,d,mask,val) \\\n'
               '        '
               'out_dword_masked_ns(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d),mask,val,HWIO_VOTETABLE_DRVr_NDd_INI2(r,d))\n'}
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

  $Header: //components/dev/core.boot/6.0/aravapal.core.boot.6.0.tip_dev/QcomPkg/SocPkg/Clarence/Library/ClockTargetLib/image/Loader/HALClkBCMHWIO.h#1 $
  $DateTime: 2022/04/30 21:50:34 $
  $Author: aravapal $

  ===========================================================================
*/


#include <HALhwio.h>
#include <msmhwiobase.h>


/*----------------------------------------------------------------------------
 * MODULE: RPMH_BCM_BCM_TOP
 *--------------------------------------------------------------------------*/

#define RPMH_BCM_BCM_TOP_REG_BASE (AOSS_BASE      + 0x00a00000)
#define RPMH_BCM_BCM_TOP_REG_BASE_SIZE 0x200000
#define RPMH_BCM_BCM_TOP_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_VOTETABLE
 *--------------------------------------------------------------------------*/

#define BCM_VOTETABLE_REG_BASE                                                              (AOSS_BASE      + 0x00a00000)
#define BCM_VOTETABLE_REG_BASE_SIZE                                                         0x100000
#define BCM_VOTETABLE_REG_BASE_USED                                                         0xd007c

#define HWIO_VOTETABLE_DRV0_ND0_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00000000)
#define HWIO_VOTETABLE_DRV0_ND0_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV0_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND0_ADDR)
#define HWIO_VOTETABLE_DRV0_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND0_IN)
#define HWIO_VOTETABLE_DRV0_ND0_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV0_ND0_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV0_ND0_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV0_ND0_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV0_ND0_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV0_ND0_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV0_ND0_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV0_ND0_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV0_ND0_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV0_ND0_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV0_ND1_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00000004)
#define HWIO_VOTETABLE_DRV0_ND1_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV0_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND1_ADDR)
#define HWIO_VOTETABLE_DRV0_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND1_IN)
#define HWIO_VOTETABLE_DRV0_ND1_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV0_ND1_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV0_ND1_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV0_ND1_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV0_ND1_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV0_ND1_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV0_ND1_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV0_ND1_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV0_ND1_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV0_ND1_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV0_ND2_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00000008)
#define HWIO_VOTETABLE_DRV0_ND2_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV0_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND2_ADDR)
#define HWIO_VOTETABLE_DRV0_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND2_IN)
#define HWIO_VOTETABLE_DRV0_ND2_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV0_ND2_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV0_ND2_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV0_ND2_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV0_ND2_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV0_ND2_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV0_ND2_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV0_ND2_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV0_ND2_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV0_ND2_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV0_ND3_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x0000000c)
#define HWIO_VOTETABLE_DRV0_ND3_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV0_ND3_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND3_ADDR)
#define HWIO_VOTETABLE_DRV0_ND3_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND3_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND3_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND3_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND3_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND3_IN)
#define HWIO_VOTETABLE_DRV0_ND3_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV0_ND3_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV0_ND3_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV0_ND3_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV0_ND3_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV0_ND3_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV0_ND3_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV0_ND3_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV0_ND3_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV0_ND3_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV0_ND4_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00000010)
#define HWIO_VOTETABLE_DRV0_ND4_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV0_ND4_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND4_ADDR)
#define HWIO_VOTETABLE_DRV0_ND4_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND4_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND4_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND4_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND4_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND4_IN)
#define HWIO_VOTETABLE_DRV0_ND4_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV0_ND4_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV0_ND4_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV0_ND4_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV0_ND4_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV0_ND4_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV0_ND4_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV0_ND4_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV0_ND4_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV0_ND4_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV0_ND5_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00000014)
#define HWIO_VOTETABLE_DRV0_ND5_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV0_ND5_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND5_ADDR)
#define HWIO_VOTETABLE_DRV0_ND5_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND5_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND5_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND5_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND5_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND5_IN)
#define HWIO_VOTETABLE_DRV0_ND5_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV0_ND5_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV0_ND5_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV0_ND5_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV0_ND5_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV0_ND5_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV0_ND5_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV0_ND5_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV0_ND5_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV0_ND5_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV0_ND6_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00000018)
#define HWIO_VOTETABLE_DRV0_ND6_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV0_ND6_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND6_ADDR)
#define HWIO_VOTETABLE_DRV0_ND6_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND6_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND6_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND6_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND6_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND6_IN)
#define HWIO_VOTETABLE_DRV0_ND6_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV0_ND6_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV0_ND6_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV0_ND6_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV0_ND6_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV0_ND6_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV0_ND6_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV0_ND6_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV0_ND6_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV0_ND6_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV0_ND10_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000028)
#define HWIO_VOTETABLE_DRV0_ND10_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND10_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND10_ADDR)
#define HWIO_VOTETABLE_DRV0_ND10_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND10_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND10_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND10_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND10_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND10_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND10_IN)
#define HWIO_VOTETABLE_DRV0_ND10_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND10_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND10_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND10_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND10_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND10_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND10_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND10_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND10_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND10_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND11_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0000002c)
#define HWIO_VOTETABLE_DRV0_ND11_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND11_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND11_ADDR)
#define HWIO_VOTETABLE_DRV0_ND11_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND11_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND11_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND11_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND11_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND11_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND11_IN)
#define HWIO_VOTETABLE_DRV0_ND11_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND11_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND11_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND11_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND11_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND11_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND11_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND11_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND11_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND11_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND12_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000030)
#define HWIO_VOTETABLE_DRV0_ND12_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND12_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND12_ADDR)
#define HWIO_VOTETABLE_DRV0_ND12_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND12_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND12_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND12_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND12_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND12_IN)
#define HWIO_VOTETABLE_DRV0_ND12_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND12_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND12_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND12_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND12_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND12_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND12_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND12_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND12_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND12_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND13_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000034)
#define HWIO_VOTETABLE_DRV0_ND13_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND13_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND13_ADDR)
#define HWIO_VOTETABLE_DRV0_ND13_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND13_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND13_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND13_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND13_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND13_IN)
#define HWIO_VOTETABLE_DRV0_ND13_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND13_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND13_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND13_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND13_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND13_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND13_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND13_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND13_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND13_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND14_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000038)
#define HWIO_VOTETABLE_DRV0_ND14_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND14_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND14_ADDR)
#define HWIO_VOTETABLE_DRV0_ND14_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND14_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND14_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND14_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND14_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND14_IN)
#define HWIO_VOTETABLE_DRV0_ND14_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND14_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND14_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND14_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND14_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND14_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND14_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND14_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND14_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND14_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND15_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0000003c)
#define HWIO_VOTETABLE_DRV0_ND15_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND15_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND15_ADDR)
#define HWIO_VOTETABLE_DRV0_ND15_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND15_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND15_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND15_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND15_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND15_IN)
#define HWIO_VOTETABLE_DRV0_ND15_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND15_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND15_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND15_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND15_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND15_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND15_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND15_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND15_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND15_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND16_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000040)
#define HWIO_VOTETABLE_DRV0_ND16_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND16_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND16_ADDR)
#define HWIO_VOTETABLE_DRV0_ND16_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND16_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND16_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND16_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND16_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND16_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND16_IN)
#define HWIO_VOTETABLE_DRV0_ND16_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND16_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND16_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND16_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND16_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND16_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND16_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND16_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND16_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND16_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND17_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000044)
#define HWIO_VOTETABLE_DRV0_ND17_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND17_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND17_ADDR)
#define HWIO_VOTETABLE_DRV0_ND17_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND17_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND17_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND17_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND17_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND17_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND17_IN)
#define HWIO_VOTETABLE_DRV0_ND17_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND17_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND17_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND17_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND17_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND17_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND17_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND17_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND17_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND17_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND18_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000048)
#define HWIO_VOTETABLE_DRV0_ND18_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND18_ADDR)
#define HWIO_VOTETABLE_DRV0_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND18_IN)
#define HWIO_VOTETABLE_DRV0_ND18_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND18_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND18_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND18_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND18_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND18_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND18_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND18_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND18_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND18_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND19_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0000004c)
#define HWIO_VOTETABLE_DRV0_ND19_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND19_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND19_ADDR)
#define HWIO_VOTETABLE_DRV0_ND19_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND19_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND19_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND19_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND19_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND19_IN)
#define HWIO_VOTETABLE_DRV0_ND19_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND19_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND19_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND19_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND19_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND19_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND19_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND19_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND19_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND19_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND20_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000050)
#define HWIO_VOTETABLE_DRV0_ND20_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND20_ADDR)
#define HWIO_VOTETABLE_DRV0_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND20_IN)
#define HWIO_VOTETABLE_DRV0_ND20_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND20_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND20_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND20_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND20_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND20_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND20_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND20_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND20_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND20_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND21_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000054)
#define HWIO_VOTETABLE_DRV0_ND21_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND21_ADDR)
#define HWIO_VOTETABLE_DRV0_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND21_IN)
#define HWIO_VOTETABLE_DRV0_ND21_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND21_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND21_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND21_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND21_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND21_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND21_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND21_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND21_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND21_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND22_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000058)
#define HWIO_VOTETABLE_DRV0_ND22_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND22_ADDR)
#define HWIO_VOTETABLE_DRV0_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND22_IN)
#define HWIO_VOTETABLE_DRV0_ND22_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND22_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND22_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND22_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND22_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND22_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND22_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND22_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND22_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND22_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND23_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0000005c)
#define HWIO_VOTETABLE_DRV0_ND23_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND23_ADDR)
#define HWIO_VOTETABLE_DRV0_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND23_IN)
#define HWIO_VOTETABLE_DRV0_ND23_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND23_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND23_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND23_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND23_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND23_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND23_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND23_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND23_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND23_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND24_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000060)
#define HWIO_VOTETABLE_DRV0_ND24_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND24_ADDR)
#define HWIO_VOTETABLE_DRV0_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND24_IN)
#define HWIO_VOTETABLE_DRV0_ND24_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND24_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND24_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND24_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND24_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND24_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND24_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND24_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND24_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND24_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND25_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000064)
#define HWIO_VOTETABLE_DRV0_ND25_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND25_ADDR)
#define HWIO_VOTETABLE_DRV0_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND25_IN)
#define HWIO_VOTETABLE_DRV0_ND25_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND25_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND25_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND25_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND25_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND25_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND25_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND25_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND25_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND25_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND26_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000068)
#define HWIO_VOTETABLE_DRV0_ND26_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND26_ADDR)
#define HWIO_VOTETABLE_DRV0_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND26_IN)
#define HWIO_VOTETABLE_DRV0_ND26_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND26_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND26_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND26_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND26_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND26_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND26_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND26_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND26_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND26_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND27_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0000006c)
#define HWIO_VOTETABLE_DRV0_ND27_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND27_ADDR)
#define HWIO_VOTETABLE_DRV0_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND27_IN)
#define HWIO_VOTETABLE_DRV0_ND27_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND27_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND27_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND27_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND27_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND27_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND27_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND27_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND27_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND27_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND30_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00000078)
#define HWIO_VOTETABLE_DRV0_ND30_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND30_ADDR)
#define HWIO_VOTETABLE_DRV0_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND30_IN)
#define HWIO_VOTETABLE_DRV0_ND30_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND30_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND30_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND30_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND30_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND30_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND30_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND30_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND30_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND30_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV0_ND31_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0000007c)
#define HWIO_VOTETABLE_DRV0_ND31_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV0_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV0_ND31_ADDR)
#define HWIO_VOTETABLE_DRV0_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV0_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV0_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV0_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV0_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV0_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV0_ND31_IN)
#define HWIO_VOTETABLE_DRV0_ND31_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV0_ND31_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV0_ND31_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV0_ND31_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV0_ND31_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV0_ND31_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV0_ND31_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV0_ND31_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV0_ND31_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV0_ND31_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND0_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00020000)
#define HWIO_VOTETABLE_DRV2_ND0_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV2_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND0_ADDR)
#define HWIO_VOTETABLE_DRV2_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND0_IN)
#define HWIO_VOTETABLE_DRV2_ND0_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV2_ND0_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV2_ND0_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV2_ND0_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV2_ND0_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV2_ND0_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV2_ND0_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV2_ND0_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV2_ND0_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV2_ND0_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV2_ND1_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00020004)
#define HWIO_VOTETABLE_DRV2_ND1_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV2_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND1_ADDR)
#define HWIO_VOTETABLE_DRV2_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND1_IN)
#define HWIO_VOTETABLE_DRV2_ND1_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV2_ND1_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV2_ND1_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV2_ND1_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV2_ND1_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV2_ND1_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV2_ND1_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV2_ND1_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV2_ND1_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV2_ND1_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV2_ND2_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00020008)
#define HWIO_VOTETABLE_DRV2_ND2_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV2_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND2_ADDR)
#define HWIO_VOTETABLE_DRV2_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND2_IN)
#define HWIO_VOTETABLE_DRV2_ND2_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV2_ND2_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV2_ND2_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV2_ND2_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV2_ND2_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV2_ND2_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV2_ND2_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV2_ND2_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV2_ND2_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV2_ND2_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV2_ND3_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x0002000c)
#define HWIO_VOTETABLE_DRV2_ND3_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV2_ND3_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND3_ADDR)
#define HWIO_VOTETABLE_DRV2_ND3_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND3_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND3_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND3_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND3_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND3_IN)
#define HWIO_VOTETABLE_DRV2_ND3_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV2_ND3_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV2_ND3_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV2_ND3_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV2_ND3_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV2_ND3_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV2_ND3_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV2_ND3_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV2_ND3_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV2_ND3_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV2_ND4_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00020010)
#define HWIO_VOTETABLE_DRV2_ND4_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV2_ND4_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND4_ADDR)
#define HWIO_VOTETABLE_DRV2_ND4_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND4_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND4_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND4_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND4_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND4_IN)
#define HWIO_VOTETABLE_DRV2_ND4_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV2_ND4_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV2_ND4_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV2_ND4_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV2_ND4_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV2_ND4_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV2_ND4_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV2_ND4_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV2_ND4_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV2_ND4_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV2_ND5_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00020014)
#define HWIO_VOTETABLE_DRV2_ND5_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV2_ND5_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND5_ADDR)
#define HWIO_VOTETABLE_DRV2_ND5_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND5_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND5_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND5_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND5_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND5_IN)
#define HWIO_VOTETABLE_DRV2_ND5_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV2_ND5_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV2_ND5_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV2_ND5_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV2_ND5_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV2_ND5_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV2_ND5_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV2_ND5_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV2_ND5_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV2_ND5_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV2_ND6_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00020018)
#define HWIO_VOTETABLE_DRV2_ND6_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV2_ND6_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND6_ADDR)
#define HWIO_VOTETABLE_DRV2_ND6_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND6_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND6_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND6_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND6_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND6_IN)
#define HWIO_VOTETABLE_DRV2_ND6_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV2_ND6_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV2_ND6_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV2_ND6_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV2_ND6_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV2_ND6_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV2_ND6_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV2_ND6_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV2_ND6_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV2_ND6_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV2_ND7_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x0002001c)
#define HWIO_VOTETABLE_DRV2_ND7_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV2_ND7_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND7_ADDR)
#define HWIO_VOTETABLE_DRV2_ND7_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND7_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND7_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND7_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND7_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND7_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND7_IN)
#define HWIO_VOTETABLE_DRV2_ND7_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV2_ND7_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV2_ND7_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV2_ND7_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV2_ND7_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV2_ND7_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV2_ND7_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV2_ND7_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV2_ND7_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV2_ND7_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV2_ND8_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00020020)
#define HWIO_VOTETABLE_DRV2_ND8_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV2_ND8_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND8_ADDR)
#define HWIO_VOTETABLE_DRV2_ND8_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND8_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND8_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND8_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND8_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND8_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND8_IN)
#define HWIO_VOTETABLE_DRV2_ND8_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV2_ND8_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV2_ND8_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV2_ND8_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV2_ND8_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV2_ND8_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV2_ND8_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV2_ND8_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV2_ND8_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV2_ND8_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV2_ND9_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00020024)
#define HWIO_VOTETABLE_DRV2_ND9_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV2_ND9_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND9_ADDR)
#define HWIO_VOTETABLE_DRV2_ND9_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND9_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND9_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND9_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND9_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND9_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND9_IN)
#define HWIO_VOTETABLE_DRV2_ND9_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV2_ND9_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV2_ND9_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV2_ND9_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV2_ND9_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV2_ND9_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV2_ND9_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV2_ND9_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV2_ND9_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV2_ND9_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV2_ND10_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020028)
#define HWIO_VOTETABLE_DRV2_ND10_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND10_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND10_ADDR)
#define HWIO_VOTETABLE_DRV2_ND10_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND10_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND10_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND10_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND10_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND10_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND10_IN)
#define HWIO_VOTETABLE_DRV2_ND10_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND10_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND10_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND10_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND10_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND10_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND10_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND10_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND10_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND10_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND11_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0002002c)
#define HWIO_VOTETABLE_DRV2_ND11_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND11_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND11_ADDR)
#define HWIO_VOTETABLE_DRV2_ND11_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND11_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND11_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND11_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND11_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND11_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND11_IN)
#define HWIO_VOTETABLE_DRV2_ND11_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND11_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND11_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND11_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND11_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND11_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND11_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND11_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND11_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND11_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND12_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020030)
#define HWIO_VOTETABLE_DRV2_ND12_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND12_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND12_ADDR)
#define HWIO_VOTETABLE_DRV2_ND12_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND12_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND12_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND12_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND12_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND12_IN)
#define HWIO_VOTETABLE_DRV2_ND12_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND12_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND12_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND12_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND12_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND12_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND12_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND12_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND12_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND12_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND13_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020034)
#define HWIO_VOTETABLE_DRV2_ND13_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND13_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND13_ADDR)
#define HWIO_VOTETABLE_DRV2_ND13_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND13_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND13_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND13_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND13_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND13_IN)
#define HWIO_VOTETABLE_DRV2_ND13_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND13_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND13_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND13_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND13_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND13_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND13_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND13_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND13_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND13_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND14_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020038)
#define HWIO_VOTETABLE_DRV2_ND14_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND14_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND14_ADDR)
#define HWIO_VOTETABLE_DRV2_ND14_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND14_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND14_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND14_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND14_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND14_IN)
#define HWIO_VOTETABLE_DRV2_ND14_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND14_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND14_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND14_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND14_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND14_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND14_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND14_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND14_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND14_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND15_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0002003c)
#define HWIO_VOTETABLE_DRV2_ND15_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND15_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND15_ADDR)
#define HWIO_VOTETABLE_DRV2_ND15_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND15_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND15_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND15_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND15_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND15_IN)
#define HWIO_VOTETABLE_DRV2_ND15_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND15_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND15_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND15_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND15_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND15_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND15_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND15_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND15_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND15_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND16_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020040)
#define HWIO_VOTETABLE_DRV2_ND16_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND16_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND16_ADDR)
#define HWIO_VOTETABLE_DRV2_ND16_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND16_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND16_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND16_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND16_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND16_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND16_IN)
#define HWIO_VOTETABLE_DRV2_ND16_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND16_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND16_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND16_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND16_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND16_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND16_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND16_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND16_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND16_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND17_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020044)
#define HWIO_VOTETABLE_DRV2_ND17_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND17_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND17_ADDR)
#define HWIO_VOTETABLE_DRV2_ND17_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND17_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND17_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND17_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND17_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND17_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND17_IN)
#define HWIO_VOTETABLE_DRV2_ND17_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND17_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND17_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND17_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND17_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND17_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND17_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND17_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND17_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND17_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND18_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020048)
#define HWIO_VOTETABLE_DRV2_ND18_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND18_ADDR)
#define HWIO_VOTETABLE_DRV2_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND18_IN)
#define HWIO_VOTETABLE_DRV2_ND18_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND18_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND18_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND18_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND18_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND18_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND18_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND18_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND18_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND18_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND19_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0002004c)
#define HWIO_VOTETABLE_DRV2_ND19_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND19_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND19_ADDR)
#define HWIO_VOTETABLE_DRV2_ND19_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND19_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND19_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND19_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND19_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND19_IN)
#define HWIO_VOTETABLE_DRV2_ND19_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND19_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND19_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND19_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND19_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND19_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND19_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND19_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND19_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND19_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND20_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020050)
#define HWIO_VOTETABLE_DRV2_ND20_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND20_ADDR)
#define HWIO_VOTETABLE_DRV2_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND20_IN)
#define HWIO_VOTETABLE_DRV2_ND20_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND20_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND20_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND20_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND20_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND20_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND20_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND20_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND20_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND20_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND21_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020054)
#define HWIO_VOTETABLE_DRV2_ND21_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND21_ADDR)
#define HWIO_VOTETABLE_DRV2_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND21_IN)
#define HWIO_VOTETABLE_DRV2_ND21_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND21_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND21_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND21_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND21_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND21_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND21_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND21_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND21_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND21_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND22_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020058)
#define HWIO_VOTETABLE_DRV2_ND22_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND22_ADDR)
#define HWIO_VOTETABLE_DRV2_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND22_IN)
#define HWIO_VOTETABLE_DRV2_ND22_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND22_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND22_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND22_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND22_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND22_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND22_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND22_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND22_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND22_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND23_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0002005c)
#define HWIO_VOTETABLE_DRV2_ND23_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND23_ADDR)
#define HWIO_VOTETABLE_DRV2_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND23_IN)
#define HWIO_VOTETABLE_DRV2_ND23_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND23_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND23_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND23_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND23_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND23_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND23_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND23_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND23_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND23_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND24_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020060)
#define HWIO_VOTETABLE_DRV2_ND24_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND24_ADDR)
#define HWIO_VOTETABLE_DRV2_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND24_IN)
#define HWIO_VOTETABLE_DRV2_ND24_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND24_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND24_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND24_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND24_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND24_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND24_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND24_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND24_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND24_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND25_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020064)
#define HWIO_VOTETABLE_DRV2_ND25_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND25_ADDR)
#define HWIO_VOTETABLE_DRV2_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND25_IN)
#define HWIO_VOTETABLE_DRV2_ND25_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND25_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND25_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND25_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND25_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND25_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND25_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND25_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND25_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND25_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND26_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020068)
#define HWIO_VOTETABLE_DRV2_ND26_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND26_ADDR)
#define HWIO_VOTETABLE_DRV2_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND26_IN)
#define HWIO_VOTETABLE_DRV2_ND26_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND26_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND26_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND26_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND26_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND26_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND26_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND26_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND26_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND26_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND27_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0002006c)
#define HWIO_VOTETABLE_DRV2_ND27_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND27_ADDR)
#define HWIO_VOTETABLE_DRV2_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND27_IN)
#define HWIO_VOTETABLE_DRV2_ND27_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND27_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND27_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND27_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND27_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND27_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND27_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND27_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND27_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND27_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND30_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00020078)
#define HWIO_VOTETABLE_DRV2_ND30_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND30_ADDR)
#define HWIO_VOTETABLE_DRV2_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND30_IN)
#define HWIO_VOTETABLE_DRV2_ND30_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND30_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND30_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND30_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND30_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND30_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND30_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND30_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND30_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND30_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV2_ND31_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0002007c)
#define HWIO_VOTETABLE_DRV2_ND31_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV2_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV2_ND31_ADDR)
#define HWIO_VOTETABLE_DRV2_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV2_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV2_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV2_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV2_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV2_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV2_ND31_IN)
#define HWIO_VOTETABLE_DRV2_ND31_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV2_ND31_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV2_ND31_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV2_ND31_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV2_ND31_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV2_ND31_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV2_ND31_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV2_ND31_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV2_ND31_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV2_ND31_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND0_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00030000)
#define HWIO_VOTETABLE_DRV3_ND0_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV3_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND0_ADDR)
#define HWIO_VOTETABLE_DRV3_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND0_IN)
#define HWIO_VOTETABLE_DRV3_ND0_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV3_ND0_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV3_ND0_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV3_ND0_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV3_ND0_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV3_ND0_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV3_ND0_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV3_ND0_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV3_ND0_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV3_ND0_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV3_ND1_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00030004)
#define HWIO_VOTETABLE_DRV3_ND1_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV3_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND1_ADDR)
#define HWIO_VOTETABLE_DRV3_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND1_IN)
#define HWIO_VOTETABLE_DRV3_ND1_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV3_ND1_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV3_ND1_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV3_ND1_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV3_ND1_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV3_ND1_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV3_ND1_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV3_ND1_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV3_ND1_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV3_ND1_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV3_ND2_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00030008)
#define HWIO_VOTETABLE_DRV3_ND2_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV3_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND2_ADDR)
#define HWIO_VOTETABLE_DRV3_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND2_IN)
#define HWIO_VOTETABLE_DRV3_ND2_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV3_ND2_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV3_ND2_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV3_ND2_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV3_ND2_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV3_ND2_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV3_ND2_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV3_ND2_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV3_ND2_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV3_ND2_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV3_ND3_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x0003000c)
#define HWIO_VOTETABLE_DRV3_ND3_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV3_ND3_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND3_ADDR)
#define HWIO_VOTETABLE_DRV3_ND3_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND3_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND3_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND3_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND3_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND3_IN)
#define HWIO_VOTETABLE_DRV3_ND3_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV3_ND3_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV3_ND3_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV3_ND3_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV3_ND3_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV3_ND3_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV3_ND3_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV3_ND3_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV3_ND3_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV3_ND3_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV3_ND4_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00030010)
#define HWIO_VOTETABLE_DRV3_ND4_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV3_ND4_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND4_ADDR)
#define HWIO_VOTETABLE_DRV3_ND4_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND4_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND4_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND4_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND4_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND4_IN)
#define HWIO_VOTETABLE_DRV3_ND4_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV3_ND4_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV3_ND4_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV3_ND4_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV3_ND4_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV3_ND4_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV3_ND4_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV3_ND4_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV3_ND4_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV3_ND4_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV3_ND12_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00030030)
#define HWIO_VOTETABLE_DRV3_ND12_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND12_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND12_ADDR)
#define HWIO_VOTETABLE_DRV3_ND12_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND12_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND12_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND12_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND12_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND12_IN)
#define HWIO_VOTETABLE_DRV3_ND12_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND12_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND12_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND12_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND12_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND12_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND12_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND12_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND12_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND12_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND18_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00030048)
#define HWIO_VOTETABLE_DRV3_ND18_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND18_ADDR)
#define HWIO_VOTETABLE_DRV3_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND18_IN)
#define HWIO_VOTETABLE_DRV3_ND18_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND18_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND18_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND18_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND18_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND18_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND18_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND18_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND18_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND18_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND19_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0003004c)
#define HWIO_VOTETABLE_DRV3_ND19_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND19_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND19_ADDR)
#define HWIO_VOTETABLE_DRV3_ND19_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND19_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND19_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND19_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND19_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND19_IN)
#define HWIO_VOTETABLE_DRV3_ND19_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND19_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND19_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND19_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND19_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND19_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND19_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND19_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND19_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND19_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND20_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00030050)
#define HWIO_VOTETABLE_DRV3_ND20_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND20_ADDR)
#define HWIO_VOTETABLE_DRV3_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND20_IN)
#define HWIO_VOTETABLE_DRV3_ND20_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND20_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND20_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND20_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND20_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND20_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND20_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND20_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND20_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND20_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND21_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00030054)
#define HWIO_VOTETABLE_DRV3_ND21_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND21_ADDR)
#define HWIO_VOTETABLE_DRV3_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND21_IN)
#define HWIO_VOTETABLE_DRV3_ND21_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND21_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND21_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND21_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND21_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND21_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND21_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND21_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND21_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND21_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND22_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00030058)
#define HWIO_VOTETABLE_DRV3_ND22_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND22_ADDR)
#define HWIO_VOTETABLE_DRV3_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND22_IN)
#define HWIO_VOTETABLE_DRV3_ND22_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND22_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND22_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND22_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND22_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND22_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND22_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND22_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND22_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND22_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND23_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0003005c)
#define HWIO_VOTETABLE_DRV3_ND23_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND23_ADDR)
#define HWIO_VOTETABLE_DRV3_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND23_IN)
#define HWIO_VOTETABLE_DRV3_ND23_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND23_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND23_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND23_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND23_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND23_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND23_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND23_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND23_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND23_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND24_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00030060)
#define HWIO_VOTETABLE_DRV3_ND24_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND24_ADDR)
#define HWIO_VOTETABLE_DRV3_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND24_IN)
#define HWIO_VOTETABLE_DRV3_ND24_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND24_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND24_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND24_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND24_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND24_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND24_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND24_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND24_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND24_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND25_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00030064)
#define HWIO_VOTETABLE_DRV3_ND25_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND25_ADDR)
#define HWIO_VOTETABLE_DRV3_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND25_IN)
#define HWIO_VOTETABLE_DRV3_ND25_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND25_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND25_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND25_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND25_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND25_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND25_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND25_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND25_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND25_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND26_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00030068)
#define HWIO_VOTETABLE_DRV3_ND26_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND26_ADDR)
#define HWIO_VOTETABLE_DRV3_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND26_IN)
#define HWIO_VOTETABLE_DRV3_ND26_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND26_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND26_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND26_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND26_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND26_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND26_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND26_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND26_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND26_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND27_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0003006c)
#define HWIO_VOTETABLE_DRV3_ND27_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND27_ADDR)
#define HWIO_VOTETABLE_DRV3_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND27_IN)
#define HWIO_VOTETABLE_DRV3_ND27_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND27_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND27_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND27_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND27_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND27_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND27_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND27_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND27_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND27_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND30_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00030078)
#define HWIO_VOTETABLE_DRV3_ND30_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND30_ADDR)
#define HWIO_VOTETABLE_DRV3_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND30_IN)
#define HWIO_VOTETABLE_DRV3_ND30_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND30_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND30_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND30_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND30_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND30_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND30_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND30_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND30_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND30_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV3_ND31_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0003007c)
#define HWIO_VOTETABLE_DRV3_ND31_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV3_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV3_ND31_ADDR)
#define HWIO_VOTETABLE_DRV3_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV3_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV3_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV3_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV3_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV3_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV3_ND31_IN)
#define HWIO_VOTETABLE_DRV3_ND31_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV3_ND31_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV3_ND31_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV3_ND31_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV3_ND31_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV3_ND31_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV3_ND31_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV3_ND31_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV3_ND31_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV3_ND31_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND0_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00040000)
#define HWIO_VOTETABLE_DRV4_ND0_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV4_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND0_ADDR)
#define HWIO_VOTETABLE_DRV4_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND0_IN)
#define HWIO_VOTETABLE_DRV4_ND0_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV4_ND0_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV4_ND0_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV4_ND0_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV4_ND0_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV4_ND0_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV4_ND0_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV4_ND0_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV4_ND0_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV4_ND0_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV4_ND1_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00040004)
#define HWIO_VOTETABLE_DRV4_ND1_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV4_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND1_ADDR)
#define HWIO_VOTETABLE_DRV4_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND1_IN)
#define HWIO_VOTETABLE_DRV4_ND1_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV4_ND1_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV4_ND1_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV4_ND1_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV4_ND1_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV4_ND1_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV4_ND1_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV4_ND1_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV4_ND1_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV4_ND1_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV4_ND2_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00040008)
#define HWIO_VOTETABLE_DRV4_ND2_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV4_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND2_ADDR)
#define HWIO_VOTETABLE_DRV4_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND2_IN)
#define HWIO_VOTETABLE_DRV4_ND2_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV4_ND2_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV4_ND2_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV4_ND2_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV4_ND2_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV4_ND2_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV4_ND2_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV4_ND2_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV4_ND2_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV4_ND2_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV4_ND3_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x0004000c)
#define HWIO_VOTETABLE_DRV4_ND3_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV4_ND3_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND3_ADDR)
#define HWIO_VOTETABLE_DRV4_ND3_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND3_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND3_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND3_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND3_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND3_IN)
#define HWIO_VOTETABLE_DRV4_ND3_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV4_ND3_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV4_ND3_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV4_ND3_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV4_ND3_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV4_ND3_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV4_ND3_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV4_ND3_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV4_ND3_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV4_ND3_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV4_ND4_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00040010)
#define HWIO_VOTETABLE_DRV4_ND4_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV4_ND4_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND4_ADDR)
#define HWIO_VOTETABLE_DRV4_ND4_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND4_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND4_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND4_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND4_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND4_IN)
#define HWIO_VOTETABLE_DRV4_ND4_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV4_ND4_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV4_ND4_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV4_ND4_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV4_ND4_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV4_ND4_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV4_ND4_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV4_ND4_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV4_ND4_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV4_ND4_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV4_ND5_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00040014)
#define HWIO_VOTETABLE_DRV4_ND5_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV4_ND5_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND5_ADDR)
#define HWIO_VOTETABLE_DRV4_ND5_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND5_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND5_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND5_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND5_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND5_IN)
#define HWIO_VOTETABLE_DRV4_ND5_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV4_ND5_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV4_ND5_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV4_ND5_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV4_ND5_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV4_ND5_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV4_ND5_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV4_ND5_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV4_ND5_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV4_ND5_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV4_ND6_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00040018)
#define HWIO_VOTETABLE_DRV4_ND6_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV4_ND6_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND6_ADDR)
#define HWIO_VOTETABLE_DRV4_ND6_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND6_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND6_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND6_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND6_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND6_IN)
#define HWIO_VOTETABLE_DRV4_ND6_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV4_ND6_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV4_ND6_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV4_ND6_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV4_ND6_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV4_ND6_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV4_ND6_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV4_ND6_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV4_ND6_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV4_ND6_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV4_ND7_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x0004001c)
#define HWIO_VOTETABLE_DRV4_ND7_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV4_ND7_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND7_ADDR)
#define HWIO_VOTETABLE_DRV4_ND7_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND7_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND7_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND7_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND7_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND7_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND7_IN)
#define HWIO_VOTETABLE_DRV4_ND7_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV4_ND7_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV4_ND7_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV4_ND7_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV4_ND7_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV4_ND7_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV4_ND7_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV4_ND7_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV4_ND7_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV4_ND7_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV4_ND8_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00040020)
#define HWIO_VOTETABLE_DRV4_ND8_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV4_ND8_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND8_ADDR)
#define HWIO_VOTETABLE_DRV4_ND8_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND8_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND8_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND8_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND8_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND8_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND8_IN)
#define HWIO_VOTETABLE_DRV4_ND8_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV4_ND8_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV4_ND8_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV4_ND8_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV4_ND8_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV4_ND8_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV4_ND8_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV4_ND8_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV4_ND8_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV4_ND8_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV4_ND9_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00040024)
#define HWIO_VOTETABLE_DRV4_ND9_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV4_ND9_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND9_ADDR)
#define HWIO_VOTETABLE_DRV4_ND9_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND9_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND9_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND9_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND9_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND9_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND9_IN)
#define HWIO_VOTETABLE_DRV4_ND9_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV4_ND9_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV4_ND9_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV4_ND9_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV4_ND9_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV4_ND9_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV4_ND9_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV4_ND9_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV4_ND9_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV4_ND9_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV4_ND12_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040030)
#define HWIO_VOTETABLE_DRV4_ND12_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND12_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND12_ADDR)
#define HWIO_VOTETABLE_DRV4_ND12_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND12_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND12_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND12_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND12_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND12_IN)
#define HWIO_VOTETABLE_DRV4_ND12_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND12_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND12_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND12_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND12_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND12_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND12_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND12_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND12_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND12_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND15_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0004003c)
#define HWIO_VOTETABLE_DRV4_ND15_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND15_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND15_ADDR)
#define HWIO_VOTETABLE_DRV4_ND15_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND15_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND15_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND15_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND15_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND15_IN)
#define HWIO_VOTETABLE_DRV4_ND15_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND15_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND15_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND15_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND15_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND15_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND15_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND15_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND15_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND15_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND16_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040040)
#define HWIO_VOTETABLE_DRV4_ND16_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND16_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND16_ADDR)
#define HWIO_VOTETABLE_DRV4_ND16_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND16_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND16_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND16_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND16_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND16_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND16_IN)
#define HWIO_VOTETABLE_DRV4_ND16_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND16_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND16_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND16_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND16_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND16_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND16_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND16_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND16_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND16_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND18_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040048)
#define HWIO_VOTETABLE_DRV4_ND18_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND18_ADDR)
#define HWIO_VOTETABLE_DRV4_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND18_IN)
#define HWIO_VOTETABLE_DRV4_ND18_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND18_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND18_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND18_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND18_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND18_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND18_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND18_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND18_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND18_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND19_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0004004c)
#define HWIO_VOTETABLE_DRV4_ND19_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND19_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND19_ADDR)
#define HWIO_VOTETABLE_DRV4_ND19_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND19_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND19_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND19_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND19_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND19_IN)
#define HWIO_VOTETABLE_DRV4_ND19_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND19_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND19_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND19_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND19_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND19_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND19_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND19_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND19_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND19_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND20_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040050)
#define HWIO_VOTETABLE_DRV4_ND20_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND20_ADDR)
#define HWIO_VOTETABLE_DRV4_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND20_IN)
#define HWIO_VOTETABLE_DRV4_ND20_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND20_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND20_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND20_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND20_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND20_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND20_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND20_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND20_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND20_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND21_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040054)
#define HWIO_VOTETABLE_DRV4_ND21_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND21_ADDR)
#define HWIO_VOTETABLE_DRV4_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND21_IN)
#define HWIO_VOTETABLE_DRV4_ND21_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND21_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND21_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND21_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND21_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND21_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND21_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND21_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND21_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND21_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND22_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040058)
#define HWIO_VOTETABLE_DRV4_ND22_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND22_ADDR)
#define HWIO_VOTETABLE_DRV4_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND22_IN)
#define HWIO_VOTETABLE_DRV4_ND22_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND22_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND22_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND22_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND22_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND22_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND22_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND22_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND22_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND22_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND23_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0004005c)
#define HWIO_VOTETABLE_DRV4_ND23_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND23_ADDR)
#define HWIO_VOTETABLE_DRV4_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND23_IN)
#define HWIO_VOTETABLE_DRV4_ND23_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND23_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND23_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND23_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND23_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND23_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND23_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND23_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND23_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND23_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND24_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040060)
#define HWIO_VOTETABLE_DRV4_ND24_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND24_ADDR)
#define HWIO_VOTETABLE_DRV4_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND24_IN)
#define HWIO_VOTETABLE_DRV4_ND24_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND24_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND24_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND24_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND24_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND24_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND24_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND24_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND24_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND24_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND25_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040064)
#define HWIO_VOTETABLE_DRV4_ND25_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND25_ADDR)
#define HWIO_VOTETABLE_DRV4_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND25_IN)
#define HWIO_VOTETABLE_DRV4_ND25_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND25_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND25_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND25_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND25_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND25_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND25_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND25_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND25_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND25_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND26_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040068)
#define HWIO_VOTETABLE_DRV4_ND26_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND26_ADDR)
#define HWIO_VOTETABLE_DRV4_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND26_IN)
#define HWIO_VOTETABLE_DRV4_ND26_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND26_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND26_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND26_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND26_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND26_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND26_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND26_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND26_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND26_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND27_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0004006c)
#define HWIO_VOTETABLE_DRV4_ND27_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND27_ADDR)
#define HWIO_VOTETABLE_DRV4_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND27_IN)
#define HWIO_VOTETABLE_DRV4_ND27_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND27_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND27_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND27_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND27_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND27_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND27_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND27_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND27_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND27_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND28_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040070)
#define HWIO_VOTETABLE_DRV4_ND28_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND28_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND28_ADDR)
#define HWIO_VOTETABLE_DRV4_ND28_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND28_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND28_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND28_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND28_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND28_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND28_IN)
#define HWIO_VOTETABLE_DRV4_ND28_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND28_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND28_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND28_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND28_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND28_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND28_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND28_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND28_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND28_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND29_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040074)
#define HWIO_VOTETABLE_DRV4_ND29_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND29_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND29_ADDR)
#define HWIO_VOTETABLE_DRV4_ND29_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND29_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND29_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND29_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND29_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND29_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND29_IN)
#define HWIO_VOTETABLE_DRV4_ND29_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND29_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND29_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND29_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND29_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND29_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND29_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND29_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND29_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND29_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND30_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00040078)
#define HWIO_VOTETABLE_DRV4_ND30_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND30_ADDR)
#define HWIO_VOTETABLE_DRV4_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND30_IN)
#define HWIO_VOTETABLE_DRV4_ND30_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND30_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND30_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND30_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND30_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND30_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND30_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND30_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND30_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND30_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV4_ND31_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0004007c)
#define HWIO_VOTETABLE_DRV4_ND31_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV4_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV4_ND31_ADDR)
#define HWIO_VOTETABLE_DRV4_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV4_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV4_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV4_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV4_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV4_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV4_ND31_IN)
#define HWIO_VOTETABLE_DRV4_ND31_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV4_ND31_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV4_ND31_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV4_ND31_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV4_ND31_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV4_ND31_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV4_ND31_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV4_ND31_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV4_ND31_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV4_ND31_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND0_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00050000)
#define HWIO_VOTETABLE_DRV5_ND0_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV5_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND0_ADDR)
#define HWIO_VOTETABLE_DRV5_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND0_IN)
#define HWIO_VOTETABLE_DRV5_ND0_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV5_ND0_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV5_ND0_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV5_ND0_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV5_ND0_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV5_ND0_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV5_ND0_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV5_ND0_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV5_ND0_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV5_ND0_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV5_ND1_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00050004)
#define HWIO_VOTETABLE_DRV5_ND1_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV5_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND1_ADDR)
#define HWIO_VOTETABLE_DRV5_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND1_IN)
#define HWIO_VOTETABLE_DRV5_ND1_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV5_ND1_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV5_ND1_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV5_ND1_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV5_ND1_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV5_ND1_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV5_ND1_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV5_ND1_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV5_ND1_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV5_ND1_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV5_ND2_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00050008)
#define HWIO_VOTETABLE_DRV5_ND2_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV5_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND2_ADDR)
#define HWIO_VOTETABLE_DRV5_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND2_IN)
#define HWIO_VOTETABLE_DRV5_ND2_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV5_ND2_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV5_ND2_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV5_ND2_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV5_ND2_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV5_ND2_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV5_ND2_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV5_ND2_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV5_ND2_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV5_ND2_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV5_ND3_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x0005000c)
#define HWIO_VOTETABLE_DRV5_ND3_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV5_ND3_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND3_ADDR)
#define HWIO_VOTETABLE_DRV5_ND3_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND3_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND3_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND3_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND3_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND3_IN)
#define HWIO_VOTETABLE_DRV5_ND3_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV5_ND3_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV5_ND3_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV5_ND3_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV5_ND3_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV5_ND3_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV5_ND3_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV5_ND3_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV5_ND3_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV5_ND3_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV5_ND4_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00050010)
#define HWIO_VOTETABLE_DRV5_ND4_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV5_ND4_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND4_ADDR)
#define HWIO_VOTETABLE_DRV5_ND4_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND4_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND4_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND4_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND4_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND4_IN)
#define HWIO_VOTETABLE_DRV5_ND4_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV5_ND4_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV5_ND4_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV5_ND4_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV5_ND4_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV5_ND4_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV5_ND4_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV5_ND4_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV5_ND4_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV5_ND4_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV5_ND5_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00050014)
#define HWIO_VOTETABLE_DRV5_ND5_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV5_ND5_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND5_ADDR)
#define HWIO_VOTETABLE_DRV5_ND5_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND5_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND5_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND5_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND5_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND5_IN)
#define HWIO_VOTETABLE_DRV5_ND5_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV5_ND5_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV5_ND5_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV5_ND5_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV5_ND5_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV5_ND5_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV5_ND5_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV5_ND5_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV5_ND5_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV5_ND5_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV5_ND6_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00050018)
#define HWIO_VOTETABLE_DRV5_ND6_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV5_ND6_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND6_ADDR)
#define HWIO_VOTETABLE_DRV5_ND6_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND6_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND6_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND6_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND6_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND6_IN)
#define HWIO_VOTETABLE_DRV5_ND6_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV5_ND6_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV5_ND6_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV5_ND6_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV5_ND6_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV5_ND6_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV5_ND6_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV5_ND6_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV5_ND6_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV5_ND6_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV5_ND10_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050028)
#define HWIO_VOTETABLE_DRV5_ND10_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND10_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND10_ADDR)
#define HWIO_VOTETABLE_DRV5_ND10_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND10_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND10_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND10_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND10_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND10_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND10_IN)
#define HWIO_VOTETABLE_DRV5_ND10_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND10_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND10_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND10_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND10_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND10_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND10_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND10_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND10_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND10_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND11_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0005002c)
#define HWIO_VOTETABLE_DRV5_ND11_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND11_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND11_ADDR)
#define HWIO_VOTETABLE_DRV5_ND11_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND11_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND11_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND11_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND11_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND11_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND11_IN)
#define HWIO_VOTETABLE_DRV5_ND11_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND11_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND11_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND11_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND11_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND11_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND11_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND11_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND11_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND11_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND12_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050030)
#define HWIO_VOTETABLE_DRV5_ND12_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND12_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND12_ADDR)
#define HWIO_VOTETABLE_DRV5_ND12_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND12_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND12_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND12_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND12_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND12_IN)
#define HWIO_VOTETABLE_DRV5_ND12_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND12_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND12_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND12_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND12_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND12_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND12_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND12_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND12_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND12_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND13_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050034)
#define HWIO_VOTETABLE_DRV5_ND13_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND13_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND13_ADDR)
#define HWIO_VOTETABLE_DRV5_ND13_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND13_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND13_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND13_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND13_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND13_IN)
#define HWIO_VOTETABLE_DRV5_ND13_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND13_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND13_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND13_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND13_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND13_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND13_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND13_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND13_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND13_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND14_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050038)
#define HWIO_VOTETABLE_DRV5_ND14_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND14_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND14_ADDR)
#define HWIO_VOTETABLE_DRV5_ND14_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND14_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND14_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND14_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND14_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND14_IN)
#define HWIO_VOTETABLE_DRV5_ND14_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND14_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND14_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND14_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND14_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND14_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND14_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND14_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND14_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND14_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND15_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0005003c)
#define HWIO_VOTETABLE_DRV5_ND15_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND15_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND15_ADDR)
#define HWIO_VOTETABLE_DRV5_ND15_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND15_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND15_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND15_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND15_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND15_IN)
#define HWIO_VOTETABLE_DRV5_ND15_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND15_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND15_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND15_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND15_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND15_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND15_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND15_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND15_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND15_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND16_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050040)
#define HWIO_VOTETABLE_DRV5_ND16_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND16_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND16_ADDR)
#define HWIO_VOTETABLE_DRV5_ND16_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND16_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND16_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND16_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND16_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND16_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND16_IN)
#define HWIO_VOTETABLE_DRV5_ND16_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND16_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND16_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND16_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND16_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND16_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND16_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND16_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND16_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND16_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND17_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050044)
#define HWIO_VOTETABLE_DRV5_ND17_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND17_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND17_ADDR)
#define HWIO_VOTETABLE_DRV5_ND17_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND17_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND17_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND17_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND17_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND17_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND17_IN)
#define HWIO_VOTETABLE_DRV5_ND17_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND17_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND17_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND17_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND17_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND17_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND17_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND17_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND17_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND17_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND18_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050048)
#define HWIO_VOTETABLE_DRV5_ND18_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND18_ADDR)
#define HWIO_VOTETABLE_DRV5_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND18_IN)
#define HWIO_VOTETABLE_DRV5_ND18_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND18_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND18_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND18_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND18_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND18_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND18_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND18_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND18_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND18_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND20_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050050)
#define HWIO_VOTETABLE_DRV5_ND20_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND20_ADDR)
#define HWIO_VOTETABLE_DRV5_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND20_IN)
#define HWIO_VOTETABLE_DRV5_ND20_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND20_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND20_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND20_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND20_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND20_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND20_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND20_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND20_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND20_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND21_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050054)
#define HWIO_VOTETABLE_DRV5_ND21_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND21_ADDR)
#define HWIO_VOTETABLE_DRV5_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND21_IN)
#define HWIO_VOTETABLE_DRV5_ND21_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND21_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND21_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND21_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND21_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND21_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND21_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND21_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND21_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND21_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND22_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050058)
#define HWIO_VOTETABLE_DRV5_ND22_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND22_ADDR)
#define HWIO_VOTETABLE_DRV5_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND22_IN)
#define HWIO_VOTETABLE_DRV5_ND22_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND22_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND22_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND22_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND22_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND22_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND22_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND22_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND22_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND22_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND23_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0005005c)
#define HWIO_VOTETABLE_DRV5_ND23_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND23_ADDR)
#define HWIO_VOTETABLE_DRV5_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND23_IN)
#define HWIO_VOTETABLE_DRV5_ND23_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND23_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND23_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND23_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND23_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND23_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND23_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND23_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND23_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND23_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND24_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050060)
#define HWIO_VOTETABLE_DRV5_ND24_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND24_ADDR)
#define HWIO_VOTETABLE_DRV5_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND24_IN)
#define HWIO_VOTETABLE_DRV5_ND24_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND24_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND24_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND24_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND24_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND24_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND24_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND24_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND24_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND24_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND25_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050064)
#define HWIO_VOTETABLE_DRV5_ND25_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND25_ADDR)
#define HWIO_VOTETABLE_DRV5_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND25_IN)
#define HWIO_VOTETABLE_DRV5_ND25_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND25_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND25_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND25_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND25_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND25_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND25_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND25_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND25_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND25_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND26_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050068)
#define HWIO_VOTETABLE_DRV5_ND26_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND26_ADDR)
#define HWIO_VOTETABLE_DRV5_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND26_IN)
#define HWIO_VOTETABLE_DRV5_ND26_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND26_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND26_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND26_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND26_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND26_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND26_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND26_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND26_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND26_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND27_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0005006c)
#define HWIO_VOTETABLE_DRV5_ND27_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND27_ADDR)
#define HWIO_VOTETABLE_DRV5_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND27_IN)
#define HWIO_VOTETABLE_DRV5_ND27_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND27_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND27_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND27_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND27_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND27_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND27_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND27_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND27_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND27_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND30_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00050078)
#define HWIO_VOTETABLE_DRV5_ND30_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND30_ADDR)
#define HWIO_VOTETABLE_DRV5_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND30_IN)
#define HWIO_VOTETABLE_DRV5_ND30_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND30_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND30_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND30_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND30_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND30_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND30_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND30_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND30_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND30_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV5_ND31_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0005007c)
#define HWIO_VOTETABLE_DRV5_ND31_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV5_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV5_ND31_ADDR)
#define HWIO_VOTETABLE_DRV5_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV5_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV5_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV5_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV5_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV5_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV5_ND31_IN)
#define HWIO_VOTETABLE_DRV5_ND31_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV5_ND31_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV5_ND31_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV5_ND31_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV5_ND31_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV5_ND31_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV5_ND31_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV5_ND31_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV5_ND31_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV5_ND31_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND0_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00060000)
#define HWIO_VOTETABLE_DRV6_ND0_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV6_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND0_ADDR)
#define HWIO_VOTETABLE_DRV6_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND0_IN)
#define HWIO_VOTETABLE_DRV6_ND0_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV6_ND0_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV6_ND0_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV6_ND0_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV6_ND0_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV6_ND0_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV6_ND0_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV6_ND0_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV6_ND0_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV6_ND0_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV6_ND1_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00060004)
#define HWIO_VOTETABLE_DRV6_ND1_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV6_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND1_ADDR)
#define HWIO_VOTETABLE_DRV6_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND1_IN)
#define HWIO_VOTETABLE_DRV6_ND1_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV6_ND1_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV6_ND1_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV6_ND1_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV6_ND1_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV6_ND1_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV6_ND1_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV6_ND1_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV6_ND1_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV6_ND1_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV6_ND2_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00060008)
#define HWIO_VOTETABLE_DRV6_ND2_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV6_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND2_ADDR)
#define HWIO_VOTETABLE_DRV6_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND2_IN)
#define HWIO_VOTETABLE_DRV6_ND2_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV6_ND2_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV6_ND2_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV6_ND2_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV6_ND2_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV6_ND2_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV6_ND2_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV6_ND2_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV6_ND2_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV6_ND2_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV6_ND3_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x0006000c)
#define HWIO_VOTETABLE_DRV6_ND3_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV6_ND3_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND3_ADDR)
#define HWIO_VOTETABLE_DRV6_ND3_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND3_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND3_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND3_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND3_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND3_IN)
#define HWIO_VOTETABLE_DRV6_ND3_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV6_ND3_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV6_ND3_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV6_ND3_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV6_ND3_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV6_ND3_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV6_ND3_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV6_ND3_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV6_ND3_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV6_ND3_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV6_ND4_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00060010)
#define HWIO_VOTETABLE_DRV6_ND4_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV6_ND4_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND4_ADDR)
#define HWIO_VOTETABLE_DRV6_ND4_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND4_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND4_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND4_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND4_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND4_IN)
#define HWIO_VOTETABLE_DRV6_ND4_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV6_ND4_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV6_ND4_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV6_ND4_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV6_ND4_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV6_ND4_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV6_ND4_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV6_ND4_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV6_ND4_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV6_ND4_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV6_ND10_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060028)
#define HWIO_VOTETABLE_DRV6_ND10_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND10_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND10_ADDR)
#define HWIO_VOTETABLE_DRV6_ND10_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND10_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND10_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND10_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND10_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND10_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND10_IN)
#define HWIO_VOTETABLE_DRV6_ND10_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND10_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND10_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND10_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND10_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND10_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND10_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND10_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND10_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND10_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND11_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0006002c)
#define HWIO_VOTETABLE_DRV6_ND11_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND11_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND11_ADDR)
#define HWIO_VOTETABLE_DRV6_ND11_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND11_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND11_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND11_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND11_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND11_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND11_IN)
#define HWIO_VOTETABLE_DRV6_ND11_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND11_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND11_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND11_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND11_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND11_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND11_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND11_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND11_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND11_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND12_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060030)
#define HWIO_VOTETABLE_DRV6_ND12_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND12_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND12_ADDR)
#define HWIO_VOTETABLE_DRV6_ND12_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND12_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND12_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND12_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND12_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND12_IN)
#define HWIO_VOTETABLE_DRV6_ND12_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND12_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND12_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND12_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND12_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND12_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND12_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND12_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND12_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND12_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND13_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060034)
#define HWIO_VOTETABLE_DRV6_ND13_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND13_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND13_ADDR)
#define HWIO_VOTETABLE_DRV6_ND13_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND13_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND13_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND13_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND13_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND13_IN)
#define HWIO_VOTETABLE_DRV6_ND13_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND13_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND13_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND13_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND13_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND13_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND13_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND13_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND13_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND13_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND14_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060038)
#define HWIO_VOTETABLE_DRV6_ND14_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND14_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND14_ADDR)
#define HWIO_VOTETABLE_DRV6_ND14_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND14_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND14_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND14_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND14_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND14_IN)
#define HWIO_VOTETABLE_DRV6_ND14_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND14_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND14_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND14_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND14_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND14_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND14_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND14_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND14_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND14_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND15_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0006003c)
#define HWIO_VOTETABLE_DRV6_ND15_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND15_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND15_ADDR)
#define HWIO_VOTETABLE_DRV6_ND15_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND15_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND15_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND15_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND15_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND15_IN)
#define HWIO_VOTETABLE_DRV6_ND15_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND15_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND15_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND15_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND15_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND15_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND15_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND15_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND15_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND15_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND17_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060044)
#define HWIO_VOTETABLE_DRV6_ND17_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND17_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND17_ADDR)
#define HWIO_VOTETABLE_DRV6_ND17_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND17_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND17_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND17_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND17_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND17_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND17_IN)
#define HWIO_VOTETABLE_DRV6_ND17_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND17_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND17_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND17_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND17_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND17_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND17_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND17_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND17_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND17_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND18_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060048)
#define HWIO_VOTETABLE_DRV6_ND18_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND18_ADDR)
#define HWIO_VOTETABLE_DRV6_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND18_IN)
#define HWIO_VOTETABLE_DRV6_ND18_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND18_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND18_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND18_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND18_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND18_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND18_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND18_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND18_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND18_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND19_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0006004c)
#define HWIO_VOTETABLE_DRV6_ND19_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND19_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND19_ADDR)
#define HWIO_VOTETABLE_DRV6_ND19_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND19_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND19_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND19_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND19_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND19_IN)
#define HWIO_VOTETABLE_DRV6_ND19_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND19_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND19_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND19_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND19_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND19_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND19_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND19_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND19_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND19_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND20_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060050)
#define HWIO_VOTETABLE_DRV6_ND20_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND20_ADDR)
#define HWIO_VOTETABLE_DRV6_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND20_IN)
#define HWIO_VOTETABLE_DRV6_ND20_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND20_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND20_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND20_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND20_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND20_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND20_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND20_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND20_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND20_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND21_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060054)
#define HWIO_VOTETABLE_DRV6_ND21_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND21_ADDR)
#define HWIO_VOTETABLE_DRV6_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND21_IN)
#define HWIO_VOTETABLE_DRV6_ND21_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND21_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND21_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND21_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND21_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND21_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND21_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND21_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND21_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND21_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND22_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060058)
#define HWIO_VOTETABLE_DRV6_ND22_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND22_ADDR)
#define HWIO_VOTETABLE_DRV6_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND22_IN)
#define HWIO_VOTETABLE_DRV6_ND22_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND22_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND22_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND22_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND22_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND22_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND22_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND22_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND22_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND22_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND23_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0006005c)
#define HWIO_VOTETABLE_DRV6_ND23_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND23_ADDR)
#define HWIO_VOTETABLE_DRV6_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND23_IN)
#define HWIO_VOTETABLE_DRV6_ND23_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND23_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND23_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND23_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND23_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND23_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND23_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND23_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND23_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND23_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND24_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060060)
#define HWIO_VOTETABLE_DRV6_ND24_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND24_ADDR)
#define HWIO_VOTETABLE_DRV6_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND24_IN)
#define HWIO_VOTETABLE_DRV6_ND24_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND24_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND24_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND24_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND24_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND24_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND24_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND24_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND24_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND24_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND25_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060064)
#define HWIO_VOTETABLE_DRV6_ND25_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND25_ADDR)
#define HWIO_VOTETABLE_DRV6_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND25_IN)
#define HWIO_VOTETABLE_DRV6_ND25_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND25_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND25_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND25_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND25_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND25_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND25_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND25_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND25_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND25_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND26_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060068)
#define HWIO_VOTETABLE_DRV6_ND26_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND26_ADDR)
#define HWIO_VOTETABLE_DRV6_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND26_IN)
#define HWIO_VOTETABLE_DRV6_ND26_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND26_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND26_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND26_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND26_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND26_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND26_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND26_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND26_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND26_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND27_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0006006c)
#define HWIO_VOTETABLE_DRV6_ND27_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND27_ADDR)
#define HWIO_VOTETABLE_DRV6_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND27_IN)
#define HWIO_VOTETABLE_DRV6_ND27_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND27_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND27_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND27_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND27_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND27_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND27_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND27_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND27_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND27_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND30_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00060078)
#define HWIO_VOTETABLE_DRV6_ND30_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND30_ADDR)
#define HWIO_VOTETABLE_DRV6_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND30_IN)
#define HWIO_VOTETABLE_DRV6_ND30_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND30_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND30_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND30_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND30_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND30_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND30_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND30_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND30_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND30_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV6_ND31_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0006007c)
#define HWIO_VOTETABLE_DRV6_ND31_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV6_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV6_ND31_ADDR)
#define HWIO_VOTETABLE_DRV6_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV6_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV6_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV6_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV6_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV6_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV6_ND31_IN)
#define HWIO_VOTETABLE_DRV6_ND31_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV6_ND31_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV6_ND31_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV6_ND31_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV6_ND31_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV6_ND31_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV6_ND31_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV6_ND31_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV6_ND31_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV6_ND31_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND0_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00070000)
#define HWIO_VOTETABLE_DRV7_ND0_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV7_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND0_ADDR)
#define HWIO_VOTETABLE_DRV7_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND0_IN)
#define HWIO_VOTETABLE_DRV7_ND0_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV7_ND0_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV7_ND0_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV7_ND0_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV7_ND0_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV7_ND0_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV7_ND0_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV7_ND0_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV7_ND0_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV7_ND0_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV7_ND1_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00070004)
#define HWIO_VOTETABLE_DRV7_ND1_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV7_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND1_ADDR)
#define HWIO_VOTETABLE_DRV7_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND1_IN)
#define HWIO_VOTETABLE_DRV7_ND1_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV7_ND1_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV7_ND1_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV7_ND1_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV7_ND1_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV7_ND1_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV7_ND1_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV7_ND1_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV7_ND1_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV7_ND1_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV7_ND2_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00070008)
#define HWIO_VOTETABLE_DRV7_ND2_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV7_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND2_ADDR)
#define HWIO_VOTETABLE_DRV7_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND2_IN)
#define HWIO_VOTETABLE_DRV7_ND2_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV7_ND2_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV7_ND2_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV7_ND2_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV7_ND2_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV7_ND2_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV7_ND2_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV7_ND2_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV7_ND2_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV7_ND2_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV7_ND12_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00070030)
#define HWIO_VOTETABLE_DRV7_ND12_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND12_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND12_ADDR)
#define HWIO_VOTETABLE_DRV7_ND12_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND12_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND12_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND12_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND12_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND12_IN)
#define HWIO_VOTETABLE_DRV7_ND12_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND12_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND12_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND12_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND12_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND12_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND12_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND12_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND12_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND12_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND18_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00070048)
#define HWIO_VOTETABLE_DRV7_ND18_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND18_ADDR)
#define HWIO_VOTETABLE_DRV7_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND18_IN)
#define HWIO_VOTETABLE_DRV7_ND18_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND18_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND18_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND18_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND18_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND18_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND18_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND18_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND18_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND18_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND19_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0007004c)
#define HWIO_VOTETABLE_DRV7_ND19_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND19_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND19_ADDR)
#define HWIO_VOTETABLE_DRV7_ND19_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND19_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND19_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND19_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND19_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND19_IN)
#define HWIO_VOTETABLE_DRV7_ND19_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND19_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND19_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND19_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND19_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND19_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND19_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND19_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND19_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND19_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND20_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00070050)
#define HWIO_VOTETABLE_DRV7_ND20_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND20_ADDR)
#define HWIO_VOTETABLE_DRV7_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND20_IN)
#define HWIO_VOTETABLE_DRV7_ND20_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND20_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND20_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND20_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND20_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND20_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND20_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND20_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND20_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND20_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND21_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00070054)
#define HWIO_VOTETABLE_DRV7_ND21_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND21_ADDR)
#define HWIO_VOTETABLE_DRV7_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND21_IN)
#define HWIO_VOTETABLE_DRV7_ND21_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND21_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND21_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND21_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND21_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND21_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND21_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND21_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND21_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND21_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND22_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00070058)
#define HWIO_VOTETABLE_DRV7_ND22_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND22_ADDR)
#define HWIO_VOTETABLE_DRV7_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND22_IN)
#define HWIO_VOTETABLE_DRV7_ND22_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND22_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND22_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND22_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND22_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND22_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND22_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND22_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND22_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND22_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND23_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0007005c)
#define HWIO_VOTETABLE_DRV7_ND23_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND23_ADDR)
#define HWIO_VOTETABLE_DRV7_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND23_IN)
#define HWIO_VOTETABLE_DRV7_ND23_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND23_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND23_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND23_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND23_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND23_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND23_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND23_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND23_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND23_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND24_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00070060)
#define HWIO_VOTETABLE_DRV7_ND24_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND24_ADDR)
#define HWIO_VOTETABLE_DRV7_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND24_IN)
#define HWIO_VOTETABLE_DRV7_ND24_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND24_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND24_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND24_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND24_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND24_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND24_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND24_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND24_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND24_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND25_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00070064)
#define HWIO_VOTETABLE_DRV7_ND25_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND25_ADDR)
#define HWIO_VOTETABLE_DRV7_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND25_IN)
#define HWIO_VOTETABLE_DRV7_ND25_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND25_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND25_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND25_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND25_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND25_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND25_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND25_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND25_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND25_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND26_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00070068)
#define HWIO_VOTETABLE_DRV7_ND26_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND26_ADDR)
#define HWIO_VOTETABLE_DRV7_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND26_IN)
#define HWIO_VOTETABLE_DRV7_ND26_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND26_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND26_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND26_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND26_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND26_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND26_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND26_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND26_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND26_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND27_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0007006c)
#define HWIO_VOTETABLE_DRV7_ND27_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND27_ADDR)
#define HWIO_VOTETABLE_DRV7_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND27_IN)
#define HWIO_VOTETABLE_DRV7_ND27_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND27_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND27_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND27_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND27_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND27_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND27_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND27_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND27_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND27_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND30_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00070078)
#define HWIO_VOTETABLE_DRV7_ND30_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND30_ADDR)
#define HWIO_VOTETABLE_DRV7_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND30_IN)
#define HWIO_VOTETABLE_DRV7_ND30_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND30_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND30_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND30_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND30_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND30_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND30_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND30_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND30_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND30_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV7_ND31_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0007007c)
#define HWIO_VOTETABLE_DRV7_ND31_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV7_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV7_ND31_ADDR)
#define HWIO_VOTETABLE_DRV7_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV7_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV7_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV7_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV7_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV7_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV7_ND31_IN)
#define HWIO_VOTETABLE_DRV7_ND31_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV7_ND31_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV7_ND31_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV7_ND31_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV7_ND31_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV7_ND31_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV7_ND31_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV7_ND31_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV7_ND31_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV7_ND31_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND0_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00080000)
#define HWIO_VOTETABLE_DRV8_ND0_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV8_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND0_ADDR)
#define HWIO_VOTETABLE_DRV8_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND0_IN)
#define HWIO_VOTETABLE_DRV8_ND0_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV8_ND0_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV8_ND0_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV8_ND0_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV8_ND0_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV8_ND0_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV8_ND0_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV8_ND0_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV8_ND0_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV8_ND0_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV8_ND1_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00080004)
#define HWIO_VOTETABLE_DRV8_ND1_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV8_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND1_ADDR)
#define HWIO_VOTETABLE_DRV8_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND1_IN)
#define HWIO_VOTETABLE_DRV8_ND1_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV8_ND1_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV8_ND1_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV8_ND1_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV8_ND1_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV8_ND1_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV8_ND1_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV8_ND1_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV8_ND1_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV8_ND1_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV8_ND2_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00080008)
#define HWIO_VOTETABLE_DRV8_ND2_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV8_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND2_ADDR)
#define HWIO_VOTETABLE_DRV8_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND2_IN)
#define HWIO_VOTETABLE_DRV8_ND2_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV8_ND2_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV8_ND2_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV8_ND2_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV8_ND2_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV8_ND2_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV8_ND2_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV8_ND2_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV8_ND2_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV8_ND2_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV8_ND10_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00080028)
#define HWIO_VOTETABLE_DRV8_ND10_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND10_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND10_ADDR)
#define HWIO_VOTETABLE_DRV8_ND10_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND10_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND10_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND10_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND10_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND10_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND10_IN)
#define HWIO_VOTETABLE_DRV8_ND10_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND10_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND10_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND10_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND10_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND10_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND10_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND10_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND10_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND10_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND11_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0008002c)
#define HWIO_VOTETABLE_DRV8_ND11_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND11_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND11_ADDR)
#define HWIO_VOTETABLE_DRV8_ND11_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND11_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND11_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND11_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND11_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND11_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND11_IN)
#define HWIO_VOTETABLE_DRV8_ND11_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND11_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND11_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND11_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND11_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND11_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND11_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND11_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND11_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND11_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND18_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00080048)
#define HWIO_VOTETABLE_DRV8_ND18_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND18_ADDR)
#define HWIO_VOTETABLE_DRV8_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND18_IN)
#define HWIO_VOTETABLE_DRV8_ND18_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND18_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND18_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND18_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND18_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND18_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND18_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND18_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND18_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND18_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND19_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0008004c)
#define HWIO_VOTETABLE_DRV8_ND19_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND19_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND19_ADDR)
#define HWIO_VOTETABLE_DRV8_ND19_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND19_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND19_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND19_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND19_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND19_IN)
#define HWIO_VOTETABLE_DRV8_ND19_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND19_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND19_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND19_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND19_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND19_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND19_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND19_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND19_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND19_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND20_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00080050)
#define HWIO_VOTETABLE_DRV8_ND20_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND20_ADDR)
#define HWIO_VOTETABLE_DRV8_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND20_IN)
#define HWIO_VOTETABLE_DRV8_ND20_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND20_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND20_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND20_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND20_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND20_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND20_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND20_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND20_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND20_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND21_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00080054)
#define HWIO_VOTETABLE_DRV8_ND21_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND21_ADDR)
#define HWIO_VOTETABLE_DRV8_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND21_IN)
#define HWIO_VOTETABLE_DRV8_ND21_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND21_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND21_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND21_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND21_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND21_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND21_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND21_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND21_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND21_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND22_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00080058)
#define HWIO_VOTETABLE_DRV8_ND22_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND22_ADDR)
#define HWIO_VOTETABLE_DRV8_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND22_IN)
#define HWIO_VOTETABLE_DRV8_ND22_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND22_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND22_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND22_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND22_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND22_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND22_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND22_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND22_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND22_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND23_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0008005c)
#define HWIO_VOTETABLE_DRV8_ND23_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND23_ADDR)
#define HWIO_VOTETABLE_DRV8_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND23_IN)
#define HWIO_VOTETABLE_DRV8_ND23_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND23_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND23_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND23_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND23_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND23_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND23_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND23_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND23_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND23_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND24_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00080060)
#define HWIO_VOTETABLE_DRV8_ND24_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND24_ADDR)
#define HWIO_VOTETABLE_DRV8_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND24_IN)
#define HWIO_VOTETABLE_DRV8_ND24_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND24_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND24_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND24_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND24_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND24_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND24_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND24_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND24_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND24_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND25_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00080064)
#define HWIO_VOTETABLE_DRV8_ND25_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND25_ADDR)
#define HWIO_VOTETABLE_DRV8_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND25_IN)
#define HWIO_VOTETABLE_DRV8_ND25_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND25_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND25_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND25_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND25_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND25_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND25_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND25_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND25_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND25_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND26_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00080068)
#define HWIO_VOTETABLE_DRV8_ND26_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND26_ADDR)
#define HWIO_VOTETABLE_DRV8_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND26_IN)
#define HWIO_VOTETABLE_DRV8_ND26_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND26_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND26_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND26_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND26_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND26_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND26_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND26_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND26_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND26_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND27_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0008006c)
#define HWIO_VOTETABLE_DRV8_ND27_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND27_ADDR)
#define HWIO_VOTETABLE_DRV8_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND27_IN)
#define HWIO_VOTETABLE_DRV8_ND27_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND27_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND27_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND27_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND27_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND27_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND27_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND27_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND27_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND27_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND30_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00080078)
#define HWIO_VOTETABLE_DRV8_ND30_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND30_ADDR)
#define HWIO_VOTETABLE_DRV8_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND30_IN)
#define HWIO_VOTETABLE_DRV8_ND30_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND30_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND30_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND30_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND30_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND30_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND30_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND30_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND30_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND30_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV8_ND31_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0008007c)
#define HWIO_VOTETABLE_DRV8_ND31_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV8_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV8_ND31_ADDR)
#define HWIO_VOTETABLE_DRV8_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV8_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV8_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV8_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV8_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV8_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV8_ND31_IN)
#define HWIO_VOTETABLE_DRV8_ND31_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV8_ND31_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV8_ND31_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV8_ND31_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV8_ND31_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV8_ND31_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV8_ND31_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV8_ND31_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV8_ND31_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV8_ND31_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND0_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00090000)
#define HWIO_VOTETABLE_DRV9_ND0_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV9_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND0_ADDR)
#define HWIO_VOTETABLE_DRV9_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND0_IN)
#define HWIO_VOTETABLE_DRV9_ND0_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV9_ND0_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV9_ND0_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV9_ND0_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV9_ND0_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV9_ND0_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV9_ND0_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV9_ND0_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV9_ND0_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV9_ND0_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV9_ND1_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00090004)
#define HWIO_VOTETABLE_DRV9_ND1_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV9_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND1_ADDR)
#define HWIO_VOTETABLE_DRV9_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND1_IN)
#define HWIO_VOTETABLE_DRV9_ND1_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV9_ND1_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV9_ND1_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV9_ND1_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV9_ND1_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV9_ND1_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV9_ND1_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV9_ND1_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV9_ND1_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV9_ND1_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV9_ND2_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00090008)
#define HWIO_VOTETABLE_DRV9_ND2_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV9_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND2_ADDR)
#define HWIO_VOTETABLE_DRV9_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND2_IN)
#define HWIO_VOTETABLE_DRV9_ND2_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV9_ND2_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV9_ND2_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV9_ND2_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV9_ND2_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV9_ND2_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV9_ND2_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV9_ND2_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV9_ND2_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV9_ND2_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV9_ND3_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x0009000c)
#define HWIO_VOTETABLE_DRV9_ND3_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV9_ND3_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND3_ADDR)
#define HWIO_VOTETABLE_DRV9_ND3_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND3_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND3_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND3_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND3_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND3_IN)
#define HWIO_VOTETABLE_DRV9_ND3_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV9_ND3_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV9_ND3_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV9_ND3_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV9_ND3_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV9_ND3_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV9_ND3_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV9_ND3_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV9_ND3_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV9_ND3_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV9_ND4_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00090010)
#define HWIO_VOTETABLE_DRV9_ND4_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV9_ND4_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND4_ADDR)
#define HWIO_VOTETABLE_DRV9_ND4_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND4_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND4_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND4_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND4_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND4_IN)
#define HWIO_VOTETABLE_DRV9_ND4_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV9_ND4_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV9_ND4_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV9_ND4_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV9_ND4_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV9_ND4_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV9_ND4_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV9_ND4_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV9_ND4_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV9_ND4_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV9_ND5_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00090014)
#define HWIO_VOTETABLE_DRV9_ND5_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV9_ND5_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND5_ADDR)
#define HWIO_VOTETABLE_DRV9_ND5_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND5_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND5_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND5_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND5_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND5_IN)
#define HWIO_VOTETABLE_DRV9_ND5_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV9_ND5_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV9_ND5_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV9_ND5_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV9_ND5_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV9_ND5_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV9_ND5_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV9_ND5_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV9_ND5_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV9_ND5_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV9_ND6_ADDR                                                        (BCM_VOTETABLE_REG_BASE      + 0x00090018)
#define HWIO_VOTETABLE_DRV9_ND6_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRV9_ND6_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND6_ADDR)
#define HWIO_VOTETABLE_DRV9_ND6_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND6_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND6_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND6_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND6_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND6_IN)
#define HWIO_VOTETABLE_DRV9_ND6_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRV9_ND6_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRV9_ND6_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRV9_ND6_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRV9_ND6_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRV9_ND6_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRV9_ND6_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRV9_ND6_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRV9_ND6_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRV9_ND6_VOTE_Y_SHFT                                                        0x0

#define HWIO_VOTETABLE_DRV9_ND10_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090028)
#define HWIO_VOTETABLE_DRV9_ND10_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND10_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND10_ADDR)
#define HWIO_VOTETABLE_DRV9_ND10_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND10_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND10_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND10_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND10_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND10_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND10_IN)
#define HWIO_VOTETABLE_DRV9_ND10_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND10_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND10_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND10_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND10_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND10_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND10_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND10_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND10_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND10_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND11_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0009002c)
#define HWIO_VOTETABLE_DRV9_ND11_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND11_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND11_ADDR)
#define HWIO_VOTETABLE_DRV9_ND11_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND11_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND11_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND11_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND11_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND11_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND11_IN)
#define HWIO_VOTETABLE_DRV9_ND11_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND11_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND11_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND11_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND11_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND11_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND11_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND11_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND11_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND11_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND12_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090030)
#define HWIO_VOTETABLE_DRV9_ND12_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND12_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND12_ADDR)
#define HWIO_VOTETABLE_DRV9_ND12_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND12_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND12_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND12_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND12_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND12_IN)
#define HWIO_VOTETABLE_DRV9_ND12_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND12_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND12_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND12_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND12_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND12_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND12_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND12_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND12_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND12_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND15_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0009003c)
#define HWIO_VOTETABLE_DRV9_ND15_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND15_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND15_ADDR)
#define HWIO_VOTETABLE_DRV9_ND15_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND15_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND15_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND15_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND15_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND15_IN)
#define HWIO_VOTETABLE_DRV9_ND15_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND15_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND15_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND15_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND15_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND15_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND15_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND15_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND15_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND15_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND16_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090040)
#define HWIO_VOTETABLE_DRV9_ND16_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND16_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND16_ADDR)
#define HWIO_VOTETABLE_DRV9_ND16_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND16_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND16_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND16_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND16_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND16_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND16_IN)
#define HWIO_VOTETABLE_DRV9_ND16_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND16_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND16_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND16_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND16_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND16_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND16_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND16_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND16_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND16_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND17_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090044)
#define HWIO_VOTETABLE_DRV9_ND17_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND17_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND17_ADDR)
#define HWIO_VOTETABLE_DRV9_ND17_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND17_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND17_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND17_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND17_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND17_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND17_IN)
#define HWIO_VOTETABLE_DRV9_ND17_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND17_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND17_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND17_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND17_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND17_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND17_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND17_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND17_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND17_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND18_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090048)
#define HWIO_VOTETABLE_DRV9_ND18_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND18_ADDR)
#define HWIO_VOTETABLE_DRV9_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND18_IN)
#define HWIO_VOTETABLE_DRV9_ND18_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND18_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND18_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND18_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND18_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND18_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND18_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND18_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND18_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND18_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND19_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0009004c)
#define HWIO_VOTETABLE_DRV9_ND19_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND19_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND19_ADDR)
#define HWIO_VOTETABLE_DRV9_ND19_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND19_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND19_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND19_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND19_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND19_IN)
#define HWIO_VOTETABLE_DRV9_ND19_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND19_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND19_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND19_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND19_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND19_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND19_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND19_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND19_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND19_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND20_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090050)
#define HWIO_VOTETABLE_DRV9_ND20_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND20_ADDR)
#define HWIO_VOTETABLE_DRV9_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND20_IN)
#define HWIO_VOTETABLE_DRV9_ND20_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND20_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND20_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND20_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND20_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND20_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND20_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND20_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND20_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND20_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND21_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090054)
#define HWIO_VOTETABLE_DRV9_ND21_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND21_ADDR)
#define HWIO_VOTETABLE_DRV9_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND21_IN)
#define HWIO_VOTETABLE_DRV9_ND21_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND21_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND21_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND21_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND21_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND21_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND21_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND21_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND21_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND21_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND22_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090058)
#define HWIO_VOTETABLE_DRV9_ND22_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND22_ADDR)
#define HWIO_VOTETABLE_DRV9_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND22_IN)
#define HWIO_VOTETABLE_DRV9_ND22_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND22_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND22_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND22_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND22_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND22_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND22_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND22_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND22_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND22_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND23_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0009005c)
#define HWIO_VOTETABLE_DRV9_ND23_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND23_ADDR)
#define HWIO_VOTETABLE_DRV9_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND23_IN)
#define HWIO_VOTETABLE_DRV9_ND23_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND23_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND23_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND23_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND23_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND23_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND23_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND23_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND23_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND23_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND24_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090060)
#define HWIO_VOTETABLE_DRV9_ND24_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND24_ADDR)
#define HWIO_VOTETABLE_DRV9_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND24_IN)
#define HWIO_VOTETABLE_DRV9_ND24_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND24_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND24_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND24_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND24_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND24_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND24_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND24_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND24_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND24_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND25_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090064)
#define HWIO_VOTETABLE_DRV9_ND25_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND25_ADDR)
#define HWIO_VOTETABLE_DRV9_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND25_IN)
#define HWIO_VOTETABLE_DRV9_ND25_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND25_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND25_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND25_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND25_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND25_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND25_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND25_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND25_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND25_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND26_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090068)
#define HWIO_VOTETABLE_DRV9_ND26_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND26_ADDR)
#define HWIO_VOTETABLE_DRV9_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND26_IN)
#define HWIO_VOTETABLE_DRV9_ND26_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND26_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND26_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND26_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND26_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND26_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND26_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND26_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND26_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND26_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND27_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0009006c)
#define HWIO_VOTETABLE_DRV9_ND27_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND27_ADDR)
#define HWIO_VOTETABLE_DRV9_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND27_IN)
#define HWIO_VOTETABLE_DRV9_ND27_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND27_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND27_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND27_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND27_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND27_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND27_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND27_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND27_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND27_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND30_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x00090078)
#define HWIO_VOTETABLE_DRV9_ND30_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND30_ADDR)
#define HWIO_VOTETABLE_DRV9_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND30_IN)
#define HWIO_VOTETABLE_DRV9_ND30_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND30_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND30_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND30_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND30_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND30_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND30_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND30_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND30_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND30_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV9_ND31_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x0009007c)
#define HWIO_VOTETABLE_DRV9_ND31_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV9_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV9_ND31_ADDR)
#define HWIO_VOTETABLE_DRV9_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV9_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV9_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV9_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV9_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV9_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV9_ND31_IN)
#define HWIO_VOTETABLE_DRV9_ND31_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV9_ND31_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV9_ND31_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV9_ND31_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV9_ND31_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV9_ND31_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV9_ND31_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV9_ND31_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV9_ND31_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV9_ND31_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV11_ND0_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000b0000)
#define HWIO_VOTETABLE_DRV11_ND0_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV11_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND0_ADDR)
#define HWIO_VOTETABLE_DRV11_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND0_IN)
#define HWIO_VOTETABLE_DRV11_ND0_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV11_ND0_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV11_ND0_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV11_ND0_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV11_ND0_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV11_ND0_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV11_ND0_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV11_ND0_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV11_ND0_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV11_ND0_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV11_ND1_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000b0004)
#define HWIO_VOTETABLE_DRV11_ND1_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV11_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND1_ADDR)
#define HWIO_VOTETABLE_DRV11_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND1_IN)
#define HWIO_VOTETABLE_DRV11_ND1_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV11_ND1_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV11_ND1_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV11_ND1_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV11_ND1_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV11_ND1_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV11_ND1_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV11_ND1_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV11_ND1_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV11_ND1_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV11_ND2_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000b0008)
#define HWIO_VOTETABLE_DRV11_ND2_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV11_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND2_ADDR)
#define HWIO_VOTETABLE_DRV11_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND2_IN)
#define HWIO_VOTETABLE_DRV11_ND2_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV11_ND2_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV11_ND2_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV11_ND2_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV11_ND2_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV11_ND2_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV11_ND2_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV11_ND2_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV11_ND2_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV11_ND2_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV11_ND3_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000b000c)
#define HWIO_VOTETABLE_DRV11_ND3_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV11_ND3_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND3_ADDR)
#define HWIO_VOTETABLE_DRV11_ND3_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND3_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND3_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND3_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND3_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND3_IN)
#define HWIO_VOTETABLE_DRV11_ND3_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV11_ND3_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV11_ND3_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV11_ND3_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV11_ND3_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV11_ND3_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV11_ND3_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV11_ND3_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV11_ND3_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV11_ND3_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV11_ND4_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000b0010)
#define HWIO_VOTETABLE_DRV11_ND4_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV11_ND4_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND4_ADDR)
#define HWIO_VOTETABLE_DRV11_ND4_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND4_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND4_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND4_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND4_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND4_IN)
#define HWIO_VOTETABLE_DRV11_ND4_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV11_ND4_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV11_ND4_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV11_ND4_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV11_ND4_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV11_ND4_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV11_ND4_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV11_ND4_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV11_ND4_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV11_ND4_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV11_ND5_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000b0014)
#define HWIO_VOTETABLE_DRV11_ND5_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV11_ND5_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND5_ADDR)
#define HWIO_VOTETABLE_DRV11_ND5_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND5_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND5_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND5_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND5_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND5_IN)
#define HWIO_VOTETABLE_DRV11_ND5_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV11_ND5_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV11_ND5_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV11_ND5_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV11_ND5_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV11_ND5_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV11_ND5_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV11_ND5_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV11_ND5_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV11_ND5_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV11_ND6_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000b0018)
#define HWIO_VOTETABLE_DRV11_ND6_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV11_ND6_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND6_ADDR)
#define HWIO_VOTETABLE_DRV11_ND6_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND6_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND6_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND6_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND6_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND6_IN)
#define HWIO_VOTETABLE_DRV11_ND6_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV11_ND6_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV11_ND6_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV11_ND6_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV11_ND6_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV11_ND6_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV11_ND6_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV11_ND6_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV11_ND6_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV11_ND6_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV11_ND12_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0030)
#define HWIO_VOTETABLE_DRV11_ND12_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND12_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND12_ADDR)
#define HWIO_VOTETABLE_DRV11_ND12_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND12_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND12_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND12_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND12_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND12_IN)
#define HWIO_VOTETABLE_DRV11_ND12_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND12_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND12_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND12_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND12_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND12_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND12_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND12_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND12_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND12_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND13_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0034)
#define HWIO_VOTETABLE_DRV11_ND13_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND13_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND13_ADDR)
#define HWIO_VOTETABLE_DRV11_ND13_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND13_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND13_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND13_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND13_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND13_IN)
#define HWIO_VOTETABLE_DRV11_ND13_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND13_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND13_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND13_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND13_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND13_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND13_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND13_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND13_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND13_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND14_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0038)
#define HWIO_VOTETABLE_DRV11_ND14_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND14_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND14_ADDR)
#define HWIO_VOTETABLE_DRV11_ND14_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND14_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND14_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND14_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND14_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND14_IN)
#define HWIO_VOTETABLE_DRV11_ND14_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND14_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND14_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND14_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND14_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND14_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND14_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND14_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND14_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND14_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND15_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b003c)
#define HWIO_VOTETABLE_DRV11_ND15_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND15_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND15_ADDR)
#define HWIO_VOTETABLE_DRV11_ND15_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND15_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND15_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND15_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND15_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND15_IN)
#define HWIO_VOTETABLE_DRV11_ND15_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND15_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND15_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND15_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND15_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND15_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND15_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND15_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND15_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND15_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND16_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0040)
#define HWIO_VOTETABLE_DRV11_ND16_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND16_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND16_ADDR)
#define HWIO_VOTETABLE_DRV11_ND16_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND16_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND16_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND16_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND16_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND16_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND16_IN)
#define HWIO_VOTETABLE_DRV11_ND16_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND16_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND16_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND16_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND16_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND16_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND16_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND16_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND16_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND16_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND18_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0048)
#define HWIO_VOTETABLE_DRV11_ND18_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND18_ADDR)
#define HWIO_VOTETABLE_DRV11_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND18_IN)
#define HWIO_VOTETABLE_DRV11_ND18_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND18_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND18_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND18_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND18_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND18_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND18_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND18_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND18_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND18_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND19_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b004c)
#define HWIO_VOTETABLE_DRV11_ND19_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND19_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND19_ADDR)
#define HWIO_VOTETABLE_DRV11_ND19_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND19_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND19_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND19_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND19_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND19_IN)
#define HWIO_VOTETABLE_DRV11_ND19_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND19_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND19_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND19_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND19_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND19_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND19_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND19_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND19_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND19_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND20_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0050)
#define HWIO_VOTETABLE_DRV11_ND20_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND20_ADDR)
#define HWIO_VOTETABLE_DRV11_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND20_IN)
#define HWIO_VOTETABLE_DRV11_ND20_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND20_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND20_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND20_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND20_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND20_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND20_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND20_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND20_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND20_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND21_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0054)
#define HWIO_VOTETABLE_DRV11_ND21_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND21_ADDR)
#define HWIO_VOTETABLE_DRV11_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND21_IN)
#define HWIO_VOTETABLE_DRV11_ND21_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND21_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND21_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND21_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND21_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND21_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND21_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND21_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND21_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND21_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND22_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0058)
#define HWIO_VOTETABLE_DRV11_ND22_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND22_ADDR)
#define HWIO_VOTETABLE_DRV11_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND22_IN)
#define HWIO_VOTETABLE_DRV11_ND22_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND22_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND22_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND22_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND22_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND22_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND22_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND22_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND22_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND22_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND23_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b005c)
#define HWIO_VOTETABLE_DRV11_ND23_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND23_ADDR)
#define HWIO_VOTETABLE_DRV11_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND23_IN)
#define HWIO_VOTETABLE_DRV11_ND23_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND23_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND23_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND23_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND23_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND23_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND23_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND23_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND23_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND23_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND24_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0060)
#define HWIO_VOTETABLE_DRV11_ND24_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND24_ADDR)
#define HWIO_VOTETABLE_DRV11_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND24_IN)
#define HWIO_VOTETABLE_DRV11_ND24_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND24_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND24_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND24_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND24_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND24_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND24_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND24_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND24_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND24_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND25_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0064)
#define HWIO_VOTETABLE_DRV11_ND25_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND25_ADDR)
#define HWIO_VOTETABLE_DRV11_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND25_IN)
#define HWIO_VOTETABLE_DRV11_ND25_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND25_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND25_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND25_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND25_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND25_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND25_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND25_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND25_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND25_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND26_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0068)
#define HWIO_VOTETABLE_DRV11_ND26_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND26_ADDR)
#define HWIO_VOTETABLE_DRV11_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND26_IN)
#define HWIO_VOTETABLE_DRV11_ND26_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND26_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND26_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND26_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND26_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND26_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND26_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND26_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND26_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND26_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND27_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b006c)
#define HWIO_VOTETABLE_DRV11_ND27_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND27_ADDR)
#define HWIO_VOTETABLE_DRV11_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND27_IN)
#define HWIO_VOTETABLE_DRV11_ND27_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND27_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND27_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND27_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND27_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND27_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND27_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND27_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND27_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND27_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND30_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b0078)
#define HWIO_VOTETABLE_DRV11_ND30_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND30_ADDR)
#define HWIO_VOTETABLE_DRV11_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND30_IN)
#define HWIO_VOTETABLE_DRV11_ND30_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND30_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND30_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND30_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND30_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND30_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND30_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND30_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND30_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND30_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV11_ND31_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000b007c)
#define HWIO_VOTETABLE_DRV11_ND31_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV11_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV11_ND31_ADDR)
#define HWIO_VOTETABLE_DRV11_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV11_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV11_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV11_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV11_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV11_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV11_ND31_IN)
#define HWIO_VOTETABLE_DRV11_ND31_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV11_ND31_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV11_ND31_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV11_ND31_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV11_ND31_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV11_ND31_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV11_ND31_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV11_ND31_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV11_ND31_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV11_ND31_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND0_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000c0000)
#define HWIO_VOTETABLE_DRV12_ND0_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV12_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND0_ADDR)
#define HWIO_VOTETABLE_DRV12_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND0_IN)
#define HWIO_VOTETABLE_DRV12_ND0_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV12_ND0_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV12_ND0_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV12_ND0_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV12_ND0_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV12_ND0_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV12_ND0_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV12_ND0_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV12_ND0_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV12_ND0_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV12_ND1_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000c0004)
#define HWIO_VOTETABLE_DRV12_ND1_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV12_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND1_ADDR)
#define HWIO_VOTETABLE_DRV12_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND1_IN)
#define HWIO_VOTETABLE_DRV12_ND1_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV12_ND1_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV12_ND1_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV12_ND1_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV12_ND1_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV12_ND1_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV12_ND1_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV12_ND1_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV12_ND1_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV12_ND1_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV12_ND2_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000c0008)
#define HWIO_VOTETABLE_DRV12_ND2_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV12_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND2_ADDR)
#define HWIO_VOTETABLE_DRV12_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND2_IN)
#define HWIO_VOTETABLE_DRV12_ND2_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV12_ND2_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV12_ND2_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV12_ND2_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV12_ND2_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV12_ND2_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV12_ND2_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV12_ND2_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV12_ND2_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV12_ND2_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV12_ND3_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000c000c)
#define HWIO_VOTETABLE_DRV12_ND3_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV12_ND3_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND3_ADDR)
#define HWIO_VOTETABLE_DRV12_ND3_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND3_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND3_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND3_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND3_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND3_IN)
#define HWIO_VOTETABLE_DRV12_ND3_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV12_ND3_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV12_ND3_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV12_ND3_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV12_ND3_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV12_ND3_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV12_ND3_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV12_ND3_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV12_ND3_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV12_ND3_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV12_ND4_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000c0010)
#define HWIO_VOTETABLE_DRV12_ND4_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV12_ND4_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND4_ADDR)
#define HWIO_VOTETABLE_DRV12_ND4_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND4_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND4_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND4_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND4_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND4_IN)
#define HWIO_VOTETABLE_DRV12_ND4_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV12_ND4_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV12_ND4_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV12_ND4_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV12_ND4_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV12_ND4_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV12_ND4_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV12_ND4_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV12_ND4_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV12_ND4_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV12_ND5_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000c0014)
#define HWIO_VOTETABLE_DRV12_ND5_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV12_ND5_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND5_ADDR)
#define HWIO_VOTETABLE_DRV12_ND5_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND5_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND5_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND5_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND5_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND5_IN)
#define HWIO_VOTETABLE_DRV12_ND5_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV12_ND5_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV12_ND5_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV12_ND5_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV12_ND5_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV12_ND5_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV12_ND5_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV12_ND5_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV12_ND5_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV12_ND5_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV12_ND6_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000c0018)
#define HWIO_VOTETABLE_DRV12_ND6_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV12_ND6_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND6_ADDR)
#define HWIO_VOTETABLE_DRV12_ND6_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND6_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND6_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND6_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND6_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND6_IN)
#define HWIO_VOTETABLE_DRV12_ND6_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV12_ND6_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV12_ND6_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV12_ND6_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV12_ND6_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV12_ND6_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV12_ND6_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV12_ND6_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV12_ND6_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV12_ND6_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV12_ND8_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000c0020)
#define HWIO_VOTETABLE_DRV12_ND8_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV12_ND8_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND8_ADDR)
#define HWIO_VOTETABLE_DRV12_ND8_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND8_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND8_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND8_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND8_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND8_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND8_IN)
#define HWIO_VOTETABLE_DRV12_ND8_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV12_ND8_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV12_ND8_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV12_ND8_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV12_ND8_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV12_ND8_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV12_ND8_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV12_ND8_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV12_ND8_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV12_ND8_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV12_ND9_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000c0024)
#define HWIO_VOTETABLE_DRV12_ND9_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV12_ND9_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND9_ADDR)
#define HWIO_VOTETABLE_DRV12_ND9_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND9_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND9_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND9_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND9_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND9_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND9_IN)
#define HWIO_VOTETABLE_DRV12_ND9_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV12_ND9_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV12_ND9_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV12_ND9_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV12_ND9_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV12_ND9_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV12_ND9_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV12_ND9_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV12_ND9_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV12_ND9_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV12_ND12_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0030)
#define HWIO_VOTETABLE_DRV12_ND12_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND12_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND12_ADDR)
#define HWIO_VOTETABLE_DRV12_ND12_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND12_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND12_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND12_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND12_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND12_IN)
#define HWIO_VOTETABLE_DRV12_ND12_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND12_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND12_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND12_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND12_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND12_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND12_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND12_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND12_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND12_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND13_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0034)
#define HWIO_VOTETABLE_DRV12_ND13_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND13_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND13_ADDR)
#define HWIO_VOTETABLE_DRV12_ND13_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND13_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND13_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND13_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND13_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND13_IN)
#define HWIO_VOTETABLE_DRV12_ND13_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND13_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND13_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND13_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND13_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND13_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND13_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND13_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND13_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND13_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND14_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0038)
#define HWIO_VOTETABLE_DRV12_ND14_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND14_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND14_ADDR)
#define HWIO_VOTETABLE_DRV12_ND14_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND14_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND14_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND14_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND14_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND14_IN)
#define HWIO_VOTETABLE_DRV12_ND14_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND14_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND14_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND14_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND14_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND14_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND14_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND14_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND14_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND14_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND15_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c003c)
#define HWIO_VOTETABLE_DRV12_ND15_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND15_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND15_ADDR)
#define HWIO_VOTETABLE_DRV12_ND15_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND15_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND15_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND15_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND15_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND15_IN)
#define HWIO_VOTETABLE_DRV12_ND15_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND15_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND15_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND15_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND15_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND15_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND15_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND15_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND15_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND15_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND16_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0040)
#define HWIO_VOTETABLE_DRV12_ND16_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND16_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND16_ADDR)
#define HWIO_VOTETABLE_DRV12_ND16_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND16_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND16_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND16_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND16_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND16_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND16_IN)
#define HWIO_VOTETABLE_DRV12_ND16_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND16_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND16_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND16_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND16_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND16_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND16_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND16_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND16_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND16_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND18_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0048)
#define HWIO_VOTETABLE_DRV12_ND18_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND18_ADDR)
#define HWIO_VOTETABLE_DRV12_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND18_IN)
#define HWIO_VOTETABLE_DRV12_ND18_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND18_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND18_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND18_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND18_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND18_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND18_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND18_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND18_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND18_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND19_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c004c)
#define HWIO_VOTETABLE_DRV12_ND19_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND19_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND19_ADDR)
#define HWIO_VOTETABLE_DRV12_ND19_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND19_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND19_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND19_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND19_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND19_IN)
#define HWIO_VOTETABLE_DRV12_ND19_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND19_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND19_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND19_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND19_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND19_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND19_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND19_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND19_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND19_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND20_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0050)
#define HWIO_VOTETABLE_DRV12_ND20_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND20_ADDR)
#define HWIO_VOTETABLE_DRV12_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND20_IN)
#define HWIO_VOTETABLE_DRV12_ND20_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND20_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND20_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND20_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND20_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND20_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND20_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND20_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND20_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND20_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND21_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0054)
#define HWIO_VOTETABLE_DRV12_ND21_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND21_ADDR)
#define HWIO_VOTETABLE_DRV12_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND21_IN)
#define HWIO_VOTETABLE_DRV12_ND21_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND21_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND21_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND21_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND21_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND21_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND21_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND21_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND21_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND21_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND22_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0058)
#define HWIO_VOTETABLE_DRV12_ND22_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND22_ADDR)
#define HWIO_VOTETABLE_DRV12_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND22_IN)
#define HWIO_VOTETABLE_DRV12_ND22_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND22_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND22_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND22_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND22_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND22_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND22_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND22_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND22_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND22_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND23_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c005c)
#define HWIO_VOTETABLE_DRV12_ND23_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND23_ADDR)
#define HWIO_VOTETABLE_DRV12_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND23_IN)
#define HWIO_VOTETABLE_DRV12_ND23_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND23_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND23_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND23_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND23_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND23_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND23_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND23_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND23_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND23_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND24_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0060)
#define HWIO_VOTETABLE_DRV12_ND24_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND24_ADDR)
#define HWIO_VOTETABLE_DRV12_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND24_IN)
#define HWIO_VOTETABLE_DRV12_ND24_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND24_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND24_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND24_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND24_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND24_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND24_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND24_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND24_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND24_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND25_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0064)
#define HWIO_VOTETABLE_DRV12_ND25_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND25_ADDR)
#define HWIO_VOTETABLE_DRV12_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND25_IN)
#define HWIO_VOTETABLE_DRV12_ND25_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND25_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND25_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND25_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND25_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND25_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND25_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND25_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND25_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND25_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND26_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0068)
#define HWIO_VOTETABLE_DRV12_ND26_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND26_ADDR)
#define HWIO_VOTETABLE_DRV12_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND26_IN)
#define HWIO_VOTETABLE_DRV12_ND26_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND26_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND26_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND26_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND26_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND26_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND26_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND26_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND26_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND26_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND27_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c006c)
#define HWIO_VOTETABLE_DRV12_ND27_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND27_ADDR)
#define HWIO_VOTETABLE_DRV12_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND27_IN)
#define HWIO_VOTETABLE_DRV12_ND27_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND27_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND27_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND27_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND27_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND27_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND27_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND27_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND27_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND27_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND30_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c0078)
#define HWIO_VOTETABLE_DRV12_ND30_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND30_ADDR)
#define HWIO_VOTETABLE_DRV12_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND30_IN)
#define HWIO_VOTETABLE_DRV12_ND30_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND30_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND30_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND30_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND30_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND30_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND30_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND30_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND30_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND30_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV12_ND31_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000c007c)
#define HWIO_VOTETABLE_DRV12_ND31_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV12_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV12_ND31_ADDR)
#define HWIO_VOTETABLE_DRV12_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV12_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV12_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV12_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV12_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV12_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV12_ND31_IN)
#define HWIO_VOTETABLE_DRV12_ND31_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV12_ND31_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV12_ND31_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV12_ND31_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV12_ND31_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV12_ND31_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV12_ND31_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV12_ND31_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV12_ND31_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV12_ND31_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND0_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000d0000)
#define HWIO_VOTETABLE_DRV13_ND0_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV13_ND0_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND0_ADDR)
#define HWIO_VOTETABLE_DRV13_ND0_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND0_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND0_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND0_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND0_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND0_IN)
#define HWIO_VOTETABLE_DRV13_ND0_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV13_ND0_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV13_ND0_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV13_ND0_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV13_ND0_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV13_ND0_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV13_ND0_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV13_ND0_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV13_ND0_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV13_ND0_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV13_ND1_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000d0004)
#define HWIO_VOTETABLE_DRV13_ND1_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV13_ND1_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND1_ADDR)
#define HWIO_VOTETABLE_DRV13_ND1_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND1_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND1_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND1_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND1_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND1_IN)
#define HWIO_VOTETABLE_DRV13_ND1_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV13_ND1_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV13_ND1_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV13_ND1_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV13_ND1_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV13_ND1_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV13_ND1_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV13_ND1_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV13_ND1_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV13_ND1_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV13_ND2_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000d0008)
#define HWIO_VOTETABLE_DRV13_ND2_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV13_ND2_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND2_ADDR)
#define HWIO_VOTETABLE_DRV13_ND2_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND2_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND2_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND2_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND2_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND2_IN)
#define HWIO_VOTETABLE_DRV13_ND2_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV13_ND2_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV13_ND2_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV13_ND2_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV13_ND2_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV13_ND2_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV13_ND2_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV13_ND2_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV13_ND2_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV13_ND2_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV13_ND3_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000d000c)
#define HWIO_VOTETABLE_DRV13_ND3_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV13_ND3_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND3_ADDR)
#define HWIO_VOTETABLE_DRV13_ND3_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND3_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND3_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND3_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND3_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND3_IN)
#define HWIO_VOTETABLE_DRV13_ND3_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV13_ND3_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV13_ND3_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV13_ND3_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV13_ND3_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV13_ND3_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV13_ND3_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV13_ND3_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV13_ND3_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV13_ND3_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV13_ND4_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000d0010)
#define HWIO_VOTETABLE_DRV13_ND4_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV13_ND4_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND4_ADDR)
#define HWIO_VOTETABLE_DRV13_ND4_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND4_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND4_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND4_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND4_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND4_IN)
#define HWIO_VOTETABLE_DRV13_ND4_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV13_ND4_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV13_ND4_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV13_ND4_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV13_ND4_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV13_ND4_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV13_ND4_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV13_ND4_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV13_ND4_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV13_ND4_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV13_ND5_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000d0014)
#define HWIO_VOTETABLE_DRV13_ND5_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV13_ND5_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND5_ADDR)
#define HWIO_VOTETABLE_DRV13_ND5_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND5_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND5_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND5_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND5_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND5_IN)
#define HWIO_VOTETABLE_DRV13_ND5_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV13_ND5_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV13_ND5_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV13_ND5_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV13_ND5_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV13_ND5_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV13_ND5_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV13_ND5_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV13_ND5_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV13_ND5_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV13_ND6_ADDR                                                       (BCM_VOTETABLE_REG_BASE      + 0x000d0018)
#define HWIO_VOTETABLE_DRV13_ND6_RMSK                                                       0xefffffff
#define HWIO_VOTETABLE_DRV13_ND6_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND6_ADDR)
#define HWIO_VOTETABLE_DRV13_ND6_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND6_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND6_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND6_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND6_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND6_IN)
#define HWIO_VOTETABLE_DRV13_ND6_RESP_REQ_BMSK                                              0x80000000
#define HWIO_VOTETABLE_DRV13_ND6_RESP_REQ_SHFT                                                    0x1f
#define HWIO_VOTETABLE_DRV13_ND6_COMMIT_BMSK                                                0x40000000
#define HWIO_VOTETABLE_DRV13_ND6_COMMIT_SHFT                                                      0x1e
#define HWIO_VOTETABLE_DRV13_ND6_VOTE_VALID_BMSK                                            0x20000000
#define HWIO_VOTETABLE_DRV13_ND6_VOTE_VALID_SHFT                                                  0x1d
#define HWIO_VOTETABLE_DRV13_ND6_VOTE_X_BMSK                                                 0xfffc000
#define HWIO_VOTETABLE_DRV13_ND6_VOTE_X_SHFT                                                       0xe
#define HWIO_VOTETABLE_DRV13_ND6_VOTE_Y_BMSK                                                    0x3fff
#define HWIO_VOTETABLE_DRV13_ND6_VOTE_Y_SHFT                                                       0x0

#define HWIO_VOTETABLE_DRV13_ND12_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0030)
#define HWIO_VOTETABLE_DRV13_ND12_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND12_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND12_ADDR)
#define HWIO_VOTETABLE_DRV13_ND12_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND12_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND12_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND12_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND12_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND12_IN)
#define HWIO_VOTETABLE_DRV13_ND12_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND12_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND12_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND12_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND12_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND12_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND12_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND12_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND12_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND12_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND13_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0034)
#define HWIO_VOTETABLE_DRV13_ND13_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND13_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND13_ADDR)
#define HWIO_VOTETABLE_DRV13_ND13_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND13_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND13_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND13_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND13_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND13_IN)
#define HWIO_VOTETABLE_DRV13_ND13_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND13_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND13_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND13_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND13_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND13_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND13_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND13_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND13_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND13_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND14_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0038)
#define HWIO_VOTETABLE_DRV13_ND14_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND14_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND14_ADDR)
#define HWIO_VOTETABLE_DRV13_ND14_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND14_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND14_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND14_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND14_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND14_IN)
#define HWIO_VOTETABLE_DRV13_ND14_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND14_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND14_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND14_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND14_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND14_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND14_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND14_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND14_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND14_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND15_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d003c)
#define HWIO_VOTETABLE_DRV13_ND15_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND15_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND15_ADDR)
#define HWIO_VOTETABLE_DRV13_ND15_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND15_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND15_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND15_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND15_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND15_IN)
#define HWIO_VOTETABLE_DRV13_ND15_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND15_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND15_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND15_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND15_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND15_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND15_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND15_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND15_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND15_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND16_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0040)
#define HWIO_VOTETABLE_DRV13_ND16_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND16_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND16_ADDR)
#define HWIO_VOTETABLE_DRV13_ND16_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND16_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND16_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND16_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND16_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND16_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND16_IN)
#define HWIO_VOTETABLE_DRV13_ND16_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND16_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND16_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND16_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND16_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND16_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND16_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND16_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND16_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND16_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND18_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0048)
#define HWIO_VOTETABLE_DRV13_ND18_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND18_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND18_ADDR)
#define HWIO_VOTETABLE_DRV13_ND18_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND18_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND18_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND18_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND18_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND18_IN)
#define HWIO_VOTETABLE_DRV13_ND18_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND18_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND18_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND18_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND18_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND18_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND18_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND18_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND18_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND18_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND19_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d004c)
#define HWIO_VOTETABLE_DRV13_ND19_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND19_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND19_ADDR)
#define HWIO_VOTETABLE_DRV13_ND19_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND19_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND19_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND19_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND19_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND19_IN)
#define HWIO_VOTETABLE_DRV13_ND19_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND19_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND19_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND19_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND19_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND19_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND19_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND19_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND19_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND19_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND20_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0050)
#define HWIO_VOTETABLE_DRV13_ND20_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND20_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND20_ADDR)
#define HWIO_VOTETABLE_DRV13_ND20_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND20_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND20_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND20_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND20_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND20_IN)
#define HWIO_VOTETABLE_DRV13_ND20_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND20_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND20_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND20_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND20_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND20_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND20_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND20_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND20_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND20_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND21_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0054)
#define HWIO_VOTETABLE_DRV13_ND21_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND21_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND21_ADDR)
#define HWIO_VOTETABLE_DRV13_ND21_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND21_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND21_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND21_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND21_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND21_IN)
#define HWIO_VOTETABLE_DRV13_ND21_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND21_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND21_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND21_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND21_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND21_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND21_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND21_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND21_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND21_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND22_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0058)
#define HWIO_VOTETABLE_DRV13_ND22_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND22_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND22_ADDR)
#define HWIO_VOTETABLE_DRV13_ND22_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND22_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND22_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND22_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND22_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND22_IN)
#define HWIO_VOTETABLE_DRV13_ND22_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND22_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND22_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND22_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND22_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND22_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND22_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND22_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND22_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND22_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND23_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d005c)
#define HWIO_VOTETABLE_DRV13_ND23_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND23_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND23_ADDR)
#define HWIO_VOTETABLE_DRV13_ND23_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND23_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND23_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND23_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND23_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND23_IN)
#define HWIO_VOTETABLE_DRV13_ND23_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND23_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND23_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND23_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND23_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND23_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND23_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND23_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND23_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND23_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND24_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0060)
#define HWIO_VOTETABLE_DRV13_ND24_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND24_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND24_ADDR)
#define HWIO_VOTETABLE_DRV13_ND24_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND24_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND24_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND24_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND24_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND24_IN)
#define HWIO_VOTETABLE_DRV13_ND24_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND24_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND24_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND24_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND24_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND24_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND24_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND24_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND24_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND24_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND25_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0064)
#define HWIO_VOTETABLE_DRV13_ND25_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND25_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND25_ADDR)
#define HWIO_VOTETABLE_DRV13_ND25_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND25_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND25_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND25_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND25_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND25_IN)
#define HWIO_VOTETABLE_DRV13_ND25_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND25_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND25_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND25_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND25_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND25_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND25_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND25_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND25_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND25_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND26_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0068)
#define HWIO_VOTETABLE_DRV13_ND26_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND26_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND26_ADDR)
#define HWIO_VOTETABLE_DRV13_ND26_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND26_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND26_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND26_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND26_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND26_IN)
#define HWIO_VOTETABLE_DRV13_ND26_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND26_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND26_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND26_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND26_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND26_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND26_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND26_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND26_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND26_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND27_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d006c)
#define HWIO_VOTETABLE_DRV13_ND27_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND27_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND27_ADDR)
#define HWIO_VOTETABLE_DRV13_ND27_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND27_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND27_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND27_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND27_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND27_IN)
#define HWIO_VOTETABLE_DRV13_ND27_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND27_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND27_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND27_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND27_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND27_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND27_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND27_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND27_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND27_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND30_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d0078)
#define HWIO_VOTETABLE_DRV13_ND30_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND30_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND30_ADDR)
#define HWIO_VOTETABLE_DRV13_ND30_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND30_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND30_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND30_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND30_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND30_IN)
#define HWIO_VOTETABLE_DRV13_ND30_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND30_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND30_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND30_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND30_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND30_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND30_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND30_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND30_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND30_VOTE_Y_SHFT                                                      0x0

#define HWIO_VOTETABLE_DRV13_ND31_ADDR                                                      (BCM_VOTETABLE_REG_BASE      + 0x000d007c)
#define HWIO_VOTETABLE_DRV13_ND31_RMSK                                                      0xefffffff
#define HWIO_VOTETABLE_DRV13_ND31_IN          \
        in_dword(HWIO_VOTETABLE_DRV13_ND31_ADDR)
#define HWIO_VOTETABLE_DRV13_ND31_INM(m)      \
        in_dword_masked(HWIO_VOTETABLE_DRV13_ND31_ADDR, m)
#define HWIO_VOTETABLE_DRV13_ND31_OUT(v)      \
        out_dword(HWIO_VOTETABLE_DRV13_ND31_ADDR,v)
#define HWIO_VOTETABLE_DRV13_ND31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRV13_ND31_ADDR,m,v,HWIO_VOTETABLE_DRV13_ND31_IN)
#define HWIO_VOTETABLE_DRV13_ND31_RESP_REQ_BMSK                                             0x80000000
#define HWIO_VOTETABLE_DRV13_ND31_RESP_REQ_SHFT                                                   0x1f
#define HWIO_VOTETABLE_DRV13_ND31_COMMIT_BMSK                                               0x40000000
#define HWIO_VOTETABLE_DRV13_ND31_COMMIT_SHFT                                                     0x1e
#define HWIO_VOTETABLE_DRV13_ND31_VOTE_VALID_BMSK                                           0x20000000
#define HWIO_VOTETABLE_DRV13_ND31_VOTE_VALID_SHFT                                                 0x1d
#define HWIO_VOTETABLE_DRV13_ND31_VOTE_X_BMSK                                                0xfffc000
#define HWIO_VOTETABLE_DRV13_ND31_VOTE_X_SHFT                                                      0xe
#define HWIO_VOTETABLE_DRV13_ND31_VOTE_Y_BMSK                                                   0x3fff
#define HWIO_VOTETABLE_DRV13_ND31_VOTE_Y_SHFT                                                      0x0

#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_ADDR(r)                                          (BCM_VOTETABLE_REG_BASE      + 0x00000200 + 0x10000 * (r))
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_RMSK                                                  0xfff
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_MAXr                                                     13
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_INI(r)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_ADDR(r), HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_INMI(r,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_ADDR(r), mask)
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_AGG_BUSY_CD_BMSK                                      0xfff
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_AGG_BUSY_CD_SHFT                                        0x0

#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_ADDR(r,m)                                            (BCM_VOTETABLE_REG_BASE      + 0x00000204 + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_RMSK                                                 0x7fff10ff
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_MAXr                                                         13
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_MAXm                                                         11
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_FE_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_FE_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_FE_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_AGG_BW_BMSK                                          0x7fff0000
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_AGG_BW_SHFT                                                0x10
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_COMMIT_CD_RAW_BMSK                                       0x1000
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_COMMIT_CD_RAW_SHFT                                          0xc
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_FINAL_CP_BMSK                                              0xf0
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_FINAL_CP_SHFT                                               0x4
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_AGG_CP_BMSK                                                 0xf
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_AGG_CP_SHFT                                                 0x0

#define HWIO_SHADOW_STATUS_DRVr_DIRTY_ND_0_ADDR(r)                                          (BCM_VOTETABLE_REG_BASE      + 0x00000284 + 0x10000 * (r))
#define HWIO_SHADOW_STATUS_DRVr_DIRTY_ND_0_RMSK                                             0xffffffff
#define HWIO_SHADOW_STATUS_DRVr_DIRTY_ND_0_MAXr                                                     13
#define HWIO_SHADOW_STATUS_DRVr_DIRTY_ND_0_INI(r)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_DIRTY_ND_0_ADDR(r), HWIO_SHADOW_STATUS_DRVr_DIRTY_ND_0_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_DIRTY_ND_0_INMI(r,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_DIRTY_ND_0_ADDR(r), mask)
#define HWIO_SHADOW_STATUS_DRVr_DIRTY_ND_0_DIRTY_ND_31_0_BMSK                               0xffffffff
#define HWIO_SHADOW_STATUS_DRVr_DIRTY_ND_0_DIRTY_ND_31_0_SHFT                                      0x0

#define HWIO_SHADOW_STATUS_DRVr_SNDs_ADDR(r,s)                                              (BCM_VOTETABLE_REG_BASE      + 0x0000028c + 0x10000 * (r) + 0x4 * (s))
#define HWIO_SHADOW_STATUS_DRVr_SNDs_RMSK                                                       0xffff
#define HWIO_SHADOW_STATUS_DRVr_SNDs_MAXr                                                           13
#define HWIO_SHADOW_STATUS_DRVr_SNDs_MAXs                                                            3
#define HWIO_SHADOW_STATUS_DRVr_SNDs_INI2(r,s)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_SNDs_ADDR(r,s), HWIO_SHADOW_STATUS_DRVr_SNDs_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_SNDs_INMI2(r,s,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_SNDs_ADDR(r,s), mask)
#define HWIO_SHADOW_STATUS_DRVr_SNDs_SEL_BIT_VEC_BMSK                                           0xffff
#define HWIO_SHADOW_STATUS_DRVr_SNDs_SEL_BIT_VEC_SHFT                                              0x0

#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_NDd_ADDR(r,d)                                        (BCM_VOTETABLE_REG_BASE      + 0x0000029c + 0x10000 * (r) + 0x4 * (d))
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_NDd_RMSK                                                 0x7fff
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_NDd_MAXr                                                     13
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_NDd_MAXd                                                     31
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_NDd_INI2(r,d)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_AGG_BW_NDd_ADDR(r,d), HWIO_SHADOW_STATUS_DRVr_AGG_BW_NDd_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_NDd_INMI2(r,d,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_AGG_BW_NDd_ADDR(r,d), mask)
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_NDd_AGG_BW_BMSK                                          0x7fff
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_NDd_AGG_BW_SHFT                                             0x0

#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_Z_NDs_ADDR(r,s)                                      (BCM_VOTETABLE_REG_BASE      + 0x0000049c + 0x10000 * (r) + 0x4 * (s))
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_Z_NDs_RMSK                                               0x7fff
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_Z_NDs_MAXr                                                   13
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_Z_NDs_MAXs                                                    3
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_Z_NDs_INI2(r,s)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_AGG_BW_Z_NDs_ADDR(r,s), HWIO_SHADOW_STATUS_DRVr_AGG_BW_Z_NDs_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_Z_NDs_INMI2(r,s,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_AGG_BW_Z_NDs_ADDR(r,s), mask)
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_Z_NDs_AGG_BW_Z_BMSK                                      0x7fff
#define HWIO_SHADOW_STATUS_DRVr_AGG_BW_Z_NDs_AGG_BW_Z_SHFT                                         0x0

#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_ADDR(r,m)                                            (BCM_VOTETABLE_REG_BASE      + 0x000004ac + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_RMSK                                                    0xfffff
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_MAXr                                                         13
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_MAXm                                                         11
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_BE_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_CLK_DEST_STATE_BMSK                                     0xf0000
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_CLK_DEST_STATE_SHFT                                        0x10
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_COMBINED_CP_BMSK                                         0xf000
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_COMBINED_CP_SHFT                                            0xc
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_SW_CP_SNAP_BMSK                                           0xf00
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_SW_CP_SNAP_SHFT                                             0x8
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_WRITTEN_CP_BMSK                                            0xf0
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_WRITTEN_CP_SHFT                                             0x4
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_CURR_CP_BMSK                                                0xf
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_CURR_CP_SHFT                                                0x0

#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_ADDR(r,m)                                        (BCM_VOTETABLE_REG_BASE      + 0x0000052c + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_RMSK                                                0x1ff01
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_MAXr                                                     13
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_MAXm                                                     11
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_SEQ_CURR_PC_BMSK                                    0x1ff00
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_SEQ_CURR_PC_SHFT                                        0x8
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_SEQ_STATE_BMSK                                          0x1
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_SEQ_STATE_SHFT                                          0x0

#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_ADDR(r,m)                           (BCM_VOTETABLE_REG_BASE      + 0x000005ac + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_RMSK                                       0x7
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_MAXr                                        13
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_MAXm                                        11
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_ISSUE_STATUS_BMSK                          0x7
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_ISSUE_STATUS_SHFT                          0x0

#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_ADDR(r,m)                            (BCM_VOTETABLE_REG_BASE      + 0x0000062c + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_RMSK                                        0x7
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_MAXr                                         13
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_MAXm                                         11
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_SENT_STATUS_BMSK                            0x7
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_SENT_STATUS_SHFT                            0x0

#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_ADDR(r,m)                            (BCM_VOTETABLE_REG_BASE      + 0x000006ac + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_RMSK                                        0x7
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_MAXr                                         13
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_MAXm                                         11
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_CMPL_STATUS_BMSK                            0x7
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_CMPL_STATUS_SHFT                            0x0

#define HWIO_SHADOW_STATUS_DRVr_BE_TCS_STATUS_CDm_ADDR(r,m)                                 (BCM_VOTETABLE_REG_BASE      + 0x0000072c + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_BE_TCS_STATUS_CDm_RMSK                                             0x7
#define HWIO_SHADOW_STATUS_DRVr_BE_TCS_STATUS_CDm_MAXr                                              13
#define HWIO_SHADOW_STATUS_DRVr_BE_TCS_STATUS_CDm_MAXm                                              11
#define HWIO_SHADOW_STATUS_DRVr_BE_TCS_STATUS_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_TCS_STATUS_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_BE_TCS_STATUS_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BE_TCS_STATUS_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_TCS_STATUS_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_BE_TCS_STATUS_CDm_TCS_CURR_STATE_BMSK                              0x7
#define HWIO_SHADOW_STATUS_DRVr_BE_TCS_STATUS_CDm_TCS_CURR_STATE_SHFT                              0x0

#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_ADDR(r)                                        (BCM_VOTETABLE_REG_BASE      + 0x0000081c + 0x10000 * (r))
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_RMSK                                             0x3fff01
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_MAXr                                                   13
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_INI(r)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_ADDR(r), HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_INMI(r,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_ADDR(r), mask)
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_CTT_EMPTY_DRV_BMSK                               0x3fff00
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_CTT_EMPTY_DRV_SHFT                                    0x8
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_CTT_EMPTY_BMSK                                        0x1
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_CTT_EMPTY_SHFT                                        0x0

#define HWIO_SHADOW_STATUS_DRVr_BCM_ADDR(r)                                                 (BCM_VOTETABLE_REG_BASE      + 0x00000820 + 0x10000 * (r))
#define HWIO_SHADOW_STATUS_DRVr_BCM_RMSK                                                           0x1
#define HWIO_SHADOW_STATUS_DRVr_BCM_MAXr                                                            13
#define HWIO_SHADOW_STATUS_DRVr_BCM_INI(r)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BCM_ADDR(r), HWIO_SHADOW_STATUS_DRVr_BCM_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BCM_INMI(r,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BCM_ADDR(r), mask)
#define HWIO_SHADOW_STATUS_DRVr_BCM_BCM_IDLE_BMSK                                                  0x1
#define HWIO_SHADOW_STATUS_DRVr_BCM_BCM_IDLE_SHFT                                                  0x0

#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_ADDR(r)                                          (BCM_VOTETABLE_REG_BASE      + 0x00000824 + 0x10000 * (r))
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_RMSK                                               0xffffff
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_MAXr                                                     13
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_INI(r)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_HW_VERSION_ADDR(r), HWIO_SHADOW_STATUS_DRVr_HW_VERSION_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_INMI(r,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_HW_VERSION_ADDR(r), mask)
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_MAJOR_BMSK                                         0xff0000
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_MAJOR_SHFT                                             0x10
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_MINOR_BMSK                                           0xff00
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_MINOR_SHFT                                              0x8
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_STEP_BMSK                                              0xff
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_STEP_SHFT                                               0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_ND_CFG
 *--------------------------------------------------------------------------*/

#define BCM_ND_CFG_REG_BASE                                             (AOSS_BASE      + 0x00be0000)
#define BCM_ND_CFG_REG_BASE_SIZE                                        0x3000
#define BCM_ND_CFG_REG_BASE_USED                                        0x8fc

#define HWIO_ND_CFG_NDd_ADDR(d)                                         (BCM_ND_CFG_REG_BASE      + 0x00000000 + 0x4 * (d))
#define HWIO_ND_CFG_NDd_RMSK                                                 0x1ff
#define HWIO_ND_CFG_NDd_MAXd                                                    31
#define HWIO_ND_CFG_NDd_INI(d)        \
        in_dword_masked(HWIO_ND_CFG_NDd_ADDR(d), HWIO_ND_CFG_NDd_RMSK)
#define HWIO_ND_CFG_NDd_INMI(d,mask)    \
        in_dword_masked(HWIO_ND_CFG_NDd_ADDR(d), mask)
#define HWIO_ND_CFG_NDd_OUTI(d,val)    \
        out_dword(HWIO_ND_CFG_NDd_ADDR(d),val)
#define HWIO_ND_CFG_NDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_ND_CFG_NDd_ADDR(d),mask,val,HWIO_ND_CFG_NDd_INI(d))
#define HWIO_ND_CFG_NDd_ND_ALGO_SEL_BMSK                                     0x1f0
#define HWIO_ND_CFG_NDd_ND_ALGO_SEL_SHFT                                       0x4
#define HWIO_ND_CFG_NDd_CLOCK_DOMAIN_ID_BMSK                                   0xf
#define HWIO_ND_CFG_NDd_CLOCK_DOMAIN_ID_SHFT                                   0x0

#define HWIO_SND_CFG_SNDs_ADDR(s)                                       (BCM_ND_CFG_REG_BASE      + 0x00000200 + 0x4 * (s))
#define HWIO_SND_CFG_SNDs_RMSK                                                0x3f
#define HWIO_SND_CFG_SNDs_MAXs                                                   3
#define HWIO_SND_CFG_SNDs_INI(s)        \
        in_dword_masked(HWIO_SND_CFG_SNDs_ADDR(s), HWIO_SND_CFG_SNDs_RMSK)
#define HWIO_SND_CFG_SNDs_INMI(s,mask)    \
        in_dword_masked(HWIO_SND_CFG_SNDs_ADDR(s), mask)
#define HWIO_SND_CFG_SNDs_OUTI(s,val)    \
        out_dword(HWIO_SND_CFG_SNDs_ADDR(s),val)
#define HWIO_SND_CFG_SNDs_OUTMI(s,mask,val) \
        out_dword_masked_ns(HWIO_SND_CFG_SNDs_ADDR(s),mask,val,HWIO_SND_CFG_SNDs_INI(s))
#define HWIO_SND_CFG_SNDs_Z_ND_ASSOCIATION_BMSK                               0x3f
#define HWIO_SND_CFG_SNDs_Z_ND_ASSOCIATION_SHFT                                0x0

#define HWIO_SND_LUT_SNDs_COLc_ADDR(s,c)                                (BCM_ND_CFG_REG_BASE      + 0x00000300 + 0x10 * (s) + 0x4 * (c))
#define HWIO_SND_LUT_SNDs_COLc_RMSK                                         0x3fff
#define HWIO_SND_LUT_SNDs_COLc_MAXs                                              3
#define HWIO_SND_LUT_SNDs_COLc_MAXc                                              3
#define HWIO_SND_LUT_SNDs_COLc_INI2(s,c)        \
        in_dword_masked(HWIO_SND_LUT_SNDs_COLc_ADDR(s,c), HWIO_SND_LUT_SNDs_COLc_RMSK)
#define HWIO_SND_LUT_SNDs_COLc_INMI2(s,c,mask)    \
        in_dword_masked(HWIO_SND_LUT_SNDs_COLc_ADDR(s,c), mask)
#define HWIO_SND_LUT_SNDs_COLc_OUTI2(s,c,val)    \
        out_dword(HWIO_SND_LUT_SNDs_COLc_ADDR(s,c),val)
#define HWIO_SND_LUT_SNDs_COLc_OUTMI2(s,c,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SNDs_COLc_ADDR(s,c),mask,val,HWIO_SND_LUT_SNDs_COLc_INI2(s,c))
#define HWIO_SND_LUT_SNDs_COLc_COL_THRESHOLD_BMSK                           0x3fff
#define HWIO_SND_LUT_SNDs_COLc_COL_THRESHOLD_SHFT                              0x0

#define HWIO_SND_LUT_SND0_COLc_CPn_ADDR(c,n)                            (BCM_ND_CFG_REG_BASE      + 0x00000500 + 0x40 * (c) + 0x4 * (n))
#define HWIO_SND_LUT_SND0_COLc_CPn_RMSK                                     0x3fff
#define HWIO_SND_LUT_SND0_COLc_CPn_MAXc                                          3
#define HWIO_SND_LUT_SND0_COLc_CPn_MAXn                                         15
#define HWIO_SND_LUT_SND0_COLc_CPn_INI2(c,n)        \
        in_dword_masked(HWIO_SND_LUT_SND0_COLc_CPn_ADDR(c,n), HWIO_SND_LUT_SND0_COLc_CPn_RMSK)
#define HWIO_SND_LUT_SND0_COLc_CPn_INMI2(c,n,mask)    \
        in_dword_masked(HWIO_SND_LUT_SND0_COLc_CPn_ADDR(c,n), mask)
#define HWIO_SND_LUT_SND0_COLc_CPn_OUTI2(c,n,val)    \
        out_dword(HWIO_SND_LUT_SND0_COLc_CPn_ADDR(c,n),val)
#define HWIO_SND_LUT_SND0_COLc_CPn_OUTMI2(c,n,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SND0_COLc_CPn_ADDR(c,n),mask,val,HWIO_SND_LUT_SND0_COLc_CPn_INI2(c,n))
#define HWIO_SND_LUT_SND0_COLc_CPn_ROW_THRESHOLD_BMSK                       0x3fff
#define HWIO_SND_LUT_SND0_COLc_CPn_ROW_THRESHOLD_SHFT                          0x0

#define HWIO_SND_LUT_SND1_COLc_CPn_ADDR(c,n)                            (BCM_ND_CFG_REG_BASE      + 0x00000600 + 0x40 * (c) + 0x4 * (n))
#define HWIO_SND_LUT_SND1_COLc_CPn_RMSK                                     0x3fff
#define HWIO_SND_LUT_SND1_COLc_CPn_MAXc                                          3
#define HWIO_SND_LUT_SND1_COLc_CPn_MAXn                                          7
#define HWIO_SND_LUT_SND1_COLc_CPn_INI2(c,n)        \
        in_dword_masked(HWIO_SND_LUT_SND1_COLc_CPn_ADDR(c,n), HWIO_SND_LUT_SND1_COLc_CPn_RMSK)
#define HWIO_SND_LUT_SND1_COLc_CPn_INMI2(c,n,mask)    \
        in_dword_masked(HWIO_SND_LUT_SND1_COLc_CPn_ADDR(c,n), mask)
#define HWIO_SND_LUT_SND1_COLc_CPn_OUTI2(c,n,val)    \
        out_dword(HWIO_SND_LUT_SND1_COLc_CPn_ADDR(c,n),val)
#define HWIO_SND_LUT_SND1_COLc_CPn_OUTMI2(c,n,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SND1_COLc_CPn_ADDR(c,n),mask,val,HWIO_SND_LUT_SND1_COLc_CPn_INI2(c,n))
#define HWIO_SND_LUT_SND1_COLc_CPn_ROW_THRESHOLD_BMSK                       0x3fff
#define HWIO_SND_LUT_SND1_COLc_CPn_ROW_THRESHOLD_SHFT                          0x0

#define HWIO_SND_LUT_SND2_COLc_CPn_ADDR(c,n)                            (BCM_ND_CFG_REG_BASE      + 0x00000700 + 0x40 * (c) + 0x4 * (n))
#define HWIO_SND_LUT_SND2_COLc_CPn_RMSK                                     0x3fff
#define HWIO_SND_LUT_SND2_COLc_CPn_MAXc                                          3
#define HWIO_SND_LUT_SND2_COLc_CPn_MAXn                                         15
#define HWIO_SND_LUT_SND2_COLc_CPn_INI2(c,n)        \
        in_dword_masked(HWIO_SND_LUT_SND2_COLc_CPn_ADDR(c,n), HWIO_SND_LUT_SND2_COLc_CPn_RMSK)
#define HWIO_SND_LUT_SND2_COLc_CPn_INMI2(c,n,mask)    \
        in_dword_masked(HWIO_SND_LUT_SND2_COLc_CPn_ADDR(c,n), mask)
#define HWIO_SND_LUT_SND2_COLc_CPn_OUTI2(c,n,val)    \
        out_dword(HWIO_SND_LUT_SND2_COLc_CPn_ADDR(c,n),val)
#define HWIO_SND_LUT_SND2_COLc_CPn_OUTMI2(c,n,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SND2_COLc_CPn_ADDR(c,n),mask,val,HWIO_SND_LUT_SND2_COLc_CPn_INI2(c,n))
#define HWIO_SND_LUT_SND2_COLc_CPn_ROW_THRESHOLD_BMSK                       0x3fff
#define HWIO_SND_LUT_SND2_COLc_CPn_ROW_THRESHOLD_SHFT                          0x0

#define HWIO_SND_LUT_SND3_COLc_CPn_ADDR(c,n)                            (BCM_ND_CFG_REG_BASE      + 0x00000800 + 0x40 * (c) + 0x4 * (n))
#define HWIO_SND_LUT_SND3_COLc_CPn_RMSK                                     0x3fff
#define HWIO_SND_LUT_SND3_COLc_CPn_MAXc                                          3
#define HWIO_SND_LUT_SND3_COLc_CPn_MAXn                                         15
#define HWIO_SND_LUT_SND3_COLc_CPn_INI2(c,n)        \
        in_dword_masked(HWIO_SND_LUT_SND3_COLc_CPn_ADDR(c,n), HWIO_SND_LUT_SND3_COLc_CPn_RMSK)
#define HWIO_SND_LUT_SND3_COLc_CPn_INMI2(c,n,mask)    \
        in_dword_masked(HWIO_SND_LUT_SND3_COLc_CPn_ADDR(c,n), mask)
#define HWIO_SND_LUT_SND3_COLc_CPn_OUTI2(c,n,val)    \
        out_dword(HWIO_SND_LUT_SND3_COLc_CPn_ADDR(c,n),val)
#define HWIO_SND_LUT_SND3_COLc_CPn_OUTMI2(c,n,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SND3_COLc_CPn_ADDR(c,n),mask,val,HWIO_SND_LUT_SND3_COLc_CPn_INI2(c,n))
#define HWIO_SND_LUT_SND3_COLc_CPn_ROW_THRESHOLD_BMSK                       0x3fff
#define HWIO_SND_LUT_SND3_COLc_CPn_ROW_THRESHOLD_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_CD_CFG
 *--------------------------------------------------------------------------*/

#define BCM_CD_CFG_REG_BASE                                     (AOSS_BASE      + 0x00be3000)
#define BCM_CD_CFG_REG_BASE_SIZE                                0x1000
#define BCM_CD_CFG_REG_BASE_USED                                0xafc

#define HWIO_CD_CFG_CDm_ADDR(m)                                 (BCM_CD_CFG_REG_BASE      + 0x00000000 + 0x4 * (m))
#define HWIO_CD_CFG_CDm_RMSK                                       0xf0f1f
#define HWIO_CD_CFG_CDm_MAXm                                            11
#define HWIO_CD_CFG_CDm_INI(m)        \
        in_dword_masked(HWIO_CD_CFG_CDm_ADDR(m), HWIO_CD_CFG_CDm_RMSK)
#define HWIO_CD_CFG_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_CD_CFG_CDm_ADDR(m), mask)
#define HWIO_CD_CFG_CDm_OUTI(m,val)    \
        out_dword(HWIO_CD_CFG_CDm_ADDR(m),val)
#define HWIO_CD_CFG_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_CD_CFG_CDm_ADDR(m),mask,val,HWIO_CD_CFG_CDm_INI(m))
#define HWIO_CD_CFG_CDm_PC_TH_BMSK                                 0xf0000
#define HWIO_CD_CFG_CDm_PC_TH_SHFT                                    0x10
#define HWIO_CD_CFG_CDm_DEPENDENT_CD_ID_BMSK                         0xf00
#define HWIO_CD_CFG_CDm_DEPENDENT_CD_ID_SHFT                           0x8
#define HWIO_CD_CFG_CDm_CD_ALGO_SEL_BMSK                              0x1f
#define HWIO_CD_CFG_CDm_CD_ALGO_SEL_SHFT                               0x0

#define HWIO_CD_CFG_ENABLE_CDm_ADDR(m)                          (BCM_CD_CFG_REG_BASE      + 0x00000080 + 0x4 * (m))
#define HWIO_CD_CFG_ENABLE_CDm_RMSK                                    0x1
#define HWIO_CD_CFG_ENABLE_CDm_MAXm                                     11
#define HWIO_CD_CFG_ENABLE_CDm_INI(m)        \
        in_dword_masked(HWIO_CD_CFG_ENABLE_CDm_ADDR(m), HWIO_CD_CFG_ENABLE_CDm_RMSK)
#define HWIO_CD_CFG_ENABLE_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_CD_CFG_ENABLE_CDm_ADDR(m), mask)
#define HWIO_CD_CFG_ENABLE_CDm_OUTI(m,val)    \
        out_dword(HWIO_CD_CFG_ENABLE_CDm_ADDR(m),val)
#define HWIO_CD_CFG_ENABLE_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_CD_CFG_ENABLE_CDm_ADDR(m),mask,val,HWIO_CD_CFG_ENABLE_CDm_INI(m))
#define HWIO_CD_CFG_ENABLE_CDm_SW_ENABLE_BMSK                          0x1
#define HWIO_CD_CFG_ENABLE_CDm_SW_ENABLE_SHFT                          0x0

#define HWIO_CD_CFG_CDm_AU_INPUTz_ADDR(m,z)                     (BCM_CD_CFG_REG_BASE      + 0x00000200 + 0x40 * (m) + 0x4 * (z))
#define HWIO_CD_CFG_CDm_AU_INPUTz_RMSK                                0x3f
#define HWIO_CD_CFG_CDm_AU_INPUTz_MAXm                                  11
#define HWIO_CD_CFG_CDm_AU_INPUTz_MAXz                                  15
#define HWIO_CD_CFG_CDm_AU_INPUTz_INI2(m,z)        \
        in_dword_masked(HWIO_CD_CFG_CDm_AU_INPUTz_ADDR(m,z), HWIO_CD_CFG_CDm_AU_INPUTz_RMSK)
#define HWIO_CD_CFG_CDm_AU_INPUTz_INMI2(m,z,mask)    \
        in_dword_masked(HWIO_CD_CFG_CDm_AU_INPUTz_ADDR(m,z), mask)
#define HWIO_CD_CFG_CDm_AU_INPUTz_OUTI2(m,z,val)    \
        out_dword(HWIO_CD_CFG_CDm_AU_INPUTz_ADDR(m,z),val)
#define HWIO_CD_CFG_CDm_AU_INPUTz_OUTMI2(m,z,mask,val) \
        out_dword_masked_ns(HWIO_CD_CFG_CDm_AU_INPUTz_ADDR(m,z),mask,val,HWIO_CD_CFG_CDm_AU_INPUTz_INI2(m,z))
#define HWIO_CD_CFG_CDm_AU_INPUTz_ND_ID_BMSK                          0x3f
#define HWIO_CD_CFG_CDm_AU_INPUTz_ND_ID_SHFT                           0x0

#define HWIO_CD_TH_CD0_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000800 + 0x4 * (n))
#define HWIO_CD_TH_CD0_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD0_CPn_MAXn                                         15
#define HWIO_CD_TH_CD0_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD0_CPn_ADDR(n), HWIO_CD_TH_CD0_CPn_RMSK)
#define HWIO_CD_TH_CD0_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD0_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD0_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD0_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD0_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD0_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD0_CPn_INI(n))
#define HWIO_CD_TH_CD0_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD0_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CDm_CPn_ADDR(m,n)                            (BCM_CD_CFG_REG_BASE      + 0x00000800 + 0x4 * (n) + 0x40 * (m))
#define HWIO_CD_TH_CDm_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CDm_CPn_MAXm                                         15
#define HWIO_CD_TH_CDm_CPn_MAXn                                         15
#define HWIO_CD_TH_CDm_CPn_INI2(m,n)        \
        in_dword_masked(HWIO_CD_TH_CDm_CPn_ADDR(m,n), HWIO_CD_TH_CDm_CPn_RMSK)
#define HWIO_CD_TH_CDm_CPn_INMI2(m,n,mask)    \
        in_dword_masked(HWIO_CD_TH_CDm_CPn_ADDR(m,n), mask)
#define HWIO_CD_TH_CDm_CPn_OUTI2(m,n,val)    \
        out_dword(HWIO_CD_TH_CDm_CPn_ADDR(m,n),val)
#define HWIO_CD_TH_CDm_CPn_OUTMI2(m,n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CDm_CPn_ADDR(m,n),mask,val,HWIO_CD_TH_CDm_CPn_INI2(m,n))
#define HWIO_CD_TH_CDm_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CDm_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD1_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000840 + 0x4 * (n))
#define HWIO_CD_TH_CD1_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD1_CPn_MAXn                                          7
#define HWIO_CD_TH_CD1_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD1_CPn_ADDR(n), HWIO_CD_TH_CD1_CPn_RMSK)
#define HWIO_CD_TH_CD1_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD1_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD1_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD1_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD1_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD1_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD1_CPn_INI(n))
#define HWIO_CD_TH_CD1_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD1_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD2_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000880 + 0x4 * (n))
#define HWIO_CD_TH_CD2_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD2_CPn_MAXn                                          7
#define HWIO_CD_TH_CD2_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD2_CPn_ADDR(n), HWIO_CD_TH_CD2_CPn_RMSK)
#define HWIO_CD_TH_CD2_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD2_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD2_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD2_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD2_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD2_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD2_CPn_INI(n))
#define HWIO_CD_TH_CD2_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD2_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD3_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x000008c0 + 0x4 * (n))
#define HWIO_CD_TH_CD3_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD3_CPn_MAXn                                          7
#define HWIO_CD_TH_CD3_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD3_CPn_ADDR(n), HWIO_CD_TH_CD3_CPn_RMSK)
#define HWIO_CD_TH_CD3_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD3_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD3_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD3_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD3_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD3_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD3_CPn_INI(n))
#define HWIO_CD_TH_CD3_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD3_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD4_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000900 + 0x4 * (n))
#define HWIO_CD_TH_CD4_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD4_CPn_MAXn                                          7
#define HWIO_CD_TH_CD4_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD4_CPn_ADDR(n), HWIO_CD_TH_CD4_CPn_RMSK)
#define HWIO_CD_TH_CD4_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD4_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD4_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD4_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD4_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD4_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD4_CPn_INI(n))
#define HWIO_CD_TH_CD4_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD4_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD5_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000940 + 0x4 * (n))
#define HWIO_CD_TH_CD5_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD5_CPn_MAXn                                          7
#define HWIO_CD_TH_CD5_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD5_CPn_ADDR(n), HWIO_CD_TH_CD5_CPn_RMSK)
#define HWIO_CD_TH_CD5_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD5_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD5_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD5_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD5_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD5_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD5_CPn_INI(n))
#define HWIO_CD_TH_CD5_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD5_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD6_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000980 + 0x4 * (n))
#define HWIO_CD_TH_CD6_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD6_CPn_MAXn                                          7
#define HWIO_CD_TH_CD6_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD6_CPn_ADDR(n), HWIO_CD_TH_CD6_CPn_RMSK)
#define HWIO_CD_TH_CD6_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD6_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD6_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD6_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD6_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD6_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD6_CPn_INI(n))
#define HWIO_CD_TH_CD6_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD6_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD7_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x000009c0 + 0x4 * (n))
#define HWIO_CD_TH_CD7_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD7_CPn_MAXn                                          7
#define HWIO_CD_TH_CD7_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD7_CPn_ADDR(n), HWIO_CD_TH_CD7_CPn_RMSK)
#define HWIO_CD_TH_CD7_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD7_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD7_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD7_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD7_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD7_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD7_CPn_INI(n))
#define HWIO_CD_TH_CD7_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD7_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD8_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000a00 + 0x4 * (n))
#define HWIO_CD_TH_CD8_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD8_CPn_MAXn                                          7
#define HWIO_CD_TH_CD8_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD8_CPn_ADDR(n), HWIO_CD_TH_CD8_CPn_RMSK)
#define HWIO_CD_TH_CD8_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD8_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD8_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD8_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD8_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD8_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD8_CPn_INI(n))
#define HWIO_CD_TH_CD8_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD8_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD9_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000a40 + 0x4 * (n))
#define HWIO_CD_TH_CD9_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD9_CPn_MAXn                                          7
#define HWIO_CD_TH_CD9_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD9_CPn_ADDR(n), HWIO_CD_TH_CD9_CPn_RMSK)
#define HWIO_CD_TH_CD9_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD9_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD9_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD9_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD9_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD9_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD9_CPn_INI(n))
#define HWIO_CD_TH_CD9_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD9_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD10_CPn_ADDR(n)                             (BCM_CD_CFG_REG_BASE      + 0x00000a80 + 0x4 * (n))
#define HWIO_CD_TH_CD10_CPn_RMSK                                    0x3fff
#define HWIO_CD_TH_CD10_CPn_MAXn                                        15
#define HWIO_CD_TH_CD10_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD10_CPn_ADDR(n), HWIO_CD_TH_CD10_CPn_RMSK)
#define HWIO_CD_TH_CD10_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD10_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD10_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD10_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD10_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD10_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD10_CPn_INI(n))
#define HWIO_CD_TH_CD10_CPn_BW_BMSK                                 0x3fff
#define HWIO_CD_TH_CD10_CPn_BW_SHFT                                    0x0

#define HWIO_CD_TH_CD11_CPn_ADDR(n)                             (BCM_CD_CFG_REG_BASE      + 0x00000ac0 + 0x4 * (n))
#define HWIO_CD_TH_CD11_CPn_RMSK                                    0x3fff
#define HWIO_CD_TH_CD11_CPn_MAXn                                        15
#define HWIO_CD_TH_CD11_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD11_CPn_ADDR(n), HWIO_CD_TH_CD11_CPn_RMSK)
#define HWIO_CD_TH_CD11_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD11_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD11_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD11_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD11_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD11_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD11_CPn_INI(n))
#define HWIO_CD_TH_CD11_CPn_BW_BMSK                                 0x3fff
#define HWIO_CD_TH_CD11_CPn_BW_SHFT                                    0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_SEQ_CFG
 *--------------------------------------------------------------------------*/

#define BCM_SEQ_CFG_REG_BASE                                                 (AOSS_BASE      + 0x00be4000)
#define BCM_SEQ_CFG_REG_BASE_SIZE                                            0x1200
#define BCM_SEQ_CFG_REG_BASE_USED                                            0xb80

#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_ADDR(m)                               (BCM_SEQ_CFG_REG_BASE      + 0x00000080 + 0x4 * (m))
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_RMSK                                       0x1ff
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_MAXm                                          11
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_INI(m)        \
        in_dword_masked(HWIO_SEQ_CFG_HW_START_ADDR_CDm_ADDR(m), HWIO_SEQ_CFG_HW_START_ADDR_CDm_RMSK)
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SEQ_CFG_HW_START_ADDR_CDm_ADDR(m), mask)
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_OUTI(m,val)    \
        out_dword(HWIO_SEQ_CFG_HW_START_ADDR_CDm_ADDR(m),val)
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SEQ_CFG_HW_START_ADDR_CDm_ADDR(m),mask,val,HWIO_SEQ_CFG_HW_START_ADDR_CDm_INI(m))
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_HW_START_ADDR_BMSK                         0x1ff
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_HW_START_ADDR_SHFT                           0x0

#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_ADDR(m)                               (BCM_SEQ_CFG_REG_BASE      + 0x00000100 + 0x4 * (m))
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_RMSK                                       0x1ff
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_MAXm                                          11
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_INI(m)        \
        in_dword_masked(HWIO_SEQ_CFG_SW_START_ADDR_CDm_ADDR(m), HWIO_SEQ_CFG_SW_START_ADDR_CDm_RMSK)
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SEQ_CFG_SW_START_ADDR_CDm_ADDR(m), mask)
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_OUTI(m,val)    \
        out_dword(HWIO_SEQ_CFG_SW_START_ADDR_CDm_ADDR(m),val)
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SEQ_CFG_SW_START_ADDR_CDm_ADDR(m),mask,val,HWIO_SEQ_CFG_SW_START_ADDR_CDm_INI(m))
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_SW_START_ADDR_BMSK                         0x1ff
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_SW_START_ADDR_SHFT                           0x0

#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_ADDR(b)                                 (BCM_SEQ_CFG_REG_BASE      + 0x00000180 + 0x4 * (b))
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_RMSK                                         0x1ff
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_MAXb                                            31
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_INI(b)        \
        in_dword_masked(HWIO_SEQ_CFG_BRANCH_ADDR_BRb_ADDR(b), HWIO_SEQ_CFG_BRANCH_ADDR_BRb_RMSK)
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_INMI(b,mask)    \
        in_dword_masked(HWIO_SEQ_CFG_BRANCH_ADDR_BRb_ADDR(b), mask)
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_OUTI(b,val)    \
        out_dword(HWIO_SEQ_CFG_BRANCH_ADDR_BRb_ADDR(b),val)
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_OUTMI(b,mask,val) \
        out_dword_masked_ns(HWIO_SEQ_CFG_BRANCH_ADDR_BRb_ADDR(b),mask,val,HWIO_SEQ_CFG_BRANCH_ADDR_BRb_INI(b))
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_BRANCH_ADDR_BMSK                             0x1ff
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_BRANCH_ADDR_SHFT                               0x0

#define HWIO_SEQ_CFG_DELAY_DLYy_ADDR(y)                                      (BCM_SEQ_CFG_REG_BASE      + 0x00000980 + 0x4 * (y))
#define HWIO_SEQ_CFG_DELAY_DLYy_RMSK                                            0xfffff
#define HWIO_SEQ_CFG_DELAY_DLYy_MAXy                                                  3
#define HWIO_SEQ_CFG_DELAY_DLYy_INI(y)        \
        in_dword_masked(HWIO_SEQ_CFG_DELAY_DLYy_ADDR(y), HWIO_SEQ_CFG_DELAY_DLYy_RMSK)
#define HWIO_SEQ_CFG_DELAY_DLYy_INMI(y,mask)    \
        in_dword_masked(HWIO_SEQ_CFG_DELAY_DLYy_ADDR(y), mask)
#define HWIO_SEQ_CFG_DELAY_DLYy_OUTI(y,val)    \
        out_dword(HWIO_SEQ_CFG_DELAY_DLYy_ADDR(y),val)
#define HWIO_SEQ_CFG_DELAY_DLYy_OUTMI(y,mask,val) \
        out_dword_masked_ns(HWIO_SEQ_CFG_DELAY_DLYy_ADDR(y),mask,val,HWIO_SEQ_CFG_DELAY_DLYy_INI(y))
#define HWIO_SEQ_CFG_DELAY_DLYy_DELAY_VAL_BMSK                                  0xfffff
#define HWIO_SEQ_CFG_DELAY_DLYy_DELAY_VAL_SHFT                                      0x0

#define HWIO_SEQ_CFG_BR_EVENT_ADDR                                           (BCM_SEQ_CFG_REG_BASE      + 0x00000b80)
#define HWIO_SEQ_CFG_BR_EVENT_RMSK                                                0xfff
#define HWIO_SEQ_CFG_BR_EVENT_IN          \
        in_dword(HWIO_SEQ_CFG_BR_EVENT_ADDR)
#define HWIO_SEQ_CFG_BR_EVENT_INM(m)      \
        in_dword_masked(HWIO_SEQ_CFG_BR_EVENT_ADDR, m)
#define HWIO_SEQ_CFG_BR_EVENT_OUT(v)      \
        out_dword(HWIO_SEQ_CFG_BR_EVENT_ADDR,v)
#define HWIO_SEQ_CFG_BR_EVENT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SEQ_CFG_BR_EVENT_ADDR,m,v,HWIO_SEQ_CFG_BR_EVENT_IN)
#define HWIO_SEQ_CFG_BR_EVENT_BR_EVENT_BIT_15_PER_VCD_BMSK                        0xfff
#define HWIO_SEQ_CFG_BR_EVENT_BR_EVENT_BIT_15_PER_VCD_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_TCS_CFG
 *--------------------------------------------------------------------------*/

#define BCM_TCS_CFG_REG_BASE                                                          (AOSS_BASE      + 0x00be5400)
#define BCM_TCS_CFG_REG_BASE_SIZE                                                     0x1400
#define BCM_TCS_CFG_REG_BASE_USED                                                     0xa80

#define HWIO_TCS_CFG_CDm_ADDR(m)                                                      (BCM_TCS_CFG_REG_BASE      + 0x00000000 + 0x4 * (m))
#define HWIO_TCS_CFG_CDm_RMSK                                                          0x7070707
#define HWIO_TCS_CFG_CDm_MAXm                                                                 11
#define HWIO_TCS_CFG_CDm_INI(m)        \
        in_dword_masked(HWIO_TCS_CFG_CDm_ADDR(m), HWIO_TCS_CFG_CDm_RMSK)
#define HWIO_TCS_CFG_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_TCS_CFG_CDm_ADDR(m), mask)
#define HWIO_TCS_CFG_CDm_OUTI(m,val)    \
        out_dword(HWIO_TCS_CFG_CDm_ADDR(m),val)
#define HWIO_TCS_CFG_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_CDm_ADDR(m),mask,val,HWIO_TCS_CFG_CDm_INI(m))
#define HWIO_TCS_CFG_CDm_TCS_CMD_WAIT_BMSK                                             0x7000000
#define HWIO_TCS_CFG_CDm_TCS_CMD_WAIT_SHFT                                                  0x18
#define HWIO_TCS_CFG_CDm_TCS_CMD_RR_CPUP_BMSK                                            0x70000
#define HWIO_TCS_CFG_CDm_TCS_CMD_RR_CPUP_SHFT                                               0x10
#define HWIO_TCS_CFG_CDm_TCS_CMD_RR_CPDOWN_BMSK                                            0x700
#define HWIO_TCS_CFG_CDm_TCS_CMD_RR_CPDOWN_SHFT                                              0x8
#define HWIO_TCS_CFG_CDm_TCS_CMD_EN_BMSK                                                     0x7
#define HWIO_TCS_CFG_CDm_TCS_CMD_EN_SHFT                                                     0x0

#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_ADDR(m,t)                                     (BCM_TCS_CFG_REG_BASE      + 0x00000080 + 0xC * (m) + 0x4 * (t))
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_RMSK                                          0x80e0ffff
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_MAXm                                                  11
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_MAXt                                                   2
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_INI2(m,t)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_ADDR(m,t), HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_RMSK)
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_INMI2(m,t,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_ADDR(m,t), mask)
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_OUTI2(m,t,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_ADDR(m,t),val)
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_OUTMI2(m,t,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_ADDR(m,t),mask,val,HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_INI2(m,t))
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_IS_VRM_VOTE_BMSK                              0x80000000
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_IS_VRM_VOTE_SHFT                                    0x1f
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_SLV_ID_BMSK                                     0xe00000
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_SLV_ID_SHFT                                         0x15
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_BCM_CD_ID_FOR_ARC_VOTE_BMSK                       0xf000
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_BCM_CD_ID_FOR_ARC_VOTE_SHFT                          0xc
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_OFFSET_BMSK                                        0xfff
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_OFFSET_SHFT                                          0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000280 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_RMSK                                                0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_MAXn                                                   15
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_ADDR(m,n)                                      (BCM_TCS_CFG_REG_BASE      + 0x00000280 + 0x4 * (n) + 0x40 * (m))
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_RMSK                                                0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_MAXm                                                   15
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_MAXn                                                   15
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_INI2(m,n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_ADDR(m,n), HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_INMI2(m,n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_ADDR(m,n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_OUTI2(m,n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_ADDR(m,n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_OUTMI2(m,n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_ADDR(m,n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_INI2(m,n))
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x000002c0 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_RMSK                                                0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000300 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_RMSK                                                0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000340 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_RMSK                                                0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000380 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_RMSK                                                0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x000003c0 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_RMSK                                                0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000400 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_RMSK                                                0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000440 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_RMSK                                                0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000480 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_RMSK                                                0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x000004c0 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_RMSK                                                0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_ADDR(n)                                       (BCM_TCS_CFG_REG_BASE      + 0x00000500 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_RMSK                                               0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_MAXn                                                  15
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD2_DATA_BMSK                                     0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD2_DATA_SHFT                                       0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD1_DATA_BMSK                                      0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD1_DATA_SHFT                                       0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD0_DATA_BMSK                                       0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD0_DATA_SHFT                                       0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_ADDR(n)                                       (BCM_TCS_CFG_REG_BASE      + 0x00000540 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_RMSK                                               0xfff
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_MAXn                                                  15
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD2_DATA_BMSK                                     0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD2_DATA_SHFT                                       0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD1_DATA_BMSK                                      0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD1_DATA_SHFT                                       0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD0_DATA_BMSK                                       0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD0_DATA_SHFT                                       0x0

#define HWIO_TCS_VOTE_RESP_BACK_ADDR                                                  (BCM_TCS_CFG_REG_BASE      + 0x00000a80)
#define HWIO_TCS_VOTE_RESP_BACK_RMSK                                                  0xffffffff
#define HWIO_TCS_VOTE_RESP_BACK_IN          \
        in_dword(HWIO_TCS_VOTE_RESP_BACK_ADDR)
#define HWIO_TCS_VOTE_RESP_BACK_INM(m)      \
        in_dword_masked(HWIO_TCS_VOTE_RESP_BACK_ADDR, m)
#define HWIO_TCS_VOTE_RESP_BACK_OUT(v)      \
        out_dword(HWIO_TCS_VOTE_RESP_BACK_ADDR,v)
#define HWIO_TCS_VOTE_RESP_BACK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCS_VOTE_RESP_BACK_ADDR,m,v,HWIO_TCS_VOTE_RESP_BACK_IN)
#define HWIO_TCS_VOTE_RESP_BACK_VOTE_RESP_BMSK                                        0xffffffff
#define HWIO_TCS_VOTE_RESP_BACK_VOTE_RESP_SHFT                                               0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_AU_CFG
 *--------------------------------------------------------------------------*/

#define BCM_AU_CFG_REG_BASE                                       (AOSS_BASE      + 0x00be6800)
#define BCM_AU_CFG_REG_BASE_SIZE                                  0x184
#define BCM_AU_CFG_REG_BASE_USED                                  0x180

#define HWIO_ALGO_ADDRg_ADDR(g)                                   (BCM_AU_CFG_REG_BASE      + 0x00000000 + 0x4 * (g))
#define HWIO_ALGO_ADDRg_RMSK                                            0xff
#define HWIO_ALGO_ADDRg_MAXg                                              31
#define HWIO_ALGO_ADDRg_INI(g)        \
        in_dword_masked(HWIO_ALGO_ADDRg_ADDR(g), HWIO_ALGO_ADDRg_RMSK)
#define HWIO_ALGO_ADDRg_INMI(g,mask)    \
        in_dword_masked(HWIO_ALGO_ADDRg_ADDR(g), mask)
#define HWIO_ALGO_ADDRg_OUTI(g,val)    \
        out_dword(HWIO_ALGO_ADDRg_ADDR(g),val)
#define HWIO_ALGO_ADDRg_OUTMI(g,mask,val) \
        out_dword_masked_ns(HWIO_ALGO_ADDRg_ADDR(g),mask,val,HWIO_ALGO_ADDRg_INI(g))
#define HWIO_ALGO_ADDRg_ALGO_ADDR_BMSK                                  0xff
#define HWIO_ALGO_ADDRg_ALGO_ADDR_SHFT                                   0x0

#define HWIO_AU_CFG_SCALARk_ADDR(k)                               (BCM_AU_CFG_REG_BASE      + 0x00000100 + 0x4 * (k))
#define HWIO_AU_CFG_SCALARk_RMSK                                        0xff
#define HWIO_AU_CFG_SCALARk_MAXk                                          31
#define HWIO_AU_CFG_SCALARk_INI(k)        \
        in_dword_masked(HWIO_AU_CFG_SCALARk_ADDR(k), HWIO_AU_CFG_SCALARk_RMSK)
#define HWIO_AU_CFG_SCALARk_INMI(k,mask)    \
        in_dword_masked(HWIO_AU_CFG_SCALARk_ADDR(k), mask)
#define HWIO_AU_CFG_SCALARk_OUTI(k,val)    \
        out_dword(HWIO_AU_CFG_SCALARk_ADDR(k),val)
#define HWIO_AU_CFG_SCALARk_OUTMI(k,mask,val) \
        out_dword_masked_ns(HWIO_AU_CFG_SCALARk_ADDR(k),mask,val,HWIO_AU_CFG_SCALARk_INI(k))
#define HWIO_AU_CFG_SCALARk_VALUE_BMSK                                  0xff
#define HWIO_AU_CFG_SCALARk_VALUE_SHFT                                   0x0

#define HWIO_AU_CFG_SCALAR_FORMAT_ADDR                            (BCM_AU_CFG_REG_BASE      + 0x00000180)
#define HWIO_AU_CFG_SCALAR_FORMAT_RMSK                                   0x7
#define HWIO_AU_CFG_SCALAR_FORMAT_IN          \
        in_dword(HWIO_AU_CFG_SCALAR_FORMAT_ADDR)
#define HWIO_AU_CFG_SCALAR_FORMAT_INM(m)      \
        in_dword_masked(HWIO_AU_CFG_SCALAR_FORMAT_ADDR, m)
#define HWIO_AU_CFG_SCALAR_FORMAT_OUT(v)      \
        out_dword(HWIO_AU_CFG_SCALAR_FORMAT_ADDR,v)
#define HWIO_AU_CFG_SCALAR_FORMAT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AU_CFG_SCALAR_FORMAT_ADDR,m,v,HWIO_AU_CFG_SCALAR_FORMAT_IN)
#define HWIO_AU_CFG_SCALAR_FORMAT_FRACTION_BMSK                          0x7
#define HWIO_AU_CFG_SCALAR_FORMAT_FRACTION_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_CFG
 *--------------------------------------------------------------------------*/

#define BCM_CFG_REG_BASE                                               (AOSS_BASE      + 0x00be7000)
#define BCM_CFG_REG_BASE_SIZE                                          0x200
#define BCM_CFG_REG_BASE_USED                                          0x110

#define HWIO_BCM_CFG_BCM_EN_ADDR                                       (BCM_CFG_REG_BASE      + 0x00000000)
#define HWIO_BCM_CFG_BCM_EN_RMSK                                              0x1
#define HWIO_BCM_CFG_BCM_EN_IN          \
        in_dword(HWIO_BCM_CFG_BCM_EN_ADDR)
#define HWIO_BCM_CFG_BCM_EN_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_BCM_EN_ADDR, m)
#define HWIO_BCM_CFG_BCM_EN_OUT(v)      \
        out_dword(HWIO_BCM_CFG_BCM_EN_ADDR,v)
#define HWIO_BCM_CFG_BCM_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_BCM_EN_ADDR,m,v,HWIO_BCM_CFG_BCM_EN_IN)
#define HWIO_BCM_CFG_BCM_EN_BCM_EN_BMSK                                       0x1
#define HWIO_BCM_CFG_BCM_EN_BCM_EN_SHFT                                       0x0

#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_ADDR                              (BCM_CFG_REG_BASE      + 0x00000004)
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_RMSK                                     0x7
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_IN          \
        in_dword(HWIO_BCM_CFG_SLV_ID_FOR_RESP_ADDR)
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_SLV_ID_FOR_RESP_ADDR, m)
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_OUT(v)      \
        out_dword(HWIO_BCM_CFG_SLV_ID_FOR_RESP_ADDR,v)
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_SLV_ID_FOR_RESP_ADDR,m,v,HWIO_BCM_CFG_SLV_ID_FOR_RESP_IN)
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_SLV_ID_BMSK                              0x7
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_SLV_ID_SHFT                              0x0

#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_ADDR                          (BCM_CFG_REG_BASE      + 0x00000008)
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_RMSK                                0x1f
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_IN          \
        in_dword(HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_ADDR)
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_ADDR, m)
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_OUT(v)      \
        out_dword(HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_ADDR,v)
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_ADDR,m,v,HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_IN)
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_DRV_ID_BMSK                         0x1f
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_DRV_ID_SHFT                          0x0

#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_ADDR                          (BCM_CFG_REG_BASE      + 0x00000088)
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_RMSK                                0x1f
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_IN          \
        in_dword(HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_ADDR)
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_ADDR, m)
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_OUT(v)      \
        out_dword(HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_ADDR,v)
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_ADDR,m,v,HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_IN)
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_DRV_ID_BMSK                         0x1f
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_DRV_ID_SHFT                          0x0

#define HWIO_BCM_CFG_DRVr_ADDR(r)                                      (BCM_CFG_REG_BASE      + 0x0000008c + 0x4 * (r))
#define HWIO_BCM_CFG_DRVr_RMSK                                           0xffffff
#define HWIO_BCM_CFG_DRVr_MAXr                                                 13
#define HWIO_BCM_CFG_DRVr_INI(r)        \
        in_dword_masked(HWIO_BCM_CFG_DRVr_ADDR(r), HWIO_BCM_CFG_DRVr_RMSK)
#define HWIO_BCM_CFG_DRVr_INMI(r,mask)    \
        in_dword_masked(HWIO_BCM_CFG_DRVr_ADDR(r), mask)
#define HWIO_BCM_CFG_DRVr_OUTI(r,val)    \
        out_dword(HWIO_BCM_CFG_DRVr_ADDR(r),val)
#define HWIO_BCM_CFG_DRVr_OUTMI(r,mask,val) \
        out_dword_masked_ns(HWIO_BCM_CFG_DRVr_ADDR(r),mask,val,HWIO_BCM_CFG_DRVr_INI(r))
#define HWIO_BCM_CFG_DRVr_RESP_ADDR_BMSK                                 0xffffff
#define HWIO_BCM_CFG_DRVr_RESP_ADDR_SHFT                                      0x0

#define HWIO_BCM_CFG_DEBUG_BUS_ADDR                                    (BCM_CFG_REG_BASE      + 0x0000010c)
#define HWIO_BCM_CFG_DEBUG_BUS_RMSK                                         0x10f
#define HWIO_BCM_CFG_DEBUG_BUS_IN          \
        in_dword(HWIO_BCM_CFG_DEBUG_BUS_ADDR)
#define HWIO_BCM_CFG_DEBUG_BUS_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_DEBUG_BUS_ADDR, m)
#define HWIO_BCM_CFG_DEBUG_BUS_OUT(v)      \
        out_dword(HWIO_BCM_CFG_DEBUG_BUS_ADDR,v)
#define HWIO_BCM_CFG_DEBUG_BUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_DEBUG_BUS_ADDR,m,v,HWIO_BCM_CFG_DEBUG_BUS_IN)
#define HWIO_BCM_CFG_DEBUG_BUS_DEBUG_BUS_EN_BMSK                            0x100
#define HWIO_BCM_CFG_DEBUG_BUS_DEBUG_BUS_EN_SHFT                              0x8
#define HWIO_BCM_CFG_DEBUG_BUS_CD_SEL_BMSK                                    0xf
#define HWIO_BCM_CFG_DEBUG_BUS_CD_SEL_SHFT                                    0x0

#define HWIO_BCM_CFG_ARCH_CG_DISABLE_ADDR                              (BCM_CFG_REG_BASE      + 0x00000110)
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_RMSK                                     0x3
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_IN          \
        in_dword(HWIO_BCM_CFG_ARCH_CG_DISABLE_ADDR)
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_ARCH_CG_DISABLE_ADDR, m)
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_OUT(v)      \
        out_dword(HWIO_BCM_CFG_ARCH_CG_DISABLE_ADDR,v)
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_ARCH_CG_DISABLE_ADDR,m,v,HWIO_BCM_CFG_ARCH_CG_DISABLE_IN)
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_BCM_FE_BMSK                              0x2
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_BCM_FE_SHFT                              0x1
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_BCM_CE_BMSK                              0x1
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_BCM_CE_SHFT                              0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_STATUS
 *--------------------------------------------------------------------------*/

#define BCM_STATUS_REG_BASE                                                     (AOSS_BASE      + 0x00bf0000)
#define BCM_STATUS_REG_BASE_SIZE                                                0x1f00
#define BCM_STATUS_REG_BASE_USED                                                0x170c

#define HWIO_STATUS_FE_AGG_FSM_ADDR                                             (BCM_STATUS_REG_BASE      + 0x00000000)
#define HWIO_STATUS_FE_AGG_FSM_RMSK                                                  0xfff
#define HWIO_STATUS_FE_AGG_FSM_IN          \
        in_dword(HWIO_STATUS_FE_AGG_FSM_ADDR)
#define HWIO_STATUS_FE_AGG_FSM_INM(m)      \
        in_dword_masked(HWIO_STATUS_FE_AGG_FSM_ADDR, m)
#define HWIO_STATUS_FE_AGG_FSM_AGG_BUSY_CD_BMSK                                      0xfff
#define HWIO_STATUS_FE_AGG_FSM_AGG_BUSY_CD_SHFT                                        0x0

#define HWIO_STATUS_FE_CDm_ADDR(m)                                              (BCM_STATUS_REG_BASE      + 0x00000004 + 0x4 * (m))
#define HWIO_STATUS_FE_CDm_RMSK                                                 0x7fff10ff
#define HWIO_STATUS_FE_CDm_MAXm                                                         11
#define HWIO_STATUS_FE_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_FE_CDm_ADDR(m), HWIO_STATUS_FE_CDm_RMSK)
#define HWIO_STATUS_FE_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_FE_CDm_ADDR(m), mask)
#define HWIO_STATUS_FE_CDm_AGG_BW_BMSK                                          0x7fff0000
#define HWIO_STATUS_FE_CDm_AGG_BW_SHFT                                                0x10
#define HWIO_STATUS_FE_CDm_COMMIT_CD_RAW_BMSK                                       0x1000
#define HWIO_STATUS_FE_CDm_COMMIT_CD_RAW_SHFT                                          0xc
#define HWIO_STATUS_FE_CDm_FINAL_CP_BMSK                                              0xf0
#define HWIO_STATUS_FE_CDm_FINAL_CP_SHFT                                               0x4
#define HWIO_STATUS_FE_CDm_AGG_CP_BMSK                                                 0xf
#define HWIO_STATUS_FE_CDm_AGG_CP_SHFT                                                 0x0

#define HWIO_STATUS_DIRTY_ND_0_ADDR                                             (BCM_STATUS_REG_BASE      + 0x00000084)
#define HWIO_STATUS_DIRTY_ND_0_RMSK                                             0xffffffff
#define HWIO_STATUS_DIRTY_ND_0_IN          \
        in_dword(HWIO_STATUS_DIRTY_ND_0_ADDR)
#define HWIO_STATUS_DIRTY_ND_0_INM(m)      \
        in_dword_masked(HWIO_STATUS_DIRTY_ND_0_ADDR, m)
#define HWIO_STATUS_DIRTY_ND_0_DIRTY_ND_31_0_BMSK                               0xffffffff
#define HWIO_STATUS_DIRTY_ND_0_DIRTY_ND_31_0_SHFT                                      0x0

#define HWIO_STATUS_SNDs_ADDR(s)                                                (BCM_STATUS_REG_BASE      + 0x0000008c + 0x4 * (s))
#define HWIO_STATUS_SNDs_RMSK                                                       0xffff
#define HWIO_STATUS_SNDs_MAXs                                                            3
#define HWIO_STATUS_SNDs_INI(s)        \
        in_dword_masked(HWIO_STATUS_SNDs_ADDR(s), HWIO_STATUS_SNDs_RMSK)
#define HWIO_STATUS_SNDs_INMI(s,mask)    \
        in_dword_masked(HWIO_STATUS_SNDs_ADDR(s), mask)
#define HWIO_STATUS_SNDs_BIT_VEC_BMSK                                               0xffff
#define HWIO_STATUS_SNDs_BIT_VEC_SHFT                                                  0x0

#define HWIO_STATUS_AGG_BW_NDd_ADDR(d)                                          (BCM_STATUS_REG_BASE      + 0x0000010c + 0x4 * (d))
#define HWIO_STATUS_AGG_BW_NDd_RMSK                                                 0x7fff
#define HWIO_STATUS_AGG_BW_NDd_MAXd                                                     31
#define HWIO_STATUS_AGG_BW_NDd_INI(d)        \
        in_dword_masked(HWIO_STATUS_AGG_BW_NDd_ADDR(d), HWIO_STATUS_AGG_BW_NDd_RMSK)
#define HWIO_STATUS_AGG_BW_NDd_INMI(d,mask)    \
        in_dword_masked(HWIO_STATUS_AGG_BW_NDd_ADDR(d), mask)
#define HWIO_STATUS_AGG_BW_NDd_AGG_BW_BMSK                                          0x7fff
#define HWIO_STATUS_AGG_BW_NDd_AGG_BW_SHFT                                             0x0

#define HWIO_STATUS_AGG_BW_Z_NDs_ADDR(s)                                        (BCM_STATUS_REG_BASE      + 0x0000030c + 0x4 * (s))
#define HWIO_STATUS_AGG_BW_Z_NDs_RMSK                                               0x7fff
#define HWIO_STATUS_AGG_BW_Z_NDs_MAXs                                                    3
#define HWIO_STATUS_AGG_BW_Z_NDs_INI(s)        \
        in_dword_masked(HWIO_STATUS_AGG_BW_Z_NDs_ADDR(s), HWIO_STATUS_AGG_BW_Z_NDs_RMSK)
#define HWIO_STATUS_AGG_BW_Z_NDs_INMI(s,mask)    \
        in_dword_masked(HWIO_STATUS_AGG_BW_Z_NDs_ADDR(s), mask)
#define HWIO_STATUS_AGG_BW_Z_NDs_AGG_BW_Z_BMSK                                      0x7fff
#define HWIO_STATUS_AGG_BW_Z_NDs_AGG_BW_Z_SHFT                                         0x0

#define HWIO_STATUS_FE_NEW_CDm_ADDR(m)                                          (BCM_STATUS_REG_BASE      + 0x0000034c + 0x4 * (m))
#define HWIO_STATUS_FE_NEW_CDm_RMSK                                                 0xffff
#define HWIO_STATUS_FE_NEW_CDm_MAXm                                                     11
#define HWIO_STATUS_FE_NEW_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_FE_NEW_CDm_ADDR(m), HWIO_STATUS_FE_NEW_CDm_RMSK)
#define HWIO_STATUS_FE_NEW_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_FE_NEW_CDm_ADDR(m), mask)
#define HWIO_STATUS_FE_NEW_CDm_FINAL_BIT_VEC_BMSK                                   0xffff
#define HWIO_STATUS_FE_NEW_CDm_FINAL_BIT_VEC_SHFT                                      0x0

#define HWIO_STATUS_BE_CDm_ADDR(m)                                              (BCM_STATUS_REG_BASE      + 0x00000800 + 0x4 * (m))
#define HWIO_STATUS_BE_CDm_RMSK                                                    0xfffff
#define HWIO_STATUS_BE_CDm_MAXm                                                         11
#define HWIO_STATUS_BE_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_CDm_ADDR(m), HWIO_STATUS_BE_CDm_RMSK)
#define HWIO_STATUS_BE_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_CDm_CLK_DEST_STATE_BMSK                                     0xf0000
#define HWIO_STATUS_BE_CDm_CLK_DEST_STATE_SHFT                                        0x10
#define HWIO_STATUS_BE_CDm_COMBINED_CP_BMSK                                         0xf000
#define HWIO_STATUS_BE_CDm_COMBINED_CP_SHFT                                            0xc
#define HWIO_STATUS_BE_CDm_SW_CP_SNAP_BMSK                                           0xf00
#define HWIO_STATUS_BE_CDm_SW_CP_SNAP_SHFT                                             0x8
#define HWIO_STATUS_BE_CDm_WRITTEN_CP_BMSK                                            0xf0
#define HWIO_STATUS_BE_CDm_WRITTEN_CP_SHFT                                             0x4
#define HWIO_STATUS_BE_CDm_CURR_CP_BMSK                                                0xf
#define HWIO_STATUS_BE_CDm_CURR_CP_SHFT                                                0x0

#define HWIO_STATUS_BE_SEQ_CDm_ADDR(m)                                          (BCM_STATUS_REG_BASE      + 0x00000880 + 0x4 * (m))
#define HWIO_STATUS_BE_SEQ_CDm_RMSK                                                0x1ff01
#define HWIO_STATUS_BE_SEQ_CDm_MAXm                                                     11
#define HWIO_STATUS_BE_SEQ_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_SEQ_CDm_ADDR(m), HWIO_STATUS_BE_SEQ_CDm_RMSK)
#define HWIO_STATUS_BE_SEQ_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_SEQ_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_SEQ_CDm_SEQ_CURR_PC_BMSK                                    0x1ff00
#define HWIO_STATUS_BE_SEQ_CDm_SEQ_CURR_PC_SHFT                                        0x8
#define HWIO_STATUS_BE_SEQ_CDm_SEQ_STATE_BMSK                                          0x1
#define HWIO_STATUS_BE_SEQ_CDm_SEQ_STATE_SHFT                                          0x0

#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_ADDR(m)                             (BCM_STATUS_REG_BASE      + 0x00000900 + 0x4 * (m))
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_RMSK                                       0x7
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_MAXm                                        11
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_ADDR(m), HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_RMSK)
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_ISSUE_STATUS_BMSK                          0x7
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_ISSUE_STATUS_SHFT                          0x0

#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_ADDR(m)                              (BCM_STATUS_REG_BASE      + 0x00000980 + 0x4 * (m))
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_RMSK                                        0x7
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_MAXm                                         11
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_ADDR(m), HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_RMSK)
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_SENT_STATUS_BMSK                            0x7
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_SENT_STATUS_SHFT                            0x0

#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_ADDR(m)                              (BCM_STATUS_REG_BASE      + 0x00000a00 + 0x4 * (m))
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_RMSK                                        0x7
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_MAXm                                         11
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_ADDR(m), HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_RMSK)
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_CMPL_STATUS_BMSK                            0x7
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_CMPL_STATUS_SHFT                            0x0

#define HWIO_STATUS_BE_TCS_STATUS_CDm_ADDR(m)                                   (BCM_STATUS_REG_BASE      + 0x00000a80 + 0x4 * (m))
#define HWIO_STATUS_BE_TCS_STATUS_CDm_RMSK                                             0x7
#define HWIO_STATUS_BE_TCS_STATUS_CDm_MAXm                                              11
#define HWIO_STATUS_BE_TCS_STATUS_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_TCS_STATUS_CDm_ADDR(m), HWIO_STATUS_BE_TCS_STATUS_CDm_RMSK)
#define HWIO_STATUS_BE_TCS_STATUS_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_TCS_STATUS_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_TCS_STATUS_CDm_TCS_CURR_STATE_BMSK                              0x7
#define HWIO_STATUS_BE_TCS_STATUS_CDm_TCS_CURR_STATE_SHFT                              0x0

#define HWIO_STATUS_CE_DRVr_CTTe_ADDR(r,e)                                      (BCM_STATUS_REG_BASE      + 0x00000f00 + 0x38 * (r) + 0x4 * (e))
#define HWIO_STATUS_CE_DRVr_CTTe_RMSK                                           0xffff07ff
#define HWIO_STATUS_CE_DRVr_CTTe_MAXr                                                   13
#define HWIO_STATUS_CE_DRVr_CTTe_MAXe                                                   13
#define HWIO_STATUS_CE_DRVr_CTTe_INI2(r,e)        \
        in_dword_masked(HWIO_STATUS_CE_DRVr_CTTe_ADDR(r,e), HWIO_STATUS_CE_DRVr_CTTe_RMSK)
#define HWIO_STATUS_CE_DRVr_CTTe_INMI2(r,e,mask)    \
        in_dword_masked(HWIO_STATUS_CE_DRVr_CTTe_ADDR(r,e), mask)
#define HWIO_STATUS_CE_DRVr_CTTe_OFFSET_BMSK                                    0xffff0000
#define HWIO_STATUS_CE_DRVr_CTTe_OFFSET_SHFT                                          0x10
#define HWIO_STATUS_CE_DRVr_CTTe_DESIRED_CP_BMSK                                     0x780
#define HWIO_STATUS_CE_DRVr_CTTe_DESIRED_CP_SHFT                                       0x7
#define HWIO_STATUS_CE_DRVr_CTTe_CD_ID_BMSK                                           0x78
#define HWIO_STATUS_CE_DRVr_CTTe_CD_ID_SHFT                                            0x3
#define HWIO_STATUS_CE_DRVr_CTTe_CTT_STATUS_BMSK                                       0x7
#define HWIO_STATUS_CE_DRVr_CTTe_CTT_STATUS_SHFT                                       0x0

#define HWIO_STATUS_CE_ADDR                                                     (BCM_STATUS_REG_BASE      + 0x00001700)
#define HWIO_STATUS_CE_RMSK                                                       0x3fff01
#define HWIO_STATUS_CE_IN          \
        in_dword(HWIO_STATUS_CE_ADDR)
#define HWIO_STATUS_CE_INM(m)      \
        in_dword_masked(HWIO_STATUS_CE_ADDR, m)
#define HWIO_STATUS_CE_CTT_EMPTY_DRV_BMSK                                         0x3fff00
#define HWIO_STATUS_CE_CTT_EMPTY_DRV_SHFT                                              0x8
#define HWIO_STATUS_CE_CTT_EMPTY_BMSK                                                  0x1
#define HWIO_STATUS_CE_CTT_EMPTY_SHFT                                                  0x0

#define HWIO_STATUS_BCM_ADDR                                                    (BCM_STATUS_REG_BASE      + 0x00001704)
#define HWIO_STATUS_BCM_RMSK                                                           0x1
#define HWIO_STATUS_BCM_IN          \
        in_dword(HWIO_STATUS_BCM_ADDR)
#define HWIO_STATUS_BCM_INM(m)      \
        in_dword_masked(HWIO_STATUS_BCM_ADDR, m)
#define HWIO_STATUS_BCM_BCM_IDLE_BMSK                                                  0x1
#define HWIO_STATUS_BCM_BCM_IDLE_SHFT                                                  0x0

#define HWIO_HW_VERSION_ADDR                                                    (BCM_STATUS_REG_BASE      + 0x00001708)
#define HWIO_HW_VERSION_RMSK                                                      0xffffff
#define HWIO_HW_VERSION_IN          \
        in_dword(HWIO_HW_VERSION_ADDR)
#define HWIO_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_HW_VERSION_ADDR, m)
#define HWIO_HW_VERSION_MAJOR_BMSK                                                0xff0000
#define HWIO_HW_VERSION_MAJOR_SHFT                                                    0x10
#define HWIO_HW_VERSION_MINOR_BMSK                                                  0xff00
#define HWIO_HW_VERSION_MINOR_SHFT                                                     0x8
#define HWIO_HW_VERSION_STEP_BMSK                                                     0xff
#define HWIO_HW_VERSION_STEP_SHFT                                                      0x0

#define HWIO_STATUS_SPVT_ADDR                                                   (BCM_STATUS_REG_BASE      + 0x0000170c)
#define HWIO_STATUS_SPVT_RMSK                                                   0x801f03f1
#define HWIO_STATUS_SPVT_IN          \
        in_dword(HWIO_STATUS_SPVT_ADDR)
#define HWIO_STATUS_SPVT_INM(m)      \
        in_dword_masked(HWIO_STATUS_SPVT_ADDR, m)
#define HWIO_STATUS_SPVT_OUT(v)      \
        out_dword(HWIO_STATUS_SPVT_ADDR,v)
#define HWIO_STATUS_SPVT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_STATUS_SPVT_ADDR,m,v,HWIO_STATUS_SPVT_IN)
#define HWIO_STATUS_SPVT_CLEAR_WRONG_VOTE_DETECTION_BMSK                        0x80000000
#define HWIO_STATUS_SPVT_CLEAR_WRONG_VOTE_DETECTION_SHFT                              0x1f
#define HWIO_STATUS_SPVT_DRV_ID_BMSK                                              0x1f0000
#define HWIO_STATUS_SPVT_DRV_ID_SHFT                                                  0x10
#define HWIO_STATUS_SPVT_NODE_ID_BMSK                                                0x3f0
#define HWIO_STATUS_SPVT_NODE_ID_SHFT                                                  0x4
#define HWIO_STATUS_SPVT_WRONG_VOTE_DETECTED_BMSK                                      0x1
#define HWIO_STATUS_SPVT_WRONG_VOTE_DETECTED_SHFT                                      0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_INTERRUPT
 *--------------------------------------------------------------------------*/

#define BCM_INTERRUPT_REG_BASE                                                    (AOSS_BASE      + 0x00bf1f00)
#define BCM_INTERRUPT_REG_BASE_SIZE                                               0x100
#define BCM_INTERRUPT_REG_BASE_USED                                               0xa0

#define HWIO_INTERRUPT_AGG_DONE_INT_EN_ADDR                                       (BCM_INTERRUPT_REG_BASE      + 0x00000000)
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_RMSK                                            0xfff
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_AGG_DONE_INT_EN_ADDR)
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_AGG_DONE_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_AGG_DONE_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_AGG_DONE_INT_EN_ADDR,m,v,HWIO_INTERRUPT_AGG_DONE_INT_EN_IN)
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_EN_BMSK                                         0xfff
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_EN_SHFT                                           0x0

#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_ADDR                                 (BCM_INTERRUPT_REG_BASE      + 0x00000004)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_RMSK                                      0xfff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_ADDR)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_ADDR,m,v,HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_IN)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_EN_BMSK                                   0xfff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_EN_SHFT                                     0x0

#define HWIO_INTERRUPT_CTT_FULL_INT_EN_ADDR                                       (BCM_INTERRUPT_REG_BASE      + 0x00000008)
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_RMSK                                           0x3fff
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_CTT_FULL_INT_EN_ADDR)
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_CTT_FULL_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_CTT_FULL_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_CTT_FULL_INT_EN_ADDR,m,v,HWIO_INTERRUPT_CTT_FULL_INT_EN_IN)
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_EN_BMSK                                        0x3fff
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_EN_SHFT                                           0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_ADDR                                  (BCM_INTERRUPT_REG_BASE      + 0x0000000c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_RMSK                                       0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_ADDR,m,v,HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_IN)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_EN_BMSK                                    0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_EN_SHFT                                      0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_ADDR                                  (BCM_INTERRUPT_REG_BASE      + 0x00000010)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_RMSK                                       0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_ADDR,m,v,HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_IN)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_EN_BMSK                                    0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_EN_SHFT                                      0x0

#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_ADDR                                   (BCM_INTERRUPT_REG_BASE      + 0x00000014)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_RMSK                                        0xfff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_ADDR)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_ADDR,m,v,HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_IN)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_EN_BMSK                                     0xfff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_EN_SHFT                                       0x0

#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_ADDR                              (BCM_INTERRUPT_REG_BASE      + 0x00000018)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_RMSK                                   0xfff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_ADDR)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_ADDR,m,v,HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_IN)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_EN_BMSK                                0xfff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_EN_SHFT                                  0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_ADDR                                  (BCM_INTERRUPT_REG_BASE      + 0x0000001c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_RMSK                                       0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_ADDR,m,v,HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_IN)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_EN_BMSK                                    0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_EN_SHFT                                      0x0

#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_ADDR                               (BCM_INTERRUPT_REG_BASE      + 0x00000020)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_RMSK                                      0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_ADDR)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_ADDR,m,v,HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_IN)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_EN_BMSK                                   0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_EN_SHFT                                   0x0

#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_ADDR                                   (BCM_INTERRUPT_REG_BASE      + 0x00000040)
#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_RMSK                                        0xfff
#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_AGG_DONE_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_AGG_DONE_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_STATUS_BMSK                                 0xfff
#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_STATUS_SHFT                                   0x0

#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_ADDR                             (BCM_INTERRUPT_REG_BASE      + 0x00000044)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_RMSK                                  0xfff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_STATUS_BMSK                           0xfff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_STATUS_SHFT                             0x0

#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_ADDR                                   (BCM_INTERRUPT_REG_BASE      + 0x00000048)
#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_RMSK                                       0x3fff
#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_CTT_FULL_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_CTT_FULL_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_STATUS_BMSK                                0x3fff
#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_STATUS_SHFT                                   0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_ADDR                              (BCM_INTERRUPT_REG_BASE      + 0x0000004c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_RMSK                                   0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_STATUS_BMSK                            0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_STATUS_SHFT                              0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_ADDR                              (BCM_INTERRUPT_REG_BASE      + 0x00000050)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_RMSK                                   0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_STATUS_BMSK                            0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_STATUS_SHFT                              0x0

#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_ADDR                               (BCM_INTERRUPT_REG_BASE      + 0x00000054)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_RMSK                                    0xfff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_STATUS_BMSK                             0xfff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_STATUS_SHFT                               0x0

#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_ADDR                          (BCM_INTERRUPT_REG_BASE      + 0x00000058)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_RMSK                               0xfff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_STATUS_BMSK                        0xfff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_STATUS_SHFT                          0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_ADDR                              (BCM_INTERRUPT_REG_BASE      + 0x0000005c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_RMSK                                   0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_STATUS_BMSK                            0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_STATUS_SHFT                              0x0

#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_ADDR                           (BCM_INTERRUPT_REG_BASE      + 0x00000060)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_RMSK                                  0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_STATUS_BMSK                           0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_STATUS_SHFT                           0x0

#define HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_ADDR                                    (BCM_INTERRUPT_REG_BASE      + 0x00000080)
#define HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_RMSK                                         0xfff
#define HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_CLEAR_BMSK                                   0xfff
#define HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_CLEAR_SHFT                                     0x0

#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_ADDR                              (BCM_INTERRUPT_REG_BASE      + 0x00000084)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_RMSK                                   0xfff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_CLEAR_BMSK                             0xfff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_CLEAR_SHFT                               0x0

#define HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_ADDR                                    (BCM_INTERRUPT_REG_BASE      + 0x00000088)
#define HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_RMSK                                        0x3fff
#define HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_CLEAR_BMSK                                  0x3fff
#define HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_CLEAR_SHFT                                     0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_ADDR                               (BCM_INTERRUPT_REG_BASE      + 0x0000008c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_RMSK                                    0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_CLEAR_BMSK                              0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_CLEAR_SHFT                                0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_ADDR                               (BCM_INTERRUPT_REG_BASE      + 0x00000090)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_RMSK                                    0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_CLEAR_BMSK                              0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_CLEAR_SHFT                                0x0

#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_ADDR                                (BCM_INTERRUPT_REG_BASE      + 0x00000094)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_RMSK                                     0xfff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_CLEAR_BMSK                               0xfff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_CLEAR_SHFT                                 0x0

#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_ADDR                           (BCM_INTERRUPT_REG_BASE      + 0x00000098)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_RMSK                                0xfff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_CLEAR_BMSK                          0xfff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_CLEAR_SHFT                            0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_ADDR                               (BCM_INTERRUPT_REG_BASE      + 0x0000009c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_RMSK                                    0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_CLEAR_BMSK                              0xfff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_CLEAR_SHFT                                0x0

#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_ADDR                            (BCM_INTERRUPT_REG_BASE      + 0x000000a0)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_RMSK                                   0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_CLEAR_BMSK                             0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_CLEAR_SHFT                             0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_AU_MEM
 *--------------------------------------------------------------------------*/

#define BCM_AU_MEM_REG_BASE                                  (AOSS_BASE      + 0x00bf2000)
#define BCM_AU_MEM_REG_BASE_SIZE                             0x400
#define BCM_AU_MEM_REG_BASE_USED                             0x1fc

#define HWIO_AU_INST_MEMa_ADDR(a)                            (BCM_AU_MEM_REG_BASE      + 0x00000000 + 0x4 * (a))
#define HWIO_AU_INST_MEMa_RMSK                               0xffffffff
#define HWIO_AU_INST_MEMa_MAXa                                      127
#define HWIO_AU_INST_MEMa_INI(a)        \
        in_dword_masked(HWIO_AU_INST_MEMa_ADDR(a), HWIO_AU_INST_MEMa_RMSK)
#define HWIO_AU_INST_MEMa_INMI(a,mask)    \
        in_dword_masked(HWIO_AU_INST_MEMa_ADDR(a), mask)
#define HWIO_AU_INST_MEMa_OUTI(a,val)    \
        out_dword(HWIO_AU_INST_MEMa_ADDR(a),val)
#define HWIO_AU_INST_MEMa_OUTMI(a,mask,val) \
        out_dword_masked_ns(HWIO_AU_INST_MEMa_ADDR(a),mask,val,HWIO_AU_INST_MEMa_INI(a))
#define HWIO_AU_INST_MEMa_INSTRUCTION_BMSK                   0xffffffff
#define HWIO_AU_INST_MEMa_INSTRUCTION_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_SEQ_MEM
 *--------------------------------------------------------------------------*/

#define BCM_SEQ_MEM_REG_BASE                     (AOSS_BASE      + 0x00bf2400)
#define BCM_SEQ_MEM_REG_BASE_SIZE                0x200
#define BCM_SEQ_MEM_REG_BASE_USED                0x13c

#define HWIO_SEQ_MEMq_ADDR(q)                    (BCM_SEQ_MEM_REG_BASE      + 0x00000000 + 0x4 * (q))
#define HWIO_SEQ_MEMq_RMSK                       0xffffffff
#define HWIO_SEQ_MEMq_MAXq                               79
#define HWIO_SEQ_MEMq_INI(q)        \
        in_dword_masked(HWIO_SEQ_MEMq_ADDR(q), HWIO_SEQ_MEMq_RMSK)
#define HWIO_SEQ_MEMq_INMI(q,mask)    \
        in_dword_masked(HWIO_SEQ_MEMq_ADDR(q), mask)
#define HWIO_SEQ_MEMq_OUTI(q,val)    \
        out_dword(HWIO_SEQ_MEMq_ADDR(q),val)
#define HWIO_SEQ_MEMq_OUTMI(q,mask,val) \
        out_dword_masked_ns(HWIO_SEQ_MEMq_ADDR(q),mask,val,HWIO_SEQ_MEMq_INI(q))
#define HWIO_SEQ_MEMq_CMD_BMSK                   0xffffffff
#define HWIO_SEQ_MEMq_CMD_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_SW_OVERRIDE
 *--------------------------------------------------------------------------*/

#define BCM_SW_OVERRIDE_REG_BASE                                                            (AOSS_BASE      + 0x00bf2600)
#define BCM_SW_OVERRIDE_REG_BASE_SIZE                                                       0x800
#define BCM_SW_OVERRIDE_REG_BASE_USED                                                       0x7ac

#define HWIO_SW_CP_CDm_ADDR(m)                                                              (BCM_SW_OVERRIDE_REG_BASE      + 0x00000000 + 0x4 * (m))
#define HWIO_SW_CP_CDm_RMSK                                                                       0x1f
#define HWIO_SW_CP_CDm_MAXm                                                                         11
#define HWIO_SW_CP_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_CP_CDm_ADDR(m), HWIO_SW_CP_CDm_RMSK)
#define HWIO_SW_CP_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_CP_CDm_ADDR(m), mask)
#define HWIO_SW_CP_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_CP_CDm_ADDR(m),val)
#define HWIO_SW_CP_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_CP_CDm_ADDR(m),mask,val,HWIO_SW_CP_CDm_INI(m))
#define HWIO_SW_CP_CDm_VALID_BMSK                                                                 0x10
#define HWIO_SW_CP_CDm_VALID_SHFT                                                                  0x4
#define HWIO_SW_CP_CDm_SW_CP_BMSK                                                                  0xf
#define HWIO_SW_CP_CDm_SW_CP_SHFT                                                                  0x0

#define HWIO_SW_MASK_FE_BE_TRIG_CDm_ADDR(m)                                                 (BCM_SW_OVERRIDE_REG_BASE      + 0x00000080 + 0x4 * (m))
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_RMSK                                                           0x1
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_MAXm                                                            11
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_MASK_FE_BE_TRIG_CDm_ADDR(m), HWIO_SW_MASK_FE_BE_TRIG_CDm_RMSK)
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_MASK_FE_BE_TRIG_CDm_ADDR(m), mask)
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_MASK_FE_BE_TRIG_CDm_ADDR(m),val)
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_MASK_FE_BE_TRIG_CDm_ADDR(m),mask,val,HWIO_SW_MASK_FE_BE_TRIG_CDm_INI(m))
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_MASK_BMSK                                                      0x1
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_MASK_SHFT                                                      0x0

#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_ADDR(m)                                               (BCM_SW_OVERRIDE_REG_BASE      + 0x00000100 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_RMSK                                                         0x1
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_MAXm                                                          11
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_STOP_AGG_CDm_ADDR(m), HWIO_SW_OVERRIDE_STOP_AGG_CDm_RMSK)
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_STOP_AGG_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_STOP_AGG_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_STOP_AGG_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_STOP_AGG_CDm_INI(m))
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_SW_STOP_AGG_BMSK                                             0x1
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_SW_STOP_AGG_SHFT                                             0x0

#define HWIO_SW_PERMIT_ONE_AGG_CDm_ADDR(m)                                                  (BCM_SW_OVERRIDE_REG_BASE      + 0x00000180 + 0x4 * (m))
#define HWIO_SW_PERMIT_ONE_AGG_CDm_RMSK                                                            0x1
#define HWIO_SW_PERMIT_ONE_AGG_CDm_MAXm                                                             11
#define HWIO_SW_PERMIT_ONE_AGG_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_PERMIT_ONE_AGG_CDm_ADDR(m),val)
#define HWIO_SW_PERMIT_ONE_AGG_CDm_PERMIT_BMSK                                                     0x1
#define HWIO_SW_PERMIT_ONE_AGG_CDm_PERMIT_SHFT                                                     0x0

#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_ADDR(m)                                              (BCM_SW_OVERRIDE_REG_BASE      + 0x00000200 + 0x4 * (m))
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_RMSK                                                        0xf
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_MAXm                                                         11
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERWRITE_FINAL_CP_CDm_ADDR(m), HWIO_SW_OVERWRITE_FINAL_CP_CDm_RMSK)
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERWRITE_FINAL_CP_CDm_ADDR(m), mask)
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERWRITE_FINAL_CP_CDm_ADDR(m),val)
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERWRITE_FINAL_CP_CDm_ADDR(m),mask,val,HWIO_SW_OVERWRITE_FINAL_CP_CDm_INI(m))
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_FINAL_CP_BMSK                                               0xf
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_FINAL_CP_SHFT                                               0x0

#define HWIO_SW_BLOCK_FINAL_CP_CDm_ADDR(m)                                                  (BCM_SW_OVERRIDE_REG_BASE      + 0x00000280 + 0x4 * (m))
#define HWIO_SW_BLOCK_FINAL_CP_CDm_RMSK                                                            0x1
#define HWIO_SW_BLOCK_FINAL_CP_CDm_MAXm                                                             11
#define HWIO_SW_BLOCK_FINAL_CP_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_BLOCK_FINAL_CP_CDm_ADDR(m), HWIO_SW_BLOCK_FINAL_CP_CDm_RMSK)
#define HWIO_SW_BLOCK_FINAL_CP_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_BLOCK_FINAL_CP_CDm_ADDR(m), mask)
#define HWIO_SW_BLOCK_FINAL_CP_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_BLOCK_FINAL_CP_CDm_ADDR(m),val)
#define HWIO_SW_BLOCK_FINAL_CP_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_BLOCK_FINAL_CP_CDm_ADDR(m),mask,val,HWIO_SW_BLOCK_FINAL_CP_CDm_INI(m))
#define HWIO_SW_BLOCK_FINAL_CP_CDm_BLOCK_BMSK                                                      0x1
#define HWIO_SW_BLOCK_FINAL_CP_CDm_BLOCK_SHFT                                                      0x0

#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_ADDR(m)                                            (BCM_SW_OVERRIDE_REG_BASE      + 0x00000300 + 0x4 * (m))
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_RMSK                                                      0xf
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_MAXm                                                       11
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_ADDR(m), HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_RMSK)
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_ADDR(m), mask)
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_ADDR(m),val)
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_ADDR(m),mask,val,HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_INI(m))
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_WRITTEN_CP_BMSK                                           0xf
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_WRITTEN_CP_SHFT                                           0x0

#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_ADDR(m)                                            (BCM_SW_OVERRIDE_REG_BASE      + 0x00000380 + 0x4 * (m))
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_RMSK                                                      0xf
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_MAXm                                                       11
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERWRITE_CURRENT_CP_CDm_ADDR(m), HWIO_SW_OVERWRITE_CURRENT_CP_CDm_RMSK)
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERWRITE_CURRENT_CP_CDm_ADDR(m), mask)
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERWRITE_CURRENT_CP_CDm_ADDR(m),val)
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERWRITE_CURRENT_CP_CDm_ADDR(m),mask,val,HWIO_SW_OVERWRITE_CURRENT_CP_CDm_INI(m))
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_CURRENT_CP_BMSK                                           0xf
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_CURRENT_CP_SHFT                                           0x0

#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_ADDR(m)                                             (BCM_SW_OVERRIDE_REG_BASE      + 0x00000400 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_RMSK                                                       0x7
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_MAXm                                                        11
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_ADDR(m), HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_RMSK)
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_INI(m))
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_CP_SEL_BMSK                                                0x7
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_CP_SEL_SHFT                                                0x0

#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ADDR(m)                                             (BCM_SW_OVERRIDE_REG_BASE      + 0x00000480 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_RMSK                                                       0x1
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_MAXm                                                        11
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ADDR(m), HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_RMSK)
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_INI(m))
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ENABLE_BMSK                                                0x1
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ENABLE_SHFT                                                0x0

#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_ADDR(m)                                              (BCM_SW_OVERRIDE_REG_BASE      + 0x00000500 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_RMSK                                                        0x1
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_MAXm                                                         11
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_ADDR(m), HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_RMSK)
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_INI(m))
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_FLUSH_BMSK                                                  0x1
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_FLUSH_SHFT                                                  0x0

#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_ADDR(m)                                     (BCM_SW_OVERRIDE_REG_BASE      + 0x00000580 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_RMSK                                             0x111
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_MAXm                                                11
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_ADDR(m), HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_RMSK)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_INI(m))
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_C_BMSK                        0x100
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_C_SHFT                          0x8
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_B_BMSK                         0x10
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_B_SHFT                          0x4
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_A_BMSK                          0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_A_SHFT                          0x0

#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_ADDR(m)                                     (BCM_SW_OVERRIDE_REG_BASE      + 0x00000600 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_RMSK                                               0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_MAXm                                                11
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_SEQ_UNBLOCK_ONCE_A_BMSK                            0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_SEQ_UNBLOCK_ONCE_A_SHFT                            0x0

#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_ADDR(m)                                     (BCM_SW_OVERRIDE_REG_BASE      + 0x00000680 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_RMSK                                               0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_MAXm                                                11
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_SEQ_UNBLOCK_ONCE_B_BMSK                            0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_SEQ_UNBLOCK_ONCE_B_SHFT                            0x0

#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_ADDR(m)                                     (BCM_SW_OVERRIDE_REG_BASE      + 0x000006c0 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_RMSK                                               0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_MAXm                                                11
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_SEQ_UNBLOCK_ONCE_C_BMSK                            0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_SEQ_UNBLOCK_ONCE_C_SHFT                            0x0

#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_ADDR(m)                                               (BCM_SW_OVERRIDE_REG_BASE      + 0x00000700 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_RMSK                                                        0x11
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_MAXm                                                          11
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_CE_INPUT_CDm_ADDR(m), HWIO_SW_OVERRIDE_CE_INPUT_CDm_RMSK)
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_CE_INPUT_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_CE_INPUT_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_CE_INPUT_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_CE_INPUT_CDm_INI(m))
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_VALID_BMSK                                                  0x10
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_VALID_SHFT                                                   0x4
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_AGG_DONE_BMSK                                                0x1
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_AGG_DONE_SHFT                                                0x0

#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_ADDR(m)                                      (BCM_SW_OVERRIDE_REG_BASE      + 0x00000780 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_RMSK                                                0x1
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_MAXm                                                 11
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_ADDR(m), HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_RMSK)
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_INI(m))
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_FORCE_CLK_EN_BMSK                                   0x1
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_FORCE_CLK_EN_SHFT                                   0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_STARC
 *--------------------------------------------------------------------------*/

#define BCM_STARC_REG_BASE                                                             (AOSS_BASE      + 0x00bf2e00)
#define BCM_STARC_REG_BASE_SIZE                                                        0xb00
#define BCM_STARC_REG_BASE_USED                                                        0xa10

#define HWIO_STARC_CTRL_ADDR                                                           (BCM_STARC_REG_BASE      + 0x00000000)
#define HWIO_STARC_CTRL_RMSK                                                           0xc00003ff
#define HWIO_STARC_CTRL_IN          \
        in_dword(HWIO_STARC_CTRL_ADDR)
#define HWIO_STARC_CTRL_INM(m)      \
        in_dword_masked(HWIO_STARC_CTRL_ADDR, m)
#define HWIO_STARC_CTRL_OUT(v)      \
        out_dword(HWIO_STARC_CTRL_ADDR,v)
#define HWIO_STARC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_STARC_CTRL_ADDR,m,v,HWIO_STARC_CTRL_IN)
#define HWIO_STARC_CTRL_STARC_EN_BMSK                                                  0x80000000
#define HWIO_STARC_CTRL_STARC_EN_SHFT                                                        0x1f
#define HWIO_STARC_CTRL_STARC_DBG_EN_BMSK                                              0x40000000
#define HWIO_STARC_CTRL_STARC_DBG_EN_SHFT                                                    0x1e
#define HWIO_STARC_CTRL_STARC_EN_PER_VCD_BMSK                                               0x3ff
#define HWIO_STARC_CTRL_STARC_EN_PER_VCD_SHFT                                                 0x0

#define HWIO_SST_VCDvc_SSss_ADDR(vc,ss)                                                (BCM_STARC_REG_BASE      + 0x00000004 + 0x80 * (vc) + 0x4 * (ss))
#define HWIO_SST_VCDvc_SSss_RMSK                                                              0xf
#define HWIO_SST_VCDvc_SSss_MAXvc                                                               9
#define HWIO_SST_VCDvc_SSss_MAXss                                                              31
#define HWIO_SST_VCDvc_SSss_INI2(vc,ss)        \
        in_dword_masked(HWIO_SST_VCDvc_SSss_ADDR(vc,ss), HWIO_SST_VCDvc_SSss_RMSK)
#define HWIO_SST_VCDvc_SSss_INMI2(vc,ss,mask)    \
        in_dword_masked(HWIO_SST_VCDvc_SSss_ADDR(vc,ss), mask)
#define HWIO_SST_VCDvc_SSss_OUTI2(vc,ss,val)    \
        out_dword(HWIO_SST_VCDvc_SSss_ADDR(vc,ss),val)
#define HWIO_SST_VCDvc_SSss_OUTMI2(vc,ss,mask,val) \
        out_dword_masked_ns(HWIO_SST_VCDvc_SSss_ADDR(vc,ss),mask,val,HWIO_SST_VCDvc_SSss_INI2(vc,ss))
#define HWIO_SST_VCDvc_SSss_CP_BMSK                                                           0xf
#define HWIO_SST_VCDvc_SSss_CP_SHFT                                                           0x0

#define HWIO_STARC_STATUS_ADDR                                                         (BCM_STARC_REG_BASE      + 0x00000800)
#define HWIO_STARC_STATUS_RMSK                                                               0x1f
#define HWIO_STARC_STATUS_IN          \
        in_dword(HWIO_STARC_STATUS_ADDR)
#define HWIO_STARC_STATUS_INM(m)      \
        in_dword_masked(HWIO_STARC_STATUS_ADDR, m)
#define HWIO_STARC_STATUS_AGG_SYSTEM_STATE_BMSK                                              0x1f
#define HWIO_STARC_STATUS_AGG_SYSTEM_STATE_SHFT                                               0x0

#define HWIO_STARC_STATUS_VCDvc_L_ADDR(vc)                                             (BCM_STARC_REG_BASE      + 0x00000804 + 0x4 * (vc))
#define HWIO_STARC_STATUS_VCDvc_L_RMSK                                                 0xffffffff
#define HWIO_STARC_STATUS_VCDvc_L_MAXvc                                                         9
#define HWIO_STARC_STATUS_VCDvc_L_INI(vc)        \
        in_dword_masked(HWIO_STARC_STATUS_VCDvc_L_ADDR(vc), HWIO_STARC_STATUS_VCDvc_L_RMSK)
#define HWIO_STARC_STATUS_VCDvc_L_INMI(vc,mask)    \
        in_dword_masked(HWIO_STARC_STATUS_VCDvc_L_ADDR(vc), mask)
#define HWIO_STARC_STATUS_VCDvc_L_SYSTEM_STATE_MAP_LOWER_32BITS_BMSK                   0xffffffff
#define HWIO_STARC_STATUS_VCDvc_L_SYSTEM_STATE_MAP_LOWER_32BITS_SHFT                          0x0

#define HWIO_STARC_STATUS_VCDvc_H_ADDR(vc)                                             (BCM_STARC_REG_BASE      + 0x00000844 + 0x4 * (vc))
#define HWIO_STARC_STATUS_VCDvc_H_RMSK                                                 0xffffffff
#define HWIO_STARC_STATUS_VCDvc_H_MAXvc                                                         9
#define HWIO_STARC_STATUS_VCDvc_H_INI(vc)        \
        in_dword_masked(HWIO_STARC_STATUS_VCDvc_H_ADDR(vc), HWIO_STARC_STATUS_VCDvc_H_RMSK)
#define HWIO_STARC_STATUS_VCDvc_H_INMI(vc,mask)    \
        in_dword_masked(HWIO_STARC_STATUS_VCDvc_H_ADDR(vc), mask)
#define HWIO_STARC_STATUS_VCDvc_H_SYSTEM_STATE_MAP_UPPER_32BITS_BMSK                   0xffffffff
#define HWIO_STARC_STATUS_VCDvc_H_SYSTEM_STATE_MAP_UPPER_32BITS_SHFT                          0x0

#define HWIO_STARC_STATUS_VCDvc_ADDR(vc)                                               (BCM_STARC_REG_BASE      + 0x00000884 + 0x4 * (vc))
#define HWIO_STARC_STATUS_VCDvc_RMSK                                                          0xf
#define HWIO_STARC_STATUS_VCDvc_MAXvc                                                           9
#define HWIO_STARC_STATUS_VCDvc_INI(vc)        \
        in_dword_masked(HWIO_STARC_STATUS_VCDvc_ADDR(vc), HWIO_STARC_STATUS_VCDvc_RMSK)
#define HWIO_STARC_STATUS_VCDvc_INMI(vc,mask)    \
        in_dword_masked(HWIO_STARC_STATUS_VCDvc_ADDR(vc), mask)
#define HWIO_STARC_STATUS_VCDvc_MCP_BMSK                                                      0xf
#define HWIO_STARC_STATUS_VCDvc_MCP_SHFT                                                      0x0

#define HWIO_STARC_OVERRIDE_ADDR                                                       (BCM_STARC_REG_BASE      + 0x000008c4)
#define HWIO_STARC_OVERRIDE_RMSK                                                       0x8000001f
#define HWIO_STARC_OVERRIDE_IN          \
        in_dword(HWIO_STARC_OVERRIDE_ADDR)
#define HWIO_STARC_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_STARC_OVERRIDE_ADDR, m)
#define HWIO_STARC_OVERRIDE_OUT(v)      \
        out_dword(HWIO_STARC_OVERRIDE_ADDR,v)
#define HWIO_STARC_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_STARC_OVERRIDE_ADDR,m,v,HWIO_STARC_OVERRIDE_IN)
#define HWIO_STARC_OVERRIDE_EN_BMSK                                                    0x80000000
#define HWIO_STARC_OVERRIDE_EN_SHFT                                                          0x1f
#define HWIO_STARC_OVERRIDE_SS_BMSK                                                          0x1f
#define HWIO_STARC_OVERRIDE_SS_SHFT                                                           0x0

#define HWIO_STARC_SYSTEM_STATE_ADDR                                                   (BCM_STARC_REG_BASE      + 0x000008c8)
#define HWIO_STARC_SYSTEM_STATE_RMSK                                                   0xffffffff
#define HWIO_STARC_SYSTEM_STATE_IN          \
        in_dword(HWIO_STARC_SYSTEM_STATE_ADDR)
#define HWIO_STARC_SYSTEM_STATE_INM(m)      \
        in_dword_masked(HWIO_STARC_SYSTEM_STATE_ADDR, m)
#define HWIO_STARC_SYSTEM_STATE_OUT(v)      \
        out_dword(HWIO_STARC_SYSTEM_STATE_ADDR,v)
#define HWIO_STARC_SYSTEM_STATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_STARC_SYSTEM_STATE_ADDR,m,v,HWIO_STARC_SYSTEM_STATE_IN)
#define HWIO_STARC_SYSTEM_STATE_DIS_BMSK                                               0xffffffff
#define HWIO_STARC_SYSTEM_STATE_DIS_SHFT                                                      0x0

#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_ADDR                                    (BCM_STARC_REG_BASE      + 0x000008d0)
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_RMSK                                           0x1
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_IN          \
        in_dword(HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_ADDR)
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_INM(m)      \
        in_dword_masked(HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_ADDR, m)
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_OUT(v)      \
        out_dword(HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_ADDR,v)
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_ADDR,m,v,HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_IN)
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_DIS_BMSK                                       0x1
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_DIS_SHFT                                       0x0

#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_ADDR(ss)                            (BCM_STARC_REG_BASE      + 0x00000994 + 0x4 * (ss))
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_RMSK                                0xffffffff
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_MAXss                                       31
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_INI(ss)        \
        in_dword_masked(HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_ADDR(ss), HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_RMSK)
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_INMI(ss,mask)    \
        in_dword_masked(HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_ADDR(ss), mask)
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_COUNT_BMSK                          0xffffffff
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_COUNT_SHFT                                 0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_DDR_MNGR
 *--------------------------------------------------------------------------*/

#define BCM_DDR_MNGR_REG_BASE                                  (AOSS_BASE      + 0x00bf3900)
#define BCM_DDR_MNGR_REG_BASE_SIZE                             0x100
#define BCM_DDR_MNGR_REG_BASE_USED                             0x8c

#define HWIO_DDR_MNGR_HARDEN_CTRL_ADDR                         (BCM_DDR_MNGR_REG_BASE      + 0x00000000)
#define HWIO_DDR_MNGR_HARDEN_CTRL_RMSK                                0x1
#define HWIO_DDR_MNGR_HARDEN_CTRL_IN          \
        in_dword(HWIO_DDR_MNGR_HARDEN_CTRL_ADDR)
#define HWIO_DDR_MNGR_HARDEN_CTRL_INM(m)      \
        in_dword_masked(HWIO_DDR_MNGR_HARDEN_CTRL_ADDR, m)
#define HWIO_DDR_MNGR_HARDEN_CTRL_OUT(v)      \
        out_dword(HWIO_DDR_MNGR_HARDEN_CTRL_ADDR,v)
#define HWIO_DDR_MNGR_HARDEN_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_DDR_MNGR_HARDEN_CTRL_ADDR,m,v,HWIO_DDR_MNGR_HARDEN_CTRL_IN)
#define HWIO_DDR_MNGR_HARDEN_CTRL_DIS_BMSK                            0x1
#define HWIO_DDR_MNGR_HARDEN_CTRL_DIS_SHFT                            0x0

#define HWIO_DDRSS_CP_EN_ADDR                                  (BCM_DDR_MNGR_REG_BASE      + 0x00000004)
#define HWIO_DDRSS_CP_EN_RMSK                                    0xffffff
#define HWIO_DDRSS_CP_EN_IN          \
        in_dword(HWIO_DDRSS_CP_EN_ADDR)
#define HWIO_DDRSS_CP_EN_INM(m)      \
        in_dword_masked(HWIO_DDRSS_CP_EN_ADDR, m)
#define HWIO_DDRSS_CP_EN_OUT(v)      \
        out_dword(HWIO_DDRSS_CP_EN_ADDR,v)
#define HWIO_DDRSS_CP_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_DDRSS_CP_EN_ADDR,m,v,HWIO_DDRSS_CP_EN_IN)
#define HWIO_DDRSS_CP_EN_SHUB_CP_EN_BMSK                         0xff0000
#define HWIO_DDRSS_CP_EN_SHUB_CP_EN_SHFT                             0x10
#define HWIO_DDRSS_CP_EN_MC_CP_EN_BMSK                             0xffff
#define HWIO_DDRSS_CP_EN_MC_CP_EN_SHFT                                0x0

#define HWIO_DDR_PSol_TO_CP_LUT_ADDR(ol)                       (BCM_DDR_MNGR_REG_BASE      + 0x00000008 + 0x4 * (ol))
#define HWIO_DDR_PSol_TO_CP_LUT_RMSK                                0xf0f
#define HWIO_DDR_PSol_TO_CP_LUT_MAXol                                  15
#define HWIO_DDR_PSol_TO_CP_LUT_INI(ol)        \
        in_dword_masked(HWIO_DDR_PSol_TO_CP_LUT_ADDR(ol), HWIO_DDR_PSol_TO_CP_LUT_RMSK)
#define HWIO_DDR_PSol_TO_CP_LUT_INMI(ol,mask)    \
        in_dword_masked(HWIO_DDR_PSol_TO_CP_LUT_ADDR(ol), mask)
#define HWIO_DDR_PSol_TO_CP_LUT_OUTI(ol,val)    \
        out_dword(HWIO_DDR_PSol_TO_CP_LUT_ADDR(ol),val)
#define HWIO_DDR_PSol_TO_CP_LUT_OUTMI(ol,mask,val) \
        out_dword_masked_ns(HWIO_DDR_PSol_TO_CP_LUT_ADDR(ol),mask,val,HWIO_DDR_PSol_TO_CP_LUT_INI(ol))
#define HWIO_DDR_PSol_TO_CP_LUT_SHUB_CP_BMSK                        0xf00
#define HWIO_DDR_PSol_TO_CP_LUT_SHUB_CP_SHFT                          0x8
#define HWIO_DDR_PSol_TO_CP_LUT_MC_CP_BMSK                            0xf
#define HWIO_DDR_PSol_TO_CP_LUT_MC_CP_SHFT                            0x0

#define HWIO_DDR_MNGR_CPLOCK_CTRL_ADDR                         (BCM_DDR_MNGR_REG_BASE      + 0x00000048)
#define HWIO_DDR_MNGR_CPLOCK_CTRL_RMSK                                0x1
#define HWIO_DDR_MNGR_CPLOCK_CTRL_IN          \
        in_dword(HWIO_DDR_MNGR_CPLOCK_CTRL_ADDR)
#define HWIO_DDR_MNGR_CPLOCK_CTRL_INM(m)      \
        in_dword_masked(HWIO_DDR_MNGR_CPLOCK_CTRL_ADDR, m)
#define HWIO_DDR_MNGR_CPLOCK_CTRL_OUT(v)      \
        out_dword(HWIO_DDR_MNGR_CPLOCK_CTRL_ADDR,v)
#define HWIO_DDR_MNGR_CPLOCK_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_DDR_MNGR_CPLOCK_CTRL_ADDR,m,v,HWIO_DDR_MNGR_CPLOCK_CTRL_IN)
#define HWIO_DDR_MNGR_CPLOCK_CTRL_DIS_BMSK                            0x1
#define HWIO_DDR_MNGR_CPLOCK_CTRL_DIS_SHFT                            0x0

#define HWIO_DDR_MNGR_MCm_FLOOR_ADDR(m)                        (BCM_DDR_MNGR_REG_BASE      + 0x0000004c + 0x4 * (m))
#define HWIO_DDR_MNGR_MCm_FLOOR_RMSK                                  0xf
#define HWIO_DDR_MNGR_MCm_FLOOR_MAXm                                   15
#define HWIO_DDR_MNGR_MCm_FLOOR_INI(m)        \
        in_dword_masked(HWIO_DDR_MNGR_MCm_FLOOR_ADDR(m), HWIO_DDR_MNGR_MCm_FLOOR_RMSK)
#define HWIO_DDR_MNGR_MCm_FLOOR_INMI(m,mask)    \
        in_dword_masked(HWIO_DDR_MNGR_MCm_FLOOR_ADDR(m), mask)
#define HWIO_DDR_MNGR_MCm_FLOOR_OUTI(m,val)    \
        out_dword(HWIO_DDR_MNGR_MCm_FLOOR_ADDR(m),val)
#define HWIO_DDR_MNGR_MCm_FLOOR_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_DDR_MNGR_MCm_FLOOR_ADDR(m),mask,val,HWIO_DDR_MNGR_MCm_FLOOR_INI(m))
#define HWIO_DDR_MNGR_MCm_FLOOR_SHUB_CP_BMSK                          0xf
#define HWIO_DDR_MNGR_MCm_FLOOR_SHUB_CP_SHFT                          0x0

#define HWIO_DDR_MNGR_FE_TO_DDR_PS_ADDR                        (BCM_DDR_MNGR_REG_BASE      + 0x0000008c)
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_RMSK                              0xff
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_IN          \
        in_dword(HWIO_DDR_MNGR_FE_TO_DDR_PS_ADDR)
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_INM(m)      \
        in_dword_masked(HWIO_DDR_MNGR_FE_TO_DDR_PS_ADDR, m)
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_OUT(v)      \
        out_dword(HWIO_DDR_MNGR_FE_TO_DDR_PS_ADDR,v)
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_DDR_MNGR_FE_TO_DDR_PS_ADDR,m,v,HWIO_DDR_MNGR_FE_TO_DDR_PS_IN)
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_MOL_BMSK                          0xf0
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_MOL_SHFT                           0x4
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_BMOL_BMSK                          0xf
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_BMOL_SHFT                          0x0



#define HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d)                                                   (BCM_VOTETABLE_REG_BASE      + 0x00000000 + 0x10000 * (r) + 0x4 * (d))
#define HWIO_VOTETABLE_DRVr_NDd_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRVr_NDd_MAXd                                                                63
#define HWIO_VOTETABLE_DRVr_NDd_INI2(r,d)        \
        in_dword_masked(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d), HWIO_VOTETABLE_DRVr_NDd_RMSK)
#define HWIO_VOTETABLE_DRVr_NDd_INMI2(r,d,mask)    \
        in_dword_masked(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d), mask)
#define HWIO_VOTETABLE_DRVr_NDd_OUTI2(r,d,val)    \
        out_dword(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d),val)
#define HWIO_VOTETABLE_DRVr_NDd_OUTMI2(r,d,mask,val) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d),mask,val,HWIO_VOTETABLE_DRVr_NDd_INI2(r,d))



#endif /* __BCM_HWIO_H__ */
