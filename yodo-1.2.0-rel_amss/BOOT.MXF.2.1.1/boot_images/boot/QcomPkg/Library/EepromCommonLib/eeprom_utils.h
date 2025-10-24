#ifndef __EEPROM_UTILS__H
#define __EEPROM_UTILS__H
/**********************************************************************
 * eeprom_utils.h
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
#include "eeprom_api.h"
#include "eeprom_core.h"

// Allocate an array to hand out handles
#define MAX_EEPROM_OPEN_HANDLES        (EEPROM_DEVICE_ID_4 + 1)

/* Check for integer overflows */
#define INT_OVERFLOW(x,y) (x + y < x)

/**********************************************************
 * Logs error codes. Circular log buffer. The err_index can be used
 * as the index to the most recent error code
 *
 * @param eeprom_err_log [IN]
 *   log buffer
 *
 * @param code [IN]
 *   Error code
 *
 **********************************************************/
void eeprom_log (eeprom_logs_t *eeprom_err_log, uint16 code);

/**********************************************************
 * Eeprom delay in uint of micro seconds
 *
 * @param usec_delay [IN]
 *   Number of micro seconds delay.
 *
 **********************************************************/
void eeprom_udelay (uint32 usec_delay);

/**********************************************************
 * Validates the passed in client's handle
 *
 * @param parti_handle [IN]
 *   EEPROM interface handle to the partition
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
EEPROM_STATUS eeprom_handle_validation(eeprom_handle_t handle);

/**********************************************************
 * Validates the Read/Write input parameters
 *
 * @param parti_handle [IN]
 *   EEPROM interface handle
 *
 * @param byte_offset [IN]
 *   Byte offset from the start of the partition/image.
 *
 * @param byte_count [IN]
 *   Number of bytes to perform the read/write operations.
 *
 * @buffer [IN]
 *   Data buffer for the read/write operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
EEPROM_STATUS eeprom_rw_parameters_validation (eeprom_handle_t handle,
                uint32 byte_offset, uint32 byte_count, void *buffer);

#endif /* __EEPROM_UTILS__H */
