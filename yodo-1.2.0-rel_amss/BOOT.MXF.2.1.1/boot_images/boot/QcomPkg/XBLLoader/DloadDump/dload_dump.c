/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                          MEMORY DEBUG INFORMATION 

GENERAL DESCRIPTION
  This module dumps security memory region to destinition address

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

Copyright 2019-2021 by Qualcomm Technologies, Inc.  All Rights Reserved..


*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*===========================================================================

                           EDIT HISTORY FOR FILE
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/17/21   rama    Move to dbginfo lib
07/22/20   rama    Updated SecLib API to remove verified info
06/25/20   rama    Added boot_seclib_if.h
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <string.h>
#include "boot_shared_imem_cookie.h"
#include "dload_dump.h"
#include "boot_error_if.h"
#include "boot_crashdump.h"
#include "boot_pmic_if.h"
#include <boot_seclib_if.h>
#include "boot_qsee_if.h"
#include "boot_logger.h"
#include "boot_sbl_shared.h"
#include <boot_dbginfo_if.h>

/*===========================================================================

                     EXTERNAL DEFINITIONS FOR MODULE

===========================================================================*/


/*===========================================================================
**  Function :  boot_dload_is_security_region_dump_allowed
** ==========================================================================
*/
/*!
* 
* @brief
*   This function will determine if sbl can dump tz in dload mode
*
* @param[in] shared_data Pointer to shared data
*        
* @par Dependencies
*   None
* 
*/
bl_error_boot_type boot_dload_is_security_region_dump_allowed(boot_handle config_context_handle, uint8 *mem_dump_supported) 
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_dbginfo_if_type *dbginfo_if = NULL;

 do
 {
  return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_DBGINFO_INTERFACE, (void **)&dbginfo_if);
  if(return_status != BL_ERR_NONE)
  {
    break;
  }

  return_status = dbginfo_if->is_ramdump_allowed((boot_boolean*)(mem_dump_supported));
  if(return_status != BL_ERR_NONE)
  {
    break;
  }
  
 }while(FALSE);
  return return_status;
}

/*===========================================================================
**  Function :  boot_dload_dump_valid_segment
** ==========================================================================
*/
/*!
* 
* @brief
*   This function will determine if Source and destinition addresses are 
*   valid/ accessible and within ranges.
*
* @param[in] 
*            region_src Source address for segment dump
*            region_size Size of segment to be dumped
*        
* @par Dependencies
*   None
* 
*/
static boot_boolean boot_dload_dump_valid_segment(boot_handle config_context_handle, uintnt region_src, uintnt region_size)
{
#ifdef SCL_pIMEM_BASE
  uint32 size_in_mb = 0;
  boot_boolean status = FALSE;
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_seclib_if_type *seclib_if = NULL;

  do
  {
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SECLIB_INTERFACE, (void **)&seclib_if);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }  
    
    /*If Pimem is disabled skip segments lying in the range */  
    return_status = seclib_if->pimem_get_status(&size_in_mb);
    if( BL_ERR_NONE != return_status)
    {
      /* Check if segment has no overlap with pimem region */
      if((region_src < SCL_pIMEM_BASE && 
          (region_src + region_size) < SCL_pIMEM_BASE &&
          (region_src + region_size) > region_src /*no overflow */ 
          ) ||
          ( (region_src + region_size) > region_src && /*no overflow */
            ((SCL_pIMEM_BASE + SCL_pIMEM_SIZE) > SCL_pIMEM_BASE) &&
            (region_src > (SCL_pIMEM_BASE + SCL_pIMEM_SIZE)) && 
            (region_src + region_size) > (SCL_pIMEM_BASE + SCL_pIMEM_SIZE) 
          )
        )
      {
        status = TRUE;
        break;
      }
      else{
        boot_log_message("pImem Disabled, segment not added to dump.");
      }
    }
    else
    { /* Pimem is enabled */
      status = TRUE;
    }
    
  }while(0);
  return status;
#else
  return TRUE;
#endif  
}


/*===========================================================================
**  Function :  boot_dload_dump_region
** ==========================================================================
*/
/*!
* 
* @brief
*   This function dumps regions for a single image (Qsee or qhee)
*
* @param[in] shared_imem_offset     Offset to locate dump info.
*            shared_imem_magic_num  Magic number to indicate cookie presence
*        
* @par Dependencies
*   None
* 
*/
static void boot_dload_dump_region(boot_handle config_context_handle, uintnt shared_imem_offset, uintnt shared_imem_magic_num) 
{
  struct security_region_dload_dump_shared_imem_cookie_type *shared_imem_dload_dump_cookie_ptr;
  struct security_region_dload_dump_info_type *security_region_dload_dump_info_ptr;
  struct boot_dump_entry_type *dump_region;
  uint32 dump_entry_index = 0;

  shared_imem_dload_dump_cookie_ptr = (struct security_region_dload_dump_shared_imem_cookie_type *)
    (uintnt)(shared_imem_offset + (uintnt)boot_shared_imem_cookie_ptr);
  
  if(shared_imem_dload_dump_cookie_ptr->magic_num == shared_imem_magic_num)
  { 
    if(shared_imem_dload_dump_cookie_ptr->dst_addr != 0x0)
    {
      /* get dump info struct address */
      security_region_dload_dump_info_ptr = (struct security_region_dload_dump_info_type *)(uintnt)
                                               shared_imem_dload_dump_cookie_ptr->dst_addr;
                                               
      if(security_region_dload_dump_info_ptr->magic_num == shared_imem_magic_num && 
         security_region_dload_dump_info_ptr->version_num >= DLOAD_DUMP_INFO_VERSION)
      {
         BL_VERIFY((security_region_dload_dump_info_ptr->num_of_entries 
                   <= BOOT_DUMP_NUM_ENTRIES), BL_ERR_RAM_DUMP_FAIL|BL_ERROR_GROUP_BOOT);
         for(dump_entry_index =0; 
             dump_entry_index < security_region_dload_dump_info_ptr->num_of_entries;
             dump_entry_index++ )
         {
            dump_region = &security_region_dload_dump_info_ptr->boot_dump_entry[dump_entry_index];
            /*Dump the segment if valid/accessible else skip */
            if( TRUE == boot_dload_dump_valid_segment(config_context_handle, (uintnt)dump_region->region_src,
                                                      (uintnt)dump_region->region_size))
            {
#ifdef SCL_pIMEM_SIZE              
              memscpy((void*)(uintnt)dump_region->region_dst,
              SCL_pIMEM_SIZE, /* TZ Segment would not exceed this max size */
              (void*)(uintnt)dump_region->region_src, 
              dump_region->region_size);
#endif              
            }
        }
        /* Once Dumps are successfully collected clear dump cookie */
        security_region_dload_dump_info_ptr->magic_num = 0x0;
      }                  
    }
  }
}


/*===========================================================================
**  Function :  boot_dload_dump_security_regions
** ==========================================================================
*/
/*!
* 
* @brief
*   This function will dump backup qsee and qhee regions according to 
*   information passed by qsee/qhee's shared imem cookies, so they can be 
*   ramdumped later.
*
* @param[in] shared_data Pointer to shared data
*        
* @par Dependencies
*   Called only in dload path
* 
*/
bl_error_boot_type boot_dload_dump_security_regions(boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  uint8 mem_dump_supported = FALSE;
  
  do
  { 
    if(boot_dload_is_dload_mode_set() == TRUE)
    {
      return_status = boot_dload_is_security_region_dump_allowed(config_context_handle, &mem_dump_supported);
      if(return_status != BL_ERR_NONE)
      {
        break;
      }
      /*Call qsee is memory dump allowed api only in dload mode */
      if(mem_dump_supported == TRUE)
      {
        /* Dump Qsee region */
        boot_dload_dump_region(config_context_handle, QSEE_DLOAD_DUMP_SHARED_IMEM_OFFSET, 
                             QSEE_DLOAD_DUMP_SHARED_IMEM_MAGIC_NUM);
      
        /* Dump Qhee region */
        boot_dload_dump_region(config_context_handle, QHEE_DLOAD_DUMP_SHARED_IMEM_OFFSET, 
                               QHEE_DLOAD_DUMP_SHARED_IMEM_MAGIC_NUM);
      }
    }
  }while(FALSE);
  
  return return_status;
}
