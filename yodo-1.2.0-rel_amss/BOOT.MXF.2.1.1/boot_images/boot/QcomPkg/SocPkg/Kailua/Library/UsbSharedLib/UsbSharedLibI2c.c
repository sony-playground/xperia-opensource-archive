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
#include "HalusbHWIO.h"
#include "DDITlmm.h"
#include "DALSys.h"   // Required for DALSYS_InitMod for TLMM

//----------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------
#define USB_I2C_TIMEOUT_MAX                             (2500)
#define USB_I2C_FREQUENCY_KHZ                           (400)
#define USB_I2C_MAX_CLOCK_STRETCH_US                    (500)

// SMB1355 mounted on I2C instance 021, but since SBL sequence start from 1, 
// so here it is 022 instead 021
#define USB_I2C_INSTANCE_DEFAULT                        (I2C_INSTANCE_022)
#define USB_I2C_PRI_SLAVE_ADDRESS_DEFAULT               (0x08)
#define USB_I2C_SEC_SLAVE_ADDRESS_DEFAULT               (0x0c)

// Allow 3 times retry for the scenario of slave NACKED.
#define USB_I2C_SLAVE_NACKED                            (1 << 3)
#define USB_I2C_RETRY_COUNT_MAX                         (3)

// USB1_PWR_3P3_EN
// HWIO_TLMM_GPIO_CFG27_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT27_OUT(0x2);
#define USB_SHARED_RETIMER_GPIO__USB1_PWR_3P3_EN        (27)

// USB1_RESET_N
// HWIO_TLMM_GPIO_CFG26_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT26_OUT(0x2);
#define USB_SHARED_RETIMER_GPIO__USB1_RESET_N           (26)

// Delay must be greater than or equal to 100us between PWR ON, RESET, and first i2c write
#define USB_SHARED_RETIMER_DELAY_US__USB1_PWR_TO_RESET  (200)

typedef struct 
{
  uint16 reg;
  uint8  data;
} qusb_i2c_cfg_type;

#if 0
static const qusb_i2c_cfg_type KB8001_RESET_CFG[] = 
{
  //in V1 the reset value change to 0x0, but to keep compa with V0 chip, write 0xD within 100 ms of releasing RESETN 
  { 0x0006,  (0x0F) }, // Mcx_reset 
  { 0x0006,  (0x0D) }, // Enable TWI
  
  { 0x5058, 0x12 },
  { 0x5059, 0x12 },
  { 0xFF63, 0x3C },
  { 0xF021, 0x02 },
  { 0xF022, 0x02 },
  { 0xF057, 0x02 },
  { 0xF058, 0x02 },
  { 0x8194, 0x37 },
  { 0xF0C9, 0x0C },
  { 0xF0CA, 0x0B },
  { 0xF0CB, 0x0A },
  { 0xF0CC, 0x09 },
  { 0xF0CD, 0x08 },
  { 0xF0CE, 0x07 },
  { 0xF0DF, 0x57 },
  { 0xF0E0, 0x66 },
  { 0xF0E1, 0x66 },
  { 0x8198, 0x33 },
  { 0x8191, 0x00 },
};
//KB8001 must be programmed to operate in USB3 mode at this time. Register settings for
//USB-C normal and flipped orientation are shown below:
static const qusb_i2c_cfg_type KB8001_USB3_LANEA_CFG[] = 
{
  { 0xF020, 0x2f },
  { 0xF056, 0x2f },
  //Normal orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};

static const qusb_i2c_cfg_type KB8001_USB3_LANEB_CFG[] = 
{
  { 0xF020, 0x2f },
  { 0xF056, 0x2f },

  { 0x0002,  (0x01) }, // mcx_orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};


//KB8001 must be programmed to operate in DisplayPort mode after a DisplayPort Configure
//Acknowledge message is received by the host. Register settings for USB-C normal and
//flipped orientation are shown below:
static const qusb_i2c_cfg_type KB8001_USB3DP_LANEA_CFG[] = 
{
  { 0xF2CB, 0x30 },
  { 0x0011, 0x00 },

  { 0x0001,  (0x01) }, // mcx_protocol
  { 0xF020, 0x2f },
  { 0xF056, 0x2f },

  { 0x0002,  (0x06) }, // mcx_orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};

static const qusb_i2c_cfg_type KB8001_USB3DP_LANEB_CFG[] = 
{
  { 0xF2CB, 0x30 },
  { 0x0011, 0x00 },

  { 0x0001,  (0x01) }, // mcx_protocol
  { 0xF020, 0x2f },
  { 0xF056, 0x2f },

  { 0x0002,  (0x07) }, // mcx_orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};

//KB8001 must be programmed to operate in DisplayPort mode after a DisplayPort Configure
//Acknowledge message is received by the host. Register settings for USB-C normal and
//flipped orientation are shown below:
static const qusb_i2c_cfg_type KB8001_DP4LN_LANEB_CFG[] = 
{
  { 0xF2CB, 0x30 },
  { 0x0011, 0x00 },

  { 0x0001,  (0x02) }, // mcx_protocol
  { 0x0002,  (0x07) }, // mcx_orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};

static const qusb_i2c_cfg_type KB8001_DP4LN_LANEA_CFG[] = 
{
  { 0xF2CB, 0x30 },
  { 0x0011, 0x00 },

  { 0x0001,  (0x02) }, // mcx_protocol
  { 0x0002,  (0x06) }, // mcx_orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};


//KB8001 must be programmed to operate in Thunderbolt mode after the Thunderbolt Enter
//Mode Acknowledge message is received by the host. Register settings for USB-C normal and
//flipped orientation are shown below:
static const qusb_i2c_cfg_type KB8001_TBT3_LANEA_CFG[] = 
{
  { 0xF26B, 0x01 },
  { 0xF26E, 0x19 },

  { 0x0001,  (0x03) }, // mcx_protocol
  { 0x0006,  (0x00) }, // mcx_reset 
};

static const qusb_i2c_cfg_type KB8001_TBT3_LANEB_CFG[] = 
{
  { 0xF26B, 0x01 },
  { 0xF26E, 0x19 },

  { 0x0001,  (0x03) }, // mcx_protocol
  { 0x0002,  (0x01) }, // mcx_orientation
  { 0x0005,  (0x02) }, // mcx_map_ctl 
  { 0x0006,  (0x00) }, // mcx_reset 
};

//KB8001 must be programmed to operate in Thunderbolt mode after the Thunderbolt Enter
//Mode Acknowledge message is received by the host. Register settings for USB-C normal and
//flipped orientation are shown below:
static const qusb_i2c_cfg_type KB8001_USB4_LANEA_CFG[] = 
{
  { 0xF26B, 0x01 },
  { 0xF26E, 0x19 },
  { 0x0001, 0x03 },

  { 0x0006,  (0x00) }, // mcx_reset 
};

static const qusb_i2c_cfg_type KB8001_USB4_LANEB_CFG[] = 
{
  { 0xF26B, 0x01 },
  { 0xF26E, 0x19 },
  { 0x0001, 0x03 },

  { 0x0002,  (0x01) }, // mcx_orientation
  { 0x0005,  (0x02) }, // mcx_map_ctl 
  { 0x0006,  (0x00) }, // mcx_reset 
};


static const uint32 kb8001_reset_cfg_size   = (sizeof(KB8001_RESET_CFG)       /sizeof(qusb_i2c_cfg_type));
static const uint32 kb8001_usb3_cfg_size    = (sizeof(KB8001_USB3_LANEA_CFG)  /sizeof(qusb_i2c_cfg_type));
static const uint32 kb8001_usb3dp_cfg_size  = (sizeof(KB8001_USB3DP_LANEA_CFG)/sizeof(qusb_i2c_cfg_type));
static const uint32 kb8001_dp4lane_cfg_size = (sizeof(KB8001_DP4LN_LANEA_CFG) /sizeof(qusb_i2c_cfg_type));
static const uint32 kb8001_tbt3_cfg_size    = (sizeof(KB8001_TBT3_LANEA_CFG)  /sizeof(qusb_i2c_cfg_type));
static const uint32 kb8001_usb4_cfg_size    = (sizeof(KB8001_USB4_LANEA_CFG)  /sizeof(qusb_i2c_cfg_type));
#endif
#define USB_RETIMER_CORE_NUM_MAX 2
static usb_i2c_ctx_type usb_i2c_ctx[USB_RETIMER_CORE_NUM_MAX];

//----------------------------------------------------------------------------
// Static Functions
//----------------------------------------------------------------------------

//============================================================================
/**
* @function  usb_shared_tlmm_gpio_high
*
* @brief For device mode: Configure GPIO high and enabled
*
* @Note : None
*
* @param  GPIO number 
*
* @return None
*
*/
//============================================================================
static void usb_shared_tlmm_gpio_high(uint32 gpio_number)
{  

  /*Handle to the DAL TLMM Device context.*/
  DalDeviceHandle   *tlmm_handle  = NULL;
  DALResult         result        = DAL_ERROR;

  /* Create a DAL-formatted GPIO configuration for */
  DALGpioSignalType config =
     (DALGpioSignalType)DAL_GPIO_CFG(
     gpio_number, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_2MA);
  
  /* Initialize DALSYS and attach to the DAL TLMM driver. */
  DALSYS_InitMod(NULL);
  result = DAL_DeviceAttach(DALDEVICEID_TLMM, &tlmm_handle);

  if((DAL_ERROR == result) || (tlmm_handle == NULL))
  {
    usb_shared_uart_log_error("tlmm: attach fail", result);
  }
  else
  {
    /* Configure the GPIO. */
    result = DalTlmm_ConfigGpio(tlmm_handle, config, DAL_TLMM_GPIO_ENABLE);
    if(DAL_SUCCESS != result)
    {
      usb_shared_uart_log_error("tlmm: config fail", result);
    }
    else
    {
      /* Drive the GPIO HIGH. */
      result = DalTlmm_GpioOut(tlmm_handle, config, DAL_GPIO_HIGH_VALUE);
      if(DAL_SUCCESS != result)
      {
        usb_shared_uart_log_error("tlmm: out fail", result);
      }
    }
    
    result = DAL_DeviceDetach(tlmm_handle);
    if(DAL_SUCCESS != result)
    {
      usb_shared_uart_log_error("tlmm: detach fail", result);
    }
  }
}

//----------------------------------------------------------------------------
// Global Functions
//----------------------------------------------------------------------------
boolean usb_shared_i2c_write(uint8 core_num, uint16 reg, uint8 data)
{
  i2c_status status = I2C_SUCCESS;
  uint32 written_count = 0;
  
  if ((core_num >= USB_RETIMER_CORE_NUM_MAX))
  {
    usb_shared_uart_log_error("usb_shared_i2c_write, invalid parameter: ", core_num);    
    return FALSE;
  }
  
  if(NULL == usb_i2c_ctx[core_num].i2c_handle)
  {
    usb_shared_uart_log_error("usb_shared_i2c_write, not open core_num: ", core_num);
    return FALSE;
  }
  
  status = i2c_write(usb_i2c_ctx[core_num].i2c_handle, &(usb_i2c_ctx[core_num].config), reg, 2, &data,
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

boolean usb_shared_i2c_read(uint8 core_num, uint16 reg, uint8 *buffer)
{
  i2c_status status = I2C_SUCCESS;
  uint32 read_count = 0;

  if ((NULL == buffer) || (core_num >= USB_RETIMER_CORE_NUM_MAX))
  {
    usb_shared_uart_log_error("usb_shared_i2c_read, invalid parameter: ", core_num);    
    return FALSE;
  }

  if(NULL == usb_i2c_ctx[core_num].i2c_handle)
  {
    usb_shared_uart_log_error("usb_shared_i2c_read, Not Open:", core_num);    
    return FALSE;
  }

  status = i2c_read(usb_i2c_ctx[core_num].i2c_handle, &(usb_i2c_ctx[core_num].config), reg, 2, buffer,
                      1, &read_count, USB_I2C_TIMEOUT_MAX);
  
  if (status != I2C_SUCCESS)

  {
    usb_shared_uart_log_error("usb_shared_i2c_read, read failed reg: ", reg);
    return FALSE;
  }
  return TRUE;
}

// ===========================================================================
/**
 * @function    usb_shared_lib_process_cfg_reg_array
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
static boolean usb_shared_lib_process_cfg_reg_array
(
  const qusb_i2c_cfg_type*  cfg_table,
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
    result = usb_shared_i2c_write(core_num, cfg_table[index].reg, cfg_table[index].data);
    if (FALSE == result)
      return FALSE;
  }
  return TRUE;
}



//============================================================================

/**
* @function usb_shared_kb8001_ctx_init
*
* @brief  API used to initialize the KB8001 I2C Ctx
*
*/
//============================================================================
void usb_kb8001_ctx_init(uint8 core_num)
{
  usb_i2c_ctx[core_num].i2c_handle = NULL;
  usb_i2c_ctx[core_num].instance = USB_I2C_INSTANCE_DEFAULT;

  usb_i2c_ctx[core_num].config.bus_frequency_khz = USB_I2C_FREQUENCY_KHZ;
  usb_i2c_ctx[core_num].config.slave_max_clock_stretch_us = USB_I2C_MAX_CLOCK_STRETCH_US;
  usb_i2c_ctx[core_num].config.mode = I2C;
  usb_i2c_ctx[core_num].config.core_configuration1 = 0;
  usb_i2c_ctx[core_num].config.core_configuration2 = 0;

  switch (core_num)
  {
    case USB_RETIMER_CORE_0:
      usb_i2c_ctx[core_num].config.slave_address = USB_I2C_PRI_SLAVE_ADDRESS_DEFAULT;  
      break;
    case USB_RETIMER_CORE_1:
      usb_i2c_ctx[core_num].config.slave_address = USB_I2C_SEC_SLAVE_ADDRESS_DEFAULT;  
      break;
    default:
      usb_i2c_ctx[core_num].config.slave_address = USB_I2C_PRI_SLAVE_ADDRESS_DEFAULT;  
  }
}


boolean usb_kb8001_reset(uint8 core_num)
{
  return TRUE; //usb_shared_lib_process_cfg_reg_array(KB8001_RESET_CFG,0,kb8001_reset_cfg_size,core_num);
}

boolean usb_shared_kb8001_deinit(uint8 core_num)
{
  i2c_status i2c_sts = I2C_SUCCESS;
  if (core_num >= USB_RETIMER_CORE_NUM_MAX)
  {
    usb_shared_uart_log_error("usb_shared_kb8001_deinit, wrong input parameter:", core_num);
    return FALSE;
  }
  if (usb_i2c_ctx[core_num].i2c_handle != NULL)
  {
    i2c_sts = i2c_close(usb_i2c_ctx[core_num].i2c_handle);
    if(I2C_SUCCESS == i2c_sts)
    {
      usb_i2c_ctx[core_num].i2c_handle = NULL;
    }
    else
    {
      usb_shared_uart_log_error("usb_shared_kb8001_deinit, failed close:", core_num);    
      return FALSE;
    }
  }
  return TRUE;
}

boolean usb_shared_is_retimer_force_dp4lane_enabled(void)
{
  EFI_STATUS                    Status      = EFI_SUCCESS;
  INT8                          UefiVar     = 0;
  UINTN                         UefiVarSize;
  
  static boolean usb_shared_force_dp4lane = FALSE;
  static boolean usb_shared_force_dp4lane_uefi_var_read = FALSE;

  if (FALSE == usb_shared_force_dp4lane_uefi_var_read)
  {
    usb_shared_force_dp4lane_uefi_var_read = TRUE;

    UefiVarSize = sizeof(UefiVar);
    Status = gRT->GetVariable(L"ForceUsb4RetimerDP4LANE", &gQcomTokenSpaceGuid, NULL, &UefiVarSize, &UefiVar);
    if(!EFI_ERROR(Status) && UefiVar) 
    {
      usb_shared_uart_log_error("USB Force USB4 Retimer DP4LANE Mode Enabled", UefiVar);
      usb_shared_force_dp4lane = TRUE;
    }
  }

  return usb_shared_force_dp4lane;
}


boolean usb_shared_kb8001_init(uint8 core_num, USB4_MODE_TYPE usb_mode, uint32 cc_lane)
{
  i2c_status i2c_sts = I2C_SUCCESS;
  boolean result = FALSE;
  if ((core_num >= USB_RETIMER_CORE_NUM_MAX) || (usb_mode >=USB4_MODE_TYPE_MAX) || (cc_lane >= QUSB_TYPE_C_NO_LANE))
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, wrong input parameter:", usb_mode);
    return FALSE;
  }

  if (usb_i2c_ctx[core_num].i2c_handle != NULL)
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, already open:", core_num);  
  }
  else
  {
    usb_kb8001_ctx_init(core_num);
  }

  if (cc_lane == 0)
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, LANE_A: core: ", core_num );
  }
  else
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, LANE_B: core: ", core_num );
  }
  #if 0
  if (core_num == 1)
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, enable GPIO core:", core_num);  

    usb_shared_tlmm_gpio_high(USB_SHARED_RETIMER_GPIO__USB1_PWR_3P3_EN);

    usb_shared_delay_us(USB_SHARED_RETIMER_DELAY_US__USB1_PWR_TO_RESET);
    
    usb_shared_tlmm_gpio_high(USB_SHARED_RETIMER_GPIO__USB1_RESET_N);

    usb_shared_delay_us(USB_SHARED_RETIMER_DELAY_US__USB1_PWR_TO_RESET);
  }
#endif
  i2c_sts = i2c_open(usb_i2c_ctx[core_num].instance, &usb_i2c_ctx[core_num].i2c_handle);
  if((I2C_SUCCESS != i2c_sts) || (usb_i2c_ctx[core_num].i2c_handle == NULL))
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, Failed open:", i2c_sts);  
    return FALSE;
  }

#if 0
  result = usb_shared_lib_process_cfg_reg_array(KB8001_RESET_CFG,0,kb8001_reset_cfg_size,core_num);
  usb_shared_uart_log_error("KB8001_RESET_CFG", result);
  if (FALSE == result)
  {
    return FALSE;
  }
#endif
#if 0
  if (usb_shared_is_retimer_force_dp4lane_enabled())
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, force DP4LANE", cc_lane);  
    usb_mode = USB4_MODE_TYPE_DP4LANE;
  }
#endif
  usb_shared_uart_log_error("KB8001_lane:", cc_lane);
  usb_shared_uart_log_error("KB8001_mode:", usb_mode);

  if (cc_lane == QUSB_TYPE_C_LANE_B)
  {
    switch (usb_mode)
    {
#if 0
      case USB4_MODE_TYPE_USB3:
        result = usb_shared_lib_process_cfg_reg_array(KB8001_USB3_LANEB_CFG,0,kb8001_usb3_cfg_size,core_num);
        break;
      case USB4_MODE_TYPE_USB3DP:
        result = usb_shared_lib_process_cfg_reg_array(KB8001_USB3DP_LANEB_CFG,0,kb8001_usb3dp_cfg_size,core_num);
        break;
      case USB4_MODE_TYPE_DP4LANE:
        result = usb_shared_lib_process_cfg_reg_array(KB8001_DP4LN_LANEB_CFG,0,kb8001_dp4lane_cfg_size,core_num);
        break;
      case USB4_MODE_TYPE_TBT3:
        result = usb_shared_lib_process_cfg_reg_array(KB8001_TBT3_LANEB_CFG,0,kb8001_tbt3_cfg_size,core_num);
        break;
      case USB4_MODE_TYPE_USB4:
        result = usb_shared_lib_process_cfg_reg_array(KB8001_USB4_LANEB_CFG,0,kb8001_usb4_cfg_size,core_num);
        break;
#endif		
      default:
        result = FALSE;
    }
  }
  else
  {
    switch (usb_mode)
    {
#if 0
      case USB4_MODE_TYPE_USB3:
        result = usb_shared_lib_process_cfg_reg_array(KB8001_USB3_LANEA_CFG,0,kb8001_usb3_cfg_size,core_num);
        break;
      case USB4_MODE_TYPE_USB3DP:
        result = usb_shared_lib_process_cfg_reg_array(KB8001_USB3DP_LANEA_CFG,0,kb8001_usb3dp_cfg_size,core_num);
        break;
      case USB4_MODE_TYPE_DP4LANE:
        result = usb_shared_lib_process_cfg_reg_array(KB8001_DP4LN_LANEA_CFG,0,kb8001_dp4lane_cfg_size,core_num);
        break;
      case USB4_MODE_TYPE_TBT3:
        result = usb_shared_lib_process_cfg_reg_array(KB8001_TBT3_LANEA_CFG,0,kb8001_tbt3_cfg_size,core_num);
        break;
      case USB4_MODE_TYPE_USB4:
        result = usb_shared_lib_process_cfg_reg_array(KB8001_USB4_LANEA_CFG,0,kb8001_usb4_cfg_size,core_num);
        break;
#endif
      default:
        result = FALSE;
    }

  }

  return result;
}
