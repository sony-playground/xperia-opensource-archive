/*===========================================================================

                              Minidump table parser

GENERAL DESCRIPTION
  This module scans the SMEM location to read address/size pair and populates
  them it to memory dump table

Copyright 2017,2020-2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================
                           EDIT HISTORY FOR FILE
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     -------------------------------------------------------
10/07/21   rama    Changes for error handling
08/09/21   rama    add encryption artifacts only if region are encrypted in Ramdump
06/22/21   rama    added MD_SS_MAX in place of MAX_NUM_OF_SS
06/02/21   ds      minidump changes
02/12/21   vk      Move to lib and ramdump table
12/12/17   aus     Updated structures as packed
12/12/17   aus     Updated structures as packed
11/02/17   aus     Added support for seq_num append
10/12/17   aus     Updated functions and structures as per design
02/02/17   bd      Call smem_init for minidump case
01/17/17   bd      Initial version

=============================================================================*/


/*==========================================================================

                   INCLUDE FILES

===========================================================================*/
#include <string.h>
#include <boot_ramdump_if.h>
#include <boot_ramdump_table_if.h>
#include <boot_ramdump_table.h>
#include "boot_minidump.h"
#include "boot_shared_imem_cookie.h"
#include "boot_error_if.h"
#include "boot_ramdump_wrapper_apis.h"
#include "smem.h"
#include "smem_type.h"
#include "boot_logger.h"
#include "boot_ddr_info.h"
#include "cil_common.h"
#include "boot_target.h"
#include <boot_dbginfo_if.h>

md_global_toc  *md_global_toc_smem_base = NULL;

/*=============================================================================

        LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

static bl_error_boot_type dload_debug_encr_all_regions (boot_handle config_context_handle, boot_handle ramdump_table_handle, uint32 start_index, uint32 num_regions)
{
  bl_error_boot_type status = BL_ERR_NONE;
  ramdump_table_if *rd_table_if = NULL;
  ramdump_table_type *rd_table_ptr = NULL;
  uint32 i = 0;
  uint64 r_base = 0, r_len = 0;
  uintnt rd_table_len = 0;

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void **)&rd_table_if);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("get_ptr error");
      break;
    }
    if (ramdump_table_handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_INVALID_MINIDUMP_TABLE_ENTRY_PASSED);
      break;
    }

    status = rd_table_if->get_table_len(ramdump_table_handle, &rd_table_len);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    rd_table_len/=sizeof(ramdump_table_type);

    status = rd_table_if->get_table_addr(ramdump_table_handle, (uintnt*)&rd_table_ptr);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    for (i=start_index; i < rd_table_len; i++)
    {
      r_base = rd_table_ptr[i].mem_base;
      r_len = rd_table_ptr[i].length;
      status = cil_md_encrypt_region(r_base, r_len, i);
      if(status != BL_ERR_NONE)
      {
        break;
      }
    }
  } while (FALSE);

  return status;
}

static bl_error_boot_type dload_debug_crypto_init(void)
{
  return cil_md_crypto_init();
}

static bl_error_boot_type dload_debug_add_encryption_aritfacts(boot_handle ramdump_table_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  status = cil_md_add_unencr_regions(ramdump_table_handle);
  if (status != BL_ERR_NONE)
  {
    return status;
  }

  return status;
}

static bl_error_boot_type dload_debug_check_oem_key(boot_handle config_context_handle, boot_handle ramdump_table_handle, uint32 start_index, uint32 num_regions)
{
  bl_error_boot_type status = BL_ERR_NONE;
  ramdump_table_if *rd_table_if = NULL;
  ramdump_table_type *rd_table_ptr = NULL;
  uintnt rd_table_len = 0;
  int i = 0;
  uint64 r_base = 0, r_len = 0;
  boolean oem_key_result = FALSE;

  do
  {
    status = boot_check_oem_key(&oem_key_result);
    if(status != BL_ERR_NONE)
    {
      boot_log_message("boot_check_oem_key error");
      break;
    }

    if(!oem_key_result)
    {
      status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void **)&rd_table_if);
      if (status != BL_ERR_NONE)
      {
        boot_log_message("get_ptr error");
        break;
      }

      status = rd_table_if->get_table_len(ramdump_table_handle, &rd_table_len);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      rd_table_len/=sizeof(ramdump_table_type);

      status = rd_table_if->get_table_addr(ramdump_table_handle, (uintnt*)&rd_table_ptr);

      if (status != BL_ERR_NONE)
      {
        break;
      }

      for (i=start_index; i < rd_table_len; i++)
      {
        r_base = rd_table_ptr[i].mem_base;
        r_len = rd_table_ptr[i].length;
        memset((void*)r_base, 0, r_len);
      }
    }
  } while (FALSE);

  return status;
}
/*===========================================================================

FUNCTION itoa

DESCRIPTION
  This function adds a region  dump table

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
static void itoa(char *p, uint32 x)
{
  uint32 rem, j, i = 0;
  char temp;

  // Process individual digits
  while (x != 0)
  {
    rem = x % 10;
    p[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
    x = x/10;
  }

  // Append string terminator
  p[i] = '\0';

  // Reverse the string
  j = i - 1;
  i = 0;
  while (i < j)
  {
    temp = p[i];
    p[i] = p[j];
    p[j] = temp;
    i++;
    j--;
  }
}

static bl_error_boot_type add_one_region_to_dump(void *handle, md_ss_region *r)
{
  bl_error_boot_type status = BL_ERR_NONE;
  char dump_region_name[DLOAD_DEBUG_STRLEN_BYTES] = "md_";
  char dump_region_bin_name[DLOAD_DEBUG_STRLEN_BYTES];
  char seq_num[5] = {0};

  strlcat(dump_region_name, (const char *)r->region_name, MD_REGION_NAME_LENGTH);

  if ((r->seq_num > 0) && (r->seq_num < 10000))
  {
    itoa(seq_num, r->seq_num);
    strlcat(dump_region_name, (const char *)seq_num, MD_REGION_NAME_LENGTH);
  }

  strlcpy(dump_region_bin_name, dump_region_name, DLOAD_DEBUG_STRLEN_BYTES);
  strlcat(dump_region_bin_name, ".BIN", DLOAD_DEBUG_STRLEN_BYTES);

  status = ramdump_table_add_entry(handle,
                                   RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                   (r->region_base_address),
                                   (r->region_size),
                                   dump_region_name,
                                   dump_region_bin_name);

  return status;
}

/*===========================================================================

FUNCTION md_get_smem_base_address

DESCRIPTION
  This function initializes the smem base address for minidump region

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void md_get_smem_base_address(void)
{
  uint32 md_smem_size = sizeof(md_global_toc);

  smem_init();

  md_global_toc_smem_base = (md_global_toc *)smem_get_addr( SBL_MINIDUMP_SMEM_ID, &md_smem_size);
}

/*===========================================================================

FUNCTION add_minidump_regions

DESCRIPTION
  This function adds all minidump regions into dump table

DEPENDENCIES
  None.

RETURN VALUE
  BL_ERR_NONE on success.

SIDE EFFECTS
  None.

===========================================================================*/
bl_error_boot_type add_minidump_regions (boot_handle config_context_handle, boot_handle ramdump_table_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  ramdump_table_if *rd_table_if = NULL;
  uintnt rd_table_len = 0;
  uint32 index = 0, count = 0, start_index = 0;
  boot_boolean is_auth_enabled = FALSE;
  md_ss_toc    ss_info;
  md_ss_region *region_info = NULL;
  boot_dbginfo_if_type *dbginfo_if = NULL;
  static boot_boolean is_encryption_initialized = FALSE;

  do
  {
    if((config_context_handle == NULL) || (ramdump_table_handle == NULL))
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_NULL_PTR_PASSED);
      goto exit;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void **)&rd_table_if);
    if (status != BL_ERR_NONE || rd_table_if == NULL)
    {
      break;
    }

    md_get_smem_base_address();

    /* If MD global TOC is not initialized */
    if ( NULL == md_global_toc_smem_base )
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_INVALID_MINIDUMP_TABLE_ENTRY_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_DBGINFO_INTERFACE, (void *)&dbginfo_if);
    if(status != BL_ERR_NONE || dbginfo_if == NULL)
    {
      break;
    }

    status = dbginfo_if->is_auth_enabled(&is_auth_enabled);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    /* Check every SS MD regions and add to the dump table */
    for (index = 0; index < MD_SS_MAX; index++)
    {
      ss_info = md_global_toc_smem_base->md_ss_toc[index];

      if (ss_info.md_ss_toc_init == 0)
        continue;

      /* Check if XBL needs to encrypt the regions */
      if ((ss_info.md_ss_enable_status == MD_SS_ENABLED) &&
          (ss_info.encryption_required == MD_SS_ENCR_REQ))
      {

        if (is_auth_enabled && !is_encryption_initialized)
        {
          status = dload_debug_crypto_init();
          if(status != BL_ERR_NONE)
          {
            return status;
          }
          is_encryption_initialized = TRUE;
        }
        region_info = (md_ss_region *)ss_info.md_ss_smem_regions_baseptr;
        count       = ss_info.ss_region_count;

        status      = rd_table_if->get_table_len(ramdump_table_handle, &rd_table_len);
        if (status != BL_ERR_NONE)
        {
          break;
        }

        start_index = rd_table_len/sizeof(ramdump_table_type);

        while (count > 0)
        {
          if ((region_info->md_valid == MD_REGION_VALID) &&
              (region_info->region_name != NULL))
          {
            status = add_one_region_to_dump(ramdump_table_handle, region_info);
            if (status != BL_ERR_NONE)
            {
              goto exit;
            }
          }

          region_info++;
          count--;
        }

        /* Get updated dump table length */
        status = rd_table_if->get_table_len(ramdump_table_handle, &rd_table_len);
        if (status != BL_ERR_NONE)
        {
          break;
        }

        if (is_auth_enabled)
        {
          status = dload_debug_check_oem_key (config_context_handle, ramdump_table_handle, start_index, rd_table_len);
          if (status != BL_ERR_NONE)
          {
            break;
          }
          status = dload_debug_encr_all_regions (config_context_handle, ramdump_table_handle, start_index, rd_table_len);
          if (status != BL_ERR_NONE)
          {
            break;
          }
        }
      }

      /* Check if MD is enabled and encryption status is complete */
      else if ( (ss_info.md_ss_enable_status == MD_SS_ENABLED) &&
                ((is_auth_enabled && (ss_info.encryption_status == MD_SS_ENCR_DONE)) ||
                 (!is_auth_enabled)) )
      {
        region_info = (md_ss_region *)ss_info.md_ss_smem_regions_baseptr;
        count       = ss_info.ss_region_count;

        while (count > 0)
        {
          if ((region_info->md_valid == MD_REGION_VALID) &&
              (region_info->region_name != NULL))
          {
            status = add_one_region_to_dump(ramdump_table_handle, region_info);
            if (status != BL_ERR_NONE)
            {
              status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_INVALID_MINIDUMP_TABLE_ENTRY_PASSED);
              goto exit;
            }
          }

          region_info++;
          count--;
        }
      }
    }

    if(is_auth_enabled && is_encryption_initialized)
    {
      status = dload_debug_add_encryption_aritfacts(ramdump_table_handle);
      if (status != BL_ERR_NONE)
      {
        break;
      }
    }

  } while (FALSE);

exit:
  return status;
}
