/*===========================================================================

  Boot Sahara format interface functions

  GENERAL DESCRIPTION
  Sahara format interface functions

  Copyright 2020-2022 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
  ============================================================================*/

  /*=============================================================================

                              EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when       who             what, where, why
  --------   ---         --------------------------------------------------
  03/31/22   yps         Porting change from Makena
  02/26/21   ck          Changed SCL_SBL1_OCIMEM_DATA_* to SCL_SYSTEM_IMEM_*
  02/16/20   vk          Initial revision

  ===========================================================================*/

  /*==========================================================================

                                 INCLUDE FILES

  ===========================================================================*/
#include <string.h>
#include <ramdump_format_if.h>
#include <boot_config_context.h>
#include <boot_media_interface_if.h>
#include <boot_error_if.h>
#include <boot_edk2_cache_if.h>
#include <boot_logger_if.h>
#include <boot_sahara_dispatch_tbl.h>
#include <boot_ramdump_table_if.h>
#include <boot_sahara_command_handler_if.h>
#include <boot_dload_debug.h>
#include <boot_target.h>


  /*===========================================================================

  **  Function :  _rd_sahara_deinit

  ** ==========================================================================
  */
  /*!
  *
  * @brief
  *  Initialize Command handler table
  *
  * @par Dependencies
  *   RAM dump table needs to be setup before
  *
  * @retval
  *   None
  *
  * @par Side Effects
  *   None
  *
  */

  bl_error_boot_type _rd_sahara_deinit(void)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_sahara_command_handler_if *sahara_command_handler_if = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;

  do
  {
    status = boot_config_context_get_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_RAMDUMP, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_SAHARA_COMMAND_HANDLER_TBL, (void **)&sahara_command_handler_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (sahara_command_handler_if)
    {
      status = mem_if->free((void *)sahara_command_handler_if);
      if (status != BL_ERR_NONE)
      {
        break;
      }


      sahara_command_handler_if = NULL;
      status = boot_config_context_set_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_SAHARA_COMMAND_HANDLER_TBL, (void *)NULL);
      if (status != BL_ERR_NONE)
      {
        break;
      }
    }

  } while (FALSE);

  return status;
}


/*=========================================================================

                       FUNCTION DEFINITIONS

=========================================================================*/


/*===========================================================================

**  Function :  rd_sahara_format_init

** ==========================================================================
*/
/*!
*
* @brief
*  Initialize the sahara format
*
* @par Dependencies
*   RAM dump table needs to be setup before
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

bl_error_boot_type rd_sahara_format_init (boot_handle media_if)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_edk2_cache_if_type *edk2_cache_if = NULL;

  boot_log_message ("Sahara Init");

  do
  {
    /* Flush the cache before calling into sahara so that all data is flushed to memory */
    status = boot_config_context_get_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_EDK2_CACHE_INTERFACE, (void**)&edk2_cache_if);
    if ((status != BL_ERR_NONE) || (edk2_cache_if == NULL))
    {
      boot_log_message("get_cache_if error");
      break;
    }

    edk2_cache_if->WriteBackInvalidateDataCacheRange ((void *)SCL_SBL1_DDR_ZI_BASE, SCL_SBL1_DDR_ZI_SIZE);
    edk2_cache_if->WriteBackInvalidateDataCacheRange ((void *)SCL_IMEM_BASE, SCL_IMEM_SIZE);

  } while (FALSE);

  return status;
}


/*===========================================================================

**  Function :  rd_raw_format_open

** ==========================================================================
*/
/*!
*
* @brief
*  Sahara interface dump
*
* @par Dependencies
*   RAM dump table needs to be setup before
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/


bl_error_boot_type rd_sahara_format_open (boot_handle  media_if_ptr)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_handle media_handle = NULL;
  boot_media_interface_if_type  *media_if = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;
  boot_sahara_command_handler_if *sahara_command_handler_if = NULL;

  DL_LOG("Sahara Open");

  media_if = (boot_media_interface_if_type*)media_if_ptr;

  do
  {
    if (media_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_LOADER, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_LOADER, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = mem_if->malloc (sizeof(boot_sahara_command_handler_if), (void *)&sahara_command_handler_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    memset ((void* )(sahara_command_handler_if), 0x0, sizeof(boot_sahara_command_handler_if));

    status = boot_config_context_set_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_SAHARA_COMMAND_HANDLER_TBL, (void *)(sahara_command_handler_if));
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Get sahara command handler interface */
    status = boot_sahara_command_handler_table_get_interface (sahara_command_handler_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Setup sahara command handler table  */
    status = boot_config_context_set_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_SAHARA_COMMAND_HANDLER_TBL, (void *)(sahara_command_handler_if));
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Enter Sahara RAMDUMP from Media Interface */
    status = media_if->open (CONFIG_CONTEXT_CRT_HANDLE, &media_handle);
    if (status != BL_ERR_NONE)
    {
      /* Free the memory malloced before sahara open */
      /* Do not save the return status to upper layers Since status is already bad */
      _rd_sahara_deinit();
      DL_LOG("rd_sahara return status:0x%x", status);
      /* Convert PIPO error to Ramdump restart error */
      if (status == GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_SAHARA_RAMDUMP_PIPO_RESTART))
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_RAMDUMP_RESTART);
      }
      break;
    }

    status = media_if->close (media_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }

  } while (FALSE);

  return status;
}


/*===========================================================================

**  Function :  rd_sahara_format_write

** ==========================================================================
*/
/*!
*
* @brief
*  Not used for Sahara currently
*
* @par Dependencies
*   RAM dump table needs to be setup before
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

bl_error_boot_type rd_sahara_format_write (boot_handle media_handle, char *filename, void *buffer, uintnt size)
{
  return BL_ERR_NONE;
}


/*===========================================================================

**  Function :  rd_sahara_format_close

** ==========================================================================
*/
/*!
*
* @brief
*  Close the handle
*
* @par Dependencies
*   RAM dump table needs to be setup before
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

bl_error_boot_type rd_sahara_format_close (boot_handle media_handle)
{
#if 0
  /* The device should be set to reset before this */
  /* Handle media interface close here */
  return media_if->close(media_handle);
#endif

  bl_error_boot_type status = _rd_sahara_deinit();
  DL_LOG("+------------------+");
  DL_LOG("| Sahara Dump done |");
  DL_LOG("+------------------+");

  return status;
}


/*===========================================================================

**  Function :  rd_sahara_format_deinit

** ==========================================================================
*/
/*!
*
* @brief
*  Deinit SAHARA
*
* @par Dependencies
*   RAM dump table needs to be setup before
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

bl_error_boot_type rd_sahara_format_deinit (boot_handle media_if)
{
  return BL_ERR_NONE;
}


/*===========================================================================

**  Function :  rd_sahara_format_get_interface

** ==========================================================================
*/
/*!
*
* @brief
*  Get Sahara format interface
*
* @par Dependencies
    Interface dependencies should be setup already*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

bl_error_boot_type rd_sahara_format_get_interface(void *format_interface_if)
{
  bl_error_boot_type error = BL_ERR_NONE;

  if (format_interface_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_INVALID_PARAMETER);
  }

  ((ramdump_format_if_type *)format_interface_if)->init   = rd_sahara_format_init;
  ((ramdump_format_if_type *)format_interface_if)->open   = rd_sahara_format_open;
  ((ramdump_format_if_type *)format_interface_if)->write  = rd_sahara_format_write;
  ((ramdump_format_if_type *)format_interface_if)->close  = rd_sahara_format_close;
  ((ramdump_format_if_type *)format_interface_if)->deinit = rd_sahara_format_deinit;

  return error;
}

