/** @file MinidumpLibNull.c
  
  Stub functions for MinidumpLib

  Copyright (c) 2020-2022, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/22/22   rama    Add new APIs
 06/22/21   rama    boot_minidump_init params update
 03/30/20   aus     Initial revision

=============================================================================*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "com_dtypes.h"
#include "boot_minidump.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 



/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/
/*===========================================================================
**  Function :  boot_md_get_global_mdtoc_addr
** ==========================================================================
*/
/*!
* 
* @brief
*   This function returns the global minidump toc if it is initialized
* 
* @param
*   None
*        
* @par Dependencies
*   None
*   
* @retval
*   md_global_toc* Pointer to the global minidump toc
* 
* @par Side Effects
*   None
* 
*/
md_global_toc* boot_md_get_global_mdtoc_addr(void)
{
  return NULL;
}

/*===========================================================================
**  Function :  boot_md_get_subsystem_toc
** ==========================================================================
*/
/*!
* 
* @brief
*   This function returns the global minidump toc if it is initialized
* 
* @param
*   md_subsys_type sub-system index
*        
* @par Dependencies
*   None
*   
* @retval
*   md_ss_toc* Pointer to the sub-system minidump toc
* 
* @par Side Effects
*   None
* 
*/
md_ss_toc* boot_md_get_subsystem_toc(md_subsys_type ss_id)
{
  return NULL;
}

/*===========================================================================
**  Function :  boot_add_minidump_region
** ==========================================================================
*/
/*!
* 
* @brief
*   This function adds a new minidump region in boot sub-system minidump table
* 
* @param
*   char*  Name of the region
*   uint64 Base address
*   uint64 Size
*        
* @par Dependencies
*   None
*   
* @retval
*   boolean TRUE if region added, FALSE otherwise
* 
* @par Side Effects
*   None
* 
*/
boolean boot_add_minidump_region(md_subsys_type ss_id, char rg_name[MD_REGION_NAME_LENGTH], uint64 rg_base_addr, uint64 rg_size)
{
  return TRUE;
}

/*===========================================================================
**  Function :  boot_minidump_init
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes Boot minidump sub-system toc
* 
* @param
*   md_ss                 [in]     subsystem index
*   md_ss_enable_status   [in]     subsystem enable status
*   encryption_required   [in]     encryption required status of subsystem
*   encryption_status     [in]     encryption status of sybsystem
*   ss_baseptr            [in]     address of subsystems region table
*
* @par Dependencies
*   None
*   
* @retval
*   boolean TRUE if init is successful, FALSE otherwise
* 
* @par Side Effects
*   None
* 
*/
boolean boot_minidump_init(md_subsys_type ss_id, uint32 md_ss_enable_status, uint32 encryption_required, uint32 encryption_status, uintnt ss_baseptr)
{
  return TRUE;
}


/*===========================================================================
**  Function :  boot_init_encryption_artifacts
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes encryption artifacts required to encrypt regions
* 
* @param
*   config_context_handle [in]    boot handle to get interfaces from config context
*   md_region_count       [in]    region count required to allocate memory for encryption artifacts
* @par Dependencies
*   None
*   
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_init_encryption_artifacts(boot_handle config_context_handle, uint32 md_region_count)
{
  return BL_ERR_NONE;
}

/*===========================================================================
**  Function :  boot_encrypt_minidump_region
** ==========================================================================
*/
/*!
* 
* @brief
*   This function encrypts a region and updates IV and MAC in encryption artifacts
* 
* @param
*   md_region_in      [in]     input buffer
*   md_region_in_size [in]     input buffer length
*   md_region_out     [in]     pointer to output buffer
* 
* @par Dependencies
*   None
* 
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_encrypt_minidump_region(uintnt * md_region_in, uintnt md_region_in_size, uintnt * md_region_out, uint32 md_region_index)
{
  return BL_ERR_NONE;
}

/*===========================================================================
**  Function :  boot_get_encryption_artifacts
** ==========================================================================
*/
/*!
* 
* @brief
*   This function returns the encryption 
*   artifacts (Wrapped key & size, IV buffer and size, MAC buffer and size)
* 
* @param
*   wrapped_key        [out] pointer to wrapped key buffer
*   wrapped_key_size   [out] pointer to store wrapped key buffer size
*   iv_buffer          [out] pointer to IV buffer
*   iv_buffer_size     [out] pointer to store IV buffer size
*   mac_buffer         [out] pointer to MAC buffer
*   mac_buffer_size    [out] pointer to store MAC buffer size
*
* @par Dependencies
*   None
*   
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_get_encryption_artifacts(uint8 ** wrapped_key, uint32 * wrapped_key_size, uint8 ** iv_buffer, uint32 * iv_buffer_size, uint8 ** mac_buffer, uint32 * mac_buffer_size)
{
  return BL_ERR_NONE;
}

/*===========================================================================
**  Function :  boot_encrypt_and_get_md_regions
** ==========================================================================
*/
/*!
* 
* @brief
*   This function performs encryption based on auth enabled state and returns minidump region list to caller
* 
* @param
*   config_context_handle     [in]    boot_handle
*   is_auth_enabled           [in]    auth enabled state
*   region_table              [out]   pointer to minidump region table
*   region_count              [out]   pointer to store region table size
*        
* @par Dependencies
*   None
*   
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_encrypt_and_get_md_regions(boot_handle config_context_handle, boot_boolean is_auth_enabled, boot_minidump_region_type ** region_table, uint32 *region_count)
{
  return BL_ERR_NONE;
}
