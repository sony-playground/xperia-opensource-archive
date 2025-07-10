/*=============================================================================

                              Boot Media Initialziation

GENERAL DESCRIPTION
  Plugs the correct interface as per the boot media.

Copyright 2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ----------------------------------------------------------
07/06/21   digants      Initial Revision
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include <boot_comdef.h>
#include <boot_media_types.h>
#include <boot_config_context.h>
#include <boot_error_if.h>
#include <boot_media_initialization.h>
#include <boot_media_interface_if.h>
/*=============================================================================

                            DEFINITIONS

=============================================================================*/


/*=========================================================================

**  Function :  boot_initialize_media_by_stage

** ==========================================================================
*/
/*!
* 
* @brief
*   Stage wise media init
* 
* @param[in] config_context_handle, init stage
* 
*/
bl_error_boot_type boot_process_media_init_table(const boot_handle config_context_handle, stage_cmd_set_per_media *media_init_table_ptr, uint32 num_table_entries, init_stage stage)
{
  bl_error_boot_type error = BL_ERR_NONE;
  boot_media_type boot_device = MEDIA_TYPE_MAX;
  uint32 num_ioctl_cmds = 0;
  ioctl_cmd_set_per_init_stage *ioctl_cmds_list_info_ptr = NULL;
  boot_media_interface_if_type *media_if = NULL;
  boot_memory_mgr_if_type * mem_if = NULL;
  ioctl_params *ioctl_cmd_params_ptr = NULL;
  
  if((config_context_handle == NULL) || (stage < STAGE_1) || (stage >= STAGE_MAX))
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_MEDIA_INITIALIZATION, BL_ERR_INVALID_PARAMETER);
  }
  
  do
  {
    /* Acquire and validate memory interface */
    error = boot_config_context_get_ptr(config_context_handle,
                                                CONFIG_CONTEXT_MEMORY_MGR_INTERFACE,
                                                (void **)&mem_if);
    if (error != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_MEDIA_IF, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Malloc media if memory */
    error = mem_if->malloc(sizeof(boot_media_interface_if_type),
                                   (void *)&media_if);
    if (error != BL_ERR_NONE)
    {
      break;
    }

    if (media_if == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_MEDIA_IF, BL_ERR_INTERFACE_FAILURE);
      break;
    }
    
    error = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, &boot_device);
    if (error != BL_ERR_NONE)
    {
      break;
    }
    
    /* Get media interface. */
    media_if->media_hw_init = NULL;
    error = boot_media_get_interface(config_context_handle, media_if);

    if (error != BL_ERR_NONE)
    {
      break;
    }
  
    /* get the ioctl command list ptr for the current boot device stage by iterating over the table */
    while(num_table_entries)
    {
      if(media_init_table_ptr->media_type == boot_device)
      {
        /* if the entry for the boot device is present in the table 
           then go ahead and lookup the current stage to get list of ioctl commands */
        ioctl_cmds_list_info_ptr = media_init_table_ptr->stage_cmd_set_table_ptr[stage];
        break;
      }
      num_table_entries--;
      media_init_table_ptr++;
    }
    
    if(ioctl_cmds_list_info_ptr != NULL)
    {
      num_ioctl_cmds = ioctl_cmds_list_info_ptr->num_cmd_entries;
      ioctl_cmd_params_ptr = ioctl_cmds_list_info_ptr->ioctl_cmd_set_ptr;      
    }

    /* go through each ioctl command in the list*/
    while(num_ioctl_cmds)
    {
      if(ioctl_cmd_params_ptr == NULL)
      {
        break;
      }
      error = media_if->ioctl((uint32)(ioctl_cmd_params_ptr->cmd), (void *)(ioctl_cmd_params_ptr->in_value_addr), (ioctl_cmd_params_ptr->in_size), NULL, NULL);
      if(error != BL_ERR_NONE)
      {
        break;
      }
      num_ioctl_cmds--;
      ioctl_cmd_params_ptr++;
    }
    
    if(error != BL_ERR_NONE)
    {
      break;
    }
    
    /* It is possible to have a media type with no interface.
       Call media's hw init if pointer is not null. */
    if (media_if->media_hw_init != NULL)
    {
      /* call media hw init once all ioctls are applied */
      error = media_if->media_hw_init(config_context_handle);
      if (error != BL_ERR_NONE)
      {
        break;
      }
    }  
    
  }while(FALSE);
  
  return error;
}