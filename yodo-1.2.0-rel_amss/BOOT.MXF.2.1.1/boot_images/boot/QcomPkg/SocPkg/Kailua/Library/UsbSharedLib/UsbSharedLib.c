/*=======================================================================*//**
 * @file        UsbSharedInit.c
 * @author:     pmahajan
 * @date        03-feb-2017
 *
 * @brief       USB common & shared USB core init implementation.
 *
 * @details     This file contains API's the Init sequence for HS and SS core implementation.
 *
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2016-2022 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
//============================================================================
// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// 
// when          who     what, where, why
// ----------   -----    ----------------------------------------------------------
// 07/13/21     pohanw   Add dp toggle from dci_common to usbshared
// 04/05/21     vpallapo Added Phy reg programming support from device tree binary
// 11/23/20     jaychoi  Makena USB PRIM, SEC, and MP Support
// 07/26/18     jaychoi  Added SSP and SS RX training improvement and PHY tuning
// 04/10/18     amitg    Poipu BU Fixes/Phy tuning for primary and secondary port
// 03/19/18     gk       Updated SS and HS Phy sequence for Multiport from latest HPG 
// 03/30/17     pm       Added configuration for sec Clock and core
// 02/03/17     pm       Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "DALSys.h"    // To get phy settings
#include "qusb_log.h"
#include "qusb_dci_common.h"
#include "UsbSharedLib.h"
#include "HalusbHWIO.h"
#include <Library/DTBExtnLib.h>
#include <Library/DTBExtnUEFILib.h>

#include "UsbSharedLibI2c.h"
#include <stdio.h>
#include <string.h>


#define USB_RUMI      (1)
#define USB_APB_REG_FLAG  (1)
#define USB_EUSB_FLAG       (1)
#define USB_PHY_WRITE_DELAY (20)

// === MINIMUM LOGGING =======================================================
// Due to shortage of IMEM, the code size needs to be reduced, so disable logging
// For debugging, enable them and change libssizcfg
#define usb_shared_error_log(a,b,c)
#define usb_shared_info_log(a,b,c)
#define usb_shared_uart_log_info(a)
#define usb_shared_uart_log_info1(a,b)
#define usb_shared_uart_log_warn(a,b)
// === MINIMUM LOGGING =======================================================
// ===========================================================================
/**
 * @function usb_shared_report_generic_error
 * 
 * @brief   This function reports generic error with error code to reduce 
 *          file size from string
 * 
 * @param   error_code      - error code
 *
 * @return  none
 */
// ===========================================================================
// Don't make it static to reduce code size
void usb_shared_report_generic_error(uint32 line_number)
{
  usb_shared_uart_log_error("UsbSharedLib.c error in line", line_number);
}



#define USB_SHARED_POLL_SS_PHY_TRAINING_TIMEOUT_US         (10000)

boolean qusb_dci_ss_lane_phy_override     = FALSE;
boolean qusb_dci_ss_phy_no_csr_reset      = FALSE;

#define QUSB_DCI_HS_PHY_SEC_CFG_ARRAY_ENTRY_CNT (sizeof(qusb_dci_hs_phy_sec_cfg)/sizeof(qusb_phy_cfg_type))
#define QUSB_DCI_SS_PHY_SEC_COMMON_CFG_ARRAY_ENTRY_CNT (sizeof(qusb_dci_ss_phy_sec_cfg_common)/sizeof(qusb_phy_cfg_type))

//============================================================================
// QUSB High-Speed Secondary PHY Configuration Array
//============================================================================
#ifdef USB_SEC_FLAG

static const qusb_phy_cfg_type qusb_dci_hs_phy_sec_cfg[] = 
  {
    { QUSB_HWIO_ADDR_EMPTY,                         (0x00) }, // 0  
    { QUSB_HWIO_ADDR_EMPTY,                         (0x00) }, // 1  
    { QUSB_HWIO_ADDR_EMPTY,                         (0x00) }, // 2  
    { QUSB_HWIO_ADDR_EMPTY,                         (0x00) }, // 3  
    //--------------------------------------------------------------------------------------
    { QUSB_HWIO_ADDR_EMPTY,  (0x00) }, // 4  
    { QUSB_HWIO_ADDR_EMPTY,  (0x00) }, // 5  
    { QUSB_HWIO_ADDR_EMPTY,  (0x00) }, // 6  
    { QUSB_HWIO_ADDR_EMPTY,  (0x00) }, // 7  
    //--------------------------------------------------------------------------------------
    { QUSB_HWIO_ADDR_END,                           (0x00) }, // 8  
    { QUSB_HWIO_ADDR_END,                           (0x00) }, // 9  
    { QUSB_HWIO_ADDR_END,                           (0x00) }, // 10 
    { QUSB_HWIO_ADDR_END,                           (0x00) }, // 11 
    //--------------------------------------------------------------------------------------
  };

// #5/20/2020 Chitwan & Lahaina USB3 UNI PHY Configuration 
// #V0.95 Chitwan USB3 Gen2 PHY Configuration - differential or SE 19.2MHz refclk 19.2MHz AuxClk autonomous mode enabled 
static const qusb_phy_cfg_type qusb_dci_ss_phy_sec_cfg_common[] =
{
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_POWER_DOWN_CONTROL_ADDR,                  (0x01) }, // 0  
  { HWIO_USB3_UNI_PHY_QSERDES_COM_SYSCLK_EN_SEL_ADDR,                             (0x1A) }, // 1  
  { HWIO_USB3_UNI_PHY_QSERDES_COM_BIN_VCOCAL_HSCLK_SEL_ADDR,                      (0x11) }, // 2  
  { HWIO_USB3_UNI_PHY_QSERDES_COM_HSCLK_SEL_ADDR,                                 (0x01) }, // 3  
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_COM_DEC_START_MODE0_ADDR,                           (0x82) }, // 4  
  { HWIO_USB3_UNI_PHY_QSERDES_COM_DIV_FRAC_START1_MODE0_ADDR,                     (0xAB) }, // 5  
  { HWIO_USB3_UNI_PHY_QSERDES_COM_DIV_FRAC_START2_MODE0_ADDR,                     (0xEA) }, // 6  
  { HWIO_USB3_UNI_PHY_QSERDES_COM_DIV_FRAC_START3_MODE0_ADDR,                     (0x02) }, // 7  
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_COM_BIN_VCOCAL_CMP_CODE1_MODE0_ADDR,                (0xCA) }, // 8  
  { HWIO_USB3_UNI_PHY_QSERDES_COM_BIN_VCOCAL_CMP_CODE2_MODE0_ADDR,                (0x1E) }, // 9  
  { HWIO_USB3_UNI_PHY_QSERDES_COM_CP_CTRL_MODE0_ADDR,                             (0x06) }, // 10 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_PLL_RCTRL_MODE0_ADDR,                           (0x16) }, // 11 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_COM_PLL_CCTRL_MODE0_ADDR,                           (0x36) }, // 12 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_VCO_TUNE1_MODE0_ADDR,                           (0x24) }, // 13 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_LOCK_CMP2_MODE0_ADDR,                           (0x34) }, // 14 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_LOCK_CMP1_MODE0_ADDR,                           (0x14) }, // 15 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_COM_LOCK_CMP_EN_ADDR,                               (0x04) }, // 16 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_SYSCLK_BUF_ENABLE_ADDR,                         (0x0A) }, // 17 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_VCO_TUNE2_MODE1_ADDR,                           (0x02) }, // 18 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_VCO_TUNE1_MODE1_ADDR,                           (0x24) }, // 19 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_COM_CORECLK_DIV_MODE1_ADDR,                         (0x08) }, // 20 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_DEC_START_MODE1_ADDR,                           (0x82) }, // 21 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_DIV_FRAC_START1_MODE1_ADDR,                     (0xAB) }, // 22 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_DIV_FRAC_START2_MODE1_ADDR,                     (0xEA) }, // 23 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_COM_DIV_FRAC_START3_MODE1_ADDR,                     (0x02) }, // 24 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_LOCK_CMP2_MODE1_ADDR,                           (0x82) }, // 25 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_LOCK_CMP1_MODE1_ADDR,                           (0x34) }, // 26 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_CP_CTRL_MODE1_ADDR,                             (0x06) }, // 27 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_COM_PLL_RCTRL_MODE1_ADDR,                           (0x16) }, // 28 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_PLL_CCTRL_MODE1_ADDR,                           (0x36) }, // 29 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_BIN_VCOCAL_CMP_CODE1_MODE1_ADDR,                (0xCA) }, // 30 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_BIN_VCOCAL_CMP_CODE2_MODE1_ADDR,                (0x1E) }, // 31 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_COM_SSC_EN_CENTER_ADDR,                             (0x01) }, // 32 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_SSC_PER1_ADDR,                                  (0x31) }, // 33 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_SSC_PER2_ADDR,                                  (0x01) }, // 34 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_SSC_STEP_SIZE1_MODE1_ADDR,                      (0xDE) }, // 35 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_COM_SSC_STEP_SIZE2_MODE1_ADDR,                      (0x07) }, // 36 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_SSC_STEP_SIZE1_MODE0_ADDR,                      (0xDE) }, // 37 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_SSC_STEP_SIZE2_MODE0_ADDR,                      (0x07) }, // 38 
  { HWIO_USB3_UNI_PHY_QSERDES_COM_VCO_TUNE_MAP_ADDR,                              (0x02) }, // 39 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_MODE_00_HIGH4_ADDR,                           (0xDC) }, // 40 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_MODE_00_HIGH3_ADDR,                           (0xBD) }, // 41 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_MODE_00_HIGH2_ADDR,                           (0xFF) }, // 42 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_MODE_00_HIGH_ADDR,                            (0x7F) }, // 43 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_MODE_00_LOW_ADDR,                             (0xFF) }, // 44 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_MODE_01_HIGH4_ADDR,                           (0xA9) }, // 45 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_MODE_01_HIGH3_ADDR,                           (0x7B) }, // 46 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_MODE_01_HIGH2_ADDR,                           (0xE4) }, // 47 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_MODE_01_HIGH_ADDR,                            (0x24) }, // 48 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_MODE_01_LOW_ADDR,                             (0x64) }, // 49 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_UCDR_PI_CONTROLS_ADDR,                           (0x99) }, // 50 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_UCDR_SB2_THRESH1_ADDR,                           (0x08) }, // 51 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_RX_UCDR_SB2_THRESH2_ADDR,                           (0x08) }, // 52 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_UCDR_SB2_GAIN1_ADDR,                             (0x00) }, // 53 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_UCDR_SB2_GAIN2_ADDR,                             (0x04) }, // 54 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_UCDR_FASTLOCK_FO_GAIN_ADDR,                      (0x2F) }, // 55 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_RX_UCDR_FASTLOCK_COUNT_LOW_ADDR,                    (0xFF) }, // 56 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_UCDR_FASTLOCK_COUNT_HIGH_ADDR,                   (0x0F) }, // 57 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_UCDR_FO_GAIN_ADDR,                               (0x09) }, // 58 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_VGA_CAL_CNTRL1_ADDR,                             (0x54) }, // 59 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_RX_VGA_CAL_CNTRL2_ADDR,                             (0x0F) }, // 60 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_EQU_ADAPTOR_CNTRL2_ADDR,                      (0x0F) }, // 61 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_EQU_ADAPTOR_CNTRL4_ADDR,                      (0x0A) }, // 62 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_EQ_OFFSET_ADAPTOR_CNTRL1_ADDR,                (0x47) }, // 63 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_RX_RX_OFFSET_ADAPTOR_CNTRL2_ADDR,                   (0x80) }, // 64 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_SIGDET_CNTRL_ADDR,                               (0x04) }, // 65 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_SIGDET_DEGLITCH_CNTRL_ADDR,                      (0x0E) }, // 66 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_DFE_CTLE_POST_CAL_OFFSET_ADDR,                   (0x38) }, // 67 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_RX_UCDR_SO_GAIN_ADDR,                               (0x05) }, // 68 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_GM_CAL_ADDR,                                     (0x00) }, // 69 
  { HWIO_USB3_UNI_PHY_QSERDES_RX_SIGDET_ENABLES_ADDR,                             (0x00) }, // 70 
  { HWIO_USB3_UNI_PHY_QSERDES_TX_LANE_MODE_1_ADDR,                                (0xA5) }, // 71 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_TX_LANE_MODE_2_ADDR,                                (0x82) }, // 72 
  { HWIO_USB3_UNI_PHY_QSERDES_TX_LANE_MODE_3_ADDR,                                (0x3F) }, // 73 
  { HWIO_USB3_UNI_PHY_QSERDES_TX_LANE_MODE_4_ADDR,                                (0x3F) }, // 74 
  { HWIO_USB3_UNI_PHY_QSERDES_TX_PI_QEC_CTRL_ADDR,                                (0x21) }, // 75 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_QSERDES_TX_RES_CODE_LANE_OFFSET_TX_ADDR,                    (0x08) }, // 76 
  { HWIO_USB3_UNI_PHY_QSERDES_TX_RES_CODE_LANE_OFFSET_RX_ADDR,                    (0x0E) }, // 77 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_LOCK_DETECT_CONFIG1_ADDR,                 (0xD0) }, // 78 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_LOCK_DETECT_CONFIG2_ADDR,                 (0x07) }, // 79 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_LOCK_DETECT_CONFIG3_ADDR,                 (0x20) }, // 80 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_LOCK_DETECT_CONFIG6_ADDR,                 (0x13) }, // 81 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_RCVR_DTCT_DLY_P1U2_L_ADDR,                (0xE7) }, // 82 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_RCVR_DTCT_DLY_P1U2_H_ADDR,                (0x03) }, // 83 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_RX_SIGDET_LVL_ADDR,                       (0xAA) }, // 84 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_PCS_TX_RX_CONFIG_ADDR,                    (0x0C) }, // 85 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_USB3_RXEQTRAINING_DFE_TIME_S2_ADDR,       (0x07) }, // 86 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_USB3_LFPS_DET_HIGH_COUNT_VAL_ADDR,        (0xF8) }, // 87 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_CDR_RESET_TIME_ADDR,                      (0x0A) }, // 88 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_ALIGN_DETECT_CONFIG1_ADDR,                (0x88) }, // 89 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_ALIGN_DETECT_CONFIG2_ADDR,                (0x13) }, // 90 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_EQ_CONFIG1_ADDR,                          (0x4B) }, // 91 
  //--------------------------------------------------------------------------------------
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_EQ_CONFIG5_ADDR,                          (0x10) }, // 92 
  { HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_REFGEN_REQ_CONFIG1_ADDR,                  (0x21) }, // 93 
  { QUSB_HWIO_ADDR_END,                                                           (0x00) }, // 94 
};
#endif


// DTB USB High-Speed Primary PHY Configuration 
// For programming prim phy in HS mode, in case of device tree blob is not available
static const usb_dtb_phy_cfg_type usb_dtb_prim_hs_phy_cfg[] =
  {
    { QUSB_HWIO_ADDR_EMPTY,                              0x00 }, // 0
    { QUSB_HWIO_ADDR_EMPTY,                              0x00 }, // 1
    { QUSB_HWIO_ADDR_EMPTY,                              0x00 }, // 2
    { QUSB_HWIO_ADDR_EMPTY,                              0x00 }, // 3
  };


#ifdef USB_APB_REG_FLAG
// WARNING:
// !!! Always double check power on reset (POR) value for every target !!!!
#define QUSB_DCI_APB_CFG_WRITE_ARRAY_ENTRY_CNT    (sizeof(usb_shared_apb_reg_write_addr)/sizeof(uint8))
#define QUSB_DCI_APB_CFG_READ_ARRAY_ENTRY_CNT     (sizeof(usb_shared_apb_reg_read_addr)/sizeof(uint8))

#define APB_USB_PHY_EMPTY                        (0xFF)
#define USB_APB_TIMEOUT_US                       (1000)
#define CR_XCVR0_DIG_CTL_EUSB_STATE_JMP_DBG_ADDR (0x57)
//----------------------------------------------------------------------------
// Static Function Declarations and Definitions
//----------------------------------------------------------------------------
static void usb_shared_phy_reg_array_process
(
  const uint32 *address_array,
  const uint8  *value_array,
  uint32        start_index,
  uint32        array_entry_cnt
);

static void usb_shared_apb_table_process
(
  const uint8  *addr_array, 
  uint16       *value_array, 
  uint32        array_entry_cnt,
  boolean       write_flag
);

static const uint8 usb_shared_apb_reg_write_addr[] =
{
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,

  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,

  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,

  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
};

static uint16 usb_shared_apb_reg_write_val[] =
{
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,

  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,

  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,

  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
};

static const uint8 usb_shared_apb_reg_read_addr[] =
{
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,

  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,

  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,

  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
  APB_USB_PHY_EMPTY,                                                            // 0x0000,
};

static uint16 usb_shared_apb_reg_read_val[] =
{
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,

  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,

  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,

  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
  /* APB_USB_PHY_EMPTY,                                                         */ 0x0000,
};

#endif

  
// ===========================================================================
/**
 * @function    usb_shared_lib_process_phy_reg_array
 * 
 * @brief   This function reads from array which define list of hwio writes for
 *          USB PHY
 * 
 * @param   cfg_array   - array holding address and value of HW register
 *          start_index     - starting index for array processing
 *          array_entry_cnt - number of entries in the array
 * 
 * @return  None
 * 
 */
// ===========================================================================
static void usb_shared_lib_process_phy_reg_array
  (
    const qusb_phy_cfg_type* phy_table,
    uint32        start_index, 
    uint32        array_entry_cnt
  )
  {
    uint32 index = start_index;
  
    if ( (NULL == phy_table)
        || (0 == array_entry_cnt) )
    {
      usb_shared_error_log(QUSB_DCI_PHY_REG_ARRAY_PROCESS__FAIL_LOG, 0, (uint32)(uintptr_t)phy_table);
      usb_shared_report_generic_error(__LINE__);
      return;
    }
    else
    {
      usb_shared_error_log(QUSB_DCI_PHY_REG_ARRAY_PROCESS__START_LOG, 0, start_index);

      for (; index < array_entry_cnt; index++)
      {
        if (QUSB_HWIO_ADDR_END == phy_table[index].address)
        {
          break;
        }
  
        if (QUSB_HWIO_ADDR_EMPTY == phy_table[index].address)
        {
          continue;
        }
        
        out_dword(phy_table[index].address, phy_table[index].value);
      }
    }
    usb_shared_error_log(QUSB_DCI_PHY_REG_ARRAY_PROCESS____END_LOG, 0, index);
  
}

//============================================================================

/**
* @function USB_SHARED_HS_PHY_INIT
*
* @brief    API used to initialize the High Speed Primary PHY 
*
*/
//============================================================================
boolean usb_shared_hs_phy_init(void)
{
  USB_DTB_STATUS_TYPE dtb_status =USB_DTB_STATUS_SUCCESS;
  usb_shared_uart_log_info("usb_shared_hs_phy_init: ++");
  
  // Kailua is 38.4 MHz
  // 1  USB_PHY_CFG0[1]   1'b1  UTMI_PHY_CMN_CNTRL_OVERRIDE_EN=1. This is a MUX select signal.
  HWIO_USB2PHY_USB_PHY_CFG0_OUT(0x2);

  // 2	USB_PHY_UTMI_CTRL5[1] 	1'b1	POR (phy_reset) to the PHY
  //    This power on reset must be asserted at least for 10us, after all supplies ramped-up.
  //    POR is active high
  HWIO_USB2PHY_USB_PHY_UTMI_CTRL5_OUT(0x2);
  usb_shared_delay_us(10);

  // 3	USB_PHY_HS_PHY_CTRL_COMMON0[0]	1'b1	Asynchronous enable for PHY
  //    phy_enable='1'
  //    If this signal is low when phy_reset de-assertion occurs, the PHY will remain inactive and will not perform power-up sequence. When this signal is asserted, then the PHY will start the normal
  //    functional mode after performing power-up sequence.
  HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_OUT(0x9);

  // 4  USB_PHY_HS_PHY_CTRL_COMMON0[3]  1'b1  Retention Mode Enable
  //    Set retenable_n = 1'b1  
  //    Retention mode allows the eUSB PHY to retain internal digital core signal states when the eUSB PHY vdd supply is lowered to a process specific retention voltage level.
  //    Retention mode also forces all internal vdd-to-vdd12 level translators into a pre-defined state based on the eUSB PHY operating mode. 
  //    Before entering Retention mode, retenable_n must be asserted to 1'b0. 
  //    This signal must be set to 1'b1 at all times when the eUSB PHY vdd supply is powered, 
  //    and is meant to be asserted to 1'b0 only when decreasing the vdd voltage to an intermediate level that is not supported by the eUSB PHY in normal operating modes. 
  //    Asserting this signal powers down all analog blocks; however, the high-voltage interrupt signals are still valid outputs
  HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_OUT(0x9);

  // 5  USB_PHY_APB_ACCESS_CMD[2] 1'b1  APB Logic Reset
  //    apb_logic_reset = 1
  //    Reset all APB related logic, including SNPS APB FSM but not the APB registers
  HWIO_USB2PHY_USB_PHY_APB_ACCESS_CMD_OUT(0x4);

  // 6  UTMI_PHY_CMN_CTRL0[6] 1'b0  Burn-in Test Enable
  //    test_burnin = 1'b0
  //    This input enables the built-in, self-burn-in testing function of the PHY. At assertion of this signal, the PHY performs a power-on-reset sequence and then enters HS Loopback mode. In HS Loopback mode, the PHY continues to transmit alternating 1's and 0's at the maximum bit rate until test_burnin is deasserted. This input has precedence over the utmi_suspend_n, utmi_port_reset and utmi_sleep_n signals. Therefore, these signals are internally overridden when test_burnin is asserted. Asserting test_burnin causes the ref_freq_sel[1:0] signal to be overridden, so that the PHY requires a 24-MHz reference clock on ref_clk. If this signal is not used, tie it low. To accomplish the same function with a different reference clock frequency, the PHY can be put into BIST Test Packet Repeat mode
  //       
  HWIO_USB2PHY_UTMI_PHY_CMN_CTRL0_OUT(0x0);

  //  scan_mode = 1'b0     Scan Test Enable
  //  Done at the PHY wrapper pin level   scan_mode = 1'b0
  //  tap_test_mode_tdr   When this test signal is high, the eUSB 2.0 PHY is in Scan mode and all scannable flip-flops are clocked by scan_clk or OCC output clocks. In normal operation, both scan_shift and scan_mode must be set to 1'b0. If this signal is not used, tie it low
  //  There is no register

  // 7  USB_PHY_FSEL_SEL  1'b1  FSEL MUX select for SW override
  HWIO_USB2PHY_USB_PHY_FSEL_SEL_OUT(0x1);
  
  // 8  USB_PHY_HS_PHY_CTRL_COMMON0[6:4]  3'b000  This sets the refclk frequency.
  //    3'b100  fsel<2:0>
  //    3'b000 = 19.2 MHz
  //    3'b100 = 38.4 MHz
  //    (Note: This control with register is not needed for default settings). 
  HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_OUT(0x49);
  
  // 9  USB_PHY_CFG_CTRL_2[7:0] 8'b10010000 Control of the feedback multiplication ratio
  //    8'b11001000 phy_cfg_pll_fb_div_7_0<7:0>
  //    8'b10010000 = 19.2 MHz
  //    8'b11001000 = 38.4 MHz
  //    phy_cfg_pll_fb_div is 12 bits shared with step 6.
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_2_OUT(0xC8);
  
  // 10 USB_PHY_CFG_CTRL_3[3:0] 4'b0001 Control of the feedback multiplication ratio
  //    4'b0000 phy_cfg_pll_fb_div_11_8<3:0>
  //    4'b0001 = 19.2 MHz
  //    4'b0000 = 38.4 MHz
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_3_OUT(0x0);
  
  // 11 USB_PHY_CFG_CTRL_3[7:4] 4'b0000 Control of the input frequency division ratio
  //    4'b0000 phy_cfg_pll_ref_div<3:0>
  //    4'b0000 = 19.2 MHz
  //    4'b0000 = 38.4 MHz
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_3_OUT(0x0);
  
  // 12 USB_PHY_CFG_CTRL_1[7:1] 7'b0000001  PLL loop bias configuration.
  //    phy_cfg_pll_cpbias_cntrl<6:0>
  //    The setting is the same for both frequencies
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_1_OUT(0x2);

  // 13 USB_PHY_CFG_CTRL_4[1:0] 2'b01 PLL vco source gain
  //    phy_cfg_pll_gmp_cntrl<1:0>
  //    The setting is the same for both frequencies
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_4_OUT(0x21);
  
  // 14 USB_PHY_CFG_CTRL_4[7:2] 6'b001000 Gain of PLL Integral Charge Pump
  //    phy_cfg_pll_int_cntrl<5:0>
  //    The setting is the same for both frequencies
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_4_OUT(0x21);  
  
  // 15 USB_PHY_CFG_CTRL_5[5:0] 6'b010000 Gain of PLL Proportional Charge Pump
  //    phy_cfg_pll_prop_cntrl<5:0>
  //    The setting is the same for both frequencies
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_5_OUT(0x50);  
  
  // 16 USB_PHY_CFG_CTRL_6[2:0] 3'b000  PLL VCO configuration
  //    phy_cfg_pll_vco_cntrl<2:0>
  //    The setting is the same for both frequencies
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_6_OUT(0x0);

  // 17 USB_PHY_CFG_CTRL_5[7:6] 2'b01 Configuration for PLL voltage reference level
  //    phy_cfg_pll_vref_tune<1:0>
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_5_OUT(0x50);  
  
  // 18 selects UTMI data bus width. Wordinterface<#> = 0; for 8 bits interface  (60 MHz)
  //    Input from chip top. No register control. Only 60 MHz, 8 bit UTMI interface is supported. Tied at the chip top.

  // 19 USB_PHY_USB_PHY_HS_PHY_CTRL2 [4]  1'b1  VBUS MUX Selection
  //    vbus_det_ext_sel
  //    Selection mux between HW port vs. SW CSR register. 
  HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_OUT(0x17);
  
  // 20 USB_PHY_HS_PHY_CTRL2[0] 1'b1  VBUS valid indication
  //    vbus_valid_ext
  //    Software writes to this bit to indicate the status of the VBUS External Valid; this bit is default to 1 and selected only when the swi_utmi_phy_cmn_ctrl_override_en bit  {USB_PHY_CFG0[1]} is set to 1 
  //    Note, the VBUS is not used in the eUSB2 PHY. It is used in PMIC/PMI and the information needs to be transferred to AOSS via the SPMI interface.
  HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_OUT(0x17);
  

  // 21 set parameter override, if needed - this is eUSB signal 
  // Set Parameter Override (if needed)  
  //init Device Tree Binary acess for PHY settings and program PHY registers
  dtb_status = usb_shared_xbl_dtb_node_init("/soc/usb0/hs_phy_cfg");
  if(USB_DTB_STATUS_SUCCESS != dtb_status)
  {
    usb_shared_uart_log_error("HS: usb_shared_xbl_dtb_node_init dtb inaccessible", dtb_status);
    
    //Program PHY HS registers
    usb_shared_uart_log_error("usb_hs_phy_cfg size ", sizeof(usb_dtb_prim_hs_phy_cfg));
     if(!usb_shared_process_phy_reg_dtb_list(usb_dtb_prim_hs_phy_cfg, sizeof(usb_dtb_prim_hs_phy_cfg)))
    {
      usb_shared_uart_log_error("HS: usb_shared_process_phy_reg_dtb_list Failed", 0);
    }
  }
  #ifdef USB_APB_REG_FLAG
  usb_shared_apb_table_process(usb_shared_apb_reg_write_addr, usb_shared_apb_reg_write_val, QUSB_DCI_APB_CFG_WRITE_ARRAY_ENTRY_CNT, TRUE);
  usb_shared_apb_table_process(usb_shared_apb_reg_read_addr, usb_shared_apb_reg_read_val, QUSB_DCI_APB_CFG_WRITE_ARRAY_ENTRY_CNT, FALSE);
  #endif

  // 21 USB_PHY_CFG_CTRL_9[2:0] 3'b000  HS Transmitter Pre-Emphasis Control
  //    phy_cfg_tx_preemp_tune[2:0]
  //    000: (design default) HS Transmitter pre-emphasis switch off
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_9_OUT(0xC8);

  // 22 USB_PHY_CFG_CTRL_8 [5:3]  3'b011  HS DC Voltage Level Adjustment
  //    phy_cfg_tx_hs_vref_tune[2:0]
  //    HS DC Voltage Level increased
  //    011: Default
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_8_OUT(0x18);
  
  // 23 USB_PHY_CFG_CTRL_9 [6:5]  2'b10 HS Transmitter Rise/Fall Time Adjustment
  //    phy_cfg_tx_rise_tune[1:0] 
  //    10: Default
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_9_OUT(0xC8);
  
  // 24 USB_PHY_CFG_CTRL_8 [7:6]  2'b00 Transmitter High-Speed Crossover Adjustment
  //    phy_cfg_tx_hs_xv_tune[1:0]
  //    00: 0 V, Default
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_8_OUT(0x18);

  
  // 25 USB_PHY_CFG_CTRL_9 [4:3]  2'b01 USB Source Impedance Adjustment
  //    phy_cfg_tx_res_tune[1:0]
  //    01: Default
  HWIO_USB2PHY_USB_PHY_CFG_CTRL_9_OUT(0xC8);
  
  //   set all inputs to default    
  //    During RESET all the outputs are indeterminate and ignored       

  
  // 26 USB_PHY_HS_PHY_CTRL2[3]   1'b1  USB2_SUSPEND_N_SEL
  //    This sets USB2_SUSPEND_N_SEL=1.  
  //    SW option for selecting between HW and SW suspend_n signal
  //    (0): selects HW suspend_n;                                       
  //    (1): selects SW suspend_n;                                       
  //    Default: selects HW suspend_n
  HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_OUT(0x1F);
  
  // 27 USB_PHY_HS_PHY_CTRL2[2]   1'b1  USB2_SUSPEND_N
  //    This sets USB2_SUSPEND_N=1.
  HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_OUT(0x1F);

  
  // 28 USB_PHY_UTMI_CTRL0[0]   1'b1  SLEEPM
  //    sets sleepm = 1; until PHYCLOCK is available. 
  HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_OUT(0x1);

  
  // 29 USB_PHY_HS_PHY_CTRL_COMMON0 [1]   1'b1  SIDDQ MUX Selection
  //    siddq_sel = 1
  //    This is a MUX selects signal between external iddq_ctrl port and internal CSR register (SIDDQ).
  //    iddq_ctrl port is coming from outside of the wrapper
  HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_OUT(0x4B);

  // 30 USB_PHY_HS_PHY_CTRL_COMMON0[2]  1'b0  SIDDQ
  //    SIDDQ is set to 0 
  //    The analog blocks are powered up.
  HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_OUT(0x4B);

  
  // 31 USB_PHY_UTMI_CTRL5[1]   1'b0  POR (phy_reset)
  //    set POR = 0; release the POR from high to low.
  HWIO_USB2PHY_USB_PHY_UTMI_CTRL5_OUT(0x0);
  
  // 32 USB_PHY_HS_PHY_CTRL2[3]   1'b0  USB2_SUSPEND_N_SEL
  //    This sets USB2_SUSPEND_N_SEL= 0. This de-selects from sw override.
  HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_OUT(0x17);

  
  // 33 USB_PHY_CFG0[1]   1'b0  UTMI_PHY_CMN_CNTRL_OVERRIDE_EN=0. Restore MUX select signal.
  //    This step is needed for ATE and SW.
  HWIO_USB2PHY_USB_PHY_CFG0_OUT(0x0);

  usb_shared_delay_us(20);
  return TRUE;

}


//============================================================================

/**
* @function USB_SHARED_HS_PHY_INIT_SEC
*
* @brief    API used to initialize the High Speed Secondary PHY 
*
*/
//============================================================================
#ifdef USB_SEC_FLAG
boolean usb_shared_hs_phy_init_sec(void)
{

  usb_shared_uart_log_info("usb_shared_hs_phy_init_sec: ++");

  usb_shared_uart_log_error("hs phy cfg size", QUSB_DCI_HS_PHY_SEC_CFG_ARRAY_ENTRY_CNT);

  // 1. Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  // >> USB_PHY_CFG0[1] = 1; UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_USB2PHY_SEC_USB_PHY_CFG0_OUTM(HWIO_USB2PHY_SEC_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 0x1 << HWIO_USB2PHY_SEC_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);

  // 2. Set the POR signal = 1 ; active high 
  // >> USB_PHY_UTMI_CTRL5[1] = 1 ; POR 
  HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL5_OUTM(HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL5_POR_BMSK, 0x1 << HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL5_POR_SHFT);

  // 3. USB_PHY_FSEL_SEL 
  HWIO_USB2PHY_SEC_USB_PHY_FSEL_SEL_OUTM(HWIO_USB2PHY_SEC_USB_PHY_FSEL_SEL_FSEL_SEL_BMSK, 0x1 << HWIO_USB2PHY_SEC_USB_PHY_FSEL_SEL_FSEL_SEL_SHFT);
  
    
  // 4. Set all strapping options:
  // >> Select reference clock frequency. FSEL[6:4] = 000; for 19.2MHz clock 
  //    USB_PHY_HS_PHY_CTRL_COMMON0[6:4] = 000; FSEL (Note: This control with register is not needed for default settings) 
  //    usb2phy_fsel[2:0]= 000, At the chip top, the usb2phy_fsel I/O need be tied off to 000 for default settings. 
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_BMSK, 0x0 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_SHFT);

  // 5. Selects the PLL bandwidth, PLLBTUNE=1
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON1_PLLBTUNE_BMSK, 0x1 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON1_PLLBTUNE_SHFT);
    
  // 6. >> Select reference clock source. REFCLKSEL[1:0] = 10; select the CLKCORE input 
  //    USB_PHY_REFCLK_CTRL[1:0] = 10; REFCLK_SEL 
  HWIO_USB2PHY_SEC_USB_PHY_REFCLK_CTRL_OUTM(HWIO_USB2PHY_SEC_USB_PHY_REFCLK_CTRL_REFCLK_SEL_BMSK, 0x2 << HWIO_USB2PHY_SEC_USB_PHY_REFCLK_CTRL_REFCLK_SEL_SHFT);
    
  // 7. Input from chip top. No register control. Only 60Mhz 8 bit UTMI interface is supported. Tied at the chip top.
  // Selects UTMI data bus width.

  // 8. Select external VBUS valid by setting VBUSVLDEXTSEL0 to 1
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_BMSK, 0x1 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_SHFT);
  
  // 9. VBUSVLDEXT0 is set to 1. This make VBUS signal valid.  Note, the VBUS and ID are not used in the femtoPHY.  
  // They are used in PMI and information needs to transferred from PMI to AOSS via the SPMI interface
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL1_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_BMSK, 0x1 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_SHFT);
  
  // Change to REXT (1), default is using EFUSE (0)
  HWIO_USB2PHY_SEC_USB_PHY_RTUNE_SEL_OUTM(HWIO_USB2PHY_SEC_USB_PHY_RTUNE_SEL_RTUNE_SEL_BMSK, 0x0 << HWIO_USB2PHY_SEC_USB_PHY_RTUNE_SEL_RTUNE_SEL_SHFT);

  // 10-15 Set Parameter Override (if needed)
  usb_shared_lib_process_phy_reg_array(
    (const qusb_phy_cfg_type*) qusb_dci_hs_phy_sec_cfg,
    0,
    QUSB_DCI_HS_PHY_SEC_CFG_ARRAY_ENTRY_CNT);


  // 16. Set VREGBYPASS = 1; The internal VREG18 is not used and bypassed. It requires VDDH= 1.8V power supply from outside 
  // >> USB_PHY_HS_PHY_CTRL_COMMON2[0] = 1; VREGBYPASS 
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON2_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON2_VREGBYPASS_BMSK, 0x1 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON2_VREGBYPASS_SHFT);

  // 17. Set ATERESET = 0 or tie ATERESET with POR: PHYCLOCK is available after atereset is deasserted
  HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL5_OUTM(HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL5_ATERESET_BMSK, 0x0 << HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL5_ATERESET_SHFT);
  
  // 18. Set TESTDATAOUTSEL to 0
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_BMSK, 0x0 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_SHFT);
  
  // 19. Set TESTCLK = 0
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_BMSK, 0x0 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_SHFT);

  // 20. Set VATESTENB = 00
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_BMSK, 0x0 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_SHFT);

  // 21. Set TESTDATAIN bits to zero until PHYCLOCK is available  
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_TEST0_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_TEST0_TESTDATAIN_BMSK, 0x0 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_TEST0_TESTDATAIN_SHFT);
  
  // 22. This sets USB2_SUSPEND_N_SEL = 1.  Set suspendm = 1; until PHYCLOCK is available by setting USB2_SUSPEND_N_SEL and USB2_SUSPEND_N  
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK, 0x1 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);

  // 23. Set USB2_SUSPEND_N = 1
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_BMSK, 0x1 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SHFT);
  
  // 24. Set sleepm = 1; until PHY CLOCK is available
  HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL0_OUTM(HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL0_SLEEPM_BMSK, 0x1 << HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL0_SLEEPM_SHFT);

  // 25. SIDDQ is set to 0. the analog block are powered up.
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_BMSK, 0x0 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_SHFT);

  // 26. Set POR = 0; release the POR from high to low
  // >> USB_PHY_UTMI_CTRL5[1] = 0; POR 
  HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL5_OUTM(HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL5_POR_BMSK, 0x0 << HWIO_USB2PHY_SEC_USB_PHY_UTMI_CTRL5_POR_SHFT);

  // 27. This sets USB2_SUSPEND_N_SEL = 0.  This de-selects from sw override   
  HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK, 0x0 << HWIO_USB2PHY_SEC_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);

  usb_shared_delay_us(20);

  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  // >> USB_PHY_CFG0[1] = 0; UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_USB2PHY_SEC_USB_PHY_CFG0_OUTM(HWIO_USB2PHY_SEC_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 0x0 << HWIO_USB2PHY_SEC_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);

  usb_shared_delay_us(20);

  return TRUE;
}
#endif
//============================================================================
/**
* @function USB_SHARED_HS_PHY_INIT
*
* @brief API used to initialize the High Speed RUMI PHY
*
* @Note : 
*
* @param    core_num
*               1st core (primary) = 0, 2nd = 1, etc
*           port_num
*               If core supports multiple ports, 0..4. (0 default)
*
* @return   None
*
*/
//============================================================================
boolean usb_shared_hs_phy_rumi_init(uint32 core_num, uint32 phy_num)
{
#if USB_RUMI
// RUMI Phy Base Address for primary, sec and MP controllers
// Subject to change per RUMI release
#define RUMI_PHY_PRIM                            (USB3_PRI_USB31_PRIM_MVS_WRAPPER_BASE + 0x00184000)  // 0x0A784000
#ifdef USB_SEC_FLAG
#define RUMI_PHY_SEC                             (USB3_2ND_USB31_PRIM_MVS_WRAPPER_BASE + 0x00120000)  // 0x0A920000
#endif
      
#define HWIO_HS2_EMU_VERSION_OFFS                (0x00000000)
#define HWIO_HS2_LOCAL_RESET_REG_OFFS            (0x00000004)
#define HWIO_HS2_CLK_STATUS_OFFS                 (0x00000010)
#define HWIO_HS2_CLK_STATUS_SEL_OFFS             (0x00000014)
#define HWIO_HS2_IMEM_DELAY_CTRL_OFFS            (0x00000100)
#define HWIO_HS2_IMEM_DELAY_MIN_DELAY_OFFS       (0x00000104)
#define HWIO_HS2_USB_CLK_CTRL_OFFS               (0x00000020)
#define HWIO_HS2_USB_CLK_STATUS_OFFS             (0x00000024)
#define HWIO_HS2_QRBTC_CONTROL_OFFS              (0x00000028)
#define HWIO_HS2_QRBTC_CONTROL_OE_OFFS           (0x0000002c)
#define HWIO_HS2_USB30_CTRL_OFFS                 (0x00000034)
#define HWIO_HS2_USB30_STATUS_OFFS               (0x00000038)
#define HWIO_HS2_USB_PIPE3_CLK_CTRL_OFFS         (0x0000003c)
#define HWIO_HS2_USB30_IRQ0_DELAY_FROM_RISE_OFFS (0x00000040)
#define HWIO_HS2_USB30_IRQ1_DELAY_FROM_RISE_OFFS (0x00000044)
#define HWIO_HS2_USB30_IRQ_DELAY_CTRL_OFFS       (0x00000048)
#define HWIO_HS2_USB30_IRQ0_DELAY_FROM_FALL_OFFS (0x00000060)
#define HWIO_HS2_USB30_IRQ1_DELAY_FROM_FALL_OFFS (0x00000064)
#define HWIO_HS2_SETUP_VERSION_OFFS              (0x00000050)
#define HWIO_HS2_USB_UNIPHY_CLK_CTRL_OFFS        (0x00000054)
#define HWIO_HS2_ROM_STRING_SIZE_OFFS            (0x00010004)

#define USB_RUMI_PHY_INIT_RETRY_COUNT_MAX        (5)

  uint32        phy_base         = RUMI_PHY_PRIM;
  const uint32  UTMI_MMCM_SHIFT  = 0x000001E0;
  uint32        retry_count;
  uint32        utmi_khz, utmi_mhz;
  
  // PHY number is not used since target does not support multi-port
  (void)phy_num;

  switch (core_num)
  {
    case 0:   phy_base = RUMI_PHY_PRIM;   break;
#ifdef USB_SEC_FLAG
    case 1:   phy_base = RUMI_PHY_SEC;    break;
#endif
    default:
    {
      usb_shared_uart_log_error("RUMI USB PHY invalid core", core_num);
    }
    break;
  }

  for (retry_count = 0; retry_count < USB_RUMI_PHY_INIT_RETRY_COUNT_MAX; retry_count++)
  {
    usb_shared_uart_log_error("RUMI PHY INIT:", retry_count);

    // Put everything in Reset except the PHY
    usb_shared_uart_log_error("RUMI PHY INIT", 0);
    out_dword(phy_base + HWIO_HS2_LOCAL_RESET_REG_OFFS, 0xFFF0);
    usb_shared_delay_us(500);
    out_dword(phy_base + HWIO_HS2_LOCAL_RESET_REG_OFFS, 0xFFF3);
    usb_shared_delay_us(500); 
    out_dword(phy_base + HWIO_HS2_LOCAL_RESET_REG_OFFS, 0xFFF0);

    // Shifting ULPI/UTMI clock MMCM
    out_dword(phy_base + HWIO_HS2_USB_CLK_CTRL_OFFS, 0x00100000);
    usb_shared_delay_us(500);
    out_dword(phy_base + HWIO_HS2_USB_CLK_CTRL_OFFS, 0x00000000);
    usb_shared_delay_us(500);
    out_dword(phy_base + HWIO_HS2_USB_CLK_CTRL_OFFS, UTMI_MMCM_SHIFT);
    usb_shared_delay_us(500);

    usb_shared_uart_log_error("UTMI MMCM clock shift value set", UTMI_MMCM_SHIFT);

    // Shifting PIPE3 clock MMCM - Not used since only USB2 supported on RUMI
    out_dword(phy_base + HWIO_HS2_USB_PIPE3_CLK_CTRL_OFFS, 0x00100000);
    usb_shared_delay_us(500);
    out_dword(phy_base + HWIO_HS2_USB_PIPE3_CLK_CTRL_OFFS, 0x00000000);
    usb_shared_delay_us(500);
    out_dword(phy_base + HWIO_HS2_USB_PIPE3_CLK_CTRL_OFFS, 0x00000004);
    usb_shared_delay_us(500);

    // Clear the other Resets */
    out_dword(phy_base + HWIO_HS2_LOCAL_RESET_REG_OFFS, 0x0);
    usb_shared_delay_us(500);

    // Put clock selector to read UTMI clock */
    out_dword(phy_base + HWIO_HS2_CLK_STATUS_SEL_OFFS, 0x00000009);
    usb_shared_delay_us(500);
    utmi_khz = in_dword(phy_base + HWIO_HS2_CLK_STATUS_OFFS);
    usb_shared_uart_log_error("UTMI CLK @ PAD (KHz):", utmi_khz);

    // Try until 60Mhz
    utmi_mhz = utmi_khz / 1000;
    if ((55 <= utmi_mhz) && (61>=utmi_mhz))
    {
      return TRUE;
    }
  }
  usb_shared_uart_log_error("RUMI USB PHY timeout (Mhz):", utmi_mhz);
#else  // USB_RUMI
  usb_shared_uart_log_error("rumi_phy_disabled", 0);
#endif // USB_RUMI
  return FALSE;
}

//============================================================================

/**
* @function USB_SHARED_SS_PHY_INIT
*
* @brief    API used to initialize the Super Speed Primary PHY 
*
*/
//============================================================================
boolean usb_shared_ss_phy_init(uint32 usb_ss_phy_lane)
{
  uint32 qusb_timeout=0x0;
  boolean       retimer_result = FALSE;
  USB_DTB_STATUS_TYPE dtb_status =USB_DTB_STATUS_SUCCESS;

  usb_shared_error_log(QUSB_SS_PHY_INIT_LOG, 0, 0);
  usb_shared_uart_log_info("usb_shared_ss_phy_init: ++");
#ifdef USB_WAIPIO_INIT_COMPILE
  // If USB SS PHY is disabled on the fuse, then return FALSE, so caller can fallback to USB2 PHY only mode
  if (HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_INM(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_USB_SS_DISABLE_BMSK))
  {
    usb_shared_uart_log_error("usb3_ss_phy_disabled", 0);
    return FALSE;
  }
#endif
  // TODO: Setting to USB3DP has not side effect. This setting will help HLOS to test USB3DP 
  // if HLOS Retimer driver is not ready
  retimer_result = usb_shared_retimer_init(USB_RETIMER_CORE_0, USB4_MODE_TYPE_USB3DP, usb_ss_phy_lane);
  if (retimer_result)
  {
    usb_ss_phy_lane = QUSB_TYPE_C_LANE_A;
  }

  // Override Type-C lane detection  override
  HWIO_USB3_DP_PHY_USB3_DP_COM_TYPEC_CTRL_OUTM(
    HWIO_USB3_DP_PHY_USB3_DP_COM_TYPEC_CTRL_SW_PORTSELECT_BMSK, 
    usb_ss_phy_lane << HWIO_USB3_DP_PHY_USB3_DP_COM_TYPEC_CTRL_SW_PORTSELECT_SHFT);
  
  HWIO_USB3_DP_PHY_USB3_DP_COM_TYPEC_CTRL_OUTM(
    HWIO_USB3_DP_PHY_USB3_DP_COM_TYPEC_CTRL_SW_PORTSELECT_MUX_BMSK,
    0x1 << HWIO_USB3_DP_PHY_USB3_DP_COM_TYPEC_CTRL_SW_PORTSELECT_MUX_SHFT);

  //init Device Tree Binary acess for PHY settings and program PHY registers
  dtb_status = usb_shared_xbl_dtb_node_init("/soc/usb0/ss_phy_cfg");
  if(USB_DTB_STATUS_SUCCESS != dtb_status)
  {
    usb_shared_error_log(DCI_DAL_ERROR_LOG, 0, __LINE__);
    usb_shared_uart_log_error("SS: usb_shared_xbl_dtb_node_init device tree Not available", dtb_status);
    return FALSE;
  }

  usb_shared_delay_us(100);

  HWIO_USB3_DP_PHY_USB3_DP_COM_SW_RESET_OUT(0x00);
  HWIO_USB3_DP_PHY_USB3_PCS_SW_RESET_OUT(0x0);
  HWIO_USB3_DP_PHY_USB3_PCS_START_CONTROL_OUT(0x3);

  usb_shared_delay_us(100);

  /* Poll PHYSTATUS field of Register USB3_PHY_PCS_STATUS to Go LOW after reset*/
  while(HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS1_INM(
        HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS1_PHYSTATUS_BMSK))
  {
    usb_shared_delay_us(100);
    if (qusb_timeout++ > 100)
    {
        USB_SHARED_ASSERT(DCI_SS_PHY_RESET_ERROR_LOG);
        usb_shared_uart_log_error("ssusb_phy_init_timeout", 0);
        return FALSE;
    }
  }

  if (usb_ss_phy_lane == 0)
  {
    usb_shared_uart_log_error("ssusb_phy_init_success lane", usb_ss_phy_lane);
  }
  else
  {
    usb_shared_uart_log_error("ssusb_phy_init_success lane", usb_ss_phy_lane);
  }
  usb_shared_uart_log_info("usb_shared_ss_phy_init: --");
  return TRUE;
}

//============================================================================

/**
* @function USB_SHARED_SS_PHY_INIT_SEC
*
* @brief    API used to initialize the Super Speed Secondary PHY 
*
*/
//============================================================================
#ifdef USB_SEC_FLAG
boolean usb_shared_ss_phy_init_sec()
{

  uint32 qusb_timeout=0x0;

  usb_shared_error_log(QUSB_SS_PHY_INIT_LOG, 0, 0);
  usb_shared_uart_log_info("usb_shared_ss_phy_init_sec: ++");

  usb_shared_lib_process_phy_reg_array(
    (const qusb_phy_cfg_type*) qusb_dci_ss_phy_sec_cfg_common,
    0,
    QUSB_DCI_SS_PHY_SEC_COMMON_CFG_ARRAY_ENTRY_CNT);

  usb_shared_delay_us(100);

  HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_SW_RESET_OUT(0x0);
  HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_START_CONTROL_OUT(0x3);

  usb_shared_delay_us(100);

  /* Poll PHYSTATUS field of Register USB3_PHY_PCS_STATUS to Go LOW after reset*/
  while(HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_PCS_STATUS1_INM(
        HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_PCS_STATUS1_PHYSTATUS_BMSK))
  {
    usb_shared_delay_us(100);
    if (qusb_timeout++ > 100)
    {
        USB_SHARED_ASSERT(DCI_SS_PHY_RESET_ERROR_LOG);
        usb_shared_uart_log_error("p2_ssusb_phy_init_timeout", 0);
        return FALSE;
    }
  }
  
  usb_shared_uart_log_error("usb_shared_ss_phy_init_sec: ss phy cfg size", QUSB_DCI_SS_PHY_SEC_COMMON_CFG_ARRAY_ENTRY_CNT);

  usb_shared_uart_log_info("usb_shared_ss_phy_init_sec: --");
  return TRUE;
}
#endif

#ifdef USB_MP_FLAG

//============================================================================

/**
* @function USB_SHARED_HS_PHY_INIT_MP0
*
* @brief    API used to initialize the High Speed MultiPort0 PHY 
*
*/
//============================================================================
boolean usb_shared_hs_phy_init_MP0(void)
{
  const char   *port_name     = "QUSB_PORT_MP0";  
  uint32        rcal_fuse     = 0;
  uint32        phy_write_cnt = 0;

  usb_shared_uart_log_info("usb_shared_hs_phy_init_MP0: ++");

  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  // >> USB_PHY_CFG0[1] = 1; UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_CFG0_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);
  
  // Set the POR signal = 1 ; active high 
  // >> USB_PHY_UTMI_CTRL5[1] = 1 ; POR 
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL5_POR_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL5_POR_SHFT);
  
  // Set all strapping options:
  // >> Select reference clock frequency. FSEL[6:4] = 000; for 19.2MHz clock 
  //    USB_PHY_HS_PHY_CTRL_COMMON0[6:4] = 000; FSEL (Note: This control with register is not needed for default settings) 
  //    usb2phy_fsel[2:0]= 000, At the chip top, the usb2phy_fsel I/O need be tied off to 000 for default settings. 
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_SHFT);

  // Selects the PLL bandwidth, PLLBTUNE=1
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON1_PLLBTUNE_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON1_PLLBTUNE_SHFT);
  
  // >> Select reference clock source. REFCLKSEL[1:0] = 10; select the CLKCORE input 
  //    USB_PHY_REFCLK_CTRL[1:0] = 10; REFCLK_SEL 
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_REFCLK_CTRL_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_REFCLK_CTRL_REFCLK_SEL_BMSK, 0x2 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_REFCLK_CTRL_REFCLK_SEL_SHFT);
  
  // Select external VBUS valid by setting VBUSVLDEXTSEL0 to 1
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_SHFT);

  // VBUSVLDEXT0 is set to 1. This make VBUS signal valid.  Note, the VBUS and ID are not used in the femtoPHY.  
  // They are used in PMI and information needs to transferred from PMI to AOSS via the SPMI interface
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL1_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_SHFT);

  // Set Parameter Override (if needed) - even if override didn't work, USB2PHY sould work
  phy_write_cnt = usb_shared_usb2phy_array_exec(port_name);
  if (0 == phy_write_cnt)
  {
    usb_shared_uart_log_error("usb2phy: SEC 0 phy write error", 0);
    usb_shared_report_generic_error(__LINE__);
    // Continue even if PHY could not be tuned.
  }

  rcal_fuse = HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_INM(HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY___FUSE_RCAL_CODE_BMSK) >> HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY___FUSE_RCAL_CODE_SHFT;
  usb_shared_uart_log_error("mp0_hsusb_phy_init_rcal_fuse", rcal_fuse);

  // Set VREGBYPASS = 1; The internal VREG18 is not used and bypassed. It requires VDDH= 1.8V power supply from outside 
  // >> USB_PHY_HS_PHY_CTRL_COMMON2[0] = 1; VREGBYPASS 
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON2_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON2_VREGBYPASS_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON2_VREGBYPASS_SHFT);

  // Set ATERESET = 0 or tie ATERESET with POR: PHYCLOCK is available after atereset is deasserted
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL5_ATERESET_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL5_ATERESET_SHFT);
  
  // Set TESTDATAOUTSEL to 0
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_SHFT);
  
  // Set TESTCLK = 0
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_SHFT);

  // Set VATESTENB = 00
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_SHFT);

  // Set TESTDATAIN bits to zero until PHYCLOCK is available  
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_TEST0_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_TEST0_TESTDATAIN_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_TEST0_TESTDATAIN_SHFT);
  
  // This sets USB2_SUSPEND_N_SEL = 1.  Set suspendm = 1; until PHYCLOCK is available by setting USB2_SUSPEND_N_SEL and USB2_SUSPEND_N  
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);

  // Set USB2_SUSPEND_N = 1
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SHFT);
  
  // Set sleepm = 1; until PHY CLOCK is available
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL0_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL0_SLEEPM_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL0_SLEEPM_SHFT);

  // SIDDQ is set to 0. the analog block are powered up.
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_SHFT);

  // Set POR = 0; release the POR from high to low
  // >> USB_PHY_UTMI_CTRL5[1] = 0; POR 
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL5_POR_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_UTMI_CTRL5_POR_SHFT);

  // This sets USB2_SUSPEND_N_SEL = 0.  This de-selects from sw override   
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);

  usb_shared_delay_us(20);

  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  // >> USB_PHY_CFG0[1] = 0; UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_CFG0_OUTM(HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_1_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);

  usb_shared_delay_us(20);

  usb_shared_uart_log_error("usb2phy: MP0 success", phy_write_cnt);

  return TRUE;
}

/**
* @function USB_SHARED_HS_PHY_INIT_MP1
*
* @brief    API used to initialize the High Speed MultiPort1 PHY 
*
*/
//============================================================================
boolean usb_shared_hs_phy_init_MP1()
{
  const char   *port_name     = "QUSB_PORT_MP1";
  uint32        phy_write_cnt = 0;

  usb_shared_uart_log_info("usb_shared_hs_phy_init_MP1: ++");
  
  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  // >> USB_PHY_CFG0[1] = 1; UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_CFG0_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);
  

  // Set the POR signal = 1 ; active high 
  // >> USB_PHY_UTMI_CTRL5[1] = 1 ; POR 
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL5_POR_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL5_POR_SHFT);
  
  // Set all strapping options:
  // >> Select reference clock frequency. FSEL[6:4] = 000; for 19.2MHz clock 
  //    USB_PHY_HS_PHY_CTRL_COMMON0[6:4] = 000; FSEL (Note: This control with register is not needed for default settings) 
  //    usb2phy_fsel[2:0]= 000, At the chip top, the usb2phy_fsel I/O need be tied off to 000 for default settings. 
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_SHFT);

  // Selects the PLL bandwidth, PLLBTUNE=1
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON1_PLLBTUNE_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON1_PLLBTUNE_SHFT);
  
  // >> Select reference clock source. REFCLKSEL[1:0] = 10; select the CLKCORE input 
  //    USB_PHY_REFCLK_CTRL[1:0] = 10; REFCLK_SEL 
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_REFCLK_CTRL_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_REFCLK_CTRL_REFCLK_SEL_BMSK, 0x2 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_REFCLK_CTRL_REFCLK_SEL_SHFT);
  
  // Select external VBUS valid by setting VBUSVLDEXTSEL0 to 1
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_SHFT);

  // VBUSVLDEXT0 is set to 1. This make VBUS signal valid.  Note, the VBUS and ID are not used in the femtoPHY.  
  // They are used in PMI and information needs to transferred from PMI to AOSS via the SPMI interface
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL1_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_SHFT);

  // Set Parameter Override (if needed) - even if override didn't work, USB2PHY sould work
  phy_write_cnt = usb_shared_usb2phy_array_exec(port_name);
  if (0 == phy_write_cnt)
  {
    usb_shared_uart_log_error("usb2phy: MP1 0 phy write error", 0);
    // Continue even if PHY could not be tuned.
  }

  // Set VREGBYPASS = 1; The internal VREG18 is not used and bypassed. It requires VDDH= 1.8V power supply from outside 
  // >> USB_PHY_HS_PHY_CTRL_COMMON2[0] = 1; VREGBYPASS 
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON2_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON2_VREGBYPASS_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON2_VREGBYPASS_SHFT);

  // Set ATERESET = 0 or tie ATERESET with POR: PHYCLOCK is available after atereset is deasserted
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL5_ATERESET_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL5_ATERESET_SHFT);
  
  // Set TESTDATAOUTSEL to 0
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_SHFT);
  
  // Set TESTCLK = 0
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_SHFT);

  // Set VATESTENB = 00
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_SHFT);

  // Set TESTDATAIN bits to zero until PHYCLOCK is available  
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_TEST0_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_TEST0_TESTDATAIN_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_TEST0_TESTDATAIN_SHFT);
  
  // This sets USB2_SUSPEND_N_SEL = 1.  Set suspendm = 1; until PHYCLOCK is available by setting USB2_SUSPEND_N_SEL and USB2_SUSPEND_N  
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);

  // Set USB2_SUSPEND_N = 1
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SHFT);
  
  // Set sleepm = 1; until PHY CLOCK is available
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL0_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL0_SLEEPM_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL0_SLEEPM_SHFT);
  
  // SIDDQ is set to 0. the analog block are powered up.
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_SHFT);

  // Set POR = 0; release the POR from high to low
  // >> USB_PHY_UTMI_CTRL5[1] = 0; POR 
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL5_POR_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_UTMI_CTRL5_POR_SHFT);

  // This sets USB2_SUSPEND_N_SEL = 0.  This de-selects from sw override   
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);

  usb_shared_delay_us(20);

  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  // >> USB_PHY_CFG0[1] = 0; UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_CFG0_OUTM(HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_2_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);

  usb_shared_delay_us(20);

  usb_shared_uart_log_error("usb2phy: MP1 success", phy_write_cnt);

  return TRUE;
}


//============================================================================

/**
* @function USB_SHARED_HS_PHY_INIT_MP2
*
* @brief    API used to initialize the High Speed MultiPort0 PHY 
*
*/
//============================================================================
boolean usb_shared_hs_phy_init_MP2()
{
  const char   *port_name     = "QUSB_PORT_MP2";
  uint32        phy_write_cnt = 0;

  usb_shared_uart_log_info("usb_shared_hs_phy_init_MP2: ++");

  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  // >> USB_PHY_CFG0[1] = 1; UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_CFG0_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);
  
  // Set the POR signal = 1 ; active high 
  // >> USB_PHY_UTMI_CTRL5[1] = 1 ; POR 
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL5_POR_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL5_POR_SHFT);
  
  // Set all strapping options:
  // >> Select reference clock frequency. FSEL[6:4] = 000; for 19.2MHz clock 
  //    USB_PHY_HS_PHY_CTRL_COMMON0[6:4] = 000; FSEL (Note: This control with register is not needed for default settings) 
  //    usb2phy_fsel[2:0]= 000, At the chip top, the usb2phy_fsel I/O need be tied off to 000 for default settings. 
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_SHFT);

  // Selects the PLL bandwidth, PLLBTUNE=1
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON1_PLLBTUNE_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON1_PLLBTUNE_SHFT);
  
  // >> Select reference clock source. REFCLKSEL[1:0] = 10; select the CLKCORE input 
  //    USB_PHY_REFCLK_CTRL[1:0] = 10; REFCLK_SEL 
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_REFCLK_CTRL_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_REFCLK_CTRL_REFCLK_SEL_BMSK, 0x2 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_REFCLK_CTRL_REFCLK_SEL_SHFT);
  
  // Select external VBUS valid by setting VBUSVLDEXTSEL0 to 1
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_SHFT);

  // VBUSVLDEXT0 is set to 1. This make VBUS signal valid.  Note, the VBUS and ID are not used in the femtoPHY.  
  // They are used in PMI and information needs to transferred from PMI to AOSS via the SPMI interface
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL1_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_SHFT);

  // Set Parameter Override (if needed) - even if override didn't work, USB2PHY sould work
  phy_write_cnt = usb_shared_usb2phy_array_exec(port_name);
  if (0 == phy_write_cnt)
  {
    usb_shared_uart_log_warn("usb2phy: MP2 0 phy write error", 0);
    usb_shared_report_generic_error(__LINE__);
    // Continue even if PHY could not be tuned.
  }

  // Set VREGBYPASS = 1; The internal VREG18 is not used and bypassed. It requires VDDH= 1.8V power supply from outside 
  // >> USB_PHY_HS_PHY_CTRL_COMMON2[0] = 1; VREGBYPASS 
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON2_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON2_VREGBYPASS_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON2_VREGBYPASS_SHFT);

  // Set ATERESET = 0 or tie ATERESET with POR: PHYCLOCK is available after atereset is deasserted
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL5_ATERESET_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL5_ATERESET_SHFT);
  
  // Set TESTDATAOUTSEL to 0
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_SHFT);
  
  // Set TESTCLK = 0
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_SHFT);

  // Set VATESTENB = 00
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_SHFT);

  // Set TESTDATAIN bits to zero until PHYCLOCK is available  
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_TEST0_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_TEST0_TESTDATAIN_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_TEST0_TESTDATAIN_SHFT);
  
  // This sets USB2_SUSPEND_N_SEL = 1.  Set suspendm = 1; until PHYCLOCK is available by setting USB2_SUSPEND_N_SEL and USB2_SUSPEND_N  
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);

  // Set USB2_SUSPEND_N = 1
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SHFT);
  
  // Set sleepm = 1; until PHY CLOCK is available
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL0_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL0_SLEEPM_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL0_SLEEPM_SHFT);

  // SIDDQ is set to 0. the analog block are powered up.
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_SHFT);

  // Set POR = 0; release the POR from high to low
  // >> USB_PHY_UTMI_CTRL5[1] = 0; POR 
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL5_POR_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_UTMI_CTRL5_POR_SHFT);

  // This sets USB2_SUSPEND_N_SEL = 0.  This de-selects from sw override   
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);

  usb_shared_delay_us(20);

  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  // >> USB_PHY_CFG0[1] = 0; UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_CFG0_OUTM(HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_3_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);

  usb_shared_delay_us(20);

  usb_shared_uart_log_error("usb2phy: MP2 success", phy_write_cnt);

  return TRUE;
}

/**
* @function USB_SHARED_HS_PHY_INIT_MP1
*
* @brief    API used to initialize the High Speed MultiPort1 PHY 
*
*/
//============================================================================
boolean usb_shared_hs_phy_init_MP3()
{
  const char   *port_name     = "QUSB_PORT_MP3";
  uint32        phy_write_cnt = 0;

  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  // >> USB_PHY_CFG0[1] = 1; UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_CFG0_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);
 

  // Set the POR signal = 1 ; active high 
  // >> USB_PHY_UTMI_CTRL5[1] = 1 ; POR 
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL5_POR_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL5_POR_SHFT);
  
  // Set all strapping options:
  // >> Select reference clock frequency. FSEL[6:4] = 000; for 19.2MHz clock 
  //    USB_PHY_HS_PHY_CTRL_COMMON0[6:4] = 000; FSEL (Note: This control with register is not needed for default settings) 
  //    usb2phy_fsel[2:0]= 000, At the chip top, the usb2phy_fsel I/O need be tied off to 000 for default settings. 
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_SHFT);

  // Selects the PLL bandwidth, PLLBTUNE=1
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON1_PLLBTUNE_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON1_PLLBTUNE_SHFT);
  
  // >> Select reference clock source. REFCLKSEL[1:0] = 10; select the CLKCORE input 
  //    USB_PHY_REFCLK_CTRL[1:0] = 10; REFCLK_SEL 
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_REFCLK_CTRL_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_REFCLK_CTRL_REFCLK_SEL_BMSK, 0x2 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_REFCLK_CTRL_REFCLK_SEL_SHFT);
  
  // Select external VBUS valid by setting VBUSVLDEXTSEL0 to 1
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_SHFT);

  // VBUSVLDEXT0 is set to 1. This make VBUS signal valid.  Note, the VBUS and ID are not used in the femtoPHY.  
  // They are used in PMI and information needs to transferred from PMI to AOSS via the SPMI interface
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL1_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_SHFT);
  
  // Set Parameter Override (if needed) - even if override didn't work, USB2PHY sould work
  phy_write_cnt = usb_shared_usb2phy_array_exec(port_name);
  if (0 == phy_write_cnt)
  {
    usb_shared_uart_log_warn("usb2phy: MP3 0 phy write error", 0);    
    usb_shared_report_generic_error(__LINE__);
    // Continue even if PHY could not be tuned.
  }

  // Set VREGBYPASS = 1; The internal VREG18 is not used and bypassed. It requires VDDH= 1.8V power supply from outside 
  // >> USB_PHY_HS_PHY_CTRL_COMMON2[0] = 1; VREGBYPASS 
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON2_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON2_VREGBYPASS_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON2_VREGBYPASS_SHFT);

  // Set ATERESET = 0 or tie ATERESET with POR: PHYCLOCK is available after atereset is deasserted
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL5_ATERESET_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL5_ATERESET_SHFT);
  
  // Set TESTDATAOUTSEL to 0
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_SHFT);
  
  // Set TESTCLK = 0
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_SHFT);

  // Set VATESTENB = 00
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_SHFT);

  // Set TESTDATAIN bits to zero until PHYCLOCK is available  
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_TEST0_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_TEST0_TESTDATAIN_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_TEST0_TESTDATAIN_SHFT);
  
  // This sets USB2_SUSPEND_N_SEL = 1.  Set suspendm = 1; until PHYCLOCK is available by setting USB2_SUSPEND_N_SEL and USB2_SUSPEND_N  
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);

  // Set USB2_SUSPEND_N = 1
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SHFT);
  
  // Set sleepm = 1; until PHY CLOCK is available
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL0_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL0_SLEEPM_BMSK, 0x1 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL0_SLEEPM_SHFT);

  // SIDDQ is set to 0. the analog block are powered up.
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_SHFT);

  // Set POR = 0; release the POR from high to low
  // >> USB_PHY_UTMI_CTRL5[1] = 0; POR 
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL5_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL5_POR_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_UTMI_CTRL5_POR_SHFT);

  // This sets USB2_SUSPEND_N_SEL = 0.  This de-selects from sw override   
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);

  usb_shared_delay_us(20);

  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  // >> USB_PHY_CFG0[1] = 0; UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_CFG0_OUTM(HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 0x0 << HWIO_AHB2PHY_0USB2PHY_4_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);

  usb_shared_delay_us(20);

  usb_shared_uart_log_error("usb2phy: MP3 success", phy_write_cnt);

  return TRUE;
}




/**
* @function USB_SHARED_SS_PHY_INIT_MP0
*
* @brief    API used to initialize the Super Speed MultiPort 0 PHY 
*
*/
//============================================================================

boolean usb_shared_ss_phy_init_MP0()
{
  const char   *port_name     = "QUSB_PORT_MP0";
  uint32        qusb_timeout  = 0;
  uint32        phy_write_cnt = 0;

  usb_shared_error_log(QUSB_SS_PHY_INIT_LOG, 0, 0);
  usb_shared_uart_log_info("usb_shared_ss_phy_init_MP0: ++");

  phy_write_cnt = usb_shared_usb3phy_array_exec(port_name);
  if (0 == phy_write_cnt)
  {
    usb_shared_uart_log_warn("usb3phy: MP0 0 phy write error", 0);
    usb_shared_report_generic_error(__LINE__);
    return FALSE;
  }

  usb_shared_delay_us(100);
  
  HWIO_AHB2PHY_0USB3_DP_PHY_0QSERDES_COM_SW_RESET_OUT(0x00);
  HWIO_AHB2PHY_0USB3_DP_PHY_0PCIE_USB3_UNI_PCS_SW_RESET_OUT(0x0);
  HWIO_AHB2PHY_0USB3_DP_PHY_0PCIE_USB3_UNI_PCS_START_CONTROL_OUT(0x3);

  usb_shared_delay_us(100);

  /* Poll PHYSTATUS field of Register USB3_PHY_PCS_STATUS to Go LOW after reset*/
  while(HWIO_AHB2PHY_0USB3_DP_PHY_0PCIE_USB3_UNI_PCS_PCS_STATUS1_INM(
        HWIO_AHB2PHY_0USB3_DP_PHY_0PCIE_USB3_UNI_PCS_PCS_STATUS1_PHYSTATUS_BMSK))
    {
    usb_shared_delay_us(100);
    if (qusb_timeout++ > 100)
      {
        USB_SHARED_ASSERT(DCI_SS_PHY_RESET_ERROR_LOG);
        usb_shared_uart_log_error("usb3phy: MP0 fail", 0);
        return FALSE;
    }
  }

  usb_shared_uart_log_error("usb3phy: MP0 success", phy_write_cnt);
  
  usb_shared_uart_log_info("usb_shared_ss_phy_init_MP0: --");
  return TRUE;
}

/**
* @function USB_SHARED_SS_PHY_INIT_MP1
*
* @brief    API used to initialize the Super Speed MultiPort 1 PHY 
*
*/
//============================================================================

boolean usb_shared_ss_phy_init_MP1()
{
  const char   *port_name     = "QUSB_PORT_MP1";
  uint32        qusb_timeout  = 0;
  uint32        phy_write_cnt = 0;

  usb_shared_error_log(QUSB_SS_PHY_INIT_LOG, 0, 0);
  usb_shared_uart_log_info("usb_shared_ss_phy_init_MP1: ++");

  phy_write_cnt = usb_shared_usb3phy_array_exec(port_name);
  if (0 == phy_write_cnt)
  {
    usb_shared_uart_log_warn("usb3phy: MP0 0 phy write error", 0);
    usb_shared_report_generic_error(__LINE__);
    return FALSE;
    }

  usb_shared_delay_us(100);
    
  HWIO_AHB2PHY_0USB3_DP_PHY_1QSERDES_COM_SW_RESET_OUT(0x00);
  HWIO_AHB2PHY_0USB3_DP_PHY_1PCIE_USB3_UNI_PCS_SW_RESET_OUT(0x0);
  HWIO_AHB2PHY_0USB3_DP_PHY_1PCIE_USB3_UNI_PCS_START_CONTROL_OUT(0x3);

  usb_shared_delay_us(100);

  /* Poll PHYSTATUS field of Register USB3_PHY_PCS_STATUS to Go LOW after reset*/
  while(HWIO_AHB2PHY_0USB3_DP_PHY_1PCIE_USB3_UNI_PCS_PCS_STATUS1_INM(
        HWIO_AHB2PHY_0USB3_DP_PHY_1PCIE_USB3_UNI_PCS_PCS_STATUS1_PHYSTATUS_BMSK))
  {
    usb_shared_delay_us(100);
    if (qusb_timeout++ > 100)
    {
        USB_SHARED_ASSERT(DCI_SS_PHY_RESET_ERROR_LOG);
        usb_shared_uart_log_error("usb3phy: MP1 timout", 0);
        return FALSE;
    }
  }

  usb_shared_uart_log_error("usb3phy: MP1 success", phy_write_cnt);

  usb_shared_uart_log_info("usb_shared_ss_phy_init_MP1: --");
  return TRUE;
}

#endif

//============================================================================
/**
* @function usb_shared_poll_ss_phy_training
*
* @brief    Polls USB SS PHY for training
*
*/
//============================================================================
void usb_shared_poll_ss_phy_training(void)
{
#ifdef USB_RETRAINING
  uint32 loop_count = USB_SHARED_POLL_SS_PHY_TRAINING_TIMEOUT_US;
  
  // Add Gen2 USB enumeration on some type_c USB combo Super Speed Plus compatibilty
  if (HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS2_INM(
    HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS2_RX_EQUALIZATION_IN_PROGRESS_BMSK))
  {
    usb_shared_uart_log_error("usb3_rx_training_in_progress", 0);

    for (; loop_count; loop_count--)
    {
      if (0 == HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS2_INM(
        HWIO_USB3_DP_PHY_USB3_PCS_PCS_STATUS2_RX_EQUALIZATION_IN_PROGRESS_BMSK))
      {
        HWIO_USB3_DP_PHY_USB3_PCS_INSIG_SW_CTRL3_OUT(0x08);
        HWIO_USB3_DP_PHY_USB3_PCS_INSIG_MX_CTRL3_OUT(0x08);

        // Wait 1us
        usb_shared_delay_us(1);

        HWIO_USB3_DP_PHY_USB3_PCS_INSIG_SW_CTRL3_OUT(0x00);
        HWIO_USB3_DP_PHY_USB3_PCS_INSIG_MX_CTRL3_OUT(0x00);

        usb_shared_uart_log_error("usb3_rx_training_done_in_us", USB_SHARED_POLL_SS_PHY_TRAINING_TIMEOUT_US - loop_count);
        break;
      }
      usb_shared_delay_us(1);
    }
    
    if (0 == loop_count)
    {
      usb_shared_uart_log_error("usb3_rx_training_timeout", USB_SHARED_POLL_SS_PHY_TRAINING_TIMEOUT_US);
    }
  }
#endif
}

//============================================================================
/**
* @function usb_shared_poll_ss_phy_training_sec
*
* @brief    Polls USB SS PHY for training
*
*/
//============================================================================
#ifdef USB_SEC_FLAG
void usb_shared_poll_ss_phy_training_sec(void)
{
#ifdef USB_RETRAINING
  uint32 loop_count = USB_SHARED_POLL_SS_PHY_TRAINING_TIMEOUT_US;
  
  // Add Gen2 USB enumeration workaround on thunderbolt v2 type_c USB combo
  if (HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_PCS_STATUS2_INM(
    HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_PCS_STATUS2_RX_EQUALIZATION_IN_PROGRESS_BMSK))
  {
    usb_shared_uart_log_error("usb3_2nd_rx_training_in_progress", 0);

    for (; loop_count; loop_count--)
    {
      if (0 == HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_PCS_STATUS2_INM(
        HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_PCS_STATUS2_RX_EQUALIZATION_IN_PROGRESS_BMSK))
      {
        HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_INSIG_SW_CTRL3_OUT(0x08);
        HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_INSIG_MX_CTRL3_OUT(0x08);

        // Wait 1us
        usb_shared_delay_us(1);

        HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_INSIG_SW_CTRL3_OUT(0x00);
        HWIO_USB3_UNI_PHY_PCIE_USB3_UNI_PCS_INSIG_MX_CTRL3_OUT(0x00);

        usb_shared_uart_log_error("usb3_2nd_rx_training_done_in_us", USB_SHARED_POLL_SS_PHY_TRAINING_TIMEOUT_US - loop_count);
        break;
      }
      usb_shared_delay_us(1);
    }
    
    if (0 == loop_count)
    {
      usb_shared_uart_log_error("usb3_2nd_rx_training_timeout", USB_SHARED_POLL_SS_PHY_TRAINING_TIMEOUT_US);
    }
  }
#endif
}
#endif

//============================================================================
/**
* @function  usb_shared_get_chip_serial_number
*
* @brief Call API to uint32 unique MSM serial string
*
* @Note : None
*
* @param  None 
*
* @return uint32: Chip serial number
*
*/
//============================================================================
uint32 usb_shared_get_chip_serial_number(void)
{
  uint32 serial_num = HWIO_CHIP_UNIQUE_ID_0_INM(HWIO_CHIP_UNIQUE_ID_0_SERIAL_NUM_BMSK) >> HWIO_CHIP_UNIQUE_ID_0_SERIAL_NUM_SHFT;
  //usb_shared_uart_log_error("usb_shared_get_chip_serial_number", serial_num);
  return serial_num;
}


//============================================================================
/**
* @function  usb_shared_get_chip_id
*
* @brief Call API to uint32 unique chip id
*
* @Note : None
*
* @param  None 
*
* @return uint32: Chip id number
*
*/
//============================================================================
uint32 usb_shared_get_chip_id(void)
{
  uint32 chip_id = HWIO_CHIP_UNIQUE_ID_1_INM(HWIO_CHIP_UNIQUE_ID_1_CHIP_ID_BMSK) >> HWIO_CHIP_UNIQUE_ID_1_CHIP_ID_SHFT;
  //usb_shared_uart_log_error("usb_shared_get_chip_id", chip_id );
  return chip_id;
}

//============================================================================
/** 
 * API is used to add chip serial number to the string and return 
 * Product String Descriptor
 * 
 * @param pointer to product string
 *              Pointer to the buffer to be updated with Product string desc
 *              Length of the buffer
 *
 * @return Appended string length
 */ 
 //============================================================================
uint32 usb_shared_get_product_str_desc_with_chip_serial(char* product_str, char* prod_str_desc, uint32 desc_len)
{
  char    chip_serial_str[QUSB_FD_PRODUCT_STRING_LENGTH_MAX];
  uint32  chip_serial;
  uint32  chip_id;
  uint32  str_desc_index;
  uint32  str_desc_size;
  uint32  chip_str_len;
  uint32  chip_str_index;

  if ((NULL == product_str)||(NULL == prod_str_desc) )
  {
    // String is NULL;
    return 0;
  }

  chip_serial = usb_shared_get_chip_serial_number();
  chip_id     = usb_shared_get_chip_id();

  chip_str_len = snprintf(chip_serial_str, sizeof(chip_serial_str), "%s_CID:%04X_SN:%08X", product_str, chip_id, chip_serial);
  //usb_shared_uart_log_error("usb_shared_get_product_str_desc_with_chip_serial", chip_str_len);  
  if (chip_str_len >= sizeof(chip_serial_str))
  {
    // Chip Seiral is too long to fit
    return 0;
  }

  // "ASCII string size" X 2 (UNICODE) 
  //   + 2 (1 byte SIZE and 1 byte STRING DESC TYPE ENUM)
  str_desc_size = (chip_str_len * 2) + 2;

  if (str_desc_size >= desc_len)
  {
    // Destination buffer over flow
    return 0;    
  }

  str_desc_index = 0;
  prod_str_desc[str_desc_index++] = (char)str_desc_size;
  prod_str_desc[str_desc_index++] = USB_DESCTYPE_STRING;

  for (chip_str_index = 0; chip_str_index < chip_str_len; chip_str_index++)
  {
    prod_str_desc[str_desc_index++] = chip_serial_str[chip_str_index];
    prod_str_desc[str_desc_index++] = 0x0;  
  }

  return str_desc_size;
}


//============================================================================
/**
* @function  usb_shared_is_eud_active
*
* @brief Returns status whether EUD is active 
*        and has already initialized High Speed PHY
*
* @Note : None
*
* @param  None 
*
* @return boolean: TRUE is EUD is active, FALSE otherwise
*
*/
//============================================================================
boolean usb_shared_is_eud_active(void)
{
#if 1 // UEFI cannot access EUD_EN2.  Skip checking until fixed by XBL_SEC
  uint32 is_eud_active = HWIO_EUD_EUD_EN2_INM(
    HWIO_EUD_EUD_EN2_EUD_EN2_BMSK) 
    >> HWIO_EUD_EUD_EN2_EUD_EN2_SHFT;

  if (is_eud_active)
  {
    usb_shared_uart_log_error("usb_eud_is_active, status ", HWIO_EUD_ENUM_STAT_REG_IN);
    return TRUE;
  }
  
  return FALSE;
#else
  return FALSE;
#endif
}

boolean usb_shared_is_run_stop_active(void)
{
  uint32 is_run_stop_active = HWIO_USB3_PRI_DCTL_INM(HWIO_USB3_PRI_DCTL_RUN_STOP_BMSK);    
  if (is_run_stop_active)
  {
    usb_shared_uart_log_error("usb run_stop status ", is_run_stop_active);
    return TRUE;
  }
  return FALSE;
}


void usb_shared_refclk_enable(boolean bEnable)
{
  uint8 value = 0;
  if (bEnable)
  {
    value =0x1;
  }
  HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_OUTM(HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_GCC_USB3_CLKREF_EN__USB3_ENABLE_BMSK,
                                            value << HWIO_TCSR_GCC_USB3_CLKREF_EN__USB3_ENABLE_GCC_USB3_CLKREF_EN__USB3_ENABLE_SHFT);
  HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_OUTM(HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_GCC_USB2_CLKREF_EN__USB2_ENABLE_BMSK,
                                            value << HWIO_TCSR_GCC_USB2_CLKREF_EN__USB2_ENABLE_GCC_USB2_CLKREF_EN__USB2_ENABLE_SHFT);

  return;
} // end usb_shared_refclk_enable




//============================================================================
/**
* @function  usb_shared_is_eud_bulk_out_ep_limit_required
*
* @brief Used to check if EP MaxPaxketSize has to be limited in Fastboot
*
* @Note : Called only in HS mode
*
* @param Endpoint Address
*		 Endpoint Attribute
*		 Endpoint MaxPacketSize
*
* @return TRUE if EUD is active and the EP is BULK type OUT EP 
*		  Otherwise FALSE
*/
//============================================================================
boolean usb_shared_is_eud_bulk_out_ep_limit_required(uint8 ep_addr, uint8 ep_attr, uint16 mps)
{
#if 0
  uint8 dir, ep_type;
  boolean is_eud_active;
  
  is_eud_active = usb_shared_is_eud_active();
  if (is_eud_active)
  {
    dir = (ep_addr >> 7); //get direction of endpoint from addr, 0 - OUT and 1 - IN
    ep_type = (ep_attr & 0x03); //get endpoint type from Endpoint attributes
	
	// Check if EP is BULK type and its direction is OUT 
    if ((dir == 0) && (ep_type == 2) && (mps == 512))
	{ 
	  usb_shared_uart_log_error("limiting EP MPS to 128", 1);
	  return TRUE;
	}
	else
	{
	  return FALSE;
	}
  
  }
  else
  {
    return FALSE;
  }
#else
  return FALSE;
#endif

}


void usb_shared_uart_log_dts_warn(USB_DTB_STATUS_TYPE error_code)
{
  usb_shared_error_log(DTB_ERROR_LOG, 0, error_code);
  usb_shared_uart_log_warn("usb_shared_xbl_dtb_node_init: ", error_code);
  return;
}


boolean usb_shared_process_phy_reg_dtb_list(const usb_dtb_phy_cfg_type* pphy_table, uint32 prop_size)
{
  uint32 index = 0;

  if(NULL== pphy_table || (prop_size % sizeof(usb_dtb_phy_cfg_type)))
  {
    usb_shared_error_log(DTB_WRONG_PARAMETER_LOG, 0, prop_size);
    usb_shared_uart_log_error("usb_shared_lib_process_phy_reg_dtb_list: Invalid paramerters received", 0);
    return FALSE;
  }

  if(usb_shared_uint32add_ovrflw(USB2PHY_CM_DWC_USB2_REG_BASE, USB2PHY_CM_DWC_USB2_REG_BASE_SIZE) ||
     usb_shared_uint32add_ovrflw(USB3_DP_PHY_CM_USB3_DP_CON_REG_BASE, USB3_DP_PHY_CM_USB3_DP_CON_REG_BASE_SIZE))
  {
    usb_shared_uart_log_dts_warn(USB_DTB_STATUS_INVALID_ADDR);
    USB_ASSERT_RETURN(0, 0);
  }

  for ( ; index < (prop_size/sizeof(usb_dtb_phy_cfg_type)); ++index)
  {
    if (QUSB_HWIO_ADDR_END == pphy_table[index].address)
    {
      break;
    }

    if (QUSB_HWIO_ADDR_EMPTY == pphy_table[index].address)
    {
      continue;
    }

    /* Allow out_dword writes only if the address falls within USB2 or USB3 PHY address space */
    if (((pphy_table[index].address >= USB2PHY_CM_DWC_USB2_REG_BASE) &&
        (pphy_table[index].address < USB2PHY_CM_DWC_USB2_REG_BASE + USB2PHY_CM_DWC_USB2_REG_BASE_SIZE)) ||
        ((pphy_table[index].address >= USB3_DP_PHY_CM_USB3_DP_CON_REG_BASE) &&
        (pphy_table[index].address < USB3_DP_PHY_CM_USB3_DP_CON_REG_BASE + USB3_DP_PHY_CM_USB3_DP_CON_REG_BASE_SIZE)))
    {
      out_dword(pphy_table[index].address, pphy_table[index].value);
    }
    else
    {
      usb_shared_uart_log_dts_warn(USB_DTB_STATUS_INVALID_ADDR);
    }

  }
  usb_shared_error_log(QUSB_DCI_PHY_REG_ARRAY_PROCESS____END_LOG, 0, index);
  
  return TRUE;
}


USB_DTB_STATUS_TYPE usb_shared_xbl_dtb_node_init(char *pdtb_node_name)
{
  void *fdtblob_h;
  int32 rt_val= -1;
  FdtNodeHandle fdtnode_h;
  usb_dtb_phy_cfg_type *pdtbphy_table = NULL;
  uint32 phy_cfg_size=0;

  if(NULL == pdtb_node_name )
  {
    usb_shared_uart_log_dts_warn(USB_DTB_STATUS_WRONG_NAME);
    return USB_DTB_STATUS_WRONG_NAME;
  }
  
  rt_val = fdt_get_blob_handle(&fdtblob_h, DEFAULT_BLOB_ID);
  if(rt_val || NULL == fdtblob_h)
  {
    usb_shared_uart_log_dts_warn(USB_DTB_STATUS_FAILED_GET_BLOB);
    return USB_DTB_STATUS_FAILED_GET_BLOB;

  }
  
  rt_val = fdt_get_node_handle(&fdtnode_h, fdtblob_h, pdtb_node_name);
  if(rt_val)
  {
    usb_shared_uart_log_dts_warn(USB_DTB_STATUS_FAILED_GET_NODE);
    return USB_DTB_STATUS_FAILED_GET_NODE;

  }

  rt_val = fdt_get_prop_size(&fdtnode_h, "table", &phy_cfg_size);
  if(rt_val)
  {
    usb_shared_uart_log_dts_warn(USB_DTB_STATUS_FAILED_GET_PROP_SIZE);
    return USB_DTB_STATUS_FAILED_GET_PROP_SIZE;
  }
  else 
  {
    usb_shared_error_log(DCI_DAL_ERROR_LOG, 0, __LINE__);
    usb_shared_uart_log_warn("usb_shared_xbl_dtb_node_init: fdt_get_prop_size SUCCESS", phy_cfg_size);
  }

  if(DAL_SUCCESS != DALSYS_Malloc(phy_cfg_size, (void**)&pdtbphy_table) )
  {
    usb_shared_uart_log_dts_warn(USB_DTB_STATUS_FAILED_ALLOC);
    return USB_DTB_STATUS_FAILED_ALLOC;
  }

  rt_val = fdt_get_uint32_prop_list(&fdtnode_h, "table", (uint32*)pdtbphy_table, phy_cfg_size);
  if(rt_val)
  {
    usb_shared_uart_log_dts_warn(USB_DTB_STATUS_FAILED_GET_PROP_LIST);
    return USB_DTB_STATUS_FAILED_GET_PROP_LIST;
  }

  //Program PHY registers 
   if(!usb_shared_process_phy_reg_dtb_list(pdtbphy_table, phy_cfg_size))
  {
    usb_shared_uart_log_dts_warn(USB_DTB_STATUS_FAILED_PROCESS_LIST);
    return USB_DTB_STATUS_FAILED_PROCESS_LIST;
  }

  if(DAL_SUCCESS != DALSYS_Free((void*)pdtbphy_table))
  {
    usb_shared_uart_log_dts_warn(USB_DTB_STATUS_FAILED_FREE);
    return USB_DTB_STATUS_FAILED_FREE;
  }
  return USB_DTB_STATUS_SUCCESS;
}

// ===========================================================================
/**
 * @function    usb_shared_dp_high
 * 
 * @brief   API used to set D+ high
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_shared_dp_high(void)
{
  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_USB2PHY_USB_PHY_CFG0_OUTM(HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 
    0x1 << HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);

  // Set UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN
  HWIO_USB2PHY_USB_PHY_CFG0_OUTM(HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN_BMSK,
    0x1 << HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN_SHFT);

  // Set OPMODE to normal i.e. 0x00
  HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_OUTM(HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_OPMODE_BMSK,
    0x0 << HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_OPMODE_SHFT);

  // Set XCVRSEL and TERMSEL to FS.
  HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_OUTM(HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_XCVRSEL_BMSK,
    0x1 << HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_XCVRSEL_SHFT);

  HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_OUTM(HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_TERMSEL_BMSK,
    0x1 << HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_TERMSEL_SHFT);
}


// ===========================================================================
/**
 * @function    usb_shared_dp_default_state
 * 
 * @brief   API used to set D+ to default state
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_shared_dp_default_state(void)
{ 
  // Clear TERMSEL and XCVRSEL
  HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_OUTM(HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_TERMSEL_BMSK,
    0x0 << HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_TERMSEL_SHFT);

  HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_OUTM(HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_XCVRSEL_BMSK,
    0x0 << HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_XCVRSEL_SHFT);

  // Clear UTMI_PHY_CMN_CTRL_OVERRIDE_EN
  HWIO_USB2PHY_USB_PHY_CFG0_OUTM(HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 
    0x0 << HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);

  // Clear UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN
  HWIO_USB2PHY_USB_PHY_CFG0_OUTM(HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN_BMSK,
    0x0 << HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN_SHFT);
}


// ===========================================================================
/**
 * @function    usb_shared_dp_toggle
 * 
 * @brief   API used to toggle D+ high then low for interval in milliseconds
 * 
 * @param   interval_ms   interval in milliseconds
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_shared_dp_toggle(uint32 interval_ms)
{
  usb_shared_dp_high();

  usb_shared_delay_us(interval_ms * 1000);

  usb_shared_dp_default_state();

  usb_shared_delay_us(20);
}

void usb_shared_eud_update_serial_number(uint32 serial_num)
{
  //qusb_error_log(DCI_EUD_UPDATE_SERIAL_NUMBER_LOG, 0, serial_num);
  usb_shared_uart_log_error("usb_eud_serial ", serial_num);
  // ID_0 is LSB
  HWIO_EUD_DEV_ID_0_OUT( (serial_num &  0x000000FF)       );
  HWIO_EUD_DEV_ID_1_OUT( (serial_num &  0x0000FF00) >> 8  );
  HWIO_EUD_DEV_ID_2_OUT( (serial_num &  0x00FF0000) >> 16 );
  HWIO_EUD_DEV_ID_3_OUT( (serial_num &  0xFF000000) >> 24 );
}



#ifdef USB_APB_REG_FLAG

// ===========================================================================
/**
 * @function    usb_shared_apb_reset
 *
 * @brief   This function reset apb driver FSM in the wrapper and USB_PHY_APB_ACCESS_STATUS
 *          This will no resetting anything inside the PHY
 *
 * @param   None
 *
 * @return  None
 *
 */
// ===========================================================================

void usb_shared_apb_reset(void)
{
  HWIO_USB2PHY_USB_PHY_APB_ACCESS_CMD_OUT(0x4);
  usb_shared_delay_us(1);
  HWIO_USB2PHY_USB_PHY_APB_ACCESS_CMD_OUT(0x0);
}

// ===========================================================================
/**
 * @function    usb_shared_apb_read
 *
 * @brief   This function perform read phy through APB driver
 *
 * @param   addr   - address to read
 *          value  - pointer to data structure to store read value
 *
 * @return  None
 *
 */
// ===========================================================================

boolean usb_shared_apb_read(uint8 addr, uint16* value)
{
  uint32 timeout_cnt = 0;
  uint32 in_progress_flag = 0;
  uint32 lsb = 0;
  uint32 msb = 0;

  //1. Write APB address to be read
  HWIO_USB2PHY_USB_PHY_APB_ADDRESS_OUTM(HWIO_USB2PHY_USB_PHY_APB_ADDRESS_APB_REG_ADDR_BMSK, (addr) << HWIO_USB2PHY_USB_PHY_APB_ADDRESS_APB_REG_ADDR_SHFT);
  
  //2. Start Cmd   (startcmd | read_cmd)
  HWIO_USB2PHY_USB_PHY_APB_ACCESS_CMD_OUT(0x2);

  do {
    usb_shared_delay_us(1);  
    timeout_cnt++;
    in_progress_flag = HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_INM(HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_RMSK);
  } while ((0x8 == in_progress_flag) && timeout_cnt<1000);

  if (0x1 == HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_INM(HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_RMSK))
  {
    lsb = HWIO_USB2PHY_USB_PHY_APB_RDDATA_LSB_INM(HWIO_USB2PHY_USB_PHY_APB_RDDATA_LSB_APB_REG_RDDATA_7_0_BMSK) << HWIO_USB2PHY_USB_PHY_APB_RDDATA_LSB_APB_REG_RDDATA_7_0_SHFT;
    msb = HWIO_USB2PHY_USB_PHY_APB_RDDATA_MSB_INM(HWIO_USB2PHY_USB_PHY_APB_RDDATA_MSB_APB_REG_RDDATA_15_8_BMSK) << HWIO_USB2PHY_USB_PHY_APB_RDDATA_MSB_APB_REG_RDDATA_15_8_SHFT;
    *value = msb <<0x8 | lsb;
    
    usb_shared_info_log(QUSB_DCI_APB_REG_READ_LOG, 0, (addr<<16) | (*value));
    HWIO_USB2PHY_USB_PHY_APB_ACCESS_CMD_OUT(0x0);
    return TRUE;
  }
  usb_shared_error_log(QUSB_DCI_APB_REG_READ__FAIL_LOG, 0, HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_INM(HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_RMSK));
  // Any value other than 0x1(ACCESS_DONE) mean error has occurred, APB reset Sequence should be initiated
  HWIO_USB2PHY_USB_PHY_APB_ACCESS_CMD_OUT(0x0);
  usb_shared_apb_reset();
  return FALSE;  
}


// ===========================================================================
/**
 * @function    usb_shared_apb_write
 *
 * @brief   This function perform write phy through APB driver
 *
 * @param   addr   - address to write
 *          value  - data to write in phy
 *
 * @return  None
 *
 */
// ===========================================================================

boolean usb_shared_apb_write(uint8 addr, uint16 value)
{
  uint32 timeout_cnt = 0;
  uint32 in_progress_flag = 0;
  uint32 lsb = (value & 0x00FF);  
  uint32 msb = (value & 0xFF00)>>8;
  
  //1. Write APB address to be write
  HWIO_USB2PHY_USB_PHY_APB_ADDRESS_OUTM(HWIO_USB2PHY_USB_PHY_APB_ADDRESS_APB_REG_ADDR_BMSK, (addr) << HWIO_USB2PHY_USB_PHY_APB_ADDRESS_APB_REG_ADDR_SHFT);
  usb_shared_info_log(QUSB_DCI_APB_REG_WRITE_LOG, 0, (addr<<16) | value);

  //2. LSB
  HWIO_USB2PHY_USB_PHY_APB_WRDATA_LSB_OUTM(HWIO_USB2PHY_USB_PHY_APB_WRDATA_LSB_APB_REG_WRDATA_7_0_BMSK,
                                            (lsb) << HWIO_USB2PHY_USB_PHY_APB_WRDATA_LSB_APB_REG_WRDATA_7_0_SHFT);


  //2. MSB
  HWIO_USB2PHY_USB_PHY_APB_WRDATA_MSB_OUTM(HWIO_USB2PHY_USB_PHY_APB_WRDATA_MSB_APB_REG_WRDATA_15_8_BMSK,
                                            msb << HWIO_USB2PHY_USB_PHY_APB_WRDATA_MSB_APB_REG_WRDATA_15_8_SHFT);

  //3. start cmd (startcmd | write_cmd)
  HWIO_USB2PHY_USB_PHY_APB_ACCESS_CMD_OUT(0x3);

  do {
    usb_shared_delay_us(1);
    timeout_cnt++;
    in_progress_flag = HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_INM(HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_RMSK);
  } while ((0x8 == in_progress_flag) && timeout_cnt < USB_APB_TIMEOUT_US);

  if (0x1 == HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_INM(HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_RMSK))
  {
    HWIO_USB2PHY_USB_PHY_APB_ACCESS_CMD_OUT(0x0);
    return TRUE;
  }
  usb_shared_error_log(QUSB_DCI_APB_REG_WRITE__FAIL_LOG, 0, HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_INM(HWIO_USB2PHY_USB_PHY_APB_ACCESS_STATUS_RMSK));
  // Any value other than 0x1(ACCESS_DONE) mean error has occurred, APB reset Sequence should be initiated  
  HWIO_USB2PHY_USB_PHY_APB_ACCESS_CMD_OUT(0x0);
  usb_shared_apb_reset();
  return FALSE;
}

// ===========================================================================
/**
 * @function    usb_shared_apb_table_process
 *
 * @brief   This function reads from array which define list of APB read/writes for
 *          eUSB PHY
 *
 * @param   address_array   - array holding address of apb register
 *          value_array     - array holding values to be read/write to HW register
 *          array_entry_cnt - number of entries in the array
 *          write_flag      - to perform read(FALSE)/WRITE(TRUE) action
 *
 * @return  None
 *
 */
// ===========================================================================

void usb_shared_apb_table_process
(
  const uint8  *addr_array, 
  uint16       *value_array, 
  uint32        array_entry_cnt,
  boolean       write_flag
)
{
  uint32 index;

  if ( (NULL == addr_array)
    || (NULL == value_array)
    || (0 == array_entry_cnt) )
  {
      usb_shared_error_log(QUSB_DCI_APB_REG_ARRAY_PROCESS__FAIL_LOG, 0, (uint32)(uintnt)addr_array);
      return;
  }

  for (index =0; index<array_entry_cnt; index++)
  {
    if (APB_USB_PHY_EMPTY == addr_array[index])
    {
      // Skipping this entries
    }
    else
    {
      if (write_flag)
      {
        if (FALSE == usb_shared_apb_write(addr_array[index],value_array[index]))
        {
          usb_shared_error_log(QUSB_DCI_APB_REG_ARRAY_PROCESS__FAIL_LOG, 0, index);
        }
      }
      else
      {
        if (FALSE == usb_shared_apb_read(addr_array[index],&value_array[index]))
        {
          usb_shared_error_log(QUSB_DCI_APB_REG_ARRAY_PROCESS__FAIL_LOG, 0, index);
        }
      }
    }
  }
  usb_shared_error_log(QUSB_DCI_APB_REG_ARRAY_PROCESS____END_LOG, 0, index);
}
#endif

boolean usb_shared_uint32add_ovrflw(uint32 a, uint32 b)
{
  if(b <= (UINT32_MAX - a))
    return FALSE;
  else
    return TRUE;
}

