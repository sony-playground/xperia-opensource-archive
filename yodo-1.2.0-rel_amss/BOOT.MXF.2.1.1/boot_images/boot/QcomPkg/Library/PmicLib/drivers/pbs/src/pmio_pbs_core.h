#ifndef __PMIO_PBS_CORE_H__
#define __PMIO_PBS_CORE_H__
/*
===========================================================================
*/
/**
  @file pmio_pbs_core.h
  @brief Auto-generated PMIO interface include file.

  This file contains PMIO register definitions for the following modules:
    PBS1_CORE
    PBS2_CORE
    PBS3_CORE

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2019 Qualcomm Technologies, Inc.
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

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pbs/src/pmio_pbs_core.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * PERIPHERAL: PBS1_CORE
 *--------------------------------------------------------------------------*/

#define PBS1_CORE_BASE                                                                0x00001600

#define PMIO_PBS1_CORE_REVISION1_ADDR                                                 (PBS1_CORE_BASE      + 0x00000000)
#define PMIO_PBS1_CORE_REVISION1_OFFS                                                 0x00000000
#define PMIO_PBS1_CORE_REVISION1_RMSK                                                       0xff
#define PMIO_PBS1_CORE_REVISION1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_REVISION1_ADDR, PMIO_PBS1_CORE_REVISION1_RMSK, 0, val)
#define PMIO_PBS1_CORE_REVISION1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_REVISION1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_REVISION1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_REVISION1_ADDR, val, len)
#define PMIO_PBS1_CORE_REVISION1_DIG_MINOR_BMSK                                             0xff
#define PMIO_PBS1_CORE_REVISION1_DIG_MINOR_SHFT                                              0x0

#define PMIO_PBS1_CORE_REVISION2_ADDR                                                 (PBS1_CORE_BASE      + 0x00000001)
#define PMIO_PBS1_CORE_REVISION2_OFFS                                                 0x00000001
#define PMIO_PBS1_CORE_REVISION2_RMSK                                                       0xff
#define PMIO_PBS1_CORE_REVISION2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_REVISION2_ADDR, PMIO_PBS1_CORE_REVISION2_RMSK, 0, val)
#define PMIO_PBS1_CORE_REVISION2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_REVISION2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_REVISION2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_REVISION2_ADDR, val, len)
#define PMIO_PBS1_CORE_REVISION2_DIG_MAJOR_BMSK                                             0xff
#define PMIO_PBS1_CORE_REVISION2_DIG_MAJOR_SHFT                                              0x0

#define PMIO_PBS1_CORE_REVISION3_ADDR                                                 (PBS1_CORE_BASE      + 0x00000002)
#define PMIO_PBS1_CORE_REVISION3_OFFS                                                 0x00000002
#define PMIO_PBS1_CORE_REVISION3_RMSK                                                       0xff
#define PMIO_PBS1_CORE_REVISION3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_REVISION3_ADDR, PMIO_PBS1_CORE_REVISION3_RMSK, 0, val)
#define PMIO_PBS1_CORE_REVISION3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_REVISION3_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_REVISION3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_REVISION3_ADDR, val, len)
#define PMIO_PBS1_CORE_REVISION3_ANA_MINOR_BMSK                                             0xff
#define PMIO_PBS1_CORE_REVISION3_ANA_MINOR_SHFT                                              0x0

#define PMIO_PBS1_CORE_REVISION4_ADDR                                                 (PBS1_CORE_BASE      + 0x00000003)
#define PMIO_PBS1_CORE_REVISION4_OFFS                                                 0x00000003
#define PMIO_PBS1_CORE_REVISION4_RMSK                                                       0xff
#define PMIO_PBS1_CORE_REVISION4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_REVISION4_ADDR, PMIO_PBS1_CORE_REVISION4_RMSK, 0, val)
#define PMIO_PBS1_CORE_REVISION4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_REVISION4_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_REVISION4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_REVISION4_ADDR, val, len)
#define PMIO_PBS1_CORE_REVISION4_ANA_MAJOR_BMSK                                             0xff
#define PMIO_PBS1_CORE_REVISION4_ANA_MAJOR_SHFT                                              0x0

#define PMIO_PBS1_CORE_PERPH_TYPE_ADDR                                                (PBS1_CORE_BASE      + 0x00000004)
#define PMIO_PBS1_CORE_PERPH_TYPE_OFFS                                                0x00000004
#define PMIO_PBS1_CORE_PERPH_TYPE_RMSK                                                      0xff
#define PMIO_PBS1_CORE_PERPH_TYPE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_TYPE_ADDR, PMIO_PBS1_CORE_PERPH_TYPE_RMSK, 0, val)
#define PMIO_PBS1_CORE_PERPH_TYPE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_TYPE_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PERPH_TYPE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PERPH_TYPE_ADDR, val, len)
#define PMIO_PBS1_CORE_PERPH_TYPE_TYPE_BMSK                                                 0xff
#define PMIO_PBS1_CORE_PERPH_TYPE_TYPE_SHFT                                                  0x0
#define PMIO_PBS1_CORE_PERPH_TYPE_TYPE_PBS_FVAL                                             0x16

#define PMIO_PBS1_CORE_PERPH_SUBTYPE_ADDR                                             (PBS1_CORE_BASE      + 0x00000005)
#define PMIO_PBS1_CORE_PERPH_SUBTYPE_OFFS                                             0x00000005
#define PMIO_PBS1_CORE_PERPH_SUBTYPE_RMSK                                                   0xff
#define PMIO_PBS1_CORE_PERPH_SUBTYPE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_SUBTYPE_ADDR, PMIO_PBS1_CORE_PERPH_SUBTYPE_RMSK, 0, val)
#define PMIO_PBS1_CORE_PERPH_SUBTYPE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_SUBTYPE_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PERPH_SUBTYPE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PERPH_SUBTYPE_ADDR, val, len)
#define PMIO_PBS1_CORE_PERPH_SUBTYPE_SUBTYPE_BMSK                                           0xff
#define PMIO_PBS1_CORE_PERPH_SUBTYPE_SUBTYPE_SHFT                                            0x0
#define PMIO_PBS1_CORE_PERPH_SUBTYPE_SUBTYPE_PBS_CORE_FVAL                                   0x1

#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_ADDR                                       (PBS1_CORE_BASE      + 0x00000006)
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_OFFS                                       0x00000006
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_RMSK                                             0x1f
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_ADDR, PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_RMSK, 0, val)
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_ADDR, val, len)
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_SHARED_OTP_CONFIG_BMSK                           0x10
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_SHARED_OTP_CONFIG_SHFT                            0x4
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_RAM_CONFIG_BMSK                             0x8
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_RAM_CONFIG_SHFT                             0x3
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_OTP_CONFIG_BMSK                             0x4
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_OTP_CONFIG_SHFT                             0x2
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_RAM_CONFIG_BMSK                             0x2
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_RAM_CONFIG_SHFT                             0x1
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_OTP_CONFIG_BMSK                             0x1
#define PMIO_PBS1_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_OTP_CONFIG_SHFT                             0x0

#define PMIO_PBS1_CORE_NUM_CLIENTS_ADDR                                               (PBS1_CORE_BASE      + 0x00000007)
#define PMIO_PBS1_CORE_NUM_CLIENTS_OFFS                                               0x00000007
#define PMIO_PBS1_CORE_NUM_CLIENTS_RMSK                                                     0xff
#define PMIO_PBS1_CORE_NUM_CLIENTS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_NUM_CLIENTS_ADDR, PMIO_PBS1_CORE_NUM_CLIENTS_RMSK, 0, val)
#define PMIO_PBS1_CORE_NUM_CLIENTS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_NUM_CLIENTS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_NUM_CLIENTS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_NUM_CLIENTS_ADDR, val, len)
#define PMIO_PBS1_CORE_NUM_CLIENTS_NUM_CLIENTS_BMSK                                         0xff
#define PMIO_PBS1_CORE_NUM_CLIENTS_NUM_CLIENTS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_STATUS0_ADDR                                               (PBS1_CORE_BASE      + 0x00000008)
#define PMIO_PBS1_CORE_SEQ_STATUS0_OFFS                                               0x00000008
#define PMIO_PBS1_CORE_SEQ_STATUS0_RMSK                                                     0x3f
#define PMIO_PBS1_CORE_SEQ_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_STATUS0_ADDR, PMIO_PBS1_CORE_SEQ_STATUS0_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_STATUS0_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_BMSK                                0x30
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_SHFT                                 0x4
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_RESERVED_FVAL                        0x0
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_NORMAL_FVAL                          0x1
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_ERROR_FVAL                           0x2
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_ABORT_FVAL                           0x3
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_BMSK                                        0xf
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_SHFT                                        0x0
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_0_FVAL                               0x0
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_1_FVAL                               0x1
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_2_FVAL                               0x2
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_3_FVAL                               0x3
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_4_FVAL                               0x4
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_5_FVAL                               0x5
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_6_FVAL                               0x6
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_7_FVAL                               0x7
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_8_FVAL                               0x8
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_9_FVAL                               0x9
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_10_FVAL                              0xa
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_11_FVAL                              0xb
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_12_FVAL                              0xc
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_13_FVAL                              0xd
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_14_FVAL                              0xe
#define PMIO_PBS1_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_15_FVAL                              0xf

#define PMIO_PBS1_CORE_NUM_TRIGCL_ADDR                                                (PBS1_CORE_BASE      + 0x00000009)
#define PMIO_PBS1_CORE_NUM_TRIGCL_OFFS                                                0x00000009
#define PMIO_PBS1_CORE_NUM_TRIGCL_RMSK                                                      0xff
#define PMIO_PBS1_CORE_NUM_TRIGCL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_NUM_TRIGCL_ADDR, PMIO_PBS1_CORE_NUM_TRIGCL_RMSK, 0, val)
#define PMIO_PBS1_CORE_NUM_TRIGCL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_NUM_TRIGCL_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_NUM_TRIGCL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_NUM_TRIGCL_ADDR, val, len)
#define PMIO_PBS1_CORE_NUM_TRIGCL_NUM_TRIGCL_BMSK                                           0xff
#define PMIO_PBS1_CORE_NUM_TRIGCL_NUM_TRIGCL_SHFT                                            0x0

#define PMIO_PBS1_CORE_SEQ_PC_STATUS0_ADDR                                            (PBS1_CORE_BASE      + 0x0000000a)
#define PMIO_PBS1_CORE_SEQ_PC_STATUS0_OFFS                                            0x0000000a
#define PMIO_PBS1_CORE_SEQ_PC_STATUS0_RMSK                                                  0xff
#define PMIO_PBS1_CORE_SEQ_PC_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_PC_STATUS0_ADDR, PMIO_PBS1_CORE_SEQ_PC_STATUS0_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_PC_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_PC_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_PC_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_PC_STATUS0_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_PC_STATUS0_PC_LSB_BMSK                                           0xff
#define PMIO_PBS1_CORE_SEQ_PC_STATUS0_PC_LSB_SHFT                                            0x0

#define PMIO_PBS1_CORE_SEQ_PC_STATUS1_ADDR                                            (PBS1_CORE_BASE      + 0x0000000b)
#define PMIO_PBS1_CORE_SEQ_PC_STATUS1_OFFS                                            0x0000000b
#define PMIO_PBS1_CORE_SEQ_PC_STATUS1_RMSK                                                  0xff
#define PMIO_PBS1_CORE_SEQ_PC_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_PC_STATUS1_ADDR, PMIO_PBS1_CORE_SEQ_PC_STATUS1_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_PC_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_PC_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_PC_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_PC_STATUS1_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_PC_STATUS1_PC_MSB_BMSK                                           0xff
#define PMIO_PBS1_CORE_SEQ_PC_STATUS1_PC_MSB_SHFT                                            0x0

#define PMIO_PBS1_CORE_SEQ_IR_STATUS0_ADDR                                            (PBS1_CORE_BASE      + 0x0000000c)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS0_OFFS                                            0x0000000c
#define PMIO_PBS1_CORE_SEQ_IR_STATUS0_RMSK                                                  0xff
#define PMIO_PBS1_CORE_SEQ_IR_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS0_ADDR, PMIO_PBS1_CORE_SEQ_IR_STATUS0_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS0_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS0_IR_BYTE0_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_IR_STATUS0_IR_BYTE0_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_IR_STATUS1_ADDR                                            (PBS1_CORE_BASE      + 0x0000000d)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS1_OFFS                                            0x0000000d
#define PMIO_PBS1_CORE_SEQ_IR_STATUS1_RMSK                                                  0xff
#define PMIO_PBS1_CORE_SEQ_IR_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS1_ADDR, PMIO_PBS1_CORE_SEQ_IR_STATUS1_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS1_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS1_IR_BYTE1_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_IR_STATUS1_IR_BYTE1_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_IR_STATUS2_ADDR                                            (PBS1_CORE_BASE      + 0x0000000e)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS2_OFFS                                            0x0000000e
#define PMIO_PBS1_CORE_SEQ_IR_STATUS2_RMSK                                                  0xff
#define PMIO_PBS1_CORE_SEQ_IR_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS2_ADDR, PMIO_PBS1_CORE_SEQ_IR_STATUS2_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS2_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS2_IR_BYTE2_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_IR_STATUS2_IR_BYTE2_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_IR_STATUS3_ADDR                                            (PBS1_CORE_BASE      + 0x0000000f)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS3_OFFS                                            0x0000000f
#define PMIO_PBS1_CORE_SEQ_IR_STATUS3_RMSK                                                  0xff
#define PMIO_PBS1_CORE_SEQ_IR_STATUS3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS3_ADDR, PMIO_PBS1_CORE_SEQ_IR_STATUS3_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS3_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_IR_STATUS3_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_IR_STATUS3_IR_BYTE3_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_IR_STATUS3_IR_BYTE3_SHFT                                          0x0

#define PMIO_PBS1_CORE_PMIC_CTL_CFG_ADDR                                              (PBS1_CORE_BASE      + 0x00000030)
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_OFFS                                              0x00000030
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_RMSK                                                    0xc0
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_CTL_CFG_ADDR, PMIO_PBS1_CORE_PMIC_CTL_CFG_RMSK, 0, val)
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_CTL_CFG_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC_CTL_CFG_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC_CTL_CFG_ADDR, val)
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_CTL_CFG_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PMIC_CTL_CFG_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_BMSK                                      0x80
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_SHFT                                       0x7
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_DISABLED_FVAL                              0x0
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_ENABLED_FVAL                               0x1
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_BMSK                                0x40
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_SHFT                                 0x6
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_MASTER_SECONDARY_ARB_FVAL            0x0
#define PMIO_PBS1_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_MASTER_PRIORITY_ARB_FVAL             0x1

#define PMIO_PBS1_CORE_PBS_WDOG_CTL_ADDR                                              (PBS1_CORE_BASE      + 0x00000031)
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_OFFS                                              0x00000031
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_RMSK                                                    0x80
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_CTL_ADDR, PMIO_PBS1_CORE_PBS_WDOG_CTL_RMSK, 0, val)
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_CTL_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_CTL_ADDR, val, len)
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_CTL_ADDR, val)
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_CTL_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_CTL_ADDR, val, len)
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_ENABLE_BMSK                                             0x80
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_ENABLE_SHFT                                              0x7
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_ENABLE_DISABLED_FVAL                                     0x0
#define PMIO_PBS1_CORE_PBS_WDOG_CTL_ENABLE_ENABLED_FVAL                                      0x1

#define PMIO_PBS1_CORE_PBS_WDOG_PET_ADDR                                              (PBS1_CORE_BASE      + 0x00000032)
#define PMIO_PBS1_CORE_PBS_WDOG_PET_OFFS                                              0x00000032
#define PMIO_PBS1_CORE_PBS_WDOG_PET_RMSK                                                    0x80
#define PMIO_PBS1_CORE_PBS_WDOG_PET_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_PET_ADDR, val)
#define PMIO_PBS1_CORE_PBS_WDOG_PET_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_PET_ADDR, val, len)
#define PMIO_PBS1_CORE_PBS_WDOG_PET_PET_BMSK                                                0x80
#define PMIO_PBS1_CORE_PBS_WDOG_PET_PET_SHFT                                                 0x7

#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_ADDR                                          (PBS1_CORE_BASE      + 0x00000033)
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_OFFS                                          0x00000033
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_RMSK                                                 0x3
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_ADDR, PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_RMSK, 0, val)
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_ADDR, val, len)
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_ADDR, val)
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_ADDR, val, len)
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_BMSK                                0x3
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_SHFT                                0x0
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_PBS_WDOG_1_MS_FVAL                  0x0
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_PBS_WDOG_10_MS_FVAL                 0x1
#define PMIO_PBS1_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_PBS_WDOG_100_MS_FVAL                0x2

#define PMIO_PBS1_CORE_PBS_SPMI_USID_ADDR                                             (PBS1_CORE_BASE      + 0x00000038)
#define PMIO_PBS1_CORE_PBS_SPMI_USID_OFFS                                             0x00000038
#define PMIO_PBS1_CORE_PBS_SPMI_USID_RMSK                                                    0xf
#define PMIO_PBS1_CORE_PBS_SPMI_USID_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_USID_ADDR, PMIO_PBS1_CORE_PBS_SPMI_USID_RMSK, 0, val)
#define PMIO_PBS1_CORE_PBS_SPMI_USID_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_USID_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PBS_SPMI_USID_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_USID_ADDR, val, len)
#define PMIO_PBS1_CORE_PBS_SPMI_USID_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_USID_ADDR, val)
#define PMIO_PBS1_CORE_PBS_SPMI_USID_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_USID_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PBS_SPMI_USID_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_USID_ADDR, val, len)
#define PMIO_PBS1_CORE_PBS_SPMI_USID_PBS_SPMI_USID_BMSK                                      0xf
#define PMIO_PBS1_CORE_PBS_SPMI_USID_PBS_SPMI_USID_SHFT                                      0x0

#define PMIO_PBS1_CORE_PBS_SPMI_GSID_ADDR                                             (PBS1_CORE_BASE      + 0x00000039)
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_OFFS                                             0x00000039
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_RMSK                                                   0xff
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_GSID_ADDR, PMIO_PBS1_CORE_PBS_SPMI_GSID_RMSK, 0, val)
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_GSID_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_GSID_ADDR, val, len)
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_GSID_ADDR, val)
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_GSID_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PBS_SPMI_GSID_ADDR, val, len)
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID1_BMSK                                    0xf0
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID1_SHFT                                     0x4
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID0_BMSK                                     0xf
#define PMIO_PBS1_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID0_SHFT                                     0x0

#define PMIO_PBS1_CORE_MEM_INTF_CFG_ADDR                                              (PBS1_CORE_BASE      + 0x00000040)
#define PMIO_PBS1_CORE_MEM_INTF_CFG_OFFS                                              0x00000040
#define PMIO_PBS1_CORE_MEM_INTF_CFG_RMSK                                                    0x80
#define PMIO_PBS1_CORE_MEM_INTF_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CFG_ADDR, PMIO_PBS1_CORE_MEM_INTF_CFG_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CFG_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CFG_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CFG_ADDR, val)
#define PMIO_PBS1_CORE_MEM_INTF_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CFG_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CFG_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_BMSK                                  0x80
#define PMIO_PBS1_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_SHFT                                   0x7
#define PMIO_PBS1_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_DISABLED_FVAL                          0x0
#define PMIO_PBS1_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_ENABLED_FVAL                           0x1

#define PMIO_PBS1_CORE_MEM_INTF_CTL_ADDR                                              (PBS1_CORE_BASE      + 0x00000041)
#define PMIO_PBS1_CORE_MEM_INTF_CTL_OFFS                                              0x00000041
#define PMIO_PBS1_CORE_MEM_INTF_CTL_RMSK                                                    0xc0
#define PMIO_PBS1_CORE_MEM_INTF_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CTL_ADDR, PMIO_PBS1_CORE_MEM_INTF_CTL_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CTL_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CTL_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CTL_ADDR, val)
#define PMIO_PBS1_CORE_MEM_INTF_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CTL_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_CTL_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_CTL_BURST_BMSK                                              0x80
#define PMIO_PBS1_CORE_MEM_INTF_CTL_BURST_SHFT                                               0x7
#define PMIO_PBS1_CORE_MEM_INTF_CTL_BURST_SINGLE_MODE_FVAL                                   0x0
#define PMIO_PBS1_CORE_MEM_INTF_CTL_BURST_BURST_MODE_FVAL                                    0x1
#define PMIO_PBS1_CORE_MEM_INTF_CTL_WR_EN_BMSK                                              0x40
#define PMIO_PBS1_CORE_MEM_INTF_CTL_WR_EN_SHFT                                               0x6
#define PMIO_PBS1_CORE_MEM_INTF_CTL_WR_EN_READ_ACCESS_FVAL                                   0x0
#define PMIO_PBS1_CORE_MEM_INTF_CTL_WR_EN_WRITE_ACCESS_FVAL                                  0x1

#define PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_ADDR                                         (PBS1_CORE_BASE      + 0x00000042)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_OFFS                                         0x00000042
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_RMSK                                               0xff
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_ADDR, PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_ADDR, val)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_MEM_INTF_ADDR_LSB_BMSK                             0xff
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_LSB_MEM_INTF_ADDR_LSB_SHFT                              0x0

#define PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_ADDR                                         (PBS1_CORE_BASE      + 0x00000043)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_OFFS                                         0x00000043
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_RMSK                                               0xff
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_ADDR, PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_ADDR, val)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_MEM_INTF_ADDR_MSB_BMSK                             0xff
#define PMIO_PBS1_CORE_MEM_INTF_ADDR_MSB_MEM_INTF_ADDR_MSB_SHFT                              0x0

#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_ADDR                                         (PBS1_CORE_BASE      + 0x00000048)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_OFFS                                         0x00000048
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_RMSK                                               0xff
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_ADDR, PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_ADDR, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_MEM_INTF_WR_DATA_0_BMSK                            0xff
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA0_MEM_INTF_WR_DATA_0_SHFT                             0x0

#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_ADDR                                         (PBS1_CORE_BASE      + 0x00000049)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_OFFS                                         0x00000049
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_RMSK                                               0xff
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_ADDR, PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_ADDR, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_MEM_INTF_WR_DATA_1_BMSK                            0xff
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA1_MEM_INTF_WR_DATA_1_SHFT                             0x0

#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_ADDR                                         (PBS1_CORE_BASE      + 0x0000004a)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_OFFS                                         0x0000004a
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_RMSK                                               0xff
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_ADDR, PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_ADDR, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_MEM_INTF_WR_DATA_2_BMSK                            0xff
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA2_MEM_INTF_WR_DATA_2_SHFT                             0x0

#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_ADDR                                         (PBS1_CORE_BASE      + 0x0000004b)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_OFFS                                         0x0000004b
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_RMSK                                               0xff
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_ADDR, PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_ADDR, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_MEM_INTF_WR_DATA_3_BMSK                            0xff
#define PMIO_PBS1_CORE_MEM_INTF_WR_DATA3_MEM_INTF_WR_DATA_3_SHFT                             0x0

#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_ADDR                                         (PBS1_CORE_BASE      + 0x0000004c)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_OFFS                                         0x0000004c
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_RMSK                                               0xff
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_ADDR, PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_MEM_INTF_RD_DATA_0_BMSK                            0xff
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA0_MEM_INTF_RD_DATA_0_SHFT                             0x0

#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_ADDR                                         (PBS1_CORE_BASE      + 0x0000004d)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_OFFS                                         0x0000004d
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_RMSK                                               0xff
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_ADDR, PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_MEM_INTF_RD_DATA_1_BMSK                            0xff
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA1_MEM_INTF_RD_DATA_1_SHFT                             0x0

#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_ADDR                                         (PBS1_CORE_BASE      + 0x0000004e)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_OFFS                                         0x0000004e
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_RMSK                                               0xff
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_ADDR, PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_MEM_INTF_RD_DATA_2_BMSK                            0xff
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA2_MEM_INTF_RD_DATA_2_SHFT                             0x0

#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_ADDR                                         (PBS1_CORE_BASE      + 0x0000004f)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_OFFS                                         0x0000004f
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_RMSK                                               0xff
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_ADDR, PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_RMSK, 0, val)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_ADDR, val, len)
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_MEM_INTF_RD_DATA_3_BMSK                            0xff
#define PMIO_PBS1_CORE_MEM_INTF_RD_DATA3_MEM_INTF_RD_DATA_3_SHFT                             0x0

#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_ADDR                                     (PBS1_CORE_BASE      + 0x00000050)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_OFFS                                     0x00000050
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_RMSK                                           0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_ADDR, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_RMSK, 0, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_ADDR, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_SEQ_ADDR_LSB_BMSK                              0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_0_SEQ_ADDR_LSB_SHFT                               0x0

#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_ADDR                                     (PBS1_CORE_BASE      + 0x00000054)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_OFFS                                     0x00000054
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_RMSK                                           0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_ADDR, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_RMSK, 0, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_ADDR, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_SEQ_ADDR_LSB_BMSK                              0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_1_SEQ_ADDR_LSB_SHFT                               0x0

#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_ADDR                                     (PBS1_CORE_BASE      + 0x00000058)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_OFFS                                     0x00000058
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_RMSK                                           0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_ADDR, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_RMSK, 0, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_ADDR, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_SEQ_ADDR_LSB_BMSK                              0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_LSB_2_SEQ_ADDR_LSB_SHFT                               0x0

#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_ADDR                                     (PBS1_CORE_BASE      + 0x00000051)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_OFFS                                     0x00000051
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_RMSK                                           0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_ADDR, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_RMSK, 0, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_ADDR, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_SEQ_ADDR_MSB_BMSK                              0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_0_SEQ_ADDR_MSB_SHFT                               0x0

#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_ADDR                                     (PBS1_CORE_BASE      + 0x00000055)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_OFFS                                     0x00000055
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_RMSK                                           0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_ADDR, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_RMSK, 0, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_ADDR, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_SEQ_ADDR_MSB_BMSK                              0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_1_SEQ_ADDR_MSB_SHFT                               0x0

#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_ADDR                                     (PBS1_CORE_BASE      + 0x00000059)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_OFFS                                     0x00000059
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_RMSK                                           0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_ADDR, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_RMSK, 0, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_ADDR, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_SEQ_ADDR_MSB_BMSK                              0xff
#define PMIO_PBS1_CORE_TRIG_START_ADDR_MSB_2_SEQ_ADDR_MSB_SHFT                               0x0

#define PMIO_PBS1_CORE_SEQ_STATUS1_ADDR                                               (PBS1_CORE_BASE      + 0x00000090)
#define PMIO_PBS1_CORE_SEQ_STATUS1_OFFS                                               0x00000090
#define PMIO_PBS1_CORE_SEQ_STATUS1_RMSK                                                     0xff
#define PMIO_PBS1_CORE_SEQ_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_STATUS1_ADDR, PMIO_PBS1_CORE_SEQ_STATUS1_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_STATUS1_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_BMSK                                      0xf0
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_SHFT                                       0x4
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_0_FVAL                              0x0
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_1_FVAL                              0x1
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_2_FVAL                              0x2
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_3_FVAL                              0x3
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_4_FVAL                              0x4
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_5_FVAL                              0x5
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_6_FVAL                              0x6
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_7_FVAL                              0x7
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_8_FVAL                              0x8
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_9_FVAL                              0x9
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_10_FVAL                             0xa
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_11_FVAL                             0xb
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_12_FVAL                             0xc
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_13_FVAL                             0xd
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_14_FVAL                             0xe
#define PMIO_PBS1_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_15_FVAL                             0xf
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_BMSK                                      0xf
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_SHFT                                      0x0
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_0_FVAL                             0x0
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_1_FVAL                             0x1
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_2_FVAL                             0x2
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_3_FVAL                             0x3
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_4_FVAL                             0x4
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_5_FVAL                             0x5
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_6_FVAL                             0x6
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_7_FVAL                             0x7
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_8_FVAL                             0x8
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_9_FVAL                             0x9
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_10_FVAL                            0xa
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_11_FVAL                            0xb
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_12_FVAL                            0xc
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_13_FVAL                            0xd
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_14_FVAL                            0xe
#define PMIO_PBS1_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_15_FVAL                            0xf

#define PMIO_PBS1_CORE_SEQ_STATUS2_ADDR                                               (PBS1_CORE_BASE      + 0x00000091)
#define PMIO_PBS1_CORE_SEQ_STATUS2_OFFS                                               0x00000091
#define PMIO_PBS1_CORE_SEQ_STATUS2_RMSK                                                     0xff
#define PMIO_PBS1_CORE_SEQ_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_STATUS2_ADDR, PMIO_PBS1_CORE_SEQ_STATUS2_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_STATUS2_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_BMSK                                    0xf0
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_SHFT                                     0x4
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_0_FVAL                            0x0
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_1_FVAL                            0x1
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_2_FVAL                            0x2
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_3_FVAL                            0x3
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_4_FVAL                            0x4
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_5_FVAL                            0x5
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_6_FVAL                            0x6
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_7_FVAL                            0x7
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_8_FVAL                            0x8
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_9_FVAL                            0x9
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_10_FVAL                           0xa
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_11_FVAL                           0xb
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_12_FVAL                           0xc
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_13_FVAL                           0xd
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_14_FVAL                           0xe
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_15_FVAL                           0xf
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_BMSK                                       0xf
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_SHFT                                       0x0
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_0_FVAL                              0x0
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_1_FVAL                              0x1
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_2_FVAL                              0x2
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_3_FVAL                              0x3
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_4_FVAL                              0x4
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_5_FVAL                              0x5
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_6_FVAL                              0x6
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_7_FVAL                              0x7
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_8_FVAL                              0x8
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_9_FVAL                              0x9
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_10_FVAL                             0xa
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_11_FVAL                             0xb
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_12_FVAL                             0xc
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_13_FVAL                             0xd
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_14_FVAL                             0xe
#define PMIO_PBS1_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_15_FVAL                             0xf

#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_ADDR                                        (PBS1_CORE_BASE      + 0x00000092)
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_OFFS                                        0x00000092
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_RMSK                                              0xff
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_ADDR, PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_ERR_PC_LSB_BMSK                                   0xff
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS0_ERR_PC_LSB_SHFT                                    0x0

#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_ADDR                                        (PBS1_CORE_BASE      + 0x00000093)
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_OFFS                                        0x00000093
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_RMSK                                              0xff
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_ADDR, PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_ERR_PC_MSB_BMSK                                   0xff
#define PMIO_PBS1_CORE_SEQ_ERR_PC_STATUS1_ERR_PC_MSB_SHFT                                    0x0

#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_ADDR                                        (PBS1_CORE_BASE      + 0x00000094)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_OFFS                                        0x00000094
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_RMSK                                              0xff
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_ADDR, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_ERR_IR_BYTE0_BMSK                                 0xff
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS0_ERR_IR_BYTE0_SHFT                                  0x0

#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_ADDR                                        (PBS1_CORE_BASE      + 0x00000095)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_OFFS                                        0x00000095
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_RMSK                                              0xff
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_ADDR, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_ERR_IR_BYTE1_BMSK                                 0xff
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS1_ERR_IR_BYTE1_SHFT                                  0x0

#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_ADDR                                        (PBS1_CORE_BASE      + 0x00000096)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_OFFS                                        0x00000096
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_RMSK                                              0xff
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_ADDR, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_ERR_IR_BYTE2_BMSK                                 0xff
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS2_ERR_IR_BYTE2_SHFT                                  0x0

#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_ADDR                                        (PBS1_CORE_BASE      + 0x00000097)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_OFFS                                        0x00000097
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_RMSK                                              0xff
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_ADDR, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_ERR_IR_BYTE3_BMSK                                 0xff
#define PMIO_PBS1_CORE_SEQ_ERR_IR_STATUS3_ERR_IR_BYTE3_SHFT                                  0x0

#define PMIO_PBS1_CORE_TRIG_STATUS0_ADDR                                              (PBS1_CORE_BASE      + 0x00000098)
#define PMIO_PBS1_CORE_TRIG_STATUS0_OFFS                                              0x00000098
#define PMIO_PBS1_CORE_TRIG_STATUS0_RMSK                                                    0x7f
#define PMIO_PBS1_CORE_TRIG_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS0_ADDR, PMIO_PBS1_CORE_TRIG_STATUS0_RMSK, 0, val)
#define PMIO_PBS1_CORE_TRIG_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS0_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_STATUS0_LAST_TRIG_COMP_BMSK                                     0x7f
#define PMIO_PBS1_CORE_TRIG_STATUS0_LAST_TRIG_COMP_SHFT                                      0x0

#define PMIO_PBS1_CORE_TRIG_STATUS1_ADDR                                              (PBS1_CORE_BASE      + 0x00000099)
#define PMIO_PBS1_CORE_TRIG_STATUS1_OFFS                                              0x00000099
#define PMIO_PBS1_CORE_TRIG_STATUS1_RMSK                                                    0x7f
#define PMIO_PBS1_CORE_TRIG_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS1_ADDR, PMIO_PBS1_CORE_TRIG_STATUS1_RMSK, 0, val)
#define PMIO_PBS1_CORE_TRIG_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS1_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_STATUS1_LAST_TRIG_NORMAL_BMSK                                   0x7f
#define PMIO_PBS1_CORE_TRIG_STATUS1_LAST_TRIG_NORMAL_SHFT                                    0x0

#define PMIO_PBS1_CORE_TRIG_STATUS2_ADDR                                              (PBS1_CORE_BASE      + 0x0000009a)
#define PMIO_PBS1_CORE_TRIG_STATUS2_OFFS                                              0x0000009a
#define PMIO_PBS1_CORE_TRIG_STATUS2_RMSK                                                    0x7f
#define PMIO_PBS1_CORE_TRIG_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS2_ADDR, PMIO_PBS1_CORE_TRIG_STATUS2_RMSK, 0, val)
#define PMIO_PBS1_CORE_TRIG_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS2_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_STATUS2_TRIG_IN_SERVICE_BMSK                                    0x7f
#define PMIO_PBS1_CORE_TRIG_STATUS2_TRIG_IN_SERVICE_SHFT                                     0x0

#define PMIO_PBS1_CORE_TRIG_STATUS3_ADDR                                              (PBS1_CORE_BASE      + 0x0000009b)
#define PMIO_PBS1_CORE_TRIG_STATUS3_OFFS                                              0x0000009b
#define PMIO_PBS1_CORE_TRIG_STATUS3_RMSK                                                    0x7f
#define PMIO_PBS1_CORE_TRIG_STATUS3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS3_ADDR, PMIO_PBS1_CORE_TRIG_STATUS3_RMSK, 0, val)
#define PMIO_PBS1_CORE_TRIG_STATUS3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS3_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_STATUS3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS3_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_STATUS3_LAST_TRIG_ERROR_BMSK                                    0x7f
#define PMIO_PBS1_CORE_TRIG_STATUS3_LAST_TRIG_ERROR_SHFT                                     0x0

#define PMIO_PBS1_CORE_TRIG_STATUS4_ADDR                                              (PBS1_CORE_BASE      + 0x0000009c)
#define PMIO_PBS1_CORE_TRIG_STATUS4_OFFS                                              0x0000009c
#define PMIO_PBS1_CORE_TRIG_STATUS4_RMSK                                                    0x7f
#define PMIO_PBS1_CORE_TRIG_STATUS4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS4_ADDR, PMIO_PBS1_CORE_TRIG_STATUS4_RMSK, 0, val)
#define PMIO_PBS1_CORE_TRIG_STATUS4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS4_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TRIG_STATUS4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TRIG_STATUS4_ADDR, val, len)
#define PMIO_PBS1_CORE_TRIG_STATUS4_LAST_TRIG_ABORTED_BMSK                                  0x7f
#define PMIO_PBS1_CORE_TRIG_STATUS4_LAST_TRIG_ABORTED_SHFT                                   0x0

#define PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_ADDR                                    (PBS1_CORE_BASE      + 0x0000009d)
#define PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_OFFS                                    0x0000009d
#define PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_RMSK                                           0x1
#define PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_ADDR, PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_ENABLE_DONE_STATUS_BMSK                        0x1
#define PMIO_PBS1_CORE_PCE_ENABLE_DONE_STATUS_ENABLE_DONE_STATUS_SHFT                        0x0

#define PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_ADDR                                    (PBS1_CORE_BASE      + 0x0000009e)
#define PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_OFFS                                    0x0000009e
#define PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_RMSK                                           0x1
#define PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_ADDR, PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_ACCESS_DONE_STATUS_BMSK                        0x1
#define PMIO_PBS1_CORE_RIF_ACCESS_DONE_STATUS_ACCESS_DONE_STATUS_SHFT                        0x0

#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_ADDR                                       (PBS1_CORE_BASE      + 0x0000009f)
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_OFFS                                       0x0000009f
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_RMSK                                             0xff
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_EOS_NOT_EMPTY_ERROR_BMSK                0x80
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_EOS_NOT_EMPTY_ERROR_SHFT                 0x7
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_OVERFLOW_ERROR_BMSK                     0x40
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_OVERFLOW_ERROR_SHFT                      0x6
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_UNDERFLOW_ERROR_BMSK                    0x20
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_UNDERFLOW_ERROR_SHFT                     0x5
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_SPMI_ERROR_BMSK                                  0x10
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_SPMI_ERROR_SHFT                                   0x4
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_LSID_ERROR_BMSK                                   0x8
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_LSID_ERROR_SHFT                                   0x3
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_SPECIAL_USID_ERROR_BMSK                           0x4
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_SPECIAL_USID_ERROR_SHFT                           0x2
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_USID_ERROR_BMSK                                   0x2
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_USID_ERROR_SHFT                                   0x1
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_INVALID_CMD_ERROR_BMSK                            0x1
#define PMIO_PBS1_CORE_SEQ_ERR_TYPE_STATUS_INVALID_CMD_ERROR_SHFT                            0x0

#define PMIO_PBS1_CORE_RAM_CFG1_ADDR                                                  (PBS1_CORE_BASE      + 0x000000a0)
#define PMIO_PBS1_CORE_RAM_CFG1_OFFS                                                  0x000000a0
#define PMIO_PBS1_CORE_RAM_CFG1_RMSK                                                        0xff
#define PMIO_PBS1_CORE_RAM_CFG1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_RAM_CFG1_ADDR, PMIO_PBS1_CORE_RAM_CFG1_RMSK, 0, val)
#define PMIO_PBS1_CORE_RAM_CFG1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_RAM_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_RAM_CFG1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_RAM_CFG1_ADDR, val, len)
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_BMSK                                                   0xff
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_SHFT                                                    0x0
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_NO_RAM_FVAL                                             0x0
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_SIZE_32X32_FVAL                                         0x1
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_SIZE_64X32_FVAL                                         0x2
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_SIZE_96X32_FVAL                                         0x3
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_SIZE_128X32_FVAL                                        0x4
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_SIZE_160X32_FVAL                                        0x5
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_SIZE_192X32_FVAL                                        0x6
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_SIZE_224X32_FVAL                                        0x7
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_SIZE_256X32_FVAL                                        0x8
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_SIZE_512X32_FVAL                                       0x10
#define PMIO_PBS1_CORE_RAM_CFG1_SIZE_SIZE_1024X32_FVAL                                      0x20

#define PMIO_PBS1_CORE_RAM_CFG2_ADDR                                                  (PBS1_CORE_BASE      + 0x000000a1)
#define PMIO_PBS1_CORE_RAM_CFG2_OFFS                                                  0x000000a1
#define PMIO_PBS1_CORE_RAM_CFG2_RMSK                                                        0xe0
#define PMIO_PBS1_CORE_RAM_CFG2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_RAM_CFG2_ADDR, PMIO_PBS1_CORE_RAM_CFG2_RMSK, 0, val)
#define PMIO_PBS1_CORE_RAM_CFG2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_RAM_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_RAM_CFG2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_RAM_CFG2_ADDR, val, len)
#define PMIO_PBS1_CORE_RAM_CFG2_MTYPE_BMSK                                                  0xe0
#define PMIO_PBS1_CORE_RAM_CFG2_MTYPE_SHFT                                                   0x5
#define PMIO_PBS1_CORE_RAM_CFG2_MTYPE_RAM18U_FVAL                                            0x0
#define PMIO_PBS1_CORE_RAM_CFG2_MTYPE_RAM65N_FVAL                                            0x1
#define PMIO_PBS1_CORE_RAM_CFG2_MTYPE_RAM15U_FVAL                                            0x2
#define PMIO_PBS1_CORE_RAM_CFG2_MTYPE_RAM22NM_FVAL                                           0x3
#define PMIO_PBS1_CORE_RAM_CFG2_MTYPE_RAM28NM_FVAL                                           0x4

#define PMIO_PBS1_CORE_NVM_CFG1_ADDR                                                  (PBS1_CORE_BASE      + 0x000000a2)
#define PMIO_PBS1_CORE_NVM_CFG1_OFFS                                                  0x000000a2
#define PMIO_PBS1_CORE_NVM_CFG1_RMSK                                                        0xff
#define PMIO_PBS1_CORE_NVM_CFG1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_NVM_CFG1_ADDR, PMIO_PBS1_CORE_NVM_CFG1_RMSK, 0, val)
#define PMIO_PBS1_CORE_NVM_CFG1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_NVM_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_NVM_CFG1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_NVM_CFG1_ADDR, val, len)
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_BMSK                                                   0xff
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_SHFT                                                    0x0
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_NO_OTP_FVAL                                             0x0
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_32_FVAL                                       0x1
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_64_FVAL                                       0x2
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_96_FVAL                                       0x3
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_128_FVAL                                      0x4
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_160_FVAL                                      0x5
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_192_FVAL                                      0x6
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_224_FVAL                                      0x7
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_256_FVAL                                      0x8
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_288_FVAL                                      0x9
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_320_FVAL                                      0xa
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_352_FVAL                                      0xb
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_384_FVAL                                      0xc
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_416_FVAL                                      0xd
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_448_FVAL                                      0xe
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_480_FVAL                                      0xf
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_512_FVAL                                     0x10
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_544_FVAL                                     0x11
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_576_FVAL                                     0x12
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_608_FVAL                                     0x13
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_640_FVAL                                     0x14
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_672_FVAL                                     0x15
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_704_FVAL                                     0x16
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_736_FVAL                                     0x17
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_768_FVAL                                     0x18
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_800_FVAL                                     0x19
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_832_FVAL                                     0x1a
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_864_FVAL                                     0x1b
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_896_FVAL                                     0x1c
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_928_FVAL                                     0x1d
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_960_FVAL                                     0x1e
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_992_FVAL                                     0x1f
#define PMIO_PBS1_CORE_NVM_CFG1_SIZE_ADDRESSES_1024_FVAL                                    0x20

#define PMIO_PBS1_CORE_NVM_CFG2_ADDR                                                  (PBS1_CORE_BASE      + 0x000000a3)
#define PMIO_PBS1_CORE_NVM_CFG2_OFFS                                                  0x000000a3
#define PMIO_PBS1_CORE_NVM_CFG2_RMSK                                                        0xf3
#define PMIO_PBS1_CORE_NVM_CFG2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_NVM_CFG2_ADDR, PMIO_PBS1_CORE_NVM_CFG2_RMSK, 0, val)
#define PMIO_PBS1_CORE_NVM_CFG2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_NVM_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_NVM_CFG2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_NVM_CFG2_ADDR, val, len)
#define PMIO_PBS1_CORE_NVM_CFG2_MTYPE_BMSK                                                  0xe0
#define PMIO_PBS1_CORE_NVM_CFG2_MTYPE_SHFT                                                   0x5
#define PMIO_PBS1_CORE_NVM_CFG2_MTYPE_EMEMORY_FVAL                                           0x0
#define PMIO_PBS1_CORE_NVM_CFG2_MTYPE_KILOPASS_FVAL                                          0x1
#define PMIO_PBS1_CORE_NVM_CFG2_MTYPE_EMEMORY15UM_FVAL                                       0x2
#define PMIO_PBS1_CORE_NVM_CFG2_MTYPE_KILOPASS22NM_FVAL                                      0x3
#define PMIO_PBS1_CORE_NVM_CFG2_MTYPE_EMEMORY28NM_FVAL                                       0x4
#define PMIO_PBS1_CORE_NVM_CFG2_TYPE_BMSK                                                   0x10
#define PMIO_PBS1_CORE_NVM_CFG2_TYPE_SHFT                                                    0x4
#define PMIO_PBS1_CORE_NVM_CFG2_TYPE_OTP_FVAL                                                0x0
#define PMIO_PBS1_CORE_NVM_CFG2_TYPE_ROM_FVAL                                                0x1
#define PMIO_PBS1_CORE_NVM_CFG2_ACCESS_BMSK                                                  0x3
#define PMIO_PBS1_CORE_NVM_CFG2_ACCESS_SHFT                                                  0x0
#define PMIO_PBS1_CORE_NVM_CFG2_ACCESS_WRITE_1200US_READ_800NS_INSTR_PR_1510NS_FVAL          0x0
#define PMIO_PBS1_CORE_NVM_CFG2_ACCESS_WRITE_600US_READ_400NS_INSTR_PR_940NS_FVAL            0x1
#define PMIO_PBS1_CORE_NVM_CFG2_ACCESS_WRITE_300US_READ_200NS_INSTR_PR_730NS_FVAL            0x2

#define PMIO_PBS1_CORE_PARAM_SETTINGS_ADDR                                            (PBS1_CORE_BASE      + 0x000000a4)
#define PMIO_PBS1_CORE_PARAM_SETTINGS_OFFS                                            0x000000a4
#define PMIO_PBS1_CORE_PARAM_SETTINGS_RMSK                                                  0x8f
#define PMIO_PBS1_CORE_PARAM_SETTINGS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PARAM_SETTINGS_ADDR, PMIO_PBS1_CORE_PARAM_SETTINGS_RMSK, 0, val)
#define PMIO_PBS1_CORE_PARAM_SETTINGS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PARAM_SETTINGS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PARAM_SETTINGS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PARAM_SETTINGS_ADDR, val, len)
#define PMIO_PBS1_CORE_PARAM_SETTINGS_FAST_PBS_BMSK                                         0x80
#define PMIO_PBS1_CORE_PARAM_SETTINGS_FAST_PBS_SHFT                                          0x7
#define PMIO_PBS1_CORE_PARAM_SETTINGS_FAST_PBS_REGULAR_PBS_FVAL                              0x0
#define PMIO_PBS1_CORE_PARAM_SETTINGS_FAST_PBS_FAST_PBS_ON_FVAL                              0x1
#define PMIO_PBS1_CORE_PARAM_SETTINGS_NUM_MACHINE_REGS_BMSK                                  0xf
#define PMIO_PBS1_CORE_PARAM_SETTINGS_NUM_MACHINE_REGS_SHFT                                  0x0

#define PMIO_PBS1_CORE_RAM_CFG3_ADDR                                                  (PBS1_CORE_BASE      + 0x000000a6)
#define PMIO_PBS1_CORE_RAM_CFG3_OFFS                                                  0x000000a6
#define PMIO_PBS1_CORE_RAM_CFG3_RMSK                                                        0xff
#define PMIO_PBS1_CORE_RAM_CFG3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_RAM_CFG3_ADDR, PMIO_PBS1_CORE_RAM_CFG3_RMSK, 0, val)
#define PMIO_PBS1_CORE_RAM_CFG3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_RAM_CFG3_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_RAM_CFG3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_RAM_CFG3_ADDR, val, len)
#define PMIO_PBS1_CORE_RAM_CFG3_SIZE_MSB_BMSK                                               0xff
#define PMIO_PBS1_CORE_RAM_CFG3_SIZE_MSB_SHFT                                                0x0

#define PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_ADDR                                      (PBS1_CORE_BASE      + 0x000000a8)
#define PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_OFFS                                      0x000000a8
#define PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_RMSK                                             0x1
#define PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_ADDR, PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_RMSK, 0, val)
#define PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_ADDR, val)
#define PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_WR_INHIBIT_BMSK                                  0x1
#define PMIO_PBS1_CORE_PMIC7_OTP_WR_INHIBIT_WR_INHIBIT_SHFT                                  0x0

#define PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_ADDR                                  (PBS1_CORE_BASE      + 0x000000a9)
#define PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_OFFS                                  0x000000a9
#define PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_RMSK                                         0x1
#define PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_ADDR, PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_PENVDD2_STATUS_BMSK                          0x1
#define PMIO_PBS1_CORE_PMIC7_OTP_PENVDD2_STATUS_PENVDD2_STATUS_SHFT                          0x0

#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_ADDR                                       (PBS1_CORE_BASE      + 0x000000aa)
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_OFFS                                       0x000000aa
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_RMSK                                             0xff
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_RMSK, 0, val)
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, val)
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_BMSK                                0x80
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_SHFT                                 0x7
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_SLEEP_FVAL                           0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_ACTIVE_FVAL                          0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_BMSK                                0x40
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_SHFT                                 0x6
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_SLEEP_FVAL                           0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_ACTIVE_FVAL                          0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_BMSK                                0x20
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_SHFT                                 0x5
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_SLEEP_FVAL                           0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_ACTIVE_FVAL                          0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_BMSK                                0x10
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_SHFT                                 0x4
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_SLEEP_FVAL                           0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_ACTIVE_FVAL                          0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_BMSK                                  0x8
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_SHFT                                  0x3
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_SLEEP_FVAL                            0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_ACTIVE_FVAL                           0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_BMSK                                  0x4
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_SHFT                                  0x2
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_SLEEP_FVAL                            0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_ACTIVE_FVAL                           0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_BMSK                                  0x2
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_SHFT                                  0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_SLEEP_FVAL                            0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_ACTIVE_FVAL                           0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_BMSK                                  0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_SHFT                                  0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_SLEEP_FVAL                            0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_ACTIVE_FVAL                           0x1

#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR                                    (PBS1_CORE_BASE      + 0x000000ab)
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_OFFS                                    0x000000ab
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_RMSK                                          0xff
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR, PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_BMSK                        0x80
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_SHFT                         0x7
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_SLEEP_FVAL                   0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_ACTIVE_FVAL                  0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_BMSK                        0x40
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_SHFT                         0x6
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_SLEEP_FVAL                   0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_ACTIVE_FVAL                  0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_BMSK                        0x20
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_SHFT                         0x5
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_SLEEP_FVAL                   0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_ACTIVE_FVAL                  0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_BMSK                        0x10
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_SHFT                         0x4
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_SLEEP_FVAL                   0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_ACTIVE_FVAL                  0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_BMSK                          0x8
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_SHFT                          0x3
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_SLEEP_FVAL                    0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_ACTIVE_FVAL                   0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_BMSK                          0x4
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_SHFT                          0x2
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_SLEEP_FVAL                    0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_ACTIVE_FVAL                   0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_BMSK                          0x2
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_SHFT                          0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_SLEEP_FVAL                    0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_ACTIVE_FVAL                   0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_BMSK                          0x1
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_SHFT                          0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_SLEEP_FVAL                    0x0
#define PMIO_PBS1_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_ACTIVE_FVAL                   0x1

#define PMIO_PBS1_CORE_PMIC7_RAM_ACC_ADDR                                             (PBS1_CORE_BASE      + 0x000000ac)
#define PMIO_PBS1_CORE_PMIC7_RAM_ACC_OFFS                                             0x000000ac
#define PMIO_PBS1_CORE_PMIC7_RAM_ACC_RMSK                                                    0xf
#define PMIO_PBS1_CORE_PMIC7_RAM_ACC_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_ACC_ADDR, PMIO_PBS1_CORE_PMIC7_RAM_ACC_RMSK, 0, val)
#define PMIO_PBS1_CORE_PMIC7_RAM_ACC_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_ACC_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC7_RAM_ACC_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_ACC_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC7_RAM_ACC_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_ACC_ADDR, val)
#define PMIO_PBS1_CORE_PMIC7_RAM_ACC_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_ACC_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC7_RAM_ACC_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_RAM_ACC_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC7_RAM_ACC_ACC_BMSK                                                0xf
#define PMIO_PBS1_CORE_PMIC7_RAM_ACC_ACC_SHFT                                                0x0

#define PMIO_PBS1_CORE_PBS_CLK_CTL_n_ADDR(n)                                          (PBS1_CORE_BASE      + (0x000000ad + 0x1 * (n)))
#define PMIO_PBS1_CORE_PBS_CLK_CTL_n_OFFS(n)                                          (0x000000ad + 0x1 * (n))
#define PMIO_PBS1_CORE_PBS_CLK_CTL_n_RMSK                                                    0x1
#define PMIO_PBS1_CORE_PBS_CLK_CTL_n_INI(ctxt, pmic, n, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_CLK_CTL_n_ADDR(n), PMIO_PBS1_CORE_PBS_CLK_CTL_n_RMSK, 0, val)
#define PMIO_PBS1_CORE_PBS_CLK_CTL_n_INFI(ctxt, pmic, n, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_CLK_CTL_n_ADDR(n), mask, shift, val)
#define PMIO_PBS1_CORE_PBS_CLK_CTL_n_INNI(ctxt, pmic, n, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PBS_CLK_CTL_n_ADDR(n), val, len)
#define PMIO_PBS1_CORE_PBS_CLK_CTL_n_OUTI(ctxt, pmic, n, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PBS_CLK_CTL_n_ADDR(n), val)
#define PMIO_PBS1_CORE_PBS_CLK_CTL_n_OUTFI(ctxt, pmic, n, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PBS_CLK_CTL_n_ADDR(n), mask, shift, val)
#define PMIO_PBS1_CORE_PBS_CLK_CTL_n_OUTNI(ctxt, pmic, n, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PBS_CLK_CTL_n_ADDR(n), val, len)
#define PMIO_PBS1_CORE_PBS_CLK_CTL_n_PBS_CLK_GATE_EN_BMSK                                    0x1
#define PMIO_PBS1_CORE_PBS_CLK_CTL_n_PBS_CLK_GATE_EN_SHFT                                    0x0

#define PMIO_PBS1_CORE_SEQ_R0_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000b0)
#define PMIO_PBS1_CORE_SEQ_R0_STATUS_OFFS                                             0x000000b0
#define PMIO_PBS1_CORE_SEQ_R0_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_R0_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R0_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_R0_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_R0_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R0_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_R0_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R0_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_R0_STATUS_R0_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_R0_STATUS_R0_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_R1_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000b1)
#define PMIO_PBS1_CORE_SEQ_R1_STATUS_OFFS                                             0x000000b1
#define PMIO_PBS1_CORE_SEQ_R1_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_R1_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R1_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_R1_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_R1_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R1_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_R1_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R1_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_R1_STATUS_R1_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_R1_STATUS_R1_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_R2_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000b2)
#define PMIO_PBS1_CORE_SEQ_R2_STATUS_OFFS                                             0x000000b2
#define PMIO_PBS1_CORE_SEQ_R2_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_R2_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R2_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_R2_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_R2_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R2_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_R2_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R2_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_R2_STATUS_R2_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_R2_STATUS_R2_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_R3_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000b3)
#define PMIO_PBS1_CORE_SEQ_R3_STATUS_OFFS                                             0x000000b3
#define PMIO_PBS1_CORE_SEQ_R3_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_R3_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R3_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_R3_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_R3_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R3_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_R3_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R3_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_R3_STATUS_R3_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_R3_STATUS_R3_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_R4_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000b4)
#define PMIO_PBS1_CORE_SEQ_R4_STATUS_OFFS                                             0x000000b4
#define PMIO_PBS1_CORE_SEQ_R4_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_R4_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R4_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_R4_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_R4_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R4_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_R4_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R4_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_R4_STATUS_R4_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_R4_STATUS_R4_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_R5_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000b5)
#define PMIO_PBS1_CORE_SEQ_R5_STATUS_OFFS                                             0x000000b5
#define PMIO_PBS1_CORE_SEQ_R5_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_R5_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R5_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_R5_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_R5_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R5_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_R5_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R5_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_R5_STATUS_R5_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_R5_STATUS_R5_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_R6_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000b6)
#define PMIO_PBS1_CORE_SEQ_R6_STATUS_OFFS                                             0x000000b6
#define PMIO_PBS1_CORE_SEQ_R6_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_R6_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R6_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_R6_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_R6_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R6_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_R6_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R6_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_R6_STATUS_R6_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_R6_STATUS_R6_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_R7_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000b7)
#define PMIO_PBS1_CORE_SEQ_R7_STATUS_OFFS                                             0x000000b7
#define PMIO_PBS1_CORE_SEQ_R7_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_R7_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R7_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_R7_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_R7_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R7_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_R7_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R7_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_R7_STATUS_R7_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_R7_STATUS_R7_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_R8_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000b8)
#define PMIO_PBS1_CORE_SEQ_R8_STATUS_OFFS                                             0x000000b8
#define PMIO_PBS1_CORE_SEQ_R8_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_R8_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R8_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_R8_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_R8_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R8_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_R8_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R8_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_R8_STATUS_R8_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_R8_STATUS_R8_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_R9_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000b9)
#define PMIO_PBS1_CORE_SEQ_R9_STATUS_OFFS                                             0x000000b9
#define PMIO_PBS1_CORE_SEQ_R9_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_R9_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R9_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_R9_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_R9_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R9_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_R9_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_R9_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_R9_STATUS_R9_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_R9_STATUS_R9_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_RA_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000ba)
#define PMIO_PBS1_CORE_SEQ_RA_STATUS_OFFS                                             0x000000ba
#define PMIO_PBS1_CORE_SEQ_RA_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_RA_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RA_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_RA_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_RA_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RA_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_RA_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RA_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_RA_STATUS_RA_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_RA_STATUS_RA_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_RB_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000bb)
#define PMIO_PBS1_CORE_SEQ_RB_STATUS_OFFS                                             0x000000bb
#define PMIO_PBS1_CORE_SEQ_RB_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_RB_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RB_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_RB_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_RB_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RB_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_RB_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RB_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_RB_STATUS_RB_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_RB_STATUS_RB_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_RC_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000bc)
#define PMIO_PBS1_CORE_SEQ_RC_STATUS_OFFS                                             0x000000bc
#define PMIO_PBS1_CORE_SEQ_RC_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_RC_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RC_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_RC_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_RC_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RC_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_RC_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RC_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_RC_STATUS_RC_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_RC_STATUS_RC_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_RD_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000bd)
#define PMIO_PBS1_CORE_SEQ_RD_STATUS_OFFS                                             0x000000bd
#define PMIO_PBS1_CORE_SEQ_RD_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_RD_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RD_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_RD_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_RD_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RD_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_RD_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RD_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_RD_STATUS_RD_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_RD_STATUS_RD_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_RE_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000be)
#define PMIO_PBS1_CORE_SEQ_RE_STATUS_OFFS                                             0x000000be
#define PMIO_PBS1_CORE_SEQ_RE_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_RE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RE_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_RE_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_RE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_RE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RE_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_RE_STATUS_RE_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_RE_STATUS_RE_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_SEQ_RF_STATUS_ADDR                                             (PBS1_CORE_BASE      + 0x000000bf)
#define PMIO_PBS1_CORE_SEQ_RF_STATUS_OFFS                                             0x000000bf
#define PMIO_PBS1_CORE_SEQ_RF_STATUS_RMSK                                                   0xff
#define PMIO_PBS1_CORE_SEQ_RF_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RF_STATUS_ADDR, PMIO_PBS1_CORE_SEQ_RF_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_RF_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RF_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_RF_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_RF_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_RF_STATUS_RF_STATUS_BMSK                                         0xff
#define PMIO_PBS1_CORE_SEQ_RF_STATUS_RF_STATUS_SHFT                                          0x0

#define PMIO_PBS1_CORE_LOCKBIT_D1_ADDR                                                (PBS1_CORE_BASE      + 0x000000d1)
#define PMIO_PBS1_CORE_LOCKBIT_D1_OFFS                                                0x000000d1
#define PMIO_PBS1_CORE_LOCKBIT_D1_RMSK                                                       0x3
#define PMIO_PBS1_CORE_LOCKBIT_D1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_LOCKBIT_D1_ADDR, PMIO_PBS1_CORE_LOCKBIT_D1_RMSK, 0, val)
#define PMIO_PBS1_CORE_LOCKBIT_D1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_LOCKBIT_D1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_LOCKBIT_D1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_LOCKBIT_D1_ADDR, val, len)
#define PMIO_PBS1_CORE_LOCKBIT_D1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_LOCKBIT_D1_ADDR, val)
#define PMIO_PBS1_CORE_LOCKBIT_D1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_LOCKBIT_D1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_LOCKBIT_D1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_LOCKBIT_D1_ADDR, val, len)
#define PMIO_PBS1_CORE_LOCKBIT_D1_LOCKBIT_D1_BMSK                                            0x3
#define PMIO_PBS1_CORE_LOCKBIT_D1_LOCKBIT_D1_SHFT                                            0x0
#define PMIO_PBS1_CORE_LOCKBIT_D1_LOCKBIT_D1_OPEN_FVAL                                       0x0
#define PMIO_PBS1_CORE_LOCKBIT_D1_LOCKBIT_D1_RSVD_FVAL                                       0x1
#define PMIO_PBS1_CORE_LOCKBIT_D1_LOCKBIT_D1_LOCKED_OPEN_FVAL                                0x2
#define PMIO_PBS1_CORE_LOCKBIT_D1_LOCKBIT_D1_LOCKED_CLOSED_FVAL                              0x3

#define PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_ADDR                                      (PBS1_CORE_BASE      + 0x000000d4)
#define PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_OFFS                                      0x000000d4
#define PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_RMSK                                             0x1
#define PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_ADDR, PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_RMSK, 0, val)
#define PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_ADDR, val)
#define PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_ADDR, val, len)
#define PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_LOCKBIT_D1_BMSK                                  0x1
#define PMIO_PBS1_CORE_ILLEGAL_WRITE_STATUS_LOCKBIT_D1_SHFT                                  0x0

#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_ADDR                                          (PBS1_CORE_BASE      + 0x000000d9)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_OFFS                                          0x000000d9
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_RMSK                                                 0x1
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL2_ADDR, PMIO_PBS1_CORE_PERPH_RESET_CTL2_RMSK, 0, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL2_ADDR, val, len)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL2_ADDR, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL2_ADDR, val, len)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_BMSK                           0x1
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_SHFT                           0x0
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_RESET_IGNORED_FVAL             0x0
#define PMIO_PBS1_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_RESET_ARMED_FVAL               0x1

#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_ADDR                                          (PBS1_CORE_BASE      + 0x000000da)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_OFFS                                          0x000000da
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_RMSK                                                 0x7
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL3_ADDR, PMIO_PBS1_CORE_PERPH_RESET_CTL3_RMSK, 0, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL3_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL3_ADDR, val, len)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL3_ADDR, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL3_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL3_ADDR, val, len)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_BMSK                                  0x4
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_SHFT                                  0x2
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_RESET_IGNORED_FVAL                    0x0
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_RESET_ARMED_FVAL                      0x1
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_BMSK                             0x2
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_SHFT                             0x1
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_RESET_IGNORED_FVAL               0x0
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_RESET_ARMED_FVAL                 0x1
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_BMSK                             0x1
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_SHFT                             0x0
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_RESET_IGNORED_FVAL               0x0
#define PMIO_PBS1_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_RESET_ARMED_FVAL                 0x1

#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_ADDR                                          (PBS1_CORE_BASE      + 0x000000db)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_OFFS                                          0x000000db
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_RMSK                                                 0x1
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL4_ADDR, PMIO_PBS1_CORE_PERPH_RESET_CTL4_RMSK, 0, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL4_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL4_ADDR, val, len)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL4_ADDR, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL4_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PERPH_RESET_CTL4_ADDR, val, len)
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_BMSK                                0x1
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_SHFT                                0x0
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_NORMAL_OPERATION_FVAL               0x0
#define PMIO_PBS1_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_SOFT_RESET_ASSERTED_FVAL            0x1

#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_ADDR                                             (PBS1_CORE_BASE      + 0x000000e0)
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_OFFS                                             0x000000e0
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_RMSK                                                    0x3
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_CFG_ADDR, PMIO_PBS1_CORE_SEQ_DEBUG_CFG_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_CFG_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_CFG_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_CFG_ADDR, val)
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_CFG_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_CFG_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_BMSK                                        0x2
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_SHFT                                        0x1
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_DEBUG_NEXT_CMD_FVAL                         0x0
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_DEBUG_NEXT_DTEST_FVAL                       0x1
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_DEBUG_EN_BMSK                                           0x1
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_DEBUG_EN_SHFT                                           0x0
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_DEBUG_EN_DISABLED_FVAL                                  0x0
#define PMIO_PBS1_CORE_SEQ_DEBUG_CFG_DEBUG_EN_ENABLED_FVAL                                   0x1

#define PMIO_PBS1_CORE_SEQ_DEBUG_NEXT_ADDR                                            (PBS1_CORE_BASE      + 0x000000e1)
#define PMIO_PBS1_CORE_SEQ_DEBUG_NEXT_OFFS                                            0x000000e1
#define PMIO_PBS1_CORE_SEQ_DEBUG_NEXT_RMSK                                                   0x1
#define PMIO_PBS1_CORE_SEQ_DEBUG_NEXT_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_NEXT_ADDR, val)
#define PMIO_PBS1_CORE_SEQ_DEBUG_NEXT_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_NEXT_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_BMSK                                          0x1
#define PMIO_PBS1_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_SHFT                                          0x0
#define PMIO_PBS1_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_DEBUG_NEXT_NOP_FVAL                           0x0
#define PMIO_PBS1_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_DEBUG_NEXT_TRIGGER_FVAL                       0x1

#define PMIO_PBS1_CORE_OTP_CFG1_ADDR                                                  (PBS1_CORE_BASE      + 0x000000e2)
#define PMIO_PBS1_CORE_OTP_CFG1_OFFS                                                  0x000000e2
#define PMIO_PBS1_CORE_OTP_CFG1_RMSK                                                         0xf
#define PMIO_PBS1_CORE_OTP_CFG1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG1_ADDR, PMIO_PBS1_CORE_OTP_CFG1_RMSK, 0, val)
#define PMIO_PBS1_CORE_OTP_CFG1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_OTP_CFG1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG1_ADDR, val, len)
#define PMIO_PBS1_CORE_OTP_CFG1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG1_ADDR, val)
#define PMIO_PBS1_CORE_OTP_CFG1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_OTP_CFG1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG1_ADDR, val, len)
#define PMIO_PBS1_CORE_OTP_CFG1_VPP_SEL_BMSK                                                 0x8
#define PMIO_PBS1_CORE_OTP_CFG1_VPP_SEL_SHFT                                                 0x3
#define PMIO_PBS1_CORE_OTP_CFG1_VPP_SEL_DVDD_FVAL                                            0x0
#define PMIO_PBS1_CORE_OTP_CFG1_VPP_SEL_VPP_EXT_FVAL                                         0x1
#define PMIO_PBS1_CORE_OTP_CFG1_PPROG_BMSK                                                   0x4
#define PMIO_PBS1_CORE_OTP_CFG1_PPROG_SHFT                                                   0x2
#define PMIO_PBS1_CORE_OTP_CFG1_PPROG_OTP_PROGRAMMING_DISABLED_FVAL                          0x0
#define PMIO_PBS1_CORE_OTP_CFG1_PPROG_OTP_PROGRAMMING_ENABLED_FVAL                           0x1
#define PMIO_PBS1_CORE_OTP_CFG1_PTM_BMSK                                                     0x3
#define PMIO_PBS1_CORE_OTP_CFG1_PTM_SHFT                                                     0x0
#define PMIO_PBS1_CORE_OTP_CFG1_PTM_REGULAR_MODES_FVAL                                       0x0
#define PMIO_PBS1_CORE_OTP_CFG1_PTM_RESERVED_FVAL                                            0x1
#define PMIO_PBS1_CORE_OTP_CFG1_PTM_MARGIN_1_READ_MODE_FVAL                                  0x2
#define PMIO_PBS1_CORE_OTP_CFG1_PTM_MARGIN_2_READ_MODE_FVAL                                  0x3

#define PMIO_PBS1_CORE_OTP_CFG2_ADDR                                                  (PBS1_CORE_BASE      + 0x000000e3)
#define PMIO_PBS1_CORE_OTP_CFG2_OFFS                                                  0x000000e3
#define PMIO_PBS1_CORE_OTP_CFG2_RMSK                                                        0x1f
#define PMIO_PBS1_CORE_OTP_CFG2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG2_ADDR, PMIO_PBS1_CORE_OTP_CFG2_RMSK, 0, val)
#define PMIO_PBS1_CORE_OTP_CFG2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_OTP_CFG2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG2_ADDR, val, len)
#define PMIO_PBS1_CORE_OTP_CFG2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG2_ADDR, val)
#define PMIO_PBS1_CORE_OTP_CFG2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_OTP_CFG2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_OTP_CFG2_ADDR, val, len)
#define PMIO_PBS1_CORE_OTP_CFG2_MARGIN_RD_WS_BMSK                                           0x1f
#define PMIO_PBS1_CORE_OTP_CFG2_MARGIN_RD_WS_SHFT                                            0x0

#define PMIO_PBS1_CORE_TEST1_ADDR                                                     (PBS1_CORE_BASE      + 0x000000e4)
#define PMIO_PBS1_CORE_TEST1_OFFS                                                     0x000000e4
#define PMIO_PBS1_CORE_TEST1_RMSK                                                           0xff
#define PMIO_PBS1_CORE_TEST1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TEST1_ADDR, PMIO_PBS1_CORE_TEST1_RMSK, 0, val)
#define PMIO_PBS1_CORE_TEST1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TEST1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TEST1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_TEST1_ADDR, val, len)
#define PMIO_PBS1_CORE_TEST1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_TEST1_ADDR, val)
#define PMIO_PBS1_CORE_TEST1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_TEST1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_TEST1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_TEST1_ADDR, val, len)
#define PMIO_PBS1_CORE_TEST1_DTEST4_EN_BMSK                                                 0x80
#define PMIO_PBS1_CORE_TEST1_DTEST4_EN_SHFT                                                  0x7
#define PMIO_PBS1_CORE_TEST1_DTEST4_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS1_CORE_TEST1_DTEST4_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS1_CORE_TEST1_DTEST3_EN_BMSK                                                 0x40
#define PMIO_PBS1_CORE_TEST1_DTEST3_EN_SHFT                                                  0x6
#define PMIO_PBS1_CORE_TEST1_DTEST3_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS1_CORE_TEST1_DTEST3_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS1_CORE_TEST1_DTEST2_EN_BMSK                                                 0x20
#define PMIO_PBS1_CORE_TEST1_DTEST2_EN_SHFT                                                  0x5
#define PMIO_PBS1_CORE_TEST1_DTEST2_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS1_CORE_TEST1_DTEST2_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS1_CORE_TEST1_DTEST1_EN_BMSK                                                 0x10
#define PMIO_PBS1_CORE_TEST1_DTEST1_EN_SHFT                                                  0x4
#define PMIO_PBS1_CORE_TEST1_DTEST1_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS1_CORE_TEST1_DTEST1_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS1_CORE_TEST1_DTEST_SEL_BMSK                                                  0xf
#define PMIO_PBS1_CORE_TEST1_DTEST_SEL_SHFT                                                  0x0

#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_ADDR                                           (PBS1_CORE_BASE      + 0x000000e5)
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_OFFS                                           0x000000e5
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_RMSK                                                  0x7
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_ADDR, PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_ADDR, val)
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_BMSK                                  0x7
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_SHFT                                  0x0
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST1_FVAL                           0x0
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST2_FVAL                           0x1
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST3_FVAL                           0x2
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST4_FVAL                           0x3
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST5_FVAL                           0x4
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST6_FVAL                           0x5
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST7_FVAL                           0x6
#define PMIO_PBS1_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST8_FVAL                           0x7

#define PMIO_PBS1_CORE_PMIC_OTP_CFG2_ADDR                                             (PBS1_CORE_BASE      + 0x000000e8)
#define PMIO_PBS1_CORE_PMIC_OTP_CFG2_OFFS                                             0x000000e8
#define PMIO_PBS1_CORE_PMIC_OTP_CFG2_RMSK                                                    0x1
#define PMIO_PBS1_CORE_PMIC_OTP_CFG2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_CFG2_ADDR, PMIO_PBS1_CORE_PMIC_OTP_CFG2_RMSK, 0, val)
#define PMIO_PBS1_CORE_PMIC_OTP_CFG2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC_OTP_CFG2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_CFG2_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC_OTP_CFG2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_CFG2_ADDR, val)
#define PMIO_PBS1_CORE_PMIC_OTP_CFG2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC_OTP_CFG2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_CFG2_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC_OTP_CFG2_PDSTB_BMSK                                              0x1
#define PMIO_PBS1_CORE_PMIC_OTP_CFG2_PDSTB_SHFT                                              0x0

#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_ADDR                                     (PBS1_CORE_BASE      + 0x000000e9)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_OFFS                                     0x000000e9
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_RMSK                                            0x1
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_ADDR, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_RMSK, 0, val)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_ADDR, val)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_PCE_FORCE_ON_BMSK                               0x1
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_ON_PCE_FORCE_ON_SHFT                               0x0

#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_ADDR                                    (PBS1_CORE_BASE      + 0x000000ea)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_OFFS                                    0x000000ea
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_RMSK                                           0x1
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_ADDR, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_RMSK, 0, val)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_ADDR, val)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_PCE_FORCE_OFF_BMSK                             0x1
#define PMIO_PBS1_CORE_PMIC_OTP_PCE_FORCE_OFF_PCE_FORCE_OFF_SHFT                             0x0

#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_ADDR                                            (PBS1_CORE_BASE      + 0x000000eb)
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_OFFS                                            0x000000eb
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_RMSK                                                  0xfb
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_CFG1_ADDR, PMIO_PBS1_CORE_PMIC7_OTP_CFG1_RMSK, 0, val)
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_CFG1_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_CFG1_ADDR, val)
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_PMIC7_OTP_CFG1_ADDR, val, len)
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_PTM_BMSK                                              0xf0
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_PTM_SHFT                                               0x4
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_PPROG_BMSK                                             0x8
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_PPROG_SHFT                                             0x3
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_PTC_BMSK                                               0x2
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_PTC_SHFT                                               0x1
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_PTR_BMSK                                               0x1
#define PMIO_PBS1_CORE_PMIC7_OTP_CFG1_PTR_SHFT                                               0x0

#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_ADDR                                        (PBS1_CORE_BASE      + 0x000000ec)
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_OFFS                                        0x000000ec
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_RMSK                                               0x1
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_ADDR, PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_ADDR, val)
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_BP_EN_BMSK                                         0x1
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_BP_EN_SHFT                                         0x0
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_BP_EN_DISABLED_FVAL                                0x0
#define PMIO_PBS1_CORE_SEQ_BREAKPOINT_CFG_BP_EN_ENABLED_FVAL                                 0x1

#define PMIO_PBS1_CORE_SEQ_BP_CTL_ADDR                                                (PBS1_CORE_BASE      + 0x000000ed)
#define PMIO_PBS1_CORE_SEQ_BP_CTL_OFFS                                                0x000000ed
#define PMIO_PBS1_CORE_SEQ_BP_CTL_RMSK                                                       0x1
#define PMIO_PBS1_CORE_SEQ_BP_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_CTL_ADDR, val)
#define PMIO_PBS1_CORE_SEQ_BP_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_CTL_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_BP_CTL_BP_CONTINUE_BMSK                                           0x1
#define PMIO_PBS1_CORE_SEQ_BP_CTL_BP_CONTINUE_SHFT                                           0x0
#define PMIO_PBS1_CORE_SEQ_BP_CTL_BP_CONTINUE_DEBUG_NEXT_NOP_FVAL                            0x0
#define PMIO_PBS1_CORE_SEQ_BP_CTL_BP_CONTINUE_DEBUG_NEXT_TRIGGER_FVAL                        0x1

#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_ADDR                                           (PBS1_CORE_BASE      + 0x000000ee)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_OFFS                                           0x000000ee
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_RMSK                                                 0xff
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_ADDR, PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_ADDR, val)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_BMSK                                     0xff
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_SHFT                                      0x0
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_DEBUG_NEXT_NOP_FVAL                       0x0
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_DEBUG_NEXT_TRIGGER_FVAL                   0x1

#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_ADDR                                           (PBS1_CORE_BASE      + 0x000000ef)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_OFFS                                           0x000000ef
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_RMSK                                                 0xff
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_ADDR, PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_RMSK, 0, val)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_ADDR, val)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_BMSK                                     0xff
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_SHFT                                      0x0
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_DEBUG_NEXT_NOP_FVAL                       0x0
#define PMIO_PBS1_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_DEBUG_NEXT_TRIGGER_FVAL                   0x1

/*----------------------------------------------------------------------------
 * PERIPHERAL: PBS2_CORE
 *--------------------------------------------------------------------------*/

#define PBS2_CORE_BASE                                                                0x00001a00

#define PMIO_PBS2_CORE_REVISION1_ADDR                                                 (PBS2_CORE_BASE      + 0x00000000)
#define PMIO_PBS2_CORE_REVISION1_OFFS                                                 0x00000000
#define PMIO_PBS2_CORE_REVISION1_RMSK                                                       0xff
#define PMIO_PBS2_CORE_REVISION1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_REVISION1_ADDR, PMIO_PBS2_CORE_REVISION1_RMSK, 0, val)
#define PMIO_PBS2_CORE_REVISION1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_REVISION1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_REVISION1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_REVISION1_ADDR, val, len)
#define PMIO_PBS2_CORE_REVISION1_DIG_MINOR_BMSK                                             0xff
#define PMIO_PBS2_CORE_REVISION1_DIG_MINOR_SHFT                                              0x0

#define PMIO_PBS2_CORE_REVISION2_ADDR                                                 (PBS2_CORE_BASE      + 0x00000001)
#define PMIO_PBS2_CORE_REVISION2_OFFS                                                 0x00000001
#define PMIO_PBS2_CORE_REVISION2_RMSK                                                       0xff
#define PMIO_PBS2_CORE_REVISION2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_REVISION2_ADDR, PMIO_PBS2_CORE_REVISION2_RMSK, 0, val)
#define PMIO_PBS2_CORE_REVISION2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_REVISION2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_REVISION2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_REVISION2_ADDR, val, len)
#define PMIO_PBS2_CORE_REVISION2_DIG_MAJOR_BMSK                                             0xff
#define PMIO_PBS2_CORE_REVISION2_DIG_MAJOR_SHFT                                              0x0

#define PMIO_PBS2_CORE_REVISION3_ADDR                                                 (PBS2_CORE_BASE      + 0x00000002)
#define PMIO_PBS2_CORE_REVISION3_OFFS                                                 0x00000002
#define PMIO_PBS2_CORE_REVISION3_RMSK                                                       0xff
#define PMIO_PBS2_CORE_REVISION3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_REVISION3_ADDR, PMIO_PBS2_CORE_REVISION3_RMSK, 0, val)
#define PMIO_PBS2_CORE_REVISION3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_REVISION3_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_REVISION3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_REVISION3_ADDR, val, len)
#define PMIO_PBS2_CORE_REVISION3_ANA_MINOR_BMSK                                             0xff
#define PMIO_PBS2_CORE_REVISION3_ANA_MINOR_SHFT                                              0x0

#define PMIO_PBS2_CORE_REVISION4_ADDR                                                 (PBS2_CORE_BASE      + 0x00000003)
#define PMIO_PBS2_CORE_REVISION4_OFFS                                                 0x00000003
#define PMIO_PBS2_CORE_REVISION4_RMSK                                                       0xff
#define PMIO_PBS2_CORE_REVISION4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_REVISION4_ADDR, PMIO_PBS2_CORE_REVISION4_RMSK, 0, val)
#define PMIO_PBS2_CORE_REVISION4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_REVISION4_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_REVISION4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_REVISION4_ADDR, val, len)
#define PMIO_PBS2_CORE_REVISION4_ANA_MAJOR_BMSK                                             0xff
#define PMIO_PBS2_CORE_REVISION4_ANA_MAJOR_SHFT                                              0x0

#define PMIO_PBS2_CORE_PERPH_TYPE_ADDR                                                (PBS2_CORE_BASE      + 0x00000004)
#define PMIO_PBS2_CORE_PERPH_TYPE_OFFS                                                0x00000004
#define PMIO_PBS2_CORE_PERPH_TYPE_RMSK                                                      0xff
#define PMIO_PBS2_CORE_PERPH_TYPE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_TYPE_ADDR, PMIO_PBS2_CORE_PERPH_TYPE_RMSK, 0, val)
#define PMIO_PBS2_CORE_PERPH_TYPE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_TYPE_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PERPH_TYPE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PERPH_TYPE_ADDR, val, len)
#define PMIO_PBS2_CORE_PERPH_TYPE_TYPE_BMSK                                                 0xff
#define PMIO_PBS2_CORE_PERPH_TYPE_TYPE_SHFT                                                  0x0
#define PMIO_PBS2_CORE_PERPH_TYPE_TYPE_PBS_FVAL                                             0x16

#define PMIO_PBS2_CORE_PERPH_SUBTYPE_ADDR                                             (PBS2_CORE_BASE      + 0x00000005)
#define PMIO_PBS2_CORE_PERPH_SUBTYPE_OFFS                                             0x00000005
#define PMIO_PBS2_CORE_PERPH_SUBTYPE_RMSK                                                   0xff
#define PMIO_PBS2_CORE_PERPH_SUBTYPE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_SUBTYPE_ADDR, PMIO_PBS2_CORE_PERPH_SUBTYPE_RMSK, 0, val)
#define PMIO_PBS2_CORE_PERPH_SUBTYPE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_SUBTYPE_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PERPH_SUBTYPE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PERPH_SUBTYPE_ADDR, val, len)
#define PMIO_PBS2_CORE_PERPH_SUBTYPE_SUBTYPE_BMSK                                           0xff
#define PMIO_PBS2_CORE_PERPH_SUBTYPE_SUBTYPE_SHFT                                            0x0
#define PMIO_PBS2_CORE_PERPH_SUBTYPE_SUBTYPE_PBS_CORE_FVAL                                   0x1

#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_ADDR                                       (PBS2_CORE_BASE      + 0x00000006)
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_OFFS                                       0x00000006
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_RMSK                                             0x1f
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_ADDR, PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_RMSK, 0, val)
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_ADDR, val, len)
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_SHARED_OTP_CONFIG_BMSK                           0x10
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_SHARED_OTP_CONFIG_SHFT                            0x4
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_RAM_CONFIG_BMSK                             0x8
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_RAM_CONFIG_SHFT                             0x3
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_OTP_CONFIG_BMSK                             0x4
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_OTP_CONFIG_SHFT                             0x2
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_RAM_CONFIG_BMSK                             0x2
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_RAM_CONFIG_SHFT                             0x1
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_OTP_CONFIG_BMSK                             0x1
#define PMIO_PBS2_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_OTP_CONFIG_SHFT                             0x0

#define PMIO_PBS2_CORE_NUM_CLIENTS_ADDR                                               (PBS2_CORE_BASE      + 0x00000007)
#define PMIO_PBS2_CORE_NUM_CLIENTS_OFFS                                               0x00000007
#define PMIO_PBS2_CORE_NUM_CLIENTS_RMSK                                                     0xff
#define PMIO_PBS2_CORE_NUM_CLIENTS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_NUM_CLIENTS_ADDR, PMIO_PBS2_CORE_NUM_CLIENTS_RMSK, 0, val)
#define PMIO_PBS2_CORE_NUM_CLIENTS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_NUM_CLIENTS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_NUM_CLIENTS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_NUM_CLIENTS_ADDR, val, len)
#define PMIO_PBS2_CORE_NUM_CLIENTS_NUM_CLIENTS_BMSK                                         0xff
#define PMIO_PBS2_CORE_NUM_CLIENTS_NUM_CLIENTS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_STATUS0_ADDR                                               (PBS2_CORE_BASE      + 0x00000008)
#define PMIO_PBS2_CORE_SEQ_STATUS0_OFFS                                               0x00000008
#define PMIO_PBS2_CORE_SEQ_STATUS0_RMSK                                                     0x3f
#define PMIO_PBS2_CORE_SEQ_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_STATUS0_ADDR, PMIO_PBS2_CORE_SEQ_STATUS0_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_STATUS0_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_BMSK                                0x30
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_SHFT                                 0x4
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_RESERVED_FVAL                        0x0
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_NORMAL_FVAL                          0x1
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_ERROR_FVAL                           0x2
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_ABORT_FVAL                           0x3
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_BMSK                                        0xf
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_SHFT                                        0x0
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_0_FVAL                               0x0
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_1_FVAL                               0x1
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_2_FVAL                               0x2
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_3_FVAL                               0x3
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_4_FVAL                               0x4
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_5_FVAL                               0x5
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_6_FVAL                               0x6
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_7_FVAL                               0x7
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_8_FVAL                               0x8
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_9_FVAL                               0x9
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_10_FVAL                              0xa
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_11_FVAL                              0xb
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_12_FVAL                              0xc
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_13_FVAL                              0xd
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_14_FVAL                              0xe
#define PMIO_PBS2_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_15_FVAL                              0xf

#define PMIO_PBS2_CORE_NUM_TRIGCL_ADDR                                                (PBS2_CORE_BASE      + 0x00000009)
#define PMIO_PBS2_CORE_NUM_TRIGCL_OFFS                                                0x00000009
#define PMIO_PBS2_CORE_NUM_TRIGCL_RMSK                                                      0xff
#define PMIO_PBS2_CORE_NUM_TRIGCL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_NUM_TRIGCL_ADDR, PMIO_PBS2_CORE_NUM_TRIGCL_RMSK, 0, val)
#define PMIO_PBS2_CORE_NUM_TRIGCL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_NUM_TRIGCL_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_NUM_TRIGCL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_NUM_TRIGCL_ADDR, val, len)
#define PMIO_PBS2_CORE_NUM_TRIGCL_NUM_TRIGCL_BMSK                                           0xff
#define PMIO_PBS2_CORE_NUM_TRIGCL_NUM_TRIGCL_SHFT                                            0x0

#define PMIO_PBS2_CORE_SEQ_PC_STATUS0_ADDR                                            (PBS2_CORE_BASE      + 0x0000000a)
#define PMIO_PBS2_CORE_SEQ_PC_STATUS0_OFFS                                            0x0000000a
#define PMIO_PBS2_CORE_SEQ_PC_STATUS0_RMSK                                                  0xff
#define PMIO_PBS2_CORE_SEQ_PC_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_PC_STATUS0_ADDR, PMIO_PBS2_CORE_SEQ_PC_STATUS0_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_PC_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_PC_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_PC_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_PC_STATUS0_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_PC_STATUS0_PC_LSB_BMSK                                           0xff
#define PMIO_PBS2_CORE_SEQ_PC_STATUS0_PC_LSB_SHFT                                            0x0

#define PMIO_PBS2_CORE_SEQ_PC_STATUS1_ADDR                                            (PBS2_CORE_BASE      + 0x0000000b)
#define PMIO_PBS2_CORE_SEQ_PC_STATUS1_OFFS                                            0x0000000b
#define PMIO_PBS2_CORE_SEQ_PC_STATUS1_RMSK                                                  0xff
#define PMIO_PBS2_CORE_SEQ_PC_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_PC_STATUS1_ADDR, PMIO_PBS2_CORE_SEQ_PC_STATUS1_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_PC_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_PC_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_PC_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_PC_STATUS1_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_PC_STATUS1_PC_MSB_BMSK                                           0xff
#define PMIO_PBS2_CORE_SEQ_PC_STATUS1_PC_MSB_SHFT                                            0x0

#define PMIO_PBS2_CORE_SEQ_IR_STATUS0_ADDR                                            (PBS2_CORE_BASE      + 0x0000000c)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS0_OFFS                                            0x0000000c
#define PMIO_PBS2_CORE_SEQ_IR_STATUS0_RMSK                                                  0xff
#define PMIO_PBS2_CORE_SEQ_IR_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS0_ADDR, PMIO_PBS2_CORE_SEQ_IR_STATUS0_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS0_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS0_IR_BYTE0_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_IR_STATUS0_IR_BYTE0_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_IR_STATUS1_ADDR                                            (PBS2_CORE_BASE      + 0x0000000d)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS1_OFFS                                            0x0000000d
#define PMIO_PBS2_CORE_SEQ_IR_STATUS1_RMSK                                                  0xff
#define PMIO_PBS2_CORE_SEQ_IR_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS1_ADDR, PMIO_PBS2_CORE_SEQ_IR_STATUS1_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS1_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS1_IR_BYTE1_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_IR_STATUS1_IR_BYTE1_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_IR_STATUS2_ADDR                                            (PBS2_CORE_BASE      + 0x0000000e)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS2_OFFS                                            0x0000000e
#define PMIO_PBS2_CORE_SEQ_IR_STATUS2_RMSK                                                  0xff
#define PMIO_PBS2_CORE_SEQ_IR_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS2_ADDR, PMIO_PBS2_CORE_SEQ_IR_STATUS2_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS2_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS2_IR_BYTE2_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_IR_STATUS2_IR_BYTE2_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_IR_STATUS3_ADDR                                            (PBS2_CORE_BASE      + 0x0000000f)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS3_OFFS                                            0x0000000f
#define PMIO_PBS2_CORE_SEQ_IR_STATUS3_RMSK                                                  0xff
#define PMIO_PBS2_CORE_SEQ_IR_STATUS3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS3_ADDR, PMIO_PBS2_CORE_SEQ_IR_STATUS3_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS3_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_IR_STATUS3_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_IR_STATUS3_IR_BYTE3_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_IR_STATUS3_IR_BYTE3_SHFT                                          0x0

#define PMIO_PBS2_CORE_PMIC_CTL_CFG_ADDR                                              (PBS2_CORE_BASE      + 0x00000030)
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_OFFS                                              0x00000030
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_RMSK                                                    0xc0
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PMIC_CTL_CFG_ADDR, PMIO_PBS2_CORE_PMIC_CTL_CFG_RMSK, 0, val)
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PMIC_CTL_CFG_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PMIC_CTL_CFG_ADDR, val, len)
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PMIC_CTL_CFG_ADDR, val)
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PMIC_CTL_CFG_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PMIC_CTL_CFG_ADDR, val, len)
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_BMSK                                      0x80
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_SHFT                                       0x7
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_DISABLED_FVAL                              0x0
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_ENABLED_FVAL                               0x1
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_BMSK                                0x40
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_SHFT                                 0x6
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_MASTER_SECONDARY_ARB_FVAL            0x0
#define PMIO_PBS2_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_MASTER_PRIORITY_ARB_FVAL             0x1

#define PMIO_PBS2_CORE_PBS_WDOG_CTL_ADDR                                              (PBS2_CORE_BASE      + 0x00000031)
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_OFFS                                              0x00000031
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_RMSK                                                    0x80
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_CTL_ADDR, PMIO_PBS2_CORE_PBS_WDOG_CTL_RMSK, 0, val)
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_CTL_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_CTL_ADDR, val, len)
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_CTL_ADDR, val)
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_CTL_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_CTL_ADDR, val, len)
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_ENABLE_BMSK                                             0x80
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_ENABLE_SHFT                                              0x7
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_ENABLE_DISABLED_FVAL                                     0x0
#define PMIO_PBS2_CORE_PBS_WDOG_CTL_ENABLE_ENABLED_FVAL                                      0x1

#define PMIO_PBS2_CORE_PBS_WDOG_PET_ADDR                                              (PBS2_CORE_BASE      + 0x00000032)
#define PMIO_PBS2_CORE_PBS_WDOG_PET_OFFS                                              0x00000032
#define PMIO_PBS2_CORE_PBS_WDOG_PET_RMSK                                                    0x80
#define PMIO_PBS2_CORE_PBS_WDOG_PET_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_PET_ADDR, val)
#define PMIO_PBS2_CORE_PBS_WDOG_PET_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_PET_ADDR, val, len)
#define PMIO_PBS2_CORE_PBS_WDOG_PET_PET_BMSK                                                0x80
#define PMIO_PBS2_CORE_PBS_WDOG_PET_PET_SHFT                                                 0x7

#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_ADDR                                          (PBS2_CORE_BASE      + 0x00000033)
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_OFFS                                          0x00000033
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_RMSK                                                 0x3
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_ADDR, PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_RMSK, 0, val)
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_ADDR, val, len)
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_ADDR, val)
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_ADDR, val, len)
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_BMSK                                0x3
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_SHFT                                0x0
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_PBS_WDOG_1_MS_FVAL                  0x0
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_PBS_WDOG_10_MS_FVAL                 0x1
#define PMIO_PBS2_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_PBS_WDOG_100_MS_FVAL                0x2

#define PMIO_PBS2_CORE_PBS_SPMI_USID_ADDR                                             (PBS2_CORE_BASE      + 0x00000038)
#define PMIO_PBS2_CORE_PBS_SPMI_USID_OFFS                                             0x00000038
#define PMIO_PBS2_CORE_PBS_SPMI_USID_RMSK                                                    0xf
#define PMIO_PBS2_CORE_PBS_SPMI_USID_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_USID_ADDR, PMIO_PBS2_CORE_PBS_SPMI_USID_RMSK, 0, val)
#define PMIO_PBS2_CORE_PBS_SPMI_USID_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_USID_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PBS_SPMI_USID_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_USID_ADDR, val, len)
#define PMIO_PBS2_CORE_PBS_SPMI_USID_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_USID_ADDR, val)
#define PMIO_PBS2_CORE_PBS_SPMI_USID_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_USID_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PBS_SPMI_USID_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_USID_ADDR, val, len)
#define PMIO_PBS2_CORE_PBS_SPMI_USID_PBS_SPMI_USID_BMSK                                      0xf
#define PMIO_PBS2_CORE_PBS_SPMI_USID_PBS_SPMI_USID_SHFT                                      0x0

#define PMIO_PBS2_CORE_PBS_SPMI_GSID_ADDR                                             (PBS2_CORE_BASE      + 0x00000039)
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_OFFS                                             0x00000039
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_RMSK                                                   0xff
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_GSID_ADDR, PMIO_PBS2_CORE_PBS_SPMI_GSID_RMSK, 0, val)
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_GSID_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_GSID_ADDR, val, len)
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_GSID_ADDR, val)
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_GSID_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PBS_SPMI_GSID_ADDR, val, len)
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID1_BMSK                                    0xf0
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID1_SHFT                                     0x4
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID0_BMSK                                     0xf
#define PMIO_PBS2_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID0_SHFT                                     0x0

#define PMIO_PBS2_CORE_MEM_INTF_CFG_ADDR                                              (PBS2_CORE_BASE      + 0x00000040)
#define PMIO_PBS2_CORE_MEM_INTF_CFG_OFFS                                              0x00000040
#define PMIO_PBS2_CORE_MEM_INTF_CFG_RMSK                                                    0x80
#define PMIO_PBS2_CORE_MEM_INTF_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CFG_ADDR, PMIO_PBS2_CORE_MEM_INTF_CFG_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CFG_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CFG_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CFG_ADDR, val)
#define PMIO_PBS2_CORE_MEM_INTF_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CFG_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CFG_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_BMSK                                  0x80
#define PMIO_PBS2_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_SHFT                                   0x7
#define PMIO_PBS2_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_DISABLED_FVAL                          0x0
#define PMIO_PBS2_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_ENABLED_FVAL                           0x1

#define PMIO_PBS2_CORE_MEM_INTF_CTL_ADDR                                              (PBS2_CORE_BASE      + 0x00000041)
#define PMIO_PBS2_CORE_MEM_INTF_CTL_OFFS                                              0x00000041
#define PMIO_PBS2_CORE_MEM_INTF_CTL_RMSK                                                    0xc0
#define PMIO_PBS2_CORE_MEM_INTF_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CTL_ADDR, PMIO_PBS2_CORE_MEM_INTF_CTL_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CTL_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CTL_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CTL_ADDR, val)
#define PMIO_PBS2_CORE_MEM_INTF_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CTL_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_CTL_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_CTL_BURST_BMSK                                              0x80
#define PMIO_PBS2_CORE_MEM_INTF_CTL_BURST_SHFT                                               0x7
#define PMIO_PBS2_CORE_MEM_INTF_CTL_BURST_SINGLE_MODE_FVAL                                   0x0
#define PMIO_PBS2_CORE_MEM_INTF_CTL_BURST_BURST_MODE_FVAL                                    0x1
#define PMIO_PBS2_CORE_MEM_INTF_CTL_WR_EN_BMSK                                              0x40
#define PMIO_PBS2_CORE_MEM_INTF_CTL_WR_EN_SHFT                                               0x6
#define PMIO_PBS2_CORE_MEM_INTF_CTL_WR_EN_READ_ACCESS_FVAL                                   0x0
#define PMIO_PBS2_CORE_MEM_INTF_CTL_WR_EN_WRITE_ACCESS_FVAL                                  0x1

#define PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_ADDR                                         (PBS2_CORE_BASE      + 0x00000042)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_OFFS                                         0x00000042
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_RMSK                                               0xff
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_ADDR, PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_ADDR, val)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_MEM_INTF_ADDR_LSB_BMSK                             0xff
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_LSB_MEM_INTF_ADDR_LSB_SHFT                              0x0

#define PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_ADDR                                         (PBS2_CORE_BASE      + 0x00000043)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_OFFS                                         0x00000043
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_RMSK                                               0xff
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_ADDR, PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_ADDR, val)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_MEM_INTF_ADDR_MSB_BMSK                             0xff
#define PMIO_PBS2_CORE_MEM_INTF_ADDR_MSB_MEM_INTF_ADDR_MSB_SHFT                              0x0

#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_ADDR                                         (PBS2_CORE_BASE      + 0x00000048)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_OFFS                                         0x00000048
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_RMSK                                               0xff
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_ADDR, PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_ADDR, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_MEM_INTF_WR_DATA_0_BMSK                            0xff
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA0_MEM_INTF_WR_DATA_0_SHFT                             0x0

#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_ADDR                                         (PBS2_CORE_BASE      + 0x00000049)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_OFFS                                         0x00000049
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_RMSK                                               0xff
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_ADDR, PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_ADDR, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_MEM_INTF_WR_DATA_1_BMSK                            0xff
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA1_MEM_INTF_WR_DATA_1_SHFT                             0x0

#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_ADDR                                         (PBS2_CORE_BASE      + 0x0000004a)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_OFFS                                         0x0000004a
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_RMSK                                               0xff
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_ADDR, PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_ADDR, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_MEM_INTF_WR_DATA_2_BMSK                            0xff
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA2_MEM_INTF_WR_DATA_2_SHFT                             0x0

#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_ADDR                                         (PBS2_CORE_BASE      + 0x0000004b)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_OFFS                                         0x0000004b
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_RMSK                                               0xff
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_ADDR, PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_ADDR, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_MEM_INTF_WR_DATA_3_BMSK                            0xff
#define PMIO_PBS2_CORE_MEM_INTF_WR_DATA3_MEM_INTF_WR_DATA_3_SHFT                             0x0

#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_ADDR                                         (PBS2_CORE_BASE      + 0x0000004c)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_OFFS                                         0x0000004c
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_RMSK                                               0xff
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_ADDR, PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_MEM_INTF_RD_DATA_0_BMSK                            0xff
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA0_MEM_INTF_RD_DATA_0_SHFT                             0x0

#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_ADDR                                         (PBS2_CORE_BASE      + 0x0000004d)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_OFFS                                         0x0000004d
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_RMSK                                               0xff
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_ADDR, PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_MEM_INTF_RD_DATA_1_BMSK                            0xff
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA1_MEM_INTF_RD_DATA_1_SHFT                             0x0

#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_ADDR                                         (PBS2_CORE_BASE      + 0x0000004e)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_OFFS                                         0x0000004e
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_RMSK                                               0xff
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_ADDR, PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_MEM_INTF_RD_DATA_2_BMSK                            0xff
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA2_MEM_INTF_RD_DATA_2_SHFT                             0x0

#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_ADDR                                         (PBS2_CORE_BASE      + 0x0000004f)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_OFFS                                         0x0000004f
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_RMSK                                               0xff
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_ADDR, PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_RMSK, 0, val)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_ADDR, val, len)
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_MEM_INTF_RD_DATA_3_BMSK                            0xff
#define PMIO_PBS2_CORE_MEM_INTF_RD_DATA3_MEM_INTF_RD_DATA_3_SHFT                             0x0

#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_ADDR                                     (PBS2_CORE_BASE      + 0x00000050)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_OFFS                                     0x00000050
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_RMSK                                           0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_ADDR, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_RMSK, 0, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_ADDR, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_SEQ_ADDR_LSB_BMSK                              0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_0_SEQ_ADDR_LSB_SHFT                               0x0

#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_ADDR                                     (PBS2_CORE_BASE      + 0x00000054)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_OFFS                                     0x00000054
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_RMSK                                           0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_ADDR, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_RMSK, 0, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_ADDR, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_SEQ_ADDR_LSB_BMSK                              0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_1_SEQ_ADDR_LSB_SHFT                               0x0

#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_ADDR                                     (PBS2_CORE_BASE      + 0x00000058)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_OFFS                                     0x00000058
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_RMSK                                           0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_ADDR, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_RMSK, 0, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_ADDR, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_SEQ_ADDR_LSB_BMSK                              0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_LSB_2_SEQ_ADDR_LSB_SHFT                               0x0

#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_ADDR                                     (PBS2_CORE_BASE      + 0x00000051)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_OFFS                                     0x00000051
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_RMSK                                           0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_ADDR, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_RMSK, 0, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_ADDR, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_SEQ_ADDR_MSB_BMSK                              0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_0_SEQ_ADDR_MSB_SHFT                               0x0

#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_ADDR                                     (PBS2_CORE_BASE      + 0x00000055)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_OFFS                                     0x00000055
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_RMSK                                           0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_ADDR, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_RMSK, 0, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_ADDR, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_SEQ_ADDR_MSB_BMSK                              0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_1_SEQ_ADDR_MSB_SHFT                               0x0

#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_ADDR                                     (PBS2_CORE_BASE      + 0x00000059)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_OFFS                                     0x00000059
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_RMSK                                           0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_ADDR, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_RMSK, 0, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_ADDR, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_SEQ_ADDR_MSB_BMSK                              0xff
#define PMIO_PBS2_CORE_TRIG_START_ADDR_MSB_2_SEQ_ADDR_MSB_SHFT                               0x0

#define PMIO_PBS2_CORE_SEQ_STATUS1_ADDR                                               (PBS2_CORE_BASE      + 0x00000090)
#define PMIO_PBS2_CORE_SEQ_STATUS1_OFFS                                               0x00000090
#define PMIO_PBS2_CORE_SEQ_STATUS1_RMSK                                                     0xff
#define PMIO_PBS2_CORE_SEQ_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_STATUS1_ADDR, PMIO_PBS2_CORE_SEQ_STATUS1_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_STATUS1_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_BMSK                                      0xf0
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_SHFT                                       0x4
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_0_FVAL                              0x0
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_1_FVAL                              0x1
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_2_FVAL                              0x2
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_3_FVAL                              0x3
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_4_FVAL                              0x4
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_5_FVAL                              0x5
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_6_FVAL                              0x6
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_7_FVAL                              0x7
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_8_FVAL                              0x8
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_9_FVAL                              0x9
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_10_FVAL                             0xa
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_11_FVAL                             0xb
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_12_FVAL                             0xc
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_13_FVAL                             0xd
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_14_FVAL                             0xe
#define PMIO_PBS2_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_15_FVAL                             0xf
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_BMSK                                      0xf
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_SHFT                                      0x0
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_0_FVAL                             0x0
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_1_FVAL                             0x1
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_2_FVAL                             0x2
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_3_FVAL                             0x3
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_4_FVAL                             0x4
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_5_FVAL                             0x5
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_6_FVAL                             0x6
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_7_FVAL                             0x7
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_8_FVAL                             0x8
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_9_FVAL                             0x9
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_10_FVAL                            0xa
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_11_FVAL                            0xb
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_12_FVAL                            0xc
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_13_FVAL                            0xd
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_14_FVAL                            0xe
#define PMIO_PBS2_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_15_FVAL                            0xf

#define PMIO_PBS2_CORE_SEQ_STATUS2_ADDR                                               (PBS2_CORE_BASE      + 0x00000091)
#define PMIO_PBS2_CORE_SEQ_STATUS2_OFFS                                               0x00000091
#define PMIO_PBS2_CORE_SEQ_STATUS2_RMSK                                                     0xff
#define PMIO_PBS2_CORE_SEQ_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_STATUS2_ADDR, PMIO_PBS2_CORE_SEQ_STATUS2_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_STATUS2_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_BMSK                                    0xf0
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_SHFT                                     0x4
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_0_FVAL                            0x0
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_1_FVAL                            0x1
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_2_FVAL                            0x2
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_3_FVAL                            0x3
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_4_FVAL                            0x4
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_5_FVAL                            0x5
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_6_FVAL                            0x6
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_7_FVAL                            0x7
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_8_FVAL                            0x8
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_9_FVAL                            0x9
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_10_FVAL                           0xa
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_11_FVAL                           0xb
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_12_FVAL                           0xc
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_13_FVAL                           0xd
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_14_FVAL                           0xe
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_15_FVAL                           0xf
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_BMSK                                       0xf
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_SHFT                                       0x0
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_0_FVAL                              0x0
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_1_FVAL                              0x1
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_2_FVAL                              0x2
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_3_FVAL                              0x3
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_4_FVAL                              0x4
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_5_FVAL                              0x5
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_6_FVAL                              0x6
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_7_FVAL                              0x7
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_8_FVAL                              0x8
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_9_FVAL                              0x9
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_10_FVAL                             0xa
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_11_FVAL                             0xb
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_12_FVAL                             0xc
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_13_FVAL                             0xd
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_14_FVAL                             0xe
#define PMIO_PBS2_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_15_FVAL                             0xf

#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_ADDR                                        (PBS2_CORE_BASE      + 0x00000092)
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_OFFS                                        0x00000092
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_RMSK                                              0xff
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_ADDR, PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_ERR_PC_LSB_BMSK                                   0xff
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS0_ERR_PC_LSB_SHFT                                    0x0

#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_ADDR                                        (PBS2_CORE_BASE      + 0x00000093)
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_OFFS                                        0x00000093
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_RMSK                                              0xff
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_ADDR, PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_ERR_PC_MSB_BMSK                                   0xff
#define PMIO_PBS2_CORE_SEQ_ERR_PC_STATUS1_ERR_PC_MSB_SHFT                                    0x0

#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_ADDR                                        (PBS2_CORE_BASE      + 0x00000094)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_OFFS                                        0x00000094
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_RMSK                                              0xff
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_ADDR, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_ERR_IR_BYTE0_BMSK                                 0xff
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS0_ERR_IR_BYTE0_SHFT                                  0x0

#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_ADDR                                        (PBS2_CORE_BASE      + 0x00000095)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_OFFS                                        0x00000095
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_RMSK                                              0xff
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_ADDR, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_ERR_IR_BYTE1_BMSK                                 0xff
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS1_ERR_IR_BYTE1_SHFT                                  0x0

#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_ADDR                                        (PBS2_CORE_BASE      + 0x00000096)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_OFFS                                        0x00000096
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_RMSK                                              0xff
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_ADDR, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_ERR_IR_BYTE2_BMSK                                 0xff
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS2_ERR_IR_BYTE2_SHFT                                  0x0

#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_ADDR                                        (PBS2_CORE_BASE      + 0x00000097)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_OFFS                                        0x00000097
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_RMSK                                              0xff
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_ADDR, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_ERR_IR_BYTE3_BMSK                                 0xff
#define PMIO_PBS2_CORE_SEQ_ERR_IR_STATUS3_ERR_IR_BYTE3_SHFT                                  0x0

#define PMIO_PBS2_CORE_TRIG_STATUS0_ADDR                                              (PBS2_CORE_BASE      + 0x00000098)
#define PMIO_PBS2_CORE_TRIG_STATUS0_OFFS                                              0x00000098
#define PMIO_PBS2_CORE_TRIG_STATUS0_RMSK                                                    0x7f
#define PMIO_PBS2_CORE_TRIG_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS0_ADDR, PMIO_PBS2_CORE_TRIG_STATUS0_RMSK, 0, val)
#define PMIO_PBS2_CORE_TRIG_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS0_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_STATUS0_LAST_TRIG_COMP_BMSK                                     0x7f
#define PMIO_PBS2_CORE_TRIG_STATUS0_LAST_TRIG_COMP_SHFT                                      0x0

#define PMIO_PBS2_CORE_TRIG_STATUS1_ADDR                                              (PBS2_CORE_BASE      + 0x00000099)
#define PMIO_PBS2_CORE_TRIG_STATUS1_OFFS                                              0x00000099
#define PMIO_PBS2_CORE_TRIG_STATUS1_RMSK                                                    0x7f
#define PMIO_PBS2_CORE_TRIG_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS1_ADDR, PMIO_PBS2_CORE_TRIG_STATUS1_RMSK, 0, val)
#define PMIO_PBS2_CORE_TRIG_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS1_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_STATUS1_LAST_TRIG_NORMAL_BMSK                                   0x7f
#define PMIO_PBS2_CORE_TRIG_STATUS1_LAST_TRIG_NORMAL_SHFT                                    0x0

#define PMIO_PBS2_CORE_TRIG_STATUS2_ADDR                                              (PBS2_CORE_BASE      + 0x0000009a)
#define PMIO_PBS2_CORE_TRIG_STATUS2_OFFS                                              0x0000009a
#define PMIO_PBS2_CORE_TRIG_STATUS2_RMSK                                                    0x7f
#define PMIO_PBS2_CORE_TRIG_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS2_ADDR, PMIO_PBS2_CORE_TRIG_STATUS2_RMSK, 0, val)
#define PMIO_PBS2_CORE_TRIG_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS2_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_STATUS2_TRIG_IN_SERVICE_BMSK                                    0x7f
#define PMIO_PBS2_CORE_TRIG_STATUS2_TRIG_IN_SERVICE_SHFT                                     0x0

#define PMIO_PBS2_CORE_TRIG_STATUS3_ADDR                                              (PBS2_CORE_BASE      + 0x0000009b)
#define PMIO_PBS2_CORE_TRIG_STATUS3_OFFS                                              0x0000009b
#define PMIO_PBS2_CORE_TRIG_STATUS3_RMSK                                                    0x7f
#define PMIO_PBS2_CORE_TRIG_STATUS3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS3_ADDR, PMIO_PBS2_CORE_TRIG_STATUS3_RMSK, 0, val)
#define PMIO_PBS2_CORE_TRIG_STATUS3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS3_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_STATUS3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS3_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_STATUS3_LAST_TRIG_ERROR_BMSK                                    0x7f
#define PMIO_PBS2_CORE_TRIG_STATUS3_LAST_TRIG_ERROR_SHFT                                     0x0

#define PMIO_PBS2_CORE_TRIG_STATUS4_ADDR                                              (PBS2_CORE_BASE      + 0x0000009c)
#define PMIO_PBS2_CORE_TRIG_STATUS4_OFFS                                              0x0000009c
#define PMIO_PBS2_CORE_TRIG_STATUS4_RMSK                                                    0x7f
#define PMIO_PBS2_CORE_TRIG_STATUS4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS4_ADDR, PMIO_PBS2_CORE_TRIG_STATUS4_RMSK, 0, val)
#define PMIO_PBS2_CORE_TRIG_STATUS4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS4_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TRIG_STATUS4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TRIG_STATUS4_ADDR, val, len)
#define PMIO_PBS2_CORE_TRIG_STATUS4_LAST_TRIG_ABORTED_BMSK                                  0x7f
#define PMIO_PBS2_CORE_TRIG_STATUS4_LAST_TRIG_ABORTED_SHFT                                   0x0

#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_ADDR                                       (PBS2_CORE_BASE      + 0x0000009f)
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_OFFS                                       0x0000009f
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_RMSK                                             0xff
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_EOS_NOT_EMPTY_ERROR_BMSK                0x80
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_EOS_NOT_EMPTY_ERROR_SHFT                 0x7
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_OVERFLOW_ERROR_BMSK                     0x40
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_OVERFLOW_ERROR_SHFT                      0x6
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_UNDERFLOW_ERROR_BMSK                    0x20
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_UNDERFLOW_ERROR_SHFT                     0x5
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_SPMI_ERROR_BMSK                                  0x10
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_SPMI_ERROR_SHFT                                   0x4
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_LSID_ERROR_BMSK                                   0x8
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_LSID_ERROR_SHFT                                   0x3
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_SPECIAL_USID_ERROR_BMSK                           0x4
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_SPECIAL_USID_ERROR_SHFT                           0x2
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_USID_ERROR_BMSK                                   0x2
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_USID_ERROR_SHFT                                   0x1
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_INVALID_CMD_ERROR_BMSK                            0x1
#define PMIO_PBS2_CORE_SEQ_ERR_TYPE_STATUS_INVALID_CMD_ERROR_SHFT                            0x0

#define PMIO_PBS2_CORE_RAM_CFG1_ADDR                                                  (PBS2_CORE_BASE      + 0x000000a0)
#define PMIO_PBS2_CORE_RAM_CFG1_OFFS                                                  0x000000a0
#define PMIO_PBS2_CORE_RAM_CFG1_RMSK                                                        0xff
#define PMIO_PBS2_CORE_RAM_CFG1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_RAM_CFG1_ADDR, PMIO_PBS2_CORE_RAM_CFG1_RMSK, 0, val)
#define PMIO_PBS2_CORE_RAM_CFG1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_RAM_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_RAM_CFG1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_RAM_CFG1_ADDR, val, len)
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_BMSK                                                   0xff
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_SHFT                                                    0x0
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_NO_RAM_FVAL                                             0x0
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_SIZE_32X32_FVAL                                         0x1
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_SIZE_64X32_FVAL                                         0x2
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_SIZE_96X32_FVAL                                         0x3
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_SIZE_128X32_FVAL                                        0x4
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_SIZE_160X32_FVAL                                        0x5
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_SIZE_192X32_FVAL                                        0x6
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_SIZE_224X32_FVAL                                        0x7
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_SIZE_256X32_FVAL                                        0x8
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_SIZE_512X32_FVAL                                       0x10
#define PMIO_PBS2_CORE_RAM_CFG1_SIZE_SIZE_1024X32_FVAL                                      0x20

#define PMIO_PBS2_CORE_RAM_CFG2_ADDR                                                  (PBS2_CORE_BASE      + 0x000000a1)
#define PMIO_PBS2_CORE_RAM_CFG2_OFFS                                                  0x000000a1
#define PMIO_PBS2_CORE_RAM_CFG2_RMSK                                                        0xe0
#define PMIO_PBS2_CORE_RAM_CFG2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_RAM_CFG2_ADDR, PMIO_PBS2_CORE_RAM_CFG2_RMSK, 0, val)
#define PMIO_PBS2_CORE_RAM_CFG2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_RAM_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_RAM_CFG2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_RAM_CFG2_ADDR, val, len)
#define PMIO_PBS2_CORE_RAM_CFG2_MTYPE_BMSK                                                  0xe0
#define PMIO_PBS2_CORE_RAM_CFG2_MTYPE_SHFT                                                   0x5
#define PMIO_PBS2_CORE_RAM_CFG2_MTYPE_RAM18U_FVAL                                            0x0
#define PMIO_PBS2_CORE_RAM_CFG2_MTYPE_RAM65N_FVAL                                            0x1
#define PMIO_PBS2_CORE_RAM_CFG2_MTYPE_RAM15U_FVAL                                            0x2
#define PMIO_PBS2_CORE_RAM_CFG2_MTYPE_RAM22NM_FVAL                                           0x3
#define PMIO_PBS2_CORE_RAM_CFG2_MTYPE_RAM28NM_FVAL                                           0x4

#define PMIO_PBS2_CORE_NVM_CFG1_ADDR                                                  (PBS2_CORE_BASE      + 0x000000a2)
#define PMIO_PBS2_CORE_NVM_CFG1_OFFS                                                  0x000000a2
#define PMIO_PBS2_CORE_NVM_CFG1_RMSK                                                        0xff
#define PMIO_PBS2_CORE_NVM_CFG1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_NVM_CFG1_ADDR, PMIO_PBS2_CORE_NVM_CFG1_RMSK, 0, val)
#define PMIO_PBS2_CORE_NVM_CFG1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_NVM_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_NVM_CFG1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_NVM_CFG1_ADDR, val, len)
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_BMSK                                                   0xff
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_SHFT                                                    0x0
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_NO_OTP_FVAL                                             0x0
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_32_FVAL                                       0x1
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_64_FVAL                                       0x2
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_96_FVAL                                       0x3
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_128_FVAL                                      0x4
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_160_FVAL                                      0x5
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_192_FVAL                                      0x6
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_224_FVAL                                      0x7
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_256_FVAL                                      0x8
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_288_FVAL                                      0x9
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_320_FVAL                                      0xa
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_352_FVAL                                      0xb
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_384_FVAL                                      0xc
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_416_FVAL                                      0xd
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_448_FVAL                                      0xe
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_480_FVAL                                      0xf
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_512_FVAL                                     0x10
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_544_FVAL                                     0x11
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_576_FVAL                                     0x12
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_608_FVAL                                     0x13
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_640_FVAL                                     0x14
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_672_FVAL                                     0x15
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_704_FVAL                                     0x16
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_736_FVAL                                     0x17
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_768_FVAL                                     0x18
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_800_FVAL                                     0x19
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_832_FVAL                                     0x1a
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_864_FVAL                                     0x1b
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_896_FVAL                                     0x1c
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_928_FVAL                                     0x1d
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_960_FVAL                                     0x1e
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_992_FVAL                                     0x1f
#define PMIO_PBS2_CORE_NVM_CFG1_SIZE_ADDRESSES_1024_FVAL                                    0x20

#define PMIO_PBS2_CORE_NVM_CFG2_ADDR                                                  (PBS2_CORE_BASE      + 0x000000a3)
#define PMIO_PBS2_CORE_NVM_CFG2_OFFS                                                  0x000000a3
#define PMIO_PBS2_CORE_NVM_CFG2_RMSK                                                        0xf3
#define PMIO_PBS2_CORE_NVM_CFG2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_NVM_CFG2_ADDR, PMIO_PBS2_CORE_NVM_CFG2_RMSK, 0, val)
#define PMIO_PBS2_CORE_NVM_CFG2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_NVM_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_NVM_CFG2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_NVM_CFG2_ADDR, val, len)
#define PMIO_PBS2_CORE_NVM_CFG2_MTYPE_BMSK                                                  0xe0
#define PMIO_PBS2_CORE_NVM_CFG2_MTYPE_SHFT                                                   0x5
#define PMIO_PBS2_CORE_NVM_CFG2_MTYPE_EMEMORY_FVAL                                           0x0
#define PMIO_PBS2_CORE_NVM_CFG2_MTYPE_KILOPASS_FVAL                                          0x1
#define PMIO_PBS2_CORE_NVM_CFG2_MTYPE_EMEMORY15UM_FVAL                                       0x2
#define PMIO_PBS2_CORE_NVM_CFG2_MTYPE_KILOPASS22NM_FVAL                                      0x3
#define PMIO_PBS2_CORE_NVM_CFG2_MTYPE_EMEMORY28NM_FVAL                                       0x4
#define PMIO_PBS2_CORE_NVM_CFG2_TYPE_BMSK                                                   0x10
#define PMIO_PBS2_CORE_NVM_CFG2_TYPE_SHFT                                                    0x4
#define PMIO_PBS2_CORE_NVM_CFG2_TYPE_OTP_FVAL                                                0x0
#define PMIO_PBS2_CORE_NVM_CFG2_TYPE_ROM_FVAL                                                0x1
#define PMIO_PBS2_CORE_NVM_CFG2_ACCESS_BMSK                                                  0x3
#define PMIO_PBS2_CORE_NVM_CFG2_ACCESS_SHFT                                                  0x0
#define PMIO_PBS2_CORE_NVM_CFG2_ACCESS_WRITE_1200US_READ_800NS_INSTR_PR_1510NS_FVAL          0x0
#define PMIO_PBS2_CORE_NVM_CFG2_ACCESS_WRITE_600US_READ_400NS_INSTR_PR_940NS_FVAL            0x1
#define PMIO_PBS2_CORE_NVM_CFG2_ACCESS_WRITE_300US_READ_200NS_INSTR_PR_730NS_FVAL            0x2

#define PMIO_PBS2_CORE_PARAM_SETTINGS_ADDR                                            (PBS2_CORE_BASE      + 0x000000a4)
#define PMIO_PBS2_CORE_PARAM_SETTINGS_OFFS                                            0x000000a4
#define PMIO_PBS2_CORE_PARAM_SETTINGS_RMSK                                                  0x8f
#define PMIO_PBS2_CORE_PARAM_SETTINGS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PARAM_SETTINGS_ADDR, PMIO_PBS2_CORE_PARAM_SETTINGS_RMSK, 0, val)
#define PMIO_PBS2_CORE_PARAM_SETTINGS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PARAM_SETTINGS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PARAM_SETTINGS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PARAM_SETTINGS_ADDR, val, len)
#define PMIO_PBS2_CORE_PARAM_SETTINGS_FAST_PBS_BMSK                                         0x80
#define PMIO_PBS2_CORE_PARAM_SETTINGS_FAST_PBS_SHFT                                          0x7
#define PMIO_PBS2_CORE_PARAM_SETTINGS_FAST_PBS_REGULAR_PBS_FVAL                              0x0
#define PMIO_PBS2_CORE_PARAM_SETTINGS_FAST_PBS_FAST_PBS_ON_FVAL                              0x1
#define PMIO_PBS2_CORE_PARAM_SETTINGS_NUM_MACHINE_REGS_BMSK                                  0xf
#define PMIO_PBS2_CORE_PARAM_SETTINGS_NUM_MACHINE_REGS_SHFT                                  0x0

#define PMIO_PBS2_CORE_RAM_CFG3_ADDR                                                  (PBS2_CORE_BASE      + 0x000000a6)
#define PMIO_PBS2_CORE_RAM_CFG3_OFFS                                                  0x000000a6
#define PMIO_PBS2_CORE_RAM_CFG3_RMSK                                                        0xff
#define PMIO_PBS2_CORE_RAM_CFG3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_RAM_CFG3_ADDR, PMIO_PBS2_CORE_RAM_CFG3_RMSK, 0, val)
#define PMIO_PBS2_CORE_RAM_CFG3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_RAM_CFG3_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_RAM_CFG3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_RAM_CFG3_ADDR, val, len)
#define PMIO_PBS2_CORE_RAM_CFG3_SIZE_MSB_BMSK                                               0xff
#define PMIO_PBS2_CORE_RAM_CFG3_SIZE_MSB_SHFT                                                0x0

#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_ADDR                                       (PBS2_CORE_BASE      + 0x000000aa)
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_OFFS                                       0x000000aa
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_RMSK                                             0xff
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_RMSK, 0, val)
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, val, len)
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, val)
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, val, len)
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_BMSK                                0x80
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_SHFT                                 0x7
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_SLEEP_FVAL                           0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_ACTIVE_FVAL                          0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_BMSK                                0x40
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_SHFT                                 0x6
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_SLEEP_FVAL                           0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_ACTIVE_FVAL                          0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_BMSK                                0x20
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_SHFT                                 0x5
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_SLEEP_FVAL                           0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_ACTIVE_FVAL                          0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_BMSK                                0x10
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_SHFT                                 0x4
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_SLEEP_FVAL                           0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_ACTIVE_FVAL                          0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_BMSK                                  0x8
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_SHFT                                  0x3
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_SLEEP_FVAL                            0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_ACTIVE_FVAL                           0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_BMSK                                  0x4
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_SHFT                                  0x2
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_SLEEP_FVAL                            0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_ACTIVE_FVAL                           0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_BMSK                                  0x2
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_SHFT                                  0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_SLEEP_FVAL                            0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_ACTIVE_FVAL                           0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_BMSK                                  0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_SHFT                                  0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_SLEEP_FVAL                            0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_ACTIVE_FVAL                           0x1

#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR                                    (PBS2_CORE_BASE      + 0x000000ab)
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_OFFS                                    0x000000ab
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_RMSK                                          0xff
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR, PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_BMSK                        0x80
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_SHFT                         0x7
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_SLEEP_FVAL                   0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_ACTIVE_FVAL                  0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_BMSK                        0x40
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_SHFT                         0x6
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_SLEEP_FVAL                   0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_ACTIVE_FVAL                  0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_BMSK                        0x20
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_SHFT                         0x5
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_SLEEP_FVAL                   0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_ACTIVE_FVAL                  0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_BMSK                        0x10
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_SHFT                         0x4
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_SLEEP_FVAL                   0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_ACTIVE_FVAL                  0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_BMSK                          0x8
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_SHFT                          0x3
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_SLEEP_FVAL                    0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_ACTIVE_FVAL                   0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_BMSK                          0x4
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_SHFT                          0x2
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_SLEEP_FVAL                    0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_ACTIVE_FVAL                   0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_BMSK                          0x2
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_SHFT                          0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_SLEEP_FVAL                    0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_ACTIVE_FVAL                   0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_BMSK                          0x1
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_SHFT                          0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_SLEEP_FVAL                    0x0
#define PMIO_PBS2_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_ACTIVE_FVAL                   0x1

#define PMIO_PBS2_CORE_PMIC7_RAM_ACC_ADDR                                             (PBS2_CORE_BASE      + 0x000000ac)
#define PMIO_PBS2_CORE_PMIC7_RAM_ACC_OFFS                                             0x000000ac
#define PMIO_PBS2_CORE_PMIC7_RAM_ACC_RMSK                                                    0xf
#define PMIO_PBS2_CORE_PMIC7_RAM_ACC_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_ACC_ADDR, PMIO_PBS2_CORE_PMIC7_RAM_ACC_RMSK, 0, val)
#define PMIO_PBS2_CORE_PMIC7_RAM_ACC_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_ACC_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PMIC7_RAM_ACC_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_ACC_ADDR, val, len)
#define PMIO_PBS2_CORE_PMIC7_RAM_ACC_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_ACC_ADDR, val)
#define PMIO_PBS2_CORE_PMIC7_RAM_ACC_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_ACC_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PMIC7_RAM_ACC_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PMIC7_RAM_ACC_ADDR, val, len)
#define PMIO_PBS2_CORE_PMIC7_RAM_ACC_ACC_BMSK                                                0xf
#define PMIO_PBS2_CORE_PMIC7_RAM_ACC_ACC_SHFT                                                0x0

#define PMIO_PBS2_CORE_PBS_CLK_CTL_n_ADDR(n)                                          (PBS2_CORE_BASE      + (0x000000ad + 0x1 * (n)))
#define PMIO_PBS2_CORE_PBS_CLK_CTL_n_OFFS(n)                                          (0x000000ad + 0x1 * (n))
#define PMIO_PBS2_CORE_PBS_CLK_CTL_n_RMSK                                                    0x1
#define PMIO_PBS2_CORE_PBS_CLK_CTL_n_INI(ctxt, pmic, n, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_CLK_CTL_n_ADDR(n), PMIO_PBS2_CORE_PBS_CLK_CTL_n_RMSK, 0, val)
#define PMIO_PBS2_CORE_PBS_CLK_CTL_n_INFI(ctxt, pmic, n, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_CLK_CTL_n_ADDR(n), mask, shift, val)
#define PMIO_PBS2_CORE_PBS_CLK_CTL_n_INNI(ctxt, pmic, n, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PBS_CLK_CTL_n_ADDR(n), val, len)
#define PMIO_PBS2_CORE_PBS_CLK_CTL_n_OUTI(ctxt, pmic, n, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PBS_CLK_CTL_n_ADDR(n), val)
#define PMIO_PBS2_CORE_PBS_CLK_CTL_n_OUTFI(ctxt, pmic, n, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PBS_CLK_CTL_n_ADDR(n), mask, shift, val)
#define PMIO_PBS2_CORE_PBS_CLK_CTL_n_OUTNI(ctxt, pmic, n, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PBS_CLK_CTL_n_ADDR(n), val, len)
#define PMIO_PBS2_CORE_PBS_CLK_CTL_n_PBS_CLK_GATE_EN_BMSK                                    0x1
#define PMIO_PBS2_CORE_PBS_CLK_CTL_n_PBS_CLK_GATE_EN_SHFT                                    0x0

#define PMIO_PBS2_CORE_SEQ_R0_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000b0)
#define PMIO_PBS2_CORE_SEQ_R0_STATUS_OFFS                                             0x000000b0
#define PMIO_PBS2_CORE_SEQ_R0_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_R0_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R0_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_R0_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_R0_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R0_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_R0_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R0_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_R0_STATUS_R0_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_R0_STATUS_R0_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_R1_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000b1)
#define PMIO_PBS2_CORE_SEQ_R1_STATUS_OFFS                                             0x000000b1
#define PMIO_PBS2_CORE_SEQ_R1_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_R1_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R1_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_R1_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_R1_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R1_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_R1_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R1_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_R1_STATUS_R1_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_R1_STATUS_R1_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_R2_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000b2)
#define PMIO_PBS2_CORE_SEQ_R2_STATUS_OFFS                                             0x000000b2
#define PMIO_PBS2_CORE_SEQ_R2_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_R2_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R2_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_R2_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_R2_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R2_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_R2_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R2_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_R2_STATUS_R2_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_R2_STATUS_R2_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_R3_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000b3)
#define PMIO_PBS2_CORE_SEQ_R3_STATUS_OFFS                                             0x000000b3
#define PMIO_PBS2_CORE_SEQ_R3_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_R3_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R3_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_R3_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_R3_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R3_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_R3_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R3_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_R3_STATUS_R3_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_R3_STATUS_R3_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_R4_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000b4)
#define PMIO_PBS2_CORE_SEQ_R4_STATUS_OFFS                                             0x000000b4
#define PMIO_PBS2_CORE_SEQ_R4_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_R4_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R4_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_R4_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_R4_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R4_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_R4_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R4_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_R4_STATUS_R4_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_R4_STATUS_R4_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_R5_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000b5)
#define PMIO_PBS2_CORE_SEQ_R5_STATUS_OFFS                                             0x000000b5
#define PMIO_PBS2_CORE_SEQ_R5_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_R5_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R5_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_R5_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_R5_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R5_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_R5_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R5_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_R5_STATUS_R5_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_R5_STATUS_R5_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_R6_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000b6)
#define PMIO_PBS2_CORE_SEQ_R6_STATUS_OFFS                                             0x000000b6
#define PMIO_PBS2_CORE_SEQ_R6_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_R6_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R6_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_R6_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_R6_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R6_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_R6_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R6_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_R6_STATUS_R6_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_R6_STATUS_R6_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_R7_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000b7)
#define PMIO_PBS2_CORE_SEQ_R7_STATUS_OFFS                                             0x000000b7
#define PMIO_PBS2_CORE_SEQ_R7_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_R7_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R7_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_R7_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_R7_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R7_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_R7_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R7_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_R7_STATUS_R7_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_R7_STATUS_R7_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_R8_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000b8)
#define PMIO_PBS2_CORE_SEQ_R8_STATUS_OFFS                                             0x000000b8
#define PMIO_PBS2_CORE_SEQ_R8_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_R8_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R8_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_R8_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_R8_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R8_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_R8_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R8_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_R8_STATUS_R8_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_R8_STATUS_R8_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_R9_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000b9)
#define PMIO_PBS2_CORE_SEQ_R9_STATUS_OFFS                                             0x000000b9
#define PMIO_PBS2_CORE_SEQ_R9_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_R9_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R9_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_R9_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_R9_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R9_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_R9_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_R9_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_R9_STATUS_R9_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_R9_STATUS_R9_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_RA_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000ba)
#define PMIO_PBS2_CORE_SEQ_RA_STATUS_OFFS                                             0x000000ba
#define PMIO_PBS2_CORE_SEQ_RA_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_RA_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RA_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_RA_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_RA_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RA_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_RA_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RA_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_RA_STATUS_RA_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_RA_STATUS_RA_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_RB_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000bb)
#define PMIO_PBS2_CORE_SEQ_RB_STATUS_OFFS                                             0x000000bb
#define PMIO_PBS2_CORE_SEQ_RB_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_RB_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RB_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_RB_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_RB_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RB_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_RB_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RB_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_RB_STATUS_RB_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_RB_STATUS_RB_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_RC_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000bc)
#define PMIO_PBS2_CORE_SEQ_RC_STATUS_OFFS                                             0x000000bc
#define PMIO_PBS2_CORE_SEQ_RC_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_RC_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RC_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_RC_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_RC_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RC_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_RC_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RC_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_RC_STATUS_RC_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_RC_STATUS_RC_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_RD_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000bd)
#define PMIO_PBS2_CORE_SEQ_RD_STATUS_OFFS                                             0x000000bd
#define PMIO_PBS2_CORE_SEQ_RD_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_RD_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RD_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_RD_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_RD_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RD_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_RD_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RD_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_RD_STATUS_RD_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_RD_STATUS_RD_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_RE_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000be)
#define PMIO_PBS2_CORE_SEQ_RE_STATUS_OFFS                                             0x000000be
#define PMIO_PBS2_CORE_SEQ_RE_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_RE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RE_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_RE_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_RE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_RE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RE_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_RE_STATUS_RE_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_RE_STATUS_RE_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_SEQ_RF_STATUS_ADDR                                             (PBS2_CORE_BASE      + 0x000000bf)
#define PMIO_PBS2_CORE_SEQ_RF_STATUS_OFFS                                             0x000000bf
#define PMIO_PBS2_CORE_SEQ_RF_STATUS_RMSK                                                   0xff
#define PMIO_PBS2_CORE_SEQ_RF_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RF_STATUS_ADDR, PMIO_PBS2_CORE_SEQ_RF_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_RF_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RF_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_RF_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_RF_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_RF_STATUS_RF_STATUS_BMSK                                         0xff
#define PMIO_PBS2_CORE_SEQ_RF_STATUS_RF_STATUS_SHFT                                          0x0

#define PMIO_PBS2_CORE_LOCKBIT_D1_ADDR                                                (PBS2_CORE_BASE      + 0x000000d1)
#define PMIO_PBS2_CORE_LOCKBIT_D1_OFFS                                                0x000000d1
#define PMIO_PBS2_CORE_LOCKBIT_D1_RMSK                                                       0x3
#define PMIO_PBS2_CORE_LOCKBIT_D1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_LOCKBIT_D1_ADDR, PMIO_PBS2_CORE_LOCKBIT_D1_RMSK, 0, val)
#define PMIO_PBS2_CORE_LOCKBIT_D1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_LOCKBIT_D1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_LOCKBIT_D1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_LOCKBIT_D1_ADDR, val, len)
#define PMIO_PBS2_CORE_LOCKBIT_D1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_LOCKBIT_D1_ADDR, val)
#define PMIO_PBS2_CORE_LOCKBIT_D1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_LOCKBIT_D1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_LOCKBIT_D1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_LOCKBIT_D1_ADDR, val, len)
#define PMIO_PBS2_CORE_LOCKBIT_D1_LOCKBIT_D1_BMSK                                            0x3
#define PMIO_PBS2_CORE_LOCKBIT_D1_LOCKBIT_D1_SHFT                                            0x0
#define PMIO_PBS2_CORE_LOCKBIT_D1_LOCKBIT_D1_OPEN_FVAL                                       0x0
#define PMIO_PBS2_CORE_LOCKBIT_D1_LOCKBIT_D1_RSVD_FVAL                                       0x1
#define PMIO_PBS2_CORE_LOCKBIT_D1_LOCKBIT_D1_LOCKED_OPEN_FVAL                                0x2
#define PMIO_PBS2_CORE_LOCKBIT_D1_LOCKBIT_D1_LOCKED_CLOSED_FVAL                              0x3

#define PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_ADDR                                      (PBS2_CORE_BASE      + 0x000000d4)
#define PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_OFFS                                      0x000000d4
#define PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_RMSK                                             0x1
#define PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_ADDR, PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_RMSK, 0, val)
#define PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_ADDR, val)
#define PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_ADDR, val, len)
#define PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_LOCKBIT_D1_BMSK                                  0x1
#define PMIO_PBS2_CORE_ILLEGAL_WRITE_STATUS_LOCKBIT_D1_SHFT                                  0x0

#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_ADDR                                          (PBS2_CORE_BASE      + 0x000000d9)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_OFFS                                          0x000000d9
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_RMSK                                                 0x1
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL2_ADDR, PMIO_PBS2_CORE_PERPH_RESET_CTL2_RMSK, 0, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL2_ADDR, val, len)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL2_ADDR, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL2_ADDR, val, len)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_BMSK                           0x1
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_SHFT                           0x0
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_RESET_IGNORED_FVAL             0x0
#define PMIO_PBS2_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_RESET_ARMED_FVAL               0x1

#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_ADDR                                          (PBS2_CORE_BASE      + 0x000000da)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_OFFS                                          0x000000da
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_RMSK                                                 0x7
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL3_ADDR, PMIO_PBS2_CORE_PERPH_RESET_CTL3_RMSK, 0, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL3_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL3_ADDR, val, len)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL3_ADDR, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL3_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL3_ADDR, val, len)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_BMSK                                  0x4
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_SHFT                                  0x2
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_RESET_IGNORED_FVAL                    0x0
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_RESET_ARMED_FVAL                      0x1
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_BMSK                             0x2
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_SHFT                             0x1
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_RESET_IGNORED_FVAL               0x0
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_RESET_ARMED_FVAL                 0x1
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_BMSK                             0x1
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_SHFT                             0x0
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_RESET_IGNORED_FVAL               0x0
#define PMIO_PBS2_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_RESET_ARMED_FVAL                 0x1

#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_ADDR                                          (PBS2_CORE_BASE      + 0x000000db)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_OFFS                                          0x000000db
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_RMSK                                                 0x1
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL4_ADDR, PMIO_PBS2_CORE_PERPH_RESET_CTL4_RMSK, 0, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL4_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL4_ADDR, val, len)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL4_ADDR, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL4_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_PERPH_RESET_CTL4_ADDR, val, len)
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_BMSK                                0x1
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_SHFT                                0x0
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_NORMAL_OPERATION_FVAL               0x0
#define PMIO_PBS2_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_SOFT_RESET_ASSERTED_FVAL            0x1

#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_ADDR                                             (PBS2_CORE_BASE      + 0x000000e0)
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_OFFS                                             0x000000e0
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_RMSK                                                    0x3
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_CFG_ADDR, PMIO_PBS2_CORE_SEQ_DEBUG_CFG_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_CFG_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_CFG_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_CFG_ADDR, val)
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_CFG_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_CFG_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_BMSK                                        0x2
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_SHFT                                        0x1
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_DEBUG_NEXT_CMD_FVAL                         0x0
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_DEBUG_NEXT_DTEST_FVAL                       0x1
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_DEBUG_EN_BMSK                                           0x1
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_DEBUG_EN_SHFT                                           0x0
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_DEBUG_EN_DISABLED_FVAL                                  0x0
#define PMIO_PBS2_CORE_SEQ_DEBUG_CFG_DEBUG_EN_ENABLED_FVAL                                   0x1

#define PMIO_PBS2_CORE_SEQ_DEBUG_NEXT_ADDR                                            (PBS2_CORE_BASE      + 0x000000e1)
#define PMIO_PBS2_CORE_SEQ_DEBUG_NEXT_OFFS                                            0x000000e1
#define PMIO_PBS2_CORE_SEQ_DEBUG_NEXT_RMSK                                                   0x1
#define PMIO_PBS2_CORE_SEQ_DEBUG_NEXT_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_NEXT_ADDR, val)
#define PMIO_PBS2_CORE_SEQ_DEBUG_NEXT_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_NEXT_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_BMSK                                          0x1
#define PMIO_PBS2_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_SHFT                                          0x0
#define PMIO_PBS2_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_DEBUG_NEXT_NOP_FVAL                           0x0
#define PMIO_PBS2_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_DEBUG_NEXT_TRIGGER_FVAL                       0x1

#define PMIO_PBS2_CORE_OTP_CFG1_ADDR                                                  (PBS2_CORE_BASE      + 0x000000e2)
#define PMIO_PBS2_CORE_OTP_CFG1_OFFS                                                  0x000000e2
#define PMIO_PBS2_CORE_OTP_CFG1_RMSK                                                         0xf
#define PMIO_PBS2_CORE_OTP_CFG1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG1_ADDR, PMIO_PBS2_CORE_OTP_CFG1_RMSK, 0, val)
#define PMIO_PBS2_CORE_OTP_CFG1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_OTP_CFG1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG1_ADDR, val, len)
#define PMIO_PBS2_CORE_OTP_CFG1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG1_ADDR, val)
#define PMIO_PBS2_CORE_OTP_CFG1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_OTP_CFG1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG1_ADDR, val, len)
#define PMIO_PBS2_CORE_OTP_CFG1_VPP_SEL_BMSK                                                 0x8
#define PMIO_PBS2_CORE_OTP_CFG1_VPP_SEL_SHFT                                                 0x3
#define PMIO_PBS2_CORE_OTP_CFG1_VPP_SEL_DVDD_FVAL                                            0x0
#define PMIO_PBS2_CORE_OTP_CFG1_VPP_SEL_VPP_EXT_FVAL                                         0x1
#define PMIO_PBS2_CORE_OTP_CFG1_PPROG_BMSK                                                   0x4
#define PMIO_PBS2_CORE_OTP_CFG1_PPROG_SHFT                                                   0x2
#define PMIO_PBS2_CORE_OTP_CFG1_PPROG_OTP_PROGRAMMING_DISABLED_FVAL                          0x0
#define PMIO_PBS2_CORE_OTP_CFG1_PPROG_OTP_PROGRAMMING_ENABLED_FVAL                           0x1
#define PMIO_PBS2_CORE_OTP_CFG1_PTM_BMSK                                                     0x3
#define PMIO_PBS2_CORE_OTP_CFG1_PTM_SHFT                                                     0x0
#define PMIO_PBS2_CORE_OTP_CFG1_PTM_REGULAR_MODES_FVAL                                       0x0
#define PMIO_PBS2_CORE_OTP_CFG1_PTM_RESERVED_FVAL                                            0x1
#define PMIO_PBS2_CORE_OTP_CFG1_PTM_MARGIN_1_READ_MODE_FVAL                                  0x2
#define PMIO_PBS2_CORE_OTP_CFG1_PTM_MARGIN_2_READ_MODE_FVAL                                  0x3

#define PMIO_PBS2_CORE_OTP_CFG2_ADDR                                                  (PBS2_CORE_BASE      + 0x000000e3)
#define PMIO_PBS2_CORE_OTP_CFG2_OFFS                                                  0x000000e3
#define PMIO_PBS2_CORE_OTP_CFG2_RMSK                                                        0x1f
#define PMIO_PBS2_CORE_OTP_CFG2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG2_ADDR, PMIO_PBS2_CORE_OTP_CFG2_RMSK, 0, val)
#define PMIO_PBS2_CORE_OTP_CFG2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_OTP_CFG2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG2_ADDR, val, len)
#define PMIO_PBS2_CORE_OTP_CFG2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG2_ADDR, val)
#define PMIO_PBS2_CORE_OTP_CFG2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_OTP_CFG2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_OTP_CFG2_ADDR, val, len)
#define PMIO_PBS2_CORE_OTP_CFG2_MARGIN_RD_WS_BMSK                                           0x1f
#define PMIO_PBS2_CORE_OTP_CFG2_MARGIN_RD_WS_SHFT                                            0x0

#define PMIO_PBS2_CORE_TEST1_ADDR                                                     (PBS2_CORE_BASE      + 0x000000e4)
#define PMIO_PBS2_CORE_TEST1_OFFS                                                     0x000000e4
#define PMIO_PBS2_CORE_TEST1_RMSK                                                           0xff
#define PMIO_PBS2_CORE_TEST1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TEST1_ADDR, PMIO_PBS2_CORE_TEST1_RMSK, 0, val)
#define PMIO_PBS2_CORE_TEST1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TEST1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TEST1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_TEST1_ADDR, val, len)
#define PMIO_PBS2_CORE_TEST1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_TEST1_ADDR, val)
#define PMIO_PBS2_CORE_TEST1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_TEST1_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_TEST1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_TEST1_ADDR, val, len)
#define PMIO_PBS2_CORE_TEST1_DTEST4_EN_BMSK                                                 0x80
#define PMIO_PBS2_CORE_TEST1_DTEST4_EN_SHFT                                                  0x7
#define PMIO_PBS2_CORE_TEST1_DTEST4_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS2_CORE_TEST1_DTEST4_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS2_CORE_TEST1_DTEST3_EN_BMSK                                                 0x40
#define PMIO_PBS2_CORE_TEST1_DTEST3_EN_SHFT                                                  0x6
#define PMIO_PBS2_CORE_TEST1_DTEST3_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS2_CORE_TEST1_DTEST3_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS2_CORE_TEST1_DTEST2_EN_BMSK                                                 0x20
#define PMIO_PBS2_CORE_TEST1_DTEST2_EN_SHFT                                                  0x5
#define PMIO_PBS2_CORE_TEST1_DTEST2_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS2_CORE_TEST1_DTEST2_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS2_CORE_TEST1_DTEST1_EN_BMSK                                                 0x10
#define PMIO_PBS2_CORE_TEST1_DTEST1_EN_SHFT                                                  0x4
#define PMIO_PBS2_CORE_TEST1_DTEST1_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS2_CORE_TEST1_DTEST1_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS2_CORE_TEST1_DTEST_SEL_BMSK                                                  0xf
#define PMIO_PBS2_CORE_TEST1_DTEST_SEL_SHFT                                                  0x0

#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_ADDR                                           (PBS2_CORE_BASE      + 0x000000e5)
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_OFFS                                           0x000000e5
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_RMSK                                                  0x7
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_ADDR, PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_ADDR, val)
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_BMSK                                  0x7
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_SHFT                                  0x0
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST1_FVAL                           0x0
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST2_FVAL                           0x1
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST3_FVAL                           0x2
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST4_FVAL                           0x3
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST5_FVAL                           0x4
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST6_FVAL                           0x5
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST7_FVAL                           0x6
#define PMIO_PBS2_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST8_FVAL                           0x7

#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_ADDR                                        (PBS2_CORE_BASE      + 0x000000ec)
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_OFFS                                        0x000000ec
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_RMSK                                               0x1
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_ADDR, PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_ADDR, val)
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_BP_EN_BMSK                                         0x1
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_BP_EN_SHFT                                         0x0
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_BP_EN_DISABLED_FVAL                                0x0
#define PMIO_PBS2_CORE_SEQ_BREAKPOINT_CFG_BP_EN_ENABLED_FVAL                                 0x1

#define PMIO_PBS2_CORE_SEQ_BP_CTL_ADDR                                                (PBS2_CORE_BASE      + 0x000000ed)
#define PMIO_PBS2_CORE_SEQ_BP_CTL_OFFS                                                0x000000ed
#define PMIO_PBS2_CORE_SEQ_BP_CTL_RMSK                                                       0x1
#define PMIO_PBS2_CORE_SEQ_BP_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_CTL_ADDR, val)
#define PMIO_PBS2_CORE_SEQ_BP_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_CTL_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_BP_CTL_BP_CONTINUE_BMSK                                           0x1
#define PMIO_PBS2_CORE_SEQ_BP_CTL_BP_CONTINUE_SHFT                                           0x0
#define PMIO_PBS2_CORE_SEQ_BP_CTL_BP_CONTINUE_DEBUG_NEXT_NOP_FVAL                            0x0
#define PMIO_PBS2_CORE_SEQ_BP_CTL_BP_CONTINUE_DEBUG_NEXT_TRIGGER_FVAL                        0x1

#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_ADDR                                           (PBS2_CORE_BASE      + 0x000000ee)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_OFFS                                           0x000000ee
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_RMSK                                                 0xff
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_ADDR, PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_ADDR, val)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_BMSK                                     0xff
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_SHFT                                      0x0
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_DEBUG_NEXT_NOP_FVAL                       0x0
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_DEBUG_NEXT_TRIGGER_FVAL                   0x1

#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_ADDR                                           (PBS2_CORE_BASE      + 0x000000ef)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_OFFS                                           0x000000ef
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_RMSK                                                 0xff
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_ADDR, PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_RMSK, 0, val)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_ADDR, val)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_BMSK                                     0xff
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_SHFT                                      0x0
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_DEBUG_NEXT_NOP_FVAL                       0x0
#define PMIO_PBS2_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_DEBUG_NEXT_TRIGGER_FVAL                   0x1

/*----------------------------------------------------------------------------
 * PERIPHERAL: PBS3_CORE
 *--------------------------------------------------------------------------*/

#define PBS3_CORE_BASE                                                                0x00001e00

#define PMIO_PBS3_CORE_REVISION1_ADDR                                                 (PBS3_CORE_BASE      + 0x00000000)
#define PMIO_PBS3_CORE_REVISION1_OFFS                                                 0x00000000
#define PMIO_PBS3_CORE_REVISION1_RMSK                                                       0xff
#define PMIO_PBS3_CORE_REVISION1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_REVISION1_ADDR, PMIO_PBS3_CORE_REVISION1_RMSK, 0, val)
#define PMIO_PBS3_CORE_REVISION1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_REVISION1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_REVISION1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_REVISION1_ADDR, val, len)
#define PMIO_PBS3_CORE_REVISION1_DIG_MINOR_BMSK                                             0xff
#define PMIO_PBS3_CORE_REVISION1_DIG_MINOR_SHFT                                              0x0

#define PMIO_PBS3_CORE_REVISION2_ADDR                                                 (PBS3_CORE_BASE      + 0x00000001)
#define PMIO_PBS3_CORE_REVISION2_OFFS                                                 0x00000001
#define PMIO_PBS3_CORE_REVISION2_RMSK                                                       0xff
#define PMIO_PBS3_CORE_REVISION2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_REVISION2_ADDR, PMIO_PBS3_CORE_REVISION2_RMSK, 0, val)
#define PMIO_PBS3_CORE_REVISION2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_REVISION2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_REVISION2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_REVISION2_ADDR, val, len)
#define PMIO_PBS3_CORE_REVISION2_DIG_MAJOR_BMSK                                             0xff
#define PMIO_PBS3_CORE_REVISION2_DIG_MAJOR_SHFT                                              0x0

#define PMIO_PBS3_CORE_REVISION3_ADDR                                                 (PBS3_CORE_BASE      + 0x00000002)
#define PMIO_PBS3_CORE_REVISION3_OFFS                                                 0x00000002
#define PMIO_PBS3_CORE_REVISION3_RMSK                                                       0xff
#define PMIO_PBS3_CORE_REVISION3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_REVISION3_ADDR, PMIO_PBS3_CORE_REVISION3_RMSK, 0, val)
#define PMIO_PBS3_CORE_REVISION3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_REVISION3_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_REVISION3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_REVISION3_ADDR, val, len)
#define PMIO_PBS3_CORE_REVISION3_ANA_MINOR_BMSK                                             0xff
#define PMIO_PBS3_CORE_REVISION3_ANA_MINOR_SHFT                                              0x0

#define PMIO_PBS3_CORE_REVISION4_ADDR                                                 (PBS3_CORE_BASE      + 0x00000003)
#define PMIO_PBS3_CORE_REVISION4_OFFS                                                 0x00000003
#define PMIO_PBS3_CORE_REVISION4_RMSK                                                       0xff
#define PMIO_PBS3_CORE_REVISION4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_REVISION4_ADDR, PMIO_PBS3_CORE_REVISION4_RMSK, 0, val)
#define PMIO_PBS3_CORE_REVISION4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_REVISION4_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_REVISION4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_REVISION4_ADDR, val, len)
#define PMIO_PBS3_CORE_REVISION4_ANA_MAJOR_BMSK                                             0xff
#define PMIO_PBS3_CORE_REVISION4_ANA_MAJOR_SHFT                                              0x0

#define PMIO_PBS3_CORE_PERPH_TYPE_ADDR                                                (PBS3_CORE_BASE      + 0x00000004)
#define PMIO_PBS3_CORE_PERPH_TYPE_OFFS                                                0x00000004
#define PMIO_PBS3_CORE_PERPH_TYPE_RMSK                                                      0xff
#define PMIO_PBS3_CORE_PERPH_TYPE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_TYPE_ADDR, PMIO_PBS3_CORE_PERPH_TYPE_RMSK, 0, val)
#define PMIO_PBS3_CORE_PERPH_TYPE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_TYPE_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PERPH_TYPE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PERPH_TYPE_ADDR, val, len)
#define PMIO_PBS3_CORE_PERPH_TYPE_TYPE_BMSK                                                 0xff
#define PMIO_PBS3_CORE_PERPH_TYPE_TYPE_SHFT                                                  0x0
#define PMIO_PBS3_CORE_PERPH_TYPE_TYPE_PBS_FVAL                                             0x16

#define PMIO_PBS3_CORE_PERPH_SUBTYPE_ADDR                                             (PBS3_CORE_BASE      + 0x00000005)
#define PMIO_PBS3_CORE_PERPH_SUBTYPE_OFFS                                             0x00000005
#define PMIO_PBS3_CORE_PERPH_SUBTYPE_RMSK                                                   0xff
#define PMIO_PBS3_CORE_PERPH_SUBTYPE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_SUBTYPE_ADDR, PMIO_PBS3_CORE_PERPH_SUBTYPE_RMSK, 0, val)
#define PMIO_PBS3_CORE_PERPH_SUBTYPE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_SUBTYPE_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PERPH_SUBTYPE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PERPH_SUBTYPE_ADDR, val, len)
#define PMIO_PBS3_CORE_PERPH_SUBTYPE_SUBTYPE_BMSK                                           0xff
#define PMIO_PBS3_CORE_PERPH_SUBTYPE_SUBTYPE_SHFT                                            0x0
#define PMIO_PBS3_CORE_PERPH_SUBTYPE_SUBTYPE_PBS_CORE_FVAL                                   0x1

#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_ADDR                                       (PBS3_CORE_BASE      + 0x00000006)
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_OFFS                                       0x00000006
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_RMSK                                             0x1f
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_ADDR, PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_RMSK, 0, val)
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_ADDR, val, len)
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_SHARED_OTP_CONFIG_BMSK                           0x10
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_SHARED_OTP_CONFIG_SHFT                            0x4
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_RAM_CONFIG_BMSK                             0x8
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_RAM_CONFIG_SHFT                             0x3
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_OTP_CONFIG_BMSK                             0x4
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_PMIC7_OTP_CONFIG_SHFT                             0x2
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_RAM_CONFIG_BMSK                             0x2
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_RAM_CONFIG_SHFT                             0x1
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_OTP_CONFIG_BMSK                             0x1
#define PMIO_PBS3_CORE_GEN_PMIC_MEM_CONFIG_PMIC5_OTP_CONFIG_SHFT                             0x0

#define PMIO_PBS3_CORE_NUM_CLIENTS_ADDR                                               (PBS3_CORE_BASE      + 0x00000007)
#define PMIO_PBS3_CORE_NUM_CLIENTS_OFFS                                               0x00000007
#define PMIO_PBS3_CORE_NUM_CLIENTS_RMSK                                                     0xff
#define PMIO_PBS3_CORE_NUM_CLIENTS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_NUM_CLIENTS_ADDR, PMIO_PBS3_CORE_NUM_CLIENTS_RMSK, 0, val)
#define PMIO_PBS3_CORE_NUM_CLIENTS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_NUM_CLIENTS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_NUM_CLIENTS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_NUM_CLIENTS_ADDR, val, len)
#define PMIO_PBS3_CORE_NUM_CLIENTS_NUM_CLIENTS_BMSK                                         0xff
#define PMIO_PBS3_CORE_NUM_CLIENTS_NUM_CLIENTS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_STATUS0_ADDR                                               (PBS3_CORE_BASE      + 0x00000008)
#define PMIO_PBS3_CORE_SEQ_STATUS0_OFFS                                               0x00000008
#define PMIO_PBS3_CORE_SEQ_STATUS0_RMSK                                                     0x3f
#define PMIO_PBS3_CORE_SEQ_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_STATUS0_ADDR, PMIO_PBS3_CORE_SEQ_STATUS0_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_STATUS0_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_BMSK                                0x30
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_SHFT                                 0x4
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_RESERVED_FVAL                        0x0
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_NORMAL_FVAL                          0x1
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_ERROR_FVAL                           0x2
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_STATUS_ABORT_FVAL                           0x3
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_BMSK                                        0xf
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_SHFT                                        0x0
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_0_FVAL                               0x0
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_1_FVAL                               0x1
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_2_FVAL                               0x2
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_3_FVAL                               0x3
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_4_FVAL                               0x4
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_5_FVAL                               0x5
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_6_FVAL                               0x6
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_7_FVAL                               0x7
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_8_FVAL                               0x8
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_9_FVAL                               0x9
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_10_FVAL                              0xa
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_11_FVAL                              0xb
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_12_FVAL                              0xc
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_13_FVAL                              0xd
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_14_FVAL                              0xe
#define PMIO_PBS3_CORE_SEQ_STATUS0_LAST_SEQ_COMP_CLIENT_15_FVAL                              0xf

#define PMIO_PBS3_CORE_NUM_TRIGCL_ADDR                                                (PBS3_CORE_BASE      + 0x00000009)
#define PMIO_PBS3_CORE_NUM_TRIGCL_OFFS                                                0x00000009
#define PMIO_PBS3_CORE_NUM_TRIGCL_RMSK                                                      0xff
#define PMIO_PBS3_CORE_NUM_TRIGCL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_NUM_TRIGCL_ADDR, PMIO_PBS3_CORE_NUM_TRIGCL_RMSK, 0, val)
#define PMIO_PBS3_CORE_NUM_TRIGCL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_NUM_TRIGCL_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_NUM_TRIGCL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_NUM_TRIGCL_ADDR, val, len)
#define PMIO_PBS3_CORE_NUM_TRIGCL_NUM_TRIGCL_BMSK                                           0xff
#define PMIO_PBS3_CORE_NUM_TRIGCL_NUM_TRIGCL_SHFT                                            0x0

#define PMIO_PBS3_CORE_SEQ_PC_STATUS0_ADDR                                            (PBS3_CORE_BASE      + 0x0000000a)
#define PMIO_PBS3_CORE_SEQ_PC_STATUS0_OFFS                                            0x0000000a
#define PMIO_PBS3_CORE_SEQ_PC_STATUS0_RMSK                                                  0xff
#define PMIO_PBS3_CORE_SEQ_PC_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_PC_STATUS0_ADDR, PMIO_PBS3_CORE_SEQ_PC_STATUS0_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_PC_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_PC_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_PC_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_PC_STATUS0_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_PC_STATUS0_PC_LSB_BMSK                                           0xff
#define PMIO_PBS3_CORE_SEQ_PC_STATUS0_PC_LSB_SHFT                                            0x0

#define PMIO_PBS3_CORE_SEQ_PC_STATUS1_ADDR                                            (PBS3_CORE_BASE      + 0x0000000b)
#define PMIO_PBS3_CORE_SEQ_PC_STATUS1_OFFS                                            0x0000000b
#define PMIO_PBS3_CORE_SEQ_PC_STATUS1_RMSK                                                  0xff
#define PMIO_PBS3_CORE_SEQ_PC_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_PC_STATUS1_ADDR, PMIO_PBS3_CORE_SEQ_PC_STATUS1_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_PC_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_PC_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_PC_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_PC_STATUS1_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_PC_STATUS1_PC_MSB_BMSK                                           0xff
#define PMIO_PBS3_CORE_SEQ_PC_STATUS1_PC_MSB_SHFT                                            0x0

#define PMIO_PBS3_CORE_SEQ_IR_STATUS0_ADDR                                            (PBS3_CORE_BASE      + 0x0000000c)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS0_OFFS                                            0x0000000c
#define PMIO_PBS3_CORE_SEQ_IR_STATUS0_RMSK                                                  0xff
#define PMIO_PBS3_CORE_SEQ_IR_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS0_ADDR, PMIO_PBS3_CORE_SEQ_IR_STATUS0_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS0_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS0_IR_BYTE0_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_IR_STATUS0_IR_BYTE0_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_IR_STATUS1_ADDR                                            (PBS3_CORE_BASE      + 0x0000000d)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS1_OFFS                                            0x0000000d
#define PMIO_PBS3_CORE_SEQ_IR_STATUS1_RMSK                                                  0xff
#define PMIO_PBS3_CORE_SEQ_IR_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS1_ADDR, PMIO_PBS3_CORE_SEQ_IR_STATUS1_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS1_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS1_IR_BYTE1_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_IR_STATUS1_IR_BYTE1_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_IR_STATUS2_ADDR                                            (PBS3_CORE_BASE      + 0x0000000e)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS2_OFFS                                            0x0000000e
#define PMIO_PBS3_CORE_SEQ_IR_STATUS2_RMSK                                                  0xff
#define PMIO_PBS3_CORE_SEQ_IR_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS2_ADDR, PMIO_PBS3_CORE_SEQ_IR_STATUS2_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS2_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS2_IR_BYTE2_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_IR_STATUS2_IR_BYTE2_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_IR_STATUS3_ADDR                                            (PBS3_CORE_BASE      + 0x0000000f)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS3_OFFS                                            0x0000000f
#define PMIO_PBS3_CORE_SEQ_IR_STATUS3_RMSK                                                  0xff
#define PMIO_PBS3_CORE_SEQ_IR_STATUS3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS3_ADDR, PMIO_PBS3_CORE_SEQ_IR_STATUS3_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS3_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_IR_STATUS3_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_IR_STATUS3_IR_BYTE3_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_IR_STATUS3_IR_BYTE3_SHFT                                          0x0

#define PMIO_PBS3_CORE_PMIC_CTL_CFG_ADDR                                              (PBS3_CORE_BASE      + 0x00000030)
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_OFFS                                              0x00000030
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_RMSK                                                    0xc0
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PMIC_CTL_CFG_ADDR, PMIO_PBS3_CORE_PMIC_CTL_CFG_RMSK, 0, val)
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PMIC_CTL_CFG_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PMIC_CTL_CFG_ADDR, val, len)
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PMIC_CTL_CFG_ADDR, val)
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PMIC_CTL_CFG_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PMIC_CTL_CFG_ADDR, val, len)
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_BMSK                                      0x80
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_SHFT                                       0x7
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_DISABLED_FVAL                              0x0
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_LOOPBACK_MODE_ENABLED_FVAL                               0x1
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_BMSK                                0x40
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_SHFT                                 0x6
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_MASTER_SECONDARY_ARB_FVAL            0x0
#define PMIO_PBS3_CORE_PMIC_CTL_CFG_SPMI_M_PRIORITY_CTL_MASTER_PRIORITY_ARB_FVAL             0x1

#define PMIO_PBS3_CORE_PBS_WDOG_CTL_ADDR                                              (PBS3_CORE_BASE      + 0x00000031)
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_OFFS                                              0x00000031
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_RMSK                                                    0x80
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_CTL_ADDR, PMIO_PBS3_CORE_PBS_WDOG_CTL_RMSK, 0, val)
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_CTL_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_CTL_ADDR, val, len)
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_CTL_ADDR, val)
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_CTL_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_CTL_ADDR, val, len)
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_ENABLE_BMSK                                             0x80
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_ENABLE_SHFT                                              0x7
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_ENABLE_DISABLED_FVAL                                     0x0
#define PMIO_PBS3_CORE_PBS_WDOG_CTL_ENABLE_ENABLED_FVAL                                      0x1

#define PMIO_PBS3_CORE_PBS_WDOG_PET_ADDR                                              (PBS3_CORE_BASE      + 0x00000032)
#define PMIO_PBS3_CORE_PBS_WDOG_PET_OFFS                                              0x00000032
#define PMIO_PBS3_CORE_PBS_WDOG_PET_RMSK                                                    0x80
#define PMIO_PBS3_CORE_PBS_WDOG_PET_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_PET_ADDR, val)
#define PMIO_PBS3_CORE_PBS_WDOG_PET_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_PET_ADDR, val, len)
#define PMIO_PBS3_CORE_PBS_WDOG_PET_PET_BMSK                                                0x80
#define PMIO_PBS3_CORE_PBS_WDOG_PET_PET_SHFT                                                 0x7

#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_ADDR                                          (PBS3_CORE_BASE      + 0x00000033)
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_OFFS                                          0x00000033
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_RMSK                                                 0x3
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_ADDR, PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_RMSK, 0, val)
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_ADDR, val, len)
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_ADDR, val)
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_ADDR, val, len)
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_BMSK                                0x3
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_SHFT                                0x0
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_PBS_WDOG_1_MS_FVAL                  0x0
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_PBS_WDOG_10_MS_FVAL                 0x1
#define PMIO_PBS3_CORE_PBS_WDOG_MAX_CNT_WDOG_MAX_CNT_SEL_PBS_WDOG_100_MS_FVAL                0x2

#define PMIO_PBS3_CORE_PBS_SPMI_USID_ADDR                                             (PBS3_CORE_BASE      + 0x00000038)
#define PMIO_PBS3_CORE_PBS_SPMI_USID_OFFS                                             0x00000038
#define PMIO_PBS3_CORE_PBS_SPMI_USID_RMSK                                                    0xf
#define PMIO_PBS3_CORE_PBS_SPMI_USID_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_USID_ADDR, PMIO_PBS3_CORE_PBS_SPMI_USID_RMSK, 0, val)
#define PMIO_PBS3_CORE_PBS_SPMI_USID_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_USID_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PBS_SPMI_USID_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_USID_ADDR, val, len)
#define PMIO_PBS3_CORE_PBS_SPMI_USID_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_USID_ADDR, val)
#define PMIO_PBS3_CORE_PBS_SPMI_USID_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_USID_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PBS_SPMI_USID_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_USID_ADDR, val, len)
#define PMIO_PBS3_CORE_PBS_SPMI_USID_PBS_SPMI_USID_BMSK                                      0xf
#define PMIO_PBS3_CORE_PBS_SPMI_USID_PBS_SPMI_USID_SHFT                                      0x0

#define PMIO_PBS3_CORE_PBS_SPMI_GSID_ADDR                                             (PBS3_CORE_BASE      + 0x00000039)
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_OFFS                                             0x00000039
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_RMSK                                                   0xff
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_GSID_ADDR, PMIO_PBS3_CORE_PBS_SPMI_GSID_RMSK, 0, val)
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_GSID_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_GSID_ADDR, val, len)
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_GSID_ADDR, val)
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_GSID_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PBS_SPMI_GSID_ADDR, val, len)
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID1_BMSK                                    0xf0
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID1_SHFT                                     0x4
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID0_BMSK                                     0xf
#define PMIO_PBS3_CORE_PBS_SPMI_GSID_PBS_SPMI_GSID0_SHFT                                     0x0

#define PMIO_PBS3_CORE_MEM_INTF_CFG_ADDR                                              (PBS3_CORE_BASE      + 0x00000040)
#define PMIO_PBS3_CORE_MEM_INTF_CFG_OFFS                                              0x00000040
#define PMIO_PBS3_CORE_MEM_INTF_CFG_RMSK                                                    0x80
#define PMIO_PBS3_CORE_MEM_INTF_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CFG_ADDR, PMIO_PBS3_CORE_MEM_INTF_CFG_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CFG_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CFG_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CFG_ADDR, val)
#define PMIO_PBS3_CORE_MEM_INTF_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CFG_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CFG_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_BMSK                                  0x80
#define PMIO_PBS3_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_SHFT                                   0x7
#define PMIO_PBS3_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_DISABLED_FVAL                          0x0
#define PMIO_PBS3_CORE_MEM_INTF_CFG_RIF_MEM_ACCESS_EN_ENABLED_FVAL                           0x1

#define PMIO_PBS3_CORE_MEM_INTF_CTL_ADDR                                              (PBS3_CORE_BASE      + 0x00000041)
#define PMIO_PBS3_CORE_MEM_INTF_CTL_OFFS                                              0x00000041
#define PMIO_PBS3_CORE_MEM_INTF_CTL_RMSK                                                    0xc0
#define PMIO_PBS3_CORE_MEM_INTF_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CTL_ADDR, PMIO_PBS3_CORE_MEM_INTF_CTL_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CTL_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CTL_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CTL_ADDR, val)
#define PMIO_PBS3_CORE_MEM_INTF_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CTL_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_CTL_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_CTL_BURST_BMSK                                              0x80
#define PMIO_PBS3_CORE_MEM_INTF_CTL_BURST_SHFT                                               0x7
#define PMIO_PBS3_CORE_MEM_INTF_CTL_BURST_SINGLE_MODE_FVAL                                   0x0
#define PMIO_PBS3_CORE_MEM_INTF_CTL_BURST_BURST_MODE_FVAL                                    0x1
#define PMIO_PBS3_CORE_MEM_INTF_CTL_WR_EN_BMSK                                              0x40
#define PMIO_PBS3_CORE_MEM_INTF_CTL_WR_EN_SHFT                                               0x6
#define PMIO_PBS3_CORE_MEM_INTF_CTL_WR_EN_READ_ACCESS_FVAL                                   0x0
#define PMIO_PBS3_CORE_MEM_INTF_CTL_WR_EN_WRITE_ACCESS_FVAL                                  0x1

#define PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_ADDR                                         (PBS3_CORE_BASE      + 0x00000042)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_OFFS                                         0x00000042
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_RMSK                                               0xff
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_ADDR, PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_ADDR, val)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_MEM_INTF_ADDR_LSB_BMSK                             0xff
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_LSB_MEM_INTF_ADDR_LSB_SHFT                              0x0

#define PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_ADDR                                         (PBS3_CORE_BASE      + 0x00000043)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_OFFS                                         0x00000043
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_RMSK                                               0xff
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_ADDR, PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_ADDR, val)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_MEM_INTF_ADDR_MSB_BMSK                             0xff
#define PMIO_PBS3_CORE_MEM_INTF_ADDR_MSB_MEM_INTF_ADDR_MSB_SHFT                              0x0

#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_ADDR                                         (PBS3_CORE_BASE      + 0x00000048)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_OFFS                                         0x00000048
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_RMSK                                               0xff
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_ADDR, PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_ADDR, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_MEM_INTF_WR_DATA_0_BMSK                            0xff
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA0_MEM_INTF_WR_DATA_0_SHFT                             0x0

#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_ADDR                                         (PBS3_CORE_BASE      + 0x00000049)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_OFFS                                         0x00000049
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_RMSK                                               0xff
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_ADDR, PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_ADDR, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_MEM_INTF_WR_DATA_1_BMSK                            0xff
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA1_MEM_INTF_WR_DATA_1_SHFT                             0x0

#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_ADDR                                         (PBS3_CORE_BASE      + 0x0000004a)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_OFFS                                         0x0000004a
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_RMSK                                               0xff
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_ADDR, PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_ADDR, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_MEM_INTF_WR_DATA_2_BMSK                            0xff
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA2_MEM_INTF_WR_DATA_2_SHFT                             0x0

#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_ADDR                                         (PBS3_CORE_BASE      + 0x0000004b)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_OFFS                                         0x0000004b
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_RMSK                                               0xff
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_ADDR, PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_ADDR, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_MEM_INTF_WR_DATA_3_BMSK                            0xff
#define PMIO_PBS3_CORE_MEM_INTF_WR_DATA3_MEM_INTF_WR_DATA_3_SHFT                             0x0

#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_ADDR                                         (PBS3_CORE_BASE      + 0x0000004c)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_OFFS                                         0x0000004c
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_RMSK                                               0xff
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_ADDR, PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_MEM_INTF_RD_DATA_0_BMSK                            0xff
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA0_MEM_INTF_RD_DATA_0_SHFT                             0x0

#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_ADDR                                         (PBS3_CORE_BASE      + 0x0000004d)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_OFFS                                         0x0000004d
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_RMSK                                               0xff
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_ADDR, PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_MEM_INTF_RD_DATA_1_BMSK                            0xff
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA1_MEM_INTF_RD_DATA_1_SHFT                             0x0

#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_ADDR                                         (PBS3_CORE_BASE      + 0x0000004e)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_OFFS                                         0x0000004e
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_RMSK                                               0xff
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_ADDR, PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_MEM_INTF_RD_DATA_2_BMSK                            0xff
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA2_MEM_INTF_RD_DATA_2_SHFT                             0x0

#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_ADDR                                         (PBS3_CORE_BASE      + 0x0000004f)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_OFFS                                         0x0000004f
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_RMSK                                               0xff
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_ADDR, PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_RMSK, 0, val)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_ADDR, val, len)
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_MEM_INTF_RD_DATA_3_BMSK                            0xff
#define PMIO_PBS3_CORE_MEM_INTF_RD_DATA3_MEM_INTF_RD_DATA_3_SHFT                             0x0

#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_ADDR                                     (PBS3_CORE_BASE      + 0x00000050)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_OFFS                                     0x00000050
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_RMSK                                           0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_ADDR, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_RMSK, 0, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_ADDR, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_SEQ_ADDR_LSB_BMSK                              0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_0_SEQ_ADDR_LSB_SHFT                               0x0

#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_ADDR                                     (PBS3_CORE_BASE      + 0x00000054)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_OFFS                                     0x00000054
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_RMSK                                           0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_ADDR, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_RMSK, 0, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_ADDR, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_SEQ_ADDR_LSB_BMSK                              0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_1_SEQ_ADDR_LSB_SHFT                               0x0

#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_ADDR                                     (PBS3_CORE_BASE      + 0x00000058)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_OFFS                                     0x00000058
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_RMSK                                           0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_ADDR, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_RMSK, 0, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_ADDR, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_SEQ_ADDR_LSB_BMSK                              0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_LSB_2_SEQ_ADDR_LSB_SHFT                               0x0

#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_ADDR                                     (PBS3_CORE_BASE      + 0x00000051)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_OFFS                                     0x00000051
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_RMSK                                           0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_ADDR, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_RMSK, 0, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_ADDR, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_SEQ_ADDR_MSB_BMSK                              0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_0_SEQ_ADDR_MSB_SHFT                               0x0

#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_ADDR                                     (PBS3_CORE_BASE      + 0x00000055)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_OFFS                                     0x00000055
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_RMSK                                           0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_ADDR, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_RMSK, 0, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_ADDR, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_SEQ_ADDR_MSB_BMSK                              0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_1_SEQ_ADDR_MSB_SHFT                               0x0

#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_ADDR                                     (PBS3_CORE_BASE      + 0x00000059)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_OFFS                                     0x00000059
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_RMSK                                           0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_ADDR, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_RMSK, 0, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_ADDR, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_SEQ_ADDR_MSB_BMSK                              0xff
#define PMIO_PBS3_CORE_TRIG_START_ADDR_MSB_2_SEQ_ADDR_MSB_SHFT                               0x0

#define PMIO_PBS3_CORE_SEQ_STATUS1_ADDR                                               (PBS3_CORE_BASE      + 0x00000090)
#define PMIO_PBS3_CORE_SEQ_STATUS1_OFFS                                               0x00000090
#define PMIO_PBS3_CORE_SEQ_STATUS1_RMSK                                                     0xff
#define PMIO_PBS3_CORE_SEQ_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_STATUS1_ADDR, PMIO_PBS3_CORE_SEQ_STATUS1_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_STATUS1_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_BMSK                                      0xf0
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_SHFT                                       0x4
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_0_FVAL                              0x0
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_1_FVAL                              0x1
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_2_FVAL                              0x2
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_3_FVAL                              0x3
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_4_FVAL                              0x4
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_5_FVAL                              0x5
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_6_FVAL                              0x6
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_7_FVAL                              0x7
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_8_FVAL                              0x8
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_9_FVAL                              0x9
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_10_FVAL                             0xa
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_11_FVAL                             0xb
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_12_FVAL                             0xc
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_13_FVAL                             0xd
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_14_FVAL                             0xe
#define PMIO_PBS3_CORE_SEQ_STATUS1_SEQ_IN_SERVICE_CLIENT_15_FVAL                             0xf
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_BMSK                                      0xf
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_SHFT                                      0x0
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_0_FVAL                             0x0
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_1_FVAL                             0x1
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_2_FVAL                             0x2
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_3_FVAL                             0x3
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_4_FVAL                             0x4
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_5_FVAL                             0x5
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_6_FVAL                             0x6
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_7_FVAL                             0x7
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_8_FVAL                             0x8
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_9_FVAL                             0x9
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_10_FVAL                            0xa
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_11_FVAL                            0xb
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_12_FVAL                            0xc
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_13_FVAL                            0xd
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_14_FVAL                            0xe
#define PMIO_PBS3_CORE_SEQ_STATUS1_LAST_SEQ_NORMAL_CLIENT_15_FVAL                            0xf

#define PMIO_PBS3_CORE_SEQ_STATUS2_ADDR                                               (PBS3_CORE_BASE      + 0x00000091)
#define PMIO_PBS3_CORE_SEQ_STATUS2_OFFS                                               0x00000091
#define PMIO_PBS3_CORE_SEQ_STATUS2_RMSK                                                     0xff
#define PMIO_PBS3_CORE_SEQ_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_STATUS2_ADDR, PMIO_PBS3_CORE_SEQ_STATUS2_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_STATUS2_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_BMSK                                    0xf0
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_SHFT                                     0x4
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_0_FVAL                            0x0
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_1_FVAL                            0x1
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_2_FVAL                            0x2
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_3_FVAL                            0x3
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_4_FVAL                            0x4
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_5_FVAL                            0x5
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_6_FVAL                            0x6
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_7_FVAL                            0x7
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_8_FVAL                            0x8
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_9_FVAL                            0x9
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_10_FVAL                           0xa
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_11_FVAL                           0xb
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_12_FVAL                           0xc
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_13_FVAL                           0xd
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_14_FVAL                           0xe
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ABORTED_CLIENT_15_FVAL                           0xf
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_BMSK                                       0xf
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_SHFT                                       0x0
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_0_FVAL                              0x0
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_1_FVAL                              0x1
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_2_FVAL                              0x2
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_3_FVAL                              0x3
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_4_FVAL                              0x4
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_5_FVAL                              0x5
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_6_FVAL                              0x6
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_7_FVAL                              0x7
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_8_FVAL                              0x8
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_9_FVAL                              0x9
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_10_FVAL                             0xa
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_11_FVAL                             0xb
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_12_FVAL                             0xc
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_13_FVAL                             0xd
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_14_FVAL                             0xe
#define PMIO_PBS3_CORE_SEQ_STATUS2_LAST_SEQ_ERROR_CLIENT_15_FVAL                             0xf

#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_ADDR                                        (PBS3_CORE_BASE      + 0x00000092)
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_OFFS                                        0x00000092
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_RMSK                                              0xff
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_ADDR, PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_ERR_PC_LSB_BMSK                                   0xff
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS0_ERR_PC_LSB_SHFT                                    0x0

#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_ADDR                                        (PBS3_CORE_BASE      + 0x00000093)
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_OFFS                                        0x00000093
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_RMSK                                              0xff
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_ADDR, PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_ERR_PC_MSB_BMSK                                   0xff
#define PMIO_PBS3_CORE_SEQ_ERR_PC_STATUS1_ERR_PC_MSB_SHFT                                    0x0

#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_ADDR                                        (PBS3_CORE_BASE      + 0x00000094)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_OFFS                                        0x00000094
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_RMSK                                              0xff
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_ADDR, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_ERR_IR_BYTE0_BMSK                                 0xff
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS0_ERR_IR_BYTE0_SHFT                                  0x0

#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_ADDR                                        (PBS3_CORE_BASE      + 0x00000095)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_OFFS                                        0x00000095
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_RMSK                                              0xff
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_ADDR, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_ERR_IR_BYTE1_BMSK                                 0xff
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS1_ERR_IR_BYTE1_SHFT                                  0x0

#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_ADDR                                        (PBS3_CORE_BASE      + 0x00000096)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_OFFS                                        0x00000096
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_RMSK                                              0xff
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_ADDR, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_ERR_IR_BYTE2_BMSK                                 0xff
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS2_ERR_IR_BYTE2_SHFT                                  0x0

#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_ADDR                                        (PBS3_CORE_BASE      + 0x00000097)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_OFFS                                        0x00000097
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_RMSK                                              0xff
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_ADDR, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_ERR_IR_BYTE3_BMSK                                 0xff
#define PMIO_PBS3_CORE_SEQ_ERR_IR_STATUS3_ERR_IR_BYTE3_SHFT                                  0x0

#define PMIO_PBS3_CORE_TRIG_STATUS0_ADDR                                              (PBS3_CORE_BASE      + 0x00000098)
#define PMIO_PBS3_CORE_TRIG_STATUS0_OFFS                                              0x00000098
#define PMIO_PBS3_CORE_TRIG_STATUS0_RMSK                                                    0x7f
#define PMIO_PBS3_CORE_TRIG_STATUS0_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS0_ADDR, PMIO_PBS3_CORE_TRIG_STATUS0_RMSK, 0, val)
#define PMIO_PBS3_CORE_TRIG_STATUS0_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS0_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_STATUS0_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS0_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_STATUS0_LAST_TRIG_COMP_BMSK                                     0x7f
#define PMIO_PBS3_CORE_TRIG_STATUS0_LAST_TRIG_COMP_SHFT                                      0x0

#define PMIO_PBS3_CORE_TRIG_STATUS1_ADDR                                              (PBS3_CORE_BASE      + 0x00000099)
#define PMIO_PBS3_CORE_TRIG_STATUS1_OFFS                                              0x00000099
#define PMIO_PBS3_CORE_TRIG_STATUS1_RMSK                                                    0x7f
#define PMIO_PBS3_CORE_TRIG_STATUS1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS1_ADDR, PMIO_PBS3_CORE_TRIG_STATUS1_RMSK, 0, val)
#define PMIO_PBS3_CORE_TRIG_STATUS1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_STATUS1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS1_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_STATUS1_LAST_TRIG_NORMAL_BMSK                                   0x7f
#define PMIO_PBS3_CORE_TRIG_STATUS1_LAST_TRIG_NORMAL_SHFT                                    0x0

#define PMIO_PBS3_CORE_TRIG_STATUS2_ADDR                                              (PBS3_CORE_BASE      + 0x0000009a)
#define PMIO_PBS3_CORE_TRIG_STATUS2_OFFS                                              0x0000009a
#define PMIO_PBS3_CORE_TRIG_STATUS2_RMSK                                                    0x7f
#define PMIO_PBS3_CORE_TRIG_STATUS2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS2_ADDR, PMIO_PBS3_CORE_TRIG_STATUS2_RMSK, 0, val)
#define PMIO_PBS3_CORE_TRIG_STATUS2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_STATUS2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS2_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_STATUS2_TRIG_IN_SERVICE_BMSK                                    0x7f
#define PMIO_PBS3_CORE_TRIG_STATUS2_TRIG_IN_SERVICE_SHFT                                     0x0

#define PMIO_PBS3_CORE_TRIG_STATUS3_ADDR                                              (PBS3_CORE_BASE      + 0x0000009b)
#define PMIO_PBS3_CORE_TRIG_STATUS3_OFFS                                              0x0000009b
#define PMIO_PBS3_CORE_TRIG_STATUS3_RMSK                                                    0x7f
#define PMIO_PBS3_CORE_TRIG_STATUS3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS3_ADDR, PMIO_PBS3_CORE_TRIG_STATUS3_RMSK, 0, val)
#define PMIO_PBS3_CORE_TRIG_STATUS3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS3_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_STATUS3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS3_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_STATUS3_LAST_TRIG_ERROR_BMSK                                    0x7f
#define PMIO_PBS3_CORE_TRIG_STATUS3_LAST_TRIG_ERROR_SHFT                                     0x0

#define PMIO_PBS3_CORE_TRIG_STATUS4_ADDR                                              (PBS3_CORE_BASE      + 0x0000009c)
#define PMIO_PBS3_CORE_TRIG_STATUS4_OFFS                                              0x0000009c
#define PMIO_PBS3_CORE_TRIG_STATUS4_RMSK                                                    0x7f
#define PMIO_PBS3_CORE_TRIG_STATUS4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS4_ADDR, PMIO_PBS3_CORE_TRIG_STATUS4_RMSK, 0, val)
#define PMIO_PBS3_CORE_TRIG_STATUS4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS4_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TRIG_STATUS4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TRIG_STATUS4_ADDR, val, len)
#define PMIO_PBS3_CORE_TRIG_STATUS4_LAST_TRIG_ABORTED_BMSK                                  0x7f
#define PMIO_PBS3_CORE_TRIG_STATUS4_LAST_TRIG_ABORTED_SHFT                                   0x0

#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_ADDR                                       (PBS3_CORE_BASE      + 0x0000009f)
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_OFFS                                       0x0000009f
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_RMSK                                             0xff
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_EOS_NOT_EMPTY_ERROR_BMSK                0x80
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_EOS_NOT_EMPTY_ERROR_SHFT                 0x7
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_OVERFLOW_ERROR_BMSK                     0x40
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_OVERFLOW_ERROR_SHFT                      0x6
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_UNDERFLOW_ERROR_BMSK                    0x20
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_RA_STACK_UNDERFLOW_ERROR_SHFT                     0x5
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_SPMI_ERROR_BMSK                                  0x10
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_SPMI_ERROR_SHFT                                   0x4
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_LSID_ERROR_BMSK                                   0x8
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_LSID_ERROR_SHFT                                   0x3
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_SPECIAL_USID_ERROR_BMSK                           0x4
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_SPECIAL_USID_ERROR_SHFT                           0x2
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_USID_ERROR_BMSK                                   0x2
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_USID_ERROR_SHFT                                   0x1
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_INVALID_CMD_ERROR_BMSK                            0x1
#define PMIO_PBS3_CORE_SEQ_ERR_TYPE_STATUS_INVALID_CMD_ERROR_SHFT                            0x0

#define PMIO_PBS3_CORE_RAM_CFG1_ADDR                                                  (PBS3_CORE_BASE      + 0x000000a0)
#define PMIO_PBS3_CORE_RAM_CFG1_OFFS                                                  0x000000a0
#define PMIO_PBS3_CORE_RAM_CFG1_RMSK                                                        0xff
#define PMIO_PBS3_CORE_RAM_CFG1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_RAM_CFG1_ADDR, PMIO_PBS3_CORE_RAM_CFG1_RMSK, 0, val)
#define PMIO_PBS3_CORE_RAM_CFG1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_RAM_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_RAM_CFG1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_RAM_CFG1_ADDR, val, len)
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_BMSK                                                   0xff
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_SHFT                                                    0x0
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_NO_RAM_FVAL                                             0x0
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_SIZE_32X32_FVAL                                         0x1
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_SIZE_64X32_FVAL                                         0x2
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_SIZE_96X32_FVAL                                         0x3
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_SIZE_128X32_FVAL                                        0x4
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_SIZE_160X32_FVAL                                        0x5
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_SIZE_192X32_FVAL                                        0x6
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_SIZE_224X32_FVAL                                        0x7
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_SIZE_256X32_FVAL                                        0x8
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_SIZE_512X32_FVAL                                       0x10
#define PMIO_PBS3_CORE_RAM_CFG1_SIZE_SIZE_1024X32_FVAL                                      0x20

#define PMIO_PBS3_CORE_RAM_CFG2_ADDR                                                  (PBS3_CORE_BASE      + 0x000000a1)
#define PMIO_PBS3_CORE_RAM_CFG2_OFFS                                                  0x000000a1
#define PMIO_PBS3_CORE_RAM_CFG2_RMSK                                                        0xe0
#define PMIO_PBS3_CORE_RAM_CFG2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_RAM_CFG2_ADDR, PMIO_PBS3_CORE_RAM_CFG2_RMSK, 0, val)
#define PMIO_PBS3_CORE_RAM_CFG2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_RAM_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_RAM_CFG2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_RAM_CFG2_ADDR, val, len)
#define PMIO_PBS3_CORE_RAM_CFG2_MTYPE_BMSK                                                  0xe0
#define PMIO_PBS3_CORE_RAM_CFG2_MTYPE_SHFT                                                   0x5
#define PMIO_PBS3_CORE_RAM_CFG2_MTYPE_RAM18U_FVAL                                            0x0
#define PMIO_PBS3_CORE_RAM_CFG2_MTYPE_RAM65N_FVAL                                            0x1
#define PMIO_PBS3_CORE_RAM_CFG2_MTYPE_RAM15U_FVAL                                            0x2
#define PMIO_PBS3_CORE_RAM_CFG2_MTYPE_RAM22NM_FVAL                                           0x3
#define PMIO_PBS3_CORE_RAM_CFG2_MTYPE_RAM28NM_FVAL                                           0x4

#define PMIO_PBS3_CORE_NVM_CFG1_ADDR                                                  (PBS3_CORE_BASE      + 0x000000a2)
#define PMIO_PBS3_CORE_NVM_CFG1_OFFS                                                  0x000000a2
#define PMIO_PBS3_CORE_NVM_CFG1_RMSK                                                        0xff
#define PMIO_PBS3_CORE_NVM_CFG1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_NVM_CFG1_ADDR, PMIO_PBS3_CORE_NVM_CFG1_RMSK, 0, val)
#define PMIO_PBS3_CORE_NVM_CFG1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_NVM_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_NVM_CFG1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_NVM_CFG1_ADDR, val, len)
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_BMSK                                                   0xff
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_SHFT                                                    0x0
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_NO_OTP_FVAL                                             0x0
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_32_FVAL                                       0x1
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_64_FVAL                                       0x2
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_96_FVAL                                       0x3
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_128_FVAL                                      0x4
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_160_FVAL                                      0x5
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_192_FVAL                                      0x6
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_224_FVAL                                      0x7
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_256_FVAL                                      0x8
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_288_FVAL                                      0x9
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_320_FVAL                                      0xa
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_352_FVAL                                      0xb
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_384_FVAL                                      0xc
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_416_FVAL                                      0xd
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_448_FVAL                                      0xe
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_480_FVAL                                      0xf
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_512_FVAL                                     0x10
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_544_FVAL                                     0x11
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_576_FVAL                                     0x12
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_608_FVAL                                     0x13
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_640_FVAL                                     0x14
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_672_FVAL                                     0x15
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_704_FVAL                                     0x16
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_736_FVAL                                     0x17
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_768_FVAL                                     0x18
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_800_FVAL                                     0x19
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_832_FVAL                                     0x1a
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_864_FVAL                                     0x1b
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_896_FVAL                                     0x1c
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_928_FVAL                                     0x1d
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_960_FVAL                                     0x1e
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_992_FVAL                                     0x1f
#define PMIO_PBS3_CORE_NVM_CFG1_SIZE_ADDRESSES_1024_FVAL                                    0x20

#define PMIO_PBS3_CORE_NVM_CFG2_ADDR                                                  (PBS3_CORE_BASE      + 0x000000a3)
#define PMIO_PBS3_CORE_NVM_CFG2_OFFS                                                  0x000000a3
#define PMIO_PBS3_CORE_NVM_CFG2_RMSK                                                        0xf3
#define PMIO_PBS3_CORE_NVM_CFG2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_NVM_CFG2_ADDR, PMIO_PBS3_CORE_NVM_CFG2_RMSK, 0, val)
#define PMIO_PBS3_CORE_NVM_CFG2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_NVM_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_NVM_CFG2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_NVM_CFG2_ADDR, val, len)
#define PMIO_PBS3_CORE_NVM_CFG2_MTYPE_BMSK                                                  0xe0
#define PMIO_PBS3_CORE_NVM_CFG2_MTYPE_SHFT                                                   0x5
#define PMIO_PBS3_CORE_NVM_CFG2_MTYPE_EMEMORY_FVAL                                           0x0
#define PMIO_PBS3_CORE_NVM_CFG2_MTYPE_KILOPASS_FVAL                                          0x1
#define PMIO_PBS3_CORE_NVM_CFG2_MTYPE_EMEMORY15UM_FVAL                                       0x2
#define PMIO_PBS3_CORE_NVM_CFG2_MTYPE_KILOPASS22NM_FVAL                                      0x3
#define PMIO_PBS3_CORE_NVM_CFG2_MTYPE_EMEMORY28NM_FVAL                                       0x4
#define PMIO_PBS3_CORE_NVM_CFG2_TYPE_BMSK                                                   0x10
#define PMIO_PBS3_CORE_NVM_CFG2_TYPE_SHFT                                                    0x4
#define PMIO_PBS3_CORE_NVM_CFG2_TYPE_OTP_FVAL                                                0x0
#define PMIO_PBS3_CORE_NVM_CFG2_TYPE_ROM_FVAL                                                0x1
#define PMIO_PBS3_CORE_NVM_CFG2_ACCESS_BMSK                                                  0x3
#define PMIO_PBS3_CORE_NVM_CFG2_ACCESS_SHFT                                                  0x0
#define PMIO_PBS3_CORE_NVM_CFG2_ACCESS_WRITE_1200US_READ_800NS_INSTR_PR_1510NS_FVAL          0x0
#define PMIO_PBS3_CORE_NVM_CFG2_ACCESS_WRITE_600US_READ_400NS_INSTR_PR_940NS_FVAL            0x1
#define PMIO_PBS3_CORE_NVM_CFG2_ACCESS_WRITE_300US_READ_200NS_INSTR_PR_730NS_FVAL            0x2

#define PMIO_PBS3_CORE_PARAM_SETTINGS_ADDR                                            (PBS3_CORE_BASE      + 0x000000a4)
#define PMIO_PBS3_CORE_PARAM_SETTINGS_OFFS                                            0x000000a4
#define PMIO_PBS3_CORE_PARAM_SETTINGS_RMSK                                                  0x8f
#define PMIO_PBS3_CORE_PARAM_SETTINGS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PARAM_SETTINGS_ADDR, PMIO_PBS3_CORE_PARAM_SETTINGS_RMSK, 0, val)
#define PMIO_PBS3_CORE_PARAM_SETTINGS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PARAM_SETTINGS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PARAM_SETTINGS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PARAM_SETTINGS_ADDR, val, len)
#define PMIO_PBS3_CORE_PARAM_SETTINGS_FAST_PBS_BMSK                                         0x80
#define PMIO_PBS3_CORE_PARAM_SETTINGS_FAST_PBS_SHFT                                          0x7
#define PMIO_PBS3_CORE_PARAM_SETTINGS_FAST_PBS_REGULAR_PBS_FVAL                              0x0
#define PMIO_PBS3_CORE_PARAM_SETTINGS_FAST_PBS_FAST_PBS_ON_FVAL                              0x1
#define PMIO_PBS3_CORE_PARAM_SETTINGS_NUM_MACHINE_REGS_BMSK                                  0xf
#define PMIO_PBS3_CORE_PARAM_SETTINGS_NUM_MACHINE_REGS_SHFT                                  0x0

#define PMIO_PBS3_CORE_RAM_CFG3_ADDR                                                  (PBS3_CORE_BASE      + 0x000000a6)
#define PMIO_PBS3_CORE_RAM_CFG3_OFFS                                                  0x000000a6
#define PMIO_PBS3_CORE_RAM_CFG3_RMSK                                                        0xff
#define PMIO_PBS3_CORE_RAM_CFG3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_RAM_CFG3_ADDR, PMIO_PBS3_CORE_RAM_CFG3_RMSK, 0, val)
#define PMIO_PBS3_CORE_RAM_CFG3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_RAM_CFG3_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_RAM_CFG3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_RAM_CFG3_ADDR, val, len)
#define PMIO_PBS3_CORE_RAM_CFG3_SIZE_MSB_BMSK                                               0xff
#define PMIO_PBS3_CORE_RAM_CFG3_SIZE_MSB_SHFT                                                0x0

#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_ADDR                                       (PBS3_CORE_BASE      + 0x000000aa)
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_OFFS                                       0x000000aa
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_RMSK                                             0xff
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_RMSK, 0, val)
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, val, len)
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, val)
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_ADDR, val, len)
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_BMSK                                0x80
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_SHFT                                 0x7
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_SLEEP_FVAL                           0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_3_ACTIVE_FVAL                          0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_BMSK                                0x40
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_SHFT                                 0x6
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_SLEEP_FVAL                           0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_2_ACTIVE_FVAL                          0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_BMSK                                0x20
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_SHFT                                 0x5
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_SLEEP_FVAL                           0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_1_ACTIVE_FVAL                          0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_BMSK                                0x10
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_SHFT                                 0x4
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_SLEEP_FVAL                           0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_NRET_N_0_ACTIVE_FVAL                          0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_BMSK                                  0x8
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_SHFT                                  0x3
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_SLEEP_FVAL                            0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_3_ACTIVE_FVAL                           0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_BMSK                                  0x4
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_SHFT                                  0x2
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_SLEEP_FVAL                            0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_2_ACTIVE_FVAL                           0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_BMSK                                  0x2
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_SHFT                                  0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_SLEEP_FVAL                            0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_1_ACTIVE_FVAL                           0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_BMSK                                  0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_SHFT                                  0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_SLEEP_FVAL                            0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_CTL_SLP_RET_N_0_ACTIVE_FVAL                           0x1

#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR                                    (PBS3_CORE_BASE      + 0x000000ab)
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_OFFS                                    0x000000ab
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_RMSK                                          0xff
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR, PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_BMSK                        0x80
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_SHFT                         0x7
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_SLEEP_FVAL                   0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_3_ACTIVE_FVAL                  0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_BMSK                        0x40
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_SHFT                         0x6
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_SLEEP_FVAL                   0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_2_ACTIVE_FVAL                  0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_BMSK                        0x20
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_SHFT                         0x5
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_SLEEP_FVAL                   0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_1_ACTIVE_FVAL                  0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_BMSK                        0x10
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_SHFT                         0x4
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_SLEEP_FVAL                   0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_NRET_STATUS_0_ACTIVE_FVAL                  0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_BMSK                          0x8
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_SHFT                          0x3
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_SLEEP_FVAL                    0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_3_ACTIVE_FVAL                   0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_BMSK                          0x4
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_SHFT                          0x2
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_SLEEP_FVAL                    0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_2_ACTIVE_FVAL                   0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_BMSK                          0x2
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_SHFT                          0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_SLEEP_FVAL                    0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_1_ACTIVE_FVAL                   0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_BMSK                          0x1
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_SHFT                          0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_SLEEP_FVAL                    0x0
#define PMIO_PBS3_CORE_PMIC7_RAM_SLEEP_STATUS_SLP_RET_STATUS_0_ACTIVE_FVAL                   0x1

#define PMIO_PBS3_CORE_PMIC7_RAM_ACC_ADDR                                             (PBS3_CORE_BASE      + 0x000000ac)
#define PMIO_PBS3_CORE_PMIC7_RAM_ACC_OFFS                                             0x000000ac
#define PMIO_PBS3_CORE_PMIC7_RAM_ACC_RMSK                                                    0xf
#define PMIO_PBS3_CORE_PMIC7_RAM_ACC_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_ACC_ADDR, PMIO_PBS3_CORE_PMIC7_RAM_ACC_RMSK, 0, val)
#define PMIO_PBS3_CORE_PMIC7_RAM_ACC_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_ACC_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PMIC7_RAM_ACC_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_ACC_ADDR, val, len)
#define PMIO_PBS3_CORE_PMIC7_RAM_ACC_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_ACC_ADDR, val)
#define PMIO_PBS3_CORE_PMIC7_RAM_ACC_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_ACC_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PMIC7_RAM_ACC_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PMIC7_RAM_ACC_ADDR, val, len)
#define PMIO_PBS3_CORE_PMIC7_RAM_ACC_ACC_BMSK                                                0xf
#define PMIO_PBS3_CORE_PMIC7_RAM_ACC_ACC_SHFT                                                0x0

#define PMIO_PBS3_CORE_PBS_CLK_CTL_n_ADDR(n)                                          (PBS3_CORE_BASE      + (0x000000ad + 0x1 * (n)))
#define PMIO_PBS3_CORE_PBS_CLK_CTL_n_OFFS(n)                                          (0x000000ad + 0x1 * (n))
#define PMIO_PBS3_CORE_PBS_CLK_CTL_n_RMSK                                                    0x1
#define PMIO_PBS3_CORE_PBS_CLK_CTL_n_INI(ctxt, pmic, n, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_CLK_CTL_n_ADDR(n), PMIO_PBS3_CORE_PBS_CLK_CTL_n_RMSK, 0, val)
#define PMIO_PBS3_CORE_PBS_CLK_CTL_n_INFI(ctxt, pmic, n, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_CLK_CTL_n_ADDR(n), mask, shift, val)
#define PMIO_PBS3_CORE_PBS_CLK_CTL_n_INNI(ctxt, pmic, n, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PBS_CLK_CTL_n_ADDR(n), val, len)
#define PMIO_PBS3_CORE_PBS_CLK_CTL_n_OUTI(ctxt, pmic, n, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PBS_CLK_CTL_n_ADDR(n), val)
#define PMIO_PBS3_CORE_PBS_CLK_CTL_n_OUTFI(ctxt, pmic, n, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PBS_CLK_CTL_n_ADDR(n), mask, shift, val)
#define PMIO_PBS3_CORE_PBS_CLK_CTL_n_OUTNI(ctxt, pmic, n, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PBS_CLK_CTL_n_ADDR(n), val, len)
#define PMIO_PBS3_CORE_PBS_CLK_CTL_n_PBS_CLK_GATE_EN_BMSK                                    0x1
#define PMIO_PBS3_CORE_PBS_CLK_CTL_n_PBS_CLK_GATE_EN_SHFT                                    0x0

#define PMIO_PBS3_CORE_SEQ_R0_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000b0)
#define PMIO_PBS3_CORE_SEQ_R0_STATUS_OFFS                                             0x000000b0
#define PMIO_PBS3_CORE_SEQ_R0_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_R0_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R0_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_R0_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_R0_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R0_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_R0_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R0_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_R0_STATUS_R0_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_R0_STATUS_R0_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_R1_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000b1)
#define PMIO_PBS3_CORE_SEQ_R1_STATUS_OFFS                                             0x000000b1
#define PMIO_PBS3_CORE_SEQ_R1_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_R1_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R1_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_R1_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_R1_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R1_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_R1_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R1_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_R1_STATUS_R1_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_R1_STATUS_R1_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_R2_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000b2)
#define PMIO_PBS3_CORE_SEQ_R2_STATUS_OFFS                                             0x000000b2
#define PMIO_PBS3_CORE_SEQ_R2_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_R2_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R2_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_R2_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_R2_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R2_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_R2_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R2_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_R2_STATUS_R2_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_R2_STATUS_R2_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_R3_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000b3)
#define PMIO_PBS3_CORE_SEQ_R3_STATUS_OFFS                                             0x000000b3
#define PMIO_PBS3_CORE_SEQ_R3_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_R3_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R3_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_R3_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_R3_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R3_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_R3_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R3_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_R3_STATUS_R3_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_R3_STATUS_R3_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_R4_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000b4)
#define PMIO_PBS3_CORE_SEQ_R4_STATUS_OFFS                                             0x000000b4
#define PMIO_PBS3_CORE_SEQ_R4_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_R4_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R4_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_R4_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_R4_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R4_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_R4_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R4_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_R4_STATUS_R4_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_R4_STATUS_R4_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_R5_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000b5)
#define PMIO_PBS3_CORE_SEQ_R5_STATUS_OFFS                                             0x000000b5
#define PMIO_PBS3_CORE_SEQ_R5_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_R5_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R5_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_R5_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_R5_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R5_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_R5_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R5_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_R5_STATUS_R5_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_R5_STATUS_R5_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_R6_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000b6)
#define PMIO_PBS3_CORE_SEQ_R6_STATUS_OFFS                                             0x000000b6
#define PMIO_PBS3_CORE_SEQ_R6_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_R6_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R6_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_R6_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_R6_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R6_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_R6_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R6_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_R6_STATUS_R6_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_R6_STATUS_R6_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_R7_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000b7)
#define PMIO_PBS3_CORE_SEQ_R7_STATUS_OFFS                                             0x000000b7
#define PMIO_PBS3_CORE_SEQ_R7_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_R7_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R7_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_R7_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_R7_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R7_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_R7_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R7_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_R7_STATUS_R7_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_R7_STATUS_R7_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_R8_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000b8)
#define PMIO_PBS3_CORE_SEQ_R8_STATUS_OFFS                                             0x000000b8
#define PMIO_PBS3_CORE_SEQ_R8_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_R8_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R8_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_R8_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_R8_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R8_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_R8_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R8_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_R8_STATUS_R8_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_R8_STATUS_R8_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_R9_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000b9)
#define PMIO_PBS3_CORE_SEQ_R9_STATUS_OFFS                                             0x000000b9
#define PMIO_PBS3_CORE_SEQ_R9_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_R9_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R9_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_R9_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_R9_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R9_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_R9_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_R9_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_R9_STATUS_R9_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_R9_STATUS_R9_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_RA_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000ba)
#define PMIO_PBS3_CORE_SEQ_RA_STATUS_OFFS                                             0x000000ba
#define PMIO_PBS3_CORE_SEQ_RA_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_RA_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RA_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_RA_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_RA_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RA_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_RA_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RA_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_RA_STATUS_RA_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_RA_STATUS_RA_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_RB_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000bb)
#define PMIO_PBS3_CORE_SEQ_RB_STATUS_OFFS                                             0x000000bb
#define PMIO_PBS3_CORE_SEQ_RB_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_RB_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RB_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_RB_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_RB_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RB_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_RB_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RB_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_RB_STATUS_RB_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_RB_STATUS_RB_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_RC_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000bc)
#define PMIO_PBS3_CORE_SEQ_RC_STATUS_OFFS                                             0x000000bc
#define PMIO_PBS3_CORE_SEQ_RC_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_RC_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RC_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_RC_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_RC_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RC_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_RC_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RC_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_RC_STATUS_RC_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_RC_STATUS_RC_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_RD_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000bd)
#define PMIO_PBS3_CORE_SEQ_RD_STATUS_OFFS                                             0x000000bd
#define PMIO_PBS3_CORE_SEQ_RD_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_RD_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RD_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_RD_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_RD_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RD_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_RD_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RD_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_RD_STATUS_RD_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_RD_STATUS_RD_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_RE_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000be)
#define PMIO_PBS3_CORE_SEQ_RE_STATUS_OFFS                                             0x000000be
#define PMIO_PBS3_CORE_SEQ_RE_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_RE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RE_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_RE_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_RE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_RE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RE_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_RE_STATUS_RE_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_RE_STATUS_RE_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_SEQ_RF_STATUS_ADDR                                             (PBS3_CORE_BASE      + 0x000000bf)
#define PMIO_PBS3_CORE_SEQ_RF_STATUS_OFFS                                             0x000000bf
#define PMIO_PBS3_CORE_SEQ_RF_STATUS_RMSK                                                   0xff
#define PMIO_PBS3_CORE_SEQ_RF_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RF_STATUS_ADDR, PMIO_PBS3_CORE_SEQ_RF_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_RF_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RF_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_RF_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_RF_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_RF_STATUS_RF_STATUS_BMSK                                         0xff
#define PMIO_PBS3_CORE_SEQ_RF_STATUS_RF_STATUS_SHFT                                          0x0

#define PMIO_PBS3_CORE_LOCKBIT_D1_ADDR                                                (PBS3_CORE_BASE      + 0x000000d1)
#define PMIO_PBS3_CORE_LOCKBIT_D1_OFFS                                                0x000000d1
#define PMIO_PBS3_CORE_LOCKBIT_D1_RMSK                                                       0x3
#define PMIO_PBS3_CORE_LOCKBIT_D1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_LOCKBIT_D1_ADDR, PMIO_PBS3_CORE_LOCKBIT_D1_RMSK, 0, val)
#define PMIO_PBS3_CORE_LOCKBIT_D1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_LOCKBIT_D1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_LOCKBIT_D1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_LOCKBIT_D1_ADDR, val, len)
#define PMIO_PBS3_CORE_LOCKBIT_D1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_LOCKBIT_D1_ADDR, val)
#define PMIO_PBS3_CORE_LOCKBIT_D1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_LOCKBIT_D1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_LOCKBIT_D1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_LOCKBIT_D1_ADDR, val, len)
#define PMIO_PBS3_CORE_LOCKBIT_D1_LOCKBIT_D1_BMSK                                            0x3
#define PMIO_PBS3_CORE_LOCKBIT_D1_LOCKBIT_D1_SHFT                                            0x0
#define PMIO_PBS3_CORE_LOCKBIT_D1_LOCKBIT_D1_OPEN_FVAL                                       0x0
#define PMIO_PBS3_CORE_LOCKBIT_D1_LOCKBIT_D1_RSVD_FVAL                                       0x1
#define PMIO_PBS3_CORE_LOCKBIT_D1_LOCKBIT_D1_LOCKED_OPEN_FVAL                                0x2
#define PMIO_PBS3_CORE_LOCKBIT_D1_LOCKBIT_D1_LOCKED_CLOSED_FVAL                              0x3

#define PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_ADDR                                      (PBS3_CORE_BASE      + 0x000000d4)
#define PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_OFFS                                      0x000000d4
#define PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_RMSK                                             0x1
#define PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_ADDR, PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_RMSK, 0, val)
#define PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_ADDR, val)
#define PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_ADDR, val, len)
#define PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_LOCKBIT_D1_BMSK                                  0x1
#define PMIO_PBS3_CORE_ILLEGAL_WRITE_STATUS_LOCKBIT_D1_SHFT                                  0x0

#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_ADDR                                          (PBS3_CORE_BASE      + 0x000000d9)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_OFFS                                          0x000000d9
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_RMSK                                                 0x1
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL2_ADDR, PMIO_PBS3_CORE_PERPH_RESET_CTL2_RMSK, 0, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL2_ADDR, val, len)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL2_ADDR, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL2_ADDR, val, len)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_BMSK                           0x1
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_SHFT                           0x0
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_RESET_IGNORED_FVAL             0x0
#define PMIO_PBS3_CORE_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_RESET_ARMED_FVAL               0x1

#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_ADDR                                          (PBS3_CORE_BASE      + 0x000000da)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_OFFS                                          0x000000da
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_RMSK                                                 0x7
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL3_ADDR, PMIO_PBS3_CORE_PERPH_RESET_CTL3_RMSK, 0, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL3_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL3_ADDR, val, len)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL3_ADDR, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL3_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL3_ADDR, val, len)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_BMSK                                  0x4
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_SHFT                                  0x2
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_RESET_IGNORED_FVAL                    0x0
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_WARM_RB_RESET_ARMED_FVAL                      0x1
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_BMSK                             0x2
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_SHFT                             0x1
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_RESET_IGNORED_FVAL               0x0
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_RESET_ARMED_FVAL                 0x1
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_BMSK                             0x1
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_SHFT                             0x0
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_RESET_IGNORED_FVAL               0x0
#define PMIO_PBS3_CORE_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_RESET_ARMED_FVAL                 0x1

#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_ADDR                                          (PBS3_CORE_BASE      + 0x000000db)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_OFFS                                          0x000000db
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_RMSK                                                 0x1
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL4_ADDR, PMIO_PBS3_CORE_PERPH_RESET_CTL4_RMSK, 0, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL4_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL4_ADDR, val, len)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL4_ADDR, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL4_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_PERPH_RESET_CTL4_ADDR, val, len)
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_BMSK                                0x1
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_SHFT                                0x0
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_NORMAL_OPERATION_FVAL               0x0
#define PMIO_PBS3_CORE_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_SOFT_RESET_ASSERTED_FVAL            0x1

#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_ADDR                                             (PBS3_CORE_BASE      + 0x000000e0)
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_OFFS                                             0x000000e0
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_RMSK                                                    0x3
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_CFG_ADDR, PMIO_PBS3_CORE_SEQ_DEBUG_CFG_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_CFG_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_CFG_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_CFG_ADDR, val)
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_CFG_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_CFG_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_BMSK                                        0x2
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_SHFT                                        0x1
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_DEBUG_NEXT_CMD_FVAL                         0x0
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_DEBUG_DTEST_DEBUG_NEXT_DTEST_FVAL                       0x1
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_DEBUG_EN_BMSK                                           0x1
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_DEBUG_EN_SHFT                                           0x0
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_DEBUG_EN_DISABLED_FVAL                                  0x0
#define PMIO_PBS3_CORE_SEQ_DEBUG_CFG_DEBUG_EN_ENABLED_FVAL                                   0x1

#define PMIO_PBS3_CORE_SEQ_DEBUG_NEXT_ADDR                                            (PBS3_CORE_BASE      + 0x000000e1)
#define PMIO_PBS3_CORE_SEQ_DEBUG_NEXT_OFFS                                            0x000000e1
#define PMIO_PBS3_CORE_SEQ_DEBUG_NEXT_RMSK                                                   0x1
#define PMIO_PBS3_CORE_SEQ_DEBUG_NEXT_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_NEXT_ADDR, val)
#define PMIO_PBS3_CORE_SEQ_DEBUG_NEXT_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_NEXT_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_BMSK                                          0x1
#define PMIO_PBS3_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_SHFT                                          0x0
#define PMIO_PBS3_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_DEBUG_NEXT_NOP_FVAL                           0x0
#define PMIO_PBS3_CORE_SEQ_DEBUG_NEXT_NEXT_CMD_DEBUG_NEXT_TRIGGER_FVAL                       0x1

#define PMIO_PBS3_CORE_OTP_CFG1_ADDR                                                  (PBS3_CORE_BASE      + 0x000000e2)
#define PMIO_PBS3_CORE_OTP_CFG1_OFFS                                                  0x000000e2
#define PMIO_PBS3_CORE_OTP_CFG1_RMSK                                                         0xf
#define PMIO_PBS3_CORE_OTP_CFG1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG1_ADDR, PMIO_PBS3_CORE_OTP_CFG1_RMSK, 0, val)
#define PMIO_PBS3_CORE_OTP_CFG1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_OTP_CFG1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG1_ADDR, val, len)
#define PMIO_PBS3_CORE_OTP_CFG1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG1_ADDR, val)
#define PMIO_PBS3_CORE_OTP_CFG1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_OTP_CFG1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG1_ADDR, val, len)
#define PMIO_PBS3_CORE_OTP_CFG1_VPP_SEL_BMSK                                                 0x8
#define PMIO_PBS3_CORE_OTP_CFG1_VPP_SEL_SHFT                                                 0x3
#define PMIO_PBS3_CORE_OTP_CFG1_VPP_SEL_DVDD_FVAL                                            0x0
#define PMIO_PBS3_CORE_OTP_CFG1_VPP_SEL_VPP_EXT_FVAL                                         0x1
#define PMIO_PBS3_CORE_OTP_CFG1_PPROG_BMSK                                                   0x4
#define PMIO_PBS3_CORE_OTP_CFG1_PPROG_SHFT                                                   0x2
#define PMIO_PBS3_CORE_OTP_CFG1_PPROG_OTP_PROGRAMMING_DISABLED_FVAL                          0x0
#define PMIO_PBS3_CORE_OTP_CFG1_PPROG_OTP_PROGRAMMING_ENABLED_FVAL                           0x1
#define PMIO_PBS3_CORE_OTP_CFG1_PTM_BMSK                                                     0x3
#define PMIO_PBS3_CORE_OTP_CFG1_PTM_SHFT                                                     0x0
#define PMIO_PBS3_CORE_OTP_CFG1_PTM_REGULAR_MODES_FVAL                                       0x0
#define PMIO_PBS3_CORE_OTP_CFG1_PTM_RESERVED_FVAL                                            0x1
#define PMIO_PBS3_CORE_OTP_CFG1_PTM_MARGIN_1_READ_MODE_FVAL                                  0x2
#define PMIO_PBS3_CORE_OTP_CFG1_PTM_MARGIN_2_READ_MODE_FVAL                                  0x3

#define PMIO_PBS3_CORE_OTP_CFG2_ADDR                                                  (PBS3_CORE_BASE      + 0x000000e3)
#define PMIO_PBS3_CORE_OTP_CFG2_OFFS                                                  0x000000e3
#define PMIO_PBS3_CORE_OTP_CFG2_RMSK                                                        0x1f
#define PMIO_PBS3_CORE_OTP_CFG2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG2_ADDR, PMIO_PBS3_CORE_OTP_CFG2_RMSK, 0, val)
#define PMIO_PBS3_CORE_OTP_CFG2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_OTP_CFG2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG2_ADDR, val, len)
#define PMIO_PBS3_CORE_OTP_CFG2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG2_ADDR, val)
#define PMIO_PBS3_CORE_OTP_CFG2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG2_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_OTP_CFG2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_OTP_CFG2_ADDR, val, len)
#define PMIO_PBS3_CORE_OTP_CFG2_MARGIN_RD_WS_BMSK                                           0x1f
#define PMIO_PBS3_CORE_OTP_CFG2_MARGIN_RD_WS_SHFT                                            0x0

#define PMIO_PBS3_CORE_TEST1_ADDR                                                     (PBS3_CORE_BASE      + 0x000000e4)
#define PMIO_PBS3_CORE_TEST1_OFFS                                                     0x000000e4
#define PMIO_PBS3_CORE_TEST1_RMSK                                                           0xff
#define PMIO_PBS3_CORE_TEST1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TEST1_ADDR, PMIO_PBS3_CORE_TEST1_RMSK, 0, val)
#define PMIO_PBS3_CORE_TEST1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TEST1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TEST1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_TEST1_ADDR, val, len)
#define PMIO_PBS3_CORE_TEST1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_TEST1_ADDR, val)
#define PMIO_PBS3_CORE_TEST1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_TEST1_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_TEST1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_TEST1_ADDR, val, len)
#define PMIO_PBS3_CORE_TEST1_DTEST4_EN_BMSK                                                 0x80
#define PMIO_PBS3_CORE_TEST1_DTEST4_EN_SHFT                                                  0x7
#define PMIO_PBS3_CORE_TEST1_DTEST4_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS3_CORE_TEST1_DTEST4_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS3_CORE_TEST1_DTEST3_EN_BMSK                                                 0x40
#define PMIO_PBS3_CORE_TEST1_DTEST3_EN_SHFT                                                  0x6
#define PMIO_PBS3_CORE_TEST1_DTEST3_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS3_CORE_TEST1_DTEST3_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS3_CORE_TEST1_DTEST2_EN_BMSK                                                 0x20
#define PMIO_PBS3_CORE_TEST1_DTEST2_EN_SHFT                                                  0x5
#define PMIO_PBS3_CORE_TEST1_DTEST2_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS3_CORE_TEST1_DTEST2_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS3_CORE_TEST1_DTEST1_EN_BMSK                                                 0x10
#define PMIO_PBS3_CORE_TEST1_DTEST1_EN_SHFT                                                  0x4
#define PMIO_PBS3_CORE_TEST1_DTEST1_EN_DISABLED_FVAL                                         0x0
#define PMIO_PBS3_CORE_TEST1_DTEST1_EN_ENABLED_FVAL                                          0x1
#define PMIO_PBS3_CORE_TEST1_DTEST_SEL_BMSK                                                  0xf
#define PMIO_PBS3_CORE_TEST1_DTEST_SEL_SHFT                                                  0x0

#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_ADDR                                           (PBS3_CORE_BASE      + 0x000000e5)
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_OFFS                                           0x000000e5
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_RMSK                                                  0x7
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_ADDR, PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_ADDR, val)
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_BMSK                                  0x7
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_SHFT                                  0x0
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST1_FVAL                           0x0
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST2_FVAL                           0x1
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST3_FVAL                           0x2
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST4_FVAL                           0x3
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST5_FVAL                           0x4
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST6_FVAL                           0x5
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST7_FVAL                           0x6
#define PMIO_PBS3_CORE_SEQ_DEBUG_DTEST_DEBUG_DTEST_SEL_DTEST8_FVAL                           0x7

#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_ADDR                                        (PBS3_CORE_BASE      + 0x000000ec)
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_OFFS                                        0x000000ec
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_RMSK                                               0x1
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_ADDR, PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_ADDR, val)
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_BP_EN_BMSK                                         0x1
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_BP_EN_SHFT                                         0x0
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_BP_EN_DISABLED_FVAL                                0x0
#define PMIO_PBS3_CORE_SEQ_BREAKPOINT_CFG_BP_EN_ENABLED_FVAL                                 0x1

#define PMIO_PBS3_CORE_SEQ_BP_CTL_ADDR                                                (PBS3_CORE_BASE      + 0x000000ed)
#define PMIO_PBS3_CORE_SEQ_BP_CTL_OFFS                                                0x000000ed
#define PMIO_PBS3_CORE_SEQ_BP_CTL_RMSK                                                       0x1
#define PMIO_PBS3_CORE_SEQ_BP_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_CTL_ADDR, val)
#define PMIO_PBS3_CORE_SEQ_BP_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_CTL_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_BP_CTL_BP_CONTINUE_BMSK                                           0x1
#define PMIO_PBS3_CORE_SEQ_BP_CTL_BP_CONTINUE_SHFT                                           0x0
#define PMIO_PBS3_CORE_SEQ_BP_CTL_BP_CONTINUE_DEBUG_NEXT_NOP_FVAL                            0x0
#define PMIO_PBS3_CORE_SEQ_BP_CTL_BP_CONTINUE_DEBUG_NEXT_TRIGGER_FVAL                        0x1

#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_ADDR                                           (PBS3_CORE_BASE      + 0x000000ee)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_OFFS                                           0x000000ee
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_RMSK                                                 0xff
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_ADDR, PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_ADDR, val)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_BMSK                                     0xff
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_SHFT                                      0x0
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_DEBUG_NEXT_NOP_FVAL                       0x0
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_LSB_BP_ADDR_LSB_DEBUG_NEXT_TRIGGER_FVAL                   0x1

#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_ADDR                                           (PBS3_CORE_BASE      + 0x000000ef)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_OFFS                                           0x000000ef
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_RMSK                                                 0xff
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_ADDR, PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_RMSK, 0, val)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_ADDR, val)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_ADDR, mask, shift, val)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_ADDR, val, len)
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_BMSK                                     0xff
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_SHFT                                      0x0
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_DEBUG_NEXT_NOP_FVAL                       0x0
#define PMIO_PBS3_CORE_SEQ_BP_ADDR_MSB_BP_ADDR_MSB_DEBUG_NEXT_TRIGGER_FVAL                   0x1


#endif /* __PMIO_PBS_CORE_H__ */
