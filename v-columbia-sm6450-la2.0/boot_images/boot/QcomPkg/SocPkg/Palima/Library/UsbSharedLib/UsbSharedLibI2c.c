/*=======================================================================*//**
 * @file        UsbSharedLibI2c.c
 * @author:     pmahajan
 * @date        30-Apr-2021
 *
 * @brief       USB common & shared USB core implementation for i2c Library.
 *
 * @details     This file contains sequence for i2c implementation for retimer.
 *
 * @note        
 *
 * 
*//*========================================================================*/
//============================================================================
/**
 *            Copyright 2020-2021 QUALCOMM Technologies Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
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
// 05/28/21     jaychoi  Update retimer sequence
// 04/30/21     jaychoi  Added support for B1 retimer
// 12/10/20     pohanw   Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------

// Below are required to read UEFI Variable
#include <Uefi.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include "qusb_log.h"
//#include "qusb_dci_common.h"
#include "UsbSharedLib.h"
#include "UsbSharedLibI2c.h"
//#include "HalusbHWIO.h"
//#include "DDITlmm.h"
//#include "DALSys.h"   // Required for DALSYS_InitMod for TLMM

//----------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------

#define USB_I2C_INSTANCE_DEFAULT                        (0xFF)
#define USB_I2C_SLAVE_ADDRESS_DEFAULT                   (0xFF)


#define USB_I2C_TIMEOUT_MAX                             (2500)
#define USB_I2C_FREQUENCY_KHZ                           (400)
#define USB_I2C_MAX_CLOCK_STRETCH_US                    (500)

// Allow 3 times retry for the scenario of slave NACKED.
#define USB_I2C_SLAVE_NACKED                            (1 << 3)
#define USB_I2C_RETRY_COUNT_MAX                         (3)


//----------------------------------------------------------------------------
// Static Functions
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Global Functions
//----------------------------------------------------------------------------
boolean usb_shared_i2c_write(usb_i2c_ctx_type* i2c_ctx, uint8 reg, uint8 data, uint8 reg_size)
{
  i2c_status status = I2C_SUCCESS;
  uint32 written_count = 0;
  uint8 byte_cnt = reg_size/8;
  
  if ((NULL == i2c_ctx) || (byte_cnt==0) || (byte_cnt>2))
  {
    usb_shared_uart_log_error("usb_shared_i2c_write, invalid parameter: ", reg_size);    
    return FALSE;
  }
  
  if(NULL == i2c_ctx->i2c_handle)
  {
    usb_shared_uart_log_error("usb_shared_i2c_write, not open 0x%x: ", 0);
    return FALSE;
  }
  
  status = i2c_write(i2c_ctx->i2c_handle, &(i2c_ctx->config), reg, byte_cnt, &data,
                      1, &written_count, USB_I2C_TIMEOUT_MAX);
  if (status != I2C_SUCCESS)

  {
    usb_shared_uart_log_error("usb_shared_i2c_write, write failed reg|data: ", reg<<16|data);
    return FALSE;
  }

  // Only enable for debugging as this prints 10s of lines to UART
  //usb_shared_uart_log_error("usb_shared_i2c_write, write reg|data: ", reg<<16|data);
  return TRUE;

}

boolean usb_shared_i2c_read(usb_i2c_ctx_type* i2c_ctx, uint8 reg, uint8 *buffer, uint8 reg_size)
{
  i2c_status status = I2C_SUCCESS;
  uint32 read_count = 0;
  uint8 byte_cnt = reg_size/8;
  
  if ((NULL == i2c_ctx) || (byte_cnt==0) || (byte_cnt>2))
  {
    usb_shared_uart_log_error("usb_shared_i2c_read, invalid parameter: ", (uint32)(uintptr_t)i2c_ctx);    
    return FALSE;
  }

  if(NULL == i2c_ctx->i2c_handle)
  {
    usb_shared_uart_log_error("usb_shared_i2c_read, Not Open:", (uint32)(uintptr_t)i2c_ctx->i2c_handle);    
    return FALSE;
  }

  status = i2c_read(i2c_ctx->i2c_handle, &(i2c_ctx->config), reg, byte_cnt, buffer,
                      1, &read_count, USB_I2C_TIMEOUT_MAX);
  
  if (status != I2C_SUCCESS)

  {
    usb_shared_uart_log_error("usb_shared_i2c_read, read failed reg: ", reg);
    return FALSE;
  }
  return TRUE;
}



//============================================================================

/**
* @function usb_i2c_ctx_init
*
* @brief  API used to initialize the I2C Ctx
*
*/
//============================================================================
void usb_i2c_ctx_init(usb_i2c_ctx_type* i2c_ctx)
{
  
  if (NULL == i2c_ctx)
  {
    usb_shared_uart_log_error("usb_i2c_ctx_init, invalid parameter: ", 0);    
    return;
  }

  i2c_ctx->i2c_handle = NULL;
  i2c_ctx->instance = USB_I2C_INSTANCE_DEFAULT;

  i2c_ctx->config.bus_frequency_khz = USB_I2C_FREQUENCY_KHZ;
  i2c_ctx->config.slave_max_clock_stretch_us = USB_I2C_MAX_CLOCK_STRETCH_US;
  i2c_ctx->config.mode = I2C;
  i2c_ctx->config.core_configuration1 = 0;
  i2c_ctx->config.core_configuration2 = 0;
  i2c_ctx->config.slave_address = USB_I2C_SLAVE_ADDRESS_DEFAULT;  

}

