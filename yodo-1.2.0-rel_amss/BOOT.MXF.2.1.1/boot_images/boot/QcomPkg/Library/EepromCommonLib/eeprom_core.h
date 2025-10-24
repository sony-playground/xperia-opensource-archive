#ifndef __EEPROM_CORE__H
#define __EEPROM_CORE__H
/**********************************************************************
 * eeprom_core.h
 *
 * This file provides definitions for the eeprom support functions
 *
 * Copyright (c) 2020 Qualcomm Technologies Inc.
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
 * 09-10-2020   eo      Initial version
 *=======================================================================*/
#include <stdbool.h>
#include "eeprom_config.h"

/** EEPROM Core operation status */
#define EEPROM_CORE_DONE                  0  /**< Operation passed */
#define EEPROM_CORE_FAIL                (-1) /**< Operation failed */
#define EEPROM_CORE_NOT_SUPPORTED       (-2) /**< Device/operation not supported */
#define EEPROM_CORE_INVALID_PARAMETER   (-3) /**< API parameters invalid */

typedef int EEPROM_CORE_STATUS;              /**< Error status values used in EEPROM driver */

#define BIT_0  0x1
#define BIT_1  0x2
#define BIT_2  0x4
#define BIT_3  0x8
#define BIT_4  0x10
#define BIT_5  0x20
#define BIT_6  0x40
#define BIT_7  0x80

/*Default 64 bytes per page */
#define PAGE_SIZE_IN_BYTES   32

/* Check for integer overflows */
#define INT_OVERFLOW(x,y) (x + y < x)

#define EEPROM_ERR_LOG_SIZE  16

/* Flash Error Log */
typedef struct 
{
  uint8  eeprom_err_index;
  uint16 eeprom_err_codes[EEPROM_ERR_LOG_SIZE];
  uint32 read_unaligned_count;
  uint32 write_unaligned_count;
  uint32 eeprom_status;
} eeprom_logs_t;

typedef struct eeprom_dev_info
{
  boolean              eeprom_init_done;
  uint8				   ref_count;
  eeprom_cfg_params_t *config_params;
} eeprom_dev_info_t;

typedef struct eeprom_drv_info
{
  boolean              init_done;
  eeprom_logs_t        debug_log;
  eeprom_dev_info_t   *eeprom_dev;
} eeprom_drv_info_t;

extern eeprom_drv_info_t eeprom_drv;

#ifndef TRUE
#define TRUE   1   /* Boolean true value. */
#endif

#ifndef FALSE
#define FALSE  0   /* Boolean false value. */
#endif

#ifndef NULL
#define NULL  0
#endif

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
 *   Data buffer for eeprom write operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
EEPROM_CORE_STATUS eeprom_core_write(eeprom_dev_info_t *eeprom_dev, uint32 address,
                                          uint32 byte_count, uint8 *buffer);

/**********************************************************
 * Allows read data from the eeprom.
 *
 * @param address [IN]
 *   Physical location of the start of the read
 *
 * @param byte_count [IN]
 *   Number of bytes to read data.
 *
 * @buffer [IN]
 *   Data buffer for eeprom read operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
EEPROM_CORE_STATUS eeprom_core_read(eeprom_dev_info_t *eeprom_dev, uint32 address,
                                         uint32 byte_count, uint8 *buffer);

/**********************************************************
 * Initializes the eeprom controller HW
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
EEPROM_CORE_STATUS eeprom_controller_init (eeprom_cfg_params_t *eeprom_cfg, bool do_init);

/**********************************************************
 * Initializes the eeprom driver.
 * Invokes eeprom_core_init() to initialize eeprom sub modules
 *
 * @param eeprom_cfg_params [IN]
 *   RAM table containing config data for supported eeprom devices
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
EEPROM_STATUS eeprom_init (struct eeprom_cfg_params *eeprom_cfg, eeprom_dev_info_t *eeprom_dev);

/**********************************************************
 * De-initialize the client's handle in the eeprom driver. Close
 * i2c driver and free up resources used by the eeprom driver
 * if no client handles are opened.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
**********************************************************/
EEPROM_STATUS eeprom_deinit (eeprom_dev_info_t *eeprom_dev);

#endif /* __EEPROM_CORE__H */
