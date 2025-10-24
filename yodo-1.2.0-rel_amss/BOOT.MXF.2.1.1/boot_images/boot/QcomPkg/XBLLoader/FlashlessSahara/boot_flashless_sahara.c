/*=============================================================================

                     Boot Flashless Sahara

GENERAL DESCRIPTION
  This file contains the implementation for boot layer that provides the interface
  to Sahara protocol.

Copyright 2020-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
07/02/22   ck           Added CLEAR_ERROR_CODE to boot_flashless_sahara_open
05/18/22   rama         Move dal_if to mem_if
02/11/22   rama         Add support for enabling sahara logging option 
01/25/22   ck           Added initialization of sahara dispatch table in hw init
07/09/21   rhy          Handling close for USB disconnect issue
07/01/21   ds           media ioctl changes
06/18/21   yps          Ignore return value of boot_flashless_sahara_close in open function
05/24/21   rama         changes to make boot_flashless_sahara_hw_init and deinit recallable
04/27/21   rhy          Changing boot_flashless_sahara_async_read to not supported
11/23/20   rhy          Added Sahara Status map functionalities
11/11/20   rhy          Renamed is_dump_support to is_ramdump_allowed
09/09/20   ck           Added boot statistics
07/02/20   rhy          Added Sahara Command handler functionalities
05/12/20   rhy          Dalsys uncache malloc for buffers
09/29/19   rhy          Initial revision.
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_flashless_sahara.h"
#include "boot_config_context.h"
#include "boot_memory_mgr_if.h"
#include "boot_statistics_if.h"
#include "boot_flashless_sahara_internal.h"
#include "boot_sahara.h"
#include "boot_sahara_internal.h"
#include "boot_sahara_status_map_if.h"
#include "boot_ddr_if.h"
#include "boot_sahara_dispatch_tbl.h"
#include "boot_sahara_logging.h"
#include "boot_dal_if.h"

// This is the avoid getting table from boot config
//#define LOCALTABLE_DEFINITION   0

/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
//Flashless device handle ID
#define SAHARA_DEV_ID 0x53414841

static bl_error_boot_type _init_boot_sahara_info(flashless_device_handle *);
static bl_error_boot_type _init_boot_sahara_data(boot_handle, boot_sahara_data *);
static void _init_boot_sahara_callback_parameters(boot_sahara_callback_parameters *);
static bl_error_boot_type _init_boot_sahara_cmd_exec_data(boot_handle, boot_sahara_cmd_exec_data *);
static bl_error_boot_type _init_boot_sahara_mem_debug_handle(boot_handle, boot_sahara_mem_debug_handle *);
static bl_error_boot_type _deinit_boot_sahara_info(flashless_device_handle *);
static bl_error_boot_type _alloc_buffer(boot_handle, uint8 **, unsigned int, DALHEAP_MEM_TYPE);
static bl_error_boot_type _free_buffer(boot_handle, uint8 **);

static bl_error_boot_type boot_flashless_sahara_close(const boot_handle handle);

static boot_boolean boot_flashless_sahara_is_hw_initialized = FALSE;

/*=============================================================================

FUNCTION DEFINITIONS

=============================================================================*/
/*=========================================================================

**  Function :  _init_handle

** ==========================================================================
*/
/*!
*
* @brief
*   intialize the block dev handle.
*
* @param[in] pointer to block dev handle
*
*/
static void _init_handle(   boot_handle config_context_handle,
                            flashless_device_handle *handle,
                            boot_memory_mgr_if_type *mem_if,
                            boot_statistics_if_type *stats_if)
{
  memset((void *)handle, 0, sizeof(flashless_device_handle));

  /* Setting boot handle commonm type */
  (handle->handle_data).id =                      SAHARA_DEV_ID;
  (handle->handle_data).config_context_handle =   config_context_handle;

  handle->mem_if           =                      mem_if;
  handle->stats_if         =                      stats_if;
  handle->is_last_image    =                      FALSE;
}

/*=========================================================================

**  Function :  _init_boot_sahara_info

** ==========================================================================
*/
/*!
*
* @brief
*   intialize boot_sahara_info.
*
* @param[in] pointer to block dev handle
*
*/
static bl_error_boot_type _init_boot_sahara_info(flashless_device_handle *handle)
{
  bl_error_boot_type error =              BL_ERR_NONE;

  if (handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }

  boot_sahara_dispatch_tbl *sahara_dispatch_tbl_ptr =     NULL;
  boot_handle config_context_handle =     (handle->handle_data).config_context_handle;
  boot_sahara_command_handler_if* sahara_cmd_handler_ptr = NULL;

  uint8 **sahara_packet_buffer_ptr = &(((handle->boot_handle_sahara_info).sahara_data).sahara_packet_buffer);
  uint8 **sahara_cmd_temp_data_resp_buf_ptr = &(((handle->boot_handle_sahara_info).sahara_cmd_data).sahara_cmd_temp_data_resp_buf);
  uint8 **sahara_mem_debug_buffer_ptr = &(((handle->boot_handle_sahara_info).mem_debug_handle).sahara_mem_debug_buffer);

  do
  {
    /* STEP 1: Initialize boot_sahara_data */
    error = _init_boot_sahara_data(config_context_handle, &((handle->boot_handle_sahara_info).sahara_data));
    if (error != BL_ERR_NONE)
    {
      break;
    }

    /* STEP 2: Initialize boot_sahara_callback_parameters */
    _init_boot_sahara_callback_parameters(&((handle->boot_handle_sahara_info).sahara_cb_parameters));

    /* STEP 3: Get Sahara Command Handler Table */
    error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SAHARA_COMMAND_HANDLER_TBL, (void **)&sahara_cmd_handler_ptr);
    if (error != BL_ERR_NONE)
    {
      return error;
    }

    if (sahara_cmd_handler_ptr == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    (handle->boot_handle_sahara_info).sahara_cmd_handler_tbl = sahara_cmd_handler_ptr;

    /* STEP 4: Initialize boot_sahara_cmd_exec_data */
    error = _init_boot_sahara_cmd_exec_data(config_context_handle, &((handle->boot_handle_sahara_info).sahara_cmd_data));
    if (error != BL_ERR_NONE)
    {
      break;
    }

    /* STEP 5: Get Sahara Dispatch Table */
    error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SAHARA_DISPATCH_TBL, (void **)&sahara_dispatch_tbl_ptr);
    if (error != BL_ERR_NONE)
    {
      return error;
    }

    if (sahara_dispatch_tbl_ptr == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    (handle->boot_handle_sahara_info).dispatch_tbl = sahara_dispatch_tbl_ptr;

    /* STEP 6: Boot_sahara_mem_debug_handle */
    error = _init_boot_sahara_mem_debug_handle(config_context_handle, &((handle->boot_handle_sahara_info).mem_debug_handle));

  } while (FALSE);

  if (error != BL_ERR_NONE)
  {
    /* Free Sahara Data, Command and Memory Debug buffer in case of failure */
    _free_buffer(config_context_handle, sahara_packet_buffer_ptr);
    _free_buffer(config_context_handle, sahara_cmd_temp_data_resp_buf_ptr);
    _free_buffer(config_context_handle, sahara_mem_debug_buffer_ptr);
  }
  return error;
}

/*=========================================================================

**  Function :  _init_boot_sahara_mem_debug_handle

** ==========================================================================
*/
/*!
*
* @brief
*   intialize the boot_sahara_mem_debug_handle and allocate memory debug.
*
* @param[in] pointer to block dev handle
*
*/
static bl_error_boot_type _init_boot_sahara_mem_debug_handle( const boot_handle config_context_handle,
    boot_sahara_mem_debug_handle* mem_debug_handle_ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  ramdump_table_if *sahara_mem_debug_tbl_ptr =   NULL;
  boot_handle ramdump_table_handle = NULL;

  if (config_context_handle == NULL || mem_debug_handle_ptr == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }
  do
  {
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void **)&sahara_mem_debug_tbl_ptr);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (sahara_mem_debug_tbl_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Get ramdump table handle. It can return NULL */
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_HANDLE, (void **)&ramdump_table_handle);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* initialize Sahara Memory Debug Table and initialize mem_debug_table */
    mem_debug_handle_ptr->mem_debug_tbl = sahara_mem_debug_tbl_ptr;
    mem_debug_handle_ptr->ramdump_table_handle = (void *)ramdump_table_handle;

    return_status = _alloc_buffer(config_context_handle, &(mem_debug_handle_ptr->sahara_mem_debug_buffer),
                                  SAHARA_MAX_MEMORY_DATA_SIZE_IN_BYTES, DALHEAP_UNCACHED);
  } while (FALSE);

  return return_status;
}


/*=========================================================================

**  Function :  _init_boot_sahara_data

** ==========================================================================
*/
/*!
*
* @brief
*   intialize the boot_sahara_data.
*
* @param[in] pointer to block dev handle
*
*/
static bl_error_boot_type _init_boot_sahara_data( const boot_handle config_context_handle,
    boot_sahara_data *boot_sahara_data_ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  if (boot_sahara_data_ptr == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }

  boot_sahara_data_ptr->revision =                        SAHARA_INTERFACE_VERSION;
  boot_sahara_data_ptr->image_id =                        0;
  boot_sahara_data_ptr->sahara_state =                    SAHARA_STATE_ENTRY;
  boot_sahara_data_ptr->sahara_done =                     FALSE;
  boot_sahara_data_ptr->status =                          SAHARA_STATUS_SUCCESS;
  boot_sahara_data_ptr->sahara_mode =                     SAHARA_MODE_IMAGE_TX_PENDING;
  boot_sahara_data_ptr->sahara_major_version =            SAHARA_VERSION_MAJOR;
  boot_sahara_data_ptr->sahara_major_version_supported =  SAHARA_VERSION_MAJOR_SUPPORTED;
  boot_sahara_data_ptr->sahara_mem_debug_enabled =        FALSE;

  return_status = _alloc_buffer(config_context_handle, &boot_sahara_data_ptr->sahara_packet_buffer,
                                SAHARA_MAX_PACKET_SIZE_IN_BYTES, DALHEAP_UNCACHED);

  return return_status;
}

/*=========================================================================

**  Function :  _init_boot_sahara_callback_parameters

** ==========================================================================
*/
/*!
*
* @brief
*   intialize the boot_sahara_callback_parameters.
*
* @param[in] pointer to block dev handle
*
*/
static void _init_boot_sahara_callback_parameters(boot_sahara_callback_parameters *boot_sahara_callback_parameters_ptr)
{
  boot_sahara_callback_parameters_ptr->sahara_rx_bytes_read =  0;
  boot_sahara_callback_parameters_ptr->sahara_rx_err_code =    BULK_SUCCESS;
  boot_sahara_callback_parameters_ptr->sahara_rx_complete =    FALSE;
  boot_sahara_callback_parameters_ptr->sahara_tx_bytes_read = 0;
  boot_sahara_callback_parameters_ptr->sahara_tx_err_code =    BULK_SUCCESS;
  boot_sahara_callback_parameters_ptr->sahara_tx_complete =    FALSE;

}

/*=========================================================================

**  Function :  _init_boot_sahara_cmd_exec_data

** ==========================================================================
*/
/*!
*
* @brief
*   intialize the boot_sahara_helper_tbl.
*
* @param[in] pointer to block dev handle
*
*/
static bl_error_boot_type _init_boot_sahara_cmd_exec_data(const boot_handle config_context_handle,
    boot_sahara_cmd_exec_data *boot_sahara_cmd_exec_data_ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  if (boot_sahara_cmd_exec_data_ptr == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }

  boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data_length =        0;
  boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_client_command =     0;
  boot_sahara_cmd_exec_data_ptr->sahara_cmd_exec_data =               NULL;

  return_status = _alloc_buffer(config_context_handle, &boot_sahara_cmd_exec_data_ptr->sahara_cmd_temp_data_resp_buf,
                                SAHARA_MAX_CMD_TEMP_DATA_RESP_BUF_IN_BYTES, DALHEAP_UNCACHED);

  return return_status;
}

/*=========================================================================

**  Function :  _alloc_buffer

** ==========================================================================
*/
/*!
*
* @brief
*   Allocate buffer.
*
* @param[in] pointer to block dev handle, size, dalheap_mem_type
*
*/
static bl_error_boot_type _alloc_buffer(const boot_handle config_context_handle, uint8 **boot_buffer_ptr,
                                        unsigned int size, DALHEAP_MEM_TYPE memType)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  if (boot_buffer_ptr == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }

  boot_memory_mgr_if_type *mem_if = NULL;

  do
  {
    /* Malloc Uncache memory for Command exec packet buffer */
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }
    if(memType == DALHEAP_ANY)
      return_status = mem_if->malloc(size, (void **)boot_buffer_ptr);
    else if(memType == DALHEAP_UNCACHED)
      return_status = mem_if->malloc_uncached(size, (void **)boot_buffer_ptr);

    if ((return_status != BL_ERR_NONE) || (*boot_buffer_ptr == NULL))
    {
      break;
    }

    memset((void *)(*boot_buffer_ptr), 0x0, size);
  } while (FALSE);

  return return_status;
}

/*=========================================================================

**  Function :  _free_buffer

** ==========================================================================
*/
/*!
*
* @brief
*   Free the  buffer
*
* @param[in] pointer to block dev handle
*
*/
static bl_error_boot_type _free_buffer( const boot_handle config_context_handle,
                                        uint8 **boot_buffer_ptr)
{
  boot_memory_mgr_if_type *mem_if = NULL;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if (boot_buffer_ptr == NULL || (*boot_buffer_ptr)==NULL)
    {
      /* Skip free() if not allocated */
      break;
    }

    /* Free packet buffer */
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    return_status = mem_if->free((void *)(*boot_buffer_ptr));
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    *boot_buffer_ptr = NULL;

  } while (FALSE);

  return return_status;
}

/*=========================================================================

**  Function :  _deinit_boot_sahara_info

** ==========================================================================
*/
/*!
*
* @brief
*   intialize boot_sahara_info.
*
* @param[in] pointer to block dev handle
*
*/
static bl_error_boot_type _deinit_boot_sahara_info(flashless_device_handle *handle)
{
  bl_error_boot_type error = BL_ERR_NONE;

  if (handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }

  boot_handle config_context_handle = (handle->handle_data).config_context_handle;

  uint8 **sahara_packet_buffer_ptr = &(((handle->boot_handle_sahara_info).sahara_data).sahara_packet_buffer);
  uint8 **sahara_cmd_temp_data_resp_buf_ptr = &(((handle->boot_handle_sahara_info).sahara_cmd_data).sahara_cmd_temp_data_resp_buf);
  uint8 **sahara_mem_debug_buffer_ptr = &(((handle->boot_handle_sahara_info).mem_debug_handle).sahara_mem_debug_buffer);

  do
  {
    /* STEP 1: Free boot_sahara_data */
    error = _free_buffer(config_context_handle, sahara_packet_buffer_ptr);
    if (error != BL_ERR_NONE)
    {
      break;
    }

    /* STEP 2: Free boot_sahara_cmd_exec_data */
    error = _free_buffer(config_context_handle, sahara_cmd_temp_data_resp_buf_ptr);
    if (error != BL_ERR_NONE)
    {
      break;
    }

    /* STEP 3: Free sahara_mem_debug_buffer */
    error = _free_buffer(config_context_handle, sahara_mem_debug_buffer_ptr);
    if (error != BL_ERR_NONE)
    {
      break;
    }

  } while (FALSE);

  return error;
}

/*=========================================================================

**  Function :  _handle_check

** ==========================================================================
*/
/*!
*
* @brief
*   Sanitize the block dev handle.
*
* @param[in] block dev handle
*
*/
static bl_error_boot_type _handle_check(boot_handle handle)
{
  flashless_device_handle * handle_ptr = NULL;


  /* Validate pointer */
  if (handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }

  /* Assign pointer after validation */
  handle_ptr = (flashless_device_handle *)handle;

  if (handle_ptr->handle_data.id != SAHARA_DEV_ID)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_HANDLE);
  }

  if (handle_ptr->mem_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_PARAMETER);
  }

  if (handle_ptr->stats_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_PARAMETER);
  }

  return BL_ERR_NONE;
}

/*=========================================================================

**  Function :  boot_flashless_sahara_hw_init

** ==========================================================================
*/
/*!
*
* @brief
*   Function to initialize block based flash device
*
* @param[in] config context handle
*
*
*/
static bl_error_boot_type boot_flashless_sahara_hw_init(const boot_handle config_context_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  boot_sahara_dispatch_tbl *sahara_dispatch_tbl_ptr = NULL;
  boot_memory_mgr_if_type * mem_if = NULL;


  if(!boot_flashless_sahara_is_hw_initialized)
  {
    /* Validate pointers */
    if (NULL == config_context_handle)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_PARAMETER);
      goto exit;
    }


    /* Obtain memory manager interface */
    error = boot_config_context_get_ptr(config_context_handle,
                                        CONFIG_CONTEXT_MEMORY_MGR_INTERFACE,
                                        (void **)&mem_if);
    if (error != BL_ERR_NONE)
    {
      goto exit;
    }

    if (mem_if == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }


    /* Populate the sahara dispatch table */
    /* Malloc dispatch table memory */
    error = mem_if->malloc(sizeof(boot_sahara_dispatch_tbl),
                           (void *)&sahara_dispatch_tbl_ptr);
    if (error != BL_ERR_NONE)
    {
      goto exit;
    }

    /* Assign dispatch table to config context */
    error = boot_config_context_set_ptr(config_context_handle,
                                        CONFIG_CONTEXT_SAHARA_DISPATCH_TBL,
                                        (void *)(sahara_dispatch_tbl_ptr));

    if (error != BL_ERR_NONE)
    {
      goto exit;
    }

    /* Initialize dispatch table */
    error = boot_sahara_dispatch_table_init(config_context_handle);
    if (error != BL_ERR_NONE)
    {
      goto exit;
    }

    /* Enumerate the Transport layer */
    error = boot_sahara_enumeration_init(sahara_dispatch_tbl_ptr);
    if (BL_ERR_NONE != error)
    {
      goto exit;
    }

    boot_flashless_sahara_is_hw_initialized = TRUE;
  }


 exit:
  return error;
}


/*=========================================================================

**  Function :  boot_flashless_sahara_open

** ==========================================================================
*/
/*!
*
* @brief
*   Function to get coldplug handle and return the block dev handle
*   to client.
*
*   Fill Handle data struture
*   STEP 2: Fill boot_sahara_info
*   STEP 3: Send Hello packet and handle for Commands or Mem Debug before exiting _open()
* @param[in] pointer to config context handle, pointer to block dev handle pointer
*
*
*/
static bl_error_boot_type boot_flashless_sahara_open(const boot_handle config_context_handle, boot_handle *handle_ptr)
{
  bl_error_boot_type error =                  BL_ERR_NONE;
  flashless_device_handle *handle =           NULL;
  boot_memory_mgr_if_type *mem_if =           NULL;
  boot_statistics_if_type *stats_if =         NULL;
  boot_sahara_status status =                 SAHARA_STATUS_SUCCESS;
  uint8 *image_id =                           NULL;
  boot_sahara_info *boot_sahara_info_ptr =    NULL;
  boot_boolean dload_cookie =                 FALSE;
  boot_boolean dump_supported =               FALSE;
  ramdump_table_if *ramdump_table_if_ptr =    NULL;
  boot_ddr_if_type *ddr_if =                  NULL;
  boolean ddr_training_dump_allowed =         FALSE;


  if (config_context_handle == NULL || handle_ptr == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_PARAMETER);
  }

  /* Get DDR interface */
  error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_DDR_INTERFACE, (void **)&ddr_if);
  if (error != BL_ERR_NONE)
  {
    ddr_if = NULL;
    CLEAR_ERROR_CODE;
    //return error;
  }

  if (ddr_if == NULL)
  {
    if (error == BL_ERR_NONE)
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_PARAMETER);
    }
  }


  /* Get memory interface */
  error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
  if (error != BL_ERR_NONE)
  {
    return error;
  }

  if (mem_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INTERFACE_FAILURE);
  }

  error = mem_if->malloc(sizeof(flashless_device_handle), (void *)&handle);
  if (error != BL_ERR_NONE)
  {
    return error;
  }
  if (handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_MEMORY_ALLOC_FAIL);
  }

  error = boot_sahara_logger_init(config_context_handle);
  if(error != BL_ERR_NONE)
  {
    return error;
  }
  /* Get boot statistics interface */
  error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_BOOT_STATS_INTERFACE, (void **)&stats_if);
  if (error != BL_ERR_NONE)
  {
    return error;
  }

  if (stats_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INTERFACE_FAILURE);
  }

  _init_handle(config_context_handle, handle, mem_if, stats_if);

  /* STEP 2: Fill boot_sahara_info */
  error = _init_boot_sahara_info(handle);

  if (error != BL_ERR_NONE)
  {
    return error;
  }

  error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_PARTITION_ID, (void **)&image_id);
  if (BL_ERR_NONE != error)
  {
    return error;
  }

  if (image_id == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_PARAMETER);
  }

  /* Get boot_handle_sahara_info from handle */
  boot_sahara_info_ptr = &(handle->boot_handle_sahara_info);

  /* Get ramdump_table_if from handle */
  ramdump_table_if_ptr = (boot_sahara_info_ptr->mem_debug_handle).mem_debug_tbl;

  /* Assign image_id in sahara_data */
  (boot_sahara_info_ptr->sahara_data).image_id = *image_id;

  /* Get RAM dump or Mini-dump cookie and change the mode */
  error = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_RAMDUMP_OR_MINIDUMP_COOKIE, (void *)&dload_cookie);
  if (error != BL_ERR_NONE)
  {
    return error;
  }

  /* Check the corresponding image is last image or not*/
  error = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_JUMP_FLAG, &(handle->is_last_image));
  if (BL_ERR_NONE != error)
  {
    return error;
  }
  if (ddr_if != NULL)
  {
    ddr_training_dump_allowed = ddr_if->get_ddr_dump_allowed();
  }

  if (dload_cookie)
  {
    /* Do not enter download mode if ramdump_table_if_ptr is NULL or dload cookie is not set */
    if (ramdump_table_if_ptr == NULL)
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_PARAMETER);
    }

    error = ramdump_table_if_ptr->is_ramdump_allowed(config_context_handle, &dump_supported);
    if (dump_supported == FALSE)
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_PARAMETER);
    }

    /* Enable memory debug once the dump collection support returns TRUE. By default it is FALSE */
    (boot_sahara_info_ptr->sahara_data).sahara_mem_debug_enabled = TRUE;

    (boot_sahara_info_ptr->sahara_data).sahara_mode = SAHARA_MODE_MEMORY_DEBUG;
  }
  else if (ddr_training_dump_allowed)
  {
    /* Set to Command mode if DDR Training is set to True */
    if (ddr_if != NULL)
      ddr_if->set_ddr_dump_allowed(FALSE);
    (boot_sahara_info_ptr->sahara_data).sahara_mode = SAHARA_MODE_COMMAND;
  }
  else if (handle->is_last_image)
  {
    (boot_sahara_info_ptr->sahara_data).sahara_mode = SAHARA_MODE_IMAGE_TX_COMPLETE;
  }

  *handle_ptr = (boot_handle)handle;

  /* STEP 3: Send Hello packet and handle for Commands or Mem Debug before exiting _open() */

  /* set last image in boot_sahara layer */
  boot_sahara_set_last_image(boot_sahara_info_ptr, handle->is_last_image);

  /* Sending Hello Packet */
  status = boot_sahara_entry(boot_sahara_info_ptr);

  /* Skip _close() if PIPO is performed for Memory Debug Mode */
  if(status == SAHARA_NAK_CABLE_DISCONNECT_ERROR &&
     (boot_sahara_info_ptr->sahara_data).sahara_mode == SAHARA_MODE_MEMORY_DEBUG)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_SAHARA_RAMDUMP_PIPO_RESTART);
  } 
  else if(status != SAHARA_STATUS_SUCCESS)
  {
    // call to _close
    error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, (BL_ERROR_SAHARA_NAK_INVALID_CMD+status));
  }
  else
  {
    /* Successfully open */
    goto exit;
  }


  /* If boot_sahara_entry fails, then call the close to make sure the buffers are free.
     Return the error with Sahara status.
     No need to collect the error since status is not Success 
  */
  boot_flashless_sahara_close(handle);  


 exit:
  return error;
}

/*=========================================================================

**  Function :  boot_flashless_sahara_poll

** ==========================================================================
*/
/*!
*
* @brief
*   Poll for Sahara Flashless
*
* @param[in] block dev handle, pointer to destination, source offset,
* number of bytes to read
*
*/
static bl_error_boot_type boot_flashless_sahara_poll(
  const boot_handle handle,
  uint8 *status_read)
{
  bl_error_boot_type error = BL_ERR_NONE;

  if (status_read == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }

  error = _handle_check(handle);
  if (error != BL_ERR_NONE)
  {
    return error;
  }

  flashless_device_handle *handle_ptr = (flashless_device_handle *)handle;

  boot_sahara_status status = SAHARA_STATUS_SUCCESS;

  status = boot_sahara_poll(&handle_ptr->boot_handle_sahara_info);

  if (status != SAHARA_STATUS_SUCCESS)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, (BL_ERROR_SAHARA_NAK_INVALID_CMD+status));
  }

  // TODO: This is not implemented
  *status_read = TRUE;

  return error;
}
/*=========================================================================

**  Function :  boot_flashless_sahara_async_read

** ==========================================================================
*/
/*!
*
* @brief
*   Read from flashless
*
* @param[in] block dev handle, pointer to destination, source offset,
* number of bytes to read
*
*/
static bl_error_boot_type boot_flashless_sahara_async_read(const boot_handle handle, void *ram_addr, uint64 src_offset, uint32 bytes_to_read)
{
  return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_FEATURE_NOT_SUPPORTED);
}

/*=========================================================================

**  Function :  boot_flashless_dev_read

** ==========================================================================
*/
/*!
*
* @brief
*   Read from flashless
*
* @param[in] block dev handle, pointer to destination, source offset,
* number of bytes to read
*
*/
static bl_error_boot_type boot_flashless_sahara_read(const boot_handle handle, void *ram_addr, uint64 src_offset, uint32 bytes_to_read)
{
  bl_error_boot_type error = BL_ERR_NONE;
  flashless_device_handle * handle_ptr = NULL;
  boot_sahara_status status = SAHARA_STATUS_SUCCESS;

  /* Validate pointers */
  if ((handle == NULL) ||
      (ram_addr == NULL))
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
  }

  error = _handle_check(handle);
  if(error != BL_ERR_NONE)
  { 
    return error;
  }

  /* Assign pointers after validation */
  handle_ptr = (flashless_device_handle *)handle;

  /* Mark operation start in boot statistics */
  handle_ptr->stats_if->statistics_start();

  status = boot_sahara_read(&handle_ptr->boot_handle_sahara_info,
                  ram_addr, src_offset, bytes_to_read);

  if(status != SAHARA_STATUS_SUCCESS)
  {
      return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, (BL_ERROR_SAHARA_NAK_INVALID_CMD+status));
  }

  /* Mark operation end and how many bytes read in boot statistics */
  handle_ptr->stats_if->statistics_stop(bytes_to_read);

  return error;
}

/*=========================================================================

**  Function :  boot_flashless_sahara_write

** ==========================================================================
*/
/*!
*
* @brief
*   Write from Flashless based flash device. Stub function.
*
* @param[in] block dev handle, pointer to destination, source offset,
* number of bytes to read
*
*/
static bl_error_boot_type boot_flashless_sahara_write(const boot_handle handle, void *ram_addr, uint64 dst_offset, uint32 bytes_to_write)
{
  return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_FEATURE_NOT_SUPPORTED);
}

/*=========================================================================

**  Function :  boot_flashless_sahara_close

** ==========================================================================
*/
/*!
*
* @brief
*   get the device attributes for coldplug device
*
* @param[in] block dev handle
*
*/
static bl_error_boot_type boot_flashless_sahara_close(const boot_handle handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  boot_sahara_status status = SAHARA_NAK_MAX_CODE;
  boot_sahara_status_map_handler_if *sahara_status_map_if = NULL;
  bl_error_boot_type client_error = GET_ERROR_INFO;

  do
  {
    error = _handle_check(handle);
    if (error != BL_ERR_NONE)
    {
      break;
    }

    flashless_device_handle *handle_ptr = (flashless_device_handle *)handle;


    error = boot_config_context_get_ptr((handle_ptr->handle_data).config_context_handle,
                                        CONFIG_CONTEXT_SAHARA_STATUS_MAP_INTERFACE,
                                        (void **)&sahara_status_map_if);

    if (error != BL_ERR_NONE)
    {
      break;
    }

    if (sahara_status_map_if == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    error = boot_sahara_logger_deinit((handle_ptr->handle_data).config_context_handle);
    if(error != BL_ERR_NONE)
    {
      break;
    }

    /*  Avoid mapping status (boot_sahara_status) with error (bl_error_boot_type) if status
        is SAHARA_STATUS_SUCCESS
    */
    if (((handle_ptr->boot_handle_sahara_info).sahara_data).status == SAHARA_STATUS_SUCCESS)
    {
      /* Map the bl_error_boot_type to boot_sahara_status */
      error = sahara_status_map_if->get_mapped_sahara_status(client_error,
              &status);
      if (error != BL_ERR_NONE)
      {
        break;
      }

      /* Update the status in boot sahara handle info for End of IMG TX */
      ((handle_ptr->boot_handle_sahara_info).sahara_data).status = status;
    }

    /*  If status is Cable Disconnect in Memory debug, then skip calling End of Image tx, 
        it will loop forever. Instead free the memory and return the status to uuper layers 
    */
    if(status != SAHARA_NAK_CABLE_DISCONNECT_ERROR &&
       SAHARA_MODE_MEMORY_DEBUG != ((&handle_ptr->boot_handle_sahara_info)->sahara_data).sahara_mode)
    {
      status = boot_sahara_end(&handle_ptr->boot_handle_sahara_info);
    }
        
    /* Free _sahara_packet_buffer and _sahara_cmd_temp_data_resp_buf */
    error = _deinit_boot_sahara_info(handle);
    if (error != BL_ERR_NONE)
    {
      break;
    }

    error = (((flashless_device_handle *)handle)->mem_if)->free(handle);
    if (error != BL_ERR_NONE)
    {
      break;
    }

    /*  return overwrite error_code if client_error is none and sahara status is not success */
    if (client_error == BL_ERR_NONE && status != SAHARA_STATUS_SUCCESS)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, status);
      break;
    }

  } while (FALSE);

  return error;
}

/*=========================================================================

**  Function :  boot_flashless_sahara_hw_deinit

** ==========================================================================
*/
/*!
*
* @brief
*   Write from Flashless based flash device. Stub function.
*
* @param[in] block dev handle, pointer to destination, source offset,
* number of bytes to read
*
*/
static bl_error_boot_type boot_flashless_sahara_hw_deinit(const boot_handle config_context_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  boot_sahara_dispatch_tbl *sahara_dispatch_tbl_ptr =     NULL;

  if(boot_flashless_sahara_is_hw_initialized)
  {
    if (config_context_handle == NULL)
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_PARAMETER);
    }


    error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SAHARA_DISPATCH_TBL, (void **)&sahara_dispatch_tbl_ptr);
    if (error != BL_ERR_NONE)
    {
      return error;
    }

    if (sahara_dispatch_tbl_ptr == NULL)
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INTERFACE_FAILURE);
    }

    /* Shutdown the Transport layer */
    error = boot_sahara_enumeration_deinit(sahara_dispatch_tbl_ptr);
    if (BL_ERR_NONE != error)
    {
      return error;
    }

    boot_flashless_sahara_is_hw_initialized = FALSE;
  }

  return error;
}

/*=========================================================================

**  Function :  boot_flashless_sahara_ioctl

** ==========================================================================
*/
/*!
*
* @brief
*   control flashless_sahara params using ioctl
*
* @param[in] command, in ptr, in size, out ptr, out size ptr
*
*/
static bl_error_boot_type boot_flashless_sahara_ioctl(uint32 cmd, void* in, uintnt in_sz, void* out, uintnt* out_sz)
{
  return BL_ERR_NONE;
}

/*=========================================================================

**  Function :  boot_flashless_dev_get_interface

** ==========================================================================
*/
/*!
*
* @brief
*   hook up the block dev apis to media interface
*
* @param[in] pointer to boot_media_interface_if_type
*
*/
bl_error_boot_type boot_flashless_dev_get_interface(void *media_interface_if)
{
  bl_error_boot_type error = BL_ERR_NONE;

  if (media_interface_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_PARAMETER);
  }

  ((boot_media_interface_if_type *)media_interface_if)->media_hw_init =     boot_flashless_sahara_hw_init;
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_deinit =   boot_flashless_sahara_hw_deinit;
  ((boot_media_interface_if_type *)media_interface_if)->open =              boot_flashless_sahara_open;
  ((boot_media_interface_if_type *)media_interface_if)->close =             boot_flashless_sahara_close;
  ((boot_media_interface_if_type *)media_interface_if)->read =              boot_flashless_sahara_read;
  ((boot_media_interface_if_type *)media_interface_if)->write =             boot_flashless_sahara_write;
  ((boot_media_interface_if_type *)media_interface_if)->async_read =        boot_flashless_sahara_async_read;
  ((boot_media_interface_if_type *)media_interface_if)->async_read_poll =   boot_flashless_sahara_poll;
  ((boot_media_interface_if_type *)media_interface_if)->ioctl =             boot_flashless_sahara_ioctl;
  return error;
}
