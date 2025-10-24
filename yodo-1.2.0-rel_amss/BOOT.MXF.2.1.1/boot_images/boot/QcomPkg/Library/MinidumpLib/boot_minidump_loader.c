/*=============================================================================
                        Minidump Library

GENERAL DESCRIPTION
    This file handles the minidump initialization and addition of new regions 
  for Boot.

Copyright 2020-2022 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
08/02/22     rama     fix mismatching IV and MAC when regions are skipped
05/13/22     rama     Changes for supporting region table within registered region
04/28/22     rama     Fix mismatching IV and MAC with regions during decryption
03/09/22     rama     Changes for supporting ECDH encryption
02/18/22     rama     Cleanup phase 2
01/18/22     rama     Re-arch updates and API separation for Loader and Core
10/16/21     yps      Avoid to add duplicate boot minidump regions
08/26/21     rama     added md_ss in boot_add_minidump_region
06/22/21     rama     boot_add_minidump_region-> seq_num is always 0
03/30/20     aus      Initial version
===========================================================================*/

/*==========================================================================

                   INCLUDE FILES

===========================================================================*/
#include <boot_minidump.h>
#include <smem.h>
#include <string.h>
#include <stdio.h>
#include <boot_encryption.h>
#include <boot_logger.h>
#include <boot_config_context.h>
#include <boot_target.h>
#include <boot_dbginfo_if.h>
#include <boot_encryption.h>
#include <boot_ramdump_table.h>
#include <seclib_defs.h>
#include <boot_blacklist_if.h>
#include <error_handler.h>

/* structure to hold encryption artifacts*/
typedef struct
{
  /*must be of size MD_AES_KEY_SIZE */
  uint8 aes_key_buffer[MD_AES_KEY_SIZE];

  /*must be of size MD_HMAC_KEY_SIZE */
  uint8 hmac_key_buffer[MD_HMAC_KEY_SIZE];

  /*must be of size SECLIB_WRAPPED_BLOB_AND_ENCR_INFO_LEN */
  uint8 wrapped_keys_and_artifacts[SECLIB_WRAPPED_BLOB_AND_ENCR_INFO_LEN];

  /*size of wrapped_keys_and_artifacts returned after wrapping */
  uint32 wrapped_keys_and_artifacts_buffer_size;

  /* buffer to hold IVs for each region encrypted */
  uint8 * iv_region_buffer;

  uint32 iv_region_buffer_size;

  /* buffer to hold MACs for each region encrypted */
  uint8 * mac_region_buffer;

  uint32 mac_region_buffer_size;

}boot_minidump_handle;

typedef boot_minidump_handle *boot_minidump_handle_t;

static boot_minidump_handle_t handle = NULL;

/*===========================================================================
**  Function :  _handle_null_check
** ==========================================================================
*/
/*!
* 
* @brief
*   This function checks the if handle is initialized
* 
* @param
*   handle    [in]    minidump handle to be checked
*        
* @par Dependencies
*   None
*   
* @retval
*   boolean TRUE if handle is valid
* 
* @par Side Effects
*   None
* 
*/
boolean _handle_null_check(boot_minidump_handle_t handle)
{
  if(handle == NULL || handle->aes_key_buffer == NULL ||
     handle->hmac_key_buffer == NULL || handle->wrapped_keys_and_artifacts == NULL ||
     handle->wrapped_keys_and_artifacts_buffer_size == 0 ||
     handle->iv_region_buffer == NULL || handle->mac_region_buffer == NULL)
      return FALSE;
    else 
      return TRUE;
}

/*===========================================================================
**  Function :  boot_get_md_region_count
** ==========================================================================
*/
/*!
* 
* @brief
*   This function steps through all the mindiump subsystem ToCs and get
*   total number of regions.
* 
* @param
*   md_region_count     [out]    pointer to store region count
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
bl_error_boot_type boot_get_md_region_count(uint32 *md_region_count)
{
  md_ss_toc *ss_info = NULL;
  uint32 count = 0, index = 0;


  if(md_region_count == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_NULL_PTR_PASSED);
  }

  /* initialize md_region_count */
  *md_region_count = 0;

  /* Loop through all the subsystems to get total number of regions */
  for(index = 0; index < MD_SS_MAX; index++)
  {
    /* get subsystem ToC for current index */
    ss_info = boot_md_get_subsystem_toc(index);

    /* check if subsystem ToC is valdi and update region count */
    if(ss_info == NULL)
    {
      continue;
    }
    else if(ss_info->md_ss_toc_init != 0)
    {
      count += ss_info->ss_region_count;
    }
  }

  *md_region_count = count;


  return BL_ERR_NONE;
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
bl_error_boot_type boot_init_encryption_artifacts(boot_handle config_context_handle, uint32 md_region_count, uint8 *md_context)
{

  bl_error_boot_type status = BL_ERR_NONE;
  uint32  offset = 0;
  boot_memory_mgr_if_type * mem_if = NULL;
  uint8 boot_aes_and_hmac_key_and_version[MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE] __attribute__ ((aligned (CACHE_LINE_LENGTH_BYTES))) = {0};

  do
  {
    /* check passed arguments */
    if(config_context_handle == NULL || md_region_count == 0 || md_context == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_INVALID_PARAMETER);
      break;
    }

    /* get memory interface from config context */
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    if(mem_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* return if handle is already initialized */
    if(_handle_null_check(handle))
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_INVALID_PARAMETER);
      break;
    }

    /* Malloc handle */
    status = mem_if->malloc(sizeof(boot_minidump_handle), (void *)&handle);
    if(status != BL_ERR_NONE || handle == NULL)
    {
      break;
    }
    if(handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_MEMORY_ALLOC_FAIL);
      break;
    }

    /* initialize handle */
    handle->iv_region_buffer = NULL;
    handle->mac_region_buffer = NULL;

    /* update the IV and MAC buffers sizes*/
    handle->iv_region_buffer_size = md_region_count * MD_AES_IV_SIZE;
    handle->mac_region_buffer_size = md_region_count * MD_AES_MAC_SIZE;
    handle->wrapped_keys_and_artifacts_buffer_size = 0;

    /* malloc buffers for IV and MAC */
    status = mem_if->malloc(handle->iv_region_buffer_size, (void *)&(handle->iv_region_buffer));
    if(status != BL_ERR_NONE)
    {
      boot_log_message("MD: IV Buf heap err");
      break;
    }

    status = mem_if->malloc(handle->mac_region_buffer_size, (void *)&(handle->mac_region_buffer));
    if(status != BL_ERR_NONE)
    {
      boot_log_message("MD: MAC Buf heap err");
      break;
    }

    /* Check if malloced buffers are NULL */
    if(handle->iv_region_buffer == NULL || handle->mac_region_buffer == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_MEMORY_ALLOC_FAIL);
      break;
    }

    /* generate AES and HMAC keys for encryption */
    status = generate_random_value((uint8 *)&(handle->aes_key_buffer), MD_AES_KEY_SIZE);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = generate_random_value((uint8 *)&(handle->hmac_key_buffer), MD_HMAC_KEY_SIZE);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    /* create the plain text keys buffer to be wrapped */
    offset+=memscpy(boot_aes_and_hmac_key_and_version,MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE,handle->aes_key_buffer,(size_t)MD_AES_KEY_SIZE);
    offset+=memscpy(&boot_aes_and_hmac_key_and_version[offset],(MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE-offset),handle->hmac_key_buffer,MD_HMAC_KEY_SIZE);
    offset+=memscpy(&boot_aes_and_hmac_key_and_version[offset],(MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE-offset),minidump_version,MD_VERSION_SIZE);

    /* Wrap plain text keys buffer */
    status = boot_encr_aes_key(config_context_handle, boot_aes_and_hmac_key_and_version, MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE, handle->wrapped_keys_and_artifacts, &(handle->wrapped_keys_and_artifacts_buffer_size), md_context);
    if(status != BL_ERR_NONE)
    {
      break;
    }

  }while(FALSE);

  return status;
}

/*===========================================================================
**  Function :  boot_update_encryption_artifacts
** ==========================================================================
*/
/*!
* 
* @brief
*   This function adds a new minidump region in boot sub-system minidump table
* 
* @param
*   aes_iv        [in]    IV buffer
*   aes_mac       [in]    MAC buffer
*   region_number [in]    region number of the encrypted region
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
static bl_error_boot_type boot_update_encryption_artifacts(uint8 * aes_iv, uint8 * aes_mac, uint8 region_number)
{
  bl_error_boot_type status = BL_ERR_NONE;

  do
  {

    /* return if handle is invalid */
    if(!_handle_null_check(handle))
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* update iv for encrypted region in the handle */
    memscpy((uint8 *)(handle->iv_region_buffer) + (region_number * MD_AES_IV_SIZE), MD_AES_IV_SIZE, aes_iv, MD_AES_IV_SIZE);

    /* update MAC for encrypted region in the handle */
    memscpy((uint8 *)(handle->mac_region_buffer) + (region_number * MD_AES_MAC_SIZE), MD_AES_MAC_SIZE, aes_mac, MD_AES_MAC_SIZE);

  }while(FALSE);

  return status;
}


/*===========================================================================
**  Function :  encrypt_minidump_region
** ==========================================================================
*/
/*!
* 
* @brief
*   This function adds a new minidump region in boot sub-system minidump table.
*   Separated this logic from boot_encrypt_minidump_region as individual subsystems 
*   adding regions do not need to track region index whereas client collecting minidumps 
*   must track region index.
* 
* @param
*   md_region_in      [in]     input buffer
*   md_region_in_size [in]     input buffer length
*   md_region_out     [in]     pointer to output buffer
*   md_region_index   [in]     index required to store IV and MAC 
*                              Needs to be in sync with region index for proper decryption
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
static bl_error_boot_type encrypt_minidump_region(uintnt * md_region_in, uintnt md_region_in_size, uintnt * md_region_out, uint32 md_region_index)
{
  bl_error_boot_type status = BL_ERR_NONE;
  uint8 mac[MD_AES_MAC_SIZE] = {0};
  uint8 boot_md_aes_iv[MD_AES_IV_SIZE];

  do
  {

    /* return if handle is invalid */
    if(!_handle_null_check(handle))
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Perform AES encryption on input region */
    if(boot_sw_cipher((void *)md_region_in, md_region_in_size,
                   (void *)md_region_out, md_region_in_size,
                   (void *)handle->aes_key_buffer, MD_AES_KEY_SIZE,
                   (void *)handle->hmac_key_buffer, MD_HMAC_KEY_SIZE,
                   (void *)boot_md_aes_iv, MD_AES_IV_SIZE,
                   (void *)mac, MD_AES_MAC_SIZE,
                   TRUE) != BL_ERR_NONE)
    {
      break;
    }

    /* Update IV and MAC for the region encrypted */
    status = boot_update_encryption_artifacts(boot_md_aes_iv, mac, md_region_index);
    if(status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_MD_ADD_REGION_FAIL);
      break;
    }

  }while(FALSE);

  return status;
}
/*===========================================================================
**  Function :  boot_encrypt_minidump_region
** ==========================================================================
*/
/*!
* 
* @brief
*   This function adds a new minidump region in boot sub-system minidump table
*   This API calls into encrypt_minidump_region as caller does not need to keep 
*   track of region index
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
bl_error_boot_type boot_encrypt_minidump_region(uintnt * md_region_in, uintnt md_region_in_size, uintnt * md_region_out)
{
  bl_error_boot_type status = BL_ERR_NONE;
  static uint32 region_index = 0;

  status = encrypt_minidump_region(md_region_in, md_region_in_size, md_region_out, region_index++);

  return status;
}

/*===========================================================================
**  Function :  boot_clear_md_regions
** ==========================================================================
*/
/*!
* 
* @brief
*   This function adds a new minidump region in boot sub-system minidump table
* 
* @param
*   index     [in]    SS index to be cleared
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
static void boot_clear_md_regions(md_subsys_type ss_id)
{
  md_ss_toc *ss_info = NULL;
  md_ss_region *region_info = NULL;
  uint32 count = 0;

  if(ss_id >= MD_SS_MAX)
  {
    return;
  }

  ss_info = boot_md_get_subsystem_toc(ss_id);
  if(ss_info == NULL)
  {
    return;
  }
  else if(ss_info->md_ss_toc_init != 0)
  {
    count = ss_info->ss_region_count;
    region_info = (md_ss_region *)ss_info->md_ss_smem_regions_baseptr;

    while(count > 0)
    {
      if((region_info->md_valid == MD_REGION_VALID) && region_info->region_name != NULL)
      {
        memset((void *)region_info->region_base_address, 0x0, region_info->region_size);
      }
      region_info++;
      count--;
    }
  }
}

/*===========================================================================
**  Function :  boot_is_region_valid
** ==========================================================================
*/
/*!
* 
* @brief
*   This function checks if the given region is valid
* 
* @param
*   config_context_handle     [in]    boot_handle
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
boot_boolean boot_is_region_valid(md_ss_region *region_info)
{
  uint32 index = 0, string_len = strlen((const char *)(region_info->region_name));
  if ((region_info->md_valid == MD_REGION_VALID) &&
      (region_info->region_name != NULL) && 
      (region_info->region_base_address != 0) &&
      (region_info->region_size != 0) &&
      (region_info->seq_num >= 0) &&
      (region_info->seq_num < UINT32_MAX) &&
      (string_len > 0))
      {
        for(index = 0; index < string_len; index++)
        {
          /* Check if region name hase non-(ASCII printable) characters */
          /* (ASCII printable) characters range from 0x20(' ') to 0x7E('~') */ 
          if(region_info->region_name[index] < ' ' || region_info->region_name[index] > '~')
            return FALSE;
        }

        return TRUE;
      }

  return FALSE;
}

bl_error_boot_type boot_print_minidump_region_info(boot_boolean is_auth_enabled)
{
  bl_error_boot_type status = BL_ERR_NONE;
  uint32 index = 0, count = 0, md_region_count = 0, invalid_regions_count = 0;
  md_ss_toc *ss_info = NULL;
  md_ss_region *region_info = NULL;
  char error_message[BOOT_ERROR_MSG_LEN] = "";

  do
  {

#ifdef MINIDUMP_FEATURE_DEBUG
    snprintf(error_message, BOOT_ERROR_MSG_LEN, "ss_index\tinit_state\ten_state\tencr_req\tencr_state\tregion_cnt\treg_index\t\treg_name\t\treg_addr\t\treg_size");
    boot_log_message(error_message);
#endif

    /* Check every SS MD regions and encrypt if required */
    for (index = 0; index < MD_SS_MAX; index++)
    {
      /* get subsystem toc for current index */
      ss_info = boot_md_get_subsystem_toc((md_subsys_type)index);

      /* skip subsystem if not initialized */
      if (ss_info == NULL || ss_info->md_ss_toc_init == 0)
        continue;
      
      /* check if subsystem toc is enabled */
      if (ss_info->md_ss_enable_status == MD_SS_ENABLED)
      {
        invalid_regions_count = 0;

        /* get the region table and region count of current subsystem */
        region_info = (md_ss_region *)(ss_info->md_ss_smem_regions_baseptr);
        count       = ss_info->ss_region_count;

        while (count > 0)
        {
          /* loop through the list of regions */
          if (region_info->md_valid == MD_REGION_VALID)
          {
            /* Check address, size, seq_no and region name */
            if (!boot_is_region_valid(region_info))
            {
              /* Print skipped regions if validity check fails */
              snprintf(error_message, BOOT_ERROR_MSG_LEN, "MD: skip invalid region subsys_id:0x%08X name:%s base:0x%11X size:0x%11X", index, region_info->region_name, (uintnt)(region_info->region_base_address),(uintnt)(region_info->region_size));
              boot_log_message(error_message);
            }
            else if (ss_info->encryption_required == MD_SS_ENCR_REQ ||
                     (is_auth_enabled && (ss_info->encryption_status == MD_SS_ENCR_DONE)) ||
                     (!is_auth_enabled))
            {
              md_region_count++;
            }
          }
          /* count the number of invalid regions in a subsystem for logging */
          else
          {
            invalid_regions_count++;
          }

#ifdef MINIDUMP_FEATURE_DEBUG
          snprintf(error_message,
                  BOOT_ERROR_MSG_LEN,
                  "%08X\t%08X\t%08X\t%08X\t%08X\t%08X\t%08X\t%16s\t%16X\t%16X",
                  index,
                  ss_info->md_ss_toc_init,
                  ss_info->md_ss_enable_status,
                  ss_info->encryption_required,
                  ss_info->encryption_status,
                  ss_info->ss_region_count,
                  md_region_count,
                  region_info->region_name,
                  region_info->region_base_address,
                  region_info->region_size);
          boot_log_message(error_message);
#endif

          region_info++;
          count--;
        }

        if(invalid_regions_count)
        {
          snprintf(error_message, BOOT_ERROR_MSG_LEN, "MD: Subsys: 0x%04X invalid count: 0x%04X", index, invalid_regions_count);
          boot_log_message(error_message);
        }
      }
    }

  }while(FALSE);

  return status;
}

/*===========================================================================
**  Function :  boot_encrypt_and_get_md_regions
** ==========================================================================
*/
/*!
* 
* @brief
*   This function adds a new minidump region in boot sub-system minidump table
* 
* @param
*   config_context_handle     [in]    boot_handle
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
bl_error_boot_type boot_encrypt_and_get_md_regions(boot_handle config_context_handle, boot_boolean is_auth_enabled, uint8 *context, boot_minidump_region_type ** region_table, uint32 *region_count)
{
  bl_error_boot_type status = BL_ERR_NONE;
  uint32 index = 0, count = 0, md_region_count = 0;
  md_ss_toc    *ss_info = NULL;
  md_ss_region *region_info = NULL;
  static boot_boolean is_encryption_initialized = FALSE;
  boot_boolean is_key_valid = FALSE;
  char error_message[BOOT_ERROR_MSG_LEN] = "";
  char seq_num[MD_REGION_NAME_LENGTH] = "";
  boot_memory_mgr_if_type *mem_if = NULL;
  boot_blacklist_if_type *blacklist_if = NULL;
  boot_minidump_region_type * region_table_array = NULL;

  do
  {
    /* check passed arguments */
    if(config_context_handle == NULL || context == NULL || region_table == NULL || region_count == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_NULL_PTR_PASSED);
      goto exit;
    }

    /* return error if MD global TOC is not initialized */
    if (boot_md_get_global_mdtoc_addr() == NULL)
    {
      boot_log_message("MD: MD table is not initialized in SMEM");
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_INVALID_MINIDUMP_TABLE_ENTRY_PASSED);
      goto exit;
    }

    /* get total number of regions for allocating buffers */
    status = boot_get_md_region_count(&md_region_count);
    if(status != BL_ERR_NONE)
    {
      goto exit;
    }
    if(md_region_count == 0)
    {
      boot_log_message("MD: No regions registered in MD table");
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_INVALID_PARAMETER);
      goto exit;
    }

    /* get interfaces from config context */
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if(status != BL_ERR_NONE)
    {
      goto exit;
    }
    if(mem_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_BLACKLIST_INTERFACE, (void **)&blacklist_if);
    if(status != BL_ERR_NONE)
    {
      goto exit;
    }
    if(blacklist_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }

    /* initialize blacklist interface for checking overlapping regions */
    status = blacklist_if->init(config_context_handle);
    if(status != BL_ERR_NONE)
    {
      goto exit;
    }

    /* allocate buffer for storing regions to be returned to caller */
    status = mem_if->malloc((sizeof(boot_minidump_region_type)*md_region_count), (void*)&region_table_array);
    if(status != BL_ERR_NONE)
    {
      boot_log_message("MD: region_table heap err");
      goto exit;
    }
    if(region_table_array == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_MEMORY_ALLOC_FAIL);
      goto exit;
    }

    /* Initialize encryption artifacts required to perform encryption if auth is enabled */
    if (!is_encryption_initialized && is_auth_enabled)
    {
      status = boot_init_encryption_artifacts(config_context_handle, md_region_count, context);
      if(status != BL_ERR_NONE)
      {
        goto exit;
      }
      is_encryption_initialized = TRUE;
    }

    status = boot_print_minidump_region_info(is_auth_enabled);
    if(status != BL_ERR_NONE)
    {
      goto exit;
    }

    /* reset region_count */
    md_region_count = 0;

    /* Check every SS MD regions and encrypt if required*/
    for (index = 0; index < MD_SS_MAX; index++)
    {
      /* get subsystem toc for current index */
      ss_info = boot_md_get_subsystem_toc((md_subsys_type)index);

      /* skip subsystem if not initialized */
      if (ss_info == NULL || ss_info->md_ss_toc_init == 0)
        continue;
      
      /* Check if subsystem toc is enabled */
      if (ss_info->md_ss_enable_status == MD_SS_ENABLED)
      {
        /* get the region table and region count of current subsystem */
        region_info = (md_ss_region *)(ss_info->md_ss_smem_regions_baseptr);
        count       = ss_info->ss_region_count;

        while (count > 0)
        {
          /* Process the entry if region is valid */
          if(region_info->md_valid == MD_REGION_VALID && boot_is_region_valid(region_info))
          {
#ifdef FEATURE_SONY_RAMDUMP
            /* Skip adding XBL log region in minidump */
            if ((strncmp((char *)(region_info->region_name), "XBL_LOG", 7) == 0) ||
                (strncmp((char *)(region_info->region_name), "MD_XBL_LOG", 10) == 0))
            {
              region_info++;
              count--;
              continue;
            }
#endif /* FEATURE_SONY_RAMDUMP */

            /* add the region to region table if the below condititons are true 
              * 1. If regions are encrypted by ramdump *
              * 2. If auth is enabled and the subsystem is marked as encr done *
              * 3. If auth is disabled then we need to add all the regions */
            if(ss_info->encryption_required == MD_SS_ENCR_REQ || 
               (is_auth_enabled && (ss_info->encryption_status == MD_SS_ENCR_DONE)) || 
               (!is_auth_enabled))
            {
              region_table_array[md_region_count].region_base_address = region_info->region_base_address;
              region_table_array[md_region_count].region_size = region_info->region_size;

              memscpy(region_table_array[md_region_count].region_name, MD_REGION_NAME_LENGTH, region_info->region_name, MD_REGION_NAME_LENGTH);

              if((region_info->seq_num > 0) && (region_info->seq_num < UINT32_MAX))
              {
                snprintf(seq_num, MD_REGION_NAME_LENGTH, "%d", region_info->seq_num);
                strlcat(region_table_array[md_region_count].region_name, (const char *)seq_num, MD_REGION_NAME_LENGTH);
              }

              /* check if region needs to be encrypted */
              if(ss_info->encryption_required == MD_SS_ENCR_REQ)
              {

                /* if encryption is required, ensure regions are not overlapping */
                status = blacklist_if->check_region_and_update((uintnt)(region_info->region_base_address), (uintnt)(region_info->region_size));
                if(status != BL_ERR_NONE)
                {
                  snprintf(error_message, BOOT_ERROR_MSG_LEN, "MD: Error overlap subsys_id:0x%08X name:%s base:0x%llX size:0x%llX", index, region_info->region_name, (uintnt)(region_info->region_base_address), (uintnt)(region_info->region_size));
                  boot_log_message(error_message);
                  goto exit;
                }

                /* Encrypt region if auth is enabled */
                if(is_auth_enabled)
                {
                  /* ensure encryption artifacts are initialized */
                  status = boot_check_oem_key((boolean *)&is_key_valid);
                  if(status != BL_ERR_NONE)
                  {
                    goto clear_region_and_exit;
                  }
                  if(!is_key_valid)
                  {
                    status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_MD_ADD_REGION_FAIL);
                    goto clear_region_and_exit;
                  }

                  /* Encrypt the current region */
                  status = encrypt_minidump_region((uintnt *)(region_info->region_base_address), region_info->region_size, (uintnt *)(region_info->region_base_address), md_region_count);
                  if (status != BL_ERR_NONE)
                  {
                    goto clear_region_and_exit;
                  }
                }
              }

              /* decryption tools parse dumps by matching regions with IV and mac using indices. 
              * Therefore we need to match the indeices for all the regions with their IV and MAC in the dumped binaries 
              * md_region_count is incremented irrespective of region being encrypted or not. If region is not encrypted, IV and MAC at that idex will be zero */
              md_region_count++;
            }
          }

          region_info++;
          count--;
        }
      }
    }

    /* return region table array and region count to the caller */
    *region_table = (boot_minidump_region_type *)region_table_array;
    *region_count = md_region_count;
    goto exit;

  } while (FALSE);

clear_region_and_exit:
  boot_clear_md_regions(index);
exit:
  return status;
}

/*===========================================================================
**  Function :  boot_get_encryption_artifacts
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
bl_error_boot_type boot_get_encryption_artifacts(uint8 ** wrapped_key, uint32 * wrapped_key_size, uint8 ** iv_buffer, uint32 * iv_buffer_size, uint8 ** mac_buffer, uint32 * mac_buffer_size)
{
  if(wrapped_key == NULL || wrapped_key_size == NULL || iv_buffer == NULL || iv_buffer_size == NULL ||
     mac_buffer == NULL || mac_buffer_size == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_NULL_PTR_PASSED);
  }
  if(!_handle_null_check(handle))
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_NULL_PTR_PASSED);
  }

  /* Update the pointers with encryption artifacts details */
  *wrapped_key = (uint8 *)(handle->wrapped_keys_and_artifacts);
  *wrapped_key_size = (handle->wrapped_keys_and_artifacts_buffer_size);
  *iv_buffer = (uint8 *)(handle->iv_region_buffer);
  *iv_buffer_size = (handle->iv_region_buffer_size);
  *mac_buffer = (uint8 *)(handle->mac_region_buffer);
  *mac_buffer_size = (handle->mac_region_buffer_size);

  return BL_ERR_NONE;
}
