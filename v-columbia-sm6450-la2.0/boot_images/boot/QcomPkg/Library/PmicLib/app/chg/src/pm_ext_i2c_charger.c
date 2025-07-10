/*! \file
*  
*  \brief  pm_ext_i2c_charger.c
*  \details Implementation file for external I2C charger chip.
*    
*  &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/06/22   xp      Creation
===========================================================================*/

#include "pm_ext_i2c_charger.h"
#include "pm_app_chg.h"
#include "pm_dt_parser.h"
#include "pm_dt.h"
#include "pm_log_utils.h"
#include "pm_utils.h"
#include "i2c_api.h"

#define I2C_TIMEOUT_MAX 2500
#define BQ25790_RERUN_APSD_OFFSET (0x11)
#define BQ25790_RERUN_APSD_DATA (0xC0)
#define BQ25790_SLAVE_ADDRESS (0x6B)
#define BQ25790_BUS_FREQ_KHZ (100)


pm_err_flag_type
pm_ext_i2c_charger_rerun_apsd(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *pm_charger_dt_config = pm_get_charger_dt_config();

  if((NULL != pm_charger_dt_config) &&
     (TRUE == pm_charger_dt_config->bq25790_enable))
  {
    // Initialize for i2c of 3rd party charger
    void* i2c_handle = NULL;
    boolean i2c_opened = FALSE;
    i2c_status status = I2C_SUCCESS;
    i2c_slave_config config =
    {
      .bus_frequency_khz = BQ25790_BUS_FREQ_KHZ,
      .slave_address = BQ25790_SLAVE_ADDRESS,
      .mode = I2C,
      .slave_max_clock_stretch_us = 500,
      .core_configuration1 = 0,
      .core_configuration2 = 0
    };
    i2c_instance instance = (i2c_instance)pm_charger_dt_config->bq25790_i2c_instance;

    do
    {
      status = i2c_open(instance, &i2c_handle);
      if(I2C_SUCCESS != status)
      {
        break;
      }

      i2c_opened = TRUE;

      uint8 offset = BQ25790_RERUN_APSD_OFFSET;
      uint8 value = BQ25790_RERUN_APSD_DATA;
      uint32 count = 0;
      status |= i2c_write(i2c_handle, &config, offset, sizeof(offset), &value, sizeof(value), &count, I2C_TIMEOUT_MAX);
    } while(FALSE);

    if(i2c_opened)
    {
      status |= i2c_close(i2c_handle);
    }

    if(I2C_SUCCESS != status)
    {
      err_flag |= PM_ERR_FLAG_FAILURE;
    }
  }

  return err_flag;
}


