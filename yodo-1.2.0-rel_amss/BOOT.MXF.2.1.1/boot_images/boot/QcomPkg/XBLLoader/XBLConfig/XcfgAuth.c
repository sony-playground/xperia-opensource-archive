/*=============================================================================

                            XBLConfig Module Sources

GENERAL DESCRIPTION
  This file contains common authentication routines used by xblconfig lib

Copyright 2017, 2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
02/09/22     ck      Updated heap names
07/25/17     yps     Added external heap base and size
05/11/17     kpa     Initial version
===========================================================================*/

#include "XBLConfig.h"
#include "boot_framework.h"
#include "boot_config_context.h"
#include "boot_whitelist_if.h"


/*=============================================================================
            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.
=============================================================================*/

/*Define whitelist for validating load addresses */
#ifndef BOOT_RAMDUMP_ENABLE
extern uintnt * boot_internal_cached_heap_base;
extern uintnt boot_internal_cached_heap_size;
#endif

extern uintnt * boot_external_cached_heap_base;
extern uintnt boot_external_cached_heap_size;


/*===========================================================================
**  Function :  xcfg_load_addr_validation_init
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes load address validation module
*  (such as whitelist checks)
*
* @param[in]
*  None
*
* @param[out]
*  None
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type. XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
whitelst_tbl_entry_type xblconfig_img_whitelist[4];
xblconfig_status_type xcfg_load_addr_validation_init(boot_handle config_context_handle)
{
  xblconfig_status_type status = XBLCONFIG_BUFFER_VALIDATION_ERR;
  bl_error_boot_type return_status = BL_ERR_NONE;
#ifndef BOOT_RAMDUMP_ENABLE
  xblconfig_img_whitelist[0].start_addr = (uint64)boot_internal_cached_heap_base;
  xblconfig_img_whitelist[0].size = boot_internal_cached_heap_size;

  xblconfig_img_whitelist[1].start_addr = (uint64)boot_external_cached_heap_base;
  xblconfig_img_whitelist[1].size = boot_external_cached_heap_size;

  xblconfig_img_whitelist[2].start_addr = SCL_SBL1_DDR_DSF_CFG_BUF_BASE;
  xblconfig_img_whitelist[2].size = SCL_SBL1_DDR_DSF_CFG_BUF_SIZE;

  xblconfig_img_whitelist[3].start_addr = SCL_SBL1_DDR_SHRM_STRUCT_BASE;
  xblconfig_img_whitelist[3].size = SCL_SBL1_DDR_SHRM_STRUCT_SIZE;
#else
  xblconfig_img_whitelist[0].start_addr = (uint64 )boot_external_cached_heap_base;
  xblconfig_img_whitelist[0].size = boot_external_cached_heap_size;

  xblconfig_img_whitelist[1].start_addr = SCL_SBL1_DDR_DSF_CFG_BUF_BASE;
  xblconfig_img_whitelist[1].size = SCL_SBL1_DDR_DSF_CFG_BUF_SIZE;

  xblconfig_img_whitelist[2].start_addr = SCL_SBL1_DDR_SHRM_STRUCT_BASE;
  xblconfig_img_whitelist[2].size = SCL_SBL1_DDR_SHRM_STRUCT_SIZE;
#endif

  /* Set the image whitelist for whitelist based image loading */
//  if( TRUE == boot_set_active_img_whitelist_table(&xblconfig_img_whitelist[0]))
//    status = XBLCONFIG_SUCCESS;

  do
  {
    return_status = boot_config_context_set_value(config_context_handle, CONFIG_CONTEXT_WHITELIST_NUM_ENTRIES, sizeof(xblconfig_img_whitelist)/sizeof(whitelst_tbl_entry_type));
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_IMAGE_WHITELIST, xblconfig_img_whitelist);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    status = XBLCONFIG_SUCCESS;

  } while (FALSE);

  return status;
}

/*===========================================================================
**  Function :  xcfg_load_addr_validation_deinit
** ==========================================================================
*/
/*!
*
* @brief
*   This function deinitializes load address validation module
*  (such as whitelist checks)
*
* @param[in]
*  None
*
* @param[out]
*  None
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type. XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xcfg_load_addr_validation_deinit (void)
{
  //boot_invalidate_img_whitelist(); TODO: Remove and move to wl_if->open and wl->close

  return XBLCONFIG_SUCCESS;
}
