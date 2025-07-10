/*=======================================================================*//**
 * @file        UsbRepeater.c
 * @author:     pohanw
 * @date        09-Sep-2021
 *
 * @brief       USB common & shared USB core implementation for repeater Library.
 *
 * @details     This file contains sequence to enable repeater.
 *
 * @note        
 *
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2021-2022 Qualcomm Technologies, Inc. All rights reserved.
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
// 09/09/21     pohanw   Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "UsbSharedLibI2c.h"
#include "HalusbHWIO.h"
#include "DDITlmm.h"
#include "DALSys.h"   // Required for DALSYS_InitMod for TLMM
#include "UsbRepeater.h"
#include "UsbSharedLib.h"

usb_i2c_ctx_type usb_repeater_i2c_ctx[USB_I2C_CORE_NUM_MAX];

// SMB1355 mounted on I2C instance 021, but since SBL sequence start from 1, 
// so here it is 022 instead 021

#define USB_I2C_REPEATER_INSTANCE_PRIMARY                            (I2C_INSTANCE_006)

#define USB_I2C_NXP_REPEATER_SLAVE_ADDRESS_PRIMARY                   (0x4F)
#define USB_I2C_TI_REPEATER_SLAVE_ADDRESS_PRIMARY                    (0x3E)

typedef struct 
{
  uint8  reg;
  uint8  data;
} usb_repeater_cfg_type;

const usb_repeater_cfg_type*  g_repeater_tuning_cfg_handle;
uint32 g_repeater_tuning_size;

static const usb_repeater_cfg_type NXP_REPEATER_TUNING_CFG_PLAT_MTP [] = 
{
  //in V1 the reset value change to 0x0, but to keep compa with V0 chip, write 0xD within 100 ms of releasing RESETN 

  {0x06, 0x40},  // Rx squelch detection threshold to 110mV; default is 125mV
  {0x07, 0x22},  // Tx Deemphasis to 2dB, Tx Deemphasis bit duration to 0.8UI;  default is 0 for both
  {0x08, 0x63},  // Output Voltage Swing to 500mV; default is 450mV 

};

static const usb_repeater_cfg_type NXP_REPEATER_TUNING_CFG_PLAT_QRD [] = 
{
  //in V1 the reset value change to 0x0, but to keep compa with V0 chip, write 0xD within 100 ms of releasing RESETN 

  {0x06, 0x40},  // Rx squelch detection threshold to 110mV; default is 125mV
  {0x07, 0x22},  // Tx Deemphasis to 2dB, Tx Deemphasis bit duration to 0.8UI; default is 0 for both
  {0x08, 0x64},  // Output Voltage Swing to 550mV; default is 450mV
};

static const usb_repeater_cfg_type TI_REPEATER_TUNING_CFG_PLAT_CDP [] = 
{
  //in V1 the reset value change to 0x0, but to keep compa with V0 chip, write 0xD within 100 ms of releasing RESETN 

  {0x70, 0x7C},  // Tx Amplitude ; 400mV to 490mV
  {0x71, 0x3B},  // Tx Pre-Emphasis ; 0.5dB to 2.1dB
  {0x73, 0x02},  // Disconnect Squelch Threshold ; 104mV to 117mV
};

static const usb_repeater_cfg_type TI_REPEATER_TUNING_CFG_PLAT_ATP [] = 
{
  //in V1 the reset value change to 0x0, but to keep compa with V0 chip, write 0xD within 100 ms of releasing RESETN 

  {0x70, 0x80},  // Tx Amplitude
  {0x71, 0x3B},  // Tx Pre-Emphasis
  {0x73, 0x05},  // Disconnect Squelch Threshold
};

boolean usb_shared_print_rep_tune_cfg(void)
{
  uint8 index =0;
  uint8 result =0;
  uint8 data = 0;

  for (index=0; index < g_repeater_tuning_size; index++)
  {
    result = usb_shared_i2c_read(&usb_repeater_i2c_ctx[0], g_repeater_tuning_cfg_handle[index].reg, 
                                        &data, 8);
    if (FALSE == result)
    {
      usb_shared_uart_log_error("read tune failed: :", result);
      return FALSE;
    }	
    usb_shared_uart_log_error("read reg|data: ", (uint32)g_repeater_tuning_cfg_handle[index].reg*10000 + (uint32)data);  
  }
  return TRUE;
}

// ===========================================================================
/**
 * @function    usb_repeater_process_cfg_reg_array
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
static boolean usb_repeater_process_cfg_reg_array
(
  const usb_repeater_cfg_type*  cfg_table,
  uint32                    start_index, 
  uint32                    array_entry_cnt,
  uint32                    core_num
)
{
  uint32 index = start_index;
  boolean result;

  if ( (NULL == cfg_table)
      || (0 == array_entry_cnt) )
  {
    usb_shared_uart_log_error("Process_Array: Null Parameter Passed", 0);
    return FALSE;
  }
  for (; index < array_entry_cnt; index++)
  {
    result = usb_shared_i2c_write(&usb_repeater_i2c_ctx[core_num], cfg_table[index].reg, cfg_table[index].data, 8);
    if (FALSE == result)
      return FALSE;
  }

  return usb_shared_print_rep_tune_cfg();
}

volatile boolean usb_shared_enable_repeater_support = FALSE;

// ===========================================================================
/**
 * @function    usb_repeater_get_tuning_cfg
 * 
 * @brief   This function configures the repeater tuning config array for a given 
 *          platform type 
 *          on QC reference design: MTP & QRD -> NXP repeater 
 *          CDP & ATP board -> TI repeater
 * 
 * @param   plat_type - usb_platform_ctx data type having platform type details.
 * 
 * @return  boolean - TRUE if tuning allowed for the platform, FALSE otherwise
 * 
 */
// ===========================================================================
static void usb_repeater_get_tuning_cfg (uint8 core_num, usb_platform_ctx plat_type)
{
  usb_repeater_i2c_ctx[core_num].instance = USB_I2C_REPEATER_INSTANCE_PRIMARY;

  switch (plat_type.platform)
  {
    case DALPLATFORMINFO_TYPE_QRD:
      g_repeater_tuning_cfg_handle = NXP_REPEATER_TUNING_CFG_PLAT_QRD;
      g_repeater_tuning_size = (sizeof(NXP_REPEATER_TUNING_CFG_PLAT_QRD) / sizeof(usb_repeater_cfg_type));
      usb_repeater_i2c_ctx[core_num].config.slave_address = USB_I2C_NXP_REPEATER_SLAVE_ADDRESS_PRIMARY;
      break;

    case DALPLATFORMINFO_TYPE_MTP:
      /* fall through */
    case DALPLATFORMINFO_TYPE_IDP:
      g_repeater_tuning_cfg_handle = NXP_REPEATER_TUNING_CFG_PLAT_MTP;
      g_repeater_tuning_size = (sizeof(NXP_REPEATER_TUNING_CFG_PLAT_MTP) / sizeof(usb_repeater_cfg_type));
      usb_repeater_i2c_ctx[core_num].config.slave_address = USB_I2C_NXP_REPEATER_SLAVE_ADDRESS_PRIMARY;
      break;

    case DALPLATFORMINFO_TYPE_CDP:
      g_repeater_tuning_cfg_handle = TI_REPEATER_TUNING_CFG_PLAT_CDP;
      g_repeater_tuning_size = (sizeof(TI_REPEATER_TUNING_CFG_PLAT_CDP) / sizeof(usb_repeater_cfg_type));
      usb_repeater_i2c_ctx[core_num].config.slave_address = USB_I2C_TI_REPEATER_SLAVE_ADDRESS_PRIMARY;
      break;

    case DALPLATFORMINFO_TYPE_ATP:
      g_repeater_tuning_cfg_handle = TI_REPEATER_TUNING_CFG_PLAT_ATP;
      g_repeater_tuning_size = (sizeof(TI_REPEATER_TUNING_CFG_PLAT_ATP) / sizeof(usb_repeater_cfg_type));
      usb_repeater_i2c_ctx[core_num].config.slave_address = USB_I2C_TI_REPEATER_SLAVE_ADDRESS_PRIMARY;
      break;

    default:
      g_repeater_tuning_cfg_handle = NULL;
      g_repeater_tuning_size = 0;
  }
}


// ===========================================================================
/**
 * @function    usb_repeater_is_tuning_allowed
 * 
 * @brief   This function returns boolean value whether repeater tuning is allowed
 *          or not for a given platform type
 * 
 * @param   plat_type - usb_platform_ctx data type having platform type details.
 * 
 * @return  boolean - TRUE if tuning allowed for the platform, FALSE otherwise
 * 
 */
// ===========================================================================
static boolean usb_repeater_is_tuning_allowed (usb_platform_ctx plat_type)
{
  static boolean repeater_tune_allow;

  switch (plat_type.platform)
  {
    case DALPLATFORMINFO_TYPE_QRD:
    case DALPLATFORMINFO_TYPE_MTP:
    case DALPLATFORMINFO_TYPE_IDP:
    case DALPLATFORMINFO_TYPE_CDP:
    case DALPLATFORMINFO_TYPE_ATP:
      repeater_tune_allow = TRUE;
      break;

    default:
      repeater_tune_allow = FALSE;
  }
  return repeater_tune_allow;
}


// ===========================================================================
/**
 * @function    usb_repeater_init
 * 
 * @brief   This function start repeater driver
 * 
 * @param   core_num   -  which core repeater locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_repeater_init(uint8 core_num)
{

  i2c_status i2c_sts = I2C_SUCCESS;
  usb_platform_ctx plat_type = usb_shared_get_platform();
  if (core_num >= USB_I2C_CORE_NUM_MAX)
  {
    usb_shared_uart_log_error("usb_repeater_init, wrong input parameter:", core_num);
    return FALSE;
  }
  usb_shared_uart_log_error("usb_repeater_init", core_num);

  usb_shared_enable_repeater_support = usb_repeater_is_tuning_allowed(plat_type);
  if (usb_shared_enable_repeater_support)
  {
    usb_shared_uart_log_error("usb_repeater_init, tuning_allowed", usb_shared_enable_repeater_support);
    if (usb_repeater_i2c_ctx[core_num].i2c_handle != NULL)
    {
      usb_shared_uart_log_error("usb_repeater_init, already open:", core_num);
    }
    else
    {
      usb_i2c_ctx_init(&usb_repeater_i2c_ctx[core_num]);
      usb_repeater_get_tuning_cfg(core_num, plat_type);
    }

    i2c_sts = i2c_open(usb_repeater_i2c_ctx[core_num].instance, &usb_repeater_i2c_ctx[core_num].i2c_handle);
    if((I2C_SUCCESS != i2c_sts) || (usb_repeater_i2c_ctx[core_num].i2c_handle == NULL))
    {
      usb_shared_uart_log_error("usb_repeater_init, Failed open:", i2c_sts);  
      return FALSE;
    }
    usb_repeater_phy_tune(core_num, 0);
  }  
  return FALSE;
}

// ===========================================================================
/**
 * @function    usb_repeater_phy_tune
 * 
 * @brief   This function start repeater driver
 * 
 * @param   core_num   -  which core repeater locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_repeater_phy_tune(uint8 core_num, uint8 usb_mode)
{
  boolean result = FALSE;
  result = usb_repeater_process_cfg_reg_array(g_repeater_tuning_cfg_handle, 0, g_repeater_tuning_size, core_num);
  if (FALSE == result)
  {
    usb_shared_uart_log_error("usb_repeater_phy_tune failed", result);
    return FALSE;
  }
  return TRUE;  
}

// ===========================================================================
/**
 * @function    usb_repeater_reset
 * 
 * @brief   This function reset repeater driver
 * 
 * @param   core_num   -  which core repeater locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_repeater_reset(uint8 core_num)
{
  if (core_num >= USB_I2C_CORE_NUM_MAX)
  {
    usb_shared_uart_log_error("usb_repeater_reset, wrong input parameter:", core_num);
    return FALSE;
  }
  usb_shared_uart_log_error("usb_repeater_reset", core_num);
  return TRUE;
}

