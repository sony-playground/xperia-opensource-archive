/*=============================================================================

                     Boot hfat device

GENERAL DESCRIPTION
  HFAT device media interface layer APIs

Copyright 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
07/01/21   ds           media ioctl changes
02/19/21   vk           Initial revision.
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <string.h>
#include "boot_hfat_dev.h"
#include "boot_memory_mgr_if.h"
#include "boot_config_context.h"

/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
/* hfat device handle ID */
#define HDEV 0x48444556


// HFAT device handle
typedef struct boot_hfat_dev_obj
{
  uint32 id;
}hfat_device_handle;


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
*   intialize the hfat dev handle.
* 
* @param[in] pointer to hfat dev handle
* 
*/
static bl_error_boot_type _init(hfat_device_handle * hfat_dev_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;

  if (hfat_dev_handle == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_HFATDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }

  /* Clear hfat device handle */
  memset((void *)hfat_dev_handle, 0, sizeof(hfat_device_handle));
  
  /* Populate id */
  hfat_dev_handle->id = HDEV;

exit:
  return error;
}


/*=========================================================================

**  Function :  _handle_check

** ==========================================================================
*/
/*!
* 
* @brief
*   Sanitize the hfat device handle.
* 
* @param[in] hfat device handle
* 
*/
static bl_error_boot_type _handle_check(hfat_device_handle * hfat_dev_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;

  /* Verify hfat device handle pointer */
  if (hfat_dev_handle == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_HFATDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Verify id */
  if (hfat_dev_handle->id != HDEV)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_HFATDEV, BL_ERR_INVALID_HANDLE);
    goto exit;
  }

#if ENABLE_TRUE_HFAT_DEV //TODO: FIXME
  /* Verify handle parameters */
  if ((hfat_dev_handle->partition_id == NULL) ||
      (hfat_dev_handle->mem_if == NULL) ||
      (hfat_dev_handle->boot_stats_if == NULL) )
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_HFATDEV, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }
#endif
    
 exit:
  return error;
}


/*=========================================================================

**  Function :  boot_hfat_dev_open

** ==========================================================================
*/
/*!
* 
* @brief
*   Function to get coldplug handle and return the block dev handle
*   to client.
* 
* @param[in] pointer to config context handle, pointer to hfat dev handle pointer
*
* 
*/
static bl_error_boot_type boot_hfat_dev_open(const boot_handle config_context_handle,
                                             boot_handle * boot_handle_ptr)
{
  bl_error_boot_type error = BL_ERR_NONE;
  return error;
}


/*=========================================================================

**  Function :  boot_hfat_dev_read

** ==========================================================================
*/
/*!
* 
* @brief
*   Read from page based flash device
* 
* @param[in] hfat dev handle, pointer to destination, source offset,
* number of bytes to read
* 
*/
static bl_error_boot_type boot_hfat_dev_read(const boot_handle boot_handle,
                                             void * ram_addr,
                                             uint64 src_offset,
                                             uint32 bytes_to_read)
{
  return BL_ERR_NONE;
}


/*=========================================================================

**  Function :  boot_hfat_dev_write

** ==========================================================================
*/
/*!
* 
* @brief
*   Write to page based flash device
* 
* @param[in] hfat dev handle, pointer to destination, source offset,
* number of bytes to write
* 
*/
static bl_error_boot_type boot_hfat_dev_write(const boot_handle boot_handle,
                                              void * ram_addr,
                                              uint64 dst_offset,
                                              uint32 bytes_to_write)
{
  return BL_ERR_NONE;
}


/*=========================================================================

**  Function :  boot_hfat_dev_close

** ==========================================================================
*/
/*!
* 
* @brief
*   get the device attributes for coldplug device
* 
* @param[in] hfat dev handle
* 
*/
static bl_error_boot_type boot_hfat_dev_close(const boot_handle boot_handle)
{
  return BL_ERR_NONE;
}


/*=========================================================================

**  Function :  boot_hfat_dev_hw_init

** ==========================================================================
*/
/*!
* 
* @brief
*   Function to initialize a page based flash device
* 
* @param[in] config context handle
*
* 
*/
static bl_error_boot_type boot_hfat_dev_hw_init(const boot_handle config_context_handle)
{
  return BL_ERR_NONE;
}


/*=========================================================================

**  Function :  boot_hfat_dev_hw_deinit

** ==========================================================================
*/
/*!
* 
* @brief
*   Function to de-initialize a page based flash device
* 
* @param[in] config context handle
*
* 
*/
static bl_error_boot_type boot_hfat_dev_hw_deinit(const boot_handle config_context_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  return error;
}

/*=========================================================================

**  Function :  boot_hfat_dev_ioctl

** ==========================================================================
*/
/*!
*
* @brief
*   control hfat_dev params using ioctl
*
* @param[in] command, in ptr, in size, out ptr, out size ptr
*
*/
static bl_error_boot_type boot_hfat_dev_ioctl(uint32 cmd, void* in, uintnt in_sz, void* out, uintnt* out_sz)
{
  return BL_ERR_NONE;
}


/*=========================================================================

**  Function :  boot_hfat_dev_get_interface

** ==========================================================================
*/
/*!
* 
* @brief
*   hook up the hfat dev apis to media interface
* 
* @param[in] pointer to boot_media_interface_if_type
* 
*/
bl_error_boot_type boot_hfat_dev_get_interface(void *media_interface_if)
{
  bl_error_boot_type error = BL_ERR_NONE;
  

  /* Verify arguments */
  if(media_interface_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_HFATDEV, BL_ERR_INVALID_PARAMETER);
  }
  
#ifdef ENABLE_TRUE_HFAT_DEV //TODO: FIXME 
  /* Assign apis */
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_init = boot_hfat_dev_hw_init;
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_deinit = boot_hfat_dev_hw_deinit;
  ((boot_media_interface_if_type *)media_interface_if)->open = boot_hfat_dev_open;
  ((boot_media_interface_if_type *)media_interface_if)->close = boot_hfat_dev_close;
  ((boot_media_interface_if_type *)media_interface_if)->read = boot_hfat_dev_read;
  ((boot_media_interface_if_type *)media_interface_if)->write = boot_hfat_dev_write;
  ((boot_media_interface_if_type *)media_interface_if)->async_read = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->async_read_poll = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->ioctl = boot_page_dev_ioctl;
#endif

  ((boot_media_interface_if_type *)media_interface_if)->media_hw_init = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_deinit = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->open = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->close = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->read = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->write = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->async_read = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->async_read_poll = NULL;
    ((boot_media_interface_if_type *)media_interface_if)->ioctl = NULL;

  return error;
}
