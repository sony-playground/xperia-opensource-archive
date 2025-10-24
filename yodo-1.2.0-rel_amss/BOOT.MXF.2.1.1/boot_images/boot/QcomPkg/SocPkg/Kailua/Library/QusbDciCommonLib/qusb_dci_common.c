/*=======================================================================*//**
 * @file        qusb_dci_common.c
 * @author:     kameya
 * @date        28-Dec-2015
 *
 * @brief       QUSB common parts of DCI shared by QusbFedlLib & QusbTargetLib.
 *
 * @details     This file contains the implementation of basic APIs to be used
 *              by both QusbTargetLib and QusbFedlLib
 *
 * @note        
 *
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2015, 2017-2022 Qualcomm Technologies, Inc. All rights reserved.
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
// 02/10/20      pw      Port Force Emergency Download (EDL) detecting Dp Ground 
// 02/13/18      gk	 Port changes from boot.xf.2.0 and boot.xf.2.2
// 2017-02-02    pm      Add UsbSharedLib
// 2015-12-28    kameya  First Draft
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "comdef.h"    // basic types as byte word uint32 etc
#include "busywait.h"  // busywait APIs
#include "DALSys.h"    // To get phy settings
#include "qusb_dci_common.h"
#include "qusb_common.h"
#include "HalusbHWIO.h"
#include "HalGccUsb.h"
#include "qusb_log.h"
#include "PlatformInfo.h"
#include "UsbSharedLib.h"
#include "pm_ldo.h"


// ---------------------------------------------------------------------------
// Force Emergency Download (EDL) detecting Dp Ground ++
// ---------------------------------------------------------------------------
#define USB_FEDL_MAX_DP_LOW_TIMEOUT_MS   (50)
#define USB_FEDL_MAX_DP_HIGH_TIMEOUT_MS  (10000)
#define USB_FEDL_DP_BMSK            (0x1)
#define USB_FEDL_EDP_BMSK                (0x1)

#define USB_EUSB_FLAG       (1)

#define USB_CFG_DTB_DEBUG_SEL_ADDR    (0x52)    // Dtb Debug Selection register address
#define USB_CFG_DTB_DEBUG_SEL_EDP_EDM (0x00B1)  // SE Receiver data for eDP,eDM 


// ---------------------------------------------------------------------------
// Force Emergency Download (EDL) --
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// EUD Tuning Parameter register table ++
// ---------------------------------------------------------------------------

#define USB2PHY_OFF(a) (((a)-(USB2PHY_CM_DWC_USB2_REG_BASE))/4)
#define EUD_USB_PHY_EMPTY (0x00)
#define QUSB_EUD_TUNE_TABLE_SIZE (24)

static uint8 qusb_dci_eud_reg_addr[QUSB_EUD_TUNE_TABLE_SIZE] =
{
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG0_ADDR                                  ),    //    0    :    (0x1)  DummyRow for EUD workaround
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG0_ADDR                                  ),    //    0    :    (0x1)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_UTMI_CTRL5_ADDR                            ),    //    1    :    (0x2)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR                   ),    //    2    :    (0x9)

  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_APB_ACCESS_CMD_ADDR                        ),    //    3    :    (0x4)
  USB2PHY_OFF( HWIO_USB2PHY_UTMI_PHY_CMN_CTRL0_ADDR                            ),    //    4    :    (0x0)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_FSEL_SEL_ADDR                              ),    //    5    :    (0x1)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR                   ),    //    6    :    (0x49) // 38.4 Mhz
  
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_2_ADDR                            ),    //    7    :    (0xC8) // 38.4 Mhz
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_3_ADDR                            ),    //    8    :    (0x0)  // 38.4 Mhz
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_1_ADDR                            ),    //    9    :    (0x2)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_4_ADDR                            ),    //    10   :    (0x21)
  
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_6_ADDR                            ),    //    11   :    (0x0)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_5_ADDR                            ),    //    12   :    (0x50)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_ADDR                          ),    //    13   :    (0x17)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_9_ADDR                            ),    //    14   :    (0xC8)
  
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_8_ADDR                            ),    //    15   :    (0x18)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_9_ADDR                            ),    //    16   :    (0xC8)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_ADDR                          ),    //    17   :    (0x1F)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_ADDR                            ),    //    18   :    (0x1)
  
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR                   ),    //    19   :    (0x4B) // 38.4 Mhz
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_UTMI_CTRL5_ADDR                            ),    //    20   :    (0x0)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_ADDR                          ),    //    21   :    (0x17)
  USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG0_ADDR                                  ),    //    22   :    (0x0)
};

static uint8 qusb_dci_eud_reg_val[QUSB_EUD_TUNE_TABLE_SIZE] =
{
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG0_ADDR                                  ),      0    */   (0x1),  //DummyRow for EUD workaround
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG0_ADDR                                  ),      0    */   (0x1),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_UTMI_CTRL5_ADDR                            ),      1    */   (0x2),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR                   ),      2    */   (0x9),

  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_APB_ACCESS_CMD_ADDR                        ),      3    */   (0x4),
  /* USB2PHY_OFF( HWIO_USB2PHY_UTMI_PHY_CMN_CTRL0_ADDR                            ),      4    */   (0x0),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_FSEL_SEL_ADDR                              ),      5    */   (0x1),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR                   ),      6    */   (0x49), // 38.4 Mhz
  
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_2_ADDR                            ),      7    */   (0xC8), // 38.4 Mhz
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_3_ADDR                            ),      8    */   (0x0),  // 38.4 Mhz
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_1_ADDR                            ),      9    */   (0x2),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_4_ADDR                            ),      10   */   (0x21),
  
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_6_ADDR                            ),      11   */   (0x0),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_5_ADDR                            ),      12   */   (0x50),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_ADDR                          ),      13   */   (0x17),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_9_ADDR                            ),      14   */   (0xC8),
  
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_8_ADDR                            ),      15   */   (0x18),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG_CTRL_9_ADDR                            ),      16   */   (0xC8),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_ADDR                          ),      17   */   (0x1F),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_ADDR                            ),      18   */   (0x1),
  
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR                   ),      19   */   (0x4B), // 38.4 Mhz
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_UTMI_CTRL5_ADDR                            ),      20   */   (0x0),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_ADDR                          ),      21   */   (0x17),
  /* USB2PHY_OFF( HWIO_USB2PHY_USB_PHY_CFG0_ADDR                                  ),      22   */   (0x0),
};

// ---------------------------------------------------------------------------
// EUD Tuning Parameter register table --
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// EUD Tuning Parameter register table --
// ---------------------------------------------------------------------------

//============================================================================

/**
* @function  qusb_dci_get_platform
*
* @brief Read platforminfo from DAL API and cache it.
*
* @Note : None.
*
* @param None.
*
* @return None.
*
*/
//============================================================================
qusb_dci_platform_type qusb_dci_get_platform(void)
{
  static qusb_dci_platform_type qusb_platform = QUSB_DCI_PLATFORM_UNKNOWN;
  DalPlatformInfoPlatformType platform;

  if (qusb_platform == QUSB_DCI_PLATFORM_UNKNOWN)
  {
    platform = PlatformInfo_Platform();
    qusb_uart_log("qusb_platform", (uint32)platform);
    switch(platform)
    {
      case DALPLATFORMINFO_TYPE_RUMI:
      {
        qusb_platform = QUSB_DCI_PLATFORM_RUMI;
      }
      break;
      
      case DALPLATFORMINFO_TYPE_VIRTIO:
      {
        qusb_platform = QUSB_DCI_PLATFORM_VIRTIO;
      }
      break;

      default:
        qusb_platform = QUSB_DCI_PLATFORM_SILICON;
    }
  }

  return qusb_platform;
}


//============================================================================

/**
* @function  qusb_dci_delay_ms
*
* @brief Perform delay in milliseconds.
*
* @Note : The USB Timers can not be used before the core is initialized.
*
* @param milliseconds
*
* @return none
*
*/
//============================================================================
void qusb_dci_delay_ms(uint32 msecs)
{
  int counter;

  for (counter = 0; counter < msecs; counter++)
  {
    busywait(1000); // 1 ms
  }   
}


//============================================================================
/**
* @function  qusb_dci_delay_us
*
* @brief Perform delay in microseconds.
*
* @Note : The USB Timers can not be used before the core is initialized.
*
* @param microseconds
*
* @return none
*
*/
//============================================================================
void qusb_dci_delay_us(uint32 usecs)
{
  busywait( usecs );
}

// ===========================================================================
/**
 * @function    qusb_hs_phy_gcc_reset
 * 
 * @brief   API used for resetting High Speed QUSB2 PHY using GCC control
 *  
 * @details API is used for resetting High Speed QUSB2 PHY using GCC control
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_hs_phy_gcc_reset(void)
{
  HWIO_GCC_QUSB2PHY_PRIM_BCR_OUTM(HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK,(0x1 << HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_SHFT));
  qusb_dci_delay_us(100);

  HWIO_GCC_QUSB2PHY_PRIM_BCR_OUTM(HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK,(0x0 << HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_SHFT));
  qusb_dci_delay_us(100);
}

// ===========================================================================
/**
 * @function    qusb_dci_usb30_gcc_reset
 * 
 * @brief   API used for resetting the Link and PHYs using GCC control
 *  
 * @details This API is used for resetting the Link and PHYs using clock control 
 * 
 * @param   boolean is_eud_active - pass if EUD is active, so PHY reset can
 *                                  be skipped.
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_usb30_gcc_reset(boolean is_eud_active)
{
  /* Reset SNPS Link controller */
  //Reset all USB3PHY Register
  HWIO_GCC_USB3_DP_PHY_PRIM_BCR_OUTM(HWIO_GCC_USB3_DP_PHY_PRIM_BCR_BLK_ARES_BMSK, (0x1<< HWIO_GCC_USB3_DP_PHY_PRIM_BCR_BLK_ARES_SHFT));
  //Reset USB3PHY REG
  HWIO_GCC_USB30_PRIM_BCR_OUTM(HWIO_GCC_USB30_PRIM_BCR_BLK_ARES_BMSK,(0x1 << HWIO_GCC_USB30_PRIM_BCR_BLK_ARES_SHFT));
  qusb_dci_delay_us(100);
  HWIO_GCC_USB30_PRIM_BCR_OUTM(HWIO_GCC_USB30_PRIM_BCR_BLK_ARES_BMSK,(0x0 << HWIO_GCC_USB30_PRIM_BCR_BLK_ARES_SHFT));
  HWIO_GCC_USB3_DP_PHY_PRIM_BCR_OUTM(HWIO_GCC_USB3_DP_PHY_PRIM_BCR_BLK_ARES_BMSK, (0x0<< HWIO_GCC_USB3_DP_PHY_PRIM_BCR_BLK_ARES_SHFT));

  
  /* Reset USB 2.0 and QMP (USB 3.0) PHYs */
  
  // SNPS Femto GCC RESET
  if (FALSE == is_eud_active)
  {
    HWIO_GCC_QUSB2PHY_PRIM_BCR_OUTM(HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK,(0x1 << HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_SHFT));
  }
  HWIO_GCC_USB3_PHY_PRIM_BCR_OUTM(HWIO_GCC_USB3_PHY_PRIM_BCR_BLK_ARES_BMSK,(0x1 << HWIO_GCC_USB3_PHY_PRIM_BCR_BLK_ARES_SHFT));
  HWIO_GCC_USB3PHY_PHY_PRIM_BCR_OUTM(HWIO_GCC_USB3PHY_PHY_PRIM_BCR_BLK_ARES_BMSK, (0x1 << HWIO_GCC_USB3PHY_PHY_PRIM_BCR_BLK_ARES_SHFT));
  
  qusb_dci_delay_us(100);
  
  HWIO_GCC_USB3PHY_PHY_PRIM_BCR_OUTM(HWIO_GCC_USB3PHY_PHY_PRIM_BCR_BLK_ARES_BMSK, (0x0 << HWIO_GCC_USB3PHY_PHY_PRIM_BCR_BLK_ARES_SHFT));
  HWIO_GCC_USB3_PHY_PRIM_BCR_OUTM(HWIO_GCC_USB3_PHY_PRIM_BCR_BLK_ARES_BMSK,(0x0 << HWIO_GCC_USB3_PHY_PRIM_BCR_BLK_ARES_SHFT));
  if (FALSE == is_eud_active)
  {
    HWIO_GCC_QUSB2PHY_PRIM_BCR_OUTM(HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK,(0x0 << HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_SHFT));
  }
  
  qusb_dci_delay_us(100);  

  return; 
}

// ===========================================================================
/**
 * @function    qusb_dci_select_utmi_clk
 * 
 * @brief   This is used for configuring the core to UTMI clock instead of pipe
 *          clock.  This needs to be called when there is no SS USB PHY.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_select_utmi_clk(void)
{
  qusb_error_log(QUSB_DCI_SELECT_UTMI_CLK_LOG, 0, 0);

  qusb_uart_log("utmi_only",0);
  
  // If operating without SS PHY, follow this sequence to disable 
  // pipe clock requirement
  HWIO_USB3_PRI_GENERAL_CFG_OUTM(HWIO_USB3_PRI_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK,
    0x1 << HWIO_USB3_PRI_GENERAL_CFG_PIPE_UTMI_CLK_DIS_SHFT);
  
  qusb_dci_delay_us(100);
  
  HWIO_USB3_PRI_GENERAL_CFG_OUTM(HWIO_USB3_PRI_GENERAL_CFG_PIPE_UTMI_CLK_SEL_BMSK,
    0x1 << HWIO_USB3_PRI_GENERAL_CFG_PIPE_UTMI_CLK_SEL_SHFT);
  
  qusb_dci_delay_us(100);
  
  HWIO_USB3_PRI_GENERAL_CFG_OUTM(HWIO_USB3_PRI_GENERAL_CFG_PIPE3_PHYSTATUS_SW_BMSK,
    0x1 << HWIO_USB3_PRI_GENERAL_CFG_PIPE3_PHYSTATUS_SW_SHFT);
  
  qusb_dci_delay_us(100);
  
  HWIO_USB3_PRI_GENERAL_CFG_OUTM(HWIO_USB3_PRI_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK,
    0x0 << HWIO_USB3_PRI_GENERAL_CFG_PIPE_UTMI_CLK_DIS_SHFT);
}

// ===========================================================================
/**
 * @function    qusb_dci_hs_phy_update_hstx_trim
 * 
 * @brief   This function will update TUNE2 HSTX_TRIM register bits if feature is enabled.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_hs_phy_update_hstx_trim(void)
{
  // For future reference
}

// =============================================================================
/**
 * @function    qusb_dci_ahb2phy_cfg
 * 
 * @brief   Configures AHB2PHY read/write states to be 1 wait cycle each.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// =============================================================================
void qusb_dci_ahb2phy_cfg(void)
{
  qusb_dci_delay_us(10);
  
  // Write 0x11 to AHB2PHY bridge CSR PERIPH_SS_AHB2PHY_TOP_CFG so that 
  // writes and reads to/from the PHY use one wait state.
  // This is essential to operate at nominal freq with lower CX rail voltages.
  // HAL_USB_WRITE (AHB2PHY_SOUTH_AHB2PHY_SOUTH_BASE, HWIO_AHB2PHY_SOUTH_AHB2PHY_SOUTH_AHB2PHY_TOP_CFG_OFFS, 0x11);

}

// ===========================================================================
/**
 * @function    qusb_hs_phy_init
 * 
 * @brief   API used to initialize the High Speed PHY.
 * 
 * @param   None.
 * 
 * @return  TRUE if PHY initializes successfully, FALSE otherwise.
 * 
 */
// ===========================================================================
boolean qusb_hs_phy_init(void)
{
  if (usb_shared_is_eud_active())
  {
    return TRUE;
  }
  qusb_hs_phy_gcc_reset();
  return usb_shared_hs_phy_init();
}

boolean qusb_dci_init_dp_gnd_state(void)
{
#if USB_EUSB_FLAG
  uint8 apb_retry = 0;
  //uint16 apb_read = 0;

  for (apb_retry =0; apb_retry < 3; apb_retry++)
  {
    if (usb_shared_apb_write(USB_CFG_DTB_DEBUG_SEL_ADDR, USB_CFG_DTB_DEBUG_SEL_EDP_EDM))
    {
      //usb_shared_apb_read(USB_CFG_DTB_DEBUG_SEL_ADDR, &apb_read);
      //qusb_uart_log("eDP Overwrite pass", apb_read);
      return TRUE;
    }
  }
  qusb_uart_log("init_dp_gnd Failed", apb_retry);
  return FALSE;
#else
  return TRUE;
#endif
}

boolean qusb_dci_get_dp_gnd_state(void)
{
  uint32 dpGnd_state =0;
  // no USB cable connected HiZ //HS_PHY_TEST_OUT[TestDataOut] == 0 
  // FEDL D+ cable high         //HS_PHY_TEST_OUT[TestDataOut] == 0
  // normal SDP cable           //HS_PHY_TEST_OUT[TestDataOut] toggles 1 & 0 and settles at 0x0
  // FEDL D+ cable GND          //HS_PHY_TEST_OUT[TestDataOut] == 1  
  dpGnd_state = (HWIO_USB2PHY_USB_PHY_HS_PHY_TEST_OUT_1_INM(HWIO_USB2PHY_USB_PHY_HS_PHY_TEST_OUT_1_TESTDATAOUT_BMSK) 
            >> HWIO_USB2PHY_USB_PHY_HS_PHY_TEST_OUT_1_TESTDATAOUT_SHFT) & USB_FEDL_EDP_BMSK;
  if (1 == dpGnd_state)
  {
    return TRUE;
  }
  return FALSE;
}


// ===========================================================================
/**
 * @function    qusb_dci_dp_gnd_check
 * 
 * @brief   API used to check if D+ is grounded.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
boolean qusb_dci_dp_gnd_check(boolean check_dp_high, uint32 check_dp_timeout_ms)
{
  uint16 ls_tries = 0;
  boolean enter_fedl = FALSE;
  boolean dp_gnd_state = TRUE;

  qusb_uart_log("qusb_dci_dp_gnd_check: ", check_dp_high);

  usb_shared_dp_high();

  usb_shared_delay_us(20);

  if(FALSE == qusb_dci_init_dp_gnd_state())
  {
    //Cannot setup dp_gnd state, skip FEDL
    return FALSE;
  }

  // Enter forced EDL mode if D+ is grounded for 50ms.
  for(ls_tries = 0; (TRUE == dp_gnd_state) && (ls_tries < USB_FEDL_MAX_DP_LOW_TIMEOUT_MS);  ls_tries++)
  {
   
    dp_gnd_state = qusb_dci_get_dp_gnd_state();

    if(FALSE == dp_gnd_state)
    {
      qusb_uart_log("dpGnd LOW, break", 0);
      break;
    }
    usb_shared_delay_us(1000);
  }

  if ((TRUE == dp_gnd_state) && (ls_tries >= USB_FEDL_MAX_DP_LOW_TIMEOUT_MS))
  {
    qusb_uart_log("dpGnd HIGH", 0);
    
    // Force EDL check using Dp GND and pull up to Dp HIGH back in timeout
    // This flag prevent device accidentally entering EDL when connected to
    // powered off USB port on PC or Hub that has D+ GND.
    // It requires User to unplug special Dp GND USB cable within the timeout
    // in order to enter EDL.
    if (FALSE == check_dp_high)
    {
      // Enter forced EDL mode just with D+ GND.
      enter_fedl = TRUE;
    }
    else
    {
      // Enter forced EDL mode if D+ is now back-up within N seconds.
      for(ls_tries = check_dp_timeout_ms; (dp_gnd_state == 1) && (ls_tries > 0);  ls_tries--)
      {

        dp_gnd_state = qusb_dci_get_dp_gnd_state();

        if(ls_tries%1000==0)
        {
          qusb_uart_log("wait unplug(dpGnd LOW), (ms):", ls_tries);
        }
        
        if (FALSE == dp_gnd_state)
        {
          qusb_uart_log("dpGnd LOW, enter FEDL", 0);
          enter_fedl = TRUE;
          break;
        }
        usb_shared_delay_us(1000);
      }
    }
  }

  usb_shared_dp_default_state();


  usb_shared_delay_us(20);

  qusb_error_log(DCI_ENTER_FEDL_LOG, 0, enter_fedl);

  return enter_fedl;
}

// =============================================================================
/**
 * @function    qusb_hs_phy_nondrive_cfg
 * 
 * @brief   Function used to configure High Speed PHY in non-drive mode.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// =============================================================================
void qusb_hs_phy_nondrive_cfg(void)
{
  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN
  HWIO_USB2PHY_USB_PHY_CFG0_OUTM(HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK, 
    0x1 << HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);

  // Set UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN
  HWIO_USB2PHY_USB_PHY_CFG0_OUTM(HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN_BMSK,
    0x1 << HWIO_USB2PHY_USB_PHY_CFG0_UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN_SHFT);

  // Set OPMODE to nondrive i.e. 0x1
  HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_OUTM(HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_OPMODE_BMSK,
    0x1 << HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_OPMODE_SHFT);

  // Set XCVRSEL and TERMSEL to FS.
  HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_OUTM(HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_XCVRSEL_BMSK,
    0x1 << HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_XCVRSEL_SHFT);

  HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_OUTM(HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_TERMSEL_BMSK,
    0x1 << HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_TERMSEL_SHFT);

}


// ===========================================================================
/**
 * @function    qusb_dci_eud_phy_tune
 * 
 * @brief       This function will populate QUSB2PHY registers onto EUD mode 
 *              manager CSR.
 * 
 * @param   none.
 * 
 * @return  none.
 * 
 */
// ===========================================================================
void qusb_dci_eud_phy_tune(void)
{
  uint32 addr   = 0;
  uint32 index  = 0;

  if (HWIO_VIOCTL_EUD_DETECT_INM(HWIO_VIOCTL_EUD_DETECT_EUD_DETECT_BMSK) == 0)
  {
    qusb_uart_log("vioclt_eud_set", HWIO_VIOCTL_EUD_DETECT_IN);

    /* Set VIOCTL_EUD_DETECT = 0x1 for device mode to indicate cable connect / Vbus HIGH */
    HWIO_VIOCTL_EUD_DETECT_OUTM(HWIO_VIOCTL_EUD_DETECT_EUD_DETECT_BMSK, 
      0x1 << HWIO_VIOCTL_EUD_DETECT_EUD_DETECT_SHFT);
  }
  /** TEST CODE to enable EUD ======================
  // Enable EUD_EN2 has WRITE-PROTECTION and can be only written in SECURE MODE
  //HWIO_EUD_EUD_EN2_OUTM(HWIO_EUD_EUD_EN2_EUD_EN2_BMSK,
  //  1 << HWIO_EUD_EUD_EN2_EUD_EN2_SHFT);

  // Wait 10s
  for (index = 0; index < 10; index++)
  {
    qusb_dci_delay_ms(1000);
    qusb_uart_log("waiting before eud tuning ....", index);
  }
  ================================================= **/
  usb_shared_refclk_enable(TRUE);
  
  // 32 tuning parameters will be loaded into PHY when pbus_ctlr_en is set if XTRA_TUNE_PARAM is set to 0x1;
  // 16 otherwise
  HWIO_EUD_EUSB2PHY_XTRA_TUNE_PARARM_EN_OUTM(
    HWIO_EUD_EUSB2PHY_XTRA_TUNE_PARARM_EN_EUSB2PHY_XTRA_TUNE_PARAM_EN_0_0_BMSK,
    1 << HWIO_EUD_EUSB2PHY_XTRA_TUNE_PARARM_EN_EUSB2PHY_XTRA_TUNE_PARAM_EN_0_0_SHFT);

  for (index = 0, addr = HWIO_EUD_Q2_TUNE_ADR00_ADDR; 
      (index < QUSB_EUD_TUNE_TABLE_SIZE) && (addr <= HWIO_EUD_Q2_TUNE_ADR23_ADDR); 
      index++)
  {
    if (qusb_dci_eud_reg_addr[index] == EUD_USB_PHY_EMPTY) continue;

    out_dword(addr, qusb_dci_eud_reg_addr[index]);
    addr+=4;
    out_dword(addr, qusb_dci_eud_reg_val[index]);
    addr+=4;
  }
      
  HWIO_EUD_PBUS_CTRL_EN_OUTM(HWIO_EUD_PBUS_CTRL_EN_PBUS_CTRL_EN_0_0_BMSK,
    0x1 << HWIO_EUD_PBUS_CTRL_EN_PBUS_CTRL_EN_0_0_SHFT);

 /** TEST CODE to enable EUD ======================
  // Enable EUD_EN2 has WRITE-PROTECTION and can be only written in SECURE MODE
  //HWIO_EUD_EUD_EN2_OUTM(HWIO_EUD_EUD_EN2_EUD_EN2_BMSK,
  //  1 << HWIO_EUD_EUD_EN2_EUD_EN2_SHFT);

  // Wait 10s
  for (index = 0; index < 10; index++)
  {
    qusb_dci_delay_ms(1000);
    qusb_uart_log("waiting for eud to enumerate ....", index);
  }
 // Check if PHY tune took effect
 qusb_uart_log("PHY TUNE:   RTUNE_SEL", HWIO_USB2PHY_USB_PHY_RTUNE_SEL_IN);
 qusb_uart_log("PHY TUNE: OVERRIDE_X1", HWIO_USB2PHY_USB_PHY_PARAMETER_OVERRIDE_X1_IN);

 ================================================= **/
}

// ===========================================================================
/**
 * @function    qusb_dci_eud_init
 * 
 * @brief       This function uses a spare register to indicate that EUD is 
                connected to an SDP / CDP port & EUD PHY init is complete.
                NS side can use this flag to keep track of EUD status if needed.
 * 
 * @param   none.
 * 
 * @return  none.
 * 
 */
// ===========================================================================
void qusb_dci_eud_init(void)
{
  qusb_uart_log("qusb_dci_eud_init", 0);

  HWIO_EUD_CSR_EUD_EN_OUTM(HWIO_EUD_CSR_EUD_EN_CSR_EUD_EN_0_0_BMSK, 
    1 << HWIO_EUD_CSR_EUD_EN_CSR_EUD_EN_0_0_SHFT);

  // Program EUD sw_attach to prevent transition to safe mode
/*  if (HWIO_EUD_SW_ATTACH_DET_INM(
        HWIO_EUD_SW_ATTACH_DET_SW_ATTACH_DET_0_0_BMSK))
  {
    HWIO_EUD_SW_ATTACH_DET_OUTM(
      HWIO_EUD_SW_ATTACH_DET_SW_ATTACH_DET_0_0_BMSK,
      (0x0 << HWIO_EUD_SW_ATTACH_DET_SW_ATTACH_DET_0_0_SHFT));
    qusb_dci_delay_ms(1);
  }
  HWIO_EUD_SW_ATTACH_DET_OUTM(
    HWIO_EUD_SW_ATTACH_DET_SW_ATTACH_DET_0_0_BMSK,
    (0x1 << HWIO_EUD_SW_ATTACH_DET_SW_ATTACH_DET_0_0_SHFT));
*/
}

// ===========================================================================
/**
 * @function    qusb_dci_enable_usb2_ldo
 * 
 * @brief   This function will be used to turn ON the USB2 LDO
 * 
 * @param   None
 * 
 * @return  TRUE or FALSE depending on success or failure.
 * 
 */
// ===========================================================================
void qusb_dci_enable_usb2_ldo(boolean enable)
{ 
  (void)enable;
  // Not supported
}

//============================================================================
/**
 * @function  qusb_dci_get_speed
 *
 * @brief Report the USB connection speed.
 *
 * @Note : Although the device is high-speed, the Host might be full-speed.
 *
 * @Note : The USB HW can be forced to Full-Speed.
 *
 * @param None 
 * @return Speed
 *              QUSB_SPEED_FULL        
 *              QUSB_SPEED_LOW         
 *              QUSB_SPEED_HIGH        
 *              QUSB_SPEED_FULL
 *              QUSB_SPEED_UNKNOWN     
 *
 * @ref SNPS spec 
 *       Chapter 6.3.1.4 DSTS ( bits 0-2)
 *
 */
//============================================================================
qusb_device_connect_speed_t qusb_dci_get_speed(void)
{
  qusb_device_connect_speed_t speed;
  /* Read DSTS to determine the speed */
  speed = HWIO_USB3_PRI_DSTS_INM(HWIO_USB3_PRI_DSTS_CONNECTSPD_BMSK);
  qusb_log(DCI_GET_SPEED_LOG, 0, (uint32)speed);
  return(speed);
}

