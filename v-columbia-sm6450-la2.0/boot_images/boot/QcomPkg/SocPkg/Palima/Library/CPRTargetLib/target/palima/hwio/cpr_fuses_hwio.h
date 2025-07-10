#ifndef __CPR_FUSES_HWIO_H__
#define __CPR_FUSES_HWIO_H__
/*
===========================================================================
*/
/**
    @file cpr_fuses_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8475 (Palima) [palima_v1.0_p3q2r45_MTO]
 
    This file contains HWIO register definitions for the following modules:
        QFPROM_CORR

    'Include' filters applied: QFPROM_CORR_CALIBRATION_ROW[QFPROM_CORR] QFPROM_CORR_PTE_ROW0_MSB[QFPROM_CORR] QFPROM_CORR_PTE_ROW3_LSB[QFPROM_CORR] 

    Generation parameters: 
    { 'filename': 'cpr_fuses_hwio.h',
      'header': '#include "msmhwiobase.h"',
      'module-filter-include': { 'QFPROM_CORR': [ 'QFPROM_CORR_CALIBRATION_ROW',
                                                  'QFPROM_CORR_PTE_ROW0_MSB',
                                                  'QFPROM_CORR_PTE_ROW3_LSB']},
      'modules': ['QFPROM_CORR'],
      'output-attrs': True,
      'output-fvals': True,
      'output-offsets': True}

    Attribute definitions for the HWIO_*_ATTR macros are as follows:
        0x0: Command register
        0x1: Read-Only
        0x2: Write-Only
        0x3: Read/Write
*/
/*
    ===========================================================================

    Copyright (c) 2022 Qualcomm Technologies, Inc.
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

    $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Palima/Library/CPRTargetLib/target/palima/hwio/cpr_fuses_hwio.h#5 $
    $DateTime: 2022/02/15 08:12:37 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: QFPROM_CORR
 *--------------------------------------------------------------------------*/

#define QFPROM_CORR_REG_BASE                                                                               (TMESS_BASE      + 0x021c2000)
#define QFPROM_CORR_REG_BASE_SIZE                                                                          0x2000
#define QFPROM_CORR_REG_BASE_USED                                                                          0x101c
#define QFPROM_CORR_REG_BASE_OFFS                                                                          0x021c2000

/////////////// VPID FUSES
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR                                                          (QFPROM_CORR_REG_BASE      + 0x428)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_OFFS                                                          (QFPROM_CORR_REG_BASE_OFFS + 0x428)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_RMSK                                                          0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ATTR                                                                       0x1
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_QC_SPARE_0_31_8_BMSK                                          0xffffff00
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_QC_SPARE_0_31_8_SHFT                                                   8
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SW_SPT_LOCAL_RAILS_VPID_BMSK                                        0xf0
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SW_SPT_LOCAL_RAILS_VPID_SHFT                                           4
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SW_SPT_GLOBAL_RAILS_VPID_BMSK                                        0xf
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SW_SPT_GLOBAL_RAILS_VPID_SHFT                                          0

/////


#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x1bc)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0x1bc)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_ATTR                                                                              0x1
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_BIN_V_IDENTIFIER_BMSK                                                0xc0000000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_BIN_V_IDENTIFIER_SHFT                                                        30
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_MINOR_REV_BMSK                                                       0x30000000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_MINOR_REV_SHFT                                                               28
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_LOGIC_RETENTION_BMSK                                                  0xe000000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_LOGIC_RETENTION_SHFT                                                         25
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_REVISION_CONTROL_BMSK                                            0x1c00000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_REVISION_CONTROL_SHFT                                                   22
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_PTE_DATA_53_52_BMSK                                                    0x300000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_PTE_DATA_53_52_SHFT                                                          20
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_LPICX_ACTIVE_BMSK                                                  0xff000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_LPICX_ACTIVE_SHFT                                                       12
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_CX_ACTIVE_BMSK                                                       0xffc
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_CX_ACTIVE_SHFT                                                           2
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_MULTIPLIER_BMSK                                                        0x3
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_MULTIPLIER_SHFT                                                          0

#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR                                                                 (QFPROM_CORR_REG_BASE      + 0x1d0)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_OFFS                                                                 (QFPROM_CORR_REG_BASE_OFFS + 0x1d0)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_ATTR                                                                              0x1
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_223_221_BMSK                                                0xe0000000
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_223_221_SHFT                                                        29
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_WAFER_ID_BMSK                                                        0x1f000000
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_WAFER_ID_SHFT                                                                24
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_X_BMSK                                                             0xff0000
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_X_SHFT                                                                   16
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_Y_BMSK                                                               0xff00
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_Y_SHFT                                                                    8
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_MEM_RETENTION_BMSK                                                         0xe0
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_MEM_RETENTION_SHFT                                                            5
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_196_192_BMSK                                                      0x1f
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_196_192_SHFT                                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x888)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x888)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_USB2PHY_RCAL_CODE_0_BMSK                                     0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_USB2PHY_RCAL_CODE_0_SHFT                                             31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_BANDGAP_TRIM_BMSK                                            0x7f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_BANDGAP_TRIM_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_NORTH_2_BGV_TRIM_BMSK                                   0xff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_NORTH_2_BGV_TRIM_SHFT                                         16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_NORTH_BGV_TRIM_BMSK                                       0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_NORTH_BGV_TRIM_SHFT                                            8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_SOUTH_BGV_TRIM_BMSK                                         0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_SOUTH_BGV_TRIM_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x88c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x88c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBRATION_63_51_BMSK                                       0xfff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBRATION_63_51_SHFT                                               19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_DHRY_POWER_TJ_SPEC2_BMSK                                        0x7f800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_DHRY_POWER_TJ_SPEC2_SHFT                                             11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_DHRY_POWER_TJ_SPEC1_BMSK                                          0x7f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_DHRY_POWER_TJ_SPEC1_SHFT                                              3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY_RCAL_CODE_3_1_BMSK                                          0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY_RCAL_CODE_3_1_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x890)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x890)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_64_BMSK                                       0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_64_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x894)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x894)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_127_96_BMSK                                      0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_127_96_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x898)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x898)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_Q6_ACD_DVM_VAL1_7_0_BMSK                                     0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_Q6_ACD_DVM_VAL1_7_0_SHFT                                             24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_Q6_ACD_DVM_VAL0_BMSK                                           0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_Q6_ACD_DVM_VAL0_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x89c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x89c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_Q6_ACD_DVM_VAL2_15_0_BMSK                                    0xffff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_Q6_ACD_DVM_VAL2_15_0_SHFT                                            16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_Q6_ACD_DVM_VAL1_23_8_BMSK                                        0xffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_Q6_ACD_DVM_VAL1_23_8_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8a0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8a0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_Q6_ACD_DVM_VAL3_BMSK                                         0xffffff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_Q6_ACD_DVM_VAL3_SHFT                                                  8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_Q6_ACD_DVM_VAL2_23_16_BMSK                                         0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_Q6_ACD_DVM_VAL2_23_16_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8a4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8a4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_Q6_ACD_DVM_VAL5_7_0_BMSK                                     0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_Q6_ACD_DVM_VAL5_7_0_SHFT                                             24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_Q6_ACD_DVM_VAL4_BMSK                                           0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_Q6_ACD_DVM_VAL4_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8a8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8a8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_Q6_ACD_DVM_VAL6_15_0_BMSK                                    0xffff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_Q6_ACD_DVM_VAL6_15_0_SHFT                                            16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_Q6_ACD_DVM_VAL5_23_8_BMSK                                        0xffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_Q6_ACD_DVM_VAL5_23_8_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8ac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8ac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_VSENSE_FUSE1_S2_1_0_BMSK                                     0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_VSENSE_FUSE1_S2_1_0_SHFT                                             30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_VSENSE_FUSE1_S1_BMSK                                         0x38000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_VSENSE_FUSE1_S1_SHFT                                                 27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_VSENSE_FUSE1_S0_BMSK                                          0x7000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_VSENSE_FUSE1_S0_SHFT                                                 24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_VSENSE_FUSE1_BMSK                                              0xff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_VSENSE_FUSE1_SHFT                                                    16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_Q6_ACD_DVM_ENABLE_BMSK                                           0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_Q6_ACD_DVM_ENABLE_SHFT                                                8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_Q6_ACD_DVM_VAL6_23_16_BMSK                                         0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_Q6_ACD_DVM_VAL6_23_16_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8b0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8b0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE2_S2_0_BMSK                                       0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE2_S2_0_SHFT                                               31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE2_S1_BMSK                                         0x60000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE2_S1_SHFT                                                 29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE2_S0_BMSK                                         0x18000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE2_S0_SHFT                                                 27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE2_BMSK                                             0x7f80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE2_SHFT                                                    19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S8_BMSK                                            0x70000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S8_SHFT                                                 16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S7_BMSK                                             0xe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S7_SHFT                                                 13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S6_BMSK                                             0x1c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S6_SHFT                                                 10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S5_BMSK                                              0x380
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S5_SHFT                                                  7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S4_BMSK                                               0x70
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S4_SHFT                                                  4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S3_BMSK                                                0xe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S3_SHFT                                                  1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S2_2_BMSK                                              0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S2_2_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8b4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8b4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CALIBRATION_383_368_BMSK                                     0xffff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CALIBRATION_383_368_SHFT                                             16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE_REVISION_CONTROL_BMSK                                0xe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE_REVISION_CONTROL_SHFT                                    13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S8_BMSK                                             0x1800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S8_SHFT                                                 11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S7_BMSK                                              0x600
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S7_SHFT                                                  9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S6_BMSK                                              0x180
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S6_SHFT                                                  7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S5_BMSK                                               0x60
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S5_SHFT                                                  5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S4_BMSK                                               0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S4_SHFT                                                  3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S3_BMSK                                                0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S3_SHFT                                                  1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S2_1_BMSK                                              0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S2_1_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8b8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8b8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CALIBRATION_415_384_BMSK                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CALIBRATION_415_384_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8bc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8bc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CALIBRATION_447_416_BMSK                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CALIBRATION_447_416_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8c0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8c0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_TUR_2_0_BMSK                           0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_TUR_2_0_SHFT                                   29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_SUT_BMSK                               0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_OFFSET_SUT_SHFT                                       24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SVS2_BMSK                                       0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SVS2_SHFT                                             18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SVS_BMSK                                         0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SVS_SHFT                                              12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_NOM_BMSK                                           0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_NOM_SHFT                                               6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SUT_BMSK                                            0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR0_TARG_VOLT_SUT_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8c4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8c4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_AGING_4_0_BMSK                                          0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_AGING_4_0_SHFT                                                  27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVS2_BMSK                               0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVS2_SHFT                                      22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVS_BMSK                                 0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVS_SHFT                                       17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVSL1_BMSK                                0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_SVSL1_SHFT                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_NOM_BMSK                                    0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_NOM_SHFT                                        7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_BMSK                                   0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_SHFT                                      2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_TUR_4_3_BMSK                                  0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR0_TARG_VOLT_OFFSET_TUR_4_3_SHFT                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8c8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8c8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_OFFSET_TUR_BMSK                               0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_OFFSET_TUR_SHFT                                       27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_SVS3_BMSK                                      0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_SVS3_SHFT                                             21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_SVS_BMSK                                        0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_SVS_SHFT                                              15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_NOM_BMSK                                          0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_NOM_SHFT                                               9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_TUR_BMSK                                           0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR1_TARG_VOLT_TUR_SHFT                                               3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR0_AGING_7_5_BMSK                                                 0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR0_AGING_7_5_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8cc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8cc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_AGING_1_0_BMSK                                          0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_AGING_1_0_SHFT                                                  30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS3_BMSK                              0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS3_SHFT                                      25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS2_BMSK                               0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS2_SHFT                                      20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS_BMSK                                  0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVS_SHFT                                       15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVSL1_BMSK                                 0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_SVSL1_SHFT                                     10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                    0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                        5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_NOML1_BMSK                                   0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR1_TARG_VOLT_OFFSET_NOML1_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8d0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8d0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SVS3_1_0_BMSK                                 0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SVS3_1_0_SHFT                                         30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SVSL1_BMSK                                    0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SVSL1_SHFT                                            24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_NOM_BMSK                                        0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_NOM_SHFT                                              18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_NOML1_BMSK                                       0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_NOML1_SHFT                                            12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SUT_BMSK                                           0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_TARG_VOLT_SUT_SHFT                                               6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR1_AGING_7_2_BMSK                                                0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR1_AGING_7_2_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR                                                         (QFPROM_CORR_REG_BASE      + 0x8d4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_OFFS                                                         (QFPROM_CORR_REG_BASE_OFFS + 0x8d4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ATTR                                                                      0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_2_0_BMSK                         0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_2_0_SHFT                                 29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_BMSK                             0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_SHFT                                     24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                                 0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                       19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_NOML1_BMSK                                0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_NOML1_SHFT                                     14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_TUR_BMSK                                   0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_TUR_SHFT                                        9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SUT_BMSK                                    0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SUT_SHFT                                        4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_SVS3_5_2_BMSK                                        0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_SVS3_5_2_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8d8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8d8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR3_TARG_VOLT_SVS_0_BMSK                                   0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR3_TARG_VOLT_SVS_0_SHFT                                           31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR3_TARG_VOLT_SUT_BMSK                                     0x7e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR3_TARG_VOLT_SUT_SHFT                                             25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_AGING_BMSK                                              0x1fe0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_AGING_SHFT                                                     17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVS3_BMSK                                0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVS3_SHFT                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVS2_BMSK                                  0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVS2_SHFT                                      7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVS_BMSK                                    0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVS_SHFT                                       2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVSL1_4_3_BMSK                               0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR2_TARG_VOLT_OFFSET_SVSL1_4_3_SHFT                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8dc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8dc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_TUR_2_0_BMSK                                 0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_TUR_2_0_SHFT                                         29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_NOM_BMSK                                     0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_NOM_SHFT                                             23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_NOML1_BMSK                                     0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_NOML1_SHFT                                           17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_SUT_BMSK                                        0x1f800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_SUT_SHFT                                             11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR3_TARG_VOLT_SVS2_BMSK                                         0x7e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR3_TARG_VOLT_SVS2_SHFT                                             5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR3_TARG_VOLT_SVS_5_1_BMSK                                       0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR3_TARG_VOLT_SVS_5_1_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8e0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8e0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_NOML1_2_0_BMSK                               0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_NOML1_2_0_SHFT                                       29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_SUT_BMSK                                     0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_SUT_SHFT                                             23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_TUR_BMSK                                0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_TUR_SHFT                                      18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_NOM_BMSK                                 0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_NOM_SHFT                                      13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_NOML1_BMSK                                0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_NOML1_SHFT                                     8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_SUT_BMSK                                    0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_OFFSET_SUT_SHFT                                       3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_TUR_5_3_BMSK                                        0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR4_TARG_VOLT_TUR_5_3_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8e4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8e4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_TUR_1_0_BMSK                          0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_TUR_1_0_SHFT                                  30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_NOM_BMSK                              0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_NOM_SHFT                                      25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_NOML1_BMSK                             0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_NOML1_SHFT                                    20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_SUT_BMSK                                 0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_SUT_SHFT                                      15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_TUR_BMSK                                         0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_TUR_SHFT                                              9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_NOM_BMSK                                          0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_NOM_SHFT                                              3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_NOML1_5_3_BMSK                                      0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_NOML1_5_3_SHFT                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8e8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8e8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_TUR_4_0_BMSK                                 0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_TUR_4_0_SHFT                                         27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_SVSL1_BMSK                                    0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_SVSL1_SHFT                                           21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_NOM_BMSK                                       0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_NOM_SHFT                                             15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_NOML1_BMSK                                       0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_NOML1_SHFT                                            9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_TUR_BMSK                                          0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR6_TARG_VOLT_TUR_SHFT                                              3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR5_TARG_VOLT_OFFSET_TUR_4_2_BMSK                                 0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR5_TARG_VOLT_OFFSET_TUR_4_2_SHFT                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8ec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8ec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_NOM_2_0_BMSK                          0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_NOM_2_0_SHFT                                  29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_NOML1_BMSK                            0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_NOML1_SHFT                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_TUR_BMSK                                0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_OFFSET_TUR_SHFT                                      19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_SVS3_BMSK                                       0x7e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_SVS3_SHFT                                            13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_SVS_BMSK                                         0x1f80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_SVS_SHFT                                              7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_NOM_BMSK                                           0x7e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_NOM_SHFT                                              1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_TUR_5_BMSK                                          0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_TUR_5_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8f0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8f0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_TUR_1_0_BMSK                                 0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_TUR_1_0_SHFT                                         30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_AGING_BMSK                                             0x3fc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_AGING_SHFT                                                     22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS3_BMSK                               0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS3_SHFT                                     17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS2_BMSK                                0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS2_SHFT                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS_BMSK                                   0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVS_SHFT                                       7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVSL1_BMSK                                  0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_SVSL1_SHFT                                     2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_NOM_4_3_BMSK                                 0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR7_TARG_VOLT_OFFSET_NOM_4_3_SHFT                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8f4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8f4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_NOM_BMSK                              0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_NOM_SHFT                                      27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_TUR_BMSK                               0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_TUR_SHFT                                      22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_SVS2_BMSK                                      0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_SVS2_SHFT                                            16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_SVS_BMSK                                         0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_SVS_SHFT                                             10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_NOM_BMSK                                          0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_NOM_SHFT                                              4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_TUR_5_2_BMSK                                        0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_TUR_5_2_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8f8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8f8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR9_TARG_VOLT_TUR_3_0_BMSK                                 0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR9_TARG_VOLT_TUR_3_0_SHFT                                         28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_AGING_BMSK                                              0xff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_AGING_SHFT                                                     20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVS3_BMSK                                0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVS3_SHFT                                     15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVS2_BMSK                                 0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVS2_SHFT                                     10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVS_BMSK                                   0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVS_SHFT                                       5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVSL1_BMSK                                  0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_TARG_VOLT_OFFSET_SVSL1_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x8fc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x8fc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TURBO_QUOT_MIN_BMSK                                    0xfff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TURBO_QUOT_MIN_SHFT                                            20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_SVS2_BMSK                                       0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_SVS2_SHFT                                            14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_SVS_BMSK                                         0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_SVS_SHFT                                              8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_NOM_BMSK                                           0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_NOM_SHFT                                              2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_TUR_5_4_BMSK                                        0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_TUR_5_4_SHFT                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x900)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x900)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_SVS2_QUOT_MIN_7_0_BMSK                                 0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_SVS2_QUOT_MIN_7_0_SHFT                                         24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_SVS_QUOT_MIN_BMSK                                        0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_SVS_QUOT_MIN_SHFT                                              12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_NOMINAL_QUOT_MIN_BMSK                                       0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_NOMINAL_QUOT_MIN_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x904)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x904)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_NOM_BMSK                                    0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_NOM_SHFT                                            26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_TUR_BMSK                                     0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_TUR_SHFT                                            20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR9_AGING_BMSK                                                0xff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR9_AGING_SHFT                                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR9_QUOT_OFFSET_BMSK                                            0xff0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR9_QUOT_OFFSET_SHFT                                                4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR9_SVS2_QUOT_MIN_11_8_BMSK                                       0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR9_SVS2_QUOT_MIN_11_8_SHFT                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x908)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x908)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_NOMINAL_QUOT_MIN_7_0_BMSK                             0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_NOMINAL_QUOT_MIN_7_0_SHFT                                     24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TURBO_QUOT_MIN_BMSK                                     0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TURBO_QUOT_MIN_SHFT                                           12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TARG_VOLT_SVS2_BMSK                                        0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TARG_VOLT_SVS2_SHFT                                            6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TARG_VOLT_SVS_BMSK                                          0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TARG_VOLT_SVS_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x90c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x90c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_QUOT_OFFSET_3_0_BMSK                                  0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_QUOT_OFFSET_3_0_SHFT                                          28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS2_QUOT_MIN_BMSK                                     0xfff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS2_QUOT_MIN_SHFT                                            16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS_QUOT_MIN_BMSK                                         0xfff0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS_QUOT_MIN_SHFT                                              4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_NOMINAL_QUOT_MIN_11_8_BMSK                                   0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_NOMINAL_QUOT_MIN_11_8_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x910)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x910)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_SVS2_3_0_BMSK                               0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_SVS2_3_0_SHFT                                       28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_SVS_BMSK                                     0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_SVS_SHFT                                            22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_NOM_BMSK                                      0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_NOM_SHFT                                            16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_TUR_BMSK                                        0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_TUR_SHFT                                            10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_BOOST_BMSK                                       0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_BOOST_SHFT                                           4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR10_QUOT_OFFSET_7_4_BMSK                                         0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR10_QUOT_OFFSET_7_4_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x914)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x914)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_NOMINAL_QUOT_MIN_5_0_BMSK                             0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_NOMINAL_QUOT_MIN_5_0_SHFT                                     26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TURBO_QUOT_MIN_BMSK                                    0x3ffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TURBO_QUOT_MIN_SHFT                                           14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_BOOST_QUOT_MIN_BMSK                                       0x3ffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_BOOST_QUOT_MIN_SHFT                                            2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS2_5_4_BMSK                                      0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS2_5_4_SHFT                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x918)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x918)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_QUOT_OFFSET_1_0_BMSK                                  0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_QUOT_OFFSET_1_0_SHFT                                          30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS2_QUOT_MIN_BMSK                                    0x3ffc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS2_QUOT_MIN_SHFT                                            18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS_QUOT_MIN_BMSK                                        0x3ffc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS_QUOT_MIN_SHFT                                              6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_NOMINAL_QUOT_MIN_11_6_BMSK                                  0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_NOMINAL_QUOT_MIN_11_6_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x91c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x91c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_NOM_BMSK                                    0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_NOM_SHFT                                            26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_TUR_BMSK                                     0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_TUR_SHFT                                            20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOST_BMSK                                     0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOST_SHFT                                          14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR11_AGING_BMSK                                                0x3fc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR11_AGING_SHFT                                                     6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR11_QUOT_OFFSET_7_2_BMSK                                        0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR11_QUOT_OFFSET_7_2_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x920)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x920)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TURBO_QUOT_MIN_7_0_BMSK                               0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TURBO_QUOT_MIN_7_0_SHFT                                       24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_BOOST_QUOT_MIN_BMSK                                     0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_BOOST_QUOT_MIN_SHFT                                           12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS2_BMSK                                        0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS2_SHFT                                            6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS_BMSK                                          0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x924)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x924)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_SVS2_QUOT_MIN_3_0_BMSK                                0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_SVS2_QUOT_MIN_3_0_SHFT                                        28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_SVS_QUOT_MIN_BMSK                                      0xfff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_SVS_QUOT_MIN_SHFT                                             16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_NOMINAL_QUOT_MIN_BMSK                                     0xfff0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_NOMINAL_QUOT_MIN_SHFT                                          4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_TURBO_QUOT_MIN_11_8_BMSK                                     0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_TURBO_QUOT_MIN_11_8_SHFT                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x928)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x928)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MXC_MODE_DISABLE_0_BMSK                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MXC_MODE_DISABLE_0_SHFT                                         31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MX_MODE_DISABLE_BMSK                                    0x70000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MX_MODE_DISABLE_SHFT                                            28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_GFX_MODE_DISABLE_BMSK                                    0xe000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_GFX_MODE_DISABLE_SHFT                                           25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MSS_MODE_DISABLE_BMSK                                    0x1c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_MSS_MODE_DISABLE_SHFT                                           22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_CX_MODE_DISABLE_BMSK                                      0x380000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR_CX_MODE_DISABLE_SHFT                                            19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CALIBRATION_1298_1296_BMSK                                     0x70000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CALIBRATION_1298_1296_SHFT                                          16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_QUOT_OFFSET_BMSK                                          0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_QUOT_OFFSET_SHFT                                               8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_SVS2_QUOT_MIN_11_4_BMSK                                     0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_SVS2_QUOT_MIN_11_4_SHFT                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x92c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x92c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CALIBRATION_1343_BMSK                                       0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CALIBRATION_1343_SHFT                                               31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_AON_AGING_BMSK                                              0x7f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_AON_AGING_SHFT                                                      23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_AON_TARG_VOLT_BMSK                                            0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_AON_TARG_VOLT_SHFT                                                  17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_APC1_MODE_DISABLE_BMSK                                     0x1c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_APC1_MODE_DISABLE_SHFT                                          14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_APC0_MODE_DISABLE_BMSK                                      0x3800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_APC0_MODE_DISABLE_SHFT                                          11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MMCX_MODE_DISABLE_BMSK                                       0x700
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MMCX_MODE_DISABLE_SHFT                                           8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_SSCCX_MODE_DISABLE_BMSK                                       0xe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_SSCCX_MODE_DISABLE_SHFT                                          5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPIMX_MODE_DISABLE_BMSK                                       0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPIMX_MODE_DISABLE_SHFT                                          2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MXC_MODE_DISABLE_2_1_BMSK                                      0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MXC_MODE_DISABLE_2_1_SHFT                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x930)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x930)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_BOOSTP_QUOT_MIN_5_0_BMSK                              0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_BOOSTP_QUOT_MIN_5_0_SHFT                                      26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_TARG_VOLT_BOOSTP_BMSK                                  0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_TARG_VOLT_BOOSTP_SHFT                                         20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR11_BOOSTP_QUOT_MIN_BMSK                                     0xfff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR11_BOOSTP_QUOT_MIN_SHFT                                           8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR11_TARG_VOLT_BOOSTP_BMSK                                       0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR11_TARG_VOLT_BOOSTP_SHFT                                          2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CALIBRATION_1345_1344_BMSK                                         0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CALIBRATION_1345_1344_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x934)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x934)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR2_TARG_VOLT_OFFSET_LSVS_D2_2_0_BMSK                      0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR2_TARG_VOLT_OFFSET_LSVS_D2_2_0_SHFT                              29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR2_TARG_VOLT_OFFSET_LSVS_D0_BMSK                          0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR2_TARG_VOLT_OFFSET_LSVS_D0_SHFT                                  24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_GLOBAL_RC_BMSK                                            0xf00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_GLOBAL_RC_SHFT                                                  20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_LOCAL_RC_BMSK                                              0xf0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_LOCAL_RC_SHFT                                                   16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR5_TARG_VOLT_OFFSET_SVSL1_BMSK                                0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR5_TARG_VOLT_OFFSET_SVSL1_SHFT                                    11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR4_TARG_VOLT_OFFSET_SVSL1_BMSK                                 0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR4_TARG_VOLT_OFFSET_SVSL1_SHFT                                     6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR12_BOOSTP_QUOT_MIN_11_6_BMSK                                   0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR12_BOOSTP_QUOT_MIN_11_6_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x938)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x938)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CALIBRATION_1439_1432_BMSK                                  0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CALIBRATION_1439_1432_SHFT                                          24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_APC0_PEAK_THROTTLE_TJ_BMSK                                    0xc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_APC0_PEAK_THROTTLE_TJ_SHFT                                          22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_APC0_PEAK_THROTTLE_FREQ_BMSK                                  0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_APC0_PEAK_THROTTLE_FREQ_SHFT                                        17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR2_TARG_VOLT_OFFSET_LSVS_D5_BMSK                             0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR2_TARG_VOLT_OFFSET_LSVS_D5_SHFT                                  12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR2_TARG_VOLT_OFFSET_LSVS_D4_BMSK                               0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR2_TARG_VOLT_OFFSET_LSVS_D4_SHFT                                   7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR2_TARG_VOLT_OFFSET_LSVS_D3_BMSK                                0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR2_TARG_VOLT_OFFSET_LSVS_D3_SHFT                                   2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR2_TARG_VOLT_OFFSET_LSVS_D2_4_3_BMSK                             0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR2_TARG_VOLT_OFFSET_LSVS_D2_4_3_SHFT                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x93c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x93c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_AOSS_K_5_0_BMSK                                             0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_AOSS_K_5_0_SHFT                                                     26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CALIBRATION_1465_1440_BMSK                                   0x3ffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CALIBRATION_1465_1440_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x940)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x940)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_P1_3_0_BMSK                                            0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_P1_3_0_SHFT                                                    28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_N1_BMSK                                                 0xffffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_N1_SHFT                                                        10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_K_15_6_BMSK                                                 0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_K_15_6_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x944)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x944)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_CALIBRATION_1535_1528_BMSK                                  0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_CALIBRATION_1535_1528_SHFT                                          24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_TDOPCODE_BMSK                                            0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_TDOPCODE_SHFT                                                  19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_RDOPCODE_BMSK                                             0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_RDOPCODE_SHFT                                                  14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_P1_17_4_BMSK                                               0x3fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_P1_17_4_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x948)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x948)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE1_1_0_BMSK                                       0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE1_1_0_SHFT                                               30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE0_BMSK                                           0x3ff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE0_SHFT                                                   20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE1_BMSK                                              0xffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE1_SHFT                                                   10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE0_BMSK                                                0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE0_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x94c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x94c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS4_OFFSET_3_0_BMSK                                      0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS4_OFFSET_3_0_SHFT                                              28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS3_OFFSET_BMSK                                           0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS3_OFFSET_SHFT                                                  23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS2_OFFSET_BMSK                                            0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS2_OFFSET_SHFT                                                  18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_OFFSET_BMSK                                             0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_OFFSET_SHFT                                                  13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS0_OFFSET_BMSK                                              0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS0_OFFSET_SHFT                                                   8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_BASE1_9_2_BMSK                                             0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_BASE1_9_2_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x950)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x950)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS11_OFFSET_0_BMSK                                       0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS11_OFFSET_0_SHFT                                               31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS10_OFFSET_BMSK                                         0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS10_OFFSET_SHFT                                                 26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS9_OFFSET_BMSK                                           0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS9_OFFSET_SHFT                                                  21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS8_OFFSET_BMSK                                            0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS8_OFFSET_SHFT                                                  16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS7_OFFSET_BMSK                                              0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS7_OFFSET_SHFT                                                  11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS6_OFFSET_BMSK                                               0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS6_OFFSET_SHFT                                                   6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS5_OFFSET_BMSK                                                0x3e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS5_OFFSET_SHFT                                                   1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS4_OFFSET_4_BMSK                                               0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS4_OFFSET_4_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x954)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x954)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS17_OFFSET_2_0_BMSK                                     0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS17_OFFSET_2_0_SHFT                                             29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS16_OFFSET_BMSK                                         0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS16_OFFSET_SHFT                                                 24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS15_OFFSET_BMSK                                           0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS15_OFFSET_SHFT                                                 19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS14_OFFSET_BMSK                                            0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS14_OFFSET_SHFT                                                 14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS13_OFFSET_BMSK                                             0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS13_OFFSET_SHFT                                                  9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS12_OFFSET_BMSK                                              0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS12_OFFSET_SHFT                                                  4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS11_OFFSET_4_1_BMSK                                            0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS11_OFFSET_4_1_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x958)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x958)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS23_OFFSET_BMSK                                         0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS23_OFFSET_SHFT                                                 27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS22_OFFSET_BMSK                                          0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS22_OFFSET_SHFT                                                 22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS21_OFFSET_BMSK                                           0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS21_OFFSET_SHFT                                                 17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS20_OFFSET_BMSK                                            0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS20_OFFSET_SHFT                                                 12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS19_OFFSET_BMSK                                              0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS19_OFFSET_SHFT                                                  7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS18_OFFSET_BMSK                                               0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS18_OFFSET_SHFT                                                  2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS17_OFFSET_4_3_BMSK                                            0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS17_OFFSET_4_3_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x95c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x95c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS30_OFFSET_1_0_BMSK                                     0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS30_OFFSET_1_0_SHFT                                             30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS29_OFFSET_BMSK                                         0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS29_OFFSET_SHFT                                                 25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS28_OFFSET_BMSK                                          0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS28_OFFSET_SHFT                                                 20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS27_OFFSET_BMSK                                            0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS27_OFFSET_SHFT                                                 15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS26_OFFSET_BMSK                                             0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS26_OFFSET_SHFT                                                 10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS25_OFFSET_BMSK                                              0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS25_OFFSET_SHFT                                                  5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS24_OFFSET_BMSK                                               0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS24_OFFSET_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x960)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x960)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1759_1739_BMSK                                  0xfffff800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1759_1739_SHFT                                          11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS_CAL_SEL_BMSK                                               0x700
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS_CAL_SEL_SHFT                                                   8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS31_OFFSET_BMSK                                               0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS31_OFFSET_SHFT                                                  3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS30_OFFSET_4_2_BMSK                                            0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS30_OFFSET_4_2_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x964)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x964)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CALIBRATION_1791_1760_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CALIBRATION_1791_1760_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x968)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x968)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_DDR_FUSE_BIG3_3_0_BMSK                                      0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_DDR_FUSE_BIG3_3_0_SHFT                                              28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_DDR_FUSE_BIG2_BMSK                                           0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_DDR_FUSE_BIG2_SHFT                                                  22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_DDR_FUSE_BIG1_BMSK                                            0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_DDR_FUSE_BIG1_SHFT                                                  16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_DACC_COMP_VREF_SEL_FUSE2_BMSK                                   0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_DACC_COMP_VREF_SEL_FUSE2_SHFT                                        8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_DACC_COMP_VREF_SEL_FUSE1_BMSK                                     0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_DACC_COMP_VREF_SEL_FUSE1_SHFT                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x96c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x96c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CALIBRATION_1855_1847_BMSK                                  0xff800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CALIBRATION_1855_1847_SHFT                                          23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_SMALL_3_BMSK                                         0x600000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_SMALL_3_SHFT                                               21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_SMALL_2_BMSK                                         0x180000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_SMALL_2_SHFT                                               19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_SMALL_1_BMSK                                          0x60000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_SMALL_1_SHFT                                               17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_MED_3_BMSK                                            0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_MED_3_SHFT                                                 12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_MED_2_BMSK                                              0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_MED_2_SHFT                                                  7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_MED_1_BMSK                                               0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_MED_1_SHFT                                                  2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_BIG3_5_4_BMSK                                             0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_DDR_FUSE_BIG3_5_4_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x970)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x970)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_NSPRAIL_HMX_WS_1_0_BMSK                          0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_NSPRAIL_HMX_WS_1_0_SHFT                                  30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_NSPRAIL_HVX_WS_BMSK                              0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_NSPRAIL_HVX_WS_SHFT                                      24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU7_WS_BMSK                               0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU7_WS_SHFT                                     18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU6_WS_BMSK                                0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU6_WS_SHFT                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU5_WS_BMSK                                  0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU5_WS_SHFT                                      6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU4_WS_BMSK                                   0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OPAMP_FUSE_CPURAIL_CPU4_WS_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x974)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x974)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ISENSE_FUSE_CURRENT_CPU5_F1_7_0_BMSK                        0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ISENSE_FUSE_CURRENT_CPU5_F1_7_0_SHFT                                24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ISENSE_FUSE_CURRENT_CPU4_F2_BMSK                              0xffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ISENSE_FUSE_CURRENT_CPU4_F2_SHFT                                    14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ISENSE_FUSE_CURRENT_CPU4_F1_BMSK                                0x3ff0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ISENSE_FUSE_CURRENT_CPU4_F1_SHFT                                     4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_NSPRAIL_HMX_WS_5_2_BMSK                                 0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OPAMP_FUSE_NSPRAIL_HMX_WS_5_2_SHFT                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x978)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x978)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU6_F2_BMSK                            0xffc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU6_F2_SHFT                                    22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU6_F1_BMSK                              0x3ff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU6_F1_SHFT                                    12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU5_F2_BMSK                                 0xffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU5_F2_SHFT                                     2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU5_F1_9_8_BMSK                               0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ISENSE_FUSE_CURRENT_CPU5_F1_9_8_SHFT                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x97c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x97c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CALIBRATION_1983_1982_BMSK                                  0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CALIBRATION_1983_1982_SHFT                                          30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_HVX_F1_BMSK                             0x3ff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_HVX_F1_SHFT                                     20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_CPU7_F2_BMSK                               0xffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_CPU7_F2_SHFT                                    10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_CPU7_F1_BMSK                                 0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ISENSE_FUSE_CURRENT_CPU7_F1_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x980)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x980)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_FUSE_CDYN_REVISON_BIT_BMSK                              0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_FUSE_CDYN_REVISON_BIT_SHFT                                      30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_DELTA_BMSK                                 0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_DELTA_SHFT                                         25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_H_LF_BMSK                                   0x1ff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_H_LF_SHFT                                          15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_CURRENT_DELTA_BMSK                                     0x7ff8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_CURRENT_DELTA_SHFT                                          3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_FUSE_RESERVED_2_0_BMSK                                         0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_FUSE_RESERVED_2_0_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x984)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x984)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CALIBRATION_2047_2028_BMSK                                  0xfffff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CALIBRATION_2047_2028_SHFT                                          12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACC_HV_MXC_BMSK                                                  0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACC_HV_MXC_SHFT                                                      6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACC_HV_MXA_BMSK                                                   0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACC_HV_MXA_SHFT                                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x988)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x988)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DQ0_DCC_RDT4_3197_1_0_BMSK                      0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DQ0_DCC_RDT4_3197_1_0_SHFT                              30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DQ0_DCC_IO_DQS_3197_BMSK                        0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DQ0_DCC_IO_DQS_3197_SHFT                                24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DQ0_DCC_IO_WCK_3197_BMSK                          0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DQ0_DCC_IO_WCK_3197_SHFT                                18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DQ0_DCC_CLK_ADJ_3197_BMSK                          0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DQ0_DCC_CLK_ADJ_3197_SHFT                               12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DCC_PLL1__3197_BMSK                                  0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DCC_PLL1__3197_SHFT                                      6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DCC_PLL0_3197_BMSK                                    0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_DDR_CH0_LP5_DCC_PLL0_3197_SHFT                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x98c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x98c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_CA_DCC_IO_CK_3197_3_0_BMSK                      0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_CA_DCC_IO_CK_3197_3_0_SHFT                              28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_DQ1_DCC_RDT4_3197_BMSK                           0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_DQ1_DCC_RDT4_3197_SHFT                                  22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_DQ1_DCC_IO_DQS_3197_BMSK                          0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_DQ1_DCC_IO_DQS_3197_SHFT                                16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_DQ1_DCC_IO_WCK_3197_BMSK                            0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_DQ1_DCC_IO_WCK_3197_SHFT                                10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_3197_BMSK                            0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_DQ1_DCC_CLK_ADJ_3197_SHFT                                4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_DQ0_DCC_RDT4_3197_5_2_BMSK                             0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_DDR_CH0_LP5_DQ0_DCC_RDT4_3197_5_2_SHFT                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x990)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x990)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH1_LP5_DQ0_DCC_IO_DQS_3197_BMSK                        0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH1_LP5_DQ0_DCC_IO_DQS_3197_SHFT                                26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH1_LP5_DQ0_DCC_IO_WCK_3197_BMSK                         0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH1_LP5_DQ0_DCC_IO_WCK_3197_SHFT                                20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH1_LP5_DQ0_DCC_CLK_ADJ_3197_BMSK                          0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH1_LP5_DQ0_DCC_CLK_ADJ_3197_SHFT                               14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH1_LP5_DCC_PLL1_3197_BMSK                                  0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH1_LP5_DCC_PLL1_3197_SHFT                                       8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH1_LP5_DCC_PLL0_3197_BMSK                                    0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH1_LP5_DCC_PLL0_3197_SHFT                                       2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH0_LP5_CA_DCC_IO_CK_3197_5_4_BMSK                             0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_DDR_CH0_LP5_CA_DCC_IO_CK_3197_5_4_SHFT                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x994)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x994)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_CA_DCC_IO_CK_3197_1_0_BMSK                      0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_CA_DCC_IO_CK_3197_1_0_SHFT                              30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_DQ1_DCC_RDT4_3197_BMSK                          0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_DQ1_DCC_RDT4_3197_SHFT                                  24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_DQ1_DCC_IO_DQS_3197_BMSK                          0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_DQ1_DCC_IO_DQS_3197_SHFT                                18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_DQ1_DCC_IO_WCK_3197_BMSK                           0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_DQ1_DCC_IO_WCK_3197_SHFT                                12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_3197_BMSK                            0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_DQ1_DCC_CLK_ADJ_3197_SHFT                                6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_DQ0_DCC_RDT4_3197_BMSK                                0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_DDR_CH1_LP5_DQ0_DCC_RDT4_3197_SHFT                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x998)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x998)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH2_LP5_DQ0_DCC_IO_DQS_3197_3_0_BMSK                    0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH2_LP5_DQ0_DCC_IO_DQS_3197_3_0_SHFT                            28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH2_LP5_DQ0_DCC_IO_WCK_3197_BMSK                         0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH2_LP5_DQ0_DCC_IO_WCK_3197_SHFT                                22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH2_LP5_DQ0_DCC_CLK_ADJ_3197_BMSK                         0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH2_LP5_DQ0_DCC_CLK_ADJ_3197_SHFT                               16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH2_LP5_DCC_PLL1_3197_BMSK                                  0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH2_LP5_DCC_PLL1_3197_SHFT                                      10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH2_LP5_DCC_PLL0_3197_BMSK                                   0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH2_LP5_DCC_PLL0_3197_SHFT                                       4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH1_LP5_CA_DCC_IO_CK_3197_5_2_BMSK                             0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_DDR_CH1_LP5_CA_DCC_IO_CK_3197_5_2_SHFT                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x99c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x99c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ1_DCC_RDT4_3197_BMSK                          0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ1_DCC_RDT4_3197_SHFT                                  26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ1_DCC_IO_DQS_3197_BMSK                         0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ1_DCC_IO_DQS_3197_SHFT                                20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ1_DCC_IO_WCK_3197_BMSK                           0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ1_DCC_IO_WCK_3197_SHFT                                14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ1_DCC_CLK_ADJ_3197_BMSK                           0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ1_DCC_CLK_ADJ_3197_SHFT                                8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ0_DCC_RDT4_3197_BMSK                                0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ0_DCC_RDT4_3197_SHFT                                   2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ0_DCC_IO_DQS_3197_5_4_BMSK                           0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_DDR_CH2_LP5_DQ0_DCC_IO_DQS_3197_5_4_SHFT                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9a0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9a0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH3_LP5_DQ0_DCC_IO_DQS_3197_1_0_BMSK                    0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH3_LP5_DQ0_DCC_IO_DQS_3197_1_0_SHFT                            30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH3_LP5_DQ0_DCC_IO_WCK_3197_BMSK                        0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH3_LP5_DQ0_DCC_IO_WCK_3197_SHFT                                24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH3_LP5_DQ0_DCC_CLK_ADJ_3197_BMSK                         0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH3_LP5_DQ0_DCC_CLK_ADJ_3197_SHFT                               18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH3_LP5_DCC_PLL1_3197_BMSK                                 0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH3_LP5_DCC_PLL1_3197_SHFT                                      12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH3_LP5_DCC_PLL0_3197_BMSK                                   0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH3_LP5_DCC_PLL0_3197_SHFT                                       6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH2_LP5_CA_DCC_IO_CK_3197_BMSK                                0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_DDR_CH2_LP5_CA_DCC_IO_CK_3197_SHFT                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9a4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9a4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ1_DCC_RDT4_3197_3_0_BMSK                      0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ1_DCC_RDT4_3197_3_0_SHFT                              28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ1_DCC_IO_DQS_3197_BMSK                         0xfc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ1_DCC_IO_DQS_3197_SHFT                                22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ1_DCC_IO_WCK_3197_BMSK                          0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ1_DCC_IO_WCK_3197_SHFT                                16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ1_DCC_CLK_ADJ_3197_BMSK                           0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ1_DCC_CLK_ADJ_3197_SHFT                               10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ0_DCC_RDT4_3197_BMSK                               0x3f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ0_DCC_RDT4_3197_SHFT                                   4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ0_DCC_IO_DQS_3197_5_2_BMSK                           0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_DDR_CH3_LP5_DQ0_DCC_IO_DQS_3197_5_2_SHFT                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9a8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9a8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CALIBRATION_2335_2312_BMSK                                  0xffffff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CALIBRATION_2335_2312_SHFT                                           8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_DDR_CH3_LP5_CA_DCC_IO_CK_3197_BMSK                                0xfc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_DDR_CH3_LP5_CA_DCC_IO_CK_3197_SHFT                                   2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_DDR_CH3_LP5_DQ1_DCC_RDT4_3197_5_4_BMSK                             0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_DDR_CH3_LP5_DQ1_DCC_RDT4_3197_5_4_SHFT                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9ac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9ac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR9_TURL3_QUOT_MIN_0_BMSK                                  0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR9_TURL3_QUOT_MIN_0_SHFT                                          31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR9_TARG_VOLT_TURL3_BMSK                                   0x7e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR9_TARG_VOLT_TURL3_SHFT                                           25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR2_TARG_VOLT_OFFSET_LSVSL1_BMSK                            0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR2_TARG_VOLT_OFFSET_LSVSL1_SHFT                                   20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR2_TARG_VOLT_OFFSET_SVSL0_BMSK                               0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR2_TARG_VOLT_OFFSET_SVSL0_SHFT                                    15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR0_TARG_VOLT_OFFSET_NOML0_BMSK                                0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR0_TARG_VOLT_OFFSET_NOML0_SHFT                                    10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR0_TARG_VOLT_OFFSET_TURL0_BMSK                                 0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR0_TARG_VOLT_OFFSET_TURL0_SHFT                                     5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR0_TARG_VOLT_OFFSET_TURL2_BMSK                                  0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CPR0_TARG_VOLT_OFFSET_TURL2_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9b0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9b0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CALIBRATION_2399_2397_BMSK                                  0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CALIBRATION_2399_2397_SHFT                                          29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR10_TURL3_QUOT_MIN_BMSK                                   0x1ffe0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR10_TURL3_QUOT_MIN_SHFT                                           17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR10_TARG_VOLT_TURL3_BMSK                                     0x1f800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR10_TARG_VOLT_TURL3_SHFT                                          11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR9_TURL3_QUOT_MIN_11_1_BMSK                                    0x7ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CPR9_TURL3_QUOT_MIN_11_1_SHFT                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9b4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9b4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CALIBRATION_2431_2430_BMSK                                  0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CALIBRATION_2431_2430_SHFT                                          30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ISENSE_FUSE_CURRENT_HMX_F2_BMSK                             0x3ff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ISENSE_FUSE_CURRENT_HMX_F2_SHFT                                     20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ISENSE_FUSE_CURRENT_HMX_F1_BMSK                                0xffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ISENSE_FUSE_CURRENT_HMX_F1_SHFT                                     10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ISENSE_FUSE_CURRENT_HVX_F2_BMSK                                  0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ISENSE_FUSE_CURRENT_HVX_F2_SHFT                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9b8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9b8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ROCOUNT_FUSE_NSPRAIL_BMSK                                   0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ROCOUNT_FUSE_NSPRAIL_SHFT                                           24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ROCOUNT_FUSE_CPURAIL_BMSK                                     0xff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ROCOUNT_FUSE_CPURAIL_SHFT                                           16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_FACTOR_FUSE_NSPRAIL_BMSK                                        0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_FACTOR_FUSE_NSPRAIL_SHFT                                            11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_FACTOR_FUSE_CPURAIL_BMSK                                         0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_FACTOR_FUSE_CPURAIL_SHFT                                             6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CALIBRATION_2437_2432_BMSK                                        0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CALIBRATION_2437_2432_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9bc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9bc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_NSPRAIL_HVX_FT_4_0_BMSK                          0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_NSPRAIL_HVX_FT_4_0_SHFT                                  27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU7_FT_BMSK                              0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU7_FT_SHFT                                     21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU6_FT_BMSK                               0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU6_FT_SHFT                                     15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU5_FT_BMSK                                 0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU5_FT_SHFT                                      9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU4_FT_BMSK                                  0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU4_FT_SHFT                                      3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ISENSE_FUSE_REVISION_CONTROL_WS_BMSK                               0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ISENSE_FUSE_REVISION_CONTROL_WS_SHFT                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9c0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9c0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_CALIBRATION_2527_2515_BMSK                                  0xfff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_CALIBRATION_2527_2515_SHFT                                          19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_CURRENT_NSP_RESTCX_BMSK                            0x7fc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_CURRENT_NSP_RESTCX_SHFT                                 10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_REVISION_CONTROL_FT_BMSK                             0x380
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_REVISION_CONTROL_FT_SHFT                                 7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_OPAMP_FUSE_NSPRAIL_HMX_FT_BMSK                                    0x7e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_OPAMP_FUSE_NSPRAIL_HMX_FT_SHFT                                       1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_OPAMP_FUSE_NSPRAIL_HVX_FT_5_BMSK                                   0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_OPAMP_FUSE_NSPRAIL_HVX_FT_5_SHFT                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9c4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9c4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_GFX_CURRENT_REVISION_BMSK                                   0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_GFX_CURRENT_REVISION_SHFT                                           30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_GFX_FUSE_RESERVED_16_0_BMSK                                 0x3fffe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_GFX_FUSE_RESERVED_16_0_SHFT                                         13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_GFX_PEAK_CURRENT_I_LF_BMSK                                      0x1fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_GFX_PEAK_CURRENT_I_LF_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9c8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9c8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_CALIBRATION_2591_2560_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_CALIBRATION_2591_2560_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9cc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9cc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_CALIBRATION_2623_2592_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_CALIBRATION_2623_2592_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9d0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9d0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_CALIBRATION_2655_2624_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_CALIBRATION_2655_2624_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9d4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9d4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_CALIBRATION_2687_2656_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_CALIBRATION_2687_2656_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9d8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9d8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_CALIBRATION_2719_2688_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_CALIBRATION_2719_2688_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR                                                        (QFPROM_CORR_REG_BASE      + 0x9dc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_OFFS                                                        (QFPROM_CORR_REG_BASE_OFFS + 0x9dc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ATTR                                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_SPARE_R315_B63_BMSK                                         0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_SPARE_R315_B63_SHFT                                                 31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_SPARE_R315_B62_BMSK                                         0x40000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_SPARE_R315_B62_SHFT                                                 30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_SPARE_R315_B61_BMSK                                         0x20000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_SPARE_R315_B61_SHFT                                                 29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_SPARE_R315_B60_BMSK                                         0x10000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_SPARE_R315_B60_SHFT                                                 28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_FT_BMSK                                                 0x8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_FT_SHFT                                                        27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_WS_BMSK                                                 0x4000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_WS_SHFT                                                        26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_Q6_ACD_DVM_FT_BMSK                                           0x2000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_Q6_ACD_DVM_FT_SHFT                                                  25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_Q6_ACD_DVM_WS_BMSK                                           0x1000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_Q6_ACD_DVM_WS_SHFT                                                  24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ISENS_FT_BMSK                                                 0x800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ISENS_FT_SHFT                                                       23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ISENS_WS_BMSK                                                 0x400000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ISENS_WS_SHFT                                                       22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_FT_BMSK                                                   0x200000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_FT_SHFT                                                         21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_WS_BMSK                                                   0x100000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_WS_SHFT                                                         20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_FT_BMSK                                                    0x80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_FT_SHFT                                                         19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_WS_BMSK                                                    0x40000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_WS_SHFT                                                         18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_FT_BMSK                                                 0x20000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_FT_SHFT                                                      17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_WS_BMSK                                                 0x10000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_WS_SHFT                                                      16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_FT_BMSK                                                    0x8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_FT_SHFT                                                        15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_WS_BMSK                                                    0x4000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_WS_SHFT                                                        14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_FT_BMSK                                                    0x2000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_FT_SHFT                                                        13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_WS_BMSK                                                    0x1000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_WS_SHFT                                                        12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_FT_BMSK                                                     0x800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_FT_SHFT                                                        11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_WS_BMSK                                                     0x400
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_WS_SHFT                                                        10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_FT_BMSK                                                     0x200
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_FT_SHFT                                                         9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_WS_BMSK                                                     0x100
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_WS_SHFT                                                         8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_FT_BMSK                                                       0x80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_FT_SHFT                                                          7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_WS_BMSK                                                       0x40
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_WS_SHFT                                                          6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_FT_BMSK                                                       0x20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_FT_SHFT                                                          5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_WS_BMSK                                                       0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_WS_SHFT                                                          4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_FT_BMSK                                                      0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_FT_SHFT                                                        3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_WS_BMSK                                                      0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_WS_SHFT                                                        2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_FT_BMSK                                                     0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_FT_SHFT                                                       1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_WS_BMSK                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_WS_SHFT                                                       0


#endif /* __CPR_FUSES_HWIO_H__ */
