/*=======================================================================*//**
 * @file        UsbRedriver.c
 * @author:     pohanw
 * @date        09-Sep-2021
 *
 * @brief       USB common & shared USB core implementation for redriver Library.
 *
 * @details     This file contains sequence to enable redriver.
 *
 * @note        
 *
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2021 Qualcomm Technologies, Inc. All rights reserved.
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
#include "UsbSharedLib.h"


#if USB_ONSEMI_REDRIVER_FLAG
usb_i2c_ctx_type usb_redriver_i2c_ctx[USB_I2C_CORE_NUM_MAX];

// SMB1355 mounted on I2C instance 021, but since SBL sequence start from 1, 
// so here it is 022 instead 021
#define USB_I2C_RETIMER_INSTANCE_PRIMARY                        (I2C_INSTANCE_006)
#define USB_I2C_RETIMER_SLAVE_ADDRESS_PRIMARY                   (0x1c)

typedef struct 
{
  uint8  reg;
  uint8  data;
} usb_redriver_cfg_type;


#define ONSEMI_GENERAL_DEVICE_SETTING_REG 0x00
// 7   Channel D enable
// 6   Channel C Enable
// 5   Channel B Enable
// 4   Channel A Enable
// 3:1 operation modes:
//      101= Two ports of USB 3.2 Gen1/Gen2 (Default)
//           Channel A: USB 3.2 RX
//           Channel B: USB3.2 TX
//           Channel C: USB3.2 TX
//           Channel D: USB3.2 RX
// 0   Chip Enable Control
#define ONSEMI_OPERATION_USB_MODE 0xFB

// 3:1 operation modes:
//      010= Four lanes of DisplayPort
//        Channel A: DP Lane
//        Channel B: DP Lane
//        Channel C: DP Lane
//        Channel D: DP Lane
#define ONSEMI_OPERATION_DP_MODE 0xF5

// 3:1 operation modes:
//      000= Two lanes of DisplayPort + One port of USB 3.2 Gen1/Gen2
//        Channel A: USB 3.2 RX
//        Channel B: USB 3.2 TX
//        Channel C: DP Lane
//        Channel D: DP Lane
#define ONSEMI_OPERATION_USB_DP_MODE 0xF1


static const usb_redriver_cfg_type ONSEMI_REDRIVER_TUNING_CFG[] = 
{
  //in V1 the reset value change to 0x0, but to keep compa with V0 chip, write 0xD within 100 ms of releasing RESETN 
  {ONSEMI_GENERAL_DEVICE_SETTING_REG, 0x00},  // General Device Settings //Disable ALL
  {0x01, 0x08},  // Channel A Equalization Settings
  {0x18, 0x03},  // Channel A Flat Gain
  {0x02, 0x07},  // Channel A Output -1dB Compression & Polarity Settings
  {0x19, 0x01},  // Channel A Loss Profile Matching Control
  {0x03, 0x08},  // Channel B Equalization Settings
  {0x1a, 0x01},  // Channel B Flat Gain Settings
  {0x04, 0x07},  // Channel B Output -1dB Compression & Polarity Settings
  {0x1b, 0x03},  // Channel B Loss Profile Matching Control
  {0x05, 0x08},  // Channel C Equalization Settings
  {0x1c, 0x01},  // Channel C Flat Gain Settings
  {0x06, 0x07},  // Channel C Output -1dB Compression & Polarity Settings
  {0x1d, 0x03},  // Channel C Loss Profile Loss Matching Control
  {0x07, 0x08},  // Channel D Equalization Settings
  {0x1e, 0x03},  // Channel D Flat Gain Settings
  {0x08, 0x07},  // Channel D Output -1dB Compression & Polarity Settings
  {0x1f, 0x01},  // Channel D Loss Profile Matching Control, USB State Machine & DP Channel Direction
};

static const uint32 onsemi_redriver_tuning_size   = (sizeof(ONSEMI_REDRIVER_TUNING_CFG)       /sizeof(usb_redriver_cfg_type));



// ===========================================================================
/**
 * @function    usb_driver_process_cfg_reg_array
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
static boolean usb_redriver_process_cfg_reg_array
(
  const usb_redriver_cfg_type*  cfg_table,
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
    result = usb_shared_i2c_write(&usb_redriver_i2c_ctx[core_num], cfg_table[index].reg, cfg_table[index].data, 8);
    if (FALSE == result)
      return FALSE;
  }
  return TRUE;
}


volatile boolean usb_shared_enable_redriver_support = FALSE;

// ===========================================================================
/**
 * @function    usb_redriver_init
 * 
 * @brief   This function start redriver driver
 * 
 * @param   core_num   -  which core redriver locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_redriver_init(uint8 core_num)
{
  i2c_status i2c_sts = I2C_SUCCESS;
  usb_platform_ctx platform = usb_shared_get_platform();
  if (core_num >= USB_I2C_CORE_NUM_MAX)
  {
    usb_shared_uart_log_error("usb_redriver_init, wrong input parameter:", core_num);
    return FALSE;
  }

  if (( usb_shared_enable_redriver_support)
    && (platform.platform== DALPLATFORMINFO_TYPE_QRD))
  {
    //usb_shared_uart_log_error("usb_redriver_init, core ", core_num);

    if (usb_redriver_i2c_ctx[core_num].i2c_handle != NULL)
    {
      usb_shared_uart_log_error("usb_redriver_init, already open:", core_num);
    }
    else
    {
      usb_i2c_ctx_init(&usb_redriver_i2c_ctx[core_num]);
      usb_redriver_i2c_ctx[core_num].instance= USB_I2C_RETIMER_INSTANCE_PRIMARY;
      usb_redriver_i2c_ctx[core_num].config.slave_address = USB_I2C_RETIMER_SLAVE_ADDRESS_PRIMARY;
    }

    i2c_sts = i2c_open(usb_redriver_i2c_ctx[core_num].instance, &usb_redriver_i2c_ctx[core_num].i2c_handle);
    if((I2C_SUCCESS != i2c_sts) || (usb_redriver_i2c_ctx[core_num].i2c_handle == NULL))
    {
      usb_shared_uart_log_error("usb_redriver_init, Failed open:", i2c_sts);  
      return FALSE;
    }
  }  
  return TRUE;
}

// ===========================================================================
/**
 * @function    usb_redriver_set_usb_mode
 * 
 * @brief   This function set usb mode for redriver
 * 
 * @param   core_num   -  which core redriver locate
 * @param   usb_mode   -  which mode usb should set to.
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_redriver_set_usb_mode(uint8 core_num, uint8 usb_mode)
{
  boolean result = FALSE;
  if ((core_num >= USB_I2C_CORE_NUM_MAX) || (usb_mode >=USB4_MODE_TYPE_MAX))
  {
    usb_shared_uart_log_error("usb_redriver_init, wrong input parameter:", usb_mode);
    return FALSE;
  }

  if (NULL == usb_redriver_i2c_ctx[core_num].i2c_handle)
  {
    if (FALSE == usb_redriver_init(core_num))
    {
      return FALSE;
    }
  }
    
  result = usb_redriver_process_cfg_reg_array(ONSEMI_REDRIVER_TUNING_CFG,0,onsemi_redriver_tuning_size,core_num);

    if (FALSE == result)
    {
      return FALSE;
    }
    switch (usb_mode)
    {
      case USB4_MODE_TYPE_USB3:
        result = usb_shared_i2c_write(&usb_redriver_i2c_ctx[core_num], ONSEMI_GENERAL_DEVICE_SETTING_REG, ONSEMI_OPERATION_USB_MODE, 8);
        break;
      case USB4_MODE_TYPE_USB3DP:
        result = usb_shared_i2c_write(&usb_redriver_i2c_ctx[core_num], ONSEMI_GENERAL_DEVICE_SETTING_REG, ONSEMI_OPERATION_USB_DP_MODE, 8);
        break;
      case USB4_MODE_TYPE_DP4LANE:
        result = usb_shared_i2c_write(&usb_redriver_i2c_ctx[core_num], ONSEMI_GENERAL_DEVICE_SETTING_REG, ONSEMI_OPERATION_DP_MODE, 8);      
        break;
      default:
        usb_shared_uart_log_error("usb_redriver_set_usb_mode, unsupported mode:", usb_mode); 
        result = usb_shared_i2c_write(&usb_redriver_i2c_ctx[core_num], ONSEMI_GENERAL_DEVICE_SETTING_REG, ONSEMI_OPERATION_USB_MODE, 8);
    }
    return result;
}

#endif
