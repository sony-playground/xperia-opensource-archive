/**********************************************************************
 * spinor_init_config.c
 *
 * Implementation of passing RAM data table from other boot environments
 * to spinor driver
 *
 * Copyright (c) 2017-2018,2020-2022
 * Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*=======================================================================
                        Edit History


when        who  what, where, why
----------  ---  ---------------------------------------------------
2022-04-13  sc   Remove unused variable.
2021-10-06  sa   Change Winbond frequency from 75Mhz to 50Mhz.
2021-02-09  sa   Enabled DDR/DTR mode.
2020-11-11  wek  Add support for Winbond W25Q521NW
2020-10-09  wek  Remove unused fields in the structure.
2018-03-29  wek  Add support for Macronix MX25U51245G
2017-05-25  md   Initial Release


======================================================================*/
#include "spinor_init_config.h"
#include <string.h>


static spinor_config_data spinor_nor_entries[];


static spinor_init_config_table_type spinor_cfg_table =
{
  .magic_no = SPINOR_INIT_TABLE_MAGIC_NUMBER,
  .total_entries = 6,
  .version_no =SPINOR_INIT_TABLE_VERSION_NUMBER,
  .spinor_config_entries = spinor_nor_entries,

};


static spinor_config_data spinor_nor_entries[] =
{
  { /* Macronix MX25U51245G */
    .magic_number = 0xFACEECAF,
    .addr_bytes = 4,
    .erase_status_polling_ms = 1, /* not part related */
    .write_status_polling_usec = 100, /* not part related */
    .freq_khz = 50000, /* Spec supports max 50k */
    .device_id = 0x003A25C2, /* This changes with each new part, command 9F*/
    .dma_enable = TRUE,
  },
  { // Winbond W25Q521NW. 64MB
    .magic_number = 0xFACEECAF,
    .addr_bytes = 4,
    .read_ddr_wait_state = 8,
    .erase_status_polling_ms = 1,
    .write_status_polling_usec = 100,
    .freq_khz = 50000,
    .device_id = 0x002060EF,
    .dma_enable = TRUE,
  },
/*
  { // Winbond W25Q256JW. 32MB
    .magic_number = 0xFACEECAF,
    .addr_bytes = 4,
    .erase_status_polling_ms = 5,
    .write_status_polling_usec = 100,
    .freq_khz = 100000,
    .device_id = 0x001960EF,
    .power_on_delay_in_100us = 8,
    .dma_enable = TRUE,
  },
  { // Micron MT25QU256ABA8ESF. 32MB
    .magic_number = 0xFACEECAF,
    .addr_bytes = 4,
    .erase_status_polling_ms = 5,
    .write_status_polling_usec = 100,
    .freq_khz = 166000,
    .device_id = 0x0019BB20,
    .power_on_delay_in_100us = 8,
    .dma_enable = TRUE,
  },
  { // Micron MT25QU256AB. 256MB
    .magic_number = 0xFACEECAF,
    .addr_bytes = 4,
    .erase_status_polling_ms = 5,
    .write_status_polling_usec = 100,
    .freq_khz = 166000,
    .device_id = 0x0020BB20,
    .power_on_delay_in_100us = 8,
    .dma_enable = TRUE,
  },
  {  // Micron MT25QU512ABA. 512MB
    .magic_number = 0xFACEECAF,
    .addr_bytes = 4,
    .erase_status_polling_ms = 5,
    .write_status_polling_usec = 100,
    .freq_khz = 166000,
    .device_id = 0x0020BA20,
    .power_on_delay_in_100us = 8,
    .dma_enable = TRUE,
  },
  */
};



/**********************************************************
 * Get the pointer to the supported NOR devices and their parameters
 *
 * @return void* [OUT]
 *   Pointer to the table that contains the Flash's NOR config parameters
 *   needed for spinor operations
 *
 **********************************************************/
void* spinor_get_config_entries_struct(void)
{
  return (void *)&spinor_nor_entries[0];
}

/**********************************************************
 * Get the number of entries in the table
 *
 * @param total_nor_entries [OUT]
 *   Total number of entries in the table
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_get_config_entries_count(uint32 *total_nor_entries)
{
  uint32 total_entries;

  total_entries = (sizeof(spinor_nor_entries) /
                   sizeof(spinor_nor_entries[0]));

  *total_nor_entries = total_entries;

  return SPINOR_DEVICE_DONE;
}


/**********************************************************
 * Get the pointer to the supported NOR devices and their parameters
 *
 * @return void* [OUT]
 *   Pointer to the table that contains the Flash's NOR config parameters
 *   needed for spinor operations
 *
 **********************************************************/
void* spinor_get_config_table_struct(void)
{
  return (void *)&spinor_cfg_table;
}


