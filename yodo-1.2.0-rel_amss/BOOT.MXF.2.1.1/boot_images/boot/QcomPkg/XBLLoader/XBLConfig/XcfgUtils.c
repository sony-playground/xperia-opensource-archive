/*=============================================================================

                            XBLConfig Module Sources

GENERAL DESCRIPTION
  This file defines XBL config Utility api's.

Copyright 2017 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
05/10/17     kpa      Added xcfg_malloc
04/05/17     kpa      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "XBLConfig.h"
#include "XcfgUtils.h"
#include "boot_config_context.h"
#include <boot_memory_mgr_if.h>

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/


/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/


/*===========================================================================
**  Function :  xcfg_malloc
** ==========================================================================
*/
/*!
*
* @brief
*   This function is a wrapper for underlying DAL memory alloc api
*
* @param[in]
*   buff_size      Requested size of memory to be alloced
*   xcfg_buff_ptr  Return parameter, callee will populate this to point to the
*                  block of alloced memory, valid only upon DAL_SUCCESS return
*                  code
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xcfg_malloc(uintnt buff_size, void **xcfg_buff_ptr)
{
  xblconfig_status_type status = XBLCONFIG_MEMORY_ALLOCATION_ERR;
  boot_memory_mgr_if_type *mem_if = NULL;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if (xcfg_buff_ptr == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }

    if (buff_size > XCFG_UINT32_MAX)
    {
      /* Currently DAL malloc api only supports uint32 alloc sizes */
      status = XBLCONFIG_OVERFLOW_ERR;
      break;
    }

    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = mem_if->malloc(buff_size, xcfg_buff_ptr);

    if ((return_status != BL_ERR_NONE) || (xcfg_buff_ptr == NULL))
    {
      status = XBLCONFIG_MEMORY_ALLOCATION_ERR;
    }
    else
    {
      status = XBLCONFIG_SUCCESS;
    }

  } while (0);
  return status;
}



/*===========================================================================
**  Function :  xcfg_free
** ==========================================================================
*/
/*!
*
* @brief
*   This function is a wrapper for underlying DAL memory free api
*
* @param[in]
*   xcfg_buff_ptr            pointer to buffer being freed
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xcfg_free
(
  void **xcfg_buff_ptr
)
{
  xblconfig_status_type status = XBLCONFIG_SUCCESS;
  boot_memory_mgr_if_type *mem_if = NULL;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if (xcfg_buff_ptr == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }

    if (*xcfg_buff_ptr != NULL)
    {
      return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      return_status = mem_if->free(*xcfg_buff_ptr);
      if (return_status != BL_ERR_NONE)
      {
        status = XBLCONFIG_MEMORY_FREE_ERR;
      }
      else
      {
        *xcfg_buff_ptr = NULL;
        status = XBLCONFIG_SUCCESS;
      }
    }
  } while (0);

  return status;
}

