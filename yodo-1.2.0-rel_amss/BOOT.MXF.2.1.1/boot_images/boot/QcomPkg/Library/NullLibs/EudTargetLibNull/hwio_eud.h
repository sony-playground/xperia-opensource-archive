#ifndef __HWIO_EUD_H__
#define __HWIO_EUD_H__
/*
===========================================================================
*/
/**
    @file hwio_eud.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SXR1230P (Aurora) [aurora_v1.0_p3q1r42_F00_rtl_partition]
 
    This file contains HWIO register definitions for the following modules:
        EUD_MODE_MANAGER
        EUD_MODE_MANAGER2
        EUD_ACORE
        EUD_DET
        EUD_EUD
        FUSE_CONTROLLER_SW_RANGE5


    Generation parameters: 
    { 'filename': 'hwio_eud.h',
      'header': '#include "msmhwiobase.h"',
      'ignore-prefixes': True,
      'modules': [ 'EUD_MODE_MANAGER',
                   'EUD_MODE_MANAGER2',
                   'EUD_ACORE',
                   'EUD_DET',
                   'EUD_EUD',
                   'FUSE_CONTROLLER_SW_RANGE5'],
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

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NullLibs/EudTargetLibNull/hwio_eud.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"

// Manual mapping created to give the tech team time to migrate to the Hamoa base names
#ifdef AHB2PHY_1_AHB2PHY_1_BASE
  #define AHB2PHY_NORTH_BASE      AHB2PHY_1_AHB2PHY_1_BASE
#endif

#ifdef AHB2PHY_1_AHB2PHY_1_BASE_PHYS
  #define AHB2PHY_NORTH_BASE_PHYS AHB2PHY_1_AHB2PHY_1_BASE_PHYS
#endif

/*----------------------------------------------------------------------------
 * MODULE: MODE_MANAGER
 *--------------------------------------------------------------------------*/

#define MODE_MANAGER_REG_BASE                                                               (AHB2PHY_NORTH_BASE      + 0x00001000)
#define MODE_MANAGER_REG_BASE_SIZE                                                          0x1000
#define MODE_MANAGER_REG_BASE_USED                                                          0x18c
#define MODE_MANAGER_REG_BASE_PHYS                                                          (AHB2PHY_NORTH_BASE_PHYS + 0x00001000)

#define HWIO_DEV_ID_0_ADDR                                                                  (MODE_MANAGER_REG_BASE      + 0x0)
#define HWIO_DEV_ID_0_PHYS                                                                  (MODE_MANAGER_REG_BASE_PHYS + 0x0)
#define HWIO_DEV_ID_0_RMSK                                                                        0xff
#define HWIO_DEV_ID_0_IN                    \
                in_dword(HWIO_DEV_ID_0_ADDR)
#define HWIO_DEV_ID_0_INM(m)            \
                in_dword_masked(HWIO_DEV_ID_0_ADDR, m)
#define HWIO_DEV_ID_0_OUT(v)            \
                out_dword(HWIO_DEV_ID_0_ADDR,v)
#define HWIO_DEV_ID_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_DEV_ID_0_ADDR,m,v,HWIO_DEV_ID_0_IN)
#define HWIO_DEV_ID_0_DEV_ID_0_7_0_BMSK                                                           0xff
#define HWIO_DEV_ID_0_DEV_ID_0_7_0_SHFT                                                              0

#define HWIO_DEV_ID_1_ADDR                                                                  (MODE_MANAGER_REG_BASE      + 0x4)
#define HWIO_DEV_ID_1_PHYS                                                                  (MODE_MANAGER_REG_BASE_PHYS + 0x4)
#define HWIO_DEV_ID_1_RMSK                                                                        0xff
#define HWIO_DEV_ID_1_IN                    \
                in_dword(HWIO_DEV_ID_1_ADDR)
#define HWIO_DEV_ID_1_INM(m)            \
                in_dword_masked(HWIO_DEV_ID_1_ADDR, m)
#define HWIO_DEV_ID_1_OUT(v)            \
                out_dword(HWIO_DEV_ID_1_ADDR,v)
#define HWIO_DEV_ID_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_DEV_ID_1_ADDR,m,v,HWIO_DEV_ID_1_IN)
#define HWIO_DEV_ID_1_DEV_ID_1_7_0_BMSK                                                           0xff
#define HWIO_DEV_ID_1_DEV_ID_1_7_0_SHFT                                                              0

#define HWIO_DEV_ID_2_ADDR                                                                  (MODE_MANAGER_REG_BASE      + 0x8)
#define HWIO_DEV_ID_2_PHYS                                                                  (MODE_MANAGER_REG_BASE_PHYS + 0x8)
#define HWIO_DEV_ID_2_RMSK                                                                        0xff
#define HWIO_DEV_ID_2_IN                    \
                in_dword(HWIO_DEV_ID_2_ADDR)
#define HWIO_DEV_ID_2_INM(m)            \
                in_dword_masked(HWIO_DEV_ID_2_ADDR, m)
#define HWIO_DEV_ID_2_OUT(v)            \
                out_dword(HWIO_DEV_ID_2_ADDR,v)
#define HWIO_DEV_ID_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_DEV_ID_2_ADDR,m,v,HWIO_DEV_ID_2_IN)
#define HWIO_DEV_ID_2_DEV_ID_2_7_0_BMSK                                                           0xff
#define HWIO_DEV_ID_2_DEV_ID_2_7_0_SHFT                                                              0

#define HWIO_DEV_ID_3_ADDR                                                                  (MODE_MANAGER_REG_BASE      + 0xc)
#define HWIO_DEV_ID_3_PHYS                                                                  (MODE_MANAGER_REG_BASE_PHYS + 0xc)
#define HWIO_DEV_ID_3_RMSK                                                                        0xff
#define HWIO_DEV_ID_3_IN                    \
                in_dword(HWIO_DEV_ID_3_ADDR)
#define HWIO_DEV_ID_3_INM(m)            \
                in_dword_masked(HWIO_DEV_ID_3_ADDR, m)
#define HWIO_DEV_ID_3_OUT(v)            \
                out_dword(HWIO_DEV_ID_3_ADDR,v)
#define HWIO_DEV_ID_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_DEV_ID_3_ADDR,m,v,HWIO_DEV_ID_3_IN)
#define HWIO_DEV_ID_3_DEV_ID_3_7_0_BMSK                                                           0xff
#define HWIO_DEV_ID_3_DEV_ID_3_7_0_SHFT                                                              0

#define HWIO_CSR_EUD_EN_ADDR                                                                (MODE_MANAGER_REG_BASE      + 0x14)
#define HWIO_CSR_EUD_EN_PHYS                                                                (MODE_MANAGER_REG_BASE_PHYS + 0x14)
#define HWIO_CSR_EUD_EN_RMSK                                                                       0x1
#define HWIO_CSR_EUD_EN_IN                    \
                in_dword(HWIO_CSR_EUD_EN_ADDR)
#define HWIO_CSR_EUD_EN_INM(m)            \
                in_dword_masked(HWIO_CSR_EUD_EN_ADDR, m)
#define HWIO_CSR_EUD_EN_OUT(v)            \
                out_dword(HWIO_CSR_EUD_EN_ADDR,v)
#define HWIO_CSR_EUD_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_CSR_EUD_EN_ADDR,m,v,HWIO_CSR_EUD_EN_IN)
#define HWIO_CSR_EUD_EN_CSR_EUD_EN_0_0_BMSK                                                        0x1
#define HWIO_CSR_EUD_EN_CSR_EUD_EN_0_0_SHFT                                                          0

#define HWIO_SW_ATTACH_DET_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x18)
#define HWIO_SW_ATTACH_DET_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x18)
#define HWIO_SW_ATTACH_DET_RMSK                                                                    0x1
#define HWIO_SW_ATTACH_DET_IN                    \
                in_dword(HWIO_SW_ATTACH_DET_ADDR)
#define HWIO_SW_ATTACH_DET_INM(m)            \
                in_dword_masked(HWIO_SW_ATTACH_DET_ADDR, m)
#define HWIO_SW_ATTACH_DET_OUT(v)            \
                out_dword(HWIO_SW_ATTACH_DET_ADDR,v)
#define HWIO_SW_ATTACH_DET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_SW_ATTACH_DET_ADDR,m,v,HWIO_SW_ATTACH_DET_IN)
#define HWIO_SW_ATTACH_DET_SW_ATTACH_DET_0_0_BMSK                                                  0x1
#define HWIO_SW_ATTACH_DET_SW_ATTACH_DET_0_0_SHFT                                                    0

#define HWIO_TIME_ATT_SAFE_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x1c)
#define HWIO_TIME_ATT_SAFE_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x1c)
#define HWIO_TIME_ATT_SAFE_RMSK                                                                    0x1
#define HWIO_TIME_ATT_SAFE_IN                    \
                in_dword(HWIO_TIME_ATT_SAFE_ADDR)
#define HWIO_TIME_ATT_SAFE_INM(m)            \
                in_dword_masked(HWIO_TIME_ATT_SAFE_ADDR, m)
#define HWIO_TIME_ATT_SAFE_OUT(v)            \
                out_dword(HWIO_TIME_ATT_SAFE_ADDR,v)
#define HWIO_TIME_ATT_SAFE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TIME_ATT_SAFE_ADDR,m,v,HWIO_TIME_ATT_SAFE_IN)
#define HWIO_TIME_ATT_SAFE_TIME_ATT_SAFE_0_0_BMSK                                                  0x1
#define HWIO_TIME_ATT_SAFE_TIME_ATT_SAFE_0_0_SHFT                                                    0

#define HWIO_EUD_STATUS_ADDR                                                                (MODE_MANAGER_REG_BASE      + 0x20)
#define HWIO_EUD_STATUS_PHYS                                                                (MODE_MANAGER_REG_BASE_PHYS + 0x20)
#define HWIO_EUD_STATUS_RMSK                                                                      0xff
#define HWIO_EUD_STATUS_IN                    \
                in_dword(HWIO_EUD_STATUS_ADDR)
#define HWIO_EUD_STATUS_INM(m)            \
                in_dword_masked(HWIO_EUD_STATUS_ADDR, m)
#define HWIO_EUD_STATUS_EUD_STATUS_2_0_BMSK                                                       0xff
#define HWIO_EUD_STATUS_EUD_STATUS_2_0_SHFT                                                          0

#define HWIO_PBUS_CTRL_EN_ADDR                                                              (MODE_MANAGER_REG_BASE      + 0x24)
#define HWIO_PBUS_CTRL_EN_PHYS                                                              (MODE_MANAGER_REG_BASE_PHYS + 0x24)
#define HWIO_PBUS_CTRL_EN_RMSK                                                                     0x1
#define HWIO_PBUS_CTRL_EN_IN                    \
                in_dword(HWIO_PBUS_CTRL_EN_ADDR)
#define HWIO_PBUS_CTRL_EN_INM(m)            \
                in_dword_masked(HWIO_PBUS_CTRL_EN_ADDR, m)
#define HWIO_PBUS_CTRL_EN_OUT(v)            \
                out_dword(HWIO_PBUS_CTRL_EN_ADDR,v)
#define HWIO_PBUS_CTRL_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_PBUS_CTRL_EN_ADDR,m,v,HWIO_PBUS_CTRL_EN_IN)
#define HWIO_PBUS_CTRL_EN_PBUS_CTRL_EN_0_0_BMSK                                                    0x1
#define HWIO_PBUS_CTRL_EN_PBUS_CTRL_EN_0_0_SHFT                                                      0

#define HWIO_EUD_PORT_SEL_ADDR                                                              (MODE_MANAGER_REG_BASE      + 0x28)
#define HWIO_EUD_PORT_SEL_PHYS                                                              (MODE_MANAGER_REG_BASE_PHYS + 0x28)
#define HWIO_EUD_PORT_SEL_RMSK                                                                     0x1
#define HWIO_EUD_PORT_SEL_IN                    \
                in_dword(HWIO_EUD_PORT_SEL_ADDR)
#define HWIO_EUD_PORT_SEL_INM(m)            \
                in_dword_masked(HWIO_EUD_PORT_SEL_ADDR, m)
#define HWIO_EUD_PORT_SEL_OUT(v)            \
                out_dword(HWIO_EUD_PORT_SEL_ADDR,v)
#define HWIO_EUD_PORT_SEL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_EUD_PORT_SEL_ADDR,m,v,HWIO_EUD_PORT_SEL_IN)
#define HWIO_EUD_PORT_SEL_EUD_PORT_SEL_0_0_BMSK                                                    0x1
#define HWIO_EUD_PORT_SEL_EUD_PORT_SEL_0_0_SHFT                                                      0

#define HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_ADDR                                              (MODE_MANAGER_REG_BASE      + 0x2c)
#define HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_PHYS                                              (MODE_MANAGER_REG_BASE_PHYS + 0x2c)
#define HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_RMSK                                                     0x3
#define HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_IN                    \
                in_dword(HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_ADDR)
#define HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_INM(m)            \
                in_dword_masked(HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_ADDR, m)
#define HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_OUT(v)            \
                out_dword(HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_ADDR,v)
#define HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_ADDR,m,v,HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_IN)
#define HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_PHY_RESET_EN_1_0_BMSK                                    0x2
#define HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_PHY_RESET_EN_1_0_SHFT                                      1
#define HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_EUSB2PHY_XTRA_TUNE_PARAM_EN_0_0_BMSK                     0x1
#define HWIO_EUSB2PHY_XTRA_TUNE_PARARM_EN_EUSB2PHY_XTRA_TUNE_PARAM_EN_0_0_SHFT                       0

#define HWIO_UTMI_SWITCH_DELAY_LSB_ADDR                                                     (MODE_MANAGER_REG_BASE      + 0x30)
#define HWIO_UTMI_SWITCH_DELAY_LSB_PHYS                                                     (MODE_MANAGER_REG_BASE_PHYS + 0x30)
#define HWIO_UTMI_SWITCH_DELAY_LSB_RMSK                                                           0xff
#define HWIO_UTMI_SWITCH_DELAY_LSB_IN                    \
                in_dword(HWIO_UTMI_SWITCH_DELAY_LSB_ADDR)
#define HWIO_UTMI_SWITCH_DELAY_LSB_INM(m)            \
                in_dword_masked(HWIO_UTMI_SWITCH_DELAY_LSB_ADDR, m)
#define HWIO_UTMI_SWITCH_DELAY_LSB_OUT(v)            \
                out_dword(HWIO_UTMI_SWITCH_DELAY_LSB_ADDR,v)
#define HWIO_UTMI_SWITCH_DELAY_LSB_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UTMI_SWITCH_DELAY_LSB_ADDR,m,v,HWIO_UTMI_SWITCH_DELAY_LSB_IN)
#define HWIO_UTMI_SWITCH_DELAY_LSB_UTMI_SWITCH_DELAY_LSB_7_0_BMSK                                 0xff
#define HWIO_UTMI_SWITCH_DELAY_LSB_UTMI_SWITCH_DELAY_LSB_7_0_SHFT                                    0

#define HWIO_UTMI_SWITCH_DELAY_MSB_ADDR                                                     (MODE_MANAGER_REG_BASE      + 0x34)
#define HWIO_UTMI_SWITCH_DELAY_MSB_PHYS                                                     (MODE_MANAGER_REG_BASE_PHYS + 0x34)
#define HWIO_UTMI_SWITCH_DELAY_MSB_RMSK                                                           0xff
#define HWIO_UTMI_SWITCH_DELAY_MSB_IN                    \
                in_dword(HWIO_UTMI_SWITCH_DELAY_MSB_ADDR)
#define HWIO_UTMI_SWITCH_DELAY_MSB_INM(m)            \
                in_dword_masked(HWIO_UTMI_SWITCH_DELAY_MSB_ADDR, m)
#define HWIO_UTMI_SWITCH_DELAY_MSB_OUT(v)            \
                out_dword(HWIO_UTMI_SWITCH_DELAY_MSB_ADDR,v)
#define HWIO_UTMI_SWITCH_DELAY_MSB_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UTMI_SWITCH_DELAY_MSB_ADDR,m,v,HWIO_UTMI_SWITCH_DELAY_MSB_IN)
#define HWIO_UTMI_SWITCH_DELAY_MSB_UTMI_SWITCH_DELAY_MSB_7_0_BMSK                                 0xff
#define HWIO_UTMI_SWITCH_DELAY_MSB_UTMI_SWITCH_DELAY_MSB_7_0_SHFT                                    0

#define HWIO_Q2_TUNE_ADR00_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x80)
#define HWIO_Q2_TUNE_ADR00_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x80)
#define HWIO_Q2_TUNE_ADR00_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR00_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR00_ADDR)
#define HWIO_Q2_TUNE_ADR00_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR00_ADDR, m)
#define HWIO_Q2_TUNE_ADR00_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR00_ADDR,v)
#define HWIO_Q2_TUNE_ADR00_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR00_ADDR,m,v,HWIO_Q2_TUNE_ADR00_IN)
#define HWIO_Q2_TUNE_ADR00_Q2_TUNE_ADR00_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR00_Q2_TUNE_ADR00_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT00_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x84)
#define HWIO_Q2_TUNE_DAT00_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x84)
#define HWIO_Q2_TUNE_DAT00_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT00_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT00_ADDR)
#define HWIO_Q2_TUNE_DAT00_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT00_ADDR, m)
#define HWIO_Q2_TUNE_DAT00_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT00_ADDR,v)
#define HWIO_Q2_TUNE_DAT00_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT00_ADDR,m,v,HWIO_Q2_TUNE_DAT00_IN)
#define HWIO_Q2_TUNE_DAT00_Q2_TUNE_DAT00_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT00_Q2_TUNE_DAT00_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR01_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x88)
#define HWIO_Q2_TUNE_ADR01_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x88)
#define HWIO_Q2_TUNE_ADR01_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR01_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR01_ADDR)
#define HWIO_Q2_TUNE_ADR01_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR01_ADDR, m)
#define HWIO_Q2_TUNE_ADR01_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR01_ADDR,v)
#define HWIO_Q2_TUNE_ADR01_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR01_ADDR,m,v,HWIO_Q2_TUNE_ADR01_IN)
#define HWIO_Q2_TUNE_ADR01_Q2_TUNE_ADR01_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR01_Q2_TUNE_ADR01_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT01_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x8c)
#define HWIO_Q2_TUNE_DAT01_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x8c)
#define HWIO_Q2_TUNE_DAT01_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT01_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT01_ADDR)
#define HWIO_Q2_TUNE_DAT01_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT01_ADDR, m)
#define HWIO_Q2_TUNE_DAT01_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT01_ADDR,v)
#define HWIO_Q2_TUNE_DAT01_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT01_ADDR,m,v,HWIO_Q2_TUNE_DAT01_IN)
#define HWIO_Q2_TUNE_DAT01_Q2_TUNE_DAT01_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT01_Q2_TUNE_DAT01_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR02_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x90)
#define HWIO_Q2_TUNE_ADR02_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x90)
#define HWIO_Q2_TUNE_ADR02_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR02_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR02_ADDR)
#define HWIO_Q2_TUNE_ADR02_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR02_ADDR, m)
#define HWIO_Q2_TUNE_ADR02_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR02_ADDR,v)
#define HWIO_Q2_TUNE_ADR02_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR02_ADDR,m,v,HWIO_Q2_TUNE_ADR02_IN)
#define HWIO_Q2_TUNE_ADR02_Q2_TUNE_ADR02_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR02_Q2_TUNE_ADR02_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT02_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x94)
#define HWIO_Q2_TUNE_DAT02_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x94)
#define HWIO_Q2_TUNE_DAT02_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT02_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT02_ADDR)
#define HWIO_Q2_TUNE_DAT02_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT02_ADDR, m)
#define HWIO_Q2_TUNE_DAT02_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT02_ADDR,v)
#define HWIO_Q2_TUNE_DAT02_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT02_ADDR,m,v,HWIO_Q2_TUNE_DAT02_IN)
#define HWIO_Q2_TUNE_DAT02_Q2_TUNE_DAT02_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT02_Q2_TUNE_DAT02_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR03_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x98)
#define HWIO_Q2_TUNE_ADR03_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x98)
#define HWIO_Q2_TUNE_ADR03_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR03_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR03_ADDR)
#define HWIO_Q2_TUNE_ADR03_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR03_ADDR, m)
#define HWIO_Q2_TUNE_ADR03_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR03_ADDR,v)
#define HWIO_Q2_TUNE_ADR03_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR03_ADDR,m,v,HWIO_Q2_TUNE_ADR03_IN)
#define HWIO_Q2_TUNE_ADR03_Q2_TUNE_ADR03_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR03_Q2_TUNE_ADR03_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT03_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x9c)
#define HWIO_Q2_TUNE_DAT03_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x9c)
#define HWIO_Q2_TUNE_DAT03_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT03_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT03_ADDR)
#define HWIO_Q2_TUNE_DAT03_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT03_ADDR, m)
#define HWIO_Q2_TUNE_DAT03_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT03_ADDR,v)
#define HWIO_Q2_TUNE_DAT03_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT03_ADDR,m,v,HWIO_Q2_TUNE_DAT03_IN)
#define HWIO_Q2_TUNE_DAT03_Q2_TUNE_DAT03_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT03_Q2_TUNE_DAT03_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR04_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xa0)
#define HWIO_Q2_TUNE_ADR04_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xa0)
#define HWIO_Q2_TUNE_ADR04_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR04_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR04_ADDR)
#define HWIO_Q2_TUNE_ADR04_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR04_ADDR, m)
#define HWIO_Q2_TUNE_ADR04_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR04_ADDR,v)
#define HWIO_Q2_TUNE_ADR04_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR04_ADDR,m,v,HWIO_Q2_TUNE_ADR04_IN)
#define HWIO_Q2_TUNE_ADR04_Q2_TUNE_ADR04_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR04_Q2_TUNE_ADR04_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT04_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xa4)
#define HWIO_Q2_TUNE_DAT04_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xa4)
#define HWIO_Q2_TUNE_DAT04_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT04_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT04_ADDR)
#define HWIO_Q2_TUNE_DAT04_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT04_ADDR, m)
#define HWIO_Q2_TUNE_DAT04_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT04_ADDR,v)
#define HWIO_Q2_TUNE_DAT04_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT04_ADDR,m,v,HWIO_Q2_TUNE_DAT04_IN)
#define HWIO_Q2_TUNE_DAT04_Q2_TUNE_DAT04_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT04_Q2_TUNE_DAT04_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR05_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xa8)
#define HWIO_Q2_TUNE_ADR05_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xa8)
#define HWIO_Q2_TUNE_ADR05_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR05_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR05_ADDR)
#define HWIO_Q2_TUNE_ADR05_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR05_ADDR, m)
#define HWIO_Q2_TUNE_ADR05_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR05_ADDR,v)
#define HWIO_Q2_TUNE_ADR05_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR05_ADDR,m,v,HWIO_Q2_TUNE_ADR05_IN)
#define HWIO_Q2_TUNE_ADR05_Q2_TUNE_ADR05_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR05_Q2_TUNE_ADR05_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT05_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xac)
#define HWIO_Q2_TUNE_DAT05_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xac)
#define HWIO_Q2_TUNE_DAT05_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT05_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT05_ADDR)
#define HWIO_Q2_TUNE_DAT05_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT05_ADDR, m)
#define HWIO_Q2_TUNE_DAT05_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT05_ADDR,v)
#define HWIO_Q2_TUNE_DAT05_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT05_ADDR,m,v,HWIO_Q2_TUNE_DAT05_IN)
#define HWIO_Q2_TUNE_DAT05_Q2_TUNE_DAT05_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT05_Q2_TUNE_DAT05_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR06_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xb0)
#define HWIO_Q2_TUNE_ADR06_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xb0)
#define HWIO_Q2_TUNE_ADR06_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR06_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR06_ADDR)
#define HWIO_Q2_TUNE_ADR06_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR06_ADDR, m)
#define HWIO_Q2_TUNE_ADR06_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR06_ADDR,v)
#define HWIO_Q2_TUNE_ADR06_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR06_ADDR,m,v,HWIO_Q2_TUNE_ADR06_IN)
#define HWIO_Q2_TUNE_ADR06_Q2_TUNE_ADR06_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR06_Q2_TUNE_ADR06_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT06_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xb4)
#define HWIO_Q2_TUNE_DAT06_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xb4)
#define HWIO_Q2_TUNE_DAT06_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT06_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT06_ADDR)
#define HWIO_Q2_TUNE_DAT06_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT06_ADDR, m)
#define HWIO_Q2_TUNE_DAT06_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT06_ADDR,v)
#define HWIO_Q2_TUNE_DAT06_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT06_ADDR,m,v,HWIO_Q2_TUNE_DAT06_IN)
#define HWIO_Q2_TUNE_DAT06_Q2_TUNE_DAT06_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT06_Q2_TUNE_DAT06_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR07_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xb8)
#define HWIO_Q2_TUNE_ADR07_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xb8)
#define HWIO_Q2_TUNE_ADR07_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR07_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR07_ADDR)
#define HWIO_Q2_TUNE_ADR07_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR07_ADDR, m)
#define HWIO_Q2_TUNE_ADR07_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR07_ADDR,v)
#define HWIO_Q2_TUNE_ADR07_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR07_ADDR,m,v,HWIO_Q2_TUNE_ADR07_IN)
#define HWIO_Q2_TUNE_ADR07_Q2_TUNE_ADR07_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR07_Q2_TUNE_ADR07_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT07_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xbc)
#define HWIO_Q2_TUNE_DAT07_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xbc)
#define HWIO_Q2_TUNE_DAT07_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT07_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT07_ADDR)
#define HWIO_Q2_TUNE_DAT07_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT07_ADDR, m)
#define HWIO_Q2_TUNE_DAT07_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT07_ADDR,v)
#define HWIO_Q2_TUNE_DAT07_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT07_ADDR,m,v,HWIO_Q2_TUNE_DAT07_IN)
#define HWIO_Q2_TUNE_DAT07_Q2_TUNE_DAT07_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT07_Q2_TUNE_DAT07_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR08_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xc0)
#define HWIO_Q2_TUNE_ADR08_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xc0)
#define HWIO_Q2_TUNE_ADR08_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR08_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR08_ADDR)
#define HWIO_Q2_TUNE_ADR08_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR08_ADDR, m)
#define HWIO_Q2_TUNE_ADR08_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR08_ADDR,v)
#define HWIO_Q2_TUNE_ADR08_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR08_ADDR,m,v,HWIO_Q2_TUNE_ADR08_IN)
#define HWIO_Q2_TUNE_ADR08_Q2_TUNE_ADR08_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR08_Q2_TUNE_ADR08_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT08_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xc4)
#define HWIO_Q2_TUNE_DAT08_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xc4)
#define HWIO_Q2_TUNE_DAT08_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT08_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT08_ADDR)
#define HWIO_Q2_TUNE_DAT08_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT08_ADDR, m)
#define HWIO_Q2_TUNE_DAT08_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT08_ADDR,v)
#define HWIO_Q2_TUNE_DAT08_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT08_ADDR,m,v,HWIO_Q2_TUNE_DAT08_IN)
#define HWIO_Q2_TUNE_DAT08_Q2_TUNE_DAT08_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT08_Q2_TUNE_DAT08_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR09_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xc8)
#define HWIO_Q2_TUNE_ADR09_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xc8)
#define HWIO_Q2_TUNE_ADR09_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR09_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR09_ADDR)
#define HWIO_Q2_TUNE_ADR09_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR09_ADDR, m)
#define HWIO_Q2_TUNE_ADR09_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR09_ADDR,v)
#define HWIO_Q2_TUNE_ADR09_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR09_ADDR,m,v,HWIO_Q2_TUNE_ADR09_IN)
#define HWIO_Q2_TUNE_ADR09_Q2_TUNE_ADR09_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR09_Q2_TUNE_ADR09_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT09_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xcc)
#define HWIO_Q2_TUNE_DAT09_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xcc)
#define HWIO_Q2_TUNE_DAT09_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT09_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT09_ADDR)
#define HWIO_Q2_TUNE_DAT09_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT09_ADDR, m)
#define HWIO_Q2_TUNE_DAT09_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT09_ADDR,v)
#define HWIO_Q2_TUNE_DAT09_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT09_ADDR,m,v,HWIO_Q2_TUNE_DAT09_IN)
#define HWIO_Q2_TUNE_DAT09_Q2_TUNE_DAT09_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT09_Q2_TUNE_DAT09_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR10_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xd0)
#define HWIO_Q2_TUNE_ADR10_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xd0)
#define HWIO_Q2_TUNE_ADR10_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR10_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR10_ADDR)
#define HWIO_Q2_TUNE_ADR10_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR10_ADDR, m)
#define HWIO_Q2_TUNE_ADR10_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR10_ADDR,v)
#define HWIO_Q2_TUNE_ADR10_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR10_ADDR,m,v,HWIO_Q2_TUNE_ADR10_IN)
#define HWIO_Q2_TUNE_ADR10_Q2_TUNE_ADR10_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR10_Q2_TUNE_ADR10_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT10_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xd4)
#define HWIO_Q2_TUNE_DAT10_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xd4)
#define HWIO_Q2_TUNE_DAT10_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT10_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT10_ADDR)
#define HWIO_Q2_TUNE_DAT10_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT10_ADDR, m)
#define HWIO_Q2_TUNE_DAT10_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT10_ADDR,v)
#define HWIO_Q2_TUNE_DAT10_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT10_ADDR,m,v,HWIO_Q2_TUNE_DAT10_IN)
#define HWIO_Q2_TUNE_DAT10_Q2_TUNE_DAT10_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT10_Q2_TUNE_DAT10_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR11_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xd8)
#define HWIO_Q2_TUNE_ADR11_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xd8)
#define HWIO_Q2_TUNE_ADR11_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR11_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR11_ADDR)
#define HWIO_Q2_TUNE_ADR11_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR11_ADDR, m)
#define HWIO_Q2_TUNE_ADR11_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR11_ADDR,v)
#define HWIO_Q2_TUNE_ADR11_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR11_ADDR,m,v,HWIO_Q2_TUNE_ADR11_IN)
#define HWIO_Q2_TUNE_ADR11_Q2_TUNE_ADR11_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR11_Q2_TUNE_ADR11_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT11_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xdc)
#define HWIO_Q2_TUNE_DAT11_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xdc)
#define HWIO_Q2_TUNE_DAT11_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT11_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT11_ADDR)
#define HWIO_Q2_TUNE_DAT11_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT11_ADDR, m)
#define HWIO_Q2_TUNE_DAT11_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT11_ADDR,v)
#define HWIO_Q2_TUNE_DAT11_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT11_ADDR,m,v,HWIO_Q2_TUNE_DAT11_IN)
#define HWIO_Q2_TUNE_DAT11_Q2_TUNE_DAT11_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT11_Q2_TUNE_DAT11_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR12_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xe0)
#define HWIO_Q2_TUNE_ADR12_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xe0)
#define HWIO_Q2_TUNE_ADR12_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR12_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR12_ADDR)
#define HWIO_Q2_TUNE_ADR12_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR12_ADDR, m)
#define HWIO_Q2_TUNE_ADR12_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR12_ADDR,v)
#define HWIO_Q2_TUNE_ADR12_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR12_ADDR,m,v,HWIO_Q2_TUNE_ADR12_IN)
#define HWIO_Q2_TUNE_ADR12_Q2_TUNE_ADR12_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR12_Q2_TUNE_ADR12_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT12_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xe4)
#define HWIO_Q2_TUNE_DAT12_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xe4)
#define HWIO_Q2_TUNE_DAT12_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT12_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT12_ADDR)
#define HWIO_Q2_TUNE_DAT12_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT12_ADDR, m)
#define HWIO_Q2_TUNE_DAT12_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT12_ADDR,v)
#define HWIO_Q2_TUNE_DAT12_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT12_ADDR,m,v,HWIO_Q2_TUNE_DAT12_IN)
#define HWIO_Q2_TUNE_DAT12_Q2_TUNE_DAT12_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT12_Q2_TUNE_DAT12_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR13_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xe8)
#define HWIO_Q2_TUNE_ADR13_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xe8)
#define HWIO_Q2_TUNE_ADR13_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR13_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR13_ADDR)
#define HWIO_Q2_TUNE_ADR13_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR13_ADDR, m)
#define HWIO_Q2_TUNE_ADR13_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR13_ADDR,v)
#define HWIO_Q2_TUNE_ADR13_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR13_ADDR,m,v,HWIO_Q2_TUNE_ADR13_IN)
#define HWIO_Q2_TUNE_ADR13_Q2_TUNE_ADR13_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR13_Q2_TUNE_ADR13_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT13_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xec)
#define HWIO_Q2_TUNE_DAT13_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xec)
#define HWIO_Q2_TUNE_DAT13_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT13_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT13_ADDR)
#define HWIO_Q2_TUNE_DAT13_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT13_ADDR, m)
#define HWIO_Q2_TUNE_DAT13_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT13_ADDR,v)
#define HWIO_Q2_TUNE_DAT13_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT13_ADDR,m,v,HWIO_Q2_TUNE_DAT13_IN)
#define HWIO_Q2_TUNE_DAT13_Q2_TUNE_DAT13_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT13_Q2_TUNE_DAT13_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR14_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xf0)
#define HWIO_Q2_TUNE_ADR14_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xf0)
#define HWIO_Q2_TUNE_ADR14_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR14_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR14_ADDR)
#define HWIO_Q2_TUNE_ADR14_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR14_ADDR, m)
#define HWIO_Q2_TUNE_ADR14_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR14_ADDR,v)
#define HWIO_Q2_TUNE_ADR14_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR14_ADDR,m,v,HWIO_Q2_TUNE_ADR14_IN)
#define HWIO_Q2_TUNE_ADR14_Q2_TUNE_ADR14_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR14_Q2_TUNE_ADR14_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT14_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xf4)
#define HWIO_Q2_TUNE_DAT14_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xf4)
#define HWIO_Q2_TUNE_DAT14_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT14_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT14_ADDR)
#define HWIO_Q2_TUNE_DAT14_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT14_ADDR, m)
#define HWIO_Q2_TUNE_DAT14_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT14_ADDR,v)
#define HWIO_Q2_TUNE_DAT14_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT14_ADDR,m,v,HWIO_Q2_TUNE_DAT14_IN)
#define HWIO_Q2_TUNE_DAT14_Q2_TUNE_DAT14_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT14_Q2_TUNE_DAT14_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR15_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xf8)
#define HWIO_Q2_TUNE_ADR15_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xf8)
#define HWIO_Q2_TUNE_ADR15_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR15_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR15_ADDR)
#define HWIO_Q2_TUNE_ADR15_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR15_ADDR, m)
#define HWIO_Q2_TUNE_ADR15_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR15_ADDR,v)
#define HWIO_Q2_TUNE_ADR15_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR15_ADDR,m,v,HWIO_Q2_TUNE_ADR15_IN)
#define HWIO_Q2_TUNE_ADR15_Q2_TUNE_ADR15_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR15_Q2_TUNE_ADR15_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT15_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0xfc)
#define HWIO_Q2_TUNE_DAT15_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0xfc)
#define HWIO_Q2_TUNE_DAT15_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT15_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT15_ADDR)
#define HWIO_Q2_TUNE_DAT15_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT15_ADDR, m)
#define HWIO_Q2_TUNE_DAT15_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT15_ADDR,v)
#define HWIO_Q2_TUNE_DAT15_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT15_ADDR,m,v,HWIO_Q2_TUNE_DAT15_IN)
#define HWIO_Q2_TUNE_DAT15_Q2_TUNE_DAT15_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT15_Q2_TUNE_DAT15_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR16_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x100)
#define HWIO_Q2_TUNE_ADR16_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x100)
#define HWIO_Q2_TUNE_ADR16_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR16_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR16_ADDR)
#define HWIO_Q2_TUNE_ADR16_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR16_ADDR, m)
#define HWIO_Q2_TUNE_ADR16_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR16_ADDR,v)
#define HWIO_Q2_TUNE_ADR16_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR16_ADDR,m,v,HWIO_Q2_TUNE_ADR16_IN)
#define HWIO_Q2_TUNE_ADR16_Q2_TUNE_ADR16_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR16_Q2_TUNE_ADR16_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT16_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x104)
#define HWIO_Q2_TUNE_DAT16_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x104)
#define HWIO_Q2_TUNE_DAT16_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT16_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT16_ADDR)
#define HWIO_Q2_TUNE_DAT16_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT16_ADDR, m)
#define HWIO_Q2_TUNE_DAT16_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT16_ADDR,v)
#define HWIO_Q2_TUNE_DAT16_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT16_ADDR,m,v,HWIO_Q2_TUNE_DAT16_IN)
#define HWIO_Q2_TUNE_DAT16_Q2_TUNE_DAT16_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT16_Q2_TUNE_DAT16_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR17_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x108)
#define HWIO_Q2_TUNE_ADR17_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x108)
#define HWIO_Q2_TUNE_ADR17_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR17_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR17_ADDR)
#define HWIO_Q2_TUNE_ADR17_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR17_ADDR, m)
#define HWIO_Q2_TUNE_ADR17_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR17_ADDR,v)
#define HWIO_Q2_TUNE_ADR17_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR17_ADDR,m,v,HWIO_Q2_TUNE_ADR17_IN)
#define HWIO_Q2_TUNE_ADR17_Q2_TUNE_ADR17_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR17_Q2_TUNE_ADR17_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT17_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x10c)
#define HWIO_Q2_TUNE_DAT17_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x10c)
#define HWIO_Q2_TUNE_DAT17_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT17_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT17_ADDR)
#define HWIO_Q2_TUNE_DAT17_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT17_ADDR, m)
#define HWIO_Q2_TUNE_DAT17_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT17_ADDR,v)
#define HWIO_Q2_TUNE_DAT17_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT17_ADDR,m,v,HWIO_Q2_TUNE_DAT17_IN)
#define HWIO_Q2_TUNE_DAT17_Q2_TUNE_DAT17_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT17_Q2_TUNE_DAT17_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR18_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x110)
#define HWIO_Q2_TUNE_ADR18_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x110)
#define HWIO_Q2_TUNE_ADR18_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR18_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR18_ADDR)
#define HWIO_Q2_TUNE_ADR18_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR18_ADDR, m)
#define HWIO_Q2_TUNE_ADR18_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR18_ADDR,v)
#define HWIO_Q2_TUNE_ADR18_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR18_ADDR,m,v,HWIO_Q2_TUNE_ADR18_IN)
#define HWIO_Q2_TUNE_ADR18_Q2_TUNE_ADR18_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR18_Q2_TUNE_ADR18_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT18_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x114)
#define HWIO_Q2_TUNE_DAT18_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x114)
#define HWIO_Q2_TUNE_DAT18_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT18_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT18_ADDR)
#define HWIO_Q2_TUNE_DAT18_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT18_ADDR, m)
#define HWIO_Q2_TUNE_DAT18_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT18_ADDR,v)
#define HWIO_Q2_TUNE_DAT18_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT18_ADDR,m,v,HWIO_Q2_TUNE_DAT18_IN)
#define HWIO_Q2_TUNE_DAT18_Q2_TUNE_DAT18_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT18_Q2_TUNE_DAT18_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR19_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x118)
#define HWIO_Q2_TUNE_ADR19_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x118)
#define HWIO_Q2_TUNE_ADR19_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR19_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR19_ADDR)
#define HWIO_Q2_TUNE_ADR19_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR19_ADDR, m)
#define HWIO_Q2_TUNE_ADR19_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR19_ADDR,v)
#define HWIO_Q2_TUNE_ADR19_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR19_ADDR,m,v,HWIO_Q2_TUNE_ADR19_IN)
#define HWIO_Q2_TUNE_ADR19_Q2_TUNE_ADR19_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR19_Q2_TUNE_ADR19_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT19_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x11c)
#define HWIO_Q2_TUNE_DAT19_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x11c)
#define HWIO_Q2_TUNE_DAT19_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT19_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT19_ADDR)
#define HWIO_Q2_TUNE_DAT19_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT19_ADDR, m)
#define HWIO_Q2_TUNE_DAT19_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT19_ADDR,v)
#define HWIO_Q2_TUNE_DAT19_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT19_ADDR,m,v,HWIO_Q2_TUNE_DAT19_IN)
#define HWIO_Q2_TUNE_DAT19_Q2_TUNE_DAT19_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT19_Q2_TUNE_DAT19_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR20_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x120)
#define HWIO_Q2_TUNE_ADR20_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x120)
#define HWIO_Q2_TUNE_ADR20_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR20_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR20_ADDR)
#define HWIO_Q2_TUNE_ADR20_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR20_ADDR, m)
#define HWIO_Q2_TUNE_ADR20_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR20_ADDR,v)
#define HWIO_Q2_TUNE_ADR20_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR20_ADDR,m,v,HWIO_Q2_TUNE_ADR20_IN)
#define HWIO_Q2_TUNE_ADR20_Q2_TUNE_ADR20_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR20_Q2_TUNE_ADR20_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT20_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x124)
#define HWIO_Q2_TUNE_DAT20_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x124)
#define HWIO_Q2_TUNE_DAT20_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT20_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT20_ADDR)
#define HWIO_Q2_TUNE_DAT20_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT20_ADDR, m)
#define HWIO_Q2_TUNE_DAT20_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT20_ADDR,v)
#define HWIO_Q2_TUNE_DAT20_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT20_ADDR,m,v,HWIO_Q2_TUNE_DAT20_IN)
#define HWIO_Q2_TUNE_DAT20_Q2_TUNE_DAT20_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT20_Q2_TUNE_DAT20_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR21_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x128)
#define HWIO_Q2_TUNE_ADR21_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x128)
#define HWIO_Q2_TUNE_ADR21_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR21_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR21_ADDR)
#define HWIO_Q2_TUNE_ADR21_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR21_ADDR, m)
#define HWIO_Q2_TUNE_ADR21_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR21_ADDR,v)
#define HWIO_Q2_TUNE_ADR21_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR21_ADDR,m,v,HWIO_Q2_TUNE_ADR21_IN)
#define HWIO_Q2_TUNE_ADR21_Q2_TUNE_ADR21_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR21_Q2_TUNE_ADR21_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT21_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x12c)
#define HWIO_Q2_TUNE_DAT21_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x12c)
#define HWIO_Q2_TUNE_DAT21_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT21_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT21_ADDR)
#define HWIO_Q2_TUNE_DAT21_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT21_ADDR, m)
#define HWIO_Q2_TUNE_DAT21_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT21_ADDR,v)
#define HWIO_Q2_TUNE_DAT21_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT21_ADDR,m,v,HWIO_Q2_TUNE_DAT21_IN)
#define HWIO_Q2_TUNE_DAT21_Q2_TUNE_DAT21_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT21_Q2_TUNE_DAT21_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR22_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x130)
#define HWIO_Q2_TUNE_ADR22_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x130)
#define HWIO_Q2_TUNE_ADR22_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR22_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR22_ADDR)
#define HWIO_Q2_TUNE_ADR22_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR22_ADDR, m)
#define HWIO_Q2_TUNE_ADR22_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR22_ADDR,v)
#define HWIO_Q2_TUNE_ADR22_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR22_ADDR,m,v,HWIO_Q2_TUNE_ADR22_IN)
#define HWIO_Q2_TUNE_ADR22_Q2_TUNE_ADR22_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR22_Q2_TUNE_ADR22_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT22_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x134)
#define HWIO_Q2_TUNE_DAT22_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x134)
#define HWIO_Q2_TUNE_DAT22_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT22_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT22_ADDR)
#define HWIO_Q2_TUNE_DAT22_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT22_ADDR, m)
#define HWIO_Q2_TUNE_DAT22_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT22_ADDR,v)
#define HWIO_Q2_TUNE_DAT22_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT22_ADDR,m,v,HWIO_Q2_TUNE_DAT22_IN)
#define HWIO_Q2_TUNE_DAT22_Q2_TUNE_DAT22_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT22_Q2_TUNE_DAT22_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR23_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x138)
#define HWIO_Q2_TUNE_ADR23_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x138)
#define HWIO_Q2_TUNE_ADR23_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR23_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR23_ADDR)
#define HWIO_Q2_TUNE_ADR23_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR23_ADDR, m)
#define HWIO_Q2_TUNE_ADR23_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR23_ADDR,v)
#define HWIO_Q2_TUNE_ADR23_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR23_ADDR,m,v,HWIO_Q2_TUNE_ADR23_IN)
#define HWIO_Q2_TUNE_ADR23_Q2_TUNE_ADR23_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR23_Q2_TUNE_ADR23_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT23_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x13c)
#define HWIO_Q2_TUNE_DAT23_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x13c)
#define HWIO_Q2_TUNE_DAT23_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT23_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT23_ADDR)
#define HWIO_Q2_TUNE_DAT23_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT23_ADDR, m)
#define HWIO_Q2_TUNE_DAT23_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT23_ADDR,v)
#define HWIO_Q2_TUNE_DAT23_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT23_ADDR,m,v,HWIO_Q2_TUNE_DAT23_IN)
#define HWIO_Q2_TUNE_DAT23_Q2_TUNE_DAT23_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT23_Q2_TUNE_DAT23_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR24_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x140)
#define HWIO_Q2_TUNE_ADR24_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x140)
#define HWIO_Q2_TUNE_ADR24_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR24_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR24_ADDR)
#define HWIO_Q2_TUNE_ADR24_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR24_ADDR, m)
#define HWIO_Q2_TUNE_ADR24_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR24_ADDR,v)
#define HWIO_Q2_TUNE_ADR24_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR24_ADDR,m,v,HWIO_Q2_TUNE_ADR24_IN)
#define HWIO_Q2_TUNE_ADR24_Q2_TUNE_ADR24_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR24_Q2_TUNE_ADR24_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT24_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x144)
#define HWIO_Q2_TUNE_DAT24_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x144)
#define HWIO_Q2_TUNE_DAT24_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT24_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT24_ADDR)
#define HWIO_Q2_TUNE_DAT24_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT24_ADDR, m)
#define HWIO_Q2_TUNE_DAT24_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT24_ADDR,v)
#define HWIO_Q2_TUNE_DAT24_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT24_ADDR,m,v,HWIO_Q2_TUNE_DAT24_IN)
#define HWIO_Q2_TUNE_DAT24_Q2_TUNE_DAT24_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT24_Q2_TUNE_DAT24_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR25_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x148)
#define HWIO_Q2_TUNE_ADR25_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x148)
#define HWIO_Q2_TUNE_ADR25_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR25_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR25_ADDR)
#define HWIO_Q2_TUNE_ADR25_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR25_ADDR, m)
#define HWIO_Q2_TUNE_ADR25_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR25_ADDR,v)
#define HWIO_Q2_TUNE_ADR25_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR25_ADDR,m,v,HWIO_Q2_TUNE_ADR25_IN)
#define HWIO_Q2_TUNE_ADR25_Q2_TUNE_ADR25_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR25_Q2_TUNE_ADR25_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT25_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x14c)
#define HWIO_Q2_TUNE_DAT25_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x14c)
#define HWIO_Q2_TUNE_DAT25_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT25_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT25_ADDR)
#define HWIO_Q2_TUNE_DAT25_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT25_ADDR, m)
#define HWIO_Q2_TUNE_DAT25_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT25_ADDR,v)
#define HWIO_Q2_TUNE_DAT25_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT25_ADDR,m,v,HWIO_Q2_TUNE_DAT25_IN)
#define HWIO_Q2_TUNE_DAT25_Q2_TUNE_DAT25_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT25_Q2_TUNE_DAT25_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR26_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x150)
#define HWIO_Q2_TUNE_ADR26_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x150)
#define HWIO_Q2_TUNE_ADR26_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR26_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR26_ADDR)
#define HWIO_Q2_TUNE_ADR26_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR26_ADDR, m)
#define HWIO_Q2_TUNE_ADR26_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR26_ADDR,v)
#define HWIO_Q2_TUNE_ADR26_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR26_ADDR,m,v,HWIO_Q2_TUNE_ADR26_IN)
#define HWIO_Q2_TUNE_ADR26_Q2_TUNE_ADR26_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR26_Q2_TUNE_ADR26_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT26_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x154)
#define HWIO_Q2_TUNE_DAT26_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x154)
#define HWIO_Q2_TUNE_DAT26_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT26_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT26_ADDR)
#define HWIO_Q2_TUNE_DAT26_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT26_ADDR, m)
#define HWIO_Q2_TUNE_DAT26_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT26_ADDR,v)
#define HWIO_Q2_TUNE_DAT26_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT26_ADDR,m,v,HWIO_Q2_TUNE_DAT26_IN)
#define HWIO_Q2_TUNE_DAT26_Q2_TUNE_DAT26_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT26_Q2_TUNE_DAT26_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR27_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x158)
#define HWIO_Q2_TUNE_ADR27_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x158)
#define HWIO_Q2_TUNE_ADR27_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR27_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR27_ADDR)
#define HWIO_Q2_TUNE_ADR27_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR27_ADDR, m)
#define HWIO_Q2_TUNE_ADR27_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR27_ADDR,v)
#define HWIO_Q2_TUNE_ADR27_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR27_ADDR,m,v,HWIO_Q2_TUNE_ADR27_IN)
#define HWIO_Q2_TUNE_ADR27_Q2_TUNE_ADR27_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR27_Q2_TUNE_ADR27_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT27_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x15c)
#define HWIO_Q2_TUNE_DAT27_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x15c)
#define HWIO_Q2_TUNE_DAT27_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT27_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT27_ADDR)
#define HWIO_Q2_TUNE_DAT27_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT27_ADDR, m)
#define HWIO_Q2_TUNE_DAT27_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT27_ADDR,v)
#define HWIO_Q2_TUNE_DAT27_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT27_ADDR,m,v,HWIO_Q2_TUNE_DAT27_IN)
#define HWIO_Q2_TUNE_DAT27_Q2_TUNE_DAT27_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT27_Q2_TUNE_DAT27_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR28_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x160)
#define HWIO_Q2_TUNE_ADR28_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x160)
#define HWIO_Q2_TUNE_ADR28_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR28_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR28_ADDR)
#define HWIO_Q2_TUNE_ADR28_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR28_ADDR, m)
#define HWIO_Q2_TUNE_ADR28_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR28_ADDR,v)
#define HWIO_Q2_TUNE_ADR28_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR28_ADDR,m,v,HWIO_Q2_TUNE_ADR28_IN)
#define HWIO_Q2_TUNE_ADR28_Q2_TUNE_ADR28_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR28_Q2_TUNE_ADR28_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT28_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x164)
#define HWIO_Q2_TUNE_DAT28_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x164)
#define HWIO_Q2_TUNE_DAT28_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT28_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT28_ADDR)
#define HWIO_Q2_TUNE_DAT28_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT28_ADDR, m)
#define HWIO_Q2_TUNE_DAT28_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT28_ADDR,v)
#define HWIO_Q2_TUNE_DAT28_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT28_ADDR,m,v,HWIO_Q2_TUNE_DAT28_IN)
#define HWIO_Q2_TUNE_DAT28_Q2_TUNE_DAT28_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT28_Q2_TUNE_DAT28_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR29_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x168)
#define HWIO_Q2_TUNE_ADR29_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x168)
#define HWIO_Q2_TUNE_ADR29_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR29_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR29_ADDR)
#define HWIO_Q2_TUNE_ADR29_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR29_ADDR, m)
#define HWIO_Q2_TUNE_ADR29_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR29_ADDR,v)
#define HWIO_Q2_TUNE_ADR29_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR29_ADDR,m,v,HWIO_Q2_TUNE_ADR29_IN)
#define HWIO_Q2_TUNE_ADR29_Q2_TUNE_ADR29_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR29_Q2_TUNE_ADR29_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT29_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x16c)
#define HWIO_Q2_TUNE_DAT29_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x16c)
#define HWIO_Q2_TUNE_DAT29_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT29_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT29_ADDR)
#define HWIO_Q2_TUNE_DAT29_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT29_ADDR, m)
#define HWIO_Q2_TUNE_DAT29_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT29_ADDR,v)
#define HWIO_Q2_TUNE_DAT29_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT29_ADDR,m,v,HWIO_Q2_TUNE_DAT29_IN)
#define HWIO_Q2_TUNE_DAT29_Q2_TUNE_DAT29_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT29_Q2_TUNE_DAT29_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR30_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x170)
#define HWIO_Q2_TUNE_ADR30_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x170)
#define HWIO_Q2_TUNE_ADR30_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR30_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR30_ADDR)
#define HWIO_Q2_TUNE_ADR30_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR30_ADDR, m)
#define HWIO_Q2_TUNE_ADR30_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR30_ADDR,v)
#define HWIO_Q2_TUNE_ADR30_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR30_ADDR,m,v,HWIO_Q2_TUNE_ADR30_IN)
#define HWIO_Q2_TUNE_ADR30_Q2_TUNE_ADR30_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR30_Q2_TUNE_ADR30_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT30_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x174)
#define HWIO_Q2_TUNE_DAT30_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x174)
#define HWIO_Q2_TUNE_DAT30_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT30_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT30_ADDR)
#define HWIO_Q2_TUNE_DAT30_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT30_ADDR, m)
#define HWIO_Q2_TUNE_DAT30_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT30_ADDR,v)
#define HWIO_Q2_TUNE_DAT30_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT30_ADDR,m,v,HWIO_Q2_TUNE_DAT30_IN)
#define HWIO_Q2_TUNE_DAT30_Q2_TUNE_DAT30_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT30_Q2_TUNE_DAT30_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_ADR31_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x178)
#define HWIO_Q2_TUNE_ADR31_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x178)
#define HWIO_Q2_TUNE_ADR31_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_ADR31_IN                    \
                in_dword(HWIO_Q2_TUNE_ADR31_ADDR)
#define HWIO_Q2_TUNE_ADR31_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_ADR31_ADDR, m)
#define HWIO_Q2_TUNE_ADR31_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_ADR31_ADDR,v)
#define HWIO_Q2_TUNE_ADR31_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_ADR31_ADDR,m,v,HWIO_Q2_TUNE_ADR31_IN)
#define HWIO_Q2_TUNE_ADR31_Q2_TUNE_ADR31_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_ADR31_Q2_TUNE_ADR31_7_0_SHFT                                                    0

#define HWIO_Q2_TUNE_DAT31_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x17c)
#define HWIO_Q2_TUNE_DAT31_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x17c)
#define HWIO_Q2_TUNE_DAT31_RMSK                                                                   0xff
#define HWIO_Q2_TUNE_DAT31_IN                    \
                in_dword(HWIO_Q2_TUNE_DAT31_ADDR)
#define HWIO_Q2_TUNE_DAT31_INM(m)            \
                in_dword_masked(HWIO_Q2_TUNE_DAT31_ADDR, m)
#define HWIO_Q2_TUNE_DAT31_OUT(v)            \
                out_dword(HWIO_Q2_TUNE_DAT31_ADDR,v)
#define HWIO_Q2_TUNE_DAT31_OUTM(m,v) \
                out_dword_masked_ns(HWIO_Q2_TUNE_DAT31_ADDR,m,v,HWIO_Q2_TUNE_DAT31_IN)
#define HWIO_Q2_TUNE_DAT31_Q2_TUNE_DAT31_7_0_BMSK                                                 0xff
#define HWIO_Q2_TUNE_DAT31_Q2_TUNE_DAT31_7_0_SHFT                                                    0

#define HWIO_EUD_EN_DELAY_LSB_ADDR                                                          (MODE_MANAGER_REG_BASE      + 0x180)
#define HWIO_EUD_EN_DELAY_LSB_PHYS                                                          (MODE_MANAGER_REG_BASE_PHYS + 0x180)
#define HWIO_EUD_EN_DELAY_LSB_RMSK                                                                0xff
#define HWIO_EUD_EN_DELAY_LSB_IN                    \
                in_dword(HWIO_EUD_EN_DELAY_LSB_ADDR)
#define HWIO_EUD_EN_DELAY_LSB_INM(m)            \
                in_dword_masked(HWIO_EUD_EN_DELAY_LSB_ADDR, m)
#define HWIO_EUD_EN_DELAY_LSB_OUT(v)            \
                out_dword(HWIO_EUD_EN_DELAY_LSB_ADDR,v)
#define HWIO_EUD_EN_DELAY_LSB_OUTM(m,v) \
                out_dword_masked_ns(HWIO_EUD_EN_DELAY_LSB_ADDR,m,v,HWIO_EUD_EN_DELAY_LSB_IN)
#define HWIO_EUD_EN_DELAY_LSB_EUD_EN_DELAY_LSB_7_0_BMSK                                           0xff
#define HWIO_EUD_EN_DELAY_LSB_EUD_EN_DELAY_LSB_7_0_SHFT                                              0

#define HWIO_EUD_EN_DELAY_MSB_ADDR                                                          (MODE_MANAGER_REG_BASE      + 0x184)
#define HWIO_EUD_EN_DELAY_MSB_PHYS                                                          (MODE_MANAGER_REG_BASE_PHYS + 0x184)
#define HWIO_EUD_EN_DELAY_MSB_RMSK                                                                0xff
#define HWIO_EUD_EN_DELAY_MSB_IN                    \
                in_dword(HWIO_EUD_EN_DELAY_MSB_ADDR)
#define HWIO_EUD_EN_DELAY_MSB_INM(m)            \
                in_dword_masked(HWIO_EUD_EN_DELAY_MSB_ADDR, m)
#define HWIO_EUD_EN_DELAY_MSB_OUT(v)            \
                out_dword(HWIO_EUD_EN_DELAY_MSB_ADDR,v)
#define HWIO_EUD_EN_DELAY_MSB_OUTM(m,v) \
                out_dword_masked_ns(HWIO_EUD_EN_DELAY_MSB_ADDR,m,v,HWIO_EUD_EN_DELAY_MSB_IN)
#define HWIO_EUD_EN_DELAY_MSB_EUD_EN_DELAY_MSB_7_0_BMSK                                           0xff
#define HWIO_EUD_EN_DELAY_MSB_EUD_EN_DELAY_MSB_7_0_SHFT                                              0

#define HWIO_MILLISEC_CNTR_ADDR                                                             (MODE_MANAGER_REG_BASE      + 0x188)
#define HWIO_MILLISEC_CNTR_PHYS                                                             (MODE_MANAGER_REG_BASE_PHYS + 0x188)
#define HWIO_MILLISEC_CNTR_RMSK                                                                   0xff
#define HWIO_MILLISEC_CNTR_IN                    \
                in_dword(HWIO_MILLISEC_CNTR_ADDR)
#define HWIO_MILLISEC_CNTR_INM(m)            \
                in_dword_masked(HWIO_MILLISEC_CNTR_ADDR, m)
#define HWIO_MILLISEC_CNTR_OUT(v)            \
                out_dword(HWIO_MILLISEC_CNTR_ADDR,v)
#define HWIO_MILLISEC_CNTR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_MILLISEC_CNTR_ADDR,m,v,HWIO_MILLISEC_CNTR_IN)
#define HWIO_MILLISEC_CNTR_MILLISEC_CNTR_7_0_BMSK                                                 0xff
#define HWIO_MILLISEC_CNTR_MILLISEC_CNTR_7_0_SHFT                                                    0

#define HWIO_CHIKNBIT_EN_DEL_CNTR_ADDR                                                      (MODE_MANAGER_REG_BASE      + 0x18c)
#define HWIO_CHIKNBIT_EN_DEL_CNTR_PHYS                                                      (MODE_MANAGER_REG_BASE_PHYS + 0x18c)
#define HWIO_CHIKNBIT_EN_DEL_CNTR_RMSK                                                             0x1
#define HWIO_CHIKNBIT_EN_DEL_CNTR_IN                    \
                in_dword(HWIO_CHIKNBIT_EN_DEL_CNTR_ADDR)
#define HWIO_CHIKNBIT_EN_DEL_CNTR_INM(m)            \
                in_dword_masked(HWIO_CHIKNBIT_EN_DEL_CNTR_ADDR, m)
#define HWIO_CHIKNBIT_EN_DEL_CNTR_OUT(v)            \
                out_dword(HWIO_CHIKNBIT_EN_DEL_CNTR_ADDR,v)
#define HWIO_CHIKNBIT_EN_DEL_CNTR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_CHIKNBIT_EN_DEL_CNTR_ADDR,m,v,HWIO_CHIKNBIT_EN_DEL_CNTR_IN)
#define HWIO_CHIKNBIT_EN_DEL_CNTR_CHIKNBIT_EN_DEL_CNTR_0_0_BMSK                                    0x1
#define HWIO_CHIKNBIT_EN_DEL_CNTR_CHIKNBIT_EN_DEL_CNTR_0_0_SHFT                                      0

/*----------------------------------------------------------------------------
 * MODULE: MODE_MANAGER2
 *--------------------------------------------------------------------------*/

#define MODE_MANAGER2_REG_BASE                 (AHB2PHY_NORTH_BASE      + 0x00002000)
#define MODE_MANAGER2_REG_BASE_SIZE            0x1000
#define MODE_MANAGER2_REG_BASE_USED            0x0
#define MODE_MANAGER2_REG_BASE_PHYS            (AHB2PHY_NORTH_BASE_PHYS + 0x00002000)

#define HWIO_EUD_EN2_ADDR                      (MODE_MANAGER2_REG_BASE      + 0x0)
#define HWIO_EUD_EN2_PHYS                      (MODE_MANAGER2_REG_BASE_PHYS + 0x0)
#define HWIO_EUD_EN2_RMSK                             0x1
#define HWIO_EUD_EN2_IN                    \
                in_dword(HWIO_EUD_EN2_ADDR)
#define HWIO_EUD_EN2_INM(m)            \
                in_dword_masked(HWIO_EUD_EN2_ADDR, m)
#define HWIO_EUD_EN2_OUT(v)            \
                out_dword(HWIO_EUD_EN2_ADDR,v)
#define HWIO_EUD_EN2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_EUD_EN2_ADDR,m,v,HWIO_EUD_EN2_IN)
#define HWIO_EUD_EN2_EUD_EN2_BMSK                     0x1
#define HWIO_EUD_EN2_EUD_EN2_SHFT                       0

/*----------------------------------------------------------------------------
 * MODULE: ACORE
 *--------------------------------------------------------------------------*/

#define ACORE_REG_BASE                                               (AHB2PHY_NORTH_BASE      + 0x00000000)
#define ACORE_REG_BASE_SIZE                                          0x1000
#define ACORE_REG_BASE_USED                                          0x240
#define ACORE_REG_BASE_PHYS                                          (AHB2PHY_NORTH_BASE_PHYS + 0x00000000)

#define HWIO_COM_TX_ID_ADDR                                          (ACORE_REG_BASE      + 0x0)
#define HWIO_COM_TX_ID_PHYS                                          (ACORE_REG_BASE_PHYS + 0x0)
#define HWIO_COM_TX_ID_RMSK                                                0xff
#define HWIO_COM_TX_ID_IN                    \
                in_dword(HWIO_COM_TX_ID_ADDR)
#define HWIO_COM_TX_ID_INM(m)            \
                in_dword_masked(HWIO_COM_TX_ID_ADDR, m)
#define HWIO_COM_TX_ID_OUT(v)            \
                out_dword(HWIO_COM_TX_ID_ADDR,v)
#define HWIO_COM_TX_ID_OUTM(m,v) \
                out_dword_masked_ns(HWIO_COM_TX_ID_ADDR,m,v,HWIO_COM_TX_ID_IN)
#define HWIO_COM_TX_ID_COM_TX_ID_7_0_BMSK                                  0xff
#define HWIO_COM_TX_ID_COM_TX_ID_7_0_SHFT                                     0

#define HWIO_COM_TX_LEN_ADDR                                         (ACORE_REG_BASE      + 0x4)
#define HWIO_COM_TX_LEN_PHYS                                         (ACORE_REG_BASE_PHYS + 0x4)
#define HWIO_COM_TX_LEN_RMSK                                               0xff
#define HWIO_COM_TX_LEN_IN                    \
                in_dword(HWIO_COM_TX_LEN_ADDR)
#define HWIO_COM_TX_LEN_INM(m)            \
                in_dword_masked(HWIO_COM_TX_LEN_ADDR, m)
#define HWIO_COM_TX_LEN_OUT(v)            \
                out_dword(HWIO_COM_TX_LEN_ADDR,v)
#define HWIO_COM_TX_LEN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_COM_TX_LEN_ADDR,m,v,HWIO_COM_TX_LEN_IN)
#define HWIO_COM_TX_LEN_COM_TX_LEN_7_0_BMSK                                0xff
#define HWIO_COM_TX_LEN_COM_TX_LEN_7_0_SHFT                                   0

#define HWIO_COM_TX_DAT_ADDR                                         (ACORE_REG_BASE      + 0x8)
#define HWIO_COM_TX_DAT_PHYS                                         (ACORE_REG_BASE_PHYS + 0x8)
#define HWIO_COM_TX_DAT_RMSK                                               0xff
#define HWIO_COM_TX_DAT_IN                    \
                in_dword(HWIO_COM_TX_DAT_ADDR)
#define HWIO_COM_TX_DAT_INM(m)            \
                in_dword_masked(HWIO_COM_TX_DAT_ADDR, m)
#define HWIO_COM_TX_DAT_OUT(v)            \
                out_dword(HWIO_COM_TX_DAT_ADDR,v)
#define HWIO_COM_TX_DAT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_COM_TX_DAT_ADDR,m,v,HWIO_COM_TX_DAT_IN)
#define HWIO_COM_TX_DAT_COM_TX_DAT_7_0_BMSK                                0xff
#define HWIO_COM_TX_DAT_COM_TX_DAT_7_0_SHFT                                   0

#define HWIO_COM_RX_ID_ADDR                                          (ACORE_REG_BASE      + 0xc)
#define HWIO_COM_RX_ID_PHYS                                          (ACORE_REG_BASE_PHYS + 0xc)
#define HWIO_COM_RX_ID_RMSK                                                0xff
#define HWIO_COM_RX_ID_IN                    \
                in_dword(HWIO_COM_RX_ID_ADDR)
#define HWIO_COM_RX_ID_INM(m)            \
                in_dword_masked(HWIO_COM_RX_ID_ADDR, m)
#define HWIO_COM_RX_ID_COM_RX_ID_7_0_BMSK                                  0xff
#define HWIO_COM_RX_ID_COM_RX_ID_7_0_SHFT                                     0

#define HWIO_COM_RX_LEN_ADDR                                         (ACORE_REG_BASE      + 0x10)
#define HWIO_COM_RX_LEN_PHYS                                         (ACORE_REG_BASE_PHYS + 0x10)
#define HWIO_COM_RX_LEN_RMSK                                               0xff
#define HWIO_COM_RX_LEN_IN                    \
                in_dword(HWIO_COM_RX_LEN_ADDR)
#define HWIO_COM_RX_LEN_INM(m)            \
                in_dword_masked(HWIO_COM_RX_LEN_ADDR, m)
#define HWIO_COM_RX_LEN_COM_RX_LEN_7_0_BMSK                                0xff
#define HWIO_COM_RX_LEN_COM_RX_LEN_7_0_SHFT                                   0

#define HWIO_COM_RX_DATA_ADDR                                        (ACORE_REG_BASE      + 0x14)
#define HWIO_COM_RX_DATA_PHYS                                        (ACORE_REG_BASE_PHYS + 0x14)
#define HWIO_COM_RX_DATA_RMSK                                              0xff
#define HWIO_COM_RX_DATA_IN                    \
                in_dword(HWIO_COM_RX_DATA_ADDR)
#define HWIO_COM_RX_DATA_INM(m)            \
                in_dword_masked(HWIO_COM_RX_DATA_ADDR, m)
#define HWIO_COM_RX_DATA_COM_RX_DATA_7_0_BMSK                              0xff
#define HWIO_COM_RX_DATA_COM_RX_DATA_7_0_SHFT                                 0

#define HWIO_INT0_EN_MASK_ADDR                                       (ACORE_REG_BASE      + 0x20)
#define HWIO_INT0_EN_MASK_PHYS                                       (ACORE_REG_BASE_PHYS + 0x20)
#define HWIO_INT0_EN_MASK_RMSK                                             0xff
#define HWIO_INT0_EN_MASK_IN                    \
                in_dword(HWIO_INT0_EN_MASK_ADDR)
#define HWIO_INT0_EN_MASK_INM(m)            \
                in_dword_masked(HWIO_INT0_EN_MASK_ADDR, m)
#define HWIO_INT0_EN_MASK_OUT(v)            \
                out_dword(HWIO_INT0_EN_MASK_ADDR,v)
#define HWIO_INT0_EN_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_INT0_EN_MASK_ADDR,m,v,HWIO_INT0_EN_MASK_IN)
#define HWIO_INT0_EN_MASK_INT0_EN_MASK_7_0_BMSK                            0xff
#define HWIO_INT0_EN_MASK_INT0_EN_MASK_7_0_SHFT                               0

#define HWIO_INT1_EN_MASK_ADDR                                       (ACORE_REG_BASE      + 0x24)
#define HWIO_INT1_EN_MASK_PHYS                                       (ACORE_REG_BASE_PHYS + 0x24)
#define HWIO_INT1_EN_MASK_RMSK                                             0xff
#define HWIO_INT1_EN_MASK_IN                    \
                in_dword(HWIO_INT1_EN_MASK_ADDR)
#define HWIO_INT1_EN_MASK_INM(m)            \
                in_dword_masked(HWIO_INT1_EN_MASK_ADDR, m)
#define HWIO_INT1_EN_MASK_OUT(v)            \
                out_dword(HWIO_INT1_EN_MASK_ADDR,v)
#define HWIO_INT1_EN_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_INT1_EN_MASK_ADDR,m,v,HWIO_INT1_EN_MASK_IN)
#define HWIO_INT1_EN_MASK_INT1_EN_MASK_7_0_BMSK                            0xff
#define HWIO_INT1_EN_MASK_INT1_EN_MASK_7_0_SHFT                               0

#define HWIO_INT2_EN_MASK_ADDR                                       (ACORE_REG_BASE      + 0x28)
#define HWIO_INT2_EN_MASK_PHYS                                       (ACORE_REG_BASE_PHYS + 0x28)
#define HWIO_INT2_EN_MASK_RMSK                                             0xff
#define HWIO_INT2_EN_MASK_IN                    \
                in_dword(HWIO_INT2_EN_MASK_ADDR)
#define HWIO_INT2_EN_MASK_INM(m)            \
                in_dword_masked(HWIO_INT2_EN_MASK_ADDR, m)
#define HWIO_INT2_EN_MASK_OUT(v)            \
                out_dword(HWIO_INT2_EN_MASK_ADDR,v)
#define HWIO_INT2_EN_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_INT2_EN_MASK_ADDR,m,v,HWIO_INT2_EN_MASK_IN)
#define HWIO_INT2_EN_MASK_INT2_EN_MASK_7_0_BMSK                            0xff
#define HWIO_INT2_EN_MASK_INT2_EN_MASK_7_0_SHFT                               0

#define HWIO_INT3_EN_MASK_ADDR                                       (ACORE_REG_BASE      + 0x2c)
#define HWIO_INT3_EN_MASK_PHYS                                       (ACORE_REG_BASE_PHYS + 0x2c)
#define HWIO_INT3_EN_MASK_RMSK                                             0xff
#define HWIO_INT3_EN_MASK_IN                    \
                in_dword(HWIO_INT3_EN_MASK_ADDR)
#define HWIO_INT3_EN_MASK_INM(m)            \
                in_dword_masked(HWIO_INT3_EN_MASK_ADDR, m)
#define HWIO_INT3_EN_MASK_OUT(v)            \
                out_dword(HWIO_INT3_EN_MASK_ADDR,v)
#define HWIO_INT3_EN_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_INT3_EN_MASK_ADDR,m,v,HWIO_INT3_EN_MASK_IN)
#define HWIO_INT3_EN_MASK_INT3_EN_MASK_7_0_BMSK                            0xff
#define HWIO_INT3_EN_MASK_INT3_EN_MASK_7_0_SHFT                               0

#define HWIO_INT4_EN_MASK_ADDR                                       (ACORE_REG_BASE      + 0x30)
#define HWIO_INT4_EN_MASK_PHYS                                       (ACORE_REG_BASE_PHYS + 0x30)
#define HWIO_INT4_EN_MASK_RMSK                                             0xff
#define HWIO_INT4_EN_MASK_IN                    \
                in_dword(HWIO_INT4_EN_MASK_ADDR)
#define HWIO_INT4_EN_MASK_INM(m)            \
                in_dword_masked(HWIO_INT4_EN_MASK_ADDR, m)
#define HWIO_INT4_EN_MASK_OUT(v)            \
                out_dword(HWIO_INT4_EN_MASK_ADDR,v)
#define HWIO_INT4_EN_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_INT4_EN_MASK_ADDR,m,v,HWIO_INT4_EN_MASK_IN)
#define HWIO_INT4_EN_MASK_INT4_EN_MASK_7_0_BMSK                            0xff
#define HWIO_INT4_EN_MASK_INT4_EN_MASK_7_0_SHFT                               0

#define HWIO_INT5_EN_MASK_ADDR                                       (ACORE_REG_BASE      + 0x34)
#define HWIO_INT5_EN_MASK_PHYS                                       (ACORE_REG_BASE_PHYS + 0x34)
#define HWIO_INT5_EN_MASK_RMSK                                             0xff
#define HWIO_INT5_EN_MASK_IN                    \
                in_dword(HWIO_INT5_EN_MASK_ADDR)
#define HWIO_INT5_EN_MASK_INM(m)            \
                in_dword_masked(HWIO_INT5_EN_MASK_ADDR, m)
#define HWIO_INT5_EN_MASK_OUT(v)            \
                out_dword(HWIO_INT5_EN_MASK_ADDR,v)
#define HWIO_INT5_EN_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_INT5_EN_MASK_ADDR,m,v,HWIO_INT5_EN_MASK_IN)
#define HWIO_INT5_EN_MASK_INT5_EN_MASK_7_0_BMSK                            0xff
#define HWIO_INT5_EN_MASK_INT5_EN_MASK_7_0_SHFT                               0

#define HWIO_INT6_EN_MASK_ADDR                                       (ACORE_REG_BASE      + 0x38)
#define HWIO_INT6_EN_MASK_PHYS                                       (ACORE_REG_BASE_PHYS + 0x38)
#define HWIO_INT6_EN_MASK_RMSK                                             0xff
#define HWIO_INT6_EN_MASK_IN                    \
                in_dword(HWIO_INT6_EN_MASK_ADDR)
#define HWIO_INT6_EN_MASK_INM(m)            \
                in_dword_masked(HWIO_INT6_EN_MASK_ADDR, m)
#define HWIO_INT6_EN_MASK_OUT(v)            \
                out_dword(HWIO_INT6_EN_MASK_ADDR,v)
#define HWIO_INT6_EN_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_INT6_EN_MASK_ADDR,m,v,HWIO_INT6_EN_MASK_IN)
#define HWIO_INT6_EN_MASK_INT6_EN_MASK_7_0_BMSK                            0xff
#define HWIO_INT6_EN_MASK_INT6_EN_MASK_7_0_SHFT                               0

#define HWIO_INT7_EN_MASK_ADDR                                       (ACORE_REG_BASE      + 0x3c)
#define HWIO_INT7_EN_MASK_PHYS                                       (ACORE_REG_BASE_PHYS + 0x3c)
#define HWIO_INT7_EN_MASK_RMSK                                             0xff
#define HWIO_INT7_EN_MASK_IN                    \
                in_dword(HWIO_INT7_EN_MASK_ADDR)
#define HWIO_INT7_EN_MASK_INM(m)            \
                in_dword_masked(HWIO_INT7_EN_MASK_ADDR, m)
#define HWIO_INT7_EN_MASK_OUT(v)            \
                out_dword(HWIO_INT7_EN_MASK_ADDR,v)
#define HWIO_INT7_EN_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_INT7_EN_MASK_ADDR,m,v,HWIO_INT7_EN_MASK_IN)
#define HWIO_INT7_EN_MASK_INT7_EN_MASK_7_0_BMSK                            0xff
#define HWIO_INT7_EN_MASK_INT7_EN_MASK_7_0_SHFT                               0

#define HWIO_INT_STATUS_0_ADDR                                       (ACORE_REG_BASE      + 0x40)
#define HWIO_INT_STATUS_0_PHYS                                       (ACORE_REG_BASE_PHYS + 0x40)
#define HWIO_INT_STATUS_0_RMSK                                             0xff
#define HWIO_INT_STATUS_0_IN                    \
                in_dword(HWIO_INT_STATUS_0_ADDR)
#define HWIO_INT_STATUS_0_INM(m)            \
                in_dword_masked(HWIO_INT_STATUS_0_ADDR, m)
#define HWIO_INT_STATUS_0_INT_STATUS_7_0_BMSK                              0xff
#define HWIO_INT_STATUS_0_INT_STATUS_7_0_SHFT                                 0

#define HWIO_INT_STATUS_1_ADDR                                       (ACORE_REG_BASE      + 0x44)
#define HWIO_INT_STATUS_1_PHYS                                       (ACORE_REG_BASE_PHYS + 0x44)
#define HWIO_INT_STATUS_1_RMSK                                             0xff
#define HWIO_INT_STATUS_1_IN                    \
                in_dword(HWIO_INT_STATUS_1_ADDR)
#define HWIO_INT_STATUS_1_INM(m)            \
                in_dword_masked(HWIO_INT_STATUS_1_ADDR, m)
#define HWIO_INT_STATUS_1_INT_STATUS_7_0_BMSK                              0xff
#define HWIO_INT_STATUS_1_INT_STATUS_7_0_SHFT                                 0

#define HWIO_FLAG_IN_WR_ADDR                                         (ACORE_REG_BASE      + 0x50)
#define HWIO_FLAG_IN_WR_PHYS                                         (ACORE_REG_BASE_PHYS + 0x50)
#define HWIO_FLAG_IN_WR_RMSK                                               0xff
#define HWIO_FLAG_IN_WR_IN                    \
                in_dword(HWIO_FLAG_IN_WR_ADDR)
#define HWIO_FLAG_IN_WR_INM(m)            \
                in_dword_masked(HWIO_FLAG_IN_WR_ADDR, m)
#define HWIO_FLAG_IN_WR_OUT(v)            \
                out_dword(HWIO_FLAG_IN_WR_ADDR,v)
#define HWIO_FLAG_IN_WR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_FLAG_IN_WR_ADDR,m,v,HWIO_FLAG_IN_WR_IN)
#define HWIO_FLAG_IN_WR_FLAG_IN_WR_7_0_BMSK                                0xff
#define HWIO_FLAG_IN_WR_FLAG_IN_WR_7_0_SHFT                                   0

#define HWIO_FLAG_IN_SET_ADDR                                        (ACORE_REG_BASE      + 0x54)
#define HWIO_FLAG_IN_SET_PHYS                                        (ACORE_REG_BASE_PHYS + 0x54)
#define HWIO_FLAG_IN_SET_RMSK                                              0xff
#define HWIO_FLAG_IN_SET_OUT(v)            \
                out_dword(HWIO_FLAG_IN_SET_ADDR,v)
#define HWIO_FLAG_IN_SET_FLAG_IN_SET_7_0_BMSK                              0xff
#define HWIO_FLAG_IN_SET_FLAG_IN_SET_7_0_SHFT                                 0

#define HWIO_FLAG_IN_CLR_ADDR                                        (ACORE_REG_BASE      + 0x58)
#define HWIO_FLAG_IN_CLR_PHYS                                        (ACORE_REG_BASE_PHYS + 0x58)
#define HWIO_FLAG_IN_CLR_RMSK                                              0xff
#define HWIO_FLAG_IN_CLR_OUT(v)            \
                out_dword(HWIO_FLAG_IN_CLR_ADDR,v)
#define HWIO_FLAG_IN_CLR_FLAG_IN_CLR_7_0_BMSK                              0xff
#define HWIO_FLAG_IN_CLR_FLAG_IN_CLR_7_0_SHFT                                 0

#define HWIO_FLAG_OUT_ADDR                                           (ACORE_REG_BASE      + 0x5c)
#define HWIO_FLAG_OUT_PHYS                                           (ACORE_REG_BASE_PHYS + 0x5c)
#define HWIO_FLAG_OUT_RMSK                                                 0xff
#define HWIO_FLAG_OUT_IN                    \
                in_dword(HWIO_FLAG_OUT_ADDR)
#define HWIO_FLAG_OUT_INM(m)            \
                in_dword_masked(HWIO_FLAG_OUT_ADDR, m)
#define HWIO_FLAG_OUT_FLAG_OUT_7_0_BMSK                                    0xff
#define HWIO_FLAG_OUT_FLAG_OUT_7_0_SHFT                                       0

#define HWIO_CTL_IN_0_ADDR                                           (ACORE_REG_BASE      + 0x60)
#define HWIO_CTL_IN_0_PHYS                                           (ACORE_REG_BASE_PHYS + 0x60)
#define HWIO_CTL_IN_0_RMSK                                                 0xff
#define HWIO_CTL_IN_0_IN                    \
                in_dword(HWIO_CTL_IN_0_ADDR)
#define HWIO_CTL_IN_0_INM(m)            \
                in_dword_masked(HWIO_CTL_IN_0_ADDR, m)
#define HWIO_CTL_IN_0_CTL_IN_0_7_0_BMSK                                    0xff
#define HWIO_CTL_IN_0_CTL_IN_0_7_0_SHFT                                       0

#define HWIO_CTL_IN_1_ADDR                                           (ACORE_REG_BASE      + 0x64)
#define HWIO_CTL_IN_1_PHYS                                           (ACORE_REG_BASE_PHYS + 0x64)
#define HWIO_CTL_IN_1_RMSK                                                 0xff
#define HWIO_CTL_IN_1_IN                    \
                in_dword(HWIO_CTL_IN_1_ADDR)
#define HWIO_CTL_IN_1_INM(m)            \
                in_dword_masked(HWIO_CTL_IN_1_ADDR, m)
#define HWIO_CTL_IN_1_CTL_IN_1_7_0_BMSK                                    0xff
#define HWIO_CTL_IN_1_CTL_IN_1_7_0_SHFT                                       0

#define HWIO_CTL_IN_2_ADDR                                           (ACORE_REG_BASE      + 0x68)
#define HWIO_CTL_IN_2_PHYS                                           (ACORE_REG_BASE_PHYS + 0x68)
#define HWIO_CTL_IN_2_RMSK                                                 0xff
#define HWIO_CTL_IN_2_IN                    \
                in_dword(HWIO_CTL_IN_2_ADDR)
#define HWIO_CTL_IN_2_INM(m)            \
                in_dword_masked(HWIO_CTL_IN_2_ADDR, m)
#define HWIO_CTL_IN_2_CTL_IN_2_7_0_BMSK                                    0xff
#define HWIO_CTL_IN_2_CTL_IN_2_7_0_SHFT                                       0

#define HWIO_CTL_IN_3_ADDR                                           (ACORE_REG_BASE      + 0x6c)
#define HWIO_CTL_IN_3_PHYS                                           (ACORE_REG_BASE_PHYS + 0x6c)
#define HWIO_CTL_IN_3_RMSK                                                 0xff
#define HWIO_CTL_IN_3_IN                    \
                in_dword(HWIO_CTL_IN_3_ADDR)
#define HWIO_CTL_IN_3_INM(m)            \
                in_dword_masked(HWIO_CTL_IN_3_ADDR, m)
#define HWIO_CTL_IN_3_CTL_IN_3_7_0_BMSK                                    0xff
#define HWIO_CTL_IN_3_CTL_IN_3_7_0_SHFT                                       0

#define HWIO_CTL_OUT_0_ADDR                                          (ACORE_REG_BASE      + 0x70)
#define HWIO_CTL_OUT_0_PHYS                                          (ACORE_REG_BASE_PHYS + 0x70)
#define HWIO_CTL_OUT_0_RMSK                                                0xff
#define HWIO_CTL_OUT_0_IN                    \
                in_dword(HWIO_CTL_OUT_0_ADDR)
#define HWIO_CTL_OUT_0_INM(m)            \
                in_dword_masked(HWIO_CTL_OUT_0_ADDR, m)
#define HWIO_CTL_OUT_0_CTL_OUT_0_7_0_BMSK                                  0xff
#define HWIO_CTL_OUT_0_CTL_OUT_0_7_0_SHFT                                     0

#define HWIO_CTL_OUT_1_ADDR                                          (ACORE_REG_BASE      + 0x74)
#define HWIO_CTL_OUT_1_PHYS                                          (ACORE_REG_BASE_PHYS + 0x74)
#define HWIO_CTL_OUT_1_RMSK                                                0xff
#define HWIO_CTL_OUT_1_IN                    \
                in_dword(HWIO_CTL_OUT_1_ADDR)
#define HWIO_CTL_OUT_1_INM(m)            \
                in_dword_masked(HWIO_CTL_OUT_1_ADDR, m)
#define HWIO_CTL_OUT_1_CTL_OUT_1_7_0_BMSK                                  0xff
#define HWIO_CTL_OUT_1_CTL_OUT_1_7_0_SHFT                                     0

#define HWIO_CTL_OUT_2_ADDR                                          (ACORE_REG_BASE      + 0x78)
#define HWIO_CTL_OUT_2_PHYS                                          (ACORE_REG_BASE_PHYS + 0x78)
#define HWIO_CTL_OUT_2_RMSK                                                0xff
#define HWIO_CTL_OUT_2_IN                    \
                in_dword(HWIO_CTL_OUT_2_ADDR)
#define HWIO_CTL_OUT_2_INM(m)            \
                in_dword_masked(HWIO_CTL_OUT_2_ADDR, m)
#define HWIO_CTL_OUT_2_CTL_OUT_2_7_0_BMSK                                  0xff
#define HWIO_CTL_OUT_2_CTL_OUT_2_7_0_SHFT                                     0

#define HWIO_CTL_OUT_3_ADDR                                          (ACORE_REG_BASE      + 0x7c)
#define HWIO_CTL_OUT_3_PHYS                                          (ACORE_REG_BASE_PHYS + 0x7c)
#define HWIO_CTL_OUT_3_RMSK                                                0xff
#define HWIO_CTL_OUT_3_IN                    \
                in_dword(HWIO_CTL_OUT_3_ADDR)
#define HWIO_CTL_OUT_3_INM(m)            \
                in_dword_masked(HWIO_CTL_OUT_3_ADDR, m)
#define HWIO_CTL_OUT_3_CTL_OUT_3_7_0_BMSK                                  0xff
#define HWIO_CTL_OUT_3_CTL_OUT_3_7_0_SHFT                                     0

#define HWIO_VBUS_INT_CLR_ADDR                                       (ACORE_REG_BASE      + 0x80)
#define HWIO_VBUS_INT_CLR_PHYS                                       (ACORE_REG_BASE_PHYS + 0x80)
#define HWIO_VBUS_INT_CLR_RMSK                                              0x1
#define HWIO_VBUS_INT_CLR_OUT(v)            \
                out_dword(HWIO_VBUS_INT_CLR_ADDR,v)
#define HWIO_VBUS_INT_CLR_VBUS_INT_CLR_0_0_BMSK                             0x1
#define HWIO_VBUS_INT_CLR_VBUS_INT_CLR_0_0_SHFT                               0

#define HWIO_CHGR_INT_CLR_ADDR                                       (ACORE_REG_BASE      + 0x84)
#define HWIO_CHGR_INT_CLR_PHYS                                       (ACORE_REG_BASE_PHYS + 0x84)
#define HWIO_CHGR_INT_CLR_RMSK                                              0x1
#define HWIO_CHGR_INT_CLR_OUT(v)            \
                out_dword(HWIO_CHGR_INT_CLR_ADDR,v)
#define HWIO_CHGR_INT_CLR_CHGR_INT_CLR_0_0_BMSK                             0x1
#define HWIO_CHGR_INT_CLR_CHGR_INT_CLR_0_0_SHFT                               0

#define HWIO_COM_EUD_VER0_ADDR                                       (ACORE_REG_BASE      + 0x200)
#define HWIO_COM_EUD_VER0_PHYS                                       (ACORE_REG_BASE_PHYS + 0x200)
#define HWIO_COM_EUD_VER0_RMSK                                             0xff
#define HWIO_COM_EUD_VER0_IN                    \
                in_dword(HWIO_COM_EUD_VER0_ADDR)
#define HWIO_COM_EUD_VER0_INM(m)            \
                in_dword_masked(HWIO_COM_EUD_VER0_ADDR, m)
#define HWIO_COM_EUD_VER0_COM_EUD_VERSION_7_0_BMSK                         0xff
#define HWIO_COM_EUD_VER0_COM_EUD_VERSION_7_0_SHFT                            0

#define HWIO_COM_EUD_VER1_ADDR                                       (ACORE_REG_BASE      + 0x204)
#define HWIO_COM_EUD_VER1_PHYS                                       (ACORE_REG_BASE_PHYS + 0x204)
#define HWIO_COM_EUD_VER1_RMSK                                             0xff
#define HWIO_COM_EUD_VER1_IN                    \
                in_dword(HWIO_COM_EUD_VER1_ADDR)
#define HWIO_COM_EUD_VER1_INM(m)            \
                in_dword_masked(HWIO_COM_EUD_VER1_ADDR, m)
#define HWIO_COM_EUD_VER1_COM_EUD_VERSION_7_0_BMSK                         0xff
#define HWIO_COM_EUD_VER1_COM_EUD_VERSION_7_0_SHFT                            0

#define HWIO_COM_EUD_VER2_ADDR                                       (ACORE_REG_BASE      + 0x208)
#define HWIO_COM_EUD_VER2_PHYS                                       (ACORE_REG_BASE_PHYS + 0x208)
#define HWIO_COM_EUD_VER2_RMSK                                             0xff
#define HWIO_COM_EUD_VER2_IN                    \
                in_dword(HWIO_COM_EUD_VER2_ADDR)
#define HWIO_COM_EUD_VER2_INM(m)            \
                in_dword_masked(HWIO_COM_EUD_VER2_ADDR, m)
#define HWIO_COM_EUD_VER2_COM_EUD_VERSION_7_0_BMSK                         0xff
#define HWIO_COM_EUD_VER2_COM_EUD_VERSION_7_0_SHFT                            0

#define HWIO_COM_EUD_VER3_ADDR                                       (ACORE_REG_BASE      + 0x20c)
#define HWIO_COM_EUD_VER3_PHYS                                       (ACORE_REG_BASE_PHYS + 0x20c)
#define HWIO_COM_EUD_VER3_RMSK                                             0xff
#define HWIO_COM_EUD_VER3_IN                    \
                in_dword(HWIO_COM_EUD_VER3_ADDR)
#define HWIO_COM_EUD_VER3_INM(m)            \
                in_dword_masked(HWIO_COM_EUD_VER3_ADDR, m)
#define HWIO_COM_EUD_VER3_COM_EUD_VERSION_7_0_BMSK                         0xff
#define HWIO_COM_EUD_VER3_COM_EUD_VERSION_7_0_SHFT                            0

#define HWIO_DBG_MUX_SEL_ADDR                                        (ACORE_REG_BASE      + 0x214)
#define HWIO_DBG_MUX_SEL_PHYS                                        (ACORE_REG_BASE_PHYS + 0x214)
#define HWIO_DBG_MUX_SEL_RMSK                                              0xff
#define HWIO_DBG_MUX_SEL_IN                    \
                in_dword(HWIO_DBG_MUX_SEL_ADDR)
#define HWIO_DBG_MUX_SEL_INM(m)            \
                in_dword_masked(HWIO_DBG_MUX_SEL_ADDR, m)
#define HWIO_DBG_MUX_SEL_OUT(v)            \
                out_dword(HWIO_DBG_MUX_SEL_ADDR,v)
#define HWIO_DBG_MUX_SEL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_DBG_MUX_SEL_ADDR,m,v,HWIO_DBG_MUX_SEL_IN)
#define HWIO_DBG_MUX_SEL_DBG_MUX_SEL_7_0_BMSK                              0xff
#define HWIO_DBG_MUX_SEL_DBG_MUX_SEL_7_0_SHFT                                 0

#define HWIO_TIE_HIGH_TIE_LOW_ADDR                                   (ACORE_REG_BASE      + 0x218)
#define HWIO_TIE_HIGH_TIE_LOW_PHYS                                   (ACORE_REG_BASE_PHYS + 0x218)
#define HWIO_TIE_HIGH_TIE_LOW_RMSK                                         0xff
#define HWIO_TIE_HIGH_TIE_LOW_IN                    \
                in_dword(HWIO_TIE_HIGH_TIE_LOW_ADDR)
#define HWIO_TIE_HIGH_TIE_LOW_INM(m)            \
                in_dword_masked(HWIO_TIE_HIGH_TIE_LOW_ADDR, m)
#define HWIO_TIE_HIGH_TIE_LOW_TIE_HIGH_TIE_LOW_1_0_BMSK                    0xff
#define HWIO_TIE_HIGH_TIE_LOW_TIE_HIGH_TIE_LOW_1_0_SHFT                       0

#define HWIO_CHIKNBIT_DBG_RD_ADDR                                    (ACORE_REG_BASE      + 0x21c)
#define HWIO_CHIKNBIT_DBG_RD_PHYS                                    (ACORE_REG_BASE_PHYS + 0x21c)
#define HWIO_CHIKNBIT_DBG_RD_RMSK                                          0xff
#define HWIO_CHIKNBIT_DBG_RD_IN                    \
                in_dword(HWIO_CHIKNBIT_DBG_RD_ADDR)
#define HWIO_CHIKNBIT_DBG_RD_INM(m)            \
                in_dword_masked(HWIO_CHIKNBIT_DBG_RD_ADDR, m)
#define HWIO_CHIKNBIT_DBG_RD_OUT(v)            \
                out_dword(HWIO_CHIKNBIT_DBG_RD_ADDR,v)
#define HWIO_CHIKNBIT_DBG_RD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_CHIKNBIT_DBG_RD_ADDR,m,v,HWIO_CHIKNBIT_DBG_RD_IN)
#define HWIO_CHIKNBIT_DBG_RD_CHIKNBIT_DBG_RD_7_0_BMSK                      0xff
#define HWIO_CHIKNBIT_DBG_RD_CHIKNBIT_DBG_RD_7_0_SHFT                         0

#define HWIO_DBG_DAT_REG0_ADDR                                       (ACORE_REG_BASE      + 0x220)
#define HWIO_DBG_DAT_REG0_PHYS                                       (ACORE_REG_BASE_PHYS + 0x220)
#define HWIO_DBG_DAT_REG0_RMSK                                             0xff
#define HWIO_DBG_DAT_REG0_IN                    \
                in_dword(HWIO_DBG_DAT_REG0_ADDR)
#define HWIO_DBG_DAT_REG0_INM(m)            \
                in_dword_masked(HWIO_DBG_DAT_REG0_ADDR, m)
#define HWIO_DBG_DAT_REG0_DBG_DAT_REG0_7_0_BMSK                            0xff
#define HWIO_DBG_DAT_REG0_DBG_DAT_REG0_7_0_SHFT                               0

#define HWIO_DBG_DAT_REG1_ADDR                                       (ACORE_REG_BASE      + 0x224)
#define HWIO_DBG_DAT_REG1_PHYS                                       (ACORE_REG_BASE_PHYS + 0x224)
#define HWIO_DBG_DAT_REG1_RMSK                                             0xff
#define HWIO_DBG_DAT_REG1_IN                    \
                in_dword(HWIO_DBG_DAT_REG1_ADDR)
#define HWIO_DBG_DAT_REG1_INM(m)            \
                in_dword_masked(HWIO_DBG_DAT_REG1_ADDR, m)
#define HWIO_DBG_DAT_REG1_DBG_DAT_REG1_7_0_BMSK                            0xff
#define HWIO_DBG_DAT_REG1_DBG_DAT_REG1_7_0_SHFT                               0

#define HWIO_DBG_DAT_REG2_ADDR                                       (ACORE_REG_BASE      + 0x228)
#define HWIO_DBG_DAT_REG2_PHYS                                       (ACORE_REG_BASE_PHYS + 0x228)
#define HWIO_DBG_DAT_REG2_RMSK                                             0xff
#define HWIO_DBG_DAT_REG2_IN                    \
                in_dword(HWIO_DBG_DAT_REG2_ADDR)
#define HWIO_DBG_DAT_REG2_INM(m)            \
                in_dword_masked(HWIO_DBG_DAT_REG2_ADDR, m)
#define HWIO_DBG_DAT_REG2_DBG_DAT_REG2_7_0_BMSK                            0xff
#define HWIO_DBG_DAT_REG2_DBG_DAT_REG2_7_0_SHFT                               0

#define HWIO_DBG_DAT_REG3_ADDR                                       (ACORE_REG_BASE      + 0x22c)
#define HWIO_DBG_DAT_REG3_PHYS                                       (ACORE_REG_BASE_PHYS + 0x22c)
#define HWIO_DBG_DAT_REG3_RMSK                                             0xff
#define HWIO_DBG_DAT_REG3_IN                    \
                in_dword(HWIO_DBG_DAT_REG3_ADDR)
#define HWIO_DBG_DAT_REG3_INM(m)            \
                in_dword_masked(HWIO_DBG_DAT_REG3_ADDR, m)
#define HWIO_DBG_DAT_REG3_DBG_DAT_REG3_7_0_BMSK                            0xff
#define HWIO_DBG_DAT_REG3_DBG_DAT_REG3_7_0_SHFT                               0

#define HWIO_DBG_DAT_REG4_ADDR                                       (ACORE_REG_BASE      + 0x230)
#define HWIO_DBG_DAT_REG4_PHYS                                       (ACORE_REG_BASE_PHYS + 0x230)
#define HWIO_DBG_DAT_REG4_RMSK                                             0xff
#define HWIO_DBG_DAT_REG4_IN                    \
                in_dword(HWIO_DBG_DAT_REG4_ADDR)
#define HWIO_DBG_DAT_REG4_INM(m)            \
                in_dword_masked(HWIO_DBG_DAT_REG4_ADDR, m)
#define HWIO_DBG_DAT_REG4_DBG_DAT_REG4_7_0_BMSK                            0xff
#define HWIO_DBG_DAT_REG4_DBG_DAT_REG4_7_0_SHFT                               0

#define HWIO_DBG_DAT_REG5_ADDR                                       (ACORE_REG_BASE      + 0x234)
#define HWIO_DBG_DAT_REG5_PHYS                                       (ACORE_REG_BASE_PHYS + 0x234)
#define HWIO_DBG_DAT_REG5_RMSK                                             0xff
#define HWIO_DBG_DAT_REG5_IN                    \
                in_dword(HWIO_DBG_DAT_REG5_ADDR)
#define HWIO_DBG_DAT_REG5_INM(m)            \
                in_dword_masked(HWIO_DBG_DAT_REG5_ADDR, m)
#define HWIO_DBG_DAT_REG5_DBG_DAT_REG5_7_0_BMSK                            0xff
#define HWIO_DBG_DAT_REG5_DBG_DAT_REG5_7_0_SHFT                               0

#define HWIO_DBG_DAT_REG6_ADDR                                       (ACORE_REG_BASE      + 0x238)
#define HWIO_DBG_DAT_REG6_PHYS                                       (ACORE_REG_BASE_PHYS + 0x238)
#define HWIO_DBG_DAT_REG6_RMSK                                             0xff
#define HWIO_DBG_DAT_REG6_IN                    \
                in_dword(HWIO_DBG_DAT_REG6_ADDR)
#define HWIO_DBG_DAT_REG6_INM(m)            \
                in_dword_masked(HWIO_DBG_DAT_REG6_ADDR, m)
#define HWIO_DBG_DAT_REG6_DBG_DAT_REG6_7_0_BMSK                            0xff
#define HWIO_DBG_DAT_REG6_DBG_DAT_REG6_7_0_SHFT                               0

#define HWIO_DBG_DAT_REG7_ADDR                                       (ACORE_REG_BASE      + 0x23c)
#define HWIO_DBG_DAT_REG7_PHYS                                       (ACORE_REG_BASE_PHYS + 0x23c)
#define HWIO_DBG_DAT_REG7_RMSK                                             0xff
#define HWIO_DBG_DAT_REG7_IN                    \
                in_dword(HWIO_DBG_DAT_REG7_ADDR)
#define HWIO_DBG_DAT_REG7_INM(m)            \
                in_dword_masked(HWIO_DBG_DAT_REG7_ADDR, m)
#define HWIO_DBG_DAT_REG7_DBG_DAT_REG7_7_0_BMSK                            0xff
#define HWIO_DBG_DAT_REG7_DBG_DAT_REG7_7_0_SHFT                               0

#define HWIO_ENUM_STAT_REG_ADDR                                      (ACORE_REG_BASE      + 0x240)
#define HWIO_ENUM_STAT_REG_PHYS                                      (ACORE_REG_BASE_PHYS + 0x240)
#define HWIO_ENUM_STAT_REG_RMSK                                            0xff
#define HWIO_ENUM_STAT_REG_IN                    \
                in_dword(HWIO_ENUM_STAT_REG_ADDR)
#define HWIO_ENUM_STAT_REG_INM(m)            \
                in_dword_masked(HWIO_ENUM_STAT_REG_ADDR, m)
#define HWIO_ENUM_STAT_REG_ENUM_STAT_REG_7_0_BMSK                          0xff
#define HWIO_ENUM_STAT_REG_ENUM_STAT_REG_7_0_SHFT                             0

/*----------------------------------------------------------------------------
 * MODULE: EUD_EUD
 *--------------------------------------------------------------------------*/

#define EUD_EUD_REG_BASE     (AHB2PHY_NORTH_BASE      + 0x00000000)
#define EUD_EUD_REG_BASE_SIZE 0x3000
#define EUD_EUD_REG_BASE_USED 0x0
#define EUD_EUD_REG_BASE_PHYS (AHB2PHY_NORTH_BASE_PHYS + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: EUD_DET
 *--------------------------------------------------------------------------*/

#define EUD_DET_REG_BASE                                (AOSS_BASE      + 0x01276000)
#define EUD_DET_REG_BASE_SIZE                           0x10
#define EUD_DET_REG_BASE_USED                           0x0
#define EUD_DET_REG_BASE_PHYS                           (AOSS_BASE_PHYS + 0x01276000)

#define HWIO_VIOCTL_EUD_DETECT_ADDR                     (EUD_DET_REG_BASE      + 0x0)
#define HWIO_VIOCTL_EUD_DETECT_PHYS                     (EUD_DET_REG_BASE_PHYS + 0x0)
#define HWIO_VIOCTL_EUD_DETECT_RMSK                            0x1
#define HWIO_VIOCTL_EUD_DETECT_IN                    \
                in_dword(HWIO_VIOCTL_EUD_DETECT_ADDR)
#define HWIO_VIOCTL_EUD_DETECT_INM(m)            \
                in_dword_masked(HWIO_VIOCTL_EUD_DETECT_ADDR, m)
#define HWIO_VIOCTL_EUD_DETECT_OUT(v)            \
                out_dword(HWIO_VIOCTL_EUD_DETECT_ADDR,v)
#define HWIO_VIOCTL_EUD_DETECT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_VIOCTL_EUD_DETECT_ADDR,m,v,HWIO_VIOCTL_EUD_DETECT_IN)
#define HWIO_VIOCTL_EUD_DETECT_EUD_DETECT_BMSK                 0x1
#define HWIO_VIOCTL_EUD_DETECT_EUD_DETECT_SHFT                   0

/*----------------------------------------------------------------------------
 * MODULE: FUSE_CONTROLLER_SW_RANGE5
 *--------------------------------------------------------------------------*/

#define FUSE_CONTROLLER_SW_RANGE5_REG_BASE                                         (TMESS_BASE      + 0x021c9000)
#define FUSE_CONTROLLER_SW_RANGE5_REG_BASE_SIZE                                    0x1000
#define FUSE_CONTROLLER_SW_RANGE5_REG_BASE_USED                                    0x54
#define FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS                                    (TMESS_BASE_PHYS + 0x021c9000)

#define HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_ADDR                                      (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x0)
#define HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_PHYS                                      (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x0)
#define HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_RMSK                                      0xffffffff
#define HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_IN                    \
                in_dword(HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_ADDR)
#define HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_INM(m)            \
                in_dword_masked(HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_ADDR, m)
#define HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_OUT(v)            \
                out_dword(HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_ADDR,v)
#define HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_ADDR,m,v,HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_IN)
#define HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_ADDRESS_BMSK                              0xffffffff
#define HWIO_VIRTUAL_FUSE_CTRL_BASE_ADDR_ADDRESS_SHFT                                       0

#define HWIO_CAPT_SEC_BOOT_GPIO_ADDR                                               (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x4)
#define HWIO_CAPT_SEC_BOOT_GPIO_PHYS                                               (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x4)
#define HWIO_CAPT_SEC_BOOT_GPIO_RMSK                                               0xffffffff
#define HWIO_CAPT_SEC_BOOT_GPIO_IN                    \
                in_dword(HWIO_CAPT_SEC_BOOT_GPIO_ADDR)
#define HWIO_CAPT_SEC_BOOT_GPIO_INM(m)            \
                in_dword_masked(HWIO_CAPT_SEC_BOOT_GPIO_ADDR, m)
#define HWIO_CAPT_SEC_BOOT_GPIO_OUT(v)            \
                out_dword(HWIO_CAPT_SEC_BOOT_GPIO_ADDR,v)
#define HWIO_CAPT_SEC_BOOT_GPIO_OUTM(m,v) \
                out_dword_masked_ns(HWIO_CAPT_SEC_BOOT_GPIO_ADDR,m,v,HWIO_CAPT_SEC_BOOT_GPIO_IN)
#define HWIO_CAPT_SEC_BOOT_GPIO_RSVD_BMSK                                          0xffffe000
#define HWIO_CAPT_SEC_BOOT_GPIO_RSVD_SHFT                                                  13
#define HWIO_CAPT_SEC_BOOT_GPIO_FORCE_USB_BOOT_GPIO_BMSK                               0x1000
#define HWIO_CAPT_SEC_BOOT_GPIO_FORCE_USB_BOOT_GPIO_SHFT                                   12
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_EUD_ENUMERATION_EN_BMSK                0x800
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_EUD_ENUMERATION_EN_SHFT                   11
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_AP_PK_HASH_IN_FUSE_BMSK                0x400
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_AP_PK_HASH_IN_FUSE_SHFT                   10
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_ALL_USE_SERIAL_NUM_BMSK                0x200
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_ALL_USE_SERIAL_NUM_SHFT                    9
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_PK_HASH_INDEX_SRC_BMSK                 0x100
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_PK_HASH_INDEX_SRC_SHFT                     8
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_APPS_PBL_BOOT_SPEED_BMSK                0xc0
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_APPS_PBL_BOOT_SPEED_SHFT                   6
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_APPS_BOOT_FROM_ROM_BMSK                 0x20
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_APPS_BOOT_FROM_ROM_SHFT                    5
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_FAST_BOOT_BMSK                          0x1e
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_FAST_BOOT_SHFT                             1
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_WDOG_DISABLE_BMSK                        0x1
#define HWIO_CAPT_SEC_BOOT_GPIO_BOOT_CONFIG_GPIO_WDOG_DISABLE_SHFT                          0

#define HWIO_SPDM_DYN_SECURE_MODE_ADDR                                             (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x8)
#define HWIO_SPDM_DYN_SECURE_MODE_PHYS                                             (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x8)
#define HWIO_SPDM_DYN_SECURE_MODE_RMSK                                                    0x1
#define HWIO_SPDM_DYN_SECURE_MODE_IN                    \
                in_dword(HWIO_SPDM_DYN_SECURE_MODE_ADDR)
#define HWIO_SPDM_DYN_SECURE_MODE_INM(m)            \
                in_dword_masked(HWIO_SPDM_DYN_SECURE_MODE_ADDR, m)
#define HWIO_SPDM_DYN_SECURE_MODE_OUT(v)            \
                out_dword(HWIO_SPDM_DYN_SECURE_MODE_ADDR,v)
#define HWIO_SPDM_DYN_SECURE_MODE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_SPDM_DYN_SECURE_MODE_ADDR,m,v,HWIO_SPDM_DYN_SECURE_MODE_IN)
#define HWIO_SPDM_DYN_SECURE_MODE_SECURE_MODE_BMSK                                        0x1
#define HWIO_SPDM_DYN_SECURE_MODE_SECURE_MODE_SHFT                                          0

#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_ADDR                                 (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0xc)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_PHYS                                 (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0xc)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_RMSK                                 0xffffffff
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_IN                    \
                in_dword(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_ADDR)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_INM(m)            \
                in_dword_masked(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_ADDR, m)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_OUT(v)            \
                out_dword(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_ADDR,v)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_ADDR,m,v,HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_IN)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION31_STICKY_BIT_BMSK             0x80000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION31_STICKY_BIT_SHFT                     31
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION30_STICKY_BIT_BMSK             0x40000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION30_STICKY_BIT_SHFT                     30
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION29_STICKY_BIT_BMSK             0x20000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION29_STICKY_BIT_SHFT                     29
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION28_STICKY_BIT_BMSK             0x10000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION28_STICKY_BIT_SHFT                     28
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION27_STICKY_BIT_BMSK              0x8000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION27_STICKY_BIT_SHFT                     27
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION26_STICKY_BIT_BMSK              0x4000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION26_STICKY_BIT_SHFT                     26
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION25_STICKY_BIT_BMSK              0x2000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION25_STICKY_BIT_SHFT                     25
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION24_STICKY_BIT_BMSK              0x1000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION24_STICKY_BIT_SHFT                     24
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION23_STICKY_BIT_BMSK               0x800000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION23_STICKY_BIT_SHFT                     23
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION22_STICKY_BIT_BMSK               0x400000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION22_STICKY_BIT_SHFT                     22
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION21_STICKY_BIT_BMSK               0x200000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION21_STICKY_BIT_SHFT                     21
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION20_STICKY_BIT_BMSK               0x100000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION20_STICKY_BIT_SHFT                     20
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION19_STICKY_BIT_BMSK                0x80000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION19_STICKY_BIT_SHFT                     19
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION18_STICKY_BIT_BMSK                0x40000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION18_STICKY_BIT_SHFT                     18
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION17_STICKY_BIT_BMSK                0x20000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION17_STICKY_BIT_SHFT                     17
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION16_STICKY_BIT_BMSK                0x10000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION16_STICKY_BIT_SHFT                     16
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION15_STICKY_BIT_BMSK                 0x8000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION15_STICKY_BIT_SHFT                     15
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION14_STICKY_BIT_BMSK                 0x4000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION14_STICKY_BIT_SHFT                     14
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION13_STICKY_BIT_BMSK                 0x2000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION13_STICKY_BIT_SHFT                     13
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION12_STICKY_BIT_BMSK                 0x1000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION12_STICKY_BIT_SHFT                     12
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION11_STICKY_BIT_BMSK                  0x800
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION11_STICKY_BIT_SHFT                     11
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION10_STICKY_BIT_BMSK                  0x400
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION10_STICKY_BIT_SHFT                     10
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION9_STICKY_BIT_BMSK                   0x200
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION9_STICKY_BIT_SHFT                       9
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION8_STICKY_BIT_BMSK                   0x100
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION8_STICKY_BIT_SHFT                       8
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION7_STICKY_BIT_BMSK                    0x80
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION7_STICKY_BIT_SHFT                       7
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION6_STICKY_BIT_BMSK                    0x40
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION6_STICKY_BIT_SHFT                       6
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION5_STICKY_BIT_BMSK                    0x20
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION5_STICKY_BIT_SHFT                       5
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION4_STICKY_BIT_BMSK                    0x10
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION4_STICKY_BIT_SHFT                       4
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION3_STICKY_BIT_BMSK                     0x8
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION3_STICKY_BIT_SHFT                       3
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION2_STICKY_BIT_BMSK                     0x4
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION2_STICKY_BIT_SHFT                       2
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION1_STICKY_BIT_BMSK                     0x2
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION1_STICKY_BIT_SHFT                       1
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION0_STICKY_BIT_BMSK                     0x1
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION0_STICKY_BIT_SHFT                       0

#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_ADDR                                 (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x10)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_PHYS                                 (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x10)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_RMSK                                 0xffffffff
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_IN                    \
                in_dword(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_ADDR)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_INM(m)            \
                in_dword_masked(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_ADDR, m)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_OUT(v)            \
                out_dword(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_ADDR,v)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_ADDR,m,v,HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_IN)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION63_STICKY_BIT_BMSK             0x80000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION63_STICKY_BIT_SHFT                     31
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION62_STICKY_BIT_BMSK             0x40000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION62_STICKY_BIT_SHFT                     30
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION61_STICKY_BIT_BMSK             0x20000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION61_STICKY_BIT_SHFT                     29
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION60_STICKY_BIT_BMSK             0x10000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION60_STICKY_BIT_SHFT                     28
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION59_STICKY_BIT_BMSK              0x8000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION59_STICKY_BIT_SHFT                     27
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION58_STICKY_BIT_BMSK              0x4000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION58_STICKY_BIT_SHFT                     26
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION57_STICKY_BIT_BMSK              0x2000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION57_STICKY_BIT_SHFT                     25
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION56_STICKY_BIT_BMSK              0x1000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION56_STICKY_BIT_SHFT                     24
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION55_STICKY_BIT_BMSK               0x800000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION55_STICKY_BIT_SHFT                     23
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION54_STICKY_BIT_BMSK               0x400000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION54_STICKY_BIT_SHFT                     22
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION53_STICKY_BIT_BMSK               0x200000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION53_STICKY_BIT_SHFT                     21
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION52_STICKY_BIT_BMSK               0x100000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION52_STICKY_BIT_SHFT                     20
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION51_STICKY_BIT_BMSK                0x80000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION51_STICKY_BIT_SHFT                     19
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION50_STICKY_BIT_BMSK                0x40000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION50_STICKY_BIT_SHFT                     18
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION49_STICKY_BIT_BMSK                0x20000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION49_STICKY_BIT_SHFT                     17
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION48_STICKY_BIT_BMSK                0x10000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION48_STICKY_BIT_SHFT                     16
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION47_STICKY_BIT_BMSK                 0x8000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION47_STICKY_BIT_SHFT                     15
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION46_STICKY_BIT_BMSK                 0x4000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION46_STICKY_BIT_SHFT                     14
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION45_STICKY_BIT_BMSK                 0x2000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION45_STICKY_BIT_SHFT                     13
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION44_STICKY_BIT_BMSK                 0x1000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION44_STICKY_BIT_SHFT                     12
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION43_STICKY_BIT_BMSK                  0x800
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION43_STICKY_BIT_SHFT                     11
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION42_STICKY_BIT_BMSK                  0x400
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION42_STICKY_BIT_SHFT                     10
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION41_STICKY_BIT_BMSK                  0x200
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION41_STICKY_BIT_SHFT                      9
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION40_STICKY_BIT_BMSK                  0x100
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION40_STICKY_BIT_SHFT                      8
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION39_STICKY_BIT_BMSK                   0x80
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION39_STICKY_BIT_SHFT                      7
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION38_STICKY_BIT_BMSK                   0x40
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION38_STICKY_BIT_SHFT                      6
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION37_STICKY_BIT_BMSK                   0x20
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION37_STICKY_BIT_SHFT                      5
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION36_STICKY_BIT_BMSK                   0x10
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION36_STICKY_BIT_SHFT                      4
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION35_STICKY_BIT_BMSK                    0x8
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION35_STICKY_BIT_SHFT                      3
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION34_STICKY_BIT_BMSK                    0x4
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION34_STICKY_BIT_SHFT                      2
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION33_STICKY_BIT_BMSK                    0x2
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION33_STICKY_BIT_SHFT                      1
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION32_STICKY_BIT_BMSK                    0x1
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_REGION32_STICKY_BIT_SHFT                      0

#define HWIO_QFPROM_BLOW_TIMER_OVRD_ADDR                                           (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x14)
#define HWIO_QFPROM_BLOW_TIMER_OVRD_PHYS                                           (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x14)
#define HWIO_QFPROM_BLOW_TIMER_OVRD_RMSK                                                0xfff
#define HWIO_QFPROM_BLOW_TIMER_OVRD_IN                    \
                in_dword(HWIO_QFPROM_BLOW_TIMER_OVRD_ADDR)
#define HWIO_QFPROM_BLOW_TIMER_OVRD_INM(m)            \
                in_dword_masked(HWIO_QFPROM_BLOW_TIMER_OVRD_ADDR, m)
#define HWIO_QFPROM_BLOW_TIMER_OVRD_OUT(v)            \
                out_dword(HWIO_QFPROM_BLOW_TIMER_OVRD_ADDR,v)
#define HWIO_QFPROM_BLOW_TIMER_OVRD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QFPROM_BLOW_TIMER_OVRD_ADDR,m,v,HWIO_QFPROM_BLOW_TIMER_OVRD_IN)
#define HWIO_QFPROM_BLOW_TIMER_OVRD_BLOW_TIMER_BMSK                                     0xfff
#define HWIO_QFPROM_BLOW_TIMER_OVRD_BLOW_TIMER_SHFT                                         0

#define HWIO_QFPROM_BLOW_TIMER_INVALID_ADDR                                        (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x18)
#define HWIO_QFPROM_BLOW_TIMER_INVALID_PHYS                                        (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x18)
#define HWIO_QFPROM_BLOW_TIMER_INVALID_RMSK                                               0x1
#define HWIO_QFPROM_BLOW_TIMER_INVALID_IN                    \
                in_dword(HWIO_QFPROM_BLOW_TIMER_INVALID_ADDR)
#define HWIO_QFPROM_BLOW_TIMER_INVALID_INM(m)            \
                in_dword_masked(HWIO_QFPROM_BLOW_TIMER_INVALID_ADDR, m)
#define HWIO_QFPROM_BLOW_TIMER_INVALID_INVALID_BMSK                                       0x1
#define HWIO_QFPROM_BLOW_TIMER_INVALID_INVALID_SHFT                                         0

#define HWIO_QFPROM_TEST_CTRL_OVRD_ADDR                                            (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x1c)
#define HWIO_QFPROM_TEST_CTRL_OVRD_PHYS                                            (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x1c)
#define HWIO_QFPROM_TEST_CTRL_OVRD_RMSK                                                   0xf
#define HWIO_QFPROM_TEST_CTRL_OVRD_IN                    \
                in_dword(HWIO_QFPROM_TEST_CTRL_OVRD_ADDR)
#define HWIO_QFPROM_TEST_CTRL_OVRD_INM(m)            \
                in_dword_masked(HWIO_QFPROM_TEST_CTRL_OVRD_ADDR, m)
#define HWIO_QFPROM_TEST_CTRL_OVRD_OUT(v)            \
                out_dword(HWIO_QFPROM_TEST_CTRL_OVRD_ADDR,v)
#define HWIO_QFPROM_TEST_CTRL_OVRD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QFPROM_TEST_CTRL_OVRD_ADDR,m,v,HWIO_QFPROM_TEST_CTRL_OVRD_IN)
#define HWIO_QFPROM_TEST_CTRL_OVRD_SEL_TST_ROM_BMSK                                       0x8
#define HWIO_QFPROM_TEST_CTRL_OVRD_SEL_TST_ROM_SHFT                                         3
#define HWIO_QFPROM_TEST_CTRL_OVRD_SEL_TST_WL_BMSK                                        0x4
#define HWIO_QFPROM_TEST_CTRL_OVRD_SEL_TST_WL_SHFT                                          2
#define HWIO_QFPROM_TEST_CTRL_OVRD_SEL_TST_BL_BMSK                                        0x2
#define HWIO_QFPROM_TEST_CTRL_OVRD_SEL_TST_BL_SHFT                                          1
#define HWIO_QFPROM_TEST_CTRL_OVRD_EN_FUSE_RES_MEAS_BMSK                                  0x1
#define HWIO_QFPROM_TEST_CTRL_OVRD_EN_FUSE_RES_MEAS_SHFT                                    0

#define HWIO_QFPROM_TEST_CTRL_INVALID_ADDR                                         (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x20)
#define HWIO_QFPROM_TEST_CTRL_INVALID_PHYS                                         (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x20)
#define HWIO_QFPROM_TEST_CTRL_INVALID_RMSK                                                0x1
#define HWIO_QFPROM_TEST_CTRL_INVALID_IN                    \
                in_dword(HWIO_QFPROM_TEST_CTRL_INVALID_ADDR)
#define HWIO_QFPROM_TEST_CTRL_INVALID_INM(m)            \
                in_dword_masked(HWIO_QFPROM_TEST_CTRL_INVALID_ADDR, m)
#define HWIO_QFPROM_TEST_CTRL_INVALID_INVALID_BMSK                                        0x1
#define HWIO_QFPROM_TEST_CTRL_INVALID_INVALID_SHFT                                          0

#define HWIO_QFPROM_ACCEL_OVRD_ADDR                                                (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x24)
#define HWIO_QFPROM_ACCEL_OVRD_PHYS                                                (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x24)
#define HWIO_QFPROM_ACCEL_OVRD_RMSK                                                     0xfff
#define HWIO_QFPROM_ACCEL_OVRD_IN                    \
                in_dword(HWIO_QFPROM_ACCEL_OVRD_ADDR)
#define HWIO_QFPROM_ACCEL_OVRD_INM(m)            \
                in_dword_masked(HWIO_QFPROM_ACCEL_OVRD_ADDR, m)
#define HWIO_QFPROM_ACCEL_OVRD_OUT(v)            \
                out_dword(HWIO_QFPROM_ACCEL_OVRD_ADDR,v)
#define HWIO_QFPROM_ACCEL_OVRD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QFPROM_ACCEL_OVRD_ADDR,m,v,HWIO_QFPROM_ACCEL_OVRD_IN)
#define HWIO_QFPROM_ACCEL_OVRD_QFPROM_GATELAST_BMSK                                     0x800
#define HWIO_QFPROM_ACCEL_OVRD_QFPROM_GATELAST_SHFT                                        11
#define HWIO_QFPROM_ACCEL_OVRD_QFPROM_TRIPPT_SEL_BMSK                                   0x700
#define HWIO_QFPROM_ACCEL_OVRD_QFPROM_TRIPPT_SEL_SHFT                                       8
#define HWIO_QFPROM_ACCEL_OVRD_QFPROM_ACCEL_BMSK                                         0xff
#define HWIO_QFPROM_ACCEL_OVRD_QFPROM_ACCEL_SHFT                                            0

#define HWIO_QFPROM_ACCEL_INVALID_ADDR                                             (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x28)
#define HWIO_QFPROM_ACCEL_INVALID_PHYS                                             (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x28)
#define HWIO_QFPROM_ACCEL_INVALID_RMSK                                                    0x1
#define HWIO_QFPROM_ACCEL_INVALID_IN                    \
                in_dword(HWIO_QFPROM_ACCEL_INVALID_ADDR)
#define HWIO_QFPROM_ACCEL_INVALID_INM(m)            \
                in_dword_masked(HWIO_QFPROM_ACCEL_INVALID_ADDR, m)
#define HWIO_QFPROM_ACCEL_INVALID_INVALID_BMSK                                            0x1
#define HWIO_QFPROM_ACCEL_INVALID_INVALID_SHFT                                              0

#define HWIO_QFPROM_BIST_CTRL_OVRD_ADDR                                            (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x2c)
#define HWIO_QFPROM_BIST_CTRL_OVRD_PHYS                                            (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x2c)
#define HWIO_QFPROM_BIST_CTRL_OVRD_RMSK                                                   0x1
#define HWIO_QFPROM_BIST_CTRL_OVRD_IN                    \
                in_dword(HWIO_QFPROM_BIST_CTRL_OVRD_ADDR)
#define HWIO_QFPROM_BIST_CTRL_OVRD_INM(m)            \
                in_dword_masked(HWIO_QFPROM_BIST_CTRL_OVRD_ADDR, m)
#define HWIO_QFPROM_BIST_CTRL_OVRD_OUT(v)            \
                out_dword(HWIO_QFPROM_BIST_CTRL_OVRD_ADDR,v)
#define HWIO_QFPROM_BIST_CTRL_OVRD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QFPROM_BIST_CTRL_OVRD_ADDR,m,v,HWIO_QFPROM_BIST_CTRL_OVRD_IN)
#define HWIO_QFPROM_BIST_CTRL_OVRD_START_BMSK                                             0x1
#define HWIO_QFPROM_BIST_CTRL_OVRD_START_SHFT                                               0

#define HWIO_QFPROM_BIST_CTRL_INVALID_ADDR                                         (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x30)
#define HWIO_QFPROM_BIST_CTRL_INVALID_PHYS                                         (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x30)
#define HWIO_QFPROM_BIST_CTRL_INVALID_RMSK                                                0x1
#define HWIO_QFPROM_BIST_CTRL_INVALID_IN                    \
                in_dword(HWIO_QFPROM_BIST_CTRL_INVALID_ADDR)
#define HWIO_QFPROM_BIST_CTRL_INVALID_INM(m)            \
                in_dword_masked(HWIO_QFPROM_BIST_CTRL_INVALID_ADDR, m)
#define HWIO_QFPROM_BIST_CTRL_INVALID_INVALID_BMSK                                        0x1
#define HWIO_QFPROM_BIST_CTRL_INVALID_INVALID_SHFT                                          0

#define HWIO_FEC_ESR_ADDR                                                          (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x34)
#define HWIO_FEC_ESR_PHYS                                                          (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x34)
#define HWIO_FEC_ESR_RMSK                                                             0xfffff
#define HWIO_FEC_ESR_IN                    \
                in_dword(HWIO_FEC_ESR_ADDR)
#define HWIO_FEC_ESR_INM(m)            \
                in_dword_masked(HWIO_FEC_ESR_ADDR, m)
#define HWIO_FEC_ESR_OUT(v)            \
                out_dword(HWIO_FEC_ESR_ADDR,v)
#define HWIO_FEC_ESR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_FEC_ESR_ADDR,m,v,HWIO_FEC_ESR_IN)
#define HWIO_FEC_ESR_CORR_TME_CNOC_PORT_BMSK                                          0x80000
#define HWIO_FEC_ESR_CORR_TME_CNOC_PORT_SHFT                                               19
#define HWIO_FEC_ESR_CORR_TME_PRIV_PORT_BMSK                                          0x40000
#define HWIO_FEC_ESR_CORR_TME_PRIV_PORT_SHFT                                               18
#define HWIO_FEC_ESR_CORR_TME_CPU_PORT_BMSK                                           0x20000
#define HWIO_FEC_ESR_CORR_TME_CPU_PORT_SHFT                                                17
#define HWIO_FEC_ESR_CORR_TME_SEQ_PORT_BMSK                                           0x10000
#define HWIO_FEC_ESR_CORR_TME_SEQ_PORT_SHFT                                                16
#define HWIO_FEC_ESR_CORR_TME_HW_PORT_BMSK                                             0x8000
#define HWIO_FEC_ESR_CORR_TME_HW_PORT_SHFT                                                 15
#define HWIO_FEC_ESR_CORR_SEC_CHAN_BMSK                                                0x4000
#define HWIO_FEC_ESR_CORR_SEC_CHAN_SHFT                                                    14
#define HWIO_FEC_ESR_CORR_BOOT_ROM_BMSK                                                0x2000
#define HWIO_FEC_ESR_CORR_BOOT_ROM_SHFT                                                    13
#define HWIO_FEC_ESR_CORR_FUSE_SENSE_BMSK                                              0x1000
#define HWIO_FEC_ESR_CORR_FUSE_SENSE_SHFT                                                  12
#define HWIO_FEC_ESR_CORR_MULT_BMSK                                                     0x800
#define HWIO_FEC_ESR_CORR_MULT_SHFT                                                        11
#define HWIO_FEC_ESR_CORR_SEEN_BMSK                                                     0x400
#define HWIO_FEC_ESR_CORR_SEEN_SHFT                                                        10
#define HWIO_FEC_ESR_ERR_TME_CNOC_PORT_BMSK                                             0x200
#define HWIO_FEC_ESR_ERR_TME_CNOC_PORT_SHFT                                                 9
#define HWIO_FEC_ESR_ERR_TME_PRIV_PORT_BMSK                                             0x100
#define HWIO_FEC_ESR_ERR_TME_PRIV_PORT_SHFT                                                 8
#define HWIO_FEC_ESR_ERR_TME_CPU_PORT_BMSK                                               0x80
#define HWIO_FEC_ESR_ERR_TME_CPU_PORT_SHFT                                                  7
#define HWIO_FEC_ESR_ERR_TME_SEQ_PORT_BMSK                                               0x40
#define HWIO_FEC_ESR_ERR_TME_SEQ_PORT_SHFT                                                  6
#define HWIO_FEC_ESR_ERR_TME_HW_PORT_BMSK                                                0x20
#define HWIO_FEC_ESR_ERR_TME_HW_PORT_SHFT                                                   5
#define HWIO_FEC_ESR_ERR_SEC_CHAN_BMSK                                                   0x10
#define HWIO_FEC_ESR_ERR_SEC_CHAN_SHFT                                                      4
#define HWIO_FEC_ESR_ERR_BOOT_ROM_BMSK                                                    0x8
#define HWIO_FEC_ESR_ERR_BOOT_ROM_SHFT                                                      3
#define HWIO_FEC_ESR_ERR_FUSE_SENSE_BMSK                                                  0x4
#define HWIO_FEC_ESR_ERR_FUSE_SENSE_SHFT                                                    2
#define HWIO_FEC_ESR_ERR_MULT_BMSK                                                        0x2
#define HWIO_FEC_ESR_ERR_MULT_SHFT                                                          1
#define HWIO_FEC_ESR_ERR_SEEN_BMSK                                                        0x1
#define HWIO_FEC_ESR_ERR_SEEN_SHFT                                                          0

#define HWIO_ECC_CORRECTABLE_STATUS_ADDR                                           (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x38)
#define HWIO_ECC_CORRECTABLE_STATUS_PHYS                                           (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x38)
#define HWIO_ECC_CORRECTABLE_STATUS_RMSK                                           0xffffffff
#define HWIO_ECC_CORRECTABLE_STATUS_IN                    \
                in_dword(HWIO_ECC_CORRECTABLE_STATUS_ADDR)
#define HWIO_ECC_CORRECTABLE_STATUS_INM(m)            \
                in_dword_masked(HWIO_ECC_CORRECTABLE_STATUS_ADDR, m)
#define HWIO_ECC_CORRECTABLE_STATUS_RSVD_BMSK                                      0xfffc0000
#define HWIO_ECC_CORRECTABLE_STATUS_RSVD_SHFT                                              18
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_14_BMSK                           0x20000
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_14_SHFT                                17
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_13_BMSK                           0x10000
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_13_SHFT                                16
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_12_BMSK                            0x8000
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_12_SHFT                                15
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_11_BMSK                            0x4000
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_11_SHFT                                14
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_10_BMSK                            0x2000
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_10_SHFT                                13
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_9_BMSK                             0x1000
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_9_SHFT                                 12
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_8_BMSK                              0x800
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_8_SHFT                                 11
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_7_BMSK                              0x400
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_7_SHFT                                 10
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_6_BMSK                              0x200
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_6_SHFT                                  9
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_5_BMSK                              0x100
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_5_SHFT                                  8
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_4_BMSK                               0x80
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_4_SHFT                                  7
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_3_BMSK                               0x40
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_3_SHFT                                  6
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_2_BMSK                               0x20
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_2_SHFT                                  5
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_1_BMSK                               0x10
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_1_SHFT                                  4
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_0_BMSK                                0x8
#define HWIO_ECC_CORRECTABLE_STATUS_MEMCONFIG_CHUNK_0_SHFT                                  3
#define HWIO_ECC_CORRECTABLE_STATUS_CALIB_CHUNK_2_BMSK                                    0x4
#define HWIO_ECC_CORRECTABLE_STATUS_CALIB_CHUNK_2_SHFT                                      2
#define HWIO_ECC_CORRECTABLE_STATUS_CALIB_CHUNK_1_BMSK                                    0x2
#define HWIO_ECC_CORRECTABLE_STATUS_CALIB_CHUNK_1_SHFT                                      1
#define HWIO_ECC_CORRECTABLE_STATUS_CALIB_CHUNK_0_BMSK                                    0x1
#define HWIO_ECC_CORRECTABLE_STATUS_CALIB_CHUNK_0_SHFT                                      0

#define HWIO_ECC_ERROR_STATUS_ADDR                                                 (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x3c)
#define HWIO_ECC_ERROR_STATUS_PHYS                                                 (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x3c)
#define HWIO_ECC_ERROR_STATUS_RMSK                                                 0xffffffff
#define HWIO_ECC_ERROR_STATUS_IN                    \
                in_dword(HWIO_ECC_ERROR_STATUS_ADDR)
#define HWIO_ECC_ERROR_STATUS_INM(m)            \
                in_dword_masked(HWIO_ECC_ERROR_STATUS_ADDR, m)
#define HWIO_ECC_ERROR_STATUS_RSVD_BMSK                                            0xfffc0000
#define HWIO_ECC_ERROR_STATUS_RSVD_SHFT                                                    18
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_14_BMSK                                 0x20000
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_14_SHFT                                      17
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_13_BMSK                                 0x10000
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_13_SHFT                                      16
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_12_BMSK                                  0x8000
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_12_SHFT                                      15
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_11_BMSK                                  0x4000
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_11_SHFT                                      14
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_10_BMSK                                  0x2000
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_10_SHFT                                      13
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_9_BMSK                                   0x1000
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_9_SHFT                                       12
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_8_BMSK                                    0x800
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_8_SHFT                                       11
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_7_BMSK                                    0x400
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_7_SHFT                                       10
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_6_BMSK                                    0x200
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_6_SHFT                                        9
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_5_BMSK                                    0x100
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_5_SHFT                                        8
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_4_BMSK                                     0x80
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_4_SHFT                                        7
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_3_BMSK                                     0x40
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_3_SHFT                                        6
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_2_BMSK                                     0x20
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_2_SHFT                                        5
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_1_BMSK                                     0x10
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_1_SHFT                                        4
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_0_BMSK                                      0x8
#define HWIO_ECC_ERROR_STATUS_MEMCONFIG_CHUNK_0_SHFT                                        3
#define HWIO_ECC_ERROR_STATUS_CALIB_CHUNK_2_BMSK                                          0x4
#define HWIO_ECC_ERROR_STATUS_CALIB_CHUNK_2_SHFT                                            2
#define HWIO_ECC_ERROR_STATUS_CALIB_CHUNK_1_BMSK                                          0x2
#define HWIO_ECC_ERROR_STATUS_CALIB_CHUNK_1_SHFT                                            1
#define HWIO_ECC_ERROR_STATUS_CALIB_CHUNK_0_BMSK                                          0x1
#define HWIO_ECC_ERROR_STATUS_CALIB_CHUNK_0_SHFT                                            0

#define HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_ADDR                                         (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x40)
#define HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_PHYS                                         (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x40)
#define HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_RMSK                                                0x1
#define HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_IN                    \
                in_dword(HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_ADDR)
#define HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_INM(m)            \
                in_dword_masked(HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_ADDR, m)
#define HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_OUT(v)            \
                out_dword(HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_ADDR,v)
#define HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_ADDR,m,v,HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_IN)
#define HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_SEQ_TIMEOUT_ACK_BMSK                                0x1
#define HWIO_APPS_PBL_SEQ_TIMEOUT_ACK_SEQ_TIMEOUT_ACK_SHFT                                  0

#define HWIO_APPS_PBL_EDL_INDICATOR_ADDR                                           (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x44)
#define HWIO_APPS_PBL_EDL_INDICATOR_PHYS                                           (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x44)
#define HWIO_APPS_PBL_EDL_INDICATOR_RMSK                                                  0x1
#define HWIO_APPS_PBL_EDL_INDICATOR_IN                    \
                in_dword(HWIO_APPS_PBL_EDL_INDICATOR_ADDR)
#define HWIO_APPS_PBL_EDL_INDICATOR_INM(m)            \
                in_dword_masked(HWIO_APPS_PBL_EDL_INDICATOR_ADDR, m)
#define HWIO_APPS_PBL_EDL_INDICATOR_OUT(v)            \
                out_dword(HWIO_APPS_PBL_EDL_INDICATOR_ADDR,v)
#define HWIO_APPS_PBL_EDL_INDICATOR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_APPS_PBL_EDL_INDICATOR_ADDR,m,v,HWIO_APPS_PBL_EDL_INDICATOR_IN)
#define HWIO_APPS_PBL_EDL_INDICATOR_EDL_INDICATOR_BMSK                                    0x1
#define HWIO_APPS_PBL_EDL_INDICATOR_EDL_INDICATOR_SHFT                                      0

#define HWIO_QFPROM_TEST_CTRL_ADDR                                                 (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x50)
#define HWIO_QFPROM_TEST_CTRL_PHYS                                                 (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x50)
#define HWIO_QFPROM_TEST_CTRL_RMSK                                                        0xf
#define HWIO_QFPROM_TEST_CTRL_IN                    \
                in_dword(HWIO_QFPROM_TEST_CTRL_ADDR)
#define HWIO_QFPROM_TEST_CTRL_INM(m)            \
                in_dword_masked(HWIO_QFPROM_TEST_CTRL_ADDR, m)
#define HWIO_QFPROM_TEST_CTRL_OUT(v)            \
                out_dword(HWIO_QFPROM_TEST_CTRL_ADDR,v)
#define HWIO_QFPROM_TEST_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QFPROM_TEST_CTRL_ADDR,m,v,HWIO_QFPROM_TEST_CTRL_IN)
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_ROM_BMSK                                            0x8
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_ROM_SHFT                                              3
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_WL_BMSK                                             0x4
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_WL_SHFT                                               2
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_BL_BMSK                                             0x2
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_BL_SHFT                                               1
#define HWIO_QFPROM_TEST_CTRL_EN_FUSE_RES_MEAS_BMSK                                       0x1
#define HWIO_QFPROM_TEST_CTRL_EN_FUSE_RES_MEAS_SHFT                                         0

#define HWIO_QFPROM_BIST_CTRL_ADDR                                                 (FUSE_CONTROLLER_SW_RANGE5_REG_BASE      + 0x54)
#define HWIO_QFPROM_BIST_CTRL_PHYS                                                 (FUSE_CONTROLLER_SW_RANGE5_REG_BASE_PHYS + 0x54)
#define HWIO_QFPROM_BIST_CTRL_RMSK                                                        0x1
#define HWIO_QFPROM_BIST_CTRL_IN                    \
                in_dword(HWIO_QFPROM_BIST_CTRL_ADDR)
#define HWIO_QFPROM_BIST_CTRL_INM(m)            \
                in_dword_masked(HWIO_QFPROM_BIST_CTRL_ADDR, m)
#define HWIO_QFPROM_BIST_CTRL_OUT(v)            \
                out_dword(HWIO_QFPROM_BIST_CTRL_ADDR,v)
#define HWIO_QFPROM_BIST_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_QFPROM_BIST_CTRL_ADDR,m,v,HWIO_QFPROM_BIST_CTRL_IN)
#define HWIO_QFPROM_BIST_CTRL_START_BMSK                                                  0x1
#define HWIO_QFPROM_BIST_CTRL_START_SHFT                                                    0


#endif /* __HWIO_EUD_H__ */
