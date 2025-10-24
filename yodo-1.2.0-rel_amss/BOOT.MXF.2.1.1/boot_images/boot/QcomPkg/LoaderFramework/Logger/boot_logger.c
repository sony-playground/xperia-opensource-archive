/*=============================================================================

                                boot logger

GENERAL DESCRIPTION
  This file contains the function implementation for logging messages during boot.
  Time unit in boot logger is microsecond(10^-6 second).

Copyright 2010-2022 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who        what, where, why
--------   ---        ---------------------------------------------------------
01/25/22   ds         boot_log_backup_to_buffer
01/05/22   rama       Clean up to remove redundant APIs
04/15/21   ds         missing func pointer
11/13/20   rama       Added boot_get_log_data.
06/08/20   yps        Update logger ptr after log buffer relocated.
08/16/19   ep         Initial version
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_logger_if.h"
#include "boot_timer_if.h"
#include "boot_memory_mgr_if.h"
#include "boot_config_context.h"
#include "boot_logger_ram.h"
#include <string.h>

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

#define NUM_LOGGERS    5

#define LOGGER_ID  0xDD244523


typedef struct boot_logger
{
  // common for all objects
  boot_handle_common_type handle_data;

  boot_registered_logger_if_type *loggers[NUM_LOGGERS];
  uint32 num_loggers;

//  boot_log_init_data *log_data;
  struct boot_log_meta_info log_meta_info;

  boot_memory_mgr_if_type *mem_if;
  boot_timer_if_type *timer_if;

} boot_logger;


static boot_logger *logger_ptr = NULL;


/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/


/*===========================================================================

**  Function :  boot_logger_deinit

** ==========================================================================
*/
/*!
 * @brief This function does init
 * @return None.
 *
 */
static bl_error_boot_type boot_logger_deinit(void)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(logger_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    for(int i = 0; i < logger_ptr->num_loggers; i++)
    {
      return_status = logger_ptr->loggers[i]->deinit();
      if(return_status != BL_ERR_NONE)
      {
        break;
      }
    }
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = logger_ptr->mem_if->free(logger_ptr);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    logger_ptr = NULL;

  } while(FALSE);

  return return_status;
}

/*===========================================================================

**  Function :  boot_logger_init

** ==========================================================================
*/
/*!
 * @brief This function does init
 * @return None.
 *
 */

static bl_error_boot_type boot_logger_init(boot_handle config_context_handle, boot_log_init_data *init_data)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_logger *l_ptr = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;
  boot_timer_if_type *timer_if = NULL;

  do
  {
    if(logger_ptr != NULL)
    {
      return_status = boot_logger_deinit();
      if(return_status != BL_ERR_NONE)
      {
          break;
      }
    }

    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if(return_status != BL_ERR_NONE)
    {
        break;
    }

    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_TIMER_INTERFACE, (void **)&timer_if);
    if(return_status != BL_ERR_NONE)
    {
        break;
    }

    return_status = mem_if->malloc(sizeof(boot_logger), (void *)&l_ptr);
      if(return_status != BL_ERR_NONE)
    {
      break;
    }
    else if(l_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_MEMORY_ALLOC_FAIL);
      break;
    }

    l_ptr->handle_data.config_context_handle = config_context_handle;
    l_ptr->handle_data.id = LOGGER_ID;

    l_ptr->num_loggers = 0;

//    l_ptr->log_data = log_data;

    l_ptr->log_meta_info.log_buf_size = init_data->log_buffer_size;
    l_ptr->log_meta_info.log_buf_start = init_data->log_buffer_start;
    l_ptr->log_meta_info.log_buf_ptr = init_data->log_buffer_start;
    l_ptr->log_meta_info.log_buf_init = TRUE;

    l_ptr->mem_if = mem_if;
    l_ptr->timer_if = timer_if;

    logger_ptr = l_ptr;

  } while(FALSE);

  return return_status;
}



bl_error_boot_type boot_register_logger(boot_registered_logger_if_type *logger)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(logger_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    if(logger == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_INVALID_PARAMETER);
      break;
    }

    if(logger_ptr->num_loggers == NUM_LOGGERS)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_LOGGER_TOO_MANY_LOGGERS);
      break;
    }

    logger_ptr->loggers[logger_ptr->num_loggers] = logger;
    logger_ptr->num_loggers++;

    return_status = logger->init(logger_ptr->handle_data.config_context_handle);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    boot_log_meta_info *log_meta_info_ptr = &(logger_ptr->log_meta_info);

    uint32 data_len = log_meta_info_ptr->log_buf_ptr - log_meta_info_ptr->log_buf_start;
    return_status = logger->log_message_raw((char *)log_meta_info_ptr->log_buf_start, data_len);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }


  } while(FALSE);

  return return_status;

}


static bl_error_boot_type boot_unregister_logger(boot_registered_logger_if_type *logger)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(logger_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    if(logger == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_INVALID_PARAMETER);
      break;
    }

    int index_logger = -1;
    for(int i = 0; i < logger_ptr->num_loggers; i++)
    {
      if(logger_ptr->loggers[i] == logger)
      {
        index_logger = i;
        break;
      }
    }

    if(index_logger == -1)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_INVALID_PARAMETER);
      break;
    }

    for(int i = index_logger; i < logger_ptr->num_loggers - 1; i++)
    {
      logger_ptr->loggers[i] = logger_ptr->loggers[i + 1];
    }

    logger_ptr->num_loggers--;

    return_status = logger->deinit();
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  } while(FALSE);

  return return_status;

}


/*===========================================================================

**  Function :  boot_log_message_raw

** ==========================================================================
*/
/*!
*
* @brief
*  Logs the given message.  Unlike boot_log_message, all data points must be
*  provided.
*
* @param[in] message  log message
*
* @param[in] timestamp  timestamp to log
*   Value of BOOT_DND_TIMESTAMP indicates timestamp will not be printed
*
* @param[in] log_type  type of the log
*
* @param[in] optional_data  Optional data that can be added to entry
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type boot_log_message_raw(char *message,
                                        uint32 timestamp,
                                        char log_type,
                                        char *optional_data)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  char *init_buffer_ptr = NULL;
  uint32 data_len = 0;


  do
  {

    if(logger_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    return_status = boot_log_message_ram(&(logger_ptr->log_meta_info), message, timestamp, log_type, optional_data, &init_buffer_ptr, &data_len);

    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    if((init_buffer_ptr != NULL) && (data_len != 0))
    {
      for(int i = 0; i < logger_ptr->num_loggers; i++)
      {
        return_status = logger_ptr->loggers[i]->log_message_raw(init_buffer_ptr, data_len);
        if(return_status != BL_ERR_NONE)
        {
          break;
        }
      }
    }

    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  } while(FALSE);

  return return_status;
}
/* boot_log_message_raw */




/*===========================================================================

**  Function :  boot_log_message_optional_data

** ==========================================================================
*/
/*!
*
* @brief
*  Logs the given message using various logging methods.It will prefix a timestamp
*  to the message string. The timestamp is calculated as the current absolute time
*  subtracts the reference time.
*
* @param[in] message           log message
*
* @param[in] optional_data     Optional data that can be added to entry
*
* @par Dependencies
*   boot_logger_ram
*   boot_logger_timer
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type boot_log_message_optional_data(char *message, char *optional_data)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(logger_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    uint32 current_timestamp;
    return_status = logger_ptr->timer_if->get_time(0, &current_timestamp);
    if(return_status != BL_ERR_NONE)
    {
      current_timestamp = 0;
    }

    return_status = boot_log_message_raw(message, current_timestamp,
                                         LOG_MSG_TYPE_BOOT, optional_data);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }


  } while (FALSE);

  return return_status;
}
/* boot_log_message_optional_data */



/*===========================================================================
**  Function :  boot_log_message
** ==========================================================================
*/
/*!
*
* @brief
*  Logs the given message using various logging methods.It will prefix a timestamp
*  to the message string. The timestamp is calculated as the current absolute time
*  subtracts the reference time.
*
* @param[in] message         log message
*
* @par Dependencies
*   boot_logger_ram
*   boot_logger_timer
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type boot_log_message(char *message)
{

  /* Call boot_log_message_optional_data so two functions do not have
     redundant logic. */
  return boot_log_message_optional_data(message, NULL);

}
/* boot_log_message */


/*===========================================================================

**  Function :  boot_log_message_delta_time_optional_data

** ==========================================================================
*/
/*!
*
* @brief
*  Logs the given message using various logging methods.It will prefix a timestamp
*  to the message string. The timestamp is calculated as the current absolute time
*  subtracts the reference time.
*
* @param[in] message           log message
*
* @param[in] optional_data     Optional data that can be added to entry
*
* @par Dependencies
*   boot_logger_ram
*   boot_logger_timer
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
static bl_error_boot_type boot_log_message_delta_time_optional_data(uint32 old_time, char *message, char *optional_data)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  do
  {
    if(logger_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }
    uint32 current_timestamp;
    return_status = logger_ptr->timer_if->get_time(0, &current_timestamp);
    if(return_status != BL_ERR_NONE)
    {
      current_timestamp = 0;
    }

    uint32 delta_time = current_timestamp - old_time;

    return_status = boot_log_message_raw(message, delta_time, LOG_MSG_TYPE_DELTA, optional_data);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

  } while(FALSE);

  return return_status;
}
/* boot_log_message_optional_data */




/*===========================================================================
**  Function :  boot_log_message_delta_time
** ==========================================================================
*/
/*!
*
* @brief
*  Logs the given message using various logging methods.It will prefix a timestamp
*  to the message string. The timestamp is calculated as the current absolute time
*  subtracts the reference time.
*
* @param[in] message         log message
*
* @par Dependencies
*   boot_logger_ram
*   boot_logger_timer
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
static bl_error_boot_type boot_log_message_delta_time(uint32 old_time, char *message)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  /* Call boot_log_message_optional_data so two functions do not have
     redundant logic. */
  return_status = boot_log_message_delta_time_optional_data(old_time, message, NULL);

  return return_status;
}
/* boot_log_message */

/*===========================================================================
**  Function :  boot_get_log_data
** ==========================================================================
*/
/*!
*
* @brief
*  Function returns the base address and size of boot logs.
*
* @param[in]
*   uint8 ** pointer to store the log buffer pointer.
*   uintnt * pointer to store the size of log buffer.
*
* @par Dependencies
*   boot_logger_init must be called
* @retval
*   BL_ERR_NONE on success.
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type boot_get_log_data(uint8 **boot_log_addr_ptr, uintnt *size_ptr)
{
  bl_error_boot_type status = BL_ERR_GET_LOG_DATA_FAIL;
  uint8 *boot_log_base_ptr = NULL;
  uintnt boot_log_init_info_size = 0;

  if(logger_ptr == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_UNINITIALIZED_VARIABLE);
	return status;
  }

  if(logger_ptr->log_meta_info.log_buf_init == TRUE &&
     logger_ptr->log_meta_info.log_buf_ptr > logger_ptr->log_meta_info.log_buf_start)
  {
    boot_log_init_info_size= logger_ptr->log_meta_info.log_buf_size;
	boot_log_base_ptr = logger_ptr->log_meta_info.log_buf_start;
  }

  if((boot_log_addr_ptr == NULL) || (size_ptr == NULL))
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_NULL_PTR_PASSED);
	return status;
  }

  if(boot_log_init_info_size > 0)
  {
    *boot_log_addr_ptr = boot_log_base_ptr;
	*size_ptr = boot_log_init_info_size;
	status = BL_ERR_NONE;
  }

  return status;
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------



/*===========================================================================
**  Function :  boot_logger_get_interface
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes a boot_logger_get_interface object
*
* @par Dependencies
*   None
*
*/

bl_error_boot_type boot_logger_get_interface(void *ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    boot_logger_if_type *logger_if = (boot_logger_if_type *)ptr;

    if(logger_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_INVALID_PARAMETER);
      break;
    }

    logger_if->init = boot_logger_init;
    logger_if->deinit = boot_logger_deinit;

    logger_if->register_logger = boot_register_logger;
    logger_if->unregister_logger = boot_unregister_logger;

    logger_if->log_message = boot_log_message;
    logger_if->log_message_optional = boot_log_message_optional_data;

    logger_if->log_message_delta_time = boot_log_message_delta_time;
    logger_if->log_message_delta_time_optional = boot_log_message_delta_time_optional_data;
    logger_if->get_log_data = boot_get_log_data;


  } while(FALSE);

  return return_status;
}


uint32 boot_log_get_time(void)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_timer_if_type *timer_if = NULL;

  return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_TIMER_INTERFACE, (void **)&timer_if);
  if(return_status != BL_ERR_NONE)
  {
    return 0;
  }

  uint32 current_timestamp;
  return_status = logger_ptr->timer_if->get_time(0, &current_timestamp);
  if(return_status != BL_ERR_NONE)
  {
    return 0;
  }

  return current_timestamp;
}


uint32 boot_log_delta_time(uint32 old_time, char *message)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_logger_if_type *logger;

  return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_LOGGER_INTERFACE, (void **)&logger);
  if(return_status != BL_ERR_NONE)
  {
    return 0;
  }

  logger->log_message_delta_time(old_time, message);

  // why return delta time?
  return 0;
}


uint32 boot_log_delta_time_optional_data(uint32 old_time, char *message, char *optional_data)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_logger_if_type *logger;

  return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_LOGGER_INTERFACE, (void **)&logger);
  if(return_status != BL_ERR_NONE)
  {
    return 0;
  }

  logger->log_message_delta_time_optional(old_time, message, optional_data);

  // why return delta time?
  return 0;
}

/*===========================================================================

**  Function :  boot_log_copy_ram

** ==========================================================================
*/
/*!
*
* @brief
* Copy the log and meta info in one memory location to some other
* memory location. This can be used to save log between sbl

 *
* @param[in] dst_meta_info_addr  destination address to save meta info
*
* @param[in] dst_log_buf_addr  destination address to save message log
*
* @param[in] src_meta_info_addr  source address to read meta info
*
* @param[in] src_log_buf_addr  source address to read message log
*
* @param[in] log_buf_size  size of the message log to copy in bytes
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
static void boot_log_copy_ram
(
  void *dst_meta_info_addr,
  void *dst_log_buf_addr,
  uint32 dst_log_buf_size,
  void *src_meta_info_addr,
  void *src_log_buf_addr,
  uint32 src_log_buf_size
)
{
  struct boot_log_meta_info *dst_meta_info_ptr =
           (struct boot_log_meta_info *)dst_meta_info_addr;

  struct boot_log_meta_info *src_meta_info_ptr =
           (struct boot_log_meta_info *)src_meta_info_addr;

  /*added if block to resolve kw error*/
  if(dst_log_buf_addr   != NULL &&
     dst_meta_info_ptr != NULL &&
     src_log_buf_addr   != NULL &&
     src_meta_info_ptr != NULL  &&
     src_log_buf_size <= dst_log_buf_size)

    {

      memcpy(dst_meta_info_ptr,
      src_meta_info_ptr,
      sizeof(struct boot_log_meta_info));

      /*now copy the log message buffer to new location*/
      memcpy(dst_log_buf_addr,
      src_log_buf_addr,
      src_log_buf_size);

      /* Zero initalize the rest of dst log buffer*/
      memset((void* )((uintnt)dst_log_buf_addr + src_log_buf_size),0,
      dst_log_buf_size - src_log_buf_size);

      /*update the meta info to reflect the new size and start address*/
      dst_meta_info_ptr->log_buf_size = dst_log_buf_size;

      dst_meta_info_ptr->log_buf_start = dst_log_buf_addr;

      dst_meta_info_ptr->log_buf_ptr = (src_meta_info_ptr->log_buf_ptr -
                                        src_meta_info_ptr->log_buf_start) +
                                       dst_meta_info_ptr->log_buf_start;
    }

}

void boot_log_relocate
(
  void *dst_meta_info_addr,
  void *dst_log_buf_addr,
  uint32 dst_log_buf_size,
  void *dst_time_marker_buf_addr,
  uint32 dst_time_marker_buf_size,
  void *src_meta_info_addr,
  void *src_log_buf_addr,
  uint32 src_log_buf_size,
  void *src_time_marker_buf_addr,
  uint32 src_time_marker_buf_size
)
{
  struct boot_log_meta_info *dst_meta_info_ptr =
  		(struct boot_log_meta_info *)dst_meta_info_addr;

  boot_log_copy_ram(dst_meta_info_addr,
                     dst_log_buf_addr,
                     dst_log_buf_size,
                     src_meta_info_addr,
                     src_log_buf_addr,
                     src_log_buf_size);
  if (logger_ptr != NULL)
  {
    dst_meta_info_ptr->log_buf_ptr = (logger_ptr->log_meta_info.log_buf_ptr -
                                      logger_ptr->log_meta_info.log_buf_start) +
                                      dst_log_buf_addr;
    dst_meta_info_ptr->log_buf_size = dst_log_buf_size;

    dst_meta_info_ptr->log_buf_start = dst_log_buf_addr;

    logger_ptr->log_meta_info.log_buf_start = dst_meta_info_ptr->log_buf_start;
    logger_ptr->log_meta_info.log_buf_size = dst_meta_info_ptr->log_buf_size;
    logger_ptr->log_meta_info.log_buf_ptr = dst_meta_info_ptr->log_buf_ptr;
  }

}

void boot_log_backup_to_buffer(void *mem_buffer_start, uint32 mem_buffer_size)
{
  uint32 log_size_from_start = 0x0;
  
  if(logger_ptr == NULL)
  {
    return;
  }
  
  memset(mem_buffer_start, 0, mem_buffer_size);
  
  if(logger_ptr->log_meta_info.log_buf_size <= mem_buffer_size)
  {
    memcpy(mem_buffer_start, (void *)(logger_ptr->log_meta_info.log_buf_start), logger_ptr->log_meta_info.log_buf_size);
    return;
  }
  
  log_size_from_start = logger_ptr->log_meta_info.log_buf_ptr - logger_ptr->log_meta_info.log_buf_start;
  
  if(log_size_from_start <= mem_buffer_size)
  {
    memcpy(mem_buffer_start, (void *)(logger_ptr->log_meta_info.log_buf_start), log_size_from_start);
    return;
  }
  
  memcpy(mem_buffer_start, (void *)(logger_ptr->log_meta_info.log_buf_ptr - mem_buffer_size), mem_buffer_size);
}
