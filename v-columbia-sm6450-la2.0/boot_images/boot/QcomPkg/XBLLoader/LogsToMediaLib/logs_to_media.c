/*=============================================================================
                              Save Logs to Media

GENERAL DESCRIPTION
  Save the current logs to storage

Copyright 2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ----------------------------------------------------------
08/25/21   ds           init_done check to save api
07/20/21   digants      Initial Revision
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include <boot_logs_to_media.h>
#include <boot_comdef.h>
#include <boot_error_if.h>
#include <boot_media_interface_if.h>
#include <boot_logger_if.h>
#include <boot_memory_mgr_if.h>
#include <boot_partition_rw.h>
#include <string.h>
#include <stdio.h>
/*=============================================================================

                            DEFINITIONS

=============================================================================*/

#define NUM_ENTRIES(x) (sizeof(x)/sizeof(x[0]))

#define MAGIC_COOKIE 0x4C544D49
#define STORAGE_SECTOR_SIZE 0x1000 //4K
#define ROUNDUP_TO_SECTOR_SIZE_MULTIPLE(x) (((x-1) & (~(STORAGE_SECTOR_SIZE-1))) + STORAGE_SECTOR_SIZE)

#define BOOT_LOG_PARTITION_SIZE 0x20000 //128KB

#define BOOT_LOG_DDR_BUFFER_SIZE SCL_SBL1_DDR_BOOT_LOG_BUF_SIZE

static char log_marker_string[] = "LOG_START-0000000000\r\n";
static boolean init_done = FALSE;
extern uint8 xbl_sc_logs_partition_id[];

typedef struct logs_to_media_info
{
  uint32 magic_cookie;
  uint32 first_log_section_offset;
  uint32 curr_lognum;
  uint32 log_section_size;
  uint32 curr_log_section_offset;
  uint32 total_partition_size;
}logs_to_media_info;

static logs_to_media_info info_struct;

static uint32 info_struct_size = sizeof(logs_to_media_info);

static whitelst_tbl_entry_type info_struct_whitelist[] = {{(uintnt)(&info_struct), sizeof(logs_to_media_info)}};

/*=========================================================================

**  Function :  boot_init_logs_to_media

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
bl_error_boot_type boot_init_logs_to_media(const boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boolean rw_error = FALSE;
  uint32 partition_size = 0;
  uint32 calculated_next_offset = 0;
  uint32 calculated_log_section_size = ROUNDUP_TO_SECTOR_SIZE_MULTIPLE(BOOT_LOG_DDR_BUFFER_SIZE + sizeof(log_marker_string));

  do
  {
    /* init only once */
    if(init_done)
    {
      break;
    }
    // reset internal data structure
    memset((void *)(&info_struct), 0, sizeof(logs_to_media_info));
    
    // get partition size for checking if partition size has changed
    rw_error = boot_get_partition_size(xbl_sc_logs_partition_id, &partition_size);
    if(rw_error != TRUE)
    {
     return_status = GET_ERROR_CODE(BL_ERROR_GROUP_STORE_LOGS, BL_PARTITION_ERROR);
     break;
    }

    // read from partition into the info_struct
    rw_error = boot_read_from_partition(info_struct_whitelist, NUM_ENTRIES(info_struct_whitelist), (uint8*)(xbl_sc_logs_partition_id), NULL, 0, (uint8*)(&info_struct),(uint32)info_struct_size);
    
    if(rw_error != TRUE)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_STORE_LOGS, BL_READ_ERROR);
      break;
    }
       
    if((info_struct.magic_cookie != MAGIC_COOKIE) || (info_struct.log_section_size != calculated_log_section_size) || (info_struct.total_partition_size != partition_size))
    {
      info_struct.magic_cookie = MAGIC_COOKIE;
      info_struct.curr_lognum = 1;
      info_struct.total_partition_size = partition_size;
      info_struct.log_section_size = calculated_log_section_size;
      info_struct.first_log_section_offset = ROUNDUP_TO_SECTOR_SIZE_MULTIPLE(info_struct_size);
      info_struct.curr_log_section_offset = ROUNDUP_TO_SECTOR_SIZE_MULTIPLE(info_struct_size);
    }
    else
    {
      calculated_next_offset = info_struct.curr_log_section_offset + info_struct.log_section_size;
      if((calculated_next_offset + info_struct.log_section_size) > info_struct.total_partition_size)
      {
        calculated_next_offset = info_struct.first_log_section_offset;
      }  
      info_struct.curr_lognum++;
      info_struct.curr_log_section_offset = calculated_next_offset;
    }
    
    // write back the new info into metadata section
    rw_error = boot_write_to_partition((uint8*)(xbl_sc_logs_partition_id), NULL, 0, (uint8 *)(&info_struct), (uint32)(info_struct_size));
    
    if(rw_error != TRUE)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_STORE_LOGS, BL_WRITE_ERROR);
      break;
    }
    init_done = TRUE;
  }while(FALSE);  

  return return_status;
}

/*=========================================================================

**  Function :  boot_save_logs_to_media

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
bl_error_boot_type boot_save_logs_to_media(const boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  uint8* boot_log_buff_addr = NULL;
  uintnt boot_log_buff_size = 0;
  boot_memory_mgr_if_type *mem_if = NULL;
  boot_logger_if_type *logger_if = NULL;
  char* temp_log_buffer = NULL;
  boolean rw_error = FALSE;
  uint32 log_marker_string_len = sizeof(log_marker_string);
  
  /* just return if init is not done or magic cookie is not populated
  this is to handle cases where init was not called or init failed (partition not present) */
  if(!init_done || info_struct.magic_cookie != MAGIC_COOKIE)
  {
    return BL_ERR_NONE;
  }

  do
  {
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if(return_status != BL_ERR_NONE || mem_if == NULL)
    {
      break;
    }    
    
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_LOGGER_INTERFACE, (void **)&logger_if);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = logger_if->get_log_data(&boot_log_buff_addr, &boot_log_buff_size);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }
    
    if(boot_log_buff_addr == NULL || boot_log_buff_size == 0)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_STORE_LOGS, BL_INCORRECT_LOG_BUFF_PARAMS);
      break;
    }
    
    return_status = mem_if->malloc(info_struct.log_section_size, (void *)&temp_log_buffer);
    if(return_status != BL_ERR_NONE || temp_log_buffer == NULL)
    {
      break;
    }
    
    /* fill in spaces for complete log_section_size */
    memset((void *)temp_log_buffer,' ',info_struct.log_section_size);
    
    /* add log number marker */
    snprintf(temp_log_buffer,log_marker_string_len,"LOG_START-%010d\r\n",info_struct.curr_lognum);
    
    /* append boot logs to the log number marker string */
    memscpy((void *)(temp_log_buffer + log_marker_string_len - 1), boot_log_buff_size, (void *)boot_log_buff_addr, boot_log_buff_size);
    
    rw_error = boot_write_to_partition((uint8*)(xbl_sc_logs_partition_id), NULL, info_struct.curr_log_section_offset, (uint8 *)(temp_log_buffer), (uint32)info_struct.log_section_size);
    
    if(rw_error != TRUE)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_STORE_LOGS, BL_WRITE_ERROR);
      break;
    }
    
  }while(FALSE);
  
  if(mem_if!=NULL && temp_log_buffer!=NULL)
  {
    mem_if->free(temp_log_buffer);
  }
  
  return return_status;
}