/*===========================================================================

                  BOOT MEMORY DEBUG HANDLER TABLE DEFINITIONS

DESCRIPTION
  Contains wrapper definition for populating sahara command handler table

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2020-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who     what, where, why
--------    ---     ----------------------------------------------------------
06/21/22   batta    Added support for Helios ramdumps.
05/25/22   rama     Changes for dynamically counting ramdump entries
05/18/22   rama     Move dal_if to mem_if
03/10/22   rama     Changes for moving minidump to ECDH based encryption
03/04/22   rama     minidump clean up phase 2
10/07/21   rama     Handle rd_table empty case in ramdump_table_get_table_len
07/16/21   rama     Moved to dbginfo lib
02/03/21   rhy      Enabled unrecoverable_error_handler for PIPO scenarios
11/11/20   rhy      Renamed is_dump_support to is_ramdump_allowed
08/13/20   rhy      Initial revision.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <stdio.h>
#include "boot_config_context.h"
#include "boot_error_if.h"
#include "Target_cust.h"
#include "boot_target.h"
#include "boot_ramdump_if.h"
#include "MIbib.h"
#include "boot_ramdump_table_if.h"
#include "boot_ramdump_table.h"
#include "boot_minidump.h"
#include "boot_ddr_info_if.h"
#include "boot_pmic_if.h"
#include "boot_memory_mgr_if.h"
#include "boot_crashdump.h"
#include "HALbootHWIO.h"
#include "HALhwio.h"
#include <seclib_defs.h>
#include <boot_dbginfo_if.h>
#include "boot_sbl_shared.h"
#include "sbl_crashdump_arch.h"
#include <boot_qsee_if.h>
#include <image_version.h>
#include <boot_dload_debug.h>

/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
#define MASK_FOR_COMPANION_CHIPS      0xF000000000

/* Memory debug handle ID */
#define ramdump_dload_handle_ID 0x4D444247

/* Memory debug handle */
typedef struct ramdump_dload_handle_obj
{
  boot_handle_common_type     handle_data;

  /* Uncached DDR ZI Zone pointer */
  ramdump_table_type    *ramdump_table_info;

  uint32                real_num_regions;

  uint32                max_num_of_entries;

  /* Pointer for storing load cmm script */
  char                  *cmm_script;

  boolean               region_table_fixed_length;

  boot_handle           target_specific_boot_handle;

} ramdump_table_handle;

static void _ramdump_len_init(ramdump_table_handle *);

typedef struct dload_restricted_region_dump_list
{
  uint64 mem_base;
  uint64 length;
  uint64 restricted_region_base;
  bl_error_boot_type (*dload_restricted_region_handler)(uint8 *buf, uint64 offset, uint64 length);
  struct dload_restricted_region_dump_list *pnext;
} dload_restricted_region_dump_list;

static dload_restricted_region_dump_list *prestrict_region_list_header = NULL;
static dload_restricted_region_dump_list *phandler= NULL;
static dload_restricted_region_dump_list *plist_last_region = NULL;


/*=============================================================================

FUNCTION DEFINITIONS

=============================================================================*/


/*===========================================================================

FUNCTION ramdump_table_add_entry

DESCRIPTION
  This function adds a region to ramdump_table_info[]

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
bl_error_boot_type ramdump_table_add_entry
(
  boot_handle handle_ptr,
  ramdump_table_save_pref_type save_pref,
  uintnt mem_base,
  uintnt length,
  char *desc,
  char *filename
)
{
  if (handle_ptr == NULL || desc == NULL || filename == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  ramdump_table_handle* handle = (ramdump_table_handle*) handle_ptr;
  uint32 index = handle->real_num_regions;
  uint32 desc_length = strlen(desc);
  uint32 filename_length = strlen(filename);
  ramdump_table_type *ramdump_table_info = handle->ramdump_table_info;

  /* Make sure we don't overrun array and align memory regions */
  if ((desc_length < DLOAD_DEBUG_STRLEN_BYTES) &&
      (filename_length < DLOAD_DEBUG_STRLEN_BYTES) &&
      (index < (handle->max_num_of_entries)))
  {
    ramdump_table_info[index].save_pref = save_pref;
    ramdump_table_info[index].mem_base  = mem_base & ~3;
    ramdump_table_info[index].length    = length  & ~3;
    strlcpy(ramdump_table_info[index].desc, desc, sizeof(ramdump_table_info[index].desc));
    strlcpy(ramdump_table_info[index].filename, filename, sizeof(ramdump_table_info[index].filename));

    handle->real_num_regions++;
  }
  else
  {
    DL_LOG ("RD:[Max %d][index %d] %s %s 0x%x 0x%x", handle->max_num_of_entries, index, filename, desc, mem_base, length);     
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_BUFFER_OVERFLOW);
  }

  return BL_ERR_NONE;
}

/*===========================================================================

FUNCTION RAMDUMP_TABLE_IS_RESTRICTED_ADDR

DESCRIPTION
  This function checks to see if it belongs to a restricted region of memory
  that is not directly accessible by H/W DMA.

DEPENDENCIES
  None.

RETURN VALUE
  TRUE if the address verifies, else FALSE.

SIDE EFFECTS
  None.

===========================================================================*/
boolean ramdump_table_is_restricted_addr(uint64 base, uint64 len)
{

  uint64 input_end_addr =0x0;

  input_end_addr = base + len - 1;
  if ((len == 0) || (input_end_addr < base))
  {
    return FALSE;
  }

  phandler = prestrict_region_list_header;
  if (phandler == NULL)
  {
    return FALSE;
  }

  while (phandler!=NULL)
  {
    if ((phandler->mem_base == base && phandler->length == len) || ((base + len) >= phandler->mem_base && (base + len) <= phandler->mem_base + phandler->length))
    {
      return TRUE;
    }
    phandler = phandler->pnext;
  }
  return FALSE;
}
/*===========================================================================

FUNCTION RAMDUMP_TABLE_COPY_RESTRICTED_REGION

DESCRIPTION
  This function is used to read the data from restricted region by correspoding
  handler.

DEPENDENCIES
  None.

RETURN VALUE
  bl_error_boot_type

SIDE EFFECTS
  None.

===========================================================================*/

bl_error_boot_type ramdump_table_copy_restricted_region(uint8 *buf, uint64 addr, uint64 len)
{
  if (phandler == NULL)
  {
    return FALSE;
  }
  return phandler->dload_restricted_region_handler(buf, (addr - phandler->restricted_region_base), len);
}

/*===========================================================================

FUNCTION dload_init_restrict_node

DESCRIPTION
  Initialize a new node of restricted regions link list

DEPENDENCIES
  None.

RETURN VALUE
  TRUE if success, else FALSE.

SIDE EFFECTS
  None.

===========================================================================*/

bl_error_boot_type dload_init_restrict_node(dload_restricted_region_dump_list **pnode)
{
  boot_memory_mgr_if_type *mem_if = NULL;
  bl_error_boot_type error = BL_ERR_NONE;
  dload_restricted_region_dump_list *plist = NULL;
  do
  {
    error = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (error != BL_ERR_NONE)
    {
      break;
    }
    error = mem_if->malloc(sizeof(dload_restricted_region_dump_list), (void *)pnode);
    if (error != BL_ERR_NONE)
    {
      break;
    }
    plist = *pnode;
    plist->dload_restricted_region_handler = NULL;
    plist->length = 0;
    plist->mem_base = 0;
    plist->restricted_region_base = 0;
    plist->pnext= NULL;
  } while (FALSE);
  return error;
}

/*===========================================================================

FUNCTION RAMDUMP_TABLE_ADD_RESTRICTED_REGION

DESCRIPTION
  This function adds a restricted region which needs specific handler for read
  each regions
DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
bl_error_boot_type ramdump_table_add_restricted_region
(
  boot_handle handle_ptr,
  uint64 addr,
  uint64 length,
  char *desc,
  char *filename,
  void *handler
)
{
  uint32 i = 0;
  bl_error_boot_type error = BL_ERR_NONE;
  dload_restricted_region_dump_list * plist = NULL;
  dload_restricted_region_dump_list * plist_prior = NULL;
  uint64 mem_base = 0;

  ramdump_table_handle* handle = (ramdump_table_handle*) handle_ptr;
  i = handle->real_num_regions;

  do
  {
    /* Make sure we don't overrun array and align memory regions */
    if (i < handle->max_num_of_entries)
    {
      if (prestrict_region_list_header == NULL)
      {
        error =  dload_init_restrict_node(&plist);
        if (error != BL_ERR_NONE)
        {
          break;
        }

        prestrict_region_list_header = plist;
        /* If the address is not 0, then the region being added is from the companion chips */
        if(addr != 0) {
           mem_base = addr;
        } else {
           mem_base = SCL_BOOT_MEMORY_RESTRICT_REGION_BASE;
        }
      }
      else
      {
        plist = prestrict_region_list_header;
        plist_prior = plist;

        /*Look for the end of restrict region link list */
        while (plist->pnext!=NULL)
        {
          plist=plist->pnext;
          plist_prior = plist;
        }

        error =  dload_init_restrict_node(&plist);
        if (error != BL_ERR_NONE)
        {
          break;
        }

        /* If the address is not 0, then the region being added is from the companion chips */
        if(addr != 0) {
           mem_base = addr;
        } else {
           mem_base  = plist_last_region->mem_base + plist_last_region->length;
        }
        plist_prior->pnext = plist;
      }

      if (handler == NULL)
      {
        break;
      }

      plist->dload_restricted_region_handler = handler;
      plist->length = length;
      plist->mem_base = mem_base;
      /* Save the pointer to node of the last added region when addr is NULL. */
      if(addr == 0) {
         plist_last_region = plist;
      }
      if(addr != 0) {
         plist->restricted_region_base = (plist->mem_base & MASK_FOR_COMPANION_CHIPS);
      } else {
         plist->restricted_region_base = plist->mem_base;
      }

      error = ramdump_table_add_entry(handle,
                                      RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                      plist->mem_base,
                                      plist->length,
                                      desc,
                                      filename);
      if (error != BL_ERR_NONE)
      {
        break;
      }
    }
  } while (0);

  return error;
}
/*=========================================================================

**  Function :  _init_handle

** ==========================================================================
*/
/*!
*
* @brief
*   Malloc ramdump_table_type and cmm script handle.
*
*/
static bl_error_boot_type _init_handle(const boot_handle config_context_handle,
                                       ramdump_table_handle *handle,
                                       boot_memory_mgr_if_type *mem_if,
                                       uint32 rd_table_number_of_entries)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if (config_context_handle == NULL || handle == NULL || mem_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  do
  {
    /* Malloc Uncache memory for ramdump_table_info */
    status = mem_if->malloc(rd_table_number_of_entries * sizeof(ramdump_table_type), (void **)&(handle->ramdump_table_info));
    if((status != BL_ERR_NONE) || ((handle->ramdump_table_info) == NULL))
    {
      DL_LOG("RD: heap err, no space for %d rd entries", rd_table_number_of_entries);
      if(((handle->ramdump_table_info) == NULL))
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MEMORY_ALLOC_FAIL);
      }
      break;
    }

    memset((void *)(handle->ramdump_table_info), 0x0, rd_table_number_of_entries * sizeof(ramdump_table_type));

    /* Malloc memory for cmm script */
    status = mem_if->malloc(SCRIPT_BUF_SIZE, (void **)&(handle->cmm_script));
    if ((status != BL_ERR_NONE) || ((handle->cmm_script) == NULL))
    {
      break;
    }

    memset((void *)(handle->cmm_script), 0x0, SCRIPT_BUF_SIZE);

    handle->region_table_fixed_length = FALSE;

    handle->max_num_of_entries = rd_table_number_of_entries;

    /* Setting boot handle common type */
    (handle->handle_data).id                    = ramdump_dload_handle_ID;
    (handle->handle_data).config_context_handle = config_context_handle;

  } while (FALSE);

  return status;
}

/*=========================================================================

**  Function :  ramdump_add_minidump_regions

** ==========================================================================
*/
/*!
*
* @brief
*   Function to check for minidump encryption artifacts and add them to ramdump 
*   table
*
* @param[in] pointer to config context handle, pointer to mem debug handle pointer
*
*
*/
static bl_error_boot_type ramdump_add_minidump_regions(const boot_handle config_context_handle, ramdump_table_handle *handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_dbginfo_if_type *dbginfo_if = NULL;
  boot_boolean is_auth_enabled = FALSE;
  uint8 * wrapped_key = NULL;
  uint8 * iv_buffer = NULL;
  uint8 * mac_buffer = NULL;
  uint32 index = 0;
  uint32 wrapped_key_size = 0;
  uint32 iv_buffer_size = 0;
  uint32 mac_buffer_size = 0;
  uint32 region_count = 0;
  boot_minidump_region_type * region_list = NULL;
  char dump_region_name[DLOAD_DEBUG_STRLEN_BYTES] = {0};
  char dump_region_bin_name[DLOAD_DEBUG_STRLEN_BYTES] = {0};
  uint8 *xbl_rd_md_context = (uint8 *)MD_CONTEXT_XBL_RD;

  if(config_context_handle == NULL || handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }
  do
  {

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_DBGINFO_INTERFACE, (void **)&dbginfo_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    if(dbginfo_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* check if secure boot is enabled */
    status = dbginfo_if->is_auth_enabled(&is_auth_enabled);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    /* if secure boot is enbled, perform encryption for regions that need to be encrypted */
    status = boot_encrypt_and_get_md_regions(config_context_handle, is_auth_enabled, xbl_rd_md_context, &region_list, &region_count);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    if(region_list == NULL || region_count == 0)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* iterate through minidump region list and add each region to ramdump table */
    for(index = 0;index < region_count; index++)
    {
      /* string manipulation for getting file name and dump file name */
      strlcat(dump_region_name, "md_", DLOAD_DEBUG_STRLEN_BYTES);
      strlcat(dump_region_name, (const char *)region_list[index].region_name, MD_REGION_NAME_LENGTH);
      strlcpy(dump_region_bin_name, dump_region_name, DLOAD_DEBUG_STRLEN_BYTES);
      strlcat(dump_region_bin_name, ".BIN", DLOAD_DEBUG_STRLEN_BYTES);

      /* add the region to dump table */
      status = ramdump_table_add_entry(handle,
                                        RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                        (region_list[index].region_base_address),
                                        (region_list[index].region_size),
                                        dump_region_name,
                                        dump_region_bin_name);
      if(status != BL_ERR_NONE)
      {
        return status;
      }

      /* clear string manipulation buffers */
      memset(dump_region_name, 0x0, sizeof(dump_region_name));
      memset(dump_region_bin_name, 0x0, sizeof(dump_region_bin_name));

    }
    
    /* If auth is enabled, Collect encryption artifacts and add to dump table */
    if(is_auth_enabled)
    {

      /* get encryption artifacts from minidump */
      status = boot_get_encryption_artifacts(&wrapped_key, &wrapped_key_size, &iv_buffer, &iv_buffer_size, &mac_buffer, &mac_buffer_size);
      if(status != BL_ERR_NONE)
      {
        break;
      }

      /* check if encryption artifacts are valid */
      if(wrapped_key == NULL || wrapped_key_size == 0 ||
          iv_buffer == NULL || iv_buffer_size == 0 ||
          mac_buffer == NULL || mac_buffer_size == 0)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
        break;
      }

      /* add encryption artifacts to dump table */
      status = ramdump_table_add_entry(handle,
                                        RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                        (uintnt)wrapped_key,
                                        wrapped_key_size,
                                        "Encrypted AES Key",
                                        "md_wrpd_keys.BIN");
      if(status != BL_ERR_NONE)
      {
        break;
      }

      status = ramdump_table_add_entry(handle,
                                        RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                        (uintnt)iv_buffer,
                                        iv_buffer_size,
                                        "IV Key region",
                                        "md_encr_iv.BIN");
      if(status != BL_ERR_NONE)
      {
        break;
      }


      status = ramdump_table_add_entry(handle,
                                        RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                        (uintnt)mac_buffer,
                                        mac_buffer_size,
                                        "MAC region",
                                        "md_encr_mac.BIN");
      if(status != BL_ERR_NONE)
      {
        break;
      }
    }
  }while(FALSE);
  
  return status;
}


/*=========================================================================

**  Function :  ramdump_table_open

** ==========================================================================
*/
/*!
*
* @brief
*   Function to get boot memory debug handle and return the mem debug handle
*   to client.
*
* @param[in] pointer to config context handle, pointer to mem debug handle pointer
*
*
*/
static bl_error_boot_type ramdump_table_open (const boot_handle config_context_handle, boot_handle *handle_ptr)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if =  NULL;
  ramdump_table_handle *handle =  NULL;
  boot_ramdump_if_type *ramdump_if =  NULL;
  ramdump_table_type *ramdump_table_info = NULL;
  uint32  print_size = 0;
  uint32 loop = 0;
  uint32 target_dependent_number_of_rd_entries = 0;
  uint32 index = 0;
  uint32 ramdump_table_entries_count = 0;
  uint32 md_region_count = 0;
  uint32 bufsize = SCRIPT_BUF_SIZE;
  boot_boolean dload_flag;
  char *script_ptr = NULL;

  if (config_context_handle == NULL || handle_ptr == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Malloc mem debug handle */
    status = mem_if->malloc(sizeof(ramdump_table_handle), (void **)&handle);
    if ((status != BL_ERR_NONE))
    {
      break;
    }
    if(handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MEMORY_ALLOC_FAIL);
      break;
    }

    memset((void *)(handle), 0x0, sizeof(ramdump_table_handle));

    /* Get Static Entries */
    ramdump_table_memory_region dump_regions[] = {MEMORY_REGION_TABLE};

    /* Calculate the number of Static entries */
    index = 0;
    while ( dump_regions[index].region_base != 0 )
    {
      index++;
    }

    /* Get number of Dynamic entries from Target */
    status = ramdump_table_target_get_entries_count(&target_dependent_number_of_rd_entries);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_INTERFACE, (void **)&ramdump_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if(ramdump_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    dload_flag = ramdump_if->get_saved_cookie();

    /* Get number of minidump entries */
    if(dload_flag & SBL_MINIDUMP_MODE_BIT_MASK)
    {
      /* set minidump region count to 0 */
      md_region_count = 0;
      /* ignore error if minidump table is not initialized in SMEM */
      boot_get_md_region_count(&md_region_count);
    }

    /* Calculate the number of regions that will be added to ramdump table to initialize the table */
    ramdump_table_entries_count = index + 
                                  target_dependent_number_of_rd_entries + 
                                  md_region_count + 
                                  MD_ENCRYPTION_ARTIFACTS_COUNT;

    /* Initialize ramdump_table_info, cmm_script */
    status = _init_handle(config_context_handle, handle, mem_if, ramdump_table_entries_count);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Set memory region table to be fixed length, required by sahara*/
    _ramdump_len_init(handle);

    /**********************************WARNING**************************************
    Please make sure all dump region file names follow the 8.3 file name format!
    ********************************************************************************/

    /* Check if DLOAD flag is set, if not only minidump regions are to be dumped */
    if (dload_flag & SBL_DLOAD_MODE_BIT_MASK)
    {
      index = 0;

      /* RAM-DUMP table defined in .builds file */
      while ( dump_regions[index].region_base != 0 )
      {
        status = ramdump_table_add_entry(handle,
                                                RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                                dump_regions[index].region_base,
                                                dump_regions[index].region_size,
                                                dump_regions[index].desc,
                                                dump_regions[index].filename
                                               );

        if (status != BL_ERR_NONE)
        {
          goto exit;
        }
        index++;
      }
    }

    /*  Get SOC specific Regions and then add in ramdump_table_info. Keep the Target specific memory handle and free it the close() is called.  */
    status = ramdump_table_target_init (config_context_handle, handle, &(handle->target_specific_boot_handle) );
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (dload_flag & SBL_MINIDUMP_MODE_BIT_MASK)
    {
      status = ramdump_add_minidump_regions(config_context_handle, handle);
      if(status != BL_ERR_NONE)
      {
        break;
      }

    }

    /*  Initialize the script for the regions we just added.
        cmm_script has been allocated. It is freed it when close() is called. */
    script_ptr = handle->cmm_script;

    /* Add build info that is appended in load.cmm */
    print_size = snprintf (script_ptr,
                           POS(bufsize),
                           "; Build ID: %s @ %s @ %s @ %s\n",
                           QC_IMAGE_VERSION_STRING_AUTO_UPDATED,
                           OEM_IMAGE_VERSION_STRING_AUTO_UPDATED,
                           __TIME__,
                           __DATE__);

    script_ptr+= print_size;
    bufsize-=print_size;

    ramdump_table_info = handle->ramdump_table_info;

    for (loop = 0; loop < (handle->real_num_regions); loop++)
    {
      /* Move s to the end of string after printing the string */
      print_size = snprintf(script_ptr, POS(bufsize),
                            "if OS.FILE(%s)\n"
                            "(\n"
                            "  d.load.binary %s 0x%lx /noclear\n"
                            ")\n",

                            ramdump_table_info[loop].filename,
                            ramdump_table_info[loop].filename,
                            ramdump_table_info[loop].mem_base);
      script_ptr += print_size;
      bufsize -= print_size;
    }

    /*  Pad the end of the script so it does not get truncated when the length of
    *   the region gets masked to 32-bit boundaries */
    (void)snprintf(script_ptr, POS(bufsize), "\n\n\n");

    status = ramdump_table_add_entry(handle,
                                            RAMDUMP_TABLE_MANDATORY,
                                            (uintnt)handle->cmm_script,
                                            (uintnt)strlen(handle->cmm_script),
                                            "CMM Script",
                                            "load.cmm"
                                           );
    if (status != BL_ERR_NONE)
    {
      break;
    }

    *handle_ptr = (boot_handle)handle;

  } while (FALSE);

exit:
  return status;
}




/*===========================================================================

FUNCTION RAMDUMP_TABLE_LEN_INIT

DESCRIPTION
  This function sets the length of the memory region table to be fixed length.
  This is used to add support for Sahara memory dumps that require a fixed
  length memory region table when ramdump_table_len called.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
static void _ramdump_len_init(ramdump_table_handle *handle)
{
  handle->region_table_fixed_length = TRUE;
}

/*=========================================================================

**  Function :  _deinit_handle

** ==========================================================================
*/
/*!
*
* @brief
*   Free the ramdump table handle.
*
*/
static bl_error_boot_type _deinit_handle(const boot_handle config_context_handle,
    ramdump_table_handle *handle,
    boot_memory_mgr_if_type *mem_if)
{
  bl_error_boot_type status = BL_ERR_NONE;

  do
  {
    handle->real_num_regions = 0;
    handle->max_num_of_entries = 0;

    /* Free Uncache memory for ramdump_table_info */
    status = mem_if->free((void *)(handle->ramdump_table_info));
    if (status != BL_ERR_NONE)
    {
      break;
    }
    handle->ramdump_table_info = NULL;

    /* Free memory for cmm script */
    status = mem_if->free((void *)(handle->cmm_script));
    if (status != BL_ERR_NONE)
    {
      break;
    }

    handle->cmm_script = NULL;

  } while (FALSE);

  return status;
}

/*=========================================================================

**  Function :  ramdump_table_supported

** ==========================================================================
*/
/*!
*
* @brief
*   Function to check whether ram/mini dump collection is supported from QSEE
*
* @param[in] pointer to config context handle, pointer to dump supported
*
*
*/
static bl_error_boot_type ramdump_table_supported(boot_handle config_context_handle, boot_boolean *dump_supported)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_dbginfo_if_type *dbginfo_if = NULL;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_DBGINFO_INTERFACE, (void **)&dbginfo_if);
  if(status != BL_ERR_NONE || dbginfo_if == NULL)
    return status;

  status = dbginfo_if->is_ramdump_allowed((boot_boolean*)dump_supported);
  return status;
}

/*=========================================================================

**  Function :  ramdump_table_get_table_addr

** ==========================================================================
*/
/*!
*
* @brief
*   Function to return ramdump_table_info pointer to client.
*
* @param[in] pointer to mem debug handle pointer
*
*
*/
static bl_error_boot_type ramdump_table_get_table_addr(boot_handle handle, uintnt *rd_entries_ptr)
{
  ramdump_table_handle *handle_ptr = NULL;
  if (handle == NULL || rd_entries_ptr == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  handle_ptr = (ramdump_table_handle*)handle;
  *rd_entries_ptr = (uintnt)handle_ptr->ramdump_table_info;
  return BL_ERR_NONE;
}

/*=========================================================================

**  Function :  ramdump_table_get_table_len

** ==========================================================================
*/
/*!
*
* @brief
*   Function to return ramdump_table_info pointer to client.
*
* @param[in] pointer to mem debug handle pointer
*
*
*/
static bl_error_boot_type ramdump_table_get_table_len(boot_handle handle, uintnt *table_len_in_bytes)
{
  ramdump_table_handle *handle_ptr = NULL;
  uint32 total_bytes = 0;
  bl_error_boot_type status = BL_ERR_NONE;

  if (handle == NULL || table_len_in_bytes == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  handle_ptr = (ramdump_table_handle*)handle;
  if(handle_ptr-> real_num_regions == 0)
  {
    *table_len_in_bytes = 0;
    goto exit;
  }

  total_bytes = (handle_ptr->real_num_regions) * sizeof(ramdump_table_type);

  /* Check for overflow */
  if ((total_bytes/(handle_ptr->real_num_regions)) == sizeof(ramdump_table_type))
  {
    *table_len_in_bytes = total_bytes;
  }
  else
  {
    *table_len_in_bytes = 0;
    status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INTEGER_OVERFLOW);
  }

exit:
  return status;
}

/*=========================================================================

**  Function :  ramdump_table_verify_addr

** ==========================================================================
*/
/*!
*
* @brief
*   Function to return ramdump_table_info pointer to client.
*
* @param[in] pointer to mem debug handle pointer
*
*
*/
static bl_error_boot_type ramdump_table_verify_addr
(
  boot_handle handle_ptr,
  uint64 base,
  uint64 len,
  boot_boolean *verified_address
)
{
  bl_error_boot_type status = BL_ERR_NONE;
  uint64 input_end_addr =0x0, table_end_addr =0x0;
  ramdump_table_handle *handle = NULL;
  uint32 loop;
  ramdump_table_type *entry = NULL;

  if (handle_ptr == NULL || verified_address == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  *verified_address = FALSE;

  handle = (ramdump_table_handle *)handle_ptr;
  input_end_addr = base + len - 1;

  do
  {
    if ((len == 0) || (input_end_addr < base))
    {
      break;
    }

    /* if region falls within region table itself then return TRUE */
    if (base >= (uint64)handle->ramdump_table_info)
    {
      table_end_addr = (uint64)(handle->ramdump_table_info) +
                       (uint64)(sizeof(ramdump_table_type) * (handle->max_num_of_entries)) - 1;
      if (input_end_addr <= table_end_addr)
      {
        *verified_address = TRUE;
        break;
      }
    }

    entry = handle->ramdump_table_info;
    for (loop = 0; loop < handle->real_num_regions; loop++)
    {
      if (base >= entry[loop].mem_base)
      {
        table_end_addr = (uint64)(entry[loop].mem_base) + (uint64)(entry[loop].length) - 1;
        if (input_end_addr <= table_end_addr)
        {
          *verified_address = TRUE;
          break;
        }
      }
    }

  } while (FALSE);

  return status;
}

/*=========================================================================

**  Function :  ramdump_table_verify_restricted_addr

** ==========================================================================
*/
/*!
*
* @brief
*   Function to get boot memory debug handle and return the mem debug handle
*   to client.
*
*   Stub function for now
*
*
*/
static bl_error_boot_type ramdump_table_verify_restricted_addr
(
  boot_handle handle_ptr,
  uint64 base,
  uint64 len,
  boot_boolean *verified_address
)
{
  if (handle_ptr == NULL || verified_address == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  *verified_address = ramdump_table_is_restricted_addr (base, len);
  return BL_ERR_NONE;
}

/*=========================================================================

**  Function :  ramdump_table_close

** ==========================================================================
*/
/*!
*
* @brief
*   Function to get boot memory debug handle and return the mem debug handle
*   to client.
*
* @param[in] pointer to config context handle, pointer to mem debug handle pointer
*
*
*/
static bl_error_boot_type ramdump_table_close(const boot_handle config_context_handle, boot_handle handle_ptr)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if =  NULL;
  ramdump_table_handle *handle = NULL;

  if (config_context_handle == NULL || handle_ptr == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  handle = (ramdump_table_handle *)handle_ptr;

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    status = _deinit_handle(config_context_handle, handle, mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    ramdump_table_target_deinit(config_context_handle, handle->target_specific_boot_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    handle->target_specific_boot_handle = NULL;

    status = mem_if->free((void *)handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }

  } while (FALSE);

  return status;
}

/* ==========================================================================

**  Function :  boot_ramdump_table_get_interface

** ==========================================================================
*/
/*!
*
* @brief
*   Initialize boot memory debug handler table.
*
* @param[in]
*
*/
bl_error_boot_type boot_ramdump_table_get_interface(void *ramdump_if)
{
  if (ramdump_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  ((ramdump_table_if *)ramdump_if)->open                        = ramdump_table_open;
  ((ramdump_table_if *)ramdump_if)->is_ramdump_allowed          = ramdump_table_supported;
  ((ramdump_table_if *)ramdump_if)->get_table_addr              = ramdump_table_get_table_addr;
  ((ramdump_table_if *)ramdump_if)->get_table_len               = ramdump_table_get_table_len;
  ((ramdump_table_if *)ramdump_if)->verify_addr                 = ramdump_table_verify_addr;
  ((ramdump_table_if *)ramdump_if)->verify_restricted_addr      = ramdump_table_verify_restricted_addr;
  ((ramdump_table_if *)ramdump_if)->copy_restricted             = ramdump_table_copy_restricted_region;
  ((ramdump_table_if *)ramdump_if)->unrecoverable_error_handler = ramdump_table_target_unrecoverable_error_handler;
  ((ramdump_table_if *)ramdump_if)->close                       = ramdump_table_close;

  return BL_ERR_NONE;
}
