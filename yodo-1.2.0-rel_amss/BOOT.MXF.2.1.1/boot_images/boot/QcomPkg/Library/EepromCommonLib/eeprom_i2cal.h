#ifndef __EEPROM_I2CAL__H
#define __EEPROM_I2CAL__H
/**********************************************************************
 *eeprom_i2cal.h
 *
 * This file provides an interface to i2c buses driver
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
 * 07-08-2022   ss      Added i2c instance in I3c parameters
 * 09-10-2020   eo      Initial version
 *=======================================================================*/
#include <stdbool.h>
#include "com_dtypes.h"

#define EEPROM_I2C_DONE                  0  /**< Operation passed */
#define EEPROM_I2C_FAIL                (-1) /**< Operation failed */
#define EEPROM_I2C_NOT_SUPPORTED       (-2) /**< Device/operation not supported */
#define EEPROM_I2C_INVALID_PARAMETER   (-3) /**< API parameters invalid */

struct i2c_init_params
{
  uint32   freq_khz;
  uint32   slave_address;
  uint32   i2c_instance;
};

typedef int EEPROM_I2C_STATUS;

typedef enum
{
   i2c_read_mode = 1,
   i2c_write_mode = 2,
} I2C_COMMAND_TYPE;

/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/

EEPROM_I2C_STATUS i2cal_init(struct i2c_init_params init_params, bool do_init);
EEPROM_I2C_STATUS i2cal_deinit(void);
EEPROM_I2C_STATUS i2cal_transfer(I2C_COMMAND_TYPE cmd_mode, struct i2c_init_params init_params,
	                                 uint32_t addr, uint8 *reg_value, uint32 len );

#endif /* __EEPROM_I2CAL__H */
