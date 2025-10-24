/*=============================================================================

                     Boot Blacklist Library

GENERAL DESCRIPTION
  This file contains the implementation for the boot-specific blacklist based
  module, to facilitate preventing the address spaces from being overwritten
  where data has already been loaded.

Copyright 2020-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
10/07/22   Rhythm       Added a condition for overlapping memory
10/13/20   digants      Initial revision.
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <string.h>
#include "boot_blacklist_if.h"
#include "boot_config_context.h"
#include "boot_memory_mgr_if.h"
#include "boot_error_if.h"

/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
//blacklist handle ID
#define BLST 0x424c5354

// blacklist entry object
typedef struct blacklist_tbl_entry
{
  uintnt start_addr;
  uintnt size;
  struct blacklist_tbl_entry *next_bl_entry;
} blacklist_tbl_entry_type;

// blacklist_info_obj
typedef struct blacklist_info_obj
{
  uint32 id;
  uint32 num_entries;
  uint32 rollback_marker;
  uint32 is_disabled;
  boot_memory_mgr_if_type *mem_if;
  blacklist_tbl_entry_type *entries;
} blacklist_info;

static blacklist_info bl_info;

typedef struct blacklist_region
{
  uintnt addr;
  uintnt size;
} boot_bl_region;

/* static blacklist for regions
that are to be blacklisted before loading any image */
static boot_bl_region static_blacklist[]=
{
  {SCL_SBL1_DDR_BASE, SCL_SBL1_DDR_SIZE}
};


/*=============================================================================

FUNCTION DEFINITIONS

=============================================================================*/

/*=========================================================================

**  Function :  _init

** ==========================================================================
*/
/*!
*
* @brief
*   initialize the internal structure.
*
* @param[in] pointer to blacklist_info_obj
*
*/
static void _init(blacklist_info *obj)
{
  memset((void *)obj, 0, sizeof(blacklist_info));
  obj->id = BLST;
  obj->num_entries = 0;
  obj->rollback_marker = 0;
  obj->is_disabled = 0;
  obj->mem_if = NULL;
  obj->entries = NULL;
}

/*=========================================================================

**  Function :  boot_blacklist_check_region_and_update

** ==========================================================================
*/
/*!
*
* @brief
* Function to check address range against the blacklist and update the blacklist
* with the new region.
*
* @param[in] start address of the range
* @param[in] size of the address range
*
*/
static bl_error_boot_type boot_blacklist_check_region_and_update(uintnt start_addr, uintnt size)
{
  bl_error_boot_type error = BL_ERR_NONE;
  blacklist_tbl_entry_type *blist = NULL;
  blacklist_tbl_entry_type *curr_entry = bl_info.entries;
  blacklist_tbl_entry_type *prev_entry = bl_info.entries;

  if (!size || ((start_addr + size) < start_addr))
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLACKLIST, BL_ERR_INVALID_PARAMETER);
  }

  if (bl_info.id != BLST)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLACKLIST, BL_ERR_BLACKLIST_NOT_INITIALIZED);
  }

  // iterate over the list to check for overlaps with already blacklisted regions
  while (curr_entry != NULL)
  {
    if (
        /* New segment starts in middle of current memory block */
        ((start_addr >= (curr_entry->start_addr)) && (start_addr < (curr_entry->start_addr + curr_entry->size)))
        /* New segment ends in middle of current memory block */
        || (((start_addr + size) > (curr_entry->start_addr)) && ((start_addr + size) <= (curr_entry->start_addr + curr_entry->size)))
        /* New segment covers entire current memory block */
        || ((start_addr <= (curr_entry->start_addr)) && (curr_entry->start_addr < (start_addr + size)))
       )
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BLACKLIST, BL_ERR_LOADING_IN_BLACKLISTED_REGION);
      break;
    }

    prev_entry = curr_entry;
    curr_entry = curr_entry->next_bl_entry;
  }

  // if disabled still check against current list but return without updating
  if (bl_info.is_disabled == 0x1)
  {
    return error;
  }

  // update the blacklist table if region not found in blacklist
  if (error == BL_ERR_NONE)
  {
    error = bl_info.mem_if->malloc(sizeof(blacklist_tbl_entry_type), (void *)&blist);
    if (error == BL_ERR_NONE && blist != NULL)
    {
      blist->start_addr = start_addr;
      blist->size = size-1;
      blist->next_bl_entry = NULL;

      if (bl_info.num_entries == 0)
      {
        bl_info.entries = blist;
      }
      else
      {
        prev_entry->next_bl_entry = blist;
      }

      bl_info.num_entries++;
    }
  }

  return error;
}

/*=========================================================================

**  Function :  boot_blacklist_commit_and_udpate_marker

** ==========================================================================
*/
/*!
*
* @brief
* Function to commit the set of blacklist in the table and
* update the rollback marker.
*
*/
static bl_error_boot_type boot_blacklist_commit_and_udpate_marker(void)
{
  bl_error_boot_type error = BL_ERR_NONE;

  if (bl_info.id != BLST)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLACKLIST, BL_ERR_BLACKLIST_NOT_INITIALIZED);
  }
  else if (bl_info.num_entries == 0 || bl_info.is_disabled == 1)
  {
    return error;
  }

  // update the marker to last entry so all the entries are commited
  bl_info.rollback_marker = bl_info.num_entries;

  return error;
}


/*=========================================================================

**  Function :  boot_blacklist_rollback_to_last_commit

** ==========================================================================
*/
/*!
*
* @brief
* Function to commit the set of blacklist in the table and
* update the rollback marker.
*
*/
static bl_error_boot_type boot_blacklist_rollback_to_last_commit(void)
{
  bl_error_boot_type error = BL_ERR_NONE;
  blacklist_tbl_entry_type *curr_entry = bl_info.entries;
  blacklist_tbl_entry_type *temp = NULL;
  uint32 entry_num = 1;
  uint32 updated_num_entries = 0;

  if (bl_info.id != BLST)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLACKLIST, BL_ERR_BLACKLIST_NOT_INITIALIZED);
  }

  if (bl_info.num_entries == 0 || bl_info.is_disabled == 1)
  {
    return error;
  }


  while (entry_num <= bl_info.num_entries)
  {
    temp = curr_entry;
    curr_entry = curr_entry->next_bl_entry;

    // delete all entries added after the rollback marker
    if (entry_num > bl_info.rollback_marker)
    {
      //clear the memory regions as well to avoid stale content
      memset((void *)(temp->start_addr), 0, temp->size);
      error = (bl_info.mem_if)->free(temp);
      if (error != BL_ERR_NONE)
      {
        break;
      }
    }
    else
    {
      if (entry_num == bl_info.rollback_marker)
      {
        temp->next_bl_entry = NULL;
      }
      updated_num_entries = entry_num;
    }
    entry_num++;
  }
  bl_info.num_entries = updated_num_entries;

  return error;
}

/*=========================================================================

**  Function :  boot_blacklist_disable

** ==========================================================================
*/
/*!
*
* @brief
* Function to disable blacklist updates
*
* @param[in] None
*
*/
static bl_error_boot_type boot_blacklist_disable(void)
{
  if (bl_info.id != BLST)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLACKLIST, BL_ERR_BLACKLIST_NOT_INITIALIZED);
  }

  bl_info.is_disabled = 0x1;

  return BL_ERR_NONE;
}


/*=========================================================================

**  Function :  boot_blacklist_enable

** ==========================================================================
*/
/*!
*
* @brief
* Function to enable blacklist updates
*
* @param[in] None
*
*/
static bl_error_boot_type boot_blacklist_enable(void)
{
  if (bl_info.id != BLST)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLACKLIST, BL_ERR_BLACKLIST_NOT_INITIALIZED);
  }

  bl_info.is_disabled = 0x0;

  return BL_ERR_NONE;
}

/*=========================================================================

**  Function :  boot_blacklist_init

** ==========================================================================
*/
/*!
*
* @brief
*   Function to initialize blacklist object.
*
* @param[in] config_context_handle
*
*/
static bl_error_boot_type boot_blacklist_init(const boot_handle config_context_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_mgr_if = NULL;
  uint32 static_bl_idx = 0;

  if (config_context_handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLACKLIST, BL_ERR_INVALID_PARAMETER);
  }

  error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_mgr_if);
  if (error != BL_ERR_NONE)
  {
    return error;
  }
  if (mem_mgr_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLACKLIST, BL_ERR_INTERFACE_FAILURE);
  }

  _init(&bl_info);

  bl_info.mem_if = mem_mgr_if;

  // Add the regions in blacklist from the static table
  for (static_bl_idx =0; static_bl_idx < ((sizeof(static_blacklist))/(sizeof(boot_bl_region))); static_bl_idx++)
  {
    if (static_blacklist[static_bl_idx].size == 0)
    {
      continue;
    }

    error = boot_blacklist_check_region_and_update(static_blacklist[static_bl_idx].addr, static_blacklist[static_bl_idx].size);
    if (error != BL_ERR_NONE)
    {
      break;
    }

    error = boot_blacklist_commit_and_udpate_marker();
    if (error != BL_ERR_NONE)
    {
      break;
    }
  }

  return error;
}

/*=========================================================================

**  Function :  boot_blacklist_deinit

** ==========================================================================
*/
/*!
*
* @brief
* Function to deinit the blacklist table and info
*
* @param[in] boot_handle
*
*/
static bl_error_boot_type boot_blacklist_deinit(void)
{
  bl_error_boot_type error = BL_ERR_NONE;
  blacklist_tbl_entry_type *curr_entry = bl_info.entries;
  blacklist_tbl_entry_type *temp = NULL;

  if (bl_info.id != BLST)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLACKLIST, BL_ERR_BLACKLIST_NOT_INITIALIZED);
  }

  while (curr_entry != NULL)
  {
    temp = curr_entry;
    curr_entry = curr_entry->next_bl_entry;

    memset((void *)(temp->start_addr), 0, temp->size);
    error = (bl_info.mem_if)->free(temp);
    if (error != BL_ERR_NONE)
    {
      break;
    }
  }

  if (error == BL_ERR_NONE)
  {
    _init(&bl_info);
    bl_info.id = 0x0;
  }

  return error;
}


/*=========================================================================

**  Function :  boot_blacklist_get_interface

** ==========================================================================
*/
/*!
*
* @brief
* Function to get blacklist through the handle.
*
* @param[in] start address of the range
*
*/
bl_error_boot_type boot_blacklist_get_interface(void *blacklist_if)
{
  bl_error_boot_type error = BL_ERR_NONE;

  if (blacklist_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLACKLIST, BL_ERR_INVALID_PARAMETER);
  }

  ((boot_blacklist_if_type *)blacklist_if)->init = boot_blacklist_init;
  ((boot_blacklist_if_type *)blacklist_if)->check_region_and_update = boot_blacklist_check_region_and_update;
  ((boot_blacklist_if_type *)blacklist_if)->commit_and_udpate_marker = boot_blacklist_commit_and_udpate_marker;
  ((boot_blacklist_if_type *)blacklist_if)->rollback_to_last_commit = boot_blacklist_rollback_to_last_commit;
  ((boot_blacklist_if_type *)blacklist_if)->disable = boot_blacklist_disable;
  ((boot_blacklist_if_type *)blacklist_if)->enable = boot_blacklist_enable;
  ((boot_blacklist_if_type *)blacklist_if)->deinit = boot_blacklist_deinit;

  return error;
}
