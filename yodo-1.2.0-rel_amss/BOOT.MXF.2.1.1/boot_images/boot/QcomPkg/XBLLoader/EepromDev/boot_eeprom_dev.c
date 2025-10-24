/*=============================================================================

                     Boot Eeprom Device

GENERAL DESCRIPTION
  This file contains the implementation for boot layer that provides the APIs
  for reading and writing to eeprom devices.

Copyright 2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
02/09/22   rama         Port statistics and cache invalidation changes
05/24/21   rama         changes to make boot_eeprom_dev_hw_init and deinit recallable
07/20/20   ck           Added pre_i2c_clock_init to boot_eeprom_dev_hw_init
05/12/20   ck           Initial revision.
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <string.h>
#include <boot_eeprom_dev.h>
#include <boot_eeprom_if.h>
#include <boot_memory_mgr_if.h>
#include <boot_config_context.h>
#include <boot_statistics_if.h>
#include <boot_clk_if.h>
#include <boot_edk2_cache_if.h>


/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
/* Eeprom device handle ID */
#define EDEV 0x45444556


// Block device handle
typedef struct boot_eeprom_dev_obj
{
  uint32 id;
  boot_memory_mgr_if_type * mem_if;
  boot_statistics_if_type * boot_stats_if;
  boot_eeprom_if_type * eeprom_if;
  eeprom_handle_t eeprom_handle;
  struct eeprom_info eeprom_info;
}eeprom_device_handle;

static boot_boolean boot_eeprom_dev_is_hw_initialized = FALSE;

/*=============================================================================

FUNCTION DEFINITIONS

=============================================================================*/
/*=========================================================================

**  Function :  _init

** ==========================================================================
*/
/*!
* 
* @brief
*   intialize the eeprom dev handle.
* 
* @param[in] pointer to eeprom dev handle
* 
*/
static void _init(eeprom_device_handle * eeprom_dev_handle)
{
  /* Clear eeprom device handle */
  memset((void *)eeprom_dev_handle,
         0,
         sizeof(eeprom_device_handle));

  
  /* Populate id */
  eeprom_dev_handle->id = EDEV;
}


/*=========================================================================

**  Function :  _handle_check

** ==========================================================================
*/
/*!
* 
* @brief
*   Sanitize the eeprom device handle.
* 
* @param[in] eeprom device handle
* 
*/
static bl_error_boot_type _handle_check(eeprom_device_handle * eeprom_dev_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;


  /* Verify eeprom device handle pointer */
  if (eeprom_dev_handle == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Verify id */
  if (eeprom_dev_handle->id != EDEV)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_INVALID_HANDLE);
    goto exit;
  }


  /* Verify handle parameters */
  if ((eeprom_dev_handle->mem_if == NULL) ||
      (eeprom_dev_handle->eeprom_if == NULL) ||
      (eeprom_dev_handle->eeprom_handle == NULL))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }

    
 exit:
  return error;
}


/*=========================================================================

**  Function :  boot_eeprom_dev_open

** ==========================================================================
*/
/*!
* 
* @brief
* 
* @param[in] pointer to config context handle, pointer to eeprom dev handle pointer
*
* 
*/
static bl_error_boot_type boot_eeprom_dev_open(const boot_handle config_context_handle,
                                               boot_handle * boot_handle_ptr)
{
  bl_error_boot_type error = BL_ERR_NONE;
  eeprom_device_handle * eeprom_dev_handle = NULL;
  boot_memory_mgr_if_type * mem_if = NULL;
  EEPROM_STATUS eeprom_status = EEPROM_DEVICE_DONE;
 
  
  /* Verify pointers */
  if((config_context_handle == NULL) ||
     (boot_handle_ptr == NULL))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }
  

  /* Get memory manager interface from config context */
  error = boot_config_context_get_ptr(config_context_handle,
                                      CONFIG_CONTEXT_MEMORY_MGR_INTERFACE,
                                      (void **)&mem_if);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }

  if(mem_if == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }


  /* Malloc memory to hold eeprom device handle */
  error = mem_if->malloc(sizeof(eeprom_device_handle),
                         (void *)&eeprom_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }
  
  if(eeprom_dev_handle == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_MEMORY_ALLOC_FAIL);
    goto exit;
  }

  
  /* Initalize the eeprom device handle */
  _init(eeprom_dev_handle);


  /* Store memory interface in eeprom device handle */
  eeprom_dev_handle->mem_if = mem_if;

  /* Get boot statistics interface from config context */
  error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_BOOT_STATS_INTERFACE, (void **)&eeprom_dev_handle->boot_stats_if);
  if(error != BL_ERR_NONE)
  {
    goto free_and_exit;
  }

  if(eeprom_dev_handle->boot_stats_if == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }


  /* Get eeprom driver interface */
  error = boot_config_context_get_ptr(config_context_handle,
                                      CONFIG_CONTEXT_EEPROM_INTERFACE,
                                      (void **)&eeprom_dev_handle->eeprom_if);
  if(error != BL_ERR_NONE)
  {
    goto free_and_exit;
  }

  if(eeprom_dev_handle->eeprom_if == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }


  /* Open eeprom */
  eeprom_status = eeprom_dev_handle->eeprom_if->eeprom_open(EEPROM_DEVICE_ID_CDT,
                                                            &eeprom_dev_handle->eeprom_handle);
  if (eeprom_status != EEPROM_DEVICE_DONE)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }
  

  /* Get eeprom information */
  eeprom_status =
    eeprom_dev_handle->eeprom_if->eeprom_get_info(eeprom_dev_handle->eeprom_handle,
                                                  &eeprom_dev_handle->eeprom_info);
  if (eeprom_status != EEPROM_DEVICE_DONE)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }

    
  /* Return pointer to new eeprom device handle created */
  *boot_handle_ptr = (boot_handle)eeprom_dev_handle;
  

 free_and_exit:
  /* If error is not BL_ERR_NONE then free memory. */
  if (error != BL_ERR_NONE)
  {
    mem_if->free(eeprom_dev_handle);
  }


 exit:
  return error;
}


/*=========================================================================

**  Function :  boot_eeprom_dev_read

** ==========================================================================
*/
/*!
* 
* @brief
*   Read from eeprom device
* 
* @param[in] eeprom dev handle, pointer to destination, source offset,
* number of bytes to read
* 
*/
static bl_error_boot_type boot_eeprom_dev_read(const boot_handle media_handle,
                                               void * ram_addr,
                                               uint64 src_offset,
                                               uint32 bytes_to_read)
{
  bl_error_boot_type error = BL_ERR_NONE;
  eeprom_device_handle * eeprom_dev_handle = NULL;
  EEPROM_STATUS eeprom_status = EEPROM_DEVICE_DONE;
  boot_edk2_cache_if_type * edk2_cache_if = NULL;


  /* Verify arguments passed */
  if ((media_handle == NULL) ||
      (ram_addr == NULL) ||
      (bytes_to_read == 0))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Assign validated pointers */
  eeprom_dev_handle = (eeprom_device_handle *)media_handle;

  
  /* Validate eeprom device handle entries */
  error = _handle_check(eeprom_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }

  /* Obtain EDK2 cache interface */
  error = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_EDK2_CACHE_INTERFACE, (void **)&edk2_cache_if);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }

  if(edk2_cache_if == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }

  /* Mark operation start in boot statistics */
  eeprom_dev_handle->boot_stats_if->statistics_start();

  /* Read from EEPROM */
  eeprom_status = eeprom_dev_handle->eeprom_if->eeprom_read(eeprom_dev_handle->eeprom_handle,
                                                            src_offset,
                                                            bytes_to_read,
                                                            ram_addr);
  if (eeprom_status != EEPROM_DEVICE_DONE)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }
  
  /* Invalidate cache to avoid cache hit on stale data. */
  edk2_cache_if->InvalidateDataCacheRange((void *)ram_addr, bytes_to_read);
  
  /* Mark operation end and how many bytes read in boot statistics */
  eeprom_dev_handle->boot_stats_if->statistics_stop(bytes_to_read);

 exit:
  return error;
}


/*=========================================================================

**  Function :  boot_eeprom_dev_write

** ==========================================================================
*/
/*!
* 
* @brief
*   Write to eeprom device
* 
* @param[in] eeprom dev handle, pointer to source, source offset,
* number of bytes to write
* 
*/
static bl_error_boot_type boot_eeprom_dev_write(const boot_handle boot_handle,
                                                void * ram_addr,
                                                uint64 dst_offset,
                                               uint32 bytes_to_write)
{
  bl_error_boot_type error = BL_ERR_NONE;
  eeprom_device_handle * eeprom_dev_handle = NULL;
  EEPROM_STATUS eeprom_status = EEPROM_DEVICE_DONE;
  

  /* Verify arguments passed */
  if ((boot_handle == NULL) ||
      (ram_addr == NULL) ||
      (bytes_to_write == 0))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Assign validated pointers */
  eeprom_dev_handle = (eeprom_device_handle *)boot_handle;

  
  /* Validate eeprom device handle entries */
  error = _handle_check(eeprom_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }

  
  /* Write to EEPROM */
  eeprom_status = eeprom_dev_handle->eeprom_if->eeprom_write(eeprom_dev_handle->eeprom_handle,
                                                             dst_offset,
                                                             bytes_to_write,
                                                             ram_addr);
  if (eeprom_status != EEPROM_DEVICE_DONE)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }


 exit:
  return error;
}


/*=========================================================================

**  Function :  boot_eeprom_dev_close

** ==========================================================================
*/
/*!
* 
* @brief
* 
* @param[in] eeprom dev handle
* 
*/
static bl_error_boot_type boot_eeprom_dev_close(const boot_handle boot_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  eeprom_device_handle * eeprom_dev_handle = NULL;
  boot_memory_mgr_if_type * mem_if;

  
  /* Verify arguments passed */
  if (boot_handle == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Assign validated eeprom device handle pointer */
  eeprom_dev_handle = (eeprom_device_handle *)boot_handle;


  /* Validate eeprom device handle entries */
  error = _handle_check(eeprom_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }


  /* Assign validated memory interface pointer */
  mem_if = eeprom_dev_handle->mem_if;

  
  /* Clear the eeprom device handle */
  memset((void *)eeprom_dev_handle,
         0,
         sizeof(eeprom_device_handle));
  
 
  /* Free handle memory */  
  error = mem_if->free(eeprom_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }

  
 exit:
  return error;
}


/*=========================================================================

**  Function :  boot_eeprom_dev_hw_init

** ==========================================================================
*/
/*!
* 
* @brief
*   Function to initialize an eeprom device
* 
* @param[in] config context handle
*
* 
*/
static bl_error_boot_type boot_eeprom_dev_hw_init(const boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_clk_if_type * clock_if = NULL;


  if(!boot_eeprom_dev_is_hw_initialized)
  {
    /* Validate pointers */
    if (config_context_handle == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROM_DEV, BL_ERR_NULL_PTR_PASSED);
      goto exit;    
    }


    /* Acquire and validate clock interface */
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_CLK_INTERFACE, (void **)&clock_if);
    if (return_status != BL_ERR_NONE)
    {
      goto exit;
    }

    if (clock_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_EEPROM_DEV, BL_ERR_NULL_PTR_PASSED);
      goto exit;
    }


    /* Enable I2C clocks */
    clock_if->init_group("i2c");
    boot_eeprom_dev_is_hw_initialized = TRUE;
  }

 exit:
  return return_status;
}


/*=========================================================================

**  Function :  boot_eeprom_dev_hw_deinit

** ==========================================================================
*/
/*!
* 
* @brief
*   Function to de-initialize an eeprom device
* 
* @param[in] config context handle
*
* 
*/
static bl_error_boot_type boot_eeprom_dev_hw_deinit(const boot_handle config_context_handle)
{
  /*if(boot_eeprom_dev_is_hw_initialized == TRUE)
  {
    //de-init hw logic
    boot_eeprom_dev_is_hw_initialized = FALSE;
  }*/
  return BL_ERR_NONE;
}


/*=========================================================================

**  Function :  boot_eeprom_dev_async_read

** ==========================================================================
*/
/*!
* 
* @brief
*   Async read from eeprom device
* 
* @param[in] eeprom dev handle, pointer to destination, source offset,
* number of bytes to read
* 
*/
static bl_error_boot_type boot_eeprom_dev_async_read(const boot_handle boot_handle,
                                                     void * ram_addr,
                                                     uint64 src_offset,
                                                     uint32 bytes_to_read)
{
  return BL_ERR_FEATURE_NOT_SUPPORTED;
}


/*=========================================================================

**  Function :  boot_eeprom_dev_async_poll

** ==========================================================================
*/
/*!
* 
* @brief
*   Async read complete polling check
* 
* @param[in] eeprom dev handle, pointer to unknown
* 
*/
static bl_error_boot_type boot_eeprom_dev_async_poll(const boot_handle boot_handle,
                                                     uint8 * unused)
{
  return BL_ERR_FEATURE_NOT_SUPPORTED;
}


/*=========================================================================

**  Function :  boot_eeprom_dev_get_interface

** ==========================================================================
*/
/*!
* 
* @brief
*   hook up the eeprom dev apis to media interface
* 
* @param[in] pointer to boot_media_interface_if_type
* 
*/
bl_error_boot_type boot_eeprom_dev_get_interface(void *media_interface_if)
{
  bl_error_boot_type error = BL_ERR_NONE;
  

  /* Verify arguments */
  if(media_interface_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_EEPROMDEV, BL_ERR_INVALID_PARAMETER);
  }
  

  /* Assign apis */
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_init = boot_eeprom_dev_hw_init;
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_deinit = boot_eeprom_dev_hw_deinit;
  ((boot_media_interface_if_type *)media_interface_if)->open = boot_eeprom_dev_open;
  ((boot_media_interface_if_type *)media_interface_if)->close = boot_eeprom_dev_close;
  ((boot_media_interface_if_type *)media_interface_if)->read = boot_eeprom_dev_read;
  ((boot_media_interface_if_type *)media_interface_if)->write = boot_eeprom_dev_write;
  ((boot_media_interface_if_type *)media_interface_if)->async_read = boot_eeprom_dev_async_read;
  ((boot_media_interface_if_type *)media_interface_if)->async_read_poll = boot_eeprom_dev_async_poll;


  return error;
}
