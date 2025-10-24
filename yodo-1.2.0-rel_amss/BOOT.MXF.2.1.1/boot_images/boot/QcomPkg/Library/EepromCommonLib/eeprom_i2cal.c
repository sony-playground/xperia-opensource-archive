/**********************************************************************
 * eeprom_i2cal.c
 *
 * This file implements function to interface spinor driver with qspi buses driver
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
 * 07-08-2022   ss      Added Support to Fetch I2C instance from DT
 * 09-10-2020   eo      Initial version
 *=======================================================================*/
#include "eeprom_utils.h"
#include "eeprom_config.h"
#include "eeprom_osal.h"
#include <api/systemdrivers/busywait.h>
#include "i2c_api.h"
#include "eeprom_core.h"
#include "eeprom_i2cal.h"


#define I2C_BUS_READ_TIMEOUT_IN_MS  2500
#define I2C_BUS_WRITE_TIMEOUT_IN_MS 2500

typedef struct i2c_config_params
{
  i2c_instance         id;
  void                *i2c_handle;
  uint32               read_timeout;
  uint32               write_timeout;
  i2c_slave_config     cfg;
} i2c_config_params_type;

i2c_config_params_type i2c_params;

EEPROM_I2C_STATUS i2cal_init(struct i2c_init_params init_params, bool do_init)
{
  EEPROM_I2C_STATUS status = EEPROM_I2C_DONE;
  i2c_status         i2c_result;
  
  if (do_init)
  {
    /* Zero initialize memory. */
    memset(&i2c_params, 0, sizeof(i2c_params));
  }

  i2c_params.id = init_params.i2c_instance;
  i2c_params.read_timeout  = I2C_BUS_READ_TIMEOUT_IN_MS;
  i2c_params.write_timeout = I2C_BUS_WRITE_TIMEOUT_IN_MS;
  
  /* i2c bus config parameters */
  i2c_params.cfg.bus_frequency_khz  = init_params.freq_khz;  
  i2c_params.cfg.slave_address      = init_params.slave_address;
  
  //i2c_params.cfg.slave_address_type = I2C_07_BIT_SLAVE_ADDRESS;  // TOdo Need to check with buses team

  if (i2c_params.i2c_handle == NULL)
  {
    i2c_result = i2c_open (i2c_params.id, &i2c_params.i2c_handle);
    if (i2c_result != I2C_SUCCESS)
    {
      status = EEPROM_I2C_FAIL;
      eeprom_log (&eeprom_drv.debug_log, 0x485);
    }
  }

  return status;
}


EEPROM_I2C_STATUS i2cal_deinit(void)
{
  EEPROM_I2C_STATUS status = EEPROM_I2C_DONE;

  if (i2c_params.i2c_handle == NULL)
  {
    status = EEPROM_I2C_FAIL;
    eeprom_log (&eeprom_drv.debug_log, 0x485);
    goto done;
  }
  	
  (void) i2c_close (i2c_params.i2c_handle);

done:
  return status;
}

EEPROM_I2C_STATUS i2cal_transfer(I2C_COMMAND_TYPE cmd_mode, struct i2c_init_params init_params, 
                                     uint32_t addr, uint8 *reg_value, uint32 len )
{
  EEPROM_I2C_STATUS  status = EEPROM_I2C_DONE;
  uint16             mem_addr, buf_len;
  i2c_status         i2c_result;
  uint32             bytes_written = 0, bytes_read = 0;

  if ((cmd_mode != i2c_read_mode) && (cmd_mode != i2c_write_mode))
  {
    status = EEPROM_I2C_FAIL;
    eeprom_log (&eeprom_drv.debug_log, 0x490);
    goto done;
  }

  i2c_params.cfg.bus_frequency_khz  = init_params.freq_khz;  
  i2c_params.cfg.slave_address      = init_params.slave_address;
  
  mem_addr = (uint16)addr;
  buf_len  = (uint16)len;
  
  if (cmd_mode == i2c_read_mode)
  {
    i2c_result = i2c_read (i2c_params.i2c_handle, &i2c_params.cfg, mem_addr, 2, 
		                   reg_value, buf_len, &bytes_read, i2c_params.read_timeout);
    if (i2c_result == I2C_SUCCESS)
    {
      if (bytes_read != buf_len)
      {
        status = EEPROM_I2C_FAIL;
        eeprom_log (&eeprom_drv.debug_log, 0x495);
      }
    }
    else
    {
      status = EEPROM_I2C_FAIL;
      eeprom_log (&eeprom_drv.debug_log, 0x500);
    }
  }
  else /* cmd_mode is write */
  {
    i2c_result = i2c_write (i2c_params.i2c_handle, &i2c_params.cfg, mem_addr, 2,
		                    reg_value, buf_len, &bytes_written, i2c_params.write_timeout);
    if (i2c_result == I2C_SUCCESS)
    {
      if (bytes_written != buf_len)
      {
        status = EEPROM_I2C_FAIL;
        eeprom_log (&eeprom_drv.debug_log, 0x505);
      }
    }
    else
    {
      status = EEPROM_I2C_FAIL;
      eeprom_log (&eeprom_drv.debug_log, 0x50A);
    }
  }

done:

  return status;
}

