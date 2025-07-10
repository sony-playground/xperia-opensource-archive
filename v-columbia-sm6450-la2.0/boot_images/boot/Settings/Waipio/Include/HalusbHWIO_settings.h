#ifndef __HALUSBHWIO_SETTINGS_H__
#define __HALUSBHWIO_SETTINGS_H__
/*
===========================================================================
*/
/**
    @file HalusbHWIO_settings.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8450 (Waipio) [waipio_v1.0_p3q3r17.2_MTO_POST_SI]
 
    This file contains HWIO register definitions for the following modules:
        USB2PHY_CM_DWC_USB2
        USB3_DP_PHY_CM_USB3_DP
        USB3_DP_PHY_USB3.*


    Generation parameters: 
    { 'filename': 'HalusbHWIO_settings.h',
      'module-filter-exclude': {},
      'module-filter-include': {},
      'modules': [ 'USB2PHY_CM_DWC_USB2',
                   'USB3_DP_PHY_CM_USB3_DP',
                   'USB3_DP_PHY_USB3.*']}
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

    $Header: //components/rel/core.boot/6.0/Settings/Waipio/Include/HalusbHWIO_settings.h#1 $
    $DateTime: 2021/05/17 18:32:26 $
    $Author: pwbldsvc $

    ===========================================================================
*/


#define QUSB_HWIO_ADDR_EMPTY                    (0xFFFFFFFF)
#define QUSB_HWIO_ADDR_END                      (0x0)

//
// copy AHB2PHY_SOUTH from msmhwiobase.h
/*----------------------------------------------------------------------------
 * BASE: AHB2PHY_SOUTH
 *--------------------------------------------------------------------------*/

#define AHB2PHY_SOUTH_BASE                                          0x088e0000
#define AHB2PHY_SOUTH_BASE_SIZE                                     0x00010000
#define AHB2PHY_SOUTH_BASE_PHYS                                     0x088e0000
// ---------------------------------------------------------------------------

/*----------------------------------------------------------------------------
 * MODULE: USB2PHY_CM_DWC_USB2
 *--------------------------------------------------------------------------*/

#define USB2PHY_CM_DWC_USB2_REG_BASE                                                           (AHB2PHY_SOUTH_BASE            + 0x00003000)
#define USB2PHY_CM_DWC_USB2_REG_BASE_SIZE                                                      0x120
#define USB2PHY_CM_DWC_USB2_REG_BASE_USED                                                      0x11c

#define HWIO_USB2PHY_USB_PHY_REVISION_ID0_ADDR                                                 (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x0)

#define HWIO_USB2PHY_USB_PHY_REVISION_ID1_ADDR                                                 (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x4)

#define HWIO_USB2PHY_USB_PHY_REVISION_ID2_ADDR                                                 (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x8)

#define HWIO_USB2PHY_USB_PHY_REVISION_ID3_ADDR                                                 (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xc)

#define HWIO_USB2PHY_USB_PHY_DEBUG_BUS_STAT0_ADDR                                              (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x10)

#define HWIO_USB2PHY_USB_PHY_DEBUG_BUS_STAT1_ADDR                                              (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x14)

#define HWIO_USB2PHY_USB_PHY_DEBUG_BUS_STAT2_ADDR                                              (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x18)

#define HWIO_USB2PHY_USB_PHY_DEBUG_BUS_STAT3_ADDR                                              (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x1c)

#define HWIO_USB2PHY_USB_PHY_HS_RX_TESTER_OUT_1_ADDR                                           (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x20)

#define HWIO_USB2PHY_USB_PHY_CHARGING_DET_OUTPUT_ADDR                                          (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x24)

#define HWIO_USB2PHY_USB_PHY_HS_PHY_TEST_OUT_1_ADDR                                            (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x28)

#define HWIO_USB2PHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_ADDR                                     (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x2c)

#define HWIO_USB2PHY_USB_PHY_UTMI_RX_DATAL_STATUS_ADDR                                         (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x30)

#define HWIO_USB2PHY_USB_PHY_UTMI_RX_DATAH_STATUS_ADDR                                         (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x34)

#define HWIO_USB2PHY_USB_PHY_UTMI_RX_PORT_STATUS_ADDR                                          (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x38)

#define HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_ADDR                                                   (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x3c)

#define HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_ADDR                                                   (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x40)

#define HWIO_USB2PHY_USB_PHY_UTMI_CTRL2_ADDR                                                   (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x44)

#define HWIO_USB2PHY_USB_PHY_UTMI_CTRL3_ADDR                                                   (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x48)

#define HWIO_USB2PHY_USB_PHY_UTMI_CTRL4_ADDR                                                   (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x4c)

#define HWIO_USB2PHY_USB_PHY_UTMI_CTRL5_ADDR                                                   (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x50)

#define HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR                                          (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x54)

#define HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON1_ADDR                                          (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x58)

#define HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON2_ADDR                                          (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x5c)

#define HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL1_ADDR                                                 (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x60)

#define HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_ADDR                                                 (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x64)

#define HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL3_ADDR                                                 (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x68)

#define HWIO_USB2PHY_USB_PHY_PARAMETER_OVERRIDE_X0_ADDR                                        (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x6c)

#define HWIO_USB2PHY_USB_PHY_PARAMETER_OVERRIDE_X1_ADDR                                        (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x70)

#define HWIO_USB2PHY_USB_PHY_PARAMETER_OVERRIDE_X2_ADDR                                        (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x74)

#define HWIO_USB2PHY_USB_PHY_PARAMETER_OVERRIDE_X3_ADDR                                        (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x78)

#define HWIO_USB2PHY_USB_PHY_CHARGING_DET_CTRL_ADDR                                            (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x7c)

#define HWIO_USB2PHY_USB_PHY_HS_PHY_TEST0_ADDR                                                 (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x80)

#define HWIO_USB2PHY_USB_PHY_HS_PHY_TEST1_ADDR                                                 (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x84)

#define HWIO_USB2PHY_USB_PHY_HS_RX_TESTER_1_REG0_ADDR                                          (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x88)

#define HWIO_USB2PHY_USB_PHY_HS_RX_TESTER_1_REG1_ADDR                                          (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x8c)

#define HWIO_USB2PHY_USB_PHY_HS_RX_TESTER_1_REG2_ADDR                                          (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x90)

#define HWIO_USB2PHY_USB_PHY_CFG0_ADDR                                                         (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x94)

#define HWIO_USB2PHY_UTMI_PHY_CMN_CTRL0_ADDR                                                   (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x98)

#define HWIO_USB2PHY_UTMI_PHY_CMN_CTRL1_ADDR                                                   (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x9c)

#define HWIO_USB2PHY_USB_PHY_REFCLK_CTRL_ADDR                                                  (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xa0)

#define HWIO_USB2PHY_USB_PHY_PWRDOWN_CTRL_ADDR                                                 (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xa4)

#define HWIO_USB2PHY_USB_PHY_TEST_DEBUG_CTRL_ADDR                                              (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xa8)

#define HWIO_USB2PHY_USB_PHY_RESET_CTRL_ADDR                                                   (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xac)

#define HWIO_USB2PHY_USB_PHY_AC_EN_ADDR                                                        (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xb0)

#define HWIO_USB2PHY_USB_PHY_RTUNE_SEL_ADDR                                                    (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xb4)

#define HWIO_USB2PHY_USB_PHY_FSEL_SEL_ADDR                                                     (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xb8)

#define HWIO_USB2PHY_USB_PHY_SKITTER_CTRL_1_ADDR                                               (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xbc)

#define HWIO_USB2PHY_USB_PHY_SKITTER_CTRL_2_ADDR                                               (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xc0)

#define HWIO_USB2PHY_USB_PHY_SKITTER_CTRL_3_ADDR                                               (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xc4)

#define HWIO_USB2PHY_USB_PHY_SKITTER_STICKY_NO_LSB_ADDR                                        (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xc8)

#define HWIO_USB2PHY_USB_PHY_SKITTER_STICKY_NO_MSB_ADDR                                        (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xcc)

#define HWIO_USB2PHY_USB_PHY_SKITTER_CALIB_COUNTER_LSB_ADDR                                    (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xd0)

#define HWIO_USB2PHY_USB_PHY_SKITTER_CALIB_COUNTER_MSB_ADDR                                    (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xd4)

#define HWIO_USB2PHY_USB_PHY_SKITTER_MUL_CONS_LSB_ADDR                                         (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xd8)

#define HWIO_USB2PHY_USB_PHY_SKITTER_MUL_CONS_MSB_ADDR                                         (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xdc)

#define HWIO_USB2PHY_USB_PHY_SKITTER_MFS_MISC_1_ADDR                                           (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xe0)

#define HWIO_USB2PHY_USB_PHY_SKITTER_MFS_MISC_2_ADDR                                           (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xe4)

#define HWIO_USB2PHY_USB_PHY_SKITTER_SPREAD_DETECT_RANGE_ADDR                                  (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xe8)

#define HWIO_USB2PHY_USB_PHY_SKITTER_JITTER_THRHOLD_ADDR                                       (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xec)

#define HWIO_USB2PHY_USB_PHY_SKITTER_STATUS_ADDR                                               (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xf0)

#define HWIO_USB2PHY_USB_PHY_INV_DLY_LSB_ADDR                                                  (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xf4)

#define HWIO_USB2PHY_USB_PHY_INV_DLY_MSB_ADDR                                                  (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xf8)

#define HWIO_USB2PHY_USB_PHY_EUD_CONNECTED_ADDR                                                (USB2PHY_CM_DWC_USB2_REG_BASE            + 0xfc)

#define HWIO_USB2PHY_USB_PHY_SKITTER_JITTER_ADDR                                               (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x100)

#define HWIO_USB2PHY_USB_PHY_TEST_DEBUG_CTRL_2_ADDR                                            (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x104)

#define HWIO_USB2PHY_EUD_PRESENT_SEL_ADDR                                                      (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x108)

#define HWIO_USB2PHY_USB_PHY_SKITTER_TIE_JITTER_LSB_ADDR                                       (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x10c)

#define HWIO_USB2PHY_USB_PHY_SKITTER_TIE_JITTER_MSB_ADDR                                       (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x110)

#define HWIO_USB2PHY_USB_PHY_SKITTER_CALIB_RODLY_1_ADDR                                        (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x114)

#define HWIO_USB2PHY_USB_PHY_SKITTER_CALIB_RODLY_2_ADDR                                        (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x118)

#define HWIO_USB2PHY_USB_PHY_SKITTER_CALIB_RODLY_3_ADDR                                        (USB2PHY_CM_DWC_USB2_REG_BASE            + 0x11c)

/*----------------------------------------------------------------------------
 * MODULE: USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM
 *--------------------------------------------------------------------------*/

#define USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE                         (AHB2PHY_SOUTH_BASE            + 0x00008000)
#define USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE_SIZE                    0x3c
#define USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE_USED                    0x38

#define HWIO_USB3_DP_PHY_USB3_DP_COM_PHY_MODE_CTRL_ADDR                                  (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x0)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_SW_RESET_ADDR                                       (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x4)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_POWER_DOWN_CTRL_ADDR                                (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x8)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_SWI_CTRL_ADDR                                       (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0xc)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_TYPEC_CTRL_ADDR                                     (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x10)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_TYPEC_PWRDN_CTRL_ADDR                               (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x14)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_DP_BIST_CFG_0_ADDR                                  (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x18)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_RESET_OVRD_CTRL_ADDR                                (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x1c)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_DBG_CLK_MUX_CTRL_ADDR                               (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x20)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_TYPEC_STATUS_ADDR                                   (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x24)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_PLACEHOLDER_STATUS_ADDR                             (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x28)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_REVISION_ID0_ADDR                                   (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x2c)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_REVISION_ID1_ADDR                                   (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x30)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_REVISION_ID2_ADDR                                   (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x34)

#define HWIO_USB3_DP_PHY_USB3_DP_COM_REVISION_ID3_ADDR                                   (USB3_DP_PHY_USB3_DP_COM_USB3_DP_COM_USB3_DP_COM_REG_BASE            + 0x38)

/*----------------------------------------------------------------------------
 * MODULE: USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT
 *--------------------------------------------------------------------------*/

#define USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE                    (AHB2PHY_SOUTH_BASE            + 0x00008200)
#define USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE_SIZE               0x5c
#define USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE_USED               0x58

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_INTGEN_STATUS1_ADDR                                      (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x0)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_INTGEN_STATUS2_ADDR                                      (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x4)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_CONFIG1_ADDR                                             (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x8)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_SIGNALBLK1_CONFIG1_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0xc)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_SIGNALBLK1_CONFIG2_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x10)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_SIGNALBLK1_CONFIG3_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x14)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_SIGNALBLK1_CONFIG4_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x18)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_SIGNALBLK1_CONFIG5_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x1c)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_SIGNALBLK2_CONFIG1_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x20)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_SIGNALBLK2_CONFIG2_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x24)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_SIGNALBLK2_CONFIG3_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x28)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_SIGNALBLK2_CONFIG4_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x2c)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_SIGNALBLK2_CONFIG5_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x30)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_STRINGBLK1_CONFIG1_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x34)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_STRINGBLK1_CONFIG2_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x38)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_STRINGBLK1_CONFIG3_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x3c)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_STRINGBLK1_CONFIG4_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x40)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_STRINGBLK1_CONFIG5_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x44)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_STRINGBLK2_CONFIG1_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x48)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_STRINGBLK2_CONFIG2_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x4c)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_STRINGBLK2_CONFIG3_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x50)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_STRINGBLK2_CONFIG4_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x54)

#define HWIO_USB3_DP_PHY_USB3_DP_DBGINT_STRINGBLK2_CONFIG5_ADDR                                  (USB3_DP_PHY_USB3_DP_DBGINT_USB3_DP_DBGINT_USB3_PCS_DEBUG_INT_REG_BASE            + 0x58)

/*----------------------------------------------------------------------------
 * MODULE: USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL
 *--------------------------------------------------------------------------*/

#define USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE                                    (AHB2PHY_SOUTH_BASE            + 0x00009000)
#define USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE_SIZE                               0x1c8
#define USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE_USED                               0x1c4

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_ATB_SEL1_ADDR                                                           (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_ATB_SEL2_ADDR                                                           (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_FREQ_UPDATE_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_BG_TIMER_ADDR                                                           (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SSC_EN_CENTER_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x10)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SSC_ADJ_PER1_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x14)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SSC_ADJ_PER2_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x18)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SSC_PER1_ADDR                                                           (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x1c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SSC_PER2_ADDR                                                           (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x20)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SSC_STEP_SIZE1_MODE0_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x24)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SSC_STEP_SIZE2_MODE0_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x28)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SSC_STEP_SIZE3_MODE0_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x2c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SSC_STEP_SIZE1_MODE1_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x30)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SSC_STEP_SIZE2_MODE1_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x34)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SSC_STEP_SIZE3_MODE1_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x38)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_POST_DIV_ADDR                                                           (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x3c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_POST_DIV_MUX_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x40)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_BIAS_EN_CLKBUFLR_EN_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x44)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CLK_ENABLE1_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x48)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SYS_CLK_CTRL_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x4c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SYSCLK_BUF_ENABLE_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x50)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_PLL_EN_ADDR                                                             (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x54)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_PLL_IVCO_ADDR                                                           (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x58)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CMN_IETRIM_ADDR                                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x5c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CMN_IPTRIM_ADDR                                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x60)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_EP_CLOCK_DETECT_CTRL_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x64)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SYSCLK_DET_COMP_STATUS_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x68)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CLK_EP_DIV_MODE0_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x6c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CLK_EP_DIV_MODE1_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x70)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CP_CTRL_MODE0_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x74)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CP_CTRL_MODE1_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x78)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_PLL_RCTRL_MODE0_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x7c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_PLL_RCTRL_MODE1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x80)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_PLL_CCTRL_MODE0_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x84)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_PLL_CCTRL_MODE1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x88)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_PLL_CNTRL_ADDR                                                          (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x8c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_BIAS_EN_CTRL_BY_PSM_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x90)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SYSCLK_EN_SEL_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x94)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CML_SYSCLK_SEL_ADDR                                                     (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x98)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_RESETSM_CNTRL_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x9c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_RESETSM_CNTRL2_ADDR                                                     (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xa0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_LOCK_CMP_EN_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xa4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_LOCK_CMP_CFG_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xa8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_LOCK_CMP1_MODE0_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xac)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_LOCK_CMP2_MODE0_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xb0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_LOCK_CMP1_MODE1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xb4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_LOCK_CMP2_MODE1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xb8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DEC_START_MODE0_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xbc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DEC_START_MSB_MODE0_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xc0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DEC_START_MODE1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xc4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DEC_START_MSB_MODE1_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xc8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DIV_FRAC_START1_MODE0_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xcc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DIV_FRAC_START2_MODE0_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xd0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DIV_FRAC_START3_MODE0_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xd4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DIV_FRAC_START1_MODE1_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xd8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DIV_FRAC_START2_MODE1_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xdc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DIV_FRAC_START3_MODE1_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xe0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_INTEGLOOP_INITVAL_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xe4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_INTEGLOOP_EN_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xe8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_INTEGLOOP_GAIN0_MODE0_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xec)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_INTEGLOOP_GAIN1_MODE0_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xf0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_INTEGLOOP_GAIN0_MODE1_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xf4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_INTEGLOOP_GAIN1_MODE1_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xf8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_INTEGLOOP_P_PATH_GAIN0_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0xfc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_INTEGLOOP_P_PATH_GAIN1_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x100)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCOCAL_DEADMAN_CTRL_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x104)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE_CTRL_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x108)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE_MAP_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x10c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE1_MODE0_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x110)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE2_MODE0_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x114)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE1_MODE1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x118)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE2_MODE1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x11c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE_INITVAL1_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x120)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE_INITVAL2_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x124)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE_MINVAL1_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x128)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE_MINVAL2_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x12c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE_MAXVAL1_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x130)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE_MAXVAL2_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x134)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE_TIMER1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x138)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_TUNE_TIMER2_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x13c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CMN_STATUS_ADDR                                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x140)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_RESET_SM_STATUS_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x144)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_RESTRIM_CODE_STATUS_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x148)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_PLLCAL_CODE1_STATUS_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x14c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_PLLCAL_CODE2_STATUS_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x150)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CLK_SELECT_ADDR                                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x154)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_HSCLK_SEL_ADDR                                                          (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x158)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_HSCLK_HS_SWITCH_SEL_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x15c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_INTEGLOOP_BINCODE_STATUS_ADDR                                           (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x160)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_PLL_ANALOG_ADDR                                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x164)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CORECLK_DIV_MODE0_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x168)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CORECLK_DIV_MODE1_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x16c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SW_RESET_ADDR                                                           (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x170)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CORE_CLK_EN_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x174)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_C_READY_STATUS_ADDR                                                     (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x178)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CMN_CONFIG_ADDR                                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x17c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CMN_RATE_OVERRIDE_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x180)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_SVS_MODE_CLK_SEL_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x184)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DEBUG_BUS0_ADDR                                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x188)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DEBUG_BUS1_ADDR                                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x18c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DEBUG_BUS2_ADDR                                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x190)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DEBUG_BUS3_ADDR                                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x194)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_DEBUG_BUS_SEL_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x198)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CMN_MISC1_ADDR                                                          (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x19c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CMN_MODE_ADDR                                                           (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x1a0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_CMN_MODE_CONTD_ADDR                                                     (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x1a4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_VCO_DC_LEVEL_CTRL_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x1a8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_BIN_VCOCAL_CMP_CODE1_MODE0_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x1ac)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_BIN_VCOCAL_CMP_CODE2_MODE0_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x1b0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_BIN_VCOCAL_CMP_CODE1_MODE1_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x1b4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_BIN_VCOCAL_CMP_CODE2_MODE1_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x1b8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_BIN_VCOCAL_HSCLK_SEL_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x1bc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_RESERVED_1_ADDR                                                         (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x1c0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_COM_MODE_OPERATION_STATUS_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_COM_USB3_QSERDES_COM_USB3_DP_QMP_PLL_REG_BASE            + 0x1c4)

/*----------------------------------------------------------------------------
 * MODULE: USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX
 *--------------------------------------------------------------------------*/

#define USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE                           (AHB2PHY_SOUTH_BASE            + 0x00009200)
#define USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE_SIZE                      0x160
#define USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE_USED                      0x15c

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_MODE_LANENO_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_INVERT_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_CLKBUF_ENABLE_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_TX_EMP_POST1_LVL_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_ADDR                                    (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x10)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_TX_DRV_LVL_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x14)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_TX_DRV_LVL_OFFSET_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x18)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_RESET_TSYNC_EN_ADDR                                           (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x1c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_ADDR                                   (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x20)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_TX_BAND_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x24)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_SLEW_CNTL_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x28)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_INTERFACE_SELECT_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x2c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_LPB_EN_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x30)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_RES_CODE_LANE_TX_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x34)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_RES_CODE_LANE_RX_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x38)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_ADDR                                  (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x3c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_ADDR                                  (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x40)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_PERL_LENGTH1_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x44)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_PERL_LENGTH2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x48)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_SERDES_BYP_EN_OUT_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x4c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DEBUG_BUS_SEL_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x50)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_TRANSCEIVER_BIAS_EN_ADDR                                      (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x54)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x58)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_TX_POL_INV_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x5c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_ADDR                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x60)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_PATTERN1_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x64)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_PATTERN2_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x68)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_PATTERN3_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x6c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_PATTERN4_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x70)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_PATTERN5_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x74)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_PATTERN6_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x78)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_PATTERN7_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x7c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_PATTERN8_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x80)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_LANE_MODE_1_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x84)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_LANE_MODE_2_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x88)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_LANE_MODE_3_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x8c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_LANE_MODE_4_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x90)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_LANE_MODE_5_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x94)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_ATB_SEL1_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x98)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_ATB_SEL2_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x9c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_RCV_DETECT_LVL_ADDR                                           (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xa0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_RCV_DETECT_LVL_2_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xa4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_PRBS_SEED1_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xa8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_PRBS_SEED2_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xac)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_PRBS_SEED3_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xb0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_PRBS_SEED4_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xb4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_RESET_GEN_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xb8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_RESET_GEN_MUXES_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xbc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_TRAN_DRVR_EMP_EN_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xc0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_TX_INTERFACE_MODE_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xc4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_VMODE_CTRL1_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xc8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xcc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_STATUS_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xd0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_ERROR_COUNT1_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xd4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_BIST_ERROR_COUNT2_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xd8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_ALOG_OBSV_BUS_STATUS_1_ADDR                                   (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xdc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_LANE_DIG_CONFIG_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xe0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_PI_QEC_CTRL_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xe4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_PRE_EMPH_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xe8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_SW_RESET_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xec)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DCC_OFFSET_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xf0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DCC_CMUX_POSTCAL_OFFSET_ADDR                                  (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xf4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DCC_CMUX_CAL_CTRL1_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xf8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DCC_CMUX_CAL_CTRL2_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0xfc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DIG_BKUP_CTRL_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x100)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DEBUG_BUS0_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x104)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DEBUG_BUS1_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x108)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DEBUG_BUS2_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x10c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DEBUG_BUS3_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x110)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_READ_EQCODE_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x114)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_READ_OFFSETCODE_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x118)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_IA_ERROR_COUNTER_LOW_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x11c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_IA_ERROR_COUNTER_HIGH_ADDR                                    (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x120)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_VGA_READ_CODE_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x124)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_VTH_READ_CODE_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x128)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DFE_TAP1_READ_CODE_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x12c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DFE_TAP2_READ_CODE_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x130)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_IDAC_STATUS_I_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x134)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_IDAC_STATUS_IBAR_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x138)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_IDAC_STATUS_Q_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x13c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_IDAC_STATUS_QBAR_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x140)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_IDAC_STATUS_A_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x144)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_IDAC_STATUS_ABAR_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x148)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_IDAC_STATUS_SM_ON_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x14c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_IDAC_STATUS_CAL_DONE_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x150)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_IDAC_STATUS_SIGNERROR_ADDR                                    (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x154)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DCC_CAL_STATUS_ADDR                                           (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x158)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXA_DCC_READ_CODE_STATUS_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_TXA_USB3_QSERDES_TXA_USB3_DP_QMP_TX_REG_BASE            + 0x15c)

/*----------------------------------------------------------------------------
 * MODULE: USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX
 *--------------------------------------------------------------------------*/

#define USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE                               (AHB2PHY_SOUTH_BASE            + 0x00009400)
#define USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE_SIZE                          0x1ec
#define USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE_USED                          0x1e8

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_FO_GAIN_HALF_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_FO_GAIN_QUARTER_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_FO_GAIN_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SO_GAIN_HALF_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SO_GAIN_QUARTER_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x10)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SO_GAIN_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x14)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SVS_FO_GAIN_HALF_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x18)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SVS_FO_GAIN_QUARTER_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SVS_FO_GAIN_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x20)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SVS_SO_GAIN_HALF_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x24)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SVS_SO_GAIN_QUARTER_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x28)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SVS_SO_GAIN_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x2c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_FASTLOCK_FO_GAIN_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x30)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SO_SATURATION_AND_ENABLE_ADDR                                (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x34)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_FO_TO_SO_DELAY_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x38)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_FASTLOCK_COUNT_LOW_ADDR                                      (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x3c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_FASTLOCK_COUNT_HIGH_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x40)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_PI_CONTROLS_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x44)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_PI_CTRL2_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x48)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SB2_THRESH1_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x4c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SB2_THRESH2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x50)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SB2_GAIN1_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x54)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_UCDR_SB2_GAIN2_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x58)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AUX_CONTROL_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x5c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AUX_DATA_TCOARSE_TFINE_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x60)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RCLK_AUXDATA_SEL_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x64)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AC_JTAG_ENABLE_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x68)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AC_JTAG_INITP_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x6c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AC_JTAG_INITN_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x70)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AC_JTAG_LVL_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x74)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AC_JTAG_MODE_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x78)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AC_JTAG_RESET_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x7c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_TERM_BW_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x80)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_RCVR_IQ_EN_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x84)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_I_DC_OFFSETS_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x88)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_IBAR_DC_OFFSETS_ADDR                                      (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x8c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_Q_DC_OFFSETS_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x90)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_QBAR_DC_OFFSETS_ADDR                                      (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x94)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_A_DC_OFFSETS_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x98)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_ABAR_DC_OFFSETS_ADDR                                      (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x9c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_EN_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xa0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_ENABLES_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xa4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_SIGN_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xa8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_HIGHZ_HIGHRATE_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xac)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_TERM_AC_BYPASS_DC_COUPLE_OFFSET_ADDR                           (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xb0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_DFE_1_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xb4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_DFE_2_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xb8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_DFE_3_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xbc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_DFE_4_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xc0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_TX_ADAPT_PRE_THRESH1_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xc4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_TX_ADAPT_PRE_THRESH2_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xc8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_TX_ADAPT_POST_THRESH_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xcc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_TX_ADAPT_MAIN_THRESH_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xd0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_VGA_CAL_CNTRL1_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xd4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_VGA_CAL_CNTRL2_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xd8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_GM_CAL_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xdc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_VGA_GAIN2_LSB_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xe0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_VGA_GAIN2_MSB_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xe4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_EQU_ADAPTOR_CNTRL1_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xe8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_EQU_ADAPTOR_CNTRL2_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xec)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_EQU_ADAPTOR_CNTRL3_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xf0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_EQU_ADAPTOR_CNTRL4_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xf4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_TSETTLE_LOW_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xf8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_TSETTLE_HIGH_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0xfc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_MEASURE_TIME_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x100)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_IDAC_ACCUMULATOR_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x104)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_EQ_OFFSET_LSB_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x108)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_EQ_OFFSET_MSB_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x10c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_EQ_OFFSET_ADAPTOR_CNTRL1_ADDR                                  (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x110)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_OFFSET_ADAPTOR_CNTRL2_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x114)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_SIGDET_ENABLES_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x118)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_SIGDET_CNTRL_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x11c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_SIGDET_LVL_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x120)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_SIGDET_DEGLITCH_CNTRL_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x124)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_BAND_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x128)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_CDR_FREEZE_UP_DN_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x12c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_CDR_RESET_OVERRIDE_ADDR                                           (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x130)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_INTERFACE_MODE_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x134)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_JITTER_GEN_MODE_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x138)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_SJ_AMP1_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x13c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_SJ_AMP2_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x140)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_SJ_PER1_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x144)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_SJ_PER2_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x148)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_PPM_OFFSET1_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x14c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_PPM_OFFSET2_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x150)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_SIGN_PPM_PERIOD1_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x154)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_SIGN_PPM_PERIOD2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x158)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_00_LOW_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x15c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_00_HIGH_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x160)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_00_HIGH2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x164)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_00_HIGH3_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x168)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_00_HIGH4_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x16c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_01_LOW_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x170)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_01_HIGH_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x174)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_01_HIGH2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x178)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_01_HIGH3_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x17c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_01_HIGH4_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x180)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_10_LOW_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x184)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_10_HIGH_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x188)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_10_HIGH2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x18c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_10_HIGH3_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x190)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_MODE_10_HIGH4_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x194)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_PHPRE_CTRL_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x198)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_PHPRE_INITVAL_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x19c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_DFE_EN_TIMER_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1a0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_DFE_CTLE_POST_CAL_OFFSET_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1a4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_DCC_CTRL1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1a8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_DCC_CTRL2_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1ac)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_VTH_CODE_ADDR                                                     (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1b0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_VTH_MIN_THRESH_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1b4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_VTH_MAX_THRESH_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1b8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_ALOG_OBSV_BUS_CTRL_1_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1bc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_PI_CTRL1_ADDR                                                     (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1c0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_PI_CTRL2_ADDR                                                     (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1c4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_PI_QUAD_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1c8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_IDATA1_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1cc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_IDATA2_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1d0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AUX_DATA1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1d4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AUX_DATA2_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1d8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AC_JTAG_OUTP_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1dc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_AC_JTAG_OUTN_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1e0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_RX_SIGDET_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1e4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXA_ALOG_OBSV_BUS_STATUS_1_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_RXA_USB3_QSERDES_RXA_USB3_DP_QMP_RX_REG_BASE            + 0x1e8)

/*----------------------------------------------------------------------------
 * MODULE: USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX
 *--------------------------------------------------------------------------*/

#define USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE                           (AHB2PHY_SOUTH_BASE            + 0x00009600)
#define USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE_SIZE                      0x160
#define USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE_USED                      0x15c

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_MODE_LANENO_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_INVERT_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_CLKBUF_ENABLE_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_TX_EMP_POST1_LVL_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_ADDR                                    (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x10)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_TX_DRV_LVL_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x14)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_TX_DRV_LVL_OFFSET_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x18)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_RESET_TSYNC_EN_ADDR                                           (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x1c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_ADDR                                   (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x20)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_TX_BAND_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x24)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_SLEW_CNTL_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x28)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_INTERFACE_SELECT_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x2c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_LPB_EN_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x30)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_RES_CODE_LANE_TX_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x34)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_RES_CODE_LANE_RX_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x38)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_ADDR                                  (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x3c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_ADDR                                  (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x40)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_PERL_LENGTH1_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x44)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_PERL_LENGTH2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x48)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_SERDES_BYP_EN_OUT_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x4c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DEBUG_BUS_SEL_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x50)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_TRANSCEIVER_BIAS_EN_ADDR                                      (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x54)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x58)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_TX_POL_INV_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x5c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_ADDR                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x60)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_PATTERN1_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x64)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_PATTERN2_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x68)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_PATTERN3_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x6c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_PATTERN4_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x70)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_PATTERN5_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x74)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_PATTERN6_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x78)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_PATTERN7_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x7c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_PATTERN8_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x80)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_LANE_MODE_1_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x84)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_LANE_MODE_2_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x88)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_LANE_MODE_3_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x8c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_LANE_MODE_4_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x90)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_LANE_MODE_5_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x94)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_ATB_SEL1_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x98)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_ATB_SEL2_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x9c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_RCV_DETECT_LVL_ADDR                                           (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xa0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_RCV_DETECT_LVL_2_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xa4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_PRBS_SEED1_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xa8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_PRBS_SEED2_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xac)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_PRBS_SEED3_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xb0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_PRBS_SEED4_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xb4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_RESET_GEN_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xb8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_RESET_GEN_MUXES_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xbc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_TRAN_DRVR_EMP_EN_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xc0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_TX_INTERFACE_MODE_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xc4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_VMODE_CTRL1_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xc8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xcc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_STATUS_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xd0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_ERROR_COUNT1_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xd4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_BIST_ERROR_COUNT2_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xd8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_ALOG_OBSV_BUS_STATUS_1_ADDR                                   (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xdc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_LANE_DIG_CONFIG_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xe0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_PI_QEC_CTRL_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xe4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_PRE_EMPH_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xe8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_SW_RESET_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xec)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DCC_OFFSET_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xf0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DCC_CMUX_POSTCAL_OFFSET_ADDR                                  (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xf4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DCC_CMUX_CAL_CTRL1_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xf8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DCC_CMUX_CAL_CTRL2_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0xfc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DIG_BKUP_CTRL_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x100)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DEBUG_BUS0_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x104)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DEBUG_BUS1_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x108)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DEBUG_BUS2_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x10c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DEBUG_BUS3_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x110)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_READ_EQCODE_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x114)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_READ_OFFSETCODE_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x118)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_IA_ERROR_COUNTER_LOW_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x11c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_IA_ERROR_COUNTER_HIGH_ADDR                                    (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x120)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_VGA_READ_CODE_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x124)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_VTH_READ_CODE_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x128)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DFE_TAP1_READ_CODE_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x12c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DFE_TAP2_READ_CODE_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x130)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_IDAC_STATUS_I_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x134)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_IDAC_STATUS_IBAR_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x138)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_IDAC_STATUS_Q_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x13c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_IDAC_STATUS_QBAR_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x140)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_IDAC_STATUS_A_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x144)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_IDAC_STATUS_ABAR_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x148)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_IDAC_STATUS_SM_ON_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x14c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_IDAC_STATUS_CAL_DONE_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x150)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_IDAC_STATUS_SIGNERROR_ADDR                                    (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x154)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DCC_CAL_STATUS_ADDR                                           (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x158)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_TXB_DCC_READ_CODE_STATUS_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_TXB_USB3_QSERDES_TXB_USB3_DP_QMP_TX_REG_BASE            + 0x15c)

/*----------------------------------------------------------------------------
 * MODULE: USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX
 *--------------------------------------------------------------------------*/

#define USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE                               (AHB2PHY_SOUTH_BASE            + 0x00009800)
#define USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE_SIZE                          0x1ec
#define USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE_USED                          0x1e8

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_FO_GAIN_HALF_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_FO_GAIN_QUARTER_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_FO_GAIN_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SO_GAIN_HALF_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SO_GAIN_QUARTER_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x10)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SO_GAIN_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x14)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SVS_FO_GAIN_HALF_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x18)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SVS_FO_GAIN_QUARTER_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SVS_FO_GAIN_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x20)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SVS_SO_GAIN_HALF_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x24)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SVS_SO_GAIN_QUARTER_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x28)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SVS_SO_GAIN_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x2c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_FASTLOCK_FO_GAIN_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x30)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SO_SATURATION_AND_ENABLE_ADDR                                (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x34)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_FO_TO_SO_DELAY_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x38)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_FASTLOCK_COUNT_LOW_ADDR                                      (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x3c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_FASTLOCK_COUNT_HIGH_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x40)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_PI_CONTROLS_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x44)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_PI_CTRL2_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x48)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SB2_THRESH1_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x4c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SB2_THRESH2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x50)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SB2_GAIN1_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x54)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_UCDR_SB2_GAIN2_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x58)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AUX_CONTROL_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x5c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AUX_DATA_TCOARSE_TFINE_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x60)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RCLK_AUXDATA_SEL_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x64)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AC_JTAG_ENABLE_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x68)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AC_JTAG_INITP_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x6c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AC_JTAG_INITN_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x70)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AC_JTAG_LVL_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x74)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AC_JTAG_MODE_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x78)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AC_JTAG_RESET_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x7c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_TERM_BW_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x80)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_RCVR_IQ_EN_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x84)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_I_DC_OFFSETS_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x88)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_IBAR_DC_OFFSETS_ADDR                                      (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x8c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_Q_DC_OFFSETS_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x90)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_QBAR_DC_OFFSETS_ADDR                                      (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x94)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_A_DC_OFFSETS_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x98)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_ABAR_DC_OFFSETS_ADDR                                      (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x9c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_EN_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xa0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_ENABLES_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xa4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_SIGN_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xa8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_HIGHZ_HIGHRATE_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xac)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_TERM_AC_BYPASS_DC_COUPLE_OFFSET_ADDR                           (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xb0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_DFE_1_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xb4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_DFE_2_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xb8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_DFE_3_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xbc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_DFE_4_ADDR                                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xc0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_TX_ADAPT_PRE_THRESH1_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xc4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_TX_ADAPT_PRE_THRESH2_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xc8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_TX_ADAPT_POST_THRESH_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xcc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_TX_ADAPT_MAIN_THRESH_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xd0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_VGA_CAL_CNTRL1_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xd4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_VGA_CAL_CNTRL2_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xd8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_GM_CAL_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xdc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_VGA_GAIN2_LSB_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xe0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_VGA_GAIN2_MSB_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xe4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_EQU_ADAPTOR_CNTRL1_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xe8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_EQU_ADAPTOR_CNTRL2_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xec)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_EQU_ADAPTOR_CNTRL3_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xf0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_EQU_ADAPTOR_CNTRL4_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xf4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_TSETTLE_LOW_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xf8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_TSETTLE_HIGH_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0xfc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_MEASURE_TIME_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x100)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_IDAC_ACCUMULATOR_ADDR                                          (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x104)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_EQ_OFFSET_LSB_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x108)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_EQ_OFFSET_MSB_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x10c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_EQ_OFFSET_ADAPTOR_CNTRL1_ADDR                                  (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x110)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_OFFSET_ADAPTOR_CNTRL2_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x114)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_SIGDET_ENABLES_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x118)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_SIGDET_CNTRL_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x11c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_SIGDET_LVL_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x120)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_SIGDET_DEGLITCH_CNTRL_ADDR                                        (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x124)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_BAND_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x128)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_CDR_FREEZE_UP_DN_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x12c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_CDR_RESET_OVERRIDE_ADDR                                           (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x130)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_INTERFACE_MODE_ADDR                                            (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x134)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_JITTER_GEN_MODE_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x138)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_SJ_AMP1_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x13c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_SJ_AMP2_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x140)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_SJ_PER1_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x144)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_SJ_PER2_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x148)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_PPM_OFFSET1_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x14c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_PPM_OFFSET2_ADDR                                                  (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x150)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_SIGN_PPM_PERIOD1_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x154)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_SIGN_PPM_PERIOD2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x158)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_00_LOW_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x15c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_00_HIGH_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x160)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_00_HIGH2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x164)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_00_HIGH3_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x168)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_00_HIGH4_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x16c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_01_LOW_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x170)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_01_HIGH_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x174)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_01_HIGH2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x178)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_01_HIGH3_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x17c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_01_HIGH4_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x180)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_10_LOW_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x184)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_10_HIGH_ADDR                                              (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x188)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_10_HIGH2_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x18c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_10_HIGH3_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x190)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_MODE_10_HIGH4_ADDR                                             (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x194)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_PHPRE_CTRL_ADDR                                                   (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x198)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_PHPRE_INITVAL_ADDR                                                (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x19c)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_DFE_EN_TIMER_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1a0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_DFE_CTLE_POST_CAL_OFFSET_ADDR                                     (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1a4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_DCC_CTRL1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1a8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_DCC_CTRL2_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1ac)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_VTH_CODE_ADDR                                                     (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1b0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_VTH_MIN_THRESH_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1b4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_VTH_MAX_THRESH_ADDR                                               (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1b8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_ALOG_OBSV_BUS_CTRL_1_ADDR                                         (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1bc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_PI_CTRL1_ADDR                                                     (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1c0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_PI_CTRL2_ADDR                                                     (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1c4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_PI_QUAD_ADDR                                                      (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1c8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_IDATA1_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1cc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_IDATA2_ADDR                                                       (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1d0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AUX_DATA1_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1d4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AUX_DATA2_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1d8)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AC_JTAG_OUTP_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1dc)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_AC_JTAG_OUTN_ADDR                                                 (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1e0)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_RX_SIGDET_ADDR                                                    (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1e4)

#define HWIO_USB3_DP_PHY_USB3_QSERDES_RXB_ALOG_OBSV_BUS_STATUS_1_ADDR                                       (USB3_DP_PHY_USB3_QSERDES_RXB_USB3_QSERDES_RXB_USB3_DP_QMP_RX_REG_BASE            + 0x1e8)

/*----------------------------------------------------------------------------
 * MODULE: USB3_DP_PHY_USB3_PCS_MISC_USB3_PCS_MISC_USB3_PCS_MISC
 *--------------------------------------------------------------------------*/

#define USB3_DP_PHY_USB3_PCS_MISC_USB3_PCS_MISC_USB3_PCS_MISC_REG_BASE                     (AHB2PHY_SOUTH_BASE            + 0x00009a00)
#define USB3_DP_PHY_USB3_PCS_MISC_USB3_PCS_MISC_USB3_PCS_MISC_REG_BASE_SIZE                0x18
#define USB3_DP_PHY_USB3_PCS_MISC_USB3_PCS_MISC_USB3_PCS_MISC_REG_BASE_USED                0x14

#define HWIO_USB3_DP_PHY_USB3_PCS_MISC_TYPEC_CTRL_ADDR                                     (USB3_DP_PHY_USB3_PCS_MISC_USB3_PCS_MISC_USB3_PCS_MISC_REG_BASE            + 0x0)

#define HWIO_USB3_DP_PHY_USB3_PCS_MISC_TYPEC_PWRDN_CTRL_ADDR                               (USB3_DP_PHY_USB3_PCS_MISC_USB3_PCS_MISC_USB3_PCS_MISC_REG_BASE            + 0x4)

#define HWIO_USB3_DP_PHY_USB3_PCS_MISC_PCS_MISC_CONFIG1_ADDR                               (USB3_DP_PHY_USB3_PCS_MISC_USB3_PCS_MISC_USB3_PCS_MISC_REG_BASE            + 0x8)

#define HWIO_USB3_DP_PHY_USB3_PCS_MISC_CLAMP_ENABLE_ADDR                                   (USB3_DP_PHY_USB3_PCS_MISC_USB3_PCS_MISC_USB3_PCS_MISC_REG_BASE            + 0xc)

#define HWIO_USB3_DP_PHY_USB3_PCS_MISC_TYPEC_STATUS_ADDR                                   (USB3_DP_PHY_USB3_PCS_MISC_USB3_PCS_MISC_USB3_PCS_MISC_REG_BASE            + 0x10)

#define HWIO_USB3_DP_PHY_USB3_PCS_MISC_PLACEHOLDER_STATUS_ADDR                             (USB3_DP_PHY_USB3_PCS_MISC_USB3_PCS_MISC_USB3_PCS_MISC_REG_BASE            + 0x14)

/*----------------------------------------------------------------------------
 * MODULE: USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE
 *--------------------------------------------------------------------------*/

#define USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE                              (AHB2PHY_SOUTH_BASE            + 0x00009b00)
#define USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE_SIZE                         0x4c
#define USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE_USED                         0x48

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_PCS_STATUS1_ADDR                                           (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x0)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_PCS_STATUS2_ADDR                                           (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x4)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_PCS_STATUS2_CLEAR_ADDR                                     (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x8)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_PCS_STATUS3_ADDR                                           (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0xc)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_BIST_CHK_ERR_CNT_L_STATUS_ADDR                             (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x10)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_BIST_CHK_ERR_CNT_H_STATUS_ADDR                             (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x14)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_BIST_CHK_STATUS_ADDR                                       (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x18)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_INSIG_SW_CTRL1_ADDR                                        (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x1c)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_INSIG_MX_CTRL1_ADDR                                        (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x20)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_OUTSIG_SW_CTRL1_ADDR                                       (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x24)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_OUTSIG_MX_CTRL1_ADDR                                       (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x28)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_TEST_CONTROL1_ADDR                                         (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x2c)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_BIST_CTRL_ADDR                                             (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x30)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_PRBS_SEED0_ADDR                                            (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x34)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_PRBS_SEED1_ADDR                                            (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x38)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_FIXED_PAT_CTRL_ADDR                                        (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x3c)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_EQ_CONFIG_ADDR                                             (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x40)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_TEST_CONTROL2_ADDR                                         (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x44)

#define HWIO_USB3_DP_PHY_USB3_PCS_LN_TEST_CONTROL3_ADDR                                         (USB3_DP_PHY_USB3_PCS_LN_USB3_PCS_LN_USB3_PCS_LANE_REG_BASE            + 0x48)

/*----------------------------------------------------------------------------
 * MODULE: USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS
 *--------------------------------------------------------------------------*/

#define USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE                                                     (AHB2PHY_SOUTH_BASE            + 0x00009c00)
#define USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE_SIZE                                                0x1f0
#define USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE_USED                                                0x1ec

#define HWIO_USB3_DP_PHY_USB3_PCS_SW_RESET_ADDR                                                             (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x0)

#define HWIO_USB3_DP_PHY_USB3_PCS_REVISION_ID0_ADDR                                                         (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x4)

#define HWIO_USB3_DP_PHY_USB3_PCS_REVISION_ID1_ADDR                                                         (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x8)

#define HWIO_USB3_DP_PHY_USB3_PCS_REVISION_ID2_ADDR                                                         (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xc)

#define HWIO_USB3_DP_PHY_USB3_PCS_REVISION_ID3_ADDR                                                         (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x10)

#define HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS1_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x14)

#define HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS2_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x18)

#define HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS3_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1c)

#define HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS4_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x20)

#define HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS5_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x24)

#define HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS6_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x28)

#define HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS7_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x2c)

#define HWIO_USB3_DP_PHY_USB3_PCS_DEBUG_BUS_0_STATUS_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x30)

#define HWIO_USB3_DP_PHY_USB3_PCS_DEBUG_BUS_1_STATUS_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x34)

#define HWIO_USB3_DP_PHY_USB3_PCS_DEBUG_BUS_2_STATUS_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x38)

#define HWIO_USB3_DP_PHY_USB3_PCS_DEBUG_BUS_3_STATUS_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x3c)

#define HWIO_USB3_DP_PHY_USB3_PCS_POWER_DOWN_CONTROL_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x40)

#define HWIO_USB3_DP_PHY_USB3_PCS_START_CONTROL_ADDR                                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x44)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_SW_CTRL1_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x48)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_SW_CTRL2_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x4c)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_SW_CTRL3_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x50)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_SW_CTRL4_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x54)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_SW_CTRL5_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x58)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_SW_CTRL6_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x5c)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_SW_CTRL7_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x60)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_SW_CTRL8_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x64)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_MX_CTRL1_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x68)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_MX_CTRL2_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x6c)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_MX_CTRL3_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x70)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_MX_CTRL4_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x74)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_MX_CTRL5_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x78)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_MX_CTRL7_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x7c)

#define HWIO_USB3_DP_PHY_USB3_PCS_INSIG_MX_CTRL8_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x80)

#define HWIO_USB3_DP_PHY_USB3_PCS_OUTSIG_SW_CTRL1_ADDR                                                      (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x84)

#define HWIO_USB3_DP_PHY_USB3_PCS_OUTSIG_MX_CTRL1_ADDR                                                      (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x88)

#define HWIO_USB3_DP_PHY_USB3_PCS_CLAMP_ENABLE_ADDR                                                         (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x8c)

#define HWIO_USB3_DP_PHY_USB3_PCS_POWER_STATE_CONFIG1_ADDR                                                  (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x90)

#define HWIO_USB3_DP_PHY_USB3_PCS_POWER_STATE_CONFIG2_ADDR                                                  (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x94)

#define HWIO_USB3_DP_PHY_USB3_PCS_FLL_CNTRL1_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x98)

#define HWIO_USB3_DP_PHY_USB3_PCS_FLL_CNTRL2_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x9c)

#define HWIO_USB3_DP_PHY_USB3_PCS_FLL_CNT_VAL_L_ADDR                                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xa0)

#define HWIO_USB3_DP_PHY_USB3_PCS_FLL_CNT_VAL_H_TOL_ADDR                                                    (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xa4)

#define HWIO_USB3_DP_PHY_USB3_PCS_FLL_MAN_CODE_ADDR                                                         (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xa8)

#define HWIO_USB3_DP_PHY_USB3_PCS_TEST_CONTROL1_ADDR                                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xac)

#define HWIO_USB3_DP_PHY_USB3_PCS_TEST_CONTROL2_ADDR                                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xb0)

#define HWIO_USB3_DP_PHY_USB3_PCS_TEST_CONTROL3_ADDR                                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xb4)

#define HWIO_USB3_DP_PHY_USB3_PCS_TEST_CONTROL4_ADDR                                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xb8)

#define HWIO_USB3_DP_PHY_USB3_PCS_TEST_CONTROL5_ADDR                                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xbc)

#define HWIO_USB3_DP_PHY_USB3_PCS_TEST_CONTROL6_ADDR                                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xc0)

#define HWIO_USB3_DP_PHY_USB3_PCS_LOCK_DETECT_CONFIG1_ADDR                                                  (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xc4)

#define HWIO_USB3_DP_PHY_USB3_PCS_LOCK_DETECT_CONFIG2_ADDR                                                  (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xc8)

#define HWIO_USB3_DP_PHY_USB3_PCS_LOCK_DETECT_CONFIG3_ADDR                                                  (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xcc)

#define HWIO_USB3_DP_PHY_USB3_PCS_LOCK_DETECT_CONFIG4_ADDR                                                  (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xd0)

#define HWIO_USB3_DP_PHY_USB3_PCS_LOCK_DETECT_CONFIG5_ADDR                                                  (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xd4)

#define HWIO_USB3_DP_PHY_USB3_PCS_LOCK_DETECT_CONFIG6_ADDR                                                  (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xd8)

#define HWIO_USB3_DP_PHY_USB3_PCS_REFGEN_REQ_CONFIG1_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xdc)

#define HWIO_USB3_DP_PHY_USB3_PCS_REFGEN_REQ_CONFIG2_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xe0)

#define HWIO_USB3_DP_PHY_USB3_PCS_REFGEN_REQ_CONFIG3_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xe4)

#define HWIO_USB3_DP_PHY_USB3_PCS_BIST_CTRL_ADDR                                                            (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xe8)

#define HWIO_USB3_DP_PHY_USB3_PCS_PRBS_POLY0_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xec)

#define HWIO_USB3_DP_PHY_USB3_PCS_PRBS_POLY1_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xf0)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT0_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xf4)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT1_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xf8)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT2_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0xfc)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT3_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x100)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT4_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x104)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT5_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x108)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT6_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x10c)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT7_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x110)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT8_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x114)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT9_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x118)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT10_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x11c)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT11_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x120)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT12_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x124)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT13_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x128)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT14_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x12c)

#define HWIO_USB3_DP_PHY_USB3_PCS_FIXED_PAT15_ADDR                                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x130)

#define HWIO_USB3_DP_PHY_USB3_PCS_TXMGN_CONFIG_ADDR                                                         (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x134)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXMGN_V0_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x138)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXMGN_V1_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x13c)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXMGN_V2_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x140)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXMGN_V3_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x144)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXMGN_V4_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x148)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXMGN_V0_RS_ADDR                                                    (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x14c)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXMGN_V1_RS_ADDR                                                    (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x150)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXMGN_V2_RS_ADDR                                                    (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x154)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXMGN_V3_RS_ADDR                                                    (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x158)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXMGN_V4_RS_ADDR                                                    (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x15c)

#define HWIO_USB3_DP_PHY_USB3_PCS_G3S2_TXMGN_MAIN_ADDR                                                      (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x160)

#define HWIO_USB3_DP_PHY_USB3_PCS_G3S2_TXMGN_MAIN_RS_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x164)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXDEEMPH_M6DB_ADDR                                                  (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x168)

#define HWIO_USB3_DP_PHY_USB3_PCS_G12S1_TXDEEMPH_M3P5DB_ADDR                                                (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x16c)

#define HWIO_USB3_DP_PHY_USB3_PCS_G3S2_PRE_GAIN_ADDR                                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x170)

#define HWIO_USB3_DP_PHY_USB3_PCS_G3S2_POST_GAIN_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x174)

#define HWIO_USB3_DP_PHY_USB3_PCS_G3S2_PRE_POST_OFFSET_ADDR                                                 (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x178)

#define HWIO_USB3_DP_PHY_USB3_PCS_G3S2_PRE_GAIN_RS_ADDR                                                     (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x17c)

#define HWIO_USB3_DP_PHY_USB3_PCS_G3S2_POST_GAIN_RS_ADDR                                                    (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x180)

#define HWIO_USB3_DP_PHY_USB3_PCS_G3S2_PRE_POST_OFFSET_RS_ADDR                                              (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x184)

#define HWIO_USB3_DP_PHY_USB3_PCS_RX_SIGDET_LVL_ADDR                                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x188)

#define HWIO_USB3_DP_PHY_USB3_PCS_RX_SIGDET_DTCT_CNTRL_ADDR                                                 (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x18c)

#define HWIO_USB3_DP_PHY_USB3_PCS_RCVR_DTCT_DLY_P1U2_L_ADDR                                                 (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x190)

#define HWIO_USB3_DP_PHY_USB3_PCS_RCVR_DTCT_DLY_P1U2_H_ADDR                                                 (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x194)

#define HWIO_USB3_DP_PHY_USB3_PCS_RATE_SLEW_CNTRL1_ADDR                                                     (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x198)

#define HWIO_USB3_DP_PHY_USB3_PCS_RATE_SLEW_CNTRL2_ADDR                                                     (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x19c)

#define HWIO_USB3_DP_PHY_USB3_PCS_PWRUP_RESET_DLY_TIME_AUXCLK_ADDR                                          (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1a0)

#define HWIO_USB3_DP_PHY_USB3_PCS_P2U3_WAKEUP_DLY_TIME_AUXCLK_L_ADDR                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1a4)

#define HWIO_USB3_DP_PHY_USB3_PCS_P2U3_WAKEUP_DLY_TIME_AUXCLK_H_ADDR                                        (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1a8)

#define HWIO_USB3_DP_PHY_USB3_PCS_TSYNC_RSYNC_TIME_ADDR                                                     (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1ac)

#define HWIO_USB3_DP_PHY_USB3_PCS_CDR_RESET_TIME_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1b0)

#define HWIO_USB3_DP_PHY_USB3_PCS_TSYNC_DLY_TIME_ADDR                                                       (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1b4)

#define HWIO_USB3_DP_PHY_USB3_PCS_ELECIDLE_DLY_SEL_ADDR                                                     (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1b8)

#define HWIO_USB3_DP_PHY_USB3_PCS_CMN_ACK_OUT_SEL_ADDR                                                      (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1bc)

#define HWIO_USB3_DP_PHY_USB3_PCS_ALIGN_DETECT_CONFIG1_ADDR                                                 (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1c0)

#define HWIO_USB3_DP_PHY_USB3_PCS_ALIGN_DETECT_CONFIG2_ADDR                                                 (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1c4)

#define HWIO_USB3_DP_PHY_USB3_PCS_ALIGN_DETECT_CONFIG3_ADDR                                                 (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1c8)

#define HWIO_USB3_DP_PHY_USB3_PCS_ALIGN_DETECT_CONFIG4_ADDR                                                 (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1cc)

#define HWIO_USB3_DP_PHY_USB3_PCS_PCS_TX_RX_CONFIG_ADDR                                                     (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1d0)

#define HWIO_USB3_DP_PHY_USB3_PCS_RX_IDLE_DTCT_CNTRL_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1d4)

#define HWIO_USB3_DP_PHY_USB3_PCS_RX_DCC_CAL_CONFIG_ADDR                                                    (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1d8)

#define HWIO_USB3_DP_PHY_USB3_PCS_EQ_CONFIG1_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1dc)

#define HWIO_USB3_DP_PHY_USB3_PCS_EQ_CONFIG2_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1e0)

#define HWIO_USB3_DP_PHY_USB3_PCS_EQ_CONFIG3_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1e4)

#define HWIO_USB3_DP_PHY_USB3_PCS_EQ_CONFIG4_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1e8)

#define HWIO_USB3_DP_PHY_USB3_PCS_EQ_CONFIG5_ADDR                                                           (USB3_DP_PHY_USB3_PCS_USB3_PCS_USB3_PCS_REG_BASE            + 0x1ec)

/*----------------------------------------------------------------------------
 * MODULE: USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3
 *--------------------------------------------------------------------------*/

#define USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE                                     (AHB2PHY_SOUTH_BASE            + 0x00009f00)
#define USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE_SIZE                                0x64
#define USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE_USED                                0x60

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_POWER_STATE_CONFIG1_ADDR                                            (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x0)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_AUTONOMOUS_MODE_STATUS_ADDR                                         (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x4)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_AUTONOMOUS_MODE_CTRL_ADDR                                           (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x8)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_AUTONOMOUS_MODE_CTRL2_ADDR                                          (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0xc)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_LFPS_RXTERM_IRQ_SOURCE_STATUS_ADDR                                  (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x10)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_LFPS_RXTERM_IRQ_CLEAR_ADDR                                          (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x14)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_LFPS_DET_HIGH_COUNT_VAL_ADDR                                        (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x18)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_LFPS_TX_ECSTART_ADDR                                                (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x1c)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_LFPS_PER_TIMER_VAL_ADDR                                             (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x20)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_LFPS_TX_END_CNT_U3_START_ADDR                                       (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x24)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_LFPS_CONFIG1_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x28)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_RXEQTRAINING_LOCK_TIME_ADDR                                         (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x2c)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_RXEQTRAINING_WAIT_TIME_ADDR                                         (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x30)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_RXEQTRAINING_CTLE_TIME_ADDR                                         (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x34)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_RXEQTRAINING_WAIT_TIME_S2_ADDR                                      (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x38)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_RXEQTRAINING_DFE_TIME_S2_ADDR                                       (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x3c)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_RCVR_DTCT_DLY_U3_L_ADDR                                             (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x40)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_RCVR_DTCT_DLY_U3_H_ADDR                                             (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x44)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_ARCVR_DTCT_EN_PERIOD_ADDR                                           (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x48)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_ARCVR_DTCT_CM_DLY_ADDR                                              (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x4c)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_TXONESZEROS_RUN_LENGTH_ADDR                                         (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x50)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_ALFPS_DEGLITCH_VAL_ADDR                                             (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x54)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_SIGDET_STARTUP_TIMER_VAL_ADDR                                       (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x58)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_TEST_CONTROL_ADDR                                                   (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x5c)

#define HWIO_USB3_DP_PHY_USB3_PCS_USB3_RXTERMINATION_DLY_SEL_ADDR                                          (USB3_DP_PHY_USB3_PCS_USB3_USB3_PCS_USB3_USB3_PCS_USB3_REG_BASE            + 0x60)


#endif /* __HALUSBHWIO_SETTINGS_H__ */
