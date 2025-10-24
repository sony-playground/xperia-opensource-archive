 /*****************************************************************************
 * EepromLibNull.c
 *
 * Copyright (c) 2020,2022 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================
                        Edit History


  when       who     what, where, why
----------   ---     ----------------------------------------------------------- 
04/12/2022   ss      Added Null function for eeprom_init_dtb()
05/13/2020   ck      Initial version

=============================================================================*/
#include "eeprom_api.h"


EEPROM_STATUS eeprom_open (uint32 dev_id,
                           eeprom_handle_t *handle)
{
  /* Validate pointers */
  if (handle == NULL)
  {
    return EEPROM_DEVICE_INVALID_PARAMETER;
  }


  /* Memory for handle would be malloc'ed here and assigned to handle double pointer.
     Instead just hard wire for simulation. */
  *handle = (void *)0xA5A5A5A5;


  return EEPROM_DEVICE_DONE;
}


EEPROM_STATUS eeprom_close (eeprom_handle_t handle)
{
  /* Validate pointers */
  if (handle == NULL)
  {
    return EEPROM_DEVICE_INVALID_PARAMETER;
  }


  /* Handle memory would be free here. */


  return EEPROM_DEVICE_DONE;
}


EEPROM_STATUS eeprom_get_info (eeprom_handle_t handle,
                               struct eeprom_info * eeprom_info)
{
  /* Verify pointers */
  if ((handle == NULL) ||
      (eeprom_info == NULL))
  {
    return EEPROM_DEVICE_INVALID_PARAMETER;
  }


  return EEPROM_DEVICE_DONE;
}


EEPROM_STATUS eeprom_write (eeprom_handle_t handle,
                            uint32 byte_offset,
                            uint32 byte_count,
                            void * buffer)
{
  /* Validate pointers */
  if ((handle == NULL) ||
      (buffer == NULL))
  {
    return EEPROM_DEVICE_INVALID_PARAMETER;
  }


  return EEPROM_DEVICE_DONE;
}


EEPROM_STATUS eeprom_read (eeprom_handle_t handle,
                           uint32 byte_offset,
                           uint32 byte_count,
                           void * buffer)
{
  /* Validate pointers */
  if ((handle == NULL) ||
      (buffer == NULL))
  {
    return EEPROM_DEVICE_INVALID_PARAMETER;
  }


  return EEPROM_DEVICE_DONE;
}


void eeprom_init_dtb(void)
{
	return;
}
