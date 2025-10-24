/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                          MEMORY DEBUG INFORMATION

GENERAL DESCRIPTION
  This module defines the memory debug information to be sent to host

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

Copyright 2005-2006, 2010-2015, 2017-2018,2020-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*===========================================================================

                           EDIT HISTORY FOR FILE
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/26/22   rama    change index type to uint32 in dload_mem_debug_get_entry_by_index
06/17/21   rama    Moved to dbginfo lib.
12/09/20   ck      Removed dload_mem_debug_is_remap_needed
07/15/20   yps     Avoid to do dload_mem_debug_init multi-times
06/11/20   yps     Support multi restricted regions dump
05/29/20   rama    Removed boot_dload.h
07/10/18   yps     Added DL_LOG api for ramdump
11/02/17   aus     Added support for post target init
10/12/17   aus     Moved structures and defines
05/22/17   yps     Increase script buffer size to 4KB
04/13/17   kpa     Added MAX_CRASHDUMP_TABLE_ENTRIES
04/04/17   kpa     Increase dload debug info regions
10/05/15   ck      Corrected copyright
06/03/15   as      Support 64bit debug only.
01/16/15   kpa     Update dload_debug_type
10/29/14   kpa     Support 64 bit memory map
09/23/14   ck      Moved target specific functions dload_mem_debug_is_device_retail_unlocked
                   and dload_mem_debug_supported to boot_dload_debug_target.
06/12/14   kedara  Update to support 64-bit MSM8996 compiler syntax.
05/30/14   kedara  Replace snprintf by qsnprintf.
03/17/14   ck      Added logic to search for QSEE header info from sbl qsee interface
03/17/14   ck      Added dload_mem_debug_zero_peripheral_memory function
03/17/14   ck      Replaced stubs with calls to seccfg driver
01/10/14   ck      Bear family does not need to share ram_dumped_allowed and device_retail_unlocked
12/18/13   ck      Removed boot_dload_dump_tz and boot_dload_is_tz_dump_allowed
12/10/13   ck      boot_is_auth_enabled does not have a return value now
12/06/13   ck      Replaced calls to boot_pbl_is_auth_enabled with boot_is_auth_enabled
11/21/13   ck      Removed boot_set_tz_execute_status
11/21/13   ck      Started changing logic in dload_mem_debug_supported for Bear
11/12/13   kedara  Added changes to support SBL crash dumps
10/11/13   jz      Added remapping functions
09/25/13   aus     Added support for retail unlock dumps
07/01/13   dh      Add 64 bits memory dump support
05/31/13   sy      Replace memcpy to strlcpy
04/24/13   jlaver  Add security check for boot_dload_dump_tz
02/28/13   kedara  Support TZ ramdump check only after TZ is loaded.
02/15/13   dh      Add boot_dload_dump_tz
02/11/13   dh      Add dload_mem_debug_supported
02/03/12   kpa     Fix integer overflow issues with end address calculation.
09/23/11   dh      move mob_sw_rev define from boot_dload_stubs.c to this file
09/14/11   dh      Rename to boot_dload_debug.c, remove unused include header
08/09/10   kpa     Merge code from 9x15 build for PW1.2.
10/13/10   plc     Updating to not depend on time api, not depricated clk api
07/23/10   niting  Added API to support fixed string length required by Sahara.
06/07/10   niting  Added support for Sahara memory dump.
01/10/06   tbg     Modified to compile with boot loader images.
10/20/05   tbg     Ported to msmshared. Moved some functions to target
                   specific file dload_debug_xxxx.c
08/01/05   ih      Created.

===========================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <boot_target.h>
#include <boot_dload_debug.h>
#include <boot_comdef.h>
#include <boot_shared_imem_cookie.h>
#include <boot_logger.h>
#include "boot_memory_mgr_if.h"
#include <boot_config_context.h>
#include <boot_ramdump_table_if.h>
#include <boot_dbginfo_if.h>
#include <boot_framework.h>

static boot_handle config_context_handle;

/*===========================================================================

                     EXTERNAL DEFINITIONS FOR MODULE

===========================================================================*/

void dload_log(const char *log, ...)
{
  va_list list = {0};
  char log_buffer[100];
  memset(log_buffer, 0, 100);
  va_start(list, log);
  vsnprintf(log_buffer, 100, log, list);
  va_end(list);
  boot_log_message(log_buffer);
}

ramdump_table_type* dload_mem_debug_get_entry_by_index (uint32 index)
{
  bl_error_boot_type status = BL_ERR_NONE;
  ramdump_table_if *rd_table_if = NULL;
  boot_handle *ramdump_table_handle = NULL;
  ramdump_table_type *rd_table_ptr = NULL;
  uintnt rd_table_entry_count = 0;

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void **)&rd_table_if);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("get_ptr error");
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_HANDLE, (void **)&ramdump_table_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = rd_table_if->get_table_len(ramdump_table_handle, &rd_table_entry_count);
    if (status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }

    rd_table_entry_count/=sizeof(ramdump_table_type);

    status = rd_table_if->get_table_addr(ramdump_table_handle, (uintnt*)&rd_table_ptr);

    if (status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }

    if (index > rd_table_entry_count)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }

  } while (FALSE);

  if (status == BL_ERR_NONE)
  {
    return &rd_table_ptr[index];
  }

  return NULL;
}

/*===========================================================================

FUNCTION DLOAD_MEM_DEBUG_INIT

DESCRIPTION
  This function call the function to do target specific initialization,
  and sets up the script.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void dload_mem_debug_init(boot_handle config_context)
{
  config_context_handle = config_context;
}


/*===========================================================================

FUNCTION DLOAD_MEM_DEBUG_LEN

DESCRIPTION
  This function returns length of the debug info response

DEPENDENCIES
  None.

RETURN VALUE
  length of the debug info response

SIDE EFFECTS
  None.

===========================================================================*/
uint32 dload_mem_debug_len(void)
{
  bl_error_boot_type status = BL_ERR_NONE;
  ramdump_table_if *rd_table_if = NULL;
  boot_handle *ramdump_table_handle = NULL;
  uintnt rd_table_size_bytes = 0;

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void **)&rd_table_if);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("get_ptr error");
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_HANDLE, (void **)&ramdump_table_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = rd_table_if->get_table_len(ramdump_table_handle, &rd_table_size_bytes);
    if (status != BL_ERR_NONE)
    {
      break;
    }
  } while (FALSE);

  return rd_table_size_bytes;
}

/*===========================================================================

FUNCTION DLOAD_MEM_DEBUG_VERIFY_ADDR

DESCRIPTION
  This function checks to see if it belongs to a region of memory that can be
  dumped.

DEPENDENCIES
  None.

RETURN VALUE
  TRUE if the address verifies, else FALSE.

SIDE EFFECTS
  None.

===========================================================================*/
boolean dload_mem_debug_verify_addr(uint64 base, uint64 len)
{
  bl_error_boot_type status = BL_ERR_NONE;
  ramdump_table_if *rd_table_if = NULL;
  boot_handle *ramdump_table_handle = NULL;
  boot_boolean verified_flag = 0;

  do
  {
    status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void **)&rd_table_if);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("get_ptr error");
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }

    status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_HANDLE, (void **)&ramdump_table_handle);
    if (status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }

    status = rd_table_if->verify_addr (ramdump_table_handle, base, len, &verified_flag);
    if (status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }
  } while (FALSE);

  return verified_flag;
}

/*===========================================================================

FUNCTION DLOAD_MEM_DEBUG_IS_RESTRICTED_ADDR

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
boolean dload_mem_debug_is_restricted_addr(uint64 base, uint64 len)
{
  bl_error_boot_type status = BL_ERR_NONE;
  ramdump_table_if *rd_table_if = NULL;
  boot_handle *ramdump_table_handle = NULL;
  boot_boolean verified_flag = 0;

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void **)&rd_table_if);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("get_ptr error");
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_HANDLE, (void **)&ramdump_table_handle);
    if (status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }

    status = rd_table_if->verify_restricted_addr (ramdump_table_handle, base, len, &verified_flag);
    if (status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }
  } while (FALSE);

  return verified_flag;
}


/*===========================================================================

FUNCTION DLOAD_MEM_DEBUG_COPY_RESTRICTED_REGION

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

bl_error_boot_type dload_mem_debug_copy_restricted_region(uint8 *buf, uint64 addr, uint64 len)
{
  bl_error_boot_type status = BL_ERR_NONE;
  ramdump_table_if *rd_table_if = NULL;
  boot_handle *ramdump_table_handle = NULL;
  boot_boolean verified_flag = 0;

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void **)&rd_table_if);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("get_ptr error");
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_HANDLE, (void **)&ramdump_table_handle);
    if (status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }

    status = rd_table_if->copy_restricted (buf, addr, len);
    if (status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_TABLE_ENTRY_PASSED);
      break;
    }
  } while (FALSE);

  return verified_flag;
}

/*===========================================================================

FUNCTION DLOAD_MEM_DEBUG_NUM_ENT

DESCRIPTION
  This function returns number of entries in the mem_debug_info table

DEPENDENCIES
  None.

RETURN VALUE
  number of entries in the mem_debug_info table

SIDE EFFECTS
  None.

===========================================================================*/
uint32 dload_mem_debug_num_ent(void)
{
  bl_error_boot_type status = BL_ERR_NONE;
  ramdump_table_if *rd_table_if = NULL;
  boot_handle *ramdump_table_handle = NULL;
  uintnt rd_table_entry_count = 0;

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void **)&rd_table_if);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("get_ptr error");
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_HANDLE, (void **)&ramdump_table_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = rd_table_if->get_table_len(ramdump_table_handle, &rd_table_entry_count);
    if (status != BL_ERR_NONE)
    {
      rd_table_entry_count = 0;
      break;
    }

    rd_table_entry_count/=sizeof(ramdump_table_type);
  } while (FALSE);

  return rd_table_entry_count;
}

/*===========================================================================

FUNCTION DLOAD_MEM_DEBUG_SAVE_PREF

DESCRIPTION
  This function returns the save preference of a given region

DEPENDENCIES
  None.

RETURN VALUE
  save preference of a given region
  0 if invalid region number
SIDE EFFECTS
  None.

===========================================================================*/
uint8 dload_mem_debug_save_pref(uint32 index)
{
  ramdump_table_type *rd_table_ptr = NULL;

  rd_table_ptr = dload_mem_debug_get_entry_by_index(index);

  if (rd_table_ptr)
  {
    return rd_table_ptr->save_pref;
  }

  return 0;
}


/*===========================================================================

FUNCTION DLOAD_MEM_DEBUG_MEM_BASE

DESCRIPTION
  This function returns the memory base of a given region

DEPENDENCIES
  None.

RETURN VALUE
  memory base of a given region
  0 if invalid region number

SIDE EFFECTS
  None.

===========================================================================*/
uint64 dload_mem_debug_mem_base(uint32 index)
{
  ramdump_table_type *rd_table_ptr = NULL;

  rd_table_ptr = dload_mem_debug_get_entry_by_index(index);

  if (rd_table_ptr)
  {
    return rd_table_ptr->mem_base;
  }

  return 0;
}
/*===========================================================================

FUNCTION DLOAD_MEM_DEBUG_MEM_LENGTH

DESCRIPTION
  This function returns the memory length of a given region

DEPENDENCIES
  None.

RETURN VALUE
  memory length of a given region
  0 if invalid region number

SIDE EFFECTS
  None.

===========================================================================*/
uint64 dload_mem_debug_mem_length(uint32 index)
{
  ramdump_table_type *rd_table_ptr = NULL;

  rd_table_ptr = dload_mem_debug_get_entry_by_index(index);

  if (rd_table_ptr)
  {
    return rd_table_ptr->length;
  }

  return 0;
}

/*===========================================================================

FUNCTION DLOAD_MEM_DEBUG_DESC

DESCRIPTION
  This function returns the description of a given region

DEPENDENCIES
  None.

RETURN VALUE
  description of a given region
  NULL if invalid region number

SIDE EFFECTS
  None.

===========================================================================*/
char *dload_mem_debug_desc(uint32 index)
{
  ramdump_table_type *rd_table_ptr = NULL;

  rd_table_ptr = dload_mem_debug_get_entry_by_index(index);
  if (rd_table_ptr)
  {
    return rd_table_ptr->desc;
  }

  return NULL;
}

/*===========================================================================

FUNCTION DLOAD_MEM_DEBUG_FILENAME

DESCRIPTION
  This function returns the filename of a given region

DEPENDENCIES
  None.

RETURN VALUE
  filename of a given region
  NULL if invalid region number

SIDE EFFECTS
  None.

===========================================================================*/
char *dload_mem_debug_filename(uint32 index)
{
  ramdump_table_type *rd_table_ptr = NULL;

  rd_table_ptr = dload_mem_debug_get_entry_by_index(index);
  if (rd_table_ptr)
  {
    return rd_table_ptr->filename;
  }

  return NULL;
}

boolean dload_mem_debug_supported()
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boolean mem_dump_supported = FALSE;
  boot_dbginfo_if_type *dbginfo_if = NULL;

  return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_DBGINFO_INTERFACE, (void **)&dbginfo_if);
  if(return_status != BL_ERR_NONE)
    return FALSE;

  return_status = dbginfo_if->is_ramdump_allowed((boot_boolean*)&mem_dump_supported);
  if(return_status != BL_ERR_NONE)
    return FALSE;
  return mem_dump_supported;
}
