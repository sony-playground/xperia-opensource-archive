/**********************************************************************
 * eeprom_api.c
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

#include "eeprom_api.h"
#include "eeprom_core.h"
#include "eeprom_utils.h"
#include "eeprom_osal.h"
#include "eeprom_config.h"

// A data stucture used by the caller of the EEPROM driver as 
// a handle to access the APIs
eeprom_dev_info_t eeprom_dev_array[MAX_EEPROM_OPEN_HANDLES];

/**
 * Opens a handle to an EEPROM device.
 *
 * @param dev_id [IN]
 *   Device ID that specifies a EEPROM device.
 *
 * @param handle [OUT]
 *   EEPROM interface handle.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 */
EEPROM_STATUS eeprom_open (uint32 dev_id, eeprom_handle_t *handle)
{
  EEPROM_STATUS status = EEPROM_DEVICE_FAIL;
  struct eeprom_cfg_data *eeprom_cfgs = NULL;
  eeprom_dev_info_t *eeprom_dev = NULL;
  eeprom_cfg_params_t *dev_params = NULL;
  uint32 idx, num_devices = 0;
  
  eeprom_get_configs(&eeprom_cfgs);

  if (eeprom_drv.init_done == FALSE)
  {
    memset(&eeprom_drv, 0, sizeof(eeprom_drv_info_t));
	eeprom_drv.eeprom_dev = &eeprom_dev_array[0];
	eeprom_drv.init_done = TRUE;
  }
  
  if (eeprom_cfgs == NULL)
  {
    eeprom_log(&eeprom_drv.debug_log, 0x108);
    goto eeprom_open_end;
  }
  	
  num_devices = eeprom_cfgs->num_devices;
  if (dev_id > num_devices)
  {
    eeprom_log(&eeprom_drv.debug_log, 0x109);
    goto eeprom_open_end;
  }

  if (dev_id >= MAX_EEPROM_OPEN_HANDLES)
  {
    eeprom_log(&eeprom_drv.debug_log, 0x110);
    goto eeprom_open_end;
  }
  
  eeprom_dev = &eeprom_dev_array[dev_id];
  
  if (eeprom_dev->eeprom_init_done == FALSE)
  {
    for (idx = 0; idx < num_devices; idx++)
    {
      if (dev_id == eeprom_cfgs->dev_params[idx].device_id)
      {
        dev_params = &eeprom_cfgs->dev_params[idx];
		break;
      }
    }
	if (dev_params == NULL)
	{
      eeprom_log(&eeprom_drv.debug_log, 0x111);
      goto eeprom_open_end;
	}
    status = eeprom_init(dev_params, eeprom_dev);
  }

  if ((eeprom_dev->eeprom_init_done == FALSE) || (handle == NULL))
  {
    eeprom_log (&eeprom_drv.debug_log, 0x112);
    goto eeprom_open_end;
  }

  *handle = (eeprom_handle_t)eeprom_dev;
  status = EEPROM_DEVICE_DONE;

eeprom_open_end:
  return status;
}

/**
 * Closes a handle to an EEPROM device.
 * Clients should close the EEPROM driver instance when accesses
 * to the EEPROM are no longer needed.
 *
 * @param handle [IN]
 *   EEPROM interface handle.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 */
EEPROM_STATUS eeprom_close (eeprom_handle_t handle)
{
  EEPROM_STATUS status = EEPROM_DEVICE_FAIL;
  eeprom_dev_info_t *eeprom_dev = NULL;

  if (eeprom_drv.init_done == FALSE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x120);
    goto eeprom_close_end;
  }

  status = eeprom_handle_validation (handle);
  if (status != EEPROM_DEVICE_DONE)
  {
    status = EEPROM_DEVICE_INVALID_PARAMETER;
    eeprom_log (&eeprom_drv.debug_log, 0x121);
    goto eeprom_close_end;
  }

  eeprom_dev = (eeprom_dev_info_t *)handle;
  
  status = eeprom_deinit(eeprom_dev);
  
  if (status != EEPROM_DEVICE_DONE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x122);
    goto eeprom_close_end;
  }

  status = EEPROM_DEVICE_DONE;

eeprom_close_end:
  return status;
}

/**
 * Gets EEPROM device information. EEPROM driver assumes that the memory
 * for returned information is allocated by the driver client.
 * \n
 *
 * @param handle [IN]
 *   EEPROM interface handle
 *
 * @param eeprom_info [OUT]
 *   Pointer to the client's EEPROM device info data.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 */
EEPROM_STATUS eeprom_get_info(eeprom_handle_t handle,
                              struct eeprom_info *eeprom_info)
{
  EEPROM_STATUS       status = EEPROM_DEVICE_FAIL;
  eeprom_dev_info_t  *eeprom_dev = NULL;

  if (eeprom_drv.init_done == FALSE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x100);
    status = EEPROM_DEVICE_FAIL;
    goto eeprom_get_info_end;
  }
  
  status = eeprom_handle_validation (handle);
  if (status != EEPROM_DEVICE_DONE)
  {
    status = EEPROM_DEVICE_INVALID_PARAMETER;
    eeprom_log (&eeprom_drv.debug_log, 0x101);
    goto eeprom_get_info_end;
  }

  eeprom_dev = (eeprom_dev_info_t *)handle;
  
  memset(eeprom_info, 0, sizeof( struct eeprom_info));
  memscpy (eeprom_info->device_name, sizeof(eeprom_info->device_name),
    eeprom_dev->config_params->device_name, sizeof(eeprom_dev->config_params->device_name));
  eeprom_info->version               = EEPROM_API_VERSION;
  eeprom_info->device_address        = eeprom_dev->config_params->base_address;
  eeprom_info->device_clk_freq_KHz   = eeprom_dev->config_params->clk;
  eeprom_info->page_size_bytes       = eeprom_dev->config_params->page_size_bytes;
  eeprom_info->total_pages_in_device = eeprom_dev->config_params->pages_per_block;
 
  status = EEPROM_DEVICE_DONE;

eeprom_get_info_end:
  return status;
}


/**
 * Allows write data to the EEPROM.
 *
 * @param handle [IN]
 *   EEPROM interface handle
 *
 * @param byte_offset [IN]
 *   Byte offset from the beginning of the EEPROM device to write to.
 *
 * @param byte_count [IN]
 *   Number of bytes to write data.
 *
 * @buffer [IN]
 *   data buffer for a EEPROM device write operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 */
EEPROM_STATUS eeprom_write (eeprom_handle_t handle,
  uint32 byte_offset, uint32 byte_count, void *buffer)
{
  EEPROM_STATUS status = EEPROM_DEVICE_FAIL;
  EEPROM_CORE_STATUS eeprom_status = EEPROM_CORE_FAIL;
  uint32 transfer_start_addr = 0;
  uint32 parti_start_block = 0;

  if (eeprom_drv.init_done == FALSE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x140);
    status = EEPROM_DEVICE_FAIL;
    goto eeprom_write_end;
  }
  
  /* validate passed in paramerters */
  status = eeprom_rw_parameters_validation (handle, byte_offset,
                                            byte_count, buffer);
  if (status != EEPROM_DEVICE_DONE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x141);
    goto eeprom_write_end;
  }

  transfer_start_addr = parti_start_block + byte_offset;

  eeprom_status = eeprom_core_write ((eeprom_dev_info_t *)handle, transfer_start_addr,
                                     byte_count, (uint8 *)buffer);
  if (eeprom_status != EEPROM_CORE_DONE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x142);
    status = EEPROM_DEVICE_FAIL;
  }
  else
  {
    status = EEPROM_DEVICE_DONE;
  }

eeprom_write_end:
  return status;
}

/**
 * Allows read data from the EEPROM
 *
 * @param handle [IN]
 *   EEPROM interface handle
 *
 * @param byte_offset [IN]
 *   Byte offset from the beginning of the EEPROM device to read from.
 *
 * @param byte_count [IN]
 *   Number of bytes to read data.
 *
 * @buffer [OUT]
 *   data buffer for a EEPROM device read operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 */
EEPROM_STATUS eeprom_read(eeprom_handle_t handle,
  uint32 byte_offset, uint32 byte_count, void *buffer)
{
  EEPROM_STATUS status = EEPROM_DEVICE_FAIL;
  EEPROM_CORE_STATUS eeprom_status = EEPROM_CORE_FAIL;

  if (eeprom_drv.init_done == FALSE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x130);
    goto eeprom_read_end;
  }

  /* validate passed in paramerters */
  status = eeprom_rw_parameters_validation (handle,
                                            byte_offset, byte_count, buffer);
  if (status != EEPROM_DEVICE_DONE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x131);
    goto eeprom_read_end;
  }

  eeprom_status = eeprom_core_read((eeprom_dev_info_t *)handle, byte_offset,
                                   byte_count, (uint8 *)buffer);

  if (eeprom_status != EEPROM_CORE_DONE)
  {
    eeprom_log (&eeprom_drv.debug_log, 0x132);
    status = EEPROM_DEVICE_FAIL;
  }
  else
  {
    status = EEPROM_DEVICE_DONE;
  }

eeprom_read_end:
  return status;
}

