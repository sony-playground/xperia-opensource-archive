/*===========================================================================

                    BOOT EXTERN ENCRYPTION DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external crypto drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright (c) 2017,2018,2020-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/07/21   rama    Changes for error handling
07/19/21   rama    Added cil_common.h
05/29/20   rama    Removed boot_extern_crypto_interface.h
10/12/17   aus     Updated to support minidump
25/04/17   bd      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include <string.h>
#include <cil_common.h>
#include <boot_target.h>
#include <boot_ramdump_table.h>
#include <boot_ramdump_if.h>
#include <boot_error_if.h>


/*===========================================================================

**  Function :  cil_md_crypto_init

** ==========================================================================
*/
/*!
* 
* @brief
*   Perform encryption initiliazation
*   
*
* @par Dependencies   
*   
*   
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type cil_md_crypto_init(void)
{
  return BL_ERR_NONE;
}

/*===========================================================================

**  Function :  cil_md_encrypt_region

** ==========================================================================
*/
/*!
* 
* @brief
*   Perform in-place encryption of the given region
*
* @par Dependencies   
*   
*   
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type cil_md_encrypt_region(uint64 r_base, uint64 r_len, uint32 r_num)
{
  return BL_ERR_NONE;
}

/*===========================================================================

**  Function :  cil_md_add_unencr_regions

** ==========================================================================
*/
/*!
* 
* @brief
*   Adds the encryption key regions to debug table
*
* @par Dependencies
*   This api Must be called AFTER cil_md_encrypt_region has been called for all regions
*   
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type cil_md_add_unencr_regions(void *handle)
{
    return BL_ERR_NONE;
}
