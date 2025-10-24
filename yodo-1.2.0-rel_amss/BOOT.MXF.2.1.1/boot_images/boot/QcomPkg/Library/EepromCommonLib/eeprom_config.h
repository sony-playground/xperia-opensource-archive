#ifndef __EEPROM_CONFIG__H
#define __EEPROM_CONFIG__H
/**********************************************************************
 * eeprom_config.h
 *
 * EEPROM Configuration Parameters Header
 *
 * Copyright (c) 2020,2022 Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*======================================================================

                        EDIT HISTORY FOR MODULE

when         who     what, where, why
----------   ---     ------------------------------------------------
08-07-2022   ss      Added Instance to which EEPROM will talk to
09-10-2020   eo      Initial version
======================================================================*/
#include "com_dtypes.h"

#define EEPROM_DT_PATH_LEN 0x100

typedef struct eeprom_cfg_params
{
  uint8  device_name[32];             /* Device name string */
  uint32 device_id;                   /* eeprom device ID */
  uint32 block_count;                 /* Number of total blocks in device */
  uint32 pages_per_block;             /* Number of pages in a block */
  uint32 page_size_bytes;             /* Logical page size */
  uint32 wbuffer_size_bytes;          /* Write Buffer size in bytes */
  uint32 flags1;                      /* Device specific flags */
  uint32 clk;                         /* Device operating frequency in KHz*/
  uint32 base_address;                /* Device base address */
  uint8  eeprom_client_ref_count;     /* Keep track of how many clients have called eeprom_init() */
  uint32 i2c_instance;                /* Instance to which the I2c will talk to */
} eeprom_cfg_params_t;

/* Structure for eeprom device configuration parameters data */
struct eeprom_cfg_data
{
  uint32 num_devices;                   /* Number of devices */
  eeprom_cfg_params_t *dev_params;      /* Device param */
};

#define EEPROM_DEVICE_FLAG_CUST_HDR    0x1         /* Custom header */


/* Gets the configuration data associated with all supported eeprom devices */
void eeprom_get_configs (struct eeprom_cfg_data **cfg_data);

#endif /* __EEPROM_CONFIG__H */
