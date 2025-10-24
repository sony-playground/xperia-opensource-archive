/*===========================================================================

                       Boot Recovery Load Image Source File

GENERAL DESCRIPTION
  This file contains functions to load image from recovery partition and
  smem alloction to store partition info

Copyright 2021 Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
01/25/21   sp      Initial Revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <stdio.h>
#include <string.h>
#include <boot_config_context.h>
#include <boot_recovery_partition.h>
#include <boot_error_if.h>
#include <boot_smem_if.h>
#include <boot_logger_if.h>
#include <boot_loader_if.h>
#include <boot_recovery_lun.h>
#include <boot_smem_if.h>

static boot_boolean smem_recovery_partition_init = FALSE;
static recovery_partition_info *imem_recovery_partition_info_ptr;
static uint8 imem_partition_index = 0;

/*===========================================================================

**  Function :  boot_recovery_partitions_info_smem_init

** ==========================================================================
*/
/*!
*
* @brief
*   This function allocates memory in shared memory for recovery partitions info.
*
* @par Dependencies
*   Call this api after smem initialization
*
* @retval
*   None
*
* @par Side Effects
*   None
*/

bl_error_boot_type boot_recovery_partitions_info_smem_init(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if = NULL;
  boot_smem_if_type *smem_if = NULL;
  smem_recovery_partitions_info *smem_recovery_partitions_info_ptr = NULL;
  uint32 copy_size = 0;
  
  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SMEM_INTERFACE, (void **)&smem_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    smem_recovery_partitions_info_ptr = (smem_recovery_partitions_info *)smem_if->alloc(RECOVERY_PARTITION_SMEM_ID, sizeof(smem_recovery_partitions_info));
    if(smem_recovery_partitions_info_ptr == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_SMEM, BL_ERR_FAIL_ALLOCATE_SMEM);
      break;
    }

    memset(smem_recovery_partitions_info_ptr, 0, sizeof(smem_recovery_partitions_info));

    smem_recovery_partitions_info_ptr->magic_cookie = SMEM_RECOVERY_PARTITION_MAGIC_COOKIE;
    smem_recovery_partitions_info_ptr->version = SMEM_RECOVERY_PARTITION_VERSION;
    smem_recovery_partitions_info_ptr->max_entries = NUM_OF_PARTITIONS;
    smem_recovery_partitions_info_ptr->num_of_entries = 0;

    smem_recovery_partition_init = TRUE;

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if((imem_recovery_partition_info_ptr != NULL) && (IMEM_PARTITIONS <= NUM_OF_PARTITIONS))
    {
       /*copy partition info of images loaded before smem initialization*/
      copy_size = memscpy((void *)&smem_recovery_partitions_info_ptr->partition_info[smem_recovery_partitions_info_ptr->num_of_entries], sizeof(smem_recovery_partitions_info_ptr->partition_info), imem_recovery_partition_info_ptr , sizeof(*imem_recovery_partition_info_ptr)*imem_partition_index);
      if(copy_size < (sizeof(*imem_recovery_partition_info_ptr)*imem_partition_index))
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_LOADER, BL_ERR_BUFFER_SIZE_TOO_SMALL);
        break;
      }
      smem_recovery_partitions_info_ptr->num_of_entries = imem_partition_index;
      mem_if->free(imem_recovery_partition_info_ptr);
    }

  }while(FALSE);
  
  return status;
 }

/*===========================================================================

**  Function :  boot_load_recovery_image

** ==========================================================================
*/
/*!
*
* @brief
*   This function loads image from recovery partition.
*
* @retval
*   None
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_load_recovery_image(boot_handle config_context_handle, uint8 *recovery_partition_id)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  bl_error_boot_type error_code;
  char bootlog_buffer[BOOT_LOG_TEMP_BUFFER_SIZE];
  boot_logger_if_type *logger = NULL;
  uint8 *partition_id = NULL;
  uint32 optional_image = FALSE;

  do
  {
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_LOGGER_INTERFACE, (void **)&logger);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    /* CASE 1: recovery_partition_id is NULL, if LUN switch is enabled switch boot LUN */
    if (recovery_partition_id == NULL)
    {
#ifdef FEATURE_RECOVERY_PARTITION_SWITCH_RECOVERY_INFO_WRITE
      snprintf (bootlog_buffer, BOOT_LOG_TEMP_BUFFER_SIZE, "Recovery LUN");
      logger->log_message (bootlog_buffer);

      return_status = boot_recovery_load_recovery_lun (config_context_handle, recovery_partition_id);
      if(return_status != BL_ERR_NONE)
      {
        break;
      }
#else
      return_status = GET_ERROR_INFO;
#endif
    }
    
    /* CASE 2: recovery_partition_id is not NULL, try loading from recovery partition*/
    if (recovery_partition_id != NULL)
    {
      error_code = GET_ERROR_INFO;

      /*clear error code from boot_load_image default partition*/
      CLEAR_ERROR_CODE;

      snprintf (bootlog_buffer, BOOT_LOG_TEMP_BUFFER_SIZE, "Load recovery partition: %lx", error_code);
      logger->log_message (bootlog_buffer);
      return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_PARTITION_ID, (void **)&partition_id);
      if(return_status != BL_ERR_NONE)
      {
        break;
      }

      return_status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_PARTITION_ID, recovery_partition_id);
      if(return_status != BL_ERR_NONE)
      {
        break;
      }

      return_status = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_OPTIONAL_IMAGE, (void *)&optional_image);
      if(return_status != BL_ERR_NONE)
      {
        break;
      }

      return_status = boot_load_image(config_context_handle);
      if(return_status == BL_ERR_NONE)
      {
        return_status = boot_recovery_add_partition_info(partition_id, recovery_partition_id);
        if(return_status != BL_ERR_NONE)
        {
          break;
        }
      }
      /*Don't update smem with partition info incase of image header invalid error and optional img is true*/
      else if((return_status == BL_ERR_IMAGE_HDR_INVALID) && (optional_image == TRUE))
      {
        return_status = BL_ERR_NONE;
      }
    }

  }while(FALSE);

return return_status;
}

/*===========================================================================

**  Function :  boot_recovery_add_partition_info

** ==========================================================================
*/
/*!
*
* @brief
*   This function copies corrupted and recovery partions info to shared memory.
*
* @par Dependencies
*   Call this api after boot_recovery_partitions_info_smem_init.
*
* @retval
*   None
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_recovery_add_partition_info(uint8 *partition_id, uint8 *recovery_partition_id)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_recovery_status smem_status = BOOT_RECOVERY_ERROR_NONE;
  uint32 copy_size = 0;
  boot_boolean flag = FALSE;

  do
  {
    if(smem_recovery_partition_init != TRUE)
    {
      if(imem_partition_index < IMEM_PARTITIONS)
      {
        for(uint8 i = 0; i < imem_partition_index; i++)
        {
          if( memcmp(partition_id, (imem_recovery_partition_info_ptr+i)->corrupted_partition_id, PARTITION_ID_MAX_SIZE) == 0)
          {
             ((imem_recovery_partition_info_ptr+i)->number_of_corruption_reports)++;
             flag = TRUE;
             break;
          }
         }

        if(flag)
          break;    
		  
        copy_size = memscpy((imem_recovery_partition_info_ptr+imem_partition_index)->corrupted_partition_id, sizeof(imem_recovery_partition_info_ptr->corrupted_partition_id), partition_id, PARTITION_ID_MAX_SIZE);
        if(copy_size < PARTITION_ID_MAX_SIZE)
        {
          status = GET_ERROR_CODE(BL_ERROR_GROUP_LOADER, BL_ERR_BUFFER_SIZE_TOO_SMALL);
          break;
        }
        copy_size = memscpy((imem_recovery_partition_info_ptr+imem_partition_index)->recovery_partition_id, sizeof(imem_recovery_partition_info_ptr->recovery_partition_id), recovery_partition_id, PARTITION_ID_MAX_SIZE);
        if(copy_size < PARTITION_ID_MAX_SIZE)
        {
          status = GET_ERROR_CODE(BL_ERROR_GROUP_LOADER, BL_ERR_BUFFER_SIZE_TOO_SMALL);
          return status;
        }
        (imem_recovery_partition_info_ptr+imem_partition_index)->number_of_corruption_reports = 1;
        imem_partition_index++;
      }
    }
    else
    {
      smem_status = boot_recovery_add_good_and_corrupted_partition_id(partition_id, recovery_partition_id);
      if(smem_status != BOOT_RECOVERY_ERROR_NONE)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_LOADER, BL_ERR_BUFFER_SIZE_TOO_SMALL);
        break;
      }
    }
  }while(FALSE);

  return status;
}

/*===========================================================================

**  Function :  boot_recovery_partitions_info_imem_init

** ==========================================================================
*/
/*!
*
* @brief
*   This function allocates dynamic memory for partition info of images loaded
    before smem initialization.
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_recovery_partitions_info_imem_init(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if = NULL;

  do
  {
      status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
      if(status != BL_ERR_NONE)
      {
        break;
      }

      status = mem_if->malloc(sizeof(*imem_recovery_partition_info_ptr)*IMEM_PARTITIONS, (void *)&imem_recovery_partition_info_ptr);
      if(status != BL_ERR_NONE)
      {
        break;
      }

      if(imem_recovery_partition_info_ptr == NULL)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_LOADER, BL_ERR_MEMORY_ALLOC_FAIL); 
        break;
      }

      memset(imem_recovery_partition_info_ptr, 0, sizeof(*imem_recovery_partition_info_ptr)*IMEM_PARTITIONS);

  }while(FALSE);

  return status;
}
