/*=============================================================================

                     Boott Partition Read

GENERAL DESCRIPTION
  This file contains the implementation for boot layer that provides the APIs
  for reading and writing to block based flash devices.

Copyright 2021-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
06/14/22   rama         Remove GET_ERROR_CODE as error code is not returned.
06/03/22   rama         Remove whitelist dependency for clients
7/15/21     rrwt          initial revision
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <string.h>
#include "boot_config_context.h"
#include "boot_partition_rw.h"
#include "boot_media_interface_if.h"
#include "boot_whitelist_if.h"
/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

typedef enum
{
  READ_PARTITION,
  WRITE_PARTITION,
  GET_PARTITION_SIZE
} partition_rw_type;

static boolean boot_partition_rw(
  uint8* partition_id_main,
  uint8* partition_id_secondary,
  uint64 partition_offset,
  uint8* buffer_ptr,
  uint32 buffer_size,
  partition_rw_type rw_type
);

/*=============================================================================

FUNCTION DEFINITIONS

=============================================================================*/

/*===========================================================================
**  Function :  boot_read_from_partition
** ==========================================================================
*
* @brief
*   This funcion will read the data from parition
*
* @par Dependencies
*
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

boolean boot_read_from_partition(
  uint8* partition_id_main,
  uint8* partition_id_secondary,
  uint64 partition_offset,
  uint8* buffer_ptr,
  uint32 buffer_size
)
{
  return boot_partition_rw(partition_id_main, partition_id_secondary, partition_offset, buffer_ptr, buffer_size, READ_PARTITION) ;
}



/*===========================================================================
**  Function :  boot_write_to_partition
** ==========================================================================
*
* @brief
*   This funcion will write the data to parition
*
* @par Dependencies
*
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

boolean boot_write_to_partition(
  uint8* partition_id_main,
  uint8* partition_id_secondary,
  uint64 partition_offset,
  uint8* buffer_ptr,
  uint32 buffer_size
)
{
  return boot_partition_rw(partition_id_main, partition_id_secondary, partition_offset, buffer_ptr, buffer_size, WRITE_PARTITION) ;
}

/*===========================================================================
**  Function :  boot_get_partition_size
** ==========================================================================
*
* @brief
*   This function returns parition size
*
* @par Dependencies
*
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
boolean boot_get_partition_size(uint8* partition_id, uint32* partition_size)
{
  return boot_partition_rw(partition_id, NULL, 0, (uint8*)partition_size, 0, GET_PARTITION_SIZE) ;
}

/*===========================================================================
**  Function :  boot_partition_rw
** ==========================================================================
*
* @brief
*   This funcion will read/write the data from parition
*
* @par Dependencies
*
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

boolean boot_partition_rw(
  uint8* partition_id_main,
  uint8* partition_id_secondary,
  uint64 partition_offset,
  uint8* buffer_ptr,
  uint32 buffer_size,
  partition_rw_type rw_type
)
{
  uint8 *backup_partition_id = NULL;
  whitelst_tbl_entry_type* backup_whitelist_table = NULL;
  uint32 backup_whitelist_num_entries = 0;
  bl_error_boot_type status = BL_ERR_NONE;
  boolean return_status = FALSE;
  boot_media_interface_if_type *media_if = NULL;
  boot_whitelist_if_type *whitelist_if = NULL;
  boot_handle media_handle = NULL;
  boot_handle whitelist_handle = NULL;
  whitelst_tbl_entry_type read_whitelist_table = {};
  uint32 read_whitelist_num_entries = 0;

  do
  {
    if (partition_id_main == NULL || (buffer_ptr == NULL) || (rw_type != GET_PARTITION_SIZE && buffer_size == 0))
    {
      status = BL_ERROR_GROUP_BOOT_MEDIA_IF | BL_ERR_NULL_PTR_PASSED;
      break;
    }

    status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PARTITION_ID, (void **)&backup_partition_id);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_set_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PARTITION_ID, partition_id_main);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (rw_type == READ_PARTITION)
    {

      /* Create a whitelist on the fly */
      read_whitelist_table.start_addr = (uintnt)buffer_ptr;
      read_whitelist_table.size = (uint32)buffer_size;
      /* calculate the size of created whitelist */
      read_whitelist_num_entries = sizeof(read_whitelist_table)/sizeof(whitelst_tbl_entry_type);
      
      status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_WHITELIST_NUM_ENTRIES, (uint32 *)&backup_whitelist_num_entries);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_IMAGE_WHITELIST, (void **)&backup_whitelist_table);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      status = boot_config_context_set_value(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_WHITELIST_NUM_ENTRIES, read_whitelist_num_entries);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      status = boot_config_context_set_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_IMAGE_WHITELIST, (void **)&read_whitelist_table);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_WHITELIST_INTERFACE, (void **)&whitelist_if);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      status = whitelist_if->open(CONFIG_CONTEXT_CRT_HANDLE, &whitelist_handle, &read_whitelist_table, read_whitelist_num_entries);
      if (status != BL_ERR_NONE)
      {
        break;
      }
    }

    status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_BOOT_MEDIA_INTERFACE, (void **)(&media_if));
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (media_if == NULL)
    {
      status = BL_ERROR_GROUP_BOOT_MEDIA_IF | BL_ERR_NULL_PTR_PASSED;
      break;
    }

    status = media_if->open(CONFIG_CONTEXT_CRT_HANDLE, &media_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (rw_type == READ_PARTITION)
    {
      status = whitelist_if->check_region(whitelist_handle, (uint64)buffer_ptr, buffer_size);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      status = media_if->read(media_handle, (void *)buffer_ptr, partition_offset, buffer_size);
    }
    else if (rw_type == WRITE_PARTITION)
    {
      status = media_if->write(media_handle, (void *)buffer_ptr, partition_offset, buffer_size);
    }
    else if (rw_type == GET_PARTITION_SIZE)
    {
      status = media_if->ioctl(GET_CURRENT_PARTITION_SIZE, media_handle, 0, (void *)(buffer_ptr), NULL);
    }

    /* if read/write on main partition fails, try to read/write on secondary parition */
    if ( rw_type != GET_PARTITION_SIZE && status!=BL_ERR_NONE && partition_id_secondary!=NULL)
    {
      status = boot_config_context_set_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PARTITION_ID, partition_id_secondary);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      if (rw_type == READ_PARTITION)
      {
        status = media_if->read(media_handle, (void *)buffer_ptr, partition_offset, buffer_size);
      }
      else if (rw_type == WRITE_PARTITION)
      {
        status = media_if->write(media_handle, (void *)buffer_ptr, partition_offset, buffer_size);
      }
    }

    if (status!= BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_set_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PARTITION_ID, backup_partition_id);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (rw_type == READ_PARTITION)
    {
      status = boot_config_context_set_value(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_WHITELIST_NUM_ENTRIES, backup_whitelist_num_entries);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      status = boot_config_context_set_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_IMAGE_WHITELIST, backup_whitelist_table);
      if (status != BL_ERR_NONE)
      {
        break;
      }
    }
    return_status = TRUE;
  } while (FALSE);

  if (whitelist_handle!= NULL)
  {
    status = whitelist_if->close(whitelist_handle);
    if (status != BL_ERR_NONE)
    {
      return_status = FALSE;
    }
  }

  if (media_handle != NULL)
  {
    status = media_if->close(media_handle);
    if (status != BL_ERR_NONE)
    {
      return_status = FALSE;
    }
  }

  return return_status;
}