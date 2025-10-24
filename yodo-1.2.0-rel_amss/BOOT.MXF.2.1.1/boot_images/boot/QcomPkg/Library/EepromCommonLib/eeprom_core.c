/**********************************************************************
 * eeprom_core.c
 *
 * Implementation of eeprom driver
 *
 * Copyright (c) 2020,2022 Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 *
 * when         who     what, where, why
 * ----------   ---     ------------------------------------------------
 * 07-08-2022   ss      Added I2C instance to be fetched from DT
 * 09-10-2020   eo      Initial version
 *=======================================================================*/
#include "eeprom_api.h"
#include "eeprom_core.h"
#include "eeprom_utils.h"
#include "eeprom_osal.h"
#include "eeprom_config.h"
#include "eeprom_i2cal.h"

eeprom_drv_info_t eeprom_drv;

/**********************************************************
 * Allows write data to the eeprom.
 *
 * @param address [IN]
 *   Physical location of the start of the write
 *
 * @param byte_count [IN]
 *   Number of bytes to write data.
 *
 * @buffer [IN]
 *   Data buffer for spinor write operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
EEPROM_CORE_STATUS eeprom_core_write (eeprom_dev_info_t *eeprom_dev, uint32 address,
                                           uint32 byte_count, uint8 *buffer)
{
  EEPROM_CORE_STATUS status = EEPROM_CORE_FAIL;
  uint32 transfer_size = 0;
  //uint32 total_bytes_written = 0;
  uint32 limit = eeprom_dev->config_params->page_size_bytes;
  I2C_COMMAND_TYPE command_mode = i2c_write_mode;
  struct i2c_init_params cfg;

  if (((uint64)buffer & 0x1F) || (byte_count & 0x3))
  {
    /* Keep a count of unalinged access for system analysis purpose */
    eeprom_drv.debug_log.write_unaligned_count++;
  }
  
  cfg.slave_address = eeprom_dev->config_params->base_address;
  cfg.freq_khz      = eeprom_dev->config_params->clk;

  while (byte_count)
  {
    /* In case the start address is not on page boundary, we write from the */
    /* start address to the end of the page as a separate write transaction */
    if (address % eeprom_dev->config_params->page_size_bytes)
    {
      transfer_size = eeprom_dev->config_params->page_size_bytes - (address % eeprom_dev->config_params->pages_per_block);
      if (transfer_size > byte_count)
      {
        transfer_size = byte_count;
      }
    }
    else
    {
      transfer_size = (byte_count > limit) ? (limit) : (byte_count);
    }

    /* Command | data addr | data buffer | length */
      if (EEPROM_I2C_DONE != i2cal_transfer(command_mode, cfg, address, buffer, transfer_size))
    {
      status = EEPROM_CORE_FAIL;
      eeprom_log (&eeprom_drv.debug_log, 0x222);
      goto eeprom_core_write_end;
    }

    //total_bytes_written += transfer_size;

    address += transfer_size;
    buffer += transfer_size;
    byte_count -= transfer_size;
  }

  status = EEPROM_CORE_DONE;

eeprom_core_write_end:
  return status;
}

/**********************************************************
 * Allows read data from the spinor.
 *
 * @param address [IN]
 *   Physical location of the start of the read
 *
 * @param byte_count [IN]
 *   Number of bytes to read data.
 *
 * @buffer [IN]
 *   Data buffer for spinor write operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
EEPROM_CORE_STATUS eeprom_core_read (eeprom_dev_info_t *eeprom_dev, uint32 address,
                                          uint32 byte_count, uint8 *buffer)
{
  EEPROM_CORE_STATUS status = EEPROM_CORE_DONE;
  uint32 max_transfer_size = 0;
  uint32 transfer_size = 0;
  uint8 *temp_buffer;
  I2C_COMMAND_TYPE command_mode = i2c_read_mode;
  struct i2c_init_params cfg;


  if (((uint64)buffer & 0x1F) || (byte_count & 0x3))
  {
    /* Keep a count of unalinged access for system analysis purpose */
    eeprom_drv.debug_log.read_unaligned_count++;
  }
  
  cfg.slave_address = eeprom_dev->config_params->base_address;
  cfg.freq_khz      = eeprom_dev->config_params->clk;

  /* The max transfer size is configurable by OEM when XIP is enabled. */
  /* When XIP is not enabled, read max transfer size is the memory size */
  max_transfer_size = eeprom_dev->config_params->wbuffer_size_bytes;

  temp_buffer = buffer;

  while (byte_count > 0)
  {
    transfer_size = (byte_count > max_transfer_size) ?
      max_transfer_size : byte_count;

    /* Command | data addr | data buffer | length */
      if (EEPROM_CORE_DONE != i2cal_transfer(command_mode, cfg, address, temp_buffer, transfer_size))
    {
      status = EEPROM_CORE_FAIL;
      eeprom_log (&eeprom_drv.debug_log, 0x231);
      goto eeprom_core_read_end;
    }

    address += transfer_size;
    byte_count -= transfer_size;
    temp_buffer = temp_buffer + transfer_size;
  }
eeprom_core_read_end:
  return status;
}

/* Local functions */
									 
/**********************************************************
 * Initializes the eeprom controller HW
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
EEPROM_CORE_STATUS eeprom_controller_init (eeprom_cfg_params_t *eeprom_cfg, bool do_init)
{
  EEPROM_CORE_STATUS status = EEPROM_CORE_DONE;
  struct i2c_init_params init;

  memset (&init, 0x0, sizeof(init));

  init.slave_address = eeprom_cfg->base_address;
  init.freq_khz      = eeprom_cfg->clk;
  init.i2c_instance  = eeprom_cfg->i2c_instance;
  
  /* Initialize the I2C buses driver */
  status = i2cal_init(init, do_init);
  if (status != EEPROM_CORE_DONE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x2C0);
  }

  return status;
}

/**********************************************************
 * Initializes the eeprom driver.
 * Invokes eeprom_controller_init() to initialize eeprom sub modules
 *
 * @param eeprom_cfg_params [IN]
 *   RAM table containing config data for supported eeprom devices
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
EEPROM_STATUS eeprom_init (eeprom_cfg_params_t *eeprom_cfg, 
                              eeprom_dev_info_t *eeprom_dev)
{
  EEPROM_STATUS status = EEPROM_DEVICE_FAIL;
  EEPROM_CORE_STATUS eeprom_status = EEPROM_I2C_FAIL;

  eeprom_dev->config_params = eeprom_cfg;

  if (eeprom_dev->config_params == NULL)
  {
    goto eeprom_init_end;
  }

  /* Give the spinor device POR reset delay before communicating with it */
  eeprom_udelay(10000);

  /* Intialize the Buses I2C driver */
  eeprom_status = eeprom_controller_init (eeprom_dev->config_params, !eeprom_dev->eeprom_init_done);
  if (eeprom_status != EEPROM_CORE_DONE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x2B3);
    goto eeprom_init_end;
  }

  if ((eeprom_dev->config_params->eeprom_client_ref_count > 0) &&
      (eeprom_dev->eeprom_init_done == TRUE))
  {
    /* eeprom_init has been done at least once */
    eeprom_dev->config_params->eeprom_client_ref_count++;
  }
  else
  {
    /* First time. Start keeping track of how many clients have called eeprom_init() */
    eeprom_dev->config_params->eeprom_client_ref_count = 1;
    eeprom_dev->eeprom_init_done = TRUE;
  }

  status = EEPROM_DEVICE_DONE;

eeprom_init_end: 
  return status;
}

/**********************************************************
 * De-initialize the client's handle in the eeprom driver. Close
 * i2c driver and free up resources used by the eeprom driver
 * if no client handles are opened.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
EEPROM_STATUS eeprom_deinit (eeprom_dev_info_t *eeprom_dev)
{
  uint8 i;
  EEPROM_STATUS status = EEPROM_DEVICE_FAIL;
  EEPROM_CORE_STATUS eeprom_status = EEPROM_CORE_DONE;

  if (eeprom_dev->eeprom_init_done == FALSE)
  {
    return EEPROM_DEVICE_FAIL;
  }

  /* check if multiple clients are using eeprom */
  if (eeprom_dev->config_params->eeprom_client_ref_count >= 2)
  {
    /* Multiple clients are using eeprom */
    eeprom_dev->config_params->eeprom_client_ref_count--;
    status = EEPROM_DEVICE_DONE;
    goto eeprom_deinit_end;
  }

  if (eeprom_dev->config_params->eeprom_client_ref_count == 0)
  {
	memset(eeprom_dev, 0, sizeof(eeprom_dev_info_t));
  }

  /* Check if need to close i2c driver handle */
  for (i = 0; i < MAX_EEPROM_OPEN_HANDLES; i++)
  {
    if (eeprom_drv.eeprom_dev[i].config_params->eeprom_client_ref_count != 0)
    {
      status = EEPROM_DEVICE_DONE;
      goto eeprom_deinit_end;
    }
  }
  
  eeprom_status = i2cal_deinit();
  if (eeprom_status != EEPROM_CORE_DONE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x2B3);
    goto eeprom_deinit_end;
  }
  eeprom_drv.init_done = FALSE;

  status = EEPROM_DEVICE_DONE;

eeprom_deinit_end:
  return status;
}
