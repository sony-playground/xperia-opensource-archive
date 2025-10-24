/**********************************************************************
 * eeprom_utils.c
 *
 * Implementation of eeprom driver support functions
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
#include "eeprom_utils.h"
#include "eeprom_osal.h"
#include "eeprom_core.h"
#include <api/systemdrivers/busywait.h>

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
void eeprom_log (eeprom_logs_t *eeprom_err_log, uint16 code)
{
  if (eeprom_err_log->eeprom_err_index >= EEPROM_ERR_LOG_SIZE)
  {
    eeprom_err_log->eeprom_err_index = 0;
  }
  eeprom_err_log->eeprom_err_codes[eeprom_err_log->eeprom_err_index++] = code;
  return;
}

/**********************************************************
 * Eeprom delay in uint of micro seconds
 *
 * @param usec_delay [IN]
 *   Number of micro seconds delay.
 *
 **********************************************************/
void eeprom_udelay (uint32 usec_delay)
{
  busywait(usec_delay);
}

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
EEPROM_STATUS eeprom_handle_validation(eeprom_handle_t handle)
{
  uint8_t i;
  eeprom_dev_info_t *eeprom_dev = NULL;
  
  if (handle == NULL)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x320);
    return EEPROM_DEVICE_FAIL;
  }
  
  if (eeprom_drv.eeprom_dev == NULL)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x321);
    return EEPROM_DEVICE_FAIL;
  }
  	
  eeprom_dev = eeprom_drv.eeprom_dev;
  	
  for (i = 0; i <= MAX_EEPROM_OPEN_HANDLES; i++)
  {
    if (handle == eeprom_dev)
    {
      return EEPROM_DEVICE_DONE;
    }
	eeprom_dev++;
  }
  
  return EEPROM_DEVICE_FAIL;
}

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
               uint32 byte_offset, uint32 byte_count, void *buffer)
{
  EEPROM_STATUS status = EEPROM_DEVICE_FAIL;
  uint32 total_device_size_in_bytes = 0;
  eeprom_dev_info_t *eeprom_dev = NULL;

  status = eeprom_handle_validation(handle);
  if (status != EEPROM_DEVICE_DONE)
  {
    status = EEPROM_DEVICE_INVALID_PARAMETER;
    eeprom_log (&eeprom_drv.debug_log, 0x340);
    goto eeprom_rw_parameters_validation_end;
  }

  eeprom_dev = (eeprom_dev_info_t *)handle;
  
  if ((buffer == NULL) || (byte_count == 0))
  {
    status = EEPROM_DEVICE_INVALID_PARAMETER;
    eeprom_log (&eeprom_drv.debug_log, 0x341);
    goto eeprom_rw_parameters_validation_end;
  }

  total_device_size_in_bytes = eeprom_dev->config_params->page_size_bytes *
                         eeprom_dev->config_params->pages_per_block;
  
  /* Overflow and Boundary Checks */
  if (INT_OVERFLOW (byte_offset, byte_count) ||
      ((byte_offset + byte_count) > total_device_size_in_bytes))
  {
    status = EEPROM_DEVICE_INVALID_PARAMETER;
    eeprom_log (&eeprom_drv.debug_log, 0x342);
    goto eeprom_rw_parameters_validation_end;
  }

  if (eeprom_dev->config_params->page_size_bytes == 0)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x343);
  }

eeprom_rw_parameters_validation_end:
  return status;
}
